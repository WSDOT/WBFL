///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2024  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// Segments.cpp : Implementation of CSegments
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "LBAM.hh"
#include "Segments.h"
#include "SegmentItem.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Fraction of member length where a location along the member is assumed to be at a
// junction of two segments
static const Float64 SEG_TOL=1.0e-5;

/////////////////////////////////////////////////////////////////////////////
// CSegments
CSegments::~CSegments()
{
   Clear();
}

HRESULT CSegments::Copy(CSegments* pcopy)
{
   // clear out copy
   pcopy->Clear();

   HRESULT hr;
   // iterate over all items and clone them
   for (ContainerIteratorType it = m_Segments.begin(); it!=m_Segments.end(); it++)
   {
      CComBSTR stg = it->first;
      VectorType& rvec= it->second;
      for(VectorIteratorType itv=rvec.begin(); itv!=rvec.end(); itv++)
      {
         // get our segment and clone it
         CComPtr<ISegmentItem> psegi(itv->second.m_T);
         CComPtr<ISegment> pis;
         hr = psegi->get_Segment(&pis);
         if (FAILED(hr))
            return hr;

         CComPtr<ISegment> psegclone;
         hr = pis->Clone(&psegclone);
         if (FAILED(hr))
            return hr;

         hr = pcopy->Add(stg, psegclone);
         if (FAILED(hr))
            return hr;
      }
   }

   return S_OK;
}

HRESULT CSegments::get_Length(BSTR bstage, Float64 Length, Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   VectorType* pvec = this->GetVector(bstage);
   if (pvec!=0)
   {
      Float64 length = 0;

      HRESULT hr;
      for (VectorIteratorType it=pvec->begin(); it!=pvec->end(); it++)
      {
         CComPtr<ISegment> psegi;
         hr = it->second.m_T->get_Segment(&psegi);
         if (FAILED(hr))
            return hr;

         Float64 len;
         psegi->get_Length(&len);
         if (FAILED(hr))
            return hr;

         if (len<0.0)
            len = -len * Length; // fractional

         length += len;
      }

      *pVal = length;
   }
   else
   {
      *pVal = 0.0; // no segments for this stage
   }

	return S_OK;
}


HRESULT CSegments::get_Count(BSTR stage, SegmentIndexType *pVal)
{
   CHECK_IN(stage);
   CHECK_RETVAL(pVal);

   VectorType* pvec = this->GetVector(stage);

   if (pvec!=0)
   {
      *pVal = pvec->size();
   }
   else
   {
      *pVal = 0;
   }

	return S_OK;
}

HRESULT CSegments::get_Segment(BSTR bstage, SegmentIndexType relPosition, ISegment **pSeg)
{
   CHECK_IN(bstage);
   CHECK_RETOBJ(pSeg);

   VectorType* pvec = this->GetVector(bstage);

   if (pvec!=0)
   {
      if (relPosition < 0 || (SegmentIndexType)pvec->size() <= relPosition)
         return E_INVALIDARG;

      return pvec->at(relPosition).second.m_T->get_Segment(pSeg);
   }
   else
   {
      *pSeg = 0;
      return S_OK;
   }
}

HRESULT CSegments::put_Segment(BSTR bstage, SegmentIndexType relPosition, ISegment *newVal)
{
   CHECK_IN(bstage);
   CHECK_IN(newVal);

   VectorType* pvec = this->GetVector(bstage);

   if (pvec != 0)
   {
      if (relPosition < 0 || (SegmentIndexType)pvec->size() <= relPosition)
        return E_INVALIDARG;

      // we control what we own
      CComPtr<ISegmentItem> pisegi = pvec->at(relPosition).second.m_T;
      CSegmentItem* psegi = dynamic_cast<CSegmentItem*>(pisegi.p);
      if (psegi==nullptr)
      {
         ATLASSERT(false);
         return E_FAIL;
      }

      HRESULT hr = psegi->PutSegment(newVal);
      if (FAILED(hr))
         return hr;

      m_pOwner->OnSegmentsChanged(this, bstage, cgtStiffness);
   }
   else
   {
      // no segments yet for this stage - add it if position is first
      if (relPosition==0)
      {
         return Add(bstage, newVal);
      }
      else
      {
         CComBSTR msg = CreateErrorMsg1S(IDS_E_NO_SEGMENTS_FOR_STAGE, bstage);
         THROW_MSG(msg, LBAM_E_NO_SEGMENTS_FOR_STAGE, IDH_E_NO_SEGMENTS_FOR_STAGE);
      }
   }

   return S_OK;
}

