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
#include <CoordGeom/CoordGeomTypes.h>
#include <CoordGeom/CompoundCurve.h>
#include <CoordGeom/CircularCurve.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/XCoordGeom.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/CubicSpline.h>

#include <GeomModel/GeomOp2d.h>
#include <GeomModel/Circle2d.h>

static Float64 tolerance = 0.1;

#define BACK_TANGENT    0x0001
#define ENTRY_SPIRAL    0x0002
#define CIRCULAR_CURVE  0x0004
#define EXIT_SPIRAL     0x0008
#define FORWARD_TANGENT 0x0010

using namespace WBFL::COGO;

std::shared_ptr<CompoundCurve> CompoundCurve::Create()
{
   return std::shared_ptr<CompoundCurve>(new CompoundCurve());
}

std::shared_ptr<CompoundCurve> CompoundCurve::Create(const WBFL::Geometry::Point2d& pbt, const WBFL::Geometry::Point2d& pi, const WBFL::Geometry::Point2d& pft, Float64 radius, Float64 lsEntry, TransitionCurveType lsEntryType, Float64 lsExit, TransitionCurveType lsExitType)
{
   return std::shared_ptr<CompoundCurve>(new CompoundCurve(pbt, pi, pft, radius, lsEntry, lsEntryType, lsExit, lsExitType));
}

std::shared_ptr<CompoundCurve> CompoundCurve::Create(const CompoundCurve& curve)
{
   return std::shared_ptr<CompoundCurve>(new CompoundCurve(curve));
}


CompoundCurve::CompoundCurve()
{
   m_PBT.Move(-1000, 0);
   m_PI.Move(0, 0);
   m_PFT.Move(1000, 1000);
   m_Radius = 1000;
   m_LsEntry = 0.0;
   m_LsEntryType = TransitionCurveType::Clothoid;
   m_LsExit = 0.0;
   m_LsExitType = TransitionCurveType::Clothoid;
}

CompoundCurve::CompoundCurve(const WBFL::Geometry::Point2d& pbt, const WBFL::Geometry::Point2d& pi, const WBFL::Geometry::Point2d& pft, Float64 radius,Float64 lsEntry,TransitionCurveType lsEntryType,Float64 lsExit,TransitionCurveType lsExitType) :
   m_PBT(pbt), m_PI(pi), m_PFT(pft), m_Radius(radius), m_LsEntry(lsEntry), m_LsEntryType(lsEntryType), m_LsExit(lsExit), m_LsExitType(lsExitType)
{
}


void CompoundCurve::SetPBT(const WBFL::Geometry::Point2d& pbt)
{
   m_PBT = pbt;
   OnPathElementChanged();
}

const WBFL::Geometry::Point2d& CompoundCurve::GetPBT() const
{
   return m_PBT;
}

void CompoundCurve::SetPI(const WBFL::Geometry::Point2d& pi)
{
   m_PI = pi;
   OnPathElementChanged();
}

const WBFL::Geometry::Point2d& CompoundCurve::GetPI() const
{
   return m_PI;
}

void CompoundCurve::SetPFT(const WBFL::Geometry::Point2d& pft)
{
   m_PFT = pft;
   OnPathElementChanged();
}

const WBFL::Geometry::Point2d& CompoundCurve::GetPFT() const
{
   return m_PFT;
}

void CompoundCurve::SetRadius(Float64 radius)
{
   PRECONDITION(0 < radius);
   m_Radius = radius;
   OnPathElementChanged();
}

Float64 CompoundCurve::GetRadius() const
{
   return m_Radius;
}

void CompoundCurve::SetSpiralType(SpiralLocation location, TransitionCurveType type)
{
   if (location == SpiralLocation::Entry)
      m_LsEntryType = type;
   else
      m_LsExitType = type;

   OnPathElementChanged();
}

TransitionCurveType CompoundCurve::GetSpiralType(SpiralLocation location) const
{
   return (location == SpiralLocation::Entry ? m_LsEntryType : m_LsExitType);
}

void CompoundCurve::SetSpiralLength(SpiralLocation location, Float64 Ls)
{
   PRECONDITION(0 <= Ls);

   if (location == SpiralLocation::Entry)
      m_LsEntry = Ls;
   else
      m_LsExit = Ls;

   OnPathElementChanged();
}

Float64 CompoundCurve::GetSpiralLength(SpiralLocation location) const
{
   return (location == SpiralLocation::Entry ? m_LsEntry : m_LsExit);
}

void CompoundCurve::Offset(Float64 dx, Float64 dy)
{
   m_PBT.Offset(dx, dy);
   m_PI.Offset(dx, dy);
   m_PFT.Offset(dx, dy);
   OnPathElementChanged();
}

CurveDirection CompoundCurve::GetCurveDirection() const
{
   auto bkTangentBearing = GetBackTangentBearing();
   auto fwdTangentBearing = GetForwardTangentBearing();

   auto angle = fwdTangentBearing.AngleBetween(bkTangentBearing);
   return (M_PI < angle.GetValue() ? CurveDirection::Right : CurveDirection::Left);
}

Angle CompoundCurve::GetSpiralAngle(SpiralLocation location) const
{
   Float64 Ls = GetSpiralLength(location);
   Float64 angle = Ls / (2 * m_Radius);
   return angle;
}

Angle CompoundCurve::GetCircularCurveAngle() const
{
   auto totalAngle = GetCurveAngle();
   auto entryAngle = GetSpiralAngle(SpiralLocation::Entry);
   auto exitAngle = GetSpiralAngle(SpiralLocation::Exit);

   Float64 angle = totalAngle - entryAngle - exitAngle;
   if (angle < 0) THROW_COGO(WBFL_COGO_E_SPIRALSOVERLAP);

#if defined _DEBUG
   // Back check angle by alternative means
   Float64 chord = GetChord();
   Float64 val = 2.0 * asin(chord / (2 * m_Radius));
   CHECK(IsEqual(val, angle, 0.001));
#endif // _DEBUG

   return angle;
}

