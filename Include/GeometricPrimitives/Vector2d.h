///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMETRY_VECTOR2D_H_
#define INCLUDED_GEOMETRY_VECTOR2D_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeometricPrimitives\GeometryExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gpSize2d;
class gpPoint2d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gpVector2d

   A class to represent a vector in 2d space.


DESCRIPTION
   This class represents a 2d vector. The Implementation was taken from 
   Chapter 1 of the original "Graphics Gems" book by Andrew Glassner.



COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 11.12.1997 : Created file
*****************************************************************************/

class GEOMCLASS gpVector2d
{
public:

   //------------------------------------------------------------------------
   // enum Side
   // Denotes either the right or left side of the vector as viewed while 
   // looking down the vector from the origin.
   enum Side {Left, Right};

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   // Creates a zero vector.
   gpVector2d();

   //------------------------------------------------------------------------
   // Explicit constructor. Creates a vector that is in the direction from
   // point a to point b.
   gpVector2d(const gpPoint2d& a, const gpPoint2d& b);

   //------------------------------------------------------------------------
   // gpVector2d
   // Explicit constructor.  Creates a vector of a given magnitude and 
   // direction angle. The direction angle is measured in radians 
   // counterclockwise from the x axis.
   gpVector2d(Float64 magnitude, Float64 direction);

   //------------------------------------------------------------------------
   // Explicit constructor.  Creates a vector using a size's x and y 
   // components
   gpVector2d(const gpSize2d& size);

