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

#ifndef INCLUDED_COGO_ILOCATE_H_
#define INCLUDED_COGO_ILOCATE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <WbflTypes.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gpPoint2d;
class cogoDirection;
class cogoAngle;

// MISCELLANEOUS
//

/*****************************************************************************
INTERFACE
   cogoILocate

   Methods for locating points in a COGO model.

DESCRIPTION
   Methods for locating points in a COGO model.

LOG
   Richard Brice : 04.22.1999 : Create File
*****************************************************************************/

struct cogoILocate
{
   //------------------------------------------------------------------------
   // Locates one point from another, using a distance and
   // direction.  A new point is created and stored in the model.
   Int32 LocateByDistDir(Int32 refPointId,   // id of reference point
                         Float64 distance,   // distance from reference point to new point
                         const cogoDirection& direction); // direction between the two points

   //------------------------------------------------------------------------
   // Locates one point from another, using a distance and direction.  
   bool LocateByDistDir(gpPoint2d* pNewPoint,
                        Int32 refPointId,   // id of reference point
                        Float64 distance,   // distance from reference point to new point
                        const cogoDirection& direction); // direction between the two points

   //------------------------------------------------------------------------
   // Locates one point from another, using a distance and
   // direction.  A new point is created and stored in the model.
   Int32 LocateByDistDir(const gpPoint2d& rRefPoint, // reference point
                         Float64 distance,   // distance from reference point to new point
                         const cogoDirection& direction); // direction between the two points

   //------------------------------------------------------------------------
   // Locates a point on a line defined by two other points.
   // A new point is created and stored in the model.
   // If distance is less than zero,  the new point is located
   // on the opposite size of fromPointId than toPointId.
   // Returns id of new point or COGO_ERROR.
   Int32 LocatePointOnLine(Int32 fromPointId,   // id of first point on the line
                           Int32 toPointId,     // id of second point on the line
                           Float64 distance);   // distance from first point to new point

   //------------------------------------------------------------------------
   // Locates a point on a line defined by two other points.
   // If distance is less than zero,  the new point is located
   // on the opposite size of fromPointId than toPointId.
  bool LocatePointOnLine(gpPoint2d* pNewPoint,
                         Int32 fromPointId,   // id of first point on the line
                         Int32 toPointId,     // id of second point on the line
                         Float64 distance) const; // distance from first point to new point

   //------------------------------------------------------------------------
   // Locates a point on a line defined by two other points.
   // A new point is created and stored in the model.
   // If distance is less than zero,  the new point is located
   // on the opposite size of fromPointId than toPointId.
   // Returns id of new point or COGO_ERROR.
   Int32 LocatePointOnLine(const gpPoint2d& fromPoint,
                           const gpPoint2d& toPoint,
                           Float64 distance);   // distance from first point to new point

   //------------------------------------------------------------------------
   // Locates a point by backsight on fromPoint, turning angle
   // on toPoint at a distance of distance. An angle that is
   // less than zero is considered to be counter-clockwise.
   bool LocateByDistAngle(gpPoint2d* pNewPoint,
                          Int32 fromPointID,
                          Int32 toPointId,
                          Float64 distance,
                          const cogoAngle& angle) const;
   Int32 LocateByDistAngle(const gpPoint2d& fromPoint,
                           const gpPoint2d& toPoint,
                           Float64 distance,
                           const cogoAngle& angle);
   Int32 LocateByDistAngle(Int32 fromPointId,
                           Int32 toPointId,
                           Float64 distance,
                           const cogoAngle& angle);

   //------------------------------------------------------------------------
   // Locates a point by backsight on fromPoint, turning angle
   // on toPoint at a distance of distance. An angle that is
   // less than zero is considered to be counter-clockwise.
   bool LocateByDistDefAngle(gpPoint2d* pNewPoint,
                             Int32 fromPointID,
                             Int32 toPointId,
                             Float64 distance,
                             const cogoAngle& angle) const;
   Int32 LocateByDistDefAngle(const gpPoint2d& fromPoint,
                              const gpPoint2d& toPoint,
                              Float64 distance,
                              const cogoAngle& angle);
   Int32 LocateByDistDefAngle(Int32 fromPointId,
                              Int32 toPointId,
                              Float64 distance,
                              const cogoAngle& angle);

   //------------------------------------------------------------------------
   bool LocateParallelLine(gpPoint2d* pStart,
                           gpPoint2d* pEnd,
                           Int32 fromPointId,
                           Int32 toPointId,
                           Float64 distance) const;
   Int32 LocateParallelLine(Int32* pStartId,
                            Int32* pEndId,
                            Int32 fromPointId,
                            Int32 toPointId,
                            Float64 distance);
   Int32 LocateParallelLine(Int32* pStartId,
                            Int32* pEndId,
                            const gpPoint2d& p1,
                            const gpPoint2d& p2,
                            Float64 distance);
};

#endif // INCLUDED_COGO_ILOCATE_H_
