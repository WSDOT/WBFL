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
#include <CoordGeom/Utilities.h>
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
   return Utilities::MeasureDirection(m_PI, m_PFT);
}

Direction CompoundCurve::GetBackTangentBearing() const
{
   return Utilities::MeasureDirection(m_PBT, m_PI);
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
      return Utilities::MeasureDirection(CS, SPI);
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

      d = Utilities::MeasureDirection(SPI, SC);
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

      auto direction = Utilities::MeasureDirection(TS, m_PI);

      SPI.Move(X, -Y);
      SPI = WBFL::Geometry::GeometricOperations::LocalToGlobal(TS, direction, SPI);
   }
   else
   {
      // Setup a coordinate system at ST, with positive X going from ST to PI
      // CS will be at point (X,Y) in this coordinate system
      // Transform CS into the global coordinate system
      auto ST = GetST();

      auto direction = Utilities::MeasureDirection(ST, m_PI);

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

   auto pnt = Utilities::LocateByDistanceAndDirection(m_PI, T, bkTanBrg, 0.0);

   return pnt;
}

WBFL::Geometry::Point2d CompoundCurve::GetST() const
{
   auto fwdTanBrg = GetForwardTangentBearing();
   auto T = GetForwardTangentLength();

   auto pnt = Utilities::LocateByDistanceAndDirection(m_PI, T, fwdTanBrg, 0.0);

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
      angle = Utilities::MeasureAngle(from, vertex, to);
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
      angle = Utilities::MeasureAngle(from, vertex, to);
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
      return Utilities::LocateByDistanceAndDirection(TS, distFromStart, bkTanBrg, 0.0);
   }
   else if (Lt <= distFromStart)
   {
      // After curve
      auto fwdTanBrg = GetForwardTangentBearing();
      auto ST = GetST();
      return Utilities::LocateByDistanceAndDirection(ST, distFromStart - Lt, fwdTanBrg, 0.0);
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

      point = Utilities::LocateByDistanceAndDirection(point, offset, direction, 0.0);
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

      curvePoint = std::make_unique<WBFL::Geometry::Point2d>(Utilities::IntersectLineAndCircle(line, circle, point));

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
         if (bkTangentPoint && !Utilities::IsPointBeforeStart(TS, PI, *bkTangentPoint))
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
         if (fwdTangentPoint && !Utilities::IsPointAfterEnd(PI, ST, *fwdTangentPoint))
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
      CollectionIndexType nSplinePoints = 7;
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
         pi = Utilities::IntersectBearings(pbt, dirBack, 0.0, pft, dirAhead, 0.0);
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

   auto direction = Utilities::MeasureDirection(TS, m_PI);

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

   auto direction = Utilities::MeasureDirection(ST, m_PI);

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

#if defined _UNITTEST
bool CompoundCurve::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve");

   TRY_TESTME(Test1(rlog));
   TRY_TESTME(Test2(rlog));
   TRY_TESTME(Test3(rlog));
   TRY_TESTME(Test4(rlog));
   TRY_TESTME(Test5(rlog));
   TRY_TESTME(Test6(rlog));
   TRY_TESTME(Test7(rlog));
   TRY_TESTME(Test8a(rlog));
   TRY_TESTME(Test8b(rlog));
   TRY_TESTME(Test9a(rlog));
   TRY_TESTME(Test9b(rlog));
   TRY_TESTME(Test10a(rlog));
   TRY_TESTME(Test10b(rlog));
   TRY_TESTME(Test11a(rlog));
   TRY_TESTME(Test11b(rlog));


   // Test curve direction
   CompoundCurve curve;

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

   TESTME_EPILOG("CompoundCurve");
}

bool CompoundCurve::Test1(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test1");

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // PBT = (0,1000)
   // PI  = (700,1000)
   // PFT = (1000,700)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 200
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(0, 1000);
   WBFL::Geometry::Point2d pi(700, 1000);
   WBFL::Geometry::Point2d pft(1000, 1300);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 100);
   curve.SetSpiralLength(SpiralLocation::Exit, 200);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   pft.Move(1000, 700);
   curve.SetPFT(pft);
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Entry) == Angle(0.1));
   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Exit) == Angle(0.2));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Entry), 99.900046285613));
   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Exit), 199.20148011396));

   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Entry), 3.3309531383959));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Exit), 13.295286546224));

   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Entry), 0.83303));
   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Exit), 3.32857));

   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Entry), 49.98333));
   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Exit), 99.86681));

   TRY_TESTME(curve.GetBackTangentBearing() == Direction(0.0));
   TRY_TESTME(curve.GetForwardTangentBearing() == Direction(7 * M_PI / 4));

   TRY_TESTME(curve.GetCurveAngle() == Angle(M_PI / 4));

   TRY_TESTME(IsEqual(curve.GetBackTangentLength(), 260.96439));
   TRY_TESTME(IsEqual(curve.GetForwardTangentLength(), 304.82311));

   TRY_TESTME(curve.GetTS() == WBFL::Geometry::Point2d(439.03561,1000.));
   TRY_TESTME(curve.GetST() == WBFL::Geometry::Point2d(915.54248, 784.45751));
   TRY_TESTME(curve.GetSC() == WBFL::Geometry::Point2d(538.93564, 996.66904));
   TRY_TESTME(curve.GetCS() == WBFL::Geometry::Point2d(765.28458, 915.91304));

   TRY_TESTME(IsEqual(curve.GetChord(), 240.32347));

   TRY_TESTME(curve.GetCircularCurveAngle() == Angle(0.485398));

   TRY_TESTME(IsEqual(curve.GetTangent(), 123.78966));
   TRY_TESTME(IsEqual(curve.GetMidOrdinate(), 14.65357));
   TRY_TESTME(IsEqual(curve.GetExternal(), 15.095991));

   TRY_TESTME(curve.GetDE(SpiralLocation::Entry) == Angle(0.1));
   TRY_TESTME(curve.GetDE(SpiralLocation::Exit) == Angle(0.2));

   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Entry), 66.701620764682));
   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Exit), 133.61377));

   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Entry), 33.365112106495));
   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Exit), 66.92168));

   TRY_TESTME(curve.GetCC() == WBFL::Geometry::Point2d(439.03561, 307.95062));
   TRY_TESTME(curve.GetSPI(SpiralLocation::Entry) == WBFL::Geometry::Point2d(505.73722, 1000));
   TRY_TESTME(curve.GetSPI(SpiralLocation::Exit) == WBFL::Geometry::Point2d(821.06328, 878.93671));

   TRY_TESTME(curve.GetCurveBackTangentBearing() == Direction(6.18318530718));
   TRY_TESTME(curve.GetCurveForwardTangentBearing() == Direction(5.69778));

   TRY_TESTME(curve.GetPCI() == WBFL::Geometry::Point2d(662.10687, 984.31070));

   TRY_TESTME(curve.GetCCC() == WBFL::Geometry::Point2d(489.01894, 499.16696));

   TRY_TESTME(IsEqual(curve.GetSpiralChord(SpiralLocation::Entry), 99.95556));
   TRY_TESTME(IsEqual(curve.GetSpiralChord(SpiralLocation::Exit), 199.64467));

   TRY_TESTME(curve.GetDF(SpiralLocation::Entry) == Angle(0.0333305));
   TRY_TESTME(curve.GetDF(SpiralLocation::Exit) == Angle(0.0666441));

   TRY_TESTME(curve.GetDH(SpiralLocation::Entry) == Angle(0.0666695));
   TRY_TESTME(curve.GetDH(SpiralLocation::Exit) == Angle(0.1333559));

   TRY_TESTME(IsEqual(curve.GetCurveLength(), 242.69908));
   TRY_TESTME(IsEqual(curve.GetTotalLength(), 542.69908));

   //
   // Bearing and Normal
   //

   // Point before curve
   TRY_TESTME(curve.GetBearing(-1.0) == Direction(0.0));
   TRY_TESTME(curve.GetNormal(-1.0) == Direction(3 * PI_OVER_2));

   // At SC
   TRY_TESTME(curve.GetBearing(100.0) == Direction(TWO_PI - 0.1));
   TRY_TESTME(curve.GetNormal(100.0) == Direction(TWO_PI - 0.1 - PI_OVER_2));

   // At CS
   TRY_TESTME(curve.GetBearing(100.0 + curve.GetCurveLength()) == Direction(7 * M_PI / 4 + 0.2));
   TRY_TESTME(curve.GetNormal(100.0 + curve.GetCurveLength()) == Direction(7 * M_PI / 4 + 0.2 - PI_OVER_2));

   // Mid-point of exit spiral
   TRY_TESTME(curve.GetBearing(100.0 + curve.GetCurveLength() + 200 / 2) == Direction(7 * M_PI / 4 + 0.05));
   TRY_TESTME(curve.GetNormal(100.0 + curve.GetCurveLength() + 200 / 2) == Direction(7 * M_PI / 4 + 0.05 - PI_OVER_2));

   // Point after curve
   TRY_TESTME(curve.GetBearing(10000.) == Direction(7 * M_PI / 4));
   TRY_TESTME(curve.GetNormal(10000.) == Direction(7 * M_PI / 4 - PI_OVER_2));

   //
   // Test PointOnCurve
   //
   TRY_TESTME(curve.PointOnCurve(-100.0) == curve.GetTS().Offset(-100, 0)); // before start of curve
   TRY_TESTME(curve.PointOnCurve(0.0) == curve.GetTS()); // at start of curve
   TRY_TESTME(curve.PointOnCurve(50.0) == WBFL::Geometry::Point2d(489.03248, 999.58335)); // half-way between TS and SC
   TRY_TESTME(curve.PointOnCurve(100.0) == curve.GetSC()); // at SC
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength() / 2) == WBFL::Geometry::Point2d(657.03416, 970.09253)); // Half-way around the circular curve
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength()) == curve.GetCS()); // at CS
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength() + 200. / 2) == WBFL::Geometry::Point2d(843.67118, 853.97221)); // Half-way along exit spiral
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength() + 200.) == curve.GetST()); // at ST
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength() + 200 + 100) == curve.GetST().Offset(100 * sin(M_PI / 4), -100 * cos(M_PI / 4))); // 100 past ST

   //
   // Test ProjectPoint
   //
   WBFL::Geometry::Point2d pnt(300, 1100);
   WBFL::Geometry::Point2d prjPoint;
   Float64 distFromStart;
   bool bOnProjection;
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(300, 1000));
   TRY_TESTME(IsEqual(distFromStart, -139.03560006006825));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(300, 900);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(300, 1000));
   TRY_TESTME(IsEqual(distFromStart, -139.03560006006825));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(500, 1100);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(496.65666, 999.36213));
   TRY_TESTME(IsEqual(distFromStart, 57.627421617507935));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(500, 900);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(504.21291, 999.07669));
   TRY_TESTME(IsEqual(distFromStart, 65.189087390899658));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(1000, 1300);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(757.96599, 920.67316));
   TRY_TESTME(IsEqual(distFromStart, 333.96853201394083));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(550, 700);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(634.29003, 977.59805));
   TRY_TESTME(IsEqual(distFromStart, 197.39671595083021));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(900, 900);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(851.19828, 847.09484));
   TRY_TESTME(IsEqual(distFromStart, 452.89497474796428));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(800, 800);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(846.70794, 851.213706));
   TRY_TESTME(IsEqual(distFromStart, 446.80167535907879));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(1100, 500);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(1150.0,550.0));
   TRY_TESTME(IsEqual(distFromStart, 874.27207383613154));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(1200, 600);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
   TRY_TESTME(IsEqual(distFromStart, 874.27207383613154));
   TRY_TESTME(bOnProjection == true);

   // This point should project onto both tangents.
   // It is nearest the back tangent.
   pnt.Move(200, 0);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(200.0,1000.0));
   TRY_TESTME(IsEqual(distFromStart, -239.03560006006825));
   TRY_TESTME(bOnProjection == true);

   // This point should project onto both tangents.
   // It is nearest the forward tangent.
   pnt.Move(400, 0);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(1050.0, 650.0));
   TRY_TESTME(IsEqual(distFromStart, 732.85071759882192));
   TRY_TESTME(bOnProjection == true);

   // This point should project onto both spirals.
   // It is nearest the entry spiral.
   pnt.Move(450, 430);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(450.78716, 999.99459));
   TRY_TESTME(IsEqual(distFromStart, 11.751562356948853));
   TRY_TESTME(bOnProjection == false);

   // This point should project onto both spirals.
   // It is nearest the exit spiral.
   pnt.Move(470, 400);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(879.50334, 820.18857));
   TRY_TESTME(IsEqual(distFromStart, 491.94904665119304));
   TRY_TESTME(bOnProjection == false);

   TESTME_EPILOG("CompoundCurve::Test1");
}

