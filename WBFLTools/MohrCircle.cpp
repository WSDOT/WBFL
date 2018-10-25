///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2011  Washington State Department of Transportation
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

// MohrCircle.cpp : Implementation of CMohrCircle
#include "stdafx.h"
#include "WBFLTools.h"
#include <MathEx.h>
#include "MohrCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMohrCircle

STDMETHODIMP CMohrCircle::get_Sii(Float64 *sii)
{
   CHECK_RETVAL(sii);
   *sii = m_Sii;
	return S_OK;
}

STDMETHODIMP CMohrCircle::put_Sii(Float64 sii)
{
   m_Sii = sii;
	return S_OK;
}

STDMETHODIMP CMohrCircle::get_Sjj(Float64 *sjj)
{
   CHECK_RETVAL(sjj);
   *sjj = m_Sjj;
	return S_OK;
}

STDMETHODIMP CMohrCircle::put_Sjj(Float64 sjj)
{
   m_Sjj = sjj;
	return S_OK;
}

STDMETHODIMP CMohrCircle::get_Sij(Float64 *sij)
{
   CHECK_RETVAL(sij);
   *sij = m_Sij;
	return S_OK;
}

STDMETHODIMP CMohrCircle::put_Sij(Float64 sij)
{
   m_Sij = sij;
	return S_OK;
}

STDMETHODIMP CMohrCircle::get_Center(Float64 *center)
{
   CHECK_RETVAL(center);

   *center = (m_Sii + m_Sjj)/2.0;

   return S_OK;
}

STDMETHODIMP CMohrCircle::get_Radius(Float64 *radius)
{
   CHECK_RETVAL(radius);

   Float64 temp;
   temp = (m_Sii - m_Sjj)/2.0;

   *radius = sqrt(temp*temp + m_Sij*m_Sij);

   return S_OK;
}

STDMETHODIMP CMohrCircle::get_PrincipleDirection(Float64 *dir)
{
   CHECK_RETVAL(dir);

   // Special case.
   Float64 radius;
   get_Radius(&radius);
   if ( IsZero(radius) )
   {
      *dir = 0.0;
      return S_OK;
   }

   Float64 angle; // This is 2*ThetaP

   angle = atan2( 2*m_Sij, (m_Sii - m_Sjj) ); // atan2 returns a value between -M_PI and M_PI

   // direction is always positive and is measured from the 
   // Counter-clockwise from the positive X axis
   if ( angle < 0 )
      angle += TWO_PI;

   *dir = angle/2.0;

	return S_OK;
}

STDMETHODIMP CMohrCircle::get_Smax(Float64 *Smax)
{
   CHECK_RETVAL(Smax);

   Float64 center;
   Float64 radius;

   get_Center(&center);
   get_Radius(&radius);

   *Smax = center + radius;
	return S_OK;
}

STDMETHODIMP CMohrCircle::get_Smin(Float64 *Smin)
{
   CHECK_RETVAL(Smin);

   Float64 center, radius;
   get_Center(&center);
   get_Radius(&radius);

   *Smin = center - radius;
	return S_OK;
}

STDMETHODIMP CMohrCircle::get_Tmax(Float64 *Tmax)
{
   CHECK_RETVAL(Tmax);
   get_Radius(Tmax);
	return S_OK;
}

STDMETHODIMP CMohrCircle::ComputeState(Float64 angle, Float64 *S11, Float64 *S22, Float64 *S12)
{
   CHECK_RETVAL(S11);
   CHECK_RETVAL(S22);
   CHECK_RETVAL(S12);

   *S11 = (m_Sii + m_Sjj)/2.0 + (m_Sii - m_Sjj)*cos(2*angle)/2.0 + m_Sij*sin(2*angle);
   *S12 = -(m_Sii - m_Sjj)*sin(2*angle)/2.0 + m_Sij*cos(2*angle);
   *S22 = m_Sii + m_Sjj - (*S11);

   return S_OK;
}

STDMETHODIMP CMohrCircle::ComputeSxx(Float64 angle,Float64* sxx)
{
   CHECK_RETVAL(sxx);
   Float64 syy, sxy;
   HRESULT hr = ComputeState(angle,sxx,&syy,&sxy);

   return hr;
}

STDMETHODIMP CMohrCircle::ComputeSxy(Float64 angle,Float64* sxy)
{
   CHECK_RETVAL(sxy);
   Float64 sxx, syy;
   HRESULT hr = ComputeState(angle,&sxx,&syy,sxy);

   return hr;
}

STDMETHODIMP CMohrCircle::ComputeSyy(Float64 angle,Float64* syy)
{
   CHECK_RETVAL(syy);
   Float64 sxx, sxy;
   HRESULT hr = ComputeState(angle,&sxx,syy,&sxy);

   return hr;
}
