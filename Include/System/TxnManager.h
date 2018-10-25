///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#ifndef INCLUDED_SYSTEM_TXNMANAGER_H_
#define INCLUDED_SYSTEM_TXNMANAGER_H_
#pragma once

// SYSTEM INCLUDES
//
#include <System\SysExp.h>
#include <System\Transaction.h>
#include <System\SingletonKiller.h>
#include <boost\shared_ptr.hpp>
#include <list>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//


/*****************************************************************************
CLASS 
   txnTxnManager

   Transaction Manager - manages Undo/Redo/Repeat

DESCRIPTION
   Manages transactions.  A transaction is a unit of change to an object.
   See The Windows Interface Guidelines for Software Design pg 64.

   This class is responsible for maintaining a transaction and undo history,
   as well as providing command update services for Undo/Redo/Repeat.

   An application should have only one Transaction Manager. The Singleton
   pattern is used to manage this.

KEYWORDS
   txnTransaction, txnMacroTxn

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class SYSCLASS txnTxnManager
{
   enum Mode {RepeatMode,RedoMode};

public:
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Executes a transaction.
   // A copy of this transaction is made using CreateClone()
   void Execute(txnTransaction& rTxn);

   //------------------------------------------------------------------------
   // Executes a transaction.
   // The transaction manager assumes ownership of pTxn and will
   // delete it when it is no longer needed.
   void Execute(txnTransaction* pTxn);

   //------------------------------------------------------------------------
   // Undoes the last undoable transaction
   void Undo();

   //------------------------------------------------------------------------
   // Executes the last undone transaction
   void Redo();

   //------------------------------------------------------------------------
   // Repeats the last transaction
   void Repeat();

   //------------------------------------------------------------------------
   // Returns true if there is a transaction to be undone
   bool CanUndo() const;

   //------------------------------------------------------------------------
   // Returns true if there is a transaction to be redone
   bool CanRedo() const;

   //------------------------------------------------------------------------
   // Returns true if there is a transaction to be repeated
   bool CanRepeat() const;

   //------------------------------------------------------------------------
   // Returns the name of the transaction to be undone
   std::_tstring UndoName() const;

   //------------------------------------------------------------------------
   // Returns the name of the transaction to be redone
   std::_tstring RedoName() const;

   //------------------------------------------------------------------------
   // Returns the name of the transaction to be repeated
   std::_tstring RepeatName() const;

   //------------------------------------------------------------------------
   // Returns the number of executed transactions
   CollectionIndexType GetTxnCount() const;

   //------------------------------------------------------------------------
   // Returns the number of transactions that have been undone.
   CollectionIndexType GetUndoCount() const;

   //------------------------------------------------------------------------
   // Writes a log of all the transactions that have been done to a
   // standard ostream.
   void WriteTransactionLog(std::_tostream& os) const;

   //------------------------------------------------------------------------
   // Clears the list of all transactions that have been done
   void ClearTxnHistory();

   //------------------------------------------------------------------------
   // Clears the list of all transactions that have been undone
   void ClearUndoHistory();

   //------------------------------------------------------------------------
   // Clears both the transaction and undo histories.
   void Clear();

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns a pointer to the only instance of the transaction manager
   static txnTxnManager* GetInstance();

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Returns true if the Transaction manager is in report mode.  It is
   // useful to know this mode so the Repeat/Redo item on the edit menu
   // can have the correct text.
   bool IsRepeatMode() const {return m_Mode == RepeatMode;}

   //------------------------------------------------------------------------
   // Returns true if the Transaction manager is in redo mode.  It is
   // useful to know this mode so the Repeat/Redo item on the edit menu
   // can have the correct text.
   bool IsRedoMode()   const {return m_Mode == RedoMode;  }

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Called by WriteTransactionLog() just before the log is written. This
   // method does nothing by default.  Derived classes can override this
   // to provide application specific information.
   virtual void WriteLogIntroduction(std::_tostream& os) const;

   //------------------------------------------------------------------------
   // Called by WriteTransactionLog() immediatly after the log is written.
   // This method does nothing by default.  Derived classes can override this
   // to provide application specific information.
   virtual void WriteLogConclusion(std::_tostream& os) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   typedef boost::shared_ptr<txnTransaction> TxnItem;
   typedef std::list<TxnItem> TxnContainer;
   typedef TxnContainer::iterator TxnIterator;
   typedef TxnContainer::reverse_iterator TxnReverseIterator;
   typedef TxnContainer::const_iterator TxnConstIterator;
   typedef TxnContainer::const_reverse_iterator TxnConstReverseIterator;

   TxnContainer m_TxnHistory;   // Txn that have been executed
   TxnContainer m_UndoHistory;  // Txn that have been undone
   static sysSingletonKillerT<txnTxnManager> ms_Killer;

   static txnTxnManager* ms_pInstance;
   friend sysSingletonKillerT<txnTxnManager>;

   Mode m_Mode;

   // GROUP: LIFECYCLE
   txnTxnManager();
   txnTxnManager(const txnTxnManager& /*rOther*/);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~txnTxnManager(); 

   // GROUP: OPERATORS
   txnTxnManager& operator = (const txnTxnManager& /*rOther*/);

   TxnItem FindFirstUndoableTxn() const;
   TxnItem FindFirstUndoableTxn(bool bRemoveFromHistory);

   //// Returns the first undoable transaction.  This transaction is
   //// removed from the m_TxnHistory container.  The returned pointer
   //// is un-owned.
   //txnTransaction* GetFirstUndoableTxn();

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

#endif // INCLUDED_SYSTEM_TXNMANAGER_H_
