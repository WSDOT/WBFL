///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2012  Washington State Department of Transportation
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

// FixedLengthRebarLayoutItem.cpp : Implementation of CFixedLengthRebarLayoutItem

#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "FixedLengthRebarLayoutItem.h"


// CFixedLengthRebarLayoutItem

STDMETHODIMP CFixedLengthRebarLayoutItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFixedLengthRebarLayoutItem
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CFixedLengthRebarLayoutItem::get__EnumRebarPatterns(IEnumRebarPatterns** enumRebarPatterns)
{
   return get__EnumElements(enumRebarPatterns);
}

HRESULT CFixedLengthRebarLayoutItem::DoSaveItem(IStructuredSave2* save,IRebarPattern* item)
{
   CComQIPtr<IStructuredStorage2> ssRebarPattern(item);
   return ssRebarPattern->Save(save);
}

HRESULT CFixedLengthRebarLayoutItem::DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem)
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

STDMETHODIMP CFixedLengthRebarLayoutItem::ContainsLocation(Float64 distFromGdrStart,VARIANT_BOOL* bResult)
{
   CHECK_RETVAL(bResult);

   *bResult = (distFromGdrStart >= m_Start && distFromGdrStart <= m_End ) ? VARIANT_TRUE : VARIANT_FALSE;

   return S_OK;
}

STDMETHODIMP CFixedLengthRebarLayoutItem::put_Start(Float64 start)
{
   ATLASSERT(start>=0.0);

   m_Start = start;

   return S_OK;
}

STDMETHODIMP CFixedLengthRebarLayoutItem::get_Start(Float64* start)
{
   CHECK_RETVAL(start);

   *start = m_Start;

   return S_OK;
}

STDMETHODIMP CFixedLengthRebarLayoutItem::put_End(Float64 end)
{
   m_End = end;

   return S_OK;
}

STDMETHODIMP CFixedLengthRebarLayoutItem::get_End(Float64* end)
{
   CHECK_RETVAL(end);

   Float64 gdr_length;
   m_pGirder->get_GirderLength(&gdr_length);
   if (m_End > gdr_length)
   {
      ATLASSERT(0); // may want to reconsider allowing this
      *end = gdr_length;
   }
   else
   {
      *end = m_End;
   }

   return S_OK;
}


STDMETHODIMP CFixedLengthRebarLayoutItem::get_Length(Float64* length)
{
   CHECK_RETVAL(length);
   Float64 end, start;
   get_End(&end);
   get_Start(&start);

   *length = end-start;

   return S_OK;
}

STDMETHODIMP CFixedLengthRebarLayoutItem::AddRebarPattern(IRebarPattern* pattern)
{
   pattern->putref_RebarLayoutItem(this);
   return Add(pattern);
}

STDMETHODIMP CFixedLengthRebarLayoutItem::putref_Girder(IPrecastGirder* girder)
{
   CHECK_IN(girder);
   m_pGirder = girder;
   return S_OK;
}
