///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

#include <MathEx.h>
#include "CoordinateXform3d.h"
#include "Helper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPoint3d

STDMETHODIMP CPoint3d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPoint3d,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPoint3d::get_X(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_X;
	return S_OK;
}

STDMETHODIMP CPoint3d::put_X(Float64 newVal)
{
   m_X = newVal;
   Fire_OnPointChanged(this);
	return S_OK;
}

STDMETHODIMP CPoint3d::get_Y(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Y;

	return S_OK;
}

STDMETHODIMP CPoint3d::put_Y(Float64 newVal)
{
   m_Y = newVal;
   Fire_OnPointChanged(this);
	return S_OK;
}

STDMETHODIMP CPoint3d::get_Z(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Z;
	return S_OK;
}

STDMETHODIMP CPoint3d::put_Z(Float64 newVal)
{
   m_Z = newVal;
   Fire_OnPointChanged(this);
	return S_OK;
}

STDMETHODIMP CPoint3d::Move(Float64 x, Float64 y, Float64 z)
{
   m_X = x;
   m_Y = y;
   m_Z = z;
   Fire_OnPointChanged(this);
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
   m_X += dx;
   m_Y += dy;
   m_Z += dz;
   Fire_OnPointChanged(this);
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

   CComObject<CCoordinateXform3d>* xform;
   HRESULT hr = CComObject<CCoordinateXform3d>::CreateInstance( &xform );
   if ( FAILED(hr) )
      return hr;

   CComPtr<ICoordinateXform3d> pXform(xform); // Use smart pointer to prevent leaks

   CComPtr<IPoint3d> origin;
   hr = CreatePoint(cx,cy,cz,NULL,&origin);
   if ( FAILED(hr) )
      return hr;

   xform->putref_RotationVector( vector );
   xform->put_RotationAngle( angle );
   xform->putref_NewOrigin( origin );

   IPoint3d* pThis = (IPoint3d*)this;
   hr = xform->Xform( &pThis, xfrmOldToNew );
   if ( FAILED(hr) )
      return hr;

   Fire_OnPointChanged(this);
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

STDMETHODIMP CPoint3d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

STDMETHODIMP CPoint3d::SameLocation(IPoint3d* pOther)
{
   CHECK_IN(pOther);

   Float64 x,y,z;
   pOther->Location(&x,&y,&z);

   if ( IsEqual(m_X,x) && IsEqual(m_Y,y) && IsEqual(m_Z,z) )
      return S_OK;
   else
      return S_FALSE;
}

STDMETHODIMP CPoint3d::Location(Float64* pX,Float64* pY,Float64* pZ)
{
   CHECK_RETVAL(pX);
   CHECK_RETVAL(pY);
   CHECK_RETVAL(pZ);

   *pX = m_X;
   *pY = m_Y;
   *pZ = m_Z;
   return S_OK;
}

STDMETHODIMP CPoint3d::Clone(IPoint3d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   CComObject<CPoint3d>* pPoint;
   HRESULT hr = CComObject<CPoint3d>::CreateInstance(&pPoint);
   if ( FAILED(hr) )
      return hr;

   (*ppPoint) = pPoint;
   (*ppPoint)->AddRef();

   (*ppPoint)->Move(m_X,m_Y,m_Z);

   return S_OK;
}

// IPersist
STDMETHODIMP CPoint3d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CPoint3d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Point3d"),1.0);
   pSave->put_Property(CComBSTR("X"),CComVariant(m_X));
   pSave->put_Property(CComBSTR("Y"),CComVariant(m_Y));
   pSave->put_Property(CComBSTR("Z"),CComVariant(m_Z));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CPoint3d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Point3d"));
   
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
