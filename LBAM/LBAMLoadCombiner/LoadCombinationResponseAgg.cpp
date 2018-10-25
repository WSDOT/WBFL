///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2012  Washington State Department of Transportation
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
#include "LoadCombinationResponseAgg.h"

#include "LoadCombinationResults.h"
#include "LoadCombinationSectionResults.h"

#include "LBAMLoadCombiner.hh"
#include "LBAMLoadCombinerErrors.h"

#include "LoadCombinationUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const Float64 ZERO_TOL=1.0e-10;

// utility classes for doing the combination
////////////////////////////////////////////
// virtual base class - handles computation of load combination modifiers via implementation inheritance
class LoadCombinationEngineBase
{
   public:
   LoadCombinationEngineBase(ILongArray* POIs, BSTR Stage, 
                             ResultsSummationType summ, LoadCombinationType lmType, 
                             IGetCombinationFactors* ifactors, bool createConfig, bool isPOIs ):
   m_CreateConfig(createConfig)
   {
      CHRException hr; // yes, we can throw from here
      CollectionIndexType numres;
      hr = POIs->get_Count(&numres);

      // initialize list of combination factors in same order as our pois
      for (CollectionIndexType i=0; i<numres; i++)
      {
         // get load modifiers
         PoiIDType id;
         hr = POIs->get_Item(i, &id);

         Float64 min_load_modifier, max_load_modifier;
         if (isPOIs)
         {
            if (id<0 && summ==rsCumulative)
            {
              THROW_LBAMC(SUM_INTERNAL_POI); // can't sum over stages for internal pois
            }

            hr = ifactors->GetPOICombinationFactors(id, Stage, lmType, &min_load_modifier, &max_load_modifier);
         }
         else
         {
            hr = ifactors->GetSupportCombinationFactors(id, Stage, lmType, &min_load_modifier, &max_load_modifier);
         }

         m_ComboFactors.push_back(ComboFactors(min_load_modifier, max_load_modifier));
      }
   }

protected:
   // vector of combination factors for our pois
   struct ComboFactors
   {
      ComboFactors(Float64 minLoadModifier, Float64 maxLoadModifier):
      m_MinLoadModifier(minLoadModifier),
      m_MaxLoadModifier(maxLoadModifier)
      {;}

      Float64                       m_MinLoadModifier;
      Float64                       m_MaxLoadModifier;
   };

   std::vector<ComboFactors>        m_ComboFactors;
   bool                             m_CreateConfig;
};

class LoadCombinationEngine: protected LoadCombinationEngineBase
{
   public:

   LoadCombinationEngine(ILongArray* POIs, BSTR Stage, 
                         ResultsSummationType summ, LoadCombinationType lmType, 
                         IGetCombinationFactors* ifactors, bool createConfig, bool isPOIs ):
   LoadCombinationEngineBase(POIs, Stage,  summ, lmType, ifactors, createConfig, isPOIs )
   {
      CollectionIndexType numres = m_ComboFactors.size();
      CreateResults(numres, summ);
   }

   void CreateResults(CollectionIndexType numRes, ResultsSummationType summ)
   {
      CHRException hr;
      CComObject<CLoadCombinationResults>* results;
      hr = CComObject<CLoadCombinationResults>::CreateInstance(&results);
      results->AllocateResults(numRes, m_CreateConfig, summ);

      // Assign pure interface pointer to insure proper destruction and raw pointer for later use
      m_Results  = results;
      m_CResults = results;
   }

   void CombineLoadCase(BSTR loadCase, ForceEffectType effect, OptimizationType optimization, 
                        Float64 minFactor, Float64 maxFactor, IResult3Ds* loadCaseResults)
   {
      CHRException hr;
      // loop over all pois
      CollectionIndexType size = m_ComboFactors.size();
      for (CollectionIndexType i=0; i<size; i++)
      {
         CComPtr<IResult3D> res3d;
         hr = loadCaseResults->get_Item(i, &res3d);

         Float64 res;
         hr = res3d->GetSingleResult(effect, &res);

         ComboFactors& rcfactors = m_ComboFactors[i];

         Float64 factor;
         if (optimization == optMaximize)
         {
            if (res >= -ZERO_TOL)  // this is done to insure comparisons between dump files
            {
               factor = maxFactor * rcfactors.m_MaxLoadModifier;
               res *= factor;
            }
            else
            {
               factor = minFactor * rcfactors.m_MinLoadModifier;
               res *= factor;
            }
         }
         else
         {
            if (res <= ZERO_TOL)  // same comment as above
            {
               factor = maxFactor * rcfactors.m_MaxLoadModifier;
               res *= factor;
            }
            else
            {
               factor = minFactor * rcfactors.m_MinLoadModifier;
               res *= factor;
            }
         }

         // store configuration object if asked
         if (m_CreateConfig)
         {
            m_CResults->SumResult(i, loadCase, res, factor);
         }
         else
         {
            m_CResults->SumResultNoConfig(i, res);
         }
      }
   }

