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

// Line2d.cpp : Implementation of CLine2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Line2d.h"
#include "Helper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT explicit_to_implicit(IPoint2d* pU, IVector2d* pV, Float64* pC, IVector2d** pN)
{
   ATLASSERT( pU != NULL );
   ATLASSERT( pV != NULL );
   ATLASSERT( pC != NULL );
   ATLASSERT( pN != NULL && *pN == NULL );

   CComPtr<IVector2d> pVN;
   Float64 x,y;
   pV->get_X(&x);
   pV->get_Y(&y);
   CreateVector(x,y,&pVN);
   pVN->Normalize();
   pVN->Normal(pN);

   pU->get_X(&x);
   pU->get_Y(&y);
   CComPtr<IVector2d> pUV;
   CreateVector(x,y,&pUV);
   (*pN)->Dot(pUV,pC);

   return S_OK;
}

HRESULT point_on_explicit_nearest(Float64 C, IVector2d* pN, IPoint2d* pPoint,IPoint2d** pPOLN)
{
   ATLASSERT( pN != NULL );
   ATLASSERT( pPoint != NULL );
   ATLASSERT( pPOLN != NULL && *pPOLN == NULL );

   // don't need to normalize N since it already should be
   Float64 x,y;
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   CComPtr<IVector2d> pVP;
   CreateVector(x,y,&pVP);
   Float64 dot;
   pN->Dot(pVP,&dot);

   Float64 q = -C + dot;

   CComPtr<IVector2d> pScaled;
   Float64 vx, vy;
   pN->get_X(&vx);
   pN->get_Y(&vy);
   CreateVector(vx,vy,&pScaled);
   pScaled->Scale(q);

   Float64 sx, sy;
   pScaled->get_X(&sx);
   pScaled->get_Y(&sy);

   CreatePoint( (x - sx), (y - sy), NULL, pPOLN );   

   return S_OK;
}

HRESULT implicit_to_explicit(Float64 C, IVector2d* pN, IPoint2d** pU, IVector2d** pV)
{
   ATLASSERT( pN != NULL );
   ATLASSERT( pU != NULL && *pU == NULL );
   ATLASSERT( pV != NULL && *pV == NULL );

   CComPtr<IPoint2d> pOrigin;
   CreatePoint(0.0,0.0,NULL,&pOrigin);

   point_on_explicit_nearest(C,pN,pOrigin,pU);
   pN->Normal( pV );
   (*pV)->Reflect();

   return S_OK;
}

HRESULT point_to_implicit(IPoint2d* pPoint1, IPoint2d* pPoint2, 
                          Float64* pC, IVector2d** pN)
{
   ATLASSERT( pPoint1 != NULL );
   ATLASSERT( pPoint2 != NULL );
   ATLASSERT( pC != NULL );
   ATLASSERT( pN != NULL && *pN == NULL );

   // Can't make a line if the end points are identical
   ATLASSERT( !IsEqualPoint(pPoint1,pPoint2) );

   CComPtr<IPoint2d> plu;
   CreatePoint(0.0,0.0,NULL,&plu);
   Float64 x1,y1;
   pPoint1->get_X(&x1);
   pPoint1->get_Y(&y1);
   plu->put_X(x1);
   plu->put_Y(y1);

   Float64 x2,y2;
   pPoint2->get_X(&x2);
   pPoint2->get_Y(&y2);

   CComPtr<IVector2d> plv;
   CreateVector(x2-x1,y2-y1,&plv);
   return explicit_to_implicit(plu,plv,pC,pN);
}

/////////////////////////////////////////////////////////////////////////////
// CLine2d

STDMETHODIMP CLine2d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILine2d,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CLine2d::FinalConstruct()
{
   m_C = 0;

   // Create a normal vector
   HRESULT hr = CreateVector(0,1,&m_pN);
   if ( FAILED(hr) )
      return hr;

   hr = m_pN->Normalize();
   return hr;
}

STDMETHODIMP CLine2d::GetExplicit(IPoint2d** p,IVector2d** d)
{
   CHECK_RETOBJ(p);
   CHECK_RETOBJ(d);

   CComPtr<IVector2d> v;
   CComPtr<IPoint2d> pnt;
   HRESULT hr = implicit_to_explicit(m_C, m_pN, &pnt, &v);
   if ( FAILED(hr) )
      return hr;

   (*p) = pnt;
   (*p)->AddRef();

   (*d) = v;
   (*d)->AddRef();

   return S_OK;
}

