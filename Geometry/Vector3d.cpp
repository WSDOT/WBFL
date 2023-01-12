///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// Vector3d.cpp : Implementation of CVector3d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Vector3d.h"
#include "Helper.h"
#include <MathEx.h>

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
		&IID_IVector3d,
      &IID_IStructuredStorage2
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

   *pVal = m_X;
	return S_OK;
}

STDMETHODIMP CVector3d::put_X(Float64 newVal)
{
   m_X = newVal;
	return S_OK;
}

STDMETHODIMP CVector3d::get_Y(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Y;
	return S_OK;
}

STDMETHODIMP CVector3d::put_Y(Float64 newVal)
{
   m_Y = newVal;
	return S_OK;
}

STDMETHODIMP CVector3d::get_Z(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Z;
	return S_OK;
}

STDMETHODIMP CVector3d::put_Z(Float64 newVal)
{
   m_Z = newVal;
	return S_OK;
}

STDMETHODIMP CVector3d::IsZero(VARIANT_BOOL *pbResult)
{
   CHECK_RETVAL(pbResult);

   *pbResult = MakeBool( ::IsZero(m_X) && ::IsZero(m_Y) && ::IsZero(m_Z) );
   return S_OK;
}

STDMETHODIMP CVector3d::get_Magnitude(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = sqrt(m_X*m_X + m_Y*m_Y + m_Z*m_Z);
	return S_OK;
}

STDMETHODIMP CVector3d::put_Magnitude(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(GEOMETRY_E_MAGNITUDELESSTHANZERO,IID_IVector3d,GEOMETRY_E_MAGNITUDELESSTHANZERO);

   HRESULT hr = Normalize();
   if ( FAILED(hr) )
      return hr;
   
   m_X *= newVal;
   m_Y *= newVal;
   m_Z *= newVal;
	return S_OK;
}

STDMETHODIMP CVector3d::Normalize()
{
   Float64 mag;
   get_Magnitude(&mag);

   if ( ::IsZero(mag) )
      return Error(IDS_E_ZEROMAGNITUDE,IID_IVector3d,GEOMETRY_E_ZEROMAGNITUDE);

   m_X /= mag;
   m_Y /= mag;
   m_Z /= mag;

	return S_OK;
}

STDMETHODIMP CVector3d::Offset(Float64 dx, Float64 dy, Float64 dz)
{
   m_X += dx;
   m_Y += dy;
   m_Z += dz;
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

   Float64 dot;
   Dot(pVector,&dot);

   Float64 mag;
   pVector->get_Magnitude(&mag);

   if ( ::IsZero(mag) )
      *pDist = 0.00;
   else
      *pDist = dot/mag;

   return S_OK;
}

STDMETHODIMP CVector3d::Reflect()
{
   m_X *= -1;
   m_Y *= -1;
   m_Z *= -1;
   return S_OK;
}

STDMETHODIMP CVector3d::Scale(Float64 factor)
{
   m_X *= factor;
   m_Y *= factor;
   m_Z *= factor;
	return S_OK;
}

STDMETHODIMP CVector3d::get_Size(ISize3d **pVal)
{
   CHECK_RETOBJ(pVal);

   return CreateSize(m_X,m_Y,m_Z,pVal);
}

STDMETHODIMP CVector3d::Cross(IVector3d *v, IVector3d **result)
{
   CHECK_IN(v);
   CHECK_RETOBJ(result);

   Float64 vx,vy,vz;
   v->get_X(&vx);
   v->get_Y(&vy);
   v->get_Z(&vz);

   Float64 x,y,z;
   x = m_Y*vz - m_Z*vy;
   y = m_Z*vx - m_X*vz;
   z = m_X*vy - m_Y*vx;

   return CreateVector(x,y,z,result);
}


