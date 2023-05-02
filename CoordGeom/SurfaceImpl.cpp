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
#include "SurfaceImpl.h"
#include <CoordGeom/Alignment.h>
#include <CoordGeom/Profile.h>
#include <CoordGeom/Utilities.h>
#include <CoordGeom/XCoordGeom.h>


#include <GeomModel/GeomOp2d.h>

using namespace WBFL::COGO;

SurfaceImpl::SurfaceImpl(const SurfaceImpl& surfaceImpl)
{
   m_SurfaceTemplateSegmentCount = surfaceImpl.m_SurfaceTemplateSegmentCount;

   m_AlignmentPoint = surfaceImpl.m_AlignmentPoint;
   m_ProfileGradePoint = surfaceImpl.m_ProfileGradePoint;

   for (const auto& surface_template : m_SurfaceTemplates)
   {
      AddSurfaceTemplate(SurfaceTemplate::Create(*surface_template));
   }

   for (const auto& superelevation : m_Superelevations)
   {
      AddSuperelevation(Superelevation::Create(*superelevation));
   }

   for (const auto& widening : m_Widenings)
   {
      AddWidening(Widening::Create(*widening));
   }
}

void SurfaceImpl::SetSurface(std::weak_ptr<const Surface> surface)
{
   m_Surface = surface;
}

std::shared_ptr<const Surface> SurfaceImpl::GetSurface() const
{
   return m_Surface.lock();
}

void SurfaceImpl::SetProfile(std::weak_ptr<const Profile> profile)
{
   m_Profile = profile;

   // if surface templates are defined before this surface is associated with
   // a profile, the templates are not sorted. Do the sorting now to guarantee
   // the are property sorted
   SortSurfaceTemplates();
}

std::shared_ptr<const Profile> SurfaceImpl::GetProfile() const
{
   return m_Profile.lock();
}

void SurfaceImpl::SetAlignmentPoint(IndexType ridgePointIdx)
{
   PRECONDITION(ridgePointIdx != INVALID_INDEX);
   m_AlignmentPoint = ridgePointIdx;
}

IndexType SurfaceImpl::GetAlignmentPoint() const
{
   return m_AlignmentPoint;
}

void SurfaceImpl::SetProfileGradePoint(IndexType ridgePointIdx)
{
   PRECONDITION(ridgePointIdx != INVALID_INDEX);
   m_ProfileGradePoint = ridgePointIdx;
}

IndexType SurfaceImpl::GetProfileGradePoint() const
{
   return m_ProfileGradePoint;
}

void SurfaceImpl::SetSurfaceTemplateSegmentCount(IndexType nSegments)
{
   if (m_SurfaceTemplateSegmentCount != nSegments)
   {
      // all surface templates must have the same number of segments
      // if the number of segments is changing, clear out all previously
      // defined templates because they will be invalid
      m_SurfaceTemplateSegmentCount = nSegments;
      m_SurfaceTemplates.clear();
      m_RidgeLines.clear();
   }
}

IndexType SurfaceImpl::GetSurfaceTemplateSegmentCount() const
{
   return m_SurfaceTemplateSegmentCount;
}

void SurfaceImpl::AddSurfaceTemplate(std::shared_ptr<SurfaceTemplate> surfaceTemplate)
{
   // add it to the collection
   m_SurfaceTemplates.emplace_back(surfaceTemplate);
   m_RidgeLines.clear();

   // sort the collection based on station
   SortSurfaceTemplates();
}

const std::vector<std::shared_ptr<SurfaceTemplate>>& SurfaceImpl::GetSurfaceTemplates()
{
   return m_SurfaceTemplates;
}

