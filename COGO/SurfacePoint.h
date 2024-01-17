///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// SurfacePoint.h : Declaration of the CSurfacePoint

#ifndef __SURFACEPOINT_H_
#define __SURFACEPOINT_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSurfacePoint
class ATL_NO_VTABLE CSurfacePoint : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSurfacePoint, &CLSID_SurfacePoint>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CSurfacePoint,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ISurfacePoint
{
public:
	CSurfacePoint()
	{
		m_pSurface = nullptr;
	}

 	HRESULT FinalConstruct();

   void SetSurfacePoint(std::shared_ptr<WBFL::COGO::SurfacePoint>& sp) { m_SurfacePoint = sp; }
   std::shared_ptr<WBFL::COGO::SurfacePoint> GetSurfacePoint() { return m_SurfacePoint; }


DECLARE_REGISTRY_RESOURCEID(IDR_SURFACEPOINT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurfacePoint)
	COM_INTERFACE_ENTRY(ISurfacePoint)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISurfacePoint
public:
   STDMETHOD(get_Surface)(ISurface* *pVal) override;
   STDMETHOD(putref_Surface)(ISurface* newVal) override;
	STDMETHOD(get_Station)(/*[out, retval]*/ IStation* *station) override;
	STDMETHOD(put_Station)(/*[in]*/ VARIANT varStation) override;
	STDMETHOD(get_NormalOffset)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_NormalOffset)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_CutLineOffset)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_CutLineOffset)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Elevation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Elevation)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_Location)(/*[out,retval]*/IPoint2d** ppLocation) override;
   STDMETHOD(put_Location)(/*[in]*/IPoint2d* ppLocation) override;
   STDMETHOD(GetPoint)(/*[out,retval]*/IPoint3d** ppPoint) override;

private:
   std::shared_ptr<WBFL::COGO::SurfacePoint> m_SurfacePoint;
   ISurface* m_pSurface; // weak reference
};

#endif //__SURFACEPOINT_H_
