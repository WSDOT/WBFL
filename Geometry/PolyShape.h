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

// PolyShape.h : Declaration of the CPolyShape

#ifndef __POLYSHAPE_H_
#define __POLYSHAPE_H_

#include "resource.h"       // main symbols
#include "Helper.h"
#include <GeomModel/Polygon.h>

/////////////////////////////////////////////////////////////////////////////
// CPolyShape
class ATL_NO_VTABLE CPolyShape : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPolyShape, &CLSID_PolyShape>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CPolyShape,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IPolyShape,
   public IShape,
   public IXYPosition
{
public:
	CPolyShape()
	{
	}

   void SetPolygon(const WBFL::Geometry::Polygon& polygon) { m_Polygon = polygon; }

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_POLYSHAPE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPolyShape)
   COM_INTERFACE_ENTRY(IPolyShape)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPolyShape
public:
	STDMETHOD(get_Points)(/*[out,retval]*/IPoint2dCollection** coll) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(get_Point)(/*[in]*/ CollectionIndexType index, /*[out, retval]*/ IPoint2d* *pVal) override;
   STDMETHOD(GetPoint)(/*[in] */ CollectionIndexType index, /*[out]*/ Float64* pX, /*[out]*/ Float64* pY) override;
   STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(RemovePoint)(/*[in]*/ CollectionIndexType index) override;
   STDMETHOD(ChangePoint)(/*[in]*/ CollectionIndexType index, /*[in]*/ Float64 x, /*[in]*/ Float64 y) override;
   STDMETHOD(ChangePointEx)(/*[in]*/ CollectionIndexType index, /*[in]*/ IPoint2d* pPoint) override;
   STDMETHOD(SetPoints)(/*[in]*/ IPoint2dCollection* pPoints) override;
   STDMETHOD(AddPoints)(/*[in]*/ IPoint2dCollection* pPoints) override;
	STDMETHOD(AddPointEx)(/*[in]*/ IPoint2d* pPoint) override;
   STDMETHOD(AddPoint)(/*[in]*/ Float64 x,/*[in]*/ Float64 y) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/ IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;

// IShape
	STDMETHOD(FurthestPoint)(/*[in]*/ILine2d* line, /*[out]*/ IPoint2d** ppPoint, /*[out]*/Float64* dist) override;
	STDMETHOD(FurthestDistance)(/*[in]*/ILine2d* line,/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Perimeter)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_ShapeProperties)(/*[out,retval]*/ IShapeProperties* *pVal) override;
	STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d* *pVal) override;
	STDMETHOD(get_PolyPoints)(/*[out,retval]*/ IPoint2dCollection** ppPolyPoints) override;
	STDMETHOD(PointInShape)(/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(Clone)(/*[out,retval]*/ IShape** pClone) override;
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* pLine,/*[out,retval]*/ IShape** pShape) override;
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ IShape** pShape) override;

// IXYPosition
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point) override;
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point) override;
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo) override;
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle) override;
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle) override;

private:
   WBFL::Geometry::Polygon m_Polygon;
   CComPtr<IPoint2d> m_HookPoint;
};

#endif //__POLYSHAPE_H_
