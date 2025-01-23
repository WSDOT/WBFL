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

// LinearDistributionFactorSegment.cpp : Implementation of CLinearDistributionFactorSegment
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "LinearDistributionFactorSegment.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinearDistributionFactorSegment

STDMETHODIMP CLinearDistributionFactorSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILinearDistributionFactorSegment,
      &IID_IDistributionFactorSegment
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CLinearDistributionFactorSegment::FinalRelease()
{
   HRESULT hr;
   if (!!m_pStartDistributionFactor)
   {
      hr = CrUnadvise(m_pStartDistributionFactor, this, IID_IDistributionFactorEvents, m_StartDistributionFactorCookie);
      ATLASSERT(SUCCEEDED(hr));
   }

   if (!!m_pEndDistributionFactor)
   {
      hr = CrUnadvise(m_pEndDistributionFactor, this, IID_IDistributionFactorEvents, m_EndDistributionFactorCookie);
      ATLASSERT(SUCCEEDED(hr));
   }
}

HRESULT CLinearDistributionFactorSegment::FinalConstruct( )
{
   HRESULT hr;
   // create a default, empty df and set up connection point
   // up a connection point to it
   hr = m_pStartDistributionFactor.CoCreateInstance(CLSID_DistributionFactor);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_pStartDistributionFactor, this, IID_IDistributionFactorEvents, &m_StartDistributionFactorCookie);
   if (FAILED(hr))
      return hr;


   hr = m_pEndDistributionFactor.CoCreateInstance(CLSID_DistributionFactor);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_pEndDistributionFactor, this, IID_IDistributionFactorEvents, &m_EndDistributionFactorCookie);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

STDMETHODIMP CLinearDistributionFactorSegment::CreateDistributionFactor(Float64 dist,IDistributionFactor** pFactor)
{
   CHECK_RETVAL(pFactor);
   if ( dist < 0 )
   {
      if ( dist < -1.0 )
      {
         ATLASSERT(false);
         return E_INVALIDARG;
      }

      dist = -dist*m_Length;
   }

   Float64 K = dist/m_Length;

   if ( IsZero(K) )
   {
      // want LLDF at start... just return the start object
      return m_pStartDistributionFactor.CopyTo(pFactor);
   }
   else if ( IsEqual(K,1.0) )
   {
      // want LLDF at end... just return the end object
      return m_pEndDistributionFactor.CopyTo(pFactor);
   }
   else
   {
      // need to linearly interpolate
      CComPtr<IDistributionFactor> factor;
      factor.CoCreateInstance(CLSID_DistributionFactor);
      Float64 PMSgl_Start, PMMul_Start, NMSgl_Start, NMMul_Start, VSgl_Start, VMul_Start, DSgl_Start, DMul_Start, RSgl_Start, RMul_Start, TSgl_Start, TMul_Start, FatM_Start, FatV_Start, Pedes_Start;
      Float64 PMSgl_End,   PMMul_End,   NMSgl_End,   NMMul_End,   VSgl_End,   VMul_End,   DSgl_End,   DMul_End,   RSgl_End,   RMul_End,   TSgl_End,   TMul_End,   FatM_End,   FatV_End,   Pedes_End;
        
      m_pStartDistributionFactor->GetG( 
      &PMSgl_Start,
      &PMMul_Start,
      &NMSgl_Start,
      &NMMul_Start,
      &VSgl_Start,
      &VMul_Start,
      &DSgl_Start,
      &DMul_Start,
      &RSgl_Start,
      &RMul_Start,
      &TSgl_Start,
      &TMul_Start,
      &FatM_Start,
      &FatV_Start,
      &Pedes_Start);
        
      m_pEndDistributionFactor->GetG( 
      &PMSgl_End,
      &PMMul_End,
      &NMSgl_End,
      &NMMul_End,
      &VSgl_End,
      &VMul_End,
      &DSgl_End,
      &DMul_End,
      &RSgl_End,
      &RMul_End,
      &TSgl_End,
      &TMul_End,
      &FatM_End,
      &FatV_End,
      &Pedes_End);

      Float64 PMSgl = K*(PMSgl_End - PMSgl_Start) + PMSgl_Start;
      Float64 PMMul = K*(PMMul_End - PMMul_Start) + PMMul_Start;
      Float64 NMSgl = K*(NMSgl_End - NMSgl_Start) + NMSgl_Start;
      Float64 NMMul = K*(NMMul_End - NMMul_Start) + NMMul_Start;
      Float64 VSgl  = K*(VSgl_End  - VSgl_Start)  + VSgl_Start;
      Float64 VMul  = K*(VMul_End  - VMul_Start)  + VMul_Start;
      Float64 DSgl  = K*(DSgl_End  - DSgl_Start)  + DSgl_Start;
      Float64 DMul  = K*(DMul_End  - DMul_Start)  + DMul_Start;
      Float64 RSgl  = K*(RSgl_End  - RSgl_Start)  + RSgl_Start;
      Float64 RMul  = K*(RMul_End  - RMul_Start)  + RMul_Start;
      Float64 TSgl  = K*(TSgl_End  - TSgl_Start)  + TSgl_Start;
      Float64 TMul  = K*(TMul_End  - TMul_Start)  + TMul_Start;
      Float64 FatM  = K*(FatM_End  - FatM_Start)  + FatM_Start;
      Float64 FatV  = K*(FatV_End  - FatV_Start)  + FatV_Start;
      Float64 Pedes = K*(Pedes_End - Pedes_Start) + Pedes_Start;

      factor->SetG( 
      PMSgl,
      PMMul,
      NMSgl,
      NMMul,
      VSgl,
      VMul,
      DSgl,
      DMul,
      RSgl,
      RMul,
      TSgl,
      TMul,
      FatM,
      FatV,
      Pedes);

      return factor.CopyTo(pFactor);
   }

   return E_FAIL;
}


