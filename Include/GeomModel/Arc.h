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

#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace Geometry
   {

/// A class to represent an arc in the X-Y Plane.  The arc is defined its start,
/// center, and end points.  The arc is always taken in a counter-clockwise direction.
class GEOMMODELCLASS Arc
{
public:
   /// Default constructor. Circle centered at (0,0) with radius of zero
   Arc();

   /// Defines an arc using three non-colinear points.
   Arc(const Point2d& start, const Point2d& center, const Point2d& end);

   virtual ~Arc();

   Arc(const Arc&) = default;
   Arc& operator=(const Arc&) = default;

   bool operator==(const Arc& other) const;
   bool operator!=(const Arc& other) const;


   void SetStart(const Point2d& start);
   Point2d& GetStart();
   const Point2d& GetStart() const;
   void SetCenter(const Point2d& center);
   Point2d& GetCenter();
   const Point2d& GetCenter() const;
   void SetEnd(const Point2d& end);
   Point2d& GetEnd();
   const Point2d& GetEnd() const;

   /// Reverses the direction of the arc by swapping the start and end points.
   void Reverse();

   Float64 GetRadius() const;
   Float64 GetLength() const;

   /// Computes the distance along the arc to the point found by intersecting
   /// a line from center to p with the arc.  If the line does not intersect
   /// the arc, the projected arc length is used.
   Float64 Distance(const Point2d& p) const;

   bool IsPointOnArc(const Point2d& p) const;

   /// Returns the central angle of the arc.
   Float64 GetCentralAngle() const;

   /// Divides an arch segment into equal length pieces.
   /// The coordinates of N - 1 points are computed, where N is the number of spaces.
   /// \image html Arc/DivideArc.jpg
   std::vector<Point2d> Divide(IndexType nSpaces) const;

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
   Point2d m_Start;
   Point2d m_Center;
   Point2d m_End;
};

   }; // Geometry
}; // WBFL
