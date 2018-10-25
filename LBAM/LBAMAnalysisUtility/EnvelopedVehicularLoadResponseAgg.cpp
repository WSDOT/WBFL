///////////////////////////////////////////////////////////////////////
// LBAM Analysis Utility - Longitindal Bridge Analysis Model
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

#include "stdafx.h"

#include "EnvelopedVehicularLoadResponseAgg.h"
#include "..\LBAMUtils.h"
#include "LBAMAnalysisUtility.hh"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// handle dealing with cancel from progress monitor
#define HANDLE_CANCEL_PROGRESS() if (m_pEnveloper->CheckForCancel()) throw S_FALSE;


// comparision functions
static bool MaxCmp(Float64 val1, Float64 val2)
{
   return val2>val1;
}

static bool MinCmp(Float64 val1, Float64 val2)
{
   return val2<val1;
}


///////////////////////////////////////////
// CEnvelopedVehicularLoadResponseAgg
///////////////////////////////////////////

STDMETHODIMP CEnvelopedVehicularLoadResponseAgg::InterfaceSupportsErrorInfo(REFIID riid)
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


// IEnvelopedVehicularResponse
STDMETHODIMP CEnvelopedVehicularLoadResponseAgg::ComputeForces(IIDArray* pois, BSTR stage, LiveLoadModelType type, 
                                                               VehicleIndexType vehicleIndex, ResultsOrientation orientation, 
                                                               ForceEffectType effect, OptimizationType optimization, 
                                                               VehicularLoadConfigurationType vehConfiguration, 
                                                               VARIANT_BOOL applyImpact, DistributionFactorType distributionType,
                                                               VARIANT_BOOL computePlacement, ILiveLoadModelSectionResults* *pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;


   OptimizationType env_optimization;
   m_pEnveloper->get_OptimizationType(&env_optimization);

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<ILiveLoadModelSectionResults> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng=0;  ieng<eng_cnt; ieng++)
      {
         HANDLE_CANCEL_PROGRESS();

         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<IEnvelopedVehicularResponse> response;
         hr = engine->get_EnvelopedVehicularResponse(&response);

         CComPtr<ILiveLoadModelSectionResults> results;
         hr = response->ComputeForces( pois, stage, type, vehicleIndex, orientation, effect, optimization,
                                       vehConfiguration, applyImpact, distributionType,
                                       computePlacement, &results);

         result_vec.push_back( results );
      }

      // intialize our vector of controlling engine id's to engine zero
      CollectionIndexType poi_cnt;
      hr = pois->get_Count(&poi_cnt);
      m_ControllingEngine.clear();
      m_ControllingEngine.resize(poi_cnt);

      // now that we have all results from all engines, envelope them
      // max results are place in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLiveLoadSectionResults(result_vec[0].m_T,result_vec[ieng].m_T,computePlacement,env_optimization,true,ieng);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_IEnvelopedVehicularResponse);
   }

   return S_OK;
}

STDMETHODIMP CEnvelopedVehicularLoadResponseAgg::ComputeDeflections(IIDArray* pois, BSTR stage, LiveLoadModelType type, 
                                                                    VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                                                                    VehicularLoadConfigurationType vehConfiguration, 
                                                                    VARIANT_BOOL applyImpact, DistributionFactorType distributionType,
                                                                    VARIANT_BOOL computePlacements, ILiveLoadModelSectionResults* *pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;


   OptimizationType env_optimization;
   m_pEnveloper->get_OptimizationType(&env_optimization);

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<ILiveLoadModelSectionResults> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng=0;  ieng<eng_cnt; ieng++)
      {
         HANDLE_CANCEL_PROGRESS();

         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<IEnvelopedVehicularResponse> response;
         hr = engine->get_EnvelopedVehicularResponse(&response);

         CComPtr<ILiveLoadModelSectionResults> results;
         hr = response->ComputeDeflections( pois, stage, type, vehicleIndex, effect, optimization,
                                            vehConfiguration, applyImpact, distributionType,
                                            computePlacements, &results);

         result_vec.push_back( results );
      }

      // intialize our vector of controlling engine id's to engine zero
      CollectionIndexType poi_cnt;
      hr = pois->get_Count(&poi_cnt);
      m_ControllingEngine.clear();
      m_ControllingEngine.resize(poi_cnt);

      // now that we have all results from all engines, envelope them
      // max results are place in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLiveLoadSectionResults(result_vec[0].m_T,result_vec[ieng].m_T,computePlacements,env_optimization,false,ieng);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_IEnvelopedVehicularResponse);
   }

   return S_OK;
}

