///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2023  Washington State Department of Transportation
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
#pragma once

// Point3d.h : Declaration of the CPoint3d

#include "resource.h"       // main symbols
#include <GeomModel/Primitives3d.h>

/////////////////////////////////////////////////////////////////////////////
// CPoint3d
class ATL_NO_VTABLE CPoint3d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPoint3d, &CLSID_Point3d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CPoint3d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IPoint3d
{
public:
	CPoint3d()
	{
	}

   std::shared_ptr<WBFL::Geometry::Point3d>& GetPoint() { return m_pPoint; }
   void SetPoint(std::shared_ptr<WBFL::Geometry::Point3d>& point) { m_pPoint = point; }

DECLARE_REGISTRY_RESOURCEID(IDR_POINT3D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPoint3d)
	COM_INTERFACE_ENTRY(IPoint3d)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   std::shared_ptr<WBFL::Geometry::Point3d> m_pPoint{ std::make_shared<WBFL::Geometry::Point3d>() };

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPoint3d
public:
   STDMETHOD(Clone)(/*[out,retval]*/IPoint3d** ppPoint) override;
   STDMETHOD(Distance)(/*[in]*/Float64 x,/*[in]*/Float64 y,/*[in]*/Float64 z,/*[out,retval]*/Float64* pDistance) override;
   STDMETHOD(DistanceEx)(/*[in]*/IPoint3d* pOther,/*[out,retval]*/Float64* pDistance) override;
   STDMETHOD(Location)(/*[out]*/Float64* pX,/*[out]*/Float64* pY,/*[out]*/Float64* pZ) override;
   STDMETHOD(SameLocation)(/*[in]*/IPoint3d* pOther) override;
   STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 cz, /*[in]*/ IVector3d* vector,/*[in]*/ Float64 angle) override;
   STDMETHOD(RotateEx)(/*[in]*/ IPoint3d* center,/*[in]*/ IVector3d* vector,/*[in]*/ Float64 angle) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize3d* pSize) override;
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy,/*[in]*/ Float64 dz) override;
	STDMETHOD(MoveEx)(/*[in]*/ IPoint3d* pPoint) override;
	STDMETHOD(Move)(/*[in]*/ Float64 x,/*[in]*/ Float64 y,/*[in]*/ Float64 z) override;
	STDMETHOD(get_Z)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Z)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Y)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X)(/*[in]*/ Float64 newVal) override;
};
