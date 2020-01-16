///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2020  Washington State Department of Transportation
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

// BasicVehicularResponse.cpp : Implementation of CBasicVehicularResponse
#include "stdafx.h"
#include "WBFLLBAMLiveLoader.h"
#include "BasicVehicularResponse.h"
#include "LBAMLiveLoader.hh"
#include "Truck.h"
#include "LiveLoaderUtils.h"

#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// free functions
/////////////////
// handle dealing with cancel from progress monitor
#define HANDLE_CANCEL_PROGRESS() if (this->CheckForCancel()) throw S_FALSE;

static bool DetermineControl(Float64 truckResp, Float64 laneResp, OptimizationType optimization)
{
   
   if (optimization==optMaximize)
      return truckResp>laneResp;
   else
      return truckResp<laneResp;
}

static void  ComputeLaneAreas(ForceEffectType optimizedEffect, OptimizationType optimization, Float64 flipFactor,
                       IInfluenceLine* lftFxInf, IInfluenceLine* rgtFxInf, IInfluenceLine* lftFyInf, IInfluenceLine* rgtFyInf, IInfluenceLine* lftMzInf, IInfluenceLine* rgtMzInf,
                       Float64* lftFxArea, Float64* lftFyArea, Float64* lftMzArea, Float64* rgtFxArea, Float64* rgtFyArea, Float64* rgtMzArea)
{
   CHRException hr;

   // have to calculate regions that unif lane load is applied for optimized effect. Then
   // apply lane/sidewalk in same regions for all effects
   // First compute for left influence line

   InfluenceSideType lane_side = optimization==optMaximize ? ilsPositive : ilsNegative;

   CComPtr<IDblArray> regions;
   switch (optimizedEffect)
   {
   case fetFx:
      if ( lftFxInf )
         hr = lftFxInf->ComputeNonZeroRegions(lane_side, &regions);
      break;
   case fetFy:
      if ( lftFyInf )
         hr = lftFyInf->ComputeNonZeroRegions(lane_side, &regions);
      break;
   case fetMz:
      if ( lftMzInf )
         hr = lftMzInf->ComputeNonZeroRegions(lane_side, &regions);
      break;
   default:
      ATLASSERT(false);
   };

   if ( lftFxInf )
      hr = lftFxInf->ComputeAreaInRegions(regions, lftFxArea);
   else
      *lftFxArea = 0;

   if ( lftFyInf )
      hr = lftFyInf->ComputeAreaInRegions(regions, lftFyArea);
   else
      *lftFyArea = 0;

   if ( lftMzInf )
      hr = lftMzInf->ComputeAreaInRegions(regions, lftMzArea);
   else
      *lftMzArea = 0;

   // if right influence lines are null, we use left value with sign flip if necesary
   if (rgtFxInf==nullptr || rgtFyInf==nullptr || rgtMzInf==nullptr)
   {
      *rgtFxArea = (*lftFxArea)*flipFactor;
      *rgtFyArea = (*lftFyArea)*flipFactor;
      *rgtMzArea = (*lftMzArea)*flipFactor;
   }
   else
   {
      // have right influence lines - need to compute areas explicitely
      if (flipFactor==-1.0)
      {
         lane_side = optimization==optMaximize ? ilsNegative : ilsPositive;
      }

      CComPtr<IDblArray> rgt_regions;
      switch (optimizedEffect)
      {
      case fetFx:
          hr = rgtFxInf->ComputeNonZeroRegions(lane_side, &rgt_regions);
          break;
      case fetFy:
          hr = rgtFyInf->ComputeNonZeroRegions(lane_side, &rgt_regions);
         break;
      case fetMz:
          hr = rgtMzInf->ComputeNonZeroRegions(lane_side, &rgt_regions);
         break;
      default:
         ATLASSERT(false);
      };

      hr = rgtFxInf->ComputeAreaInRegions(rgt_regions, rgtFxArea);
      hr = rgtFyInf->ComputeAreaInRegions(rgt_regions, rgtFyArea);
      hr = rgtMzInf->ComputeAreaInRegions(rgt_regions, rgtMzArea);
   }
}

/////////////////////////////////////////////////////////////////////////////
// CBasicVehicularResponse

