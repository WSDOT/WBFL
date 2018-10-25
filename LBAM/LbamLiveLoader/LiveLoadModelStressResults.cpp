///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2018  Washington State Department of Transportation
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

// LiveLoadModelStressResults.cpp : Implementation of CLiveLoadModelStressResults
#include "stdafx.h"
#include "WBFLLBAMLiveLoader.h"
#include "LiveLoadModelStressResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadModelStressResults

STDMETHODIMP CLiveLoadModelStressResults::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILiveLoadModelStressResults
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLiveLoadModelStressResults::Clear()
{
	m_Results.clear();

	return S_OK;
}

STDMETHODIMP CLiveLoadModelStressResults::Reserve(CollectionIndexType size)
{
	if (size>=0)
      m_Results.reserve(size);
   else
      return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CLiveLoadModelStressResults::get_Count(CollectionIndexType *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Results.size();

	return S_OK;
}

STDMETHODIMP CLiveLoadModelStressResults::Add(IStressResult *leftResult, ILiveLoadConfiguration *leftConfig, IStressResult *rightResult, ILiveLoadConfiguration *rightConfig)
{
   CHECK_IN(leftResult);
   CHECK_IN(rightResult);

	m_Results.push_back( LlmResults(leftResult, leftConfig, rightResult, rightConfig) );

	return S_OK;
}

STDMETHODIMP CLiveLoadModelStressResults::GetResult(CollectionIndexType index, IStressResult **leftResult, ILiveLoadConfiguration **leftConfig, IStressResult **rightResult, ILiveLoadConfiguration **rightConfig)
{

   HRESULT hr;
	if (0 <= index && index < (CollectionIndexType)m_Results.size())
   {
      LlmResults& rresult = m_Results[index];

      hr = rresult.m_LeftResult.CopyTo(leftResult);
      if (FAILED(hr))
         return hr;

      if (leftConfig!=nullptr)
      {
         hr = rresult.m_LeftConfig.CopyTo(leftConfig);
         if (FAILED(hr))
            return hr;
      }

      hr = rresult.m_RightResult.CopyTo(rightResult);
      if (FAILED(hr))
         return hr;

      if (leftConfig!=nullptr)
      {
         hr = rresult.m_RightConfig.CopyTo(rightConfig);
         if (FAILED(hr))
            return hr;
      }
   }
   else
      return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CLiveLoadModelStressResults::SetResult(CollectionIndexType index, IStressResult *leftResult, ILiveLoadConfiguration *leftConfig, IStressResult *rightResult, ILiveLoadConfiguration *rightConfig)
{
   CHECK_IN(leftResult);
   CHECK_IN(rightResult);

	if (0 <= index && index < (CollectionIndexType)m_Results.size())
   {
      LlmResults& rresult = m_Results[index];
      rresult.m_LeftResult  = leftResult;
      rresult.m_LeftConfig  = leftConfig;
      rresult.m_RightResult = rightResult;
      rresult.m_RightConfig = rightConfig;
   }
   else
      return E_INVALIDARG;

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CLiveLoadModelStressResults::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   m_Results.clear();

   hr = pload->BeginUnit(CComBSTR("LiveLoadModelStressResults"));
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
      m_Results.reserve(cnt);

      for (long ic = 0; ic<cnt; ic++)
      {
         LlmResults reshldr;

         // left side
         var.Clear();
         hr = pload->get_Property(_bstr_t("LeftResult"),&var);
         if (FAILED(hr))
            return hr;

         // get variant into more convenient form
         CComPtr<IStressResult> left_res;
         hr = _CopyVariantToInterface<IStressResult>::copy(&left_res, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         reshldr.m_LeftResult = left_res;

         var.Clear();
         hr = pload->get_Property(_bstr_t("LeftConfig"),&var);
         if (FAILED(hr))
            return hr;

         // null configurations are written out as longs (see Save)
         if (var.vt==VT_I4)
         {
            reshldr.m_LeftConfig = nullptr;
         }
         else
         {
            // get variant into more convenient form
            CComPtr<ILiveLoadConfiguration> cfg;
            hr = _CopyVariantToInterface<ILiveLoadConfiguration>::copy(&cfg, &var);
            if (FAILED(hr))
               return STRLOAD_E_INVALIDFORMAT;

            reshldr.m_LeftConfig = cfg;
         }

         // right side
         var.Clear();
         hr = pload->get_Property(_bstr_t("RightResult"),&var);
         if (FAILED(hr))
            return hr;

         // get variant into more convenient form
         CComPtr<IStressResult> right_res;
         hr = _CopyVariantToInterface<IStressResult>::copy(&right_res, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         reshldr.m_RightResult = right_res;

         var.Clear();
         hr = pload->get_Property(_bstr_t("RightConfig"),&var);
         if (FAILED(hr))
            return hr;

         if (var.vt==VT_I4)
         {
            reshldr.m_RightConfig = nullptr;
         }
         else
         {
            // get variant into more convenient form
            CComPtr<ILiveLoadConfiguration> cfg;
            hr = _CopyVariantToInterface<ILiveLoadConfiguration>::copy(&cfg, &var);
            if (FAILED(hr))
               return STRLOAD_E_INVALIDFORMAT;

            reshldr.m_RightConfig = cfg;
         }

         // add to collection
         m_Results.push_back(reshldr);
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

STDMETHODIMP CLiveLoadModelStressResults::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("LiveLoadModelStressResults"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      CollectionIndexType cnt = m_Results.size();

      hr = psave->put_Property(CComBSTR("Count"),_variant_t(cnt));
      if (FAILED(hr))
         return hr;

      for (CollectionIndexType ic = 0; ic<cnt; ic++)
      {
         const LlmResults& llres = m_Results[ic];

         hr = psave->put_Property(CComBSTR("LeftResult"),_variant_t(llres.m_LeftResult));
         if (FAILED(hr))
            return hr;

         // remember config can be null
         if (llres.m_LeftConfig!=nullptr)
            hr = psave->put_Property(CComBSTR("LeftConfig"),_variant_t(llres.m_LeftConfig));
         else
            hr = psave->put_Property(CComBSTR("LeftConfig"),_variant_t((long)0));

         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("RightResult"),_variant_t(llres.m_RightResult));
         if (FAILED(hr))
            return hr;

         if (llres.m_RightConfig!=nullptr)
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
