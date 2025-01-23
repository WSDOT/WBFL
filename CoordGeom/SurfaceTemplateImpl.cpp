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
#include "SurfaceTemplateImpl.h"
#include <CoordGeom/Surface.h>
#include <CoordGeom/Profile.h>
#include <numeric>

using namespace WBFL::COGO;

SurfaceTemplateImpl::SurfaceTemplateImpl(const Station& station) :
   m_Station(station)
{
}

void SurfaceTemplateImpl::SetSurface(std::weak_ptr<const Surface> surface)
{
   m_Surface = surface;
   m_SegmentTemplates.resize(m_Surface.lock()->GetSurfaceTemplateSegmentCount());
}

std::shared_ptr<const Surface> SurfaceTemplateImpl::GetSurface() const
{
   return m_Surface.lock();
}

const Station& SurfaceTemplateImpl::GetStation() const
{
   return m_Station;
}

std::tuple<Float64, Float64, SurfaceTemplateSegment::SlopeType> SurfaceTemplateImpl::GetSegmentParameters(IndexType segmentIdx)
{
   return m_SegmentTemplates[segmentIdx].GetParameters();
}

void SurfaceTemplateImpl::UpdateSegmentParameters(IndexType segmentIdx, Float64 width, Float64 slope, SurfaceTemplateSegment::SlopeType slopeType)
{
   m_SegmentTemplates[segmentIdx].SetParameters(width, slope, slopeType);
}

IndexType SurfaceTemplateImpl::GetCount() const
{
   return m_SegmentTemplates.size();
}

SurfaceTemplateSegment& SurfaceTemplateImpl::GetSegment(IndexType idx)
{
   return m_SegmentTemplates[idx];
}

const SurfaceTemplateSegment& SurfaceTemplateImpl::GetSegment(IndexType idx) const
{
   return m_SegmentTemplates[idx];
}

void SurfaceTemplateImpl::Clear()
{
   m_SegmentTemplates.clear();
}

Float64 SurfaceTemplateImpl::GetRidgePointElevationChange(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   // computes the change in elevation between two ridge points
   PRECONDITION(ridgePoint1Idx <= m_SegmentTemplates.size()); // there are one more ridge points than segments (that is why the evaluation is <= and not the usual < )
   PRECONDITION(ridgePoint2Idx <= m_SegmentTemplates.size());

   Float64 sign = ::BinarySign((int)ridgePoint2Idx - (int)ridgePoint1Idx);
   Float64 delta = 0;
   IndexType startIdx = min(ridgePoint1Idx, ridgePoint2Idx);
   IndexType endIdx = max(ridgePoint1Idx, ridgePoint2Idx);
   for (IndexType idx = startIdx; idx < endIdx; idx++)
   {
      auto [width,slope,slopeType] = m_SegmentTemplates[idx].GetParameters();
      delta += sign * width * slope;
   }

   return delta;
}

Float64 SurfaceTemplateImpl::GetElevationChange(IndexType ridgePointIdx, Float64 offset) const
{
   // Computes the change in elevation between a ridge point and an offset measured from the ridge point
   PRECONDITION(ridgePointIdx <= m_SegmentTemplates.size()); // there are one more ridge points than segments (that is why the evaluation is <= and not the usual < )

   Float64 sign = ::BinarySign(offset);

   Float64 delta = 0;
   if (0 <= offset)
   {
      // working left to right from the specified ridge point
      SegmentIndexType nSegments = m_SegmentTemplates.size();
      Float64 running_offset = 0;
      for (IndexType idx = ridgePointIdx; idx < nSegments; idx++)
      {
         auto [width,slope,slopeType] = m_SegmentTemplates[idx].GetParameters();

         if (offset < running_offset + width)
         {
            // the end of this segment is beyond the point we are looking for
            // get distance to the point
            width = offset - running_offset;
            delta += sign * width * slope;
            break; // don't go any further
         }

         delta += sign * width * slope;

         running_offset += width;
      }
   }
   else
   {
      // working right to left from the specified ridge point
      Float64 running_offset = 0;
      for (IndexType idx = ridgePointIdx - 1; idx != INVALID_INDEX; idx--)
      {
         auto [width,slope,slopeType] = m_SegmentTemplates[idx].GetParameters();

         if (running_offset - width < offset)
         {
            width = running_offset - offset;
            delta += sign * width * slope;
            break; // don't go any further
         }
         delta += sign * width * slope;
         running_offset -= width;
      }
   }

   return delta;
}

