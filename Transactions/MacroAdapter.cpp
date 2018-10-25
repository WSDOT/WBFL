///////////////////////////////////////////////////////////////////////
// Transactions - Utility library for managing transactions, undo/redo
// Copyright © 1999-2013  Washington State Department of Transportation
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

// MacroAdapter.cpp : Implementation of CMacroAdapter
#include "stdafx.h"
#include "WBFLTransactions.h"
#include "MacroAdapter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMacroAdapter

STDMETHODIMP CMacroAdapter::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMacroAdapter
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
	
STDMETHODIMP CMacroAdapter::Execute()
{
   return (m_Macro ? m_Macro->Execute() : S_OK);
}

STDMETHODIMP CMacroAdapter::Undo()
{
   return (m_Macro ? m_Macro->Undo() : S_OK);
}

STDMETHODIMP CMacroAdapter::get_Name(BSTR *pVal)
{
   return (m_Macro ? m_Macro->get_Name(pVal) : S_OK);
}

STDMETHODIMP CMacroAdapter::get_IsUndoable(VARIANT_BOOL *pVal)
{
   return (m_Macro ? m_Macro->get_IsUndoable(pVal) : S_OK);
}

STDMETHODIMP CMacroAdapter::get_IsRepeatable(VARIANT_BOOL *pVal)
{
   return (m_Macro ? m_Macro->get_IsRepeatable(pVal) : S_OK);
}

STDMETHODIMP CMacroAdapter::get_Macro(IMacroTransaction* *pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_Macro;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CMacroAdapter::putref_Macro(IMacroTransaction* newVal)
{
   CHECK_IN(newVal);
   m_Macro = newVal;
   return S_OK;
}
