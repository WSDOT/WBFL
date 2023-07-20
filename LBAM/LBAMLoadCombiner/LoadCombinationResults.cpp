///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2023  Washington State Department of Transportation
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

// LoadCombinationResults.cpp : Implementation of CLoadCombinationResults
#include "stdafx.h"
#include "WBFLLBAMLoadCombiner.h"
#include "LoadCombinationResults.h"

#include "LoadCombinationResultConfiguration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationResults

STDMETHODIMP CLoadCombinationResults::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadCombinationResults
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLoadCombinationResults::Clear()
{
	m_ComboResults.clear();

	return S_OK;
}

STDMETHODIMP CLoadCombinationResults::Reserve(IndexType size)
{
   if (size<0)
      return E_INVALIDARG;

   m_ComboResults.reserve(size);

	return S_OK;
}

STDMETHODIMP CLoadCombinationResults::get_Count(IndexType *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_ComboResults.size();

	return S_OK;
}

STDMETHODIMP CLoadCombinationResults::Add(Float64 Result, ILoadCombinationResultConfiguration *Config)
{

   m_ComboResults.emplace_back(Result, Config);

	return S_OK;
}

STDMETHODIMP CLoadCombinationResults::SetResult(IndexType index, Float64 Result, ILoadCombinationResultConfiguration *Config)
{

   if ( index < 0 || (IndexType)m_ComboResults.size() <= index)
      return E_INVALIDARG;

   ComboRes& rres = m_ComboResults[index];

   rres.m_Result  = Result;
   rres.m_Config  = Config;

	return S_OK;
}

STDMETHODIMP CLoadCombinationResults::GetResult(IndexType index, Float64* Result, ILoadCombinationResultConfiguration **Config)
{
   if ( index < 0 || (IndexType)m_ComboResults.size() <= index)
      return E_INVALIDARG;

	CHECK_RETVAL(Result);

   ComboRes& rres = m_ComboResults[index];

   *Result  = rres.m_Result;

   if (Config!=nullptr)
   {
      return rres.m_Config.CopyTo(Config);
   }

   return S_OK;
}


HRESULT CLoadCombinationResults::AllocateResults(IndexType size, bool createConfig, ResultsSummationType summ)
{
   HRESULT hr;

   if (size<0)
   {
      ATLASSERT(false);
      return E_INVALIDARG;
   }

   ATLASSERT(m_ComboResults.empty()); // should only be allocating once

   m_ComboResults.reserve(size);

   for (IndexType i = 0; i<size; i++)
   {
      CComPtr<ILoadCombinationResultConfiguration> config;

      // create configuration object only if asked
      if (createConfig)
      {
         CComObject<CLoadCombinationResultConfiguration>* coconfig;
         hr = CComObject<CLoadCombinationResultConfiguration>::CreateInstance(&coconfig);
         if (FAILED(hr))
            return hr;

         hr = coconfig->put_SummationType(summ);
         if (FAILED(hr))
            return hr;

         config = coconfig;

      }

      // add empty result
      m_ComboResults.emplace_back(0.0, config);
   }

   return S_OK;
}


HRESULT CLoadCombinationResults::SumResultNoConfig(IndexType index, Float64 Result)
{
   ATLASSERT(0 <= index && index < (IndexType)m_ComboResults.size());

   ComboRes& rres = m_ComboResults[index];

   rres.m_Result +=  Result;

   return S_OK;
}

HRESULT CLoadCombinationResults::SumResult(IndexType index, BSTR loadCase, Float64 Result, Float64 Factor)
{
   HRESULT hr;
   ATLASSERT(0 <= index && index < (IndexType)m_ComboResults.size());

   ComboRes& rres = m_ComboResults[index];

   rres.m_Result +=  Result;

   ATLASSERT(rres.m_Config!=nullptr);

   hr = rres.m_Config->AddLoadCaseFactor(loadCase, Factor);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   return S_OK;
}

HRESULT CLoadCombinationResults::SumLLResult(IndexType index, Float64 Result, ILiveLoadConfiguration* Config, Float64 Factor)
{

   HRESULT hr;
   ATLASSERT(0 <= index && index < (IndexType)m_ComboResults.size());

   ComboRes& rres = m_ComboResults[index];

   rres.m_Result +=  Result;

   ATLASSERT(rres.m_Config!=nullptr);

   hr = rres.m_Config->put_LiveLoadFactor(Factor);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   hr = rres.m_Config->AddLiveLoadConfiguration(Config);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   return S_OK;
}


// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CLoadCombinationResults::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   m_ComboResults.clear();

   hr = pload->BeginUnit(CComBSTR("LoadCombinationResults"));
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
      hr = pload->get_Property(_bstr_t("Count"),&var);
      if (FAILED(hr))
         return hr;

      long cnt = var;
      m_ComboResults.reserve(cnt);

      for (long ic = 0; ic<cnt; ic++)
      {
         ComboRes reshldr;

         // left side
         var.Clear();
         hr = pload->get_Property(_bstr_t("Result"),&var);
         if (FAILED(hr))
            return hr;

         reshldr.m_Result = var;

         var.Clear();
         hr = pload->get_Property(_bstr_t("Config"),&var);
         if (FAILED(hr))
            return hr;

         // null configurations are written out as longs (see Save)
         if (var.vt==VT_I4)
         {
            reshldr.m_Config = nullptr;
         }
         else
         {
            // get variant into more convenient form
            CComPtr<ILoadCombinationResultConfiguration> cfg;
            hr = _CopyVariantToInterface<ILoadCombinationResultConfiguration>::copy(&cfg, &var);
            if (FAILED(hr))
               return STRLOAD_E_INVALIDFORMAT;

            reshldr.m_Config = cfg;
         }
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

STDMETHODIMP CLoadCombinationResults::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("LoadCombinationResults"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      IndexType cnt = m_ComboResults.size();

      hr = psave->put_Property(CComBSTR("Count"),_variant_t(cnt));
      if (FAILED(hr))
         return hr;

      for (IndexType ic = 0; ic<cnt; ic++)
      {
         const ComboRes& llres = m_ComboResults[ic];

         hr = psave->put_Property(CComBSTR("Result"),_variant_t(llres.m_Result));
         if (FAILED(hr))
            return hr;

         if (llres.m_Config!=nullptr)
            hr = psave->put_Property(CComBSTR("Config"),_variant_t(llres.m_Config));
         else
            hr = psave->put_Property(CComBSTR("Config"),_variant_t((long)0));

         if (FAILED(hr))
            return hr;
      }
   }

   hr = psave->EndUnit();
   return hr;
}
