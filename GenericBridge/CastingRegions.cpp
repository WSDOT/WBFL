///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2019  Washington State Department of Transportation
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

// CastingRegions.cpp : Implementation of CCastingRegions
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "CastingRegions.h"
#include "CastingRegion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCastingRegions
void CCastingRegions::FinalRelease()
{
}

STDMETHODIMP CCastingRegions::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICastingRegions,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////
HRESULT CCastingRegions::DoSaveItem(IStructuredSave2* save,ICastingRegion* item)
{
   CComQIPtr<IStructuredStorage2> ss(item);
   return ss->Save(save);
}

HRESULT CCastingRegions::DoLoadItem(IStructuredLoad2* load,ICastingRegion* *ppItem)
{
   return E_FAIL;
}

/////////////////////////////////////////////////////////////////
// ICastingRegions
STDMETHODIMP CCastingRegions::putref_Bridge(IGenericBridge* pBridge)
{
   CHECK_IN(pBridge);
   m_pBridge = pBridge; // weak references
   return S_OK;
}

STDMETHODIMP CCastingRegions::get_Bridge(IGenericBridge** ppBridge)
{
   CHECK_RETOBJ(ppBridge);
   (*ppBridge) = m_pBridge;
   if (*ppBridge)
      (*ppBridge)->AddRef();

   return S_OK;
}

STDMETHODIMP CCastingRegions::put_Boundary(CastingRegionBoundary boundary)
{
   m_Boundary = boundary;
   return S_OK;
}

STDMETHODIMP CCastingRegions::get_Boundary(CastingRegionBoundary *pBoundary)
{
   CHECK_RETVAL(pBoundary);
   *pBoundary = m_Boundary;
   return S_OK;
}

STDMETHODIMP CCastingRegions::CreateRegion(PierIDType startPierID, Float64 Xstart, PierIDType endPierID,Float64 Xend, IMaterial* pMaterial, ICastingRegion** ppRegion)
{
   if (startPierID == INVALID_ID || endPierID == INVALID_ID)
   {
      return E_INVALIDARG;
   }

   CComObject<CCastingRegion>* pRegion;
   CComObject<CCastingRegion>::CreateInstance(&pRegion);
   pRegion->Init(this, startPierID, Xstart, endPierID, Xend, pMaterial);

   CComPtr<ICastingRegion> castingRegion = pRegion;
   Add(castingRegion);

   castingRegion.CopyTo(ppRegion);

   return S_OK;
}

STDMETHODIMP CCastingRegions::FindRegion(Float64 Xb, SectionBias bias, IndexType* pIndex, ICastingRegion** ppRegion)
{
   CHECK_RETVAL(pIndex);
   CHECK_RETOBJ(ppRegion);
   if (m_coll.size() == 1)
   {
      *pIndex = 0;
      m_coll.front().second.m_T.CopyTo(ppRegion);
      return S_OK;
   }

   *pIndex = 0;
   auto iter = std::begin(m_coll);
   auto end = std::end(m_coll);
   for( ; iter != end; iter++)
   {
      auto& storedItem(*iter);
      CComPtr<ICastingRegion> region(storedItem.second);
      VARIANT_BOOL vbContainsPoint;
      region->ContainsPoint(Xb, &vbContainsPoint);
      if (vbContainsPoint == VARIANT_TRUE)
      {
         // the current region contains the point
         // if the request is for a right face section bias and Xb is at
         // the end of the region, then the actual region is the next region
         Float64 XbStart, XbEnd;
         region->GetRange(&XbStart, &XbEnd);
         if (bias == sbRight && IsEqual(Xb,XbEnd) && iter+1 != end)
         {
            auto& nextStoredItem(*(iter + 1));
            CComPtr<ICastingRegion> next_region(nextStoredItem.second);
#if defined _DEBUG
            VARIANT_BOOL vbNextContainsPoint;
            next_region->ContainsPoint(Xb, &vbNextContainsPoint);
            ATLASSERT(vbNextContainsPoint == VARIANT_TRUE);
#endif
            next_region.CopyTo(ppRegion);
            (*pIndex)++;
         }
         else
         {
            region.CopyTo(ppRegion);
         }
         return S_OK;
      }
      (*pIndex)++;
   }
   return E_FAIL;
}

