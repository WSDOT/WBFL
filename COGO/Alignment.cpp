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

// Alignment.cpp : Implementation of CAlignment
#include "stdafx.h"
#include "WBFLCogo.h"
#include "Alignment.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlignment
HRESULT CAlignment::FinalConstruct()
{
   m_Alignment = WBFL::COGO::Alignment::Create();
   return S_OK;
}

void CAlignment::FinalRelease()
{
}

void CAlignment::SetAlignment(std::shared_ptr<WBFL::COGO::Alignment> alignment) 
{ 
   m_Alignment = alignment; 
   m_PathElements.clear();
   for (auto& element : m_Alignment->GetPathElements())
   {
      CComPtr<IPathElement> path_element;
      cogoUtil::CreatePathElement(element, &path_element);
      m_PathElements.emplace_back(path_element);
   }
   
   m_Profiles.clear();
   for(const auto& [id,profile] : m_Alignment->GetProfiles())
   {
      CComPtr<IProfile> new_profile;
      cogoUtil::CreateProfile(profile, &new_profile);
      m_Profiles.emplace(id, new_profile);
   }
}

#if defined _DEBUG
#define VALIDATE Validate()
void CAlignment::Validate() const
{
   ATLASSERT(m_PathElements.size() == m_Alignment->GetPathElementCount());
   ATLASSERT(m_Profiles.size() == m_Alignment->GetProfileCount());

   // inner elements must be the same
   IndexType idx = 0;
   for (auto path_element : m_PathElements)
   {
      ATLASSERT(cogoUtil::GetInnerPathElement(path_element) == m_Alignment->GetPathElement(idx++));
   }

   for (const auto& [ID,profile] : m_Profiles)
   {
      ATLASSERT(cogoUtil::GetInnerProfile(profile) == m_Alignment->GetProfile(ID));
   }
}
#else
#define VALIDATE
#endif

STDMETHODIMP CAlignment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAlignment,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
      if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAlignment::get_RefStation(IStation** station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_Alignment->GetReferenceStation(), station);
}

STDMETHODIMP CAlignment::put_RefStation(VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;
   m_Alignment->SetReferenceStation(station);
   return S_OK;
}

