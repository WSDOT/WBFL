///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// ParabolicTendonSegment.cpp : Implementation of CParabolicTendonSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "ParabolicTendonSegment.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParabolicTendonSegment
HRESULT CParabolicTendonSegment::FinalConstruct()
{
   HRESULT hr;
   hr = m_Start.CoCreateInstance(CLSID_Point3d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_End.CoCreateInstance(CLSID_Point3d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   m_Slope = 0;
   m_SlopeEnd = qcbLeft;

   m_pTendon = nullptr;
   
   m_bUpdateParabolas = true;

   return S_OK;
}

void CParabolicTendonSegment::FinalRelease()
{
}

STDMETHODIMP CParabolicTendonSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IParabolicTendonSegment,
      &IID_ITendonSegment,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// IParabolicTendonSegment
STDMETHODIMP CParabolicTendonSegment::put_Start(IPoint3d* start)
{
   CHECK_IN(start);
   Float64 x,y,z;
   start->Location(&x,&y,&z);
   m_Start->Move(x,y,z);
   m_bUpdateParabolas = true;
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_Start(IPoint3d** start)
{
   CHECK_RETOBJ(start);
   return m_Start->Clone(start);
}

STDMETHODIMP CParabolicTendonSegment::put_End(IPoint3d* end)
{
   CHECK_IN(end);
   Float64 x,y,z;
   end->Location(&x,&y,&z);
   m_End->Move(x,y,z);
   m_bUpdateParabolas = true;
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_End(IPoint3d** end)
{
   CHECK_RETOBJ(end);
   return m_End->Clone(end);
}

STDMETHODIMP CParabolicTendonSegment::put_Slope(Float64 slope)
{
   ATLASSERT(IsZero(slope)); // current implementation assumes
   // that the slope is zero at one end of the parabola.
   // Generalize this later

   m_Slope = slope;
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_Slope(Float64* slope)
{
   CHECK_RETVAL(slope);
   *slope = m_Slope;
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::put_SlopeEnd(DirectionType end)
{
   m_SlopeEnd = end;
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_SlopeEnd(DirectionType* end)
{
   CHECK_RETVAL(end);
   *end = m_SlopeEnd;
   return S_OK;
}

/////////////////////////////////////////////////////
// ITendonSegment
STDMETHODIMP CParabolicTendonSegment::get_Position(TendonMeasure measure,Float64 z,IPoint3d** cg)
{
#pragma Reminder("UPDATE: need to make adjustment for strand being offset in duct if measure is tmTendon")
   CHECK_RETOBJ(cg);

   const mathPolynomial2d& parabolaX = GetParabolaX();
   const mathPolynomial2d& parabolaY = GetParabolaY();

   Float64 x = parabolaX.Evaluate(z);
   Float64 y = parabolaY.Evaluate(z);

   x = IsZero(x) ? 0 : x;
   z = IsZero(z) ? 0 : z;

   CComPtr<IPoint3d> p;
   p.CoCreateInstance(CLSID_Point3d);
   p->Move(x,y,z);
   (*cg) = p;
   (*cg)->AddRef();

   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_Slope(Float64 z,IVector3d** slope)
{
   CHECK_RETOBJ(slope);

   const mathPolynomial2d& parabolaX = GetParabolaX();
   const mathPolynomial2d& parabolaY = GetParabolaY();
   const mathPolynomial2d& slope_fn_x = GetParabolaDX();
   const mathPolynomial2d& slope_fn_y = GetParabolaDY();

   Float64 sx = slope_fn_x.Evaluate(z);
   Float64 sy = slope_fn_y.Evaluate(z);

   if (m_pTendon)
   {
      // get horizontal angular change due to plan view angle points in the superstructure member
      // NOTE: no angle points if this tendon segment is associated with a superstructure member segment
      Float64 value = 0;
      CComPtr<ISuperstructureMember> ssmbr;
      m_pTendon->get_SuperstructureMember(&ssmbr);
      if (ssmbr)
      {
         CComPtr<IAngle> planAngle;
         ssmbr->GetPlanAngle(z, &planAngle);
         planAngle->get_Value(&value);
      }

      Float64 a = atan(sx);
      sx = -tan(a+value);
   }

   CComPtr<IVector3d> vector;
   vector.CoCreateInstance(CLSID_Vector3d);

   vector->put_X(sx);
   vector->put_Y(sy);
   vector->put_Z(1.0);

   (*slope) = vector;
   (*slope)->AddRef();

   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_Length(Float64* length)
{
   // approximate the length of the tendon by summing straigh line chords from the centerline
   // a more exact method is available here  https://www.math.drexel.edu/~tolya/arc_length_x%5E2.pdf
   // but this method requires some manipulation since it only uses y=x^2 whereas our equation is y=Ax^2 + Bx + C
   *length = 0;

   CComPtr<IPoint3dCollection> points;
   get_Centerline(tmPath, &points);
   IndexType nPoints;
   points->get_Count(&nPoints);
   CComPtr<IPoint3d> p1, p2;
   IndexType idx = 0;
   points->get_Item(idx++, &p1);
   for (; idx < nPoints; idx++)
   {
      p2.Release();
      points->get_Item(idx, &p2);
      Float64 ds;
      p2->DistanceEx(p1, &ds);
      (*length) += ds;

      p1 = p2;
   }

   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::ProjectedLength(Float64* dx,Float64* dy,Float64* dz)
{
   CHECK_RETVAL(dx);
   CHECK_RETVAL(dy);
   CHECK_RETVAL(dz);

   Float64 x1,y1,z1;
   m_Start->Location(&x1,&y1,&z1);

   Float64 x2,y2,z2;
   m_End->Location(&x2,&y2,&z2);

   *dx = x2 - x1;
   *dy = y2 - y1;
   *dz = z2 - z1;

   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_Centerline(TendonMeasure measure,IPoint3dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   CComPtr<IPoint3dCollection> points;
   points.CoCreateInstance(CLSID_Point3dCollection);

   Float64 zStart, zEnd;
   m_Start->get_Z(&zStart);
   m_End->get_Z(&zEnd);

   Float64 dz = zEnd - zStart;

   IndexType nPoints = 11;
   for ( IndexType i = 0; i < nPoints; i++ )
   {
      Float64 z = zStart + i*dz/(nPoints-1);      

      CComPtr<IPoint3d> point;
      get_Position(measure,z,&point);
      points->Add(point);
   }

   return points.CopyTo(ppPoints);
}

STDMETHODIMP CParabolicTendonSegment::putref_Tendon(ITendon* pTendon)
{
   m_pTendon = pTendon;
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_Tendon(ITendon** ppTendon)
{
   (*ppTendon) = m_pTendon;
   if ( (*ppTendon) )
   {
      (*ppTendon)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_MinimumRadiusOfCurvature(Float64* pMinRadiusOfCurvature)
{
   CHECK_RETVAL(pMinRadiusOfCurvature);

   const mathPolynomial2d& fx = GetParabolaY();
   std::vector<Float64> coefficients(fx.GetCoefficients());
   ATLASSERT(coefficients.size() == 3);
   Float64 A = coefficients[0];

   // Parabola in the form of y = Ax^2 + Bx + C
   // if the coefficient A is zero, then the tendon path is linear,
   // the curvature is zero and the radius of curvature is infinite

   Float64 r = IsZero(A) ? DBL_MAX : 1/(2*A);

   *pMinRadiusOfCurvature = fabs(r);

   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CParabolicTendonSegment::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("ParabolicTendonSegment"));

   ATLASSERT(false); // not implemented

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("ParabolicTendonSegment"),1.0);

   ATLASSERT(false); // not implemented

   save->EndUnit();

   return S_OK;
}

void CParabolicTendonSegment::UpdateParabolas()
{
   if (m_bUpdateParabolas == false)
   {
      // already up to date
      return;
   }

   Float64 x1, y1, z1;
   m_Start->Location(&x1, &y1, &z1);

   Float64 x2, y2, z2;
   m_End->Location(&x2, &y2, &z2);

   Float64 dx = x2 - x1;
   Float64 dy = y2 - y1;
   Float64 dz = z2 - z1;

   // X Parabola
   Float64 A, B, C;
   if (m_SlopeEnd == qcbLeft)
   {
      // Slope is known at the left end
      A = (dx - dz*m_Slope) / (dz*dz);
      B = m_Slope - 2 * A*z1;
      C = x1 - A*z1*z1 - B*z1;
   }
   else
   {
      A = -(dx - dz*m_Slope) / (dz*dz);
      B = m_Slope - 2 * A*z2;
      C = x1 - A*z1*z1 - B*z1;
   }

   std::vector<Float64> coefficients;
   coefficients.push_back(A); // x = Az^2 + Bz + C
   coefficients.push_back(B);
   coefficients.push_back(C);

   m_ParabolaX.SetCoefficients(coefficients);
   m_ParabolaDX = m_ParabolaX.GetDerivative();

   // Y Parabola
   if (m_SlopeEnd == qcbLeft)
   {
      // Slope is known at the left end
      A = (dy - dz*m_Slope) / (dz*dz);
      B = m_Slope - 2 * A*z1;
      C = y1 - A*z1*z1 - B*z1;
   }
   else
   {
      A = -(dy - dz*m_Slope) / (dz*dz);
      B = m_Slope - 2 * A*z2;
      C = y1 - A*z1*z1 - B*z1;
   }


   coefficients.clear();
   coefficients.push_back(A); // y = Az^2 + Bz + C
   coefficients.push_back(B);
   coefficients.push_back(C);

   m_ParabolaY.SetCoefficients(coefficients);
   m_ParabolaDY = m_ParabolaY.GetDerivative();
   
   m_bUpdateParabolas = false;
}

const mathPolynomial2d& CParabolicTendonSegment::GetParabolaX()
{
   UpdateParabolas();
   return m_ParabolaX;
}

const mathPolynomial2d& CParabolicTendonSegment::GetParabolaDX()
{
   UpdateParabolas();
   return m_ParabolaDX;
}

const mathPolynomial2d& CParabolicTendonSegment::GetParabolaY()
{
   UpdateParabolas();
   return m_ParabolaY;
}

const mathPolynomial2d& CParabolicTendonSegment::GetParabolaDY()
{
   UpdateParabolas();
   return m_ParabolaDY;
}
