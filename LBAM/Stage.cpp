///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2010  Washington State Department of Transportation
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

// Stage.cpp : Implementation of CStage
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "Stage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStage

STDMETHODIMP CStage::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStage
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStage::get_Name(BSTR *pVal)
{
	CHECK_RETSTRING(pVal);

   *pVal = m_Name.Copy();
   
	return S_OK;
}

STDMETHODIMP CStage::put_Name(BSTR newVal)
{
   CHECK_IN(newVal);

   CComBSTR name(newVal);
   if (name.Length() == 0)
      return E_INVALIDARG;

   if (name != m_Name)
   {
      m_Name = name;
      Fire_OnStageChanged(this, cgtStage);
   }

	return S_OK;
}

STDMETHODIMP CStage::get_Description(BSTR *pVal)
{
	CHECK_RETSTRING(pVal);
   *pVal = m_Description.Copy();
	return S_OK;
}

STDMETHODIMP CStage::put_Description(BSTR newVal)
{
   CHECK_IN(newVal);

   CComBSTR desc(newVal);
   if (desc.Length() == 0)
      return E_INVALIDARG;

   if (desc != m_Description)
   {
      m_Description = desc;
      Fire_OnStageChanged(this, cgtDescription);
   }

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CStage::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("Stage"));
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
      m_Name = (LPCTSTR)name;

      var.Clear();
      hr = pload->get_Property(_bstr_t("Description"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t description(var);
      m_Description = (LPCTSTR)description;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CStage::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("Stage"), MY_VER);
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("Name"),_variant_t(m_Name));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("Description"),_variant_t(m_Description));
   if (FAILED(hr))
      return hr;

   hr = psave->EndUnit();
   return hr;
}

STDMETHODIMP CStage::Clone(IStage **clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CStage>* pnew;
   HRESULT hr = CComObject<CStage>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IStage> pscs(pnew); // for reference count

   pnew->m_Name                 = m_Name;
   pnew->m_Description          = m_Description;

   return pscs.CopyTo(clone);
}
