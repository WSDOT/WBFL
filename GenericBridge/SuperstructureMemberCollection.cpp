///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

// SuperstructureMemberCollection.cpp : Implementation of CSuperstructureMemberCollection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "SuperstructureMemberCollection.h"
#include "SuperstructureMember.h"
#include <ComException.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperstructureMemberCollection
HRESULT CSuperstructureMemberCollection::FinalConstruct()
{
//   // Start with 1 default superstructure member
//   CComObject<CSuperstructureMember>* pMember;
//   CComObject<CSuperstructureMember>::CreateInstance(&pMember);
//   CComPtr<ISuperstructureMember> mbr(pMember);
//
//   SuperstructureMemberCollImpl::Add(mbr);

   return S_OK;
}

void CSuperstructureMemberCollection::FinalRelease()
{
   // Forces all the connection points to disconnect
   SuperstructureMemberCollImpl::Clear();
}

void CSuperstructureMemberCollection::SetBridge(IGenericBridge* pBridge)
{
   m_pBridge = pBridge;

   SuperstructureMemberCollImpl::iterator iter;
   for ( iter = begin(); iter != end(); iter++ )
   {
      CComPtr<ISuperstructureMember> mbr = (*iter)->second;
      CSuperstructureMember* pMbr = dynamic_cast<CSuperstructureMember*>(mbr.p);

      pMbr->SetBridge(pBridge);
   }
}

void CSuperstructureMemberCollection::RenameStageReferences(BSTR bstrOldName,BSTR bstrNewName)
{
   // The name of a stage changed... update the references
	for(iterator it= begin(); it!=end(); it++)
   {
      CComPtr<ISuperstructureMember> mbr = it->second;
      CSuperstructureMember* pMbr = dynamic_cast<CSuperstructureMember*>(mbr.p);

      pMbr->RenameStageReferences(bstrOldName,bstrNewName);
   }
}

void CSuperstructureMemberCollection::AddDataForStage(BSTR bstrName)
{
   // Notify each member of the new stage
	for(iterator it= begin(); it!=end(); it++)
   {
      CComPtr<ISuperstructureMember> mbr = it->second;
      CSuperstructureMember* pMbr = dynamic_cast<CSuperstructureMember*>(mbr.p);

      pMbr->AddDataForStage(bstrName);
   }
}

void CSuperstructureMemberCollection::RemoveDataForStage(BSTR bstrName)
{
   // Notify each member that a stage has been removed
	for(iterator it= begin(); it!=end(); it++)
   {
      CComPtr<ISuperstructureMember> mbr = it->second;
      CSuperstructureMember* pMbr = dynamic_cast<CSuperstructureMember*>(mbr.p);

      pMbr->RemoveDataForStage(bstrName);
   }
}

void CSuperstructureMemberCollection::SetID(long id)
{
   m_ID = id;
}

void CSuperstructureMemberCollection::SetPoints(IPoint2d* pLeftEnd,IPoint2d* pLeftRef,IPoint2d* pRightEnd,IPoint2d* pRightRef)
{
   m_RefPoint[etStart] = pLeftRef;
   m_RefPoint[etEnd]   = pRightRef;

   m_EndPoint[etStart] = pLeftEnd;
   m_EndPoint[etEnd]   = pRightEnd;
}

STDMETHODIMP CSuperstructureMemberCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISuperstructureMemberCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CSuperstructureMemberCollection::AdviseSuperstructureMember(ISuperstructureMember* ssm,DWORD *pdwCookie)
{
   CComPtr<ISuperstructureMember> member(ssm);
   HRESULT hr = member.Advise(GetUnknown(),IID_ISuperstructureMemberEvents,pdwCookie);
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point on Superstructure Member\n");
      return hr;
   }

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CSuperstructureMemberCollection::UnadviseSuperstructureMember(ISuperstructureMember* ssm,DWORD dwCookie)
{
   InternalAddRef(); // conteract InternalRelease() in advise
   CComQIPtr<IConnectionPointContainer> pCPC(ssm);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(IID_ISuperstructureMemberEvents,&pCP);

   HRESULT hr = pCP->Unadvise(dwCookie);
   ATLASSERT( SUCCEEDED(hr) );

   return hr;
}

