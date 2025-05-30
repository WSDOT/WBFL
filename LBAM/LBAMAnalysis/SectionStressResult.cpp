///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2025  Washington State Department of Transportation
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

// SectionStressResult.cpp : Implementation of CSectionStressResult
#include "stdafx.h"
#include "WBFLLBAMAnalysis.h"
#include "SectionStressResult.h"
#include "StressResult.h"
#include "LBAMAnalysis.hh"


/////////////////////////////////////////////////////////////////////////////
// CSectionStressResult
STDMETHODIMP CSectionStressResult::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISectionStressResult
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSectionStressResult::get_LeftCount(/*[out,retval]*/ IndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_LeftResults.size();
   return S_OK;
}

STDMETHODIMP CSectionStressResult::AddLeftResult(/*[in]*/ Float64 newVal)
{
   m_LeftResults.push_back(newVal);
   return S_OK;
}

STDMETHODIMP CSectionStressResult::SetLeftResult(/*[in]*/IndexType index, /*[in]*/ Float64 newVal)
{
   try
   {
      Float64& rval = m_LeftResults.at(index);
      rval = newVal;
   }
   catch(...) // most likely out_of_range
   {
      return E_INVALIDARG;
   }
   
   return S_OK;
}

STDMETHODIMP CSectionStressResult::GetLeftResult(/*[in]*/IndexType index, /*[out,retval]*/ Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   try
   {
      const Float64& rval = m_LeftResults.at(index);
      *pVal = rval;
   }
   catch(...) // most likely out_of_range
   {
      return E_INVALIDARG;
   }
   return S_OK;
}

STDMETHODIMP CSectionStressResult::get_RightCount(/*[out,retval]*/ IndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_RightResults.size();
   return S_OK;
}

STDMETHODIMP CSectionStressResult::AddRightResult(/*[in]*/ Float64 newVal)
{
   m_RightResults.push_back(newVal);
   return S_OK;
}

STDMETHODIMP CSectionStressResult::SetRightResult(/*[in]*/IndexType index, /*[in]*/ Float64 newVal)
{
   try
   {
      Float64& rval = m_RightResults.at(index);
      rval = newVal;
   }
   catch(...) // most likely out_of_range
   {
      return E_INVALIDARG;
   }
   
   return S_OK;
}

STDMETHODIMP CSectionStressResult::GetRightResult(/*[in]*/IndexType index, /*[out,retval]*/ Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   try
   {
      const Float64& rval = m_RightResults.at(index);
      *pVal = rval;
   }
   catch(...) // most likely out_of_range
   {
      return E_INVALIDARG;
   }
   return S_OK;
}


STDMETHODIMP CSectionStressResult::CreateLeftStressResult(IStressResult* *result)
{
   CHECK_RETOBJ(result);

   HRESULT hr;
	CComObject<CStressResult>* res;
   hr = CComObject<CStressResult>::CreateInstance(&res);
   if (FAILED(hr))
      return hr;

   CComPtr<IStressResult> pres(res);

   res->m_Results.assign(m_LeftResults.begin(), m_LeftResults.end());

	return pres.CopyTo(result);
}

STDMETHODIMP CSectionStressResult::CreateRightStressResult(IStressResult* *result)
{
   CHECK_RETOBJ(result);

   HRESULT hr;
	CComObject<CStressResult>* res;
   hr = CComObject<CStressResult>::CreateInstance(&res);
   if (FAILED(hr))
      return hr;

   CComPtr<IStressResult> pres(res);

   res->m_Results.assign(m_RightResults.begin(), m_RightResults.end());

	return pres.CopyTo(result);
}

STDMETHODIMP CSectionStressResult::Clone(ISectionStressResult **clone)
{
   CHECK_RETOBJ(clone);

   // create a new stress point collection and fill it up
   CComObject<CSectionStressResult>* pnew;
   HRESULT hr = CComObject<CSectionStressResult>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   pnew->m_LeftResults  = m_LeftResults;
   pnew->m_RightResults = m_RightResults;

   *clone = pnew;
   (*clone)->AddRef();

	return S_OK;
}

