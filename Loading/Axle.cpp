///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2021  Washington State Department of Transportation
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

// Axle.cpp : Implementation of CAxle
#include "stdafx.h"
#include "WBFLLoading.h"
#include "Axle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAxle

STDMETHODIMP CAxle::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ldIAxle
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAxle::get_Weight(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_Weight;

	return S_OK;
}

STDMETHODIMP CAxle::put_Weight(Float64 newVal)
{
   if (newVal<=0.0)
      return E_INVALIDARG;

	if (newVal != m_Weight)
   {
      m_Weight = newVal;
      Fire_OnAxleChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CAxle::get_Spacing(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Spacing;

	return S_OK;
}

STDMETHODIMP CAxle::put_Spacing(Float64 newVal)
{
   if (newVal<=0.0)
      return E_INVALIDARG;

	if (newVal != m_Spacing)
   {
      m_Spacing = newVal;
      Fire_OnAxleChanged(this);
   }

	return S_OK;
}

static const Float64 MY_VER=1.0;

STDMETHODIMP CAxle::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("Axle"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      CComVariant var;
      hr = pload->get_Property(CComBSTR("Weight"),&var);
      if (FAILED(hr))
         return hr;

      m_Weight = var.dblVal;
      var.Clear();

      hr = pload->get_Property(CComBSTR("Spacing"),&var);
      if (FAILED(hr))
         return hr;

      m_Spacing = var.dblVal;

   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CAxle::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   
   hr = psave->BeginUnit(CComBSTR("Axle"), MY_VER);
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("Weight"),CComVariant(m_Weight));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("Spacing"),CComVariant(m_Spacing));
   if (FAILED(hr))
      return hr;

   hr = psave->EndUnit();
   return hr;
}

STDMETHODIMP CAxle::Clone(ldIAxle **clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CAxle>* pclone;
   HRESULT hr =CComObject<CAxle>::CreateInstance(&pclone);
   if (FAILED(hr))
      return hr;

   pclone->m_Weight = m_Weight;
   pclone->m_Spacing = m_Spacing;

   *clone = pclone;
   pclone->AddRef(); // for client

	return S_OK;
}
