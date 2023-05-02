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
#include <CoordGeom/SurfaceProfile.h>

using namespace WBFL::COGO;

std::shared_ptr<SurfaceProfile> SurfaceProfile::Create()
{
   return std::shared_ptr<SurfaceProfile>(new SurfaceProfile);
}

SurfaceProfile::SurfaceProfile(const Station& station)
{
   // need better constructors
}

void SurfaceProfile::SetSurface(std::weak_ptr<const Surface> surface)
{
   m_Surface = surface;
}

std::shared_ptr<const Surface> SurfaceProfile::GetSurface() const
{
   return m_Surface.lock();
}

void SurfaceProfile::SetStation(const Station& station)
{
   m_Station = station;
}

const Station& SurfaceProfile::GetStation() const
{
   return m_Station;
}

void SurfaceProfile::SetSkewAngle(const Angle& skewAngle)
{
   m_SkewAngle = skewAngle;
}

const Angle& SurfaceProfile::GetSkewAngle() const
{
   return m_SkewAngle;
}

void SurfaceProfile::SetDirection(const Direction& direction)
{
   m_Direction = direction;
}

const Direction& SurfaceProfile::GetDirection() const
{
   return m_Direction;
}

std::shared_ptr<SurfacePoint> SurfaceProfile::CreateSurfacePoint(const Station& station, Float64 normalOffset, Float64 cutlineOffset, Float64 elevation, const WBFL::Geometry::Point2d& location) 
{
   m_SurfacePoints.emplace_back(SurfacePoint::Create(station, normalOffset, cutlineOffset, elevation, location));
   auto surface_point = m_SurfacePoints.back();
   surface_point->SetSurface(GetSurface());
   return surface_point;
}

IndexType SurfaceProfile::GetSurfacePointCount() const
{
   return m_SurfacePoints.size();
}

std::shared_ptr<SurfacePoint> SurfaceProfile::GetSurfacePoint(IndexType surfacePointIdx)
{
   return m_SurfacePoints[surfacePointIdx];
}

std::shared_ptr<const SurfacePoint> SurfaceProfile::GetSurfacePoint(IndexType surfacePointIdx) const
{
   return m_SurfacePoints[surfacePointIdx];
}

Float64 SurfaceProfile::GetSurfacePointElevationChange(IndexType surfacePoint1Idx, IndexType surfacePoint2Idx) const
{
   // computes the change in elevation between two surface points
   auto surface_point_1 = GetSurfacePoint(surfacePoint1Idx);
   auto surface_point_2 = GetSurfacePoint(surfacePoint2Idx);
   return surface_point_2->GetElevation() - surface_point_1->GetElevation();
}

Float64 SurfaceProfile::GetElevationChange(IndexType surfacePointIdx, Float64 offset) const
{
   // Computes the change in elevation between a surface point and an offset measured from the surface point
   Float64 sign = ::BinarySign(offset);

   Float64 delta = 0;
   if (0 <= offset)
   {
      // working left to right from the specified surface point
      Float64 running_offset = 0;
      IndexType nSurfacePoints = m_SurfacePoints.size();
      for (IndexType idx = surfacePointIdx; idx < nSurfacePoints - 1; idx++)
      {
         const auto& surface_point_1 = GetSurfacePoint(idx);
         const auto& surface_point_2 = GetSurfacePoint(idx + 1);

         auto dist = surface_point_2->GetLocation().Distance(surface_point_1->GetLocation());

         auto pnt1 = surface_point_1->GetPoint();
         auto pnt2 = surface_point_2->GetPoint();
         auto dz = pnt2.Z() - pnt1.Z();

         if (offset < (running_offset + dist))
         {
            // the second point is beyond the point we are looking for
            // get the distance to the point
            auto z = offset - running_offset;
            dz = ::LinInterp(z, pnt1.Z(), pnt2.Z(), dist);
            delta += dz;
            break; // don't go any further
         }
         delta += dz;
         running_offset += dist;
      }
   }
   else
   {
      // working right to left from the specified surface point
      Float64 running_offset = 0;
      for (IndexType idx = surfacePointIdx; 0 < idx; idx--)
      {
         auto surface_point_1 = GetSurfacePoint(idx - 1);
         auto surface_point_2 = GetSurfacePoint(idx);

         auto dist = surface_point_2->GetLocation().Distance(surface_point_1->GetLocation());

         auto pnt1 = surface_point_1->GetPoint();
         auto pnt2 = surface_point_2->GetPoint();
         auto dz = pnt2.Z() - pnt1.Z();

         if ((running_offset - dist) < offset)
         {
            // the first point is before the point we are looking for
            // get the distance to the point
            auto z = running_offset - offset;
            dz = ::LinInterp(z, pnt2.Z(), pnt1.Z(), dist);
            delta += dz;
            break; // don't go any further
         }
         delta += dz;
         running_offset -= dist;
      }
   }

   return delta;
}

