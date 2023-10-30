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
#include <GeomModel/Section.h>
#include <GeomModel/SectionComponent.h>
#include <GeomModel/Shape.h>
#include <GeomModel/ElasticProperties.h>
#include <GeomModel/MassProperties.h>
#include <algorithm>

using namespace WBFL::Geometry;

template <class T>
inline void ValidateIndex(IndexType idx, const T& container)
{
   if (container.size() < idx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
}

// create elastic props from a component
ElasticProperties make_elastic_properties(const SectionComponent& rCmp);

std::unique_ptr<Section> Section::CreateClone() const
{
   return std::make_unique<Section>(*this);
}

void Section::Offset(Float64 dx, Float64 dy)
{
   Offset(Size2d(dx, dy));
}

void Section::Offset(const Size2d& delta)
{
   std::for_each(std::begin(m_Components), std::end(m_Components), [&](auto& component) {component.GetShape().Offset(delta); });
}

void Section::Move(Shape::LocatorPoint lp, const Point2d& to)
{
   Offset(to - GetLocatorPoint(lp));
}

void Section::Move(const Point2d& from, const Point2d& to)
{
   Offset(to - from);
}

void Section::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   Rotate(Point2d(cx, cy), angle);
}

void Section::Rotate(const Point2d& center, Float64 angle)
{
   std::for_each(std::begin(m_Components), std::end(m_Components), [&](auto& component) {component.GetShape().Rotate(center, angle); });
}

void Section::SetHookPoint(std::shared_ptr<Point2d> hookPnt)
{
   if (!m_Components.empty()) m_Components.front().GetShape().SetHookPoint(hookPnt);
}

void Section::SetHookPoint(const Point2d& hookPnt)
{
   if (!m_Components.empty()) m_Components.front().GetShape().SetHookPoint(hookPnt);
}

std::shared_ptr<Point2d> Section::GetHookPoint()
{
   return m_Components.empty() ? std::shared_ptr<Point2d>() : m_Components.front().GetShape().GetHookPoint();
}

std::shared_ptr<const Point2d> Section::GetHookPoint() const
{
   return m_Components.empty() ? std::shared_ptr<const Point2d>() : m_Components.front().GetShape().GetHookPoint();
}

Point2d Section::GetLocatorPoint(Shape::LocatorPoint lp) const
{
   return m_Components.empty() ? Point2d(0, 0) : m_Components.front().GetShape().GetLocatorPoint(lp);
}

void Section::SetLocatorPoint(Shape::LocatorPoint lp, const Point2d& position)
{
   Move(lp, position);
}

void Section::AddComponent(const Shape& shape, Float64 fgModE, Float64 fgDensity, Float64 bgModE, Float64 bgDensity, SectionComponent::ComponentType componentType)
{
   std::shared_ptr<Shape> clone_shape(shape.CreateClone().release());
   AddComponent(clone_shape, fgModE, fgDensity, bgModE, bgDensity, componentType);
}

void Section::AddComponent(std::shared_ptr<Shape> shape, Float64 fgModE, Float64 fgDensity, Float64 bgModE, Float64 bgDensity, SectionComponent::ComponentType componentType)
{
   m_Components.emplace_back(shape, fgModE, fgDensity, bgModE, bgDensity, componentType);
}

const SectionComponent& Section::GetComponent(IndexType idx) const
{
   ValidateIndex(idx, m_Components);
   return m_Components[idx];
}

SectionComponent& Section::GetComponent(IndexType idx)
{
   ValidateIndex(idx, m_Components);
   return m_Components[idx];
}

void Section::RemoveComponent(IndexType idx)
{
   ValidateIndex(idx, m_Components);
   m_Components.erase(m_Components.begin() + idx);
}

void Section::Clear()
{
   m_Components.clear();
}

ElasticProperties Section::GetElasticProperties() const
{
   ElasticProperties props;
   std::for_each(std::cbegin(m_Components), std::cend(m_Components), 
      [&](const auto& component)
      {
         if (component.GetComponentType() == SectionComponent::ComponentType::Structural)
         {
            props += make_elastic_properties(component);
         }
      }
   );
   return props;
}

MassProperties Section::GetMassProperties() const
{
   Float64 sum = 0;
   std::for_each(std::cbegin(m_Components), std::cend(m_Components), 
      [&](const auto& component)
      {
         sum += (component.GetForegroundDensity() - component.GetBackgroundDensity()) * component.GetShape().GetProperties().GetArea(); 
      }
   );
   return MassProperties(sum);
}

Rect2d Section::GetBoundingBox(bool bExcludeNonstructuralComponents) const
{
   Rect2d boundingBox;
   if (m_Components.size() == 0) return boundingBox;

   auto begin = std::cbegin(m_Components);
   auto iter = begin;
   auto end = std::cend(m_Components);
   for (; iter != end; iter++)
   {
      const SectionComponent& component(*iter);
      if (bExcludeNonstructuralComponents && component.GetComponentType() == SectionComponent::ComponentType::Nonstructural)
         continue;

      const Shape& shape = component.GetShape();
      if (iter == begin)
         boundingBox = shape.GetBoundingBox();
      else
         boundingBox.Union(shape.GetBoundingBox());
   }
   return boundingBox;
}

std::unique_ptr<Section> Section::CreateClippedSection(const Line2d& line,Line2d::Side side) const
{
   std::unique_ptr<Section> clipped(std::make_unique<Section>());
   std::for_each(std::cbegin(m_Components), std::cend(m_Components), 
      [&](const auto& component)
      {
         auto clipped_shape = component.GetShape().CreateClippedShape(line, side);
         if (clipped_shape) clipped->AddComponent(std::move(clipped_shape), component.GetForegroundModE(), component.GetForegroundDensity(), component.GetBackgroundModE(), component.GetBackgroundDensity(), component.GetComponentType());
      }
   );
   return clipped;
}

std::unique_ptr<Section> Section::CreateClippedSection(const Rect2d& r, Section::ClipRegion region) const
{
   std::unique_ptr<Section> clipped(std::make_unique<Section>());
   std::for_each(std::cbegin(m_Components), std::cend(m_Components),
      [&](const auto& component)
      {
         Shape::ClipRegion shape_region = (region == ClipRegion::In ? Shape::ClipRegion::In : Shape::ClipRegion::Out);
         auto clipped_shape = component.GetShape().CreateClippedShape(r, shape_region);
         if (clipped_shape) clipped->AddComponent(std::move(clipped_shape), component.GetForegroundModE(), component.GetForegroundDensity(), component.GetBackgroundModE(), component.GetBackgroundDensity(), component.GetComponentType());
      }
   );
   return clipped;
}

ElasticProperties make_elastic_properties(const SectionComponent& rCmp)
{
   const Shape& rs = rCmp.GetShape();
   Float64 e = rCmp.GetForegroundModE() - rCmp.GetBackgroundModE();
   ShapeProperties gp = rs.GetProperties();

   return ElasticProperties(e * gp.GetArea(), gp.GetCentroid(), e * gp.GetIxx(), e * gp.GetIyy(), e * gp.GetIxy(), gp.GetXleft(), gp.GetYbottom(), gp.GetXright(), gp.GetYtop());
}

