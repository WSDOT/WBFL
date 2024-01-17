///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2024  Washington State Department of Transportation
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

// StressPoint.cpp : Implementation of CStressPoint
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "StressPoint.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStressPoint

STDMETHODIMP CStressPoint::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStressPoint
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStressPoint::get_Sa(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_Sa;
	return S_OK;
}

STDMETHODIMP CStressPoint::put_Sa(Float64 newVal)
{
   if (m_Sa != newVal)
   {
	   m_Sa = newVal;
      Fire_OnStressPointChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CStressPoint::get_Sm(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Sm;

	return S_OK;
}

STDMETHODIMP CStressPoint::put_Sm(Float64 newVal)
{
   if (m_Sm!=newVal)
   {
	   m_Sm = newVal;
      Fire_OnStressPointChanged(this);
   }

	return S_OK;
}

static const Float64 MY_VER=1.0;

STDMETHODIMP CStressPoint::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("StressPoint"));
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
      hr = pload->get_Property(_bstr_t("Sa"),&var);
      if (FAILED(hr))
         return hr;

      m_Sa = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("Sm"),&var);
      if (FAILED(hr))
         return hr;

      m_Sm = var;

   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CStressPoint::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   HRESULT hr;
   
   hr = psave->BeginUnit(CComBSTR("StressPoint"), MY_VER);
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("Sa"),_variant_t(m_Sa));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("Sm"),_variant_t(m_Sm));
   if (FAILED(hr))
      return hr;

   hr = psave->EndUnit();
   return hr;
}

STDMETHODIMP CStressPoint::Clone(IStressPoint **clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CStressPoint>* pclone;
   HRESULT hr =CComObject<CStressPoint>::CreateInstance(&pclone);
   if (FAILED(hr))
      return hr;

   pclone->m_Sa = m_Sa;
   pclone->m_Sm = m_Sm;

   *clone = pclone;
   pclone->AddRef(); // for client

	return S_OK;
}
