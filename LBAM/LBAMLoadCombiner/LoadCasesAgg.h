///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright � 1999-2025  Washington State Department of Transportation
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

// LoadCasesAgg.h : Declaration of the CLoadCasesAgg

#ifndef __LOADCASESAGG_H_
#define __LOADCASESAGG_H_

#include "resource.h"       // main symbols
#include "WBFLLBAM.h"

/////////////////////////////////////////////////////////////////////////////
// CLoadCasesAgg
class ATL_NO_VTABLE CLoadCasesAgg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public ILoadCases
{
public:

	CLoadCasesAgg()
	{
	}

	~CLoadCasesAgg()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCasesAgg)
	COM_INTERFACE_ENTRY(ILoadCases)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCasesAgg)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILoadCasesAgg
public:
// ILoadCases
   STDMETHOD(get_Item)(/*[in]*/IndexType index, /*[out,retval]*/ ILoadCase* *pVal) override;
   STDMETHOD(get__NewEnum)(/*[out,retval]*/ IUnknown** retval) override;  
   STDMETHOD(get_Count)(/*[out,retval]*/ IndexType *pVal) override;
   STDMETHOD(get__EnumElements)(/*[out,retval]*/ IEnumLoadCase* *pVal) override;
   STDMETHOD(Find)(/*[in]*/BSTR name, /*[out,retval]*/ILoadCase**) override;
   STDMETHOD(Add)(/*[in]*/ILoadCase*) override;
   STDMETHOD(RemoveByName)(/*[in]*/BSTR name) override;
   STDMETHOD(RemoveByIndex)(/*[in]*/IndexType index, /*[out,retval]*/BSTR* name) override;
   STDMETHOD(Clone)(/*[out,retval]*/ILoadCases**) override;
   STDMETHOD(Clear)() override;

   // internal implementation
   CComPtr<ILoadCases> m_LoadCases;
};

#endif //__LoadCasesAgg_H_
