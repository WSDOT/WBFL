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

#if defined _UNITTEST
#include <CoordGeom/Alignment.h>
#include <CoordGeom/ProfileSegment.h>
bool Surface::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Surface");
   TRY_TESTME(TestBasicSurface(rlog));
   TRY_TESTME(TestWidenedSurface(rlog));
   TRY_TESTME(TestSuperelevatedSurface(rlog));
   TESTME_EPILOG("Surface");
}

bool Surface::TestBasicSurface(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Surface::BasicSurface");

   auto alignment = Alignment::Create();
   auto profile = Profile::Create();
   Float64 elev = 100.0;
   auto segment = ProfileSegment::Create(ProfilePoint(0.0, elev), ProfilePoint(100.0, elev));
   profile->AddProfileElement(segment); // flat profile at elevation 100
   auto surface = Surface::Create(4, 2, 2);
   profile->AddSurface(0, surface);
   alignment->AddProfile(0, profile);

   TRY_TESTME(surface->GetSurfaceTemplateSegmentCount() == 4);

   auto surface_template = surface->CreateSurfaceTemplate(0.00); // Template at Station 0+00
   surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

   surface_template = surface->CreateSurfaceTemplate(50.00); // Template at Station 0+50
   surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

   surface_template = surface->CreateSurfaceTemplate(100.00); // Template at Station 1+00
   surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

   std::shared_ptr<SurfaceTemplate> st1, st2;
   std::tie(st1, st2) = surface->GetBoundingTemplates(25.0);
   TRY_TESTME(st1->GetStation() == Station(0.00));
   TRY_TESTME(st2->GetStation() == Station(50.00));

   std::tie(st1, st2) = surface->GetBoundingTemplates(75.0);
   TRY_TESTME(st1->GetStation() == Station(50.00));
   TRY_TESTME(st2->GetStation() == Station(100.00));

   std::tie(st1, st2) = surface->GetBoundingTemplates(-50);
   TRY_TESTME(st1->GetStation() == Station(0.00));
   TRY_TESTME(st2->GetStation() == Station(0.00));

   std::tie(st1, st2) = surface->GetBoundingTemplates(200);
   TRY_TESTME(st1->GetStation() == Station(100.00));
   TRY_TESTME(st2->GetStation() == Station(100.00));

   TRY_TESTME(surface->ContainsStation(0.0) == true);
   TRY_TESTME(surface->ContainsStation(50.0) == true);
   TRY_TESTME(surface->ContainsStation(100.0) == true);
   TRY_TESTME(surface->ContainsStation(-100.0) == false);
   TRY_TESTME(surface->ContainsStation(500.0) == false);

   Station s1, s2;
   std::tie(s1, s2) = surface->GetStationRange();
   TRY_TESTME(s1 == Station(0.0));
   TRY_TESTME(s2 == Station(100.0));

   TESTME_EPILOG("Surface::BasicSurface");
}

