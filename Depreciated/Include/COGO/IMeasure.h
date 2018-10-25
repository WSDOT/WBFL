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

#ifndef INCLUDED_COGO_IMEASURE_H_
#define INCLUDED_COGO_IMEASURE_H_
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
class cogoAngle;
class cogoDirection;

// MISCELLANEOUS
//

/*****************************************************************************
INTERFACE
   cogoIMeasure

   Methods for measuring things in a COGO model.

DESCRIPTION
   Methods for measuring things in a COGO model.

LOG
   Richard Brice : 04.22.1999 : Create File
*****************************************************************************/

struct cogoIMeasure
{
   //------------------------------------------------------------------------
   virtual ~cogoIMeasure() {}

   //------------------------------------------------------------------------
   virtual bool ComputeArea(Float64* pArea,const std::vector<Int32>& vPointIds) const = 0;

   //------------------------------------------------------------------------
   // Computes the clockwise angle at vertexId from fromId
   // to toId. Returns true if successful.
   virtual bool ComputeAngle(cogoAngle* pAngle,Int32 fromId,Int32 vertexId,Int32 toId) const = 0;

   //------------------------------------------------------------------------
   // Computes the inverse between two points
   virtual bool Inverse(Float64* pDistance,         // Distance between points
                        cogoDirection* pDirection,  // Direction from point 1 to point 2
                        Int32 fromPointId,          // id of point 1 - from point
                        Int32 toPointId) const = 0; // id of point 2 - to point
};

#endif // INCLUDED_COGO_IMEASURE_H_
