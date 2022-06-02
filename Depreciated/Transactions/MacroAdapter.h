///////////////////////////////////////////////////////////////////////
// Transactions - Utility library for managing transactions, undo/redo
// Copyright © 1999-2022  Washington State Department of Transportation
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

// MacroAdapter.h : Declaration of the CMacroAdapter

#ifndef __MACROADAPTER_H_
#define __MACROADAPTER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMacroAdapter
class ATL_NO_VTABLE CMacroAdapter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMacroAdapter, &CLSID_WBFLMacroAdapter>,
	public ISupportErrorInfo,
	public IWBFLMacroAdapter
{
public:
	CMacroAdapter()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MACROADAPTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMacroAdapter)
	COM_INTERFACE_ENTRY(IWBFLMacroAdapter)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   CComPtr<IWBFLMacroTransaction> m_Macro;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IWBFLMacroAdapter
public:
	STDMETHOD(Execute)() override;
	STDMETHOD(Undo)() override;
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal) override;
   STDMETHOD(get_IsUndoable)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(get_IsRepeatable)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(get_Macro)(/*[out, retval]*/ IWBFLMacroTransaction* *pVal) override;
	STDMETHOD(putref_Macro)(/*[in]*/ IWBFLMacroTransaction* newVal) override;
};

#endif //__MACROADAPTER_H_
