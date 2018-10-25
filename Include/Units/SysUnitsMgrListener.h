///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_UNITS_SYSUNITSMGRLISTENER_H_
#define INCLUDED_UNITS_SYSUNITSMGRLISTENER_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Units\UnitsExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   unitSysUnitsMgrListener

   Listener class for unitsSysUnitsMgr.


DESCRIPTION
   Listener class for unitsSysUnitsMgr.

LOG
   rab : 12.09.1997 : Created file
*****************************************************************************/

class UNITSCLASS unitSysUnitsMgrListener
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   unitSysUnitsMgrListener();

   //------------------------------------------------------------------------
   // Copy constructor
   unitSysUnitsMgrListener(const unitSysUnitsMgrListener& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~unitSysUnitsMgrListener();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   unitSysUnitsMgrListener& operator = (const unitSysUnitsMgrListener& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual void OnRegistered();

   //------------------------------------------------------------------------
   virtual void OnUnregistered();

   //------------------------------------------------------------------------
   virtual void OnUpdate();

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
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_UNITS_SYSUNITSMGRLISTENER_H_
