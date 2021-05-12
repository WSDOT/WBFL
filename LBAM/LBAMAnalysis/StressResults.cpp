///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2021  Washington State Department of Transportation
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

// StressResults.cpp : Implementation of CStressResults
#include "stdafx.h"
#include "WBFLLBAMAnalysis.h"
#include "StressResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStressResults

STDMETHODIMP CStressResults::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStressResults
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStressResults::Clone(/*[out]*/IStressResults* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new stress point collection and fill it up
   CComObject<CStressResults>* pnew;
   HRESULT hr = CComObject<CStressResults>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IStressResults> spisps(pnew); // holder for reference count

   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      CComPtr<IStressResult> isp;
      
      // deep clone
      hr = it->second.m_T->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection points
      hr = spisps->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   *pColl = spisps;
   (*pColl)->AddRef();

   return S_OK;
}


