///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// CogoEngine.h : Declaration of the CCogoEngine

#ifndef __COGOENGINE_H_
#define __COGOENGINE_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCogoEngine
class ATL_NO_VTABLE CCogoEngine : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCogoEngine, &CLSID_CogoEngine>,
	public ISupportErrorInfo,
	public ICogoEngine,
   public IMeasure2,
   public ILocate2,
   public IIntersect2,
   public IProject2,
   public IDivide2,
   public ITangent2
{
public:
	CCogoEngine()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_COGOENGINE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCogoEngine)
	COM_INTERFACE_ENTRY(ICogoEngine)
	COM_INTERFACE_ENTRY(ILocate2)
	COM_INTERFACE_ENTRY(IIntersect2)
	COM_INTERFACE_ENTRY(IProject2)
	COM_INTERFACE_ENTRY(IDivide2)
	COM_INTERFACE_ENTRY(ITangent2)
	COM_INTERFACE_ENTRY(IMeasure2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICogoEngine
public:
   STDMETHOD(get_Intersect)(/*[out, retval]*/ IIntersect2* *pVal) override;
   STDMETHOD(get_Locate)(/*[out, retval]*/ ILocate2* *pVal) override;
   STDMETHOD(get_Measure)(/*[out, retval]*/ IMeasure2* *pVal) override;
   STDMETHOD(get_Project)(/*[out, retval]*/ IProject2* *pVal) override;
   STDMETHOD(get_Divide)(/*[out, retval]*/ IDivide2* *pVal) override;
   STDMETHOD(get_Tangent)(/*[out, retval]*/ ITangent2* *pVal) override;

// IMeasure2
public:
   STDMETHOD(Angle)(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* vertex,/*[in]*/ IPoint2d* to,/*[out,retval]*/ IAngle** angle) override;
   STDMETHOD(Area)(/*[in]*/ IPoint2dCollection* points,/*[out,retval]*/ Float64* area) override;
   STDMETHOD(Distance)(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to,/*[out,retval]*/ Float64* dist) override;
   STDMETHOD(Direction)(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to,/*[out,retval]*/ IDirection** dir) override;
   STDMETHOD(Inverse)(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to,/*[out]*/ Float64* dist,/*[out]*/ IDirection** dir) override;

// ILocate2
public:
   STDMETHOD(ByDistAngle)(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varAngle, /*[in]*/ Float64 offset,/*[out,retval]*/IPoint2d** point) override;
   STDMETHOD(ByDistDefAngle)(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* to, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDefAngle, /*[in]*/ Float64 offset, /*[out,retval]*/ IPoint2d** point) override;
   STDMETHOD(ByDistDir)(/*[in]*/ IPoint2d* from, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset,/*[out,retval]*/ IPoint2d** point) override;
   STDMETHOD(PointOnLine)(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* to, /*[in]*/ Float64 dist, /*[in]*/ Float64 offset,/*[out,retval]*/ IPoint2d** point) override;
   STDMETHOD(ParallelLineByPoints)(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to, /*[in]*/ Float64 offset,/*[out]*/IPoint2d** p1,/*[out]*/IPoint2d** p2) override;
   STDMETHOD(ParallelLineSegment)(/*[in]*/ ILineSegment2d* ls,/*[in]*/ Float64 offset,/*[out,retval]*/ ILineSegment2d** linesegment) override;

// IIntersect2
public:
   STDMETHOD(Bearings)(/*[in]*/ IPoint2d* p1, /*[in]*/ VARIANT varDir1, /*[in]*/ Float64 offset1,/*[in]*/ IPoint2d* p2, /*[in]*/ VARIANT varDir2, /*[in]*/ Float64 offset2, /*[out,retval]*/ IPoint2d** point) override;
   STDMETHOD(BearingCircle)(/*[in]*/ IPoint2d* p1, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset,/*[in]*/ IPoint2d* center, /*[in]*/ Float64 radius, /*[in]*/ IPoint2d* nearest, /*[out,retval]*/ IPoint2d** point) override;
   STDMETHOD(Circles)(/*[in]*/ IPoint2d* p1, /*[in]*/ Float64 r1, /*[in]*/ IPoint2d* p2, /*[in]*/ Float64 r2, /*[in]*/ IPoint2d* nearest, /*[out,retval]*/ IPoint2d** point) override;
   STDMETHOD(LineByPointsCircle)(/*[in]*/ IPoint2d* p1, /*[in]*/ IPoint2d* p2, /*[in]*/ Float64 offset,/*[in]*/ IPoint2d* center, /*[in]*/ Float64 radius, /*[in]*/ IPoint2d* nearest, /*[out,retval]*/ IPoint2d** point) override;
   STDMETHOD(LinesByPoints)(/*[in]*/ IPoint2d* p11, /*[in]*/ IPoint2d* p12, /*[in]*/ Float64 offset1,/*[in]*/ IPoint2d* p21, /*[in]*/ IPoint2d* p22, /*[in]*/ Float64 offset2, /*[out,retval]*/ IPoint2d** point) override;
   STDMETHOD(Lines)(/*[in]*/ILineSegment2d* l1,/*[in]*/Float64 offset1,/*[in]*/ILineSegment2d* l2,/*[in]*/Float64 offset2,/*[out,retval]*/ IPoint2d** point) override;
   STDMETHOD(LineSegmentCircle)(/*[in]*/ ILineSegment2d* pSeg, /*[in]*/ Float64 offset,/*[in]*/ IPoint2d* center, /*[in]*/ Float64 radius, /*[in]*/ IPoint2d* nearest, /*[out,retval]*/ IPoint2d** point) override;

// IProject2
public:
   STDMETHOD(PointOnLineByPoints)(/*[in]*/ IPoint2d* pnt, /*[in]*/ IPoint2d* start, /*[in]*/ IPoint2d* end, /*[in]*/ Float64 offset,/*[out,retval]*/IPoint2d** point) override;
   STDMETHOD(PointOnLineSegment)(/*[in]*/ IPoint2d* from,/*[in]*/ ILineSegment2d* seg, /*[in]*/ Float64 offset, /*[out,retval]*/ IPoint2d** point) override;

// IDivide2
public:
   STDMETHOD(Arc)(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* vertex, /*[in]*/ IPoint2d* to,/*[in]*/ CollectionIndexType nParts,/*[out,retval]*/ IPoint2dCollection** points) override;
   STDMETHOD(BetweenPoints)(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* to,/*[in]*/ CollectionIndexType nParts,/*[out,retval]*/ IPoint2dCollection** points) override;
   STDMETHOD(LineSegment)(/*[in]*/ ILineSegment2d* seg,/*[in]*/ CollectionIndexType nParts,/*[out,retval]*/ IPoint2dCollection** points) override;
	STDMETHOD(CompoundCurve)(/*[in]*/ ICompoundCurve* curve, /*[in]*/ CollectionIndexType nParts, /*[out,retval]*/ IPoint2dCollection** points) override;
   STDMETHOD(Path)(/*[in]*/IPath* pPath,/*[in]*/ CollectionIndexType nParts,/*[in]*/ Float64 start,/*[in]*/ Float64 end,/*[out,retval]*/IPoint2dCollection** points) override;

// ITangent2
public:
   STDMETHOD(External)(/*[in]*/ IPoint2d* center1, /*[in]*/ Float64 radius1,/*[in]*/ IPoint2d* center2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign, /*[out]*/ IPoint2d** t1,/*[out]*/ IPoint2d** t2) override;
   STDMETHOD(Cross)(/*[in]*/ IPoint2d* center1, /*[in]*/ Float64 radius1,/*[in]*/ IPoint2d* center2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign, /*[out]*/ IPoint2d** t1,/*[out]*/ IPoint2d** t2) override;
   STDMETHOD(Point)(/*[in]*/ IPoint2d* center, /*[in]*/ Float64 radius,/*[in]*/ IPoint2d* point, /*[in]*/ TangentSignType sign, /*[out]*/ IPoint2d** tangent) override;
};

#endif //__COGOENGINE_H_
