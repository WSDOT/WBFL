///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2010  Washington State Department of Transportation
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

// LiveLoadModel.h : Declaration of the CLiveLoadModel

#ifndef __LIVELOADMODEL_H_
#define __LIVELOADMODEL_H_

#include "resource.h"       // main symbols
#include "LiveLoadCP.h"

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadModel
class ATL_NO_VTABLE CLiveLoadModel : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CLiveLoadModel,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CLiveLoadModel, &CLSID_LiveLoadModel>,
	public ISupportErrorInfo, 
	public IConnectionPointContainerImpl<CLiveLoadModel>,
	public ILiveLoadModel,
   public IPersistImpl<CLiveLoadModel>,
	public IStructuredStorage2,
	public CProxyDLiveLoadModelEvents< CLiveLoadModel >,
   public IObjectSafetyImpl<CLiveLoadModel,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IVehicularLoadsEvents
{
public:
   CLiveLoadModel():
   m_DistributionFactorType(dftNone),
   m_VehicularLoadsCookie(0)
	{
	}

   STDMETHOD(FinalConstruct)();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_LIVELOADMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLiveLoadModel)
	COM_INTERFACE_ENTRY(ILiveLoadModel)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IVehicularLoadsEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLiveLoadModel)
CONNECTION_POINT_ENTRY(IID_ILiveLoadModelEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILiveLoadModel
public:
	STDMETHOD(get_VehicularLoads)(/*[out, retval]*/ IVehicularLoads* *pVal);
	STDMETHOD(putref_VehicularLoads)(/*[in]*/ IVehicularLoads* newVal);
	STDMETHOD(Clear)();
	STDMETHOD(Clone)(ILiveLoadModel **ppCS);
	STDMETHOD(get_DistributionFactorType)(/*[out, retval]*/ DistributionFactorType *pVal);
	STDMETHOD(put_DistributionFactorType)(/*[in]*/ DistributionFactorType newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);

// IVehicularLoadsEvents
   STDMETHOD(OnVehicularLoadsChanged)(IVehicularLoad* item, ChangeType change);
   STDMETHOD(OnVehicularLoadsRenamed)(BSTR oldName, BSTR newName);
   STDMETHOD(OnVehicularLoadsAdded)(IVehicularLoad* item);
   STDMETHOD(OnVehicularLoadsBeforeRemove)(IVehicularLoad* item);
   
   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

protected:
   CComBSTR               m_Name;
   DistributionFactorType m_DistributionFactorType;

   CComPtr<IVehicularLoads> m_VehicularLoads;
   DWORD                    m_VehicularLoadsCookie;
};

#endif //__LIVELOADMODEL_H_
