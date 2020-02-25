///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// TrafficBarrier.h : Declaration of the CTrafficBarrier

#ifndef __TRAFFICBARRIER_H_
#define __TRAFFICBARRIER_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CTrafficBarrier
class ATL_NO_VTABLE CTrafficBarrier : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTrafficBarrier, &CLSID_TrafficBarrier>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CTrafficBarrier,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public ITrafficBarrier,
	public IShape,
   public IXYPosition,
   public IStructuredStorage2,
   public IPersist,
   public IPoint2dEvents,
   public CProxyDPoint2dEvents< CTrafficBarrier >,
   public IConnectionPointContainerImpl<CTrafficBarrier>
{
public:
	CTrafficBarrier()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_TRAFFICBARRIER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTrafficBarrier)
	COM_INTERFACE_ENTRY(ITrafficBarrier)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTrafficBarrier)
	CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

private:
   Float64 m_X1;
   Float64 m_X2;
   Float64 m_X3;
   Float64 m_X4;
   Float64 m_X5;
   Float64 m_Y1;
   Float64 m_Y2;
   Float64 m_Y3;
   Float64 m_Y4;
   TrafficBarrierOrientation m_Orientation;
   Float64 m_Rotation;

   CComPtr<IPoint2d> m_pHookPoint;  // Hook point at intersection of top edge of slab and barrier
   unsigned long   m_HookPointCookie;

   //       +--+
   //       |   \
   //       |    \
   //       |     \
   //       |  *---\----      * = HookPoint
   //       |  | slab
   //       +--+--------

   bool   m_Dirty;
   void MakeDirty() {m_Dirty = true;}

   CComPtr<IPolyShape> m_pShape;
   HRESULT GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py);
   HRESULT UpdateShape();

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ITrafficBarrier
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(get_Orientation)(/*[out, retval]*/ TrafficBarrierOrientation *pVal) override;
	STDMETHOD(put_Orientation)(/*[in]*/ TrafficBarrierOrientation newVal) override;
	STDMETHOD(get_HookPoint)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_Y4)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y4)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Y3)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y3)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Y2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Y1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y1)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X5)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X5)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X4)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X4)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X3)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X3)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X1)(/*[in]*/ Float64 newVal) override;

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
};

#endif //__TRAFFICBARRIER_H_
