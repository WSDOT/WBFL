///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// BstrArray.h : Declaration of the CBstrArray

#ifndef __BSTRARRAY_H_
#define __BSTRARRAY_H_

#include "resource.h"       // main symbols
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CBstrArray
class ATL_NO_VTABLE CBstrArray : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBstrArray, &CLSID_BstrArray>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CBstrArray,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IBstrArray
{
public:
	CBstrArray()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BSTRARRAY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBstrArray)
	COM_INTERFACE_ENTRY(IBstrArray)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IBstrArray
public:
	STDMETHOD(Find)(/*[in]*/BSTR value, /*[out,retval]*/CollectionIndexType* fndIndex);
	STDMETHOD(ReDim)(/*[in]*/CollectionIndexType size);
	STDMETHOD(Clone)(/*[out,retval]*/IBstrArray* *clone);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(Clear)();
	STDMETHOD(Reserve)(/*[in]*/CollectionIndexType count);
	STDMETHOD(Insert)(/*[in]*/CollectionIndexType relPosition, /*[in]*/BSTR item);
	STDMETHOD(Remove)(/*[in]*/CollectionIndexType relPosition);
	STDMETHOD(Add)(/*[in]*/BSTR item);
	STDMETHOD(get_Item)(/*[in]*/CollectionIndexType relPosition, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Item)(/*[in]*/CollectionIndexType relPosition, /*[in]*/ BSTR newVal);
	STDMETHOD(get__NewEnum)(struct IUnknown ** );
	STDMETHOD(get__EnumElements)(struct IEnumBstrArray ** );

protected:
   typedef std::vector< CAdapt<CComBSTR> >       ContainerType;
   typedef ContainerType::iterator ContainerIterator;
   ContainerType m_Values;

};

#endif //__BSTRARRAY_H_
