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

// TransitionCurve.h : Declaration of the CTransitionCurve

#pragma once

#include "resource.h"       // main symbols



/////////////////////////////////////////////////////////////////////////////
// CTransitionCurve
class ATL_NO_VTABLE CTransitionCurve : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CTransitionCurve,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CTransitionCurve, &CLSID_TransitionCurve>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CTransitionCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ITransitionCurve,
   public IPathElement // see note on ICompoundCurve interface definition in IDL file
{
public:
	CTransitionCurve()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetCurve(std::shared_ptr<WBFL::COGO::TransitionCurve> curve) { m_Curve = curve; }
   std::shared_ptr<WBFL::COGO::TransitionCurve> GetCurve() { return m_Curve; }

DECLARE_REGISTRY_RESOURCEID(IDR_TRANSITIONCURVE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTransitionCurve)
   COM_INTERFACE_ENTRY(ITransitionCurve)
   COM_INTERFACE_ENTRY(IPathElement)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ITransitionCurve
public:
   STDMETHOD(Init)(/*[in]*/IPoint2d* pStart, /*[in]*/VARIANT varStartDirection, /*[in]*/Float64 R1, /*[in]*/Float64 R2, /*[in]*/Float64 L,/*[in]*/TransitionCurveType type) override;
   STDMETHOD(get_Type)(/*[out, retval]*/TransitionCurveType* pType);
   STDMETHOD(get_R1)(/*[out, retval]*/Float64* pR1) override;
   STDMETHOD(get_R2)(/*[out, retval]*/Float64* pR2) override;
   STDMETHOD(GetRadius)(/*[in]*/Float64 distance, /*[out, retval]*/Float64* pRadius) override;
   STDMETHOD(get_X)(/*[out, retval]*/Float64* x) override;
   STDMETHOD(get_Y)(/*[out, retval]*/Float64* y) override;
   STDMETHOD(get_LongTangent)(/*[out, retval]*/Float64* u) override;
   STDMETHOD(get_ShortTangent)(/*[out, retval]*/Float64* v) override;
   STDMETHOD(get_PI)(/*[out, retval]*/IPoint2d** pPI) override;
   STDMETHOD(get_Angle)(/*[out, retval]*/IAngle** ppAngle) override;
   STDMETHOD(get_Direction)(/*[out,retval]*/ CurveDirectionType* dir) override;

   STDMETHOD(get_StartDirection)(/*[out, retval]*/IDirection** pStartDirection) override;
   STDMETHOD(get_EndDirection)(/*[out, retval]*/IDirection** pEndDirection) override;

   STDMETHOD(DistanceFromStart)(/*[in]*/ IPoint2d* point, /*[out, retval]*/ Float64* dist);

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
   std::shared_ptr<WBFL::COGO::TransitionCurve> m_Curve;
};
