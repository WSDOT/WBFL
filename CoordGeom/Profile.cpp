///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/Profile.h>
#include "ProfileImpl.h"

using namespace WBFL::COGO;


std::shared_ptr<Profile> Profile::Create()
{
   //return std::make_shared<Profile>(); This doesn't work because make_shared needs a public constructor for alignment
   // Create new shared_ptr for a Profile object. We can't use std::make_shared because it needs a public constructor.
   // The best we can do is use new
   auto ptr = std::shared_ptr<Profile>(new Profile());

   // In Profile::Profile, I tried to pass the return value from weak_from_this into the
   // constructor for ProfileImpl. However it didn't work. In the line above "new Profile()" is 
   // not a shared pointer so in Profile::Profile() weak_from_this() returns nullptr (as it should).
   // The following line associates the newly created shared_ptr<Profile> object with it's internal
   // profile implementation object, m_pImpl.
   ptr->m_pImpl->SetProfile(ptr.get()->weak_from_this());
   return ptr;
}

std::shared_ptr<Profile> Profile::Create(const Profile& profile)
{
   auto ptr = std::shared_ptr<Profile>(new Profile(profile));
   ptr->m_pImpl->SetProfile(ptr.get()->weak_from_this());
   return ptr;
}

Profile::Profile()
{
   m_pImpl = std::make_unique<ProfileImpl>();
}

Profile::Profile(const Profile& profile)
{
   m_pImpl = std::make_unique<ProfileImpl>(*profile.m_pImpl);
}

Profile::~Profile() = default; // when using the PIMPL idiom, this is how we have to define the destructor in order to keep the compiler happy

void Profile::SetAlignment(std::weak_ptr<const Alignment> alignment)
{
   m_pImpl->SetAlignment(alignment);
}

std::shared_ptr<const Alignment> Profile::GetAlignment() const
{
   return m_pImpl->GetAlignment();
}

void Profile::AddSurface(IDType id,std::shared_ptr<Surface> surface)
{
   PRECONDITION(id != INVALID_ID);
   PRECONDITION(surface);
   PRECONDITION(surface->GetProfile() == nullptr); // surface can't be associated with different profile
   surface->SetProfile(weak_from_this());
   m_pImpl->AddSurface(id, surface);
}

std::shared_ptr<const Surface> Profile::GetSurface(IDType id) const
{
   return m_pImpl->GetSurface(id);
}

const std::map<IDType, std::shared_ptr<const Surface>>& Profile::GetSurfaces() const
{
   return m_pImpl->GetSurfaces();
}

void Profile::ClearSurfaces()
{
   return m_pImpl->ClearSurfaces();
}

void Profile::Clear()
{
   return m_pImpl->Clear();
}

std::pair<IDType, std::shared_ptr<const Surface>> Profile::GetSurfaceContainingStation(const Station& station) const
{
   return m_pImpl->GetSurfaceContainingStation(station);
}

std::shared_ptr<SurfaceTemplate> Profile::CreateSurfaceTemplateSectionCut(IDType surfaceID, const Station& station, bool bApplySuperelevations) const
{
   return CreateSurfaceTemplateSectionCut(GetSurface(surfaceID), station, bApplySuperelevations);
}

std::shared_ptr<SurfaceTemplate> Profile::CreateSurfaceTemplateSectionCut(std::shared_ptr<const Surface> surface, const Station& station, bool bApplySuperelevations) const
{
   return surface->CreateSurfaceTemplateSectionCut(station, bApplySuperelevations);
}

void Profile::AddProfileElement(std::shared_ptr<ProfileElement> profileElement)
{
   PRECONDITION(profileElement);
   PRECONDITION(profileElement->GetProfile() == nullptr); // Profile element can't be associated with multiple profiles
   profileElement->SetProfile(weak_from_this());
   m_pImpl->AddProfileElement(profileElement);
}

std::shared_ptr<ProfileElement> Profile::GetProfileElement(IndexType idx)
{
   return m_pImpl->GetProfileElement(idx);
}

std::shared_ptr<const ProfileElement> Profile::GetProfileElement(IndexType idx) const
{
   return m_pImpl->GetProfileElement(idx);
}

const std::vector<std::shared_ptr<ProfileElement>>& Profile::GetProfileElements() const
{
   return m_pImpl->GetProfileElements();
}

IndexType Profile::GetProfileElementCount() const
{
   return m_pImpl->GetProfileElementCount();
}

void Profile::ClearProfileElements()
{
   return m_pImpl->ClearProfileElements();
}

Float64 Profile::Elevation(const Station& station) const
{
   return m_pImpl->Elevation(station);
}

Float64 Profile::Elevation(IDType surfaceID, const Station& station, Float64 offset) const
{
   return m_pImpl->Elevation(surfaceID, station, offset);
}

Float64 Profile::Elevation(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset) const
{
   return m_pImpl->Elevation(surface, station, offset);
}

Float64 Profile::Grade(const Station& station) const
{
   return m_pImpl->Grade(station);
}

Float64 Profile::SurfaceTemplateSegmentSlope(IDType surfaceID, const Station& station, IndexType segmentIdx) const
{
   return m_pImpl->SurfaceTemplateSegmentSlope(surfaceID, station, segmentIdx);
}

Float64 Profile::SurfaceTemplateSegmentSlope(std::shared_ptr<const Surface> surface, const Station& station, IndexType segmentIdx) const
{
   return m_pImpl->SurfaceTemplateSegmentSlope(surface, station, segmentIdx);
}

Float64 Profile::CrossSlope(IDType surfaceID, const Station& station, Float64 offset) const
{
   return m_pImpl->CrossSlope(surfaceID, station, offset);
}

Float64 Profile::CrossSlope(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset) const
{
   return m_pImpl->CrossSlope(surface, station, offset);
}

Float64 Profile::GetRidgePointOffset(IDType surfaceID, const Station& station, IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   return m_pImpl->GetRidgePointOffset(surfaceID, station, ridgePoint1Idx, ridgePoint2Idx);
}

Float64 Profile::GetRidgePointElevation(IDType surfaceID, const Station& station, IndexType ridgePointIdx) const
{
   return m_pImpl->GetRidgePointElevation(surfaceID, station, ridgePointIdx);
}

std::pair<Float64, Float64> Profile::GetRidgePointOffsetAndElevation(IDType surfaceID, const Station& station, IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   return m_pImpl->GetRidgePointOffsetAndElevation(surfaceID, station, ridgePoint1Idx, ridgePoint2Idx);
}

void Profile::OnProfileChanged()
{
   m_pImpl->OnProfileChanged();
}
