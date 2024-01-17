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

// SegmentItem.cpp : Implementation of CSegmentItem
#include "stdafx.h"
#include "WBFLLBAMLoadCombiner.h"
#include "LoadCaseResponseAgg.h"

#include "LBAMLoadCombiner.hh"
#include "LBAMLoadCombinerErrors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSegmentItem
// add up a collection of ISectionResult3D's
inline void SumSectionResult3Ds(ISectionResult3Ds* Summ, ISectionResult3Ds* Tmp, IndexType Cnt)
{
   CHRException hr;
   for (IndexType i = 0; i<Cnt; i++)
   {
      CComPtr<ISectionResult3D> sm, tp;
      hr = Summ->get_Item(i, &sm);
      hr = Tmp->get_Item(i, &tp);
      hr = sm->FactorAndSum(tp, 1.0, 1.0);
   }
}

inline void SumResult3Ds(IResult3Ds* Summ, IResult3Ds* Tmp, IndexType Cnt)
{
   CHRException hr;
   for (IndexType i = 0; i<Cnt; i++)
   {
      CComPtr<IResult3D> sm, tp;
      hr = Summ->get_Item(i, &sm);
      hr = Tmp->get_Item(i, &tp);
      hr = sm->FactorAndSum(tp, 1.0);
   }
}

inline void SumSectionStressResults(ISectionStressResults* results, ISectionStressResults* incRes, IndexType numPois)
{
   CHRException hr;
   for (IndexType i = 0; i<numPois; i++)
   {
      CComPtr<ISectionStressResult> res, inc_res;
      hr = results->get_Item(i, &res);
      hr = incRes->get_Item(i, &inc_res);
      hr = res->FactorAndSum(inc_res, 1.0, 1.0);
   }
}

STDMETHODIMP CLoadCaseResponseAgg::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ISegmentItem
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


// ILoadCaseResponse
STDMETHODIMP CLoadCaseResponseAgg::ComputeForces(BSTR LoadCase, IIDArray* POIs, BSTR Stage, ResultsOrientation orientation, 
                                                 ResultsSummationType summ, ISectionResult3Ds **pResults)
{
   CHECK_IN(LoadCase);
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      *pResults = nullptr;

      m_pCombiner->Validate();

      // get the list of active load groups for the load case
      CLoadCombiner::LoadCaseIterator lcit( m_pCombiner->m_LoadCases.find( CLoadCombiner::NameHolder(LoadCase) ) );
      if (lcit == m_pCombiner->m_LoadCases.end())
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCASE_NO_EXIST, LoadCase);
         THROW_LBAMC_MSG(LOADCASE_NO_EXIST, msg);
      }

      CLoadCombiner::NameVec rloadgroups  = lcit->second;

      IndexType num_pois;
      hr = POIs->get_Count(&num_pois);

      // create our results object
      CComPtr<ISectionResult3Ds> results;

      // create our results object
      hr = results.CoCreateInstance(CLSID_SectionResult3Ds);
      hr = results->Reserve(num_pois);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_SectionResult3D,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      // create zeroed results
      for (IndexType ipoi = 0; ipoi<num_pois; ipoi++)
      {
         CComPtr<ISectionResult3D> pres;
         hr = factory->CreateInstance(nullptr, IID_ISectionResult3D, (void**)&pres);
         hr = results->Add(pres);
      }

      // cycle through load groups and sum
      IndexType lg_cnt = rloadgroups.size();
      for (IndexType ilg = 0; ilg<lg_cnt; ilg++)
      {
         CMB_HANDLE_CANCEL_PROGRESS();

         CComPtr<ISectionResult3Ds> loc_res;

         CComBSTR& lg_name = rloadgroups[ilg];

         HRESULT h = m_pCombiner->m_pLoadGroupResponse->ComputeForces(lg_name, POIs, Stage, orientation, summ, &loc_res);
         if (FAILED(h))
         {
            if (h==LBAMA_E_LOADGROUP_NOT_FOUND)
            {
               CComBSTR msg = CreateErrorMsg2S(IDS_E_INVALID_LG_RESP, LoadCase, lg_name);
               THROW_LBAMC_MSG(INVALID_LG_RESP, msg);
            }
            else
               THROW_HR(h);
         }

         SumSectionResult3Ds(results, loc_res, num_pois);
      }

      CMB_HANDLE_CANCEL_PROGRESS();
      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_ILoadCaseResponse);
   }

	return S_OK;
}

