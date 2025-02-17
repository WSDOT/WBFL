///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright � 1999-2025  Washington State Department of Transportation
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

// BridgeDeckRebarPattern.cpp : Implementation of CBridgeDeckRebarPattern
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "BridgeDeckRebarPattern.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBridgeDeckRebarPattern
HRESULT CBridgeDeckRebarPattern::FinalConstruct()
{
   m_bIsLumped = VARIANT_FALSE;
   return S_OK;
}

void CBridgeDeckRebarPattern::FinalRelease()
{
   m_RebarLayoutItem.Detach();
}

STDMETHODIMP CBridgeDeckRebarPattern::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBridgeDeckRebarPattern,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// IBridgeDeckRebarPattern implementation
STDMETHODIMP CBridgeDeckRebarPattern::putref_Rebar(IRebar* rebar)
{
   CHECK_IN(rebar);
   m_Rebar = rebar;
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarPattern::get_Rebar(IRebar** rebar)
{
   CHECK_RETOBJ(rebar);
   return m_Rebar.CopyTo(rebar);
}

STDMETHODIMP CBridgeDeckRebarPattern::putref_RebarLayoutItem(IBridgeDeckRebarLayoutItem* rebarLayoutItem)
{
   CHECK_IN(rebarLayoutItem);
   m_RebarLayoutItem.Detach();
   m_RebarLayoutItem.Attach(rebarLayoutItem);
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarPattern::put_Spacing(Float64 spacing)
{
   m_Spacing = spacing;
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarPattern::get_Spacing(Float64* spacing)
{
   CHECK_RETVAL(spacing);
   *spacing = m_Spacing;
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarPattern::put_Location(Float64 y)
{
   m_Y = y;
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarPattern::get_Location(Float64* pY)
{
   CHECK_RETVAL(pY);
   *pY = m_Y;
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarPattern::put_IsLumped(VARIANT_BOOL bIsLumped)
{
   m_bIsLumped = bIsLumped;
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarPattern::get_IsLumped(VARIANT_BOOL* pbIsLumped)
{
   CHECK_RETVAL(pbIsLumped);
   *pbIsLumped = m_bIsLumped;
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CBridgeDeckRebarPattern::Load(IStructuredLoad2* load)
{
   ATLASSERT(false);
   return E_NOTIMPL;
}

STDMETHODIMP CBridgeDeckRebarPattern::Save(IStructuredSave2* save)
{
   ATLASSERT(false);
   return E_NOTIMPL;
}
