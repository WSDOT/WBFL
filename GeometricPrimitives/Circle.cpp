///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2017  Washington State Department of Transportation
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
#include <GeometricPrimitives\Circle.h>
#include <GeometricPrimitives\LineSegment2d.h>
#include <GeometricPrimitives\Line2d.h>
#include <GeometricPrimitives\GeomOp2d.h>
#include <GeometricPrimitives\Arc.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gpCircle
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpCircle::gpCircle() :
m_Center(0,0)
{
   m_Radius = 0;
}


gpCircle::gpCircle(const gpCircle& rOther)
{
   MakeCopy(rOther);
}

gpCircle::gpCircle(const gpPoint2d& center,Float64 radius) :
m_Radius(radius),
m_Center(center)
{
}

gpCircle::gpCircle(const gpPoint2d& p1,const gpPoint2d& p2)
{
   gpLineSegment2d diameter(p1,p2);
   m_Radius = diameter.Length()/2;
   m_Center = diameter.GetMidPoint();
}

gpCircle::gpCircle(const gpPoint2d& p1,const gpPoint2d& p2, const gpPoint2d& p3)
{
   gpLineSegment2d ls1(p1,p2);
   gpLineSegment2d ls2(p2,p3);
   gpLine2d l1(p1,p2);
   gpLine2d l2(p2,p3);

   if ( l1.IsCollinear(l2) )
   {
      m_Center = p2;
      m_Radius = 0;
      return;
   }

   // Create normal lines passing through the mid-point of ls1 and ls2.
   gpPoint2d mp1 = ls1.GetMidPoint();
   gpPoint2d mp2 = ls2.GetMidPoint();

   gpLine2d nl1 = l1.Normal(mp1);
   gpLine2d nl2 = l2.Normal(mp2);

   // Find the intersection of nl1 and nl2.  This is the center point.
   Int16 nIntersect = gpGeomOp2d::Intersect(&m_Center,nl1,nl2);
   CHECK(nIntersect == 1);

   m_Radius = p1.Distance(m_Center);
}

gpCircle::gpCircle(const gpArc& arc)
{
   m_Center = arc.GetCenter();
   m_Radius = arc.GetRadius();
}

gpCircle::~gpCircle()
{
}

//======================== OPERATORS  =======================================
gpCircle& gpCircle::operator= (const gpCircle& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void gpCircle::SetRadius(Float64 r)
{
   m_Radius = r;
}

Float64 gpCircle::GetRadius() const
{
   return m_Radius;
}

void gpCircle::SetCenter(const gpPoint2d& center)
{
   m_Center = center;
}

gpPoint2d gpCircle::GetCenter() const
{
   return m_Center;
}

Float64 gpCircle::GetPerimeter() const
{
   return TWO_PI*m_Radius;
}

//======================== INQUIRY    =======================================
bool gpCircle::IsPointOnCircle(const gpPoint2d& p) const
{
   Float64 dist = m_Center.Distance(p);
   return IsEqual(dist,m_Radius);
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool gpCircle::AssertValid() const
{
   return true;
}

void gpCircle::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for gpCircle") << endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpCircle::MakeCopy(const gpCircle& rOther)
{
   m_Center = rOther.m_Center;
   m_Radius = rOther.m_Radius;
}

void gpCircle::MakeAssignment(const gpCircle& rOther)
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


bool operator==(const gpCircle& lhs, const gpCircle& rhs)
{
   return IsEqual(lhs.GetRadius(),rhs.GetRadius()) && lhs.GetCenter() == rhs.GetCenter();
}

bool operator!=(const gpCircle& lhs, const gpCircle& rhs)
{
   return !(lhs==rhs);
}

#if defined _UNITTEST
bool gpCircle::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpCircle");

   // Valid three point circle
   gpCircle c3p(gpPoint2d(0,0),gpPoint2d(10,0),gpPoint2d(5,5));
   TRY_TESTME( c3p.GetCenter() == gpPoint2d(5,0) );
   TRY_TESTME( IsEqual(c3p.GetRadius(),5.0) );

   // Invalid three point circle
   gpCircle c3pi(gpPoint2d(0,0),gpPoint2d(0,0),gpPoint2d(0,0));
   TRY_TESTME( c3pi.GetCenter() == gpPoint2d(0,0) );
   TRY_TESTME( IsEqual(c3pi.GetRadius(),0.0) );

   // Two point circle
   gpCircle c2p(gpPoint2d(0,0),gpPoint2d(10,0));
   TRY_TESTME( c2p.GetCenter() == gpPoint2d(5,0) );
   TRY_TESTME( IsEqual(c2p.GetRadius(),5.0) );
   TRY_TESTME( c2p.IsPointOnCircle(gpPoint2d(5,-5)) == true );

   TESTME_EPILOG("gpCircle");
}
#endif // _UNITTEST


