///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2023  Washington State Department of Transportation
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

// DistributionFactors.cpp : Implementation of CDistributionFactors
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "DistributionFactors.h"
#include "LBAM.hh"
#include "FilteredDfSegmentCollection.h"
#include "DistributionFactorSegment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Fraction of member length where a location along the member is assumed to be at a
// junction of two segments
static const Float64 SEG_TOL=1.0e-5;
/////////////////////////////////////////////////////////////////////////////
// CDistributionFactors

STDMETHODIMP CDistributionFactors::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDistributionFactors
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CDistributionFactors::FinalConstruct()
{
   HRESULT hr;
   // construct default segment
   CComObject<CDistributionFactorSegment>* pseg;
   hr = CComObject<CDistributionFactorSegment>::CreateInstance(&pseg);
   if (FAILED(hr))
      return hr;

   m_DefaultFactorSeg = pseg;

   return S_OK;
}

void CDistributionFactors::FinalRelease()
{
   // free up all of our connectionpoints on destruct
   IndexType cnt = 0;
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      OnBeforeRemove(*it, cnt++);
   }
}


STDMETHODIMP CDistributionFactors::get_IsSymmetrical(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_IsSymmetrical;
	return S_OK;
}

STDMETHODIMP CDistributionFactors::put_IsSymmetrical(VARIANT_BOOL newVal)
{
   if (newVal==m_IsSymmetrical)
      return S_OK;

   if (newVal==VARIANT_FALSE)
   {
      m_IsSymmetrical = newVal;
   }
   else
   {
      m_IsSymmetrical = VARIANT_TRUE;
   }

   Fire_OnDistributionFactorsChanged();

	return S_OK;
}


STDMETHODIMP CDistributionFactors::get_Length(Float64 superstructureLength,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 length = 0.0;

   // clone collection
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      Float64 len;
      CComPtr<IDistributionFactorSegment>& isp = it->second;

      HRESULT hr = isp->get_Length(&len);
      if (FAILED(hr))
         return hr;

      if (len<0.0)
         len = -len * superstructureLength; // fractional

      length += len;
   }

   *pVal = length;

	return S_OK;
}

STDMETHODIMP CDistributionFactors::GetFactorForLocation(Float64 location, Float64 superstructureLength, IDistributionFactor** leftLLDF, IDistributionFactor** rightLLDF)
{
   CHECK_RETOBJ(leftLLDF);
   CHECK_RETOBJ(rightLLDF);

   try
   {
      HRESULT hr;
      // can't find anything that's off of member
      Float64 local_dist;
      try
      {
         local_dist = GetFracDistance(location, superstructureLength);
      }
      catch(FracRes&)
      {
         THROW_LBAM(LOCATION_OOR);
      }

      location = local_dist;

      // can't find segment if there are none
      IndexType size;
      hr = this->get_Count(&size);

      if (size == 0)
      {
         // return default df
         m_DefaultFactorSeg->put_Length(superstructureLength);
         m_DefaultFactorSeg->get_DistributionFactor(leftLLDF);
         m_DefaultFactorSeg->get_DistributionFactor(rightLLDF);
         return S_OK;
      }

      // set up for location search
      if (m_IsSymmetrical==VARIANT_TRUE)
      {
         // we will only be searching over half the length of symmetrical sections
         Float64 l2 = superstructureLength/2.0;
         if(l2 < location)
         {
            location = superstructureLength-location;
         }
      }

      Float64 seg_tol = SEG_TOL * superstructureLength;

      // search the vector for our segment
      Float64 seg_end = 0;
      iterator it( begin() );
      iterator itend( end() );
      for (; it!=itend; it++)
      {
         IDistributionFactorSegment* pseg = it->second.m_T;

         Float64 len;
         pseg->get_Length(&len);
         if (FAILED(hr))
            return hr;

         if (len<0.0)
            len = -len * superstructureLength; // fractional

         seg_end += len;

         if (location <= seg_end+seg_tol)
         {
            // we found our segment
            CComQIPtr<ILinearDistributionFactorSegment> linearSegment(pseg);
            if ( linearSegment )
            {
               linearSegment->CreateDistributionFactor(location-(seg_end-len),leftLLDF);
            }
            else
            {
               pseg->get_DistributionFactor(leftLLDF);
            }

             // now need to see if we are at a segment junction
            if (seg_end-seg_tol <= location)
            {
               // We are within tolerance - only need to check if this is the last segment
               // If this is not the last segment, assign it to right side. If it is, Right is nullptr.
               iterator it2(it);
               if ( ++it2 != this->end() )
               {
                  IDistributionFactorSegment* psegi2 = it2->second.m_T;
                  CComQIPtr<ILinearDistributionFactorSegment> linearSegment(psegi2);
                  if ( linearSegment )
                  {
                     linearSegment->CreateDistributionFactor(location-seg_end,rightLLDF);
                  }
                  else
                  {
                     psegi2->get_DistributionFactor(rightLLDF);
                  }
               }
            }

            break;
         }
      }

      if (seg_end+seg_tol < location)
      {
         // List of segments was shorter than Length.
         // Extend the last segment to the end
         IDistributionFactorSegment* pLastSegment = this->back()->second.m_T;
         CComQIPtr<ILinearDistributionFactorSegment> linearSegment(pLastSegment);
         if ( linearSegment )
         {
            linearSegment->get_EndDistributionFactor(leftLLDF);
         }
         else
         {
            pLastSegment->get_DistributionFactor(leftLLDF);
         }
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IDistributionFactors);
   }

	return S_OK;

   return S_OK;
}

