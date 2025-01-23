///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// ProfilePoint.h : Declaration of the CProfilePoint

#ifndef __PROFILEPOINT_H_
#define __PROFILEPOINT_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CProfilePoint
class ATL_NO_VTABLE CProfilePoint : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProfilePoint, &CLSID_ProfilePoint>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CProfilePoint,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IProfilePoint
{
public:
	CProfilePoint()
	{
	}

 	HRESULT FinalConstruct();

	void SetProfilePoint(std::shared_ptr<WBFL::COGO::ProfilePoint> point) { m_ProfilePoint = point; }
	std::shared_ptr<WBFL::COGO::ProfilePoint> GetProfilePoint() { return m_ProfilePoint; }


DECLARE_REGISTRY_RESOURCEID(IDR_PROFILEPOINT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProfilePoint)
	COM_INTERFACE_ENTRY(IProfilePoint)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IProfilePoint
public:
	STDMETHOD(get_Station)(/*[out, retval]*/ IStation* *station) override;
	STDMETHOD(put_Station)(/*[in]*/ VARIANT varStation) override;
	STDMETHOD(get_Elevation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Elevation)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(Location)(IStation** pStation, Float64* pElevation) override;
   STDMETHOD(Move)(VARIANT varStation, Float64 elevation) override;
	STDMETHOD(Clone)(IProfilePoint** ppClone) override;

private:
	std::shared_ptr<WBFL::COGO::ProfilePoint> m_ProfilePoint{ std::make_shared<WBFL::COGO::ProfilePoint>() };
};

#endif //__PROFILEPOINT_H_
