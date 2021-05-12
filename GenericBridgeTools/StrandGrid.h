///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2021  Washington State Department of Transportation
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

// StrandGrid.h : Declaration of the CStrandGrid

#ifndef __STRANDGRID_H_
#define __STRANDGRID_H_

#include "resource.h"       // main symbols

#include <GeometricPrimitives\Primitives.h>
#include <vector>
#include <set>
#include <MathEx.h>

/////////////////////////////////////////////////////////////////////////////
// CStrandGrid
class ATL_NO_VTABLE CStrandGrid : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStrandGrid, &CLSID_StrandGrid>,
	public ISupportErrorInfo,
	public IStrandGrid,
	public IStrandGridFiller,
   public IObjectSafetyImpl<CStrandGrid,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CStrandGrid()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_STRANDGRID)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrandGrid)
	COM_INTERFACE_ENTRY(IStrandGrid)
	COM_INTERFACE_ENTRY(IStrandGridFiller)
	COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStrandGrid
public:
   // Grid points represent holes where strands can go
   // Grid points use a compacted numbering sequence where points with positive X values
   // are placed symmetrically (e.g., represent two actual strand locations)
   // Grid points are in Girder Section Coordinates (0,0 is at top center of girder)
   STDMETHOD(AddGridPoint)(/*[in]*/IPoint2d* point) override;
   STDMETHOD(AddGridPoints)(/*[in]*/IPoint2dCollection* points) override;
   STDMETHOD(get_GridPointCount)(/*[out,retval]*/GridIndexType* count) override;
   STDMETHOD(get_GridPoint)(/*[in]*/ GridIndexType idx,/*[out,retval]*/IPoint2d** point) override;
   STDMETHOD(get_GridPoints)(/*[out,retval]*/IPoint2dCollection** point) override;
   STDMETHOD(RemoveGridPoint)(/*[in]*/ GridIndexType idx) override;
   STDMETHOD(ClearGridPoints)() override;

   STDMETHOD(GridBoundingBox)(/*[out,retval]*/IRect2d** box) override;

