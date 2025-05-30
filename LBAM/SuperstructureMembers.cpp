///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2025  Washington State Department of Transportation
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

// SuperstructureMembers.cpp : Implementation of CSuperstructureMembers
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "SuperstructureMembers.h"


/////////////////////////////////////////////////////////////////////////////
// CSuperstructureMembers

STDMETHODIMP CSuperstructureMembers::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISuperstructureMembers
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSuperstructureMembers::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 len = 0;
   iterator it( begin() );
   iterator itend( end() );
	for(; it!=itend; it++)
   {
      Float64 tmp;
      HRESULT hr = it->second.m_T->get_Length(&tmp);
      if (FAILED(hr))
         return hr;

      len += tmp;
   }

   *pVal = len;

	return S_OK;
}

STDMETHODIMP CSuperstructureMembers::get_Offset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_Offset;

	return S_OK;
}

STDMETHODIMP CSuperstructureMembers::put_Offset(Float64 newVal)
{
	if (newVal<=0.0)
      return E_INVALIDARG;

   if (newVal!=m_Offset)
   {
      m_Offset = newVal;
      Fire_OnSuperstructureMembersOffset();
   } 

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CSuperstructureMembers::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(_bstr_t("SuperstructureMembers"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      _variant_t var;
      hr = pload->get_Property(_bstr_t("Offset"),&var);
      if (FAILED(hr))
         return hr;

      m_Offset = var;

      hr = PersistentSuperstructureMemberCollImpl::Load(pload);
      if (FAILED(hr))
         return hr;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CSuperstructureMembers::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(_bstr_t("SuperstructureMembers"), MY_VER);
      hr = psave->put_Property(_bstr_t("Offset"),_variant_t(m_Offset));
      hr = PersistentSuperstructureMemberCollImpl::Save(psave);
      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMembers);
   }

   return S_OK;
}

STDMETHODIMP CSuperstructureMembers::OnSuperstructureMemberChanged(/*[in]*/ISuperstructureMember* pSuperstructureMember, BSTR stage, ChangeType change)
{
   Fire_OnSuperstructureMembersChanged(pSuperstructureMember, stage, change);
   return S_OK;
}

STDMETHODIMP CSuperstructureMembers::Clone(ISuperstructureMembers* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new stress point collection and fill it up
   CComObject<CSuperstructureMembers>* pnew;
   HRESULT hr = CComObject<CSuperstructureMembers>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ISuperstructureMembers> spisms(pnew);

   // clone properties
   pnew->m_Offset = m_Offset;

   // clone collection
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      CComPtr<ISuperstructureMember> isp;
      
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


