///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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
   m_Length = 1.0;
   m_Release[etStart] = rtNone;
   m_Release[etEnd]   = rtNone;

   m_pSegments = new CSegments(this);

   m_bAreSegmentsSymmetrical = VARIANT_FALSE;
   m_bAreSegmentLengthsFractional  = VARIANT_FALSE;

   return S_OK;
}

void CSuperstructureMember::FinalRelease()
{
   // destroy segments while we are still alive
   m_pSegments->Clear();
   delete m_pSegments;
   m_pSegments = 0;
}

void CSuperstructureMember::SetBridge(IGenericBridge* pBridge)
{
   m_pBridge = pBridge;

   m_pSegments->SetBridge(m_pBridge);
}

void CSuperstructureMember::RenameStageReferences(BSTR bstrOldName,BSTR bstrNewName)
{
   if (m_bstrReleaseStage[etStart] == bstrOldName )
      m_bstrReleaseStage[etStart] = bstrNewName;

   if (m_bstrReleaseStage[etEnd] == bstrOldName )
      m_bstrReleaseStage[etEnd] = bstrNewName;
}

void CSuperstructureMember::AddDataForStage(BSTR bstrName)
{
}

void CSuperstructureMember::RemoveDataForStage(BSTR bstrName)
{
#pragma Reminder("Status Item...")
   // If the support removal stage is removed, log that in the status center
   if (m_bstrReleaseStage[etStart] == bstrName )
      m_bstrReleaseStage[etStart].Empty();

   if (m_bstrReleaseStage[etEnd] == bstrName )
      m_bstrReleaseStage[etEnd].Empty();
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
// CSegmentsOwner implementation
HRESULT CSuperstructureMember::SetUpConnection(ISegmentItem* pCp, unsigned long* pcookie)
{
   HRESULT hr = AdviseSegmentItem(pCp,pcookie);
   return S_OK;
}

void CSuperstructureMember::BreakConnection(ISegmentItem* pCp, unsigned long cookie)
{
   UnadviseSegmentItem(pCp,cookie);
}

void CSuperstructureMember::OnSegmentsChanged(CSegments* psegments)
{
   Fire_OnSuperstructureMemberChanged(this);
}

Float64 CSuperstructureMember::Length()
{
   return m_Length;
}

HRESULT CSuperstructureMember::AdviseSegmentItem(ISegmentItem* segItem,DWORD* pdwCookie)
{
   CComPtr<ISegmentItem> item(segItem);
   HRESULT hr = item.Advise(GetUnknown(),IID_ISegmentItemEvents,pdwCookie);
   ATLASSERT(SUCCEEDED(hr));

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CSuperstructureMember::UnadviseSegmentItem(ISegmentItem* segItem,DWORD dwCookie)
{
   InternalAddRef(); // conteract InternalRelease() in advise
   CComQIPtr<IConnectionPointContainer> pCPC(segItem);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(IID_ISegmentItemEvents,&pCP);

   HRESULT hr = pCP->Unadvise(dwCookie);
   ATLASSERT( SUCCEEDED(hr) );

   return hr;
}

////////////////////////////////////////////////////////////////////////
// ISegmentMeasure
STDMETHODIMP CSuperstructureMember::IsFractional()
{
   VARIANT_BOOL bFractional;
   get_AreSegmentLengthsFractional(&bFractional);
   return ( bFractional == VARIANT_TRUE ? S_OK : S_FALSE );
}

////////////////////////////////////////////////////////////////////////
// ISuperstructureMember implementation

STDMETHODIMP CSuperstructureMember::get_Length(Float64 *pVal)
{
	CHECK_RETVAL(pVal);
   (*pVal) = m_Length;
	return S_OK;
}

STDMETHODIMP CSuperstructureMember::put_Length(Float64 length)
{
   ATLASSERT( !IsZero(length) );

   if ( IsEqual(m_Length,length) )
      return S_OK;

   m_Length = length;
   Fire_OnSuperstructureMemberChanged(this);
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::SetEndRelease(EndType end, BSTR bstrReleaseStage, ReleaseType release)
{
   CComBSTR bstrCurrReleaseStage = m_bstrReleaseStage[end];
   ReleaseType currRelease       = m_Release[end];

   if ( bstrCurrReleaseStage == bstrReleaseStage && currRelease == release )
      return S_OK; // Nothing is changing

   m_bstrReleaseStage[end] = bstrReleaseStage;
   m_Release[end] = release;

   Fire_OnSuperstructureMemberChanged(this);
   
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::GetEndRelease(EndType end, BSTR *strReleaseStage, ReleaseType *release)
{
   CHECK_RETSTRING(strReleaseStage);
   CHECK_RETVAL(release);

   (*strReleaseStage) = m_bstrReleaseStage[end].Copy();
   (*release)         = m_Release[end];

	return S_OK;
}

STDMETHODIMP CSuperstructureMember::get_SegmentLength(Float64 *pVal)
{
   // returns the length of the superstructure member by 
   // adding up the length of each segment
   try
   {
	   return m_pSegments->get_Length(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::get_SegmentCount(CollectionIndexType *pVal)
{
   try
   {
      HRESULT hr = m_pSegments->get_Count(pVal);
      if ( FAILED(hr) && HRESULT_FACILITY(hr) == FACILITY_ITF )
         return Error(HRESULT_CODE(hr),IID_ISuperstructureMember,hr); // custom HRESULT
      else
         return hr;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::get_Segment(CollectionIndexType idx, ISegment **pVal)
{
   try
   {
   	HRESULT hr = m_pSegments->get_Segment(idx, pVal);
      if ( FAILED(hr) && HRESULT_FACILITY(hr) == FACILITY_ITF )
         return Error(HRESULT_CODE(hr),IID_ISuperstructureMember,hr); // custom HRESULT
      else
         return hr;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::get_AreSegmentsSymmetrical(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = m_bAreSegmentsSymmetrical;
	return S_OK;
}

STDMETHODIMP CSuperstructureMember::put_AreSegmentsSymmetrical(VARIANT_BOOL bSymmetrical)
{
   if ( m_bAreSegmentsSymmetrical == bSymmetrical )
      return S_OK;

   m_bAreSegmentsSymmetrical = bSymmetrical;
   Fire_OnSuperstructureMemberChanged(this);
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::get_AreSegmentLengthsFractional(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = m_bAreSegmentLengthsFractional;
	return S_OK;
}

STDMETHODIMP CSuperstructureMember::put_AreSegmentLengthsFractional(VARIANT_BOOL bFractional)
{
   if ( m_bAreSegmentLengthsFractional == bFractional )
      return S_OK;

   m_bAreSegmentLengthsFractional = bFractional;
   Fire_OnSuperstructureMemberChanged(this);
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::AddSegment(ISegment* segment)
{
   try
   {
      // make sure segment length is consistent with expected length measurement type
      Float64 length;
      segment->get_Length(&length);
      if ( m_bAreSegmentLengthsFractional == VARIANT_TRUE )
      {
         if ( length > 0 )
            return Error(IDS_E_FRACTIONAL_EXPECTED,IID_ISuperstructureMember,GB_E_FRACTIONAL_EXPECTED);
      }
      else
      {
         if ( length < 0 )
            return Error(IDS_E_ABSOLUTE_EXPECTED,IID_ISuperstructureMember,GB_E_ABSOLUTE_EXPECTED);
      }

      segment->putref_SegmentMeasure(this);

      HRESULT hr = m_pSegments->Add(segment);
      if ( FAILED(hr) )
         return hr;

      return S_OK;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::InsertSegment(CollectionIndexType idx,ISegment* segment)
{
   try
   {
      HRESULT hr = m_pSegments->Insert(idx,segment);
      if ( FAILED(hr) )
         return hr;

      CComPtr<ISegment> s;
      m_pSegments->get_Segment(idx,&s);

      return S_OK;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::MoveSegmentTo(CollectionIndexType fromIdx, CollectionIndexType toIdx)
{
   try
   {
   	return m_pSegments->MoveTo(fromIdx,toIdx);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::CopySegmentTo(CollectionIndexType fromIdx, CollectionIndexType toIdx)
{
   // The default container implement does a pointer copy (i.e. a link) this is not the
   // behavior I want here... This is why I'm overriding the implementation

   if ( fromIdx == toIdx )
      return S_OK; // Do nothing if from and to are the same

   // Create a clone of the object that is going to be copied
   CComPtr<ISegment> copySegment;
   HRESULT hr = get_Segment(fromIdx,&copySegment);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ISegment> clone;
   copySegment->Clone(&clone);

   // Remove the item at the destination
   m_pSegments->Remove(toIdx);

   // Insert the clone at the destination
   return m_pSegments->Insert(toIdx,clone);
}

STDMETHODIMP CSuperstructureMember::RemoveSegment(CollectionIndexType idx)
{
   try
   {
	   return m_pSegments->Remove(idx);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::RemoveSegments()
{
   try
   {
      return m_pSegments->RemoveSegments();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::GetMemberSegments(IFilteredSegmentCollection **ppSeg)
{
   try
   {
   	return m_pSegments->GetMemberSegments(m_Length, m_bAreSegmentsSymmetrical, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::GetSegmentForMemberLocation(Float64 location, Float64* dist,ISegmentItem **ppSeg)
{
   try
   {
   	return m_pSegments->GetSegmentForMemberLocation(m_Length, m_bAreSegmentsSymmetrical, location, dist, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::ReverseSegments()
{
   return m_pSegments->Reverse();
}

STDMETHODIMP CSuperstructureMember::Clone(ISuperstructureMember* *clone)
{
   CComObject<CSuperstructureMember>* pClone;
   HRESULT hr = CComObject<CSuperstructureMember>::CreateInstance(&pClone);
   if (FAILED(hr))
      return hr;

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->SetBridge(m_pBridge);

   pClone->put_Length(m_Length);
   pClone->put_AreSegmentsSymmetrical(m_bAreSegmentsSymmetrical);
   pClone->put_AreSegmentLengthsFractional(m_bAreSegmentLengthsFractional);
   pClone->SetEndRelease(etStart, m_bstrReleaseStage[etStart],m_Release[etStart]);
   pClone->SetEndRelease(etEnd,   m_bstrReleaseStage[etEnd],  m_Release[etEnd]);
   
   hr = m_pSegments->Copy( pClone->GetSegments() );
   if (FAILED(hr))
      return hr;

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

   load->get_Property(CComBSTR("Length"),&var);
   m_Length = var.dblVal;

   load->get_Property(CComBSTR("Symmetrical"),&var);
   m_bAreSegmentsSymmetrical = var.boolVal;

   load->get_Property(CComBSTR("StartRelease"),&var);
   m_Release[0] = (ReleaseType)var.lVal;

   load->get_Property(CComBSTR("EndRelease"),&var);
   m_Release[1] = (ReleaseType)var.lVal;

   load->get_Property(CComBSTR("StartReleaseStage"),&var);
   m_bstrReleaseStage[0] = var.bstrVal;
   var.Clear();

   load->get_Property(CComBSTR("EndReleaseStage"),&var);
   m_bstrReleaseStage[1] = var.bstrVal;
   var.Clear();

   m_pSegments->Load(load);

#pragma Reminder("UPDATE: Load Item Data")

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CSuperstructureMember::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("SuperstructureMember"),1.0);

   save->put_Property(CComBSTR("Length"),CComVariant(m_Length));
   save->put_Property(CComBSTR("Symmetrical"),CComVariant(m_bAreSegmentsSymmetrical));
   save->put_Property(CComBSTR("StartRelease"),CComVariant(m_Release[0]));
   save->put_Property(CComBSTR("EndRelease"),CComVariant(m_Release[1]));
   save->put_Property(CComBSTR("StartReleaseStage"),CComVariant(m_bstrReleaseStage[0]));
   save->put_Property(CComBSTR("EndReleaseStage"),CComVariant(m_bstrReleaseStage[1]));

#pragma Reminder("UPDATE: Save Item Data")

   m_pSegments->Save(save);

   save->EndUnit();
   return S_OK;
}