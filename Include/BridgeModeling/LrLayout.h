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

#ifndef INCLUDED_BRIDGEMODELING_LRLAYOUT_H_
#define INCLUDED_BRIDGEMODELING_LRLAYOUT_H_
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
class bmfGirder;
class bmfLrZone;
class matRebar;

// MISCELLANEOUS
//

// a struct to represent a rebar cut at a location

/*****************************************************************************
CLASS 
   bmfLrLayout

   This class defines the layout of longitudinal bars along a girder


DESCRIPTION
   This class defines longitudinal mild steel reinforcement in a girder. The
   steel is laid out into longitidinal zones along the girder which can then
   contain patterns (rows) of rebars.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.25.1999 : Created file
*****************************************************************************/

class BMFCLASS bmfLrLayout
{
public:

   // a useful data struct for describing rebar instances in 2d
   struct RebarInstance
   {
      RebarInstance(gpPoint2d loc, const matRebar* pmat, Float64 min_cut):
      m_Location(loc),
      m_pRebar(pmat),
      m_MinCutoffLength(min_cut)
      {
      }
   
      gpPoint2d       m_Location;
      const matRebar* m_pRebar;
      Float64         m_MinCutoffLength; // Distance from cut location
                                         // to nearest end of bar
   };
   typedef std::vector<RebarInstance> RebarInstanceList;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfLrLayout();

   //------------------------------------------------------------------------
   // Constructor with girder - layout must be associated with a girder before
   // it can be used. 
   bmfLrLayout(const bmfGirder* pGirder);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfLrLayout(const bmfLrLayout& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfLrLayout();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bmfLrLayout& operator = (const bmfLrLayout& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Get all of the rebars at a particular location along the girder.
   // NOTE: This list is temporary. don't expect it to be valid if the 
   // bridge model or girder is changed in any way.
   virtual RebarInstanceList GetRebarsAtCut(Float64 cutLocation) const;

   // GROUP: ACCESS
   //------------------------------------------------------------------------
   // Get the pointer to the girder that encloses this layout.
   // The pointer is used for callbacks to get lengths, etc.
   const bmfGirder* GetGirder() const;

   //------------------------------------------------------------------------
   // Set the pointer to the girder that encloses this layout.
   void SetGirder(const bmfGirder* pGirder);

   //------------------------------------------------------------------------
   // Get number of zones of lr along the girder
   virtual ZoneIndexType GetNumZones() const;

   //------------------------------------------------------------------------
   // Get a specific zone
   virtual bmfLrZone* GetZone(ZoneIndexType zoneNum) const;

   //------------------------------------------------------------------------
   // Add a zone. Returns the total number of zones after the add.
   // Takes ownership of pointer, so pointer must be on heap
   virtual ZoneIndexType AddZone(bmfLrZone* pZone);

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bmfLrLayout& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfLrLayout& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   const bmfGirder* m_pGirder;

   typedef boost::shared_ptr<bmfLrZone> ZonePtr;
   typedef std::vector<ZonePtr> ZoneVec;
   typedef ZoneVec::iterator ZoneVecIterator;
   typedef ZoneVec::const_iterator ZoneVecConstIterator;
   ZoneVec m_ZoneVec;

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

#endif // INCLUDED_BRIDGEMODELING_LRLAYOUT_H_
