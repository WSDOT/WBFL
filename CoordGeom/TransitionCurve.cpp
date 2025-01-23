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
#include <CoordGeom/TransitionCurve.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/CubicSpline.h>

#include <GeomModel/GeomOp2d.h>
#include <GeomModel/Circle2d.h>


#define BACK_TANGENT    0x0001
#define TRANSITION_CURVE  0x0002
#define FORWARD_TANGENT 0x0004

// References
// 1) "Calculating coordinates along a clothoid between 2 curves", https://math.stackexchange.com/questions/1785816/calculating-coordinates-along-a-clothoid-betwen-2-curves
// 2) "How to calculate the length of a clothoid segment?", https://math.stackexchange.com/questions/3287710/how-to-calculate-length-of-clothoid-segment

using namespace WBFL::COGO;

// Determinate of
// | a b |
// | c d |
Float64 Det(Float64 a, Float64 b, Float64 c, Float64 d)
{
   return a * d - b * c;
}

std::shared_ptr<TransitionCurve> TransitionCurve::Create()
{
   return std::shared_ptr<TransitionCurve>(new TransitionCurve());
}

std::shared_ptr<TransitionCurve> TransitionCurve::Create(const WBFL::Geometry::Point2d& start, const Direction& startDirection, Float64 R1, Float64 R2, Float64 L, TransitionCurveType type)
{
   return std::shared_ptr<TransitionCurve>(new TransitionCurve(start, startDirection, R1, R2, L, type));
}

std::shared_ptr<TransitionCurve> TransitionCurve::Create(const TransitionCurve& curve)
{
   return std::shared_ptr<TransitionCurve>(new TransitionCurve(curve));
}

TransitionCurve::TransitionCurve(const WBFL::Geometry::Point2d& start, const Direction& startDirection, Float64 R1, Float64 R2, Float64 L, TransitionCurveType type)
{
   Init(start, startDirection, R1, R2, L, type);
}

