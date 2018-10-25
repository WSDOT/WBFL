///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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

// MomentCurvatureSolution.cpp : Implementation of CMomentCurvatureSolution
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "MomentCurvatureSolution.h"
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMomentCurvatureSolution
HRESULT CMomentCurvatureSolution::FinalConstruct()
{
   return S_OK;
}

void CMomentCurvatureSolution::FinalRelease()
{
}

void CMomentCurvatureSolution::AddCurvaturePoint(Float64 M,Float64 k,IPlane3d* strainPlane)
{
   CurvaturePoint cp;
   cp.M = M;
   cp.k = k;
   cp.StrainPlane = strainPlane;

   m_CurvaturePoints.push_back(cp);
   std::sort(m_CurvaturePoints.begin(),m_CurvaturePoints.end());
}

STDMETHODIMP CMomentCurvatureSolution::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMomentCurvatureSolution,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IMomentCurvatureSolution
STDMETHODIMP CMomentCurvatureSolution::get_MaxMoment(Float64* Mmax)
{
   CHECK_RETVAL(Mmax);

   std::vector<CurvaturePoint>::iterator iter;
   iter = std::max_element(m_CurvaturePoints.begin(),m_CurvaturePoints.end());
   *Mmax = (*iter).M;

   return S_OK;
}

STDMETHODIMP CMomentCurvatureSolution::get_MaxMomentCurvature(Float64* k)
{
   CHECK_RETVAL(k);
   std::vector<CurvaturePoint>::iterator iter;
   iter = std::max_element(m_CurvaturePoints.begin(),m_CurvaturePoints.end());
   *k = (*iter).k;
   return S_OK;
}

STDMETHODIMP CMomentCurvatureSolution::PeakCapacity(Float64* Mmax,Float64* k)
{
   CHECK_RETVAL(Mmax);
   CHECK_RETVAL(k);
   std::vector<CurvaturePoint>::iterator iter;
   iter = std::max_element(m_CurvaturePoints.begin(),m_CurvaturePoints.end());
   *Mmax = (*iter).M;
   *k = (*iter).k;
   return S_OK;
}

STDMETHODIMP CMomentCurvatureSolution::get_Moment(CollectionIndexType idx,Float64* pM)
{
   CHECK_RETVAL(pM);
   *pM = m_CurvaturePoints[idx].M;

   return S_OK;
}

STDMETHODIMP CMomentCurvatureSolution::get_Curvature(CollectionIndexType idx,Float64* k)
{
   CHECK_RETVAL(k);
   *k = m_CurvaturePoints[idx].k;
   return S_OK;
}

STDMETHODIMP CMomentCurvatureSolution::get_StrainPlane(CollectionIndexType idx,IPlane3d** strainPlane)
{
   CHECK_RETOBJ(strainPlane);
   (*strainPlane) = m_CurvaturePoints[idx].StrainPlane;

   if ( *strainPlane )
      (*strainPlane)->AddRef();

   return S_OK;
}
   
STDMETHODIMP CMomentCurvatureSolution::get_PointCount(CollectionIndexType* nPoints)
{
   CHECK_RETVAL(nPoints);
   *nPoints = m_CurvaturePoints.size();
   return S_OK;
}

