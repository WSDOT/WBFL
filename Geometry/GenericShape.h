///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// GenericShape.h : Declaration of the CGenericShape

#include "resource.h"       // main symbols
#include <GeomModel/GenericShape.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CGenericShape
class ATL_NO_VTABLE CGenericShape : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGenericShape, &CLSID_GenericShape>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CGenericShape,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IGenericShape,
   public IShape,
   public IXYPosition
{
public:
	CGenericShape()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

	void SetShape(const WBFL::Geometry::GenericShape& shape);
	WBFL::Geometry::GenericShape& GetShape() { return m_Shape; }

DECLARE_REGISTRY_RESOURCEID(IDR_GENERICSHAPE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGenericShape)
	COM_INTERFACE_ENTRY(IGenericShape)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::GenericShape m_Shape;
	CComPtr<IPoint2d> m_pCentroid;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IGenericShape
public:
   STDMETHOD(get_Area)(Float64 *pVal) override;
   STDMETHOD(put_Area)(Float64 newVal) override;
   STDMETHOD(put_Perimeter)(Float64 newVal) override;
   STDMETHOD(get_Centroid)(IPoint2d* *pVal) override;
   STDMETHOD(putref_Centroid)(IPoint2d* newVal) override;
	STDMETHOD(get_Ybottom)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Ybottom)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Ytop)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Ytop)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Xright)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Xright)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Xleft)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Xleft)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_Ixx)(Float64 *pVal) override;
   STDMETHOD(put_Ixx)(Float64 newVal) override;
   STDMETHOD(get_Iyy)(Float64 *pVal) override;
   STDMETHOD(put_Iyy)(Float64 newVal) override;
   STDMETHOD(get_Ixy)(Float64 *pVal) override;
   STDMETHOD(put_Ixy)(Float64 newVal) override;
	STDMETHOD(get_Shape)(IShape* *pVal) override;
	STDMETHOD(get_XYPosition)(IXYPosition* *pVal) override;

// IShape
public:
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
public:
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point) override;
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point) override;
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo) override;
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle) override;
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle) override;
};