void TransitionCurve::Init(const WBFL::Geometry::Point2d& start, const Direction& startDirection, Float64 R1, Float64 R2, Float64 L, TransitionCurveType type)
{
   PRECONDITION(!IsEqual(R1, R2)); // both can't same number
   PRECONDITION(!IsZero(L)); // curve must have a length

   m_Type = type;

   // capture input values before we adjust them
   m_r1 = R1;
   m_r2 = R2;

   // zero means infinite radius.... set value to maximum possible vale
   R1 = IsZero(R1) ? Float64_Max : R1;
   R2 = IsZero(R2) ? Float64_Max : R2;

   m_StartPoint = start;

   m_StartDirection = startDirection;
   m_StartDirectionValue = m_StartDirection.GetValue();

   m_R1 = fabs(R1);
   m_R2 = fabs(R2);

   m_Rs = Max(m_R1, m_R2);
   m_Re = Min(m_R1, m_R2);
   m_Sign = IsEqual(fabs(R1), m_Re) ? ::BinarySign(R1) : ::BinarySign(R2);

   m_L = L;

   Float64 a, b, delta;
   CHECK(!IsZero(m_R1) && !IsZero(m_R2));

   m_SignY = (m_R1 < m_R2) ? -1.0 : 1.0;
   m_A = sqrt(L / (1 / m_Re - 1 / m_Rs)); // from reference 2

   Float64 t1 = m_A * m_A / (2 * pow(Min(m_Rs, m_Re), 2));
   Float64 l1 = 2 * t1 * Min(m_Rs, m_Re);
   CHECK(IsEqual(l1, sqrt(2 * m_A * m_A * t1)));

   Float64 t2 = m_A * m_A / (2 * pow(Max(m_Rs, m_Re), 2));
   Float64 l2 = 2 * t2 * Max(m_Rs, m_Re);
   CHECK(IsEqual(l2, sqrt(2 * m_A * m_A * t2)));

   Float64 x_ = (m_R1 < m_R2) ? SpiralX(l1, t1) : SpiralX(l2, t2);
   Float64 y_ = (m_R1 < m_R2) ? SpiralY(l1, t1) : SpiralY(l2, t2);
   y_ *= m_Sign * m_SignY;

   // start of transition curve in global coordinates
   auto [x,y] = m_StartPoint.GetLocation();

   delta = m_StartDirectionValue;
   if (m_R1 < m_R2)
   {
      Float64 angle = m_Sign * l1 / (2 * m_Re);
      delta += angle + M_PI;
   }


   // Find origin of curve coordinates in global space
   // Solve for a and b using Cramer's Rule
   // The coordinate transformation equations given in the source document (reference #1) is:
   // x_ = (x - a)cos(delta) - (y - b)sin(delta)
   // y_ = (x - a)sin(delta) + (y - b)cos(delta)
   // These equations are incorrect!!!
   // The correct coordinate transformation equations are:
   // x_ =  (x - a)cos(delta) + (y - b)sin(delta)
   // y_ = -(x - a)sin(delta) + (y - b)cos(delta)
   Float64 cos_delta = cos(delta);
   Float64 sin_delta = sin(delta);
   Float64 a1 = -cos_delta;
   Float64 a2 = sin_delta;
   Float64 b1 = -sin_delta;
   Float64 b2 = -cos_delta;
   Float64 c1 = x_ - (x * cos_delta + y * sin_delta);
   Float64 c2 = y_ - (-x * sin_delta + y * cos_delta);


   Float64 Dx = Det(c1, b1,
      c2, b2);
   Float64 Dy = Det(a1, c1,
      a2, c2);
   Float64 D = Det(a1, b1,
      a2, b2);
   a = Dx / D;
   b = Dy / D;

   m_StartDist = l2;
   m_Ls = L + m_StartDist;

   m_SpiralAngle = m_Ls / (2 * m_Re);

   // set up the local spiral coordinate system
   m_SpiralOrigin.Move(a, b);
   m_SpiralRotation = delta;

   // Get the point and end direction
   m_EndPoint = PointOnCurve(m_L);
   m_EndDirection = m_StartDirection + m_Sign * m_SpiralAngle;

   m_PI = COGO::IntersectBearings(m_StartPoint, m_StartDirection, 0.0, m_EndPoint, m_EndDirection, 0.0);

   auto d1 = m_StartPoint.Distance(m_PI);
   auto d2 = m_EndPoint.Distance(m_PI);
   m_U = Max(d1, d2); // long tangent
   m_V = Min(d1, d2); // short tangent
}

const WBFL::Geometry::Point2d& TransitionCurve::GetStart() const
{
   return m_StartPoint;
}

const Direction& TransitionCurve::GetStartDirection() const
{
   return m_StartDirection;
}

Float64 TransitionCurve::GetStartRadius() const
{
   return m_r1;
}

Float64 TransitionCurve::GetEndRadius() const
{
   return m_r2;
}

TransitionCurveType TransitionCurve::GetTransitionType() const
{
   return m_Type;
}

Float64 TransitionCurve::GetRadius(Float64 distFromStart) const
{
   if (IsZero(distFromStart))
   {
      // at start of curve, use original radius
      return m_r1;
   }
   else if (IsEqual(distFromStart, m_L))
   {
      // at end of curve, use original radius
      return m_r2;
   }
   else
   {
      // Compute radius at distance from start
      // R*L = A^2  --> R = A^2/L
      return m_A * m_A / distFromStart;
   }
}

Float64 TransitionCurve::GetX() const
{
   return SpiralX(m_L, m_SpiralAngle);
}

Float64 TransitionCurve::GetY() const
{
   return SpiralY(m_L, m_SpiralAngle);
}

Float64 TransitionCurve::GetLongTangent() const
{
   return m_U;
}

Float64 TransitionCurve::GetShortTangent() const
{
   return m_V;
}

WBFL::Geometry::Point2d TransitionCurve::GetPI() const
{
   return m_PI;
}

Angle TransitionCurve::GetAngle() const
{
   return m_StartDirection.AngleBetween(m_EndDirection);
}

CurveDirection TransitionCurve::GetCurveDirection() const
{
   return (M_PI < GetAngle().GetValue() ? CurveDirection::Right : CurveDirection::Left);
}

