///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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

#ifndef INCLUDED_UNITS_XUNIT_H_
#define INCLUDED_UNITS_XUNIT_H_
#pragma once

#include <Units\UnitsExp.h>
#include <System\Exception.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   unitXUnit

   Unit system exception.


DESCRIPTION
   Unit system exception.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.21.1997 : Created file
*****************************************************************************/

class UNITSCLASS unitXUnit : public sysXBase
{
public:
   // GROUP: ENUMERATIONS
   enum Reason { BadStationFormat };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   unitXUnit(Reason reason,LPCTSTR file,Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   unitXUnit(const unitXUnit& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~unitXUnit();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   unitXUnit& operator = (const unitXUnit& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   virtual void Throw() const;
   virtual Int32 GetReason() const;
   Reason GetReasonCode() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const unitXUnit& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const unitXUnit& rOther);

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

#endif // INCLUDED_UNITS_XUNIT_H_
