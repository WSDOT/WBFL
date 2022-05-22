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

#ifndef INCLUDED_GEOMETRY_LINESEGMENT2D_H_
#define INCLUDED_GEOMETRY_LINESEGMENT2D_H_
#pragma once

#include <vector>
#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace Geometry
   {
      /// Interface defining a line segment in a two dimensional Cartesian coordinate system.
      ///
      /// A line segment is a line with finite length between start and end points
      /// \image html LineSegment2d/LineSegment.jpg
      class GEOMMODELCLASS LineSegment2d
      {
      public:
         LineSegment2d();

         /// Explicit constructor.  Creates a line segment from start to end.
         LineSegment2d(std::shared_ptr<Point2d>& start, std::shared_ptr<Point2d>& end);

         LineSegment2d(const Point2d& start, const Point2d& end);

         /// Explicit constructor.  Creates a line segment from start to end.
         LineSegment2d(Float64 x1,Float64 y1, Float64 x2,Float64 y2);

         /// Explicit constructor.  Creates a line segment that starts at start 
         /// and ends at (start.X()+relEnd.Dx(),start.Y()+relEnd.Dy()).
         LineSegment2d(std::shared_ptr<Point2d>& start, const Size2d& relEnd);
         LineSegment2d(const Point2d& start, const Size2d& relEnd);

         virtual ~LineSegment2d();

         LineSegment2d(const LineSegment2d&);
         LineSegment2d& operator=(const LineSegment2d&);

         bool operator==(const LineSegment2d& other) const;
         bool operator!=(const LineSegment2d& other) const;

         void ThroughPoints(std::shared_ptr<Point2d>& start, std::shared_ptr<Point2d>& end);
         void ThroughPoints(const Point2d& start, const Point2d& end);

         /// Returns true if point is contained between the end points of this line 
         /// segment,  otherwise returns false.
         bool ContainsPoint(const Point2d& point,Float64 tolerance = 1.0e-5) const;

         /// Returns the length of the line segment.
         Float64 Length() const;

         /// Sets the start point of the line segment.
         void SetStartPoint(std::shared_ptr<Point2d>& startPoint);
         void SetStartPoint(const Point2d& startPoint);

         /// Returns the start point of the line segment.
         std::shared_ptr<Point2d>& GetStartPoint();
         const std::shared_ptr<Point2d>& GetStartPoint() const;

         /// Sets the end point of the line segment.
         void SetEndPoint(std::shared_ptr<Point2d>& endPoint);
         void SetEndPoint(const Point2d& endPoint);

         /// Returns the end point of the line segment.
         std::shared_ptr<Point2d>& GetEndPoint();
         const std::shared_ptr<Point2d>& GetEndPoint() const;

         /// Returns the mid point of the line segment.
         Point2d GetMidPoint() const;

         LineSegment2d& Offset(Float64 distance);
         LineSegment2d& OffsetBy(Float64 distance) const;

         /// Offsets this line segment by the given delta arguments. This line is 
         /// changed by translating its control points by the given distance.  
         /// Returns a reference to this line segment.
         LineSegment2d& Offset(Float64 dx,Float64 dy);
         LineSegment2d& Offset(const Size2d& size);

         /// Returns a segment line which is offset to this line segment by the given 
         /// displacement arguments. This is not changed.
         LineSegment2d OffsetBy(Float64 dx, Float64 dy) const;
         LineSegment2d OffsetBy(const Size2d& size) const;

         /// Rotates this line segment about the given center point by the given 
         /// angle (in radians). This is changed. Returns a reference to this line segment.
         LineSegment2d& Rotate(const Point2d& centerPoint, Float64 angle);

         /// Returns a line segment equal to this line segment rotated about the 
         /// given center point by the given angle (in radians). This is not changed.
         LineSegment2d RotateBy(const Point2d& centerPoint, Float64 angle) const;
   
         /// Divides the line segment into nSpaces equally divided spaces.  Returns
         /// a vector containing the coordinate of each point, including the line segment end points.
        /// \image html LineSegment2d/DivideLineSegment.jpg
         std::vector<Point2d> Divide(IndexType nSpaces) const;
  
      #if defined _DEBUG
         /// Returns true if the class is in a valid state, otherwise returns false
         bool AssertValid() const;

         /// Dumps the contents of the class to the given stream.
         void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         /// Self-Test function. Returns true if successful.
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST

      private:
         std::shared_ptr<Point2d> m_pStart{ std::make_shared<Point2d>(0,0) };
         std::shared_ptr<Point2d> m_pEnd{ std::make_shared<Point2d>(1,0) };
      };
   }; // Geometry
}; // WBFL

#endif // INCLUDED_GEOMETRY_LINESEGMENT2D_H_
