///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/CoordGeomTypes.h>
#include <CoordGeom/Angle.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/Station.h>

#include <GeomModel/Primitives.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/LineSegment2d.h>
#include <GeomModel/Circle.h>
#include <GeomModel/Circle2d.h>

#include <string>


namespace WBFL
{
   namespace COGO
   {
      /// @brief Class that implements coordinate geometry calculations
      class COORDGEOMCLASS COGO
      {
      public:
         COGO() = delete;
         COGO(const COGO& ) = delete;

         /// @brief Parses a comma delimited format string for angular measure and returns the individual tags
         static std::tuple<std::_tstring, std::_tstring, std::_tstring> ParseAngleTags(const std::_tstring& strFormat);


         /// @brief Converts an angle given in radians to deg-min-sec format
         /// @return Tuple of the format <Degree,Minute,Second>
         static std::tuple<short,unsigned short,Float64> ToDMS(Float64 value);

         /// @brief Converts an angle given in deg-min-sec format to an angle in radians
         static Float64 FromDMS(short deg, unsigned short min = 0, Float64 sec = 0.0);

         /// @brief Normalizes an angle between 0 and \f$2\pi\f$.
         static Float64 NormalizeAngle(Float64 angle);

         /// @brief Creates a line parallel to a line defined by p and direction
         /// @param p Point on the line
         /// @param direction Direction of the line
         /// @param offset Offset from the line to the new line
         /// @return The new parallel line
         static WBFL::Geometry::Line2d CreateParallelLine(const WBFL::Geometry::Point2d& p, const Direction& direction, Float64 offset);

         //
         // Measurement Functions
         //

         /// @brief Measures the angle formed by three non-coincident points.
         /// @image html Images/Angle.jpg
         /// @param from Point the angle is measured from
         /// @param vertex Point at the vertex of the angle
         /// @param to Point the angle is measured to
         /// @return The angle
         static WBFL::COGO::Angle MeasureAngle(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& vertex, const WBFL::Geometry::Point2d& to);

         /// @brief Measures the angle of a polygon
         /// @image html Images/Area.jpg
         /// The polygon must consist of at least three non-colinear points. Points may be defined either clockwise or counter-clockwise. The last point need not be the same as the first. 
         /// Degenerate polygons (polygon with intersecting edges such as a bow-tie shape) are not detected. An incorrect area will be computed if a degenerate polygon is input.
         /// @param vPoints Collection of points that comprise the polygon
         /// @return The area of the polygon
         static Float64 MeasureArea(std::vector<WBFL::Geometry::Point2d>& vPoints);
         
         /// @brief Measures the distance between two points.
         /// @image html Images/Distance.jpg
         /// @param p1 The first point
         /// @param p2 The second point
         /// @return Distance between the points
         static Float64 MeasureDistance(const WBFL::Geometry::Point2d& p1, const WBFL::Geometry::Point2d& p2);
         
         /// @brief Measures the direction between two points.
         /// @image html Images/Direction.jpg
         /// @param p1 The first point
         /// @param p2 The second point
         /// @return Direction of the line from the first to second point
         static WBFL::COGO::Direction MeasureDirection(const WBFL::Geometry::Point2d& p1, const WBFL::Geometry::Point2d& p2);
         
         /// @brief Measures the distance and direction between two points.
         /// @image html Images/Direction.jpg
         /// @param p1 The first point
         /// @param p2 The second point
         /// @return Returns a pair of the format (Distance,Direction). Distance between points. Direction of the line from the first to second point
         static std::pair<Float64, Direction>  ComputeInverse(const WBFL::Geometry::Point2d& p1, const WBFL::Geometry::Point2d& p2);

         //
         // Locate Functions
         //

         /// @brief Locates a point by distance and angle
         /// @image html Images/ByDistAngle.jpg
         /// @param from The first point
         /// @param to The second point
         /// @param distance Distance from the second point to the new point
         /// @param angle Angle from the line between the first and second point at which to locate the new point
         /// @param offset Offset from the line between the first and second point
         /// @return 
         static WBFL::Geometry::Point2d LocateByDistanceAndAngle(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& to, Float64 distance, const WBFL::COGO::Angle& angle, Float64 offset);

         /// @brief Locates a point by distance and deflection angle
         /// @image html Images/ByDistDefAngle.jpg
         /// @param from The first point
         /// @param to The second point
         /// @param distance Distance from the second point to the new point
         /// @param defAngle Deflection angle the line between the first and second point at which to locate the point
         /// @param offset Offset from the line between the first and second point
         /// @return 
         static WBFL::Geometry::Point2d LocateByDistanceAndDeflectionAngle(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& to, Float64 distance, const Angle& defAngle, Float64 offset);
         