STDMETHODIMP CLine2d::SetExplicit(IPoint2d *p,IVector2d* d)
{
   CHECK_IN(p);
   CHECK_IN(d);

   VARIANT_BOOL bIsZero;
   d->IsZero( &bIsZero );
   if ( bIsZero == VARIANT_TRUE )
      return Error(IDS_E_ZEROMAGNITUDE,IID_ILine2d,GEOMETRY_E_ZEROMAGNITUDE);

   m_pN.Release();
   return explicit_to_implicit(p, d, &m_C, &m_pN);
}

STDMETHODIMP CLine2d::SetImplicit(Float64 c, IVector2d *pN)
{
   CHECK_IN(pN);

   VARIANT_BOOL bIsZero;
   pN->IsZero( &bIsZero );
   if ( bIsZero == VARIANT_TRUE )
      return Error(IDS_E_ZEROMAGNITUDE,IID_ILine2d,GEOMETRY_E_ZEROMAGNITUDE);

   m_C = c;

   // Copy the vector X and Y properties.
   // We don't want the have someone on the outside have a reference to
   // the private data of this class.
   Float64 x,y;
   pN->get_X(&x);
   pN->get_Y(&y);

   m_pN->put_X(x);
   m_pN->put_Y(y);

   return S_OK;
}

STDMETHODIMP CLine2d::GetImplicit(Float64 *pC, IVector2d** pN)
{
   CHECK_RETVAL(pC);
   CHECK_RETOBJ(pN);

   // Copy the vector X and Y properties.
   // We don't want the have someone on the outside have a reference to
   // the private data of this class.
   Float64 x,y;
   GetCoordinates(m_pN,&x,&y);

   CComPtr<IVector2d> v;
   CreateVector(x,y,&v);

   (*pN) = v;
   (*pN)->AddRef();

   *pC = m_C;

   return S_OK;
}

STDMETHODIMP CLine2d::ThroughPoints(IPoint2d *p1, IPoint2d *p2)
{
   CHECK_IN(p1);
   CHECK_IN(p2);

   if ( IsEqualPoint(p1,p2) )
      return Error(IDS_E_SAMEPOINTS,IID_ILine2d,GEOMETRY_E_SAMEPOINTS);

   m_pN.Release();
   return point_to_implicit(p1,p2,&m_C,&m_pN);
}

STDMETHODIMP CLine2d::Offset(Float64 offset)
{
   m_C += offset;
   return S_OK;
}

STDMETHODIMP CLine2d::Rotate(Float64 cx,Float64 cy, Float64 angle)
{
   CComPtr<IPoint2d> pU;
   CComPtr<IVector2d> pV;
   implicit_to_explicit(m_C,m_pN,&pU,&pV);

   pU->Rotate( cx, cy, angle );
   pV->Rotate( angle );

   m_pN.Release();
   return explicit_to_implicit(pU,pV,&m_C,&m_pN);
}

STDMETHODIMP CLine2d::RotateEx(IPoint2d *pCenter, Float64 angle)
{
   CHECK_IN(pCenter);

   Float64 x,y;
   pCenter->get_X(&x);
   pCenter->get_Y(&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CLine2d::Reverse()
{
   m_pN->Reflect();
   m_C *= -1;
   return S_OK;
}

STDMETHODIMP CLine2d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CLine2d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CLine2d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Line2d"),1.0);

   // Save the offset constant
   pSave->put_Property(CComBSTR("C"),CComVariant(m_C));

   pSave->BeginUnit(CComBSTR("Normal"),1.0);
   // Save the normal vector.
   // This vector is not polymorphic. The SetImplicit method has
   // By Value semantics. Therefore, we do not need to save
   // the vector with its CLSID.
   CComQIPtr<IStructuredStorage2> ss(m_pN);
   ATLASSERT(ss);
   ss->Save(pSave);
   pSave->EndUnit(); // Normal

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CLine2d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Line2d"));
   
   pLoad->get_Property(CComBSTR("C"),&var);
   m_C = var.dblVal;

   pLoad->BeginUnit(CComBSTR("Normal"));
   CComQIPtr<IStructuredStorage2> ss(m_pN);
   ATLASSERT(ss);
   ss->Load(pLoad);

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);// Normal
   ATLASSERT(bEnd == VARIANT_TRUE);

   pLoad->EndUnit(&bEnd);
   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
