///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// Vector2d.cpp : Implementation of CVector2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Vector2d.h"
#include "Helper.h"
#include <MathEx.h>
#include <GeomModel/Primitives.h>

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
		&IID_IVector2d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CVector2d::get_X(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_pVector->X();
	return S_OK;
}

STDMETHODIMP CVector2d::put_X(Float64 newVal)
{
   m_pVector->X() = newVal;
	return S_OK;
}

STDMETHODIMP CVector2d::get_Y(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_pVector->Y();
   return S_OK;
}

STDMETHODIMP CVector2d::put_Y(Float64 newVal)
{
   m_pVector->Y() = newVal;
	return S_OK;
}

STDMETHODIMP CVector2d::get_Direction(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pVector->GetDirection();
	return S_OK;
}

STDMETHODIMP CVector2d::put_Direction(Float64 newVal)
{
   m_pVector->SetDirection(newVal);
	return S_OK;
}

STDMETHODIMP CVector2d::get_Magnitude(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pVector->GetMagnitude();
	return S_OK;
}

STDMETHODIMP CVector2d::put_Magnitude(Float64 newVal)
{
   HRESULT hr = S_OK;

   if ( newVal < 0 )
      return Error(IDS_E_MAGNITUDELESSTHANZERO,IID_IVector2d,GEOMETRY_E_MAGNITUDELESSTHANZERO);
   
   m_pVector->SetMagnitude(newVal);

   return S_OK;
}

STDMETHODIMP CVector2d::get_Size(ISize2d **pVal)
{
   CHECK_RETOBJ(pVal);
   auto size = m_pVector->GetSize();
   return CreateSize(size.Dx(),size.Dy(),pVal);
}

STDMETHODIMP CVector2d::IsZero(VARIANT_BOOL *pbResult)
{
   CHECK_RETVAL(pbResult);

   *pbResult = ( m_pVector->IsZero() ) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CVector2d::Normal(IVector2d **ppNormal)
{
   CHECK_RETOBJ(ppNormal);
   return CreateVector(m_pVector->Normal(), ppNormal);
}

STDMETHODIMP CVector2d::Normalize()
{
   try
   {
      m_pVector->Normalize();
   }
   catch (...)
   {
      return Error(IDS_E_ZEROMAGNITUDE, IID_IVector2d, GEOMETRY_E_ZEROMAGNITUDE);
   }
	return S_OK;
}

STDMETHODIMP CVector2d::Offset(Float64 dx, Float64 dy)
{
   m_pVector->Offset(dx, dy);
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

   Float64 x, y;
   pVector->get_X(&x); pVector->get_Y(&y);

   try
   {
      *pVal = m_pVector->Projection(WBFL::Geometry::Vector2d(WBFL::Geometry::Size2d(x, y)));
   }
   catch (...)
   {
      return Error(IDS_E_ZEROMAGNITUDE, IID_IVector2d, GEOMETRY_E_ZEROMAGNITUDE);
   }

   return S_OK;
}

STDMETHODIMP CVector2d::Reflect()
{
   m_pVector->Reflect();
	return S_OK;
}

STDMETHODIMP CVector2d::Rotate(Float64 angle)
{
   m_pVector->Rotate(angle);
   return S_OK;
}

STDMETHODIMP CVector2d::Scale(Float64 factor)
{
   m_pVector->Scale(factor);
   return S_OK;
}

STDMETHODIMP CVector2d::Dot(IVector2d *v, Float64 *val)
{
   CHECK_IN(v);
   CHECK_RETVAL(val);
   
   Float64 x, y;
   v->get_X(&x); v->get_Y(&y);
   *val = m_pVector->Dot(WBFL::Geometry::Vector2d(WBFL::Geometry::Size2d(x, y)));


   return S_OK;
}

STDMETHODIMP CVector2d::AngleBetween(IVector2d* v,Float64* val)
{
   CHECK_IN(v);
   CHECK_RETVAL(val);

   Float64 x, y;
   v->get_X(&x); v->get_Y(&y);

   try
   {
      *val = m_pVector->AngleBetween(WBFL::Geometry::Vector2d(WBFL::Geometry::Size2d(x, y)));
   }
   catch (...)
   {
      return Error(IDS_E_ZEROMAGNITUDE, IID_IVector2d, GEOMETRY_E_ZEROMAGNITUDE);
   }

   return S_OK;
}

STDMETHODIMP CVector2d::IncrementBy(IVector2d* v,IVector2d** val)
{
   CHECK_IN(v);
   CHECK_RETOBJ(val);

   Float64 x, y;
   v->get_X(&x); v->get_Y(&y);

   return CreateVector(*m_pVector + WBFL::Geometry::Vector2d(WBFL::Geometry::Size2d(x, y)), val);
}

STDMETHODIMP CVector2d::Increment(IVector2d* v)
{
   CHECK_IN(v);

   Float64 x, y;
   v->get_X(&x); v->get_Y(&y);

   *m_pVector += WBFL::Geometry::Vector2d(WBFL::Geometry::Size2d(x, y));

   return S_OK;
}

STDMETHODIMP CVector2d::DecrementBy(IVector2d* v,IVector2d** val)
{
   CHECK_IN(v);
   CHECK_RETOBJ(val);

   Float64 x, y;
   v->get_X(&x); v->get_Y(&y);

   return CreateVector(*m_pVector - WBFL::Geometry::Vector2d(WBFL::Geometry::Size2d(x, y)), val);
}

STDMETHODIMP CVector2d::Decrement(IVector2d* v)
{
   CHECK_IN(v);

   Float64 x, y;
   v->get_X(&x); v->get_Y(&y);

   *m_pVector -= WBFL::Geometry::Vector2d(WBFL::Geometry::Size2d(x, y));

   return S_OK;
}

STDMETHODIMP CVector2d::Clone(IVector2d** ppClone)
{
   CHECK_RETVAL(ppClone);
   return CreateVector(*m_pVector, ppClone);
}