//HRESULT CSuperstructureMemberCollection::PutFractional(CSuperstructureMemberCollection* pThis,VARIANT_BOOL bFractional)
//{
//   if ( pThis->m_bFrac == bFractional )
//      return S_OK;
//
//   // Need to convert all lengths of superstrucutre members to Fractional or Absolute
//   long gdrLineIdx = ::GB_GetGirderLineIndex(pThis->m_pBridge,pThis);
//   Float64 totalLength;
//   Float64 length;
//   Float64 startOffset, endOffset;
//
//   pThis->m_pBridge->get_GirderLineLength(gdrLineIdx,&length);
//   pThis->get_Offset(etStart,&startOffset);
//   pThis->get_Offset(etEnd,&endOffset);
//   totalLength = startOffset + length + endOffset;
//
//   for(iterator it= pThis->begin(); it != pThis->end(); it++)
//   {
//      Float64 mbrLength;
//      CComPtr<ISuperstructureMember> mbr(it->second);
//      HRESULT hr = mbr->get_Length(&mbrLength);
//      if (FAILED(hr))
//         return hr;
//
//      CSuperstructureMember* pMbr = dynamic_cast<CSuperstructureMember*>(mbr.p);
//      if ( bFractional == VARIANT_TRUE )
//      {
//         // make the length fractional
//         pMbr->SetLengthSilent( -1*mbrLength/totalLength ); // < 0 means fractional
//      }
//      else
//      {
//         // make the length absolute
//         ATLASSERT(mbrLength <= 0);
//         pMbr->SetLengthSilent( -1*mbrLength*totalLength ); // -1 makes value position
//      }
//   }
//
//   pThis->m_bFrac = bFractional;
//   pThis->Fire_OnSuperstructureMemberCollectionChanged(pThis);
//   return S_OK;
//}
//
//HRESULT CSuperstructureMemberCollection::PutSymmetrical(CSuperstructureMemberCollection* pThis,VARIANT_BOOL bSymmetrical)
//{
//   if ( pThis->m_bSym == bSymmetrical )
//      return S_OK;
//
//   pThis->m_bSym = bSymmetrical;
//   pThis->Fire_OnSuperstructureMemberCollectionChanged(pThis);
//   return S_OK;
//}
//
//HRESULT CSuperstructureMemberCollection::PutOffset(CSuperstructureMemberCollection* pThis,EndType end,Float64 offset)
//{
//   if ( offset < 0.0 )
//      return E_INVALIDARG;
//
//   if (!IsEqual(offset,pThis->m_Offset[end]))
//   {
//      pThis->m_Offset[end] = offset;
//      pThis->Fire_OnSuperstructureMemberCollectionChanged(pThis);
//   } 
//
//   return S_OK;
//}
//
//HRESULT CSuperstructureMemberCollection::DoAddSuperstructureMember(CSuperstructureMemberCollection* pThis)
//{
//   CComObject<CSuperstructureMember>* pMember;
//   CComObject<CSuperstructureMember>::CreateInstance(&pMember);
//   CComPtr<ISuperstructureMember> mbr = pMember;
//
//   return pThis->SuperstructureMemberCollImpl::Add(mbr);
//}
//
//HRESULT CSuperstructureMemberCollection::UndoAddSuperstructureMember(CSuperstructureMemberCollection* pThis)
//{
//   long count;
//   pThis->SuperstructureMemberCollImpl::get_Count(&count);
//   return pThis->SuperstructureMemberCollImpl::Remove(count-1);
//}
//
//HRESULT CSuperstructureMemberCollection::DoInsertSuperstructureMember(CSuperstructureMemberCollection* pThis,long& idx)
//{
//   CComObject<CSuperstructureMember>* pMember;
//   CComObject<CSuperstructureMember>::CreateInstance(&pMember);
//   CComPtr<ISuperstructureMember> mbr = pMember;
//
//   return pThis->SuperstructureMemberCollImpl::Insert(idx,mbr);
//}
//
//HRESULT CSuperstructureMemberCollection::UndoInsertSuperstructureMember(CSuperstructureMemberCollection* pThis,long& idx)
//{
//   return pThis->SuperstructureMemberCollImpl::Remove(idx);
//}
//
//HRESULT CSuperstructureMemberCollection::DoMoveTo(CSuperstructureMemberCollection* pThis,std::pair<long,long>& keys)
//{
//   long from = keys.first;
//   long to   = keys.second;
//
//   return pThis->SuperstructureMemberCollImpl::MoveTo(from,to);
//}
//
//HRESULT CSuperstructureMemberCollection::UndoMoveTo(CSuperstructureMemberCollection* pThis,std::pair<long,long>& keys)
//{
//   std::pair<long,long> reverseKeys;
//   reverseKeys.first = keys.second;
//   reverseKeys.second = keys.first;
//
//   return DoMoveTo(pThis,reverseKeys);
//}
//
//HRESULT CSuperstructureMemberCollection::DoCopyTo(CSuperstructureMemberCollection* pThis,COPYTO& data)
//{
//   // Hang on to the member that is going to be replaced by the copy for a later undo
//   HRESULT hr = pThis->get_Item(data.to,&data.mbr); // Get a pointer fo the object that will be replaced
//   if ( FAILED(hr) )
//      return hr;
//
//   // Get the item that is going to be copied and clone it
//   CComPtr<ISuperstructureMember> mbr;
//   hr = pThis->get_Item(data.from,&mbr);
//   if ( FAILED(hr) )
//      return hr;
//
//   CSuperstructureMember* pMbr = dynamic_cast<CSuperstructureMember*>(mbr.p);
//   CComPtr<ISuperstructureMember> clone;
//   pMbr->Clone(&clone);
//
//   // Remove the item at the destination
//   pThis->SuperstructureMemberCollImpl::Remove(data.to);
//
//   // Insert the clone at the destination
//   return pThis->SuperstructureMemberCollImpl::Insert(data.to,clone);
//}
//
//HRESULT CSuperstructureMemberCollection::UndoCopyTo(CSuperstructureMemberCollection* pThis,COPYTO& data)
//{
//   // Remove the cloned item from the destination
//   pThis->SuperstructureMemberCollImpl::Remove(data.to);
//
//   // Insert the original back into the collection
//   return pThis->SuperstructureMemberCollImpl::Insert(data.to,data.mbr);
//}
//
//HRESULT CSuperstructureMemberCollection::DoRemove(CSuperstructureMemberCollection* pThis,REMOVE& data)
//{
//   return pThis->SuperstructureMemberCollImpl::Remove(data.index);
//}
//
//HRESULT CSuperstructureMemberCollection::UndoRemove(CSuperstructureMemberCollection* pThis,REMOVE& data)
//{
//   return pThis->SuperstructureMemberCollImpl::Insert(data.index,data.mbr);
//}
//
//HRESULT CSuperstructureMemberCollection::DoReverse(CSuperstructureMemberCollection* pThis,long& dummy)
//{
//   return pThis->SuperstructureMemberCollImpl::Reverse();
//}
//
//HRESULT CSuperstructureMemberCollection::DoClear(CSuperstructureMemberCollection* pThis,CLEAR& data)
//{
//   // Capture all the members that are going to be removed for a later undo
//   iterator iter;
//   for ( iter = pThis->begin(); iter != pThis->end(); iter++ )
//   {
//      StoredType* st = *iter;
//      CComPtr<ISuperstructureMember> mbr(st->second);
//
//      data.members.push_back(mbr);
//   }
//
//   pThis->SuperstructureMemberCollImpl::Clear();
//   return S_OK;
//}
//
//HRESULT CSuperstructureMemberCollection::UndoClear(CSuperstructureMemberCollection* pThis,CLEAR& data)
//{
//   std::vector<CComPtr<ISuperstructureMember> >::iterator iter;
//   for ( iter = data.members.begin(); iter != data.members.end(); iter++ )
//   {
//      CComPtr<ISuperstructureMember> mbr = *iter;
//      pThis->SuperstructureMemberCollImpl::Add(mbr);
//   }
//   return S_OK;
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CSuperstructureMemberCollection::get_Item(CollectionIndexType position, ISuperstructureMember* *pVal)
{
   return SuperstructureMemberCollImpl::get_Item(position,pVal);
}