Float64 SurfaceProfile::GetSlope(IndexType surfacePointIdx, Float64 offset) const
{
   Float64 slope = 0.0;

   if (0 <= offset)
   {
      // working left to right from the specified surface point
      Float64 leftEdge = 0;
      IndexType nSurfacePoints = m_SurfacePoints.size();
      for (IndexType idx = surfacePointIdx; idx < nSurfacePoints - 1; idx++)
      {
         const auto& surface_point_1 = GetSurfacePoint(idx);
         const auto& surface_point_2 = GetSurfacePoint(idx + 1);

         auto dist = surface_point_2->GetLocation().Distance(surface_point_1->GetLocation());

         auto pnt1 = surface_point_1->GetPoint();
         auto pnt2 = surface_point_2->GetPoint();
         auto dz = pnt2.Z() - pnt1.Z();

         if (::InRange(leftEdge, offset, leftEdge + dist))
         {
            slope = dz / dist;
            break;
         }

         leftEdge += dist;
      }
   }
   else
   {
      // working right to left from the specified surface point
      Float64 rightEdge = 0;
      for (IndexType idx = surfacePointIdx - 1; 0 < idx; idx--)
      {
         auto surface_point_1 = GetSurfacePoint(idx - 1);
         auto surface_point_2 = GetSurfacePoint(idx);

         auto dist = surface_point_2->GetLocation().Distance(surface_point_1->GetLocation());

         auto pnt1 = surface_point_1->GetPoint();
         auto pnt2 = surface_point_2->GetPoint();
         auto dz = pnt2.Z() - pnt1.Z();


         if (::InRange(rightEdge - dist, offset, rightEdge))
         {
            slope = dz / dist;
            break;
         }

         rightEdge -= dist;
      }
   }

   return slope;
}

Float64 SurfaceProfile::GetSegmentSlope(IndexType segmentIdx) const
{
   auto surface_point_1 = GetSurfacePoint(segmentIdx);
   auto surface_point_2 = GetSurfacePoint(segmentIdx+1);

   auto pnt1 = surface_point_1->GetPoint();
   auto pnt2 = surface_point_2->GetPoint();

   auto dist = surface_point_2->GetLocation().Distance(surface_point_1->GetLocation());

   auto dz = pnt2.Z() - pnt1.Z();

   return IsZero(dist) ? Float64_Max : dz / dist;
}

Float64 SurfaceProfile::GetSurfacePointOffset(IndexType surfacePointIdx) const
{
   return GetSurfacePoint(surfacePointIdx)->GetCutlineOffset();
}

std::pair<Float64,Float64> SurfaceProfile::GetSurfacePointOffsetAndElevation(IndexType surfacePointIdx) const
{
   auto sp = GetSurfacePoint(surfacePointIdx);
   return std::make_pair(sp->GetCutlineOffset(), sp->GetElevation());
}