std::pair<std::shared_ptr<SurfaceTemplate>, std::shared_ptr<SurfaceTemplate>> SurfaceImpl::GetBoundingTemplates(const Station& station) const
{
   PRECONDITION(!m_SurfaceTemplates.empty());
   
   // Templates at ends extend infinitely up/down station
   // Deal with special cases first
   if (m_SurfaceTemplates.size() == 1)
   {
      // only one template. It bounds all
      return std::make_pair(m_SurfaceTemplates.front(), m_SurfaceTemplates.back());
   }
   else
   {
      // Check if station is before or after all templates
      auto alignment = GetProfile()->GetAlignment();
      const auto& station_front = m_SurfaceTemplates.front()->GetStation();
      if (alignment->CompareStations(m_SurfaceTemplates.front()->GetStation(), station) <= 0)
      {
         // station is before the start of the templates. use the front template for the bracket
         return std::make_pair(m_SurfaceTemplates.front(), m_SurfaceTemplates.front());
      }
      else
      {
         if(0 <= alignment->CompareStations(m_SurfaceTemplates.back()->GetStation(),station))
         {
            // station is after end of templates. use back template for bracket
            return std::make_pair(m_SurfaceTemplates.back(), m_SurfaceTemplates.back());
         }
         else
         {
            // station is in between two templates - find bracketing templates
            auto iter1(m_SurfaceTemplates.begin());
            auto iter2(std::next(iter1));
            auto end(m_SurfaceTemplates.end());
            for (; iter2 != end; iter1++, iter2++)
            {
               const auto& template1(*iter1);
               const auto& template2(*iter2);

               if (0 <= alignment->CompareStations(template1->GetStation(),station) && // station is at or after station1
                   0 <= alignment->CompareStations(station,template2->GetStation()))  // station is at or before station2
               {
                  // station is between station1 and station2... these are the templates that we want
                  return std::make_pair(template1, template2);
               }
            }
         }
      }
   }

   // if we get here, something went wrong
   CHECK(false);
   return std::make_pair(nullptr, nullptr);
}

void SurfaceImpl::ClearSurfaceTemplates()
{
   m_SurfaceTemplates.clear();
   m_RidgeLines.clear();
}

WBFL::Geometry::LineSegment2d SurfaceImpl::GetStartBoundaryLine() const
{
   PRECONDITION(!m_SurfaceTemplates.empty());
   return CreateTemplateLine(m_SurfaceTemplates.front());
}

WBFL::Geometry::LineSegment2d SurfaceImpl::GetEndBoundaryLine() const
{
   // this is the plan view line for the last surface template
   PRECONDITION(!m_SurfaceTemplates.empty());
   return CreateTemplateLine(m_SurfaceTemplates.back());
}

std::pair<Station, Station> SurfaceImpl::GetStationRange() const
{
   PRECONDITION(!m_SurfaceTemplates.empty());
   return std::make_pair(m_SurfaceTemplates.front()->GetStation(), m_SurfaceTemplates.back()->GetStation());
}

bool SurfaceImpl::ContainsStation(const Station& station) const
{
   auto boundary_stations = GetStationRange();
   auto alignment = GetProfile()->GetAlignment();
   auto result1 = alignment->CompareStations(boundary_stations.first, station);
   auto result2 = alignment->CompareStations(station, boundary_stations.second);
   if (0 <= result1 && 0 <= result2)
   {
      // station is between surface boundary stations
      return true;
   }
   else
   {
      return false;
   }
}

