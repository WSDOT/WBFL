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
#include <GeomModel/GenericShape.h>
#include <GeomModel/Primitives.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>
#include "MohrCircle.h"

using namespace WBFL::Geometry;

GenericShape::GenericShape(Float64 area,
   std::shared_ptr<Point2d>& centroid,
   Float64 ixx, Float64 iyy, Float64 ixy,
   Float64 xLeft, Float64 yBottom,
   Float64 xRight, Float64 yTop,
   Float64 perimeter)
{
   SetProperties(area, centroid, ixx, iyy, ixy, xLeft, yBottom, xRight, yTop, perimeter);
}

GenericShape::GenericShape(Float64 area,
   const Point2d& centroid,
   Float64 ixx, Float64 iyy, Float64 ixy,
   Float64 xLeft, Float64 yBottom,
   Float64 xRight, Float64 yTop,
   Float64 perimeter)
{
   SetProperties(area, centroid, ixx, iyy, ixy, xLeft, yBottom, xRight, yTop, perimeter);
}

void GenericShape::SetProperties(Float64 area, std::shared_ptr<Point2d>& centroid, Float64 ixx, Float64 iyy, Float64 ixy, Float64 xLeft, Float64 yBottom, Float64 xRight, Float64 yTop, Float64 perimeter)
{
   m_Area = area;
   m_pCentroid = centroid;
   m_Ixx = ixx;
   m_Iyy = iyy;
   m_Ixy = ixy;
   m_Xleft = xLeft;
   m_Ybottom = yBottom;
   m_Xright = xRight;
   m_Ytop = yTop;
   m_Perimeter = perimeter;
}

void GenericShape::SetProperties(Float64 area, const Point2d& centroid, Float64 ixx, Float64 iyy, Float64 ixy, Float64 xLeft, Float64 yBottom, Float64 xRight, Float64 yTop, Float64 perimeter)
{
   m_Area = area;
   m_pCentroid->Move(centroid);
   m_Ixx = ixx;
   m_Iyy = iyy;
   m_Ixy = ixy;
   m_Xleft = xLeft;
   m_Ybottom = yBottom;
   m_Xright = xRight;
   m_Ytop = yTop;
   m_Perimeter = perimeter;
}

void GenericShape::GetProperties(Float64* area, std::shared_ptr<Point2d>* centroid, Float64* ixx, Float64* iyy, Float64* ixy, Float64* xLeft, Float64* yBottom, Float64* xRight, Float64* yTop, Float64* perimeter) const
{
   *area = m_Area;
   *centroid = m_pCentroid;
   *ixx = m_Ixx;
   *iyy = m_Iyy;
   *ixy = m_Ixy;
   *yTop = m_Ytop;
   *yBottom = m_Ybottom;
   *xLeft = m_Xleft;
   *xRight = m_Xright;
   *perimeter = m_Perimeter;
}

void GenericShape::SetArea(Float64 area)
{
   m_Area = area;
}

Float64 GenericShape::GetArea() const
{
   return m_Area;
}

void GenericShape::SetCentroid(const Point2d& centroid)
{
   m_pCentroid->Move(centroid);
}

void GenericShape::SetCentroid(std::shared_ptr<Point2d> centroid)
{
   m_pCentroid = centroid;
}

std::shared_ptr<const Point2d> GenericShape::GetCentroid() const
{
   return m_pCentroid;
}

std::shared_ptr<Point2d> GenericShape::GetCentroid()
{
   return m_pCentroid;
}

void GenericShape::SetIxx(Float64 ixx)
{
   m_Ixx = ixx;
}

Float64 GenericShape::GetIxx() const
{
   return m_Ixx;
}

void GenericShape::SetIyy(Float64 iyy)
{
   m_Iyy = iyy;
}

Float64 GenericShape::GetIyy() const
{
   return m_Iyy;
}

void GenericShape::SetIxy(Float64 ixy)
{
   m_Ixy = ixy;
}

Float64 GenericShape::GetIxy() const
{
   return m_Ixy;
}

void GenericShape::SetYtop(Float64 ytop)
{
   m_Ytop = ytop;
}

Float64 GenericShape::GetYtop() const
{
   return m_Ytop;
}

void GenericShape::SetYbottom(Float64 ybot)
{
   m_Ybottom = ybot;
}

Float64 GenericShape::GetYbottom() const
{
   return m_Ybottom;
}

void GenericShape::SetXleft(Float64 xleft)
{
   m_Xleft = xleft;
}

Float64 GenericShape::GetXleft() const
{
   return m_Xleft;
}

void GenericShape::SetXright(Float64 xright)
{
   m_Xright = xright;

}

Float64 GenericShape::GetXright() const
{
   return m_Xright;
}

void GenericShape::SetPerimeter(Float64 p)
{
   m_Perimeter = p;
}

Float64 GenericShape::GetPerimeter() const
{
   return m_Perimeter;
}

void GenericShape::Reflect(const Line2d& line)
{
   m_pCentroid->Move(GeometricOperations::ReflectPointAcrossLine(*m_pCentroid, line));
}

std::unique_ptr<Shape> GenericShape::CreateReflectedShape(const Line2d& line) const
{
   auto clone = CreateClone();
   clone->Reflect(line);
   return clone;
}

void GenericShape::Offset(Float64 dx, Float64 dy)
{
   Offset(Size2d(dx, dy));
}

void GenericShape::Offset(const Size2d& delta)
{
   m_pCentroid->Offset(delta);
}

