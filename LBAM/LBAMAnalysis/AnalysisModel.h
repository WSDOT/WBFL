///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2016  Washington State Department of Transportation
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

// AnalysisModel.h: interface for the CAnalysisModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALYSISMODEL_H__A1C2BAF3_A20B_11D5_B05D_00105A9AF985__INCLUDED_)
#define AFX_ANALYSISMODEL_H__A1C2BAF3_A20B_11D5_B05D_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WBFLLBAMAnalysis.h"
#include "AnalysisUtils.h"
#include "WBFLLBAM.h"
#include "LBAMUtils.h"

#include <WBFLFem2d.h>

#include <WBFLTools.h>

#include <set>
#include <map>
#include <vector>

#include "InfluenceLine.h"
#include "AMUtils.h"


struct ILBAMModel;
class SortedPoiMapTracker;

class CAnalysisModel  
{
///////////////////////////////////////////////////////////////////////////
//
// This class is the main engine for the superstructure. It performs nearly all
// of the mapping between the LBAM and the fem model.
//
// BASIC RULES (if you break these, you break lots of things):
//
//  1. Fem Members along the superstructure are numbered contiguously from 0-n
//  2. Joints are numbered to optimize solution
//  3. LBAM LoadGroups map to fem load cases 0-n
//  4. Influence lines and other special loads are given negative fem load case id's (see top of .cpp file)
//  5. The left-most support is located at global X=0.0
//
///////////////////////////////////////////////////////////////////////////
   friend SortedPoiMapTracker;

public:
	CAnalysisModel(ILBAMModel* pModel, BSTR stage, IStageOrder* pStageOrder, ILoadGroupOrder* pLoadGroupOrder,
                  PoiIDType minSpanPoiIncr, PoiIDType minCantileverPoiIncr, bool forForce);
	virtual ~CAnalysisModel();

   void BuildModel(BSTR bstrName);
   void DumpFEMModel();

   void GetForce(LoadGroupIDType loadGroupID, PoiIDType poiId, ResultsOrientation orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight,  Float64* fyRight, Float64* mzRight);
   void GetDeflection(LoadGroupIDType loadGroupID, PoiIDType poiId, Float64* dxLeft, Float64* dyLeft, Float64* rzLeft, Float64* dxRight,  Float64* dyRight, Float64* rzRight);
   void GetReaction(LoadGroupIDType loadGroupID, SupportIDType suptId, Float64* Fx, Float64* Fy, Float64* Mz);
   void GetSupportDeflection(LoadGroupIDType loadGroupID, SupportIDType suptId, Float64* Dx, Float64* Dy, Float64* Rz);
   void GetStress(LoadGroupIDType loadGroupID, PoiIDType poiId, std::vector<Float64>& sLeft, std::vector<Float64>& sRight, bool* wasComputed);

   void ClearLoads();
   void GenerateLoads();

   void ClearPOIs();
   void GeneratePOIs();
   void GenerateUserDefinedPOIs();
   void GenerateInternalPOIs();
   void GenerateInternalPOIsAtSpans();
   void GenerateInternalPOIsAtCantilevers();
   void GenerateInternalPOIsAtSuperstructureMembers();
   void GenerateInternalPOIsAtTemporarySupports();

   void GetUnitLoadResponse(PoiIDType poiID,PoiIDType loadPoiID, ForceEffectType forceEffect, ResultsOrientation orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight,  Float64* fyRight, Float64* mzRight);

   // return reaction force between temporary support and superstructure.
   void GetTemporarySupportReaction(LoadGroupIDType loadGroupID, SupportIDType tempSupportID, Float64* Fx, Float64* Fy, Float64* Mz);
   // apply temporary support reaction force to model for this stage
   void ApplyTemporarySupportReaction(LoadCaseIDType tempSupportLoadCaseID, SupportIDType tempSupportID, Float64 fx, Float64 fy, Float64 mz);

   // influence-related functions
   void ClearInfluenceLoads();
   void GenerateInfluenceLoads();
   void GetInfluenceLines(PoiIDType poiID,
                          ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, Float64 deflZeroTolerance, 
                          IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                          IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                          IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                          IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                          IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                          IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl);
   void GetReactionInfluenceLine(SupportIDType supportID, ForceEffectType ReactionEffect, CInfluenceLine* pInfl);
   void GetSupportDeflectionInfluenceLine(SupportIDType supportID, ForceEffectType ReactionEffect, CInfluenceLine* pInfl);

