///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2012  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODELING_LrSplicedGirderFlexiZONE_H_
#define INCLUDED_BRIDGEMODELING_LrSplicedGirderFlexiZONE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\SplicedGirder.h>
#include <BridgeModeling\lrFlexiZone.h>

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

class BMFCLASS bmfLrSplicedGirderFlexiZone : public bmfLrFlexiZone
{
public:

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   // class is useless until it gets a girder
   bmfLrSplicedGirderFlexiZone(SegmentIndexType segment);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfLrSplicedGirderFlexiZone(const bmfLrSplicedGirderFlexiZone& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfLrSplicedGirderFlexiZone();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bmfLrSplicedGirderFlexiZone& operator = (const bmfLrSplicedGirderFlexiZone& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // polymorphic cloning
   virtual bmfLrZone* CreateClone() const;

   //------------------------------------------------------------------------
   // Get location of zone. Measured from start of girder
   virtual void GetZoneLocation(Float64* zoneStart, Float64* zoneLength)const;

   //------------------------------------------------------------------------
   // Get location of zone. Measured from start of segment that reinforcment is in
   virtual void GetSegmentZoneLocation(Float64* zoneStart, Float64* zoneLength)const;

   //------------------------------------------------------------------------
   // Get segment that zone is contained in
   virtual SegmentIndexType GetSegment()const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Get the pointer to the spliced girder that encloses this zone.
   // The pointer is used for callbacks to get lengths, etc.
   const bmfSplicedGirder* GetSplicedGirder() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bmfLrSplicedGirderFlexiZone& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfLrSplicedGirderFlexiZone& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   SegmentIndexType m_Segment;

   // GROUP: LIFECYCLE

   bmfLrSplicedGirderFlexiZone();

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

#endif // INCLUDED_BRIDGEMODELING_LrSplicedGirderFlexiZONE_H_
