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

// CompoundCurve.h : Declaration of the CCompoundCurve

#ifndef __CompoundCurve_H_
#define __CompoundCurve_H_
#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CCompoundCurve
class ATL_NO_VTABLE CCompoundCurve :
   public CComObjectRootEx<CComSingleThreadModel>,
   //   public CComRefCountTracer<CCompoundCurve,CComObjectRootEx<CComSingleThreadModel> >,
   public CComCoClass<CCompoundCurve, &CLSID_CompoundCurve>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CCompoundCurve, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ICompoundCurve,
   public IPathElement // see note on ICompoundCurve interface definition in IDL file
{
public:
   CCompoundCurve()
   {
   }

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetCurve(std::shared_ptr<WBFL::COGO::CompoundCurve> curve) { m_Curve = curve; }
   std::shared_ptr<WBFL::COGO::CompoundCurve> GetCurve() { return m_Curve; }

   DECLARE_REGISTRY_RESOURCEID(IDR_COMPOUNDCURVE)

   DECLARE_PROTECT_FINAL_CONSTRUCT()

   BEGIN_COM_MAP(CCompoundCurve)
      COM_INTERFACE_ENTRY(ICompoundCurve)
      COM_INTERFACE_ENTRY(IPathElement)
      COM_INTERFACE_ENTRY(ISupportErrorInfo)
      COM_INTERFACE_ENTRY(IObjectSafety)
   END_COM_MAP()

   // ISupportsErrorInfo
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

   // ICompoundCurve
public:
   STDMETHOD(get_DegreeCurvature)(/*[in]*/ Float64 D,/*[in]*/ DegreeCurvatureType dcMethod,/*[out,retval]*/ IAngle** pDC) override;
   STDMETHOD(get_TotalLength)(/*[out,retval]*/ Float64* pVal) override;
   STDMETHOD(get_CurveLength)(/*[out,retval]*/ Float64* pVal) override;
   STDMETHOD(get_Direction)(/*[out,retval]*/ CurveDirectionType* dir) override;
   STDMETHOD(get_DF)(/*[in]*/SpiralType spType,/*[out,retval]*/ IAngle** pDF) override;
   STDMETHOD(get_DH)(/*[in]*/SpiralType spType,/*[out,retval]*/ IAngle** pDH) override;
   STDMETHOD(get_SpiralChord)(/*[in]*/SpiralType spType,/*[out,retval]*/ Float64* cs) override;
   STDMETHOD(get_CCC)(/*[out, retval]*/ IPoint2d** pVal) override;
   STDMETHOD(get_PCI)(/*[out, retval]*/ IPoint2d** pVal) override;
   STDMETHOD(get_CurveBkTangentBrg)(/*[out,retval]*/IDirection** brg) override;
   STDMETHOD(get_CurveFwdTangentBrg)(/*[out,retval]*/IDirection** brg) override;
   STDMETHOD(get_SPI)(/*[in]*/SpiralType spType,/*[out,retval]*/IPoint2d** pSPI) override;
   STDMETHOD(get_CC)(/*[out, retval]*/ IPoint2d** pVal) override;
   STDMETHOD(get_LongTangent)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* u) override;
   STDMETHOD(get_ShortTangent)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* v) override;
   STDMETHOD(get_DE)(/*[in]*/SpiralType spType,/*[out,retval]*/IAngle** pDE) override;
   STDMETHOD(get_External)(/*[out,retval]*/Float64* external) override;
   STDMETHOD(get_MidOrdinate)(/*[out,retval]*/Float64* mo) override;
   STDMETHOD(get_Tangent)(/*[out,retval]*/Float64* tangent) override;
   STDMETHOD(get_CircularCurveAngle)(/*[out,retval]*/ IAngle** pVal) override;
   STDMETHOD(get_Chord)(/*[out,retval]*/Float64* chord) override;
   STDMETHOD(get_SC)(/*[out, retval]*/ IPoint2d** pVal) override;
   STDMETHOD(get_CS)(/*[out, retval]*/ IPoint2d** pVal) override;
   STDMETHOD(get_TS)(/*[out, retval]*/ IPoint2d** pVal) override;
   STDMETHOD(get_ST)(/*[out, retval]*/ IPoint2d** pVal) override;
   STDMETHOD(get_BkTangentLength)(/*[out,retval]*/Float64* t) override;
   STDMETHOD(get_FwdTangentLength)(/*[out,retval]*/Float64* t) override;
   STDMETHOD(get_CurveAngle)(/*[out,retval]*/ IAngle** pVal) override;
   STDMETHOD(get_BkTangentBrg)(/*[out, retval]*/ IDirection** pVal) override;
   STDMETHOD(get_FwdTangentBrg)(/*[out, retval]*/ IDirection** pVal) override;
   STDMETHOD(get_Q)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* q) override;
   STDMETHOD(get_T)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* t) override;
   STDMETHOD(get_X)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* x) override;
   STDMETHOD(get_Y)(/*[in]*/SpiralType spType,/*[out,retval]*/Float64* y) override;
   STDMETHOD(get_SpiralAngle)(/*[in]*/ SpiralType spType,/*[out, retval]*/ IAngle** pVal) override;
   STDMETHOD(get_SpiralLength)(/*[in]*/ SpiralType spType,/*[out, retval]*/ Float64* pVal) override;
   STDMETHOD(put_SpiralLength)(/*[in]*/ SpiralType spType,/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_Radius)(/*[out, retval]*/ Float64* pVal) override;
   STDMETHOD(put_Radius)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_PFT)(/*[out, retval]*/ IPoint2d** pVal) override;
   STDMETHOD(put_PFT)(/*[in]*/ IPoint2d* newVal) override;
   STDMETHOD(get_PI)(/*[out, retval]*/ IPoint2d** pVal) override;
   STDMETHOD(put_PI)(/*[in]*/ IPoint2d* newVal) override;
   STDMETHOD(get_PBT)(/*[out, retval]*/ IPoint2d** pVal) override;
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
   std::shared_ptr<WBFL::COGO::CompoundCurve> m_Curve;
};

#endif //__CompoundCurve_H_
