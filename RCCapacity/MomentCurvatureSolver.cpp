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

// MomentCurvatureSolver.cpp : Implementation of CMomentCurvatureSolver
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "MomentCurvatureSolver.h"
#include "MomentCurvatureSolution.h"
#include "MomentCapacitySolver.h"
#include "MomentCapacitySolution.h"
#include <WBFLGeometry.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_FAIL 4

/////////////////////////////////////////////////////////////////////////////
// CMomentCurvatureSolver
HRESULT CMomentCurvatureSolver::FinalConstruct()
{
   HRESULT hr;

   CComObject<CMomentCapacitySolver>* pSolver;
   hr = CComObject<CMomentCapacitySolver>::CreateInstance(&pSolver);
   if ( FAILED(hr) )
      return hr;

   m_CapacitySolver = pSolver;

   CComObject<CMomentCapacitySolution>* pSolution;
   hr = CComObject<CMomentCapacitySolution>::CreateInstance(&pSolution);
   if ( FAILED(hr) )
      return hr;

   m_CapacitySolution = pSolution;

   m_kInitialStep = 1e-5;

   return S_OK;
}

void CMomentCurvatureSolver::FinalRelease()
{
}


STDMETHODIMP CMomentCurvatureSolver::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMomentCurvatureSolver,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IMomentCurvatureSolver
STDMETHODIMP CMomentCurvatureSolver::putref_Section(IGeneralSection* pSection)
{
   return m_CapacitySolver->putref_Section(pSection);
}

STDMETHODIMP CMomentCurvatureSolver::get_Section(IGeneralSection** pSection)
{
   return m_CapacitySolver->get_Section(pSection);
}

STDMETHODIMP CMomentCurvatureSolver::put_Slices(long nSlices)
{
   return m_CapacitySolver->put_Slices(nSlices);
}

STDMETHODIMP CMomentCurvatureSolver::get_Slices(long* nSlices)
{
   return m_CapacitySolver->get_Slices(nSlices);
}

STDMETHODIMP CMomentCurvatureSolver::put_AxialTolerance(Float64 tolerance)
{
   return m_CapacitySolver->put_AxialTolerance(tolerance);
}

STDMETHODIMP CMomentCurvatureSolver::get_AxialTolerance(Float64* tolerance)
{
   return m_CapacitySolver->get_AxialTolerance(tolerance);
}

STDMETHODIMP CMomentCurvatureSolver::put_MaxIterations(long maxIter)
{
   return m_CapacitySolver->put_MaxIterations(maxIter);
}

STDMETHODIMP CMomentCurvatureSolver::get_MaxIterations(long* maxIter)
{
   return m_CapacitySolver->get_MaxIterations(maxIter);
}

STDMETHODIMP CMomentCurvatureSolver::put_InitialCurvatureStep(Float64 k)
{
   m_kInitialStep = k;
   return S_OK;
}

STDMETHODIMP CMomentCurvatureSolver::get_InitialCurvatureStep(Float64* k)
{
   CHECK_RETVAL(k);
   *k = m_kInitialStep;
   return S_OK;
}

STDMETHODIMP CMomentCurvatureSolver::Solve(Float64 Fz,Float64 angle,IMomentCurvatureSolution** solution)
{
   CHECK_RETOBJ(solution);

   CComObject<CMomentCurvatureSolution>* pSolution;
   CComObject<CMomentCurvatureSolution>::CreateInstance(&pSolution);

   HRESULT hr = S_OK;
   Uint32 nFail = 0;
   Float64 k = 0;
   while ( SUCCEEDED(hr) )
   {
      hr = AnalyzeSection(Fz,angle,k,pSolution);

      if ( FAILED(hr) && nFail < MAX_FAIL )
      {
         hr = S_OK;
         k -= GetCurvatureIncrement(nFail);
         nFail++;
      }

      k += GetCurvatureIncrement(nFail);
   }

   (*solution) = pSolution;
   (*solution)->AddRef();

   return S_OK;
}

Float64 CMomentCurvatureSolver::GetCurvatureIncrement(Uint32 nFail)
{
   return m_kInitialStep/pow(2.,Float64(nFail));
}

HRESULT CMomentCurvatureSolver::AnalyzeSection(Float64 Fz,Float64 angle,Float64 k,CMomentCurvatureSolution* solution)
{
   HRESULT hr;

   hr = m_CapacitySolver->Solve(Fz,angle,k,smFixedCurvature,&m_CapacitySolution.p);
   if ( FAILED(hr) )
      return hr;

#if defined _DEBUG
   Float64 Pz;
   m_CapacitySolution->get_Fz(&Pz);

   Float64 tolerance;
   get_AxialTolerance(&tolerance);

   ATLASSERT(IsEqual(Fz,Pz,tolerance));
#endif
   Float64 Mx,My;
   CComPtr<IPlane3d> strainPlane;

   m_CapacitySolution->get_Mx(&Mx);
   m_CapacitySolution->get_My(&My);

   Float64 M = sqrt(Mx*Mx + My*My);

   m_CapacitySolution->get_StrainPlane(&strainPlane);
   solution->AddCurvaturePoint(M,k,strainPlane);

   return S_OK;
}
