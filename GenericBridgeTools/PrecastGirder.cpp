///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2013  Washington State Department of Transportation
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

// PrecastGirder.cpp : Implementation of CPrecastGirder
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "PrecastGirder.h"
#include <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

// CPrecastGirder
HRESULT CPrecastGirder::FinalConstruct()
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

   hr = m_RebarLayout.CoCreateInstance(CLSID_RebarLayout);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IGeomUtil> geom_util;
   hr = geom_util.CoCreateInstance(CLSID_GeomUtil);
   if ( FAILED(hr) )
      return hr;

   m_UpdateLengths = true;

   geom_util->get_Point2dFactory(&m_Point2dFactory);

   m_StrandFillTool.CoCreateInstance(CLSID_StrandFillTool);

   return S_OK;
}

void CPrecastGirder::FinalRelease()
{
}

STDMETHODIMP CPrecastGirder::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPrecastGirder
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPrecastGirder::Initialize(ISegment* segment,IStrandMover* strandMover)
{
   CHECK_IN(segment);
   //CHECK_IN(strandMover);

   m_pSegment = segment;
   m_pStrandMover = strandMover;


   m_HarpGridEnd[etStart]->put_StrandMover(strandMover);
   m_HarpGridEnd[etEnd]->put_StrandMover(strandMover);

   m_HarpGridHp[etStart]->put_StrandMover(strandMover);
   m_HarpGridHp[etEnd]->put_StrandMover(strandMover);

   return S_OK;
}