STDMETHODIMP CAlignment::AddPathElement(IPathElement* element)
{
   CHECK_IN(element);
   m_Alignment->AddPathElement(cogoUtil::GetInnerPathElement(element));
   m_PathElements.emplace_back(element);
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CAlignment::InsertPathElement(IndexType idx, IPathElement* element)
{
   CHECK_IN(element);
   m_Alignment->InsertPathElement(idx, cogoUtil::GetInnerPathElement(element));
   m_PathElements.emplace(m_PathElements.begin() + idx, element);
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CAlignment::ClearPathElements()
{
   m_Alignment->ClearPathElements();
   m_PathElements.clear();
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CAlignment::get_Item(IndexType idx,IPathElement** pVal)  
{ 
   CHECK_RETOBJ(pVal);
   VALIDATE;
   if (m_PathElements.size() <= idx) return E_INVALIDARG;
   auto path_element = m_PathElements[idx];
   ATLASSERT(cogoUtil::GetInnerPathElement(path_element) == m_Alignment->GetPathElement(idx));
   return path_element.CopyTo(pVal);
}

STDMETHODIMP CAlignment::get_Count(IndexType* pVal)
{
   CHECK_RETVAL(pVal);
   VALIDATE;
   *pVal = m_Alignment->GetPathElementCount();
   return S_OK;
}

STDMETHODIMP CAlignment::AddProfile(IDType id, IProfile* pProfile)
{
   CHECK_IN(pProfile);
   m_Alignment->AddProfile(id, cogoUtil::GetInnerProfile(pProfile));
   pProfile->put_Alignment(this);
   m_Profiles.emplace(id, pProfile);
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CAlignment::GetProfile(IDType id,IProfile** pVal)
{
   VALIDATE;

   auto found = m_Profiles.find(id);
   if (found == m_Profiles.end())
      return E_INVALIDARG;

   auto profile = found->second;
   ATLASSERT(cogoUtil::GetInnerProfile(profile) == m_Alignment->GetProfile(id));

   return profile.CopyTo(pVal);
}

STDMETHODIMP CAlignment::ClearProfiles()
{
   m_Alignment->ClearProfiles();
   m_Profiles.clear();
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CAlignment::Move(Float64 dist, VARIANT varDirection)
{
   auto [hr, direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;
   m_Alignment->Move(dist, direction);
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CAlignment::StationAndOffset(IPoint2d* point, IStation** station, Float64* offset)
{
   CHECK_IN(point);
   CHECK_RETOBJ(station);
   CHECK_RETVAL(offset);
   VALIDATE;

   auto [s, o] = m_Alignment->StationAndOffset(cogoUtil::GetPoint(point));
   *offset = o;
   return cogoUtil::CreateStation(s, station);
}

STDMETHODIMP CAlignment::ProjectPoint(IPoint2d* point, IPoint2d** newPoint, IStation** ppStation, VARIANT_BOOL* pvbOnProjection)
{
   CHECK_IN(point);
   CHECK_RETOBJ(newPoint);
   CHECK_RETOBJ(ppStation);
   CHECK_RETVAL(pvbOnProjection);
   VALIDATE;

   auto [np, station, bOP] = m_Alignment->ProjectPoint(cogoUtil::GetPoint(point));

   *pvbOnProjection = (bOP ? VARIANT_TRUE : VARIANT_FALSE);
   cogoUtil::CreateStation(station, ppStation);
   return cogoUtil::CreatePoint(np, newPoint);
}

STDMETHODIMP CAlignment::LocatePoint( VARIANT varStation, OffsetMeasureType offsetMeasure, Float64 offset, VARIANT varDirection, IPoint2d* *newPoint)
{
   CHECK_RETOBJ(newPoint);
   VALIDATE;

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   WBFL::COGO::Direction direction;
   std::tie(hr, direction) = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreatePoint(m_Alignment->LocatePoint(station, WBFL::COGO::OffsetType(offsetMeasure), offset, direction), newPoint);
}

STDMETHODIMP CAlignment::Intersect(ILine2d* pLine, IPoint2d* pNearest, IPoint2d** point)
{
   CHECK_IN(pLine);
   CHECK_IN(pNearest);
   CHECK_RETOBJ(point);
   VALIDATE;

   auto [bFound, ip] = m_Alignment->Intersect(cogoUtil::GetLine(pLine), cogoUtil::GetPoint(pNearest), true, true);
   if (bFound)
      return cogoUtil::CreatePoint(ip, point);
   else
      return E_FAIL;
}

STDMETHODIMP CAlignment::IntersectEx(ILine2d* pLine, IPoint2d* pNearest, VARIANT_BOOL vbProjectBack, VARIANT_BOOL vbProjectAhead, IPoint2d** point)
{
   CHECK_IN(pLine);
   CHECK_IN(pNearest);
   CHECK_RETOBJ(point);
   VALIDATE;

   auto [bFound, ip] = m_Alignment->Intersect(cogoUtil::GetLine(pLine), cogoUtil::GetPoint(pNearest), vbProjectBack == VARIANT_TRUE, vbProjectAhead == VARIANT_TRUE);
   if (bFound)
      return cogoUtil::CreatePoint(ip, point);
   else
      return E_FAIL;
}

STDMETHODIMP CAlignment::GetBearing(VARIANT varStation,IDirection* *dir)
{
   CHECK_RETOBJ(dir);
   VALIDATE;

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreateDirection(m_Alignment->GetBearing(station), dir);
}

STDMETHODIMP CAlignment::GetNormal(VARIANT varStation,IDirection* *dir)
{
   CHECK_RETOBJ(dir);
   VALIDATE;

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreateDirection(m_Alignment->GetNormal(station), dir);
}

STDMETHODIMP CAlignment::GetDirection(VARIANT varStation, BSTR bstrOrientation,IDirection** direction)
{
   VALIDATE;
   USES_CONVERSION;

   CHECK_RETOBJ(direction);

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;


   std::_tstring strOrientation(OLE2T(bstrOrientation));
   auto dir = m_Alignment->GetDirection(station, strOrientation);
   return cogoUtil::CreateDirection(dir, direction);
}

STDMETHODIMP CAlignment::get_Length(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   VALIDATE;
   *pLength = m_Alignment->GetLength();
   return S_OK;
}

STDMETHODIMP CAlignment::CreateSubAlignment(VARIANT varStartStation,VARIANT varEndStation,IAlignment** ppAlignment)
{
   CHECK_RETOBJ(ppAlignment);
   VALIDATE;

   auto [hr, startStation] = cogoUtil::StationFromVariant(varStartStation);
   if (FAILED(hr)) return hr;

   WBFL::COGO::Station endStation;
   std::tie(hr, endStation) = cogoUtil::StationFromVariant(varEndStation);
   if (FAILED(hr)) return hr;

   auto subalignment = m_Alignment->CreateSubAlignment(startStation, endStation);
   return cogoUtil::CreateAlignment(subalignment, ppAlignment);
}

STDMETHODIMP CAlignment::CreateOffsetAlignment(Float64 offset, IAlignment** ppAlignment)
{
   CHECK_RETOBJ(ppAlignment);
   VALIDATE;

   auto offset_alignment = m_Alignment->CreateOffsetAlignment(offset);
   return cogoUtil::CreateAlignment(offset_alignment, ppAlignment);
}

STDMETHODIMP CAlignment::CreateOffsetPath(Float64 offset, IPath** path)
{
   CHECK_RETOBJ(path);
   VALIDATE;
   return cogoUtil::CreatePath(m_Alignment->CreateOffsetPath(offset), path);
}

STDMETHODIMP CAlignment::CreateSubPath(VARIANT varStartStation, VARIANT varEndStation, IPath** path)
{
   CHECK_RETOBJ(path);
   VALIDATE;

   auto [hr, startStation] = cogoUtil::StationFromVariant(varStartStation);
   if (FAILED(hr)) return hr;

   WBFL::COGO::Station endStation;
   std::tie(hr, endStation) = cogoUtil::StationFromVariant(varEndStation);
   if (FAILED(hr)) return hr;


   return cogoUtil::CreatePath(m_Alignment->CreateSubpath(startStation, endStation), path);
}

STDMETHODIMP CAlignment::AddStationEquation(Float64 back, Float64 ahead)
{
   m_Alignment->AddStationEquation(back, ahead);
   return S_OK;
}

STDMETHODIMP CAlignment::GetStationEquationCount(IndexType* pCount)
{
   CHECK_RETVAL(pCount);
   *pCount = m_Alignment->GetStationEquations().size();
   return S_OK;
}

STDMETHODIMP CAlignment::GetStationEquation(IndexType i, IStationEquation** ppEquation)
{
   CHECK_RETOBJ(ppEquation);
   if (m_Alignment->GetStationEquations().size() <= i) return E_INVALIDARG;

   const auto& station_equation = m_Alignment->GetStationEquations()[i];
   return cogoUtil::CreateStationEquation(station_equation, ppEquation);
}

STDMETHODIMP CAlignment::ClearStationEquations()
{
   m_Alignment->ClearStationEquations();
   return S_OK;
}

STDMETHODIMP CAlignment::IncrementStation(VARIANT varStation, Float64 distance, IStation** ppStation)
{
   CHECK_RETOBJ(ppStation);

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreateStation(m_Alignment->IncrementStation(station, distance), ppStation);
}

STDMETHODIMP CAlignment::IncrementStationBy(IStation* station, Float64 distance)
{
   auto& sta = cogoUtil::GetInnerStation(station);
   m_Alignment->IncrementStationBy(sta, distance);
   return S_OK;
}

STDMETHODIMP CAlignment::ConvertToNormalizedStation(VARIANT varStation, Float64* pStation)
{
   CHECK_RETVAL(pStation);
   
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   *pStation = m_Alignment->ConvertToNormalizedStation(station).GetValue();
   return S_OK;
}

STDMETHODIMP CAlignment::ConvertToNormalizedStationEx(VARIANT varStation, IStation** ppStation)
{
   CHECK_RETOBJ(ppStation);

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreateStation(m_Alignment->ConvertToNormalizedStation(station), ppStation);
}

STDMETHODIMP CAlignment::ConvertFromNormalizedStation(Float64 normalizedStation, IStation** ppStation)
{
   CHECK_RETOBJ(ppStation);

   return cogoUtil::CreateStation(m_Alignment->ConvertFromNormalizedStation(normalizedStation), ppStation);
}

STDMETHODIMP CAlignment::ConvertFromNormalizedStationEx(VARIANT varStation, IStation** ppStation)
{
   CHECK_RETOBJ(ppStation);

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreateStation(m_Alignment->ConvertFromNormalizedStation(station), ppStation);
}

STDMETHODIMP CAlignment::CompareStations(VARIANT varStation1, VARIANT varStation2, Int8* pResult)
{
   CHECK_RETVAL(pResult);

   auto [hr, station1] = cogoUtil::StationFromVariant(varStation1);
   if (FAILED(hr)) return hr;

   WBFL::COGO::Station station2;
   std::tie(hr, station2) = cogoUtil::StationFromVariant(varStation2);
   if (FAILED(hr)) return hr;

   *pResult = m_Alignment->CompareStations(station1, station2);
   return S_OK;
}

STDMETHODIMP CAlignment::DistanceBetweenStations(VARIANT varStation1, VARIANT varStation2, Float64* pDist)
{
   CHECK_RETVAL(pDist);

   auto [hr, station1] = cogoUtil::StationFromVariant(varStation1);
   if (FAILED(hr)) return hr;

   WBFL::COGO::Station station2;
   std::tie(hr, station2) = cogoUtil::StationFromVariant(varStation2);
   if (FAILED(hr)) return hr;

   *pDist = m_Alignment->DistanceBetweenStations(station1, station2);
   return S_OK;
}

STDMETHODIMP CAlignment::Clone(IAlignment* *clone)
{
   CHECK_RETOBJ(clone);
   auto backing_clone = WBFL::COGO::Alignment::Create(*m_Alignment);
   return cogoUtil::CreateAlignment(backing_clone, clone);
}
