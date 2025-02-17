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

// CircularManderSection.h : Declaration of the CCircularManderSection

#ifndef __CircularManderSection_H_
#define __CircularManderSection_H_

#include "resource.h"       // main symbols
#include <Materials/ConfinedConcreteModel.h>

class CManderSection
{
public:
	virtual const std::shared_ptr<const WBFL::Materials::ManderModelSection>& GetSection() const = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CCircularManderSection
class ATL_NO_VTABLE CCircularManderSection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCircularManderSection, &CLSID_CircularManderSection>,
	public CManderSection,
	public ISupportErrorInfo,
	public ICircularManderSection
{
public:
	CCircularManderSection()
	{
		m_Section = std::make_shared<WBFL::Materials::CircularManderSection>();
		m_BaseSection = std::dynamic_pointer_cast<WBFL::Materials::ManderModelSection>(m_Section);
	}

	virtual const std::shared_ptr<const WBFL::Materials::ManderModelSection>& GetSection() const override { return m_BaseSection; }

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
	std::shared_ptr<WBFL::Materials::CircularManderSection> m_Section;
	std::shared_ptr<const WBFL::Materials::ManderModelSection> m_BaseSection;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IManderModelSection
public:
   STDMETHOD(put_TransvYieldStrength)(/*[in]*/Float64 fyh) override;
	STDMETHOD(get_TransvYieldStrength)(/*[out,retval]*/Float64* fyh) override;
   STDMETHOD(put_TransvReinforcementRuptureStrain)(/*[in]*/Float64 esu) override;
   STDMETHOD(get_TransvReinforcementRuptureStrain)(/*[out,retval]*/Float64* esu) override;
   STDMETHOD(get_TransvReinforcementRatio)(/*[out,retval]*/Float64* ps) override;
	STDMETHOD(get_ConfinementEffectivenessCoefficient)(/*[out,retval]*/Float64* ke) override;

// ICircularManderSection
public:
   STDMETHOD(put_TransvReinforcementType)(/*[in]*/TransvReinforcementType trt) override;
	STDMETHOD(get_TransvReinforcementType)(/*[out,retval]*/TransvReinforcementType* trt) override;
	STDMETHOD(put_Asp)(/*[in]*/Float64 asp) override;
	STDMETHOD(get_Asp)(/*[out,retval]*/Float64* asp) override;
	STDMETHOD(put_As)(/*[in]*/Float64 as) override;
	STDMETHOD(get_As)(/*[out,retval]*/Float64* as) override;
	STDMETHOD(put_db)(/*[in]*/Float64 db) override;
	STDMETHOD(get_db)(/*[out,retval]*/Float64* db) override;
	STDMETHOD(put_S)(/*[in]*/Float64 s) override;
	STDMETHOD(get_S)(/*[out,retval]*/Float64* s) override;
	STDMETHOD(put_Diameter)(/*[in]*/Float64 d) override;
	STDMETHOD(get_Diameter)(/*[out,retval]*/Float64* d) override;
	STDMETHOD(put_Cover)(/*[in]*/Float64 c) override;
	STDMETHOD(get_Cover)(/*[out,retval]*/Float64* c) override;
};

#endif //__CircularManderSection_H_