Angle CompoundCurve::GetCurveAngle() const
{
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

Float64 CompoundCurve::GetX(SpiralLocation location) const
{
   return SpiralX(GetSpiralLength(location), GetSpiralAngle(location));
}

Float64 CompoundCurve::GetY(SpiralLocation location) const
{
   return SpiralY(GetSpiralLength(location), GetSpiralAngle(location));
}

Float64 CompoundCurve::GetQ(SpiralLocation location) const
{
   auto angle = GetSpiralAngle(location);
   auto y = GetY(location);
   auto q = y - m_Radius*(1.0 - cos(angle));
   return q;
}

Float64 CompoundCurve::GetT(SpiralLocation location) const
{
   auto angle = GetSpiralAngle(location);
   auto x = GetX(location);
   auto t = x - m_Radius * sin(angle);
   return t;
}

Direction CompoundCurve::GetForwardTangentBearing() const
{
   return COGO::MeasureDirection(m_PI, m_PFT);
}

Direction CompoundCurve::GetBackTangentBearing() const
{
   return COGO::MeasureDirection(m_PBT, m_PI);
}

Float64 CompoundCurve::GetForwardTangentLength() const
{
   Float64 T = 0;
   if (IsZero(m_LsEntry) && IsZero(m_LsExit))
   {
      //  No spirals
      auto angle = GetCurveAngle();
      T = m_Radius * tan(angle / 2);
   }
   else if (!IsZero(m_LsEntry) && IsZero(m_LsExit))
   {
      // Entry Spiral Only
      auto angle = GetCurveAngle();
      auto Q1 = GetQ(SpiralLocation::Entry);
      T = (m_Radius + Q1 - m_Radius * cos(angle)) / sin(angle);
   }
   else if (IsZero(m_LsEntry) && !IsZero(m_LsExit))
   {
      // Exit Spiral Only
      auto angle = GetCurveAngle();
      auto K2 = GetT(SpiralLocation::Exit);
      auto Q2 = GetQ(SpiralLocation::Exit);
      T = (m_Radius - (m_Radius + Q2) * cos(angle)) / sin(angle) + K2;
   }
   else
   {
      // Entry and Exit Spirals
      auto angle = GetCurveAngle();
      auto K2 = GetT(SpiralLocation::Exit);
      auto Q1 = GetQ(SpiralLocation::Entry);
      auto Q2 = GetQ(SpiralLocation::Exit);

      Float64 M = fabs((Q1 - Q2)) / sin(angle);

      Float64 sign = (Q2 < Q1) ? 1 : -1;

      T = K2 + (m_Radius + Q2) * tan(angle / 2) + sign * M;
   }

   return T;
}

Float64 CompoundCurve::GetBackTangentLength() const
{
   Float64 T = 0;
   if (IsZero(m_LsEntry) && IsZero(m_LsExit))
   {
      //  No spirals
      auto angle = GetCurveAngle();
      T = m_Radius * tan(angle / 2);
   }
   else if (!IsZero(m_LsEntry) && IsZero(m_LsExit))
   {
      // Entry Spiral Only
      auto angle = GetCurveAngle();
      auto K1 = GetT(SpiralLocation::Entry);
      auto Q1 = GetQ(SpiralLocation::Entry);
      T = (m_Radius - (m_Radius + Q1) * cos(angle)) / sin(angle) + K1;
   }
   else if (IsZero(m_LsEntry) && !IsZero(m_LsExit))
   {
      // Exit Spiral Only
      auto angle = GetCurveAngle();
      auto Q2 = GetQ(SpiralLocation::Exit);
      T = (m_Radius + Q2 - m_Radius * cos(angle)) / sin(angle);
   }
   else
   {
      // Entry and Exit Spirals
      auto angle = GetCurveAngle();
      auto K1 = GetT(SpiralLocation::Entry);
      auto Q1 = GetQ(SpiralLocation::Entry);
      auto Q2 = GetQ(SpiralLocation::Exit);

      Float64 M = fabs((Q1 - Q2)) / sin(angle);

      Float64 sign = (Q2 < Q1) ? -1 : 1;

      T = K1 + (m_Radius + Q1) * tan(angle / 2) + sign * M;
   }

   return T;
}

Direction CompoundCurve::GetCurveForwardTangentBearing() const
{
   if (IsZero(m_LsExit))
   {
      // No Exit Spiral
      return GetForwardTangentBearing();
   }
   else
   {
      // Exit Spiral
      auto CS = GetCS();
      auto SPI = GetSPI(SpiralLocation::Exit);
      return COGO::MeasureDirection(CS, SPI);
   }
}

Direction CompoundCurve::GetCurveBackTangentBearing() const
{
   Direction d;
   if (IsZero(m_LsEntry))
   {
      // No Entry Spiral
      d = GetBackTangentBearing();
   }
   else
   {
      // Entry Spiral
      auto SPI = GetSPI(SpiralLocation::Entry);
      auto SC = GetSC();

      d = COGO::MeasureDirection(SPI, SC);
   }
   return d;
}

WBFL::Geometry::Point2d CompoundCurve::GetCCC() const
{
   // Get Bk and Fwd Tangent Bearings of the circular curve
   auto bkBrg = GetCurveBackTangentBearing();
   auto fwdBrg = GetCurveForwardTangentBearing();

   // Create a line normal to the bk tangent brg

   // vector in the direction of the line
   auto bkNormal = bkBrg + PI_OVER_2; // add 90 deg to get the normal
   WBFL::Geometry::Vector2d v1(1.0, bkNormal);

   // point on the line
   auto SC = GetSC();
   WBFL::Geometry::Line2d l1(SC, v1);

   // Create a line normal to the fwd tangent brg

   // vector in the direction of the line
   auto fwdNormal = fwdBrg + PI_OVER_2; // add 90 deg to get the normal
   WBFL::Geometry::Vector2d v2(1.0, fwdNormal);

   // point on the line
   auto CS = GetCS();
   WBFL::Geometry::Line2d l2(CS, v2);

   // Intersect the 2 lines
   WBFL::Geometry::Point2d p;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(l1, l2, &p);
   CHECK(nIntersections == 1);
   return p;
}

WBFL::Geometry::Point2d CompoundCurve::GetPCI() const
{
   // Get Bk and Fwd Tangent Bearings of the circular curve
   auto bkBrg = GetCurveBackTangentBearing();
   auto fwdBrg = GetCurveForwardTangentBearing();

   // Create a line in the direction of the bk tangent brg

   // vector in the direction of the line
   WBFL::Geometry::Vector2d v1(1.0, bkBrg);

   // point on the line
   auto spi1 = GetSPI(SpiralLocation::Entry);

   WBFL::Geometry::Line2d l1(spi1, v1);

   // Create a line in the direction of the fwd tangent brg

   // vector in the direction of the line
   WBFL::Geometry::Vector2d v2(1.0, fwdBrg);

   // point on the line
   auto spi2 = GetSPI(SpiralLocation::Exit);

   WBFL::Geometry::Line2d l2(spi2, v2);

   // Intersect the 2 lines
   WBFL::Geometry::Point2d p;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(l1, l2, &p);
   CHECK(nIntersections == 1);
   return p;
}

WBFL::Geometry::Point2d CompoundCurve::GetSPI(SpiralLocation location) const
{
   WBFL::Geometry::Point2d SPI;

   Float64 U = GetLongTangent(location);
   Float64 X, Y;
   X = U;
   Y = 0;

   if (location == SpiralLocation::Entry)
   {
      // Setup a coordinate system at TS, with positive X going from TS to PI.
      // SC will be at point (X,-Y) in this coordinate system
      // Transform SC into the global coordinate system
      auto TS = GetTS();

      auto direction = COGO::MeasureDirection(TS, m_PI);

      SPI.Move(X, -Y);
      SPI = WBFL::Geometry::GeometricOperations::LocalToGlobal(TS, direction, SPI);
   }
   else
   {
      // Setup a coordinate system at ST, with positive X going from ST to PI
      // CS will be at point (X,Y) in this coordinate system
      // Transform CS into the global coordinate system
      auto ST = GetST();

      auto direction = COGO::MeasureDirection(ST, m_PI);

      SPI.Move(X, Y);
      SPI = WBFL::Geometry::GeometricOperations::LocalToGlobal(ST, direction, SPI);
   }

   return SPI;
}

WBFL::Geometry::Point2d CompoundCurve::GetCC() const
{
   auto TS = GetTS();
   auto ST = GetST();

   if (m_PI == TS || m_PI == ST)
   {
      // this curve is really just a point... CC is going to be at the same location
      // creating lines t1 and t2 will fail below.... just you the PI and the CC and return
      return m_PI;
   }

   WBFL::Geometry::Line2d t1(m_PI, TS); // bk tangent (reversed)
   WBFL::Geometry::Line2d t2(m_PI, ST); // fwd tangent (reversed)

   auto n1 = WBFL::Geometry::GeometricOperations::CreateNormalLineThroughPoint(t1, TS);
   auto n2 = WBFL::Geometry::GeometricOperations::CreateNormalLineThroughPoint(t2, ST);

   WBFL::Geometry::Point2d p;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(n1, n2, &p);
   CHECK(nIntersections == 1);

#if defined _DEBUG
   // intersect tangents... should intersect at PI
   WBFL::Geometry::Point2d testPoint;
   auto result = WBFL::Geometry::GeometricOperations::Intersect(t1, t2, &testPoint);
   CHECK(result == 1);
   CHECK(testPoint == m_PI);

   // intersect forward tangent and its normal
   // should intersect at TS
   result = WBFL::Geometry::GeometricOperations::Intersect(t1, n1, &testPoint);
   CHECK(result == 1);
   CHECK(testPoint == TS);

   // intersect back tangent and its normal
   // should intersect at ST
   result = WBFL::Geometry::GeometricOperations::Intersect(t2, n2, &testPoint);
   CHECK(result == 1);
   CHECK(testPoint == ST);
#endif // _DEBUG

   return p;
}

WBFL::Geometry::Point2d CompoundCurve::GetSC() const
{
   auto X = GetX(SpiralLocation::Entry);
   auto Y = GetY(SpiralLocation::Entry);

   return PointOnEntrySpiral(X, Y);
}

WBFL::Geometry::Point2d CompoundCurve::GetCS() const
{
   auto X = GetX(SpiralLocation::Exit);
   auto Y = GetY(SpiralLocation::Exit);

   return PointOnExitSpiral(X, Y);
}

WBFL::Geometry::Point2d CompoundCurve::GetTS() const
{
   auto bkTanBrg = GetBackTangentBearing();
   bkTanBrg.Increment(M_PI); // reverse bearing PI to PBT

   auto T = GetBackTangentLength();

   auto pnt = COGO::LocateByDistanceAndDirection(m_PI, T, bkTanBrg, 0.0);

   return pnt;
}

WBFL::Geometry::Point2d CompoundCurve::GetST() const
{
   auto fwdTanBrg = GetForwardTangentBearing();
   auto T = GetForwardTangentLength();

   auto pnt = COGO::LocateByDistanceAndDirection(m_PI, T, fwdTanBrg, 0.0);

   return pnt;
}

Float64 CompoundCurve::GetChord() const
{
   auto SC = GetSC();
   auto CS = GetCS();
   return SC.Distance(CS);
}

Float64 CompoundCurve::GetTangent() const
{
   auto angle = GetCircularCurveAngle();
   auto T = m_Radius * tan(angle / 2);
   return T;
}

Float64 CompoundCurve::GetMidOrdinate() const
{
   auto angle = GetCircularCurveAngle();
   auto MO = m_Radius * (1 - cos(angle / 2));
   return MO;
}

Float64 CompoundCurve::GetExternal() const
{
   auto angle = GetCircularCurveAngle();
   auto E = m_Radius * (1 / cos(angle / 2) - 1);
   return E;
}

Angle CompoundCurve::GetDE(SpiralLocation location) const
{
   // Deviation angle of spiral measured from back tangent (or forward tangent)
   // to tangent through the spiral at its maximum degree
   return GetSpiralAngle(location);
}

Angle CompoundCurve::GetDH(SpiralLocation location) const
{
   WBFL::Geometry::Point2d from, vertex, to;

   auto direction = GetCurveDirection();

   if (location == SpiralLocation::Entry)
   {
      if (direction == CurveDirection::Right)
      {
         from = GetSPI(SpiralLocation::Entry);
         vertex = GetSC();
         to = GetTS();
      }
      else
      {
         from = GetTS();
         vertex = GetSC();
         to = GetSPI(SpiralLocation::Entry);
      }
   }
   else
   {
      if (direction == CurveDirection::Right)
      {
         from = GetST();
         vertex = GetCS();
         to = GetSPI(SpiralLocation::Exit);
      }
      else
      {
         from = GetSPI(SpiralLocation::Exit);
         vertex = GetCS();
         to = GetST();
      }
   }

   WBFL::COGO::Angle angle;
   try
   {
      angle = COGO::MeasureAngle(from, vertex, to);
   }
   catch(...)
   {
      // 3 points are the same. This occurs when the spiral lengths are zero
      angle = 0.0;
   }

   return angle;
}

Angle CompoundCurve::GetDF(SpiralLocation location) const
{
   WBFL::Geometry::Point2d from, vertex, to;

   auto direction = GetCurveDirection();

   if (location == SpiralLocation::Entry)
   {
      if (direction == CurveDirection::Right)
      {
         from = GetSC();
         vertex = GetTS();
         to = GetSPI(SpiralLocation::Entry);
      }
      else
      {
         from = GetSPI(SpiralLocation::Entry);
         vertex = GetTS();
         to = GetSC();
      }
   }
   else
   {
      if (direction == CurveDirection::Right)
      {
         from = GetSPI(SpiralLocation::Exit);
         vertex = GetST();
         to = GetCS();
      }
      else
      {
         from = GetCS();
         vertex = GetST();
         to = GetSPI(SpiralLocation::Exit);
      }
   }

   WBFL::COGO::Angle angle;
   try
   {
      angle = COGO::MeasureAngle(from, vertex, to);
   }
   catch (...)
   {
      // 3 points are the same. This occurs when the spiral lengths are zero
      angle = 0.0;
   }

   return angle;
}

Float64 CompoundCurve::GetShortTangent(SpiralLocation location) const
{
   // If the length is zero, V is zero
   Float64 Ls = GetSpiralLength(location);
   if (IsZero(Ls))
   {
      return 0.0;
   }

   auto X = GetX(location);
   auto Y = GetY(location);

   auto DE = GetDE(location);

   Float64 v = Y / sin(DE);
   return v;
}

Float64 CompoundCurve::GetLongTangent(SpiralLocation location) const
{
   // If the length is zero, U is zero
   Float64 Ls = GetSpiralLength(location);
   if (IsZero(Ls))
   {
      return 0.0;
   }

   auto X = GetX(location);
   auto Y = GetY(location);

   auto DE = GetDE(location);

   Float64 u = X - Y / tan(DE);
   return u;
}

Float64 CompoundCurve::GetSpiralChord(SpiralLocation location) const
{
   auto start = (location == SpiralLocation::Entry ? GetTS() : GetST());
   auto end = (location == SpiralLocation::Entry ? GetSC() : GetCS());
   return start.Distance(end);
}

Float64 CompoundCurve::GetTotalLength() const
{
   auto L = GetCurveLength();
   return m_LsEntry + L + m_LsExit;
}

Float64 CompoundCurve::GetCurveLength() const
{
   auto angle = GetCircularCurveAngle();
   return m_Radius * angle;
}

Angle CompoundCurve::GetDegreeOfCurvature(const Angle& delta, DegreeCurvature type) const
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

WBFL::Geometry::Point2d CompoundCurve::PointOnCurve(Float64 distFromStart) const
{
   Float64 Lc = GetCurveLength(); // Length of circular curve
   Float64 Lt = GetTotalLength(); // Total length of curve

   if (distFromStart <= 0)
   {
      // Before curve
      auto bkTanBrg = GetBackTangentBearing();
      auto TS = GetTS();
      return COGO::LocateByDistanceAndDirection(TS, distFromStart, bkTanBrg, 0.0);
   }
   else if (Lt <= distFromStart)
   {
      // After curve
      auto fwdTanBrg = GetForwardTangentBearing();
      auto ST = GetST();
      return COGO::LocateByDistanceAndDirection(ST, distFromStart - Lt, fwdTanBrg, 0.0);
   }
   else
   {
      auto dir = GetCurveDirection();

      Float64 sign = (dir == CurveDirection::Left ? 1 : -1);

      // On curve
      if (distFromStart <= m_LsEntry)
      {
         // On entry spiral
         return PointOnEntrySpiral(distFromStart);
      }
      else if (m_LsEntry < distFromStart && distFromStart <= (m_LsEntry + Lc))
      {
         // On circular curve
         Float64 ls = distFromStart - m_LsEntry; // arc length from start of circular curve

         Float64 sweepAngle = sign * ls / m_Radius;

         // start of circular curve
         auto SC = GetSC();

         // center of circular curve
         auto CCC = GetCCC();

         SC.Rotate(CCC,sweepAngle);

         return SC;
      }
      else
      {
         // On exit spiral
         Float64 ls = Lt - distFromStart; // arc length measured from the end of the curve
         return PointOnExitSpiral(ls);
      }
   }
}

std::vector<WBFL::Geometry::Point2d> CompoundCurve::Divide(IndexType nParts) const
{
   PRECONDITION(0 < nParts);

   std::vector<WBFL::Geometry::Point2d> points;
   auto total_length = GetTotalLength();
   auto step = total_length / nParts;

   auto nPoints = nParts + 1;
   for (IndexType i = 0; i < nPoints; i++)
   {
      Float64 dist_from_start = i * step;
      points.push_back(PointOnCurve(dist_from_start));
   }

   return points;
}

//
// PathElement methods
//
std::shared_ptr<PathElement> CompoundCurve::Clone() const
{
   return std::shared_ptr<CompoundCurve>(new CompoundCurve(*this));
}

const WBFL::Geometry::Point2d& CompoundCurve::GetStartPoint() const
{
   m_TS = GetTS();
   return m_TS;
}

const WBFL::Geometry::Point2d& CompoundCurve::GetEndPoint() const
{
   m_ST = GetST();
   return m_ST;
}

void CompoundCurve::Move(Float64 distance, const Direction& direction)
{
   WBFL::Geometry::Vector2d v(distance, direction);
   m_PBT.Offset(v.GetSize());
   m_PI.Offset(v.GetSize());
   m_PFT.Offset(v.GetSize());
   OnPathElementChanged();
}

Float64 CompoundCurve::GetLength() const
{
   return GetTotalLength();
}

std::vector<WBFL::Geometry::Point2d> CompoundCurve::GetKeyPoints() const
{
   std::vector<WBFL::Geometry::Point2d> vPoints{ GetTS(),GetSC(),GetCS(),GetST() };
   return vPoints;
}

WBFL::Geometry::Point2d CompoundCurve::LocatePoint(Float64 distFromStart, OffsetType offsetType, Float64 offset, const Direction& direction) const
{
   offset = PathElement::AdjustOffset(distFromStart, offsetType, offset, direction); // offset is now along direction
   auto point = PointOnCurve(distFromStart);
   if (!IsZero(offset))
   {

      point = COGO::LocateByDistanceAndDirection(point, offset, direction, 0.0);
   }

   return point;
}

Direction CompoundCurve::GetBearing(Float64 distFromStart) const
{
   Float64 Lc = GetCurveLength(); // Length of circular curve
   Float64 Lt = GetTotalLength(); // Total length of curve

   if (distFromStart <= 0)
   {
      // Before curve
      return GetBackTangentBearing();
   }
   else if (Lt <= distFromStart)
   {
      // After curve
      return GetForwardTangentBearing();
   }
   else
   {
      auto dir = GetCurveDirection();

      Float64 sign = (dir == CurveDirection::Left ? 1 : -1);

      // On curve
      if (distFromStart <= m_LsEntry)
      {
         // On entry spiral
         Float64 La = distFromStart; // arc length

         auto angle = GetSpiralAngle(SpiralLocation::Entry);

         Float64 sweepAngle = pow(La / m_LsEntry, 2) * sign * angle;

         auto bearing = GetBackTangentBearing();
         bearing.Increment(sweepAngle);
         return bearing;
      }
      else if (m_LsEntry < distFromStart && distFromStart <= (m_LsEntry + Lc))
      {
         // On circular curve
         Float64 La = distFromStart - m_LsEntry; // arc length

         Float64 sweepAngle = sign * La / m_Radius;

         auto bearing = GetCurveBackTangentBearing();
         bearing.Increment(sweepAngle);
         return bearing;
      }
      else
      {
         // On exit spiral
         Float64 La = Lt - distFromStart; // arc length measured from the end of the curve

         auto angle = GetSpiralAngle(SpiralLocation::Exit);

         // sweep angle measured from the end of the curve
         Float64 sweepAngle = sign * pow(La / m_LsExit, 2) * angle;

         auto bearing = GetForwardTangentBearing();
         bearing.Increment(-sweepAngle);
         return bearing;
      }
   }
}

std::tuple<WBFL::Geometry::Point2d, Float64, bool> CompoundCurve::ProjectPoint(const WBFL::Geometry::Point2d& point) const
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
      auto TS = GetTS();
      bkTangentDistance = TS.Distance(*bkTangentPoint);
      bkTangentDistance *= -1;

      // deal with the case when the point is exactly at the start of the curve
      bkTangentDistance = IsZero(bkTangentDistance, 1e-9) ? 0.0 : bkTangentDistance;
   }

   std::unique_ptr<WBFL::Geometry::Point2d> entrySpiralPoint;
   Float64 entrySpiralOffset;
   Float64 entrySpiralDistance;
   if (projection_region & ENTRY_SPIRAL)
   {
      WBFL::Geometry::Point2d p;
      std::tie(entrySpiralDistance,p) = ProjectPointOnEntrySpiral(point);
      entrySpiralPoint = std::make_unique<WBFL::Geometry::Point2d>(p);
      entrySpiralOffset = point.Distance(*entrySpiralPoint); // distance from the point to where it projects onto the entry spiral
   }

   std::unique_ptr<WBFL::Geometry::Point2d> curvePoint;
   Float64 curveOffset;
   Float64 curveDistance;
   if (projection_region & CIRCULAR_CURVE)
   {
      // Create a line from CCC through the projected point
      // Intersect this line with the circular arc, finding the
      // point that is nearest SC.
      auto ccc = GetCCC();

      WBFL::Geometry::Line2d line(ccc, point);
      WBFL::Geometry::Circle2d circle(ccc, m_Radius);

      auto sc = GetSC();

      curvePoint = std::make_unique<WBFL::Geometry::Point2d>(COGO::IntersectLineAndCircle(line, circle, point));

      auto dir = GetCurveDirection();
      Float64 angle;
      if (dir == CurveDirection::Right)
         angle = WBFL::Geometry::GeometricOperations::Angle(*curvePoint, ccc, sc);
      else
         angle = WBFL::Geometry::GeometricOperations::Angle(sc, ccc, *curvePoint);

#if defined _DEBUG
      // The subtended angle must be less than or equal to the
      // circular curve angle (or the point isn't on the circular part of the curve)
      CHECK(IsLE(angle, GetCircularCurveAngle().GetValue()));
#endif // _DEBUG

      CHECK(0 <= angle);
      Float64 dist = m_Radius * angle; // distance along circular curve to projected point
      Float64 Ls = GetSpiralLength(SpiralLocation::Entry);
      curveDistance = Ls + dist;

      curveOffset = point.Distance(*curvePoint); // distance from the point to where it projects onto the circular curve
   }

   std::unique_ptr<WBFL::Geometry::Point2d> exitSpiralPoint;
   Float64 exitSpiralOffset;
   Float64 exitSpiralDistance;
   if (projection_region & EXIT_SPIRAL)
   {
      WBFL::Geometry::Point2d p;
      std::tie(exitSpiralDistance,p) = ProjectPointOnExitSpiral(point);
      exitSpiralPoint = std::make_unique<WBFL::Geometry::Point2d>(p);
      exitSpiralOffset = point.Distance(*exitSpiralPoint); // distance from the point to where it projects onto the exit spiral
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
      auto pft = GetPFT();

      WBFL::Geometry::Line2d line(pi, pft);

      fwdTangentPoint = std::make_unique<WBFL::Geometry::Point2d>(WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, point));
      fwdTangentOffset = point.Distance(*fwdTangentPoint); // distance from the point to where it projects onto the forward tangent

      // compute distance along the forward tangent to the projection point
      auto st = GetST();
      fwdTangentDistance = st.Distance(*fwdTangentPoint);

      Float64 Lt = GetTotalLength(); // Total length of curve

      // deal with case when point is exactly at the end of the curve
      if (IsZero(fwdTangentDistance))
         fwdTangentDistance = Lt;
      else
         fwdTangentDistance += Lt;
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

   if (entrySpiralPoint && entrySpiralOffset < min_offset)
   {
      min_offset = entrySpiralOffset;
      newPoint = *entrySpiralPoint;
      distFromStart = entrySpiralDistance;
      bOnProjection = false;
   }

   if (curvePoint && curveOffset < min_offset)
   {
      min_offset = curveOffset;
      newPoint = *curvePoint;
      distFromStart = curveDistance;
      bOnProjection = false;
   }

   if (exitSpiralPoint && exitSpiralOffset < min_offset)
   {
      min_offset = exitSpiralOffset;
      newPoint = *exitSpiralPoint;
      distFromStart = exitSpiralDistance;
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

std::vector<WBFL::Geometry::Point2d> CompoundCurve::Intersect(const WBFL::Geometry::Line2d& line, bool bProjectBack, bool bProjectAhead) const
{
   std::vector<WBFL::Geometry::Point2d> vPoints;

   //
   // First check to see if the line intersects the circular curve
   ///

   // get the key circular curve points
   auto SC = GetSC();
   auto CS = GetCS();
   auto CCC = GetCCC();
   auto PI = GetPI();
   auto TS = GetTS();
   auto ST = GetST();

   WBFL::Geometry::Circle2d circle(CCC, m_Radius);

   WBFL::Geometry::Point2d pnt1, pnt2;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line, circle, &pnt1, &pnt2);

   auto direction = GetCurveDirection();

   Float64 delta;
   if (direction == CurveDirection::Left)
      delta = WBFL::Geometry::GeometricOperations::Angle(SC, CCC, CS);
   else
      delta = WBFL::Geometry::GeometricOperations::Angle(CS, CCC, SC);

#if defined _DEBUG
   CHECK(IsEqual(delta, GetCircularCurveAngle().GetValue()));
#endif

   std::unique_ptr<WBFL::Geometry::Point2d> pntCurve1, pntCurve2;
   if (1 <= nIntersections)
   {
      Float64 angle;
      if (direction == CurveDirection::Left)
         angle = WBFL::Geometry::GeometricOperations::Angle(SC, CCC, pnt1);
      else
         angle = WBFL::Geometry::GeometricOperations::Angle(pnt1, CCC, SC);

      if (0 <= angle && angle <= delta)
         pntCurve1 = std::make_unique<WBFL::Geometry::Point2d>(pnt1);
   }

   if (nIntersections == 2)
   {
      Float64 angle;
      if (direction == CurveDirection::Left)
         angle = WBFL::Geometry::GeometricOperations::Angle(SC, CCC, pnt2);
      else
         angle = WBFL::Geometry::GeometricOperations::Angle(pnt2, CCC, SC);

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
      auto dist1 = TS.Distance(*pntCurve1);
      auto dist2 = TS.Distance(*pntCurve2);
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

      // Check if it intersects the entry spiral
      std::unique_ptr<WBFL::Geometry::Point2d> pntEntrySpiral;
      if (0 < m_LsEntry)
      {
         // when evaluated, this function returns the distance from the line to the curve
         // if the curve is to the left of the line the distance is negative
         CLineIntersectFunction function(this, line);
         WBFL::Math::BrentsRootFinder rootFinder;
         Float64 ya = function.Evaluate(0);
         Float64 yb = function.Evaluate(m_LsEntry);
         if (0 < ya * yb)
         {
            // The end points don't bracket the solution....
            // Either the line doesn't intersect the spiral, it intersects it in two places
            // or it is tangent to the spiral

            // If the line intersects both the lines that are tangent to the spiral
            // then there is at least one intersection point
            auto SPI = GetSPI(SpiralLocation::Entry);
            WBFL::Geometry::LineSegment2d seg1(TS, SPI);

            WBFL::Geometry::Point2d pnt1;
            auto nIntersections1 = WBFL::Geometry::GeometricOperations::Intersect(line, seg1, &pnt1);

            WBFL::Geometry::Line2d seg2(SPI, SC);
            WBFL::Geometry::Point2d pnt2;
            auto nIntersections2 = WBFL::Geometry::GeometricOperations::Intersect(line, seg2, &pnt2);

            if (nIntersections1 == 1 && nIntersections2 == 1)
            {
               // need to find a distance along the curve that is between the two intersection points
               // so we have a bracket that works... to do this, search for a point on the spiral where
               // the tangent to the spiral is parallel to the line
               CParallelLineFunction parallel_function(this, line);
               Float64 limit;
               try
               {
                  limit = rootFinder.FindRootInRange(parallel_function, 0, m_LsEntry, 0.0000001);
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
                  return vPoints;// with tangency, there is only one solution so just leave now
               }
               else
               {
                  // Line is not tangent to the curve

                  // Figure out if the line is on the inside or outside of the curve. If on the outside, it doesn't intersect

                  // Compute Offset
                  auto brg = GetBearing(limit); // bearing at the projected point

                  WBFL::Geometry::Vector2d v(1.0, brg);

                  WBFL::Geometry::Line2d tangent_line(POC, v); // Line through the projected point, forward direction

                  auto normal_line = WBFL::Geometry::GeometricOperations::CreateNormalLineThroughPoint(tangent_line, POC);

                  WBFL::Geometry::Point2d point_on_line;
                  auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line, normal_line, &point_on_line);
                  CHECK(nIntersections == 1);

                  Float64 offset = tangent_line.DistanceToPoint(point_on_line);
                  CHECK(!IsZero(offset)); // if offset is zero, the line is tangent and we should have dealt with that above

                  // negative offset means point_on_line is to the left of tangent_line

                  if ((0 < offset && direction == CurveDirection::Left) || (offset < 0 && direction == CurveDirection::Right))
                  {
                     // line is on the inside of the curve so there are intersections
                     try
                     {
                        // get first intersection in first segment
                        Float64 dist1 = rootFinder.FindRootInRange(function, 0, limit, 0.0001);
                        vPoints.emplace_back(PointOnCurve(dist1));
                        CHECK(TestIntersection(line, vPoints.back()));

                        // get second intersection in second segment
                        Float64 dist2 = rootFinder.FindRootInRange(function, limit, m_LsEntry, 0.0001);
                        vPoints.emplace_back(PointOnCurve(dist2));
                        CHECK(TestIntersection(line, vPoints.back()));
                        CHECK(vPoints.size() == 2); // got both intersection points, return now
                        return vPoints;
                     }
                     catch (WBFL::Math::XRootFinder& /*mx*/)
                     {
                        CHECK(false); // should never fire
                     }
                  }
               }
            }
         }
         else
         {
            // find the single intersection point
            try
            {
               Float64 dist1 = rootFinder.FindRootInRange(function, 0, m_LsEntry, 0.0001);
               pntEntrySpiral = std::make_unique<WBFL::Geometry::Point2d>(PointOnCurve(dist1));
               CHECK(TestIntersection(line, *pntEntrySpiral));
            }
            catch (WBFL::Math::XRootFinder& /*mx*/)
            {
               CHECK(false);
            }
         }
      }


      // Check if it intersects the exit spiral
      std::unique_ptr<WBFL::Geometry::Point2d> pntExitSpiral;
      if (0 < m_LsExit)
      {
         // when evaluated, this function returns the distance from the line to the curve
         // if the curve is to the left of the line the distance is negative
         CLineIntersectFunction function(this, line);
         WBFL::Math::BrentsRootFinder rootFinder;
         Float64 length = GetTotalLength();
         Float64 ya = function.Evaluate(length - m_LsExit);
         Float64 yb = function.Evaluate(length);
         if (0 < ya * yb)
         {
            // The end points don't bracket the solution....
            // Either the line doesn't intersect the spiral, it intersects it in two places
            // or it is tangent to the spiral

            // If the line intersects both the lines that are tangent to the spiral
            // then there is at least one intersection point
            auto SPI = GetSPI(SpiralLocation::Exit);
            WBFL::Geometry::LineSegment2d seg1(ST, SPI);

            WBFL::Geometry::Point2d pnt1;
            auto nIntersections1 = WBFL::Geometry::GeometricOperations::Intersect(line, seg1, &pnt1);

            WBFL::Geometry::Line2d seg2(SPI, CS);
            WBFL::Geometry::Point2d pnt2;
            auto nIntersections2 = WBFL::Geometry::GeometricOperations::Intersect(line, seg2, &pnt2);

            if (nIntersections1 == 1 && nIntersections2 == 1)
            {
               // need to find a distance along the curve that is between the two intersection points
               // so we have a bracket that works... to do this, search for a point on the spiral where
               // the tangent to the spiral is parallel to the line
               CParallelLineFunction parallel_function(this, line);
               Float64 limit;
               try
               {
                  limit = rootFinder.FindRootInRange(parallel_function, length - m_LsExit, length, 0.0000001);
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
                  return vPoints;// with tangency, there is only one solution so just leave now
               }
               else
               {
                  // Line is not tangent to the curve

                  // Figure out if the line is on the inside or outside of the curve. If on the outside, it doesn't insersect

                  // Compute Offset
                  auto brg = GetBearing(limit);
                  WBFL::Geometry::Vector2d  v(1.0, brg);
                  WBFL::Geometry::Line2d tangent_line(POC, v); // Line through the projected point, forward direction

                  auto normal_line = WBFL::Geometry::GeometricOperations::CreateNormalLineThroughPoint(tangent_line, POC);

                  WBFL::Geometry::Point2d point_on_line;
                  auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line, normal_line, &point_on_line);
                  CHECK(nIntersections == 1);


                  Float64 offset = tangent_line.DistanceToPoint(point_on_line);
                  CHECK(!IsZero(offset)); // if offset is zero, the line is tangent and we should have dealt with that above

                  // negative offset means point_on_line is to the left of tangent_line

                  if ((0 < offset && direction == CurveDirection::Left) || (offset < 0 && direction == CurveDirection::Right))
                  {
                     // line is on the inside of the curve so there are intersections
                     try
                     {
                        // get first intersection in first segment
                        Float64 dist1 = rootFinder.FindRootInRange(function, length - m_LsExit, limit, 0.0001);
                        vPoints.emplace_back( PointOnCurve(dist1) );
                        CHECK(TestIntersection(line, vPoints.back()));

                        // get second intersection in second segment
                        Float64 dist2 = rootFinder.FindRootInRange(function, limit, length, 0.0001);
                        vPoints.emplace_back(PointOnCurve(dist2));
                        CHECK(TestIntersection(line, vPoints.back()));
                        CHECK(vPoints.size() == 2);// got both intersection points, return now
                        return vPoints;
                     }
                     catch (WBFL::Math::XRootFinder& /*mx*/)
                     {
                        CHECK(false); // should never fire
                     }
                  }
               }
            }
         }
         else
         {
            // find the single intersection point
            try
            {
               Float64 dist1 = rootFinder.FindRootInRange(function, length - m_LsExit, length, 0.0001);
               pntExitSpiral = std::make_unique<WBFL::Geometry::Point2d>(PointOnCurve(dist1));
               CHECK(TestIntersection(line, *pntExitSpiral));
            }
            catch (WBFL::Math::XRootFinder& /*mx*/)
            {
               CHECK(false);
            }
         }
      }

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
         if (bkTangentPoint && !COGO::IsPointBeforeStart(TS, PI, *bkTangentPoint))
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
         if (fwdTangentPoint && !COGO::IsPointAfterEnd(PI, ST, *fwdTangentPoint))
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

      if (pntEntrySpiral)
         nPoints++;

      if (pntExitSpiral)
         nPoints++;

      if (fwdTangentPoint)
         nPoints++;

      // This method assumes there is never more than 2 intersection points
      CHECK(nPoints <= 2);
