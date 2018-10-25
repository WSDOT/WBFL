///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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

// BruteForceVehicularResponse.cpp : Implementation of CBruteForceVehicularResponse
#include "stdafx.h"
#include <Float.h>

#include "WBFLLBAMLiveLoader.h"
#include "BruteForceVehicularResponse.h"
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

Float64 GetMinSpanLength(ISupportLocations* suppLocs)
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

/////////////////////////////////////////////////////////////////////////////
// CBruteForceVehicularResponse
CBruteForceVehicularResponse::CBruteForceVehicularResponse():
m_ModelDirty(true),
m_LiveLoadDirty(true),
m_MinVariableAxleIncrement(0.5),
m_ContextCookie(0),
m_InflStrategy(NULL),
m_DfStrategy(NULL),
m_ApplicabilityStrategy(NULL)
{
}

STDMETHODIMP CBruteForceVehicularResponse::InterfaceSupportsErrorInfo(REFIID riid)
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

void CBruteForceVehicularResponse::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_Context, this, IID_IVehicularAnalysisContextEvents, m_ContextCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CBruteForceVehicularResponse::Initialize(/*[in]*/IUnknown* context)
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
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<IInfluenceLineResponse> presp(context);
      if (presp!=NULL)
      {
         m_InfluenceLineResponse = presp;
      }
      else
      {
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<ILiveLoadNegativeMomentRegion> pcf(context);
      if (pcf!=NULL)
      {
         m_LiveLoadNegativeMomentRegion = pcf;
      }
      else
      {
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<IGetDistributionFactors> pdf(context);
      if (pdf!=NULL)
      {
         m_GetDistributionFactors = pdf;
      }
      else
      {
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<ISupportLocations> sup_locs(m_Context);
      if (sup_locs!=NULL)
      {
         m_SupportLocations = sup_locs;
      }
      else
      {
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<IGetStressPoints> gsp(context);
      if (gsp!=NULL)
      {
         m_GetStressPoints = gsp;
      }
      else
      {
         ATLASSERT(false);
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
STDMETHODIMP CBruteForceVehicularResponse::InitializeProgressMonitor(IProgressMonitor * newVal, LONG cookie)
{
   CHECK_IN(newVal);
   m_pProgressMonitor = newVal;
   m_ProgressCookie = cookie;

   return S_OK;
}


STDMETHODIMP CBruteForceVehicularResponse::ComputeForces(IIDArray* poiIDs, BSTR stage, LiveLoadModelType type, 
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
      m_InflStrategy = &InflStrategy;

      ForceDistributionFactorStrategy DfStrategy(m_GetDistributionFactors, optimization);
      m_DfStrategy = &DfStrategy;

      ForceLLApplicabilityStrategy ApplStrategy(m_LiveLoadNegativeMomentRegion);
      m_ApplicabilityStrategy = &ApplStrategy;

      // need to place truck before and after pois to capture shear response jumps
      if (effect==fetFy)
         m_CaptureJumps = true;
      else
         m_CaptureJumps = false;

      hr = ComputeResponse(poiIDs, stage, type, 
                           vehicleIndex,
                           effect, optimization, 
                           vehConfiguration,
                           doApplyImpact, distributionType,
                           computePlacements,
                           pResults);

      m_InflStrategy          = NULL;
      m_DfStrategy            = NULL;
      m_ApplicabilityStrategy = NULL;

   }
   catch(...)
   {
      m_InflStrategy          = NULL;
      m_DfStrategy            = NULL;
      m_ApplicabilityStrategy = NULL;

      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }
   return hr;
}

STDMETHODIMP CBruteForceVehicularResponse::ComputeDeflections(IIDArray* pois, BSTR stage, LiveLoadModelType type, 
                                                            VehicleIndexType vehicleIndex, 
                                                            ForceEffectType effect, OptimizationType optimization, 
                                                            VehicularLoadConfigurationType vehConfiguration,
                                                            VARIANT_BOOL doApplyImpact, DistributionFactorType distributionType,
                                                            VARIANT_BOOL computePlacements,
                                                            ILiveLoadModelSectionResults** pResults)
{
   CHECK_IN(pois);
   CHECK_IN(stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      // set up context and strategies
      DeflectionInfluenceLineStrategy InflStrategy(m_InfluenceLineResponse);
      m_InflStrategy = &InflStrategy;

      DeflectionDistributionFactorStrategy DfStrategy(m_GetDistributionFactors);
      m_DfStrategy = &DfStrategy;

      DeflectionLLApplicabilityStrategy ApplStrategy;
      m_ApplicabilityStrategy = &ApplStrategy;

      m_CaptureJumps = false;

      hr = this->ComputeResponse(pois, stage, type, 
                                   vehicleIndex,  
                                   effect, optimization, 
                                   vehConfiguration,
                                   doApplyImpact, distributionType,
                                   computePlacements,
                                   pResults);

      m_InflStrategy = NULL;
      m_DfStrategy = NULL;
      m_ApplicabilityStrategy = NULL;
   }
   catch(...)
   {
      m_InflStrategy          = NULL;
      m_DfStrategy            = NULL;
      m_ApplicabilityStrategy = NULL;

      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

   return hr;
}

STDMETHODIMP CBruteForceVehicularResponse::ComputeReactions(IIDArray* supports, BSTR stage, LiveLoadModelType type, 
                                                            VehicleIndexType vehicleIndex, 
                                                            ForceEffectType effect, OptimizationType optimization, 
                                                            VehicularLoadConfigurationType vehConfiguration,
                                                            VARIANT_BOOL doApplyImpact, DistributionFactorType distributionType,
                                                            VARIANT_BOOL computePlacements,
                                                            ILiveLoadModelResults** pResults)
{
   CHECK_IN(supports);
   CHECK_IN(stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      // set up context and strategies
      ReactionInfluenceLineStrategy InflStrategy(m_InfluenceLineResponse);
      m_InflStrategy = &InflStrategy;

      ReactionDistributionFactorStrategy DfStrategy(m_GetDistributionFactors);
      m_DfStrategy = &DfStrategy;

      ReactionLLApplicabilityStrategy ApplStrategy(m_SupportLocations);
      m_ApplicabilityStrategy = &ApplStrategy;

      m_CaptureJumps = false;

      // compute left and right results and use max of both
      CComPtr<ILiveLoadModelSectionResults> sec_res;

      hr = this->ComputeResponse(supports, stage, type, 
                                   vehicleIndex,  
                                   effect, optimization, 
                                   vehConfiguration,
                                   doApplyImpact, distributionType,
                                   computePlacements,
                                   &sec_res);

      m_InflStrategy          = NULL;
      m_DfStrategy            = NULL;
      m_ApplicabilityStrategy = NULL;

      // copy section results to non-section based - taking local maxes along the way
      CComPtr<ILiveLoadModelResults> results;
      LLSectionToRes(sec_res, optimization, &results);

      hr = results.CopyTo(pResults);
   }
   catch(...)
   {
      m_InflStrategy          = NULL;
      m_DfStrategy            = NULL;
      m_ApplicabilityStrategy = NULL;

      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

   return hr;
}

STDMETHODIMP CBruteForceVehicularResponse::ComputeSupportDeflections(IIDArray* supports, BSTR stage, LiveLoadModelType type, 
                                                            VehicleIndexType vehicleIndex, 
                                                            ForceEffectType effect, OptimizationType optimization, 
                                                            VehicularLoadConfigurationType vehConfiguration,
                                                            VARIANT_BOOL doApplyImpact, DistributionFactorType distributionType,
                                                            VARIANT_BOOL computePlacements,
                                                            ILiveLoadModelResults** pResults)
{
   CHECK_IN(supports);
   CHECK_IN(stage);
   CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      // set up context and strategies
      SupportDeflectionInfluenceLineStrategy InflStrategy(m_InfluenceLineResponse);
      m_InflStrategy = &InflStrategy;

      SupportDeflectionDistributionFactorStrategy DfStrategy(m_GetDistributionFactors);
      m_DfStrategy = &DfStrategy;

      SupportDeflectionLLApplicabilityStrategy ApplStrategy;
      m_ApplicabilityStrategy = &ApplStrategy;

      m_CaptureJumps = false;

      // compute left and right results and use max of both
      CComPtr<ILiveLoadModelSectionResults> sec_res;
      hr = this->ComputeResponse(supports, stage, type, 
                                   vehicleIndex,  
                                   effect, optimization, 
                                   vehConfiguration,
                                   doApplyImpact, distributionType,
                                   computePlacements,
                                   &sec_res);

      m_InflStrategy = NULL;
      m_DfStrategy = NULL;

      // copy section results to non-section based - taking local maxes along the way
      CComPtr<ILiveLoadModelResults> results;
      LLSectionToRes(sec_res, optimization, &results);

      hr = results.CopyTo(pResults);
   }
   catch(...)
   {
      m_InflStrategy          = NULL;
      m_DfStrategy            = NULL;
      m_ApplicabilityStrategy = NULL;

      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

   return hr;
}

STDMETHODIMP CBruteForceVehicularResponse::ComputeStresses(IIDArray* poiIDs, BSTR stage, LiveLoadModelType type, 
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

STDMETHODIMP CBruteForceVehicularResponse::ComputeResponse(IIDArray* poiIDs, BSTR stage, LiveLoadModelType type, 
                                                           VehicleIndexType vehicleIndex, 
                                                           ForceEffectType effect, OptimizationType optimization, 
                                                           VehicularLoadConfigurationType vehConfiguration,
                                                           VARIANT_BOOL doApplyImpact, DistributionFactorType distributionType,
                                                           VARIANT_BOOL vbComputePlacements,
                                                           ILiveLoadModelSectionResults** pResults)
{
   CHRException hr;
   try
   {
      AssertValid();

      // set up cached values for response locations, vehicle configuration, and local truck
      Compute(stage, type, vehicleIndex, vehConfiguration, doApplyImpact);

      CollectionIndexType nPOI;
      hr = poiIDs->get_Count(&nPOI);

      // create results collection
      CComObject<CLiveLoadModelSectionResults>* cresults;
      CComObject<CLiveLoadModelSectionResults>::CreateInstance(&cresults);
      CComPtr<ILiveLoadModelSectionResults> results(cresults);
      hr = results->Reserve(nPOI);


      // see if this effect has a sign change at left/right faces
      Float64 flip_factor = m_InflStrategy->SignFlip();

      for (CollectionIndexType poiIdx = 0; poiIdx < nPOI; poiIdx++)
      {
         HANDLE_CANCEL_PROGRESS();

         PoiIDType poiID;
         hr = poiIDs->get_Item(poiIdx, &poiID);

         // our results for this round
         Float64 left_result  = 0.0;
         Float64 right_result = 0.0;
         CComPtr<ILiveLoadConfiguration> left_config;
         CComPtr<ILiveLoadConfiguration> right_config;

         // create dummy live load configurations
         if (vbComputePlacements == VARIANT_TRUE)
         {
            CComObject<CLiveLoadConfiguration>* pconfig;
            hr = CComObject<CLiveLoadConfiguration>::CreateInstance(&pconfig);

            left_config = pconfig;
            left_config->put_IsApplicable(VARIANT_FALSE);

            pconfig = NULL;
            hr = CComObject<CLiveLoadConfiguration>::CreateInstance(&pconfig);
            right_config = pconfig;
            right_config->put_IsApplicable(VARIANT_FALSE);
         }

         // see if our live load is applicable at this location
         ApplicabilityLoc applicabilityloc = m_ApplicabilityStrategy->GetApplicability(poiID, stage, 
                                                                 VARIANT_TRUE, m_LiveLoadApplicability, 
                                                                 effect, optimization);
         if (applicabilityloc != appNone)
         {

            // get our influence line(s)
            CComPtr<IInfluenceLine> lft_infl_line, rgt_infl_line;
            hr = m_InflStrategy->ComputeInfluenceLine(poiID, stage, effect, &lft_infl_line, &rgt_infl_line);

            // compute responses for left influence line
            // the only time we don't compute left influence results is for right applicability with a valid right influence 
            if ( !(applicabilityloc==appRight && rgt_infl_line!=NULL) )
            {
               ComputeInflResponse(type, vehicleIndex, effect, optimization, vehConfiguration, doApplyImpact, vbComputePlacements, 
                                   lft_infl_line, &left_result, &right_result, left_config, right_config);

            }
         
            if (applicabilityloc == appLeft)
            {
               // results only applicable to left side - zero out right
               right_result = 0.0;

               if (vbComputePlacements == VARIANT_TRUE)
               {  
                  right_config->put_IsApplicable(VARIANT_FALSE);
               }
            }
            else if (applicabilityloc == appRight)
            {

               if (rgt_infl_line != NULL)
               {
                  // compute responses for right influence line
                  // We have to fake out compute function because it does not know anything about left/right face 
                  // sign conventions
                  OptimizationType loc_optimization = optimization;
                  if (flip_factor==-1.0)
                  {
                     loc_optimization = (optimization==optMaximize) ? optMinimize : optMaximize;
                  }

                  ComputeInflResponse(type, vehicleIndex, effect, loc_optimization, vehConfiguration, doApplyImpact, vbComputePlacements, 
                                      rgt_infl_line, &left_result, &right_result, left_config, right_config);

                  if (vbComputePlacements == VARIANT_TRUE)
                  {
                     right_config->put_Optimization(optimization); // make sure we're in right sign convention
                  }
               }
               else
               {
                  // results were computed using left influence line above
                  right_result *= flip_factor;
               }

               // only applicable to right side - zero out any computed left results
               left_result = 0.0;

               if (vbComputePlacements == VARIANT_TRUE)
               {  
                  left_config->put_IsApplicable(VARIANT_FALSE);
               }

            }
            else if (applicabilityloc == appBoth)
            {
               if (rgt_infl_line != NULL)
               {
                  // compute responses for right influence line
                  // create a bogus result and  configuration object to hold the left result since we won't be using it
                  Float64 bog_left_result;
                  CComPtr<ILiveLoadConfiguration> bog_left_config;
                  if (vbComputePlacements == VARIANT_TRUE)
                  {
                     CComObject<CLiveLoadConfiguration>* pconfig;
                     hr = CComObject<CLiveLoadConfiguration>::CreateInstance(&pconfig);

                     bog_left_config =pconfig;
                     bog_left_config->put_IsApplicable(VARIANT_FALSE);
                  }

                  // We have to fake out compute function because it does not know anything about left/right face 
                  // sign conventions
                  OptimizationType loc_optimization = optimization;
                  if (flip_factor==-1.0)
                  {
                     loc_optimization = (optimization==optMaximize) ? optMinimize : optMaximize;
                  }

                  ComputeInflResponse(type, vehicleIndex, effect, loc_optimization, vehConfiguration, doApplyImpact, vbComputePlacements, 
                                      rgt_infl_line, &bog_left_result, &right_result, bog_left_config, right_config);

                  if (vbComputePlacements == VARIANT_TRUE)
                  {  
                     right_config->put_Optimization(optimization); // make sure we're in right sign convention
                  }
               }
               else
               {
                  // results were computed using left influence line above
                  right_result *= flip_factor;
               }

            }
            else
            {
               ATLASSERT(false); // should never get here
            }
         }
         else
         {
            // Live load not applible at this location... do nothing
            ATLASSERT(applicabilityloc == appNone);
         }

         // apply distribution factors if desired
         if (distributionType != dftNone)
         {
            Float64 left_dfactor  = 1.0;
            Float64 right_dfactor = 1.0;
            DistributionFactorType left_used_dftype, right_used_dftype;
            m_DfStrategy->GetOptimalDfs(poiID, stage, effect, distributionType,
                                                 &left_dfactor, &left_used_dftype, 
                                                 &right_dfactor, &right_used_dftype);

            left_result  *= left_dfactor;
            right_result *= right_dfactor;

            if (vbComputePlacements == VARIANT_TRUE)
            {
               hr = left_config->put_DistributionFactorType(left_used_dftype);
               hr = right_config->put_DistributionFactorType(right_used_dftype);
            }
         }

         // add our result to the collection
         if ( optimization == optMaximize )
         {
            if ( left_result > flip_factor*right_result )
               hr = results->Add(left_result, left_config, flip_factor*left_result, left_config);
            else
               hr = results->Add(flip_factor*right_result, right_config, right_result, right_config);
         }
         else
         {
            if ( left_result < flip_factor*right_result )
               hr = results->Add(left_result, left_config, flip_factor*left_result, left_config);
            else
               hr = results->Add(flip_factor*right_result, right_config, right_result, right_config);
         }
//         hr = results->Add(left_result, left_config, right_result, right_config);
      }

      hr = results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IEnvelopedVehicularResponse);
   }

	return hr;
}

void CBruteForceVehicularResponse::ComputeInflResponse(LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                                                       VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                                                       VARIANT_BOOL computePlacements, IInfluenceLine* inflLine, 
                                                       Float64* leftResult, Float64 *rightResult, 
                                                       ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig)
{
   CHRException hr;

   *leftResult = 0.0;
   *rightResult = 0.0;

   // Determine side of influence line where we will be working
   InfluenceSideType truck_side;
   if (m_IsNotional)
      truck_side = optimization==optMaximize ? ilsPositive : ilsNegative;
   else
      truck_side = ilsBoth;

   // check to see if the influence line is flat - no use running trucks over nothing
   VARIANT_BOOL is_influence_zero;
   hr = inflLine->IsZero(truck_side, &is_influence_zero);

   if (is_influence_zero == VARIANT_FALSE)
   {
      // have applicable, valid influence line

      // set up loop parameters for truck placement. 
      // We place truck before and after poi to pick up shear jumps due to axle loads
      Float64 plc_delta[3];
      long pls_loops;
      if (m_CaptureJumps)
      {
         pls_loops = 3;
         plc_delta[0] = -m_TruckPlacementTolerance;
         plc_delta[1] = 0.0;
         plc_delta[2] =  m_TruckPlacementTolerance;
      }
      else
      {
         pls_loops = 1;
         plc_delta[0] = 0.0;
      }

      // set up our class for doing value comparisons - remember this function works on left-face coordinates
      iLLCompare* left_compare;
      iLLCompare* right_compare;
      IntializeCompare(optimization, &left_compare, &right_compare);

      Float64 left_truck_result = 0;
      Float64 right_truck_result = 0;

      if (m_IsTruck)
      {
         AxleIndexType num_axles = m_Truck.GetNumAxles();

         std::vector<AxleState> applied_axles;
         applied_axles.reserve(num_axles);

         // loop over truck forward and backwards
         TruckDirectionType directions[2] = {ltdForward, ltdReverse};
         for (int idir = 0; idir < 2; idir++)
         {
            TruckDirectionType direction = directions[idir];
            m_Truck.SetTruckDirection(direction);

            // loop over each axle spacing for the truck
            for (AxleSpacingIterator axleSpacingIter = m_AxleSpacings.begin(); axleSpacingIter != m_AxleSpacings.end(); axleSpacingIter++)
            {
               Float64 axle_spacing = *axleSpacingIter;

               if ( m_Truck.IsVariableAxle() )
               {
                  m_Truck.SetVariableAxleSpacing( axle_spacing );
               }

               // loop over all pois and place each axle at every poi
               for (PoiLocationIterator pli = m_PoiLocations.begin(); pli!=m_PoiLocations.end(); pli++)
               {
                  Float64 poi_loc = pli->Location;
                  // place truck slighly before and after poi, but only for shear response
                  for (long ipls=0; ipls<pls_loops; ipls++)
                  {
                     Float64 bumper_loc = poi_loc + plc_delta[ipls];

                     for (AxleIndexType axleIndex = 0; axleIndex < num_axles; axleIndex++)
                     {
                        Float64 axle_loc       = m_Truck.GetAxleLocation(axleIndex);
                        Float64 truck_location = bumper_loc - axle_loc;

                        if (!applied_axles.empty())
                           applied_axles.clear();

                        VARIANT_BOOL is_dual;
                        Float64 left_tres, right_tres;

                        m_Truck.EvaluatePrimaryInfl(truck_location, truck_side, inflLine, 
                                                    &applied_axles, &is_dual, &left_tres, &right_tres);

                        // perform comparison and store data for new max if there is one.
                        if (left_compare->CompareResults(left_tres))
                        {
                           left_compare->StoreState(left_tres, truck_location, direction, applied_axles, axle_spacing);
                        }

                        if (right_compare->CompareResults(right_tres))
                        {
                           right_compare->StoreState(right_tres, truck_location, direction, applied_axles, axle_spacing);
                        }
                     }
                  }
               }
            }
         }

         left_truck_result   = left_compare->GetResult();
         right_truck_result  = right_compare->GetResult();

         if (computePlacements == VARIANT_TRUE)
         {
             left_compare->ConfigureTruckPlacement(leftConfig, type, vehicleIndex, vehConfiguration, 
                                                   effect, optimization, doApplyImpact);
             right_compare->ConfigureTruckPlacement(rightConfig, type, vehicleIndex, vehConfiguration, 
                                                    effect, optimization, doApplyImpact);
         }
      }
      else
      {
         // placement makes no sense if there is no truck defined
      }

      // deal with lane and sidewalk results
      Float64 lane_result = 0.0;
      Float64 sidewalk_result = 0.0;
      if (m_IsLane || m_IsSidewalk)
      {
         InfluenceSideType lane_side = optimization==optMaximize ? ilsPositive : ilsNegative;

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
         *leftResult  =  left_truck_result  + lane_result;
         *rightResult =  right_truck_result + lane_result;
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
         ATLASSERT(false);
         throw E_INVALIDARG;
      }
   }
}
 
void CBruteForceVehicularResponse::Compute(BSTR stage, LiveLoadModelType type, VehicleIndexType vehicleIndex,
                                           VehicularLoadConfigurationType vehConfiguration, 
                                           VARIANT_BOOL doApplyImpact)
{
   CHRException hr;

   Float64 model_length;
   hr = m_SupportLocations->get_TotalLength(&model_length);

   // see if we already have initialized our truck for this case
   if (m_LiveLoadDirty || 
       type!=m_CachedLiveLoadModel || 
       vehicleIndex!=m_CachedVehicleIndex || 
       vehConfiguration!=m_CachedVehConfiguration ||
       doApplyImpact!=m_CachedDoApplyImpact) 
   {
      // get vehicle
      CComPtr<IVehicularLoad> pvl;
      GetVehicularLoad(type, vehicleIndex, m_LiveLoad, &pvl);

      // update our cache control variables
      m_CachedVehConfiguration = GetSelectedVehicularConfiguration( vehConfiguration, pvl);
      m_CachedLiveLoadModel = type;
      m_CachedVehicleIndex = vehicleIndex;
      m_CachedDoApplyImpact = doApplyImpact;

      // Compute some control information
      m_IsTruck    = m_CachedVehConfiguration==vlcTruckOnly || m_CachedVehConfiguration==vlcTruckPlusLane || m_CachedVehConfiguration==vlcTruckLaneEnvelope;
      m_IsLane     = m_CachedVehConfiguration==vlcLaneOnly  || m_CachedVehConfiguration==vlcTruckPlusLane || m_CachedVehConfiguration==vlcTruckLaneEnvelope;
      m_IsSidewalk = m_CachedVehConfiguration==vlcSidewalkOnly;

      // get fixed axle configuration wrt datum - factor axle weights
      if (m_IsTruck)
      {
         m_Truck.Initialize(pvl, (m_CachedDoApplyImpact!=VARIANT_FALSE) );
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
            ATLASSERT(lane_im>0.0);

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

      // set up axle spacings for variable axle trucks
      m_AxleSpacings.clear();
      if (m_Truck.IsVariableAxle())
      {
         Float64 min_axle_spacing = m_Truck.GetMinVariableAxleSpacing();
         Float64 max_axle_spacing = m_Truck.GetMaxVariableAxleSpacing();

         if (max_axle_spacing <= min_axle_spacing)
         {
            THROW_LBAMLL(INVALID_VAR_SPACING);
         }

         // make sure superstructure is longer than min spacing length
         if (min_axle_spacing < model_length)
         {
            // Set max spacing so that it does not exceed length of bridge
            if (model_length < max_axle_spacing)
            {
               max_axle_spacing = model_length;
            }

            ATLASSERT(0 < m_MinVariableAxleIncrement);

            long num_spacings;
            Float64 delta;

            // compute variable axle increments
            Float64 min_span_length = GetMinSpanLength(m_SupportLocations);
            
            // prevent the maximum axle spacing to be larger than the minimum span length
            if ( min_span_length < max_axle_spacing )
               max_axle_spacing = min_span_length;

            Float64 diff = max_axle_spacing - min_axle_spacing;
            Float64 truck_delta = diff / 8;
            if ( m_MinVariableAxleIncrement < truck_delta )
            {
               delta = truck_delta;
               num_spacings = 9;
            }
            else
            {
               num_spacings = (int)((diff-1.0e-5)/m_MinVariableAxleIncrement) + 1;
               delta = diff / num_spacings;
               num_spacings++;
            }

            Float64 spacing = min_axle_spacing;
            for (long is = 0; is < num_spacings; is++)
            {
               ATLASSERT( IsGE(min_axle_spacing,spacing) && IsLE(spacing,max_axle_spacing) );
               m_AxleSpacings.push_back(spacing);
               spacing += delta;
            }
            ATLASSERT( IsEqual(min_axle_spacing,m_AxleSpacings.front()) );
            ATLASSERT( IsEqual(max_axle_spacing,m_AxleSpacings.back()) );
         }
         else
         {
            // entire superstructure is shorter than min variable axle spacing. only need to use min spacing
            m_AxleSpacings.push_back(min_axle_spacing);
         }
      }
      else
      {
         // no variable axles put a dummy in the array so our computation loop will work
         m_AxleSpacings.push_back(0.0);
      }

      m_LiveLoadDirty = false;
   }

   // get response locations from model
   if (m_ModelDirty || m_CachedStage!=_bstr_t(stage))
   {
      m_PoiLocations.clear();

      CComQIPtr<IAnalysisPOIs> poi_utility(m_Context);
      CComPtr<IIDArray> poiids;
      CComPtr<IDblArray> poilocs;
      hr = poi_utility->GetSuperstructurePois(stage , &poiids, &poilocs);

      CollectionIndexType nPOI;
      hr = poiids->get_Count(&nPOI);
#ifdef _DEBUG
      CollectionIndexType tsiz;
      hr = poilocs->get_Count(&tsiz);
      ATLASSERT(nPOI==tsiz);
#endif
      Float64 last_loc;
      bool first = true;
      for (CollectionIndexType poiIdx = 0; poiIdx < nPOI; poiIdx++)
      {
         PoiIDType poiID;
         hr = poiids->get_Item(poiIdx, &poiID);

         Float64 loc;
         hr = poilocs->get_Item(poiIdx, &loc);

         last_loc = loc;

         // remove redundant locations
         if (first || last_loc!=loc)
         {
            m_PoiLocations.push_back( PoiLocation(poiID,loc) );
         }
      }

      m_TruckPlacementTolerance = model_length/10000.0;

      m_ModelDirty=false;
      m_CachedStage = stage;
   }
}


void CBruteForceVehicularResponse::IntializeCompare(OptimizationType optimization, iLLCompare** pleftCompare, iLLCompare** prightCompare)
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

void CBruteForceVehicularResponse::AssertValid()
{
   ATLASSERT(m_InflStrategy != NULL);

   if (m_LiveLoad == NULL)
   {
      // must be initialized before use
      THROW_LBAMLL(LL_INITIALIZATION);
   }

   ATLASSERT(m_MinVariableAxleIncrement>0);
}

STDMETHODIMP CBruteForceVehicularResponse::OnLiveLoadChanged( LiveLoadModelType type)
{
   m_LiveLoadDirty = true;
   return S_OK;
}

STDMETHODIMP CBruteForceVehicularResponse::OnStiffnessResponseChanged(ChangeScopeType scope, PoiIDType poiID)
{
   m_ModelDirty = true;
   m_CachedStage = "";
   return S_OK;
}