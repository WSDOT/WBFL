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

#if defined _DEBUG
bool LineSegment2d::AssertValid() const
{
   return true;
}

void LineSegment2d::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for LineSegment2d") << WBFL::Debug::endl;
   os << _T("  m_pStart = (")<< m_Start.X()<<_T(", ")<< m_Start.Y()<<_T(")")<< WBFL::Debug::endl;
   os << _T("  m_pEnd = (")<< m_End.X()<<_T(", ")<< m_End.Y()<<_T(")")<< WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool LineSegment2d::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("LineSegment2d");

   const Point2d p0_0(0,0), p1_1(1,1), p0_1(0,1), p1_4(1,4), p0_3(0,3),pn3_0(-3,0);
   const Point2d p4_1(4,1), pn1_2(-1,2), pn1_0(-1,0), p0_6(0,6);
   const LineSegment2d up(p0_0, p0_6), down(p0_1, p0_0), left(p0_1,p4_1);
   const LineSegment2d at45(pn3_0,p1_4);
   const LineSegment2d atn45(p1_4,Size2d(-4,-4));
   LineSegment2d ltemp1, ltemp2;

   // get/set endpoints
   TRY_TESTME(at45.GetEndPoint()   == p1_4);
   TRY_TESTME(at45.GetStartPoint() == pn3_0);
   ltemp1 = at45;
   ltemp1.SetEndPoint(pn1_0);
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-2,0)));
   ltemp1.SetStartPoint(Point2d(1,-4));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(0,-2)));

   // Length
   TRY_TESTME (up.Length()    == 6);
   TRY_TESTME (left.Length()  == 4);
   TRY_TESTME (at45.Length()  == sqrt(32.));
   TRY_TESTME (atn45.Length() == sqrt(32.));

   // ContainsPoint
   TRY_TESTME (at45.ContainsPoint(p1_4));
   TRY_TESTME (atn45.ContainsPoint(p0_3));
   TRY_TESTME (at45.ContainsPoint(pn1_2));
   TRY_TESTME (atn45.ContainsPoint(pn1_2));
   TRY_TESTME (up.ContainsPoint(Point2d(0,.5)));
   TRY_TESTME (up.ContainsPoint(p0_0));
   TRY_TESTME (left.ContainsPoint(Point2d(.5,1)));
   TRY_TESTME (left.ContainsPoint(Point2d(0,1)));

   Point2d p1(-10, -10);
   Point2d p2(-50, 20);
   LineSegment2d seg1(p1, p2);
   Point2d p3(-30, 5);
   Point2d p4(0, 0);
   TRY_TESTME(seg1.ContainsPoint(p3, 1.0e-6));
   TRY_TESTME(!seg1.ContainsPoint(p4, 1.0e-6));
   TRY_TESTME(seg1.ContainsPoint(p1, 1.0e-6));
   TRY_TESTME(seg1.ContainsPoint(p2, 1.0e-6));

   // offset - offsetby
   Point2d ptest;
   ltemp1 = at45.OffsetBy(-1,0);
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-2,2)));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(0,4)));
   ltemp2 = at45.OffsetBy(0,1);
   TRY_TESTME (ltemp1 != ltemp2); // should not be equal
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-2,2)));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(0,4)));
   ltemp1 = at45.OffsetBy(1,1);  // offset in direction of line
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(1,4)));


   // rotate
   ltemp1 = left.RotateBy(Point2d(-2,1),atan(1.));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(1,4)));
   ltemp1 = up.RotateBy(Point2d(0,3),-atan(1.));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(1,4)));
   ltemp1 = left.RotateBy(Point2d(-2,1),5*atan(1.));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-5,-2)));
   
#if defined _DEBUG
   at45.Dump(rlog.GetLogContext());
#endif

   // divide
   std::vector<Point2d> points;
   std::vector<Point2d> correct_points;
   LineSegment2d div_line(Point2d(0,0),Point2d(10,10));
   points = div_line.Divide(2);
   correct_points.emplace_back(0,0);
   correct_points.emplace_back(5,5);
   correct_points.emplace_back(10,10);
   TRY_TESTME ( points == correct_points );

   correct_points.clear();
   correct_points.emplace_back(0,0);
   correct_points.emplace_back(-5,-5);
   correct_points.emplace_back(-10,-10);
   div_line.SetEndPoint(Point2d( -10,-10 ));
   points = div_line.Divide(2);
   TRY_TESTME ( points == correct_points );

   //
   // DivideLineSegment
   //
   p1.Move(10, 10);
   p2.Move(30, 30);
   seg1.SetStartPoint(p1);
   seg1.SetEndPoint(p2);
   points = seg1.Divide(1);
   TRY_TESTME(points.size() == 2);

   points = seg1.Divide(4);
   TRY_TESTME(points.size() == 5);

   TRY_TESTME(points[0] == Point2d(10, 10));
   TRY_TESTME(points[1] == Point2d(15, 15));
   TRY_TESTME(points[2] == Point2d(20, 20));
   TRY_TESTME(points[3] == Point2d(25, 25));
   TRY_TESTME(points[4] == Point2d(30, 30));

   TESTME_EPILOG("LineSegment2d");
}
#endif // _UNITTEST


