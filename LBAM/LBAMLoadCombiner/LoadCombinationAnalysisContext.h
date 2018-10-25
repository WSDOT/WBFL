///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
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
   m_pLoadCasesAgg(NULL),
   m_pStagesAgg(NULL),
   m_LoadCasesEventsCookie(0),
   m_pLoadCombinationsAgg(NULL),
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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILoadCombinationAnalysisContext
public:
	STDMETHOD(Initialize)(/*[in]*/ILBAMModel* model, /*[in]*/ILoadGroupResponse* loadGroupResponse, 
                         /*[in]*/ILiveLoadModelResponse* liveLoadModelResponse, /*[in]*/IBasicVehicularResponse* basicVres,
                         /*[in]*/IAnalysisPOIs* analysisPOIs, /*[in]*/IGetStressPoints* crossSection);

// ILoadGroupResponse
public:
	STDMETHOD(ComputeForces)(/*[in]*/BSTR LoadGroup, /*[in]*/ILongArray* poiIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsOrientation orientation, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionResult3Ds** results);
   STDMETHOD(ComputeDeflections)(/*[in]*/BSTR LoadGroup, /*[in]*/ILongArray* poiIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionResult3Ds** results);
   STDMETHOD(ComputeReactions)(/*[in]*/BSTR LoadGroup, /*[in]*/ILongArray* supportIDs, /*[in]*/BSTR Stage,/*[in]*/ResultsSummationType summ,/*[out,retval]*/IResult3Ds** results);
   STDMETHOD(ComputeSupportDeflections)(/*[in]*/BSTR LoadGroup, /*[in]*/ILongArray* supportIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/IResult3Ds** results);
   STDMETHOD(ComputeStresses)(/*[in]*/BSTR LoadGroup, /*[in]*/ILongArray* poiIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionStressResults **results);

// ILiveLoadModelResponse
	STDMETHOD(ComputeForces)(/*[in]*/ILongArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                            /*[in]*/ResultsOrientation orientation, /*[in]*/ForceEffectType effect, 
                            /*[in]*/OptimizationType optimization, 
                            /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                            /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                            /*[in]*/VARIANT_BOOL computePlacement, /*[out]*/ILiveLoadModelSectionResults** results);

	STDMETHOD(ComputeDeflections)(/*[in]*/ILongArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                                 /*[in]*/ForceEffectType effect, 
                                 /*[in]*/OptimizationType optimization, 
                                 /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                                 /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                                 /*[in]*/VARIANT_BOOL computePlacement, /*[out]*/ILiveLoadModelSectionResults** results);

	STDMETHOD(ComputeReactions)(/*[in]*/ILongArray* supportIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                               /*[in]*/ForceEffectType effect, 
                               /*[in]*/OptimizationType optimization, 
                               /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                               /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                               /*[in]*/VARIANT_BOOL computePlacement, /*[out]*/ILiveLoadModelResults** results);

	STDMETHOD(ComputeSupportDeflections)(/*[in]*/ILongArray* supportIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                                        /*[in]*/ForceEffectType effect, 
                                        /*[in]*/OptimizationType optimization, 
                                        /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                                        /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                                        /*[in]*/VARIANT_BOOL computePlacement, /*[out]*/ILiveLoadModelResults** results);

	STDMETHOD(ComputeStresses)(/*[in]*/ILongArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type,  
                              /*[in]*/ForceEffectType effect, 
                              /*[in]*/OptimizationType optimization, 
                              /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                              /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                              /*[in]*/VARIANT_BOOL computePlacement, /*[out]*/ILiveLoadModelStressResults** results);

// IBasicVehicularResponse
	STDMETHOD(ComputeForces)(/*[in]*/ILongArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/ResultsOrientation orientation,
                            /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results);

	STDMETHOD(ComputeDeflections)(/*[in]*/ILongArray* poiIDs, /*[in]*/BSTR stage, 
                            /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results);

	STDMETHOD(ComputeReactions)(/*[in]*/ILongArray* supportIDs, /*[in]*/BSTR stage,
                               /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/IResult3Ds* *results);

	STDMETHOD(ComputeSupportDeflections)(/*[in]*/ILongArray* supportIDs, /*[in]*/BSTR stage,
                                        /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/IResult3Ds* *results);

	STDMETHOD(ComputeStresses)(/*[in]*/ILongArray* poiIDs, /*[in]*/BSTR stage,
                              /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/ISectionStressResults* *results);


// IGetActiveLoadGroups
   STDMETHOD(GetActiveLoadGroups)(/*[out,retval]*/IBstrArray* *loadGroups);

// IGetCombinationFactors
   STDMETHOD(GetPOICombinationFactors)(/*[in]*/PoiIDType POI, /*[in]*/BSTR Stage, /*[in]*/LoadCombinationType type, /*[out]*/Float64* minLoadModifier, /*[out]*/Float64* maxLoadModifier);
   STDMETHOD(GetSupportCombinationFactors)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR Stage, /*[in]*/LoadCombinationType type, /*[out]*/Float64* minLoadModifier, /*[out]*/Float64* maxLoadModifier);

// ILBAMModelEvents
   STDMETHOD(OnModelChanged)(/*[in]*/ILBAMModel* Model, ChangeType change);

// IAnalysisPOIs
   STDMETHOD(get_SpanPoiIncrement)( PoiIDType *pVal);
   STDMETHOD(put_SpanPoiIncrement)( PoiIDType newVal);
   STDMETHOD(get_CantileverPoiIncrement)(PoiIDType *pVal);
   STDMETHOD(put_CantileverPoiIncrement)( PoiIDType newVal);
   STDMETHOD(GetSuperstructurePois)(BSTR stage, ILongArray** poiIDs, IDblArray** poiLocations);
   STDMETHOD(GetPoiInfo)(BSTR stage, PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* memberLocation);

// IGetStressPoints
   STDMETHOD(GetStressPointsAtPOI)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out]*/IStressPoints* *leftCs,  /*[out]*/IStressPoints* *rightCs);

// ILoadCasesEvents
   STDMETHOD(OnLoadCasesChanged)(ILoadCase* item, ChangeType change);
   STDMETHOD(OnLoadCasesRenamed)(BSTR oldName, BSTR newName);
   STDMETHOD(OnLoadCasesAdded)(ILoadCase* item);
   STDMETHOD(OnLoadCasesBeforeRemove)(ILoadCase* item);

// ILoadCombinationsEvents
   STDMETHOD(OnLoadCombinationsChanged)(ILoadCombination* item, ChangeType change);
   STDMETHOD(OnLoadCombinationsRenamed)(BSTR oldName, BSTR newName);
   STDMETHOD(OnLoadCombinationsAdded)(ILoadCombination* item);
   STDMETHOD(OnLoadCombinationsBeforeRemove)(ILoadCombination* item);

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
