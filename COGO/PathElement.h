///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// PathElement.h : Declaration of the CPathElement

#ifndef __PATHELEMENT_H_
#define __PATHELEMENT_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"

/////////////////////////////////////////////////////////////////////////////
// CPathElement
class ATL_NO_VTABLE CPathElement : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPathElement,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPathElement, &CLSID_PathElement>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPathElement,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CPathElement>,
	public IPathElement,
	public IHorzCurveEvents,
	public ILineSegment2dEvents,
	public IPoint2dEvents,
   public ICubicSplineEvents,
	public IStructuredStorage2,
	public CProxyDPathElementEvents< CPathElement >,
   public IPersistImpl<CPathElement>
{
public:
	CPathElement()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PATHELEMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPathElement)
	COM_INTERFACE_ENTRY(IPathElement)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IHorzCurveEvents)
	COM_INTERFACE_ENTRY(ILineSegment2dEvents)
	COM_INTERFACE_ENTRY(IPoint2dEvents)
	COM_INTERFACE_ENTRY(ICubicSplineEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPathElement)
CONNECTION_POINT_ENTRY(IID_IPathElementEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPathElement
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(Move)(/*[in]*/ Float64 dist,/*[in]*/ IDirection* direction);
   STDMETHOD(Clone)(/*[out,retval]*/ IPathElement* *clone);
	STDMETHOD(get_Value)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(putref_Value)(/*[in]*/ IUnknown* newVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ PathElementType *pVal);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// IHorzCurveEvents
	STDMETHOD(OnHorzCurveChanged)(IHorzCurve * hc)
	{
      ATLASSERT(m_Value.IsEqualObject(hc));
      Fire_OnPathElementChanged(this);
      return S_OK;
	}
// ILineSegment2dEvents
	STDMETHOD(OnLineSegmentChanged)(ILineSegment2d * lineSeg)
	{
      ATLASSERT(m_Value.IsEqualObject(lineSeg));
      Fire_OnPathElementChanged(this);
      return S_OK;
	}
// IPoint2dEvents
	STDMETHOD(OnPointChanged)(IPoint2d * point)
	{
      ATLASSERT(m_Value.IsEqualObject(point));
      Fire_OnPathElementChanged(this);
      return S_OK;
	}
// ICubicSplineEvents
	STDMETHOD(OnSplineChanged)(ICubicSpline * spline)
	{
      ATLASSERT(m_Value.IsEqualObject(spline));
      Fire_OnPathElementChanged(this);
      return S_OK;
	}
private:
   PathElementType m_Type;
   CComPtr<IUnknown> m_Value;
   DWORD m_dwCookie;

   void Advise();
   void Unadvise();
};

#endif //__PATHELEMENT_H_
