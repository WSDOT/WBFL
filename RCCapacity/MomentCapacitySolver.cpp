///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
//                   Bridge and Structures Office
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
}


STDMETHODIMP CMomentCapacitySolver::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMomentCapacitySolver,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
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
   m_bUpdateTensionLimit     = true;
   m_bUpdateCompressionLimit = true;

   return m_GeneralSolver->putref_Section(pSection);
}

STDMETHODIMP CMomentCapacitySolver::get_Section(IGeneralSection** pSection)
{
   return m_GeneralSolver->get_Section(pSection);
}

STDMETHODIMP CMomentCapacitySolver::Solve(Float64 Fz,Float64 angle,Float64 k_or_ec,SolutionMethod solutionMethod,IMomentCapacitySolution** solution)
{
   m_bFurthestPointUpdated = false;
   m_XFurthest = -999999;
   m_YFurthest = -999999;

   Float64 FzT, MxT, MyT, eoT;
   TensionLimit(&FzT,&MxT,&MyT,&eoT);

   Float64 FzC, MxC, MyC, eoC;
   CompressionLimit(&FzC,&MxC,&MyC,&eoC);

   if ( ( IsZero(FzT) && IsZero(MxT) && IsZero(MyT) ) || ( IsZero(FzC) && IsZero(MxC) && IsZero(MyC) ) )
      return ZeroCapacitySolution(solution);

   if ( IsEqual(Fz,FzC) || IsEqual(Fz,FzT) )
   {
      HRESULT hr = ZeroCapacitySolution(solution);

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

   return AnalyzeSection(Fz,angle,k_or_ec,solutionMethod,solution);
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

STDMETHODIMP CMomentCapacitySolver::CompressionLimit(Float64* Fz,Float64* Mx,Float64* My,Float64* eo)
{
   if ( !m_bUpdateCompressionLimit )
   {
      *Fz = m_FzCompressionLimit;
      *Mx = m_MxCompressionLimit;
      *My = m_MyCompressionLimit;
      *eo = m_eoCompressionLimit;

      return S_OK;
   }

   CHECK_RETVAL(eo);

   CComPtr<IGeneralSection> section;
   get_Section(&section);

   Float64 minStrain = -10000;
   CollectionIndexType nShapes;
   section->get_ShapeCount(&nShapes);
   for ( CollectionIndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++ )
   {
      CComPtr<IStressStrain> material;
      section->get_ForegroundMaterial(shapeIdx,&material);

      if ( material == NULL )
         continue; // shape is a void

      Float64 strain_at_peak_stress;
      material->get_StrainAtPeakStress(&strain_at_peak_stress);

      if ( strain_at_peak_stress <= 0 )
         minStrain = _cpp_max(strain_at_peak_stress,minStrain);
   }

   m_StrainPlane->ThroughAltitude(minStrain);

   m_eoCompressionLimit = minStrain;
   *eo = m_eoCompressionLimit;

   long nSlices;
   get_Slices(&nSlices);
   put_Slices(1);
   HRESULT hr = m_GeneralSolver->Solve(m_StrainPlane,&m_CompressionSolution.p);
   put_Slices(nSlices);

   if ( SUCCEEDED(hr) )
   {
      m_CompressionSolution->get_Fz(&m_FzCompressionLimit);
      m_CompressionSolution->get_Mx(&m_MxCompressionLimit);
      m_CompressionSolution->get_My(&m_MyCompressionLimit);

      *Fz = m_FzCompressionLimit;
      *Mx = m_MxCompressionLimit;
      *My = m_MyCompressionLimit;

      m_bUpdateCompressionLimit = false;
   }

   return hr;
}

STDMETHODIMP CMomentCapacitySolver::TensionLimit(Float64* Fz,Float64* Mx,Float64* My,Float64* eo)
{
   if ( !m_bUpdateTensionLimit )
   {
      *Fz = m_FzTensionLimit;
      *Mx = m_MxTensionLimit;
      *My = m_MyTensionLimit;
      *eo = m_eoTensionLimit;

      return S_OK;
   }

   CHECK_RETVAL(eo);

   CComPtr<IGeneralSection> section;
   get_Section(&section);

   Float64 maxYieldStrain = -10000;
   CollectionIndexType nShapes;
   section->get_ShapeCount(&nShapes);
   for ( CollectionIndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++ )
   {
      CComPtr<IStressStrain> material;
      section->get_ForegroundMaterial(shapeIdx,&material);

      if ( material == NULL )
         continue; // shape is a void

      Float64 e_yield;
      material->get_YieldStrain(&e_yield);

      maxYieldStrain = _cpp_max(e_yield,maxYieldStrain);
   }

   m_StrainPlane->ThroughAltitude(maxYieldStrain);

   m_eoTensionLimit = maxYieldStrain;
   *eo = m_eoTensionLimit;

   long nSlices;
   get_Slices(&nSlices);
   put_Slices(1);

   HRESULT hr = m_GeneralSolver->Solve(m_StrainPlane,&m_TensionSolution.p);

   put_Slices(nSlices);

   if ( SUCCEEDED(hr) )
   {
      m_TensionSolution->get_Fz(&m_FzTensionLimit);
      m_TensionSolution->get_Mx(&m_MxTensionLimit);
      m_TensionSolution->get_My(&m_MyTensionLimit);

      *Fz = m_FzTensionLimit;
      *Mx = m_MxTensionLimit;
      *My = m_MyTensionLimit;

      m_bUpdateTensionLimit = false;
   }

   return hr;
}

void CMomentCapacitySolver::UpdateStrainPlane(Float64 angle,Float64 k_or_ec,Float64 eo,SolutionMethod solutionMethod)
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
         Float64 d = 1000; // distance between P1 and P2. P1 and P2 are points on the neutral axis

         m_P1->Move(-eo*sin(angle)/k - d*cos(angle),
                     eo*cos(angle)/k - d*sin(angle),
                    0.0
                    );

         m_P2->Move(-eo*sin(angle)/k + d*cos(angle),
                     eo*cos(angle)/k + d*sin(angle),
                    0.0
                    );

         m_P3->Move( 0, 0, eo );

         m_StrainPlane->ThroughPoints(m_P1,m_P2,m_P3);
      }
   }
   else
   {
      // curvature varies. The strain at the extreme point on the compression side changes
      Float64 ec = k_or_ec;

      UpdateFurthestPoint(angle);

      if ( IsEqual(ec,eo) )
      {
         m_StrainPlane->ThroughAltitude(eo);
      }
      else
      {
         Float64 d = 1000; // distance between P1 and P2. P1 and P2 are points on the X axis
         m_P1->Move(-d*cos(angle),-d*sin(angle),eo);
         m_P2->Move( d*cos(angle), d*sin(angle),eo);

         m_P3->Move(m_XFurthest,m_YFurthest,ec);
         m_StrainPlane->ThroughPoints(m_P1,m_P2,m_P3);
      }
   }
}

