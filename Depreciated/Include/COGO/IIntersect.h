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

#ifndef INCLUDED_COGO_IINTERSECT_H_
#define INCLUDED_COGO_IINTERSECT_H_
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

// MISCELLANEOUS
//

/*****************************************************************************
INTERFACE
   cogoIIntersect

   Methods for locating a points by finding intersections

DESCRIPTION
   Methods for locating a points by finding intersections

LOG
   Richard Brice : 04.22.1999 : Created File
*****************************************************************************/

struct cogoIIntersect
{
   //------------------------------------------------------------------------
   bool LineLineIntersect(gpPoint2d* pPoint,
                          Int32 pnt1,const cogoDirection& d1,Float64 offset1,
                          Int32 pnt2,const cogoDirection& d2,Float64 offset2);

   //------------------------------------------------------------------------
   bool LineLineIntersect(gpPoint2d* pPoint,
                          Int32 p1,
                          Int32 p2,
                          Float64 offset1,
                          Int32 p3,
                          Int32 p4,
                          Float64 offset2);

   //------------------------------------------------------------------------
   // Finds the intersection point of the line passing through points p1 and p2
   // and the line passing through p3 and p4.  The intersection points is stored
   // with id id.
   Int32 LineLineIntersect(Int32 p1,
                           Int32 p2,
                           Float64 offset1,
                           Int32 p3,
                           Int32 p4,
                           Float64 offset2);

};

#endif // INCLUDED_COGO_IINTERSECT_H_
