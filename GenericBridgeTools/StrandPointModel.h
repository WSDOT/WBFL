///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2025  Washington State Department of Transportation
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

// StrandPointModel.h : Declaration of the CStrandPointModel

#pragma once

#include "resource.h"       // main symbols
#include "StrandModelBase.h"
#include <GenericBridge\Helpers.h>
#include <map>
#include <set>

/////////////////////////////////////////////////////////////////////////////
// CStrandGridModel
class ATL_NO_VTABLE CStrandPointModel :
   public CComObjectRootEx<CComSingleThreadModel>,
   public CComCoClass<CStrandPointModel, &CLSID_StrandPointModel>,
   public CStrandModelBase,
   public IStrandPointModel,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CStrandPointModel,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CStrandPointModel()
	{
   }

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_STRANDPOINTMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrandPointModel)
   COM_INTERFACE_ENTRY(IStrandModel)
   COM_INTERFACE_ENTRY(IStrandPointModel)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   // Record of each individual strand
   struct StrandRecord
   {
      StrandRecord(Float64 X, Float64 Ys, Float64 Yhp1, Float64 Yhp2, Float64 Ye, VARIANT_BOOL vbExtendedLeft, VARIANT_BOOL vbExtendedRight, Float64 debondLeft, Float64 debondRight);
      Float64 X; // horizontal position of strand in Girder Section Coordinates
      std::array<Float64, 4> Y; // vertical position of strand in Girder Section Coordinates
      std::array<VARIANT_BOOL, 2> Extended;
      std::array<Float64, 2> Debond; // location of where bonding starts, measured from left end of girder
   };
   std::array<std::vector<StrandRecord>, 3> m_Strands; // array index is strand type
                                                       
   // Debond sections are locations from the ends of the girder where debonding occurs
   // Typically, more than one strand is debonded at a location.
   // DebondSectionRecord keeps track of all the strands that are debonded at
   // a commond location
   struct DebondSectionRecord
   {
      Float64 Z; // distance from end of girder to this debond section
      std::vector<StrandIndexType> Strands; // indexes of strands that begin bond at this section
      bool operator<(const DebondSectionRecord& dsRecord) const { return Z < dsRecord.Z; }
   };
   std::array<std::array<std::set<DebondSectionRecord>, 3>, 2> m_DebondSections;

   // Strand rows are groups of strands at the same elevation.
   // Typically, strands are defined in horizontal rows.
   // RowRecord keeps track of all the strands at a common elevation
   struct RowRecord
   {
      Float64 Y; // elevation of row in Girder Section Coordinates
      std::vector<StrandIndexType> Strands; // indexes of strands that are in this row
      bool operator<(const RowRecord& row) const { return Y < row.Y; }
   };
   std::array<std::map<Float64, std::set<RowRecord>>, 3> m_StrandRows;
   std::set<RowRecord>& GetStrandRows(StrandType strandType, Float64 Xs);

   struct STRANDDEBONDRECORD
   {
      Float64 LdbStart;
      Float64 LdbEnd;
      Float64 XSum;
      Float64 YSum;
      StrandIndexType nStrands;
   };

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStrandModel
public:
   STDMETHOD(Initialize)(ISuperstructureMemberSegment* segment,IPrecastGirder* pGirder) override { return CStrandModelBase::Initialize(segment,pGirder); }
   STDMETHOD(putref_StrandMaterial)(StrandType strandType, IPrestressingStrand* pMaterial) override { return CStrandModelBase::putref_StrandMaterial(strandType, pMaterial); }
   STDMETHOD(get_StrandMaterial)(StrandType strandType, IPrestressingStrand** ppMaterial) override { return CStrandModelBase::get_StrandMaterial(strandType, ppMaterial); }

   STDMETHOD(SetHarpingPoints)(Float64 hp1, Float64 hp2) override { return CStrandModelBase::SetHarpingPoints(hp1, hp2); }
   STDMETHOD(GetHarpingPoints)(Float64* hp1, Float64* hp2) override { return CStrandModelBase::GetHarpingPoints(hp1, hp2); }
   STDMETHOD(SetEndHarpingPoints)(Float64 hp1, Float64 hp2) override { return CStrandModelBase::SetEndHarpingPoints(hp1, hp2); }
   STDMETHOD(GetEndHarpingPoints)(Float64* hp1, Float64* hp2) override { return CStrandModelBase::GetEndHarpingPoints(hp1, hp2); }
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
   STDMETHOD(GetHarpingPointLocations)(Float64* hp1, Float64* hp2) override { return CStrandModelBase::GetHarpingPointLocations(hp1, hp2); }
   STDMETHOD(GetEndHarpingPointLocations)(Float64* hp1, Float64* hp2) override { return CStrandModelBase::GetEndHarpingPointLocations(hp1, hp2); }

   STDMETHOD(put_StraightStrandProfileType)(StrandProfileType profileType) override { return CStrandModelBase::put_StraightStrandProfileType(profileType); }
   STDMETHOD(get_StraightStrandProfileType)(StrandProfileType* pProfileType) override { return CStrandModelBase::get_StraightStrandProfileType(pProfileType); }
   STDMETHOD(put_TemporaryStrandProfileType)(StrandProfileType profileType) override { return CStrandModelBase::put_TemporaryStrandProfileType(profileType); }
   STDMETHOD(get_TemporaryStrandProfileType)(StrandProfileType* pProfileType) override { return CStrandModelBase::get_TemporaryStrandProfileType(pProfileType); }

   STDMETHOD(GetStrandRowCount)(StrandType strandType, Float64 Xs, RowIndexType* nRows) override;
   STDMETHOD(GetNumStrandsInRow)(StrandType strandType, Float64 Xs, RowIndexType rowIdx, StrandIndexType* nStrands) override;
   STDMETHOD(GetStrandsInRow)(StrandType strandType, Float64 Xs, RowIndexType rowIdx, IIndexArray** ppStrandIndicies) override;
   STDMETHOD(GetUnadjustedStrandRowElevation)(StrandType strandType, Float64 Xs, RowIndexType rowIdx, Float64* fElevation) override;

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

   STDMETHOD(GetStraightStrandDebondLengthByPositionIndex)(Float64 Xs, StrandIndexType positionIndex, Float64* XCoord, Float64* YCoord, Float64* l1, Float64* l2);
   STDMETHOD(GetStraightStrandsDebondedByPositionIndex)(Float64 Xs, IIndexArray** positionIndexes) override;

   STDMETHOD(GetStraightStrandDebondCount)(WDebondLocationType loc, StrandIndexType* pCount) override;
   STDMETHOD(GetDebondingLocations)(StrandType strandType,IDblArray** arrLeft, IDblArray** arrRight) override;
   STDMETHOD(GetDebondedStrandsAtSection)(EndType endType, StrandType strandType, SectionIndexType sectionIdx, IIndexArray** pstnIndexes) override;
   STDMETHOD(get_StraightStrandDebondInRow)(Float64 Xs, RowIndexType rowIdx, StrandIndexType* nStrands) override;
   STDMETHOD(GetStraightStrandBondedLengthByPositionIndex)(StrandIndexType positionIndex, Float64 Xs, Float64* XCoord, Float64* YCoord, Float64* leftBond, Float64* rightBond);
   STDMETHOD(IsExteriorStraightStrandDebondedInRow)(Float64 Xs, RowIndexType rowIndex, VARIANT_BOOL* bResult) override;
   STDMETHOD(GetStraightStrandDebondedConfigurationCountByRow)(Float64 Xs, RowIndexType rowIdx, IndexType* pConfigCount) override;
   STDMETHOD(GetStraightStrandDebondConfigurationByRow)(Float64 Xs, RowIndexType rowIdx, IndexType configIdx, Float64* pXstart, Float64* pBondedLength, Float64* pCgX, Float64* pCgY, IndexType* pnStrands) override;
   STDMETHOD(GetStraightStrandDebondedRows)(Float64 Xs, IIndexArray** ppRowIndexes) override;

