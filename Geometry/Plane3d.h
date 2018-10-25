///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2016  Washington State Department of Transportation
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


/////////////////////////////////////////////////////////////////////////////
// CPlane3d
class ATL_NO_VTABLE CPlane3d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPlane3d, &CLSID_Plane3d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CPlane3d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IPlane3d,
   public IStructuredStorage2,
   public IPersist
{
public:
	CPlane3d()
	{
      m_A = 0.00;
      m_B = 0.00;
      m_C = 0.00;
      m_D = 0.00;
      m_bIsXYPlane = VARIANT_TRUE;
	}

   void Init(Float64 a,Float64 b,Float64 c,Float64 d,VARIANT_BOOL bXYPlane)
   {
      m_A = a;
      m_B = b;
      m_C = c;
      m_D = d;
      m_bIsXYPlane = bXYPlane;
   }

DECLARE_REGISTRY_RESOURCEID(IDR_PLANE3D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPlane3d)
	COM_INTERFACE_ENTRY(IPlane3d)
	COM_INTERFACE_ENTRY2(IUnknown,IPlane3d)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY2(IUnknown,IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

private:
   Float64 m_A;
   Float64 m_B;
   Float64 m_C;
   Float64 m_D;
   VARIANT_BOOL m_bIsXYPlane;  // true if plane is parallel to global XY plane

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPlane3d
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(PointOnPlaneNearestOrigin)(/*[out,retval]*/IPoint3d** ppPoint);
   STDMETHOD(SortestDistance)(/*[in]*/IPoint3d* point,/*[out,retval]*/Float64* pDistance);
   STDMETHOD(LineSegmentIntersect)(/*[in]*/ ILineSegment3d* pLineSegment,/*[out,retval]*/IPoint3d** ppPoint);
	STDMETHOD(GetZ)(/*[in]*/ Float64 x,/*[in]*/ Float64 y, /*[out, retval]*/ Float64 *pVal);
	STDMETHOD(GetY)(/*[in]*/ Float64 x,/*[in]*/ Float64 z, /*[out, retval]*/ Float64 *pVal);
	STDMETHOD(GetX)(/*[in]*/ Float64 y,/*[in]*/ Float64 z, /*[out, retval]*/ Float64 *pVal);
	STDMETHOD(ThroughAltitude)(/*[in]*/ Float64 altitude);
	STDMETHOD(ThroughLineEx)(/*[in]*/ ILine2d* pLine,/*[in]*/ IPoint3d* pPnt);
	STDMETHOD(ThroughPoints)(/*[in]*/ IPoint3d* p1,/*[in]*/ IPoint3d* p2,/*[in]*/ IPoint3d* p3);
   STDMETHOD(Clone)(/*[out,retval]*/IPlane3d** clone);

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__PLANE3D_H_
