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

// Profile.cpp : Implementation of CProfile
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Profile.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined _DEBUG
void CProfile::Validate() const
{
   // Validate Profile Elements
   {
      // Containers must be the same size
      ATLASSERT(m_ProfileElements.size() == m_Profile->GetProfileElementCount());

      // The backing elements in the COM objects must be the same as the profile's elements
      const auto& profile_elements = m_Profile->GetProfileElements();
      auto iter1 = m_ProfileElements.begin();
      auto end = m_ProfileElements.end();
      auto iter2 = profile_elements.begin();
      for (; iter1 != end; iter1++, iter2++)
      {
         CComPtr<IProfileElement> com_profile_element(*iter1);
         const auto& profile_element(*iter2);
         ATLASSERT(cogoUtil::GetInnerProfileElement(com_profile_element) == profile_element);
      }
   }

   // Validate Surfaces
   {
      const auto& surfaces = m_Profile->GetSurfaces();
      ATLASSERT(m_Surfaces.size() == surfaces.size()); // containers must be same size

      // backing objects must be the same
      auto iter1 = m_Surfaces.begin();
      auto end = m_Surfaces.end();
      auto iter2 = surfaces.begin();
      for (; iter1 != end; iter1++, iter2++)
      {
         ATLASSERT(iter1->first == iter2->first); // check IDs
         CComPtr<ISurface> com_surface(iter1->second);
         const auto& surface(iter2->second);
         ATLASSERT(cogoUtil::GetInnerSurface(com_surface) == surface);
      }
   }
}
#define VALIDATE Validate()
#else
#define VALIDATE
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfile
HRESULT CProfile::FinalConstruct()
{
   m_Profile = WBFL::COGO::Profile::Create();
   return S_OK;
}

void CProfile::FinalRelease()
{
}

void CProfile::SetProfile(std::shared_ptr<WBFL::COGO::Profile> profile)
{ 
   m_Profile = profile; 
   for (const auto& element : m_Profile->GetProfileElements())
   {
      CComPtr<IProfileElement> profile_element;
      cogoUtil::CreateProfileElement(element, &profile_element);
      m_ProfileElements.emplace_back(profile_element);
   }

   m_Surfaces.clear();
   for (const auto& surface_record : m_Profile->GetSurfaces())
   {
      CComPtr<ISurface> surface;
      cogoUtil::CreateSurface(std::const_pointer_cast<WBFL::COGO::Surface>(surface_record.second), &surface);
      m_Surfaces.emplace(surface_record.first, surface);
   }

   VALIDATE;
}

STDMETHODIMP CProfile::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProfile,
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

STDMETHODIMP CProfile::put_Alignment(IAlignment* pAlignment)
{
   CHECK_IN(pAlignment);
   m_pAlignment = pAlignment;
   return S_OK;
}