void CMomentCapacitySolver::UpdateFurthestPoint(Float64 angle)
{
   if ( m_bFurthestPointUpdated )
      return;

   CComPtr<IGeneralSection> section;
   m_GeneralSolver->get_Section(&section);


   // create a line parallel to the neutral axis passing through (0,0)
   // this line must be in the opposite direction as the neutral axis because we will be using
   // the IShape::FurthestDistance method. This method returns the distance to the furthest point
   // of a shape on the right side of the line.
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   CComPtr<IVector2d> line_direction;
   line_direction.CoCreateInstance(CLSID_Vector2d);
   line_direction->put_Direction(angle+M_PI);

   CComPtr<IPoint2d> origin;
   origin.CoCreateInstance(CLSID_Point2d);
   origin->Move(0,0);

   line->SetExplicit(origin,line_direction);

   // find the furthest distance from the right side of this line to the section
   // this is the distance from the origin to the extreme compression fiber

   // the IShape::FurthestDistance will return a value less than zero if the entire shape
   // is on the tension side

   Float64 furthest_distance = -99999999;

   CollectionIndexType shape_count;
   section->get_ShapeCount(&shape_count);
   for ( CollectionIndexType shapeIdx = 0; shapeIdx < shape_count; shapeIdx++ )
   {
      CComPtr<IShape> shape;
      section->get_Shape(shapeIdx,&shape);

      Float64 dist;
      shape->FurthestDistance(line,&dist);

      furthest_distance = _cpp_max(furthest_distance,dist);
   }

   // these coordinates are in the system that is parallel to the neutral axis
   Float64 x = 0;
   Float64 y = furthest_distance;

   // rotate this coordinates into the global system
   // (the x term is commented out because x is zero)
   m_XFurthest = /* x*cos(angle) */ - y*sin(angle);
   m_YFurthest = /* x*sin(angle) */ + y*cos(angle);

   m_bFurthestPointUpdated = true;
}

