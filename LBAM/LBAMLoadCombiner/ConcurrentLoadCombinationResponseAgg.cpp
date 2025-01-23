///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
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

// ConcurrentLoadCombinationResponseAgg.cpp : Implementation of CConcurrentLoadCombinationResponseAgg
#include "stdafx.h"
#include "WBFLLBAMLoadCombiner.h"
#include "ConcurrentLoadCombinationResponseAgg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static void FactorAndSumStressResults(ISectionStressResults* results, ISectionStressResults* lc_results, IndexType numPOIs, Float64 Factor)
{
   CHRException hr;
   for (IndexType ip = 0; ip<numPOIs; ip++)
   {
      CComPtr<ISectionStressResult> sumres, newres;
      hr = results->get_Item(ip, &sumres);

      hr = lc_results->get_Item(ip, &newres);

      hr = sumres->FactorAndSum(newres, Factor, Factor);
   }
}

static void FactorAndSumSectionResults(ISectionResult3Ds* results, ISectionResult3Ds* lc_results, IndexType numPOIs, Float64 Factor)
{
   CHRException hr;
   for (IndexType ip = 0; ip<numPOIs; ip++)
   {
      CComPtr<ISectionResult3D> sumres, newres;
      hr = results->get_Item(ip, &sumres);

      hr = lc_results->get_Item(ip, &newres);

      hr = sumres->FactorAndSum(newres, Factor, Factor);
   }
}

