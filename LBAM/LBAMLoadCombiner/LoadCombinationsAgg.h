///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright (C) 2009  Washington State Department of Transportation
//                     Bridge and Structures Office
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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILoadCombinationsAgg
public:
// ILoadCombinations
   STDMETHOD(get_Item)(/*[in]*/CollectionIndexType index, /*[out,retval]*/ ILoadCombination* *pVal);
   STDMETHOD(get__NewEnum)(/*[out,retval]*/ IUnknown** retval);  
   STDMETHOD(get_Count)(/*[out,retval]*/ CollectionIndexType *pVal);
   STDMETHOD(get__EnumElements)(/*[out,retval]*/ IEnumLoadCombination* *pVal);
   STDMETHOD(Find)(/*[in]*/BSTR name, /*[out,retval]*/ILoadCombination**);
   STDMETHOD(Add)(/*[in]*/ILoadCombination*);
   STDMETHOD(RemoveByName)(/*[in]*/BSTR name);
   STDMETHOD(RemoveByIndex)(/*[in]*/CollectionIndexType index, /*[out,retval]*/BSTR* name);
   STDMETHOD(Clone)(/*[out,retval]*/ILoadCombinations**);
   STDMETHOD(Clear)();

   // internal implementation
   CComPtr<ILoadCombinations> m_LoadCombinations;
};

#endif //__LoadCombinationsAgg_H_
