///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// Segments.cpp : Implementation of CSegments
#include "stdafx.h"
#include "GenericBridge.hh"
#include "Segments.h"
#include "SegmentItem.h"
#include <algorithm>
#include "FilteredSegmentCollection.h"
#include <ComException.h>
#include <MathEx.h>
#include "Segment.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSegments
CSegments::~CSegments()
{
   Clear();
}

void CSegments::SetBridge(IGenericBridge* pBridge)
{
   m_pBridge = pBridge;
//
//   // iterate through all segments and break connections
//   for (VectorIteratorType it = m_Segments.begin(); it!=m_Segments.end(); it++)
//   {
//      StoredType& stored = *it;
//      CComPtr<ISegmentItem> item = stored.second;
//      CComPtr<ISegment> segment;
//      item->get_Segment(&segment);
//
//      CSegment* pSegment = dynamic_cast<CSegment*>(segment.p);
//      pSegment->SetBridge(pBridge);
//   }
}

void CSegments::MakeFractional()
{
   MakeFractional(true);
}

void CSegments::MakeAbsolute()
{
   MakeFractional(false);
}

bool CSegments::IsFractional()
{
   return m_bFractional;
}

HRESULT CSegments::RemoveSegments()
{
   // erase all 
   for (VectorIteratorType itv=m_Segments.begin(); itv!= m_Segments.end(); itv++)
   {
      // break connection points first
      m_pOwner->BreakConnection(itv->second.m_T.p, itv->first);
   }

   // Erase all the segments
   m_Segments.clear();

   m_pOwner->OnSegmentsChanged(this);

   return S_OK;
}

HRESULT CSegments::Copy(CSegments* pcopy)
{
   // clear out copy
   pcopy->Clear();

   HRESULT hr;
   // iterate over all items and clone them
   for (VectorIteratorType it = m_Segments.begin(); it!=m_Segments.end(); it++)
   {
      StoredType& stored = *it;

      // get our segment and clone it
      CComPtr<ISegmentItem> segment_item(stored.second);
      CComPtr<ISegment> segment;
      hr = segment_item->get_Segment(&segment);
      if (FAILED(hr))
         return hr;

      CComPtr<ISegment> segment_clone;
      hr = segment->Clone(&segment_clone);
      if (FAILED(hr))
         return hr;

      hr = pcopy->Add(segment_clone);
      if (FAILED(hr))
         return hr;
   }

   return S_OK;
}

HRESULT CSegments::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 length=0;

   for (VectorIteratorType it = m_Segments.begin(); it != m_Segments.end(); it++)
   {
      StoredType& stored = *it;
      CComPtr<ISegmentItem> segment_item(stored.second);
      CComPtr<ISegment> segment;
      HRESULT hr = segment_item->get_Segment(&segment);
      if (FAILED(hr))
         return hr;

      Float64 len;
      segment->get_Length(&len);
      if (FAILED(hr))
         return hr;

      if (len < 0.0)
         len = -len * m_pOwner->Length(); // fractional

      length += len;
   }

   *pVal = length;

	return S_OK;
}


HRESULT CSegments::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = m_Segments.size();

	return S_OK;
}

HRESULT CSegments::get_Segment(CollectionIndexType relPosition, ISegment **pSeg)
{
   CHECK_RETOBJ(pSeg);

   if ( !IsValidIndex(relPosition,m_Segments) )
   {
      return E_INVALIDARG;
   }

   return m_Segments.at(relPosition).second.m_T->get_Segment(pSeg);
}


HRESULT CSegments::Add(ISegment * pSeg)
{
   CHECK_IN(pSeg);

   // this function uses Insert to do real work. 
   return Insert(m_Segments.size(), pSeg);
}

