///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2024  Washington State Department of Transportation
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

namespace WBFL
{
   namespace Geometry
   {
      class Size2d;
      class Point2d;
      /// Represents a vector in a two dimensional Cartesian coordinate system. 
      ///
      /// A vector is a quantity that has magnitude and direction. The default vector is {1,0}.
      /// \image html Vector2d/Vector.jpg
      class GEOMMODELCLASS Vector2d
      {
      public:

         /// Denotes either the right or left side of the vector as viewed while 
         /// looking down the vector from the origin.
         enum class Side {Left, Right};

         /// Creates a zero vector.
         Vector2d();

         /// Explicit constructor. Creates a vector that is in the direction from point a to point b.
         Vector2d(const Point2d& a, const Point2d& b);

         /// Explicit constructor.  Creates a vector of a given magnitude and 
         /// direction angle. The direction angle is measured in radians 
         /// counterclockwise from the x axis.
         Vector2d(Float64 magnitude, Float64 direction);

         /// Explicit constructor.  Creates a vector using a size's x and y components
         Vector2d(const Size2d& size);

         virtual ~Vector2d();

         Vector2d(const Vector2d&) = default;
         Vector2d& operator=(const Vector2d&) = default;

         bool operator==(const Vector2d& other) const;
         bool operator!=(const Vector2d& other) const;

         /// Reflection or negation. Returns the vector (-x,-y).  This is not changed. 
         Vector2d operator - () const;

         /// Adds this vector by the given vector argument. This is changed to 
         /// (x + vector.X(),y + vector.Y()).
         Vector2d& operator += (const Vector2d& vector);

         /// Subtracts the given vector from this. This is changed to 
         /// (x - vector.X(),y + vector.Y()).
         Vector2d& operator -= (const Vector2d& vector);

         /// Returns the angle from this vector towards rOther.
      /// The angle between the vectors is computed as \f$ \alpha = \cos{^{-1}} \left(\frac{x_1 x_2 + y_1 y_2}{\mid \overrightarrow{V_1} \mid \mid \overrightarrow{V_2} \mid}\right) \f$.
      /// \image html Vector2d/AngleBetween.jpg
         Float64 AngleBetween(const Vector2d& rOther) const;

         /// Returns the component of this vector along rOther. Equivalent to this->Dot(rOther)/rother.Magnitude()
      /// \image html Vector2d/Projection.jpg
         Float64 Projection(const Vector2d& rOther) const;

         /// Dot Product. Returns the dot product with this and rother.
      /// The dot product is computed as \f$dot = x_1 x_2 + y_1 y_2\f$
         Float64 Dot(const Vector2d& rOther) const;

         /// Returns true if this vector is the zero vector
         bool IsZero() const;

         /// Get direction (slope angle) in radians. The angle is measured 
         /// counterclockwise from the positive X direction.
         Float64 GetDirection() const;

         /// Returns a Size2d object that has Dx and Dy equal to the x and y 
         /// components of this vector.
         Size2d GetSize()const;

         /// Returns the magnitude of the vector.
         Float64 GetMagnitude() const;

         /// Returns the magnitude of the vector squared. This method is faster than 
         /// Magnitude() when only comparing lengths.
         Float64 GetRelMagnitude() const;

         /// Reflection or Negation. Changes this to the vector (-x,-y) and returns 
         /// a reference to it. 
      /// \image html Vector2d/Reflect.jpg
         Vector2d& Reflect();

         /// Normalizes (i.e., makes a unit vector) this vector and returns a reference
         /// to it. Changes this vector.
         Vector2d& Normalize();

         /// Normalizes (i.e., makes a unit vector) this vector and returns a copy 
         /// of it. This vector is not changed.
         Vector2d NormalizeBy() const;

         /// Returns a vector perpendicular to this, rotated 90 degrees counterclockwise.
         /// The new vector is of the same length This vector is not changed.
         /// \image html Vector2d/Normal.jpg
         Vector2d Normal(Side side=Side::Left) const;

