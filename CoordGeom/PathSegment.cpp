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
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/COGO.h>

#include <GeomModel/GeomOp2d.h>

using namespace WBFL::COGO;

std::shared_ptr<PathSegment> PathSegment::Create()
{
   return std::shared_ptr<PathSegment>(new PathSegment());
}

std::shared_ptr<PathSegment> PathSegment::Create(const PathSegment& segment)
{
   return std::shared_ptr<PathSegment>(new PathSegment(segment));
}

std::shared_ptr<PathSegment> PathSegment::Create(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end)
{
   return std::shared_ptr<PathSegment>(new PathSegment(start,end));
}

std::shared_ptr<PathSegment> PathSegment::Create(Float64 x1, Float64 y1, Float64 x2, Float64 y2)
{
   return std::shared_ptr<PathSegment>(new PathSegment(x1,y1,x2,y2));
}

std::shared_ptr<PathSegment> PathSegment::Create(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Size2d& relEnd)
{
   return std::shared_ptr<PathSegment>(new PathSegment(start,relEnd));
}

PathSegment::PathSegment(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end) :
   PathElement()
{
   m_Segment.ThroughPoints(start, end);
}

PathSegment::PathSegment(Float64 x1, Float64 y1, Float64 x2, Float64 y2) :
   PathElement()
{
   m_Segment = WBFL::Geometry::LineSegment2d(x1, y1, x2, y2);
}

PathSegment::PathSegment(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Size2d& relEnd) :
   PathElement()
{
   m_Segment = WBFL::Geometry::LineSegment2d(start, relEnd);
}

const WBFL::Geometry::Point2d& PathSegment::GetStartPoint() const
{
   return m_Segment.GetStartPoint();
}

const WBFL::Geometry::Point2d& PathSegment::GetEndPoint() const
{
   return m_Segment.GetEndPoint();
}

WBFL::Geometry::Point2d PathSegment::PointOnCurve(Float64 distFromStart) const
{
   return COGO::LocateByDistanceAndAngle(m_Segment.GetStartPoint(), m_Segment.GetEndPoint(), distFromStart, 0.0, 0.0);
}

void PathSegment::ThroughPoints(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end)
{
   m_Segment.ThroughPoints(start, end);
   CHECK(0 < m_Segment.Length());
   OnPathElementChanged();
}

void PathSegment::Offset(Float64 offset)
{
   m_Segment.Offset(offset);
   OnPathElementChanged();
}

std::shared_ptr<PathElement> PathSegment::Clone() const
{
   return std::shared_ptr<PathSegment>(new PathSegment(*this));
}

void PathSegment::Move(Float64 distance, const Direction& direction)
{
   WBFL::Geometry::Vector2d v(distance, direction);
   auto start = GetStartPoint();
   auto end = GetEndPoint();
   start.Offset(v.GetSize());
   end.Offset(v.GetSize());
   m_Segment.ThroughPoints(start, end);
   OnPathElementChanged();
}

void PathSegment::Offset(Float64 dx, Float64 dy)
{
   m_Segment.Offset(dx, dy);
   OnPathElementChanged();
}

Float64 PathSegment::GetLength() const
{
   return m_Segment.Length();
}

std::vector<WBFL::Geometry::Point2d> PathSegment::GetKeyPoints() const
{
   std::vector<WBFL::Geometry::Point2d> vPoints{ GetStartPoint(),GetEndPoint() };
   return vPoints;
}

WBFL::Geometry::Point2d PathSegment::LocatePoint(Float64 distFromStart, OffsetType offsetType, Float64 offset, const Direction& direction) const
{
   offset = PathElement::AdjustOffset(distFromStart, offsetType, offset, direction); // offset is now along direction

   auto line_direction = COGO::MeasureDirection(GetStartPoint(), GetEndPoint());
   auto point = COGO::LocateByDistanceAndDirection(GetStartPoint(), distFromStart, line_direction, 0.0);
   if (!IsZero(offset))
   {
      point = COGO::LocateByDistanceAndDirection(point, offset, direction, 0.0);
   }
   return point;
}

Direction PathSegment::GetBearing(Float64 distFromStart) const
{
   return COGO::MeasureDirection(GetStartPoint(), GetEndPoint());
}

