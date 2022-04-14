///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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
   m_StrainPlane.CoCreateInstance(CLSID_Plane3d);

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
   m_StrainPlane.Release();
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
   m_bFurthestPointUpdated = false;
   m_XFurthest = -Float64_Max;
   m_YFurthest = -Float64_Max;

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

      CComPtr<IPlane3d> strainPlane;
      (*solution)->get_StrainPlane(&strainPlane);

      CComPtr<ILine2d> na;
      if (IsEqual(Fz,FzC))
      {
         m_CompressionSolution->get_NeutralAxis(&na);
         (*solution)->InitSolution(FzC,MxC,MyC,strainPlane,na,cgC,C,cgT,T,m_CompressionSolution);
      }
      else
      {
         m_TensionSolution->get_NeutralAxis(&na);
         (*solution)->InitSolution(FzT,MxT,MyT,strainPlane,na,cgC,C,cgT,T,m_TensionSolution);
      }

      return hr;
   }

   // If the strain is fixed at one of the extreme faces of the section
   // change the solution method to an extreme face method
   if (solutionMethod == smFixedStrain)
   {
      if (IsGE(0.0, angle) && IsLT(angle, M_PI) && IsEqual(strainLocation, m_Top))
         solutionMethod = smFixedCompressionStrain;
      else if (IsGE(0.0, angle) && IsLT(angle, M_PI) && IsEqual(strainLocation, m_Bottom))
         solutionMethod = smFixedTensionStrain;
      else if (IsGE(M_PI, angle) && IsLT(angle, TWO_PI) && IsEqual(strainLocation, m_Top))
         solutionMethod = smFixedTensionStrain;
      else if (IsGE(M_PI, angle) && IsLT(angle, TWO_PI) && IsEqual(strainLocation, m_Bottom))
         solutionMethod = smFixedCompressionStrain;
   }

   // no special case solutions, so let's do the strain compatibility analysis
   if (solutionMethod == smFixedCurvature)
      return AnalyzeSection(Fz, angle, k_or_ec, solutionMethod, strainLocation, solution);
   else
      return AnalyzeSection2(Fz, angle, k_or_ec, solutionMethod, strainLocation, solution);
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

   m_Top = -Float64_Max;
   m_Bottom = Float64_Max;
   
   CollectionIndexType nShapes;
   section->get_ShapeCount(&nShapes);
   for (CollectionIndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++)
   {
      CComPtr<IShape> shape;
      section->get_Shape(shapeIdx, &shape);
      CComPtr<IRect2d> bbox;
      shape->get_BoundingBox(&bbox);
      Float64 t, b;
      bbox->get_Top(&t);
      bbox->get_Bottom(&b);
      m_Top = Max(m_Top, t);
      m_Bottom = Min(m_Bottom, b);

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
   m_StrainPlane->ThroughAltitude(compStrain);

   long nSlices;
   get_Slices(&nSlices);

   put_Slices(1);
   HRESULT hr = m_GeneralSolver->Solve(m_StrainPlane, &m_CompressionSolution.p);
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
   m_StrainPlane->ThroughAltitude(tensStrain);

   put_Slices(1);
   hr = m_GeneralSolver->Solve(m_StrainPlane, &m_TensionSolution.p);
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
   if ( solutionMethod == smFixedCurvature )
   {
      // curvature is fixed... move the strain plain up/down changing the strain at the extreme point
      Float64 k = k_or_ec;
      if ( IsZero(k,1e-20) )
      {
         m_StrainPlane->ThroughAltitude(eo);
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

         m_StrainPlane->ThroughPoints(m_P1,m_P2,m_P3);
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
         m_StrainPlane->ThroughAltitude(eo);
      }
      else
      {
         if (solutionMethod == smFixedStrain)
         {
            m_XFurthest = 0;
            m_YFurthest = strainLocation;
         }
         else
         {
            UpdateFurthestPoint(angle, solutionMethod);
         }


         Float64 Y;
         if (solutionMethod == smFixedCompressionStrain)
         {
            // strain is fixed at the extreme compression fiber - set the trial strain at the opposite side of the section
            Y = (IsGE(0.0, angle) && IsLT(angle, M_PI) ? m_Bottom : m_Top);
         }
         else if (solutionMethod == smFixedTensionStrain)
         {
            // strain is fixed at the extreme tension fiber - set the trial strain at the opposite side of the section
            Y = (IsGE(0.0, angle) && IsLT(angle, M_PI) ? m_Top : m_Bottom);
         }
         else if (solutionMethod == smFixedStrain)
         {
            // stain is fixed at an arbitrary height in the section... set the strain based on its value (tension/compresion) and the direction of the neutral axis
            Float64 middle = (m_Top + m_Bottom) / 2;
            Y = m_YFurthest < middle ? m_Top : m_Bottom;
            //if (IsGE(0.0, angle) && IsLT(angle, M_PI))
            //   Y = (eo <= 0 ? m_Bottom : m_Top);
            //else
            //   Y = (eo <= 0 ? m_Top : m_Bottom);

            //if (IsEqual(Y, m_YFurthest))
            //{
            //   // the controlling strain point is one of the top/bottom points
            //   if(ec <= 0)
            //      Y = (IsGE(0.0, angle) && IsLT(angle, M_PI) ? m_Bottom : m_Top); // same as smFixedCompressionStrain
            //   else
            //      Y = (IsGE(0.0, angle) && IsLT(angle, M_PI) ? m_Top : m_Bottom); // same as smFixedTensionStrain
            //}
         }
         ATLASSERT(!IsEqual(Y, m_YFurthest));

         Float64 d = 1000; // distance between P1 and P2.
         Float64 sin_angle = sin(angle);
         Float64 cos_angle = cos(angle);
         m_P1->Move(-d*cos_angle - Y*sin_angle, -d*sin_angle + Y/**cos_angle*/, eo);
         m_P2->Move( d*cos_angle - Y*sin_angle,  d*sin_angle + Y/**cos_angle*/, eo);

         m_P3->Move(m_XFurthest, m_YFurthest, ec);

         // The strain plain is defined by three points. One point is where the strain is fixed
         // The other two define a line of constant strain through the trial strain value
         m_StrainPlane->ThroughPoints(m_P1, m_P2, m_P3);
      }
   }
}

