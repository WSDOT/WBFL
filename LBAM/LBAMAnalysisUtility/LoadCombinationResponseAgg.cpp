///////////////////////////////////////////////////////////////////////
// LBAM Analysis Utility - Longitindal Bridge Analysis Model
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

// SegmentItem.cpp : Implementation of CSegmentItem
#include "stdafx.h"

#include "LoadCombinationResponseAgg.h"
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
// CLoadCombinationResponseAgg
///////////////////////////////////////////

STDMETHODIMP CLoadCombinationResponseAgg::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ILoadCombinationResponse
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// ILoadCombinationResponse
STDMETHODIMP CLoadCombinationResponseAgg::ComputeForces(BSTR loadCombination, IIDArray* POIs, BSTR Stage, ResultsOrientation orientation, 
                                                       ResultsSummationType summ, ForceEffectType effect, OptimizationType optimization, 
                                                       VARIANT_BOOL includeLiveLoad, VARIANT_BOOL includeImpact, VARIANT_BOOL computeConfig,
                                                       ILoadCombinationSectionResults** pResults)
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

      std::vector< CAdapt< CComPtr<ILoadCombinationSectionResults> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng = 0;  ieng<eng_cnt; ieng++)
      {
         HANDLE_CANCEL_PROGRESS();

         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<ILoadCombinationResponse> response;
         hr = engine->get_LoadCombinationResponse(&response);

         CComPtr<ILoadCombinationSectionResults> results;

         hr = response->ComputeForces(loadCombination, POIs, Stage, orientation, 
                                      summ, effect, optimization, 
                                      includeLiveLoad, includeImpact, computeConfig,
                                      &results);

         result_vec.push_back( results );

      }

      // intialize our vector of controlling engine id's to engine zero
      CollectionIndexType poi_cnt;
      hr = POIs->get_Count(&poi_cnt);
      m_ControllingEngine.clear();
      m_ControllingEngine.resize(poi_cnt);

      // now that we have all results from all engines, envelope them
      // max results are place in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLoadCombinationSectionResults(result_vec[0].m_T,result_vec[ieng].m_T,computeConfig,env_optimization,true,ieng);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILoadCombinationResponse);
   }

   return S_OK;
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeDeflections(BSTR loadCombination, IIDArray* POIs, BSTR Stage,
                                                             ResultsSummationType summ, ForceEffectType effect, OptimizationType optimization, 
                                                             VARIANT_BOOL includeLiveLoad, VARIANT_BOOL includeImpact,  VARIANT_BOOL computeConfig,
                                                             ILoadCombinationSectionResults** pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<ILoadCombinationSectionResults> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng = 0;  ieng<eng_cnt; ieng++)
      {
         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<ILoadCombinationResponse> response;
         hr = engine->get_LoadCombinationResponse(&response);

         CComPtr<ILoadCombinationSectionResults> results;

         hr = response->ComputeDeflections(loadCombination, POIs, Stage, 
                                           summ, effect, optimization, 
                                           includeLiveLoad, includeImpact, computeConfig,
                                           &results);

         result_vec.push_back( results );

      }

      // now that we have all results from all engines, envelope them
      // max results are place in the first member of the vector

      // intialize our vector of controlling engine id's to engine zero
      CollectionIndexType poi_cnt;
      hr = POIs->get_Count(&poi_cnt);
      m_ControllingEngine.clear();
      m_ControllingEngine.resize(poi_cnt);


      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLoadCombinationSectionResults(result_vec[0].m_T,result_vec[ieng].m_T,computeConfig,optimization,false,ieng);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILoadCombinationResponse);
   }

   return S_OK;
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeReactions(BSTR loadCombination, IIDArray* POIs, BSTR Stage,
                                                           ResultsSummationType summ, ForceEffectType effect, 
                                                           OptimizationType optimization, 
                                                           VARIANT_BOOL includeLiveLoad, VARIANT_BOOL includeImpact,  VARIANT_BOOL computeConfig,
                                                           ILoadCombinationResults** pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<ILoadCombinationResults> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng = 0;  ieng<eng_cnt; ieng++)
      {
         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<ILoadCombinationResponse> response;
         hr = engine->get_LoadCombinationResponse(&response);

         CComPtr<ILoadCombinationResults> results;

         hr = response->ComputeReactions(loadCombination, POIs, Stage, 
                                           summ, effect, optimization, 
                                           includeLiveLoad, includeImpact, computeConfig,
                                           &results);

         result_vec.push_back( results );
      }

      CollectionIndexType poi_cnt;
      hr = POIs->get_Count(&poi_cnt);
      m_ControllingEngineReactions.resize(poi_cnt,0);

      // now that we have all results from all engines, envelope them
      // max results are place in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLoadCombinationResults(result_vec[0].m_T, result_vec[ieng].m_T,computeConfig, optimization,ieng);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILoadCombinationResponse);
   }

   return S_OK;
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeSupportDeflections(BSTR loadCombination, IIDArray* POIs, BSTR Stage,
                                                           ResultsSummationType summ, ForceEffectType effect, 
                                                           OptimizationType optimization, 
                                                           VARIANT_BOOL includeLiveLoad, VARIANT_BOOL includeImpact,  VARIANT_BOOL computeConfig,
                                                           ILoadCombinationResults** pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<ILoadCombinationResults> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng = 0;  ieng<eng_cnt; ieng++)
      {
         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<ILoadCombinationResponse> response;
         hr = engine->get_LoadCombinationResponse(&response);

         CComPtr<ILoadCombinationResults> results;

         hr = response->ComputeSupportDeflections(loadCombination, POIs, Stage, 
                                                  summ, effect, optimization, 
                                                  includeLiveLoad, includeImpact, computeConfig,
                                                  &results);

         result_vec.push_back( results );
      }

      CollectionIndexType poi_cnt;
      hr = POIs->get_Count(&poi_cnt);
      m_ControllingEngineReactions.resize(poi_cnt,0);

      // now that we have all results from all engines, envelope them
      // max results are place in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLoadCombinationResults(result_vec[0].m_T, result_vec[ieng].m_T,computeConfig, optimization,ieng);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILoadCombinationResponse);
   }

   return S_OK;
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeStresses(BSTR loadCombination, IIDArray* POIs, BSTR Stage,
                                                          ResultsSummationType summ, ForceEffectType effect, OptimizationType optimization, 
                                                          VARIANT_BOOL includeLiveLoad,VARIANT_BOOL includeImpact,   VARIANT_BOOL computeConfig,
                                                          ILoadCombinationStressResults** pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   try
   {
      // first compute forces to get optimal configurations
      CComPtr<ILoadCombinationSectionResults> force_res;

      hr = ComputeForces(loadCombination, POIs, Stage, roMember, 
                         summ, effect,  optimization, 
                         includeLiveLoad, includeImpact, VARIANT_TRUE,
                         &force_res);

      // we can then use the configurations to compute our stress results
      CComPtr<ILoadCombinationStressResults> results;
      hr = results.CoCreateInstance(CLSID_LoadCombinationStressResults);

      CollectionIndexType num_pois;
      hr = force_res->get_Count(&num_pois);
      hr = results->Reserve(num_pois);

      CComPtr<IIDArray> single_poi;
      hr = single_poi.CoCreateInstance(CLSID_IDArray);

      hr = single_poi->ReDim(1);

      // loop over all pois and compute stresses due to optimization at that poi for the correct model
      for (CollectionIndexType ipoi = 0; ipoi<num_pois; ipoi++)
      {
         // use configuration object from force results to compute stresses
         // get left and right config objects
         Float64 left_force, right_force;
         CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
         hr = force_res->GetResult(ipoi, &left_force, &left_config, &right_force, &right_config);

         // determine which engine (model) was the optimal, and get the appropriate response interfaces
         CollectionIndexType left_engine_idx  = m_ControllingEngine[ipoi].Left;
         CollectionIndexType right_engine_idx = m_ControllingEngine[ipoi].Right;

         CComPtr<ILBAMAnalysisEngine> left_engine, right_engine;
         m_pEnveloper->GetEngine(left_engine_idx,  &left_engine);
         m_pEnveloper->GetEngine(right_engine_idx, &right_engine);

         CComPtr<IConcurrentLoadCombinationResponse> left_response, right_response;
         hr = left_engine->get_ConcurrentLoadCombinationResponse(&left_response);
         hr = right_engine->get_ConcurrentLoadCombinationResponse(&right_response);

         // compute results one poi at a time
         PoiIDType poi_id;
         POIs->get_Item(ipoi, &poi_id);
         single_poi->put_Item(0, poi_id);

         CComPtr<ISectionStressResults> left_stresses, right_stresses;
         hr = left_response->ComputeStresses(single_poi, Stage, left_config, &left_stresses);

         hr = right_response->ComputeStresses(single_poi, Stage, right_config, &right_stresses);

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
      return DealWithExceptions(m_pEnveloper, IID_ILoadCombinationResponse);
   }

   return ERROR_CALL_NOT_IMPLEMENTED;
}

///////////////////////////////////////////////////////////////////////
// IConcurrentLoadCombinationResponse
STDMETHODIMP CLoadCombinationResponseAgg::ComputeForces(IIDArray* pois, 
                                                        BSTR stage, 
                                                        ResultsOrientation orientation, 
                                                        ILoadCombinationResultConfiguration* config, 
                                                        ISectionResult3Ds* *pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   // create a bucket to dump the results in
   CComPtr<ISectionResult3Ds> results;
   hr = results.CoCreateInstance(CLSID_SectionResult3Ds);

   try
   {

      // we are going to need an array for POI-by-POI computations below
      CComPtr<IIDArray> single_poi;
      hr = single_poi.CoCreateInstance(CLSID_IDArray);

      hr = single_poi->ReDim(1);

      CollectionIndexType nPois;
      pois->get_Count(&nPois);
      for ( CollectionIndexType poiIdx = 0; poiIdx < nPois; poiIdx++ )
      {
         // determine which engine (model) was the optimal, and get the appropriate response interfaces
         CollectionIndexType left_engine_idx  = m_ControllingEngine[poiIdx].Left;
         CollectionIndexType right_engine_idx = m_ControllingEngine[poiIdx].Right;

         CComPtr<ILBAMAnalysisEngine> left_engine, right_engine;
         m_pEnveloper->GetEngine(left_engine_idx,  &left_engine);
         m_pEnveloper->GetEngine(right_engine_idx, &right_engine);

         CComPtr<IConcurrentLoadCombinationResponse> left_response, right_response;
         hr = left_engine->get_ConcurrentLoadCombinationResponse(&left_response);
         hr = right_engine->get_ConcurrentLoadCombinationResponse(&right_response);

         // compute results one poi at a time
         PoiIDType poi_id;
         pois->get_Item(poiIdx, &poi_id);
         single_poi->put_Item(0, poi_id);

         CComPtr<ISectionResult3Ds> left_results, right_results;
         left_response->ComputeForces(single_poi,stage,orientation,config,&left_results);
         right_response->ComputeForces(single_poi,stage,orientation,config,&right_results);

#if defined _DEBUG
         // we sent one poi in, expecting to get one result out
         CollectionIndexType c;
         left_results->get_Count(&c);
         ATLASSERT(c == 1);

         right_results->get_Count(&c);
         ATLASSERT(c == 1);
#endif

         CComPtr<ISectionResult3D> left_result, right_result;
         left_results->get_Item(0,&left_result);
         right_results->get_Item(0,&right_result);

         CComPtr<ISectionResult3D> result;
         hr = result.CoCreateInstance(CLSID_SectionResult3D);

         Float64 x,y,z;
         Float64 Lx,Ly,Lz;
         left_result->GetResult(&x,&y,&z,&Lx,&Ly,&Lz);

         Float64 Rx,Ry,Rz;
         right_result->GetResult(&Rx,&Ry,&Rz,&x,&y,&z);

         result->SetResult(Lx,Ly,Lz,Rx,Ry,Rz);

         results->Add(result);
      }
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_IConcurrentLoadCombinationResponse);
   }

   hr = results.CopyTo(pResults);

   return S_OK;
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeDeflections(IIDArray* pois, BSTR stage, ILoadCombinationResultConfiguration* config, ISectionResult3Ds* *pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   // create a bucket to dump the results in
   CComPtr<ISectionResult3Ds> results;
   hr = results.CoCreateInstance(CLSID_SectionResult3Ds);

   try
   {

      // we are going to need an array for POI-by-POI computations below
      CComPtr<IIDArray> single_poi;
      hr = single_poi.CoCreateInstance(CLSID_IDArray);

      hr = single_poi->ReDim(1);

      CollectionIndexType nPois;
      pois->get_Count(&nPois);
      for ( CollectionIndexType poiIdx = 0; poiIdx < nPois; poiIdx++ )
      {
         // determine which engine (model) was the optimal, and get the appropriate response interfaces
         CollectionIndexType left_engine_idx  = m_ControllingEngine[poiIdx].Left;
         CollectionIndexType right_engine_idx = m_ControllingEngine[poiIdx].Right;

         CComPtr<ILBAMAnalysisEngine> left_engine, right_engine;
         m_pEnveloper->GetEngine(left_engine_idx,  &left_engine);
         m_pEnveloper->GetEngine(right_engine_idx, &right_engine);

         CComPtr<IConcurrentLoadCombinationResponse> left_response, right_response;
         hr = left_engine->get_ConcurrentLoadCombinationResponse(&left_response);
         hr = right_engine->get_ConcurrentLoadCombinationResponse(&right_response);

         // compute results one poi at a time
         PoiIDType poi_id;
         pois->get_Item(poiIdx, &poi_id);
         single_poi->put_Item(0, poi_id);

         CComPtr<ISectionResult3Ds> left_results, right_results;
         left_response->ComputeDeflections(single_poi,stage,config,&left_results);
         right_response->ComputeDeflections(single_poi,stage,config,&right_results);

#if defined _DEBUG
         // we sent one poi in, expecting to get one result out
         CollectionIndexType c;
         left_results->get_Count(&c);
         ATLASSERT(c == 1);

         right_results->get_Count(&c);
         ATLASSERT(c == 1);
#endif

         CComPtr<ISectionResult3D> left_result, right_result;
         left_results->get_Item(0,&left_result);
         right_results->get_Item(0,&right_result);

         CComPtr<ISectionResult3D> result;
         hr = result.CoCreateInstance(CLSID_SectionResult3D);

         Float64 x,y,z;
         Float64 Lx,Ly,Lz;
         left_result->GetResult(&x,&y,&z,&Lx,&Ly,&Lz);

         Float64 Rx,Ry,Rz;
         right_result->GetResult(&Rx,&Ry,&Rz,&x,&y,&z);

         result->SetResult(Lx,Ly,Lz,Rx,Ry,Rz);

         results->Add(result);
      }
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_IConcurrentLoadCombinationResponse);
   }

   hr = results.CopyTo(pResults);

   return S_OK;
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeReactions(IIDArray* pois, 
                                                           BSTR stage, 
                                                           ILoadCombinationResultConfiguration* config, 
                                                           IResult3Ds* *pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   // create a bucket to dump the results in
   CComPtr<IResult3Ds> results;
   hr = results.CoCreateInstance(CLSID_Result3Ds);

   try
   {

      // we are going to need an array for POI-by-POI computations below
      CComPtr<IIDArray> single_poi;
      hr = single_poi.CoCreateInstance(CLSID_IDArray);

      hr = single_poi->ReDim(1);

      CollectionIndexType nPois;
      pois->get_Count(&nPois);
      for ( CollectionIndexType poiIdx = 0; poiIdx < nPois; poiIdx++ )
      {
         // determine which engine (model) was the optimal, and get the appropriate response interfaces
         CollectionIndexType engine_idx = m_ControllingEngineReactions[poiIdx];

         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(engine_idx,  &engine);

         CComPtr<IConcurrentLoadCombinationResponse> concurrent_response;
         hr = engine->get_ConcurrentLoadCombinationResponse(&concurrent_response);

         // compute results one poi at a time
         PoiIDType poi_id;
         pois->get_Item(poiIdx, &poi_id);
         single_poi->put_Item(0, poi_id);

         CComPtr<IResult3Ds> results;
         concurrent_response->ComputeReactions(single_poi,stage,config,&results);

#if defined _DEBUG
         // we sent one poi in, expecting to get one result out
         CollectionIndexType c;
         results->get_Count(&c);
         ATLASSERT(c == 1);
#endif

         CComPtr<IResult3D> result;
         results->get_Item(0,&result);

         results->Add(result);
      }
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_IConcurrentLoadCombinationResponse);
   }

   hr = results.CopyTo(pResults);

   return S_OK;
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeSupportDeflections(IIDArray* pois, BSTR stage, ILoadCombinationResultConfiguration* config, IResult3Ds* *pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   // create a bucket to dump the results in
   CComPtr<IResult3Ds> results;
   hr = results.CoCreateInstance(CLSID_Result3Ds);

   try
   {

      // we are going to need an array for POI-by-POI computations below
      CComPtr<IIDArray> single_poi;
      hr = single_poi.CoCreateInstance(CLSID_IDArray);

      hr = single_poi->ReDim(1);

      CollectionIndexType nPois;
      pois->get_Count(&nPois);
      for ( CollectionIndexType poiIdx = 0; poiIdx < nPois; poiIdx++ )
      {
         // determine which engine (model) was the optimal, and get the appropriate response interfaces
         CollectionIndexType engine_idx = m_ControllingEngineReactions[poiIdx];

         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(engine_idx,  &engine);

         CComPtr<IConcurrentLoadCombinationResponse> concurrent_response;
         hr = engine->get_ConcurrentLoadCombinationResponse(&concurrent_response);

         // compute results one poi at a time
         PoiIDType poi_id;
         pois->get_Item(poiIdx, &poi_id);
         single_poi->put_Item(0, poi_id);

         CComPtr<IResult3Ds> results;
         concurrent_response->ComputeSupportDeflections(single_poi,stage,config,&results);

#if defined _DEBUG
         // we sent one poi in, expecting to get one result out
         CollectionIndexType c;
         results->get_Count(&c);
         ATLASSERT(c == 1);
#endif

         CComPtr<IResult3D> result;
         results->get_Item(0,&result);

         results->Add(result);
      }
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_IConcurrentLoadCombinationResponse);
   }

   hr = results.CopyTo(pResults);

   return S_OK;
}

