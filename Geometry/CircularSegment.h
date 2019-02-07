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

// CircularSegment.h : Declaration of the CCircularSegment

#ifndef __CIRCULARSEGMENT_H_
#define __CIRCULARSEGMENT_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CCircularSegment
class ATL_NO_VTABLE CCircularSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCircularSegment, &CLSID_CircularSegment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCircularSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public ICircularSegment,
	public IShape,
	public IXYPosition,
   public IStructuredStorage2,
   public IPersist,
   public IPoint2dEvents,
   public CProxyDPoint2dEvents< CCircularSegment >,
   public IConnectionPointContainerImpl<CCircularSegment>
{
public:
	CCircularSegment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_CIRCULARSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCircularSegment)
	COM_INTERFACE_ENTRY(ICircularSegment)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IShape)
	COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICircularSegment
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
	STDMETHOD(get_Rotation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Rotation)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_InteriorAngle)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_InteriorAngle)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_MidOrdinate)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_MidOrdinate)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Center)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_Center)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_Radius)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Radius)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_HookPoint)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;

// IShape
	STDMETHOD(get_ShapeProperties)(IShapeProperties * * pVal) override;
	STDMETHOD(get_BoundingBox)(IRect2d * * pVal) override;
	STDMETHOD(get_PolyPoints)(IPoint2dCollection * * ppPolyPoints) override;
	STDMETHOD(Clone)(IShape** pClone) override;
	STDMETHOD(PointInShape)(IPoint2d * pPoint, VARIANT_BOOL * pbResult) override;
	STDMETHOD(ClipWithLine)(ILine2d * pLine, IShape * * pShape) override;
	STDMETHOD(ClipIn)(IRect2d * pRect, IShape * * pShape) override;
	STDMETHOD(get_Perimeter)(Float64 * pVal) override;
	STDMETHOD(FurthestDistance)(ILine2d * line, Float64 * pVal) override;

// IXYPosition
	STDMETHOD(Offset)(Float64 dx, Float64 dy) override;
	STDMETHOD(OffsetEx)(ISize2d * pSize) override;
	STDMETHOD(get_LocatorPoint)(LocatorPointType lp, IPoint2d * * point) override;
	STDMETHOD(put_LocatorPoint)(LocatorPointType lp, IPoint2d * point) override;
	STDMETHOD(MoveEx)(IPoint2d * pFrom, IPoint2d * pTo) override;
	STDMETHOD(RotateEx)(IPoint2d * pPoint, Float64 angle) override;
	STDMETHOD(Rotate)(Float64 cx, Float64 cy, Float64 angle) override;

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
	Float64 m_Radius;
   Float64 m_MO;
   Float64 m_Rotation;
	CComPtr<IPoint2d> m_HookPoint;
   CComPtr<IPoint2d> m_Center;

   unsigned long   m_HookPointCookie;
   unsigned long   m_CenterPointCookie;
   bool m_SquelchEvents;

   void AdjustHookPoint();
   void AdjustCenterPoint();
   HRESULT EdgePoints(IPoint2d** p1,IPoint2d** p2);
   HRESULT BoundaryLine(ILine2d** line);
public :

BEGIN_CONNECTION_POINT_MAP(CCircularSegment)
	CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

};

#endif //__CIRCULARSEGMENT_H_