STDMETHODIMP CEnvelopedVehicularLoadResponseAgg::ComputeReactions(IIDArray* supports, BSTR stage, LiveLoadModelType type, 
                                                                  VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                                                                  VehicularLoadConfigurationType vehConfiguration, 
                                                                  VARIANT_BOOL applyImpact, DistributionFactorType distributionType,
                                                                  VARIANT_BOOL computePlacements, ILiveLoadModelResults* *pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   OptimizationType env_optimization;
   m_pEnveloper->get_OptimizationType(&env_optimization);

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<ILiveLoadModelResults> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng=0;  ieng<eng_cnt; ieng++)
      {
         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<IEnvelopedVehicularResponse> response;
         hr = engine->get_EnvelopedVehicularResponse(&response);

         CComPtr<ILiveLoadModelResults> results;

         hr = response->ComputeReactions(supports, stage, type, 
        		                             vehicleIndex, effect, env_optimization, 
					    	                    vehConfiguration, 
                                         applyImpact, distributionType,
							                    computePlacements, &results);

         result_vec.push_back( results );
      }

      // now that we have all results from all engines, envelope them
      // max results are place in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLiveLoadResults(result_vec[0].m_T, result_vec[ieng].m_T,computePlacements, optimization);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILiveLoadModelResponse);
   }

   return S_OK;
}

STDMETHODIMP CEnvelopedVehicularLoadResponseAgg::ComputeSupportDeflections(IIDArray* supports, BSTR stage, LiveLoadModelType type, 
                                                                           VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                                                                           VehicularLoadConfigurationType vehConfiguration, 
                                                                           VARIANT_BOOL applyImpact, DistributionFactorType distributionType,
                                                                           VARIANT_BOOL computePlacements, ILiveLoadModelResults* *pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   OptimizationType env_optimization;
   m_pEnveloper->get_OptimizationType(&env_optimization);

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<ILiveLoadModelResults> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng=0;  ieng<eng_cnt; ieng++)
      {
         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<IEnvelopedVehicularResponse> response;
         hr = engine->get_EnvelopedVehicularResponse(&response);

         CComPtr<ILiveLoadModelResults> results;

		   hr = response->ComputeSupportDeflections(supports, stage, type, 
		                                  vehicleIndex, effect, env_optimization, 
					    	                   vehConfiguration, 
                                        applyImpact, distributionType,
							                   computePlacements, &results);

         result_vec.push_back( results );
      }

      // now that we have all results from all engines, envelope them
      // max results are place in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLiveLoadResults(result_vec[0].m_T, result_vec[ieng].m_T,computePlacements, optimization);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILiveLoadModelResponse);
   }

   return S_OK;
}

STDMETHODIMP CEnvelopedVehicularLoadResponseAgg::ComputeStresses(IIDArray* pois, BSTR stage, LiveLoadModelType type, 
                                                                 VehicleIndexType vehicleIndex, 
                                                                 ForceEffectType effect, OptimizationType optimization, 
                                                                 VehicularLoadConfigurationType vehConfiguration, 
                                                                 VARIANT_BOOL applyImpact, DistributionFactorType distributionType,
                                                                 VARIANT_BOOL computePlacements, ILiveLoadModelStressResults* *pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   try
   {
      // first compute forces to get optimal configurations
      CComPtr<ILiveLoadModelSectionResults> force_res;

      hr = ComputeForces(pois, stage, type, 
                         vehicleIndex, roMember, 
                         effect, optimization, 
                         vehConfiguration, 
                         applyImpact, distributionType,
                         VARIANT_TRUE, &force_res);

      // we can then use the configurations to compute our stress results
      CComPtr<ILiveLoadModelStressResults> results;
      hr = results.CoCreateInstance(CLSID_LiveLoadModelStressResults);

      CollectionIndexType num_pois;
      hr = force_res->get_Count(&num_pois);
      hr = results->Reserve(num_pois);

      CComPtr<IIDArray> single_poi;
      hr = single_poi.CoCreateInstance(CLSID_IDArray);

      hr = single_poi->ReDim(1);

      // loop over all pois and compute stresses due to optimization at that poi for the correct model
      for (CollectionIndexType ipoi=0; ipoi<num_pois; ipoi++)
      {
         // use configuration object from force results to compute stresses
         // get left and right config objects
         Float64 left_force, right_force;
         CComPtr<ILiveLoadConfiguration> left_config, right_config;
         hr = force_res->GetResult(ipoi, &left_force, &left_config, &right_force, &right_config);

         // determine which engine (model) was the optimal, and get the appropriate response interfaces
         CollectionIndexType left_engine_idx  = m_ControllingEngine[ipoi].Left;
         CollectionIndexType right_engine_idx = m_ControllingEngine[ipoi].Right;

         CComPtr<ILBAMAnalysisEngine> left_engine, right_engine;
         m_pEnveloper->GetEngine(left_engine_idx,  &left_engine);
         m_pEnveloper->GetEngine(right_engine_idx, &right_engine);

         CComPtr<IBasicVehicularResponse> left_response, right_response;
         hr = left_engine->get_BasicVehicularResponse(&left_response);
         hr = right_engine->get_BasicVehicularResponse(&right_response);

         // compute results one poi at a time
         PoiIDType poi_id;
         pois->get_Item(ipoi, &poi_id);
         single_poi->put_Item(0, poi_id);

         CComPtr<ISectionStressResults> left_stresses, right_stresses;
         hr = left_response->ComputeStresses(single_poi, stage, left_config, &left_stresses);

         hr = right_response->ComputeStresses(single_poi, stage, right_config, &right_stresses);

         CComPtr<ISectionStressResult> left_sec_stress, right_sec_stress;
         hr = left_stresses->get_Item(0, &left_sec_stress);

         hr = right_stresses->get_Item(0, &right_sec_stress);

         // extract out results from left and right sections
         CComPtr<IStressResult> left_stress, right_stress;
         hr = left_sec_stress->CreateLeftStressResult(&left_stress);

         hr = right_sec_stress->CreateRightStressResult(&right_stress);

         hr = results->Add(left_stress, left_config, right_stress, right_config);
      }

      return results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILiveLoadModelResponse);
   }

   return ERROR_CALL_NOT_IMPLEMENTED;
}

