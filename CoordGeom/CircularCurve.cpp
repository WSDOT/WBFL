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
#include <CoordGeom/CircularCurve.h>
#include <CoordGeom/Utilities.h>
#include <CoordGeom/PathSegment.h>

#include <GeomModel/GeomOp2d.h>
#include <GeomModel/Circle2d.h>

#define BACK_TANGENT    0x0001
#define CIRCULAR_CURVE  0x0002
#define FORWARD_TANGENT 0x0004

using namespace WBFL::COGO;

std::shared_ptr<CircularCurve> CircularCurve::Create()
{
   return std::shared_ptr<CircularCurve>(new CircularCurve());
}

std::shared_ptr<CircularCurve> CircularCurve::Create(const WBFL::Geometry::Point2d& pbt, const WBFL::Geometry::Point2d& pi, const WBFL::Geometry::Point2d& pft, Float64 radius)
{
   return std::shared_ptr<CircularCurve>(new CircularCurve(pbt, pi, pft, radius));
}

std::shared_ptr<CircularCurve> CircularCurve::Create(const CircularCurve& curve)
{
   return std::shared_ptr<CircularCurve>(new CircularCurve(curve));
}

CircularCurve::CircularCurve()
{
   m_PBT.Move(-1000, 0);
   m_PI.Move(0, 0);
   m_PFT.Move(1000, 1000);
   m_Radius = 1000;
}

CircularCurve::CircularCurve(const WBFL::Geometry::Point2d& pbt, const WBFL::Geometry::Point2d& pi, const WBFL::Geometry::Point2d& pft, Float64 radius) :
   m_PBT(pbt), m_PI(pi), m_PFT(pft),m_Radius(radius)
{
}

void CircularCurve::SetPBT(const WBFL::Geometry::Point2d& pbt)
{
   m_PBT = pbt;
   OnPathElementChanged();
}

const WBFL::Geometry::Point2d& CircularCurve::GetPBT() const
{
   return m_PBT;
}

void CircularCurve::SetPI(const WBFL::Geometry::Point2d& pi)
{
   m_PI = pi;
   OnPathElementChanged();
}

const WBFL::Geometry::Point2d& CircularCurve::GetPI() const
{
   return m_PI;
}

void CircularCurve::SetPFT(const WBFL::Geometry::Point2d& pft)
{
   m_PFT = pft;
   OnPathElementChanged();
}

const WBFL::Geometry::Point2d& CircularCurve::GetPFT() const
{
   return m_PFT;
}

void CircularCurve::SetRadius(Float64 radius)
{
   PRECONDITION(0 < radius);
   m_Radius = radius;
   OnPathElementChanged();
}

Float64 CircularCurve::GetRadius() const
{
   return m_Radius;
}

WBFL::Geometry::Point2d CircularCurve::GetPC() const
{
   auto bkTangentBearing = GetBackTangentBearing();
   bkTangentBearing.Increment(M_PI); // reverse the bearing (PI to PBT);
   auto T = GetTangent();
   return Utilities::LocateByDistanceAndDirection(m_PI, T, bkTangentBearing, 0.0);
}

WBFL::Geometry::Point2d CircularCurve::GetPT() const
{
   auto fwdTangentBearing = GetForwardTangentBearing();
   auto T = GetTangent();
   return Utilities::LocateByDistanceAndDirection(m_PI, T, fwdTangentBearing, 0.0);
}

Direction CircularCurve::GetForwardTangentBearing() const
{
   return Utilities::MeasureDirection(m_PI, m_PFT);
}

Direction CircularCurve::GetBackTangentBearing() const
{
   return Utilities::MeasureDirection(m_PBT, m_PI);
}

Angle CircularCurve::GetAngle() const
{
   // Total curve angle
   auto bkTangentBearing = GetBackTangentBearing();
   auto fwdTangentBearing = GetForwardTangentBearing();

   auto direction = GetCurveDirection();
   Angle angle;
   if (direction == CurveDirection::Left)
      angle = fwdTangentBearing.AngleBetween(bkTangentBearing);
   else
      angle = bkTangentBearing.AngleBetween(fwdTangentBearing);

   angle.Normalize();
   return angle;
}
   