HRESULT CSegments::Add(BSTR bstage, ISegment * pSeg)
{
   CHECK_IN(bstage);
   CHECK_IN(pSeg);

   CComBSTR stage(bstage);
   if (!stage || stage.Length()==0)
      return E_INVALIDARG;

   // this function uses Insert to do real work. Here we just need to determine
   // if we have a vector set up for our stage. If not, we just Insert at zero.
   SegmentIndexType size = 0;

   ContainerIteratorType it = m_Segments.find(stage);
   if (it != m_Segments.end())
   {
      // data exists for this stage - determine size
      VectorType& vec = it->second;
      size = vec.size();
   }

   return Insert(size, bstage, pSeg);
}

HRESULT CSegments::Insert(SegmentIndexType relPosition, BSTR bstage, ISegment *pSeg)
{
   HRESULT hr;
   CHECK_IN(bstage);
   CHECK_IN(pSeg);

   CComBSTR stage(bstage);
   if (!stage || stage.Length()==0)
      return E_INVALIDARG;

   ContainerIteratorType it = m_Segments.find(stage);
   if (it == m_Segments.end())
   {
      // Don't have this stage yet, we need to create it.
      // But only if this is the first - we don't allow collections with holes
      if (relPosition == 0)
      {
         std::pair <ContainerIteratorType, bool> res;
         res = m_Segments.insert( ContainerType::value_type( stage, VectorType() ));
         if (!res.second)
         {
            ATLASSERT(false); // insert failed - this should never happen
            return E_FAIL;
         }
         it = res.first;
      }
      else
      {
         // should be first item for new stage but relPosition!=0
         return E_INVALIDARG;
      }
   }

   // have a valid vector
   VectorType& vec = it->second;

   // make sure our new data will fit
   SegmentIndexType cnt = vec.size();
   if (relPosition<0 || relPosition>cnt)
      return E_INVALIDARG;

   // create and initilize our new segmentitem
   CComObject<CSegmentItem>* psegitem;
   hr = CComObject<CSegmentItem>::CreateInstance(&psegitem);

   CComPtr<ISegmentItem> pholder(psegitem); // memory leak avoidance

   psegitem->m_Stage = bstage;
   hr = psegitem->PutSegment(pSeg);
   if (FAILED(hr))
      return hr;

   // have owner set up event handling
   DWORD cookie;
   hr = m_pOwner->SetUpConnection(psegitem, &cookie);
   if (FAILED(hr))
      return hr;

   VectorIteratorType itv = vec.begin();
   itv += relPosition;
   vec.insert(itv, VectorType::value_type(cookie, ValueType(pholder)));

   // update relative positions
   UpdateRelPositions(&vec);

   m_pOwner->OnSegmentsChanged(this, bstage, cgtStiffness);

	return S_OK;
}

HRESULT CSegments::MoveTo(BSTR bstage, SegmentIndexType fromIndex, SegmentIndexType toIndex)
{
   CHECK_IN(bstage);

   // get vector for this stage
   VectorType* pvec = this->GetVector(bstage);

   if (pvec==0)
   {
      CComBSTR msg = CreateErrorMsg1S(IDS_E_NO_SEGMENTS_FOR_STAGE, bstage);
      THROW_MSG(msg, LBAM_E_NO_SEGMENTS_FOR_STAGE, IDH_E_NO_SEGMENTS_FOR_STAGE);
   }

   // check bounds
   SegmentIndexType ub = pvec->size()-1;
   if ((fromIndex <0 || fromIndex>ub) || (toIndex <0 || toIndex>ub))
      return E_INVALIDARG;

   // do nothing if from==to
   if (fromIndex == toIndex)
      return S_OK;

   // make temporary copy
   StoredType store( (*pvec)[fromIndex] );

   // erase by index
   VectorIteratorType it = pvec->begin();
   it += fromIndex;

   pvec->erase(it);

   // insert by index
   it = pvec->begin();
   it += toIndex;

   pvec->insert(it, store);

   UpdateRelPositions(pvec);

   m_pOwner->OnSegmentsChanged(this, bstage, cgtStiffness);

   return S_OK;

}