HRESULT CSegments::Insert(CollectionIndexType relPosition, ISegment *pSeg)
{
   HRESULT hr;
   CHECK_IN(pSeg);

   CollectionIndexType count = m_Segments.size();
   if (relPosition < 0 || count < relPosition)
      return E_INVALIDARG;

   // create and initilize our new segmentitem
   CComObject<CSegmentItem>* psegitem;
   hr = CComObject<CSegmentItem>::CreateInstance(&psegitem);

   CComPtr<ISegmentItem> pholder(psegitem); // memory leak avoidance

   // Store a copy of the segment
   CComPtr<ISegment> clone;
   pSeg->Clone(&clone);

   hr = psegitem->PutRefSegment(clone);
   if (FAILED(hr))
      return hr;

//   // Give the segment a reference to its container
//   // (Needed so that a segment can validate its length as absolute or fractional)
//   CSegment* pSegment = dynamic_cast<CSegment*>(pSeg);
//   pSegment->SetContainer(this);
//   pSegment->SetBridge(m_pBridge);

   // have owner set up event handling
   unsigned long cookie;
   hr = m_pOwner->SetUpConnection(psegitem, &cookie);
   if (FAILED(hr))
      return hr;

   VectorIteratorType itv = m_Segments.begin();
   itv += relPosition;
   m_Segments.insert(itv, VectorType::value_type(cookie, CAdapt<CComPtr<ISegmentItem>>(psegitem)));

   // update relative positions
   UpdateRelPositions(&m_Segments);

   m_pOwner->OnSegmentsChanged(this);

	return S_OK;
}

HRESULT CSegments::MoveTo(CollectionIndexType fromIndex, CollectionIndexType toIndex)
{
   if ( fromIndex == toIndex )
      return S_OK; 

   // check bounds
   CollectionIndexType ub = m_Segments.size()-1;
   if ((fromIndex < 0 || ub < fromIndex) || (toIndex <0 || ub < toIndex))
      return E_INVALIDARG;

   // do nothing if from==to
   if (fromIndex == toIndex)
      return S_OK;

   // make temporary copy
   StoredType store( m_Segments[fromIndex] );

   // erase by index
   VectorIteratorType it = m_Segments.begin();
   it += fromIndex;

   m_Segments.erase(it);

   // insert by index
   it = m_Segments.begin();
   it += toIndex;

   m_Segments.insert(it, store);

   UpdateRelPositions(&m_Segments);

   m_pOwner->OnSegmentsChanged(this);

   return S_OK;

}

HRESULT CSegments::CopyTo(CollectionIndexType fromIndex, CollectionIndexType toIndex)
{
   // Nothing to do if copying to self
   if (fromIndex == toIndex )
      return S_OK;

   CollectionIndexType ub = m_Segments.size()-1;
   if ((fromIndex < 0 || ub < fromIndex) || (toIndex < 0 || (ub+1) < toIndex))
      return E_INVALIDARG;

   // get the segment
   CComPtr<ISegment> segment;
   HRESULT hr = m_Segments.at(fromIndex).second.m_T->get_Segment(&segment);
   if (FAILED(hr))
      return hr;

   return Insert(toIndex, segment);
}

HRESULT CSegments::Remove(CollectionIndexType index)
{
   if ( !IsValidIndex(index,m_Segments) )
      return E_INVALIDARG;

   // erase by index
   VectorIteratorType itv = m_Segments.begin();
   itv += index;

   // break connection points first
   m_pOwner->BreakConnection(itv->second.m_T, itv->first);

   m_Segments.erase(itv);

   // reindex SegmentItems
   UpdateRelPositions(&m_Segments);

   m_pOwner->OnSegmentsChanged(this);

	return S_OK;
}

HRESULT CSegments::Reverse()
{
   if (m_Segments.size() < 2)
      return S_OK;

   std::reverse(m_Segments.begin(), m_Segments.end());

   UpdateRelPositions(&m_Segments);

   m_pOwner->OnSegmentsChanged(this);

   return S_OK;
}

