///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// Path.cpp : Implementation of CPath
#include "stdafx.h"
#include "WBFLCogo.h"
#include "Path.h"
#include "PathElement.h"
#include <WBFLCogo\CogoHelpers.h>
#include "CubicSpline.h"
#include "CompoundCurve.h"
#include "CircularCurve.h"
#include "TransitionCurve.h"
#include "CogoEngine.h"
#include <Float.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPath
HRESULT CPath::FinalConstruct()
{
   HRESULT hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CComObject<CCogoEngine>* pEngine;
   CComObject<CCogoEngine>::CreateInstance(&pEngine);
   m_CogoEngine = pEngine;

   m_Xform.CoCreateInstance(CLSID_CoordinateXform2d);

   return S_OK;
}

void CPath::FinalRelease()
{
}

STDMETHODIMP CPath::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPath,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

//STDMETHODIMP CPath::get__NewEnum(IUnknown** retval)
//{
//   return S_OK;
//}

STDMETHODIMP CPath::get_Item(CollectionIndexType idx, IPathElement* *pVal)
{
   CHECK_RETOBJ(pVal);

   if ( !IsValidIndex(idx,m_coll) )
   {
      return E_INVALIDARG;
   }

   CComVariant& at = m_coll[idx];
   CComVariant& var = at;
   var.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CPath::putref_Item(CollectionIndexType idx, IPathElement *pVal)
{
   CHECK_IN(pVal);

   if ( !IsValidIndex(idx,m_coll) )
   {
      return E_INVALIDARG;
   }

   // Get the item
   CComVariant& at = m_coll[idx];
   CComVariant& var = at; // Variant holding IUnknown to PathElement

   var = pVal; // Associate new PathElement with this variant

   return S_OK;
}

STDMETHODIMP CPath::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   long count;
   IPathElementCollection::get_Count(&count);
   *pVal = (CollectionIndexType)count;
   return S_OK;
}

STDMETHODIMP CPath::Add(IPathElement* element)
{
   return Insert(m_coll.size(), element);
}

STDMETHODIMP CPath::AddEx(IUnknown* dispElement)
{
   return InsertEx(m_coll.size(),dispElement);
}

STDMETHODIMP CPath::Insert(CollectionIndexType idx, IPathElement* element)
{
   CHECK_IN(element);

   if ( idx < 0 || (CollectionIndexType)m_coll.size() < idx )
   {
      return E_INVALIDARG;
   }

   m_coll.insert(m_coll.begin() + idx,CComVariant(element) );

   m_PathElements.clear();
   
   return S_OK;
}

STDMETHODIMP CPath::InsertEx(CollectionIndexType idx, IUnknown* dispElement)
{
   CHECK_IN(dispElement);
   CComQIPtr<IPoint2d> point(dispElement);
   CComQIPtr<ICircularCurve> arc(dispElement);
   CComQIPtr<ITransitionCurve> transition(dispElement);
   CComQIPtr<ICompoundCurve> curve(dispElement);
   CComQIPtr<ILineSegment2d> ls(dispElement);
   CComQIPtr<ICubicSpline> spline(dispElement);
   CComQIPtr<IPath> path(dispElement);

   if ( point == nullptr && arc == nullptr && transition == nullptr && curve == nullptr && ls == nullptr && spline == nullptr && path == nullptr )
   {
      return Error(IDS_E_PATHELEMENTTYPE,IID_IPath,COGO_E_PATHELEMENTTYPE);
   }

   if ( path )
   {
      CollectionIndexType nElements;
      path->get_Count(&nElements);
      for ( CollectionIndexType idx = 0; idx < nElements; idx++ )
      {
         CComPtr<IPathElement> element;
         path->get_Item(idx,&element);

         HRESULT hr = Insert(m_coll.size(),element);
         if ( FAILED(hr) )
         {
            return hr;
         }
      }
   }
   else
   {
      CComObject<CPathElement>* pElement;
      CComObject<CPathElement>::CreateInstance(&pElement);
      CComPtr<IPathElement> element = pElement;

      if ( point )
      {
         element->putref_Value(dispElement);
      }
      else
      {
         element->putref_Value(dispElement);
      }

      return Insert(idx,pElement);
   }

   return S_OK;
}

STDMETHODIMP CPath::Remove(VARIANT varID)
{
   if ( varID.vt == VT_I2 || varID.vt == VT_I4 )
   {
      // Element identified by zero-based index
      long index = (varID.vt == VT_I2 ? varID.iVal : varID.lVal);
      if ( index < 0 || (long)m_coll.size() <= index )
      {
         return E_INVALIDARG;
      }

      m_coll.erase(m_coll.begin() + index);
   }
   else if ( varID.vt == VT_UNKNOWN || varID.vt == VT_DISPATCH )
   {
      // Element identified by an Path element object or by proint, line segment, or horz curve
      CComQIPtr<IPathElement> element(varID.punkVal);
      CComQIPtr<IPoint2d> point(varID.punkVal);
      CComQIPtr<ICircularCurve> arc(varID.punkVal);
      CComQIPtr<ITransitionCurve> transition(varID.punkVal);
      CComQIPtr<ICompoundCurve> hc(varID.punkVal);
      CComQIPtr<ILineSegment2d> ls(varID.punkVal);
      CComQIPtr<ICubicSpline> spline(varID.punkVal);

      // The input object is not of the correct type
      if ( element    == nullptr && 
           point      == nullptr &&
           ls         == nullptr &&
           arc        == nullptr &&
           transition == nullptr &&
           hc         == nullptr &&
           spline     == nullptr)
      {
         return E_INVALIDARG;
      }

      bool bRemoved = false;
      for ( auto iter = m_coll.begin(); iter < m_coll.end(); iter++ )
      {
         CComVariant& at = *iter;
         CComVariant& varElement = at;
         CComQIPtr<IPathElement> ae(varElement.punkVal);
         CComPtr<IUnknown> dispVal;
         ae->get_Value(&dispVal);
         if ( element != nullptr && element.IsEqualObject(varElement.punkVal) ||
              point   != nullptr && point.IsEqualObject(dispVal)              ||
              ls      != nullptr && ls.IsEqualObject(dispVal)                 ||
              arc     != nullptr && arc.IsEqualObject(dispVal)                ||
              transition != nullptr && transition.IsEqualObject(dispVal)      ||
              spline  != nullptr && ls.IsEqualObject(dispVal)                 ||
              hc      != nullptr && hc.IsEqualObject(dispVal) )
         {
            m_coll.erase(iter);
            bRemoved = true;
            break; // exit the loop
         }
      }

      if ( !bRemoved )
      {
         return E_INVALIDARG;
      }
   }
   else
   {
      return E_INVALIDARG;
   }

   m_PathElements.clear();
   
	return S_OK;
}

STDMETHODIMP CPath::Clear()
{
   m_coll.clear();
   m_PathElements.clear();
   return S_OK;
}

