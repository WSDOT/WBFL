///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright (C) 2009  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// LoadCombinationSectionResults.cpp : Implementation of CLoadCombinationSectionResults
#include "stdafx.h"
#include "WBFLLBAMLoadCombiner.h"
#include "LoadCombinationSectionResults.h"

#include "LoadCombinationResultConfiguration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationSectionResults

STDMETHODIMP CLoadCombinationSectionResults::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadCombinationSectionResults
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLoadCombinationSectionResults::Clear()
{
	m_ComboResults.clear();

	return S_OK;
}

STDMETHODIMP CLoadCombinationSectionResults::Reserve(CollectionIndexType size)
{
   if (size<0)
      return E_INVALIDARG;

   m_ComboResults.reserve(size);

	return S_OK;
}

STDMETHODIMP CLoadCombinationSectionResults::get_Count(CollectionIndexType *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_ComboResults.size();

	return S_OK;
}

STDMETHODIMP CLoadCombinationSectionResults::Add(Float64 leftResult, ILoadCombinationResultConfiguration *leftConfig, Float64 rightResult, ILoadCombinationResultConfiguration *rightConfig)
{

   m_ComboResults.push_back( ComboRes(leftResult, rightResult, leftConfig, rightConfig) );

	return S_OK;
}

STDMETHODIMP CLoadCombinationSectionResults::SetResult(CollectionIndexType index, Float64 leftResult, ILoadCombinationResultConfiguration *leftConfig, Float64 rightResult, ILoadCombinationResultConfiguration *rightConfig)
{

   if (index < 0 || (CollectionIndexType)m_ComboResults.size() <= index)
      return E_INVALIDARG;

   ComboRes& rres = m_ComboResults[index];

   rres.m_LeftResult  = leftResult;
   rres.m_LeftConfig  = leftConfig;
   rres.m_RightResult = rightResult;
   rres.m_RightConfig = rightConfig;

	return S_OK;
}

STDMETHODIMP CLoadCombinationSectionResults::GetResult(CollectionIndexType index, Float64* leftResult, ILoadCombinationResultConfiguration **leftConfig, Float64* rightResult, ILoadCombinationResultConfiguration **rightConfig)
{
   HRESULT hr;

   if (index < 0 || (CollectionIndexType)m_ComboResults.size() <= index)
      return E_INVALIDARG;

	CHECK_RETVAL(leftResult);
	CHECK_RETVAL(rightResult);

   ComboRes& rres = m_ComboResults[index];

   *leftResult  = rres.m_LeftResult;
   *rightResult = rres.m_RightResult;

   if (leftConfig!=NULL)
   {
      hr = rres.m_LeftConfig.CopyTo(leftConfig);
      if (FAILED(hr))
         return hr;
   }

   if (rightConfig!=NULL)
   {
      hr = rres.m_RightConfig.CopyTo(rightConfig);
      if (FAILED(hr))
         return hr;
   }

   return S_OK;
}


HRESULT CLoadCombinationSectionResults::AllocateResults(CollectionIndexType size, bool createConfig, ResultsSummationType summ)
{
   HRESULT hr;

   if (size<0)
   {
      ATLASSERT(0);
      return E_INVALIDARG;
   }

   ATLASSERT(m_ComboResults.empty()); // should only be allocating once

   m_ComboResults.reserve(size);

   for (CollectionIndexType i=0; i<size; i++)
   {
      CComPtr<ILoadCombinationResultConfiguration> left_config;
      CComPtr<ILoadCombinationResultConfiguration> right_config;

      // create configuration object only if asked
      if (createConfig)
      {
         CComObject<CLoadCombinationResultConfiguration>* left_coconfig;
         hr = CComObject<CLoadCombinationResultConfiguration>::CreateInstance(&left_coconfig);
         if (FAILED(hr))
            return hr;

         hr = left_coconfig->put_SummationType(summ);
         if (FAILED(hr))
            return hr;

         left_config = left_coconfig;

         CComObject<CLoadCombinationResultConfiguration>* right_coconfig;
         hr = CComObject<CLoadCombinationResultConfiguration>::CreateInstance(&right_coconfig);
         if (FAILED(hr))
            return hr;

         hr = right_coconfig->put_SummationType(summ);
         if (FAILED(hr))
            return hr;

         right_config = right_coconfig;
      }

      // add empty result
      m_ComboResults.push_back( ComboRes(0.0, 0.0, left_config, right_config) );
   }

   return S_OK;
}


HRESULT CLoadCombinationSectionResults::SumResultNoConfig(CollectionIndexType index, Float64 leftResult, Float64 rightResult)
{
   ATLASSERT(0 <= index && index < (CollectionIndexType)m_ComboResults.size());

   ComboRes& rres = m_ComboResults[index];

   rres.m_LeftResult +=  leftResult;
   rres.m_RightResult += rightResult;

   return S_OK;
}

