///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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
#pragma once

// Circle.h : Declaration of the CCircle

#include "resource.h"       // main symbols
#include <GeomModel/Circle.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CCircle
class ATL_NO_VTABLE CCircle : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCircle, &CLSID_Circle>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CCircle,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public ICircle,
	public IShapeXYPositionImpl<CCircle, WBFL::Geometry::Circle>
{
public:
	CCircle()
	{
	}

   HRESULT FinalConstruct();

	void SetShape(const WBFL::Geometry::Circle& shape);
	virtual WBFL::Geometry::Circle& GetShape() override { return m_Circle; }

DECLARE_REGISTRY_RESOURCEID(IDR_CIRCLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCircle)
	COM_INTERFACE_ENTRY(ICircle)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
	WBFL::Geometry::Circle m_Circle;
	CComPtr<IPoint2d> m_pCenter;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICircle
public:
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
   STDMETHOD(ContainsPoint)(/*[in]*/IPoint2d* p,/*[out,retval]*/ VARIANT_BOOL* pResult) override;
	STDMETHOD(PointOnCircle)(/*[in]*/IPoint2d* p,/*[out,retval]*/ VARIANT_BOOL* pResult) override;
	STDMETHOD(ThroughTwoPoints)(/*[in]*/IPoint2d* p1,/*[in]*/ IPoint2d* p2) override;
	STDMETHOD(ThroughThreePoints)(/*[in]*/IPoint2d* p1,/*[in]*/ IPoint2d* p2,/*[in]*/ IPoint2d* p3) override;
	STDMETHOD(get_Center)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_Center)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_Radius)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Radius)(/*[in]*/ Float64 newVal) override;
};
