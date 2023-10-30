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
#include <GeomModel/Triangle.h>
#include <MathEx.h>

using namespace WBFL::Geometry;

Triangle::Triangle() :ShapeOnPolygonImpl()
{
}

Triangle::Triangle(std::shared_ptr<Point2d>& hookPnt, Float64 h, Float64 w, Float64 c, Float64 rotAngle) :
   ShapeOnPolygonImpl(hookPnt), m_Height(h), m_Width(w), m_Offset(c), m_Rotation(rotAngle)
{
   PRECONDITION(w>=0);
   PRECONDITION(h>=0);
}

Triangle::Triangle(const Point2d& hookPnt, Float64 h, Float64 w, Float64 c, Float64 rotAngle) :
   ShapeOnPolygonImpl(hookPnt), m_Height(h), m_Width(w), m_Offset(c), m_Rotation(rotAngle)
{
   PRECONDITION(w >= 0);
   PRECONDITION(h >= 0);
}

Triangle::Triangle(const Triangle& other) : ShapeOnPolygonImpl(other)
{
   Copy(other);
}

Triangle::~Triangle()
{
}

Triangle& Triangle::operator=(const Triangle& other)
{
   if (this != &other)
   {
      __super::operator=(other);
      Copy(other);
   }
   return *this;
}

void Triangle::SetWidth(Float64 w)
{
   m_Width = w;
   SetDirtyFlag();
}

Float64 Triangle::GetWidth() const
{
   return m_Width;
}

void Triangle::SetHeight(Float64 h)
{
   m_Height = h;
   SetDirtyFlag();
}

Float64 Triangle::GetHeight() const
{
   return m_Height;
}

void Triangle::SetOffset(Float64 c)
{
   m_Offset = c;
   SetDirtyFlag();
}

Float64 Triangle::GetOffset() const
{
   return m_Offset;
}

void Triangle::SetRotationAngle(Float64 rotAngle)
{
   m_Rotation = rotAngle;
   SetDirtyFlag();
}

Float64 Triangle::GetRotationAngle() const
{
   return m_Rotation;
}

void Triangle::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void Triangle::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> Triangle::CreateClone() const
{
   return std::make_unique<Triangle>(*this);
}

void Triangle::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   // create polygon geometry
   Point2d p1(0,0);
   Point2d p2(m_Width,0);
   Point2d p3(m_Offset,m_Height);

   polygon->AddPoint(p1);
   polygon->AddPoint(p2);
   polygon->AddPoint(p3);

   // move to hookpoint coordinates
   polygon->Offset(*GetHookPoint());

   // rotate if needed
   if (m_Rotation != 0.)
      polygon->Rotate(*GetHookPoint(), m_Rotation);
}

void Triangle::Copy(const Triangle& other)
{
   m_Height = other.m_Height;
   m_Width = other.m_Width;
   m_Offset = other.m_Offset;
   m_Rotation = other.m_Rotation;
}
