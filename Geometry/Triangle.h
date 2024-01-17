///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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
#pragma once

// Triangle.h : Declaration of the CTriangle

#include "resource.h"       // main symbols
#include <GeomModel/Triangle.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CTriangle
class ATL_NO_VTABLE CTriangle : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTriangle, &CLSID_Triangle>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CTriangle,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public ITriangle,
	public IShapeXYPositionImpl<CTriangle, WBFL::Geometry::Triangle>
{
public:
	CTriangle()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

	void SetShape(const WBFL::Geometry::Triangle& shape);
	virtual WBFL::Geometry::Triangle& GetShape() override { return m_Triangle; }

DECLARE_REGISTRY_RESOURCEID(IDR_TRIANGLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTriangle)
	COM_INTERFACE_ENTRY(ITriangle)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
	WBFL::Geometry::Triangle m_Triangle;
	CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ITriangle
public:
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(get_HookPoint)(/*[out,retval]*/ IPoint2d** hookPnt) override;
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
	STDMETHOD(get_Offset)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Offset)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Height)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Width)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Width)(/*[in]*/ Float64 newVal) override;
};
