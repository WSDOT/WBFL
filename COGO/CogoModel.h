///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// CogoModel.h : Declaration of the CCogoModel

#ifndef __COGOMODEL_H_
#define __COGOMODEL_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCogoModel
class ATL_NO_VTABLE CCogoModel : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CCogoModel,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CCogoModel, &CLSID_CogoModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCogoModel,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ICogoModel,
   public IMeasure,
   public ILocate,
   public IIntersect,
   public IProject,
   public IDivide,
   public ITangent
{
public:
	CCogoModel()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_COGOMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCogoModel)
	COM_INTERFACE_ENTRY(ICogoModel)
	COM_INTERFACE_ENTRY(IMeasure)
	COM_INTERFACE_ENTRY(ILocate)
	COM_INTERFACE_ENTRY(IIntersect)
	COM_INTERFACE_ENTRY(IProject)
	COM_INTERFACE_ENTRY(IDivide)
	COM_INTERFACE_ENTRY(ITangent)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICogoModel
public:
   STDMETHOD(StorePoint)(IDType id, Float64 x, Float64 y) override;
   STDMETHOD(StorePointEx)(IDType id, IPoint2d* pPoint) override;
   STDMETHOD(StorePoints)(IDType firstID, IDType idInc, IPoint2dCollection* pPoints) override;
   STDMETHOD(GetPointCount)(IndexType* nPoints) override;
   STDMETHOD(GetPointByID)(IDType id, IPoint2d** ppPoint) override;
   STDMETHOD(GetPointByIndex)(IndexType idx, IDType* pID, IPoint2d** ppPoint) override;
   STDMETHOD(ReplacePointByID)(IDType id, Float64 x, Float64 y) override;
   STDMETHOD(ReplacePointByIDEx)(IDType id, IPoint2d* pPoint) override;
   STDMETHOD(ReplacePointByIndex)(IndexType idx, Float64 x, Float64 y) override;
   STDMETHOD(ReplacePointByIndexEx)(IndexType idx, IPoint2d* pPoint) override;
   STDMETHOD(RemovePointByID)(IDType id) override;
   STDMETHOD(RemovePointByIndex)(IndexType index) override;
   STDMETHOD(ClearPoints)() override;
   STDMETHOD(StorePathSegment)(IDType id, IDType startID, IDType endID) override;
   STDMETHOD(GetPathSegmentByID)(IDType id, IDType* pStartID, IDType* pEndID) override;
   STDMETHOD(GetPathSegmentByIndex)(IndexType idx, IDType* pID, IDType* pStartID, IDType* pEndID) override;
   STDMETHOD(CreatePathSegmentByID)(IDType id, IPathSegment** ppSegment) override;
   STDMETHOD(CreatePathSegmentByIndex)(IndexType idx, IPathSegment** ppSegment) override;
   STDMETHOD(RemovePathSegmentByID)(IDType id) override;
   STDMETHOD(RemovePathSegmentByIndex)(IndexType index) override;
   STDMETHOD(ClearPathSegments)() override;
   STDMETHOD(StoreCompoundCurve)(IDType id, IDType pbtID, IDType piID, IDType pftID, Float64 radius, Float64 lsEntry, TransitionCurveType lsEntryType, Float64 lsExit, TransitionCurveType lsExitType) override;
   STDMETHOD(GetCompoundCurveCountByID)(IDType id, IndexType* nCurves) override;
   STDMETHOD(GetCompoundCurveCountByIndex)(IndexType index, IDType* pID, IndexType* nCurves) override;
   STDMETHOD(GetCompoundCurveByID)(IDType id, IDType* pbtID, IDType* piID, IDType* pftID, Float64* pRadius, Float64* pLsEntry, TransitionCurveType* pLsEntryType, Float64* pLsExit, TransitionCurveType* pLsExitType) override;
   STDMETHOD(GetCompoundCurveByIndex)(IndexType idx, IDType* pbtID, IDType* piID, IDType* pftID, Float64* pRadius, Float64* pLsEntry, TransitionCurveType* pLsEntryType, Float64* pLsExit, TransitionCurveType* pLsExitType) override;
   STDMETHOD(CreateCompoundCurveByID)(IDType id, ICompoundCurve** ppCurve) override;
   STDMETHOD(CreateCompoundCurveByIndex)(IndexType idx, ICompoundCurve** ppCurve) override;
   STDMETHOD(RemoveCompoundCurveByID)(IDType id) override;
   STDMETHOD(RemoveCompoundCurveByIndex)(IndexType index) override;
   STDMETHOD(ClearCompoundCurves)() override;
   STDMETHOD(StoreCircularCurve)(IDType id, IDType pbtID, IDType piID, IDType pftID, Float64 radius) override;
   STDMETHOD(GetCircularCurveByID)(IDType id, IDType* pbtID, IDType* piID, IDType* pftID, Float64* pRadius) override;
   STDMETHOD(GetCircularCurveByIndex)(IndexType idx, IDType* pID, IDType* pbtID, IDType* piID, IDType* pftID, Float64* pRadius) override;
   STDMETHOD(CreateCircularCurveByID)(IDType id, ICircularCurve** ppCurve) override;
   STDMETHOD(CreateCircularCurveByIndex)(IndexType idx, ICircularCurve** ppCurve) override;
   STDMETHOD(RemoveCircularCurveByID)(IDType id) override;
   STDMETHOD(RemoveCircularCurveByIndex)(IndexType index) override;
   STDMETHOD(ClearCircularCurves)() override;
   STDMETHOD(StoreTransitionCurve)(IDType id, IDType startID, VARIANT varDirection, Float64 r1, Float64 r2, Float64 L, TransitionCurveType transitionType) override;
   STDMETHOD(GetTransitionCurveByID)(IDType id, IDType* startID, IDirection** ppDirection, Float64* r1, Float64* r2, Float64* L, TransitionCurveType* transitionType) override;
   STDMETHOD(GetTransitionCurveByIndex)(IndexType index, IDType* pID, IDType* startID, IDirection** ppDirection, Float64* r1, Float64* r2, Float64* L, TransitionCurveType* transitionType) override;
   STDMETHOD(CreateTransitionCurveByID)(IDType id, ITransitionCurve** ppCurve) override;
   STDMETHOD(CreateTransitionCurveByIndex)(IndexType index, ITransitionCurve** ppCurve) override;
   STDMETHOD(RemoveTransitionCurveByID)(IDType id) override;
   STDMETHOD(RemoveTransitionCurveByIndex)(IndexType index) override;
   STDMETHOD(ClearTransitionCurvese)() override;
   STDMETHOD(StoreCubicSpline)(IDType id, IIDArray* pIDs) override;
   STDMETHOD(GetCubicSplineByID)(IDType id, IIDArray** ppIDs) override;
   STDMETHOD(GetCubicSplineByIndex)(IndexType index, IDType* pID, IIDArray** ppIDs) override;
   STDMETHOD(CreateCubicSplineByID)(IDType id, ICubicSpline** ppCurve) override;
   STDMETHOD(CreateCubicSplineByIndex)(IndexType index, ICubicSpline** ppCurve) override;
   STDMETHOD(RemoveCubicSplineByID)(IDType id) override;
   STDMETHOD(RemoveCubicSplineByIndex)(IndexType index) override;
   STDMETHOD(ClearCubicSplines)() override;
   STDMETHOD(StoreAlignment)(IDType id) override;
   STDMETHOD(GetAlignmentCount)(IndexType* nAlignments) override;
   STDMETHOD(AddPathElementToAlignmentByID)(IDType alignemntID, PathElementType elementType, IDType elementID) override;
   STDMETHOD(AddPathElementToAlignmentByIndex)(IndexType alignemntIndex, PathElementType elementType, IDType elementID) override;
   STDMETHOD(GetAlignmentPathElementCountByID)(IDType alignmentID, IndexType* nElements) override;
   STDMETHOD(GetAlignmentPathElementCountByIndex)(IndexType alignentIndex, IndexType* nElements) override;
   STDMETHOD(GetAlignmentPathElementByID)(IDType alignmentID, IndexType elementIndex, PathElementType* pType, IDType* pElementID) override;
   STDMETHOD(GetAlignmentPathElementByIndex)(IndexType alignmentIndex, IndexType elementIndex, IDType* pID, PathElementType* pType, IDType* pElementID) override;
   STDMETHOD(GetAlignmentID)(IndexType alignmentIdx, IDType* pID) override;
   STDMETHOD(CreateAlignmentByID)(IDType id, IAlignment** ppAlignment) override;
   STDMETHOD(CreateAlignmentByIndex)(IndexType index, IAlignment** ppAlignment) override;
   STDMETHOD(RemoveAlignmentByID)(IDType id) override;
   STDMETHOD(RemoveAlignmentByIndex)(IndexType index) override;
   STDMETHOD(ClearAlignments)() override;
   STDMETHOD(SetAlignmentReferenceStation)(IDType aligmentID, VARIANT varStation) override;
   STDMETHOD(RemoveAlignmentReferenceStation)(IDType aligmentID) override;
   STDMETHOD(GetAlignmentReferenceStation)(IDType aligmentID, IStation** ppStation) override;
   STDMETHOD(AddStationEquation)(IDType alignmentID, Float64 back, Float64 ahead) override;
   STDMETHOD(GetStationEquationCount)(IDType alignmentID, IndexType* nEquations) override;
   STDMETHOD(GetStationEquation)(IDType alignmentID, IndexType equationIndex, Float64* pBack, Float64* pAhead) override;
   STDMETHOD(ClearStationEquations)() override;
   STDMETHOD(StorePath)(IDType id) override;
   STDMETHOD(GetPathCount)(IndexType* nPaths) override;
   STDMETHOD(AddPathElementToPathByID)(IDType pathID, PathElementType elementType, IDType elementID) override;
   STDMETHOD(AddPathElementToPathByIndex)(IndexType pathIndex, PathElementType elementType, IDType elementID) override;
   STDMETHOD(GetPathElementCountByID)(IDType id, IndexType* nElements) override;
   STDMETHOD(GetPathElementCountByIndex)(IndexType index, IndexType* nElements) override;
   STDMETHOD(GetPathElementByID)(IDType pathID, IndexType elementIndex, PathElementType* pType, IDType* pElementID) override;
   STDMETHOD(GetPathElementByIndex)(IndexType pathIndex, IndexType elementIndex, IDType* pID, PathElementType* pType, IDType* pElementID) override;
   STDMETHOD(GetPathID)(IndexType idx, IDType* pPathID) override;
   STDMETHOD(CreatePathByID)(IDType id, IPath** ppPath) override;
   STDMETHOD(CreatePathByIndex)(IndexType index, IPath** ppPath) override;
   STDMETHOD(RemovePathByID)(IDType id) override;
   STDMETHOD(RemovePathByIndex)(IndexType index) override;
   STDMETHOD(ClearPaths)() override;
   STDMETHOD(StoreProfilePoint)(IDType id, VARIANT varStation, Float64 elevation) override;
   STDMETHOD(StoreProfilePointEx)(IDType id, IProfilePoint* pPoint) override;
   STDMETHOD(GetProfilePointCount)(IndexType* nPoints) override;
   STDMETHOD(GetProfilePointByID)(IDType id, IProfilePoint** ppPoint) override;
   STDMETHOD(GetProfilePointByIndex)(IndexType index, IDType* pID, IProfilePoint** ppPoint) override;
   STDMETHOD(RemoveProfilePointByID)(IDType id) override;
   STDMETHOD(RemoveProfilePointByIndex)(IndexType index) override;
   STDMETHOD(ClearProfilePoints)() override;
   STDMETHOD(StoreProfileSegment)(IDType id, IDType startID, IDType endID) override;
   STDMETHOD(GetProfileSegmentCount)(IndexType* nSegments) override;
   STDMETHOD(GetProfileSegmentByID)(IDType id, IDType* pStartID, IDType* pEndID) override;
   STDMETHOD(GetProfileSegmentByIndex)(IndexType index, IDType* pID, IDType* pStartID, IDType* pEndID) override;
   STDMETHOD(CreateProfileSegmentByID)(IDType id, IProfileSegment** ppSegment) override;
   STDMETHOD(CreateProfileSegmentByIndex)(IndexType index, IProfileSegment** ppSegment) override;
   STDMETHOD(RemoveProfileSegmentByID)(IDType id) override;
   STDMETHOD(RemoveProfileSegmentByIndex)(IndexType index) override;
   STDMETHOD(ClearProfileSegments)() override;
   STDMETHOD(StoreVerticalCurve)(IDType id, IDType pbg, IDType pvi, IDType pfg, Float64 l1_or_g1, Float64 l2_or_g2) override;
   STDMETHOD(GetVerticalCurveCount)(IndexType* nCurves) override;
   STDMETHOD(GetVerticalCurveByID)(IDType id, IDType* pbg, IDType* pvi, IDType* pfg, Float64* l1_or_g1, Float64* l2_or_g2) override;
   STDMETHOD(GetVerticalCurveByIndex)(IndexType index, IDType* pID, IDType* pbg, IDType* pvi, IDType* pfg, Float64* l1_or_g1, Float64* l2_or_g2) override;
   STDMETHOD(CreateVerticalCurveByID)(IDType id, IVerticalCurve** ppVertCurve) override;
   STDMETHOD(CreateVerticalCurveByIndex)(IndexType index, IVerticalCurve** ppVertCurve) override;   
   STDMETHOD(RemoveVerticalCurveByID)(IDType id) override;
   STDMETHOD(RemoveVerticalCurveByIndex)(IndexType index) override;
   STDMETHOD(ClearVerticalCurves)() override;
   STDMETHOD(StoreProfile)(IDType id) override;
   STDMETHOD(GetProfileCount)(IndexType* nProfiles) override;
   STDMETHOD(AddProfileElementByID)(IDType profileID, ProfileElementType elementType, IDType elementID) override;
   STDMETHOD(AddProfileElementByIndex)(IndexType profileIndex, ProfileElementType elementType, IDType elementID) override;
   STDMETHOD(GetProfileElementCountByID)(IDType id, IndexType* nElements) override;
   STDMETHOD(GetProfileElementCountByIndex)(IndexType index, IndexType* nElements) override;
   STDMETHOD(GetProfileElementByID)(IDType profileID, IndexType elementIndex, ProfileElementType* pType, IDType* pElementID) override;
   STDMETHOD(GetProfileElementByIndex)(IndexType profileIndex, IndexType elementIndex, ProfileElementType* pType, IDType* pElementID) override;
   STDMETHOD(CreateProfileByID)(IDType profileID, IProfile** ppProfile) override;
   STDMETHOD(CreateProfileByIndex)(IndexType profileIndex, IProfile** ppProfile) override;
   STDMETHOD(RemoveProfileByID)(IDType id) override;
   STDMETHOD(RemoveProfileByIndex)(IndexType index) override;
   STDMETHOD(ClearProfiles)() override;

   STDMETHOD(StoreSurface)(IDType surfaceID, IndexType nSegments, IndexType alignmentPointIdx, IndexType profilePointIdx) override;
   STDMETHOD(GetSurfaceCount)(IndexType* nSurfaces) override;
   STDMETHOD(AddSurfaceTemplate)(IDType surfaceID, VARIANT varStation) override;
   STDMETHOD(CopySurfaceTemplateByID)(IDType surfaceID, IndexType templateIdx, VARIANT varStation) override;
   STDMETHOD(CopySurfaceTemplateByIndex)(IndexType surfaceIndex, IndexType templateIdx, VARIANT varStation) override;
   STDMETHOD(MoveSurfaceTemplateByID)(IDType surfaceID, IndexType templateIdx, VARIANT varNewStation) override;
   STDMETHOD(MoveSurfaceTemplateByIndex)(IndexType surfaceIndex, IndexType templateIdx, VARIANT varNewStation) override;
   STDMETHOD(GetSurfaceTemplateCountByID)(IDType surfaceID, IndexType* nSurfaceTemplates) override;
   STDMETHOD(GetSurfaceTemplateCountByIndex)(IndexType surfaceIndex, IDType* pID, IndexType* nSurfaceTemplates) override;
   STDMETHOD(GetSurfaceTemplateLocationByID)(IDType surfaceID, IndexType templateIdx, IStation** ppStation) override;
   STDMETHOD(GetSurfaceTemplateLocationByIndex)(IndexType surfaceIndex, IndexType templateIdx, IStation** ppStation) override;
   STDMETHOD(UpdateSurfaceTemplateSegmentByID)(IDType surfaceID, IndexType templateIndex, IndexType segmentIndex, Float64 width, Float64 slope, TemplateSlopeType slopeType) override;
   STDMETHOD(UpdateSurfaceTemplateSegmentByIndex)(IndexType surfaceIndex, IndexType templateIndex, IndexType segmentIndex, Float64 width, Float64 slope, TemplateSlopeType slopeType) override;
   STDMETHOD(RemoveSurfaceByID)(IDType surfaceID) override;
   STDMETHOD(RemoveSurfaceByIndex)(IndexType surfaceIndex) override;
   STDMETHOD(StoreSuperelevationByID)(IDType surfaceID, VARIANT varBeginTransitionStation, VARIANT varBeginFullSuperStation, VARIANT varEndFullSuperStation, VARIANT varEndTransitionStation, Float64 rate, IndexType pivotPointIdx,      SuperTransitionType beginTransitionType, Float64 beginL1, Float64 beginL2, SuperTransitionType endTransitionType, Float64 endL1, Float64 endL2) override;
   STDMETHOD(StoreSuperelevationByIndex)(IndexType surfaceIndex, VARIANT varBeginTransitionStation, VARIANT varBeginFullSuperStation, VARIANT varEndFullSuperStation, VARIANT varEndTransitionStation, Float64 rate, IndexType pivotPointIdx,      SuperTransitionType beginTransitionType, Float64 beginL1, Float64 beginL2, SuperTransitionType endTransitionType, Float64 endL1, Float64 endL2) override;
   STDMETHOD(StoreWideningByID)(IDType surfaceID, VARIANT varBeginTransitionStation, VARIANT varBeginFullWidening, VARIANT varEndFullWidening, VARIANT varEndTransitionStation, Float64 widening, IndexType segment1, IndexType segment2) override;
   STDMETHOD(StoreWideningByIndex)(IndexType surfaceIndex, VARIANT varBeginTransitionStation, VARIANT varBeginFullWidening, VARIANT varEndFullWidening, VARIANT varEndTransitionStation, Float64 widening, IndexType segment1, IndexType segment2) override;
   STDMETHOD(CreateSurfaceByID)(IDType surfaceID, ISurface** ppSurface) override;
   STDMETHOD(CreateSurfaceByIndex)(IndexType surfaceIndex, ISurface** ppSurface) override;

   STDMETHOD(AttachProfileToAlignment)(IDType profileID, IDType alignmentID) override;
   STDMETHOD(AttachSurfaceToProfile)(IDType surfaceID, IDType profileID) override;

   STDMETHOD(get_Tangent)(/*[out, retval]*/ ITangent* *pVal) override;
   STDMETHOD(get_Divide)(/*[out, retval]*/ IDivide* *pVal) override;
	STDMETHOD(get_Project)(/*[out, retval]*/ IProject* *pVal) override;
	STDMETHOD(get_Measure)(/*[out, retval]*/ IMeasure* *pVal) override;
	STDMETHOD(get_Locate)(/*[out, retval]*/ ILocate* *pVal) override;
	STDMETHOD(get_Intersect)(/*[out, retval]*/ IIntersect* *pVal) override;
   STDMETHOD(get_Engine)(ICogoEngine** ppEngine) override;
	STDMETHOD(Clear)() override;

