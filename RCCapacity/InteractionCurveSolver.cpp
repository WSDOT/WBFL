///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// InteractionCurveSolver.cpp : Implementation of CInteractionCurveSolver
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "InteractionCurveSolver.h"
#include "InteractionCurveSolution.h"
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInteractionCurveSolver

STDMETHODIMP CInteractionCurveSolver::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IInteractionCurveSolver,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CInteractionCurveSolver::FinalConstruct()
{
   m_Solver.CoCreateInstance(CLSID_MomentCurvatureSolver);
   return S_OK;
}

void CInteractionCurveSolver::FinalRelease()
{
}

STDMETHODIMP CInteractionCurveSolver::putref_Section(IGeneralSection* pSection)
{
   return m_Solver->putref_Section(pSection);
}

STDMETHODIMP CInteractionCurveSolver::get_Section(IGeneralSection** pSection)
{
   return m_Solver->get_Section(pSection);
}

STDMETHODIMP CInteractionCurveSolver::put_Slices(long nSlices)
{
   return m_Solver->put_Slices(nSlices);
}

STDMETHODIMP CInteractionCurveSolver::get_Slices(long* nSlices)
{
   return m_Solver->get_Slices(nSlices);
}

STDMETHODIMP CInteractionCurveSolver::put_SliceGrowthFactor(Float64 sliceGrowthFactor)
{
   return m_Solver->put_SliceGrowthFactor(sliceGrowthFactor);
}

STDMETHODIMP CInteractionCurveSolver::get_SliceGrowthFactor(Float64* sliceGrowthFactor)
{
   return m_Solver->get_SliceGrowthFactor(sliceGrowthFactor);
}

STDMETHODIMP CInteractionCurveSolver::put_AxialTolerance(Float64 tolerance)
{
   return m_Solver->put_AxialTolerance(tolerance);
}

STDMETHODIMP CInteractionCurveSolver::get_AxialTolerance(Float64* tolerance)
{
   return m_Solver->get_AxialTolerance(tolerance);
}

STDMETHODIMP CInteractionCurveSolver::put_MaxIterations(long maxIter)
{
   return m_Solver->put_MaxIterations(maxIter);
}

STDMETHODIMP CInteractionCurveSolver::get_MaxIterations(long* maxIter)
{
   return m_Solver->get_MaxIterations(maxIter);
}

STDMETHODIMP CInteractionCurveSolver::put_InitialCurvatureStep(Float64 k)
{
   return m_Solver->put_InitialCurvatureStep(k);
}

STDMETHODIMP CInteractionCurveSolver::get_InitialCurvatureStep(Float64* k)
{
   return m_Solver->get_InitialCurvatureStep(k);
}

STDMETHODIMP CInteractionCurveSolver::Solve(Float64 Fz,long naIncrement,IInteractionCurveSolution** solution)
{
   CHECK_RETOBJ(solution);
   
   CComObject<CInteractionCurveSolution>* pSolution;
   CComObject<CInteractionCurveSolution>::CreateInstance(&pSolution);
   (*solution) = pSolution;
   (*solution)->AddRef();

   for ( long i = 0; i < naIncrement; i++ )
   {
      Float64 angle = i*TWO_PI/naIncrement;
      CComPtr<IMomentCurvatureSolution> mc;

      m_Solver->Solve(Fz,angle,&mc);

      (*solution)->AddSolutionPoint(angle,mc);

      if ( i == 0 )
         (*solution)->AddSolutionPoint(TWO_PI,mc);
   }

   return S_OK;
}
