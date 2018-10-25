///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2011  Washington State Department of Transportation
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
#include "CombinationCP.h"

#include <WBFLComCollections.h>
#include "LBAMCP.h"

class CLoadCases;
typedef  CComBSTRKeyedCollection<ILoadCases, ILoadCase, IEnumLoadCase, &IID_IEnumLoadCase,CollectionIndexType> LoadCaseCollImpl;
typedef CPersistentCollection<CLoadCases, LoadCaseCollImpl,CollectionIndexType> PersistentLoadCaseCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CLoadCases
class ATL_NO_VTABLE CLoadCases : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLoadCases, &CLSID_LoadCases>,
	public ISupportErrorInfo,
   public PersistentLoadCaseCollImpl,
	public IConnectionPointContainerImpl<CLoadCases>,
	public CProxyDLoadCasesEvents< CLoadCases >,
   public IObjectSafetyImpl<CLoadCases,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ILoadCaseEvents
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
   COM_INTERFACE_ENTRY(ILoadCaseEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCases)
CONNECTION_POINT_ENTRY(IID_ILoadCasesEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILoadCaseEvents
   STDMETHOD(OnLoadCaseChanged)(/*[in]*/ILoadCase* LoadCase,ChangeType type);
   STDMETHOD(OnLoadCaseRenamed)(BSTR oldNam, BSTR newNam);

// ILoadCases
public:
	STDMETHOD(Clone)(/*[out, retval]*/ ILoadCases** clone);

protected:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal);
   virtual HRESULT OnAfterAdd( StoredType* pVal);
   virtual HRESULT OnBeforeRemove ( StoredType* pVal);
   virtual HRESULT OnAfterRemove( BSTR name);

public:
   virtual void FinalRelease();
};

#endif //__LOADCASES_H_
