///////////////////////////////////////////////////////////////////////
// LBAM Analysis Utility - Longitindal Bridge Analysis Model
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

// LBAMModelEnveloper.h : Declaration of the CLBAMModelEnveloper

#ifndef __LBAMMODELENVELOPER_H_
#define __LBAMMODELENVELOPER_H_

#include "resource.h"       // main symbols

#include <vector>
#include <WBFLUnitServer.h>
#include <WBFLLBAMAnalysisUtility.h>



class CLoadCombinationResponseAgg;
class CLiveLoadResponseAgg;

/////////////////////////////////////////////////////////////////////////////
// CLBAMModelEnveloper
class ATL_NO_VTABLE CLBAMModelEnveloper : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLBAMModelEnveloper, &CLSID_LBAMModelEnveloper>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CLBAMModelEnveloper,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportProgressMonitor,
	public ILBAMModelEnveloper
{
public:
   friend CLoadCombinationResponseAgg;

	CLBAMModelEnveloper()
	{
	}

   HRESULT FinalConstruct();


DECLARE_REGISTRY_RESOURCEID(IDR_LBAMMODELENVELOPER)

DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CLBAMModelEnveloper)
	COM_INTERFACE_ENTRY(ILBAMModelEnveloper)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_AGGREGATE(IID_ILoadCombinationResponse, m_pLoadCombinationResponseAgg.p)
   COM_INTERFACE_ENTRY_AGGREGATE(IID_IConcurrentLoadCombinationResponse, m_pLoadCombinationResponseAgg.p)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(ISupportProgressMonitor)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISupportProgressMonitor
	STDMETHOD(InitializeProgressMonitor)(IProgressMonitor * newVal, LONG cookie);


// ILBAMModelEnveloper
public:
	STDMETHOD(get_LoadGroupResponse)(/*[in]*/ ForceEffectType forceEffect, /*[in]*/ OptimizationType optimization, /*[out,retval]*/ ILoadGroupResponse** pVal);
   STDMETHOD(get_LoadCaseResponse)(/*[in]*/ ForceEffectType forceEffect, /*[in]*/ OptimizationType optimization, /*[out,retval]*/ ILoadCaseResponse** pVal);
	STDMETHOD(get_LoadCombinationResponse)(/*[out, retval]*/ ILoadCombinationResponse* *pVal);
   STDMETHOD(get_EnvelopedVehicularResponse)(/*[out, retval]*/ IEnvelopedVehicularResponse* *pVal);
   STDMETHOD(get_LiveLoadModelResponse)(/*[out,retval]*/ ILiveLoadModelResponse* *pVal);
	STDMETHOD(Initialize)(/*[in]*/ IUnkArray* models, AnalysisType aType,/*[in]*/OptimizationType opType);
	STDMETHOD(get_Engines)(/*[out]*/ IUnkArray* * models);
	STDMETHOD(get_AnalysisType)(/*[out]*/ AnalysisType* type);
   STDMETHOD(get_OptimizationType)(/*[out]*/ OptimizationType* opType);

	STDMETHOD(AddModel)(/*[in]*/ILBAMModel* pModel);
   STDMETHOD(AddEngine)(/*[in]*/ILBAMAnalysisEngine* pEngine);

   CollectionIndexType EngineCount();
   void GetEngine(CollectionIndexType idx, ILBAMAnalysisEngine* *engine);

protected:
   std::vector< CAdapt< CComPtr<ILBAMAnalysisEngine> > > m_Engines;
   AnalysisType                                          m_AnalysisType;
   OptimizationType                                      m_OptimizationType;

// aggregates
   CComPtr<IUnknown>                 m_pLoadGroupResponseAgg[3][2];  // first index = force effect
   CComPtr<IUnknown>                 m_pLoadCaseResponseAgg[3][2];   // second index = optimization type
   CComPtr<IUnknown>                 m_pLoadCombinationResponseAgg;
   CComPtr<IUnknown>                 m_pLiveLoadResponseAgg;
   CComPtr<IUnknown>                 m_pEnvelopedVehicularLoadResponseAgg;

   // progress monitoring
public:
   bool CheckForCancel()
   {
      if (m_pProgressMonitor)
      {
         VARIANT_BOOL cncl = VARIANT_FALSE;
         HRESULT hr = m_pProgressMonitor->get_WasCancelled(&cncl);
         ATLASSERT(SUCCEEDED(hr));
         return cncl!=VARIANT_FALSE;
      }
      else
         return false;
   }

   CComPtr<IProgressMonitor>                m_pProgressMonitor;
   long                                     m_ProgressCookie;
};

#endif //__LBAMMODELENVELOPER_H_
