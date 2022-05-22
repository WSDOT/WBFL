///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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
#include <GeomModel/Rectangle.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

Rectangle::Rectangle() :
   ShapeOnPolygonImpl()
{
}

Rectangle::Rectangle(std::shared_ptr<Point2d>& hookPnt, Float64 w, Float64 h) :
   ShapeOnPolygonImpl(hookPnt), m_Height(h), m_Width(w)
{
   PRECONDITION(w >= 0);
   PRECONDITION(h >= 0);
}

Rectangle::Rectangle(const Point2d& hookPnt, Float64 w, Float64 h) :
   ShapeOnPolygonImpl(hookPnt), m_Height(h), m_Width(w)
{
   PRECONDITION(w >= 0);
   PRECONDITION(h >= 0);
}

Rectangle::Rectangle(const Rectangle& other) :
   ShapeOnPolygonImpl(other)
{
   Copy(other);
}

WBFL::Geometry::Rectangle& Rectangle::operator=(const Rectangle& other)
{
   if (this != &other)
   {
      __super::operator=(other);
      Copy(other);
   }
   return *this;
}

Rectangle::~Rectangle()
{
}

void Rectangle::SetWidth(Float64 w)
{
   PRECONDITION(w>=0);
   m_Width = w;
   SetDirtyFlag();
}

Float64 Rectangle::GetWidth() const
{
   return m_Width;
}

void Rectangle::SetHeight(Float64 h)
{
   PRECONDITION(h>=0);
   m_Height = h;
   SetDirtyFlag();
}

Float64 Rectangle::GetHeight() const
{
   return m_Height;
}

void Rectangle::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void Rectangle::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

Float64 Rectangle::GetPerimeter() const
{
   return 2 * (m_Height + m_Width);
}


std::unique_ptr<Shape> Rectangle::CreateClone() const
{
   return std::make_unique<Rectangle>(*this);
}

#if defined _DEBUG
bool Rectangle::AssertValid() const
{
   if (m_Width<0) return false;
   if (m_Height<0) return false;
   return __super::AssertValid();
}

void Rectangle::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for Rectangle ***")<< WBFL::Debug::endl;
   __super::Dump( os );
   os << _T("  (Height, Width) = (")<<m_Height<<_T(", ")<<m_Width<<_T(")")<< WBFL::Debug::endl;
   os << _T("  Hook Point      = (")<<GetHookPoint()->X()<<_T(", ")<<GetHookPoint()->Y()<<_T(")")<< WBFL::Debug::endl;
   os << _T("  Rotation        =  ")<<m_Rotation<< WBFL::Debug::endl;
}
#endif // _DEBUG

void Rectangle::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   Float64 cx = GetHookPoint()->X();
   Float64 cy = GetHookPoint()->Y();
   Float64 w2 = m_Width/2.;
   Float64 h2 = m_Height/2.;
   Point2d br(cx+w2, cy-h2);
   Point2d bl(cx-w2, cy-h2);
   Point2d tr(cx+w2, cy+h2);
   Point2d tl(cx-w2, cy+h2);

   // rotate points if needed
   if (m_Rotation != 0.)
   {
      br.Rotate(cx, cy, m_Rotation);
      bl.Rotate(cx, cy, m_Rotation);
      tr.Rotate(cx, cy, m_Rotation);
      tl.Rotate(cx, cy, m_Rotation);
   }

   polygon->AddPoint(br);
   polygon->AddPoint(bl);
   polygon->AddPoint(tl);
   polygon->AddPoint(tr);
}

void Rectangle::Copy(const Rectangle& other)
{
   m_Height = other.m_Height;
   m_Width = other.m_Width;
   m_Rotation = other.m_Rotation;
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool Rectangle::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Rectangle");

   Rectangle rt(Point2d(1, 2),2,4);
   TRY_TESTME( IsEqual(2., rt.GetWidth())) ;
   TRY_TESTME( IsEqual(4., rt.GetHeight())) ;
   TRY_TESTME( Point2d(1,2) == *rt.GetHookPoint()); 
   ShapeProperties aprops = rt.GetProperties();
   TRY_TESTME ( IsEqual(aprops.GetArea(), 8.)) ;
   TRY_TESTME ( IsEqual(aprops.GetIxx(),  10.66, .1)) ;
   TRY_TESTME ( IsEqual(aprops.GetIyy(),   2.66, .1)) ;
   TRY_TESTME ( IsEqual(aprops.GetIxy(),   0.00, .001)) ;
   TRY_TESTME ( rt.GetBoundingBox() == Rect2d(0,0,2,4)) ;

   rt.SetHookPoint(Point2d(0,0));
   TRY_TESTME (rt.GetBoundingBox() == Rect2d(-1,-2,1,2)) ;
   rt.Move(Shape::LocatorPoint::CenterCenter, Point2d(1,2));
   TRY_TESTME (rt.GetBoundingBox() == Rect2d(0,0,2,4)) ;

   Float64 ang = atan(.5);
   Float64 dis = 2*cos(ang);
   rt.Rotate(Point2d(0,0),ang);
   TRY_TESTME (rt.GetBoundingBox() == Rect2d(-dis,0,dis,sqrt(20.))) ;
   rt.Rotate(Point2d(0,0),-ang);

   // resize rectangle and clip it into a triangle
   rt.SetWidth(40);
   rt.SetHeight(50);
   rt.SetHookPoint(Point2d(20,25));
   Line2d up_left(Point2d(0,0), Vector2d(Size2d(1,1)));
   Line2d up_rgt(Point2d(40,0), Vector2d(Size2d(-3,5)));
   std::unique_ptr<Shape> pfirst(rt.CreateClippedShape(up_left, Line2d::Side::Left));
   std::unique_ptr<Shape> ptriang(pfirst->CreateClippedShape(up_rgt, Line2d::Side::Right));
   aprops = ptriang->GetProperties();
   TRY_TESTME ( IsEqual(aprops.GetArea(), 500.)) ;
   TRY_TESTME ( ptriang->GetBoundingBox() == Rect2d(0,0,40,25)) ;

#if defined _DEBUG
   rt.Dump(rlog.GetLogContext());
#endif

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(rt) == true);

   TESTME_EPILOG("Rectangle");
}

#endif // _UNITTEST



