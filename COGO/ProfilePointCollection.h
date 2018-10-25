///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2016  Washington State Department of Transportation
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

// ProfilePointCollection.h : Declaration of the CProfilePointCollection

#ifndef __PROFILEPOINTCOLLECTION_H_
#define __PROFILEPOINTCOLLECTION_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"
#include "Collections.h"

class CProfilePointCollection;
typedef PersistentKeyedCollection<CProfilePointCollection,IProfilePointCollection,&IID_IProfilePointCollection,CogoElementKey,IProfilePoint> ProfilePointCollectionImpl;

/////////////////////////////////////////////////////////////////////////////
// CProfilePointCollection
class ATL_NO_VTABLE CProfilePointCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProfilePointCollection, &CLSID_ProfilePointCollection>,
	public IConnectionPointContainerImpl<CProfilePointCollection>,
	public ProfilePointCollectionImpl,
   public IProfilePointEvents,
   public CProxyDProfilePointCollectionEvents< CProfilePointCollection >
{
public:
	CProfilePointCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PROFILEPOINTCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProfilePointCollection)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IProfilePointEvents)

   COM_INTERFACE_ENTRY_CHAIN(ProfilePointCollectionImpl)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CProfilePointCollection)
   CONNECTION_POINT_ENTRY(IID_IProfilePointCollectionEvents)
END_CONNECTION_POINT_MAP()

   virtual CComBSTR GetCollectionName() { return CComBSTR("ProfilePoints"); }
   virtual CComBSTR GetItemName() { return CComBSTR("ProfilePoint"); }

// IProfilePointCollection
public:
   STDMETHOD(Clone)(/*[out,retval]*/ IProfilePointCollection* *clone);
   STDMETHOD(get__EnumProfilePoints)(/*[out,retval]*/ IEnumProfilePoints** ppenum);
	STDMETHOD(get_Factory)(/*[out,retval]*/IProfilePointFactory* *factory);
   STDMETHOD(putref_Factory)(/*[in]*/IProfilePointFactory* factory);
	STDMETHOD(Clear)();
	STDMETHOD(Add)(/*[in]*/ CogoElementKey key,/*[in]*/ VARIANT varStation,/*[in]*/ Float64 elevation,/*[out,retval]*/IProfilePoint* *pp);
	STDMETHOD(AddEx)(/*[in]*/ CogoElementKey key,/*[in]*/ IProfilePoint* newVal);
	STDMETHOD(Remove)(/*[in]*/ CogoElementKey key);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(get_Item)(/*[in]*/ CogoElementKey key, /*[out, retval]*/ IProfilePoint* *pVal);
	STDMETHOD(putref_Item)(/*[in]*/ CogoElementKey key, /*[in]*/ IProfilePoint* newVal);
// STDMETHOD(get__NewEnum)(IUnknown** retval);
   STDMETHOD(get__EnumKeys)(IEnumKeys** ppenum);
	STDMETHOD(FindKey)(/*[in]*/ IProfilePoint* pp,/*[out,retval]*/CogoElementKey* key);
	STDMETHOD(Key)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoElementKey* key);

// IProfilePointEvents
public:
	STDMETHOD(OnProfilePointChanged)(IProfilePoint* pp);

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);
   HRESULT ProfilePointNotFound(CogoElementKey key);
   HRESULT ProfilePointAlreadyDefined(CogoElementKey key);
   HRESULT ProfilePointKeyError(CogoElementKey key,UINT nHelpString,HRESULT hRes);

   void Advise(CogoElementKey key,IProfilePoint* pp);
   void Unadvise(CogoElementKey key,IProfilePoint* pp);
   void UnadviseAll();
   std::map<CogoElementKey,DWORD> m_Cookies;

   CComPtr<IProfilePointFactory> m_Factory;
};

#endif //__PROFILEPOINTCOLLECTION_H_