HRESULT CLoadCombinationSectionResults::SumResult(CollectionIndexType index, BSTR loadCase, Float64 leftResult, Float64 leftFactor, Float64 rightResult, Float64 rightFactor)
{
   CHECK_IN(loadCase);

   HRESULT hr;
   ATLASSERT(0 <= index && index < (CollectionIndexType)m_ComboResults.size());

   ComboRes& rres = m_ComboResults[index];

   rres.m_LeftResult +=  leftResult;
   rres.m_RightResult += rightResult;

   ATLASSERT(rres.m_LeftConfig!=NULL);
   ATLASSERT(rres.m_RightConfig!=NULL);

   hr = rres.m_LeftConfig->AddLoadCaseFactor(loadCase, leftFactor);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = rres.m_RightConfig->AddLoadCaseFactor(loadCase, rightFactor);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   return S_OK;
}

HRESULT CLoadCombinationSectionResults::SumLLResult(CollectionIndexType index, Float64 leftResult, ILiveLoadConfiguration* leftConfig, Float64 rightResult, 
                                             ILiveLoadConfiguration* rightConfig, Float64 Factor)
{

   HRESULT hr;
   ATLASSERT(0 <= index && index < (CollectionIndexType)m_ComboResults.size());

   ComboRes& rres = m_ComboResults[index];

   rres.m_LeftResult +=  leftResult;
   rres.m_RightResult += rightResult;

   ATLASSERT(rres.m_LeftConfig!=NULL);
   ATLASSERT(rres.m_RightConfig!=NULL);

   hr = rres.m_LeftConfig->put_LiveLoadFactor(Factor);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = rres.m_RightConfig->put_LiveLoadFactor(Factor);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = rres.m_LeftConfig->AddLiveLoadConfiguration(leftConfig);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = rres.m_RightConfig->AddLiveLoadConfiguration(rightConfig);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   return S_OK;
}


// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CLoadCombinationSectionResults::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   m_ComboResults.clear();

   hr = pload->BeginUnit(CComBSTR("LoadCombinationSectionResults"));
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

      for (long ic=0; ic<cnt; ic++)
      {
         ComboRes reshldr;

         // left side
         var.Clear();
         hr = pload->get_Property(_bstr_t("LeftResult"),&var);
         if (FAILED(hr))
            return hr;

         reshldr.m_LeftResult = var;

         var.Clear();
         hr = pload->get_Property(_bstr_t("LeftConfig"),&var);
         if (FAILED(hr))
            return hr;

         // null configurations are written out as longs (see Save)
         if (var.vt==VT_I4)
         {
            reshldr.m_LeftConfig = NULL;
         }
         else
         {
            // get variant into more convenient form
            CComPtr<ILoadCombinationResultConfiguration> cfg;
            hr = _CopyVariantToInterface<ILoadCombinationResultConfiguration>::copy(&cfg, &var);
            if (FAILED(hr))
               return STRLOAD_E_INVALIDFORMAT;

            reshldr.m_LeftConfig = cfg;
         }

         // right side
         var.Clear();
         hr = pload->get_Property(_bstr_t("RightResult"),&var);
         if (FAILED(hr))
            return hr;

         reshldr.m_RightResult = var;

         var.Clear();
         hr = pload->get_Property(_bstr_t("RightConfig"),&var);
         if (FAILED(hr))
            return hr;

         if (var.vt==VT_I4)
         {
            reshldr.m_RightConfig = NULL;
         }
         else
         {
            // get variant into more convenient form
            CComPtr<ILoadCombinationResultConfiguration> cfg;
            hr = _CopyVariantToInterface<ILoadCombinationResultConfiguration>::copy(&cfg, &var);
            if (FAILED(hr))
               return STRLOAD_E_INVALIDFORMAT;

            reshldr.m_RightConfig = cfg;
         }

         // add to collection
         m_ComboResults.push_back(reshldr);
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

STDMETHODIMP CLoadCombinationSectionResults::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("LoadCombinationSectionResults"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      long cnt = m_ComboResults.size();

      hr = psave->put_Property(CComBSTR("Count"),_variant_t(cnt));
      if (FAILED(hr))
         return hr;

      for (long ic=0; ic<cnt; ic++)
      {
         const ComboRes& llres = m_ComboResults[ic];

         hr = psave->put_Property(CComBSTR("LeftResult"),_variant_t(llres.m_LeftResult));
         if (FAILED(hr))
            return hr;

         if (llres.m_LeftConfig!=NULL)
            hr = psave->put_Property(CComBSTR("LeftConfig"),_variant_t(llres.m_LeftConfig));
         else
            hr = psave->put_Property(CComBSTR("LeftConfig"),_variant_t((long)0));

         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("RightResult"),_variant_t(llres.m_RightResult));
         if (FAILED(hr))
            return hr;

         if (llres.m_RightConfig!=NULL)
            hr = psave->put_Property(CComBSTR("RightConfig"),_variant_t(llres.m_RightConfig));
         else
            hr = psave->put_Property(CComBSTR("RightConfig"),_variant_t((long)0));

         if (FAILED(hr))
            return hr;
      }
   }

   hr = psave->EndUnit();
   return hr;
}
