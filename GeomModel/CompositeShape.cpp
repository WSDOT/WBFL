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
#include <GeomModel/CompositeShape.h>
#include <MathEx.h>
#include <algorithm>

using namespace WBFL::Geometry;

template <class T>
inline void ValidateIndex(IndexType idx, const T& container)
{
   if (container.size() <= idx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
}

CompositeShape::CompositeShape() :
   Shape()
{
}

CompositeShape::CompositeShape(const CompositeShape& rOther) :
   Shape(rOther)
{
   Copy(rOther);
}

CompositeShape::~CompositeShape()
{
}

CompositeShape& CompositeShape::operator= (const CompositeShape& rOther)
{
   if (this != &rOther)
   {
      __super::operator=(rOther);
      Clear();
      Copy(rOther);
   }

   return *this;
}

void CompositeShape::Offset(const Size2d& delta)
{
   std::for_each(m_Shapes.begin(), m_Shapes.end(), [&](auto& shape) {shape.first->Offset(delta); });
   SetDirtyFlag();
}

void CompositeShape::Rotate(const Point2d& center, Float64 angle)
{
   std::for_each(m_Shapes.begin(), m_Shapes.end(), [&](auto& shape) {shape.first->Rotate(center,angle); });
   SetDirtyFlag();
}

void CompositeShape::Offset(Float64 dx, Float64 dy)
{
   Offset(Size2d(dx, dy));
}

void CompositeShape::Move(LocatorPoint lp, const Point2d& to)
{
   Move(GetLocatorPoint(lp),to);
}

void CompositeShape::Move(const Point2d& from, const Point2d& to)
{
   Offset(to - from);
}

void CompositeShape::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   Rotate(Point2d(cx, cy), angle);
}

void CompositeShape::SetHookPoint(std::shared_ptr<Point2d>& hookPnt)
{
   if (0 < m_Shapes.size()) m_Shapes.front().first->SetHookPoint(hookPnt);
}

void CompositeShape::SetHookPoint(const Point2d& hookPnt)
{
   if (0 < m_Shapes.size()) m_Shapes.front().first->SetHookPoint(hookPnt);
}

std::shared_ptr<Point2d>& CompositeShape::GetHookPoint()
{
   return (0 < m_Shapes.size() ? m_Shapes.front().first->GetHookPoint() : m_DummyHookPoint);
}

const std::shared_ptr<Point2d>& CompositeShape::GetHookPoint() const
{
   return (0 < m_Shapes.size() ? m_Shapes.front().first->GetHookPoint() : m_DummyHookPoint);
}

Point2d CompositeShape::GetLocatorPoint(LocatorPoint point) const
{
   if (0 < m_Shapes.size())
      return m_Shapes.front().first->GetLocatorPoint(point);
   else
      return Point2d(0, 0);
}

void CompositeShape::SetLocatorPoint(LocatorPoint lp, Point2d& position)
{
   Move(lp, position);
}

Float64 CompositeShape::GetFurthestDistance(const Line2d& line, Line2d::Side side) const
{
   Float64 fd = -Float64_Max;
   for (const auto& pair : m_Shapes)
   {
      fd = Max(fd, pair.first->GetFurthestDistance(line, side));
   }
   return fd;
}

void CompositeShape::GetFurthestPoint(const Line2d& line, Line2d::Side side, Point2d& furthestPoint, Float64& furthestDistance) const
{
   Point2d fp;
   Float64 fd = -Float64_Max;
   for (const auto& pair : m_Shapes)
   {
      Point2d p;
      Float64 dist;
      pair.first->GetFurthestPoint(line, side, p, dist);
      if (fd < dist)
      {
         fp = p;
         fd = dist;
      }
   }

   furthestPoint = fp;
   furthestDistance = fd;
}

bool CompositeShape::PointInShape(const Point2d& p) const
{
   for (const auto& pair : m_Shapes)
   {
      if (pair.first->PointInShape(p) && pair.second == ShapeType::Solid)
      {
         return true;
      }
   }

   return false;
}

Float64 CompositeShape::GetPerimeter() const
{
   if (0 < m_Shapes.size())
      return m_Shapes.front().first->GetPerimeter();
   else
      return 0;
}

ShapeProperties CompositeShape::GetProperties() const
{
   return GetShapeProperties();
}

Rect2d CompositeShape::GetBoundingBox() const
{
   const auto& props = GetShapeProperties();
   const auto& cg = props.GetCentroid();
   return Rect2d(cg.X() - props.GetXleft(), cg.Y() - props.GetYbottom(), props.GetXright() + cg.X(), props.GetYtop() + cg.Y());
}

