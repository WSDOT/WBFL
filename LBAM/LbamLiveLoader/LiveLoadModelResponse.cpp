///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2023  Washington State Department of Transportation
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

// LiveLoadModelResponse.cpp : Implementation of CLiveLoadModelResponse
#include "stdafx.h"
#include "WBFLLBAMLiveLoader.h"
#include "LiveLoadModelResponse.h"
#include "LBAMLiveLoader.hh"

#include "BruteForceVehicularResponse.h"
#include "LiveLoadConfiguration.h"
#include "LiveLoadModelSectionResults.h"
#include "LiveLoadModelResults.h"
#include "LiveLoaderUtils.h"

#include "BasicVehicularResponse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// handle dealing with cancel from progress monitor
#define HANDLE_CANCEL_PROGRESS() if (this->CheckForCancel()) throw S_FALSE;

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadModelResponse

STDMETHODIMP CLiveLoadModelResponse::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILiveLoadModelResponse
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// comparison functions

bool CompareMax(Float64 newv, Float64 oldv)
{
   return ::IsGT(oldv,newv); //newv>oldv;
}

bool CompareMin(Float64 newv, Float64 oldv)
{
   return ::IsLT(newv,oldv); //newv<oldv;
}


// section values
static void ComputeMax(LiveLoadModelType type, VehicleIndexType vehIdx, IndexType numPois, 
                bool (*leftCompare)(Float64, Float64), bool (*rightCompare)(Float64, Float64), 
                VARIANT_BOOL doComputePlacement, 
                ILiveLoadModelSectionResults* envResults, ILiveLoadModelSectionResults* results)
{
   CHRException hr;
   if (vehIdx==0)
   {
      // first vehicle. no comparison needed. first is optimal, by definition
      for (IndexType poiIdx = 0; poiIdx < numPois; poiIdx++)
      {
         Float64 left_result, right_result;
         CComPtr<ILiveLoadConfiguration> left_config, right_config;
         hr = envResults->GetResult(poiIdx, &left_result, &left_config, &right_result, &right_config);
         hr = results->Add(left_result, left_config, right_result, right_config);
      }
   }
   else
   {
      // need to perform comparison with previously computed results
      for (IndexType poiIdx = 0; poiIdx < numPois; poiIdx++)
      {
         // pull out new result to compare with
         Float64 new_left_result, new_right_result;
         CComPtr<ILiveLoadConfiguration> new_left_config, new_right_config;
         hr = envResults->GetResult(poiIdx, &new_left_result, &new_left_config, &new_right_result, &new_right_config);

         // old result 
         Float64 old_left_result, old_right_result;
         CComPtr<ILiveLoadConfiguration> old_left_config, old_right_config;
         hr = results->GetResult(poiIdx, &old_left_result, &old_left_config, &old_right_result, &old_right_config);

         bool new_max_occurred=false;
         Float64 left_result, right_result;
         CComPtr<ILiveLoadConfiguration> left_config, right_config;

         // left side
         if (leftCompare(new_left_result, old_left_result))
         {
            new_max_occurred = true;
            left_result = new_left_result;
            left_config = new_left_config;
         }
         else
         {
            left_result = old_left_result;
            left_config = old_left_config;
         }

         // right side
         if (rightCompare(new_right_result, old_right_result))
         {
            new_max_occurred = true;
            right_result = new_right_result;
            right_config = new_right_config;
         }
         else
         {
            right_result = old_right_result;
            right_config = old_right_config;
         }

         // only need to update if a new maximum occurred
         if (new_max_occurred)
         {
            hr = results->SetResult(poiIdx,left_result, left_config, right_result, right_config);
         }
      }
   }
}