HRESULT CSegments::GetSegmentForMemberLocation(Float64 Length, VARIANT_BOOL isSymmetrical, Float64 location, Float64* dist,ISegmentItem** ppSegi)
{
   CHECK_RETVAL(dist);
   CHECK_RETOBJ(ppSegi);

   // can't find anything that's off of member
   Float64 local_dist;
   try
   {
      local_dist = GB_GetFracDistance(location, Length, true);
      local_dist = IsEqual(local_dist,Length) ? Length : local_dist;
   }
   catch(FracRes&)
   {
      THROW_IDS(IDS_E_LOCATION_OUT_OF_RANGE,GB_E_LOCATION_OUT_OF_RANGE,IDH_E_LOCATION_OUT_OF_RANGE);
   }

   location = local_dist;
	
   // set up for location search
   if (isSymmetrical==VARIANT_TRUE)
   {
      // we will only be searching over half the length of symmetrical sections
      Float64 l2 = Length/2.0;
      if(l2 < location)
         location = Length-location;

      Length = l2;
   }

   // search the vector for our segment
   Float64 len = 0;
   Float64 loc = 0;
   for (VectorIteratorType it = m_Segments.begin(); it != m_Segments.end(); it++)
   {
      StoredType& stored = *it;
      CComPtr<ISegmentItem> segment_item = stored.second;
      CComPtr<ISegment> segment;
      HRESULT hr = segment_item->get_Segment(&segment);
      if (FAILED(hr))
         return hr;

      segment->get_Length(&len);
      if (FAILED(hr))
         return hr;

      if (len < 0.0)
         len = -len * m_pOwner->Length(); // fractional

      loc += len;

      if (location <= loc)
      {
         // we found our segment
         *ppSegi = segment_item;
         (*ppSegi)->AddRef();

         *dist = location - (loc-len);
         break;
      }
   }

   if (loc < location)
   {
      // List of segments was shorter than Length.
      // Extend the last segment to the end
      CComPtr<ISegmentItem> psegi = m_Segments.back().second;

      *ppSegi = psegi;
      (*ppSegi)->AddRef();

      *dist = location - (loc-len);
   }

	return S_OK;
}


HRESULT CSegments::GetSegments(IFilteredSegmentCollection ** pcoll )
{
	CHECK_RETOBJ(pcoll);

   CComObject<CFilteredSegmentCollection>* pnew;
   HRESULT hr = CComObject<CFilteredSegmentCollection>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IFilteredSegmentCollection> pholder(pnew); // memory leak prot

   (*pcoll) = pnew;
   (*pcoll)->AddRef();

   // add segment items to temporary container
   for (VectorIteratorType it = m_Segments.begin(); it != m_Segments.end(); it++)
   {
      StoredType& stored = *it;
      CComPtr<ISegmentItem> segment_item(stored.second);
      CComPtr<ISegment> segment;
      hr = segment_item->get_Segment(&segment);
      if (FAILED(hr))
         return hr;

      hr = pnew->Add(segment);
      if (FAILED(hr))
         return hr;
   }   


	return S_OK;
}

static const Float64 TOL =1.0e-8;

