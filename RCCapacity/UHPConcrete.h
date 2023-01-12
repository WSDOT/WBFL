///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// UHPConcrete.h : Declaration of the CUHPConcrete

#ifndef __UHPConcrete_H_
#define __UHPConcrete_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>

/////////////////////////////////////////////////////////////////////////////
// CUHPConcrete
class ATL_NO_VTABLE CUHPConcrete : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUHPConcrete, &CLSID_UHPConcrete>,
	public ISupportErrorInfo,
	public IUHPConcrete,
	public IStressStrain,
	public ISupportUnitServer,
   public IStructuredStorage2,
   public IPersist
{
public:
   CUHPConcrete() :
      m_bstrName("UHPC")
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_UHPCONCRETE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUHPConcrete)
	COM_INTERFACE_ENTRY(IUHPConcrete)
	COM_INTERFACE_ENTRY(IStressStrain)
   COM_INTERFACE_ENTRY(ISupportUnitServer)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

   Float64 m_fc; // in KSI units
   Float64 m_ecu;
   Float64 m_K1;
   Float64 m_alpha;
   Float64 m_ftcr;
   Float64 m_ftloc;
   Float64 m_etloc;
   Float64 m_gamma;
   CComPtr<IUnitServer> m_UnitServer;
   CComBSTR m_bstrName;

   Float64 GetEc();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IUHPConcrete
public:
   STDMETHOD(get_fc)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_fc)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_ecu)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_ecu)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_K1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_K1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_alpha)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_alpha)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_ftcr)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_ftcr)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_ftloc)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_ftloc)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_etloc)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_etloc)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_gamma)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_gamma)(/*[in]*/ Float64 newVal) override;

// IStressStrain
public:
   STDMETHOD(put_Name)(/*[in]*/BSTR name) override;
	STDMETHOD(get_Name)(/*[out,retval]*/BSTR *name) override;
   STDMETHOD(ComputeStress)(/*[in]*/ Float64 strain,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(StrainLimits)(/*[out]*/Float64* minStrain,/*[out]*/Float64* maxStrain) override;
   STDMETHOD(get_YieldStrain)(/*[out,retval]*/Float64* pey) override;
   STDMETHOD(get_ModulusOfElasticity)(/*[out,retval]*/Float64* pE) override;
   STDMETHOD(get_StrainAtPeakStress)(/*[out,retval]*/Float64* strain) override;

// ISupportUnitServer
public:
		STDMETHOD(get_UnitServer)(/*[out,retval]*/ IUnitServer** ppVal ) override;
		STDMETHOD(putref_UnitServer)(/*[in]*/ IUnitServer* pNewVal ) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID) override;
};

#endif //__UHPConcrete_H_