// single values
static void ComputeMax(LiveLoadModelType type, VehicleIndexType vehIdx, IndexType numPois, 
                       bool (*Compare)(Float64, Float64), VARIANT_BOOL doComputePlacement, 
                       ILiveLoadModelResults* envResults, ILiveLoadModelResults* results)
{
   CHRException hr;
   if (vehIdx == 0)
   {
      // first vehicle. no comparison needed. first is optimal, by definition
      for (IndexType poiIdx = 0; poiIdx < numPois; poiIdx++)
      {
         Float64 result;
         CComPtr<ILiveLoadConfiguration> config;
         hr = envResults->GetResult(poiIdx, &result, &config);
         hr = results->Add(result, config);
      }
   }
   else
   {
      // need to perform comparison with previously computed results
      for (IndexType poiIdx = 0; poiIdx < numPois; poiIdx++)
      {
         // pull out new result to compare with
         Float64 new_result;
         CComPtr<ILiveLoadConfiguration> new_config;
         hr = envResults->GetResult(poiIdx, &new_result, &new_config);

         // old result 
         Float64 old_result;
         CComPtr<ILiveLoadConfiguration> old_config;
         hr = results->GetResult(poiIdx, &old_result, &old_config);

         // perform comparison and replace result if we have a new max
         if (Compare(new_result, old_result))
         {
            hr = results->SetResult(poiIdx, new_result, new_config);
         }
      }
   }
}

// ISupportProgressMonitor
STDMETHODIMP CLiveLoadModelResponse::InitializeProgressMonitor(IProgressMonitor * newVal, LONG cookie)
{
   CHECK_IN(newVal);

   m_pProgressMonitor = newVal;
   m_ProgressCookie = cookie;

   return S_OK;
}

STDMETHODIMP CLiveLoadModelResponse::ComputeForces(IIDArray* poiIDs, BSTR stage, LiveLoadModelType type, ResultsOrientation orientation, 
                                                   ForceEffectType effect, OptimizationType optimization, 
                                                   VehicularLoadConfigurationType vehConfiguration, 
                                                   VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, 
                                                   VARIANT_BOOL computePlacement, 
                                                   ILiveLoadModelSectionResults** pResults)
{
   CHECK_IN(poiIDs);
   CHECK_IN(stage);
	CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      CComPtr<ILiveLoadModel> pLiveLoadModel;
      GetLiveLoadModel(type, m_LiveLoad, &pLiveLoadModel);

      DistributionFactorType df_type = dftNone;

      if (applyDistribution == VARIANT_TRUE)
      {
         hr = pLiveLoadModel->get_DistributionFactorType(&df_type);
      }

      CComPtr<IVehicularLoads> pVehicularLoads;
      hr = pLiveLoadModel->get_VehicularLoads(&pVehicularLoads);

      VehicleIndexType nVehicles;
      hr = pVehicularLoads->get_Count(&nVehicles);

      IndexType nPOI;
      hr = poiIDs->get_Count(&nPOI);

      // create our results object
      CComObject<CLiveLoadModelSectionResults>* cresults;
      CComObject<CLiveLoadModelSectionResults>::CreateInstance(&cresults);
      CComPtr<ILiveLoadModelSectionResults> results(cresults);
      hr = results->Reserve(nPOI);

      if (nVehicles == 0)
      {
         // no vehicles - need to create empty results and return
         for (IndexType poiIdx = 0; poiIdx < nPOI; poiIdx++)
         {
            CComPtr<ILiveLoadConfiguration> left_config, right_config;
            if ( computePlacement == VARIANT_TRUE )
            {
               left_config.CoCreateInstance(CLSID_LiveLoadConfiguration);
               right_config.CoCreateInstance(CLSID_LiveLoadConfiguration);
            }
            hr = results->Add(0.0, left_config, 0.0, right_config);
         }
      }
      else
      {
         // set up our comparison function
         bool (*fleft_compare)(Float64, Float64);
         bool (*fright_compare)(Float64, Float64);
         if (optimization==optMaximize)
         {
            fleft_compare  = &CompareMax;
            fright_compare = &CompareMin;
         }
         else
         {
            fleft_compare  = &CompareMin;
            fright_compare = &CompareMax;
         }

         // loop over all vehicular loads and find the maximum

         for (VehicleIndexType vehicleIdx = 0; vehicleIdx < nVehicles; vehicleIdx++)
         {
            HANDLE_CANCEL_PROGRESS();

            CComPtr<ILiveLoadModelSectionResults> env_results;
            hr = m_EnvelopedResponse->ComputeForces(poiIDs, stage, type, vehicleIdx, orientation, 
                                                    effect, optimization, vehConfiguration, applyImpact, df_type,
                                                    computePlacement, &env_results);

            ComputeMax(type, vehicleIdx, nPOI, fleft_compare, fright_compare, computePlacement, env_results, results);
         }
      }

      hr = results.CopyTo(pResults);

   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILiveLoadModelResponse);
   }

   return hr;
}

