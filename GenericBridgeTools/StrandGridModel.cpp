///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2024  Washington State Department of Transportation
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

// StrandGridModel.cpp : Implementation of CStrandGridModel
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "StrandGridModel.h"
#include "Helpers.h"

#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// In Girder Section Coordinates (anytime we cut a section through the girder)
// the elevation of strands with a Linear profile need to adjusted by -precamber.
// 
// In Girder Profile Coordinates (anytime we are getting profile or side view information)
// the elevation of strands with a FollowGirder profile need to be adjusted by +precamber.
// Also, the position of harp point grids need to be adjusted by precamber. These
// grids are not anchored to the ends of the girder like straight and temporary strands.
/////////////////////////////////////////////////////////////////////////////

// CStrandGridModel
HRESULT CStrandGridModel::FinalConstruct()
{
   HRESULT hr = m_StraightGrid[etStart].CoCreateInstance(CLSID_StrandGrid);
   if ( FAILED(hr) )
      return hr;

   hr = m_StraightGrid[etEnd].CoCreateInstance(CLSID_StrandGrid);
   if ( FAILED(hr) )
      return hr;

   hr = m_HarpGridEnd[etStart].CoCreateInstance(CLSID_StrandGrid);
   if ( FAILED(hr) )
      return hr;

   hr = m_HarpGridEnd[etEnd].CoCreateInstance(CLSID_StrandGrid);
   if ( FAILED(hr) )
      return hr;

   hr = m_HarpGridHp[etStart].CoCreateInstance(CLSID_StrandGrid);
   if ( FAILED(hr) )
      return hr;

   hr = m_HarpGridHp[etEnd].CoCreateInstance(CLSID_StrandGrid);
   if ( FAILED(hr) )
      return hr;

   hr = m_TempGrid[etStart].CoCreateInstance(CLSID_StrandGrid);
   if ( FAILED(hr) )
      return hr;

   hr = m_TempGrid[etEnd].CoCreateInstance(CLSID_StrandGrid);
   if ( FAILED(hr) )
      return hr;

   m_UpdateHarpedMaxFill = true;

   m_StrandFillTool.CoCreateInstance(CLSID_StrandFillTool);

   return S_OK;
}

void CStrandGridModel::FinalRelease()
{
}

STDMETHODIMP CStrandGridModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IStrandGridModel
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CStrandGridModel::OnInitialize()
{
   HRESULT hr = CStrandModelBase::OnInitialize();
   if (FAILED(hr))
   {
      return hr;
   }

   // If we have an asymmetric section, the strands aren't lined up
   // under top center (0,0) of girder. Apply an adjustment
   // to position the strand grid correctly
   CComPtr<IShape> shape;
   m_pSegment->get_GirderShape(0.0, sbRight, cstGirder, &shape);

   CComQIPtr<IAsymmetricSection> asymmetric(shape);
   if (asymmetric)
   {
      // lateral adjustment
      Float64 twLeft, twRight;
      asymmetric->GetTopWidth(&twLeft, &twRight);
      Float64 top_width = twLeft + twRight;

      Float64 bwLeft, bwRight;
      CComQIPtr<IGirderSection> section(shape);
      section->get_BottomWidth(&bwLeft, &bwRight);
      Float64 bottom_width = bwLeft + bwRight;

      Float64 Xadj = (top_width < bottom_width) ? 0.5*(bwLeft - bwRight) : 0.5*(twLeft - twRight);

      Float64 Yadj = 0;

      for (int i = 0; i < 2; i++)
      {
         m_StraightGrid[i]->SetStrandAdjustment(Xadj, Yadj);
         m_HarpGridEnd[i]->SetStrandAdjustment(Xadj, Yadj);
         m_HarpGridHp[i]->SetStrandAdjustment(Xadj, Yadj);
         m_TempGrid[i]->SetStrandAdjustment(Xadj, Yadj);
      }
   }

   return S_OK;
}


STDMETHODIMP CStrandGridModel::SetStrandMovers(IStrandMover* pStartStrandMover,IStrandMover* pHp1StrandMover,IStrandMover* pHp2StrandMover,IStrandMover* pEndStrandMover)
{
   // harped strands can be moved at the end and harping points. How they movei is controlled by the strand mover
   m_HarpGridEnd[etStart]->putref_StrandMover(sgtEnd,etStart,pStartStrandMover);
   m_HarpGridEnd[etEnd]->putref_StrandMover(sgtEnd,etEnd,pEndStrandMover);

   m_HarpGridHp[etStart]->putref_StrandMover(sgtHarpPoint,etStart,pHp1StrandMover);
   m_HarpGridHp[etEnd]->putref_StrandMover(sgtHarpPoint,etEnd,pHp2StrandMover);

   m_CGs[Harped].clear();
   
   return S_OK;
}

STDMETHODIMP CStrandGridModel::putref_StrandMover(StrandGridType sgType,EndType endType,IStrandMover* strandMover)
{
   CHECK_IN(strandMover);

   if ( sgType == sgtEnd )
   {
      m_HarpGridEnd[endType]->putref_StrandMover(sgtEnd,endType,strandMover);
   }
   else
   {
      m_HarpGridHp[endType]->putref_StrandMover(sgtHarpPoint, endType,strandMover);
   }

   m_CGs[Harped].clear();

   return S_OK;
}

STDMETHODIMP CStrandGridModel::get_StrandMover(StrandGridType sgType,EndType endType,IStrandMover** ppStrandMover)
{
   CHECK_RETOBJ(ppStrandMover);

   if ( sgType == sgtEnd )
   {
      StrandGridType gt;
      EndType et;
      m_HarpGridEnd[endType]->GetStrandMover(&gt,&et,ppStrandMover);
      ATLASSERT(gt == sgType);
      ATLASSERT(et == endType);
   }
   else
   {
      StrandGridType gt;
      EndType et;
      m_HarpGridHp[endType]->GetStrandMover(&gt,&et,ppStrandMover);
      ATLASSERT(gt == sgType);
      ATLASSERT(et == endType);
   }

   return S_OK;
}

