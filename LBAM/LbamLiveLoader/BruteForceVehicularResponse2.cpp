///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2013  Washington State Department of Transportation
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

// BruteForceVehicularResponse2.cpp : Implementation of CBruteForceVehicularResponse2
#include "stdafx.h"
#include <Float.h>

#include "WBFLLBAMLiveLoader.h"
#include "BruteForceVehicularResponse2.h"
#include "LiveLoadModelSectionResults.h"
#include "LiveLoadModelResults.h"
#include "LiveLoadConfiguration.h"
#include "BasicVehicularResponse.h"

#include "LBAMLiveLoader.hh"
#include "Truck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// handle dealing with cancel from progress monitor
#define HANDLE_CANCEL_PROGRESS() if (this->CheckForCancel()) throw S_FALSE;

// class for maximizing
MaxLLCompare::MaxLLCompare() : iLLCompare()
{
}

MaxLLCompare::MaxLLCompare(const MaxLLCompare& other) :
iLLCompare(other)
{
}

bool MaxLLCompare::DoCompare(Float64 newVal, Float64 oldVal)
{
   return newVal>oldVal;
}

iLLCompare* MaxLLCompare::Clone()
{ 
   return new MaxLLCompare(*this); 
}

// class for minimizing
MinLLCompare::MinLLCompare() : 
iLLCompare()
{
}

MinLLCompare::MinLLCompare(const MinLLCompare& other) :
iLLCompare(other)
{
}

bool MinLLCompare::DoCompare(Float64 newVal, Float64 oldVal)
{
   return newVal<oldVal;
}

iLLCompare* MinLLCompare::Clone()
{ 
   return new MinLLCompare(*this); 
}


InflResponseRecord::InflResponseRecord(PoiIDType poiID,LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                                       VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                                       iLLCompare* pLeftCompare, iLLCompare* pRightCompare)
{
   Init(poiID,type,vehicleIndex,effect,optimization,vehConfiguration,doApplyImpact,pLeftCompare,pRightCompare);
}

InflResponseRecord::InflResponseRecord(const InflResponseRecord& other)
{
   Init(other.m_PoiID,other.m_Type,other.m_VehicleIndex,other.m_Effect,other.m_Optimization,other.m_VehConfiguration,other.m_doApplyImpact,other.m_pLeftCompare,other.m_pRightCompare);
}

InflResponseRecord::~InflResponseRecord()
{
   delete m_pLeftCompare;
   delete m_pRightCompare;
}

void InflResponseRecord::Init(PoiIDType poiID,LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                              VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                              iLLCompare* pLeftCompare, iLLCompare* pRightCompare)
{
   m_PoiID            = poiID;
   m_Type             = type;
   m_VehicleIndex     = vehicleIndex;
   m_Effect           = effect;
   m_Optimization     = optimization;
   m_VehConfiguration = vehConfiguration;
   m_doApplyImpact    = doApplyImpact;

   if ( pLeftCompare )
      m_pLeftCompare = pLeftCompare->Clone();
   else
      m_pLeftCompare = 0;

   if ( pRightCompare )
      m_pRightCompare = pRightCompare->Clone();
   else
      m_pRightCompare = 0;
}

bool InflResponseRecord::operator<(const InflResponseRecord& other) const
{
   if ( m_PoiID < other.m_PoiID )
      return true;

   if ( other.m_PoiID < m_PoiID )
      return false;

   if ( m_Type < other.m_Type )
      return true;

   if ( other.m_Type < m_Type )
      return false;

   if ( m_VehicleIndex < other.m_VehicleIndex )
      return true;

   if ( other.m_VehicleIndex < m_VehicleIndex )
      return false;

   if ( m_Effect < other.m_Effect )
      return true;

   if ( other.m_Effect < m_Effect )
      return false;

   if ( m_Optimization < other.m_Optimization )
      return true;

   if ( other.m_Optimization < m_Optimization )
      return false;
   
   if ( m_VehConfiguration < other.m_VehConfiguration )
      return true;
   
   if ( other.m_VehConfiguration < m_VehConfiguration )
      return false;

   if ( m_doApplyImpact < other.m_doApplyImpact )
      return true;

   if ( other.m_doApplyImpact < m_doApplyImpact )
      return false;

   return false;
}

InflResponseRecord& InflResponseRecord::operator=(const InflResponseRecord& other)
{
   Init(other.m_PoiID,other.m_Type,other.m_VehicleIndex,other.m_Effect,other.m_Optimization,other.m_VehConfiguration,other.m_doApplyImpact,other.m_pLeftCompare,other.m_pRightCompare);
   return *this;
}

///////////////////////////////////////////////////////
// free functions
inline void ConfigureLaneConfig(ILiveLoadConfiguration* llConfig, LiveLoadModelType type, VehicleIndexType vehicleIndex, VehicularLoadConfigurationType Config, 
                             ForceEffectType forceEffect, OptimizationType optimization,
                             VARIANT_BOOL doApplyImpact)
{
   llConfig->put_IsApplicable(VARIANT_TRUE);
   llConfig->put_LiveLoadModel(type);
   llConfig->put_VehicleIndex(vehicleIndex);
   llConfig->put_VehicularLoadConfiguration(Config);
   llConfig->put_ForceEffect(forceEffect);
   llConfig->put_Optimization(optimization);

   llConfig->put_TruckDirection(ltdForward);
   llConfig->put_TruckPosition(0.0);
   llConfig->put_VariableSpacing(0.0);

   llConfig->put_DoApplyImpact(doApplyImpact);
}

inline void LLSectionToRes(ILiveLoadModelSectionResults* secRes, OptimizationType optimization, ILiveLoadModelResults* *Res)
{
   CHRException hr;

   CollectionIndexType ressize;
   hr = secRes->get_Count(&ressize);

   CComObject<CLiveLoadModelResults>* cresults;
   CComObject<CLiveLoadModelResults>::CreateInstance(&cresults);
   CComPtr<ILiveLoadModelResults> results(cresults);
   hr = results->Reserve(ressize);

   for (CollectionIndexType is=0; is<ressize; is++)
   {
      Float64 left_val, right_val;
      CComPtr<ILiveLoadConfiguration> left_config, right_config;
      hr = secRes->GetResult(is, &left_val, &left_config, &right_val, &right_config);

      if (optimization==optMaximize)
      {
         if (left_val>right_val)
         {
            hr = results->Add(left_val, left_config);
         }
         else
         {
            hr = results->Add(right_val, right_config);
         }
      }
      else
      {
         if (left_val<right_val)
         {
            hr = results->Add(left_val, left_config);
         }
         else
         {
            hr = results->Add(right_val, right_config);
         }
      }
   }

   hr = results.CopyTo(Res);
}

static Float64 GetMinSpanLength(ISupportLocations* suppLocs)
{
   CHRException hr;

   CComPtr<IDblArray> supp_locs;
   hr = suppLocs->get_SupportLocations(&supp_locs);

   Float64 min_length = DBL_MAX;
   CollectionIndexType num_supps;
   hr = supp_locs->get_Count(&num_supps);
   Float64 start_loc;
   hr = supp_locs->get_Item(0, &start_loc);
   for (CollectionIndexType i=1; i<num_supps; i++)
   {
      Float64 end_loc;
      hr = supp_locs->get_Item(i, &end_loc);
      Float64 span_length = end_loc-start_loc;
      min_length = min(min_length, span_length);

      start_loc = end_loc;
   }

   ATLASSERT(min_length>0.0);

   return min_length;
}

static Float64 GetMaxSpanLength(ISupportLocations* suppLocs)
{
   CHRException hr;

   CComPtr<IDblArray> supp_locs;
   hr = suppLocs->get_SupportLocations(&supp_locs);

   Float64 max_length = 0;
   CollectionIndexType num_supps;
   hr = supp_locs->get_Count(&num_supps);
   Float64 start_loc;
   hr = supp_locs->get_Item(0, &start_loc);
   for (CollectionIndexType i=1; i<num_supps; i++)
   {
      Float64 end_loc;
      hr = supp_locs->get_Item(i, &end_loc);
      Float64 span_length = end_loc-start_loc;
      max_length = max(max_length, span_length);

      start_loc = end_loc;
   }

   ATLASSERT(max_length > 0.0);

   return max_length;
}

/////////////////////////////////////////////////////////////////////////////
// CBruteForceVehicularResponse2
CBruteForceVehicularResponse2::CBruteForceVehicularResponse2():
m_ModelDirty(true),
m_LiveLoadDirty(true),
m_VariableAxleSpacings(3),
m_ContextCookie(0),
m_pInflStrategy(NULL),
m_pDfStrategy(NULL),
m_pApplicabilityStrategy(NULL)
{
}

