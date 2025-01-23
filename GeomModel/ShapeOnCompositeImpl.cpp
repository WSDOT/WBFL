///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <GeomModel/ShapeOnCompositeImpl.h>
#include <MathEx.h>
#include <algorithm>

using namespace WBFL::Geometry;

ShapeOnCompositeImpl::ShapeOnCompositeImpl() :
   ShapeImpl()
{
}

ShapeOnCompositeImpl::ShapeOnCompositeImpl(std::shared_ptr<Point2d>& hookPnt) :
   ShapeImpl(hookPnt)
{
}

ShapeOnCompositeImpl::ShapeOnCompositeImpl(const Point2d& hookPnt) :
   ShapeImpl(hookPnt)
{
}

ShapeOnCompositeImpl::ShapeOnCompositeImpl(const ShapeOnCompositeImpl& rOther) :
   ShapeImpl(rOther)
{
}

ShapeOnCompositeImpl::~ShapeOnCompositeImpl()
{
}

ShapeOnCompositeImpl& ShapeOnCompositeImpl::operator= (const ShapeOnCompositeImpl& rOther)
{
   if (this != &rOther)
   {
      __super::operator=(rOther);
   }

   return *this;
}

ShapeProperties ShapeOnCompositeImpl::GetProperties() const
{
   return GetComposite()->GetProperties();
}

Rect2d ShapeOnCompositeImpl::GetBoundingBox() const
{
   return GetComposite()->GetBoundingBox();
}

std::vector<Point2d> ShapeOnCompositeImpl::GetPolyPoints() const
{
   return GetComposite()->GetPolyPoints();
}

bool ShapeOnCompositeImpl::PointInShape(const Point2d& p) const
{
   return GetComposite()->PointInShape(p);
}

std::unique_ptr<Shape> ShapeOnCompositeImpl::CreateClippedShape(const Line2d& line, Line2d::Side side) const
{
   return GetComposite()->CreateClippedShape(line, side);
}

std::unique_ptr<Shape> ShapeOnCompositeImpl::CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const
{
   return GetComposite()->CreateClippedShape(r, region);
}

Float64 ShapeOnCompositeImpl::GetFurthestDistance(const Line2d& line, Line2d::Side side) const
{
   return GetComposite()->GetFurthestDistance(line, side);
}

std::pair<Point2d,Float64> ShapeOnCompositeImpl::GetFurthestPoint(const Line2d& line, Line2d::Side side) const
{
   return GetComposite()->GetFurthestPoint(line, side);
}

Float64 ShapeOnCompositeImpl::GetPerimeter() const
{
   return GetComposite()->GetPerimeter();
}

void ShapeOnCompositeImpl::Reflect(const Line2d& line)
{
   GetComposite()->Reflect(line);
}

void ShapeOnCompositeImpl::DoOffset(const Size2d& delta)
{
   GetComposite()->Offset(delta);
}

void ShapeOnCompositeImpl::DoRotate(const Point2d& center, Float64 angle)
{
   GetComposite()->Rotate(center, angle);
}

void ShapeOnCompositeImpl::Copy(const ShapeOnCompositeImpl& other)
{
   m_bIsDirty = other.m_bIsDirty;
   if (other.m_Composite) m_Composite = std::make_unique<CompositeShape>(*other.m_Composite);
}

std::unique_ptr<CompositeShape>& ShapeOnCompositeImpl::GetComposite() const
{
   UpdateComposite();
   return m_Composite;
}

void ShapeOnCompositeImpl::SetDirtyFlag(bool bFlag)
{
   m_bIsDirty = bFlag;
}

bool ShapeOnCompositeImpl::IsDirty() const
{
   return m_bIsDirty;
}

void ShapeOnCompositeImpl::UpdateComposite() const
{
   if (!m_bIsDirty && !IsHookPointChanged()) return;
   if (m_Composite == nullptr) m_Composite = std::make_unique<CompositeShape>();
   m_Composite->Clear();
   OnUpdateComposite(m_Composite);
   ShapeCurrentWithHookPoint();
   m_bIsDirty = false;
}