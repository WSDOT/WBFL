///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2025  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMETRY_PRIMITIVES3D_H_
#define INCLUDED_GEOMETRY_PRIMITIVES3D_H_
#pragma once

#include <GeomModel/GeomModelExp.h>

namespace WBFL
{
   namespace Geometry
   {
      class GEOMMODELCLASS Point2d;
      class GEOMMODELCLASS Point3d;
      class GEOMMODELCLASS Size3d;

      /// Encapsulates the notion of a 3-dimensional quantity that usually 
      /// represents a displacement or the height, width, and depth of a rectangular
      /// prism.
      class GEOMMODELCLASS Size3d
      {
      public:
         Size3d();
         Size3d(Float64 dx, Float64 dy,Float64 dz);
         Size3d(const Point3d& point);
   
         virtual ~Size3d();

         Size3d(const Size3d&) = default;
         Size3d& operator=(const Size3d&) = default;

         /// Calculates an offset to this Size3d object using the given size argument
         /// as the displacement.  Returns (dx+size.Dx(), dy+size.Dy(), dz+size.Dz()).
         /// This object is unchanged.
         Size3d operator+(const Size3d& size) const;

         /// Scales the size object by c. Returns (Dx()*c, Dy()*c, Dz*c).
         Size3d operator*(Float64 c) const;

         /// Scales the size object by c. Returns (Dx()/c, Dy()/c, Dz()/c).
         Size3d operator/(Float64 c) const;

         /// Calculates an offset to this Size3d object using the given size argument
         /// as the displacement.  Returns (dx-size.Dx(), dy-size.Dy(), dz-size.Dz()).  
         /// This object is unchanged.
         Size3d operator-(const Size3d& size) const;

         /// Returns the Size3d object (-dx,-dy, -dz). This object is unchanged.
         Size3d operator-() const;

         /// Returns true if this Size3d object is equal to the rOther Size3d 
         /// object, otherwise returns false.
         bool operator==(const Size3d& rOther) const;

         /// Returns false if this Size3d object is equal to the rOther Size3d 
         /// object, otherwise returns true.
         bool operator!=(const Size3d& rOther) const;

         /// Offset this Size3d object by the given size argument.  This Size3d
         /// object is changed to (Dx+size.Dx(),Dy+size.Dy(),Dz+size.Dz()).
         /// Returns a reference to this object.
         Size3d& operator+= (const Size3d& rOther);

         /// Negatively offset this Size3d object by the given size argument.  
         /// This Size3d object is changed to (Dx+size.Dx(),Dy+size.Dy(),Dz+size.Dz()).
         /// Returns a reference to this object.
         Size3d& operator-= (const Size3d& rOther);

         /// Divides Dx, Dy, and Dz by c.
         Size3d& operator/= (Float64 c);

         /// Multiplies Dx, Dy, and Dz by c.
         Size3d& operator*= (Float64 c);

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

         /// Returns the size in the z direction.
         Float64 Dz() const;

         /// Returns the size in the z direction.
         Float64& Dz();

         void SetDimensions(Float64 dx, Float64 dy, Float64 dz);
         void SetDimensions(const Point3d& point);

         /// Returns the size dimensions
         std::tuple<Float64,Float64,Float64> GetDimensions() const;

      private:
         Float64 m_Dx{ 0.0 };
         Float64 m_Dy{ 0.0 };
         Float64 m_Dz{ 0.0 };
      };

      inline GEOMMODELFUNC Size3d operator/(Size3d& size, Float64 c)
      {   return size.operator/( c ); }
      inline GEOMMODELFUNC Size3d operator/(Float64 c,Size3d& size)
      {   return size.operator/( c ); }
      inline GEOMMODELFUNC Size3d operator*(Size3d& size, Float64 c)
      {   return size.operator*( c ); }
      inline GEOMMODELFUNC Size3d operator*(Float64 c,Size3d& size)
      {   return size.operator*( c ); }

      /// Encapsulates the notion of a 3-dimensional point that represents a
      /// position in a Cartesian coordinate system.
      class GEOMMODELCLASS Point3d
      {
      public:
         /// Default constructor.  Sets x, y, and z to zero.
         Point3d();

         /// Constructor. Sets coordinate to (x,y,z).
         Point3d(Float64 x,Float64 y,Float64 z);

         Point3d(const Point2d& pnt, Float64 z);

         virtual ~Point3d();

         Point3d(const Point3d&) = default;
         Point3d& operator=(const Point3d&) = default;

         bool operator==(const Point3d& other) const;

         bool operator!=(const Point3d& other) const;