         /// @brief Locates a point by distance and direction
         /// @image html Images/ByDistDir.jpg
         /// @param from The point the new point is located from
         /// @param distance Distance from the point to the new point
         /// @param direction Direction at which to locate the point
         /// @param offset Offset from the line defined by the point and direction
         /// @return 
         static WBFL::Geometry::Point2d LocateByDistanceAndDirection(const WBFL::Geometry::Point2d& from, Float64 distance, const Direction& direction, Float64 offset);

         /// @brief Locates a point on a line
         /// @image html Images/PointOnLine.jpg
         /// @param from The first point
         /// @param to The second point 
         /// @param distance Distance from the first point to the new point. If a negative value is used, the new point will be located before the start point.
         /// @param offset Offset from the line between the first and second point to the new point.
         /// @return 
         static WBFL::Geometry::Point2d LocatePointOnLine(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& to, Float64 distance, Float64 offset);

         /// @brief Locates a line parallel to a line defined by two points.
         /// @image html Images/ParallelLineByPoints.jpg
         /// @param from The first point
         /// @param to The second point
         /// @param offset Offset from the source line to the new line
         /// @return Pair of the form (Start Point of new line, End Point of new line)
         static std::pair<WBFL::Geometry::Point2d,WBFL::Geometry::Point2d> LocateParallelLineByPoints(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& to, Float64 offset);

         /// @brief Locates a parallel line segment.
         /// @image html Images/ParallelLineSegment.jpg
         /// @param ls A line segment
         /// @param offset Offset from the line segment to the new line segment
         /// @return The line segment
         static WBFL::Geometry::LineSegment2d LocateParallelLineSegment(const WBFL::Geometry::LineSegment2d& ls, Float64 offset);

         //
         // Intersect Functions
         //

         /// @brief Intersects two lines defined by point and direction.
         /// @image html Images/Bearings.jpg
         /// @param p1 First point on the first line
         /// @param dir1 Direction of the first line 
         /// @param offset1 Offset from the first line
         /// @param p2 Point on the second line 
         /// @param dir2 Direction of the second line
         /// @param offset2 Offset from the second line
         /// @return Intersection point
         static WBFL::Geometry::Point2d IntersectBearings(const WBFL::Geometry::Point2d& p1, const Direction& dir1, Float64 offset1, const WBFL::Geometry::Point2d& p2, const Direction& dir2, Float64 offset2);

         /// @brief Intersects a line defined by a point and direction with a circle.
         /// @image html Images/BearingCircle.jpg
         /// @param p1 Point on the line
         /// @param dir1 Direction of the line
         /// @param offset1 Offset from the line
         /// @param center Center of the circle
         /// @param radius Circle radius
         /// @param nearest Point that will be nearest the solution point in the event two intersection points are found
         /// @return Intersection point
         static WBFL::Geometry::Point2d IntersectBearingAndCircle(const WBFL::Geometry::Point2d& p1, const Direction& dir1, Float64 offset1, const WBFL::Geometry::Point2d& center, Float64 radius, const WBFL::Geometry::Point2d& nearest);

         /// @brief Intersects two circles
         /// @image html Images/Circles.jpg
         /// @param center1 Center of first circle
         /// @param radius1 Radius of first circle
         /// @param center2 Center of second circle
         /// @param radius2 Radius of second circle
         /// @param nearest Point that will be nearest the solution point in the event two intersection points are found
         /// @return Intersection point
         static WBFL::Geometry::Point2d IntersectCircles(const WBFL::Geometry::Point2d& center1, Float64 radius1, const WBFL::Geometry::Point2d& center2, Float64 radius2, const WBFL::Geometry::Point2d& nearest);

         /// @brief Intersects a line defined by two points with a circle.
         /// @image html Images/LineByPointsCircle.jpg
         /// @param p1 First point on the line
         /// @param p2 Second point on the line
         /// @param offset Offset from the line
         /// @param center Second point on the line
         /// @param radius Second point on the line
         /// @param nearest Point that will be nearest the solution point in the event two intersection points are found
         /// @return Intersection point
         static WBFL::Geometry::Point2d IntersectLineByPointsAndCircle(const WBFL::Geometry::Point2d& p1, const WBFL::Geometry::Point2d& p2, Float64 offset, const WBFL::Geometry::Point2d& center, Float64 radius, const WBFL::Geometry::Point2d& nearest);

         /// @brief Intersects two lines defined by points.
         /// @image html Images/LinesByPoints.jpg 
         /// @param p11 First point through which the first line passes
         /// @param p12 Second point through which the first line passes 
         /// @param offset1 Offset from the first line
         /// @param p21 First point through which the second line passes
         /// @param p22 Second point through which the second line passes
         /// @param offset2 Offset from the second line
         /// @return Intersection point
         static WBFL::Geometry::Point2d IntersectLinesByPoints(const WBFL::Geometry::Point2d& p11, const WBFL::Geometry::Point2d& p12, Float64 offset1, const WBFL::Geometry::Point2d& p21, const WBFL::Geometry::Point2d& p22, Float64 offset2);