   // contraflexure
   void ClearContraflexureLoads();
   void GenerateContraflexureLoads();
   void ComputeContraflexurePOIs();
   void GetContraflexureLocations(IDblArray* *locations);
   void GetContraflexureForce(ForceEffectType effect, CInfluenceLine* results);
   void IsPOIInContraflexureZone(PoiIDType poiID, InZoneType* isInZone);

   void IsPOIInNegativeLiveLoadMomentZone(PoiIDType poiID, InZoneType* isInZone);
   void GetNegativeMomentRegions(IDblArray* *locations);

   bool GetSuperstructureMemberForGlobalX(Float64 xLoc, MemberIDType* ssmId, Float64* ssmXLoc);

   // save fem model to persistence
   void SaveModel(IStructuredSave2* Save);


// IAnalysisPOIs
   HRESULT get_SpanPoiIncrement( PoiIDType *pVal);
   HRESULT put_SpanPoiIncrement( PoiIDType newVal);
   HRESULT get_CantileverPoiIncrement(PoiIDType *pVal);
   HRESULT put_CantileverPoiIncrement( PoiIDType newVal);
   HRESULT GetSuperstructurePois(IIDArray* *poiIDs, IDblArray* *poiLocations);
   HRESULT GetPoiInfo(PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* memberLoc);

// IGetSegmentCrossSection
   void GetSegmentCrossSectionAtPOI(PoiIDType poiID, ISegmentCrossSection* *leftCs, ISegmentCrossSection* *rightCs);

// IGetStressPoints
   void GetStressPointsAtPOI(PoiIDType poiID, IStressPoints* *leftCs, IStressPoints* *rightCs);

// IGetDistributionFactors
   void GetPOIDistributionFactor(PoiIDType POI, IDistributionFactor* *leftFactor, IDistributionFactor* *rightFactor);
   void GetSupportDistributionFactor(SupportIndexType supportIdx, IDistributionFactor **Factor);

private:
	CAnalysisModel();

   ILBAMModel*      m_pLBAMModel;
   CComBSTR         m_Stage;
   IStageOrder*     m_pStageOrder;
   ILoadGroupOrder* m_pLoadGroupOrder;
   bool             m_bForcesModel;    // model is either for force or deflection calculations

   CComPtr<IFem2dModel> m_pFem2d;
   Float64 m_LayoutTolerance;
   Float64 m_PoiTolerance;


   // superstructure layout information. start of spans is at 0.0 which is where first support is
   Float64              m_TotalLength;
   Float64              m_LeftOverhang;
   Float64              m_RightOverhang;
   std::vector<Float64> m_SpanEnds;                   // locations of ends of spans
   std::vector<Float64> m_SuperstructureMemberEnds;   // locations of ends of SSM's
   std::set<Float64>    m_AllSpanEnds;                // locations of ends of all spans - including those created by temporary supports

   // fem model layout information - used to map between the LBAM and Fem Models
   // elements
   struct ElementLayout
   {
      MemberIDType           m_FemMemberID; // id of element in fem
      CComPtr<ISegmentCrossSection> m_XSect;

      ElementLayout():
         m_FemMemberID(-1) 
         {;}
      ElementLayout(MemberIDType id, ISegmentCrossSection* pxs):
         m_FemMemberID(id),
         m_XSect(pxs)
         {;}
   };
   typedef std::vector<ElementLayout>       ElementLayoutVec;
   typedef ElementLayoutVec::iterator       ElementLayoutVecIterator;
   typedef std::vector<ElementLayoutVec>    ElementLayoutGroup;
   typedef ElementLayoutGroup::iterator     ElementLayoutGroupIterator;
   typedef std::map<MemberIDType, ElementLayoutVec> ElementLayoutMap;
   typedef ElementLayoutMap::iterator       ElementLayoutMapIterator;

   ElementLayoutGroup   m_SpanElements;
   ElementLayoutGroup   m_SuperstructureMemberElements;
   ElementLayoutGroup   m_SupportElements;
   ElementLayoutMap     m_TemporarySupportElements;

   // nodes and supports
   typedef std::vector<IDType>         IdList;
   typedef IdList::iterator            IdListIterator;
   typedef std::map<IDType, IDType>    IdMap;
   typedef IdMap::iterator             IdMapIterator;
   typedef std::set<IDType>            IdSet;
   typedef IdSet::iterator             IdSetIterator;

   IdList    m_SupportNodes;             // nodes at bottoms of supports
   IdMap     m_TemporarySupportNodes;    // nodes at bottoms of temporary supports
   IdMap     m_TemporarySupportNodeLocs; // nodes generated for temporary supports belonging in another stage

