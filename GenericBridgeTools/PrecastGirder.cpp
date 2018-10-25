///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2015  Washington State Department of Transportation
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
#include "RebarLayout.h"
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

   CComObject<CRebarLayout>* pRebarLayout;
   CComObject<CRebarLayout>::CreateInstance(&pRebarLayout);
   m_RebarLayout = pRebarLayout;

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
   // ATL HAS BEEN CHANGED - The ref count is scrambled at this point
   // Not sure what will happen when we call AtlUnadvise

   //// we're dieing here so we can't kill ourself in the unadvise
   //ULONG cnt = this->AddRef();
   //ATLASSERT(cnt==2);

   DWORD dwRef = m_dwRef;
   m_dwRef = 10;

   if ( m_dwCookie != 0 )
   {
      HRESULT hr = AtlUnadvise(m_pBridge,IID_IGenericBridgeEvents,m_dwCookie);
      ATLASSERT( SUCCEEDED(hr) );
   }

   m_dwRef = dwRef;
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

STDMETHODIMP CPrecastGirder::Initialize(IGenericBridge* bridge,IStrandMover* strandMover,SpanIndexType spanIdx,GirderIndexType gdrIdx)
{
   CHECK_IN(bridge);
   CHECK_IN(strandMover);

   if ( spanIdx == INVALID_INDEX || gdrIdx == INVALID_INDEX )
      return E_INVALIDARG;

   m_pBridge = bridge;
   m_pStrandMover = strandMover;
   m_SpanIdx = spanIdx;
   m_GirderIdx = gdrIdx;

   CComPtr<IUnknown> punk;
   QueryInterface(IID_IUnknown,(void**)&punk);

   // sink event
   HRESULT hr;
   hr = AtlAdvise(bridge,punk,IID_IGenericBridgeEvents,&m_dwCookie);
   if ( FAILED(hr) )
      return hr; 

   m_HarpGridEnd[etStart]->put_StrandMover(strandMover);
   m_HarpGridEnd[etEnd]->put_StrandMover(strandMover);

   m_HarpGridHp[etStart]->put_StrandMover(strandMover);
   m_HarpGridHp[etEnd]->put_StrandMover(strandMover);

   return S_OK;
}

