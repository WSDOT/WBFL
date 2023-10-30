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
#include <CoordGeom/Path.h>
#include <CoordGeom/PathSegment.h>

#include <GeomModel/GeomOp2d.h>
#include <CoordGeom/COGO.h>

#include <xutility>

using namespace WBFL::COGO;

std::shared_ptr<Path> Path::Create()
{
   return std::shared_ptr<Path>(new Path());
}

std::shared_ptr<Path> Path::Create(const Path& path)
{
   return std::shared_ptr<Path>(new Path(path));
}

std::shared_ptr<Path> Path::Create(const std::vector<std::shared_ptr<PathElement>>& vElements)
{
   auto path = Path::Create();
   for (auto element : vElements)
   {
      path->AddPathElement(element);
   }
   return path;
}

Path::Path(const Path& other)
{
   for (const auto& pathElement : other.m_Elements)
   {
      m_Elements.emplace_back(pathElement->Clone());
   }
}

void Path::AddPathElement(std::shared_ptr<PathElement> pathElement)
{
   PRECONDITION(pathElement->GetPath() == nullptr);
   pathElement->SetPath(weak_from_this());
   m_Elements.emplace_back(pathElement);
   OnPathChanged();
}

void Path::InsertPathElement(IndexType idx, std::shared_ptr<PathElement> pathElement)
{
   PRECONDITION(pathElement->GetPath() == nullptr);
   pathElement->SetPath(weak_from_this());
   m_Elements.insert(m_Elements.begin() + idx, pathElement);
   OnPathChanged();
}

IndexType Path::GetPathElementCount() const
{
   return m_Elements.size();
}

std::shared_ptr<PathElement> Path::GetPathElement(IndexType idx)
{
   return m_Elements[idx];
}

std::shared_ptr<const PathElement> Path::GetPathElement(IndexType idx) const
{
   return m_Elements[idx];
}

std::vector<std::shared_ptr<PathElement>>& Path::GetPathElements()
{
   return m_Elements;
}

const std::vector<std::shared_ptr<PathElement>>& Path::GetPathElements() const
{
   return m_Elements;
}

void Path::Clear()
{
   // Path elements are shared_ptr objects. There could be other shared_ptr's to these path elements
   // Disassociate the path elements from this path
   std::for_each(m_Elements.begin(), m_Elements.end(), [](auto element){element->SetPath(std::shared_ptr<Path>(nullptr)); });
   m_Elements.clear();
   OnPathChanged();
}

std::pair<Float64, Float64> Path::DistanceAndOffset(const WBFL::Geometry::Point2d& point) const
{
   // Find where the point projects onto the path
   auto [prjPoint,distFromStart,bOnProjection] = ProjectPoint(point);

   // Get the bearing at the location where the point projects onto the path
   auto brg = GetBearing(distFromStart);

   // create a line tangent to the path, through the projection point in the forward direction
   WBFL::Geometry::Line2d line(prjPoint, WBFL::Geometry::Vector2d(1.0, brg));

   // Get the shortest distance from the input point to the line.
   // ShortestOffsetToPoint takes care of sign of offset based on point being on the left or right of the line
   Float64 offset = WBFL::Geometry::GeometricOperations::ShortestOffsetToPoint(line, point);

   return std::make_pair(distFromStart, offset);
}


std::vector<WBFL::Geometry::Point2d> Path::Divide(IndexType nParts) const
{
   return Divide(0.0, -1.0, nParts);
}

std::vector<WBFL::Geometry::Point2d> Path::Divide(Float64 start, Float64 end, IndexType nParts) const
{
   PRECONDITION(0 < nParts);
   PRECONDITION(0 <= start);
   PRECONDITION(0 <= end ? start <= end : true);

   std::vector<WBFL::Geometry::Point2d> points;
   if (end < 0) end = GetLength();
   auto length_to_divide = end - start;
   auto step = length_to_divide / nParts;

   auto nPoints = nParts + 1;
   for (IndexType i = 0; i < nPoints; i++)
   {
      Float64 dist_from_start = start + i * step;
      points.push_back(PointOnCurve(dist_from_start));
   }

   return points;
}