STDMETHODIMP CBasicVehicularResponse::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBasicVehicularResponse
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CBasicVehicularResponse::Initialize(/*[in]*/IUnknown* context)
{
   try
   {
      if (m_LiveLoad != nullptr)
      {
         // can only initialize once
         THROW_LBAMLL(LL_INITIALIZATION);
      }

      // Latch onto the parts of the context we need 
      // We don't need events either
      CComQIPtr<ILiveLoad> pll(context);
      if (pll!=nullptr)
      {
         m_LiveLoad = pll;
      }
      else
      {
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<IInfluenceLineResponse> presp(context);
      if (presp!=nullptr)
      {
         m_InfluenceLineResponse = presp;
      }
      else
      {
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<ILiveLoadNegativeMomentRegion> cfresp(context);
      if (presp!=nullptr)
      {
         m_LiveLoadNegativeMomentRegion = cfresp;
      }
      else
      {
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<IGetDistributionFactors> pdf(context);
      if (pdf!=nullptr)
      {
         m_GetDistributionFactors = pdf;
      }
      else
      {
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }

      CComQIPtr<IGetStressPoints> gsp(context);
      if (gsp!=nullptr)
      {
         m_GetStressPoints = gsp;
      }
      else
      {
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }


      CComQIPtr<ISupportLocations> sup_locs(context);
      if (sup_locs!=nullptr)
      {
         m_SupportLocations = sup_locs;
      }
      else
      {
         ATLASSERT(false);
         THROW_LBAMLL(INVALID_VEHICULAR_CONTEXT);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IBasicVehicularResponse);
   }

   return S_OK;
}

void CBasicVehicularResponse::QuickInitialize(ILiveLoad* liveLoad, IInfluenceLineResponse* influenceLineResponse, 
                                              ILiveLoadNegativeMomentRegion* llnmr, 
                                              IGetDistributionFactors* getDistributionFactors,
                                              ISupportLocations* supportLocations, 
                                              IGetStressPoints* getStressPoints)
{
   if (m_LiveLoad != nullptr)
   {
      // can only initialize once
      THROW_LBAMLL(LL_INITIALIZATION);
   }

   m_LiveLoad                      = liveLoad;
   m_InfluenceLineResponse         = influenceLineResponse;
   m_LiveLoadNegativeMomentRegion  = llnmr;
   m_GetDistributionFactors        = getDistributionFactors;
   m_GetStressPoints               = getStressPoints;
   m_SupportLocations              = supportLocations;
}

// ISupportProgressMonitor
STDMETHODIMP CBasicVehicularResponse::InitializeProgressMonitor(IProgressMonitor * newVal, LONG cookie)
{
   CHECK_IN(newVal);
   m_pProgressMonitor = newVal;
   m_ProgressCookie = cookie;

   return S_OK;
}

STDMETHODIMP CBasicVehicularResponse::ComputeForces(IIDArray* POIs, BSTR stage, ResultsOrientation orientation,
                                                    ILiveLoadConfiguration* config, ISectionResult3Ds* *results)
{
   CHECK_IN(POIs);
   CHECK_IN(stage);
//   CHECK_IN(config);
   CHECK_RETOBJ(results);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      if ( config )
      {
         // set up context and strategies
         ForceInfluenceLineStrategy InflStrategy(m_InfluenceLineResponse, orientation);
         m_InflStrategy = &InflStrategy;

         OptimizationType optimization;
         hr = config->get_Optimization(&optimization);

         ForceDistributionFactorStrategy DfStrategy(m_GetDistributionFactors, optimization);
         m_DfStrategy = &DfStrategy;

         ForceLLApplicabilityStrategy ApplStrategy(m_LiveLoadNegativeMomentRegion);
         m_ApplicabilityStrategy = &ApplStrategy;

         hr =  ComputeResponse(POIs, stage, config, results);

         m_InflStrategy = nullptr;
         m_DfStrategy = nullptr;
         m_ApplicabilityStrategy = nullptr;
      }
      else
      {
         CollectionIndexType poi_cnt;
         hr = POIs->get_Count(&poi_cnt);

         // create our results collection 
         CComPtr<ISectionResult3Ds> the_results;
         hr = the_results.CoCreateInstance(CLSID_SectionResult3Ds);
         hr = the_results->Reserve(poi_cnt);

         // just add empty results and return
         for (CollectionIndexType ipoi = 0; ipoi < poi_cnt; ipoi++)
         {
            CComPtr<ISectionResult3D> the_result;
            hr = the_result.CoCreateInstance(CLSID_SectionResult3D);
            hr = the_results->Add(the_result);
         }

         (*results) = the_results;
         (*results)->AddRef();
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IBasicVehicularResponse);
   }

   return hr;
}

STDMETHODIMP CBasicVehicularResponse::ComputeDeflections(IIDArray* POIs, BSTR stage,
                                                         ILiveLoadConfiguration* config, ISectionResult3Ds* *results)
{
   CHECK_IN(POIs);
   CHECK_IN(stage);
   CHECK_IN(config);
   CHECK_RETOBJ(results);

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

      hr =  ComputeResponse(POIs, stage, config, results);

      m_InflStrategy = nullptr;
      m_DfStrategy = nullptr;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IBasicVehicularResponse);
   }

   return hr;
}


