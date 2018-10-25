///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// VehicularLoad.h : Declaration of the CVehicularLoad

#ifndef __VEHICULARLOAD_H_
#define __VEHICULARLOAD_H_

#include "resource.h"       // main symbols
#include "LiveLoadCP.h"

/////////////////////////////////////////////////////////////////////////////
// CVehicularLoad
class ATL_NO_VTABLE CVehicularLoad : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CVehicularLoad,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CVehicularLoad, &CLSID_VehicularLoad>,
	public ISupportErrorInfo, 
	public IConnectionPointContainerImpl<CVehicularLoad>,
	public IVehicularLoad,
   public IPersistImpl<CVehicularLoad>,
	public IStructuredStorage2,
	public CProxyDVehicularLoadEvents< CVehicularLoad >,
   public IObjectSafetyImpl<CVehicularLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IAxlesEvents
{
public:
   CVehicularLoad():
   m_AxlesCookie(0),
   m_IMLane(0),
   m_IMTruck(0),
   m_LaneFactor(1.0),
   m_TruckFactor(1.0),
   m_SidewalkLoad(0),
   m_LaneLoad(0),
   m_VariableMaxSpacing(0),
   m_VariableAxle(FIXED_AXLE_TRUCK),
   m_LiveLoadApplicability(llaEntireStructure),
   m_UseNotional(VARIANT_TRUE),
   m_VehicularLoadConfiguration(vlcDefault),
   m_Name(0)
   {
	}

   STDMETHOD(FinalConstruct)();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_VEHICULARLOAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVehicularLoad)
	COM_INTERFACE_ENTRY(IVehicularLoad)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IAxlesEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CVehicularLoad)
CONNECTION_POINT_ENTRY(IID_IVehicularLoadEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVehicularLoad
public:
   STDMETHOD(SumAxleWeights)(/*[out,retval]*/Float64* pWeight);
	STDMETHOD(Clone)(/*[out,retval]*/IVehicularLoad** clone);
	STDMETHOD(get_IMLane)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_IMLane)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_IMTruck)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_IMTruck)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_LaneFactor)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_LaneFactor)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_TruckFactor)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_TruckFactor)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_SidewalkLoad)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_SidewalkLoad)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_LaneLoad)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_LaneLoad)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_VariableMaxSpacing)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_VariableMaxSpacing)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_VariableAxle)(/*[out, retval]*/ AxleIndexType *pVal);
	STDMETHOD(put_VariableAxle)(/*[in]*/ AxleIndexType newVal);
	STDMETHOD(get_Axles)(/*[out, retval]*/ IAxles* *pVal);
	STDMETHOD(putref_Axles)(/*[in]*/ IAxles* newVal);
	STDMETHOD(get_Applicability)(/*[out, retval]*/ LiveLoadApplicabilityType *pVal);
	STDMETHOD(put_Applicability)(/*[in]*/ LiveLoadApplicabilityType newVal);
	STDMETHOD(get_UseNotional)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_UseNotional)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Configuration)(/*[out, retval]*/ VehicularLoadConfigurationType *pVal);
	STDMETHOD(put_Configuration)(/*[in]*/ VehicularLoadConfigurationType newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

// IAxlesEvents
   STDMETHOD(OnAxlesChanged)(IAxle* item);
   STDMETHOD(OnAxlesAdded)(IAxle* item, AxleIndexType idx);
   STDMETHOD(OnAxlesBeforeRemove)(IAxle* item, AxleIndexType idx);
	STDMETHOD(OnAxlesMoveTo)(AxleIndexType from, AxleIndexType to);
	STDMETHOD(OnAxlesCopyTo)(AxleIndexType from, AxleIndexType to);
	STDMETHOD(OnAxlesReverse)();

protected:   
   CComPtr<IAxles>                m_Axles;
   DWORD                          m_AxlesCookie;

   Float64                         m_IMLane;
   Float64                         m_IMTruck;
   Float64                         m_LaneFactor;
   Float64                         m_TruckFactor;
   Float64                         m_SidewalkLoad;
   Float64                         m_LaneLoad;
   Float64                         m_VariableMaxSpacing;
   AxleIndexType                  m_VariableAxle;
   LiveLoadApplicabilityType      m_LiveLoadApplicability;
   VARIANT_BOOL                   m_UseNotional;
   VehicularLoadConfigurationType m_VehicularLoadConfiguration;
   CComBSTR                       m_Name;
};

#endif //__VEHICULARLOAD_H_
