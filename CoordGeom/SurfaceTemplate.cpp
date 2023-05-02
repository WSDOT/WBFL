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
#include <CoordGeom/SurfaceTemplate.h>
#include <CoordGeom/Surface.h>
#include <CoordGeom/Profile.h>
#include "SurfaceTemplateImpl.h"

using namespace WBFL::COGO;

std::shared_ptr<SurfaceTemplate> SurfaceTemplate::Create(const Station& station)
{
   return std::shared_ptr<SurfaceTemplate>(new SurfaceTemplate(station));
}

std::shared_ptr<SurfaceTemplate> SurfaceTemplate::Create(const SurfaceTemplate& surfaceTemplate)
{
   return std::shared_ptr<SurfaceTemplate>(new SurfaceTemplate(surfaceTemplate));
}

SurfaceTemplate::SurfaceTemplate(const Station& station)
{
   m_pImpl = std::make_unique<SurfaceTemplateImpl>(station);
}

SurfaceTemplate::SurfaceTemplate(const SurfaceTemplate& surfaceTemplate)
{
   m_pImpl = std::make_unique<SurfaceTemplateImpl>(*surfaceTemplate.m_pImpl);

   // The default constructor of the implementation class copies the surface data member.
   // A newly created surface template object should not be associated with a surface,
   // so set the surface to nullptr
   m_pImpl->SetSurface(std::shared_ptr<Surface>(nullptr));
}

SurfaceTemplate::~SurfaceTemplate() = default;

void SurfaceTemplate::SetSurface(std::weak_ptr<const Surface> surface)
{
   m_pImpl->SetSurface(surface);
}

std::shared_ptr<const Surface> SurfaceTemplate::GetSurface() const
{
   return m_pImpl->GetSurface();
}

const Station& SurfaceTemplate::GetStation() const
{
   return m_pImpl->GetStation();
}

std::tuple<Float64, Float64, SurfaceTemplateSegment::SlopeType> SurfaceTemplate::GetSegmentParameters(IndexType segmentIdx)
{
   return m_pImpl->GetSegmentParameters(segmentIdx);
}

void SurfaceTemplate::UpdateSegmentParameters(IndexType segmentIdx, Float64 width, Float64 slope, SurfaceTemplateSegment::SlopeType slopeType)
{
   m_pImpl->UpdateSegmentParameters(segmentIdx, width, slope, slopeType);
}

IndexType SurfaceTemplate::GetCount() const
{
   return m_pImpl->GetCount();
}

SurfaceTemplateSegment& SurfaceTemplate::GetSegment(IndexType idx)
{
   return m_pImpl->GetSegment(idx);
}

const SurfaceTemplateSegment& SurfaceTemplate::GetSegment(IndexType idx) const
{
   return m_pImpl->GetSegment(idx);
}

void SurfaceTemplate::Clear()
{
   m_pImpl->Clear();
}

Float64 SurfaceTemplate::GetRidgePointElevationChange(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   return m_pImpl->GetRidgePointElevationChange(ridgePoint1Idx, ridgePoint2Idx);
}

Float64 SurfaceTemplate::GetElevationChange(IndexType ridgePointIdx, Float64 offset) const
{
   return m_pImpl->GetElevationChange(ridgePointIdx, offset);
}

Float64 SurfaceTemplate::GetSlope(IndexType ridgePointIdx, Float64 offset) const
{
   return m_pImpl->GetSlope(ridgePointIdx, offset);
}

Float64 SurfaceTemplate::GetSegmentSlope(IndexType idx) const
{
   return m_pImpl->GetSegmentSlope(idx);
}

Float64 SurfaceTemplate::GetRidgePointOffset(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   return m_pImpl->GetRidgePointOffset(ridgePoint1Idx, ridgePoint2Idx);
}

Float64 SurfaceTemplate::GetRidgePointElevation(IndexType ridgePointIdx) const
{
   return m_pImpl->GetRidgePointElevation(ridgePointIdx);
}

std::pair<Float64,Float64> SurfaceTemplate::GetRidgePointOffsetAndElevation(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   return m_pImpl->GetRidgePointOffsetAndElevation(ridgePoint1Idx, ridgePoint2Idx);
}

