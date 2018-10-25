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

#ifndef INCLUDED_BRIDGEMODELING_TRAFFICBARRIER_H_
#define INCLUDED_BRIDGEMODELING_TRAFFICBARRIER_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bmfTrafficBarrierTemplate;
class gmTrafficBarrier;
class gmSection;
class matConcreteEx;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfTrafficBarrier

   Represents a traffic barrier in a real bridge.


DESCRIPTION
   Represents a traffic barrier in a real bridge.  A basic traffic barrier
   (gmTrafficBarrier) is described by its cross section and material.
   The cross section is project along the length of the traffic barrier to make 
   it a prismatic solid.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.11.1998 : Created file
*****************************************************************************/

class BMFCLASS bmfTrafficBarrier
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfTrafficBarrier(const bmfTrafficBarrierTemplate* pTpl);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfTrafficBarrier(const bmfTrafficBarrier& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfTrafficBarrier();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bmfTrafficBarrier& operator = (const bmfTrafficBarrier& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   gmSection* CreateSection() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   std::_tstring GetName() const;

   //------------------------------------------------------------------------
   const gmTrafficBarrier* GetTrafficBarrierShape() const;

   //------------------------------------------------------------------------
   const matConcreteEx* GetConcrete() const;

   //------------------------------------------------------------------------
   const bmfTrafficBarrierTemplate* GetTemplate() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bmfTrafficBarrier& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const bmfTrafficBarrier& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   const bmfTrafficBarrierTemplate* m_pTpl;

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

#endif // INCLUDED_BRIDGEMODELING_TRAFFICBARRIER_H_
