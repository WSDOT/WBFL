///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// MixedSolver.h : Declaration of the CMixedSolver

#ifndef __MIXEDSOLVER_H_
#define __MIXEDSOLVER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMixedSolver
class ATL_NO_VTABLE CMixedSolver : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMixedSolver, &CLSID_MixedSolver>,
	public IMixedSolver
{
public:
	CMixedSolver()
	{
      m_UnitMode = suSI;
      m_bCflangeOverhangOnly = VARIANT_FALSE;
   }

DECLARE_REGISTRY_RESOURCEID(IDR_MIXEDSOLVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMixedSolver)
	COM_INTERFACE_ENTRY(IRCSolver)
	COM_INTERFACE_ENTRY(IMixedSolver)
END_COM_MAP()

   SpecUnitType m_UnitMode;
   VARIANT_BOOL m_bCflangeOverhangOnly;

// IMixedSolver
public:
   STDMETHOD(put_UnitMode)(/*[in]*/ SpecUnitType unitMode) override;
   STDMETHOD(get_UnitMode)(/*[out,retval]*/ SpecUnitType* unitMode) override;

// IRCSolver
public:
	STDMETHOD(get_IsCflangeOverhangOnly)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_IsCflangeOverhangOnly)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(Solve)(/*[in]*/ IRCBeam* beam,/*[out,retval]*/ IRCSolution* *solution) override;
};

#endif //__MIXEDSOLVER_H_
