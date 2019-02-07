///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2019  Washington State Department of Transportation
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

// Rectangle.h : Declaration of the CRectangle

#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CRectangle
class ATL_NO_VTABLE CRectangle : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRectangle, &CLSID_Rect>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CRectangle,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IRectangle,
	public IShape,
   public IXYPosition,
   public IStructuredStorage2,
   public IPersist,
   public CProxyDPoint2dEvents< CRectangle >,
   public IConnectionPointContainerImpl<CRectangle>,
   public IPoint2dEvents
{
public:
	CRectangle()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_RECTANGLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRectangle)
	COM_INTERFACE_ENTRY(IRectangle)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CRectangle)
	CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

private:
   void GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py);

   CComPtr<IPoint2d> m_pHookPoint; // CenterCenter point
   unsigned long   m_HookPointCookie;
   Float64 m_Height;
   Float64 m_Width;
   Float64 m_Rotation;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRectangle
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
	STDMETHOD(get_HookPoint)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_Width)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Width)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Height)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;

// IShape
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

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

// IPoint2dEvents
public:
	STDMETHOD(OnPointChanged)(IPoint2d* point) override;

private:
   // dirty flags to signal completion of different computations and cached properties
   bool m_DirtyBoundingBox;
   bool m_DirtyProperties;
   bool m_DirtyPolyShape;
   void MakeDirty() { m_DirtyBoundingBox = m_DirtyProperties = m_DirtyPolyShape = true;}

   // cached shape properties
   struct ShapeProps
   {
      Float64 Area;
      Float64 Ixx;
      Float64 Iyy;
      Float64 Ixy;
      Float64 Xleft;
      Float64 Xright;
      Float64 Ytop;
      Float64 Ybottom;
      Float64 Cx;  // centriod coord's
      Float64 Cy;

      ShapeProps()
      {
         Init();
      }
      void Init();
      HRESULT CreateIShapeProperties(IShapeProperties ** props);

   } m_ShapeProps;


   // cached bounding rectangle
   struct BoundRect
   {
      Float64 Left;
      Float64 Right;
      Float64 Top;
      Float64 Bottom;

      BoundRect()
      {
         Init();
      }
      
      void Init()
      {
         Left = Right = Top = Bottom = 0.0;
      }

      HRESULT CreateIRect(IRect2d** rect);

   } m_BoundingRect;

   CComPtr<IShape> m_pPolyShape;

   void UpdateBoundingRect();
   void UpdateShapeProperties();
   void UpdatePolyShape();
   
};

#endif //__RECTANGLE_H_
