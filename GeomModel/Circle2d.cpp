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
#include <GeomModel/Circle2d.h>
#include <GeomModel/LineSegment2d.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/GeomOp2d.h>
#include <GeomModel/Arc.h>
#include <MathEx.h>

using namespace WBFL::Geometry;

Circle2d::Circle2d(const Point2d& center, Float64 radius) :
   m_Radius(radius),
   m_Center(center)
{
   PRECONDITION(0 <= radius);
}

Circle2d::Circle2d(const Point2d& p1,const Point2d& p2)
{
   LineSegment2d diameter(p1,p2);
   m_Radius = diameter.Length()/2;
   m_Center.Move(diameter.GetMidPoint());
}

Circle2d::Circle2d(const Point2d& p1,const Point2d& p2, const Point2d& p3)
{
   LineSegment2d ls1(p1,p2);
   LineSegment2d ls2(p2,p3);
   Line2d l1(p1,p2);
   Line2d l2(p2,p3);

   if ( l1.IsColinear(l2) )
   {
      m_Center = p2;
      m_Radius = 0;
      return;
   }

   // Create normal lines passing through the mid-point of ls1 and ls2.
   Point2d mp1 = ls1.GetMidPoint();
   Point2d mp2 = ls2.GetMidPoint();

   Line2d nl1 = l1.Normal(mp1);
   Line2d nl2 = l2.Normal(mp2);

   // Find the intersection of nl1 and nl2.  This is the center point.
   Int16 nIntersect = GeometricOperations::Intersect(nl1,nl2,&m_Center);
   CHECK(nIntersect == 1);

   m_Radius = p1.Distance(m_Center);
}

Circle2d::Circle2d(const Arc& arc)
{
   m_Center = arc.GetCenter();
   m_Radius = arc.GetRadius();
}

Circle2d::~Circle2d()
{
}

bool Circle2d::operator==(const Circle2d& other) const
{
   return IsEqual(m_Radius, other.m_Radius) && (m_Center == other.m_Center);
}

bool Circle2d::operator!=(const Circle2d& other) const
{
   return !(*this == other);
}

void Circle2d::SetRadius(Float64 radius)
{
   PRECONDITION(0 <= radius);
   m_Radius = radius;
}

Float64 Circle2d::GetRadius() const
{
   return m_Radius;
}

void Circle2d::SetCenter(const Point2d& center)
{
   m_Center = center;
}

Point2d& Circle2d::GetCenter()
{
   return m_Center;
}

const Point2d& Circle2d::GetCenter() const
{
   return m_Center;
}

Float64 Circle2d::GetPerimeter() const
{
   return TWO_PI*m_Radius;
}

bool Circle2d::IsPointOnPerimeter(const Point2d& p) const
{
   Float64 dist = m_Center.Distance(p);
   return IsEqual(dist,m_Radius);
}
