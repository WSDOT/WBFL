///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2025  Washington State Department of Transportation
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

// CubicSpline.h : Declaration of the CCubicSpline

#ifndef __CUBICSPLINE_H_
#define __CUBICSPLINE_H_
#pragma once

#include "resource.h"       // main symbols
#include <vector>
#include <Math\Math.h>

class CSplineSegment;

/////////////////////////////////////////////////////////////////////////////
// CCubicSpline
class ATL_NO_VTABLE CCubicSpline : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCubicSpline, &CLSID_CubicSpline>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCubicSpline,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ICubicSpline,
   public IPathElement // see note on ICompoundCurve interface definition in IDL file
{
public:
	CCubicSpline()
	{
   }

   HRESULT FinalConstruct();
   void FinalRelease();
   
   void SetSpline(std::shared_ptr<WBFL::COGO::CubicSpline> spline) { m_Curve = spline; }
   std::shared_ptr<WBFL::COGO::CubicSpline> GetSpline() { return m_Curve; }

DECLARE_REGISTRY_RESOURCEID(IDR_CUBICSPLINE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCubicSpline)
   COM_INTERFACE_ENTRY(ICubicSpline)
   COM_INTERFACE_ENTRY(IPathElement)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICubicSpline
public:
   STDMETHOD(AddPoints)(/*[in]*/IPoint2dCollection* points) override;
	STDMETHOD(AddPoint)(/*[in]*/Float64 x,/*[in]*/Float64 y) override;
	STDMETHOD(AddPointEx)(/*[in]*/IPoint2d* point) override;
   STDMETHOD(get_PointCount)(/*[out,retval]*/IndexType* nPoints) override;
	STDMETHOD(get_Point)(/*[in]*/IndexType idx,/*[out,retval]*/IPoint2d** point) override;
   STDMETHOD(get_Points)(/*[out,retval]*/IPoint2dCollection** ppPoints) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(put_StartDirection)(/*[in]*/ VARIANT varDirection) override;
	STDMETHOD(get_StartDirection)(/*[out,retval]*/IDirection** dir) override;
	STDMETHOD(put_EndDirection)(/*[in]*/ VARIANT varDirection) override;
	STDMETHOD(get_EndDirection)(/*[out,retval]*/IDirection** dir) override;
   STDMETHOD(BearingAtPoint)(/*[in]*/IndexType idx,/*[out,retval]*/IDirection** pDir) override;
   STDMETHOD(NormalAtPoint)(/*[in]*/IndexType idx,/*[out,retval]*/IDirection** pDir) override;
   STDMETHOD(DistanceFromStartAtPoint)(/*[in]*/ IndexType idx,/*[out,retval]*/ Float64* dist) override;

   // IPathElement
public:
   STDMETHOD(Clone)(IPathElement** clone) override;
   STDMETHOD(Move)(Float64 dist, VARIANT varDirection) override;
   STDMETHOD(Offset)(Float64 dx, Float64 dy) override;
   STDMETHOD(PointOnCurve)(Float64 distance, IPoint2d** pVal) override;
   STDMETHOD(GetStartPoint)(IPoint2d** ppPoint) override;
   STDMETHOD(GetEndPoint)(IPoint2d** ppPoint) override;
   STDMETHOD(GetLength)(Float64* pLength) override;
   STDMETHOD(GetKeyPoints)(IPoint2dCollection** ppPoints) override;
   STDMETHOD(LocatePoint)(Float64 distFromStart, OffsetMeasureType offsetType, Float64 offset, VARIANT varDirection, IPoint2d** ppPoint) override;
   STDMETHOD(GetBearing)(Float64 distFromStart, IDirection** ppDirection) override;
   STDMETHOD(GetNormal)(Float64 distFromStart, IDirection** ppNormal) override;
   STDMETHOD(ProjectPoint)(IPoint2d* point, IPoint2d** ppProjPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection) override;
   STDMETHOD(Intersect)(ILine2d* pLine, VARIANT_BOOL vbProjectBack, VARIANT_BOOL vbProjectAhead, IPoint2dCollection** ppPoints) override;
   STDMETHOD(CreateOffsetPath)(Float64 offset, IPath** ppPath) override;
   STDMETHOD(CreateSubpath)(Float64 start, Float64 end, IPath** ppPath) override;

private:
   std::shared_ptr<WBFL::COGO::CubicSpline> m_Curve;
};

#endif //__CUBICSPLINE_H_
