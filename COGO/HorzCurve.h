///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 2001  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// HorzCurve.h : Declaration of the CHorzCurve

#ifndef __HORZCURVE_H_
#define __HORZCURVE_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"

#include <MathEx.h>
#include <Math\Math.h>

class CEntrySpiralFunction;
class CExitSpiralFunction;

/////////////////////////////////////////////////////////////////////////////
// CHorzCurve
class ATL_NO_VTABLE CHorzCurve : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CHorzCurve,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CHorzCurve, &CLSID_HorzCurve>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CHorzCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CHorzCurve>,
   public CProxyDHorzCurveEvents< CHorzCurve >,
   public IPoint2dEvents,
   public IHorzCurve,
   public IStructuredStorage2,
   public IPersistImpl<CHorzCurve>
{
public:
	CHorzCurve()
	{
      m_Ls1 = 0;
      m_Ls2 = 0;
      m_Radius = 1000;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_HORZCURVE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHorzCurve)
	COM_INTERFACE_ENTRY(IHorzCurve)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CHorzCurve)
CONNECTION_POINT_ENTRY(IID_IHorzCurveEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IHorzCurve
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(Clone)(/*[out,retval]*/ IHorzCurve* *clone);
	STDMETHOD(get_PointFactory)(/*[out,retval]*/ IPoint2dFactory* *factory);
	STDMETHOD(putref_PointFactory)(/*[in]*/ IPoint2dFactory *factory);
	STDMETHOD(Intersect)(/*[in]*/ILine2d* line,/*[in]*/VARIANT_BOOL bProjectBack,/*[in]*/VARIANT_BOOL bProjectAhead,/*[out]*/ IPoint2d** p1,/*[out]*/ IPoint2d** p2);
   STDMETHOD(DistanceFromStart)(/*[in]*/ IPoint2d* point,/*[out,retval]*/ Float64* dist);
	STDMETHOD(ProjectPoint)(/*[in]*/ IPoint2d* point,/*[out,retval]*/ IPoint2d* *pNewPoint);
	STDMETHOD(PointOnCurve)(/*[in]*/ Float64 distance,/*[out,retval]*/IPoint2d* *pVal);
	STDMETHOD(Normal)(/*[in]*/ Float64 distance,/*[out,retval]*/IDirection* *pVal);
	STDMETHOD(Bearing)(/*[in]*/ Float64 distance,/*[out,retval]*/IDirection* *pVal);
   STDMETHOD(get_DegreeCurvature)(/*[in]*/ Float64 D,/*[in]*/ DegreeCurvatureType dcMethod,/*[out,retval]*/ IAngle** pDC);
	STDMETHOD(get_TotalLength)(/*[out,retval]*/ Float64* pVal);
	STDMETHOD(get_CurveLength)(/*[out,retval]*/ Float64* pVal);
   STDMETHOD(get_Direction)(/*[out,retval]*/ CurveDirectionType* dir);
	STDMETHOD(get_DF)(/*[in]*/SpiralType spType,/*[out,retval]*/ IAngle** pDF);
	STDMETHOD(get_DH)(/*[in]*/SpiralType spType,/*[out,retval]*/ IAngle** pDH);
   STDMETHOD(get_SpiralChord)(/*[in]*/SpiralType spType,/*[out,retval]*/ Float64* cs);
   STDMETHOD(get_CCC)(/*[out, retval]*/ IPoint2d* *pVal);
   STDMETHOD(get_PCI)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_CurveBkTangentBrg)(/*[out,retval]*/IDirection* *brg);
	STDMETHOD(get_CurveFwdTangentBrg)(/*[out,retval]*/IDirection* *brg);
	STDMETHOD(get_SPI)(/*[in]*/SpiralType spType,/*[out,retval]*/IPoint2d** pSPI);
	STDMETHOD(get_CC)(/*[out, retval]*/ IPoint2d* *pVal);
   STDMETHOD(get_LongTangent)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* u);
	STDMETHOD(get_ShortTangent)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* v);
   STDMETHOD(get_DE)(/*[in]*/SpiralType spType,/*[out,retval]*/IAngle* *pDE);
	STDMETHOD(get_External)(/*[out,retval]*/Float64* external);
   STDMETHOD(get_MidOrdinate)(/*[out,retval]*/Float64* mo);
	STDMETHOD(get_Tangent)(/*[out,retval]*/Float64* tangent);
   STDMETHOD(get_CircularCurveAngle)(/*[out,retval]*/ IAngle* *pVal);
	STDMETHOD(get_Chord)(/*[out,retval]*/Float64* chord);
   STDMETHOD(get_SC)(/*[out, retval]*/ IPoint2d* *pVal);
   STDMETHOD(get_CS)(/*[out, retval]*/ IPoint2d* *pVal);
   STDMETHOD(get_TS)(/*[out, retval]*/ IPoint2d* *pVal);
   STDMETHOD(get_ST)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(get_BkTangentLength)(/*[out,retval]*/Float64* t);
	STDMETHOD(get_FwdTangentLength)(/*[out,retval]*/Float64* t);
   STDMETHOD(get_CurveAngle)(/*[out,retval]*/ IAngle* *pVal);
	STDMETHOD(get_BkTangentBrg)(/*[out, retval]*/ IDirection* *pVal);
	STDMETHOD(get_FwdTangentBrg)(/*[out, retval]*/ IDirection* *pVal);
	STDMETHOD(get_Q)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* q);
   STDMETHOD(get_T)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* t);
	STDMETHOD(get_X)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* x);
	STDMETHOD(get_Y)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* y);
	STDMETHOD(get_SpiralAngle)(/*[in]*/ SpiralType spType,/*[out, retval]*/ IAngle* *pVal);
   STDMETHOD(get_SpiralLength)(/*[in]*/ SpiralType spType,/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_SpiralLength)(/*[in]*/ SpiralType spType,/*[in]*/ Float64 newVal);
	STDMETHOD(get_Radius)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Radius)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_PFT)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(putref_PFT)(/*[in]*/ IPoint2d* newVal);
	STDMETHOD(get_PI)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(putref_PI)(/*[in]*/ IPoint2d* newVal);
	STDMETHOD(get_PBT)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(putref_PBT)(/*[in]*/ IPoint2d* newVal);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// IPointEvents
