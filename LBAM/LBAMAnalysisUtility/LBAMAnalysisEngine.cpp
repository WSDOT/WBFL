///////////////////////////////////////////////////////////////////////
// LBAM Analysis Utility - Longitindal Bridge Analysis Model
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

// LBAMAnalysisEngine.cpp : Implementation of CLBAMAnalysisEngine
#include "stdafx.h"
#include "LBAMAnalysisUtility.hh"
#include "LBAMAnalysisEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLBAMAnalysisEngine

STDMETHODIMP CLBAMAnalysisEngine::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILBAMAnalysisEngine
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLBAMAnalysisEngine::Initialize(ILBAMModel *model, AnalysisType forceOrDeflection)
{
   return InitializeEx(model,forceOrDeflection,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr);
}

STDMETHODIMP CLBAMAnalysisEngine::InitializeEx(ILBAMModel* model,AnalysisType forceOrDeflection,
		                                         ILoadGroupResponse* plgResponse,
                                               IUnitLoadResponse* pUnitLoadResponse,
		                                         IInfluenceLineResponse* pilResponse,
		                                         IAnalysisPOIs* pPois,
		                                         IBasicVehicularResponse* pBVR,
		                                         ILiveLoadModelResponse* pLLMR,
		                                         IEnvelopedVehicularResponse* pEVR,
		                                         ILoadCaseResponse* plcResponse,
		                                         ILoadCombinationResponse* plcomboResponse,
		                                         IConcurrentLoadCombinationResponse* pclcResponse,
		                                         ILiveLoadNegativeMomentRegion* pllnmRegion,
		                                         IContraflexureResponse* pcontraResponse )
{
   CHECK_IN(model);

   CHRException hr;
   HRESULT hrr;

   try
   {
      if (m_pModel!=nullptr)
      {
         THROW_LBAMAU(ENGINE_INIT_ONCE)
      }

      m_pModel = model;
      m_AnalysisType = forceOrDeflection;

      // create base load group response engine
      if ( plgResponse )
      {
         // load group response provided.. use it
         m_pLoadGroupResponse = plgResponse;
      }
      else
      {
         // not provided... create one
         if (m_AnalysisType==atForce)
         {
            hrr = m_pLoadGroupResponse.CoCreateInstance(CLSID_LoadGroupForceResponse);
         }
         else
         {
            hrr = m_pLoadGroupResponse.CoCreateInstance(CLSID_LoadGroupDeflectionResponse);
         }

         if (FAILED(hrr))
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to create Load Group response component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }
      }

      // associate the load group response with the model
      CComQIPtr<IDependOnLBAM> lgctx(m_pLoadGroupResponse);
      if(lgctx==nullptr)
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI context interface from load group component"));
         THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
      }

      hr = lgctx->putref_Model(m_pModel);



      // get unit load interfaces
      if ( pUnitLoadResponse )
      {
         m_pUnitLoadResponse = pUnitLoadResponse;
      }
      else
      {
         CComQIPtr<IUnitLoadResponse> unitLoadResponse(m_pLoadGroupResponse);
         if(unitLoadResponse==nullptr)
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI unit load response component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }

         m_pUnitLoadResponse = unitLoadResponse;
      }


      // get influence interfaces
      if ( pilResponse )
      {
         m_pInfluenceLineResponse = pilResponse;
      }
      else
      {
         CComQIPtr<IInfluenceLineResponse> influence(m_pLoadGroupResponse);
         if(influence==nullptr)
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI influence response component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }

         m_pInfluenceLineResponse = influence;
      }

      // contraflexure response
      if ( pcontraResponse )
      {
         m_pContraflexureResponse = pcontraResponse;
      }
      else
      {
         CComQIPtr<IContraflexureResponse> contraflexure(m_pLoadGroupResponse);
         if(contraflexure==nullptr)
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI contraflexure response component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }

         m_pContraflexureResponse = contraflexure;
      }


      // live load negative moment region
      if ( pllnmRegion )
      {
         m_pLiveLoadNegativeMomentRegion = pllnmRegion;
      }
      else
      {
         CComQIPtr<ILiveLoadNegativeMomentRegion> llnmr(m_pLoadGroupResponse);
         if(llnmr==nullptr)
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI ILiveLoadNegativeMomentRegion response component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }

         m_pLiveLoadNegativeMomentRegion = llnmr;
      }

      // analysis pois

      if ( pPois )
      {
         m_pAnalysisPOIs = pPois;
      }
      else
      {
         CComQIPtr<IAnalysisPOIs> analysispois(m_pLoadGroupResponse);
         if(analysispois==nullptr)
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI analysis pois component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }

         m_pAnalysisPOIs = analysispois;
      }

      CComQIPtr<IGetStressPoints> get_sps(m_pLoadGroupResponse);
      if(get_sps==nullptr)
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI IGetStressPoints"));
         THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
      }

      CComQIPtr<IGetDistributionFactors> get_df(m_pLoadGroupResponse);
      if(get_df==nullptr)
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI IGetDistributionFactors"));
         THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
      }


      // set up live load context
      hrr = m_pVehicularAnalysisContext.CoCreateInstance( CLSID_VehicularAnalysisContext );
      if (FAILED(hrr))
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to create Vehicular Analysis Context context component"));
         THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
      }

      hr = m_pVehicularAnalysisContext->Initialize(m_pModel, m_pInfluenceLineResponse, m_pLiveLoadNegativeMomentRegion, m_pAnalysisPOIs, get_df, get_sps);


      // basic vehicular response
      if ( pBVR )
      {
         m_pBvResponse = pBVR;
      }
      else
      {
         hrr = m_pBvResponse.CoCreateInstance( CLSID_BasicVehicularResponse );
         if (FAILED(hrr))
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to create Basic Vehicular Response component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }
      }

      CComQIPtr<IDependOnVehicularAnalysisContext> depcontxt(m_pBvResponse);
      if(depcontxt==nullptr)
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI Vehicular Analysis Context Dependency component"));
         THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
      }

      hr = depcontxt->Initialize(m_pVehicularAnalysisContext);

      if ( pEVR )
      {
         m_pEnvResponse = pEVR;
      }
      else
      {
         hrr = m_pEnvResponse.CoCreateInstance( CLSID_BruteForceVehicularResponse2 );
         if (FAILED(hrr))
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to create Brute Force Vehicular Response component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }
      }
      depcontxt.Release();
      m_pEnvResponse->QueryInterface(&depcontxt);
      if(depcontxt==nullptr)
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI Vehicular Analysis Context Dependency component"));
         THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
      }

      hr = depcontxt->Initialize(m_pVehicularAnalysisContext);
      

      // LiveLoadModel Response
      if ( pLLMR )
      {
         m_pLiveLoadModelResponse = pLLMR;
      }
      else
      {
         hrr = m_pLiveLoadModelResponse.CoCreateInstance( CLSID_LiveLoadModelResponse );
         if (FAILED(hrr))
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to create LiveLoadModel Response component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }
      }

      // make the live load model response use the same response engine as the one provided (or created earlier)
      CComQIPtr<ISupportEnvelopedVehicularResponseFactory> supportFactory(m_pLiveLoadModelResponse);
      if ( supportFactory )
         supportFactory->putref_EnvelopedVehicularRepsonse(m_pEnvResponse);


      CComQIPtr<IDependOnVehicularAnalysisContext> envdepcontxt(m_pLiveLoadModelResponse);
      if(envdepcontxt==nullptr)
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI analysis pois component"));
         THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
      }

      hr = envdepcontxt->Initialize(m_pVehicularAnalysisContext);

      // Enveloped Vehicular Response
      if ( !m_pEnvResponse )
      {
         CComQIPtr<IEnvelopingStrategy> envstrategy(m_pLiveLoadModelResponse);
         if(envstrategy==nullptr)
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI LiveLoadModelResponse component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }

         hr = envstrategy->get_Strategy(&m_pEnvResponse);
      }

      // create our load combination context
      CComPtr<ILoadCombinationAnalysisContext> plclc;
      hrr = plclc.CoCreateInstance( CLSID_LoadCombinationAnalysisContext );
      if (FAILED(hrr))
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to create LoadCombinationAnalysisContext component"));
         THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
      }

      hr = plclc->Initialize(m_pModel, m_pLoadGroupResponse, m_pLiveLoadModelResponse, m_pBvResponse, m_pAnalysisPOIs, get_sps);

      // make a load combiner
      if ( plcResponse )
      {
         m_pLoadCaseResponse = plcResponse;
      }
      else
      {
         CComPtr<ILoadCaseResponse> lc_response;
         hrr = lc_response.CoCreateInstance( CLSID_LoadCombiner );
         if (FAILED(hrr))
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to create LoadCombiner component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }

         m_pLoadCaseResponse = lc_response;
      }

      // initialize our load combiner with the context
      CComQIPtr<IDependOnLoadCombinationAnalysisContext> depctx(m_pLoadCaseResponse);
      if (depctx==nullptr)
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI DependOnLoadCombinationAnalysisContext component"));
         THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
      }

      hr = depctx->Initialize(plclc);

      if ( plcomboResponse )
      {
         m_pLoadCombinationResponse = plcomboResponse;
      }
      else
      {
         CComQIPtr<ILoadCombinationResponse> lcr_response(m_pLoadCaseResponse);
         if (lcr_response==nullptr)
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI LoadCombinationResponse component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }

         m_pLoadCombinationResponse = lcr_response;
      }

      if ( pclcResponse )
      {
         m_pConcurrentLoadCombinationResponse = pclcResponse;
      }
      else
      {
         CComQIPtr<IConcurrentLoadCombinationResponse> clcr_response(m_pLoadCaseResponse);
         if (clcr_response==nullptr)
         {
            CComBSTR msg = CreateErrorMsg1S(IDS_E_INVALID_CONTEXT, CComBSTR("Unable to QI ConcurrentLoadCombinationResponse component"));
            THROW_LBAMAU_MSG(INVALID_CONTEXT, msg);
         }

         m_pConcurrentLoadCombinationResponse = clcr_response;
      }
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}