// IStrandGridFiller
// Functions below have to do with filling of grid points and query for filled strands
public:      
   // Max number strands that can be filled
   STDMETHOD(get_MaxStrandCount)(/*[out,retval]*/StrandIndexType* count) override;

   // Returns a vector of integers GridPointCount long indicating the max number of strands
   // that can be placed at each Grid point (1, or 2)
   STDMETHOD(GetMaxStrandFill)(/*[out,retval]*/IIndexArray** maxFill) override;

   // Set or get vector of integers indicated number of strands filled at each Grid point
   // Possible values are 0, 1, or 2. Length of vector is GridPointCount
   // If Grid point has positive X value and 1 is input, the strand is placed at X=0.0
   // If Grid point has zero X value and 2 is input, one strand is placed at X=0.0
   STDMETHOD(get_StrandFill)(/*[out,retval]*/IIndexArray** fill) override;
   STDMETHOD(putref_StrandFill)(/*[in]*/IIndexArray* fill) override;

   STDMETHOD(putref_StrandMover)(/*[in]*/StrandGridType gridType,/*[in]*/EndType endType,/*[in]*/IStrandMover* mover) override;
   STDMETHOD(GetStrandMover)(/*[out]*/StrandGridType* gridType,/*[out]*/EndType* endType,/*[out]*/IStrandMover** mover) override;

   // Set/Get lateral and vertical offsets for the strand positions
   // This is useful when the strands aren't centered on (0,0) as assumed
   STDMETHOD(GetStrandAdjustment)(Float64* pdx,Float64* pdy) override;
   STDMETHOD(SetStrandAdjustment)(Float64 dx,Float64 dy) override;

   // Return number of currently filled strand locations
	STDMETHOD(GetStrandCount)(/*[out,retval]*/ StrandIndexType* count) override;

	STDMETHOD(RemoveAllStrands)() override;

   // Returns a collection of all currently filled strand locations
	STDMETHOD(GetStrandPositions)(/*[out,retval]*/IPoint2dCollection** points) override;

   // Convert strand index (defined in IPoint2dCollection's above) to Grid index
   STDMETHOD(StrandIndexToGridIndex)(/*[in]*/StrandIndexType pstnIndex, /*[out,retval]*/ GridIndexType* gridIndex) override;
   STDMETHOD(GridIndexToStrandIndex)(/*[in]*/ GridIndexType gridIndex, /*[out,retval]*/ StrandIndexType* strandIndex1, /*[out,retval]*/ StrandIndexType* strandIndex2) override;
   // Return CG of currently filled strands - adjusted for vertical offset
	STDMETHOD(get_CG)(/*[out]*/Float64* cgx, /*[out]*/Float64* cgy) override;

   // bounding box of adjusted strand positions
	STDMETHOD(get_StrandBoundingBox)(/*[out,retval]*/IRect2d** box) override;

   // upper and lower bounds for filled strands - position adjustments are NOT applied
	STDMETHOD(get_FilledGridBounds)(/*[out]*/Float64* bottomElev, /*[out]*/Float64* topElev) override;

   // returns the number of rows with strands
	STDMETHOD(get_RowsWithStrand)(/*[out,retval]*/RowIndexType* nRows) override;

   // returns the number of strands in a given row
	STDMETHOD(get_NumStrandsInRow)(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/StrandIndexType* nStrands) override;

   // returns unadjusted elevation of strand row
	STDMETHOD(get_StrandRowElevation)(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/Float64* pElevation) override;

   // returns the strand positions that are filled within a row
	STDMETHOD(get_StrandsInRow)(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/IIndexArray** ppStrandIndicies) override;

   // Ex methods are typically for testing a new fill.
   // they allow input of a temporary fill array. Internal fill array is not changed
	STDMETHOD(GetStrandCountEx)(/*[in]*/IIndexArray* fill, /*[out,retval]*/ StrandIndexType* count) override;
	STDMETHOD(GetStrandPositionsEx)(/*[in]*/IIndexArray* fill, /*[out,retval]*/IPoint2dCollection** points) override;
	STDMETHOD(get_CGEx)(/*[in]*/IIndexArray* fill,/*[out]*/Float64* cgx, /*[out]*/Float64* cgy) override;
	STDMETHOD(get_StrandBoundingBoxEx)(/*[in]*/IIndexArray* fill, /*[out,retval]*/IRect2d** box) override;
	STDMETHOD(get_FilledGridBoundsEx)(/*[in]*/IIndexArray* fill, /*[out]*/Float64* bottomElev, /*[out]*/Float64* topElev) override;
   STDMETHOD(StrandIndexToGridIndexEx)(/*[in]*/IIndexArray* fill, /*[in]*/ StrandIndexType strandIndex, /*[out,retval]*/ GridIndexType* gridIndex) override;

   // Debonding
	STDMETHOD(DebondStrandByGridIndex)(/*[in]*/GridIndexType grdIndex,/*[in]*/Float64 l1,/*[in]*/Float64 l2) override;
	STDMETHOD(GetDebondedStrandsByGridIndex)(/*[out,retval]*/IIndexArray** grdIndexes) override;
	STDMETHOD(GetDebondLengthByGridIndex)(/*[in]*/GridIndexType grdIndex,/*[out*/Float64* XCoord,/*[out]*/Float64* YCoord, /*[out]*/Float64* l1,/*[out]*/Float64* l2) override;

   // rough count of debonded strands for current fill
   STDMETHOD(GetStrandDebondCount)(/*[in]*/ WDebondLocationType loc, /*[out,retval]*/ StrandIndexType* count) override;

   // Debonded  strands based on Positions index (i.e., from get_StrandPositions)
	STDMETHOD(GetDebondLengthByPositionIndex)(/*[in]*/StrandIndexType positionIndex,/*[out*/Float64* XCoord,/*[out]*/Float64* YCoord, /*[out]*/Float64* l1,/*[out]*/Float64* l2) override;
	STDMETHOD(GetStrandsDebondedByPositionIndex)(/*[in]*/Float64 distFromStart,/*[in]*/Float64 girderLength, /*[out,retval]*/IIndexArray** positionIndexes) override;

   STDMETHOD(GetBondedLengthByPositionIndex)(/*[in]*/StrandIndexType positionIndex, /*[in]*/Float64 distFromStart, /*[in]*/Float64 girderLength,
      /*[out*/Float64* XCoord,/*[out]*/Float64* YCoord, /*[out]*/Float64* leftBond, /*[out]*/Float64* rightBond);

   STDMETHOD(GetBondedLengthByGridIndex)(/*[in]*/GridIndexType grdIndex, /*[in]*/Float64 distFromStart, /*[in]*/Float64 girderLength,
      /*[out*/Float64* XCoord,/*[out]*/Float64* YCoord, /*[out]*/Float64* leftBond, /*[out]*/Float64* rightBond);

	STDMETHOD(get_StrandDebondInRow)(/*[in]*/ RowIndexType rowIdx,/*[out,retval]*/StrandIndexType* nStrands) override;
	STDMETHOD(IsExteriorStrandDebondedInRow)(/*[in]*/ RowIndexType rowIndex,/*[out,retval]*/VARIANT_BOOL* bResult) override;

	STDMETHOD(GetDebondSections)(/*[out]*/IDblArray** arrLeft,/*[out]*/IDblArray** arrRight) override;
	STDMETHOD(GetDebondAtLeftSection)(/*[in]*/SectionIndexType sectionIdx,/*[out,retval]*/IIndexArray** strandIndexes) override;
	STDMETHOD(GetDebondAtRightSection)(/*[in]*/SectionIndexType sectionIdx,/*[out,retval]*/IIndexArray** strandIndexes) override;

   STDMETHOD(GetDebondedRows)(/*[out]*/IIndexArray** ppRowIndexes); // returns the indicies of rows that have debonded strands
   STDMETHOD(GetDebondedConfigurationCountByRow)(/*[in]*/RowIndexType rowIdx, /*[out]*/IndexType* pConfigCount); // returns number of different debonding configurations in this row
   STDMETHOD(GetDebondConfigurationByRow)(/*[in]*/RowIndexType rowIdx, /*[in]*/IndexType configIdx, /*[out]*/Float64* pLdbStart, /*[out]*/Float64* pLdbEnd, /*[out]*/Float64* pCgX, /*[out]*/Float64* pCgY, /*[out]*/IndexType* pnStrands); // returns a debonding configuration in this row

	STDMETHOD(ClearDebonding)() override;


