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
#include <vector>

namespace WBFL
{
   namespace Geometry
   {
      class Line2d;
      class Point2d;
      class LineSegment2d;
      class Point3d;
      class Vector3d;
      class Circle2d;
      class Circle;
      class Arc;

      /// Utility class for geometric operations on 2d geometric primitives.  This
      /// class encapsulates operations that do not fit nicely into either class
      /// that they operate on.
      class GEOMMODELCLASS GeometricOperations
      {
      public:
         GeometricOperations() = delete;
         ~GeometricOperations() = delete;
         GeometricOperations(const GeometricOperations&) = delete;
         GeometricOperations& operator=(const GeometricOperations&) = delete;

         /// Finds the intersection between line (segment) l1 and l2 and stores the 
         /// result in p.  Returns the number of intersections found.  Returns 0 if 
         /// the lines are parallel or do not intersect,  the contents of p are 
         /// undefined.  Returns 1 if an intersect is found, p contains the 
         /// intersection point.  Returns -1 if the lines are collinear and 
         /// overlapping,  p contains the coordinates of the first overlapping point..
         static Int16 Intersect(const LineSegment2d& l1,
                                const LineSegment2d& l2,
                                Point2d* point);

         static Int16 Intersect(const Line2d& l1,
                                const Line2d& l2,
                                Point2d* point);

         static Int16 Intersect(const LineSegment2d& l1,
                                const Line2d& l2,
                                Point2d* point);

         static Int16 Intersect(const Line2d& l1,
                                const LineSegment2d& l2,
                                Point2d* point);

         static Int16 Intersect(const Line2d& l,
            const Circle2d& c,
            Point2d* p1, Point2d* p2);

         static Int16 Intersect(const Line2d& l,
            const Circle& c,
            Point2d* p1, Point2d* p2);

         static Int16 Intersect(const Line2d& l,
                                const Arc& arc, 
                                Point2d* p1,Point2d* p2);
         
         static Int16 Intersect(const Circle& c1,
            const Circle& c2,
            Point2d* p1, Point2d* p2);

         static Int16 Intersect(const Circle2d& c1,
            const Circle2d& c2,
            Point2d* p1, Point2d* p2);

         /// Returns true if l1 and l2 are parallel,  otherwise returns false.
         static bool IsParallel(const Line2d& l1, const Line2d& l2);
         static bool IsParallel(const LineSegment2d& l1, const LineSegment2d& l2);
         static bool IsParallel(const LineSegment2d& l1, const Line2d& l2);
         static bool IsParallel(const Line2d& l1, const LineSegment2d& l2);

         /// Returns true if l1 and l2 are parallel and in the same direction,  otherwise returns false.
         static bool SameDirection(const Line2d& l1, const Line2d& l2);
         static bool SameDirection(const LineSegment2d& l1, const LineSegment2d& l2);
         static bool SameDirection(const LineSegment2d& l1, const Line2d& l2);
         static bool SameDirection(const Line2d& l1, const LineSegment2d& l2);

         /// Generates points on a circle with a given center and radius.  The first
         /// point is located at (r,initAngle) where initAngle is measured counterclockwise
         /// from the X-axis.
         static void GenerateCircle(IndexType numPoints,///< number of points to generate
                                    const Point2d& center,///< center of the circle
                                    Float64 radius,///< radius of the circle
                                    Float64 initAngle,///< Counter-clockwise angle from the positive X-axis, measured in radians, that determines where the first point is located.
                                    std::vector<Point2d>* vPoints///< container where points are stored
         );

         /// Generates points on a circle with a given center and radius.  The first
         /// point is located at (r,initAngle) where initAngle is measured counterclockwise
         /// from the X-axis. Subsequent points are located by incrementing initAngle with deltaAngle.
         static void GenerateCircle(const Point2d& center,///< center of the circle
                                    Float64 radius,///< radius of the circle
                                    Float64 initAngle,///< Counter-clockwise angle from the positive X-axis, measured in radians, that determines where the first point is located.
                                    Float64 deltaAngle,///< Angular increment
                                    std::vector<Point2d>* vPoints///< container where points are stored
         );

         /// Computes the angle formed by three points
         /// \image html GeomUtil2d/Angle.jpg
         static Float64 Angle(
            const Point2d& start, ///< start point
            const Point2d& center, ///< vertex of the angle
            const Point2d& end ///< angle, measured in radians
         );