STDMETHODIMP CPath::LocatePoint( Float64 distance, OffsetMeasureType offsetMeasure, Float64 offset, VARIANT varDir, IPoint2d* *newPoint)
{
   CHECK_RETOBJ(newPoint);

   HRESULT hr = S_OK;
   CComPtr<IDirection> dir;
   if ( !IsZero(offset) )
   {
      hr = cogoUtil::DirectionFromVariant(varDir,&dir);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   if ( offsetMeasure == omtNormal && !IsZero(offset) && dir != nullptr)
   {
      // add offset so that it is along direction
      CComPtr<IDirection> normal;
      this->Normal(distance,&normal);

      CComPtr<IAngle> objAngle;
      dir->AngleBetween(normal,&objAngle); // dir - normal

      Float64 angle;
      objAngle->get_Value(&angle);

      offset *= cos(angle);
   }

   // Find the path element that encompasses the input distance.
   // The return values are the distance to the beginning of this element
   // and the path element. The path element will be either
   // a petLineSegment or petCompoundCurve. If needed, a temporary path
   // element object will be created.
   CComPtr<IPathElement> element;
   Float64 beginDist;
   FindElement(distance,&beginDist,&element);

   PathElementType type;
   element->get_Type(&type);
   ATLASSERT( type != petPoint ); // Cannot be petPoint

   CComPtr<IUnknown> dispVal;
   element->get_Value(&dispVal);

   if ( type == petLineSegment )
   {
      // Path element is a line segment

      // The Path is in the direction of the line segment
      // Locate a point on the Path and then the offset point
      Float64 dist = distance - beginDist; // distance from start of element

      CComQIPtr<ILineSegment2d> ls(dispVal);
      ATLASSERT(ls);

      CComPtr<IPoint2d> start, end;
      ls->get_StartPoint(&start);
      ls->get_EndPoint(&end);

      Float64 length;
      CComPtr<IDirection> dirPath;
      cogoUtil::Inverse(start,end,&length,&dirPath);

      CComPtr<IPoint2d> basePoint;
      cogoUtil::LocateByDistDir(start,dist,dirPath,0.0,&basePoint);

      if ( !IsZero(offset) )
      {
         cogoUtil::LocateByDistDir(basePoint,offset,dir,0.0,newPoint);
      }
      else
      {
         (*newPoint) = basePoint;
         (*newPoint)->AddRef();
      }

      return S_OK;
   }
   else if (type == petCircularCurve)
   {
      // The begin distance is at the PC point on the curve
      // The Path follows the curve
      // Use the curve object to locate the baseline point
      // and the locate the offset point
      Float64 dist_along_curve = distance - beginDist;

      CComQIPtr<ICircularCurve> hc(dispVal);
      ATLASSERT(hc);

      CComPtr<IPoint2d> basePoint;
      hr = hc->PointOnCurve(dist_along_curve, &basePoint);
      if (FAILED(hr))
      {
         return hr;
      }

      if (!IsZero(offset))
      {
         cogoUtil::LocateByDistDir(basePoint, offset, dir, 0.0,  newPoint);
      }
      else
      {
         (*newPoint) = basePoint;
         (*newPoint)->AddRef();
      }

      return S_OK;
   }
   else if (type == petTransitionCurve)
   {
      // The begin distance is at the TS point on the curve
      // The Path follows the curve
      // Use the curve object to locate the baseline point
      // and the locate the offset point
      Float64 dist_along_curve = distance - beginDist;

      CComQIPtr<ITransitionCurve> hc(dispVal);
      ATLASSERT(hc);

      CComPtr<IPoint2d> basePoint;
      hr = hc->PointOnCurve(dist_along_curve, &basePoint);
      if (FAILED(hr))
      {
         return hr;
      }

      if (!IsZero(offset))
      {
         cogoUtil::LocateByDistDir(basePoint, offset, dir, 0.0, newPoint);
      }
      else
      {
         (*newPoint) = basePoint;
         (*newPoint)->AddRef();
      }

      return S_OK;
   }
   else if ( type == petCompoundCurve )
   {
      // The begin distance is at the TS point on the curve
      // The Path follows the curve
      // Use the curve object to locate the baseline point
      // and the locate the offset point
      Float64 dist_along_curve = distance - beginDist;

      CComQIPtr<ICompoundCurve> hc(dispVal);
      ATLASSERT(hc);

      CComPtr<IPoint2d> basePoint;
      hr = hc->PointOnCurve(dist_along_curve,&basePoint);
      if ( FAILED(hr) )
      {
         return hr;
      }

      if ( !IsZero(offset) )
      {
         cogoUtil::LocateByDistDir(basePoint,offset,dir,0.0,newPoint);
      }
      else
      {
         (*newPoint) = basePoint;
         (*newPoint)->AddRef();
      }

      return S_OK;
   }
   else if ( type == petCubicSpline )
   {
      // The begin distance is at the start point on the spline
      // The Path follows the curve
      // Use the curve object to locate the baseline point
      // and the locate the offset point
      Float64 dist_along_spline = distance - beginDist;

      CComQIPtr<ICubicSpline> spline(dispVal);
      ATLASSERT(spline);

      CComPtr<IPoint2d> basePoint;
      hr = spline->PointOnSpline(dist_along_spline,&basePoint);
      if ( FAILED(hr) )
      {
         return hr;
      }

      if ( !IsZero(offset) )
      {
         cogoUtil::LocateByDistDir(basePoint,offset,dir,0.0,newPoint);
      }
      else
      {
         (*newPoint) = basePoint;
         (*newPoint)->AddRef();
      }

      return S_OK;
   }
   else
   {
      ATLASSERT(false); // should never get here
   }

   ATLASSERT(false); // Should never get here!!!
   return E_NOTIMPL;
}

STDMETHODIMP CPath::Bearing(Float64 distance,IDirection* *dir)
{
   CHECK_RETOBJ(dir);

   // Find a path element that encompasses the input distance.
   // The return values are the distance to the beginning of this element
   // and the Path element. The Path element will be either
   // an petLineSegment or petCompoundCurve. If needed, a temporary Path
   // element object will be created.
   CComPtr<IPathElement> element;
   Float64 beginDist;
   FindElement(distance,&beginDist,&element);

   PathElementType type;
   element->get_Type(&type);
   ATLASSERT( type != petPoint ); // Cannot be petPoint

   CComPtr<IUnknown> dispVal;
   element->get_Value(&dispVal);

   if ( type == petLineSegment )
   {
      // Path element is a line segment
      CComQIPtr<ILineSegment2d> ls(dispVal);
      ATLASSERT(ls);

      CComPtr<IPoint2d> start, end;
      ls->get_StartPoint(&start);
      ls->get_EndPoint(&end);

      Float64 length;
      cogoUtil::Inverse(start,end,&length,dir);

      return S_OK;
   }
   else if (type == petCircularCurve)
   {
      // The begin distance is to the PC point on the curve
      // The Path follows the curve
      // Use the curve object to locate the baseline point
      // and the locate the offset point
      Float64 dist_along_curve = distance - beginDist;

      CComQIPtr<ICircularCurve> hc(dispVal);
      ATLASSERT(hc);

      hc->Bearing(dist_along_curve, dir);
      return S_OK;
   }
   else if (type == petTransitionCurve)
   {
      // The begin distance is to the TS point on the curve
      // The Path follows the curve
      // Use the curve object to locate the baseline point
      // and the locate the offset point
      Float64 dist_along_curve = distance - beginDist;

      CComQIPtr<ITransitionCurve> hc(dispVal);
      ATLASSERT(hc);

      hc->Bearing(dist_along_curve, dir);
      return S_OK;
   }
   else if ( type == petCompoundCurve )
   {
      // The begin distance is to the TS point on the curve
      // The Path follows the curve
      // Use the curve object to locate the baseline point
      // and the locate the offset point
      Float64 dist_along_curve = distance - beginDist;

      CComQIPtr<ICompoundCurve> hc(dispVal);
      ATLASSERT(hc);

      hc->Bearing(dist_along_curve,dir);
      return S_OK;
   }
   else if ( type == petCubicSpline )
   {
      // The begin distance is to the start of spline
      // The Path follows the curve
      // Use the curve object to locate the baseline point
      // and the locate the offset point
      Float64 dist_along_spline = distance - beginDist;

      CComQIPtr<ICubicSpline> spline(dispVal);
      ATLASSERT(spline);

      spline->Bearing(dist_along_spline,dir);
      return S_OK;
   }

   ATLASSERT(false); // Should never get here!!!
   return E_NOTIMPL;
}

STDMETHODIMP CPath::Normal(Float64 distance,IDirection* *dir)
{
//   CHECK_RETOBJ(dir); // This is handled in call to Bearing

   HRESULT hr = Bearing(distance,dir);
   if ( FAILED(hr) )
   {
      return hr;
   }

   (*dir)->IncrementBy(CComVariant(3*PI_OVER_2));

   return S_OK;
}

STDMETHODIMP CPath::ProjectPoint(IPoint2d* point, IPoint2d* *newPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection)
{
   CHECK_IN(point);
   CHECK_RETVAL(pDistFromStart);
   CHECK_RETVAL(pvbOnProjection);
   CHECK_RETOBJ(newPoint);

   std::vector<Element>& vElements = GetPathElements();

   Float64 shortestDistance = DBL_MAX;

   auto nElements = vElements.size();
   auto first = vElements.begin();
   auto iter = first;
   auto end = vElements.end();
   auto last = end - 1;
   for( ; iter != end; iter++)
   {
      auto element(*iter);
      CComPtr<IPathElement> path_element(element.pathElement);

      CComPtr<IPoint2d> prjPoint;
      Float64 dist_from_start_of_element;
      VARIANT_BOOL vbOnProjection;
      ProjectPointOnElement(point,path_element,&prjPoint,&dist_from_start_of_element,&vbOnProjection);

      if (
         (iter != first && iter != last && vbOnProjection == VARIANT_TRUE) // don't consider projections on internal elements
         ||
         (iter == first && vbOnProjection == VARIANT_TRUE && 0 < dist_from_start_of_element && 1 < nElements) // don't consider projections after the end of the first element if there are more than 1 elements
         ||
         (iter == last && vbOnProjection == VARIANT_TRUE && dist_from_start_of_element < 0 && 1 < nElements) // don't consider projects before the start of the last element if there are more than 1 elements
         )
      {
         continue;
      }


      Float64 dist_from_element_to_point;
      CComPtr<IDirection> dir;
      cogoUtil::Inverse(point,prjPoint,&dist_from_element_to_point,&dir);

      if (dist_from_element_to_point < shortestDistance )
      {
         shortestDistance = dist_from_element_to_point;
         if (*newPoint) (*newPoint)->Release();
         (*newPoint) = prjPoint;
         (*newPoint)->AddRef();
         *pDistFromStart = element.start + dist_from_start_of_element;
         *pvbOnProjection = vbOnProjection;
      }
   }

   return S_OK;
}

STDMETHODIMP CPath::Offset(IPoint2d* point,Float64* distance,Float64* offset)
{
   CHECK_IN(point);
   CHECK_RETVAL(offset);

   // Find where the point projects onto the path
   CComPtr<IPoint2d> prjPoint;
   VARIANT_BOOL vbOnProjection;
   HRESULT hr = ProjectPoint(point, &prjPoint, distance, &vbOnProjection);
   if (FAILED(hr)) return hr;

   // Get the bearing at the location where the point projects onto the path
   CComPtr<IDirection> brg;
   Bearing(*distance, &brg);
   Float64 dir;
   brg->get_Value(&dir); // bearing at the projected point

   // create a line tangent to the path, through the projection point in the forard direction
   CComPtr<IVector2d> vector;
   vector.CoCreateInstance(CLSID_Vector2d);
   vector->put_Direction(dir);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->SetExplicit(prjPoint, vector);

   // Get the shortest distance from the input point to the line.
   // ShortestOffsetToPoint takes care of sign of offset based on point being on the left or right of the line
   m_GeomUtil->ShortestOffsetToPoint(line, point, offset);

   return S_OK;
}

STDMETHODIMP CPath::Intersect(ILine2d* line,IPoint2d* pNearest,IPoint2d** point)
{
   return IntersectEx(line,pNearest,VARIANT_TRUE,VARIANT_TRUE,point);
}

STDMETHODIMP CPath::IntersectEx(ILine2d* line,IPoint2d* pNearest,VARIANT_BOOL vbProjectBack,VARIANT_BOOL vbProjectAhead,IPoint2d** point)
{
   CHECK_IN(line);
   CHECK_IN(pNearest);
   CHECK_RETOBJ(point);

   std::vector<Element>& vElements = GetPathElements();

   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   std::vector<Element>::iterator iter(vElements.begin());
   std::vector<Element>::iterator end(vElements.end());
   for ( ; iter != end; iter++ )
   {
      Element& element = (*iter);

      bool bProjectBack  = (vbProjectBack  == VARIANT_FALSE ? false : (iter == vElements.begin() ? true : false));
      bool bProjectAhead = (vbProjectAhead == VARIANT_FALSE ? false : (iter == vElements.end() - 1 ? true : false));
      IntersectElement(line,element.pathElement,bProjectBack,bProjectAhead,points);
   }

   Float64 shortestDistance = DBL_MAX;
   CComPtr<IPoint2d> nearestPoint;
   CComPtr<IEnumPoint2d> enumPoints;
   points->get__Enum(&enumPoints);
   CComPtr<IPoint2d> p;
   while ( enumPoints->Next(1,&p,nullptr) != S_FALSE )
   {
      Float64 dist;
      CComPtr<IDirection> dir;
      cogoUtil::Inverse(p,pNearest,&dist,&dir);

      if ( dist < shortestDistance )
      {
         shortestDistance = dist;
         nearestPoint = p;
      }

      p.Release();
   }

   if ( nearestPoint )
   {
      (*point) = nearestPoint;
      (*point)->AddRef();
      return S_OK;
   }

   return Error(IDS_E_NOINTERSECTION,IID_IPath,COGO_E_NOINTERSECTION);
}

STDMETHODIMP CPath::get_Length(Float64* pLength)
{
   CHECK_RETVAL(pLength);

   GetPathElements(); // causes the path length to be computed if it is out of date
   *pLength = m_PathLength;
   return S_OK;
}

STDMETHODIMP CPath::get__EnumPathElements(IEnumPathElements** pVal)
{
   CHECK_RETOBJ(pVal);

   typedef CComEnumOnSTL<IEnumPathElements,
                         &IID_IEnumPathElements, 
                         IPathElement*,
      _CopyVariantToInterface<IPathElement>, 
                                                std::vector<CComVariant>> Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = pEnum->Init( nullptr, m_coll );
   if ( FAILED(hr) )
   {
      return hr;
   }

   pEnum->QueryInterface( pVal );

   return S_OK;
}

void CPath::FindElement(Float64 distance,Float64* pBeginDist,IPathElement* *pElement)
{
   Element testElement;
   testElement.start = distance;
   testElement.end   = distance;

   std::vector<Element>& vElements = GetPathElements();

   // NOTE: lower_bound performs a binary search
   std::vector<Element>::iterator lowerBound = std::lower_bound(vElements.begin(), vElements.end(), testElement, [](const auto& v1, const auto& v2) {return IsLE(v1.end,v2.start);});
   if ( lowerBound == vElements.end() )
   {
      if ( IsLE(distance,vElements.front().start) )
      {
         lowerBound = vElements.begin();
      }
      else if ( IsLE(vElements.back().end,distance) )
      {
         lowerBound = vElements.end()-1;
      }
      else
      {
         ATLASSERT(vElements.size() == 1);
         lowerBound = vElements.begin();
      }
   }
   Element& element(*lowerBound);
   *pBeginDist = element.start;
   element.pathElement.CopyTo(pElement);
}

std::vector<Element>& CPath::GetPathElements()
{
   if ( m_PathElements.size() == 0 )
   {
      // as we build up the path elements, we know the length of each element
      // we can compute the path length as we go instead of having to do it later
      m_PathLength = 0; 

      // container has been requested before... initalized
      if ( m_coll.size() == 0 )
      {
         // There are no Path elements defined
         // The Path is a straight line, due east with the reference point at (0,0)
         // Create an Path element accordingly
         CComPtr<IPoint2d> start;
         CComPtr<IPoint2d> end;
         start.CoCreateInstance(CLSID_Point2d);
         end.CoCreateInstance(CLSID_Point2d);

         Float64 length = 100;

         start->Move(0,0);
         end->Move(length,0);

         CComPtr<IPathElement> element;
         CreateDummyPathElement(start,end,&element);

         Element myElement;
         myElement.start = 0;
         myElement.end = myElement.start + length;
         myElement.pathElement = element;
         m_PathElements.push_back(myElement);

         m_PathLength += length;
      }
      else if ( m_coll.size() == 1 )
      {
         // There is exactly one element defining the Path
         //
         // The first Path element is projected
         // to define the Path

         CComPtr<IPathElement> element;
         get_Item(0,&element);

         PathElementType type;
         element->get_Type(&type);

         CComPtr<IUnknown> dispVal;
         element->get_Value(&dispVal);

         if ( type == petPoint )
         {
            CComQIPtr<IPoint2d> pnt(dispVal);

            ATLASSERT( m_coll.size() == 1 );
            // Path is due east
            // Create a line segment element to represent this
            CComQIPtr<IPoint2d> start(dispVal); // Path point is the start point
            CComPtr<IPoint2d> end; // create an end point
            end.CoCreateInstance(CLSID_Point2d);

            cogoUtil::CopyPoint(end,start); // make the start and end point equal

            Float64 length = 100;
            end->Offset(length,0); // offset the end point in the X direction only (makes the line due east)

            // make a line segment
            CComPtr<IPathElement> element;
            CreateDummyPathElement(start,end,&element);

            Element myElement;
            myElement.start = 0;
            myElement.end = length;
            myElement.pathElement = element;
            m_PathElements.push_back(myElement);

            m_PathLength += length;
         }
         else if ( type == petLineSegment || type == petCircularCurve || type == petTransitionCurve || type == petCompoundCurve || type == petCubicSpline )
         {
            // The one and only element is a line segment or horz curve...
            // Just return it
            Float64 length = GetElementLength(element);
            Element myElement;
            myElement.start = 0;
            myElement.end = myElement.start + length;
            myElement.pathElement = element;
            m_PathElements.push_back(myElement);

            m_PathLength += length;
         }
         else
         {
            ATLASSERT(false); // Should never get here
         }
      }
      else
      {
         // There are multiple Path elements
         auto currIter = m_coll.begin();
         auto nextIter = currIter + 1;
         CComPtr<IPathElement> currElement, nextElement;
         Float64 currDist = 0.00;
         Float64 nextDist = currDist;
         do
         {
            // NOTE: The order of these next 4 lines is critical
            bool bExtendBack = ( currIter == m_coll.begin() ? true : false );
            CComVariant& atCurr = *currIter++;
            CComVariant& atNext = *nextIter++;
            bool bExtendAhead = false;

            CComVariant& varCurrElement = atCurr;
            CComVariant& varNextElement = atNext;

            currElement.Release();
            nextElement.Release();
            varCurrElement.pdispVal->QueryInterface(&currElement);
            varNextElement.pdispVal->QueryInterface(&nextElement);

            PathElementType currType, nextType;
            currElement->get_Type(&currType);
            nextElement->get_Type(&nextType);

            CComPtr<IUnknown> currVal;
            CComPtr<IUnknown> nextVal;
            currElement->get_Value(&currVal);
            nextElement->get_Value(&nextVal);

            if ( currType == petPoint )
            {
               // Current element is a point
               // Since points don't have length, we have to project a line
               // to the next element to determine if the point falls between
               // this point and the next element. If it does, add it to the list.
               CComQIPtr<IPoint2d> currPoint(currVal);

               CComPtr<IPathElement> element;
               CreateDummyPathElement(currPoint,nextElement,&element);

               CComPtr<IUnknown> dispDummy;
               element->get_Value(&dispDummy);
               CComQIPtr<ILineSegment2d> dummyLS(dispDummy);
               Float64 length;
               dummyLS->get_Length(&length);

               if ( !IsZero(length) )
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end = nextDist;
                  myElement.pathElement = element;
                  m_PathElements.push_back(myElement);
   
                  m_PathLength += length;
               }
            }
            else if ( currType == petLineSegment )
            {
               // Current segment is a line segment.
               CComQIPtr<ILineSegment2d> currLS(currVal);
               Float64 length;
               currLS->get_Length(&length);

               if ( !IsZero(length) )
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end = nextDist;
                  myElement.pathElement = currElement;
                  m_PathElements.push_back(myElement);
   
                  m_PathLength += length;
               }

               // Now add a line segment that goes from the end of this one to the
               // start of the next element
               CComPtr<IPoint2d> currEndPoint;
               currLS->get_EndPoint(&currEndPoint);

               currDist = nextDist;

               CComPtr<IPathElement> element;
               CreateDummyPathElement(currEndPoint,nextElement,&element);

               CComPtr<IUnknown> dispDummy;
               element->get_Value(&dispDummy);
               CComQIPtr<ILineSegment2d> dummyLS(dispDummy);
               dummyLS->get_Length(&length);

               if ( !IsZero(length) )
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end = nextDist;
                  myElement.pathElement = element;
                  m_PathElements.push_back(myElement);
   
                  m_PathLength += length;
               }
            }
            else if (currType == petCircularCurve)
            {
               // Current segment is a circular curve.
               CComQIPtr<ICircularCurve> currHC(currVal);
               Float64 length;
               currHC->get_Length(&length);

               if (!IsZero(length))
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end = nextDist;
                  myElement.pathElement = currElement;
                  m_PathElements.push_back(myElement);

                  m_PathLength += length;
               }

               // Now add a line segment that goes from the end of this one to the
               // start of the next element
               CComPtr<IPoint2d> currEndPoint;
               currHC->get_PT(&currEndPoint);

               currDist = nextDist;

               CComPtr<IPathElement> element;
               CreateDummyPathElement(currEndPoint, nextElement, &element);

               CComPtr<IUnknown> dispDummy;
               element->get_Value(&dispDummy);
               CComQIPtr<ILineSegment2d> dummyLS(dispDummy);
               dummyLS->get_Length(&length);

               if (!IsZero(length))
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end = nextDist;
                  myElement.pathElement = element;
                  m_PathElements.push_back(myElement);

                  m_PathLength += length;
               }
            }
            else if (currType == petTransitionCurve)
            {
               // Current segment is a transition curve.
               CComQIPtr<ITransitionCurve> currHC(currVal);
               Float64 length;
               currHC->get_Length(&length);

               if (!IsZero(length))
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end = nextDist;
                  myElement.pathElement = currElement;
                  m_PathElements.push_back(myElement);

                  m_PathLength += length;
               }

               // Now add a line segment that goes from the end of this one to the
               // start of the next element
               CComPtr<IPoint2d> currEndPoint;
               currHC->get_End(&currEndPoint);

               currDist = nextDist;

               CComPtr<IPathElement> element;
               CreateDummyPathElement(currEndPoint, nextElement, &element);

               CComPtr<IUnknown> dispDummy;
               element->get_Value(&dispDummy);
               CComQIPtr<ILineSegment2d> dummyLS(dispDummy);
               dummyLS->get_Length(&length);

               if (!IsZero(length))
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end = nextDist;
                  myElement.pathElement = element;
                  m_PathElements.push_back(myElement);

                  m_PathLength += length;
               }
            }
            else if ( currType == petCompoundCurve )
            {
               // Current segment is a horz curve.
               CComQIPtr<ICompoundCurve> currHC(currVal);
               Float64 length;
               currHC->get_TotalLength(&length);
      
               if ( !IsZero(length) )
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end   = nextDist;
                  myElement.pathElement = currElement;
                  m_PathElements.push_back(myElement);
   
                  m_PathLength += length;
               }

               // Now add a line segment that goes from the end of this one to the
               // start of the next element
               CComPtr<IPoint2d> currEndPoint;
               currHC->get_ST(&currEndPoint);

               currDist = nextDist;

               CComPtr<IPathElement> element;
               CreateDummyPathElement(currEndPoint,nextElement,&element);

               CComPtr<IUnknown> dispDummy;
               element->get_Value(&dispDummy);
               CComQIPtr<ILineSegment2d> dummyLS(dispDummy);
               dummyLS->get_Length(&length);

               if ( !IsZero(length) )
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end   = nextDist;
                  myElement.pathElement = element;
                  m_PathElements.push_back(myElement);
   
                  m_PathLength += length;
               }
            }
            else if ( currType == petCubicSpline )
            {
               // Current segment is a cubic spline
               CComQIPtr<ICubicSpline> currSpline(currVal);
               Float64 length;
               currSpline->get_Length(&length);

               if ( !IsZero(length) )
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end   = nextDist;
                  myElement.pathElement = currElement;
                  m_PathElements.push_back(myElement);
   
                  m_PathLength += length;
               }

               // Now add a line segment that goes from the end of this one to the
               // start of the next element
               CComPtr<IPoint2d> currEndPoint;
               currSpline->get_EndPoint(&currEndPoint);

               currDist = nextDist;

               CComPtr<IPathElement> element;
               CreateDummyPathElement(currEndPoint,nextElement,&element);

               CComPtr<IUnknown> dispDummy;
               element->get_Value(&dispDummy);
               CComQIPtr<ILineSegment2d> dummyLS(dispDummy);
               dummyLS->get_Length(&length);

               if ( !IsZero(length) )
               {
                  nextDist += length;
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end   = nextDist;
                  myElement.pathElement = element;
                  m_PathElements.push_back(myElement);
   
                  m_PathLength += length;
               }
            }
            else
            {
               ATLASSERT(false); // Should never get here
            }

            currDist = nextDist;

         } while ( nextIter != m_coll.end() );

         // Check the last element
         // If the last element is a point, we have to create a dummy Path element, for a dummy line segment, that
         // projects the Path based on the last Path element
         CComPtr<IPathElement> lastElement;
         get_Item(m_coll.size()-1,&lastElement);

         PathElementType lastType;
         lastElement->get_Type(&lastType);

         CComPtr<IUnknown> lastVal;
         lastElement->get_Value(&lastVal);

         if ( lastType == petPoint )
         {
            // The last element is a point. We have to go back to the
            // previous element and create a line segment Path element
            CComQIPtr<IPoint2d> lastPoint(lastVal);

            CComPtr<IPathElement> prevElement;
            get_Item(m_coll.size()-2,&prevElement);

            PathElementType prevType;
            prevElement->get_Type(&prevType);

            CComPtr<IUnknown> prevVal;
            prevElement->get_Value(&prevVal);

            CComPtr<IPoint2d> prevPoint;
            if ( prevType == petPoint )
            {
               // if previous type is a point, then it projected a line
               // to this point... nothing left to do
            }
            else if (prevType == petLineSegment )
            {
               CComQIPtr<ILineSegment2d> prevLS(prevVal);
               prevLS->get_EndPoint(&prevPoint);
            }
            else if ( prevType == petCircularCurve || prevType == petTransitionCurve || prevType == petCompoundCurve )
            {
               // if previous type is a horizontal curve, then it projected a line
               // to this point... nothing left to do
            }
            else if ( prevType == petCubicSpline )
            {
               CComQIPtr<ICubicSpline> prevSpline(prevVal);
               prevSpline->get_EndPoint(&prevPoint);
            }
            else
            {
               ATLASSERT(false); // should never get nere
            }


            if ( prevPoint )
            {
               CComPtr<IDirection> dir;
               Float64 dist;
               cogoUtil::Inverse(prevPoint,lastPoint,&dist,&dir);
               currDist -= dist; // distance to the end of the second to last element

               CComPtr<IPathElement> element;
               CreateDummyPathElement(prevPoint,lastPoint,&element);

               CComPtr<IUnknown> dispDummy;
               element->get_Value(&dispDummy);
               CComQIPtr<ILineSegment2d> dummyLS(dispDummy);
               Float64 length;
               dummyLS->get_Length(&length);

               if ( !IsZero(length) )
               {
                  Element myElement;
                  myElement.start = currDist;
                  myElement.end   = myElement.start + length;
                  myElement.pathElement = element;
                  m_PathElements.push_back(myElement);
   
                  m_PathLength += length;
               }
            }
         }
         else if ( lastType == petLineSegment || lastType == petCircularCurve || lastType == petTransitionCurve || lastType == petCompoundCurve || lastType == petCubicSpline )
         {
            // The last element is a line segment, horiz curve, or spline... Simply add the last element
            Float64 length = GetElementLength(lastElement);
            Element myElement;
            myElement.start = currDist;
            myElement.end   = myElement.start + length;
            myElement.pathElement = lastElement;
            m_PathElements.push_back(myElement);
   
            m_PathLength += length;
         }
      }
   }
   return m_PathElements;
}

