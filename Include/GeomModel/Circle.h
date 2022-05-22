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

#ifndef INCLUDED_GEOMMODEL_CIRCLE_H_
#define INCLUDED_GEOMMODEL_CIRCLE_H_
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/ShapeOnAlternativePolygonImpl.h>

namespace WBFL
{
   namespace Geometry
   {
class Polygon;

/// Object representing a Circle
///
/// \image html Circle/Circle.jpg
/// Section properties in centroidal coordinates. 
/// \f[ A = \pi r^2 \f]
/// \f[ I_x = I_y =\frac{\pi r^2}{4} \f]
/// \f[ I_{xy} = 0 \f]
/// \f[ Perimeter = 2 \pi r \f]
class GEOMMODELCLASS Circle : public ShapeOnAlternativePolygonImpl
{
public:
   /// Default constructor.  Creates a Circle with radius equal 
   /// to zero,  with its hook point at (0,0).
   Circle();

   /// Explicit constructor.  Creates a Circle with radius, and
   /// the hook point positioned at hookPnt.
   Circle(std::shared_ptr<Point2d>& hookPnt, Float64 radius);
   Circle(const Point2d& hookPnt, Float64 radius);

   Circle(const Circle&);
   Circle& operator=(const Circle&);

   virtual ~Circle();

   // Sets the Radius of the Circle.
   void SetRadius(Float64 radius);

   /// Returns the Radius of the Circle.
   Float64 GetRadius() const;

   void SetParameters(const Point2d& center, Float64 radius);
   void SetParameters(std::shared_ptr<Point2d>& center, Float64 radius);
   void GetParameters(std::shared_ptr<Point2d>* pCenter, Float64* radius) const;

   void ThroughTwoPoints(const Point2d& p1, const Point2d& p2);
   void ThroughThreePoints(const Point2d& p1, const Point2d& p2, const Point2d& p3);

   /// Translates a shape by a delta amount.
   virtual void DoOffset(const Size2d& delta) override;

   /// Rotates a shape.  The rotation is centered about point center.  The 
   /// rotation angle is measured in radians counter clockwise.
   virtual void DoRotate(const Point2d& center, Float64 angle) override;

   ///  Returns the shape properties
   virtual ShapeProperties GetProperties() const override;

   /// Returns the smallest rectangle that bounds the entire shape.
   virtual Rect2d GetBoundingBox() const override;

   virtual bool PointInShape(const Point2d& p) const override;
   virtual Float64 GetPerimeter() const override;

   bool PointOnCircle(const Point2d& p);

   /// Creates a clone of this shape.
   virtual std::unique_ptr<Shape> CreateClone() const override;

   /// Clips this shape against line.  Clips away the portion of the shape on the
   /// side of the line defined by side.  This is a factory method.  You are 
   /// responsible for freeing the memory allocated by this method.  If the shape
   /// lies entirely on the clipping side of the line 0 is returned.
   virtual std::unique_ptr<Shape> CreateClippedShape(const Line2d& line, Line2d::Side side) const;

   /// Clips this shape against Circle r.  Clips in or out of the Circle
   /// as specified by region.  This is a factory method.  You are responsible 
   /// for freeing memory allocated by this method.  This method returns 0 if, 
   /// the shape lies entirely within the clipping Circle and region is set 
   /// to clip out, or the shape and the Circle do not intersect and region 
   /// is to clip in.
   virtual std::unique_ptr<Shape> CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const override;

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
   // Self-diagnostic test function.
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

protected:
   virtual void OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const override;

private:
   Float64 m_Radius{ 0.0 };
   void Copy(const Circle& other);
};

   }; // Geometry
}; // WBFL

#endif // INCLUDED_GEOMMODEL_CIRCLE_H_