STDMETHODIMP CBasicVehicularResponse::ComputeReactions(IIDArray* POIs, BSTR stage,
                                                       ILiveLoadConfiguration* config, IResult3Ds* *pResults)
{
   CHECK_IN(POIs);
   CHECK_IN(stage);
   CHECK_IN(config);
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

      // compute left and right results and use max of both
      CComPtr<ISectionResult3Ds> sec_res;
      hr =  ComputeResponse(POIs, stage, config, &sec_res);

      m_InflStrategy = nullptr;
      m_DfStrategy = nullptr;

      OptimizationType optimization;
      hr = config->get_Optimization(&optimization);

      CollectionIndexType ressize;
      hr = sec_res->get_Count(&ressize);

      CComPtr<IResult3Ds> loc_results;
      hr = loc_results.CoCreateInstance(CLSID_Result3Ds);
      hr = loc_results->Reserve(ressize);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_Result3D,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      for (CollectionIndexType is = 0; is<ressize; is++)
      {
         CComPtr<IResult3D> pres;
         hr = factory->CreateInstance(nullptr, IID_IResult3D, (void**)&pres);

         CComPtr<ISectionResult3D> sec_3d;
         hr = sec_res->get_Item(is, &sec_3d);

         Float64 fx_left, fy_left, mz_left;
         Float64 fx_right, fy_right, mz_right;
         hr = sec_3d->GetResult(&fx_left, &fy_left, &mz_left, &fx_right, &fy_right, &mz_right);

         if (optimization==optMaximize)
         {
            hr = pres->SetResult( max(fx_left,fx_right), max(fy_left,fy_right), max(mz_left,mz_right) );
         }
         else
         {
            hr = pres->SetResult( min(fx_left,fx_right), min(fy_left,fy_right), min(mz_left,mz_right) );
         }

         hr = loc_results->Add(pres);
      }

      hr = loc_results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IBasicVehicularResponse);
   }

   return hr;
}

STDMETHODIMP CBasicVehicularResponse::ComputeSupportDeflections(IIDArray* supports, BSTR stage,
                                                                ILiveLoadConfiguration* config, 
                                                                IResult3Ds* *pResults)
{
   CHECK_IN(supports);
   CHECK_IN(stage);
   CHECK_IN(config);
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

      // compute left and right results and use max of both
      CComPtr<ISectionResult3Ds> sec_res;
      hr =  ComputeResponse(supports, stage, config, &sec_res);

      m_InflStrategy = nullptr;
      m_DfStrategy = nullptr;

      OptimizationType optimization;
      hr = config->get_Optimization(&optimization);

      CollectionIndexType ressize;
      hr = sec_res->get_Count(&ressize);

      CComPtr<IResult3Ds> loc_results;
      hr = loc_results.CoCreateInstance(CLSID_Result3Ds);
      hr = loc_results->Reserve(ressize);

      // factory for results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_Result3D,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      for (CollectionIndexType is = 0; is<ressize; is++)
      {
         CComPtr<IResult3D> pres;
         hr = factory->CreateInstance(nullptr, IID_IResult3D, (void**)&pres);

         CComPtr<ISectionResult3D> sec_3d;
         hr = sec_res->get_Item(is, &sec_3d);

         Float64 fx_left, fy_left, mz_left;
         Float64 fx_right, fy_right, mz_right;
         hr = sec_3d->GetResult(&fx_left, &fy_left, &mz_left, &fx_right, &fy_right, &mz_right);

         if (optimization==optMaximize)
         {
            hr = pres->SetResult( max(fx_left,fx_right), max(fy_left,fy_right), max(mz_left,mz_right) );
         }
         else
         {
            hr = pres->SetResult( min(fx_left,fx_right), min(fy_left,fy_right), min(mz_left,mz_right) );
         }

         hr = loc_results->Add(pres);
      }

      hr =  loc_results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IBasicVehicularResponse);
   }

   return hr;
}

