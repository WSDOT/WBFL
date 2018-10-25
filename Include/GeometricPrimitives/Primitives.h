///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// SYSTEM INCLUDES
//
#include <GeometricPrimitives\GeometryExp.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class GEOMCLASS gpPoint2d;
class GEOMCLASS gpSize2d;
class GEOMCLASS gpRect2d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gpSize2d

   Encapsulates the notion of a two-dimensional quantity that usually 
   represents a displacement or the height and width of a rectangle.


DESCRIPTION
   Encapsulates the notion of a two-dimensional quantity that usually 
   represents a displacement or the height and width of a rectangle.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.03.1997 : Created file
*****************************************************************************/

class GEOMCLASS gpSize2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor. Set dimensions to zero.
   gpSize2d();

   //------------------------------------------------------------------------
   // Constructor. Sets dimensions to dx and dy.
   gpSize2d(Float64 dx, Float64 dy);

   //------------------------------------------------------------------------
   // Constructor. Sets dimensions to point.Dx() and point.Dy().
   gpSize2d(const gpPoint2d& point);

   //------------------------------------------------------------------------
   // Copy constructor
   gpSize2d(const gpSize2d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpSize2d();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   gpSize2d& operator = (const gpSize2d& rOther);

   //------------------------------------------------------------------------
   // Calculates an offset to this gp2sSize object usint the give size argument
   // as the displacement.  Returns (dx+size.Dx(), dy+size.Dy()).  This object
   // is unchanged.
   gpSize2d operator + (const gpSize2d& size) const;

   //------------------------------------------------------------------------
   // Scales the size object by c. Returns (Dx()*c, Dy()*c).
   gpSize2d operator*(Float64 c) const;

   //------------------------------------------------------------------------
   // Scales the size object by c. Returns (Dx()/c, Dy()/c).
   gpSize2d operator/(Float64 c) const;

   //------------------------------------------------------------------------
   // Calculates an offset to this gp2sSize object usint the give size argument
   // as the displacement.  Returns (dx-size.Dx(), dy-size.Dy()).  This object
   // is unchanged.
   gpSize2d operator - (const gpSize2d& size) const;

   //------------------------------------------------------------------------
   // Returns the gp2sSize object (-dx,-dy). This object is unchanged.
   gpSize2d operator- () const;

   //------------------------------------------------------------------------
   // Returns true if this gpSize2d object is equal to the rOther gpSize2d 
   // object, otherwise returns false.
   bool operator==(const gpSize2d& rOther) const;

   //------------------------------------------------------------------------
   // Returns false if this gpSize2d object is equal to the rOther gpSize2d 
   // object, otherwise returns true.
   bool operator!=(const gpSize2d& rOther) const;

   //------------------------------------------------------------------------
   // Offset this gpSize2d object by the give size argument.  This gpSize2d
   // object is chaged to (Dx+size.Dx(),Dy+size.Dy()).  Returns a reference
   // to this object.
   gpSize2d& operator+= (const gpSize2d& rOther);

   //------------------------------------------------------------------------
   // Negatively offset this gpSize2d object by the give size argument.  
   // This gpSize2d object is chaged to (Dx+size.Dx(),Dy+size.Dy()).
   // Returns a reference to this object.
   gpSize2d& operator-= (const gpSize2d& rOther);

   //------------------------------------------------------------------------
   // Divides Dx and Dy by c.
   gpSize2d& operator/= (Float64 c);

   //------------------------------------------------------------------------
   // Multiplies Dx and Dy by c.
   gpSize2d& operator*= (Float64 c);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns the length of the diagonal of the rectangle represented by
   // this object.
   Float64 Magnitude() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the size in the x direction.
   Float64 Dx() const;

   //------------------------------------------------------------------------
   // Returns the size in the x direction.
   Float64& Dx();

   //------------------------------------------------------------------------
   // Returns the size in the y direction.
   Float64 Dy() const;

   //------------------------------------------------------------------------
   // Returns the size in the y direction.
   Float64& Dy();

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // TestMe
   // Self-Test function. Returns true if successful.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gpSize2d& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gpSize2d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Dx;
   Float64 m_Dy;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

inline GEOMFUNC gpSize2d operator/(gpSize2d& size, Float64 c)
{   return size.operator/( c ); }
inline GEOMFUNC gpSize2d operator/(Float64 c,gpSize2d& size)
{   return size.operator/( c ); }
inline GEOMFUNC gpSize2d operator*(gpSize2d& size, Float64 c)
{   return size.operator*( c ); }
inline GEOMFUNC gpSize2d operator*(Float64 c,gpSize2d& size)
{   return size.operator*( c ); }
GEOMFUNC std::ostream& operator<<(std::ostream& os,gpSize2d& size);

/*****************************************************************************
CLASS 
   gpPoint2d

   Encapsulates the notion of a two-dimensional point that represents a
   position in a Cartesian coordinate system.


DESCRIPTION
   Encapsulates the notion of a two-dimensional point that represents a
   position in a Cartesian coordinate system.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.03.1997 : Created file
*****************************************************************************/

class GEOMCLASS gpPoint2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Sets x and y to zero.
   gpPoint2d();

   //------------------------------------------------------------------------
   // Constructor. Sets coordinate to (x,y).
   gpPoint2d(Float64 x,Float64 y);

   //------------------------------------------------------------------------
   // Copy constructor
   gpPoint2d(const gpPoint2d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpPoint2d();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gpPoint2d& operator = (const gpPoint2d& rOther);

   //------------------------------------------------------------------------
   // Calcuates an offset to this point using the given size argument as 
   // the displacement.  Returns (x+size.Dx(),y+size.Dy()).  This point is
   // not changed.
   gpPoint2d operator+ (const gpSize2d& size) const;

   //------------------------------------------------------------------------
   // Calcuates an offset to this point using the given size argument as 
   // the displacement.  Returns (x-size.Dx(),y-size.Dy()).  This point is
   // not changed.
   gpPoint2d operator- (const gpSize2d& size) const;

   //------------------------------------------------------------------------
   // Calculates the size between two points.  Returns x-p.X(), y-p.Y().
   // This point is not changed.
   gpSize2d operator- (const gpPoint2d& p) const;

   //------------------------------------------------------------------------
   // Returns the point (-x,-y). This point is not changed.
   gpPoint2d operator- () const;

   //------------------------------------------------------------------------
   // Offsets this point by the given size argument.  This point is changed to
   // (x+size.Dx(),y+size.Dy()).  Returns a reference to this point.
   gpPoint2d& operator+= (const gpSize2d& size);

   //------------------------------------------------------------------------
   // Offsets this point by the given size argument.  This point is changed to
   // (x-size.Dx(),y-size.Dy()).  Returns a reference to this point.
   gpPoint2d& operator-= (const gpSize2d& size);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns the distance between this point and the origin.
   Float64 Magnitude() const;

   //------------------------------------------------------------------------
   // Moves this point to a new position defined by x,y.
   void Move(Float64 x,Float64 y);

   //------------------------------------------------------------------------
   // Moves this point to a new position defined by newPosition.
   void Move(const gpPoint2d& newPosition);

   //------------------------------------------------------------------------
   // Returns the distance between this point and point p.
   Float64 Distance(const gpPoint2d& p) const;

   //------------------------------------------------------------------------
   // Offsets this point by the given delta arguments.  This point is changed
   // to (x+dx,y+dy).  Returns a reference to this point.
   gpPoint2d& Offset(Float64 dx,Float64 dy);

   //------------------------------------------------------------------------
   // Offsets this point by the given delta arguments.  This point is changed
   // to (x+size.Dx(),y+size.Dy()).  Returns a reference to this point.
   gpPoint2d& Offset(const gpSize2d& size);

   //------------------------------------------------------------------------
   // Calculates an offset to this point using the given displacement 
   // arguments.  Returns the point (x+dx,y+dy).  This point is not
   // changed.
   gpPoint2d OffsetBy(Float64 dx,Float64 dy) const;

   //------------------------------------------------------------------------
   // Calculates an offset to this point using the given displacement 
   // arguments.  Returns the point (x+size.Dx(),y+size.Dy()).
   // This point is not changed.
   gpPoint2d OffsetBy(const gpSize2d& size) const;


   //------------------------------------------------------------------------
   // Rotates this point about the given center point by the given angle. 
   // This point is changed. Returns a reference to this point.
   gpPoint2d& Rotate(const gpPoint2d& centerPoint, Float64 angle);

   //------------------------------------------------------------------------
   // Returns a point equal to this point rotated about the given center 
   // point by the given angle. This point is not changed.
   gpPoint2d RotateBy(const gpPoint2d& centerPoint, Float64 angle) const;


   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the x coordinate of the point.
   Float64 X() const;

   //------------------------------------------------------------------------
   // Returns the x coordinate of the point.
   Float64& X();

   //------------------------------------------------------------------------
   // Returns the y coordinate of the point.
   Float64 Y() const;

   //------------------------------------------------------------------------
   // Returns the y coordinate of the point.
   Float64& Y();
   
   // GROUP: INQUIRY
   // GROUP: DEBUG

#if defined _DEBUG
   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // TestMe
   // Self-Test function. Returns true if successful.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST


protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gpPoint2d& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gpPoint2d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_X;
   Float64 m_Y;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

//------------------------------------------------------------------------
// Returns true if lhs is equal to rhs,  otherwise false.
GEOMFUNC bool operator==(const gpPoint2d& lhs, const gpPoint2d& rhs);

//------------------------------------------------------------------------
// Returns true if lhs is not equal to rhs,  otherwise false.
GEOMFUNC bool operator!=(const gpPoint2d& lhs, const gpPoint2d& rhs);

//------------------------------------------------------------------------
GEOMFUNC std::ostream& operator<<(std::ostream& os,const gpPoint2d& p);

/*****************************************************************************
CLASS 
   gpRect2d

   gpRect2d is a support class that encapsulates the properties of a rectangle
   with sides parallel to the x- and y-axes.

DESCRIPTION
   gpRect2d is a support class that encapsulates the properties of a rectangle
   with sides parallel to the x- and y-axes. Member functions and operators
   are provided for comparing, assigning, and manipulating sizes.

  The origin of the rectangle is at the bottom left corner

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/
class GEOMCLASS gpRect2d
{
public:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor. Sets left, bottom, right, and top to zero.
   gpRect2d();

   //------------------------------------------------------------------------
   // Creates a rectangle with the given dimensions
   gpRect2d(Float64 left,  Float64 bottom,
            Float64 right, Float64 top);

   //------------------------------------------------------------------------
   // Creates a rectangle with the given bottom left and top right corners
   gpRect2d(const gpPoint2d& bottomLeft,const gpPoint2d& topRight);

   //------------------------------------------------------------------------
   // Creates a rectangle with the given bottom left corner and the given
   // size.
   gpRect2d(const gpPoint2d& bottomLeft,const gpSize2d& size);

   //------------------------------------------------------------------------
   // Copy constructor
   gpRect2d(const gpRect2d& rOther);

   //------------------------------------------------------------------------
   virtual ~gpRect2d() {}

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   gpRect2d& operator= (const gpRect2d& r);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns the area of the rectangle
   Float64 Area() const;

   //------------------------------------------------------------------------
   // Repositions and resizes this rectangle to the given values.
   void Set(Float64 left,Float64 bottom,Float64 right,Float64 top);

   //------------------------------------------------------------------------
   // Repositions and resizes this rectangle using the given corner points.
   void Set(const gpPoint2d& bottomLeft, const gpPoint2d& topRight);

   //------------------------------------------------------------------------
   // Empties this rectangle by setting left, top, right, and bottom to 0.
   void SetEmpty();

   //------------------------------------------------------------------------
   // Sets the left, top, right, and bottom of the rectangle to 0.
   void SetNull();

   //------------------------------------------------------------------------
   // Re-positions and re-sizes the rectangle, given a new bottom left corner
   // and a width and height.
   void SetWH(Float64 left,Float64 bottom,Float64 width,Float64 height);

   //------------------------------------------------------------------------
   // Re-positions and re-sizes the rectangle, given a new bottom left corner
   // and a width and height.
   void SetWH(const gpPoint2d& bottomLeft,const gpSize2d& size);

   //------------------------------------------------------------------------
   // Returns the top left corner of the rectangle.
   gpPoint2d TopLeft() const;

   //------------------------------------------------------------------------
   // Returns the top right corner of the rectangle.
   gpPoint2d TopRight() const;

   //------------------------------------------------------------------------
   // Returns the bottom left corner of the rectangle.
   gpPoint2d BottomLeft() const;

   //------------------------------------------------------------------------
   // Returns the bottom right corner of the rectangle.
   gpPoint2d BottomRight() const;

   //------------------------------------------------------------------------
   // Returns the center point of the rectangle.
   gpPoint2d Center() const;

   //------------------------------------------------------------------------
   // Returns the center point on the top edge of the rectangle.
   gpPoint2d TopCenter() const;

   //------------------------------------------------------------------------
   // Returns the center point on the bottom edge of the rectangle.
   gpPoint2d BottomCenter() const;

   //------------------------------------------------------------------------
   // Returns the center point on the left edge of the rectangle.
   gpPoint2d LeftCenter() const;

   //------------------------------------------------------------------------
   // Returns the center point on the right edge of the rectangle.
   gpPoint2d RightCenter() const;

   //------------------------------------------------------------------------
   // Returns a <i>gpSize2d</i> object representing the width and height of
   // this rectangle.
   gpSize2d Size() const;


   //------------------------------------------------------------------------
   // Returns bottom - top
   Float64 Height() const;

   //------------------------------------------------------------------------
   // Returns right - left.
   Float64 Width() const;

   //------------------------------------------------------------------------
   // Inflates a rectangle by the given delta arguments. The top left corner
   // of the returned rectangle is (left - dx, top + dy), while its bottom
   // right corner is (right + dx, bottom - dy).
   gpRect2d& Inflate(Float64 dx,Float64 dy);

   //------------------------------------------------------------------------
   // Inflates a rectangle by the given delta arguments. The top left corner
   // of the returned rectangle is (left - size.dx, top + size.dy), while its bottom
   // right corner is (right + size.dx, bottom - size.dy).
   gpRect2d& Inflate(const gpSize2d& size);

   //------------------------------------------------------------------------
   // Inflates a rectangle by the given delta arguments. The top left corner
   // of the returned rectangle is (left - dx, top + dy), while its bottom
   // right corner is (right + dx, bottom - dy). The calling rectagle is unchanged.
   gpRect2d InflateBy(Float64 dx,Float64 dy) const;

   //------------------------------------------------------------------------
   // Inflates a rectangle by the given delta arguments. The top left corner
   // of the returned rectangle is (left - size.dx, top + size.dy), while its bottom
   // right corner is (right + size.dx, bottom - size.dy). The calling rectagle is unchanged.
   gpRect2d InflateBy(const gpSize2d& size) const;

   //------------------------------------------------------------------------
   // Move the lower left corner of the rectangle to a new location and
   // maintain the current dimension.
   gpRect2d& MoveTo(Float64 bottom,Float64 left);

   //------------------------------------------------------------------------
   // Move the lower left point of the rectangle while maintaining the
   // current dimension. The calling rectangle is unchanged.
   gpRect2d MovedTo(Float64 bottom,Float64 left) const;

   //------------------------------------------------------------------------
   // Normalizes this rectangle by switching the left and right data member 
   // values if left > right, and switching the top and bottom data member 
   // values if top < bottom. Normalize returns the normalized rectangle. A 
   // valid but nonnormal rectangle might have left > right or top < bottom 
   // or both. In such cases, many manipulations (such as determining width 
   // and height) become unnecessarily complicated. Normalizing a rectangle 
   // means interchanging the corner point values so that left < right and 
   // top > bottom. The physical properties of a rectangle are unchanged by 
   // this process.
   gpRect2d& Normalize();

   //------------------------------------------------------------------------
   // Returns a normalized rectangle with the top left corner at
   // (Min(left, right), Max(top, bottom)) and the bottom right corner at 
   // (Max(left, right), Min(top, bottom)). The calling rectangle object is 
   // unchanged. A valid but nonnormal rectangle might have left > right or 
   // top < bottom or both. In such cases, many manipulations (such as 
   // determining width and height) become unnecessarily complicated. 
   // Normalizing a rectangle means interchanging the corner point values so 
   // that left < right and top > bottom. The physical properties of a rectangle
   // are unchanged by this process.
   gpRect2d Normalized() const;

   //------------------------------------------------------------------------
   // Changes this rectangle so its corners are offset by the given delta values. 
   // The revised rectangle has a top left corner at (left + dx, top + dy) and a 
   // right bottom corner at (right + dx, bottom + dy). The revised rectangle is returned.
   gpRect2d& Offset(Float64 dx,Float64 dy);

   //------------------------------------------------------------------------
   // Returns a rectangle with the corners are offset by the given delta values. 
   // The rectangle has a top left corner at (left + dx, top + dy) and a 
   // right bottom corner at (right + dx, bottom + dy).
   gpRect2d OffsetBy(Float64 dx,Float64 dy) const;

   //------------------------------------------------------------------------
   // Changes the dimensions of the Rect equal to the union of it and the other rectangle.
   // The union is the smallest rectangle that contains both source rectangles. 
   // Note: Both of the rectangles must be normalized or this function may fail. 
   // You can call Normalize to normalize the rectangles before calling this function.
   gpRect2d& Union(const gpRect2d& rOther);

   //------------------------------------------------------------------------
   // Makes a gpRect2d with dimensions Rect equal to the union of it and the other rectangle.
   // The union is the smallest rectangle that contains both source rectangles. 
   // Note: Both of the rectangles must be normalized or this function may fail. 
   // You can call Normalize to normalize the rectangles before calling this function.
   gpRect2d UnionBy(const gpRect2d& rOther) const;

   //------------------------------------------------------------------------
   // Changes the dimenstions equal to the intersection of the two rectangles. 
   // The intersection is the largest rectangle contained in both existing rectangles.
   // Note: Both of the rectangles must be normalized or this function may fail. 
   // You can call Normalize to normalize the rectangles before calling this function.
   gpRect2d& Intersection(const gpRect2d& rOther);

   //------------------------------------------------------------------------
   // Makes a gpRect2d with dimenstions equal to the intersection of the two rectangles. 
   // The intersection is the largest rectangle contained in both existing rectangles.
   // Note: Both of the rectangles must be normalized or this function may fail. 
   // You can call Normalize to normalize the rectangles before calling this function.
   gpRect2d  IntersectionBy(const gpRect2d& rOther) const;

   //------------------------------------------------------------------------
   // Changes the dimensions so that the rectangle bounds the point creating
   // the smallest union of the existing rectangle and the point.
   // Note: Both of the rectangles must be normalized or this function may fail. 
   // You can call Normalize to normalize the rectangles before calling this function.
   gpRect2d& BoundPoint(const gpPoint2d& rPoint);

   //------------------------------------------------------------------------
   // Makes a gpRect2d with dimenstions so that the rectangle bounds the point creating
   // the smallest union of the existing rectangle and the point.
   // Note: Both of the rectangles must be normalized or this function may fail. 
   // You can call Normalize to normalize the rectangles before calling this function.
   gpRect2d  BoundPointBy(const gpPoint2d& rPoint) const;
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the x coordinate of the left edge
   Float64 Left() const;

   //------------------------------------------------------------------------
   // Returns the x coordinate of the left edge
   Float64& Left();

   //------------------------------------------------------------------------
   // Returns the x coordinate of the right edge
   Float64 Right() const;

   //------------------------------------------------------------------------
   // Returns the x coordinate of the right edge
   Float64& Right();

   //------------------------------------------------------------------------
   // Returns the y coordinate of the top edge
   Float64 Top() const;

   //------------------------------------------------------------------------
   // Returns the y coordinate of the top edge
   Float64& Top();

   //------------------------------------------------------------------------
   // Returns the y coordinate of the bottom edge
   Float64 Bottom() const;

   //------------------------------------------------------------------------
   // Returns the y coordinate of the bottom edge
   Float64& Bottom();

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Returns <b>true</b> if left >= right or bottom >= top; otherwise, returns <b>false</b>.
   bool IsNormalized() const;

   //------------------------------------------------------------------------
   // Returns <b>true</b> if left, right, top, and bottom are all zero.
   bool IsNull() const;

   //------------------------------------------------------------------------
   // Returns <b>true</b> if the givin <i>point</i> lies within this rectangle;
   // otherwise, it returns <b>false</b>. If <i>point</i> is on the left
   // vertical or top horizontal borders of the rectangle, <i>Contains</i>
   // also returns <b>true</b>, but if <i>point</i> is on the right vertical
   // or bottom horizontal borders, <i>Contains</i> returns <b>false</b>.
   bool Contains(const gpPoint2d& point) const;

   //------------------------------------------------------------------------
   // Returns <b>true</b> if the <i>other</i> rectangle lies within this 
   // rectangle. <i>other</i> can share edges with <i>this</i>. 
   // Otherwise, it returns <b>false</b>.
   bool Contains(const gpRect2d& other) const;

   //------------------------------------------------------------------------
   // Returns <b>true</b> if the <i>other</i> rectangle shares any interior
   // points with this rectangle; otherwise, it returns <b>false</b>.
   bool Touches(const gpRect2d& other) const;

#if defined _DEBUG
   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // TestMe
   // Self-Test function. Returns true if successful.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gpRect2d& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gpRect2d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Left;
   Float64 m_Bottom;
   Float64 m_Right;
   Float64 m_Top;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

//------------------------------------------------------------------------
// operator ==
// Returns true if lhs is equal to rhs,  otherwise returns false. 
GEOMFUNC bool operator==(const gpRect2d& lhs, const gpRect2d& rhs);

//------------------------------------------------------------------------
// operator !=
// Returns true if lhs is not equal to rhs,  otherwise returns false. 
GEOMFUNC bool operator!=(const gpRect2d& lhs, const gpRect2d& rhs);

//------------------------------------------------------------------------
GEOMFUNC std::ostream& operator<<(std::ostream& os,const gpRect2d& rect);

#endif // INCLUDED_GEOMETRY_PRIMITIVES_H_