// IStrandPointModel
public:
   STDMETHOD(AddStraightStrand)(Float64 X, Float64 Ys, Float64 Ye, VARIANT_BOOL vbExtendedStart, VARIANT_BOOL vbExtendedEnd, Float64 debondLeft, Float64 debondRight) override;
   STDMETHOD(AddHarpedStrand)(Float64 X, Float64 Ys, Float64 Yhp1, Float64 Yhp2, Float64 Ye) override;
   STDMETHOD(AddTemporaryStrand)(Float64 X, Float64 Ys, Float64 Ye) override;

private:
   HRESULT AddStrand(StrandType strandType, Float64 X, Float64 Ys, Float64 Yhp1, Float64 Yhp2, Float64 Ye, VARIANT_BOOL vbExtendedLeft, VARIANT_BOOL vbExtendedRight, Float64 debondLeft, Float64 debondRight);
   HRESULT GetStrandBoundingBox(StrandType strandType, int location, IRect2d** ppBoundingBox);
   void RemoveDebondedStrandPositions(StrandType strandType,Float64 Xs, IPoint2dCollection* pPoints);
   void GetStrandControlPoints(Float64 Xs, StrandType strandType, const StrandRecord& strandRecord, Float64* pZ1, Float64* pY1, Float64* pZ2, Float64* pY2,ZoneType* pZone) const;
   ZoneType GetZone(Float64 Xs, StrandType strandType) const;
   Float64 GetStrandSlope(Float64 Xs, StrandType strandType,const StrandRecord& strandRecord) const;
   std::vector<STRANDDEBONDRECORD> GetStraightStrandDebondedConfigurations(RowIndexType rowIdx);
   Float64 GetSectionHeight(Float64 Xs) const;
   Float64 GetGirderDepthAdjustment(Float64 Xs) const;

   HRESULT GetStrandPosition(StrandType strandType, StrandIndexType strandIdx, Float64 Xs, IPoint2d** ppPoint) const;
};
