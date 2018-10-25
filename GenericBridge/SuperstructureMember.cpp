///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// SuperstructureMember.cpp : Implementation of CSuperstructureMember
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "SuperstructureMember.h"
#include "Segment.h"
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
   m_pBridge = NULL;
   m_LocationType = ltInteriorGirder;

   m_Release[etStart] = rtNone;
   m_Release[etEnd]   = rtNone;

   return S_OK;
}

void CSuperstructureMember::FinalRelease()
{
}

void CSuperstructureMember::Init(GirderIDType id,LocationType locationType,IGenericBridge* pBridge)
{
   m_ID = id;
   m_LocationType = locationType;
   m_pBridge = pBridge;
}

STDMETHODIMP CSuperstructureMember::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISuperstructureMember,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
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

STDMETHODIMP CSuperstructureMember::AddSegment(ISegment* segment)
{
   m_Segments.push_back(segment);

   m_Segments.back()->putref_SuperstructureMember(this);

   CollectionIndexType nSegments = m_Segments.size();
   if ( 1 < nSegments )
   {
      m_Segments[nSegments-1]->putref_PrevSegment(m_Segments[nSegments-2].p);
      m_Segments[nSegments-2]->putref_NextSegment(m_Segments[nSegments-1].p);
   }

   return S_OK;
}

STDMETHODIMP CSuperstructureMember::get_Segment(SegmentIndexType idx, ISegment **pVal)
{
   if ( idx < 0 || m_Segments.size() <= idx )
      return E_INVALIDARG;

   return m_Segments[idx].CopyTo(pVal);
}

STDMETHODIMP CSuperstructureMember::GetDistanceFromStartOfSegment(Float64 distFromStartOfSSMbr,Float64* distFromStartOfSegment,SegmentIndexType* pSegIdx,ISegment** ppSeg)
{
   if ( distFromStartOfSSMbr < 0 )
   {
      // location before start, return first segment
      m_Segments.front().CopyTo(ppSeg);
      *pSegIdx = 0;
      return E_FAIL;
   }

   std::vector<CComPtr<ISegment>>::iterator segIter(m_Segments.begin());
   std::vector<CComPtr<ISegment>>::iterator segIterEnd(m_Segments.end());

   Float64 currentDistFromStart = 0;
   for ( ; segIter != segIterEnd; segIter++ )
   {
      CComPtr<ISegment> segment(*segIter);

      Float64 segmentLength;
      segment->get_Length(&segmentLength);

      currentDistFromStart += segmentLength;
      if ( distFromStartOfSSMbr <= currentDistFromStart )
      {
         // The end of the current segment is right at or beyond the location we are looking for.
         // This is the first segment to have its end go past the target location so
         // it is the segment we are looking for.

         segment.CopyTo(ppSeg);
         Float64 distFromEndOfSegment = currentDistFromStart - distFromStartOfSSMbr;
         *distFromStartOfSegment = segmentLength - distFromEndOfSegment;

         *pSegIdx = segIter - m_Segments.begin();

         return S_OK;
      }
   }

   // segment not found, return last segment
   m_Segments.back().CopyTo(ppSeg);
   *pSegIdx = m_Segments.size()-1;
   return E_FAIL;
}

STDMETHODIMP CSuperstructureMember::GetDistanceFromStart(SegmentIndexType segIdx,Float64 distFromStartOfSegment,Float64* pDistFromStartOfGirder)
{
   // distFromStartOfSegment is in segment coordinates
   // pDistFromStartOfGirder is in girder path coordinates

   std::vector<CComPtr<ISegment>>::iterator segIter(m_Segments.begin());
   std::vector<CComPtr<ISegment>>::iterator segIterEnd(segIter + segIdx);

   Float64 distFromStart = 0;
   for ( ; segIter != segIterEnd; segIter++ )
   {
      CComPtr<ISegment> segment(*segIter);

      CComPtr<IGirderLine> girderLine;
      segment->get_GirderLine(&girderLine);

      Float64 length;
      girderLine->get_LayoutLength(&length);

      distFromStart += length;
   }

   *pDistFromStartOfGirder = distFromStart + distFromStartOfSegment;

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

STDMETHODIMP CSuperstructureMember::get_LocationType(LocationType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_LocationType;
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

STDMETHODIMP CSuperstructureMember::GetItemDataCount(CollectionIndexType* count)
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