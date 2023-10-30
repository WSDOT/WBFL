///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// Rect2d.h : Declaration of the CRect2d

#ifndef __RECT2D_H_
#define __RECT2D_H_

#include "resource.h"       // main symbols
#include <GeomModel/Primitives.h>


/////////////////////////////////////////////////////////////////////////////
// CRect2d
class ATL_NO_VTABLE CRect2d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRect2d, &CLSID_Rect2d>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CRect2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IRect2d
{
public:
	CRect2d()
	{
	}


DECLARE_REGISTRY_RESOURCEID(IDR_RECT2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRect2d)
	COM_INTERFACE_ENTRY(IRect2d)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
	WBFL::Geometry::Rect2d m_Rect;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRect2d
public:
   STDMETHOD(Clone)(/*[out,retval]*/IRect2d** clone) override;
	STDMETHOD(IsNormalized)(/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(IsNull)(/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(Touches)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(ContainsRect)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(ContainsPoint)(/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(SetNull)() override;
	STDMETHOD(SetEmpty)() override;
	STDMETHOD(Size)(/*[out,retval]*/ ISize2d** ppSize) override;
	STDMETHOD(UnionBy)(/*[in]*/ IRect2d* pRect, /*[out,retval]*/ IRect2d** ppUnion) override;
	STDMETHOD(Union)(/*[in]*/ IRect2d* pRect) override;
	STDMETHOD(Intersect)(/*[in]*/ IRect2d* pRect, /*[out,retval]*/ IRect2d** ppIntersection) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
	STDMETHOD(Normalize)() override;
	STDMETHOD(InflateEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(Inflate)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Width)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(BoundPointEx)(/*[in]*/IPoint2d* pPoint) override;
	STDMETHOD(BoundPoint)(/*[in]*/Float64 x,/*[in]*/ Float64 y) override;
	STDMETHOD(get_TopRight)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_TopCenter)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_TopLeft)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_CenterRight)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_CenterLeft)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_CenterCenter)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_BottomRight)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_BottomCenter)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_BottomLeft)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_Area)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Bottom)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Bottom)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Top)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Top)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Right)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Right)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Left)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Left)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(SetBounds)(/*[in]*/ Float64 Left, /*[in]*/ Float64 Right, /*[in]*/ Float64 Bottom, /*[in]*/ Float64 Top) override;
	STDMETHOD(GetBounds)(/*[out, retval]*/ Float64* pLeft, /*[out, retval]*/ Float64* pRight, /*[out, retval]*/ Float64* pBottom, /*[out, retval]*/ Float64* pTop) override;
};

#endif //__RECT2D_H_
