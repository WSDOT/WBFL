///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2013  Washington State Department of Transportation
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

// VehicularLoads.cpp : Implementation of CVehicularLoads
#include "stdafx.h"
#include "WBFLLoading.h"
#include "VehicularLoads.h"
#include "LoadingUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVehicularLoads

STDMETHODIMP CVehicularLoads::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ldIVehicularLoads
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CVehicularLoads::OnVehicularLoadChanged(/*[in]*/ldIVehicularLoad* pVehicularLoad, ldLoadingChangeType change)
{
   Fire_OnVehicularLoadsChanged(pVehicularLoad, change);
   return S_OK;
}

STDMETHODIMP CVehicularLoads::OnVehicularLoadRenamed(BSTR oldNam, BSTR newNam)
{
   Fire_OnVehicularLoadsRenamed(oldNam, newNam);
   return S_OK;
}

HRESULT CVehicularLoads::OnBeforeAdd( StoredType* pVal)
{
   CHECK_IN(pVal);
   try
   {
      // set up connection VehicularLoadnt
      HRESULT hr;
      hr = CrAdvise(pVal->second.m_T, this, IID_ldIVehicularLoadEvents, &(pVal->first));
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

HRESULT CVehicularLoads::OnAfterAdd( StoredType* pVal, VehicleIndexType idx)
{
   Fire_OnVehicularLoadsAdded(pVal->second.m_T);
   return S_OK;
}

HRESULT CVehicularLoads::OnBeforeRemove ( StoredType* pVal, VehicleIndexType idx)
{
   try
   {
      // release connection VehicularLoadnt
      HRESULT hr;
      hr = CrUnadvise(pVal->second.m_T, this, IID_ldIVehicularLoadEvents, pVal->first);
      if (FAILED(hr))
         return hr;
   }
   catch(...)
   {
      ATLASSERT(0);
      return E_FAIL;
   }

   Fire_OnVehicularLoadsBeforeRemove(pVal->second.m_T);

   return S_OK;
}

HRESULT CVehicularLoads::OnAfterRemove( VehicleIndexType idx)
{
   return S_OK;
}

void CVehicularLoads::FinalRelease()
{
   // free up all of our connectionVehicularLoadnts on destruct
   CollectionIndexType i=0;
   for (iterator it= begin(); it != end(); it++)
   {
      this->OnBeforeRemove(*it, i);
      i++;
   }
}

STDMETHODIMP CVehicularLoads::Clone(ldIVehicularLoads* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new  collection and fill it up
   CComObject<CVehicularLoads>* pnew;
   HRESULT hr = CComObject<CVehicularLoads>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ldIVehicularLoads> spisms(pnew);

   // clone properties

   // clone collection
   for (iterator it= begin(); it != end(); it++)
   {
      CComPtr<ldIVehicularLoad> isp;
      
      // deep clone
      hr = it->second.m_T->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection VehicularLoadnts
      hr = spisms->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   return spisms.CopyTo(pColl);
}