bool CPath::FindElement(IUnknown* pUnk,Element* pElement)
{
   auto& vElements = GetPathElements();
   for (auto& element : vElements)
   {
      CComPtr<IUnknown> pUnkValue;
      element.pathElement->get_Value(&pUnkValue);
      if (pUnkValue.IsEqualObject(pUnk))
      {
         *pElement = element;
         return true;
      }
   }

   return false;
}

void CPath::GetStartPoint(IPathElement* pElement,IPoint2d** ppStartPoint)
{
   PathElementType type;
   pElement->get_Type(&type);

   CComPtr<IUnknown> val;
   pElement->get_Value(&val);

   switch( type )
   {
   case petPoint:
      {
         CComQIPtr<IPoint2d> point(val);
         (*ppStartPoint) = point;
         (*ppStartPoint)->AddRef();
         break;
      }
   case petLineSegment:
      {
         CComQIPtr<ILineSegment2d> ls(val);
         CComPtr<IPoint2d> start;
         ls->get_StartPoint(&start);
         start.QueryInterface(ppStartPoint);
         break;
      }
   case petCircularCurve:
      {
         CComQIPtr<ICircularCurve> hc(val);
         hc->get_PC(ppStartPoint);
         break;
      }
   case petTransitionCurve:
      {
         CComQIPtr<ITransitionCurve> hc(val);
         hc->get_Start(ppStartPoint);
         break;
      }
   case petCompoundCurve:
      {
         CComQIPtr<ICompoundCurve> hc(val);
         hc->get_TS(ppStartPoint);
         break;
      }
   case petCubicSpline:
      {
         CComQIPtr<ICubicSpline> spline(val);
         spline->get_StartPoint(ppStartPoint);
         break;
      }

   default:
      ATLASSERT(false); // Should never get here
   }

}

void CPath::GetEndPoint(IPathElement* pElement,IPoint2d** ppEndPoint)
{
   PathElementType type;
   pElement->get_Type(&type);

   CComPtr<IUnknown> val;
   pElement->get_Value(&val);

   switch( type )
   {
   case petPoint:
      {
         CComQIPtr<IPoint2d> point(val);
         (*ppEndPoint) = point;
         (*ppEndPoint)->AddRef();
         break;
      }
   case petLineSegment:
      {
         CComQIPtr<ILineSegment2d> ls(val);
         CComPtr<IPoint2d> end;
         ls->get_EndPoint(&end);
         end.QueryInterface(ppEndPoint);
         break;
      }
   case petCircularCurve:
      {
         CComQIPtr<ICircularCurve> hc(val);
         hc->get_PT(ppEndPoint);
         break;
      }
   case petTransitionCurve:
      {
         CComQIPtr<ITransitionCurve> hc(val);
         hc->get_End(ppEndPoint);
         break;
      }
   case petCompoundCurve:
      {
         CComQIPtr<ICompoundCurve> hc(val);
         hc->get_ST(ppEndPoint);
         break;
      }
   case petCubicSpline:
      {
         CComQIPtr<ICubicSpline> spline(val);
         spline->get_EndPoint(ppEndPoint);
         break;
      }

   default:
      ATLASSERT(false); // Should never get here
   }

}

void CPath::CreateDummyPathElement(IPoint2d* pStart,IPoint2d* pEnd,IPathElement* *pElement)
{
   CComPtr<ILineSegment2d> dummyLS;
   dummyLS.CoCreateInstance(CLSID_LineSegment2d);
   dummyLS->putref_StartPoint(pStart);
   dummyLS->putref_EndPoint(pEnd);

   CComPtr<IPathElement> dummyElement;
   dummyElement.CoCreateInstance(CLSID_PathElement);
   dummyElement->putref_Value(dummyLS);

   (*pElement) = dummyElement;
   (*pElement)->AddRef();
}

void CPath::CreateDummyPathElement(IPoint2d* pStart,IPathElement* nextElement,IPathElement* *pElement)
{
   CComPtr<IPoint2d> nextPoint;
   GetStartPoint(nextElement,&nextPoint);
   CreateDummyPathElement(pStart,nextPoint,pElement);
}

