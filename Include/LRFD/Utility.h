///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2011  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_UTILITY_H_
#define INCLUDED_LRFD_UTILITY_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdUtility

   Utility class for miscellaneous LRFD formulations.


DESCRIPTION
   Utility class for miscellaneous LRFD formulations.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.18.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdUtility
{
public:
   // GROUP: ENUMERATIONS
   enum GirderPosition{ LeftExterior, Interior, RightExterior};

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdUtility();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Computes the effective slab width of a slab on IBeam section.
   // Code Reference: 1st Edition Article 4.6.2.6
   // Units: Consistant Length Units
   // 
   // effLength        Effective Span Length
   // leftSpacing      Spacing to girder left of this one or distance to
   //                  edge of slab if left exterior girder.
   // rightSpacing     Spacing to girder right of this one or distance to
   //                  edge of slab if right exterior girder
   // tSlab            Structural depth of the slab
   // tWeb             Thickness of the I-beam web
   // wTopFlange       Width of the I-beam top flange
   // pos              Position of this girder in the cross section
   static Float64 IbeamEffFlangeWidth(Float64 effSpanLength,
                                      Float64 leftSpacing,
                                      Float64 rightSpacing,
                                      Float64 tSlab,
                                      Float64 tWeb,
                                      Float64 wTopFlange,
                                      GirderPosition position);

   //------------------------------------------------------------------------
   // Returns the multiple presence factor the the specified number of
   // loaded lanes. Article 3.6.1.1.2
   static Float64 GetMultiplePresenceFactor(Uint32 nLanesLoaded);

   //------------------------------------------------------------------------
   // Returns the width of a single design lane, given the curb to curb width
   // of the driving surface.  Article 3.6.1.1.1
   static Float64 GetDesignLaneWidth(Float64 wCurbToCurb);

   //------------------------------------------------------------------------
   // Returns the number of design lanes, given the curb to curb width
   // of the driving surface.  Article 3.6.1.1.1
   static Uint16 GetNumDesignLanes(Float64 wCurbToCurb);

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _UNITTEST
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

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
   // Default constructor
   lrfdUtility();

   // Prevent accidental copying and assignment
   lrfdUtility(const lrfdUtility&);
   lrfdUtility& operator=(const lrfdUtility&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_UTILITY_H_