STDMETHODIMP CPrecastGirder::put_StrandMover(/*[in]*/IStrandMover* strandMover)
{
   CHECK_IN(strandMover);

   m_pStrandMover = strandMover;

   m_HarpGridEnd[etStart]->put_StrandMover(strandMover);
   m_HarpGridEnd[etEnd]->put_StrandMover(strandMover);

   m_HarpGridHp[etStart]->put_StrandMover(strandMover);
   m_HarpGridHp[etEnd]->put_StrandMover(strandMover);

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_StrandMover(/*[out,retval]*/IStrandMover** ppStrandMover)
{
   CHECK_RETOBJ(ppStrandMover);
   return m_pStrandMover.CopyTo(ppStrandMover);
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

STDMETHODIMP CPrecastGirder::put_UseDifferentHarpedGridsAtEnds(VARIANT_BOOL bUseDifferent)
{
   m_UseDifferentHarpedGirdAtEnds = bUseDifferent;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_UseDifferentHarpedGridsAtEnds(VARIANT_BOOL* bUseDifferent)
{
   *bUseDifferent = m_UseDifferentHarpedGirdAtEnds;
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

STDMETHODIMP CPrecastGirder::get_LeftEndSize(Float64* size)
{
   CHECK_RETVAL(size);

   DoUpdateLengths();

   *size = m_Lengths.dbLeftEndSize;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_RightEndSize(Float64* size)
{
   CHECK_RETVAL(size);

   DoUpdateLengths();

   *size = m_Lengths.dbRightEndSize;

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
   CHECK_RETOBJ(pntPier1);
   CHECK_RETOBJ(pntEnd1);
   CHECK_RETOBJ(pntBrg1);
   CHECK_RETOBJ(pntBrg2);
   CHECK_RETOBJ(pntEnd2);
   CHECK_RETOBJ(pntPier2);

   CComPtr<ICogoInfo> cogoInfo;
   m_pBridge->get_CogoInfo(&cogoInfo);
   CogoElementKey id1,id2;

   cogoInfo->get_PierGirderIntersectionPointID(m_SpanIdx,  m_GirderIdx,qcbAfter,&id1);
   cogoInfo->get_PierGirderIntersectionPointID(m_SpanIdx+1,m_GirderIdx,qcbBefore,&id2);

   CComPtr<ICogoModel> cogoModel;
   m_pBridge->get_CogoModel(&cogoModel);
   
   CComPtr<IPointCollection> points;
   cogoModel->get_Points(&points);

   // Get the points where the girder line intersect the CL pier
   points->get_Item(id1,pntPier1);
   points->get_Item(id2,pntPier2);

   // get the connection data
   CComPtr<IConnection> c1,c2;
   GetLeftConnection(&c1);
   GetRightConnection(&c2);

   Float64 endDist1, endDist2;
   get_LeftEndSize(&endDist1);
   get_RightEndSize(&endDist2);

   // Get the points where the girder line intersect the CL pier
   cogoInfo->get_BearingGirderIntersectionPointID(m_SpanIdx,  m_GirderIdx,qcbAfter,&id1);
   cogoInfo->get_BearingGirderIntersectionPointID(m_SpanIdx+1,m_GirderIdx,qcbBefore,&id2);
   points->get_Item(id1,pntBrg1);
   points->get_Item(id2,pntBrg2);

   // Compute end of girder points
   CComPtr<ICogoEngine> cogoEngine;
   cogoEngine.CoCreateInstance(CLSID_CogoEngine);

   CComQIPtr<ILocate2> locate(cogoEngine);
   locate->PointOnLine(*pntBrg1,*pntPier2,-endDist1,0.00,pntEnd1);
   locate->PointOnLine(*pntBrg2,*pntPier1,-endDist2,0.00,pntEnd2);

   return S_OK;
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

   //   m_HarpedMaxStrandFill.CoCreateInstance(CLSID_LongArray);

   //   CComPtr<ILongArray> hp_fill, end_fill;
   //   m_HarpGridEnd[etStart]->GetMaxStrandFill(&end_fill);
   //   m_HarpGridHp[etStart]->GetMaxStrandFill(&hp_fill);

   //   CollectionIndexType num_hp, num_end;
   //   end_fill->get_Count(&num_end);
   //   hp_fill->get_Count(&num_hp);

   //   if (num_hp != num_end)
   //   {
   //      // this should never happen - strand arrays must be the same length;
   //      ATLASSERT(0);
   //      return E_FAIL;
   //   }

   //   m_MaxHarpedStrands=0;
   //   m_HarpedMaxStrandFill->Reserve(num_hp);
   //   for (CollectionIndexType i=0; i<num_hp; i++)
   //{
   //      IDType hp, end; // should be index type, but must be ID type because of LongArray
   //      hp_fill->get_Item(i, &hp);
   //      end_fill->get_Item(i, &end);

   //      // use the max fill value from both grids
   //      hp = max(end, hp);
   //      m_HarpedMaxStrandFill->Add(hp);
   //      m_MaxHarpedStrands += StrandIndexType(hp);
   //   }

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

STDMETHODIMP CPrecastGirder::get_TempStrandPositions(Float64 distFromStart, IPoint2dCollection** points)
{
   CComPtr<IIndexArray> fill;
   m_TempGrid[etStart]->get_StrandFill(&fill);
   return get_TempStrandPositionsEx(distFromStart,fill,points);
}

STDMETHODIMP CPrecastGirder::get_TempStrandPositionsEx(Float64 distFromStart, IIndexArray* fill, IPoint2dCollection** points)
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


STDMETHODIMP CPrecastGirder::get_HarpedStrandRowsWithStrand(Float64 distFromStart,RowIndexType* nRows)
{
   CComPtr<IStrandGridFiller> grid;
   GetHarpedStrandGrid(distFromStart,&grid);
   return grid->get_RowsWithStrand(nRows);
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandsInRow(Float64 distFromStart,RowIndexType rowIdx,IIndexArray** gridIndexes)
{
   CComPtr<IStrandGridFiller> grid;
   GetHarpedStrandGrid(distFromStart,&grid);
   return grid->get_StrandsInRow(rowIdx, gridIndexes);
}

STDMETHODIMP CPrecastGirder::get_NumHarpedStrandsInRow(Float64 distFromStart,RowIndexType rowIdx,StrandIndexType* nStrands)
{
   CComPtr<IStrandGridFiller> grid;
   GetHarpedStrandGrid(distFromStart,&grid);
   return grid->get_NumStrandsInRow(rowIdx, nStrands);
}

STDMETHODIMP CPrecastGirder::get_RebarLayout(IRebarLayout** rebarLayout)
{
   CHECK_RETOBJ(rebarLayout);
   (*rebarLayout) = m_RebarLayout;
   (*rebarLayout)->AddRef();
   return S_OK;
}


///// PRIVATE /////
void CPrecastGirder::GetLeftConnection(IConnection** connection)
{
   CComPtr<ISpanCollection> spans;
   m_pBridge->get_Spans(&spans);

   CComPtr<ISpan> span;
   spans->get_Item(m_SpanIdx,&span);

   CComPtr<ISuperstructureMember> ssmbr;
   span->get_SuperstructureMember(m_GirderIdx,&ssmbr); 

   CComQIPtr<IItemData> item_data(ssmbr);
   CComPtr<IUnknown> punk;
   item_data->GetItemData(CComBSTR("Left Connection"),&punk);

   punk.QueryInterface(connection);
}

void CPrecastGirder::GetRightConnection(IConnection** connection)
{
   CComPtr<ISpanCollection> spans;
   m_pBridge->get_Spans(&spans);

   CComPtr<ISpan> span;
   spans->get_Item(m_SpanIdx,&span);

   CComPtr<ISuperstructureMember> ssmbr;
   span->get_SuperstructureMember(m_GirderIdx,&ssmbr); 

   CComQIPtr<IItemData> item_data(ssmbr);
   CComPtr<IUnknown> punk;
   item_data->GetItemData(CComBSTR("Right Connection"),&punk);

   punk.QueryInterface(connection);
}

void CPrecastGirder::GetEndDistance(EndType end,CogoElementKey brgPntID,CogoElementKey pierPntID,CogoElementKey girderLineID,IConnection* connection,IPier* pier,ICogoModel* cogoModel,Float64* endDist)
{
   Float64 end_dist;
   connection->get_EndDistance(&end_dist);

   MeasurementType measure_type;
   connection->get_EndDistanceMeasurementType(&measure_type);

   MeasurementLocation measure_loc;
   connection->get_EndDistanceMeasurementLocation(&measure_loc);

   if ( measure_type == mtAlongItem )
   {
      // Measured along girder
      if ( measure_loc == mlCenterlineBearing )
      {
         ;// do nothing - input is same as internal
      }
      else if ( measure_loc == mlPierLine )
      {
         // subtract end dist from bearing offset
         Float64 bearing_offset;
         CComQIPtr<IMeasure> measure(cogoModel);
         measure->Distance(brgPntID,pierPntID,&bearing_offset); // want offset measured along girder
         end_dist = bearing_offset - end_dist;
      }
      else
         ATLASSERT(0);
   }
   else if ( measure_type == mtNormal )
   {
      // Measured normal to pier
      // First create a line along the pier centerline
      CComPtr<IPointCollection> points;
      cogoModel->get_Points(&points);
      CComPtr<IPoint2d> pier_pnt;
      points->get_Item(pierPntID, &pier_pnt);

      CComPtr<IDirection> pier_dir;
      pier->get_Direction(&pier_dir);

      CComPtr<ICogoEngine> cogoEngine;
      cogoEngine.CoCreateInstance(CLSID_CogoEngine);
      CComQIPtr<ILocate2> locate(cogoEngine);

      Float64 dist = end==etEnd ? 10.0 : -10.0; // distance is abitrary, we just want a line that's left side faces inward to span
      CComPtr<IPoint2d> pier_pnt2;
      locate->ByDistDir(pier_pnt, dist, CComVariant(pier_dir), 0.0, &pier_pnt2);

      CComPtr<ILine2d> pier_line;
      pier_line.CoCreateInstance(CLSID_Line2d);
      pier_line->ThroughPoints(pier_pnt, pier_pnt2);

      // compute distance from bearing point to CL pier along CL pier
      CComPtr<IPoint2d> brg_pnt;
      points->get_Item(brgPntID, &brg_pnt);

      CComPtr<IGeomUtil2d> geom_util;
      geom_util.CoCreateInstance(CLSID_GeomUtil);

      Float64 bearing_to_pier_dist;
      geom_util->ShortestDistanceToPoint(pier_line, brg_pnt, &bearing_to_pier_dist);
      bearing_to_pier_dist *= -1.0; // left side is negative 

      // get girder line to intersect with
      CComPtr<ILineSegmentCollection> lineSegments;
      cogoModel->get_LineSegments(&lineSegments);
      CComPtr<ILineSegment2d> gdr_lineseg;
      lineSegments->get_Item(girderLineID,&gdr_lineseg);
      // make segment into a line so we know we'll intersect
      CComPtr<IPoint2d> gdr_pnt1, gdr_pnt2;
      gdr_lineseg->get_StartPoint(&gdr_pnt1);
      gdr_lineseg->get_EndPoint(&gdr_pnt2);

      CComPtr<ILine2d> gdr_line;
      gdr_line.CoCreateInstance(CLSID_Line2d);
      gdr_line->ThroughPoints(gdr_pnt1, gdr_pnt2);

      // Now we have our construction lines. Basic idea is to offset the pier line and find
      // its intersection with the girder line. That will give us the end of the girder
      Float64 offset_dist=0.0;
      Float64 sign = 1;
      if ( measure_loc == mlCenterlineBearing )
      {
         // measured from centerline bearing
         offset_dist = bearing_to_pier_dist - end_dist;
      }
      else if ( measure_loc == mlPierLine )
      {
         offset_dist = end_dist;

         if (end_dist > bearing_to_pier_dist)
         {
            // end of girder is before bearing, negative end dist
            sign = -1;
         }
      }
      else
      {
         ATLASSERT(0);
      }

      pier_line->Offset(offset_dist);

      CComPtr<IPoint2d> end_of_girder;
      geom_util->LineLineIntersect(pier_line,gdr_line,&end_of_girder);

      // finally, our end distance
      geom_util->Distance(brg_pnt, end_of_girder, &end_dist);
      end_dist *= sign;
   }
   else
   {
      ATLASSERT(0);
   }

   *endDist   = end_dist;
}

void CPrecastGirder::GetHarpPointLocations(Float64& hp1,Float64& hp2)
{
   hp1 = GetHarpPointLocation(m_HP1,false);
   hp2 = GetHarpPointLocation(m_HP2,true);

   ATLASSERT( hp1 <= hp2 );
}

Float64 CPrecastGirder::GetHarpPointLocation(Float64 hp,bool bRight)
{
   Float64 left_end_size;
   Float64 right_end_size;

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
      get_LeftEndSize(&left_end_size);
      get_RightEndSize(&right_end_size);
      result = (bRight ? gdr_length - right_end_size - hp : left_end_size + hp);
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
         IndexType first_row;
         endFill->get_Item(0,&first_row);
         ASSERT(first_row == 1); // only one strand at the bottom... but we need it to be 2 for odd fill at top
#endif

         StrandIndexType running_cnt = (m_UseDifferentHarpedGirdAtEnds == VARIANT_TRUE ? 2 : 1);
         m_OddHpFill->Add(running_cnt); 

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
                  if ( m_UseDifferentHarpedGirdAtEnds == VARIANT_TRUE )
                     m_OddHpFill->Add(fill_val-1);
                  else
                     m_OddHpFill->Add(fill_val);

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

STDMETHODIMP CPrecastGirder::OnBridgeChanged(/*[in]*/ IGenericBridge* bridge)
{
   m_UpdateLengths=true;
   return S_OK;
}

void CPrecastGirder::DoUpdateLengths()
{
   if (m_UpdateLengths)
   {
      CComPtr<ICogoInfo> cogoInfo;
      m_pBridge->get_CogoInfo(&cogoInfo);

      PierIndexType startPierIdx = PierIndexType(m_SpanIdx);
      PierIndexType endPierIdx = PierIndexType(startPierIdx+1);

      // get ID of intersection CL Pier and CL Girder
      CogoElementKey startPierPntID, endPierPntID;
      cogoInfo->get_PierGirderIntersectionPointID(startPierIdx, m_GirderIdx, qcbAfter,  &startPierPntID);
      cogoInfo->get_PierGirderIntersectionPointID(endPierIdx,   m_GirderIdx, qcbBefore, &endPierPntID);

      // get ID of intersection CL bearing and CL girder
      CogoElementKey startBrgPntID, endBrgPntID;
      cogoInfo->get_BearingGirderIntersectionPointID(startPierIdx, m_GirderIdx, qcbAfter,  &startBrgPntID);
      cogoInfo->get_BearingGirderIntersectionPointID(endPierIdx,   m_GirderIdx, qcbBefore, &endBrgPntID);

      // get girder line ID
      CogoElementKey girderLineID;
      cogoInfo->get_GirderLineID(startPierIdx, m_GirderIdx, &girderLineID);

      // compute bearing offsets
      CComPtr<ICogoModel> cogoModel;
      m_pBridge->get_CogoModel(&cogoModel);

      CComQIPtr<IMeasure> measure(cogoModel);
      measure->Distance(startPierPntID,startBrgPntID,&m_Lengths.dbLeftBearingOffset);
      measure->Distance(endPierPntID,  endBrgPntID,  &m_Lengths.dbRightBearingOffset);
      m_Lengths.dbLeftBearingOffset  = IsZero(m_Lengths.dbLeftBearingOffset)  ? 0 : m_Lengths.dbLeftBearingOffset;
      m_Lengths.dbRightBearingOffset = IsZero(m_Lengths.dbRightBearingOffset) ? 0 : m_Lengths.dbRightBearingOffset;

      // compute span length
      measure->Distance(startBrgPntID,endBrgPntID,&m_Lengths.dbSpanLength);

      // left and right end size
      CComPtr<IConnection> connectionl;
      GetLeftConnection(&connectionl);

      CComPtr<IPierCollection> piers;
      m_pBridge->get_Piers(&piers);

      CComPtr<IPier> pierl;
      piers->get_Item(startPierIdx,&pierl);

      Float64 end_dist;
      GetEndDistance(etStart,startBrgPntID,startPierPntID,girderLineID,connectionl,pierl,cogoModel,&end_dist);
      end_dist = IsZero(end_dist) ? 0 : end_dist;
      m_Lengths.dbLeftEndSize       = end_dist;

      CComPtr<IConnection> connectionr;
      GetRightConnection(&connectionr);

      CComPtr<IPier> pierr;
      piers->get_Item(endPierIdx,&pierr);

      GetEndDistance(etEnd,endBrgPntID,endPierPntID,girderLineID,connectionr,pierr,cogoModel,&end_dist);
      end_dist = IsZero(end_dist) ? 0 : end_dist;
      m_Lengths.dbRightEndSize        = end_dist;

      m_Lengths.dbGirderLength = m_Lengths.dbSpanLength + m_Lengths.dbLeftEndSize + m_Lengths.dbRightEndSize;

      m_UpdateLengths=false;
   }
}


void CPrecastGirder::GetHarpedStrandGrid(Float64 distFromStart,IStrandGridFiller** ppGrid)
{
   Float64 hp1, hp2;
   GetHarpPointLocations(hp1,hp2);

   if ( distFromStart < hp1 )
   {
      m_HarpGridEnd[etStart].CopyTo(ppGrid);
   }
   else if ( hp2 < distFromStart )
   {
      m_HarpGridEnd[etEnd].CopyTo(ppGrid);
   }
   else 
   {
      m_HarpGridHp[etStart].CopyTo(ppGrid);
   }
}
