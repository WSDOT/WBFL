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
#include <GeomModel/LineSegment3d.h>
#include <GeomModel/Vector3d.h>
#include <math.h>
#include <iostream>
#include <MathEx.h>

using namespace WBFL::Geometry;

LineSegment3d::LineSegment3d(Float64 x1,Float64 y1, Float64 z1, Float64 x2,Float64 y2, Float64 z2)
{
   m_Start.Move(x1, y1, z1);
   m_End.Move(x2, y2, z2);
}

LineSegment3d::LineSegment3d(const Point3d& start, const Point3d& end) :
m_Start(start), m_End(end)
{
}

LineSegment3d::LineSegment3d(const Point3d& start, const Size3d& relEnd)
{
   m_Start.Move(start);
   m_End.Move(m_Start.X() + relEnd.Dx(), m_Start.Y() + relEnd.Dy(), m_Start.Z() + relEnd.Dz());
}

bool LineSegment3d::operator==(const LineSegment3d& other) const
{
   return (GetStartPoint() == other.GetStartPoint() && GetEndPoint() == other.GetEndPoint());
}

bool LineSegment3d::operator!=(const LineSegment3d& other) const
{
   return !(*this == other);
}

void LineSegment3d::ThroughPoints(const Point3d& start, const Point3d& end)
{
   m_Start = start;
   m_End = end;
}

Float64 LineSegment3d::Length() const
{
   return m_Start.Distance(m_End);
}

void LineSegment3d::SetStartPoint(const Point3d& p)
{
   m_Start = p;
}

const Point3d& LineSegment3d::GetStartPoint() const
{
   return m_Start;
}

void LineSegment3d::SetEndPoint(const Point3d& p)
{
   m_End = p;
}

const Point3d& LineSegment3d::GetEndPoint() const
{
   return m_End;
}

Point3d LineSegment3d::GetMidPoint() const
{
   Size3d size = m_End - m_Start;
   size /= 2;
   return m_Start + size;
}

LineSegment3d& LineSegment3d::Offset(Float64 dx,Float64 dy,Float64 dz)
{
   m_Start.Offset(dx, dy, dz);
   m_End.Offset(dx, dy, dz);
   return *this;
}

LineSegment3d& LineSegment3d::Offset(const Size3d& size)
{
   return Offset(size.Dx(), size.Dy(), size.Dz());
}

LineSegment3d LineSegment3d::OffsetBy(Float64 dx, Float64 dy,Float64 dz) const
{
   LineSegment3d t(*this);
   return t.Offset(dx,dy,dz);
}

LineSegment3d LineSegment3d::OffsetBy(const Size3d& size) const
{
   LineSegment3d t(*this);
   return t.Offset(size);
}

std::vector<Point3d> LineSegment3d::Divide(Uint16 nSpaces) const
{
   std::vector<Point3d> points;
   Size3d size = m_End - m_Start;
   Size3d delta = size/nSpaces;
   for ( Uint16 i = 0; i < nSpaces + 1; i++ )
   {
      Point3d p = m_Start + i*delta;
      points.push_back( p );
   }

   return points;
}

Float64 LineSegment3d::DistanceToPoint(const Point3d& p) const
{
   //https://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
   Vector3d v0(p);
   Vector3d v1(m_Start);
   Vector3d v2(m_End);

   auto vd = (v2 - v1).Cross(v1 - v0);
   auto vn = (v2 - v1);
   Float64 dist = vd.GetMagnitude() / vn.GetMagnitude();
   return dist;
}
