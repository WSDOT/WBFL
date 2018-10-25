///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2012  Washington State Department of Transportation
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

// LineSegment2d.h : Declaration of the CLineSegment2d

#ifndef __LINESEGMENT2D_H_
#define __LINESEGMENT2D_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CLineSegment2d
class ATL_NO_VTABLE CLineSegment2d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLineSegment2d, &CLSID_LineSegment2d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CLineSegment2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public ILineSegment2d,
   public IStructuredStorage2,
   public IPersist,
   public CProxyDLineSegment2dEvents< CLineSegment2d >,
   public IConnectionPointContainerImpl<CLineSegment2d>,
   public IPoint2dEvents
{
public:
	CLineSegment2d()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_LINESEGMENT2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLineSegment2d)
	COM_INTERFACE_ENTRY(ILineSegment2d)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLineSegment2d)
	CONNECTION_POINT_ENTRY(IID_ILineSegment2dEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IPoint2d> m_pStart;
   CComPtr<IPoint2d> m_pEnd;
   DWORD m_dwStartCookie;
   DWORD m_dwEndCookie;

   bool m_bEventsOn;
   void EventsOff();
   void EventsOn(bool bFire=true);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILineSegment2d
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(Clone)(/*[out,retval]*/ILineSegment2d** ppClone);
   STDMETHOD(ThroughPoints)(/*[in]*/ IPoint2d* p1, /*[in]*/ IPoint2d* p2);
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize);
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy);
   STDMETHOD(Offset2)(/*[in]*/ Float64 distance);
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pCenter,/*[in]*/ Float64 angle);
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx, /*[in]*/ Float64 cy, /*[in]*/ Float64 angle);
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_EndPoint)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(putref_EndPoint)(/*[in]*/ IPoint2d* newVal);
	STDMETHOD(get_StartPoint)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(putref_StartPoint)(/*[in]*/ IPoint2d* newVal);

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
public :

// IPoint2dEvents
	STDMETHOD(OnPointChanged)(IPoint2d * point)
	{
      if ( m_bEventsOn )
         Fire_OnLineSegmentChanged(this);

      return S_OK;
	}
};

#endif //__LINESEGMENT2D_H_
