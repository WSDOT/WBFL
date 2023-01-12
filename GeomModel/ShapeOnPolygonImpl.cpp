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
#include <GeomModel/ShapeOnPolygonImpl.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

void ShapeOnPolygonImpl::GetFurthestPoint(const Line2d& line, Line2d::Side side, Point2d& furthestPoint, Float64& furthestDistance) const
{
   GetPolygon()->GetFurthestPoint(line, side, furthestPoint, furthestDistance);
}

bool ShapeOnPolygonImpl::PointInShape(const Point2d& p) const
{
   return GetPolygon()->PointInShape(p);
}

Float64 ShapeOnPolygonImpl::GetPerimeter() const
{
   return GetPolygon()->GetPerimeter();
}

#if defined _DEBUG
bool ShapeOnPolygonImpl::AssertValid() const
{
   return true;
}

void ShapeOnPolygonImpl::Dump(WBFL::Debug::LogContext& os) const
{
   ASSERTVALID;
   os << _T("Dump for ShapeOnPolygonImpl") << WBFL::Debug::endl;
}
#endif // _DEBUG


#if defined _UNITTEST
bool ShapeOnPolygonImpl::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ShapeOnPolygonImpl");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented");
   TESTME_EPILOG("ShapeOnPolygonImpl");
}
#endif // _UNITTEST
