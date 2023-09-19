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
#include <CoordGeom/CubicSpline.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/XCoordGeom.h>

#include <GeomModel/CoordinateXform2d.h>
#include <GeomModel/GeomOp2d.h>

#include <array>
#include <map>

using namespace WBFL::COGO;

std::shared_ptr<CubicSpline> CubicSpline::Create()
{
   return std::shared_ptr<CubicSpline>(new CubicSpline());
}

std::shared_ptr<CubicSpline> CubicSpline::Create(const CubicSpline& curve)
{
   return std::shared_ptr<CubicSpline>(new CubicSpline(curve));
}

void CubicSpline::AddPoints(const std::vector<WBFL::Geometry::Point2d>& vPoints)
{
   m_vPoints.insert(m_vPoints.end(), vPoints.begin(), vPoints.end());
   m_bUpdateSpline = true;
   OnPathElementChanged();

#if defined _DEBUG
   if (2 <= m_vPoints.size())
   {
      UpdateSpline();
   }
#endif // _DEBUG}
}

void CubicSpline::AddPoint(Float64 x, Float64 y)
{
   AddPoint(WBFL::Geometry::Point2d(x, y));
}

void CubicSpline::AddPoint(const WBFL::Geometry::Point2d& p)
{
   m_vPoints.emplace_back(p);

   m_bUpdateSpline = true;
   OnPathElementChanged();

#if defined _DEBUG
   if (2 <= m_vPoints.size())
   {
      UpdateSpline();
   }
#endif // _DEBUG}
}


IndexType CubicSpline::GetPointCount() const
{
   return m_vPoints.size();
}

const WBFL::Geometry::Point2d& CubicSpline::GetPoint(IndexType idx) const
{
   if (m_vPoints.size() <= idx) THROW_COGO(WBFL_COGO_E_INVALIDINDEX);
   return m_vPoints[idx];
}

const std::vector<WBFL::Geometry::Point2d>& CubicSpline::GetPoints() const
{
   return m_vPoints;
}

const WBFL::Geometry::Point2d& CubicSpline::GetStartPoint() const
{
   CheckValid();
   return m_vPoints.front();
}

const WBFL::Geometry::Point2d& CubicSpline::GetEndPoint() const
{
   CheckValid();
   return m_vPoints.back();
}

void CubicSpline::Clear()
{
   m_vPoints.clear();
}

void CubicSpline::SetStartDirection(const Direction& direction)
{
   m_StartDirection = direction;

   m_bUpdateSpline = true;
   OnPathElementChanged();

#if defined _DEBUG
   if (2 <= m_vPoints.size())
   {
      UpdateSpline();
   }
#endif // _DEBUG
}

const Direction& CubicSpline::GetStartDirection() const
{
   return m_StartDirection;
}

void CubicSpline::SetEndDirection(const Direction& direction)
{
   m_EndDirection = direction;

   m_bUpdateSpline = true;
   OnPathElementChanged();

#if defined _DEBUG
   if (2 <= m_vPoints.size())
   {
      UpdateSpline();
   }
#endif // _DEBUG
}

const Direction& CubicSpline::GetEndDirection() const
{
   return m_EndDirection;
}

Direction CubicSpline::GetBearingAtPoint(IndexType idx) const
{
   if (m_vPoints.size() <= idx) THROW_COGO(WBFL_COGO_E_INVALIDINDEX);

   CheckValid();
   UpdateSpline();

   auto splineIdx = (idx == m_SplineSegments.size() ? idx - 1 : idx);
   const auto& splineSegment = m_SplineSegments[splineIdx];

   // get the slope at the start of the spline segment unless idx is the last point on the last segment
   Float64 x;
   if (idx == m_SplineSegments.size())
   {
      x = splineSegment.pntB.X();
   }
   else
   {
      x = splineSegment.pntA.X();
   }

   Float64 slope = splineSegment.Slope(x);

   Float64 direction = atan(slope);

   direction += m_RotationAngle;

   return direction;
}

Direction CubicSpline::GetNormalAtPoint(IndexType idx) const
{
   Direction bearing = GetBearingAtPoint(idx);
   bearing.Increment(-PI_OVER_2);
   return bearing;
}

WBFL::Geometry::Point2d CubicSpline::PointOnCurve(Float64 distFromStart) const
{
   WBFL::Geometry::Point2d point;

   CheckValid();
   UpdateSpline();

   auto length = GetLength();

   distFromStart = IsZero(distFromStart) ? 0 : distFromStart;
   distFromStart = IsEqual(distFromStart, length) ? length : distFromStart;

   auto [pSplineSegment, splineDist] = FindSplineSegment(distFromStart);

   if (pSplineSegment == nullptr) // before or after spline
   {
      if (splineDist < 0)
      {
         // before start
         const auto& pntStart = m_vPoints.front();

         auto [sx,sy] = pntStart.GetLocation();

         Float64 x = sx + splineDist * cos(m_StartDirection);
         Float64 y = sy + splineDist * sin(m_StartDirection);

         point.Move(x, y);
      }
      else
      {
         // after end
         const auto& pntEnd = m_vPoints.back();

         auto [ex,ey] = pntEnd.GetLocation();

         Float64 x = ex + splineDist * cos(m_EndDirection);
         Float64 y = ey + splineDist * sin(m_EndDirection);

         point.Move(x, y);
      }
   }
   else
   {
      auto [x,y] = pSplineSegment->GetPoint(splineDist);

      point.Move(x, y);

      m_CoordXform.Xform(point, WBFL::Geometry::CoordinateXform2d::Type::NewToOld);
   }

   return point;
}