std::pair<bool,WBFL::Geometry::Point2d> Path::Intersect(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Point2d& nearest, bool bProjectBack, bool bProjectAhead) const
{
   std::vector<WBFL::Geometry::Point2d> vPoints;

   const auto& vElements = GetConnectedPathElements();
   auto begin = vElements.begin();
   auto iter = begin;
   auto end = vElements.end();
   for (; iter != end; iter++)
   {
      const auto& path_element(*iter);
      bool bProjectBackThisElement = (bProjectBack == false ? false : (iter == begin ? true : false));
      bool bProjectAheadThisElement = (bProjectAhead == false ? false : (iter == std::prev(end) ? true : false));

      auto points = path_element.element->Intersect(line, bProjectBackThisElement, bProjectAheadThisElement);
      vPoints.insert(vPoints.end(), points.begin(), points.end());
   }

   std::pair<bool, WBFL::Geometry::Point2d> result{ false,WBFL::Geometry::Point2d() };
   if (!vPoints.empty())
   {
      Float64 shortest_distance = Float64_Max;
      WBFL::Geometry::Point2d nearest_point;
      for (auto& point : vPoints)
      {
         auto distance = point.Distance(nearest);
         if (distance < shortest_distance)
         {
            shortest_distance = distance;
            nearest_point = point;
         }
      }
      result.first = true;
      result.second = nearest_point;
   }

   return result;
}

//
// PathElement methods
//
std::shared_ptr<PathElement> Path::Clone() const
{
   return Path::Create(*this);
}

const WBFL::Geometry::Point2d& Path::GetStartPoint() const
{
   const auto& vElements = GetConnectedPathElements();
   return vElements.front().element->GetStartPoint();
}

const WBFL::Geometry::Point2d& Path::GetEndPoint() const
{
   const auto& vElements = GetConnectedPathElements();
   return vElements.back().element->GetEndPoint();
}

WBFL::Geometry::Point2d Path::PointOnCurve(Float64 distFromStart) const
{
   return LocatePoint(distFromStart, OffsetType::Normal, 0.00, 0.00);
}

void Path::Move(Float64 distance, const Direction& direction)
{
   auto dx = distance * cos(direction);
   auto dy = distance * sin(direction);

   dx = ::IsZero(dx) ? 0 : dx;
   dy = ::IsZero(dy) ? 0 : dy;

   for (auto& element : m_Elements)
   {
      element->Move(distance, direction);
   }
   OnPathElementChanged();
}

void Path::Offset(Float64 dx, Float64 dy)
{
   for (auto& element : m_Elements)
   {
      element->Offset(dx, dy);
   }
   OnPathElementChanged();
}

Float64 Path::GetLength() const
{
   const auto& vElements = GetConnectedPathElements(); // not used, but it computes m_PathLength
   return m_PathLength;
}

std::vector<WBFL::Geometry::Point2d> Path::GetKeyPoints() const
{
   std::vector<WBFL::Geometry::Point2d> vPoints;
   const auto& vElements = GetConnectedPathElements();
   for (const auto& element : vElements)
   {
      auto key_points = element.element->GetKeyPoints();
      vPoints.insert(vPoints.end(), key_points.begin(), key_points.end());
   }
   return vPoints;
}

WBFL::Geometry::Point2d Path::LocatePoint(Float64 distFromStart, OffsetType offsetType, Float64 offset, const Direction& dir) const
{
   auto [element,beginDist] = FindElement(distFromStart);
   Float64 dist_from_start_of_element = distFromStart - beginDist;
   return element->LocatePoint(dist_from_start_of_element, offsetType, offset, dir);
}

Direction Path::GetBearing(Float64 distFromStart) const
{
   auto [element, beginDist] = FindElement(distFromStart);
   Float64 dist_from_start_of_element = distFromStart - beginDist;
   return element->GetBearing(dist_from_start_of_element);
}

