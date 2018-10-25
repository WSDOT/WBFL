///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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

// StrainHardenedRebarModel.h : Declaration of the CStrainHardenedRebarModel

#ifndef __StrainHardenedRebarModel_H_
#define __StrainHardenedRebarModel_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStrainHardenedRebarModel
class ATL_NO_VTABLE CStrainHardenedRebarModel : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStrainHardenedRebarModel, &CLSID_StrainHardenedRebarModel>,
	public ISupportErrorInfo,
	public IStrainHardenedRebarModel,
	public IStressStrain
{
public:
   CStrainHardenedRebarModel() :
      m_bstrName("Strain Hardened Rebar")
	{
      m_Fy = 60;
      m_Fu = 90;
      m_Es = 29000;
      m_esh = 0.006;
      m_efr = 0.07;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRAINHARDENEDREBARMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrainHardenedRebarModel)
	COM_INTERFACE_ENTRY(IStrainHardenedRebarModel)
	COM_INTERFACE_ENTRY(IStressStrain)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

   Float64 m_Fy, m_Fu, m_Es, m_esh, m_efr;
   CComBSTR m_bstrName;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStrainHardenedRebarModel
public:
	STDMETHOD(Init)(/*[in]*/ Float64 fy,/*[in]*/ Float64 fu,/*[in]*/ Float64 Es,/*[in]*/ Float64 esh,/*[in]*/ Float64 efr);
	STDMETHOD(get_Es)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Es)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_fy)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_fy)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_fu)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_fu)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_esh)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_esh)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_efr)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_efr)(/*[in]*/ Float64 newVal);

// IStressStrain
public:
   STDMETHOD(put_Name)(/*[in]*/BSTR name);
	STDMETHOD(get_Name)(/*[out,retval]*/BSTR *name);
   STDMETHOD(ComputeStress)(/*[in]*/ Float64 strain,/*[out,retval]*/Float64* pVal);
   STDMETHOD(StrainLimits)(/*[out]*/Float64* minStrain,/*[out]*/Float64* maxStrain);
   STDMETHOD(get_YieldStrain)(/*[out,retval]*/Float64* pey);
   STDMETHOD(get_ModulusOfElasticity)(/*[out,retval]*/Float64* pE);
   STDMETHOD(get_StrainAtPeakStress)(/*[out,retval]*/Float64* strain);
};

#endif //__StrainHardenedRebarModel_H_
