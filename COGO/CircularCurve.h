///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// CircularCurve.h : Declaration of the CCircularCurve

#ifndef __CircularCurve_H_
#define __CircularCurve_H_
#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CCircularCurve
class ATL_NO_VTABLE CCircularCurve : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CCircularCurve,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CCircularCurve, &CLSID_CircularCurve>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCircularCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ICircularCurve,
   public IPathElement // see note on ICompoundCurve interface definition in IDL file
{
public:
	CCircularCurve()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetCurve(std::shared_ptr<WBFL::COGO::CircularCurve> curve) { m_Curve = curve; }
   std::shared_ptr<WBFL::COGO::CircularCurve> GetCurve() { return m_Curve; }

DECLARE_REGISTRY_RESOURCEID(IDR_CIRCULARCURVE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCircularCurve)
	COM_INTERFACE_ENTRY(ICircularCurve)
	COM_INTERFACE_ENTRY(IPathElement)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICircularCurve
public:
   STDMETHOD(get_DegreeCurvature)(/*[in]*/ Float64 D,/*[in]*/ DegreeCurvatureType dcMethod,/*[out,retval]*/ IAngle** pDC) override;
   STDMETHOD(get_Direction)(/*[out,retval]*/ CurveDirectionType* dir) override;
   STDMETHOD(get_Center)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_External)(/*[out,retval]*/Float64* external) override;
   STDMETHOD(get_MidOrdinate)(/*[out,retval]*/Float64* mo) override;
	STDMETHOD(get_Tangent)(/*[out,retval]*/Float64* tangent) override;
	STDMETHOD(get_Chord)(/*[out,retval]*/Float64* chord) override;
	STDMETHOD(get_TangentLength)(/*[out,retval]*/Float64* t) override;
   STDMETHOD(get_Angle)(/*[out,retval]*/ IAngle* *pVal) override;
	STDMETHOD(get_BkTangentBrg)(/*[out, retval]*/ IDirection* *pVal) override;
	STDMETHOD(get_FwdTangentBrg)(/*[out, retval]*/ IDirection* *pVal) override;
	STDMETHOD(get_PC)(/*[out, retval]*/ IPoint2d** pVal) override;
	STDMETHOD(get_PT)(/*[out, retval]*/ IPoint2d** pVal) override;
	STDMETHOD(get_Radius)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Radius)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_PFT)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(put_PFT)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_PI)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(put_PI)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_PBT)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(put_PBT)(/*[in]*/ IPoint2d* newVal) override;

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
   std::shared_ptr<WBFL::COGO::CircularCurve> m_Curve;
};

#endif //__CircularCurve_H_