std::tuple<WBFL::Geometry::Point2d, Float64, bool> Path::ProjectPoint(const WBFL::Geometry::Point2d& point) const
{
   Float64 shortestDistance = Float64_Max;
   WBFL::Geometry::Point2d the_point;
   Float64 the_distance;
   bool the_projection;

   const auto& vElements = GetConnectedPathElements();

   auto nElements = vElements.size();
   auto first = vElements.begin();
   auto iter = first;
   auto end = vElements.end();
   auto last = end - 1;
   for (; iter != end; iter++)
   {
      auto path_element(*iter);

      WBFL::Geometry::Point2d prjPoint;
      Float64 dist_from_start_of_element;
      bool bOnProjection;
      try
      {
         std::tie(prjPoint, dist_from_start_of_element, bOnProjection) = path_element.element->ProjectPoint(point);
      }
      catch (...)
      {
      }

      bool bValidProjection = true;
      if (
         (iter != first && iter != last && bOnProjection == true) // don't consider projections on internal elements
         ||
         (iter == first && bOnProjection == true && 0 < dist_from_start_of_element && 1 < nElements) // don't consider projections after the end of the first element if there are more than 1 elements
         ||
         (iter == last && bOnProjection == true && dist_from_start_of_element < 0 && 1 < nElements) // don't consider projects before the start of the last element if there are more than 1 elements
         )
      {
         bValidProjection = false;
      }

      if (bValidProjection)
      {
         Float64 dist_from_element_to_point = point.Distance(prjPoint);
         if (dist_from_element_to_point < shortestDistance)
         {
            shortestDistance = dist_from_element_to_point;
            the_point = prjPoint;
            the_distance = path_element.start + dist_from_start_of_element;
            the_projection = bOnProjection;
         }
      }
   }

   return std::make_tuple(the_point, the_distance, the_projection);
}

std::vector<WBFL::Geometry::Point2d> Path::Intersect(const WBFL::Geometry::Line2d& line, bool bProjectBack, bool bProjectAhead) const
{
   std::vector<WBFL::Geometry::Point2d> vPoints;
   auto begin = m_Elements.begin();
   auto iter = begin;
   auto end = m_Elements.end();
   auto last = std::prev(end);
   for ( ; iter != end; iter++)
   {
      const auto& element(*iter);
      std::vector<WBFL::Geometry::Point2d> vPointsThisElement = element->Intersect(line, iter == begin ? bProjectBack : false, iter == last ? bProjectAhead : false);
      vPoints.insert(vPoints.end(), vPointsThisElement.begin(), vPointsThisElement.end());
   }
   return vPoints;
}

std::vector<std::shared_ptr<PathElement>> Path::CreateOffsetPath(Float64 offset) const
{
   if (IsZero(offset))
   {
      auto clone = this->Clone();
      auto clone_path = std::dynamic_pointer_cast<Path>(clone);
      return clone_path->m_Elements;
   }

   std::vector<std::shared_ptr<PathElement>> path_elements;
   const auto& vElements = GetConnectedPathElements();
   auto begin = vElements.begin();
   auto iter = begin;
   auto end = vElements.end();

   // start iterating over vElements until the first element whose offset path
   // doesn't degrade to nothing (curves will degrade to nothing when the offset is greater than the radius)
   while (path_elements.empty() && iter != end)
   {
      const auto& element = iter->element;
      auto e = element->CreateOffsetPath(offset);
      path_elements.insert(path_elements.end(), e.begin(), e.end());
      iter++;
   }

   // loop over all the remaining path elements, creating an offset element for each one, and
   // adjusting end points so the resulting offset path is continuous
   for (; iter != end; iter++)
   {
      const auto& element = iter->element;
      auto e = element->CreateOffsetPath(offset);

      if (!e.empty())
      {
         auto& prev_offset_element = path_elements.back();
         auto& next_offset_element = e.front();
         if (prev_offset_element->GetEndPoint() != next_offset_element->GetStartPoint())
         {
            // the offset path isn't continuous, adjust end points
            auto prev_offset_tangent = prev_offset_element->GetEndTangent();
            auto next_offset_tangent = next_offset_element->GetStartTangent();

            WBFL::Geometry::Point2d pi;
            auto result = WBFL::Geometry::GeometricOperations::Intersect(prev_offset_tangent, next_offset_tangent, &pi);
            CHECK(result == 1);

            // Assuming that the discontinuous elements are PathSegments
            auto prev_segment = std::dynamic_pointer_cast<PathSegment>(prev_offset_element);
            auto next_segment = std::dynamic_pointer_cast<PathSegment>(next_offset_element);
            CHECK(prev_segment);
            CHECK(next_segment);
            prev_segment->ThroughPoints(prev_segment->GetStartPoint(), pi);
            next_segment->ThroughPoints(pi, next_segment->GetEndPoint());
         }
      }

      path_elements.insert(path_elements.end(), e.begin(), e.end());
   }

   return path_elements;
}

