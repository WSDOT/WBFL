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

#include "StdAfx.h"
#include <EAF\EAFTxnManager.h>
#include <algorithm>

#if defined _UNITTEST
#include "TxnTestClass.h"
#endif // _UNITTEST

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

std::unique_ptr<CEAFTxnManagerFactory> CEAFTxnManager::ms_pFactory;
std::unique_ptr<CEAFTxnManager> CEAFTxnManager::ms_pInstance;

void CEAFTxnManager::Execute(CEAFTransaction& txn)
{
   Execute(std::move(txn.CreateClone()));
}

void CEAFTxnManager::Execute(std::unique_ptr<CEAFTransaction>&& txn)
{
   if (txn->Execute())
   {
      m_TxnHistory.emplace_back(std::move(txn));
      m_Mode = Mode::Repeat;
   }
}

void CEAFTxnManager::Undo()
{
   TxnContainer::iterator iter = FindFirstUndoableTxn();
   CHECK(iter != m_TxnHistory.end()); // You've called this out of sequence if there is not an undoable CEAF.

   // In release builds, simply don't undo.  This will keep the program from a fatal crash.
   if (iter == m_TxnHistory.end())
      return;

   // move the unique pointer of of m_TxnHistory so it isn't deleted when remove the transaction from the container
   // this method know owns the transaction.
   std::unique_ptr<CEAFTransaction> CEAF(std::move(*iter));
   m_TxnHistory.erase(iter);

   // undo the transaction
   CEAF->Undo();

   // put the trasaction into the undo history
   // m_UndoHistory now owns the transaction
   m_UndoHistory.emplace_back( std::move(CEAF) );
   m_Mode = Mode::Redo;
}

void CEAFTxnManager::Redo()
{
   PRECONDITION(m_Mode == Mode::Redo);

   if (m_UndoHistory.empty()) return;
   
   // Move the unique_ptr so the CEAF isn't deleted when pop_back is called.
   // The transation is now owned in the local scope of this method
   auto txn = std::move(m_UndoHistory.back());
   m_UndoHistory.pop_back();

   if (txn->Execute())
   {
      m_TxnHistory.emplace_back(std::move(txn));
   }
}

void CEAFTxnManager::Repeat()
{
   PRECONDITION(m_Mode == Mode::Repeat);

   if (m_TxnHistory.empty()) return;

   auto& txn = m_TxnHistory.back();
   
   CHECK(txn->IsRepeatable() );

   Execute(*txn);  // call the reference version!!! We want a Clone.
} // Repeat

bool CEAFTxnManager::CanUndo() const
{
   if (m_TxnHistory.empty()) return false;

   auto iter = FindFirstUndoableTxn();
   return (iter == m_TxnHistory.end() ? false : true);
}

bool CEAFTxnManager::CanRedo() const
{
   bool retval = false;

   switch(m_Mode)
   {
   case Mode::Repeat:
        retval = false;
        break;

   case Mode::Redo:
        retval = m_UndoHistory.empty() ? false : true;
        break;
   }

   return retval;
}

bool CEAFTxnManager::CanRepeat() const
{
   bool retval = false;

   switch(m_Mode)
   {
   case Mode::Repeat:
        if (m_TxnHistory.empty())
        {
           retval = false;
        }
        else
        {
           auto& txn = m_TxnHistory.back();
           retval = txn->IsRepeatable() ? true : false;
        }
        break;

   case Mode::Redo:
        retval = false;
        break;
   }

   return retval;
}

std::_tstring CEAFTxnManager::UndoName() const
{
   std::_tstring name(_T(""));

   if (!m_TxnHistory.empty())
   {
      auto iter = FindFirstUndoableTxn();
      if (iter != m_TxnHistory.end() ) name = (*iter)->Name();
   }

   return name;
}

std::_tstring CEAFTxnManager::RedoName() const
{
   std::_tstring name(_T(""));

   if ( !m_UndoHistory.empty() )
   {
      auto& txn = m_UndoHistory.back();
      if(txn) name = txn->Name();
   }

   return name;
}

std::_tstring CEAFTxnManager::RepeatName() const
{
   std::_tstring name(_T(""));

   if ( !m_TxnHistory.empty() )
   {
      auto& txn = m_TxnHistory.back();
      if(txn) name = txn->Name();
   }

   return name;
}