#if defined _UNITTEST
#include <CoordGeom/Alignment.h>
#include <CoordGeom/ProfileSegment.h>
bool SurfaceProfile::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("SurfaceProfile");

   auto alignment = Alignment::Create();
   auto profile = Profile::Create();
   Float64 station1 = 0.0;
   Float64 station2 = 100.0;
   Float64 elev1 = 10.0;
   Float64 elev2 = 20.0;
   auto segment = ProfileSegment::Create(ProfilePoint(station1, elev1), ProfilePoint(station2, elev2));
   profile->AddProfileElement(segment); // uphill profile with a 10 ft rise over 100 ft
   auto surface = Surface::Create(4, 2, 2);
   profile->AddSurface(0, surface);
   alignment->AddProfile(0, profile);

   auto surface_template = surface->CreateSurfaceTemplate(station1);
   surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

   surface_template = surface->CreateSurfaceTemplate(station2);
   surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

   // cut with a 45 degree right skew
   Float64 cut_station = (station1 + station2) / 2;
   auto surface_profile = surface->CreateSurfaceProfileSectionCut(cut_station, M_PI / 4, true);
   TRY_TESTME(surface_profile->GetSurface() == surface);
   TRY_TESTME(surface_profile->GetSkewAngle() == Angle(M_PI / 4));
   TRY_TESTME(surface_profile->GetDirection() == Direction(M_PI / 4));

   auto surface_point = surface_profile->GetSurfacePoint(0);
   TRY_TESTME(surface_point->GetSurface() == surface);
   TRY_TESTME(surface_point->GetStation() == Station(70.0));
   TRY_TESTME(IsEqual(surface_point->GetNormalOffset(), -20.0));
   TRY_TESTME(IsEqual(surface_point->GetCutlineOffset(), -28.284271247461902));
   TRY_TESTME(IsEqual(surface_point->GetElevation(), 16.4));
   TRY_TESTME(surface_point->GetPoint() == WBFL::Geometry::Point3d(70, 20, 16.4));

   surface_point = surface_profile->GetSurfacePoint(4);
   TRY_TESTME(surface_point->GetSurface() == surface);
   TRY_TESTME(surface_point->GetStation() == Station(30.0));
   TRY_TESTME(IsEqual(surface_point->GetNormalOffset(), 20.0));
   TRY_TESTME(IsEqual(surface_point->GetCutlineOffset(), 28.284271247461902));
   TRY_TESTME(IsEqual(surface_point->GetElevation(), 12.4));
   TRY_TESTME(surface_point->GetPoint() == WBFL::Geometry::Point3d(30, -20, 12.4));

   // cut with a 45 degree left skew
   surface_profile = surface->CreateSurfaceProfileSectionCut(cut_station, -M_PI / 4, true);
   TRY_TESTME(surface_profile->GetSurface() == surface);
   TRY_TESTME(surface_profile->GetSkewAngle() == Angle(-M_PI / 4));
   TRY_TESTME(surface_profile->GetDirection() == Direction(3 * M_PI / 4));

   surface_point = surface_profile->GetSurfacePoint(0);
   TRY_TESTME(surface_point->GetSurface() == surface);
   TRY_TESTME(surface_point->GetStation() == Station(30.0));
   TRY_TESTME(IsEqual(surface_point->GetNormalOffset(), -20.0));
   TRY_TESTME(IsEqual(surface_point->GetCutlineOffset(), -28.284271247461902));
   TRY_TESTME(IsEqual(surface_point->GetElevation(), 12.4));
   TRY_TESTME(surface_point->GetPoint() == WBFL::Geometry::Point3d(30, 20, 12.4));

   surface_point = surface_profile->GetSurfacePoint(4);
   TRY_TESTME(surface_point->GetSurface() == surface);
   TRY_TESTME(surface_point->GetStation() == Station(70.0));
   TRY_TESTME(IsEqual(surface_point->GetNormalOffset(), 20.0));
   TRY_TESTME(IsEqual(surface_point->GetCutlineOffset(), 28.284271247461902));
   TRY_TESTME(IsEqual(surface_point->GetElevation(), 16.4));
   TRY_TESTME(surface_point->GetPoint() == WBFL::Geometry::Point3d(70, -20, 16.4));

   TESTME_EPILOG("SurfaceProfile");
}
#endif // _UNITTEST