STDMETHODIMP CCastingRegions::FindRegionEx(GirderIDType ssmbrID, SegmentIndexType segIdx, Float64 Xs, SectionBias bias, IndexType* pIndex,ICastingRegion** ppRegion)
{
   CHECK_RETVAL(pIndex);
   CHECK_RETOBJ(ppRegion);
   if (m_coll.size() == 1)
   {
      *pIndex = 0;
      m_coll.front().second.m_T.CopyTo(ppRegion);
      return S_OK;
   }

   // Get ssmbrID, segIdx, Xs as a plan view point
   CComPtr<ISuperstructureMember> ssMbr;
   m_pBridge->get_SuperstructureMember(ssmbrID, &ssMbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   ssMbr->get_Segment(segIdx, &segment);

   CComPtr<IGirderLine> girderLine;
   segment->get_GirderLine(&girderLine);

   CComPtr<IPoint2d> pntStart;
   girderLine->get_EndPoint(etStart, &pntStart); // point at start of segment (Xs is measured from here)

   CComPtr<IDirection> direction;
   girderLine->get_Direction(&direction); // segment direction

   // locate a point Xs from pntStart
   CComPtr<IBridgeGeometry> geometry;
   m_pBridge->get_BridgeGeometry(&geometry);
   CComPtr<ICogoModel> cogoModel;
   geometry->get_CogoModel(&cogoModel);
   CComPtr<ICogoEngine> cogoEngine;
   cogoModel->get_Engine(&cogoEngine);

   CComPtr<ILocate2> locate;
   cogoEngine->get_Locate(&locate);

   CComPtr<IPoint2d> point;
   locate->ByDistDir(pntStart, Xs, CComVariant(direction), 0.0, &point);

   // get the station and offset of the point
   CComPtr<IAlignment> alignment;
   m_pBridge->get_Alignment(&alignment);

   CComPtr<IStation> station;
   Float64 offset;
   alignment->Offset(point, &station, &offset); // this is the station of the boundary when measuring normal to alignment

   // find the closest pier to the point so we can get its direction
   CComPtr<IPierCollection> piers;
   m_pBridge->get_Piers(&piers);
   PierIndexType nPiers;
   piers->get_Count(&nPiers);
   PierIndexType closestPierIdx = INVALID_INDEX;
   Float64 distToClosestPier = Float64_Max;
   for (PierIndexType pierIdx = 0; pierIdx < nPiers; pierIdx++)
   {
      CComPtr<IBridgePier> pier;
      piers->get_Item(pierIdx, &pier);
      CComPtr<IStation> pierStation;
      pier->get_Station(&pierStation);

      Float64 dist;
      alignment->DistanceBetweenStations(CComVariant(pierStation), CComVariant(station), &dist);
      if (fabs(dist) < distToClosestPier)
      {
         distToClosestPier = fabs(dist);
         closestPierIdx = pierIdx;
      }
   }

   if (m_Boundary == crbParallelToPier || closestPierIdx == 0 || closestPierIdx == nPiers-1)
   {
      // region boundary is parallel to pier so intersect a line passing through point, that is parallel to the pier,
      // to with the alignment and get the station/offset of that point

      // region boundary is always parallelto the first and last pier

      CComPtr<IBridgePier> closestPier;
      piers->get_Item(closestPierIdx, &closestPier);
      CComPtr<IDirection> dirClosestPier;
      closestPier->get_Direction(&dirClosestPier);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      CComPtr<IPoint2d> p;
      CComPtr<IVector2d> v;
      line->GetExplicit(&p, &v);

      Float64 dir;
      dirClosestPier->get_Value(&dir);
      v->put_Direction(dir);
      line->SetExplicit(point, v);

      CComPtr<IPoint2d> pntOnAlignment;
      alignment->IntersectEx(line, point, VARIANT_TRUE, VARIANT_TRUE, &pntOnAlignment);

      station.Release();
      alignment->Offset(pntOnAlignment, &station, &offset);
   }

   // get the location of the point in bridge coordinates
   CComPtr<IBridgePier> first_pier;
   piers->get_Item(0, &first_pier);
   CComPtr<IStation> firstStation;
   first_pier->get_Station(&firstStation);

   Float64 Xb;
   alignment->DistanceBetweenStations(CComVariant(firstStation), CComVariant(station), &Xb);

   // use the other version to find the region
   return FindRegion(Xb, bias, pIndex, ppRegion);
}

STDMETHODIMP CCastingRegions::get__EnumCastingRegions(IEnumCastingRegions** enumCastingRegions)
{
   return get__EnumElements(enumCastingRegions);
}
