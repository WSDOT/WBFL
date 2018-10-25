///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// ProfilePointCollection.h : Declaration of the CProfilePointCollection

#ifndef __PROFILEPOINTCOLLECTION_H_
#define __PROFILEPOINTCOLLECTION_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"
#include "Collections.h"

class CProfilePointCollection;
typedef PersistentIDCollection<CProfilePointCollection,IProfilePointCollection,&IID_IProfilePointCollection,CogoObjectID,IProfilePoint> ProfilePointCollectionImpl;

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

   CComBSTR GetCollectionName() { return CComBSTR("ProfilePoints"); }
   CComBSTR GetItemName() { return CComBSTR("ProfilePoint"); }

// IProfilePointCollection
public:
   STDMETHOD(Clone)(/*[out,retval]*/ IProfilePointCollection* *clone) override;
   STDMETHOD(get__EnumProfilePoints)(/*[out,retval]*/ IEnumProfilePoints** ppenum) override;
	STDMETHOD(get_Factory)(/*[out,retval]*/IProfilePointFactory* *factory) override;
   STDMETHOD(putref_Factory)(/*[in]*/IProfilePointFactory* factory) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(Add)(/*[in]*/ CogoObjectID id,/*[in]*/ VARIANT varStation,/*[in]*/ Float64 elevation,/*[out,retval]*/IProfilePoint* *pp) override;
	STDMETHOD(AddEx)(/*[in]*/ CogoObjectID id,/*[in]*/ IProfilePoint* newVal) override;
	STDMETHOD(Remove)(/*[in]*/ CogoObjectID id) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_Item)(/*[in]*/ CogoObjectID id, /*[out, retval]*/ IProfilePoint* *pVal) override;
	STDMETHOD(putref_Item)(/*[in]*/ CogoObjectID id, /*[in]*/ IProfilePoint* newVal) override;
// STDMETHOD(get__NewEnum)(IUnknown** retval) override;
   STDMETHOD(get__EnumIDs)(IEnumIDs** ppenum) override;
	STDMETHOD(FindID)(/*[in]*/ IProfilePoint* pp,/*[out,retval]*/CogoObjectID* ID) override;
	STDMETHOD(ID)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoObjectID* ID) override;

// IProfilePointEvents
public:
	STDMETHOD(OnProfilePointChanged)(IProfilePoint* pp) override;

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);
   HRESULT ProfilePointNotFound(CogoObjectID id);
   HRESULT ProfilePointAlreadyDefined(CogoObjectID id);
   HRESULT ProfilePointIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes);

   void Advise(CogoObjectID id,IProfilePoint* pp);
   void Unadvise(CogoObjectID id,IProfilePoint* pp);
   void UnadviseAll();
   std::map<CogoObjectID,DWORD> m_Cookies;

   CComPtr<IProfilePointFactory> m_Factory;
};

#endif //__PROFILEPOINTCOLLECTION_H_