WBFL::Geometry::Point2d TransitionCurve::GetEnd() const
{
   return m_EndPoint;
}

Direction TransitionCurve::GetEndDirection() const
{
   return m_EndDirection;
}

WBFL::Geometry::Point2d TransitionCurve::PointOnCurve(Float64 distFromStart) const
{
   WBFL::Geometry::Point2d pnt;
   if (distFromStart < 0)
   {
      // want point before curve, so use the back tangent
      pnt = COGO::LocateByDistanceAndDirection(GetStartPoint(), distFromStart, m_StartDirection, 0.0);
   }
   else if (m_Ls < distFromStart)
   {
      // want point after curve, so use the ahead tangent
      pnt = COGO::LocateByDistanceAndDirection(GetEndPoint(), distFromStart - m_Ls, m_EndDirection, 0.0);
   }
   else
   {
      auto s = DistanceFromStartOfSpiral(distFromStart);
      auto sweepAngle = pow(s / m_Ls, 2) * m_SpiralAngle;

      Float64 x_ = SpiralX(s, sweepAngle);
      Float64 y_ = m_Sign * m_SignY * SpiralY(s, sweepAngle);

      pnt.Move(x_, y_);

      pnt = WBFL::Geometry::GeometricOperations::LocalToGlobal(m_SpiralOrigin, m_SpiralRotation, pnt);
   }
   return pnt;
}

std::vector<WBFL::Geometry::Point2d> TransitionCurve::Divide(IndexType nParts) const
{
   PRECONDITION(0 < nParts);

   std::vector<WBFL::Geometry::Point2d> points;
   auto total_length = GetLength();
   auto step = total_length / nParts;

   auto nPoints = nParts + 1;
   for (IndexType i = 0; i < nPoints; i++)
   {
      Float64 dist_from_start = i * step;
      points.push_back(PointOnCurve(dist_from_start));
   }

   return points;
}

Float64 TransitionCurve::DistanceFromStart(const WBFL::Geometry::Point2d& point) const
{
   auto [dist,prjPoint] = DoProjectPoint(point);
   return dist;
}

void TransitionCurve::Offset(Float64 dx, Float64 dy)
{
   m_StartPoint.Offset(dx, dy);
   m_EndPoint.Offset(dx, dy);

   m_PI.Offset(dx, dy);
   m_SpiralOrigin.Offset(dx, dy);
}

//
// PathElement methods
//

std::shared_ptr<PathElement> TransitionCurve::Clone() const
{
   return std::shared_ptr<TransitionCurve>(new TransitionCurve(*this));
}

const WBFL::Geometry::Point2d& TransitionCurve::GetStartPoint() const
{
   return m_StartPoint;
}

const WBFL::Geometry::Point2d& TransitionCurve::GetEndPoint() const
{
   return m_EndPoint;
}

void TransitionCurve::Move(Float64 distance, const Direction& direction)
{
   WBFL::Geometry::Vector2d v(distance, direction);
   m_StartPoint.Offset(v.GetSize());
   m_EndPoint.Offset(v.GetSize());
}

Float64 TransitionCurve::GetLength() const
{
   return m_L;
}

std::vector<WBFL::Geometry::Point2d> TransitionCurve::GetKeyPoints() const
{
   std::vector<WBFL::Geometry::Point2d> vPoints{ GetStartPoint(),GetEndPoint() };
   return vPoints;
}

WBFL::Geometry::Point2d TransitionCurve::LocatePoint(Float64 distFromStart, OffsetType offsetType, Float64 offset, const Direction& direction) const
{
   offset = PathElement::AdjustOffset(distFromStart, offsetType, offset, direction); // offset is now along direction
   auto point = PointOnCurve(distFromStart);
   if (!IsZero(offset))
   {

      point = COGO::LocateByDistanceAndDirection(point, offset, direction, 0.0);
   }

   return point;
}

