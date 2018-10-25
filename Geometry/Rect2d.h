///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2016  Washington State Department of Transportation
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


/////////////////////////////////////////////////////////////////////////////
// CRect2d
class ATL_NO_VTABLE CRect2d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRect2d, &CLSID_Rect2d>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CRect2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IPersist,
   public IRect2d,
   public IStructuredStorage2
{
public:
	CRect2d()
	{
      m_Top    = 0.00;
      m_Left   = 0.00;
      m_Bottom = 0.00;
      m_Right  = 0.00;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_RECT2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRect2d)
	COM_INTERFACE_ENTRY(IRect2d)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

private:
   Float64 m_Top;
   Float64 m_Left;
   Float64 m_Bottom;
   Float64 m_Right;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRect2d
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(Clone)(/*[out,retval]*/IRect2d** clone);
	STDMETHOD(IsNormalized)(/*[out,retval]*/ VARIANT_BOOL* pbResult);
	STDMETHOD(IsNull)(/*[out,retval]*/ VARIANT_BOOL* pbResult);
	STDMETHOD(Touches)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ VARIANT_BOOL* pbResult);
	STDMETHOD(ContainsRect)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ VARIANT_BOOL* pbResult);
	STDMETHOD(ContainsPoint)(/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ VARIANT_BOOL* pbResult);
	STDMETHOD(SetNull)();
	STDMETHOD(SetEmpty)();
	STDMETHOD(Size)(/*[out,retval]*/ ISize2d** ppSize);
	STDMETHOD(UnionBy)(/*[in]*/ IRect2d* pRect, /*[out,retval]*/ IRect2d** ppUnion);
	STDMETHOD(Union)(/*[in]*/ IRect2d* pRect);
	STDMETHOD(Intersect)(/*[in]*/ IRect2d* pRect, /*[out,retval]*/ IRect2d** ppIntersection);
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize);
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy);
	STDMETHOD(Normalize)();
	STDMETHOD(InflateEx)(/*[in]*/ ISize2d* pSize);
	STDMETHOD(Inflate)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy);
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Width)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(BoundPointEx)(/*[in]*/IPoint2d* pPoint);
	STDMETHOD(BoundPoint)(/*[in]*/Float64 x,/*[in]*/ Float64 y);
	STDMETHOD(get_TopRight)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_TopCenter)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_TopLeft)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_CenterRight)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_CenterLeft)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_CenterCenter)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_BottomRight)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_BottomCenter)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_BottomLeft)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_Area)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Bottom)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Bottom)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Top)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Top)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Right)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Right)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Left)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Left)(/*[in]*/ Float64 newVal);
	STDMETHOD(SetBounds)(/*[in]*/ Float64 Left, /*[in]*/ Float64 Right, /*[in]*/ Float64 Bottom, /*[in]*/ Float64 Top);
	STDMETHOD(GetBounds)(/*[out, retval]*/ Float64* pLeft, /*[out, retval]*/ Float64* pRight, /*[out, retval]*/ Float64* pBottom, /*[out, retval]*/ Float64* pTop);
// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__RECT2D_H_