Float64 CircularCurve::GetTangent() const
{
   auto angle = GetAngle().GetValue();
   return m_Radius * tan(angle / 2);
}

Float64 CircularCurve::GetChord() const
{
   return GetPC().Distance(GetPT());
}

Float64 CircularCurve::GetMidOrdinate() const
{
   auto angle = GetAngle();
   return m_Radius * (1 - cos(angle.GetValue() / 2));
}

Float64 CircularCurve::GetExternal() const
{
   auto angle = GetAngle();
   return m_Radius * (1 / cos(angle.GetValue() / 2) - 1);
}

WBFL::Geometry::Point2d CircularCurve::GetCenter() const
{
   auto PC = GetPC();
   auto PT = GetPT();

   if (m_PI == PC || m_PI == PT)
   {
      // this curve is really just a point... CC is going to be at the same location
      // creating lines t1 and t2 will fail below.... just you the PI and the CC and return
      return m_PI;
   }

   WBFL::Geometry::Line2d t1(m_PI, PC); // bk tangent (reversed)
   WBFL::Geometry::Line2d t2(m_PI, PT); // fwd tangent (reversed);

   auto n1 = WBFL::Geometry::GeometricOperations::CreateNormalLineThroughPoint(t1, PC);
   auto n2 = WBFL::Geometry::GeometricOperations::CreateNormalLineThroughPoint(t2, PT);

   WBFL::Geometry::Point2d center;
   auto result = WBFL::Geometry::GeometricOperations::Intersect(n1, n2, &center);
   CHECK(result == 1);

#if defined _DEBUG
   // intersect tangents... should intersect at PI
   WBFL::Geometry::Point2d testPoint;
   result = WBFL::Geometry::GeometricOperations::Intersect(t1, t2,&testPoint);
   CHECK(result == 1);
   CHECK(testPoint == m_PI);

   // intersect forward tangent and its normal
   // should intersect at PC
   result = WBFL::Geometry::GeometricOperations::Intersect(t1, n1, &testPoint);
   CHECK(result == 1);
   CHECK(testPoint == PC);

   // intersect back tangent and its normal
   // should intersect at PT
   result = WBFL::Geometry::GeometricOperations::Intersect(t2, n2, &testPoint);
   CHECK(result == 1);
   CHECK(testPoint == PT);
#endif // _DEBUG

   return center;
}

CurveDirection CircularCurve::GetCurveDirection() const
{
   auto bkTangentBearing = GetBackTangentBearing();
   auto fwdTangentBearing = GetForwardTangentBearing();

   auto angle = fwdTangentBearing.AngleBetween(bkTangentBearing);
   return (M_PI < angle.GetValue() ? CurveDirection::Right : CurveDirection::Left);
}

Angle CircularCurve::GetDegreeOfCurvature(const Angle& delta, DegreeCurvature type) const
{
   Float64 dc = 0;
   if (type == DegreeCurvature::Arc || type == DegreeCurvature::Highway)
   {
      dc = delta.GetValue() / m_Radius;
   }
   else
   {
      dc = 2 * asin(delta.GetValue() / (2 * m_Radius));
   }

   return dc;
}

WBFL::Geometry::Point2d CircularCurve::PointOnCurve(Float64 distFromStart) const
{
   Float64 l = GetLength();

   if (distFromStart <= 0)
   {
      // Before curve
      auto bkTangentBrg = GetBackTangentBearing();
      auto pc = GetPC();
      return Utilities::LocateByDistanceAndDirection(pc, distFromStart, bkTangentBrg, 0.0);
   }
   else if (l <= distFromStart)
   {
      // After curve
      auto fwdTangentBrg = GetForwardTangentBearing();
      auto pt = GetPT();
      return Utilities::LocateByDistanceAndDirection(pt, distFromStart - l, fwdTangentBrg, 0.0);
   }
   else
   {
      // On curve
      auto dir = GetCurveDirection();

      Float64 sign = (dir == CurveDirection::Left ? 1 : -1);

      Float64 sweepAngle = sign * distFromStart / m_Radius;

      // start of circular curve
      auto pc = GetPC();

      // center of circular curve
      auto center = GetCenter();

      return pc.Rotate(center, sweepAngle);
   }
}

