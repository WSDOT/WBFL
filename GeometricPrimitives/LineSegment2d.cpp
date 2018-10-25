///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2011  Washington State Department of Transportation
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

#include <GeometricPrimitives\GeometryLib.h>
#include <GeometricPrimitives\LineSegment2d.h>
#include <math.h>
#include <iostream>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gpLineSegment2d
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpLineSegment2d::gpLineSegment2d()
{
}

gpLineSegment2d::gpLineSegment2d(const gpPoint2d& start, const gpPoint2d& end):
m_P1(start),
m_P2(end)
{
}

gpLineSegment2d::gpLineSegment2d(Float64 x1,Float64 y1, Float64 x2,Float64 y2):
m_P1(x1,y1),
m_P2(x2,y2)
{
}

gpLineSegment2d::gpLineSegment2d(const gpPoint2d& start, const gpSize2d& relEnd):
m_P1(start),
m_P2(start.X()+relEnd.Dx(),start.Y()+relEnd.Dy())
{
}


gpLineSegment2d::gpLineSegment2d(const gpLineSegment2d& rOther)
{
   MakeCopy(rOther);
}

gpLineSegment2d::~gpLineSegment2d()
{
}

//======================== OPERATORS  =======================================
gpLineSegment2d& gpLineSegment2d::operator= (const gpLineSegment2d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

bool gpLineSegment2d::Contains(const gpPoint2d& point,Float64 tol) const
{
   // stole implemenation from unidraw's LineObj class and added tolerance. We might
   // want to consider having a global geometric tolerance for the gp package.
   
	if ((point.X() >= _cpp_min(m_P1.X(), m_P2.X())-tol) && 
       (point.X() <= _cpp_max(m_P1.X(), m_P2.X())+tol) &&
	    (point.Y() >= _cpp_min(m_P1.Y(), m_P2.Y())-tol) && 
       (point.Y() <= _cpp_max(m_P1.Y(), m_P2.Y())+tol))
   {
      Float64 prod = (point.Y() - m_P1.Y())*(m_P2.X() - m_P1.X()) - 
                     (m_P2.Y() - m_P1.Y() )*(point.X() - m_P1.X());

      if (IsZero(prod,tol))
         return true;
      else
         return false;
   }
   else
      return false;
}

Float64 gpLineSegment2d::Length() const
{
   return m_P1.Distance(m_P2);
}


void gpLineSegment2d::SetStartPoint (const gpPoint2d& p)
{
   m_P1 = p;
}

gpPoint2d gpLineSegment2d::GetStartPoint() const
{
   return m_P1;
}

void gpLineSegment2d::SetEndPoint(const gpPoint2d& p)
{
   m_P2 = p;
}

gpPoint2d gpLineSegment2d::GetEndPoint() const
{
   return m_P2;
}

gpPoint2d gpLineSegment2d::GetMidPoint() const
{
   gpSize2d size = m_P2 - m_P1;
   size /= 2;
   return m_P1 + size;
}

gpLineSegment2d& gpLineSegment2d::Offset(Float64 dx,Float64 dy)
{
   m_P1.X() += dx;
   m_P1.Y() += dy;
   m_P2.X() += dx;
   m_P2.Y() += dy;
   return *this;
}

gpLineSegment2d& gpLineSegment2d::Offset(const gpSize2d& size)
{
   return Offset(size.Dx(), size.Dy());
}

gpLineSegment2d gpLineSegment2d::OffsetBy(Float64 dx, Float64 dy) const
{
   gpLineSegment2d t(*this);
   return t.Offset(dx,dy);
}

gpLineSegment2d gpLineSegment2d::OffsetBy(const gpSize2d& size) const
{
   gpLineSegment2d t(*this);
   return t.Offset(size);
}


gpLineSegment2d& gpLineSegment2d::Rotate(const gpPoint2d& centerPoint, Float64 angle)
{
   m_P1.Rotate(centerPoint, angle);
   m_P2.Rotate(centerPoint, angle);
   return *this;

}


gpLineSegment2d gpLineSegment2d::RotateBy(const gpPoint2d& centerPoint, Float64 angle) const
{
   gpLineSegment2d t(*this);
   return t.Rotate(centerPoint, angle);
}

std::vector<gpPoint2d> gpLineSegment2d::Divide(Uint16 nSpaces) const
{
   std::vector<gpPoint2d> points;
   gpSize2d size = m_P2 - m_P1;
   gpSize2d delta = size/nSpaces;
   for ( Uint16 i = 0; i < nSpaces + 1; i++ )
   {
      gpPoint2d p = m_P1 + i*delta;
      points.push_back( p );
   }

   return points;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gpLineSegment2d::AssertValid() const
{
   return true;
}

void gpLineSegment2d::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for gpLineSegment2d") << endl;
   os << _T("  m_P1 = (")<< m_P1.X()<<_T(", ")<< m_P1.Y()<<_T(")")<<endl;
   os << _T("  m_P2 = (")<< m_P2.X()<<_T(", ")<< m_P2.Y()<<_T(")")<<endl;
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpLineSegment2d::MakeCopy(const gpLineSegment2d& rOther)
{
   m_P1 = rOther.m_P1;
   m_P2 = rOther.m_P2;
}

void gpLineSegment2d::MakeAssignment(const gpLineSegment2d& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

bool operator==(const gpLineSegment2d& lhs, const gpLineSegment2d& rhs)
{
   return (lhs.GetStartPoint()==rhs.GetStartPoint() && lhs.GetEndPoint()==rhs.GetEndPoint());
}

bool operator!=(const gpLineSegment2d& lhs, const gpLineSegment2d& rhs)
{
   return !(lhs==rhs);
}

#if defined _UNITTEST
bool gpLineSegment2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpLineSegment2d");

   const gpPoint2d p0_0(0,0), p1_1(1,1), p0_1(0,1), p1_4(1,4), p0_3(0,3),pn3_0(-3,0);
   const gpPoint2d p4_1(4,1), pn1_2(-1,2), pn1_0(-1,0), p0_6(0,6);
   const gpLineSegment2d up(p0_0, p0_6), down(p0_1, p0_0), left(p0_1,p4_1);
   const gpLineSegment2d at45(pn3_0,p1_4);
   const gpLineSegment2d atn45(p1_4,gpSize2d(-4,-4));
   gpLineSegment2d ltemp1, ltemp2;

   // get/set endpoints
   TRY_TESTME (at45.GetEndPoint()   == p1_4);
   TRY_TESTME (at45.GetStartPoint() == pn3_0);
   ltemp1 = at45;
   ltemp1.SetEndPoint(pn1_0);
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-2,0)));
   ltemp1.SetStartPoint(gpPoint2d(1,-4));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(0,-2)));

   // Length
   TRY_TESTME (up.Length()    == 6);
   TRY_TESTME (left.Length()  == 4);
   TRY_TESTME (at45.Length()  == sqrt(32.));
   TRY_TESTME (atn45.Length() == sqrt(32.));

   // contains
   TRY_TESTME (at45.Contains(p1_4));
   TRY_TESTME (atn45.Contains(p0_3));
   TRY_TESTME (at45.Contains(pn1_2));
   TRY_TESTME (atn45.Contains(pn1_2));
   TRY_TESTME (up.Contains(gpPoint2d(0,.5)));
   TRY_TESTME (up.Contains(p0_0));
   TRY_TESTME (left.Contains(gpPoint2d(.5,1)));
   TRY_TESTME (left.Contains(gpPoint2d(0,1)));

   // offset - offsetby
   gpPoint2d ptest;
   ltemp1 = at45.OffsetBy(-1,0);
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-2,2)));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(0,4)));
   ltemp2 = at45.OffsetBy(0,1);
   TRY_TESTME (ltemp1 != ltemp2); // should not be equal
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-2,2)));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(0,4)));
   ltemp1 = at45.OffsetBy(1,1);  // offset in direction of line
   TRY_TESTME (ltemp1.Contains(gpPoint2d(1,4)));


   // rotate
   ltemp1 = left.RotateBy(gpPoint2d(-2,1),atan(1.));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(1,4)));
   ltemp1 = up.RotateBy(gpPoint2d(0,3),-atan(1.));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(1,4)));
   ltemp1 = left.RotateBy(gpPoint2d(-2,1),5*atan(1.));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-5,-2)));
   
#if defined _DEBUG
   at45.Dump(rlog.GetDumpCtx());
#endif

   // divide
   std::vector<gpPoint2d> points;
   std::vector<gpPoint2d> correct_points;
   gpLineSegment2d div_line(gpPoint2d(0,0),gpPoint2d(10,10));
   points = div_line.Divide(2);
   correct_points.push_back(gpPoint2d(0,0));
   correct_points.push_back(gpPoint2d(5,5));
   correct_points.push_back(gpPoint2d(10,10));
   TRY_TESTME ( points == correct_points );

   correct_points.clear();
   correct_points.push_back(gpPoint2d(0,0));
   correct_points.push_back(gpPoint2d(-5,-5));
   correct_points.push_back(gpPoint2d(-10,-10));
   div_line.SetEndPoint( gpPoint2d(-10,-10) );
   points = div_line.Divide(2);
   TRY_TESTME ( points == correct_points );

   TESTME_EPILOG("gpLineSegment2d");
}
#endif // _UNITTEST