STDMETHODIMP CLiveLoadModelResponse::ComputeDeflections(IIDArray* poiIDs, BSTR stage, LiveLoadModelType type,
                                                        ForceEffectType effect, OptimizationType optimization, 
                                                        VehicularLoadConfigurationType vehConfiguration, 
                                                        VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, 
                                                        VARIANT_BOOL computePlacement, 
                                                        ILiveLoadModelSectionResults** pResults)
{
   CHECK_IN(poiIDs);
   CHECK_IN(stage);
	CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      CComPtr<ILiveLoadModel> pllm;
      GetLiveLoadModel(type, m_LiveLoad, &pllm);

      DistributionFactorType df_type = dftNone;

      if (applyDistribution == VARIANT_TRUE)
      {
         hr = pllm->get_DistributionFactorType(&df_type);
      }

      CComPtr<IVehicularLoads> vehicularLoads;
      hr = pllm->get_VehicularLoads(&vehicularLoads);

      VehicleIndexType nVehicles;
      hr = vehicularLoads->get_Count(&nVehicles);

      IndexType nPOI;
      hr = poiIDs->get_Count(&nPOI);

      // create our results object
      CComObject<CLiveLoadModelSectionResults>* cresults;
      CComObject<CLiveLoadModelSectionResults>::CreateInstance(&cresults);
      CComPtr<ILiveLoadModelSectionResults> results(cresults);
      hr = results->Reserve(nPOI);

      if (nVehicles == 0)
      {
         // no vehicles - need to create empty results and return
         for (IndexType poiIdx = 0; poiIdx < nPOI; poiIdx++)
         {
            hr = results->Add(0.0, nullptr, 0.0, nullptr);
         }
      }
      else
      {
         // set up our comparison function
         bool (*fleft_compare)(Float64, Float64);
         bool (*fright_compare)(Float64, Float64);
         if (optimization==optMaximize)
         {
            fleft_compare  = &CompareMax;
            fright_compare = &CompareMax;
         }
         else
         {
            fleft_compare  = &CompareMin;
            fright_compare = &CompareMin;
         }

         // loop over all vehicular loads and find the maximum
         for (VehicleIndexType vehicleIdx = 0; vehicleIdx < nVehicles; vehicleIdx++)
         {
            HANDLE_CANCEL_PROGRESS();

            CComPtr<ILiveLoadModelSectionResults> env_results;
            hr = m_EnvelopedResponse->ComputeDeflections(poiIDs, stage, type, vehicleIdx, effect, 
                                                         optimization, vehConfiguration, applyImpact, df_type,
                                                         computePlacement, &env_results);

            ComputeMax(type, vehicleIdx, nPOI, fleft_compare, fright_compare, computePlacement, env_results, results);
         }
      }

      hr = results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILiveLoadModelResponse);
   }

   return hr;
}


STDMETHODIMP CLiveLoadModelResponse::ComputeReactions(IIDArray* supportIDs, BSTR stage, LiveLoadModelType type,
                                                      ForceEffectType effect, OptimizationType optimization, 
                                                      VehicularLoadConfigurationType vehConfiguration, 
                                                      VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, 
                                                      VARIANT_BOOL computePlacement, 
                                                      ILiveLoadModelResults** pResults)
{
   CHECK_IN(supportIDs);
   CHECK_IN(stage);
	CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      CComPtr<ILiveLoadModel> pllm;
      GetLiveLoadModel(type, m_LiveLoad, &pllm);

      DistributionFactorType df_type = dftNone;

      if (applyDistribution == VARIANT_TRUE)
      {
         hr = pllm->get_DistributionFactorType(&df_type);
      }

      CComPtr<IVehicularLoads> pvls;
      hr = pllm->get_VehicularLoads(&pvls);

      VehicleIndexType nVehicles;
      hr = pvls->get_Count(&nVehicles);

      IndexType nSupports;
      hr = supportIDs->get_Count(&nSupports);

      // create our results object
      CComObject<CLiveLoadModelResults>* cresults;
      CComObject<CLiveLoadModelResults>::CreateInstance(&cresults);
      CComPtr<ILiveLoadModelResults> results(cresults);
      hr = results->Reserve(nSupports);

      if (nVehicles == 0)
      {
         // no vehicles - need to create empty results and return
         for (IndexType supportIdx = 0; supportIdx < nSupports; supportIdx++)
         {
            hr = results->Add(0.0, nullptr);
         }
      }
      else
      {
         // set up our comparison function
         bool (*fcompare)(Float64, Float64);
         if (optimization==optMaximize)
         {
            fcompare  = &CompareMax;
         }
         else
         {
            fcompare  = &CompareMin;
         }

         // loop over all vehicular loads and find the maximum
         for (VehicleIndexType vehicleIdx = 0; vehicleIdx < nVehicles; vehicleIdx++)
         {
            HANDLE_CANCEL_PROGRESS();

            CComPtr<ILiveLoadModelResults> env_results;
            hr = m_EnvelopedResponse->ComputeReactions(supportIDs, stage, type, vehicleIdx, effect, 
                                                       optimization, vehConfiguration, applyImpact, df_type,
                                                       computePlacement, &env_results);

            ComputeMax(type, vehicleIdx, nSupports, fcompare, computePlacement, env_results, results);
         }
      }

      hr = results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILiveLoadModelResponse);
   }

   return hr;
}