std::vector<std::shared_ptr<PathElement>> Path::CreateSubpath(Float64 start, Float64 end) const
{
   std::vector<std::shared_ptr<PathElement>> subpath_elements;
   const auto& vElements = GetConnectedPathElements();
   for (const auto& path_element : vElements)
   {
      auto dist_to_subpath_start = start - path_element.start;
      auto dist_to_subpath_end = end - path_element.start;

      auto this_subpath_elements = path_element.element->CreateSubpath(dist_to_subpath_start, dist_to_subpath_end);

      for (auto& subpath_element : this_subpath_elements)
      {
         subpath_elements.emplace_back(subpath_element);
      }
   }

   // if none of the elements contribute to the sub-path, create a sub-path with
   // a point at the start and end of the sub-path range.
   auto pntStart = LocatePoint(start, OffsetType::Normal, 0.0, 0.0);
   if (subpath_elements.empty())
   {
      auto pntEnd = LocatePoint(end, OffsetType::Normal, 0.0, 0.0);
      subpath_elements.emplace_back(PathSegment::Create(pntStart, pntEnd));
   }
   else
   {
      // make straight element at start of path
      auto element = subpath_elements.front();
      auto pntEnd = element->GetStartPoint();
      auto segment = PathSegment::Create(pntStart, pntEnd);
      if(!IsZero(segment->GetLength()))
         subpath_elements.insert(subpath_elements.begin(),segment);

      // make straight segment at end of path
      element = subpath_elements.back();
      pntStart = element->GetEndPoint();
      pntEnd = LocatePoint(end, OffsetType::Normal, 0.0, 0.0);
      segment = PathSegment::Create(pntStart, pntEnd);
      if (!IsZero(segment->GetLength()))
         subpath_elements.emplace_back(segment);
   }

   return subpath_elements;
}



//
// Private helper methods
//
std::pair<std::shared_ptr<const PathElement>,Float64> Path::FindElement(Float64 distFromStart) const
{
   Element testElement(distFromStart, distFromStart, nullptr);

   const auto& vElements = GetConnectedPathElements();

   // NOTE: lower_bound performs a binary search
   auto lowerBound = std::lower_bound(vElements.begin(), vElements.end(), testElement, [](const auto& v1, const auto& v2) {return IsLE(v1.end, v2.start); });
   if (lowerBound == vElements.end())
   {
      if (IsLE(distFromStart, vElements.front().start))
      {
         lowerBound = vElements.begin();
      }
      else if (IsLE(vElements.back().end, distFromStart))
      {
         lowerBound = vElements.end() - 1;
      }
      else
      {
         CHECK(vElements.size() == 1);
         lowerBound = vElements.begin();
      }
   }

   const auto& element(*lowerBound);
   return std::make_pair(element.element, element.start);
}

