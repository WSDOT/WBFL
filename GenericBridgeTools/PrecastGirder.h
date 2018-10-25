///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2014  Washington State Department of Transportation
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

// PrecastGirder.h : Declaration of the CPrecastGirder

#ifndef __PRECASTGIRDER_H_
#define __PRECASTGIRDER_H_

#include "resource.h"       // main symbols
#include <vector>
#include <set>
#include <MathEx.h>

/////////////////////////////////////////////////////////////////////////////
// CPrecastGirder
class ATL_NO_VTABLE CPrecastGirder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPrecastGirder, &CLSID_PrecastGirder>,
	public ISupportErrorInfo,
	public IPrecastGirder,
   public IObjectSafetyImpl<CPrecastGirder,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CPrecastGirder()
	{
      m_pSegment = 0;

      // default harping point... fraction of girder length, measured from left end
      m_HPMeasure = hpmFractionOfGirderLength;
      m_HPReference = hprEndOfGirder;
      m_HPStart = 0.0;
      m_HP1 = 0.4;
      m_HP2 = 0.4;
      m_HPEnd = 0.0;
      m_AllowOddNumberOfHarpedStrands=VARIANT_FALSE;
      m_UseDifferentHarpedGirdAtEnds=VARIANT_TRUE;

      m_bUseMinHpDistance = VARIANT_FALSE;
      m_MinHpDist = 0;

      m_UpdateLengths = true;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PRECASTGIRDER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPrecastGirder)
	COM_INTERFACE_ENTRY(IPrecastGirder)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   ISegment* m_pSegment; // weak reference to the superstructure member segment for this girder
   CComPtr<IStrandMover> m_pStrandMover;
   CComPtr<IStrandFillTool> m_StrandFillTool;

   CComPtr<IPrestressingStrand> m_StraightStrandMaterial;
   CComPtr<IPrestressingStrand> m_HarpedStrandMaterial;
   CComPtr<IPrestressingStrand> m_TemporaryStrandMaterial;

   SpanIndexType m_SpanIdx;
   GirderIndexType m_GirderIdx;

   // array index is EndType enum value
   CComPtr<IStrandGridFiller> m_StraightGrid[2];
   CComPtr<IStrandGridFiller> m_HarpGridEnd[2];
   CComPtr<IStrandGridFiller> m_HarpGridHp[2];
   CComPtr<IStrandGridFiller> m_TempGrid[2];
   
   // this is a special fill array that represents the max between harped strands at the HP and at the Ends
   CComPtr<IIndexArray> m_HarpedMaxStrandFill;
   StrandIndexType m_MaxHarpedStrands;
   bool m_UpdateHarpedMaxFill;

   CComPtr<IRebarLayout> m_RebarLayout;

   // If this is true, it is possible that the one-to-one relationship between strand grid fill locations
   // at the girder ends and harping points is broken. i.e., different fills are are needed for each.
   VARIANT_BOOL m_AllowOddNumberOfHarpedStrands;

   // If this is true, different harped grids are used at the ends of the girder than at the
   // harping point.
   VARIANT_BOOL m_UseDifferentHarpedGirdAtEnds;

   // data and functions required to compute harped grid if odd strands are allowed
   CComPtr<IIndexArray> m_OddHpFill;
   HRESULT ComputeHpFill(IIndexArray* endFill, IIndexArray** hpFill);

   // HPStart and HP1 are measured from the left end of the girder
   // HPEnd and HP2 are measured from the right end of the girder
   Float64 m_HPStart, m_HPEnd; // location of the m_HarpGridEnd harp grids
   Float64 m_HP1, m_HP2; // harping point location (location of the m_HarpGridHp harp grids)
   HarpPointReference m_HPReference; // describes from where the harping point is measured
   HarpPointMeasure m_HPMeasure; // describes how the harping point is located

   VARIANT_BOOL m_bUseMinHpDistance;
   Float64 m_MinHpDist;   

   // geometry factory for performance
   CComPtr<IPoint2dFactory> m_Point2dFactory;

   // caching of span and girder lengths
   bool m_UpdateLengths;
   void DoUpdateLengths();

   struct Lengths
   {
      Float64 dbSpanLength;           // cl-brg to cl-brg
      Float64 dbGirderLength;         // end to end
      Float64 dbLeftEndDistance;      // cl-brg to end (left end of girder)
      Float64 dbRightEndDistance;     // cl-brg to end (right end of girder)
      Float64 dbLeftBearingOffset;    // cl-pier to cl-brg (left end of girder)
      Float64 dbRightBearingOffset;   // cl-pier to cl-brg (right end of girder)
   } m_Lengths;
  
   void GetHarpPointLocations(Float64& hp1,Float64& hp2);
   void GetEndHarpPointLocations(Float64& hp1,Float64& hp2);
   Float64 GetHarpPointLocation(Float64 hp,bool bRight);
   Float64 GetHarpPatternFillAdjustment();
   HRESULT UpdateMaxStrandFill();

   HRESULT GetStrandPositions(Float64 distFromStart, Float64 distBetweenGrids, IIndexArray* startFill, IStrandGridFiller* pStartGrid, IIndexArray* endFill, IStrandGridFiller* pEndGrid, IPoint2dCollection** points);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPrecastGirder
