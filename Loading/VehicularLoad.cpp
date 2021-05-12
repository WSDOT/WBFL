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

// VehicularLoad.cpp : Implementation of CVehicularLoad
#include "stdafx.h"
#include "WBFLLoading.h"
#include "VehicularLoad.h"
#include "LoadingUtils.h"
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
		&IID_ldIVehicularLoad
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

   hr = m_Axles.CoCreateInstance(CLSID_ldAxles);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_Axles, this, IID_ldIAxlesEvents, &m_AxlesCookie);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

void CVehicularLoad::FinalRelease()
{
   ATLASSERT(!!m_Axles);
   HRESULT hr = CrUnadvise(m_Axles, this, IID_ldIAxlesEvents, m_AxlesCookie);
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
      Fire_OnVehicularLoadChanged(this, ldcgDescription);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_Configuration(ldVehicularLoadConfigurationType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_VehicularLoadConfiguration;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_Configuration(ldVehicularLoadConfigurationType newVal)
{
   if ( (int)newVal<ldvcDefault || (int)newVal>ldvcSidewalkOnly )
      return E_INVALIDARG;

	if (newVal != m_VehicularLoadConfiguration)
   {
      m_VehicularLoadConfiguration = newVal;
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
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
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_Applicability(ldLiveLoadApplicabilityType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_LiveLoadApplicability;

	return S_OK;
}

STDMETHODIMP CVehicularLoad::put_Applicability(ldLiveLoadApplicabilityType newVal)
{
   if ( (int)newVal<ldlaEntireStructure || (int)newVal>ldlaContraflexure )
      return E_INVALIDARG;

	if (newVal != m_LiveLoadApplicability)
   {
      m_LiveLoadApplicability = newVal;
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CVehicularLoad::get_Axles(ldIAxles **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_Axles.CopyTo(pVal);
}

STDMETHODIMP CVehicularLoad::putref_Axles(ldIAxles *newVal)
{
   CHECK_IN(newVal);
	if (!m_Axles.IsEqualObject(newVal))
   {
      // first we must break our cp with old collection if we had one
      HRESULT hr;
      if (!!m_Axles)
      {
         hr = CrUnadvise(m_Axles, this, IID_ldIAxlesEvents, m_AxlesCookie);
         if (FAILED(hr))
            return hr;
      }

      // assign new collection
      m_Axles = newVal;

      // establish cp with new collection
      hr = CrAdvise(m_Axles, this, IID_ldIAxlesEvents, &m_AxlesCookie);
      if (FAILED(hr))
         return hr;

      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
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
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
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
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
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
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
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
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
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
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
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
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
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
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
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
      Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
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
      
      CComVariant var;
      hr = pload->get_Property(CComBSTR("Name"),&var);
      if (FAILED(hr))
         return hr;

      m_Name = var.bstrVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("VehicularLoadConfiguration"),&var);
      if (FAILED(hr))
         return hr;

      m_VehicularLoadConfiguration = (ldVehicularLoadConfigurationType)var.lVal;

      switch(m_VehicularLoadConfiguration)
      {
      case ldvcDefault:
      case ldvcTruckPlusLane:
      case ldvcTruckLaneEnvelope:
      case ldvcTruckOnly:
      case ldvcLaneOnly:
         break; // all drop throught... all legal values

      default:
         return STRLOAD_E_INVALIDFORMAT;
      }

      var.Clear();
      hr = pload->get_Property(CComBSTR("UseNotional"),&var);
      if (FAILED(hr))
         return hr;

      m_UseNotional = var.boolVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("LiveLoadApplicability"),&var);
      if (FAILED(hr))
         return hr;

      m_LiveLoadApplicability = (ldLiveLoadApplicabilityType)var.lVal;
      switch(m_LiveLoadApplicability)
      {
      case ldlaEntireStructure:
      case ldlaContraflexure:
         break;

      default:
         return STRLOAD_E_INVALIDFORMAT;
      }

      var.Clear();
      hr = pload->get_Property(CComBSTR("VariableAxle"),&var);
      if (FAILED(hr))
         return hr;

      m_VariableAxle = var.iVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("VariableMaxSpacing"),&var);
      if (FAILED(hr))
         return hr;

      m_VariableMaxSpacing = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("LaneLoad"),&var);
      if (FAILED(hr))
         return hr;

      m_LaneLoad = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("SidewalkLoad"),&var);
      if (FAILED(hr))
         return hr;

      m_SidewalkLoad = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("TruckFactor"),&var);
      if (FAILED(hr))
         return hr;

      m_TruckFactor = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("LaneFactor"),&var);
      if (FAILED(hr))
         return hr;

      m_LaneFactor = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("IMTruck"),&var);
      if (FAILED(hr))
         return hr;

      m_IMTruck = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("IMLane"),&var);
      if (FAILED(hr))
         return hr;

      m_IMLane = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("Axles"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ldIAxles> pisps;
      hr = _CopyVariantToInterface<ldIAxles>::copy(&pisps, &var);
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
      hr = psave->put_Property(CComBSTR("Name"),CComVariant(m_Name));
      hr = psave->put_Property(CComBSTR("VehicularLoadConfiguration"),CComVariant(m_VehicularLoadConfiguration));
      hr = psave->put_Property(CComBSTR("UseNotional"),CComVariant(m_UseNotional));
      hr = psave->put_Property(CComBSTR("LiveLoadApplicability"),CComVariant(m_LiveLoadApplicability));
      hr = psave->put_Property(CComBSTR("VariableAxle"),CComVariant(m_VariableAxle));
      hr = psave->put_Property(CComBSTR("VariableMaxSpacing"),CComVariant(m_VariableMaxSpacing));
      hr = psave->put_Property(CComBSTR("LaneLoad"),CComVariant(m_LaneLoad));
      hr = psave->put_Property(CComBSTR("SidewalkLoad"),CComVariant(m_SidewalkLoad));
      hr = psave->put_Property(CComBSTR("TruckFactor"),CComVariant(m_TruckFactor));
      hr = psave->put_Property(CComBSTR("LaneFactor"),CComVariant(m_LaneFactor));
      hr = psave->put_Property(CComBSTR("IMTruck"),CComVariant(m_IMTruck));
      hr = psave->put_Property(CComBSTR("IMLane"),CComVariant(m_IMLane));
      hr = psave->put_Property(CComBSTR("Axles"),CComVariant(m_Axles));
      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ldIVehicularLoad);
   }

   return S_OK;
}