HRESULT CMomentCapacitySolver::GetNeutralAxisParameterRange(Float64 k_or_ec,SolutionMethod solutionMethod,Float64 angle,Float64 Fz,Float64* peo_lower,Float64* peo_upper,Float64* pFz_lower,Float64* pFz_upper)
{
   Float64 FzMax, FzMin, Mx, My;
   TensionLimit(&FzMax,&Mx,&My,peo_upper);
   CompressionLimit(&FzMin,&Mx,&My,peo_lower);

   if ( !InRange(FzMin,Fz,FzMax) )
      return E_FAIL;

   Float64 eo_lower = (solutionMethod == smFixedCompressiveStrain ? k_or_ec : -0.0035);
   Float64 eo_upper =  0.11;

   Float64 Fz_lower = 0;
   Float64 Fz_upper = 0;

   HRESULT hr;

   bool bDone = false;
   while ( !bDone )
   {
      UpdateStrainPlane(angle,k_or_ec,eo_lower,solutionMethod);

      hr = m_GeneralSolver->Solve(m_StrainPlane,&m_GeneralSolution.p);
      if ( FAILED(hr) )
         return hr;

      m_GeneralSolution->get_Fz(&Fz_lower);
      m_GeneralSolution->get_Mx(&Mx);
      m_GeneralSolution->get_My(&My);

      Fz_lower -= Fz;
   
      UpdateStrainPlane(angle,k_or_ec,eo_upper,solutionMethod);
      hr = m_GeneralSolver->Solve(m_StrainPlane,&m_GeneralSolution.p);
      if ( FAILED(hr) )
         return hr;

      m_GeneralSolution->get_Fz(&Fz_upper);
      m_GeneralSolution->get_Mx(&Mx);
      m_GeneralSolution->get_My(&My);

      Fz_upper -= Fz;

      if ( Fz_lower*Fz_upper < 0 )
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

HRESULT CMomentCapacitySolver::AnalyzeSection(Float64 Fz,Float64 angle,Float64 k_or_ec,SolutionMethod solutionMethod,IMomentCapacitySolution** solution)
{
   if ( solution == NULL )
      return E_INVALIDARG;

   HRESULT hr;

   // solve with method of false position
   Float64 Fz_lower, Fz_upper;
   Float64 eo_lower, eo_upper;
   hr = GetNeutralAxisParameterRange(k_or_ec,solutionMethod,angle,Fz,&eo_lower,&eo_upper,&Fz_lower,&Fz_upper);
   if ( FAILED(hr) )
      return hr;

   Float64 Mx,My;

   int side = 0;
   Float64 Fz_r = 0;
   Float64 eo_r;
   long iter = 0;
   for ( iter = 0; iter < m_MaxIter; iter++ )
   {
      if ( IsZero(Fz_r,m_AxialTolerance) && IsZero(Fz_lower,m_AxialTolerance) && IsZero(Fz_upper,m_AxialTolerance) )
         break; // converged

      eo_r = (Fz_upper*eo_lower - Fz_lower*eo_upper) / ( Fz_upper - Fz_lower );
      UpdateStrainPlane(angle,k_or_ec,eo_r,solutionMethod);
      hr = m_GeneralSolver->Solve(m_StrainPlane,&m_GeneralSolution.p);
      if ( FAILED(hr) )
         return hr;

      m_GeneralSolution->get_Fz(&Fz_r);
      m_GeneralSolution->get_Mx(&Mx);
      m_GeneralSolution->get_My(&My);

      Fz_r -= Fz;

      if ( Fz_r*Fz_upper > 0 )
      {
         eo_upper = eo_r;
         Fz_upper = Fz_r;
         if ( side == -1 )
            Fz_lower /= 2;

         side = -1;
      }
      else if ( Fz_lower*Fz_r > 0 )
      {
         eo_lower = eo_r;
         Fz_lower = Fz_r;
         if ( side == 1 )
            Fz_upper /= 2;

         side = 1;
      }
      else
      {
         break;
      }
   }

   if ( m_MaxIter <= iter )
      return Error(IDS_E_SOLUTIONNOTFOUND,IID_IMomentCapacitySolver,RC_E_SOLUTIONNOTFOUND);

   if ( *solution == NULL )
   {
      CComObject<CMomentCapacitySolution>* pSolution;
      CComObject<CMomentCapacitySolution>::CreateInstance(&pSolution);
      (*solution) = pSolution;
      (*solution)->AddRef();
   }

   Float64 Pz = Fz_r + Fz;
//   Pz = IsZero(Pz) ? 0 : Pz;
//   Mx = IsZero(Mx) ? 0 : Mx;
//   My = IsZero(My) ? 0 : My;

   Float64 C,T;
   m_GeneralSolution->get_CompressionResultant(&C);
   m_GeneralSolution->get_TensionResultant(&T);

   ATLASSERT( IsZero(C+T-Fz,m_AxialTolerance) );

   CComPtr<IPoint2d> cgC, cgT;
   m_GeneralSolution->get_CompressionResultantLocation(&cgC);
   m_GeneralSolution->get_TensionResultantLocation(&cgT);

   CComPtr<IPlane3d> strainPlane;
   m_StrainPlane->Clone(&strainPlane);

   CComPtr<ILine2d> neutralAxis;
   m_GeneralSolution->get_NeutralAxis(&neutralAxis);
   (*solution)->InitSolution(Pz,Mx,My,strainPlane,neutralAxis,cgC,C,cgT,T,m_GeneralSolution);
   m_GeneralSolution = 0;

   if ( hr == S_FALSE )
      return Error(IDS_E_MATERIALFAILURE,IID_IMomentCapacitySolver,RC_E_MATERIALFAILURE);

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