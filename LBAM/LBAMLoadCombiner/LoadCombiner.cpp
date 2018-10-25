///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2011  Washington State Department of Transportation
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

// LoadCombiner.cpp : Implementation of CLoadCombiner
#include "stdafx.h"
#include "WBFLLBAMLoadCombiner.h"
#include "LoadCombiner.h"

#include "LBAMLoadCombiner.hh"
#include "LBAMLoadCombinerErrors.h"

#include "LoadCaseResponseAgg.h"
#include "LoadCombinationResponseAgg.h"
#include "ConcurrentLoadCombinationResponseAgg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadCombiner

STDMETHODIMP CLoadCombiner::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadCaseResponse,
		&IID_ILoadCombinationResponse,
		&IID_IConcurrentLoadCombinationResponse
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CLoadCombiner::FinalRelease()
{
   if (m_Context!=NULL)
   {
      HRESULT hr = CrUnadvise(m_Context, this, IID_ILoadCombinationAnalysisContextEvents, m_ContextCookie);
      ATLASSERT(SUCCEEDED(hr));
   }
}

HRESULT CLoadCombiner::FinalConstruct()
{
   HRESULT hr;
   // Create aggregated objects
   // For some undocumented reason, you must ask for iunknown when aggregating
   // LoadCase Response
   IUnknown* myiu = this->GetControllingUnknown();
   CComAggObject<CLoadCaseResponseAgg>* plc;
   hr = CComAggObject<CLoadCaseResponseAgg>::CreateInstance(myiu,&plc);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // tell our aggregate about us
   plc->m_contained.m_pCombiner = this;

   hr = plc->QueryInterface(IID_IUnknown, (void**)&m_pLoadCaseResponseAgg);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // our typed version for performance
   hr = plc->QueryInterface(IID_ILoadCaseResponse, (void**)&m_pLoadCaseResponse);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   this->Release();

   // LoadCombination Response
   CComAggObject<CLoadCombinationResponseAgg>* plcb;
   hr = CComAggObject<CLoadCombinationResponseAgg>::CreateInstance(myiu,&plcb);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // tell our aggregate about us
   plcb->m_contained.m_pCombiner = this;

   hr = plcb->QueryInterface(IID_IUnknown, (void**)&m_pLoadCombinationResponseAgg);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // ConcurrentLoadCombination Response
   CComAggObject<CConcurrentLoadCombinationResponseAgg>* pclcb;
   hr = CComAggObject<CConcurrentLoadCombinationResponseAgg>::CreateInstance(myiu,&pclcb);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // our typed version for performance
   hr = pclcb->QueryInterface(IID_IConcurrentLoadCombinationResponse, (void**)&m_pConcurrentLoadCombinationResponse);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   this->Release();

   // tell our aggregate about us
   pclcb->m_contained.m_pCombiner = this;

   hr = pclcb->QueryInterface(IID_IUnknown, (void**)&m_pConcurrentLoadCombinationResponseAgg);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   return S_OK;
}

