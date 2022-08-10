///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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

#ifndef INCLUDED_GEOMETRY_PRIMITIVES_H_
#define INCLUDED_GEOMETRY_PRIMITIVES_H_
#pragma once

#include <GeomModel/GeomModelExp.h>


namespace WBFL
{
   namespace Geometry
   {
      class GEOMMODELCLASS Point2d;
      class GEOMMODELCLASS Size2d;
      class GEOMMODELCLASS Rect2d;

      /// Encapsulates the notion of a two-dimension quantity that usually represents a displacement or the height and width of a rectangle
      class GEOMMODELCLASS Size2d
      {
      public:
         Size2d();
         Size2d(Float64 dx, Float64 dy);
         Size2d(const Point2d& point);
         virtual ~Size2d();

         Size2d(const Size2d&) = default;
         Size2d& operator=(const Size2d&) = default;

         /// Returns true if this Size2d object is equal to the rOther Size2d 
         /// object, otherwise returns false.
         bool operator==(const Size2d& rOther) const;

         /// Returns false if this Size2d object is equal to the rOther Size2d 
         /// object, otherwise returns true.
         bool operator!=(const Size2d& rOther) const;

         /// Calculates an offset to this Size object using the give size argument
         /// as the displacement.  Returns (dx+size.Dx(), dy+size.Dy()).  This object
         /// is unchanged.
         Size2d operator+(const Size2d& size) const;

         /// Scales the size object by c. Returns (Dx()*c, Dy()*c).
         Size2d operator*(Float64 c) const;

         /// Scales the size object by c. Returns (Dx()/c, Dy()/c).
         Size2d operator/(Float64 c) const;

         /// Calculates an offset to this Size object using the give size argument
         /// as the displacement.  Returns (dx-size.Dx(), dy-size.Dy()).  This object
         /// is unchanged.
         Size2d operator-(const Size2d& size) const;

         /// Returns the Size object (-dx,-dy). This object is unchanged.
         Size2d operator-() const;

         /// Offset this Size2d object by the give size argument.  This Size2d
         /// object is chaged to (Dx+size.Dx(),Dy+size.Dy()).  Returns a reference
         /// to this object.
         Size2d& operator+=(const Size2d& rOther);

         /// Negatively offset this Size2d object by the give size argument.  
         /// This Size2d object is chaged to (Dx+size.Dx(),Dy+size.Dy()).
         /// Returns a reference to this object.
         Size2d& operator-= (const Size2d& rOther);

         /// Divides Dx and Dy by c.
         Size2d& operator/= (Float64 c);

         /// Multiplies Dx and Dy by c.
         Size2d& operator*= (Float64 c);

         /// Returns the length of the diagonal of the rectangle represented by this object.
         Float64 Magnitude() const;

         /// Returns the size in the x direction.
         Float64 Dx() const;

         /// Returns the size in the x direction.
         Float64& Dx();

         /// Returns the size in the y direction.
         Float64 Dy() const;

         /// Returns the size in the y direction.
         Float64& Dy();

         void SetDimensions(Float64 dx, Float64 dy);
         void SetDimensions(const Point2d& point);

         /// Returns the size dimensions
         void GetDimensions(Float64* dx, Float64* dy) const;

      #if defined _DEBUG
         /// Dumps the contents of the class to the given stream.
         void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         /// Self-Test function. Returns true if successful.
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST

      private:
         Float64 m_Dx{ 0.0 };
         Float64 m_Dy{ 0.0 };
      };

      inline GEOMMODELFUNC Size2d operator/(Size2d& size, Float64 c)
      {   return size.operator/( c ); }
      inline GEOMMODELFUNC Size2d operator/(Float64 c,Size2d& size)
      {   return size.operator/( c ); }
      inline GEOMMODELFUNC Size2d operator*(Size2d& size, Float64 c)
      {   return size.operator*( c ); }
      inline GEOMMODELFUNC Size2d operator*(Float64 c,Size2d& size)
      {   return size.operator*( c ); }

