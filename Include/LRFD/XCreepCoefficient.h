///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2023  Washington State Department of Transportation
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

LOG
   rab : 03.16.1999 : Created file
*****************************************************************************/

class LRFDCLASS lrfdXCreepCoefficient : public WBFL::System::XBase
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
   lrfdXCreepCoefficient(const lrfdXCreepCoefficient& rOther) = default;

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdXCreepCoefficient() override;

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdXCreepCoefficient& operator = (const lrfdXCreepCoefficient& rOther) = default;

   // GROUP: OPERATIONS
   virtual void Throw() const override;
   virtual Int32 GetReason() const noexcept override;
   Reason GetReasonCode() const noexcept;

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
   virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG


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
