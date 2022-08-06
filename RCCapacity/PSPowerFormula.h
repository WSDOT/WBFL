///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// PSPowerFormula.h : Declaration of the CPSPowerFormula

#ifndef __PSPOWERFORMULA_H_
#define __PSPOWERFORMULA_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <Materials/PSPowerFormulaModel.h>

/////////////////////////////////////////////////////////////////////////////
// CPSPowerFormula
class ATL_NO_VTABLE CPSPowerFormula : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPSPowerFormula, &CLSID_PSPowerFormula>,
	public ISupportErrorInfo,
   public IPowerFormula,
	public IStressStrain,
   public ISupportUnitServer
{
public:
   CPSPowerFormula() :
      m_Model(_T("Strand"))
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PSPOWERFORMULA)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPSPowerFormula)
   COM_INTERFACE_ENTRY(IPowerFormula)
	COM_INTERFACE_ENTRY(IStressStrain)
   COM_INTERFACE_ENTRY(ISupportUnitServer)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

void ClearUnits();
void SetupUnits();

WBFL::Materials::PSPowerFormulaModel m_Model;
   CComPtr<IUnitServer> m_UnitServer;
   CComPtr<IUnit> m_ksiUnit;
   CComPtr<IUnitConvert2> m_Convert;


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPowerFormula
public:
   STDMETHOD(get_Grade)(/*[out,retval]*/StrandGradeType* grade) override;
	STDMETHOD(put_Grade)(/*[in]*/StrandGradeType grade) override;
   STDMETHOD(get_ProductionMethod)(/*[out,retval]*/ProductionMethodType* type) override;
	STDMETHOD(put_ProductionMethod)(/*[in]*/ProductionMethodType type) override;
   STDMETHOD(put_ReductionFactor)(/*[in]*/Float64 factor) override;
   STDMETHOD(get_ReductionFactor)(/*[out, retval]*/Float64* factor) override;
   STDMETHOD(SetStrainLimits)(/*[in]*/Float64 eMin, /*[in]*/Float64 eMax) override;

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
   STDMETHOD(get_UnitServer)(/*[out,retval]*/ IUnitServer** ppVal) override;
   STDMETHOD(putref_UnitServer)(/*[in]*/ IUnitServer* pNewVal) override;
};

#endif //__PSPOWERFORMULA_H_
