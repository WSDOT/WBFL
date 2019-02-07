///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2019  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_MACROTXN_H_
#define INCLUDED_SYSTEM_MACROTXN_H_
#pragma once

#include <System\SysExp.h>
#include <System\Transaction.h>

#include <memory>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   txnMacroTxn

   A macro transaction

DESCRIPTION
   A macro transaction is a collection of other transactions.

KEYWORDS
   txnTransaction, txnTxnManager
*****************************************************************************/

class SYSCLASS txnMacroTxn : public txnTransaction
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   txnMacroTxn();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~txnMacroTxn(); 

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Executes all the transactions that make up the macro, in the order
   // in which they were added to the macro.
   bool Execute();

   //------------------------------------------------------------------------
   // Calls Undo() for every transaction in the macros, in the reverse order
   // in which they were added to the macro.
   void Undo();

   //------------------------------------------------------------------------
   // Returns the name of the macro
   std::_tstring Name() const;
   
   //------------------------------------------------------------------------
   // Assigns a name to the macro
   void Name(const std::_tstring& name);

   //------------------------------------------------------------------------
   // Returns a pointer to a copy of the transaction
   txnTransaction* CreateClone() const;

   //------------------------------------------------------------------------
   // Writes all transactions in this macro to the log.
   void Log(std::_tostream& os) const;

   //------------------------------------------------------------------------
   // Adds a transaction to the macro.  The transaction is cloned.
   void AddTransaction(txnTransaction& rTxn);

   //------------------------------------------------------------------------
   // Adds a transaction to the macro. The transaction is not cloned.
   // The macro assumes responsibility for deleting the transactions.
   void AddTransaction(txnTransaction* pTxn);

   // GROUP: ACCESS

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Returns true if all of the transactions in the macro are undoable.
   bool IsUndoable();

   //------------------------------------------------------------------------
   // Returns true if all of the transactions in the macro are repeatable.
   bool IsRepeatable();

   //------------------------------------------------------------------------
   // Returns the number of transactions in the macro.
   CollectionIndexType GetTxnCount();

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   #pragma warning(disable:4251)
   std::_tstring m_Name;
   typedef std::shared_ptr<txnTransaction> TransactionPtr;
   typedef std::vector<TransactionPtr> TxnContainer;
   typedef TxnContainer::iterator TxnIterator;
   typedef TxnContainer::const_iterator TxnConstIterator;
   typedef TxnContainer::reverse_iterator TxnReverseIterator;

   TxnContainer m_Transactions;

private:
   // GROUP: LIFECYCLE
   txnMacroTxn(const txnMacroTxn& /*rOther*/);               // Remove to enable copy

   // GROUP: OPERATORS
   txnMacroTxn& operator = (const txnMacroTxn& /*rOther*/);  // Remove to enable assignment

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

#endif // INCLUDED_SYSTEM_MACROTXN_H_
