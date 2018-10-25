///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright (C) 2009  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// Axles.cpp : Implementation of CAxles
#include "stdafx.h"
#include "WBFLLoading.h"
#include "Axles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAxles

STDMETHODIMP CAxles::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ldIAxles
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAxles::OnAxleChanged(/*[in]*/ldIAxle* pAxle)
{
   CHECK_IN(pAxle);

   Fire_OnAxlesChanged(pAxle);
   return S_OK;
}

STDMETHODIMP CAxles::Clone(ldIAxles* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new  collection and fill it up
   CComObject<CAxles>* pnew;
   HRESULT hr = CComObject<CAxles>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ldIAxles> spisms(pnew);

   // clone properties

   // clone collection
   for (iterator it= begin(); it != end(); it++)
   {
      CComPtr<ldIAxle> isp;
      
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


