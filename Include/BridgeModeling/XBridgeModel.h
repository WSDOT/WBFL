///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright � 1999-2022  Washington State Department of Transportation
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


#ifndef INCLUDED_BRIDGEMODELING_XBRIDGEMODEL_H_
#define INCLUDED_BRIDGEMODELING_XBRIDGEMODEL_H_
#pragma once


// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <System\Exception.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfXBridgeModel

   Bridge Modeling Framework exception class.


DESCRIPTION
   Bridge Modeling Framework exception class.  Objects of this type are
   thrown when exceptional conditions arrise in the Bridge Modeling Package.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class BMFCLASS bmfXBridgeModel : public sysXBase
{
public:
   // GROUP: ENUMERATIONS

   //------------------------------------------------------------------------
   enum Reason { Unknown,
                 PoolEntryNotFound
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor.
   bmfXBridgeModel(Reason reason,
                   LPCTSTR file,
                   Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfXBridgeModel(const bmfXBridgeModel& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfXBridgeModel();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bmfXBridgeModel& operator = (const bmfXBridgeModel& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   void Throw() const;

   //------------------------------------------------------------------------
   // Returns the reason the exception was thrown.
   Int32 GetReason() const;

   //------------------------------------------------------------------------
   // Returns the reason the exception was thrown.
   Reason GetReasonCode() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Reason      m_Reason;

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

#endif // INCLUDED_BRIDGEMODELING_XBRIDGEMODEL_H_