void SurfaceImpl::ConfigureSurfaceTemplate(std::shared_ptr<SurfaceTemplate> surfaceTemplate, bool bApplySuperelevations) const
{
   PRECONDITION(surfaceTemplate->GetSurface() == GetSurface());

   // Creates the actual surface at the specified station. If bApplySuperelevationsAndWidenings is true
   // the surface is adjusted for superelevations and widenings, otherwise the surface is based on
   // the basic templates alone.

   const auto& station = surfaceTemplate->GetStation();

   // Find the two surface templates that bound the station.
   std::shared_ptr<SurfaceTemplate> template1, template2;
   std::tie(template1, template2) = GetBoundingTemplates(station);

   // number of templates segments must be the same in both templates
   auto nSegments1 = template1->GetCount();
   auto nSegments2 = template2->GetCount();
   CHECK(nSegments1 == nSegments2); // Number of template segments must the be the same in adjacent surface templates.

   // interpolation factor

   auto alignment = GetProfile()->GetAlignment();
   Float64 sta = alignment->ConvertToNormalizedStation(station).GetValue();
   Float64 sta1 = alignment->ConvertToNormalizedStation(template1->GetStation()).GetValue();
   Float64 sta2 = alignment->ConvertToNormalizedStation(template2->GetStation()).GetValue();

   Float64 factor = IsZero(sta2 - sta1) ? 0 : (sta - sta1) / (sta2 - sta1);
   // interpolated value = (factor)(value2-value1) + value1

   for (IndexType segIdx = 0; segIdx < nSegments1; segIdx++)
   {
      // Get these values from the Template
      Float64 width1, width2;
      Float64 slope1, slope2;
      SurfaceTemplateSegment::SlopeType slopeType1, slopeType2;

      const auto& segment1 = template1->GetSegment(segIdx);
      const auto& segment2 = template2->GetSegment(segIdx);

      std::tie(width1, slope1, slopeType1) = segment1.GetParameters();
      std::tie(width2, slope2, slopeType2) = segment2.GetParameters();

      if (slopeType1 != slopeType2 && (slopeType1 == SurfaceTemplateSegment::SlopeType::Horizontal || slopeType2 == SurfaceTemplateSegment::SlopeType::Horizontal))
      {
         // cannot interpolate between slopes if one is fixed and one is not
         // (what is the resulting slope? fixed/not fixed???)
         CHECK(false);
         THROW_COGO(WBFL_COGO_E_SURFACESLOPEMISMATCHERROR);
      }

      // Interpolate slope
      Float64 slope = 0;
      SurfaceTemplateSegment::SlopeType slopeType = SurfaceTemplateSegment::SlopeType::Horizontal;
      if ((slopeType1 != SurfaceTemplateSegment::SlopeType::Horizontal || slopeType2 != SurfaceTemplateSegment::SlopeType::Horizontal) && slopeType1 != slopeType2)
      {
         // interpolation is a little bit tricky because one slope is fixed horizontal and one is fixed vertical
         // Convert slopes so that they are both horizontal.
         Float64 s1 = (slopeType1 == SurfaceTemplateSegment::SlopeType::FixedVertical ? (IsZero(slope1, 0.00001) ? ::BinarySign(slope1) * Float64_Max : 1 / slope1) : slope1);
         Float64 s2 = (slopeType2 == SurfaceTemplateSegment::SlopeType::FixedVertical ? (IsZero(slope2, 0.00001) ? ::BinarySign(slope2) * Float64_Max : 1 / slope2) : slope2);
         slope = factor * (s2 - s1) + s1;
         slopeType = SurfaceTemplateSegment::SlopeType::FixedHorizontal;
      }
      else
      {
         slopeType = slopeType1;
         slope = factor * (slope2 - slope1) + slope1;
      }

      // Interpolate width
      Float64 width = factor * (width2 - width1) + width1;

      // Add widening
      Float64 widening = GetWidening(station, segIdx);
      width += widening;

      if (bApplySuperelevations)
      {
         // Add superelevation
         std::tie(slope,slopeType) = GetSuperelevatedSlope(station, segIdx, slope, slopeType);
      }

      // Add to segment we are created
      surfaceTemplate->UpdateSegmentParameters(segIdx, width, slope, slopeType);
   }
}

