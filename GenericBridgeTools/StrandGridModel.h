///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2018  Washington State Department of Transportation
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

// StrandGridModel.h : Declaration of the CStrandGridModel

#pragma once

#include "resource.h"       // main symbols
#include "StrandModelBase.h"
#include <map>

/////////////////////////////////////////////////////////////////////////////
// CStrandGridModel
class ATL_NO_VTABLE CStrandGridModel :
   public CComObjectRootEx<CComSingleThreadModel>,
   public CComCoClass<CStrandGridModel, &CLSID_StrandGridModel>,
   public CStrandModelBase,
   public IStrandGridModel,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CStrandGridModel,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CStrandGridModel()
	{
      m_AllowOddNumberOfHarpedStrands = VARIANT_FALSE;
      m_UseDifferentHarpedGirdAtEnds  = VARIANT_TRUE;
   }

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_STRANDGRIDMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrandGridModel)
   COM_INTERFACE_ENTRY(IStrandModel)
   COM_INTERFACE_ENTRY(IStrandGridModel)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   CComPtr<IStrandFillTool> m_StrandFillTool;

   // array index is EndType enum value
   // these objects support both the IStrandGrid and IStrandGridFiller
   // interfaces. We'll use IStrandGridFiller here since we use it most
   // often (reduces the number of QI calls)
   std::array<CComPtr<IStrandGridFiller>, 2> m_StraightGrid;
   std::array<CComPtr<IStrandGridFiller>, 2> m_HarpGridEnd;
   std::array<CComPtr<IStrandGridFiller>, 2> m_HarpGridHp;
   std::array<CComPtr<IStrandGridFiller>, 2> m_TempGrid;

   // this is a special fill array that represents the max between harped strands at the HP and at the Ends
   CComPtr<IIndexArray> m_HarpedMaxStrandFill;
   StrandIndexType m_MaxHarpedStrands;
   bool m_UpdateHarpedMaxFill;

   // If this is true, it is possible that the one-to-one relationship between strand grid fill locations
   // at the girder ends and harping points is broken. i.e., different fills are are needed for each.
   VARIANT_BOOL m_AllowOddNumberOfHarpedStrands;

   // If this is true, different harped grids are used at the ends of the girder than at the
   // harping point.
   VARIANT_BOOL m_UseDifferentHarpedGirdAtEnds;

   // data and functions required to compute harped grid if odd strands are allowed
   CComPtr<IIndexArray> m_OddHpFill;
   HRESULT ComputeHpFill(IIndexArray* endFill, IIndexArray** hpFill);

   protected:
   virtual HRESULT OnInitialize() override;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStrandModel
