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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

std::unique_ptr<CEAFTxnManagerFactory> CEAFTxnManager::ms_pFactory;
std::unique_ptr<CEAFTxnManager> CEAFTxnManager::ms_pInstance;

void CEAFTxnManager::Execute(const CEAFTransaction& txn)
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
   std::unique_ptr<CEAFTransaction> txn(std::move(*iter));
   m_TxnHistory.erase(iter);

   // undo the transaction
   txn->Undo();

   // put the transaction into the undo history
   // m_UndoHistory now owns the transaction
   m_UndoHistory.emplace_back( std::move(txn) );
   m_Mode = Mode::Redo;
}

void CEAFTxnManager::Redo()
{
   PRECONDITION(m_Mode == Mode::Redo);

   if (m_UndoHistory.empty()) return;
   
   // Move the unique_ptr so the CEAF isn't deleted when pop_back is called.
   // The transaction is now owned in the local scope of this method
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

CEAFTxnManager& CEAFTxnManager::GetInstance()
{
   if ( ms_pInstance == nullptr )
   {
      // we don't have an instance of the transaction manager, create one
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

   return *ms_pInstance;
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
   // want the first undoable transcation from the end of the list so we need to search backward using reverse iterators
   auto result = std::find_if(std::rbegin(m_TxnHistory), std::rend(m_TxnHistory), [](auto& CEAF) {return CEAF->IsUndoable(); });

   // we need to return a forward iterator, if nothing was found, return the end iterator, otherwise
   // get the base of the reverse iterator using result.base(). this is a forward iterator point to one
   // location ahead of the found element (this is just how reverse iterators work). use the prefix form of the decrement
   // operator to move the result iterator back one spot then get the base iterator
   return result == std::rend(m_TxnHistory) ? std::end(m_TxnHistory) : --result.base();
}

CEAFTxnManager::TxnContainer::const_iterator CEAFTxnManager::FindFirstUndoableTxn() const
{
   auto result = std::find_if(std::rbegin(m_TxnHistory), std::rend(m_TxnHistory), [](const auto& txn) {return txn->IsUndoable(); });
   return result == std::rend(m_TxnHistory) ? std::end(m_TxnHistory) : --result.base();
}