private: // methods
   void InvalidateGrid();
   void ValidateGrid();
   void InvalidateFill();
   HRESULT ValidateFill();

   void AdjustStrand(Float64 originalX, Float64 originalY, Float64* newXLeft,Float64* newXRight, Float64* newY );

private:

   // grid data (empty points)
   struct GridPoint2d
   {
      Float64    dPointX;
      Float64    dPointY;
      StrandIndexType nStrandsAtGridPoint; // number of strands at this grid point (0,1, or 2)
      StrandIndexType StrandPositionIndex[2]; // strand position index for the 1 or 2 strands for this grid point (undefined if nStrandsAtGridPoint is 0)
      bool bIsDebonded;
      Float64 DebondLength[2]; // both ends of the strand (undefined if nStrandsAtGridPoint == 0)

      GridPoint2d() : dPointX(0.0), dPointY(0.0), nStrandsAtGridPoint(0), bIsDebonded(false){}
      GridPoint2d(Float64 x, Float64 y) : dPointX(x),dPointY(y), nStrandsAtGridPoint(0), bIsDebonded(false) {}

      bool operator==(const GridPoint2d& rOther)
      { return dPointX == rOther.dPointX && dPointY == rOther.dPointY && nStrandsAtGridPoint == rOther.nStrandsAtGridPoint; }
   };

   typedef std::vector<GridPoint2d> GridCollection;
   typedef GridCollection::iterator GridCollectionIterator;
   GridCollection m_GridPoints;

   bool m_bUpdateGrid;
   CComPtr<IRect2d> m_GridBoundingBox;
   CComPtr<IIndexArray> m_MaxFill;
   StrandIndexType m_MaxCount;

   // filled strands
   // rows where grid points lie
   struct Row
   {
      Float64 Elevation;

      // grid points that make up this row
      typedef std::vector<GridIndexType> GridPointsType;
      GridPointsType GridPoints;

      bool operator==(const Row& rOther) const
      { 
         return ::IsEqual(Elevation,rOther.Elevation,1.0e-04); 
      }

      bool operator<(const Row& rOther) const 
      { 
         return Elevation+1.0e-04 < rOther.Elevation; 
      }
   };

   // defines a section in the girder
   // where strands become bonded
   struct DebondSection
   {
      Float64 Location;
      typedef std::set<GridIndexType> GridPointsType;
      GridPointsType GridPoints; // indicies of grid points that contain debonded strands at this section
      bool operator==(const DebondSection& rOther) const { ::IsEqual(Location,rOther.Location); }
      bool operator<(const DebondSection& rOther) const { return Location < rOther.Location; }
   };

   void AddDebondSection(GridIndexType gridIdx,Float64 left,Float64 right);

   std::set<DebondSection> m_LeftSections, m_RightSections;
   std::set<Row> m_Rows;

   bool m_bUpdateFill;
   CComPtr<IIndexArray> m_CurrentFill; // array of strand position indicies for the strands that are actually used
   std::vector<GridIndexType>  m_StrandToGridMap; // index into array is a strand index, value stored in array is corresponding grid point index
   
   // Strand grid adjustments
   Float64 m_Xadj; // offsets entire strand grid horizontally
   Float64 m_Yadj; // offsets entire strand grid verticaly

   StrandIndexType GetStrandCount();

   // helper function for GetDebondAtLeftSection and GetDebondAtRightSection
   HRESULT GetDebondAtSection(DebondSection& rSection,/*[out,retval]*/IIndexArray** strandIndexes);

   CComPtr<IStrandMover> m_pStrandMover;
   StrandGridType m_StrandGridType;
   EndType m_EndType;

   // geometry factory for performance
   CComPtr<IPoint2dFactory> m_Point2dFactory;

   bool EvenStrandsOnLeft(IndexType gridIdx) const;
   bool IsLeftStrandPosition(GridPoint2d& gridPoint, IndexType positionIndex, bool bEvenStrandsOnLeft) const;
};

#endif //__STRANDGRID_H_
