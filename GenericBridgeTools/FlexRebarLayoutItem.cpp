///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2015  Washington State Department of Transportation
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

// FlexRebarLayoutItem.cpp : Implementation of CFlexRebarLayoutItem
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "FlexRebarLayoutItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlexRebarLayoutItem
void CFlexRebarLayoutItem::FinalRelease()
{
}

STDMETHODIMP CFlexRebarLayoutItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFlexRebarLayoutItem,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CFlexRebarLayoutItem::get__EnumRebarPatterns(IEnumRebarPatterns** enumRebarPatterns)
{
   return get__EnumElements(enumRebarPatterns);
}

/////////////////////////////////////////////////////////////////
HRESULT CFlexRebarLayoutItem::DoSaveItem(IStructuredSave2* save,IRebarPattern* item)
{
   CComQIPtr<IStructuredStorage2> ssRebarPattern(item);
   return ssRebarPattern->Save(save);
}

HRESULT CFlexRebarLayoutItem::DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem)
{
//   // Create a new span object
//   CComObject<CSpan>* pSpan;
//   CComObject<CSpan>::CreateInstance(&pSpan);
//   CComPtr<ISpan> newSpan = pSpan;
//
//   ATLASSERT(m_pBridge != NULL);
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

STDMETHODIMP CFlexRebarLayoutItem::ContainsLocation(Float64 distFromStart,VARIANT_BOOL* bResult)
{
   CHECK_RETVAL(bResult);

   Float64 start, length;
   get_Start(&start);
   get_Length(&length);

   *bResult = (distFromStart < start || (start+length) < distFromStart ) ? VARIANT_FALSE : VARIANT_TRUE;

   return S_OK;
}

STDMETHODIMP CFlexRebarLayoutItem::get_Start(Float64* start)
{
   CHECK_RETVAL(start);

   Float64 length;
   get_Length(&length);

   Float64 gdr_length;
   m_pGirder->get_GirderLength(&gdr_length);

   switch( m_Position )
   {
   case lpLeft:
      *start = 0;
      break;

   case lpCenter:
      *start = (gdr_length - length)/2;
      break;

   case lpRight:
      *start = gdr_length - length;
      break;
   }

   return S_OK;
}

STDMETHODIMP CFlexRebarLayoutItem::get_Length(Float64* length)
{
   CHECK_RETVAL(length);
   Float64 gdr_length;
   m_pGirder->get_GirderLength(&gdr_length);

   *length = m_Factor*gdr_length;

   return S_OK;
}

STDMETHODIMP CFlexRebarLayoutItem::AddRebarPattern(IRebarPattern* pattern)
{
   pattern->putref_RebarLayoutItem(this);
   return Add(pattern);
}

STDMETHODIMP CFlexRebarLayoutItem::get_Position(LayoutPosition* lp)
{
   CHECK_RETVAL(lp);
   *lp = m_Position;
   return S_OK;
}

STDMETHODIMP CFlexRebarLayoutItem::put_Position(LayoutPosition lp)
{
   m_Position = lp;
   return S_OK;
}

STDMETHODIMP CFlexRebarLayoutItem::get_LengthFactor(Float64* lf)
{
   CHECK_RETVAL(lf);
   *lf = m_Factor;
   return S_OK;
}

STDMETHODIMP CFlexRebarLayoutItem::put_LengthFactor(Float64 lf)
{
   m_Factor = lf;
   return S_OK;
}

STDMETHODIMP CFlexRebarLayoutItem::putref_Girder(IPrecastGirder* girder)
{
   CHECK_IN(girder);
   m_pGirder = girder;
   return S_OK;
}