std::vector<WBFL::Geometry::Point2d> CircularCurve::Divide(IndexType nParts) const
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

// PathElement methods

std::shared_ptr<PathElement> CircularCurve::Clone() const
{
   return std::shared_ptr<CircularCurve>(new CircularCurve(*this));
}

const WBFL::Geometry::Point2d& CircularCurve::GetStartPoint() const
{
   m_PC = GetPC();
   return m_PC;
}

const WBFL::Geometry::Point2d& CircularCurve::GetEndPoint() const
{
   m_PT = GetPT();
   return m_PT;
}

void CircularCurve::Move(Float64 distance, const Direction& direction)
{
   WBFL::Geometry::Vector2d v(distance, direction);
   m_PBT.Offset(v.GetSize());
   m_PI.Offset(v.GetSize());
   m_PFT.Offset(v.GetSize());
   OnPathElementChanged();
}

void CircularCurve::Offset(Float64 dx, Float64 dy)
{
   m_PBT.Offset(dx, dy);
   m_PI.Offset(dx, dy);
   m_PFT.Offset(dx, dy);
   OnPathElementChanged();
}

Float64 CircularCurve::GetLength() const
{
   auto angle = GetAngle();
   return m_Radius * angle.GetValue();
}

std::vector<WBFL::Geometry::Point2d> CircularCurve::GetKeyPoints() const
{
   std::vector<WBFL::Geometry::Point2d> vPoints{ GetPC(),GetPT() };
   return vPoints;
}

WBFL::Geometry::Point2d CircularCurve::LocatePoint(Float64 distFromStart, OffsetType offsetType, Float64 offset, const Direction& direction) const
{
   offset = PathElement::AdjustOffset(distFromStart, offsetType, offset, direction); // offset is now along direction
   auto point = PointOnCurve(distFromStart);
   if (!IsZero(offset))
   {

      point = Utilities::LocateByDistanceAndDirection(point, offset, direction, 0.0);
   }

   return point;
}

Direction CircularCurve::GetBearing(Float64 distFromStart) const
{
   Float64 l = GetLength();
   if (distFromStart <= 0)
   {
      // before curve
      return GetBackTangentBearing();
   }
   else if (l <= distFromStart)
   {
      // after curve
      return GetForwardTangentBearing();
   }
   else
   {
      // on curve
      auto dir = GetCurveDirection();
      Float64 sign = (dir == CurveDirection::Left ? 1 : -1);
      Float64 sweepAngle = sign * distFromStart / m_Radius;
      return GetBackTangentBearing().Increment(sweepAngle);
   }
}