STDMETHODIMP CLBAMAnalysisEngine::get_UnitLoadResponse(IUnitLoadResponse* *pVal)
{
   CHECK_RETOBJ(pVal);

   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pUnitLoadResponse!=nullptr);

      return m_pUnitLoadResponse.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}

STDMETHODIMP CLBAMAnalysisEngine::get_LoadGroupResponse(ILoadGroupResponse **pVal)
{
   CHECK_RETOBJ(pVal);

   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pLoadGroupResponse!=nullptr);

      return m_pLoadGroupResponse.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}


STDMETHODIMP CLBAMAnalysisEngine::get_ContraflexureResponse(IContraflexureResponse **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pContraflexureResponse!=nullptr);

      return m_pContraflexureResponse.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}


STDMETHODIMP CLBAMAnalysisEngine::get_InfluenceLineResponse(IInfluenceLineResponse **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pInfluenceLineResponse!=nullptr);

      return m_pInfluenceLineResponse.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}


STDMETHODIMP CLBAMAnalysisEngine::get_AnalysisPOIs(IAnalysisPOIs **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pAnalysisPOIs!=nullptr);

      return m_pAnalysisPOIs.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}

STDMETHODIMP CLBAMAnalysisEngine::get_BasicVehicularResponse(IBasicVehicularResponse **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pBvResponse!=nullptr);

      return m_pBvResponse.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}

