///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 2000  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// Vector2d.cpp : Implementation of CVector2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Vector2d.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVector2d

STDMETHODIMP CVector2d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVector2d,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CVector2d::get_X(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_X;
	return S_OK;
}

STDMETHODIMP CVector2d::put_X(Float64 newVal)
{
   m_X = newVal;
	return S_OK;
}

STDMETHODIMP CVector2d::get_Y(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Y;
   return S_OK;
}

STDMETHODIMP CVector2d::put_Y(Float64 newVal)
{
   m_Y = newVal;
	return S_OK;
}

STDMETHODIMP CVector2d::get_Direction(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 angle = atan2(m_Y,m_X);
   angle = NormalizeAngle( angle );

   *pVal = angle;
	return S_OK;
}

STDMETHODIMP CVector2d::put_Direction(Float64 newVal)
{
   Float64 magnitude;
   get_Magnitude(&magnitude);

   m_X = magnitude * cos(newVal);
   m_Y = magnitude * sin(newVal);

	return S_OK;
}

STDMETHODIMP CVector2d::get_Magnitude(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = sqrt( m_X*m_X + m_Y*m_Y);
	return S_OK;
}

STDMETHODIMP CVector2d::put_Magnitude(Float64 newVal)
{
   HRESULT hr = S_OK;

   if ( newVal < 0 )
      return Error(IDS_E_MAGNITUDELESSTHANZERO,IID_IVector2d,GEOMETRY_E_MAGNITUDELESSTHANZERO);
   
   hr = Normalize();
   if ( FAILED(hr) )
      return hr;

   m_X *= newVal;
   m_Y *= newVal;

   return S_OK;
}

STDMETHODIMP CVector2d::get_Size(ISize2d **pVal)
{
   CHECK_RETOBJ(pVal);

   return CreateSize(m_X,m_Y,pVal);
}

STDMETHODIMP CVector2d::IsZero(VARIANT_BOOL *pbResult)
{
   CHECK_RETVAL(pbResult);

   *pbResult = ( ::IsZero(m_X) && ::IsZero(m_Y) ) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CVector2d::Normal(IVector2d **ppNormal)
{
   CHECK_RETOBJ(ppNormal);
   return CreateVector( -m_Y, m_X, ppNormal );
}

STDMETHODIMP CVector2d::Normalize()
{
   Float64 mag;
   get_Magnitude(&mag);

   if ( ::IsZero(mag) )
      return Error(IDS_E_ZEROMAGNITUDE,IID_IVector2d,GEOMETRY_E_ZEROMAGNITUDE);

   m_X /= mag;
   m_Y /= mag;

	return S_OK;
}

STDMETHODIMP CVector2d::Offset(Float64 dx, Float64 dy)
{
   m_X += dx;
   m_Y += dy;
	return S_OK;
}

STDMETHODIMP CVector2d::OffsetEx(ISize2d *pSize)
{
   CHECK_IN(pSize);

   Float64 dx, dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Offset( dx, dy );
}

STDMETHODIMP CVector2d::Projection(IVector2d *pVector, Float64 *pVal)
{
   CHECK_IN(pVector);
   CHECK_RETVAL(pVal);

   Float64 dot;
   Dot(pVector,&dot);

   Float64 mag;
   pVector->get_Magnitude(&mag);

   if ( ::IsZero(mag) )
      *pVal = 0.00;
   else
      *pVal = dot/mag;

   return S_OK;
}

STDMETHODIMP CVector2d::Reflect()
{
   m_X *= -1;
   m_Y *= -1;
	return S_OK;
}

STDMETHODIMP CVector2d::Rotate(Float64 angle)
{
   Float64 x, y;
   Float64 cosa = cos(angle);
   Float64 sina = sin(angle);
   
   x = m_X*cosa - m_Y*sina;
   y = m_X*sina + m_Y*cosa;

   m_X = x;
   m_Y = y;

   return S_OK;
}

STDMETHODIMP CVector2d::Scale(Float64 factor)
{
   m_X *= factor;
   m_Y *= factor; 

   return S_OK;
}

STDMETHODIMP CVector2d::Dot(IVector2d *v, Float64 *val)
{
   CHECK_IN(v);
   CHECK_RETVAL(val);

   Float64 x, y;
   v->get_X(&x);
   v->get_Y(&y);
   *val = (m_X*x) + (m_Y*y);

   return S_OK;
}

STDMETHODIMP CVector2d::AngleBetween(IVector2d* v,Float64* val)
{
   CHECK_IN(v);
   CHECK_RETVAL(val);

   Float64 dot;
   Float64 mag1, mag2;

   Dot(v,&dot);
   get_Magnitude(&mag1);
   v->get_Magnitude(&mag2);

   if ( ::IsZero(mag1) || ::IsZero(mag2) )
      return Error(IDS_E_ZEROMAGNITUDE,IID_IVector2d,GEOMETRY_E_ZEROMAGNITUDE);

   Float64 x = dot/(mag1*mag2);
   if ( ::IsZero(x-1.0) )
      x = 1.0;

   *val = acos(x);

   *val = NormalizeAngle(*val);

   return S_OK;
}

STDMETHODIMP CVector2d::IncrementBy(IVector2d* v,IVector2d** val)
{
   CHECK_IN(v);
   CHECK_RETOBJ(val);

   Float64 x,y;
   v->get_X(&x);
   v->get_Y(&y);

   CComObject<CVector2d>* pVec;
   CComObject<CVector2d>::CreateInstance(&pVec);
   *val = pVec;
   (*val)->AddRef();

   (*val)->put_X(m_X + x);
   (*val)->put_Y(m_Y + y);

   return S_OK;
}

STDMETHODIMP CVector2d::Increment(IVector2d* v)
{
   CHECK_IN(v);

   Float64 x,y;
   v->get_X(&x);
   v->get_Y(&y);

   m_X += x;
   m_Y += y;

   return S_OK;
}

STDMETHODIMP CVector2d::DecrementBy(IVector2d* v,IVector2d** val)
{
   CHECK_IN(v);
   CHECK_RETOBJ(val);

   Float64 x,y;
   v->get_X(&x);
   v->get_Y(&y);

   CComObject<CVector2d>* pVec;
   CComObject<CVector2d>::CreateInstance(&pVec);
   *val = pVec;
   (*val)->AddRef();

   (*val)->put_X(m_X - x);
   (*val)->put_Y(m_Y - y);

   return S_OK;
}

STDMETHODIMP CVector2d::Decrement(IVector2d* v)
{
   CHECK_IN(v);

   Float64 x,y;
   v->get_X(&x);
   v->get_Y(&y);

   m_X -= x;
   m_Y -= y;

   return S_OK;
}

STDMETHODIMP CVector2d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CVector2d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CVector2d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Vector2d"),1.0);
   pSave->put_Property(CComBSTR("X"),CComVariant(m_X));
   pSave->put_Property(CComBSTR("Y"),CComVariant(m_Y));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CVector2d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Vector2d"));
   
   pLoad->get_Property(CComBSTR("X"),&var);
   m_X = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Y"),&var);
   m_Y = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