STDMETHODIMP CProfile::get_Alignment(IAlignment** ppAlignment)
{
   // NOTE: Profile is a Child to Alignment. The Alignment provided
   // from this methods should be the exact same COM object as the actual
   // parent object. For this reason, we can't create a new IAlignment
   // wrapper object. This COM Profile object needs to keep track of its
   // parent COM Alignment object.
   CHECK_RETVAL(ppAlignment);
   if (m_pAlignment)
   {
      (*ppAlignment) = m_pAlignment;
      (*ppAlignment)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CProfile::AddProfileElement(IProfileElement* element)
{
   CHECK_IN(element);
   m_Profile->AddProfileElement(cogoUtil::GetInnerProfileElement(element));
   element->put_Profile(this);
   m_ProfileElements.emplace_back(element);
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CProfile::get_Item(IndexType idx,IProfileElement **pVal)
{
   CHECK_RETOBJ(pVal);
   VALIDATE;
   if (m_ProfileElements.size() <= idx) return E_INVALIDARG;
   auto profile_element = m_ProfileElements[idx];
   return profile_element.CopyTo(pVal);
}

STDMETHODIMP CProfile::get_ProfileElementCount(IndexType *pVal)
{
   CHECK_RETVAL(pVal);
   VALIDATE;
   *pVal = m_ProfileElements.size();
   return S_OK;
}

STDMETHODIMP CProfile::ClearProfileElements()
{
   m_Profile->ClearProfileElements();
   m_ProfileElements.clear();
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CProfile::AddSurface(IDType id, ISurface* pSurface)
{
   CHECK_IN(pSurface);
   m_Profile->AddSurface(id, cogoUtil::GetInnerSurface(pSurface));
   m_Surfaces.emplace(id, pSurface);
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CProfile::GetSurface(IDType id, ISurface** ppSurface)
{
   CHECK_RETOBJ(ppSurface);
   VALIDATE;
   auto found = m_Surfaces.find(id);
   if (found == m_Surfaces.end())
   {
      return E_INVALIDARG;
   }
   else
   {
      auto surface = found->second;
      ATLASSERT(cogoUtil::GetInnerSurface(surface) == m_Profile->GetSurface(id));
      return surface.CopyTo(ppSurface);
   }
}

STDMETHODIMP CProfile::ClearSurfaces()
{
   m_Profile->ClearSurfaces();
   m_Surfaces.clear();
   VALIDATE;
   return S_OK;
}

STDMETHODIMP CProfile::Clear()
{
   ClearProfileElements();
   ClearSurfaces();
   return S_OK;
}

STDMETHODIMP CProfile::CreateSurfaceTemplateSectionCut(IDType surfaceID, VARIANT varStation, VARIANT_BOOL vbApplySuperelevation, ISurfaceTemplate** ppTemplate)
{
   VALIDATE;
   CComPtr<ISurface> surface;
   HRESULT hr = GetSurface(surfaceID, &surface);
   if (FAILED(hr)) return hr;
   return CreateSurfaceTemplateSectionCutEx(surface, varStation, vbApplySuperelevation, ppTemplate);
}

STDMETHODIMP CProfile::CreateSurfaceTemplateSectionCutEx(ISurface* pSurface, VARIANT varStation, VARIANT_BOOL vbApplySuperelevation, ISurfaceTemplate** ppTemplate)
{
   CHECK_IN(pSurface);
   CHECK_RETOBJ(ppTemplate);
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   auto surface = cogoUtil::GetInnerSurface(pSurface);
   auto surface_template = m_Profile->CreateSurfaceTemplateSectionCut(surface, station, vbApplySuperelevation == VARIANT_TRUE);

   return cogoUtil::CreateSurfaceTemplate(pSurface, surface_template, ppTemplate);
}


STDMETHODIMP CProfile::GetSurfaceContainingStation(VARIANT varStation, IDType* pID, ISurface** ppSurface)
{
   CHECK_RETOBJ(ppSurface);
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   std::shared_ptr<const WBFL::COGO::Surface> surface;
   std::tie(*pID,surface) = m_Profile->GetSurfaceContainingStation(station);
   if (*pID == INVALID_ID)
   {
      *ppSurface = nullptr;
      hr = E_FAIL;
   }
   else
   {
      hr = this->GetSurface(*pID, ppSurface);
   }

   return hr;
}

STDMETHODIMP CProfile::Elevation(IDType surfaceID, VARIANT varStation, Float64 offset, Float64 *elev)
{
   CHECK_RETVAL(elev);
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   *elev = m_Profile->Elevation(surfaceID, station, offset);
   return S_OK;
}

STDMETHODIMP CProfile::Grade(VARIANT varStation, Float64 *grade)
{
   CHECK_RETVAL(grade);
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   *grade = m_Profile->Grade(station);
   return S_OK;
}

STDMETHODIMP CProfile::CrossSlope(IDType surfaceID, VARIANT varStation, Float64 offset, Float64* slope)
{
   CHECK_RETVAL(slope);
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   *slope = m_Profile->CrossSlope(surfaceID, station, offset);
   return S_OK;
}

STDMETHODIMP CProfile::SurfaceTemplateSegmentSlope(IDType surfaceID,VARIANT varStation,IndexType templateSegmentIdx,Float64* pSlope)
{
   CHECK_RETVAL(pSlope);
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   *pSlope = m_Profile->SurfaceTemplateSegmentSlope(surfaceID, station, templateSegmentIdx);
   return S_OK;
}

STDMETHODIMP CProfile::GetRidgePointOffset(IDType surfaceID,VARIANT varStation,IndexType ridgePoint1Idx,IndexType ridgePoint2Idx,Float64* pOffset)
{
   CHECK_RETVAL(pOffset);
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;
    
   try
   {
      *pOffset = m_Profile->GetRidgePointOffset(surfaceID, station, ridgePoint1Idx, ridgePoint2Idx);
      hr = S_OK;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CProfile::GetRidgePointElevation(IDType surfaceID, VARIANT varStation, IndexType ridgePointIdx, Float64* pElev)
{
   CHECK_RETVAL(pElev);
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   try
   {
      *pElev = m_Profile->GetRidgePointElevation(surfaceID, station, ridgePointIdx);
      hr = S_OK;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CProfile::GetRidgePointOffsetAndElevation(IDType surfaceID, VARIANT varStation, IndexType ridgePoint1Idx, IndexType ridgePoint2Idx, Float64* pOffset, Float64* pElev)
{
   CHECK_RETVAL(pOffset);
   CHECK_RETVAL(pElev);
   VALIDATE;

   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;
   try
   {
      std::tie(*pOffset,*pElev) = m_Profile->GetRidgePointOffsetAndElevation(surfaceID, station, ridgePoint1Idx, ridgePoint2Idx);
      hr = S_OK;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}
