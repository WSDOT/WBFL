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
#include "COGOCP.h"
#include <Math\Math.h>
#include <WBFLGeometry\GeomHelpers.h>


/////////////////////////////////////////////////////////////////////////////
// CTransitionCurve
class ATL_NO_VTABLE CTransitionCurve : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CTransitionCurve,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CTransitionCurve, &CLSID_TransitionCurve>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CTransitionCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IConnectionPointContainerImpl<CTransitionCurve>,
   public CProxyDTransitionCurveEvents< CTransitionCurve >,
   public ITransitionCurve,
   public IStructuredStorage2,
   public IPersistImpl<CTransitionCurve>
{
public:
	CTransitionCurve()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_TRANSITIONCURVE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTransitionCurve)
   COM_INTERFACE_ENTRY(ITransitionCurve)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTransitionCurve)
   CONNECTION_POINT_ENTRY(IID_ITransitionCurveEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ITransitionCurve
public:
   STDMETHOD(Init)(/*[in]*/IPoint2d* pStart, /*[in]*/IDirection* pStartDirection, /*[in]*/Float64 R1, /*[in]*/Float64 R2, /*[in]*/Float64 L,/*[in]*/TransitionCurveType type) override;
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

   STDMETHOD(get_Start)(/*[out, retval]*/IPoint2d** pStart) override;
   STDMETHOD(get_StartDirection)(/*[out, retval]*/IDirection** pStartDirection) override;
   STDMETHOD(get_Length)(/*[out, retval]*/Float64* pLength) override;
   STDMETHOD(get_End)(/*[out, retval]*/IPoint2d** pEnd) override;
   STDMETHOD(get_EndDirection)(/*[out, retval]*/IDirection** pEndDirection) override;

   STDMETHOD(PointOnCurve)(/*[in]*/Float64 distanceFromStart, /*[out, retval]*/IPoint2d** point) override;
   STDMETHOD(Bearing)(/*[in]*/ Float64 distanceFromStart, /*[out, retval]*/IDirection** pDirection) override;
   STDMETHOD(Normal)(/*[in]*/ Float64 distanceFromStart, /*[out, retval]*/IDirection** pDirection) override;
   STDMETHOD(ProjectPoint)(/*[in]*/ IPoint2d* point, /*[out]*/ IPoint2d** newPoint, /*[out]*/ Float64* distFromStart, /*[out]*/ VARIANT_BOOL* pvbOnProjection) override;
   STDMETHOD(DistanceFromStart)(/*[in]*/ IPoint2d* point, /*[out, retval]*/ Float64* dist);
   STDMETHOD(Intersect)(/*[in]*/ILine2d* line,/*[in]*/VARIANT_BOOL bProjectBack,/*[in]*/VARIANT_BOOL bProjectAhead, /*[out]*/ IPoint2dCollection** points) override;

   STDMETHOD(Move)(/*[in]*/ Float64 dist, /*[in]*/ IDirection* direction) override;
   STDMETHOD(Offset)(/*[in]*/Float64 dx,/*[in]*/Float64 dy) override;

   STDMETHOD(get_PointFactory)(/*[out,retval]*/ IPoint2dFactory* *factory) override;
   STDMETHOD(putref_PointFactory)(/*[in]*/ IPoint2dFactory *factory) override;
   STDMETHOD(Clone)(/*[out, retval]*/ ITransitionCurve* *clone) override;
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pVal) override;


// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