HRESULT CSegments::CopyTo(BSTR bstage, SegmentIndexType fromIndex, SegmentIndexType toIndex)
{
   CHECK_IN(bstage);

   // get vector for this stage
   VectorType* pvec = this->GetVector(bstage);
   if (pvec==0)
   {
      CComBSTR msg = CreateErrorMsg1S(IDS_E_NO_SEGMENTS_FOR_STAGE, bstage);
      THROW_MSG(msg, LBAM_E_NO_SEGMENTS_FOR_STAGE, IDH_E_NO_SEGMENTS_FOR_STAGE);
   }

   SegmentIndexType ub = pvec->size()-1;
   if ((fromIndex <0 || fromIndex>ub) || (toIndex <0 || toIndex>ub+1))
      return E_INVALIDARG;

   // get the segment
   CComPtr<ISegment> psegi;
   HRESULT hr = pvec->at(fromIndex).second.m_T->get_Segment(&psegi);
   if (FAILED(hr))
      return hr;

   return Insert(toIndex, bstage, psegi);
}

HRESULT CSegments::Remove(BSTR bstage, SegmentIndexType index)
{
   CHECK_IN(bstage);

   CComBSTR stage(bstage);
   if (!stage || stage.Length()==0)
      return E_INVALIDARG;

   ContainerIteratorType it = m_Segments.find(stage);
   if (it != m_Segments.end())
   {
      // get vector for this stage
      VectorType& rvec = it->second;

      if (index < 0 || rvec.size() <= index)
         return E_INVALIDARG;

      // erase by index
      VectorIteratorType itv = rvec.begin();
      itv += index;

      // break connection points first
      m_pOwner->BreakConnection(itv->second.m_T, itv->first);

      rvec.erase(itv);

      // if this was the last member of the vector, we need to erase this stage
      if (rvec.size()==0)
      {
         m_Segments.erase(it);
      }

      // reindex SegmentItems
      UpdateRelPositions(&rvec);
   }
   else
   {
      return E_INVALIDARG;
   }

   m_pOwner->OnSegmentsChanged(this, bstage, cgtStiffness);

	return S_OK;
}

HRESULT CSegments::Reverse(BSTR bstage)
{
   CHECK_IN(bstage);

   // get vector for this stage
   VectorType* pvec = this->GetVector(bstage);
   if (pvec==0)
   {
      CComBSTR msg = CreateErrorMsg1S(IDS_E_NO_SEGMENTS_FOR_STAGE, bstage);
      THROW_MSG(msg, LBAM_E_NO_SEGMENTS_FOR_STAGE, IDH_E_NO_SEGMENTS_FOR_STAGE);
   }

   if (pvec->size()<2)
      return S_OK;

   std::reverse(pvec->begin(), pvec->end());

   UpdateRelPositions(pvec);

   m_pOwner->OnSegmentsChanged(this, bstage, cgtStiffness);

   return S_OK;
}

HRESULT CSegments::GetSegmentForMemberLocation(BSTR bstage, Float64 Length, VARIANT_BOOL isSymmetrical, Float64 location, ISegmentItem** ppLeftSegi, ISegmentItem** ppRightSegi)
{
   CHECK_IN(bstage);
   CHECK_RETOBJ(ppLeftSegi);
   CHECK_RETOBJ(ppRightSegi);

   *ppLeftSegi  = nullptr;
   *ppRightSegi = nullptr;

   // can't find anything that's off of member
   Float64 local_dist;
   try
   {
      local_dist = GetFracDistance(location, Length);
   }
   catch(FracRes&)
   {
      THROW_LBAM(LOCATION_OOR);
   }

   location = local_dist;

   // get vector for this stage
   VectorType* pvec = this->GetVector(bstage);

   // can't find segment if there are none
   if (pvec==0 || pvec->size()==0)
   {
      return S_OK;
   }

   // set up for location search
   if (isSymmetrical==VARIANT_TRUE)
   {
      // we will only be searching over half the length of symmetrical sections
      Float64 l2 = Length/2.0;
      if(location>l2)
         location = Length-location;
   }

   Float64 seg_tol = SEG_TOL * Length;

   // search the vector for our segment
   HRESULT hr;
   Float64 seg_end = 0;
   for (VectorIteratorType it=pvec->begin(); it!=pvec->end(); it++)
   {

      CComPtr<ISegment> pseg;
      ISegmentItem* psegi = it->second.m_T;
      hr = psegi->get_Segment(&pseg);
      if (FAILED(hr))
         return hr;

      Float64 len;
      pseg->get_Length(&len);
      if (FAILED(hr))
         return hr;

      if (len<0.0)
         len = -len * Length; // fractional

      seg_end += len;

      if (seg_end+seg_tol >= location)
      {
         // we found our segment - assign left side
         *ppLeftSegi = psegi;
         (*ppLeftSegi)->AddRef();

          // now need to see if we are at a segment junction
         if (location >= seg_end-seg_tol)
         {
            // We are within tolerance - only need to check if this is the last segment
            // If this is not the last segment, assign it to right side. If it is, Right is nullptr.
            VectorIteratorType it2 = it;
            if ( ++it2 != pvec->end() )
            {
               ISegmentItem* psegi2 = it2->second.m_T;
               *ppRightSegi = psegi2;
               (*ppRightSegi)->AddRef();
            }
         }

         break;
      }
   }

   if (seg_end+seg_tol<location)
   {
      // List of segments was shorter than Length.
      // Extend the last segment to the end
      ISegmentItem* psegi = pvec->back().second.m_T;

      *ppLeftSegi = psegi;
      (*ppLeftSegi)->AddRef();
   }

	return S_OK;
}


