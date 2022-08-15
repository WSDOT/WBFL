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

// InteractionCapacityCurveSolution.cpp : Implementation of CInteractionCapacityCurveSolution
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "InteractionCapacityCurveSolution.h"
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInteractionCapacityCurveSolution

STDMETHODIMP CInteractionCapacityCurveSolution::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IInteractionCapacityCurveSolution,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CInteractionCapacityCurveSolution::get_MomentCapacitySolution(CollectionIndexType index,IMomentCapacitySolution** solution)
{
   CHECK_RETOBJ(solution);
   *solution = m_CapacityInfo[index].Capacity;
   (*solution)->AddRef();
   return S_OK;
}

STDMETHODIMP CInteractionCapacityCurveSolution::AddSolutionPoint(IMomentCapacitySolution* solution)
{
   CHECK_IN(solution);
   CAPACITYINFO ci;
   solution->get_Fz(&ci.Fz);
   ci.Capacity = solution;
   m_CapacityInfo.push_back(ci);
   std::sort(m_CapacityInfo.begin(), m_CapacityInfo.end());

   return S_OK;
}

STDMETHODIMP CInteractionCapacityCurveSolution::get_SolutionPointCount(CollectionIndexType* nPoints)
{
   CHECK_RETVAL(nPoints);
   *nPoints = m_CapacityInfo.size();
   return S_OK;
}