   void CombineLiveLoad(Float64 llFactor, OptimizationType optimization, ILiveLoadModelResults* llmResults)
   {
      CHRException hr;
      // loop over all pois
      CollectionIndexType size = m_ComboFactors.size();
      for (CollectionIndexType i=0; i<size; i++)
      {
         Float64 llresult;
         CComPtr<ILiveLoadConfiguration> llconfig;
         hr = llmResults->GetResult(i, &llresult, &llconfig);

         ComboFactors& rcfactors = m_ComboFactors[i];

         // always use max loadmodifier since optimized live load never decreases optimized value
         llFactor *= rcfactors.m_MaxLoadModifier;

         llresult  *= llFactor;

         if (m_CreateConfig)
         {
            m_CResults->SumLLResult(i, llresult, llconfig, llFactor);
         }
         else
         {
            m_CResults->SumResultNoConfig(i, llresult);
         }
      }
   }

   // our results
   CComPtr<ILoadCombinationResults> m_Results;

private:
   CLoadCombinationResults*         m_CResults; // need local access to results object
};

// Section based results
//////////////
class SectionLoadCombinationEngine: protected LoadCombinationEngineBase
{
   public:

   SectionLoadCombinationEngine(ILongArray* POIs, BSTR Stage, 
                         ResultsSummationType summ, LoadCombinationType lmType, 
                         IGetCombinationFactors* ifactors, bool createConfig, bool doFlip ):
   LoadCombinationEngineBase(POIs, Stage,  summ, lmType, ifactors, createConfig, true )
   {
      m_Flip = doFlip ? -1 : 1;

      CollectionIndexType numres = m_ComboFactors.size();
      CreateResults(numres, summ);
   }

   void CreateResults(CollectionIndexType numRes, ResultsSummationType summ)
   {
      CHRException hr;
      CComObject<CLoadCombinationSectionResults>* results;
      hr = CComObject<CLoadCombinationSectionResults>::CreateInstance(&results);
      results->AllocateResults(numRes, m_CreateConfig, summ);

      // Assign pure interface pointer to insure proper destruction and raw pointer for later use
      m_Results  = results;
      m_CResults = results;
   }

   void CombineLoadCase(BSTR loadCase, ForceEffectType effect, OptimizationType optimization, 
                        Float64 minFactor, Float64 maxFactor, ISectionResult3Ds* loadCaseResults)
   {
      CHRException hr;
      // loop over all pois
      CollectionIndexType size = m_ComboFactors.size();
      for (CollectionIndexType i=0; i<size; i++)
      {
         CComPtr<ISectionResult3D> res3d;
         hr = loadCaseResults->get_Item(i, &res3d);

         Float64 left_res, right_res;
         hr = res3d->GetSingleResult(effect, &left_res, &right_res);

         ComboFactors& rcfactors = m_ComboFactors[i];

         Float64 left_factor, right_factor;
         if (optimization == optMaximize)
         {
            // max positive left value and negative right value
            if (left_res > -ZERO_TOL)
            {
               left_factor = maxFactor * rcfactors.m_MaxLoadModifier;
               left_res *= left_factor;
            }
            else
            {
               left_factor = minFactor * rcfactors.m_MinLoadModifier;
               left_res *= left_factor;
            }

            if (m_Flip*right_res > -ZERO_TOL)
            {
               right_factor = maxFactor * rcfactors.m_MaxLoadModifier;
               right_res *= right_factor;
            }
            else
            {
               right_factor = minFactor * rcfactors.m_MinLoadModifier;
               right_res *= right_factor;
            }
         }
         else
         {
            // max negative left value and positive right value
            if (left_res < ZERO_TOL)
            {
               left_factor = maxFactor * rcfactors.m_MaxLoadModifier;
               left_res *= left_factor;
            }
            else
            {
               left_factor = minFactor * rcfactors.m_MinLoadModifier;
               left_res *= left_factor;
            }

            if (m_Flip*right_res < ZERO_TOL)
            {
               right_factor = maxFactor * rcfactors.m_MaxLoadModifier;
               right_res *= right_factor;
            }
            else
            {
               right_factor = minFactor * rcfactors.m_MinLoadModifier;
               right_res *= right_factor;
            }
         }

         // store configuration object if asked
         if (m_CreateConfig)
         {
            m_CResults->SumResult(i, loadCase, left_res, left_factor, right_res, right_factor);
         }
         else
         {
            m_CResults->SumResultNoConfig(i, left_res, right_res);
         }
      }
   }

