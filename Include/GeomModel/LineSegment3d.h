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

#pragma once

#include <vector>
#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Primitives3d.h>

namespace WBFL
{
   namespace Geometry
   {
      /// Interface defining a line segment in a 3D Cartesian coordinate system.
      ///
      /// A line segment is a line with finite length between start and end points
      /// \image html LineSegment3d/LineSegment3d.png
      class GEOMMODELCLASS LineSegment3d
      {
      public:
         LineSegment3d() = default;

         /// Explicit constructor.  Creates a line segment from start to end.
         LineSegment3d(const Point3d& start, const Point3d& end);

         /// Explicit constructor.  Creates a line segment from start to end.
         LineSegment3d(Float64 x1,Float64 y1,Float64 z1, Float64 x2,Float64 y2,Float64 z2);

         /// Explicit constructor.  Creates a line segment that starts at start 
         /// and ends at (start.X()+relEnd.Dx(),start.Y()+relEnd.Dy(),start.Z()+relEnd.Dz()).
         LineSegment3d(const Point3d& start, const Size3d& relEnd);

         LineSegment3d(const LineSegment3d& other) = default;
         LineSegment3d& operator=(const LineSegment3d& other) = default;
         virtual ~LineSegment3d() = default;

         bool operator==(const LineSegment3d& other) const;
         bool operator!=(const LineSegment3d& other) const;

         void ThroughPoints(const Point3d& start, const Point3d& end);

         /// Returns the length of the line segment.
         Float64 Length() const;

         /// Sets the start point of the line segment.
         void SetStartPoint(const Point3d& startPoint);

         /// Returns the start point of the line segment.
         const Point3d& GetStartPoint() const;

         /// Sets the end point of the line segment.
         void SetEndPoint(const Point3d& endPoint);

         /// Returns the end point of the line segment.
         const Point3d& GetEndPoint() const;

         /// Returns the mid point of the line segment.
         Point3d GetMidPoint() const;

         /// Offsets this line segment by the given delta arguments. This line is 
         /// changed by translating its control points by the given distance.  
         /// Returns a reference to this line segment.
         LineSegment3d& Offset(Float64 dx,Float64 dy,Float64 dz);
         LineSegment3d& Offset(const Size3d& size);

         /// Returns a segment line which is offset to this line segment by the given 
         /// displacement arguments. This is not changed.
         LineSegment3d OffsetBy(Float64 dx, Float64 dy,Float64 dz) const;
         LineSegment3d OffsetBy(const Size3d& size) const;
   
         /// Divides the line segment into nSpaces equally divided spaces.  Returns
         /// a vector containing the coordinate of each point, including the line segment end points.
         std::vector<Point3d> Divide(Uint16 nSpaces) const;

         Float64 DistanceToPoint(const Point3d& p) const;

      private:
         Point3d m_Start;
         Point3d m_End;
      };
   }; // Geometry
}; // WBFL
