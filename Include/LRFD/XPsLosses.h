///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_XPSLOSSES_H_
#define INCLUDED_LRFD_XPSLOSSES_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <System\Exception.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdXPsLosses

   Exception object thrown when the lrfdPsLosses class encounters an exceptional
   condition.


DESCRIPTION
   Exception object thrown when the lrfdPsLosses class encounters an exceptional
   condition.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.31.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdXPsLosses : public sysXBase
{
public:
   // GROUP: ENUMERATION

   //------------------------------------------------------------------------
   enum Reason { fpjOutOfRange,   // The jacking stress, fpj does not exceed
                                  // 0.5fpu. (See 5.9.5.4.4b)
                 fcOutOfRange,    // 28MPa(4KSI) <= f'c <= 70MPa(10KSI)
                 Specification,   // wrong specification version
                 StrandType,      // wrong stand type
                 Unknown };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdXPsLosses(Reason reason,
                 LPCTSTR file,
                 Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdXPsLosses(const lrfdXPsLosses& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdXPsLosses();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdXPsLosses& operator = (const lrfdXPsLosses& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual void Throw() const;

   //------------------------------------------------------------------------
   virtual Int32 GetReason() const;

   //------------------------------------------------------------------------
   Reason GetReasonCode() const;

   // GROUP: ACCESS

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the class is in a valid state, otherwise returns
   // false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdXPsLosses& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const lrfdXPsLosses& rOther);

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

#endif // INCLUDED_LRFD_XPSLOSSES_H_