HRESULT CSegments::GetMemberSegments(Float64 length, VARIANT_BOOL isSymmetrical, IFilteredSegmentCollection **pColl)
{
	CHECK_RETOBJ(pColl);

   if (length <= 0.0)
      return E_INVALIDARG;

   // use ComObject's create for effieciency
   CComObject<CFilteredSegmentCollection>* pnew_coll;
   HRESULT hr = CComObject<CFilteredSegmentCollection>::CreateInstance(&pnew_coll);
   if (FAILED(hr))
      return hr;


   CComPtr<IFilteredSegmentCollection> pholder(pnew_coll); // holder for ref cnt purposes

   // three different logic choices here: no segments, symmetrical or unsymmetrical
   if (m_Segments.size()==0)
   {
      // return empty collection if there are no segments
      *pColl = pnew_coll;
      (*pColl)->AddRef(); // for client
      return S_OK;
   }
   else if (isSymmetrical==VARIANT_FALSE)
   {
      // member is not symmetrical
      Float64 len=0.0;
      Float64 prevlen=0.0;
      for (VectorIteratorType it = m_Segments.begin(); it != m_Segments.end(); it++)
      {
         StoredType& stored = *it;
         CComPtr<ISegmentItem> segment_item = stored.second;
         CComPtr<ISegment> segment;
         hr = segment_item->get_Segment(&segment);
         if (FAILED(hr))
         {
            ATLASSERT(0); // should never happen
            return hr;
         }

         Float64 seglen;
         hr = segment->get_Length(&seglen);

         if (seglen < 0.0)
            seglen = -seglen * m_pOwner->Length(); // fractional

         prevlen = length - len; // distance to go from start of this 
                                 // segment to end
         len += seglen;

         if ( len == length || len+TOL <= length )
         {
            // just add segment to our list
            hr = pnew_coll->Add(segment);
            if (FAILED(hr))
               return hr;

            if (len == length)
               break; // we're done
         }
         else 
         {
            // we hit the end of the road and the length of the segments is greater
            // than the member length - we'll need to make a custom segment just
            // for the final segment.
            CComPtr<ISegment> last_segment;
            hr = segment->Clone(&last_segment);
            if (FAILED(hr))
               return hr;

//            // Set the length without validation, events, or transactions
//            CSegment* pClone = dynamic_cast<CSegment*>(last_segment.p);
//            pClone->SetLength(prevlen);
            last_segment->put_Length(prevlen);

//            pClone->SetContainer(this);
//            pClone->SetBridge(m_pBridge);

            hr = pnew_coll->Add(last_segment);
            if (FAILED(hr))
               return hr;

            break; // we're done
         }
      }

      // we've finished through the sections, now let's see if the length of the 
      // sections filled the member. If not, we need to extend the length of the
      // last segment to fill it
      if (len < length)
      {
         CollectionIndexType cnt;
         hr = pnew_coll->get_Count(&cnt);

         CComPtr<ISegment> last_segment;
         hr = pnew_coll->get_Item(cnt-1,&last_segment);
         if (FAILED(hr))
            return hr;

         // we don't know if this is a unique segment or a reference - hence
         // we must make a clone and replace it with the clone
         CComPtr<ISegment> last_segment_clone;
         hr = last_segment->Clone(&last_segment_clone);
         if (FAILED(hr))
            return hr;

         // Set the length without validation, events, or transactions
//         CSegment* pClone = dynamic_cast<CSegment*>(last_segment_clone.p);
//         pClone->SetLength(prevlen);
         last_segment_clone->put_Length(prevlen);

//         pClone->SetContainer(this);
//         pClone->SetBridge(m_pBridge);


         hr = pnew_coll->Remove(cnt-1);
         if (FAILED(hr))
            return hr;

         hr = pnew_coll->Insert(cnt-1,last_segment_clone);
         if (FAILED(hr))
            return hr;
      }

      *pColl = pnew_coll;
      (*pColl)->AddRef(); // for client
   }
   else
   {
      // member is symmetrical
      Float64 length2 = length/2.0;

      // let's build the left half by calling ourself for a non-symmetrical section
      // half our length
      IFilteredSegmentCollection* piifcol=NULL;
      hr = this->GetMemberSegments(length2, VARIANT_FALSE, &piifcol);
      if (FAILED(hr))
         return hr;

      // need to cast so we can call Add below
      CFilteredSegmentCollection* pifcol = static_cast<CFilteredSegmentCollection*>(piifcol);
      if (piifcol==NULL)
      {
         ATLASSERT(0);
         return E_FAIL; // we know our collection so this should never happen
      }

      CollectionIndexType count;
      hr = pifcol->get_Count(&count);
      if (FAILED(hr))
         return hr;

      if (count < 1)
         return S_OK; // no segments

      // now let's fill in the right end
      // we know that the last segment must be extended to make it symmetrical
      CComPtr<ISegment> pfirst;
      hr = pifcol->get_Item(count-1, &pfirst);
      if (FAILED(hr))
         return hr;

      Float64 l1;
      hr = pfirst->get_Length(&l1);
      if (FAILED(hr))
         return hr;

      if (l1<0.0)
         l1 = -l1 * m_pOwner->Length(); // fractional

      l1 *= 2.0;

      // We must clone it to make sure it is unique (could have used a state flag from recursive call)
      CComPtr<ISegment> ptmp;
      hr = pfirst->Clone(&ptmp);
      if (FAILED(hr))
         return hr;

      // Set the length without validation, events, or transactions
//      CSegment* pClone = dynamic_cast<CSegment*>(ptmp.p);
//      pClone->SetLength(l1);
      ptmp->put_Length(l1);
//      pClone->SetContainer(this);
//      pClone->SetBridge(m_pBridge);

      hr = pifcol->Remove(count-1);
      if (FAILED(hr))
         return hr;

      hr = pifcol->Insert(count-1,ptmp);
      if (FAILED(hr))
         return hr;

      // now let's fill in the rest by copying from the left side to the right
      for (CollectionIndexType lfcnt = count-2; lfcnt>=0; lfcnt--)
      {
         CComPtr<ISegment> plft;
         hr = pifcol->get_Item(lfcnt, &plft);
         if (FAILED(hr))
            return hr;

         hr = pifcol->Add(plft);
         if (FAILED(hr))
            return hr;
      }

      *pColl = pifcol; // no need to addref since our recursive call 
                       // already did it.
   }

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CSegments::Load(IStructuredLoad2 * pload)
{
   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("Segments"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   CComVariant var;

   hr = pload->get_Property(CComBSTR("SegmentCount"),&var);
   if (FAILED(hr))
      return hr;

   long segment_count = var.lVal;
   var.Clear();
   for (long iseg=0; iseg < segment_count; iseg++)
   {
      // Create a new segment object
      CComObject<CSegment>* pSegment;
      CComObject<CSegment>::CreateInstance(&pSegment);
      CComPtr<ISegment> segment = pSegment;
//      pSegment->SetBridge(m_pBridge);

      CComQIPtr<IStructuredStorage2> ssSegment(segment);
      ssSegment->Load(pload);

      hr = Add(segment);
      if (FAILED(hr))
         return hr;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}


STDMETHODIMP CSegments::Save(IStructuredSave2 * psave)
{
   HRESULT hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("Segments"), MY_VER);
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("SegmentCount"),CComVariant((long)m_Segments.size()));
      if (FAILED(hr))
         return hr;

      for(VectorIteratorType itv = m_Segments.begin(); itv != m_Segments.end(); itv++)
      {
         // write segments
         StoredType& stored = *itv;
         CComPtr<ISegmentItem> segment_item = stored.second;

         CComPtr<ISegment> segment;
         hr = segment_item->get_Segment(&segment);
         if (FAILED(hr))
            return hr;

           CComQIPtr<IStructuredStorage2> ssSegment(segment);
           hr = ssSegment->Save(psave);
         if (FAILED(hr))
            return hr;
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      ATLASSERT(0);
      return E_FAIL;
   }

   return hr;
}

void CSegments::Clear()
{
   // iterate through all segments and break connections
   for (VectorIteratorType it = m_Segments.begin(); it!=m_Segments.end(); it++)
   {
      StoredType& stored = *it;
      m_pOwner->BreakConnection(stored.second.m_T, stored.first);
   }

   m_Segments.clear();
}

void CSegments::UpdateRelPositions(CSegments::VectorType* pvec)
{
   long i=0;
   for(VectorIteratorType itv=pvec->begin(); itv!=pvec->end(); itv++)
   {
      // have to cast stored item to get access to put method
      CSegmentItem* psegi = static_cast<CSegmentItem*>(itv->second.m_T.p);
      if (psegi==NULL)
      {
         ATLASSERT(0); // should never happen since we are eating our own dog food here
      }

      psegi->m_RelPosition = i;
      i++;
   }
}

void CSegments::MakeFractional(bool bFractional)
{
   if ( m_bFractional == bFractional )
      return;

   // get the overall length of the pier member
   Float64 length = m_pOwner->Length();

   for ( VectorIteratorType it = m_Segments.begin(); it != m_Segments.end(); it++ )
   {
      StoredType& stored = *it;
      CComPtr<ISegmentItem> segment_item(stored.second);
      CComPtr<ISegment> segment;
      segment_item->get_Segment(&segment);

      Float64 segLength;
      segment->get_Length(&segLength);

      ATLASSERT( bFractional == true ? segLength >= 0 : segLength <= 0 );

      if ( bFractional == true )
      {
         segLength /= -length;
      }
      else
      {
         segLength *= -length;
      }

      ATLASSERT( bFractional == false ? segLength >= 0 : segLength <= 0 );

//      // Cast to a private interface that allows the length to be set without
//      // creating a transaction or an event
//      // (After all, this is a transaction handler, and it fires an event)
//      CSegment* pSegment = dynamic_cast<CSegment*>(segment.p);
//      pSegment->SetLength(segLength);
      segment->put_Length(segLength);
   }

   m_bFractional = bFractional;
}