void SurfaceImpl::ConfigureSurfaceProfile(std::shared_ptr<SurfaceProfile> surfaceProfile, const Station& station, const Angle& skewAngle, bool bApplySuperelevations) const
{
   // create the cut line
   auto alignment = GetProfile()->GetAlignment();
   auto normal = alignment->GetNormal(station); // this is the normal to the right, we need to increment the normal to the left by the skew angle
   normal.Increment(M_PI);
   auto direction = normal.IncrementBy(-skewAngle); // increment with the skew angle to get the direction of the cutting line. positive skews to the right so use the negative of the skew angle
   auto point_on_alignment = alignment->LocatePoint(station, OffsetType::AlongDirection, 0.0, direction);

   surfaceProfile->SetSkewAngle(skewAngle);
   surfaceProfile->SetDirection(direction);

   auto cutLine = WBFL::Geometry::Line2d(point_on_alignment, WBFL::Geometry::Vector2d(1.0, direction)); 

   UpdateRidgeLines();

   IndexType nSubSurfaces = m_SurfaceTemplates.size();
   nSubSurfaces--;
   CHECK(m_RidgeLines.size() == nSubSurfaces);
   for (IndexType subSurfaceIdx = 0; subSurfaceIdx < nSubSurfaces; subSurfaceIdx++)
   {
      const auto& vRidgeLines = m_RidgeLines[subSurfaceIdx];
      IndexType nRidgeLines = vRidgeLines.size();
      for (IndexType ridgeLineIdx = 0; ridgeLineIdx < nRidgeLines; ridgeLineIdx++)
      {
         const auto& ridgeLine = vRidgeLines[ridgeLineIdx];

         bool bFound;
         WBFL::Geometry::Point2d point;
         std::tie(bFound, point) = ridgeLine->Intersect(cutLine, point_on_alignment, true, true);

         if (bFound == false && (subSurfaceIdx == 0 || subSurfaceIdx == nSubSurfaces - 1))
         {
            // we are in the first or last sub-surface and the cut line didn't intersect a ridge line
            // see if it intersects the surface boundary line
            WBFL::Geometry::LineSegment2d endLine;
            if (subSurfaceIdx == 0)
            {
               endLine = GetStartBoundaryLine();
            }
            else
            {
               endLine = GetEndBoundaryLine();
            }
            WBFL::Geometry::Point2d p;
            if (0 < WBFL::Geometry::GeometricOperations::Intersect(cutLine, endLine, &p))
            {
               point = p;
               bFound = true;
            }
         }

         if (bFound)
         {
            Station station;
            Float64 normal_offset;
            std::tie(station, normal_offset) = alignment->StationAndOffset(point);
            Float64 elev = GetProfile()->Elevation(GetSurface(), station, normal_offset);

            Float64 cut_line_offset = point_on_alignment.Distance(point);
            cut_line_offset *= ::BinarySign(normal_offset);

            surfaceProfile->CreateSurfacePoint(station, normal_offset, cut_line_offset, elev, point);
         }
      }
   }
}

void SurfaceImpl::AddSuperelevation(std::shared_ptr<Superelevation> superelevation)
{
   PRECONDITION(superelevation->GetSurface() == GetSurface());

   m_Superelevations.emplace_back(superelevation);
   auto alignment = GetProfile()->GetAlignment();
   std::sort(m_Superelevations.begin(), m_Superelevations.end(), 
      [&alignment](const auto& se1, const auto& se2) 
      {
         return 0 < (alignment ? alignment->CompareStations(se1->GetBeginTransition(), se2->GetBeginTransition()) : Utilities::CompareNormalizedStations(se1->GetBeginTransition(), se2->GetBeginTransition()));
      }
   );
}

std::shared_ptr<Superelevation> SurfaceImpl::FindSuperelevation(const Station& station) const
{
   auto alignment = GetProfile()->GetAlignment();
   auto normalized_station = alignment->ConvertToNormalizedStation(station).GetValue();
   auto iter = std::find_if(m_Superelevations.begin(), m_Superelevations.end(), 
      [&alignment, &normalized_station](const auto& super) 
      {
         return InRange(alignment->ConvertToNormalizedStation(super->GetBeginTransition()).GetValue(),
                        normalized_station,
                        alignment->ConvertToNormalizedStation(super->GetEndTransition()).GetValue()); 
      }
   );

   return iter == m_Superelevations.end() ? nullptr : *iter;
}