Direction TransitionCurve::GetBearing(Float64 distFromStart) const
{
   if (IsLE(distFromStart,0.0))
      return m_StartDirection;

   if (IsLE(m_Ls,distFromStart))
      return m_EndDirection;

   auto s = DistanceFromStartOfSpiral(distFromStart);
   auto sweepAngle = pow(s / m_Ls, 2) * m_SpiralAngle;

   if (m_R1 < m_R2)
   {
      sweepAngle -= m_SpiralAngle;
   }

   return m_StartDirectionValue + m_Sign * m_SignY * sweepAngle;
}

std::tuple<WBFL::Geometry::Point2d, Float64, bool> TransitionCurve::ProjectPoint(const WBFL::Geometry::Point2d& point) const
{
   // determine if the point projects onto the entry spiral, circular curve, or exit spiral
   int projection_region = ProjectionRegion(point);

   std::unique_ptr<WBFL::Geometry::Point2d> bkTangentPoint;
   Float64 bkTangentOffset;
   Float64 bkTangentDistance;
   if (projection_region & BACK_TANGENT)
   {
      // point projects onto the back tangent

      // Create a line object along the back tangent bearing. Locate the point on
      // that line that is nearest the input point
      auto pi = GetPI();

      WBFL::Geometry::Line2d line(m_StartPoint, pi);

      // compute offset from "point" to the back tangent (used to determine if it is closer to the back tangent than other points on the curve)
      bkTangentPoint = std::make_unique<WBFL::Geometry::Point2d>(WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, point));
      bkTangentOffset = point.Distance(*bkTangentPoint); // distance from the point to where it projects onto the back tangent

      // compute distance along the back tangent to the projection point
      bkTangentDistance = m_StartPoint.Distance(*bkTangentPoint);
      bkTangentDistance *= -1;

      // deal with the case when the point is exactly at the start of the curve
      bkTangentDistance = IsZero(bkTangentDistance, 1e-9) ? 0.0 : bkTangentDistance;
   }


   std::unique_ptr<WBFL::Geometry::Point2d> curvePoint;
   Float64 curveOffset;
   Float64 curveDistance;
   if (projection_region & TRANSITION_CURVE)
   {
      WBFL::Geometry::Point2d cp;
      std::tie(curveDistance,cp) = DoProjectPoint(point);
      curvePoint = std::make_unique<WBFL::Geometry::Point2d>(cp);
      curveOffset = point.Distance(*curvePoint);
   }

   std::unique_ptr<WBFL::Geometry::Point2d> fwdTangentPoint;
   Float64 fwdTangentOffset;
   Float64 fwdTangentDistance;
   if (projection_region & FORWARD_TANGENT)
   {
      // point projects onto the forward tangent

      // Create a line object along the forward tangent bearing. Locate the point on
      // that line that is nearest the input point
      auto pi = GetPI();

      WBFL::Geometry::Line2d line(pi, m_EndPoint);
      fwdTangentPoint = std::make_unique<WBFL::Geometry::Point2d>(WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, point));

      fwdTangentOffset = point.Distance(*fwdTangentPoint); // distance from the point to where it projects onto the forward tangent

      // compute distance along the forward tangent to the projection point
      fwdTangentDistance = m_EndPoint.Distance(*fwdTangentPoint);

      Float64 L = GetLength(); // length of curve

      // deal with case when point is exactly at the end of the curve
      if (IsZero(fwdTangentDistance))
         fwdTangentDistance = L;
      else
         fwdTangentDistance += L;
   }

   // find the projected point that is closest to the curve
   WBFL::Geometry::Point2d newPoint;
   Float64 distFromStart;
   bool bOnProjection;
   Float64 min_offset = Float64_Max;
   if (bkTangentPoint && bkTangentOffset < min_offset)
   {
      min_offset = bkTangentOffset;
      newPoint = *bkTangentPoint;
      distFromStart = bkTangentDistance;
      bOnProjection = true;
   }

   if (curvePoint && curveOffset < min_offset)
   {
      min_offset = curveOffset;
      newPoint = *curvePoint;
      distFromStart = curveDistance;
      bOnProjection = false;
   }

   if (fwdTangentPoint && fwdTangentOffset < min_offset)
   {
      min_offset = fwdTangentOffset;
      newPoint = *fwdTangentPoint;
      distFromStart = fwdTangentDistance;
      bOnProjection = true;
   }

   return std::make_tuple(newPoint, distFromStart, bOnProjection);
}