#endif


      if (bkTangentPoint) vPoints.emplace_back(*bkTangentPoint);
      if (pntCurve1) vPoints.emplace_back(*pntCurve1);
      if (pntCurve2) vPoints.emplace_back(*pntCurve2);
      if (pntEntrySpiral) vPoints.emplace_back(*pntEntrySpiral);
      if (pntExitSpiral) vPoints.emplace_back(*pntExitSpiral);
      if (fwdTangentPoint) vPoints.emplace_back(*fwdTangentPoint);

#if defined _DEBUG
      CHECK(vPoints.size() == nPoints);
#endif
   }

   return vPoints;
}

std::vector<std::shared_ptr<PathElement>> CompoundCurve::CreateOffsetPath(Float64 offset) const
{
   std::vector<std::shared_ptr<PathElement>> vElements;

   auto curve_direction = GetCurveDirection();

   auto TS = GetTS();
   auto CC = GetCC();
   auto ST = GetST();

   auto d1 = TS.Distance(CC);
   auto d2 = ST.Distance(CC);

   // It is useful to have line objects that represent the tangents of the curve.
   // Create them now because they will be used later.
   const auto& PBT = GetPBT();
   const auto& PI = GetPI();
   const auto& PFT = GetPFT();

   WBFL::Geometry::Line2d l1(PBT, PI);
   WBFL::Geometry::Line2d l2(PI, PFT);

   // Deal with the case of the curve degrading to a single point
   if ((curve_direction == CurveDirection::Right && (d1 <= offset || d2 <= offset)) ||
      (curve_direction == CurveDirection::Left && (d1 <= -offset || d2 <= -offset)))
   {
      // The parallel curve is past the CC point... this degrades the curve to a point

      // offset the curve tangents and intersect them
      l1.Offset(-offset);
      l2.Offset(-offset);

      WBFL::Geometry::Point2d ip;
      auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(l1, l2, &ip);
      CHECK(nIntersections == 1);

      // model point as a zero length line segment
      auto path_element = PathSegment::Create(ip, ip);
      vElements.emplace_back(path_element);
   }
   else
   {
      //
      // Curve remains a curve
      //
      IndexType nPoints = 10;

      //
      // Entry spiral
      //
      Float64 LsEntry = GetSpiralLength(SpiralLocation::Entry);
      if (0 < LsEntry)
      {
         auto angle = GetSpiralAngle(SpiralLocation::Entry);
         if (PI_OVER_2 < angle)
         {
            // If the angle subtended by the spiral is more than 90deg, it is looping back on itself.
            // The cubic spline object can't handle that, so create two splines and join them into
            // a CompositePathElement object
            auto spline1 = CreateSubpathSpline(0.0, LsEntry / 2, nPoints);
            auto offset_spline1 = spline1->CreateOffsetPath(offset);
            for (auto& offset_spline_element : offset_spline1)
            {
               vElements.emplace_back(offset_spline_element);
            }

            auto spline2 = CreateSubpathSpline(LsEntry / 2, LsEntry, nPoints);
            auto offset_spline2 = spline2->CreateOffsetPath(offset);
            for (auto& offset_spline_element : offset_spline2)
            {
               vElements.emplace_back(offset_spline_element);
            }
         }
         else
         {
            auto spline = CreateSubpathSpline(0.0, LsEntry, nPoints);
            auto offset_spline = spline->CreateOffsetPath(offset);
            for (auto& offset_spline_element : offset_spline)
            {
               vElements.emplace_back(offset_spline_element);
            }
         }
      }

      //
      // Circular Curve
      //

      // Create lines parallel to the tangents of the circular curve. The intersection point of these lines is the new PI.
      auto SC = GetSC();
      auto PCI = GetPCI();
      auto CS = GetCS();

      l1.ThroughPoints(SC, PCI);
      l2.ThroughPoints(PCI, CS);


      auto bkTangent = WBFL::Geometry::GeometricOperations::CreateParallelLine(l1, offset);
      auto fwdTangent = WBFL::Geometry::GeometricOperations::CreateParallelLine(l2, offset);

      WBFL::Geometry::Point2d newPI;
      auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(bkTangent, fwdTangent, &newPI);
      CHECK(nIntersections == 1);

      auto newPBT = WBFL::Geometry::GeometricOperations::PointOnLineNearest(bkTangent, SC);
      auto newPFT = WBFL::Geometry::GeometricOperations::PointOnLineNearest(fwdTangent, CS);

      // compute new circular curve radius
      Float64 newRadius = (curve_direction == CurveDirection::Right ? m_Radius - offset : m_Radius + offset);
      auto offset_curve = CircularCurve::Create(newPBT, newPI, newPFT, newRadius);

#if defined _DEBUG
      CHECK(GetCCC() == offset_curve->GetCenter());
      CHECK(GetCircularCurveAngle() == offset_curve->GetAngle());
#endif

      vElements.emplace_back(offset_curve);

      //
      // Exit spiral
      //
      Float64 LsExit = GetSpiralLength(SpiralLocation::Exit);
      if (0 < LsExit)
      {
         Float64 L = GetCurveLength();

         auto angle = GetSpiralAngle(SpiralLocation::Exit);
         if (PI_OVER_2 < angle)
         {
            auto spline1 = CreateSubpathSpline(LsEntry + L, LsEntry + L + LsExit / 2, nPoints);
            auto offset_spline1 = spline1->CreateOffsetPath(offset);
            for (auto& offset_spline_element : offset_spline1)
            {
               vElements.emplace_back(offset_spline_element);
            }

            auto spline2 = CreateSubpathSpline(LsEntry + L + LsExit / 2, LsEntry + L + LsExit, nPoints);
            auto offset_spline2 = spline2->CreateOffsetPath(offset);
            for (auto& offset_spline_element : offset_spline2)
            {
               vElements.emplace_back(offset_spline_element);
            }
         }
         else
         {
            auto spline = CreateSubpathSpline(LsEntry + L, LsEntry + L + LsExit, nPoints);
            auto offset_spline = spline->CreateOffsetPath(offset);
            for (auto& offset_spline_element : offset_spline)
            {
               vElements.emplace_back(offset_spline_element);
            }
         }
      }
   }
   
   return vElements;
}

