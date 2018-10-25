///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#if !defined INCLUDED_SYSTEM_NEXTAVAILABLEID_H_
#define INCLUDED_SYSTEM_NEXTAVAILABLEID_H_
#pragma once

#include <System\SysExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysNextAvailableId

   Manages a list of unique identifiers.

DESCRIPTION
   The NextAvailableId class manages a list of unique identifiers.  Objects of
   this type keep track of a which identifiers have been requested and which
   ones have been used.

IMPLENTATION NOTES
   This class uses a simple implementation at this point.  The basic idea of
   the implementation is to keep track of the highest requested number and
   treat it as used.  When the Int32 that is used in the implementation is about
   to overflow is when there is no more id's available.  Using numbers out
   of sequence results in a loss of available numbers.  Returned numbers are
   not recovered.

   In a future implementation, vectors of used, reserved, and available numbers
   are needed.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class SYSCLASS sysNextAvailableId
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   sysNextAvailableId();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysNextAvailableId(); 

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Reserves an id.  The id returned by this method will never be
   // used again until it is restored. If this object is out of unique
   // identifiers, an exception is thrown.
   //
   // <B>The excpetion throwning hasn't been implemented yet.  Do this
   // when the exception scheme is solidified.  Document the type of
   // exception thrown here.</B>
   Int32 ReserveNextId();

   //------------------------------------------------------------------------
   // Reserves a sequence of identifiers begining with <i>startId</i> and 
   // ending with <i>endId</i>.
   void ReserveSequence(Int32 startId,Int32 endId);

   //------------------------------------------------------------------------
   // Notify this object that you are using an id so that it can make sure
   // it does not reserve this same id.  There is no need to call this
   // method for ids returned from ReserveNextId(), though it is harmless to
   // do so. For identifiers not returned by ReserveNextId(), (roll your own
   // identifiers), be sure to call IsUsed() prior to marking an id as used.
   // In the debbuging version, this method will fail if <i>id</i> is already
   // in use.
   void UsingId(Int32 id);

   //------------------------------------------------------------------------
   // Returns an id to the list of available identifiers.
   void RestoreId(Int32 id);

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Returns the largest used identifier
   Int32 LargestedUsed() const;

   //------------------------------------------------------------------------
   // Returns true if <i>id</i> is currently in use.
   bool IsUsed(Int32 id) const;

   //------------------------------------------------------------------------
   // Returns true if there are still id's to be reserved.
   bool AreThereMore() const;

   //------------------------------------------------------------------------
   // Resets the counter back to zero
   void Reset();

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   //------------------------------------------------------------------------
   // See note for m_IdOverflowThreshold.
   Int32 m_NextAvailableId;

   //------------------------------------------------------------------------
   // Maximum value that m_NextAvailableId can take.  If the type of 
   // m_NextAvailableId changes, the type and value of this constant will
   // have to change as well.
   const Int32 m_IdOverflowThreshold; 

   // GROUP: LIFECYCLE
   sysNextAvailableId(const sysNextAvailableId& /*rNextAvailableId*/);               // Remove to enable copy

   // GROUP: OPERATORS
   sysNextAvailableId& operator = (const sysNextAvailableId& /*rNextAvailableId*/);  // Remove to enable assignment

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_SYSTEM_NEXTAVAILABLEID_H_
