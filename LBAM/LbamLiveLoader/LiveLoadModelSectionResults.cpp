///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2010  Washington State Department of Transportation
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

// ILiveLoadModelSectionResults.cpp : Implementation of CLiveLoadModelSectionResults
#include "stdafx.h"
#include "WBFLLBAMLiveLoader.h"
#include "LiveLoadModelSectionResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadModelSectionResults

STDMETHODIMP CLiveLoadModelSectionResults::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILiveLoadModelSectionResults
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLiveLoadModelSectionResults::Clear()
{
	m_Results.clear();

	return S_OK;
}

STDMETHODIMP CLiveLoadModelSectionResults::Reserve(CollectionIndexType size)
{
	if (size>=0)
      m_Results.reserve(size);
   else
      return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CLiveLoadModelSectionResults::get_Count(CollectionIndexType *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Results.size();

	return S_OK;
}

STDMETHODIMP CLiveLoadModelSectionResults::Add(Float64 leftResult, ILiveLoadConfiguration *leftConfig, Float64 rightResult, ILiveLoadConfiguration *rightConfig)
{

	m_Results.push_back( LlmResults(leftResult, leftConfig, rightResult, rightConfig) );

	return S_OK;
}

STDMETHODIMP CLiveLoadModelSectionResults::SetResult(CollectionIndexType index, Float64 leftResult, ILiveLoadConfiguration *leftConfig, Float64 rightResult, ILiveLoadConfiguration *rightConfig)
{

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

STDMETHODIMP CLiveLoadModelSectionResults::GetResult(CollectionIndexType index, Float64 *leftResult, ILiveLoadConfiguration **leftConfig, Float64 *rightResult, ILiveLoadConfiguration **rightConfig)
{
   // Left and Right config can be NULL
  
	if (0 <= index && index < (CollectionIndexType)m_Results.size())
   {
      LlmResults& rresult = m_Results[index];

      *leftResult     = rresult.m_LeftResult;

      if (leftConfig!=NULL)
         rresult.m_LeftConfig.CopyTo(leftConfig);

      *rightResult    = rresult.m_RightResult;

      if (rightConfig!=NULL)
         rresult.m_RightConfig.CopyTo(rightConfig);
   }
   else
      return E_INVALIDARG;

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CLiveLoadModelSectionResults::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   m_Results.clear();

   hr = pload->BeginUnit(CComBSTR("LiveLoadModelSectionResults"));
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

      for (long ic=0; ic<cnt; ic++)
      {
         LlmResults reshldr;

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

STDMETHODIMP CLiveLoadModelSectionResults::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("LiveLoadModelSectionResults"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      long cnt = m_Results.size();

      hr = psave->put_Property(CComBSTR("Count"),_variant_t(cnt));
      if (FAILED(hr))
         return hr;

      for (long ic=0; ic<cnt; ic++)
      {
         const LlmResults& llres = m_Results[ic];

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
