///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
//                   Bridge and Structures Office
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
      m_bstrName("Strand")
	{
      m_ProductionMethod = pmtLowRelaxation;
      m_StrandGrade = sgtGrade270;

      m_Fpu = 270;
      m_Eps = 28500;
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

   ProductionMethodType m_ProductionMethod;
   StrandGradeType m_StrandGrade;

   Float64 m_Fpu;
   Float64 m_Eps;

   CComBSTR m_bstrName;

   CComPtr<IUnitServer> m_UnitServer;
   CComPtr<IUnit> m_ksiUnit;
   CComPtr<IUnitConvert2> m_Convert;

   Float64 m_MinStrain;
   Float64 m_MaxStrain;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPowerFormula
public:
   STDMETHOD(get_Grade)(/*[out,retval]*/StrandGradeType* grade);
	STDMETHOD(put_Grade)(/*[in]*/StrandGradeType grade);
   STDMETHOD(get_ProductionMethod)(/*[out,retval]*/ProductionMethodType* type);
	STDMETHOD(put_ProductionMethod)(/*[in]*/ProductionMethodType type);

// IStressStrain
public:
   STDMETHOD(put_Name)(/*[in]*/BSTR name);
	STDMETHOD(get_Name)(/*[out,retval]*/BSTR *name);
   STDMETHOD(ComputeStress)(/*[in]*/ Float64 strain,/*[out,retval]*/Float64* pVal);
   STDMETHOD(StrainLimits)(/*[out]*/Float64* minStrain,/*[out]*/Float64* maxStrain);
   STDMETHOD(get_YieldStrain)(/*[out,retval]*/Float64* pey);
   STDMETHOD(get_ModulusOfElasticity)(/*[out,retval]*/Float64* pE);
   STDMETHOD(get_StrainAtPeakStress)(/*[out,retval]*/Float64* strain);

// ISupportUnitServer
public:
		STDMETHOD(get_UnitServer)(/*[out,retval]*/ IUnitServer** ppVal );
		STDMETHOD(putref_UnitServer)(/*[in]*/ IUnitServer* pNewVal );
};

#endif //__PSPOWERFORMULA_H_