      /// Encapsulates the notion of a two-dimensional point that represents a
      /// position in a Cartesian coordinate system.
      class GEOMMODELCLASS Point2d
      {
      public:
         Point2d();
         Point2d(Float64 x,Float64 y);
         virtual ~Point2d();

         Point2d(const Point2d&) = default;
         Point2d& operator=(const Point2d&) = default;

         bool operator==(const Point2d& other) const;
         bool operator!=(const Point2d& other) const;

         /// Calcuates an offset to this point using the given size argument as 
         /// the displacement.  Returns (x+size.Dx(),y+size.Dy()).  This point is
         /// not changed.
         Point2d operator+ (const Size2d& size) const;

         /// Calcuates an offset to this point using the given size argument as 
         /// the displacement.  Returns (x-size.Dx(),y-size.Dy()).  This point is
         /// not changed.
         Point2d operator- (const Size2d& size) const;

         /// Calculates the size between two points.  Returns x-p.X(), y-p.Y().
         /// This point is not changed.
         Size2d operator- (const Point2d& p) const;

         /// Returns the point (-x,-y). This point is not changed.
         Point2d operator- () const;

         /// Offsets this point by the given size argument.  This point is changed to
         /// (x+size.Dx(),y+size.Dy()).  Returns a reference to this point.
         Point2d& operator+= (const Size2d& size);

         /// Offsets this point by the given size argument.  This point is changed to
         /// (x-size.Dx(),y-size.Dy()).  Returns a reference to this point.
         Point2d& operator-= (const Size2d& size);

         /// Returns the distance between this point and the origin.
         Float64 Magnitude() const;

         /// Scales X and Y by c
         void Scale(Float64 c);

         /// Moves this point to a new position defined by x,y.
         void Move(Float64 x,Float64 y);

         /// Moves this point to a new position defined by newPosition.
         void Move(const Point2d& newPosition);

         /// Returns the distance between this point and point p.
         Float64 Distance(Float64 x, Float64 y) const;
         Float64 Distance(const Point2d& p) const;

         /// Offsets this point by the given delta arguments.  This point is changed
         /// to (x+dx,y+dy).  Returns a reference to this point.
         Point2d& Offset(Float64 dx,Float64 dy);

         /// Offsets this point by the given delta arguments.  This point is changed
         /// to (x+size.Dx(),y+size.Dy()).  Returns a reference to this point.
         Point2d& Offset(const Size2d& size);

         /// Calculates an offset to this point using the given displacement 
         /// arguments.  Returns the point (x+dx,y+dy).  This point is not
         /// changed.
         Point2d OffsetBy(Float64 dx,Float64 dy) const;

         /// Calculates an offset to this point using the given displacement 
         /// arguments.  Returns the point (x+size.Dx(),y+size.Dy()).
         /// This point is not changed.
         Point2d OffsetBy(const Size2d& size) const;

         /// Rotates this point about the given center point by the given angle. 
         /// This point is changed. Returns a reference to this point.
         Point2d& Rotate(Float64 x, Float64 y, Float64 angle);
         Point2d& Rotate(const Point2d& centerPoint, Float64 angle);

         /// Returns a point equal to this point rotated about the given center 
         /// point by the given angle. This point is not changed.
         Point2d RotateBy(Float64 x, Float64 y, Float64 angle) const;
         Point2d RotateBy(const Point2d& centerPoint, Float64 angle) const;

         /// Returns the x coordinate of the point.
         Float64 X() const;

         /// Returns the x coordinate of the point.
         Float64& X();

         /// Returns the y coordinate of the point.
         Float64 Y() const;

         /// Returns the y coordinate of the point.
         Float64& Y();

         /// Returns the coordinate of the point
         void GetLocation(Float64* x, Float64* y) const;
   
      #if defined _DEBUG
         /// Dumps the contents of the class to the given stream.
         void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         /// Self-Test function. Returns true if successful.
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST

      private:
         Float64 m_X{ 0.0 };
         Float64 m_Y{ 0.0 };
      };


