///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// MomentCapacitySolver.cpp : Implementation of CMomentCapacitySolver
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "MomentCapacitySolver.h"
#include "MomentCapacitySolution.h"
#include <WBFLGeometry.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMomentCapacitySolver
HRESULT CMomentCapacitySolver::FinalConstruct()
{
   m_GeneralSolver.CoCreateInstance(CLSID_GeneralSectionSolver);
   m_IncrementalStrainPlane.CoCreateInstance(CLSID_Plane3d);

   m_P1.CoCreateInstance(CLSID_Point3d);
   m_P2.CoCreateInstance(CLSID_Point3d);
   m_P3.CoCreateInstance(CLSID_Point3d);

   m_AxialTolerance = 0.01;
   m_MaxIter = 50;

   return S_OK;
}

void CMomentCapacitySolver::FinalRelease()
{
   m_GeneralSolver.Release();
   m_GeneralSolution.Release();
   m_TensionSolution.Release();
   m_CompressionSolution.Release();
   m_IncrementalStrainPlane.Release();
   m_P1.Release();
   m_P2.Release();
   m_P3.Release();
}


STDMETHODIMP CMomentCapacitySolver::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMomentCapacitySolver,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IMomentCapacitySolver
STDMETHODIMP CMomentCapacitySolver::put_AxialTolerance(Float64 tolerance)
{
   m_AxialTolerance = tolerance;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolver::get_AxialTolerance(Float64* tolerance)
{
   CHECK_RETVAL(tolerance);
   *tolerance = m_AxialTolerance;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolver::put_MaxIterations(long maxIter)
{
   m_MaxIter = maxIter;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolver::get_MaxIterations(long* maxIter)
{
   CHECK_RETVAL(maxIter);
   *maxIter = m_MaxIter;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolver::put_Slices(long nSlices)
{
   return m_GeneralSolver->put_Slices(nSlices);
}

STDMETHODIMP CMomentCapacitySolver::get_Slices(long* nSlices)
{
   return m_GeneralSolver->get_Slices(nSlices);
}

STDMETHODIMP CMomentCapacitySolver::put_SliceGrowthFactor(Float64 sliceGrowthFactor)
{
   return m_GeneralSolver->put_SliceGrowthFactor(sliceGrowthFactor);
}

STDMETHODIMP CMomentCapacitySolver::get_SliceGrowthFactor(Float64* sliceGrowthFactor)
{
   return m_GeneralSolver->get_SliceGrowthFactor(sliceGrowthFactor);
}

STDMETHODIMP CMomentCapacitySolver::putref_Section(IGeneralSection* pSection)
{
   m_bUpdateLimits = true;
   return m_GeneralSolver->putref_Section(pSection);
}

STDMETHODIMP CMomentCapacitySolver::get_Section(IGeneralSection** pSection)
{
   return m_GeneralSolver->get_Section(pSection);
}

STDMETHODIMP CMomentCapacitySolver::Solve(Float64 Fz,Float64 angle,Float64 k_or_ec,Float64 strainLocation,SolutionMethod solutionMethod,IMomentCapacitySolution** solution)
{
   // initialize some parameters using during the solution
   m_bAnalysisPointUpdated = false;

   // Get the forces and strains that bound the solution

   // Get the maximum tension force and moments at the zero curvature case (pure tension case)
   Float64 FzT, MxT, MyT, eoT;
   TensionLimit(&FzT,&MxT,&MyT,&eoT);

   // Get the maximum compression force and moments at the zero curvature case (pure compression case)
   Float64 FzC, MxC, MyC, eoC;
   CompressionLimit(&FzC,&MxC,&MyC,&eoC);

   if ((IsZero(FzT) && IsZero(MxT) && IsZero(MyT)) || (IsZero(FzC) && IsZero(MxC) && IsZero(MyC)))
   {
      // no tension or compression capacity so the capacity is zeron
      return ZeroCapacitySolution(solution);
   }

   if ( IsEqual(Fz,FzC) || IsEqual(Fz,FzT) )
   {
      // The axial force is equal to the tension or compression capacity so we have our solution

      // start with a zero capacity solution sinced it is initialized for the zero curvature case
      HRESULT hr = ZeroCapacitySolution(solution);


      // populate the solution object with the values from the controlling case
      CComPtr<IPoint2d> cgT, cgC;
      (*solution)->get_CompressionResultantLocation(&cgC);
      (*solution)->get_TensionResultantLocation(&cgT);
      
      Float64 T,C;
      (*solution)->get_CompressionResultant(&C);
      (*solution)->get_TensionResultant(&T);

      CComPtr<IPlane3d> incrementalStrainPlane;
      (*solution)->get_IncrementalStrainPlane(&incrementalStrainPlane);

      ATLASSERT(m_bAnalysisPointUpdated == true);

      if (IsEqual(Fz,FzC))
      {
         (*solution)->InitSolution(FzC,MxC,MyC, incrementalStrainPlane,m_ExtremeCompressionPoint,cgC,C,m_ExtremeTensionPoint,cgT,T,0.0,m_CompressionSolution);
      }
      else
      {
         (*solution)->InitSolution(FzT,MxT,MyT, incrementalStrainPlane, m_ExtremeCompressionPoint,cgC,C, m_ExtremeTensionPoint,cgT,T, 0.0,m_TensionSolution);
      }

      return hr;
   }

   return AnalyzeSection(Fz, angle, k_or_ec, solutionMethod, strainLocation, solution);
}

STDMETHODIMP CMomentCapacitySolver::get_PlasticCentroid(IPoint2d** pcg)
{
   CHECK_RETOBJ(pcg);

   Float64 P, Mx, My, eo;
   CompressionLimit(&P,&Mx,&My,&eo);

   Float64 x = -My/P;
   Float64 y =  Mx/P;

   x = IsZero(x) ? 0 : x;
   y = IsZero(y) ? 0 : y;

   CComPtr<IPoint2d> cg;
   cg.CoCreateInstance(CLSID_Point2d);
   cg->Move(x,y);

   *pcg = cg;
   (*pcg)->AddRef();
   return S_OK;
}

HRESULT CMomentCapacitySolver::UpdateLimits()
{
   if (!m_bUpdateLimits)
   {
      return S_OK;
   }

   CComPtr<IGeneralSection> section;
   get_Section(&section);

   Float64 compStrain =  -Float64_Max;
   Float64 tensStrain = -Float64_Max;
   
   CollectionIndexType nShapes;
   section->get_ShapeCount(&nShapes);
   for (CollectionIndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++)
   {
      CComPtr<IStressStrain> material;
      section->get_ForegroundMaterial(shapeIdx, &material);

      if (material == nullptr)
      {
         continue; // shape is a void
      }

      Float64 min_strain, max_strain;
      material->StrainLimits(&min_strain, &max_strain);
      compStrain = Max(min_strain, compStrain);
      ATLASSERT(compStrain <= 0);

      tensStrain = Max(max_strain, tensStrain);
      ATLASSERT(0 <= tensStrain);
   }

   m_eoCompressionLimit = compStrain;
   m_IncrementalStrainPlane->ThroughAltitude(compStrain);

   long nSlices;
   get_Slices(&nSlices);

   put_Slices(1);
   HRESULT hr = m_GeneralSolver->Solve(m_IncrementalStrainPlane, &m_CompressionSolution.p);
   put_Slices(nSlices);

   if (SUCCEEDED(hr))
   {
      m_CompressionSolution->get_Fz(&m_FzCompressionLimit);
      m_CompressionSolution->get_Mx(&m_MxCompressionLimit);
      m_CompressionSolution->get_My(&m_MyCompressionLimit);
   }
   else
   {
      return hr;
   }

   m_eoTensionLimit = tensStrain;
   m_IncrementalStrainPlane->ThroughAltitude(tensStrain);

   put_Slices(1);
   hr = m_GeneralSolver->Solve(m_IncrementalStrainPlane, &m_TensionSolution.p);
   put_Slices(nSlices);

   if (SUCCEEDED(hr))
   {
      m_TensionSolution->get_Fz(&m_FzTensionLimit);
      m_TensionSolution->get_Mx(&m_MxTensionLimit);
      m_TensionSolution->get_My(&m_MyTensionLimit);
   }
   else
   {
      return hr;
   }

   m_bUpdateLimits = false;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolver::CompressionLimit(Float64* Fz,Float64* Mx,Float64* My,Float64* eo)
{
   CHECK_RETVAL(Fz);
   CHECK_RETVAL(Mx);
   CHECK_RETVAL(My);
   CHECK_RETVAL(eo);

   HRESULT hr = UpdateLimits();
   if (FAILED(hr))
   {
      return hr;
   }

   *Fz = m_FzCompressionLimit;
   *Mx = m_MxCompressionLimit;
   *My = m_MyCompressionLimit;
   *eo = m_eoCompressionLimit;

   return S_OK;
}

STDMETHODIMP CMomentCapacitySolver::TensionLimit(Float64* Fz,Float64* Mx,Float64* My,Float64* eo)
{
   CHECK_RETVAL(Fz);
   CHECK_RETVAL(Mx);
   CHECK_RETVAL(My);
   CHECK_RETVAL(eo);

   HRESULT hr = UpdateLimits();
   if (FAILED(hr))
   {
      return hr;
   }

   *Fz = m_FzTensionLimit;
   *Mx = m_MxTensionLimit;
   *My = m_MyTensionLimit;
   *eo = m_eoTensionLimit;

   return S_OK;
}

void CMomentCapacitySolver::UpdateStrainPlane(Float64 angle,Float64 k_or_ec,Float64 strainLocation,SolutionMethod solutionMethod,Float64 eo)
{
   UpdateAnalysisPoints(angle, solutionMethod, strainLocation);

   if ( solutionMethod == smFixedCurvature )
   {
      // curvature is fixed... move the strain plain up/down changing the strain at the extreme point
      Float64 k = k_or_ec;
      if ( IsZero(k,1e-6) )
      {
         m_IncrementalStrainPlane->ThroughAltitude(eo);
      }
      else
      {
         // P1 and P2 are arbitrary points on the neutral axis where strain = 0.0
         Float64 d = 1000; // distance between P1 and P2.

         Float64 sin_angle = sin(angle);
         Float64 cos_angle = cos(angle);

         m_P1->Move(-eo*sin_angle/k - d*cos_angle,
                     eo*cos_angle/k - d*sin_angle,
                    0.0
                    );

         m_P2->Move(-eo*sin_angle/k + d*cos_angle,
                     eo*cos_angle/k + d*sin_angle,
                    0.0
                    );

         m_P3->Move( 0, 0, eo );

         m_IncrementalStrainPlane->ThroughPoints(m_P1,m_P2,m_P3);
      }
   }
   else
   {
      // Curvature varies. 
      Float64 ec = k_or_ec;

#if defined _DEBUG
      if (solutionMethod == smFixedCompressionStrain)
         ATLASSERT(ec <= 0); // compression is negative
      else if (solutionMethod == smFixedTensionStrain) 
         ATLASSERT(0 <= ec); // tension is positive
      else if (solutionMethod == smFixedStrain)
      {
      } // do nothing
      else
         ATLASSERT(false); // shouldn't get here
#endif

      if ( IsEqual(ec,eo) )
      {
         m_IncrementalStrainPlane->ThroughAltitude(eo);
      }
      else
      {
         UpdateControlPoints(angle, solutionMethod, strainLocation);

         Float64 d = 1000; // distance between P1 and P2.
         Float64 sin_angle = sin(angle);
         Float64 cos_angle = cos(angle);
         if (solutionMethod == smFixedStrain)
         {
            Float64 yna = ec / eo; // distance from where strain is known to the neutral axis
            m_P1->Move(-yna * sin_angle - d * cos_angle, strainLocation + yna * cos_angle - d * sin_angle, 0.0);
            m_P2->Move(-yna * sin_angle + d * cos_angle, strainLocation + yna * cos_angle + d * sin_angle, 0.0);
         }
         else
         {
            Float64 X, Y;
            m_ControlPoint->Location(&X, &Y);
            m_P1->Move(X - d * cos_angle, Y - d * sin_angle, eo);
            m_P2->Move(X + d * cos_angle, Y + d * sin_angle, eo);
         }

         Float64 X, Y;
         m_FixedPoint->Location(&X, &Y);
         m_P3->Move(X, Y, ec);

         // The strain plain is defined by three points. One point is where the strain is fixed
         // The other two define a line of constant strain through the trial strain value
         m_IncrementalStrainPlane->ThroughPoints(m_P1, m_P2, m_P3);
      }
   }
}

void CMomentCapacitySolver::UpdateAnalysisPoints(Float64 angle, SolutionMethod solutionMethod,Float64 strainLocation)
{
   if (m_bAnalysisPointUpdated)
      return;

   CComPtr<IGeneralSection> section;
   m_GeneralSolver->get_Section(&section);

   // create a line parallel to the neutral axis passing through (0,0)
   // The IShape::FurthestPoint method returns the furthest point of the shape on the right side of a line.
   // Compression is on the left side of the neutral axis. If the solutionMethod is smFixedCompressionStrain
   // then the line must be in the opposite direction of the neutral axis.
   CComPtr<IVector2d> compression_line_direction, tension_line_direction;
   compression_line_direction.CoCreateInstance(CLSID_Vector2d);
   tension_line_direction.CoCreateInstance(CLSID_Vector2d);

   // for compression, add 180deg so the line is in the opposite direction of the neutral axis
   compression_line_direction->put_Direction(angle + M_PI);
   tension_line_direction->put_Direction(angle);
   
   CComPtr<ILine2d> compression_side_line, tension_side_line;
   compression_side_line.CoCreateInstance(CLSID_Line2d);
   tension_side_line.CoCreateInstance(CLSID_Line2d);

   CComPtr<IPoint2d> origin;
   origin.CoCreateInstance(CLSID_Point2d);
   origin->Move(0,0);

   compression_side_line->SetExplicit(origin, compression_line_direction);
   tension_side_line->SetExplicit(origin, tension_line_direction);

   // Find the furthest distance from the right side of this line to the section.
   // This is the distance from the origin to the extreme tension or compression fiber, depending on the direction of the line.

   // IShape::FurthestPoint will return a value less than zero if the entire shape
   // is on the opposite side of the line than we are interested in.

   CComPtr<IPoint2d> pntCompression, pntTension;
   Float64 dCompression = -Float64_Max;
   Float64 dTension = -Float64_Max;
   CollectionIndexType shape_count;
   section->get_ShapeCount(&shape_count);
   for ( CollectionIndexType shapeIdx = 0; shapeIdx < shape_count; shapeIdx++ )
   {
      CComPtr<IShape> shape;
      section->get_Shape(shapeIdx,&shape);

      CComPtr<IPoint2d> pntC, pntT;
      Float64 dist_compression, dist_tension;
      shape->FurthestPoint(compression_side_line, &pntC, &dist_compression);
      shape->FurthestPoint(tension_side_line, &pntT, &dist_tension);

      if (dCompression < dist_compression)
      {
         dCompression = dist_compression;
         pntCompression.Release();
         pntC.CopyTo(&pntCompression);
      }

      if (dTension < dist_tension)
      {
         dTension = dist_tension;
         pntTension.Release();
         pntT.CopyTo(&pntTension);
      }
   }

   m_ExtremeCompressionPoint.Release();
   m_ExtremeCompressionPoint = pntCompression;

   m_ExtremeTensionPoint.Release();
   m_ExtremeTensionPoint = pntTension;

   m_bAnalysisPointUpdated = true;
}

void CMomentCapacitySolver::UpdateControlPoints(Float64 angle, SolutionMethod solutionMethod, Float64 strainLocation)
{
   ATLASSERT(solutionMethod == smFixedCompressionStrain || solutionMethod == smFixedTensionStrain || solutionMethod == smFixedStrain);

   UpdateAnalysisPoints(angle, solutionMethod, strainLocation);

   switch (solutionMethod)
   {
   case smFixedCurvature:
      ATLASSERT(false);
      break;
   case smFixedCompressionStrain:
      m_FixedPoint = m_ExtremeCompressionPoint;
      m_ControlPoint = m_ExtremeTensionPoint;
      break;

   case smFixedTensionStrain:
      m_FixedPoint = m_ExtremeTensionPoint;
      m_ControlPoint = m_ExtremeCompressionPoint;
      break;

   case smFixedStrain:
   {
      if (m_FixedPoint == nullptr) m_FixedPoint.CoCreateInstance(CLSID_Point2d);
      m_FixedPoint->Move(0, strainLocation);

      // fixed point is not guarenteed to be at pntCompression or pntTension
      // determine if pntCompression or pntTension should be the control point

      // Get Size for fixed point to pntCompression and pntTension...
      CComPtr<ISize2d> sizeC, sizeT;
      m_FixedPoint->SizeEx(m_ExtremeCompressionPoint, &sizeC);
      m_FixedPoint->SizeEx(m_ExtremeTensionPoint, &sizeT);

      // ... then use the sizes to create vectors from fixed point to the tension and compression points ...
      Float64 dx, dy;
      sizeC->Dimensions(&dx, &dy);
      CComPtr<IVector2d> vC;
      vC.CoCreateInstance(CLSID_Vector2d);
      vC->put_X(dx); vC->put_Y(dy);

      sizeT->Dimensions(&dx, &dy);
      CComPtr<IVector2d> vT;
      vT.CoCreateInstance(CLSID_Vector2d);
      vT->put_X(dx); vT->put_Y(dy);

      // ... then get the direction of the vectors (in both directions)
      Float64 dirC1, dirC2;
      vC->get_Direction(&dirC1);
      vC->Reflect();
      vC->get_Direction(&dirC2);

      Float64 dirT1, dirT2;
      vT->get_Direction(&dirT1);
      vT->Reflect();
      vT->get_Direction(&dirT2);

      // ... if the direction of the vector between fixed point and the compression point are the same as the direction of the neutral axis (or in opposite directions)
      // the use the tension point, otherwise use the compression point. if the point with the same direction as the neutral axis is used, the strain plane
      // will be constructed from 3 colinear points (bad)
      if (IsEqual(angle, dirC1) || IsEqual(angle, dirC2))
      {
         m_ControlPoint = m_ExtremeTensionPoint;
      }
      else
      {
         m_ControlPoint = m_ExtremeCompressionPoint;
      }
   }
   break;
   }
}

HRESULT CMomentCapacitySolver::GetNeutralAxisParameterRange(Float64 k_or_ec,Float64 strainLocation,SolutionMethod solutionMethod,Float64 angle,Float64 Fz,Float64* peo_lower,Float64* peo_upper,Float64* pFz_lower,Float64* pFz_upper)
{
   Float64 FzMax, FzMin, Mx, My;
   TensionLimit(&FzMax,&Mx,&My,peo_upper);
   CompressionLimit(&FzMin,&Mx,&My,peo_lower);

   if (!InRange(FzMin, Fz, FzMax))
   {
      return Error(IDS_E_NEUTRALAXISNOTBOUNDED, IID_IMomentCapacitySolver, RC_E_NEUTRALAXISNOTBOUNDED);
   }

   Float64 eo_lower = (solutionMethod == smFixedCompressionStrain ? k_or_ec : *peo_lower);
   Float64 eo_upper = (solutionMethod == smFixedTensionStrain ? k_or_ec : *peo_upper);

   Float64 Fz_lower = 0;
   Float64 Fz_upper = 0;

   HRESULT hr;

   bool bDone = false;
   while ( !bDone )
   {
      UpdateStrainPlane(angle,k_or_ec,strainLocation,solutionMethod,eo_lower);

      hr = m_GeneralSolver->Solve(m_IncrementalStrainPlane,&m_GeneralSolution.p);
      if ( FAILED(hr) )
         return hr;

      m_GeneralSolution->get_Fz(&Fz_lower);
      m_GeneralSolution->get_Mx(&Mx);
      m_GeneralSolution->get_My(&My);

      Fz_lower -= Fz;
   
      UpdateStrainPlane(angle,k_or_ec,strainLocation,solutionMethod,eo_upper);
      hr = m_GeneralSolver->Solve(m_IncrementalStrainPlane,&m_GeneralSolution.p);
      if ( FAILED(hr) )
         return hr;

      m_GeneralSolution->get_Fz(&Fz_upper);
      m_GeneralSolution->get_Mx(&Mx);
      m_GeneralSolution->get_My(&My);

      Fz_upper -= Fz;

      if ( Fz_lower*Fz_upper <= 0 )
      {
         bDone = true;
      }
      else
      {
         eo_lower -= (eo_upper - eo_lower)/2;
         eo_upper += (eo_upper - eo_lower)/2;
      }
   }

   *peo_lower = eo_lower;
   *peo_upper = eo_upper;
   *pFz_lower = Fz_lower;
   *pFz_upper = Fz_upper;

   return hr;
}

HRESULT CMomentCapacitySolver::AnalyzeSection(Float64 Fz,Float64 angle,Float64 k_or_ec,SolutionMethod solutionMethod, Float64 strainLocation,IMomentCapacitySolution** solution)
{
   if ( solution == nullptr )
      return E_INVALIDARG;

   HRESULT hr = S_OK;

   // solve with method of false position (aka regula falsi method)
   // http://en.wikipedia.org/wiki/False_position_method
   // http://mathworld.wolfram.com/MethodofFalsePosition.html

   Float64 Fz_lower, Fz_upper;
   Float64 eo_lower, eo_upper;
   hr = GetNeutralAxisParameterRange(k_or_ec,strainLocation,solutionMethod,angle,Fz,&eo_lower,&eo_upper,&Fz_lower,&Fz_upper);
   if ( FAILED(hr) )
      return hr;

   ATLASSERT(eo_lower < eo_upper);

   Float64 Mx,My;

   int side = 0;
   Float64 Fz_r = 0;
   Float64 eo_r = 0; // first guess is zero strain at the control point (we get better convergence this say)
   long iter = 0;
   for ( iter = 0; iter < m_MaxIter; iter++ )
   {
      if (IsZero(Fz_r, m_AxialTolerance) && IsZero(Fz_lower, m_AxialTolerance) && IsZero(Fz_upper, m_AxialTolerance))
      {
         break; // converged
      }

      hr = S_OK; // need to reset for each iteration - there may have been an overstrained material in a previous interation but the solution was incorrect. don't want to carry that bad state into this iteration

      // update guess for strain at the control point
      eo_r = (Fz_upper * eo_lower - Fz_lower * eo_upper) / (Fz_upper - Fz_lower);

      UpdateStrainPlane(angle,k_or_ec,strainLocation,solutionMethod,eo_r);
      hr = m_GeneralSolver->Solve(m_IncrementalStrainPlane,&m_GeneralSolution.p);
      if (FAILED(hr))
      {
         return hr;
      }

      m_GeneralSolution->get_Fz(&Fz_r);
      m_GeneralSolution->get_Mx(&Mx);
      m_GeneralSolution->get_My(&My);

      Fz_r -= Fz;

      if ( 0 < Fz_r*Fz_upper )
      {
         eo_upper = eo_r;
         Fz_upper = Fz_r;
         if (side == -1)
         {
            Fz_lower /= 2;
         }

         side = -1;
      }
      else if ( 0 < Fz_lower*Fz_r )
      {
         eo_lower = eo_r;
         Fz_lower = Fz_r;
         if (side == 1)
         {
            Fz_upper /= 2;
         }

         side = 1;
      }
      else
      {
         break;
      }
   }

   // This block of code is moved to the bottom of this function so that
   // the state of the last iteration is captured for the caller
   //if (m_MaxIter <= iter)
   //{
   //   return Error(IDS_E_SOLUTIONNOTFOUND, IID_IMomentCapacitySolver, RC_E_SOLUTIONNOTFOUND);
   //}

   if ( *solution == nullptr )
   {
      CComObject<CMomentCapacitySolution>* pSolution;
      CComObject<CMomentCapacitySolution>::CreateInstance(&pSolution);
      (*solution) = pSolution;
      (*solution)->AddRef();
   }

   Float64 Pz = Fz_r + Fz;

   Float64 C,T;
   m_GeneralSolution->get_CompressionResultant(&C);
   m_GeneralSolution->get_TensionResultant(&T);

   ATLASSERT( IsZero(C+T-Fz,m_AxialTolerance) );

   CComPtr<IPoint2d> cgC, cgT;
   m_GeneralSolution->get_CompressionResultantLocation(&cgC);
   m_GeneralSolution->get_TensionResultantLocation(&cgT);

   // Compute curvature
   CComPtr<IGeneralSection> section;
   m_GeneralSolver->get_Section(&section);
   IndexType primaryShapeIdx;
   section->get_PrimaryShapeIndex(&primaryShapeIdx);
   CComPtr<IUnkArray> arrSlices;
   m_GeneralSolution->FindSlices(primaryShapeIdx, &arrSlices);
   IndexType nSlices;
   arrSlices->get_Count(&nSlices);
   CComPtr<IUnknown> punk1, punk2;
   arrSlices->get_Item(0, &punk1);
   arrSlices->get_Item(nSlices - 1, &punk2);
   CComQIPtr<IGeneralSectionSlice> slice1(punk1);
   CComQIPtr<IGeneralSectionSlice> slice2(punk2);

   CComPtr<IPoint2d> cg1, cg2;
   slice1->get_CG(&cg1);
   slice2->get_CG(&cg2);
   Float64 dist;
   cg1->DistanceEx(cg2, &dist);

   Float64 e1, e2;
   slice1->get_TotalStrain(&e1);
   slice2->get_TotalStrain(&e2);

   Float64 k = (e2 - e1) / dist;

#if defined _DEBUG
   if (solutionMethod == smFixedCurvature)
   {
      ATLASSERT(IsEqual(k_or_ec, k));
   }
#endif

   (*solution)->InitSolution(Pz, Mx, My, m_IncrementalStrainPlane, m_ExtremeCompressionPoint, cgC, C, m_ExtremeTensionPoint, cgT, T, k, m_GeneralSolution);

   m_GeneralSolution.Release(); // this must be released because it will get changed by subsequent analyses and that will change (*solution)

   if (m_MaxIter <= iter)
   {
      return Error(IDS_E_SOLUTIONNOTFOUND, IID_IMomentCapacitySolver, RC_E_SOLUTIONNOTFOUND);
   }

   if (hr == S_FALSE)
   {
      return Error(IDS_E_MATERIALFAILURE, IID_IMomentCapacitySolver, RC_E_MATERIALFAILURE);
   }

   return S_OK;
}

HRESULT CMomentCapacitySolver::ZeroCapacitySolution(IMomentCapacitySolution** solution)
{
   CComObject<CMomentCapacitySolution>* pSolution;
   CComObject<CMomentCapacitySolution>::CreateInstance(&pSolution);
   (*solution) = pSolution;
   (*solution)->AddRef();

  return S_OK;
}
