///////////////////////////////////////////////////////////////////////
// Transactions - Utility library for managing transactions, undo/redo
// Copyright © 1999-2012  Washington State Department of Transportation
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

// MacroTransaction.h : Declaration of the CMacroTransaction

#ifndef __MACROTRANSACTION_H_
#define __MACROTRANSACTION_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CMacroTransaction
class ATL_NO_VTABLE CMacroTransaction : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMacroTransaction, &CLSID_MacroTransaction>,
	public ISupportErrorInfo,
	public IMacroTransaction
{
public:
   CMacroTransaction() :
      m_bstrName("Macro")
	{
      m_bIsUndoable   = VARIANT_TRUE;
      m_bIsRepeatable = VARIANT_TRUE;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MACROTRANSACTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMacroTransaction)
	COM_INTERFACE_ENTRY(IMacroTransaction)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   CComBSTR m_bstrName;
   VARIANT_BOOL m_bIsUndoable;
   VARIANT_BOOL m_bIsRepeatable;

   typedef CAdapt<CComPtr<ITransaction> > TxnType;
   typedef std::vector<TxnType> TxnContainer;

   TxnContainer m_Transactions;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMacroTransaction
public:
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(get_IsRepeatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_IsUndoable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(AddTransaction)(/*[in]*/ ITransaction* txn);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(Undo)();
	STDMETHOD(Execute)();
};

#endif //__MACROTRANSACTION_H_