STDMETHODIMP CDistributionFactors::GetSegmentForLocation(Float64 location, Float64 superstructureLength, IDistributionFactorSegment** ppLeftSegi, IDistributionFactorSegment** ppRightSegi)
{
   CHECK_RETOBJ(ppLeftSegi);
   CHECK_RETOBJ(ppRightSegi);

   *ppLeftSegi  = nullptr;
   *ppRightSegi = nullptr;

   try
   {
      HRESULT hr;
      // can't find anything that's off of member
      Float64 local_dist;
      try
      {
         local_dist = GetFracDistance(location, superstructureLength);
      }
      catch(FracRes&)
      {
         THROW_LBAM(LOCATION_OOR);
      }

      location = local_dist;

      // can't find segment if there are none
      IndexType size;
      hr = this->get_Count(&size);

      if (size==0)
      {
         // return default df
         m_DefaultFactorSeg->put_Length(superstructureLength);
         return m_DefaultFactorSeg.CopyTo(ppLeftSegi);
      }

      // set up for location search
      if (m_IsSymmetrical==VARIANT_TRUE)
      {
         // we will only be searching over half the length of symmetrical sections
         Float64 l2 = superstructureLength/2.0;
         if(location>l2)
            location = superstructureLength-location;
      }

      Float64 seg_tol = SEG_TOL * superstructureLength;

      // search the vector for our segment
      Float64 seg_end = 0;
      iterator it( begin() );
      iterator itend( end() );
      for (; it!=itend; it++)
      {
         IDistributionFactorSegment* pseg = it->second.m_T;

         Float64 len;
         pseg->get_Length(&len);
         if (FAILED(hr))
            return hr;

         if (len<0.0)
            len = -len * superstructureLength; // fractional

         seg_end += len;

         if (seg_end+seg_tol >= location)
         {
            // we found our segment - assign left side
            *ppLeftSegi = pseg;
            (*ppLeftSegi)->AddRef();

             // now need to see if we are at a segment junction
            if (location >= seg_end-seg_tol)
            {
               // We are within tolerance - only need to check if this is the last segment
               // If this is not the last segment, assign it to right side. If it is, Right is nullptr.
               iterator it2(it);
               if ( ++it2 != this->end() )
               {
                  IDistributionFactorSegment* psegi2 = it2->second.m_T;
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
         *ppLeftSegi = this->back()->second.m_T;
         (*ppLeftSegi)->AddRef();
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IDistributionFactors);
   }

	return S_OK;
}

static const Float64 TOL =1.0e-8;

STDMETHODIMP CDistributionFactors::GetMemberSegments(Float64 superstructureLength, IFilteredDfSegmentCollection **pColl)
{
   try
   {
      return GetMemberSegments(superstructureLength, m_IsSymmetrical, pColl);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IDistributionFactors);
   }

}

HRESULT CDistributionFactors::GetMemberSegments(Float64 Length, VARIANT_BOOL isSymmetrical, IFilteredDfSegmentCollection **pColl)
{
	CHECK_RETOBJ(pColl);

   if (Length<=0.0)
      return E_INVALIDARG;

   // use ComObject's create for efficiency
   CComObject<CFilteredDfSegmentCollection>* pnew_coll;
   HRESULT hr = CComObject<CFilteredDfSegmentCollection>::CreateInstance(&pnew_coll);
   if (FAILED(hr))
      return hr;

   CComPtr<IFilteredDfSegmentCollection> pholder(pnew_coll); // holder for ref cnt purposes

   // three different logic choices here: no segments, symmetrical or unsymmetrical
   IndexType size;
   hr = this->get_Count(&size);
   if (FAILED(hr))
      return hr;
   if (size==0)
   {
      // return collection with one default segment if there are no segments
      m_DefaultFactorSeg->put_Length(Length);
      pnew_coll->Add(m_DefaultFactorSeg);

      return pholder.CopyTo(pColl);
   }
   else if (isSymmetrical==VARIANT_FALSE)
   {
      // member is not symmetrical
      hr = LayoutSegments(Length, Length, pnew_coll);
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
      hr = LayoutSegments(Length2, Length, pnew_coll);
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
      CComPtr<IDistributionFactorSegment> pfirst;
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
      CComPtr<IDistributionFactorSegment> ptmp;
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
         IndexType lfcnt = cnt-1;
         do
         {
            CComPtr<IDistributionFactorSegment> plft;
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

HRESULT CDistributionFactors::LayoutSegments(Float64 layoutLength, Float64 totalLength, CFilteredDfSegmentCollection* pnew_coll)
{
   CHECK_IN(pnew_coll);

   HRESULT hr;
   Float64 len=0.0;
   Float64 prevlen=0.0;
   iterator it(this->begin());
   iterator itend(this->end());
   for (; it!=itend; it++)
   {
      IDistributionFactorSegment* pseg = it->second.m_T;

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
         CComPtr<IDistributionFactorSegment> ptmp;
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

      CComPtr<IDistributionFactorSegment> pseg;
      hr = pnew_coll->get_Item(cnt-1,&pseg);
      if (FAILED(hr))
         return hr;

      // we don't know if this is a unique segment or a reference - hence
      // we must make a clone and replace it with the clone
      CComPtr<IDistributionFactorSegment> ptmp;
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

STDMETHODIMP CDistributionFactors::OnDistributionFactorSegmentChanged()
{
   Fire_OnDistributionFactorsChanged();

	return S_OK;
}

STDMETHODIMP CDistributionFactors::Clone(/*[out,retval]*/IDistributionFactors** pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new  collection and fill it up
   CComObject<CDistributionFactors>* pnew;
   HRESULT hr = CComObject<CDistributionFactors>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IDistributionFactors> spisms(pnew);

   // clone properties
   pnew->m_IsSymmetrical = m_IsSymmetrical;

   // clone collection
   iterator it( begin() );
   iterator itend( end() );
   for (; it != itend; it++)
   {
      CComPtr<IDistributionFactorSegment> isp;
      
      // deep clone
      hr = it->second.m_T->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection points
      hr = spisms->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   return spisms.CopyTo(pColl);
}
