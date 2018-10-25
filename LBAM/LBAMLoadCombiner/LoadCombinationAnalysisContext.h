///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2018  Washington State Department of Transportation
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

// LoadCombinationAnalysisContext.h : Declaration of the CLoadCombinationAnalysisContext

#ifndef __LOADCOMBINATIONANALYSISCONTEXT_H_
#define __LOADCOMBINATIONANALYSISCONTEXT_H_

#include "resource.h"       // main symbols
#include "LBAMLoadCombinerCP.h"
#include "LoadCasesAgg.h"
#include "StagesAgg.h"
#include "LoadCombinationsAgg.h"

#include <map>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationAnalysisContext
class ATL_NO_VTABLE CLoadCombinationAnalysisContext : 
#if defined (_DEBUG_LOGGING)
   public CComRefCountTracer<CLoadCombinationAnalysisContext,CComObjectRootEx<CComSingleThreadModel> >,
#else
	public CComObjectRootEx<CComSingleThreadModel>,
#endif
	public CComCoClass<CLoadCombinationAnalysisContext, &CLSID_LoadCombinationAnalysisContext>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLoadCombinationAnalysisContext>,
	public ILoadCombinationAnalysisContext,
	public ILoadGroupResponse, 
	public ILiveLoadModelResponse,
	public IBasicVehicularResponse,
	public IGetActiveLoadGroups, 
	public IGetCombinationFactors,
	public IAnalysisPOIs, 
	public IGetStressPoints,
	public ILBAMModelEvents,
	public ILoadCasesEvents,
   public ILoadCombinationsEvents,
   public IObjectSafetyImpl<CLoadCombinationAnalysisContext,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDLoadCombinationAnalysisContextEvents< CLoadCombinationAnalysisContext >
{
public:
   CLoadCombinationAnalysisContext():
   m_ModelEventsCookie(0),
   m_pLoadCasesAgg(nullptr),
   m_pStagesAgg(nullptr),
   m_LoadCasesEventsCookie(0),
   m_pLoadCombinationsAgg(nullptr),
   m_LoadCombinationsEventsCookie(0),
   m_IsValidated(false)
   {
	}

   ~CLoadCombinationAnalysisContext()
   {
   }

DECLARE_REGISTRY_RESOURCEID(IDR_LOADCOMBINATIONANALYSISCONTEXT)

DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CLoadCombinationAnalysisContext)
	COM_INTERFACE_ENTRY(ILoadCombinationAnalysisContext)
	COM_INTERFACE_ENTRY(ILoadGroupResponse)
	COM_INTERFACE_ENTRY(ILiveLoadModelResponse)
	COM_INTERFACE_ENTRY(IBasicVehicularResponse)
   COM_INTERFACE_ENTRY(IGetActiveLoadGroups)
	COM_INTERFACE_ENTRY(IGetCombinationFactors)
	COM_INTERFACE_ENTRY(IAnalysisPOIs)
	COM_INTERFACE_ENTRY(IGetStressPoints)
   COM_INTERFACE_ENTRY(ILBAMModelEvents)
   COM_INTERFACE_ENTRY(ILoadCasesEvents)
   COM_INTERFACE_ENTRY(ILoadCombinationsEvents)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY_AGGREGATE(IID_ILoadCases, m_pLoadCases.p)
   COM_INTERFACE_ENTRY_AGGREGATE(IID_IStages, m_pStages.p)
   COM_INTERFACE_ENTRY_AGGREGATE(IID_ILoadCombinations, m_pLoadCombinations.p)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCombinationAnalysisContext)
