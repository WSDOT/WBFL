///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2012  Washington State Department of Transportation
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

// Span.cpp : Implementation of CSpan
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "Span.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpan

STDMETHODIMP CSpan::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISpan
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSpan::FinalConstruct( )
{
   HRESULT hr;
   // create a default, empty collection of stress points and set
   // up a connection point to it
   hr = m_TemporarySupports.CoCreateInstance(CLSID_TemporarySupports);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_TemporarySupports, this, IID_ITemporarySupportsEvents, &m_TemporarySupportsCookie);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

void CSpan::FinalRelease()
{
   ATLASSERT(!!m_TemporarySupports);
   HRESULT hr = CrUnadvise(m_TemporarySupports, this, IID_ITemporarySupportsEvents, m_TemporarySupportsCookie);
   ATLASSERT(SUCCEEDED(hr));
}



STDMETHODIMP CSpan::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Length;

	return S_OK;
}

STDMETHODIMP CSpan::put_Length(Float64 newVal)
{
   if (newVal<=0.0)
      return E_INVALIDARG;

   if (newVal != m_Length)
   {
   	m_Length = newVal;
      Fire_OnSpanChanged(this, CComBSTR("*"), cgtStiffness);
   }

	return S_OK;
}

STDMETHODIMP CSpan::get_TemporarySupports(ITemporarySupports **pVal)
{
   CHECK_RETOBJ(pVal);

	return m_TemporarySupports.CopyTo(pVal);
}

STDMETHODIMP CSpan::putref_TemporarySupports(ITemporarySupports *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_TemporarySupports.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_TemporarySupports)
   {
      hr = CrUnadvise(m_TemporarySupports, this, IID_ITemporarySupportsEvents, m_TemporarySupportsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_TemporarySupports = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_TemporarySupports, this, IID_ITemporarySupportsEvents, &m_TemporarySupportsCookie);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   Fire_OnSpanChanged(this, CComBSTR("*"), cgtStress);

	return S_OK;
}

STDMETHODIMP CSpan::Clone(ISpan **clone)
{
   CHECK_RETOBJ(clone);

   // create a new stress point collection and fill it up
   CComObject<CSpan>* pnew;
   HRESULT hr = CComObject<CSpan>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ISpan> pscs(pnew); // for reference count

   pnew->m_Length               = m_Length;

   pnew->m_LoadModifierHelper  = m_LoadModifierHelper;

   CComPtr<ITemporarySupports> psp;
   hr = m_TemporarySupports->Clone(&psp);
   if (FAILED(hr))
      return hr;

   hr = pscs->putref_TemporarySupports(psp);
   if (FAILED(hr))
      return hr;

   return pscs.CopyTo(clone);
}

STDMETHODIMP CSpan::GetLoadModifier(LoadCombinationType type, Float64 *minVal, Float64 *maxVal)
{
	return m_LoadModifierHelper.GetLoadModifier(type, minVal, maxVal);
}

STDMETHODIMP CSpan::SetLoadModifier(LoadCombinationType type, Float64 minVal, Float64 maxVal)
{
   bool did_fire;
   HRESULT hr = m_LoadModifierHelper.SetLoadModifier(type, minVal, maxVal, &did_fire);
   if (FAILED(hr))
      return hr;

   if (did_fire)
      Fire_OnSpanChanged(this, CComBSTR("*"), cgtCombination);

	return S_OK;
}

HRESULT CSpan::OnTemporarySupportsChanged(ITemporarySupport* ps, BSTR stage, ChangeType change)
{
   Fire_OnSpanChanged(this, stage, change);
   return S_OK;
}

HRESULT CSpan::OnTemporarySupportsAdded(ITemporarySupport* ps,SupportIndexType index)
{
   Fire_OnSpanChanged(this, CComBSTR("*"), cgtStiffness);
   return S_OK;
}

HRESULT CSpan::OnTemporarySupportsBeforeRemove(ITemporarySupport* ps,SupportIndexType index)
{
   Fire_OnSpanChanged(this, CComBSTR("*"), cgtStiffness);
   return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CSpan::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("Span"));
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

      // LoadModifiers
      hr = m_LoadModifierHelper.Load(pload);
      if (FAILED(hr))
         return hr;

      hr = pload->get_Property(_bstr_t("TemporarySupports"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ITemporarySupports> pisps;
      hr = _CopyVariantToInterface<ITemporarySupports>::copy(&pisps, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_TemporarySupports(pisps);
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

STDMETHODIMP CSpan::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("Span"), MY_VER);
      hr = psave->put_Property(CComBSTR("Length"),_variant_t(m_Length));
      hr = m_LoadModifierHelper.Save(psave);
      hr = psave->put_Property(CComBSTR("TemporarySupports"),_variant_t(m_TemporarySupports));
      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISpan);
   }

   return S_OK;
}

STDMETHODIMP CSpan::RemoveStage(BSTR stage)
{
   CHECK_IN(stage);

	// only stage dependent data is for temporary supports
   SupportIndexType cnt;
   HRESULT hr = m_TemporarySupports->get_Count(&cnt);
   if (FAILED(hr))
      return hr;

   for (SupportIndexType i=0; i<cnt; i++)
   {
      CComPtr<ITemporarySupport> its;
      hr = m_TemporarySupports->get_Item(i, &its);
      if (FAILED(hr))
         return hr;

      hr = its->RemoveStage(stage);
      if (FAILED(hr))
         return hr;
   }

	return S_OK;
}
