///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// MultiWeb2.h : Declaration of the CMultiWeb2

#ifndef __MultiWeb2_H_
#define __MultiWeb2_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiWeb2
class ATL_NO_VTABLE CMultiWeb2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMultiWeb2, &CLSID_MultiWeb2>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CMultiWeb2,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IMultiWeb2,
	public IShape,
   public IXYPosition,
   public IStructuredStorage2,
   public IPersist,
   public IPoint2dEvents,
   public CProxyDPoint2dEvents< CMultiWeb2 >,
   public IConnectionPointContainerImpl<CMultiWeb2>
{
public:
	CMultiWeb2()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_MULTIWEB2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMultiWeb2)
	COM_INTERFACE_ENTRY(IMultiWeb2)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CMultiWeb2)
	CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IPoint2d> m_pHookPoint; // BottomCenter
   CComPtr<IPolyShape> m_pShape; // Implementation Polygon
   Float64   m_Rotation;
   Float64   m_H1;
   Float64   m_H2;
   Float64   m_H3;
   Float64   m_W1;
   Float64   m_W2;
   Float64   m_T1;
   Float64   m_T2;
   Float64   m_T3;
   Float64   m_T4;
   Float64   m_T5;
   Float64   m_F1;
   Float64   m_F2;
   Float64   m_C1;
   Float64   m_C2;
   WebIndexType m_WebCount;
   VARIANT_BOOL   m_bLeftBlockOut;
   VARIANT_BOOL   m_bRightBlockOut;

   bool   m_Dirty;
   DWORD  m_HookPointCookie;

   HRESULT GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py);
   HRESULT UpdateShape();
   void MakeDirty() {m_Dirty = true;}

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMultiWeb2
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal);
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal);
	STDMETHOD(get_AvgWebWidth)(/*[in]*/ WebIndexType webIdx,/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_TopFlangeWidth)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(get_HookPoint)(/*[out,retval]*/ IPoint2d** hookPnt);
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt);
	STDMETHOD(get_WebLocation)(/*[in]*/WebIndexType webIdx,/*[out,retval]*/Float64* location);
   STDMETHOD(get_WebCount)(/*[out, retval]*/ WebIndexType *pVal);
	STDMETHOD(put_WebCount)(/*[in]*/ WebIndexType newVal);
   STDMETHOD(get_W1)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_W1)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_W2)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_W2)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_H1)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_H1)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_H2)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_H2)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_H3)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_H3)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_T1)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_T1)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_T2)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_T2)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_T3)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_T3)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_T4)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_T4)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_T5)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_T5)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_F1)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_F1)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_F2)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_F2)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_C1)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_C1)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_C2)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_C2)(/*[in]*/ Float64 newVal);
   STDMETHOD(put_LeftBlockOut)(/*[in]*/VARIANT_BOOL bLeftBlockOut);
   STDMETHOD(get_LeftBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbLeftBlockOut);
   STDMETHOD(put_RightBlockOut)(/*[in]*/VARIANT_BOOL bRightBlockOut);
   STDMETHOD(get_RightBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbRightBlockOut);

// IShape
public:
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

};

#endif //__MultiWeb2_H_
