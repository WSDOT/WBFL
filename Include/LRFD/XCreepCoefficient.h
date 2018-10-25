///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_XCREEPCOEFFICIENT_H_
#define INCLUDED_LRFD_XCREEPCOEFFICIENT_H_
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
   lrfdXCreepCoefficient

   Exception object thrown when the lrfdCreepCoefficient class can't compute
   the creep coefficient.


DESCRIPTION
   Exception object thrown when the lrfdCreepCoefficient class can't compute
   the creep coefficient.  This will only occur when the V/S ratio exceeds the
   limit specified in the LRFD specification;


COPYRIGHT
   Copyright (c) 1997-1999
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 03.16.1999 : Created file
*****************************************************************************/

class LRFDCLASS lrfdXCreepCoefficient : public sysXBase
{
public:
   // GROUP: ENUMERATION
   enum Reason { VSRatio, Specification };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdXCreepCoefficient(Reason reason,
                    LPCTSTR file,
                    Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdXCreepCoefficient(const lrfdXCreepCoefficient& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdXCreepCoefficient();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdXCreepCoefficient& operator = (const lrfdXCreepCoefficient& rOther);

   // GROUP: OPERATIONS
   virtual void Throw() const;
   virtual Int32 GetReason() const;
   Reason GetReasonCode() const;

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

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdXCreepCoefficient& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const lrfdXCreepCoefficient& rOther);

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

#endif // INCLUDED_LRFD_XCREEPCOEFFICIENT_H_
