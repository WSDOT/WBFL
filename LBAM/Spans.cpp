///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// Spans.cpp : Implementation of CSpans
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "Spans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpans

STDMETHODIMP CSpans::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISpans
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSpans::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 length = 0.0;

   // clone collection
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      Float64 len;
      CComPtr<ISpan>& isp = it->second.m_T;

      HRESULT hr = isp->get_Length(&len);
      if (FAILED(hr))
         return hr;

      length += len;
   }

   *pVal = length;

	return S_OK;
}

STDMETHODIMP CSpans::OnSpanChanged(/*[in]*/ISpan* pSpan, BSTR stage, ChangeType change)
{
   Fire_OnSpansChanged(pSpan, stage, change);
   return S_OK;
}

STDMETHODIMP CSpans::Clone(ISpans* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new  collection and fill it up
   CComObject<CSpans>* pnew;
   HRESULT hr = CComObject<CSpans>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ISpans> spisms(pnew);

   // clone properties

   // clone collection
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      CComPtr<ISpan> isp;
      
      // deep clone
      hr = it->second.m_T->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection points
      hr = spisms->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   return spisms.CopyTo(pColl);
}


