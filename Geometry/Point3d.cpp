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

// Point3d.cpp : Implementation of CPoint3d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Point3d.h"
#include <GeomModel/CoordinateXform3d.h>
#include <MathEx.h>


/////////////////////////////////////////////////////////////////////////////
// CPoint3d

STDMETHODIMP CPoint3d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPoint3d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPoint3d::get_X(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_pPoint->X();
	return S_OK;
}

STDMETHODIMP CPoint3d::put_X(Float64 newVal)
{
   m_pPoint->X() = newVal;
	return S_OK;
}

STDMETHODIMP CPoint3d::get_Y(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_pPoint->Y();

	return S_OK;
}

STDMETHODIMP CPoint3d::put_Y(Float64 newVal)
{
   m_pPoint->Y() = newVal;
	return S_OK;
}

STDMETHODIMP CPoint3d::get_Z(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_pPoint->Z();
	return S_OK;
}

STDMETHODIMP CPoint3d::put_Z(Float64 newVal)
{
   m_pPoint->Z() = newVal;
	return S_OK;
}

STDMETHODIMP CPoint3d::Move(Float64 x, Float64 y, Float64 z)
{
   m_pPoint->Move(x, y, z);
	return S_OK;
}

STDMETHODIMP CPoint3d::MoveEx(IPoint3d *pPoint)
{
   CHECK_IN(pPoint);

   Float64 x,y,z;
   pPoint->Location(&x,&y,&z);

   return Move(x,y,z);
}

STDMETHODIMP CPoint3d::Offset(Float64 dx, Float64 dy, Float64 dz)
{
   m_pPoint->Offset(dx, dy, dz);
	return S_OK;
}

STDMETHODIMP CPoint3d::OffsetEx(ISize3d *pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy,dz;
   pSize->Dimensions(&dx,&dy,&dz);

   return Offset(dx,dy,dz);
}

STDMETHODIMP CPoint3d::Rotate(Float64 cx,Float64 cy,Float64 cz,IVector3d* vector,Float64 angle)
{
   CHECK_IN(vector);

   VARIANT_BOOL bIsZero;
   vector->IsZero(&bIsZero);
   if ( bIsZero == VARIANT_TRUE )
      return Error(IDS_E_ZEROMAGNITUDE,IID_IPoint3d,GEOMETRY_E_ZEROMAGNITUDE);

   WBFL::Geometry::Point3d origin(cx, cy, cz);
   
   Float64 x, y, z;
   vector->get_X(&x); vector->get_Y(&y); vector->get_Z(&z);
   WBFL::Geometry::Vector3d rv(x, y, z);

   WBFL::Geometry::CoordinateXform3d xform(origin, rv, angle);

   xform.Xform(*m_pPoint, WBFL::Geometry::CoordinateXform3d::Type::OldToNew);

   return S_OK;
}

STDMETHODIMP CPoint3d::RotateEx(IPoint3d* center,IVector3d* vector,Float64 angle)
{
   CHECK_IN(center);
   CHECK_IN(vector);

   Float64 cx,cy,cz;
   center->Location(&cx,&cy,&cz);

   return Rotate(cx,cy,cz,vector,angle);
}

STDMETHODIMP CPoint3d::SameLocation(IPoint3d* pOther)
{
   CHECK_IN(pOther);

   Float64 x,y,z;
   pOther->Location(&x,&y,&z);

   if ( IsEqual(m_pPoint->X(),x) && IsEqual(m_pPoint->Y(),y) && IsEqual(m_pPoint->Z(),z) )
      return S_OK;
   else
      return S_FALSE;
}

STDMETHODIMP CPoint3d::Location(Float64* pX,Float64* pY,Float64* pZ)
{
   CHECK_RETVAL(pX);
   CHECK_RETVAL(pY);
   CHECK_RETVAL(pZ);

   std::tie(*pX,*pY,*pZ) = m_pPoint->GetLocation();

   return S_OK;
}

STDMETHODIMP CPoint3d::Distance(Float64 x,Float64 y,Float64 z,Float64* pDistance)
{
   CHECK_RETVAL(pDistance);
   *pDistance = m_pPoint->Distance(x, y, z);
   return S_OK;
}

STDMETHODIMP CPoint3d::DistanceEx(IPoint3d* pOther,Float64* pDistance)
{
   CHECK_IN(pOther);
   Float64 x,y,z;
   pOther->Location(&x,&y,&z);
   return Distance(x,y,z,pDistance);
}

STDMETHODIMP CPoint3d::Clone(IPoint3d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   CComObject<CPoint3d>* pPoint;
   HRESULT hr = CComObject<CPoint3d>::CreateInstance(&pPoint);
   if ( FAILED(hr) )
      return hr;

   pPoint->m_pPoint = std::make_shared<WBFL::Geometry::Point3d>(*m_pPoint);

   (*ppPoint) = pPoint;
   (*ppPoint)->AddRef();

   return S_OK;
}