std::vector<std::shared_ptr<PathElement>> CompoundCurve::CreateSubpath(Float64 start, Float64 end) const
{
   std::vector<std::shared_ptr<PathElement>> vElements;

   auto length = GetLength();
   if (end < 0 || length < start)
   {
      // sub-path ends before the start of this element or the sub-path begins after
      // the start of this element - there isn't a sub-path for this element
   }
   else if (IsLE(start, 0.0) && IsLE(length, end))
   {
      // the entire line segment is between the start and end
      vElements.emplace_back(Clone());
   }
   else
   {
      // only a fraction of the curve is part of the sub-path

      // get parameters from the original curve so that we
      // can determine were it is relative to the sub-path
      auto Ls1 = GetSpiralLength(SpiralLocation::Entry);
      auto Ls2 = GetSpiralLength(SpiralLocation::Exit);
      auto L = GetCurveLength();
      auto Lt = GetTotalLength();

      enum class RelativePointLocation
      {
         StartBeforeTS = 1,
         StartInEntrySpiral = 2,
         StartInCircularCurve = 3,
         StartInExitSpiral = 4,
         EndAfterST = 5,
         EndInEntrySpiral = 6,
         EndInCircularCurve = 7,
         EndInExitSpiral = 8
      };

      RelativePointLocation StartPoint, EndPoint;

      // determine the start point of the sub-path curve
      if (start < 0)
      {
         // sub-path starts before start of HC
         StartPoint = RelativePointLocation::StartBeforeTS;
      }
      else if (0 <= start && start < Ls1)
      {
         // sub-path starts in the entry spiral
         StartPoint = RelativePointLocation::StartInEntrySpiral;
      }
      else if (Ls1 <= start && start < Ls1 + L)
      {
         // sub-path starts in the circular portion of the curve
         StartPoint = RelativePointLocation::StartInCircularCurve;
      }
      else if ( Ls1 + L <= start && start < Ls1 + L + Ls2)
      {
         // sub-path starts in the exit spiral
         StartPoint = RelativePointLocation::StartInExitSpiral;
      }
      else
      {
         CHECK(false); // should never get here.. sub path starts after this curve
      }


      // determine the end point of the sub-path curve
      if (end < 0)
      {
         CHECK(false); // should never get here.. sub path ends before this curve
      }
      else if (0 <= end && end < Ls1)
      {
         // sub-path ends in entry spiral
         EndPoint = RelativePointLocation::EndInEntrySpiral;
      }
      else if (Ls1 <= end && end < Ls1 + L)
      {
         // sub-path starts in the circular portion of the curve
         EndPoint = RelativePointLocation::EndInCircularCurve;
      }
      else if (Ls1 + L <= end && end < Ls1 + L + Ls2)
      {
         // sub-path starts in the exit spiral
         EndPoint = RelativePointLocation::EndInExitSpiral;
      }
      else
      {
         EndPoint = RelativePointLocation::EndAfterST;
      }

      // build the sub-path curve
      IndexType nSplinePoints = 7;
      if ((StartPoint == RelativePointLocation::StartBeforeTS || StartPoint == RelativePointLocation::StartInEntrySpiral) && EndPoint == RelativePointLocation::EndInEntrySpiral)
      {
         Float64 start_distance = Max(0., start);
         Float64 end_distance = Min(end, Ls1);
         vElements.emplace_back(CreateSubpathSpline(start_distance, end_distance, nSplinePoints));
      }
      else if (StartPoint == RelativePointLocation::StartInExitSpiral && (EndPoint == RelativePointLocation::EndInExitSpiral || EndPoint == RelativePointLocation::EndAfterST))
      {
         Float64 start_distance = Max(Ls1 + L, start);
         Float64 end_distance = Min(end, Lt);
         vElements.emplace_back(CreateSubpathSpline(start_distance, end_distance, nSplinePoints));
      }
      else
      {
         // determine the curve parameters of the sub-path curve

         // set up variables for sub-path curve
         Float64 R = GetRadius();
         Direction dirBack;
         Direction dirAhead;
         WBFL::Geometry::Point2d pbt, pi, pft;
         Float64 ls1 = 0;
         Float64 ls2 = 0;

         if (StartPoint == RelativePointLocation::StartInEntrySpiral)
         {
            Float64 start_distance = Max(0., start);
            Float64 end_distance = Min(end, Ls1);
            auto spline = CreateSubpathSpline(start_distance, end_distance, nSplinePoints);
            vElements.emplace_back(spline);

            // curve begins at end of approximated spiral
            pbt = PointOnCurve(end_distance);
            dirBack = GetBearing(end_distance);
         }
         else if (StartPoint == RelativePointLocation::StartBeforeTS)
         {
            ls1 = Ls1;
            pbt = PointOnCurve(start);
            dirBack = GetBearing(start);
         }
         else
         {
            // starting in circular curve
            pbt = PointOnCurve(start);
            dirBack = GetBearing(start);
         }

         if (EndPoint == RelativePointLocation::EndInExitSpiral)
         {
            Float64 start_distance = Max(Ls1 + L, start);
            Float64 end_distance = Min(end, Lt);
            auto spline = CreateSubpathSpline(start_distance, end_distance, nSplinePoints);
            vElements.emplace_back(spline);

            // curve ends at the start of the approximated spiral
            pft = PointOnCurve(start_distance);
            dirAhead = GetBearing(start_distance);
         }
         else if (EndPoint == RelativePointLocation::EndAfterST)
         {
            ls2 = Ls2;

            pft = PointOnCurve(end);
            dirAhead = GetBearing(end);
         }
         else
         {
            // ends in circular curve
            pft = PointOnCurve(end);
            dirAhead = GetBearing(end);
         }

         // PI is at the intersection of the tangents
         pi = COGO::IntersectBearings(pbt, dirBack, 0.0, pft, dirAhead, 0.0);
         auto compound_curve = CompoundCurve::Create();
         compound_curve->SetPBT(pbt);
         compound_curve->SetPI(pi);
         compound_curve->SetPFT(pft);
         compound_curve->SetRadius(R);
         compound_curve->SetSpiralLength(SpiralLocation::Entry, ls1);
         compound_curve->SetSpiralLength(SpiralLocation::Exit, ls2);

         if (EndPoint == RelativePointLocation::EndInExitSpiral)
         {
            // If the end spiral is already in vElements, we can't put compound_curve
            // at the end. We want entry spiral, compound curve, exit spiral
            // insert compound_curve before the last element
            vElements.emplace(std::prev(vElements.end()), compound_curve);
         }
         else
         {
            vElements.emplace_back(compound_curve);
         }
      }
   }

   return vElements;
}

