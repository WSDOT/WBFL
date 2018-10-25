///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODELING_LRPATTERN_H_
#define INCLUDED_BRIDGEMODELING_LRPATTERN_H_
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
class matRebar;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfLrPattern

   Abstract class to Define a pattern of rebars in a cross section. An
   example would be a row of rebars


DESCRIPTION
   Abstract class to Define a pattern of rebars in a cross section. An
   example would be a row of rebars


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.26.1999 : Created file
*****************************************************************************/

class BMFCLASS bmfLrPattern
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfLrPattern();

   //------------------------------------------------------------------------
   // Default constructor
   // NOTE: this class must have a valid matRebar* in order to work properly.
   bmfLrPattern(const matRebar* pRebar);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfLrPattern();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // polymorphic cloning
   virtual bmfLrPattern* CreateClone() const=0;

   //------------------------------------------------------------------------
   // Get number of bars in pattern
   virtual Uint32 GetNumBars() const = 0;

   //------------------------------------------------------------------------
   // Get the ith bar location. zero-based
   virtual gpPoint2d GetBarLocation(Uint32 barNum) const=0;

   //------------------------------------------------------------------------
   // Get the rebar material for all bars used in pattern
   virtual const matRebar* GetRebar() const;

   //------------------------------------------------------------------------
   // Set the rebar material for all bars used in pattern. It is assumed that
   // the pointer is owned elsewhere and its scope transcends this class.
   virtual void SetRebar(const matRebar* pRebar);

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // pointer to rebar material
   const matRebar* m_pRebar;

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

#endif // INCLUDED_BRIDGEMODELING_LRPATTERN_H_