bool Surface::TestWidenedSurface(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Surface::WidenedSurface");
   auto alignment = Alignment::Create();
   auto profile = Profile::Create();
   Float64 elev = 100.0;
   auto segment = ProfileSegment::Create(ProfilePoint(0.0, elev), ProfilePoint(100.0, elev));
   profile->AddProfileElement(segment); // flat profile at elevation 100
   auto surface = Surface::Create(4, 2, 2);
   profile->AddSurface(0, surface);
   alignment->AddProfile(0, profile);

   auto surface_template = surface->CreateSurfaceTemplate(0.00); // Template at Station 0+00
   surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

   surface_template = surface->CreateSurfaceTemplate(100.00); // Template at Station 1+00
   surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

   auto widening = Widening::Create();
   surface->AddWidening(widening);
   widening->SetSegment(0, 0);
   widening->SetSegment(1, 3);
   widening->SetWidening(10.0);
   widening->SetBeginTransition(10.0);
   widening->SetBeginFullWidening(40.0);
   widening->SetEndFullWidening(60.0);
   widening->SetEndTransition(90.0);

   auto template_cut = surface->CreateSurfaceTemplateSectionCut(-50.0, false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

   template_cut = surface->CreateSurfaceTemplateSectionCut(25.0,false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 15.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 15.0));

   template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 20.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 20.0));

   template_cut = surface->CreateSurfaceTemplateSectionCut(75.0, false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 15.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 15.0));

   template_cut = surface->CreateSurfaceTemplateSectionCut(150.0, false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

   widening->SetSegment(0, 1);
   widening->SetSegment(1, 2);

   template_cut = surface->CreateSurfaceTemplateSectionCut(25.0, false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(), 15.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(), 15.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

   template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(), 20.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(), 20.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

   template_cut = surface->CreateSurfaceTemplateSectionCut(75.0, false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(), 15.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(), 15.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

   widening->SetWidening(-10);
   template_cut = surface->CreateSurfaceTemplateSectionCut(25.0, false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(),  5.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(),  5.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

   template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(),  0.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(),  0.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

   template_cut = surface->CreateSurfaceTemplateSectionCut(75.0, false);
   TRY_TESTME(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(1).GetWidth(),  5.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(2).GetWidth(),  5.0));
   TRY_TESTME(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

   TESTME_EPILOG("Surface::WidenedSurface");
}

bool Surface::TestSuperelevatedSurface(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Surface::SuperelevatedSurface");

   auto alignment = Alignment::Create();
   auto profile = Profile::Create();
   Float64 elev = 100.0;
   auto segment = ProfileSegment::Create(ProfilePoint(0.0, elev), ProfilePoint(100.0, elev));
   profile->AddProfileElement(segment); // flat profile at elevation 100
   auto surface = Surface::Create(4, 2, 2);
   profile->AddSurface(0, surface);
   alignment->AddProfile(0, profile);

   auto surface_template1 = surface->CreateSurfaceTemplate(0.00); // Template at Station 0+00
   surface_template1->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template1->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template1->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template1->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

   auto surface_template2 = surface->CreateSurfaceTemplate(100.00); // Template at Station 1+00
   surface_template2->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template2->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template2->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template2->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

   auto superelevation = Superelevation::Create(0.0, 40, 60, 100, 0.06, 2); // pivot about center
   surface->AddSuperelevation(superelevation);

   auto template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(0), 0.06));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(1), 0.06));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(2), 0.06));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(3), 0.06));
   
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(0),  98.8));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(1),  99.4));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(2), 100.0));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(3), 100.6));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(4), 101.2));

   // pivot about left edge
   superelevation->SetPivotPoint(0);
   template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(0),  99.4));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(1), 100.0));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(2), 100.6));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(3), 101.2));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(4), 101.8));

   // pivot about right edge
   superelevation->SetPivotPoint(4);
   template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(0), 97.0));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(1), 97.6));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(2), 98.2));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(3), 98.8));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(4), 99.4));

   // Fix the slope of the outside so it isn't changed by superelevation
   surface_template1->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::FixedHorizontal);
   surface_template2->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::FixedHorizontal);
   surface_template1->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::FixedHorizontal);
   surface_template2->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::FixedHorizontal);
   superelevation->SetPivotPoint(2); // pivot about center
   template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(0), 0.04));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(1), 0.06));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(2), 0.06));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(3), -0.04));

   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(0), 99.0));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(1), 99.4));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(2), 100.0));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(3), 100.6));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(4), 100.2));

   superelevation->SetPivotPoint(0); // pivot about left edge
   template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(0), 0.04));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(1), 0.06));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(2), 0.06));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(3), -0.04));

   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(0), 99.4));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(1), 99.8));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(2), 100.4));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(3), 101.0));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(4), 100.6));

   superelevation->SetPivotPoint(4); // pivot about right edge
   template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(0), 0.04));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(1), 0.06));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(2), 0.06));
   TRY_TESTME(IsEqual(template_cut->GetSegmentSlope(3), -0.04));

   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(0), 98.2));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(1), 98.6));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(2), 99.2));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(3), 99.8));
   TRY_TESTME(IsEqual(template_cut->GetRidgePointElevation(4), 99.4));

   TESTME_EPILOG("Surface::SuperelevatedSurface");
}


#endif // _UNITTEST


