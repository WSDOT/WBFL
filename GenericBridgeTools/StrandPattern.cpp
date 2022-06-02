///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2022, Washington State Department of Transportation, All Rights Reserved
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

// StrandPattern.cpp : Implementation of CStrandPattern
#include "stdafx.h"
#include "GenericBridgeTools.h"
#include "StrandPattern.h"

#include <float.h>

/////////////////////////////////////////////////////////////////////////////
// CStrandPattern
HRESULT CStrandPattern::FinalConstruct()
{
   m_bReflectionEnabled = VARIANT_TRUE;
   m_PatternPoints.CoCreateInstance(CLSID_Point2dCollection);

   m_PatternBoundingBox.CoCreateInstance(CLSID_Rect2d);
   m_bUpdatePatternBoundingBox = true;

   m_StrandBoundingBox.CoCreateInstance(CLSID_Rect2d);
   m_bUpdateStrandBoundingBox = true;

   return S_OK;
}

void CStrandPattern::FinalRelease()
{
}

STDMETHODIMP CStrandPattern::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStrandPattern
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStrandPattern::AddPatternPoint(IPoint2d* point)
{
   CHECK_IN(point);

   double x;
   double y;
   point->get_X(&x);
   point->get_Y(&y);
   if ( x < 0 )
      return E_INVALIDARG; // x must be 0.0 or more

   // make a copy... copy by value semantics
   CComPtr<IPoint2d> p;
   p.CoCreateInstance(CLSID_Point2d);
   p->Move(x,y);

   HRESULT hr;
   hr = m_PatternPoints->Add(p);
   if ( FAILED(hr) )
      return hr;

   StrandPoint sp(point);
   sp.FillSequence = m_StrandPoints.size();
   m_StrandPoints.push_back(sp);

   // Place this debond point in a row
   Row* the_row = 0;
   Row target;
   point->get_Y(&target.Elevation);

   std::set<Row>::iterator found = m_Rows.find(target);
   if ( found != m_Rows.end() )
   {
      Row& row = *found;
      row.StrandPoints.push_back(m_StrandPoints.size()-1);

      the_row = &row;
   }
   else
   {
      Row row;
      row.Elevation = target.Elevation;
      row.StrandPoints.push_back( m_StrandPoints.size()-1 );
      std::pair<std::set<Row>::iterator,bool> result = m_Rows.insert(row);
      ATLASSERT(result.second == true);
      the_row = &(*(result.first));
   }

   // if the point is off the vertical centerline, mirror it about the Y axis
   // to ensure the symmetric of the strand pattern
   if ( 0 < x )
   {
      CComPtr<IPoint2d> p2;
      p2.CoCreateInstance(CLSID_Point2d);
      p2->Move(-x,target.Elevation);
      StrandPoint sp2(p2);
      sp2.FillSequence = m_StrandPoints.size();
      m_StrandPoints.push_back(sp2);

      the_row->StrandPoints.push_back(m_StrandPoints.size()-1);
   }

   m_bUpdatePatternBoundingBox = true;

   return S_OK;
}

STDMETHODIMP CStrandPattern::AddPatternPoints(IPoint2dCollection* points)
{
   CHECK_IN(points);
   CComPtr<IEnumPoint2d> enum_points;
   CComPtr<IPoint2d> point;
   points->get__Enum(&enum_points);
   while ( enum_points->Next(1,&point,NULL) != S_FALSE )
   {
      HRESULT hr = AddPatternPoint(point);
      if ( FAILED(hr) )
         return hr;

      point.Release();
   }

   return S_OK;
}

STDMETHODIMP CStrandPattern::get_PatternPointCount(long* count)
{
   return m_PatternPoints->get_Count(count);
}

STDMETHODIMP CStrandPattern::get_PatternPoint(long idx,IPoint2d** point)
{
   CHECK_RETOBJ(point);

   CComPtr<IPoint2d> p;
   HRESULT hr = m_PatternPoints->get_Item(idx,&p);

   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> new_point;
   new_point.CoCreateInstance(CLSID_Point2d);
   new_point->MoveEx(p);

   (*point) = new_point;
   (*point)->AddRef();

   return S_OK;
}

