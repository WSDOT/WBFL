///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2013  Washington State Department of Transportation
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

// VoidedSlab2.h : Declaration of the CVoidedSlab2
#pragma once
#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CVoidedSlab2
class ATL_NO_VTABLE CVoidedSlab2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVoidedSlab2, &CLSID_VoidedSlab2>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CVoidedSlab2,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IVoidedSlab2,
	public IShape,
	public ICompositeShape,
   public IXYPosition,
   public IStructuredStorage2,
   public IPersist,
   public IPoint2dEvents,
   public CProxyDPoint2dEvents< CVoidedSlab2 >,
   public IConnectionPointContainerImpl<CVoidedSlab2>
{
public:
	CVoidedSlab2()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_VOIDEDSLAB2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVoidedSlab2)
	COM_INTERFACE_ENTRY(IVoidedSlab2)
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

BEGIN_CONNECTION_POINT_MAP(CVoidedSlab2)
	CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IPoint2d> m_pHookPoint; // BottomCenter
   CComPtr<ICompositeShape> m_pShape; // Implementation shape
   Float64   m_Rotation;
   Float64   m_W;
   Float64   m_H;
   Float64   m_Dext;
   Float64   m_Dint;
   Float64   m_Sext;
   Float64   m_Sint;
   Float64   m_C1;
   Float64   m_C2;
   Float64   m_C3;
   Float64   m_Hext;
   Float64   m_Hint;
   CollectionIndexType m_VoidCount;

   VARIANT_BOOL m_bLeftBlockOut, m_bRightBlockOut;

   bool   m_Dirty;
   DWORD  m_HookPointCookie;

   HRESULT GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py);
   HRESULT UpdateShape();
   void MakeDirty() {m_Dirty = true;}

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVoidedSlab2
public:
   STDMETHOD(put_Height)(/*[in]*/Float64 h);
   STDMETHOD(get_Height)(/*[out,retval]*/Float64* h);
   STDMETHOD(put_Width)(/*[in]*/Float64 w);
   STDMETHOD(get_Width)(/*[out,retval]*/Float64* w);
   STDMETHOD(put_C1)(/*[in]*/Float64 c1);
   STDMETHOD(get_C1)(/*[out,retval]*/Float64* c1);
   STDMETHOD(put_C2)(/*[in]*/Float64 c2);
   STDMETHOD(get_C2)(/*[out,retval]*/Float64* c2);
   STDMETHOD(put_C3)(/*[in]*/Float64 c3);
   STDMETHOD(get_C3)(/*[out,retval]*/Float64* c3);
   STDMETHOD(put_LeftBlockOut)(/*[in]*/VARIANT_BOOL bLeftBlockOut);
   STDMETHOD(get_LeftBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbLeftBlockOut);
   STDMETHOD(put_RightBlockOut)(/*[in]*/VARIANT_BOOL bRightBlockOut);
   STDMETHOD(get_RightBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbRightBlockOut);
   STDMETHOD(put_ExteriorVoidDiameter)(/*[in]*/Float64 d);
   STDMETHOD(get_ExteriorVoidDiameter)(/*[out,retval]*/Float64* d);
   STDMETHOD(put_InteriorVoidDiameter)(/*[in]*/Float64 d);
   STDMETHOD(get_InteriorVoidDiameter)(/*[out,retval]*/Float64* d);
   STDMETHOD(put_ExteriorVoidSpacing)(/*[in]*/Float64 s);
   STDMETHOD(get_ExteriorVoidSpacing)(/*[out,retval]*/Float64* s);
   STDMETHOD(put_InteriorVoidSpacing)(/*[in]*/Float64 s);
   STDMETHOD(get_InteriorVoidSpacing)(/*[out,retval]*/Float64* s);
   STDMETHOD(put_ExteriorVoidElevation)(/*[in]*/Float64 h1);
   STDMETHOD(get_ExteriorVoidElevation)(/*[out,retval]*/Float64* h1);
   STDMETHOD(put_InteriorVoidElevation)(/*[in]*/Float64 h2);
   STDMETHOD(get_InteriorVoidElevation)(/*[out,retval]*/Float64* h2);
   STDMETHOD(put_VoidCount)(/*[in]*/CollectionIndexType nv);
   STDMETHOD(get_VoidCount)(/*[out,retval]*/CollectionIndexType* nv);
   STDMETHOD(get_HookPoint)(/*[out,retval]*/IPoint2d** hookPnt);
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt);
   STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal);
   STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal);
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pStg);

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

// ICompositeShape
public:
// STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
//	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal);
//	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal);
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ ICompositeShapeItem* *pVal);
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType idx);
   STDMETHOD(Clear)();
   STDMETHOD(ReplaceEx)(CollectionIndexType idx,ICompositeShapeItem* pShapeItem);
   STDMETHOD(Replace)(CollectionIndexType idx,IShape* pShape);
	STDMETHOD(AddShapeEx)(/*[in]*/ ICompositeShapeItem* ShapeItem);
   STDMETHOD(AddShape)(/*[in]*/ IShape* shape,/*[in]*/ VARIANT_BOOL bVoid);

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