std::tuple<WBFL::Geometry::Point2d, Float64, bool> PathSegment::ProjectPoint(const WBFL::Geometry::Point2d& point) const
{
   WBFL::Geometry::Point2d newPoint;
   Float64 distFromStart;
   bool bOnProjection;

   if (0 < GetLength())
   {
      WBFL::Geometry::Line2d line(GetStartPoint(), GetEndPoint());
      auto p = WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, point);

      const auto& start = GetStartPoint();
      const auto& end = GetEndPoint();
      
      if (p == start)
         p = start;
      else if (p == end)
         p = end;

      newPoint = p;

      distFromStart = start.Distance(p);

      bool bBeforeStart = COGO::IsPointBeforeStart(start,end, p);
      bool bAfterEnd = COGO::IsPointAfterEnd(start, end, p);
      if (bBeforeStart)
      {
         distFromStart *= -1; // negative because it is before start (but distance is always an absolute value)
         bOnProjection = true;
      }
      else if (bAfterEnd)
      {
         bOnProjection = true;
      }
      else
      {
         bOnProjection = false;
      }
   }
   else
   {
      // the only way we get here is if start and end are the same point
      // if that is the case, the point always projects to the start
      newPoint = GetStartPoint();
      distFromStart = 0.0;
      bOnProjection = false;
   }

   return std::make_tuple(newPoint, distFromStart, bOnProjection);
}

std::vector<WBFL::Geometry::Point2d> PathSegment::Intersect(const WBFL::Geometry::Line2d& line, bool bProjectBack, bool bProjectAhead) const
{
   std::vector<WBFL::Geometry::Point2d> vPoints;

   if (!bProjectBack && !bProjectAhead)
   {
      // not projecting this line segment
      // check if line intersections segments
      WBFL::Geometry::Point2d point;
      auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line, m_Segment, &point);
      if (0 < nIntersections)
      {
         CHECK(nIntersections == 1); // only expecting one
         vPoints.emplace_back(point);
      }
   }
   else
   {
      // line segment is to be projected
      // create a line from the line segment
      auto start = GetStartPoint();
      auto end = GetEndPoint();
      WBFL::Geometry::Line2d thisLine(start, end);

      // intersect lines
      WBFL::Geometry::Point2d point;
      auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line, thisLine, &point);
      if (0 < nIntersections)
      {
         bool bBeforeStart = COGO::IsPointBeforeStart(start, end, point);
         bool bAfterEnd = COGO::IsPointAfterEnd(start, end, point);
         if (start == point  || // point is at start of segment
            end == point || // point is at end of segment
            (bBeforeStart && bProjectBack) || // point is before start and projection on back tangent is permitted
            (bAfterEnd && bProjectAhead) || // point is after end and projection on ahead tangent is permitted
            (!bBeforeStart && !bAfterEnd)) // point is not before start and not after end, therefore it must be on the segment
         {
            vPoints.emplace_back(point);
         }
      }
   }

   return vPoints;
}

std::vector<std::shared_ptr<PathElement>> PathSegment::CreateOffsetPath(Float64 offset) const
{
   auto offset_segment = std::dynamic_pointer_cast<PathSegment>(Clone());
   offset_segment->m_Segment.Offset(offset);

   std::vector<std::shared_ptr<PathElement>> vElements;
   vElements.emplace_back(offset_segment);
   return vElements;
}

std::vector<std::shared_ptr<PathElement>> PathSegment::CreateSubpath(Float64 start, Float64 end) const
{
   std::vector<std::shared_ptr<PathElement>> vElements;

   auto length = GetLength();

   if (IsLE(end,0.0) || IsGE(length,start))
   {
      // sub-path ends before the start of this element or the sub-path begins after
      // the start of this element - there isn't a sub-path for this element
      //
      // do nothing
   }
   else if (IsLE(start, 0.0) && IsLE(length, end))
   {
      // the entire line segment is between the start and end
      vElements.emplace_back(Clone());
   }
   else
   {
      // only a fraction of the line segment is part of the sub-path
      const auto& startPoint = GetStartPoint();
      const auto& endPoint = GetEndPoint();

      Float64 xs, ys;
      std::tie(xs,ys) = startPoint.GetLocation();

      Float64 xe, ye;
      std::tie(xe,ye) = endPoint.GetLocation();

      auto subpath = PathSegment::Create();
      auto subpath_start_point = subpath->GetStartPoint();
      auto subpath_end_point = subpath->GetEndPoint();

      if (IsGT(0.0,start))
      {
         // start of sub-path is after the start of this segment
         // locate point where the sub-path starts
         subpath_start_point = COGO::LocatePointOnLine(startPoint, endPoint, start, 0.0);
      }
      else
      {
         // start of this segment is after the start of the sub-path
         subpath_start_point.Move(xs, ys);
      }

      if (IsGT(length,end))
      {
         // line segment ends before the sub-path
         subpath_end_point.Move(xe,ye);
      }
      else
      {
         // end of sub-path is before end of this segment
         // locate point where sub-path ends;
         subpath_end_point = COGO::LocatePointOnLine(startPoint, endPoint, end, 0.0);
      }

      subpath->ThroughPoints(subpath_start_point, subpath_end_point);
      vElements.emplace_back(subpath);
   }

   return vElements;
}
