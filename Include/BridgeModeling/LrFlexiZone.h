///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_BRIDGEMODELING_LRFLEXIZONE_H_
#define INCLUDED_BRIDGEMODELING_LRFLEXIZONE_H_
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
class bmfGirder;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfLrFlexiZone

   Zone of longitudinal rebar which can "flex" along the length of a
   girder. Length of layout is given as a factor (0-1.0) of the girder length.


DESCRIPTION
   Allows simple description of long. steel along length of girder. 

   

   Zone can be based on girder Start, Center, or End


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.26.1999 : Created file
*****************************************************************************/

class BMFCLASS bmfLrFlexiZone : public bmfLrZone
{
public:
   //------------------------------------------------------------------------
   // The zone can be justified (just like text) in any of the three following
   // ways along the length of the girder.
   enum ZoneJustification {Left, Center, Right};

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   // class is useless until it gets a girder
   bmfLrFlexiZone();

   //------------------------------------------------------------------------
   // Copy constructor
   bmfLrFlexiZone(const bmfLrFlexiZone& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfLrFlexiZone();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bmfLrFlexiZone& operator = (const bmfLrFlexiZone& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // polymorphic cloning
   virtual bmfLrZone* CreateClone() const;

   //------------------------------------------------------------------------
   // Get location of zone. Measured from start of girder
   virtual void GetZoneLocation(Float64* zoneStart, Float64* zoneLength)const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the justification of the zone along the length of the girder
   ZoneJustification GetZoneJustification() const;

   //------------------------------------------------------------------------
   // Set the justification of the zone along the length of the girder
   void SetZoneJustification(ZoneJustification just);

   //------------------------------------------------------------------------
   // Get the factor which describes the length of the zone. The length of the
   // zone = factor * GirderLength. and the factor can vary from (0.0-1.0)
   Float64 GetFactor() const;

   //------------------------------------------------------------------------
   // Get the factor which describes the length of the zone. The length of the
   // zone = factor * GirderLength. and the factor can vary from (0.0-1.0)
   void SetFactor(Float64 factor);

   //------------------------------------------------------------------------
   // Get the pointer to the girder that encloses this zone.
   // The pointer is used for callbacks to get lengths, etc.
   const bmfGirder* GetGirder() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bmfLrFlexiZone& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfLrFlexiZone& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64           m_Factor;
   ZoneJustification m_Justification;

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

#endif // INCLUDED_BRIDGEMODELING_LRFLEXIZONE_H_
