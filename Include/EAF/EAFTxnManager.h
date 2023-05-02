///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

#pragma once

#include <EAF\EAFExp.h>
#include <EAF\EAFTransaction.h>

#include <list>

class CEAFTxnManager;

/// Abstract interface for a transaction manager factory. 
/// Implementations of this interface use the abstract factory pattern
/// to create application specific transcation managers
class EAFCLASS CEAFTxnManagerFactory
{
public:
   virtual std::unique_ptr<CEAFTxnManager> CreateTransactionManager() = 0;
};

/// Manages transactions.  A transaction is a unit of change to an object.
/// See The Windows Interface Guidelines for Software Design pg 64.
///
/// This class is responsible for maintaining a transaction and undo history,
/// as well as providing command update services for Undo/Redo/Repeat.
///
/// An application should have only one Transaction Manager. The Singleton
/// pattern is used to manage this.
class EAFCLASS CEAFTxnManager
{
public:
   CEAFTxnManager() = default;
   virtual ~CEAFTxnManager() = default;

   CEAFTxnManager(const CEAFTxnManager&) = delete;
   CEAFTxnManager& operator=(const CEAFTxnManager&) = delete;

   /// Executes a transaction.
   /// A copy of this transaction is made using CreateClone()
   /// The cloned transaction is maintained in the transaction history
   /// and will be used for Undo/Redo/Repeat if permitted
   virtual void Execute(CEAFTransaction& rTxn);

   /// Executes a transaction.
   /// The transaction is maintained in the transaction history
   /// and will be used for Undo/Redo/Repeat if permitted
   virtual void Execute(std::unique_ptr<CEAFTransaction>&& pTxn);

   /// Undoes the last undoable transaction
   virtual void Undo();

   /// Executes the last undone transaction
   virtual void Redo();

   /// Repeats the last transaction
   virtual void Repeat();

   /// Returns true if there is a transaction to be undone
   virtual bool CanUndo() const;

   /// Returns true if there is a transaction to be redone
   virtual bool CanRedo() const;

   /// Returns true if there is a transaction to be repeated
   virtual bool CanRepeat() const;

   /// Returns the name of the transaction to be undone
   virtual std::_tstring UndoName() const;

   /// Returns the name of the transaction to be redone
   virtual std::_tstring RedoName() const;

   /// Returns the name of the transaction to be repeated
   virtual std::_tstring RepeatName() const;

   /// Returns the number of executed transactions
   virtual IndexType GetTxnCount() const;

   /// Returns the number of transactions that have been undone.
   virtual IndexType GetUndoCount() const;

   /// Writes a log of all the transactions that have been done to a standard ostream.
   virtual void WriteTransactionLog(std::_tostream& os) const;

   /// Clears the list of all transactions that have been done
   virtual void ClearTxnHistory();

   /// Clears the list of all transactions that have been undone
   virtual void ClearUndoHistory();

   /// Clears both the transaction and undo histories.
   virtual void Clear();

   /// Sets the transaction manager factory. Call this before any calls
   /// to GetInstance to create a custom transaction manager
   static void SetTransactionManagerFactory(std::unique_ptr<CEAFTxnManagerFactory>&& pFactory);

   /// Returns a pointer to the only instance of the transaction manager
   static std::unique_ptr<CEAFTxnManager>& GetInstance();

   /// Returns true if the Transaction manager is in report mode.  It is
   /// useful to know this mode so the Repeat/Redo item on the edit menu
   /// can have the correct text.
   virtual bool IsRepeatMode() const {return m_Mode == Mode::Repeat;}

   /// Returns true if the Transaction manager is in redo mode.  It is
   /// useful to know this mode so the Repeat/Redo item on the edit menu
   /// can have the correct text.
   virtual bool IsRedoMode()   const {return m_Mode == Mode::Redo;  }

protected:
   enum class Mode { Repeat, Redo };

   /// Called by WriteTransactionLog() just before the log is written. This
   /// method does nothing by default.  Derived classes can override this
   /// to provide application specific information.
   virtual void WriteLogIntroduction(std::_tostream& os) const;

   /// Called by WriteTransactionLog() immediatly after the log is written.
   /// This method does nothing by default.  Derived classes can override this
   /// to provide application specific information.
   virtual void WriteLogConclusion(std::_tostream& os) const;

protected:
   using TxnContainer = std::list<std::unique_ptr<CEAFTransaction>>;

   TxnContainer m_TxnHistory;   // Txn that have been executed
   TxnContainer m_UndoHistory;  // Txn that have been undone

   static std::unique_ptr<CEAFTxnManagerFactory> ms_pFactory;
   static std::unique_ptr<CEAFTxnManager> ms_pInstance;

   Mode m_Mode{ Mode::Repeat };

   TxnContainer::iterator FindFirstUndoableTxn();
   TxnContainer::const_iterator FindFirstUndoableTxn() const;

#if defined _DEBUG
public:
   bool AssertValid() const;
   void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
public:
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
};