bool CompoundCurve::Test2(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test2");

   /////////////////////////////////////////////////////
   // Test a symmetrical curve to the right
   // PBT = (0,1000)
   // PI  = (700,1000)
   // PFT = (1000,700)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 0
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(0, 1000);
   WBFL::Geometry::Point2d pi(700, 1000);
   WBFL::Geometry::Point2d pft(1000, 1300);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 100);
   curve.SetSpiralLength(SpiralLocation::Exit, 0);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   pft.Move(1000, 700);
   curve.SetPFT(pft);
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Entry) == Angle(0.1));
   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Exit) == Angle(0.0));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Entry), 99.900046));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Entry), 3.33095));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Exit), 0.0));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Exit), 0.0));

   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Entry), 0.83304));
   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Exit), 0.0));

   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Entry), 49.98334));
   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Exit), 0.0));

   TRY_TESTME(curve.GetBackTangentBearing() == Direction(0.0));
   TRY_TESTME(curve.GetForwardTangentBearing() == Direction(7 * M_PI / 4));
   TRY_TESTME(curve.GetCurveAngle() == Angle(M_PI / 4));

   TRY_TESTME(IsEqual(curve.GetBackTangentLength(), 256.25708337133716));
   TRY_TESTME(IsEqual(curve.GetForwardTangentLength(), 208.28487168090101));

   TRY_TESTME(curve.GetTS() == WBFL::Geometry::Point2d(443.7429166, 1000.));
   TRY_TESTME(curve.GetST() == WBFL::Geometry::Point2d(847.27964518413501, 852.72035481586499));
   TRY_TESTME(curve.GetSC() == WBFL::Geometry::Point2d(543.64296291427536, 996.66904686160410));
   TRY_TESTME(curve.GetCS() == WBFL::Geometry::Point2d(847.27964518413501, 852.72035481586499));

   TRY_TESTME(IsEqual(curve.GetChord(), 336.03044));
   TRY_TESTME(curve.GetCircularCurveAngle() == Angle(0.685398));
   TRY_TESTME(IsEqual(curve.GetTangent(), 178.38830241973267));
   TRY_TESTME(IsEqual(curve.GetMidOrdinate(), 29.074438143756819));

   TRY_TESTME(curve.GetDE(SpiralLocation::Entry) == Angle(0.1));
   TRY_TESTME(curve.GetDE(SpiralLocation::Exit) == Angle(0.0));

   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Entry), 66.701620764681550));
   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Exit), 0.0));

   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Entry), 33.365112106495175));
   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Exit), 0.0));

   TRY_TESTME(curve.GetCC() == WBFL::Geometry::Point2d(443.74291662866278, 449.18362626039277));

   TRY_TESTME(curve.GetSPI(SpiralLocation::Entry) == WBFL::Geometry::Point2d(510.44453739334438, 1000.0));
   TRY_TESTME(curve.GetSPI(SpiralLocation::Exit) == WBFL::Geometry::Point2d(847.27964518413501,  852.72035481586499));

   TRY_TESTME(curve.GetCurveBackTangentBearing() == Direction(6.18318530718));
   TRY_TESTME(curve.GetCurveForwardTangentBearing() == Direction(7 * M_PI / 4));

   TRY_TESTME(curve.GetPCI() == WBFL::Geometry::Point2d(721.14006685878576, 978.85993314121424));
   TRY_TESTME(curve.GetCCC() == WBFL::Geometry::Point2d(493.72625459086026, 499.16696422259037));

   TRY_TESTME(IsEqual(curve.GetSpiralChord(SpiralLocation::Entry), 99.955562));
   TRY_TESTME(IsEqual(curve.GetSpiralChord(SpiralLocation::Exit), 0.0));

   TRY_TESTME(curve.GetDF(SpiralLocation::Entry) == Angle(0.0333305));
   TRY_TESTME(curve.GetDF(SpiralLocation::Exit) == Angle(0.0));

   TRY_TESTME(curve.GetDH(SpiralLocation::Entry) == Angle(0.0666695));
   TRY_TESTME(curve.GetDH(SpiralLocation::Exit) == Angle(0.0));

   TRY_TESTME(IsEqual(curve.GetCurveLength(), 342.69908169872417));
   TRY_TESTME(IsEqual(curve.GetTotalLength(), 442.69908169872417));


   //
   // Bearing and Normal
   //
 
   // Point before curve
   TRY_TESTME(curve.GetBearing(-1) == Direction(0.0));
   TRY_TESTME(curve.GetNormal(-1) == Direction(3 * PI_OVER_2));

   // At SC
   TRY_TESTME(curve.GetBearing(100.0) == Direction(TWO_PI - 0.1));
   TRY_TESTME(curve.GetNormal(100.0) == Direction(TWO_PI - 0.1 - PI_OVER_2));

   // At CS
   TRY_TESTME(curve.GetBearing(100.0 + curve.GetCurveLength()) == Direction(7 * M_PI / 4));
   TRY_TESTME(curve.GetNormal(100.0 + curve.GetCurveLength()) == Direction(7 * M_PI / 4 - PI_OVER_2));

   // Point after curve
   TRY_TESTME(curve.GetBearing(10000.) == Direction(7 * M_PI / 4));
   TRY_TESTME(curve.GetNormal(10000.) == Direction(7 * M_PI / 4 - PI_OVER_2));

   //
   // Test PointOnCurve
   //
   
   TRY_TESTME(curve.PointOnCurve(-100) == curve.GetTS().Offset(-100, 0)); // Before TS
   TRY_TESTME(curve.PointOnCurve(0.0) == curve.GetTS()); // At TS
   TRY_TESTME(curve.PointOnCurve(50.0) == WBFL::Geometry::Point2d(493.73979, 999.58335)); // half-way between TS and SC
   TRY_TESTME(curve.PointOnCurve(100.0) == curve.GetSC()); // At SC
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength()/2) == WBFL::Geometry::Point2d(707.91621, 950.96633)); // Half-way around the circular curve
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength()) == curve.GetCS()); // At CS
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength()) == curve.GetST()); // At ST
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength() + 100) == curve.GetST().Offset(100 * sin(M_PI / 4), -100 * cos(M_PI / 4))); // 100 past ST

   //
   // Test ProjectPoint
   //
   WBFL::Geometry::Point2d pnt(300, 1100);
   WBFL::Geometry::Point2d prjPoint;
   Float64 distFromStart;
   bool bOnProjection;
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(300, 1000));
   TRY_TESTME(IsEqual(distFromStart, -143.74291662866284));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(300, 900);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(300, 1000));
   TRY_TESTME(IsEqual(distFromStart, -143.74291662866284));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(500, 1100);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(497.13371677391137, 999.49259034960562));
   TRY_TESTME(IsEqual(distFromStart, 53.395140171051025));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(500, 900);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(503.55430627716134, 999.28655987692082));
   TRY_TESTME(IsEqual(distFromStart, 59.819048643112183));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(1000, 1300);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(760.90548936690845, 921.79594631502243));
   TRY_TESTME(IsEqual(distFromStart, 331.87429448137652));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(550, 700);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(628.63123683543824, 980.62375954859954));
   TRY_TESTME(IsEqual(distFromStart, 186.59783566077238));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(900, 900);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(850.0, 850.0));
   TRY_TESTME(IsEqual(distFromStart, 446.54624437378743));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(800, 800);
   std::tie(prjPoint, distFromStart, bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(850.0, 850.0));
   TRY_TESTME(IsEqual(distFromStart, 446.54624437378743));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(1100, 500);
      std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
   TRY_TESTME(IsEqual(distFromStart, 870.81031308571596));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(1200, 600);
      std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
   TRY_TESTME(IsEqual(distFromStart, 870.81031308571596));
   TRY_TESTME(bOnProjection == true);

   TESTME_EPILOG("CompoundCurve::Test2");
}