STDMETHODIMP CBruteForceVehicularResponse2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IEnvelopedVehicularResponse
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CBruteForceVehicularResponse2::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_Context, this, IID_IVehicularAnalysisContextEvents, m_ContextCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CBruteForceVehicularResponse2::Initialize(/*[in]*/IUnknown* context)
{
   CHECK_IN(context);

   CHRException hr;
   try
   {
      if (m_LiveLoad != NULL)
      {
         // can only initialize once
         THROW_LBAMLL(LL_INITIALIZATION);
      }

      m_Context = context;

      // listen to context for change events
      hr = CrAdvise(m_Context, this, IID_IVehicularAnalysisContextEvents, &m_ContextCookie);

      // Latch onto the parts of the context we need 
      CComQIPtr<ILiveLoad> pll(context);
      if (pll!=NULL)
      {
         m_LiveLoad = pll;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<IInfluenceLineResponse> presp(context);
      if (presp!=NULL)
      {
         m_InfluenceLineResponse = presp;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<ILiveLoadNegativeMomentRegion> pcf(context);
      if (pcf!=NULL)
      {
         m_LiveLoadNegativeMomentRegion = pcf;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<IGetDistributionFactors> pdf(context);
      if (pdf!=NULL)
      {
         m_GetDistributionFactors = pdf;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<ISupportLocations> sup_locs(m_Context);
      if (sup_locs!=NULL)
      {
         m_SupportLocations = sup_locs;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<IGetStressPoints> gsp(context);
      if (gsp!=NULL)
      {
         m_GetStressPoints = gsp;
      }
      else
      {
         ATLASSERT(0);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

   return hr;
}

// ISupportProgressMonitor
STDMETHODIMP CBruteForceVehicularResponse2::InitializeProgressMonitor(IProgressMonitor * newVal, LONG cookie)
{
   CHECK_IN(newVal);
   m_pProgressMonitor = newVal;
   m_ProgressCookie = cookie;

   return S_OK;
}

STDMETHODIMP CBruteForceVehicularResponse2::ComputeForces(IIDArray* poiIDs, BSTR stage, LiveLoadModelType type, 
                                                         VehicleIndexType vehicleIndex, ResultsOrientation orientation, 
                                                         ForceEffectType effect, OptimizationType optimization, 
                                                         VehicularLoadConfigurationType vehConfiguration,
                                                         VARIANT_BOOL doApplyImpact, DistributionFactorType distributionType,
                                                         VARIANT_BOOL computePlacements,
                                                         ILiveLoadModelSectionResults** pResults)
{
   CHECK_IN(poiIDs);
   CHECK_IN(stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      // set up context and strategies
      ForceInfluenceLineStrategy InflStrategy(m_InfluenceLineResponse, orientation);
      m_pInflStrategy = &InflStrategy;

      ForceDistributionFactorStrategy DfStrategy(m_GetDistributionFactors, optimization);
      m_pDfStrategy = &DfStrategy;

      ForceLLApplicabilityStrategy ApplStrategy(m_LiveLoadNegativeMomentRegion);
      m_pApplicabilityStrategy = &ApplStrategy;

      m_pResultsCache = &m_ForceInflResponse;

      m_bComputingReaction = false;
      m_bComputingMaximumInteriorSupportReaction = false;
      if ( effect == fetMz && optimization == optMinimize )
         m_bComputingMinimumMoment = true;
      else
         m_bComputingMinimumMoment = false;
         

      this->m_RealOptimization = optimization;
      hr = this->ComputeResponse(poiIDs, stage, type, 
                                 vehicleIndex,
                                 effect,  
                                 vehConfiguration,
                                 doApplyImpact, distributionType,
                                 computePlacements,
                                 pResults);

      m_pInflStrategy          = NULL;
      m_pDfStrategy            = NULL;
      m_pApplicabilityStrategy = NULL;

   }
   catch(...)
   {
      m_pInflStrategy          = NULL;
      m_pDfStrategy            = NULL;
      m_pApplicabilityStrategy = NULL;

      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }
   return hr;
}

STDMETHODIMP CBruteForceVehicularResponse2::ComputeDeflections(IIDArray* poiIDs, BSTR stage, LiveLoadModelType type, 
                                                               VehicleIndexType vehicleIndex, 
                                                               ForceEffectType effect, OptimizationType optimization, 
                                                               VehicularLoadConfigurationType vehConfiguration,
                                                               VARIANT_BOOL doApplyImpact, DistributionFactorType distributionType,
                                                               VARIANT_BOOL computePlacements,
                                                               ILiveLoadModelSectionResults** pResults)
{
   CHECK_IN(poiIDs);
   CHECK_IN(stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      // set up context and strategies
      DeflectionInfluenceLineStrategy InflStrategy(m_InfluenceLineResponse);
      m_pInflStrategy = &InflStrategy;

      DeflectionDistributionFactorStrategy DfStrategy(m_GetDistributionFactors);
      m_pDfStrategy = &DfStrategy;

      DeflectionLLApplicabilityStrategy ApplStrategy;
      m_pApplicabilityStrategy = &ApplStrategy;

      m_bComputingReaction = false;
      m_bComputingMaximumInteriorSupportReaction = false;
      m_bComputingMinimumMoment = false;

      m_pResultsCache = &m_DeflInflResponse;

      this->m_RealOptimization = optimization;
      hr = this->ComputeResponse(poiIDs, stage, type, 
                                 vehicleIndex,  
                                 effect,  
                                 vehConfiguration,
                                 doApplyImpact, distributionType,
                                 computePlacements,
                                 pResults);

      m_pInflStrategy = NULL;
      m_pDfStrategy = NULL;
      m_pApplicabilityStrategy = NULL;
   }
   catch(...)
   {
      m_pInflStrategy          = NULL;
      m_pDfStrategy            = NULL;
      m_pApplicabilityStrategy = NULL;

      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

   return hr;
}

STDMETHODIMP CBruteForceVehicularResponse2::ComputeReactions(IIDArray* supportIDs, BSTR stage, LiveLoadModelType type, 
                                                            VehicleIndexType vehicleIndex, 
                                                            ForceEffectType effect, OptimizationType optimization, 
                                                            VehicularLoadConfigurationType vehConfiguration,
                                                            VARIANT_BOOL doApplyImpact, DistributionFactorType distributionType,
                                                            VARIANT_BOOL computePlacements,
                                                            ILiveLoadModelResults** pResults)
{
   CHECK_IN(supportIDs);
   CHECK_IN(stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      // set up context and strategies
      ReactionInfluenceLineStrategy InflStrategy(m_InfluenceLineResponse);
      m_pInflStrategy = &InflStrategy;

      ReactionDistributionFactorStrategy DfStrategy(m_GetDistributionFactors);
      m_pDfStrategy = &DfStrategy;

      ReactionLLApplicabilityStrategy ApplStrategy(m_SupportLocations);
      m_pApplicabilityStrategy = &ApplStrategy;

      m_bComputingReaction = true;
      m_bComputingMaximumInteriorSupportReaction = false;
      m_bComputingMinimumMoment = false;

      m_pResultsCache = &m_ReactionInflResponse;

      // compute left and right results and use max of both
      CComPtr<ILiveLoadModelSectionResults> sec_res;

      this->m_RealOptimization = optimization;
      hr = this->ComputeResponse(supportIDs, stage, type, 
                                   vehicleIndex,  
                                   effect,  
                                   vehConfiguration,
                                   doApplyImpact, distributionType,
                                   computePlacements,
                                   &sec_res);

      m_pInflStrategy          = NULL;
      m_pDfStrategy            = NULL;
      m_pApplicabilityStrategy = NULL;

      // copy section results to non-section based - taking local maxes along the way
      CComPtr<ILiveLoadModelResults> results;
      LLSectionToRes(sec_res, optimization, &results);

      hr = results.CopyTo(pResults);
   }
   catch(...)
   {
      m_pInflStrategy          = NULL;
      m_pDfStrategy            = NULL;
      m_pApplicabilityStrategy = NULL;

      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

   return hr;
}

STDMETHODIMP CBruteForceVehicularResponse2::ComputeSupportDeflections(IIDArray* supportIDs, BSTR stage, LiveLoadModelType type, 
                                                            VehicleIndexType vehicleIndex, 
                                                            ForceEffectType effect, OptimizationType optimization, 
                                                            VehicularLoadConfigurationType vehConfiguration,
                                                            VARIANT_BOOL doApplyImpact, DistributionFactorType distributionType,
                                                            VARIANT_BOOL computePlacements,
                                                            ILiveLoadModelResults** pResults)
{
   CHECK_IN(supportIDs);
   CHECK_IN(stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      // set up context and strategies
      SupportDeflectionInfluenceLineStrategy InflStrategy(m_InfluenceLineResponse);
      m_pInflStrategy = &InflStrategy;

      SupportDeflectionDistributionFactorStrategy DfStrategy(m_GetDistributionFactors);
      m_pDfStrategy = &DfStrategy;

      SupportDeflectionLLApplicabilityStrategy ApplStrategy;
      m_pApplicabilityStrategy = &ApplStrategy;

      m_bComputingReaction = false;
      m_bComputingMaximumInteriorSupportReaction = false;
      m_bComputingMinimumMoment = false;

      m_pResultsCache = &m_SupportDeflInflResponse;

      // compute left and right results and use max of both
      CComPtr<ILiveLoadModelSectionResults> sec_res;
      this->m_RealOptimization = optimization;
      hr = this->ComputeResponse(supportIDs, stage, type, 
                                   vehicleIndex,  
                                   effect,  
                                   vehConfiguration,
                                   doApplyImpact, distributionType,
                                   computePlacements,
                                   &sec_res);

      m_pInflStrategy = NULL;
      m_pDfStrategy = NULL;

      // copy section results to non-section based - taking local maxes along the way
      CComPtr<ILiveLoadModelResults> results;
      LLSectionToRes(sec_res, optimization, &results);

      hr = results.CopyTo(pResults);
   }
   catch(...)
   {
      m_pInflStrategy          = NULL;
      m_pDfStrategy            = NULL;
      m_pApplicabilityStrategy = NULL;

      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

   return hr;
}

STDMETHODIMP CBruteForceVehicularResponse2::ComputeStresses(IIDArray* poiIDs, BSTR stage, LiveLoadModelType type, 
                                                           VehicleIndexType vehicleIndex,
                                                           ForceEffectType effect, OptimizationType optimization, 
                                                           VehicularLoadConfigurationType vehConfiguration,
                                                           VARIANT_BOOL doApplyImpact, DistributionFactorType distributionType,
                                                           VARIANT_BOOL computePlacements,
                                                           ILiveLoadModelStressResults** pResults)
{
   CHECK_IN(poiIDs);
   CHECK_IN(stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      // use force optimization and all assumptions (strategies) associated with it
      CComPtr<ILiveLoadModelSectionResults> force_res;
      hr = this->ComputeForces(poiIDs, stage, type, vehicleIndex, roMember, effect, optimization, vehConfiguration,
                               doApplyImpact, distributionType, VARIANT_TRUE, &force_res);

      // use basic stress calculation to compute stresses for optimized truck location (configuration)
      CComObject<CBasicVehicularResponse>* basic_response;
      hr = CComObject<CBasicVehicularResponse>::CreateInstance(&basic_response);

      CComPtr<IBasicVehicularResponse> pbasic_response(basic_response); // exception safety

      // secret (non-com) back door to inialize in a hurry
      basic_response->QuickInitialize(m_LiveLoad, m_InfluenceLineResponse, m_LiveLoadNegativeMomentRegion, 
                                      m_GetDistributionFactors, m_SupportLocations, 
                                      m_GetStressPoints);

      hr = LLSectionToStressResults(poiIDs, stage, force_res, basic_response,  pResults);

   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

   return hr;
}

STDMETHODIMP CBruteForceVehicularResponse2::ComputeResponse(IIDArray* poiIDs, BSTR stage, LiveLoadModelType type, 
                                                           VehicleIndexType vehicleIndex, 
                                                           ForceEffectType effect, 
                                                           VehicularLoadConfigurationType vehConfiguration,
                                                           VARIANT_BOOL doApplyImpact, DistributionFactorType distributionType,
                                                           VARIANT_BOOL vbComputePlacements,
                                                           ILiveLoadModelSectionResults** pResults)
{
   CHRException hr;
   try
   {
      AssertValid();

      Configure(stage, type, vehicleIndex, vehConfiguration, doApplyImpact);

      CollectionIndexType nPoi;
      hr = poiIDs->get_Count(&nPoi);

      // create results collection
      CComObject<CLiveLoadModelSectionResults>* cresults;
      CComObject<CLiveLoadModelSectionResults>::CreateInstance(&cresults);
      CComPtr<ILiveLoadModelSectionResults> results(cresults);
      hr = results->Reserve(nPoi);


      // see if this effect has a sign change at left/right faces
      Float64 flip_factor = m_pInflStrategy->SignFlip();

      for (CollectionIndexType poiIdx = 0; poiIdx < nPoi; poiIdx++)
      {
         HANDLE_CANCEL_PROGRESS();

         PoiIDType poi_id;
         hr = poiIDs->get_Item(poiIdx, &poi_id);

         bool bIsAtSupport = IsPoiAtSupport(stage,poi_id);

         if ( m_bComputingReaction )
         {
            bIsAtSupport = true;
            // if we are computing a reaction, the poi_id is the support id
            // determine if we are computing a maximum reaction at an interior support
            VARIANT_BOOL bIsInteriorSupport;
            m_SupportLocations->IsInteriorSupport(poi_id,&bIsInteriorSupport);

            if ( bIsInteriorSupport == VARIANT_TRUE && m_RealOptimization == optMaximize )
            {
               m_bComputingMaximumInteriorSupportReaction = true;
            }
            else
            {
               m_bComputingMaximumInteriorSupportReaction = false;
            }
         }

         // our results for this round
         Float64 left_result=0.0;
         Float64 right_result=0.0;
         CComPtr<ILiveLoadConfiguration> left_config;
         CComPtr<ILiveLoadConfiguration> right_config;

         // create dummy live load configurations
         bool computePlacements = (vbComputePlacements == VARIANT_TRUE ? true : false);

         if (computePlacements)
         {
            CComObject<CLiveLoadConfiguration>* pconfig;
            hr = CComObject<CLiveLoadConfiguration>::CreateInstance(&pconfig);

            left_config = pconfig;
            left_config->put_IsApplicable(VARIANT_FALSE);

            pconfig=NULL;
            hr = CComObject<CLiveLoadConfiguration>::CreateInstance(&pconfig);
            right_config = pconfig;
            right_config->put_IsApplicable(VARIANT_FALSE);
         }

         // see if our live load is applicable at this location
         ApplicabilityLoc applicabilityloc = m_pApplicabilityStrategy->GetApplicability(poi_id, stage, 
                                                                 VARIANT_TRUE, m_LiveLoadApplicability, 
                                                                 effect, m_RealOptimization);
         if (applicabilityloc != appNone)
         {

            // get our influence line(s) for this poi
            CComPtr<IInfluenceLine> lft_infl_line, rgt_infl_line;
            hr = m_pInflStrategy->ComputeInfluenceLine(poi_id, stage, effect, &lft_infl_line, &rgt_infl_line);

            // Left face results come from left influence line
            if ( lft_infl_line )
            {
               Float64 bogus_result;
               CComPtr<ILiveLoadConfiguration> bogus_config;
               if (computePlacements)
               {
                  CComObject<CLiveLoadConfiguration>* pConfig;
                  hr = CComObject<CLiveLoadConfiguration>::CreateInstance(&pConfig);

                  bogus_config = pConfig;
                  bogus_config->put_IsApplicable(VARIANT_FALSE);
               }

               ComputeInflResponse(poi_id,type, vehicleIndex, effect, m_RealOptimization, vehConfiguration, doApplyImpact, vbComputePlacements, 
                                   lft_infl_line, ssLeft, &left_result, &bogus_result, left_config, bogus_config);

               if ( m_bComputingReaction && rgt_infl_line == NULL )
               {
                  right_result = bogus_result;
                  right_config = bogus_config;
               }
            }


            // Right face results come from right influence line
            if ( rgt_infl_line )
            {
               Float64 bogus_result;
               CComPtr<ILiveLoadConfiguration> bogus_config;
               if (computePlacements)
               {
                  CComObject<CLiveLoadConfiguration>* pConfig;
                  hr = CComObject<CLiveLoadConfiguration>::CreateInstance(&pConfig);

                  bogus_config = pConfig;
                  bogus_config->put_IsApplicable(VARIANT_FALSE);
               }

               OptimizationType loc_optimization = m_RealOptimization;
               if (flip_factor == -1.0)
               {
                  loc_optimization = (m_RealOptimization==optMaximize) ? optMinimize : optMaximize;
               }

               ComputeInflResponse(poi_id,type, vehicleIndex, effect, loc_optimization, vehConfiguration, doApplyImpact, vbComputePlacements, 
                                   rgt_infl_line, ssRight, &bogus_result, &right_result, bogus_config, right_config);

               if (computePlacements)
               {
                  right_config->put_Optimization(m_RealOptimization); // make sure we're in right sign convention
               }
            }
         }
         else
         {
            // Live load not applible at this location... do nothing
            ATLASSERT(applicabilityloc==appNone);
         }

         // apply distribution factors if desired
         Float64 left_dfactor  = 1.0;
         Float64 right_dfactor = 1.0;
         if (distributionType!=dftNone)
         {
            DistributionFactorType left_used_dftype, right_used_dftype;
            m_pDfStrategy->GetOptimalDfs(poi_id, stage, effect, distributionType,
                                                 &left_dfactor, &left_used_dftype, 
                                                 &right_dfactor, &right_used_dftype);

            left_result  *= left_dfactor;
            right_result *= right_dfactor;

            if (computePlacements)
            {
               hr = left_config->put_DistributionFactorType(left_used_dftype);
               hr = right_config->put_DistributionFactorType(right_used_dftype);
            }
         }

         // add our result to the collection
         if ( bIsAtSupport )
         {
            if ( effect == fetMz )
               right_result *= flip_factor;

            hr = results->Add(left_result, left_config, right_result, right_config);
         }
         else
         {
            if ( m_RealOptimization == optMaximize )
            {
               if ( left_result > right_result )
               {
                  // left face results are going on the right face side. The right and left DF
                  // could be different... if they are, scale the result
                  Float64 df_right = IsZero(left_dfactor) ? 1 : right_dfactor/left_dfactor;
                  hr = results->Add(left_result, left_config, flip_factor*left_result*df_right, left_config);
               }
               else
               {
                  Float64 df_left = IsZero(right_dfactor) ? 1 : left_dfactor/right_dfactor;
                  hr = results->Add(right_result*df_left, right_config, flip_factor*right_result, right_config);
               }
            }
            else
            {
               if ( left_result < right_result )
               {
                  Float64 df_right = IsZero(left_dfactor) ? 1 : right_dfactor/left_dfactor;
                  hr = results->Add(left_result, left_config, flip_factor*left_result*df_right, left_config);
               }
               else
               {
                  Float64 df_left = IsZero(right_dfactor) ? 1 : left_dfactor/right_dfactor;
                  hr = results->Add(right_result*df_left, right_config, flip_factor*right_result, right_config);
               }
            }
         }
      }

      hr = results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

	return hr;
}

void CBruteForceVehicularResponse2::ComputeInflResponse(PoiIDType poiID,LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                                                        VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                                                        VARIANT_BOOL computePlacements, IInfluenceLine* inflLine, Side side,
                                                        Float64* leftResult, Float64 *rightResult, 
                                                        ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig)
{
   CHRException hr;

   *leftResult  = 0.0;
   *rightResult = 0.0;

   // Determine side of influence line where we will be working
   InfluenceSideType truck_side;
   if (m_IsNotional)
      truck_side = (optimization == optMaximize) ? ilsPositive : ilsNegative;
   else
      truck_side = ilsBoth;

   // check to see if the influence line is flat - no use running trucks over nothing
   VARIANT_BOOL is_influence_zero;
   hr = inflLine->IsZero(truck_side, &is_influence_zero);

   if (is_influence_zero == VARIANT_TRUE)
      return; // all zeros, get the heck outta here... 


   // have applicable, valid influence line
   Float64 left_truck_result  = 0;
   Float64 right_truck_result = 0;

   // set up our class for doing value comparisons - remember this function works on left-face coordinates
   iLLCompare* left_compare = NULL;
   iLLCompare* right_compare = NULL;
   if ( !GetInflResponse(poiID,type, vehicleIndex, effect, vehConfiguration, doApplyImpact, &left_compare, &right_compare ) )
   {
      IntializeCompare(optimization, &left_compare, &right_compare);
      EvaluateTruckLoad(type,vehicleIndex,effect,optimization,vehConfiguration,doApplyImpact,computePlacements,inflLine,truck_side,left_compare,right_compare,&left_truck_result,&right_truck_result,leftConfig,rightConfig);
      SaveInflResponse(poiID,type,vehicleIndex,effect, vehConfiguration,doApplyImpact,left_compare,right_compare);
   }
   else
   {
      left_truck_result = left_compare->GetResult();
      right_truck_result = right_compare->GetResult();
   }

   if (computePlacements == VARIANT_TRUE)
   {
       left_compare->ConfigureTruckPlacement(leftConfig, type, vehicleIndex, vehConfiguration, 
                                             effect, optimization, doApplyImpact);

       right_compare->ConfigureTruckPlacement(rightConfig, type, vehicleIndex, vehConfiguration, 
                                              effect, optimization, doApplyImpact);
   }


   // deal with lane and sidewalk results
   Float64 lane_result     = 0.0;
   Float64 sidewalk_result = 0.0;
   if (m_IsLane || m_IsSidewalk)
   {
      InfluenceSideType lane_side = (optimization == optMaximize ? ilsPositive : ilsNegative);

      Float64 area;
      hr = inflLine->ComputeArea(lane_side, &area);

      if (m_IsLane)
      {
         lane_result = m_LaneLoad * area;
      }

      if (m_IsSidewalk)
      {
         sidewalk_result = m_SidewalkLoad * area;
      }
   }

   // combine truck and lane response - both responses are already factored at this point
   if (m_CachedVehConfiguration == vlcTruckOnly)
   {
      // truck only
      *leftResult  = left_truck_result;
      *rightResult = right_truck_result;
   }
   else if (m_CachedVehConfiguration == vlcTruckPlusLane)
   {
      // sum truck plus lane (LRFD)
      *leftResult  =  left_truck_result  + ::BinarySign(left_truck_result)*fabs(lane_result);
      *rightResult =  right_truck_result + ::BinarySign(right_truck_result)*fabs(lane_result);
   }
   else if (m_CachedVehConfiguration == vlcTruckLaneEnvelope)
   {
      // envelope truck and lane response (LFD)
      if (left_compare->DoCompare(left_truck_result, lane_result))
         *leftResult = left_truck_result;
      else
         *leftResult = lane_result;

      if (right_compare->DoCompare(right_truck_result,lane_result))
         *rightResult = right_truck_result;
      else
         *rightResult = lane_result;
   }
   else if (m_CachedVehConfiguration == vlcLaneOnly)
   {
      // lane only
      *leftResult  = lane_result;
      *rightResult = lane_result;

      if (computePlacements == VARIANT_TRUE)
      {
         ConfigureLaneConfig(leftConfig, type, vehicleIndex,  m_CachedVehConfiguration, effect, optimization,
                                 doApplyImpact);

         ConfigureLaneConfig(rightConfig, type, vehicleIndex, m_CachedVehConfiguration, effect, optimization,
                                 doApplyImpact);
      }
   }
   else if (m_CachedVehConfiguration == vlcSidewalkOnly)
   {
      // sidewalk only
      *leftResult  = sidewalk_result;
     * rightResult = sidewalk_result;

      if (computePlacements == VARIANT_TRUE)
      {
         ConfigureLaneConfig(leftConfig, type, vehicleIndex, m_CachedVehConfiguration, effect, optimization,
                                 doApplyImpact);
         ConfigureLaneConfig(rightConfig, type, vehicleIndex, m_CachedVehConfiguration, effect, optimization,
                                 doApplyImpact);
      }
   }
   else
   {
      ATLASSERT(0);
      throw E_INVALIDARG;
   }
}
 
void CBruteForceVehicularResponse2::Configure(BSTR stage, LiveLoadModelType type, VehicleIndexType vehicleIndex,
                                              VehicularLoadConfigurationType vehConfiguration, 
                                              VARIANT_BOOL doApplyImpact)
{
   ConfigureAnalysisCache(stage, type, vehicleIndex, vehConfiguration, doApplyImpact);
   ConfigureAxleSpacings();
   ConfigureAnalysisPoints(stage);
}

void CBruteForceVehicularResponse2::ConfigureAnalysisCache(BSTR stage, LiveLoadModelType type, VehicleIndexType vehicleIndex,
                                                           VehicularLoadConfigurationType vehConfiguration, 
                                                           VARIANT_BOOL doApplyImpact)
{
   // see if we already have initialized our truck for this case
   CHRException hr;

   if (m_LiveLoadDirty                              || 
       type             != m_CachedLiveLoadModel    || 
       vehicleIndex     != m_CachedVehicleIndex     || 
       vehConfiguration != m_CachedVehConfiguration ||
       doApplyImpact    != m_CachedDoApplyImpact
       ) 
   {
      // get vehicle
      CComPtr<IVehicularLoad> pvl;
      GetVehicularLoad(type, vehicleIndex, m_LiveLoad, &pvl);

      // update our cache control variables
      m_CachedVehConfiguration = GetSelectedVehicularConfiguration( vehConfiguration, pvl);
      m_CachedLiveLoadModel    = type;
      m_CachedVehicleIndex     = vehicleIndex;
      m_CachedDoApplyImpact    = doApplyImpact;

      // Compute some control information
      m_IsTruck    = m_CachedVehConfiguration==vlcTruckOnly || m_CachedVehConfiguration==vlcTruckPlusLane || m_CachedVehConfiguration==vlcTruckLaneEnvelope;
      m_IsLane     = m_CachedVehConfiguration==vlcLaneOnly  || m_CachedVehConfiguration==vlcTruckPlusLane || m_CachedVehConfiguration==vlcTruckLaneEnvelope;
      m_IsSidewalk = m_CachedVehConfiguration==vlcSidewalkOnly;

      // get fixed axle configuration wrt datum - factor axle weights
      if (m_IsTruck)
      {
         m_Truck.Initialize(pvl, (m_CachedDoApplyImpact==VARIANT_TRUE) );
      }

      // compute lane load
      m_LaneLoad=0.0;
      if (m_IsLane)
      {
         hr = pvl->get_LaneLoad(&m_LaneLoad);

         Float64 lane_factor;
         hr = pvl->get_LaneFactor(&lane_factor);
         ATLASSERT(lane_factor>=0.0);

         if (m_CachedDoApplyImpact == VARIANT_TRUE)
         {
            Float64 lane_im;
            hr = pvl->get_IMLane(&lane_im);

            lane_factor*=lane_im;
         }

         m_LaneLoad *= lane_factor;

         if (m_LaneLoad==0.0) 
            m_IsLane = false;  // optimization
      }

      // sidewalk load
      m_SidewalkLoad=0.0;
      if (m_IsSidewalk)
      {
         hr = pvl->get_SidewalkLoad(&m_SidewalkLoad);
      }

      // see if notional model is to be used
      VARIANT_BOOL is_notional;
      hr = pvl->get_UseNotional(&is_notional);

      m_IsNotional = (is_notional == VARIANT_TRUE ? true : false);

      // see where results are applicable on structure
      hr = pvl->get_Applicability(&m_LiveLoadApplicability);

      m_LiveLoadDirty = false;
   }
}

void CBruteForceVehicularResponse2::ConfigureAnalysisPoints(BSTR stage)
{
   CHRException hr;
   if (m_ModelDirty || m_CachedStage != CComBSTR(stage))
   {
      m_CachedStage = stage;

      m_PoiLocations.clear();

      CComQIPtr<IAnalysisPOIs> poi_utility(m_Context);
      CComPtr<IIDArray> poiids;
      CComPtr<IDblArray> poilocs;
      hr = poi_utility->GetSuperstructurePois(m_CachedStage , &poiids, &poilocs);

      CollectionIndexType nPois;
      hr = poiids->get_Count(&nPois);

#ifdef _DEBUG
      CollectionIndexType tsiz;
      hr = poilocs->get_Count(&tsiz);
      ATLASSERT(nPois==tsiz); // number of items must match
#endif

      Float64 last_loc;
      bool first = true;
      for (CollectionIndexType i = 0; i < nPois; i++)
      {
         PoiIDType id;
         hr = poiids->get_Item(i, &id);

         Float64 loc;
         hr = poilocs->get_Item(i, &loc);

         last_loc = loc;

         // remove redundant locations
         if (first || last_loc!=loc)
         {
            m_PoiLocations.push_back( PoiLocation(id,loc) );
         }
      }

      m_ModelDirty  = false;
   }
}

void CBruteForceVehicularResponse2::ConfigureAxleSpacings()
{
   CHRException hr;

   m_AxleSpacings.clear();

   if ( !m_IsTruck )
      return;

   if ( !m_Truck.IsVariableAxle() )
   {
      // no variable axles put a dummy in the array so our computation loop will work
      m_AxleSpacings.push_back(0.0);
      return; 
   }


   Float64 model_length;
   hr = m_SupportLocations->get_TotalLength(&model_length);

   Float64 min_spc = m_Truck.GetMinVariableAxleSpacing();
   Float64 max_spc = m_Truck.GetMaxVariableAxleSpacing();

   if (max_spc<=min_spc)
   {
      THROW_LBAMLL(INVALID_VAR_SPACING);
   }

   // make sure superstructure is longer than min spacing length
   if (model_length>min_spc)
   {
      // Set max spacing so that it does not exceed length of bridge
      if (max_spc>model_length)
      {
         max_spc = model_length;
      }

      ATLASSERT(m_VariableAxleSpacings>1);
      // compute variable axle increments based on truck information alone
      Float64 diff = max_spc - min_spc;
      Float64 truck_delta = diff / (m_VariableAxleSpacings-1);

      // To aid accuracy, variable axle increments should be less than a fraction of the
      // minimum span length.
      // Compute variable axle increments based on minimum span length
      Float64 min_span_length = GetMinSpanLength(m_SupportLocations);
      Float64 span_delta = min_span_length / (m_VariableAxleSpacings-1);

      long num_spacings;
      Float64 delta;
      if (truck_delta<span_delta)
      {
         delta        = truck_delta;
         num_spacings = m_VariableAxleSpacings;
      }
      else
      {
         // need more varaible axle spacings to accomodate short span
         num_spacings = long(((diff-1.0e-7)/span_delta)+1);
         delta = diff/(num_spacings-1);
      }

      // fill up the spacing array
      Float64 spac = min_spc;
      for (long is=0; is<num_spacings; is++)
      {
         m_AxleSpacings.push_back(spac);
         spac += delta;
      }
      ATLASSERT(IsEqual(spac-delta, max_spc));
   }
   else
   {
      // entire superstructure is shorter than min variable axle spacing. only need to use min spacing
      m_AxleSpacings.push_back(min_spc);
   }
}

void CBruteForceVehicularResponse2::IntializeCompare(OptimizationType optimization, iLLCompare** pleftCompare, iLLCompare** prightCompare)
{
   // set up left and right comparison classes
   if (optimization==optMaximize)
   {
      *pleftCompare  =  &m_LeftMaxCompare;
      *prightCompare =  &m_RightMaxCompare;
   }
   else
   {
      *pleftCompare  =  &m_LeftMinCompare;
      *prightCompare =  &m_RightMinCompare;
   }

   (*pleftCompare)->Init();
   (*prightCompare)->Init();
}

void CBruteForceVehicularResponse2::AssertValid()
{
   ATLASSERT(m_pInflStrategy != NULL);

   if (m_LiveLoad == NULL)
   {
      // must be initialized before use
      THROW_LBAMLL(LL_INITIALIZATION);
   }

   ATLASSERT(m_VariableAxleSpacings>0);
}

STDMETHODIMP CBruteForceVehicularResponse2::OnLiveLoadChanged( LiveLoadModelType type)
{
   m_LiveLoadDirty = true;
   return S_OK;
}

STDMETHODIMP CBruteForceVehicularResponse2::OnStiffnessResponseChanged(ChangeScopeType scope, PoiIDType poiID)
{
   m_ModelDirty = true;
   m_CachedStage = "";
   return S_OK;
}

void CBruteForceVehicularResponse2::EvaluateTruckLoad(LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                                                       VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                                                       VARIANT_BOOL computePlacements, IInfluenceLine* inflLine, InfluenceSideType truck_side,
                                                       iLLCompare* pLeftCompare,iLLCompare* pRightCompare,
                                                       Float64* pLeftResult, Float64 *pRightResult,
                                                       ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig)
{
   *pLeftResult  = 0;
   *pRightResult = 0;

   if ( !m_IsTruck || m_Truck.GetNumAxles() == 0 )
   {
      // there is no truck, or no axles... force a compare
      // to avoid problems with ASSERTs later
      pLeftCompare->CompareResults(0.0);
      pRightCompare->CompareResults(0.0);
      return;
   }


   if ( (m_bComputingMinimumMoment || m_bComputingMaximumInteriorSupportReaction) &&
         m_Truck.IsVariableAxle() && m_Truck.NegMomentsAndReactions() ) 
   {
      if (m_bComputingMinimumMoment )
      {
         // analyzing for negative moment with a variable axle truck
         EvaluateForMinMoment(type, vehicleIndex, effect, optimization, 
                              vehConfiguration, doApplyImpact,
                              computePlacements, inflLine, truck_side,
                              pLeftCompare, pRightCompare,
                              pLeftResult, pRightResult,
                              leftConfig, rightConfig);
      }
      else if ( m_bComputingMaximumInteriorSupportReaction )
      {
         EvaluateForInteriorSupportReaction(type, vehicleIndex, effect, optimization, 
                                            vehConfiguration, doApplyImpact,
                                            computePlacements, inflLine, truck_side,
                                            pLeftCompare, pRightCompare,
                                            pLeftResult, pRightResult,
                                            leftConfig, rightConfig);
      }
   }
   else
   {
      // analyzing for everything else
      Evaluate(type, vehicleIndex, effect, optimization, 
               vehConfiguration, doApplyImpact,
               computePlacements, inflLine, truck_side,
               pLeftCompare, pRightCompare,
               pLeftResult, pRightResult,
               leftConfig, rightConfig);
   }

}

void CBruteForceVehicularResponse2::EvaluateForMinMoment(LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                                                        VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                                                        VARIANT_BOOL computePlacements, IInfluenceLine* inflLine, InfluenceSideType truck_side,
                                                        iLLCompare* pLeftCompare,iLLCompare* pRightCompare,
                                                        Float64* pLeftResult, Float64 *pRightResult,
                                                        ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig)
{
   CHRException hr;

   ATLASSERT( m_Truck.IsVariableAxle() );
   AxleIndexType variableAxleIndex = m_Truck.GetVariableAxleIndex();

   Float64 minVariableAxleSpacing = m_Truck.GetMinVariableAxleSpacing();
   Float64 maxVariableAxleSpacing = m_Truck.GetMaxVariableAxleSpacing();

   AxleIndexType nAxles = m_Truck.GetNumAxles();

   std::vector<AxleState> applied_axles;
   applied_axles.reserve(nAxles);

   CComPtr<IDblArray> supportLocations;
   m_SupportLocations->get_SupportLocations(&supportLocations);

   CollectionIndexType nSupports;
   supportLocations->get_Count(&nSupports);

   Float64 prevSupportLocation;
   Float64 nextSupportLocation;
   Float64 minValue, prevMinLocation, nextMinLocation;
   for ( CollectionIndexType supportIdx = 0; supportIdx < nSupports; supportIdx++ )
   {
      Float64 currSupportLocation;
      supportLocations->get_Item(supportIdx,&currSupportLocation);

      VARIANT_BOOL bIsInteriorSupport;
      m_SupportLocations->IsInteriorSupport(supportIdx,&bIsInteriorSupport);
      if ( bIsInteriorSupport == VARIANT_FALSE )
      {
         // skip if this is the first or last support
         if ( supportIdx == 0 )
         {
            prevSupportLocation = currSupportLocation;
         }

         continue; 
      }

      // get location of next support
      supportLocations->get_Item(supportIdx+1,&nextSupportLocation);

      // get location of min influence value in the previous and next spans
      if ( supportIdx == 1 )
      {
         // only need to do this if we are at the first interior support,
         // otherwise the prevMinLocation is set equal to the nextMinLocation at the end
         // of the loop
         inflLine->FindMinValue(prevSupportLocation,currSupportLocation,&prevMinLocation,&minValue);

         // if there isn't a min value location, then just use the mid-span point
         if ( prevMinLocation < 0 )
         {
            prevMinLocation = (prevSupportLocation + currSupportLocation)/2;
         }
      }

      inflLine->FindMinValue(currSupportLocation,nextSupportLocation,&nextMinLocation,&minValue);


      // if there isn't a min value location, then just use the mid-span point
      if ( nextMinLocation < 0 )
      {
         nextMinLocation = (currSupportLocation + nextSupportLocation)/2;
      }


      // for each axle before the pivot axle (variable spacing axle), position the truck
      // such that the axle is at the min influence value in the next span. For each axle after
      // the variable spacing, adjust the variable axle spacing such that each axle after the 
      // variable space is at the min influence value in the previous span.

      //             |   |   |<----- var spacing -------->|  |   |
      //             v   v   v                            v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 0, rearAxleIndex = 3
      //  ^                                       o

      //                 |   |   |                        |  |   |
      //                 v   v   v                        v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 0, rearAxleIndex = 4
      //  ^                                       o

      //                     |   |   |                    |  |   |
      //                     v   v   v                    v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 0, rearAxleIndex = 5
      //  ^                                       o


      //             |   |   |                                |  |   |
      //             v   v   v                                v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 1, rearAxleIndex = 3
      //  ^                                       o

      //                 |   |   |                            |  |   |
      //                 v   v   v                            v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 1, rearAxleIndex = 4
      //  ^                                       o

      //                     |   |   |                        |  |   |
      //                     v   v   v                        v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 1, rearAxleIndex = 5
      //  ^                                       o

      //             |   |   |                                   |  |   |
      //             v   v   v                                   v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 2, rearAxleIndex = 3
      //  ^                                       o

      //                 |   |   |                               |  |   |
      //                 v   v   v                               v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 2, rearAxleIndex = 4
      //  ^                                       o

      //                     |   |   |                           |  |   |
      //                     v   v   v                           v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 2, rearAxleIndex = 5
      //  ^                                       o

      // if the required variable axle spacing is less than the min spacing, or greater than the max spacing, the spacing is
      // set to the limiting value and the truck is analyzed with the current pivot axle. Then, without changing the variable
      // axle spacing, the pivot axle is moved to the rear group of axles and each of the remaining axles are positioned
      // on the rear min influence value location

      //                 |   |   |<-- Less than min spacing ---->|  |   |
      //                 v   v   v     or greater than max       v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 2, rearAxleIndex = 4
      //  ^                                       o

      // set spacing to min spacing and finish current analysis loop

      //                   |   |   |<-- Min/max spacing     ---->|  |   |
      //                   v   v   v                             v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 2, rearAxleIndex = 4
      //  ^                                       o

      // pivot on rear axles to finish the loop. variable axle spacing is fixed at limiting value

      //                 |   |   |<-- Min/max spacing     ---->|  |   |
      //                 v   v   v                             v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 2, rearAxleIndex = 4
      //  ^                                       o

      //                     |   |   |<-- Min/max spacing     ---->|  |   |
      //                     v   v   v                             v  v   v
      //  ===================x===================================x================~ frontAxleIndx = 2, rearAxleIndex = 5
      //  ^                                       o

      // if the required axle spacing is less than the min or greater than the max, and the truck cannot be positioned
      // such that the leading or trailing group of axles is at the min influnece values, then the truck will be
      // configured with the limiting spacing, the axle before the variable space will be placed on the support
      // and the truck will be moved in small increments until the axle just after the variable space reaches
      // the support.

      //                                  spacing
      //                        |   |   |<------->|  |   |
      //                        v   v   v         v  v   v
      //  ===================x===================================x================~ 
      //  ^                                       o

      //                                     spacing
      //                           |   |   |<------->|  |   |
      //                           v   v   v         v  v   v
      //  ===================x===================================x================~ 
      //  ^                                       o

      //                                        spacing
      //                              |   |   |<------->|  |   |
      //                              v   v   v         v  v   v
      //  ===================x===================================x================~ 
      //  ^                                       o

      //                                            spacing
      //                                  |   |   |<------->|  |   |
      //                                  v   v   v         v  v   v
      //  ===================x===================================x================~ 
      //  ^                                       o

      // check to see if the truck, at it's maximum length, will have the two axle groups in adjacent spans
      // if the pivot axle is at a minimum influence value location
      m_Truck.SetVariableAxleSpacing(maxVariableAxleSpacing);
      Float64 max_truck_length = m_Truck.Length();
      if ( max_truck_length < (nextMinLocation - prevMinLocation) )
      {
         // the truck is too short to straddle the pier if the pivot axle is at a minimum influence value location
         // for the range of axle spaces, walk the truck over the pier

         // divide axle spacing range into steps
         SpacingIndexType nAxleSpaces = 4; 
         Uint32 nSteps      = 4;
         Float64 axleSpacingStep = (maxVariableAxleSpacing - minVariableAxleSpacing)/(nAxleSpaces-1);
         for ( SpacingIndexType axleSpaceIdx = 0; axleSpaceIdx < nAxleSpaces; axleSpaceIdx++ )
         {
            Float64 axleSpacing = minVariableAxleSpacing + axleSpaceIdx*axleSpacingStep;
            m_Truck.SetVariableAxleSpacing(axleSpacing);

            // at this axle spacing, move the truck until the axle after the variable axle
            // reaches the support
            Float64 stepSize = axleSpacing/(nSteps-1);
            for ( Uint32 stepIdx = 0; stepIdx < nSteps; stepIdx++ )
            {
               for ( int truckDir = 0; truckDir < 2; truckDir++ )
               {
                  TruckDirectionType direction = (truckDir == 0 ? ltdForward : ltdReverse);
                  Float64 sign = (direction == ltdForward ? 1 : -1);
         
                  AxleIndexType pivotAxleIndex = variableAxleIndex;
                  m_Truck.SetTruckDirection(direction,pivotAxleIndex);

                  Float64 truck_location = currSupportLocation + sign*stepIdx*stepSize;

                  VARIANT_BOOL is_dual;
                  Float64 left_truck_result, right_truck_result;

                  m_Truck.EvaluatePrimaryInfl(truck_location, truck_side, inflLine, 
                                              &applied_axles, &is_dual, &left_truck_result, &right_truck_result);

                  //WATCH("Vehicle Index " << vehicleIndex << " Axle Spacing " << m_Truck.GetVariableAxleSpacing() << " Dir " << (direction == ltdForward ? "F" : "R") << " Position " << truck_location << " Pivot Axle " << pivotAxleIndex);

                  // perform comparison and store data for new max if there is one.
                  if (pLeftCompare->CompareResults(left_truck_result))
                  {
                     pLeftCompare->StoreState(left_truck_result, truck_location, direction, pivotAxleIndex, applied_axles, m_Truck.GetVariableAxleSpacing());
                  }

                  if (pRightCompare->CompareResults(right_truck_result))
                  {
                     pRightCompare->StoreState(right_truck_result, truck_location, direction, pivotAxleIndex, applied_axles, m_Truck.GetVariableAxleSpacing());
                  }
               } // next truck direction
            } // next step
         } // next axle spacing
      }
      else
      {
         for ( int truckDir = 0; truckDir < 2; truckDir++ )
         {
            TruckDirectionType direction = (truckDir == 0 ? ltdForward : ltdReverse);

            if ( direction == ltdReverse )
            {
               // if the direction is reversed, swap the prev/next min locations
               Float64 temp = nextMinLocation;
               nextMinLocation = prevMinLocation;
               prevMinLocation = temp;
            }

            for ( AxleIndexType frontAxleIndex = 0; frontAxleIndex <= variableAxleIndex; frontAxleIndex++ )
            {
               // compute a variable axle spacing such that each axle after the variable axle is at the
               // min influence value in the previous span
         
               bool bPivotOnRearAxle = false;

               for ( AxleIndexType rearAxleIndex = variableAxleIndex+1; rearAxleIndex < nAxles; rearAxleIndex++ )
               {
                  Float64 truck_location       = (bPivotOnRearAxle ? prevMinLocation : nextMinLocation);
                  AxleIndexType pivotAxleIndex = (bPivotOnRearAxle ? rearAxleIndex   : frontAxleIndex);

                  ATLASSERT(rearAxleIndex     != INVALID_INDEX && rearAxleIndex     < nAxles);
                  ATLASSERT(frontAxleIndex    != INVALID_INDEX && frontAxleIndex    < nAxles);
                  ATLASSERT(variableAxleIndex != INVALID_INDEX && variableAxleIndex < nAxles);

                  m_Truck.SetTruckDirection(direction,pivotAxleIndex); 

                  // location of variable axle, measured from the pivot axle ( < 0 if after pivot for a forward truck)
                  Float64 variableAxleLocation = m_Truck.GetAxleLocation(variableAxleIndex);

                  Float64 nextAxleLocation = m_Truck.GetAxleLocation(variableAxleIndex + 1); // next axle after the variable axle
                  Float64 rearAxleLocation = m_Truck.GetAxleLocation(rearAxleIndex);         // current "rear" axle that is at the location in the previous span

                  // compute the variable axle spacing
                  //
                  // if we are pivoting on the rear axle group, then the variable axle spacing is at an extreme value and it is
                  // already fixed, otherwise it needs to be computed
                  Float64 variableAxleSpacing = m_Truck.GetVariableAxleSpacing();
                  bool bAxleSpacingAdjusted = true;
                  if ( !bPivotOnRearAxle )
                  {
                     variableAxleSpacing = (nextMinLocation - prevMinLocation) + variableAxleLocation - (nextAxleLocation - rearAxleLocation);
                     variableAxleSpacing *= (direction == ltdReverse ? -1 : 1); // swap sign if reverse
                     bAxleSpacingAdjusted = false;
                  }

                  if ( variableAxleSpacing < minVariableAxleSpacing )
                  {
                     //WATCH("Variable axle spacing less than min - use min axle spacing");
                     // the spacing is less then the min, make the spacing equal to the min value
                     variableAxleSpacing = minVariableAxleSpacing;

                     // this time through the loop, pivot on the front axle, then, everytime
                     // through this loop we will get constrained by the same min spacing so
                     // pivot on the rear axle 

                     if ( !bPivotOnRearAxle )
                        rearAxleIndex--; // back up one so we can do this loop again

                     bPivotOnRearAxle = true; // next time through the loop pivot on the rear axle

                     bAxleSpacingAdjusted = true;
                  }

                  if ( maxVariableAxleSpacing < variableAxleSpacing )
                  {
                     //WATCH("Variable axle spacing greater than max - use max axle spacing");
                     // the spacing is bigger than the max, make it equal the max value
                     variableAxleSpacing = maxVariableAxleSpacing;

                     // this time through the loop, pivot on the front axle, then, everytime
                     // through this loop we will get constrained by the same max spacing so
                     // pivot on the rear axle 

                     if ( !bPivotOnRearAxle )
                        rearAxleIndex--; // back up one so we can do this loop again

                     bPivotOnRearAxle = true; // next time through the loop pivot on the rear axle

                     bAxleSpacingAdjusted = true;
                  }

                  m_Truck.SetVariableAxleSpacing(variableAxleSpacing);

   //#if defined _DEBUG
   //               m_Truck.DumpAxles(truck_location);
   //#endif
                  // if the variable axle (the axle after the variable spacing) is in the same
                  // span as the axle before the variable spacing, then the "dual trucks" are in
                  // the same span so skip it (dual trucks have more than 3 axles)
                  Float64 variableAxlePosition = m_Truck.GetAxlePosition(variableAxleIndex+1,truck_location);
                  if ( 
                     ( (direction == ltdForward && currSupportLocation < variableAxlePosition)   || 
                       (direction == ltdReverse && variableAxlePosition < currSupportLocation) )
                       &&
                     (3 < nAxles)
                     )
                  {
                     //WATCH("Skipping truck because axles are in same span");
                     continue;
                  }


                  // if axle spacing is not adjusted, check to make sure variable axle spacing adds up
                  ATLASSERT(bAxleSpacingAdjusted ? true : IsEqual(nextMinLocation+m_Truck.GetAxleLocation(rearAxleIndex),prevMinLocation));

                  VARIANT_BOOL is_dual;
                  Float64 left_truck_result, right_truck_result;

                  m_Truck.EvaluatePrimaryInfl(truck_location, truck_side, inflLine, 
                                              &applied_axles, &is_dual, &left_truck_result, &right_truck_result);

                  //WATCH("Vehicle Index " << vehicleIndex << " Axle Spacing " << m_Truck.GetVariableAxleSpacing() << " Dir " << (direction == ltdForward ? "F" : "R") << " Position " << truck_location << " Pivot Axle " << pivotAxleIndex);

                  // perform comparison and store data for new max if there is one.
                  if (pLeftCompare->CompareResults(left_truck_result))
                  {
                     pLeftCompare->StoreState(left_truck_result, truck_location, direction, pivotAxleIndex, applied_axles, m_Truck.GetVariableAxleSpacing());
                  }

                  if (pRightCompare->CompareResults(right_truck_result))
                  {
                     pRightCompare->StoreState(right_truck_result, truck_location, direction, pivotAxleIndex, applied_axles, m_Truck.GetVariableAxleSpacing());
                  }
               } // next rear axle
            } // next front axle
         } // next truck direction
      } // end if for size of truck

      prevSupportLocation = currSupportLocation;


      // logically, we need to store the next value as the previous value when the loop restarts
      // however, when the truck direction changes above, prev and next are swapped. Thus, prev
      // has the correct value for the start of the next loop
      //prevMinLocation = nextMinLocation;
   
   } // next support

   // get the enveloped results
   *pLeftResult   = pLeftCompare->GetResult();
   *pRightResult  = pRightCompare->GetResult();
}
      
void CBruteForceVehicularResponse2::EvaluateForInteriorSupportReaction(LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                                                                       VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                                                                       VARIANT_BOOL computePlacements, IInfluenceLine* inflLine, InfluenceSideType truck_side,
                                                                       iLLCompare* pLeftCompare,iLLCompare* pRightCompare,
                                                                       Float64* pLeftResult, Float64 *pRightResult,
                                                                       ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig)
{
   CHRException hr;

   ATLASSERT( m_Truck.IsVariableAxle() );
   AxleIndexType variableAxleIndex = m_Truck.GetVariableAxleIndex();

   Float64 minVariableAxleSpacing = m_Truck.GetMinVariableAxleSpacing();

   AxleIndexType nAxles = m_Truck.GetNumAxles();

   std::vector<AxleState> applied_axles; 
   applied_axles.reserve(nAxles);

   CComPtr<IDblArray> supportLocations;
   m_SupportLocations->get_SupportLocations(&supportLocations);

   CollectionIndexType nSupports;
   supportLocations->get_Count(&nSupports);

   for ( CollectionIndexType supportIdx = 0; supportIdx < nSupports; supportIdx++ )
   {
      Float64 currSupportLocation;
      supportLocations->get_Item(supportIdx,&currSupportLocation);

      VARIANT_BOOL bIsInteriorSupport;
      m_SupportLocations->IsInteriorSupport(supportIdx,&bIsInteriorSupport);
      if ( bIsInteriorSupport == VARIANT_FALSE )
      {
         continue; 
      }

      // interior support reaction influence line is such that we want all of the axles as close to
      // the support as possible. the variable axle spacing will be fixed at the minimum value and 
      // the truck will be moved in small increments until the axle just after the variable space reaches
      // the support

      // we are only after the extreme "compressive" reaction. the dual trucks don't apply to the
      // uplift reaction when both trucks have to be in the same span. (and that would be a span
      // that is remote from the support we are considering)

      //                                  spacing
      //                        |   |   |<------->|  |   |
      //                        v   v   v         v  v   v
      //  ===================x===================================x================~ 
      //  ^                                       o

      //                                     spacing
      //                           |   |   |<------->|  |   |
      //                           v   v   v         v  v   v
      //  ===================x===================================x================~ 
      //  ^                                       o

      //                                        spacing
      //                              |   |   |<------->|  |   |
      //                              v   v   v         v  v   v
      //  ===================x===================================x================~ 
      //  ^                                       o

      //                                            spacing
      //                                  |   |   |<------->|  |   |
      //                                  v   v   v         v  v   v
      //  ===================x===================================x================~ 
      //  ^                                       o

      // divide axle spacing range into steps
      Float64 approxStepSize = m_Truck.MinAxleSpacing()/5;
      Uint32 nSteps = Uint32(minVariableAxleSpacing/approxStepSize);
      nSteps = ForceIntoRange(Uint32(3),nSteps,Uint32(11));
      m_Truck.SetVariableAxleSpacing(minVariableAxleSpacing);

      // move the truck until the axle after the variable axle reaches the support
      Float64 stepSize = minVariableAxleSpacing/(nSteps-1);
      for ( Uint32 stepIdx = 0; stepIdx < nSteps; stepIdx++ )
      {
         for ( int truckDir = 0; truckDir < 2; truckDir++ )
         {
            TruckDirectionType direction = (truckDir == 0 ? ltdForward : ltdReverse);
            Float64 sign = (direction == ltdForward ? 1 : -1);
   
            AxleIndexType pivotAxleIndex = variableAxleIndex;
            m_Truck.SetTruckDirection(direction,pivotAxleIndex);

            Float64 truck_location = currSupportLocation + sign*stepIdx*stepSize;

            VARIANT_BOOL is_dual;
            Float64 left_truck_result, right_truck_result;

            m_Truck.EvaluatePrimaryInfl(truck_location, truck_side, inflLine, 
                                        &applied_axles, &is_dual, &left_truck_result, &right_truck_result);

            //WATCH("Vehicle Index " << vehicleIndex << " Axle Spacing " << m_Truck.GetVariableAxleSpacing() << " Dir " << (direction == ltdForward ? "F" : "R") << " Position " << truck_location << " Pivot Axle " << pivotAxleIndex);

            // perform comparison and store data for new max if there is one.
            if (pLeftCompare->CompareResults(left_truck_result))
            {
               pLeftCompare->StoreState(left_truck_result, truck_location, direction, pivotAxleIndex, applied_axles, m_Truck.GetVariableAxleSpacing());
            }

            if (pRightCompare->CompareResults(right_truck_result))
            {
               pRightCompare->StoreState(right_truck_result, truck_location, direction, pivotAxleIndex, applied_axles, m_Truck.GetVariableAxleSpacing());
            }
         } // next truck direction
      } // next step
   } // next support

   // get the enveloped results
   *pLeftResult   = pLeftCompare->GetResult();
   *pRightResult  = pRightCompare->GetResult();
}

void CBruteForceVehicularResponse2::Evaluate(LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                                             VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                                             VARIANT_BOOL computePlacements, IInfluenceLine* inflLine, InfluenceSideType truck_side,
                                             iLLCompare* pLeftCompare,iLLCompare* pRightCompare,
                                             Float64* pLeftResult, Float64 *pRightResult,
                                             ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig)
{
   CHRException hr;

   AxleIndexType num_axles = m_Truck.GetNumAxles();

   std::vector<AxleState> applied_axles;
   applied_axles.reserve(num_axles);


   // evaluate every axle on every POI
   AxleIndexType nAxlePositions = num_axles;
   AxleIndexType* pivotAxles = new AxleIndexType[nAxlePositions];

   for ( AxleIndexType axleIdx = 0; axleIdx < nAxlePositions; axleIdx++ )
   {
      pivotAxles[axleIdx] = axleIdx;
   }

   // loop over each axle spacing for the truck
   AxleSpacingIterator ias( m_AxleSpacings.begin() );
   AxleSpacingIterator iasend( m_AxleSpacings.end() );
   for (; ias != iasend; ias++)
   {
      Float64 axle_spacing = *ias;
      if ( m_Truck.IsVariableAxle() )
      {
         m_Truck.SetVariableAxleSpacing( axle_spacing );
      }

      // loop over all pois and place each axle at every poi
      PoiLocationIterator pli( m_PoiLocations.begin() );
      PoiLocationIterator pliend( m_PoiLocations.end() );
      for (; pli != pliend; pli++)
      {
         Float64 poi_loc = pli->Location;

         Float64 truck_location = poi_loc;

         for (AxleIndexType axleIndex = 0; axleIndex < nAxlePositions; axleIndex++)
         {
            AxleIndexType pivotAxleIndex = pivotAxles[axleIndex];

            VARIANT_BOOL is_dual;
            Float64 left_truck_result, right_truck_result;

            for ( int truckDir = 0; truckDir < 2; truckDir++ )
            {
               TruckDirectionType direction = (truckDir == 0 ? ltdForward : ltdReverse);

               // set truck direction and pivot on the current axle
               m_Truck.SetTruckDirection(direction,pivotAxleIndex);

               m_Truck.EvaluatePrimaryInfl(truck_location, truck_side, inflLine, 
                                           &applied_axles, &is_dual, &left_truck_result, &right_truck_result);

               //WATCH("Vehicle Index " << vehicleIndex << " Axle Spacing " << axle_spacing << " Dir " << (truckDir == 0 ? "F" : "R") << " Position " << truck_location << " Pivot Axle " << pivotAxleIndex);

               // perform comparison and store data for new max if there is one.
               if (pLeftCompare->CompareResults(left_truck_result))
               {
                  pLeftCompare->StoreState(left_truck_result, truck_location, direction, pivotAxleIndex, applied_axles, axle_spacing);
               }

               if (pRightCompare->CompareResults(right_truck_result))
               {
                  pRightCompare->StoreState(right_truck_result, truck_location, direction, pivotAxleIndex, applied_axles, axle_spacing);
               }
            } // truck direction
         } // next axle
      } // next poi
   } // next axle spacing (variable axle)

   // done with this array
   delete[] pivotAxles;

   // get the enveloped results
   *pLeftResult   = pLeftCompare->GetResult();
   *pRightResult  = pRightCompare->GetResult();
}

bool CBruteForceVehicularResponse2::GetInflResponse(PoiIDType poiID,LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, 
                                                    VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                                                    iLLCompare** ppLeftCompare, iLLCompare** ppRightCompare)
{
   InflResponseRecord key(poiID,type,vehicleIndex, effect, m_RealOptimization, vehConfiguration, doApplyImpact );

   ConstInflResponseIterator found( m_pResultsCache->find(key) );
   if ( found == m_pResultsCache->end() )
   {
      return false;
   }

   const InflResponseRecord& record = *found;
   (*ppLeftCompare)  = record.m_pLeftCompare;
   (*ppRightCompare) = record.m_pRightCompare;

   return true;
}

void CBruteForceVehicularResponse2::SaveInflResponse(PoiIDType poiID,LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, 
                                                     VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                                                     iLLCompare* pLeftCompare, iLLCompare* pRightCompare)
{
   InflResponseRecord record(poiID, type, vehicleIndex, effect, m_RealOptimization, vehConfiguration, doApplyImpact, pLeftCompare, pRightCompare);

   std::pair<InflResponseIterator,bool> result( m_pResultsCache->insert(record) );
   ATLASSERT( result.second == true );
}

bool CBruteForceVehicularResponse2::IsPoiAtSupport(BSTR stage,PoiIDType poiID)
{
   CComPtr<IInfluenceLineResponse> response;
   m_pInflStrategy->GetInfluenceLineResponse(&response);
   CComQIPtr<IVehicularAnalysisContext> context(response);
   CComQIPtr<IAnalysisPOIs> analysisPOIs(context);

   MemberType lbamMbrType;
   MemberIDType mbrID;
   Float64 mbrLocation;
   HRESULT hr = analysisPOIs->GetPoiInfo(stage, poiID, &lbamMbrType, &mbrID, &mbrLocation);
   ATLASSERT(SUCCEEDED(hr));
   IndexType targetSSMbrIdx = (IndexType)mbrID; // memberID is the member index

   CComPtr<ILBAMModel> model;
   context->get_Model(&model);

   CComPtr<IStages> stages;
   model->get_Stages(&stages);

   StageIndexType stageIdx;
   stages->FindIndex(stage,&stageIdx);
   ATLASSERT(stageIdx != INVALID_INDEX);

   // Find the global position of the POI (measured from the left support)
   Float64 Xg, Yg;
   model->ComputeLocation(mbrID, lbamMbrType, mbrLocation, &Xg, &Yg);

   ATLASSERT(IsZero(Yg));

   Float64 Xs = 0; // support locations
   if ( IsEqual(Xs,Xg) )
      return true; // poi is at first support

   CComPtr<ISpans> spans;
   model->get_Spans(&spans);
   SpanIndexType nSpans;
   spans->get_Count(&nSpans);
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans && Xs < Xg; spanIdx++ )
   {
      CComPtr<ISpan> span;
      spans->get_Item(spanIdx,&span);

      // Check it POI is at a temporary support
      CComPtr<ITemporarySupports> tempSupports;
      span->get_TemporarySupports(&tempSupports);
      IndexType nTS;
      tempSupports->get_Count(&nTS);
      for ( IndexType tsIdx = 0; tsIdx < nTS; tsIdx++ )
      {
         CComPtr<ITemporarySupport> tempSupport;
         tempSupports->get_Item(tsIdx,&tempSupport);

         // check to see if the temporary support has been removed
         CComBSTR bstrRemovalStage;
         tempSupport->get_StageRemoved(&bstrRemovalStage);

         StageIndexType removalStageIdx;
         stages->FindIndex(bstrRemovalStage,&removalStageIdx);

         if ( removalStageIdx <= stageIdx )
            continue; // it has been removed... continue with next temporary support

         // temporary support is active in this stage so see if it is at the location of this POI
         Float64 location;
         tempSupport->get_Location(&location);

         if ( IsEqual(Xg,Xs+location) )
            return true; // yep... poi is at the temporary support
      }

      // Now check for support at end of span
      Float64 length;
      span->get_Length(&length);

      Xs += length;
//      if ( spanIdx == nSpans-1 )
      {
         if ( IsEqual(Xs,Xg) )
         {
            return true; // poi is at the end of the span
         }
      }
   }

   return false;
}
