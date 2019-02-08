///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2019  Washington State Department of Transportation
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

// Model.h : Declaration of the CModel

#ifndef __MODEL_H_
#define __MODEL_H_

#include "resource.h"       // main symbols
#include "LBAMCP.h"

#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CModel
class ATL_NO_VTABLE CModel : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CModel,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CModel, &CLSID_LBAMModel>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CModel>,
	public ILBAMModel,
   public IPersistImpl<CModel>,
	public IStructuredStorage2,
	public ISuperstructureMembersEvents,
	public ISupportsEvents,
	public ISpansEvents,
	public IPOIsEvents, 
	public IStagesEvents, 
	public ILoadGroupsEvents,
	public ILoadCasesEvents, 
	public ILoadCombinationsEvents,
	public IPointLoadsEvents, 
	public IDistributedLoadsEvents,
	public ITemperatureLoadsEvents,
	public ISettlementLoadsEvents,
	public IStrainLoadsEvents,
	public ILiveLoadEvents, 
	public IDistributionFactorsEvents,
   public IObjectSafetyImpl<CModel,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDLBAMModelEvents< CModel >
{
public:
   CModel():
   m_LocationCache(this)
	{
	}

   ~CModel()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_MODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CModel)
	COM_INTERFACE_ENTRY(ILBAMModel)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISuperstructureMembersEvents)
   COM_INTERFACE_ENTRY(ISupportsEvents)
   COM_INTERFACE_ENTRY(ISpansEvents)
   COM_INTERFACE_ENTRY(IPOIsEvents)
   COM_INTERFACE_ENTRY(IStagesEvents)
   COM_INTERFACE_ENTRY(ILoadGroupsEvents)
   COM_INTERFACE_ENTRY(ILoadCasesEvents)
   COM_INTERFACE_ENTRY(ILoadCombinationsEvents)
   COM_INTERFACE_ENTRY(IPointLoadsEvents)
   COM_INTERFACE_ENTRY(IDistributedLoadsEvents)
   COM_INTERFACE_ENTRY(ITemperatureLoadsEvents)
   COM_INTERFACE_ENTRY(ISettlementLoadsEvents)
   COM_INTERFACE_ENTRY(IStrainLoadsEvents)
   COM_INTERFACE_ENTRY(ILiveLoadEvents)
   COM_INTERFACE_ENTRY(IDistributionFactorsEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CModel)
