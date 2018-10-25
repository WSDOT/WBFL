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

// AxialInteractionCurveSolver.cpp : Implementation of CAxialInteractionCurveSolver
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "AxialInteractionCurveSolver.h"
#include "InteractionCapacityCurveSolution.h"
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAxialInteractionCurveSolver

STDMETHODIMP CAxialInteractionCurveSolver::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAxialInteractionCurveSolver,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CAxialInteractionCurveSolver::FinalConstruct()
{
   m_Solver.CoCreateInstance(CLSID_MomentCapacitySolver);
   return S_OK;
}

void CAxialInteractionCurveSolver::FinalRelease()
{
}

STDMETHODIMP CAxialInteractionCurveSolver::putref_Section(IGeneralSection* pSection)
{
   return m_Solver->putref_Section(pSection);
}

STDMETHODIMP CAxialInteractionCurveSolver::get_Section(IGeneralSection** pSection)
{
   return m_Solver->get_Section(pSection);
}

STDMETHODIMP CAxialInteractionCurveSolver::put_Slices(long nSlices)
{
   return m_Solver->put_Slices(nSlices);
}

STDMETHODIMP CAxialInteractionCurveSolver::get_Slices(long* nSlices)
{
   return m_Solver->get_Slices(nSlices);
}

STDMETHODIMP CAxialInteractionCurveSolver::put_AxialTolerance(Float64 tolerance)
{
   return m_Solver->put_AxialTolerance(tolerance);
}

STDMETHODIMP CAxialInteractionCurveSolver::get_AxialTolerance(Float64* tolerance)
{
   return m_Solver->get_AxialTolerance(tolerance);
}

STDMETHODIMP CAxialInteractionCurveSolver::put_MaxIterations(long maxIter)
{
   return m_Solver->put_MaxIterations(maxIter);
}

STDMETHODIMP CAxialInteractionCurveSolver::get_MaxIterations(long* maxIter)
{
   return m_Solver->get_MaxIterations(maxIter);
}

STDMETHODIMP CAxialInteractionCurveSolver::CompressionLimit(Float64* Fz,Float64* Mx,Float64* My,Float64* eo)
{
   return m_Solver->CompressionLimit(Fz,Mx,My,eo);
}

STDMETHODIMP CAxialInteractionCurveSolver::TensionLimit(Float64* Fz,Float64* Mx,Float64* My,Float64* eo)
{
   return m_Solver->TensionLimit(Fz,Mx,My,eo);
}

STDMETHODIMP CAxialInteractionCurveSolver::Solve(Float64 na,long nFzSteps,IInteractionCapacityCurveSolution** solution)
{
   CHECK_RETOBJ(solution);
   
   CComObject<CInteractionCapacityCurveSolution>* pSolution;
   CComObject<CInteractionCapacityCurveSolution>::CreateInstance(&pSolution);
   (*solution) = pSolution;
   (*solution)->AddRef();

   Float64 FzMin, FzMax;
   Float64 Mx, My, eo;
   m_Solver->TensionLimit(&FzMax,&Mx,&My,&eo);
   m_Solver->CompressionLimit(&FzMin,&Mx,&My,&eo);

   if ( nFzSteps < 3 )
      nFzSteps = 3;

   for ( long i = 0; i < nFzSteps; i++ )
   {
      Float64 fz = FzMin + (FzMax - FzMin)*i/(nFzSteps-1);

      CComPtr<IMomentCapacitySolution> mc;

      m_Solver->Solve(fz,na,eo,smFixedCompressiveStrain,&mc);

      (*solution)->AddSolutionPoint(mc);
   }

   return S_OK;
}