//
// Private methods
//

Float64 CompoundCurve::SpiralX(Float64 ls, Float64 angle) const
{
   return ls * (1 - pow(angle, 2) / 10 + pow(angle, 4) / 216 - pow(angle, 6) / 9360);
}

Float64 CompoundCurve::SpiralY(Float64 ls, Float64 angle) const
{
   return ls * (angle / 3 - pow(angle, 3) / 42 + pow(angle, 5) / 1320 - pow(angle, 7) / 75600);
}

WBFL::Geometry::Point2d CompoundCurve::PointOnEntrySpiral(Float64 x, Float64 y) const
{
   // Setup a coordinate system at TS, with positive X going from TS to PI.
   // SC will be at point (X,kY) in this coordinate system.
   // k = 1 for left curves and -1 for right curves
   // Transform SC into the global coordinate system
   auto TS = GetTS();

   auto direction = COGO::MeasureDirection(TS, m_PI);

   auto cd = GetCurveDirection();
   Float64 k = (cd == CurveDirection::Left ? 1 : -1);

   WBFL::Geometry::Point2d p(x, k * y);
   p = WBFL::Geometry::GeometricOperations::LocalToGlobal(TS, direction, p);
   return p;
}

WBFL::Geometry::Point2d CompoundCurve::PointOnExitSpiral(Float64 x, Float64 y) const
{
   // Setup a coordinate system at ST, with positive X going from ST to PI
   // CS will be at point (X,kY) in this coordinate system
   // k = -1 for left curves and 1 for right curves
   // Transform CS into the global coordinate system
   auto ST = GetST();

   auto direction = COGO::MeasureDirection(ST, m_PI);

   auto cd = GetCurveDirection();
   Float64 k = (cd == CurveDirection::Left ? -1 : 1);

   WBFL::Geometry::Point2d p(x, k * y);
   p = WBFL::Geometry::GeometricOperations::LocalToGlobal(ST, direction, p);
   return p;
}