std::tuple<WBFL::Geometry::Point2d, Float64, bool>  CircularCurve::ProjectPoint(const WBFL::Geometry::Point2d& point) const
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
      WBFL::Geometry::Line2d line(GetPBT(), GetPI());

      // compute offset from "point" to the back tangent (used to determine if it is closer to the back tangent than other points on the curve)
      bkTangentPoint = std::make_unique<WBFL::Geometry::Point2d>(WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, point));
      bkTangentOffset = point.Distance(*bkTangentPoint); // distance from the point to where it projects onto the back tangent

      // compute distance along the back tangent to the projection point
      auto PC = GetPC();
      bkTangentDistance = PC.Distance(*bkTangentPoint);
      bkTangentDistance *= -1;

      // deal with the case when the point is exactly at the start of the curve
      bkTangentDistance = IsZero(bkTangentDistance, 1e-9) ? 0.0 : bkTangentDistance;
   }

   std::unique_ptr<WBFL::Geometry::Point2d> curvePoint;
   Float64 curveOffset;
   Float64 curveDistance;
   if (projection_region & CIRCULAR_CURVE)
   {
      // Create a line from center through the projected point
      // Intersect this line with the circular arc, finding the
      // point that is nearest PC.
      auto center = GetCenter();

      WBFL::Geometry::Line2d line(center, point);
      WBFL::Geometry::Circle2d circle(center, m_Radius);

      auto PC = GetPC();

      WBFL::Geometry::Point2d i1 = Utilities::IntersectLineAndCircle(line, circle, point);
      curvePoint = std::make_unique<WBFL::Geometry::Point2d>(i1);

      auto dir = GetCurveDirection();
      Float64 angle;
      if (dir == CurveDirection::Right)
         angle = WBFL::Geometry::GeometricOperations::Angle(*curvePoint, center, PC);
      else
         angle = WBFL::Geometry::GeometricOperations::Angle(PC, center, *curvePoint);

#if defined _DEBUG
      // The subtended angle must be less than or equal to the
      // circular curve angle (or the point isn't on the circular part of the curve)
      auto cca = GetAngle();
      CHECK(IsLE(angle, cca.GetValue()));
#endif // _DEBUG

      CHECK(0 <= angle);
      curveDistance = m_Radius * angle; // distance along circular curve to projected point
      curveOffset = point.Distance(*curvePoint); // distance from the point to where it projects onto the circular curve
   }

   std::unique_ptr<WBFL::Geometry::Point2d> fwdTangentPoint;
   Float64 fwdTangentOffset;
   Float64 fwdTangentDistance;
   if (projection_region & FORWARD_TANGENT)
   {
      // point projects onto the forward tangent

      // Create a line object along the forward tangent bearing. Locate the point on
      // that line that is nearest the input point
      auto PI = GetPI();
      auto PFT = GetPFT();

      WBFL::Geometry::Line2d line(PI, PFT);

      fwdTangentPoint = std::make_unique<WBFL::Geometry::Point2d>(WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, point));
      fwdTangentOffset = point.Distance(*fwdTangentPoint); // distance from the point to where it projects onto the forward tangent

      // compute distance along the forward tangent to the projection point
      auto PT = GetPT();
      fwdTangentDistance = PT.Distance(*fwdTangentPoint);

      Float64 L = GetLength(); // length of curve

      // deal with case when point is exactly at the end of the curve
      if (IsZero(fwdTangentDistance))
         fwdTangentDistance = L;
      else
         fwdTangentDistance += L;
   }

   // find the projected point that is closest to the curve
   Float64 min_offset = Float64_Max;
   std::tuple<WBFL::Geometry::Point2d, Float64, bool> result;
   if (bkTangentPoint && bkTangentOffset < min_offset)
   {
      min_offset = bkTangentOffset;
      result = std::make_tuple(*bkTangentPoint, bkTangentDistance, true);
   }

   if (curvePoint && curveOffset < min_offset)
   {
      min_offset = curveOffset;
      result = std::make_tuple(*curvePoint, curveDistance, false);
   }

   if (fwdTangentPoint && fwdTangentOffset < min_offset)
   {
      min_offset = fwdTangentOffset;
      result = std::make_tuple(*fwdTangentPoint, fwdTangentDistance, true);
   }
   
   return result;
}

std::vector<WBFL::Geometry::Point2d> CircularCurve::Intersect(const WBFL::Geometry::Line2d& line, bool bProjectBack, bool bProjectAhead) const
{
   std::vector<WBFL::Geometry::Point2d> vPoints;

   //
   // First check to see if the line intersects the circular curve
   ///

   // get the key circular curve points
   auto pc = GetPC();
   auto center = GetCenter();
   auto pt = GetPT();
   const auto& pi = GetPI();

   WBFL::Geometry::Circle2d circle(center, m_Radius);

   WBFL::Geometry::Point2d pnt1, pnt2;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line, circle, &pnt1, &pnt2);

   auto direction = GetCurveDirection();

   Float64 delta;
   if (direction == CurveDirection::Left)
      delta = WBFL::Geometry::GeometricOperations::Angle(pc, center, pt);
   else
      delta = WBFL::Geometry::GeometricOperations::Angle(pt, center, pc);

#if defined _DEBUG
   CHECK(IsEqual(delta, GetAngle().GetValue()));