STDMETHODIMP CLoadCaseResponseAgg::ComputeDeflections(BSTR LoadCase, IIDArray* POIs, BSTR Stage,
                                                 ResultsSummationType summ, ISectionResult3Ds **pResults)
{
   CHECK_IN(LoadCase);
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      *pResults = nullptr;

      m_pCombiner->Validate();

      // get the list of active load groups for the load case
      CLoadCombiner::LoadCaseIterator lcit( m_pCombiner->m_LoadCases.find( CLoadCombiner::NameHolder(LoadCase) ) );
      if (lcit == m_pCombiner->m_LoadCases.end())
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCASE_NO_EXIST, LoadCase);
         THROW_LBAMC_MSG(LOADCASE_NO_EXIST, msg);
      }

      CLoadCombiner::NameVec rloadgroups  = lcit->second;

      IndexType num_pois;
      hr = POIs->get_Count(&num_pois);

      // create our results object
      CComPtr<ISectionResult3Ds> results;

      // create our results object
      hr = results.CoCreateInstance(CLSID_SectionResult3Ds);
      hr = results->Reserve(num_pois);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_SectionResult3D,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      // no load groups - just return results as zero
      for (IndexType ipoi = 0; ipoi<num_pois; ipoi++)
      {
         CComPtr<ISectionResult3D> pres;
         hr = factory->CreateInstance(nullptr, IID_ISectionResult3D, (void**)&pres);
         hr = results->Add(pres);
      }

      // cycle through load groups and sum
      IndexType lg_cnt = rloadgroups.size();
      for (IndexType ilg = 0; ilg<lg_cnt; ilg++)
      {
         CMB_HANDLE_CANCEL_PROGRESS();

         CComPtr<ISectionResult3Ds> loc_res;

         CComBSTR& lg_name = rloadgroups[ilg];

         HRESULT h = m_pCombiner->m_pLoadGroupResponse->ComputeDeflections(lg_name, POIs, Stage, summ, &loc_res);
         if (FAILED(h))
         {
            if (h==LBAMA_E_LOADGROUP_NOT_FOUND)
            {
               CComBSTR msg = CreateErrorMsg2S(IDS_E_INVALID_LG_RESP, LoadCase, lg_name);
               THROW_LBAMC_MSG(INVALID_LG_RESP, msg);
            }
            else
                  THROW_HR(h);
         }

         SumSectionResult3Ds(results, loc_res, num_pois);
      }

      CMB_HANDLE_CANCEL_PROGRESS();
      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_ILoadCaseResponse);
   }

	return S_OK;
}



STDMETHODIMP CLoadCaseResponseAgg::ComputeReactions(BSTR LoadCase, IIDArray* POIs, BSTR Stage,
                                                 ResultsSummationType summ, IResult3Ds **pResults)
{
   CHECK_IN(LoadCase);
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      *pResults = nullptr;

      m_pCombiner->Validate();

      // get the list of active load groups for the load case
      CLoadCombiner::LoadCaseIterator lcit( m_pCombiner->m_LoadCases.find( CLoadCombiner::NameHolder(LoadCase) ) );
      if (lcit == m_pCombiner->m_LoadCases.end())
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCASE_NO_EXIST, LoadCase);
         THROW_LBAMC_MSG(LOADCASE_NO_EXIST, msg);
      }

      CLoadCombiner::NameVec rloadgroups  = lcit->second;

      IndexType num_pois;
      hr = POIs->get_Count(&num_pois);

      // create our results object
      CComPtr<IResult3Ds> results;

      // create our results object
      hr = results.CoCreateInstance(CLSID_Result3Ds);
      hr = results->Reserve(num_pois);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_Result3D,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      // no load groups - just return results as zero
      for (IndexType ipoi = 0; ipoi<num_pois; ipoi++)
      {
         CComPtr<IResult3D> pres;
         hr = factory->CreateInstance(nullptr, IID_IResult3D, (void**)&pres);
         hr = results->Add(pres);
      }

      // cycle through load groups
      IndexType lg_cnt = rloadgroups.size();
      for (IndexType ilg = 0; ilg<lg_cnt; ilg++)
      {
         CMB_HANDLE_CANCEL_PROGRESS();

         CComPtr<IResult3Ds> loc_res;

         CComBSTR& lg_name = rloadgroups[ilg];

         HRESULT h = m_pCombiner->m_pLoadGroupResponse->ComputeReactions(lg_name, POIs, Stage, summ, &loc_res);
         if (FAILED(h))
         {
            if (h==LBAMA_E_LOADGROUP_NOT_FOUND)
            {
               CComBSTR msg = CreateErrorMsg2S(IDS_E_INVALID_LG_RESP, LoadCase, lg_name);
               THROW_LBAMC_MSG(INVALID_LG_RESP, msg);
            }
            else
               THROW_HR(h);
         }

         SumResult3Ds(results, loc_res, num_pois);
      }

      CMB_HANDLE_CANCEL_PROGRESS();
      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_ILoadCaseResponse);
   }

	return S_OK;
}

