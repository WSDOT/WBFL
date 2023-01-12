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

// RebarModel.h : Declaration of the CRebarModel

#ifndef __REBARMODEL_H_
#define __REBARMODEL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRebarModel
class ATL_NO_VTABLE CRebarModel : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRebarModel, &CLSID_RebarModel>,
	public ISupportErrorInfo,
	public IRebarModel,
	public IStressStrain,
   public IStructuredStorage2,
   public IPersist
{
public:
   CRebarModel() :
      m_bstrName("Rebar")
	{
      m_Fy = 60;
      m_Es = 29000;
      m_MinStrain = -0.07;
      m_MaxStrain =  0.07;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_REBARMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRebarModel)
	COM_INTERFACE_ENTRY(IRebarModel)
	COM_INTERFACE_ENTRY(IStressStrain)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

   Float64 m_Fy, m_Es;
   Float64 m_MinStrain;
   Float64 m_MaxStrain;
   CComBSTR m_bstrName;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRebarModel
public:
   STDMETHOD(get_MaxStrain)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_MaxStrain)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Es)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Es)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_fy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_fy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(Init)(/*[in]*/ Float64 fy,/*[in]*/ Float64 Es,/*[in]*/Float64 maxStrain) override;

// IStressStrain
public:
   STDMETHOD(put_Name)(/*[in]*/BSTR name) override;
	STDMETHOD(get_Name)(/*[out,retval]*/BSTR *name) override;
   STDMETHOD(ComputeStress)(/*[in]*/ Float64 strain,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(StrainLimits)(/*[out]*/Float64* minStrain,/*[out]*/Float64* maxStrain) override;
   STDMETHOD(get_YieldStrain)(/*[out,retval]*/Float64* pey) override;
   STDMETHOD(get_ModulusOfElasticity)(/*[out,retval]*/Float64* pE) override;
   STDMETHOD(get_StrainAtPeakStress)(/*[out,retval]*/Float64* strain) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID) override;
};

#endif //__REBARMODEL_H_
