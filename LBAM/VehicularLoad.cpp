///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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

// VehicularLoad.cpp : Implementation of CVehicularLoad
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "VehicularLoad.h"
#include "LBAMUtils.h"
#include "Axles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVehicularLoad

STDMETHODIMP CVehicularLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVehicularLoad
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CVehicularLoad::FinalConstruct( )
{
   HRESULT hr;
   // create a default, empty collection of stress points and set
   // up a connection point to it
//   CComObject<CAxles>* pa;
//   hr = CComObject<CAxles>::CreateInstance(&pa);
//   if (FAILED(hr))
//      return hr;

   hr = m_Axles.CoCreateInstance(CLSID_Axles);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_Axles, this, IID_IAxlesEvents, &m_AxlesCookie);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

void CVehicularLoad::FinalRelease()
{
   ATLASSERT(!!m_Axles);
   HRESULT hr = CrUnadvise(m_Axles, this, IID_IAxlesEvents, m_AxlesCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CVehicularLoad::get_Name(BSTR *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Name.Copy();

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_Name(BSTR newVal)
{
   CHECK_IN(newVal);

	if (newVal!=m_Name)
   {
      m_Name = newVal;
      Fire_OnVehicularLoadChanged(this, cgtDescription);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_Configuration(VehicularLoadConfigurationType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_VehicularLoadConfiguration;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_Configuration(VehicularLoadConfigurationType newVal)
{
   if ( (int)newVal<vlcDefault || (int)newVal>vlcSidewalkOnly )
      return E_INVALIDARG;

	if (newVal != m_VehicularLoadConfiguration)
   {
      m_VehicularLoadConfiguration = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_UseNotional(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_UseNotional;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_UseNotional(VARIANT_BOOL newVal)
{
   if (newVal!=VARIANT_TRUE && newVal!=VARIANT_FALSE)
      return E_INVALIDARG;

	if (newVal != m_UseNotional)
   {
      m_UseNotional = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_Applicability(LiveLoadApplicabilityType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_LiveLoadApplicability;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_Applicability(LiveLoadApplicabilityType newVal)
{
   if ( (int)newVal<llaEntireStructure || (int)newVal>llaNegMomentAndInteriorPierReaction )
      return E_INVALIDARG;

	if (newVal != m_LiveLoadApplicability)
   {
      m_LiveLoadApplicability = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_Axles(IAxles **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_Axles.CopyTo(pVal);
}

STDMETHODIMP CVehicularLoad::putref_Axles(IAxles *newVal)
{
   CHECK_IN(newVal);
	if (!m_Axles.IsEqualObject(newVal))
   {
      // first we must break our cp with old collection if we had one
      HRESULT hr;
      if (!!m_Axles)
      {
         hr = CrUnadvise(m_Axles, this, IID_IAxlesEvents, m_AxlesCookie);
         if (FAILED(hr))
            return hr;
      }

      // assign new collection
      m_Axles = newVal;

      // establish cp with new collection
      hr = CrAdvise(m_Axles, this, IID_IAxlesEvents, &m_AxlesCookie);
      if (FAILED(hr))
         return hr;

      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_VariableAxle(AxleIndexType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_VariableAxle;
	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_VariableAxle(AxleIndexType newVal)
{
	if (newVal != m_VariableAxle)
   {
      m_VariableAxle = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_VariableMaxSpacing(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_VariableMaxSpacing;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_VariableMaxSpacing(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

	if (newVal != m_VariableMaxSpacing)
   {
      m_VariableMaxSpacing = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_LaneLoad(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_LaneLoad;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_LaneLoad(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

	if (newVal != m_LaneLoad)
   {
      m_LaneLoad = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_SidewalkLoad(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_SidewalkLoad;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_SidewalkLoad(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

	if (newVal != m_SidewalkLoad)
   {
      m_SidewalkLoad = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_TruckFactor(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_TruckFactor;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_TruckFactor(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

	if (newVal != m_TruckFactor)
   {
      m_TruckFactor = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_LaneFactor(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_LaneFactor;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_LaneFactor(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

	if (newVal != m_LaneFactor)
   {
      m_LaneFactor = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_IMTruck(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_IMTruck;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_IMTruck(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

	if (newVal != m_IMTruck)
   {
      m_IMTruck = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_IMLane(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_IMLane;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_IMLane(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

	if (newVal != m_IMLane)
   {
      m_IMLane = newVal;
      Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   }

	return S_OK;
}


// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CVehicularLoad::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("VehicularLoad"));
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

      m_Name = var.bstrVal;

      var.Clear();
      hr = pload->get_Property(_bstr_t("VehicularLoadConfiguration"),&var);
      if (FAILED(hr))
         return hr;

      long lc = var;
      m_VehicularLoadConfiguration = (VehicularLoadConfigurationType)lc;

      var.Clear();
      hr = pload->get_Property(_bstr_t("UseNotional"),&var);
      if (FAILED(hr))
         return hr;

      m_UseNotional = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("LiveLoadApplicability"),&var);
      if (FAILED(hr))
         return hr;

      lc = var;
      if (lc == llaEntireStructure)
         m_LiveLoadApplicability = llaEntireStructure;
      else if (lc == llaContraflexure)
         m_LiveLoadApplicability = llaContraflexure;
      else if (lc == llaNegMomentAndInteriorPierReaction)
         m_LiveLoadApplicability = llaNegMomentAndInteriorPierReaction;
      else
      {
         ATLASSERT(false);
         return STRLOAD_E_INVALIDFORMAT;
      }

      var.Clear();
      hr = pload->get_Property(_bstr_t("VariableAxle"),&var);
      if (FAILED(hr))
         return hr;

      m_VariableAxle = VARIANT2INDEX(var);

      var.Clear();
      hr = pload->get_Property(_bstr_t("VariableMaxSpacing"),&var);
      if (FAILED(hr))
         return hr;

      m_VariableMaxSpacing = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("LaneLoad"),&var);
      if (FAILED(hr))
         return hr;

      m_LaneLoad = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("SidewalkLoad"),&var);
      if (FAILED(hr))
         return hr;

      m_SidewalkLoad = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("TruckFactor"),&var);
      if (FAILED(hr))
         return hr;

      m_TruckFactor = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("LaneFactor"),&var);
      if (FAILED(hr))
         return hr;

      m_LaneFactor = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("IMTruck"),&var);
      if (FAILED(hr))
         return hr;

      m_IMTruck = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("IMLane"),&var);
      if (FAILED(hr))
         return hr;

      m_IMLane = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("Axles"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IAxles> pisps;
      hr = _CopyVariantToInterface<IAxles>::copy(&pisps, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_Axles(pisps);
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

STDMETHODIMP CVehicularLoad::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("VehicularLoad"), MY_VER);
      hr = psave->put_Property(CComBSTR("Name"),_variant_t(m_Name));
      hr = psave->put_Property(CComBSTR("VehicularLoadConfiguration"),_variant_t((long)m_VehicularLoadConfiguration));
      hr = psave->put_Property(CComBSTR("UseNotional"),_variant_t(m_UseNotional));
      hr = psave->put_Property(CComBSTR("LiveLoadApplicability"),_variant_t((long)m_LiveLoadApplicability));
      hr = psave->put_Property(CComBSTR("VariableAxle"),_variant_t(m_VariableAxle));
      hr = psave->put_Property(CComBSTR("VariableMaxSpacing"),_variant_t(m_VariableMaxSpacing));
      hr = psave->put_Property(CComBSTR("LaneLoad"),_variant_t(m_LaneLoad));
      hr = psave->put_Property(CComBSTR("SidewalkLoad"),_variant_t(m_SidewalkLoad));
      hr = psave->put_Property(CComBSTR("TruckFactor"),_variant_t(m_TruckFactor));
      hr = psave->put_Property(CComBSTR("LaneFactor"),_variant_t(m_LaneFactor));
      hr = psave->put_Property(CComBSTR("IMTruck"),_variant_t(m_IMTruck));
      hr = psave->put_Property(CComBSTR("IMLane"),_variant_t(m_IMLane));
      hr = psave->put_Property(CComBSTR("Axles"),_variant_t(m_Axles));
      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IVehicularLoad);
   }

   return S_OK;
}

STDMETHODIMP CVehicularLoad::SumAxleWeights(Float64* pWeight)
{
   CHECK_RETVAL(pWeight);
   Float64 w = 0;

   CollectionIndexType nAxles;
   m_Axles->get_Count(&nAxles);
   for ( CollectionIndexType axleIdx = 0; axleIdx < nAxles; axleIdx++ )
   {
      CComPtr<IAxle> axle;
      m_Axles->get_Item(axleIdx,&axle);

      Float64 axle_weight;
      axle->get_Weight(&axle_weight);

      w += axle_weight;
   }

   *pWeight = w;
   return S_OK;
}

STDMETHODIMP CVehicularLoad::Clone(IVehicularLoad **clone)
{
   CHECK_RETOBJ(clone);

   // create a new stress point collection and fill it up
   CComObject<CVehicularLoad>* pnew;
   HRESULT hr = CComObject<CVehicularLoad>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IVehicularLoad> psvl(pnew); // for reference count

   pnew->m_IMLane                       = m_IMLane;
   pnew->m_IMTruck                      = m_IMTruck;
   pnew->m_LaneFactor                   = m_LaneFactor;
   pnew->m_TruckFactor                  = m_TruckFactor;
   pnew->m_SidewalkLoad                 = m_SidewalkLoad;
   pnew->m_LaneLoad                     = m_LaneLoad;
   pnew->m_VariableMaxSpacing           = m_VariableMaxSpacing;
   pnew->m_VariableAxle                 = m_VariableAxle;
   pnew->m_LiveLoadApplicability        = m_LiveLoadApplicability;
   pnew->m_UseNotional                  = m_UseNotional;
   pnew->m_VehicularLoadConfiguration   = m_VehicularLoadConfiguration;
   pnew->m_Name                         = m_Name;


   CComPtr<IAxles> psp;
   hr = m_Axles->Clone(&psp);
   if (FAILED(hr))
      return hr;

   hr = psvl->putref_Axles(psp);
   if (FAILED(hr))
      return hr;

   return psvl.CopyTo(clone);
}

STDMETHODIMP CVehicularLoad::OnAxlesChanged(IAxle* item)
{
   Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   return S_OK;
}
STDMETHODIMP CVehicularLoad::OnAxlesAdded(IAxle* item, AxleIndexType idx)
{
   Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   return S_OK;
}
STDMETHODIMP CVehicularLoad::OnAxlesBeforeRemove(IAxle* item, AxleIndexType idx)
{
   Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   return S_OK;
}
STDMETHODIMP CVehicularLoad::OnAxlesMoveTo(AxleIndexType from, AxleIndexType to)
{
   Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   return S_OK;
}
STDMETHODIMP CVehicularLoad::OnAxlesCopyTo(AxleIndexType from, AxleIndexType to)
{
   Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   return S_OK;
}
STDMETHODIMP CVehicularLoad::OnAxlesReverse()
{
   Fire_OnVehicularLoadChanged(this, cgtLiveLoad);
   return S_OK;
}
