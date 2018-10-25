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

#ifndef INCLUDED_BRIDGEMODELING_TRAFFICBARRIERTEMPLATE_H_
#define INCLUDED_BRIDGEMODELING_TRAFFICBARRIERTEMPLATE_H_
#pragma once

// SYSTEM INCLUDES
//
#include <string>

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gmTrafficBarrier;
class matConcreteEx;
class bmfTrafficBarrier;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfTrafficBarrierTemplate

   Describes the general layout of a traffic barrier.


DESCRIPTION
   Describes the general layout of a traffic barrier.  A basic traffic barrier
   (gmTrafficBarreri) is described by its cross section and material.
   The cross section is project along the length of the traffic barrier to make 
   it a prismatic solid.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.11.1998 : Created file
*****************************************************************************/

class BMFCLASS bmfTrafficBarrierTemplate
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfTrafficBarrierTemplate(const std::_tstring& name,
                             const gmTrafficBarrier* pTB,
                             const matConcreteEx* pConc);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfTrafficBarrierTemplate(const bmfTrafficBarrierTemplate& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfTrafficBarrierTemplate();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bmfTrafficBarrierTemplate& operator = (const bmfTrafficBarrierTemplate& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   bmfTrafficBarrier* CreateTrafficBarrier() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetName(const std::_tstring& name);

   //------------------------------------------------------------------------
   std::_tstring GetName() const;

   //------------------------------------------------------------------------
   void SetTrafficBarrierShape(const gmTrafficBarrier* pTB);

   //------------------------------------------------------------------------
   const gmTrafficBarrier* GetTrafficBarrierShape();

   //------------------------------------------------------------------------
   const gmTrafficBarrier* GetTrafficBarrierShape() const;

   //------------------------------------------------------------------------
   void SetConcrete(const matConcreteEx* pConc);

   //------------------------------------------------------------------------
   const matConcreteEx* GetConcrete();

   //------------------------------------------------------------------------
   const matConcreteEx* GetConcrete() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bmfTrafficBarrierTemplate& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const bmfTrafficBarrierTemplate& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::_tstring m_Name;
   const gmTrafficBarrier* m_pTB;
   const matConcreteEx* m_pConc;

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

#endif // INCLUDED_BRIDGEMODELING_TRAFFICBARRIERTEMPLATE_H_