      inline GEOMMODELFUNC Point2d operator*(const Point2d& p1, const Point2d& p2) { return Point2d(p1.X() * p2.X(), p1.Y() * p2.Y()); }
      inline GEOMMODELFUNC Point2d operator*(Float64 K, const Point2d& p) { return Point2d(p.X() * K, p.Y() * K); }
      inline GEOMMODELFUNC Point2d operator*(const Point2d& p, Float64 K) { return Point2d(p.X() * K, p.Y() * K); }
      inline GEOMMODELFUNC Point2d operator/(Float64 K, const Point2d& p) { return Point2d(p.X() / K, p.Y() / K); }
      inline GEOMMODELFUNC Point2d operator/(const Point2d& p, Float64 K) { return Point2d(p.X() / K, p.Y() / K); }
      inline GEOMMODELFUNC Point2d& operator*=(Point2d& p, Float64 K) { p.Scale(K); return p; }
      inline GEOMMODELFUNC Point2d& operator/=(Point2d& p, Float64 K) { p.Scale(1.0/K); return p; }

      /// Rect2d is a support class that encapsulates the properties of a rectangle
      /// with sides parallel to the x- and y-axes.
      class GEOMMODELCLASS Rect2d
      {
      public:
         /// Default constructor. Sets left, bottom, right, and top to zero.
         Rect2d();

         /// Creates a rectangle with the given dimensions
         Rect2d(Float64 left,  Float64 bottom, Float64 right, Float64 top);

         /// Creates a rectangle with the given bottom left and top right corners
         Rect2d(const Point2d& bottomLeft,const Point2d& topRight);

         /// Creates a rectangle with the given bottom left corner and the given size.
         Rect2d(const Point2d& bottomLeft,const Size2d& size);

         virtual ~Rect2d() {}

         Rect2d(const Rect2d&) = default;
         Rect2d& operator=(const Rect2d&) = default;

         bool operator==(const Rect2d& other) const;
         bool operator!=(const Rect2d& other) const;

         /// Returns the area of the rectangle
         Float64 Area() const;

         /// Repositions and resizes this rectangle to the given values.
         void Set(Float64 left,Float64 bottom,Float64 right,Float64 top);

         /// Repositions and resizes this rectangle using the given corner points.
         void Set(const Point2d& bottomLeft, const Point2d& topRight);

         /// Empties this rectangle by setting left, top, right, and bottom to 0.
         void SetEmpty();

         /// Sets the left, top, right, and bottom of the rectangle to 0.
         void SetNull();

         /// Re-positions and re-sizes the rectangle, given a new bottom left corner
         /// and a width and height.
         void SetWH(Float64 left,Float64 bottom,Float64 width,Float64 height);

         /// Re-positions and re-sizes the rectangle, given a new bottom left corner
         /// and a width and height.
         void SetWH(const Point2d& bottomLeft,const Size2d& size);

         /// Returns the top left corner of the rectangle.
         Point2d TopLeft() const;

         /// Returns the top right corner of the rectangle.
         Point2d TopRight() const;

         /// Returns the bottom left corner of the rectangle.
         Point2d BottomLeft() const;

         /// Returns the bottom right corner of the rectangle.
         Point2d BottomRight() const;

         /// Returns the center point of the rectangle.
         Point2d Center() const;

         /// Returns the center point on the top edge of the rectangle.
         Point2d TopCenter() const;

         /// Returns the center point on the bottom edge of the rectangle.
         Point2d BottomCenter() const;

         /// Returns the center point on the left edge of the rectangle.
         Point2d LeftCenter() const;

         /// Returns the center point on the right edge of the rectangle.
         Point2d RightCenter() const;

         /// Returns a Size2d object representing the width and height of this rectangle.
         Size2d Size() const;

         /// Returns bottom - top
         Float64 Height() const;

         /// Returns right - left.
         Float64 Width() const;

         /// Inflates a rectangle by the given delta arguments. The top left corner
         /// of the returned rectangle is (left - dx, top + dy), while its bottom
         /// right corner is (right + dx, bottom - dy).
         Rect2d& Inflate(Float64 dx,Float64 dy);

