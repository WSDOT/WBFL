///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2023  Washington State Department of Transportation
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

// IndexArray.h : Declaration of the CIndexArray

#pragma once

#include "resource.h"       // main symbols

#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CIndexArray
class ATL_NO_VTABLE CIndexArray : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIndexArray, &CLSID_IndexArray>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CIndexArray,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IIndexArray
{
public:
	CIndexArray()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_INDEXARRAY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIndexArray)
	COM_INTERFACE_ENTRY(IIndexArray)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IIndexArray
public:
	STDMETHOD(Find)(/*[in]*/CollectionIndexType value, /*[out,retval]*/CollectionIndexType* fndIndex) override;
	STDMETHOD(ReDim)(/*[in]*/CollectionIndexType size) override;
	STDMETHOD(Clone)(/*[out,retval]*/IIndexArray* *clone) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(Reserve)(/*[in]*/CollectionIndexType count) override;
	STDMETHOD(Insert)(/*[in]*/CollectionIndexType relPosition, /*[in]*/CollectionIndexType item) override;
	STDMETHOD(Remove)(/*[in]*/CollectionIndexType relPosition) override;
	STDMETHOD(Add)(/*[in]*/CollectionIndexType item) override;
	STDMETHOD(get_Item)(/*[in]*/CollectionIndexType relPosition, /*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(put_Item)(/*[in]*/CollectionIndexType relPosition, /*[in]*/ CollectionIndexType newVal) override;
	STDMETHOD(get__NewEnum)(struct IUnknown ** ) override;
	STDMETHOD(get__EnumElements)(struct IEnumIndexArray ** ) override;
   STDMETHOD(Assign)(/*[in]*/CollectionIndexType numElements, /*[in]*/CollectionIndexType value) override;

protected:
   using ContainerType = std::vector<CollectionIndexType>;
	using ContainerIterator = ContainerType::iterator;
   ContainerType m_Values;
};
