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

// LiveLoadModelResponse.h : Declaration of the CLiveLoadModelResponse

#ifndef __LIVELOADMODELRESPONSE_H_
#define __LIVELOADMODELRESPONSE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadModelResponse
class ATL_NO_VTABLE CLiveLoadModelResponse : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CLiveLoadModelResponse,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CLiveLoadModelResponse, &CLSID_LiveLoadModelResponse>,
	public ISupportErrorInfo,
	public IEnvelopingStrategy,
	public IDependOnVehicularAnalysisContext,
	public ILiveLoadModelResponse,
   public ISupportEnvelopedVehicularResponseFactory,
   public IObjectSafetyImpl<CLiveLoadModelResponse,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportProgressMonitor
{
public:
	CLiveLoadModelResponse()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LIVELOADMODELRESPONSE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLiveLoadModelResponse)
	COM_INTERFACE_ENTRY(ILiveLoadModelResponse)
	COM_INTERFACE_ENTRY(IDependOnVehicularAnalysisContext)
   COM_INTERFACE_ENTRY(ISupportEnvelopedVehicularResponseFactory)
	COM_INTERFACE_ENTRY(IEnvelopingStrategy)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(ISupportProgressMonitor)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

public:
// IDependOnVehicularAnalysisContext
	STDMETHOD(Initialize)(/*[in]*/IUnknown* context) override;

// ISupportProgressMonitor
	STDMETHOD(InitializeProgressMonitor)(IProgressMonitor * newVal, LONG cookie) override;

// IEnvelopingStrategy
	STDMETHOD(get_Strategy)(IEnvelopedVehicularResponse * * pVal) override;
	STDMETHOD(putref_Strategy)(IEnvelopedVehicularResponse * pVal) override;

// ISupportEnvelopedVehicularResponseFactory
	STDMETHOD(putref_EnvelopedVehicularRepsonseFactory)(/*[in]*/ IEnvelopedVehicularResponseFactory* pFactory) override;
	STDMETHOD(get_EnvelopedVehicularRepsonseFactory)(/*[out,retval]*/ IEnvelopedVehicularResponseFactory** pFactory) override;
   STDMETHOD(putref_EnvelopedVehicularRepsonse)(/*[in]*/ IEnvelopedVehicularResponse* pResponse) override;

// ILiveLoadModelResponse
	STDMETHOD(ComputeForces)(/*[in]*/IIDArray* pois, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                            /*[in]*/ResultsOrientation orientation, /*[in]*/ForceEffectType effect, 
                            /*[in]*/OptimizationType optimization, 
                            /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                            /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                            /*[in]*/VARIANT_BOOL computePlacement,
                            /*[out]*/ILiveLoadModelSectionResults** results) override;

	STDMETHOD(ComputeDeflections)(/*[in]*/IIDArray* pois, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                                /*[in]*/ForceEffectType effect, 
                                /*[in]*/OptimizationType optimization, 
                                /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                                /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                                /*[in]*/VARIANT_BOOL computePlacement,
                                /*[out]*/ILiveLoadModelSectionResults** results) override;

	STDMETHOD(ComputeReactions)(/*[in]*/IIDArray* pois, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                               /*[in]*/ForceEffectType effect, 
                               /*[in]*/OptimizationType optimization, 
                               /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                               /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                               /*[in]*/VARIANT_BOOL computePlacement,
                               /*[out]*/ILiveLoadModelResults** results) override;

	STDMETHOD(ComputeSupportDeflections)(/*[in]*/IIDArray* pois, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                               /*[in]*/ForceEffectType effect, 
                               /*[in]*/OptimizationType optimization, 
                               /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                               /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                               /*[in]*/VARIANT_BOOL computePlacement,
                               /*[out]*/ILiveLoadModelResults** results) override;

	STDMETHOD(ComputeStresses)(/*[in]*/IIDArray* pois, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                              /*[in]*/ForceEffectType effect, 
                              /*[in]*/OptimizationType optimization, 
                              /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                              /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                              /*[in]*/VARIANT_BOOL computePlacement,
                              /*[out]*/ILiveLoadModelStressResults** results) override;

private:
   // progress monitoring
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

   // innards
   CComPtr<IEnvelopedVehicularResponseFactory> m_Factory;
   CComPtr<IUnknown>                       m_Context;
   CComPtr<ILiveLoad>                      m_LiveLoad;
   CComPtr<IInfluenceLineResponse>         m_InfluenceLineResponse;
   CComPtr<ILiveLoadNegativeMomentRegion>  m_LiveLoadNegativeMomentRegion;
   CComPtr<IGetDistributionFactors>        m_GetDistributionFactors;
   CComPtr<ISupportLocations>              m_SupportLocations;
   CComPtr<IGetStressPoints>               m_GetStressPoints;

   CComPtr<IEnvelopedVehicularResponse> m_EnvelopedResponse;

};

#endif //__LIVELOADMODELRESPONSE_H_