void CPath::IntersectElement(ILine2d* line,IPathElement* element,bool bProjectBack,bool bProjectAhead,IPoint2dCollection* points)
{
   CComPtr<IUnknown> dispVal;
   element->get_Value(&dispVal);

   PathElementType type;
   element->get_Type(&type);
   ATLASSERT(type == petLineSegment || type == petCircularCurve || type == petTransitionCurve || type == petCompoundCurve || type == petCubicSpline);

   if ( type == petLineSegment )
   {
      // Projects onto a line segment
      CComQIPtr<ILineSegment2d> ls(dispVal);

      if ( !bProjectBack && !bProjectAhead )
      {
         CComPtr<IPoint2d> p;
         m_GeomUtil->IntersectLineWithLineSegment(line,ls,&p);
         if ( p )
         {
            points->Add(p);
         }

         return; // Done!
      }

      // line segment is to be projected
      // create a line from the line segment
      CComPtr<IPoint2d> start, end;
      ls->get_StartPoint(&start);
      ls->get_EndPoint(&end);

      CComPtr<ILine2d> line2;
      line2.CoCreateInstance(CLSID_Line2d);
      line2->ThroughPoints(start,end);

      // intersect lines
      CComPtr<IPoint2d> p;
      m_GeomUtil->LineLineIntersect(line,line2,&p);

      if ( p )
      {
         bool bBeforeStart = cogoUtil::IsPointBeforeStart(start,end,p);
         bool bAfterEnd    = cogoUtil::IsPointAfterEnd(start,end,p);
         if ( start->SameLocation(p) == S_OK ||
              end->SameLocation(p)   == S_OK ||
              (bBeforeStart && bProjectBack) || 
              (bAfterEnd && bProjectAhead)   || 
              (!bBeforeStart && !bAfterEnd) )
         {
            points->Add(p);
         }
      }
   }
   else if (type == petCircularCurve)
   {
      // Projects onto a horizontal curve
      CComQIPtr<ICircularCurve> hc(dispVal);

      CComPtr<IPoint2d> p1, p2;
      hc->Intersect(line,
         bProjectBack ? VARIANT_TRUE : VARIANT_FALSE,
         bProjectAhead ? VARIANT_TRUE : VARIANT_FALSE,
         &p1, &p2);

      if (p1)
      {
         points->Add(p1);
      }

      if (p2)
      {
         points->Add(p2);
      }
   }
   else if (type == petTransitionCurve)
   {
      // Projects onto a horizontal curve
      CComQIPtr<ITransitionCurve> hc(dispVal);

      CComPtr<IPoint2dCollection> intersection_points;
      hc->Intersect(line,
         bProjectBack ? VARIANT_TRUE : VARIANT_FALSE,
         bProjectAhead ? VARIANT_TRUE : VARIANT_FALSE,
         &intersection_points);

      IndexType nPoints;
      intersection_points->get_Count(&nPoints);
      for (IndexType i = 0; i < nPoints; i++)
      {
         CComPtr<IPoint2d> point;
         intersection_points->get_Item(i, &point);
         points->Add(point);
      }
   }
   else if ( type == petCompoundCurve )
   {
      // Projects onto a horizontal curve
      CComQIPtr<ICompoundCurve> hc(dispVal);

      CComPtr<IPoint2d> p1,p2;
      hc->Intersect(line, 
                    bProjectBack  ? VARIANT_TRUE : VARIANT_FALSE, 
                    bProjectAhead ? VARIANT_TRUE : VARIANT_FALSE, 
                    &p1, &p2);

      if ( p1 )
      {
         points->Add(p1);
      }

      if ( p2 )
      {
         points->Add(p2);
      }
   }
   else if ( type == petCubicSpline )
   {
      // Projects onto a cubic spline
      CComQIPtr<ICubicSpline> spline(dispVal);

      CComPtr<IPoint2dCollection> intPoints;
      spline->Intersect(line, 
                        bProjectBack  ? VARIANT_TRUE : VARIANT_FALSE, 
                        bProjectAhead ? VARIANT_TRUE : VARIANT_FALSE, 
                        &intPoints);

      CollectionIndexType nPoints;
      intPoints->get_Count(&nPoints);
      for ( CollectionIndexType i = 0; i < nPoints; i++ )
      {
         CComPtr<IPoint2d> p;
         intPoints->get_Item(i,&p);
         points->Add(p);
      }
   }
}

void CPath::ProjectPointOnElement(IPoint2d* point,IPathElement* pElement,IPoint2d** pNewPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection)
{
   CComPtr<IUnknown> dispVal;
   pElement->get_Value(&dispVal);

   PathElementType type;
   pElement->get_Type(&type);
   ATLASSERT(type == petLineSegment || type == petCircularCurve || type == petTransitionCurve || type == petCompoundCurve || type == petCubicSpline);

   if (type == petLineSegment)
   {
      // Projects onto a line segment
      CComQIPtr<ILineSegment2d> ls(dispVal);

      CComPtr<IPoint2d> start, end;
      ls->get_StartPoint(&start);
      ls->get_EndPoint(&end);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      if (SUCCEEDED(line->ThroughPoints(start, end)))
      {
         CComPtr<IPoint2d> p;
         m_GeomUtil->PointOnLineNearest(line, point, &p);
         if (p->SameLocation(start) == S_OK)
         {
            p->MoveEx(start);
         }
         else if (p->SameLocation(end) == S_OK)
         {
            p->MoveEx(end);
         }
         (*pNewPoint) = p;
         (*pNewPoint)->AddRef();

         start->DistanceEx(p, pDistFromStart);
         bool bBeforeStart = cogoUtil::IsPointBeforeStart(start, end, p);
         bool bAfterEnd = cogoUtil::IsPointAfterEnd(start, end, p);
         if(bBeforeStart)
         {
            *pDistFromStart *= -1; // negative because it is before start (but distance is always an absolute value)
            *pvbOnProjection = VARIANT_TRUE;
         }
         else if (bAfterEnd)
         {
            *pvbOnProjection = VARIANT_TRUE;
         }
         else
         {
            *pvbOnProjection = VARIANT_FALSE;
         }
      }
      else
      {
         // the only way we get here is if start and end are the same point
         // if that is the case, the point always projects to the start
         ATLASSERT(start->SameLocation(end) == S_OK);
         start->Clone(pNewPoint);
         *pDistFromStart = 0.0;
         *pvbOnProjection = VARIANT_FALSE;
      }
   }
   else if (type == petCircularCurve)
   {
      // Projects onto a horizontal curve
      CComQIPtr<ICircularCurve> hc(dispVal);
      hc->ProjectPoint(point, pNewPoint, pDistFromStart, pvbOnProjection);
   }
   else if (type == petTransitionCurve)
   {
      // Projects onto a horizontal curve
      CComQIPtr<ITransitionCurve> hc(dispVal);
      hc->ProjectPoint(point, pNewPoint, pDistFromStart, pvbOnProjection);
   }
   else if (type == petCompoundCurve)
   {
      // Projects onto a horizontal curve
      CComQIPtr<ICompoundCurve> hc(dispVal);
      hc->ProjectPoint(point, pNewPoint, pDistFromStart, pvbOnProjection);
   }
   else if (type == petCubicSpline)
   {
      CComQIPtr<ICubicSpline> spline(dispVal);
      spline->ProjectPoint(point, pNewPoint, pDistFromStart, pvbOnProjection);
   }
   else
   {
      ATLASSERT(false); // should never get here
   }
}

STDMETHODIMP CPath::Clone(IPath* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CPath>* pClone;
   CComObject<CPath>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IEnumPathElements> enumPathElements;
   get__EnumPathElements(&enumPathElements);
   CComPtr<IPathElement> path_element;
   while ( enumPathElements->Next(1,&path_element,nullptr) != S_FALSE )
   {
      CComPtr<IPathElement> clonePE;
      path_element->Clone(&clonePE);

      (*clone)->Add(clonePE);

      path_element.Release();
   };

   return S_OK;
}

STDMETHODIMP CPath::CreateOffsetPath(Float64 offset,IPath** path)
{
   CHECK_RETOBJ(path);

   // if the offset is zero, the parallel path is just a copy of this path
   if ( IsZero(offset) )
   {
      return Clone(path);
   }

   // +offset = right
   // -offset = left

   CComObject<CPath>* pClone;
   CComObject<CPath>::CreateInstance(&pClone);

   (*path) = pClone;
   (*path)->AddRef();

   std::vector<Element>& vElements = GetPathElements();
   const auto& begin = vElements.cbegin();
   auto& iter = vElements.cbegin();
   const auto& end = vElements.cend();
   for (; iter != end; iter++)
   {
      const auto& element(*iter);

      CComPtr<IPathElement> prev_path_element;
      if (iter != begin)
      {
         prev_path_element = (iter - 1)->pathElement;
      }

      CComPtr<IPathElement> path_element = element.pathElement;

      CComPtr<IPathElement> next_path_element;
      if (iter + 1 != end)
      {
         next_path_element = (iter + 1)->pathElement;
      }

      // clone the path element
      CComPtr<IPathElement> clonePE;
      path_element->Clone(&clonePE);

      // now modify it so that it is offset and parallel to the original
      PathElementType type;
      clonePE->get_Type(&type);
      CComPtr<IUnknown> punk;
      clonePE->get_Value(&punk);
      switch(type)
      {
      case petPoint:
         {
            ATLASSERT(false); // should never get here
         }
         break;

      case petLineSegment:
         {
            CComQIPtr<ILineSegment2d> ls(punk);
            CComPtr<IPoint2d> start;
            CComPtr<IPoint2d> end;
            ls->get_StartPoint(&start);
            ls->get_EndPoint(&end);

            Float64 sx,sy;
            Float64 ex,ey;
            start->Location(&sx,&sy);
            end->Location(&ex,&ey);

            Float64 dir = atan2(ey - sy, ex - sx);

            Float64 dxStart, dyStart;
            Float64 dxEnd, dyEnd;

            dxStart = offset*sin(dir);
            dyStart = -offset*cos(dir);

            dxEnd = dxStart;
            dyEnd = dyStart;

            if (prev_path_element)
            {
               // if previous path element is a line segment, we need to adjust the offset
               // distance and direction to be along a line that is half-way between
               // the previous and this line segment.
               PathElementType prevElementType;
               prev_path_element->get_Type(&prevElementType);
               if (prevElementType == petLineSegment)
               {
                  CComPtr<IUnknown> prev_element_punk;
                  prev_path_element->get_Value(&prev_element_punk);
                  CComQIPtr<ILineSegment2d> prev_ls(prev_element_punk);

                  CComPtr<IPoint2d> prevStart, prevEnd;
                  prev_ls->get_StartPoint(&prevStart);
                  prev_ls->get_EndPoint(&prevEnd);

                  Float64 psx, psy;
                  Float64 pex, pey;
                  prevStart->Location(&psx, &psy);
                  prevEnd->Location(&pex, &pey);
                  Float64 dirPrev = atan2(pey - psy, pex - psx);

                  Float64 dirOffset = PI_OVER_2 + 0.5*(dir + dirPrev);

                  Float64 adjOffset = offset / cos(0.5*(dir - dirPrev));

                  dxStart = -adjOffset*cos(dirOffset);
                  dyStart = -adjOffset*sin(dirOffset);
               }
            }

            if (next_path_element)
            {
               // if next path element is a line segment, we need to adjust the offset
               // distance and direction to be along a line that is half-way between
               // the this and the next line segment.
               PathElementType nextElementType;
               next_path_element->get_Type(&nextElementType);
               if (nextElementType == petLineSegment)
               {
                  CComPtr<IUnknown> next_element_punk;
                  next_path_element->get_Value(&next_element_punk);
                  CComQIPtr<ILineSegment2d> next_ls(next_element_punk);

                  CComPtr<IPoint2d> nextStart, nextEnd;
                  next_ls->get_StartPoint(&nextStart);
                  next_ls->get_EndPoint(&nextEnd);

                  Float64 nsx, nsy;
                  Float64 nex, ney;
                  nextStart->Location(&nsx, &nsy);
                  nextEnd->Location(&nex, &ney);
                  Float64 dirNext = atan2(ney - nsy, nex - nsx);

                  Float64 dirOffset = PI_OVER_2 + 0.5*(dir + dirNext);

                  Float64 adjOffset = offset / cos(0.5*(dirNext - dir));

                  dxEnd = -adjOffset*cos(dirOffset);
                  dyEnd = -adjOffset*sin(dirOffset);
               }
            }
   
            start->Offset(dxStart, dyStart);
            end->Offset(dxEnd, dyEnd);
            ls->ThroughPoints(start, end);
         }
         break;

      case petCircularCurve:
         {
            CComQIPtr<ICircularCurve> hc(punk);
            CComPtr<IUnknown> result;
            CreateOffsetCircularCurve(offset, hc, &result);
            CComQIPtr<IUnkArray> unkArray(result);
            if (unkArray)
            {
               clonePE.Release();
               IndexType nItems;
               unkArray->get_Count(&nItems);
               for (IndexType i = 0; i < nItems; i++)
               {
                  CComPtr<IUnknown> unk;
                  unkArray->get_Item(i, &unk);
                  (*path)->AddEx(unk);
               }
            }
            else
            {
               clonePE->putref_Value(result);
            }
         }
         break;

      case petTransitionCurve:
         {
            CComQIPtr<ITransitionCurve> hc(punk);
            CComPtr<IUnknown> result;
            CreateOffsetTransitionCurve(offset, hc, &result);
            CComQIPtr<IUnkArray> unkArray(result);
            if (unkArray)
            {
               clonePE.Release();
               IndexType nItems;
               unkArray->get_Count(&nItems);
               for (IndexType i = 0; i < nItems; i++)
               {
                  CComPtr<IUnknown> unk;
                  unkArray->get_Item(i, &unk);
                  (*path)->AddEx(unk);
               }
            }
            else
            {
               clonePE->putref_Value(result);
            }
         }
         break;

      case petCompoundCurve:
         {
            CComQIPtr<ICompoundCurve> hc(punk);
            CComPtr<IUnknown> result;
            CreateOffsetCompoundCurve(offset,hc,&result);
            CComQIPtr<IUnkArray> unkArray(result);
            if (unkArray)
            {
               clonePE.Release();
               IndexType nItems;
               unkArray->get_Count(&nItems);
               for (IndexType i = 0; i < nItems; i++)
               {
                  CComPtr<IUnknown> unk;
                  unkArray->get_Item(i, &unk);
                  (*path)->AddEx(unk);
               }
            }
            else
            {
               clonePE->putref_Value(result);
            }
         }
         break;

      case petCubicSpline:
         {
            CComQIPtr<ICubicSpline> spline(punk);
            CComPtr<IUnknown> result;
            CreateOffsetCubicSpline(offset,spline,&result);
            clonePE->putref_Value(result);
         }
         break;

      default:
         ATLASSERT(false); // should never get here
         break;
      }

      (*path)->Add(clonePE);

      path_element.Release();
   }

   return S_OK;
}

