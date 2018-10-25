///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include <System\SysLib.h>

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          txnMacroTxn           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <System\MacroTxn.h>

#if defined _UNITTEST
#include "TxnTestClass.h"
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//======================== LIFECYCLE  =======================================

txnMacroTxn::txnMacroTxn() :
txnTransaction()
{
   m_Name = _T("Macro");
} // txnMacroTxn

txnMacroTxn::~txnMacroTxn()
{
} // ~txnMacroTxn

//======================== OPERATORS  =======================================

//======================== OPERATIONS =======================================
bool txnMacroTxn::Execute()
{
   // Execute every txn in the list, starting with the first one
   // put into the container
   TxnIterator begin = m_Transactions.begin();
   TxnIterator end   = m_Transactions.end();

   while ( begin != end )
   {
      TransactionPtr pTxn = *begin++;
      pTxn->Execute();
   }

   // :KLUDGE: rab 01.09.97 : Macro always executes
   // :METHOD: MacroTxn::Execute
   //
   // This method always returns true.  It would be better if
   // pTxn->Execute() above checked the return value.  If one of the
   // txns returned false, all of the previous txns would be undone
   // and this method will return false.

   return true;
} // Execute

void txnMacroTxn::Undo()
{
   // Undo every txn in the list
   // Traverse the list backwards so that the last txn 
   // executed is the first one undone.
   TxnReverseIterator begin = m_Transactions.rbegin();
   TxnReverseIterator end   = m_Transactions.rend();

   while ( begin != end )
   {
      TransactionPtr pTxn = *begin++;
      pTxn->Undo();
   }
} // Undo

std::_tstring txnMacroTxn::Name() const
{
   return m_Name;
} // GetName

void txnMacroTxn::Name(const std::_tstring& name)
{
   m_Name = name;
} // Name

txnTransaction* txnMacroTxn::CreateClone() const
{
   txnMacroTxn* pClone = new txnMacroTxn;

   TxnConstIterator begin = m_Transactions.begin();
   TxnConstIterator end   = m_Transactions.end();
   while ( begin != end )
   {
      TransactionPtr pTxn = *begin++;

      // Use the reference version.
      // We are not giving up ownership of the txn
      pClone->AddTransaction(*pTxn);
   }

   pClone->Name(m_Name);

   return pClone;
} // Clone

void txnMacroTxn::Log(std::_tostream& os) const
{
   os << Name() << ": ";
   TxnConstIterator begin = m_Transactions.begin();
   TxnConstIterator end   = m_Transactions.end();
   while ( begin != end )
   {
      TransactionPtr pTxn = *begin++;
      pTxn->Log(os);

      if (begin != end)
         os << ", ";
   }
} // Log

void txnMacroTxn::AddTransaction(txnTransaction& rTxn)
{
   TransactionPtr clone( rTxn.CreateClone() );
   m_Transactions.push_back( clone );
} // AddTransaction

void txnMacroTxn::AddTransaction(txnTransaction* pTxn)
{
   TransactionPtr ptr( pTxn );
   m_Transactions.push_back(ptr);
} // AddTransaction

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
bool txnMacroTxn::IsUndoable()
{
   // this txn is NOT undoable if one if its steps is NOT undoable
   // All steps must be undoable if the macro is undoable.

   bool is_undoable = true;
   TxnIterator begin = m_Transactions.begin();
   TxnIterator end   = m_Transactions.end();
   while ( begin != end )
   {
      TransactionPtr pTxn = *begin++;

      if ( !pTxn->IsUndoable() )
      {
         is_undoable = false;
         break;
      }
   }

   return is_undoable;
} // IsUndoable

bool txnMacroTxn::IsRepeatable()
{
   // this txn is NOT repeatable if one if its steps is NOT repeatable
   // All steps must be repeatable if the macro is repeatable.

   bool is_repeatable = true;
   TxnIterator begin = m_Transactions.begin();
   TxnIterator end   = m_Transactions.end();
   while ( begin != end )
   {
      TransactionPtr pTxn = *begin++;

      if (!pTxn->IsRepeatable())
      {
         is_repeatable = false;
         break;
      }
   }

   return is_repeatable;
} // IsRepeatable

CollectionIndexType txnMacroTxn::GetTxnCount()
{
   return m_Transactions.size();
} // GetTxnCount

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool txnMacroTxn::AssertValid() const
{
   return true;
}

void txnMacroTxn::Dump(dbgDumpContext& os) const
{
   os << "Dump for txnMacroTxn" << endl;
   os << Name() << ": ";
   TxnConstIterator begin = m_Transactions.begin();
   TxnConstIterator end   = m_Transactions.end();
   while ( begin != end )
   {
      TransactionPtr pTxn = *begin++;
      pTxn->Dump(os);

      if (begin != end)
         os << ", ";
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool txnMacroTxn::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("txnMacroTxn");
   testUndoableTxn      txn1;
   testNotUndoableTxn   txn2;
   testNotRepeatableTxn txn3;

   txnMacroTxn macro;
   macro.AddTransaction( txn1 );
   macro.AddTransaction( txn1 );
   macro.AddTransaction( txn1 );
   TRY_TESTME( macro.IsUndoable()   == true );
   TRY_TESTME( macro.IsRepeatable() == true );

   macro.AddTransaction( txn2 );
   TRY_TESTME( macro.IsUndoable()   == false );
   TRY_TESTME( macro.IsRepeatable() == true );

   macro.AddTransaction( txn3 );
   TRY_TESTME( macro.IsUndoable()   == false );
   TRY_TESTME( macro.IsRepeatable() == false );

   TESTME_EPILOG("txnMacroTxn");
}
#endif // _UNITTEST
