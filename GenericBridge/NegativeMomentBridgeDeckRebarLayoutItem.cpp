///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
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

// NegativeMomentBridgeDeckRebarLayoutItem.cpp : Implementation of CNegativeMomentBridgeDeckRebarLayoutItem
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "NegativeMomentBridgeDeckRebarLayoutItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNegativeMomentBridgeDeckRebarLayoutItem
void CNegativeMomentBridgeDeckRebarLayoutItem::FinalRelease()
{
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_INegativeMomentBridgeDeckRebarLayoutItem,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::get__EnumRebarPatterns(IEnumBridgeDeckRebarPatterns** enumRebarPatterns)
{
   return get__EnumElements(enumRebarPatterns);
}

/////////////////////////////////////////////////////////////////
HRESULT CNegativeMomentBridgeDeckRebarLayoutItem::DoSaveItem(IStructuredSave2* save,IRebarPattern* item)
{
   CComQIPtr<IStructuredStorage2> ssRebarPattern(item);
   return ssRebarPattern->Save(save);
}

HRESULT CNegativeMomentBridgeDeckRebarLayoutItem::DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem)
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

Float64 CNegativeMomentBridgeDeckRebarLayoutItem::GetStart(Float64 offset)
{
   Float64 start;
   get_Start(&start); // start point of bar measured relative to the intersection of the pier line and the alignment

   CComPtr<IAngle> objSkewAngle;
   m_Pier->get_SkewAngle(&objSkewAngle);
   Float64 skewAngle;
   objSkewAngle->get_Value(&skewAngle);
   start += offset*tan(skewAngle);
   return start;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::ContainsLocation(Float64 distFromStart,Float64 offset,VARIANT_BOOL* bResult)
{
   CHECK_RETVAL(bResult);

   Float64 start = GetStart(offset);
   Float64 length;
   get_Length(&length);
   Float64 end = start+length;

   *bResult = (::InRange(start,distFromStart,end) ? VARIANT_TRUE : VARIANT_FALSE);

   return S_OK;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::get_Start(Float64* start)
{
   CHECK_RETVAL(start);
   *start = m_PierLocation - m_LeftCutoff;
   return S_OK;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::get_Length(Float64* length)
{
   CHECK_RETVAL(length);
   *length = m_LeftCutoff + m_RightCutoff;
   return S_OK;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::AddRebarPattern(IBridgeDeckRebarPattern* pattern)
{
   pattern->putref_RebarLayoutItem(this);
   return Add(pattern);
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::putref_Bridge(IGenericBridge* pBridge)
{
   CHECK_IN(pBridge);
   m_pBridge = pBridge;
   return S_OK;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::put_PierID(PierIDType pierID)
{
   ATLASSERT(m_pBridge != nullptr); // call putref_Bridge before setting the pier
   CComPtr<IPierCollection> piers;
   m_pBridge->get_Piers(&piers);

   m_PierID = pierID;
   m_Pier.Release();
   HRESULT hr = piers->FindPierByID(pierID, &m_Pier);
   ATLASSERT(SUCCEEDED(hr));

   m_Pier->get_Location(&m_PierLocation);

   return S_OK;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::get_PierID(PierIDType* pPierID)
{
   CHECK_RETVAL(pPierID);
   *pPierID = m_PierID;
   return S_OK;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::put_LeftCutoff(Float64 coLeft)
{
   if ( coLeft < 0 )
      return E_INVALIDARG;

   m_LeftCutoff = coLeft;
   return S_OK;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::get_LeftCutoff(Float64* pcoLeft)
{
   CHECK_RETVAL(pcoLeft);
   *pcoLeft = m_LeftCutoff;
   return S_OK;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::put_RightCutoff(Float64 coRight)
{
   if ( coRight < 0 )
      return E_INVALIDARG;

   m_RightCutoff = coRight;
   return S_OK;
}

STDMETHODIMP CNegativeMomentBridgeDeckRebarLayoutItem::get_RightCutoff(Float64* pcoRight)
{
   CHECK_RETVAL(pcoRight);
   *pcoRight = m_RightCutoff;
   return S_OK;
}
