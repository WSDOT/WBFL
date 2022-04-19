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

#ifndef INCLUDED_GEOMETRY_VECTOR3D_H_
#define INCLUDED_GEOMETRY_VECTOR3D_H_
#pragma once


#include <GeomModel/GeomModelExp.h>

namespace WBFL
{
   namespace Geometry
   {
      class Size3d;
      class Point3d;

      /// Represents a vector in a three dimensional cartesian coordinate system. 
      ///
      /// A vector is a quantity that has magnitude and direction. The default vector is {1,0,0}.
      /// \image html Vector3d/Vector3d.jpg	
      class GEOMMODELCLASS Vector3d
      {
      public:
         Vector3d();

         /// Explicit constructor. Creates a vector that is in the direction from point a to point b.
         Vector3d(const Point3d& a, const Point3d& b);

         /// Explicit constructor.  Creates a vector using x, y, and z
         Vector3d(Float64 x,Float64 y,Float64 z);

         /// Explicit constructor.  Creates a vector using a size's x, y, and z components
         Vector3d(const Size3d& size);

         virtual ~Vector3d();

         Vector3d(const Vector3d&) = default;
         Vector3d& operator=(const Vector3d&) = default;

         bool operator==(const Vector3d& other) const;
         bool operator!=(const Vector3d& other) const;

         /// Reflection or negation. Returns the vector (-x,-y,-z).  This is not changed. 
         Vector3d operator - () const;

         /// Adds this vector by the given vector argument. This is changed to 
         /// (x + vector.X(),y + vector.Y(), z + vector.Z()).
         Vector3d& operator += (const Vector3d& vector);

         /// Subtracts the given vector from this. This is changed to 
         /// (x - vector.X(), y - vector.Y(), z - vector.Z()).
         Vector3d& operator -= (const Vector3d& vector);

         /// Computes the angle between two vectors. 
         /// The angle between the vectors is computed as \f$ \alpha = \cos{^{-1}} \left(\frac{x_1 x_2 + y_1 y_2 + z_1 z_2}{\mid\overrightarrow{V_1} \mid \mid \overrightarrow{V_2} \mid}\right) \f$.
         /// \image html Vector3d/AngleBetween.jpg
         Float64 AngleBetween(const Vector3d& rOther) const;

         /// Returns the component of this vector along rOther. Equivalent to this->Dot(rOther)/rother.Magnitude()
      /// In the figure below, the magnitude of the red vector is equal the project of the black vector (this vector) onto the green vector.
      /// \image html Vector3d/Projection.jpg
         Float64 Projection(const Vector3d& rOther) const;

         /// Dot Product. Returns the dot product with this and rother.
      /// The dot product is computed as \f$dot = x_1 x_2 + y_1 y_2 + z_1 z_2\f$
         Float64 Dot(const Vector3d& rOther) const;

         /// Computes the cross product of this with rOther.
      /// The cross product is computed as \f$ \overrightarrow{V_1} \times \overrightarrow{V_2} = (y_1 z_2 - z_1 y_2)\overrightarrow{i} + (z_1 x_2 - x_1 z_2)\overrightarrow{j} + (x_1 y_2 - y_1 x_2)\overrightarrow{k} \f$
         Vector3d Cross(const Vector3d& rOther) const;

         /// Returns true if this vector is the zero vector
         bool IsZero() const;

         /// Returns a Size2d object that has Dx and Dy equal to the x and y components of this vector.
         Size3d GetSize()const;

         /// Returns the magnitude of the vector.
         Float64 GetMagnitude() const;

         /// Returns the magnitude of the vector squared. This method is faster than 
         /// Magnitude() when only comparing lengths.
         Float64 GetRelMagnitude() const;

         /// Reflection or Negation. Changes this to the vector (-x,-y, -z) and returns a reference to it. 
      /// \image html Vector3d/Reflect.jpg
         Vector3d& Reflect();

         /// Normalizes (i.e., makes a unit vector) this vector and returns a reference to it. Changes this vector.
         Vector3d& Normalize();

         /// Normalizes (i.e., makes a unit vector) this vector and returns a copy of it. This vector is not changed.
         Vector3d NormalizeBy() const;

