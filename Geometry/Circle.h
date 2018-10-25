///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 2000  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// Circle.h : Declaration of the CCircle

#ifndef __CIRCLE_H_
#define __CIRCLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCircle
class ATL_NO_VTABLE CCircle : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCircle, &CLSID_Circle>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CCircle,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public ICircle,
	public IShape,
	public IXYPosition,
   public IStructuredStorage2,
   public IPersist
{
public:
	CCircle()
	{
      m_Radius = 0.00;
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_CIRCLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCircle)
	COM_INTERFACE_ENTRY(ICircle)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

private:
   CComPtr<IPoint2d> m_pCenter;
   Float64 m_Radius;

   void GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py);

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICircle
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal);
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal);
   STDMETHOD(ContainsPoint)(/*[in]*/IPoint2d* p,/*[out,retval]*/ VARIANT_BOOL* pResult);
	STDMETHOD(PointOnCircle)(/*[in]*/IPoint2d* p,/*[out,retval]*/ VARIANT_BOOL* pResult);
	STDMETHOD(ThroughTwoPoints)(/*[in]*/IPoint2d* p1,/*[in]*/ IPoint2d* p2);
	STDMETHOD(ThroughThreePoints)(/*[in]*/IPoint2d* p1,/*[in]*/ IPoint2d* p2,/*[in]*/ IPoint2d* p3);
	STDMETHOD(get_Center)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(putref_Center)(/*[in]*/ IPoint2d* newVal);
	STDMETHOD(get_Radius)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Radius)(/*[in]*/ Float64 newVal);

// IShape
	STDMETHOD(FurthestDistance)(/*[in]*/ILine2d* line,/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Perimeter)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(get_ShapeProperties)(/*[out,retval]*/ IShapeProperties* *pVal);
	STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d* *pVal);
	STDMETHOD(get_PolyPoints)(/*[out,retval]*/ IPoint2dCollection** ppPolyPoints);
	STDMETHOD(PointInShape)(/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ VARIANT_BOOL* pbResult);
	STDMETHOD(Clone)(/*[out,retval]*/ IShape** pClone);
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* pLine,/*[out,retval]*/ IShape** pShape);
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ IShape** pShape);

// IXYPosition
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy);
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize);
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point);
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point);
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo);
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle);
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle);

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__CIRCLE_H_