         /// @brief Intersects two line segments.
         /// @image html Images/Lines.jpg
         /// @param ls1 First line segment
         /// @param offset1 Offset from first line segment
         /// @param ls2 Second line segment
         /// @param offset2 Offset from second line segment
         /// @return Intersection point
         static WBFL::Geometry::Point2d IntersectLineSegments(const WBFL::Geometry::LineSegment2d& ls1, Float64 offset1, const WBFL::Geometry::LineSegment2d& ls2, Float64 offset2);

         /// @brief Intersects a line segment and a circle
         /// @image html Images/LineSegmentCircle.jpg
         /// @param ls The line segment
         /// @param offset Offset from the line segment
         /// @param center Center of circle
         /// @param radius Circle radius
         /// @param nearest Point that will be nearest the solution point in the event two intersection points are found
         /// @return Intersection point
         static WBFL::Geometry::Point2d IntersectLineSegmentAndCircle(const WBFL::Geometry::LineSegment2d& ls, Float64 offset, const WBFL::Geometry::Point2d& center, Float64 radius, const WBFL::Geometry::Point2d& nearest);

         /// @brief Intersects a line and a circle
         /// @param line The line
         /// @param circle  The circle
         /// @param nearest Point that will be nearest the solution point in the event two intersection points are found
         /// @return Intersection point
         static WBFL::Geometry::Point2d IntersectLineAndCircle(const WBFL::Geometry::Line2d& line,const WBFL::Geometry::Circle2d& circle,const WBFL::Geometry::Point2d& nearest);

         /// @brief Intersections two lines
         /// @param line1 First line
         /// @param line2 Second line
         /// @return Intersection point
         static WBFL::Geometry::Point2d IntersectLines(const WBFL::Geometry::Line2d& line1, const WBFL::Geometry::Line2d& line2);

         //
         // Project Functions
         //
         
         /// @brief Projects a point onto a line defined by two points.
         /// @image html Images/PointOnLineByPoints.jpg
         /// @param point The point to project
         /// @param start First point on the line
         /// @param end Second point on the line
         /// @param offset Offset from the line
         /// @return Projected point
         static WBFL::Geometry::Point2d ProjectPointOnLineByPoints(const WBFL::Geometry::Point2d& point, const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end, Float64 offset);

         /// @brief Projects a point onto a line segment.
         /// @image html Images/PointOnLneSegment.jpg
         /// @param point The point to project
         /// @param segment The line segment
         /// @param offset Offset from the line segment
         /// @return Projected point
         static WBFL::Geometry::Point2d ProjectPointOnLineSegment(const WBFL::Geometry::Point2d& point, const WBFL::Geometry::LineSegment2d& segment, Float64 offset);

         //
         // Divide Functions
         //

         /// @brief Divides an arc into equal length segments.
         /// This method will divide an arc into nParts equally spaced points. nParts+1 points will be created including the start and end points.
         /// @image html Images/DivideArc.jpg
         /// @param from Point arc is measured from
         /// @param vertex Vertex point
         /// @param to Point arc is measured to
         /// @param nParts Number of parts to divide the arc into.
         /// @return A collection of the resulting points
         static std::vector<WBFL::Geometry::Point2d> DivideArc(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& vertex, const WBFL::Geometry::Point2d& to, IndexType nParts);

         /// @brief Divides the distance between two points.
         /// This method will divide a line segment defined by two points into nParts equally spaced points. nParts+1 points will be created.
         /// @image html Images/DivideBetweenPoints.jpg
         /// @param from Start point
         /// @param to End point
         /// @param nParts  Number of parts to divide the line segment into.
         /// @return A collection of the resulting points
         static std::vector<WBFL::Geometry::Point2d> DivideBetweenPoints(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& to, IndexType nParts);

         //
         // Tangent Functions
         //

         /// @brief Locates points tangent to two circles where the tangent lines cross between circles.
         /// If sign is CW then the points indicated in the figure are located. If sign is CCW, then the tangent points on the opposite tangent are located.
         /// @image html Images/Cross.gif
         /// @param center1 Center of the first circle
         /// @param radius1 Radius of the first circle
         /// @param center2 Center of the second circle
         /// @param radius2 Radius of the second circle
         /// @param sign Indicates which of the two tangent lines to use to locate the tangent points
         /// @return Pair in the form of (Point,Point) where the points are the tangent points
         static std::pair<WBFL::Geometry::Point2d, WBFL::Geometry::Point2d> CrossingTangents(const WBFL::Geometry::Point2d& center1, Float64 radius1, const WBFL::Geometry::Point2d& center2, Float64 radius2, TangentSign sign);