Float64 SurfaceTemplateImpl::GetSlope(IndexType ridgePointIdx, Float64 offset) const
{
   PRECONDITION(ridgePointIdx <= m_SegmentTemplates.size()); // there are one more ridge points than segments (that is why the evaluation is <= and not the usual < )

   // if the offset is beyond the surface boundary the slope is 0
   Float64 surface_slope = 0;
   if (0 <= offset)
   {
      // working left to right from the specified ridge point
      Float64 leftEdge = 0;
      SegmentIndexType nSegments = m_SegmentTemplates.size();
      for (IndexType idx = ridgePointIdx; idx < nSegments; idx++)
      {
         auto [width,slope,slopeType] = m_SegmentTemplates[idx].GetParameters();

         if (::InRange(leftEdge, offset, leftEdge + width))
         {
            if (slopeType == SurfaceTemplateSegment::SlopeType::FixedVertical)
            {
               surface_slope = (IsZero(slope, 0.00001) ? ::BinarySign(slope) * DBL_MAX : 1 / slope);
            }
            else
            {
               surface_slope = slope;
            }
            break; // we have the slope, break out of the loop
         }

         leftEdge += width;
      }
   }
   else
   {
      // working right to left from the specified ridge point
      Float64 rightEdge = 0;
      for (IndexType idx = ridgePointIdx - 1; idx != INVALID_INDEX; idx--)
      {
         auto [width,slope,slopeType] = m_SegmentTemplates[idx].GetParameters();

         if (::InRange(rightEdge - width, offset, rightEdge))
         {
            if (slopeType == SurfaceTemplateSegment::SlopeType::FixedVertical)
            {
               surface_slope = (IsZero(slope, 0.00001) ? ::BinarySign(slope) * DBL_MAX : 1 / slope);
            }
            else
            {
               surface_slope = slope;
            }

            break; // we have the slope, break out of the loop
         }

         rightEdge -= width;
      }
   }

   return surface_slope;
}

Float64 SurfaceTemplateImpl::GetSegmentSlope(IndexType idx) const
{
   auto [width,slope,slopeType] = m_SegmentTemplates[idx].GetParameters();

   Float64 segment_slope = slope;
   if (slopeType == SurfaceTemplateSegment::SlopeType::FixedVertical)
   {
      segment_slope = (IsZero(slope, 0.00001) ? ::BinarySign(slope) * Float64_Max : 1 / slope);
   }

   return segment_slope;
}

Float64 SurfaceTemplateImpl::GetRidgePointOffset(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   if (ridgePoint1Idx == ridgePoint2Idx)
   {
      return 0.0;
   }

   IndexType startSegmentIdx = Min(ridgePoint1Idx, ridgePoint2Idx);
   IndexType endSegmentIdx = Max(ridgePoint1Idx, ridgePoint2Idx);
   auto begin = m_SegmentTemplates.begin();
   auto end = begin;
   std::advance(begin, startSegmentIdx);
   std::advance(end, endSegmentIdx);
   Float64 offset = std::accumulate(begin, end, 0.0, [](auto total, const auto& segment) {return total += segment.GetWidth(); });

   // ridge point 2 is to the left of ridge point 1
   // so offset is to the left (negative value)
   if (ridgePoint2Idx < ridgePoint1Idx)
   {
      offset *= -1;
   }

   return offset;
}

Float64 SurfaceTemplateImpl::GetRidgePointElevation(IndexType ridgePointIdx) const
{
   auto surface = GetSurface();
   auto offset_from_alignment_to_ridge_point = GetRidgePointOffset(surface->GetAlignmentPoint(), ridgePointIdx);
   return surface->GetProfile()->Elevation(surface, m_Station, offset_from_alignment_to_ridge_point);
}

std::pair<Float64,Float64> SurfaceTemplateImpl::GetRidgePointOffsetAndElevation(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   // Gets the offset and elevation of the specified ridge point at the station provided. Offset is measured from the ridge point identified by ridgePoint2Idx
   auto offset_between_ridge_points = GetRidgePointOffset(ridgePoint1Idx, ridgePoint2Idx);
   auto elevation = GetRidgePointElevation(ridgePoint2Idx);
   return std::make_pair(offset_between_ridge_points, elevation);
}
