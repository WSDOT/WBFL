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

#ifndef INCLUDED_SYSTEM_TRANSACTION_H_
#define INCLUDED_SYSTEM_TRANSACTION_H_
#pragma once

#include <string>
#include <System\SysExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   txnTransaction

   Encapsulates a transaction

DESCRIPTION
   A transaction is a unit of change in the system.

KEYWORDS
   txnTxnManager, txnMacroTxn

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class SYSCLASS txnTransaction
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default Constructor
   txnTransaction();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~txnTransaction(); 

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Causes the transaction to execute
   //
   // Returns true if the transaction executes sucessfully
   virtual bool Execute();

   //------------------------------------------------------------------------
   // Causes the transaction to undo itself
   virtual void Undo();

   //------------------------------------------------------------------------
   // Creates a copy of the transaction
   //
   // Returns a pointer to the clone
   virtual txnTransaction* CreateClone() const = 0;

   //------------------------------------------------------------------------
   // Writes the name of the transaction to a stream
   virtual void Log(std::ostream& os) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the name of the transaction. This is useful for Undo/Redo menu
   // commands.
   virtual std::string Name() const = 0;

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Returns true if the transaction can be undone
   virtual bool IsUndoable();

   //------------------------------------------------------------------------
   // Returns true if the transaction can be repeated
   virtual bool IsRepeatable();

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
   txnTransaction(const txnTransaction& /*rOther*/); 

   // GROUP: OPERATORS
   txnTransaction& operator = (const txnTransaction& /*rOther*/);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
#if defined _DEBUG
public:
   bool AssertValid() const;
   void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
public:
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_SYSTEM_TRANSACTION_H_
