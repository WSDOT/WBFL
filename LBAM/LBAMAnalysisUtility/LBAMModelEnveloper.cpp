///////////////////////////////////////////////////////////////////////
// LBAM Analysis Utility - Longitindal Bridge Analysis Model
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

// LBAMModelEnveloper.cpp : Implementation of CLBAMModelEnveloper
#include "stdafx.h"
#include "LBAMModelEnveloper.h"

#include "LoadGroupResponseAgg.h"
#include "LoadCaseResponseAgg.h"
#include "LoadCombinationResponseAgg.h"
#include "LiveLoadResponseAgg.h"
#include "EnvelopedVehicularLoadResponseAgg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLBAMModelEnveloper

STDMETHODIMP CLBAMModelEnveloper::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILBAMModelEnveloper
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CLBAMModelEnveloper::FinalConstruct()
{
   HRESULT hr;
   // Create aggregated objects
   // For some undocumented reason, you must ask for iunknown when aggregating
   IUnknown* pControllingUnknown = this->GetControllingUnknown();

   for ( int i = 0; i < 3; i++ ) // ForceEffectType
   {
      for ( int j = 0; j < 2; j++ ) // OptimizationType
      {
         CComAggObject<CLoadGroupResponseAgg>* pLoadGroupResponseAgg;
         hr = CComAggObject<CLoadGroupResponseAgg>::CreateInstance(pControllingUnknown,&pLoadGroupResponseAgg);
         if ( FAILED(hr))
         {
            ATLASSERT(false);
            return hr;
         }

         pLoadGroupResponseAgg->m_contained.m_pEnveloper = this;
         pLoadGroupResponseAgg->m_contained.m_ForceEffect = (ForceEffectType)i;
         pLoadGroupResponseAgg->m_contained.m_Optimization = (OptimizationType)j;

         hr = pLoadGroupResponseAgg->QueryInterface(IID_IUnknown,(void**)&m_pLoadGroupResponseAgg[i][j]);
         if (FAILED(hr))
         {
            ATLASSERT(false);
            return hr;
         }



         CComAggObject<CLoadCaseResponseAgg>* pLoadCaseResponseAgg;
         hr = CComAggObject<CLoadCaseResponseAgg>::CreateInstance(pControllingUnknown,&pLoadCaseResponseAgg);
         if ( FAILED(hr))
         {
            ATLASSERT(false);
            return hr;
         }

         pLoadCaseResponseAgg->m_contained.m_pEnveloper = this;
         pLoadCaseResponseAgg->m_contained.m_ForceEffect = (ForceEffectType)i;
         pLoadCaseResponseAgg->m_contained.m_Optimization = (OptimizationType)j;

         hr = pLoadCaseResponseAgg->QueryInterface(IID_IUnknown,(void**)&m_pLoadCaseResponseAgg[i][j]);
         if (FAILED(hr))
         {
            ATLASSERT(false);
            return hr;
         }
      }
   }



   // LoadCombination Response
   CComAggObject<CLoadCombinationResponseAgg>* pLoadCombinationResponseAgg;
   hr = CComAggObject<CLoadCombinationResponseAgg>::CreateInstance(pControllingUnknown,&pLoadCombinationResponseAgg);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   // tell our aggregate about us
   pLoadCombinationResponseAgg->m_contained.m_pEnveloper = this;

   hr = pLoadCombinationResponseAgg->QueryInterface(IID_IUnknown, (void**)&m_pLoadCombinationResponseAgg);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   // Live Load Response
   CComAggObject<CLiveLoadResponseAgg>* pLiveLoadResponseAgg;
   hr = CComAggObject<CLiveLoadResponseAgg>::CreateInstance(pControllingUnknown,&pLiveLoadResponseAgg);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   // tell our aggregate about us
   pLiveLoadResponseAgg->m_contained.m_pEnveloper = this;

   hr = pLiveLoadResponseAgg->QueryInterface(IID_IUnknown, (void**)&m_pLiveLoadResponseAgg);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }


   // Vehicular Load Envelope Response
   CComAggObject<CEnvelopedVehicularLoadResponseAgg>* pEnvelopedVehicularLoadResponseAgg;
   hr = CComAggObject<CEnvelopedVehicularLoadResponseAgg>::CreateInstance(pControllingUnknown,&pEnvelopedVehicularLoadResponseAgg);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   // tell our aggregate about us
   pEnvelopedVehicularLoadResponseAgg->m_contained.m_pEnveloper = this;

   hr = pEnvelopedVehicularLoadResponseAgg->QueryInterface(IID_IUnknown, (void**)&m_pEnvelopedVehicularLoadResponseAgg);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   return S_OK;
}