std::vector<Point2d> CompositeShape::GetPolyPoints() const
{
   if (m_Shapes.size() == 0)
      return m_DummyPoints;
   else
      return m_Shapes.front().first->GetPolyPoints();
}

void CompositeShape::Reflect(const Line2d& line)
{
   std::for_each(m_Shapes.begin(), m_Shapes.end(), [&line](auto& pair) {pair.first->Reflect(line); });
}

std::unique_ptr<Shape> CompositeShape::CreateReflectedShape(const Line2d& line) const
{
   auto clone = CreateClone();
   clone->Reflect(line);
   return clone;
}

std::unique_ptr<Shape> CompositeShape::CreateClone() const
{
   return std::make_unique<CompositeShape>(*this);
}

std::unique_ptr<Shape> CompositeShape::CreateClippedShape(const Line2d& line, Line2d::Side side) const
{
   std::unique_ptr<CompositeShape> clipped(std::make_unique<CompositeShape>());
   for(const auto& pair : m_Shapes)
   {
      std::unique_ptr<Shape> clipped_piece = pair.first->CreateClippedShape(line, side);
      if (clipped_piece) clipped->AddShape(std::move(clipped_piece), pair.second);
   }

   if (clipped->GetShapeCount() == 0)
      return nullptr;

   return clipped;
}

std::unique_ptr<Shape> CompositeShape::CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const
{
   std::unique_ptr<CompositeShape> clipped(std::make_unique<CompositeShape>());
   for (const auto& pair : m_Shapes)
   {
      std::unique_ptr<Shape> clipped_piece = pair.first->CreateClippedShape(r, region);
      if (clipped_piece) clipped->AddShape(std::move(clipped_piece), pair.second);
   }

   if (clipped->GetShapeCount() == 0)
      return nullptr;

   return clipped;
}

void CompositeShape::AddShape(const Shape& shape,CompositeShape::ShapeType shapeType)
{
   AddShape(shape.CreateClone(), shapeType);
}

void CompositeShape::AddShape(std::unique_ptr<Shape>&& shape, CompositeShape::ShapeType shapeType)
{
   if (m_Shapes.empty() && shapeType == ShapeType::Void)
      THROW_GEOMETRY(WBFL_GEOMETRY_E_SHAPE); // first shape must be solid

   m_Shapes.emplace_back(std::move(shape), shapeType);
   SetDirtyFlag();
}

void CompositeShape::RemoveShape(IndexType idx)
{
   ValidateIndex(idx, m_Shapes);
   m_Shapes.erase(m_Shapes.begin() + idx);
   SetDirtyFlag();
}

void CompositeShape::Clear()
{
   m_Shapes.clear();
   SetDirtyFlag();
}

std::shared_ptr<Shape>& CompositeShape::GetShape(IndexType idx)
{
   ValidateIndex(idx, m_Shapes);
   return m_Shapes[idx].first;
}

const std::shared_ptr<Shape>& CompositeShape::GetShape(IndexType idx) const
{
   ValidateIndex(idx, m_Shapes);
   return m_Shapes[idx].first;
}

CompositeShape::ShapeType CompositeShape::GetShapeType(IndexType idx) const
{
   ValidateIndex(idx, m_Shapes);
   return m_Shapes[idx].second;
}

bool CompositeShape::IsSolid(IndexType idx) const
{
   return GetShapeType(idx) == ShapeType::Solid;
}

bool CompositeShape::IsVoid(IndexType idx) const
{
   return GetShapeType(idx) == ShapeType::Void;
}

IndexType CompositeShape::GetShapeCount() const
{
   return m_Shapes.size();
}

void CompositeShape::SetDirtyFlag(bool bFlag)
{
   m_bIsDirty = bFlag;
}

bool CompositeShape::GetDirtyFlag() const
{
   return m_bIsDirty;
}

const ShapeProperties& CompositeShape::GetShapeProperties() const
{
   if (!m_bIsDirty) return m_Properties;

   ShapeProperties props;
   if (0 < m_Shapes.size())
   {
      props = m_Shapes.front().first->GetProperties();
      auto iter = m_Shapes.begin() + 1;
      auto end = m_Shapes.end();
      for(; iter != end; iter++)
      {
         const auto& pair(*iter);
         const ShapeProperties& p = pair.first->GetProperties();
         if (pair.second == ShapeType::Solid)
            props += p; // shape is a solid
         else
            props -= p; // shape is a void
      }
   }
   m_Properties = props;

   m_bIsDirty = false;
   return m_Properties;
}

void CompositeShape::Copy(const CompositeShape& other)
{
   m_bIsDirty = other.m_bIsDirty;
   m_Properties = other.m_Properties;

   for (const auto& pair : other.m_Shapes)
   {
      m_Shapes.emplace_back(pair.first->CreateClone(), pair.second);
   }
}