STDMETHODIMP CPath::CreateConnectedPath(IPath** path)
{
   // creates a path object that is exactly the same as this one,
   // except that all the gaps are filled with line segments.
   // the resulting path will consist of only line segments and curves
   CComObject<CPath>* pClone;
   CComObject<CPath>::CreateInstance(&pClone);

   (*path) = pClone;
   (*path)->AddRef();

   std::vector<Element>& vElements = GetPathElements();
   for (const auto& element : vElements)
   {
      CComPtr<IPathElement> path_element = element.pathElement;

#if defined _DEBUG
      PathElementType type;
      path_element->get_Type(&type);
      ATLASSERT(type != petPoint);
#endif

      (*path)->Add(path_element);
   }

   return S_OK;
}

STDMETHODIMP CPath::CreateSubPath(Float64 start,Float64 end,IPath** path)
{
   CHECK_RETOBJ(path);

   CComObject<CPath>* pClone;
   CComObject<CPath>::CreateInstance(&pClone);

   (*path) = pClone;
   (*path)->AddRef();

   std::vector<Element>& vElements = GetPathElements();
   for (const auto& element : vElements)
   {
      CComPtr<IPathElement> path_element = element.pathElement;

      PathElementType type;
      path_element->get_Type(&type);
      CComPtr<IUnknown> punk;
      path_element->get_Value(&punk);

      HRESULT hr;
      switch(type)
      {
      case petPoint:
         {
            ATLASSERT(false); // should never be a point
         }
         break;

      case petLineSegment:
         {
            CComQIPtr<ILineSegment2d> ls(punk);
            CComPtr<ILineSegment2d> newLS;
            hr = CreateSubPathElement(start,end,ls,&newLS);
            if ( SUCCEEDED(hr) )
            {
               SavePathElement(*path,newLS);
            }
         }
         break;

      case petCircularCurve:
      {
         CComQIPtr<ICircularCurve> hc(punk);
         CComPtr<IUnknown> result;
         hr = CreateSubPathElement(start, end, hc, &result);
         if (SUCCEEDED(hr))
         {
            SavePathElement(*path, result);
         }
      }
      break;

      case petTransitionCurve:
      {
         CComQIPtr<ITransitionCurve> hc(punk);
         CComPtr<IUnknown> result;
         hr = CreateSubPathElement(start, end, hc, &result);
         if (SUCCEEDED(hr))
         {
            SavePathElement(*path, result);
         }
      }
      break;

      case petCompoundCurve:
         {
            CComQIPtr<ICompoundCurve> hc(punk);
            CComPtr<IUnknown> result1,result2,result3;
            hr = CreateSubPathElement(start,end,hc,&result1,&result2,&result3);
            if ( SUCCEEDED(hr) )
            {
               if ( result1 )
               {
                  SavePathElement(*path,result1);
               }

               if ( result2 )
               {
                  SavePathElement(*path,result2);
               }

               if ( result3 )
               {
                  SavePathElement(*path,result3);
               }
            }
         }
         break;

      case petCubicSpline:
         {
            CComQIPtr<ICubicSpline> spline(punk);
            CComPtr<IUnknown> result;
            hr = CreateSubPathElement(start,end,spline,&result);
            if ( SUCCEEDED(hr) )
            {
               SavePathElement(*path,result);
            }
         }
         break;

      default:
         ATLASSERT(false); // should never get here
         break;
      }


      path_element.Release();
   }

   // if none of the elements contribute to the sub-path, create a sub-path with
   // a point at the start and end of the sub-path range.
   CollectionIndexType nElements;
   (*path)->get_Count(&nElements);
   if ( nElements == 0 )
   {
      CComPtr<IPoint2d> p1, p2;
      LocatePoint(start,omtNormal,0.0,CComVariant(0.0),&p1);
      LocatePoint(end,  omtNormal,0.0,CComVariant(0.0),&p2);

      SavePathElement(*path,p1);
      SavePathElement(*path,p2);
   }

   return S_OK;
}

STDMETHODIMP CPath::Move(Float64 dist,IDirection* direction)
{
   CHECK_IN(direction);

   Float64 angle;
   direction->get_Value(&angle);
   Float64 dx, dy;
   dx = dist*cos(angle);
   dy = dist*sin(angle);

   dx = ::IsZero(dx) ? 0 : dx;
   dy = ::IsZero(dy) ? 0 : dy;

   // adjust the cached elements. the cached elements have references to the input elements so moving the cached elements
   // that directly relate to an input element moves the input element as well
   //
   // We can't just simply over the elements because some adjacent elements may share common points.
   // For example, there may be a common point between two line segments. We can't offset the two line
   // segments by dx and dy because the commont point will be offset twice.
   //
   // The solution is to get the control points for every element and offset the control points
   // The set is devised such that only unique points are captured
   std::vector<CComPtr<IPoint2d>> points;
   std::vector<Element>& vElements = GetPathElements();
   for (const auto& element : vElements)
   {
      CComPtr<IPathElement> path_element = element.pathElement;
      CPathElement* pPathElement = dynamic_cast<CPathElement*>(path_element.p);
      pPathElement->GetControlPoints(points);
   }

   std::sort(points.begin(), points.end());
   points.erase(std::unique(points.begin(), points.end(), [](auto p1, auto p2) {return p1.IsEqualObject(p2); }), points.end());

   for (auto& point : points)
   {
      point->Offset(dx, dy);
   }

   Fire_OnPathChanged(this);

   return S_OK;
}

STDMETHODIMP CPath::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CPath::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("Path"),1.0);
   
   pSave->BeginUnit(CComBSTR("PathElements"),1.0);
   CollectionIndexType count = m_coll.size();
   pSave->put_Property(CComBSTR("Count"),CComVariant(count));
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      pSave->put_Property(CComBSTR("PathElement"),m_coll[i]);
   }
   pSave->EndUnit(); // PathElements

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CPath::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Path"));

   pLoad->BeginUnit(CComBSTR("PathElements"));
   pLoad->get_Property(CComBSTR("Count"),&var);
   CollectionIndexType count = var.iVal;

   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      pLoad->get_Property(CComBSTR("PathElement"),&var);
      CComPtr<IPathElement> element;
      _CopyVariantToInterface<IPathElement>::copy(&element,&var);
      Add(element);
   }
   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd); // PathElements

   pLoad->EndUnit(&bEnd);

   return S_OK;
}

void CPath::CreateOffsetCircularCurve(Float64 offset, ICircularCurve* hc, IUnknown** result)
{
   CurveDirectionType curve_direction;
   hc->get_Direction(&curve_direction);

   CComPtr<IPoint2d> PC, CC, PT;
   hc->get_PC(&PC);
   hc->get_Center(&CC);
   hc->get_PT(&PT);

   Float64 d1, d2;
   PC->DistanceEx(CC, &d1);
   PT->DistanceEx(CC, &d2);

   // It is useful to have line objects that represent the tangents of the curve.
   // Create them now because they will be used later.
   CComPtr<IPoint2d> PBT, PI, PFT;
   hc->get_PBT(&PBT);
   hc->get_PI(&PI);
   hc->get_PFT(&PFT);

   CComPtr<ILine2d> l1, l2;
   l1.CoCreateInstance(CLSID_Line2d);
   l2.CoCreateInstance(CLSID_Line2d);

   l1->ThroughPoints(PBT, PI);
   l2->ThroughPoints(PI, PFT);

   // Deal with the case of the curve degrading to a single point
   if ((curve_direction == cdRight && (d1 <= offset || d2 <= offset)) ||
      (curve_direction == cdLeft && (d1 <= -offset || d2 <= -offset)))
   {
      // The parallel curve is past the CC point... this degrades the curve to a point

      // offset the curve tangents and intersect them
      l1->Offset(-offset);
      l2->Offset(-offset);

      CComPtr<IPoint2d> point;
      m_GeomUtil->LineLineIntersect(l1, l2, &point);

      (*result) = point;
      (*result)->AddRef();
      return;
   }


   //
   // Curve remains a curve
   //
   CComPtr<IUnkArray> unkArray;
   unkArray.CoCreateInstance(CLSID_UnkArray);

   // Use the curve tangents to create new tangents at an offset. The intersection point of these lines is the new PI.
   CComPtr<ILine2d> bkTangent, fwdTangent;
   m_GeomUtil->CreateParallelLine(l1, offset, &bkTangent);
   m_GeomUtil->CreateParallelLine(l2, offset, &fwdTangent);

   CComPtr<IPoint2d> newPI;
   m_GeomUtil->LineLineIntersect(bkTangent, fwdTangent, &newPI);

   CComPtr<IPoint2d> newPBT, newPFT;
   m_GeomUtil->PointOnLineNearest(bkTangent, PC, &newPBT);
   m_GeomUtil->PointOnLineNearest(fwdTangent, PT, &newPFT);

   // compute new circular curve radius
   Float64 radius;
   hc->get_Radius(&radius);

   CComPtr<ICircularCurve> offset_curve;
   offset_curve.CoCreateInstance(CLSID_CircularCurve);
   Float64 newRadius = (curve_direction == cdRight ? radius - offset : radius + offset);
   offset_curve->putref_PBT(newPBT);
   offset_curve->putref_PI(newPI);
   offset_curve->putref_PFT(newPFT);

   offset_curve->put_Radius(newRadius);

#if defined _DEBUG
   CComPtr<IPoint2d> _cc;
   offset_curve->get_Center(&_cc);
   ATLASSERT(CC->SameLocation(_cc) == S_OK);

   CComPtr<IAngle> delta_angle;
   hc->get_Angle(&delta_angle);
   Float64 delta;
   delta_angle->get_Value(&delta);

   CComPtr<IAngle> _delta_angle;
   offset_curve->get_Angle(&_delta_angle);
   Float64 _delta;
   _delta_angle->get_Value(&_delta);

   ATLASSERT(IsEqual(delta, _delta));
#endif

   unkArray->Add(offset_curve);


   (*result) = unkArray;
   (*result)->AddRef();
}