// IDependOnLoadCombinationAnalysisContext
STDMETHODIMP CLoadCombiner::Initialize(/*[in]*/IUnknown* context)
{
   try
   {
      if (m_Context!= NULL)
      {
         // can only initialize once
         THROW_LBAMC(LC_INITIALIZATION);
      }

      m_Context = context;

      // listen to context for change events
      HRESULT hr = CrAdvise(m_Context, this, IID_ILoadCombinationAnalysisContextEvents, &m_ContextCookie);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return hr;
      }

      // pull some interfaces from context since we know we'll need them.
      CComQIPtr<ILiveLoadModelResponse> pllmr(context);
      if (pllmr!=NULL)
      {
         m_pLiveLoadModelResponse = pllmr;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMC(INVALID_LC_CONTEXT);
      }

      CComQIPtr<IBasicVehicularResponse> pbvr(context);
      if (pbvr!=NULL)
      {
         m_pBasicVehicularResponse = pbvr;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMC(INVALID_LC_CONTEXT);
      }

      CComQIPtr<ILoadGroupResponse> plgr(context);
      if (plgr!=NULL)
      {
         m_pLoadGroupResponse = plgr;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMC(INVALID_LC_CONTEXT);
      }

      CComQIPtr<IGetCombinationFactors> pcf(context);
      if (plgr!=NULL)
      {
         m_pGetCombinationFactors = pcf;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMC(INVALID_LC_CONTEXT);
      }

      CComQIPtr<IGetStressPoints> pgcs(context);
      if (plgr!=NULL)
      {
         m_pGetStressPoints = pgcs;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMC(INVALID_LC_CONTEXT);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

	return S_OK;
}

// ISupportProgressMonitor
STDMETHODIMP CLoadCombiner::InitializeProgressMonitor(IProgressMonitor * newVal, LONG cookie)
{
   CHECK_IN(newVal);

   m_pProgressMonitor = newVal;
   m_ProgressCookie = cookie;

   return S_OK;
}


HRESULT CLoadCombiner::GetStressPoints(long poiID, BSTR stage, IStressPoints* *leftSps, IStressPoints* *rightSps)
{
   CHECK_IN(stage);
   CHECK_RETOBJ(leftSps);
   CHECK_RETOBJ(rightSps);

   HRESULT hr;

   CComPtr<IStressPoints> left_sps, right_sps;
   hr = m_pGetStressPoints->GetStressPointsAtPOI(poiID, stage, &left_sps, &right_sps);
   if(FAILED(hr))
      return hr;

   ATLASSERT(left_sps!=0); 
   left_sps.CopyTo(leftSps);

   if (right_sps!=NULL)
      return right_sps.CopyTo(rightSps);
   else
      return left_sps.CopyTo(rightSps);
}


// ILoadCombinationAnalysisContextEvents 
STDMETHODIMP CLoadCombiner::OnCombinationChanged(ComboType ctype, BSTR combination)
{
   Invalidate();

	return S_OK;
}

STDMETHODIMP CLoadCombiner::OnResultsChanged()
{
   Invalidate();

	return S_OK;
}

void CLoadCombiner::Invalidate()
{
   m_LoadCases.clear();
   m_LoadCombinations.clear();

   m_IsValidated = false;
}

// this function must be called within a try block
void CLoadCombiner::Validate()
{
   if (!m_IsValidated)
   {
      ValidateLoadCases();

      ValidateLoadCombinations();

      m_IsValidated = true;
   }
}

STDMETHODIMP CLoadCombiner::GetActiveLoadCases(/*[out,retval]*/IBstrArray* *loadCases)
{
   CHECK_RETOBJ(loadCases);

   CHRException hr;

   try
   {
      Validate();

      CComPtr<IBstrArray> names;
      hr = names.CoCreateInstance(CLSID_BstrArray);

      LoadCaseList::iterator it( m_LoadCases.begin() );
      LoadCaseList::iterator itend( m_LoadCases.end() );
      for (; it!=itend; it++)
      {
         NameVec& load_grnms = it->second;
         if (! load_grnms.empty() )
         {
            const NameHolder& name = it->first;
            hr = names->Add( name.m_T );
         }
      }

      return names.CopyTo(loadCases);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

   return hr;
}


void CLoadCombiner::ValidateLoadCases()
{
   CHRException hr;
   // first latch onto load cases and see which load groups are active
   // get active load groups
   CComQIPtr<IGetActiveLoadGroups> palg(m_Context);
   if (palg==NULL)
   {
      ATLASSERT(0);
      THROW_LBAMC(INVALID_LC_CONTEXT);
   }

   CComPtr<IBstrArray> blgs;
   hr = palg->GetActiveLoadGroups(&blgs);

   // Get LoadCases and set up data structures so they only refer to active loadgroups
   CollectionIndexType lc_cnt;

   CComQIPtr<ILoadCases> load_cases(m_Context);
   if (load_cases==NULL)
   {
      ATLASSERT(0);
      THROW_LBAMC(INVALID_LC_CONTEXT);
   }

   hr = load_cases->get_Count(&lc_cnt);

   for (CollectionIndexType ilc=0; ilc<lc_cnt; ilc++)
   {
      CComPtr<ILoadCase> load_case;
      hr = load_cases->get_Item(ilc, &load_case);

      NameHolder lc_name;
      hr = load_case->get_Name(&(lc_name.m_T));

      // put load case into our list 
      NameVec empty_vec;
      std::pair<LoadCaseIterator, bool> insit( m_LoadCases.insert(LoadCaseList::value_type(lc_name, empty_vec)) );
      if (!insit.second)
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCASE_DUPLICATE, lc_name.m_T );
         THROW_LBAMC_MSG(LOADCASE_DUPLICATE, msg);
      }

      // latch on to current vector of loadgroups for this load case
      NameVec& rloadgroups = insit.first->second;

      CollectionIndexType lg_cnt;
      hr = load_case->get_LoadGroupCount(&lg_cnt);

      for (CollectionIndexType ilg=0; ilg<lg_cnt; ilg++)
      {
         CComBSTR lg_name;
         hr = load_case->GetLoadGroup(ilg, &lg_name);

         // see if loadgroup is in active list and add it to this load case if it is
         CollectionIndexType fidx;
         if (SUCCEEDED(blgs->Find(lg_name, &fidx)))
         {
            rloadgroups.push_back(lg_name);
         }
      }
   }
}