#if defined _UNITTEST
#include <CoordGeom/Alignment.h>
#include <CoordGeom/ProfileSegment.h>
bool SurfaceTemplate::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("SurfaceTemplate");

   auto alignment = Alignment::Create();
   auto profile = Profile::Create();
   Float64 elev = 100.0;
   auto segment = ProfileSegment::Create(ProfilePoint(0.0, elev), ProfilePoint(100.0, elev));
   profile->AddProfileElement(segment); // flat profile at elevation 100
   auto surface = Surface::Create(4,2,2);
   profile->AddSurface(0, surface);
   alignment->AddProfile(0, profile);

   auto surface_template = surface->CreateSurfaceTemplate(0.00);
   surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

   TRY_TESTME(IsEqual(surface_template->GetRidgePointElevationChange(0, 4), 0.0));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointElevationChange(0, 1), 0.4));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointElevationChange(1, 2), 0.2));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointElevationChange(2, 3), -0.2));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointElevationChange(3, 4), -0.4));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointElevationChange(0, 2), 0.6));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointElevationChange(2, 4), -0.6));

   TRY_TESTME(IsEqual(surface_template->GetElevationChange(0, -5.0), 0.0));
   TRY_TESTME(IsEqual(surface_template->GetElevationChange(0, 5.0), 0.2));
   TRY_TESTME(IsEqual(surface_template->GetElevationChange(1, -5.0), -0.2));
   TRY_TESTME(IsEqual(surface_template->GetElevationChange(1, 5.0), 0.1));
   TRY_TESTME(IsEqual(surface_template->GetElevationChange(4, -5.0), 0.2));
   TRY_TESTME(IsEqual(surface_template->GetElevationChange(4, 5.0), 0.0));
   TRY_TESTME(IsEqual(surface_template->GetElevationChange(2, -5.0), -0.1));
   TRY_TESTME(IsEqual(surface_template->GetElevationChange(2, 5.0), -0.1));

   TRY_TESTME(IsEqual(surface_template->GetSlope(0, -5.0), 0.0));
   TRY_TESTME(IsEqual(surface_template->GetSlope(0,  5.0), 0.04));
   TRY_TESTME(IsEqual(surface_template->GetSlope(1, -5.0), 0.04));
   TRY_TESTME(IsEqual(surface_template->GetSlope(1, 5.0), 0.02));
   TRY_TESTME(IsEqual(surface_template->GetSlope(4, -5.0), -0.04));
   TRY_TESTME(IsEqual(surface_template->GetSlope(4, 5.0), 0.0));
   TRY_TESTME(IsEqual(surface_template->GetSlope(2, -5.0), 0.02));
   TRY_TESTME(IsEqual(surface_template->GetSlope(2, 5.0), -0.02));

   TRY_TESTME(IsEqual(surface_template->GetSegmentSlope(0), 0.04));
   TRY_TESTME(IsEqual(surface_template->GetSegmentSlope(1), 0.02));
   TRY_TESTME(IsEqual(surface_template->GetSegmentSlope(2), -0.02));
   TRY_TESTME(IsEqual(surface_template->GetSegmentSlope(3), -0.04));

   TRY_TESTME(IsEqual(surface_template->GetRidgePointOffset(0, 4), 40.0));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointOffset(4, 0), -40.0));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointOffset(0, 1), 10.0));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointOffset(1, 2), 10.0));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointOffset(2, 3), 10.0));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointOffset(3, 4), 10.0));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointOffset(0, 2), 20.0));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointOffset(2, 4), 20.0));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointOffset(4, 2), -20.0));
   TRY_TESTME(IsEqual(surface_template->GetRidgePointOffset(2, 2), 0.0));

   TRY_TESTME(surface_template->GetRidgePointOffsetAndElevation(0, 0) == std::make_pair(0.0, elev - 0.6));
   TRY_TESTME(surface_template->GetRidgePointOffsetAndElevation(0, 4) == std::make_pair(40.0, elev - 0.6));
   TRY_TESTME(surface_template->GetRidgePointOffsetAndElevation(0, 1) == std::make_pair(10.0, elev - 0.2));
   TRY_TESTME(surface_template->GetRidgePointOffsetAndElevation(1, 0) == std::make_pair(-10.0, elev - 0.6));
   TRY_TESTME(surface_template->GetRidgePointOffsetAndElevation(2, 4) == std::make_pair(20.0, elev - 0.6));
   TRY_TESTME(surface_template->GetRidgePointOffsetAndElevation(4, 2) == std::make_pair(-20.0, elev));
   TRY_TESTME(surface_template->GetRidgePointOffsetAndElevation(2, 3) == std::make_pair(10.0, elev - 0.2));
   TRY_TESTME(surface_template->GetRidgePointOffsetAndElevation(3, 4) == std::make_pair(10.0, elev - 0.6));

   TESTME_EPILOG("SurfaceTemplate");
}
#endif // _UNITTEST