WBFL::Geometry::Point2d CompoundCurve::PointOnEntrySpiral(Float64 distFromTS) const
{
   auto angle = GetSpiralAngle(SpiralLocation::Entry);

   Float64 sweepAngle = pow(distFromTS / m_LsEntry, 2) * angle;

   Float64 x = SpiralX(distFromTS, sweepAngle);
   Float64 y = SpiralY(distFromTS, sweepAngle);

   return PointOnEntrySpiral(x, y);
}

WBFL::Geometry::Point2d CompoundCurve::PointOnExitSpiral(Float64 distFromST) const
{
   auto angle = GetSpiralAngle(SpiralLocation::Exit);

   // sweep angle measured from the end of the curve
   Float64 sweepAngle = pow(distFromST / m_LsExit, 2) * angle;

   Float64 x = SpiralX(distFromST, sweepAngle);
   Float64 y = SpiralY(distFromST, sweepAngle);

   return PointOnExitSpiral(x, y);
}

std::pair<Float64,WBFL::Geometry::Point2d> CompoundCurve::ProjectPointOnEntrySpiral(const WBFL::Geometry::Point2d& point) const
{
   CEntrySpiralFunction function(this, point);

   Float64 Ls = GetSpiralLength(SpiralLocation::Entry);

   WBFL::Math::BrentsRootFinder rootFinder;
   Float64 dist = rootFinder.FindRootInRange(function, 0, Ls, 0.00001);

   return std::make_pair(dist, PointOnEntrySpiral(dist));
}