STDMETHODIMP CLiveLoadModelResponse::ComputeSupportDeflections(IIDArray* supportIDs, BSTR stage, LiveLoadModelType type,
                                                      ForceEffectType effect, OptimizationType optimization, 
                                                      VehicularLoadConfigurationType vehConfiguration, 
                                                      VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, 
                                                      VARIANT_BOOL computePlacement, 
                                                      ILiveLoadModelResults** pResults)
{
   CHECK_IN(supportIDs);
   CHECK_IN(stage);
	CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      CComPtr<ILiveLoadModel> pllm;
      GetLiveLoadModel(type, m_LiveLoad, &pllm);

      DistributionFactorType df_type = dftNone;

      if (applyDistribution == VARIANT_TRUE)
      {
         hr = pllm->get_DistributionFactorType(&df_type);
      }

      CComPtr<IVehicularLoads> pvls;
      hr = pllm->get_VehicularLoads(&pvls);

      VehicleIndexType nVehicles;
      hr = pvls->get_Count(&nVehicles);

      IndexType nSupports;
      hr = supportIDs->get_Count(&nSupports);

      // create our results object
      CComObject<CLiveLoadModelResults>* cresults;
      CComObject<CLiveLoadModelResults>::CreateInstance(&cresults);
      CComPtr<ILiveLoadModelResults> results(cresults);
      hr = results->Reserve(nSupports);

      if (nVehicles == 0)
      {
         // no vehicles - need to create empty results and return
         for (IndexType supportIdx = 0; supportIdx < nSupports; supportIdx++)
         {
            hr = results->Add(0.0, nullptr);
         }
      }
      else
      {
         // set up our comparison function
         bool (*fcompare)(Float64, Float64);
         if (optimization==optMaximize)
         {
            fcompare  = &CompareMax;
         }
         else
         {
            fcompare  = &CompareMin;
         }

         // loop over all vehicular loads and find the maximum
         for (VehicleIndexType vehicleIdx = 0; vehicleIdx < nVehicles; vehicleIdx++)
         {
            HANDLE_CANCEL_PROGRESS();

            CComPtr<ILiveLoadModelResults> env_results;
            hr = m_EnvelopedResponse->ComputeSupportDeflections(supportIDs, stage, type, vehicleIdx, effect, 
                                                       optimization, vehConfiguration, applyImpact, df_type,
                                                       computePlacement, &env_results);

            ComputeMax(type, vehicleIdx, nSupports, fcompare, computePlacement, env_results, results);
         }
      }

      hr = results.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILiveLoadModelResponse);
   }

   return hr;
}


