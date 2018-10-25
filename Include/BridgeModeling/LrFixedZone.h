///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEMODELING_LRFIXEDZONE_H_
#define INCLUDED_BRIDGEMODELING_LRFIXEDZONE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\lrZone.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfLrFixedZone

   Zone of longitudinal rebar which has fixed end points.


DESCRIPTION
   Allows simple description of long. steel along length of girder. 

COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.26.1999 : Created file
*****************************************************************************/

class BMFCLASS bmfLrFixedZone : public bmfLrZone
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   // class is useless until it gets a girder
   bmfLrFixedZone();

   //------------------------------------------------------------------------
   // Full constructor
   bmfLrFixedZone(Float64 startLocation, Float64 length);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfLrFixedZone(const bmfLrFixedZone& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfLrFixedZone();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bmfLrFixedZone& operator = (const bmfLrFixedZone& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // polymorphic cloning
   virtual bmfLrZone* CreateClone() const;

   //------------------------------------------------------------------------
   // Get location of zone. Measured from start of girder
   virtual void GetZoneLocation(Float64* zoneStart, Float64* zoneLength)const;

   //------------------------------------------------------------------------
   // Set location of zone. Measured from start of girder.
   // This class has no way of checking whether the zone is actually within a 
   // girder.
   void  SetZoneLocation(Float64 zoneStart, Float64 zoneLength);

   // GROUP: ACCESS


   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bmfLrFixedZone& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfLrFixedZone& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64   m_ZoneStart;
   Float64   m_ZoneLength;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_LRFIXEDZONE_H_