Float64 CubicSpline::DistanceFromStartAtPoint(IndexType idx) const
{
   if (m_vPoints.size() <= idx) THROW_COGO(WBFL_COGO_E_INVALIDINDEX);

   if (idx == 0)
   {
      return 0;
   }

   if (idx == m_vPoints.size() - 1)
   {
      return GetLength();
   }

   // add up length of spline segments
   Float64 distance = 0;
   std::for_each(m_SplineSegments.cbegin(), m_SplineSegments.cbegin() + idx, [&distance](const auto& splineSegment) {distance += splineSegment.Length(); });
   return distance;
}

void CubicSpline::Offset(Float64 dx, Float64 dy)
{
   std::for_each(std::begin(m_vPoints), std::end(m_vPoints), [&dx, &dy](auto& point) {point.Offset(dx, dy); });
   m_bUpdateSpline = true;
   OnPathElementChanged();
}

//
// PathElement methods
// 
std::shared_ptr<PathElement> CubicSpline::Clone() const
{
   return std::shared_ptr<CubicSpline>(new CubicSpline(*this));
}

void CubicSpline::Move(Float64 distance,const Direction& direction)
{
   WBFL::Geometry::Vector2d v(distance, direction);
   for (auto& point : m_vPoints)
   {
      point.Offset(v.GetSize());
   }
   m_bUpdateSpline = true;
   OnPathElementChanged();
}

Float64 CubicSpline::GetLength() const
{
   CheckValid();
   UpdateSpline();
   Float64 L = 0;
   std::for_each(std::cbegin(m_SplineSegments), std::cend(m_SplineSegments), [&L](const auto& splineSegment) {L += splineSegment.Length(); });
   return L;
}

std::vector<WBFL::Geometry::Point2d> CubicSpline::GetKeyPoints() const
{
   return m_vPoints;
}

WBFL::Geometry::Point2d CubicSpline::LocatePoint(Float64 distFromStart, OffsetType offsetType, Float64 offset, const Direction& direction) const
{
   offset = PathElement::AdjustOffset(distFromStart, offsetType, offset, direction); // offset is now along direction
   auto point = PointOnCurve(distFromStart);
   if (!IsZero(offset))
   {

      point = COGO::LocateByDistanceAndDirection(point, offset, direction, 0.0);
   }

   return point;
}

Direction CubicSpline::GetBearing(Float64 distFromStart) const
{
   CheckValid();
   UpdateSpline();

   distFromStart = IsZero(distFromStart) ? 0 : distFromStart;
   if (distFromStart <= 0)
   {
      // before start
      return m_StartDirection;
   }

   Float64 length = GetLength();

   distFromStart = IsEqual(length, distFromStart) ? length : distFromStart;

   if (length <= distFromStart)
   {
      // after end
      return m_EndDirection;
   }

   // evaluate the slope... convert to a bearing
   auto point_on_curve = PointOnCurve(distFromStart);
   m_CoordXform.Xform(point_on_curve, WBFL::Geometry::CoordinateXform2d::Type::OldToNew);

   Float64 x = point_on_curve.X();

   Float64 slope = Slope(x, true, true);

   Float64 direction = atan(slope);

   return direction;
}