STDMETHODIMP CStrandPattern::get_PatternPoints(IPoint2dCollection** points)
{
   CHECK_RETOBJ(points);

   CComPtr<IPoint2dCollection> new_points;
   new_points.CoCreateInstance(CLSID_Point2dCollection);

   CComPtr<IEnumPoint2d> enum_point;
   CComPtr<IPoint2d> point;
   m_PatternPoints->get__Enum(&enum_point);
   while ( enum_point->Next(1,&point,NULL) != S_FALSE )
   {
      CComPtr<IPoint2d> new_point;
      new_point.CoCreateInstance(CLSID_Point2d);

      new_point->MoveEx(point);
      new_points->Add(new_point);

      point.Release();
   }

   (*points) = new_points;
   (*points)->AddRef();

   return S_OK;
}

STDMETHODIMP CStrandPattern::RemovePatternPoint(long idx)
{
   HRESULT hr = m_PatternPoints->Remove(idx);
   if ( FAILED(hr) )
      return hr;

   long nStrands;
   GetStrandCount(&nStrands);

   CComPtr<IPoint2dCollection> points = m_PatternPoints;
   m_PatternPoints.Release();
   m_PatternPoints.CoCreateInstance(CLSID_Point2dCollection);

   ClearPatternPoints();
   AddPatternPoints(points);
   SetStrandCount(nStrands,0);

   m_bUpdatePatternBoundingBox = true;

   return S_OK;
}

STDMETHODIMP CStrandPattern::ClearPatternPoints()
{
   RemoveAllStrands();
   m_PatternPoints->Clear();
   m_StrandPoints.clear();
   m_Rows.clear();
   m_LeftSections.clear();
   m_RightSections.clear();

   m_bUpdatePatternBoundingBox = true;

   return S_OK;
}

STDMETHODIMP CStrandPattern::EnablePointReflection(VARIANT_BOOL bEnable)
{
   m_bReflectionEnabled = bEnable;
   return S_OK;
}

STDMETHODIMP CStrandPattern::IsPointReflectionEnabled(VARIANT_BOOL* bEnable)
{
   CHECK_RETVAL(bEnable);
   *bEnable = m_bReflectionEnabled;
   return S_OK;
}

STDMETHODIMP CStrandPattern::get_StrandPointCount(long* count)
{
   CHECK_RETVAL(count);
   *count = m_StrandPoints.size();
   return S_OK;
}

STDMETHODIMP CStrandPattern::get_MaxStrandCount(long* count)
{
   return get_StrandPointCount(count);
}

STDMETHODIMP CStrandPattern::get_StrandPatternPoint(long idx,IPoint2d** point)
{
   CHECK_RETOBJ(point);
   if ( idx < 0 || m_StrandPoints.size() <= idx )
      return E_INVALIDARG;

   CComPtr<IPoint2d> p = m_StrandPoints[idx].Point;

   CComPtr<IPoint2d> new_point;
   new_point.CoCreateInstance(CLSID_Point2d);
   new_point->MoveEx(p);

   (*point) = new_point;
   (*point)->AddRef();

   return S_OK;
}

STDMETHODIMP CStrandPattern::get_StrandPoint(long idx,IPoint2d** point)
{
   long nStrands;
   GetStrandCount(&nStrands);

   // if there is an odd number of strands and reflection is not enabled
   // the first strand will be forced to the centerline if it's x position is non-zero
   CComPtr<IPoint2d> first_point = m_StrandPoints[0].Point;
   double first_x;
   double first_y;
   first_point->get_X(&first_x);
   first_point->get_Y(&first_y);
   bool bForceFirstStrandToCenter = (0 < first_x) && (nStrands%2 != 0) && (m_bReflectionEnabled == VARIANT_FALSE); 

   CComPtr<IPoint2d> new_point;
   new_point.CoCreateInstance(CLSID_Point2d);

   if ( idx == 0 && bForceFirstStrandToCenter )
   {
      new_point->Move(0,first_y);
   }
   else
   {
      // if the first strand is being forced to the center, then the second strand
      // is omitted.... increment the index by one
      if ( bForceFirstStrandToCenter )
        idx++;

      // Get the raw strand pattern point
      CComPtr<IPoint2d> p = m_StrandPoints[idx].Point;

      double x,y;
      p->get_X(&x);
      p->get_Y(&y);

      new_point->Move(x,y);
   }

   (*point) = new_point;
   (*point)->AddRef();

   return S_OK;
}