STDMETHODIMP CBasicVehicularResponse::ComputeStresses(IIDArray* POIs, BSTR stage,
                                                      ILiveLoadConfiguration* config, ISectionStressResults* *pResults)
{
   CHECK_IN(POIs);
   CHECK_IN(stage);
//   CHECK_IN(config);
   CHECK_RETOBJ(pResults);
   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      // compute forces for configuration
      CComPtr<ISectionResult3Ds> force_results;
      hr = this->ComputeForces(POIs, stage, roMember, config, &force_results);

      // create our results object
      CComPtr<ISectionStressResults> results;
      hr = results.CoCreateInstance(CLSID_SectionStressResults);

      CollectionIndexType num_res;
      hr = force_results->get_Count(&num_res);
      hr = results->Reserve(num_res);

      // factory for individual results
      CComPtr<IClassFactory> factory;
      hr = ::CoGetClassObject(CLSID_SectionStressResult,CLSCTX_ALL,nullptr,IID_IClassFactory,(void**)&factory);

      for (CollectionIndexType i = 0; i<num_res; i++)
      {
         PoiIDType poi_id;
         hr = POIs->get_Item(i,&poi_id);

         CComPtr<ISectionStressResult> stress_res;
         hr = factory->CreateInstance(nullptr, IID_ISectionStressResult, (void**)&stress_res);

         // forces
         CComPtr<ISectionResult3D> force_result;
         hr = force_results->get_Item(i, &force_result);

         Float64 fx_l, fy_l, mz_l, fx_r, fy_r, mz_r;
         hr = force_result->GetResult(&fx_l, &fy_l, &mz_l, &fx_r, &fy_r, &mz_r);

         HANDLE_CANCEL_PROGRESS();

         // stress coefficients
         CComPtr<IStressPoints> lft_sps, rgt_sps;
         this->GetStressPoints(poi_id, stage, &lft_sps, &rgt_sps);

         // left side
         CollectionIndexType num_sps;
         hr = lft_sps->get_Count(&num_sps);

         for (CollectionIndexType isp = 0; isp<num_sps; isp++)
         {
            CComPtr<IStressPoint> sp;
            hr = lft_sps->get_Item(isp,&sp);

            Float64 sa, sm;
            hr = sp->get_Sa(&sa);
            hr = sp->get_Sm(&sm);

            Float64 stress = fx_l*sa + mz_l*sm;

            hr = stress_res->AddLeftResult(stress);
         }

         // right side - uses left values if right is not distict
         if (rgt_sps==nullptr)
            rgt_sps = lft_sps;

         hr = rgt_sps->get_Count(&num_sps);

         for (CollectionIndexType isp = 0; isp<num_sps; isp++)
         {
            CComPtr<IStressPoint> sp;
            hr = rgt_sps->get_Item(isp,&sp);

            Float64 sa, sm;
            hr = sp->get_Sa(&sa);
            hr = sp->get_Sm(&sm);

            Float64 stress = -fx_r*sa - mz_r*sm;

            hr = stress_res->AddRightResult(stress);
         }

         hr = results->Add(stress_res);
      }

      hr = results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IBasicVehicularResponse);
   }

   return hr;
}

