///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2020  Washington State Department of Transportation
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

// LoadCases.h : Declaration of the CLoadCases

#ifndef __LOADCASES_H_
#define __LOADCASES_H_

#include "resource.h"       // main symbols
#include "LoadingCP.h"

#include "ComCollections.h"

class CLoadCases;
typedef  CComBSTRKeyedCollection<ldILoadCases, ldILoadCase, ldIEnumLoadCase, &IID_ldIEnumLoadCase, CollectionIndexType> LoadCaseCollImpl;
typedef CPersistentCollection<CLoadCases, LoadCaseCollImpl, CollectionIndexType> PersistentLoadCaseCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CLoadCases
class ATL_NO_VTABLE CLoadCases : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLoadCases, &CLSID_ldLoadCases>,
	public ISupportErrorInfo,
   public PersistentLoadCaseCollImpl,
	public IConnectionPointContainerImpl<CLoadCases>,
	public CProxyDLoadCasesEvents< CLoadCases >,
   public IObjectSafetyImpl<CLoadCases,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ldILoadCaseEvents
{
public:
	CLoadCases()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADCASES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCases)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   // Chains in the COM_MAP in the persistence impl
   COM_INTERFACE_ENTRY_CHAIN(PersistentLoadCaseCollImpl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ldILoadCaseEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCases)
CONNECTION_POINT_ENTRY(IID_ldILoadCasesEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ldILoadCaseEvents
   STDMETHOD(OnLoadCaseChanged)(/*[in]*/ldILoadCase* LoadCase,ldLoadingChangeType type) override;
   STDMETHOD(OnLoadCaseRenamed)(BSTR oldNam, BSTR newNam) override;

// ldILoadCases
public:
	STDMETHOD(Clone)(/*[out, retval]*/ ldILoadCases** clone) override;

protected:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal) override;
   virtual HRESULT OnAfterAdd( StoredType* pVal) override;
   virtual HRESULT OnBeforeRemove ( StoredType* pVal) override;
   virtual HRESULT OnAfterRemove( BSTR name) override;

public:
   void FinalRelease();
};

#endif //__LOADCASES_H_
