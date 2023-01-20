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
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Shape.h>
#include <GeomModel/ShapeProperties.h>

namespace WBFL
{
   namespace Geometry
   {

/// Composite shapes are composed of primitive geometric shapes, such as circles and polygons, can be created to
/// represent complex shapes. The geometric properties of complex shapes can be computed.
class GEOMMODELCLASS CompositeShape : public Shape
{
public:
   enum class ShapeType { Solid, Void };

   CompositeShape();
   CompositeShape(const CompositeShape& rOther);
   virtual ~CompositeShape();

   CompositeShape& CompositeShape::operator= (const CompositeShape& rOther);

   virtual void Offset(const Size2d& delta) override;
   virtual void Rotate(const Point2d& center, Float64 angle) override;

   virtual void Offset(Float64 dx, Float64 dy) override;
   virtual void Move(LocatorPoint lp, const Point2d& to) override;
   virtual void Move(const Point2d& from, const Point2d& to) override;
   virtual void Rotate(Float64 cx, Float64 cy, Float64 angle) override;

   virtual void SetHookPoint(std::shared_ptr<Point2d>& hookPnt) override;
   virtual void SetHookPoint(const Point2d& hookPnt) override;
   virtual std::shared_ptr<Point2d>& GetHookPoint() override;
   virtual const std::shared_ptr<Point2d>& GetHookPoint() const override;

   virtual Point2d GetLocatorPoint(LocatorPoint point) const override;
   virtual void SetLocatorPoint(LocatorPoint lp, Point2d& position) override;

   virtual void Reflect(const Line2d& line) override;
   virtual std::unique_ptr<Shape> CreateReflectedShape(const Line2d& line) const override;

   /// Returns the geometric properties of the shape
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
   virtual void GetFurthestPoint(const Line2d& line, Line2d::Side side, Point2d& furthestPoint, Float64& furthestDistance) const override;

   /// Returns the perimeter of the shape
   virtual Float64 GetPerimeter() const override;

   /// Creates a clone of this shape.
   virtual std::unique_ptr<Shape> CreateClone() const override;

   /// Adds a clone of shape to the composite
   void AddShape(const Shape& shape,ShapeType shapeType = ShapeType::Solid);

   /// Adds a shape to the composite
   void AddShape(std::unique_ptr<Shape>&& shape, ShapeType shapeType = ShapeType::Solid);

   /// Removes a shape from the composite
   void RemoveShape(IndexType idx);

   /// Removes all shapes from the composite
   void Clear();

   /// Returns a shape
   std::shared_ptr<Shape>& GetShape(IndexType idx);

   /// Returns a shape
   const std::shared_ptr<Shape>& GetShape(IndexType idx) const;

   /// Returns the type of shape
   ShapeType GetShapeType(IndexType idx) const;

   /// Returns true if a shape is solid
   bool IsSolid(IndexType idx) const;

   /// Returns true if a shape is a void
   bool IsVoid(IndexType idx) const;

   /// Returns the number of shapes
   IndexType GetShapeCount() const;

#if defined _DEBUG
   virtual bool AssertValid() const;
   virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

protected:
   const ShapeProperties& GetShapeProperties() const;
   void SetDirtyFlag(bool bFlag = true);
   bool GetDirtyFlag() const;

private:
   std::vector<std::pair<std::shared_ptr<Shape>,ShapeType>> m_Shapes;
   std::vector<Point2d> m_DummyPoints; // used in GetPolyPoints if this composite is empty
   std::shared_ptr<Point2d> m_DummyHookPoint{ std::make_shared<Point2d>(0,0) };

   mutable bool m_bIsDirty{ true };
   mutable ShapeProperties m_Properties;

   void Copy(const CompositeShape& other);
};

   }; // Geometry
}; // WBFL