STDMETHODIMP CLBAMModelEnveloper::Initialize(IUnkArray* pModels, AnalysisType aType,OptimizationType opType)
{
   HRESULT hr;

   m_AnalysisType = aType;
   m_OptimizationType = opType;

   m_Engines.clear();

   if ( !pModels )
      return S_OK;

   // loop over each model and set up an engine for it
   CollectionIndexType nModels;
   hr = pModels->get_Count(&nModels);
   if (FAILED(hr))
      return hr;


   for (CollectionIndexType im = 0; im < nModels; im++)
   {
      CComPtr<IUnknown> unk;
      hr = pModels->get_Item(im, &unk);
      if (FAILED(hr))
         return hr;

      CComQIPtr<ILBAMModel> mdl(unk);
      if (mdl==nullptr)
      {
         m_Engines.clear();
         return E_INVALIDARG;
      }

      CComPtr<ILBAMAnalysisEngine> engine;
      hr = engine.CoCreateInstance(CLSID_LBAMAnalysisEngine);
      if (FAILED(hr))
         return hr;

      hr = engine->Initialize(mdl, m_AnalysisType);
      if (FAILED(hr))
         return hr;


      m_Engines.push_back ( engine );

   }

	return S_OK;
}

STDMETHODIMP CLBAMModelEnveloper::AddModel(ILBAMModel* pModel)
{
   HRESULT hr = S_OK;

   CComPtr<ILBAMAnalysisEngine> engine;
   hr = engine.CoCreateInstance(CLSID_LBAMAnalysisEngine);
   if (FAILED(hr))
      return hr;

   hr = engine->Initialize(pModel, m_AnalysisType);
   if (FAILED(hr))
      return hr;

   m_Engines.push_back ( engine );

   return S_OK;
}

STDMETHODIMP CLBAMModelEnveloper::AddEngine(ILBAMAnalysisEngine* pEngine)
{
   AnalysisType analysisType;
   pEngine->get_AnalysisType(&analysisType);

   if (analysisType != m_AnalysisType )
      return E_INVALIDARG;

   CComPtr<ILBAMAnalysisEngine> engine(pEngine);
   m_Engines.push_back(engine);

   return S_OK;
}

// ISupportProgressMonitor
STDMETHODIMP CLBAMModelEnveloper::InitializeProgressMonitor(IProgressMonitor * newVal, LONG cookie)
{
   m_pProgressMonitor = newVal;
   m_ProgressCookie = cookie;

   return S_OK;
}


STDMETHODIMP CLBAMModelEnveloper::get_Engines(IUnkArray* *pVal)
{
   CHECK_RETOBJ(pVal);

   HRESULT hr;

   CComPtr<IUnkArray> unka;
   hr = unka.CoCreateInstance(CLSID_UnkArray);
   if (FAILED(hr))
      return hr;

   CollectionIndexType cnt = m_Engines.size();
   for (CollectionIndexType im = 0; im<cnt; im++)
   {
     
      hr = unka->Add(m_Engines[im].m_T);
      if (FAILED(hr))
         return hr;
   }

	return unka.CopyTo(pVal);
}

STDMETHODIMP CLBAMModelEnveloper::get_AnalysisType(AnalysisType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_AnalysisType;
	return S_OK;
}

STDMETHODIMP CLBAMModelEnveloper::get_OptimizationType(OptimizationType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_OptimizationType;
	return S_OK;
}

CollectionIndexType CLBAMModelEnveloper::EngineCount()
{
   return m_Engines.size();
}

void CLBAMModelEnveloper::GetEngine(CollectionIndexType idx, ILBAMAnalysisEngine* *engine)
{
   try
   {
      HRESULT hr;
      hr = m_Engines[idx].m_T.CopyTo(engine);

      if (FAILED(hr))
      {
         ATLASSERT(false);
         throw hr;
      }
   }
   catch(...)
   {
      ATLASSERT(false);
      *engine = nullptr;
   }
}

STDMETHODIMP CLBAMModelEnveloper::get_LoadCombinationResponse(ILoadCombinationResponse* *pVal)
{
   CHECK_RETOBJ(pVal);
   CComQIPtr<ILoadCombinationResponse> resp(m_pLoadCombinationResponseAgg);
	return resp.CopyTo(pVal);
}

STDMETHODIMP CLBAMModelEnveloper::get_LiveLoadModelResponse(ILiveLoadModelResponse* *pVal)
{
   CHECK_RETOBJ(pVal);
   CComQIPtr<ILiveLoadModelResponse> resp(m_pLiveLoadResponseAgg);
	return resp.CopyTo(pVal);
}

STDMETHODIMP CLBAMModelEnveloper::get_EnvelopedVehicularResponse(IEnvelopedVehicularResponse* *pVal)
{
   CHECK_RETOBJ(pVal);
   CComQIPtr<IEnvelopedVehicularResponse> resp(m_pEnvelopedVehicularLoadResponseAgg);
	return resp.CopyTo(pVal);
}

STDMETHODIMP CLBAMModelEnveloper::get_LoadGroupResponse(ForceEffectType forceEffect, OptimizationType optimization, ILoadGroupResponse** pVal)
{
   CHECK_RETOBJ(pVal);
   CComQIPtr<ILoadGroupResponse> resp(m_pLoadGroupResponseAgg[forceEffect][optimization]);
	return resp.CopyTo(pVal);
}

STDMETHODIMP CLBAMModelEnveloper::get_LoadCaseResponse(ForceEffectType forceEffect, OptimizationType optimization, ILoadCaseResponse** pVal)
{
   CHECK_RETOBJ(pVal);
   CComQIPtr<ILoadCaseResponse> resp(m_pLoadCaseResponseAgg[forceEffect][optimization]);
	return resp.CopyTo(pVal);
}