std::vector<WBFL::Geometry::Point2d> TransitionCurve::Intersect(const WBFL::Geometry::Line2d& line, bool bProjectBack, bool bProjectAhead) const
{
   std::vector<WBFL::Geometry::Point2d> vPoints;

   // when evaluated, this function returns the distance from the line to the curve
   // if the curve is to the left of the line the distance is negative
   CLineIntersectFunction function(this, line);
   WBFL::Math::BrentsRootFinder rootFinder;
   Float64 ya = function.Evaluate(m_StartDist);
   Float64 yb = function.Evaluate(m_Ls);
   if (0 < ya * yb)
   {
      // The end points don't bracket the solution....
      // Either the line doesn't intersect the spiral, it intersects it in two places
      // or it is tangent to the spiral

      // If the line intersects both the lines that are tangent to the spiral
      // then there is at least one intersection point
      auto SPI = GetPI();
      WBFL::Geometry::LineSegment2d seg1(m_StartPoint, SPI);

      WBFL::Geometry::Point2d pnt1;
      auto nIntersect1 = WBFL::Geometry::GeometricOperations::Intersect(line, seg1, &pnt1);

      WBFL::Geometry::LineSegment2d seg2(SPI, m_EndPoint);
      WBFL::Geometry::Point2d pnt2;
      auto nIntersect2 = WBFL::Geometry::GeometricOperations::Intersect(line, seg2, &pnt2);

      if (0 < nIntersect1 && 0 < nIntersect2)
      {
         // there are at least 1 intersection point... 
         // need to find a distance along the curve that is between the two intersection points
         // so we have a bracket that works... to do this, search for a point on the spiral where
         // the tangent to the spiral is parallel to the line
         CParallelLineFunction parallel_function(this, line);
         Float64 limit;
         try
         {
            limit = rootFinder.FindRootInRange(parallel_function, m_StartDist, m_Ls, 0.0000001);
         }
         catch (WBFL::Math::XRootFinder& /*e*/)
         {
            CHECK(false);
         }

         // if this location is on the intersecting line, the intersecting line
         // is tangent to the spiral
         auto POC = PointOnCurve(limit);

         if (line.ContainsPoint(POC, 0.001))
         {
            // Line is tangent
            vPoints.emplace_back(POC);
            return vPoints; // with tangency, there is only one solution so just leave now
         }
         else
         {
            // Line is not tangent
            try
            {
               // get first intersection in first segment
               Float64 dist1 = rootFinder.FindRootInRange(function, m_StartDist, limit, 0.0001);
               auto pnt = PointOnCurve(dist1);
               CHECK(TestIntersection(line, pnt));
               vPoints.emplace_back(pnt);

               // get second intersection in second segment
               Float64 dist2 = rootFinder.FindRootInRange(function, limit, m_Ls, 0.0001);
               pnt = PointOnCurve(dist2);
               CHECK(TestIntersection(line, pnt));
               vPoints.emplace_back(pnt);

               return vPoints; // we got both intersection points... leave now
            }
            catch (WBFL::Math::XRootFinder& /*mx*/)
            {
               CHECK(false); // should never fire
            }
         }
      }
   }
   else
   {
      // find the single intersection point
      try
      {
         Float64 dist1 = rootFinder.FindRootInRange(function, m_StartDist, m_Ls, 0.0001);
         auto pntOnCurve = PointOnCurve(dist1);
         CHECK(TestIntersection(line, pntOnCurve));
         vPoints.emplace_back(pntOnCurve);
      }
      catch (WBFL::Math::XRootFinder& /*mx*/)
      {
         CHECK(false);
      }
   }

   // check intersection with back tangent
   if (bProjectBack)
   {
      auto bkTangentLine = GetBackTangentLine();
      WBFL::Geometry::Point2d pnt;

      // if there was an intersection point and the point is before the start of the Start-SPI line
      // then this is an intersection on the back tangent projection 
      if (0 < WBFL::Geometry::GeometricOperations::Intersect(line, bkTangentLine, &pnt) && COGO::IsPointBeforeStart(m_StartPoint, m_PI, pnt))
      {
         vPoints.emplace_back(pnt);
      }
   }

   // check intersection with forward tangent
   if (bProjectAhead)
   {
      auto fwdTangentLine = GetForwardTangentLine();
      WBFL::Geometry::Point2d pnt;
      // if there was an intersection point and the point is after the end of the SPI-End line
      // then this is an intersection on the forward tangent projection 
      if (0 < WBFL::Geometry::GeometricOperations::Intersect(line, fwdTangentLine, &pnt) && COGO::IsPointAfterEnd(m_PI, m_EndPoint, pnt))
      {
         vPoints.emplace_back(pnt);
      }
   }

   return vPoints;
}

