///////////////////////////////////////////////////////////////////////
// LBAM Analysis Utility - Longitindal Bridge Analysis Model
// Copyright © 1999-2010  Washington State Department of Transportation
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

// LBAMAnalysisEngine.h : Declaration of the CLBAMAnalysisEngine

#ifndef __LBAMANALYSISENGINE_H_
#define __LBAMANALYSISENGINE_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <WBFLLBAMAnalysisUtility.h>

/////////////////////////////////////////////////////////////////////////////
// CLBAMAnalysisEngine
class ATL_NO_VTABLE CLBAMAnalysisEngine : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CLBAMAnalysisEngine,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CLBAMAnalysisEngine, &CLSID_LBAMAnalysisEngine>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLBAMAnalysisEngine>,
	public ILBAMAnalysisEngine,
   public IObjectSafetyImpl<CLBAMAnalysisEngine,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportProgressMonitorForEngine
{
public:
	CLBAMAnalysisEngine()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LBAMANALYSISENGINE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLBAMAnalysisEngine)
	COM_INTERFACE_ENTRY(ILBAMAnalysisEngine)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISupportProgressMonitorForEngine)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLBAMAnalysisEngine)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILBAMAnalysisEngine
public:
	STDMETHOD(get_ContraflexureResponse)(/*[out, retval]*/ IContraflexureResponse* *pVal);
	STDMETHOD(get_LiveLoadNegativeMomentRegion)(/*[out, retval]*/ ILiveLoadNegativeMomentRegion* *pVal);
	STDMETHOD(get_AnalysisType)(/*[out, retval]*/ AnalysisType *pVal);
	STDMETHOD(get_Model)(/*[out, retval]*/ ILBAMModel* *pVal);
	STDMETHOD(get_LoadCaseResponse)(/*[out, retval]*/ ILoadCaseResponse* *pVal);
	STDMETHOD(get_EnvelopedVehicularResponse)(/*[out, retval]*/ IEnvelopedVehicularResponse* *pVal);
	STDMETHOD(get_LiveLoadModelResponse)(/*[out, retval]*/ ILiveLoadModelResponse* *pVal);
	STDMETHOD(get_BasicVehicularResponse)(/*[out, retval]*/ IBasicVehicularResponse* *pVal);
	STDMETHOD(get_AnalysisPOIs)(/*[out, retval]*/ IAnalysisPOIs* *pVal);
	STDMETHOD(get_InfluenceLineResponse)(/*[out, retval]*/ IInfluenceLineResponse* *pVal);
	STDMETHOD(get_LoadGroupResponse)(/*[out, retval]*/ ILoadGroupResponse* *pVal);
	STDMETHOD(get_LoadCombinationResponse)(/*[out, retval]*/ ILoadCombinationResponse* *pVal);
	STDMETHOD(get_ConcurrentLoadCombinationResponse)(/*[out, retval]*/ IConcurrentLoadCombinationResponse* *pVal);
	STDMETHOD(Initialize)(/*[in]*/ILBAMModel* model, /*[in]*/AnalysisType forceOrDeflection);
   STDMETHOD(InitializeEx)(/*[in]*/ILBAMModel* model, /*[in]*/AnalysisType forceOrDeflection,
		                     /*[in]*/ ILoadGroupResponse* plgResponse,
		                     /*[in]*/ IInfluenceLineResponse* pilResponse,
		                     /*[in]*/ IAnalysisPOIs* pPois,
		                     /*[in]*/ IBasicVehicularResponse* pBVR,
		                     /*[in]*/ ILiveLoadModelResponse* pLLMR,
		                     /*[in]*/ IEnvelopedVehicularResponse* pEVR,
		                     /*[in]*/ ILoadCaseResponse* plcResponse,
		                     /*[in]*/ ILoadCombinationResponse* plcomboResponse,
		                     /*[in]*/ IConcurrentLoadCombinationResponse* pclcResponse,
		                     /*[in]*/ ILiveLoadNegativeMomentRegion* pllnmRegion,
		                     /*[in]*/ IContraflexureResponse* pcontraResponse );

// ISupportProgressMonitorForEngine
	STDMETHOD(InitializeProgressMonitor4E)(IProgressMonitor* newVal, LONG loadGroupCookie, LONG liveLoadCookie, LONG loadCombinationCookie);

private:
   AnalysisType                                 m_AnalysisType;

   CComPtr<ILBAMModel>                          m_pModel;
   CComPtr<IContraflexureResponse>              m_pContraflexureResponse;
   CComPtr<ILoadGroupResponse>                  m_pLoadGroupResponse;
   CComPtr<ILiveLoadNegativeMomentRegion>       m_pLiveLoadNegativeMomentRegion;
   CComPtr<IInfluenceLineResponse>              m_pInfluenceLineResponse;
   CComPtr<IAnalysisPOIs>                       m_pAnalysisPOIs;
   CComPtr<IVehicularAnalysisContext>           m_pVehicularAnalysisContext;
   CComPtr<IBasicVehicularResponse>             m_pBvResponse;
   CComQIPtr<ILiveLoadModelResponse>            m_pLiveLoadModelResponse;
   CComPtr<IEnvelopedVehicularResponse>         m_pEnvResponse;
   CComPtr<ILoadCaseResponse>                   m_pLoadCaseResponse;
   CComPtr<ILoadCombinationResponse>            m_pLoadCombinationResponse;
   CComPtr<IConcurrentLoadCombinationResponse>  m_pConcurrentLoadCombinationResponse;
};

#endif //__LBAMANALYSISENGINE_H_
