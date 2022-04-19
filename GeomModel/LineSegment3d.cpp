///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

LineSegment3d::LineSegment3d()
{
}

LineSegment3d::LineSegment3d(const LineSegment3d& other)
{
   m_pStart = std::make_shared<Point3d>(*other.m_pStart);
   m_pEnd = std::make_shared<Point3d>(*other.m_pEnd);
}

LineSegment3d& LineSegment3d::operator=(const LineSegment3d& other)
{
   if (this != &other)
   {
      m_pStart = std::make_shared<Point3d>(*other.m_pStart);
      m_pEnd = std::make_shared<Point3d>(*other.m_pEnd);
   }
   return *this;
}

LineSegment3d::LineSegment3d(std::shared_ptr<Point3d>& start, std::shared_ptr<Point3d>& end):
m_pStart(start),
m_pEnd(end)
{
}

LineSegment3d::LineSegment3d(Float64 x1,Float64 y1, Float64 z1, Float64 x2,Float64 y2, Float64 z2)
{
   m_pStart->Move(x1, y1, z1);
   m_pEnd->Move(x2, y2, z2);
}

LineSegment3d::LineSegment3d(std::shared_ptr<Point3d>& start, const Size3d& relEnd):
m_pStart(start)
{
   m_pEnd->Move(m_pStart->X() + relEnd.Dx(), m_pStart->Y() + relEnd.Dy(), m_pStart->Z() + relEnd.Dz());
}

LineSegment3d::LineSegment3d(const Point3d& start, const Size3d& relEnd)
{
   m_pStart->Move(start);
   m_pEnd->Move(m_pStart->X() + relEnd.Dx(), m_pStart->Y() + relEnd.Dy(), m_pStart->Z() + relEnd.Dz());
}

LineSegment3d::~LineSegment3d()
{
}

bool LineSegment3d::operator==(const LineSegment3d& other) const
{
   return (GetStartPoint() == other.GetStartPoint() && GetEndPoint() == other.GetEndPoint());
}

bool LineSegment3d::operator!=(const LineSegment3d& other) const
{
   return !(*this == other);
}

void LineSegment3d::ThroughPoints(std::shared_ptr<Point3d>& start, std::shared_ptr<Point3d>& end)
{
   m_pStart = start;
   m_pEnd = end;
}

void LineSegment3d::ThroughPoints(const Point3d& start, const Point3d& end)
{
   m_pStart->Move(start);
   m_pEnd->Move(end);
}

Float64 LineSegment3d::GetLength() const
{
   return m_pStart->Distance(*m_pEnd);
}

void LineSegment3d::SetStartPoint (std::shared_ptr<Point3d>& p)
{
   m_pStart = p;
}

std::shared_ptr<Point3d>& LineSegment3d::GetStartPoint()
{
   return m_pStart;
}

const std::shared_ptr<Point3d>& LineSegment3d::GetStartPoint() const
{
   return m_pStart;
}

void LineSegment3d::SetEndPoint(std::shared_ptr<Point3d>& p)
{
   m_pEnd = p;
}

std::shared_ptr<Point3d>& LineSegment3d::GetEndPoint()
{
   return m_pEnd;
}

const std::shared_ptr<Point3d>& LineSegment3d::GetEndPoint() const
{
   return m_pEnd;
}

Point3d LineSegment3d::GetMidPoint() const
{
   Size3d size = *m_pEnd - *m_pStart;
   size /= 2;
   return *m_pStart + size;
}

LineSegment3d& LineSegment3d::Offset(Float64 dx,Float64 dy,Float64 dz)
{
   m_pStart->Offset(dx, dy, dz);
   m_pEnd->Offset(dx, dy, dz);
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
   Size3d size = *m_pEnd - *m_pStart;
   Size3d delta = size/nSpaces;
   for ( Uint16 i = 0; i < nSpaces + 1; i++ )
   {
      Point3d p = *m_pStart + i*delta;
      points.push_back( p );
   }

   return points;
}

Float64 LineSegment3d::DistanceToPoint(const Point3d& p) const
{
   //https://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
   Vector3d v0(p);
   Vector3d v1(*m_pStart);
   Vector3d v2(*m_pEnd);

   auto vd = (v2 - v1).Cross(v1 - v0);
   auto vn = (v2 - v1);
   Float64 dist = vd.GetMagnitude() / vn.GetMagnitude();
   return dist;
}

#if defined _DEBUG
bool LineSegment3d::AssertValid() const
{
   return true;
}

void LineSegment3d::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for LineSegment3d") << endl;
   os << _T("  m_pStart = (")<< m_pStart->X()<<_T(", ")<< m_pStart->Y() <<_T(", ") << m_pStart->Z() << _T(")") << endl;
   os << _T("  m_End = (")<< m_pEnd->X()<<_T(", ")<< m_pEnd->Y() << _T(", ") << m_pEnd->Z() << _T(")") << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool LineSegment3d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("LineSegment3d");


   //
   // Test Length property
   //
   LineSegment3d seg(10, 10, 10, 20, 20, 20);
   Float64 length = seg.GetLength();
   TRY_TESTME(IsEqual(length, 17.320508));

   //
   // Test Offset method
   //
   seg.Offset(-10, -10, 0);
   TRY_TESTME(IsEqual(seg.GetStartPoint()->X(), 0.0));
   TRY_TESTME(IsEqual(seg.GetStartPoint()->Y(), 0.0));
   TRY_TESTME(IsEqual(seg.GetStartPoint()->Z(), 10.0));
   TRY_TESTME(IsEqual(seg.GetEndPoint()->X(), 10.0));
   TRY_TESTME(IsEqual(seg.GetEndPoint()->Y(), 10.0));
   TRY_TESTME(IsEqual(seg.GetEndPoint()->Z(), 20.0));

   seg.GetStartPoint()->Move(10, 10, 10);
   seg.GetEndPoint()->Move(20, 20, 20);

   auto midpoint = seg.GetMidPoint();
   TRY_TESTME(IsEqual(midpoint.X(), 15.0));
   TRY_TESTME(IsEqual(midpoint.Y(), 15.0));
   TRY_TESTME(IsEqual(midpoint.Z(), 15.0));

   TESTME_EPILOG("LineSegment3d");
}
#endif // _UNITTEST


