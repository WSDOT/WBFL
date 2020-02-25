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

// LineSegment3d.h : Declaration of the CLineSegment3d

#ifndef __LineSegment3d_H_
#define __LineSegment3d_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CLineSegment3d
class ATL_NO_VTABLE CLineSegment3d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLineSegment3d, &CLSID_LineSegment3d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CLineSegment3d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public ILineSegment3d,
   public IStructuredStorage2,
   public IPersist,
   public CProxyDLineSegment3dEvents< CLineSegment3d >,
   public IConnectionPointContainerImpl<CLineSegment3d>,
   public IPoint3dEvents
{
public:
	CLineSegment3d()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_LINESEGMENT3D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLineSegment3d)
	COM_INTERFACE_ENTRY(ILineSegment3d)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint3dEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLineSegment3d)
	CONNECTION_POINT_ENTRY(IID_ILineSegment3dEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IPoint3d> m_pStart;
   CComPtr<IPoint3d> m_pEnd;
   DWORD m_dwStartCookie;
   DWORD m_dwEndCookie;

   bool m_bEventsOn;
   void EventsOff();
   void EventsOn(bool bFire=true);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILineSegment3d
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/ILineSegment3d** ppClone) override;
   STDMETHOD(ThroughPoints)(/*[in]*/ IPoint3d* p1, /*[in]*/ IPoint3d* p2) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize3d* pSize) override;
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy,/*[in]*/ Float64 dz) override;
	//STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pCenter,/*[in]*/ Float64 angle) override;
	//STDMETHOD(Rotate)(/*[in]*/ Float64 cx, /*[in]*/ Float64 cy, /*[in]*/ Float64 angle) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_EndPoint)(/*[out, retval]*/ IPoint3d* *pVal) override;
	STDMETHOD(putref_EndPoint)(/*[in]*/ IPoint3d* newVal) override;
	STDMETHOD(get_StartPoint)(/*[out, retval]*/ IPoint3d* *pVal) override;
	STDMETHOD(putref_StartPoint)(/*[in]*/ IPoint3d* newVal) override;

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;
public :

// IPoint3dEvents
	STDMETHOD(OnPointChanged)(IPoint3d * point)
	{
      if ( m_bEventsOn )
         Fire_OnLineSegmentChanged(this);

      return S_OK;
	}
};

#endif //__LineSegment3d_H_