   IdSet     m_TemporarySupportIDs; // lists all temporary supports for all stages. Used for efficiency

   // POI information - a sorted vector
   bool               m_IsPoiMapUpdated;
   PoiMapCollection   m_PoiMap;
   // sorted version of the above collection, but only pois on the superstructure sorted by location
   typedef std::auto_ptr<SortedPoiMapTracker> PoiTrackerHolder;
   PoiTrackerHolder m_pPoiTracker;
   // most recently generated fem poi id. this is used in mapping between lbam and fem pois
   PoiIDType m_LastFemPoiID;
   // Most recently generated internal poi id.
   PoiIDType m_LastInternalPoiID;

   // Minimum POI increments
   PoiIDType m_MinSpanPoiIncrement;
   PoiIDType m_MinCantileverPoiIncrement;


   InfluenceLoadSet m_InfluenceLoadSet;

   // influence-related private functions
   void GenerateInfluenceLoadLocations();
   void ComputeInfluenceLoadLocation(PoiIDType poiID,MemberType lbmbrType, MemberIDType lbmbrID, Float64 lbmbrLoc);

   // cached data for contraflexure computation
   CComPtr<IDblArray> m_ContraflexureLocations;
   // pois where contraflexure locations are
   std::vector<PoiIDType> m_ContraflexurePOIs;

   void GenerateContraflexurePOIs();
   void ComputeContraflexureLocations();

   // member functions for laying out and generating model
   void LayoutSuperstructure(ISuperstructureMembers* pmembers, ISpans* pspans, ISupports* pSupports, SuperNodeLocs* node_locs);
   void LayoutSpanNodes(ISuperstructureMembers* pmembers, ISpans* pspans, ISupports* pSupports, SuperNodeLocs* node_locs);
   void LayoutSuperstructureMemberNodes(ISuperstructureMembers* pMembers, SuperNodeLocs* pSuperNodeLocs);
   void PlaceHinges(ISuperstructureMembers* pMembers, Float64 LeftOverhang, SuperNodeLocs* node_locs);
   bool IsMemberEndReleased(ISuperstructureMember* pMember, Side side, MemberReleaseType releaseType);

   bool IsTempSupportInStage(ITemporarySupport* temporarySupport);
   bool IsTempSupportInModel(SupportIDType tmpSupportID); // call only after fem model is generated
   void LayoutSupport(SupportIDType supportIdx, ISupports* supports, SubNodeLocs* pNodeLocs);
   void LayoutSupportNodes(SupportIDType supportIdx, ISupports* supports, SubNodeLocs* pNodeLocs);

   void LayoutTemporarySupport(SpanIndexType spanIdx, Float64 tempSupportLocation, ITemporarySupport* pSupport, SubNodeLocs* pNodeLocs);
   void LayoutTemporarySupportNodes(SpanIndexType spanIdx, Float64 tempSupportLocation, ITemporarySupport* pSupport, SubNodeLocs* pNodeLocs);

   void GenerateFemModel(SuperNodeLocs* pNodeLocs);
   void GenerateSuperstructureFemModel(SuperNodeLocs* pNodeLocs,  IFem2dJointCollection*  pJoints, IFem2dMemberCollection* pMembers, MemberIDType* pNextFemMemberID);
   void GenerateSubstructureFemModel(SuperNodeLocs* pNodeLocs,  IFem2dJointCollection*  pJoints, IFem2dMemberCollection* pMembers, MemberIDType* pNextFemMemberID);
   void GenerateSupportFemModel(SubNodeLocs* psnl, IFem2dJointCollection*  pJoints, IFem2dMemberCollection* pMembers, ElementLayoutVec* pLayoutVec, MemberIDType* pNextFemMemberID);
   void CheckFemModelStability(SuperNodeLocs* pNodeLocs,  IFem2dJointCollection*  pJoints, IFem2dMemberCollection* pMembers);

