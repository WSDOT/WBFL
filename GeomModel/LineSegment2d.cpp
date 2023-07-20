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
#include <GeomModel/LineSegment2d.h>
#include <math.h>
#include <iostream>
#include <MathEx.h>

using namespace WBFL::Geometry;

LineSegment2d::LineSegment2d(const Point2d& start, const Point2d& end) :
   m_Start(start), m_End(end)
{
}

LineSegment2d::LineSegment2d(Float64 x1,Float64 y1, Float64 x2,Float64 y2)
{
   m_Start.Move(x1, y1);
   m_End.Move(x2, y2);
}

LineSegment2d::LineSegment2d(const Point2d& start, const Size2d& relEnd)
{
   m_Start.Move(start);
   m_End.Move(m_Start.X() + relEnd.Dx(), m_Start.Y() + relEnd.Dy());
}

bool LineSegment2d::operator==(const LineSegment2d& other) const
{
   return (GetStartPoint() == other.GetStartPoint() && GetEndPoint() == other.GetEndPoint());
}

bool LineSegment2d::operator!=(const LineSegment2d& other) const
{
   return !(*this == other);
}

void LineSegment2d::ThroughPoints(const Point2d& start, const Point2d& end)
{
   m_Start.Move(start);
   m_End.Move(end);
}

bool LineSegment2d::ContainsPoint(const Point2d& point,Float64 tol) const
{
   // adopted implementation from unidraw's LineObj class and added tolerance. We might
   // want to consider having a global geometric tolerance for the gp package.
   
	if ((point.X() >= Min(m_Start.X(), m_End.X())-tol) && 
       (point.X() <= Max(m_Start.X(), m_End.X())+tol) &&
	    (point.Y() >= Min(m_Start.Y(), m_End.Y())-tol) && 
       (point.Y() <= Max(m_Start.Y(), m_End.Y())+tol))
   {
      Float64 prod = (point.Y() - m_Start.Y())*(m_End.X() - m_Start.X()) - 
                     (m_End.Y() - m_Start.Y() )*(point.X() - m_Start.X());

      if (IsZero(prod,tol))
         return true;
      else
         return false;
   }
   else
      return false;
}

Float64 LineSegment2d::Length() const
{
   return m_Start.Distance(m_End);
}

void LineSegment2d::SetStartPoint(const Point2d& startPoint)
{
   m_Start.Move(startPoint);
}

const Point2d& LineSegment2d::GetStartPoint() const
{
   return m_Start;
}

void LineSegment2d::SetEndPoint(const Point2d& endPoint)
{
   m_End.Move(endPoint);
}

const Point2d& LineSegment2d::GetEndPoint() const
{
   return m_End;
}

Point2d LineSegment2d::GetMidPoint() const
{
   Size2d size = m_End - m_Start;
   size /= 2;
   return m_Start + size;
}

LineSegment2d& LineSegment2d::Offset(Float64 distance)
{
   Size2d size = m_End - m_Start;
   auto length = size.Magnitude();
   Float64 ox = 0;
   Float64 oy = 0;
   if (!IsZero(length))
   {
      ox =  distance * size.Dy() / length;
      oy = -distance * size.Dx() / length;
   }
   return Offset(ox, oy);
}

LineSegment2d LineSegment2d::OffsetBy(Float64 distance) const
{
   LineSegment2d t(*this);
   return t.Offset(distance);
}

LineSegment2d& LineSegment2d::Offset(Float64 dx,Float64 dy)
{
   m_Start.X() += dx;
   m_Start.Y() += dy;
   m_End.X() += dx;
   m_End.Y() += dy;
   return *this;
}

LineSegment2d& LineSegment2d::Offset(const Size2d& size)
{
   return Offset(size.Dx(), size.Dy());
}

LineSegment2d LineSegment2d::OffsetBy(Float64 dx, Float64 dy) const
{
   LineSegment2d t(*this);
   return t.Offset(dx,dy);
}

LineSegment2d LineSegment2d::OffsetBy(const Size2d& size) const
{
   LineSegment2d t(*this);
   return t.Offset(size);
}

LineSegment2d& LineSegment2d::Rotate(const Point2d& centerPoint, Float64 angle)
{
   m_Start.Rotate(centerPoint, angle);
   m_End.Rotate(centerPoint, angle);
   return *this;

}

LineSegment2d LineSegment2d::RotateBy(const Point2d& centerPoint, Float64 angle) const
{
   LineSegment2d t(*this);
   return t.Rotate(centerPoint, angle);
}

std::vector<Point2d> LineSegment2d::Divide(IndexType nSpaces) const
{
   if (nSpaces == 0 || nSpaces == INVALID_INDEX)
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG);

   std::vector<Point2d> points;
   Size2d size = m_End - m_Start;
   Size2d delta = size/(Float64)nSpaces;
   for ( IndexType i = 0; i < nSpaces + 1; i++ )
   {
      Point2d p = m_Start + (Float64)i*delta;
      points.push_back( p );
   }

   return points;
}
