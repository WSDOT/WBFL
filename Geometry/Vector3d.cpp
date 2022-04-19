///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// Vector3d.cpp : Implementation of CVector3d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Vector3d.h"
#include "Helper.h"
#include <MathEx.h>
#include <GeomModel/Primitives3d.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVector3d

STDMETHODIMP CVector3d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVector3d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CVector3d::get_X(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pVector->X();
	return S_OK;
}

STDMETHODIMP CVector3d::put_X(Float64 newVal)
{
   m_pVector->X() = newVal;
	return S_OK;
}

STDMETHODIMP CVector3d::get_Y(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pVector->Y();
	return S_OK;
}

STDMETHODIMP CVector3d::put_Y(Float64 newVal)
{
   m_pVector->Y() = newVal;
	return S_OK;
}

STDMETHODIMP CVector3d::get_Z(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pVector->Z();
	return S_OK;
}

STDMETHODIMP CVector3d::put_Z(Float64 newVal)
{
   m_pVector->Z() = newVal;
	return S_OK;
}

STDMETHODIMP CVector3d::IsZero(VARIANT_BOOL *pbResult)
{
   CHECK_RETVAL(pbResult);

   *pbResult = MakeBool( m_pVector->IsZero() );
   return S_OK;
}

STDMETHODIMP CVector3d::get_Magnitude(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pVector->GetMagnitude();
	return S_OK;
}

STDMETHODIMP CVector3d::put_Magnitude(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_MAGNITUDELESSTHANZERO,IID_IVector3d,GEOMETRY_E_MAGNITUDELESSTHANZERO);

   m_pVector->SetMagnitude(newVal);

   return S_OK;
}

STDMETHODIMP CVector3d::Normalize()
{
   try
   {
      m_pVector->Normalize();
   }
   catch (...)
   {
      return Error(IDS_E_ZEROMAGNITUDE, IID_IVector3d, GEOMETRY_E_ZEROMAGNITUDE);
   }
	return S_OK;
}

STDMETHODIMP CVector3d::Offset(Float64 dx, Float64 dy, Float64 dz)
{
   m_pVector->Offset(dx, dy, dz);
	return S_OK;
}

STDMETHODIMP CVector3d::OffsetEx(ISize3d *pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy,dz;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);
   pSize->get_Dz(&dz);

   return Offset(dx,dy,dz);
}

STDMETHODIMP CVector3d::Projection(IVector3d *pVector, Float64 *pDist)
{
   CHECK_IN(pVector);
   CHECK_RETVAL(pDist);

   Float64 x, y, z;
   pVector->get_X(&x); pVector->get_Y(&y); pVector->get_Z(&z);
   try
   {
      *pDist = m_pVector->Projection(WBFL::Geometry::Vector3d(x, y, z));
   }
   catch (...)
   {
      return Error(IDS_E_ZEROMAGNITUDE, IID_IVector3d, GEOMETRY_E_ZEROMAGNITUDE);
   }
   return S_OK;
}

STDMETHODIMP CVector3d::Reflect()
{
   m_pVector->Reflect();
   return S_OK;
}

STDMETHODIMP CVector3d::Scale(Float64 factor)
{
   m_pVector->Scale(factor);
	return S_OK;
}

STDMETHODIMP CVector3d::get_Size(ISize3d **pVal)
{
   CHECK_RETOBJ(pVal);

   auto size = m_pVector->GetSize();

   return CreateSize(size.Dx(),size.Dy(),size.Dz(),pVal);
}

STDMETHODIMP CVector3d::Cross(IVector3d *v, IVector3d **result)
{
   CHECK_IN(v);
   CHECK_RETOBJ(result);

   Float64 x, y, z;
   v->get_X(&x); v->get_Y(&y); v->get_Z(&z);

   auto cross = m_pVector->Cross(WBFL::Geometry::Vector3d(x,y,z));
   return CreateVector(cross, result);
}


STDMETHODIMP CVector3d::Dot(IVector3d *v, Float64 *val)
{
   CHECK_IN(v);
   CHECK_RETVAL(val);

   Float64 x, y, z;
   v->get_X(&x); v->get_Y(&y); v->get_Z(&z);

   *val = m_pVector->Dot(WBFL::Geometry::Vector3d(x, y, z));

   return S_OK;
}

STDMETHODIMP CVector3d::AngleBetween(IVector3d* v,Float64* angle)
{
   CHECK_IN(v);
   CHECK_RETVAL(angle);

   Float64 x, y, z;
   v->get_X(&x); v->get_Y(&y); v->get_Z(&z);

   try
   {
      *angle = m_pVector->AngleBetween(WBFL::Geometry::Vector3d(x, y, z));
   }
   catch (...)
   {
      return Error(IDS_E_ZEROMAGNITUDE, IID_IVector3d, GEOMETRY_E_ZEROMAGNITUDE);
   }
   return S_OK;
}

STDMETHODIMP CVector3d::IncrementBy(IVector3d* v,IVector3d** val)
{
   CHECK_IN(v);
   CHECK_RETOBJ(val);

   Float64 x, y, z;
   v->get_X(&x); v->get_Y(&y); v->get_Z(&z);

   return CreateVector(*m_pVector + WBFL::Geometry::Vector3d(x, y, z), val);
}

STDMETHODIMP CVector3d::Increment(IVector3d* v)
{
   CHECK_IN(v);

   Float64 x, y, z;
   v->get_X(&x); v->get_Y(&y); v->get_Z(&z);
 
   *m_pVector += WBFL::Geometry::Vector3d(x, y, z);

   return S_OK;
}

STDMETHODIMP CVector3d::DecrementBy(IVector3d* v,IVector3d** val)
{
   CHECK_IN(v);
   CHECK_RETOBJ(val);

   Float64 x, y, z;
   v->get_X(&x); v->get_Y(&y); v->get_Z(&z);

   return CreateVector(*m_pVector - WBFL::Geometry::Vector3d(x, y, z), val);
}

STDMETHODIMP CVector3d::Decrement(IVector3d* v)
{
   CHECK_IN(v);

   Float64 x, y, z;
   v->get_X(&x); v->get_Y(&y); v->get_Z(&z);

   *m_pVector -= WBFL::Geometry::Vector3d(x, y, z);

   return S_OK;
}

STDMETHODIMP CVector3d::Clone(IVector3d** ppClone)
{
   CHECK_RETVAL(ppClone);
   return CreateVector(*m_pVector, ppClone);
}
