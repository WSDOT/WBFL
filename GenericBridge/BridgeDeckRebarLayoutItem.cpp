///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2018  Washington State Department of Transportation
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

// BridgeDeckRebarLayoutItem.cpp : Implementation of CBridgeDeckRebarLayoutItem
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "BridgeDeckRebarLayoutItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBridgeDeckRebarLayoutItem
void CBridgeDeckRebarLayoutItem::FinalRelease()
{
}

STDMETHODIMP CBridgeDeckRebarLayoutItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBridgeDeckRebarLayoutItem,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CBridgeDeckRebarLayoutItem::get__EnumRebarPatterns(IEnumBridgeDeckRebarPatterns** enumRebarPatterns)
{
   return get__EnumElements(enumRebarPatterns);
}

/////////////////////////////////////////////////////////////////
HRESULT CBridgeDeckRebarLayoutItem::DoSaveItem(IStructuredSave2* save,IRebarPattern* item)
{
   CComQIPtr<IStructuredStorage2> ssRebarPattern(item);
   return ssRebarPattern->Save(save);
}

HRESULT CBridgeDeckRebarLayoutItem::DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem)
{
//   // Create a new span object
//   CComObject<CSpan>* pSpan;
//   CComObject<CSpan>::CreateInstance(&pSpan);
//   CComPtr<ISpan> newSpan = pSpan;
//
//   ATLASSERT(m_pBridge != nullptr);
//   pSpan->SetBridge(m_pBridge);
//
//   CComQIPtr<IStructuredStorage2> ssSpan(newSpan);
//   HRESULT hr = ssSpan->Load(load);
//   if ( FAILED(hr) )
//      return hr;
//
//   (*ppItem) = newSpan;
//   (*ppItem)->AddRef();
//
//   return S_OK;

   // Need to polymorphically create rebar pattern item
   return E_FAIL;
}

STDMETHODIMP CBridgeDeckRebarLayoutItem::ContainsLocation(Float64 distFromStart,Float64 offset,VARIANT_BOOL* bResult)
{
   CHECK_RETVAL(bResult);

   Float64 start, length;
   get_Start(&start);
   get_Length(&length);
   Float64 end = start + length;

   *bResult = (::InRange(start,distFromStart,end) ? VARIANT_TRUE : VARIANT_FALSE);

   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarLayoutItem::get_Start(Float64* start)
{
   CHECK_RETVAL(start);
   *start = 0;
   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarLayoutItem::get_Length(Float64* length)
{
   CHECK_RETVAL(length);

   m_pBridge->get_Length(length);

   return S_OK;
}

STDMETHODIMP CBridgeDeckRebarLayoutItem::AddRebarPattern(IBridgeDeckRebarPattern* pattern)
{
   pattern->putref_RebarLayoutItem(this);
   return Add(pattern);
}

STDMETHODIMP CBridgeDeckRebarLayoutItem::putref_Bridge(IGenericBridge* pBridge)
{
   CHECK_IN(pBridge);
   m_pBridge = pBridge;
   return S_OK;
}
