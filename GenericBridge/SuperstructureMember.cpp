///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// SuperstructureMember.cpp : Implementation of CSuperstructureMember
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "SuperstructureMember.h"
#include "Segment.h"
#include <GenericBridge\Helpers.h>
#include <ComException.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperstructureMember
HRESULT CSuperstructureMember::FinalConstruct()
{
   m_ID = INVALID_ID;
   m_LeftSSMbrID = INVALID_ID;
   m_RightSSMbrID = INVALID_ID;
   m_pBridge = nullptr;

   m_Release[etStart] = rtNone;
   m_Release[etEnd]   = rtNone;

   return S_OK;
}

void CSuperstructureMember::FinalRelease()
{
}

void CSuperstructureMember::Init(GirderIDType id, GirderIDType leftSSMbrID, GirderIDType rightSSMbrID, IGenericBridge* pBridge)
{
   m_ID = id;
   m_LeftSSMbrID = leftSSMbrID;
   m_RightSSMbrID = rightSSMbrID;
   m_pBridge = pBridge;
}

STDMETHODIMP CSuperstructureMember::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISuperstructureMember,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////
// ISuperstructureMember implementation

STDMETHODIMP CSuperstructureMember::get_ID(GirderIDType* pID)
{
   CHECK_RETVAL(pID);
   *pID = m_ID;
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::AddSegment(ISuperstructureMemberSegment* segment)
{
   m_Segments.push_back(segment);

   m_Segments.back()->putref_SuperstructureMember(this);

   IndexType nSegments = m_Segments.size();
   if ( 1 < nSegments )
   {
      m_Segments[nSegments-1]->putref_PrevSegment(m_Segments[nSegments-2].p);
      m_Segments[nSegments-2]->putref_NextSegment(m_Segments[nSegments-1].p);
   }

   ClearGirderProfile(this);

   return S_OK;
}

STDMETHODIMP CSuperstructureMember::get_Segment(SegmentIndexType idx, ISuperstructureMemberSegment **pVal)
{
   if ( idx < 0 || m_Segments.size() <= idx )
      return E_INVALIDARG;

   return m_Segments[idx].CopyTo(pVal);
}

STDMETHODIMP CSuperstructureMember::GetDistanceFromStartOfSegment(Float64 Xg,Float64* pXs,SegmentIndexType* pSegIdx,ISuperstructureMemberSegment** ppSeg)
{
   if ( Xg < 0 )
   {
      // location before start, return first segment
      m_Segments.front().CopyTo(ppSeg);
      *pSegIdx = 0;
      *pXs = Xg;
      return S_FALSE;
   }

   CComPtr<ISuperstructureMemberSegment> firstSegment(m_Segments.front());
   CComPtr<IGirderLine> firstGirderLine;
   firstSegment->get_GirderLine(&firstGirderLine);
   Float64 brgOffset,endDist;
   firstGirderLine->get_BearingOffset(etStart,&brgOffset);
   firstGirderLine->get_EndDistance(etStart,&endDist);

   // it is easier to work in girder path coordinates
   Float64 Xgp = Xg + (brgOffset-endDist);

   std::vector<CComPtr<ISuperstructureMemberSegment>>::iterator segIter(m_Segments.begin());
   std::vector<CComPtr<ISuperstructureMemberSegment>>::iterator segIterEnd(m_Segments.end());

   Float64 currentDistFromStart = 0;
   for ( ; segIter != segIterEnd; segIter++ )
   {
      CComPtr<ISuperstructureMemberSegment> segment(*segIter);

      Float64 segmentLength;
      segment->get_LayoutLength(&segmentLength);

      currentDistFromStart += segmentLength;
      if ( Xgp <= currentDistFromStart )
      {
         // The end of the current segment is right at or beyond the location we are looking for.
         // This is the first segment to have its end go past the target location so
         // it is the segment we are looking for.

         Float64 XgpStart = currentDistFromStart - segmentLength; // location of the start of the segment in girder path coordinates
         Float64 Xsp = Xgp - XgpStart; // distance along segments in segment path coordinates

         CComPtr<IGirderLine> girderLine;
         segment->get_GirderLine(&girderLine);
         girderLine->get_BearingOffset(etStart,&brgOffset);
         girderLine->get_EndDistance(etStart,&endDist);

         Float64 Xs  = Xsp - (brgOffset-endDist); // distance from start face of segment

         segment.CopyTo(ppSeg);
         *pXs = Xs;

         *pSegIdx = segIter - m_Segments.begin();

         return S_OK;
      }
   }

   // the point we are looking for is beyond the end of the girder path coordinates.
   // this, however does not mean the point isn't on the girder. if the distance between
   // the Xgp and the end of the girder path coordinate system is less than the end size
   // Xgp is on the end of the last segment.
   CComPtr<ISuperstructureMemberSegment> lastSegment(m_Segments.back());
   CComPtr<IGirderLine> lastGirderLine;
   lastSegment->get_GirderLine(&lastGirderLine);
   lastGirderLine->get_BearingOffset(etEnd,&brgOffset);
   lastGirderLine->get_EndDistance(etEnd,&endDist);
   if ( fabs(currentDistFromStart-Xgp) <= fabs(brgOffset-endDist) )
   {
      lastSegment.CopyTo(ppSeg);
      *pSegIdx = m_Segments.size()-1;
      Float64 segmentLength;
      lastGirderLine->get_LayoutLength(&segmentLength);
      Float64 XgpStart = currentDistFromStart - segmentLength;
      Float64 Xsp = Xgp - XgpStart;
      lastGirderLine->get_BearingOffset(etStart,&brgOffset);
      lastGirderLine->get_EndDistance(etStart,&endDist);
      Float64 Xs = Xsp - (brgOffset-endDist);
      *pXs = Xs;
      return S_OK;
   }

   // Xgp is not on the girder, return last segment
   m_Segments.back().CopyTo(ppSeg);
   *pSegIdx = m_Segments.size()-1;
   return E_FAIL;
}

STDMETHODIMP CSuperstructureMember::GetDistanceFromStart(SegmentIndexType segIdx,Float64 Xs,Float64* pXg)
{
   if ( segIdx == 0 )
   {
      // Xg = Xs for the first segment
      *pXg = Xs;
      return S_OK;
   }

   // work in girder path coordinates
   // sum layout lengths until we get to the start of the segment in question
   Float64 XgpStart = 0;
   ATLASSERT( segIdx < m_Segments.size() );
   std::vector<CComPtr<ISuperstructureMemberSegment>>::iterator segIter(m_Segments.begin());
   std::vector<CComPtr<ISuperstructureMemberSegment>>::iterator segIterEnd(segIter + segIdx);
   for ( ; segIter != segIterEnd; segIter++ )
   {
      CComPtr<ISuperstructureMemberSegment> segment(*segIter);

      CComPtr<IGirderLine> girderLine;
      segment->get_GirderLine(&girderLine);

      Float64 layout_length;
      girderLine->get_LayoutLength(&layout_length);

      XgpStart += layout_length;
   }

   // add distance from CL Pier/TS to start face of this segment
   //
   // CL Pier 0
   // |
   // |<--------------------------- Xgp ---------------------->|
   // |<----------------- XgpFace ----------->|<----- Xs ----->|
   // |<-------------- XgpStart ---------->|  |                |
   // |                                    |  |                |
   // |     +--------------/ /----------+  |  +----------------*-----/
   // |     | Seg 0        \ \ Seg i-1  |  |  |  Seg i (thisSegment) \
   // |     +--------------/ /----------+  |  +----------------------/
   // |     |                             CL Pier/TS           |
   // |< * >|<-------------------- Xg ------------------------>|
   //    |
   //    +-- offset

   CComPtr<ISuperstructureMemberSegment> thisSegment(*(m_Segments.begin()+segIdx));
   CComPtr<IGirderLine> girderLine;
   thisSegment->get_GirderLine(&girderLine);
   Float64 brgOffset, endDist;
   girderLine->get_BearingOffset(etStart,&brgOffset);
   girderLine->get_EndDistance(etStart,&endDist);
   Float64 XgpFace = XgpStart + (brgOffset-endDist);

   // add segment distance
   Float64 Xgp = XgpFace + Xs;

   // subtract the distance from CL Pier at start of girder to face of start of girder
   girderLine.Release();
   m_Segments.front()->get_GirderLine(&girderLine);
   girderLine->get_BearingOffset(etStart,&brgOffset);
   girderLine->get_EndDistance(etStart,&endDist);
   Float64 offset = brgOffset - endDist;
   Float64 Xg = Xgp - offset;
   *pXg = Xg;

   return S_OK;
}

STDMETHODIMP CSuperstructureMember::get_SegmentCount(SegmentIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Segments.size();
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::SetEndRelease(EndType end, StageIndexType stageIdx, ReleaseType release)
{
   StageIndexType currStageIdx = m_ReleaseStageIndex[end];
   ReleaseType currRelease     = m_Release[end];

   if ( currStageIdx == stageIdx && currRelease == release )
      return S_OK; // Nothing is changing

   m_ReleaseStageIndex[end] = stageIdx;
   m_Release[end] = release;
   
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::GetEndRelease(EndType end, StageIndexType* pStageIdx, ReleaseType *release)
{
   CHECK_RETVAL(pStageIdx);
   CHECK_RETVAL(release);

   (*pStageIdx) = m_ReleaseStageIndex[end];
   (*release)   = m_Release[end];

	return S_OK;
}

STDMETHODIMP CSuperstructureMember::GetPlanAngle(Float64 distFromStartOfSSMbr,IAngle** ppAngle)
{
   Float64 distFromStartOfSegment;
   SegmentIndexType segIdx;
   CComPtr<ISuperstructureMemberSegment> segment;
   HRESULT hr = GetDistanceFromStartOfSegment(distFromStartOfSSMbr,&distFromStartOfSegment,&segIdx,&segment);

   SegmentIndexType nSegments;
   get_SegmentCount(&nSegments);

   Float64 cummAngle = 0;
   for ( SegmentIndexType sIdx = 1; sIdx <= segIdx; sIdx++ )
   {
      CComPtr<ISuperstructureMemberSegment> backSegment;
      get_Segment(sIdx-1,&backSegment);

      CComPtr<ISuperstructureMemberSegment> aheadSegment;
      get_Segment(sIdx,&aheadSegment);

      CComPtr<IGirderLine> backGdrLine, aheadGdrLine;
      backSegment->get_GirderLine(&backGdrLine);
      aheadSegment->get_GirderLine(&aheadGdrLine);

      CComPtr<IDirection> backDirection, aheadDirection;
      backGdrLine->get_Direction(&backDirection);
      aheadGdrLine->get_Direction(&aheadDirection);

      CComPtr<IAngle> objAngle;
      backDirection->AngleBetween(aheadDirection,&objAngle);

      Float64 value;
      objAngle->get_Value(&value);

      cummAngle += value;
   }

   CComPtr<IAngle> angle;
   angle.CoCreateInstance(CLSID_Angle);
   angle->put_Value(cummAngle);

   return angle.CopyTo(ppAngle);
}

STDMETHODIMP CSuperstructureMember::get_LocationType(LocationType* pVal)
{
   CHECK_RETVAL(pVal);

   LocationType locationType;
   if (m_LeftSSMbrID == INVALID_ID )
   {
      locationType = ltLeftExteriorGirder;
   }
   else if (m_RightSSMbrID == INVALID_ID)
   {
      locationType = ltRightExteriorGirder;
   }
   else
   {
      locationType = ltInteriorGirder;
   }

   *pVal = locationType;

   return S_OK;
}

STDMETHODIMP CSuperstructureMember::get_LeftSSMbrID(GirderIDType* pID)
{
   CHECK_RETVAL(pID);
   *pID = m_LeftSSMbrID;
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::get_RightSSMbrID(GirderIDType* pID)
{
   CHECK_RETVAL(pID);
   *pID = m_RightSSMbrID;
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::get_Bridge(IGenericBridge** ppBridge)
{
   CHECK_RETOBJ(ppBridge);
   *ppBridge = m_pBridge;
   (*ppBridge)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IItemData implementation
STDMETHODIMP CSuperstructureMember::AddItemData(BSTR name,IUnknown* data)
{
   return m_ItemDataMgr.AddItemData(name,data);
}

STDMETHODIMP CSuperstructureMember::GetItemData(BSTR name,IUnknown** data)
{
   return m_ItemDataMgr.GetItemData(name,data);
}

STDMETHODIMP CSuperstructureMember::RemoveItemData(BSTR name)
{
   return m_ItemDataMgr.RemoveItemData(name);
}

STDMETHODIMP CSuperstructureMember::GetItemDataCount(IndexType* count)
{
   return m_ItemDataMgr.GetItemDataCount(count);
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CSuperstructureMember::Load(IStructuredLoad2* load)
{
   CComVariant var;

   load->BeginUnit(CComBSTR("SuperstructureMember"));


//   load->get_Property(CComBSTR("StartRelease"),&var);
//   m_Release[0] = (ReleaseType)var.lVal;
//
//   load->get_Property(CComBSTR("EndRelease"),&var);
//   m_Release[1] = (ReleaseType)var.lVal;
//
//   load->get_Property(CComBSTR("StartReleaseStage"),&var);
//   m_bstrReleaseStage[0] = var.bstrVal;
//   var.Clear();
//
//   load->get_Property(CComBSTR("EndReleaseStage"),&var);
//   m_bstrReleaseStage[1] = var.bstrVal;
//   var.Clear();
//
//#pragma Reminder("UPDATE: Load Item Data")
//
   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("SuperstructureMember"),1.0);

//   save->put_Property(CComBSTR("StartRelease"),CComVariant(m_Release[0]));
//   save->put_Property(CComBSTR("EndRelease"),CComVariant(m_Release[1]));
//   save->put_Property(CComBSTR("StartReleaseStage"),CComVariant(m_bstrReleaseStage[0]));
//   save->put_Property(CComBSTR("EndReleaseStage"),CComVariant(m_bstrReleaseStage[1]));
//
//#pragma Reminder("UPDATE: Save Item Data")

   save->EndUnit();
   return S_OK;
}