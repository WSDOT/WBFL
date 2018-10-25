///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
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

// LiveLoadModelResults.cpp : Implementation of CLiveLoadModelResults
#include "stdafx.h"
#include "WBFLLBAMLiveLoader.h"
#include "LiveLoadModelResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadModelResults

STDMETHODIMP CLiveLoadModelResults::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILiveLoadModelResults
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CLiveLoadModelResults::Clear()
{
	m_Results.clear();

	return S_OK;
}

STDMETHODIMP CLiveLoadModelResults::Reserve(CollectionIndexType size)
{
	if (size>0)
      m_Results.reserve(size);
   else
      return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CLiveLoadModelResults::get_Count(CollectionIndexType *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Results.size();

	return S_OK;
}

STDMETHODIMP CLiveLoadModelResults::Add(Float64 result, ILiveLoadConfiguration *config)
{

	m_Results.push_back( LlmResults(result, config) );

	return S_OK;
}

STDMETHODIMP CLiveLoadModelResults::SetResult(CollectionIndexType index, Float64 result, ILiveLoadConfiguration *config)
{

	if (0 <= index && index < (CollectionIndexType)m_Results.size())
   {
      LlmResults& rresult = m_Results[index];
      rresult.m_Result  = result;
      rresult.m_Config  = config;
   }
   else
      return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CLiveLoadModelResults::GetResult(CollectionIndexType index, Float64 *result, ILiveLoadConfiguration **config)
{
	if (0 <= index && index < (CollectionIndexType)m_Results.size())
   {
      LlmResults& rresult = m_Results[index];

      *result     = rresult.m_Result;

      if (config!=NULL)
         rresult.m_Config.CopyTo(config);
   }
   else
      return E_INVALIDARG;

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CLiveLoadModelResults::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   m_Results.clear();

   hr = pload->BeginUnit(CComBSTR("LiveLoadModelResults"));
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
            reshldr.m_Config = NULL;
         }
         else
         {
            // get variant into more convenient form
            CComPtr<ILiveLoadConfiguration> cfg;
            hr = _CopyVariantToInterface<ILiveLoadConfiguration>::copy(&cfg, &var);
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

STDMETHODIMP CLiveLoadModelResults::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("LiveLoadModelResults"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      CollectionIndexType cnt = m_Results.size();

      hr = psave->put_Property(CComBSTR("Count"),_variant_t(cnt));
      if (FAILED(hr))
         return hr;

      for (CollectionIndexType ic=0; ic<cnt; ic++)
      {
         const LlmResults& llres = m_Results[ic];

         hr = psave->put_Property(CComBSTR("Result"),_variant_t(llres.m_Result));
         if (FAILED(hr))
            return hr;

         if (llres.m_Config!=NULL)
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
