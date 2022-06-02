///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include "LoadingCP.h"

/////////////////////////////////////////////////////////////////////////////
// CVehicularLoad
class ATL_NO_VTABLE CVehicularLoad : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CVehicularLoad,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CVehicularLoad, &CLSID_ldVehicularLoad>,
	public ISupportErrorInfo, 
	public IConnectionPointContainerImpl<CVehicularLoad>,
	public ldIVehicularLoad,
   public IPersistImpl<CVehicularLoad>,
	public IStructuredStorage2,
	public CProxyDVehicularLoadEvents< CVehicularLoad >,
   public IObjectSafetyImpl<CVehicularLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ldIAxlesEvents
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
   m_VariableAxle(-1),
   m_LiveLoadApplicability(ldlaEntireStructure),
   m_UseNotional(VARIANT_TRUE),
   m_VehicularLoadConfiguration(ldvcDefault),
   m_Name(0)
   {
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_VEHICULARLOAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVehicularLoad)
	COM_INTERFACE_ENTRY(ldIVehicularLoad)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ldIAxlesEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CVehicularLoad)
CONNECTION_POINT_ENTRY(IID_ldIVehicularLoadEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ldIVehicularLoad
public:
	STDMETHOD(Clone)(/*[out,retval]*/ldIVehicularLoad** clone) override;
	STDMETHOD(get_IMLane)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_IMLane)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_IMTruck)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_IMTruck)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_LaneFactor)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_LaneFactor)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_TruckFactor)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_TruckFactor)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_SidewalkLoad)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_SidewalkLoad)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_LaneLoad)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_LaneLoad)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_VariableMaxSpacing)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_VariableMaxSpacing)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_VariableAxle)(/*[out, retval]*/ AxleIndexType *pVal) override;
	STDMETHOD(put_VariableAxle)(/*[in]*/ AxleIndexType newVal) override;
	STDMETHOD(get_Axles)(/*[out, retval]*/ ldIAxles* *pVal) override;
	STDMETHOD(putref_Axles)(/*[in]*/ ldIAxles* newVal) override;
	STDMETHOD(get_Applicability)(/*[out, retval]*/ ldLiveLoadApplicabilityType *pVal) override;
	STDMETHOD(put_Applicability)(/*[in]*/ ldLiveLoadApplicabilityType newVal) override;
	STDMETHOD(get_UseNotional)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_UseNotional)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(get_Configuration)(/*[out, retval]*/ ldVehicularLoadConfigurationType *pVal) override;
	STDMETHOD(put_Configuration)(/*[in]*/ ldVehicularLoadConfigurationType newVal) override;
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal) override;
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// ldIAxlesEvents
   STDMETHOD(OnAxlesChanged)(ldIAxle* item) override;
   STDMETHOD(OnAxlesAdded)(ldIAxle* item, AxleIndexType id) override;
   STDMETHOD(OnAxlesBeforeRemove)(ldIAxle* item, AxleIndexType id) override;
	STDMETHOD(OnAxlesMoveTo)(AxleIndexType from, AxleIndexType to) override;
	STDMETHOD(OnAxlesCopyTo)(AxleIndexType from, AxleIndexType to) override;
	STDMETHOD(OnAxlesReverse)() override;

protected:   
   CComPtr<ldIAxles>                m_Axles;
   DWORD                            m_AxlesCookie;

   Float64                          m_IMLane;
   Float64                          m_IMTruck;
   Float64                          m_LaneFactor;
   Float64                          m_TruckFactor;
   Float64                          m_SidewalkLoad;
   Float64                          m_LaneLoad;
   Float64                          m_VariableMaxSpacing;
   AxleIndexType                    m_VariableAxle;
   ldLiveLoadApplicabilityType      m_LiveLoadApplicability;
   VARIANT_BOOL                     m_UseNotional;
   ldVehicularLoadConfigurationType m_VehicularLoadConfiguration;
   CComBSTR                         m_Name;
};

#endif //__VEHICULARLOAD_H_