// IMeasure
public:
  	STDMETHOD(Angle)(/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID vertexID,/*[in]*/ CogoObjectID toID,/*[out,retval]*/ IAngle** angle) override;
	STDMETHOD(Area)(/*[in]*/ VARIANT IDs,/*[out,retval]*/ Float64* area) override;
	STDMETHOD(Distance)(/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID,/*[out,retval]*/ Float64* dist) override;
	STDMETHOD(Direction)(/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID,/*[out,retval]*/ IDirection** dir) override;
   STDMETHOD(Inverse)(/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID,/*[out]*/ Float64* dist,/*[out]*/ IDirection** dir) override;

// ILocate
public:
   STDMETHOD(ParallelLineSegment)(/*[in]*/ CogoObjectID newLineID,/*[in]*/ CogoObjectID newFromID,/*[in]*/ CogoObjectID newToID,/*[in]*/ CogoObjectID lineID, /*[in]*/ Float64 offset) override;
   STDMETHOD(ParallelLineByPoints)(/*[in]*/ CogoObjectID newFromID,/*[in]*/ CogoObjectID newToID,/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID, /*[in]*/ Float64 offset) override;
	STDMETHOD(ByDistAngle)(/*[in]*/ CogoObjectID newID,/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varAngle, /*[in]*/ Float64 offset) override;
	STDMETHOD(ByDistDefAngle)(/*[in]*/ CogoObjectID newID,/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID toID, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDefAngle, /*[in]*/ Float64 offset) override;
	STDMETHOD(ByDistDir)(/*[in]*/ CogoObjectID newID,/*[in]*/ CogoObjectID fromID, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset) override;
	STDMETHOD(PointOnLine)(/*[in]*/ CogoObjectID newID,/*[in]*/ CogoObjectID fromID, /*[in]*/ CogoObjectID toID, /*[in]*/ Float64 dist, /*[in]*/ Float64 offset) override;
   STDMETHOD(LinesByPoints)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID id11, /*[in]*/ CogoObjectID id12, /*[in]*/ Float64 offset1,/*[in]*/ CogoObjectID id21, /*[in]*/ CogoObjectID id22, /*[in]*/ Float64 offset2, /*[out,retval]*/ VARIANT_BOOL* bFound) override;