bool CompoundCurve::Test3(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test3");

   /////////////////////////////////////////////////////
   // Test a symmetrical curve to the right
   // PBT = (0,1000)
   // PI  = (700,1000)
   // PFT = (1000,700)
   // R   = 500
   // Entry Spiral Length = 0
   // Exit Spiral Length = 200
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(0, 1000);
   WBFL::Geometry::Point2d pi(700, 1000);
   WBFL::Geometry::Point2d pft(1000, 1300);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 0);
   curve.SetSpiralLength(SpiralLocation::Exit, 200);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   pft.Move(1000, 700);
   curve.SetPFT(pft);
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);


   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Entry) == Angle(0.0));
   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Exit) == Angle(0.2));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Entry), 0.0));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Exit), 199.20148));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Exit), 13.29528));

   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Exit), 3.3285754668449599));

   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Exit), 99.866814716429502));

   TRY_TESTME(curve.GetBackTangentBearing() == Direction(0.0));
   TRY_TESTME(curve.GetForwardTangentBearing() == Direction(7 * M_PI / 4));
   TRY_TESTME(curve.GetCurveAngle() == Angle(M_PI / 4));

   TRY_TESTME(IsEqual(curve.GetBackTangentLength(), 211.81409775514197));
   TRY_TESTME(IsEqual(curve.GetForwardTangentLength(), 303.64502043613209));

   TRY_TESTME(curve.GetTS() == WBFL::Geometry::Point2d(488.18590224485806, 1000.));
   TRY_TESTME(curve.GetST() == WBFL::Geometry::Point2d(914.70945302391669, 785.29054697608319));
   TRY_TESTME(curve.GetSC() == WBFL::Geometry::Point2d(488.18590224485803, 1000.0));
   TRY_TESTME(curve.GetCS() == WBFL::Geometry::Point2d(764.45154833828497, 916.74607711240822));

   TRY_TESTME(IsEqual(curve.GetChord(), 288.53755888547977));
   TRY_TESTME(curve.GetCircularCurveAngle() == Angle(0.585398));
   TRY_TESTME(IsEqual(curve.GetTangent(), 150.67729930386835));
   TRY_TESTME(IsEqual(curve.GetMidOrdinate(), 21.265711194506100));

   TRY_TESTME(curve.GetDE(SpiralLocation::Entry) == Angle(0.0));
   TRY_TESTME(curve.GetDE(SpiralLocation::Exit) == Angle(0.2));

   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Exit), 133.61377246612963));

   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Exit), 66.921685863727987));

   TRY_TESTME(curve.GetCC() == WBFL::Geometry::Point2d(488.18590224485803, 358.76699619702475));

   TRY_TESTME(curve.GetSPI(SpiralLocation::Entry) == WBFL::Geometry::Point2d(488.18590224485803, 1000.0));
   TRY_TESTME(curve.GetSPI(SpiralLocation::Exit) == WBFL::Geometry::Point2d(820.23024845320003, 879.76975154679985));

   TRY_TESTME(curve.GetCurveBackTangentBearing() == Direction(0.0));
   TRY_TESTME(curve.GetCurveForwardTangentBearing() == Direction(7 * M_PI / 4 + 0.2));

   TRY_TESTME(curve.GetPCI() == WBFL::Geometry::Point2d(638.86320154872624, 1000.0));

   TRY_TESTME(curve.GetCCC() == WBFL::Geometry::Point2d(488.18590224485797, 500.0));

   TRY_TESTME(IsEqual(curve.GetSpiralChord(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetSpiralChord(SpiralLocation::Exit), 199.64467016161149));

   TRY_TESTME(curve.GetDF(SpiralLocation::Entry) == Angle(0.0));
   TRY_TESTME(curve.GetDF(SpiralLocation::Exit) == Angle(0.0666441));

   TRY_TESTME(curve.GetDH(SpiralLocation::Entry) == Angle(0.0));
   TRY_TESTME(curve.GetDH(SpiralLocation::Exit) == Angle(0.1333559));

   TRY_TESTME(IsEqual(curve.GetCurveLength(), 292.69908169872417));
   TRY_TESTME(IsEqual(curve.GetTotalLength(), 492.69908169872417));


   //
   // Bearing and Normal
   //
  
   // Point before curve
   TRY_TESTME(curve.GetBearing(-1) == Direction(0.0));
   TRY_TESTME(curve.GetNormal(-1) == Direction(3*PI_OVER_2));

   // At CS
   TRY_TESTME(curve.GetBearing(curve.GetCurveLength()) == Direction(7 * M_PI / 4 + 0.2));
   TRY_TESTME(curve.GetNormal(curve.GetCurveLength()) == Direction(7 * M_PI / 4 + 0.2 - PI_OVER_2));

   // Point after curve
   TRY_TESTME(curve.GetBearing(10000.) == Direction(7 * M_PI / 4));
   TRY_TESTME(curve.GetNormal(10000.) == Direction(7 * M_PI / 4 - PI_OVER_2));

   //
   // Test PointOnCurve
   //
   TRY_TESTME(curve.PointOnCurve(-100) == curve.GetTS().Offset(-100, 0)); // Before TS
   TRY_TESTME(curve.PointOnCurve(0.0) == curve.GetTS()); // At TS
   TRY_TESTME(curve.PointOnCurve(0.0) == curve.GetSC()); // At SC
   TRY_TESTME(curve.PointOnCurve(curve.GetCurveLength() / 2) == WBFL::Geometry::Point2d(632.45468,978.73429)); // Half-way around the circular curve
   TRY_TESTME(curve.PointOnCurve(curve.GetCurveLength()) == curve.GetCS()); // At CS
   TRY_TESTME(curve.PointOnCurve(curve.GetCurveLength() + 200./2) == WBFL::Geometry::Point2d(842.83815, 854.80525)); // Half-way along exit spiral
   TRY_TESTME(curve.PointOnCurve(curve.GetCurveLength() + 200.) == curve.GetST()); // At ST
   TRY_TESTME(curve.PointOnCurve(curve.GetTotalLength() + 100) == curve.GetST().Offset(100 * sin(M_PI / 4), -100 * cos(M_PI / 4))); // 100 past ST


   //
   // Test ProjectPoint
   //
   WBFL::Geometry::Point2d pnt(300, 1100);
   WBFL::Geometry::Point2d prjPoint;
   Float64 distFromStart;
   bool bOnProjection;
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(300, 1000));
   TRY_TESTME(IsEqual(distFromStart, -188.18590224485803));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(300, 900);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(300, 1000));
   TRY_TESTME(IsEqual(distFromStart, -188.18590224485803));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(500, 1100);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(498.02907578081619, 999.90310254579163));
   TRY_TESTME(IsEqual(distFromStart, 9.8438094375546967));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(500, 900);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(502.94708752500497, 999.78205991134200));
   TRY_TESTME(IsEqual(distFromStart, 14.763330356833970));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(1000, 1300);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(757.64331368111448, 921.18013179882087));
   TRY_TESTME(IsEqual(distFromStart, 284.57415999276304));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(550, 700);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(635.83013345708582, 977.70407261164269));
   TRY_TESTME(IsEqual(distFromStart, 149.87871522359342));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(900, 900);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(851.17791915026055, 847.17749344031427));
   TRY_TESTME(IsEqual(distFromStart, 404.00109986431255));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(800, 800);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(846.80545046763643, 851.19704221174209));
   TRY_TESTME(IsEqual(distFromStart, 398.06179503566875));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(1100, 500);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
   TRY_TESTME(IsEqual(distFromStart, 825.45016433048499));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(1200, 600);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
   TRY_TESTME(IsEqual(distFromStart, 825.45016433048499));
   TRY_TESTME(bOnProjection == true);

   TESTME_EPILOG("CompoundCurve::Test3");
}

