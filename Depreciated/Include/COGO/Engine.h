///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_COGO_ENGINE_H_
#define INCLUDED_COGO_ENGINE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Cogo\CogoExp.h>
#include <Cogo\CogoDirection.h>
#include <Cogo\CogoAngle.h>
#include <GeometricPrimitives\Primitives.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   cogoEngine

   Utility class the performs coordinate geometry calculations on primative
   COGO entities such as points, lines, arc, circles, etc.


DESCRIPTION
   Utility class the performs coordinate geometry calculations on primative
   COGO entities such as points, lines, arc, circles, etc.

   This is a utility class. It cannot be instantiated.  All of its member
   functions are static.

COPYRIGHT
   Copyright (c) 1999
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   Richard Brice : 04.21.1999 : Created file
*****************************************************************************/

class COGOCLASS cogoEngine
{
public:
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Computes the inverse between two points
   static void Inverse(Float64* pDistance,
                       cogoDirection* pDirection,
                       const gpPoint2d& rFromPoint,
                       const gpPoint2d& rToPoint);

   //------------------------------------------------------------------------
   // Computes the clockwise angle at vertex from fromPnt to toPnt.
   static cogoAngle ComputeAngle(const gpPoint2d& fromPnt,
                                 const gpPoint2d& vertex,
                                 const gpPoint2d& toPnt );

   //------------------------------------------------------------------------
   // Computes the area of a polygon.
   static Float64 ComputeArea(const std::vector<gpPoint2d>& vPoints);

   //------------------------------------------------------------------------
   // Locates one point from another, using a distance and direction.  
   static gpPoint2d LocateByDistDir(const gpPoint2d& fromPoint,
                                    Float64 distance,
                                    const cogoDirection& direction);

   //------------------------------------------------------------------------
   // Locates a point one a line defined by two other points.
   // If distance is less than zero,  the new point is located
   // on the opposite size of fromPoint than toPoint.
   static gpPoint2d LocatePointOnLine(const gpPoint2d& fromPoint,
                                      const gpPoint2d& toPoint,
                                      Float64 distance);

   //------------------------------------------------------------------------
   // Locates a point by backsight on fromPoint, turning angle on toPoint at
   // a distance of distance. An angle that is less than zero is considered 
   // to be counter-clockwise.
   static gpPoint2d LocateByDistAngle(const gpPoint2d& fromPoint,
                                      const gpPoint2d& toPoint,
                                      Float64 distance,
                                      const cogoAngle& angle);
   //------------------------------------------------------------------------
   // Locates a point by backsight on fromPoint, turning angle
   // on toPoint at a distance of distance. An angle that is
   // less than zero is considered to be counter-clockwise.
   static gpPoint2d LocateByDistDefAngle(const gpPoint2d& fromPoint,
                                         const gpPoint2d& toPoint,
                                         Float64 distance,
                                         const cogoAngle& angle);

   //------------------------------------------------------------------------
   static void LocateParallelLine(gpPoint2d* pStart,
                                  gpPoint2d* pEnd,
                                  const gpPoint2d& p1,
                                  const gpPoint2d& p2,
                                  Float64 distance);

   //------------------------------------------------------------------------
   static gpPoint2d ProjectPointOnLine(const gpPoint2d& fromPoint,
                                       const gpPoint2d& toPoint,
                                       Float64 offset,
                                       const gpPoint2d& projPoint);

   //------------------------------------------------------------------------
   static bool LineLineIntersect(gpPoint2d* pPoint,
                                 const gpPoint2d& pnt1,const cogoDirection& d1,Float64 offset1,
                                 const gpPoint2d& pnt2,const cogoDirection& d2,Float64 offset2);

   //------------------------------------------------------------------------
   static bool LineLineIntersect(gpPoint2d* pPoint,
                                 const gpPoint2d& pnt1a,const gpPoint2d& pnt1b,
                                 const gpPoint2d& pnt2a,const gpPoint2d& pnt2b);
   //------------------------------------------------------------------------
   // Divides the line from p1 to p2 into nParts equal length parts.
   static std::vector<gpPoint2d> DivideLine(const gpPoint2d& p1, const gpPoint2d& p2,Uint16 nParts);

   //------------------------------------------------------------------------
   // Divides the clockwise arc defined by fromPnt, vertex, toPnt into nParts
   // equal length parts.
   static std::vector<gpPoint2d> DivideArc(const gpPoint2d& fromPnt, const gpPoint2d& vertex,const gpPoint2d& toPnt,Uint16 nParts);

   // GROUP: ACCESS
   // GROUP: INQUIRY

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

   //------------------------------------------------------------------------
   cogoEngine();
   cogoEngine(const cogoEngine& rOther);
   cogoEngine& operator = (const cogoEngine& rOther);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
#if defined _UNITTEST
public:
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_COGO_ENGINE_H_

