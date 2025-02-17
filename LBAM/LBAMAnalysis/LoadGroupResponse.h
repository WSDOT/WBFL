///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright � 1999-2025  Washington State Department of Transportation
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

// LoadGroupResponse.h : Declaration of the CLoadGroupResponse

#ifndef __LoadGroupResponse_H_
#define __LoadGroupResponse_H_

#include "resource.h"       // main symbols
#include "AnalysisModel.h"
#include "AnalysisUtils.h"

#include <vector>
#include <set>
#include <map>

#include <memory>


#include "LBAMAnalysisCP.h"

#include <WBFLTools.h>

/////////////////////////////////////////////////////////////////////////////
// CLoadGroupResponse
class ATL_NO_VTABLE CLoadGroupResponse : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CLoadGroupResponse,CComObjectRootEx<CComSingleThreadModel> >,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLoadGroupResponse>,
	public ILoadGroupResponse,
   public IUnitLoadResponse,
	public IDependOnLBAM,
	public IInfluenceLineResponse,
	public IContraflexureResponse,
	public ILiveLoadNegativeMomentRegion,
	public IGetFemForLoadGroupResponse,
	public IAnalysisPOIs,
	public IGetActiveLoadGroups,
	public IGetSegmentCrossSection,
	public IGetStressPoints,
	public IGetDistributionFactors,
	public ISupportProgressMonitor,
	public ILBAMModelEvents,
	public ISuperstructureMembersEvents,
	public ISupportsEvents,
	public ISpansEvents, 
	public IPOIsEvents, 
	public IStagesEvents,
	public ILoadGroupsEvents,
	public IPointLoadsEvents,
	public IDistributedLoadsEvents,
	public ITemperatureLoadsEvents,
	public ISettlementLoadsEvents, 
	public IStrainLoadsEvents,
   public IDiagnostics
{

public:
   CLoadGroupResponse():
   m_ChangeManager(this),
   m_ForceInfluenceZeroTolerance(1.0e-10),
   m_DeflectionInfluenceZeroTolerance(1.0e-12),
   m_MinSpanPoiIncrement(10),
   m_MinCantileverPoiIncrement(2)
	{
	}

   ~CLoadGroupResponse()
   {
   }

   void FinalRelease();
   HRESULT FinalConstruct();

//DECLARE_REGISTRY_RESOURCEID(IDR_LOADGROUPRESPONSE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadGroupResponse)
	COM_INTERFACE_ENTRY(ILoadGroupResponse)
   COM_INTERFACE_ENTRY(IUnitLoadResponse)
	COM_INTERFACE_ENTRY(IDependOnLBAM)
	COM_INTERFACE_ENTRY(IGetFemForLoadGroupResponse)
	COM_INTERFACE_ENTRY(IInfluenceLineResponse)
	COM_INTERFACE_ENTRY(IContraflexureResponse)
	COM_INTERFACE_ENTRY(ILiveLoadNegativeMomentRegion)
	COM_INTERFACE_ENTRY(IAnalysisPOIs)
	COM_INTERFACE_ENTRY(IGetActiveLoadGroups)
	COM_INTERFACE_ENTRY(IGetSegmentCrossSection)
	COM_INTERFACE_ENTRY(IGetStressPoints)
	COM_INTERFACE_ENTRY(IGetDistributionFactors)
   COM_INTERFACE_ENTRY(ISupportProgressMonitor)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ILBAMModelEvents)
   COM_INTERFACE_ENTRY(ISuperstructureMembersEvents)
   COM_INTERFACE_ENTRY(ISupportsEvents)
   COM_INTERFACE_ENTRY(ISpansEvents)
   COM_INTERFACE_ENTRY(IPOIsEvents)
   COM_INTERFACE_ENTRY(IStagesEvents)
   COM_INTERFACE_ENTRY(ILoadGroupsEvents)
   COM_INTERFACE_ENTRY(IPointLoadsEvents)
   COM_INTERFACE_ENTRY(IDistributedLoadsEvents)
   COM_INTERFACE_ENTRY(ITemperatureLoadsEvents)
   COM_INTERFACE_ENTRY(ISettlementLoadsEvents)
   COM_INTERFACE_ENTRY(IStrainLoadsEvents)
   COM_INTERFACE_ENTRY(IDiagnostics)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadGroupResponse)