void CLoadCombiner::ValidateLoadCombinations()
{
   CHRException hr;

   // cache needed load combination information.

   CComQIPtr<ILoadCombinations> load_combos(m_Context);
   if (load_combos==NULL)
   {
      ATLASSERT(0);
      THROW_LBAMC(INVALID_LC_CONTEXT);
   }

   CollectionIndexType lc_cnt;
   hr = load_combos->get_Count(&lc_cnt);

   for (CollectionIndexType ilc=0; ilc<lc_cnt; ilc++)
   {
      CComPtr<ILoadCombination> load_combo;
      hr = load_combos->get_Item(ilc, &load_combo);

      NameHolder lcmb_name;
      hr = load_combo->get_Name(&(lcmb_name.m_T));

      // put load combo into our list 
      ComboData empty_vec;
      std::pair<LoadCombinationIterator, bool> insit( m_LoadCombinations.insert(LoadCombinationList::value_type(lcmb_name, empty_vec)) );
      if (!insit.second)
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADCOMBO_DUPLICATE, lcmb_name.m_T );
         THROW_LBAMC_MSG(LOADCOMBO_DUPLICATE, msg);
      }

      // latch on to current vector of loadcases for this load combo
      ComboData& rcombo_data = insit.first->second;

      // load combination type
      hr = load_combo->get_LoadCombinationType(&(rcombo_data.m_LoadCombinationType));

      // set up factors for live load
      hr = load_combo->get_LiveLoadFactor(&(rcombo_data.m_LiveLoadFactor));

      CollectionIndexType count;
      hr = load_combo->GetLiveLoadModelCount(&count);
      for ( CollectionIndexType i = 0; i < count; i++ )
      {
         LiveLoadModelType llt;
         hr = load_combo->GetLiveLoadModel(i,&llt);
         rcombo_data.m_LiveLoadModels.push_back(llt);
      }

      // get loadcase factors and keep only those load cases that have loadgroups associated
      CollectionIndexType lcf_cnt;
      hr = load_combo->get_LoadCaseFactorCount(&lcf_cnt);

      LoadCaseIterator lc_it_end( m_LoadCases.end());

      for (CollectionIndexType ilcf=0; ilcf<lcf_cnt; ilcf++)
      {
         CComBSTR lcs_name;
         Float64 min_factor, max_factor;
         hr = load_combo->GetLoadCaseFactor(ilcf, &lcs_name, &min_factor, &max_factor);

         LoadCaseIterator lc_it( m_LoadCases.find(lcs_name) );
         if (lc_it != lc_it_end)
         {
            // see if load case has any associated load groups. Add case only if it does
            NameVec& rloadgroups = lc_it->second;

            if (!rloadgroups.empty())
            {
               rcombo_data.m_LoadCaseFactors.push_back(ComboData::LoadCaseFactors(lcs_name, min_factor, max_factor));
            }
         }
         else
         {
            // combination references a loadcase that doesn't exist
            CComBSTR msg = CreateErrorMsg2S(IDS_E_INVALID_CASE_COMBO, lcmb_name.m_T, lcs_name );
            THROW_LBAMC_MSG(INVALID_CASE_COMBO, msg);
         }
      }
   }
}