HRESULT CSegments::GetSegmentsForStage(BSTR bstage, IFilteredSegmentCollection ** pcoll )
{
   CHECK_IN(bstage);
	CHECK_RETOBJ(pcoll);

   VectorType* pvec = this->GetVector(bstage);

   CComObject<CFilteredSegmentCollection>* pnew;
   HRESULT hr = CComObject<CFilteredSegmentCollection>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IFilteredSegmentCollection> pholder(pnew); // memory leak prot

   pnew->AddRef(); // for client
   *pcoll = pnew;

   if (pvec==0)
   {
      return S_OK;
   }

   // add segment items to temporary container
   for (VectorIteratorType it=pvec->begin(); it!=pvec->end(); it++)
   {
      ISegmentItem* psegi = it->second.m_T;
      CComPtr<ISegment> pseg;
      hr = psegi->get_Segment(&pseg);
      if (FAILED(hr))
         return hr;

      hr = pnew->Add(pseg);
      if (FAILED(hr))
         return hr;
   }   

	return S_OK;
}

static const Float64 TOL =1.0e-8;

HRESULT CSegments::GetMemberSegments(BSTR bstage, Float64 Length, VARIANT_BOOL isSymmetrical, IFilteredSegmentCollection **pColl)
{
   CHECK_IN(bstage);
	CHECK_RETOBJ(pColl);

   if (Length<=0.0)
      return E_INVALIDARG;

   VectorType* pvec = this->GetVector(bstage);

   // use ComObject's create for efficiency
   CComObject<CFilteredSegmentCollection>* pnew_coll;
   HRESULT hr = CComObject<CFilteredSegmentCollection>::CreateInstance(&pnew_coll);
   if (FAILED(hr))
      return hr;

   CComPtr<IFilteredSegmentCollection> pholder(pnew_coll); // holder for ref cnt purposes

   // three different logic choices here: no segments, symmetrical or unsymmetrical
   if (pvec==0 || pvec->size()==0)
   {
      // return empty collection if there are no segments
      *pColl = pnew_coll;
      (*pColl)->AddRef(); // for client
      return S_OK;
   }
   else if (isSymmetrical==VARIANT_FALSE)
   {
      // member is not symmetrical
      hr = LayoutSegments(Length, Length, pvec, pnew_coll);
      if (FAILED(hr))
         return hr;

      *pColl = pnew_coll;
      (*pColl)->AddRef(); // for client
   }
   else
   {
      // member is symmetrical
      Float64 Length2 = Length/2.0;

      //  build the left half by calling for a non-symmetrical section
      hr = LayoutSegments(Length2, Length, pvec, pnew_coll);
      if (FAILED(hr))
         return hr;

      SegmentIndexType cnt;
      hr = pnew_coll->get_Count(&cnt);
      if (FAILED(hr))
         return hr;

      if (cnt<1)
         return S_OK; // no segments

      // now let's fill in the right end
      // we know that the last segment must be extended to make it symmetrical
      CComPtr<ISegment> pfirst;
      hr = pnew_coll->get_Item(cnt-1, &pfirst);
      if (FAILED(hr))
         return hr;

      Float64 l1;
      hr = pfirst->get_Length(&l1);
      if (FAILED(hr))
         return hr;

      if (l1<0.0)
         l1 = -l1 * Length; // fractional

      l1 *= 2.0;

      // We must clone it to make sure it is unique 
      CComPtr<ISegment> ptmp;
      hr = pfirst->Clone(&ptmp);
      if (FAILED(hr))
         return hr;

      hr = ptmp->put_Length(l1);
      if (FAILED(hr))
         return hr;

      hr = pnew_coll->Remove(cnt-1);
      if (FAILED(hr))
         return hr;

      hr = pnew_coll->Insert(cnt-1,ptmp);
      if (FAILED(hr))
         return hr;

      // now let's fill in the rest by copying from the left side to the right
      if ( 2 <= cnt )
      {
         SegmentIndexType lfcnt = cnt-1;
         do
         {
            CComPtr<ISegment> plft;
            hr = pnew_coll->get_Item(lfcnt-1, &plft);
            if (FAILED(hr))
               return hr;

            hr = pnew_coll->Add(plft);
            if (FAILED(hr))
               return hr;

            lfcnt--;
         } while (lfcnt > 0);
      }

      *pColl = pnew_coll;
      (*pColl)->AddRef(); // for client
   }

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;

void CSegments::Load(IStructuredLoad2 * pload)
{
   CHRException hr;

   hr = pload->BeginUnit(CComBSTR("Segments"));

   Float64 ver;
   hr = pload->get_Version(&ver);

   if (ver!=MY_VER)
      hr = STRLOAD_E_BADVERSION;

   {
      _variant_t var;
      hr = pload->get_Property(_bstr_t("StageCount"),&var);

      long stage_count = var;
      var.Clear();
      for (long istg = 0; istg<stage_count; istg++)
      {
         hr = pload->BeginUnit(CComBSTR("StageData"));

         hr = pload->get_Property(_bstr_t("StageName"),&var);

         _bstr_t stage_name(var);
         var.Clear();

         hr = pload->get_Property(_bstr_t("SegmentCount"),&var);

         long segment_count = var;
         var.Clear();
         for (long iseg = 0; iseg<segment_count; iseg++)
         {
            hr = pload->get_Property(_bstr_t("Segment"),&var);

            // get variant into more convenient form
            CComPtr<ISegment> pics;
            if ( FAILED(_CopyVariantToInterface<ISegment>::copy(&pics, &var)))
               hr = STRLOAD_E_INVALIDFORMAT;

            var.Clear();

            hr = Add(stage_name, pics);
         }

         VARIANT_BOOL eb;
         hr = pload->EndUnit(&eb);
      }
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);

   if (eb!=VARIANT_TRUE)
      hr = STRLOAD_E_INVALIDFORMAT;
}


void CSegments::Save(IStructuredSave2 * psave)
{
   CHRException hr;
   hr = psave->BeginUnit(CComBSTR("Segments"), MY_VER);
   hr = psave->put_Property(CComBSTR("StageCount"),_variant_t(m_Segments.size()));
   for (ContainerIteratorType it = m_Segments.begin(); it!=m_Segments.end(); it++)
   {
      hr = psave->BeginUnit(CComBSTR("StageData"), MY_VER);
      hr = psave->put_Property(CComBSTR("StageName"),_variant_t(it->first));

      VectorType& rvec= it->second;

      hr = psave->put_Property(CComBSTR("SegmentCount"),_variant_t(rvec.size()));

      for(VectorIteratorType itv=rvec.begin(); itv!=rvec.end(); itv++)
      {
         // write segments
         ISegmentItem* psegi = itv->second.m_T;
         CComPtr<ISegment> pseg;
         hr = psegi->get_Segment(&pseg);

         hr = psave->put_Property(CComBSTR("Segment"),_variant_t(pseg));
      }

      hr = psave->EndUnit();
   }

   hr = psave->EndUnit();
}

void CSegments::Clear()
{
   // iterate through all segments and break connections
   for (ContainerIteratorType it = m_Segments.begin(); it!=m_Segments.end(); it++)
   {
      VectorType& rvec= it->second;
      for(VectorIteratorType itv=rvec.begin(); itv!=rvec.end(); itv++)
      {
         m_pOwner->BreakConnection(itv->second.m_T, itv->first);
      }
   }

   m_Segments.clear();
}


HRESULT CSegments::RemoveStage(BSTR bstage)
{
   CHECK_IN(bstage);
   try
   {
      CComBSTR stage(bstage);
      if (!stage || stage.Length()==0)
      {
         throw 1;
      }

      ContainerIteratorType it = m_Segments.find(stage);
      if (it != m_Segments.end())
      {
         VectorType& rvec = it->second;

         // erase all 
         for (VectorIteratorType itv=rvec.begin(); itv!= rvec.end(); itv++)
         {
            // break connection points first
            m_pOwner->BreakConnection(itv->second.m_T, itv->first);

         }

         // erase stage
         m_Segments.erase(it);
      }
   }
   catch(...)
   {
      CComBSTR msg = CreateErrorMsg1S(IDS_E_NO_SEGMENTS_FOR_STAGE, bstage);
      THROW_MSG(msg, LBAM_E_NO_SEGMENTS_FOR_STAGE, IDH_E_NO_SEGMENTS_FOR_STAGE);
   }

   return S_OK;
}


// private
CSegments::VectorType* CSegments::GetVector(BSTR bstage)
{
   CComBSTR stage(bstage);
   if (!stage || stage.Length()==0)
   {
      THROW_LBAM(BLANK_NAMES_NOT_ALLOWED);
   }

   ContainerIteratorType it = m_Segments.find(stage);
   if (it != m_Segments.end())
   {
      // data exists for this stage
      return &(it->second);
   }
   else
   {
      // not found
      return nullptr;
   }
}

void CSegments::UpdateRelPositions(CSegments::VectorType* pvec)
{
   SegmentIndexType i = 0;
   for(VectorIteratorType itv=pvec->begin(); itv!=pvec->end(); itv++)
   {
      // have to cast stored item to get access to put method
      CSegmentItem* psegi = static_cast<CSegmentItem*>(itv->second.m_T.p);
      if (psegi==nullptr)
      {
         ATLASSERT(false); // should never happen since we are eating our own dog food here
      }

      psegi->m_RelPosition = i;
      i++;
   }
}

HRESULT CSegments::LayoutSegments(Float64 layoutLength, Float64 totalLength, VectorType* pvec, CFilteredSegmentCollection* pnew_coll)
{
   HRESULT hr;
   Float64 len=0.0;
   Float64 prevlen=0.0;
   for (VectorIteratorType it=pvec->begin(); it!=pvec->end(); it++)
   {
      ISegmentItem* psegi = it->second.m_T;
      CComPtr<ISegment> pseg;
      hr = psegi->get_Segment(&pseg);
      if (FAILED(hr))
      {
         ATLASSERT(false); // should never happen
         return hr;
      }

      Float64 seglen;
      hr = pseg->get_Length(&seglen);

      if (seglen<0.0)
         seglen = -seglen * totalLength; // fractional

      prevlen = layoutLength - len; // distance to go from start of this 
                                    // segment to end
      len += seglen;

      if (len == layoutLength || len+TOL <= layoutLength)
      {
         // just add segment to our list
         hr = pnew_coll->Add(pseg);
         if (FAILED(hr))
            return hr;

         if (len == layoutLength)
            break; // we're done
      }
      else 
      {
         // we hit the end of the road and the length of the segments is greater
         // than the member length - we'll need to make a custom segment just
         // for the final segment.
         CComPtr<ISegment> ptmp;
         hr = pseg->Clone(&ptmp);
         if (FAILED(hr))
            return hr;

         hr = ptmp->put_Length(prevlen);
         if (FAILED(hr))
            return hr;

         hr = pnew_coll->Add(ptmp);
         if (FAILED(hr))
            return hr;

         break; // we're done
      }
   }

   // we've finished through the sections, now let's see if the length of the 
   // sections filled the member. If not, we need to extend the length of the
   // last segment to fill it
   if (len<layoutLength)
   {
      SegmentIndexType cnt;
      hr = pnew_coll->get_Count(&cnt);

      CComPtr<ISegment> pseg;
      hr = pnew_coll->get_Item(cnt-1,&pseg);
      if (FAILED(hr))
         return hr;

      // we don't know if this is a unique segment or a reference - hence
      // we must make a clone and replace it with the clone
      CComPtr<ISegment> ptmp;
      hr = pseg->Clone(&ptmp);
      if (FAILED(hr))
         return hr;

      hr = ptmp->put_Length(prevlen);
      if (FAILED(hr))
         return hr;

      hr = pnew_coll->Remove(cnt-1);
      if (FAILED(hr))
         return hr;

      hr = pnew_coll->Insert(cnt-1,ptmp);
      if (FAILED(hr))
         return hr;
   }

   return S_OK;
}