void GenericShape::Move(LocatorPoint lp, const Point2d& to)
{
   Offset(to - GetLocatorPoint(lp));
}

void GenericShape::Move(const Point2d& from, const Point2d& to)
{
   Offset(to - from);
}

void GenericShape::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   Rotate(Point2d(cx, cy), angle);
}

void GenericShape::Rotate(const Point2d& center, Float64 angle)
{
   m_pCentroid->Rotate(center, angle);
   m_Rotation += angle;
}

void GenericShape::SetHookPoint(std::shared_ptr<Point2d> hookPnt)
{
   SetCentroid(hookPnt);
}

void GenericShape::SetHookPoint(const Point2d& hookPnt)
{
   SetCentroid(hookPnt);
}

std::shared_ptr<Point2d> GenericShape::GetHookPoint()
{
   return GetCentroid();
}

std::shared_ptr<const Point2d> GenericShape::GetHookPoint() const
{
   return GetCentroid();
}

Point2d GenericShape::GetLocatorPoint(LocatorPoint lp) const
{
   Point2d p(*m_pCentroid);
   switch (lp)
   {
   case Shape::LocatorPoint::HookPoint:
      break;

   case Shape::LocatorPoint::TopLeft:
      p.Offset(-m_Xleft,m_Ytop);
      break;

   case Shape::LocatorPoint::TopCenter:
      p.Offset(0, m_Ytop);
      break;

   case Shape::LocatorPoint::TopRight:
      p.Offset(m_Xright,m_Ytop);
      break;

   case Shape::LocatorPoint::CenterLeft:
       p.Offset(-m_Xleft, 0);
      break;

   case Shape::LocatorPoint::CenterCenter:
      break;

   case Shape::LocatorPoint::CenterRight:
      p.Offset(m_Xright, 0);
      break;

   case Shape::LocatorPoint::BottomLeft:
      p.Offset(-m_Xleft, -m_Ybottom);
      break;

   case Shape::LocatorPoint::BottomCenter:
      p.Offset(0, -m_Ybottom);
      break;

   case Shape::LocatorPoint::BottomRight:
      p.Offset(m_Xright,-m_Ybottom);
      break;
   }

   return p;
}

void GenericShape::SetLocatorPoint(LocatorPoint lp, const Point2d& position)
{
   Move(GetLocatorPoint(lp), position);
}

ShapeProperties GenericShape::GetProperties() const
{
   // rotate properties into correct orientation.
   Float64 ixx(m_Ixx), ixy(m_Ixy), iyy(m_Iyy);
   if (!IsZero(m_Rotation))
   {
      MohrCircle mc(m_Ixx, m_Iyy, m_Ixy);
      std::tie(ixx,iyy,ixy) = mc.ComputeState(m_Rotation);
   }

   ShapeProperties props(m_Area, *m_pCentroid, ixx, iyy, ixy, m_Xleft, m_Ybottom, m_Xright, m_Ytop);
   return props;
}

Rect2d GenericShape::GetBoundingBox() const
{
   auto [cx,cy] = m_pCentroid->GetLocation();
   return Rect2d(cx - m_Xleft, cy - m_Ybottom, cx + m_Xright, cy + m_Ytop);
}

std::vector<Point2d> GenericShape::GetPolyPoints() const
{
   return std::vector<Point2d>{*m_pCentroid};
}

bool GenericShape::PointInShape(const Point2d& p) const
{
   auto [x,y] = p.GetLocation();
   auto [cx,cy] = m_pCentroid->GetLocation();

   if ( (cx-m_Xleft <= x && x <= cx+m_Xright) &&
        (cy-m_Ybottom <= y && y <= cy+m_Ytop) )
   {
      return true;
   }
   else
   {
      return false;
   }
}

std::unique_ptr<Shape> GenericShape::CreateClippedShape(const Line2d& line, Line2d::Side side) const
{
   // if CG is on the right of the line, create a clone, otherwise
   // consider the shape to be clipped away

   Float64 d = -1.0*line.DistanceToPoint(*m_pCentroid);
   if ( d <= 0 )
   {
      // CG is on the left side of the line
      return nullptr;
   }
   else
   {
      // CG is on the right side of the line
      return CreateClone();
   }
}

std::unique_ptr<Shape> GenericShape::CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const
{
   if (r.Contains(*m_pCentroid))
   {
      return CreateClone();
   }
   return nullptr;
}

Float64 GenericShape::GetFurthestDistance(const Line2d& line, Line2d::Side side) const
{
   auto [p, fd] = GetFurthestPoint(line, side);
   return fd;
}

std::pair<Point2d,Float64> GenericShape::GetFurthestPoint(const Line2d& line, Line2d::Side side) const
{
   auto furthestPoint = *m_pCentroid;

   // get distance from left side of line to center
   auto furthestDistance = line.DistanceToPoint(*m_pCentroid);
   if (side == Line2d::Side::Right)
      furthestDistance = -furthestDistance;

   return std::make_pair(furthestPoint, furthestDistance);
}

std::unique_ptr<Shape> GenericShape::CreateClone() const
{
    auto clone = std::make_unique<GenericShape>(*this); // this copies a shared pointer so clone has the same centroid object as this
    clone->SetCentroid(std::make_shared<WBFL::Geometry::Point2d>(*GetCentroid())); // setting the centroid by reference creates a new shared pointer inside of clone
    return clone;
}
