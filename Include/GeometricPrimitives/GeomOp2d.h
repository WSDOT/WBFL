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

#ifndef INCLUDED_GEOMETRY_GEOMOP2D_H_
#define INCLUDED_GEOMETRY_GEOMOP2D_H_
#pragma once

// SYSTEM INCLUDES
//
#include <vector>
#include <GeometricPrimitives\GeometryExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gpLine2d;
class gpPoint2d;
class gpLineSegment2d;
class gpPoint3d;
class gpVector3d;
class gpCircle;
class gpArc;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gpGeomOp2d

   Utility class for geometric operations on 2d geometric primitives.  


DESCRIPTION
   Utility class for geometric operations on 2d geometric primitives.  This
   class encapsulates operations that do not fit nicely into either class
   that they operate on.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 11.19.1997 : Created file
*****************************************************************************/

class GEOMCLASS gpGeomOp2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gpGeomOp2d();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpGeomOp2d();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Intersect
   // Finds the intersection between line (segment) l1 and l2 and stores the 
   // result in p.  Returns the number of intersections found.  Returns 0 if 
   // the lines are parallel or do not intersect,  the contents of p are 
   // undefined.  Returns 1 if an intersect is found, p contains the 
   // intersection point.  Returns -1 if the lines are collinear and 
   // overlapping,  p contains the coordinates of the first overlapping point..
   static Int16 Intersect(gpPoint2d* pPoint,
                          const gpLineSegment2d& l1,
                          const gpLineSegment2d& l2);

   static Int16 Intersect(gpPoint2d* pPoint,
                          const gpLine2d& l1,
                          const gpLine2d& l2);

   static Int16 Intersect(gpPoint2d* pPoint,
                          const gpLineSegment2d& l1,
                          const gpLine2d& l2);

   static Int16 Intersect(gpPoint2d* pPoint,
                          const gpLine2d& l1,
                          const gpLineSegment2d& l2);

   static Int16 Intersect(gpPoint2d* p1,gpPoint2d* p2,
                          const gpLine2d& l,
                          const gpCircle& c);

   static Int16 Intersect(gpPoint2d* p1,gpPoint2d* p2,
                          const gpLine2d& l,
                          const gpArc& arc);

   //------------------------------------------------------------------------
   // IsParallel
   // Returns true if l1 and l2 are parallel,  otherwise returns false.
   static bool IsParallel(const gpLineSegment2d& l1,
                          const gpLineSegment2d& l2);

   static bool IsParallel(const gpLine2d& l1,
                          const gpLine2d& l2);

   static bool IsParallel(const gpLineSegment2d& l1,
                          const gpLine2d& l2);

   static bool IsParallel(const gpLine2d& l1,
                          const gpLineSegment2d& l2);

   //------------------------------------------------------------------------
   // GenerateCircle
   // Generates points on a circle with a given center and radius.  The first
   // point is located at (r,initAngle) where initAngle is measured counterclockwise
   // from the X-axis.
   static void GenerateCircle(Int16 numPoints,
                              const gpPoint2d& center,
                              Float64 radius,
                              Float64 initAngle,
                              std::vector<gpPoint2d>* ppoints);

   static void GenerateCircle(const gpPoint2d& center,
                              Float64 radius,
                              Float64 initAngle,
                              Float64 deltaAngle,
                              std::vector<gpPoint2d>* ppoints);

   //------------------------------------------------------------------------
   // Forces angle to be between zero and two pi. Angle is measured in radians.
   static Float64 NormalizeAngle(Float64 angle);

   //------------------------------------------------------------------------
   // Transforms a point from the local 3d system to a global 3d space.
   // origin is the coordinate of the origin of the local coordinate system, in global coordinates
   // unitVector is a unit vector that defines the local coordinate system,
   // point is the point to be transformed
   static gpPoint3d LocalToGlobal(const gpPoint3d& origin,
                                  const gpVector3d& unitVector,
                                  Float64 angle,
                                  const gpPoint3d& point);

   //------------------------------------------------------------------------
   // Transforms a point from the global 3d space to a local 3d coordinate
   // system.
   // origin is the coordinate of the origin of the local coordinate system, in global coordinates
   // unitVector is a unit vector that defines the local coordinate system,
   // point is the point to be transformed
   static gpPoint3d GlobalToLocal(const gpPoint3d& origin,
                                  const gpVector3d& unitVector,
                                  Float64 angle,
                                  const gpPoint3d& global);

   //------------------------------------------------------------------------
   // Transforms a point from the local 2d system to a global 2d space.
   // origin is the coordinate of the origin of the local coordinate system, in global coordinates
   // angle is the rotation angle of the local coordinate system, in radians, measured CCW from +X axis
   // point is the point to be transformed
   static gpPoint2d LocalToGlobal(const gpPoint2d& origin,
                                  Float64 angle,
                                  const gpPoint2d& local);

   //------------------------------------------------------------------------
   // Transforms a point from the global 2d space to a local 2d space.
   // origin is the coordinate of the origin of the local coordinate system, in global coordinates
   // angle is the rotation angle of the local coordinate system, in radians, measured CCW from +X axis
   // point is the point to be transformed
   static gpPoint2d GlobalToLocal(const gpPoint2d& origin,
                                  Float64 angle,
                                  const gpPoint2d& global);

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // A self-test function - returns true if passed.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

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
   virtual void Dump(dbgDumpContext& dc) const;
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   gpGeomOp2d(const gpGeomOp2d&);
   gpGeomOp2d& operator=(const gpGeomOp2d&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GEOMETRY_GEOMOP2D_H_