STDMETHODIMP CSectionStressResult::FactorAndSum(ISectionStressResult *incRes, Float64 leftFactor, Float64 rightFactor)
{
   CHECK_IN(incRes);

   try
   {
	   HRESULT hr;
      IndexType left_cnt, right_cnt;
      hr = incRes->get_LeftCount(&left_cnt);
      if (FAILED(hr))
         return hr;

      hr = incRes->get_RightCount(&right_cnt);
      if (FAILED(hr))
         return hr;

      // check for error conditions before mutating
      if (left_cnt != m_LeftResults.size())
         THROW_LBAMA(INCOMP_STRESSRESULTS);

      if (right_cnt != m_RightResults.size())
         THROW_LBAMA(INCOMP_STRESSRESULTS);

      // perform summations
      for (IndexType i = 0; i<left_cnt; i++)
      {
         Float64& rd = m_LeftResults[i];

         Float64 inc;
         hr = incRes->GetLeftResult(i, &inc);
         if (FAILED(hr))
            return hr;

         rd += (inc*leftFactor);
      }

      for (IndexType i = 0; i<right_cnt; i++)
      {
         Float64& rd = m_RightResults[i];

         Float64 inc;
         hr = incRes->GetRightResult(i, &inc);
         if (FAILED(hr))
            return hr;

         rd += (inc*rightFactor);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISectionStressResult);
   }

	return S_OK;
}

STDMETHODIMP CSectionStressResult::HpSumResults(/*[in]*/IndexType numLeft, /*[in]*/Float64* leftVals, /*[in]*/IndexType numRight, /*[in]*/Float64* rightVals)
{
   // left
   IndexType size = m_LeftResults.size();
   if (numLeft!=size)
      return E_INVALIDARG;

   Float64Iterator it( m_LeftResults.begin() );
   Float64Iterator itend( m_LeftResults.end() );
   for (; it!=itend; it++)
   {
      *it += *(leftVals++);
   }

   // right
   size = m_RightResults.size();
   if (numRight!=size)
      return E_INVALIDARG;

   Float64Iterator itr( m_RightResults.begin() );
   Float64Iterator itrend( m_RightResults.end() );
   for (; itr!=itrend; itr++)
   {
      *itr += *(rightVals++);
   }

   return S_OK;
}

STDMETHODIMP CSectionStressResult::HpSetResults(/*[in]*/IndexType numLeft, /*[in]*/Float64* leftVals, /*[in]*/IndexType numRight, /*[in]*/Float64* rightVals)
{
   ATLASSERT(numLeft>=0);
   ATLASSERT(numRight>=0);

   m_LeftResults.assign(leftVals, leftVals+numLeft);
   m_RightResults.assign(rightVals, rightVals+numLeft);

   return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CSectionStressResult::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("SectionStressResult"));
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
      hr = pload->get_Property(_bstr_t("LeftCount"),&var);
      if (FAILED(hr))
         return hr;

      long cnt = var;
      m_LeftResults.clear();
      m_LeftResults.reserve(cnt);

      for (long i = 0; i<cnt; i++)
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("LeftVal"),&var);
         if (FAILED(hr))
            return hr;

         m_LeftResults.push_back((Float64)var);
      }

      // right
      var.Clear();
      hr = pload->get_Property(_bstr_t("RightCount"),&var);
      if (FAILED(hr))
         return hr;

      cnt = var;
      m_RightResults.clear();
      m_RightResults.reserve(cnt);

      for (long i = 0; i<cnt; i++)
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("RightVal"),&var);
         if (FAILED(hr))
            return hr;

         m_RightResults.push_back((Float64)var);
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


STDMETHODIMP CSectionStressResult::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("SectionStressResult"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      IndexType cnt = m_LeftResults.size();
      hr = psave->put_Property(CComBSTR("LeftCount"),_variant_t(cnt));
      if (FAILED(hr))
         return hr;

      for (IndexType i = 0; i<cnt; i++)
      {
         hr = psave->put_Property(CComBSTR("LeftVal"),_variant_t(m_LeftResults[i]));
         if (FAILED(hr))
            return hr;
      }

      cnt = m_RightResults.size();
      hr = psave->put_Property(CComBSTR("RightCount"),_variant_t(cnt));
      if (FAILED(hr))
         return hr;

      for (IndexType i = 0; i<cnt; i++)
      {
         hr = psave->put_Property(CComBSTR("RightVal"),_variant_t(m_RightResults[i]));
         if (FAILED(hr))
            return hr;
      }
   }

   hr = psave->EndUnit();
   return hr;
}


