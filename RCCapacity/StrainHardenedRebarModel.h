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

// StrainHardenedRebarModel.h : Declaration of the CStrainHardenedRebarModel

#ifndef __StrainHardenedRebarModel_H_
#define __StrainHardenedRebarModel_H_

#include "resource.h"       // main symbols
#include <Materials/RebarModel.h>

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
      m_Model(_T("Strain Hardened Rebar"), WBFL::Units::ConvertToSysUnits(60, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(90, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(29000, WBFL::Units::Measure::KSI), 0.006, 0.07)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRAINHARDENEDREBARMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrainHardenedRebarModel)
	COM_INTERFACE_ENTRY(IStrainHardenedRebarModel)
	COM_INTERFACE_ENTRY(IStressStrain)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

   WBFL::Materials::RebarModel m_Model;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStrainHardenedRebarModel
public:
	STDMETHOD(Init)(/*[in]*/ Float64 fy,/*[in]*/ Float64 fu,/*[in]*/ Float64 Es,/*[in]*/ Float64 esh,/*[in]*/ Float64 efr) override;
	STDMETHOD(get_Es)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Es)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_fy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_fy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_fu)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_fu)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_esh)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_esh)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_efr)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_efr)(/*[in]*/ Float64 newVal) override;

// IStressStrain
public:
   STDMETHOD(put_Name)(/*[in]*/BSTR name) override;
	STDMETHOD(get_Name)(/*[out,retval]*/BSTR *name) override;
   STDMETHOD(ComputeStress)(/*[in]*/ Float64 strain,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(StrainLimits)(/*[out]*/Float64* minStrain,/*[out]*/Float64* maxStrain) override;
   STDMETHOD(get_YieldStrain)(/*[out,retval]*/Float64* pey) override;
   STDMETHOD(get_ModulusOfElasticity)(/*[out,retval]*/Float64* pE) override;
   STDMETHOD(get_StrainAtPeakStress)(/*[out,retval]*/Float64* strain) override;
};

#endif //__StrainHardenedRebarModel_H_