STDMETHODIMP CLoadCombinationResponseAgg::ComputeStresses(IIDArray* pois, BSTR stage, ILoadCombinationResultConfiguration* config, ISectionStressResults* *pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   // create a bucket to dump the results in
   CComPtr<ISectionStressResults> results;
   hr = results.CoCreateInstance(CLSID_SectionStressResults);

   try
   {

      // we are going to need an array for POI-by-POI computations below
      CComPtr<IIDArray> single_poi;
      hr = single_poi.CoCreateInstance(CLSID_IDArray);

      hr = single_poi->ReDim(1);

      CollectionIndexType nPois;
      pois->get_Count(&nPois);
      for ( CollectionIndexType poiIdx = 0; poiIdx < nPois; poiIdx++ )
      {
         // determine which engine (model) was the optimal, and get the appropriate response interfaces
         CollectionIndexType left_engine_idx  = m_ControllingEngine[poiIdx].Left;
         CollectionIndexType right_engine_idx = m_ControllingEngine[poiIdx].Right;

         CComPtr<ILBAMAnalysisEngine> left_engine, right_engine;
         m_pEnveloper->GetEngine(left_engine_idx,  &left_engine);
         m_pEnveloper->GetEngine(right_engine_idx, &right_engine);

         CComPtr<IConcurrentLoadCombinationResponse> left_response, right_response;
         hr = left_engine->get_ConcurrentLoadCombinationResponse(&left_response);
         hr = right_engine->get_ConcurrentLoadCombinationResponse(&right_response);

         // compute results one poi at a time
         PoiIDType poi_id;
         pois->get_Item(poiIdx, &poi_id);
         single_poi->put_Item(0, poi_id);

         CComPtr<ISectionStressResults> left_results, right_results;
         left_response->ComputeStresses(single_poi,stage,config,&left_results);
         right_response->ComputeStresses(single_poi,stage,config,&right_results);

#if defined _DEBUG
         // we sent one poi in, expecting to get one result out
         CollectionIndexType c;
         left_results->get_Count(&c);
         ATLASSERT(c == 1);

         right_results->get_Count(&c);
         ATLASSERT(c == 1);
#endif

         CComPtr<ISectionStressResult> left_result, right_result;
         left_results->get_Item(0,&left_result);
         right_results->get_Item(0,&right_result);

         CComPtr<ISectionStressResult> result;
         hr = result.CoCreateInstance(CLSID_SectionStressResult);

         CollectionIndexType nLeft, nRight;
         left_result->get_RightCount(&nRight);
         right_result->get_LeftCount(&nLeft);

         for ( CollectionIndexType i = 0; i < nRight; i++ )
         {
            Float64 f;
            left_result->GetRightResult(i,&f);
            result->AddLeftResult(f);
         }

         for ( CollectionIndexType i = 0; i < nLeft; i++ )
         {
            Float64 f;
            right_result->GetLeftResult(i,&f);
            result->AddRightResult(f);
         }

         results->Add(result);
      }
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_IConcurrentLoadCombinationResponse);
   }

   hr = results.CopyTo(pResults);

   return S_OK;
}

