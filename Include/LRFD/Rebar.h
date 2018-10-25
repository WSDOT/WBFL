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

#ifndef INCLUDED_LRFD_REBAR_H_
#define INCLUDED_LRFD_REBAR_H_
#pragma once

// SYSTEM INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Material\Rebar.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdRebar

   Encapsulates constants and equations associated with rebar


DESCRIPTION
   Encapsulates constants and equations associated with rebar


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 12.31.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdRebar
{
public:
   // GROUP: ENUMERATIONS
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdRebar();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Calculates the maximum stress in the bursting zone per 5.10.10.1
   static Float64 GetMaxBurstingStress(Float64 fyRebar);

   //------------------------------------------------------------------------
   // Returns the distance from the ends of the girder within which the bursting
   // stress requirements must be checked. 5.10.10.1
   static Float64 GetBurstingZoneLength( Float64 girderHeight );

   //------------------------------------------------------------------------
   // Returns the minimum bar size in the confinment zone per 5.10.10.2
   // Bar size correlates to lrfdRebarPool
   static matRebar::Size GetMinConfinmentBarSize();

   //------------------------------------------------------------------------
   // Returns the minimum bar area in the confinment zone per 5.10.10.2
   static Float64 GetMaxConfinmentBarSpacing();

   //------------------------------------------------------------------------
   // Returns the minimum Av/S in the confinment zone per 5.10.10.2
   static Float64 GetMinConfinmentAvS();

   //------------------------------------------------------------------------
   // Returns the minimum av/s for detailing per 5.8.2.5
   static Float64 GetAvOverSMin(Float64 fc, Float64 bv, Float64 fy);

   //------------------------------------------------------------------------
   // Returns max barspacing for Vu over and under limits per 5.8.2.7
   static void GetMaxStirrupSpacing(Float64* sUnderLimit, Float64* sOverLimit);

   //------------------------------------------------------------------------
   // Returns max development length of a rebar in tension per 5.11.2.1.1
   // modification factors are not applied
   static Float64 GetTensileDevelopmentLength(const matRebar& rebar, Float64 fc);

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
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG
#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
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
   lrfdRebar();

   // Prevent accidental copying and assignment
   lrfdRebar(const lrfdRebar&);
   lrfdRebar& operator=(const lrfdRebar&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_REBAR_H_
