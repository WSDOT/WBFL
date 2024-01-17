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

// BulbTee2.h : Declaration of the CBulbTee

#include "resource.h"       // main symbols
#include <GeomModel/BulbTee.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CBulbTee
class ATL_NO_VTABLE CBulbTee2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBulbTee2, &CLSID_BulbTee2>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CBulbTee2,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IBulbTee2,
	public IShapeXYPositionImpl<CBulbTee2, WBFL::Geometry::BulbTee>
{
public:
	CBulbTee2()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetShape(const WBFL::Geometry::BulbTee& shape);
	virtual WBFL::Geometry::BulbTee& GetShape() override { return m_Beam; }

DECLARE_REGISTRY_RESOURCEID(IDR_BULBTEE2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBulbTee2)
	COM_INTERFACE_ENTRY(IBulbTee2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::BulbTee m_Beam;
   CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBulbTee2
public:
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(get_TopFlangeWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_BottomFlangeWidth)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(GetBottomFlangePoints)(/*[out]*/IPoint2d** ppLeftTop, /*[out]*/IPoint2d** ppLeftBottom, /*[out]*/IPoint2d** ppRightTop, /*[out]*/IPoint2d** ppRightBottom);
   STDMETHOD(GetTopFlangePoints)(/*[out]*/IPoint2d** ppLeftTop, /*[out]*/IPoint2d** ppLeftBottom, /*[out]*/IPoint2d** ppTopCL,/*[out]*/IPoint2d** ppTopCentral,/*[out]*/IPoint2d** ppRightTop, /*[out]*/IPoint2d** ppRightBottom);
   STDMETHOD(GetTopFlangeThickness)(/*[out]*/Float64* pHl, /*[out]*/Float64* pHc, /*[out]*/Float64* pHr);
   STDMETHOD(get_AvgWebWidth)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_MinHeight)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_MaxHeight)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_CLHeight)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/ IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
   STDMETHOD(get_n2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_n2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_n1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_n1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_T2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_T2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_T1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_T1)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D7)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D7)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D6)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D6)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D5)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D5)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D4)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D4)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D3)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D3)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_C2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_C2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_C1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_C1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_W6)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W6)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_W5)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W5)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_W4)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W4)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W3)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W3)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W1)(/*[in]*/ Float64 newVal) override;
};