   void CombineLiveLoad(Float64 llFactor, OptimizationType optimization, ILiveLoadModelSectionResults* llmResults)
   {
      CHRException hr;
      // loop over all pois
      CollectionIndexType size = m_ComboFactors.size();
      for (CollectionIndexType i=0; i<size; i++)
      {
         Float64 left_llresult, right_llresult;
         CComPtr<ILiveLoadConfiguration> left_llconfig, right_llconfig;
         hr = llmResults->GetResult(i, &left_llresult, &left_llconfig, &right_llresult, &right_llconfig);

         ComboFactors& rcfactors = m_ComboFactors[i];

         // always use max loadmodifier since optimized live load never decreases optimized value
         llFactor *= rcfactors.m_MaxLoadModifier;

         left_llresult  *= llFactor;
         right_llresult *= llFactor;

         if (m_CreateConfig)
         {
            m_CResults->SumLLResult(i, left_llresult, left_llconfig, right_llresult, right_llconfig, llFactor);
         }
         else
         {
            m_CResults->SumResultNoConfig(i, left_llresult, right_llresult);
         }
      }
   }

   // our results
   CComPtr<ILoadCombinationSectionResults> m_Results;

private:
   CLoadCombinationSectionResults*         m_CResults; // need local access to results object

   int m_Flip; // flip for force and deflection results
};

///////////////////////////////////////////
// CLoadCombinationResponseAgg
///////////////////////////////////////////