STDMETHODIMP CStrandGridModel::GetStrandPositions(StrandType strandType,Float64 Xs, IPoint2dCollection** points)
{
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = GetStraightStrandPositions(Xs, nullptr, points);
      break;
      
   case Harped:
      hr = GetHarpedStrandPositions(Xs, nullptr, points);
      break;

   case Temporary:
      hr = GetTemporaryStrandPositions(Xs, nullptr, points);
      break;

   default:
      ATLASSERT(false); // is there a new type?
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::GetStrandCG(StrandType strandType, Float64 Xs, IPoint2d** pntCG)
{
   return GetStrandCGEx(strandType, Xs, nullptr, pntCG);
}

STDMETHODIMP CStrandGridModel::GetStrandCGEx(StrandType strandType, Float64 Xs, IIndexArray* fill, IPoint2d** pntCG)
{
   CHECK_RETVAL(pntCG);

   if (fill == nullptr)
   {
      // look in the cache
      const auto found = m_CGs[strandType].find(Xs);
      if (found != m_CGs[strandType].end())
      {
         // we found the CG we want in our cache.
         // return it.
         return found->second.CopyTo(pntCG);
      }
   }

   CComPtr<IPoint2dCollection> points;
   GetStrandPositionsEx(strandType, Xs, fill, &points);
   if (strandType == Straight)
   {
      RemoveStraightStrandDebondedStrandPositions(Xs, points);
   }
   GetCGFromPoints(points, pntCG);

   if (fill == nullptr)
   {
      // add to our cache
      auto result = m_CGs[strandType].insert(std::make_pair(Xs, *pntCG));
      ATLASSERT(result.second == true);
   }
   return S_OK;
}

STDMETHODIMP CStrandGridModel::GetStrandCount(StrandType strandType, StrandIndexType* pStrands)
{
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = GetStraightStrandCount(nullptr, pStrands);
      break;

   case Harped:
      hr = GetHarpedStrandCount(nullptr, pStrands);
      break;

   case Temporary:
      hr = GetTemporaryStrandCount(nullptr, pStrands);
      break;

   default:
      ATLASSERT(false); // is there a new type?
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::GetStrandPositionsEx(StrandType strandType,Float64 Xs, IIndexArray* fill, IPoint2dCollection** points)
{
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = GetStraightStrandPositions(Xs, fill, points);
      break;

   case Harped:
      hr = GetHarpedStrandPositions(Xs, fill, points);
      break;

   case Temporary:
      hr = GetTemporaryStrandPositions(Xs, fill, points);
      break;

   default:
      ATLASSERT(false); // is there a new type?
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::GetStrandCountEx(StrandType strandType, IIndexArray* fill,StrandIndexType* pStrands)
{
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = GetStraightStrandCount(fill, pStrands);
      break;

   case Harped:
      hr = GetHarpedStrandCount(fill, pStrands);
      break;

   case Temporary:
      hr = GetTemporaryStrandCount(fill, pStrands);
      break;

   default:
      ATLASSERT(false); // is there a new type?
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::get_StraightStrandGrid(EndType endType,IStrandGrid** grid)
{
   CHECK_RETOBJ(grid);

   return m_StraightGrid[endType].QueryInterface(grid);
}

STDMETHODIMP CStrandGridModel::get_TemporaryStrandGrid(EndType endType,IStrandGrid** grid)
{
   CHECK_RETOBJ(grid);

   return m_TempGrid[endType].QueryInterface(grid);
}

STDMETHODIMP CStrandGridModel::get_HarpedStrandGridEnd(EndType endType,IStrandGrid** grid)
{
   CHECK_RETOBJ(grid);

   return m_HarpGridEnd[endType].QueryInterface(grid);
}

STDMETHODIMP CStrandGridModel::get_HarpedStrandGridHP(EndType endType,IStrandGrid** grid)
{
   CHECK_RETOBJ(grid);

   return m_HarpGridHp[endType].QueryInterface(grid);
}

STDMETHODIMP CStrandGridModel::put_AllowOddNumberOfHarpedStrands(VARIANT_BOOL bUseMin)
{
   m_AllowOddNumberOfHarpedStrands = bUseMin;

   if (bUseMin == VARIANT_TRUE)
   {
      // temporary fill array for harped fill at hp - only used if odd is true
      if (!m_OddHpFill)
      {
         m_OddHpFill.CoCreateInstance(CLSID_IndexArray);
      }
   }

   m_CGs[Harped].clear();

   return S_OK;
}

STDMETHODIMP CStrandGridModel::get_AllowOddNumberOfHarpedStrands(VARIANT_BOOL* bUseMin)
{
   *bUseMin = m_AllowOddNumberOfHarpedStrands;
   return S_OK;
}

STDMETHODIMP CStrandGridModel::put_UseDifferentHarpedGridsAtEnds(VARIANT_BOOL bUseDifferent)
{
   m_UseDifferentHarpedGirdAtEnds = bUseDifferent;
   m_CGs[Harped].clear();
   return S_OK;
}

STDMETHODIMP CStrandGridModel::get_UseDifferentHarpedGridsAtEnds(VARIANT_BOOL* bUseDifferent)
{
   *bUseDifferent = m_UseDifferentHarpedGirdAtEnds;
   return S_OK;
}

STDMETHODIMP CStrandGridModel::get_HarpedStrandAdjustmentEnd(EndType endType,Float64* offset)
{
   Float64 dx;
   return m_HarpGridEnd[endType]->GetStrandAdjustment(&dx,offset);
}

STDMETHODIMP CStrandGridModel::put_HarpedStrandAdjustmentEnd(EndType endType,Float64 offset)
{
   // cannot adjust if increment is less than zero
   Float64 increment, dummy;
   CComPtr<IStrandMover> strandMover;
   get_StrandMover(sgtEnd,endType,&strandMover);
   strandMover->get_StrandIncrements(&increment, &dummy);

   Float64 dx, dy;
   m_HarpGridEnd[endType]->GetStrandAdjustment(&dx,&dy);

   HRESULT hr;
   if (increment<0.0 && !IsZero(offset))
   {
      ATLASSERT(false); // cannot adjust if increment<0.0
      m_HarpGridEnd[endType]->SetStrandAdjustment(dx,0.0);
      hr = E_INVALIDARG;
   }
   else
   {
      m_HarpGridEnd[endType]->SetStrandAdjustment(dx,offset);
      hr = S_OK;
   }

   m_CGs[Harped].clear();
   return hr;
}

STDMETHODIMP CStrandGridModel::get_HarpedStrandAdjustmentHP(EndType endType,Float64* offset)
{
   Float64 dx;
   return m_HarpGridHp[endType]->GetStrandAdjustment(&dx,offset);
}

STDMETHODIMP CStrandGridModel::put_HarpedStrandAdjustmentHP(EndType endType,Float64 offset)
{
   // cannot adjust if increment is less than zero
   Float64 increment, dummy;
   CComPtr<IStrandMover> strandMover;
   get_StrandMover(sgtHarpPoint,endType,&strandMover);
   strandMover->get_StrandIncrements(&increment, &dummy);

   Float64 dx, dy;
   m_HarpGridHp[endType]->GetStrandAdjustment(&dx,&dy);

   HRESULT hr;
   if (increment<0.0 && !IsZero(offset))
   {
      ATLASSERT(false); // cannot adjust if increment<0.0
      m_HarpGridHp[endType]->SetStrandAdjustment(dx,0.0);
      hr = E_INVALIDARG;
   }
   else
   {
      m_HarpGridHp[endType]->SetStrandAdjustment(dx,offset);
      hr = S_OK;
   }
   m_CGs[Harped].clear();
   return hr;
}

STDMETHODIMP CStrandGridModel::GetMaxStrandFill(StrandType strandType,IIndexArray** fill)
{
   CHECK_RETOBJ(fill);
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = m_StraightGrid[etStart]->GetMaxStrandFill(fill);
      break;

   case Harped:
   {
      UpdateMaxStrandFill();
      hr = m_HarpedMaxStrandFill.CopyTo(fill);
   }
   break;

   case Temporary:
      hr = m_TempGrid[etStart]->GetMaxStrandFill(fill);
      break;

   default:
      ATLASSERT(false);
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CStrandGridModel::putref_StrandFill(StrandType strandType, IIndexArray* fill)
{
   CHECK_IN(fill);
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = PutRefStraightStrandFill(fill);
      break;

   case Harped:
      hr = PutRefHarpedStrandFill(fill);
      break;

   case Temporary:
      hr = PutRefTemporaryStrandFill(fill);
      break;

   default:
      ATLASSERT(false);
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CStrandGridModel::get_StrandFill(StrandType strandType, IIndexArray** fill)
{
   CHECK_RETOBJ(fill);
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = m_StraightGrid[etStart]->get_StrandFill(fill);
      break;

   case Harped:
      hr = m_HarpGridEnd[etStart]->get_StrandFill(fill);
      break;

   case Temporary:
      hr = m_TempGrid[etStart]->get_StrandFill(fill);
      break;

   default:
      ATLASSERT(false);
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CStrandGridModel::StrandIndexToGridIndex(StrandType strandType,StrandIndexType strandIndex, GridIndexType* gridIndex)
{
   CHECK_RETVAL(gridIndex);
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = m_StraightGrid[etStart]->StrandIndexToGridIndex(strandIndex, gridIndex);
      break;

   case Harped:
      hr = m_HarpGridEnd[etStart]->StrandIndexToGridIndex(strandIndex, gridIndex);
      break;

   case Temporary:
      hr = m_TempGrid[etStart]->StrandIndexToGridIndex(strandIndex, gridIndex);
      break;

   default:
      ATLASSERT(false);
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CStrandGridModel::StrandIndexToGridIndexEx(StrandType strandType,IIndexArray* fill, StrandIndexType strandIndex, GridIndexType* gridIndex)
{
   CHECK_RETVAL(gridIndex);
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = m_StraightGrid[etStart]->StrandIndexToGridIndexEx(fill, strandIndex, gridIndex);
      break;

   case Harped:
      hr = m_HarpGridEnd[etStart]->StrandIndexToGridIndexEx(fill, strandIndex, gridIndex);
      break;

   case Temporary:
      hr = m_HarpGridEnd[etStart]->StrandIndexToGridIndexEx(fill, strandIndex, gridIndex);
      break;

   default:
      ATLASSERT(false);
      hr = E_FAIL;
   }
   return hr;
}

// Compute bounding boxes of harped and straight strands accounting for vertical offsets for harped strands
STDMETHODIMP CStrandGridModel::StraightStrandBoundingBox(EndType endType,IRect2d** box)
{
   return m_StraightGrid[endType]->get_StrandBoundingBox(box);
}

STDMETHODIMP CStrandGridModel::StraightStrandBoundingBoxEx( EndType endType,IIndexArray* fill, IRect2d** box)
{
   return m_StraightGrid[endType]->get_StrandBoundingBoxEx(fill, box);
}

STDMETHODIMP CStrandGridModel::HarpedEndStrandBoundingBox(EndType endType,IRect2d** box)
{
   return m_HarpGridEnd[endType]->get_StrandBoundingBox(box);
}

STDMETHODIMP CStrandGridModel::HarpedEndStrandBoundingBoxEx( EndType endType,IIndexArray* fill, IRect2d** box)
{
   return m_HarpGridEnd[endType]->get_StrandBoundingBoxEx(fill, box);
}


STDMETHODIMP CStrandGridModel::HarpedHpStrandBoundingBox(EndType endType,IRect2d** box)
{
   return m_HarpGridHp[endType]->get_StrandBoundingBox(box);
}

STDMETHODIMP CStrandGridModel::HarpedHpStrandBoundingBoxEx(EndType endType, IIndexArray* fill, IRect2d** box)
{
   // compute harped fill at hp
   CComPtr<IIndexArray> hp_fill;
   HRESULT hr = ComputeHpFill(fill, &hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   return m_HarpGridHp[endType]->get_StrandBoundingBoxEx(hp_fill, box);
}

STDMETHODIMP CStrandGridModel::GetStrandRowCount(StrandType strandType, Float64 Xs, RowIndexType* nRows)
{
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = m_StraightGrid[etStart]->get_RowsWithStrand(nRows);
      break;

   case Harped:
   {
      CComPtr<IStrandGridFiller> grid;
      GetHarpedStrandGrid(Xs, &grid);
      hr = grid->get_RowsWithStrand(nRows);
   }
      break;

   case Temporary:
      hr =  m_TempGrid[etStart]->get_RowsWithStrand(nRows);
      break;

   default:
      ATLASSERT(false);
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::GetNumStrandsInRow(StrandType strandType, Float64 Xs, RowIndexType rowIdx, StrandIndexType* nStrands)
{
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = m_StraightGrid[etStart]->get_NumStrandsInRow(rowIdx, nStrands);
      break;

   case Harped:
   {
      CComPtr<IStrandGridFiller> grid;
      GetHarpedStrandGrid(Xs,&grid);
      hr = grid->get_NumStrandsInRow(rowIdx, nStrands);
   }
      break;

   case Temporary:
      hr = m_TempGrid[etStart]->get_NumStrandsInRow(rowIdx, nStrands);
      break;

   default:
      ATLASSERT(false);
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::GetUnadjustedStrandRowElevation(StrandType strandType, Float64 Xs, RowIndexType rowIdx, Float64* pElevation)
{
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = m_StraightGrid[etStart]->get_StrandRowElevation(rowIdx, pElevation);
      break;

   case Harped:
   {
      CComPtr<IStrandGridFiller> grid;
      GetHarpedStrandGrid(Xs,&grid);
      hr = grid->get_StrandRowElevation(rowIdx, pElevation);
   }
      break;

   case Temporary:
      hr = m_TempGrid[etStart]->get_StrandRowElevation(rowIdx, pElevation);
      break;

   default:
      ATLASSERT(false);
   }

   return hr;
}


STDMETHODIMP CStrandGridModel::GetStrandsInRow(StrandType strandType, Float64 Xs,RowIndexType rowIdx, IIndexArray** ppStrandIndicies)
{
   CHECK_RETOBJ(ppStrandIndicies);
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = m_StraightGrid[etStart]->get_StrandsInRow(rowIdx, ppStrandIndicies);
      break;

   case Harped:
   {
      CComPtr<IStrandGridFiller> grid;
      GetHarpedStrandGrid(Xs, &grid);
      hr = grid->get_StrandsInRow(rowIdx, ppStrandIndicies);
   }
   break;

   case Temporary:
      hr = m_TempGrid[etStart]->get_StrandsInRow(rowIdx, ppStrandIndicies);
      break;

   default:
      ATLASSERT(false);
      hr = E_FAIL;
   }
   return S_OK;
}

STDMETHODIMP CStrandGridModel::get_TopElevation(Float64* top)
{
   CComPtr<IStrandMover> strandMover;
   get_StrandMover(sgtEnd,etEnd,&strandMover);
   
   return strandMover->get_TopElevation(top);
}

STDMETHODIMP CStrandGridModel::GetHarpedEndAdjustmentBounds(EndType endType,Float64* minDownwardAdjustment, Float64* maxUpwardAdjustment)
{
   CHECK_RETVAL(minDownwardAdjustment);
   CHECK_RETVAL(maxUpwardAdjustment);

   HRESULT hr(S_OK);

   CComPtr<IStrandMover> strandMover;
   get_StrandMover(sgtEnd,endType,&strandMover);

   // get unadjusted top and bottom bounds
   Float64 top, bottom;
   hr = m_HarpGridEnd[endType]->get_FilledGridBounds(&bottom,&top);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   Float64 dx, dy;
   hr = m_HarpGridEnd[endType]->GetStrandAdjustment(&dx,&dy);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   bottom -= dy;
   top    -= dy;

   if (IsZero(bottom) && IsZero(top))
   {
      // no strands exist so we cannot adjust them
      *minDownwardAdjustment = 0.0;
      *maxUpwardAdjustment   = 0.0;
   }
   else
   {
      // get max locations of strands
      Float64 bottom_min, top_max;
      hr = strandMover->get_EndStrandElevationBoundaries(endType,&bottom_min, &top_max);
      if (FAILED(hr))
      {
         ATLASSERT(false);
         return hr;
      }

      *minDownwardAdjustment = bottom_min - bottom;
      *maxUpwardAdjustment = top_max - top;

      // if these fire, strands cannot be adjusted within section bounds. this should be caught at library entry time.
      ATLASSERT(*minDownwardAdjustment <= 0.0);
      ATLASSERT(0.0 <= *maxUpwardAdjustment);
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::GetHarpedEndAdjustmentBoundsEx(EndType endType, IIndexArray* fill, Float64* minDownwardAdjustment, Float64* maxUpwardAdjustment)

{
   CHECK_RETVAL(minDownwardAdjustment);
   CHECK_RETVAL(maxUpwardAdjustment);

   HRESULT hr(S_OK);

   CComPtr<IStrandMover> strandMover;
   get_StrandMover(sgtEnd,endType,&strandMover);

   // get adjusted top and bottom bounds
   Float64 top, bottom;
   hr = m_HarpGridEnd[endType]->get_FilledGridBoundsEx(fill,&bottom,&top);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   Float64 dx,dy;
   hr = m_HarpGridEnd[endType]->GetStrandAdjustment(&dx,&dy);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   if (IsZero(bottom) && IsZero(top))
   {
      // no strands exist so we cannot adjust them
      *minDownwardAdjustment = 0.0;
      *maxUpwardAdjustment   = 0.0;
   }
   else
   {
      bottom -= dy;
      top    -= dy;

      // get max locations of strands
      Float64 bottom_min, top_max;
      hr = strandMover->get_EndStrandElevationBoundaries(endType,&bottom_min, &top_max);
      if (FAILED(hr))
      {
         ATLASSERT(false);
         return hr;
      }

      *minDownwardAdjustment = bottom_min - bottom;
      *maxUpwardAdjustment = top_max - top;

      // if these fire, strands cannot be adjusted within section bounds. this should be caught at library entry time.
      ATLASSERT(*minDownwardAdjustment<1.0e-06);
      ATLASSERT(*maxUpwardAdjustment>-1.0e-06);
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::GetHarpedHpAdjustmentBounds( EndType endType,Float64* minDownwardAdjustment, Float64* maxUpwardAdjustment)
{
   CHECK_RETVAL(minDownwardAdjustment);
   CHECK_RETVAL(maxUpwardAdjustment);

   HRESULT hr(S_OK);

   CComPtr<IStrandMover> strandMover;
   get_StrandMover(sgtHarpPoint,endType,&strandMover);

   // get unadjusted top and bottom bounds
   Float64 top, bottom;
   hr = m_HarpGridHp[endType]->get_FilledGridBounds(&bottom,&top);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   Float64 dx,dy;
   hr = m_HarpGridHp[endType]->GetStrandAdjustment(&dx,&dy);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   bottom -= dy;
   top    -= dy;

   if (IsZero(bottom) && IsZero(top))
   {
      // no strands exist so we cannot adjust them
      *minDownwardAdjustment = 0.0;
      *maxUpwardAdjustment   = 0.0;
   }
   else
   {
      // get max locations of strands
      Float64 bottom_min, top_max;
      hr = strandMover->get_HpStrandElevationBoundaries(endType,&bottom_min, &top_max);
      if (FAILED(hr))
      {
         ATLASSERT(false);
         return hr;
      }

      *minDownwardAdjustment = bottom_min - bottom;
      *maxUpwardAdjustment = top_max - top;

      // if these fire, strands cannot be adjusted within section bounds. this should be caught at library entry time.
      ATLASSERT(*minDownwardAdjustment<=0.0);
      ATLASSERT(*maxUpwardAdjustment>=0.0);
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::GetHarpedHpAdjustmentBoundsEx(EndType endType, IIndexArray* fill, Float64* minDownwardAdjustment, Float64* maxUpwardAdjustment)

{
   CHECK_RETVAL(minDownwardAdjustment);
   CHECK_RETVAL(maxUpwardAdjustment);

   HRESULT hr(S_OK);

   CComPtr<IStrandMover> strandMover;
   get_StrandMover(sgtHarpPoint,endType,&strandMover);

   // compute hp fill, if different
   CComPtr<IIndexArray> hp_fill;
   hr = ComputeHpFill(fill, &hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   // get unadjusted top and bottom bounds
   Float64 top, bottom;
   hr = m_HarpGridHp[endType]->get_FilledGridBoundsEx(hp_fill,&bottom,&top);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   Float64 dx,dy;
   hr = m_HarpGridHp[endType]->GetStrandAdjustment(&dx,&dy);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   bottom -= dy;
   top    -= dy;


   if (IsZero(bottom) && IsZero(top))
   {
      // no strands exist so we cannot adjust them
      *minDownwardAdjustment = 0.0;
      *maxUpwardAdjustment   = 0.0;
   }
   else
   {
      // get max locations of strands
      Float64 bottom_min, top_max;
      hr = strandMover->get_HpStrandElevationBoundaries(endType,&bottom_min, &top_max);
      if (FAILED(hr))
      {
         ATLASSERT(false);
         return hr;
      }

      *minDownwardAdjustment = bottom_min - bottom;
      *minDownwardAdjustment = IsZero(*minDownwardAdjustment) ? 0.00 : *minDownwardAdjustment;

      *maxUpwardAdjustment = top_max - top;
      *maxUpwardAdjustment = IsZero(*maxUpwardAdjustment) ? 0.00 : *maxUpwardAdjustment;

      // if these fire, strands cannot be adjusted within section bounds. this should be caught at library entry time.
      ATLASSERT(*minDownwardAdjustment<=0.0);
      ATLASSERT(*maxUpwardAdjustment>=0.0);
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::GetHarpedEndFilledGridBoundsEx(EndType endType,IIndexArray* fill, Float64* bottomElev, Float64* topElev)
{
   return m_HarpGridEnd[endType]->get_FilledGridBoundsEx( fill, bottomElev, topElev);
}

STDMETHODIMP CStrandGridModel::GetHarpedHpFilledGridBoundsEx(EndType endType,IIndexArray* fill, Float64* bottomElev, Float64* topElev)
{
   // compute hp fill, if different
   CComPtr<IIndexArray> hp_fill;
   HRESULT hr = ComputeHpFill(fill, &hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   return m_HarpGridHp[endType]->get_FilledGridBoundsEx( hp_fill, bottomElev, topElev);
}

STDMETHODIMP CStrandGridModel::get_HarpedEndAdjustmentIncrement(Float64* increment)
{
   StrandIndexType cnt;
   HRESULT hr = m_HarpGridEnd[etStart]->get_MaxStrandCount(&cnt);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   if (0 < cnt)
   {
      CComPtr<IStrandMover> strandMover;
      get_StrandMover(sgtEnd,etStart,&strandMover);

      Float64 dummy;
      return strandMover->get_StrandIncrements(increment, &dummy);
   }
   else
   {
      *increment = -1.0;
      return S_OK;
   }
}

STDMETHODIMP CStrandGridModel::get_HarpedHpAdjustmentIncrement(Float64* increment)
{
   StrandIndexType cnt;
   HRESULT hr = m_HarpGridEnd[etStart]->get_MaxStrandCount(&cnt);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   if (0 < cnt)
   {
      CComPtr<IStrandMover> strandMover;
      get_StrandMover(sgtEnd,etStart,&strandMover);
      Float64 dummy;
      return strandMover->get_StrandIncrements(&dummy, increment);
   }
   else
   {
      *increment = -1.0;
      return S_OK;
   }
}

STDMETHODIMP CStrandGridModel::HarpedEndStrandBoundaryCheck(EndType endType,Float64* adjustment)
{
   CHECK_RETVAL(adjustment);
   
   HRESULT hr(S_OK);

   Float64 dx,dy;
   hr = m_HarpGridEnd[endType]->GetStrandAdjustment(&dx,&dy);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   Float64 min_adjust, max_adjust;
   hr = GetHarpedEndAdjustmentBounds(endType,&min_adjust, &max_adjust);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   *adjustment = 0.0; // the default

   if (max_adjust < dy)
   {
      // too high - must adjust down
      *adjustment = max_adjust - dy;
   }
   else if (dy < min_adjust)
   {
      // too low - adjust upward
      *adjustment = min_adjust - dy;
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::HarpedHpStrandBoundaryCheck(EndType endType,Float64* adjustment)
{
   CHECK_RETVAL(adjustment);
   
   HRESULT hr(S_OK);

   Float64 dx,dy;
   hr = m_HarpGridHp[endType]->GetStrandAdjustment(&dx,&dy);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   Float64 min_adjust, max_adjust;
   hr = GetHarpedHpAdjustmentBounds(endType,&min_adjust, &max_adjust);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   *adjustment = 0.0; // the default

   if (max_adjust < dy)
   {
      // too high - must adjust down
      *adjustment = max_adjust - dy;
   }
   else if (dy < min_adjust)
   {
      // too low - adjust upward
      *adjustment = min_adjust - dy;
   }

   return hr;
}

STDMETHODIMP CStrandGridModel::ComputeMaxHarpedStrandSlope(Float64 Xs,Float64* slope)
{
   // NOTE: We tried to implement this with a call to ComputeMaxHarpedStrandSlopeEx, similar to what we did with Average slope
   // but it didn't work well. That's not to say that it can't work well. The implemention requires more analysis
   // that we have time to do right now. In the future, consider making this a call to ComputeMaxHarpedStrandSlopeEx with
   // fill = nullptr and offsets = 0.0.
   CHECK_RETVAL(slope);

   StrandIndexType nStrands;
   m_HarpGridEnd[etStart]->GetStrandCount(&nStrands);
   if (nStrands == 0)
   {
      *slope = DBL_MAX;
      return S_OK;
   }

#if defined _DEBUG
   Float64 gdrLength;
   m_pGirder->get_GirderLength(&gdrLength);
   ATLASSERT(0.0 <= Xs  && Xs <= gdrLength);
#endif

   Float64 leftEndHP, leftHP, rightHP, rightEndHP;
   GetHarpingPointLocations(&leftHP, &rightHP);
   GetEndHarpingPointLocations(&leftEndHP, &rightEndHP);

   if (::IsLT(Xs,leftEndHP) || (::IsLT(leftHP,Xs) && ::IsLT(Xs,rightHP)) || ::IsLT(rightEndHP,Xs))
   {
      // point under consideration is outside of sloped region or between harp points
      // strands are assumed to be horizonal
      *slope = DBL_MAX;
      return S_OK;
   }

   Float64 run; // as in rise over run
   CComPtr<IPoint2dCollection> start, end;
   if ( ::IsLE(Xs,leftHP) )
   {
      ATLASSERT(leftEndHP <= Xs);
      GetStrandPositions(Harped,leftEndHP,&start);
      GetStrandPositions(Harped,leftHP, &end);
      run = leftHP - leftEndHP;

      // vertical position is in girder section coordinates... (measured down from top of girder)
      // Change to a bottom up measurement based on a consistent datum at the bottom of the girder at the start
      Float64 HgLeftEndHP = GetSectionHeight(leftEndHP);
      Float64 HgLeftHP = GetSectionHeight(leftHP);

      Float64 leftEndHPprecamber, leftHPprecamber;
      m_pSegment->ComputePrecamber(leftEndHP, &leftEndHPprecamber);
      m_pSegment->ComputePrecamber(leftHP, &leftHPprecamber);

      start->Offset(0, HgLeftEndHP + leftEndHPprecamber);
      end->Offset(0, HgLeftHP + leftHPprecamber);
   }
   else
   {
      ATLASSERT(Xs <= rightEndHP);
      GetStrandPositions(Harped, rightHP,  &start);
      GetStrandPositions(Harped, rightEndHP, &end);
      run = rightEndHP - rightHP;

      // vertical position is in girder section coordinates... (measured down from top of girder)
      // Change to a bottom up measurement based on a consistent datum at the bottom of the girder at the start
      Float64 HgRightHP = GetSectionHeight(rightHP);
      Float64 HgRightEndHP = GetSectionHeight(rightEndHP);

      Float64 rightHPprecamber, rightEndHPprecamber;
      m_pSegment->ComputePrecamber(rightHP, &rightHPprecamber);
      m_pSegment->ComputePrecamber(rightEndHP, &rightEndHPprecamber);

      start->Offset(0, HgRightHP + rightHPprecamber);
      end->Offset(0, HgRightEndHP + rightEndHPprecamber);
   }

#if defined _DEBUG
   IndexType nStrandStart,nStrandEnd;
   start->get_Count(&nStrandStart);
   end->get_Count(&nStrandEnd);
   ATLASSERT(nStrandStart == nStrandEnd && nStrandStart == nStrands);
#endif

   *slope = DBL_MAX;
   for ( StrandIndexType strandIdx = 0; strandIdx < nStrands; strandIdx++ )
   {
      CComPtr<IPoint2d> pntStart, pntEnd;
      start->get_Item(strandIdx,&pntStart);
      end->get_Item(strandIdx,&pntEnd);

      Float64 ys, ye;
      pntStart->get_Y(&ys);
      pntEnd->get_Y(&ye);

      Float64 rise = ye - ys;

      if (!IsZero(rise))
      {
         // Slope is in the format 1:n (rise:run)
         // Positive slopes are upwards and towards the right
         Float64 n = run/rise;
         if ( MinIndex(fabs(*slope),fabs(n)) == 1 )
         {
            *slope = n;
         }
      }
   }

   return S_OK;
}

STDMETHODIMP CStrandGridModel::ComputeMaxHarpedStrandSlopeEx(Float64 Xs, IIndexArray* fill, Float64 startOffset, Float64 hp1Offset, Float64 hp2Offset, Float64 endOffset, Float64* slope)
{
   CHECK_RETVAL(slope);

   StrandIndexType nStrands;
   m_HarpGridEnd[etStart]->GetStrandCountEx(fill, &nStrands);
   if ( nStrands == 0 )
   {
      *slope = DBL_MAX;
      return S_OK;
   }


#if defined _DEBUG
   Float64 gdrLength;
   m_pGirder->get_GirderLength(&gdrLength);
   ATLASSERT(0.0 <= Xs  && Xs <= gdrLength);
#endif

   Float64 leftEndHP, leftHP, rightHP, rightEndHP;
   GetHarpingPointLocations(&leftHP, &rightHP);
   GetEndHarpingPointLocations(&leftEndHP, &rightEndHP);

   if (::IsLT(Xs, leftEndHP) || (::IsLT(leftHP, Xs) && ::IsLT(Xs, rightHP)) || ::IsLT(rightEndHP, Xs))
   {
      // point under consideration is outside of sloped region or between harp points
      // strands are assumed to be horizonal
      *slope = DBL_MAX;
      return S_OK;
   }

   // strand positions - adjusted for current offset value
   CComPtr<IPoint2dCollection> start, end;
   Float64 dx, curr_start_offset, curr_end_offset;
   Float64 start_offset, end_offset;
   Float64 run; // as in rise over run
   if ( ::IsLE(Xs,leftHP) )
   {
      m_HarpGridEnd[etStart]->GetStrandPositionsEx(fill, &start);
      m_HarpGridHp[etStart]->GetStrandPositionsEx(fill, &end);

      // need to subtract current offsets out so we can add our own
      m_HarpGridEnd[etStart]->GetStrandAdjustment(&dx,&curr_start_offset);
      m_HarpGridHp[etStart]->GetStrandAdjustment(&dx,&curr_end_offset);

      start_offset = startOffset;
      end_offset   = hp1Offset;

      run = leftHP - leftEndHP;


      // vertical position is in girder section coordinates... (measured down from top of girder)
      // Change to a bottom up measurement based on a consistent datum at the bottom of the girder at the start
      Float64 HgLeftEndHP = GetSectionHeight(leftEndHP);
      Float64 HgLeftHP = GetSectionHeight(leftHP);

      Float64 leftEndHPprecamber, leftHPprecamber;
      m_pSegment->ComputePrecamber(leftEndHP, &leftEndHPprecamber);
      m_pSegment->ComputePrecamber(leftHP, &leftHPprecamber);

      start->Offset(0, HgLeftEndHP + leftEndHPprecamber);
      end->Offset(0, HgLeftHP + leftHPprecamber);
   }
   else
   {
      m_HarpGridHp[etEnd]->GetStrandPositionsEx(fill, &start);
      m_HarpGridEnd[etEnd]->GetStrandPositionsEx(fill, &end);

      // need to subtract current offsets out so we can add our own
      m_HarpGridHp[etEnd]->GetStrandAdjustment(&dx,&curr_start_offset);
      m_HarpGridEnd[etEnd]->GetStrandAdjustment(&dx,&curr_end_offset);

      start_offset = hp2Offset;
      end_offset   = endOffset;

      run = rightEndHP - rightHP;

      // vertical position is in girder section coordinates... (measured down from top of girder)
      // Change to a bottom up measurement based on a consistent datum at the bottom of the girder at the start
      Float64 HgRightHP = GetSectionHeight(rightHP);
      Float64 HgRightEndHP = GetSectionHeight(rightEndHP);

      Float64 rightHPprecamber, rightEndHPprecamber;
      m_pSegment->ComputePrecamber(rightHP, &rightHPprecamber);
      m_pSegment->ComputePrecamber(rightEndHP, &rightEndHPprecamber);

      start->Offset(0, HgRightHP + rightHPprecamber);
      end->Offset(0, HgRightEndHP + rightEndHPprecamber);
   }

#if defined _DEBUG
   IndexType nStrandStart,nStrandEnd;
   start->get_Count(&nStrandStart);
   end->get_Count(&nStrandEnd);
   ATLASSERT(nStrandStart == nStrandEnd && nStrandStart == nStrands);
#endif

   *slope = DBL_MAX;
   for ( StrandIndexType strandIdx = 0; strandIdx < nStrands; strandIdx++ )
   {
      CComPtr<IPoint2d> pntStart, pntEnd;
      start->get_Item(strandIdx,&pntStart);
      end->get_Item(strandIdx,&pntEnd);

      Float64 ys, ye;
      pntStart->get_Y(&ys);
      pntEnd->get_Y(&ye);

      Float64 rise = (ye - curr_end_offset + end_offset) - (ys - curr_start_offset + start_offset);

      if (!IsZero(rise))
      {
         // Slope is in the format 1:n (rise:run)
         // Positive slopes are upwards and towards the right
         Float64 n = run/rise;
         if ( MinIndex(fabs(*slope),fabs(n)) == 1 )
         {
            *slope = n;
         }
      }
   }
    
   return S_OK;
}

STDMETHODIMP CStrandGridModel::ComputeAvgHarpedStrandSlopeEx(Float64 Xs,IIndexArray* fill,Float64 startOffset, Float64 hp1Offset, Float64 hp2Offset, Float64 endOffset,Float64* slope)
{
   CHECK_RETVAL(slope);

#if defined _DEBUG
   Float64 gdrLength;
   m_pGirder->get_GirderLength(&gdrLength);
   ATLASSERT(0.0 <= Xs  && Xs <= gdrLength);
#endif

   Float64 leftEndHP, leftHP, rightHP, rightEndHP;
   GetHarpingPointLocations(&leftHP, &rightHP);
   GetEndHarpingPointLocations(&leftEndHP, &rightEndHP);

   if ( InRange(leftEndHP, Xs,leftHP) )
   {
      Float64 cg_x, cg_leftEndHP, cg_leftHP;
      if (fill)
      {
         m_HarpGridEnd[etStart]->get_CGEx(fill, &cg_x, &cg_leftEndHP);
         m_HarpGridHp[etStart]->get_CGEx(fill, &cg_x, &cg_leftHP);

         // cg values in grid are adjusted for internal offset - remove them
         Float64 dx, end_offset, hp_offset;
         m_HarpGridEnd[etStart]->GetStrandAdjustment(&dx, &end_offset);
         m_HarpGridHp[etStart]->GetStrandAdjustment(&dx, &hp_offset);

         cg_leftEndHP -= end_offset;
         cg_leftHP -= hp_offset;
      }
      else
      {
         m_HarpGridEnd[etStart]->get_CG(&cg_x, &cg_leftEndHP);
         m_HarpGridHp[etStart]->get_CG(&cg_x, &cg_leftHP);
      }

      // add external adjustments
      cg_leftEndHP += startOffset;
      cg_leftHP += hp1Offset;

      // make cg measured consistently from bottom
      Float64 HgLeftEndHP = GetSectionHeight(leftEndHP);
      Float64 HgLeftHP = GetSectionHeight(leftHP);

      Float64 leftEndHPprecamber, leftHPprecamber;
      m_pSegment->ComputePrecamber(leftEndHP, &leftEndHPprecamber);
      m_pSegment->ComputePrecamber(leftHP, &leftHPprecamber);

      cg_leftEndHP += HgLeftEndHP + leftEndHPprecamber;
      cg_leftHP += HgLeftHP + leftHPprecamber;

      if ( !::IsEqual(cg_leftEndHP, cg_leftHP) )
      {
         *slope = (leftHP - leftEndHP)/(cg_leftHP - cg_leftEndHP);
      }
      else
      {
         *slope = DBL_MAX;
      }
   }
   else if ( InRange(rightHP, Xs,rightEndHP) )
   {
      Float64 cg_x, cg_rightHP, cg_rightEndHP;
      if (fill)
      {
         m_HarpGridHp[etEnd]->get_CGEx(fill, &cg_x, &cg_rightHP);
         m_HarpGridEnd[etEnd]->get_CGEx(fill, &cg_x, &cg_rightEndHP);

         // cg values are adjusted for internal offset - remove them
         Float64 dx, end_offset, hp_offset;
         m_HarpGridHp[etEnd]->GetStrandAdjustment(&dx, &hp_offset);
         m_HarpGridEnd[etEnd]->GetStrandAdjustment(&dx, &end_offset);

         cg_rightHP -= hp_offset;
         cg_rightEndHP -= end_offset;
      }
      else
      {
         m_HarpGridHp[etEnd]->get_CG(&cg_x, &cg_rightHP);
         m_HarpGridEnd[etEnd]->get_CG(&cg_x, &cg_rightEndHP);
      }

      // add external adjustments
      cg_rightHP += hp2Offset;
      cg_rightEndHP += endOffset;

      // make cg measured consistently from bottom
      Float64 HgRightHP = GetSectionHeight(rightHP);
      Float64 HgRightEndHP = GetSectionHeight(rightEndHP);

      Float64 rightHPprecamber, rightEndHPprecamber;
      m_pSegment->ComputePrecamber(rightHP, &rightHPprecamber);
      m_pSegment->ComputePrecamber(rightEndHP, &rightEndHPprecamber);

      cg_rightHP += HgRightHP + rightHPprecamber;
      cg_rightEndHP += HgRightEndHP + rightEndHPprecamber;

      if ( !::IsEqual(cg_rightHP, cg_rightEndHP) )
      {
         *slope = (rightEndHP - rightHP) / (cg_rightEndHP - cg_rightHP);
      }
      else
      {
         *slope = DBL_MAX;
      }
   }
   else
   {
      ATLASSERT(Xs < leftEndHP || (leftHP < Xs && Xs < rightHP) || rightEndHP < Xs);
      *slope = DBL_MAX;
   }

   return S_OK;
}

STDMETHODIMP CStrandGridModel::ComputeAvgHarpedStrandSlope(Float64 Xs, Float64* slope)
{
   return ComputeAvgHarpedStrandSlopeEx(Xs, nullptr, 0, 0, 0, 0, slope);
}

STDMETHODIMP CStrandGridModel::GetStrandProfile(StrandType strandType, StrandIndexType strandIdx, IPoint2dCollection** ppProfilePoints)
{
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = GetStraightStrandProfile(strandIdx, ppProfilePoints);
      break;

   case Harped:
      hr = GetHarpedStrandProfile(strandIdx, ppProfilePoints);
      break;

   case Temporary:
      hr = GetTemporaryStrandProfile(strandIdx, ppProfilePoints);
      break;
   default:
      ATLASSERT(false);
   }
   return hr;
}

STDMETHODIMP CStrandGridModel::GetMaxStrands(StrandType strandType, StrandIndexType* nStrands)
{
   CHECK_RETVAL(nStrands);
   HRESULT hr = S_OK;
   switch (strandType)
   {
   case Straight:
      hr = m_StraightGrid[etStart]->get_MaxStrandCount(nStrands);
      break;

   case Harped:
      // this is complicated because we are pulling from two strand grids
      UpdateMaxStrandFill();
      *nStrands = m_MaxHarpedStrands;
      hr = S_OK;
      break;

   case Temporary:
      hr = m_TempGrid[etStart]->get_MaxStrandCount(nStrands);
      break;

   default:
      ATLASSERT(false);
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CStrandGridModel::GetStraightStrandDebondCount( WDebondLocationType loc,  StrandIndexType* count)
{
   return m_StraightGrid[etStart]->GetStrandDebondCount(loc, count);
}

STDMETHODIMP CStrandGridModel::GetStrandCGProfile(VARIANT_BOOL bIncludeTempStrands, IPoint2dCollection** ppProfilePoints)
{
   CHECK_RETOBJ(ppProfilePoints);
   CComPtr<IPoint2dCollection> profilePoints;
   profilePoints.CoCreateInstance(CLSID_Point2dCollection);

   StrandIndexType Ns, Nh, Nt(0);
   GetStrandCount(Straight,&Ns);
   GetStrandCount(Harped,&Nh);
   if (bIncludeTempStrands == VARIANT_TRUE)
   {
      GetStrandCount(Temporary,&Nt);
   }

   Float64 hp1, hp2, hp3, hp4;
   StrandIndexType nStrands = Ns + Nh + Nt;
   if (nStrands != 0)
   {
      Float64 Ls;
      m_pSegment->get_Length(&Ls);

      GetHarpPointLocations(hp2, hp3);
      GetEndHarpPointLocations(hp1, hp4);

      // start with a vector containing the key strand control points
      std::vector<Float64> vPoints{ 0.0, hp1, hp2, hp3, hp4, Ls };

      // if there is precamber and the straight/temporary strand following the shape of precamber, add points
      // in between so the profile has the curve
      Float64 precamber;
      m_pSegment->get_Precamber(&precamber);
      if (!IsZero(precamber) && ((0 < Ns && m_StraightStrandProfileType == FollowGirder) || (0 < Nt && m_TemporaryStrandProfileType == FollowGirder)))
      {
         int nPoints = 11;
         for (int i = 0; i < nPoints; i++)
         {
            Float64 x = i*Ls / (nPoints - 1);
            vPoints.push_back(x);
         }
      }

      // add debonding points... add a point just before and just after
      // the point where bond begins so we see the "jump" in the strand cg profile
      StrandIndexType nDebonded;
      GetStraightStrandDebondCount(WDebondLocationType::wdblLeft, &nDebonded);
      if (0 < Ns && nDebonded != 0)
      {
         for (StrandIndexType strandIdx = 0; strandIdx < Ns; strandIdx++)
         {
            Float64 X, Y, l1, l2;
            GetStraightStrandDebondLengthByPositionIndex(0.0, strandIdx, &X, &Y, &l1, &l2);
            if (0 < l1)
            {
               vPoints.push_back(l1 - 0.001);
            }
            
            vPoints.push_back(l1);
            vPoints.push_back(Ls - l2);

            if (0 < l2)
            {
               vPoints.push_back(Ls - l2 + 0.001);
            }
         }
      }

      // sort and eliminate duplicate points
      std::sort(vPoints.begin(), vPoints.end());
      vPoints.erase(std::unique(vPoints.begin(), vPoints.end()), vPoints.end());
      ATLASSERT(0 <= vPoints.front());
      ATLASSERT(vPoints.back() <= Ls);

      for (const auto& x : vPoints)
      {
         CComPtr<IPoint2d> pntCGStraight;
         Float64 cgXstraight(0), cgYstraight(0);

         Float64 precamber;
         m_pSegment->ComputePrecamber(x, &precamber);

         if (0 < Ns)
         {
            GetStrandCG(Straight, x, &pntCGStraight);
            pntCGStraight->Location(&cgXstraight, &cgYstraight);

            if (m_StraightStrandProfileType == FollowGirder)
            {
               cgYstraight += precamber;
            }

            Float64 Yadj = GetGirderDepthAdjustment(x, 0, Ls);
            cgYstraight -= Yadj;
         }

         CComPtr<IPoint2d> pntCGHarped;
         Float64 cgXharped(0), cgYharped(0);
         if (0 < Nh)
         {
            GetStrandCG(Harped, x, &pntCGHarped);
            pntCGHarped->Location(&cgXharped, &cgYharped);

            cgYharped += precamber;

            Float64 Yadj = GetGirderDepthAdjustment(x, 0, Ls);
            cgYharped -= Yadj;
         }

         Float64 cgXtemp(0), cgYtemp(0);
         if (bIncludeTempStrands == VARIANT_TRUE && 0 < Nt)
         {
            CComPtr<IPoint2d> pntCGTemp;
            GetStrandCG(Temporary, x, &pntCGTemp);
            pntCGTemp->Location(&cgXtemp, &cgYtemp);

            if (m_TemporaryStrandProfileType == FollowGirder)
            {
               cgYtemp += precamber;
            }

            Float64 Yadj = GetGirderDepthAdjustment(x, 0, Ls);
            cgYtemp -= Yadj;
         }

         //Float64 cgx = (Ns*cgXstraight + Nh*cgXharped + Nt*cgXtemp) / nStrands;
         Float64 cgy = (Ns*cgYstraight + Nh*cgYharped + Nt*cgYtemp) / nStrands;

         CComPtr<IPoint2d> pntCG;
         pntCG.CoCreateInstance(CLSID_Point2d);
         pntCG->Move(x, cgy);

         profilePoints->Add(pntCG);
      }
   }

   // put the strand profiles in the same longitudinal coordinate system as the girder profile
   CComPtr<IGirderLine> girderLine;
   m_pSegment->get_GirderLine(&girderLine);

   Float64 brgOffset, endDist;
   girderLine->get_BearingOffset(etStart, &brgOffset);
   girderLine->get_EndDistance(etStart, &endDist);
   Float64 offset = brgOffset - endDist;

   profilePoints->Offset(offset, 0);

   profilePoints.CopyTo(ppProfilePoints);
   return S_OK;
}

STDMETHODIMP CStrandGridModel::ClearStraightStrandDebonding()
{
   m_StraightGrid[etStart]->ClearDebonding();
   m_StraightGrid[etEnd]->ClearDebonding();
   m_CGs[Straight].clear();
   return S_OK;
}

STDMETHODIMP CStrandGridModel::DebondStraightStrandByGridIndex(GridIndexType grdIndex,Float64 l1,Float64 l2)
{
   m_StraightGrid[etStart]->DebondStrandByGridIndex(grdIndex, l1, l2);
   m_StraightGrid[etEnd]->DebondStrandByGridIndex(grdIndex, l1, l2);
   m_CGs[Straight].clear();
   return S_OK;
}

STDMETHODIMP CStrandGridModel::GetDebondedStraightStrandsByGridIndex(IIndexArray** grdIndexes)
{
   return m_StraightGrid[etStart]->GetDebondedStrandsByGridIndex(grdIndexes);
}

STDMETHODIMP CStrandGridModel::GetStraightStrandDebondLengthByGridIndex(EndType endType,GridIndexType grdIndex,Float64* XCoord,Float64* YCoord, Float64* l1,Float64* l2)
{
   return m_StraightGrid[endType]->GetDebondLengthByGridIndex(grdIndex, XCoord, YCoord, l1, l2);
}

// Debonded straight strands based on Positions index (i.e., from get_StraightStrandPositions)
STDMETHODIMP CStrandGridModel::GetStraightStrandDebondLengthByPositionIndex(Float64 Xs,StrandIndexType positionIndex,Float64* XCoord, Float64* YCoord, Float64* l1,Float64* l2)
{
   return m_StraightGrid[etStart]->GetDebondLengthByPositionIndex(positionIndex, XCoord, YCoord, l1, l2);
}

STDMETHODIMP CStrandGridModel::GetStraightStrandsDebondedByPositionIndex(Float64 Xs, IIndexArray** positionIndexes)
{
   Float64 grd_length;
   m_pGirder->get_GirderLength(&grd_length);

   return m_StraightGrid[etStart]->GetStrandsDebondedByPositionIndex(Xs, grd_length, positionIndexes);
}

STDMETHODIMP CStrandGridModel::get_StraightStrandDebondInRow(Float64 Xs, RowIndexType rowIdx,StrandIndexType* nStrands)
{
   return m_StraightGrid[etStart]->get_StrandDebondInRow(rowIdx, nStrands);
}

STDMETHODIMP CStrandGridModel::IsExteriorStraightStrandDebondedInRow(Float64 Xs, RowIndexType rowIndex,VARIANT_BOOL* bResult)
{
   return m_StraightGrid[etStart]->IsExteriorStrandDebondedInRow(rowIndex, bResult);
}

STDMETHODIMP CStrandGridModel::GetDebondingLocations(StrandType strandType, IDblArray** arrLeft,IDblArray** arrRight)
{
   if (strandType == Straight)
   {
      return m_StraightGrid[etStart]->GetDebondSections(arrLeft, arrRight);
   }
   else
   {
      return E_INVALIDARG;
   }
}

STDMETHODIMP CStrandGridModel::GetDebondedStrandsAtSection(EndType endType, StrandType strandType, SectionIndexType sectionIdx, IIndexArray** pstnIndexes)
{
   if (strandType == Straight)
   {
      if (endType == etStart)
      {
         return m_StraightGrid[etStart]->GetDebondAtLeftSection(sectionIdx, pstnIndexes);
      }
      else
      {
         return m_StraightGrid[etStart]->GetDebondAtRightSection(sectionIdx, pstnIndexes);
      }
   }
   else
   {
      return E_INVALIDARG;
   }
}

STDMETHODIMP CStrandGridModel::GetStraightStrandBondedLengthByPositionIndex(StrandIndexType positionIndex, Float64 distFromStart, 
   Float64* XCoord, Float64* YCoord, Float64* leftBond, Float64* rightBond)
{
   Float64 gdr_length;
   m_pGirder->get_GirderLength(&gdr_length);

   // straight strand grids may not be exactly equal for taper girders...
   Float64 leftBond1, leftBond2;
   Float64 rightBond1, rightBond2;
   Float64 X1,Y1,X2,Y2;
   m_StraightGrid[etStart]->GetBondedLengthByPositionIndex(positionIndex, distFromStart, gdr_length, &X1,&Y1, &leftBond1, &rightBond1);
   m_StraightGrid[etEnd  ]->GetBondedLengthByPositionIndex(positionIndex, distFromStart, gdr_length, &X2,&Y2, &leftBond2, &rightBond2);
   ATLASSERT(IsEqual(leftBond1,leftBond2));
   ATLASSERT(IsEqual(rightBond1,rightBond2));
   *leftBond = leftBond1;
   *rightBond = rightBond1;
   *XCoord = ::LinInterp(distFromStart, X1, X2, gdr_length);
   *YCoord = ::LinInterp(distFromStart, Y1, Y2, gdr_length);

   *YCoord += GetGirderDepthAdjustment(distFromStart,0.0,gdr_length);

   return S_OK;
}

STDMETHODIMP CStrandGridModel::GetStraightStrandBondedLengthByGridIndex(GridIndexType grdIndex, Float64 distFromStart, 
                                              Float64* XCoord, Float64* YCoord, Float64* leftBond, Float64* rightBond)
{
   Float64 gdr_length;
   m_pGirder->get_GirderLength(&gdr_length);

   Float64 leftBond1, leftBond2;
   Float64 rightBond1, rightBond2;
   Float64 X1,Y1,X2,Y2;
   m_StraightGrid[etStart]->GetBondedLengthByGridIndex(grdIndex, distFromStart, gdr_length, &X1,&Y1, &leftBond1, &rightBond1);
   m_StraightGrid[etEnd  ]->GetBondedLengthByGridIndex(grdIndex, distFromStart, gdr_length, &X2,&Y2, &leftBond2, &rightBond2);
   ATLASSERT(IsEqual(leftBond1,leftBond2));
   ATLASSERT(IsEqual(rightBond1,rightBond2));
   *leftBond = leftBond1;
   *rightBond = rightBond1;
   *XCoord = ::LinInterp(distFromStart, X1, X2, gdr_length);
   *YCoord = ::LinInterp(distFromStart, Y1, Y2, gdr_length);

   *YCoord += GetGirderDepthAdjustment(distFromStart,0.0,gdr_length);

   return S_OK;
}

STDMETHODIMP CStrandGridModel::GetStraightStrandDebondedRows(Float64 Xs,IIndexArray** ppRowIndexes)
{
   return m_StraightGrid[etStart]->GetDebondedRows(ppRowIndexes);
}

STDMETHODIMP CStrandGridModel::GetStraightStrandDebondedConfigurationCountByRow(Float64 Xs, RowIndexType rowIdx, IndexType* pConfigCount)
{
   return m_StraightGrid[etStart]->GetDebondedConfigurationCountByRow(rowIdx, pConfigCount);
}

STDMETHODIMP CStrandGridModel::GetStraightStrandDebondConfigurationByRow(Float64 Xs, RowIndexType rowIdx, IndexType configIdx, Float64* pXstart, Float64* pBondedLength, Float64* pCgX, Float64* pCgY, IndexType* pnStrands)
{
   Float64 gdr_length;
   m_pGirder->get_GirderLength(&gdr_length);

   Float64 LdbStart, LdbEnd;
   m_StraightGrid[etStart]->GetDebondConfigurationByRow(rowIdx, configIdx, &LdbStart, &LdbEnd, pCgX, pCgY, pnStrands);
   *pXstart = LdbStart;
   *pBondedLength = gdr_length - LdbStart - LdbEnd;
   return S_OK;
}

HRESULT CStrandGridModel::ComputeHpFill(IIndexArray* endFill, IIndexArray** hpFill)
{
   // Fill for harped strands at harping points can be different than at girder ends
   // if the odd number of strands option is activated
   if (m_AllowOddNumberOfHarpedStrands == VARIANT_TRUE)
   {
      StrandIndexType nStrands;
      m_HarpGridEnd[etStart]->GetStrandCountEx(endFill, &nStrands);

#if defined _DEBUG
      StrandIndexType cnt;
      m_HarpGridEnd[etEnd]->GetStrandCountEx(endFill,&cnt);
      ATLASSERT(cnt == nStrands);
#endif

      if (1 < nStrands && nStrands%2 != 0) // if there is more than 1 harped strand and the number of strands is odd
      {
         // we allow, and have, an odd number of strands.

         // we are in business, start alternate fill of hp grid
         m_OddHpFill->Clear();
         IndexType fill_size;
         endFill->get_Count(&fill_size);
         m_OddHpFill->Reserve(fill_size);

         // put two strands in the first hp location
#if defined _DEBUG
         IndexType first_row;
         endFill->get_Item(0,&first_row);
         ASSERT(first_row == 1); // only one strand at the bottom... but we need it to be 2 for odd fill at top
#endif

         StrandIndexType running_cnt = (m_UseDifferentHarpedGirdAtEnds == VARIANT_TRUE ? 2 : 1);
         m_OddHpFill->Add(running_cnt); 

         for (IndexType is = 1; is < fill_size; is++)
         {
            if (running_cnt < nStrands)
            {
               // there are still strands to fill

               StrandIndexType fill_val;
               endFill->get_Item(is, &fill_val);
               
               running_cnt += fill_val;
               
               if (running_cnt <= nStrands)
               {
                  // not at the end yet, just fill it up
                  m_OddHpFill->Add(fill_val);
               }
               else
               {
                  // we are at the end... add the odd strand
                  if ( m_UseDifferentHarpedGirdAtEnds == VARIANT_TRUE )
                  {
                     m_OddHpFill->Add(fill_val-1);
                  }
                  else
                  {
                     m_OddHpFill->Add(fill_val);
                  }

                  running_cnt--;
               }
            }
            else
            {
               m_OddHpFill->Add(0);
            }
         }

         // Return with modified grid
         ATLASSERT(running_cnt==nStrands);
         return m_OddHpFill.CopyTo(hpFill);
      }
   }

   // if we get to here, hp grid is same as end
   endFill->AddRef();
   *hpFill = endFill;

   return S_OK;
}

void CStrandGridModel::GetHarpedStrandGrid(Float64 Xs,IStrandGridFiller** ppGrid)
{
   Float64 hp1, hp2;
   GetHarpPointLocations(hp1,hp2);

   if (Xs < hp1 )
   {
      m_HarpGridEnd[etStart].CopyTo(ppGrid);
   }
   else if ( hp2 < Xs)
   {
      m_HarpGridEnd[etEnd].CopyTo(ppGrid);
   }
   else 
   {
      m_HarpGridHp[etStart].CopyTo(ppGrid);
   }
}

void CStrandGridModel::RemoveStraightStrandDebondedStrandPositions(Float64 Xs, IPoint2dCollection* pPoints)
{
   StrandIndexType nDebonded;
   GetStraightStrandDebondCount(WDebondLocationType::wdblLeft, &nDebonded);
   if (nDebonded == 0)
   {
      // no debonded strands... nothing to do
      return;
   }

   Float64 Ls;
   m_pSegment->get_Length(&Ls);

   // work backwards so removing an item doesn't mess up the iterator
   IndexType nPoints;
   pPoints->get_Count(&nPoints);
   for (StrandIndexType strandIdx = nPoints - 1; 0 <= strandIdx && strandIdx != INVALID_INDEX; strandIdx--)
   {
      Float64 X, Y, l1, l2;
      GetStraightStrandDebondLengthByPositionIndex(Xs, strandIdx, &X, &Y, &l1, &l2);
#if defined _DEBUG
      CComPtr<IPoint2d> pnt;
      pPoints->get_Item(strandIdx, &pnt);
      Float64 px, py;
      pnt->Location(&px, &py);
      ATLASSERT(IsEqual(px, X));
      ATLASSERT(IsEqual(py, Y));
#endif
      if (!IsZero(l1) || !IsZero(l2))
      {
         // this is some debonding... does it occur at this section?
         Float64 leftBond = Xs - l1; // amount of bonded strands on the left side of distFromStart
         Float64 rightBond = Ls - Xs - l2; // amount of bonded strand on the right side of distFromStart
         if (IsZero(Xs) || IsEqual(Xs, Ls))
         {
            if (IsLT(leftBond, 0.0) || IsLT(rightBond, 0.0))
            {
               // strand is not bonded at this section... remove it
               pPoints->Remove(strandIdx);
            }
         }
         else
         {
            if (IsLE(leftBond, 0.0) || IsLE(rightBond, 0.0))
            {
               // strand is not bonded at this section... remove it
               pPoints->Remove(strandIdx);
            }
         }
      }
   }
}

Float64 CStrandGridModel::GetSectionHeight(Float64 Xs)
{
   Float64 Hg;
   CComPtr<IShape> shape;
   m_pSegment->get_GirderShape(Xs,sbLeft,cstGirder,&shape);
   CComPtr<IRect2d> bbox;
   shape->get_BoundingBox(&bbox);
   bbox->get_Height(&Hg);
   return Hg;
}

Float64 CStrandGridModel::GetGirderDepthAdjustment(Float64 Xs, Float64 distToStartGrid, Float64 distBetweenGrids, IStrandGridFiller* pStartGridFiller, IStrandGridFiller* pEndGridFiller)
{
   Float64 Yadj = 0;
   CComQIPtr<ITaperedGirderSegment> taperedSegment(m_pSegment);
   CComQIPtr<IThickenedFlangeSegment> thickenedSegment(m_pSegment);
   if (taperedSegment || thickenedSegment)
   {
      Float64 Lg;
      m_pGirder->get_GirderLength(&Lg);

      Float64 Hstart, Hend;
      StrandGridType gridType;
      EndType endType;
      CComPtr<IStrandMover> mover;
      if (pStartGridFiller)
      {
         pStartGridFiller->GetStrandMover(&gridType, &endType, &mover);
      }

      if (mover)
      {
         mover->get_SectionHeight(&Hstart);
      }
      else
      {
         Hstart = GetSectionHeight(distToStartGrid);
      }

      mover.Release();
      if (pEndGridFiller)
      {
         pEndGridFiller->GetStrandMover(&gridType, &endType, &mover);
      }

      if (mover)
      {
         mover->get_SectionHeight(&Hend);
      }
      else
      {
         Hend = GetSectionHeight(distToStartGrid + distBetweenGrids);
      }

      // Height of section at distFromStart assuming a straight line connection top of the girder
      // at the start and end grids
      Float64 H = ::LinInterp(Xs-distToStartGrid,Hstart,Hend,distBetweenGrids);

      // Get actual height of section at distFromStart
      Float64 Hg = GetSectionHeight(Xs);

      // amount to vertically adjust the elevation of the strands
      Yadj = H - Hg;
   }

   return Yadj;
}

HRESULT CStrandGridModel::GetStraightStrandPositions(Float64 Xs, IIndexArray* fill, IPoint2dCollection** points)
{
   if (fill == nullptr)
   {
      m_StraightGrid[etStart]->get_StrandFill(&fill);
   }

   Float64 gdrLength;
   m_pGirder->get_GirderLength(&gdrLength);

   Float64 precamber(0.0);
   if (m_StraightStrandProfileType == Linear)
   {
      m_pSegment->ComputePrecamber(Xs, &precamber);
   }

   HRESULT hr = GetStrandPositions(Xs, 0.0, gdrLength, gdrLength, -precamber, -precamber, fill, m_StraightGrid[etStart], fill, m_StraightGrid[etEnd], points);

   if (m_StraightStrandProfileType == FollowGirder)
   {
      m_pSegment->ComputePrecamber(Xs, &precamber);
      (*points)->Offset(0, precamber);
   }

   return hr;
}

HRESULT CStrandGridModel::GetHarpedStrandPositions(Float64 Xs, IIndexArray* fill, IPoint2dCollection** points)
{
   CHECK_RETOBJ(points);

   if (fill == nullptr)
   {
      m_HarpGridEnd[etStart]->get_StrandFill(&fill);
   }

   // may need to interpolate
   Float64 gdrLength, leftEndHP, leftHP, rightHP, rightEndHP;
   m_pGirder->get_GirderLength(&gdrLength);
   GetHarpingPointLocations(&leftHP, &rightHP);
   GetEndHarpingPointLocations(&leftEndHP, &rightEndHP);

   // harped strands always have a Linear profile so their elevation need to be adjusted for precamber effects
   if (::IsLE(Xs, leftEndHP))
   {
      // in start portion of harped strands governed by the start grid
      m_HarpGridEnd[etStart]->GetStrandPositionsEx(fill, points);
      Float64 precamber;
      m_pSegment->ComputePrecamber(Xs, &precamber);
      (*points)->Offset(0, -precamber);
      return S_OK;
   }
   else if (::IsGE(rightEndHP, Xs))
   {
      // in end portion of the harped strands governed by the end grid
      m_HarpGridEnd[etEnd]->GetStrandPositionsEx(fill, points);
      Float64 precamber;
      m_pSegment->ComputePrecamber(Xs, &precamber);
      (*points)->Offset(0, -precamber);
      return S_OK;
   }
   else if (leftHP <= Xs && Xs <= rightHP)
   {
      // between harp points
      CComPtr<IIndexArray> hp_fill;
      HRESULT hr = ComputeHpFill(fill, &hp_fill);
      ATLASSERT(SUCCEEDED(hr));

      Float64 leftPrecamber, rightPrecamber;
      m_pSegment->ComputePrecamber(leftHP, &leftPrecamber);
      m_pSegment->ComputePrecamber(rightHP, &rightPrecamber);

      // assume harped strand are straight between harping points (they don't follow the bottom of the girder if precambered)
      hr = GetStrandPositions(Xs, leftHP, rightHP - leftHP, gdrLength, leftPrecamber, rightPrecamber, hp_fill, m_HarpGridHp[etStart], hp_fill, m_HarpGridHp[etEnd], points);
      ATLASSERT(SUCCEEDED(hr));

      return hr;
   }
   else if (leftEndHP < Xs && Xs < leftHP)
   {
      // on the sloped part of the harped strands at the left end of the girder

      // compute harped fill at hp
      CComPtr<IIndexArray> hp_fill;
      HRESULT hr = ComputeHpFill(fill, &hp_fill);
      ATLASSERT(SUCCEEDED(hr));

      Float64 leftPrecamber, rightPrecamber;
      m_pSegment->ComputePrecamber(leftEndHP, &leftPrecamber);
      m_pSegment->ComputePrecamber(leftHP, &rightPrecamber);

      hr = GetStrandPositions(Xs, leftEndHP, leftHP - leftEndHP, gdrLength, leftPrecamber, rightPrecamber, fill, m_HarpGridEnd[etStart], hp_fill, m_HarpGridHp[etStart], points);

      ATLASSERT(SUCCEEDED(hr));
      return hr;
   }
   else
   {
      ATLASSERT(rightHP < Xs && Xs < rightEndHP);
      // on the sloped part of the harped strands at right end of girder
      // compute harped fill at hp
      CComPtr<IIndexArray> hp_fill;
      HRESULT hr = ComputeHpFill(fill, &hp_fill);
      ATLASSERT(SUCCEEDED(hr));

      Float64 leftPrecamber, rightPrecamber;
      m_pSegment->ComputePrecamber(rightHP, &leftPrecamber);
      m_pSegment->ComputePrecamber(rightEndHP, &rightPrecamber);

      hr = GetStrandPositions(Xs, rightHP, rightEndHP - rightHP, gdrLength, leftPrecamber, rightPrecamber, hp_fill, m_HarpGridHp[etEnd], fill, m_HarpGridEnd[etEnd], points);

      ATLASSERT(SUCCEEDED(hr));
      return hr;
   }
}

HRESULT CStrandGridModel::GetTemporaryStrandPositions(Float64 Xs, IIndexArray* fill, IPoint2dCollection** points)
{
   if (fill == nullptr)
   {
      m_TempGrid[etStart]->get_StrandFill(&fill);
   }

   Float64 gdrLength;
   m_pGirder->get_GirderLength(&gdrLength);

   Float64 precamber(0.0);
   if (m_TemporaryStrandProfileType == Linear)
   {
      m_pSegment->ComputePrecamber(Xs, &precamber);
   }

   HRESULT hr = GetStrandPositions(Xs, 0.0, gdrLength, gdrLength, -precamber, -precamber, fill, m_TempGrid[etStart], fill, m_TempGrid[etEnd], points);

   if (m_TemporaryStrandProfileType == FollowGirder)
   {
      m_pSegment->ComputePrecamber(Xs, &precamber);
      (*points)->Offset(0, precamber);
   }

   return hr;
}

HRESULT CStrandGridModel::GetStrandPositions(Float64 Xs, Float64 distToStartGrid, Float64 distBetweenGrids, Float64 Lg, Float64 startPrecamber, Float64 endPrecamber,IIndexArray* startFill, IStrandGridFiller* pStartGridFiller, IIndexArray* endFill, IStrandGridFiller* pEndGridFiller, IPoint2dCollection** points)
{
   CComPtr<IPoint2dCollection> startPoints;
   CComPtr<IPoint2dCollection> endPoints;
   pStartGridFiller->GetStrandPositionsEx(startFill,&startPoints); // gets a copy, in Girder Section Coordinates
   pEndGridFiller->GetStrandPositionsEx(endFill,&endPoints); // gets a copy, in Girder Section Coordinates

   // adjust strand grids so that they are measured from the same datum (bottom of girder at left end)
   Float64 Hg = GetSectionHeight(0);
   startPoints->Offset(0, Hg + startPrecamber);
   endPoints->Offset(0, Hg + endPrecamber);

   Float64 Yadj = GetGirderDepthAdjustment(Xs, distToStartGrid, distBetweenGrids, pStartGridFiller, pEndGridFiller);

   IndexType nPoints;
   startPoints->get_Count(&nPoints);

#if defined _DEBUG
   IndexType np;
   endPoints->get_Count(&np);
   ATLASSERT(np == nPoints);
#endif

   CComPtr<IPoint2dCollection> pnts;
   pnts.CoCreateInstance(CLSID_Point2dCollection);
   for (IndexType idx = 0; idx < nPoints; idx++ )
   {
      CComPtr<IPoint2d> pntStart,  pntEnd;
      startPoints->get_Item(idx,&pntStart);
      endPoints->get_Item(idx,&pntEnd);

      Float64 sx,sy;
      pntStart->Location(&sx, &sy);

      Float64 ex, ey;
      pntEnd->Location(&ex, &ey);

      Float64 x = ::LinInterp(Xs - distToStartGrid,sx,ex,distBetweenGrids);
      Float64 y = ::LinInterp(Xs - distToStartGrid,sy,ey,distBetweenGrids);

      CComPtr<IPoint2d> pnt;
      pnt.CoCreateInstance(CLSID_Point2d);
      pnt->Move(x,y+Yadj);
      pnts->Add(pnt);
   }

   // adjust the location of the strands to be in Girder Section Coordinates again
   Float64 precamber;
   m_pSegment->ComputePrecamber(Xs, &precamber);
   pnts->Offset(0, -Hg - precamber);

   (*points) = pnts;
   (*points)->AddRef();
   return S_OK;
}

HRESULT CStrandGridModel::GetStraightStrandCount(IIndexArray* fill, StrandIndexType* nStrands)
{
   if (fill == nullptr)
   {
      return m_StraightGrid[etStart]->GetStrandCount(nStrands);
   }
   else
   {
      return m_StraightGrid[etStart]->GetStrandCountEx(fill, nStrands);
   }
}

HRESULT CStrandGridModel::GetHarpedStrandCount(IIndexArray* fill, StrandIndexType* nStrands)
{
   if (fill == nullptr)
   {
      m_HarpGridHp[etStart]->GetStrandCount(nStrands);
#if defined _DEBUG
      StrandIndexType nsend;
      m_HarpGridEnd[etStart]->GetStrandCount(&nsend);
      ATLASSERT(nsend == *nStrands);
#endif
   }
   else
   {
      HRESULT hr = m_HarpGridEnd[etStart]->GetStrandCountEx(fill, nStrands);

#ifdef _DEBUG
      // compute hp fill, if different
      CComPtr<IIndexArray> hp_fill;
      hr = ComputeHpFill(fill, &hp_fill);
      if (FAILED(hr))
      {
         ATLASSERT(false);
         return hr;
      }

      StrandIndexType nsend;
      m_HarpGridHp[etStart]->GetStrandCountEx(hp_fill, &nsend);
      ATLASSERT(nsend == *nStrands);
#endif _DEBUG
   }

   return S_OK;
}

HRESULT CStrandGridModel::GetTemporaryStrandCount(IIndexArray* fill, StrandIndexType* nStrands)
{
   if (fill == nullptr)
   {
      return m_TempGrid[etStart]->GetStrandCount(nStrands);
   }
   else
   {
      return m_TempGrid[etStart]->GetStrandCountEx(fill, nStrands);
   }
}

HRESULT CStrandGridModel::GetStraightStrandProfile(StrandIndexType strandIdx,/*[out, retval]*/IPoint2dCollection** ppProfilePoints)
{
   CHECK_RETOBJ(ppProfilePoints);

   CComPtr<IPoint2dCollection> profilePoints;
   profilePoints.CoCreateInstance(CLSID_Point2dCollection);

   Float64 Ls;
   m_pSegment->get_Length(&Ls);

   std::vector<Float64> vPoints;

   Float64 X, Y, l1, l2;
   GetStraightStrandDebondLengthByPositionIndex(0.0,strandIdx,&X,&Y,&l1,&l2);
   Float64 xMin = l1;
   Float64 xMax = Ls - l2;

   vPoints.push_back(xMin);
   vPoints.push_back(xMax);

   Float64 precamber;
   m_pSegment->get_Precamber(&precamber);
   if (m_StraightStrandProfileType == FollowGirder || !IsZero(precamber))
   {
      int nPoints = 11;
      for (int i = 0; i < nPoints; i++)
      {
         Float64 Xs = i*Ls / (nPoints - 1);
         if (xMin < Xs && Xs < xMax)
         {
            vPoints.push_back(Xs);
         }
      }
   }

   CComQIPtr<ISplicedGirderSegment> splicedSegment(m_pSegment);
   if (splicedSegment)
   {
      CComPtr<IDblArray> array;
      splicedSegment->GetProfileControlPoints(VARIANT_FALSE, VARIANT_TRUE, &array); // exclude clousure and get values in segment coordinates

      CComPtr<IEnumDblArray> enumArray;
      array->get__EnumElements(&enumArray);
      Float64 Xs;
      while(enumArray->Next(1, &Xs, nullptr) != S_FALSE)
      {
         vPoints.push_back(Xs);
      }
   }

   std::sort(vPoints.begin(), vPoints.end());
   vPoints.erase(std::unique(vPoints.begin(), vPoints.end()), vPoints.end()); 

   for (const auto& x : vPoints)
   {
      CComPtr<IPoint2dCollection> strandPoints;
      GetStrandPositions(Straight, x, &strandPoints);

      CComPtr<IPoint2d> strandPoint;
      strandPoints->get_Item(strandIdx, &strandPoint);

      Float64 y;
      strandPoint->get_Y(&y);

      if (m_StraightStrandProfileType == FollowGirder)
      {
         m_pSegment->ComputePrecamber(x, &precamber);
         y += precamber;
      }

      Float64 Yadj = GetGirderDepthAdjustment(x, 0, Ls);
      y -= Yadj;

      CComPtr<IPoint2d> profilePoint;
      profilePoint.CoCreateInstance(CLSID_Point2d);
      profilePoint->Move(x, y);
      profilePoints->Add(profilePoint);
   }

   // put the strand profiles in the same longitudinal coordinate system as the girder profile
   CComPtr<IGirderLine> girderLine;
   m_pSegment->get_GirderLine(&girderLine);

   Float64 brgOffset, endDist;
   girderLine->get_BearingOffset(etStart, &brgOffset);
   girderLine->get_EndDistance(etStart, &endDist);
   Float64 offset = brgOffset - endDist;

   profilePoints->Offset(offset, 0);

   profilePoints.CopyTo(ppProfilePoints);
   return S_OK;
}

HRESULT CStrandGridModel::GetHarpedStrandProfile(StrandIndexType strandIdx,/*[out, retval]*/IPoint2dCollection** ppProfilePoints)
{
   CHECK_RETOBJ(ppProfilePoints);

   CComPtr<IPoint2dCollection> profilePoints;
   profilePoints.CoCreateInstance(CLSID_Point2dCollection);

   Float64 Ls;
   m_pSegment->get_Length(&Ls);

   Float64 hp1, hp2, hp3, hp4;
   GetHarpPointLocations(hp2, hp3);
   GetEndHarpPointLocations(hp1, hp4);

   std::vector<Float64> vPoints{ 0.0, hp1, hp2, hp3, hp4, Ls };
   vPoints.erase(std::unique(vPoints.begin(), vPoints.end()), vPoints.end()); // eliminate duplicates

   for (const auto& x : vPoints)
   {
      CComPtr<IPoint2dCollection> strandPoints;
      GetStrandPositions(Harped, x, &strandPoints);

      CComPtr<IPoint2d> strandPoint;
      strandPoints->get_Item(strandIdx, &strandPoint);

      Float64 y;
      strandPoint->get_Y(&y);

      Float64 precamber;
      m_pSegment->ComputePrecamber(x, &precamber);
      y += precamber;

      Float64 Yadj = GetGirderDepthAdjustment(x, 0, Ls);
      y -= Yadj;

      CComPtr<IPoint2d> profilePoint;
      profilePoint.CoCreateInstance(CLSID_Point2d);
      profilePoint->Move(x, y);

      profilePoints->Add(profilePoint);
   }

   // put the strand profiles in the same longitudinal coordinate system as the girder profile
   CComPtr<IGirderLine> girderLine;
   m_pSegment->get_GirderLine(&girderLine);

   Float64 brgOffset, endDist;
   girderLine->get_BearingOffset(etStart, &brgOffset);
   girderLine->get_EndDistance(etStart, &endDist);
   Float64 offset = brgOffset - endDist;

   profilePoints->Offset(offset, 0);

   profilePoints.CopyTo(ppProfilePoints);
   return S_OK;
}

HRESULT CStrandGridModel::GetTemporaryStrandProfile(StrandIndexType strandIdx,/*[out, retval]*/IPoint2dCollection** ppProfilePoints)
{
   CHECK_RETOBJ(ppProfilePoints);

   CComPtr<IPoint2dCollection> profilePoints;
   profilePoints.CoCreateInstance(CLSID_Point2dCollection);

   Float64 Ls;
   m_pSegment->get_Length(&Ls);

   std::vector<Float64> vPoints{ 0.0, Ls };

   Float64 precamber;
   m_pSegment->get_Precamber(&precamber);

   Float64 tft = 0;
   CComQIPtr<IThickenedFlangeSegment> thickenedSegment(m_pSegment);
   if (thickenedSegment)
   {
      thickenedSegment->get_FlangeThickening(&tft);
   }

   if (m_TemporaryStrandProfileType == FollowGirder && (!IsZero(precamber) || !IsZero(tft)))
   {
      int nPoints = 11;
      for (int i = 0; i < nPoints; i++)
      {
         Float64 Xs = i*Ls / (nPoints - 1);
         vPoints.push_back(Xs);
      }
   }

   std::sort(vPoints.begin(), vPoints.end());
   vPoints.erase(std::unique(vPoints.begin(), vPoints.end()), vPoints.end());

   for (const auto& x : vPoints)
   {
      CComPtr<IPoint2dCollection> strandPoints;
      GetStrandPositions(Temporary, x, &strandPoints);

      CComPtr<IPoint2d> strandPoint;
      strandPoints->get_Item(strandIdx, &strandPoint);

      Float64 y;
      strandPoint->get_Y(&y);

      if (m_TemporaryStrandProfileType == FollowGirder)
      {
         m_pSegment->ComputePrecamber(x, &precamber);
         y += precamber;

         if (thickenedSegment)
         {
            thickenedSegment->get_TopFlangeThickening(x, &tft);
            y += tft;
         }
      }

      Float64 Yadj = GetGirderDepthAdjustment(x, 0, Ls);
      y -= Yadj;

      CComPtr<IPoint2d> profilePoint;
      profilePoint.CoCreateInstance(CLSID_Point2d);
      profilePoint->Move(x, y);
      profilePoints->Add(profilePoint);
   }

   // put the strand profiles in the same longitudinal coordinate system as the girder profile
   CComPtr<IGirderLine> girderLine;
   m_pSegment->get_GirderLine(&girderLine);

   Float64 brgOffset, endDist;
   girderLine->get_BearingOffset(etStart, &brgOffset);
   girderLine->get_EndDistance(etStart, &endDist);
   Float64 offset = brgOffset - endDist;

   profilePoints->Offset(offset, 0);

   profilePoints.CopyTo(ppProfilePoints);
   return S_OK;
}

HRESULT CStrandGridModel::UpdateMaxStrandFill()
{
   // this is not simple because we have two grids to deal with
   if (m_UpdateHarpedMaxFill)
   {
      HRESULT hr = m_StrandFillTool->ComputeHarpedStrandMaxFill(m_HarpGridEnd[etStart], m_HarpGridHp[etStart],&m_MaxHarpedStrands,&m_HarpedMaxStrandFill);
      if (FAILED(hr))
      {
         return hr;
      }

      m_UpdateHarpedMaxFill = false;
   }

   return S_OK;
}


HRESULT CStrandGridModel::PutRefStraightStrandFill(IIndexArray* fill)
{
   m_CGs[Straight].clear();
   HRESULT hr = m_StraightGrid[etStart]->putref_StrandFill(fill);
   if (FAILED(hr))
   {
      return hr;
   }

   hr = m_StraightGrid[etEnd]->putref_StrandFill(fill);
   if (FAILED(hr))
   {
      return hr;
   }

   return S_OK;
}

HRESULT CStrandGridModel::PutRefHarpedStrandFill(IIndexArray* fill)
{
   m_CGs[Harped].clear();
   HRESULT hr = m_HarpGridEnd[etStart]->putref_StrandFill(fill);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   hr = m_HarpGridEnd[etEnd]->putref_StrandFill(fill);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   CComPtr<IIndexArray> hp_fill;
   hr = ComputeHpFill(fill, &hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   hr = m_HarpGridHp[etStart]->putref_StrandFill(hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   hr = m_HarpGridHp[etEnd]->putref_StrandFill(hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   return S_OK;
}

HRESULT CStrandGridModel::PutRefTemporaryStrandFill(IIndexArray* fill)
{
   m_CGs[Temporary].clear();
   HRESULT hr = m_TempGrid[etStart]->putref_StrandFill(fill);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   hr = m_TempGrid[etEnd]->putref_StrandFill(fill);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   return S_OK;
}
