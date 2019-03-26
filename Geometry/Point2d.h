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

// Point2d.h : Declaration of the CPoint2d

#ifndef __POINT2D_H_
#define __POINT2D_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CPoint2d
class ATL_NO_VTABLE CPoint2d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPoint2d, &CLSID_Point2d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CPoint2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CPoint2d>,
	public CProxyDPoint2dEvents< CPoint2d >,
   public IPersist,
	public IPoint2d,
   public IStructuredStorage2
{
public:
	CPoint2d()
	{
      m_X = 0.00;
      m_Y = 0.00;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_POINT2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPoint2d)
	COM_INTERFACE_ENTRY(IPoint2d)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPoint2d)
CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

private:
   Float64 m_X;
   Float64 m_Y;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPoint2dEx
public:
   STDMETHOD(Clone)(/*[out,retval]*/IPoint2d** ppPoint) override;

   STDMETHOD(Size)(Float64 x, Float64 y, ISize2d** ppSize) override;
   STDMETHOD(SizeEx)(IPoint2d* pPoint, ISize2d** ppSize) override;
   STDMETHOD(Distance)(Float64 x,Float64 y,Float64* pDistance) override;
   STDMETHOD(DistanceEx)(IPoint2d* pOther,Float64* pDistance) override;
   STDMETHOD(Location)(/*[out]*/Float64* pX,/*[out]*/Float64* pY) override;
   STDMETHOD(SameLocation)(/*[in]*/IPoint2d* pOther) override;
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pCenter,/*[in]*/ Float64 angle) override;
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pPoint) override;
	STDMETHOD(Move)(/*[in]*/ Float64 x,/*[in]*/ Float64 y) override;
	STDMETHOD(get_Y)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X)(/*[in]*/ Float64 newVal) override;

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;
};

#endif //__POINT2D_H_