std::tuple<WBFL::Geometry::Point2d, Float64, bool> CubicSpline::ProjectPoint(const WBFL::Geometry::Point2d& point) const
{
   CheckValid();
   UpdateSpline();

   WBFL::Geometry::Point2d newPoint;
   Float64 distFromStart;
   bool bOnProjection;

   // First we have to determine if the point is before or after the spline
   // This is accomplished by setting up coordinate systems at the start and end
   // of the spline. The X axes are the line connecting the start and end points.

   WBFL::Geometry::CoordinateXform2d xfrm; // local coordinate transform

   // Setup the first coordinate system, with origin at p0
   const auto& p0 = GetStartPoint();
   const auto& pn = GetEndPoint();

   auto dir = COGO::MeasureDirection(p0, pn);

   xfrm.SetNewOrigin(p0);
   xfrm.SetRotationAngle(dir);

   WBFL::Geometry::Point2d xfrmPoint = xfrm.XformBy(point, WBFL::Geometry::CoordinateXform2d::Type::OldToNew);
   Float64 x1 = xfrmPoint.X(); // X ordinate in coordinate system 1
   x1 = IsZero(x1) ? 0.00 : x1;

   // Setup the second coordinate system, with origin at pn
   xfrm.SetNewOrigin(pn);
   xfrm.SetRotationAngle(dir + M_PI);
   xfrmPoint = xfrm.XformBy(point, WBFL::Geometry::CoordinateXform2d::Type::OldToNew);
   Float64 x2 = xfrmPoint.X();
   x2 = IsZero(x2) ? 0.00 : x2;

   if (x1 < 0 && x2 < 0)
   {
      // Point projects onto both the forward and back tangents
      // Find the point nearest the spline. If equal distance, take the
      // point on the forward tangent

      // Create a line object along the back tangent bearing. Locate the point on
      // that line that is nearest the input point
      WBFL::Geometry::Line2d line(p0, WBFL::Geometry::Vector2d(1.0, m_StartDirection));

      auto p1 = WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, point);

      // Create a line object along the forward tangent bearing. Locate the point on
      // that line that is nearest the input point
      line.SetExplicit(pn, WBFL::Geometry::Vector2d(1.0, m_EndDirection));

      auto p2 = WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, point);

      Float64 d1 = point.Distance(p1);
      Float64 d2 = point.Distance(p2);

      if (d1 < d2)
      {
         // Point projects onto the back tangent bearing (it is before the curve)
         newPoint = p1;
         distFromStart = p0.Distance(p1);
         (distFromStart) *= -1;
         CHECK(distFromStart <= 0); // must be negative because it is before the curve
      }
      else
      {
         // Point projects onto the forward tangent bearing (it is after the curve)
         newPoint = p2;
         distFromStart = pn.Distance(p2);
         auto Lt = GetLength();
         distFromStart += Lt;
         CHECK(0 <= distFromStart && Lt <= distFromStart);
      }

      bOnProjection = true;
   }
   else if (x1 <= 0)
   {
      // Point is before the curve
      // Create a line object along the back tangent bearing. Locate the point on
      // that line that is nearest the input point
      WBFL::Geometry::Line2d line(p0, WBFL::Geometry::Vector2d(1.0, m_StartDirection));

      newPoint = WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, point);
      distFromStart = p0.Distance(newPoint);
      distFromStart *= -1;

      CHECK(distFromStart <= 0); // must be negative because it is before the curve

      bOnProjection = true;
   }
   else if (0 < x1 && 0 < x2)
   {
      // point is between limits of spline

      // we have to work in the rotated coordinate system
      auto pntRotated = m_CoordXform.XformBy(point, WBFL::Geometry::CoordinateXform2d::Type::OldToNew);

      auto [px,py] = pntRotated.GetLocation();

      // NOTE: when comparing distance from the point to be projected onto the spline and the point on 
      // the spline where a normal vector passes through the point to be projected, the square of the 
      // distance will be evaluated. The actual distance between these points doesn't matter so we
      // can save some CPU cycles by not computing the square root.

      Float64 dist_from_start = 0;
      Float64 shortest_distance = Float64_Max;
      Float64 sx{ -99999 }, sy{ -99999 }; // coordinates of point on segment that produced the current "shortest distance"

      bool bFound = false;

      // for each spline, find a point on the spline that a normal vector passes through
      // and also passes through the target point.
      //
      // compute the distance between these two points
      //
      // the point associated with the shortest distance is the one we are after
      for (const auto& splineSegment : m_SplineSegments)
      {
         SplineSegmentProjectPointFunction fn(splineSegment, pntRotated);
         WBFL::Math::BisectionRootFinder rootfinder;

         // find the length along the spline segment where a normal line passes through
         // point
         Float64 s; // distance along segment
         try
         {
            s = rootfinder.FindRootInRange(fn, 0, splineSegment.Length(), 0.00001);
         }
         catch (...)
         {
            // a solution wasn't found... go to the next segment
            dist_from_start += splineSegment.Length();
            continue;
         }

         bFound = true;

         auto [x,y] = splineSegment.GetPoint(s);

         Float64 dist2 = (px - x) * (px - x) + (py - y) * (py - y); // square of the distance

         if (dist2 < shortest_distance)
         {
            shortest_distance = dist2;
            distFromStart = dist_from_start + s;
            sx = x;
            sy = y;
         }
      }

      if (bFound)
      {
         CHECK(sx != -99999 && sy != -99999);
         newPoint.Move(sx, sy);

         // convert back to original coordinate system
         m_CoordXform.Xform(newPoint, WBFL::Geometry::CoordinateXform2d::Type::NewToOld);

         bOnProjection = false;
      }
      else
      {
         THROW_COGO(WBFL_COGO_E_POINTPROJECTION);
      }
   }
   else if (x2 <= 0)
   {
      // Point is after the curve
      // Create a line object along the forward tangent bearing. Locate the point on
      // that line that is nearest the input point
      WBFL::Geometry::Line2d line(pn, WBFL::Geometry::Vector2d(1.0, m_EndDirection));

      newPoint = WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, point);

      distFromStart = pn.Distance(newPoint);
      auto Lt = GetLength();
      distFromStart += Lt;

      bOnProjection = true;

      CHECK(0 <= distFromStart && Lt <= distFromStart);
   }
   else
   {
      CHECK(false); // should never get here
   }

   return std::make_tuple(newPoint, distFromStart, bOnProjection);
}

