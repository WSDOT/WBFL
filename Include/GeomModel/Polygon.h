///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMMODEL_POLYGON_H_
#define INCLUDED_GEOMMODEL_POLYGON_H_
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/ShapeImpl.h>
#include <GeomModel/ShapeProperties.h>

namespace WBFL
{
   namespace Geometry
   {
   /// A general polygon.
   ///
   /// \image html PolyShape/PolyShape.jpg
   /// The points of the polygon can be defined clockwise or counter-clockwise. The polygon can be open (first and last points are not the same) or closed (first and last points are the same).
   /// The hook point is the first point of the polygon. Moving the hook point causes all the points of the polygon to move.
   /// While it is possible to create degenerate shapes, shapes where edges cross(like a bowtie), shape properties will not be computed correctly for these types of shapes.
   /// 
   /// Specifying symmetry can greatly improve efficiency. Points may be defined for half of a polygon with either the a line parallel to the Y-axis or the X-axis as the axis of symmetry.
   /// The half-polygon cannot have points that define an edge that is coincident with the axis of symmetry.
   /// 
   /// ShapeProperties in global coordinates are computed with the following equations:
   /// \f[ A = \sum{(x_{i+1} - x_i)y_i + \frac{1}{2}(x_{i+1} - x_i)(y_{i+1} - y_i)} \f]
   /// \f[ I_x = \sum{
   ///           \frac{{y_i}^3(x_{i+1} - x_i)}{12} 
   ///           + (x_{i+1}-x_i)y_i {\frac{y_i}{2}}^2 
   ///           + \frac{(y_{i+1} - y_i)^3 (x_{i+1} - x_i)}{36}
   ///           + \frac{1}{2} (x_{i+1} - x_i)(y_{i+1} - y_i) \left[ \frac{(y_{i+1} - y_i)}{3} + y_i \right] ^3 
   ///           } \f]
   /// \f[ I_y = \sum{
   ///           \frac{y_i(x_{i+1} - x_i)^3}{12} 
   ///           + (x_{i+1}-x_i)y_i \left[ x_i + \frac{(x_{i+1} - x_i)}{2} \right]^2 
   ///           + \frac{(y_{i+1} - y_i)(x_{i+1} - x_i)^3 }{36}
   ///           + \frac{1}{2} (x_{i+1} - x_i)(y_{i+1} - y_i) \left[ \frac{2(x_{i+1} - x_i)}{3} + x_i \right] ^3 
   ///           } \f]
   /// \f[ I_{xy} = \sum{
   ///            (x_{i+1} - x_i)\frac{{y_i}^2}{2} \left( x_i + \frac{x_{i+1} - x_i}{2} \right)
   ///            + \frac{1}{2} (x_{i+1} - x_i)(y_{i+1} - y_i) \left( \frac{y_{i+1} - y_i}{3} - y_i  \right) \left[ \frac{2(x_{i+1} - x_i)}{3} + x_i \right]
   ///            + \frac{(x_{i+1} - x_i)^2(y_{i+1} - y_i)^2}{72}
   ///            } \f]
   /// \f[ \overline{x} = \frac{ \sum{ \frac{1}{2}y_i(x_{i+1} - x_i)(x_{i+1} + x_i) + \frac{1}{2}(x_{i+1} - x_i)(y_{i+1} - y_i) \left[ \frac{2}{3}(x_{i+1} + x_i) + x_i \right] } }{A} \f]
   /// \f[ \overline{y} = \frac{ \sum{ \frac{1}{2}{y_i}^2(x_{i+1} - x_i) + \frac{1}{2}(x_{i+1} - x_i)(y_{i+1} - y_i) \left[ \frac{1}{3}(y_{i+1} + y_i) + y_i \right] } }{A} \f]

class GEOMMODELCLASS Polygon : public ShapeImpl
{
public:
   enum class Symmetry {None,X,Y};

   Polygon() = default;
   Polygon(std::shared_ptr<Point2d>& hookPnt);
   Polygon(const Polygon&) = default;

   virtual ~Polygon() = default;

   Polygon& operator=(const Polygon&) = default;

   /// Defines the symmetry of the shape. For symmetry about a line parallel to the X axis, axis is the Y value for that line.
   void SetSymmetry(Symmetry sym,///< type of symmetry
                    Float64 axis=0 ///< location of the axis of symmetry
   );
   Symmetry GetSymmetry() const;
   Float64 GetSymmetryAxis() const;

