///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// Angle.h : Declaration of the CAngle

#ifndef __ANGLE_H_
#define __ANGLE_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAngle
class ATL_NO_VTABLE CAngle : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAngle, &CLSID_Angle>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CAngle,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IAngle
{
public:
	CAngle()
	{
	}

	void SetAngle(std::shared_ptr<WBFL::COGO::Angle> angle) { m_Angle = angle; }
	std::shared_ptr<WBFL::COGO::Angle> GetAngle() { return m_Angle; }

DECLARE_REGISTRY_RESOURCEID(IDR_ANGLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAngle)
	COM_INTERFACE_ENTRY(IAngle)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IAngle
public:
   STDMETHOD(Clone)(/*[out,retval]*/ IAngle* *clone) override;
   STDMETHOD(Increment)(/*[in]*/ VARIANT varAngle,/*[out,retval]*/ IAngle* *pVal) override;
   STDMETHOD(IncrementBy)(/*[in]*/ VARIANT varAngle) override;
   STDMETHOD(FromVariant)(/*[in]*/ VARIANT varAngle) override;
	STDMETHOD(FromString)(/*[in]*/ BSTR bstrAngle) override;
	STDMETHOD(FromDMS)(/*[in]*/ long deg,/*[in]*/ long min,/*[in]*/ Float64 sec) override;
	STDMETHOD(Normalize)() override;
	STDMETHOD(get_Second)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Minute)(/*[out, retval]*/ long *pVal) override;
	STDMETHOD(get_Degree)(/*[out, retval]*/ long *pVal) override;
	STDMETHOD(get_Value)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Value)(/*[in]*/ Float64 newVal) override;

private:
	std::shared_ptr<WBFL::COGO::Angle> m_Angle{ std::make_shared<WBFL::COGO::Angle>() };
};

#endif //__ANGLE_H_
