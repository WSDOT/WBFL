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

// LFDSolver.h : Declaration of the CLFDSolver

#ifndef __LFDSOLVER_H_
#define __LFDSOLVER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLFDSolver
class ATL_NO_VTABLE CLFDSolver : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLFDSolver, &CLSID_LFDSolver>,
	public ILFDSolver
{
public:
	CLFDSolver()
	{
      m_UnitMode = suSI;
      m_bCflangeOverhangOnly = VARIANT_FALSE;
   }

DECLARE_REGISTRY_RESOURCEID(IDR_LFDSOLVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLFDSolver)
	COM_INTERFACE_ENTRY(IRCSolver)
	COM_INTERFACE_ENTRY(ILFDSolver)
END_COM_MAP()

   SpecUnitType m_UnitMode;
   VARIANT_BOOL m_bCflangeOverhangOnly;

// ILFDSolver
public:
   STDMETHOD(put_UnitMode)(/*[in]*/ SpecUnitType unitMode) override;
   STDMETHOD(get_UnitMode)(/*[out,retval]*/ SpecUnitType* unitMode) override;

// IRCSolver
public:
	STDMETHOD(get_IsCflangeOverhangOnly)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_IsCflangeOverhangOnly)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(Solve)(/*[in]*/ IRCBeam* beam,/*[out,retval]*/ IRCSolution* *solution) override;
};

#endif //__LFDSOLVER_H_