STDMETHODIMP CStrandPattern::AddStrand(long* nAdded)
{
   long nStrands;
   GetStrandCount(&nStrands);

   if ( m_StrandPoints.size() == 0 || m_StrandPoints.size() <= nStrands )
   {
      if ( nAdded )
         *nAdded = 0;

      return S_FALSE;
   }

   long inc;
   double x;
   m_StrandPoints[nStrands].Point->get_X(&x);
   if ( 0 < x && m_bReflectionEnabled == VARIANT_TRUE )
      inc = 2; // we have to add strands in pairs (unless it is on the Y axis)
   else
      inc = 1; // strand point on Y axis or reflection is disabled

   // make sure we haven't exceeded the limit
   if ( m_StrandPoints.size() < (nStrands+inc) )
   {
      if ( nAdded )
         *nAdded = 0;

      return S_FALSE;
   }

   StrandPoint& sp = m_StrandPoints[nStrands];
   sp.bHasStrand = true;

   if ( inc == 2 )
   {
      StrandPoint& sp2 = m_StrandPoints[nStrands+1];
      sp2.bHasStrand = true;
   }

   if ( nAdded )
      *nAdded = inc;

   m_bUpdateStrandBoundingBox = true;

   return S_OK;
}

STDMETHODIMP CStrandPattern::RemoveStrand(long* nRemoved)
{
   long nStrands;
   GetStrandCount(&nStrands);

   if ( nStrands == 0 )
   {
      if ( nRemoved )
         *nRemoved = 0;

      return S_FALSE;
   }

   long inc = 0;
   StrandPoint& sp = *(m_StrandPoints.begin() + nStrands - 1);
   double x;
   sp.Point->get_X(&x);
   if ( x < 0 && m_bReflectionEnabled == VARIANT_TRUE )
      inc = 2;
   else
      inc = 1;

   sp.bHasStrand = false;

   if ( inc == 2 )
   {
      StrandPoint& sp2 = *(m_StrandPoints.begin() + nStrands - 2);
      sp2.bHasStrand = false;
   }

   if ( nRemoved )
      *nRemoved = inc;

#if defined _DEBUG
   long ns;
   GetStrandCount(&ns);
   ATLASSERT( ns == nStrands - inc );
#endif // _DEBUG

   m_bUpdateStrandBoundingBox = true;

   return S_OK;
}

STDMETHODIMP CStrandPattern::RemoveAllStrands()
{
   std::vector<StrandPoint>::iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      StrandPoint& sp = *iter;
      sp.bHasStrand = false;
      sp.bIsDebonded = false;
   }

   m_bUpdateStrandBoundingBox = true;

   return S_OK;
}

STDMETHODIMP CStrandPattern::TestStrandCount(long nStrands,long* nValid)
{
   CHECK_RETVAL(nValid);

   // If nStrands is more than the pattern can hold,
   // return the max value.
   if ( m_StrandPoints.size() < nStrands )
   {
      *nValid = m_StrandPoints.size();
      return S_FALSE;
   }

   // If nStrands is zero...
   if ( nStrands == 0 )
   {
      *nValid = 0;
      return S_OK;
   }

   StrandPoint& sp = m_StrandPoints[nStrands-1];
   double x;
   sp.Point->get_X(&x);
   if ( 0 < x && m_bReflectionEnabled == VARIANT_TRUE )
   {
      // Can't set the number of strands because the requested strand
      // is to the left of Y axis and strands must be reflected.  The
      // next highest valid number of strands is nStrands+1.
      *nValid = nStrands+1;
      return S_FALSE;
   }

   // It is valid!
   *nValid = 0;
   return S_OK;
}

STDMETHODIMP CStrandPattern::SetStrandCount(long nStrands,long* nResult)
{
   CHECK_RETVAL(nResult);

   // If nStrands doesn't fit, return a valid value
   long next_strand;
   HRESULT hr = TestStrandCount(nStrands,&next_strand);
   if ( next_strand != 0 )
   {
      *nResult = next_strand;
      return S_FALSE;
   }

   long cStrands = 0;
   std::vector<StrandPoint>::iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      StrandPoint& sp = *iter;
      sp.bHasStrand = false;

      if ( cStrands < nStrands )
      {
         sp.bHasStrand = true;
         cStrands++;
      }
   }

   *nResult = 0; // 0 means successs... all strands were placed
   m_bUpdateStrandBoundingBox = true;
   return S_OK;
}

