///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// UnconfinedConcrete.h : Declaration of the CUnconfinedConcrete

#ifndef __UNCONFINEDCONCRETE_H_
#define __UNCONFINEDCONCRETE_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <Materials/UnconfinedConcreteModel.h>

/////////////////////////////////////////////////////////////////////////////
// CUnconfinedConcrete
class ATL_NO_VTABLE CUnconfinedConcrete : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUnconfinedConcrete, &CLSID_UnconfinedConcrete>,
	public ISupportErrorInfo,
	public IUnconfinedConcrete,
	public IStressStrain,
	public ISupportUnitServer
{
public:
   CUnconfinedConcrete() :
      m_Model(_T("Concrete"))
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_UNCONFINEDCONCRETE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUnconfinedConcrete)
	COM_INTERFACE_ENTRY(IUnconfinedConcrete)
	COM_INTERFACE_ENTRY(IStressStrain)
	COM_INTERFACE_ENTRY(ISupportUnitServer)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

   WBFL::Materials::UnconfinedConcreteModel m_Model;
	CComPtr<IUnitServer> m_UnitServer;
	CComPtr<IUnit> m_ksiUnit;
	CComPtr<IUnitConvert2> m_Convert;

	void SetupUnits();
	void ClearUnits();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IUnconfinedConcrete
public:
	STDMETHOD(get_fc)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_fc)(/*[in]*/ Float64 newVal) override;

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

#endif //__UNCONFINEDCONCRETE_H_