CONNECTION_POINT_ENTRY(IID_ILBAMModelEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILBAMModel
public:
   STDMETHOD(get_Name)(BSTR* name) override;
   STDMETHOD(put_Name)(BSTR name) override;

	STDMETHOD(get_DistributionFactors)(/*[out, retval]*/ IDistributionFactors* *pVal) override;
	STDMETHOD(get_LiveLoad)(/*[out, retval]*/ ILiveLoad* *pVal) override;
   STDMETHOD(ConvertSpanToSuperstructureLocation)(MemberIDType spanMbrID,Float64 spanLoc,MemberIDType* pSSMbrID,Float64* pSSMbrLoc) override;
	STDMETHOD(ComputeLocation)(/*[in]*/MemberIDType mbrID, /*[in]*/MemberType mbrType, /*[in]*/Float64 mbrLocation, /*[out]*/Float64* Xloc, /*[out]*/Float64* Yloc) override;
	STDMETHOD(get_LoadGroups)(/*[out, retval]*/ ILoadGroups* *pVal) override;
	STDMETHOD(get_LoadCases)(/*[out, retval]*/ ILoadCases* *pVal) override;
	STDMETHOD(get_LoadCombinations)(/*[out, retval]*/ ILoadCombinations* *pVal) override;
	STDMETHOD(get_StrainLoads)(/*[out, retval]*/ IStrainLoads* *pVal) override;
	STDMETHOD(get_SettlementLoads)(/*[out, retval]*/ ISettlementLoads* *pVal) override;
	STDMETHOD(get_TemperatureLoads)(/*[out, retval]*/ ITemperatureLoads* *pVal) override;
	STDMETHOD(get_DistributedLoads)(/*[out, retval]*/ IDistributedLoads* *pVal) override;
	STDMETHOD(get_PointLoads)(/*[out, retval]*/ IPointLoads* *pVal) override;
	STDMETHOD(LeftSpan)(/*[in]*/SpanIndexType relPosition, /*[out,retval]*/ISpan**) override;
	STDMETHOD(RightSpan)(/*[in]*/SpanIndexType relPosition, /*[out,retval]*/ISpan**) override;
	STDMETHOD(LeftSupport)(/*[in]*/SupportIndexType relPosition, /*[out,retval]*/ISupport**) override;
	STDMETHOD(RightSupport)(/*[in]*/SupportIndexType relPosition, /*[out,retval]*/ISupport**) override;
	STDMETHOD(RemoveStage)(BSTR stage) override;
	STDMETHOD(get_Stages)(/*[out, retval]*/ IStages* *pVal) override;
	STDMETHOD(get_POIs)(/*[out, retval]*/ IPOIs* *pVal) override;
	STDMETHOD(Clear)() override;
   STDMETHOD(get_TemporarySupports)(ITemporarySupports** ppVal) override;
	STDMETHOD(get_Spans)(/*[out, retval]*/ ISpans* *pVal) override;
	STDMETHOD(get_Supports)(/*[out, retval]*/ ISupports* *pVal) override;
	STDMETHOD(Clone)(/*[out,retval]*/ ILBAMModel** clone) override;
	STDMETHOD(get_SuperstructureMembers)(/*[out, retval]*/ ISuperstructureMembers* *pVal) override;
   STDMETHOD(put_ForceEquilibriumTolerance)(/*[in]*/Float64 tol);
   STDMETHOD(get_ForceEquilibriumTolerance)(/*[out, retval]*/Float64* tol);
   STDMETHOD(put_MomentEquilibriumTolerance)(/*[in]*/Float64 tol);
   STDMETHOD(get_MomentEquilibriumTolerance)(/*[out, retval]*/Float64* tol);
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pVal) override;

   // The following methods were in the ILBAMModel interface at one time. They were
   // removed because they present a nightmare for event handling.
   // They are kept here though to facilitate initialization of this object
protected:
	STDMETHOD(putref_DistributionFactors)(/*[in]*/ IDistributionFactors* newVal);
	STDMETHOD(putref_LiveLoad)(/*[in]*/ ILiveLoad* newVal);
	STDMETHOD(putref_LoadGroups)(/*[in]*/ ILoadGroups* newVal);
	STDMETHOD(putref_LoadCases)(/*[in]*/ ILoadCases* newVal);
	STDMETHOD(putref_LoadCombinations)(/*[in]*/ ILoadCombinations* newVal);
	STDMETHOD(putref_StrainLoads)(/*[in]*/ IStrainLoads* newVal);
	STDMETHOD(putref_TemperatureLoads)(/*[in]*/ ITemperatureLoads* newVal);
	STDMETHOD(putref_SettlementLoads)(/*[in]*/ ISettlementLoads* newVal);
	STDMETHOD(putref_DistributedLoads)(/*[in]*/ IDistributedLoads* newVal);
	STDMETHOD(putref_PointLoads)(/*[in]*/ IPointLoads* newVal);
	STDMETHOD(putref_Stages)(/*[in]*/ IStages* newVal);
	STDMETHOD(putref_POIs)(/*[in]*/ IPOIs* newVal);
	STDMETHOD(putref_Spans)(/*[in]*/ ISpans* newVal);
	STDMETHOD(putref_Supports)(/*[in]*/ ISupports* newVal);
	STDMETHOD(putref_SuperstructureMembers)(/*[in]*/ ISuperstructureMembers* newVal);

public:
   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// ISuperstructureMembersEvents
   STDMETHOD(OnSuperstructureMembersChanged)(ISuperstructureMember* item, BSTR stage, ChangeType change) override;
   STDMETHOD(OnSuperstructureMembersAdded)(ISuperstructureMember* item, CollectionIndexType index) override;
   STDMETHOD(OnSuperstructureMembersBeforeRemove)(ISuperstructureMember* item, CollectionIndexType index) override;
	STDMETHOD(OnSuperstructureMembersMoveTo)(CollectionIndexType from, CollectionIndexType to) override;
	STDMETHOD(OnSuperstructureMembersCopyTo)(CollectionIndexType from, CollectionIndexType to) override;
	STDMETHOD(OnSuperstructureMembersReverse)() override;
	STDMETHOD(OnSuperstructureMembersOffset)() override;

