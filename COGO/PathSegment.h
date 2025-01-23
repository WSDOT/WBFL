///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// PathElement.h : Declaration of the CPathElement

#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPathSegment
class ATL_NO_VTABLE CPathSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPathElement,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPathSegment, &CLSID_PathSegment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPathSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IPathSegment,
   public IPathElement // see note on ICompoundCurve interface definition in IDL file
{
public:
   CPathSegment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetPathSegment(std::shared_ptr<WBFL::COGO::PathSegment> segment) { m_Curve = segment; }
   std::shared_ptr<WBFL::COGO::PathSegment> GetPathSegment(){ return m_Curve; }

DECLARE_REGISTRY_RESOURCEID(IDR_PATHSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPathSegment)
   COM_INTERFACE_ENTRY(IPathSegment)
   COM_INTERFACE_ENTRY(IPathElement)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPathSegment
public:
   STDMETHOD(ThroughPoints)(IPoint2d* pStart,IPoint2d* pEnd) override;
   STDMETHOD(Offset)(Float64 offset) override;

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
   std::shared_ptr<WBFL::COGO::PathSegment> m_Curve;
};