STDMETHODIMP CVehicularLoad::Clone(ldIVehicularLoad **clone)
{
   CHECK_RETOBJ(clone);

   // create a new stress point collection and fill it up
   CComObject<CVehicularLoad>* pnew;
   HRESULT hr = CComObject<CVehicularLoad>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ldIVehicularLoad> psvl(pnew); // for reference count

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


   CComPtr<ldIAxles> psp;
   hr = m_Axles->Clone(&psp);
   if (FAILED(hr))
      return hr;

   hr = psvl->putref_Axles(psp);
   if (FAILED(hr))
      return hr;

   return psvl.CopyTo(clone);
}

STDMETHODIMP CVehicularLoad::OnAxlesChanged(ldIAxle* item)
{
   Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
   return S_OK;
}
STDMETHODIMP CVehicularLoad::OnAxlesAdded(ldIAxle* item, AxleIndexType id)
{
   Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
   return S_OK;
}
STDMETHODIMP CVehicularLoad::OnAxlesBeforeRemove(ldIAxle* item, AxleIndexType id)
{
   Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
   return S_OK;
}
STDMETHODIMP CVehicularLoad::OnAxlesMoveTo(AxleIndexType from, AxleIndexType to)
{
   Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
   return S_OK;
}
STDMETHODIMP CVehicularLoad::OnAxlesCopyTo(AxleIndexType from, AxleIndexType to)
{
   Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
   return S_OK;
}
STDMETHODIMP CVehicularLoad::OnAxlesReverse()
{
   Fire_OnVehicularLoadChanged(this, ldcgLiveLoad);
   return S_OK;
}