std::vector<WBFL::Geometry::Point2d> CubicSpline::Intersect(const WBFL::Geometry::Line2d& line, bool bProjectBack, bool bProjectAhead) const
{
   CheckValid();
   UpdateSpline();

   std::vector<WBFL::Geometry::Point2d> vPoints;

   WBFL::Geometry::Point2d lastPoint; // last point stored

   if (bProjectBack)
   {
      // create a "back tangent" line
      const auto& pntStart = GetStartPoint();
      WBFL::Geometry::Line2d bkTangent(pntStart, WBFL::Geometry::Vector2d(1.0, m_StartDirection));

      // do a line-line intersect
      WBFL::Geometry::Point2d bkTangentPoint;
      auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line, bkTangent, &bkTangentPoint);
      // intersection point is in global coordinates

      if (nIntersections == 1)
      {
         // intersection must occur before the start of the spline

         // get the distance and direction from the start point to the back tangent point
         // distance is always positive and should be greater than zero.
         // if the directions are the same, the direction from the start of the spline
         // to the back tangent point, the intersection occurs within the spline and
         // that isn't what we are looking for
         auto [dist,dir] = COGO::ComputeInverse(pntStart, bkTangentPoint);

         if (m_StartDirection != dir)
         {
            // intersection is before the start of the spline so
            // we'll keep that point
            vPoints.emplace_back(bkTangentPoint);
            lastPoint = bkTangentPoint;
         }
      }
   }

   // intersect line with each spline segment. retain intersection points

   // the line is in the global coordinate system and the spline segments
   // are in the local spline coordinate system. create a line object
   // in the local coordinate system
   auto [pnt,v] = line.GetExplicit();
   m_CoordXform.Xform(pnt, WBFL::Geometry::CoordinateXform2d::Type::OldToNew);
   v.Rotate(-m_RotationAngle);
   WBFL::Geometry::Line2d line2(pnt, v);

   for (const auto& splineSegment : m_SplineSegments)
   {
      auto vIntersectPoints = splineSegment.Intersect(line2); // intersection points are in local spline coordinates
      for (auto& ip : vIntersectPoints)
      {
         // convert to global coordinates
         m_CoordXform.Xform(ip, WBFL::Geometry::CoordinateXform2d::Type::NewToOld);
         if (ip != lastPoint)
         {
            vPoints.emplace_back(ip);
            lastPoint = ip;
         }
      }
   }


   if (bProjectAhead)
   {
      // create an "ahead tangent" line
      const auto& endPoint = GetEndPoint();
      WBFL::Geometry::Line2d aheadTangent(endPoint, WBFL::Geometry::Vector2d(1.0, m_EndDirection));

      // do a line-line intersect
      WBFL::Geometry::Point2d aheadTangentPoint;
      auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line, aheadTangent, &aheadTangentPoint);

      if (0 < nIntersections)
      {
         // intersection must occur after the end of the spline

         // get the distance and direction from the end point to the ahead tangent point
         // distance is always positive and should be greater than zero.
         // if the directions are the same, the direction from the end of the spline
         // to the ahead tangent point, the intersection occurs after the spline and
         // that is what we are looking for
         auto [dist,dir] = COGO::ComputeInverse(endPoint, aheadTangentPoint);

         if (m_EndDirection == dir)
         {
            // intersection is after the end of the spline so
            // we'll keep that point
            if (aheadTangentPoint != lastPoint)
            {
               vPoints.emplace_back(aheadTangentPoint);
               lastPoint = aheadTangentPoint;
            }
         }
      }
   }

   return vPoints;
}

std::vector<std::shared_ptr<PathElement>> CubicSpline::CreateOffsetPath(Float64 offset) const
{
   IndexType pntIdx = 0;
   std::vector<WBFL::Geometry::Point2d> vOffsetPoints;
   for (const auto& point : m_vPoints)
   {
      auto direction = GetBearingAtPoint(pntIdx++);
      auto offset_point = COGO::LocateByDistanceAndDirection(point, 0.0, direction, offset);
      vOffsetPoints.emplace_back(offset_point);
   }

   auto offset_spline = CubicSpline::Create();
   offset_spline->AddPoints(vOffsetPoints);
   offset_spline->SetStartDirection(GetStartDirection());
   offset_spline->SetEndDirection(GetEndDirection());

   std::vector<std::shared_ptr<PathElement>> vElements{ offset_spline };
   return vElements;
}

std::vector<std::shared_ptr<PathElement>> CubicSpline::CreateSubpath(Float64 start, Float64 end) const
{
   std::vector<std::shared_ptr<PathElement>> vElements;

   auto length = GetLength();
   if (end < 0 || length < start)
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
      // only a fraction of the spline is part of the sub-path

      // get start point of sub-spline
      WBFL::Geometry::Point2d pntStart;
      Direction dirStart;
      if (start < 0)
      {
         // start of sub-path range is before start of spline
         // use the original spline start point
         pntStart = GetStartPoint();
         dirStart = GetStartDirection();
      }
      else
      {
         // start of the sub-path range is on the spline
         // use the point on spline at start as the start point of the sub spline
         pntStart = PointOnCurve(start);
         dirStart = GetBearing(start);
      }

      WBFL::Geometry::Point2d pntEnd;
      Direction dirEnd;
      if (length < end)
      {
         // end of sub-path range is after end of spline
         // use the original spline end point
         pntEnd = GetEndPoint();
         dirEnd = GetEndDirection();
      }
      else
      {
         // end of the sub-path range is on the spline
         // use the point on spline at end as the end point of the sub spline
         pntEnd = PointOnCurve(end);
         dirEnd = GetBearing(end);
      }

      // Start building up the sub-spline
      auto subpath_spline(CubicSpline::Create());

      // start with the start point and direction
      subpath_spline->AddPoint(pntStart);
      subpath_spline->SetStartDirection(dirStart);

      // distance from start of sub-path range to start of spline, or 0 if spline starts after sub-path range
      Float64 start_distance = Max(0., start);

      // distance from start of sub-path range to the end of spline, or the length of spline if the sub-path ends after the spline
      Float64 end_distance = Min(end, length);


      // use the actual spline points that are in the sub-path range
      // keep track of the number of points added to the sub-spline between the start and end points

      std::map<Float64, IndexType> vPoints; // use a map so the points are automatically sorted

      // all the points between the start and end
      // add those points to the sub-spline that are between the start and end
      auto begin = m_vPoints.begin();
      auto iter = std::next(begin);
      auto end_iter = std::prev(m_vPoints.end());
      for( ; iter != end_iter; iter++)
      {
         auto i = std::distance(begin, iter);
         auto distFromStartOfSpline = DistanceFromStartAtPoint(i);

         if (start < distFromStartOfSpline && distFromStartOfSpline < end)
         {
            // this point falls within the sub-path range... use it in the sub-spline
            vPoints.insert(std::make_pair(distFromStartOfSpline, i));
         }
      }

      // generate 10 more points to "fill in the blanks" between the other points
      IndexType nIntermediatePoints = 10;
      for (IndexType i = 1; i < nIntermediatePoints; i++)
      {
         Float64 distFromStart = start_distance + i * (end_distance - start_distance) / nIntermediatePoints;
         vPoints.insert(std::make_pair(distFromStart, INVALID_INDEX)); // if this fails, there is already a point at distFromStart so that's ok
      }


      for (const auto& [distFromStart,index] : vPoints)
      {
         // start and end points are handled elsewhere... make sure we aren't duplicating them
         CHECK(!IsEqual(distFromStart, start));
         CHECK(!IsEqual(distFromStart, end));

         WBFL::Geometry::Point2d p;
         if (index == INVALID_INDEX)
         {
            p = PointOnCurve(distFromStart);
         }
         else
         {
            p = GetPoint(index);
         }
         subpath_spline->AddPoint(p);
      }

      // finish it out with the end point and direction
      subpath_spline->AddPoint(pntEnd);
      subpath_spline->SetEndDirection(dirEnd);

      vElements.emplace_back(subpath_spline);
   }

   return vElements;
}