STDMETHODIMP CVector3d::Dot(IVector3d *v, Float64 *val)
{
   CHECK_IN(v);
   CHECK_RETVAL(val);

   Float64 vx,vy,vz;
   v->get_X(&vx);
   v->get_Y(&vy);
   v->get_Z(&vz);

   *val = m_X*vx + m_Y*vy + m_Z*vz;
   return S_OK;
}

STDMETHODIMP CVector3d::AngleBetween(IVector3d* v,Float64* angle)
{
   CHECK_IN(v);
   CHECK_RETVAL(angle);

   Float64 dot;
   Float64 mag1, mag2;

   Dot(v,&dot);
   get_Magnitude(&mag1);
   v->get_Magnitude(&mag2);

   if ( ::IsZero(mag1) || ::IsZero(mag2) )
      return Error(IDS_E_ZEROMAGNITUDE,IID_IVector3d,GEOMETRY_E_ZEROMAGNITUDE);

   Float64 x = dot/(mag1*mag2);

   // if z is just barely greater than 1, make it equal to one
   if ( ::IsZero(x-1.0) && 1.0 < x )
      x = 1.0;

   *angle = acos(x);
   *angle = NormalizeAngle(*angle);

   return S_OK;
}

STDMETHODIMP CVector3d::IncrementBy(IVector3d* v,IVector3d** val)
{
   CHECK_IN(v);
   CHECK_RETOBJ(val);

   Float64 x,y,z;
   v->get_X(&x);
   v->get_Y(&y);
   v->get_Z(&z);

   CComObject<CVector3d>* pVec;
   CComObject<CVector3d>::CreateInstance(&pVec);
   *val = pVec;
   (*val)->AddRef();

   (*val)->put_X(m_X + x);
   (*val)->put_Y(m_Y + y);
   (*val)->put_Z(m_Z + z);

   return S_OK;
}

STDMETHODIMP CVector3d::Increment(IVector3d* v)
{
   CHECK_IN(v);

   Float64 x,y,z;
   v->get_X(&x);
   v->get_Y(&y);
   v->get_Z(&z);

   m_X += x;
   m_Y += y;
   m_Z += z;

   return S_OK;
}

STDMETHODIMP CVector3d::DecrementBy(IVector3d* v,IVector3d** val)
{
   CHECK_IN(v);
   CHECK_RETOBJ(val);

   Float64 x,y,z;
   v->get_X(&x);
   v->get_Y(&y);
   v->get_Z(&z);

   CComObject<CVector3d>* pVec;
   CComObject<CVector3d>::CreateInstance(&pVec);
   *val = pVec;
   (*val)->AddRef();

   (*val)->put_X(m_X - x);
   (*val)->put_Y(m_Y - y);
   (*val)->put_Z(m_Z - z);

   return S_OK;
}

STDMETHODIMP CVector3d::Decrement(IVector3d* v)
{
   CHECK_IN(v);

   Float64 x,y,z;
   v->get_X(&x);
   v->get_Y(&y);
   v->get_Z(&z);

   m_X -= x;
   m_Y -= y;
   m_Z -= z;

   return S_OK;
}

STDMETHODIMP CVector3d::Clone(IVector3d** ppClone)
{
   CHECK_RETVAL(ppClone);
   CComObject<CVector3d>* pClone;
   CComObject<CVector3d>::CreateInstance(&pClone);

   pClone->m_X = m_X;
   pClone->m_Y = m_Y;
   pClone->m_Z = m_Z;

   (*ppClone) = pClone;
   (*ppClone)->AddRef();

   return S_OK;
}

STDMETHODIMP CVector3d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CVector3d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CVector3d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Vector3d"),1.0);
   pSave->put_Property(CComBSTR("X"),CComVariant(m_X));
   pSave->put_Property(CComBSTR("Y"),CComVariant(m_Y));
   pSave->put_Property(CComBSTR("Z"),CComVariant(m_Z));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CVector3d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Vector2d"));
   
   pLoad->get_Property(CComBSTR("X"),&var);
   m_X = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Y"),&var);
   m_Y = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Z"),&var);
   m_Z = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