STDMETHODIMP CStrandPattern::GetStrandCount(long* nStrands)
{
   CHECK_RETVAL(nStrands);
   *nStrands = 0;
   std::vector<StrandPoint>::const_iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      const StrandPoint& sp = *iter;
      if ( sp.bHasStrand )
         (*nStrands)++;
   }

   return S_OK;
}

STDMETHODIMP CStrandPattern::get_RowsWithStrand(long* nRows)
{
   CHECK_RETVAL(nRows);
   *nRows = 0;
   std::set<Row>::const_iterator iter;
   for ( iter = m_Rows.begin(); iter != m_Rows.end(); iter++ )
   {
      const Row& row = *iter;

      std::vector<long>::const_iterator row_iter;
      for ( row_iter = row.StrandPoints.begin(); row_iter != row.StrandPoints.end(); row_iter++ )
      {
         long index = *row_iter;
         const StrandPoint& sp = m_StrandPoints[index];
         if ( sp.bHasStrand )
         {
            (*nRows)++;
            break; // break out of row_iter loop
         }
      }
   }

   return S_OK;
}

STDMETHODIMP CStrandPattern::get_StrandsInRow(long rowIdx,long* nStrands)
{
   CHECK_RETVAL(nStrands);
   if ( rowIdx < 0 || m_Rows.size() <= rowIdx )
      return E_INVALIDARG;

   std::set<Row>::const_iterator iter = m_Rows.begin();
   for ( long i = 0; i < rowIdx; i++ )
      iter++;

   const Row& row = *iter;
   *nStrands = 0;

   std::vector<long>::const_iterator sp_iter;
   for ( sp_iter = row.StrandPoints.begin(); sp_iter != row.StrandPoints.end(); sp_iter++ )
   {
      long index = *sp_iter;
      const StrandPoint& sp = m_StrandPoints[index];

      if ( sp.bHasStrand )
         (*nStrands)++;
   }

   return S_OK;
}

STDMETHODIMP CStrandPattern::AddDebondedStrand(double l1,double l2,long* nAdded)
{
   long num_added;
   HRESULT hr = AddStrand(&num_added);
   if ( nAdded )
      *nAdded = num_added;

   if ( num_added == 0 )
      return hr;

   long nStrands;
   GetStrandCount(&nStrands);
   nStrands -= num_added;

   StrandPoint& sp = m_StrandPoints[nStrands];
   sp.bIsDebonded = true;
   sp.DebondLength[0] = l1;
   sp.DebondLength[1] = l2;


   // Was the strand point mirrored about CL?
   if ( num_added == 2 )
   {
      StrandPoint& sp2 = m_StrandPoints[nStrands+1];
      sp2.bIsDebonded = true;
      sp2.DebondLength[0] = l1;
      sp2.DebondLength[1] = l2;
   }

   AddDebondSection(m_StrandPoints.size()-1,l1,l2);
 
   return S_OK;
}

STDMETHODIMP CStrandPattern::IsDebonded(long index,VARIANT_BOOL* bResult)
{
   CHECK_RETVAL(bResult);

   if ( index < 0 || m_StrandPoints.size() <= index )
      return E_INVALIDARG;

   StrandPoint& sp = m_StrandPoints[index];
   *bResult = sp.bIsDebonded ? VARIANT_TRUE : VARIANT_FALSE;

   return S_OK;
}

STDMETHODIMP CStrandPattern::DebondStrand(long index,double l1,double l2)
{
   if ( index < 0 || m_StrandPoints.size() <= index )
      return E_INVALIDARG;

   StrandPoint& sp = m_StrandPoints[index];
   sp.bIsDebonded = true;
   sp.DebondLength[0] = l1;
   sp.DebondLength[1] = l2;

   AddDebondSection(index,l1,l2);


   double x;
   sp.Point->get_X(&x);
   if ( !IsZero(x) && m_bReflectionEnabled == VARIANT_TRUE )
   {
      // need to debond the corrosponding strand that is the reflection of this one
      if ( x < 0 )
         index--;
      else
         index++;

      StrandPoint& sp2 = m_StrandPoints[index];
      sp2.bIsDebonded = true;
      sp2.DebondLength[0] = l1;
      sp2.DebondLength[1] = l2;

      AddDebondSection(index,l1,l2);
   }
   
   return S_OK;
}

