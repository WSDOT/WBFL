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

#ifndef INCLUDED_GEOMMODEL_CIRCULARSEGMENT_H_
#define INCLUDED_GEOMMODEL_CIRCULARSEGMENT_H_
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/ShapeOnAlternativePolygonImpl.h>
#include <GeomModel/LineSegment2d.h>
/// <summary>
/// 
/// </summary>
namespace WBFL
{
   namespace Geometry
   {
class Polygon;

/// Object representing a circular segment
///
/// \image html CircularSegment/CircularSegment.jpg
///
/// \f[ \alpha (radians) \f]
/// \f[ A = r^2 \left(\alpha - \frac{\sin 2\alpha}{2} \right) \f]
/// \f[ \overline{x} = \frac{4r}{3} \frac{\sin^3\alpha}{2\alpha-\sin 2\alpha} \f]
/// \f[ \overline{y} = 0 \f]
/// \f[ I_x = \frac{Ar^2}{4} \left(1 - \frac{4\sin^3\alpha\cos\alpha}{3(2\alpha-\sin2\alpha)} \right) \f]
/// \f[ I_y = \frac{Ar^2}{4} \left(1 + \frac{4\sin^3\alpha\cos\alpha}{2\alpha-\sin2\alpha} \right) \f]
class GEOMMODELCLASS CircularSegment : public ShapeOnAlternativePolygonImpl
{
public:
   CircularSegment();
   CircularSegment(const Point2d& center, Float64 radius, Float64 midOrdinate, Float64 rotation);

   virtual ~CircularSegment();

   CircularSegment(const CircularSegment&);
   CircularSegment& operator=(const CircularSegment&);


   /// Locates the shape by placing the center of the circle at the specified point.
   void SetCenter(const Point2d& center);

   /// Gets the center of the circle
   Point2d GetCenter() const;

   /// Sets the Radius of the Circle.
   void SetRadius(Float64 radius);

   /// Returns the Radius of the Circle.
   Float64 GetRadius() const;

   /// Sets the mid-ordinate (aka sagitta).
   void SetMidOrdinate(Float64 mo);

   /// Returns the mid-ordinate (aka sagitta)
   Float64 GetMidOrdinate() const;

   /// Returns the chord connecting the edges of the circular segment
   LineSegment2d GetChord() const;

   /// Sets the rotation.
   void SetRotation(Float64 rotation);

   /// Returns the rotation
   Float64 GetRotation() const;

   /// Sets the interior angle.
   void SetInteriorAngle(Float64 ia);

   /// Returns the interior angle
   Float64 GetInteriorAngle() const;

   /// Translates a shape by a delta amount.
   virtual void DoOffset(const Size2d& delta) override;

   /// Rotates a shape.  The rotation is centered about point center.  The 
   /// rotation angle is measured in radians counter clockwise.
   virtual void DoRotate(const Point2d& center, Float64 angle) override;

   /// Returns the shape properties.
   virtual ShapeProperties GetProperties() const override;

   /// Returns the smallest rectangle that bounds the entire shape.
   virtual Rect2d GetBoundingBox() const override;

   virtual bool PointInShape(const Point2d& p) const override;
   virtual Float64 GetPerimeter() const override;

   // Creates a clone of this shape.
   virtual std::unique_ptr<Shape> CreateClone() const override;

   /// Clips this shape against line.  Clips away the portion of the shape on the
   /// side of the line defined by side. If the shape lies entirely on the clipping side of the line a nullptr is returned
   virtual std::unique_ptr<Shape> CreateClippedShape(const Line2d& line, Line2d::Side side) const override;

   /// Clips this shape against Circle r.  Clips in or out of the Circle
   /// as specified by region. This method returns a nullptr when 
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
   virtual void Dump(dbgDumpContext& os) const override;
#endif // _DEBUG

#if defined _UNITTEST
   // Self-diagnostic test function.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   virtual void OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const override;

private:
   Float64 m_Radius{ 0.0 };
   Float64 m_MidOrdinate{ 0.0 };
   Float64 m_Rotation{ 0.0 };

   void UpdateHookPoint(const Point2d& center);

   void Copy(const CircularSegment& other);
};

   }; // Geometry
}; // WBFL

#endif // INCLUDED_GEOMMODEL_CIRCULARSEGMENT_H_