// IIntersect
public:
   STDMETHOD(Bearings)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID id1, /*[in]*/ VARIANT varDir1, /*[in]*/ Float64 offset1,/*[in]*/ CogoObjectID id2, /*[in]*/ VARIANT varDir2, /*[in]*/ Float64 offset2,/*[out,retval]*/ VARIANT_BOOL* bFound) override;
   STDMETHOD(BearingCircle)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID id1, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset,/*[in]*/ CogoObjectID idc, /*[in]*/ Float64 radius, /*[in]*/ CogoObjectID idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound) override;
   STDMETHOD(Circles)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID id1, /*[in]*/ Float64 r1, /*[in]*/ CogoObjectID id2, /*[in]*/ Float64 r2, /*[in]*/ CogoObjectID idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound) override;
   STDMETHOD(LineByPointsCircle)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID id1, /*[in]*/ CogoObjectID id2, /*[in]*/ Float64 offset,/*[in]*/ CogoObjectID idc, /*[in]*/ Float64 radius, /*[in]*/ CogoObjectID idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound) override;
   STDMETHOD(Lines)(/*[in]*/CogoObjectID newID,/*[in]*/CogoObjectID id1,/*[in]*/Float64 offset1,/*[in]*/CogoObjectID id2,/*[in]*/Float64 offset2,/*[out,retval]*/VARIANT_BOOL* bFound) override;
   STDMETHOD(LineSegmentCircle)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID lineID, /*[in]*/ Float64 offset,/*[in]*/ CogoObjectID idc, /*[in]*/ Float64 radius, /*[in]*/ CogoObjectID idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound) override;

