///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2021  Washington State Department of Transportation
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

// HorzCurve.h : Declaration of the CHorzCurve

#ifndef __HORZCURVE_H_
#define __HORZCURVE_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"

#include <Math\Math.h>

class CEntrySpiralFunction;
class CExitSpiralFunction;

#define BACK_TANGENT    0x0001
#define ENTRY_SPIRAL    0x0002
#define CIRCULAR_CURVE  0x0004
#define EXIT_SPIRAL     0x0008
#define FORWARD_TANGENT 0x0010


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

   int ProjectionRegion(IPoint2d* pPoint);
   bool IsPointOnCurve(IPoint2d* pPoint);

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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IHorzCurve
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IHorzCurve* *clone) override;
	STDMETHOD(get_PointFactory)(/*[out,retval]*/ IPoint2dFactory* *factory) override;
	STDMETHOD(putref_PointFactory)(/*[in]*/ IPoint2dFactory *factory) override;
	STDMETHOD(Intersect)(/*[in]*/ILine2d* line,/*[in]*/VARIANT_BOOL bProjectBack,/*[in]*/VARIANT_BOOL bProjectAhead,/*[out]*/ IPoint2d** p1,/*[out]*/ IPoint2d** p2) override;
   STDMETHOD(ProjectPoint)(/*[in]*/ IPoint2d* point, /*[out]*/ IPoint2d* *newPoint, /*[out]*/ Float64* distFromStart, /*[out]*/ VARIANT_BOOL* pvbOnProjection) override;
   STDMETHOD(PointOnCurve)(/*[in]*/ Float64 distance,/*[out,retval]*/IPoint2d* *pVal) override;
	STDMETHOD(Normal)(/*[in]*/ Float64 distance,/*[out,retval]*/IDirection* *pVal) override;
	STDMETHOD(Bearing)(/*[in]*/ Float64 distance,/*[out,retval]*/IDirection* *pVal) override;
   STDMETHOD(get_DegreeCurvature)(/*[in]*/ Float64 D,/*[in]*/ DegreeCurvatureType dcMethod,/*[out,retval]*/ IAngle** pDC) override;
	STDMETHOD(get_TotalLength)(/*[out,retval]*/ Float64* pVal) override;
	STDMETHOD(get_CurveLength)(/*[out,retval]*/ Float64* pVal) override;
   STDMETHOD(get_Direction)(/*[out,retval]*/ CurveDirectionType* dir) override;
	STDMETHOD(get_DF)(/*[in]*/SpiralType spType,/*[out,retval]*/ IAngle** pDF) override;
	STDMETHOD(get_DH)(/*[in]*/SpiralType spType,/*[out,retval]*/ IAngle** pDH) override;
   STDMETHOD(get_SpiralChord)(/*[in]*/SpiralType spType,/*[out,retval]*/ Float64* cs) override;
   STDMETHOD(get_CCC)(/*[out, retval]*/ IPoint2d* *pVal) override;
   STDMETHOD(get_PCI)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_CurveBkTangentBrg)(/*[out,retval]*/IDirection* *brg) override;
	STDMETHOD(get_CurveFwdTangentBrg)(/*[out,retval]*/IDirection* *brg) override;
	STDMETHOD(get_SPI)(/*[in]*/SpiralType spType,/*[out,retval]*/IPoint2d** pSPI) override;
	STDMETHOD(get_CC)(/*[out, retval]*/ IPoint2d* *pVal) override;
   STDMETHOD(get_LongTangent)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* u) override;
	STDMETHOD(get_ShortTangent)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* v) override;
   STDMETHOD(get_DE)(/*[in]*/SpiralType spType,/*[out,retval]*/IAngle* *pDE) override;
	STDMETHOD(get_External)(/*[out,retval]*/Float64* external) override;
   STDMETHOD(get_MidOrdinate)(/*[out,retval]*/Float64* mo) override;
	STDMETHOD(get_Tangent)(/*[out,retval]*/Float64* tangent) override;
   STDMETHOD(get_CircularCurveAngle)(/*[out,retval]*/ IAngle* *pVal) override;
	STDMETHOD(get_Chord)(/*[out,retval]*/Float64* chord) override;
   STDMETHOD(get_SC)(/*[out, retval]*/ IPoint2d* *pVal) override;
   STDMETHOD(get_CS)(/*[out, retval]*/ IPoint2d* *pVal) override;
   STDMETHOD(get_TS)(/*[out, retval]*/ IPoint2d* *pVal) override;
   STDMETHOD(get_ST)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(get_BkTangentLength)(/*[out,retval]*/Float64* t) override;
	STDMETHOD(get_FwdTangentLength)(/*[out,retval]*/Float64* t) override;
   STDMETHOD(get_CurveAngle)(/*[out,retval]*/ IAngle* *pVal) override;
	STDMETHOD(get_BkTangentBrg)(/*[out, retval]*/ IDirection* *pVal) override;
	STDMETHOD(get_FwdTangentBrg)(/*[out, retval]*/ IDirection* *pVal) override;
	STDMETHOD(get_Q)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* q) override;
   STDMETHOD(get_T)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* t) override;
	STDMETHOD(get_X)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* x) override;
	STDMETHOD(get_Y)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* y) override;
	STDMETHOD(get_SpiralAngle)(/*[in]*/ SpiralType spType,/*[out, retval]*/ IAngle* *pVal) override;
   STDMETHOD(get_SpiralLength)(/*[in]*/ SpiralType spType,/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_SpiralLength)(/*[in]*/ SpiralType spType,/*[in]*/ Float64 newVal) override;
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

   CComPtr<IPoint2d> m_TS, m_ST;

   Float64 m_Radius;
   Float64 m_Ls1, m_Ls2;

   CComPtr<IGeomUtil2d> m_GeomUtil;
   CComPtr<IPoint2dFactory> m_PointFactory;
   CComPtr<ICoordinateXform2d> m_Xform;

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

   // creates line objects for the curve tangents
   void GetBkTangentLine(ILine2d** line);
   void GetFwdTangentLine(ILine2d** line);

   // returns true if line is parallel to tangent and there is no possiblity of an intersection
   bool LineParallelToTangent(ILine2d* pTangentLine,ILine2d* pLine,IPoint2d* pTangentPoint);
   void GetCurveCenterNormalIntersectPoints(IPoint2d** pPOBT,IPoint2d** pPOFT);

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

      Float64 offset;
      m_GeomUtil->ShortestOffsetToPoint(m_Line,m_TargetPoint,&offset);
      return offset;
   }

   virtual mathFunction2d* Clone() const override
   {
      return new CEntrySpiralFunction(m_pCurve,m_TargetPoint,m_GeomUtil);
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

      Float64 offset;
      m_GeomUtil->ShortestOffsetToPoint(m_Line,m_TargetPoint,&offset);
      return offset;
   }

   virtual mathFunction2d* Clone() const override
   {
      return new CExitSpiralFunction(m_pCurve,m_TargetPoint,m_GeomUtil);
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

         Float64 offset;
         m_GeomUtil->ShortestOffsetToPoint(m_Line,point_on_curve,&offset);

         return offset;
      }

      virtual mathFunction2d* Clone() const override
      {
         return new CLineIntersectFunction(m_pCurve,m_Line,m_GeomUtil);
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
         m_Line->GetExplicit(&p,&m_Nline);

         m_N.CoCreateInstance(CLSID_Vector2d);
      }

      Float64 Evaluate(Float64 distFromStartOfCurve) const
      {
         // trying to find location on curve where line and angle are parallel
         CComPtr<IDirection> normal;
         m_pCurve->Normal(distFromStartOfCurve,&normal);

         Float64 dir;
         normal->get_Value(&dir);
         m_N->put_Direction(dir);

         Float64 dot;
         m_Nline->Dot(m_N, &dot);

         return dot;
      }

      virtual mathFunction2d* Clone() const override
      {
         return new CParallelLineFunction(m_pCurve,m_Line,m_GeomUtil);
      }

private:
   CHorzCurve* m_pCurve;
   CComPtr<IVector2d> m_Nline, m_N;
   Float64 m_Angle;
   Float64 m_ReverseAngle;
   CComPtr<ILine2d> m_Line;
   CComPtr<IGeomUtil2d> m_GeomUtil;
};

#endif //__HORZCURVE_H_
