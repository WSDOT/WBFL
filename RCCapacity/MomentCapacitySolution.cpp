///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
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

// MomentCapacitySolution.cpp : Implementation of CMomentCapacitySolution
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "MomentCapacitySolution.h"
#include <WBFLGeometry.h>
#include <MathEx.h>


/////////////////////////////////////////////////////////////////////////////
// CMomentCapacitySolution
HRESULT CMomentCapacitySolution::FinalConstruct()
{
   m_IncrementalStrainPlane.CoCreateInstance(CLSID_Plane3d);
   m_cgC.CoCreateInstance(CLSID_Point2d);
   m_cgT.CoCreateInstance(CLSID_Point2d);
   m_ExtremeCompressionPoint.CoCreateInstance(CLSID_Point2d);
   m_ExtremeTensionPoint.CoCreateInstance(CLSID_Point2d);

   m_Fz = 0;
   m_Mx = 0;
   m_My = 0;
   m_C  = 0;
   m_T  = 0;
   m_Curvature = 0;

   return S_OK;
}

void CMomentCapacitySolution::FinalRelease()
{
}


STDMETHODIMP CMomentCapacitySolution::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMomentCapacitySolution,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IMomentCapacitySolution
STDMETHODIMP CMomentCapacitySolution::InitSolution(Float64 fz,Float64 mx,Float64 my,IPlane3d* incrementalStrainPlane, IPoint2d* pntC,IPoint2d* cgC,Float64 C, IPoint2d* pntT, IPoint2d* cgT,Float64 T,Float64 k,IGeneralSectionSolution* solution)
{
   m_Fz = fz;
   m_Mx = mx;
   m_My = my;

   if (incrementalStrainPlane)
   {
      m_IncrementalStrainPlane.Release();
      incrementalStrainPlane->Clone(&m_IncrementalStrainPlane);
   }

   m_C = C;
   m_T = T;

   if (pntC)
      m_ExtremeCompressionPoint->MoveEx(pntC);

   if ( cgC )
      m_cgC->MoveEx(cgC);

   if (pntT)
      m_ExtremeTensionPoint->MoveEx(pntT);

   if ( cgT )
      m_cgT->MoveEx(cgT);

   m_Curvature = k;

   if ( solution )
      m_GeneralSolution = solution;

   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_Fz(Float64* fz)
{
   CHECK_RETVAL(fz);
   *fz = m_Fz;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_Mx(Float64* mx)
{
   CHECK_RETVAL(mx);
   *mx = m_Mx;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_My(Float64* my)
{
   CHECK_RETVAL(my);
   *my = m_My;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_IncrementalStrainPlane(IPlane3d** strainPlane)
{
   CHECK_RETOBJ(strainPlane);
   (*strainPlane) = m_IncrementalStrainPlane;
   (*strainPlane)->AddRef();
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_NeutralAxis(ILine2d** neutralAxis)
{
   return m_GeneralSolution->get_NeutralAxis(neutralAxis);
}

STDMETHODIMP CMomentCapacitySolution::get_NeutralAxisDirection(Float64* angle)
{
   return m_GeneralSolution->get_NeutralAxisDirection(angle);
}

STDMETHODIMP CMomentCapacitySolution::get_DepthToNeutralAxis(Float64* pc)
{
   CHECK_RETVAL(pc);

   // Compute depth to neutral axis, c
   CComPtr<IGeomUtil2d> geomUtil;
   geomUtil.CoCreateInstance(CLSID_GeomUtil);
   CComPtr<ILine2d> na;
   m_GeneralSolution->get_NeutralAxis(&na);
   CComPtr<IPoint2d> point_on_na;
   geomUtil->PointOnLineNearest(na, m_ExtremeCompressionPoint, &point_on_na);
   Float64 c;
   point_on_na->DistanceEx(m_ExtremeCompressionPoint, &c);

   *pc = c;

   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_CompressionResultant(Float64* pC)
{
   CHECK_RETVAL(pC);
   *pC = m_C;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_TensionResultant(Float64* t)
{
   CHECK_RETVAL(t);
   *t = m_T;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_CompressionResultantLocation(IPoint2d** cgC)
{
   CHECK_RETOBJ(cgC);
   (*cgC) = m_cgC;
   (*cgC)->AddRef();
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_TensionResultantLocation(IPoint2d** cgT)
{
   CHECK_RETOBJ(cgT);
   (*cgT) = m_cgT;
   (*cgT)->AddRef();
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_ExtremeCompressionPoint(IPoint2d** pntC)
{
   CHECK_RETOBJ(pntC);
   (*pntC) = m_ExtremeCompressionPoint;
   (*pntC)->AddRef();
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_ExtremeTensionPoint(IPoint2d** pntT)
{
   CHECK_RETOBJ(pntT);
   (*pntT) = m_ExtremeTensionPoint;
   (*pntT)->AddRef();
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_DepthToCompressionResultant(Float64* pdc)
{
   CHECK_RETVAL(pdc);

   CComPtr<IGeomUtil2d> geom_util;
   geom_util.CoCreateInstance(CLSID_GeomUtil);

   CComPtr<ILine2d> na;
   get_NeutralAxis(&na);

   Float64 d1, d2;
   geom_util->ShortestOffsetToPoint(na, m_ExtremeCompressionPoint, &d1);
   geom_util->ShortestOffsetToPoint(na, m_cgC, &d2);
   
   *pdc = fabs(d1) - fabs(d2);
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_DepthToTensionResultant(Float64* pde)
{
   CHECK_RETVAL(pde);

   CComPtr<IGeomUtil2d> geom_util;
   geom_util.CoCreateInstance(CLSID_GeomUtil);

   CComPtr<ILine2d> na;
   get_NeutralAxis(&na);

   Float64 d1, d2;
   geom_util->ShortestOffsetToPoint(na, m_ExtremeCompressionPoint, &d1);
   geom_util->ShortestOffsetToPoint(na, m_cgT, &d2);

   *pde = fabs(d1) + fabs(d2);
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_MomentArm(Float64* pMA)
{
   return m_cgT->DistanceEx(m_cgC, pMA);
}

STDMETHODIMP CMomentCapacitySolution::get_Curvature(Float64* pK)
{
   CHECK_RETVAL(pK);
   *pK = m_Curvature;
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_GeneralSectionSolution(IGeneralSectionSolution** solution)
{
   CHECK_RETOBJ(solution);
   (*solution) = m_GeneralSolution;
   if (*solution)
   {
      (*solution)->AddRef();
   }
   return S_OK;
}
