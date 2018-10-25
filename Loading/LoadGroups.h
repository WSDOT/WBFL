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

// LoadGroups.h : Declaration of the CLoadGroups

#ifndef __LOADGROUPS_H_
#define __LOADGROUPS_H_

#include "resource.h"       // main symbols
#include "LoadingCP.h"
#include "ComCollections.h"

class CLoadGroups;
typedef  CComBSTRKeyedCollection<ldILoadGroups, ldILoadGroup, ldIEnumLoadGroup, &IID_ldIEnumLoadGroup, CollectionIndexType> LoadGroupCollImpl;
typedef CPersistentCollection<CLoadGroups, LoadGroupCollImpl, CollectionIndexType> PersistentLoadGroupCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CLoadGroups
class ATL_NO_VTABLE CLoadGroups : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLoadGroups, &CLSID_ldLoadGroups>,
	public ISupportErrorInfo,
   public PersistentLoadGroupCollImpl,
	public IConnectionPointContainerImpl<CLoadGroups>,
	public CProxyDLoadGroupsEvents< CLoadGroups >,
   public IObjectSafetyImpl<CLoadGroups,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ldILoadGroupEvents
{
public:
	CLoadGroups()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADGROUPS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadGroups)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   // Chains in the COM_MAP in the persistence impl
   COM_INTERFACE_ENTRY_CHAIN(PersistentLoadGroupCollImpl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ldILoadGroupEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadGroups)
CONNECTION_POINT_ENTRY(IID_ldILoadGroupsEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ldILoadGroupEvents
   STDMETHOD(OnLoadGroupChanged)(/*[in]*/ldILoadGroup* LoadGroup,ldLoadingChangeType type);
   STDMETHOD(OnLoadGroupRenamed)(BSTR oldNam, BSTR newNam);

// ldILoadGroups
public:
	STDMETHOD(Clone)(/*[out, retval]*/ ldILoadGroups** clone);

protected:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal);
   virtual HRESULT OnAfterAdd( StoredType* pVal);
   virtual HRESULT OnBeforeRemove ( StoredType* pVal);
   virtual HRESULT OnAfterRemove( BSTR name);

public:
   virtual void FinalRelease();
};

#endif //__LOADGROUPS_H_