bool CompoundCurve::Test4(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test4");

   /////////////////////////////////////////////////////
   // Test a symmetrical curve to the right
   // PBT = (0,1000)
   // PI  = (700,1000)
   // PFT = (1000,700)
   // R   = 500
   // Entry Spiral Length = 0
   // Exit Spiral Length = 0
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(0, 1000);
   WBFL::Geometry::Point2d pi(700, 1000);
   WBFL::Geometry::Point2d pft(1000, 1300);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 0);
   curve.SetSpiralLength(SpiralLocation::Exit, 0);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   pft.Move(1000, 700);
   curve.SetPFT(pft);
   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Entry) == Angle(0.0));
   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Exit) == Angle(0.0));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Entry), 0.0));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Exit), 0.0));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Exit), 0.0));

   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Exit), 0.0));

   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Exit), 0.0));

   TRY_TESTME(curve.GetBackTangentBearing() == Direction(0.0));
   TRY_TESTME(curve.GetForwardTangentBearing() == Direction(7 * M_PI / 4));
   TRY_TESTME(curve.GetCurveAngle() == Angle(M_PI / 4));

   TRY_TESTME(IsEqual(curve.GetBackTangentLength(), 207.10678));
   TRY_TESTME(IsEqual(curve.GetForwardTangentLength(), 207.10678));

   TRY_TESTME(curve.GetTS() == WBFL::Geometry::Point2d(492.89321881345245, 1000.0));
   TRY_TESTME(curve.GetST() == WBFL::Geometry::Point2d(846.44660940672622, 853.55339059327366));
   TRY_TESTME(curve.GetSC() == WBFL::Geometry::Point2d(492.89321881345245, 1000.0));
   TRY_TESTME(curve.GetCS() == WBFL::Geometry::Point2d(846.44660940672622, 853.55339059327366));

   TRY_TESTME(IsEqual(curve.GetChord(), 382.68343236508986));
   TRY_TESTME(curve.GetCircularCurveAngle() == Angle(M_PI/4));
   TRY_TESTME(IsEqual(curve.GetTangent(), 207.10678118654752));
   TRY_TESTME(IsEqual(curve.GetMidOrdinate(), 38.060233744356630));

   TRY_TESTME(curve.GetDE(SpiralLocation::Entry) == Angle(0.0));
   TRY_TESTME(curve.GetDE(SpiralLocation::Exit) == Angle(0.0));

   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Exit), 0.0));

   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Exit), 0.0));

   TRY_TESTME(curve.GetCC() == WBFL::Geometry::Point2d(492.89321881345245, 500.0));

   TRY_TESTME(curve.GetSPI(SpiralLocation::Entry) == WBFL::Geometry::Point2d(492.89322, 1000.0));
   TRY_TESTME(curve.GetSPI(SpiralLocation::Exit) == WBFL::Geometry::Point2d(846.44661, 853.55339));

   TRY_TESTME(curve.GetCurveBackTangentBearing() == Direction(0.0));
   TRY_TESTME(curve.GetCurveForwardTangentBearing() == Direction(7 * M_PI / 4));

   TRY_TESTME(curve.GetPCI() == WBFL::Geometry::Point2d(700., 1000.0));

   TRY_TESTME(curve.GetCCC() == WBFL::Geometry::Point2d(492.89322, 500.0));

   TRY_TESTME(IsEqual(curve.GetSpiralChord(SpiralLocation::Entry), 0.0));
   TRY_TESTME(IsEqual(curve.GetSpiralChord(SpiralLocation::Exit), 0.0));

   TRY_TESTME(curve.GetDF(SpiralLocation::Entry) == Angle(0.0));
   TRY_TESTME(curve.GetDF(SpiralLocation::Exit) == Angle(0.0));

   TRY_TESTME(curve.GetDH(SpiralLocation::Entry) == Angle(0.0));
   TRY_TESTME(curve.GetDH(SpiralLocation::Exit) == Angle(0.0));

   TRY_TESTME(IsEqual(curve.GetCurveLength(), 392.69908169872411));
   TRY_TESTME(IsEqual(curve.GetTotalLength(), 392.69908169872411));

   //
   // Bearing and Normal
   //
  
   // Point before curve
   TRY_TESTME(curve.GetBearing(-1) == Direction(0.0));
   TRY_TESTME(curve.GetNormal(-1) == Direction(3 * PI_OVER_2));

   // At mid-point of curve
   TRY_TESTME(curve.GetBearing(curve.GetCurveLength() / 2) == Direction(7 * M_PI / 4 + M_PI / 8));
   TRY_TESTME(curve.GetNormal(curve.GetCurveLength() / 2) == Direction(7 * M_PI / 4 + M_PI / 8 - PI_OVER_2));

   // Point after curve
   TRY_TESTME(curve.GetBearing(10000.) == Direction(7 * M_PI / 4));
   TRY_TESTME(curve.GetNormal(10000.) == Direction(7 * M_PI / 4 - PI_OVER_2));


   //
   // Test PointOnCurve
   //
   TRY_TESTME(curve.PointOnCurve(-100) == curve.GetTS().Offset(-100, 0)); // Before TS
   TRY_TESTME(curve.PointOnCurve(0.0) == curve.GetTS()); // At TS
   TRY_TESTME(curve.PointOnCurve(0.0) == curve.GetSC()); // At SC
   TRY_TESTME(curve.PointOnCurve(curve.GetCurveLength() / 2) == WBFL::Geometry::Point2d(684.23493, 961.93977)); // Half-way around the circular curve
   TRY_TESTME(curve.PointOnCurve(curve.GetCurveLength()) == curve.GetCS()); // At CS
   TRY_TESTME(curve.PointOnCurve(curve.GetCurveLength()) == curve.GetST()); // At ST
   TRY_TESTME(curve.PointOnCurve(curve.GetTotalLength() + 100) == curve.GetST().Offset(100 * sin(M_PI / 4), -100 * cos(M_PI / 4))); // 100 past ST

   //
   // Test ProjectPoint
   //
   WBFL::Geometry::Point2d pnt(300, 1100);
   WBFL::Geometry::Point2d prjPoint;
   Float64 distFromStart;
   bool bOnProjection;
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(300, 1000));
   TRY_TESTME(IsEqual(distFromStart, -192.89321881345245));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(300, 900);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(300, 1000));
   TRY_TESTME(IsEqual(distFromStart, -192.89321881345245));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(500, 1100);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(498.81512107569978, 999.96492984393990));
   TRY_TESTME(IsEqual(distFromStart, 5.9220407208209203));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(500, 900);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(501.77529352889013, 999.92110252390921));
   TRY_TESTME(IsEqual(distFromStart, 8.8825419271126869));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(1000, 1300);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(760.58505570770842, 922.30448785228305));
   TRY_TESTME(IsEqual(distFromStart, 282.48097189865661));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(550, 700);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(630.17360217890621, 980.78487532682811));
   TRY_TESTME(IsEqual(distFromStart, 139.06644242357936));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(900, 900);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(850.0, 850.0));
   TRY_TESTME(IsEqual(distFromStart, 397.72433486814077));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(800, 800);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(850.0, 850.0));
   TRY_TESTME(IsEqual(distFromStart, 397.72433486814077));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(1100, 500);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
   TRY_TESTME(IsEqual(distFromStart, 821.98840358006942));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(1200, 600);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
   TRY_TESTME(IsEqual(distFromStart, 821.98840358006942));
   TRY_TESTME(bOnProjection == true);

   TESTME_EPILOG("CompoundCurve::Test4");
}

bool CompoundCurve::Test5(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test5");

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // PBT = (0,1000)
   // PI  = (700,1000)
   // PFT = (1000,1300)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 200
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(0, 1000);
   WBFL::Geometry::Point2d pi(700, 1000);
   WBFL::Geometry::Point2d pft(1000, 1300);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 100);
   curve.SetSpiralLength(SpiralLocation::Exit, 200);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Entry) == Angle(0.1));
   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Exit) == Angle(0.2));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Entry), 99.900046285613));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Entry), 3.3309531383959));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Exit), 199.20148011396));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Exit), 13.295286546224));

   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Entry), 0.83303));
   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Exit), 3.3285754668449599));

   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Entry), 49.983337962198455));
   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Exit), 99.866814716429502));

   TRY_TESTME(curve.GetBackTangentBearing() == Direction(0.0));
   TRY_TESTME(curve.GetForwardTangentBearing() == Direction(M_PI / 4));
   TRY_TESTME(curve.GetCurveAngle() == Angle(M_PI / 4));

   TRY_TESTME(IsEqual(curve.GetBackTangentLength(), 260.96439));
   TRY_TESTME(IsEqual(curve.GetForwardTangentLength(), 304.82311));

   TRY_TESTME(curve.GetTS() == WBFL::Geometry::Point2d(439.03560006006825, 1000.0000000000000));
   TRY_TESTME(curve.GetST() == WBFL::Geometry::Point2d(915.54248880132559, 1215.5424888013256));
   TRY_TESTME(curve.GetSC() == WBFL::Geometry::Point2d(538.93564634568077, 1003.3309531383959));
   TRY_TESTME(curve.GetCS() == WBFL::Geometry::Point2d(765.28458411569386, 1084.0869586650006));

   TRY_TESTME(IsEqual(curve.GetChord(), 240.323477));
   TRY_TESTME(curve.GetCircularCurveAngle() == Angle(0.48539816339744829));
   TRY_TESTME(IsEqual(curve.GetTangent(), 123.78966));
   TRY_TESTME(IsEqual(curve.GetMidOrdinate(), 14.65357));

   TRY_TESTME(curve.GetDE(SpiralLocation::Entry) == Angle(0.1));
   TRY_TESTME(curve.GetDE(SpiralLocation::Exit) == Angle(0.2));

   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Entry), 66.701620764682));
   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Exit), 133.613772));

   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Entry), 33.365112106495));
   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Exit), 66.92168));

   TRY_TESTME(curve.GetCC() == WBFL::Geometry::Point2d(439.035600, 1692.0493775));

   TRY_TESTME(curve.GetSPI(SpiralLocation::Entry) == WBFL::Geometry::Point2d(505.73722, 1000.0));
   TRY_TESTME(curve.GetSPI(SpiralLocation::Exit) == WBFL::Geometry::Point2d(821.063284, 1121.06328));

   TRY_TESTME(curve.GetCurveBackTangentBearing() == Direction(0.1));
   TRY_TESTME(curve.GetCurveForwardTangentBearing() == Direction(M_PI / 4 - 0.2));

   TRY_TESTME(curve.GetPCI() == WBFL::Geometry::Point2d(662.10687, 1015.68929));

   TRY_TESTME(curve.GetCCC() == WBFL::Geometry::Point2d(489.01893, 1500.833035));

   TRY_TESTME(IsEqual(curve.GetSpiralChord(SpiralLocation::Entry), 99.95556));
   TRY_TESTME(IsEqual(curve.GetSpiralChord(SpiralLocation::Exit), 199.64467));

   TRY_TESTME(curve.GetDF(SpiralLocation::Entry) == Angle(0.0333305));
   TRY_TESTME(curve.GetDF(SpiralLocation::Exit) == Angle(0.0666441));

   TRY_TESTME(curve.GetDH(SpiralLocation::Entry) == Angle(0.0666695));
   TRY_TESTME(curve.GetDH(SpiralLocation::Exit) == Angle(0.1333559));

   TRY_TESTME(IsEqual(curve.GetCurveLength(), 242.699081));
   TRY_TESTME(IsEqual(curve.GetTotalLength(), 542.699081));

   //
   // Bearing and Normal
   //
 
   // Point before curve
   TRY_TESTME(curve.GetBearing(-1) == Direction(0.0));
   TRY_TESTME(curve.GetNormal(-1) == Direction(3 * PI_OVER_2));

   // At SC
   TRY_TESTME(curve.GetBearing(100.0) == Direction(0.1));
   TRY_TESTME(curve.GetNormal(100.0) == Direction(3*PI_OVER_2 + 0.1));
   
   // At CS
   TRY_TESTME(curve.GetBearing(100.0 + curve.GetCurveLength()) == Direction(M_PI / 4 - 0.2));
   TRY_TESTME(curve.GetNormal(100.0 + curve.GetCurveLength()) == Direction(3 * PI_OVER_2 + M_PI / 4 - 0.2));

   // Mid-point of exit spiral
   TRY_TESTME(curve.GetBearing(100.0 + curve.GetCurveLength() + 200. / 2) == Direction(M_PI / 4 - 0.05));
   TRY_TESTME(curve.GetNormal(100.0 + curve.GetCurveLength() + 200. / 2) == Direction(3 * PI_OVER_2 + M_PI / 4 - 0.05));

   // Point after curve
   TRY_TESTME(curve.GetBearing(10000.) == Direction(M_PI / 4));
   TRY_TESTME(curve.GetNormal(10000.) == Direction(3*PI_OVER_2 + M_PI / 4 ));

   //
   // Test PointOnCurve
   //
   TRY_TESTME(curve.PointOnCurve(-100) == curve.GetTS().Offset(-100, 0)); // Before TS
   TRY_TESTME(curve.PointOnCurve(0.0) == curve.GetTS()); // At TS
   TRY_TESTME(curve.PointOnCurve(50.0) == WBFL::Geometry::Point2d(489.03248, 1000.41665)); // half-way between TS and SC
   TRY_TESTME(curve.PointOnCurve(100.0) == curve.GetSC()); // At SC
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength()/2) == WBFL::Geometry::Point2d(657.034161, 1029.90747)); // Half-way around the circular curve
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength()) == curve.GetCS()); // At CS
   TRY_TESTME(curve.PointOnCurve(100.0 + curve.GetCurveLength() + 200.0/2) == WBFL::Geometry::Point2d(843.67118, 1146.02779)); // Half-way along exit spiral
   TRY_TESTME(curve.PointOnCurve(curve.GetTotalLength()) == curve.GetST()); // At ST
   TRY_TESTME(curve.PointOnCurve(curve.GetTotalLength() + 100) == curve.GetST().Offset(100 * sin(M_PI / 4), 100 * cos(M_PI / 4))); // 100 past ST

   //
   // Test ProjectPoint
   //
   WBFL::Geometry::Point2d pnt(400, 1100);
   WBFL::Geometry::Point2d prjPoint;
   Float64 distFromStart;
   bool bOnProjection;
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(400, 1000));
   TRY_TESTME(IsEqual(distFromStart, -39.035600060068248));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(400, 900);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(400, 1000));
   TRY_TESTME(IsEqual(distFromStart, -39.035600060068248));
   TRY_TESTME(bOnProjection == true);

   pnt.Move(490, 1100);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(492.88607, 1000.52063));
   TRY_TESTME(IsEqual(distFromStart, 53.855001926422119));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(490, 900);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(487.62895, 1000.38253));
   TRY_TESTME(IsEqual(distFromStart, 48.596060276031494));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(650, 1100);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(675.36056, 1036.85373));
   TRY_TESTME(IsEqual(distFromStart, 240.94946090466198));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(650, 900);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(618.41971, 1017.86777));
   TRY_TESTME(IsEqual(distFromStart, 180.89063696761301));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(850, 1200);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(874.35534, 1174.81344));
   TRY_TESTME(IsEqual(distFromStart, 484.77395276195659));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(1050, 1000);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(877.34833, 1177.71447));
   TRY_TESTME(IsEqual(distFromStart, 488.94216517574444));
   TRY_TESTME(bOnProjection == false);

   pnt.Move(1200, 1300);
   std::tie(prjPoint,distFromStart,bOnProjection) = curve.ProjectPoint(pnt);
   TRY_TESTME(prjPoint == WBFL::Geometry::Point2d(1100.0, 1400.0));
   TRY_TESTME(IsEqual(distFromStart, 803.56139571747667));
   TRY_TESTME(bOnProjection == true);

   TESTME_EPILOG("CompoundCurve::Test5");
}