CONNECTION_POINT_ENTRY(IID_ILoadCombinationAnalysisContextEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILoadCombinationAnalysisContext
public:
	STDMETHOD(Initialize)(/*[in]*/ILBAMModel* model, /*[in]*/ILoadGroupResponse* loadGroupResponse, 
                         /*[in]*/ILiveLoadModelResponse* liveLoadModelResponse, /*[in]*/IBasicVehicularResponse* basicVres,
                         /*[in]*/IAnalysisPOIs* analysisPOIs, /*[in]*/IGetStressPoints* crossSection) override;

// ILoadGroupResponse
public:
	STDMETHOD(ComputeForces)(/*[in]*/BSTR LoadGroup, /*[in]*/IIDArray* poiIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsOrientation orientation, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionResult3Ds** results) override;
   STDMETHOD(ComputeDeflections)(/*[in]*/BSTR LoadGroup, /*[in]*/IIDArray* poiIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionResult3Ds** results) override;
   STDMETHOD(ComputeReactions)(/*[in]*/BSTR LoadGroup, /*[in]*/IIDArray* supportIDs, /*[in]*/BSTR Stage,/*[in]*/ResultsSummationType summ,/*[out,retval]*/IResult3Ds** results) override;
   STDMETHOD(ComputeSupportDeflections)(/*[in]*/BSTR LoadGroup, /*[in]*/IIDArray* supportIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/IResult3Ds** results) override;
   STDMETHOD(ComputeStresses)(/*[in]*/BSTR LoadGroup, /*[in]*/IIDArray* poiIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionStressResults **results) override;

// ILiveLoadModelResponse
	STDMETHOD(ComputeForces)(/*[in]*/IIDArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                            /*[in]*/ResultsOrientation orientation, /*[in]*/ForceEffectType effect, 
                            /*[in]*/OptimizationType optimization, 
                            /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                            /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                            /*[in]*/VARIANT_BOOL computePlacement, /*[out]*/ILiveLoadModelSectionResults** results) override;

	STDMETHOD(ComputeDeflections)(/*[in]*/IIDArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                                 /*[in]*/ForceEffectType effect, 
                                 /*[in]*/OptimizationType optimization, 
                                 /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                                 /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                                 /*[in]*/VARIANT_BOOL computePlacement, /*[out]*/ILiveLoadModelSectionResults** results) override;

	STDMETHOD(ComputeReactions)(/*[in]*/IIDArray* supportIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                               /*[in]*/ForceEffectType effect, 
                               /*[in]*/OptimizationType optimization, 
                               /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                               /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                               /*[in]*/VARIANT_BOOL computePlacement, /*[out]*/ILiveLoadModelResults** results) override;

	STDMETHOD(ComputeSupportDeflections)(/*[in]*/IIDArray* supportIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                                        /*[in]*/ForceEffectType effect, 
                                        /*[in]*/OptimizationType optimization, 
                                        /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                                        /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                                        /*[in]*/VARIANT_BOOL computePlacement, /*[out]*/ILiveLoadModelResults** results) override;

	STDMETHOD(ComputeStresses)(/*[in]*/IIDArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                              /*[in]*/ForceEffectType effect, 
                              /*[in]*/OptimizationType optimization, 
                              /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                              /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                              /*[in]*/VARIANT_BOOL computePlacement, /*[out]*/ILiveLoadModelStressResults** results) override;

// IBasicVehicularResponse
	STDMETHOD(ComputeForces)(/*[in]*/IIDArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/ResultsOrientation orientation,
                            /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results) override;

	STDMETHOD(ComputeDeflections)(/*[in]*/IIDArray* poiIDs, /*[in]*/BSTR stage, 
                            /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results) override;

	STDMETHOD(ComputeReactions)(/*[in]*/IIDArray* supportIDs, /*[in]*/BSTR stage,
                               /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/IResult3Ds* *results) override;

	STDMETHOD(ComputeSupportDeflections)(/*[in]*/IIDArray* supportIDs, /*[in]*/BSTR stage,
                                        /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/IResult3Ds* *results) override;

	STDMETHOD(ComputeStresses)(/*[in]*/IIDArray* poiIDs, /*[in]*/BSTR stage,
                              /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/ISectionStressResults* *results) override;


// IGetActiveLoadGroups
   STDMETHOD(GetActiveLoadGroups)(/*[out,retval]*/IBstrArray* *loadGroups) override;

// IGetCombinationFactors
   STDMETHOD(GetPOICombinationFactors)(/*[in]*/PoiIDType POI, /*[in]*/BSTR Stage, /*[in]*/LoadCombinationType type, /*[out]*/Float64* minLoadModifier, /*[out]*/Float64* maxLoadModifier) override;
   STDMETHOD(GetSupportCombinationFactors)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR Stage, /*[in]*/LoadCombinationType type, /*[out]*/Float64* minLoadModifier, /*[out]*/Float64* maxLoadModifier) override;

