///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2023  Washington State Department of Transportation
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

// LoadCase.h : Declaration of the CLoadCase

#ifndef __LOADCASE_H_
#define __LOADCASE_H_

#include "resource.h"       // main symbols
#include "LoadingCP.h"

#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLoadCase
class ATL_NO_VTABLE CLoadCase : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CLoadCase,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CLoadCase, &CLSID_ldLoadCase>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLoadCase>,
	public ldILoadCase,
   public IPersistImpl<CLoadCase>,
	public IStructuredStorage2,
   public IObjectSafetyImpl<CLoadCase,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDLoadCaseEvents< CLoadCase >
{
public:
   CLoadCase():
   m_ItemData(0)  // set to integer as default
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADCASE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCase)
	COM_INTERFACE_ENTRY(ldILoadCase)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCase)
CONNECTION_POINT_ENTRY(IID_ldILoadCaseEvents)
END_CONNECTION_POINT_MAP()

// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ldILoadCase
public:
	STDMETHOD(get_LoadGroupCount)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(Clone)(/*[out,retval]*/ldILoadCase** clone) override;
	STDMETHOD(RemoveLoadGroupByIndex)(/*[in]*/CollectionIndexType index) override;
	STDMETHOD(RemoveLoadGroup)(/*[in]*/BSTR loadGroupName) override;
	STDMETHOD(SetLoadGroup)(/*[in]*/CollectionIndexType index, /*[in]*/BSTR newName) override;
	STDMETHOD(GetLoadGroup)(/*[in]*/CollectionIndexType index, /*[out]*/BSTR* loadGroupName) override;
	STDMETHOD(AddLoadGroup)(/*[in]*/BSTR loadGroupName) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(get_ItemData)(/*[out, retval]*/ VARIANT *pVal) override;
	STDMETHOD(put_ItemData)(/*[in]*/ VARIANT newVal) override;
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal) override;
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal) override;
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal) override;
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal) override;

protected:
   CComBSTR     m_Name;
   CComBSTR     m_Description;
   CComVariant  m_ItemData;

   using LoadGroupContainer = std::vector<CComBSTR>;
	using LoadGroupIterator = LoadGroupContainer::iterator;

   LoadGroupContainer m_LoadGroups;
};

#endif //__LOADCASE_H_
