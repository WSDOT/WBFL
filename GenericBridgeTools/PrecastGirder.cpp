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

// PrecastGirder.cpp : Implementation of CPrecastGirder
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "PrecastGirder.h"
#include <limits>
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

   CComPtr<IGeomUtil> geom_util;
   hr = geom_util.CoCreateInstance(CLSID_GeomUtil);
   if ( FAILED(hr) )
      return hr;

   m_UpdateLengths = true;

   geom_util->get_Point2dFactory(&m_Point2dFactory);

   m_StrandFillTool.CoCreateInstance(CLSID_StrandFillTool);

   m_StraightStrandProfileType = FollowGirder;
   m_TemporaryStrandProfileType = Linear;

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
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPrecastGirder::Initialize(ISuperstructureMemberSegment* segment)
{
   CHECK_IN(segment);

   m_pSegment = segment;


   CComQIPtr<IThickenedFlangeSegment> thickenedSegment(m_pSegment);
   if (thickenedSegment)
   {
      CComPtr<IShape> shape;
      thickenedSegment->get_GirderShape(0.0, &shape);
      CComQIPtr<IAsymmetricSection> asymmetric(shape);
      if (asymmetric)
      {
         Float64 wLeft, wRight;
         asymmetric->GetTopWidth(&wLeft, &wRight);
         Float64 Xadj = 0.5*(wLeft - wRight);

         for (int i = 0; i < 2; i++)
         {
            m_StraightGrid[i]->SetStrandAdjustment(Xadj, 0.0);
            m_HarpGridEnd[i]->SetStrandAdjustment(Xadj, 0.0);
            m_HarpGridHp[i]->SetStrandAdjustment(Xadj, 0.0);
            m_TempGrid[i]->SetStrandAdjustment(Xadj, 0.0);
         }
      }
   }


   return S_OK;
}

STDMETHODIMP CPrecastGirder::SetStrandMovers(IStrandMover* pStartStrandMover,IStrandMover* pHp1StrandMover,IStrandMover* pHp2StrandMover,IStrandMover* pEndStrandMover)
{
   m_HarpGridEnd[etStart]->putref_StrandMover(sgtEnd,etStart,pStartStrandMover);
   m_HarpGridEnd[etEnd]->putref_StrandMover(sgtEnd,etEnd,pEndStrandMover);

   m_HarpGridHp[etStart]->putref_StrandMover(sgtHarpPoint,etStart,pHp1StrandMover);
   m_HarpGridHp[etEnd]->putref_StrandMover(sgtHarpPoint,etEnd,pHp2StrandMover);
   
   return S_OK;
}

STDMETHODIMP CPrecastGirder::putref_StrandMover(/*[in]*/StrandGridType sgType,/*[in]*/EndType endType,/*[in]*/IStrandMover* strandMover)
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

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_StrandMover(/*[in]*/StrandGridType sgType,/*[in]*/EndType endType,/*[out,retval]*/IStrandMover** ppStrandMover)
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

STDMETHODIMP CPrecastGirder::get_HarpedStrandAdjustmentEnd(EndType endType,Float64* offset)
{
   Float64 dx;
   return m_HarpGridEnd[endType]->GetStrandAdjustment(&dx,offset);
}

