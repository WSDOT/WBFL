///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
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

// POIs.h : Declaration of the CPOIs

#ifndef __POIS_H_
#define __POIS_H_

#include "resource.h"       // main symbols
#include "POICP.h"
#include <WBFLComCollections.h>

class CPOIs;
typedef  CComIDKeyedCollection<IPOIs, IPOI, IEnumPOI, &IID_IEnumPOI,CollectionIndexType> POICollImpl;
typedef CPersistentCollection<CPOIs, POICollImpl,CollectionIndexType> PersistentPOICollImpl;

/////////////////////////////////////////////////////////////////////////////
// CPOIs
class ATL_NO_VTABLE CPOIs : 
	public CComObjectRootEx<CComSingleThreadModel>,
// public CComRefCountTracer<CPOIs,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPOIs, &CLSID_POIs>,
	public ISupportErrorInfo,
   public PersistentPOICollImpl,
	public IConnectionPointContainerImpl<CPOIs>,
	public CProxyDPOIsEvents< CPOIs >,
   public IObjectSafetyImpl<CPOIs,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IPOIEvents
{
public:
	CPOIs()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_POIS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPOIs)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   // Chains in the COM_MAP in the persistence impl
   COM_INTERFACE_ENTRY_CHAIN(PersistentPOICollImpl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPOIEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPOIs)
CONNECTION_POINT_ENTRY(IID_IPOIsEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPOIEvents
   STDMETHOD(OnPOIChanged)(/*[in]*/IPOI* POI,ChangeType type) override;
   STDMETHOD(OnPOIRenamed)(/*[in]*/PoiIDType oldID, /*[in]*/ PoiIDType newID) override;

// IPOIs
public:
	STDMETHOD(Clone)(/*[out, retval]*/ IPOIs** clone) override;

protected:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal) override;
   virtual HRESULT OnAfterAdd( StoredType* pVal) override;
   virtual HRESULT OnBeforeRemove ( StoredType* pVal) override;
   virtual HRESULT OnAfterRemove( PoiIDType id) override;

public:
   void FinalRelease();
};

#endif //__POIS_H_