IndexType CEAFTxnManager::GetTxnCount() const
{
   return m_TxnHistory.size();
}

IndexType CEAFTxnManager::GetUndoCount() const
{
   return m_UndoHistory.size();
}

void CEAFTxnManager::WriteTransactionLog(std::_tostream& os) const
{
   WriteLogIntroduction(os);
   std::for_each(std::begin(m_TxnHistory), std::end(m_TxnHistory), [&os](auto& CEAF) {CEAF->Log(os); os << std::endl; });
   WriteLogConclusion(os);
}

void CEAFTxnManager::ClearTxnHistory()
{
   m_TxnHistory.clear();
}

void CEAFTxnManager::ClearUndoHistory()
{
   m_UndoHistory.clear();
}

void CEAFTxnManager::Clear()
{
   ClearTxnHistory();
   ClearUndoHistory();
   m_Mode = Mode::Repeat;
}

void CEAFTxnManager::SetTransactionManagerFactory(std::unique_ptr<CEAFTxnManagerFactory>&& pFactory)
{
   ms_pFactory = std::move(pFactory);
}

std::unique_ptr<CEAFTxnManager>& CEAFTxnManager::GetInstance()
{
   if ( ms_pInstance == nullptr )
   {
      // we don't have an instace of the transaction manager, create one
      if (ms_pFactory == nullptr)
      {
         // we don't have a transcation manager factory so just create the default CEAF mgr.
         ms_pInstance = std::make_unique<CEAFTxnManager>();
      }
      else
      {
         // we have a factory, so let it create the CEAF mgr.
         ms_pInstance = ms_pFactory->CreateTransactionManager();
      }
   }

   return ms_pInstance;
}

void CEAFTxnManager::WriteLogIntroduction(std::_tostream& /*os*/) const
{
   // Do nothing
}

void CEAFTxnManager::WriteLogConclusion(std::_tostream& /*os*/) const
{
   // Do nothing
}

CEAFTxnManager::TxnContainer::iterator CEAFTxnManager::FindFirstUndoableTxn()
{
   // want the first unduable transcation from the end of the list so we need to search backward using reverse iterators
   auto result = std::find_if(std::rbegin(m_TxnHistory), std::rend(m_TxnHistory), [](auto& CEAF) {return CEAF->IsUndoable(); });

   // we need to return a forward iterator, if nothing was found, return the end iterator, otherwise
   // get the base of the reverse iterator using result.base(). this is a forward iterator point to one
   // location ahead of the found element (this is just how reverse iterators work). use the prefix form of the decrement
   // operator to move the result iterator back one spot then get the base iterator
   return result == std::rend(m_TxnHistory) ? std::end(m_TxnHistory) : --result.base();
}

CEAFTxnManager::TxnContainer::const_iterator CEAFTxnManager::FindFirstUndoableTxn() const
{
   auto result = std::find_if(std::rbegin(m_TxnHistory), std::rend(m_TxnHistory), [](const auto& CEAF) {return CEAF->IsUndoable(); });
   return result == std::rend(m_TxnHistory) ? std::end(m_TxnHistory) : --result.base();
}

#if defined _DEBUG
bool CEAFTxnManager::AssertValid() const
{
   return true;
}

void CEAFTxnManager::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for CEAFTxnManager" << WBFL::Debug::endl;
   std::for_each(std::begin(m_TxnHistory), std::end(m_TxnHistory), [&os](auto& CEAF) {CEAF->Dump(os); os << WBFL::Debug::endl; });
}
#endif // _DEBUG

