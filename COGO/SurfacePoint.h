///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// SurfacePoint.h : Declaration of the CSurfacePoint

#ifndef __SURFACEPOINT_H_
#define __SURFACEPOINT_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"

/////////////////////////////////////////////////////////////////////////////
// CSurfacePoint
class ATL_NO_VTABLE CSurfacePoint : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSurfacePoint, &CLSID_SurfacePoint>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CSurfacePoint,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	//public IConnectionPointContainerImpl<CSurfacePoint>,
	//public CProxyDSurfacePointEvents< CSurfacePoint >,
   public ISurfacePoint,
   public IStructuredStorage2,
   public IPersistImpl<CSurfacePoint>
{
public:
	CSurfacePoint()
	{
      m_pSurface = NULL;
      m_Station = 0;
      m_NormalOffset = 0;
      m_CutLineOffset = 0;
      m_Elevation = 0;
	}

   	HRESULT FinalConstruct();


DECLARE_REGISTRY_RESOURCEID(IDR_SURFACEPOINT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurfacePoint)
	COM_INTERFACE_ENTRY(ISurfacePoint)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	//COM_INTERFACE_ENTRY(IConnectionPointContainer)
	//COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSurfacePoint)
//CONNECTION_POINT_ENTRY(IID_ISurfacePointEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISurfacePoint
public:
   STDMETHOD(get_Surface)(ISurface* *pVal);
   STDMETHOD(putref_Surface)(ISurface* newVal);
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
	STDMETHOD(get_Station)(/*[out, retval]*/ IStation* *station);
	STDMETHOD(put_Station)(/*[in]*/ VARIANT varStation);
	STDMETHOD(get_NormalOffset)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_NormalOffset)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_CutLineOffset)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_CutLineOffset)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Elevation)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Elevation)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_Location)(/*[out,retval]*/IPoint2d** ppLocation);
   STDMETHOD(put_Location)(/*[in]*/IPoint2d* ppLocation);
   STDMETHOD(GetPoint)(/*[out,retval]*/IPoint3d** ppPoint);
   STDMETHOD(Clone)(/*[out,retval]*/ ISurfacePoint* *clone);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

private:
   ISurface* m_pSurface; // weak reference
   CComPtr<IStation> m_Station; // station where a line normal to the alignment passes through this surface point
   Float64 m_NormalOffset; // offset of this surface point, normal to the alignment at station
   Float64 m_CutLineOffset; // offset of this surface point, measured along the cut line from the alignment
   Float64 m_Elevation; // elevation of this surface point
   CComPtr<IPoint2d> m_Location; // this is the location of the point in 2D global coordinates

   HRESULT ValidateStation(IStation* station);
};

#endif //__SURFACEPOINT_H_
