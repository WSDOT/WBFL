///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2011  Washington State Department of Transportation
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

// TemporarySupports.cpp : Implementation of CTemporarySupports
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "TemporarySupports.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemporarySupports

STDMETHODIMP CTemporarySupports::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITemporarySupports
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE; 
}

STDMETHODIMP CTemporarySupports::OnTemporarySupportChanged(/*[in]*/ITemporarySupport* pTemporarySupport, BSTR stage, /*[in]*/ChangeType change)
{
   Fire_OnTemporarySupportsChanged(pTemporarySupport, stage, change);
   return S_OK;
}

STDMETHODIMP CTemporarySupports::Clone(/*[out]*/ITemporarySupports* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new stress point collection and fill it up
   CComObject<CTemporarySupports>* pnew;
   HRESULT hr = CComObject<CTemporarySupports>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ITemporarySupports> spisps(pnew); // holder for reference count

   for (iterator it= begin(); it != end(); it++)
   {
      CComPtr<ITemporarySupport> isp;
      
      // deep clone
      hr = it->second.m_T->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection points
      hr = spisps->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   return spisps.CopyTo(pColl);
}

STDMETHODIMP CTemporarySupports::Find(SupportIDType tsID,ITemporarySupport** ppTS)
{
   CHECK_RETOBJ(ppTS);

   for (iterator it= begin(); it != end(); it++)
   {
      CComPtr<ITemporarySupport> ts = it->second;
      SupportIDType id;
      ts->get_ID(&id);

      if ( id == tsID )
      {
         return ts.CopyTo(ppTS);
      }
   }

   return S_OK;
}
