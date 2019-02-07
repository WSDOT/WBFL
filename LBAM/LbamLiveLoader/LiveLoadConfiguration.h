///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2019  Washington State Department of Transportation
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

// LiveLoadConfiguration.h : Declaration of the CLiveLoadConfiguration

#ifndef __LIVELOADCONFIGURATION_H_
#define __LIVELOADCONFIGURATION_H_

#include "resource.h"       // main symbols
#include "LBAMLiveLoaderCP.h"

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadConfiguration
class ATL_NO_VTABLE CLiveLoadConfiguration : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLiveLoadConfiguration, &CLSID_LiveLoadConfiguration>,
	public IConnectionPointContainerImpl<CLiveLoadConfiguration>,
	public ISupportErrorInfo,
	public ILiveLoadConfiguration,
	public CProxyDLiveLoadConfigurationEvents< CLiveLoadConfiguration >,
   public IPersistImpl<CLiveLoadConfiguration>,
   public IObjectSafetyImpl<CLiveLoadConfiguration,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
   CLiveLoadConfiguration():
   m_DoApplyImpact(VARIANT_FALSE),
   m_IsApplicable(VARIANT_FALSE),
   m_DistributionFactorType(dftNone),
   m_ForceEffectType(fetMz),
   m_LiveLoadModelType(lltNone),
   m_VehicleIndex(0),
   m_TruckDirection(ltdForward),
   m_TruckPosition(0.0),
   m_PivotAxleIndex(0),
   m_VariableSpacing(0.0),
   m_VehicularLoadConfiguration(vlcDefault),
   m_OptimizationType(optMaximize)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LIVELOADCONFIGURATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLiveLoadConfiguration)
	COM_INTERFACE_ENTRY(ILiveLoadConfiguration)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLiveLoadConfiguration)
CONNECTION_POINT_ENTRY(IID_ILiveLoadConfigurationEvents)
END_CONNECTION_POINT_MAP()

   HRESULT FinalConstruct();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILiveLoadConfiguration
public:
   STDMETHOD(get_PivotAxleIndex)(/*[out, retval]*/ AxleIndexType *pVal) override;
   STDMETHOD(put_PivotAxleIndex)(/*[in]*/ AxleIndexType newVal) override;
	STDMETHOD(get_VehicleIndex)(/*[out, retval]*/ AxleIndexType *pVal) override;
	STDMETHOD(put_VehicleIndex)(/*[in]*/ AxleIndexType newVal) override;
	STDMETHOD(get_LiveLoadModel)(/*[out, retval]*/ LiveLoadModelType *pVal) override;
	STDMETHOD(put_LiveLoadModel)(/*[in]*/ LiveLoadModelType newVal) override;
	STDMETHOD(get_DistributionFactorType)(/*[out, retval]*/ DistributionFactorType *pVal) override;
	STDMETHOD(put_DistributionFactorType)(/*[in]*/ DistributionFactorType newVal) override;
	STDMETHOD(get_IsApplicable)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_IsApplicable)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(get_DoApplyImpact)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_DoApplyImpact)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(get_AxleConfig)(/*[out, retval]*/ IIndexArray* *pVal) override;
	STDMETHOD(put_AxleConfig)(/*[in]*/ IIndexArray* newVal) override;
	STDMETHOD(get_VariableSpacing)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_VariableSpacing)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_TruckDirection)(/*[out, retval]*/ TruckDirectionType *pVal) override;
	STDMETHOD(put_TruckDirection)(/*[in]*/ TruckDirectionType newVal) override;
	STDMETHOD(get_TruckPosition)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_TruckPosition)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_VehicularLoadConfiguration)(/*[out, retval]*/ VehicularLoadConfigurationType *pVal) override;
	STDMETHOD(put_VehicularLoadConfiguration)(/*[in]*/ VehicularLoadConfigurationType newVal) override;
	STDMETHOD(get_ForceEffect)(/*[out, retval]*/ ForceEffectType *pVal) override;
	STDMETHOD(put_ForceEffect)(/*[in]*/ ForceEffectType newVal) override;
	STDMETHOD(get_Optimization)(/*[out, retval]*/ OptimizationType *pVal) override;
	STDMETHOD(put_Optimization)(/*[in]*/ OptimizationType newVal) override;
	STDMETHOD(Clone)(/*[out, retval]*/ ILiveLoadConfiguration**pClone) override;

// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

protected:
   VehicleIndexType               m_VehicleIndex;
   LiveLoadModelType              m_LiveLoadModelType;

   CComPtr<IIndexArray>             m_AxleConfig; // indicies of the axles that are actually used
   Float64                         m_VariableSpacing;
   TruckDirectionType             m_TruckDirection;
   Float64                         m_TruckPosition;
   VARIANT_BOOL                   m_DoApplyImpact;
   VARIANT_BOOL                   m_IsApplicable;
   VehicularLoadConfigurationType m_VehicularLoadConfiguration;
   DistributionFactorType         m_DistributionFactorType;
   ForceEffectType                m_ForceEffectType;
   OptimizationType               m_OptimizationType;
   AxleIndexType                  m_PivotAxleIndex;

};

#endif //__LIVELOADCONFIGURATION_H_
