///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODELING_LRZONE_H_
#define INCLUDED_BRIDGEMODELING_LRZONE_H_
#pragma once

// SYSTEM INCLUDES
//
#include <boost\shared_ptr.hpp>

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bmfLrPattern;
class bmfLrLayout;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfLrZone

   Describes a  segment along a girder which contains longitudinal
   reinforcement. The reinforcement in a zone is constant along its length.


DESCRIPTION
   A zone can have multiple Patterns of reinforcement (e.g., rows) in it. 


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.25.1999 : Created file
*****************************************************************************/

class BMFCLASS bmfLrZone
{
public:
   friend bmfLrLayout;
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor. Zone of zero length that starts at zero.
   // Zone is pretty much useless until it is added to a Layout.
   bmfLrZone();

   //------------------------------------------------------------------------
   // Copy constructor
   bmfLrZone(const bmfLrZone& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfLrZone();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bmfLrZone& operator = (const bmfLrZone& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // polymorphic cloning
   virtual bmfLrZone* CreateClone() const=0;

   //------------------------------------------------------------------------
   // Does location lie within zone? If so, nearest gives the distance
   // to the closest zone boundary. 
   virtual bool IsInZone(Float64 testLoc, Float64* nearest);

   // GROUP: ACCESS
   //------------------------------------------------------------------------
   // Get the layout that this zone belongs to
   const bmfLrLayout* GetLayout() const;

   //------------------------------------------------------------------------
   // Get location of zone. Measured from start of girder
   virtual void GetZoneLocation(Float64* zoneStart, Float64* zoneLength)const=0;

   //------------------------------------------------------------------------
   // Get number of patterns in zone
   CollectionIndexType GetNumPatterns() const;

   //------------------------------------------------------------------------
   // Get a pointer to the ith pattern - zero based index
   bmfLrPattern* GetPattern(CollectionIndexType idx);

   //------------------------------------------------------------------------
   // Add a new pattern - returns the number of patterns added thusfar.
   // Takes ownership of the pattern
   CollectionIndexType AddPattern( bmfLrPattern* pPattern);

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bmfLrZone& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const bmfLrZone& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // our layout
   const  bmfLrLayout* m_pLayout;

   // vector of patterns
   typedef boost::shared_ptr<bmfLrPattern> PatternPtr;
   typedef std::vector<PatternPtr> PatternVec;
   typedef PatternVec::iterator PatternVecIterator;
   typedef PatternVec::const_iterator PatternVecConstIterator;
   PatternVec m_PatternVec;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Set the layout that this zone belongs to. This is typically done by the 
   // layout when the zone is added.
   void SetLayout(const  bmfLrLayout* pLay);

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

#endif // INCLUDED_BRIDGEMODELING_LRZONE_H_
