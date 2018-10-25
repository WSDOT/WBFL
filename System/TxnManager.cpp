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

#include <System\SysLib.h>

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          txnTxnManager           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <System\TxnManager.h>                // class implementation
#include <algorithm>

#if defined _UNITTEST
#include "TxnTestClass.h"
#endif // _UNITTEST

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

txnTxnManager* txnTxnManager::ms_pInstance = 0;
sysSingletonKillerT<txnTxnManager> txnTxnManager::ms_Killer;

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void txnTxnManager::Execute(txnTransaction& rTxn)
{
   txnTransaction* pTxn = rTxn.CreateClone();
   Execute(pTxn);
} // Execute

void txnTxnManager::Execute(txnTransaction* pTxn)
{
   if (pTxn->Execute())
   {
      m_TxnHistory.push_back( TxnItem(pTxn) );
      m_Mode = RepeatMode;
   }
} // Execute

void txnTxnManager::Undo()
{
   TxnItem pTxn = FindFirstUndoableTxn(true);

   // You've called this out of sequence if there is not an undoable txn.
   CHECK( pTxn != 0 );

   // In release builds, simply don't undo.  This will keep the program from
   // a fatal crash.
   if (pTxn == 0)
      return;

   // Undo the txn
   pTxn->Undo();
   m_UndoHistory.push_back( pTxn );
   m_Mode = RedoMode;
} // Undo

void txnTxnManager::Redo()
{
   PRECONDITION(m_Mode == RedoMode);

   if ( m_UndoHistory.empty() )
   {
      return;
   }

   TxnItem apTxn = m_UndoHistory.back();
   m_UndoHistory.pop_back();

   if (apTxn->Execute())
   {
      m_TxnHistory.push_back( apTxn );
   }

   // The real transaction pointer is deleted.
} // Redo

void txnTxnManager::Repeat()
{
   PRECONDITION(m_Mode == RepeatMode);

   if ( m_TxnHistory.empty() )
   {
      return;
   }

   TxnItem apTxn = m_TxnHistory.back();
   
   CHECK( apTxn->IsRepeatable() );

   Execute(*apTxn);  // call the reference version!!! We want a Clone.
} // Repeat

bool txnTxnManager::CanUndo() const
{
   if (m_TxnHistory.empty())
      return false;

   TxnItem pTxn = FindFirstUndoableTxn();

   return ( pTxn == 0 ? false : true );
} // CanUndo

bool txnTxnManager::CanRedo() const
{
   bool retval = false;

   switch(m_Mode)
   {
   case RepeatMode:
        retval = false;
        break;

   case RedoMode:
        retval = m_UndoHistory.empty() ? false : true;
        break;
   }

   return retval;
} // CanRedo

bool txnTxnManager::CanRepeat() const
{
   TxnItem apTxn;
   bool retval = false;

   switch(m_Mode)
   {
   case RepeatMode:
        if (m_TxnHistory.empty())
        {
           retval = false;
        }
        else
        {
           apTxn = m_TxnHistory.back();
           retval = apTxn->IsRepeatable() ? true : false;
        }
        break;

   case RedoMode:
        retval = false;
        break;
   }

   return retval;
} // CanRedo

std::_tstring txnTxnManager::UndoName() const
{
   std::_tstring name(_T(""));

   if (m_TxnHistory.empty())
      return name;

   TxnItem pTxn = FindFirstUndoableTxn();
   if (pTxn != 0)
      name = pTxn->Name();

   return name;

}

std::_tstring txnTxnManager::RedoName() const
{
   std::_tstring name(_T(""));

   if ( !m_UndoHistory.empty() )
   {
      TxnItem apTxn = m_UndoHistory.back();
      name = apTxn->Name();
   }

   return name;
}

std::_tstring txnTxnManager::RepeatName() const
{
   std::_tstring name(_T(""));

   if ( !m_TxnHistory.empty() )
   {
      TxnItem apTxn = m_TxnHistory.back();
      name = apTxn->Name();
   }

   return name;
}

CollectionIndexType txnTxnManager::GetTxnCount() const
{
   return m_TxnHistory.size();
}

CollectionIndexType txnTxnManager::GetUndoCount() const
{
   return m_UndoHistory.size();
}