// IProject
public:
   STDMETHOD(PointOnCurve)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID fromID, /*[in]*/CogoObjectID curveID) override;
   STDMETHOD(PointOnLineByPoints)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID fromID, /*[in]*/ CogoObjectID startID, /*[in]*/ CogoObjectID endID, /*[in]*/ Float64 offset) override;
   STDMETHOD(PointOnLineSegment)(/*[in]*/CogoObjectID newID,/*[in]*/ CogoObjectID fromID,/*[in]*/ CogoObjectID lineID, /*[in]*/ Float64 offset) override;

// IDivide
public:
   STDMETHOD(Arc)(/*[in]*/CogoObjectID firstID,/*[in]*/ CogoObjectID idInc, /*[in]*/ CogoObjectID fromID, /*[in]*/ CogoObjectID HorzexID, /*[in]*/ CogoObjectID toID,/*[in]*/ CollectionIndexType nParts) override;
   STDMETHOD(BetweenPoints)(/*[in]*/CogoObjectID firstID,/*[in]*/ CogoObjectID idInc, /*[in]*/ CogoObjectID fromID, /*[in]*/ CogoObjectID toID,/*[in]*/ CollectionIndexType nParts) override;
   STDMETHOD(LineSegment)(/*[in]*/CogoObjectID firstID,/*[in]*/ CogoObjectID idInc, /*[in]*/ CogoObjectID lineID,/*[in]*/ CollectionIndexType nParts) override;
	STDMETHOD(CompoundCurve)(/*[in]*/ CogoObjectID firstID, /*[in]*/ CogoObjectID idInc, /*[in]*/ CogoObjectID curveID, /*[in]*/ CollectionIndexType nParts) override;
   STDMETHOD(Path)(/*[in]*/CogoObjectID firstID,/*[in]*/CogoObjectID idInc,/*[in]*/CogoObjectID pathID,/*[in]*/ CollectionIndexType nParts,/*[in]*/ Float64 start,/*[in]*/ Float64 end) override;

// ITangent
public:
   STDMETHOD(External)(/*[in]*/ CogoObjectID newID1, /*[in]*/ CogoObjectID idCenter1, /*[in]*/ Float64 radius1,/*[in]*/ CogoObjectID newID2,/*[in]*/ CogoObjectID idCenter2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign) override;
   STDMETHOD(Cross)(/*[in]*/ CogoObjectID newID1, /*[in]*/ CogoObjectID idCenter1, /*[in]*/ Float64 radius1,/*[in]*/ CogoObjectID newID2,/*[in]*/ CogoObjectID idCenter2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign) override;
   STDMETHOD(Point)(/*[in]*/ CogoObjectID newID, /*[in]*/ CogoObjectID idCenter, /*[in]*/ Float64 radius,/*[in]*/ CogoObjectID pointID,/*[in]*/ TangentSignType sign) override;

private:
   std::shared_ptr<WBFL::COGO::Model> m_Model{ std::make_shared<WBFL::COGO::Model>() };
   CComPtr<ICogoEngine> m_Engine;

   template <class C> IDType GetID(const C& container, IndexType index);
};

#endif //__COGOMODEL_H_