private:
   TransitionCurveType m_Type;
   CComPtr<IPoint2d> m_StartPoint; // point where transition curve beings
   CComPtr<IDirection> m_StartDirection;
   Float64 m_r1; // radius at start of transition curve (use 0.0 for infinite radius) - this is the input value
   Float64 m_r2; // radius at end of transition curve (use 0.0 for infinite radius) - this is the input value
   Float64 m_L; // length of transition curve

   Float64 m_R1; // radius at start - this is the value where 0.0 is converted to Float64_Max for easier computations
   Float64 m_R2; // radius at end - this is the value where 0.0 is converted to Float64_Max for easier computations
   Float64 m_StartDirectionValue; // this is the value in the m_StartDirection object

   CComPtr<IPoint2d> m_EndPoint;
   CComPtr<IDirection> m_EndDirection;
   CComPtr<IPoint2d> m_PI;

   Float64 m_U; // long tangent
   Float64 m_V; // short tangent

   Float64 m_Rs; // radius at start of transition curve nearest (or at) the point of infinite radius (greatest absolute value of R1 and R2)
   Float64 m_Re; // radius at end of transition curve opposite the point of infinite radius (least absolute value of R1 and R2)
   Float64 m_A; // scale factor
   Float64 m_Ls; // length of curve from the point of infinite radius to the end of the transition curve segment
   Float64 m_SpiralAngle; // Total angle of the full spiral (from point of infinite radius to terminus of curve)
   Float64 m_StartDist; // distance from start of full spiral at point of infinite radius to start of actual curve

   Float64 m_Sign; // 1 for CCW, -1 for CW curves
   Float64 m_SignY; // Sign to correct Y values based on direction of local coordinate system

   CComPtr<IPoint2d> m_SpiralOrigin;
   Float64 m_SpiralRotation;

   CComPtr<IPoint2dFactory> m_PointFactory;

   void Advise(IPoint2d* pnt, DWORD* pdwCookie);
   void Unadvise(IPoint2d* pnt, DWORD* pdwCookie);

   Float64 SpiralX(Float64 ls,Float64 angle);
   Float64 SpiralY(Float64 ls,Float64 angle);

   Float64 DistanceFromStartOfSpiral(Float64 distance);

   void ProjectPoint(IPoint2d* point,Float64* pDistFromStart, IPoint2d* *pNewPoint);
   
   // creates line objects for the curve tangents
   void GetBkTangentLine(ILine2d** line);
   void GetFwdTangentLine(ILine2d** line);

   bool IsPointOnCurve(IPoint2d* pPoint);
   bool IsPointOnLine(ILine2d* pLine,IPoint2d* pPoint);
   bool TestIntersection(ILine2d* pLine,IPoint2d* pPoint);

   int ProjectionRegion(IPoint2d* pPoint);

   class CLineIntersectFunction : public mathFunction2d
   {
   public:
      CLineIntersectFunction(CTransitionCurve* tc, ILine2d* line) :
         m_pCurve(tc), m_Line(line)
      {
      }

      Float64 Evaluate(Float64 distFromStartOfCurve) const
      {
         // output is distance between line and the point located at
         // distFromStartOfCurve

         CComPtr<IPoint2d> point_on_curve;
         m_pCurve->PointOnCurve(distFromStartOfCurve, &point_on_curve);

         Float64 dist;
         geomUtil::ShortestDistanceToPoint(m_Line, point_on_curve, &dist);
         return dist;
      }

      virtual mathFunction2d* Clone() const override
      {
         return new CLineIntersectFunction(m_pCurve, m_Line);
      }

   private:
      CTransitionCurve* m_pCurve;
      CComPtr<ILine2d> m_Line;
   };

   class CParallelLineFunction : public mathFunction2d
   {
   public:
      CParallelLineFunction(CTransitionCurve* tc, ILine2d* line) :
         m_pCurve(tc), m_Line(line)
      {
         CComPtr<IPoint2d> p;
         CComPtr<IVector2d> v;
         m_Line->GetExplicit(&p, &v);

         v->get_Direction(&m_Angle);
      }

      Float64 Evaluate(Float64 distFromStartOfCurve) const
      {
         // trying to find location on curve where line and angle are parallel
         CComPtr<IDirection> dir;
         m_pCurve->Bearing(distFromStartOfCurve, &dir);

         Float64 angle;
         dir->get_Value(&angle);

         if (IsZero(angle) && 3 * PI_OVER_2 < m_Angle)
         {
            angle = 2 * M_PI;
         }

         return m_Angle - angle;
      }

      virtual mathFunction2d* Clone() const override
      {
         return new CParallelLineFunction(m_pCurve, m_Line);
      }

   private:
      CTransitionCurve* m_pCurve;
      Float64 m_Angle;
      CComPtr<ILine2d> m_Line;
   };

   class CSpiralFunction : public mathFunction2d
   {
   public:
      CSpiralFunction(CTransitionCurve* tc,IPoint2d* tp) :
         m_pCurve(tc), m_TargetPoint(tp)
      {
         m_Vector.CoCreateInstance(CLSID_Vector2d);
         m_Line.CoCreateInstance(CLSID_Line2d);
      }
   
      Float64 Evaluate(Float64 x) const
      {
         CComPtr<IPoint2d> pnt;
         m_pCurve->PointOnCurve(x,&pnt);
   
         CComPtr<IDirection> dir;
         m_pCurve->Normal(x,&dir);
         Float64 angle;
         dir->get_Value(&angle);
   
         m_Vector->put_Direction(angle);
     
         m_Line->SetExplicit(pnt,m_Vector);
   
         Float64 dist;
         geomUtil::ShortestDistanceToPoint(m_Line,m_TargetPoint,&dist);
         return dist;
      }
   
      virtual mathFunction2d* Clone() const override
      {
         return new CSpiralFunction(m_pCurve,m_TargetPoint);
      }
   
   private:
      CTransitionCurve* m_pCurve;
      CComPtr<IPoint2d> m_TargetPoint;
      CComPtr<IVector2d> m_Vector;
      CComPtr<ILine2d> m_Line;
   };
};