#if defined _UNITTEST
bool CEAFTxnManager::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CEAFTxnManger");

   testUndoableTxn txn1;
   testNotRepeatableTxn txn2;
   testNotUndoableTxn txn3;

   std::unique_ptr<CEAFTxnManager>& pMgr = CEAFTxnManager::GetInstance();

   // Test the start up state
   TRY_TESTME( pMgr->CanUndo()      == false );
   TRY_TESTME( pMgr->CanRedo()      == false );
   TRY_TESTME( pMgr->CanRepeat()    == false );
   TRY_TESTME( pMgr->GetTxnCount()  == 0 );
   TRY_TESTME( pMgr->GetUndoCount() == 0 );
   TRY_TESTME( pMgr->IsRedoMode()   == false );
   TRY_TESTME( pMgr->IsRepeatMode() == true );

   // Add a couple of non-repeatable transactions
   pMgr->Execute( txn2 );
   pMgr->Execute( txn2 );
   TRY_TESTME( pMgr->CanRepeat()    == false ); // there are no repeatable CEAF's
   TRY_TESTME( pMgr->IsRedoMode()   == false );
   TRY_TESTME( pMgr->IsRepeatMode() == true );

   // Add a repeatable CEAF
   pMgr->Execute(txn1 );
   TRY_TESTME( pMgr->CanRepeat()    == true ); // now there is one repeatable CEAF
   TRY_TESTME( pMgr->RepeatName()   == std::_tstring(_T("Undoable Txn")) );
   TRY_TESTME( pMgr->IsRedoMode()   == false );
   TRY_TESTME( pMgr->IsRepeatMode() == true );

   // Repeat the last CEAF
   pMgr->Repeat();
   TRY_TESTME( pMgr->CanRepeat()    == true );
   TRY_TESTME( pMgr->RepeatName()   == std::_tstring(_T("Undoable Txn")) );
   TRY_TESTME( pMgr->GetTxnCount()  == 4 );
   TRY_TESTME( pMgr->GetUndoCount() == 0 );
   TRY_TESTME( pMgr->IsRedoMode()   == false );
   TRY_TESTME( pMgr->IsRepeatMode() == true );
   
   // At this point, we can undo txn1, txn1, txn2, txn2 or we can repeat txn1
   TRY_TESTME( pMgr->CanUndo()   == true );
   TRY_TESTME( pMgr->CanRedo()   == false );
   TRY_TESTME( pMgr->CanRepeat() == true );

   // Undo the last txn
   TRY_TESTME( pMgr->UndoName()     == std::_tstring(_T("Undoable Txn")) );
   pMgr->Undo();
   pMgr->Undo();
   TRY_TESTME( pMgr->UndoName()     == std::_tstring(_T("Not Repeatable Txn")) );
   TRY_TESTME( pMgr->CanUndo()      == true );
   TRY_TESTME( pMgr->CanRedo()      == true );
   TRY_TESTME( pMgr->CanRepeat()    == false );
   TRY_TESTME( pMgr->GetTxnCount()  == 2 );
   TRY_TESTME( pMgr->GetUndoCount() == 2 );
   TRY_TESTME( pMgr->IsRedoMode()   == true );
   TRY_TESTME( pMgr->IsRepeatMode() == false );

   // Redo the last undo
   TRY_TESTME( pMgr->RedoName()     == std::_tstring(_T("Undoable Txn")) );
   pMgr->Redo();
   TRY_TESTME( pMgr->UndoName()     == std::_tstring(_T("Undoable Txn")) );
   TRY_TESTME( pMgr->CanUndo()      == true );
   TRY_TESTME( pMgr->CanRedo()      == true );
   TRY_TESTME( pMgr->CanRepeat()    == false );
   TRY_TESTME( pMgr->GetTxnCount()  == 3 );
   TRY_TESTME( pMgr->GetUndoCount() == 1 );
   TRY_TESTME( pMgr->IsRedoMode()   == true );
   TRY_TESTME( pMgr->IsRepeatMode() == false );

   // Add a non-undoable txn followed by an undoable txn
   pMgr->Execute(txn3 );
   pMgr->Execute(txn1 );
   TRY_TESTME( pMgr->UndoName()     == std::_tstring(_T("Undoable Txn")) );
   TRY_TESTME( pMgr->CanUndo()      == true );
   TRY_TESTME( pMgr->CanRedo()      == false );
   TRY_TESTME( pMgr->CanRepeat()    == true );
   TRY_TESTME( pMgr->GetTxnCount()  == 5 );
   TRY_TESTME( pMgr->GetUndoCount() == 1 );
   TRY_TESTME( pMgr->IsRedoMode()   == false );
   TRY_TESTME( pMgr->IsRepeatMode() == true );

   // Undo the last txn, the next txn is not-undoable, but there is another
   // undoable one farther up the stack so undo should be enabled.
   pMgr->Undo();
   TRY_TESTME( pMgr->UndoName()     == std::_tstring(_T("Undoable Txn")) );
   TRY_TESTME( pMgr->CanUndo()      == true );
   TRY_TESTME( pMgr->CanRedo()      == true );
   TRY_TESTME( pMgr->CanRepeat()    == false );
   TRY_TESTME( pMgr->GetTxnCount()  == 4 );
   TRY_TESTME( pMgr->GetUndoCount() == 2 );
   TRY_TESTME( pMgr->IsRedoMode()   == true );
   TRY_TESTME( pMgr->IsRepeatMode() == false );

   // Undo all that we can (should be 3 times)
   pMgr->Undo();
   pMgr->Undo();
   pMgr->Undo();
   TRY_TESTME( pMgr->CanUndo()      == false );
   TRY_TESTME( pMgr->CanRedo()      == true );
   TRY_TESTME( pMgr->CanRepeat()    == false );
   TRY_TESTME( pMgr->GetTxnCount()  == 1 );
   TRY_TESTME( pMgr->GetUndoCount() == 5 );
   TRY_TESTME( pMgr->IsRedoMode()   == true );
   TRY_TESTME( pMgr->IsRepeatMode() == false );

   // Clear the txn history, but keep the undo history
   pMgr->ClearTxnHistory();
   TRY_TESTME( pMgr->CanUndo()      == false );
   TRY_TESTME( pMgr->CanRedo()      == true );
   TRY_TESTME( pMgr->CanRepeat()    == false );
   TRY_TESTME( pMgr->GetTxnCount()  == 0 );
   TRY_TESTME( pMgr->GetUndoCount() == 5 );
   TRY_TESTME( pMgr->IsRedoMode()   == true );
   TRY_TESTME( pMgr->IsRepeatMode() == false );

   // Add a few txns back
   pMgr->Execute(txn1 );
   pMgr->Execute(txn1 );
   pMgr->Execute(txn1 );
   TRY_TESTME( pMgr->CanUndo()      == true );
   TRY_TESTME( pMgr->CanRedo()      == false );
   TRY_TESTME( pMgr->CanRepeat()    == true );
   TRY_TESTME( pMgr->GetTxnCount()  == 3 );
   TRY_TESTME( pMgr->GetUndoCount() == 5 );
   TRY_TESTME( pMgr->IsRedoMode()   == false );
   TRY_TESTME( pMgr->IsRepeatMode() == true );
   TRY_TESTME( pMgr->UndoName()     == std::_tstring(_T("Undoable Txn")) );

   // Clear the undo history, but keep the txn history
   pMgr->ClearUndoHistory();
   TRY_TESTME( pMgr->CanUndo()      == true );
   TRY_TESTME( pMgr->CanRedo()      == false );
   TRY_TESTME( pMgr->CanRepeat()    == true );
   TRY_TESTME( pMgr->GetTxnCount()  == 3 );
   TRY_TESTME( pMgr->GetUndoCount() == 0 );
   TRY_TESTME( pMgr->IsRedoMode()   == false );
   TRY_TESTME( pMgr->IsRepeatMode() == true );

   // Undo one CEAF just so there is something in m_UndoHistory
   pMgr->Undo();
   TRY_TESTME( pMgr->CanUndo()      == true );
   TRY_TESTME( pMgr->CanRedo()      == true );
   TRY_TESTME( pMgr->CanRepeat()    == false );
   TRY_TESTME( pMgr->GetTxnCount()  == 2 );
   TRY_TESTME( pMgr->GetUndoCount() == 1 );
   TRY_TESTME( pMgr->IsRedoMode()   == true );
   TRY_TESTME( pMgr->IsRepeatMode() == false );
   TRY_TESTME( pMgr->RedoName()     == std::_tstring(_T("Undoable Txn")) );

   // Clear everything out
   pMgr->Clear();
   TRY_TESTME( pMgr->CanUndo()      == false );
   TRY_TESTME( pMgr->CanRedo()      == false );
   TRY_TESTME( pMgr->CanRepeat()    == false );
   TRY_TESTME( pMgr->GetTxnCount()  == 0 );
   TRY_TESTME( pMgr->GetUndoCount() == 0 );
   TRY_TESTME( pMgr->IsRedoMode()   == false );
   TRY_TESTME( pMgr->IsRepeatMode() == true );

   TESTME_EPILOG("CEAFTxnManger");
}
#endif // _UNITTEST