         /// Calculates an offset to this point using the given size argument as 
         /// the displacement.  Returns (x+size.Dx(),y+size.Dy(),z+size.Dz()).
         /// This point is not changed.
         Point3d operator+ (const Size3d& size) const;

         /// Calculates an offset to this point using the given size argument as 
         /// the displacement.  Returns (x-size.Dx(),y-size.Dy(),z-size.Dz()).
         /// This point is not changed.
         Point3d operator- (const Size3d& size) const;

         /// Calculates the size between two points.  Returns x-p.X(), y-p.Y(), z-p.Z().
         /// This point is not changed.
         Size3d operator- (const Point3d& p) const;

         /// Returns the point (-x,-y,-z). This point is not changed.
         Point3d operator- () const;

         /// Offsets this point by the given size argument.  This point is changed to
         /// (x+size.Dx(),y+size.Dy(),z+size.Dz()).  Returns a reference to this point.
         Point3d& operator+= (const Size3d& size);

         /// Offsets this point by the given size argument.  This point is changed to
         /// (x-size.Dx(),y-size.Dy(),z-size.Dz()).  Returns a reference to this point.
         Point3d& operator-= (const Size3d& size);

         /// Returns the distance between this point and the origin.
         Float64 Magnitude() const;

         /// Scales X, Y and Z by c
         void Scale(Float64 c);

         /// Moves this point to a new position defined by x,y,z.
         void Move(Float64 x,Float64 y,Float64 z);

         /// Moves this point to a new position defined by pnt and z.
         void Move(const Point2d& pnt, Float64 z);

         /// Moves this point to a new position defined by newPosition.
         void Move(const Point3d& newPosition);

         /// Returns the distance between this point and point p.
         Float64 Distance(Float64 x, Float64 y, Float64 z) const;
         Float64 Distance(const Point3d& p) const;

         /// Offsets this point by the given delta arguments.  This point is changed
         /// to (x+dx,y+dy,z+dz).  Returns a reference to this point.
         Point3d& Offset(Float64 dx,Float64 dy,Float64 dz);

         /// Offsets this point by the given delta arguments.  This point is changed
         /// to (x+size.Dx(),y+size.Dy(),z+size.Dz()).  Returns a reference to this point.
         Point3d& Offset(const Size3d& size);

         /// Calculates an offset to this point using the given displacement 
         /// arguments.  Returns the point (x+dx,y+dy,z+dz).  This point is not
         /// changed.
         Point3d OffsetBy(Float64 dx,Float64 dy,Float64 dz) const;

         /// Calculates an offset to this point using the given displacement 
         /// arguments.  Returns the point (x+size.Dx(),y+size.Dy(),z+size.Dz()).
         /// This point is not changed.
         Point3d OffsetBy(const Size3d& size) const;

         /// Returns the x coordinate of the point.
         Float64 X() const;

         /// Returns the x coordinate of the point.
         Float64& X();

         /// Returns the y coordinate of the point.
         Float64 Y() const;

         /// Returns the y coordinate of the point.
         Float64& Y();

         /// Returns the z coordinate of the point.
         Float64 Z() const;

         /// Returns the z coordinate of the point.
         Float64& Z();

         /// Returns the location of this point
         std::tuple<Float64,Float64,Float64> GetLocation() const;

      private:
         Float64 m_X{ 0.0 };
         Float64 m_Y{ 0.0 };
         Float64 m_Z{ 0.0 };
      };

      inline GEOMMODELFUNC Point3d operator*(const Point3d& p1, const Point3d& p2) { return Point3d(p1.X() * p2.X(), p1.Y() * p2.Y(), p1.Z()*p2.Z()); }
      inline GEOMMODELFUNC Point3d operator*(Float64 K, const Point3d& p) { return Point3d(p.X() * K, p.Y() * K, p.Z() * K); }
      inline GEOMMODELFUNC Point3d operator*(const Point3d& p, Float64 K) { return Point3d(p.X() * K, p.Y() * K, p.Z() * K); }
      inline GEOMMODELFUNC Point3d operator/(Float64 K, const Point3d& p) { return Point3d(p.X() / K, p.Y() / K, p.Z() / K); }
      inline GEOMMODELFUNC Point3d operator/(const Point3d& p, Float64 K) { return Point3d(p.X() / K, p.Y() / K, p.Z() / K); }
      inline GEOMMODELFUNC Point3d& operator*=(Point3d& p, Float64 K) { p.Scale(K); return p; }
      inline GEOMMODELFUNC Point3d& operator/=(Point3d& p, Float64 K) { p.Scale(1.0 / K); return p; }   } // namespace Geometry
} // namespace WBFL

#endif // INCLUDED_GEOMETRY_PRIMITIVES3D_H_