bool CompoundCurve::Test6(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test6");
   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // PBT = (-1000,0)
   // PI  = (0,0)
   // PFT = (937.993610303, -346.652545108)
   // R   = 1000
   // Entry Spiral Length = 350
   // Exit Spiral Length = 150

   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(-1000, 0);
   WBFL::Geometry::Point2d pi(0, 0);
   WBFL::Geometry::Point2d pft(937.993610303, -346.652545108);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(1000);
   curve.SetSpiralLength(SpiralLocation::Entry, 350);
   curve.SetSpiralLength(SpiralLocation::Exit, 150);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Entry) == Angle(0.175));
   TRY_TESTME(curve.GetSpiralAngle(SpiralLocation::Exit) == Angle(0.075));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Entry), 348.929643656));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Entry), 20.3720487046));

   TRY_TESTME(IsEqual(curve.GetX(SpiralLocation::Exit), 149.91564697));
   TRY_TESTME(IsEqual(curve.GetY(SpiralLocation::Exit), 3.7484935732));

   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Entry), 5.0985876095420));
   TRY_TESTME(IsEqual(curve.GetQ(SpiralLocation::Exit), 0.93731168541681));

   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Entry), 174.82150606254));
   TRY_TESTME(IsEqual(curve.GetT(SpiralLocation::Exit), 74.985939697062));

   TRY_TESTME(curve.GetBackTangentBearing() == Direction(0.0));
   TRY_TESTME(curve.GetForwardTangentBearing() == Direction(TWO_PI - 0.354));
   TRY_TESTME(curve.GetCurveAngle() == Angle(0.354));

   TRY_TESTME(IsEqual(curve.GetBackTangentLength(), 342.601202));
   TRY_TESTME(IsEqual(curve.GetForwardTangentLength(), 266.02964));

   TRY_TESTME(curve.GetTS() == WBFL::Geometry::Point2d(-342.601202, 0.0));
   TRY_TESTME(curve.GetST() == WBFL::Geometry::Point2d(249.53410, -92.21985));
   TRY_TESTME(curve.GetSC() == WBFL::Geometry::Point2d(6.32844, -20.37205));
   TRY_TESTME(curve.GetCS() == WBFL::Geometry::Point2d(107.61475, -43.76727));

   TRY_TESTME(IsEqual(curve.GetChord(), 103.95313));
   TRY_TESTME(curve.GetCircularCurveAngle() == Angle(0.104));
   TRY_TESTME(IsEqual(curve.GetTangent(), 52.04692));
   TRY_TESTME(IsEqual(curve.GetMidOrdinate(), 1.35169));

   TRY_TESTME(curve.GetDE(SpiralLocation::Entry) == Angle(0.175));
   TRY_TESTME(curve.GetDE(SpiralLocation::Exit) == Angle(0.075));

   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Entry), 233.70873));
   TRY_TESTME(IsEqual(curve.GetLongTangent(SpiralLocation::Exit), 100.02948));

   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Entry), 117.00802));
   TRY_TESTME(IsEqual(curve.GetShortTangent(SpiralLocation::Exit), 50.026801));

   TRY_TESTME(curve.GetCC() == WBFL::Geometry::Point2d(-342.60120, -1694.45569));

   TRY_TESTME(curve.GetSPI(SpiralLocation::Entry) == WBFL::Geometry::Point2d(-108.89246, 0.0));
   TRY_TESTME(curve.GetSPI(SpiralLocation::Exit) == WBFL::Geometry::Point2d(155.70708, -57.54437));

   TRY_TESTME(curve.GetCurveBackTangentBearing() == Direction(6.10818));
   TRY_TESTME(curve.GetCurveForwardTangentBearing() == Direction(6.00418));

   TRY_TESTME(curve.GetPCI() == WBFL::Geometry::Point2d(57.580424, -29.43384));

   TRY_TESTME(curve.GetCCC() == WBFL::Geometry::Point2d(-167.77969, -1005.09858));

   TESTME_EPILOG("CompoundCurve::Test6");
}

bool CompoundCurve::Test7(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test7");
   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // Spiral lengths overlap
   // PBT = (0,1000)
   // PI  = (700,1000)
   // PFT = (1000,1300)
   // R   = 500
   // Entry Spiral Length = 500
   // Exit Spiral Length = 700

   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(0, 1000);
   WBFL::Geometry::Point2d pi(700, 1000);
   WBFL::Geometry::Point2d pft(1000, 1300);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 500);
   curve.SetSpiralLength(SpiralLocation::Exit, 700);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   try
   {
      curve.GetCircularCurveAngle();
   }
   catch(XCoordGeom& e)
   {
      TRY_TESTME(e.GetReason() == WBFL_COGO_E_SPIRALSOVERLAP);
   }

   TESTME_EPILOG("CompoundCurve::Test7");
}

bool CompoundCurve::Test8a(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test8a");
   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // Spiral lengths overlap
   // PBT = (0,1000)
   // PI  = (700,1000)
   // PFT = (1000,1300)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 200

   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(0, 1000);
   WBFL::Geometry::Point2d pi(700, 1000);
   WBFL::Geometry::Point2d pft(1000, 1300);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 100);
   curve.SetSpiralLength(SpiralLocation::Exit, 200);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   // create a line
   WBFL::Geometry::Line2d line;

   // Important curve points
   auto cc = curve.GetCC();
   auto spi1 = curve.GetSPI(SpiralLocation::Entry);
   auto spi2 = curve.GetSPI(SpiralLocation::Exit);

   // make line intersect entry spiral
   line.ThroughPoints(cc, spi1);
   auto vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front()  == WBFL::Geometry::Point2d(505.64225645686224, 1000.9854331731150));

   // make line intersect exit spiral
   line.ThroughPoints(cc, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(818.84459859920526, 1124.3794191254133));

   // make line intersect circular curve
   line.ThroughPoints(cc, pi);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(684.65428056880842, 1040.6952164811710));

   // intersect both spirals at once
   line.ThroughPoints(spi1, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(508.67043163106791, 1001.1261389033072));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(809.35182374575743, 1116.5668976835791));

   // intersect circular curve in two places
   // first locate two points on the curve
   auto cp1 = curve.PointOnCurve(110);
   auto cp2 = curve.PointOnCurve(140);

   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(548.87503670886008, 1004.4287172526595));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(578.53372538212068, 1008.9111895010718));

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1 = curve.PointOnCurve(150);
   cp2 = curve.PointOnCurve(151);

   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(588.35360, 1010.79974));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(589.33347, 1010.99939));

   // line tangent to entry spiral
   auto POC = curve.PointOnCurve(50);
   auto dir = curve.GetBearing(50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(489.03247, 1000.41664));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(489.03247, 1000.41664));

   // intersect entry spiral in 2 locations
   cp1 = curve.PointOnCurve(35);
   cp2 = curve.PointOnCurve(45);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(474.03507484100646, 1000.1429151347374));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(484.03375483745350, 1000.3037411037024));

   // line tangent to exit spiral
   Float64 length = curve.GetTotalLength();
   POC = curve.PointOnCurve(length - 50);
   dir = curve.GetBearing(length - 50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, 1180.3350144338078));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, 1180.3350144338078));

   // intersect exit spiral in 2 locations
   cp1 = curve.PointOnCurve(length - 45);
   cp2 = curve.PointOnCurve(length - 35);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(883.61562936445966, 1183.8304112645556));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(890.74331577219289, 1190.8443728455015));

   // line tangent to circular curve
   POC = curve.PointOnCurve(length / 2);
   dir = curve.GetBearing(length / 2);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(703.20889, 1049.03367));

   // line intersect back tangent and exit spiral
   line.ThroughPoints(pbt, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(813.501198, 1119.948289));

   // again, but don't project back
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(813.501198, 1119.948289));

   // line intersect fwd tangent and entry spiral
   line.ThroughPoints(spi1, pft);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(507.50055, 1001.07029));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(1000.0, 1300.0));

   // again, but don't project ahead
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front()  == WBFL::Geometry::Point2d(507.50055, 1001.07029));

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1.Move(0, 900);
   cp2.Move(700, 900);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(0, 1100);
   cp2.Move(700, 1100);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(787.96427, 1099.99997));

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1.Move(0, 1500);
   cp2.Move(700, 1500);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1200.0, 1500.0));

   // again, but don't project curve
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1.Move(800, 1000);
   cp2.Move(1100, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(600, 1000);
   cp2.Move(900, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(617.666636, 1017.666636));

   // again, but on inside of curve (intersect with projected tangent)
   cp1.Move(200, 1000);
   cp2.Move(500, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(200.0, 1000.0));

   // again, but don't project curve
   cp1.Move(200, 1000);
   cp2.Move(500, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1.Move(0, 1000);
   cp2.Move(1000, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0,1000.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(1000.0, 1300.0));

   // again, but project only back
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));

   // again, but project only ahead
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1000.0, 1300.0));

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1.Move(690, 1000);
   cp2.Move(710, 1010);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   TESTME_EPILOG("CompoundCurve::Test8a");
}

