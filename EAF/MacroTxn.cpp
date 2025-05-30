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

#include "stdafx.h"
#include <EAF\MacroTxn.h>

using namespace WBFL::EAF;

bool MacroTxn::Execute()
{
   // Execute every transaction in the list, starting with the first one
   // put into the container
   auto begin = m_Transactions.begin();
   auto iter = begin;
   auto end = m_Transactions.end();

   for ( ; iter != end; iter++ )
   {
      auto& txn(*iter);
      if (!txn->Execute())
      {
         // this transaction failed... roll back
         break;
      }
   }

   if (iter != end)
   {
      // something went wrong... roll back all completed transactions
      iter--; // back up one
      do
      {
         auto& txn(*iter);
         ASSERT(txn->IsUndoable()); // there isn't going to be a full rollback
         txn->Undo();
         iter--;
      } while (iter != begin);

      return false;
   }

   return true;
}

void MacroTxn::Undo()
{
   // Undo every transaction in the list
   // Traverse the list backwards so that the last transaction 
   // executed is the first one undone.
   std::for_each(std::rbegin(m_Transactions), std::rend(m_Transactions), [](auto& txn) {txn->Undo(); });
}

std::_tstring MacroTxn::Name() const
{
   return m_Name;
}

void MacroTxn::Name(const std::_tstring& name)
{
   m_Name = name;
}

std::unique_ptr<Transaction> MacroTxn::CreateClone() const
{
   std::unique_ptr<MacroTxn> pClone(std::make_unique<MacroTxn>());
   pClone->Name(m_Name);

   // use the reference version of AddTransaction so the individual transactions are cloned
   std::for_each(std::begin(m_Transactions), std::end(m_Transactions), [&pClone](auto& txn) {pClone->AddTransaction(*txn); });

   return pClone;
}

void MacroTxn::Log(std::_tostream& os) const
{
   os << Name() << ": ";
   auto begin = m_Transactions.begin();
   auto end   = m_Transactions.end();
   while ( begin != end )
   {
      auto& pTxn = *begin++;
      pTxn->Log(os);

      if (begin != end) os << ", ";
   }
}

void MacroTxn::AddTransaction(Transaction& txn)
{
   m_Transactions.emplace_back(txn.CreateClone());
}

void MacroTxn::AddTransaction(std::unique_ptr<Transaction>&& pTxn)
{
   m_Transactions.emplace_back(std::move(pTxn));
}

bool MacroTxn::IsUndoable() const
{
   // this transaction is NOT undoable if one if its steps is NOT undoable
   // All steps must be undoable if the macro is undoable.

   bool is_undoable = true;
   auto begin = m_Transactions.cbegin();
   auto end   = m_Transactions.cend();
   while ( begin != end )
   {
      const auto& pTxn = *begin++;

      if ( !pTxn->IsUndoable() )
      {
         is_undoable = false;
         break;
      }
   }

   return is_undoable;
}

bool MacroTxn::IsRepeatable() const
{
   // this transaction is NOT repeatable if one if its steps is NOT repeatable
   // All steps must be repeatable if the macro is repeatable.

   bool is_repeatable = true;
   auto begin = m_Transactions.cbegin();
   auto end   = m_Transactions.cend();
   while ( begin != end )
   {
      const auto& pTxn = *begin++;

      if (!pTxn->IsRepeatable())
      {
         is_repeatable = false;
         break;
      }
   }

   return is_repeatable;
}

IndexType MacroTxn::GetTxnCount() const
{
   return m_Transactions.size();
}
