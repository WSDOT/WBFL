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

// LoadCombinationAnalysisContext.cpp : Implementation of CLoadCombinationAnalysisContext
#include "stdafx.h"
#include "WBFLLBAMLoadCombiner.h"
#include "LBAM.hh"
#include "LBAMLoadCombiner.hh"
#include "LBAMLoadCombinerErrors.h"
#include "LoadCombinationAnalysisContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationAnalysisContext

STDMETHODIMP CLoadCombinationAnalysisContext::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadCombinationAnalysisContext
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CLoadCombinationAnalysisContext::FinalConstruct()
{
   HRESULT hr;
   // Create aggregated objects
   // for some undocumented reason, you must ask for iunknown when aggregating
   // Load Cases
   IUnknown* myiu = this->GetControllingUnknown();
   CComAggObject<CLoadCasesAgg>* plc;
   hr = CComAggObject<CLoadCasesAgg>::CreateInstance(myiu,&plc);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // assign both pointers
   m_pLoadCasesAgg = plc;

   hr = plc->QueryInterface(IID_IUnknown, (void**)&m_pLoadCases);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // Stages
   CComAggObject<CStagesAgg>* pstg;
   hr = CComAggObject<CStagesAgg>::CreateInstance(myiu,&pstg);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // assign both pointers
   m_pStagesAgg = pstg;

   hr = pstg->QueryInterface(IID_IUnknown, (void**)&m_pStages);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // Load Combinations
   CComAggObject<CLoadCombinationsAgg>* plcb;
   hr = CComAggObject<CLoadCombinationsAgg>::CreateInstance(myiu,&plcb);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // assign both pointers
   m_pLoadCombinationsAgg = plcb;

   hr = plcb->QueryInterface(IID_IUnknown, (void**)&m_pLoadCombinations);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   return S_OK;
}


void CLoadCombinationAnalysisContext::FinalRelease()
{
   HRESULT hr;

   // unwire events
   if (m_pModel!=NULL)
   {
      hr = CrUnadvise(m_pModel, this, IID_ILBAMModelEvents, m_ModelEventsCookie);
      ATLASSERT(SUCCEEDED(hr));

      hr = CrUnadvise(m_pLoadCasesAgg->m_contained.m_LoadCases, this, IID_ILoadCasesEvents, m_LoadCasesEventsCookie);
      ATLASSERT(SUCCEEDED(hr));

      hr = CrUnadvise(m_pLoadCombinationsAgg->m_contained.m_LoadCombinations, this, IID_ILoadCombinationsEvents, m_LoadCombinationsEventsCookie);
      ATLASSERT(SUCCEEDED(hr));
   }
}