         /// @brief  Locates points tangent to two circles where the tangent lines are external to the circles.
         /// If sign is CW then the points indicated in the figure are located. If sign is CCW, then the tangent points on the opposite tangent are located.
         /// @image html Images/External.gif
         /// @param center1 Center of the first circle
         /// @param radius1 Radius of the first circle
         /// @param center2 Center of the second circle
         /// @param radius2 Radius of the second circle
         /// @param sign Indicates which of the two tangent lines to use to locate the tangent points
         /// @return Pair in the form of (Point,Point) where the points are the tangent points
         static std::pair<WBFL::Geometry::Point2d,WBFL::Geometry::Point2d> ExternalTangents(const WBFL::Geometry::Point2d& center1, Float64 radius1, const WBFL::Geometry::Point2d& center2, Float64 radius2, TangentSign sign);

         /// @brief Locates point tangent to a circle.
         /// If sign is CW then the points indicated in the figure are located. If sign is CCW, then the tangent points on the opposite tangent are located.
         /// @image html Images/Point.gif
         /// @param center Center of the circle
         /// @param radius Circle radius
         /// @param point Point forming a line passing through the circle center point
         /// @param sign Indicates which of the two tangent lines to use to locate the tangent points
         /// @return The tangent point
         static WBFL::Geometry::Point2d TangentPoint(const WBFL::Geometry::Point2d& center, Float64 radius, const WBFL::Geometry::Point2d& point, TangentSign sign);

         /// @brief Returns true if point is on the line formed by start and end and occurs before start
         static bool IsPointBeforeStart(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end, const WBFL::Geometry::Point2d& point);

         /// @brief Returns true if point is on the line formed by start and end and occurs after end
         static bool IsPointAfterEnd(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end, const WBFL::Geometry::Point2d& point);

         /// @brief Compares the relative location of two stations
         /// @param alignment Alignment used for basis of comparison. The comparison will take station equations into consideration.
         /// @param s1 The first station. If alignment is nullptr, must be a normalized station.
         /// @param s2 The second station. If alignment is nullptr, must be a normalized station.
         /// @return 0 if s1 is at the same location as s2, 1 if s1 is before s2 and -1 if s1 is after s2
         static Int8 CompareStations(std::shared_ptr<const Alignment> alignment, const Station& s1, const Station& s2);

         /// @brief Compares the relative location of two normalized stations
         /// @param s1 The first station. Must be a normalized station.
         /// @param s2 The second station. Must be a normalized station.
         /// @return 0 if s1 is at the same location as s2, 1 if s1 is before s2 and -1 if s1 is after s2
         static Int8 CompareNormalizedStations(const Station& s1, const Station& s2);

         /// @brief Converts a station a normalized value
         /// @param alignment 
         /// @param s The station to convert. If alignment is nullptr, must be a normalized station.
         /// @return 
         static Float64 ConvertToNormalizedStation(std::shared_ptr<const Alignment> alignment, const Station& s);
         
         /// @brief Converts a normalized station value to a Station object, making considerations for the station equations
         /// @param alignment The alignment with station equations.
         /// @param normalizedStation Station value
         /// @return Station object
         static Station ConvertFromNormalizedStation(std::shared_ptr<const Alignment> alignment, Float64 normalizedStation);

         /// @brief Converts a normalized station object to a Station object, making considerations for the station equations
         /// @param alignment The alignment with station equations.
         /// @param station Station object, which must be normalized (StationZoneIndex is INVALID_INDEX)
         /// @return Station object
         static Station ConvertFromNormalizedStation(std::shared_ptr<const Alignment> alignment, const Station& station);

         /// @brief Computes the distance between two stations. This is effectively s2 - s2, however station equations are taken into consideration.
         /// @param alignment The alignment with station equations.
         /// @param s1 The first station. If alignment is nullptr, must be a normalized station.
         /// @param s2 The second station. If alignment is nullptr, must be a normalized station.
         /// @return The distance between stations
         static Float64 DistanceBetweenStations(std::shared_ptr<const Alignment> alignment, const Station& s1, const Station& s2);

         /// @brief Moves the station by the specified distance, making considerations for the station equations
         /// @param alignment The alignment with station equations.
         /// @param station Station to be moved. If alignment is nullptr, must be a normalized station.
         /// @param distance Distance to move the station
         /// @return The station object after incrementing its location
         static Station& IncrementStation(std::shared_ptr<const Alignment> alignment, Station& station, Float64 distance);

         /// @brief Moves the station by the specified distance, making considerations for the station equations
         /// @param alignment The alignment with station equations.
         /// @param station Station from which the new station will be located. If alignment is nullptr, must be a normalized station.
         /// @param distance Distance to move the station
         /// @return A new station object offset from the original station
         static Station IncrementStationBy(std::shared_ptr<const Alignment> alignment, const Station& station, Float64 distance);
      };
   };
};