STDMETHODIMP CLoadCaseResponseAgg::ComputeSupportDeflections(BSTR LoadCase, IIDArray* POIs, BSTR Stage,
                                                 ResultsSummationType summ, IResult3Ds **pResults)
{
   CHECK_IN(LoadCase);
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      *pResults = nullptr;

      m_pCombiner->Validate();

      // get the list of active load groups for the load case
      CLoadCombiner::LoadCaseIterator lcit( m_pCombiner->m_LoadCases.find( CLoadCombiner::NameHolder(LoadCase) ) );
      if (lcit == m_pCombiner->m_LoadCases.end())
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCASE_NO_EXIST, LoadCase);
         THROW_LBAMC_MSG(LOADCASE_NO_EXIST, msg);
      }

      CLoadCombiner::NameVec rloadgroups  = lcit->second;

      IndexType num_pois;
      hr = POIs->get_Count(&num_pois);

      // create our results object
      CComPtr<IResult3Ds> results;

      // create our results object
      hr = results.CoCreateInstance(CLSID_Result3Ds);
      hr = results->Reserve(num_pois);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_Result3D,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      // no load groups - just return results as zero
      for (IndexType ipoi = 0; ipoi<num_pois; ipoi++)
      {
         CComPtr<IResult3D> pres;
         hr = factory->CreateInstance(nullptr, IID_IResult3D, (void**)&pres);
         hr = results->Add(pres);
      }

      // cycle through load groups - we'll let server create our first results object and return it
      IndexType lg_cnt = rloadgroups.size();
      for (IndexType ilg = 0; ilg<lg_cnt; ilg++)
      {
         CMB_HANDLE_CANCEL_PROGRESS();

         CComPtr<IResult3Ds> loc_res;

         CComBSTR& lg_name = rloadgroups[ilg];

         HRESULT h = m_pCombiner->m_pLoadGroupResponse->ComputeSupportDeflections(lg_name, POIs, Stage, summ, &loc_res);
         if (FAILED(h))
         {
            if (h==LBAMA_E_LOADGROUP_NOT_FOUND)
            {
               CComBSTR msg = CreateErrorMsg2S(IDS_E_INVALID_LG_RESP, LoadCase, lg_name);
               THROW_LBAMC_MSG(INVALID_LG_RESP, msg);
            }
            else
               THROW_HR(h);
         }

         SumResult3Ds(results, loc_res, num_pois);
      }

      CMB_HANDLE_CANCEL_PROGRESS();
      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_ILoadCaseResponse);
   }

	return S_OK;
}

STDMETHODIMP CLoadCaseResponseAgg::ComputeStresses(BSTR LoadCase, IIDArray* POIs, BSTR Stage,
                                                 ResultsSummationType summ, ISectionStressResults **pResults)
{
   CHECK_IN(LoadCase);
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      *pResults = nullptr;

      m_pCombiner->Validate();

      // get the list of active load groups for the load case
      CLoadCombiner::LoadCaseIterator lcit( m_pCombiner->m_LoadCases.find( CLoadCombiner::NameHolder(LoadCase) ) );
      if (lcit == m_pCombiner->m_LoadCases.end())
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCASE_NO_EXIST, LoadCase);
         THROW_LBAMC_MSG(LOADCASE_NO_EXIST, msg);
      }

      CLoadCombiner::NameVec rloadgroups  = lcit->second;

      IndexType num_pois;
      hr = POIs->get_Count(&num_pois);

      // create our results object
      CComPtr<ISectionStressResults> results;
      hr = results.CoCreateInstance(CLSID_SectionStressResults);
      hr = results->Reserve(num_pois);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_SectionStressResult,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      // Create results of zeros
      for (IndexType ipoi = 0; ipoi<num_pois; ipoi++)
      {
         PoiIDType poi_id;
         hr = POIs->get_Item(ipoi, &poi_id);

         CComPtr<ISectionStressResult> pres;
         hr = factory->CreateInstance(nullptr, IID_ISectionStressResult, (void**)&pres);

         // must determine the number of stress points and add a zero result for each
         CComPtr<IStressPoints> left_sps, right_sps;
         m_pCombiner->GetStressPoints(poi_id, Stage, &left_sps, &right_sps);

         // left
         IndexType cnt;
         hr = left_sps->get_Count(&cnt);
         for (IndexType i = 0; i<cnt; i++)
         {
            hr = pres->AddLeftResult(0.0);
         }

         // right
         hr = right_sps->get_Count(&cnt);
         for (IndexType i = 0; i<cnt; i++)
         {
            hr = pres->AddRightResult(0.0);
         }

         hr = results->Add(pres);
      }

      // cycle through load groups - we'll let server create our first results object and return it
      IndexType lg_cnt = rloadgroups.size();
      for (IndexType ilg = 0; ilg<lg_cnt; ilg++)
      {
         CMB_HANDLE_CANCEL_PROGRESS();

         CComPtr<ISectionStressResults> loc_res;
         CComBSTR& lg_name = rloadgroups[ilg];

         HRESULT h = m_pCombiner->m_pLoadGroupResponse->ComputeStresses(lg_name, POIs, Stage, summ, &loc_res);
         if (FAILED(h))
         {
            if (h==LBAMA_E_LOADGROUP_NOT_FOUND)
            {
               CComBSTR msg = CreateErrorMsg2S(IDS_E_INVALID_LG_RESP, LoadCase, lg_name);
               THROW_LBAMC_MSG(INVALID_LG_RESP, msg);
            }
            else
               THROW_HR(h);
         }

         SumSectionStressResults(results, loc_res, num_pois);
      }

      CMB_HANDLE_CANCEL_PROGRESS();
      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_ILoadCaseResponse);
   }

	return S_OK;
}