         /// Scales the magnitude of this vector by factor and returns a reference 
         /// to it. A negative value for scale will cause the vector to point in the 
         /// opposite direction. Changes this vector.
         /// \image html Vector3d/Scale.jpg
         Vector3d& Scale(Float64 factor);

         /// Returns a vector with a magnitude equal to factor*magnitude along the 
         /// direction of this. A negative value for magnitude will cause the vector
         /// to point in the opposite direction. This vector is not changed.
         /// \image html Vector3d/Scale.jpg
         Vector3d ScaleBy(Float64 factor) const;

         /// Changes the x, y, and z components of this vector to size.Dx(), size.Dy(), size.Dz(). 
         /// Changes this vector.
         Vector3d& SetSize(Float64 dx, Float64 dy, Float64 dz);
         Vector3d& SetSize(const Size3d& size);

         /// Offsets this vector by the given delta arguments. This vector is changed
         /// to (x+dx,y+dy,z+dz). Returns a reference to this vector.
         Vector3d& Offset(Float64 dx,Float64 dy,Float64 dz);

         /// Offsets this vector by the given delta arguments. This vector is changed
         /// to (x + size.Dx(), y + size.Dy(), z+size.Dz()). Returns a reference to this vector.
         Vector3d& Offset(const Size3d& size);

         /// Calculates an offset to this vector using the given displacement 
         /// arguments.  Returns the vector (x+dx,y+dy,z+dz).
         /// This vector is not changed.
         Vector3d OffsetBy(Float64 dx, Float64 dy, Float64 dz) const;

         /// Calculates an offset to this vector using the given displacement 
         /// arguments.  Returns the vector (x+size.Dx(),y+size.Dy(),z+size.Dz()).
         /// This vector is not changed.
         Vector3d OffsetBy(const Size3d& size) const;

         /// Scales this vector to the given magnitude and returns a reference to it.
         /// A negative value for magnitude will cause the vector to point in 
         /// the opposite direction. Changes this vector.
         Vector3d& SetMagnitude(Float64 magnitude);

         /// Returns a vector of the given magnitude along the direction of
         /// this. A negative value for magnitude will cause the vector to 
         /// point in the opposite direction. This vector is not changed.
         Vector3d SetMagnitudeBy(Float64 magnitude) const;

         /// Increments the dimensions of this vector by adding the dimensions of v
         Vector3d& Increment(const Vector3d& other);

         /// Creates a new vector by adding the dimensions v with this vector
         Vector3d IncrementBy(const Vector3d& other) const;

         /// Decrements the dimensions of this vector by subtracting the dimensions of v
         Vector3d& Decrement(const Vector3d& other);

         /// Creates a new vector by subtracting the dimensions v from this vector
         Vector3d DecrementBy(const Vector3d& other) const;

         /// Returns the x component of this vector.
         Float64 X() const;

         /// Returns the x component of this vector.
         Float64& X();

         /// Returns the y component of this vector.
         Float64 Y() const;

         /// Returns the y component of this vector.
         Float64& Y();

         /// Returns the z component of this vector.
         Float64 Z() const;

         /// Returns the z component of this vector.
         Float64& Z();

         /// Returns the dimensions of this vector.
         void GetDimensions(Float64* x, Float64* y, Float64* z) const;

      #if defined _DEBUG
         /// Returns true if the class is in a valid state, otherwise returns false
         bool AssertValid() const;

         /// Dumps the contents of the class to the given stream.
         void Dump(dbgDumpContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         /// A self-test function - returns true if passed.
         static bool TestMe(dbgLog& rlog);
      #endif // _UNITTEST

      private:
         Float64 m_X{ 0.0 };
         Float64 m_Y{ 0.0 };
         Float64 m_Z{ 0.0 };
      };

      /// Vector addition. Returns the vector lhs + rhs.
      GEOMMODELFUNC Vector3d operator+(const Vector3d& lhs, const Vector3d& rhs);

      /// Vector addition. Returns the vector lhs + Reflect(rhs).
      GEOMMODELFUNC Vector3d operator-(const Vector3d& lhs, const Vector3d& rhs);
   }; // Geometry
}; // WBFL


#endif // INCLUDED_GEOMETRY_VECTOR3D_H_
