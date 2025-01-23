///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2025  Washington State Department of Transportation
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

// CompositeHaunchDepthFunction.cpp : Implementation of CCompositeHaunchDepthFunction
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "CompositeHaunchDepthFunction.h"
#include <GenericBridge\Helpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompositeHaunchDepthFunction
void CCompositeHaunchDepthFunction::FinalRelease()
{
}

STDMETHODIMP CCompositeHaunchDepthFunction::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICompositeHaunchDepthFunction
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////
STDMETHODIMP CCompositeHaunchDepthFunction::GetHaunchDepth(/*[in]*/Float64 location, /*[out, retval]*/Float64* pHaunchDepth)
{
	if (m_HaunchLayouts.empty())
	{
		ASSERT(0); // should never be called be for Initialize
		return S_FALSE;
	}

	// most common condition will be two spans laid across the segment. First look at front and back
	const HaunchLayout& rfront = m_HaunchLayouts.front();

	// check if location is before or within first layout
	if (location <= rfront.StartLocation + rfront.Length)
	{
		*pHaunchDepth = ::ComputeHaunchDepthAlongSegment(location - rfront.StartLocation, rfront.Length, rfront.HaunchDepths);
	}
	else
	{
		// check if location is within or after the last layout
		const HaunchLayout& rback = m_HaunchLayouts.back();
		if (location > rback.StartLocation)
		{
			*pHaunchDepth = ::ComputeHaunchDepthAlongSegment(location - rback.StartLocation, rback.Length, rback.HaunchDepths);
		}
		else
		{
			std::size_t siz = m_HaunchLayouts.size();
			ASSERT(siz>2);

			bool found = false;
			for (std::size_t ilayout = 1; ilayout < siz - 1; ilayout++)
			{
				const HaunchLayout& rlayout = m_HaunchLayouts[ilayout];
				if (location <= rlayout.StartLocation + rlayout.Length)
				{
					*pHaunchDepth = ::ComputeHaunchDepthAlongSegment(location - rlayout.StartLocation, rlayout.Length, rlayout.HaunchDepths);
					found = true;
					break;
				}
			}

			if (!found)
			{
				ASSERT(0); // This should never happen
				*pHaunchDepth = 0.0;
				return FALSE;
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CCompositeHaunchDepthFunction::Initialize(/*[in]*/Float64 startOffset, /*[in]*/Float64 layoutLength, /*[in]*/IDblArray* haunchVals)
{
	m_StartOffset = startOffset;

	m_HaunchLayouts.clear();

	// create our starting layout
	HaunchLayout layout;
	layout.StartLocation = m_StartOffset;
	layout.Length = layoutLength;

	CComPtr<IEnumDblArray> enum_dbls;
	HRESULT hr = haunchVals->get__EnumElements(&enum_dbls);
	Float64 dbl;
	while (enum_dbls->Next(1, &dbl, nullptr) != S_FALSE)
	{
		layout.HaunchDepths.push_back(dbl);
	}

	m_HaunchLayouts.push_back(layout);

	return S_OK;
}

STDMETHODIMP CCompositeHaunchDepthFunction::AddLayout(/*[in]*/Float64 layoutLength, /*[in]*/IDblArray* haunchVals)
{
	if (m_HaunchLayouts.empty())
	{
		ASSERT(0); // should never be called be for Initialize
		return S_FALSE;
	}

	const HaunchLayout& rback = m_HaunchLayouts.back();

	HaunchLayout layout;
	layout.StartLocation = rback.StartLocation + rback.Length;
	layout.Length = layoutLength;

	CComPtr<IEnumDblArray> enum_dbls;
	HRESULT hr = haunchVals->get__EnumElements(&enum_dbls);
	Float64 dbl;
	while (enum_dbls->Next(1, &dbl, nullptr) != S_FALSE)
	{
		layout.HaunchDepths.push_back(dbl);
	}

	m_HaunchLayouts.push_back(layout);

	return S_OK;
}