public:
	STDMETHOD(Initialize)(ISegment* segment,IStrandMover* strandMover);

   STDMETHOD(putref_StraightStrandMaterial)(IPrestressingStrand* pMaterial);
   STDMETHOD(get_StraightStrandMaterial)(IPrestressingStrand** ppMaterial);

   STDMETHOD(putref_HarpedStrandMaterial)(IPrestressingStrand* pMaterial);
   STDMETHOD(get_HarpedStrandMaterial)(IPrestressingStrand** ppMaterial);

   STDMETHOD(putref_TemporaryStrandMaterial)(IPrestressingStrand* pMaterial);
   STDMETHOD(get_TemporaryStrandMaterial)(IPrestressingStrand** ppMaterial);

   STDMETHOD(get_StraightStrandGrid)(/*[in]*/EndType endType,/*[out,retval]*/IStrandGrid** grid);
	STDMETHOD(get_TemporaryStrandGrid)(/*[in]*/EndType endType,/*[out,retval]*/IStrandGrid** grid);
	STDMETHOD(get_HarpedStrandGridEnd)(/*[in]*/EndType endType,/*[out,retval]*/IStrandGrid** grid);
	STDMETHOD(get_HarpedStrandGridHP)(/*[in]*/EndType endType,/*[out,retval]*/IStrandGrid** grid);

	STDMETHOD(put_AllowOddNumberOfHarpedStrands)(/*[in]*/VARIANT_BOOL bUseMin);
	STDMETHOD(get_AllowOddNumberOfHarpedStrands)(/*[out,retval]*/VARIANT_BOOL* bUseMin);

	STDMETHOD(put_UseDifferentHarpedGridsAtEnds)(/*[in]*/VARIANT_BOOL bUseDifferent);
	STDMETHOD(get_UseDifferentHarpedGridsAtEnds)(/*[out,retval]*/VARIANT_BOOL* bUseDifferent);

	STDMETHOD(get_TopElevation)(/*[out,retval]*/Float64* top);

	STDMETHOD(get_HarpedStrandAdjustmentEnd)(/*[out,retval]*/Float64* offset);
	STDMETHOD(put_HarpedStrandAdjustmentEnd)(/*[in]*/Float64 offset);
	STDMETHOD(get_HarpedStrandAdjustmentHP)(/*[out,retval]*/Float64* offset);
	STDMETHOD(put_HarpedStrandAdjustmentHP)(/*[in]*/Float64 offset);

	STDMETHOD(SetHarpingPoints)(/*[in]*/Float64 hp1,/*[in]*/Float64 hp2);
	STDMETHOD(GetHarpingPoints)(/*[out]*/Float64* hp1,/*[out]*/Float64* hp2);
	STDMETHOD(SetEndHarpingPoints)(/*[in]*/Float64 hp1,/*[in]*/Float64 hp2);
	STDMETHOD(GetEndHarpingPoints)(/*[out]*/Float64* hp1,/*[out]*/Float64* hp2);
	STDMETHOD(put_HarpingPointMeasure)(/*[in]*/ HarpPointMeasure measure);
	STDMETHOD(get_HarpingPointMeasure)(/*[out,retval]*/ HarpPointMeasure* measure);
	STDMETHOD(put_HarpingPointReference)(/*[in]*/ HarpPointReference hpRef);
	STDMETHOD(get_HarpingPointReference)(/*[out,retval]*/ HarpPointReference* hpRef);
   STDMETHOD(put_UseMinHarpPointDistance)(/*[in]*/VARIANT_BOOL bUseMin);
	STDMETHOD(get_UseMinHarpPointDistance)(/*[out,retval]*/VARIANT_BOOL* bUseMin);
   STDMETHOD(put_MinHarpPointDistance)(/*[in]*/Float64 minHpDist);
	STDMETHOD(get_MinHarpPointDistance)(/*[out,retval]*/Float64* minHpDist);
	STDMETHOD(GetHarpingPointLocations)(/*[out]*/Float64* hp1,/*[out]*/Float64* hp2);
	STDMETHOD(GetEndHarpingPointLocations)(/*[out]*/Float64* hp1,/*[out]*/Float64* hp2);

   STDMETHOD(get_SpanLength)(/*[out,retval]*/ Float64* length);
   STDMETHOD(get_GirderLength)(/*[out,retval]*/ Float64* length);
   STDMETHOD(get_LeftEndDistance)(/*[out,retval]*/ Float64* size);
   STDMETHOD(get_RightEndDistance)(/*[out,retval]*/ Float64* size);
   STDMETHOD(get_LeftBearingOffset)(/*[out,retval]*/ Float64* offset);
   STDMETHOD(get_RightBearingOffset)(/*[out,retval]*/ Float64* offset);
   STDMETHOD(GetEndPoints)(/*[out]*/IPoint2d** pntPier1,/*[out]*/IPoint2d** pntEnd1,/*[out]*/IPoint2d** pntBrg1,/*[out]*/IPoint2d** pntBrg2,/*[out]*/IPoint2d** pntEnd2,/*[out]*/IPoint2d** pntPier2);

   STDMETHOD(get_HarpedMaxStrandFill)(/*[out,retval]*/IIndexArray** fill);
   STDMETHOD(get_TemporaryMaxStrandFill)(/*[out,retval]*/IIndexArray** fill);
   STDMETHOD(get_StraightMaxStrandFill)(/*[out,retval]*/IIndexArray** fill);

   STDMETHOD(get_StraightStrandFill)(/*[out,retval]*/IIndexArray** fill);
   STDMETHOD(put_StraightStrandFill)(/*[in]*/IIndexArray* fill);
   STDMETHOD(get_HarpedStrandFill)(/*[out,retval]*/IIndexArray** fill);
   STDMETHOD(put_HarpedStrandFill)(/*[in]*/IIndexArray* fill);
   STDMETHOD(get_TemporaryStrandFill)(/*[out,retval]*/IIndexArray** fill);
   STDMETHOD(put_TemporaryStrandFill)(/*[in]*/IIndexArray* fill);

   STDMETHOD(get_StraightStrandPositions)(/*[in]*/Float64 distFromStart, /*[out,retval]*/IPoint2dCollection** points);
   STDMETHOD(get_StraightStrandPositionsEx)(/*[in]*/Float64 distFromStart, /*[in]*/IIndexArray* fill, /*[out,retval]*/IPoint2dCollection** points);
   STDMETHOD(get_HarpedStrandPositions)(/*[in]*/Float64 distFromStart, /*[out,retval]*/IPoint2dCollection** points);
   STDMETHOD(get_HarpedStrandPositionsEx)(/*[in]*/Float64 distFromStart, /*[in]*/IIndexArray* fill, /*[out,retval]*/IPoint2dCollection** points);
   STDMETHOD(get_TemporaryStrandPositions)(/*[in]*/Float64 distFromStart, /*[out,retval]*/IPoint2dCollection** points);
   STDMETHOD(get_TemporaryStrandPositionsEx)(/*[in]*/Float64 distFromStart, /*[in]*/IIndexArray* fill, /*[out,retval]*/IPoint2dCollection** points);

   STDMETHOD(StraightStrandIndexToGridIndex)(/*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex);
   STDMETHOD(StraightStrandIndexToGridIndexEx)(/*[in]*/IIndexArray* fill, /*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex);
   STDMETHOD(HarpedStrandIndexToGridIndex)(/*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex);
   STDMETHOD(HarpedStrandIndexToGridIndexEx)(/*[in]*/IIndexArray* fill, /*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex);
   STDMETHOD(TemporaryStrandIndexToGridIndex)(/*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex);
   STDMETHOD(TemporaryStrandIndexToGridIndexEx)(/*[in]*/IIndexArray* fill, /*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex);

   // Compute bounding boxes of harped and straight strands accounting for vertical offsets for harped strands
   STDMETHOD(StraightStrandBoundingBox)(/*[in]*/EndType endType, /*[out,retval]*/IRect2d** box);
   STDMETHOD(StraightStrandBoundingBoxEx)(/*[in]*/EndType endType, /*[in]*/ IIndexArray* fill, /*[out,retval]*/IRect2d** box);
   STDMETHOD(HarpedEndStrandBoundingBox)(/*[in]*/EndType endType, /*[out,retval]*/IRect2d** box);
   STDMETHOD(HarpedEndStrandBoundingBoxEx)(/*[in]*/EndType endType, /*[in]*/ IIndexArray* fill, /*[out,retval]*/IRect2d** box);
   STDMETHOD(HarpedHpStrandBoundingBox)(/*[in]*/EndType endType, /*[out,retval]*/IRect2d** box);
   STDMETHOD(HarpedHpStrandBoundingBoxEx)(/*[in]*/EndType endType, /*[in]*/ IIndexArray* fill, /*[out,retval]*/IRect2d** box);

   STDMETHOD(GetHarpedEndFilledGridBoundsEx)(/*[in]*/IIndexArray* fill, /*[out]*/Float64* bottomElev, /*[out]*/Float64* topElev);
   STDMETHOD(GetHarpedHpFilledGridBoundsEx)(/*[in]*/IIndexArray* fill, /*[out]*/Float64* bottomElev, /*[out]*/Float64* topElev);

   // Compute offset adjustment required in order to put harped strands within proper bounds
   // If zero, no adjustment is required. 
   // If non-zero, add this number to current offset to move current harped strands just enough to fit within cross section boundary
   STDMETHOD(HarpedEndStrandBoundaryCheck)(/*[out,retval]*/Float64* adjustment);
   STDMETHOD(HarpedHpStrandBoundaryCheck)(/*[out,retval]*/Float64* adjustment);

   STDMETHOD(ComputeMaxHarpedStrandSlope)(/*[in]*/Float64 distFromStart,/*[out,retval]*/Float64* slope);
   STDMETHOD(ComputeMaxHarpedStrandSlopeEx)(/*[in]*/Float64 distFromStart, /*[in]*/IIndexArray* fill, /*[in]*/ Float64 endOffset,/*[in]*/ Float64 hpOffset,/*[out,retval]*/Float64* slope);
   STDMETHOD(ComputeAvgHarpedStrandSlope)(/*[in]*/Float64 distFromStart,/*[out,retval]*/Float64* slope);
   STDMETHOD(ComputeAvgHarpedStrandSlopeEx)(/*[in]*/Float64 distFromStart, /*[in]*/IIndexArray* fill, /*[in]*/ Float64 endOffset,/*[in]*/ Float64 hpOffset,/*[out,retval]*/Float64* slope);

   STDMETHOD(GetHarpedEndAdjustmentBounds)(/*[out]*/Float64* DownwardAdjustment, /*[out]*/Float64* UpwardAdjustment);
   STDMETHOD(GetHarpedEndAdjustmentBoundsEx)(/*[in]*/ IIndexArray* fill, /*[out]*/Float64* DownwardAdjustment, /*[out]*/Float64* UpwardAdjustment);
   STDMETHOD(GetHarpedHpAdjustmentBounds)(/*[out]*/Float64* DownwardAdjustment, /*[out]*/Float64* UpwardAdjustment);
   STDMETHOD(GetHarpedHpAdjustmentBoundsEx)(/*[in]*/ IIndexArray* fill, /*[out]*/Float64* DownwardAdjustment, /*[out]*/Float64* UpwardAdjustment);

   STDMETHOD(get_HarpedEndAdjustmentIncrement)(/*[out,retval]*/Float64* increment);
   STDMETHOD(get_HarpedHpAdjustmentIncrement)(/*[out,retval]*/Float64* increment);

   STDMETHOD(get_MaxStraightStrands)(/*[out,retval]*/StrandIndexType* nStrands);
   STDMETHOD(get_MaxHarpedStrands)(/*[out,retval]*/StrandIndexType* nStrands);
   STDMETHOD(get_MaxTemporaryStrands)(/*[out,retval]*/StrandIndexType* nStrands);

	STDMETHOD(GetStraightStrandCount)(/*[out,retval]*/ StrandIndexType* nStrands);
	STDMETHOD(GetHarpedStrandCount)(/*[out,retval]*/ StrandIndexType* nStrands);
	STDMETHOD(GetTemporaryStrandCount)(/*[out,retval]*/ StrandIndexType* nStrands);
	STDMETHOD(GetStraightStrandCountEx)(/*[in]*/ IIndexArray* fill, /*[out,retval]*/ StrandIndexType* nStrands);
	STDMETHOD(GetHarpedStrandCountEx)(/*[in]*/ IIndexArray* fill, /*[out,retval]*/ StrandIndexType* nStrands);
	STDMETHOD(GetTemporaryStrandCountEx)(/*[in]*/ IIndexArray* fill, /*[out,retval]*/ StrandIndexType* nStrands);

   // rough count of debonded strands for current fill
   STDMETHOD(GetStraightStrandDebondCount)(/*[out,retval]*/ StrandIndexType* count);

   // Debond straight strands based on Grid index
   STDMETHOD(ClearStraightStrandDebonding)();
	STDMETHOD(DebondStraightStrandByGridIndex)(/*[in]*/GridIndexType grdIndex,/*[in]*/Float64 l1,/*[in]*/Float64 l2);
	STDMETHOD(GetDebondedStraightStrandsByGridIndex)(/*[out,retval]*/IIndexArray** grdIndexes);
	STDMETHOD(GetStraightStrandDebondLengthByGridIndex)(/*[in]*/EndType endType,/*[in]*/GridIndexType grdIndex,/*[out]*/Float64* YCoord, /*[out]*/Float64* l1,/*[out]*/Float64* l2);

   // Debonded straight strands based on Positions index (i.e., from get_StraightStrandPositions)
	STDMETHOD(GetStraightStrandDebondLengthByPositionIndex)(/*[in]*/EndType endType,/*[in]*/StrandIndexType positionIndex,/*[out]*/Float64* YCoord,/*[out]*/Float64* l1,/*[out]*/Float64* l2);
	STDMETHOD(GetStraightStrandsDebondedByPositionIndex)(/*[in]*/EndType endType,/*[in]*/Float64 distFromStart, /*[out,retval]*/IIndexArray** positionIndexes);

	STDMETHOD(get_StraightStrandRowsWithStrand)(/*[out,retval]*/RowIndexType* nRows);
	STDMETHOD(get_NumStraightStrandsInRow)(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/StrandIndexType* nStrands);
	STDMETHOD(get_StraightStrandsInRow)(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/IIndexArray** grdIndexes);
   STDMETHOD(get_StraightStrandDebondInRow)(/*[in]*/ RowIndexType rowIdx,/*[out,retval]*/StrandIndexType* nStrands);
   STDMETHOD(IsExteriorStraightStrandDebondedInRow)(/*[in]*/ RowIndexType rowIndex,/*[out,retval]*/VARIANT_BOOL* bResult);

   STDMETHOD(get_HarpedStrandRowsWithStrand)(/*[out,retval]*/RowIndexType* nRows);
   STDMETHOD(get_HarpedStrandsInRow)(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/IIndexArray** gridIndexes);
   STDMETHOD(get_NumHarpedStrandsInRow)(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/StrandIndexType* nStrands);

	STDMETHOD(GetStraightStrandDebondAtSections)(/*[out]*/IDblArray** arrLeft,/*[out]*/IDblArray** arrRight);
	STDMETHOD(GetStraightStrandDebondAtLeftSection)(/*[in]*/SectionIndexType sectionIdx,/*[out,retval]*/IIndexArray** pstnIndexes);
	STDMETHOD(GetStraightStrandDebondAtRightSection)(/*[in]*/SectionIndexType sectionIdx,/*[out,retval]*/IIndexArray** pstnIndexes);

   STDMETHOD(GetStraightStrandBondedLengthByPositionIndex)(/*[in]*/StrandIndexType positionIndex, /*[in]*/Float64 distFromStart, 
                                                /*[out]*/Float64* YCoord, /*[out]*/Float64* leftBond, /*[out]*/Float64* rightBond);
   STDMETHOD(GetStraightStrandBondedLengthByGridIndex)(/*[in]*/GridIndexType grdIndex, /*[in]*/Float64 distFromStart, 
                                               /*[out]*/Float64* YCoord, /*[out]*/Float64* leftBond, /*[out]*/Float64* rightBond);

   STDMETHOD(get_RebarLayout)(/*[out,retval]*/IRebarLayout** rebarLayout);
};

#endif //__PRECASTGIRDER_H_
