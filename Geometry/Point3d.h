///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// Point3d.h : Declaration of the CPoint3d

#ifndef __POINT3D_H_
#define __POINT3D_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CPoint3d
class ATL_NO_VTABLE CPoint3d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPoint3d, &CLSID_Point3d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CPoint3d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IPoint3d,
   public IStructuredStorage2,
   public IPersist,
   public CProxyDPoint3dEvents< CPoint3d >,
   public IConnectionPointContainerImpl<CPoint3d>
{
public:
	CPoint3d()
	{
      m_X = 0.00;
      m_Y = 0.00;
      m_Z = 0.00;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_POINT3D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPoint3d)
	COM_INTERFACE_ENTRY(IPoint3d)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPoint3d)
	CONNECTION_POINT_ENTRY(IID_IPoint3dEvents)
END_CONNECTION_POINT_MAP()

private:
   Float64 m_X;
   Float64 m_Y;
   Float64 m_Z;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPoint3d
public:
   STDMETHOD(Clone)(/*[out,retval]*/IPoint3d** ppPoint);
   STDMETHOD(Location)(/*[out]*/Float64* pX,/*[out]*/Float64* pY,/*[out]*/Float64* pZ);
   STDMETHOD(SameLocation)(/*[in]*/IPoint3d* pOther);
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 cz, /*[in]*/ IVector3d* vector,/*[in]*/ Float64 angle);
   STDMETHOD(RotateEx)(/*[in]*/ IPoint3d* center,/*[in]*/ IVector3d* vector,/*[in]*/ Float64 angle);
	STDMETHOD(OffsetEx)(/*[in]*/ ISize3d* pSize);
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy,/*[in]*/ Float64 dz);
	STDMETHOD(MoveEx)(/*[in]*/ IPoint3d* pPoint);
	STDMETHOD(Move)(/*[in]*/ Float64 x,/*[in]*/ Float64 y,/*[in]*/ Float64 z);
	STDMETHOD(get_Z)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Z)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Y)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Y)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_X)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_X)(/*[in]*/ Float64 newVal);

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

};

#endif //__POINT3D_H_