// Make sure maximum value is in res1
void CLoadCombinationResponseAgg::EnvelopeLoadCombinationSectionResults(ILoadCombinationSectionResults* res1, ILoadCombinationSectionResults* res2,
                                           VARIANT_BOOL computeConfig, OptimizationType optimization, bool doFlip, CollectionIndexType engineIdx)
{
   CHRException hr;

   // use a function pointer to streamline min/max'ing
   bool (*lftcmp)(Float64, Float64);
   bool (*rgtcmp)(Float64, Float64);

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

   // loop over all pois and replace res1 with optmized results from res2 if needed.
   CollectionIndexType poi_cnt;
   hr = res1->get_Count(&poi_cnt);

   for (CollectionIndexType ipoi = 0; ipoi<poi_cnt; ipoi++)
   {
      CComPtr<ILoadCombinationResultConfiguration> lconf1, lconf2, rconf1, rconf2;
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


void CLoadCombinationResponseAgg::EnvelopeLoadCombinationResults(ILoadCombinationResults* res1, ILoadCombinationResults* res2,
                                    VARIANT_BOOL computeConfig, OptimizationType optimization,CollectionIndexType engineIdx)
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

   for (CollectionIndexType ipoi = 0; ipoi<poi_cnt; ipoi++)
   {
      CComPtr<ILoadCombinationResultConfiguration> conf1, conf2;
      Float64 val1, val2;

      hr = res1->GetResult(ipoi, &val1, &conf1);
      hr = res2->GetResult(ipoi, &val2, &conf2);

      bool did;
      did = cmp(val1, val2);

      if (did)
      {
         m_ControllingEngineReactions.push_back(engineIdx);
         hr = res1->SetResult(ipoi, val2, conf2);
      }
   }
}


