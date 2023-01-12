///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
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

// MomentCapacitySolution.cpp : Implementation of CMomentCapacitySolution
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "MomentCapacitySolution.h"
#include <WBFLGeometry.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMomentCapacitySolution
HRESULT CMomentCapacitySolution::FinalConstruct()
{
   m_StrainPlane.CoCreateInstance(CLSID_Plane3d);
   m_NeutralAxis.CoCreateInstance(CLSID_Line2d);
   m_cgC.CoCreateInstance(CLSID_Point2d);
   m_cgT.CoCreateInstance(CLSID_Point2d);

   m_Fz = 0;
   m_Mx = 0;
   m_My = 0;
   m_C  = 0;
   m_T  = 0;

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
STDMETHODIMP CMomentCapacitySolution::InitSolution(Float64 fz,Float64 mx,Float64 my,IPlane3d* strainPlane,ILine2d* neutralAxis,IPoint2d* cgC,Float64 C,IPoint2d* cgT,Float64 T,IGeneralSectionSolution* solution)
{
   m_Fz = fz;
   m_Mx = mx;
   m_My = my;

   if ( strainPlane )
      m_StrainPlane = strainPlane;

   if ( neutralAxis )
      m_NeutralAxis = neutralAxis;

   m_C = C;
   m_T = T;

   if ( cgC )
      m_cgC = cgC;

   if ( cgT )
      m_cgT = cgT;

   if ( solution )
      m_Solution = solution;

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

STDMETHODIMP CMomentCapacitySolution::get_StrainPlane(IPlane3d** strainPlane)
{
   CHECK_RETOBJ(strainPlane);
   (*strainPlane) = m_StrainPlane;
   (*strainPlane)->AddRef();
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_NeutralAxis(ILine2d** neutralAxis)
{
   CHECK_RETOBJ(neutralAxis);
   (*neutralAxis) = m_NeutralAxis;
   (*neutralAxis)->AddRef();
   return S_OK;
}

STDMETHODIMP CMomentCapacitySolution::get_NeutralAxisDirection(Float64* angle)
{
   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> d;
   m_NeutralAxis->GetExplicit(&p,&d);
   return d->get_Direction(angle);
}

STDMETHODIMP CMomentCapacitySolution::get_CompressionResultant(Float64* c)
{
   CHECK_RETVAL(c);
   *c = m_C;
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

STDMETHODIMP CMomentCapacitySolution::get_GeneralSectionSolution(IGeneralSectionSolution** solution)
{
   CHECK_RETOBJ(solution);
   (*solution) = m_Solution;
   if (*solution)
   {
      (*solution)->AddRef();
   }
   return S_OK;
}
