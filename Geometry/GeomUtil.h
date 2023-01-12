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

// GeomUtil.h : Declaration of the CGeomUtil

#ifndef __GEOMUTIL_H_
#define __GEOMUTIL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGeomUtil
class ATL_NO_VTABLE CGeomUtil : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGeomUtil, &CLSID_GeomUtil>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CGeomUtil,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IGeomUtil,
	public IGeomUtil2d
   {
public:
	CGeomUtil()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_GEOMUTIL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGeomUtil)
	COM_INTERFACE_ENTRY(IGeomUtil)
	COM_INTERFACE_ENTRY(IGeomUtil2d)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   // cached objects for speed efficiencies
   CComPtr<IVector2d> m_Vector;

// ISupportErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IGeomUtil
public:
	STDMETHOD(get_Geom2d)(/*[out,retval]*/ IGeomUtil2d** util) override;

// IGeomUtil2d
public:
   STDMETHOD(CreateParallelLineSegment)(/*[in]*/ ILineSegment2d* pSeg,/*[in]*/Float64 offset,/*[out.retval]*/ ILineSegment2d** pNewSeg) override;
	STDMETHOD(IsLineParallelToLineSegment)(/*[in]*/ILine2d* pLine,/*[in]*/ ILineSegment2d* pSeg,/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(AreLineSegmentsParallel)(/*[in]*/ ILineSegment2d* pSeg1,/*[in]*/ ILineSegment2d* pSeg2,/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(AreLinesParallel)(/*[in]*/ ILine2d* pLine1,/*[in]*/ ILine2d* pLine2,/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(IsSameDirection)(/*[in]*/ ILine2d* pLine1,/*[in]*/ ILine2d* pLine2,/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(IntersectLineWithLineSegment)(/*[in]*/ ILine2d* pLine,/*[in]*/ ILineSegment2d* pSeg,/*[out,retval]*/ IPoint2d** ppPoint) override;
	STDMETHOD(SegSegIntersect)(/*[in]*/ ILineSegment2d* pSeg1,/*[in]*/ ILineSegment2d* pSeg2,/*[out,retval]*/ IPoint2d** ppPoint) override;
   STDMETHOD(LineLineIntersect)(/*[in]*/ILine2d* l1, /*[in]*/ILine2d *l2, /*[out,retval]*/IPoint2d **ppPoint) override;
	STDMETHOD(DivideArc)(/*[in]*/ IPoint2d* pStart,/*[in]*/ IPoint2d* pCenter,/*[in]*/ IPoint2d* pEnd,/*[in]*/ IndexType nSpaces,/*[out,retval]*/ IPoint2dCollection** ppPoints) override;
	STDMETHOD(CreateNormalLineThroughPoint)(/*[in]*/ ILine2d* pLine,/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ ILine2d** ppLine) override;
   STDMETHOD(CreateParallelLine)(/*[in]*/ ILine2d* pLine,/*[in]*/ Float64 dist,/*[out,retval]*/ILine2d** ppLine) override;
	STDMETHOD(CreateParallelLineThroughPoint)(/*[in]*/ ILine2d* pLine,/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ ILine2d** ppLine) override;
   STDMETHOD(PointOnLineNearest)(/*[in]*/ ILine2d* pLine,/*[in]*/ IPoint2d* pPoint, /*[out,retval]*/ IPoint2d** ppPOLN) override;
	STDMETHOD(ShortestOffsetToPoint)(/*[in]*/ ILine2d* pLine,/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ Float64* pOffset) override;
	STDMETHOD(Angle)(/*[in]*/ IPoint2d* pStart,/*[in]*/ IPoint2d* pCenter,/*[in]*/ IPoint2d* pEnd,/*[out,retval]*/ Float64* angle) override;
	STDMETHOD(GenerateCircle)(/*[in]*/ IndexType nPoints,/*[in]*/ IPoint2d* center,/*[in]*/ Float64 radius, /*[in]*/ Float64 initAngle,/*[out,retval]*/ IPoint2dCollection** points) override;
	STDMETHOD(LineCircleIntersect)(/*[in]*/ ILine2d *line,/*[in]*/ ICircle* circle,/*[out]*/ IPoint2d** p1,/*[out]*/ IPoint2d** p2,/*[out,retval]*/ short* nIntersect) override;
	STDMETHOD(CircleCircleIntersect)(/*[in]*/ ICircle* circle1,/*[in]*/ ICircle* circle2,/*[out]*/ IPoint2d** p1,/*[out]*/ IPoint2d** p2,/*[out,retval]*/ short* nIntersect) override;
   STDMETHOD(PointInTriangle)(/*[in]*/IPoint2d* p,/*[in]*/IPoint2d* pA,/*[in]*/IPoint2d* pB,/*[in]*/IPoint2d* pC,/*[out,retval]*/VARIANT_BOOL* pbResult) override;
};

#endif //__GEOMUTIL_H_