//
// Private methods
//

Float64 CubicSpline::Slope(Float64 distFromStart, bool bProjectBack, bool bProjectAhead) const
{
   auto p = PointOnCurve(distFromStart);

   // transform point to spline coordinates
   m_CoordXform.Xform(p, WBFL::Geometry::CoordinateXform2d::Type::OldToNew);

   Float64 xs = p.X(); // x in spline coordinates

   // quick check to see if we even need to worry about evaluating the spline
   auto xStart = m_SplineSegments.front().pntA.X();
   auto xEnd = m_SplineSegments.back().pntB.X();

   if ((xs < xStart && !bProjectBack) || (xEnd < xs && !bProjectAhead))
   {
      THROW_COGO(WBFL_COGO_E_INVALIDARG); // Distance from start must be between start and end of the spline
   }

   // check if x is before the start of the spline
   if (xs < xStart && bProjectBack)
   {
      auto slope = tan(m_StartDirection - m_RotationAngle);
      return slope;
   }

   // check if x is after the end of the spline
   if (xEnd < xs && bProjectAhead)
   {
      auto slope = tan(m_EndDirection - m_RotationAngle);
      return slope;
   }

   // find the spline that contains x
   for (const auto& splineSegment : m_SplineSegments)
   {
      auto xa = splineSegment.pntA.X();
      auto xb = splineSegment.pntB.X();

      if (InRange(xa, xs, xb))
      {
         Float64 slope = splineSegment.Slope(xs);
         slope += tan(m_RotationAngle);
         return slope;
      }
   }

   CHECK(false); // should never get here
   return -9999999;
}

void CubicSpline::CreateSplineSegments() const
{
   m_SplineSegments.clear();

   // determine the orientation of a coordinate system with it's origin
   // at the first point and its positive X axis passing through the last point
   const auto& p0 = GetStartPoint(); // point 0
   const auto& pn = GetEndPoint(); // point "n"

   auto [distance,direction] = COGO::ComputeInverse(p0, pn);

   m_RotationAngle = direction.GetValue();

   // later on, we will need to compute the slope of the start and end tangent using the tan function
   // if the start or end angles are PI/2 or 3PI/2, tan is infinity and we've got problems
   // rotate the "local" coordinate system to avoid this problem
   Angle start_angle(m_StartDirection.GetValue() - m_RotationAngle.GetValue());
   start_angle.Normalize();

   Angle end_angle(m_EndDirection.GetValue() - m_RotationAngle.GetValue());
   end_angle.Normalize();
   while ((IsEqual(start_angle.GetValue(), PI_OVER_2) || IsEqual(start_angle.GetValue(), 3 * PI_OVER_2)) ||
      (IsEqual(end_angle.GetValue(), PI_OVER_2) || IsEqual(end_angle.GetValue(), 3 * PI_OVER_2)))
   {
      m_RotationAngle.Increment(M_PI * 10. / 180.);  // 10 degree "tweak" of the rotation angle
      start_angle.SetValue(m_StartDirection.GetValue() - m_RotationAngle.GetValue());
      start_angle.Normalize();

      end_angle.SetValue(m_EndDirection.GetValue() - m_RotationAngle.GetValue());
      end_angle.Normalize();
   }

   m_CoordXform.SetNewOrigin(p0);
   m_CoordXform.SetRotationAngle(m_RotationAngle);

   // transform the points into the new coordinate system
   // and same in a spline segment object
   auto iter1 = m_vPoints.begin();
   auto iter2 = std::next(iter1);
   auto end = m_vPoints.end();
   for( ; iter2 != end; iter1++,iter2++)
   {
      const auto& pi = *iter1;
      const auto& pi1 = *iter2;

      auto pntA = m_CoordXform.XformBy(pi, WBFL::Geometry::CoordinateXform2d::Type::OldToNew);
      auto pntB = m_CoordXform.XformBy(pi1, WBFL::Geometry::CoordinateXform2d::Type::OldToNew);

      // pntB.X() must be after pntA.X()
      if (pntB.X() <= pntA.X())
      {
         CHECK(false); // did you mean for this to happen?
         THROW_COGO(WBFL_COGO_E_CUBICSPLINEPOINTS);
      }

      m_SplineSegments.emplace_back(pntA,pntB);
   }

#if defined _DEBUG
   IndexType nSegments = m_SplineSegments.size();
   for (IndexType segIdx = 0; segIdx < nSegments - 1; segIdx++)
   {
      // check that the end of the previous segment is equal to the start of th next segment
      CHECK(m_SplineSegments[segIdx].pntB == m_SplineSegments[segIdx + 1].pntA);
   }
#endif
}