   void AddPoint(Float64 x, Float64 y);
   void AddPoint(const Point2d& p);

   /// Adds points to the polygon
   void AddPoints(const std::vector<Point2d>& points);

   /// Replaces the points
   void SetPoints(const std::vector<Point2d>& points);

   /// Remove all points from the polygon.
   void Clear();

   /// Removes a point from the polygon.
   /// If the polygon has an axis of symmetry, the point index must be that of a real
   /// point, not a mirrored point
   void RemovePoint(IndexType idx);

   /// Returns the point at the specified index.
   Point2d GetPoint(IndexType idx) const;

   /// Returns the total number of points in the polygon, including points defined by symmetry
   IndexType GetCount() const;

   /// Replaces the point at the specified index.
   /// If the polygon has an axis of symmetry, the point index must be that of a real
   /// point, not a mirrored point
   void ReplacePoint(IndexType idx, Float64 x,Float64 y);

   /// Replaces the point at the specified index.
   /// If the polygon has an axis of symmetry, the point index must be that of a real
   /// point, not a mirrored point
   void ReplacePoint(IndexType idx,const Point2d& p);

   /// Returns a point-wise representation of the shape
   virtual std::vector<Point2d> GetPolyPoints() const override;

   /// Creates a clone.
   virtual std::unique_ptr<Shape> CreateClone() const override;

   /// Assigns a Properties object to the object pointed to by pProperties. 
   /// The origin of the shape properties object is the centroid of this shape
   /// with a rotation of zero.
   virtual ShapeProperties GetProperties() const override;

   /// Returns the smallest rectangle that bounds the entire shape.
   virtual Rect2d GetBoundingBox() const override;

   virtual bool PointInShape(const Point2d& p) const override;
   virtual Float64 GetPerimeter() const override;

   // Clips this shape against line.  Clips away the portion of the shape on the
   // side of the line defined by side.  This is a factory method.  You are 
   // responsible for freeing the memory allocated by this method.  If the shape
   // lies entirely on the clipping side of the line 0 is returned. Any listeners
   // to the original section are not transferred to this new section.
   virtual std::unique_ptr<Shape> CreateClippedShape(const Line2d& line, Line2d::Side side) const override;

   /// Clips this shape against rectangle r.  Clips in or out of the rectangle
   /// as specified by region.  This is a factory method.  You are responsible 
   /// for freeing memory allocated by this method.  This method returns 0 if, 
   /// the shape lies entirely within the clipping rectangle and region is set 
   /// to clip out, or the shape and the rectangle do not intersect and region 
   /// is to clip in. Any listeners to the original section are not transferred
   /// to this new section.
   virtual std::unique_ptr<Shape> CreateClippedShape(const Rect2d& r,Shape::ClipRegion region) const override;

   /// Returns the distance to a line that is parallel to line, on specified 
   /// side of line,  that passes through the furthest point on the shape 
   /// from line.
   virtual Float64 GetFurthestDistance(const Line2d& line, Line2d::Side side) const override;

#if defined _DEBUG
   /// Returns true if the class is in a valid state, otherwise returns false
   virtual bool AssertValid() const override;

   /// Dumps the contents of the class to the given stream.
   virtual void Dump(WBFL::Debug::LogContext& os) const override;
#endif // _DEBUG

#if defined _UNITTEST
   /// Self-diagnostic test function.
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
protected:
   virtual void DoOffset(const Size2d& delta) override;
   virtual void DoRotate(const Point2d& center, Float64 angle) override;

private:
   Symmetry m_Symmetry{ Symmetry::None };
   Float64 m_SymmetryAxis{ 0.0 };

   mutable std::vector<Point2d> m_Points;

   mutable bool m_bIsDirty{ true };
   mutable ShapeProperties m_Properties;
   mutable Rect2d m_BoundingBox;
   mutable Float64 m_Perimeter{ 0.0 };

   void UpdateProperties() const;
   void UpdatePoints() const;
   bool PointInShape_Private(const Point2d & point) const;
   std::unique_ptr<Shape> CreateClippedShape_Private(const Line2d & line, Line2d::Side side, const std::vector<Point2d>&points) const;
   Point2d GetMirroredPoint(const Point2d& point) const;
   void GetAllPoints(std::vector<Point2d>*points) const;
};


   }; // Geometry
}; // WBFL



#endif // INCLUDED_GEOMMODEL_POLYGON_H_