public:
	STDMETHOD(OnPointChanged)(IPoint2d* point);

private:
   CComPtr<IPoint2d> m_PBT, m_PI, m_PFT;
   DWORD m_dwPBT, m_dwPI, m_dwPFT;

   Float64 m_Radius;
   Float64 m_Ls1, m_Ls2;

   CComPtr<IGeomUtil2d> m_GeomUtil;
   CComPtr<IPoint2dFactory> m_PointFactory;

   void Advise(IPoint2d* pnt,DWORD* pdwCookie);
   void Unadvise(IPoint2d* pnt,DWORD* pdwCookie);

   Float64 SpiralX(Float64 ls,Float64 angle);
   Float64 SpiralY(Float64 ls,Float64 angle);
   void PointOnEntrySpiral(Float64 x,Float64 y,IPoint2d** pVal);
   void PointOnExitSpiral(Float64 x,Float64 y,IPoint2d** pVal);
   void PointOnEntrySpiral(Float64 distFromTS,IPoint2d** pVal);
   void PointOnExitSpiral(Float64 distFromST,IPoint2d** pVal);
   void ProjectPointOnEntrySpiral(IPoint2d* point,Float64* pDistFromStart,IPoint2d** newPoint);
   void ProjectPointOnExitSpiral(IPoint2d* point,Float64* pDistFromStart,IPoint2d** newPoint);
	void ProjectPoint(IPoint2d* point,Float64* pDistFromStart, IPoint2d* *pNewPoint);

   // creates line objects for the curve tangents
   void GetBkTangentLine(ILine2d** line);
   void GetFwdTangentLine(ILine2d** line);

   // returns true if line is parallel to tangent and there is no possiblity of an intersection
   bool LineParallelToTangent(ILine2d* pTangentLine,ILine2d* pLine,IPoint2d* pTangentPoint);
   void GetCurveCenterNormalIntersectPoints(IPoint2d** pPOBT,IPoint2d** pPOFT);

   bool IsPointOnCurve(IPoint2d* pPoint);
   bool IsPointOnLine(ILine2d* pLine,IPoint2d* pPoint);
   bool TestIntersection(ILine2d* pLine,IPoint2d* pPoint);

   friend CEntrySpiralFunction;
   friend CExitSpiralFunction;


};


