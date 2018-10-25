///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// PlateGirder.h : Declaration of the CPlateGirder

#ifndef __PLATEGIRDER_H_
#define __PLATEGIRDER_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CPlateGirder
class ATL_NO_VTABLE CPlateGirder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPlateGirder, &CLSID_PlateGirder>,
   public IObjectSafetyImpl<CPlateGirder,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo,
   public IShape,
   public IXYPosition,
   public IPlateGirder,
   public IStructuredStorage2,
   public IPersist,
   public IPoint2dEvents,
   public CProxyDPoint2dEvents< CPlateGirder >,
   public IConnectionPointContainerImpl<CPlateGirder>
{
public:
	CPlateGirder()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PLATEGIRDER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPlateGirder)
	COM_INTERFACE_ENTRY(IPlateGirder)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPlateGirder)
	CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPlateGirder
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
	STDMETHOD(get_HookPoint)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* newVal);
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal);
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal);
	STDMETHOD(get_QBottomFlange)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_QTopFlange)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_WebThick)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_WebThick)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_WebHeight)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_WebHeight)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_BottomFlangeThick)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_BottomFlangeThick)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_BottomFlangeWidth)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_BottomFlangeWidth)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_TopFlangeThick)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_TopFlangeThick)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_TopFlangeWidth)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_TopFlangeWidth)(/*[in]*/ Float64 newVal);

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

// IPoint2dEvents
public:
	STDMETHOD(OnPointChanged)(IPoint2d* point);

private:
   CComPtr<IPoint2d> m_pHookPoint; // BottomCenter
   CComPtr<IPolyShape> m_pShape; // Implementation Polygon
   Float64 m_Rotation;
	Float64 m_webThick;
	Float64 m_webHeight;
	Float64 m_bfThick;
	Float64 m_bfWidth;
	Float64 m_tfThick;
	Float64 m_tfWidth;

   bool   m_Dirty;
   unsigned long   m_HookPointCookie;

   HRESULT UpdateShape();
   HRESULT GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py);
   void MakeDirty() {m_Dirty = true;}
};

#endif //__PLATEGIRDER_H_
