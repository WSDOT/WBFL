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

#ifndef INCLUDED_LRFD_XSHEAR_H_
#define INCLUDED_LRFD_XSHEAR_H_
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
   lrfdXShear

   Exception object thrown when the lrfdShear class encounters an exceptional
   condition.


DESCRIPTION
   Exception object thrown when the lrfdShear class encounters an exceptional
   condition.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 02.04.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdXShear : public sysXBase
{
public:
   // GROUP: ENUMERATION
   enum Reason { vfcOutOfRange,  // v/fc > 0.25. A bigger section is needed
                 MaxIterExceeded, // The maximum number of iterations was
                                  // exceeded before a solution was found
                 StrainOutOfRange // The strain computed by eq'n 5.8.3.4.2-2, 
                                  // adjusted by eq'n 5.8.3.4.2-3, is out of 
                                  // the range supported by Figure 5.8.3.4.2-1
                                  // and Table 5.8.3.4.2-1
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdXShear(Reason reason,
              LPCTSTR file,
              Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdXShear(const lrfdXShear& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdXShear();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdXShear& operator = (const lrfdXShear& rOther);

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
   void MakeCopy(const lrfdXShear& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdXShear& rOther);

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

#endif // INCLUDED_LRFD_XSHEAR_H_
