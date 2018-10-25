///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2013  Washington State Department of Transportation
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

// LoadCombinations.h : Declaration of the CLoadCombinations

#ifndef __LOADCOMBINATIONS_H_
#define __LOADCOMBINATIONS_H_

#include "resource.h"       // main symbols
#include "LoadingCP.h"
#include "ComCollections.h"

class CLoadCombinations;
typedef  CComBSTRKeyedCollection<ldILoadCombinations, ldILoadCombination, ldIEnumLoadCombination, &IID_ldIEnumLoadCombination, CollectionIndexType> LoadCombinationCollImpl;
typedef CPersistentCollection<CLoadCombinations, LoadCombinationCollImpl, CollectionIndexType> PersistentLoadCombinationCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinations
class ATL_NO_VTABLE CLoadCombinations : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLoadCombinations, &CLSID_ldLoadCombinations>,
	public ISupportErrorInfo,
   public PersistentLoadCombinationCollImpl,
	public IConnectionPointContainerImpl<CLoadCombinations>,
	public CProxyDLoadCombinationsEvents< CLoadCombinations >,
   public IObjectSafetyImpl<CLoadCombinations,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ldILoadCombinationEvents
{
public:
   CLoadCombinations()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADCOMBINATIONS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCombinations)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   // Chains in the COM_MAP in the persistence impl
   COM_INTERFACE_ENTRY_CHAIN(PersistentLoadCombinationCollImpl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ldILoadCombinationEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCombinations)
CONNECTION_POINT_ENTRY(IID_ldILoadCombinationsEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ldILoadCombinationEvents
   STDMETHOD(OnLoadCombinationChanged)(/*[in]*/ldILoadCombination* LoadCombination,ldLoadingChangeType type);
   STDMETHOD(OnLoadCombinationRenamed)(BSTR oldNam, BSTR newNam);

// ldILoadCombinations
public:
	STDMETHOD(Clone)(/*[out, retval]*/ ldILoadCombinations** clone);

protected:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal);
   virtual HRESULT OnAfterAdd( StoredType* pVal);
   virtual HRESULT OnBeforeRemove ( StoredType* pVal);
   virtual HRESULT OnAfterRemove( BSTR name);

public:
   virtual void FinalRelease();

};

#endif //__LOADCOMBINATIONS_H_
