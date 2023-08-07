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
#include "ProfileImpl.h"
#include <CoordGeom/COGO.h>
#include <CoordGeom/Alignment.h>
#include <CoordGeom/Surface.h>
#include <CoordGeom/ProfileSegment.h>
#include <CoordGeom/ProfileElement.h>
#include <CoordGeom/XCoordGeom.h>

using namespace WBFL::COGO;

class CompareProfileElements
{
public:
   CompareProfileElements(std::shared_ptr<const Alignment> alignment) :m_Alignment(alignment) { }
   bool operator()(const std::shared_ptr<ProfileElement>& pX, const std::shared_ptr<ProfileElement>& pY)
   {
      const auto& prev_element_end_point = pX->GetEndPoint();
      const auto& next_element_start_point = pY->GetStartPoint();
      return 0 < m_Alignment->CompareStations(prev_element_end_point.GetStation(), next_element_start_point.GetStation());
   }

private:
   std::shared_ptr<const Alignment> m_Alignment;
};

ProfileImpl::ProfileImpl()
{
}

ProfileImpl::ProfileImpl(const ProfileImpl& profileImpl)
{
   for (const auto& profile_element : profileImpl.m_Elements)
   {
      AddProfileElement(profile_element->Clone());
   }

   for (const auto& [id,surface] : m_Surfaces)
   {
      AddSurface(id,Surface::Create(*surface));
   }
}

void ProfileImpl::OnProfileChanged()
{
   // The profile was changed, clear out the cached data
   m_ProfileElements.clear();
}

void ProfileImpl::SetProfile(std::weak_ptr<Profile> profile)
{
   m_Profile = profile;
}

void ProfileImpl::SetAlignment(std::weak_ptr<const Alignment> alignment)
{
   m_Alignment = alignment;
}

std::shared_ptr<const Alignment> ProfileImpl::GetAlignment() const
{
   return m_Alignment.lock();
}

void ProfileImpl::AddSurface(IDType id,std::shared_ptr<const Surface> surface)
{
   m_Surfaces.emplace(id,surface);
}

std::shared_ptr<const Surface> ProfileImpl::GetSurface(IDType id) const
{
   auto found = m_Surfaces.find(id);
   return (found == m_Surfaces.end() ? nullptr : found->second);
}

const std::map<IDType, std::shared_ptr<const Surface>>& ProfileImpl::GetSurfaces() const
{
   return m_Surfaces;
}

void ProfileImpl::ClearSurfaces()
{
   m_Surfaces.clear();
}

void ProfileImpl::Clear()
{
   ClearProfileElements();
   ClearSurfaces();
}

std::pair<IDType, std::shared_ptr<const Surface>> ProfileImpl::GetSurfaceContainingStation(const Station& station) const
{
   for (const auto& surface_record : m_Surfaces)
   {
      if (surface_record.second->ContainsStation(station))
      {
         return surface_record;
      }
   }

   // surface not found
   return std::make_pair(INVALID_ID, nullptr);
}

void ProfileImpl::AddProfileElement(std::shared_ptr<ProfileElement> profileElement)
{
   m_Elements.emplace_back(profileElement);
   std::sort(std::begin(m_Elements), std::end(m_Elements), CompareProfileElements(GetAlignment()));
   OnProfileChanged();
}

std::shared_ptr<ProfileElement> ProfileImpl::GetProfileElement(IndexType idx)
{
   return m_Elements[idx];
}

std::shared_ptr<const ProfileElement> ProfileImpl::GetProfileElement(IndexType idx) const
{
   return m_Elements[idx];
}

IndexType ProfileImpl::GetProfileElementCount() const
{
   return m_Elements.size();
}

const std::vector<std::shared_ptr<ProfileElement>>& ProfileImpl::GetProfileElements() const
{
   return m_Elements;
}

void ProfileImpl::ClearProfileElements()
{
   m_Elements.clear();
   OnProfileChanged();
}

Float64 ProfileImpl::Elevation(const Station& station) const
{
   return Elevation(nullptr, station, 0.0);
}

Float64 ProfileImpl::Elevation(IDType surfaceID, const Station& station, Float64 offset) const
{
   return Elevation(GetSurface(surfaceID), station, offset);
}

Float64 ProfileImpl::Elevation(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset) const
{
   auto [grade,elevation,slope] = GradeAndElevation(surface, station, offset);
   return elevation;
}

Float64 ProfileImpl::Grade(const Station& station) const
{
   auto [grade, elevation, slope] = GradeAndElevation(nullptr, station, 0.0);
   return grade;
}

Float64 ProfileImpl::SurfaceTemplateSegmentSlope(IDType surfaceID, const Station& station, IndexType segmentIdx) const
{
   return SurfaceTemplateSegmentSlope(GetSurface(surfaceID), station, segmentIdx);
}

Float64 ProfileImpl::SurfaceTemplateSegmentSlope(std::shared_ptr<const Surface> surface, const Station& station, IndexType segmentIdx) const
{
   auto surface_template = surface->CreateSurfaceTemplateSectionCut(station, true);
   return surface_template->GetSegmentSlope(segmentIdx);
}

