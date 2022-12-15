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

#ifndef INCLUDED_GEOMETRY_PLANE3D_H_
#define INCLUDED_GEOMETRY_PLANE3D_H_
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace Geometry
   {
      class LineSegment3d;
      class Line2d;
      class Point3d;
      class Vector3d;

      /// Represents a plane in three dimension space.
      ///
      /// \image html Plane3d/Plane3d.jpg
      class GEOMMODELCLASS Plane3d
      {
      public:
         Plane3d();
         Plane3d(const Point3d& p, const Vector3d& n);
         Plane3d(Float64 a, Float64 b, Float64 c, Float64 d);
         Plane3d(Float64 altitude);
         Plane3d(const Line2d& line, const Point3d& point);
         Plane3d(const Point3d& p1, const Point3d& p2, const Point3d& p3);
         virtual ~Plane3d();

         Plane3d(const Plane3d&) = default;
         Plane3d& operator=(const Plane3d&) = default;

         /// Defines the plane with a point and a vector normal to the plane
         void Init(const Point3d& p, const Vector3d& n);

         /// Defines the plane with the coefficients of the scalar equation of a plane (Ax + By + Cz + D = 0)
         void Init(Float64 a, Float64 b, Float64 c, Float64 d);

         /// Gets the coefficients for the scalar equation of a plane
         void GetConstants(Float64* pA, Float64* pB, Float64* pC, Float64* pD) const;

         /// Defines a plane parallel to the XY plane at the specified altitude.
         void ThroughAltitude(Float64 altitude);

         /// Defines a plane that contains a line in the XY Plane and a point in space.
         void ThroughLine(const Line2d& line, const Point3d& point);

         /// Defines a plane that contains specified three points.
         void ThroughPoints(const Point3d& p1, const Point3d& p2, const Point3d& p3);

         /// Defines a plane parallel to the XY plane at the specified altitude. (Same as ThroughAltitude)
         void XY(Float64 altitude);

         /// Defines a plane parallel to the XZ plane at the specified altitude.
         void XZ(Float64 altitude);

         /// Defines a plane parallel to the YZ plane at the specified altitude.
         void YZ(Float64 altitude);

         Float64 GetX(Float64 y, Float64 z) const;
         Float64 GetY(Float64 x, Float64 z) const;
         Float64 GetZ(Float64 x, Float64 y) const;

         /// Returns the point of intersection of the specified line segment and the plane
         Point3d LineSegmentIntersect(const LineSegment3d& lineSegment) const;

         /// Returns the shortest distance from the specified point to the plane
         Float64 ShortestDistance(const Point3d& point) const;

         /// Returns the point on the plane nearest the specified point
         Point3d PointOnPlaneNearest(const Point3d& point) const;

         /// Returns the a vector normal to the plane. The vector is taken to be Ax,By,Cz and is not normalized
         Vector3d NormalVector() const;

#if defined _DEBUG
         /// Returns true if the class is in a valid state, otherwise returns false
         bool AssertValid() const;

         /// Dumps the contents of the class to the given stream.
         void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
         /// A self-test function - returns true if passed.
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         Float64 m_A{ 0.0 };
         Float64 m_B{ 0.0 };
         Float64 m_C{ 0.0 };
         Float64 m_D{ 0.0 };
      };
   }; // Geometry
}; // WBFL

#endif // INCLUDED_GEOMETRY_PLANE3D_H_