STDMETHODIMP CPrecastGirder::putref_StraightStrandMaterial(IPrestressingStrand* pMaterial)
{
   CHECK_IN(pMaterial);
   m_StraightStrandMaterial = pMaterial;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_StraightStrandMaterial(IPrestressingStrand** ppMaterial)
{
   CHECK_RETOBJ(ppMaterial);
   return m_StraightStrandMaterial.CopyTo(ppMaterial);
}

STDMETHODIMP CPrecastGirder::putref_HarpedStrandMaterial(IPrestressingStrand* pMaterial)
{
   CHECK_IN(pMaterial);
   m_HarpedStrandMaterial = pMaterial;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandMaterial(IPrestressingStrand** ppMaterial)
{
   CHECK_RETOBJ(ppMaterial);
   return m_HarpedStrandMaterial.CopyTo(ppMaterial);
}

STDMETHODIMP CPrecastGirder::putref_TemporaryStrandMaterial(IPrestressingStrand* pMaterial)
{
   CHECK_IN(pMaterial);
   m_TemporaryStrandMaterial = pMaterial;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_TemporaryStrandMaterial(IPrestressingStrand** ppMaterial)
{
   CHECK_RETOBJ(ppMaterial);
   return m_TemporaryStrandMaterial.CopyTo(ppMaterial);
}

STDMETHODIMP CPrecastGirder::get_StraightStrandGrid(EndType endType,IStrandGrid** grid)
{
   CHECK_RETOBJ(grid);

   return m_StraightGrid[endType].QueryInterface(grid);
}

STDMETHODIMP CPrecastGirder::get_TemporaryStrandGrid(EndType endType,IStrandGrid** grid)
{
   CHECK_RETOBJ(grid);

   return m_TempGrid[endType].QueryInterface(grid);
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandGridEnd(EndType endType,IStrandGrid** grid)
{
   CHECK_RETOBJ(grid);

   return m_HarpGridEnd[endType].QueryInterface(grid);
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandGridHP(EndType endType,IStrandGrid** grid)
{
   CHECK_RETOBJ(grid);

   return m_HarpGridHp[endType].QueryInterface(grid);
}

STDMETHODIMP CPrecastGirder::put_AllowOddNumberOfHarpedStrands(VARIANT_BOOL bUseMin)
{
   m_AllowOddNumberOfHarpedStrands = bUseMin;

   if (bUseMin== VARIANT_TRUE)
   {
      // temporary fill array for harped fill at hp - only used if odd is true
      if (!m_OddHpFill)
      {
         m_OddHpFill.CoCreateInstance(CLSID_IndexArray);
      }
   }

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_AllowOddNumberOfHarpedStrands(VARIANT_BOOL* bUseMin)
{
   *bUseMin=m_AllowOddNumberOfHarpedStrands;
   return S_OK;
}


STDMETHODIMP CPrecastGirder::get_HarpedStrandAdjustmentEnd(Float64* offset)
{
   return m_HarpGridEnd[etStart]->get_VerticalStrandAdjustment(offset);
}

STDMETHODIMP CPrecastGirder::put_HarpedStrandAdjustmentEnd(Float64 offset)
{
   // cannot adjust if increment is less than zero
   Float64 increment, dummy;
   m_pStrandMover->get_StrandIncrements(&increment, &dummy);

   if (increment<0.0 && !IsZero(offset))
   {
      ATLASSERT(0); // cannot adjust if increment<0.0
      m_HarpGridEnd[etStart]->put_VerticalStrandAdjustment(0.0);
      m_HarpGridEnd[etEnd]->put_VerticalStrandAdjustment(0.0);
      return E_INVALIDARG;
   }
   else
   {
      m_HarpGridEnd[etStart]->put_VerticalStrandAdjustment(offset);
      m_HarpGridEnd[etEnd]->put_VerticalStrandAdjustment(offset);
      return S_OK;
   }
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandAdjustmentHP(Float64* offset)
{
   return m_HarpGridHp[etStart]->get_VerticalStrandAdjustment(offset);
}

STDMETHODIMP CPrecastGirder::put_HarpedStrandAdjustmentHP(Float64 offset)
{
   // cannot adjust if increment is less than zero
   Float64 increment, dummy;
   m_pStrandMover->get_StrandIncrements( &dummy, &increment );

   if (increment<0.0 && !IsZero(offset))
   {
      ATLASSERT(0); // cannot adjust if increment<0.0
      m_HarpGridHp[etStart]->put_VerticalStrandAdjustment(0.0);
      m_HarpGridHp[etEnd]->put_VerticalStrandAdjustment(0.0);
      return E_INVALIDARG;
   }
   else
   {
      m_HarpGridHp[etStart]->put_VerticalStrandAdjustment(offset);
      m_HarpGridHp[etEnd]->put_VerticalStrandAdjustment(offset);
      return S_OK;
   }
}

STDMETHODIMP CPrecastGirder::SetHarpingPoints(Float64 hp1,Float64 hp2)
{
   // must be positive values... HarpPointMeasure will indicate if this is fractional
   if ( hp1 < 0 || hp2 < 0 )
   {
      ATLASSERT(false);
      return E_INVALIDARG;
   }

   m_HP1 = hp1;
   m_HP2 = hp2;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetHarpingPoints(Float64* hp1,Float64* hp2)
{
   CHECK_RETVAL(hp1);
   CHECK_RETVAL(hp2);

   *hp1 = m_HP1;
   *hp2 = m_HP2;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::put_HarpingPointMeasure(HarpPointMeasure measure)
{
   m_HPMeasure = measure;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_HarpingPointMeasure(HarpPointMeasure* measure)
{
   CHECK_RETVAL(measure);
   *measure = m_HPMeasure;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::put_HarpingPointReference(HarpPointReference hpRef)
{
   m_HPReference = hpRef;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_HarpingPointReference(HarpPointReference* hpRef)
{
   CHECK_RETVAL(hpRef);
   *hpRef = m_HPReference;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetHarpingPointLocations(Float64* hp1,Float64* hp2)
{
   CHECK_RETVAL(hp1);
   CHECK_RETVAL(hp2);

   GetHarpPointLocations(*hp1,*hp2);
   return S_OK;
}

STDMETHODIMP CPrecastGirder::put_UseMinHarpPointDistance(VARIANT_BOOL bUseMin)
{
   m_bUseMinHpDistance = bUseMin;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_UseMinHarpPointDistance(VARIANT_BOOL* bUseMin)
{
   CHECK_RETVAL(bUseMin);
   *bUseMin = m_bUseMinHpDistance;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::put_MinHarpPointDistance(Float64 minHpDist)
{
   m_MinHpDist = minHpDist;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_MinHarpPointDistance(Float64* minHpDist)
{
   CHECK_RETVAL(minHpDist);
   *minHpDist = m_MinHpDist;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_SpanLength(Float64* length)
{
   CHECK_RETVAL(length);

   DoUpdateLengths();

   *length = m_Lengths.dbSpanLength;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_GirderLength(Float64* length)
{
   CHECK_RETVAL(length);

   DoUpdateLengths();

   *length = m_Lengths.dbGirderLength;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_LeftEndDistance(Float64* size)
{
   CHECK_RETVAL(size);

   DoUpdateLengths();

   *size = m_Lengths.dbLeftEndDistance;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_RightEndDistance(Float64* size)
{
   CHECK_RETVAL(size);

   DoUpdateLengths();

   *size = m_Lengths.dbRightEndDistance;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_LeftBearingOffset(Float64* offset)
{
   CHECK_RETVAL(offset);

   DoUpdateLengths();

   *offset = m_Lengths.dbLeftBearingOffset;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_RightBearingOffset(Float64* offset)
{
   CHECK_RETVAL(offset);

   DoUpdateLengths();

   *offset = m_Lengths.dbRightBearingOffset;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetEndPoints(IPoint2d** pntPier1,IPoint2d** pntEnd1,IPoint2d** pntBrg1,IPoint2d** pntBrg2,IPoint2d** pntEnd2,IPoint2d** pntPier2)
{
   CComPtr<IGirderLine> girderLine;
   m_pSegment->get_GirderLine(&girderLine);

   return girderLine->GetEndPoints(pntPier1,pntEnd1,pntBrg1,pntBrg2,pntEnd2,pntPier2);
}


STDMETHODIMP CPrecastGirder::get_HarpedMaxStrandFill(/*[out,retval]*/IIndexArray** fill)
{
   CHECK_RETOBJ(fill);

   UpdateMaxStrandFill();

   return m_HarpedMaxStrandFill.CopyTo(fill);
}

HRESULT CPrecastGirder::UpdateMaxStrandFill()
{
   // this is not simple because we have two grids to deal with
   if (m_UpdateHarpedMaxFill)
   {
      CComQIPtr<IStrandGridFiller> pEndGridFiller(m_HarpGridEnd[etStart]);
      CComQIPtr<IStrandGridFiller> pHPGridFiller(m_HarpGridHp[etStart]);
      HRESULT hr = m_StrandFillTool->ComputeHarpedStrandMaxFill(pEndGridFiller,pHPGridFiller,&m_MaxHarpedStrands,&m_HarpedMaxStrandFill);
      if ( FAILED(hr) )
         return hr;

      m_UpdateHarpedMaxFill = false;
   }

      return S_OK;
}

// these functions are easier since there is only a single strand grid for each
STDMETHODIMP CPrecastGirder::get_TemporaryMaxStrandFill(/*[out,retval]*/IIndexArray** fill)
{
   return m_TempGrid[etStart]->GetMaxStrandFill(fill);
}

STDMETHODIMP CPrecastGirder::get_StraightMaxStrandFill(/*[out,retval]*/IIndexArray** fill)
{
   return m_StraightGrid[etStart]->GetMaxStrandFill(fill);
}

STDMETHODIMP CPrecastGirder::get_StraightStrandFill(IIndexArray** fill)
{
   return m_StraightGrid[etStart]->get_StrandFill(fill);
}

STDMETHODIMP CPrecastGirder::put_StraightStrandFill(/*[inl]*/IIndexArray* fill)
{
   HRESULT hr = m_StraightGrid[etStart]->put_StrandFill(fill);
   if ( FAILED(hr) )
      return hr;

   hr = m_StraightGrid[etEnd]->put_StrandFill(fill);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandFill(IIndexArray** fill)
{
   return m_HarpGridEnd[etStart]->get_StrandFill(fill);
}

STDMETHODIMP CPrecastGirder::put_HarpedStrandFill(/*[inl]*/IIndexArray* fill)
{
   HRESULT hr = m_HarpGridEnd[etStart]->put_StrandFill(fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = m_HarpGridEnd[etEnd]->put_StrandFill(fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   CComPtr<IIndexArray> hp_fill;
   hr = ComputeHpFill(fill, &hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = m_HarpGridHp[etStart]->put_StrandFill(hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = m_HarpGridHp[etEnd]->put_StrandFill(hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_TemporaryStrandFill(IIndexArray** fill)
{
   return m_TempGrid[etStart]->get_StrandFill(fill);
}

STDMETHODIMP CPrecastGirder::put_TemporaryStrandFill(/*[inl]*/IIndexArray* fill)
{
   HRESULT hr = m_TempGrid[etStart]->put_StrandFill(fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = m_TempGrid[etEnd]->put_StrandFill(fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   return S_OK;
}


STDMETHODIMP CPrecastGirder::get_StraightStrandPositions(Float64 distFromStart, IPoint2dCollection** points)
{
   CComPtr<IIndexArray> fill;
   m_StraightGrid[etStart]->get_StrandFill(&fill);
   return get_StraightStrandPositionsEx(distFromStart,fill,points);
}

STDMETHODIMP CPrecastGirder::get_StraightStrandPositionsEx(Float64 distFromStart, IIndexArray* fill, IPoint2dCollection** points)
{
   Float64 gdrLength;
   get_GirderLength(&gdrLength);

   HRESULT hr = GetStrandPositions(distFromStart, gdrLength, fill, m_StraightGrid[etStart], fill, m_StraightGrid[etEnd], points);
   return hr;
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandPositions(Float64 distFromStart, IPoint2dCollection** points)
{
   CComPtr<IIndexArray> fill;
   m_HarpGridEnd[etStart]->get_StrandFill(&fill);
   return get_HarpedStrandPositionsEx(distFromStart,fill,points);
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandPositionsEx(Float64 distFromStart, IIndexArray* fill, IPoint2dCollection** points)
{
   CHECK_RETOBJ(points);

   // may need to interpolate
   Float64 gdrLength, leftHP, rightHP;
   get_GirderLength(&gdrLength);
   GetHarpingPointLocations(&leftHP, &rightHP);

   if ( IsEqual(distFromStart,0.0) )
   {
      // exactly at start of girder
      return m_HarpGridEnd[etStart]->GetStrandPositionsEx(fill,points);
   }
   else if ( IsEqual(distFromStart,gdrLength) )
   {
      // exactly at girder end
      return m_HarpGridEnd[etEnd]->GetStrandPositionsEx(fill,points);
   }
   else if ( leftHP <= distFromStart && distFromStart <= rightHP )
   {
      // between harp points
      CComPtr<IIndexArray> hp_fill;
      HRESULT hr = ComputeHpFill(fill, &hp_fill);
      ATLASSERT( SUCCEEDED(hr) );

      hr = GetStrandPositions(distFromStart - leftHP, rightHP-leftHP, hp_fill, m_HarpGridHp[etStart], hp_fill, m_HarpGridHp[etEnd], points);
      ATLASSERT( SUCCEEDED(hr) );
      return hr;
   }
   else if ( distFromStart < leftHP )
   {
      // on the sloped part of the harped strands at the left end of the girder

      // compute harped fill at hp
      CComPtr<IIndexArray> hp_fill;
      HRESULT hr = ComputeHpFill(fill, &hp_fill);
      ATLASSERT( SUCCEEDED(hr) );

      hr = GetStrandPositions(distFromStart, leftHP, fill, m_HarpGridEnd[etStart], hp_fill, m_HarpGridHp[etStart], points);
      ATLASSERT( SUCCEEDED(hr) );
      return hr;
   }
   else
   {
      ATLASSERT( rightHP < distFromStart );
      // on the sloped part of the harped strands at right end of girder
      // compute harped fill at hp
      CComPtr<IIndexArray> hp_fill;
      HRESULT hr = ComputeHpFill(fill, &hp_fill);
      ATLASSERT( SUCCEEDED(hr) );

      hr = GetStrandPositions(distFromStart - rightHP, gdrLength - rightHP, hp_fill, m_HarpGridHp[etEnd], fill, m_HarpGridEnd[etEnd], points);
      ATLASSERT( SUCCEEDED(hr) );
      return hr;
   }
}

STDMETHODIMP CPrecastGirder::get_TemporaryStrandPositions(Float64 distFromStart, IPoint2dCollection** points)
{
   CComPtr<IIndexArray> fill;
   m_TempGrid[etStart]->get_StrandFill(&fill);
   return get_TemporaryStrandPositionsEx(distFromStart,fill,points);
}

STDMETHODIMP CPrecastGirder::get_TemporaryStrandPositionsEx(Float64 distFromStart, IIndexArray* fill, IPoint2dCollection** points)
{
   Float64 gdrLength;
   get_GirderLength(&gdrLength);

   HRESULT hr = GetStrandPositions(distFromStart, gdrLength, fill, m_TempGrid[etStart], fill, m_TempGrid[etEnd], points);
   return hr;
}

STDMETHODIMP CPrecastGirder::StraightStrandIndexToGridIndex(/*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex)
{
   return m_StraightGrid[etStart]->StrandIndexToGridIndex(strandIndex, gridIndex);
}

STDMETHODIMP CPrecastGirder::StraightStrandIndexToGridIndexEx(/*[in]*/IIndexArray* fill, /*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex)
{
   return m_StraightGrid[etStart]->StrandIndexToGridIndexEx(fill, strandIndex, gridIndex);
}

STDMETHODIMP CPrecastGirder::HarpedStrandIndexToGridIndex(/*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex)
{
   return m_HarpGridEnd[etStart]->StrandIndexToGridIndex(strandIndex, gridIndex);
}

STDMETHODIMP CPrecastGirder::HarpedStrandIndexToGridIndexEx(/*[in]*/IIndexArray* fill, /*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex)
{
   return m_HarpGridEnd[etStart]->StrandIndexToGridIndexEx(fill, strandIndex, gridIndex);
}

STDMETHODIMP CPrecastGirder::TemporaryStrandIndexToGridIndex(/*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex)
{
   return m_TempGrid[etStart]->StrandIndexToGridIndex(strandIndex, gridIndex);
}

STDMETHODIMP CPrecastGirder::TemporaryStrandIndexToGridIndexEx(/*[in]*/IIndexArray* fill, /*[in]*/StrandIndexType strandIndex, /*[out,retval]*/GridIndexType* gridIndex)
{
   return m_HarpGridEnd[etStart]->StrandIndexToGridIndexEx(fill, strandIndex, gridIndex);
}

// Compute bounding boxes of harped and straight strands accounting for vertical offsets for harped strands
STDMETHODIMP CPrecastGirder::StraightStrandBoundingBox(EndType endType,IRect2d** box)
{
   return m_StraightGrid[endType]->get_StrandBoundingBox(box);
}

STDMETHODIMP CPrecastGirder::StraightStrandBoundingBoxEx( EndType endType,IIndexArray* fill, IRect2d** box)
{
   return m_StraightGrid[endType]->get_StrandBoundingBoxEx(fill, box);
}

STDMETHODIMP CPrecastGirder::HarpedEndStrandBoundingBox(EndType endType,IRect2d** box)
{
   return m_HarpGridEnd[endType]->get_StrandBoundingBox(box);
}

STDMETHODIMP CPrecastGirder::HarpedEndStrandBoundingBoxEx( EndType endType,IIndexArray* fill, IRect2d** box)
{
   return m_HarpGridEnd[endType]->get_StrandBoundingBoxEx(fill, box);
}


STDMETHODIMP CPrecastGirder::HarpedHpStrandBoundingBox(EndType endType,IRect2d** box)
{
   return m_HarpGridHp[endType]->get_StrandBoundingBox(box);
}

STDMETHODIMP CPrecastGirder::HarpedHpStrandBoundingBoxEx(EndType endType, IIndexArray* fill, IRect2d** box)
{
   // compute harped fill at hp
   CComPtr<IIndexArray> hp_fill;
   HRESULT hr = ComputeHpFill(fill, &hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   return m_HarpGridHp[endType]->get_StrandBoundingBoxEx(hp_fill, box);
}

STDMETHODIMP CPrecastGirder::get_TopElevation(/*[out,retval]*/Float64* top)
{
   return m_pStrandMover->get_TopElevation(top);
}


STDMETHODIMP CPrecastGirder::GetHarpedEndAdjustmentBounds(/*[out]*/Float64* minDownwardAdjustment, /*[out]*/Float64* maxUpwardAdjustment)

{
   CHECK_RETVAL(minDownwardAdjustment);
   CHECK_RETVAL(maxUpwardAdjustment);

   HRESULT hr(S_OK);

   EndType endType = etStart;

   // get unadjusted top and bottom bounds
   Float64 top, bottom;
   hr = m_HarpGridEnd[endType]->get_FilledGridBounds(&bottom,&top);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   Float64 adjust;
   hr = m_HarpGridEnd[endType]->get_VerticalStrandAdjustment(&adjust);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   bottom -= adjust;
   top    -= adjust;

   if (bottom==0.0 && top==0.0)
   {
      // no strands exist so we cannot adjust them
      *minDownwardAdjustment = 0.0;
      *maxUpwardAdjustment   = 0.0;
   }
   else
   {
      // get max locations of strands
      Float64 bottom_min, top_max;
      hr = m_pStrandMover->get_EndStrandElevationBoundaries(&bottom_min, &top_max);
      if (FAILED(hr))
      {
         ATLASSERT(0);
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

STDMETHODIMP CPrecastGirder::GetHarpedEndAdjustmentBoundsEx(/*[in]*/ IIndexArray* fill, /*[out]*/Float64* minDownwardAdjustment, /*[out]*/Float64* maxUpwardAdjustment)

{
   CHECK_RETVAL(minDownwardAdjustment);
   CHECK_RETVAL(maxUpwardAdjustment);

   HRESULT hr(S_OK);

   EndType endType = etStart;

   // get adjusted top and bottom bounds
   Float64 top, bottom;
   hr = m_HarpGridEnd[endType]->get_FilledGridBoundsEx(fill,&bottom,&top);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   Float64 adjust;
   hr = m_HarpGridEnd[endType]->get_VerticalStrandAdjustment(&adjust);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   if (bottom==0.0 && top==0.0)
   {
      // no strands exist so we cannot adjust them
      *minDownwardAdjustment = 0.0;
      *maxUpwardAdjustment   = 0.0;
   }
   else
   {
      bottom -= adjust;
      top    -= adjust;

      // get max locations of strands
      Float64 bottom_min, top_max;
      hr = m_pStrandMover->get_EndStrandElevationBoundaries(&bottom_min, &top_max);
      if (FAILED(hr))
      {
         ATLASSERT(0);
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

STDMETHODIMP CPrecastGirder::GetHarpedHpAdjustmentBounds(/*[out]*/Float64* minDownwardAdjustment, /*[out]*/Float64* maxUpwardAdjustment)

{
   CHECK_RETVAL(minDownwardAdjustment);
   CHECK_RETVAL(maxUpwardAdjustment);

   HRESULT hr(S_OK);

   EndType endType = etStart;

   // get unadjusted top and bottom bounds
   Float64 top, bottom;
   hr = m_HarpGridHp[endType]->get_FilledGridBounds(&bottom,&top);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   Float64 adjust;
   hr = m_HarpGridHp[endType]->get_VerticalStrandAdjustment(&adjust);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   bottom -= adjust;
   top    -= adjust;

   if (bottom==0.0 && top==0.0)
   {
      // no strands exist so we cannot adjust them
      *minDownwardAdjustment = 0.0;
      *maxUpwardAdjustment   = 0.0;
   }
   else
   {
      // get max locations of strands
      Float64 bottom_min, top_max;
      hr = m_pStrandMover->get_HpStrandElevationBoundaries(&bottom_min, &top_max);
      if (FAILED(hr))
      {
         ATLASSERT(0);
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

STDMETHODIMP CPrecastGirder::GetHarpedHpAdjustmentBoundsEx(/*[in]*/ IIndexArray* fill, /*[out]*/Float64* minDownwardAdjustment, /*[out]*/Float64* maxUpwardAdjustment)

{
   CHECK_RETVAL(minDownwardAdjustment);
   CHECK_RETVAL(maxUpwardAdjustment);

   HRESULT hr(S_OK);

   EndType endType = etStart;

   // compute hp fill, if different
   CComPtr<IIndexArray> hp_fill;
   hr = ComputeHpFill(fill, &hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // get unadjusted top and bottom bounds
   Float64 top, bottom;
   hr = m_HarpGridHp[endType]->get_FilledGridBoundsEx(hp_fill,&bottom,&top);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   Float64 adjust;
   hr = m_HarpGridHp[endType]->get_VerticalStrandAdjustment(&adjust);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   bottom -= adjust;
   top    -= adjust;


   if (bottom==0.0 && top==0.0)
   {
      // no strands exist so we cannot adjust them
      *minDownwardAdjustment = 0.0;
      *maxUpwardAdjustment   = 0.0;
   }
   else
   {
      // get max locations of strands
      Float64 bottom_min, top_max;
      hr = m_pStrandMover->get_HpStrandElevationBoundaries(&bottom_min, &top_max);
      if (FAILED(hr))
      {
         ATLASSERT(0);
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

STDMETHODIMP CPrecastGirder::GetHarpedEndFilledGridBoundsEx(/*[in]*/IIndexArray* fill, /*[out]*/Float64* bottomElev, /*[out]*/Float64* topElev)
{
   return m_HarpGridEnd[etStart]->get_FilledGridBoundsEx( fill, bottomElev, topElev);
}

STDMETHODIMP CPrecastGirder::GetHarpedHpFilledGridBoundsEx(/*[in]*/IIndexArray* fill, /*[out]*/Float64* bottomElev, /*[out]*/Float64* topElev)
{
   // compute hp fill, if different
   CComPtr<IIndexArray> hp_fill;
   HRESULT hr = ComputeHpFill(fill, &hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   return m_HarpGridHp[etStart]->get_FilledGridBoundsEx( hp_fill, bottomElev, topElev);
}

STDMETHODIMP CPrecastGirder::get_HarpedEndAdjustmentIncrement(/*[out,retval]*/Float64* increment)
{
   StrandIndexType cnt;
   HRESULT hr = m_HarpGridEnd[etStart]->get_MaxStrandCount(&cnt);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   if (cnt>0)
   {
      Float64 dummy;
      return m_pStrandMover->get_StrandIncrements(increment, &dummy);
   }
   else
   {
      *increment = -1.0;
      return S_OK;
   }
}

STDMETHODIMP CPrecastGirder::get_HarpedHpAdjustmentIncrement(/*[out,retval]*/Float64* increment)
{
   StrandIndexType cnt;
   HRESULT hr = m_HarpGridEnd[etStart]->get_MaxStrandCount(&cnt);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   if (cnt>0)
   {
      Float64 dummy;
      return m_pStrandMover->get_StrandIncrements(&dummy, increment);
   }
   else
   {
      *increment = -1.0;
      return S_OK;
   }
}

STDMETHODIMP CPrecastGirder::HarpedEndStrandBoundaryCheck(Float64* adjustment)
{
   CHECK_RETVAL(adjustment);
   
   HRESULT hr(S_OK);

   Float64 current_adjustment;
   hr = m_HarpGridEnd[etStart]->get_VerticalStrandAdjustment(&current_adjustment);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   Float64 min_adjust, max_adjust;
   hr = GetHarpedEndAdjustmentBounds(&min_adjust, &max_adjust);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   *adjustment = 0.0; // the default

   if (current_adjustment > max_adjust)
   {
      // too high - must adjust down
      *adjustment = max_adjust - current_adjustment;
   }
   else if (current_adjustment < min_adjust)
   {
      // too low - adjust upward
      *adjustment = min_adjust - current_adjustment;
   }

   return hr;
}

STDMETHODIMP CPrecastGirder::HarpedHpStrandBoundaryCheck(Float64* adjustment)
{
   CHECK_RETVAL(adjustment);
   
   HRESULT hr(S_OK);

   Float64 current_adjustment;
   hr = m_HarpGridHp[etStart]->get_VerticalStrandAdjustment(&current_adjustment);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   Float64 min_adjust, max_adjust;
   hr = GetHarpedHpAdjustmentBounds(&min_adjust, &max_adjust);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   *adjustment = 0.0; // the default

   if (current_adjustment > max_adjust)
   {
      // too high - must adjust down
      *adjustment = max_adjust - current_adjustment;
   }
   else if (current_adjustment < min_adjust)
   {
      // too low - adjust upward
      *adjustment = min_adjust - current_adjustment;
   }

   return hr;
}



STDMETHODIMP CPrecastGirder::ComputeMaxHarpedStrandSlope(Float64 distFromStart,Float64* slope)
{
   CHECK_RETVAL(slope);

   Float64 hp1,hp2;
   GetHarpPointLocations(hp1,hp2);

   if ( hp1 < distFromStart && distFromStart < hp2 )
   {
      // point under consideration is between harp points
      *slope = DBL_MAX;
      return S_OK;
   }

   EndType endType = (distFromStart <= hp1 ? etStart : etEnd);

   StrandIndexType nstrands;
   m_HarpGridEnd[endType]->GetStrandCount(&nstrands);
   if ( nstrands == 0 )
   {
      *slope = DBL_MAX;
      return S_OK;
   }




   Float64 gdr_length;
   get_GirderLength(&gdr_length);

   ATLASSERT(distFromStart>=0.0 && distFromStart<=gdr_length);

   Float64 run; // as in rise over run
   CComPtr<IPoint2dCollection> start, hp;
   if ( distFromStart <= hp1 )
   {
      get_HarpedStrandPositions(0.0,&start);
      get_HarpedStrandPositions(hp1,&hp);
      run = hp1;
   }
   else if ( hp2 <= distFromStart )
   {
      get_HarpedStrandPositions(gdr_length,&start);
      get_HarpedStrandPositions(hp2,&hp);
      run = gdr_length - hp2;
   }

   CollectionIndexType nStrandStart,nStrandHP;
   start->get_Count(&nStrandStart);
   hp->get_Count(&nStrandHP);
   ATLASSERT(nStrandStart == nStrandHP && nStrandStart == nstrands);

   *slope = DBL_MAX;
   for ( StrandIndexType strandIdx = 0; strandIdx < nstrands; strandIdx++ )
   {
      CComPtr<IPoint2d> pntStart, pntEnd;
      start->get_Item(strandIdx,&pntStart);
      hp->get_Item(strandIdx,&pntEnd);

      Float64 ys, ye;
      pntStart->get_Y(&ys);
      pntEnd->get_Y(&ye);

      Float64 rise = ys - ye;

      if (rise!=0.0)
      {
         *slope = _cpp_min(*slope,run/rise);
      }
   }

   return S_OK;
}

STDMETHODIMP CPrecastGirder::ComputeMaxHarpedStrandSlopeEx(Float64 distFromStart, IIndexArray* fill,  Float64 endOffset, Float64 hpOffset,Float64* slope)
{
   CHECK_RETVAL(slope);

   StrandIndexType nstrands;
   m_HarpGridEnd[etStart]->GetStrandCountEx(fill, &nstrands);
   if ( nstrands == 0 )
   {
      *slope = DBL_MAX;
      return S_OK;
   }

   Float64 hp1,hp2;
   GetHarpPointLocations(hp1,hp2);

   if ( hp1 < distFromStart && distFromStart < hp2 )
   {
      // point under consideration is between harp points
      *slope = DBL_MAX;
      return S_OK;
   }

   Float64 gdr_length;
   get_GirderLength(&gdr_length);

   ATLASSERT(distFromStart>=0.0 && distFromStart<=gdr_length);

   EndType endType = ( distFromStart < hp1 ) ? etStart : etEnd;

   // strand positions - adjusted for current offset value
   CComPtr<IPoint2dCollection> end_strands, hp_strands;
   m_HarpGridEnd[endType]->GetStrandPositionsEx(fill, &end_strands);
   m_HarpGridHp[endType]->GetStrandPositionsEx(fill, &hp_strands);

   // need to subtract current offsets out so we can add our own
   Float64 curr_end_offset, curr_hp_offset;
   m_HarpGridEnd[endType]->get_VerticalStrandAdjustment(&curr_end_offset);
   m_HarpGridHp[endType]->get_VerticalStrandAdjustment(&curr_hp_offset);

   Float64 run; // as in rise over run
   if ( ::IsLE(distFromStart,hp1) )
   {
      run = hp1;
   }
   else if ( ::IsLE(hp2,distFromStart) )
   {
      run = gdr_length - hp2;
   }

   CollectionIndexType nStrandStart,nStrandHP;
   end_strands->get_Count(&nStrandStart);
   hp_strands->get_Count(&nStrandHP);
   ATLASSERT(nStrandStart == nStrandHP && nStrandStart == nstrands);

   *slope = DBL_MAX;
   for ( StrandIndexType strandIdx = 0; strandIdx < nstrands; strandIdx++ )
   {
      CComPtr<IPoint2d> pntEnd, pntHP;
      end_strands->get_Item(strandIdx,&pntEnd);
      hp_strands->get_Item(strandIdx,&pntHP);

      Float64 yend, yhp;
      pntEnd->get_Y(&yend);
      pntHP->get_Y(&yhp);

      Float64 rise = (yend - curr_end_offset + endOffset) - (yhp - curr_hp_offset + hpOffset);

      if (rise!=0.0)
      {
         *slope = _cpp_min(*slope,run/rise);
      }
   }
    
   return S_OK;
}


STDMETHODIMP CPrecastGirder::ComputeAvgHarpedStrandSlopeEx(Float64 distFromStart,IIndexArray* fill,Float64 endOffset,Float64 hpOffset,Float64* slope)
{
   CHECK_RETVAL(slope);

   Float64 hp1,hp2;
   GetHarpPointLocations(hp1,hp2);

   Float64 gdr_length;
   get_GirderLength(&gdr_length);

   ATLASSERT(0.0 <= distFromStart && distFromStart <= gdr_length);

   if ( ::IsLE(distFromStart,hp1) )
   {
      Float64 cg_x, cg_end, cg_hp;
      m_HarpGridEnd[etStart]->get_CGEx(fill, &cg_x, &cg_end);
      m_HarpGridHp[etStart]->get_CGEx(fill, &cg_x, &cg_hp);

      // cg values in grid are adjusted for internal offset - remove them
      Float64 end_offset, hp_offset;
      m_HarpGridEnd[etStart]->get_VerticalStrandAdjustment(&end_offset);
      m_HarpGridHp[etStart]->get_VerticalStrandAdjustment(&hp_offset);

      cg_end -= end_offset;
      cg_hp  -= hp_offset;

      // add external adjustments
      cg_end += endOffset;
      cg_hp  += hpOffset;

      if (cg_end!=cg_hp)
         *slope = hp1/(cg_end - cg_hp);
      else
         *slope = DBL_MAX;
   }
   else if ( ::IsLE(hp2,distFromStart) )
   {
      Float64 cg_x, cg_end, cg_hp;
      m_HarpGridEnd[etEnd]->get_CGEx(fill, &cg_x, &cg_end);
      m_HarpGridHp[etEnd]->get_CGEx(fill, &cg_x, &cg_hp);

      // cg values are adjusted for internal offset - remove them
      Float64 end_offset, hp_offset;
      m_HarpGridEnd[etEnd]->get_VerticalStrandAdjustment(&end_offset);
      m_HarpGridHp[etEnd]->get_VerticalStrandAdjustment(&hp_offset);

      cg_end -= end_offset;
      cg_hp  -= hp_offset;

      // add external adjustments
      cg_end += endOffset;
      cg_hp  += hpOffset;

      if (cg_end!=cg_hp)
         *slope = (gdr_length - hp2) / (cg_end - cg_hp);
      else
         *slope = DBL_MAX;
   }
   else
   {
      ATLASSERT( hp1 < distFromStart && distFromStart < hp2 );
      *slope = DBL_MAX;
   }

   return S_OK;
}

STDMETHODIMP CPrecastGirder::ComputeAvgHarpedStrandSlope(Float64 distFromStart, Float64* slope)
{
   CHECK_RETVAL(slope);

   Float64 hp1,hp2;
   GetHarpPointLocations(hp1,hp2);

   Float64 gdr_length;
   get_GirderLength(&gdr_length);

   ATLASSERT(distFromStart>=0.0 && distFromStart<=gdr_length+TOLERANCE);

   if ( ::IsLE(distFromStart,hp1) )
   {
      Float64 cg_x, cg_end, cg_hp;
      m_HarpGridEnd[etStart]->get_CG(&cg_x, &cg_end);
      m_HarpGridHp[etStart]->get_CG(&cg_x, &cg_hp);

      if (cg_end!=cg_hp)
         *slope = hp1/(cg_end - cg_hp);
      else
         *slope = DBL_MAX;
   }
   else if ( ::IsLE(hp2,distFromStart) )
   {
      Float64 cg_x, cg_end, cg_hp;
      m_HarpGridEnd[etEnd]->get_CG(&cg_x, &cg_end);
      m_HarpGridHp[etEnd]->get_CG(&cg_x, &cg_hp);

      if (cg_end!=cg_hp)
         *slope = (gdr_length - hp2) / (cg_end - cg_hp);
      else
         *slope = DBL_MAX;
   }
   else
   {
      ATLASSERT( hp1 < distFromStart && distFromStart < hp2 );
      *slope = DBL_MAX;
   }

   return S_OK;
}


STDMETHODIMP CPrecastGirder::get_MaxStraightStrands(StrandIndexType* nStrands)
{
   return m_StraightGrid[etStart]->get_MaxStrandCount(nStrands);
}

STDMETHODIMP CPrecastGirder::get_MaxHarpedStrands(StrandIndexType* nStrands)
{
   // this is complicated because we are pulling from two strand grids
   UpdateMaxStrandFill();

   *nStrands = m_MaxHarpedStrands;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_MaxTemporaryStrands(StrandIndexType* nStrands)
{
   return m_TempGrid[etStart]->get_MaxStrandCount(nStrands);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandCount(/*[out,retval]*/ StrandIndexType* nStrands)
{
   return m_StraightGrid[etStart]->GetStrandCount(nStrands);
}

STDMETHODIMP CPrecastGirder::GetHarpedStrandCount(/*[out,retval]*/ StrandIndexType* nStrands)
{
   StrandIndexType nsend;
   m_HarpGridEnd[etStart]->GetStrandCount(&nsend);
   m_HarpGridHp[etStart]->GetStrandCount(nStrands);
   ATLASSERT(nsend==*nStrands);
   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetTemporaryStrandCount(/*[out,retval]*/ StrandIndexType* nStrands)
{
   return m_TempGrid[etStart]->GetStrandCount(nStrands);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandCountEx(/*[in]*/ IIndexArray* fill, /*[out,retval]*/ StrandIndexType* nStrands)
{
   return m_StraightGrid[etStart]->GetStrandCountEx(fill, nStrands);
}

STDMETHODIMP CPrecastGirder::GetHarpedStrandCountEx(/*[in]*/ IIndexArray* fill, /*[out,retval]*/ StrandIndexType* nStrands)
{
   StrandIndexType nsend;
   HRESULT hr = m_HarpGridEnd[etStart]->GetStrandCountEx(fill, &nsend);

#ifdef _DEBUG
   // compute hp fill, if different
   CComPtr<IIndexArray> hp_fill;
   hr = ComputeHpFill(fill, &hp_fill);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   m_HarpGridHp[etStart]->GetStrandCountEx(hp_fill, nStrands);
   ATLASSERT(nsend==*nStrands);
#endif _DEBUG

   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetTemporaryStrandCountEx(/*[in]*/ IIndexArray* fill, /*[out,retval]*/ StrandIndexType* nStrands)
{
   return m_TempGrid[etStart]->GetStrandCountEx(fill, nStrands);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandDebondCount(/*[out,retval]*/ StrandIndexType* count)
{
   return m_StraightGrid[etStart]->GetStrandDebondCount(count);
}

STDMETHODIMP CPrecastGirder::ClearStraightStrandDebonding()
{
   m_StraightGrid[etStart]->ClearDebonding();
   m_StraightGrid[etEnd]->ClearDebonding();
   return S_OK;
}

STDMETHODIMP CPrecastGirder::DebondStraightStrandByGridIndex(/*[in]*/GridIndexType grdIndex,/*[in]*/Float64 l1,/*[in]*/Float64 l2)
{
   m_StraightGrid[etStart]->DebondStrandByGridIndex(grdIndex, l1, l2);
   m_StraightGrid[etEnd]->DebondStrandByGridIndex(grdIndex, l1, l2);
   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetDebondedStraightStrandsByGridIndex(/*[out,retval]*/IIndexArray** grdIndexes)
{
   return m_StraightGrid[etStart]->GetDebondedStrandsByGridIndex(grdIndexes);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandDebondLengthByGridIndex(/*[in]*/GridIndexType grdIndex,/*[out]*/Float64* YCoord, /*[out]*/Float64* l1,/*[out]*/Float64* l2)
{
   return m_StraightGrid[etStart]->GetDebondLengthByGridIndex(grdIndex, YCoord, l1, l2);
}

// Debonded straight strands based on Positions index (i.e., from get_StraightStrandPositions)
STDMETHODIMP CPrecastGirder::GetStraightStrandDebondLengthByPositionIndex(/*[in]*/StrandIndexType positionIndex,/*[out]*/Float64* YCoord, /*[out]*/Float64* l1,/*[out]*/Float64* l2)
{
   return m_StraightGrid[etStart]->GetDebondLengthByPositionIndex(positionIndex, YCoord, l1, l2);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandsDebondedByPositionIndex(/*[in]*/Float64 distFromStart, /*[out,retval]*/IIndexArray** positionIndexes)
{
   Float64 grd_length;
   this->get_GirderLength(&grd_length);

   return m_StraightGrid[etStart]->GetStrandsDebondedByPositionIndex(distFromStart, grd_length, positionIndexes);
}

STDMETHODIMP CPrecastGirder::get_StraightStrandRowsWithStrand(/*[out,retval]*/RowIndexType* nRows)
{
   return m_StraightGrid[etStart]->get_RowsWithStrand(nRows);
}

STDMETHODIMP CPrecastGirder::get_NumStraightStrandsInRow(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/StrandIndexType* nStrands)
{
   return m_StraightGrid[etStart]->get_NumStrandsInRow(rowIdx, nStrands);
}

STDMETHODIMP CPrecastGirder::get_StraightStrandsInRow(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/IIndexArray** grdIndexes)
{
   return m_StraightGrid[etStart]->get_StrandsInRow(rowIdx, grdIndexes);
}

STDMETHODIMP CPrecastGirder::get_StraightStrandDebondInRow(/*[in]*/ RowIndexType rowIdx,/*[out,retval]*/StrandIndexType* nStrands)
{
   return m_StraightGrid[etStart]->get_StrandDebondInRow(rowIdx, nStrands);
}

STDMETHODIMP CPrecastGirder::IsExteriorStraightStrandDebondedInRow(/*[in]*/ RowIndexType rowIndex,/*[out,retval]*/VARIANT_BOOL* bResult)
{
   return m_StraightGrid[etStart]->IsExteriorStrandDebondedInRow(rowIndex, bResult);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandDebondAtSections(/*[out]*/IDblArray** arrLeft,/*[out]*/IDblArray** arrRight)
{
   return m_StraightGrid[etStart]->GetDebondSections(arrLeft, arrRight);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandDebondAtLeftSection(/*[in]*/SectionIndexType sectionIdx,/*[out,retval]*/IIndexArray** pstnIndexes)
{
   return m_StraightGrid[etStart]->GetDebondAtLeftSection(sectionIdx, pstnIndexes);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandDebondAtRightSection(/*[in]*/SectionIndexType sectionIdx,/*[out,retval]*/IIndexArray** pstnIndexes)
{
   return m_StraightGrid[etStart]->GetDebondAtRightSection(sectionIdx, pstnIndexes);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandBondedLengthByPositionIndex(/*[in]*/StrandIndexType positionIndex, /*[in]*/Float64 distFromStart, 
                                              /*[out]*/Float64* YCoord, /*[out]*/Float64* leftBond, /*[out]*/Float64* rightBond)
{
   Float64 gdr_length;
   get_GirderLength(&gdr_length);

   return m_StraightGrid[etStart]->GetBondedLengthByPositionIndex(positionIndex, distFromStart, gdr_length, YCoord, leftBond, rightBond);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandBondedLengthByGridIndex(/*[in]*/GridIndexType grdIndex, /*[in]*/Float64 distFromStart, 
                                              /*[out]*/Float64* YCoord, /*[out]*/Float64* leftBond, /*[out]*/Float64* rightBond)
{
   Float64 gdr_length;
   get_GirderLength(&gdr_length);

   return m_StraightGrid[etStart]->GetBondedLengthByGridIndex(grdIndex, distFromStart, gdr_length, YCoord, leftBond, rightBond);
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandRowsWithStrand(RowIndexType* nRows)
{
   return m_HarpGridHp[etStart]->get_RowsWithStrand(nRows);
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandsInRow(RowIndexType rowIdx,IIndexArray** gridIndexes)
{
   return m_HarpGridHp[etStart]->get_StrandsInRow(rowIdx, gridIndexes);
}

STDMETHODIMP CPrecastGirder::get_NumHarpedStrandsInRow(RowIndexType rowIdx,StrandIndexType* nStrands)
{
   return m_HarpGridHp[etStart]->get_NumStrandsInRow(rowIdx, nStrands);
}


STDMETHODIMP CPrecastGirder::get_RebarLayout(IRebarLayout** rebarLayout)
{
   CHECK_RETOBJ(rebarLayout);
   (*rebarLayout) = m_RebarLayout;
   (*rebarLayout)->AddRef();
   return S_OK;
}


///// PRIVATE /////
void CPrecastGirder::GetHarpPointLocations(Float64& hp1,Float64& hp2)
{
   hp1 = GetHarpPointLocation(m_HP1,false);
   hp2 = GetHarpPointLocation(m_HP2,true);

   ATLASSERT( hp1 <= hp2 );
}

Float64 CPrecastGirder::GetHarpPointLocation(Float64 hp,bool bRight)
{
   Float64 left_end_distance;
   Float64 right_end_distance;

   Float64 span_length;
   get_SpanLength(&span_length);

   Float64 gdr_length;
   get_GirderLength(&gdr_length);

   if ( m_HPMeasure == hpmFractionOfGirderLength )
      hp *= gdr_length;

   if ( m_HPMeasure == hpmFractionOfSpanLength )
      hp *= span_length;

   if ( m_bUseMinHpDistance == VARIANT_TRUE && hp < m_MinHpDist )
      hp = m_MinHpDist;

   // hp can now be considered the location of the harp point measured
   // from the point of reference. 

   // convert the hp from it's point of reference to the left end of the girder
   Float64 result;
   switch( m_HPReference )
   {
   case hprEndOfGirder:
      result = (bRight ? gdr_length - hp : hp);
      if ( (bRight && result < gdr_length/2) || (!bRight && gdr_length/2 < result) )
         result = gdr_length/2;
      break;

   case hprCenterOfGirder:
      result = (bRight ? gdr_length/2 + hp : gdr_length/2 - hp);
      if ( (bRight && gdr_length < result) || (!bRight && result < 0) )
         result = gdr_length/2;
      break;

   case hprBearing:
      get_LeftEndDistance(&left_end_distance);
      get_RightEndDistance(&right_end_distance);
      result = (bRight ? gdr_length - right_end_distance - hp : left_end_distance + hp);
      if ( (bRight && result < gdr_length/2) || (!bRight && gdr_length/2 < result) )
         result = gdr_length/2;
      break;
   }

   ATLASSERT( 0 < result && result < gdr_length );
   return result;
}


HRESULT CPrecastGirder::GetStrandPositions(Float64 distFromStart, Float64 distBetweenGrids, IIndexArray* startFill, IStrandGridFiller* pStartGrid, IIndexArray* endFill, IStrandGridFiller* pEndGrid, IPoint2dCollection** points)
{
   CComPtr<IPoint2dCollection> startPoints;
   CComPtr<IPoint2dCollection> endPoints;
   pStartGrid->GetStrandPositionsEx(startFill,&startPoints);
   pEndGrid->GetStrandPositionsEx(endFill,&endPoints);

   CollectionIndexType nPoints;
   startPoints->get_Count(&nPoints);

#if defined _DEBUG
   CollectionIndexType np;
   endPoints->get_Count(&np);
   ATLASSERT(np == nPoints);
#endif

   CComPtr<IPoint2dCollection> pnts;
   pnts.CoCreateInstance(CLSID_Point2dCollection);
   for (CollectionIndexType idx = 0; idx < nPoints; idx++ )
   {
      CComPtr<IPoint2d> pntStart,  pntEnd;
      startPoints->get_Item(idx,&pntStart);
      endPoints->get_Item(idx,&pntEnd);

      Float64 sx,sy;
      pntStart->get_X(&sx);
      pntStart->get_Y(&sy);

      Float64 ex, ey;
      pntEnd->get_X(&ex);
      pntEnd->get_Y(&ey);

      Float64 x = ::LinInterp(distFromStart,sx,ex,distBetweenGrids);
      Float64 y = ::LinInterp(distFromStart,sy,ey,distBetweenGrids);

      CComPtr<IPoint2d> pnt;
      m_Point2dFactory->CreatePoint(&pnt);
      pnt->Move(x,y);
      pnts->Add(pnt);
   }

   (*points) = pnts;
   (*points)->AddRef();
   return S_OK;
}

HRESULT CPrecastGirder::ComputeHpFill(IIndexArray* endFill, IIndexArray** hpFill)
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
         CollectionIndexType fill_size;
         endFill->get_Count(&fill_size);
         m_OddHpFill->Reserve(fill_size);

         // put two strands in the first hp location
#if defined _DEBUG
         CollectionIndexType first_row;
         endFill->get_Item(0,&first_row);
         ASSERT(first_row == 1); // only one strand at the bottom... but we need it to be 2 for odd fill at top
#endif

         StrandIndexType running_cnt = 2;
         m_OddHpFill->Add(running_cnt); // start with 2 strands

         for (CollectionIndexType is = 1; is < fill_size; is++)
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
                  m_OddHpFill->Add(fill_val-1);
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

void CPrecastGirder::DoUpdateLengths()
{
   if (m_UpdateLengths)
   {
      CComPtr<IPoint2d> pntPier1, pntEnd1, pntBrg1;
      CComPtr<IPoint2d> pntPier2, pntEnd2, pntBrg2;
      GetEndPoints(&pntPier1,&pntEnd1,&pntBrg1,&pntBrg2,&pntEnd2,&pntPier2);

      pntEnd1->DistanceEx(pntEnd2,&m_Lengths.dbGirderLength);
      pntBrg1->DistanceEx(pntBrg2,&m_Lengths.dbSpanLength);
      pntPier1->DistanceEx(pntBrg1,&m_Lengths.dbLeftBearingOffset);
      pntPier2->DistanceEx(pntBrg2,&m_Lengths.dbRightBearingOffset);
      pntEnd1->DistanceEx(pntBrg1,&m_Lengths.dbLeftEndDistance);
      pntEnd2->DistanceEx(pntBrg2,&m_Lengths.dbRightEndDistance);

      m_UpdateLengths = false;
   }
}

