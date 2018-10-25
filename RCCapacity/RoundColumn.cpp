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

// RoundColumn.cpp : Implementation of CRoundColumn
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "RoundColumn.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoundColumn

STDMETHODIMP CRoundColumn::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRoundColumn,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CRoundColumn::put_Diameter(Float64 dia)
{
   m_Diameter = dia;
   return S_OK;
}

STDMETHODIMP CRoundColumn::get_Diameter(Float64* dia)
{
   CHECK_RETVAL(dia);
   *dia = m_Diameter;
   return S_OK;
}

STDMETHODIMP CRoundColumn::put_Cover(Float64 cover)
{
   m_Cover = cover;
   return S_OK;
}

STDMETHODIMP CRoundColumn::get_Cover(Float64* cover)
{
   CHECK_RETVAL(cover);
   *cover = m_Cover;
   return S_OK;
}

STDMETHODIMP CRoundColumn::put_As(Float64 as)
{
   m_As = as;
   return S_OK;
}

STDMETHODIMP CRoundColumn::get_As(Float64* as)
{
   CHECK_RETVAL(as);
   *as = m_As;
   return S_OK;
}

STDMETHODIMP CRoundColumn::put_fc(Float64 fc)
{
   m_Fc = fc;
   return S_OK;
}

STDMETHODIMP CRoundColumn::get_fc(Float64* fc)
{
   CHECK_RETVAL(fc);
   *fc = m_Fc;
   return S_OK;
}

STDMETHODIMP CRoundColumn::put_fy(Float64 fy)
{
   m_Fy = fy;
   return S_OK;
}

STDMETHODIMP CRoundColumn::get_fy(Float64* fy)
{
   CHECK_RETVAL(fy);
   *fy = m_Fy;
   return S_OK;
}

STDMETHODIMP CRoundColumn::put_Es(Float64 es)
{
   m_Es = es;
   return S_OK;
}

STDMETHODIMP CRoundColumn::get_Es(Float64* es)
{
   CHECK_RETVAL(es);
   *es = m_Es;
   return S_OK;
}

STDMETHODIMP CRoundColumn::ComputeInteraction(long nSteps,IPoint2dCollection* *points)
{
   return ComputeInteractionCurve(nSteps,false,0,0,points,nullptr);
}

STDMETHODIMP CRoundColumn::ComputeInteractionEx(long nSteps,Float64 ecl,Float64 etl,IPoint2dCollection** ppUnfactored,IPoint2dCollection** ppFactored)
{
   return ComputeInteractionCurve(nSteps,true,ecl,etl,ppUnfactored,ppFactored);
}

HRESULT CRoundColumn::ComputeInteractionCurve(long nSteps,bool bFactor,Float64 ecl,Float64 etl,IPoint2dCollection** ppUnfactored,IPoint2dCollection** ppFactored)
{
   CHECK_RETOBJ(ppUnfactored);
   if ( bFactor )
   {
      CHECK_RETOBJ(ppFactored);
   }

   // This is a C translation from an old FORTRAN routine
   // The numbers refer to the line numbers in the original FORTRAN source
   CComPtr<IPoint2dCollection> unfactoredPoints;
   unfactoredPoints.CoCreateInstance(CLSID_Point2dCollection);

   CComPtr<IPoint2dCollection> factoredPoints;
   if ( bFactor )
   {
      factoredPoints.CoCreateInstance(CLSID_Point2dCollection);
   }

   Float64 p1, xm;
   Uint32 nb;
   Float64 b;
   Float64 r1, r2, x1, y1, x2, y2, o, o1, o2, z1, z2, w, a;
   Float64 f, f1, dol, sgn;
   Uint32 count;

   p1 = 0;
   xm = 0;

   Float64 step_size = 2*m_Diameter/nSteps;

   count = 0;
   for (long i = 1; i <= nSteps; i++ )
   {
      w = i*step_size; // depth to neutral axis
      for (nb = 1; nb <= 180; nb++)
      {
         b = nb*1;
         o = b*M_PI/180.0;
         r1 = m_Diameter/2;
         o1 = (b-0.5)*M_PI/180;
         x1 = r1*sin(o);
         y1 = r1*cos(o) + r1;
         r2 = r1 - m_Cover;
         x2 = r2*sin(o1);
         y2 = r2*cos(o1) + r1;
         z1 = (1 - y1/w)*0.003;
         z2 = (1 - y2/w)*0.003;
         // Comp = plus, Tension = minus
         // Compute forces in steel ring
         a = m_As/360;
         if (!((y2-0.85*w) > 0))
            {
            if (!(fabs(z2) >= m_Fy/m_Es))
               {
               f = a*(z2*m_Es - 0.85*m_Fc);
               }
            else // 120
               {
               if (z2 < 0)
                  sgn = -1; // 121
               else
                  sgn = 1;  // 122

               f = sgn*(m_Fy - 0.85*m_Fc)*a; // 123
               }
            }
         else // 125
            {
            if (!(fabs(z2) >= m_Fy/m_Es)) // 150
               {
               f = z2*m_Es*a;
               }
            else // 160
               {
               if (z2 < 0)
                  sgn = -1; // 161
               else
                  sgn = 1; // 162

               f = sgn*m_Fy*a; // 163
               }
            } // 165

         // Compute forces due to concrete

         o2 = (b-1)*M_PI/180.;
         dol = fabs(y1-r1*cos(o2)-r1);
         if (!((y1-0.85*w) >= 0))
            {
            f1 = (x1 + r1*sin(o2))/2 * dol * 0.85*m_Fc;
            }
         else // 190
            {
            f1 = 0;
            }

         // 195

         // Compute total axial force
         p1 += f + f1;

         // Compute total moment
         xm += f*(r1 - y2) + f1*(r1 - (y1 + r1*cos(o2) + r1)/2);

         } // 220 CONTINUE

      p1 *= 2;
      xm *= 2;

      CComPtr<IPoint2d> point;
      point.CoCreateInstance(CLSID_Point2d);
      point->Move(xm,-p1); // make tesion + and compression -
      unfactoredPoints->Add(point);

      if ( bFactor )
      {
         Float64 et = 0.003*( (m_Diameter-m_Cover)/w - 1);
         Float64 phi = 0.75 + 0.15*(et-ecl)/(etl-ecl);
         phi = ::ForceIntoRange(0.75,phi,0.9);

         xm *= phi;
         p1 *= phi;

         CComPtr<IPoint2d> point;
         point.CoCreateInstance(CLSID_Point2d);
         point->Move(xm,-p1);
         factoredPoints->Add(point);
      }

      count++;

      p1 = 0;
      xm = 0;
      } // 235 CONTINUE

   (*ppUnfactored) = unfactoredPoints;
   (*ppUnfactored)->AddRef();

   if ( bFactor )
   {
      (*ppFactored) = factoredPoints;
      (*ppFactored)->AddRef();
   }

   return S_OK;
}