#endif

   std::unique_ptr<WBFL::Geometry::Point2d> pntCurve1, pntCurve2;
   if (1 <= nIntersections)
   {
      Float64 angle;
      if (direction == CurveDirection::Left)
         angle = WBFL::Geometry::GeometricOperations::Angle(pc, center, pnt1);
      else
         angle = WBFL::Geometry::GeometricOperations::Angle(pnt1, center, pc);

      if (0 <= angle && angle <= delta)
         pntCurve1 = std::make_unique<WBFL::Geometry::Point2d>(pnt1);
   }

   if (nIntersections == 2)
   {
      Float64 angle;
      if (direction == CurveDirection::Left)
         angle = WBFL::Geometry::GeometricOperations::Angle(pc, center, pnt2);
      else
         angle = WBFL::Geometry::GeometricOperations::Angle(pnt2, center, pc);

      if (0 <= angle && angle <= delta)
         pntCurve2 = std::make_unique<WBFL::Geometry::Point2d>(pnt2);
   }

   if (pntCurve1 == nullptr && pntCurve2 != nullptr)
   {
      pntCurve1.swap(pntCurve2);
   }

   // both intersection points are in the circular curve, we are done
   if (pntCurve1 && pntCurve2)
   {
      CHECK(nIntersections == 2);
      // make the point that is nearest the beginning of the curve the first point
      auto dist1 = pc.Distance(*pntCurve1);
      auto dist2 = pc.Distance(*pntCurve2);
      if (dist1 < dist2)
      {
         vPoints.emplace_back(*pntCurve1);
         vPoints.emplace_back(*pntCurve2);
      }
      else
      {
         vPoints.emplace_back(*pntCurve2);
         vPoints.emplace_back(*pntCurve1);
      }
   }
   else
   {
      // If we get here, the line doesn't intersect the circular curve 
      // or it only intersects it in one place

      // check intersection with back tangent
      std::unique_ptr<WBFL::Geometry::Point2d> bkTangentPoint;
      if (bProjectBack == true)
      {
         auto bkTangentLine = GetBackTangentLine();
         WBFL::Geometry::Point2d pnt;
         if (WBFL::Geometry::GeometricOperations::Intersect(line, bkTangentLine, &pnt) == 1)
            bkTangentPoint = std::make_unique<WBFL::Geometry::Point2d>(pnt);

         // if there was an intersection point and the point is not before the start of the TS-PI line
         // then this isn't an intersection on the back tangent projection 
         if (bkTangentPoint && !Utilities::IsPointBeforeStart(pc, pi, *bkTangentPoint))
            bkTangentPoint = nullptr;
      }

      // check intersection with forward tangent
      std::unique_ptr<WBFL::Geometry::Point2d> fwdTangentPoint;
      if (bProjectAhead == true)
      {
         auto fwdTangentLine = GetForwardTangentLine();
         WBFL::Geometry::Point2d pnt;
         if (WBFL::Geometry::GeometricOperations::Intersect(line, fwdTangentLine, &pnt) == 1)
            fwdTangentPoint = std::make_unique<WBFL::Geometry::Point2d>(pnt);

         // if there was an intersection point and the point is not after the end of the PI-ST line
         // then this isn't an intersection on the forward tangent projection 
         if (fwdTangentPoint && !Utilities::IsPointAfterEnd(pi, pt, *fwdTangentPoint))
            fwdTangentPoint = nullptr;
      }

#if defined _DEBUG
      int nPoints = 0;

      if (bkTangentPoint)
         nPoints++;

      if (pntCurve1)
         nPoints++;

      if (pntCurve2)
         nPoints++;

      if (fwdTangentPoint)
         nPoints++;

      // This method assumes there is never more than 2 intersection points
      CHECK(nPoints <= 2);
#endif

      if(bkTangentPoint) vPoints.emplace_back(*bkTangentPoint);
      if (pntCurve1) vPoints.emplace_back(*pntCurve1);
      if (pntCurve2) vPoints.emplace_back(*pntCurve2);
      if (fwdTangentPoint) vPoints.emplace_back(*fwdTangentPoint);

#if defined _DEBUG
      CHECK(vPoints.size() == nPoints);
#endif
   }

   return vPoints;
}

