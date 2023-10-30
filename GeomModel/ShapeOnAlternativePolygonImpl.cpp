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
#include <GeomModel/ShapeOnAlternativePolygonImpl.h>

using namespace WBFL::Geometry;

ShapeOnAlternativePolygonImpl::ShapeOnAlternativePolygonImpl()
{
}

ShapeOnAlternativePolygonImpl::ShapeOnAlternativePolygonImpl(std::shared_ptr<Point2d>& hookPnt) :
   ShapeImpl(hookPnt)
{
}

ShapeOnAlternativePolygonImpl::ShapeOnAlternativePolygonImpl(const Point2d& hookPnt) :
   ShapeImpl(hookPnt)
{
}

ShapeOnAlternativePolygonImpl::ShapeOnAlternativePolygonImpl(const ShapeOnAlternativePolygonImpl& other) :
   ShapeImpl(other)
{
   Copy(other);
}

ShapeOnAlternativePolygonImpl::~ShapeOnAlternativePolygonImpl()
{
}

ShapeOnAlternativePolygonImpl& ShapeOnAlternativePolygonImpl::operator=(const ShapeOnAlternativePolygonImpl& other)
{
   if (this != &other)
   {
      __super::operator=(other);
      Copy(other);
   }
   return *this;
}

std::vector<Point2d> ShapeOnAlternativePolygonImpl::GetPolyPoints() const
{
   return GetPolygon()->GetPolyPoints();
}

void ShapeOnAlternativePolygonImpl::SetHookPoint(std::shared_ptr<Point2d> hookPnt)
{
   __super::SetHookPoint(hookPnt);
   SetDirtyFlag();
}

void ShapeOnAlternativePolygonImpl::SetHookPoint(const Point2d& hookPnt)
{
   __super::SetHookPoint(hookPnt);
   SetDirtyFlag();
}

void ShapeOnAlternativePolygonImpl::Offset(const Size2d& delta)
{
   __super::Offset(delta);
   SetDirtyFlag();
}

void ShapeOnAlternativePolygonImpl::Rotate(const Point2d& center, Float64 angle)
{
   __super::Rotate(center, angle);
   SetDirtyFlag();
}

void ShapeOnAlternativePolygonImpl::Reflect(const Line2d& line)
{
   GetPolygon()->Reflect(line);
}

void ShapeOnAlternativePolygonImpl::Copy(const ShapeOnAlternativePolygonImpl& other)
{
   m_bIsDirty = other.m_bIsDirty;
   if (other.m_Polygon) m_Polygon = std::make_unique<Polygon>(*other.m_Polygon);
}

std::unique_ptr<WBFL::Geometry::Polygon>& ShapeOnAlternativePolygonImpl::GetPolygon() const
{
   UpdatePolygon();
   return m_Polygon;
}

void ShapeOnAlternativePolygonImpl::SetDirtyFlag(bool bFlag)
{
   m_bIsDirty = bFlag;
}

bool ShapeOnAlternativePolygonImpl::IsDirty() const
{
   return m_bIsDirty;
}

void ShapeOnAlternativePolygonImpl::UpdatePolygon() const
{
   if (!m_bIsDirty && !IsHookPointChanged()) return;
   if (m_Polygon == nullptr) m_Polygon = std::make_unique<Polygon>();
   m_Polygon->Clear();
   OnUpdatePolygon(m_Polygon);
   ShapeCurrentWithHookPoint();
   m_bIsDirty = false;
}