public:
   STDMETHOD(Initialize)(ISuperstructureMemberSegment* segment,IPrecastGirder* pGirder) override { return CStrandModelBase::Initialize(segment,pGirder); }
   STDMETHOD(putref_StrandMaterial)(StrandType strandType, IPrestressingStrand* pMaterial) override { return CStrandModelBase::putref_StrandMaterial(strandType, pMaterial); }
   STDMETHOD(get_StrandMaterial)(StrandType strandType, IPrestressingStrand** ppMaterial) override { return CStrandModelBase::get_StrandMaterial(strandType, ppMaterial); }

   STDMETHOD(put_StraightStrandProfileType)(StrandProfileType profileType) override { return CStrandModelBase::put_StraightStrandProfileType(profileType); }
   STDMETHOD(get_StraightStrandProfileType)(StrandProfileType* pProfileType) override { return CStrandModelBase::get_StraightStrandProfileType(pProfileType); }
   STDMETHOD(put_TemporaryStrandProfileType)(StrandProfileType profileType) override { return CStrandModelBase::put_TemporaryStrandProfileType(profileType); }
   STDMETHOD(get_TemporaryStrandProfileType)(StrandProfileType* pProfileType) override { return CStrandModelBase::get_TemporaryStrandProfileType(pProfileType); }

   STDMETHOD(SetHarpingPoints)(Float64 hp1, Float64 hp2) override { return CStrandModelBase::SetHarpingPoints(hp1, hp2); }
   STDMETHOD(GetHarpingPoints)(Float64* hp1, Float64* hp2) override { return CStrandModelBase::GetHarpingPoints(hp1, hp2); }
   STDMETHOD(SetEndHarpingPoints)(Float64 hp1, Float64 hp2) override { return CStrandModelBase::SetEndHarpingPoints(hp1,hp2); }
   STDMETHOD(GetEndHarpingPoints)(Float64* hp1, Float64* hp2) override { return CStrandModelBase::GetEndHarpingPoints(hp1,hp2); }
   STDMETHOD(put_HarpingPointMeasure)(HarpPointMeasure measure) override { return CStrandModelBase::put_HarpingPointMeasure(measure); }
   STDMETHOD(get_HarpingPointMeasure)(HarpPointMeasure* measure) override { return CStrandModelBase::get_HarpingPointMeasure(measure); }
   STDMETHOD(put_EndHarpingPointMeasure)(HarpPointMeasure measure) override { return CStrandModelBase::put_EndHarpingPointMeasure(measure); }
   STDMETHOD(get_EndHarpingPointMeasure)(HarpPointMeasure* measure) override { return CStrandModelBase::get_EndHarpingPointMeasure(measure); }
   STDMETHOD(put_HarpingPointReference)(HarpPointReference hpRef) override { return CStrandModelBase::put_HarpingPointReference(hpRef); }
   STDMETHOD(get_HarpingPointReference)(HarpPointReference* hpRef) override { return CStrandModelBase::get_HarpingPointReference(hpRef); }
   STDMETHOD(put_EndHarpingPointReference)(HarpPointReference hpRef) override { return CStrandModelBase::put_EndHarpingPointReference(hpRef); }
   STDMETHOD(get_EndHarpingPointReference)(HarpPointReference* hpRef) override { return CStrandModelBase::get_EndHarpingPointReference(hpRef); }
   STDMETHOD(put_UseMinHarpPointDistance)(VARIANT_BOOL bUseMin) override { return CStrandModelBase::put_UseMinHarpPointDistance(bUseMin); }
   STDMETHOD(get_UseMinHarpPointDistance)(VARIANT_BOOL* bUseMin) override { return CStrandModelBase::get_UseMinHarpPointDistance(bUseMin); }
   STDMETHOD(put_MinHarpPointDistance)(Float64 minHpDist) override { return CStrandModelBase::put_MinHarpPointDistance(minHpDist); }
   STDMETHOD(get_MinHarpPointDistance)(Float64* minHpDist) override { return CStrandModelBase::get_MinHarpPointDistance(minHpDist); }
   STDMETHOD(GetHarpingPointLocations)(Float64* hp1, Float64* hp2) override { return CStrandModelBase::GetHarpingPointLocations(hp1,hp2); }
   STDMETHOD(GetEndHarpingPointLocations)(Float64* hp1, Float64* hp2) override { return CStrandModelBase::GetEndHarpingPointLocations(hp1,hp2); }

   STDMETHOD(GetStrandRowCount)(StrandType strandType, Float64 Xs, RowIndexType* nRows) override;
   STDMETHOD(GetNumStrandsInRow)(StrandType strandType, Float64 Xs, RowIndexType rowIdx, StrandIndexType* nStrands) override;
   STDMETHOD(GetStrandsInRow)(StrandType strandType, Float64 Xs, RowIndexType rowIdx, IIndexArray** ppStrandIndicies) override;

   STDMETHOD(GetStrandPositions)(StrandType strandType, Float64 Xs, IPoint2dCollection** ppPoints) override;
   STDMETHOD(GetStrandCount)(StrandType strandType, StrandIndexType* pStrands) override;
   STDMETHOD(GetStrandCG)(StrandType strandType, Float64 Xs, IPoint2d** pntCG) override;
   STDMETHOD(ComputeMaxHarpedStrandSlope)(Float64 Xs, Float64* pSlope) override;
   STDMETHOD(ComputeAvgHarpedStrandSlope)(Float64 Xs, Float64* pSlope) override;
   STDMETHOD(GetStrandProfile)(StrandType strandType, StrandIndexType strandIdx, IPoint2dCollection** ppProfile) override;
   STDMETHOD(GetStrandCGProfile)(VARIANT_BOOL bIncludeTempStrands, IPoint2dCollection** ppProfile) override;

   STDMETHOD(StraightStrandBoundingBox)(EndType endType, IRect2d** box) override;
   STDMETHOD(HarpedEndStrandBoundingBox)(EndType endType, IRect2d** box) override;
   STDMETHOD(HarpedHpStrandBoundingBox)(EndType endType, IRect2d** box) override;

   // Debonded straight strands based on Positions index (i.e., from get_StraightStrandPositions)
   STDMETHOD(GetStraightStrandDebondLengthByPositionIndex)(Float64 Xs, StrandIndexType positionIndex, Float64* XCoord, Float64* YCoord, Float64* l1, Float64* l2) override;
   STDMETHOD(GetStraightStrandsDebondedByPositionIndex)(Float64 Xs, IIndexArray** positionIndexes) override;

   STDMETHOD(GetStraightStrandDebondCount)(WDebondLocationType loc, StrandIndexType* pCount) override;
   STDMETHOD(GetDebondingLocations)(StrandType strandType,IDblArray** arrLeft, IDblArray** arrRight) override;
   STDMETHOD(GetDebondedStrandsAtSection)(EndType endType, StrandType strandType, SectionIndexType sectionIdx, IIndexArray** pstnIndexes) override;
   STDMETHOD(GetStraightStrandBondedLengthByPositionIndex)(StrandIndexType positionIndex, Float64 Xs, Float64* XCoord, Float64* YCoord, Float64* leftBond, Float64* rightBond) override;
   STDMETHOD(get_StraightStrandDebondInRow)(Float64 Xs,RowIndexType rowIdx, StrandIndexType* nStrands) override;
   STDMETHOD(IsExteriorStraightStrandDebondedInRow)(Float64 Xs, RowIndexType rowIndex, VARIANT_BOOL* bResult) override;
   STDMETHOD(GetStraightStrandDebondedConfigurationCountByRow)(Float64 Xs, RowIndexType rowIdx, IndexType* pConfigCount) override;
   STDMETHOD(GetStraightStrandDebondConfigurationByRow)(Float64 Xs, RowIndexType rowIdx, IndexType configIdx, Float64* pXstart, Float64* pBondedLength, IndexType* pnStrands) override;
   STDMETHOD(GetStraightStrandDebondedRows)(Float64 Xs,IIndexArray** ppRowIndexes) override;