void CPath::CreateOffsetTransitionCurve(Float64 offset, ITransitionCurve* hc, IUnknown** result)
{
   // determine if the curve degrades to a point

   CurveDirectionType curve_direction;
   hc->get_Direction(&curve_direction);

   // create lines that are normal to the start and end of curve and find their intersection point
   CComPtr<IPoint2d> pntStart, pntEnd;
   hc->get_Start(&pntStart);
   hc->get_End(&pntEnd);

   CComPtr<IDirection> dirStart, dirEnd;
   hc->get_StartDirection(&dirStart);
   hc->get_EndDirection(&dirEnd);
   Float64 start_dir, end_dir;
   dirStart->get_Value(&start_dir);
   dirEnd->get_Value(&end_dir);

   CComPtr<IVector2d> vStart;
   vStart.CoCreateInstance(CLSID_Vector2d);
   vStart->put_Direction(start_dir + PI_OVER_2);

   CComPtr<IVector2d> vEnd;
   vEnd.CoCreateInstance(CLSID_Vector2d);
   vEnd->put_Direction(end_dir + PI_OVER_2);

   CComPtr<ILine2d> start_normal_line;
   start_normal_line.CoCreateInstance(CLSID_Line2d);
   start_normal_line->SetExplicit(pntStart, vStart);

   CComPtr<ILine2d> end_normal_line;
   end_normal_line.CoCreateInstance(CLSID_Line2d);
   end_normal_line->SetExplicit(pntEnd, vEnd);

   CComPtr<IPoint2d> cc;
   geomUtil::LineLineIntersect(start_normal_line, end_normal_line, &cc);

   // find distance from start and end to the intersection point
   Float64 d1, d2;
   pntStart->DistanceEx(cc, &d1);
   pntEnd->DistanceEx(cc, &d2);

   // Deal with the case of the curve degrading to a single point
   if ((curve_direction == cdRight && (d1 <= offset || d2 <= offset)) ||
      (curve_direction == cdLeft && (d1 <= -offset || d2 <= -offset)))
   {
      // The parallel curve is past the CC point... this degrades the curve to a point

      CComPtr<IPoint2d> PI;
      hc->get_PI(&PI);

      CComPtr<ILine2d> l1, l2;
      l1.CoCreateInstance(CLSID_Line2d);
      l2.CoCreateInstance(CLSID_Line2d);

      l1->ThroughPoints(pntStart, PI);
      l2->ThroughPoints(PI, pntEnd);

      // offset the curve tangents and intersect them
      l1->Offset(-offset);
      l2->Offset(-offset);

      CComPtr<IPoint2d> point;
      m_GeomUtil->LineLineIntersect(l1, l2, &point);

      (*result) = point;
      (*result)->AddRef();
      return;
   }


   //
   // Curve remains a curve
   //
   CComPtr<IUnkArray> unkArray;
   unkArray.CoCreateInstance(CLSID_UnkArray);

   IndexType nPoints = 10;

   Float64 Ls;
   hc->get_Length(&Ls);

   CComPtr<IAngle> spAngle;
   hc->get_Angle(&spAngle);
   Float64 angle;
   spAngle->get_Value(&angle);
   if (PI_OVER_2 < angle)
   {
      CComPtr<ICubicSpline> spline1;
      CreateSubCurveSpline(0.0, Ls / 2, nPoints, hc, &spline1);
      CComPtr<IUnknown> offset_spline1;
      CreateOffsetCubicSpline(offset, spline1, &offset_spline1);
      unkArray->Add(offset_spline1);

      CComPtr<ICubicSpline> spline2;
      CreateSubCurveSpline(Ls / 2, Ls, nPoints, hc, &spline2);
      CComPtr<IUnknown> offset_spline2;
      CreateOffsetCubicSpline(offset, spline2, &offset_spline2);
      unkArray->Add(offset_spline2);
   }
   else
   {
      CComPtr<ICubicSpline> spline;
      CreateSubCurveSpline(0.0, Ls, nPoints, hc, &spline);
      CComPtr<IUnknown> offset_spline;
      CreateOffsetCubicSpline(offset, spline, &offset_spline);
      unkArray->Add(offset_spline);
   }

   (*result) = unkArray;
   (*result)->AddRef();
}

void CPath::CreateOffsetCompoundCurve(Float64 offset,ICompoundCurve* hc,IUnknown** result)
{
   CurveDirectionType curve_direction;
   hc->get_Direction(&curve_direction);

   CComPtr<IPoint2d> TS, CC, ST;
   hc->get_TS(&TS);
   hc->get_CC(&CC);
   hc->get_ST(&ST);

   Float64 d1,d2;
   TS->DistanceEx(CC, &d1);
   ST->DistanceEx(CC, &d2);

   // It is useful to have line objects that represent the tangents of the curve.
   // Create them now because they will be used later.
   CComPtr<IPoint2d> PBT, PI, PFT;
   hc->get_PBT(&PBT);
   hc->get_PI(&PI);
   hc->get_PFT(&PFT);

   CComPtr<ILine2d> l1, l2;
   l1.CoCreateInstance(CLSID_Line2d);
   l2.CoCreateInstance(CLSID_Line2d);

   l1->ThroughPoints(PBT,PI);
   l2->ThroughPoints(PI,PFT);

   // Deal with the case of the curve degrading to a single point
   if ( ( curve_direction == cdRight && (d1 <=  offset || d2 <=  offset )) ||
        ( curve_direction == cdLeft  && (d1 <= -offset || d2 <= -offset )) )
   {
      // The parallel curve is past the CC point... this degrades the curve to a point

      // offset the curve tangents and intersect them
      l1->Offset(-offset);
      l2->Offset(-offset);

      CComPtr<IPoint2d> point;
      m_GeomUtil->LineLineIntersect(l1,l2,&point);

      (*result) = point;
      (*result)->AddRef();
      return;
   }


   //
   // Curve remains a curve
   //
   CComPtr<IUnkArray> unkArray;
   unkArray.CoCreateInstance(CLSID_UnkArray);

   IndexType nPoints = 10;

   //
   // Entry spiral
   //
   Float64 LsEntry;
   hc->get_SpiralLength(spEntry, &LsEntry);
   if (0 < LsEntry)
   {
      CComPtr<IAngle> spAngle;
      hc->get_SpiralAngle(spEntry, &spAngle);
      Float64 angle;
      spAngle->get_Value(&angle);
      if (PI_OVER_2 < angle)
      {
         CComPtr<ICubicSpline> spline1;
         CreateSubCurveSpline(0.0, LsEntry / 2, nPoints, hc, &spline1);
         CComPtr<IUnknown> offset_spline1;
         CreateOffsetCubicSpline(offset, spline1, &offset_spline1);
         unkArray->Add(offset_spline1);

         CComPtr<ICubicSpline> spline2;
         CreateSubCurveSpline(LsEntry /2, LsEntry, nPoints, hc, &spline2);
         CComPtr<IUnknown> offset_spline2;
         CreateOffsetCubicSpline(offset, spline2, &offset_spline2);
         unkArray->Add(offset_spline2);
      }
      else
      {
         CComPtr<ICubicSpline> spline;
         CreateSubCurveSpline(0.0, LsEntry, nPoints, hc, &spline);
         CComPtr<IUnknown> offset_spline;
         CreateOffsetCubicSpline(offset, spline, &offset_spline);
         unkArray->Add(offset_spline);
      }
   }

   //
   // Circular Curve
   //

   // Create lines parallel to the tangents of the circular curve. The intersection point of these lines is the new PI.
   CComPtr<IPoint2d> SC, PCI, CS;
   hc->get_SC(&SC);
   hc->get_PCI(&PCI);
   hc->get_CS(&CS);

   l1->ThroughPoints(SC, PCI);
   l2->ThroughPoints(PCI, CS);

   CComPtr<ILine2d> bkTangent, fwdTangent;
   m_GeomUtil->CreateParallelLine(l1,offset,&bkTangent);
   m_GeomUtil->CreateParallelLine(l2,offset,&fwdTangent);
   
   CComPtr<IPoint2d> newPI;
   m_GeomUtil->LineLineIntersect(bkTangent,fwdTangent,&newPI);
   
   CComPtr<IPoint2d> newPBT, newPFT;
   m_GeomUtil->PointOnLineNearest(bkTangent, SC,&newPBT);
   m_GeomUtil->PointOnLineNearest(fwdTangent,CS,&newPFT);
   
   // compute new circular curve radius
   Float64 radius;
   hc->get_Radius(&radius);

   CComPtr<ICompoundCurve> offset_curve;
   offset_curve.CoCreateInstance(CLSID_CompoundCurve);
   Float64 newRadius = (curve_direction == cdRight ? radius - offset : radius + offset);
   offset_curve->putref_PBT(newPBT);
   offset_curve->putref_PI(newPI);
   offset_curve->putref_PFT(newPFT);
   
   offset_curve->put_Radius(newRadius);

#if defined _DEBUG
   CComPtr<IPoint2d> ccc;
   hc->get_CCC(&ccc);

   CComPtr<IPoint2d> _ccc;
   offset_curve->get_CCC(&_ccc);
   ATLASSERT(ccc->SameLocation(_ccc) == S_OK);

   CComPtr<IAngle> delta_angle;
   hc->get_CircularCurveAngle(&delta_angle);
   Float64 delta;
   delta_angle->get_Value(&delta);

   CComPtr<IAngle> _delta_angle;
   offset_curve->get_CircularCurveAngle(&_delta_angle);
   Float64 _delta;
   _delta_angle->get_Value(&_delta);

   ATLASSERT(IsEqual(delta, _delta));
   
   CComPtr<IPoint2d> _SC, _CS;
   offset_curve->get_SC(&_SC);
   offset_curve->get_CS(&_CS);
#endif

   unkArray->Add(offset_curve);

   //
   // Exit spiral
   //
   Float64 LsExit;
   hc->get_SpiralLength(spExit, &LsExit);
   if (0 < LsExit)
   {
      Float64 L;
      hc->get_CurveLength(&L);

      CComPtr<IAngle> spAngle;
      hc->get_SpiralAngle(spExit, &spAngle);
      Float64 angle;
      spAngle->get_Value(&angle);
      if (PI_OVER_2 < angle)
      {
         CComPtr<ICubicSpline> spline1;
         CreateSubCurveSpline(LsEntry + L, LsEntry + L + LsExit/2, nPoints, hc, &spline1);
         CComPtr<IUnknown> offset_spline1;
         CreateOffsetCubicSpline(offset, spline1, &offset_spline1);
         unkArray->Add(offset_spline1);

         CComPtr<ICubicSpline> spline2;
         CreateSubCurveSpline(LsEntry + L + LsExit / 2, LsEntry + L + LsExit, nPoints, hc, &spline2);
         CComPtr<IUnknown> offset_spline2;
         CreateOffsetCubicSpline(offset, spline2, &offset_spline2);
         unkArray->Add(offset_spline2);
      }
      else
      {
         CComPtr<ICubicSpline> spline;
         CreateSubCurveSpline(LsEntry + L, LsEntry + L + LsExit, nPoints, hc, &spline);
         CComPtr<IUnknown> offset_spline;
         CreateOffsetCubicSpline(offset, spline, &offset_spline);
         unkArray->Add(offset_spline);
      }
   }

   (*result) = unkArray;
   (*result)->AddRef();
}

void CPath::CreateOffsetCubicSpline(Float64 offset,ICubicSpline* spline,IUnknown** result)
{
   // get all the points that define the spline
   CComPtr<IPoint2dCollection> points;
   spline->get_Points(&points);

   CollectionIndexType nPoints;
   points->get_Count(&nPoints);

   // locate each spline point
   CComQIPtr<ILocate2> locate(m_CogoEngine);
   CComPtr<IPoint2dCollection> newPoints;
   newPoints.CoCreateInstance(CLSID_Point2dCollection);
   for ( CollectionIndexType i = 0; i < nPoints; i++ )
   {
      CComPtr<IDirection> dir;
      spline->BearingAtPoint(i,&dir);

      CComPtr<IPoint2d> p;
      points->get_Item(i,&p);

      CComPtr<IPoint2d> newPoint;
      locate->ByDistDir(p,0.00,CComVariant(dir),offset,&newPoint);

      newPoints->Add(newPoint);
   }

   spline->Clear();
   spline->AddPoints(newPoints);

   (*result) = spline;
   (*result)->AddRef();
}

void CPath::CreateOffsetPoint(CollectionIndexType elementIdx,Float64 offset,IPoint2d** pPoint)
{
   CComPtr<IPoint2d> prevPoint, nextPoint;

   if ( elementIdx != 0 )
   {
      // there is an element before this one... get its end point
      CComPtr<IPathElement> prevElement;
      get_Item(elementIdx-1,&prevElement);
      GetEndPoint(prevElement,&prevPoint);
   }

   CComPtr<IPathElement> nextElement;
   get_Item(elementIdx+1,&nextElement);
   if ( nextElement )
   {
      GetStartPoint(nextElement,&nextPoint);
   }

   if (prevPoint == nullptr && nextPoint == nullptr )
   {
      // nothing before or after this point, assume straight line due East
      (*pPoint)->Offset(0,offset);
   }
   else if ( prevPoint != nullptr && nextPoint != nullptr )
   {
      CComPtr<ILine2d> l1,l2;
      l1.CoCreateInstance(CLSID_Line2d);
      l2.CoCreateInstance(CLSID_Line2d);

      l1->ThroughPoints(prevPoint,*pPoint);
      l2->ThroughPoints(*pPoint,nextPoint);

      CComPtr<ILine2d> line1,line2;
      m_GeomUtil->CreateParallelLine(l1,offset,&line1);
      m_GeomUtil->CreateParallelLine(l2,offset,&line2);

      CComPtr<IPoint2d> pnt;
      m_GeomUtil->LineLineIntersect(line1,line2,&pnt);
      Float64 x,y;
      pnt->Location(&x,&y);
      (*pPoint)->Move(x,y);
   }
   else if ( prevPoint == nullptr && nextPoint != nullptr )
   {
      CComPtr<ILine2d> l;
      l.CoCreateInstance(CLSID_Line2d);
      l->ThroughPoints(*pPoint,nextPoint);

      CComPtr<ILine2d> line;
      m_GeomUtil->CreateParallelLine(l,offset,&line);

      CComPtr<IPoint2d> pnt;
      m_GeomUtil->PointOnLineNearest(line,*pPoint,&pnt);
      Float64 x,y;
      pnt->Location(&x,&y);
      (*pPoint)->Move(x,y);
   }
   else if ( prevPoint != nullptr && nextPoint == nullptr )
   {
      CComPtr<ILine2d> l;
      l.CoCreateInstance(CLSID_Line2d);
      l->ThroughPoints(prevPoint,*pPoint);

      CComPtr<ILine2d> line;
      m_GeomUtil->CreateParallelLine(l,offset,&line);

      CComPtr<IPoint2d> pnt;
      m_GeomUtil->PointOnLineNearest(line,*pPoint,&pnt);
      Float64 x,y;
      pnt->Location(&x,&y);
      (*pPoint)->Move(x,y);
   }
}

