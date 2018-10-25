///////////////////////////////////////////////////////////////////////
// Transactions - Utility library for managing transactions, undo/redo
// Copyright © 1999-2018  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TransactionMgr.cpp : Implementation of CTransactionMgr
#include "stdafx.h"
#include "WBFLTransactions.h"
#include "TransactionMgr.h"
#include "MacroTransaction.h"
#include "MacroAdapter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransactionMgr
void CTransactionMgr::FinalRelease()
{
   ATLTRACE("CTransactionMgr::FinalRelease()\n");
   Clear();
}

STDMETHODIMP CTransactionMgr::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IWBFLTransactionMgr
	};
	for (CollectionIndexType i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CTransactionMgr::Execute(IWBFLTransaction *pTxn)
{
   CComPtr<IWBFLTransaction> txn(pTxn);

   if ( m_Macros.size() > 0 )
   {
      CAdapt<CComPtr<IWBFLMacroTransaction> > macro = m_Macros.back();
      macro.m_T->AddTransaction(txn);
      return S_OK;
   }

   HRESULT hr = txn->Execute();
   if ( FAILED(hr) )
      return hr;

   m_TxnHistory.emplace_back(txn);
   m_Mode = txnRepeat;

	return S_OK;
}

STDMETHODIMP CTransactionMgr::Undo()
{
   CComPtr<IWBFLTransaction> txn;
   if ( FAILED(GetFirstUndoableTxn(&txn)) )
      return S_OK; // No undoable transactions... do nothing

   if ( txn == nullptr )
      return S_OK;

   HRESULT hr = txn->Undo();
   if ( FAILED(hr) )
      return hr;

   m_UndoHistory.emplace_back(txn);
   m_Mode = txnRedo;

	return S_OK;
}

STDMETHODIMP CTransactionMgr::Redo()
{
   ATLASSERT( m_Mode == txnRedo );

   TxnType item = m_UndoHistory.back();
   m_UndoHistory.pop_back();

   CComPtr<IWBFLTransaction> txn(item.m_T);
   
   return Execute(txn);
}

STDMETHODIMP CTransactionMgr::Repeat()
{
   ATLASSERT( m_Mode == txnRepeat );

   TxnType item = m_TxnHistory.back();
   CComPtr<IWBFLTransaction> txn(item.m_T);

   VARIANT_BOOL bRepeatable;
   txn->get_IsRepeatable(&bRepeatable);
   if ( bRepeatable == VARIANT_FALSE )
      return E_FAIL; // You must first call CanRepeat to determine if the current txn is repeatable

   return Execute(txn);
}

STDMETHODIMP CTransactionMgr::get_CanUndo(VARIANT_BOOL *pVal)
{
   if ( m_TxnHistory.empty() )
   {
      *pVal = VARIANT_FALSE;
      return S_OK;
   }

   CComPtr<IWBFLTransaction> txn;
   FindFirstUndoableTxn(&txn);

   *pVal = (txn == nullptr ? VARIANT_FALSE : VARIANT_TRUE );
   return S_OK;
}

STDMETHODIMP CTransactionMgr::get_CanRedo(VARIANT_BOOL *pVal)
{
   switch(m_Mode)
   {
   case txnRepeat:
      *pVal = VARIANT_FALSE;
      break;

   case txnRedo:
      *pVal = m_UndoHistory.empty() ? VARIANT_FALSE : VARIANT_TRUE;
      break;
   }

	return S_OK;
}

STDMETHODIMP CTransactionMgr::get_CanRepeat(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here
   switch( m_Mode )
   {
   case txnRepeat:
      {
         if ( m_TxnHistory.empty() )
         {
            *pVal = VARIANT_FALSE;
         }
         else
         {
            TxnType item = m_TxnHistory.back();
            CComPtr<IWBFLTransaction> txn(item.m_T);
            txn->get_IsRepeatable(pVal);
         }
      }
      break;

   case txnRedo:
      *pVal = VARIANT_FALSE;
      break;
   }

	return S_OK;
}

STDMETHODIMP CTransactionMgr::get_UndoName(BSTR *pVal)
{
   CComPtr<IWBFLTransaction> txn;
   FindFirstUndoableTxn(&txn);

   if ( txn )
   {
      txn->get_Name(pVal);
   }
   else
   {
      CComBSTR bstrBlank("");
      *pVal = bstrBlank.Copy();
   }

	return S_OK;
}

STDMETHODIMP CTransactionMgr::get_RedoName(BSTR *pVal)
{
   if ( m_UndoHistory.empty() )
   {
      CComBSTR bstrBlank("");
      *pVal = bstrBlank.Copy();
   }
   else
   {
      TxnType item = m_UndoHistory.back();
      CComPtr<IWBFLTransaction> txn(item.m_T);
      txn->get_Name(pVal);
   }

	return S_OK;
}

STDMETHODIMP CTransactionMgr::get_RepeatName(BSTR *pVal)
{
   if ( m_TxnHistory.empty() )
   {
      CComBSTR bstrBlank("");
      *pVal = bstrBlank.Copy();
   }
   else
   {
      TxnType item = m_TxnHistory.back();
      CComPtr<IWBFLTransaction> txn(item.m_T);
      txn->get_Name(pVal);
   }

	return S_OK;
}

STDMETHODIMP CTransactionMgr::get_TransactionCount(CollectionIndexType *pVal)
{
   *pVal = m_TxnHistory.size();
	return S_OK;
}

STDMETHODIMP CTransactionMgr::get_UndoCount(CollectionIndexType *pVal)
{
   *pVal = m_UndoHistory.size();
	return S_OK;
}

STDMETHODIMP CTransactionMgr::PeekTransaction(CollectionIndexType idx, IWBFLTransaction* *txn)
{
   if ( idx < 0 || m_TxnHistory.size() <= idx )
      return E_INVALIDARG;

   TxnContainer::iterator iter = m_TxnHistory.begin();
   for ( CollectionIndexType i = 0; i < idx; i++ )
      iter++;

   TxnType item = *iter;
   (*txn) = item.m_T;
   (*txn)->AddRef();

   return S_OK;
}

STDMETHODIMP CTransactionMgr::PeekUndo(CollectionIndexType idx, IWBFLTransaction* *txn)
{
   if ( idx < 0 || m_UndoHistory.size() <= idx )
      return E_INVALIDARG;

   TxnContainer::iterator iter = m_UndoHistory.begin();
   for ( CollectionIndexType i = 0; i < idx; i++ )
      iter++;

   TxnType item = *iter;
   (*txn) = item.m_T;
   (*txn)->AddRef();

   return S_OK;
}

STDMETHODIMP CTransactionMgr::ClearTransactionHistory()
{
   m_TxnHistory.clear();
	return S_OK;
}

STDMETHODIMP CTransactionMgr::ClearUndoHistory()
{
   m_UndoHistory.clear();
	return S_OK;
}

STDMETHODIMP CTransactionMgr::Clear()
{
   ClearTransactionHistory();
   ClearUndoHistory();
   m_Mode = txnRepeat;
	return S_OK;
}

STDMETHODIMP CTransactionMgr::get_Mode(TxnModeType* mode)
{
   CHECK_RETVAL(mode);
   *mode = m_Mode;
	return S_OK;
}

STDMETHODIMP CTransactionMgr::BeginMacro(VARIANT nameOrMacro)
{
   if ( nameOrMacro.vt == VT_BSTR )
   {
      CComObject<CMacroTransaction>* pMacro;
      CComObject<CMacroTransaction>::CreateInstance(&pMacro);

      CComPtr<IWBFLMacroTransaction> macro = pMacro;
      macro->put_Name(nameOrMacro.bstrVal);

      m_Macros.push_back(macro);
   }
   else if ( nameOrMacro.vt == VT_UNKNOWN || nameOrMacro.vt == VT_DISPATCH)
   {
      CComQIPtr<IWBFLMacroTransaction> macro(nameOrMacro.punkVal);
      if ( macro == nullptr )
         return E_INVALIDARG;

      m_Macros.emplace_back(macro);
   }
   else
   {
      return E_INVALIDARG;
   }

   return S_OK;
}

STDMETHODIMP CTransactionMgr::ExecuteMacro()
{
   // If there are no transactions in the macro, then there
   // is nothing to execute... just get the heck outta here.
   CComPtr<IWBFLMacroTransaction> macro = m_Macros.back();
   m_Macros.pop_back();
   
   CollectionIndexType count;
   macro->get_Count(&count);

   if ( count == 0 )
      return S_OK;

   // Adapt the macro and execute
   CComObject<CMacroAdapter>* pAdapter;
   CComObject<CMacroAdapter>::CreateInstance(&pAdapter);
   pAdapter->putref_Macro(macro);

   return Execute(pAdapter);
}

STDMETHODIMP CTransactionMgr::AbortMacro()
{
   // If there are no transactions in the macro, then there
   // is nothing to execute... just get the heck outta here.
   m_Macros.pop_back();
   return S_OK;
}

HRESULT CTransactionMgr::FindFirstUndoableTxn(IWBFLTransaction* *txn) const
{
   *txn = nullptr;

   TxnContainer::const_reverse_iterator begin = m_TxnHistory.rbegin();
   TxnContainer::const_reverse_iterator end   = m_TxnHistory.rend();

   while ( begin != end )
   {
      TxnType item = *begin++;
      CComPtr<IWBFLTransaction> pTxn = item.m_T;
      VARIANT_BOOL bIsUndoable;
      pTxn->get_IsUndoable(&bIsUndoable);
      if ( bIsUndoable == VARIANT_TRUE )
      {
         *txn = pTxn;
         (*txn)->AddRef();
         return S_OK;
      }
   }

   return S_FALSE;
} 

HRESULT CTransactionMgr::GetFirstUndoableTxn(IWBFLTransaction* *txn)
{
   *txn = nullptr;

   TxnContainer::iterator i;

   m_TxnHistory.reverse();

   for ( i = m_TxnHistory.begin(); i != m_TxnHistory.end(); i++ )
   {
      TxnType item = *i;
      CComPtr<IWBFLTransaction> pTxn = item.m_T;
      VARIANT_BOOL bIsUndoable;
      pTxn->get_IsUndoable(&bIsUndoable);
      if ( bIsUndoable == VARIANT_TRUE )
      {
         *txn = pTxn;
         (*txn)->AddRef();

         // Erase the entry from the container
         m_TxnHistory.erase( i );

         break;
      }
   }

   m_TxnHistory.reverse();
   return S_OK;
}