// Make sure maximum value is in res1
void CEnvelopedVehicularLoadResponseAgg::EnvelopeLiveLoadSectionResults(ILiveLoadModelSectionResults* res1, ILiveLoadModelSectionResults* res2,
                                           VARIANT_BOOL computeConfig, OptimizationType optimization, bool doFlip, CollectionIndexType engineIdx)
{
   // res1 contains the current controlling value

   CHRException hr;

   // use a function pointer to streamline min/max'ing
   bool (*lftcmp)(Float64, Float64);
   bool (*rgtcmp)(Float64, Float64);

   if ( doFlip )
   {
      if (optimization==optMaximize)
      {
         lftcmp = &MinCmp;
         rgtcmp = &MaxCmp;
      }
      else
      {
         lftcmp = &MaxCmp;
         rgtcmp = &MinCmp;
      }
   }
   else
   {
      if (optimization==optMaximize)
      {
         lftcmp = &MaxCmp;

         if (doFlip)
            rgtcmp = &MinCmp;
         else
            rgtcmp = &MaxCmp;
      }
      else
      {
         lftcmp = &MinCmp;

         if (doFlip)
            rgtcmp = &MaxCmp;
         else
            rgtcmp = &MinCmp;
      }
   }

   // loop over all pois and replace res1 with optmized results from res2 if needed.
   CollectionIndexType poi_cnt;
   hr = res1->get_Count(&poi_cnt);

   for (CollectionIndexType ipoi=0; ipoi<poi_cnt; ipoi++)
   {
      CComPtr<ILiveLoadConfiguration> lconf1, lconf2, rconf1, rconf2;
      Float64 lval1, lval2, rval1, rval2;

      hr = res1->GetResult(ipoi, &lval1, &lconf1, &rval1, &rconf1);
      hr = res2->GetResult(ipoi, &lval2, &lconf2, &rval2, &rconf2);

      bool ldo, rdo;
      ldo = lftcmp(lval1, lval2);
      rdo = rgtcmp(rval1, rval2);

      if (ldo)
      {
         m_ControllingEngine[ipoi].Left = engineIdx;

         if (rdo)
         {
            m_ControllingEngine[ipoi].Right = engineIdx;

            // replace res1's right and left
            hr = res1->SetResult(ipoi, lval2, lconf2, rval2, rconf2);
         }
         else
         {
            // left only
            hr = res1->SetResult(ipoi, lval2, lconf2, rval1, rconf1);
         }
      }
      else if (rdo)
      {
         // right only
         m_ControllingEngine[ipoi].Right = engineIdx;
         hr = res1->SetResult(ipoi, lval1, lconf1, rval2, rconf2);
      }
   }
}


void CEnvelopedVehicularLoadResponseAgg::EnvelopeLiveLoadResults(ILiveLoadModelResults* res1, ILiveLoadModelResults* res2,
                                    VARIANT_BOOL computeConfig, OptimizationType optimization)
{
   CHRException hr;

   // use a function pointer to streamline min/max'ing
   bool (*cmp)(Float64, Float64);

   if (optimization==optMaximize)
   {
      cmp = &MaxCmp;
   }
   else
   {
      cmp = &MinCmp;
   }

   // loop over all pois and replace res1 with optmized results from res2 if needed.
   CollectionIndexType poi_cnt;
   hr = res1->get_Count(&poi_cnt);

   for (CollectionIndexType ipoi=0; ipoi<poi_cnt; ipoi++)
   {
      CComPtr<ILiveLoadConfiguration> conf1, conf2;
      Float64 val1, val2;

      hr = res1->GetResult(ipoi, &val1, &conf1);
      hr = res2->GetResult(ipoi, &val2, &conf2);

      bool did;
      did = cmp(val1, val2);

      if (did)
      {
         hr = res1->SetResult(ipoi, val2, conf2);
      }
   }
}