STDMETHODIMP CStrandPattern::BondStrand(long index)
{
   if ( index < 0 || m_StrandPoints.size() <= index )
      return E_INVALIDARG;

   StrandPoint& sp = m_StrandPoints[index];

   // if the strand is not debonded, it must be bonded so there is nothing left to do
   if ( !sp.bIsDebonded )
      return S_OK;

   // Remove left section
   Section target;
   target.Location = sp.DebondLength[0];
   std::set<Section>::iterator found = m_LeftSections.find(target);
   ATLASSERT( found != m_LeftSections.end() );
   Section& left_section = *found;
   std::set<long>::iterator iter;
   for ( iter = left_section.StrandPoint.begin(); iter != left_section.StrandPoint.end(); iter++ )
   {
      if ( *iter == index )
      {
         left_section.StrandPoint.erase(iter);
      }
      break;
   }

   // Remove right section
   target.Location = sp.DebondLength[1];
   found = m_RightSections.find(target);
   ATLASSERT( found != m_RightSections.end() );
   Section& right_section = *found;
   for ( iter = right_section.StrandPoint.begin(); iter != right_section.StrandPoint.end(); iter++ )
   {
      if ( *iter == index )
      {
         right_section.StrandPoint.erase(iter);
      }
      break;
   }

   sp.bIsDebonded = false;
   sp.DebondLength[0] = 0;
   sp.DebondLength[1] = 0;

   double x;
   sp.Point->get_X(&x);
   if ( !IsZero(x) && m_bReflectionEnabled == VARIANT_TRUE )
   {
      // need to debond the corrosponding strand that is the reflection of this one
      if ( x < 0 )
         index--;
      else
         index++;

      StrandPoint& sp2 = m_StrandPoints[index];
      sp2.bIsDebonded = false;
      sp2.DebondLength[0] = 0;
      sp2.DebondLength[1] = 0;
   }

   return S_OK;
}

STDMETHODIMP CStrandPattern::GetDebondLength(long index,double* l1,double* l2)
{
   CHECK_RETVAL(l1);
   CHECK_RETVAL(l2);

   if ( index < 0 || m_StrandPoints.size() <= index )
      return E_INVALIDARG;

   StrandPoint& sp = m_StrandPoints[index];
   if ( !sp.bIsDebonded )
      return S_FALSE;

   *l1 = sp.DebondLength[0];
   *l2 = sp.DebondLength[1];

   return S_OK;
}

STDMETHODIMP CStrandPattern::get_DebondStrandsInRow(long rowIdx,long* nStrands)
{
   CHECK_RETVAL(nStrands);

   if ( rowIdx < 0 || m_Rows.size() <= rowIdx )
      return E_INVALIDARG;

   std::set<Row>::const_iterator iter = m_Rows.begin();
   for ( long i = 0; i < rowIdx; i++ )
      iter++;

   const Row& row = *iter;
   *nStrands = 0;

   std::vector<long>::const_iterator sp_iter;
   for ( sp_iter = row.StrandPoints.begin(); sp_iter != row.StrandPoints.end(); sp_iter++ )
   {
      long index = *sp_iter;
      const StrandPoint& sp = m_StrandPoints[index];

      if ( sp.bHasStrand && sp.bIsDebonded )
         (*nStrands)++;
   }

   return S_OK;
}

STDMETHODIMP CStrandPattern::IsExteriorStrandDebondedInRow(long rowIndex,VARIANT_BOOL* bResult)
{
   CHECK_RETVAL(bResult);

   if ( rowIndex < 0 || m_Rows.size() <= rowIndex )
      return E_INVALIDARG;

   std::set<Row>::const_iterator iter = m_Rows.begin();
   for ( long i = 0; i < rowIndex; i++ )
      iter++;

   const Row& row = *iter;
   long exteriorStrandIndex;
   double xmax = 0;

   std::vector<long>::const_iterator sp_iter;
   for ( sp_iter = row.StrandPoints.begin(); sp_iter != row.StrandPoints.end(); sp_iter++ )
   {
      long index = *sp_iter;
      const StrandPoint& sp = m_StrandPoints[index];

      double x;
      sp.Point->get_X(&x);
      if ( xmax <= fabs(x) )
      {
         xmax = fabs(x);
         exteriorStrandIndex = index;
      }
   }

   const StrandPoint& sp = m_StrandPoints[exteriorStrandIndex];
   *bResult = (sp.bIsDebonded ? VARIANT_TRUE : VARIANT_FALSE);

   return S_OK;
}

