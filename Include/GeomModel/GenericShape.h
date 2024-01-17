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
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Shape.h>
#include <GeomModel/ShapeProperties.h>

namespace WBFL
{
   namespace Geometry
   {
      class Point2d;
      class Rect2d;

      /// Interface defining a generic shape.
      ///
      /// A generic shape is defined only by its properties. It does not represent an actual geometric entity.
      /// The properties of a generic shape are similar to the properties of the ShapeProperties object but differs
      /// in that a generic shape can be used like more concrete shape types
      class GEOMMODELCLASS GenericShape : public Shape
      {
      public:
         GenericShape() = default;

         // Copy constructor. The centroid is shared with the copied object.
         GenericShape(const GenericShape&) = default;

         GenericShape(Float64 area,
            std::shared_ptr<Point2d>& centroid,
            Float64 ixx = 0, Float64 iyy = 0, Float64 ixy = 0,
            Float64 xLeft = 0, Float64 yBottom = 0,
            Float64 xRight = 0, Float64 yTop = 0,
            Float64 perimeter = 0);

         GenericShape(Float64 area,
            const Point2d& centroid, ///< A copy of this point is created at stored as a shared_ptr
            Float64 ixx = 0, Float64 iyy = 0, Float64 ixy = 0,
            Float64 xLeft = 0, Float64 yBottom = 0,
            Float64 xRight = 0, Float64 yTop = 0,
            Float64 perimeter = 0);


         ~GenericShape() = default;

         GenericShape& operator=(const GenericShape&) = default;

         void SetProperties(Float64 area, const Point2d& centroid, Float64 ixx, Float64 iyy, Float64 ixy, Float64 xLeft, Float64 yBottom, Float64 xRight, Float64 yTop, Float64 perimeter);
         void SetProperties(Float64 area, std::shared_ptr<Point2d>& centroid, Float64 ixx, Float64 iyy, Float64 ixy, Float64 xLeft, Float64 yBottom, Float64 xRight, Float64 yTop, Float64 perimeter);
         void GetProperties(Float64* area, std::shared_ptr<Point2d>* centroid, Float64* ixx, Float64* iyy, Float64* ixy, Float64* xLeft, Float64* yBottom, Float64* xRight, Float64* yTop, Float64* perimeter) const;

         /// Sets the area of the shape.
         void SetArea(Float64 area);

         /// Returns the area of the shape.
         Float64 GetArea() const;

         /// Sets the centroid of the shape, measured in current coordinates.
         /// The shared_ptr is moved to the location of centroid
         void SetCentroid(const Point2d& centoid);

         /// Sets the centroid of the shape, measured in current coordinates.
         /// The shared_ptr is replace with centroid
         void SetCentroid(std::shared_ptr<Point2d> centoid);

         /// Returns the centroid of the shape, measured in current coordinates.
         std::shared_ptr<Point2d> GetCentroid();
         std::shared_ptr<const Point2d> GetCentroid() const;

         /// Sets the moment of inertia about the x axis of the current coordinate system.
         void SetIxx(Float64 ixx);

         /// Returns the moment of inertia about the x axis of the current coordinate system.
         Float64 GetIxx() const;

         /// Sets the moment of inertia about the y axis of the current coordinate system.
         void SetIyy(Float64 iyy);

         /// Returns the moment of inertia about the y axis of the current coordinate system.
         Float64 GetIyy() const;

         /// Returns the product of inertia about the current coordinate system.
         void SetIxy(Float64 ixy);

         /// Returns the product of inertia about the current coordinate system.
         Float64 GetIxy() const;

         /// Sets the distance from the centroid to the top edge of the bounding 
         /// rectangle. This distance is always given using the centroidal orientation.
         void SetYtop(Float64 ytop);

         /// Returns the distance from the centroid to the top edge of the bounding 
         /// rectangle. This distance is always given using the centroidal orientation.
         Float64 GetYtop() const;

         /// Sets the distance from the centroid to the bottom edge of the 
         /// bounding rectangle. This distance is always given using the centroidal orientation.
         void SetYbottom(Float64 ybot);

         /// Returns the distance from the centroid to the bottom edge of the 
         /// bounding rectangle. This distance is always given using the centroidal orientation.
         Float64 GetYbottom() const;

         /// Sets the distance from the centroid to the left edge of the bounding 
         /// rectangle. This distance is always given using the centroidal orientation.
         void SetXleft(Float64 xleft);

         /// Returns the distance from the centroid to the left edge of the bounding 
         /// rectangle. This distance is always given using the centroidal orientation.
         Float64 GetXleft() const;

         /// Sets the distance from the centroid to the right edge of the bounding 
         /// rectangle. This distance is always given using the centroidal orientation.
         void SetXright(Float64 xright);
   
