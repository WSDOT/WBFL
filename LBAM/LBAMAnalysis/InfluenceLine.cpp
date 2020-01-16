///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2020  Washington State Department of Transportation
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

// InfluenceLine.cpp : Implementation of CInfluenceLine
#include "stdafx.h"
#include "WBFLLBAMAnalysis.h"
#include "LBAMAnalysis.hh"
#include "AnalysisUtils.h"
#include "InfluenceLine.h"

#include <algorithm>
#include "Interpolate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Float64 CInfluenceLine::ms_LocationTolerance = 1e-6;

/////////////////////////////////////////////////////////////////////////////
// CInfluenceLine

STDMETHODIMP CInfluenceLine::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IInfluenceLine
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CInfluenceLine::get_Location(Float64* location)
{
   CHECK_RETVAL(location);
   *location = m_GlobalX;
   return S_OK;
}

STDMETHODIMP CInfluenceLine::get_POI(PoiIDType* poi)
{
   CHECK_RETVAL(poi);
   *poi = m_idPOI;
   return S_OK;
}

STDMETHODIMP CInfluenceLine::Item(/*[in]*/CollectionIndexType idx, /*[in]*/InfluenceSideType side, /*[out]*/ Float64* value, /*[out]*/InfluenceLocationType* locationType, /*[out]*/Float64* location)
{
   CHECK_RETVAL(value);
   CHECK_RETVAL(location);
   CHECK_RETVAL(locationType);

   try
   {
      Compute(side);

      InfluencePointContainer& container = GetContainer(side);

      if ( 0 <= idx && idx < container.size() )
      {
         const InflPoint& pnt = container[idx];
         *value = pnt.m_Value;
         *location = pnt.m_Location;
         *locationType = pnt.m_LocationType;
      }
      else
      {
         ATLASSERT(false);
         return E_INVALIDARG;
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return S_OK;
}

STDMETHODIMP CInfluenceLine::get_Count( InfluenceSideType side, CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);

   try
   {
      Compute(side);

      InfluencePointContainer& container = GetContainer(side);

      *pVal = container.size();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return S_OK;
}

STDMETHODIMP CInfluenceLine::Add(InfluenceLocationType locationType, Float64 location, Float64 value)
{
   try
   {
      // data is no good now
      Invalidate();

      InfluencePointContainer& container = GetContainer(ilsBoth);

      container.emplace_back(value,location,locationType);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return S_OK;
}

STDMETHODIMP CInfluenceLine::Remove(/*[in]*/CollectionIndexType idx)
{
   try
   {
      InfluencePointContainer& container = GetContainer(ilsBoth);

      if ( 0 <= idx && idx < container.size() )
      {
         InfluencePointIterator it( container.begin() );
         it += idx;
         container.erase(it);

         Invalidate();
      }
      else
      {
         ATLASSERT(false);
         return E_INVALIDARG;
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return S_OK;
}

STDMETHODIMP CInfluenceLine::Clear()
{
   InfluencePointContainer& container = GetContainer(ilsBoth);

   container.clear();

   Invalidate();

   return S_OK;
}

STDMETHODIMP CInfluenceLine::Bounds(/*[out]*/Float64* start, Float64* end)
{
   CHECK_RETVAL(start);
   CHECK_RETVAL(end);

   try
   {
      Compute(ilsBoth);

      *start = m_StartBound;
      *end = m_EndBound;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return S_OK;
}

STDMETHODIMP CInfluenceLine::FindMaxValue(Float64 start,Float64 end,Float64* pLocation,Float64* pValue)
{
   CHECK_RETVAL(pLocation);
   CHECK_RETVAL(pValue);

   if ( start < m_StartBound || m_EndBound < end )
      return E_INVALIDARG;

   Float64 maxVal   = 0;
   Float64 location = -1;
   try
   {
      Compute(ilsBoth);
      InfluencePointContainer& container = GetContainer(ilsBoth);

      // guess at the starting index
      CollectionIndexType startIdx = CollectionIndexType(container.size()*start/(m_EndBound - m_StartBound) - 1);
      startIdx = ForceIntoRange<CollectionIndexType>(0,startIdx,container.size()-1);
      while ( start < container[startIdx].m_Location )
      {
         if ( startIdx == 0 )
            break;

         startIdx--; // back up until start is before location
      }


      InfluencePointIterator iter(container.begin() + startIdx);
      InfluencePointIterator iterend( container.end() );
      for (; iter != iterend; iter++ )
      {
         InflPoint& inflPoint = *iter;
         if ( (start <= inflPoint.m_Location && inflPoint.m_Location <= end) && // in range
              (maxVal < inflPoint.m_Value) ) // and a new max value
         {
            maxVal = inflPoint.m_Value;
            location = inflPoint.m_Location;
         }

         if ( end < inflPoint.m_Location )
            break; // we are not out of range
      }

      *pValue    = maxVal;
      *pLocation = location;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return ( location < 0 ? E_FAIL : S_OK);
}

STDMETHODIMP CInfluenceLine::FindMinValue(Float64 start,Float64 end,Float64* pLocation,Float64* pValue)
{
   CHECK_RETVAL(pLocation);
   CHECK_RETVAL(pValue);

   if ( start < m_StartBound || m_EndBound < end )
      return E_INVALIDARG;

   Float64 minVal   = 0;
   Float64 location = -1;
   try
   {
      Compute(ilsBoth);
      InfluencePointContainer& container = GetContainer(ilsBoth);

      // guess at the starting index
      long startIdx = long(container.size()*start/(m_EndBound - m_StartBound) - 1);
      startIdx = ForceIntoRange(0L,startIdx,long(container.size()-1));
      while ( start < container[startIdx].m_Location )
      {
         if ( startIdx == 0 )
            break;

         startIdx--; // back up until start is before location
      }


      InfluencePointIterator iter( container.begin() + startIdx );
      InfluencePointIterator iterend( container.end() );
      for (; iter != iterend; iter++ )
      {
         InflPoint& inflPoint = *iter;
         if ( (start <= inflPoint.m_Location && inflPoint.m_Location <= end) && // in range
              (inflPoint.m_Value < minVal) ) // and a new min value
         {
            minVal = inflPoint.m_Value;
            location = inflPoint.m_Location;
         }

         if ( end < inflPoint.m_Location )
            break; // we are not out of range
      }

      *pValue    = minVal;
      *pLocation = location;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return ( location < 0 ? E_FAIL : S_OK);
}

STDMETHODIMP CInfluenceLine::Evaluate(Float64 location, InfluenceSideType side, VARIANT_BOOL* isDualValue, 
                                      Float64* leftValue, Float64* rightValue)
{
   CHECK_RETVAL(isDualValue);
   CHECK_RETVAL(leftValue);
   CHECK_RETVAL(rightValue);

   *isDualValue = VARIANT_FALSE; // assume single valued
   *leftValue   = 0.0;
   *rightValue  = 0.0;

   try
   {
      Compute(side);

      if (location<m_StartBound || location>m_EndBound)
      {
         // Location is out of bounds of influence line. No response.
         return S_OK;
      }

      // get right influence line for side
      InfluencePointContainer& container = GetContainer(side);

      // use index used in last call as a guess for this one - not very high tech, but effective
      const InflPoint& first_gs = container[ m_LastFound[side] ];

      // Use of tolerance allows points very near dual-value points to nail the location
      if (::IsLT(location,first_gs.m_Location,ms_LocationTolerance) )
      {
         // look backward
         for(CollectionIndexType i = m_LastFound[side]-1; i >= 0; i--)
         {
            const InflPoint& curr = container[i];
            if (curr.m_Location <= location)
            {
               // we're in the neighborhood
               if ( IsEqual(curr.m_Location,location,ms_LocationTolerance) )
               {
                  // Dead on 
                  // See if it's dual valued
                  if (curr.m_LocationType == iflDualRight)
                  {
                     ATLASSERT(i!=0);
                     const InflPoint& lft = container[i-1];
                     ATLASSERT(lft.m_LocationType==iflDualLeft);
                     ATLASSERT( IsEqual(lft.m_Location,location) );
                     *isDualValue = VARIANT_TRUE;
                     *rightValue= curr.m_Value;
                     *leftValue = lft.m_Value;
                  }
                  else
                  {
                     *leftValue = curr.m_Value;
                     *rightValue= curr.m_Value;
                  }
               }
               else
               {
                  // not dead on, so webe interpolatin
                  const InflPoint& next = container[i+1];
                  *leftValue = InterpolateTrapezoid(location, curr.m_Location, next.m_Location, curr.m_Value, next.m_Value);
                  *rightValue = *leftValue;
               }

               m_LastFound[side] = i;
               break; // done with loop
            }
         }
      }
      else if (::IsLT(first_gs.m_Location,location,ms_LocationTolerance))
      {
         // look forward
         CollectionIndexType num_pts = container.size();
         for(CollectionIndexType i=m_LastFound[side]+1; i< num_pts; i++)
         {
            const InflPoint& curr = container[i];
            if (location <= curr.m_Location)
            {
               // we're in the neighborhood
               if ( IsEqual(curr.m_Location,location,ms_LocationTolerance) )
               {
                  // Dead on - see if it's dual valued
                  if (curr.m_LocationType == iflDualLeft)
                  {
                     ATLASSERT(i!=num_pts-1);
                     const InflPoint& rgt = container[i+1];
                     //ATLASSERT(rgt.m_LocationType==iflDualRight);
                     ATLASSERT(IsEqual(rgt.m_Location,location));
                     *isDualValue = VARIANT_TRUE;
                     *rightValue= rgt.m_Value;
                     *leftValue = curr.m_Value;
                  }
                  else
                  {
                     *leftValue  = curr.m_Value;
                     *rightValue = curr.m_Value;
                  }
               }
               else
               {
                  // not dead on, so webe interpolatin
                  const InflPoint& prev = container[i-1];
                  *leftValue = InterpolateTrapezoid(location, prev.m_Location, curr.m_Location, prev.m_Value, curr.m_Value);
                  *rightValue = *leftValue;
               }

               m_LastFound[side] = i;
               break; // done with loop
            }
         }
      }
      else
      {
         // nailed it on first guess - only need to check if we are dual-valued
         if (first_gs.m_LocationType == iflDualLeft)
         {
            // go to next value
            const InflPoint& rgt = container[m_LastFound[side]+1];
            //ATLASSERT(rgt.m_LocationType==iflDualRight);
            ATLASSERT(IsEqual(rgt.m_Location,location,ms_LocationTolerance));
            *isDualValue = VARIANT_TRUE;
            *leftValue = first_gs.m_Value;
            *rightValue= rgt.m_Value;
         }
         else if (first_gs.m_LocationType == iflDualRight)
         {
            const InflPoint& lft = container[m_LastFound[side]-1];
            ATLASSERT(lft.m_LocationType==iflDualLeft);
            ATLASSERT(IsEqual(lft.m_Location,location,ms_LocationTolerance));
            *isDualValue = VARIANT_TRUE;
            *leftValue = lft.m_Value;
            *rightValue= first_gs.m_Value;
         }
         else
         {
            *leftValue  = first_gs.m_Value;
            *rightValue = first_gs.m_Value;
         }
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return S_OK;
}

HRESULT CInfluenceLine::Reserve(CollectionIndexType n)
{
   if (n<0)
   {
      ATLASSERT(false);
      return E_INVALIDARG;
   }

   try
   {
      InfluencePointContainer& container = GetContainer(ilsBoth);
      container.reserve(n);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return S_OK;
}

HRESULT CInfluenceLine::GetZeroTolerance(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_ZeroTolerance;
   return S_OK;
}

HRESULT CInfluenceLine::SetZeroTolerance(Float64 val)
{
   ATLASSERT(!m_IsComputed[ilsBoth]); // this should be called just after creation and before any accessors are called

   if(val<0.0)
      return E_INVALIDARG;

   if (val!=m_ZeroTolerance)
   {
      m_ZeroTolerance=val;
      Invalidate();
   }

   return S_OK;
}

STDMETHODIMP CInfluenceLine::Clone(IInfluenceLine* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new stress point collection and fill it up
   CComObject<CInfluenceLine>* pnew;
   HRESULT hr = CComObject<CInfluenceLine>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IInfluenceLine> spisps(pnew); // holder for reference count

   // copy data
   pnew->m_ZeroTolerance = m_ZeroTolerance;
   pnew->m_StartBound    = m_StartBound;
   pnew->m_EndBound      = m_EndBound;

   for (long i = 0; i<3; i++)
   {
      pnew->m_InfluencePoints[i] = m_InfluencePoints[i];
      pnew->m_IsComputed[i]      = m_IsComputed[i];
      pnew->m_LastFound[i]       = m_LastFound[i];
   }

   *pColl = spisps;
   (*pColl)->AddRef();

   return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CInfluenceLine::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   this->Clear();

   hr = pload->BeginUnit(CComBSTR("InfluenceLine"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {
      _variant_t var;
      hr = pload->get_Property(_bstr_t("ZeroTolerance"),&var);
      if (FAILED(hr))
         return hr;

      m_ZeroTolerance = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("Count"),&var);
      if (FAILED(hr))
         return hr;

      // only loads and saves primary influence line
      InfluencePointContainer& container = GetContainer(ilsBoth);

      long count = var;
      for (long i = 0; i<count; i++)
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("Value"),&var);
         if (FAILED(hr))
            return hr;

         Float64 value = var;

         var.Clear();
         hr = pload->get_Property(_bstr_t("Location"),&var);
         if (FAILED(hr))
            return hr;

         Float64 location = var;

         var.Clear();
         hr = pload->get_Property(_bstr_t("LocationType"),&var);
         if (FAILED(hr))
            return hr;

         long type = var;
         InfluenceLocationType loc_type;

         if (type==iflSingle)
         {
            loc_type = iflSingle;
         }
         else if (type==iflDualLeft)
         {
            loc_type = iflDualLeft;
         }
         else if (type==iflDualRight)
         {
            loc_type = iflDualRight;
         }
         else
         {
            ATLASSERT(false);
            return STRLOAD_E_INVALIDFORMAT;
         }

         container.emplace_back(value, location, loc_type);
      }

   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   Invalidate();

   return S_OK;
}

STDMETHODIMP CInfluenceLine::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("InfluenceLine"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
 
      hr = psave->put_Property(CComBSTR("ZeroTolerance"),_variant_t(m_ZeroTolerance));
      if (FAILED(hr))
         return hr;

      // only loads and saves primary influence line
      InfluencePointContainer& container = GetContainer(ilsBoth);

      CollectionIndexType count = container.size();
      hr = psave->put_Property(CComBSTR("Count"),_variant_t(count) );
      if (FAILED(hr))
         return hr;

      for (CollectionIndexType i = 0; i<count; i++)
      {
         const InflPoint& curr = container[i];

         hr = psave->put_Property(CComBSTR("Value"),_variant_t(curr.m_Value) );
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("Location"),_variant_t(curr.m_Location) );
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("LocationType"),_variant_t((long)curr.m_LocationType) );
         if (FAILED(hr))
            return hr;
      }
   }

   hr = psave->EndUnit();
   return hr;
}

void CInfluenceLine::Invalidate()
{
   m_IsComputed[0]=false;
   m_IsComputed[1]=false;
   m_IsComputed[2]=false;

   m_LastFound[0] = 0;
   m_LastFound[1] = 0;
   m_LastFound[3] = 0;

   InfluencePointContainer& negcontainer = GetContainer(ilsNegative);
   negcontainer.clear();

   InfluencePointContainer& poscontainer = GetContainer(ilsPositive);
   poscontainer.clear();
}


void CInfluenceLine::Compute(InfluenceSideType side)
{
   // process our main (ilsBoth) influence points
   ComputeMainValues();

   if (side != ilsBoth)
   {
      Flatten(side);
   }
}

void CInfluenceLine::ComputeMainValues()
{
   // This routine preens the influence line before we evaluate it. 
   // Note that lines must be in sorted order before calling

   // first check that main influence values are computed
   if(!m_IsComputed[ilsBoth])
   {
      InfluencePointContainer& container = GetContainer(ilsBoth);

#if defined(_DEBUG_LOGGING)
      ATLTRACE(_T("Trace Influence Main Values BEFORE Compute()"));
      TraceInfluenceLine(ilsBoth);
#endif

      if (container.empty())
      {
         m_StartBound = 0;
         m_EndBound = 0;
      }
      else
      {
         if (m_ProcessingType != iptRaw)
         {
            // make a temporary copy of infl points
            InfluencePointContainer temp;
            temp.assign(container.begin(), container.end());

            // zero out noise values
            if (0.0 < m_ZeroTolerance)
            {
               ZeroOutInflPoint make_zero(m_ZeroTolerance);
               std::for_each(temp.begin(), temp.end(), make_zero);
            }

            // optimize and copy back into our container
            OptimizeInfluence(temp, container);
         }

         // cache bounds
         const InflPoint& first = container.front();
         m_StartBound = first.m_Location;

         const InflPoint& last = container.back();
         m_EndBound = last.m_Location;
      }

      // no good information on last place evalulated. so let's be safe
      m_LastFound[ilsBoth] = 0;

      // compute and cache areas
      DoComputeArea();

      m_IsComputed[ilsBoth] = true;

#if defined(_DEBUG_LOGGING)
      ATLTRACE(_T("Trace Influence Main Values AFTER Compute()"));
      TraceInfluenceLine(ilsBoth);
#endif
   }
}


void CInfluenceLine::OptimizeInfluence(const InfluencePointContainer& source, InfluencePointContainer& target)
{
   // this function removes excessive locations (misfits) in the "flat spots" in an influence line

   CollectionIndexType source_size = source.size();
   if (source_size==0)
   {
      ATLASSERT(false);  // probably shouldn't see any empty influence lines here
     target.clear();
      return;
   }
   // first walk through source and identify excessive locations
   std::vector<long> misfits;

   if (2 < source_size)
   {
      ConstInfluencePointIterator it3( source.begin() );
      ConstInfluencePointIterator it1( it3++ );
      ConstInfluencePointIterator it2( it3++ );
      long misfit=1;
      bool last_was_misfit=false;
      ConstInfluencePointIterator itend( source.end() );
      while( it3!=itend )
      {
         if (IsEqual(it1->m_Value, it2->m_Value, m_ZeroTolerance) )
         {
            // if two nodes are at the same location, and have the same value, we can take the second one out,
            // provided that we didn't just take the first one out
            if (it1->m_Location == it2->m_Location && !last_was_misfit)
            {
               misfits.push_back(misfit); // index of it2
               last_was_misfit = true;
            }
            else if ( IsEqual(it2->m_Value, it3->m_Value, m_ZeroTolerance) )
            {
               // if three nodes in a row have equal values, then we can take the middle one out
               misfits.push_back(misfit); // index of it2
               last_was_misfit = true;
            }
            else
            {
               last_was_misfit = false;
            }
         }
         else
         {
            last_was_misfit = false;
         }

         it1++;
         it2++;
         it3++;
         misfit++;
      }
   }

   // next copy source data into target neglecting misfits
   CollectionIndexType mis_size = misfits.size();

#if defined(_DEBUG_LOGGING)
   ATLTRACE(_T("Misfits - %4d of them\n"), mis_size);
   for (long im = 0; im<mis_size; im++)
   {
      ATLTRACE(_T("%4d, %4d\n"), im, misfits[im]);
   }
#endif 


   if (mis_size!=0)
   {
      // need to skip on misfits
      CollectionIndexType source_size = source.size();
      ATLASSERT(source_size>mis_size);
      target.clear();
      target.reserve(source_size-mis_size);

      CollectionIndexType mfc = 0;
      CollectionIndexType i = 0;
      while(i<source_size)
      {
         if (  mfc<mis_size  && i==misfits[mfc] )
         {
            // a misfit - do nothing
            mfc++;
         }
         else
         {
            // not a misfit - add it to source
            // copy as single-valued - next pass will take care of left/right values
            target.push_back( source[i].CopySingle() );
         }
         i++;
      }
   }
   else
   {
      // just copy the whole thing
      target.assign(source.begin(), source.end());
   }

   // finally, make sure dual-values are accounted for
   CollectionIndexType target_size=target.size();
   if (target_size>2)
   {
      // See comment below from RAB
//#if defined (_DEBUG)
//      bool last_matched=false;
//      Float64 last_loc;
//#endif
      InfluencePointIterator it2( target.begin() );
      InfluencePointIterator it1( it2++ );
      InfluencePointIterator itend( target.end() );
      while( it2!=itend )
      {
         if ( IsEqual(it1->m_Location,it2->m_Location,ms_LocationTolerance) )
         {
            it1->m_LocationType = iflDualLeft;
            it2->m_LocationType = iflDualRight;
         }

// Commented out by RAB during PGSplice development. The method of virtual work is used To compute 
// deflections from the time-step analysis. The calculate the deflection at a POI, the
// moment diagram due to a unit load at that POI is needed. When the LBAM/InfluenceLine code
// condenses POIs at the same location the mapping between the POI and the influence load case is lost.
// This cause a lot of problems. Since the duplicates occur at very few POI it is easier and quicker
// to just allow the inefficiency at a couple locations then it is to a have an elaborate solution
// to a complex problem.
//         // some debug code here to check that we don't have three or more of the same location
//#if defined (_DEBUG)
//         if ( IsEqual(it1->m_Location,it2->m_Location,ms_LocationTolerance) )
//         {
//            if (last_matched)
//            {
//               ATLASSERT(false); // have three points at the same location - this is bad form and indicates an inefficient influence line
//            }
//            last_matched = true;
//            last_loc = it2->m_Location;
//         }
//         else
//         {
//            last_matched = false;
//         }
//#endif
         // loop
         it1++;
         it2++;
      }
   }
}

void CInfluenceLine::Flatten(InfluenceSideType side)
{
   if (side==ilsBoth)
   {
      ATLASSERT(false);
      return;
   }

   // this algorithm does two things - it flattens out one side of the influence line, and it
   // tries to remove duplicate values
   ATLASSERT(m_IsComputed[ilsBoth]==true); // primary results must be computed prior to calling this


   if (side==ilsNegative)
   {
      if (!m_IsComputed[ilsNegative])
      {
         InfluencePointContainer& primary_container = GetContainer(ilsBoth);
         CollectionIndexType orig_size = primary_container.size();

         if (orig_size==0)
            return;

         // put new influence points into a new container then copy to our member container
         InfluencePointContainer local_infl;
         local_infl.reserve(orig_size*12/10);  // make room for intersections

         // whack positive values
         InfluencePointIterator it2( primary_container.begin() );
         InfluencePointIterator it1(it2++ );

         // first deal with end condition
         InflPoint& p1 = *it1;

         if (p1.m_Value>0.0)
         {
            local_infl.push_back( p1.CopyAndZero() );
         }
         else 
         {
            local_infl.push_back( p1 );
         }

         // loop through and flatten
         InfluencePointIterator itend( primary_container.end() );
         while( it2 != itend )
         {
            InflPoint& p1 = *it1;
            InflPoint& p2 = *it2;

            // cases
            if (p1.m_Value>=0.0 && p2.m_Value>=0.0)
            {
               // both positive
               local_infl.push_back( p2.CopyAndZero() );
            }
            else if (p1.m_Value<=0.0 && p2.m_Value<=0.0)
            {
               // both negative
               local_infl.push_back( p2 );
            }
            else if (p1.m_Value>0.0 && p2.m_Value<0.0)
            {
               // downward intersection
               if ( IsEqual(p1.m_Location, p2.m_Location, ms_LocationTolerance) )
               {
                  // vertical drop
                  // if assert below fires, then influence line was not properly laid out
                  //ATLASSERT( p1.m_LocationType==iflDualLeft && p2.m_LocationType==iflDualRight );
                  local_infl.push_back( p2 );
               }
               else
               {
                  // not a vertical drop: need to add an intersection point
                  Float64 xloc = InterpolateZeroLocation(p1.m_Location, p2.m_Location, p1.m_Value, p2.m_Value);
                  local_infl.emplace_back(0.0, xloc, iflSingle);
                  local_infl.push_back( p2 );
               }
            }
            else
            {
               // upward intersection
               if (IsEqual(p1.m_Location, p2.m_Location, ms_LocationTolerance))
               {
                  // vertical climb
                  // if assert below fires, then influence line was not properly laid out
                  //ATLASSERT( p1.m_LocationType==iflDualLeft && p2.m_LocationType==iflDualRight );
                  local_infl.push_back( p2.CopyAndZero() );
               }
               else
               {
                  // not a vertical climb: need to add an intersection point
                  Float64 xloc = InterpolateZeroLocation(p1.m_Location, p2.m_Location, p1.m_Value, p2.m_Value);
                  local_infl.emplace_back(0.0, xloc, iflSingle);
                  local_infl.push_back( p2.CopyAndZero() );
               }
            }

            it1 = it2;
            it2++;
         }

         // optimize out duplicate points and assign flattened influence line to our local
         InfluencePointContainer& container = GetContainer(ilsNegative);

         OptimizeInfluence(local_infl, container);

         m_IsComputed[ilsNegative] = true;
      }
   }
   else if (side==ilsPositive)
   {
      if (!m_IsComputed[ilsPositive])
      {
         InfluencePointContainer& primary_container = GetContainer(ilsBoth);
         CollectionIndexType orig_size = primary_container.size();

         if (orig_size==0)
            return;

         // put new influence points into a new container then copy to our member container
         InfluencePointContainer local_infl;
         local_infl.reserve(orig_size*12/10);  // make room for intersections

         // whack negative values
         InfluencePointIterator it2( primary_container.begin() );
         InfluencePointIterator it1( it2++ );

         // first deal with end condition
         InflPoint& p1 = *it1;

         if (p1.m_Value<0.0)
         {
            local_infl.push_back( p1.CopyAndZero() );
         }
         else 
         {
            local_infl.push_back( p1 );
         }

         // loop through and flatten
         InfluencePointIterator itend( primary_container.end() );
         while( it2 != itend )
         {
            InflPoint& p1 = *it1;
            InflPoint& p2 = *it2;

            // cases
            if (p1.m_Value>=0.0 && p2.m_Value>=0.0)
            {
               // both positive
               local_infl.push_back( p2 );
            }
            else if (p1.m_Value<=0.0 && p2.m_Value<=0.0)
            {
               // both negative
               local_infl.push_back( p2.CopyAndZero() );
            }
            else if (p1.m_Value>0.0 && p2.m_Value<0.0)
            {
               // downward intersection
               if ( IsEqual(p1.m_Location, p2.m_Location, ms_LocationTolerance) )
               {
                  // vertical drop
                  // if assert below fires, then influence line was not properly laid out
                  //ATLASSERT( p1.m_LocationType==iflDualLeft && p2.m_LocationType==iflDualRight );
                  local_infl.push_back( p2.CopyAndZero() );
               }
               else
               {
                  // not a vertical drop: need to add an intersection point
                  Float64 xloc = InterpolateZeroLocation(p1.m_Location, p2.m_Location, p1.m_Value, p2.m_Value);
                  local_infl.emplace_back(0.0, xloc, iflSingle);
                  local_infl.push_back( p2.CopyAndZero() );
               }
            }
            else
            {
               // upward intersection
               if (IsEqual(p1.m_Location, p2.m_Location,ms_LocationTolerance))
               {
                  // vertical climb
                  // if assert below fires, then influence line was not properly laid out
                  //ATLASSERT( p1.m_LocationType==iflDualLeft && p2.m_LocationType==iflDualRight );
                  local_infl.push_back( p2 );
               }
               else
               {
                  // not a vertical climb: need to add an intersection point
                  Float64 xloc = InterpolateZeroLocation(p1.m_Location, p2.m_Location, p1.m_Value, p2.m_Value);
                  local_infl.emplace_back(0.0, xloc, iflSingle);
                  local_infl.push_back( p2 );
               }
            }

            it1 = it2;
            it2++;
         }

         // optimize out duplicate points and assign flattened influence line to our local
         InfluencePointContainer& container = GetContainer(ilsPositive);

         OptimizeInfluence(local_infl, container);

         m_IsComputed[ilsPositive] = true;
      }
   }
   else
   {
      ATLASSERT(false);
   }
}

#if defined(_DEBUG_LOGGING)
void CInfluenceLine::TraceInfluenceLine(InfluenceSideType side) 
{
   if (side==ilsBoth)
      ATLTRACE(_T("Trace of raw Primary Influence Values\n"));
   else if (side==ilsPositive)
      ATLTRACE(_T("Trace of raw Positive Influence Values\n"));
   else
      ATLTRACE(_T("Trace of raw Negative Influence Values\n"));


   InfluencePointContainer& container = GetContainer(side);

   long size = container.size();
   ATLTRACE(_T("Number of Influence Values = %d\n"),size);

   long i = 0;
   for (ConstInfluencePointIterator it=container.begin(); it!=container.end(); it++)
   {
      const InflPoint& ifl = *it;
      LPCTSTR side[] = {"Single","Left  ","Right "};
      ATLTRACE(_T("%4d Location Global %f, %s, Value = %f\n"), i, ifl.m_Location, side[ifl.m_LocationType], ifl.m_Value);
      i++;
   }

   ATLTRACE(_T("Trace of Influence Values - done\n"));
}
#endif

inline Float64 ComputePntArea(const CInfluenceLine::InflPoint& pnt1, const CInfluenceLine::InflPoint& pnt2, InfluenceSideType side, Float64 tolerance)
{
   ATLASSERT( IsLE(pnt1.m_Location, pnt2.m_Location) );

   if (IsEqual(pnt1.m_Location, pnt2.m_Location, tolerance) )
      return 0.0;

   if (side == ilsPositive)
   {
      if ( pnt1.m_Value>=0.0 && pnt2.m_Value>=0.0 )
      {
         return  TrapezoidArea(pnt1.m_Location, pnt2.m_Location, pnt1.m_Value, pnt2.m_Value);
      }
      else if (pnt1.m_Value>0.0)
      {
         Float64 x2 = InterpolateZeroLocation(pnt1.m_Location, pnt2.m_Location, pnt1.m_Value, pnt2.m_Value);
         return 0.5*(x2-pnt1.m_Location)*pnt1.m_Value;
      }
      else if (pnt2.m_Value>0.0)
      {
         Float64 x1 = InterpolateZeroLocation(pnt1.m_Location, pnt2.m_Location, pnt1.m_Value, pnt2.m_Value);
         return 0.5*(pnt2.m_Location-x1)*pnt2.m_Value;
      }
      else
      {
         return 0.0;
      }
   }
   else if (side == ilsNegative)
   {
      if (pnt1.m_Value<=0.0 && pnt2.m_Value<=0.0)
      {
         return  TrapezoidArea(pnt1.m_Location, pnt2.m_Location, pnt1.m_Value, pnt2.m_Value);
      }
      else if (pnt1.m_Value<0.0)
      {
         Float64 x2 = InterpolateZeroLocation(pnt1.m_Location, pnt2.m_Location, pnt1.m_Value, pnt2.m_Value);
         return 0.5*(x2-pnt1.m_Location)*pnt1.m_Value;
      }
      else if (pnt2.m_Value<0.0)
      {
         Float64 x1 = InterpolateZeroLocation(pnt1.m_Location, pnt2.m_Location, pnt1.m_Value, pnt2.m_Value);
         return 0.5*(pnt2.m_Location-x1)*pnt2.m_Value;
      }
      else
      {
         return 0.0;
      }
   }
   else
   {
      // simpson's rule
      return  TrapezoidArea(pnt1.m_Location, pnt2.m_Location, pnt1.m_Value, pnt2.m_Value);
   }
}

STDMETHODIMP CInfluenceLine::ComputeArea(InfluenceSideType side, Float64* pArea)
{
   try
   {
      // Use full influence line to compute area - might be able to optimize by using flattened line
      // if it is available. 
      Compute(ilsBoth);

      *pArea = m_Area[side];
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return S_OK;
}

void CInfluenceLine::DoComputeArea()
{
   InfluencePointContainer& container = GetContainer(ilsBoth);

   CollectionIndexType size = container.size();
   if (size<2)
   {
      m_Area[ilsBoth]     = 0.0;
      m_Area[ilsPositive] = 0.0;
      m_Area[ilsNegative] = 0.0;
   }
   else
   {
      InfluencePointIterator it2( container.begin() );
      InfluencePointIterator it1( it2++ );
      
      Float64 pos_area=0.0;
      Float64 neg_area=0.0;
      InfluencePointIterator itend( container.end() );
      while(it2!=itend)
      {
         const InflPoint& pnt1 = *it1;
         const InflPoint& pnt2 = *it2;

         pos_area += ComputePntArea(pnt1, pnt2, ilsPositive, ms_LocationTolerance);
         neg_area += ComputePntArea(pnt1, pnt2, ilsNegative, ms_LocationTolerance);

         it1 = it2++;
      }

      m_Area[ilsBoth]     = neg_area + pos_area;
      m_Area[ilsPositive] = pos_area;
      m_Area[ilsNegative] = neg_area;
   }
}

STDMETHODIMP CInfluenceLine::ComputeNonZeroRegions(InfluenceSideType side, IDblArray* *locations)
{
   CHECK_RETOBJ(locations);

   try
   {
      Compute(ilsBoth);
      InfluencePointContainer& container = GetContainer(ilsBoth);

      DblRegion zone_locations;
      CollectionIndexType size = container.size();
      if (size>1)
      {
         if (side==ilsPositive)
         {
            // get regions that have positive values
            InfluencePointIterator it2( container.begin() );
            InfluencePointIterator it1( it2++ );

            int iseg = 0;
            CollectionIndexType numsegs = size-1;
            bool in_zone = false;
            InfluencePointIterator itend( container.end() );
            while (it2 != itend )
            {
               InflPoint& pnt1 = *it1;
               InflPoint& pnt2 = *it2;

               Float64 x_intersect;
               LineAttitude lat = GetLineSegmentAttitude(pnt1.m_Location, pnt1.m_Value, pnt2.m_Location, pnt2.m_Value, &x_intersect,m_ZeroTolerance);

               if (!in_zone)
               {
                  if (lat==trpCrossingUpward&& !::IsZero(pnt2.m_Value,m_ZeroTolerance))
                  {
                     // Just crossed over to positive zone 
                     in_zone = true;
                     zone_locations.AddLocation(x_intersect);
                  }
                  else if (iseg==0)
                  {
                     // starting cases
                     if (lat == trpPositive)
                     {
                        // very first segment is positive
                        in_zone = true;
                        zone_locations.AddLocation(pnt1.m_Location);
                     }
                     else if (lat == trpCrossingDownward && ::IsGT(0.0,pnt1.m_Value,m_ZeroTolerance))
                     {
                        // very first segment crosses from positive to negative
                        zone_locations.push_back(pnt1.m_Location);  // push_back allows for duplicate location 
                        zone_locations.push_back(x_intersect);
                     }
                  }
               }
               else
               {
                  // in zone
                  if (lat==trpCrossingDownward)
                  {
                     in_zone = false;
                     zone_locations.AddLocation(x_intersect);
                  }
               }

               if (in_zone && iseg==numsegs-1)
               {
                  // last segment - need to close zone
                  in_zone = false;
                  zone_locations.AddLocation(pnt2.m_Location);
               }

               // loop
               it1 = it2++;
               iseg++;
            }
         }
         else if (side==ilsNegative)
         {
            InfluencePointIterator it2( container.begin() );
            InfluencePointIterator it1( it2++ );

            int iseg = 0;
            CollectionIndexType numsegs = size-1;
            bool in_zone = false;
            InfluencePointIterator itend( container.end() );
            while (it2 != itend )
            {
               InflPoint& pnt1 = *it1;
               InflPoint& pnt2 = *it2;

               Float64 x_intersect;
               LineAttitude lat = GetLineSegmentAttitude(pnt1.m_Location, pnt1.m_Value, pnt2.m_Location, pnt2.m_Value, &x_intersect,m_ZeroTolerance);

               if (!in_zone)
               {
                  if (lat==trpCrossingDownward && !::IsZero(pnt2.m_Value,m_ZeroTolerance))
                  {
                     // Just crossed over to negative zone 
                     in_zone = true;
                     zone_locations.AddLocation(x_intersect);
                  }
                  else if (iseg==0)
                  {
                     // starting cases
                     if (lat == trpNegative)
                     {
                        // very first segment is negative
                        in_zone = true;
                        zone_locations.AddLocation(pnt1.m_Location);
                     }
                     else if (lat == trpCrossingUpward  && ::IsLT(pnt1.m_Value,0.0,m_ZeroTolerance))
                     {
                        // very first segment crosses from negative to positive
                        zone_locations.push_back(pnt1.m_Location);
                        zone_locations.push_back(x_intersect);
                     }
                  }
               }
               else
               {
                  if (lat==trpCrossingUpward)
                  {
                     in_zone = false;
                     zone_locations.AddLocation(x_intersect);
                  }
               }

               if (in_zone && iseg==numsegs-1)
               {
                  // last segment - need to close zone
                  in_zone = false;
                  zone_locations.AddLocation(pnt2.m_Location);
               }

               // loop
               it1 = it2++;
               iseg++;
            }
         }
         else
         {
            // look for any non-zero regions
            // get regions that have positive values
            InfluencePointIterator it2( container.begin() );
            InfluencePointIterator it1( it2++ );

            int iseg = 0;
            CollectionIndexType numsegs = size-1;
            bool in_zone = false;
            InfluencePointIterator itend( container.end() );
            while (it2 != itend )
            {
               InflPoint& pnt1 = *it1;
               InflPoint& pnt2 = *it2;

               Float64 x_intersect;
               LineAttitude lat = GetLineSegmentAttitude(pnt1.m_Location, pnt1.m_Value, pnt2.m_Location, pnt2.m_Value, &x_intersect,m_ZeroTolerance);

               if (!in_zone)
               {
                  if (lat != trpZero)
                  {
                     // Just crossed over to non-zero
                     zone_locations.AddLocation(pnt1.m_Location);
                     in_zone = true;

                     if (iseg==0 && ::IsZero(pnt2.m_Value, m_ZeroTolerance))
                     {
                        // starting value goes from non-zero to zero
                        zone_locations.push_back(pnt2.m_Location);
                        in_zone = false;
                     }
                  }
               }
               else
               {
                  if (lat==trpZero)
                  {
                     // crossed over to zero zone
                     in_zone = false;
                     zone_locations.AddLocation(pnt1.m_Location);
                  }
               }

               if (in_zone && iseg==numsegs-1)
               {
                  // end of curve
                  zone_locations.push_back(pnt2.m_Location);
               }


               // loop
               it1 = it2++;
               iseg++;
            }
         }
      }
      // should always have an even number of locations to define zone
   #if defined _DEBUG
      size = zone_locations.size();
      ATLASSERT(size%2 == 0);
   #endif

      // have locations now copy them into safearray
      size = zone_locations.size();
      CComPtr<IDblArray> locs;
      CHRException hr;
      hr = locs.CoCreateInstance(CLSID_DblArray);
      hr = locs->Reserve(size);
      for (CollectionIndexType i = 0; i<size; i++)
      {
         hr = locs->Add(zone_locations[i]);
      }

      *locations = locs.Detach();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

	return S_OK;
}

void CInfluenceLine::FindInflPnt(Float64 location, InfluencePointIterator& cursor, InfluencePointIterator& end)
{
   ATLASSERT(cursor!=end);
   Float64 val = cursor->m_Location;
   ATLASSERT( val <= location);

   while (cursor!=end)
   {
      InfluencePointIterator cur(cursor);
      cur++;

      if (cur!=end)
      {
         if (cur->m_Location > location) // next point is after location
            return;
      }

      cursor = cur;
   }
}

Float64 CInfluenceLine::CalcInflArea(Float64 startLoc, Float64 endLoc, InfluencePointIterator& cursor, InfluencePointIterator& end)
{
   Float64 area = 0.0;

   Float64 loc_cur = cursor->m_Location;
   Float64 val_cur = cursor->m_Value;
   ATLASSERT(loc_cur <= startLoc);

   InfluencePointIterator lcur(cursor);
   lcur++;
   if (lcur==end)
   {
      cursor=lcur;
   }
   else
   {

      Float64 loc_nxt = lcur->m_Location;
      Float64 val_nxt = lcur->m_Value;

      ATLASSERT(loc_nxt > startLoc); // FindInflPnt should insure this

      // see if we need to interpolate our start location
      if (loc_cur!=startLoc)
      {
         val_cur = InterpolateTrapezoid(startLoc, loc_cur, loc_nxt, val_cur, val_nxt);
         loc_cur = startLoc;
      }

      bool loop = true;
      while (loop)
      {
         // see if we are at end of region
         if (loc_nxt>endLoc)
         {
            // segment crosses into next region
            val_nxt = InterpolateTrapezoid(endLoc, loc_cur, loc_nxt, val_cur, val_nxt);
            loc_nxt = endLoc;
            loop = false;
         }

         // compute area for current segment
         Float64 loc_area = TrapezoidArea(loc_cur, loc_nxt, val_cur, val_nxt);

         area += loc_area;

         if (loop)
         {
            lcur++;
            if (loc_nxt==endLoc)
            {
               loop = false;  // we hit the end exactly
            }
            else if (lcur!=end)
            {
               loc_cur = loc_nxt;
               val_cur = val_nxt;
               loc_nxt = lcur->m_Location;
               val_nxt = lcur->m_Value;
            }
            else
            {
               loop = false;
            }
         }
      }

      // only change the cursor if we haven't run it past the end
      if (lcur==end || lcur->m_Location <= endLoc)
         cursor = lcur;
   }

   return area;
}


STDMETHODIMP CInfluenceLine::ComputeAreaInRegions(IDblArray* regions, Float64* pArea)
{
   CHECK_IN(regions);
   CHECK_RETVAL(pArea);

   CHRException hr;

   try
   {
      Compute(ilsBoth);

      // attach regions and check validity
      CollectionIndexType rgn_size;
      hr = regions->get_Count(&rgn_size);

      if (rgn_size%2 != 0)
      {
         ATLASSERT(false); // about to throw
         THROW_LBAMA(INVALID_REGION); // regions must have two boundaries
      }

      // no regions, no area
      if (rgn_size==0)
      {
         *pArea=0.0;
         return S_OK;
      }

      // we have regions
      // regions must be within bounds of il
      Float64 ilstart, ilend;
      hr = Bounds(&ilstart, &ilend);

      Float64 loc;
      hr = regions->get_Item(0, &loc);
      if (loc < ilstart)
      {
         ATLASSERT(false); // about to throw
         THROW_LBAMA(INVALID_REGION); 
      }

      hr = regions->get_Item(rgn_size-1, &loc);
      if (ilend < loc)
      {
         ATLASSERT(false); // about to throw
         THROW_LBAMA(INVALID_REGION); 
      }

      // Compute areas
      InfluencePointContainer& container = GetContainer(ilsBoth);
      InfluencePointIterator cursor( container.begin() );
      InfluencePointIterator end( container.end() );

      Float64 area = 0.0;
      CollectionIndexType num_rgns = rgn_size/2;
      for (CollectionIndexType ir = 0; ir < num_rgns; ir++)
      {
         // start and end locations of region
         Float64 r_start, r_end;
         hr = regions->get_Item(ir*2,   &r_start);
         hr = regions->get_Item(ir*2+1, &r_end);

         // forward cursor to inflpoint at or just before start of region
         FindInflPnt(r_start, cursor, end);
         if (cursor == end)
            break;

         // only compute area if region is not zero-length
         if ( 0.0 < (r_end - r_start))
         {
            // compute area of all segments in this region and
            // forward cursor to inflpoint at or just before end of this region
            Float64 loc_area = CalcInflArea(r_start, r_end, cursor, end);

            area += loc_area;
         }

         if (cursor==end)
            break;
      }

      *pArea=area;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return S_OK;

}


STDMETHODIMP CInfluenceLine::IsZero(InfluenceSideType side, VARIANT_BOOL* isZero)
{
   CHECK_RETVAL(isZero);

   try
   {
      Compute(side);

      *isZero = VARIANT_TRUE;

      InfluencePointContainer& container = GetContainer(side);

      InfluencePointIterator it( container.begin() );
      InfluencePointIterator itend( container.end() );
      while(it != itend)
      {
         InflPoint& p1 = *it++;

         if (p1.m_Value!=0.0)
         {
            *isZero = VARIANT_FALSE;
            break;
         }
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IInfluenceLine);
   }

   return S_OK;
}