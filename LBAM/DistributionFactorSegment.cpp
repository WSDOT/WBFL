///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2016  Washington State Department of Transportation
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

// DistributionFactorSegment.cpp : Implementation of CDistributionFactorSegment
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "DistributionFactorSegment.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDistributionFactorSegment

STDMETHODIMP CDistributionFactorSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDistributionFactorSegment
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CDistributionFactorSegment::FinalRelease()
{
   HRESULT hr;
   if (!!m_pDistributionFactor)
   {
      hr = CrUnadvise(m_pDistributionFactor, this, IID_IDistributionFactorEvents, m_DistributionFactorCookie);
      ATLASSERT(SUCCEEDED(hr));
   }
}

STDMETHODIMP CDistributionFactorSegment::FinalConstruct( )
{
   HRESULT hr;
   // create a default, empty df and set up connection point
   // up a connection point to it
   hr = m_pDistributionFactor.CoCreateInstance(CLSID_DistributionFactor);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_pDistributionFactor, this, IID_IDistributionFactorEvents, &m_DistributionFactorCookie);
   if (FAILED(hr))
      return hr;

   return S_OK;
}


STDMETHODIMP CDistributionFactorSegment::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Length;
	return S_OK;
}

STDMETHODIMP CDistributionFactorSegment::put_Length(Float64 newVal)
{
   if (newVal < -1.0)
      return E_INVALIDARG;

   if (newVal != m_Length)
   {
	   m_Length = newVal;
      Fire_OnDistributionFactorSegmentChanged();
   }

	return S_OK;
}

STDMETHODIMP CDistributionFactorSegment::get_DistributionFactor(IDistributionFactor **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_pDistributionFactor.CopyTo(pVal);
}

STDMETHODIMP CDistributionFactorSegment::putref_DistributionFactor(IDistributionFactor *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same 
   if ( m_pDistributionFactor.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old section if we had one
   HRESULT hr;
   if (!!m_pDistributionFactor)
   {
      hr = CrUnadvise(m_pDistributionFactor, this, IID_IDistributionFactorEvents, m_DistributionFactorCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new 
   m_pDistributionFactor = newVal;

   // establish cp with new 
   hr = CrAdvise(m_pDistributionFactor, this, IID_IDistributionFactorEvents, &m_DistributionFactorCookie);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   Fire_OnDistributionFactorSegmentChanged();

	return S_OK;
}

// IDistributionFactorEvents
STDMETHODIMP CDistributionFactorSegment::OnDistributionFactorChanged(IDistributionFactor* pdf)
{
   Fire_OnDistributionFactorSegmentChanged();
   return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CDistributionFactorSegment::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("DistributionFactorSegment"));
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
      hr = pload->get_Property(_bstr_t("Length"),&var);
      if (FAILED(hr))
         return hr;

      m_Length = var;
      var.Clear();


      hr = pload->get_Property(_bstr_t("DistributionFactor"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IDistributionFactor> pics;
      hr = _CopyVariantToInterface<IDistributionFactor>::copy(&pics, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_DistributionFactor(pics);
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

STDMETHODIMP CDistributionFactorSegment::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("DistributionFactorSegment"), MY_VER);
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Length"),_variant_t(m_Length));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("DistributionFactor"),_variant_t(m_pDistributionFactor));
      if (FAILED(hr))
         return hr;

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISegment);
   }

   return hr;
}

STDMETHODIMP CDistributionFactorSegment::Clone(IDistributionFactorSegment **pps)
{
   CHECK_RETOBJ(pps);

   // deep copy
   CComObject<CDistributionFactorSegment>* pclone;
   HRESULT hr = CComObject<CDistributionFactorSegment>::CreateInstance(&pclone);
   if (FAILED(hr))
      return hr;

   CComPtr<IDistributionFactorSegment> spseg(pclone); // to keep reference count exception safe

   pclone->m_Length = m_Length;

   CComPtr<IDistributionFactor> pcs;
   hr = m_pDistributionFactor->Clone(&pcs);
   if (FAILED(hr))
      return hr;

   hr = spseg->putref_DistributionFactor(pcs);
   if (FAILED(hr))
      return hr;

   return spseg.CopyTo(pps);
}