void CubicSpline::UpdateSpline() const
{
   // See http://sites.science.oregonstate.edu/~restrepo/475A/Notes/sourcea.pdf (See page 143)
   // https://en.wikipedia.org/wiki/Spline_(mathematics)

   if (!m_bUpdateSpline)
   {
      return;
   }

   CreateSplineSegments();

   auto nSegments = m_SplineSegments.size();
   auto nPoints = nSegments + 1;

   // spline coefficients y = a + bx + cx^2 + dx^3
   std::vector<Float64> an(nPoints);
   std::vector<Float64> bn(nSegments);
   std::vector<Float64> cn(nPoints);
   std::vector<Float64> dn(nSegments);
   std::vector<Float64> hi(nSegments);

   // set an[i] = f(xi)
   // hi = x(i+1) - x(i)
   IndexType i = 0;
   for (const auto& splineSegment : m_SplineSegments)
   {
      an[i] = splineSegment.pntA.Y();

      auto xi = splineSegment.pntA.X();
      auto xi1 = splineSegment.pntB.X();

      Float64 h = xi1 - xi;
      hi[i] = h;

      i++;
   }
   CHECK(i == nPoints - 1);

   // get the last point
   an[nPoints - 1] = m_SplineSegments.back().pntB.Y();

   // get start and end slope WRT rotated coordinate system
   Angle start_angle(m_StartDirection.GetValue() - m_RotationAngle.GetValue());
   start_angle.Normalize();
   CHECK(!IsEqual(start_angle.GetValue(), PI_OVER_2) && !IsEqual(start_angle.GetValue(), 3 * PI_OVER_2));
   Float64 start_slope = tan(start_angle);

   Angle end_angle(m_EndDirection.GetValue() - m_RotationAngle.GetValue());
   end_angle.Normalize();
   CHECK(!IsEqual(end_angle.GetValue(), PI_OVER_2) && !IsEqual(end_angle.GetValue(), 3 * PI_OVER_2));
   Float64 end_slope = tan(end_angle);

   std::vector<Float64> alpha(nPoints);
   // set alpha0 = 3(a1-a0)/hi0 - 3*f'(x0)
   alpha[0] = 3 * (an[1] - an[0]) / hi[0] - 3 * start_slope;

   // set alphai=(3/hi)*[a(i+1)-ai]-[3/h(i-1)]*[ai-a(i-1)]     for i=1,2,3,...,n-1
   for (i = 1; i < nPoints - 1; i++)
   {
      alpha[i] = (3 / hi[i]) * (an[(i + 1)] - an[i]) - (3 / hi[(i - 1)]) * (an[i] - an[(i - 1)]);
   }

   // set alphan = 3*f'(xn)-3{an-an(n-1)}/hi(n-1)
   alpha[nPoints - 1] = (3 * end_slope) - 3 * (an[(nPoints - 1)] - an[(nPoints - 2)]) / hi[(nPoints - 2)];

   std::vector<Float64> li(nPoints);
   std::vector<Float64> ui(nPoints);
   std::vector<Float64> zi(nPoints);
   // set li0=2hi0
   //     ui0=0.5
   //     zi0=ai0/li0
   li[0] = (2 * hi[0]);
   ui[0] = 0.5;
   zi[0] = (alpha[0] / li[0]);

   // for i=1,2,3,...,n-1 ,set
   //    li=[2*{x(i+1)-x(i-1)}]-[h(i-1)*u(i-1)]
   //    ui=hi/li
   //    zi=[ai-{h(i-1)*z(i-1)}]/li
   for (i = 1; i < nSegments; i++)
   {
      auto& splineSegment1 = m_SplineSegments[i - 1];  // x(i-1) = pntA, x(i) = pntB
      auto& splineSegment2 = m_SplineSegments[i];    // x(i) = pntA, x(i+1) = pntB

      auto prevX = splineSegment1.pntA.X(); // x(i-1);
      auto nextX = splineSegment2.pntB.X(); // x(i+1)

      li[i] = ((2 * (nextX - prevX)) - (hi[i - 1] * ui[i - 1]));
      ui[i] = (hi[i] / li[i]);
      zi[i] = ((alpha[i] - (hi[i - 1] * zi[i - 1])) / li[i]);
   }

   // set lin=h(n-1){2-ui(n-1)}
   //     zin={ain-hi(n-1)zi(n-1)}/lin
   //     cn=zin
   li[(nPoints - 1)] = (hi[(nSegments - 1)] * (2 - ui[(nSegments - 1)]));
   zi[(nPoints - 1)] = ((alpha[(nPoints - 1)] - (hi[(nSegments - 1)] * zi[(nPoints - 2)])) / li[(nPoints - 1)]);
   cn[(nPoints - 1)] = zi[(nPoints - 1)];

   // for i=n-1,n-2,...,0   , set
   //     ci=zi-[ui*c(i+1)]
   //     bi=[a(i+1)-ai]/hi-{hi*{c(i+1)+[2*ci]}/3
   //     di=[c(i+1)-ci]/[3*hi]
   for (i = nPoints - 1; i >= 1; i--)
   {
      cn[i - 1] = (zi[i - 1] - (ui[i - 1] * cn[(i)]));
      bn[i - 1] = (((an[i] - an[i - 1]) / hi[i - 1]) - ((hi[i - 1] * (cn[i] + (2 * cn[i - 1]))) / 3));
      dn[i - 1] = ((cn[i] - cn[i - 1]) / (3 * hi[i - 1]));
   }

   i = 0;
   for (auto& splineSegment : m_SplineSegments)
   {
      splineSegment.Init(an[i], bn[i], cn[i], dn[i]);
      i++;
   }
   CHECK(i == nPoints - 1);
   m_bUpdateSpline = false;

#if defined _DEBUG
   ValidateSpline();
#endif
}