// ILBAMModelEvents
   STDMETHOD(OnModelChanged)(/*[in]*/ILBAMModel* Model, ChangeType change) override;

// IAnalysisPOIs
   STDMETHOD(get_SpanPoiIncrement)( PoiIDType *pVal) override;
   STDMETHOD(put_SpanPoiIncrement)( PoiIDType newVal) override;
   STDMETHOD(get_CantileverPoiIncrement)(PoiIDType *pVal) override;
   STDMETHOD(put_CantileverPoiIncrement)( PoiIDType newVal) override;
   STDMETHOD(GetSuperstructurePois)(BSTR stage, IIDArray** poiIDs, IDblArray** poiLocations) override;
   STDMETHOD(GetPoiInfo)(BSTR stage, PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* memberLocation) override;

// IGetStressPoints
   STDMETHOD(GetStressPointsAtPOI)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out]*/IStressPoints* *leftCs,  /*[out]*/IStressPoints* *rightCs) override;

// ILoadCasesEvents
   STDMETHOD(OnLoadCasesChanged)(ILoadCase* item, ChangeType change) override;
   STDMETHOD(OnLoadCasesRenamed)(BSTR oldName, BSTR newName) override;
   STDMETHOD(OnLoadCasesAdded)(ILoadCase* item) override;
   STDMETHOD(OnLoadCasesBeforeRemove)(ILoadCase* item) override;

// ILoadCombinationsEvents
   STDMETHOD(OnLoadCombinationsChanged)(ILoadCombination* item, ChangeType change) override;
   STDMETHOD(OnLoadCombinationsRenamed)(BSTR oldName, BSTR newName) override;
   STDMETHOD(OnLoadCombinationsAdded)(ILoadCombination* item) override;
   STDMETHOD(OnLoadCombinationsBeforeRemove)(ILoadCombination* item) override;

   // virtual overrides
   void FinalRelease();
   HRESULT FinalConstruct();

private:
   // keep our cache up to date
   void Validate();
   void Invalidate();
   void ComputeSpanEnds();
   void GetLoadModifier(MemberType mbrType, MemberIDType mbrID, Float64 mbrLocation, LoadCombinationType type, Float64* minFactor, Float64* maxFactor);

   bool m_IsValidated;

   // locations of ends of spans - needed to determine factors for superstructuremembers
   std::vector<Float64> m_SpanEnds; 

   CComPtr<ILBAMModel>        m_pModel;
   DWORD                      m_ModelEventsCookie;

   // agregation objects - proxies to real interface objects
   // hold two pointers to avoid having to cast in many places
   CComAggObject<CLoadCasesAgg>*        m_pLoadCasesAgg;
   CComPtr<IUnknown>                    m_pLoadCases;      // has to be IUnknown in order for COM_INTERFACE_ENTRY_AGGREGATE to work
   DWORD                                m_LoadCasesEventsCookie;

   CComAggObject<CLoadCombinationsAgg>* m_pLoadCombinationsAgg;
   CComPtr<IUnknown>                    m_pLoadCombinations;
   DWORD                                m_LoadCombinationsEventsCookie;

   CComAggObject<CStagesAgg>*           m_pStagesAgg;
   CComPtr<IUnknown>                    m_pStages; 

   // response objects
   CComPtr<ILoadGroupResponse>      m_pLoadGroupResponse;
   CComPtr<ILiveLoadModelResponse>  m_pLiveLoadModelResponse;
   CComPtr<IBasicVehicularResponse> m_pBasicVehicularResponse;
   CComPtr<IAnalysisPOIs>           m_pAnalysisPOIs;
   CComPtr<IGetStressPoints>        m_pGetStressPoints;
};

#endif //__LOADCOMBINATIONANALYSISCONTEXT_H_