STDMETHODIMP CLBAMAnalysisEngine::get_LiveLoadModelResponse(ILiveLoadModelResponse **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pLiveLoadModelResponse!=nullptr);

      return m_pLiveLoadModelResponse.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}

STDMETHODIMP CLBAMAnalysisEngine::get_EnvelopedVehicularResponse(IEnvelopedVehicularResponse **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pEnvResponse!=nullptr);

      return m_pEnvResponse.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}


STDMETHODIMP CLBAMAnalysisEngine::get_LoadCaseResponse(ILoadCaseResponse **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pLoadCaseResponse!=nullptr);

      return m_pLoadCaseResponse.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}

STDMETHODIMP CLBAMAnalysisEngine::get_LoadCombinationResponse(ILoadCombinationResponse **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pLoadCombinationResponse!=nullptr);

      return m_pLoadCombinationResponse.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}

STDMETHODIMP CLBAMAnalysisEngine::get_ConcurrentLoadCombinationResponse(IConcurrentLoadCombinationResponse **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pConcurrentLoadCombinationResponse!=nullptr);

      return m_pConcurrentLoadCombinationResponse.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}

STDMETHODIMP CLBAMAnalysisEngine::get_Model(ILBAMModel **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      return m_pModel.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}

STDMETHODIMP CLBAMAnalysisEngine::get_LiveLoadNegativeMomentRegion(ILiveLoadNegativeMomentRegion **pVal)
{
   CHECK_RETOBJ(pVal);
   try
   {
	   if (m_pModel==nullptr)
         THROW_LBAMAU(ENGINE_INIT);

      ATLASSERT(m_pLiveLoadNegativeMomentRegion!=nullptr);

      return m_pLiveLoadNegativeMomentRegion.CopyTo(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

	return S_OK;
}



STDMETHODIMP CLBAMAnalysisEngine::get_AnalysisType(AnalysisType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_AnalysisType;

	return S_OK;
}

// ISupportProgressMonitor
STDMETHODIMP CLBAMAnalysisEngine::InitializeProgressMonitor4E(IProgressMonitor * iPm, LONG loadGroupCookie, LONG liveLoadCookie, LONG loadCombinationCookie)
{
   CHRException hr;
   if (m_pModel==nullptr)
   {
      // engine must be initialized before calling this
      ATLASSERT(FALSE); 
      return Error(LBAMU_E_PROGRESS_INIT_SEQUENCE,IID_ISupportProgressMonitor,IDS_E_PROGRESS_INIT_SEQUENCE);
   }

   try
   {
      // load group, influence line, and contraflexure response - we know our components well
      CComQIPtr<ISupportProgressMonitor> lgispm(m_pLoadGroupResponse);
      if (lgispm==nullptr)
      {
         ATLASSERT(false);
         return E_FAIL;
      }

      hr = lgispm->InitializeProgressMonitor(iPm, loadGroupCookie);

      // load combiner
      CComQIPtr<ISupportProgressMonitor> cispm(m_pLoadCombinationResponse);
      if (cispm==nullptr)
      {
         // this should never happen since we should know who we have created (eating our own dog food)
         ATLASSERT(false);
         return E_FAIL;
      }

      hr = cispm->InitializeProgressMonitor(iPm, loadCombinationCookie);

      // basic live load
      CComQIPtr<ISupportProgressMonitor> bvispm(m_pBvResponse);
      if (bvispm==nullptr)
      {
         // this should never happen since we should know who we have created (eating our own dog food)
         ATLASSERT(false);
         return E_FAIL;
      }

      hr = bvispm->InitializeProgressMonitor(iPm, liveLoadCookie);

      // enveloped live load
      CComQIPtr<ISupportProgressMonitor> evlispm(m_pEnvResponse);
      if (evlispm==nullptr)
      {
         // this should never happen since we should know who we have created (eating our own dog food)
         ATLASSERT(false);
         return E_FAIL;
      }

      hr = evlispm->InitializeProgressMonitor(iPm, liveLoadCookie);

      // live load model response
      CComQIPtr<ISupportProgressMonitor> llmispm(m_pLiveLoadModelResponse);
      if (llmispm==nullptr)
      {
         // this should never happen since we should know who we have created (eating our own dog food)
         ATLASSERT(false);
         return E_FAIL;
      }

      hr = llmispm->InitializeProgressMonitor(iPm, liveLoadCookie);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMAnalysisEngine);
   }

   return S_OK;
}