HRESULT CPath::CreateSubPathElement(Float64 start,Float64 end,ILineSegment2d* pLS,ILineSegment2d** ppLineSegment)
{
   // get distance from the start of the path to the start and end of the line segment
   Element element;

   CComPtr<IUnknown> pUnk;
   pLS->QueryInterface(&pUnk);
   VERIFY(FindElement(pUnk, &element));

   Float64 lsStart = element.start;
   Float64 lsEnd = element.end;


   CComQIPtr<ILocate2> locate(m_CogoEngine);

   if ( (lsEnd < start) || // line segment ends before start of sub-path range
        (end < lsStart)    // line segment starts after end of sub-path range
      )
   {
      // this line segment is not part of the sub-path
      (*ppLineSegment) = nullptr;
      return S_OK;
   }
   else if ( start <= lsStart && lsEnd <= end )
   {
      // entire line segment is between the start and end... create a clone because the line segment is part of the sub-path
      return pLS->Clone(ppLineSegment);
   }
   else
   {
      // only a fraction of the line segment is part of the sub-path
      CComPtr<IPoint2d> lsStartPoint, lsEndPoint;
      pLS->get_StartPoint(&lsStartPoint);
      pLS->get_EndPoint(&lsEndPoint);

      Float64 xs,ys;
      lsStartPoint->Location(&xs,&ys);

      Float64 xe,ye;
      lsEndPoint->Location(&xe,&ye);

      CComPtr<ILineSegment2d> clone;
      clone.CoCreateInstance(CLSID_LineSegment2d);

      CComPtr<IPoint2d> cloneStart, cloneEnd;
      clone->get_StartPoint(&cloneStart);
      clone->get_EndPoint(&cloneEnd);

      if ( lsStart <= start )
      {
         // start of sub-path is before start of line segment
         // locate point at start of line segment
         cloneStart.Release();
         locate->PointOnLine(lsStartPoint,lsEndPoint,start - lsStart, 0.00, &cloneStart);
      }
      else
      {
         // start of line segment is after start of sub-path
         // use start of line segment
         cloneStart->Move(xs,ys);
      }

      if ( lsEnd <= end )
      {
         // line segment ends before the sub-path
         // use end point of line semgent
         cloneEnd->Move(xe,ye);
      }
      else
      {
         cloneEnd.Release();
         locate->PointOnLine(lsStartPoint,lsEndPoint,end - lsStart, 0.00, &cloneEnd);
      }

      clone->putref_StartPoint(cloneStart);
      clone->putref_EndPoint(cloneEnd);

      Float64 length;
      clone->get_Length(&length);
      if ( IsZero(length) )
      {
         // this line segment is not part of the sub-path
         (*ppLineSegment) = nullptr;
      }
      else
      {
         clone.CopyTo(ppLineSegment);
      }
      return S_OK;
   }

   return S_OK;
}

HRESULT CPath::CreateSubPathElement(Float64 start, Float64 end, ICircularCurve* pHC, IUnknown** ppResult)
{
   (*ppResult) = nullptr;

   // get distance from the start of the path to the start and end of the curve
   Element element;

   CComPtr<IUnknown> pUnk;
   pHC->QueryInterface(&pUnk);
   VERIFY(FindElement(pUnk, &element));

   Float64 hcStart = element.start;
   Float64 hcEnd = element.end;


   if ((hcEnd < start) || // curve ends before start of sub-path range
       (end < hcStart)    // curve starts after end of sub-path range
      )
   {
      // this curve is not part of the sub-path
      return S_OK;
   }
   else if (start <= hcStart && hcEnd <= end)
   {
      // entire curve is between the start and end... create a clone because the entire curve is part of the sub-path
      CComPtr<ICircularCurve> clone;
      pHC->Clone(&clone);
      (*ppResult) = clone;
      (*ppResult)->AddRef();
      return S_OK;
   }
   else
   {
      // only a fraction of the curve is part of the sub-path

      Float64 R;
      pHC->get_Radius(&R); // curve radius remains constant

      CComPtr<IDirection> dirBack;
      CComPtr<IDirection> dirAhead;
      CComPtr<IPoint2d> pbt;
      CComPtr<IPoint2d> pi;
      CComPtr<IPoint2d> pft;

      // start in circular curve
      pHC->PointOnCurve(start - hcStart, &pbt);
      pHC->Bearing(start - hcStart, &dirBack);

      // ends in circular curve
      pHC->PointOnCurve(end - hcStart, &pft);
      pHC->Bearing(end - hcStart, &dirAhead);


      // PI is at the intesection of the tangents
      CComQIPtr<IIntersect2> intersect(m_CogoEngine);
      intersect->Bearings(pbt, CComVariant(dirBack), 0.00, pft, CComVariant(dirAhead), 0.00, &pi);

         CComObject<CCircularCurve>* pCircularCurve;
         CComObject<CCircularCurve>::CreateInstance(&pCircularCurve);
         CComPtr<ICircularCurve> hc = pCircularCurve;
         hc->putref_PBT(pbt);
         hc->putref_PFT(pft);
         hc->putref_PI(pi);
         hc->put_Radius(R);

         (*ppResult) = hc;
         (*ppResult)->AddRef();
   }

   return S_OK;
}

HRESULT CPath::CreateSubPathElement(Float64 start, Float64 end, ITransitionCurve* pHC, IUnknown** ppResult)
{
   (*ppResult) = nullptr;

   // get distance from the start of the path to the start and end of the horz curve
   Element element;

   CComPtr<IUnknown> pUnk;
   pHC->QueryInterface(&pUnk);
   VERIFY(FindElement(pUnk, &element));

   Float64 hcStart = element.start;
   Float64 hcEnd = element.end;


   if ((hcEnd < start) || // curve ends before start of sub-path range
      (end < hcStart)    // curve starts after end of sub-path range
      )
   {
      // this curve is not part of the sub-path
      return S_OK;
   }
   else if (start <= hcStart && hcEnd <= end)
   {
      // entire curve is between the start and end... create a clone because the entire curve is part of the sub-path
      CComPtr<ITransitionCurve> clone;
      pHC->Clone(&clone);
      (*ppResult) = clone;
      (*ppResult)->AddRef();
      return S_OK;
  }
   else
   {
      // only a fraction of the curve is part of the sub-path

      // build the sub-path curve
      CollectionIndexType nSplinePoints = 7;
      CComPtr<ICubicSpline> spline;
      Float64 Ls;
      pHC->get_Length(&Ls);
      Float64 start_distance = Max(0., start - hcStart);
      Float64 end_distance = Min(end - hcStart, Ls);
      CreateSubCurveSpline(start_distance, end_distance, nSplinePoints, pHC, &spline);

      (*ppResult) = spline;
      (*ppResult)->AddRef();
   }

   return S_OK;

}

typedef enum RelativePointLocation
{
   StartBeforeTS        = 1,
   StartInEntrySpiral   = 2,
   StartInCircularCurve = 3,
   StartInExitSpiral    = 4,
   EndAfterST           = 5,
   EndInEntrySpiral     = 6,
   EndInCircularCurve   = 7,
   EndInExitSpiral      = 8
} RelativePointLocation;

HRESULT CPath::CreateSubPathElement(Float64 start,Float64 end,ICompoundCurve* pHC,IUnknown** ppResult1,IUnknown** ppResult2,IUnknown** ppResult3)
{
   (*ppResult1) = nullptr;
   (*ppResult2) = nullptr;
   (*ppResult3) = nullptr;

   // get distance from the start of the path to the start and end of the horz curve
   Element element;

   CComPtr<IUnknown> pUnk;
   pHC->QueryInterface(&pUnk);
   VERIFY(FindElement(pUnk, &element));

   Float64 hcStart = element.start;
   Float64 hcEnd = element.end;


   if ( (hcEnd < start) || // curve ends before start of sub-path range
        (end < hcStart)    // curve starts after end of sub-path range
      )
   {
      // this curve is not part of the sub-path
      return S_OK;
   }
   else if ( start <= hcStart && hcEnd <= end )
   {
      // entire curve is between the start and end... create a clone because the entire curve is part of the sub-path
      CComPtr<ICompoundCurve> clone;
      pHC->Clone(&clone);
      (*ppResult1) = clone;
      (*ppResult1)->AddRef();
      return S_OK;
   }
   else
   {
      // only a fraction of the curve is part of the sub-path

      // get parameters from the original curve so that we
      // can determine were it is relative to the sub-path
      Float64 Ls1, Ls2, L, Lt;
      pHC->get_SpiralLength(spEntry,&Ls1);
      pHC->get_SpiralLength(spExit,&Ls2);
      pHC->get_CurveLength(&L);
      pHC->get_TotalLength(&Lt);

      RelativePointLocation StartPoint, EndPoint;

      // determine the start point of the sub-path curve
      if ( start < hcStart )
      {
         // sub-path starts before start of HC
         StartPoint = StartBeforeTS;
      }
      else if ( hcStart <= start && start < hcStart+Ls1 )
      {
         // sub-path starts in the entry spiral
         StartPoint = StartInEntrySpiral;
      }
      else if ( hcStart+Ls1 <= start && start < hcStart+Ls1+L )
      {
         // sub-path starts in the circular portion of the curve
         StartPoint = StartInCircularCurve;
      }
      else if ( hcStart+Ls1+L <= start && start < hcStart+Ls1+L+Ls2 )
      {
         // sub-path starts in the exit spiral
         StartPoint = StartInExitSpiral;
      }
      else
      {
         ATLASSERT(false); // should never get here.. sub path starts after this curve
      }


      // determine the end point of the sub-path curve
      if ( end < hcStart )
      {
         ATLASSERT(false); // should never get here.. sub path ends before this curve
      }
      else if ( hcStart <= end && end < hcStart+Ls1 )
      {
         // sub-path ends in entry spiral
         EndPoint = EndInEntrySpiral;
      }
      else if ( hcStart+Ls1 <= end && end < hcStart+Ls1+L )
      {
         // sub-path starts in the circular portion of the curve
         EndPoint = EndInCircularCurve;
      }
      else if ( hcStart+Ls1+L <= end && end < hcStart+Ls1+L+Ls2 )
      {
         // sub-path starts in the exit spiral
         EndPoint = EndInExitSpiral;
      }
      else
      {
         EndPoint = EndAfterST;
      }

      // build the sub-path curve
      CollectionIndexType nSplinePoints = 7;
      if ( (StartPoint == StartBeforeTS || StartPoint == StartInEntrySpiral) && EndPoint == EndInEntrySpiral )
      {
         CComPtr<ICubicSpline> spline;
         Float64 start_distance = Max(0.,start-hcStart);
         Float64 end_distance   = Min(end - hcStart,Ls1);
         CreateSubCurveSpline(start_distance,end_distance,nSplinePoints,pHC,&spline);
         
         (*ppResult1) = spline;
         (*ppResult1)->AddRef();
         return S_OK;
      }
      else if ( StartPoint == StartInExitSpiral && (EndPoint == EndInExitSpiral || EndPoint == EndAfterST) )
      {
         CComPtr<ICubicSpline> spline;
         Float64 start_distance = Max(Ls1+L,start-hcStart);
         Float64 end_distance   = Min(end - hcStart,Lt);
         CreateSubCurveSpline(start_distance,end_distance,nSplinePoints,pHC,&spline);

         (*ppResult1) = spline;
         (*ppResult1)->AddRef();
         return S_OK;
      }
      else
      {
         // determine the curve parameters of the sub-path curve

         // set up variables for sub-path curve
         Float64 R;
         pHC->get_Radius(&R); // curve radius remains constant
         CComPtr<IDirection> dirBack;
         CComPtr<IDirection> dirAhead;
         CComPtr<IPoint2d> pbt;
         CComPtr<IPoint2d> pi;
         CComPtr<IPoint2d> pft;
         Float64 ls1 = 0;
         Float64 ls2 = 0;

         if ( StartPoint == StartInEntrySpiral )
         {
            CComPtr<ICubicSpline> spline;
            Float64 start_distance = Max(0.,start-hcStart);
            Float64 end_distance = Min(end - hcStart,Ls1);
            CreateSubCurveSpline(start_distance,end_distance,nSplinePoints,pHC,&spline);
         
            (*ppResult1) = spline;
            (*ppResult1)->AddRef();

            // curve begins at end of approximated spiral
            pHC->PointOnCurve(end_distance,&pbt);
            pHC->Bearing(end_distance,&dirBack);
         }
         else if ( StartPoint == StartBeforeTS )
         {
            ls1 = Ls1;
            pHC->PointOnCurve(start-hcStart,&pbt);
            pHC->Bearing(start-hcStart,&dirBack);
         }
         else
         {
            // starting in circular curve
            pHC->PointOnCurve(start-hcStart,&pbt);
            pHC->Bearing(start-hcStart,&dirBack);
         }

         if ( EndPoint == EndInExitSpiral )
         {
            CComPtr<ICubicSpline> spline;
            Float64 start_distance = Max(Ls1+L,start-hcStart);
            Float64 end_distance = Min(end - hcStart,Lt);
            CreateSubCurveSpline(start_distance,end_distance,nSplinePoints,pHC,&spline);

            (*ppResult3) = spline;
            (*ppResult3)->AddRef();

            // curve ends at the start of the approximated spiral
            pHC->PointOnCurve(start_distance,&pft);
            pHC->Bearing(start_distance,&dirAhead);
         }
         else if ( EndPoint == EndAfterST )
         {
            ls2 = Ls2;

            pHC->PointOnCurve(end-hcStart,&pft);
            pHC->Bearing(end-hcStart,&dirAhead);
         }
         else
         {
            // ends in circular curve
            pHC->PointOnCurve(end-hcStart,&pft);
            pHC->Bearing(end-hcStart,&dirAhead);
         }


         // PI is at the intesection of the tangents
         CComQIPtr<IIntersect2> intersect(m_CogoEngine);
         intersect->Bearings(pbt,CComVariant(dirBack),0.00,pft,CComVariant(dirAhead),0.00,&pi);

         CComObject<CCompoundCurve>* pCompoundCurve;
         CComObject<CCompoundCurve>::CreateInstance(&pCompoundCurve);
         CComPtr<ICompoundCurve> hc = pCompoundCurve;
         hc->putref_PBT(pbt);
         hc->putref_PFT(pft);
         hc->putref_PI(pi);
         hc->put_Radius(R);
         hc->put_SpiralLength(spEntry,ls1);
         hc->put_SpiralLength(spExit,ls2);

         (*ppResult2) = hc;
         (*ppResult2)->AddRef();
      }
   }

   return S_OK;
}

