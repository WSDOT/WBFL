///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
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

// StressResult.cpp : Implementation of CStressResult
#include "stdafx.h"
#include "WBFLLBAMAnalysis.h"
#include "StressResult.h"
#include "LBAMAnalysis.hh"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStressResult

STDMETHODIMP CStressResult::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStressResult
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStressResult::get_Count(/*[out,retval]*/ CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Results.size();
   return S_OK;
}

STDMETHODIMP CStressResult::AddResult(/*[in]*/ Float64 newVal)
{
   m_Results.push_back(newVal);
   return S_OK;
}

STDMETHODIMP CStressResult::SetResult(/*[in]*/CollectionIndexType index, /*[in]*/ Float64 newVal)
{
   try
   {
      Float64& rval = m_Results.at(index);
      rval = newVal;
   }
   catch(...) // most likely out_of_range
   {
      return E_INVALIDARG;
   }
   
   return S_OK;
}

STDMETHODIMP CStressResult::GetResult(/*[in]*/CollectionIndexType index, /*[out,retval]*/ Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   try
   {
      const Float64& rval = m_Results.at(index);
      *pVal = rval;
   }
   catch(...) // most likely out_of_range
   {
      return E_INVALIDARG;
   }
   return S_OK;
}

STDMETHODIMP CStressResult::FactorAndSum(IStressResult *incRes, Float64 Factor)
{
   CHECK_IN(incRes);
   try
   {
	   HRESULT hr;
      CollectionIndexType cnt;
      hr = incRes->get_Count(&cnt);
      if (FAILED(hr))
         return hr;

      // check for error conditions before mutating
      if (cnt != m_Results.size())
         THROW_LBAMA(INCOMP_STRESSRESULTS);

      // perform summations
      for (CollectionIndexType i=0; i<cnt; i++)
      {
         Float64& rd = m_Results[i];

         Float64 inc;
         hr = incRes->GetResult(i, &inc);
         if (FAILED(hr))
            return hr;

         rd += (inc*Factor);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IStressResult);
   }

	return S_OK;
}

STDMETHODIMP CStressResult::Clone(IStressResult **clone)
{
   CHECK_RETOBJ(clone);

   // create a new stress point collection and fill it up
   CComObject<CStressResult>* pnew;
   HRESULT hr = CComObject<CStressResult>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   pnew->m_Results  = m_Results;

   *clone = pnew;
   (*clone)->AddRef();

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CStressResult::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("StressResult"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      // left
      _variant_t var;
      hr = pload->get_Property(_bstr_t("Count"),&var);
      if (FAILED(hr))
         return hr;

      long cnt = var;
      m_Results.clear();
      m_Results.reserve(cnt);

      for (long i=0; i<cnt; i++)
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("Val"),&var);
         if (FAILED(hr))
            return hr;

         m_Results.push_back((Float64)var);
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

STDMETHODIMP CStressResult::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("StressResult"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      CollectionIndexType cnt = m_Results.size();
      hr = psave->put_Property(CComBSTR("Count"),_variant_t(cnt));
      if (FAILED(hr))
         return hr;

      for (CollectionIndexType i=0; i<cnt; i++)
      {
         hr = psave->put_Property(CComBSTR("Val"),_variant_t(m_Results[i]));
         if (FAILED(hr))
            return hr;
      }
   }

   hr = psave->EndUnit();
   return hr;
}

STDMETHODIMP CStressResult::HpSumResults(/*[in]*/CollectionIndexType Num, /*[in]*/Float64* Vals)
{
   CHECK_IN(Vals);

   // left
   CollectionIndexType size = m_Results.size();
   if (Num!=size)
      return E_INVALIDARG;

   Float64Iterator it( m_Results.begin() );
   Float64Iterator itend( m_Results.end() );
   for (; it!=itend; it++)
   {
      *it += *(Vals++);
   }

   return S_OK;
}

STDMETHODIMP CStressResult::HpSetResults(/*[in]*/CollectionIndexType Num, /*[in]*/Float64* Vals)
{
   CHECK_IN(Vals);

   ATLASSERT(Num>=0);

   m_Results.assign(Vals, Vals+Num);

   return S_OK;
}
