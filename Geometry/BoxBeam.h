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

// BoxBeam.h : Declaration of the CBoxBeam

#ifndef __BOXBEAM_H_
#define __BOXBEAM_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CBoxBeam
class ATL_NO_VTABLE CBoxBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBoxBeam, &CLSID_BoxBeam>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CBoxBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IBoxBeam,
	public IShape,
	public ICompositeShape,
   public IXYPosition,
   public IStructuredStorage2,
   public IPersist,
   public IPoint2dEvents,
   public CProxyDPoint2dEvents< CBoxBeam >,
   public IConnectionPointContainerImpl<CBoxBeam>
{
public:
	CBoxBeam()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_BOXBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBoxBeam)
	COM_INTERFACE_ENTRY(IBoxBeam)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(ICompositeShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CBoxBeam)
	CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IPoint2d> m_pHookPoint; // BottomCenter
   CComPtr<ICompositeShape> m_pShape; // Implementation shape
   Float64   m_Rotation;
   Float64   m_W1;
   Float64   m_W2;
   Float64   m_W3;
   Float64   m_W4;
   Float64   m_H1;
   Float64   m_H2;
   Float64   m_H3;
   Float64   m_H4;
   Float64   m_H5;
   Float64   m_H6;
   Float64   m_H7;
   Float64   m_F1;
   Float64   m_F2;
   Float64   m_C1;

   VARIANT_BOOL m_bLeftBlockOut, m_bRightBlockOut;
   VARIANT_BOOL m_bUseOverallWidth;

   CollectionIndexType m_VoidCount;

   bool   m_Dirty;
   unsigned long   m_HookPointCookie;

   HRESULT GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py);
   HRESULT UpdateShape();
   void MakeDirty() {m_Dirty = true;}

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBoxBeam
public:
   STDMETHOD(get_W1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_W2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_W3)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W3)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_W4)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W4)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H3)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H3)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H4)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H4)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H5)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H5)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H6)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H6)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H7)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H7)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_F1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_F1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_F2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_F2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_C1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_C1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(put_VoidCount)(/*[in]*/CollectionIndexType nv) override;
   STDMETHOD(get_VoidCount)(/*[out,retval]*/CollectionIndexType* nv) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/ IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
   STDMETHOD(get_WebWidth)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_BottomFlangeWidth)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_TopFlangeWidth)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
   STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pStg) override;
   STDMETHOD(put_LeftBlockOut)(/*[in]*/VARIANT_BOOL bLeftBlockOut) override;
   STDMETHOD(get_LeftBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbLeftBlockOut) override;
   STDMETHOD(put_RightBlockOut)(/*[in]*/VARIANT_BOOL bRightBlockOut) override;
   STDMETHOD(get_RightBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbRightBlockOut) override;
   STDMETHOD(get_Width)(/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(get_Height)(/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(put_UseOverallWidth)(/*[in]*/VARIANT_BOOL bUseOverallWidth) override;
   STDMETHOD(get_UseOverallWidth)(/*[out,retval]*/VARIANT_BOOL* pbUseOverallWidth) override;

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

// ICompositeShape
public:
// STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
//	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
//	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ ICompositeShapeItem* *pVal) override;
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType idx) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(ReplaceEx)(CollectionIndexType idx,ICompositeShapeItem* pShapeItem) override;
   STDMETHOD(Replace)(CollectionIndexType idx,IShape* pShape) override;
	STDMETHOD(AddShapeEx)(/*[in]*/ ICompositeShapeItem* ShapeItem) override;
   STDMETHOD(AddShape)(/*[in]*/ IShape* shape,/*[in]*/ VARIANT_BOOL bVoid) override;

// IXYPosition
public:
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

#endif //__BOXBEAM_H_