STDMETHODIMP CLinearDistributionFactorSegment::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Length;
	return S_OK;
}

STDMETHODIMP CLinearDistributionFactorSegment::put_Length(Float64 newVal)
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

STDMETHODIMP CLinearDistributionFactorSegment::get_DistributionFactor(IDistributionFactor **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_pStartDistributionFactor.CopyTo(pVal);
}

STDMETHODIMP CLinearDistributionFactorSegment::putref_DistributionFactor(IDistributionFactor *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same 
   if ( m_pStartDistributionFactor.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old section if we had one
   HRESULT hr;
   if (!!m_pStartDistributionFactor)
   {
      hr = CrUnadvise(m_pStartDistributionFactor, this, IID_IDistributionFactorEvents, m_StartDistributionFactorCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new 
   m_pStartDistributionFactor = newVal;

   // establish cp with new 
   hr = CrAdvise(m_pStartDistributionFactor, this, IID_IDistributionFactorEvents, &m_StartDistributionFactorCookie);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   Fire_OnDistributionFactorSegmentChanged();

	return S_OK;
}

STDMETHODIMP CLinearDistributionFactorSegment::get_EndDistributionFactor(IDistributionFactor **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_pEndDistributionFactor.CopyTo(pVal);
}

STDMETHODIMP CLinearDistributionFactorSegment::putref_EndDistributionFactor(IDistributionFactor *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same 
   if ( m_pEndDistributionFactor.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old section if we had one
   HRESULT hr;
   if (!!m_pEndDistributionFactor)
   {
      hr = CrUnadvise(m_pEndDistributionFactor, this, IID_IDistributionFactorEvents, m_EndDistributionFactorCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new 
   m_pEndDistributionFactor = newVal;

   // establish cp with new 
   hr = CrAdvise(m_pEndDistributionFactor, this, IID_IDistributionFactorEvents, &m_EndDistributionFactorCookie);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   Fire_OnDistributionFactorSegmentChanged();

	return S_OK;
}

// IDistributionFactorEvents
STDMETHODIMP CLinearDistributionFactorSegment::OnDistributionFactorChanged(IDistributionFactor* pdf)
{
   Fire_OnDistributionFactorSegmentChanged();
   return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CLinearDistributionFactorSegment::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("LinearDistributionFactorSegment"));
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


      hr = pload->get_Property(_bstr_t("StartDistributionFactor"),&var);
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


      hr = pload->get_Property(_bstr_t("EndDistributionFactor"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      pics.Release();
      hr = _CopyVariantToInterface<IDistributionFactor>::copy(&pics, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_EndDistributionFactor(pics);
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

STDMETHODIMP CLinearDistributionFactorSegment::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("LinearDistributionFactorSegment"), MY_VER);
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Length"),_variant_t(m_Length));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("StartDistributionFactor"),_variant_t(m_pStartDistributionFactor));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("EndDistributionFactor"),_variant_t(m_pEndDistributionFactor));
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

STDMETHODIMP CLinearDistributionFactorSegment::Clone(IDistributionFactorSegment **pps)
{
   CHECK_RETOBJ(pps);

   // deep copy
   CComObject<CLinearDistributionFactorSegment>* pclone;
   HRESULT hr = CComObject<CLinearDistributionFactorSegment>::CreateInstance(&pclone);
   if (FAILED(hr))
      return hr;

   CComPtr<ILinearDistributionFactorSegment> spseg(pclone); // to keep reference count exception safe

   pclone->m_Length = m_Length;

   CComPtr<IDistributionFactor> startClone;
   hr = m_pStartDistributionFactor->Clone(&startClone);
   if (FAILED(hr))
      return hr;

   hr = spseg->putref_DistributionFactor(startClone);
   if (FAILED(hr))
      return hr;

   CComPtr<IDistributionFactor> endClone;
   hr = m_pEndDistributionFactor->Clone(&endClone);
   if (FAILED(hr))
      return hr;

   hr = spseg->putref_EndDistributionFactor(endClone);
   if (FAILED(hr))
      return hr;

   CComQIPtr<IDistributionFactorSegment> dfSeg(spseg);
   return dfSeg.CopyTo(pps);
}