class CEntrySpiralFunction : public mathFunction2d
{
public:
   CEntrySpiralFunction(CHorzCurve* hc,IPoint2d* tp,IGeomUtil2d* gu) :
      m_pCurve(hc), m_TargetPoint(tp), m_GeomUtil(gu)
   {
      m_Vector.CoCreateInstance(CLSID_Vector2d);
      m_Line.CoCreateInstance(CLSID_Line2d);
   }

   Float64 Evaluate(Float64 x) const
   {
      CComPtr<IPoint2d> pnt;
      m_pCurve->PointOnEntrySpiral(x,&pnt);

      CComPtr<IDirection> dir;
      m_pCurve->Normal(x,&dir);
      Float64 angle;
      dir->get_Value(&angle);

      m_Vector->put_Direction(angle);
  
      m_Line->SetExplicit(pnt,m_Vector);

      Float64 dist;
      m_GeomUtil->ShortestDistanceToPoint(m_Line,m_TargetPoint,&dist);
      return dist;
   }

private:
   CHorzCurve* m_pCurve;
   CComPtr<IGeomUtil2d> m_GeomUtil;
   CComPtr<IPoint2d> m_TargetPoint;
   CComPtr<IVector2d> m_Vector;
   CComPtr<ILine2d> m_Line;
};


class CExitSpiralFunction : public mathFunction2d
{
public:
   CExitSpiralFunction(CHorzCurve* hc,IPoint2d* tp,IGeomUtil2d* gu) :
      m_pCurve(hc), m_TargetPoint(tp), m_GeomUtil(gu)
   {
      m_Vector.CoCreateInstance(CLSID_Vector2d);
      m_Line.CoCreateInstance(CLSID_Line2d);
   }

   Float64 Evaluate(Float64 x) const
   {
      CComPtr<IPoint2d> pnt;
      m_pCurve->PointOnExitSpiral(x,&pnt);

      Float64 Lt; // total length
      m_pCurve->get_TotalLength(&Lt);
      CComPtr<IDirection> dir;
      m_pCurve->Normal(Lt - x,&dir);
      Float64 angle;
      dir->get_Value(&angle);

      m_Vector->put_Direction(angle);
  
      m_Line->SetExplicit(pnt,m_Vector);

      Float64 dist;
      m_GeomUtil->ShortestDistanceToPoint(m_Line,m_TargetPoint,&dist);
      return dist;
   }

private:
   CHorzCurve* m_pCurve;
   CComPtr<IGeomUtil2d> m_GeomUtil;
   CComPtr<IPoint2d> m_TargetPoint;
   CComPtr<IVector2d> m_Vector;
   CComPtr<ILine2d> m_Line;
};

class CLineIntersectFunction : public mathFunction2d
{
public:
   CLineIntersectFunction(CHorzCurve* hc,ILine2d* line,IGeomUtil2d* util) :
      m_pCurve(hc), m_Line(line), m_GeomUtil(util)
      {
      }

      Float64 Evaluate(Float64 distFromStartOfCurve) const
      {
         // output is distance between line and the point located at
         // distFromStartOfCurve

         CComPtr<IPoint2d> point_on_curve;
         m_pCurve->PointOnCurve(distFromStartOfCurve,&point_on_curve);

         Float64 dist;
         m_GeomUtil->ShortestDistanceToPoint(m_Line,point_on_curve,&dist);

         return dist;
      }

private:
   CHorzCurve* m_pCurve;
   CComPtr<ILine2d> m_Line;
   CComPtr<IGeomUtil2d> m_GeomUtil;
};

class CParallelLineFunction : public mathFunction2d
{
public:
   CParallelLineFunction(CHorzCurve* hc,ILine2d* line,IGeomUtil2d* util) :
      m_pCurve(hc), m_Line(line), m_GeomUtil(util)
      {
         CComPtr<IPoint2d> p;
         CComPtr<IVector2d> v;
         m_Line->GetExplicit(&p,&v);

         v->get_Direction(&m_Angle);
      }

      Float64 Evaluate(Float64 distFromStartOfCurve) const
      {
         // trying to find location on curve where line and angle are parallel
         CComPtr<IDirection> dir;
         m_pCurve->Bearing(distFromStartOfCurve,&dir);

         Float64 angle;
         dir->get_Value(&angle);

         return m_Angle - angle;
      }

private:
   CHorzCurve* m_pCurve;
   Float64 m_Angle;
   CComPtr<ILine2d> m_Line;
   CComPtr<IGeomUtil2d> m_GeomUtil;
};

#endif //__HORZCURVE_H_