STDMETHODIMP CLiveLoadModelResponse::ComputeStresses(IIDArray* poiIDs, BSTR stage, LiveLoadModelType type,
                                                   ForceEffectType effect, OptimizationType optimization, 
                                                   VehicularLoadConfigurationType vehConfiguration, 
                                                   VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, 
                                                   VARIANT_BOOL computePlacement, 
                                                   ILiveLoadModelStressResults** pResults)
{
   CHECK_IN(poiIDs);
   CHECK_IN(stage);
	CHECK_RETOBJ(pResults);

   CHRException hr;
   try
   {
      HANDLE_CANCEL_PROGRESS();

      // use optimized force configuration to compute stresses
      CComPtr<ILiveLoadModelSectionResults> force_results;
      hr = this->ComputeForces(poiIDs, stage, type, roMember, effect, optimization, vehConfiguration, applyImpact, 
                               applyDistribution, VARIANT_TRUE, &force_results);

      // use basic stress calculation to compute stresses for optimized truck location (configuration)
      CComObject<CBasicVehicularResponse>* basic_response;
      hr = CComObject<CBasicVehicularResponse>::CreateInstance(&basic_response);

      CComPtr<IBasicVehicularResponse> pbasic_response(basic_response); // exception safety

      // secret (non-com) back door to inialize in a hurry
      basic_response->QuickInitialize(m_LiveLoad, m_InfluenceLineResponse, m_LiveLoadNegativeMomentRegion, 
                                      m_GetDistributionFactors, m_SupportLocations, 
                                      m_GetStressPoints);

      hr = LLSectionToStressResults(poiIDs, stage, force_results, basic_response,  pResults);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILiveLoadModelResponse);
   }

   return hr;
}


// IDependOnVehicularAnalysisContext
STDMETHODIMP CLiveLoadModelResponse::Initialize(/*[in]*/IUnknown* context)
{
   try
   {
      // first set up our context - we need to know ILiveLoad to get our work done
      if (m_Context != nullptr)
      {
         // can only initialize once
         THROW_LBAMLL(LL_INITIALIZATION);
      }

      m_Context = context;

      // Latch onto the parts of the context we need 
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

      CComQIPtr<ILiveLoadNegativeMomentRegion> pcf(context);
      if (pcf!=nullptr)
      {
         m_LiveLoadNegativeMomentRegion = pcf;
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

      CComQIPtr<ISupportLocations> sup_locs(m_Context);
      if (sup_locs!=nullptr)
      {
         m_SupportLocations = sup_locs;
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

      CHRException hr;

      // Next create our live load enveloper. Use the brute force strategy by default
      if ( m_EnvelopedResponse == nullptr )
      {
         if ( m_Factory == nullptr )
         {
            CComObject<CBruteForceVehicularResponse>* p_vehicular_response;
            hr = CComObject<CBruteForceVehicularResponse>::CreateInstance(&p_vehicular_response);
            m_EnvelopedResponse = p_vehicular_response;
         }
         else
         {
            m_Factory->CreateEnvelopedVehicularResponse(&m_EnvelopedResponse);
         }

         CComQIPtr<IDependOnVehicularAnalysisContext> dep_ctx(m_EnvelopedResponse);
         if (dep_ctx!=nullptr)
         {
            dep_ctx->Initialize(m_Context);
         }
         else
         {
            ATLASSERT(false);
            hr = E_FAIL;
         }
      }

   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILiveLoadModelResponse);
   }

   return S_OK;
}

STDMETHODIMP CLiveLoadModelResponse::get_Strategy(IEnvelopedVehicularResponse * * pVal)
{
   CHECK_RETOBJ(pVal);
   if (m_EnvelopedResponse!=nullptr)
   {
      return m_EnvelopedResponse.CopyTo(pVal);
   }
   else
   {
      ATLASSERT(false);
      return E_FAIL;
   }
}

STDMETHODIMP CLiveLoadModelResponse::putref_Strategy(IEnvelopedVehicularResponse * pVal)
{
   CHECK_IN(pVal);

   m_EnvelopedResponse = pVal;

   return S_OK;
}

STDMETHODIMP CLiveLoadModelResponse::putref_EnvelopedVehicularRepsonseFactory(IEnvelopedVehicularResponseFactory* pFactory)
{
   m_Factory = pFactory;
   return S_OK;
}

STDMETHODIMP CLiveLoadModelResponse::get_EnvelopedVehicularRepsonseFactory(IEnvelopedVehicularResponseFactory** pFactory)
{
   CHECK_RETOBJ(pFactory);
   (*pFactory) = m_Factory;
   if ( *pFactory )
      (*pFactory)->AddRef();

   return S_OK;
}

STDMETHODIMP CLiveLoadModelResponse::putref_EnvelopedVehicularRepsonse(IEnvelopedVehicularResponse* pResponse)
{
   m_EnvelopedResponse = pResponse;
   return S_OK;
}
