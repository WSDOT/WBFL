///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <CoordGeom/Surface.h>
#include "SurfaceImpl.h"
#include <CoordGeom/Station.h>

using namespace WBFL::COGO;

std::shared_ptr<Surface> Surface::Create()
{
   //return std::make_shared<Surface>(); This doesn't work because make_shared needs a public constructor for Surface
   // Create new shared_ptr for a Profile object. We can't use std::make_shared because it needs a public constructor.
   // The best we can do is use new
   auto ptr = std::shared_ptr<Surface>(new Surface());

   // In Surface::Surface, I tried to pass the return value from weak_from_this into the
   // constructor for SurfaceImpl. However it didn't work. In the line above "new Surface()" is 
   // not a shared pointer so in Surface::Surface() weak_from_this() returns nullptr (as it should).
   // The following line associates the newly created shared_ptr<Surface> object with it's internal
   // surface implementation object, m_pImpl.
   ptr->m_pImpl->SetSurface(ptr.get()->weak_from_this());
   return ptr;
}

std::shared_ptr<Surface> Surface::Create(const Surface& surface)
{
   auto ptr = std::shared_ptr<Surface>(new Surface(surface));
   ptr->m_pImpl->SetSurface(ptr.get()->weak_from_this());
   return ptr;
}

std::shared_ptr<Surface> Surface::Create(IndexType nSegments,IndexType alignmentPointIdx,IndexType profilePointIdx)
{
   auto surface = Surface::Create();
   surface->SetSurfaceTemplateSegmentCount(nSegments);
   surface->SetAlignmentPoint(alignmentPointIdx);
   surface->SetProfileGradePoint(profilePointIdx);
   return surface;
}

Surface::Surface()
{
   m_pImpl = std::make_unique<SurfaceImpl>();
}

Surface::Surface(const Surface& surface)
{
   m_pImpl = std::make_unique<SurfaceImpl>(*surface.m_pImpl);
}

Surface::~Surface() = default; // when using the PIMPL idiom, this is how we have to define the destructor in order to keep the compiler happy


void Surface::SetProfile(std::weak_ptr<const Profile> profile)
{
   PRECONDITION(profile.lock());
   m_pImpl->SetProfile(profile);
}

std::shared_ptr<const Profile> Surface::GetProfile() const
{
   return m_pImpl->GetProfile();
}

void Surface::SetAlignmentPoint(IndexType ridgePointIdx)
{
   m_pImpl->SetAlignmentPoint(ridgePointIdx);
}

IndexType Surface::GetAlignmentPoint() const
{
   return m_pImpl->GetAlignmentPoint();
}

void Surface::SetProfileGradePoint(IndexType ridgePointIdx)
{
   m_pImpl->SetProfileGradePoint(ridgePointIdx);
}

IndexType Surface::GetProfileGradePoint() const
{
   return m_pImpl->GetProfileGradePoint();
}

void Surface::SetSurfaceTemplateSegmentCount(IndexType nSegments)
{
   m_pImpl->SetSurfaceTemplateSegmentCount(nSegments);
}

IndexType Surface::GetSurfaceTemplateSegmentCount() const
{
   return m_pImpl->GetSurfaceTemplateSegmentCount();
}

std::shared_ptr<SurfaceTemplate> Surface::CreateSurfaceTemplate(const Station& station)
{
   // create new template at specified station
   auto surface_template = SurfaceTemplate::Create(station);
   surface_template->SetSurface(weak_from_this()); // associate with this surface
   m_pImpl->AddSurfaceTemplate(surface_template); // pass it on to the implementation class to manage storage
   return surface_template;
}

const std::vector<std::shared_ptr<SurfaceTemplate>>& Surface::GetSurfaceTemplates()
{
   return m_pImpl->GetSurfaceTemplates();
}

std::pair<std::shared_ptr<SurfaceTemplate>, std::shared_ptr<SurfaceTemplate>> Surface::GetBoundingTemplates(const Station& station) const
{
   return m_pImpl->GetBoundingTemplates(station);
}

void Surface::ClearSurfaceTemplates()
{
   m_pImpl->ClearSurfaceTemplates();
}

WBFL::Geometry::LineSegment2d Surface::GetStartBoundaryLine() const
{
   return m_pImpl->GetStartBoundaryLine();
}

WBFL::Geometry::LineSegment2d Surface::GetEndBoundaryLine() const
{
   return m_pImpl->GetEndBoundaryLine();
}

std::pair<Station, Station> Surface::GetStationRange() const
{
   return m_pImpl->GetStationRange();
}

bool Surface::ContainsStation(const Station& station) const
{
   return m_pImpl->ContainsStation(station);
}

std::shared_ptr<SurfaceTemplate> Surface::CreateSurfaceTemplateSectionCut(const Station& station, bool bApplySuperelevations) const
{
   auto surface_template = SurfaceTemplate::Create(station);
   surface_template->SetSurface(weak_from_this());
   m_pImpl->ConfigureSurfaceTemplate(surface_template, bApplySuperelevations); // don't need to pass in station here. station is a property of surface_template .
   return surface_template;
}

std::shared_ptr<SurfaceProfile> Surface::CreateSurfaceProfileSectionCut(const Station& station, const Angle& skewAngle, bool bApplySuperelevations) const
{
   // need to create the SurfaceProfile here and associated it with this Surface object
   // SurfaceImpl is not a friend of SurfaceProfile
   auto surface_profile = SurfaceProfile::Create();
   surface_profile->SetSurface(weak_from_this());
   m_pImpl->ConfigureSurfaceProfile(surface_profile, station, skewAngle, bApplySuperelevations);
   return surface_profile;
}

void Surface::AddSuperelevation(std::shared_ptr<Superelevation> superelevation)
{
   PRECONDITION(superelevation->GetSurface() == nullptr);
   superelevation->SetSurface(weak_from_this());
   m_pImpl->AddSuperelevation(superelevation);
}

std::shared_ptr<Superelevation> Surface::FindSuperelevation(const Station& station) const
{
   return m_pImpl->FindSuperelevation(station);
}

void Surface::ClearSuperelevations()
{
   m_pImpl->ClearSuperelevations();
}

void Surface::AddWidening(std::shared_ptr<Widening> widening)
{
   PRECONDITION(widening->GetSurface() == nullptr);
   widening->SetSurface(weak_from_this());
   m_pImpl->AddWidening(widening);
}

std::shared_ptr<Widening> Surface::FindWidening(const Station& station) const
{
   return m_pImpl->FindWidening(station);
}

void Surface::ClearWidenings()
{
   m_pImpl->ClearWidenings();
}
