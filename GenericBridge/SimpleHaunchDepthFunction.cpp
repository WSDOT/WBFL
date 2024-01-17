///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2024  Washington State Department of Transportation
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

// SimpleHaunchDepthFunction.cpp : Implementation of CSimpleHaunchDepthFunction
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "SimpleHaunchDepthFunction.h"
#include <GenericBridge\Helpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleHaunchDepthFunction
void CSimpleHaunchDepthFunction::FinalRelease()
{
}

STDMETHODIMP CSimpleHaunchDepthFunction::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISimpleHaunchDepthFunction
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////
STDMETHODIMP CSimpleHaunchDepthFunction::GetHaunchDepth(/*[in]*/Float64 location, /*[out, retval]*/Float64* pHaunchDepth)
{
	location -= m_StartOffset; 

	*pHaunchDepth = ::ComputeHaunchDepthAlongSegment(location, m_LayoutLength, m_HaunchDepths);

	return S_OK;
}

STDMETHODIMP CSimpleHaunchDepthFunction::Initialize(/*[in]*/Float64 startOffset, /*[in]*/Float64 layoutLength, /*[in]*/IDblArray* haunchVals)
{
	m_StartOffset = startOffset;
	m_LayoutLength = layoutLength;

	m_HaunchDepths.clear();

	CComPtr<IEnumDblArray> enum_dbls;
	HRESULT hr = haunchVals->get__EnumElements(&enum_dbls);
	Float64 dbl;
	while (enum_dbls->Next(1, &dbl, nullptr) != S_FALSE)
	{
		m_HaunchDepths.push_back(dbl);
	}

	return S_OK;
}