std::vector<std::shared_ptr<PathElement>> TransitionCurve::CreateOffsetPath(Float64 offset) const
{
   std::vector<std::shared_ptr<PathElement>> vElements;

   // determine if the curve degrades to a point

   auto curve_direction = GetCurveDirection();

   // create lines that are normal to the start and end of curve and find their intersection point
   const auto& pntStart = GetStart();
   const auto& pntEnd = GetEndPoint();

   const auto& dirStart = GetStartDirection();
   auto dirEnd = GetEndDirection();

   WBFL::Geometry::Line2d start_normal_line(pntStart, WBFL::Geometry::Vector2d(1.0, dirStart + PI_OVER_2));
   WBFL::Geometry::Line2d end_normal_line(pntEnd, WBFL::Geometry::Vector2d(1.0, dirEnd + PI_OVER_2));

   WBFL::Geometry::Point2d cc;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(start_normal_line, end_normal_line,&cc);
   CHECK(nIntersections == 1);

   // find distance from start and end to the intersection point
   auto d1 = pntStart.Distance(cc);
   auto d2 = pntEnd.Distance(cc);

   if ((curve_direction == CurveDirection::Right && (offset < d1 && offset < d2)) ||
      (curve_direction == CurveDirection::Left && (-offset < d1 && -offset < d2)))
   {
      // There isn't a way to make a parallel offset for a clothoid spiral. We will approximate the parallel offset with a spline curve
      IndexType nPoints = 10;

      Float64 Ls = GetLength();

      auto angle = GetAngle();

      if (PI_OVER_2 < angle)
      {
         // If the angle subtended by the spiral is more than 90deg, it is looping back on itself.
         // The cubic spline object can't handle that, so create two splines and join them into
         // a CompositePathElement object
         auto spline1 = CreateSubpathSpline(0.0, Ls / 2, nPoints);
         auto offset_spline1 = spline1->CreateOffsetPath(offset);
         for (auto& offset_spline_element : offset_spline1)
         {
            vElements.emplace_back(offset_spline_element);
         }

         auto spline2 = CreateSubpathSpline(Ls / 2, Ls, nPoints);
         auto offset_spline2 = spline2->CreateOffsetPath(offset);
         for (auto& offset_spline_element : offset_spline2)
         {
            vElements.emplace_back(offset_spline_element);
         }
      }
      else
      {
         auto spline = CreateSubpathSpline(0.0, Ls, nPoints);
         auto offset_spline = spline->CreateOffsetPath(offset);
         for (auto& offset_spline_element : offset_spline)
         {
            vElements.emplace_back(offset_spline_element);
         }
      }
   }
   return vElements;
}

std::vector<std::shared_ptr<PathElement>> TransitionCurve::CreateSubpath(Float64 start, Float64 end) const
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
      // only a fraction of the curve is part of the sub-path

      // build the sub-path curve
      IndexType nSplinePoints = 7;
      vElements.emplace_back(CreateSubpathSpline(start, end, nSplinePoints));
   }

   return vElements;
}

//
// Private methods
//

WBFL::Geometry::Line2d TransitionCurve::GetBackTangentLine() const
{
   WBFL::Geometry::Vector2d v(1.0, m_StartDirectionValue);
   return WBFL::Geometry::Line2d(m_StartPoint, v);
}

