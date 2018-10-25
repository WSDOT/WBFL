///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 2008  Washington State Department of Transportation
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
#include "COGOCP.h"
#include <vector>
#include <Math\Math.h>

class CSplineSegment;

/////////////////////////////////////////////////////////////////////////////
// CCubicSpline
class ATL_NO_VTABLE CCubicSpline : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCubicSpline, &CLSID_Direction>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCubicSpline,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CCubicSpline>,
   public ICubicSpline,
   public IStructuredStorage2,
   public CProxyDCubicSplineEvents< CCubicSpline >,
   public IPersistImpl<CCubicSpline>
{
public:
	CCubicSpline()
	{
      m_bUpdateSpline = true;
      m_StartDirection = 0;
      m_EndDirection = 0;
      m_RotationAngle = 0;
   }

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_CUBICSPLINE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCubicSpline)
	COM_INTERFACE_ENTRY(ICubicSpline)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCubicSpline)
   CONNECTION_POINT_ENTRY(IID_ICubicSplineEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICubicSpline
public:
   STDMETHOD(AddPoints)(/*[in]*/IPoint2dCollection* points);
	STDMETHOD(AddPoint)(/*[in]*/Float64 x,/*[in]*/Float64 y);
	STDMETHOD(AddPointEx)(/*[in]*/IPoint2d* point);
   STDMETHOD(get_PointCount)(/*[out,retval]*/CollectionIndexType* nPoints);
	STDMETHOD(get_Point)(/*[in]*/CollectionIndexType idx,/*[out,retval]*/IPoint2d** point);
   STDMETHOD(get_Points)(/*[out,retval]*/IPoint2dCollection** ppPoints);
	STDMETHOD(get_StartPoint)(/*[out,retval]*/IPoint2d** point);
	STDMETHOD(get_EndPoint)(/*[out,retval]*/IPoint2d** point);
	STDMETHOD(Clear)();
	STDMETHOD(put_StartDirection)(/*[in]*/ VARIANT varDirection);
	STDMETHOD(get_StartDirection)(/*[out,retval]*/IDirection** dir);
	STDMETHOD(put_EndDirection)(/*[in]*/ VARIANT varDirection);
	STDMETHOD(get_EndDirection)(/*[out,retval]*/IDirection** dir);
   STDMETHOD(Bearing)(/*[in]*/ Float64 distance,/*[out,retval]*/IDirection* *pVal);
   STDMETHOD(BearingAtPoint)(/*[in]*/CollectionIndexType idx,/*[out,retval]*/IDirection** pDir);
	STDMETHOD(Normal)(/*[in]*/ Float64 distance,/*[out,retval]*/IDirection* *pVal);
   STDMETHOD(NormalAtPoint)(/*[in]*/CollectionIndexType idx,/*[out,retval]*/IDirection** pDir);
	STDMETHOD(PointOnSpline)(/*[in]*/ Float64 distance,/*[out,retval]*/IPoint2d* *pVal);
   STDMETHOD(ProjectPoint)(/*[in]*/ IPoint2d* point,/*[out,retval]*/ IPoint2d* *pNewPoint);
   STDMETHOD(DistanceFromStart)(/*[in]*/ IPoint2d* point,/*[out,retval]*/ Float64* dist);
   STDMETHOD(DistanceFromStartAtPoint)(/*[in]*/ CollectionIndexType idx,/*[out,retval]*/ Float64* dist);
	STDMETHOD(Intersect)(/*[in]*/ILine2d* line,/*[in]*/VARIANT_BOOL bProjectBack,/*[in]*/VARIANT_BOOL bProjectAhead,/*[out,retval]*/IPoint2dCollection** points);
   STDMETHOD(get_Length)(/*[out,retval]*/Float64* pLength);
   STDMETHOD(get_PointFactory)(/*[out,retval]*/ IPoint2dFactory* *factory);
   STDMETHOD(putref_PointFactory)(/*[in]*/ IPoint2dFactory *factory);
   STDMETHOD(Clone)(/*[out,retval]*/ ICubicSpline* *clone);
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pVal);
   STDMETHOD(Evaluate)(/*[in]*/Float64 x,/*[in]*/VARIANT_BOOL bProjectBack,/*[in]*/VARIANT_BOOL bProjectAhead,/*[out,retval]*/Float64* y);
	STDMETHOD(Slope)(/*[in]*/Float64 x,/*[in]*/VARIANT_BOOL bProjectBack,/*[in]*/VARIANT_BOOL bProjectAhead,/*[out,retval]*/Float64* dy);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