bool CompoundCurve::Test8b(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test8b");
   // same as Test8a except the direction of the curve is reverse

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // Spiral lengths overlap
   // PBT = (1000,1300)
   // PI  = (700,1000)
   // PFT = (0,1000)
   // R   = 500
   // Entry Spiral Length = 200
   // Exit Spiral Length = 100

   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(1000, 1300);
   WBFL::Geometry::Point2d pi(700, 1000);
   WBFL::Geometry::Point2d pft(0, 1000);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 200);
   curve.SetSpiralLength(SpiralLocation::Exit, 100);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   // create a line
   WBFL::Geometry::Line2d line;

   // Important curve points
   auto cc = curve.GetCC();
   auto spi1 = curve.GetSPI(SpiralLocation::Entry);
   auto spi2 = curve.GetSPI(SpiralLocation::Exit);

   // make line intersect exit spiral
   line.ThroughPoints(cc, spi2);
   auto vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(505.64225645686224, 1000.9854331731150));

   // make line intersect entry spiral
   line.ThroughPoints(cc, spi1);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(818.84459859920526, 1124.3794191254133));

   // make line intersect circular curve
   line.ThroughPoints(cc, pi);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(684.65428056880842, 1040.6952164811710));

   // intersect both spirals at once
   line.ThroughPoints(spi1, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(809.35182374575743, 1116.5668976835791));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(508.67043163106791, 1001.1261389033072));

   // intersect circular curve in two places
   // first locate two points on the curve
   Float64 length = curve.GetTotalLength();
   auto cp1 = curve.PointOnCurve(length - 140);
   auto cp2 = curve.PointOnCurve(length - 110);

   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(578.53372538212068, 1008.9111895010718));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(548.87503670886008, 1004.4287172526595));

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1 = curve.PointOnCurve(length - 151);
   cp2 = curve.PointOnCurve(length - 150);

   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(589.33347, 1010.99939));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(588.35360, 1010.79974));

   // line tangent to exit spiral
   auto POC = curve.PointOnCurve(length - 50);
   auto dir = curve.GetBearing(length - 50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(489.03247, 1000.41664));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(489.03247, 1000.41664));

   // intersect entry spiral in 2 locations
   cp1 = curve.PointOnCurve(length - 45);
   cp2 = curve.PointOnCurve(length - 35);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(484.03375483745350, 1000.303741103702));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(474.03507484100646, 1000.142915134737));

   // line tangent to exit spiral
   POC = curve.PointOnCurve(50);
   dir = curve.GetBearing(50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, 1180.3350144338078));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, 1180.3350144338078));

   // intersect exit spiral in 2 locations
   cp1 = curve.PointOnCurve(35);
   cp2 = curve.PointOnCurve(45);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(890.74331577219289, 1190.8443728455015));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(883.61562929997854, 1183.8304112013670));

   // line tangent to circular curve
   POC = curve.PointOnCurve(length / 2);
   dir = curve.GetBearing(length / 2);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(703.20889, 1049.03367));

   // line intersect back tangent and exit spiral
   line.ThroughPoints(pft, spi1);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(813.50119, 1119.94828));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(0.0,1000.0));

   // again, but don't project back
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(813.50119, 1119.94828));

   // line intersect fwd tangent and entry spiral
   line.ThroughPoints(spi2, pbt);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1000.0,1300.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(507.50055, 1001.07029));

   // again, but don't project ahead
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(507.50055, 1001.07029));

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1.Move(0, 900);
   cp2.Move(700, 900);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(0, 1100);
   cp2.Move(700, 1100);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(787.96427, 1099.99997));

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1.Move(0, 1500);
   cp2.Move(700, 1500);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1200.0,1500.0));

   // again, but don't project curve
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1.Move(800, 1000);
   cp2.Move(1100, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(600, 1000);
   cp2.Move(900, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(617.66664, 1017.66664));

   // again, but on inside of curve (intersect with projected tangent)
   cp1.Move(200, 1000);
   cp2.Move(500, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(200.0, 1000.0));

   // again, but don't project curve
   cp1.Move(200, 1000);
   cp2.Move(500, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1.Move(0, 1000);
   cp2.Move(1000, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1000.0, 1300.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(0.0, 1000.0));

   // again, but project only back
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));

   // again, but project only ahead
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1000.0, 1300.0));

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1.Move(690, 1000);
   cp2.Move(710, 1010);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   TESTME_EPILOG("CompoundCurve::Test8b");
}

bool CompoundCurve::Test9a(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test9a");
   // This is the same as Test8a except the curve has been mirrored about the Y axis

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // Spiral lengths overlap
   // PBT = (0,1000)
   // PI  = (-700,1000)
   // PFT = (-1000,1300)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 200
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(0, 1000);
   WBFL::Geometry::Point2d pi(-700, 1000);
   WBFL::Geometry::Point2d pft(-1000, 1300);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 100);
   curve.SetSpiralLength(SpiralLocation::Exit, 200);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   // create a line
   WBFL::Geometry::Line2d line;

   // get some useful curve points
   auto cc = curve.GetCC();
   auto spi1 = curve.GetSPI(SpiralLocation::Entry);
   auto spi2 = curve.GetSPI(SpiralLocation::Exit);

   // make line intersect entry spiral
   line.ThroughPoints(cc, spi1);
   auto vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-505.64225645686224, 1000.9854331731151));

   // make line intersect exit spiral
   line.ThroughPoints(cc, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-818.84459859920526, 1124.3794191254133));


   // make line intersect circular curve
   line.ThroughPoints(cc, pi);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-684.65428056880842, 1040.6952164811710));

   // intersect both spirals at once
   line.ThroughPoints(spi1, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-508.67043163106791, 1001.1261389033072));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-809.35182374575743, 1116.5668976835791));


   // intersect circular curve in two places
   // first locate two points on the curve
   auto cp1 = curve.PointOnCurve(110);
   auto cp2 = curve.PointOnCurve(140);

   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-548.87503670886008, 1004.4287172526595));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-578.53372538212068, 1008.9111895010718));

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1 = curve.PointOnCurve(150);
   cp2 = curve.PointOnCurve(151);

   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-588.35360, 1010.79974));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-589.33347, 1010.99939));

   // line tangent to entry spiral
   auto POC = curve.PointOnCurve(50);
   auto dir = curve.GetBearing(50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, 1000.41664));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, 1000.41664));

   // intersect entry spiral in 2 locations
   cp1 = curve.PointOnCurve(35);
   cp2 = curve.PointOnCurve(45);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-474.03507484100646, 1000.1429151347374));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-484.03375483745350, 1000.3037411037024));

   // line tangent to exit spiral
   Float64 length = curve.GetTotalLength();
   POC = curve.PointOnCurve(length - 50);
   dir = curve.GetBearing(length - 50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, 1180.3350144338078));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, 1180.3350144338078));

   // intersect exit spiral in 2 locations
   cp1 = curve.PointOnCurve(length - 45);
   cp2 = curve.PointOnCurve(length - 35);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-883.61562936445966, 1183.8304112645556));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-890.74331577219289, 1190.8443728455015));


   // line tangent to circular curve
   POC = curve.PointOnCurve(length / 2);
   dir = curve.GetBearing(length / 2);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-703.20889, 1049.03367));

   // line intersect back tangent and exit spiral
   line.ThroughPoints(pbt, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-813.501198, 1119.948289));

   // again, but don't project back
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-813.501198, 1119.948289));

   // line intersect fwd tangent and entry spiral
   line.ThroughPoints(spi1, pft);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-507.50055, 1001.07029));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-1000.0, 1300.0));

   // again, but don't project ahead
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-507.50055, 1001.07029));

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1.Move(0, 900);
   cp2.Move(-700, 900);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(0, 1100);
   cp2.Move(-700, 1100);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-787.96427, 1099.99997));

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1.Move(0, 1500);
   cp2.Move(-700, 1500);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1200.0, 1500.0));

   // again, but don't project curve
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1.Move(-800, 1000);
   cp2.Move(-1100, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(-600, 1000);
   cp2.Move(-900, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-617.666636, 1017.666636));


   // again, but on inside of curve (intersect with projected tangent)
   cp1.Move(-200, 1000);
   cp2.Move(-500, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-200.0, 1000.0));

   // again, but don't project curve
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1.Move(0, 1000);
   cp2.Move(-1000, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-1000.0, 1300.0));

   // again, but project only back
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));

   // again, but project only ahead
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, 1300.0));

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1.Move(-690, 1000);
   cp2.Move(-710, 1010);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   TESTME_EPILOG("CompoundCurve::Test9a");
}