void txnTxnManager::WriteTransactionLog(std::_tostream& os) const
{
   TxnConstIterator begin = m_TxnHistory.begin();
   TxnConstIterator end   = m_TxnHistory.end();

   WriteLogIntroduction(os);

   while ( begin != end )
   {
      TxnItem apTxn = *begin++;
      apTxn->Log( os );
      os << std::endl;
   }

   WriteLogConclusion(os);
}

void txnTxnManager::ClearTxnHistory()
{
   m_TxnHistory.clear();
}

void txnTxnManager::ClearUndoHistory()
{
   m_UndoHistory.clear();
}

void txnTxnManager::Clear()
{
   ClearTxnHistory();
   ClearUndoHistory();
   m_Mode = RepeatMode;
}

//======================== ACCESS     =======================================
txnTxnManager* txnTxnManager::GetInstance()
{
   if ( ms_pInstance == 0 )
   {
      ms_pInstance = new txnTxnManager;
      ms_Killer.SetDoomed( ms_pInstance );
   }

   return ms_pInstance;
} // GetInstance

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

txnTxnManager::txnTxnManager()
{
   m_Mode = RepeatMode;
} // txnTxnManager

txnTxnManager::~txnTxnManager()
{
   Clear();
} // ~txnTxnManager

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void txnTxnManager::WriteLogIntroduction(std::_tostream& /*os*/) const
{
   // Do nothing
}

void txnTxnManager::WriteLogConclusion(std::_tostream& /*os*/) const
{
   // Do nothing
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
txnTxnManager::TxnItem txnTxnManager::FindFirstUndoableTxn() const
{
   TxnConstReverseIterator iter = m_TxnHistory.rbegin();
   TxnConstReverseIterator end   = m_TxnHistory.rend();

   while ( iter != end )
   {
      TxnItem apTxn = *iter++;
      if ( apTxn->IsUndoable() )
      {
         return apTxn;
      }
   }

   return txnTxnManager::TxnItem();
}

txnTxnManager::TxnItem txnTxnManager::FindFirstUndoableTxn(bool bRemoveFromHistory)
{
   // to do a removal, we need a forward iterator
   m_TxnHistory.reverse(); // reverse the container

   TxnIterator iter = m_TxnHistory.begin();
   TxnIterator end  = m_TxnHistory.end();

   TxnItem apTxn;
   while ( iter != end )
   {
      apTxn = *iter;
      if ( apTxn->IsUndoable() )
      {
         if ( bRemoveFromHistory )
            m_TxnHistory.erase(iter);

         break;
      }

      iter++;
   }

   // put the history back in the correct order
   m_TxnHistory.reverse();

   return apTxn;
} // FindFirstUndoableTxn

//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool txnTxnManager::AssertValid() const
{
   return true;
}

void txnTxnManager::Dump(dbgDumpContext& os) const
{
   os << "Dump for txnTxnManager" << endl;

   TxnConstIterator begin = m_TxnHistory.begin();
   TxnConstIterator end   = m_TxnHistory.end();

   while ( begin != end )
   {
      TxnItem apTxn = *begin++;
      apTxn->Dump( os );
      os << endl;
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool txnTxnManager::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("txnTxnManger");

   testUndoableTxn txn1;
   testNotRepeatableTxn txn2;
   testNotUndoableTxn txn3;

   txnTxnManager* pMgr = txnTxnManager::GetInstance();

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
   TRY_TESTME( pMgr->CanRepeat()    == false ); // there are no repeatable txn's
   TRY_TESTME( pMgr->IsRedoMode()   == false );
   TRY_TESTME( pMgr->IsRepeatMode() == true );

   // Add a repeatable txn
   pMgr->Execute( txn1 );
   TRY_TESTME( pMgr->CanRepeat()    == true ); // now there is one repeatable txn
   TRY_TESTME( pMgr->RepeatName()   == std::_tstring(_T("Undoable Txn")) );
   TRY_TESTME( pMgr->IsRedoMode()   == false );
   TRY_TESTME( pMgr->IsRepeatMode() == true );

   // Repeat the last txn
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
   pMgr->Execute( txn3 );
   pMgr->Execute( txn1 );
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
   pMgr->Execute( txn1 );
   pMgr->Execute( txn1 );
   pMgr->Execute( txn1 );
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

   // Undo one txn just so there is something in m_UndoHistory
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

   TESTME_EPILOG("txnTxnManger");
}
#endif // _UNITTEST
