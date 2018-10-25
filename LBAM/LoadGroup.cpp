///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
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

// LoadGroup.cpp : Implementation of CLoadGroup
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "LoadGroup.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadGroup

STDMETHODIMP CLoadGroup::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadGroup
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLoadGroup::get_Name(BSTR *pVal)
{
	CHECK_RETOBJ(pVal);

   *pVal = m_Name.Copy();
   
	return S_OK;
}

STDMETHODIMP CLoadGroup::put_Name(BSTR newVal)
{
   CHECK_IN(newVal);

   CComBSTR name(newVal);
   if (name.Length() == 0)
      return E_INVALIDARG;

   if (name != m_Name)
   {
      CComBSTR oldnam(m_Name);
      m_Name = name;
      Fire_OnLoadGroupRenamed(oldnam, newVal);
   }

	return S_OK;
}

STDMETHODIMP CLoadGroup::get_Description(BSTR *pVal)
{
	CHECK_RETOBJ(pVal);
   *pVal = m_Description.Copy();
	return S_OK;
}

STDMETHODIMP CLoadGroup::put_Description(BSTR newVal)
{
   CHECK_IN(newVal);

   CComBSTR desc(newVal);
   if (desc.Length() == 0)
      return E_INVALIDARG;

   if (desc != m_Description)
   {
      m_Description = desc;
      Fire_OnLoadGroupChanged(this, cgtDescription);
   }

	return S_OK;
}

STDMETHODIMP CLoadGroup::get_Transient(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_Transient;

	return S_OK;
}

STDMETHODIMP CLoadGroup::put_Transient(VARIANT_BOOL newVal)
{
   if (newVal!=m_Transient)
   {
      m_Transient = newVal;
      Fire_OnLoadGroupChanged(this, cgtLoads);
   }

	return S_OK;
}


// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CLoadGroup::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("LoadGroup"));
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
      hr = pload->get_Property(_bstr_t("Name"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t name(var);
      m_Name = (const char*)name;

      var.Clear();
      hr = pload->get_Property(_bstr_t("Description"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t description(var);
      m_Description = (const char*)description;
 
      var.Clear();
      hr = pload->get_Property(_bstr_t("Transient"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t istrn(var);
      if (istrn == _bstr_t("True"))
      {
         m_Transient = VARIANT_TRUE;
      }
      else if (istrn == _bstr_t("False"))
      {
         m_Transient = VARIANT_FALSE;
      }
      else
      {
         ATLASSERT(0);
         return STRLOAD_E_INVALIDFORMAT;
      }
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CLoadGroup::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("LoadGroup"), MY_VER);
      hr = psave->put_Property(CComBSTR("Name"),_variant_t(m_Name));
      hr = psave->put_Property(CComBSTR("Description"),_variant_t(m_Description));

      _bstr_t issymm("False");
      if (m_Transient == VARIANT_TRUE)
         issymm = "True";

      hr = psave->put_Property(CComBSTR("Transient"),_variant_t(issymm));

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadGroup);
   }

   return S_OK;
}

STDMETHODIMP CLoadGroup::Clone(ILoadGroup **clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CLoadGroup>* pnew;
   HRESULT hr = CComObject<CLoadGroup>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ILoadGroup> pscs(pnew); // for reference count

   pnew->m_Name                 = m_Name;
   pnew->m_Description          = m_Description;
   pnew->m_Transient            = m_Transient;

   return pscs.CopyTo(clone);
}