bool CompoundCurve::Test9b(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test9b");
   // same as Test9a except the direction of the curve is reverse

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // Spiral lengths overlap
   // PBT = (-1000,1300)
   // PI  = (-700,1000)
   // PFT = (0,1000)
   // R   = 500
   // Entry Spiral Length = 200
   // Exit Spiral Length = 100
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(-1000, 1300);
   WBFL::Geometry::Point2d pi(-700, 1000);
   WBFL::Geometry::Point2d pft(0,1000);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 200);
   curve.SetSpiralLength(SpiralLocation::Exit, 100);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);


   // create a line
   WBFL::Geometry::Line2d line;

   // get some useful curve points
   auto cc = curve.GetCC();
   auto spi1 = curve.GetSPI(SpiralLocation::Entry);
   auto spi2 = curve.GetSPI(SpiralLocation::Exit);

   // make line intersect exit spiral
   line.ThroughPoints(cc, spi2);
   auto vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-505.64225645686224, 1000.9854331731151));

   // make line intersect entry spiral
   line.ThroughPoints(cc, spi1);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-818.84459859920526, 1124.3794191254133));

   // make line intersect circular curve
   line.ThroughPoints(cc, pi);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-684.65428056880842, 1040.6952164811710));

   // intersect both spirals at once
   line.ThroughPoints(spi1, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-809.35182374575743, 1116.5668976835791));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-508.67043163106791, 1001.1261389033072));

   // intersect circular curve in two places
   // first locate two points on the curve
   Float64 length = curve.GetTotalLength();
   auto cp1 = curve.PointOnCurve(length - 140);
   auto cp2 = curve.PointOnCurve(length - 110);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-578.53372538212068, 1008.9111895010718));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-548.87503670886008, 1004.4287172526595));

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1 = curve.PointOnCurve(length - 151);
   cp2 = curve.PointOnCurve(length - 150);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-589.33347, 1010.99939));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-588.35360, 1010.79974));

   //// line tangent to exit spiral
   auto POC = curve.PointOnCurve(length - 50);
   auto dir = curve.GetBearing(length - 50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, 1000.41664));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, 1000.41664));

   // intersect entry spiral in 2 locations
   cp1 = curve.PointOnCurve(length - 45);
   cp2 = curve.PointOnCurve(length - 35);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-484.03375483745350, 1000.3037411037024));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-474.03507484100646, 1000.1429151347374));

   // line tangent to exit spiral
   POC = curve.PointOnCurve(50);
   dir = curve.GetBearing(50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, 1180.3350144338078));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, 1180.3350144338078));

   // intersect exit spiral in 2 locations
   cp1 = curve.PointOnCurve(35);
   cp2 = curve.PointOnCurve(45);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-890.74331577219289, 1190.8443728455015));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-883.61562929997831, 1183.8304112013673));

   // line tangent to circular curve
   POC = curve.PointOnCurve(length / 2);
   dir = curve.GetBearing(length/2);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-703.20889, 1049.03367));

   // line intersect back tangent and exit spiral
   line.ThroughPoints(pft, spi1);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-813.50119, 1119.94828));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(0.0, 1000.0));

   // again, but don't project back
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-813.50119, 1119.94828));

   // line intersect fwd tangent and entry spiral
   line.ThroughPoints(spi2, pbt);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, 1300.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-507.50055, 1001.07029));

   // again, but don't project ahead
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-507.50055, 1001.07029));

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1.Move(0, 900);
   cp2.Move(-700, 900);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(0, 1100);
   cp2.Move(-700, 1100);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-787.96427, 1099.99997));

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1.Move(0, 1500);
   cp2.Move(-700, 1500);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1200.0, 1500.0));

   // again, but don't project curve
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1.Move(-800, 1000);
   cp2.Move(-1100, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(-600, 1000);
   cp2.Move(-900, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-617.66664, 1017.66664));

   // again, but on inside of curve (intersect with projected tangent)
   cp1.Move(-200, 1000);
   cp2.Move(-500, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-200.0, 1000.0));

   // again, but don't project curve
   cp1.Move(-200, 1000);
   cp2.Move(-500, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1.Move(0, 1000);
   cp2.Move(-1000, 1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, 1300.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(0, 1000.0));

   // again, but project only back
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));

   // again, but project only ahead
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, 1300.0));

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1.Move(-690, 1000);
   cp2.Move(-710, 1010);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   TESTME_EPILOG("CompoundCurve::Test9b");
}

bool CompoundCurve::Test10a(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test10a");
   // same as Test8a except curve has been mirrored about the X axis

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // Spiral lengths overlap
   // PBT = (0,-1000)
   // PI  = (700,-1000)
   // PFT = (1000,-1300)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 200
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(0, -1000);
   WBFL::Geometry::Point2d pi(700, -1000);
   WBFL::Geometry::Point2d pft(1000, -1300);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 100);
   curve.SetSpiralLength(SpiralLocation::Exit, 200);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   // create a line
   WBFL::Geometry::Line2d line;

   // Important curve points
   auto cc = curve.GetCC();
   auto spi1 = curve.GetSPI(SpiralLocation::Entry);
   auto spi2 = curve.GetSPI(SpiralLocation::Exit);

   // make line intersect entry spiral
   line.ThroughPoints(cc, spi1);
   auto vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(505.64225645686224, -1000.9854331731150));

   // make line intersect exit spiral
   line.ThroughPoints(cc, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(818.84459859920526, -1124.3794191254133));

   // make line intersect circular curve
   line.ThroughPoints(cc, pi);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(684.65428056880842, -1040.6952164811710));

   // intersect both spirals at once
   line.ThroughPoints(spi1, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(508.67043163106791, -1001.1261389033072));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(809.35182374575743, -1116.5668976835791));

   // intersect circular curve in two places
   // first locate two points on the curve
   auto cp1 = curve.PointOnCurve(110);
   auto cp2 = curve.PointOnCurve(140);

   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(548.87503670886008, -1004.4287172526595));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(578.53372538212068, -1008.9111895010718));

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1 = curve.PointOnCurve(150);
   cp2 = curve.PointOnCurve(151);

   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(588.35360, -1010.79974));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(589.33347, -1010.99939));

   // line tangent to entry spiral
   auto POC = curve.PointOnCurve(50);
   auto dir = curve.GetBearing(50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(489.03247, -1000.41664));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(489.03247, -1000.41664));

   // intersect entry spiral in 2 locations
   cp1 = curve.PointOnCurve(35);
   cp2 = curve.PointOnCurve(45);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(474.03507484100646, -1000.1429151347374));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(484.03375483745350, -1000.3037411037024));

   // line tangent to exit spiral
   Float64 length = curve.GetTotalLength();
   POC = curve.PointOnCurve(length - 50);
   dir = curve.GetBearing(length - 50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, -1180.3350144338078));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, -1180.3350144338078));

   // intersect exit spiral in 2 locations
   cp1 = curve.PointOnCurve(length - 45);
   cp2 = curve.PointOnCurve(length - 35);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(883.61562936445966, -1183.8304112645556));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(890.74331577219289, -1190.8443728455015));

   // line tangent to circular curve
   POC = curve.PointOnCurve(length / 2);
   dir = curve.GetBearing(length / 2);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(703.20889, -1049.03367));

   // line intersect back tangent and exit spiral
   line.ThroughPoints(pbt, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(813.501198, -1119.948289));

   // again, but don't project back
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(813.501198, -1119.948289));

   // line intersect fwd tangent and entry spiral
   line.ThroughPoints(spi1, pft);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(507.50055, -1001.07029));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(1000.0, -1300.0));

   // again, but don't project ahead
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(507.50055, -1001.07029));

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1.Move(0, -900);
   cp2.Move(700, -900);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(0, -1100);
   cp2.Move(700, -1100);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(787.96427, -1099.99997));

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1.Move(0, -1500);
   cp2.Move(700, -1500);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1200.0, -1500.0));

   // again, but don't project curve
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1.Move(800, -1000);
   cp2.Move(1100, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(600, -1000);
   cp2.Move(900, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(617.666636, -1017.666636));

   // again, but on inside of curve (intersect with projected tangent)
   cp1.Move(200, -1000);
   cp2.Move(500, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(200.0, -1000.0));

   // again, but don't project curve
   cp1.Move(200, -1000);
   cp2.Move(500, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1.Move(0, -1000);
   cp2.Move(1000, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(1000.0, -1300.0));;

   // again, but project only back
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));

   // again, but project only ahead
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1000.0, -1300.0));

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1.Move(690, -1000);
   cp2.Move(710, -1010);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   TESTME_EPILOG("CompoundCurve::Test10a");
}

bool CompoundCurve::Test10b(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test10b");
   // same as Test10a except the direction of the curve is reverse

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // Spiral lengths overlap
   // PBT = (1000,-1300)
   // PI  = (700,-1000)
   // PFT = (0,-1000)
   // R   = 500
   // Entry Spiral Length = 200
   // Exit Spiral Length = 100
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(1000, -1300);
   WBFL::Geometry::Point2d pi(700, -1000);
   WBFL::Geometry::Point2d pft(0, -1000);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 200);
   curve.SetSpiralLength(SpiralLocation::Exit, 100);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   // create a line
   WBFL::Geometry::Line2d line;

   // Important curve points
   auto cc = curve.GetCC();
   auto spi1 = curve.GetSPI(SpiralLocation::Entry);
   auto spi2 = curve.GetSPI(SpiralLocation::Exit);

   // make line intersect exit spiral
   line.ThroughPoints(cc, spi2);
   auto vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(505.64225645686224, -1000.9854331731150));

   // make line intersect entry spiral
   line.ThroughPoints(cc, spi1);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(818.84459859920526, -1124.3794191254133));

   // make line intersect circular curve
   line.ThroughPoints(cc, pi);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(684.65428056880842, -1040.6952164811710));

   // intersect both spirals at once
   line.ThroughPoints(spi1, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(809.35182374575743, -1116.5668976835791));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(508.67043163106791, -1001.1261389033072));

   // intersect circular curve in two places
   // first locate two points on the curve
   Float64 length = curve.GetTotalLength();
   auto cp1 = curve.PointOnCurve(length - 140);
   auto cp2 = curve.PointOnCurve(length - 110);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(578.53372538212068, -1008.9111895010718));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(548.87503670886008, -1004.4287172526595));

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1 = curve.PointOnCurve(length - 151);
   cp2 = curve.PointOnCurve(length - 150);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(589.33347, -1010.99939));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(588.35360, -1010.79974));

   // line tangent to exit spiral
   auto POC = curve.PointOnCurve(length - 50);
   auto dir = curve.GetBearing(length - 50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(489.03247, -1000.41664));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(489.03247, -1000.41664));

   // intersect entry spiral in 2 locations
   cp1 = curve.PointOnCurve(length - 45);
   cp2 = curve.PointOnCurve(length - 35);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(484.03375483745350, -1000.3037411037024));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(474.03507484100646, -1000.1429151347374));

   // line tangent to exit spiral
   POC = curve.PointOnCurve(50);
   dir = curve.GetBearing(50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, -1180.3350144338078));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, -1180.3350144338078));

   // intersect exit spiral in 2 locations
   cp1 = curve.PointOnCurve(35);
   cp2 = curve.PointOnCurve(45);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(890.74331577219289, -1190.8443728455015));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(883.61562929997842, -1183.8304112013670));

   // line tangent to circular curve
   POC = curve.PointOnCurve(length / 2);
   dir = curve.GetBearing(length / 2);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(703.20889, -1049.03367));

   // line intersect back tangent and exit spiral
   line.ThroughPoints(pft, spi1);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(813.50119, -1119.94828));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(0.0, -1000.0));

   // again, but don't project ahead
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(813.50119, -1119.94828));

   // line intersect fwd tangent and entry spiral
   line.ThroughPoints(spi2, pbt);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1000.0,-1300.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(507.50056, -1001.07029));

   // again, but don't project back
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(507.50056, -1001.07029));

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1.Move(0, -900);
   cp2.Move(700, -900);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(0, -1100);
   cp2.Move(700, -1100);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(787.96427, -1099.99998));

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1.Move(0, -1500);
   cp2.Move(700, -1500);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1200.0, -1500.0));

   // again, but don't project curve
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1.Move(800, -1000);
   cp2.Move(1100, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(600, -1000);
   cp2.Move(900, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(617.66664, -1017.66664));

   // again, but on inside of curve (intersect with projected tangent)
   cp1.Move(200, -1000);
   cp2.Move(500, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(200.0, -1000.0));

   // again, but don't project curve
   cp1.Move(200, -1000);
   cp2.Move(500, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1.Move(0, -1000);
   cp2.Move(1000, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1000.0, -1300.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(0.0, -1000.0));

   // again, but project only ahead
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));

   // again, but project only back
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(1000.0, -1300.0));

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1.Move(690, -1000);
   cp2.Move(710, -1010);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   TESTME_EPILOG("CompoundCurve::Test10b");
}