// IStrandGridModel
public:
   STDMETHOD(SetStrandMovers)(IStrandMover* pStartStrandMover, IStrandMover* pHp1StrandMover, IStrandMover* pHp2StrandMover, IStrandMover* pEndStrandMover) override;
   STDMETHOD(putref_StrandMover)(StrandGridType sgType,EndType endType,IStrandMover* pStrandMover) override;
   STDMETHOD(get_StrandMover)(StrandGridType sgType,EndType endType,IStrandMover** ppStrandMover) override;

   STDMETHOD(GetStrandPositionsEx)(StrandType strandType,Float64 Xs, IIndexArray* fill, IPoint2dCollection** points) override;
   STDMETHOD(GetStrandCGEx)(StrandType strandType, Float64 Xs, IIndexArray* fill, IPoint2d** pntCG) override;
   STDMETHOD(GetStrandCountEx)(StrandType strandType, IIndexArray* fill,StrandIndexType* pStrands) override;

   STDMETHOD(StraightStrandBoundingBoxEx)(EndType endType,  IIndexArray* fill, IRect2d** box) override;
   STDMETHOD(HarpedEndStrandBoundingBoxEx)(EndType endType,  IIndexArray* fill, IRect2d** box) override;
   STDMETHOD(HarpedHpStrandBoundingBoxEx)(EndType endType,  IIndexArray* fill, IRect2d** box) override;

   STDMETHOD(get_StraightStrandGrid)(EndType endType,IStrandGrid** grid) override;
   STDMETHOD(get_TemporaryStrandGrid)(EndType endType,IStrandGrid** grid) override;
   STDMETHOD(get_HarpedStrandGridEnd)(EndType endType,IStrandGrid** grid) override;
   STDMETHOD(get_HarpedStrandGridHP)(EndType endType,IStrandGrid** grid) override;
   
   STDMETHOD(put_AllowOddNumberOfHarpedStrands)(VARIANT_BOOL bUseMin) override;
   STDMETHOD(get_AllowOddNumberOfHarpedStrands)(VARIANT_BOOL* bUseMin) override;
   
   STDMETHOD(put_UseDifferentHarpedGridsAtEnds)(VARIANT_BOOL bUseDifferent) override;
   STDMETHOD(get_UseDifferentHarpedGridsAtEnds)(VARIANT_BOOL* bUseDifferent) override;
   
   STDMETHOD(get_TopElevation)(Float64* top) override;
   
   STDMETHOD(get_HarpedStrandAdjustmentEnd)(EndType endType,Float64* offset) override;
   STDMETHOD(put_HarpedStrandAdjustmentEnd)(EndType endType,Float64 offset) override;
   STDMETHOD(get_HarpedStrandAdjustmentHP)(EndType endType,Float64* offset) override;
   STDMETHOD(put_HarpedStrandAdjustmentHP)(EndType endType,Float64 offset) override;

   STDMETHOD(GetMaxStrandFill)(StrandType strandType,IIndexArray** fill) override;
   
   STDMETHOD(putref_StrandFill)(StrandType strandType,IIndexArray* fill) override;
   STDMETHOD(get_StrandFill)(StrandType strandType, IIndexArray** fill) override;
   
   STDMETHOD(StrandIndexToGridIndex)(StrandType strandType,StrandIndexType strandIndex, GridIndexType* gridIndex) override;
   STDMETHOD(StrandIndexToGridIndexEx)(StrandType strandType, IIndexArray* fill, StrandIndexType strandIndex, GridIndexType* gridIndex) override;
   
   STDMETHOD(GetHarpedEndFilledGridBoundsEx)(EndType endType,IIndexArray* fill, Float64* bottomElev, Float64* topElev) override;
   STDMETHOD(GetHarpedHpFilledGridBoundsEx)(EndType endType,IIndexArray* fill, Float64* bottomElev, Float64* topElev) override;

   STDMETHOD(GetHarpedEndAdjustmentBounds)(EndType endType, Float64* DownwardAdjustment, Float64* UpwardAdjustment) override;
   STDMETHOD(GetHarpedEndAdjustmentBoundsEx)(EndType endType, IIndexArray* fill, Float64* DownwardAdjustment, Float64* UpwardAdjustment) override;
   STDMETHOD(GetHarpedHpAdjustmentBounds)(EndType endType, Float64* DownwardAdjustment, Float64* UpwardAdjustment) override;
   STDMETHOD(GetHarpedHpAdjustmentBoundsEx)(EndType endType, IIndexArray* fill, Float64* DownwardAdjustment, Float64* UpwardAdjustment) override;

   // Compute offset adjustment required in order to put harped strands within proper bounds
   // If zero, no adjustment is required. 
   // If non-zero, add this number to current offset to move current harped strands just enough to fit within cross section boundary
   STDMETHOD(HarpedEndStrandBoundaryCheck)(EndType endType,Float64* adjustment) override;
   STDMETHOD(HarpedHpStrandBoundaryCheck)(EndType endType,Float64* adjustment) override;
   
   STDMETHOD(ComputeMaxHarpedStrandSlopeEx)(Float64 Xs, IIndexArray* fill,  Float64 startOffset, Float64 hp1Offset, Float64 hp2Offset, Float64 endOffset,Float64* slope) override;
   STDMETHOD(ComputeAvgHarpedStrandSlopeEx)(Float64 Xs, IIndexArray* fill,  Float64 startOffset, Float64 hp1Offset, Float64 hp2Offset, Float64 endOffset,Float64* slope) override;
   
   
   STDMETHOD(get_HarpedEndAdjustmentIncrement)(Float64* increment) override;
   STDMETHOD(get_HarpedHpAdjustmentIncrement)(Float64* increment) override;
   
   STDMETHOD(GetMaxStrands)(StrandType strandType,StrandIndexType* nStrands) override;
   
   // Debond straight strands based on Grid index
   STDMETHOD(ClearStraightStrandDebonding)() override;
   STDMETHOD(DebondStraightStrandByGridIndex)(GridIndexType grdIndex,Float64 l1,Float64 l2) override;
   STDMETHOD(GetDebondedStraightStrandsByGridIndex)(IIndexArray** grdIndexes) override;
   STDMETHOD(GetStraightStrandDebondLengthByGridIndex)(EndType endType,GridIndexType grdIndex,Float64* XCoord, Float64* YCoord, Float64* l1,Float64* l2) override;
   
   STDMETHOD(GetStraightStrandBondedLengthByGridIndex)(GridIndexType grdIndex, Float64 distFromStart, Float64* XCoord, Float64* YCoord, Float64* leftBond, Float64* rightBond) override;
   
