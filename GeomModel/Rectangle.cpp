///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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
#include <GeomModel/Rectangle.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <MathEx.h>

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