bool CompoundCurve::Test11a(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test11a");
   // same as Test8 except curve has been mirrored about the X axis and the Y axis

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // Spiral lengths overlap
   // PBT = (0,-1000)
   // PI  = (-700,-1000)
   // PFT = (-1000,-1300)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 200
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(0, -1000);
   WBFL::Geometry::Point2d pi(-700, -1000);
   WBFL::Geometry::Point2d pft(-1000, -1300);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 100);
   curve.SetSpiralLength(SpiralLocation::Exit, 200);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Left);

   // create a line
   WBFL::Geometry::Line2d line;

   // Important curve points
   auto cc = curve.GetCC();
   auto spi1 = curve.GetSPI(SpiralLocation::Entry);
   auto spi2 = curve.GetSPI(SpiralLocation::Exit);

   // make line intersect entry spiral
   line.ThroughPoints(cc, spi1);
   auto vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-505.64225645686224, -1000.9854331731150));

   // make line intersect exit spiral
   line.ThroughPoints(cc, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-818.84459859920526, -1124.3794191254133));

   // make line intersect circular curve
   line.ThroughPoints(cc, pi);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-684.65428056880842, -1040.6952164811710));

   // intersect both spirals at once
   line.ThroughPoints(spi1, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-508.67043163106791, -1001.1261389033072));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-809.35182374575743, -1116.5668976835791));

   // intersect circular curve in two places
   // first locate two points on the curve
   auto cp1 = curve.PointOnCurve(110);
   auto cp2 = curve.PointOnCurve(140);
   line.ThroughPoints(cp1,cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-548.87503670886008, -1004.4287172526595));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-578.53372538212068, -1008.9111895010718));

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1 = curve.PointOnCurve(150);
   cp2 = curve.PointOnCurve(151);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-588.35360, -1010.79974));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-589.33347, -1010.99939));

   // line tangent to entry spiral
   auto POC = curve.PointOnCurve(50);
   auto dir = curve.GetBearing(50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, -1000.41664));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, -1000.41664));

   // intersect entry spiral in 2 locations
   cp1 = curve.PointOnCurve(35);
   cp2 = curve.PointOnCurve(45);
   line.ThroughPoints(cp1,cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-474.03507484100646, -1000.1429151347374));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-484.03375483745350, -1000.3037411037024));

   // line tangent to exit spiral
   Float64 length = curve.GetTotalLength();
   POC = curve.PointOnCurve(length - 50);
   dir = curve.GetBearing(length - 50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, -1180.3350144338078));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, -1180.3350144338078));

   // intersect exit spiral in 2 locations
   cp1 = curve.PointOnCurve(length - 45);
   cp2 = curve.PointOnCurve(length - 35);
   line.ThroughPoints(cp1,cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-883.61562929997842, -1183.8304112013670));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-890.74331577219289, -1190.8443728455015));

   // line tangent to circular curve
   POC = curve.PointOnCurve(length / 2);
   dir = curve.GetBearing(length / 2);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-703.20889, -1049.03367));

   // line intersect back tangent and exit spiral
   line.ThroughPoints(pbt, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-813.50119, -1119.94828));

   // again, but don't project back
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-813.50119, -1119.94828));

   // line intersect fwd tangent and entry spiral
   line.ThroughPoints(spi1, pft);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-507.50056, -1001.07029));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-1000.0, -1300.0));

   // again, but don't project ahead
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-507.50056, -1001.07029));

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1.Move(0, -900);
   cp2.Move(-700, -900);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(0, -1100);
   cp2.Move(-700, -1100);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-787.96427, -1099.99998));

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1.Move(0, -1500);
   cp2.Move(-700, -1500);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1200.0, -1500.0));

   // again, but don't project curve
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1.Move(-800, -1000);
   cp2.Move(-1100, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(-600, -1000);
   cp2.Move(-900, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-617.66664, -1017.66664));

   // again, but on inside of curve (intersect with projected tangent)
   cp1.Move(-200, -1000);
   cp2.Move(-500, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-200.0, -1000.0));

   // again, but don't project curve
   cp1.Move(-200, -1000);
   cp2.Move(-500, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1.Move(0, -1000);
   cp2.Move(-1000, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-1000.0, -1300.0));

   // again, but project only back
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));

   // again, but project only ahead
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, -1300.0));

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1.Move(-690, -1000);
   cp2.Move(-710, -1010);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   TESTME_EPILOG("CompoundCurve::Test11a");
}

bool CompoundCurve::Test11b(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompoundCurve::Test11b");
   // same as Test10b except the direction of the curve is reverse

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // Spiral lengths overlap
   // PBT = (-1000,-1300)
   // PI  = (-700,-1000)
   // PFT = (0,-1000)
   // R   = 500
   // Entry Spiral Length = 200
   // Exit Spiral Length = 100
   CompoundCurve curve;

   WBFL::Geometry::Point2d pbt(-1000, -1300);
   WBFL::Geometry::Point2d pi(-700, -1000);
   WBFL::Geometry::Point2d pft(0, -1000);

   curve.SetPBT(pbt);
   curve.SetPI(pi);
   curve.SetPFT(pft);

   curve.SetRadius(500);
   curve.SetSpiralLength(SpiralLocation::Entry, 200);
   curve.SetSpiralLength(SpiralLocation::Exit, 100);

   TRY_TESTME(curve.GetCurveDirection() == CurveDirection::Right);

   // create a line
   WBFL::Geometry::Line2d line;

   // Important curve points
   auto cc = curve.GetCC();
   auto spi1 = curve.GetSPI(SpiralLocation::Entry);
   auto spi2 = curve.GetSPI(SpiralLocation::Exit);

   // make line intersect exit spiral
   line.ThroughPoints(cc, spi2);
   auto vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-505.64225645686224, -1000.9854331731150));

   // make line intersect entry spiral
   line.ThroughPoints(cc, spi1);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-818.84459859920526, -1124.3794191254133));

   // make line intersect circular curve
   line.ThroughPoints(cc, pi);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-684.65428056880842, -1040.6952164811710));

   // intersect both spirals at once
   line.ThroughPoints(spi1, spi2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-809.35182374575743, -1116.5668976835791));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-508.67043163106791, -1001.1261389033072));

   // intersect circular curve in two places
   // first locate two points on the curve
   Float64 length = curve.GetTotalLength();
   auto cp1 = curve.PointOnCurve(length - 140);
   auto cp2 = curve.PointOnCurve(length - 110);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-578.53372538212068, -1008.9111895010718));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-548.87503670886008, -1004.4287172526595));

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   auto POC = curve.PointOnCurve(length - 50);
   auto dir = curve.GetBearing(length - 50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, -1000.41664));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, -1000.41664));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, -1000.41664));


   // intersect entry spiral in 2 locations
   cp1 = curve.PointOnCurve(length - 45);
   cp2 = curve.PointOnCurve(length - 35);
   line.ThroughPoints(cp1,cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-484.03375483745350, -1000.3037411037024));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-474.03507484100646, -1000.1429151347374));

   // line tangent to exit spiral
   POC = curve.PointOnCurve(50);
   dir = curve.GetBearing(50);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, -1180.3350144338078));

   // reverse the direction of the tangent line
   dir.Increment(M_PI);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, -1180.3350144338078));

   // intersect exit spiral in 2 locations
   cp1 = curve.PointOnCurve(35);
   cp2 = curve.PointOnCurve(45);
   line.ThroughPoints(cp1,cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-890.74331577219289, -1190.8443728455015));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-883.61562929997842, -1183.8304112013670));


   // line tangent to circular curve
   POC = curve.PointOnCurve(length / 2);
   dir = curve.GetBearing(length / 2);
   line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-703.20889, -1049.03367));

   // line intersect back tangent and exit spiral
   line.ThroughPoints(pft, spi1);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-813.50119, -1119.94828));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(0.0, -1000.0));

   // again, but don't project back
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-813.50119, -1119.94828));

   // line intersect fwd tangent and entry spiral
   line.ThroughPoints(spi2, pbt);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, -1300.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(-507.50056, -1001.07029));

   // again, but don't project ahead
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-507.50056, -1001.07029));

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1.Move(0, -900);
   cp2.Move(-700, -900);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(0, -1100);
   cp2.Move(-700, -1100);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-787.96427, -1099.99998));

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1.Move(0, -1500);
   cp2.Move(-700, -1500);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1200.0, -1500.0));

   // again, but don't project curve
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1.Move(-800, -1000);
   cp2.Move(-1100, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // again, but on inside of curve (intersect with curve)
   cp1.Move(-600, -1000);
   cp2.Move(-900, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-617.66664, -1017.66664));

   // again, but on inside of curve (intersect with projected tangent)
   cp1.Move(-200, -1000);
   cp2.Move(-500, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-200.0, -1000.0));

   // again, but don't project curve
   cp1.Move(-200, -1000);
   cp2.Move(-500, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1.Move(0, -1000);
   cp2.Move(-1000, -1300);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   vPoints = curve.Intersect(line, true, true);
   TRY_TESTME(vPoints.size() == 2);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, -1300.0));
   TRY_TESTME(vPoints.back() == WBFL::Geometry::Point2d(0.0, -1000.0));

   // again, but project only back
   vPoints = curve.Intersect(line, false, true);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));

   // again, but project only ahead
   vPoints = curve.Intersect(line, true, false);
   TRY_TESTME(vPoints.size() == 1);
   TRY_TESTME(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, -1300.0));

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1.Move(-690, -1000);
   cp2.Move(-710, -1010);
   line.ThroughPoints(cp1, cp2);
   vPoints = curve.Intersect(line, false, false);
   TRY_TESTME(vPoints.size() == 0);

   TESTME_EPILOG("CompoundCurve::Test11b");
}

#endif // _UNITTEST