END_CONNECTION_POINT_MAP()

   // pure virtual function to support type-specific com exception handling
   virtual HRESULT DealWithMyExceptions() = 0;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILoadGroupResponse
public:
	STDMETHOD(get_Model)(/*[out, retval]*/ ILBAMModel* *pVal) override;
	STDMETHOD(putref_Model)(/*[in]*/ ILBAMModel* newVal) override;
	STDMETHOD(ComputeForces)(/*[in]*/BSTR LoadGroup, /*[in]*/IIDArray* poiIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsOrientation orientation, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionResult3Ds** results) override;
   STDMETHOD(ComputeDeflections)(/*[in]*/BSTR LoadGroup, /*[in]*/IIDArray* poiIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionResult3Ds** results) override;
   STDMETHOD(ComputeReactions)(/*[in]*/BSTR LoadGroup, /*[in]*/IIDArray* supportIDs, /*[in]*/BSTR Stage,/*[in]*/ResultsSummationType summ,/*[out,retval]*/IResult3Ds** results) override;
   STDMETHOD(ComputeSupportDeflections)(/*[in]*/BSTR LoadGroup, /*[in]*/IIDArray* supportIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/IResult3Ds** results) override;
   STDMETHOD(ComputeStresses)(/*[in]*/BSTR LoadGroup, /*[in]*/IIDArray* poiIDs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ,  /*[out,retval]*/ISectionStressResults **results) override;

// IDiagnostics
public:
   STDMETHOD(DumpFEMModels)() override;

// IUnitLoadReponse
public:
   STDMETHOD(ComputeForces)(/*[in]*/IIDArray* poiIDs,/*[in]*/PoiIDType ldPoiID,/*[in]*/BSTR bstrStage,/*[in]*/ForceEffectType forceEffectType,/*[in]*/ResultsOrientation orientation, /*[out,retval]*/ISectionResult3Ds** results) override;


// IInfluenceLineResponse
public:
   STDMETHOD(ComputeForceInfluenceLine)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType forceEffect, /*[in]*/ ResultsOrientation orientation, /*[out]*/IInfluenceLine** leftInfl, /*[out]*/IInfluenceLine** rightInfl) override;
   STDMETHOD(ComputeDeflectionInfluenceLine)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType deflectionEffect, /*[out]*/IInfluenceLine** leftInfl, /*[out]*/IInfluenceLine** rightInfl) override;
   STDMETHOD(ComputeReactionInfluenceLine)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType ReactionEffect, /*[out,retval]*/ IInfluenceLine** newVal) override;
   STDMETHOD(ComputeSupportDeflectionInfluenceLine)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType ReactionEffect, /*[out,retval]*/ IInfluenceLine** newVal) override;
	STDMETHOD(SetZeroTolerance)(/*[in]*/Float64 forceTolerance, /*[in]*/Float64 deflectionTolerance) override;
	STDMETHOD(GetZeroTolerance)(/*[out]*/Float64* forceTolerance, /*[out]*/Float64* deflectionTolerance) override;

// IContraflexureResponse
public:
   STDMETHOD(ComputeContraflexureLocations)(/*[in]*/BSTR stage, /*[out,retval]*/IDblArray* *locations) override;
   STDMETHOD(ComputeContraflexureResponse)(/*[in]*/BSTR stage,/*[in]*/ForceEffectType effect, /*[out,retval]*/IInfluenceLine** results) override;
   STDMETHOD(get_IsPOIInContraflexureZone)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out,retval]*/InZoneType* isInZone) override;

// ILiveLoadNegativeMomentRegion
public:
   STDMETHOD(get_IsPOIInNegativeLiveLoadMomentZone)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out,retval]*/InZoneType* isInZone) override;
   STDMETHOD(ComputeNegativeMomentRegions)(/*[in]*/BSTR stage, /*[out,retval]*/IDblArray* *locations) override;


// IGetFemForLoadGroupResponse
public:
   STDMETHOD(SaveFem2D)(/*[in]*/BSTR Stage, /*[in]*/IStructuredSave2* Save) override;