STDMETHODIMP CStrandPattern::GetDebondStrandCount(long* nDebondedStrands)
{
   CHECK_RETVAL(nDebondedStrands);

   *nDebondedStrands = 0;
   std::vector<StrandPoint>::iterator iter;
   for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
   {
      StrandPoint& sp = *iter;
      if ( sp.bIsDebonded )
         (*nDebondedStrands)++;
   }

   return S_OK;
}

STDMETHODIMP CStrandPattern::GetDebondSections(IDblArray** left,IDblArray** right)
{
   CHECK_RETOBJ(left);
   CHECK_RETOBJ(right);

   CComPtr<IDblArray> objLeft, objRight;
   objLeft.CoCreateInstance(CLSID_DblArray);
   objRight.CoCreateInstance(CLSID_DblArray);

   std::set<Section>::iterator iter;
   for ( iter = m_LeftSections.begin(); iter != m_LeftSections.end(); iter++ )
   {
      Section& section = *iter;
      objLeft->Add( section.Location );
   }

   std::set<Section>::reverse_iterator riter;
   for ( riter = m_RightSections.rbegin(); riter != m_RightSections.rend(); riter++ )
   {
      Section& section = *riter;
      objRight->Add( section.Location );
   }

   (*left) = objLeft;
   (*left)->AddRef();

   (*right) = objRight;
   (*right)->AddRef();

   return S_OK;
}

STDMETHODIMP CStrandPattern::DebondStrandsAtLeftSection(long sectionIdx,long* nDebondedStrands)
{
   CHECK_RETVAL(nDebondedStrands);
   if ( sectionIdx < 0 || m_LeftSections.size() <= sectionIdx )
      return E_INVALIDARG;

   std::set<Section>::iterator iter;
   long idx = 0;
   for ( iter = m_LeftSections.begin(); iter != m_LeftSections.end() && idx != sectionIdx; iter++, idx++ )
   {
   }

   ATLASSERT(iter != m_LeftSections.end() && idx == sectionIdx );

   Section& section = *iter;
   *nDebondedStrands = section.StrandPoint.size();

   return S_OK;
}

STDMETHODIMP CStrandPattern::DebondStrandsAtRightSection(long sectionIdx,long* nDebondedStrands)
{
   CHECK_RETVAL(nDebondedStrands);
   if ( sectionIdx < 0 || m_RightSections.size() <= sectionIdx )
      return E_INVALIDARG;

   std::set<Section>::reverse_iterator iter;
   long idx = 0;
   for ( iter = m_RightSections.rbegin(); iter != m_RightSections.rend() && idx != sectionIdx; iter++, idx++ )
   {
   }

//   ATLASSERT(iter != m_RightSections.end() && idx == sectionIdx );

   Section& section = *iter;
   *nDebondedStrands = section.StrandPoint.size();

   return S_OK;
}

STDMETHODIMP CStrandPattern::get_CG(double distFromStart,double gdrLength,IPoint2d** cg)
{
   long nStrands;
   GetStrandCount(&nStrands);

   return get_CGEx(nStrands,distFromStart,gdrLength,cg);
}

STDMETHODIMP CStrandPattern::get_CGEx(long nStrands,double distFromStart,double gdrLength,IPoint2d** cg)
{
   CHECK_RETOBJ(cg);

   // Cache the current number of strands in the pattern, set it to the desired value
   // compute CG, and then reset the current value
   long nStrandsCurrent,nResult;
   GetStrandCount(&nStrandsCurrent);
   SetStrandCount(nStrands,&nResult);

#if defined _DEBUG
   long valid;
   TestStrandCount(nStrands,&valid);
   ATLASSERT( valid == 0 );
#endif // _DEBUG


   long nBondedStrands = 0;
   double sum_x = 0.0;
   double sum_y = 0.0;
   for ( long i = 0; i < nStrands; i++ )
   {
      StrandPoint& sp = m_StrandPoints[i];

      double left_bond  = 0.0;
      double right_bond = gdrLength;

      // if strand is debonded, determine where the bond points are 
      // measured from the left end
      if ( sp.bIsDebonded )
      {
         left_bond  = sp.DebondLength[0];
         right_bond = gdrLength - sp.DebondLength[1];
      }

      // count the strand only if it is bonded at this location
      if ( InRange(left_bond,distFromStart,right_bond) )
      {
         // Don't get the strand coordinate directly... use the get_StrandPoint method
         // because it accounts for reflection
         CComPtr<IPoint2d> p;
         get_StrandPoint(i,&p);

         double x,y;
         p->get_X(&x);
         p->get_Y(&y);

         sum_x += x;
         sum_y += y;

         nBondedStrands++;
      }
   }

   CComPtr<IPoint2d> point;
   point.CoCreateInstance(CLSID_Point2d);
   if ( nStrands == 0 )
      point->Move(0,0);
   else
      point->Move(sum_x/nBondedStrands,sum_y/nBondedStrands);

   (*cg) = point;
   (*cg)->AddRef();

   SetStrandCount(nStrandsCurrent,&nResult);
   return S_OK;
}

