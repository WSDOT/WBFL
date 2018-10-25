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

// CoordinateXform3d.cpp : Implementation of CCoordinateXform3d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "CoordinateXform3d.h"
#include "Helper.h"
#include <Math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// REFERENCES
// HP-41 Advantage Advanced Solutions Pac
// Hewlett Packard, July 1985
// pp 117-125

/////////////////////////////////////////////////////////////////////////////
// CCoordinateXform3d
HRESULT CCoordinateXform3d::FinalConstruct()
{
   HRESULT hr;
   hr = CreatePoint(0.00,0.00,0.00,NULL,&m_pNewOrigin);
   if ( FAILED(hr) ) return hr;

   hr = CreateVector(0.00,0.00,1.00,&m_pRotationVector);
   if ( FAILED(hr) ) return hr;

   m_Angle = 0.00;

   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICoordinateXform3d,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCoordinateXform3d::get_NewOrigin(IPoint3d **pVal)
{
   CHECK_RETOBJ(pVal);

   m_pNewOrigin->QueryInterface(pVal);

   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::putref_NewOrigin(IPoint3d *newVal)
{
   CHECK_IN(newVal);

   m_pNewOrigin = newVal;
   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::get_RotationAngle(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Angle;
   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::put_RotationAngle(Float64 newVal)
{
   m_Angle = newVal;
   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::get_RotationVector(IVector3d **pVal)
{
   CHECK_RETOBJ(pVal);

   m_pRotationVector->QueryInterface(pVal);

   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::putref_RotationVector(IVector3d *newVal)
{
   CHECK_IN(newVal);

   m_pRotationVector = newVal;

   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::Xform(IPoint3d** point,XformType type)
{
   CHECK_INOUT(point);

   HRESULT hr = S_OK;

   // Rotation Vector cannot be zero.
   VARIANT_BOOL bIsZero;
   m_pRotationVector->IsZero(  &bIsZero );
   if ( bIsZero == VARIANT_TRUE )
      return Error( IDS_E_ZEROMAGNITUDE, IID_ICoordinateXform2d, GEOMETRY_E_ZEROMAGNITUDE );

   if ( type == xfrmNewToOld )
      hr = NewToOld(*point);
   else
      hr = OldToNew(*point);

   return hr;
}

STDMETHODIMP CCoordinateXform3d::XformEx(IPoint3d* point, XformType type, IPoint3d** result)
{
   CHECK_IN(point);
   CHECK_RETOBJ(result);

   CreatePoint(point,NULL,result);
   return Xform(result,type);
}

STDMETHODIMP CCoordinateXform3d::NewToOld(IPoint3d *point)
{
   CComPtr<IVector3d> origin;
   CreateVector(m_pNewOrigin,&origin);

   CComPtr<IVector3d> Pn;
   CreateVector(point,&Pn);

   CComPtr<IVector3d> unit;
   CreateVector( m_pRotationVector, &unit );
   unit->Normalize();

   Float64 dot;
   Pn->Dot(unit,&dot);

   Float64 k = dot*(1-cos(m_Angle));

   CComPtr<IVector3d> v1;
   CreateVector(unit,&v1);
   v1->Scale(k);

   CComPtr<IVector3d> v2;
   CreateVector(Pn,&v2);
   v2->Scale(cos(m_Angle));

   CComPtr<IVector3d> xp;
   Pn->Cross(unit,&xp);

   CComPtr<IVector3d> v3;
   CreateVector(xp,&v3);
   v3->Scale(sin(-m_Angle));

   CComPtr<IVector3d> Po;
   CreateVector(v1,&Po);
   Add(Po,Po,v2);
   Add(Po,Po,v3);
   Add(Po,Po,origin);

   Float64 x,y,z;
   GetCoordinates(Po,&x,&y,&z);
   PutCoordinates(x,y,z,point);

   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::OldToNew(IPoint3d *point)
{
   CComPtr<IVector3d> origin;
   CreateVector(m_pNewOrigin,&origin);

   CComPtr<IVector3d> Po;
   CreateVector( point, &Po );

   CComPtr<IVector3d> v0;
   CreateVector(&v0);
   Subtract(v0,Po,origin);

   CComPtr<IVector3d> unit;
   CreateVector( m_pRotationVector, &unit );
   unit->Normalize();

   Float64 dot;
   v0->Dot(unit,&dot);
   
   Float64 k = dot*(1-cos(m_Angle));

   CComPtr<IVector3d> v1;
   CreateVector(unit,&v1);
   v1->Scale(k);

   CComPtr<IVector3d> v2;
   CreateVector(v0,&v2);
   v2->Scale(cos(m_Angle));

   CComPtr<IVector3d> xp;
   v0->Cross(unit,&xp);

   CComPtr<IVector3d> v3;
   CreateVector( xp, &v3);
   v3->Scale( sin(m_Angle) );

   CComPtr<IVector3d> Pn;
   CreateVector(v1,&Pn);
   Add(Pn,Pn,v2);
   Add(Pn,Pn,v3);

   Float64 x,y,z;
   GetCoordinates(Pn,&x,&y,&z);
   PutCoordinates(x,y,z,point);

   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CCoordinateXform3d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CCoordinateXform3d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("CoordinateXform3d"),1.0);

   // Save the offset constant
   pSave->put_Property(CComBSTR("Angle"),CComVariant(m_Angle));
   pSave->put_Property(CComBSTR("NewOrigin"),CComVariant(m_pNewOrigin));
   pSave->put_Property(CComBSTR("RotationVector"),CComVariant(m_pRotationVector));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("CoordinateXform3d"));
   
   pLoad->get_Property(CComBSTR("Angle"),&var);
   m_Angle = var.dblVal;

   pLoad->get_Property(CComBSTR("NewOrigin"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint3d>::copy(&m_pNewOrigin,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   pLoad->get_Property(CComBSTR("RotationVector"),&var);
   if ( FAILED( _CopyVariantToInterface<IVector3d>::copy(&m_pRotationVector,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
