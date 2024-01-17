///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
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

// LoadCombinationResultConfiguration.cpp : Implementation of CLoadCombinationResultConfiguration
#include "stdafx.h"
#include "WBFLLBAMLoadCombiner.h"
#include "LoadCombinationResultConfiguration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationResultConfiguration

STDMETHODIMP CLoadCombinationResultConfiguration::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadCombinationResultConfiguration
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLoadCombinationResultConfiguration::get_LoadCaseFactorCount(IndexType *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_LoadCaseFactors.size();

	return S_OK;
}

STDMETHODIMP CLoadCombinationResultConfiguration::GetLoadCaseFactor(IndexType index, BSTR *loadCase, Float64 *factor)
{
   CHECK_RETSTRING(loadCase);
   CHECK_RETVAL(factor);

	if (index < 0 || (IndexType)m_LoadCaseFactors.size() <= index)
      return E_INVALIDARG;

   LoadCaseFactor& rcf = m_LoadCaseFactors[index];

   rcf.m_LoadCaseName.CopyTo(loadCase);
   *factor = rcf.m_Factor;

	return S_OK;
}

STDMETHODIMP CLoadCombinationResultConfiguration::AddLoadCaseFactor(BSTR loadCase, Float64 factor)
{
   CHECK_IN(loadCase);

   m_LoadCaseFactors.emplace_back(loadCase, factor);

	return S_OK;
}

STDMETHODIMP CLoadCombinationResultConfiguration::get_LiveLoadFactor(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_LiveLoadFactor;

	return S_OK;
}

STDMETHODIMP CLoadCombinationResultConfiguration::put_LiveLoadFactor(Float64 newVal)
{
   m_LiveLoadFactor = newVal;

	return S_OK;
}

STDMETHODIMP CLoadCombinationResultConfiguration::AddLiveLoadConfiguration(ILiveLoadConfiguration *Config)
{
   // it is OK if this is a nullptr Config
   m_LLConfig.push_back(Config);

	return S_OK;
}

STDMETHODIMP CLoadCombinationResultConfiguration::GetLiveLoadConfiguration(IndexType index,ILiveLoadConfiguration **Config)
{
   if ( index < 0 || (IndexType)m_LLConfig.size() <= index )
      return E_INVALIDARG;

	CHECK_RETOBJ(Config);

   return m_LLConfig[index].CopyTo(Config);
}

STDMETHODIMP CLoadCombinationResultConfiguration::GetLiveLoadConfigurationCount(IndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_LLConfig.size();
   return S_OK;
}

STDMETHODIMP CLoadCombinationResultConfiguration::get_SummationType(ResultsSummationType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_ResultsSummationType;

	return S_OK;
}

STDMETHODIMP CLoadCombinationResultConfiguration::put_SummationType(ResultsSummationType newVal)
{
	m_ResultsSummationType = newVal;

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=2.0;

STDMETHODIMP CLoadCombinationResultConfiguration::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("LoadCombinationResultConfiguration"));
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
      hr = pload->get_Property(_bstr_t("LiveLoadFactor"),&var);
      if (FAILED(hr))
         return hr;

      m_LiveLoadFactor = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("ResultsSummationType"),&var);
      if (FAILED(hr))
         return hr;

      long ir = var;
      if (ir==rsIncremental)
      {
         m_ResultsSummationType = rsIncremental;
      }
      else if (ir==rsCumulative)
      {
         m_ResultsSummationType = rsCumulative;
      }
      else
      {
         ATLASSERT(false);
         return STRLOAD_E_INVALIDFORMAT;
      }

      if ( ver < 2 )
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("LiveLoadConfiguration"),&var);
         if (FAILED(hr))
            return hr;

         // get variant into more convenient form
         CComPtr<ILiveLoadConfiguration> pisps;
         hr = _CopyVariantToInterface<ILiveLoadConfiguration>::copy(&pisps, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         hr = AddLiveLoadConfiguration(pisps);
         if (FAILED(hr))
            return hr;
      }
      else
      {
         var.Clear();
         hr = pload->BeginUnit(_bstr_t("LiveLoadConfiguration"));
         if (FAILED(hr))
            return hr;

         var.Clear();
         hr = pload->get_Property(_bstr_t("Count"),&var);
         long count = var;
         for ( long i = 0; i < count; i++ )
         {
            var.Clear();
            hr = pload->get_Property(_bstr_t("LiveLoadConfiguration"),&var);
            if (FAILED(hr))
               return hr;

            // get variant into more convenient form
            CComPtr<ILiveLoadConfiguration> pisps;
            hr = _CopyVariantToInterface<ILiveLoadConfiguration>::copy(&pisps, &var);
            if (FAILED(hr))
               return STRLOAD_E_INVALIDFORMAT;

            hr = AddLiveLoadConfiguration(pisps);
            if (FAILED(hr))
               return hr;
         }

         VARIANT_BOOL eb;
         hr = pload->EndUnit(&eb);
         if (FAILED(hr))
            return hr;
      }

      var.Clear();
      hr = pload->get_Property(_bstr_t("LoadCaseFactorCount"),&var);
      if (FAILED(hr))
         return hr;

      long cnt = var;

      for (long i = 0; i<cnt; i++)
      {
         LoadCaseFactor lcf;

         var.Clear();
         hr = pload->get_Property(_bstr_t("LoadCaseName"),&var);
         if (FAILED(hr))
            return hr;

         lcf.m_LoadCaseName = (TCHAR*)_bstr_t(var);

         var.Clear();
         hr = pload->get_Property(_bstr_t("LoadCaseFactor"),&var);
         if (FAILED(hr))
            return hr;

         lcf.m_Factor = var;
      }
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CLoadCombinationResultConfiguration::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("LoadCombinationResultConfiguration"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("LiveLoadFactor"),_variant_t(m_LiveLoadFactor));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("ResultsSummationType"),_variant_t((long)m_ResultsSummationType));
      if (FAILED(hr))
         return hr;

      hr = psave->BeginUnit(CComBSTR("LiveLoadConfiguration"),1.0);
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Count"),_variant_t((long)m_LLConfig.size()));
      if (FAILED(hr))
         return hr;

      std::vector<CComPtr<ILiveLoadConfiguration> >::iterator iter;
      for ( iter = m_LLConfig.begin(); iter != m_LLConfig.end(); iter++ )
      {
         hr = psave->put_Property(CComBSTR("LiveLoadConfiguration"),_variant_t(*iter));
         if (FAILED(hr))
            return hr;
      }

      hr = psave->EndUnit();

      hr = psave->put_Property(CComBSTR("LoadCaseFactorCount"),_variant_t((long)m_LoadCaseFactors.size()));
      if (FAILED(hr))
         return hr;

      for (LcfIterator it=m_LoadCaseFactors.begin(); it!=m_LoadCaseFactors.end(); it++)
      {
         LoadCaseFactor& lcf = *it;

         hr = psave->put_Property(CComBSTR("LoadCaseName"),_variant_t(lcf.m_LoadCaseName));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("LoadCaseFactor"),_variant_t(lcf.m_Factor));
         if (FAILED(hr))
            return hr;
      }
   }

   hr = psave->EndUnit();
   return hr;
}