STDMETHODIMP CStrandPattern::get_PatternBoundingBox(IRect2d** box)
{
   CHECK_RETOBJ(box);

   if ( m_bUpdatePatternBoundingBox )
   {
      m_PatternBoundingBox->put_Left(0);
      m_PatternBoundingBox->put_Right(0);
      m_PatternBoundingBox->put_Top(0);
      m_PatternBoundingBox->put_Bottom(0);

      std::vector<StrandPoint>::iterator iter;
      for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
      {
         StrandPoint& sp = *iter;

         m_PatternBoundingBox->BoundPointEx(sp.Point);
      }

      m_bUpdatePatternBoundingBox = false;
   }


   CComPtr<IRect2d> clone;
   clone.CoCreateInstance(CLSID_Rect2d);

   double l,r,t,b;
   m_PatternBoundingBox->get_Left(&l);
   m_PatternBoundingBox->get_Right(&r);
   m_PatternBoundingBox->get_Top(&t);
   m_PatternBoundingBox->get_Bottom(&b);

   clone->put_Left(l);
   clone->put_Right(r);
   clone->put_Top(t);
   clone->put_Bottom(b);

   (*box) = clone;
   (*box)->AddRef();

   return S_OK;
}

STDMETHODIMP CStrandPattern::get_StrandBoundingBox(IRect2d** box)
{
   CHECK_RETOBJ(box);

   if ( m_bUpdateStrandBoundingBox )
   {
      m_StrandBoundingBox->put_Left(0);
      m_StrandBoundingBox->put_Right(0);
      m_StrandBoundingBox->put_Top(0);
      m_StrandBoundingBox->put_Bottom(0);

      std::vector<StrandPoint>::iterator iter;
      for ( iter = m_StrandPoints.begin(); iter != m_StrandPoints.end(); iter++ )
      {
         StrandPoint& sp = *iter;

         if ( sp.bHasStrand )
            m_StrandBoundingBox->BoundPointEx(sp.Point);
      }

      m_bUpdateStrandBoundingBox = false;
   }


   CComPtr<IRect2d> clone;
   clone.CoCreateInstance(CLSID_Rect2d);

   double l,r,t,b;
   m_StrandBoundingBox->get_Left(&l);
   m_StrandBoundingBox->get_Right(&r);
   m_StrandBoundingBox->get_Top(&t);
   m_StrandBoundingBox->get_Bottom(&b);

   clone->put_Left(l);
   clone->put_Right(r);
   clone->put_Top(t);
   clone->put_Bottom(b);

   (*box) = clone;
   (*box)->AddRef();

   return S_OK;
}

void CStrandPattern::AddDebondSection(long strandIdx,double left,double right)
{
  // Place this debond point in a section
   Section target;
   target.Location = left;
   std::set<Section>::iterator found = m_LeftSections.find(target);
   if ( found != m_LeftSections.end() )
   {
      Section& section = *found;
      section.StrandPoint.insert(strandIdx);
   }
   else
   {
      Section section;
      section.Location = target.Location;
      section.StrandPoint.insert( strandIdx );
      std::pair<std::set<Section>::iterator,bool> result = m_LeftSections.insert(section);
      ATLASSERT(result.second == true);
   }

   target.Location = right;
   found = m_RightSections.find(target);
   if ( found != m_RightSections.end() )
   {
      Section& section = *found;
      section.StrandPoint.insert(strandIdx);
   }
   else
   {
      Section section;
      section.Location = target.Location;
      section.StrandPoint.insert( strandIdx );
      std::pair<std::set<Section>::iterator,bool> result = m_RightSections.insert(section);
      ATLASSERT(result.second == true);
   }
}