void SurfaceImpl::ClearSuperelevations()
{
   m_Superelevations.clear();
}

void SurfaceImpl::AddWidening(std::shared_ptr<Widening> widening)
{
   PRECONDITION(widening->GetSurface() == GetSurface());
   m_Widenings.emplace_back(widening);
   auto alignment = GetProfile()->GetAlignment();
   std::sort(m_Widenings.begin(), m_Widenings.end(),
      [&alignment](const auto& se1, const auto& se2)
      {
         return 0 < (alignment ? alignment->CompareStations(se1->GetBeginTransition(), se2->GetBeginTransition()) : Utilities::CompareNormalizedStations(se1->GetBeginTransition(), se2->GetBeginTransition()));
      }
   );
}

std::shared_ptr<Widening> SurfaceImpl::FindWidening(const Station& station) const
{
   auto alignment = GetProfile()->GetAlignment();
   auto normalized_station = alignment->ConvertToNormalizedStation(station).GetValue();
   auto iter = std::find_if(m_Widenings.begin(), m_Widenings.end(),
      [&alignment, &normalized_station](const auto& super)
      {
         return InRange(alignment->ConvertToNormalizedStation(super->GetBeginTransition()).GetValue(),
         normalized_station,
         alignment->ConvertToNormalizedStation(super->GetEndTransition()).GetValue());
      }
   );

   return iter == m_Widenings.end() ? nullptr : *iter;
}

void SurfaceImpl::ClearWidenings()
{
   m_Widenings.clear();
}

std::shared_ptr<const Widening> SurfaceImpl::GetWidening(const Station& station) const
{
   // searches for the Widening that contains the specified station

   auto alignment = GetProfile()->GetAlignment();

   auto normalized_station = alignment->ConvertToNormalizedStation(station);
   for (const auto& widening : m_Widenings)
   {
      const auto& startStation = widening->GetBeginTransition();
      const auto& endStation = widening->GetEndTransition();
      if (0 <= alignment->CompareStations(startStation, station) && 0 <= alignment->CompareStations(station, endStation))
         return widening;
   }

   return std::shared_ptr<const Widening>();
}

std::shared_ptr<const Superelevation> SurfaceImpl::GetSuperelevation(const Station& station) const
{
   // searches for the Superelevation that contains the specified station

   auto alignment = GetProfile()->GetAlignment();

   auto normalized_station = alignment->ConvertToNormalizedStation(station);
   for (const auto& super : m_Superelevations)
   {
      const auto& startStation = super->GetBeginTransition();
      const auto& endStation = super->GetEndTransition();
      if (0 <= alignment->CompareStations(startStation, station) && 0 <= alignment->CompareStations(station, endStation))
         return super;
   }

   return std::shared_ptr<const Superelevation>();
}

Float64 SurfaceImpl::GetWidening(const Station& station, IndexType templateSegmentIdx) const
{
   auto widening = GetWidening(station);
   if (widening == nullptr)
      return 0.0;

   return widening->GetWidening(station, templateSegmentIdx);
}

std::pair<Float64, SurfaceTemplateSegment::SlopeType> SurfaceImpl::GetSuperelevatedSlope(const Station& station,IndexType templateSegmentIdx, Float64 slope, SurfaceTemplateSegment::SlopeType slopeType) const
{
   std::pair<Float64, SurfaceTemplateSegment::SlopeType> result;
   auto superelevation = GetSuperelevation(station);
   if (superelevation == nullptr)
   {
      // no superelevation at this station... just return the original values
      result.first = slope;
      result.second = slopeType;
   }
   else
   {
      if (slopeType == SurfaceTemplateSegment::SlopeType::Horizontal)
      {
         // slope can be adjusted by superelevation
         result.first = superelevation->GetSlope(station, slope);
         result.second = SurfaceTemplateSegment::SlopeType::Horizontal;
      }
      else
      {
         // slope is one of the fixed type.... not altered by superelevation
         // just return the original values
         result.first = slope;
         result.second = slopeType;
      }
   }

   return result;
}