   //------------------------------------------------------------------------
   // Copy constructor
   gpVector2d(const gpVector2d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpVector2d();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gpVector2d& operator = (const gpVector2d& rOther);

   //------------------------------------------------------------------------
   // operator -
   // Reflection or negation. Returns the vector (-x,-y).  This is not changed. 
   gpVector2d operator - () const;

   //------------------------------------------------------------------------
   // operator +=
   // Adds this vector by the given vector argument. This is changed to 
   // (x + vector.X(),y + vector.Y()).
   gpVector2d& operator += (const gpVector2d& vector);

   //------------------------------------------------------------------------
   // operator -=
   // Subtracts the given vector from this. This is changed to 
   // (x - vector.X(),y + vector.Y()).
   gpVector2d& operator -= (const gpVector2d& vector);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // AngleBetween
   // Returns the angle from this vector towards rOther.
   Float64 AngleBetween(const gpVector2d& rOther) const;

   //------------------------------------------------------------------------
   // ComponentAlong
   // Returns the component of this vector along rOther. Equivalent to this->Dot(rOther)/rother.Magnitude()
   Float64 Projection(const gpVector2d& rOther) const;

   //------------------------------------------------------------------------
   // Dot
   // Dot Product. Returns the dot product with this and rother.
   Float64 Dot(const gpVector2d& rOther) const;

   //------------------------------------------------------------------------
   // IsZero
   // Returns true if this vector is the zero vector
   bool IsZero() const;

   //------------------------------------------------------------------------
   // Get direction (slope angle) in radians. The angle is measured 
   // counterclockwise from the positive X direction.
   Float64 GetDirection() const;

   //------------------------------------------------------------------------
   // GetSize
   // Returns a gpSize2d object that has Dx and Dy equal to the x and y 
   // components of this vector.
   gpSize2d GetSize()const;

   //------------------------------------------------------------------------
   // Magnitude
   // Returns the magnitude of the vector.
   Float64 GetMagnitude() const;

   //------------------------------------------------------------------------
   // RelMagnitude
   // Returns the magnitude of the vector squared. This method is faster than 
   // Magnitude() when only comparing lengths.
   Float64 GetRelMagnitude() const;

   //------------------------------------------------------------------------
   // Reflect
   // Reflection or Negation. Changes this to the vector (-x,-y) and returns 
   // a reference to it. 
   gpVector2d& Reflect();

   //------------------------------------------------------------------------
   // Normalize
   // Normalizes (i.e., makes a unit vector) this vector and returns a reference
   // to it. Changes this vector.
   gpVector2d& Normalize();

   //------------------------------------------------------------------------
   // NormalizeBy
   // Normalizes (i.e., makes a unit vector) this vector and returns a copy 
   // of it. This vector is not changed.
   gpVector2d NormalizeBy() const;

   //------------------------------------------------------------------------
   // Normal
   // Returns a vector perpendicular to this, rotated 90 degrees counterclockwise.
   // The new vector is of the same length This vector is not changed.
   gpVector2d Normal(Side side=Left) const;

   //------------------------------------------------------------------------
   // Scale
   // Scales the magnitude of this vector by factor and returns a reference 
   // to it. A negative value for scale will cause the vector to point in the 
   // opposite direction. Changes this vector.
   gpVector2d& Scale(Float64 factor);

   //------------------------------------------------------------------------
   // ScaleBy
   // Returns a vector with a magnitude equal to factor*magnitude along the 
   // direction of this. A negative value for magnitude will cause the vector
   // to point in the opposite direction. This vector is not changed.
   gpVector2d ScaleBy(Float64 factor) const;

   //------------------------------------------------------------------------
   // SetDirection
   // Changes the direction angle of this vector to direction and returns a 
   // reference to it. The length of this vector is not changed. Changes this vector.
   gpVector2d& SetDirection(Float64 direction);

   //------------------------------------------------------------------------
   // SetSize
   // Changes the x and y components of this vector to size.Dx(), size.Dy(). 
   // Changes this vector.
   gpVector2d& SetSize(const gpSize2d& size);

   //------------------------------------------------------------------------
   // SetSize
   // Changes the x and y components of this vector to X, Y
   // Changes this vector.
   gpVector2d& SetSize(Float64 x,Float64 y);

   //------------------------------------------------------------------------
   // Offset
   // Offsets this vector by the given delta arguments. This vector is changed
   // to (x+dx,y+dy) or (x + size.Dx(), y + size.Dy()).  Returns a reference 
   // to this vector.
   gpVector2d& Offset(Float64 dx,Float64 dy);
   gpVector2d& Offset(const gpSize2d& size);

   //------------------------------------------------------------------------
   // OffsetBy
   // Calculates an offset to this vector using the given displacement 
   // arguments.  Returns the vector (x+dx,y+dy) or (x+size.Dx(),y+size.Dy()).
   // This vector is not changed.
   gpVector2d OffsetBy(Float64 dx, Float64 dy) const;
   gpVector2d OffsetBy(const gpSize2d& size) const;

   //------------------------------------------------------------------------
   // SetMagnitude
   // Scales this vector to the given magnitude and returns a reference to it.
   // A negative value for lengthmagnitude will cause the vector to point in 
   // the opposite direction. Changes this vector.
   gpVector2d& SetMagnitude(Float64 magnitude);

   //------------------------------------------------------------------------
   // SetMagnitudeBy
   // Returns a vector of the given magnitude along the direction of
   // this. A negative value for lengthmagnitude will cause the vector to 
   // point in the opposite direction. This vector is not changed.
   gpVector2d SetMagnitudeBy(Float64 magnitude) const;

   //------------------------------------------------------------------------
   // Rotate
   // Rotates this vector by the given angle (in radians). The length of this 
   // vector is not changed. This vector is changed. Returns a reference to 
   // this vector.
   gpVector2d& Rotate(Float64 angle);

   //------------------------------------------------------------------------
   // RotateBy
   // Returns a vector equal to this vector rotated by the given angle 
   // (radians). The length of the new vector is equal to the length of 
   // this vector. This vector is not changed.
   gpVector2d RotateBy(Float64 angle) const;

   //------------------------------------------------------------------------
   // X
   // Returns the x component of this vector.
   Float64 X() const;

   //------------------------------------------------------------------------
   // X
   // Returns the x component of this vector.
   Float64& X();

   //------------------------------------------------------------------------
   // Y
   // Returns the y component of this vector.
   Float64 Y() const;

   //------------------------------------------------------------------------
   // Y
   // Returns the y component of this vector.
   Float64& Y();
   
   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;

#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // A self-test function - returns true if passed.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gpVector2d& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gpVector2d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_X, m_Y;
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
   GEOMFUNC bool operator==(const gpVector2d& lhs, const gpVector2d& rhs);

   //------------------------------------------------------------------------
   // operator !=
   // Returns true if lhs is not equal to rhs,  otherwise returns false. 
   GEOMFUNC bool operator!=(const gpVector2d& lhs, const gpVector2d& rhs);

   //------------------------------------------------------------------------
   // operator +
   // Vector addition. Returns the vector lhs + rhs.
   GEOMFUNC gpVector2d operator+(const gpVector2d& lhs, const gpVector2d& rhs);

   //------------------------------------------------------------------------
   // operator -
   // Vector addition. Returns the vector lhs + Reflect(rhs).
   GEOMFUNC gpVector2d operator-(const gpVector2d& lhs, const gpVector2d& rhs);




#endif // INCLUDED_GEOMETRY_VECTOR2D_H_
