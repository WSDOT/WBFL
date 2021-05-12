///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_ISTRUCTUREDSAVE_H_
#define INCLUDED_SYSTEM_ISTRUCTUREDSAVE_H_
#pragma once

#include <System\SysExp.h>
#include <System\XStructuredSave.h>

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysIStructuredSave

   Pure interface class for saving structured data to a data source.


DESCRIPTION
   Pure interface class for saving structured data to a data source.
   This class was based on an article by Neil Hunt of Rational Corp.
   call Unit Testing. The class is certainly useful for more than
   unit testing.

LOG
   rdp : 07.10.1998 : Created file
*****************************************************************************/

class SYSCLASS sysIStructuredSave
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   virtual ~sysIStructuredSave() {}

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Mark the Beginning of a structured data chunk. This call must be always
   // balanced by a corresponding call to EndUnit. An optional version number
   // may be used to tag major units.
   virtual void BeginUnit(LPCTSTR name, Float64 version=0) = 0;

   //------------------------------------------------------------------------
   // Mark the end of a structured data chunk that was started by a call to 
   // BeginUnit.
   virtual void EndUnit() = 0;

   //------------------------------------------------------------------------
   // Get the version number of the current unit
   virtual Float64 GetVersion() = 0;

   //------------------------------------------------------------------------
   // Get the version number of the top-most unit
   virtual Float64 GetTopVersion() = 0;

   //------------------------------------------------------------------------
   // Write a string property
   virtual void Property(LPCTSTR name, LPCTSTR value) = 0;

   //------------------------------------------------------------------------
   // Write a real number property
   virtual void Property(LPCTSTR name, Float64 value) = 0;

   //------------------------------------------------------------------------
   // Write an integral property
   virtual void Property(LPCTSTR name, Int16 value) = 0;

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, Uint16 value) = 0;

   //------------------------------------------------------------------------
   // Write an integral property
   virtual void Property(LPCTSTR name, Int32 value) = 0;

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, Uint32 value) = 0;

   //------------------------------------------------------------------------
   // Write an integral property
   virtual void Property(LPCTSTR name, Int64 value) = 0;

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, Uint64 value) = 0;

   //------------------------------------------------------------------------
   // Write an integral property
   virtual void Property(LPCTSTR name, LONG value) = 0;

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, ULONG value) = 0;

   //------------------------------------------------------------------------
   // Write a bool property
   virtual void Property(LPCTSTR name, bool value) = 0;

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
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_SYSTEM_ISTRUCTUREDSAVE_H_