STDMETHODIMP CSuperstructureMemberCollection::get_Count(CollectionIndexType* pVal)
{
   return SuperstructureMemberCollImpl::get_Count(pVal);
}

STDMETHODIMP CSuperstructureMemberCollection::get_ID(long* id)
{
   CHECK_RETVAL(id);
   *id = m_ID;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberCollection::Add()
{
   CComObject<CSuperstructureMember>* pMember;
   CComObject<CSuperstructureMember>::CreateInstance(&pMember);
   CComPtr<ISuperstructureMember> mbr = pMember;

   return SuperstructureMemberCollImpl::Add(mbr);
}

STDMETHODIMP CSuperstructureMemberCollection::Insert(CollectionIndexType relPosition)
{
   CComObject<CSuperstructureMember>* pMember;
   CComObject<CSuperstructureMember>::CreateInstance(&pMember);
   CComPtr<ISuperstructureMember> mbr = pMember;

   return SuperstructureMemberCollImpl::Insert(relPosition,mbr);
}

STDMETHODIMP CSuperstructureMemberCollection::MoveTo(CollectionIndexType fromPosition,CollectionIndexType toPosition)
{
   return SuperstructureMemberCollImpl::MoveTo(fromPosition,toPosition);
}

STDMETHODIMP CSuperstructureMemberCollection::CopyTo(CollectionIndexType fromPosition, CollectionIndexType toPosition)
{
   // The default container implement does a pointer copy (i.e. a link) this is not the
   // behavior I want here... This is why I'm overriding the implementation

   // Get the item that is going to be copied and clone it
   CComPtr<ISuperstructureMember> mbr;
   HRESULT hr = get_Item(fromPosition,&mbr);
   if ( FAILED(hr) )
      return hr;

   CSuperstructureMember* pMbr = dynamic_cast<CSuperstructureMember*>(mbr.p);
   CComPtr<ISuperstructureMember> clone;
   pMbr->Clone(&clone);

   // Remove the item at the destination
   SuperstructureMemberCollImpl::Remove(toPosition);

   // Insert the clone at the destination
   return SuperstructureMemberCollImpl::Insert(toPosition,clone);
}

STDMETHODIMP CSuperstructureMemberCollection::Remove(CollectionIndexType position)
{
   return SuperstructureMemberCollImpl::Remove(position);
}

STDMETHODIMP CSuperstructureMemberCollection::Reverse()
{
   return SuperstructureMemberCollImpl::Reverse();
}

STDMETHODIMP CSuperstructureMemberCollection::Clear()
{
   return SuperstructureMemberCollImpl::Clear();
}

STDMETHODIMP CSuperstructureMemberCollection::get_MemberLength(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 len=0;
	for(iterator it= begin(); it!=end(); it++)
   {
      Float64 tmp;
      CComPtr<ISuperstructureMember> mbr(it->second);
      HRESULT hr = mbr->get_Length(&tmp);
      if (FAILED(hr))
         return hr;

      len += tmp;
   }

   *pVal = len;


	return S_OK;
}

STDMETHODIMP CSuperstructureMemberCollection::get_Symmetrical(VARIANT_BOOL* bSym)
{
   CHECK_RETVAL(bSym);

   *bSym = m_bSym;

   return S_OK;
}

STDMETHODIMP CSuperstructureMemberCollection::put_Symmetrical(VARIANT_BOOL bSym)
{
   if ( m_bSym == bSym )
      return S_OK;

   m_bSym = bSym;
   Fire_OnSuperstructureMemberCollectionChanged(this);
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberCollection::Clone(ISuperstructureMemberCollection* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new stress point collection and fill it up
   CComObject<CSuperstructureMemberCollection>* pnew;
   HRESULT hr = CComObject<CSuperstructureMemberCollection>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ISuperstructureMemberCollection> spisms(pnew);

   // spisms has one superstructure member by default... remove it
   dynamic_cast<CSuperstructureMemberCollection*>(pnew)->Clear();

   // clone properties
   pnew->m_bSym  = m_bSym;

   // clone collection
   for (iterator it= begin(); it != end(); it++)
   {
      CComPtr<ISuperstructureMember> isp;

      // deep clone
      CComPtr<ISuperstructureMember> ssm(it->second);
      CSuperstructureMember* pSSM = dynamic_cast<CSuperstructureMember*>(ssm.p);
      hr = pSSM->Clone(&isp);
      //hr = it->second->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection points
      hr = ((SuperstructureMemberCollImpl*)pnew)->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   *pColl = spisms;
   (*pColl)->AddRef();

   return S_OK;
}

//STDMETHODIMP CSuperstructureMemberCollection::GetMemberForLocation(Float64 location, ISuperstructureMember** mbr)
//{
//   if ( location < 0 )
//      return E_INVALIDARG;
//
//   CHECK_RETOBJ(mbr);
//
//   CComPtr<IFilteredSuperstructureMemberCollection> members;
//   HRESULT hr = GetSuperstructureMembers(&members);
//   if ( FAILED(hr) )
//      return hr;
//
//   Float64 gdr_line_length;
//   m_pBridge->get_GirderLineLength(m_GdrLineIdx,&gdr_line_length);
//
//   Float64 distance_from_start = 0;
//   CComPtr<IEnumSuperstructureMember> enum_mbrs;
//   members->get__EnumElements(&enum_mbrs);
//   CComPtr<ISuperstructureMember> curr_mbr;
//   while ( enum_mbrs->Next(1,&curr_mbr,NULL) != S_FALSE )
//   {
//      Float64 length;
//      curr_mbr->get_Length(&length);
//
//      if ( m_bFrac == VARIANT_TRUE )
//      {
//         // superstructure member length is a fraction of the overall
//         // girder line length
//         length *= gdr_line_length;
//      }
//
//      if ( InRange(distance_from_start,location,distance_from_start+length) )
//      {
//         (*mbr) = curr_mbr;
//         (*mbr)->AddRef();
//         return S_OK;
//      }
//
//      distance_from_start += length;
//      curr_mbr.Release();
//   }
//
//   // If we got this far, location is beyond the end of the girder line
//   return E_INVALIDARG;
//}

STDMETHODIMP CSuperstructureMemberCollection::GetSuperstructureMembers(IFilteredSuperstructureMemberCollection** pColl)
{
   CHECK_RETOBJ(pColl);

   // use ComObject's create for effieciency
   CComObject<CFilteredSuperstructureMemberCollection>* pnew_coll;
   HRESULT hr = CComObject<CFilteredSuperstructureMemberCollection>::CreateInstance(&pnew_coll);
   if (FAILED(hr))
      return hr;


   Float64 length;
   get_MemberLength(&length);


   CComPtr<IFilteredSuperstructureMemberCollection> pholder(pnew_coll); // holder for ref cnt purposes

   // three different logic choices here: no members, symmetrical or unsymmetrical
   CollectionIndexType nMembers;
   get_Count(&nMembers);
   if ( nMembers == 0 )
   {
      // return empty collection if there are no members
      *pColl = pnew_coll;
      (*pColl)->AddRef(); // for client
      return S_OK;
   }
   else if (m_bSym == VARIANT_FALSE)
   {
      FillNonSymmetrical(length,pnew_coll);
      *pColl = pnew_coll;
      (*pColl)->AddRef(); // for client
   }
   else
   {
      FillSymmetrical(length,pnew_coll);
      *pColl = pnew_coll;
      (*pColl)->AddRef(); // for client
   }

	return S_OK;
}

STDMETHODIMP CSuperstructureMemberCollection::GetReferencePoint(EndType endType,IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   (*ppPoint) = m_RefPoint[endType];
   (*ppPoint)->AddRef();
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberCollection::GetEndPoint(EndType endType,IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   (*ppPoint) = m_EndPoint[endType];
   (*ppPoint)->AddRef();
   return S_OK;
}

//STDMETHODIMP CSuperstructureMemberCollection::GetSegmentForSpanLocation(long spanIdx,Float64 location,Float64* dist,ISegment** segment)
//{
//   HRESULT hr;
//   Float64 dist_from_start;
//   hr = SpanLocationToAbsolute(spanIdx,location,&dist_from_start);
//   if ( FAILED(hr) )
//      return hr;
//
//   return GetSegmentForLocation(dist_from_start,dist,segment);
//}
//
//STDMETHODIMP CSuperstructureMemberCollection::GetSegmentForLocation(Float64 location,Float64* dist,ISegment** segment)
//{
//   CHECK_RETVAL(dist);
//   CHECK_RETOBJ(segment);
//
//   if ( location < 0 )
//      return E_INVALIDARG;
//
//   HRESULT hr;
//
//   CComPtr<IFilteredSuperstructureMemberCollection> mbrs;
//   hr = GetSuperstructureMembers(&mbrs);
//   if ( FAILED(hr) )
//      return hr;
//
//   VARIANT_BOOL bFracMbrs;
//   get_Fractional(&bFracMbrs);
//
//   Float64 gdr_line_length;
//   m_pBridge->get_GirderLineLength(m_GdrLineIdx,&gdr_line_length);
//
//   if ( gdr_line_length < location )
//      return E_INVALIDARG;
//
//   Float64 cumm_location = 0;
//   CComPtr<IEnumSuperstructureMember> enum_mbrs;
//   mbrs->get__EnumElements(&enum_mbrs);
//
//   long nSSMbrs;
//   mbrs->get_Count(&nSSMbrs);
//
//   long ssMbrIdx = 0;
//
//   CComPtr<ISuperstructureMember> mbr;
//   while ( enum_mbrs->Next(1,&mbr,NULL) != S_FALSE )
//   {
//      Float64 mbr_length;
//      mbr->get_Length(&mbr_length);
//
//      if ( bFracMbrs == VARIANT_TRUE )
//         mbr_length *= gdr_line_length;
//
//      if ( IsLE(cumm_location,location) && location < cumm_location+mbr_length ||
//         (ssMbrIdx == nSSMbrs-1 && IsEqual(location,cumm_location+mbr_length)) )
//      {
//         // member was found... break
//         break;
//      }
//      
//      cumm_location += mbr_length;
//
//      mbr.Release();
//
//      ssMbrIdx++;
//   }
//
//   // Get segment out of member
//   Float64 dist_along_member = location - cumm_location;
//   if ( bFracMbrs == VARIANT_TRUE )
//   {
//      dist_along_member /= gdr_line_length;
//   }
//
//   CComPtr<ISegmentItem> seg_item;
//   hr = mbr->GetSegmentForMemberLocation(dist_along_member,dist,&seg_item);
//   if ( FAILED(hr) )
//      return hr;
//
//   if ( bFracMbrs == VARIANT_TRUE )
//   {
//      *dist *= gdr_line_length;
//   }
//
//   return seg_item->get_Segment(segment);
//}

//STDMETHODIMP CSuperstructureMemberCollection::GetSegmentPoint(Float64 location,long* ssmbrIdx,long* segmentIdx,Float64* dist)
//{
//   HRESULT hr;
//
//   Float64 girder_line_length = 0;
//   CComPtr<IGirderSpacing> spacing;
//   m_pBridge->get_GirderSpacing(&spacing);
//   long gdrLineIdx;
//   spacing->get_GirderLineIndex(this,&gdrLineIdx);
//
//   m_pBridge->get_GirderLineLength(gdrLineIdx,&girder_line_length);
//
//
//   // Need to stretch/mirror/squish members and segments
//
//   *ssmbrIdx = 0;
//   Float64 cumm_length = 0;
//   for(iterator it = begin(); it != end(); it++, (*ssmbrIdx)++ )
//   {
//      Float64 mbrLength;
//      CComPtr<ISuperstructureMember> mbr(it->second);
//
//      hr = mbr->get_Length(&mbrLength);
//      if (FAILED(hr))
//         return hr;
//
//      if ( m_bFrac == VARIANT_TRUE )
//         mbrLength *= girder_line_length;
//
//      *dist = location-cumm_length;
//
//      VARIANT_BOOL bFracSegment;
//      mbr->get_Fractional(&bFracSegment);
//
////      if ( bFracSegment == VARIANT_TRUE )
////         *dist /= mbrLength;
//
//      CComPtr<ISegmentItem> segItem;
//      hr = mbr->GetSegmentForMemberLocation(*dist,&segItem);
//// NOTE: It is ok if this call fails. It simply means *dist is past the
////       end of the member.
////      if ( FAILED(hr) )
////         return hr;
//
//      if (segItem)
//      {
//         segItem->get_RelPosition(segmentIdx);
//
//         // Need to measre dist from start of segment
//         for ( long s = 0; s < (*segmentIdx); s++ )
//         {
//            Float64 segment_length;
//
//            CComPtr<ISegment> segment;
//            mbr->get_Segment(s,&segment);
//
//            segment->get_Length(&segment_length);
//
//            if ( bFracSegment == VARIANT_TRUE )
//               segment_length *= -mbrLength;
//
//            (*dist) -= segment_length;
//         }
//         return S_OK;
//      }
//
//      cumm_length += mbrLength;
//   }
//
//   ATLASSERT(false); // should never get here
//   return E_FAIL;
//}
///////////////////////////////////////////////////
HRESULT CSuperstructureMemberCollection::DoSaveItem(IStructuredSave2* save,ISuperstructureMember* item)
{
   CComQIPtr<IStructuredStorage2> ssSSM(item);
   return ssSSM->Save(save);
}

HRESULT CSuperstructureMemberCollection::DoLoadItem(IStructuredLoad2* load,ISuperstructureMember* *ppItem)
{
   CComObject<CSuperstructureMember>* pMember;
   CComObject<CSuperstructureMember>::CreateInstance(&pMember);
   CComPtr<ISuperstructureMember> mbr = pMember;
   pMember->SetBridge(m_pBridge);

   CComQIPtr<IStructuredStorage2> ssSSM(mbr);
   HRESULT hr = ssSSM->Load(load);
   if ( FAILED(hr) )
      return hr;

   (*ppItem) = mbr;
   (*ppItem)->AddRef();

   return S_OK;
}

HRESULT CSuperstructureMemberCollection::SaveAdditionalProperties(IStructuredSave2 *save)
{
   save->put_Property(CComBSTR("Symmetrical"),CComVariant(m_bSym));

   return S_OK;
}

HRESULT CSuperstructureMemberCollection::LoadAdditionalProperties(IStructuredLoad2 *load)
{
   CComVariant var;
   load->get_Property(CComBSTR("Symmetrical"),&var); m_bSym      = var.boolVal;

   return S_OK;
}

//HRESULT CSuperstructureMemberCollection::SpanLocationToAbsolute(long spanIdx,Float64 location,Float64* dist)
//{
//   CComPtr<ISpanCollection> spans;
//   m_pBridge->get_Spans(&spans);
//
//   long nSpans;
//   spans->get_Count(&nSpans);
//
//   if ( spanIdx < 0 || nSpans <= spanIdx )
//      return E_INVALIDARG;
//
//   // convert location from start of span to location from start of superstructure member collection
//   Float64 loc = 0;
//   for ( long s = 0; s < spanIdx; s++ )
//   {
//      CComPtr<ISpan> span;
//      spans->get_Item(s,&span);
//      Float64 l;
//      span->get_GirderLineLength(m_GdrLineIdx,&l);
//      loc += l;
//   }
//
//   Float64 offset;
//   get_Offset(etStart,&offset);
//
//   loc += offset;
//
//   if ( location < 0 )
//   {
//      // location is fraction span length
//      CComPtr<ISpan> span;
//      spans->get_Item(spanIdx,&span);
//      Float64 l;
//      span->get_GirderLineLength(m_GdrLineIdx,&l);
//      location *= -l;
//   }
//
//   loc += location;
//
//   *dist = loc;
//   return S_OK;
//}

HRESULT CSuperstructureMemberCollection::FillNonSymmetrical(Float64 gdrLineLength,CFilteredSuperstructureMemberCollection* pColl)
{
   HRESULT hr;

   Float64 len     = 0.0;
   Float64 prevlen = 0.0;

   for (iterator it = begin(); it != end(); it++)
   {
      StoredType* pStored = *it;
      CComPtr<ISuperstructureMember> member = pStored->second;
      ATLASSERT(member != NULL);

      Float64 mbr_length;
      member->get_Length(&mbr_length);

      prevlen = gdrLineLength - len; // distance to go from start of this superstructure member to end
      len += mbr_length;

      const Float64 TOL=0.001;
      if ( len == gdrLineLength || len+TOL <= gdrLineLength )
      {
         // just add member to our list
         hr = pColl->Add(member);
         if (FAILED(hr))
            return hr;

         if (len == gdrLineLength)
            break; // we're done
      }
      else 
      {
         // we hit the end of the road and the length of the members are greater
         // than the girder line length - we'll need to make a custom member just
         // for the final member.
         CComPtr<ISuperstructureMember> last_member;
         CSuperstructureMember* pMember = dynamic_cast<CSuperstructureMember*>(member.p);
         hr = pMember->Clone(&last_member);
         if (FAILED(hr))
            return hr;

         last_member->put_Length(prevlen);

         hr = pColl->Add(last_member);
         if (FAILED(hr))
            return hr;

         break; // we're done
      } 
   }

   // we've finished through the member, now let's see if the length of the 
   // members filled the girder line. If not, we need to extend the length of the
   // last member to fill it
   if (len < gdrLineLength)
   {
      CollectionIndexType cnt;
      hr = pColl->get_Count(&cnt);

      CComPtr<ISuperstructureMember> last_member;
      hr = pColl->get_Item(cnt-1,&last_member);
      if (FAILED(hr))
         return hr;

      // we don't know if this is a unique segment or a reference - hence
      // we must make a clone and replace it with the clone
      CComPtr<ISuperstructureMember> last_member_clone;
      CSuperstructureMember* pLastMember = dynamic_cast<CSuperstructureMember*>(last_member.p);
      hr = pLastMember->Clone(&last_member_clone);
      if (FAILED(hr))
         return hr;

      // Set the length without validation, events, or transactions
      last_member_clone->put_Length(prevlen);


      hr = pColl->Remove(cnt-1);
      if (FAILED(hr))
         return hr;

      hr = pColl->Insert(cnt-1,last_member_clone);
      if (FAILED(hr))
         return hr;
   }

   return S_OK;
}

HRESULT CSuperstructureMemberCollection::FillSymmetrical(Float64 gdrLineLength,CFilteredSuperstructureMemberCollection* pColl)
{
   HRESULT hr;

   // member is symmetrical
   Float64 length2 = gdrLineLength/2.0;

   // let's build the left half by calling ourself for a non-symmetrical section
   // half our length
   hr = FillNonSymmetrical(length2,pColl);
   if (FAILED(hr))
      return hr;


   CollectionIndexType count;
   hr = pColl->get_Count(&count);
   if (FAILED(hr))
      return hr;

   if (count < 1)
      return S_OK; // no members

   // now let's fill to the right end
   // we know that the last member must be extended to make it symmetrical
   CComPtr<ISuperstructureMember> pfirst;
   hr = pColl->get_Item(count-1, &pfirst);
   if (FAILED(hr))
      return hr;

   Float64 l1;
   hr = pfirst->get_Length(&l1);
   if (FAILED(hr))
      return hr;

   if (l1 < 0.0)
      l1 *= gdrLineLength; // fractional

   l1 *= 2.0;

   // We must clone it to make sure it is unique (could have used a state flag from recursive call)
   CComPtr<ISuperstructureMember> ptmp;
   CSuperstructureMember* pFirst = dynamic_cast<CSuperstructureMember*>(pfirst.p);
   hr = pFirst->Clone(&ptmp);
   if (FAILED(hr))
      return hr;

   // Set the length without validation, events, or transactions
   ptmp->put_Length(l1);

   hr = pColl->Remove(count-1);
   if (FAILED(hr))
      return hr;

   hr = pColl->Insert(count-1,ptmp);
   if (FAILED(hr))
      return hr;

   // now let's fill in the rest by copying from the left side to the right
   for (long lfcnt = count-2; lfcnt>=0; lfcnt--)
   {
      CComPtr<ISuperstructureMember> plft;
      hr = pColl->get_Item(lfcnt, &plft);
      if (FAILED(hr))
         return hr;

      hr = pColl->Add(plft);
      if (FAILED(hr))
         return hr;
   }

   return S_OK;
}
