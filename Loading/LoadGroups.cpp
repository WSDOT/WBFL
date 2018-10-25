///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
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

// LoadGroups.cpp : Implementation of CLoadGroups
#include "stdafx.h"
#include "WBFLLoading.h"
#include "LoadGroups.h"
#include "LoadingUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadGroups

STDMETHODIMP CLoadGroups::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ldILoadGroups
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CLoadGroups::OnLoadGroupChanged(/*[in]*/ldILoadGroup* pLoadGroup, ldLoadingChangeType change)
{
   Fire_OnLoadGroupsChanged(pLoadGroup, change);
   return S_OK;
}

STDMETHODIMP CLoadGroups::OnLoadGroupRenamed(BSTR oldNam, BSTR newNam)
{
   Fire_OnLoadGroupsRenamed(oldNam, newNam);
   return S_OK;
}

HRESULT CLoadGroups::OnBeforeAdd( StoredType* pVal)
{
   CHECK_IN(pVal);
   try
   {
      // set up connection LoadGroupnt
      HRESULT hr;
      hr = CrAdvise(pVal->second.m_T, this, IID_ldILoadGroupEvents, &(pVal->first));
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

HRESULT CLoadGroups::OnAfterAdd( StoredType* pVal)
{
   Fire_OnLoadGroupsAdded(pVal->second.m_T);
   return S_OK;
}

HRESULT CLoadGroups::OnBeforeRemove ( StoredType* pVal)
{
   try
   {
      // release connection LoadGroupnt
      HRESULT hr;
      hr = CrUnadvise(pVal->second.m_T, this, IID_ldILoadGroupEvents, pVal->first);
      if (FAILED(hr))
         return hr;
   }
   catch(...)
   {
      ATLASSERT(false);
      return E_FAIL;
   }

   Fire_OnLoadGroupsBeforeRemove(pVal->second.m_T);

   return S_OK;
}

HRESULT CLoadGroups::OnAfterRemove( BSTR name)
{
   return S_OK;
}

void CLoadGroups::FinalRelease()
{
   // free up all of our connectionLoadGroupnts on destruct
   for (iterator it= begin(); it != end(); it++)
   {
      this->OnBeforeRemove(*it);
   }
}

STDMETHODIMP CLoadGroups::Clone(ldILoadGroups* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new  collection and fill it up
   CComObject<CLoadGroups>* pnew;
   HRESULT hr = CComObject<CLoadGroups>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ldILoadGroups> spisms(pnew);

   // clone properties

   // clone collection
   for (iterator it= begin(); it != end(); it++)
   {
      CComPtr<ldILoadGroup> isp;
      
      // deep clone
      hr = it->second.m_T->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection LoadGroupnts
      hr = spisms->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   *pColl = spisms;
   (*pColl)->AddRef();

   return S_OK;
}

