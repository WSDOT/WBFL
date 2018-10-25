///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2014  Washington State Department of Transportation
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

// DblArray.h : Declaration of the CDblArray

#ifndef __DBLARRAY_H_
#define __DBLARRAY_H_

#include "resource.h"       // main symbols

#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CDblArray
class ATL_NO_VTABLE CDblArray : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDblArray, &CLSID_DblArray>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CDblArray,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IDblArray
{
public:
	CDblArray()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DBLARRAY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDblArray)
	COM_INTERFACE_ENTRY(IDblArray)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDblArray
public:
	STDMETHOD(ReDim)(/*[in]*/CollectionIndexType size);
	STDMETHOD(Clone)(/*[out,retval]*/IDblArray* *clone);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(Clear)();
	STDMETHOD(Reserve)(/*[in]*/CollectionIndexType count);
	STDMETHOD(Insert)(/*[in]*/CollectionIndexType relPosition, /*[in]*/Float64 item);
	STDMETHOD(Remove)(/*[in]*/CollectionIndexType relPosition);
	STDMETHOD(Add)(/*[in]*/Float64 item);
	STDMETHOD(get_Item)(/*[in]*/CollectionIndexType relPosition, /*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Item)(/*[in]*/CollectionIndexType relPosition, /*[in]*/ Float64 newVal);
	STDMETHOD(get__NewEnum)(struct IUnknown ** );
	STDMETHOD(get__EnumElements)(struct IEnumDblArray ** );

protected:
   typedef std::vector<Float64>       ContainerType;
   typedef ContainerType::iterator ContainerIterator;
   ContainerType m_Values;
};

#endif //__DBLARRAY_H_