STDMETHODIMP CPrecastGirder::put_HarpedStrandAdjustmentEnd(EndType endType,Float64 offset)
{
   // cannot adjust if increment is less than zero
   Float64 increment, dummy;
   CComPtr<IStrandMover> strandMover;
   get_StrandMover(sgtEnd,endType,&strandMover);
   strandMover->get_StrandIncrements(&increment, &dummy);

   Float64 dx, dy;
   m_HarpGridEnd[endType]->GetStrandAdjustment(&dx,&dy);

   if (increment<0.0 && !IsZero(offset))
   {
      ATLASSERT(false); // cannot adjust if increment<0.0
      m_HarpGridEnd[endType]->SetStrandAdjustment(dx,0.0);
      return E_INVALIDARG;
   }
   else
   {
      m_HarpGridEnd[endType]->SetStrandAdjustment(dx,offset);
      return S_OK;
   }
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandAdjustmentHP(EndType endType,Float64* offset)
{
   Float64 dx;
   return m_HarpGridHp[endType]->GetStrandAdjustment(&dx,offset);
}

STDMETHODIMP CPrecastGirder::put_HarpedStrandAdjustmentHP(EndType endType,Float64 offset)
{
   // cannot adjust if increment is less than zero
   Float64 increment, dummy;
   CComPtr<IStrandMover> strandMover;
   get_StrandMover(sgtHarpPoint,endType,&strandMover);
   strandMover->get_StrandIncrements(&increment, &dummy);

   Float64 dx, dy;
   m_HarpGridHp[endType]->GetStrandAdjustment(&dx,&dy);

   if (increment<0.0 && !IsZero(offset))
   {
      ATLASSERT(false); // cannot adjust if increment<0.0
      m_HarpGridHp[endType]->SetStrandAdjustment(dx,0.0);
      return E_INVALIDARG;
   }
   else
   {
      m_HarpGridHp[endType]->SetStrandAdjustment(dx,offset);
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

STDMETHODIMP CPrecastGirder::SetEndHarpingPoints(Float64 hp1,Float64 hp2)
{
   // must be positive values... HarpPointMeasure will indicate if this is fractional
   if ( hp1 < 0 || hp2 < 0 )
   {
      ATLASSERT(false);
      return E_INVALIDARG;
   }

   m_HPStart = hp1;
   m_HPEnd = hp2;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetEndHarpingPoints(Float64* hp1,Float64* hp2)
{
   CHECK_RETVAL(hp1);
   CHECK_RETVAL(hp2);

   *hp1 = m_HPStart;
   *hp2 = m_HPEnd;

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

STDMETHODIMP CPrecastGirder::put_EndHarpingPointMeasure(HarpPointMeasure measure)
{
   m_EndHPMeasure = measure;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_EndHarpingPointMeasure(HarpPointMeasure* measure)
{
   CHECK_RETVAL(measure);
   *measure = m_EndHPMeasure;
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

STDMETHODIMP CPrecastGirder::put_EndHarpingPointReference(HarpPointReference hpRef)
{
   m_EndHPReference = hpRef;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_EndHarpingPointReference(HarpPointReference* hpRef)
{
   CHECK_RETVAL(hpRef);
   *hpRef = m_EndHPReference;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetHarpingPointLocations(Float64* hp1,Float64* hp2)
{
   CHECK_RETVAL(hp1);
   CHECK_RETVAL(hp2);

   GetHarpPointLocations(*hp1,*hp2);
   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetEndHarpingPointLocations(Float64* hp1,Float64* hp2)
{
   CHECK_RETVAL(hp1);
   CHECK_RETVAL(hp2);

   GetEndHarpPointLocations(*hp1,*hp2);
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
      if (FAILED(hr))
      {
         return hr;
      }

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

STDMETHODIMP CPrecastGirder::putref_StraightStrandFill(/*[inl]*/IIndexArray* fill)
{
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

STDMETHODIMP CPrecastGirder::get_HarpedStrandFill(IIndexArray** fill)
{
   return m_HarpGridEnd[etStart]->get_StrandFill(fill);
}

STDMETHODIMP CPrecastGirder::putref_HarpedStrandFill(/*[inl]*/IIndexArray* fill)
{
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

STDMETHODIMP CPrecastGirder::get_TemporaryStrandFill(IIndexArray** fill)
{
   return m_TempGrid[etStart]->get_StrandFill(fill);
}

STDMETHODIMP CPrecastGirder::putref_TemporaryStrandFill(/*[inl]*/IIndexArray* fill)
{
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

STDMETHODIMP CPrecastGirder::put_StraightStrandProfileType(StrandProfileType profileType)
{
   m_StraightStrandProfileType = profileType;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_StraightStrandProfileType(StrandProfileType* pProfileType)
{
   CHECK_RETVAL(pProfileType);
   *pProfileType = m_StraightStrandProfileType;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::put_TemporaryStrandProfileType(StrandProfileType profileType)
{
   m_TemporaryStrandProfileType = profileType;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_TemporaryStrandProfileType(StrandProfileType* pProfileType)
{
   CHECK_RETVAL(pProfileType);
   *pProfileType = m_TemporaryStrandProfileType;
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_StraightStrandCG(/*[in]*/Float64 distFromStart, /*[out,retval]*/IPoint2d** pntCG)
{
   CHECK_RETVAL(pntCG);
   CComPtr<IPoint2dCollection> points;
   get_StraightStrandPositions(distFromStart, &points);
   RemoveStraightStrandDebondedStrandPositions(distFromStart, points);
   GetCGFromPoints(points, pntCG);
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_StraightStrandCGEx(/*[in]*/Float64 distFromStart, /*[in]*/IIndexArray* fill, /*[out,retval]*/IPoint2d** pntCG)
{
   CHECK_RETVAL(pntCG);
   CComPtr<IPoint2dCollection> points;
   get_StraightStrandPositionsEx(distFromStart, fill, &points);
   RemoveStraightStrandDebondedStrandPositions(distFromStart, points);
   GetCGFromPoints(points, pntCG);
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandCG(/*[in]*/Float64 distFromStart, /*[out,retval]*/IPoint2d** pntCG)
{
   CHECK_RETVAL(pntCG);
   CComPtr<IPoint2dCollection> points;
   get_HarpedStrandPositions(distFromStart, &points);
   GetCGFromPoints(points, pntCG);
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandCGEx(/*[in]*/Float64 distFromStart, /*[in]*/IIndexArray* fill, /*[out,retval]*/IPoint2d** pntCG)
{
   CHECK_RETVAL(pntCG);
   CComPtr<IPoint2dCollection> points;
   get_HarpedStrandPositionsEx(distFromStart, fill, &points);
   GetCGFromPoints(points, pntCG);
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_TemporaryStrandCG(/*[in]*/Float64 distFromStart, /*[out,retval]*/IPoint2d** pntCG)
{
   CHECK_RETVAL(pntCG);
   CComPtr<IPoint2dCollection> points;
   get_TemporaryStrandPositions(distFromStart, &points);
   GetCGFromPoints(points, pntCG);
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_TemporaryStrandCGEx(/*[in]*/Float64 distFromStart, /*[in]*/IIndexArray* fill, /*[out,retval]*/IPoint2d** pntCG)
{
   CHECK_RETVAL(pntCG);
   CComPtr<IPoint2dCollection> points;
   get_TemporaryStrandPositionsEx(distFromStart, fill, &points);
   GetCGFromPoints(points, pntCG);
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

   Float64 precamber(0.0);
   if (m_StraightStrandProfileType == Linear)
   {
      m_pSegment->ComputePrecamber(distFromStart, &precamber);
   }

   HRESULT hr = GetStrandPositions(distFromStart, 0.0, gdrLength, gdrLength, -precamber, -precamber, fill, m_StraightGrid[etStart], fill, m_StraightGrid[etEnd], points);

   if (m_StraightStrandProfileType == FollowGirder)
   {
      m_pSegment->ComputePrecamber(distFromStart, &precamber);
      (*points)->Offset(0, precamber);
   }

   return hr;
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandPositions(Float64 distFromStart, IPoint2dCollection** points)
{
   CComPtr<IIndexArray> fill;
   m_HarpGridEnd[etStart]->get_StrandFill(&fill);
   return get_HarpedStrandPositionsEx(distFromStart, fill,points);
}

STDMETHODIMP CPrecastGirder::get_HarpedStrandPositionsEx(Float64 distFromStart, IIndexArray* fill, IPoint2dCollection** points)
{
   CHECK_RETOBJ(points);

   // may need to interpolate
   Float64 gdrLength, leftEndHP, leftHP, rightHP, rightEndHP;
   get_GirderLength(&gdrLength);
   GetHarpingPointLocations(&leftHP, &rightHP);
   GetEndHarpingPointLocations(&leftEndHP,&rightEndHP);

   // harped strands always have a Linear profile so there elevation need to be adjusted for precamber effects
   if ( ::IsLE(distFromStart,leftEndHP) )
   {
      // in start portion of harped strands governed by the start grid
      m_HarpGridEnd[etStart]->GetStrandPositionsEx(fill,points);
      Float64 precamber;
      m_pSegment->ComputePrecamber(distFromStart, &precamber);
      (*points)->Offset(0, -precamber);
      return S_OK;
   }
   else if ( ::IsGE(rightEndHP,distFromStart) )
   {
      // in end portion of the harped strands governed by the end grid
      m_HarpGridEnd[etEnd]->GetStrandPositionsEx(fill,points);
      Float64 precamber;
      m_pSegment->ComputePrecamber(distFromStart, &precamber);
      (*points)->Offset(0, -precamber);
      return S_OK;
   }
   else if ( leftHP <= distFromStart && distFromStart <= rightHP )
   {
      // between harp points
      CComPtr<IIndexArray> hp_fill;
      HRESULT hr = ComputeHpFill(fill, &hp_fill);
      ATLASSERT( SUCCEEDED(hr) );

      Float64 leftPrecamber, rightPrecamber;
      m_pSegment->ComputePrecamber(leftHP, &leftPrecamber);
      m_pSegment->ComputePrecamber(rightHP, &rightPrecamber);

      // assume harped strand are straight between harping points (they don't follow the bottom of the girder if precambered)
      hr = GetStrandPositions(distFromStart, leftHP, rightHP-leftHP, gdrLength, leftPrecamber, rightPrecamber, hp_fill, m_HarpGridHp[etStart], hp_fill, m_HarpGridHp[etEnd], points);
      ATLASSERT( SUCCEEDED(hr) );

      return hr;
   }
   else if ( leftEndHP < distFromStart && distFromStart < leftHP )
   {
      // on the sloped part of the harped strands at the left end of the girder

      // compute harped fill at hp
      CComPtr<IIndexArray> hp_fill;
      HRESULT hr = ComputeHpFill(fill, &hp_fill);
      ATLASSERT( SUCCEEDED(hr) );

      Float64 leftPrecamber, rightPrecamber;
      m_pSegment->ComputePrecamber(leftEndHP, &leftPrecamber);
      m_pSegment->ComputePrecamber(leftHP, &rightPrecamber);

      hr = GetStrandPositions(distFromStart, leftEndHP, leftHP-leftEndHP, gdrLength, leftPrecamber, rightPrecamber, fill, m_HarpGridEnd[etStart], hp_fill, m_HarpGridHp[etStart], points);

      ATLASSERT( SUCCEEDED(hr) );
      return hr;
   }
   else
   {
      ATLASSERT( rightHP < distFromStart && distFromStart < rightEndHP );
      // on the sloped part of the harped strands at right end of girder
      // compute harped fill at hp
      CComPtr<IIndexArray> hp_fill;
      HRESULT hr = ComputeHpFill(fill, &hp_fill);
      ATLASSERT( SUCCEEDED(hr) );

      Float64 leftPrecamber, rightPrecamber;
      m_pSegment->ComputePrecamber(rightHP, &leftPrecamber);
      m_pSegment->ComputePrecamber(rightEndHP, &rightPrecamber);

      hr = GetStrandPositions(distFromStart, rightHP, rightEndHP - rightHP, gdrLength, leftPrecamber, rightPrecamber, hp_fill, m_HarpGridHp[etEnd], fill, m_HarpGridEnd[etEnd], points);

      ATLASSERT( SUCCEEDED(hr) );
      return hr;
   }
}

STDMETHODIMP CPrecastGirder::get_TemporaryStrandPositions(Float64 distFromStart, IPoint2dCollection** points)
{
   CComPtr<IIndexArray> fill;
   m_TempGrid[etStart]->get_StrandFill(&fill);
   return get_TemporaryStrandPositionsEx(distFromStart, fill,points);
}

STDMETHODIMP CPrecastGirder::get_TemporaryStrandPositionsEx(Float64 distFromStart, IIndexArray* fill, IPoint2dCollection** points)
{
   Float64 gdrLength;
   get_GirderLength(&gdrLength);

   Float64 precamber(0.0);
   if (m_TemporaryStrandProfileType == Linear)
   {
      m_pSegment->ComputePrecamber(distFromStart, &precamber);
   }

   HRESULT hr = GetStrandPositions(distFromStart, 0.0, gdrLength, gdrLength, -precamber, -precamber, fill, m_TempGrid[etStart], fill, m_TempGrid[etEnd], points);

   if (m_TemporaryStrandProfileType == FollowGirder)
   {
      m_pSegment->ComputePrecamber(distFromStart, &precamber);
      (*points)->Offset(0, precamber);
   }

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
      ATLASSERT(false);
      return hr;
   }

   return m_HarpGridHp[endType]->get_StrandBoundingBoxEx(hp_fill, box);
}

STDMETHODIMP CPrecastGirder::get_TopElevation(/*[out,retval]*/Float64* top)
{
   CComPtr<IStrandMover> strandMover;
   get_StrandMover(sgtEnd,etEnd,&strandMover);
   
   return strandMover->get_TopElevation(top);
}


STDMETHODIMP CPrecastGirder::GetHarpedEndAdjustmentBounds(/*[in]*/EndType endType,/*[out]*/Float64* minDownwardAdjustment, /*[out]*/Float64* maxUpwardAdjustment)

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

STDMETHODIMP CPrecastGirder::GetHarpedEndAdjustmentBoundsEx(/*[in]*/EndType endType,/*[in]*/ IIndexArray* fill, /*[out]*/Float64* minDownwardAdjustment, /*[out]*/Float64* maxUpwardAdjustment)

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

STDMETHODIMP CPrecastGirder::GetHarpedHpAdjustmentBounds(/*[in]*/ EndType endType,/*[out]*/Float64* minDownwardAdjustment, /*[out]*/Float64* maxUpwardAdjustment)
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

STDMETHODIMP CPrecastGirder::GetHarpedHpAdjustmentBoundsEx(/*[in]*/EndType endType,/*[in]*/ IIndexArray* fill, /*[out]*/Float64* minDownwardAdjustment, /*[out]*/Float64* maxUpwardAdjustment)

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

STDMETHODIMP CPrecastGirder::GetHarpedEndFilledGridBoundsEx(/*[in]*/EndType endType,/*[in]*/IIndexArray* fill, /*[out]*/Float64* bottomElev, /*[out]*/Float64* topElev)
{
   return m_HarpGridEnd[endType]->get_FilledGridBoundsEx( fill, bottomElev, topElev);
}

STDMETHODIMP CPrecastGirder::GetHarpedHpFilledGridBoundsEx(/*[in]*/EndType endType,/*[in]*/IIndexArray* fill, /*[out]*/Float64* bottomElev, /*[out]*/Float64* topElev)
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

STDMETHODIMP CPrecastGirder::get_HarpedEndAdjustmentIncrement(/*[out,retval]*/Float64* increment)
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

STDMETHODIMP CPrecastGirder::get_HarpedHpAdjustmentIncrement(/*[out,retval]*/Float64* increment)
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

STDMETHODIMP CPrecastGirder::HarpedEndStrandBoundaryCheck(EndType endType,Float64* adjustment)
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

STDMETHODIMP CPrecastGirder::HarpedHpStrandBoundaryCheck(EndType endType,Float64* adjustment)
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

STDMETHODIMP CPrecastGirder::ComputeMaxHarpedStrandSlope(Float64 distFromStart,Float64* slope)
{
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
   get_GirderLength(&gdrLength);
   ATLASSERT(0.0 <= distFromStart  && distFromStart <= gdrLength);
#endif

   Float64 leftEndHP, leftHP, rightHP, rightEndHP;
   GetHarpingPointLocations(&leftHP, &rightHP);
   GetEndHarpingPointLocations(&leftEndHP, &rightEndHP);

   if ( distFromStart < leftEndHP || (leftHP < distFromStart && distFromStart < rightHP) || rightEndHP < distFromStart )
   {
      // point under consideration is outside of sloped region or between harp points
      // strands are assumed to be horizonal
      *slope = DBL_MAX;
      return S_OK;
   }

   Float64 run; // as in rise over run
   CComPtr<IPoint2dCollection> start, end;
   if ( ::IsLE(distFromStart,leftHP) )
   {
      ATLASSERT(leftEndHP <= distFromStart);
      get_HarpedStrandPositions(leftEndHP,&start);
      get_HarpedStrandPositions(leftHP, &end);
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
      ATLASSERT(distFromStart <= rightEndHP);
      get_HarpedStrandPositions(rightHP,  &start);
      get_HarpedStrandPositions(rightEndHP, &end);
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
   CollectionIndexType nStrandStart,nStrandEnd;
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

STDMETHODIMP CPrecastGirder::ComputeMaxHarpedStrandSlopeEx(Float64 distFromStart, IIndexArray* fill,  Float64 startOffset, Float64 hp1Offset, Float64 hp2Offset, Float64 endOffset,Float64* slope)
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
   get_GirderLength(&gdrLength);
   ATLASSERT(0.0 <= distFromStart  && distFromStart <= gdrLength);
#endif

   Float64 leftEndHP, leftHP, rightHP, rightEndHP;
   GetHarpingPointLocations(&leftHP, &rightHP);
   GetEndHarpingPointLocations(&leftEndHP, &rightEndHP);

   if (distFromStart < leftEndHP || (leftHP < distFromStart && distFromStart < rightHP) || rightEndHP < distFromStart)
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
   if ( ::IsLE(distFromStart,leftHP) )
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
   CollectionIndexType nStrandStart,nStrandEnd;
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


STDMETHODIMP CPrecastGirder::ComputeAvgHarpedStrandSlopeEx(Float64 distFromStart,IIndexArray* fill,Float64 startOffset, Float64 hp1Offset, Float64 hp2Offset, Float64 endOffset,Float64* slope)
{
   CHECK_RETVAL(slope);

#if defined _DEBUG
   Float64 gdrLength;
   get_GirderLength(&gdrLength);
   ATLASSERT(0.0 <= distFromStart  && distFromStart <= gdrLength);
#endif

   Float64 leftEndHP, leftHP, rightHP, rightEndHP;
   GetHarpingPointLocations(&leftHP, &rightHP);
   GetEndHarpingPointLocations(&leftEndHP, &rightEndHP);

   if ( InRange(leftEndHP,distFromStart,leftHP) )
   {
      Float64 cg_x, cg_leftEndHP, cg_leftHP;
      m_HarpGridEnd[etStart]->get_CGEx(fill, &cg_x, &cg_leftEndHP);
      m_HarpGridHp[etStart]->get_CGEx(fill, &cg_x, &cg_leftHP);

      // cg values in grid are adjusted for internal offset - remove them
      Float64 dx, end_offset, hp_offset;
      m_HarpGridEnd[etStart]->GetStrandAdjustment(&dx,&end_offset);
      m_HarpGridHp[etStart]->GetStrandAdjustment(&dx,&hp_offset);

      cg_leftEndHP -= end_offset;
      cg_leftHP -= hp_offset;

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
   else if ( InRange(rightHP,distFromStart,rightEndHP) )
   {
      Float64 cg_x, cg_rightHP, cg_rightEndHP;
      m_HarpGridHp[etEnd]->get_CGEx(fill, &cg_x, &cg_rightHP);
      m_HarpGridEnd[etEnd]->get_CGEx(fill, &cg_x, &cg_rightEndHP);

      // cg values are adjusted for internal offset - remove them
      Float64 dx, end_offset, hp_offset;
      m_HarpGridHp[etEnd]->GetStrandAdjustment(&dx,&hp_offset);
      m_HarpGridEnd[etEnd]->GetStrandAdjustment(&dx, &end_offset);

      cg_rightHP  -= hp_offset;
      cg_rightEndHP -= end_offset;

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
      ATLASSERT( distFromStart < leftEndHP || (leftHP < distFromStart && distFromStart < rightHP) || rightEndHP < distFromStart);
      *slope = DBL_MAX;
   }

   return S_OK;
}

STDMETHODIMP CPrecastGirder::ComputeAvgHarpedStrandSlope(Float64 distFromStart, Float64* slope)
{
   CHECK_RETVAL(slope);

#if defined _DEBUG
   Float64 gdrLength;
   get_GirderLength(&gdrLength);
   ATLASSERT(0.0 <= distFromStart  && distFromStart <= gdrLength);
#endif

   Float64 leftEndHP, leftHP, rightHP, rightEndHP;
   GetHarpingPointLocations(&leftHP, &rightHP);
   GetEndHarpingPointLocations(&leftEndHP, &rightEndHP);

   if ( InRange(leftEndHP,distFromStart,leftHP) )
   {
      Float64 cg_x, cg_leftEndHP, cg_leftHP;
      m_HarpGridEnd[etStart]->get_CG(&cg_x, &cg_leftEndHP);
      m_HarpGridHp[etStart]->get_CG(&cg_x, &cg_leftHP);

      // make cg measured consistently from bottom
      Float64 HgLeftEndHP = GetSectionHeight(leftEndHP);
      Float64 HgLeftHP = GetSectionHeight(leftHP);

      Float64 leftEndHPprecamber, leftHPprecamber;
      m_pSegment->ComputePrecamber(leftEndHP, &leftEndHPprecamber);
      m_pSegment->ComputePrecamber(leftHP, &leftHPprecamber);

      cg_leftEndHP += HgLeftEndHP + leftEndHPprecamber;
      cg_leftHP += HgLeftHP + leftHPprecamber;

      if ( !::IsEqual(cg_leftEndHP,cg_leftHP) )
      {
         *slope = (leftHP - leftEndHP)/(cg_leftHP - cg_leftEndHP);
      }
      else
      {
         *slope = DBL_MAX;
      }
   }
   else if ( InRange(rightHP,distFromStart,rightEndHP) )
   {
      Float64 cg_x, cg_rightHP, cg_rightEndHP;
      m_HarpGridHp[etEnd]->get_CG(&cg_x, &cg_rightHP);
      m_HarpGridEnd[etEnd]->get_CG(&cg_x, &cg_rightEndHP);

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
      ATLASSERT(distFromStart < leftEndHP || (leftHP < distFromStart && distFromStart < rightHP) || rightEndHP < distFromStart);
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

   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetTemporaryStrandCountEx(/*[in]*/ IIndexArray* fill, /*[out,retval]*/ StrandIndexType* nStrands)
{
   return m_TempGrid[etStart]->GetStrandCountEx(fill, nStrands);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandDebondCount(/*[in]*/ WDebondLocationType loc, /*[out,retval]*/ StrandIndexType* count)
{
   return m_StraightGrid[etStart]->GetStrandDebondCount(loc, count);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandProfile(/*[in]*/StrandIndexType strandIdx,/*[out, retval]*/IPoint2dCollection** ppProfilePoints)
{
   CHECK_RETOBJ(ppProfilePoints);

   CComPtr<IPoint2dCollection> profilePoints;
   profilePoints.CoCreateInstance(CLSID_Point2dCollection);

   Float64 Ls;
   m_pSegment->get_Length(&Ls);

   std::vector<Float64> vPoints;

   Float64 X, Y, l1, l2;
   GetStraightStrandDebondLengthByPositionIndex(etStart,strandIdx,&X,&Y,&l1,&l2);
   Float64 xMin = l1;
   Float64 xMax = Ls - l2;

   vPoints.push_back(xMin);
   vPoints.push_back(xMax);

   Float64 precamber;
   m_pSegment->get_Precamber(&precamber);
   if (m_StraightStrandProfileType == FollowGirder && !IsZero(precamber))
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

   std::sort(vPoints.begin(), vPoints.end());
   vPoints.erase(std::unique(vPoints.begin(), vPoints.end()), vPoints.end()); 

   for (const auto& x : vPoints)
   {
      CComPtr<IPoint2dCollection> strandPoints;
      get_StraightStrandPositions(x, &strandPoints);

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

STDMETHODIMP CPrecastGirder::GetHarpedStrandProfile(/*[in]*/StrandIndexType strandIdx,/*[out, retval]*/IPoint2dCollection** ppProfilePoints)
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
      get_HarpedStrandPositions(x, &strandPoints);

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

STDMETHODIMP CPrecastGirder::GetTemporaryStrandProfile(/*[in]*/StrandIndexType strandIdx,/*[out, retval]*/IPoint2dCollection** ppProfilePoints)
{
   CHECK_RETOBJ(ppProfilePoints);

   CComPtr<IPoint2dCollection> profilePoints;
   profilePoints.CoCreateInstance(CLSID_Point2dCollection);

   Float64 Ls;
   m_pSegment->get_Length(&Ls);

   std::vector<Float64> vPoints{ 0.0, Ls };

   Float64 precamber;
   m_pSegment->get_Precamber(&precamber);

   if (m_TemporaryStrandProfileType == FollowGirder && !IsZero(precamber))
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
      get_TemporaryStrandPositions(x, &strandPoints);

      CComPtr<IPoint2d> strandPoint;
      strandPoints->get_Item(strandIdx, &strandPoint);

      Float64 y;
      strandPoint->get_Y(&y);

      if (m_TemporaryStrandProfileType == FollowGirder)
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

STDMETHODIMP CPrecastGirder::GetStrandCGProfile(VARIANT_BOOL bIncludeTempStrands, IPoint2dCollection** ppProfilePoints)
{
   CHECK_RETOBJ(ppProfilePoints);
   CComPtr<IPoint2dCollection> profilePoints;
   profilePoints.CoCreateInstance(CLSID_Point2dCollection);

   StrandIndexType Ns, Nh, Nt(0);
   GetStraightStrandCount(&Ns);
   GetHarpedStrandCount(&Nh);
   if (bIncludeTempStrands == VARIANT_TRUE)
   {
      GetTemporaryStrandCount(&Nt);
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
         for (StrandIndexType strandIdx = 0; strandIdx < nStrands; strandIdx++)
         {
            Float64 X, Y, l1, l2;
            GetStraightStrandDebondLengthByPositionIndex(etStart, strandIdx, &X, &Y, &l1, &l2);
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
            get_StraightStrandCG(x, &pntCGStraight);
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
            get_HarpedStrandCG(x, &pntCGHarped);
            pntCGHarped->Location(&cgXharped, &cgYharped);

            cgYharped += precamber;

            Float64 Yadj = GetGirderDepthAdjustment(x, 0, Ls);
            cgYharped -= Yadj;
         }

         Float64 cgXtemp(0), cgYtemp(0);
         if (bIncludeTempStrands == VARIANT_TRUE && 0 < Nt)
         {
            CComPtr<IPoint2d> pntCGTemp;
            get_TemporaryStrandCG(x, &pntCGTemp);
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

STDMETHODIMP CPrecastGirder::GetStraightStrandDebondLengthByGridIndex(/*[in]*/EndType endType,/*[in]*/GridIndexType grdIndex,/*[out]*/Float64* XCoord,/*[out]*/Float64* YCoord, /*[out]*/Float64* l1,/*[out]*/Float64* l2)
{
   return m_StraightGrid[endType]->GetDebondLengthByGridIndex(grdIndex, XCoord, YCoord, l1, l2);
}

// Debonded straight strands based on Positions index (i.e., from get_StraightStrandPositions)
STDMETHODIMP CPrecastGirder::GetStraightStrandDebondLengthByPositionIndex(/*[in]*/EndType endType,/*[in]*/StrandIndexType positionIndex,/*[out]*/Float64* XCoord, /*[out]*/Float64* YCoord, /*[out]*/Float64* l1,/*[out]*/Float64* l2)
{
   return m_StraightGrid[endType]->GetDebondLengthByPositionIndex(positionIndex, XCoord, YCoord, l1, l2);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandsDebondedByPositionIndex(/*[in]*/EndType endType,/*[in]*/Float64 distFromStart, /*[out,retval]*/IIndexArray** positionIndexes)
{
   Float64 grd_length;
   this->get_GirderLength(&grd_length);

   return m_StraightGrid[endType]->GetStrandsDebondedByPositionIndex(distFromStart, grd_length, positionIndexes);
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
   /*[out]*/Float64* XCoord, /*[out]*/Float64* YCoord, /*[out]*/Float64* leftBond, /*[out]*/Float64* rightBond)
{
   Float64 gdr_length;
   get_GirderLength(&gdr_length);

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

STDMETHODIMP CPrecastGirder::GetStraightStrandBondedLengthByGridIndex(/*[in]*/GridIndexType grdIndex, /*[in]*/Float64 distFromStart, 
                                              /*[out]*/Float64* XCoord, /*[out]*/Float64* YCoord, /*[out]*/Float64* leftBond, /*[out]*/Float64* rightBond)
{
   Float64 gdr_length;
   get_GirderLength(&gdr_length);

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

STDMETHODIMP CPrecastGirder::GetStraightStrandDebondedRows(/*[out]*/IIndexArray** ppRowIndexes)
{
   return m_StraightGrid[etStart]->GetDebondedRows(ppRowIndexes);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandDebondedConfigurationCountByRow(/*[in]*/RowIndexType rowIdx, /*[out]*/IndexType* pConfigCount)
{
   return m_StraightGrid[etStart]->GetDebondedConfigurationCountByRow(rowIdx, pConfigCount);
}

STDMETHODIMP CPrecastGirder::GetStraightStrandDebondConfigurationByRow(/*[in]*/RowIndexType rowIdx, /*[in]*/IndexType configIdx, /*[out]*/Float64* pXstart, /*[out]*/Float64* pBondedLength, /*[out]*/IndexType* pnStrands)
{
   Float64 gdr_length;
   get_GirderLength(&gdr_length);

   Float64 LdbStart, LdbEnd;
   m_StraightGrid[etStart]->GetDebondConfigurationByRow(rowIdx, configIdx, &LdbStart, &LdbEnd, pnStrands);
   *pXstart = LdbStart;
   *pBondedLength = gdr_length - LdbStart - LdbEnd;
   return S_OK;
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

STDMETHODIMP CPrecastGirder::get_SuperstructureMemberSegment(ISuperstructureMemberSegment** segment)
{
   CHECK_RETOBJ(segment);
   (*segment) = m_pSegment;
   if ( m_pSegment )
   {
      (*segment)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_RebarLayout(IRebarLayout** rebarLayout)
{
   CHECK_RETOBJ(rebarLayout);

   if ( m_RebarLayout == nullptr )
   {
      HRESULT hr = m_RebarLayout.CoCreateInstance(CLSID_RebarLayout);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   (*rebarLayout) = m_RebarLayout;
   (*rebarLayout)->AddRef();
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_ClosureJointRebarLayout(IRebarLayout** rebarLayout)
{
   CHECK_RETOBJ(rebarLayout);

   if ( m_ClosureJointRebarLayout == nullptr )
   {
      HRESULT hr = m_ClosureJointRebarLayout.CoCreateInstance(CLSID_RebarLayout);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   (*rebarLayout) = m_ClosureJointRebarLayout;
   (*rebarLayout)->AddRef();
   return S_OK;
}


///// PRIVATE /////
void CPrecastGirder::GetHarpPointLocations(Float64& hp1,Float64& hp2)
{
   hp1 = GetHarpPointLocation(m_HP1,m_HPReference,m_HPMeasure,false,false);
   hp2 = GetHarpPointLocation(m_HP2,m_HPReference,m_HPMeasure,true,false);

   ATLASSERT( hp1 <= hp2 );
}

void CPrecastGirder::GetEndHarpPointLocations(Float64& hp1,Float64& hp2)
{
   hp1 = GetHarpPointLocation(m_HPStart,m_EndHPReference,m_EndHPMeasure,false,true);
   hp2 = GetHarpPointLocation(m_HPEnd,  m_EndHPReference,m_EndHPMeasure,true,true);

   ATLASSERT( hp1 <= hp2 );
}

Float64 CPrecastGirder::GetHarpPointLocation(Float64 hp,HarpPointReference hpRef,HarpPointMeasure hpMeasure,bool bRight,bool bLocatingEndHarpPoint)
{
   Float64 left_end_distance;
   Float64 right_end_distance;

   Float64 span_length;
   get_SpanLength(&span_length);

   Float64 gdr_length;
   get_GirderLength(&gdr_length);

   if (hpMeasure == hpmFractionOfGirderLength)
   {
      hp *= gdr_length;
   }

   if (hpMeasure == hpmFractionOfSpanLength)
   {
      hp *= span_length;
   }

   if (m_bUseMinHpDistance == VARIANT_TRUE && hp < m_MinHpDist && !bLocatingEndHarpPoint)
   {
      hp = m_MinHpDist;
   }

   // hp can now be considered the location of the harp point measured
   // from the point of reference. 

   // convert the hp from it's point of reference to the left end of the girder
   Float64 result;
   switch( hpRef )
   {
   case hprEndOfGirder:
      result = (bRight ? gdr_length - hp : hp);
      if ((bRight && result < gdr_length / 2) || (!bRight && gdr_length / 2 < result))
      {
         result = gdr_length / 2;
      }
      break;

   case hprCenterOfGirder:
      result = (bRight ? gdr_length/2 + hp : gdr_length/2 - hp);
      if ((bRight && gdr_length < result) || (!bRight && result < 0))
      {
         result = gdr_length / 2;
      }
      break;

   case hprBearing:
      get_LeftEndDistance(&left_end_distance);
      get_RightEndDistance(&right_end_distance);
      result = (bRight ? gdr_length - right_end_distance - hp : left_end_distance + hp);
      if ((bRight && result < gdr_length / 2) || (!bRight && gdr_length / 2 < result))
      {
         result = gdr_length / 2;
      }
      break;
   }

   ATLASSERT( 0 <= result && result <= gdr_length );
   return result;
}

Float64 CPrecastGirder::GetGirderDepthAdjustment(Float64 Xs, Float64 distToStartGrid, Float64 distBetweenGrids, IStrandGridFiller* pStartGridFiller, IStrandGridFiller* pEndGridFiller)
{
   Float64 Yadj = 0;
   CComQIPtr<ITaperedGirderSegment> taperedSegment(m_pSegment);
   CComQIPtr<IThickenedFlangeSegment> thickenedSegment(m_pSegment);
   if (taperedSegment || thickenedSegment)
   {
      Float64 Lg;
      get_GirderLength(&Lg);

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

Float64 CPrecastGirder::GetGirderWidthAdjustment(Float64 Xs)
{
   Float64 Xadj = 0;
   CComPtr<IShape> shape;
   m_pSegment->get_PrimaryShape(Xs, &shape);

   CComQIPtr<IAsymmetricSection> asymmetric(shape);
   if (asymmetric)
   {
      Float64 wLeft, wRight;
      asymmetric->GetTopWidth(&wLeft, &wRight);
      // wLeft - w/2 = wLeft - (wLeft+wRight)/2 = wLeft/2 - wRight/2
      Xadj = 0.5*(wLeft - wRight);
   }

   return Xadj;
}

HRESULT CPrecastGirder::GetStrandPositions(Float64 distFromStart, Float64 distToStartGrid, Float64 distBetweenGrids, Float64 Lg, Float64 startPrecamber, Float64 endPrecamber,IIndexArray* startFill, IStrandGridFiller* pStartGridFiller, IIndexArray* endFill, IStrandGridFiller* pEndGridFiller, IPoint2dCollection** points)
{
   CComPtr<IPoint2dCollection> startPoints;
   CComPtr<IPoint2dCollection> endPoints;
   pStartGridFiller->GetStrandPositionsEx(startFill,&startPoints); // gets a copy, in Girder Section Coordinates
   pEndGridFiller->GetStrandPositionsEx(endFill,&endPoints); // gets a copy, in Girder Section Coordinates

   // adjust strand grids so that they are measured from the same datum (bottom of girder at left end)
   Float64 Hg = GetSectionHeight(0);
   startPoints->Offset(0, Hg + startPrecamber);
   endPoints->Offset(0, Hg + endPrecamber);

   Float64 Yadj = GetGirderDepthAdjustment(distFromStart, distToStartGrid, distBetweenGrids, pStartGridFiller, pEndGridFiller);
   Float64 Xadj = GetGirderWidthAdjustment(distFromStart);

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
      pntStart->Location(&sx, &sy);

      Float64 ex, ey;
      pntEnd->Location(&ex, &ey);

      Float64 x = ::LinInterp(distFromStart-distToStartGrid,sx,ex,distBetweenGrids);
      Float64 y = ::LinInterp(distFromStart-distToStartGrid,sy,ey,distBetweenGrids);

      CComPtr<IPoint2d> pnt;
      m_Point2dFactory->CreatePoint(&pnt);
      pnt->Move(x+Xadj,y+Yadj);
      pnts->Add(pnt);
   }

   // adjust the location of the strands to be in Girder Section Coordinates again
   Float64 precamber;
   m_pSegment->ComputePrecamber(distFromStart, &precamber);
   pnts->Offset(0, -Hg - precamber);

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

      CComPtr<ICogoEngine> cogoEngine;
      cogoEngine.CoCreateInstance(CLSID_CogoEngine);
      CComPtr<IMeasure2> measure;
      cogoEngine->get_Measure(&measure);

      CComPtr<IDirection> direction; // direction from end to pier point
      Float64 offset; // this is always a positive value because it is a distance
      measure->Inverse(pntPier1,pntBrg1,&offset,&direction);
      if ( !IsZero(offset) )
      {
         // need to determine if the intersection with the pier line is before or after the
         // start CL Brg. we do this by comparing directions
         CComPtr<IDirection> dirSegment;
         measure->Direction(pntEnd1,pntEnd2,&dirSegment); // direction of segment

         Float64 d1,d2;
         direction->get_Value(&d1);
         dirSegment->get_Value(&d2);

         if ( !IsEqual(d1,d2) )
         {
            m_Lengths.dbLeftBearingOffset *= -1;
         }
      }

      direction.Release();
      measure->Inverse(pntBrg2,pntPier2,&offset,&direction);
      if ( !IsZero(offset) )
      {
         // need to determine if the intersection with the pier line is before or after the
         // start CL Brg. we do this by comparing directions
         CComPtr<IDirection> dirSegment;
         measure->Direction(pntEnd1,pntEnd2,&dirSegment); // direction of segment

         Float64 d1,d2;
         direction->get_Value(&d1);
         dirSegment->get_Value(&d2);

         if ( !IsEqual(d1,d2) )
         {
            m_Lengths.dbRightBearingOffset *= -1;
         }
      }

      m_UpdateLengths = false;
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

Float64 CPrecastGirder::GetSectionHeight(Float64 Xs)
{
   Float64 Hg;
   CComPtr<IShape> shape;
   m_pSegment->get_PrimaryShape(Xs,&shape);
   CComPtr<IRect2d> bbox;
   shape->get_BoundingBox(&bbox);
   bbox->get_Height(&Hg);
   return Hg;
}

void CPrecastGirder::GetCGFromPoints(IPoint2dCollection* points, IPoint2d** pCG)
{
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance(CLSID_Point2d);

   Float64 sumX = 0;
   Float64 sumY = 0;
   IndexType nPoints;
   points->get_Count(&nPoints);
   for (IndexType idx = 0; idx < nPoints; idx++)
   {
      CComPtr<IPoint2d> pnt;
      points->get_Item(idx, &pnt);
      Float64 x, y;
      pnt->Location(&x, &y);
      sumX += x;
      sumY += y;
   }

   Float64 cgX = (nPoints == 0 ? 0 : sumX / nPoints);
   Float64 cgY = (nPoints == 0 ? 0 : sumY / nPoints);
   pnt->Move(cgX, cgY);
   pnt.CopyTo(pCG);
}

void CPrecastGirder::RemoveStraightStrandDebondedStrandPositions(Float64 distFromStart, IPoint2dCollection* pPoints)
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
      GetStraightStrandDebondLengthByPositionIndex(etStart, strandIdx, &X, &Y, &l1, &l2);
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
         Float64 leftBond = distFromStart - l1; // amount of bonded strands on the left side of distFromStart
         Float64 rightBond = Ls - distFromStart - l2; // amount of bonded strand on the right side of distFromStart
         if (IsZero(distFromStart) || IsEqual(distFromStart, Ls))
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
