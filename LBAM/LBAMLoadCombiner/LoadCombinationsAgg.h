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

// LoadCombinationsAgg.h : Declaration of the CLoadCombinationsAgg

#ifndef __LOADCOMBINATIONSAGG_H_
#define __LOADCOMBINATIONSAGG_H_

#include "resource.h"       // main symbols
#include "WBFLLBAM.h"

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationsAgg
class ATL_NO_VTABLE CLoadCombinationsAgg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CLoadCombinationsAgg,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ILoadCombinations
{
public:

	CLoadCombinationsAgg()
	{
	}

	~CLoadCombinationsAgg()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCombinationsAgg)
	COM_INTERFACE_ENTRY(ILoadCombinations)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCombinationsAgg)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILoadCombinationsAgg
public:
// ILoadCombinations
   STDMETHOD(get_Item)(/*[in]*/IndexType index, /*[out,retval]*/ ILoadCombination* *pVal) override;
   STDMETHOD(get__NewEnum)(/*[out,retval]*/ IUnknown** retval) override;  
   STDMETHOD(get_Count)(/*[out,retval]*/ IndexType *pVal) override;
   STDMETHOD(get__EnumElements)(/*[out,retval]*/ IEnumLoadCombination* *pVal) override;
   STDMETHOD(Find)(/*[in]*/BSTR name, /*[out,retval]*/ILoadCombination**) override;
   STDMETHOD(Add)(/*[in]*/ILoadCombination*) override;
   STDMETHOD(RemoveByName)(/*[in]*/BSTR name) override;
   STDMETHOD(RemoveByIndex)(/*[in]*/IndexType index, /*[out,retval]*/BSTR* name) override;
   STDMETHOD(Clone)(/*[out,retval]*/ILoadCombinations**) override;
   STDMETHOD(Clear)() override;

   // internal implementation
   CComPtr<ILoadCombinations> m_LoadCombinations;
};

#endif //__LoadCombinationsAgg_H_