private:
   HRESULT UpdateSpline();

   HRESULT CreateSplineSegments();
   std::vector<CSplineSegment> m_SplineSegments;

   // distance = distance from start of cubic spline
   // return value = distance from start of spline segment
   CSplineSegment* FindSplineSegment(Float64 distance,Float64* pDistFromStartOfSegment);
   
   void CreatePoint(IPoint2d** ppPoint);

   HRESULT ProjectPoint(IPoint2d* point,Float64* pDistFromStart,IPoint2d* *pNewPoint);

   HRESULT CheckValid();

   CComPtr<ICoordinateXform2d> m_CoordXform;
   CComPtr<IGeomUtil2d> m_GeomUtil;

   CComPtr<IPoint2dFactory> m_PointFactory;
   CComPtr<IPoint2dCollection> m_Points;
   Float64 m_StartDirection; // angle (rad) measured CCW from due east
   Float64 m_EndDirection;   // angle (rad) measured CCW from due east
   Float64 m_RotationAngle;  // rotation angle between the global coordinate system and the spline coordinate system

   bool m_bUpdateSpline;
};

class CSplineSegment
{
public:
   CSplineSegment();
   void Init(Float64 A, Float64 B, Float64 C, Float64 D);
   Float64 Length() const;
   Float64 Length(Float64 dx) const;
   Float64 Evaluate(Float64 x) const;
   Float64 Slope(Float64 x) const;
   void GetPoint(Float64 distance,Float64* pX,Float64* pY) const;
   Float64 Bearing(Float64 distance) const;
   Float64 Normal(Float64 distance) const;
   void Intersect(ILine2d* line,IGeomUtil2d* pGU,IPoint2d** p1,IPoint2d** p2,IPoint2d** p3) const;

   CComPtr<IPoint2d> pntA; // point at start of segment
   CComPtr<IPoint2d> pntB; // point at end of segment

private:
   // f(x)  =  A + Bx +  Cx^2 +  Dx^3
   // f'(x) =      B  + 2Cx   + 3Dx^2
   Float64 A, B, C, D;
   
   mutable bool m_bComputeLength;
   mutable Float64 m_Length;
};

class CSplineSegmentLengthFunction : public mathFunction2d
{
public:
   CSplineSegmentLengthFunction(const CSplineSegment& splineSegment);
   Float64 Evaluate(Float64 x) const;

private:
   const CSplineSegment& m_SplineSegment;
};

class CSplineSegmentPointFunction : public mathFunction2d
{
public:
   CSplineSegmentPointFunction(Float64 distance,Float64 x0,const CSplineSegment& splineSegment);
   Float64 Evaluate(Float64 x) const;

private:
   Float64 m_Distance; // distance along segment where solution is sought
   Float64 m_X0; // x0
   const CSplineSegment& m_SplineSegment;
};


class CSplineSegmentProjectPointFunction : public mathFunction2d
{
public:
   CSplineSegmentProjectPointFunction(const CSplineSegment& splineSegment,IPoint2d* tp,IGeomUtil2d* gu);
   Float64 Evaluate(Float64 x) const;

private:
   const CSplineSegment& m_SplineSegment;
   CComPtr<IGeomUtil2d> m_GeomUtil;
   CComPtr<IPoint2d> m_TargetPoint;
   CComPtr<IVector2d> m_Vector;
   CComPtr<ILine2d> m_Line;
   CComPtr<IPoint2d> m_Point;
};


#endif //__CUBICSPLINE_H_