HRESULT CPath::CreateSubPathElement(Float64 start,Float64 end,ICubicSpline* pSpline,IUnknown** ppResult)
{
   // get distance from the start of the path to the start and end of the spline
   Element element;

   CComPtr<IUnknown> pUnk;
   pSpline->QueryInterface(&pUnk);
   VERIFY(FindElement(pUnk, &element));

   Float64 splineStart = element.start;
   Float64 splineEnd = element.end;

   // determine where the subpath range is (start,end) relative to the spline
   if ( (splineEnd < start) || // spline ends before start of sub-path range
        (end < splineStart)    // spline starts after end of sub-path range
      )
   {
      // this spline is not part of the sub-path
      (*ppResult) = nullptr;
      return S_OK;
   }
   else if ( ::IsLE(start,splineStart) && ::IsLE(splineEnd,end) )
   {
      // entire spline is between the start and end... create a clone because the entire spline is part of the sub-path
      CComPtr<ICubicSpline> clone;
      pSpline->Clone(&clone);
      (*ppResult) = clone;
      (*ppResult)->AddRef();
      return S_OK;
   }
   else
   {
      // only a fraction of the spline is part of the sub-path

      // get start point of sub-spline
      CComPtr<IPoint2d> pntStart;
      CComPtr<IDirection> dirStart;
      if ( start < splineStart )
      {
         // start of sub-path range is before start of spline
         // use the original spline start point
         pSpline->get_StartPoint(&pntStart);
         pSpline->get_StartDirection(&dirStart);
      }
      else
      {
         // start of the sub-path range is on the spline
         // use the point on spline at start as the start point of the sub spline
         pSpline->PointOnSpline(start-splineStart,&pntStart);
         pSpline->Bearing(start-splineStart,&dirStart);
      }

      // get end point of sub-spline
      CComPtr<IPoint2d> pntEnd;
      CComPtr<IDirection> dirEnd;
      if ( splineEnd < end )
      {
         // end of sub-path range is after end of splie
         // use the original spline end point
         pSpline->get_EndPoint(&pntEnd);
         pSpline->get_EndDirection(&dirEnd);
      }
      else
      {
         // end of the sub-path range is on the spline
         // use the point on spline at end as the end point of the sub spline
         pSpline->PointOnSpline(end-splineStart,&pntEnd);
         pSpline->Bearing(end-splineStart,&dirEnd);
      }

      // Start building up the sub-spline
      CComObject<CCubicSpline>* pSubSpline;
      CComObject<CCubicSpline>::CreateInstance(&pSubSpline);
      CComPtr<ICubicSpline> subSpline = pSubSpline;

      // start point
      subSpline->AddPointEx(pntStart);
      subSpline->put_StartDirection( CComVariant(dirStart) );

      // distance from start of sub-path range to start of spline, or 0 if spline starts after sub-path range
      Float64 start_distance = Max(0.,start-splineStart);

      // distance from start of sub-path range to the end of spline, or the length of spline if the sub-path ends after the spline
      Float64 splineLength;
      pSpline->get_Length(&splineLength);
      Float64 end_distance = Min(end - splineStart,splineLength);

      // keep track of the number of points added to the sub-spline between the start and end points
      long nSubPoints = 0;

      std::map<Float64, IndexType> vPoints;

      // all the points between the start and end
      // add those points to the sub-spline that are between the start and end
      CollectionIndexType nPoints;
      pSpline->get_PointCount(&nPoints);
      for ( CollectionIndexType i = 1; i < nPoints-1; i++ )
      {
         Float64 distFromStartOfSpline;
         pSpline->DistanceFromStartAtPoint(i,&distFromStartOfSpline);

         if ( start_distance < distFromStartOfSpline && distFromStartOfSpline < end_distance )
         {
            // this point falls within the sub-path range... use it in the sub-spline
            vPoints.insert(std::make_pair(distFromStartOfSpline, i));
         }
      }

      IndexType nIntermediatePoints = 10;
      for (IndexType i = 1; i < nIntermediatePoints; i++)
      {
         Float64 distFromStart = start_distance + i*(end_distance - start_distance) / nIntermediatePoints;
         vPoints.insert(std::make_pair(distFromStart, INVALID_INDEX)); // if this fails, there is already a point at distFromStart so that's ok
      }


      CComPtr<IPoint2d> p;
      for (const auto& pair : vPoints)
      {
         // start and end points are handeled elsewhere... make sure we aren't duplicating them
         ATLASSERT(!IsEqual(pair.first, start));
         ATLASSERT(!IsEqual(pair.first, end));

         p.Release();
         if (pair.second == INVALID_INDEX)
         {
            pSpline->PointOnSpline(pair.first, &p);
         }
         else
         {
            pSpline->get_Point(pair.second, &p);
         }
         pSubSpline->AddPointEx(p);
      }

      // finish it out with the end point and direction
      subSpline->AddPointEx(pntEnd);
      subSpline->put_EndDirection( CComVariant(dirEnd) );

      (*ppResult) = subSpline;
      (*ppResult)->AddRef();
      return S_OK;
   }

   return S_OK;
}

 
HRESULT CPath::CreateSubCurveSpline(Float64 start,Float64 end,CollectionIndexType nPoints,ICompoundCurve* pHC,ICubicSpline** ppSpline)
{
   // create a cubic spline to represent the sub-portion of the entry spiral
   CComObject<CCubicSpline>* pSpline;
   CComObject<CCubicSpline>::CreateInstance(&pSpline);
   CComPtr<ICubicSpline> spline = pSpline;

   CComPtr<IPoint2d>   pntStart; // start point of spline
   CComPtr<IDirection> dirStart; // start direction of spline
   pHC->PointOnCurve(start,&pntStart);
   pHC->Bearing(start,&dirStart);

   spline->AddPointEx(pntStart);
   spline->put_StartDirection(CComVariant(dirStart));

   // lay out some points between the start point and the end point
   // so the cubic spline gives a good approximation of the spiral
   CollectionIndexType nIntermediatePoints = nPoints-2;
   for ( CollectionIndexType i = 0; i < nIntermediatePoints; i++ )
   {
      Float64 d = start + (i+1)*(end - start)/(nIntermediatePoints+1);

      CComPtr<IPoint2d> p;
      pHC->PointOnCurve(d,&p);
      spline->AddPointEx(p);
   }

   // finish with the end point
   CComPtr<IPoint2d> pntEnd;
   CComPtr<IDirection> dirEnd;
   pHC->PointOnCurve(end,&pntEnd);
   pHC->Bearing(end,&dirEnd);
   spline->AddPointEx(pntEnd);
   spline->put_EndDirection(CComVariant(dirEnd));

   (*ppSpline) = spline;
   (*ppSpline)->AddRef();

   return S_OK;
}

HRESULT CPath::CreateSubCurveSpline(Float64 start, Float64 end, CollectionIndexType nPoints, ITransitionCurve* pHC, ICubicSpline** ppSpline)
{
   // create a cubic spline to represent the sub-portion of the entry spiral
   CComObject<CCubicSpline>* pSpline;
   CComObject<CCubicSpline>::CreateInstance(&pSpline);
   CComPtr<ICubicSpline> spline = pSpline;

   CComPtr<IPoint2d>   pntStart; // start point of spline
   CComPtr<IDirection> dirStart; // start direction of spline
   pHC->PointOnCurve(start, &pntStart);
   pHC->Bearing(start, &dirStart);

   spline->AddPointEx(pntStart);
   spline->put_StartDirection(CComVariant(dirStart));

   // lay out some points between the start point and the end point
   // so the cubic spline gives a good approximation of the spiral
   CollectionIndexType nIntermediatePoints = nPoints - 2;
   for (CollectionIndexType i = 0; i < nIntermediatePoints; i++)
   {
      Float64 d = start + (i + 1) * (end - start) / (nIntermediatePoints + 1);

      CComPtr<IPoint2d> p;
      pHC->PointOnCurve(d, &p);
      spline->AddPointEx(p);
   }

   // finish with the end point
   CComPtr<IPoint2d> pntEnd;
   CComPtr<IDirection> dirEnd;
   pHC->PointOnCurve(end, &pntEnd);
   pHC->Bearing(end, &dirEnd);
   spline->AddPointEx(pntEnd);
   spline->put_EndDirection(CComVariant(dirEnd));

   (*ppSpline) = spline;
   (*ppSpline)->AddRef();

   return S_OK;
}

HRESULT CPath::SavePathElement(IPath* pPath,IUnknown* pUnk)
{
   CComObject<CPathElement>* pNewPathElement;
   CComObject<CPathElement>::CreateInstance(&pNewPathElement);
   CComPtr<IPathElement> newPathElement = pNewPathElement;
   HRESULT hr = newPathElement->putref_Value(pUnk);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = pPath->Add(newPathElement);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return S_OK;
}

Float64 CPath::GetElementLength(IPathElement* pElement)
{
   PathElementType type;
   pElement->get_Type(&type);
   CComPtr<IUnknown> punk;
   pElement->get_Value(&punk);

   Float64 length = 0;
   switch(type)
   {
      case petPoint:
         length = 0;
         break;

      case petLineSegment:
         {
            CComQIPtr<ILineSegment2d> ls(punk);
            ls->get_Length(&length);
         }
         break;

      case petCircularCurve:
      {
         CComQIPtr<ICircularCurve> hc(punk);
         hc->get_Length(&length);
      }
      break;

      case petTransitionCurve:
      {
         CComQIPtr<ITransitionCurve> hc(punk);
         hc->get_Length(&length);
      }
      break;

      case petCompoundCurve:
      {
         CComQIPtr<ICompoundCurve> hc(punk);
         hc->get_TotalLength(&length);
      }
      break;

      case petCubicSpline:
         {
            CComQIPtr<ICubicSpline> spline(punk);
            spline->get_Length(&length);
         }
         break;

      default:
         ATLASSERT(false); // should never get here
         break;
   }

   return length;
}

#if defined _DEBUG
void CPath::DumpPathElements()
{
   std::vector<Element>& vElements = GetPathElements();
   for (const auto& element : vElements)
   {
      CComPtr<IPathElement> path_element = element.pathElement;

      PathElementType type;
      path_element->get_Type(&type);
      CComPtr<IUnknown> punk;
      path_element->get_Value(&punk);

      switch(type)
      {
      case petPoint:
         {
            CComQIPtr<IPoint2d> point(punk);
            DumpPathElement(point);
         }
         break;

      case petLineSegment:
         {
            CComQIPtr<ILineSegment2d> ls(punk);
            DumpPathElement(ls);
         }
         break;

      case petCircularCurve:
      {
         CComQIPtr<ICircularCurve> hc(punk);
         DumpPathElement(hc);
      }
      break;

      case petTransitionCurve:
      {
         CComQIPtr<ITransitionCurve> hc(punk);
         DumpPathElement(hc);
      }
      break;

      case petCompoundCurve:
      {
         CComQIPtr<ICompoundCurve> hc(punk);
         DumpPathElement(hc);
      }
      break;

      case petCubicSpline:
         {
            CComQIPtr<ICubicSpline> spline(punk);
            DumpPathElement(spline);
         }
         break;

      default:
         ATLASSERT(false); // should never get here
         break;
      }

      path_element.Release();
   }
}

void CPath::DumpPathElement(IPoint2d* pPoint)
{
   Float64 x,y;
   pPoint->Location(&x,&y);
   ATLTRACE2("Point (%f,%f)\n",x,y);
}

void CPath::DumpPathElement(ILineSegment2d* pLS)
{
   CComPtr<IPoint2d> pntStart,pntEnd;
   pLS->get_StartPoint(&pntStart);
   pLS->get_EndPoint(&pntEnd);

   Float64 sx,sy;
   pntStart->Location(&sx,&sy);

   Float64 ex,ey;
   pntEnd->Location(&ex,&ey);

   ATLTRACE2("Line Segment (%f,%f) (%f,%f)\n",sx,sy,ex,ey);
}

void CPath::DumpPathElement(ICircularCurve* pHC)
{
   ATLTRACE2("CircularCurve\n");
}

void CPath::DumpPathElement(ITransitionCurve* pHC)
{
   ATLTRACE2("TransitionCurve\n");
}

void CPath::DumpPathElement(ICompoundCurve* pHC)
{
   ATLTRACE2("CompoundCurve\n");
}

void CPath::DumpPathElement(ICubicSpline* pSpine)
{
   ATLTRACE2("Spline\n");
}
#endif