std::pair<CubicSpline::SplineSegment*,Float64> CubicSpline::FindSplineSegment(Float64 distFromStart) const
{
   if (distFromStart < 0)
   {
      return std::make_pair(nullptr,distFromStart);
   }

   Float64 start_distance = 0;
   for (auto& splineSegment : m_SplineSegments)
   {
      Float64 S = splineSegment.Length();

      if (start_distance <= distFromStart && distFromStart < start_distance + S)
      {
         return std::make_pair(&splineSegment, distFromStart - start_distance);
      }

      start_distance += S;
   }

   // beyond end
   return std::make_pair(nullptr, distFromStart - start_distance);
}

void CubicSpline::CheckValid() const
{
   if (m_vPoints.size() < 2)
   {
      THROW_COGO(WBFL_COGO_E_CUBICSPLINEPOINTS);
   }
}

#if defined _DEBUG
void CubicSpline::ValidateSpline() const
{
   // using the points defined by the user, compute points on the spline
   // the result should be the same point
   for(const auto& pnt : m_vPoints)
   {
      auto pnt2 = m_CoordXform.XformBy(pnt, WBFL::Geometry::CoordinateXform2d::Type::OldToNew);
      Float64 X = pnt2.X();

      for (const auto& splineSegment : m_SplineSegments)
      {
         auto Xa = splineSegment.pntA.X();
         auto Xb = splineSegment.pntB.X();
         if (InRange(Xa, X, Xb))
         {
            Float64 Y = splineSegment.Evaluate(X);
            pnt2.Move(X, Y);

            auto pnt3 = m_CoordXform.XformBy(pnt2, WBFL::Geometry::CoordinateXform2d::Type::NewToOld);
            CHECK(pnt == pnt3);
         }
      }

      // project a point on the spline onto the spline will result in the same point
      auto [pnt4,dist_from_start,bOnProjection] = ProjectPoint(pnt);
      CHECK(pnt ==  pnt4);
   }

   // make sure location and slope at comment segment boundaries are the same
   IndexType nSegments = m_SplineSegments.size();
   for (IndexType idx = 0; idx < nSegments - 1; idx++)
   {
      auto Xb = m_SplineSegments[idx].pntB.X();
      auto Xa = m_SplineSegments[idx + 1].pntA.X();
      CHECK(IsEqual(Xa, Xb));
      CHECK(m_SplineSegments[idx].pntB == m_SplineSegments[idx + 1].pntA);
      Float64 slope1 = m_SplineSegments[idx].Slope(Xb);
      Float64 slope2 = m_SplineSegments[idx + 1].Slope(Xa);
      CHECK(IsEqual(slope1, slope2));
   }
}
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////

CubicSpline::SplineSegment::SplineSegment()
{
}

CubicSpline::SplineSegment::SplineSegment(const WBFL::Geometry::Point2d& pntA, const WBFL::Geometry::Point2d& pntB) : pntA(pntA), pntB(pntB)
{
}

void CubicSpline::SplineSegment::Init(Float64 a, Float64 b, Float64 c, Float64 d)
{
   A = a;
   B = b;
   C = c;
   D = d;
   m_bComputeLength = true;
}

Float64 CubicSpline::SplineSegment::Length() const
{
   if (m_bComputeLength)
   {
      auto xb = pntB.X();
      auto xa = pntA.X();

      Float64 dx = xb - xa;
      m_Length = Length(dx);
      m_bComputeLength = false;
   }

   return m_Length;
}

Float64 CubicSpline::SplineSegment::Length(Float64 dx) const
{
   Float64 xa = pntA.X();

   SplineSegmentLengthFunction fn(*this);

   WBFL::Math::TrapezoidalRuleIntegrator integrator;
   Float64 L = integrator.Evaluate(fn, xa, xa + dx, 50);
   return L;
}

Float64 CubicSpline::SplineSegment::Evaluate(Float64 x) const
{
   Float64 xa = pntA.X();
   Float64 z = x - xa;
   return A + B * z + C * z * z + D * z * z * z;
}

Float64 CubicSpline::SplineSegment::Slope(Float64 x) const
{
   Float64 xa = pntA.X();
   Float64 z = x - xa;
   return B + 2 * C * z + 3 * D * z * z;
}

std::pair<Float64,Float64> CubicSpline::SplineSegment::GetPoint(Float64 distance) const
{
   Float64 xa = pntA.X();
   Float64 xb = pntB.X();

   SplineSegmentPointFunction fn(distance, xa, *this);

   WBFL::Math::BisectionRootFinder rootfinder;
   Float64 xr = rootfinder.FindRootInRange(fn, xa, xb, 0.00001);
   Float64 yr = Evaluate(xr);

   return std::make_pair(xr, yr);
}

Float64 CubicSpline::SplineSegment::Bearing(Float64 distance) const
{
   // evaluate the slope... convert to a bearing
   auto [x,y] = GetPoint(distance);

   Float64 slope = Slope(x);

   Float64 angle = atan(slope);
   return WBFL::Geometry::GeometricOperations::NormalizeAngle(angle);
}

