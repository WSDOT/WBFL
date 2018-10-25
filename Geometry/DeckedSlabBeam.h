///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2018  Washington State Department of Transportation
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

// DeckedSlabBeam.h : Declaration of the CDeckedSlabBeam
#pragma once
#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CDeckedSlabBeam
class ATL_NO_VTABLE CDeckedSlabBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDeckedSlabBeam, &CLSID_DeckedSlabBeam>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CDeckedSlabBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IDeckedSlabBeam,
	public IShape,
	public ICompositeShape,
   public IXYPosition,
   public IStructuredStorage2,
   public IPersist,
   public IPoint2dEvents,
   public CProxyDPoint2dEvents< CDeckedSlabBeam >,
   public IConnectionPointContainerImpl<CDeckedSlabBeam>
{
public:
	CDeckedSlabBeam()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_DECKEDSLABBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDeckedSlabBeam)
	COM_INTERFACE_ENTRY(IDeckedSlabBeam)
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

BEGIN_CONNECTION_POINT_MAP(CDeckedSlabBeam)
	CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IPoint2d> m_pHookPoint; // BottomCenter
   CComPtr<ICompositeShape> m_pShape; // Implementation shape
   Float64   m_Rotation;
   Float64   m_A;
   Float64   m_B;
   Float64   m_C;
   Float64   m_W;
   Float64   m_Tt;
   Float64   m_Tb;
   Float64   m_F;
   VARIANT_BOOL   m_bLeftBlockOut;
   VARIANT_BOOL   m_bRightBlockOut;
   CollectionIndexType m_VoidCount;

   bool   m_Dirty;
   DWORD  m_HookPointCookie;

   HRESULT GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py);
   HRESULT UpdateShape();
   void MakeDirty() {m_Dirty = true;}

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IDeckedSlabBeam
public:
   STDMETHOD(put_A)(/*[in]*/Float64 a) override;
   STDMETHOD(get_A)(/*[out,retval]*/Float64* a) override;
   STDMETHOD(put_B)(/*[in]*/Float64 b) override;
   STDMETHOD(get_B)(/*[out,retval]*/Float64* b) override;
   STDMETHOD(put_C)(/*[in]*/Float64 c) override;
   STDMETHOD(get_C)(/*[out,retval]*/Float64* c) override;
   STDMETHOD(put_W)(/*[in]*/Float64 w) override;
   STDMETHOD(get_W)(/*[out,retval]*/Float64* w) override;
   STDMETHOD(put_Tt)(/*[in]*/Float64 Tt) override;
   STDMETHOD(get_Tt)(/*[out,retval]*/Float64* Tt) override;
   STDMETHOD(put_Tb)(/*[in]*/Float64 Tb) override;
   STDMETHOD(get_Tb)(/*[out,retval]*/Float64* Tb) override;
   STDMETHOD(put_F)(/*[in]*/Float64 f) override;
   STDMETHOD(get_F)(/*[out,retval]*/Float64* f) override;
   STDMETHOD(put_LeftBlockOut)(/*[in]*/VARIANT_BOOL bLeftBlockOut) override;
   STDMETHOD(get_LeftBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbLeftBlockOut) override;
   STDMETHOD(put_RightBlockOut)(/*[in]*/VARIANT_BOOL bRightBlockOut) override;
   STDMETHOD(get_RightBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbRightBlockOut) override;
   STDMETHOD(put_VoidCount)(/*[in]*/CollectionIndexType nv) override;
   STDMETHOD(get_VoidCount)(/*[out,retval]*/CollectionIndexType* nv) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
   STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
   STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pStg) override;

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
