///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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
#include <GeomModel/Vector2d.h>
#include <MathEx.h> // for TOLERANCE

namespace WBFL
{
   namespace Geometry
   {
      class LineSegment2d;
      class Point2d;
      class Size2d;

      /// Interface defining a directed line of infinite length.
      ///
      /// A line is described by its implicit form, its explicit form, or by two points.
      /// The implicit form consists of the shortest distance from the origin to the line and a unit vector normal to the line.
      /// \image html Line2d/Implicit.jpg
      /// The explicit from consists of a point and a unit vector in the direction of the line.
      /// \image html Line2d/Explicit.jpg
      /// The line can also be described as passing through two points.The direction of the line is from the first point, towards the second point.
      /// \image html Line2d/TwoPoints.jpg
      class GEOMMODELCLASS Line2d
      {
      public:
         /// The side of a line can be best defined by an illustration.  Imagine 
         /// you are standing at the point P1 and looking toward P2: Left is to the 
         /// left side, Right is the right side.
         enum class Side { Left, Right };

         /// Creates a line parallel to the x-axis at y = 0.
         Line2d();

         /// Explicit constructor.  Creates a line passing through points p1 and p2.
         /// Has the same behavior as the default constructor if the points are identical
         Line2d(const Point2d& p1,const Point2d& p2);

         /// Explicit constructor.  Creates a line from line segment ls.
         Line2d(const LineSegment2d& ls);

         /// Explicit constructor.  Creates a line from its implicit representation
         /// refer to Graphics Gems, Chapter 1 for details
         /// c  - distance from closest point on origin to the origin
         /// rn - vector normal to the line. Left side of line is in positive rn
         Line2d(Float64 c, const Vector2d& rn);

         /// Explicit constructor.  Creates a line from its explicit representation
         /// refer to Graphics Gems, Chapter 1 for details
         /// ru - a point on the line
         /// rv - tangent vector to line. Left side of line is on left looking in 
         ///      positive rv direction.
         Line2d(const Point2d& ru, const Vector2d& rv);

         virtual ~Line2d();

         Line2d(const Line2d&) = default;
         Line2d& operator=(const Line2d&) = default;

         bool operator==(const Line2d& other) const;
         bool operator!=(const Line2d& other) const;

         /// Returns true if point is contained in the locus of points that define 
         /// this line,  otherwise returns false.
         bool ContainsPoint(const Point2d& point,Float64 tolerance = TOLERANCE) const;

         /// Returns the slope of the line.  If the line is vertical and pointing 
         /// upwards,  returns std::numeric_limits<float>::infinity().
         /// If the line is vertical and pointing downwards,  returns 
         /// -std::numeric_limits<float>::infinity()
         Float64 GetSlope() const;

         /// Returns true if rOther is colinear to this.
         bool IsColinear(const Line2d& rOther) const;

         /// Offsets this line by the given delta arguments. This line is changed
         /// by translating its control points by the given distance.  Returns a 
         /// reference to this line.
         Line2d& Offset(Float64 dx,Float64 dy);
         Line2d& Offset(const Size2d& size);
         Line2d& Offset(Float64 offset);

         /// Returns a line which is offset to this line by the given displacement 
         /// arguments. This line is not changed.
         Line2d OffsetBy(Float64 dx, Float64 dy) const;
         Line2d OffsetBy(const Size2d& size) const;
         Line2d OffsetBy(Float64 offset) const;

         /// Returns a point on the line which is nearest to the given point.
         Point2d PointOnLineNearest(const Point2d& point) const;

         /// Returns the distance from the line to a given point. If the point is on
         /// the left side of the line, it returns a positive value. If the point is
         /// on the right side of the line it returns a negative value.
         Float64 DistanceToPoint(const Point2d& rPnt) const;

         /// Rotates this line about the given center point by the given angle. 
         /// This line is changed. Returns a reference to this line.
         Line2d& Rotate(const Point2d& centerPoint, Float64 angle);

         /// Returns a line equal to this line rotated about the given center point 
         /// by the given angle. This line is not changed.
         Line2d RotateBy(const Point2d& centerPoint, Float64 angle) const;

         /// Returns a line that is parallel to this line and offset from this line 
         /// by the specified amount.  The offset is measured perpendicular to this 
         /// line.  An negative offset reverses the effect of the side argument.
         Line2d Parallel(Float64 offset, Line2d::Side side) const;

         /// Returns a line that is parallel to this line and passes through point.
         Line2d Parallel(const Point2d& point) const;

         /// Returns a line that passes from point to the normal to this line. 
         Line2d Normal(const Point2d& point) const;
   
         /// Returns the side of the line that the point is on.  If the point
         /// is on the line, Left is returned.
         Line2d::Side GetSide(const Point2d& point) const;

         /// Reverse the direction of the line.
         void Reverse();

         /// Set implicit form of line
         void SetImplicit(Float64 c, const Vector2d& n);
   
         /// get implicit form of line
         std::pair<Float64,Vector2d> GetImplicit() const;
   
         /// set explicit form of line
         void SetExplicit(const Point2d& u, const Vector2d& v);
   
         /// get explicit form of line
         std::pair<Point2d,Vector2d> GetExplicit() const;

         /// Sets a line passing through points p1 and p2.
         /// Has the same behavior as the default constructor if the points are 
         /// identical. These points are not retrievable.
         void ThroughPoints(const Point2d& p1,const Point2d& p2);

      private:
         // line is stored implicitly (refer to Graphics Gems)
         Vector2d m_N; // normal vector *** Must be normalized !!!!
         Float64  m_c{ 0.0 }; // distance from origin

#if defined _DEBUG
         bool AssertValid() const;
#endif // _DEBUG
      };
   }; // Geometry
}; // WBFL
