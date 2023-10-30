///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// MassProperties.h : Declaration of the CMassProperties

#ifndef __MASSPROPERTIES_H_
#define __MASSPROPERTIES_H_

#include "resource.h"       // main symbols
#include <GeomModel/MassProperties.h>

/////////////////////////////////////////////////////////////////////////////
// CMassProperties
class ATL_NO_VTABLE CMassProperties : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMassProperties, &CLSID_MassProperties>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CMassProperties,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IMassProperties
{
public:
	CMassProperties()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MASSPROPERTIES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMassProperties)
	COM_INTERFACE_ENTRY(IMassProperties)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IMassProperties
public:
	STDMETHOD(AddProperties)(/*[in]*/ IMassProperties* props) override;
	STDMETHOD(get_MassPerLength)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_MassPerLength)(/*[in]*/ Float64 newVal) override;

private:
	WBFL::Geometry::MassProperties m_Props;
};

#endif //__MASSPROPERTIES_H_
