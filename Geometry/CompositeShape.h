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

// CompositeShape.h : Declaration of the CCompositeShape

#ifndef __COMPOSITESHAPE_H_
#define __COMPOSITESHAPE_H_

#include "resource.h"       // main symbols

#include "WBFLComCollections.h"

// NOTE: Ideally this object would be implemented by delegating implementation details to WBFL::Geometry::CompositeShape.
// This is very difficult and would require breaking encapsulation and ruining extensibility.
// To save a WBFL::Geometry::Shape into a WBFL::Geometry::CompositeShape object, we would have to figure
// out what kind of WBFL::Geometry::Shape the IShape pointer wraps. There are two problems with this.
// 1) If the client creates a new shape that isn't implemented with WBFL::Geometry::Shape, there is no
// way we can put that shape into the underlying WBFL::Geometry::CompositeShae object, and 2) in order to
// learn that type of Shape the IShape pointer wraps, we need to do dynamic casts on known types which
// will break every time a new shape is added. For these reasons, this object does not use WBFL::Geometry::CompositeShape
// as the underlying implementation


class CCompositeShape;
using CompositeShapeVectorImpl = CComVectorCollectionNoEnum<ICompositeShape,ICompositeShapeItem,IndexType>;

/////////////////////////////////////////////////////////////////////////////
// CCompositeShape
class ATL_NO_VTABLE CCompositeShape : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCompositeShape, &CLSID_CompositeShape>,
   public IObjectSafetyImpl<CCompositeShape,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo,
   public IShape,
   public IXYPosition,
	public CompositeShapeVectorImpl
{
public:
	CCompositeShape()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMPOSITESHAPE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCompositeShape)
	COM_INTERFACE_ENTRY(ICompositeShape)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(IShape)
    COM_INTERFACE_ENTRY(IXYPosition)
    COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

protected:
   CComBSTR GetCollectionName()
   {
      return CComBSTR("CompositeShape"); // This is the "Unit Name" stored in the persistance stream
   }

public:
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICompositeShape
public:
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
   STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
   //	STDMETHOD(get_Item)(/*[in]*/ IndexType idx, /*[out, retval]*/ ICompositeShapeItem* *pVal) override;
//	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal) override;
//	STDMETHOD(get_Count)(/*[out, retval]*/ IndexType *pVal) override;
//	STDMETHOD(Remove)(/*[in]*/ IndexType idx) override;
//	STDMETHOD(Clear)() override;
   STDMETHOD(ReplaceEx)(IndexType idx,ICompositeShapeItem* pShapeItem) override;
   STDMETHOD(Replace)(IndexType idx,IShape* pShape) override;
	STDMETHOD(AddShapeEx)(/*[in]*/ ICompositeShapeItem* ShapeItem) override;
   STDMETHOD(AddShape)(/*[in]*/ IShape* shape,/*[in]*/ VARIANT_BOOL bVoid) override;

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

#endif //__COMPOSITESHAPE_H_
