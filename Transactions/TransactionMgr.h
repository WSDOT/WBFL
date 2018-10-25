///////////////////////////////////////////////////////////////////////
// Transactions - Utility library for managing transactions, undo/redo
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TransactionMgr.h : Declaration of the CTransactionMgr

#ifndef __TRANSACTIONMGR_H_
#define __TRANSACTIONMGR_H_

#include "resource.h"       // main symbols
#include <list>
#include <stack>

/////////////////////////////////////////////////////////////////////////////
// CTransactionMgr
class ATL_NO_VTABLE CTransactionMgr : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTransactionMgr, &CLSID_WBFLTransactionMgr>,
	public ISupportErrorInfo,
	public IWBFLTransactionMgr
{
public:
	CTransactionMgr()
	{
      m_Mode = txnRepeat;
	}

   ~CTransactionMgr()
   {
      ATLTRACE("CTransactionMgr::~CTransactionMgr()\n");
   }

   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_TRANSACTIONMGR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTransactionMgr)
	COM_INTERFACE_ENTRY(IWBFLTransactionMgr)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   typedef CAdapt<CComPtr<IWBFLTransaction> > TxnType;
   typedef std::list<TxnType> TxnContainer;
   TxnContainer m_TxnHistory;
   TxnContainer m_UndoHistory;

   TxnModeType m_Mode;

   CComPtr<IWBFLMacroTransaction> m_TargetMacro;
   std::list<CAdapt<CComPtr<IWBFLMacroTransaction> > > m_Macros;

   // Finds the first undoable transaction.  The m_TxnHistory container
   // retains ownership of the transaction pointer.
   HRESULT FindFirstUndoableTxn(IWBFLTransaction* *txn) const;

   // Returns the first undoable transaction.  This transaction is
   // removed from the m_TxnHistory container.  The returned pointer
   // is un-owned.
   HRESULT GetFirstUndoableTxn(IWBFLTransaction* *txn);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IWBFLTransactionMgr
public:
	STDMETHOD(get_Mode)(/*[out, retval]*/ TxnModeType* mode) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(ClearUndoHistory)() override;
	STDMETHOD(ClearTransactionHistory)() override;
   STDMETHOD(PeekTransaction)(/*[in]*/ CollectionIndexType idx,/*[out,retval]*/ IWBFLTransaction* *txn) override;
   STDMETHOD(PeekUndo)(/*[in]*/ CollectionIndexType idx,/*[out,retval]*/ IWBFLTransaction* *txn) override;
	STDMETHOD(get_UndoCount)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_TransactionCount)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_RepeatName)(/*[out, retval]*/ BSTR *pVal) override;
	STDMETHOD(get_RedoName)(/*[out, retval]*/ BSTR *pVal) override;
	STDMETHOD(get_UndoName)(/*[out, retval]*/ BSTR *pVal) override;
	STDMETHOD(get_CanRepeat)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(get_CanRedo)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(get_CanUndo)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(Repeat)() override;
	STDMETHOD(Redo)() override;
	STDMETHOD(Undo)() override;
	STDMETHOD(Execute)(/*[in]*/IWBFLTransaction* txn) override;
   STDMETHOD(BeginMacro)(/*[in]*/  VARIANT nameOrMacro) override;
   STDMETHOD(ExecuteMacro)() override;
   STDMETHOD(AbortMacro)() override;
};

#endif //__TRANSACTIONMGR_H_