// ISupportsEvents
   STDMETHOD(OnSupportsChanged)(ISupport* item, BSTR stage, ChangeType change) override;
   STDMETHOD(OnSupportsAdded)(ISupport* item, SupportIndexType index) override;
   STDMETHOD(OnSupportsBeforeRemove)(ISupport* item, SupportIndexType index) override;
	STDMETHOD(OnSupportsMoveTo)(SupportIndexType from, SupportIndexType to) override;
	STDMETHOD(OnSupportsCopyTo)(SupportIndexType from, SupportIndexType to) override;
	STDMETHOD(OnSupportsReverse)() override;

// ISpansEvents
   STDMETHOD(OnSpansChanged)(ISpan* item, BSTR stage, ChangeType change) override;
   STDMETHOD(OnSpansAdded)(ISpan* item, SpanIndexType index) override;
   STDMETHOD(OnSpansBeforeRemove)(ISpan* item, SpanIndexType index) override;
	STDMETHOD(OnSpansMoveTo)(SpanIndexType from, SpanIndexType to) override;
	STDMETHOD(OnSpansCopyTo)(SpanIndexType from, SpanIndexType to) override;
	STDMETHOD(OnSpansReverse)() override;

// IPOIsEvents
   STDMETHOD(OnPOIsChanged)(IPOI* poi, ChangeType change) override;
   STDMETHOD(OnPOIsRenamed)(PoiIDType oldID, PoiIDType newID) override;
   STDMETHOD(OnPOIsAdded)(IPOI* poi) override;
   STDMETHOD(OnPOIsBeforeRemove)(IPOI* poi) override;

// IStagesEvents
   STDMETHOD(OnStagesChanged)(IStage* item, ChangeType change) override;
   STDMETHOD(OnStagesAdded)(IStage* item, StageIndexType relPos) override;
   STDMETHOD(OnStagesBeforeRemove)(IStage* item, StageIndexType relPos) override;
	STDMETHOD(OnStagesMoveTo)(StageIndexType from, StageIndexType to) override;
	STDMETHOD(OnStagesCopyTo)(StageIndexType from, StageIndexType to) override;
	STDMETHOD(OnStagesReverse)() override;

// ILoadGroupsEvents
   STDMETHOD(OnLoadGroupsChanged)(ILoadGroup* item, ChangeType change) override;
   STDMETHOD(OnLoadGroupsRenamed)(BSTR oldName, BSTR newName) override;
   STDMETHOD(OnLoadGroupsAdded)(ILoadGroup* item) override;
   STDMETHOD(OnLoadGroupsBeforeRemove)(ILoadGroup* item) override;

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

// IPointLoadsEvents
   STDMETHOD(OnPointLoadsChanged)(IPointLoadItem* item) override;
   STDMETHOD(OnPointLoadsAdded)(IPointLoadItem* item) override;
   STDMETHOD(OnPointLoadsBeforeRemove)(IPointLoadItem* item) override;

// IDistributedLoadsEvents
   STDMETHOD(OnDistributedLoadsChanged)(IDistributedLoadItem* item) override;
   STDMETHOD(OnDistributedLoadsAdded)(IDistributedLoadItem* item) override;
   STDMETHOD(OnDistributedLoadsBeforeRemove)(IDistributedLoadItem* item) override;

// ITemperatureLoadsEvents
   STDMETHOD(OnTemperatureLoadsChanged)(ITemperatureLoadItem* item) override;
   STDMETHOD(OnTemperatureLoadsAdded)(ITemperatureLoadItem* item) override;
   STDMETHOD(OnTemperatureLoadsBeforeRemove)(ITemperatureLoadItem* item) override;