Float64 ProfileImpl::CrossSlope(IDType surfaceID, const Station& station, Float64 offset) const
{
   return CrossSlope(GetSurface(surfaceID), station, offset);
}

Float64 ProfileImpl::CrossSlope(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset) const
{
   auto [grade, elevation, slope] = GradeAndElevation(surface, station, offset);
   return slope;
}

Float64 ProfileImpl::GetRidgePointOffset(IDType surfaceID, const Station& station, IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   auto surface = GetSurface(surfaceID);
   if (surface == nullptr || surface->ContainsStation(station) == false) THROW_COGO(WBFL_COGO_E_INVALIDARG);

   auto surface_template = surface->CreateSurfaceTemplateSectionCut(station, true);
   return surface_template->GetRidgePointOffset(ridgePoint1Idx, ridgePoint2Idx);
}

Float64 ProfileImpl::GetRidgePointElevation(IDType surfaceID, const Station& station, IndexType ridgePointIdx) const
{
   auto surface = GetSurface(surfaceID);
   if (surface == nullptr || surface->ContainsStation(station) == false) THROW_COGO(WBFL_COGO_E_INVALIDARG);
   auto surface_template = surface->CreateSurfaceTemplateSectionCut(station, true);
   return surface_template->GetRidgePointElevation(ridgePointIdx);
}

std::pair<Float64, Float64> ProfileImpl::GetRidgePointOffsetAndElevation(IDType surfaceID, const Station& station, IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   auto surface = GetSurface(surfaceID);
   if (surface == nullptr || surface->ContainsStation(station) == false) THROW_COGO(WBFL_COGO_E_INVALIDARG);

   auto surface_template = surface->CreateSurfaceTemplateSectionCut(station, true);
   return surface_template->GetRidgePointOffsetAndElevation(ridgePoint1Idx, ridgePoint2Idx);
}

std::tuple<Float64, Float64, Float64> ProfileImpl::GradeAndElevation(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset) const
{
   Float64 grade, elevation, slope;
   if (m_Elements.size() == 0)
   {
      elevation = 0.0;
      std::tie(elevation,slope) = AdjustForOffset(surface, station, offset, elevation);
      grade = 0.0;
   }
   else
   {
      auto alignment = GetAlignment();
      if (0 < alignment->CompareStations(station, m_Elements.front()->GetStartPoint().GetStation()))
      {
         // Station is before the first station defined for the alignment
         std::tie(grade,elevation) = BeforeProfileGradeAndElevation(station);
         std::tie(elevation,slope) = AdjustForOffset(surface, station, offset, elevation);
      }
      else if(0 < alignment->CompareStations(m_Elements.back()->GetEndPoint().GetStation(), station))
      {
         // Station is after the last station defined for the alignment
         std::tie(grade,elevation) = AfterProfileGradeAndElevation(station);
         std::tie(elevation,slope) = AdjustForOffset(surface, station, offset, elevation);
      }
      else
      {
         // Station is somewhere in the middle of the alignment
         std::tie(grade,elevation) = ProfileGradeAndElevation(station);
         std::tie(elevation,slope) = AdjustForOffset(surface, station, offset, elevation);
      }
   }

   return std::make_tuple(grade, elevation, slope);
}

std::pair<Float64, Float64> ProfileImpl::BeforeProfileGradeAndElevation(const Station& station) const
{
   Float64 grade = 0;
   Float64 elevation = 0;
   if (!m_Elements.empty())
   {
      const auto& profile_element = m_Elements.front();
      std::tie(grade,elevation) = profile_element->ComputeGradeAndElevation(station);
   }
   return std::make_pair(grade, elevation);
}

std::pair<Float64,Float64> ProfileImpl::ProfileGradeAndElevation(const Station& station) const
{
   auto alignment = GetAlignment();
   auto ns = alignment->ConvertToNormalizedStation(station).GetValue();
   auto [element,distFromStart] = FindElement(ns);
   return element->ComputeGradeAndElevation(station);
}

std::pair<Float64, Float64> ProfileImpl::AfterProfileGradeAndElevation(const Station& station) const
{
   Float64 grade = 0;
   Float64 elevation = 0;
   if (!m_Elements.empty())
   {
      const auto& profile_element = m_Elements.back();
      std::tie(grade,elevation) = profile_element->ComputeGradeAndElevation(station);
   }
   return std::make_pair(grade, elevation);
}

