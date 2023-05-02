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
   WBFL::Geometry::Point2d prjPoint;
   Float64 distFromStart;
   bool bOnProjection;
   std::tie(prjPoint,distFromStart,bOnProjection) = ProjectPoint(point);

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
   std::shared_ptr<const PathElement> element;
   Float64 beginDist;
   std::tie(element,beginDist) = FindElement(distFromStart);
   Float64 dist_from_start_of_element = distFromStart - beginDist;
   return element->LocatePoint(dist_from_start_of_element, offsetType, offset, dir);
}

Direction Path::GetBearing(Float64 distFromStart) const
{
   std::shared_ptr<const PathElement> element;
   Float64 beginDist;
   std::tie(element, beginDist) = FindElement(distFromStart);
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
   for (const auto& element : vElements)
   {
      auto e = element.element->CreateOffsetPath(offset);
      if (!e.empty())  path_elements.insert(path_elements.end(), e.begin(), e.end());
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
   if (subpath_elements.empty())
   {
      auto p1 = LocatePoint(start, OffsetType::Normal, 0.0, 0.0);
      auto p2 = LocatePoint(end, OffsetType::Normal, 0.0, 0.0);
      subpath_elements.emplace_back(PathSegment::Create(p1, p2));
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
   return std::make_pair(element.element, element.start);;
}

const std::vector<Path::Element>& Path::GetConnectedPathElements() const
{
   if (m_ConnectedPathElements.empty())
   {
      // as we build up the path elements, we know the length of each element
      // we can compute the path length as we go instead of having to do it later
      m_PathLength = 0;

      // container has been requested before... initialized
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
         //
         // The first Path element is projected
         // to define the Path
         Float64 length = m_Elements.front()->GetLength();
         m_ConnectedPathElements.emplace_back(0.0, length, m_Elements.front());
         m_PathLength += length;
      }
      else
      {
         // There are multiple Path elements
         Float64 start = 0.0;
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
               const auto& endPrev = m_ConnectedPathElements.back().element->GetEndPoint();
               const auto& startNext = element->GetStartPoint();
               if (endPrev != startNext)
               {
                  // there is a gap between elements - fill it with a straight segment
                  auto segment = PathSegment::Create(endPrev, startNext);
                  auto segment_length = segment->GetLength();
                  m_ConnectedPathElements.emplace_back(start, start + segment_length, segment);
                  m_PathLength += segment_length;
                  start += segment_length;
               }
            }

            m_ConnectedPathElements.emplace_back(start, start + length, element);
            m_PathLength += length;
            start += length;
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


#if defined _UNITTEST
bool Path::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Path");

   TESTME_EPILOG("Path");
}
#endif // _UNITTEST


