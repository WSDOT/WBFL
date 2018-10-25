///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2015  Washington State Department of Transportation
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

// LoadCombinations.cpp : Implementation of CLoadCombinations
#include "stdafx.h"
#include "WBFLLoading.h"
#include "LoadCombinations.h"
#include "LoadingUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinations

STDMETHODIMP CLoadCombinations::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ldILoadCombinations
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLoadCombinations::OnLoadCombinationChanged(/*[in]*/ldILoadCombination* pLoadCombination, ldLoadingChangeType change)
{
   Fire_OnLoadCombinationsChanged(pLoadCombination, change);
   return S_OK;
}

STDMETHODIMP CLoadCombinations::OnLoadCombinationRenamed(BSTR oldNam, BSTR newNam)
{
   Fire_OnLoadCombinationsRenamed(oldNam, newNam);
   return S_OK;
}

HRESULT CLoadCombinations::OnBeforeAdd( StoredType* pVal)
{
   CHECK_IN(pVal);
   try
   {
      // set up connection LoadCombinationnt
      HRESULT hr;
      hr = CrAdvise(pVal->second.m_T, this, IID_ldILoadCombinationEvents, &(pVal->first));
      if (FAILED(hr))
         return hr;
   }
   catch(...)
   {
      ATLASSERT(0);
      return E_FAIL;
   }
   return S_OK;
}

HRESULT CLoadCombinations::OnAfterAdd( StoredType* pVal)
{
   Fire_OnLoadCombinationsAdded(pVal->second.m_T);
   return S_OK;
}

HRESULT CLoadCombinations::OnBeforeRemove ( StoredType* pVal)
{
   try
   {
      // release connection LoadCombinationnt
      HRESULT hr;
      hr = CrUnadvise(pVal->second.m_T, this, IID_ldILoadCombinationEvents, pVal->first);
      if (FAILED(hr))
         return hr;
   }
   catch(...)
   {
      ATLASSERT(0);
      return E_FAIL;
   }

   Fire_OnLoadCombinationsBeforeRemove(pVal->second.m_T);

   return S_OK;
}

HRESULT CLoadCombinations::OnAfterRemove( BSTR name)
{
   return S_OK;
}

void CLoadCombinations::FinalRelease()
{
   // free up all of our connectionLoadCombinationnts on destruct
   for (iterator it= begin(); it != end(); it++)
   {
      this->OnBeforeRemove(*it);
   }
}

STDMETHODIMP CLoadCombinations::Clone(ldILoadCombinations* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new  collection and fill it up
   CComObject<CLoadCombinations>* pnew;
   HRESULT hr = CComObject<CLoadCombinations>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ldILoadCombinations> spisms(pnew);

   // clone properties

   // clone collection
   for (iterator it= begin(); it != end(); it++)
   {
      CComPtr<ldILoadCombination> isp;
      
      // deep clone
      hr = it->second.m_T->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection LoadCombinations
      hr = spisms->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   return spisms.CopyTo(pColl);
}


