///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
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

// UnkArray.h : Declaration of the CUnkArray

#ifndef __UNKARRAY_H_
#define __UNKARRAY_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CUnkArray
class ATL_NO_VTABLE CUnkArray : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUnkArray, &CLSID_UnkArray>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CUnkArray,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IUnkArray
{
public:
	CUnkArray()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_UNKARRAY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUnkArray)
	COM_INTERFACE_ENTRY(IUnkArray)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUnkArray
public:
	STDMETHOD(Clone)(/*[out,retval]*/IUnkArray* *clone);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(Clear)();
	STDMETHOD(Reserve)(/*[in]*/CollectionIndexType count);
	STDMETHOD(Insert)(/*[in]*/CollectionIndexType relPosition, /*[in]*/IUnknown* item);
	STDMETHOD(Remove)(/*[in]*/CollectionIndexType relPosition);
	STDMETHOD(Add)(/*[in]*/IUnknown* item);
	STDMETHOD(get_Item)(/*[in]*/CollectionIndexType relPosition, /*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(put_Item)(/*[in]*/CollectionIndexType relPosition, /*[in]*/ IUnknown* newVal);
	STDMETHOD(get__NewEnum)(struct IUnknown ** );
	STDMETHOD(get__EnumElements)(struct IEnumUnkArray ** );

   typedef CAdapt<CComPtr<IUnknown> > MemberType;
   typedef std::vector<MemberType>    ContainerType;
   typedef ContainerType::iterator    ContainerIterator;

protected:
   ContainerType m_Values;
};

#endif //__UNKARRAY_H_
