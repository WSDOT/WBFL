///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2015  Washington State Department of Transportation
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

// CrossSection.cpp : Implementation of CCrossSection
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "CrossSection.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCrossSection

STDMETHODIMP CSegmentCrossSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISegmentCrossSection
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSegmentCrossSection::FinalConstruct( )
{
   HRESULT hr;
   // create a default, empty collection of stress points and set
   // up a connection point to it
   hr = m_StressPoints.CoCreateInstance(CLSID_StressPoints);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_StressPoints, this, IID_IStressPointsEvents, &m_StressPointsCookie);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

void CSegmentCrossSection::FinalRelease()
{
   ATLASSERT(!!m_StressPoints);
   HRESULT hr = CrUnadvise(m_StressPoints, this, IID_IStressPointsEvents, m_StressPointsCookie);
   ATLASSERT(SUCCEEDED(hr));
}


STDMETHODIMP CSegmentCrossSection::get_Depth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Depth;

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::put_Depth(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

   if (newVal != m_Depth)
   {
   	m_Depth = newVal;
      Fire_OnSegmentCrossSectionChanged(this, cgtStiffness);
   }

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::get_EAForce(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_EAForce;

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::put_EAForce(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

   if (newVal != m_EAForce)
   {
	   m_EAForce = newVal;
      Fire_OnSegmentCrossSectionChanged(this, cgtStiffness);
   }

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::get_EIForce(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_EIForce;

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::put_EIForce(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

   if (newVal != m_EIForce)
   {
	   m_EIForce = newVal;
      Fire_OnSegmentCrossSectionChanged(this, cgtStiffness);
   }

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::get_EADefl(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_EADefl;

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::put_EADefl(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

   if (newVal != m_EADefl)
   {
	   m_EADefl = newVal;
      Fire_OnSegmentCrossSectionChanged(this, cgtStiffness);
   }

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::get_EIDefl(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_EIDefl;

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::put_EIDefl(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

   if (newVal != m_EIDefl)
   {
	   m_EIDefl = newVal;
      Fire_OnSegmentCrossSectionChanged(this, cgtStiffness);
   }

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::get_ThermalCoeff(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Thermal;

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::put_ThermalCoeff(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

   if (newVal != m_Thermal)
   {
	   m_Thermal = newVal;
      Fire_OnSegmentCrossSectionChanged(this, cgtStiffness);
   }

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::get_StressPoints(IStressPoints **pVal)
{
   CHECK_RETOBJ(pVal);

	return m_StressPoints.CopyTo(pVal);
}

STDMETHODIMP CSegmentCrossSection::putref_StressPoints(IStressPoints *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_StressPoints.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   hr = CrUnadvise(m_StressPoints, this, IID_IStressPointsEvents, m_StressPointsCookie);
   if (FAILED(hr))
      return hr;

   // assign new collection
   m_StressPoints = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_StressPoints, this, IID_IStressPointsEvents, &m_StressPointsCookie);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   Fire_OnSegmentCrossSectionChanged(this, cgtStress);

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::SetStiffness(Float64 EAForce, Float64 EIForce, Float64 EADefl, Float64 EIDefl)
{
	if (EAForce<0.0)
      return E_INVALIDARG;
	if (EIForce<0.0)
      return E_INVALIDARG;
	if (EADefl<0.0)
      return E_INVALIDARG;
	if (EIDefl<0.0)
      return E_INVALIDARG;

   bool c = false;

   if (m_EAForce != EAForce)
   {
      m_EAForce = EAForce;
      c = true;
   }

   if (m_EIForce != EIForce)
   {
      m_EIForce = EIForce;
      c = true;
   }

   if (m_EADefl != EADefl)
   {
      m_EADefl  = EADefl;
      c = true;
   }

   if (m_EIDefl != EIDefl)
   {
      m_EIDefl  = EIDefl;
      c = true;
   }

   if (c)
      Fire_OnSegmentCrossSectionChanged(this, cgtStiffness);

	return S_OK;
}

STDMETHODIMP CSegmentCrossSection::GetStiffness(Float64 *EAForce, Float64 *EIForce, Float64 *EADefl, Float64 *EIDefl)
{
   CHECK_RETVAL(EAForce);
   CHECK_RETVAL(EIForce);
   CHECK_RETVAL(EADefl);
   CHECK_RETVAL(EIDefl);

   *EAForce = m_EAForce;
   *EIForce = m_EIForce;
   *EADefl  = m_EADefl;
   *EIDefl  = m_EIDefl;

	return S_OK;
}

HRESULT CSegmentCrossSection::OnStressPointsChanged(CollectionIndexType index)
{
   Fire_OnSegmentCrossSectionChanged(this, cgtStress);
   return S_OK;
}

HRESULT CSegmentCrossSection::OnStressPointsAdded(CollectionIndexType index)
{
   Fire_OnSegmentCrossSectionChanged(this, cgtStress);
   return S_OK;
}

HRESULT CSegmentCrossSection::OnStressPointsRemoved(CollectionIndexType index)
{
   Fire_OnSegmentCrossSectionChanged(this, cgtStress);
   return S_OK;
}


// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CSegmentCrossSection::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("SegmentCrossSection"));
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
      hr = pload->get_Property(_bstr_t("EAForce"),&var);
      if (FAILED(hr))
         return hr;

      m_EAForce = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("EIForce"),&var);
      if (FAILED(hr))
         return hr;

      m_EIForce = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("EADefl"),&var);
      if (FAILED(hr))
         return hr;

      m_EADefl = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("EIDefl"),&var);
      if (FAILED(hr))
         return hr;

      m_EIDefl = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("Thermal"),&var);
      if (FAILED(hr))
         return hr;

      m_Thermal = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("Depth"),&var);
      if (FAILED(hr))
         return hr;

      m_Depth = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("StressPoints"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IStressPoints> pisps;
      hr = _CopyVariantToInterface<IStressPoints>::copy(&pisps, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_StressPoints(pisps);
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

STDMETHODIMP CSegmentCrossSection::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("SegmentCrossSection"), MY_VER);
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("EAForce"),_variant_t(m_EAForce));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("EIForce"),_variant_t(m_EIForce));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("EADefl"),_variant_t(m_EADefl));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("EIDefl"),_variant_t(m_EIDefl));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Thermal"),_variant_t(m_Thermal));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Depth"),_variant_t(m_Depth));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("StressPoints"),_variant_t(m_StressPoints));
      if (FAILED(hr))
         return hr;

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISegmentCrossSection);
   }

   return hr;
}

STDMETHODIMP CSegmentCrossSection::Clone(ISegmentCrossSection **ppCS)
{
   CHECK_RETOBJ(ppCS);

   // create a new stress point collection and fill it up
   CComObject<CSegmentCrossSection>* pnew;
   HRESULT hr = CComObject<CSegmentCrossSection>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ISegmentCrossSection> pscs(pnew); // for reference count

   pnew->m_Depth   = m_Depth;
   pnew->m_EADefl  = m_EADefl;
   pnew->m_EAForce = m_EAForce;
   pnew->m_EIDefl  = m_EIDefl;
   pnew->m_EIForce = m_EIForce;
   pnew->m_Thermal = m_Thermal;

   CComPtr<IStressPoints> psp;
   hr = m_StressPoints->Clone(&psp);
   if (FAILED(hr))
      return hr;

   hr = pscs->putref_StressPoints(psp);
   if (FAILED(hr))
      return hr;

   return pscs.CopyTo(ppCS);
}
