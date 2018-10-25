///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2014  Washington State Department of Transportation
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

// LoadCases.cpp : Implementation of CLoadCases
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "LoadCases.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadCases

STDMETHODIMP CLoadCases::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadCases
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLoadCases::OnLoadCaseChanged(/*[in]*/ILoadCase* pLoadCase, ChangeType change)
{
   Fire_OnLoadCasesChanged(pLoadCase, change);
   return S_OK;
}

STDMETHODIMP CLoadCases::OnLoadCaseRenamed(BSTR oldNam, BSTR newNam)
{
   Fire_OnLoadCasesRenamed(oldNam, newNam);
   return S_OK;
}

HRESULT CLoadCases::OnBeforeAdd( StoredType* pVal)
{
   CHECK_IN(pVal);
   try
   {
      // set up connection 
      HRESULT hr;
      hr = CrAdvise(pVal->second.m_T, this, IID_ILoadCaseEvents, &(pVal->first));
      if (FAILED(hr))
         return hr;
   }
   catch(...)
   {
      ATLASSERT(false);
      return E_FAIL;
   }
   return S_OK;
}

HRESULT CLoadCases::OnAfterAdd( StoredType* pVal)
{
   Fire_OnLoadCasesAdded(pVal->second.m_T);
   return S_OK;
}

HRESULT CLoadCases::OnBeforeRemove ( StoredType* pVal)
{
   try
   {
      // release connection 
      HRESULT hr;
      hr = CrUnadvise(pVal->second.m_T, this, IID_ILoadCaseEvents, pVal->first);
      if (FAILED(hr))
         return hr;
   }
   catch(...)
   {
      ATLASSERT(false);
      return E_FAIL;
   }

   Fire_OnLoadCasesBeforeRemove(pVal->second.m_T);

   return S_OK;
}

HRESULT CLoadCases::OnAfterRemove( BSTR name)
{
   return S_OK;
}

void CLoadCases::FinalRelease()
{
   // free up on destruct
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      this->OnBeforeRemove(*it);
   }
}

STDMETHODIMP CLoadCases::Clone(ILoadCases* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new  collection and fill it up
   CComObject<CLoadCases>* pnew;
   HRESULT hr = CComObject<CLoadCases>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ILoadCases> spisms(pnew);

   // clone properties

   // clone collection
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      CComPtr<ILoadCase> isp;
      
      // deep clone
      hr = it->second.m_T->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection LoadCasents
      hr = spisms->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   return spisms.CopyTo(pColl);
}