const std::vector<Path::Element>& Path::GetConnectedPathElements() const
{
   if (m_ConnectedPathElements.empty())
   {
      // as we build up the path elements, we know the length of each element
      // we can compute the path length as we go instead of having to do it later
      m_PathLength = 0;

      if (m_Elements.size() == 0)
      {
         // There are no Path elements defined
         // The Path is a straight line, due east with the reference point at (0,0)
         // Create an Path element accordingly
         Float64 length = 100;
         auto segment(PathSegment::Create(0, 0, length, 0));
         m_ConnectedPathElements.emplace_back(0.0, length, segment);
         m_PathLength += length;
      }
      else if (m_Elements.size() == 1)
      {
         // There is exactly one element defining the Path
         Float64 length = m_Elements.front()->GetLength();
         m_ConnectedPathElements.emplace_back(0.0, length, m_Elements.front());
         m_PathLength += length;
      }
      else
      {
         // There are multiple Path elements
         Float64 start = 0.0;
         auto begin = m_Elements.begin();
         auto left_iter = begin;
         auto right_iter = std::next(left_iter);
         auto end = m_Elements.end();
         bool bLastElementStored = false;
         for (; right_iter != end; left_iter++, right_iter++)
         {
            const auto& left_element = *left_iter;
            const auto& right_element = *right_iter;

            if (left_element->GetEndPoint() != right_element->GetStartPoint())
            {
               // adjacent elements are not connected
               auto gap_direction = COGO::MeasureDirection(left_element->GetEndPoint(), right_element->GetStartPoint());
               auto left_segment = std::dynamic_pointer_cast<PathSegment>(left_element);
               auto right_segment = std::dynamic_pointer_cast<PathSegment>(right_element);

               if (gap_direction == left_element->GetBearing(left_element->GetLength()) && left_segment)
               {
                  // the gap element is in the same direction as the left element - extend the end of the left element instead of creating a new element
                  auto extended_left_segment = std::dynamic_pointer_cast<PathSegment>(left_segment->Clone());
                  extended_left_segment->ThroughPoints(extended_left_segment->GetStartPoint(), right_element->GetStartPoint());
                  auto length = extended_left_segment->GetLength();
                  m_ConnectedPathElements.emplace_back(start, start + length, extended_left_segment);
                  start += length;
                  m_PathLength += length;
               }
               else if (gap_direction == right_element->GetBearing(0.0) && right_segment)
               {
                  // the gap element is in the same direction as the right element - extend the start of the right element instead of creating a new element

                  // store the left segment
                  auto length = left_element->GetLength();
                  m_ConnectedPathElements.emplace_back(start, start + length, left_element);
                  start += length;
                  m_PathLength += length;

                  // adjust and store the right segment
                  auto extended_right_segment = std::dynamic_pointer_cast<PathSegment>(right_segment->Clone());
                  extended_right_segment->ThroughPoints(left_element->GetEndPoint(), extended_right_segment->GetEndPoint());
                  length = extended_right_segment->GetLength();
                  m_ConnectedPathElements.emplace_back(start, start + length, extended_right_segment);
                  start += length;
                  m_PathLength += length;

                  if (std::next(right_iter) == end)
                     bLastElementStored = true;
               }
               else
               {
                  // make a gap element

                  // store the left element
                  auto length = left_element->GetLength();
                  m_ConnectedPathElements.emplace_back(start, start + length, left_element);
                  start += length;
                  m_PathLength += length;

                  // create and store a gap element
                  auto gap_segment = PathSegment::Create(left_element->GetEndPoint(), right_element->GetStartPoint());
                  length = gap_segment->GetLength();
                  m_ConnectedPathElements.emplace_back(start, start + length, gap_segment);
                  m_PathLength += length;
                  start += length;
               }
            }
            else
            {
               auto length = left_element->GetLength();
               m_ConnectedPathElements.emplace_back(start, start + length, left_element);
               start += length;
               m_PathLength += length;
            }
         }

         if (!bLastElementStored)
         {
            const auto& last_element = m_Elements.back();
            auto length = last_element->GetLength();
            m_ConnectedPathElements.emplace_back(start, start + length, last_element);
            m_PathLength += length;
         }
      }
   }

   return m_ConnectedPathElements;
}

void Path::OnPathChanged()
{
   // the path was changed so clear out the cached data
   m_ConnectedPathElements.clear();
}