std::vector<std::shared_ptr<PathElement>> CircularCurve::CreateOffsetPath(Float64 offset) const
{
   std::vector<std::shared_ptr<PathElement>> vElements;

   auto curve_direction = GetCurveDirection();

   auto PC = GetPC();
   auto PT = GetPT();

   // It is useful to have line objects that represent the tangents of the curve.
   // Create them now because they will be used later.
   const auto& PBT = GetPBT();
   const auto& PI = GetPI();
   const auto& PFT = GetPFT();

   WBFL::Geometry::Line2d l1(PBT, PI);
   WBFL::Geometry::Line2d l2(PI, PFT);

   // Deal with the case of the curve degrading to a single point
   if ((curve_direction == CurveDirection::Right && m_Radius <= offset) ||
       (curve_direction == CurveDirection::Left && m_Radius <= -offset))
   {
      // The parallel curve is past the CC point... this degrades the curve to a point

      // offset the curve tangents and intersect them
      l1.Offset(-offset);
      l2.Offset(-offset);

      WBFL::Geometry::Point2d ip;
      auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(l1, l2, &ip);
      CHECK(nIntersections == 1);

      // implement as a zero length path segment
      vElements.emplace_back(PathSegment::Create(ip, ip));
   }
   else
   {
      //
      // Curve remains a curve
      //
      // Use the curve tangents to create new tangents at an offset. The intersection point of these lines is the new PI.
      auto bkTangent = WBFL::Geometry::GeometricOperations::CreateParallelLine(l1, offset);
      auto fwdTangent = WBFL::Geometry::GeometricOperations::CreateParallelLine(l2, offset);

      WBFL::Geometry::Point2d newPI;
      auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(bkTangent, fwdTangent, &newPI);
      CHECK(nIntersections == 1);

      auto newPBT = WBFL::Geometry::GeometricOperations::PointOnLineNearest(bkTangent, PC);
      auto newPFT = WBFL::Geometry::GeometricOperations::PointOnLineNearest(fwdTangent, PT);

      // compute new circular curve radius
      Float64 newRadius = (curve_direction == CurveDirection::Right ? m_Radius - offset : m_Radius + offset);

      // create the offset curve
      auto offset_curve = CircularCurve::Create(newPBT, newPI, newPFT, newRadius);

#if defined _DEBUG
      CHECK(GetCenter() == offset_curve->GetCenter());
      CHECK(GetAngle() == offset_curve->GetAngle());
#endif

      vElements.emplace_back(offset_curve);
   }
   return vElements;
}

std::vector<std::shared_ptr<PathElement>> CircularCurve::CreateSubpath(Float64 start, Float64 end) const
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

      // start in circular curve
      auto pbt = PointOnCurve(start);
      auto bkTangentBrg = GetBearing(start);

      // ends in circular curve
      auto pft = PointOnCurve(end);
      auto fwdTangentBrg = GetBearing(end);

      // PI is at the intersection of the tangents
      auto pi = Utilities::IntersectBearings(pbt, bkTangentBrg, 0.0, pft, fwdTangentBrg, 0.0);

      vElements.emplace_back(CircularCurve::Create(pbt, pi, pft, m_Radius));
   }

   return vElements;
}

int CircularCurve::ProjectionRegion(const WBFL::Geometry::Point2d& point) const
{
   int result = 0;

   // check circular curve

   // put coordinate system at PC with X tangent to the curve
   auto origin = GetPC();
   auto brg = GetBackTangentBearing();

   auto xfrmPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(origin, brg.GetValue(), point);
   Float64 x1 = xfrmPoint.X(); // X ordinate in coordinate system 1

   // put coordinate system at PT with X tangent to the curve
   origin = GetPT();
   brg = GetForwardTangentBearing();

   xfrmPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(origin, brg.GetValue(), point);
   Float64 x2 = xfrmPoint.X(); // X ordinate in coordinate system 2

   if (x1 < 0)
      result |= BACK_TANGENT;

   if (0 < x2)
      result |= FORWARD_TANGENT;

   if (0 <= x1 && x2 <= 0)
      result |= CIRCULAR_CURVE;

   return result;
}

WBFL::Geometry::Line2d CircularCurve::GetBackTangentLine() const
{
   return WBFL::Geometry::Line2d(m_PBT, m_PI);
}

