///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPath
HRESULT CPath::FinalConstruct()
{
   m_Path = WBFL::COGO::Path::Create();
   return S_OK;
}

void CPath::FinalRelease()
{
}

void CPath::SetPath(std::shared_ptr<WBFL::COGO::Path> path)
{
   m_Path = path;
   m_PathElements.clear();
   for (auto& element : m_Path->GetPathElements())
   {
      CComPtr<IPathElement> path_element;
      cogoUtil::CreatePathElement(element, &path_element);
      m_PathElements.emplace_back(path_element);
   }
}

#if defined _DEBUG
#define VALIDATE Validate()
void CPath::Validate() const
{
   ATLASSERT(m_PathElements.size() == m_Path->GetPathElementCount());

   // inner elements must be the same
   IndexType idx = 0;
   for (auto path_element : m_PathElements)
   {
      ATLASSERT(cogoUtil::GetInnerPathElement(path_element) == m_Path->GetPathElement(idx++));
   }
}
#else
#define VALIDATE
#endif

STDMETHODIMP CPath::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPath,
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

STDMETHODIMP CPath::get_Item(CollectionIndexType idx, IPathElement* *pVal)
{
   CHECK_RETOBJ(pVal);
   VALIDATE;
   return cogoUtil::CreatePathElement(m_Path->GetPathElement(idx), pVal);
}

STDMETHODIMP CPath::put_Item(CollectionIndexType idx, IPathElement *pVal)
{
   CHECK_IN(pVal);
   m_Path->InsertPathElement(idx, cogoUtil::GetInnerPathElement(pVal));
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CPath::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   VALIDATE;
   *pVal = m_Path->GetPathElementCount();
   return S_OK;
}

STDMETHODIMP CPath::Add(IPathElement* element)
{
   m_Path->AddPathElement(cogoUtil::GetInnerPathElement(element));
   m_PathElements.emplace_back(element);
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CPath::Insert(CollectionIndexType idx, IPathElement* element)
{
   CHECK_IN(element);
   m_Path->InsertPathElement(idx, cogoUtil::GetInnerPathElement(element));
   m_PathElements.emplace(m_PathElements.begin() + idx, element);
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CPath::Clear()
{
   m_Path->Clear();
   m_PathElements.clear();
   VALIDATE;
   return S_OK;
}


STDMETHODIMP CPath::DistanceAndOffset(IPoint2d* point,Float64* distance,Float64* offset)
{
   CHECK_IN(point);
   CHECK_RETVAL(distance);
   CHECK_RETVAL(offset);
   VALIDATE;

   std::tie(*distance,*offset) = m_Path->DistanceAndOffset(cogoUtil::GetPoint(point));
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
   VALIDATE;

   bool bResult;
   WBFL::Geometry::Point2d p;
   std::tie(bResult, p) = m_Path->Intersect(cogoUtil::GetLine(line), cogoUtil::GetPoint(pNearest), vbProjectBack == VARIANT_TRUE, vbProjectAhead == VARIANT_TRUE);
   if (bResult)
   {
      return cogoUtil::CreatePoint(p, point);
   }
   return E_FAIL;
}

STDMETHODIMP CPath::Clone(IPath* *clone)
{
   CHECK_RETOBJ(clone);
   auto backing_clone = WBFL::COGO::Path::Create(*m_Path);
   return cogoUtil::CreatePath(backing_clone, clone);
}

//
// IPathElement
//
STDMETHODIMP CPath::Clone(IPathElement** clone)
{
   CHECK_RETOBJ(clone);
   auto backing_clone = WBFL::COGO::Path::Create(*m_Path);
   return cogoUtil::CreatePathElement(backing_clone, clone);
}

STDMETHODIMP CPath::Move(Float64 dist, VARIANT varDirection)
{
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Direction direction;
   std::tie(hr, direction) = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   m_Path->Move(dist, direction);
   return S_OK;
}

STDMETHODIMP CPath::Offset(Float64 dx, Float64 dy)
{
   m_Path->Offset(dx, dy);
   return S_OK;
}

STDMETHODIMP CPath::PointOnCurve(Float64 distance, IPoint2d** pVal)
{
   CHECK_RETVAL(pVal);
   auto point = m_Path->PointOnCurve(distance);
   return cogoUtil::CreatePoint(point, pVal);
}

STDMETHODIMP CPath::GetStartPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Path->GetStartPoint(), ppPoint);
}

