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

#ifndef INCLUDED_GEOMETRY_VECTOR3D_H_
#define INCLUDED_GEOMETRY_VECTOR3D_H_
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
class gpSize3d;
class gpPoint3d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gpVector3d

   A class to represent a vector in 3d space.


DESCRIPTION
   This class represents a 3d vector.

COPYRIGHT
   Copyright (c) 1999
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   Richard Brice : 04.21.1999 : Created file
*****************************************************************************/

class GEOMCLASS gpVector3d
{
public:

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   // Creates a zero vector.
   gpVector3d();

   //------------------------------------------------------------------------
   // Explicit constructor. Creates a vector that is in the direction from
   // point a to point b.
   gpVector3d(const gpPoint3d& a, const gpPoint3d& b);

   //------------------------------------------------------------------------
   // Explicit constructor.  Creates a vector using x, y, and z
   gpVector3d(Float64 x,Float64 y,Float64 z);

   //------------------------------------------------------------------------
   // Explicit constructor.  Creates a vector using a size's x, y, and z
   // components
   gpVector3d(const gpSize3d& size);

   //------------------------------------------------------------------------
   // Copy constructor
   gpVector3d(const gpVector3d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpVector3d();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gpVector3d& operator = (const gpVector3d& rOther);

   //------------------------------------------------------------------------
   // operator -
   // Reflection or negation. Returns the vector (-x,-y,-z).  This is not changed. 
   gpVector3d operator - () const;

   //------------------------------------------------------------------------
   // operator +=
   // Adds this vector by the given vector argument. This is changed to 
   // (x + vector.X(),y + vector.Y(), z + vector.Z()).
   gpVector3d& operator += (const gpVector3d& vector);

   //------------------------------------------------------------------------
   // operator -=
   // Subtracts the given vector from this. This is changed to 
   // (x - vector.X(), y - vector.Y(), z - vector.Z()).
   gpVector3d& operator -= (const gpVector3d& vector);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // AngleBetween
   // Returns the angle from this vector towards rOther.
   Float64 AngleBetween(const gpVector3d& rOther) const;

   //------------------------------------------------------------------------
   // ComponentAlong
   // Returns the component of this vector along rOther. Equivalent to this->Dot(rOther)/rother.Magnitude()
   Float64 Projection(const gpVector3d& rOther) const;

   //------------------------------------------------------------------------
   // Dot
   // Dot Product. Returns the dot product with this and rother.
   Float64 Dot(const gpVector3d& rOther) const;

   //------------------------------------------------------------------------
   // Computes the cross product of this with rOther.
   gpVector3d Cross(const gpVector3d& rOther) const;

   //------------------------------------------------------------------------
   // IsZero
   // Returns true if this vector is the zero vector
   bool IsZero() const;

   //------------------------------------------------------------------------
   // GetSize
   // Returns a gpSize2d object that has Dx and Dy equal to the x and y 
   // components of this vector.
   gpSize3d GetSize()const;

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
   // Reflection or Negation. Changes this to the vector (-x,-y, -z) and returns 
   // a reference to it. 
   gpVector3d& Reflect();

   //------------------------------------------------------------------------
   // Normalize
   // Normalizes (i.e., makes a unit vector) this vector and returns a reference
   // to it. Changes this vector.
   gpVector3d& Normalize();

   //------------------------------------------------------------------------
   // NormalizeBy
   // Normalizes (i.e., makes a unit vector) this vector and returns a copy 
   // of it. This vector is not changed.
   gpVector3d NormalizeBy() const;

   //------------------------------------------------------------------------
   // Scale
   // Scales the magnitude of this vector by factor and returns a reference 
   // to it. A negative value for scale will cause the vector to point in the 
   // opposite direction. Changes this vector.
   gpVector3d& Scale(Float64 factor);

   //------------------------------------------------------------------------
   // ScaleBy
   // Returns a vector with a magnitude equal to factor*magnitude along the 
   // direction of this. A negative value for magnitude will cause the vector
   // to point in the opposite direction. This vector is not changed.
   gpVector3d ScaleBy(Float64 factor) const;

   //------------------------------------------------------------------------
   // SetSize
   // Changes the x, y, and z components of this vector to size.Dx(), size.Dy(), size.Dz(). 
   // Changes this vector.
   gpVector3d& SetSize(const gpSize3d& size);

   //------------------------------------------------------------------------
   // Offset
   // Offsets this vector by the given delta arguments. This vector is changed
   // to (x+dx,y+dy,z+dz) or (x + size.Dx(), y + size.Dy(), z+size.Dz()).
   // Returns a reference to this vector.
   gpVector3d& Offset(Float64 dx,Float64 dy,Float64 dz);
   gpVector3d& Offset(const gpSize3d& size);

   //------------------------------------------------------------------------
   // OffsetBy
   // Calculates an offset to this vector using the given displacement 
   // arguments.  Returns the vector (x+dx,y+dy,z+dz) or 
   // (x+size.Dx(),y+size.Dy(),z+size.Dz()).
   // This vector is not changed.
   gpVector3d OffsetBy(Float64 dx, Float64 dy, Float64 dz) const;
   gpVector3d OffsetBy(const gpSize3d& size) const;

   //------------------------------------------------------------------------
   // SetMagnitude
   // Scales this vector to the given magnitude and returns a reference to it.
   // A negative value for magnitude will cause the vector to point in 
   // the opposite direction. Changes this vector.
   gpVector3d& SetMagnitude(Float64 magnitude);

   //------------------------------------------------------------------------
   // SetMagnitudeBy
   // Returns a vector of the given magnitude along the direction of
   // this. A negative value for magnitude will cause the vector to 
   // point in the opposite direction. This vector is not changed.
   gpVector3d SetMagnitudeBy(Float64 magnitude) const;

   //------------------------------------------------------------------------
   // Returns the x component of this vector.
   Float64 X() const;

   //------------------------------------------------------------------------
   // Returns the x component of this vector.
   Float64& X();

   //------------------------------------------------------------------------
   // Returns the y component of this vector.
   Float64 Y() const;

   //------------------------------------------------------------------------
   // Returns the y component of this vector.
   Float64& Y();

   //------------------------------------------------------------------------
   // Returns the z component of this vector.
   Float64 Z() const;

   //------------------------------------------------------------------------
   // Returns the z component of this vector.
   Float64& Z();
   
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
   void MakeCopy(const gpVector3d& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gpVector3d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_X, m_Y, m_Z;

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
   GEOMFUNC bool operator==(const gpVector3d& lhs, const gpVector3d& rhs);

   //------------------------------------------------------------------------
   // operator !=
   // Returns true if lhs is not equal to rhs,  otherwise returns false. 
   GEOMFUNC bool operator!=(const gpVector3d& lhs, const gpVector3d& rhs);

   //------------------------------------------------------------------------
   // operator +
   // Vector addition. Returns the vector lhs + rhs.
   GEOMFUNC gpVector3d operator+(const gpVector3d& lhs, const gpVector3d& rhs);

   //------------------------------------------------------------------------
   // operator -
   // Vector addition. Returns the vector lhs + Reflect(rhs).
   GEOMFUNC gpVector3d operator-(const gpVector3d& lhs, const gpVector3d& rhs);




#endif // INCLUDED_GEOMETRY_VECTOR3D_H_
