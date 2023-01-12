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

#ifndef INCLUDED_GEOMMODEL_Shape_H_
#define INCLUDED_GEOMMODEL_Shape_H_
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Line2d.h>

namespace WBFL
{
   namespace Geometry
   {
class CompositeShape;
class ShapeProperties;
class Rect2d;

/// A shape is a representation of the boundary contour of something.  A shape
/// could represent the boundary of a section through a structural member or
/// the boundary of a parcel of land.  
/// 
/// This abstract base class provides a framework for extending the shape through inheritance.
class GEOMMODELCLASS Shape
{
public:
   /// Defines the region of a rectangle that a shape should be clipped against.
   enum class ClipRegion{ In, Out };

   /// Defines the major locator points on a bounding rectangle.
   enum class LocatorPoint {HookPoint,
                      TopLeft,    TopCenter,    TopRight,
                      CenterLeft, CenterCenter, CenterRight,
                      BottomLeft, BottomCenter, BottomRight};

   virtual ~Shape() {}

   /// Offset a shape by a delta amount.
   virtual void Offset(Float64 dx, Float64 dy) = 0;
   virtual void Offset(const Size2d& delta) = 0;

   /// Move a shape by moving from one point in space to another. 
   virtual void Move(LocatorPoint point,const Point2d& to) = 0;
   virtual void Move(const Point2d& from,const Point2d& to) = 0;

   /// Rotates a shape.  The rotation is centered about point center.  The 
   /// rotation angle is measured in radians counter clockwise.
   virtual void Rotate(Float64 cx, Float64 cy, Float64 angle) = 0;
   virtual void Rotate(const Point2d& center, Float64 angle) = 0;

   /// Sets the hook point object
   virtual void SetHookPoint(std::shared_ptr<Point2d>& hookPnt) = 0;

   /// Sets the value of the current hook point
   virtual void SetHookPoint(const Point2d& hookPnt) = 0;

   /// Returns the hook point object
   virtual std::shared_ptr<Point2d>& GetHookPoint() = 0;

   /// Returns the hook point object
   virtual const std::shared_ptr<Point2d>& GetHookPoint() const = 0;

   /// Returns a point located at the specified location on the bounding box 
   /// around the shape.
   virtual Point2d GetLocatorPoint(LocatorPoint lp) const = 0;

   /// Moves the shape so that the locator point is at the specified position
   virtual void SetLocatorPoint(LocatorPoint lp, Point2d& position) = 0;

   /// Returns the geometric properties of the shape
   /// The origin of the shape properties object is the centroid of this shape
   /// with a rotation of zero.
   virtual ShapeProperties GetProperties() const  = 0;

   /// Returns the smallest rectangle that bounds the entire shape.
   virtual Rect2d GetBoundingBox() const  = 0;

   /// Returns a point-wise representation of the shape
   virtual std::vector<Point2d> GetPolyPoints() const = 0;

   /// Tests a point to determine if it is within the boundary of this shape. Points that are on the boundary of the shape are not within the shape.
   virtual bool PointInShape(const Point2d& p) const = 0;

   /// Clips this shape against line.  Clips away the portion of the shape on the
   /// side of the line defined by side.  If the shape lies entirely on the clipping side of the line a nullptr is returned.
   virtual std::unique_ptr<Shape> CreateClippedShape(const Line2d& line, Line2d::Side side) const = 0;

   /// Clips this shape against rectangle r.  Clips in or out of the rectangle
   /// as specified by region.  This method returns a nullptr if, 
   /// the shape lies entirely within the clipping rectangle and region is set 
   /// to clip out, or the shape and the rectangle do not intersect and region 
   /// is to clip in.
   virtual std::unique_ptr<Shape> CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const = 0;

   /// Returns the distance to a line that is parallel to line, on specified 
   /// side of line, that passes through the furthest point on the shape from line.
   virtual Float64 GetFurthestDistance(const Line2d& line, Line2d::Side side) const = 0;

   /// Gets the distance and location of the point on the shape that is furthest from, and on the specified side of the provided line
   virtual void GetFurthestPoint(const Line2d& line, Line2d::Side side, Point2d& furthestPoint, Float64& furthestDistance) const = 0;

   /// Returns the perimeter of the shape
   virtual Float64 GetPerimeter() const = 0;

   /// Creates a clone of this shape.
   virtual std::unique_ptr<Shape> CreateClone() const = 0;

#if defined _DEBUG
   /// Returns true if the class is in a valid state, otherwise returns false
   virtual bool AssertValid() const  = 0;

   /// Dumps the contents of the class to the given stream.
   virtual void Dump(WBFL::Debug::LogContext& os) const  = 0;
#endif // _DEBUG
};

   }; // Geometry
}; // WBFL

#endif 