WBFL::Geometry::LineSegment2d SurfaceImpl::CreateTemplateLine(std::shared_ptr<const SurfaceTemplate> surfaceTemplate) const
{
   // creates a plan view line segment that is normal to the alignment at the location of the
   // surface template. the line segment goes between the left and right ridge points
   auto alignment = GetProfile()->GetAlignment();

   const auto& station = surfaceTemplate->GetStation();
   auto normal = alignment->GetNormal(station);

   auto leftOffset = surfaceTemplate->GetRidgePointOffset(0, m_AlignmentPoint);

   IndexType nRidgePoints = surfaceTemplate->GetCount(); // this is # of template segments
   nRidgePoints++; // there is one more ridge point than segments
   
   Float64 rightOffset = surfaceTemplate->GetRidgePointOffset(nRidgePoints - 1, m_AlignmentPoint);

   auto pnt1 = alignment->LocatePoint(station, OffsetType::AlongDirection, leftOffset, normal);
   auto pnt2 = alignment->LocatePoint(station, OffsetType::AlongDirection, rightOffset, normal);

   return WBFL::Geometry::LineSegment2d(pnt1, pnt2);
}

void SurfaceImpl::UpdateRidgeLines() const
{
   if (0 < m_RidgeLines.size())
   {
      return; // ridge lines are valid
   }

   // create line segments that connect the ridge points in consecutive surface templates
   // these are lines in plan view.
   auto alignment = GetProfile()->GetAlignment();

   IndexType nTemplates = m_SurfaceTemplates.size();
   for (IndexType templateIdx = 0; templateIdx < nTemplates - 1; templateIdx++)
   {
      IndexType subSurfaceIndex = templateIdx;

      // get adjacent templates
      const auto& template1 = m_SurfaceTemplates[templateIdx];
      const auto& template2 = m_SurfaceTemplates[templateIdx+1];

      IndexType nSegments = template1->GetCount();
      CHECK(template2->GetCount() == nSegments);

      std::vector<std::shared_ptr<Path>> vRidgeLines;
      IndexType nRidgePoints = nSegments + 1;
      for (IndexType ridgePointIdx = 0; ridgePointIdx < nRidgePoints; ridgePointIdx++)
      {
         // get the offset from the alignment point to the ridge point
         auto offset1 = template1->GetRidgePointOffset(m_AlignmentPoint, ridgePointIdx);
         auto offset2 = template2->GetRidgePointOffset(m_AlignmentPoint, ridgePointIdx);

         CHECK(::IsEqual(offset1, offset2)); // we can't handle a surface that is getting wider yet

         auto path = alignment->CreateOffsetPath(offset1);
         vRidgeLines.emplace_back(path);
      }

      m_RidgeLines.insert(std::make_pair(subSurfaceIndex, vRidgeLines));
   }
}

void SurfaceImpl::SortSurfaceTemplates()
{
   // sort based on stations
   auto alignment = GetAlignment();
   std::sort(m_SurfaceTemplates.begin(), m_SurfaceTemplates.end(),
      [&alignment](const auto& t1, const auto& t2)
      {
         return 0 < (alignment ? alignment->CompareStations(t1->GetStation(), t2->GetStation()) : Utilities::CompareNormalizedStations(t1->GetStation(), t2->GetStation()));
      }
   );
}

std::shared_ptr<const Alignment> SurfaceImpl::GetAlignment()
{
   auto profile = GetProfile();
   return profile == nullptr ? nullptr : profile->GetAlignment();
}
