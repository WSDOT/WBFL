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

// VehicularLoads.h : Declaration of the CVehicularLoads

#ifndef __VEHICULARLOADS_H_
#define __VEHICULARLOADS_H_

#include "resource.h"       // main symbols
#include "LiveLoadCP.h"
#include <WBFLComCollections.h>

class CVehicularLoads;
typedef  CComVectorCollection<IVehicularLoads, IVehicularLoad, IEnumVehicularLoad, &IID_IEnumVehicularLoad,VehicleIndexType> VehicularLoadCollImpl;
typedef CPersistentCollection<CVehicularLoads, VehicularLoadCollImpl,VehicleIndexType> PersistentVehicularLoadCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CVehicularLoads
class ATL_NO_VTABLE CVehicularLoads : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVehicularLoads, &CLSID_VehicularLoads>,
	public ISupportErrorInfo,
   public PersistentVehicularLoadCollImpl,
	public IConnectionPointContainerImpl<CVehicularLoads>,
	public CProxyDVehicularLoadsEvents< CVehicularLoads >,
   public IObjectSafetyImpl<CVehicularLoads,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IVehicularLoadEvents
{
public:
	CVehicularLoads()
	{
	}

   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_VEHICULARLOADS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVehicularLoads)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   // Chains in the COM_MAP in the persistence impl
   COM_INTERFACE_ENTRY_CHAIN(PersistentVehicularLoadCollImpl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IVehicularLoadEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CVehicularLoads)
CONNECTION_POINT_ENTRY(IID_IVehicularLoadsEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// Events
   STDMETHOD(OnVehicularLoadChanged)(/*[in]*/IVehicularLoad* VehicularLoad,ChangeType type) override;

// IVehicularLoads
public:
	STDMETHOD(Clone)(/*[out, retval]*/ IVehicularLoads** clone) override;

protected:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal) override;
   virtual HRESULT OnAfterAdd( StoredType* pVal, VehicleIndexType idx) override;
   virtual HRESULT OnBeforeRemove ( StoredType* pVal, VehicleIndexType idx) override;
   virtual HRESULT OnAfterRemove( VehicleIndexType idx) override;

};

#endif //__VEHICULARLOADS_H_
