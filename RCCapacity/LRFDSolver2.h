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

// LRFDSolver2.h : Declaration of the CLRFDSolver2

#pragma once

#include "resource.h"       // main symbols

// This object does moment capacity analysis using the closed form method in LRFD 2015.
// Instead of determining if fy or fs should be used in the analysis based on the geomtry
// of the section, the strains in the rebar are computed directly from a bi-linear 
// stress-strain curve.

/////////////////////////////////////////////////////////////////////////////
// CLRFDSolver2
class ATL_NO_VTABLE CLRFDSolver2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLRFDSolver2, &CLSID_LRFDSolver2>,
	public ILRFDSolver2,
	public IRCSolver2,
	public IRCSolver2Ex
{
public:
	CLRFDSolver2()
	{
      m_Tolerance = 0.00001;
      m_UnitMode = suSI;
      m_bCflangeOverhangOnly = VARIANT_FALSE;
      m_ec = 0.003;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LRFDSOLVER2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLRFDSolver2)
	COM_INTERFACE_ENTRY(ILRFDSolver2)
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

   void InitStrandModel(IStressStrain** model,Float64 fpu,Float64 Eps);
   void InitRebarModel(IStressStrain** model,Float64 fy,Float64 Es);

// IRCSolver
public:
	STDMETHOD(Solve)(/*[in]*/ IRCBeam* beam,/*[out,retval]*/ IRCSolution* *solution) override;

// IRCSolver2
public:
	STDMETHOD(Solve)(/*[in]*/ IRCBeam2* beam,/*[out,retval]*/ IRCSolutionEx* *solution) override;

// IRCSolver2Ex
public:
	STDMETHOD(Solve)(/*[in]*/ IRCBeam2Ex* beam,/*[out,retval]*/ IRCSolutionEx* *solution) override;

// ILRFDSolver2
public:
   STDMETHOD(put_Tolerance)(/*[in]*/ Float64 tolerance) override;
   STDMETHOD(get_Tolerance)(/*[out,retval]*/ Float64* tolerance) override;
	STDMETHOD(get_IsCflangeOverhangOnly)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_IsCflangeOverhangOnly)(/*[in]*/ VARIANT_BOOL newVal) override;
   STDMETHOD(putref_StrandModel)(/*[in]*/ IStressStrain* model) override;
   STDMETHOD(get_StrandModel)(/*[out,retval]*/ IStressStrain* *model) override;
   STDMETHOD(putref_RebarModel)(/*[in]*/ IStressStrain* model) override;
   STDMETHOD(get_RebarModel)(/*[out,retval]*/ IStressStrain* *model) override;
   STDMETHOD(put_UnitMode)(/*[in]*/ SpecUnitType unitMode) override;
   STDMETHOD(get_UnitMode)(/*[out,retval]*/ SpecUnitType* unitMode) override;
};