// IAnalysisPOIs
public:
   STDMETHOD(get_SpanPoiIncrement)(/*[out,retval]*/ PoiIDType *pVal) override;
   STDMETHOD(put_SpanPoiIncrement)(/*[in]*/ PoiIDType newVal) override;
   STDMETHOD(get_CantileverPoiIncrement)(/*[out,retval]*/ PoiIDType *pVal) override;
   STDMETHOD(put_CantileverPoiIncrement)(/*[in]*/ PoiIDType newVal) override;
   STDMETHOD(GetSuperstructurePois)(/*[in]*/BSTR stage, /*[out]*/IIDArray* *poiIDs, /*[out]*/IDblArray* *poiLocations) override;
   STDMETHOD(GetPoiInfo)(/*[in]*/BSTR stage, /*[in]*/PoiIDType poiID, /*[out]*/MemberType* lbamMemberType, /*[out]*/MemberIDType* memberID, /*[out]*/Float64* memberLocation) override;

// IGetActiveLoadGroups
public:
   STDMETHOD(GetActiveLoadGroups)(/*[out,retval]*/IBstrArray* *loadGroups) override;

// IGetDistributionFactors
public:
   STDMETHOD(GetPOIDistributionFactor)(/*[in]*/PoiIDType POI, /*[in]*/BSTR stage, /*[out]*/IDistributionFactor* *leftFactor, /*[out]*/IDistributionFactor* *rightFactor) override;
	STDMETHOD(GetSupportDistributionFactor)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR Stage, /*[out,retval]*/IDistributionFactor* *Factor) override;

// IGetSegmentCrossSection
public:
   STDMETHOD(GetSegmentCrossSectionAtPOI)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out]*/ISegmentCrossSection* *leftCs,  /*[out]*/ISegmentCrossSection* *rightCs) override;

// IGetStressPoints
public:
   STDMETHOD(GetStressPointsAtPOI)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out]*/IStressPoints* *leftCs,  /*[out]*/IStressPoints* *rightCs) override;

// ISupportProgressMonitor
public:
	STDMETHOD(InitializeProgressMonitor)(IProgressMonitor * newVal, LONG cookie) override;

// Events we are interested in
// ILBAMModelEvents
public:
   STDMETHOD(OnModelChanged)(ILBAMModel* me, ChangeType change) override;

// ISuperstructureMembersEvents
public:
   STDMETHOD(OnSuperstructureMembersChanged)(ISuperstructureMember* item, BSTR stage, ChangeType change) override;
   STDMETHOD(OnSuperstructureMembersAdded)(ISuperstructureMember* item, IndexType index) override;
   STDMETHOD(OnSuperstructureMembersBeforeRemove)(ISuperstructureMember* item, IndexType index) override;
	STDMETHOD(OnSuperstructureMembersMoveTo)(IndexType from, IndexType to) override;
	STDMETHOD(OnSuperstructureMembersCopyTo)(IndexType from, IndexType to) override;
	STDMETHOD(OnSuperstructureMembersReverse)() override;
	STDMETHOD(OnSuperstructureMembersOffset)() override;

// ISupportsEvents
public:
   STDMETHOD(OnSupportsChanged)(ISupport* item, BSTR stage, ChangeType change) override;
   STDMETHOD(OnSupportsAdded)(ISupport* item, PierIndexType index) override;
   STDMETHOD(OnSupportsBeforeRemove)(ISupport* item, PierIndexType index) override;
	STDMETHOD(OnSupportsMoveTo)(PierIndexType from, PierIndexType to) override;
	STDMETHOD(OnSupportsCopyTo)(PierIndexType from, PierIndexType to) override;
	STDMETHOD(OnSupportsReverse)() override;

// ISpansEvents
public:
   STDMETHOD(OnSpansChanged)(ISpan* item, BSTR stage, ChangeType change) override;
   STDMETHOD(OnSpansAdded)(ISpan* item, SpanIndexType index) override;
   STDMETHOD(OnSpansBeforeRemove)(ISpan* item, SpanIndexType index) override;
	STDMETHOD(OnSpansMoveTo)(SpanIndexType from, SpanIndexType to) override;
	STDMETHOD(OnSpansCopyTo)(SpanIndexType from, SpanIndexType to) override;
	STDMETHOD(OnSpansReverse)() override;

// IPOIsEvents
public:
   STDMETHOD(OnPOIsChanged)(IPOI* poi, ChangeType change) override;
   STDMETHOD(OnPOIsRenamed)(PoiIDType oldID, PoiIDType newID) override;
   STDMETHOD(OnPOIsAdded)(IPOI* poi) override;
   STDMETHOD(OnPOIsBeforeRemove)(IPOI* poi) override;