STDMETHODIMP CLoadCombinationResponseAgg::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ILoadCombinationResponse
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// ILoadCombinationResponse
STDMETHODIMP CLoadCombinationResponseAgg::ComputeForces(BSTR loadCombination, ILongArray* POIs, BSTR Stage, ResultsOrientation orientation, 
                                                       ResultsSummationType summ, ForceEffectType effect, OptimizationType optimization, 
                                                       VARIANT_BOOL includeLiveLoad,  VARIANT_BOOL includeImpact, VARIANT_BOOL computeConfig,
                                                       ILoadCombinationSectionResults** pResults)
{
   CHECK_IN(loadCombination);
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_RETOBJ(pResults);
   CHRException hr;
   try
   {
      *pResults = NULL;

      // make sure our combination table is up to date
      m_pCombiner->Validate();


      // get cached information for combo
      CLoadCombiner::LoadCombinationIterator lcit( m_pCombiner->m_LoadCombinations.find( CLoadCombiner::NameHolder(loadCombination) ) );
      if (lcit == m_pCombiner->m_LoadCombinations.end())
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCOMBO_NO_EXIST, loadCombination);
         THROW_LBAMC_MSG(LOADCOMBO_NO_EXIST, msg);
      }

      CLoadCombiner::ComboData& rcombo_data  = lcit->second;

      // create our load combination engine
      SectionLoadCombinationEngine lc_engine(POIs, Stage, summ, rcombo_data.m_LoadCombinationType, 
                                             m_pCombiner->m_pGetCombinationFactors, 
                                             computeConfig!=VARIANT_FALSE, true);

      CMB_HANDLE_CANCEL_PROGRESS();

      // loop over load case results and apply them to combination
      CollectionIndexType num_combos = rcombo_data.m_LoadCaseFactors.size();
      for (CollectionIndexType i_combo=0; i_combo<num_combos; i_combo++)
      {
         CLoadCombiner::ComboData::LoadCaseFactors& rfactors = rcombo_data.m_LoadCaseFactors[i_combo];

         CComPtr<ISectionResult3Ds> lc_results;
         hr = m_pCombiner->m_pLoadCaseResponse->ComputeForces(rfactors.m_LoadCaseName, POIs, Stage, 
                                                              orientation, summ, &lc_results);

         lc_engine.CombineLoadCase(rfactors.m_LoadCaseName, effect, optimization, 
                                   rfactors.m_MinFactor, rfactors.m_MaxFactor, lc_results);
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      // get live load results (factored by impact and distribution)
      bool is_liveload = includeLiveLoad == VARIANT_TRUE && 
                         rcombo_data.m_LiveLoadModels.size() != 0 &&
                         rcombo_data.m_LiveLoadFactor != 0.0;
      if (is_liveload)
      {
         std::vector<LiveLoadModelType>::iterator iter( rcombo_data.m_LiveLoadModels.begin() );
         std::vector<LiveLoadModelType>::iterator iterend( rcombo_data.m_LiveLoadModels.end() );
         for ( ; iter != iterend; iter++ )
         {
            LiveLoadModelType llt = *iter;
            if ( llt == lltNone )
               continue;

            CComPtr<ILiveLoadModelSectionResults> liveload_results;
            hr = m_pCombiner->m_pLiveLoadModelResponse->ComputeForces(POIs, Stage, llt, orientation, 
                                                        effect, optimization, vlcDefault, includeImpact, VARIANT_TRUE, computeConfig,
                                                        &liveload_results);
            CollectionIndexType ll_size;
            hr = liveload_results->get_Count(&ll_size);

            CMB_HANDLE_CANCEL_PROGRESS();

            if (ll_size>0)  // it's possible that no live load results exist for the given ll model
            {
               CollectionIndexType poisiz;
               hr = POIs->get_Count(&poisiz);
               ATLASSERT(ll_size==poisiz);

               lc_engine.CombineLiveLoad(rcombo_data.m_LiveLoadFactor, optimization, liveload_results);
            }
         }
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      return lc_engine.m_Results.CopyTo(pResults);

   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_ILoadCombinationResponse);
   }
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeDeflections(BSTR loadCombination, ILongArray* POIs, BSTR Stage,
                                                             ResultsSummationType summ, ForceEffectType effect, OptimizationType optimization, 
                                                             VARIANT_BOOL includeLiveLoad,  VARIANT_BOOL includeImpact, VARIANT_BOOL computeConfig,
                                                             ILoadCombinationSectionResults** pResults)
{
   CHECK_IN(loadCombination);
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_RETOBJ(pResults);
   CHRException hr;
   try
   {
      *pResults = NULL;

      // make sure our combination table is up to date
      m_pCombiner->Validate();

      // get cached information for combo
      CLoadCombiner::LoadCombinationIterator lcit( m_pCombiner->m_LoadCombinations.find( CLoadCombiner::NameHolder(loadCombination) ) );
      if (lcit == m_pCombiner->m_LoadCombinations.end())
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCOMBO_NO_EXIST, loadCombination);
         THROW_LBAMC_MSG(LOADCOMBO_NO_EXIST, msg);
      }

      CLoadCombiner::ComboData& rcombo_data  = lcit->second;

      // create our load combination engine
      SectionLoadCombinationEngine lc_engine(POIs, Stage, summ, rcombo_data.m_LoadCombinationType, 
                                      m_pCombiner->m_pGetCombinationFactors, computeConfig!=VARIANT_FALSE, false);

      CMB_HANDLE_CANCEL_PROGRESS();

      // loop over load case results and apply them to combination
      CollectionIndexType num_combos = rcombo_data.m_LoadCaseFactors.size();
      for (CollectionIndexType i_combo=0; i_combo<num_combos; i_combo++)
      {
         CLoadCombiner::ComboData::LoadCaseFactors& rfactors = rcombo_data.m_LoadCaseFactors[i_combo];

         CComPtr<ISectionResult3Ds> lc_results;
         hr = m_pCombiner->m_pLoadCaseResponse->ComputeDeflections(rfactors.m_LoadCaseName, POIs, Stage, 
                                                                   summ, &lc_results);

         lc_engine.CombineLoadCase(rfactors.m_LoadCaseName, effect, optimization, 
                                   rfactors.m_MinFactor, rfactors.m_MaxFactor, lc_results);
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      // get live load results (factored by impact but not distribution)
      bool is_liveload = includeLiveLoad == VARIANT_TRUE && 
                         rcombo_data.m_LiveLoadModels.size() != 0 &&
                         rcombo_data.m_LiveLoadFactor != 0.0;

      if (is_liveload)
      {
         std::vector<LiveLoadModelType>::iterator iter( rcombo_data.m_LiveLoadModels.begin() );
         std::vector<LiveLoadModelType>::iterator iterend( rcombo_data.m_LiveLoadModels.end() );
         for ( ; iter != iterend; iter++ )
         {
            LiveLoadModelType llt = *iter;
            if (llt == lltNone )
               continue;

            CComPtr<ILiveLoadModelSectionResults> liveload_results;
            hr = m_pCombiner->m_pLiveLoadModelResponse->ComputeDeflections(POIs, Stage, llt,
                                                        effect, optimization, vlcDefault, includeImpact, VARIANT_TRUE, computeConfig,
                                                        &liveload_results);

            CMB_HANDLE_CANCEL_PROGRESS();

            lc_engine.CombineLiveLoad(rcombo_data.m_LiveLoadFactor, optimization, liveload_results);
         }
      }

      return lc_engine.m_Results.CopyTo(pResults);

   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_ILoadCombinationResponse);
   }
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeReactions(BSTR loadCombination, ILongArray* POIs, BSTR Stage,
                                                           ResultsSummationType summ, ForceEffectType effect, 
                                                           OptimizationType optimization, 
                                                           VARIANT_BOOL includeLiveLoad,  VARIANT_BOOL includeImpact, VARIANT_BOOL computeConfig,
                                                           ILoadCombinationResults** pResults)
{
   CHECK_IN(loadCombination);
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_RETOBJ(pResults);
   CHRException hr;
   try
   {
      *pResults = NULL;

      // make sure our combination table is up to date
      m_pCombiner->Validate();

      // get cached information for combo
      CLoadCombiner::LoadCombinationIterator lcit( m_pCombiner->m_LoadCombinations.find( CLoadCombiner::NameHolder(loadCombination) ) );
      if (lcit == m_pCombiner->m_LoadCombinations.end())
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCOMBO_NO_EXIST, loadCombination);
         THROW_LBAMC_MSG(LOADCOMBO_NO_EXIST, msg);
      }

      CLoadCombiner::ComboData& rcombo_data  = lcit->second;

      // create our load combination engine
      LoadCombinationEngine lc_engine(POIs, Stage, summ, rcombo_data.m_LoadCombinationType, 
                                      m_pCombiner->m_pGetCombinationFactors, computeConfig!=VARIANT_FALSE, false);

      CMB_HANDLE_CANCEL_PROGRESS();

      // loop over load case results and apply them to combination
      CollectionIndexType num_combos = rcombo_data.m_LoadCaseFactors.size();
      for (CollectionIndexType i_combo=0; i_combo<num_combos; i_combo++)
      {
         CLoadCombiner::ComboData::LoadCaseFactors& rfactors = rcombo_data.m_LoadCaseFactors[i_combo];

         CComPtr<IResult3Ds> lc_results;
         hr = m_pCombiner->m_pLoadCaseResponse->ComputeReactions(rfactors.m_LoadCaseName, POIs, Stage, 
                                                                 summ, &lc_results);

         lc_engine.CombineLoadCase(rfactors.m_LoadCaseName, effect, optimization, 
                                   rfactors.m_MinFactor, rfactors.m_MaxFactor, lc_results);
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      // get live load results (factored by impact but not distribution)
      bool is_liveload = includeLiveLoad == VARIANT_TRUE && 
                         rcombo_data.m_LiveLoadModels.size() != 0 &&
                         rcombo_data.m_LiveLoadFactor != 0.0;

      if (is_liveload)
      {
         std::vector<LiveLoadModelType>::iterator iter( rcombo_data.m_LiveLoadModels.begin() );
         std::vector<LiveLoadModelType>::iterator iterend( rcombo_data.m_LiveLoadModels.end() );
         for (; iter != iterend; iter++ )
         {
            LiveLoadModelType llt = *iter;
            if ( llt == lltNone )
               continue;

            CComPtr<ILiveLoadModelResults> liveload_results;
            hr = m_pCombiner->m_pLiveLoadModelResponse->ComputeReactions(POIs, Stage, llt,
                                                        effect, optimization, vlcDefault, includeImpact, VARIANT_TRUE, computeConfig,
                                                        &liveload_results);

            CMB_HANDLE_CANCEL_PROGRESS();

            lc_engine.CombineLiveLoad(rcombo_data.m_LiveLoadFactor, optimization, liveload_results);
         }
      }

      return lc_engine.m_Results.CopyTo(pResults);

   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_ILoadCombinationResponse);
   }
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeSupportDeflections(BSTR loadCombination, ILongArray* POIs, BSTR Stage,
                                                           ResultsSummationType summ, ForceEffectType effect, 
                                                           OptimizationType optimization, 
                                                           VARIANT_BOOL includeLiveLoad, VARIANT_BOOL includeImpact,  VARIANT_BOOL computeConfig,
                                                           ILoadCombinationResults** pResults)
{
   CHECK_IN(loadCombination);
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_RETOBJ(pResults);
   CHRException hr;
   try
   {
      *pResults = NULL;

      // make sure our combination table is up to date
      m_pCombiner->Validate();

      // get cached information for combo
      CLoadCombiner::LoadCombinationIterator lcit( m_pCombiner->m_LoadCombinations.find( CLoadCombiner::NameHolder(loadCombination) ) );
      if (lcit == m_pCombiner->m_LoadCombinations.end())
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCOMBO_NO_EXIST, loadCombination);
         THROW_LBAMC_MSG(LOADCOMBO_NO_EXIST, msg);
      }

      CLoadCombiner::ComboData& rcombo_data  = lcit->second;

      // create our load combination engine
      LoadCombinationEngine lc_engine(POIs, Stage, summ, rcombo_data.m_LoadCombinationType, 
                                      m_pCombiner->m_pGetCombinationFactors, computeConfig!=VARIANT_FALSE, false);

      CMB_HANDLE_CANCEL_PROGRESS();

      // loop over load case results and apply them to combination
      CollectionIndexType num_combos = rcombo_data.m_LoadCaseFactors.size();
      for (CollectionIndexType i_combo=0; i_combo<num_combos; i_combo++)
      {
         CLoadCombiner::ComboData::LoadCaseFactors& rfactors = rcombo_data.m_LoadCaseFactors[i_combo];

         CComPtr<IResult3Ds> lc_results;
         hr = m_pCombiner->m_pLoadCaseResponse->ComputeSupportDeflections(rfactors.m_LoadCaseName, POIs, Stage, 
                                                                 summ, &lc_results);

         lc_engine.CombineLoadCase(rfactors.m_LoadCaseName, effect, optimization, 
                                   rfactors.m_MinFactor, rfactors.m_MaxFactor, lc_results);
      }

      CMB_HANDLE_CANCEL_PROGRESS();

      // get live load results (factored by impact but not distribution)
      bool is_liveload = includeLiveLoad == VARIANT_TRUE && 
                         rcombo_data.m_LiveLoadModels.size() != 0 &&
                         rcombo_data.m_LiveLoadFactor != 0.0;

      if (is_liveload)
      {
         std::vector<LiveLoadModelType>::iterator iter( rcombo_data.m_LiveLoadModels.begin() );
         std::vector<LiveLoadModelType>::iterator iterend( rcombo_data.m_LiveLoadModels.end() );
         for ( ; iter != iterend; iter++ )
         {
            LiveLoadModelType llt = *iter;
            if ( llt == lltNone )
               continue;

            CComPtr<ILiveLoadModelResults> liveload_results;
            hr = m_pCombiner->m_pLiveLoadModelResponse->ComputeSupportDeflections(POIs, Stage, llt,
                                                        effect, optimization, vlcDefault, includeImpact, VARIANT_TRUE, computeConfig,
                                                        &liveload_results);

            CMB_HANDLE_CANCEL_PROGRESS();

            lc_engine.CombineLiveLoad(rcombo_data.m_LiveLoadFactor, optimization, liveload_results);
         }
      }

      return lc_engine.m_Results.CopyTo(pResults);

   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_ILoadCombinationResponse);
   }
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeStresses(BSTR loadCombination, ILongArray* POIs, BSTR Stage,
                                                          ResultsSummationType summ, ForceEffectType effect, OptimizationType optimization, 
                                                          VARIANT_BOOL includeLiveLoad,  VARIANT_BOOL includeImpact, VARIANT_BOOL computeConfig,
                                                          ILoadCombinationStressResults** pResults)
{
   CHECK_IN(loadCombination);
   CHECK_IN(POIs);
   CHECK_IN(Stage);
   CHECK_RETOBJ(pResults);
   CHRException hr;
   try
   {
      *pResults = NULL;

      // need to get configuration from force response and use it to compute stresses
      CComPtr<ILoadCombinationSectionResults> force_res;
      hr = this->ComputeForces(loadCombination, POIs, Stage, roMember, summ, effect, 
                               optimization, includeLiveLoad, includeImpact, VARIANT_TRUE, &force_res);

     CMB_HANDLE_CANCEL_PROGRESS();

     return CombSectionToStressResults(POIs, Stage, force_res, 
                                        m_pCombiner->m_pConcurrentLoadCombinationResponse,  pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pCombiner, IID_ILoadCombinationResponse);
   }
}