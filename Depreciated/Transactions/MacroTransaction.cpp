///////////////////////////////////////////////////////////////////////
// Transactions - Utility library for managing transactions, undo/redo
// Copyright � 1999-2022  Washington State Department of Transportation
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

// MacroTransaction.cpp : Implementation of CMacroTransaction
#include "stdafx.h"
#include "WBFLTransactions.h"
#include "MacroTransaction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMacroTransaction

STDMETHODIMP CMacroTransaction::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IWBFLMacroTransaction
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMacroTransaction::Execute()
{
   TxnContainer::iterator iter;
   for ( iter = m_Transactions.begin(); iter != m_Transactions.end(); iter++ )
   {
      TxnType item = *iter;
      CComPtr<IWBFLTransaction> txn(item.m_T);

      txn->Execute();
   }

	return S_OK;
}

STDMETHODIMP CMacroTransaction::Undo()
{
   TxnContainer::reverse_iterator iter;
   for ( iter = m_Transactions.rbegin(); iter != m_Transactions.rend(); iter++ )
   {
      TxnType item = *iter;
      CComPtr<IWBFLTransaction> txn(item.m_T);

      txn->Undo();
   }

	return S_OK;
}

STDMETHODIMP CMacroTransaction::get_Name(BSTR *pVal)
{
   *pVal = m_bstrName.Copy();
	return S_OK;
}

STDMETHODIMP CMacroTransaction::put_Name(BSTR newVal)
{
   m_bstrName = newVal;
	return S_OK;
}

STDMETHODIMP CMacroTransaction::AddTransaction(IWBFLTransaction *txn)
{
   m_Transactions.emplace_back(txn);

   VARIANT_BOOL bIsUndoable;
   txn->get_IsUndoable(&bIsUndoable);
   if ( bIsUndoable == VARIANT_FALSE )
      m_bIsUndoable = VARIANT_FALSE;

   VARIANT_BOOL bIsRepeatable;
   txn->get_IsRepeatable(&bIsRepeatable);
   if ( bIsRepeatable == VARIANT_FALSE )
      m_bIsRepeatable = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CMacroTransaction::get_IsUndoable(VARIANT_BOOL *pVal)
{
   *pVal = m_bIsUndoable;
	return S_OK;
}

STDMETHODIMP CMacroTransaction::get_IsRepeatable(VARIANT_BOOL *pVal)
{
   *pVal = m_bIsRepeatable;
	return S_OK;
}


STDMETHODIMP CMacroTransaction::get_Count(CollectionIndexType *pVal)
{
   *pVal = m_Transactions.size();
	return S_OK;
}