         /// Forces angle to be between zero and two pi. Angle is measured in radians.
         static Float64 NormalizeAngle(Float64 angle);

         /// Computes the shortest offset between a line and a point. Negative values indicate the point is to the left of the line.
         /// \image html GeomUtil2d/ShortestOffsetToPoint.jpg
         static Float64 ShortestOffsetToPoint(const Line2d& line, const Point2d& point);

         /// @brief Reflects a point across a line
         /// @param point the point to be reflected
         /// @param line the line across the point is reflected
         /// @return the reflected point
         static Point2d ReflectPointAcrossLine(const Point2d& point, const Line2d& line);

         /// Transforms a point from the local 3d system to a global 3d space.
         /// origin is the coordinate of the origin of the local coordinate system, in global coordinates
         /// unitVector is a unit vector that defines the local coordinate system,
         /// point is the point to be transformed
         static Point3d LocalToGlobal(const Point3d& origin,
                                        const Vector3d& unitVector,
                                        Float64 angle,
                                        const Point3d& point);

         /// Transforms a point from the global 3d space to a local 3d coordinate system.
         /// origin is the coordinate of the origin of the local coordinate system, in global coordinates
         /// unitVector is a unit vector that defines the local coordinate system,
         /// point is the point to be transformed
         static Point3d GlobalToLocal(const Point3d& origin,
                                        const Vector3d& unitVector,
                                        Float64 angle,
                                        const Point3d& global);

         /// Transforms a point from the local 2d system to a global 2d space.
         /// origin is the coordinate of the origin of the local coordinate system, in global coordinates
         /// angle is the rotation angle of the local coordinate system, in radians, measured CCW from +X axis
         /// point is the point to be transformed
         static Point2d LocalToGlobal(const Point2d& origin,
                                        Float64 angle,
                                        const Point2d& local);

         /// Transforms a point from the global 2d space to a local 2d space.
         /// origin is the coordinate of the origin of the local coordinate system, in global coordinates
         /// angle is the rotation angle of the local coordinate system, in radians, measured CCW from +X axis
         /// point is the point to be transformed
         static Point2d GlobalToLocal(const Point2d& origin,
                                        Float64 angle,
                                        const Point2d& global);

         /// locates a point on the line defined by p1 and p2, at a distance distFromStart from p1
         static Point2d PointOnLine(const Point2d& p1, const Point2d& p2, Float64 distFromStart);

         /// Locates the point on a line nearest a specified point
         /// \image html GeomUtil2d/PointOnLineNearest.jpg
         static Point2d PointOnLineNearest(const Line2d& line, const Point2d& point);

         /// Creates a line that is parallel to the specified line.
         static Line2d CreateParallelLine(
            const Line2d& line, ///< The source line
            Float64 dist ///< Distance to offset the parallel line from the source line. The parallel line will be on the right side of the source line if this parameter is greater than zero. 
         );

         /// Creates a line that is parallel to the specified line.
         static LineSegment2d CreateParallelLineSegment(
            const LineSegment2d& segment, ///< The source line
            Float64 dist ///< Distance to offset the parallel line from the source line. The parallel line will be on the right side of the source line if this parameter is greater than zero. 
         );

         /// Creates a line parallel to the specified line, and passing through a specified point. The parallel line has the same direction as the specified line.
         /// \image html GeomUtil2d/CreateParallelLineThroughPoint.jpg
         static Line2d CreateParallelLineThroughPoint(const Line2d& line, const Point2d& point);

         /// Creates a line normal to the specified line, and passing through a specified point. The normal line is directed to the right of the specified line.
         /// \image html GeomUtil2d/CreateNormalLineThroughPoint.jpg
         static Line2d CreateNormalLineThroughPoint(const Line2d& line, const Point2d& point);

         /// Returns true if p is in the triangle formed by verties A, B, and C
         static bool IsPointInTriangle(const Point2d& p, const Point2d& A, const Point2d& B, const Point2d& C);

         // Returns true if a point lies along a segment within a tolerance distance
         static bool DoesLineSegmentContainPoint(const LineSegment2d& l1, const Point2d& point, Float64 tolerance);
      };
   }; // Geometry
}; // WBFL
