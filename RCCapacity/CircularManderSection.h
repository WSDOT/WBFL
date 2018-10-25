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

// CircularManderSection.h : Declaration of the CCircularManderSection

#ifndef __CircularManderSection_H_
#define __CircularManderSection_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>

/////////////////////////////////////////////////////////////////////////////
// CCircularManderSection
class ATL_NO_VTABLE CCircularManderSection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCircularManderSection, &CLSID_CircularManderSection>,
	public ISupportErrorInfo,
	public ICircularManderSection
{
public:
	CCircularManderSection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_CIRCULARMANDERSECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCircularManderSection)
	COM_INTERFACE_ENTRY(IManderModelSection)
	COM_INTERFACE_ENTRY(ICircularManderSection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   TransvReinforcementType m_TransvReinforcementType;
   Float64 m_Asp;
   Float64 m_As;
   Float64 m_db;
   Float64 m_S;
   Float64 m_Diameter;
   Float64 m_Cover;
   Float64 m_fyh;

   Float64 Get_ds();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IManderModelSection
public:
   STDMETHOD(put_TransvYieldStrength)(/*[in]*/Float64 fyh);
	STDMETHOD(get_TransvYieldStrength)(/*[out,retval]*/Float64* fyh);
	STDMETHOD(get_TransvReinforcementRatio)(/*[out,retval]*/Float64* ps);
	STDMETHOD(get_ConfinementEffectivenessCoefficient)(/*[out,retval]*/Float64* ke);

// ICircularManderSection
public:
   STDMETHOD(put_TransvReinforcementType)(/*[in]*/TransvReinforcementType trt);
	STDMETHOD(get_TransvReinforcementType)(/*[out,retval]*/TransvReinforcementType* trt);
	STDMETHOD(put_Asp)(/*[in]*/Float64 asp);
	STDMETHOD(get_Asp)(/*[out,retval]*/Float64* asp);
	STDMETHOD(put_As)(/*[in]*/Float64 as);
	STDMETHOD(get_As)(/*[out,retval]*/Float64* as);
	STDMETHOD(put_db)(/*[in]*/Float64 db);
	STDMETHOD(get_db)(/*[out,retval]*/Float64* db);
	STDMETHOD(put_S)(/*[in]*/Float64 s);
	STDMETHOD(get_S)(/*[out,retval]*/Float64* s);
	STDMETHOD(put_Diameter)(/*[in]*/Float64 d);
	STDMETHOD(get_Diameter)(/*[out,retval]*/Float64* d);
	STDMETHOD(put_Cover)(/*[in]*/Float64 c);
	STDMETHOD(get_Cover)(/*[out,retval]*/Float64* c);
};

#endif //__CircularManderSection_H_
