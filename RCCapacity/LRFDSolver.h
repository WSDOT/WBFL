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

// LRFDSolver.h : Declaration of the CLRFDSolver

#ifndef __LRFDSOLVER_H_
#define __LRFDSOLVER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLRFDSolver
class ATL_NO_VTABLE CLRFDSolver : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLRFDSolver, &CLSID_LRFDSolver>,
	public ILRFDSolver
{
public:
	CLRFDSolver()
	{
      m_UnitMode = suSI;
      m_bCflangeOverhangOnly = VARIANT_FALSE;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LRFDSOLVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLRFDSolver)
	COM_INTERFACE_ENTRY(ILRFDSolver)
	COM_INTERFACE_ENTRY(IRCSolver)
END_COM_MAP()

   SpecUnitType m_UnitMode;
   VARIANT_BOOL m_bCflangeOverhangOnly;

// ILRFDSolver
public:
   STDMETHOD(put_UnitMode)(/*[in]*/ SpecUnitType unitMode);
   STDMETHOD(get_UnitMode)(/*[out,retval]*/ SpecUnitType* unitMode);

// IRCSolver
public:
	STDMETHOD(get_IsCflangeOverhangOnly)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsCflangeOverhangOnly)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(Solve)(/*[in]*/ IRCBeam* beam,/*[out,retval]*/ IRCSolution* *solution);
};

#endif //__LRFDSOLVER_H_
