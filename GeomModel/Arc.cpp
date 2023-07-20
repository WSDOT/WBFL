///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/Arc.h>
#include <GeomModel/LineSegment2d.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/Vector2d.h>
#include <MathEx.h>

using namespace WBFL::Geometry;

Arc::Arc() :
m_Start(0,0),
m_Center(0,0),
m_End(0,0)
{
}

Arc::Arc(const Point2d& start,const Point2d& center, const Point2d& end) :
m_Start(start),
m_Center(center),
m_End(end)
{
}

Arc::~Arc()
{
}

void Arc::SetStart(const Point2d& start)
{
   m_Start = start;
}

Point2d& Arc::GetStart()
{
   return m_Start;
}

const Point2d& Arc::GetStart() const
{
   return m_Start;
}

void Arc::SetCenter(const Point2d& center)
{
   m_Center = center;
}

Point2d& Arc::GetCenter()
{
   return m_Center;
}

const Point2d& Arc::GetCenter() const
{
   return m_Center;
}

void Arc::SetEnd(const Point2d& end)
{
   m_End = end;
}

Point2d& Arc::GetEnd()
{
   return m_End;
}

const Point2d& Arc::GetEnd() const
{
   return m_End;
}

void Arc::Reverse()
{
   Point2d tmp = m_Start;
   m_Start = m_End;
   m_End = tmp;
}

Float64 Arc::GetRadius() const
{
   return m_Center.Distance(m_Start);
}

Float64 Arc::GetLength() const
{
   return Distance(m_End);
}

Float64 Arc::Distance(const Point2d& p) const
{
   Vector2d v1(m_Center,m_Start);
   Vector2d v2(m_Center,p);
   Float64 delta = v2.AngleBetween(v1);
   Float64 radius = GetRadius();
   Float64 distance = delta*radius;
   return distance;
}

Float64 Arc::GetCentralAngle() const
{
   Vector2d v1(m_Center,m_Start);
   Vector2d v2(m_Center,m_End);
   Float64 delta = v2.AngleBetween(v1);

   Line2d line(m_Center,v1);
   if ( line.GetSide(m_End) == Line2d::Side::Right )
      delta = TWO_PI - delta;

   return delta;
}

bool Arc::IsPointOnArc(const Point2d& p) const
{
   Float64 dist = m_Center.Distance(p);
   Float64 radius = GetRadius();
   if ( !IsEqual(dist,radius) )
      return false;

   Line2d l1(m_Center,m_Start);
   Line2d l2(m_Center,m_End);

   Line2d::Side side1 = l1.GetSide(p);
   Line2d::Side side2 = l2.GetSide(p);

   if ( side1 == Line2d::Side::Left && side2 == Line2d::Side::Right )
   {
      return true;
   }

   // Because of the way lines determine left and right, there is a special case
   // of a point that is exactly at the end of the arc.  Such a point is considered
   // on the arc, but the above test doesn't correctly detect that case.  Make a
   // check here for that special case
   if ( p == m_End )
      return true;

   return false;
}

std::vector<Point2d> Arc::Divide(IndexType nSpaces) const
{
   if (nSpaces < 1 || nSpaces == INVALID_INDEX)
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG);

   std::vector<Point2d> vPoints;

   Float64 sx, sy; // Start Point
   Float64 cx, cy; // Center Point
   Float64 ex, ey; // End point
   Float64 radius; // Radius (measured center to start)
   Float64 dir;    // Direction of start vector measured from Y = 0 (+X)

   std::tie(sx,sy) = m_Start.GetLocation();
   std::tie(cx,cy) = m_Center.GetLocation();
   std::tie(ex,ey) = m_End.GetLocation();

   radius = sqrt(pow(sx - cx, 2) + pow(sy - cy, 2));

   dir = atan2(sy - cy, sx - cx);

   Float64 sweep_angle = GetCentralAngle();
   Float64 delta_angle = sweep_angle / nSpaces;

   vPoints.emplace_back(m_Start);

   for (IndexType i = 0; i < nSpaces - 1; i++)
   {
      Float64 angle = dir + (i + 1) * delta_angle;
      Float64 dx = radius * cos(angle);
      Float64 dy = radius * sin(angle);
      Float64 x = cx + dx;
      Float64 y = cy + dy;

      vPoints.emplace_back(x, y);
   }

   vPoints.emplace_back(m_End);
   return vPoints;
}

bool Arc::operator==(const Arc& other) const
{
   return IsEqual(GetRadius(),other.GetRadius()) && GetCenter() == other.GetCenter();
}

bool Arc::operator!=(const Arc& other) const
{
   return !(*this == other);
}