         // Returns the distance from the centroid to the right edge of the bounding 
         // rectangle. This distance is always given using the centroidal orientation.
         Float64 GetXright() const;

         /// Sets the perimeter of the shape
         void SetPerimeter(Float64 p);

         /// Offset a shape by a delta amount.
         virtual void Offset(Float64 dx, Float64 dy) override;
         virtual void Offset(const Size2d& delta) override;

         /// Move a shape by moving from one point in space to another. 
         virtual void Move(LocatorPoint point, const Point2d& to) override;
         virtual void Move(const Point2d& from, const Point2d& to) override;

         /// Rotates a shape.  The rotation is centered about point center.  The 
         /// rotation angle is measured in radians counter clockwise.
         virtual void Rotate(Float64 cx, Float64 cy, Float64 angle) override;
         virtual void Rotate(const Point2d& center, Float64 angle) override;

         /// Sets the hook point location. Same as calling SetCentroid
         virtual void SetHookPoint(const Point2d& hookPnt) override;

         /// Sets the hook point location. Same as calling SetCentroid
         virtual void SetHookPoint(std::shared_ptr<Point2d> hookPnt) override;

         /// Returns the hook point location. Same as calling GetCentroid
         virtual std::shared_ptr<Point2d> GetHookPoint() override;

         /// Returns the hook point location. Same as calling GetCentroid
         virtual std::shared_ptr<const Point2d> GetHookPoint() const override;

         /// Returns a point located at the specified location on the bounding box 
         /// around the shape.
         virtual Point2d GetLocatorPoint(LocatorPoint lp) const override;

         /// Moves the shape so that the locator point is at the specified position
         virtual void SetLocatorPoint(LocatorPoint lp, const Point2d& position) override;

         /// Assigns a Properties object to the object pointed to by pProperties. 
         /// The origin of the shape properties object is the centroid of this shape
         /// with a rotation of zero.
         virtual ShapeProperties GetProperties() const override;

         /// Returns the smallest rectangle that bounds the entire shape.
         virtual Rect2d GetBoundingBox() const override;

         /// Returns a point-wise representation of the shape
         virtual std::vector<Point2d> GetPolyPoints() const override;

         /// Tests a point to determine if it is within the boundary of this shape. Points that are on the boundary of the shape are not within the shape.
         virtual bool PointInShape(const Point2d& p) const override;

         /// Clips this shape against line.  Clips away the portion of the shape on the
         /// side of the line defined by side.  This is a factory method.  You are 
         /// responsible for freeing the memory allocated by this method.  If the shape
         /// lies entirely on the clipping side of the line a nullptr is returned.
         virtual std::unique_ptr<Shape> CreateClippedShape(const Line2d& line, Line2d::Side side) const override;

         /// Clips this shape against rectangle r.  Clips in or out of the rectangle
         /// as specified by region.  This method returns a nullptr if, 
         /// the shape lies entirely within the clipping rectangle and region is set 
         /// to clip out, or the shape and the rectangle do not intersect and region 
         /// is to clip in.
         virtual std::unique_ptr<Shape> CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const override;

         /// Returns the distance to a line that is parallel to line, on specified 
         /// side of line,  that passes through the furthest point on the shape 
         /// from line.
         virtual Float64 GetFurthestDistance(const Line2d& line, Line2d::Side side) const override;

         /// Gets the distance and location of the point on the shape that is furthest from, and on the specified side of, the provided line
         virtual std::pair<Point2d,Float64> GetFurthestPoint(const Line2d& line, Line2d::Side side) const override;

         /// Returns the perimeter of the shape
         virtual Float64 GetPerimeter() const override;

         /// Reflects the centroid point across the line.
         /// Since this shape doesn't have an actual shape, the properties are not altered.
         virtual void Reflect(const Line2d& line) override;
         virtual std::unique_ptr<Shape> CreateReflectedShape(const Line2d& line) const override;

         /// Creates a clone of this shape.
         virtual std::unique_ptr<Shape> CreateClone() const override;

      private:
         Float64 m_Area{ 0.0 };
         std::shared_ptr<Point2d> m_pCentroid{ std::make_shared<Point2d>() };
         Float64 m_Ixx{ 0.0 };
         Float64 m_Iyy{ 0.0 };
         Float64 m_Ixy{ 0.0 };
         Float64 m_Xleft{ 0.0 };
         Float64 m_Xright{ 0.0 };
         Float64 m_Ytop{ 0.0 };
         Float64 m_Ybottom{ 0.0 };
         Float64 m_Perimeter{ 0.0 };
         Float64 m_Rotation{ 0.0 };
      };
   }; // Geometry
}; // WBFL