         /// Inflates a rectangle by the given delta arguments. The top left corner
         /// of the returned rectangle is (left - size.dx, top + size.dy), while its bottom
         /// right corner is (right + size.dx, bottom - size.dy).
         Rect2d& Inflate(const Size2d& size);

         /// Inflates a rectangle by the given delta arguments. The top left corner
         /// of the returned rectangle is (left - dx, top + dy), while its bottom
         /// right corner is (right + dx, bottom - dy). The calling rectagle is unchanged.
         Rect2d InflateBy(Float64 dx,Float64 dy) const;

         /// Inflates a rectangle by the given delta arguments. The top left corner
         /// of the returned rectangle is (left - size.dx, top + size.dy), while its bottom
         /// right corner is (right + size.dx, bottom - size.dy). The calling rectagle is unchanged.
         Rect2d InflateBy(const Size2d& size) const;

         /// Move the lower left corner of the rectangle to a new location and
         /// maintain the current dimension.
         Rect2d& MoveTo(Float64 bottom,Float64 left);

         /// Move the lower left point of the rectangle while maintaining the
         /// current dimension. The calling rectangle is unchanged.
         Rect2d MovedTo(Float64 bottom,Float64 left) const;

         /// Normalizes this rectangle by switching the left and right data member 
         /// values if left > right, and switching the top and bottom data member 
         /// values if top < bottom. Normalize returns the normalized rectangle. A 
         /// valid but nonnormal rectangle might have left > right or top < bottom 
         /// or both. In such cases, many manipulations (such as determining width 
         /// and height) become unnecessarily complicated. Normalizing a rectangle 
         /// means interchanging the corner point values so that left < right and 
         /// top > bottom. The physical properties of a rectangle are unchanged by 
         /// this process.
         Rect2d& Normalize();

         /// Returns a normalized rectangle with the top left corner at
         /// (Min(left, right), Max(top, bottom)) and the bottom right corner at 
         /// (Max(left, right), Min(top, bottom)). The calling rectangle object is 
         /// unchanged. A valid but nonnormal rectangle might have left > right or 
         /// top < bottom or both. In such cases, many manipulations (such as 
         /// determining width and height) become unnecessarily complicated. 
         /// Normalizing a rectangle means interchanging the corner point values so 
         /// that left < right and top > bottom. The physical properties of a rectangle
         /// are unchanged by this process.
         Rect2d Normalized() const;

         /// Changes this rectangle so its corners are offset by the given delta values. 
         /// The revised rectangle has a top left corner at (left + dx, top + dy) and a 
         /// right bottom corner at (right + dx, bottom + dy). The revised rectangle is returned.
         Rect2d& Offset(Float64 dx, Float64 dy);
         Rect2d& Offset(const Size2d& delta);

         /// Returns a rectangle with the corners are offset by the given delta values. 
         /// The rectangle has a top left corner at (left + dx, top + dy) and a 
         /// right bottom corner at (right + dx, bottom + dy).
         Rect2d OffsetBy(Float64 dx,Float64 dy) const;
         Rect2d OffsetBy(const Size2d& delta) const;

         /// Changes the dimensions of the Rect equal to the union of it and the other rectangle.
         /// The union is the smallest rectangle that contains both source rectangles. 
         /// Note: Both of the rectangles must be normalized or this function may fail. 
         /// You can call Normalize to normalize the rectangles before calling this function.
         /// \image html Rect2d/Union.jpg
         Rect2d& Union(const Rect2d& rOther);

         /// Makes a Rect2d with dimensions Rect equal to the union of it and the other rectangle.
         /// The union is the smallest rectangle that contains both source rectangles. 
         /// Note: Both of the rectangles must be normalized or this function may fail. 
         /// You can call Normalize to normalize the rectangles before calling this function.
         /// \image html Rect2d/Union.jpg
         Rect2d UnionBy(const Rect2d& rOther) const;

