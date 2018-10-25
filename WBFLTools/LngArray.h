///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
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

// LngArray.h : Declaration of the CLngArray

#ifndef __LngArray_H_
#define __LngArray_H_

#include "resource.h"       // main symbols

#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLngArray
class ATL_NO_VTABLE CLongArray : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLongArray, &CLSID_LongArray>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CLongArray,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ILongArray
{
public:
	CLongArray()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LONGARRAY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLongArray)
	COM_INTERFACE_ENTRY(ILongArray)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILngArray
public:
	STDMETHOD(Find)(/*[in]*/LONG value, /*[out,retval]*/CollectionIndexType* fndIndex) override;
	STDMETHOD(ReDim)(/*[in]*/CollectionIndexType size) override;
	STDMETHOD(Clone)(/*[out,retval]*/ILongArray* *clone) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(Reserve)(/*[in]*/CollectionIndexType count) override;
	STDMETHOD(Insert)(/*[in]*/CollectionIndexType relPosition, /*[in]*/LONG item) override;
	STDMETHOD(Remove)(/*[in]*/CollectionIndexType relPosition) override;
	STDMETHOD(Add)(/*[in]*/LONG item) override;
	STDMETHOD(get_Item)(/*[in]*/CollectionIndexType relPosition, /*[out, retval]*/ LONG *pVal) override;
	STDMETHOD(put_Item)(/*[in]*/CollectionIndexType relPosition, /*[in]*/ LONG newVal) override;
	STDMETHOD(get__NewEnum)(struct IUnknown ** ) override;
	STDMETHOD(get__EnumElements)(struct IEnumLongArray ** ) override;

protected:
   typedef std::vector<LONG>       ContainerType;
   typedef ContainerType::iterator ContainerIterator;
   ContainerType m_Values;
};
#endif //__LngArray_H_