STDMETHODIMP CPath::GetEndPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Path->GetEndPoint(), ppPoint);
}

STDMETHODIMP CPath::GetLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   VALIDATE;
   *pLength = m_Path->GetLength();
   return S_OK;
}

STDMETHODIMP CPath::GetKeyPoints(IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   return cogoUtil::CreatePoints(m_Path->GetKeyPoints(), ppPoints);
}

STDMETHODIMP CPath::LocatePoint(Float64 distance, OffsetMeasureType offsetMeasure, Float64 offset, VARIANT varDirection, IPoint2d** newPoint)
{
   CHECK_RETOBJ(newPoint);
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Direction direction;
   std::tie(hr, direction) = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreatePoint(m_Path->LocatePoint(distance, WBFL::COGO::OffsetType(offsetMeasure), offset, direction), newPoint);
}

STDMETHODIMP CPath::GetBearing(Float64 distance, IDirection** dir)
{
   CHECK_RETOBJ(dir);
   VALIDATE;
   return cogoUtil::CreateDirection(m_Path->GetBearing(distance), dir);
}

STDMETHODIMP CPath::GetNormal(Float64 distance, IDirection** dir)
{
   CHECK_RETOBJ(dir);
   VALIDATE;
   return cogoUtil::CreateDirection(m_Path->GetNormal(distance), dir);
}

STDMETHODIMP CPath::ProjectPoint(IPoint2d* point, IPoint2d** newPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection)
{
   CHECK_IN(point);
   CHECK_RETOBJ(newPoint);
   CHECK_RETVAL(pDistFromStart);
   CHECK_RETVAL(pvbOnProjection);
   VALIDATE;

   WBFL::Geometry::Point2d np;
   Float64 dfs;
   bool bOP;
   std::tie(np, dfs, bOP) = m_Path->ProjectPoint(cogoUtil::GetPoint(point));

   *pDistFromStart = dfs;
   *pvbOnProjection = (bOP ? VARIANT_TRUE : VARIANT_FALSE);
   return cogoUtil::CreatePoint(np, newPoint);
}

STDMETHODIMP CPath::Intersect(ILine2d* pLine, VARIANT_BOOL vbProjectBack, VARIANT_BOOL vbProjectAhead, IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   auto vPoints = m_Path->Intersect(cogoUtil::GetLine(pLine), vbProjectBack == VARIANT_TRUE, vbProjectAhead == VARIANT_TRUE);
   CComPtr<IPoint2dCollection> points;
   HRESULT hr = points.CoCreateInstance(CLSID_Point2dCollection);
   if (FAILED(hr)) return hr;
   for (auto& point : vPoints)
   {
      CComPtr<IPoint2d> pnt;
      cogoUtil::CreatePoint(point, &pnt);
      points->Add(pnt);
   }
   return points.CopyTo(ppPoints);
}

STDMETHODIMP CPath::CreateOffsetPath(Float64 offset, IPath** path)
{
   CHECK_RETOBJ(path);
   VALIDATE;
   auto offset_path_elements = m_Path->CreateOffsetPath(offset);
   auto offset_path = WBFL::COGO::Path::Create();
   for (auto& offset_path_element : offset_path_elements)
   {
      offset_path->AddPathElement(offset_path_element);
   }

   return cogoUtil::CreatePath(offset_path, path);
}

STDMETHODIMP CPath::CreateSubpath(Float64 start, Float64 end, IPath** path)
{
   CHECK_RETOBJ(path);
   VALIDATE;
   auto subpath_elements = m_Path->CreateSubpath(start, end);
   auto subpath = WBFL::COGO::Path::Create();
   for (auto& subpath_element : subpath_elements)
   {
      subpath->AddPathElement(subpath_element);
   }
   return cogoUtil::CreatePath(subpath, path);
}

