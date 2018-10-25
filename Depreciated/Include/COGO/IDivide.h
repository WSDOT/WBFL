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

#ifndef INCLUDED_COGO_IDIVIDE_H_
#define INCLUDED_COGO_IDIVIDE_H_
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
   cogoIDivide

   Methods for locating points by dividing geometric constructs

DESCRIPTION
   Methods for locating points by dividing geometric constructs

LOG
   Richard Brice : 04.22.1999 : Created File
*****************************************************************************/

struct cogoIDivide
{
   //------------------------------------------------------------------------
   // Divides the line from fromPointId to toPointId into nParts equal
   // length parts. The intermediate points are stored in vPoints.
   // Returns true if successful, otherwise false.
   bool DivideLine(std::vector<gpPoint2d>* pPoints,
                   Int32 fromPointId, Int32 toPointId,Uint16 nParts) const;

   //------------------------------------------------------------------------
   // Divides the line from fromPointId to toPointId into nParts equal
   // length parts. The intermediate points are stored begining with id
   // and incremented by idInc. Care must be taken not to override
   // previously stored points.
   // Returns true if successful, otherwise false.
   bool DivideLine(std::vector<Int32>* pIds,
                   Int32 fromPointId, Int32 toPointId,Uint16 nParts);

   //------------------------------------------------------------------------
   // Divides the line from p1 to p2 into nParts equal
   // length parts. The intermediate points are stored begining with id
   // and incremented by idInc. Care must be taken not to override
   // previously stored points.
   // Returns true if successful, otherwise false.
   void DivideLine(std::vector<Int32>* pIds,
                   const gpPoint2d& p1, const gpPoint2d& p2,Uint16 nParts);

   //------------------------------------------------------------------------
   // Divides the clockwise arc defined by fromId, vertexId, 
   // toId into nParts equal length parts. The intermediate 
   // points are stored in vPoints.  Returns true if successful,
   // otherwise false.
   bool DivideArc(std::vector<gpPoint2d>* pPoints,
                  Int32 fromId,Int32 vertexId,Int32 toId,Uint16 nParts) const;

   //------------------------------------------------------------------------
   // Divides the clockwise arc defined by fromId, vertexId, 
   // toId into nParts equal length parts.
   // The intermediate points are stored begining with id
   // and incremented by idInc. Care must be taken not to override
   // previously stored points.
   // Returns true if successful, otherwise false.
   bool DivideArc(std::vector<Int32>* pIds,
                  Int32 fromId,Int32 vertexId,Int32 toId,Uint16 nParts);

   //------------------------------------------------------------------------
   // Divides the clockwise arc defined by fromPnt, vertex, 
   // toPnt into nParts equal length parts.
   // The intermediate points are stored begining with id
   // and incremented by idInc. Care must be taken not to override
   // previously stored points.
   // Returns true if successful, otherwise false.
   void DivideArc(std::vector<Int32>* pIds,
                  const gpPoint2d& fromPnt,const gpPoint2d& vertex,const gpPoint2d& toPnt,Uint16 nParts);

};

#endif // INCLUDED_COGO_IDIVIDE_H_
