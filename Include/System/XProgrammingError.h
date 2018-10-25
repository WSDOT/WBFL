///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#ifndef INCLUDED_SYSTEM_XPROGRAMMINGERROR_H_
#define INCLUDED_SYSTEM_XPROGRAMMINGERROR_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <System\SysExp.h>
#include <System\Exception.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysXProgrammingError

   A programming error exception thrown when a programming error is
   encountered.


DESCRIPTION
   A programming error exception thrown when a programming error is
   encountered.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.21.1997 : Created file
*****************************************************************************/

class SYSCLASS sysXProgrammingError : public sysXBase
{
public:
   // GROUP: ENUMERATIONS
   enum Reason { CodeFault,        // There is an error in the source code,
                 InvalidValue,     // A valid is inavlid
                 ValueOutOfRange,  // A value was out of a required range
                 NotImplemented,   // A code segment is not implemented
                 AssertValidFailed // A call to AssertValid() failed
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   sysXProgrammingError(Reason reason, const char* file, Int32 line);

   //------------------------------------------------------------------------
   // Copy constructor
   sysXProgrammingError(const sysXProgrammingError& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysXProgrammingError();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   sysXProgrammingError& operator = (const sysXProgrammingError& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void Throw() const;

   //------------------------------------------------------------------------
   Int32 GetReason() const;

   //------------------------------------------------------------------------
   Reason GetReasonCode() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const sysXProgrammingError& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const sysXProgrammingError& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Reason m_Reason;

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

#endif // INCLUDED_SYSTEM_PROGRAMMINGERROR_H_