std::pair<Float64, WBFL::Geometry::Point2d> CompoundCurve::ProjectPointOnExitSpiral(const WBFL::Geometry::Point2d& point) const
{
   CExitSpiralFunction function(this, point);

   Float64 Ls = GetSpiralLength(SpiralLocation::Exit);

   WBFL::Math::BrentsRootFinder rootFinder;
   Float64 dist = rootFinder.FindRootInRange(function, 0, Ls, 0.00001); // dist from end
   Float64 Lt = GetTotalLength();
   return std::make_pair(Lt - dist, PointOnExitSpiral(dist));
}

int CompoundCurve::ProjectionRegion(const WBFL::Geometry::Point2d& point) const
{
   int result = 0;

   if (0 < m_LsEntry)
   {
      // check entry spiral

      // put coordinate system at TS with Y towards the center of the curve
      auto origin = GetTS();
      auto brg = GetBackTangentBearing();

      auto xfrmPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(origin, brg, point);
      Float64 x1 = xfrmPoint.X(); // X ordinate in coordinate system 1

      // put coordinate system at SC with Y towards the center of the curve
      origin = GetSC();

      brg = GetBearing(m_LsEntry);

      xfrmPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(origin,brg,point);
      Float64 x2 = xfrmPoint.X(); // X ordinate in coordinate system 2

      if (x1 < 0)
         result |= BACK_TANGENT;

      if (0 <= x1 && x2 <= 0)
         result |= ENTRY_SPIRAL;
   }

   if (0 < m_LsExit)
   {
      // check exit spiral

      // put coordinate system at CS with Y towards the center of the curve
      auto origin = GetCS();
      auto Lt = GetTotalLength();
      auto brg = GetBearing(Lt - m_LsExit);

      auto xfrmPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(origin, brg, point);
      Float64 x1 = xfrmPoint.X(); // X ordinate in coordinate system 1

      // put coordinate system at ST with Y towards the center of the curve
      origin = GetST();
      brg = GetForwardTangentBearing();

      xfrmPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(origin, brg, point);
      Float64 x2 = xfrmPoint.X(); // X ordinate in coordinate system 2

      if (0 < x2)
         result |= FORWARD_TANGENT;

      if (0 <= x1 && x2 <= 0)
         result |= EXIT_SPIRAL;
   }

   // check circular curve

   // put coordinate system at SC with Y towards the center of the curve
   auto origin = GetSC();
   auto brg = GetBearing(m_LsEntry);

   auto xfrmPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(origin, brg, point);
   Float64 x1 = xfrmPoint.X(); // X ordinate in coordinate system 1

   // put coordinate system at CS with Y towards the center of the curve
   origin = GetCS();

   auto L = GetCurveLength();

   brg = GetBearing(m_LsEntry + L);

   xfrmPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(origin, brg, point);
   Float64 x2 = xfrmPoint.X(); // X ordinate in coordinate system 2

   if (IsZero(m_LsEntry) && x1 < 0)
      result |= BACK_TANGENT;

   if (IsZero(m_LsExit) && 0 < x2)
      result |= FORWARD_TANGENT;

   if (0 <= x1 && x2 <= 0)
      result |= CIRCULAR_CURVE;

   return result;
}

WBFL::Geometry::Line2d CompoundCurve::GetBackTangentLine() const
{
   return WBFL::Geometry::Line2d(m_PBT, m_PI);
}

WBFL::Geometry::Line2d CompoundCurve::GetForwardTangentLine() const
{
   return WBFL::Geometry::Line2d(m_PI, m_PFT);
}

std::shared_ptr<CubicSpline> CompoundCurve::CreateSubpathSpline(Float64 start, Float64 end, IndexType nPoints) const
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
bool CompoundCurve::IsPointOnCurve(const WBFL::Geometry::Point2d& point) const
{
   auto result = ProjectPoint(point);
   Float64 distFromStart = std::get<1>(result); // distFromStart is in position 1 of the result tuple
   auto pntOnCurve = PointOnCurve(distFromStart);
   return IsZero(point.Distance(pntOnCurve),tolerance);
}

bool CompoundCurve::IsPointOnLine(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Point2d& point) const
{
   return line.ContainsPoint(point,tolerance);
}

bool CompoundCurve::TestIntersection(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Point2d& point) const
{
   return IsPointOnCurve(point) && IsPointOnLine(line, point);
}
#endif // _DEBUG
