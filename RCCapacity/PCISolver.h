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

// PCISolver.h : Declaration of the CPCISolver

#ifndef __PCISOLVER_H_
#define __PCISOLVER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPCISolver
class ATL_NO_VTABLE CPCISolver : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPCISolver, &CLSID_PCISolver>,
	public IPCISolver,
	public IRCSolver2,
	public IRCSolver2Ex
{
public:
	CPCISolver()
	{
      m_Tolerance = 0.00001;
      m_UnitMode = suSI;
      m_bCflangeOverhangOnly = VARIANT_FALSE;
      m_ec = 0.003;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PCISOLVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPCISolver)
	COM_INTERFACE_ENTRY(IPCISolver)
	COM_INTERFACE_ENTRY(IRCSolver)
	COM_INTERFACE_ENTRY(IRCSolver2)
	COM_INTERFACE_ENTRY(IRCSolver2Ex)
END_COM_MAP()

   Float64 m_Tolerance;
   Float64 m_ec; // concrete crushing strain
   CComPtr<IStressStrain> m_StrandModel;
   CComPtr<IStressStrain> m_RebarModel;
   SpecUnitType m_UnitMode;
   VARIANT_BOOL m_bCflangeOverhangOnly;

   void InitStrandModel(IStressStrain** model,IUnitServer* unitServer);
   void InitRebarModel(IStressStrain** model,Float64 fy,Float64 Es);

// IRCSolver
public:
	STDMETHOD(Solve)(/*[in]*/ IRCBeam* beam,/*[out,retval]*/ IRCSolution* *solution);

// IRCSolver2
public:
	STDMETHOD(Solve)(/*[in]*/ IRCBeam2* beam,/*[out,retval]*/ IRCSolutionEx* *solution);

// IRCSolver2Ex
public:
	STDMETHOD(Solve)(/*[in]*/ IRCBeam2Ex* beam,/*[out,retval]*/ IRCSolutionEx* *solution);

// IPCISolver
public:
   STDMETHOD(put_Tolerance)(/*[in]*/ Float64 tolerance);
   STDMETHOD(get_Tolerance)(/*[out,retval]*/ Float64* tolerance);
	STDMETHOD(get_IsCflangeOverhangOnly)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsCflangeOverhangOnly)(/*[in]*/ VARIANT_BOOL newVal);
   STDMETHOD(putref_StrandModel)(/*[in]*/ IStressStrain* model);
   STDMETHOD(get_StrandModel)(/*[out,retval]*/ IStressStrain* *model);
   STDMETHOD(putref_RebarModel)(/*[in]*/ IStressStrain* model);
   STDMETHOD(get_RebarModel)(/*[out,retval]*/ IStressStrain* *model);
   STDMETHOD(put_UnitMode)(/*[in]*/ SpecUnitType unitMode);
   STDMETHOD(get_UnitMode)(/*[out,retval]*/ SpecUnitType* unitMode);
};

#endif //__PCISOLVER_H_
