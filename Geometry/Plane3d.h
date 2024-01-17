///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// Plane3d.h : Declaration of the CPlane3d

#ifndef __PLANE3D_H_
#define __PLANE3D_H_

#include "resource.h"       // main symbols
#include <GeomModel/Plane3d.h>

/////////////////////////////////////////////////////////////////////////////
// CPlane3d
class ATL_NO_VTABLE CPlane3d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPlane3d, &CLSID_Plane3d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CPlane3d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IPlane3d
{
public:
	CPlane3d()
	{
	}

   void Init(Float64 a, Float64 b, Float64 c, Float64 d)
   {
      m_Plane.Init(a, b, c, d);
   }

DECLARE_REGISTRY_RESOURCEID(IDR_PLANE3D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPlane3d)
	COM_INTERFACE_ENTRY(IPlane3d)
	COM_INTERFACE_ENTRY2(IUnknown,IPlane3d)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::Plane3d m_Plane;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPlane3d
public:
   STDMETHOD(PointOnPlaneNearestOrigin)(/*[in]*/IPoint3d* pPoint,/*[out,retval]*/IPoint3d** ppPoint) override;
   STDMETHOD(SortestDistance)(/*[in]*/IPoint3d* point,/*[out,retval]*/Float64* pDistance) override;
   STDMETHOD(LineSegmentIntersect)(/*[in]*/ ILineSegment3d* pLineSegment,/*[out,retval]*/IPoint3d** ppPoint) override;
	STDMETHOD(GetZ)(/*[in]*/ Float64 x,/*[in]*/ Float64 y, /*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(GetY)(/*[in]*/ Float64 x,/*[in]*/ Float64 z, /*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(GetX)(/*[in]*/ Float64 y,/*[in]*/ Float64 z, /*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(ThroughAltitude)(/*[in]*/ Float64 altitude) override;
	STDMETHOD(ThroughLineEx)(/*[in]*/ ILine2d* pLine,/*[in]*/ IPoint3d* pPnt) override;
	STDMETHOD(ThroughPoints)(/*[in]*/ IPoint3d* p1,/*[in]*/ IPoint3d* p2,/*[in]*/ IPoint3d* p3) override;
   STDMETHOD(Clone)(/*[out,retval]*/IPlane3d** clone) override;
};

#endif //__PLANE3D_H_
