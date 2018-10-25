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

#ifndef INCLUDED_LRFD_AUTOVERSION_H_
#define INCLUDED_LRFD_AUTOVERSION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Lrfd\VersionMgr.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdAutoVersion

   Automatic object used to reset specification version settings.


DESCRIPTION
   Automatic object used to reset specification version settings.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 12.03.1997 : Created file
*****************************************************************************/

class LRFDCLASS lrfdAutoVersion
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.
   // Sets version and units to the current version and units returned from
   // lrfdVersionMgr.
   lrfdAutoVersion();

   //------------------------------------------------------------------------
   lrfdAutoVersion(lrfdVersionMgr::Version v, lrfdVersionMgr::Units u);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdAutoVersion(const lrfdAutoVersion& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdAutoVersion();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdAutoVersion& operator = (const lrfdAutoVersion& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   //------------------------------------------------------------------------
   // Sets the spec version that will be set when this object is destroyed.
   void SetVersion(lrfdVersionMgr::Version v);

   //------------------------------------------------------------------------
   // Sets the spec units that will be set when this object is destroyed.
   void SetUnits(lrfdVersionMgr::Units u);

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
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdAutoVersion& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdAutoVersion& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   lrfdVersionMgr::Version m_Version;
   lrfdVersionMgr::Units   m_Units;

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

#endif // INCLUDED_LRFD_AUTOVERSION_H_
