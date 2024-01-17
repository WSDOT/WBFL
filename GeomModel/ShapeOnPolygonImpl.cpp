///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <GeomModel/ShapeOnPolygonImpl.h>

using namespace WBFL::Geometry;

ShapeOnPolygonImpl::ShapeOnPolygonImpl()
{
}

ShapeOnPolygonImpl::ShapeOnPolygonImpl(std::shared_ptr<Point2d>& hookPnt) :
   ShapeOnAlternativePolygonImpl(hookPnt)
{
}

ShapeOnPolygonImpl::ShapeOnPolygonImpl(const Point2d& hookPnt) :
   ShapeOnAlternativePolygonImpl(hookPnt)
{
}

ShapeOnPolygonImpl::ShapeOnPolygonImpl(const ShapeOnPolygonImpl& other) :
   ShapeOnAlternativePolygonImpl(other)
{
   Copy(other);
}

ShapeOnPolygonImpl::~ShapeOnPolygonImpl()
{
}

ShapeOnPolygonImpl& ShapeOnPolygonImpl::operator=(const ShapeOnPolygonImpl& other)
{
   if (this != &other)
   {
      __super::operator=(other);
      Copy(other);
   }
   return *this;
}

void ShapeOnPolygonImpl::Copy(const ShapeOnPolygonImpl& other)
{
   // this class doesn't have any data to copy.... this is a placeholder
}

ShapeProperties ShapeOnPolygonImpl::GetProperties() const
{
   return GetPolygon()->GetProperties();
}

Rect2d ShapeOnPolygonImpl::GetBoundingBox() const
{
   return GetPolygon()->GetBoundingBox();
}

std::vector<Point2d> ShapeOnPolygonImpl::GetPolyPoints() const
{
   return GetPolygon()->GetPolyPoints();
}

std::unique_ptr<Shape> ShapeOnPolygonImpl::CreateClippedShape(const Line2d& line, Line2d::Side side) const
{
   return GetPolygon()->CreateClippedShape(line, side);
}

std::unique_ptr<Shape> ShapeOnPolygonImpl::CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const
{
   return GetPolygon()->CreateClippedShape(r, region);
}

Float64 ShapeOnPolygonImpl::GetFurthestDistance(const Line2d& line, Line2d::Side side) const
{
   return GetPolygon()->GetFurthestDistance(line, side);
}

std::pair<Point2d,Float64> ShapeOnPolygonImpl::GetFurthestPoint(const Line2d& line, Line2d::Side side) const
{
   return GetPolygon()->GetFurthestPoint(line, side);
}

bool ShapeOnPolygonImpl::PointInShape(const Point2d& p) const
{
   return GetPolygon()->PointInShape(p);
}

Float64 ShapeOnPolygonImpl::GetPerimeter() const
{
   return GetPolygon()->GetPerimeter();
}

void ShapeOnPolygonImpl::Reflect(const Line2d& line)
{
   GetPolygon()->Reflect(line);
}