// IStagesEvents
public:
   STDMETHOD(OnStagesChanged)(IStage* item, ChangeType change) override;
   STDMETHOD(OnStagesAdded)(IStage* item, StageIndexType index) override;
   STDMETHOD(OnStagesBeforeRemove)(IStage* item, StageIndexType index) override;
	STDMETHOD(OnStagesMoveTo)(StageIndexType from, StageIndexType to) override;
	STDMETHOD(OnStagesCopyTo)(StageIndexType from, StageIndexType to) override;
	STDMETHOD(OnStagesReverse)() override;

// ILoadGroupsEvents
public:
   STDMETHOD(OnLoadGroupsChanged)(ILoadGroup* item, ChangeType change) override;
   STDMETHOD(OnLoadGroupsRenamed)(BSTR oldName, BSTR newName) override;
   STDMETHOD(OnLoadGroupsAdded)(ILoadGroup* item) override;
   STDMETHOD(OnLoadGroupsBeforeRemove)(ILoadGroup* item) override;

// IPointLoadsEvents
public:
   STDMETHOD(OnPointLoadsChanged)(IPointLoadItem* item) override;
   STDMETHOD(OnPointLoadsAdded)(IPointLoadItem* item) override;
   STDMETHOD(OnPointLoadsBeforeRemove)(IPointLoadItem* item) override;

// IDistributedLoadsEvents
public:
   STDMETHOD(OnDistributedLoadsChanged)(IDistributedLoadItem* item) override;
   STDMETHOD(OnDistributedLoadsAdded)(IDistributedLoadItem* item) override;
   STDMETHOD(OnDistributedLoadsBeforeRemove)(IDistributedLoadItem* item) override;

// ITemperatureLoadsEvents
public:
   STDMETHOD(OnTemperatureLoadsChanged)(ITemperatureLoadItem* item) override;
   STDMETHOD(OnTemperatureLoadsAdded)(ITemperatureLoadItem* item) override;
   STDMETHOD(OnTemperatureLoadsBeforeRemove)(ITemperatureLoadItem* item) override;

// ISettlementLoadsEvents
public:
   STDMETHOD(OnSettlementLoadsChanged)(ISettlementLoadItem* item) override;
   STDMETHOD(OnSettlementLoadsAdded)(ISettlementLoadItem* item) override;
   STDMETHOD(OnSettlementLoadsBeforeRemove)(ISettlementLoadItem* item) override;

// IStrainLoadsEvents
public:
   STDMETHOD(OnStrainLoadsChanged)(IStrainLoadItem* item) override;
   STDMETHOD(OnStrainLoadsAdded)(IStrainLoadItem* item) override;
   STDMETHOD(OnStrainLoadsBeforeRemove)(IStrainLoadItem* item) override;

private: // helper methods
   
   HRESULT CacheInfluenceLines(PoiIDType poiID, BSTR stage,ResultsOrientation orientation);

