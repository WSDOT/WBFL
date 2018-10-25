///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// ParabolicTendonSegment.h : Declaration of the CParabolicTendonSegment
#pragma once

#include "resource.h"       // main symbols
//#include "GenericBridgeCP.h"

#include <Math\Math.h>


/////////////////////////////////////////////////////////////////////////////
// CParabolicTendonSegment
class ATL_NO_VTABLE CParabolicTendonSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CParabolicTendonSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CParabolicTendonSegment, &CLSID_ParabolicTendonSegment>,
	public ISupportErrorInfo,
	public IParabolicTendonSegment,
   public IStructuredStorage2,
//   public CProxyDParabolicTendonSegmentEvents< CParabolicTendonSegment >,
//   public IParabolicTendonSegmentPointContainerImpl<CParabolicTendonSegment>,
   public IObjectSafetyImpl<CParabolicTendonSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CParabolicTendonSegment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PARABOLICTENDONSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CParabolicTendonSegment)
	COM_INTERFACE_ENTRY(IParabolicTendonSegment)
   COM_INTERFACE_ENTRY(ITendonSegment)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
//   COM_INTERFACE_ENTRY_IMPL(IParabolicTendonSegmentPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CParabolicTendonSegment)
//	CONNECTION_POINT_ENTRY(IID_IParabolicTendonSegmentEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IPoint3d> m_Start;
   CComPtr<IPoint3d> m_End;
   Float64 m_Slope; // slope at either the start or end of the tendon segment (must be zero for now)
                    // when generalized, slope may need to be a vector as it is actually a 3D quantity
   DirectionType m_SlopeEnd; // specifies which end of the tendon segment has a slope of m_Slope
   CComPtr<IGeomUtil3d> m_GeomUtil;

   mathPolynomial2d GetParabolaX(); // parabola looking in elevation
   mathPolynomial2d GetParabolaY(); // parabola looking in plan (think parabolic tendon in sloped U-beam web, top view)

   ITendon* m_pTendon;

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IParabolicTendonSegment
public:
   STDMETHOD(put_Start)(/*[in]*/ IPoint3d* start);
	STDMETHOD(get_Start)(/*[out,retval]*/ IPoint3d** start);
	STDMETHOD(put_End)(/*[in]*/ IPoint3d* end);
   STDMETHOD(get_End)(/*[out,retval]*/ IPoint3d** end);
   STDMETHOD(put_Slope)(Float64 slope);
   STDMETHOD(get_Slope)(Float64* slope);
   STDMETHOD(put_SlopeEnd)(DirectionType end);
   STDMETHOD(get_SlopeEnd)(DirectionType* end);

// ITendonSegment
public:
   STDMETHOD(get_Position)(/*[in]*/ TendonMeasure measure,/*[in]*/ Float64 z,/*[out,retval]*/ IPoint3d** cg);
	STDMETHOD(get_Slope)(/*[in]*/ Float64 z,/*[out,retval]*/ IVector3d** slope);
	STDMETHOD(get_Length)(/*[out,retval]*/ Float64* length);
   STDMETHOD(ProjectedLength)(/*[out]*/ Float64* dx,/*[out]*/ Float64* dy,/*[out]*/ Float64* dz);
   STDMETHOD(get_Centerline)(/*[in]*/ TendonMeasure measure,/*[out,retval]*/IPoint3dCollection** ppPoints);
   STDMETHOD(putref_Tendon)(/*[in]*/ITendon* pTendon);
   STDMETHOD(get_Tendon)(/*[out,retval]*/ITendon** ppTendon);
   STDMETHOD(get_MinimumRadiusOfCurvature)(/*[out,retval]*/Float64* pMinRadiusOfCurvature);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};
