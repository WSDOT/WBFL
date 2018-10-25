///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2015  Washington State Department of Transportation
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
#include <GeometricPrimitives\Arc.h>
#include <GeometricPrimitives\LineSegment2d.h>
#include <GeometricPrimitives\Line2d.h>
#include <GeometricPrimitives\Vector2d.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gpArc
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpArc::gpArc() :
m_Start(0,0),
m_Center(0,0),
m_End(0,0)
{
}


gpArc::gpArc(const gpArc& rOther)
{
   MakeCopy(rOther);
}

gpArc::gpArc(const gpPoint2d& start,const gpPoint2d& center, const gpPoint2d& end) :
m_Start(start),
m_Center(center),
m_End(end)
{
}

gpArc::~gpArc()
{
}

//======================== OPERATORS  =======================================
gpArc& gpArc::operator= (const gpArc& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================

void gpArc::SetStart(const gpPoint2d& start)
{
   m_Start = start;
}

gpPoint2d gpArc::GetStart() const
{
   return m_Start;
}

void gpArc::SetCenter(const gpPoint2d& center)
{
   m_Center = center;
}

gpPoint2d gpArc::GetCenter() const
{
   return m_Center;
}

void gpArc::SetEnd(const gpPoint2d& end)
{
   m_End = end;
}

gpPoint2d gpArc::GetEnd() const
{
   return m_End;
}

void gpArc::Reverse()
{
   gpPoint2d tmp = m_Start;
   m_Start = m_End;
   m_End = tmp;
}

Float64 gpArc::GetRadius() const
{
   return m_Center.Distance(m_Start);
}

Float64 gpArc::GetLength() const
{
   return Distance(m_End);
}

Float64 gpArc::Distance(const gpPoint2d& p) const
{
   gpVector2d v1(m_Center,m_Start);
   gpVector2d v2(m_Center,p);
   Float64 delta = v2.AngleBetween(v1);
   Float64 radius = GetRadius();
   Float64 distance = delta*radius;
   return distance;
}

Float64 gpArc::GetCentralAngle() const
{
   gpVector2d v1(m_Center,m_Start);
   gpVector2d v2(m_Center,m_End);
   Float64 delta = v2.AngleBetween(v1);

   gpLine2d line(m_Center,v1);
   if ( line.GetSide(m_End) == gpLine2d::Right )
      delta = TWO_PI - delta;

   return delta;
}

//======================== INQUIRY    =======================================
bool gpArc::IsPointOnArc(const gpPoint2d& p) const
{
   Float64 dist = m_Center.Distance(p);
   Float64 radius = GetRadius();
   if ( !IsEqual(dist,radius) )
      return false;

   gpLine2d l1(m_Center,m_Start);
   gpLine2d l2(m_Center,m_End);

   gpLine2d::Side side1 = l1.GetSide(p);
   gpLine2d::Side side2 = l2.GetSide(p);

   if ( side1 == gpLine2d::Left && side2 == gpLine2d::Right )
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

//======================== DEBUG      =======================================
#if defined _DEBUG
bool gpArc::AssertValid() const
{
   return true;
}

void gpArc::Dump(dbgDumpContext& os) const
{
   os << "Dump for gpArc" << endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpArc::MakeCopy(const gpArc& rOther)
{
   m_Start     = rOther.m_Start;
   m_Center    = rOther.m_Center;
   m_End       = rOther.m_End;
}

void gpArc::MakeAssignment(const gpArc& rOther)
{
   MakeCopy( rOther );
}

//======================== TESTING =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


bool operator==(const gpArc& lhs, const gpArc& rhs)
{
   return IsEqual(lhs.GetRadius(),rhs.GetRadius()) && lhs.GetCenter() == rhs.GetCenter();
}

bool operator!=(const gpArc& lhs, const gpArc& rhs)
{
   return !(lhs==rhs);
}

#if defined _UNITTEST
bool gpArc::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpArc");

   gpArc a1(gpPoint2d(10,0),gpPoint2d(0,0),gpPoint2d(0,10));
   gpArc a2( gpPoint2d(-5,-5), gpPoint2d(0,0), gpPoint2d(-5,5) );

   // IsPointOnArc
   TRY_TESTME( a1.IsPointOnArc(gpPoint2d(-10,  0)) == false );
   TRY_TESTME( a1.IsPointOnArc(gpPoint2d(  0,-10)) == false );
   TRY_TESTME( a1.IsPointOnArc(gpPoint2d( 10,  0)) == true );
   TRY_TESTME( a1.IsPointOnArc(gpPoint2d(  0, 10)) == true );

   TRY_TESTME( a2.IsPointOnArc(gpPoint2d( 7.07106781187,0)) == true );
   TRY_TESTME( a2.IsPointOnArc(gpPoint2d(-7.07106781187,0)) == false );

   // CentralAngle
   TRY_TESTME( IsEqual(a1.GetCentralAngle(),PI_OVER_2) );
   a1.Reverse();
   TRY_TESTME( IsEqual(a1.GetCentralAngle(),3*PI_OVER_2) );

   TRY_TESTME( IsEqual(a2.GetCentralAngle(),3*PI_OVER_2) );
   a2.Reverse();
   TRY_TESTME( IsEqual(a2.GetCentralAngle(),PI_OVER_2) );

   TESTME_EPILOG("gpArc");
}
#endif // _UNITTEST