WBFL::Geometry::Line2d CircularCurve::GetForwardTangentLine() const
{
   return WBFL::Geometry::Line2d(m_PI, m_PFT);
}

#if defined _UNITTEST
bool CircularCurve::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CircularCurve");

   // Test curve direction
   CircularCurve curve;

   // Forward Tangent Bearing = N 45 E
   curve.SetPBT(WBFL::Geometry::Point2d(0, 1000));
   curve.SetPI(WBFL::Geometry::Point2d(1000, 1000));
   curve.SetPFT(WBFL::Geometry::Point2d(1000, 1500));
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   curve.SetPFT(WBFL::Geometry::Point2d(1000, 500));
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   // Forward Tangent Bearing = N 45 W
   curve.SetPBT(WBFL::Geometry::Point2d(0, 1000));
   curve.SetPI(WBFL::Geometry::Point2d(1000, 1000));
   curve.SetPFT(WBFL::Geometry::Point2d(-1000, 1500));
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   curve.SetPFT(WBFL::Geometry::Point2d(-1000, 500));
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   // Forward Tangent Bearing = S 45 W
   curve.SetPBT(WBFL::Geometry::Point2d(0, 1000));
   curve.SetPI(WBFL::Geometry::Point2d(-1000, -1000));
   curve.SetPFT(WBFL::Geometry::Point2d(-1000, -1500));
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   curve.SetPFT(WBFL::Geometry::Point2d(-1000, -500));
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   // Forward Tangent Bearing = S 45 E
   curve.SetPBT(WBFL::Geometry::Point2d(0, 1000));
   curve.SetPI(WBFL::Geometry::Point2d(1000, -1000));
   curve.SetPFT(WBFL::Geometry::Point2d(1000, -500));
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   curve.SetPFT(WBFL::Geometry::Point2d(1000, -1500));
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   // Test symmetrical curve to the right
   curve.SetPBT(WBFL::Geometry::Point2d(0, 1000));
   curve.SetPI(WBFL::Geometry::Point2d(700, 1000));
   curve.SetPFT(WBFL::Geometry::Point2d(1000, 1300));
   curve.SetRadius(500);
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);
   curve.SetPFT(WBFL::Geometry::Point2d(1000, 700));
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   TRY_TESTME(curve.GetBackTangentBearing() == Direction(0.0));
   TRY_TESTME(curve.GetForwardTangentBearing() == Direction(7 * M_PI / 4));

   TRY_TESTME(curve.GetPC() == WBFL::Geometry::Point2d(492.89322, 1000));
   TRY_TESTME(curve.GetPT() == WBFL::Geometry::Point2d(846.44661, 853.55339));

   TRY_TESTME(IsEqual(curve.GetChord(), 382.68343));
   TRY_TESTME(IsEqual(curve.GetTangent(), 207.10678));
   TRY_TESTME(IsEqual(curve.GetMidOrdinate(), 38.06023));
   TRY_TESTME(IsEqual(curve.GetLength(), 392.69908));
   TRY_TESTME(curve.GetCenter() == WBFL::Geometry::Point2d(492.89322,500));

   // Bearing and normal
   // Point before curve
   TRY_TESTME(curve.GetBearing(-1) == Direction(0.0));
   TRY_TESTME(curve.GetNormal(-1) == Direction(3 * PI_OVER_2));

   // Mid-point of curve
   TRY_TESTME(curve.GetBearing(curve.GetLength() / 2) == Direction(7 * M_PI / 4 + M_PI / 8));
   TRY_TESTME(curve.GetNormal(curve.GetLength() / 2) == Direction(7 * M_PI / 4 + M_PI / 8 - PI_OVER_2));

   // Point after curve
   TRY_TESTME(curve.GetBearing(10000) == Direction(7 * M_PI / 4));
   TRY_TESTME(curve.GetNormal(10000) == Direction(7 * M_PI / 4 - PI_OVER_2));

   // PointOnCurve
   TRY_TESTME(curve.PointOnCurve(-100) == curve.GetPC().Offset(-100, 0)); // Before PC
   TRY_TESTME(curve.PointOnCurve(0) == curve.GetPC()); // At PC
   TRY_TESTME(curve.PointOnCurve(curve.GetLength() / 2) == WBFL::Geometry::Point2d(684.23493, 961.93977)); // Half-way around the curve
   TRY_TESTME(curve.PointOnCurve(curve.GetLength()) == curve.GetPT()); // At PT
   TRY_TESTME(curve.PointOnCurve(curve.GetLength() + 100) == curve.GetPT().Offset(100*sin(M_PI/4),-100*cos(M_PI/4)));

   // ProjectPoint
   WBFL::Geometry::Point2d point(300, 1100);
   WBFL::Geometry::Point2d p;
   Float64 distFromStart;
   bool bOnProjection;
   std::tie(p,distFromStart,bOnProjection) = curve.ProjectPoint(point);
   TRY_TESTME(p == WBFL::Geometry::Point2d(300, 1000));
   TRY_TESTME(IsEqual(distFromStart, -192.89321881345245));
   TRY_TESTME(bOnProjection == true);

   point.Move(300, 900);
   std::tie(p, distFromStart, bOnProjection) = curve.ProjectPoint(point);
   TRY_TESTME(p == WBFL::Geometry::Point2d(300, 1000));
   TRY_TESTME(IsEqual(distFromStart, -192.89321881345245));
   TRY_TESTME(bOnProjection == true);

   point.Move(500, 1100);
   std::tie(p, distFromStart, bOnProjection) = curve.ProjectPoint(point);
   TRY_TESTME(p == WBFL::Geometry::Point2d(498.81512, 999.96493));
   TRY_TESTME(IsEqual(distFromStart, 5.9220407208210313));
   TRY_TESTME(bOnProjection == false);

   point.Move(500, 900);
   std::tie(p, distFromStart, bOnProjection) = curve.ProjectPoint(point);
   TRY_TESTME(p == WBFL::Geometry::Point2d(501.775293, 999.92110));
   TRY_TESTME(IsEqual(distFromStart, 8.8825419271125750));
   TRY_TESTME(bOnProjection == false);

   point.Move(1000, 1300);
   std::tie(p, distFromStart, bOnProjection) = curve.ProjectPoint(point);
   TRY_TESTME(p == WBFL::Geometry::Point2d(760.585055, 922.304487));
   TRY_TESTME(IsEqual(distFromStart, 282.48097189865649));
   TRY_TESTME(bOnProjection == false);

   point.Move(550, 700);
   std::tie(p, distFromStart, bOnProjection) = curve.ProjectPoint(point);
   TRY_TESTME(p == WBFL::Geometry::Point2d(630.173602, 980.784875));
   TRY_TESTME(IsEqual(distFromStart, 139.06644242357913));
   TRY_TESTME(bOnProjection == false);

   point.Move(900, 900);
   std::tie(p, distFromStart, bOnProjection) = curve.ProjectPoint(point);
   TRY_TESTME(p == WBFL::Geometry::Point2d(850, 850));
   TRY_TESTME(IsEqual(distFromStart, 397.72433486814077));
   TRY_TESTME(bOnProjection == true);

   point.Move(800, 800);
   std::tie(p, distFromStart, bOnProjection) = curve.ProjectPoint(point);
   TRY_TESTME(p == WBFL::Geometry::Point2d(850, 850));
   TRY_TESTME(IsEqual(distFromStart, 397.72433486814077));
   TRY_TESTME(bOnProjection == true);

   point.Move(1100, 500);
   std::tie(p, distFromStart, bOnProjection) = curve.ProjectPoint(point);
   TRY_TESTME(p == WBFL::Geometry::Point2d(1150, 550));
   TRY_TESTME(IsEqual(distFromStart, 821.98840358006942));
   TRY_TESTME(bOnProjection == true);

   point.Move(1200, 600);
   std::tie(p, distFromStart, bOnProjection) = curve.ProjectPoint(point);
   TRY_TESTME(p == WBFL::Geometry::Point2d(1150, 550));
   TRY_TESTME(IsEqual(distFromStart, 821.98840358006942));
   TRY_TESTME(bOnProjection == true);

   TESTME_EPILOG("CircularCurve");
}
#endif // _UNITTEST