std::pair<Float64, Float64> ProfileImpl::AdjustForOffset(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset, Float64 profileElevation) const
{
   Float64 slope = 0;
   Float64 adjElevation = profileElevation;

   if (surface == nullptr) return std::make_pair(adjElevation,slope);

   auto surface_template = GetProfile()->CreateSurfaceTemplateSectionCut(surface, station, false/*don't apply superelevation*/);

   auto alignmentPointIdx = surface->GetAlignmentPoint();
   auto profileGradePointIdx = surface->GetProfileGradePoint();

   Float64 elevation = 0.0;

   auto superelevation = surface->FindSuperelevation(station);
   if (superelevation)
   {
      // this station is in a superelevation transition!!!
      IndexType pivotPoint = superelevation->GetPivotPoint();

      // determine elevation at pivot point based on normal section
      Float64 delta = surface_template->GetRidgePointElevationChange(profileGradePointIdx, pivotPoint);

      Float64 pivotElevation = profileElevation + delta;

      // Create the superelevated section
      auto superelevated_surface_template = GetProfile()->CreateSurfaceTemplateSectionCut(surface, station, true /*apply superelevation*/);

      // determine elevation at alignment based on superelevation section
      delta = superelevated_surface_template->GetRidgePointElevationChange(pivotPoint, alignmentPointIdx);

      Float64 alignmentElev = pivotElevation + delta;

      // adjust elevation for offset from alignment
      delta = superelevated_surface_template->GetElevationChange(alignmentPointIdx, offset);
      elevation = alignmentElev + delta;

      // get the cross slope
      slope = superelevated_surface_template->GetSlope(alignmentPointIdx, offset);
   }
   else
   {
      // Determine elevation at Alignment = Profile Elevation + Change in elevation from profile point to alignment point
      Float64 delta = surface_template->GetRidgePointElevationChange(profileGradePointIdx, alignmentPointIdx);
      Float64 alignmentElev = profileElevation + delta;

      // Adjust elevation for offset from alignment
      delta = surface_template->GetElevationChange(alignmentPointIdx, offset);
      elevation = alignmentElev + delta;

      // get the cross slope
      slope = surface_template->GetSlope(alignmentPointIdx, offset);
   }

   adjElevation = elevation;

   return std::make_pair(adjElevation, slope);
}

const std::vector<ProfileImpl::Element>& ProfileImpl::GetConnectedProfileElements() const
{
   if (m_ProfileElements.size() == 0)
   {
      // container has been requested before... initialized
      if (m_Elements.size() == 0)
      {
         // There are no profile elements defined
      }
      else if (m_Elements.size() == 1)
      {
         // There is exactly one element defining the profile
         //
         // The first profile element is projected
         // to define the profile
         Float64 length = m_Elements.front()->GetLength();
         Float64 start_station = GetAlignment()->ConvertToNormalizedStation(m_Elements.front()->GetStartPoint().GetStation()).GetValue();
         m_ProfileElements.emplace_back(start_station, start_station + length, m_Elements.front());
      }
      else
      {
         // There are multiple profile elements
         Float64 start_station = GetAlignment()->ConvertToNormalizedStation(m_Elements.front()->GetStartPoint().GetStation()).GetValue();
         auto begin = m_Elements.begin();
         auto iter = begin;
         auto endIter = m_Elements.end();
         for (; iter != endIter; iter++)
         {
            const auto& element = *iter;
            auto length = element->GetLength();

            if (iter != begin)
            {
               // check if this element is connected to the previous element
               const auto& endPrev = m_ProfileElements.back().element->GetEndPoint();
               const auto& startNext = element->GetStartPoint();
               if (endPrev != startNext)
               {
                  // there is a gap between elements - fill it with a straight segment
                  CHECK(m_ProfileElements.back().element->GetProfile().get() == GetProfile().get());
                  auto profile = m_ProfileElements.back().element->GetProfile();
                  auto segment = ProfileSegment::Create(endPrev,startNext);
                  segment->SetProfile(profile); // need to associate the profile segment with this profile, just like as in AddProfileElement
                  auto segment_length = segment->GetLength();
                  if (0 < segment_length)
                  {
                     m_ProfileElements.emplace_back(start_station, start_station + segment_length, segment);
                     start_station += segment_length;
                  }
               }
            }

            m_ProfileElements.emplace_back(start_station, start_station + length, element);
            start_station += length;
         }
      }
   }

   return m_ProfileElements;
}

std::pair<std::shared_ptr<ProfileElement>,Float64> ProfileImpl::FindElement(Float64 normalizedStation) const
{
   Element testElement(normalizedStation, normalizedStation, nullptr);

   const auto& vElements = GetConnectedProfileElements();

   // NOTE: lower_bound performs a binary search
   auto lowerBound = std::lower_bound(vElements.begin(), vElements.end(), testElement, [](const auto& v1, const auto& v2) {return IsLE(v1.end_station, v2.start_station); });
   if (lowerBound == vElements.end())
   {
      if (IsLE(normalizedStation, vElements.front().start_station))
      {
         lowerBound = vElements.begin();
      }
      else if (IsLE(vElements.back().end_station, normalizedStation))
      {
         lowerBound = std::prev(vElements.end());
      }
      else
      {
         CHECK(vElements.size() == 1);
         lowerBound = vElements.begin();
      }
   }

   const auto& element(*lowerBound);
   return std::make_pair(element.element, element.start_station);
}