// ISettlementLoadsEvents
   STDMETHOD(OnSettlementLoadsChanged)(ISettlementLoadItem* item) override;
   STDMETHOD(OnSettlementLoadsAdded)(ISettlementLoadItem* item) override;
   STDMETHOD(OnSettlementLoadsBeforeRemove)(ISettlementLoadItem* item) override;

// IStrainLoadsEvents
   STDMETHOD(OnStrainLoadsChanged)(IStrainLoadItem* item) override;
   STDMETHOD(OnStrainLoadsAdded)(IStrainLoadItem* item) override;
   STDMETHOD(OnStrainLoadsBeforeRemove)(IStrainLoadItem* item) override;

// ILiveLoadEvents
   STDMETHOD(OnLiveLoadChanged)(ILiveLoad* load, LiveLoadModelType lltype) override;

// IDistributionFactorsEvents
   STDMETHOD(OnDistributionFactorsChanged)() override;
   STDMETHOD(OnDistributionFactorsAdded)(IDistributionFactorSegment* item, CollectionIndexType idx) override;
   STDMETHOD(OnDistributionFactorsBeforeRemove)(IDistributionFactorSegment* item, CollectionIndexType idx) override;
	STDMETHOD(OnDistributionFactorsMoveTo)(CollectionIndexType from, CollectionIndexType to) override;
	STDMETHOD(OnDistributionFactorsCopyTo)(CollectionIndexType from, CollectionIndexType to) override;
	STDMETHOD(OnDistributionFactorsReverse)() override;


protected:
   CComBSTR                         m_Name;
   CComPtr<IStrainLoads>            m_StrainLoads;
   DWORD                            m_StrainLoadsCookie;
   CComPtr<ISettlementLoads>        m_SettlementLoads;
   DWORD                            m_SettlementLoadsCookie;
   CComPtr<ITemperatureLoads>       m_TemperatureLoads;
   DWORD                            m_TemperatureLoadsCookie;
   CComPtr<IDistributedLoads>       m_DistributedLoads;
   DWORD                            m_DistributedLoadsCookie;
   CComPtr<IPointLoads>             m_PointLoads;
   DWORD                            m_PointLoadsCookie;
   CComPtr<IStages>                 m_Stages;
   DWORD                            m_StagesCookie;
   CComPtr<ILoadGroups>             m_LoadGroups;
   DWORD                            m_LoadGroupsCookie;
   CComPtr<ILoadCases>              m_LoadCases;
   DWORD                            m_LoadCasesCookie;
   CComPtr<ILoadCombinations>       m_LoadCombinations;
   DWORD                            m_LoadCombinationsCookie;
   CComPtr<IPOIs>                   m_POIs;
   DWORD                            m_POIsCookie;
   CComPtr<ISpans>                  m_Spans;
   DWORD                            m_SpansCookie;
   CComPtr<ISuperstructureMembers>  m_SuperstructureMembers;
   DWORD                            m_SuperstructureMembersCookie;
   CComPtr<ISupports>               m_Supports;
   DWORD                            m_SupportsCookie;
   CComPtr<ILiveLoad>               m_LiveLoad;
   DWORD                            m_LiveLoadCookie;
   CComPtr<IDistributionFactors>    m_DistributionFactors;
   DWORD                            m_DistributionFactorsCookie;

   Float64 m_ForceEquilibriumTolerance;
   Float64 m_MomentEquilibriumTolerance;

private:
   // local private members
	VOID FireModelChanged(ChangeType change); 

   // cached values for location computation
   class LocationCache
   {
   public:
      LocationCache(CModel* pModel);
      void Invalidate();
      void ComputeLocation(MemberIDType mbrID, MemberType mbrType, Float64 mbrLocation, Float64 *Xloc, Float64 *Yloc);
      void ConvertSpanToSuperstructureLocation(MemberIDType spanMbrID,Float64 spanLoc,MemberIDType* pSSMbrID,Float64* pSSMbrLoc);
   private:
      void Validate();
      LocationCache();
      bool m_LocationUpdated;
      std::vector<Float64> m_SpanEnds;
      std::vector<Float64> m_SsmEnds;
      CModel* m_pModel;
   };

   LocationCache m_LocationCache;
};

#endif //__MODEL_H_