         /// Changes the dimenstions equal to the intersection of the two rectangles. 
         /// The intersection is the largest rectangle contained in both existing rectangles.
         /// Note: Both of the rectangles must be normalized or this function may fail. 
         /// You can call Normalize to normalize the rectangles before calling this function.
         /// \image html Rect2d/Intersect.jpg
         Rect2d& Intersection(const Rect2d& rOther);

         /// Makes a Rect2d with dimenstions equal to the intersection of the two rectangles. 
         /// The intersection is the largest rectangle contained in both existing rectangles.
         /// Note: Both of the rectangles must be normalized or this function may fail. 
         /// You can call Normalize to normalize the rectangles before calling this function.
         /// \image html Rect2d/Intersect.jpg
         Rect2d  IntersectionBy(const Rect2d& rOther) const;

         /// Changes the dimensions so that the rectangle bounds the point creating
         /// the smallest union of the existing rectangle and the point.
         /// Note: Both of the rectangles must be normalized or this function may fail. 
         /// You can call Normalize to normalize the rectangles before calling this function.
         Rect2d& BoundPoint(const Point2d& rPoint);
         Rect2d& BoundPoint(Float64 x, Float64 y);

         /// Makes a Rect2d with dimenstions so that the rectangle bounds the point creating
         /// the smallest union of the existing rectangle and the point.
         /// Note: Both of the rectangles must be normalized or this function may fail. 
         /// You can call Normalize to normalize the rectangles before calling this function.
         Rect2d BoundPointBy(const Point2d& rPoint) const;
         Rect2d BoundPointBy(Float64 x, Float64 y) const;

         /// Returns the x coordinate of the left edge
         Float64 Left() const;

         /// Returns the x coordinate of the left edge
         Float64& Left();

         /// Returns the x coordinate of the right edge
         Float64 Right() const;

         /// Returns the x coordinate of the right edge
         Float64& Right();

         /// Returns the y coordinate of the top edge
         Float64 Top() const;

         /// Returns the y coordinate of the top edge
         Float64& Top();

         /// Returns the y coordinate of the bottom edge
         Float64 Bottom() const;

         /// Returns the y coordinate of the bottom edge
         Float64& Bottom();

         /// Returns true if left >= right or bottom >= top; otherwise, returns false.
         bool IsNormalized() const;

         /// Returns true if left, right, top, and bottom are all zero or if the area is zero.
         bool IsNull() const;

         /// Returns true if the given point lies within this rectangle;
         /// otherwise, it returns false. If point is on the left
         /// vertical or top horizontal borders of the rectangle, Contains
         /// also returns true, but if point is on the right vertical
         /// or bottom horizontal borders, Contains returns false.
         bool Contains(const Point2d& point) const;

         /// Returns true if the other rectangle lies within this 
         /// rectangle. other can share edges with this. 
         /// Otherwise, it returns false.
         bool Contains(const Rect2d& other) const;

         /// Returns true if the other rectangle shares any interior
         /// points with this rectangle; otherwise, it returns false.
         bool Touches(const Rect2d& other) const;

         /// Constants defining the position of this rectangle relative to another
         enum class RelPosition
         {
            Contains, ///< The other rectangle is entirely contained within this rectangle
            Touches, ///< The other rectangle touches this rectangle
            Outside ///< The other rectangle is entirely outside of this rectangle
         };

         /// Check if other rectangle is Enclosed (possibly touching boundaries),
         /// Intersects (has union), or Entirely outside of this.
         RelPosition GetPosition(const Rect2d& other) const;


      #if defined _DEBUG
         /// Dumps the contents of the class to the given stream.
         void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         /// Self-Test function. Returns true if successful.
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST

      private:
         Float64 m_Left{ 0.0 };
         Float64 m_Bottom{ 0.0 };
         Float64 m_Right{ 0.0 };
         Float64 m_Top{ 0.0 };
      };
   } // namespace Geometry
} // namespace WBFL

#endif // INCLUDED_GEOMETRY_PRIMITIVES_H_