         /// Scales the magnitude of this vector by factor and returns a reference 
         /// to it. A negative value for scale will cause the vector to point in the 
         /// opposite direction. Changes this vector.
      /// \image html Vector2d/Scale.jpg
         Vector2d& Scale(Float64 factor);

         /// Returns a vector with a magnitude equal to factor*magnitude along the 
         /// direction of this. A negative value for magnitude will cause the vector
         /// to point in the opposite direction. This vector is not changed.
      /// \image html Vector2d/Scale.jpg
         Vector2d ScaleBy(Float64 factor) const;

         Vector2d& Increment(const Vector2d& other);
         Vector2d IncrementBy(const Vector2d& other) const;
         Vector2d& Decrement(const Vector2d& other);
         Vector2d DecrementBy(const Vector2d& other) const;

         /// Changes the direction angle of this vector to direction and returns a 
         /// reference to it. The length of this vector is not changed. Changes this vector.
         Vector2d& SetDirection(Float64 direction);
         Vector2d SetDirectionBy(Float64 direction) const;

         /// Changes the x and y components of this vector to size.Dx(), size.Dy(). 
         /// Changes this vector.
         Vector2d& SetSize(const Size2d& size);

         /// Changes the x and y components of this vector to X, Y
         /// Changes this vector.
         Vector2d& SetSize(Float64 x,Float64 y);

         /// Offsets this vector by the given delta arguments. This vector is changed
         /// to (x+dx,y+dy).  Returns a reference to this vector.
      /// \image html Vector2d/Offset.jpg
         Vector2d& Offset(Float64 dx,Float64 dy);

         /// Offsets this vector by the given delta arguments. This vector is changed
         /// to (x + size.Dx(), y + size.Dy()).  Returns a reference to this vector.
      /// \image html Vector2d/Offset.jpg
         Vector2d& Offset(const Size2d& size);

         /// Calculates an offset to this vector using the given displacement 
         /// arguments.  Returns the vector (x+dx,y+dy). This vector is not changed.
      /// \image html Vector2d/Offset.jpg
         Vector2d OffsetBy(Float64 dx, Float64 dy) const;

         /// Calculates an offset to this vector using the given displacement 
         /// arguments.  Returns the vector (x+size.Dx(),y+size.Dy()). This vector is not changed.
      /// \image html Vector2d/Offset.jpg
         Vector2d OffsetBy(const Size2d& size) const;

         /// Scales this vector to the given magnitude and returns a reference to it.
         /// A negative value for magnitude will cause the vector to point in 
         /// the opposite direction. Changes this vector.
         Vector2d& SetMagnitude(Float64 magnitude);

         /// Returns a vector of the given magnitude along the direction of
         /// this. A negative value for magnitude will cause the vector to 
         /// point in the opposite direction. This vector is not changed.
         Vector2d SetMagnitudeBy(Float64 magnitude) const;

         /// Rotates this vector by the given angle (in radians). The length of this 
         /// vector is not changed. This vector is changed. Returns a reference to 
         /// this vector.
      /// \image html Vector2d/Rotate.jpg
         Vector2d& Rotate(Float64 angle);

         /// Returns a vector equal to this vector rotated by the given angle 
         /// (radians). The length of the new vector is equal to the length of 
         /// this vector. This vector is not changed.
      /// \image html Vector2d/Rotate.jpg
         Vector2d RotateBy(Float64 angle) const;

         /// Returns the x component of this vector.
         Float64 X() const;

         /// Returns the x component of this vector.
         Float64& X();

         /// Returns the y component of this vector.
         Float64 Y() const;

         /// Returns the y component of this vector.
         Float64& Y();

         /// Returns the dimensions of this vector
         std::pair<Float64,Float64> GetDimensions() const;

      private:
         Float64 m_X{ 1.0 };
         Float64 m_Y{ 0.0 };
      };


      /// Vector addition. Returns the vector lhs + rhs.
      GEOMMODELFUNC Vector2d operator+(const Vector2d& lhs, const Vector2d& rhs);

      /// Vector addition. Returns the vector lhs + Reflect(rhs).
      GEOMMODELFUNC Vector2d operator-(const Vector2d& lhs, const Vector2d& rhs);

   }
}