public:
   ///////////////////////////////////////////////////////////
   // CAnalysisController
   // class for keeping stage and loadgroup ordering under control
   ///////////////////////////////////////////////////////////
   class CAnalysisController: public IStageOrder, public ILoadGroupOrder
   {
   public:
      void Update(ILBAMModel* pLBAM);
      void Clear();

   public:
      // stage-related functions
      StageIndexType StageCount();
      CComBSTR Stage(StageIndexType index);
      bool GetStageIndex(BSTR stage,StageIndexType* pStageIdx);

      StageIndexType CheckedStageOrder(BSTR stage);

   public:
      // Load group-related functions
      // Provides different ways to iterate through loadgroups
      // Note that fem load case id's are incremented by 10,000 for each loadgroup. This
      // is done to allow room for load cases created for up to 10,000 temporary supports
      IndexType LoadGroupCount();
      CComBSTR LoadGroup(IndexType index);
      void GetLoadGroupInfo(BSTR LoadGroup, LoadGroupIDType* femLgId, bool* isTransient);
      void GetLoadGroupInfoByIndex(IndexType index, LoadGroupIDType* femLgId, bool* isTransient);

      // functions to determine whether loads were ever actually applied in a load group
      void SetLoadGroupAsActive(BSTR LoadGroup);
      IBstrArray* GetActiveLoadGroups();  // returns a SafeArray of BSTR's

   public:
      // functions to deal with stage/loadcase management for temporary supports
      // Reactions for temporary supports must be tracked for each lbam 
      // load group so they can be summed through stages.
      // Hence, we need an additional fem load group for every temporary support,
      // for every lbam load group
      //////////////////////////
      // total number of temporary supports in model
      SupportIndexType TemporarySupportCount();

      // gets the temporary support index for the specified support ID. returns INVALID_INDEX if not found
      SupportIndexType GetTemporarySupportIndex(SupportIDType tsID);

      // id of ith temporary support
      SupportIDType GetTemporarySupportID(SupportIndexType tempSupportIdx);

      // sequence # of erection stage for ith ts
      StageIndexType TemporarySupportErectionStageIdx(SupportIndexType tempSupportIdx);

      // sequence # of removal stage for ith ts
      StageIndexType TemporarySupportRemovalStageIndex( SupportIndexType tempSupportIdx);

      // Get loop control information for a response analysis. This comes in two
      // basic parts - first stage and load case information for primary loading, and
      // next, stages and load cases where temporary support reaction responses are.
      struct TemporarySupportLoadInfo
      {
         LoadCaseIDType m_FemLoadCaseID;
         StageIndexType m_StageIdx;
         TemporarySupportLoadInfo(LoadCaseIDType femLoadCaseID, StageIndexType stageIdx): 
            m_FemLoadCaseID(femLoadCaseID),
            m_StageIdx(stageIdx)
            {;}
      };
      using TemporarySupportLoadInfoColl = std::vector<TemporarySupportLoadInfo>;
      using TemporarySupportLoadInfoIterator = TemporarySupportLoadInfoColl::iterator;

      void GetResponseControlInfo(BSTR loadGroup, BSTR stage, ResultsSummationType summType,
                                  TemporarySupportLoadInfoColl& tempSuppportLoadInfo);

   private:
      // stage stuff
      void UpdateStageOrder(ILBAMModel* pLBAM);
      using StagesType = std::vector<CComBSTR>;
      using StagesTypeIterator = StagesType::iterator;
      StagesType m_Stages;

   private:
      // load group stuff
      void UpdateLoadGroupOrder(ILBAMModel* pLBAM);

      LoadCaseIDType m_LastFemLoadCase; // 
      struct LoadGroupInfo
      {
         LoadGroupInfo(LoadCaseIDType femLcId, bool isTransient):
         m_FemLoadCaseID(femLcId),
         m_IsTransient(isTransient),
         m_IsLoaded(false)
         {;}

         LoadCaseIDType m_FemLoadCaseID;  // load case id in fe model
         bool m_IsTransient;
         bool m_IsLoaded; // true if there were any loads applied to this loadgroup
      };
      // maps load group name to fem load group
      using LoadGroupsType = std::map< CComBSTR, LoadGroupInfo>;
      using LoadGroupsTypeIterator = LoadGroupsType::iterator;
      LoadGroupsType m_LoadGroups;

   private:
      // Temporary support stuff
      void UpdateTemporarySupportLoadings(ILBAMModel* pLBAM);

      struct TemporarySupportInfo
      {
         SupportIDType m_ID; // id of temporary support
         StageIndexType m_ErectionStageIdx; // index of erection stage
         StageIndexType m_RemovalStageIdx; // index of removal stage
         TemporarySupportInfo(SupportIDType tsId, StageIndexType erectionStageIdx, StageIndexType removalStageIdx): 
            m_ID(tsId),
            m_ErectionStageIdx(erectionStageIdx),
            m_RemovalStageIdx(removalStageIdx)
            {;}
       };
      using TemporarySupportInfoColl = std::vector<TemporarySupportInfo>;
      using TemporarySupportInfoCollIterator = TemporarySupportInfoColl::iterator;

      TemporarySupportInfoColl m_TemporarySupportInfo;

   };

   CAnalysisController    m_AnalysisController;

   // progress monitoring
   bool CheckForCancel()
   {
      if (m_pProgressMonitor)
      {
         VARIANT_BOOL cncl = VARIANT_FALSE;
         HRESULT hr = m_pProgressMonitor->get_WasCancelled(&cncl);
         ATLASSERT(SUCCEEDED(hr));
         ATLASSERT(cncl==VARIANT_FALSE);
         return cncl!=VARIANT_FALSE;
      }
      else
         return false;
   }

   CComPtr<IProgressMonitor>                m_pProgressMonitor;
   long                                     m_ProgressCookie;

   // LBAM collections kept so we can listen to their events
   DWORD                            m_ModelCookie;
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
   CComPtr<IPOIs>                   m_POIs;
   DWORD                            m_POIsCookie;
   CComPtr<ISpans>                  m_Spans;
   DWORD                            m_SpansCookie;
   CComPtr<ISuperstructureMembers>  m_SuperstructureMembers;
   DWORD                            m_SuperstructureMembersCookie;
   CComPtr<ISupports>               m_Supports;
   DWORD                           m_SupportsCookie;

