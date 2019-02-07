///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2019  Washington State Department of Transportation
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
#include "WBFLLBAM.h"
#include "LoadCombinations.h"
#include "LBAMUtils.h"

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
		&IID_ILoadCombinations
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLoadCombinations::OnLoadCombinationChanged(/*[in]*/ILoadCombination* pLoadCombination, ChangeType change)
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
      hr = CrAdvise(pVal->second.m_T, this, IID_ILoadCombinationEvents, &(pVal->first));
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
      hr = CrUnadvise(pVal->second.m_T, this, IID_ILoadCombinationEvents, pVal->first);
      if (FAILED(hr))
         return hr;
   }
   catch(...)
   {
      ATLASSERT(false);
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
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      this->OnBeforeRemove(*it);
   }
}

STDMETHODIMP CLoadCombinations::Clone(ILoadCombinations* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new  collection and fill it up
   CComObject<CLoadCombinations>* pnew;
   HRESULT hr = CComObject<CLoadCombinations>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ILoadCombinations> spisms(pnew);

   // clone properties

   // clone collection
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      CComPtr<ILoadCombination> isp;
      
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