private:
   void GetHarpedStrandGrid(Float64 Xs, IStrandGridFiller** ppGrid);
   void RemoveStraightStrandDebondedStrandPositions(Float64 distFromStart, IPoint2dCollection* pPoints);

   Float64 GetSectionHeight(Float64 Xs);
   Float64 GetGirderDepthAdjustment(Float64 Xs, Float64 distToStartGrid, Float64 distBetweenGrids, IStrandGridFiller* pStartGridFiller = nullptr, IStrandGridFiller* pEndGridFiller = nullptr);
   HRESULT GetStraightStrandPositions(Float64 Xs, IIndexArray* fill, IPoint2dCollection** points);
   HRESULT GetHarpedStrandPositions(Float64 Xs, IIndexArray* fill, IPoint2dCollection** points);
   HRESULT GetTemporaryStrandPositions(Float64 Xs, IIndexArray* fill, IPoint2dCollection** points);
   HRESULT GetStrandPositions(Float64 Xs, Float64 distToStartGrid, Float64 distBetweenGrids, Float64 Lg, Float64 startPrecamber, Float64 endPrecamber, IIndexArray* startFill, IStrandGridFiller* pStartGridFiller, IIndexArray* endFill, IStrandGridFiller* pEndGridFiller, IPoint2dCollection** points);

   HRESULT GetStraightStrandCount(IIndexArray* fill, StrandIndexType* nStrands);
   HRESULT GetHarpedStrandCount(IIndexArray* fill, StrandIndexType* nStrands);
   HRESULT GetTemporaryStrandCount(IIndexArray* fill, StrandIndexType* nStrands);

   HRESULT GetStraightStrandProfile(StrandIndexType strandIdx,IPoint2dCollection** ppProfilePoints);
   HRESULT GetHarpedStrandProfile(StrandIndexType strandIdx,IPoint2dCollection** ppProfilePoints);
   HRESULT GetTemporaryStrandProfile(StrandIndexType strandIdx,IPoint2dCollection** ppProfilePoints);
   //Float64 GetHarpPatternFillAdjustment();
   HRESULT UpdateMaxStrandFill();

   HRESULT PutRefStraightStrandFill(IIndexArray* fill);
   HRESULT PutRefHarpedStrandFill(IIndexArray* fill);
   HRESULT PutRefTemporaryStrandFill(IIndexArray* fill);
};
