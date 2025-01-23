///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

/// @brief Abstract interface for a transaction manager factory. 
/// Implementations of this interface use the abstract factory pattern
/// to create application specific transcation managers
class EAFCLASS CEAFTxnManagerFactory
{
public:
   virtual std::unique_ptr<CEAFTxnManager> CreateTransactionManager() = 0;
};

/// @brief Manages transactions.  A transaction is a unit of change to an object.
/// See The Windows Interface Guidelines for Software Design pg 64.
///
/// This class is responsible for maintaining a transaction and undo history,
/// as well as providing command update services for Undo/Redo/Repeat.
///
/// An application should have only one Transaction Manager. The Singleton
/// pattern is used to manage this.
/// 
/// A customized transaction manager may be define through inheritance. The transaction manager
/// is a global resource object and the EAF framework gains access to it by calling CEAFTxnManager::GetInstance().
/// CEAFTxnManager::SetTransactionManagerFactory() must be called prior to the first call to CEAFTxnManager::GetInstance()
/// for your custom transaction manager to be instantiated.
class EAFCLASS CEAFTxnManager
{
public:
   CEAFTxnManager() = default;
   virtual ~CEAFTxnManager() = default;

   CEAFTxnManager(const CEAFTxnManager&) = delete;
   CEAFTxnManager& operator=(const CEAFTxnManager&) = delete;

   /// @brief Executes a transaction.
   /// A copy of this transaction is made using CreateClone()
   /// The cloned transaction is maintained in the transaction history
   /// and will be used for Undo/Redo/Repeat if permitted
   virtual void Execute(const CEAFTransaction& rTxn);

   /// @brief Executes a transaction.
   /// The transaction is maintained in the transaction history
   /// and will be used for Undo/Redo/Repeat if permitted
   virtual void Execute(std::unique_ptr<CEAFTransaction>&& pTxn);

   ///@brief  Undoes the last undoable transaction
   virtual void Undo();

   /// @brief Executes the last undone transaction
   virtual void Redo();

   /// @brief Repeats the last transaction
   virtual void Repeat();

   /// @brief Returns true if there is a transaction to be undone
   virtual bool CanUndo() const;

   /// @brief Returns true if there is a transaction to be redone
   virtual bool CanRedo() const;

   /// @brief Returns true if there is a transaction to be repeated
   virtual bool CanRepeat() const;

   /// @brief Returns the name of the transaction to be undone
   virtual std::_tstring UndoName() const;

   /// @brief Returns the name of the transaction to be redone
   virtual std::_tstring RedoName() const;

   /// @brief Returns the name of the transaction to be repeated
   virtual std::_tstring RepeatName() const;

   /// @brief Returns the number of executed transactions
   virtual IndexType GetTxnCount() const;

   /// @brief Returns the number of transactions that have been undone.
   virtual IndexType GetUndoCount() const;

   /// @brief Writes a log of all the transactions that have been done to a standard ostream.
   virtual void WriteTransactionLog(std::_tostream& os) const;

   /// @brief Clears the list of all transactions that have been done
   virtual void ClearTxnHistory();

   /// @brief Clears the list of all transactions that have been undone
   virtual void ClearUndoHistory();

   /// @brief Clears both the transaction and undo histories.
   virtual void Clear();

   /// @brief Sets the transaction manager factory. Call this before any calls
   /// to GetInstance to create a custom transaction manager
   static void SetTransactionManagerFactory(std::unique_ptr<CEAFTxnManagerFactory>&& pFactory);

   /// @brief Returns the only instance of the transaction manager
   static CEAFTxnManager& GetInstance();

   /// @brief Returns true if the Transaction manager is in repeat mode.  It is
   /// useful to know this mode so the Repeat/Redo item on the edit menu
   /// can have the correct text.
   virtual bool IsRepeatMode() const {return m_Mode == Mode::Repeat;}

   /// @brief Returns true if the Transaction manager is in redo mode.  It is
   /// useful to know this mode so the Repeat/Redo item on the edit menu
   /// can have the correct text.
   virtual bool IsRedoMode()   const {return m_Mode == Mode::Redo;  }

protected:
   enum class Mode { Repeat, Redo };

   /// @brief Called by WriteTransactionLog() just before the log is written. This
   /// method does nothing by default.  Derived classes can override this
   /// to provide application specific information.
   virtual void WriteLogIntroduction(std::_tostream& os) const;

   /// @brief Called by WriteTransactionLog() immediately after the log is written.
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
};
