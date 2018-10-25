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

#ifndef INCLUDED_COGO_IPROJECT_H_
#define INCLUDED_COGO_IPROJECT_H_
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
   cogoIProject

   Interface for locating COGO points by making projections.

DESCRIPTION
   Interface for locating COGO points by making projections.

LOG
   Richard Brice : 04.22.1999 : Created File
*****************************************************************************/

struct cogoIProject
{
   //------------------------------------------------------------------------
   bool ProjectPointOnLine(gpPoint2d* pNewPoint,
                           Int32 fromPointId,
                           Int32 toPointId,
                           Float64 offset,
                           Int32 projPointId) const;

   //------------------------------------------------------------------------
   Int32 ProjectPointOnLine(Int32 fromPointId,
                            Int32 toPointId,
                            Float64 offset,
                            Int32 projPointId);

   //------------------------------------------------------------------------
   Int32 ProjectPointOnLine(const gpPoint2d& fromPoint,
                            const gpPoint2d& toPoint,
                            Float64 offset,
                            const gpPoint2d& projPoint);

};

#endif // INCLUDED_COGO_IPROJECT_H_