void CMomentCapacitySolver::UpdateFurthestPoint(Float64 angle, SolutionMethod solutionMethod)
{
   ATLASSERT(solutionMethod == smFixedCompressionStrain || solutionMethod == smFixedTensionStrain);

   if ( m_bFurthestPointUpdated )
      return;

   CComPtr<IGeneralSection> section;
   m_GeneralSolver->get_Section(&section);


   // create a line parallel to the neutral axis passing through (0,0)
   // The IShape::FurthestDistance method returns the furthest point of the shape on the right side of a line.
   // Compression is on the left side of the neutral axis. If the solutionMethod is smFixedCompressionStrain
   // then the line must be in the opposite direction of the neutral axis.
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   CComPtr<IVector2d> line_direction;
   line_direction.CoCreateInstance(CLSID_Vector2d);
   if(solutionMethod == smFixedCompressionStrain)
      line_direction->put_Direction(angle+M_PI); // for compression, add 180deg so the line is in the opposite direction of the neutral axis
   else
      line_direction->put_Direction(angle);

   CComPtr<IPoint2d> origin;
   origin.CoCreateInstance(CLSID_Point2d);
   origin->Move(0,0);

   line->SetExplicit(origin,line_direction);

   // Find the furthest distance from the right side of this line to the section.
   // This is the distance from the origin to the extreme tension or compression fiber, depending on the direction of the line.

   // IShape::FurthestDistance will return a value less than zero if the entire shape
   // is on the opposite side of the line than we are interested in.

   Float64 furthest_distance = -Float64_Max;

   CollectionIndexType shape_count;
   section->get_ShapeCount(&shape_count);
   for ( CollectionIndexType shapeIdx = 0; shapeIdx < shape_count; shapeIdx++ )
   {
      CComPtr<IShape> shape;
      section->get_Shape(shapeIdx,&shape);

      Float64 dist;
      shape->FurthestDistance(line,&dist);

      furthest_distance = Max(furthest_distance,dist);
   }

   // these coordinates are in the system that is parallel to the neutral axis
   Float64 x = 0;
   Float64 y = furthest_distance;

   // rotate this coordinates into the global system
   // (the x term is commented out because x is zero)
   Float64 _angle = (solutionMethod == smFixedCompressionStrain ? angle : angle + M_PI);
   m_XFurthest = /* x*cos(_angle) */ - y*sin(_angle);
   m_YFurthest = /* x*sin(_angle) */ + y*cos(_angle);

   m_bFurthestPointUpdated = true;
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

      hr = m_GeneralSolver->Solve(m_StrainPlane,&m_GeneralSolution.p);
      if ( FAILED(hr) )
         return hr;

      m_GeneralSolution->get_Fz(&Fz_lower);
      m_GeneralSolution->get_Mx(&Mx);
      m_GeneralSolution->get_My(&My);

      Fz_lower -= Fz;
   
      UpdateStrainPlane(angle,k_or_ec,strainLocation,solutionMethod,eo_upper);
      hr = m_GeneralSolver->Solve(m_StrainPlane,&m_GeneralSolution.p);
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
      hr = m_GeneralSolver->Solve(m_StrainPlane,&m_GeneralSolution.p);
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

   //CComPtr<IPlane3d> strainPlane;
   //m_StrainPlane->Clone(&strainPlane);

   // build the total strain plane by "Adding" the initial strians with the incremental solution strain
   //
   
   // Get the incremental strain plane
   CComPtr<IPlane3d> incremental_strain_plane;
   m_StrainPlane->Clone(&incremental_strain_plane);

   // get the initial strain plane for the primary shape
   CComPtr<IGeneralSection> section;
   m_GeneralSolver->get_Section(&section);
   IndexType primaryShapeIdx;
   section->get_PrimaryShape(&primaryShapeIdx);
   CComPtr<IPlane3d> initial_strain_plane;
   section->get_InitialStrain(primaryShapeIdx, &initial_strain_plane);

   // get three points on the initial strain plane
   CComPtr<IPoint3d> A1, A2, A3;
   A1.CoCreateInstance(CLSID_Point3d);
   A2.CoCreateInstance(CLSID_Point3d);
   A3.CoCreateInstance(CLSID_Point3d);
   Float64 Z;
   initial_strain_plane->GetZ(-100, 100, &Z);
   A1->Move(-100, 100, Z);
   initial_strain_plane->GetZ(100, 100, &Z);
   A2->Move(100, 100, Z);
   initial_strain_plane->GetZ(-100, -100, &Z);
   A3->Move(-100, -100, Z);

   // get the incremental strain on these three points
   // and offset the initial strain by the increment strain
   incremental_strain_plane->GetZ(-100, 100, &Z);
   A1->Offset(0, 0, Z);
   incremental_strain_plane->GetZ(100, 100, &Z);
   A2->Offset(0, 0, Z);
   incremental_strain_plane->GetZ(-100, -100, &Z);
   A3->Offset(0, 0, Z);

   // create a new plane... the total strain plane through these three points
   CComPtr<IPlane3d> total_strain_plane;
   total_strain_plane.CoCreateInstance(CLSID_Plane3d);
   total_strain_plane->ThroughPoints(A1, A2, A3);

   CComPtr<ILine2d> neutralAxis;
   m_GeneralSolution->get_NeutralAxis(&neutralAxis);
   //(*solution)->InitSolution(Pz,Mx,My,strainPlane,neutralAxis,cgC,C,cgT,T,m_GeneralSolution);
   (*solution)->InitSolution(Pz, Mx, My, total_strain_plane, neutralAxis, cgC, C, cgT, T, m_GeneralSolution);
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

void CMomentCapacitySolver::UpdateStrainPlane2(Float64 naAngle, Float64 x, Float64 y, Float64 ec, Float64 k)
{
   if (IsZero(k,1.0e-20))
   {
      m_StrainPlane->ThroughAltitude(ec);
   }
   else
   {
      Float64 yna = ec / k; // distance from where strain is known to the neutral axis
      Float64 sin_angle = sin(naAngle);
      Float64 cos_angle = cos(naAngle);
      
      Float64 d = 1000; // distance between P1 and P2 on the neutral axis

      m_P1->Move(x - yna * sin_angle - d * cos_angle, y + yna * cos_angle - d * sin_angle,0.0);
      m_P2->Move(x - yna * sin_angle + d * cos_angle, y + yna * cos_angle + d * sin_angle,0.0);
      m_P3->Move(x, y, ec);

      // The strain plain is defined by three points. One point is where the strain is fixed
      // The other two define a line of constant strain through the trial strain value
      HRESULT hr = m_StrainPlane->ThroughPoints(m_P1, m_P2, m_P3);
      ATLASSERT(SUCCEEDED(hr)); // if this fails, the P1,P2,P3 don't form a plane
   }
}

HRESULT CMomentCapacitySolver::AnalyzeSection2(Float64 Fz, Float64 naAngle, Float64 k_or_ec, SolutionMethod solutionMethod, Float64 strainLocation, IMomentCapacitySolution** solution)
{
   if (solution == nullptr)
      return E_INVALIDARG;

   HRESULT hr = S_OK;

   // solve with method of false position (aka regula falsi method)
   // http://en.wikipedia.org/wiki/False_position_method
   // http://mathworld.wolfram.com/MethodofFalsePosition.html

   Float64 k_lower = 1.0e-20;
   Float64 k_upper = 1.0;

   Float64 ec = k_or_ec;
   Float64 x = 0.0;
   Float64 y;
   if (solutionMethod == smFixedCompressionStrain)
      y = (0.0 <= naAngle && naAngle < M_PI ? m_Top : m_Bottom);
   else if (solutionMethod == smFixedTensionStrain)
      y = (0.0 <= naAngle && naAngle < M_PI ? m_Bottom : m_Top);
   else
      y = strainLocation;

   Float64 Fz_lower = 0;
   Float64 Fz_upper = 0;

   // iterate until Fz_lower and Fz_upper have opposite signs - this is when the solution is bounded
   bool bDone = false;
   while (!bDone)
   {
      UpdateStrainPlane2(naAngle, x, y, ec, k_lower);
      hr = m_GeneralSolver->Solve(m_StrainPlane, &m_GeneralSolution.p);
      m_GeneralSolution->get_Fz(&Fz_lower);
      Fz_lower -= Fz;

      UpdateStrainPlane2(naAngle, x, y, ec, k_upper);
      hr = m_GeneralSolver->Solve(m_StrainPlane, &m_GeneralSolution.p);
      m_GeneralSolution->get_Fz(&Fz_upper);
      Fz_upper -= Fz;

      if (Fz_lower * Fz_upper <= 0)
      {
         bDone = true;
      }
      else
      {
         k_lower -= (k_upper - k_lower) / 2;
         k_upper += (k_upper - k_lower) / 2;
      }
   }

   Float64 Mx, My;

   int side = 0;
   Float64 Fz_r = 0;
   Float64 k_guess = 0;
   long iter = 0;
   for (iter = 0; iter < m_MaxIter; iter++)
   {
      if (IsZero(Fz_r, m_AxialTolerance) && IsZero(Fz_lower, m_AxialTolerance) && IsZero(Fz_upper, m_AxialTolerance))
      {
         break; // converged
      }

      hr = S_OK; // need to reset for each iteration - there may have been an overstrained material in a previous interation but the solution was incorrect. don't want to carry that bad state into this iteration

      // update guess for strain at the control point
      k_guess = (Fz_upper * k_lower - Fz_lower * k_upper) / (Fz_upper - Fz_lower);

      UpdateStrainPlane2(naAngle, x, y, ec, k_guess);
      hr = m_GeneralSolver->Solve(m_StrainPlane, &m_GeneralSolution.p);
      if (FAILED(hr))
      {
         return hr;
      }

      m_GeneralSolution->get_Fz(&Fz_r);
      m_GeneralSolution->get_Mx(&Mx);
      m_GeneralSolution->get_My(&My);

      Fz_r -= Fz;

      if (0 < Fz_r * Fz_upper)
      {
         k_upper = k_guess;
         Fz_upper = Fz_r;
         if (side == -1)
         {
            Fz_lower /= 2;
         }

         side = -1;
      }
      else if (0 < Fz_lower * Fz_r)
      {
         k_lower = k_guess;
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

   if (*solution == nullptr)
   {
      CComObject<CMomentCapacitySolution>* pSolution;
      CComObject<CMomentCapacitySolution>::CreateInstance(&pSolution);
      (*solution) = pSolution;
      (*solution)->AddRef();
   }

   Float64 Pz = Fz_r + Fz;

   Float64 C, T;
   m_GeneralSolution->get_CompressionResultant(&C);
   m_GeneralSolution->get_TensionResultant(&T);

   ATLASSERT(IsZero(C + T - Fz, m_AxialTolerance));

   CComPtr<IPoint2d> cgC, cgT;
   m_GeneralSolution->get_CompressionResultantLocation(&cgC);
   m_GeneralSolution->get_TensionResultantLocation(&cgT);

   //CComPtr<IPlane3d> strainPlane;
   //m_StrainPlane->Clone(&strainPlane);

   // build the total strain plane by "Adding" the initial strians with the incremental solution strain
   //

   // Get the incremental strain plane
   CComPtr<IPlane3d> incremental_strain_plane;
   m_StrainPlane->Clone(&incremental_strain_plane);

   // get the initial strain plane for the primary shape
   CComPtr<IGeneralSection> section;
   m_GeneralSolver->get_Section(&section);
   IndexType primaryShapeIdx;
   section->get_PrimaryShape(&primaryShapeIdx);
   CComPtr<IPlane3d> initial_strain_plane;
   section->get_InitialStrain(primaryShapeIdx, &initial_strain_plane);

   // get three points on the initial strain plane
   CComPtr<IPoint3d> A1, A2, A3;
   A1.CoCreateInstance(CLSID_Point3d);
   A2.CoCreateInstance(CLSID_Point3d);
   A3.CoCreateInstance(CLSID_Point3d);
   Float64 Z;
   initial_strain_plane->GetZ(-100, 100, &Z);
   A1->Move(-100, 100, Z);
   initial_strain_plane->GetZ(100, 100, &Z);
   A2->Move(100, 100, Z);
   initial_strain_plane->GetZ(-100, -100, &Z);
   A3->Move(-100, -100, Z);

   // get the incremental strain on these three points
   // and offset the initial strain by the increment strain
   incremental_strain_plane->GetZ(-100, 100, &Z);
   A1->Offset(0, 0, Z);
   incremental_strain_plane->GetZ(100, 100, &Z);
   A2->Offset(0, 0, Z);
   incremental_strain_plane->GetZ(-100, -100, &Z);
   A3->Offset(0, 0, Z);

   // create a new plane... the total strain plane through these three points
   CComPtr<IPlane3d> total_strain_plane;
   total_strain_plane.CoCreateInstance(CLSID_Plane3d);
   total_strain_plane->ThroughPoints(A1, A2, A3);

   CComPtr<ILine2d> neutralAxis;
   m_GeneralSolution->get_NeutralAxis(&neutralAxis);
   //(*solution)->InitSolution(Pz,Mx,My,strainPlane,neutralAxis,cgC,C,cgT,T,m_GeneralSolution);
   (*solution)->InitSolution(Pz, Mx, My, total_strain_plane, neutralAxis, cgC, C, cgT, T, m_GeneralSolution);
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