protected:
   // flag. if true model is for force calculations, if false, model is for deflection calcs.
   bool                             m_ForForces;
   void ClearModels();
private:
   // our Model
   CComPtr<ILBAMModel>                  m_pLBAM;

   HRESULT Init(ILBAMModel* model);
   void ValidateModels();
   void ValidateTemporarySupportForces();

   // our list of models
   using Models = std::vector< std::shared_ptr<CAnalysisModel>>;
   using ModelsIterator = Models::iterator;
   Models m_Models;

   // influence - related private stuff
   void ValidateInfluenceCalc(BSTR stage);

   // Minimum POI increments
   PoiIDType m_MinSpanPoiIncrement;
   PoiIDType m_MinCantileverPoiIncrement;

   // data structures to keep influence lines around after they have been computed
   // base class
   struct InfluenceLineKeeper
   {
      // Data members required to manage an InfluenceLine
      PoiIDType               PoiID;
      StageIndexType          StageIdx;
      ForceEffectType         ForceEffect;
      ResultsOrientation      Orientation;

      // constructor
      InfluenceLineKeeper(PoiIDType poiID, StageIndexType stageIdx, ForceEffectType forceEffect, ResultsOrientation orientation):
      PoiID(poiID),
      StageIdx(stageIdx),
      ForceEffect(forceEffect),
      Orientation(orientation)
      {;}
 
      // < operator
      bool operator< (const InfluenceLineKeeper& other) const
      {
         if ( PoiID < other.PoiID )
            return true;

         if ( other.PoiID < PoiID )
            return false;

         if (StageIdx < other.StageIdx)
            return true;

         if (other.StageIdx < StageIdx)
            return false;

         if (ForceEffect < other.ForceEffect)
            return true;

         if (other.ForceEffect < ForceEffect)
            return false;

         if (Orientation < other.Orientation)
            return true;

         if (other.Orientation < Orientation)
            return false;

         return false;
      }
   private:
      InfluenceLineKeeper();
   };

   // dual value (left/right) model
   struct DvInfluenceLineKeeper: public InfluenceLineKeeper
   {
      // Data members required to keep an InfluenceLine
      CComPtr<IInfluenceLine> LeftInfluenceLine;
      CComPtr<IInfluenceLine> RightInfluenceLine;

      // constructor
      DvInfluenceLineKeeper(PoiIDType poiID, StageIndexType stageIdx, ForceEffectType forceEffect, ResultsOrientation orientation, 
                            IInfluenceLine* leftInfluenceLine, IInfluenceLine* rightInfluenceLine):
      InfluenceLineKeeper(poiID, stageIdx, forceEffect, orientation),
      LeftInfluenceLine(leftInfluenceLine),
      RightInfluenceLine(rightInfluenceLine)
      {;}
   };

   using DvInfluenceLineCache = std::set<DvInfluenceLineKeeper>;
   using DvInfluenceLineCacheIterator = DvInfluenceLineCache::iterator;

   // Single value model
   struct SvInfluenceLineKeeper: public InfluenceLineKeeper
   {
      // Data members required to keep an InfluenceLine
      CComPtr<IInfluenceLine> InfluenceLine;

      // constructor
      SvInfluenceLineKeeper(PoiIDType poiID, StageIndexType stageIdx, ForceEffectType forceEffect, ResultsOrientation orientation, 
                            IInfluenceLine* influenceLine):
      InfluenceLineKeeper(poiID, stageIdx, forceEffect, orientation),
      InfluenceLine(influenceLine)
      {;}
   };

   using SvInfluenceLineCache = std::set<SvInfluenceLineKeeper>;
   using SvInfluenceLineCacheIterator = SvInfluenceLineCache::iterator;


   DvInfluenceLineCache m_CachedForceInfluenceLines;
   DvInfluenceLineCache m_CachedDeflectionInfluenceLines;
   SvInfluenceLineCache m_CachedReactionInfluenceLines;
   SvInfluenceLineCache m_CachedSupportDeflectionInfluenceLines;

   Float64 m_ForceInfluenceZeroTolerance;
   Float64 m_DeflectionInfluenceZeroTolerance;

   // change manager class to help deal with events
   class ChangeManager
   {
   public:
      ChangeManager(CLoadGroupResponse* LoadGroupResponse):
         m_pLoadGroupResponse(LoadGroupResponse)
      {
         Init();
      }
      // events in
      void OnModelHosed();   // something changed to break entire model
      void OnLoadGroupChanged(BSTR loadgroup);
      void OnLoadGroupRenamed(BSTR oldName, BSTR newName);
      void OnLoadGroupAdded(BSTR loadgroup);
      void OnLoadGroupRemoved(BSTR loadgroup);
      void OnPOIChanged(PoiIDType POI);
      void OnPOIRenamed(PoiIDType oldID, PoiIDType newID);
      void OnPOIAdded(PoiIDType POI);
      void OnPOIRemoved(PoiIDType POI);
      void OnStressCalcChanged();

      void OnInfluenceLoadDataChanged();

      // events telling us that results have been updated
      void OnOrderingUpdated(); // stage and loadgroup orders were updated
      void OnModelUpdated(); // models have been updated - no build needed
      void OnInfluenceCalcUpdated(BSTR stage);
      void OnContraflexureCalcUpdated(BSTR stage);

      using IntegerList = std::set<IDType>;
      using IntegerListIterator = IntegerList::iterator;
      using NameList = std::set<_bstr_t>;
      using NameListIterator = NameList::iterator;

      // accessor functions which help to determine what to do with changes
      bool IsModelHosed();   
      bool IsStressCalcHosed();
      bool IsInfluenceCalcHosed(BSTR stage);
      bool IsContraflexureCalcHosed(BSTR stage);
      bool IsModelUpdated(); 
      bool IsOrderingUpdated();

      bool HaveLoadGroupsChanged();
      bool HavePOIsChanged();

      enum EventType {leChanged, leAdded, leRemoved};
      NameList LoadGroupsForEvent(EventType event);
      IntegerList POIsForEvent(EventType event);

   private:
      ChangeManager();
      void Init();

      // event handling functions that catch fine-grained information about changes to 
      // load groups and pois
      void AddPOIEvent(PoiIDType id, EventType event)
      {
         IntegerEventListIterator it = m_POIsEvents.find(id);
         if (it != m_POIsEvents.end())
            it->second = event;
         else
            m_POIsEvents.insert(IntegerEventList::value_type(id, event));
      }

      void AddLoadGroupEvent(BSTR loadGroup, EventType event)
      {
         NameEventListIterator it = m_LoadGroupsEvents.find(loadGroup);
         if (it != m_LoadGroupsEvents.end())
            it->second = event;
         else
            m_LoadGroupsEvents.insert(NameEventList::value_type(loadGroup, event));
      }

      CLoadGroupResponse* m_pLoadGroupResponse;
      bool m_ModelHosed;
      bool m_StressCalcHosed;
      bool m_ModelUpdated;
      bool m_IsOrderingUpdated;

      // tracking and caching of influence data 
      using InfluenceStageList = std::set<_bstr_t>;
      using InfluenceStageIterator = InfluenceStageList::iterator;
      InfluenceStageList m_UpdatedInfluenceLoadStages;

      using NameEventList = std::map< _bstr_t, EventType >;
      using NameEventListIterator = NameEventList::iterator;
      NameEventList m_LoadGroupsEvents;

      using IntegerEventList = std::map<IDType, EventType>;
      using IntegerEventListIterator = IntegerEventList::iterator;
      IntegerEventList m_POIsEvents;
   };

   friend ChangeManager;
   ChangeManager m_ChangeManager;
};

#endif //__LoadGroupResponse_H_