WBFL::Geometry::Line2d TransitionCurve::GetForwardTangentLine() const
{
   WBFL::Geometry::Vector2d v(1.0, m_EndDirection.GetValue());
   return WBFL::Geometry::Line2d(m_EndPoint, v);
}

int TransitionCurve::ProjectionRegion(const WBFL::Geometry::Point2d& point) const
{
   int result = 0;

   // put coordinate system at Start with X tangent to the curve
   auto xfrmPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(m_StartPoint, m_StartDirectionValue, point);
   Float64 x1 = xfrmPoint.X(); // X ordinate in coordinate system 1

   // put coordinate system at End with X tangent to the curve
   xfrmPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(m_EndPoint, m_EndDirection.GetValue(), point);
   Float64 x2 = xfrmPoint.X(); // X ordinate in coordinate system 2

   if (x1 < 0)
      result |= BACK_TANGENT;

   if (0 < x2)
      result |= FORWARD_TANGENT;

   if (0 <= x1 && x2 <= 0)
      result |= TRANSITION_CURVE;

   return result;
}

Float64 TransitionCurve::SpiralX(Float64 ls, Float64 angle) const
{
   return ls * (1 - pow(angle, 2) / 10 + pow(angle, 4) / 216 - pow(angle, 6) / 9360);
}

Float64 TransitionCurve::SpiralY(Float64 ls, Float64 angle) const
{
   return ls * (angle / 3 - pow(angle, 3) / 42 + pow(angle, 5) / 1320 - pow(angle, 7) / 75600);
}


Float64 TransitionCurve::DistanceFromStartOfSpiral(Float64 distance) const
{
   // Adjust distance into distance from start (point of infinite radius) of spiral
   if (m_R1 < m_R2)
   {
      // infinite radius is towards the end of the spiral so
      // change distance to be from that end
      distance = m_Ls - distance;
   }
   else
   {
      distance += m_StartDist;
   }

   return distance;
}

std::pair<Float64,WBFL::Geometry::Point2d> TransitionCurve::DoProjectPoint(const WBFL::Geometry::Point2d& point) const
{
   CSpiralFunction function(this, point);
   WBFL::Math::BrentsRootFinder rootFinder;
   Float64 dist = rootFinder.FindRootInRange(function, m_StartDist, m_Ls, 0.00001); // dist from end
   return std::make_pair(dist, PointOnCurve(dist));
}

std::shared_ptr<CubicSpline> TransitionCurve::CreateSubpathSpline(Float64 start, Float64 end, IndexType nPoints) const
{
   // create a cubic spline to represent the sub-portion of this spiral
   auto spline = CubicSpline::Create();

   auto pntStart = PointOnCurve(start);
   auto dirStart = GetBearing(start);

   spline->AddPoint(pntStart);
   spline->SetStartDirection(dirStart);

   // lay out some points between the start point and the end point
   // so the cubic spline gives a good approximation of the spiral
   IndexType nIntermediatePoints = nPoints - 2;
   for (IndexType i = 0; i < nIntermediatePoints; i++)
   {
      Float64 d = start + (i + 1) * (end - start) / (nIntermediatePoints + 1);
      spline->AddPoint(PointOnCurve(d));
   }

   // finish with the end point

   auto pntEnd = PointOnCurve(end);
   auto dirEnd = GetBearing(end);
   spline->AddPoint(pntEnd);
   spline->SetEndDirection(dirEnd);

   return spline;
}

#if defined _DEBUG
bool TransitionCurve::IsPointOnCurve(const WBFL::Geometry::Point2d& point) const
{
   auto dist = DistanceFromStart(point);
   auto pntOnCurve = PointOnCurve(dist);
   return IsZero(point.Distance(pntOnCurve));
}

bool TransitionCurve::IsPointOnLine(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Point2d& point) const
{
   return line.ContainsPoint(point);
}

bool TransitionCurve::TestIntersection(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Point2d& point) const
{
   return IsPointOnCurve(point) && IsPointOnLine(line, point);
}
#endif // _DEBUG