STDMETHODIMP CLoadCombinationAnalysisContext::Initialize(ILBAMModel *model, ILoadGroupResponse *loadGroupResponse, 
                                                         ILiveLoadModelResponse *liveLoadModelResponse, /*[in]*/IBasicVehicularResponse* basicVres, 
                                                         IAnalysisPOIs* pois, IGetStressPoints* stressPoints)
{
	CHECK_IN(model);
	CHECK_IN(loadGroupResponse);
	CHECK_IN(liveLoadModelResponse);
	CHECK_IN(pois);

   try
   {
      CHRException hr;

      if (m_pModel != NULL)
      {
         // can only initialize once
         THROW_LBAMC(LC_INITIALIZATION);
      }

      // set up model and connections to load cases and combinations
      m_pModel = model;

      // Set up influence lines and contraflexure
      m_pLoadGroupResponse      = loadGroupResponse;
      m_pBasicVehicularResponse = basicVres;
      m_pLiveLoadModelResponse  = liveLoadModelResponse;
      m_pAnalysisPOIs           = pois;
      m_pGetStressPoints        = stressPoints;

      // listen to model
      hr = CrAdvise(m_pModel, this, IID_ILBAMModelEvents, &m_ModelEventsCookie);

      // TRICKY: ILoadCases and ILoadCombinations have to be treated as aggregates because they have functions
      //         with the same names.

      // Load Cases
      CComPtr<ILoadCases> plcs;
      hr = m_pModel->get_LoadCases(&plcs);

      m_pLoadCasesAgg->m_contained.m_LoadCases = plcs;

      hr = CrAdvise(plcs, this, IID_ILoadCasesEvents, &m_LoadCasesEventsCookie);

      // Stages
      CComPtr<IStages> pstgs;
      hr = m_pModel->get_Stages(&pstgs);

      m_pStagesAgg->m_contained.m_Stages = pstgs;

      // Load Combinations
      CComPtr<ILoadCombinations> plcbs;
      hr = m_pModel->get_LoadCombinations(&plcbs);

      m_pLoadCombinationsAgg->m_contained.m_LoadCombinations = plcbs;

      hr = CrAdvise(plcbs, this, IID_ILoadCombinationsEvents, &m_LoadCombinationsEventsCookie);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCombinationAnalysisContext);
   }

   return S_OK;
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeForces(BSTR LoadGroup, ILongArray* poiIDs, BSTR Stage, ResultsOrientation orientation, ResultsSummationType summ, ISectionResult3Ds** results)
{
   return m_pLoadGroupResponse->ComputeForces(LoadGroup, poiIDs, Stage, orientation, summ, results);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeDeflections(BSTR LoadGroup, ILongArray* poiIDs, BSTR Stage, ResultsSummationType summ, ISectionResult3Ds** results)
{
   return m_pLoadGroupResponse->ComputeDeflections(LoadGroup, poiIDs, Stage, summ, results);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeReactions(BSTR LoadGroup, ILongArray* supportIDs, BSTR Stage,ResultsSummationType summ,IResult3Ds** results)
{
   return m_pLoadGroupResponse->ComputeReactions(LoadGroup, supportIDs, Stage, summ, results);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeSupportDeflections(BSTR LoadGroup, ILongArray* supportIDs, BSTR Stage, ResultsSummationType summ, IResult3Ds** results)
{
   return m_pLoadGroupResponse->ComputeSupportDeflections( LoadGroup, supportIDs, Stage, summ, results);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeStresses(BSTR LoadGroup, ILongArray* poiIDs, BSTR Stage, ResultsSummationType summ, ISectionStressResults **results)
{
   return m_pLoadGroupResponse->ComputeStresses(LoadGroup, poiIDs, Stage, summ, results);
}


// ILiveLoadModelResponse
STDMETHODIMP CLoadCombinationAnalysisContext::ComputeForces(ILongArray* poiIDs, BSTR stage, LiveLoadModelType type,  
                                                            ResultsOrientation orientation, ForceEffectType effect, 
                                                            OptimizationType optimization, 
                                                            VehicularLoadConfigurationType vehConfiguration, 
                                                            VARIANT_BOOL applyImpact,  VARIANT_BOOL applyDistribution,
                                                            VARIANT_BOOL computePlacement, ILiveLoadModelSectionResults** results)
{
   return m_pLiveLoadModelResponse->ComputeForces(poiIDs, stage, type, orientation, effect,  optimization, vehConfiguration, 
                                                  applyImpact, applyDistribution, computePlacement, results);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeDeflections(ILongArray* poiIDs, BSTR stage, LiveLoadModelType type,  
                                                                 ForceEffectType effect, 
                                                                 OptimizationType optimization, 
                                                                 VehicularLoadConfigurationType vehConfiguration, 
                                                                 VARIANT_BOOL applyImpact,  VARIANT_BOOL applyDistribution,
                                                                 VARIANT_BOOL computePlacement, ILiveLoadModelSectionResults** results)
{
   return m_pLiveLoadModelResponse->ComputeDeflections(poiIDs, stage, type, effect,  optimization, vehConfiguration, 
                                                       applyImpact, applyDistribution, computePlacement, results);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeReactions(ILongArray* supportIDs, BSTR stage, LiveLoadModelType type,  
                                                               ForceEffectType effect, 
                                                               OptimizationType optimization, 
                                                               VehicularLoadConfigurationType vehConfiguration, 
                                                               VARIANT_BOOL applyImpact,  VARIANT_BOOL applyDistribution,
                                                               VARIANT_BOOL computePlacement, ILiveLoadModelResults** results)
{
   return m_pLiveLoadModelResponse->ComputeReactions(supportIDs, stage, type, effect,  optimization, vehConfiguration, 
                                                     applyImpact, applyDistribution, computePlacement, results);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeSupportDeflections(ILongArray* supportIDs, BSTR stage, LiveLoadModelType type,  
                                                               ForceEffectType effect, 
                                                               OptimizationType optimization, 
                                                               VehicularLoadConfigurationType vehConfiguration, 
                                                               VARIANT_BOOL applyImpact,  VARIANT_BOOL applyDistribution,
                                                               VARIANT_BOOL computePlacement, ILiveLoadModelResults** results)
{
   return m_pLiveLoadModelResponse->ComputeSupportDeflections(supportIDs, stage, type, effect,  optimization, vehConfiguration, 
                                                     applyImpact, applyDistribution, computePlacement, results);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeStresses(ILongArray* poiIDs, BSTR stage, LiveLoadModelType type,  
                                                              ForceEffectType effect, 
                                                              OptimizationType optimization, 
                                                              VehicularLoadConfigurationType vehConfiguration, 
                                                              VARIANT_BOOL applyImpact,  VARIANT_BOOL applyDistribution,
                                                              VARIANT_BOOL computePlacement, ILiveLoadModelStressResults** results)
{
   return m_pLiveLoadModelResponse->ComputeStresses(poiIDs, stage, type, effect,  optimization, vehConfiguration, 
                                                    applyImpact, applyDistribution, computePlacement, results);
}

// IBasicVehicularResponse
STDMETHODIMP CLoadCombinationAnalysisContext::ComputeForces(ILongArray* poiIDs, BSTR stage, ResultsOrientation orientation,
                                                            ILiveLoadConfiguration* config, ISectionResult3Ds* *results)
{
   return m_pBasicVehicularResponse->ComputeForces(poiIDs, stage, orientation, config, results);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeDeflections(ILongArray* poiIDs, BSTR stage,
                                                                 ILiveLoadConfiguration* config, ISectionResult3Ds* *results)
{
   return m_pBasicVehicularResponse->ComputeDeflections(poiIDs, stage, config, results);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeReactions(ILongArray* supportIDs, BSTR stage,
                                                               ILiveLoadConfiguration* config, IResult3Ds* *pResults)
{
   return m_pBasicVehicularResponse->ComputeReactions(supportIDs, stage, config, pResults);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeSupportDeflections(ILongArray* supportIDs, BSTR stage,
                                                               ILiveLoadConfiguration* config, IResult3Ds* *pResults)
{
   return m_pBasicVehicularResponse->ComputeSupportDeflections(supportIDs, stage, config, pResults);
}

STDMETHODIMP CLoadCombinationAnalysisContext::ComputeStresses(ILongArray* poiIDs, BSTR stage,
                                                               ILiveLoadConfiguration* config, ISectionStressResults* *pResults)
{
   return m_pBasicVehicularResponse->ComputeStresses(poiIDs, stage, config, pResults);
}

////// IGetActiveLoadGroups

STDMETHODIMP CLoadCombinationAnalysisContext::GetActiveLoadGroups(IBstrArray* *pVal)
{
   CComQIPtr<IGetActiveLoadGroups> algs(m_pLoadGroupResponse);
   ATLASSERT(algs!=NULL);

   return algs->GetActiveLoadGroups(pVal);
}

// IGetCombinationFactors
STDMETHODIMP CLoadCombinationAnalysisContext::GetPOICombinationFactors(PoiIDType POI, BSTR Stage,LoadCombinationType type, Float64* minLoadModifier, Float64* maxLoadModifier)
{
   CHRException hr;

   try
   {
      Validate();

      // latch onto pois
      MemberType mbr_type;
      MemberIDType mbr_id;
      Float64 mbr_loc;
      hr = this->GetPoiInfo(Stage, POI, &mbr_type, &mbr_id, &mbr_loc);

      // get LoadModifier
      this->GetLoadModifier(mbr_type, mbr_id, mbr_loc, type, minLoadModifier, maxLoadModifier );

   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCombinationAnalysisContext);
   }

   return S_OK;
}

STDMETHODIMP CLoadCombinationAnalysisContext::GetSupportCombinationFactors(SupportIDType supportID, BSTR Stage,LoadCombinationType type, Float64* minLoadModifier, Float64* maxLoadModifier)
{
   CHRException hr;

   try
   {
      Validate();

      // see if we asked for a support
      CComPtr<ISupports> supports;
      hr = m_pModel->get_Supports(&supports);

      SupportIndexType nSupports;
      hr = supports->get_Count(&nSupports);

      if (0 <= supportID && supportID < (SupportIDType)nSupports )
      {
         CComPtr<ISupport> support;
         hr = supports->get_Item(supportID, &support);

         hr = support->GetLoadModifier(type, minLoadModifier, maxLoadModifier);
      }
      else
      {
         // supportID is < 0, might be a temporary support
         SpanIndexType spanIdx;
         CComPtr<ITemporarySupport> temporary_support;
         FindTemporarySupport(m_pModel, supportID, &temporary_support, &spanIdx);

         if (temporary_support!=NULL) 
         {
            hr = temporary_support->GetLoadModifier(type, minLoadModifier, maxLoadModifier);
         }
         else
         {
            // no support here by that name
            CComBSTR msg = ::CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, supportID);
            THROW_LBAMC_MSG(SUPPORT_NOT_EXIST,msg);
         }
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCombinationAnalysisContext);
   }

   return S_OK;
}


///////////////////////////////////////////////////////////////
////// IAnalysisPOIs
///////////////////////////////////////////////////////////////

HRESULT CLoadCombinationAnalysisContext::get_SpanPoiIncrement( PoiIDType *pVal)
{
   return m_pAnalysisPOIs->get_SpanPoiIncrement( pVal);
}

HRESULT CLoadCombinationAnalysisContext::put_SpanPoiIncrement( PoiIDType newVal)
{
   return m_pAnalysisPOIs->put_SpanPoiIncrement( newVal);
}

HRESULT CLoadCombinationAnalysisContext::get_CantileverPoiIncrement(PoiIDType *pVal)
{
   return m_pAnalysisPOIs->get_CantileverPoiIncrement( pVal);
}

HRESULT CLoadCombinationAnalysisContext::put_CantileverPoiIncrement( PoiIDType newVal)
{
   return m_pAnalysisPOIs->put_CantileverPoiIncrement(newVal);
}

HRESULT CLoadCombinationAnalysisContext::GetSuperstructurePois(BSTR stage, ILongArray** poiIDs, IDblArray** poiLocations)
{
   return m_pAnalysisPOIs->GetSuperstructurePois(stage, poiIDs, poiLocations);
}

HRESULT CLoadCombinationAnalysisContext::GetPoiInfo(BSTR stage, PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* memberLocation)
{
   return m_pAnalysisPOIs->GetPoiInfo(stage, poiID, lbamMemberType, memberID, memberLocation);
}

///////////////////////////////////////////////////////////////
// GetStressPointss
///////////////////////////////////////////////////////////////
STDMETHODIMP CLoadCombinationAnalysisContext::GetStressPointsAtPOI(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out]*/IStressPoints* *leftSps,  /*[out]*/IStressPoints* *rightSps)
{
   return m_pGetStressPoints->GetStressPointsAtPOI(poiID, stage, leftSps, rightSps);
}


// ILBAMModelEvents
STDMETHODIMP CLoadCombinationAnalysisContext::OnModelChanged(ILBAMModel* Model, ChangeType change)
{
   CHRException hr;
   try
   {
      // a few things we dont care about
      if (change!=cgtDescription || change!=cgtUserItemData)
      {
         // our LoadModifiers may have changed
         Invalidate();

         // most live load combo events are handled in OnLiveLoadChanged below except for the case where the entire 
         // ILoadCases or ILoadCombinations object is swapped out of the model. This requires more draconian measures

         // first check if the LoadCombinations were swapped out
         CComPtr<ILoadCombinations> plcbs;
         hr = m_pModel->get_LoadCombinations(&plcbs);

         if (!plcbs.IsEqualObject(m_pLoadCombinationsAgg->m_contained.m_LoadCombinations))
         {
            // entire combo was swapped out
            hr = CrUnadvise(m_pLoadCombinationsAgg->m_contained.m_LoadCombinations, this, IID_ILoadCombinationsEvents, m_LoadCombinationsEventsCookie);

            m_pLoadCombinationsAgg->m_contained.m_LoadCombinations = plcbs;

            hr = CrAdvise(plcbs, this, IID_ILoadCombinationsEvents, &m_LoadCombinationsEventsCookie);

            // have to assume at this point that all is hosed.
            Fire_OnCombinationChanged(ctLoadCombination,CComBSTR("*"));
         }

         // Check if the LoadCases were swapped out
         CComPtr<ILoadCases> plcs;
         hr = m_pModel->get_LoadCases(&plcs);

         if (!plcs.IsEqualObject(m_pLoadCasesAgg->m_contained.m_LoadCases))
         {
            hr = CrUnadvise(m_pLoadCasesAgg->m_contained.m_LoadCases, this, IID_ILoadCasesEvents, m_LoadCasesEventsCookie);

            m_pLoadCasesAgg->m_contained.m_LoadCases = plcs;

            hr = CrAdvise(plcs, this, IID_ILoadCasesEvents, &m_LoadCasesEventsCookie);

            // have to assume at this point that all is hosed.
            Fire_OnCombinationChanged(ctLoadCase,CComBSTR("*"));
         }

         Fire_OnResultsChanged();
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCombinationAnalysisContext);
   }

   return S_OK;
}


// ILoadCasesEvents
STDMETHODIMP CLoadCombinationAnalysisContext::OnLoadCasesChanged(ILoadCase* item, ChangeType change)
{
   CComBSTR name;
   item->get_Name(&name);
   Fire_OnCombinationChanged(ctLoadCase, name);

   return S_OK;
}

STDMETHODIMP CLoadCombinationAnalysisContext::OnLoadCasesRenamed(BSTR oldName, BSTR newName)
{
   Fire_OnCombinationChanged(ctLoadCase, oldName);

   return S_OK;
}

STDMETHODIMP CLoadCombinationAnalysisContext::OnLoadCasesAdded(ILoadCase* item)
{
   CComBSTR name;
   item->get_Name(&name);
   Fire_OnCombinationChanged(ctLoadCase, name);

   return S_OK;
}

STDMETHODIMP CLoadCombinationAnalysisContext::OnLoadCasesBeforeRemove(ILoadCase* item)
{
   CComBSTR name;
   item->get_Name(&name);
   Fire_OnCombinationChanged(ctLoadCase, name);

   return S_OK;
}

// ILoadCombinationsEvents
STDMETHODIMP CLoadCombinationAnalysisContext::OnLoadCombinationsChanged(ILoadCombination* item, ChangeType change)
{
   CComBSTR name;
   item->get_Name(&name);
   Fire_OnCombinationChanged(ctLoadCombination, name);

   return S_OK;
}

STDMETHODIMP CLoadCombinationAnalysisContext::OnLoadCombinationsRenamed(BSTR oldName, BSTR newName)
{
   Fire_OnCombinationChanged(ctLoadCombination, oldName);

   return S_OK;
}

STDMETHODIMP CLoadCombinationAnalysisContext::OnLoadCombinationsAdded(ILoadCombination* item)
{
   CComBSTR name;
   item->get_Name(&name);
   Fire_OnCombinationChanged(ctLoadCombination, name);

   return S_OK;
}

STDMETHODIMP CLoadCombinationAnalysisContext::OnLoadCombinationsBeforeRemove(ILoadCombination* item)
{
   CComBSTR name;
   item->get_Name(&name);
   Fire_OnCombinationChanged(ctLoadCombination, name);

   return S_OK;
}

////////////////////////////////////////
/// our privates
/////////////////////////////////////////
void CLoadCombinationAnalysisContext::Invalidate()
{
   m_IsValidated = false;
}

// compute our cached data
void CLoadCombinationAnalysisContext::Validate()
{
   if (!m_IsValidated)
   {
      // compute locations of ends of spans needed later
      ComputeSpanEnds();

      // now we're up to date
      m_IsValidated = true;
   }
}

void CLoadCombinationAnalysisContext::GetLoadModifier(MemberType mbrType, MemberIDType mbrID, Float64 mbrLocation, LoadCombinationType type, Float64* minFactor, Float64* maxFactor)
{
   CHRException hr;
   switch (mbrType)
   {
   case mtSpan:
      {
         CComPtr<ISpans> spans;
         hr = m_pModel->get_Spans(&spans);

         CComPtr<ISpan> span;
         hr = spans->get_Item(mbrID, &span);

         hr = span->GetLoadModifier(type, minFactor, maxFactor);
      }
      break;
   case mtSuperstructureMember:
      {
         // superstructuremembers do not have a LoadModifier associated with them
         // we need to use the closest span
         Float64 xloc, yloc;
         hr = m_pModel->ComputeLocation(mbrID, mbrType, mbrLocation, &xloc, &yloc);

         long span_no=0;
         bool found = false;
         std::vector<Float64>::iterator its( m_SpanEnds.begin() );
         std::vector<Float64>::iterator itsend( m_SpanEnds.end() );
         for (; its!=itsend; its++)
         {
            Float64 loc = *its;
            if (xloc<= loc)
            {
               found = true;
               break;
            }
            else
               span_no++;
         }

         if (!found) 
            span_no--; // assume on overhang

         // have span number - get factors using span
         this->GetLoadModifier(mtSpan, span_no, 0.0, type, minFactor, maxFactor);
      }
      break;
   case mtSupport:
      {
         CComPtr<ISupports> supports;
         hr = m_pModel->get_Supports(&supports);

         CComPtr<ISupport> support;
         hr = supports->get_Item(mbrID, &support);
         hr = support->GetLoadModifier(type, minFactor, maxFactor);
      }
      break;
   case mtTemporarySupport:
      {
         SpanIndexType spanno;
         CComPtr<ITemporarySupport> temporary_support;
         FindTemporarySupport(m_pModel, mbrID, &temporary_support, &spanno);

         if (temporary_support!=NULL) 
         {
            hr = temporary_support->GetLoadModifier(type, minFactor, maxFactor);
         }
         else
         {
            CComBSTR msg = ::CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, mbrID);
            THROW_LBAMC_MSG(SUPPORT_NOT_EXIST,msg);
         }
      }
      break;
   default:
      {
         THROW_LBAMC(POI_INVALID_MBR);
      }
      break;
   };
}

void CLoadCombinationAnalysisContext::ComputeSpanEnds()
{
   CHRException hr;

   m_SpanEnds.clear();

   CComPtr<ISpans> spans;
   hr = m_pModel->get_Spans(&spans);

   SpanIndexType span_cnt;
   hr = spans->get_Count(&span_cnt);

   Float64 loc = 0.0;
   for (SpanIndexType ispan=0; ispan<span_cnt; ispan++)
   {
      CComPtr<ISpan> span;
      hr = spans->get_Item(ispan, &span);

      Float64 length;
      hr = span->get_Length(&length);

      loc += length;

      m_SpanEnds.push_back(loc);
   }
}