Float64 CubicSpline::SplineSegment::Normal(Float64 distance) const
{
   Float64 angle = Bearing(distance);
   angle -= PI_OVER_2;
   return WBFL::Geometry::GeometricOperations::NormalizeAngle(angle);
}

std::vector<WBFL::Geometry::Point2d> CubicSpline::SplineSegment::Intersect(const WBFL::Geometry::Line2d& line) const
{
   std::vector<WBFL::Geometry::Point2d> vPoints;

   // get coefficients for function of line
   // y = mx + k

   // get the explicit form of the line and derive the slope, m, 
   // from the vector running in the direction of the line
   auto [p,dir] = line.GetExplicit();

   auto size = dir.GetSize();
   auto dx = size.Dx();
   auto dy = size.Dy();
   
   auto xa = pntA.X();
   auto xb = pntB.X();

   int nRoots = 0;
   std::array<Float64, 3> x;
   if (IsZero(dx))
   {
      // the line is vertical. there will be exactly one intersection point
      nRoots = 1;
      x[0] = p.X();
      x[0] -= xa;
   }
   else
   {
      Float64 m = dy / dx;

      // determine the y-intercept
      // we need any point on the line to do this. an easy point to get
      // is the point on the line nearest the origin
      WBFL::Geometry::Point2d origin(0, 0);

      auto poln = WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, origin);
      auto [X,Y] = poln.GetLocation();
      Float64 k = Y - m * (X - xa);

      // solve A + Bx + Cx^2 + Dx^3 - (mx+k) = (A-k) + (B-m)x + Cx^2 + Dx^3 = 0
      // NOTE: The coefficients in this CubicSplineSegment class and in the
      // cubic solver aren't the same.
      //          k1*x^3   + k2*x^2   + k3*x   + k4
      // Spline   D          C          B        A
      // Solver   A          B          C        D
      WBFL::Math::CubicSolver solver(D, C, (B - m), (A - k));

      auto roots = solver.Solve();
      nRoots = roots.size();
      int i = 0;
      for (auto r : roots)  x[i++] = r;

#if defined _DEBUG
      for (int i = 0; i < nRoots; i++)
      {
         Float64 z1 = A + B * x[i] + C * x[i] * x[i] + D * x[i] * x[i] * x[i];
         Float64 z2 = m * x[i] + k;
         CHECK(IsEqual(z1, z2, 0.0001));
   }
#endif // _DEBUG
   }

   for (int i = 0; i < nRoots; i++)
   {
      if (InRange(xa, x[i] + xa, xb))
      {
         // keep only the roots that are within the limits of the spline segment
         vPoints.emplace_back(x[i] + xa, Evaluate(x[i] + xa));
      }
   }

   return vPoints;
}


///////////////////////////////////////////////////////
CubicSpline::SplineSegmentLengthFunction::SplineSegmentLengthFunction(const SplineSegment& splineSegment) :
   m_SplineSegment(splineSegment)
{
}

Float64 CubicSpline::SplineSegmentLengthFunction::Evaluate(Float64 x) const
{
   Float64 dy = m_SplineSegment.Slope(x);
   return sqrt(1 + dy * dy);
}

std::unique_ptr<WBFL::Math::Function> CubicSpline::SplineSegmentLengthFunction::Clone() const
{
   return std::make_unique<CubicSpline::SplineSegmentLengthFunction>(m_SplineSegment);
}

///////////////////////////////////////////////////////
CubicSpline::SplineSegmentPointFunction::SplineSegmentPointFunction(Float64 distance, Float64 x0, const SplineSegment& splineSegment) :
   m_Distance(distance),
   m_X0(x0),
   m_SplineSegment(splineSegment)
{
}

Float64 CubicSpline::SplineSegmentPointFunction::Evaluate(Float64 x) const
{
   // solve (target distance - distance between [x0,x] along the spline curve) = 0
   //
   //        x
   //      /    __________
   // S -  |  \/(1 + dy^2) dx = 0
   //      /
   //       x0
   Float64 dist = x - m_X0;
   Float64 result = m_Distance - m_SplineSegment.Length(dist);
   return result;
}

std::unique_ptr<WBFL::Math::Function> CubicSpline::SplineSegmentPointFunction::Clone() const
{
   return std::make_unique<CubicSpline::SplineSegmentPointFunction>(m_Distance, m_X0, m_SplineSegment);
}

/////////////////////////////////////////////////////////////

CubicSpline::SplineSegmentProjectPointFunction::SplineSegmentProjectPointFunction(const SplineSegment& splineSegment, const WBFL::Geometry::Point2d& tp) :
   m_SplineSegment(splineSegment), m_TargetPoint(tp)
{
}

Float64 CubicSpline::SplineSegmentProjectPointFunction::Evaluate(Float64 s) const
{
   Float64 angle = m_SplineSegment.Normal(s);

   auto [x,y] = m_SplineSegment.GetPoint(s);

   WBFL::Geometry::Line2d line(WBFL::Geometry::Point2d(x,y), WBFL::Geometry::Vector2d(1.0, angle));  // line that is normal to the curve at "s" from the start

   // shortest offset between the target point and the normal line
   // > 0 if target point is on the right hand side of the normal line
   auto offset = WBFL::Geometry::GeometricOperations::ShortestOffsetToPoint(line, m_TargetPoint);
   return offset;
}

std::unique_ptr<WBFL::Math::Function> CubicSpline::SplineSegmentProjectPointFunction::Clone() const
{
   return std::make_unique<CubicSpline::SplineSegmentProjectPointFunction>(m_SplineSegment, m_TargetPoint);
}