   void ClearPOIs(IFem2dPOICollection* femPois);
   void CreateSpanPOI(PoiIDType poiID, SpanIndexType spanIdx, Float64 mbrLoc, IPOI* poi=NULL);
   void CreateSsmPOI(PoiIDType poiID, CollectionIndexType ssmbrIdx, Float64 mbrLoc, IPOI* poi=NULL);
   void CreateSupportPOI(PoiIDType poiID, SupportIDType supportID, Float64 mbrLoc, IPOI* poi=NULL);
   void CreateTemporarySupportPOI(PoiIDType poiID, SupportIDType tempSupportID, Float64 mbrLoc, IPOI* poi=NULL);
   void CreateFemPOI(PoiIDType poiID, MemberType mbrType, MemberIDType lbamMbrID, Float64 lbamMbrLoc, MemberIDType femMbrID, Float64 femMbrLoc, MemberLocationType locType, IPOI* poi);
   void CreateFemMbrPOI(PoiIDType poiID, MemberType mbrType, MemberIDType lbamMbrID, Float64 lbamMbrLoc, MemberIDType leftMbrID, IPOI* poi);
   void ConfigurePoiMap(MemberType mbrType, MemberIDType lbamMbrID, Float64 lbamMbrLoc, IPOI* poi, PoiMap* poi_map);
   HRESULT GetSsPoiInfo(PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* globalX);
   HRESULT GetPoiInfoPrv(PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* localX, Float64* globalX);
   void GetSegmentCrossSectionAtLocation(MemberType mbrType, MemberIDType lbamMbrID, Float64 lbamMbrLoc, ISegmentCrossSection* *leftSps, ISegmentCrossSection* *rightSps);

   void GenerateLoadsForLoadGroup(BSTR loadGroup);
   void GeneratePointLoadsForLoadGroup(BSTR loadGroup, IFem2dLoading* femLoading, bool* wereLoadsApplied);
   void GenerateDistributedLoadsForLoadGroup(BSTR loadGroup, IFem2dLoading* femLoading, bool* wereLoadsApplied);
   void GenerateStrainLoadsForLoadGroup(BSTR loadGroup, IFem2dLoading* femLoading, bool* wereLoadsApplied);
   void GenerateTemperatureLoadsForLoadGroup(BSTR loadGroup, IFem2dLoading* femLoading, bool* wereLoadsApplied);
   void GenerateSettlementLoadsForLoadGroup(BSTR loadGroup, IFem2dLoading* femLoading, bool* wereLoadsApplied);

   void GetFemMembersForLBAMMember(MemberType mbrType, MemberIDType mbrId, const ElementLayoutVec* *pMbrList );
   Float64 GetLBAMMemberLength(MemberType mbrType, MemberIDType mbrId);
   void GetFemLocForLBAMLoc(MemberType lbamMbrType, MemberIDType lbamMbrId, Float64 lbamLoc, MemberLocationType* locType, MemberIDType* pfemId, Float64* pfemLoc);
   void GetFemLocAtSupport(MemberType supportType, MemberIDType lbamMbrId, Float64 lbamLoc, MemberLocationType* locType, MemberIDType* pfemId, Float64* pfemLoc);
   void GetFemMemberLocationAlongSupport(const ElementLayoutVec* pMemberList, Float64 lbamLoc, MemberLocationType* locType, MemberIDType* pfemId, Float64* pfemLoc);
   void GetFemMemberLocationAlongSSM(  CollectionIndexType ssmIdx,  Float64 lbamLoc, MemberLocationType* locType, MemberIDType* pfemId, Float64* pfemLoc);
   void GetFemMemberLocationAlongSpan( SpanIndexType spanIdx, Float64 lbamLoc, MemberLocationType* locType, MemberIDType* pfemId, Float64* pfemLoc);
   void GetSuperstructureMemberLocationAlongSpan(SpanIndexType spanIdx,Float64 spanLoc,MemberIDType* mbrID,Float64* pMbrLoc);

   // This function gets the fem member at globalLoc along a list of members.
   void GetFemMemberLocationAlongMemberList( Float64 globalLoc, Float64 leftEnd, Float64 rightEnd, ElementLayoutVec& memberList, 
                                             MemberLocationType* locType, MemberIDType* pmemberId, Float64* pfemLoc);

   void GenDistributedLoadAlongElements(IFem2dDistributedLoadCollection* femDistrLoads,
                                        LoadOrientation orientation, LoadDirection direction,
                                        Float64 startLocation, Float64 endLocation, 
                                        Float64 mbrLength, Float64 wStart, Float64 wEnd, 
                                        const ElementLayoutVec* pfemMbrList, LoadIDType* lastLoadID);

   void GenStrainLoadAlongElements(IFem2dMemberStrainCollection* pFemStrainLoads,
                                   Float64 startLocation, Float64 endLocation, 
                                   Float64 mbrLength, Float64 axial_strain, Float64 curvature, 
                                   const ElementLayoutVec* pfemMbrList, LoadIDType* lastLoadID);

   void DealWithFem2dExceptions();

};

#endif // !defined(AFX_ANALYSISMODEL_H__A1C2BAF3_A20B_11D5_B05D_00105A9AF985__INCLUDED_)
