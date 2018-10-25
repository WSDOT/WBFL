///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// LiveLoadConfiguration.cpp : Implementation of CLiveLoadConfiguration
#include "stdafx.h"
#include "WBFLLBAMLiveLoader.h"
#include "LiveLoadConfiguration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadConfiguration

STDMETHODIMP CLiveLoadConfiguration::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILiveLoadConfiguration
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CLiveLoadConfiguration::FinalConstruct()
{
   HRESULT hr = m_AxleConfig.CoCreateInstance(CLSID_IndexArray);
   ATLASSERT(SUCCEEDED(hr));
   return hr;
}

STDMETHODIMP CLiveLoadConfiguration::get_LiveLoadModel(LiveLoadModelType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_LiveLoadModelType;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_LiveLoadModel(LiveLoadModelType newVal)
{
	if (m_LiveLoadModelType != newVal)
   {
   	m_LiveLoadModelType = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_VehicleIndex(VehicleIndexType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_VehicleIndex;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_VehicleIndex(VehicleIndexType newVal)
{
   if (newVal == INVALID_INDEX)
   {
      return E_INVALIDARG;
   }

	if (m_VehicleIndex != newVal)
   {
   	m_VehicleIndex = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_VehicularLoadConfiguration(VehicularLoadConfigurationType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_VehicularLoadConfiguration;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_VehicularLoadConfiguration(VehicularLoadConfigurationType newVal)
{
	if (m_VehicularLoadConfiguration != newVal)
   {
   	m_VehicularLoadConfiguration = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }

	return S_OK;
}


STDMETHODIMP CLiveLoadConfiguration::get_TruckPosition(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_TruckPosition;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_TruckPosition(Float64 newVal)
{
	if (m_TruckPosition != newVal)
   {
   	m_TruckPosition = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_PivotAxleIndex(AxleIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_PivotAxleIndex;
   return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_PivotAxleIndex(AxleIndexType newVal)
{
	if (m_PivotAxleIndex != newVal)
   {
   	m_PivotAxleIndex = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_TruckDirection(TruckDirectionType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_TruckDirection;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_TruckDirection(TruckDirectionType newVal)
{
   if (m_TruckDirection != newVal)
   {
	   m_TruckDirection = newVal;
      Fire_OnLiveLoadConfigurationChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_DoApplyImpact(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_DoApplyImpact;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_DoApplyImpact(VARIANT_BOOL newVal)
{
   if (newVal != m_DoApplyImpact)
   {
	   m_DoApplyImpact = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }
	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_VariableSpacing(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_VariableSpacing;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_VariableSpacing(Float64 newVal)
{
   if (newVal<0.0)
      return E_INVALIDARG;

   if (newVal!=m_VariableSpacing)
   {
	   m_VariableSpacing = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }
	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_AxleConfig(IIndexArray* *pVal)
{
   CHECK_RETOBJ(pVal);

   return m_AxleConfig.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_AxleConfig(IIndexArray* newVal)
{
   CHECK_IN(newVal);

   m_AxleConfig = newVal;

   Fire_OnLiveLoadConfigurationChanged(this);

   return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_IsApplicable(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_IsApplicable;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_IsApplicable(VARIANT_BOOL newVal)
{
   if (newVal != m_IsApplicable)
   {
	   m_IsApplicable = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_DistributionFactorType(DistributionFactorType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_DistributionFactorType;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_DistributionFactorType(DistributionFactorType newVal)
{
	if (m_DistributionFactorType != newVal)
   {
	   m_DistributionFactorType = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_ForceEffect(ForceEffectType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_ForceEffectType;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_ForceEffect(ForceEffectType newVal)
{
	if (m_ForceEffectType != newVal)
   {
   	m_ForceEffectType = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::get_Optimization(OptimizationType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_OptimizationType;

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::put_Optimization(OptimizationType newVal)
{
	if (m_OptimizationType != newVal)
   {
   	m_OptimizationType = newVal;

      Fire_OnLiveLoadConfigurationChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::Clone(ILiveLoadConfiguration* *pClone)
{
   CHECK_RETOBJ(pClone);

   HRESULT hr;
   CComObject<CLiveLoadConfiguration>* cclone;
   hr = CComObject<CLiveLoadConfiguration>::CreateInstance(&cclone);
   if (FAILED(hr))
      return hr;

   CComPtr<ILiveLoadConfiguration> clone(cclone);

   cclone->m_VehicleIndex               = m_VehicleIndex;
   cclone->m_LiveLoadModelType          = m_LiveLoadModelType;

   m_AxleConfig.CopyTo( &(cclone->m_AxleConfig) );
   cclone->m_VariableSpacing            = m_VariableSpacing;
   cclone->m_TruckDirection             = m_TruckDirection;
   cclone->m_TruckPosition              = m_TruckPosition;
   cclone->m_DoApplyImpact              = m_DoApplyImpact;
   cclone->m_IsApplicable               = m_IsApplicable; 
   cclone->m_VehicularLoadConfiguration = m_VehicularLoadConfiguration;
   cclone->m_DistributionFactorType     = m_DistributionFactorType;
   cclone->m_ForceEffectType            = m_ForceEffectType;
   cclone->m_OptimizationType           = m_OptimizationType;
   cclone->m_PivotAxleIndex             = m_PivotAxleIndex;

   return clone.CopyTo(pClone);
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CLiveLoadConfiguration::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("LiveLoadConfiguration"));
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
      hr = pload->get_Property(_bstr_t("VehicleIndex"),&var);
      if (FAILED(hr))
         return hr;

      m_VehicleIndex = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("LiveLoadModelType"),&var);
      if (FAILED(hr))
         return hr;

      m_LiveLoadModelType = (LiveLoadModelType)(var.lVal);

      hr = pload->BeginUnit(CComBSTR("AxleConfig"));
      if (FAILED(hr))
         return hr;

      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("AxleConfigCount"),&var);
         if (FAILED(hr))
            return hr;

         CollectionIndexType cnt = var;

         m_AxleConfig->Clear();
         m_AxleConfig->Reserve(cnt);

         for (CollectionIndexType i=0; i<cnt; i++)
         {
            var.Clear();
            hr = pload->get_Property(_bstr_t("Axle"),&var);
            if (FAILED(hr))
               return hr;

            AxleIndexType axl = var;
            m_AxleConfig->Add(axl);
         }
      }

      VARIANT_BOOL eb;
      hr = pload->EndUnit(&eb);
      if (FAILED(hr))
         return hr;

      if (eb!=VARIANT_TRUE)
         return STRLOAD_E_INVALIDFORMAT;

      var.Clear();
      hr = pload->get_Property(_bstr_t("VariableSpacing"),&var);
      if (FAILED(hr))
         return hr;

      m_VariableSpacing = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("TruckDirection"),&var);
      if (FAILED(hr))
         return hr;

      m_TruckDirection = (TruckDirectionType)var.lVal;

      var.Clear();
      hr = pload->get_Property(_bstr_t("PivotAxleIndex"),&var);
      if (FAILED(hr))
         return hr;

      m_PivotAxleIndex = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("TruckPosition"),&var);
      if (FAILED(hr))
         return hr;

      m_TruckPosition = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("DoApplyImpact"),&var);
      if (FAILED(hr))
         return hr;

      if ((long)var == VARIANT_FALSE)
         m_DoApplyImpact = VARIANT_FALSE;
      else
         m_DoApplyImpact = VARIANT_TRUE;

      var.Clear();
      hr = pload->get_Property(_bstr_t("IsApplicable"),&var);
      if (FAILED(hr))
         return hr;

      if ((long)var == VARIANT_FALSE)
         m_IsApplicable = VARIANT_FALSE;
      else
         m_IsApplicable = VARIANT_TRUE;

      var.Clear();
      hr = pload->get_Property(_bstr_t("VehicularLoadConfiguration"),&var);
      if (FAILED(hr))
         return hr;

      m_VehicularLoadConfiguration = (VehicularLoadConfigurationType)var.lVal;
      
      var.Clear();
      hr = pload->get_Property(_bstr_t("DistributionFactorType"),&var);
      if (FAILED(hr))
         return hr;

      m_DistributionFactorType = (DistributionFactorType)var.lVal;

      var.Clear();
      hr = pload->get_Property(_bstr_t("ForceEffectType"),&var);
      if (FAILED(hr))
         return hr;

      m_ForceEffectType = (ForceEffectType)var.lVal;

      var.Clear();
      hr = pload->get_Property(_bstr_t("OptimizationType"),&var);
      if (FAILED(hr))
         return hr;

      m_OptimizationType = (OptimizationType)var.lVal;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb == VARIANT_FALSE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CLiveLoadConfiguration::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("LiveLoadConfiguration"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("VehicleIndex"),_variant_t(m_VehicleIndex));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("LiveLoadModelType"),_variant_t((long)m_LiveLoadModelType));
      if (FAILED(hr))
         return hr;

      hr = psave->BeginUnit(CComBSTR("AxleConfig"), MY_VER);
      if (FAILED(hr))
         return hr;

      {
         AxleIndexType nAxles;
         hr = m_AxleConfig->get_Count(&nAxles);
         hr = psave->put_Property(CComBSTR("AxleConfigCount"),_variant_t(nAxles));
         if (FAILED(hr))
            return hr;

         for (AxleIndexType axleIdx = 0; axleIdx < nAxles; axleIdx++)
         {
            AxleIndexType appliedAxleIdx;
            hr = m_AxleConfig->get_Item(axleIdx, &appliedAxleIdx);
            hr = psave->put_Property(CComBSTR("Axle"),_variant_t(appliedAxleIdx));
            if (FAILED(hr))
               return hr;
         }
      }

      hr = psave->EndUnit();
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("VariableSpacing"),_variant_t(m_VariableSpacing));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("TruckDirection"),_variant_t((long)m_TruckDirection));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("PivotAxleIndex"),_variant_t((long)m_PivotAxleIndex));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("TruckPosition"),_variant_t(m_TruckPosition));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("DoApplyImpact"),_variant_t((long)m_DoApplyImpact));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("IsApplicable"),_variant_t((long)m_IsApplicable));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("VehicularLoadConfiguration"),_variant_t((long)m_VehicularLoadConfiguration));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("DistributionFactorType"),_variant_t((long)m_DistributionFactorType));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("ForceEffectType"),_variant_t((long)m_ForceEffectType));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("OptimizationType"),_variant_t((long)m_OptimizationType));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   return hr;
}