HRESULT CBasicVehicularResponse::ComputeResponse(IIDArray* POIs, BSTR stage,
                                                      ILiveLoadConfiguration* config, ISectionResult3Ds* *results)
{
   CHECK_IN(POIs);
   CHECK_IN(stage);
   CHECK_IN(config);
   CHECK_RETOBJ(results);

   CHRException hr;
	try
   {
      AssertValid();

      CollectionIndexType poi_cnt;
      hr = POIs->get_Count(&poi_cnt);

      // create our results collection 
      CComPtr<ISectionResult3Ds> the_results;
      hr = the_results.CoCreateInstance(CLSID_SectionResult3Ds);
      hr = the_results->Reserve(poi_cnt);

      // see if load placement is applicable
      VARIANT_BOOL is_applicable;
      hr = config->get_IsApplicable(&is_applicable);
      if (is_applicable == VARIANT_TRUE)
      {
         // get vehicle
         LiveLoadModelType llm_type;
         VehicleIndexType vehicle_index;
         hr = config->get_LiveLoadModel(&llm_type);
         hr = config->get_VehicleIndex(&vehicle_index);

         CComPtr<IVehicularLoad> pvl;
         GetVehicularLoad(llm_type, vehicle_index, m_LiveLoad, &pvl);

         // get application type and compute some control information
         VehicularLoadConfigurationType plc_config;
         hr = config->get_VehicularLoadConfiguration(&plc_config);
         VehicularLoadConfigurationType veh_configuration = GetSelectedVehicularConfiguration(plc_config, pvl);
         bool is_truck    = veh_configuration==vlcTruckOnly || veh_configuration==vlcTruckPlusLane ||veh_configuration==vlcTruckLaneEnvelope;
         bool is_lane     = veh_configuration==vlcLaneOnly  || veh_configuration==vlcTruckPlusLane ||veh_configuration==vlcTruckLaneEnvelope;
         bool is_sidewalk = veh_configuration==vlcSidewalkOnly;

         VARIANT_BOOL do_apply_impact;
         hr = config->get_DoApplyImpact(&do_apply_impact);

         DistributionFactorType df_type;
         hr = config->get_DistributionFactorType(&df_type);

         // get fixed axle configuration wrt datum - factor axle weights
         FixedTruck truck;
         Float64 truck_position=0.0;
         if (is_truck)
         {
            truck.Initialize(pvl, (do_apply_impact!=VARIANT_FALSE), config);

            // truck position along bridge
            hr = config->get_TruckPosition(&truck_position);
         }

         // compute lane load
         Float64 lane_load=0.0;
         if (is_lane)
         {
            hr = pvl->get_LaneLoad(&lane_load);

            Float64 lane_factor;
            hr = pvl->get_LaneFactor(&lane_factor);

            if (do_apply_impact == VARIANT_TRUE)
            {
               Float64 lane_impact;
               hr = pvl->get_IMLane(&lane_impact);

               lane_factor *= lane_impact;
            }

            lane_load *= lane_factor;

            if (lane_load==0.0) 
               is_lane = false;  // optimization
         }

         // compute sidewalk load
         Float64 sidewalk_load=0.0;
         if (is_sidewalk)
         {
            hr = pvl->get_SidewalkLoad(&sidewalk_load);
            if (sidewalk_load==0.0) 
               is_sidewalk = false;  // optimization
         }

         // get applicability of live load so we only apply it at applicable pois
         LiveLoadApplicabilityType llapplicability;
         hr = pvl->get_Applicability(&llapplicability);

         // see if notional model is to be used
         VARIANT_BOOL is_notional = VARIANT_FALSE;
         hr = pvl->get_UseNotional(&is_notional);

         OptimizationType optimization;
         hr = config->get_Optimization(&optimization);
         ForceEffectType optimized_effect;
         hr = config->get_ForceEffect(&optimized_effect);

         // see if this effect has a sign change at left/right faces
         Float64 flip_factor = m_InflStrategy->SignFlip();

         // optimization for right-side values is opposite of left if flip factor is -1
         OptimizationType rgt_optimization;
         if (flip_factor!= -1.0)
         {
            rgt_optimization = optimization;
         }
         else
         {
            rgt_optimization = optimization==optMaximize ? optMinimize : optMaximize;
         }

         // loop over pois, get influence lines and evaluate answers
         for (CollectionIndexType ipoi = 0; ipoi<poi_cnt; ipoi++)
         {
            HANDLE_CANCEL_PROGRESS();

            PoiIDType poi_id;
            hr = POIs->get_Item(ipoi, &poi_id);

            // our result
            Float64 lft_fx_result=0.0, lft_fy_result=0.0, lft_mz_result=0.0;
            Float64 rgt_fx_result=0.0, rgt_fy_result=0.0, rgt_mz_result=0.0;

            // see if we need to compute anything for this location
            ApplicabilityLoc applicabilityloc = m_ApplicabilityStrategy->GetApplicability(poi_id, stage, 
                                                                    VARIANT_TRUE, llapplicability, 
                                                                    optimized_effect, optimization);
            if (applicabilityloc != appNone)
            {
               CComPtr<IInfluenceLine> fx_lft_inf, fy_lft_inf, mz_lft_inf;
               CComPtr<IInfluenceLine> fx_rgt_inf, fy_rgt_inf, mz_rgt_inf;
               hr = m_InflStrategy->ComputeInfluenceLine(poi_id, stage, fetFx, &fx_lft_inf, &fx_rgt_inf);
               hr = m_InflStrategy->ComputeInfluenceLine(poi_id, stage, fetFy, &fy_lft_inf, &fy_rgt_inf);
               hr = m_InflStrategy->ComputeInfluenceLine(poi_id, stage, fetMz, &mz_lft_inf, &mz_rgt_inf);

               // Compute truck portion of response if requested
               Float64 lft_truck_resp_fx = 0.0, rgt_truck_resp_fx = 0.0;
               Float64 lft_truck_resp_fy = 0.0, rgt_truck_resp_fy = 0.0;
               Float64 lft_truck_resp_mz = 0.0, rgt_truck_resp_mz = 0.0;
               if (is_truck)
               {
                  // always evaluate with both sides of the influence line. We want the truck
                  // response in its current location and configuration (disappearing axle trick has
                  // already happened when determining the configuration, see truck.Initialize() above)
                  VARIANT_BOOL is_dual;
                  truck.EvaluatePrimary(truck_position, ilsBoth, flip_factor, fx_lft_inf, fx_rgt_inf, nullptr, nullptr, &is_dual, &lft_truck_resp_fx, &rgt_truck_resp_fx);
                  truck.EvaluatePrimary(truck_position, ilsBoth, flip_factor, fy_lft_inf, fy_rgt_inf, nullptr, nullptr, &is_dual, &lft_truck_resp_fy, &rgt_truck_resp_fy);
                  truck.EvaluatePrimary(truck_position, ilsBoth, flip_factor, mz_lft_inf, mz_rgt_inf, nullptr, nullptr, &is_dual, &lft_truck_resp_mz, &rgt_truck_resp_mz);
               }

               // Compute lane and sidewalk responses if requested
               Float64 lft_lane_resp_fx = 0.0, lft_lane_resp_fy = 0.0, lft_lane_resp_mz = 0.0;
               Float64 rgt_lane_resp_fx = 0.0, rgt_lane_resp_fy = 0.0, rgt_lane_resp_mz = 0.0;
               Float64 lft_sidewalk_resp_fx = 0.0, lft_sidewalk_resp_fy = 0.0, lft_sidewalk_resp_mz = 0.0;
               Float64 rgt_sidewalk_resp_fx = 0.0, rgt_sidewalk_resp_fy = 0.0, rgt_sidewalk_resp_mz = 0.0;

               if (is_lane || is_sidewalk)
               {
                  // Compute areas under influence lines for given action/optimization
                  Float64 lft_fx_area, lft_fy_area, lft_mz_area;
                  Float64 rgt_fx_area, rgt_fy_area, rgt_mz_area;

                  // vehicle config doesn't have the actual lane load configuraiton so
                  // we have to figure it out based on the optimization type and force effect
                  ComputeLaneAreas(optimized_effect, optimization, flip_factor,
                                   fx_lft_inf, fx_rgt_inf, fy_lft_inf, fy_rgt_inf,mz_lft_inf, mz_rgt_inf,
                                   &lft_fx_area, &lft_fy_area, &lft_mz_area, &rgt_fx_area, &rgt_fy_area, &rgt_mz_area);

                  // apply them to lane and sidewalk responses if requested
                  if (is_lane)
                  {
                     lft_lane_resp_fx = lane_load * lft_fx_area;
                     lft_lane_resp_fy = lane_load * lft_fy_area;
                     lft_lane_resp_mz = lane_load * lft_mz_area;
                     rgt_lane_resp_fx = lane_load * rgt_fx_area;
                     rgt_lane_resp_fy = lane_load * rgt_fy_area;
                     rgt_lane_resp_mz = lane_load * rgt_mz_area;
                  }

                  if (is_sidewalk)
                  {
                     lft_sidewalk_resp_fx = sidewalk_load * lft_fx_area;
                     lft_sidewalk_resp_fy = sidewalk_load * lft_fy_area;
                     lft_sidewalk_resp_mz = sidewalk_load * lft_mz_area;
                     rgt_sidewalk_resp_fx = sidewalk_load * rgt_fx_area;
                     rgt_sidewalk_resp_fy = sidewalk_load * rgt_fy_area;
                     rgt_sidewalk_resp_mz = sidewalk_load * rgt_mz_area;
                  }
               }

               // combine truck and lane response - both responses are already factored at this point
               if (veh_configuration==vlcTruckOnly)
               {
                  // truck only  
                  lft_fx_result = lft_truck_resp_fx;
                  lft_fy_result = lft_truck_resp_fy;
                  lft_mz_result = lft_truck_resp_mz;
                  rgt_fx_result = rgt_truck_resp_fx;
                  rgt_fy_result = rgt_truck_resp_fy;
                  rgt_mz_result = rgt_truck_resp_mz;
               }
               else if (veh_configuration==vlcLaneOnly)
               {
                  // lane only
                  lft_fx_result = lft_lane_resp_fx;
                  lft_fy_result = lft_lane_resp_fy;
                  lft_mz_result = lft_lane_resp_mz;
                  rgt_fx_result = rgt_lane_resp_fx;
                  rgt_fy_result = rgt_lane_resp_fy;
                  rgt_mz_result = rgt_lane_resp_mz;
               }
               else if (veh_configuration==vlcTruckPlusLane)
               {
                  // sum truck plus lane (LRFD)
                  lft_fx_result = lft_truck_resp_fx;
                  lft_fy_result = lft_truck_resp_fy;
                  lft_mz_result = lft_truck_resp_mz;
                  rgt_fx_result = rgt_truck_resp_fx;
                  rgt_fy_result = rgt_truck_resp_fy;
                  rgt_mz_result = rgt_truck_resp_mz;

                  if (is_lane)
                  {
                     lft_fx_result += lft_lane_resp_fx;
                     lft_fy_result += lft_lane_resp_fy;
                     lft_mz_result += lft_lane_resp_mz;
                     rgt_fx_result += rgt_lane_resp_fx;
                     rgt_fy_result += rgt_lane_resp_fy;
                     rgt_mz_result += rgt_lane_resp_mz;
                  }
               }
               else if (veh_configuration==vlcTruckLaneEnvelope)
               {
                  // envelope truck and lane response (LFD)
                  // first need to figure out if truck or lane controls
                  bool is_lft_truck, is_rgt_truck;
                  switch (optimized_effect)
                  {
                  case fetFx:
                     is_lft_truck = DetermineControl(lft_truck_resp_fx, lft_lane_resp_fx, optimization);
                     is_rgt_truck = DetermineControl(rgt_truck_resp_fx, rgt_lane_resp_fx, rgt_optimization);
                     break;
                  case fetFy:
                     is_lft_truck = DetermineControl(lft_truck_resp_fy, lft_lane_resp_fy, optimization);
                     is_rgt_truck = DetermineControl(rgt_truck_resp_fy,  rgt_lane_resp_fy, rgt_optimization);
                     break;
                  case fetMz:
                     is_lft_truck = DetermineControl(lft_truck_resp_mz, lft_lane_resp_mz, optimization);
                     is_rgt_truck = DetermineControl(rgt_truck_resp_mz, rgt_lane_resp_mz, rgt_optimization);
                     break;
                  default:
                     ATLASSERT(false);
                  };

                  // set result based on controlling effect
                  if (is_lft_truck)
                  {
                     lft_fx_result  = lft_truck_resp_fx;
                     lft_fy_result  = lft_truck_resp_fy;
                     lft_mz_result  = lft_truck_resp_mz;
                  }
                  else
                  {
                     lft_fx_result  = lft_lane_resp_fx;
                     lft_fy_result  = lft_lane_resp_fy;
                     lft_mz_result  = lft_lane_resp_mz;
                  }

                  if (is_rgt_truck)
                  {
                     rgt_fx_result = rgt_truck_resp_fx;
                     rgt_fy_result = rgt_truck_resp_fy;
                     rgt_mz_result = rgt_truck_resp_mz;
                  }
                  else
                  {
                     rgt_fx_result += rgt_lane_resp_fx;
                     rgt_fy_result += rgt_lane_resp_fy;
                     rgt_mz_result += rgt_lane_resp_mz;
                  }
               }
               else if (veh_configuration==vlcSidewalkOnly)
               {
                  // sidewalk only
                  lft_fx_result  = lft_sidewalk_resp_fx;
                  lft_fy_result  = lft_sidewalk_resp_fy;
                  lft_mz_result  = lft_sidewalk_resp_mz;
                  rgt_fx_result  = rgt_sidewalk_resp_fx;
                  rgt_fy_result  = rgt_sidewalk_resp_fy;
                  rgt_mz_result  = rgt_sidewalk_resp_mz;
               }
               else
               {
                  ATLASSERT(false);
               }

               // see if results are only applicable to left or right result
               if (applicabilityloc==appLeft)
               {
                  // results only applicable to left side - zero out right
                  rgt_fx_result = 0.0;
                  rgt_fy_result = 0.0;
                  rgt_mz_result = 0.0;
               }
               else if (applicabilityloc==appRight)
               {
                  // results only applicable to right side - zero out left
                  lft_fx_result = 0.0;
                  lft_fy_result = 0.0;
                  lft_mz_result = 0.0;
               }

               // apply distribution factor if requested
               if (df_type != dftNone)
               {
                  Float64 lft_fxfactor, lft_fyfactor, lft_mzfactor;
                  Float64 rgt_fxfactor, rgt_fyfactor, rgt_mzfactor;
                  m_DfStrategy->GetConcurrentDfs(poi_id, stage, df_type,
                                                 &lft_fxfactor,  &lft_fyfactor,  &lft_mzfactor,
                                                 &rgt_fxfactor, &rgt_fyfactor, &rgt_mzfactor);

                  lft_fx_result *= lft_fxfactor;
                  lft_fy_result *= lft_fyfactor;
                  lft_mz_result *= lft_mzfactor;
                  rgt_fx_result *= rgt_fxfactor;
                  rgt_fy_result *= rgt_fyfactor;
                  rgt_mz_result *= rgt_mzfactor;
               }
            }

            // assign and append result to collection
            CComPtr<ISectionResult3D> the_result;
            hr = the_result.CoCreateInstance(CLSID_SectionResult3D);

            hr = the_result->SetResult(lft_fx_result, lft_fy_result, lft_mz_result,
                                       rgt_fx_result, rgt_fy_result, rgt_mz_result);

            hr = the_results->Add(the_result);
         }
      }
      else
      {
         // results are not applicable - just add empty results and return
         for (CollectionIndexType ipoi = 0; ipoi<poi_cnt; ipoi++)
         {
            PoiIDType poi_id;
            hr = POIs->get_Item(ipoi, &poi_id);

            // our result
            CComPtr<ISectionResult3D> the_result;
            hr = the_result.CoCreateInstance(CLSID_SectionResult3D);

            // append result to collection
            hr = the_results->Add(the_result);
         }
      }
      // return our answer
      hr = the_results.CopyTo(results);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IBasicVehicularResponse);
   }

   return hr;
}


void CBasicVehicularResponse::AssertValid()
{
   ATLASSERT(m_InflStrategy!=nullptr);

   if (m_LiveLoad == nullptr)
   {
      // must be initialized before use
      THROW_LBAMLL(LL_INITIALIZATION);
   }
}



void CBasicVehicularResponse::GetStressPoints(PoiIDType poiID, BSTR stage, IStressPoints* *leftSps, IStressPoints* *rightSps)
{
   CHRException hr;

   CComPtr<IStressPoints> lft_sps, rgt_sps;
   hr = m_GetStressPoints->GetStressPointsAtPOI(poiID, stage, &lft_sps, &rgt_sps);

   ATLASSERT(lft_sps!=0); 
   lft_sps.CopyTo(leftSps);

   if (rgt_sps!=nullptr)
      rgt_sps.CopyTo(rightSps);
   else
      lft_sps.CopyTo(rightSps);
}