static void FactorAndSumResults(IResult3Ds* results, IResult3Ds* lc_results, IndexType numPOIs, Float64 Factor)
{
   CHRException hr;
   for (IndexType ip = 0; ip<numPOIs; ip++)
   {
      CComPtr<IResult3D> sumres, newres;
      hr = results->get_Item(ip, &sumres);

      hr = lc_results->get_Item(ip, &newres);

      hr = sumres->FactorAndSum(newres, Factor);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CConcurrentLoadCombinationResponseAgg

STDMETHODIMP CConcurrentLoadCombinationResponseAgg::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IConcurrentLoadCombinationResponse
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CConcurrentLoadCombinationResponseAgg::ComputeForces(IIDArray* POIs, BSTR Stage, ResultsOrientation Orientation, 
                                                                  ILoadCombinationResultConfiguration *Config, ISectionResult3Ds **pResults)
{
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_IN(Config);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      *pResults = nullptr;

      IndexType num_pois;
      hr = POIs->get_Count(&num_pois);

      // create our results object and fill it with zeroed results
      CComPtr<ISectionResult3Ds> results;
      hr = results.CoCreateInstance(CLSID_SectionResult3Ds);
      hr = results->Reserve(num_pois);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_SectionResult3D,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      // Create a zeroed results array
      for (IndexType ipoi = 0; ipoi<num_pois; ipoi++)
      {
         CComPtr<ISectionResult3D> pres;
         hr = factory->CreateInstance(nullptr, IID_ISectionResult3D, (void**)&pres);
         hr = results->Add(pres);
      }

      CMB_HANDLE_CANCEL_PROGRESS();

       // get number of load cases
      IndexType num_lcs;
      hr = Config->get_LoadCaseFactorCount(&num_lcs);

      ResultsSummationType summ;
      hr = Config->get_SummationType(&summ);

      // loop over load case results and apply them to combination
      for (IndexType i_lc = 0; i_lc<num_lcs; i_lc++)
      {
         CComBSTR lcs_name;
         Float64 factor;

         hr = Config->GetLoadCaseFactor(i_lc, &lcs_name, &factor);

         CComPtr<ISectionResult3Ds> lc_results;
         hr = m_pCombiner->m_pLoadCaseResponse->ComputeForces(lcs_name, POIs, Stage, 
                                                              Orientation, summ, &lc_results);

         FactorAndSumSectionResults(results, lc_results, num_pois, factor);

         CMB_HANDLE_CANCEL_PROGRESS();
      }

      Float64 ll_factor;
      hr = Config->get_LiveLoadFactor(&ll_factor);

      if (ll_factor!=0.0)
      {
         IndexType count;
         Config->GetLiveLoadConfigurationCount(&count);
         for (IndexType i = 0; i < count; i++ )
         {
            CComPtr<ILiveLoadConfiguration> ll_config;
            hr = Config->GetLiveLoadConfiguration(i,&ll_config);

            if (ll_config!=nullptr)
            {
               CComPtr<ISectionResult3Ds>      liveload_results;
               hr = m_pCombiner->m_pBasicVehicularResponse->ComputeForces(POIs, Stage, Orientation, ll_config, &liveload_results);

               FactorAndSumSectionResults(results, liveload_results, num_pois, ll_factor);
            }
         }
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_IConcurrentLoadCombinationResponse);
   }

	return S_OK;
}

STDMETHODIMP CConcurrentLoadCombinationResponseAgg::ComputeDeflections(IIDArray* POIs, BSTR Stage,
                                                                  ILoadCombinationResultConfiguration *Config, 
                                                                  ISectionResult3Ds **pResults)
{
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_IN(Config);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      *pResults = nullptr;

      IndexType num_pois;
      hr = POIs->get_Count(&num_pois);

      // create our results object and fill it with zeroed results
      CComPtr<ISectionResult3Ds> results;
      hr = results.CoCreateInstance(CLSID_SectionResult3Ds);
      hr = results->Reserve(num_pois);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_SectionResult3D,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      // Create a zeroed results array
      for (IndexType ipoi = 0; ipoi<=num_pois; ipoi++)
      {
         CComPtr<ISectionResult3D> pres;
         hr = factory->CreateInstance(nullptr, IID_ISectionResult3D, (void**)&pres);
         hr = results->Add(pres);
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      // get number of load cases
      IndexType num_lcs;
      hr = Config->get_LoadCaseFactorCount(&num_lcs);

      ResultsSummationType summ;
      hr = Config->get_SummationType(&summ);

      // loop over load case results and apply them to combination
      for (IndexType i_lc = 0; i_lc<num_lcs; i_lc++)
      {
         CComBSTR lcs_name;
         Float64 factor;

         hr = Config->GetLoadCaseFactor(i_lc, &lcs_name, &factor);

         CComPtr<ISectionResult3Ds> lc_results;
         hr = m_pCombiner->m_pLoadCaseResponse->ComputeDeflections(lcs_name, POIs, Stage, 
                                                                   summ, &lc_results);

         FactorAndSumSectionResults(results, lc_results, num_pois, factor);

         CMB_HANDLE_CANCEL_PROGRESS();
      }

      Float64 ll_factor;
      hr = Config->get_LiveLoadFactor(&ll_factor);

      if (ll_factor!=0.0)
      {
         IndexType count;
         Config->GetLiveLoadConfigurationCount(&count);
         for ( IndexType i = 0; i < count; i++ )
         {
            CComPtr<ILiveLoadConfiguration> ll_config;
            hr = Config->GetLiveLoadConfiguration(i,&ll_config);

            if (ll_config!=nullptr)
            {
               CComPtr<ISectionResult3Ds>      liveload_results;
               hr = m_pCombiner->m_pBasicVehicularResponse->ComputeDeflections(POIs, Stage, 
                                                                               ll_config, &liveload_results);
               FactorAndSumSectionResults(results, liveload_results, num_pois, ll_factor);
            }
         }
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_IConcurrentLoadCombinationResponse);
   }

	return S_OK;
}

STDMETHODIMP CConcurrentLoadCombinationResponseAgg::ComputeReactions(IIDArray* POIs, BSTR Stage,
                                                                  ILoadCombinationResultConfiguration *Config, 
                                                                  IResult3Ds **pResults)
{
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_IN(Config);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      *pResults = nullptr;

      IndexType num_pois;
      hr = POIs->get_Count(&num_pois);

      // create our results object and fill it with zeroed results
      CComPtr<IResult3Ds> results;
      hr = results.CoCreateInstance(CLSID_Result3Ds);
      hr = results->Reserve(num_pois);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_Result3D,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      // Create a zeroed results array
      for (IndexType ipoi = 0; ipoi<=num_pois; ipoi++)
      {
         CComPtr<IResult3D> pres;
         hr = factory->CreateInstance(nullptr, IID_IResult3D, (void**)&pres);
         hr = results->Add(pres);
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      // get number of load cases
      IndexType num_lcs;
      hr = Config->get_LoadCaseFactorCount(&num_lcs);

      ResultsSummationType summ;
      hr = Config->get_SummationType(&summ);

      // loop over load case results and apply them to combination
      for (IndexType i_lc = 0; i_lc<num_lcs; i_lc++)
      {
         CComBSTR lcs_name;
         Float64 factor;

         hr = Config->GetLoadCaseFactor(i_lc, &lcs_name, &factor);

         CComPtr<IResult3Ds> lc_results;
         hr = m_pCombiner->m_pLoadCaseResponse->ComputeReactions(lcs_name, POIs, Stage, 
                                                                 summ, &lc_results);

         FactorAndSumResults(results, lc_results, num_pois, factor);
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      Float64 ll_factor;
      hr = Config->get_LiveLoadFactor(&ll_factor);
      if (ll_factor!=0.0)
      {
         IndexType count;
         Config->GetLiveLoadConfigurationCount(&count);
         for ( IndexType i = 0; i < count; i++ )
         {
            CComPtr<ILiveLoadConfiguration> ll_config;
            hr = Config->GetLiveLoadConfiguration(i,&ll_config);

            if (ll_config!=nullptr)
            {
               CComPtr<IResult3Ds>      liveload_results;
               hr = m_pCombiner->m_pBasicVehicularResponse->ComputeReactions(POIs, Stage, ll_config, &liveload_results);

               FactorAndSumResults(results, liveload_results, num_pois, ll_factor);
            }
         }
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_IConcurrentLoadCombinationResponse);
   }

	return S_OK;
}

STDMETHODIMP CConcurrentLoadCombinationResponseAgg::ComputeSupportDeflections(IIDArray* POIs, BSTR Stage,
                                                                  ILoadCombinationResultConfiguration *Config, 
                                                                  IResult3Ds **pResults)
{
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_IN(Config);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      *pResults = nullptr;

      IndexType num_pois;
      hr = POIs->get_Count(&num_pois);

      // create our results object and fill it with zeroed results
      CComPtr<IResult3Ds> results;
      hr = results.CoCreateInstance(CLSID_Result3Ds);
      hr = results->Reserve(num_pois);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_Result3D,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      // Create a zeroed results array
      for (IndexType ipoi = 0; ipoi<=num_pois; ipoi++)
      {
         CComPtr<IResult3D> pres;
         hr = factory->CreateInstance(nullptr, IID_IResult3D, (void**)&pres);
         hr = results->Add(pres);
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      // get number of load cases
      IndexType num_lcs;
      hr = Config->get_LoadCaseFactorCount(&num_lcs);

      ResultsSummationType summ;
      hr = Config->get_SummationType(&summ);

      // loop over load case results and apply them to combination
      for (IndexType i_lc = 0; i_lc<num_lcs; i_lc++)
      {
         CComBSTR lcs_name;
         Float64 factor;

         hr = Config->GetLoadCaseFactor(i_lc, &lcs_name, &factor);

         CComPtr<IResult3Ds> lc_results;
         hr = m_pCombiner->m_pLoadCaseResponse->ComputeSupportDeflections(lcs_name, POIs, Stage, 
                                                                 summ, &lc_results);

         FactorAndSumResults(results, lc_results, num_pois, factor);

         CMB_HANDLE_CANCEL_PROGRESS();
      }

      Float64 ll_factor;
      hr = Config->get_LiveLoadFactor(&ll_factor);

      if (ll_factor!=0.0)
      {
         IndexType count;
         Config->GetLiveLoadConfigurationCount(&count);
         for ( IndexType i = 0; i < count; i++ )
         {
            CComPtr<ILiveLoadConfiguration> ll_config;
            hr = Config->GetLiveLoadConfiguration(i,&ll_config);

            if (ll_config!=nullptr)
            {
               CComPtr<IResult3Ds>      liveload_results;
               hr = m_pCombiner->m_pBasicVehicularResponse->ComputeSupportDeflections(POIs, Stage, ll_config, &liveload_results);

               FactorAndSumResults(results, liveload_results, num_pois, ll_factor);
            }
         }
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_IConcurrentLoadCombinationResponse);
   }

	return S_OK;
}


STDMETHODIMP CConcurrentLoadCombinationResponseAgg::ComputeStresses(IIDArray* POIs, BSTR Stage,
                                                                  ILoadCombinationResultConfiguration *Config, 
                                                                  ISectionStressResults **pResults)
{
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_IN(Config);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      *pResults = nullptr;

      IndexType num_pois;
      hr = POIs->get_Count(&num_pois);

      // create our results object and fill it with zeroed results
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

      CMB_HANDLE_CANCEL_PROGRESS();

      // get number of load cases
      IndexType num_lcs;
      hr = Config->get_LoadCaseFactorCount(&num_lcs);

      ResultsSummationType summ;
      hr = Config->get_SummationType(&summ);

      // loop over load case results and apply them to combination
      for (IndexType i_lc = 0; i_lc<num_lcs; i_lc++)
      {
         CComBSTR lcs_name;
         Float64 factor;

         hr = Config->GetLoadCaseFactor(i_lc, &lcs_name, &factor);

         CComPtr<ISectionStressResults> lc_results;
         hr = m_pCombiner->m_pLoadCaseResponse->ComputeStresses(lcs_name, POIs, Stage, 
                                                                summ, &lc_results);

         FactorAndSumStressResults(results, lc_results, num_pois, factor);

         CMB_HANDLE_CANCEL_PROGRESS();
      }

      Float64 ll_factor;
      hr = Config->get_LiveLoadFactor(&ll_factor);

      if (ll_factor!=0.0)
      {
         IndexType count;
         Config->GetLiveLoadConfigurationCount(&count);
         for ( IndexType i = 0; i < count; i++ )
         {
            CComPtr<ILiveLoadConfiguration> ll_config;
            hr = Config->GetLiveLoadConfiguration(i,&ll_config);

            if (ll_config!=nullptr)
            {
               CComPtr<ISectionStressResults>      liveload_results;
               hr = m_pCombiner->m_pBasicVehicularResponse->ComputeStresses(POIs, Stage, ll_config, &liveload_results);

               FactorAndSumStressResults(results, liveload_results, num_pois, ll_factor);
            }
         }
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_IConcurrentLoadCombinationResponse);
   }

	return S_OK;
}
