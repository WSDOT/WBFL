///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include "COGOCP.h"

#include <Math\Math.h>


/////////////////////////////////////////////////////////////////////////////
// CCircularCurve
class ATL_NO_VTABLE CCircularCurve : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CCircularCurve,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CCircularCurve, &CLSID_CircularCurve>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCircularCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CCircularCurve>,
   public CProxyDCircularCurveEvents< CCircularCurve >,
   public IPoint2dEvents,
   public ICircularCurve,
   public IStructuredStorage2,
   public IPersistImpl<CCircularCurve>
{
public:
	CCircularCurve()
	{
      m_Radius = 1000;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   int ProjectionRegion(IPoint2d* pPoint);
   bool IsPointOnCurve(IPoint2d* pPoint);

DECLARE_REGISTRY_RESOURCEID(IDR_CIRCULARCURVE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCircularCurve)
	COM_INTERFACE_ENTRY(ICircularCurve)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCircularCurve)
CONNECTION_POINT_ENTRY(IID_ICircularCurveEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICircularCurve
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/ ICircularCurve* *clone) override;
	STDMETHOD(get_PointFactory)(/*[out,retval]*/ IPoint2dFactory* *factory) override;
	STDMETHOD(putref_PointFactory)(/*[in]*/ IPoint2dFactory *factory) override;
	STDMETHOD(Intersect)(/*[in]*/ILine2d* line,/*[in]*/VARIANT_BOOL bProjectBack,/*[in]*/VARIANT_BOOL bProjectAhead,/*[out]*/ IPoint2d** p1,/*[out]*/ IPoint2d** p2) override;
   STDMETHOD(ProjectPoint)(/*[in]*/ IPoint2d* point, /*[out]*/ IPoint2d* *newPoint, /*[out]*/ Float64* distFromStart, /*[out]*/ VARIANT_BOOL* pvbOnProjection) override;
   STDMETHOD(PointOnCurve)(/*[in]*/ Float64 distance,/*[out,retval]*/IPoint2d* *pVal) override;
	STDMETHOD(Normal)(/*[in]*/ Float64 distance,/*[out,retval]*/IDirection* *pVal) override;
	STDMETHOD(Bearing)(/*[in]*/ Float64 distance,/*[out,retval]*/IDirection* *pVal) override;
   STDMETHOD(get_DegreeCurvature)(/*[in]*/ Float64 D,/*[in]*/ DegreeCurvatureType dcMethod,/*[out,retval]*/ IAngle** pDC) override;
	STDMETHOD(get_Length)(/*[out,retval]*/ Float64* pVal) override;
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
	STDMETHOD(putref_PFT)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_PI)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_PI)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_PBT)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_PBT)(/*[in]*/ IPoint2d* newVal) override;
   STDMETHOD(Offset)(/*[in]*/Float64 dx,/*[in]*/Float64 dy) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

// IPointEvents
public:
	STDMETHOD(OnPointChanged)(IPoint2d* point) override;

private:
   bool m_bHoldEvents;
   bool m_bPendingEvents;

   CComPtr<IPoint2d> m_PBT, m_PI, m_PFT;
   DWORD m_dwPBT, m_dwPI, m_dwPFT;

   CComPtr<IPoint2d> m_PC, m_PT;

   Float64 m_Radius;

   CComPtr<IPoint2dFactory> m_PointFactory;

   void Advise(IPoint2d* pnt,DWORD* pdwCookie);
   void Unadvise(IPoint2d* pnt,DWORD* pdwCookie);

   // creates line objects for the curve tangents
   void GetBkTangentLine(ILine2d** line);
   void GetFwdTangentLine(ILine2d** line);

   // returns true if line is parallel to tangent and there is no possiblity of an intersection
   bool LineParallelToTangent(ILine2d* pTangentLine,ILine2d* pLine,IPoint2d* pTangentPoint);
   //void GetCurveCenterNormalIntersectPoints(IPoint2d** pPOBT,IPoint2d** pPOFT);

   bool IsPointOnLine(ILine2d* pLine,IPoint2d* pPoint);
   bool TestIntersection(ILine2d* pLine,IPoint2d* pPoint);
};

#endif //__CircularCurve_H_
