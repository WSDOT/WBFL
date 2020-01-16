///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// BulbTee.cpp : Implementation of CBulbTee
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "BulbTee.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// CBulbTee
HRESULT CBulbTee::FinalConstruct()
{
   m_Rotation = 0.0;

   m_BulbTee.CoCreateInstance(CLSID_BulbTee2);
   m_BulbTee.QueryInterface(&m_Shape);
   m_BulbTee.QueryInterface(&m_Position);

   m_BulbTee->put_C2(0);
   m_BulbTee->put_n1(0);
   m_BulbTee->put_n2(0);

   return S_OK;
}

void CBulbTee::FinalRelease()
{
}

STDMETHODIMP CBulbTee::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IBulbTee,
      &IID_IShape,
      &IID_IXYPosition,
      &IID_IStructuredStorage2
   };
   for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

STDMETHODIMP CBulbTee::get_W1(Float64 *pVal)
{
   return m_BulbTee->get_W1(pVal);
}

STDMETHODIMP CBulbTee::put_W1(Float64 newVal)
{
   return m_BulbTee->put_W1(newVal);
}

STDMETHODIMP CBulbTee::get_W2(Float64 *pVal)
{
   return m_BulbTee->get_W2(pVal);
}

STDMETHODIMP CBulbTee::put_W2(Float64 newVal)
{
   return m_BulbTee->put_W2(newVal);
}

STDMETHODIMP CBulbTee::get_W3(Float64 *pVal)
{
   return m_BulbTee->get_W3(pVal);
}

STDMETHODIMP CBulbTee::put_W3(Float64 newVal)
{
   return m_BulbTee->put_W3(newVal);
}

STDMETHODIMP CBulbTee::get_W4(Float64 *pVal)
{
   return m_BulbTee->get_W4(pVal);
}

STDMETHODIMP CBulbTee::put_W4(Float64 newVal)
{
   return m_BulbTee->put_W4(newVal);
}

STDMETHODIMP CBulbTee::get_W5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 w5, w6;
   m_BulbTee->get_W5(&w5);
   m_BulbTee->get_W6(&w6);
   *pVal = w5 + w6;
   return S_OK;
}

STDMETHODIMP CBulbTee::put_W5(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee, GEOMETRY_E_DIMENSION);

   Float64 w5 = newVal / 2;
   Float64 w6 = newVal / 2;
   m_BulbTee->put_W5(w5);
   m_BulbTee->put_W6(w6);

   return S_OK;
}

STDMETHODIMP CBulbTee::get_C1(Float64 *pVal)
{
   return m_BulbTee->get_C1(pVal);
}

STDMETHODIMP CBulbTee::put_C1(Float64 newVal)
{
   return m_BulbTee->put_C1(newVal);
}

STDMETHODIMP CBulbTee::get_D1(Float64 *pVal)
{
   return m_BulbTee->get_D1(pVal);
}

STDMETHODIMP CBulbTee::put_D1(Float64 newVal)
{
   return m_BulbTee->put_D1(newVal);
}

STDMETHODIMP CBulbTee::get_D2(Float64 *pVal)
{
   return m_BulbTee->get_D2(pVal);
}

STDMETHODIMP CBulbTee::put_D2(Float64 newVal)
{
   return m_BulbTee->put_D2(newVal);
}

STDMETHODIMP CBulbTee::get_D3(Float64 *pVal)
{
   return m_BulbTee->get_D3(pVal);
}

STDMETHODIMP CBulbTee::put_D3(Float64 newVal)
{
   return m_BulbTee->put_D3(newVal);
}

STDMETHODIMP CBulbTee::get_D4(Float64 *pVal)
{
   return m_BulbTee->get_D4(pVal);
}

STDMETHODIMP CBulbTee::put_D4(Float64 newVal)
{
   return m_BulbTee->put_D4(newVal);
}

STDMETHODIMP CBulbTee::get_D5(Float64 *pVal)
{
   return m_BulbTee->get_D5(pVal);
}

STDMETHODIMP CBulbTee::put_D5(Float64 newVal)
{
   return m_BulbTee->put_D5(newVal);
}

STDMETHODIMP CBulbTee::get_D6(Float64 *pVal)
{
   return m_BulbTee->get_D6(pVal);
}

STDMETHODIMP CBulbTee::put_D6(Float64 newVal)
{
   return m_BulbTee->put_D6(newVal);
}

STDMETHODIMP CBulbTee::get_D7(Float64 *pVal)
{
   return m_BulbTee->get_D7(pVal);
}

STDMETHODIMP CBulbTee::put_D7(Float64 newVal)
{
   return m_BulbTee->put_D7(newVal);
}

STDMETHODIMP CBulbTee::get_T1(Float64 *pVal)
{
   return m_BulbTee->get_T1(pVal);
}

STDMETHODIMP CBulbTee::put_T1(Float64 newVal)
{
   return m_BulbTee->put_T1(newVal);
}

STDMETHODIMP CBulbTee::get_T2(Float64 *pVal)
{
   return m_BulbTee->get_T2(pVal);
}

STDMETHODIMP CBulbTee::put_T2(Float64 newVal)
{
   return m_BulbTee->put_T2(newVal);
}

STDMETHODIMP CBulbTee::get_HookPoint(IPoint2d** hookPnt)
{
   return m_BulbTee->get_HookPoint(hookPnt);
}

STDMETHODIMP CBulbTee::putref_HookPoint(IPoint2d* hookPnt)
{
   return m_BulbTee->putref_HookPoint(hookPnt);
}

STDMETHODIMP CBulbTee::get_Height(Float64 *pVal)
{
#if defined _DEBUG
   Float64 Hmin, Hmax, Hcl;
   m_BulbTee->get_MinHeight(&Hmin);
   m_BulbTee->get_MaxHeight(&Hmax);
   m_BulbTee->get_CLHeight(&Hcl);
   ATLASSERT(IsEqual(Hmin, Hmax));
   ATLASSERT(IsEqual(Hmin, Hcl));
#endif
   return m_BulbTee->get_MinHeight(pVal);
}

STDMETHODIMP CBulbTee::get_AvgWebWidth(Float64 *pVal)
{
   return m_BulbTee->get_AvgWebWidth(pVal);
}

STDMETHODIMP CBulbTee::get_BottomFlangeWidth(Float64 *pVal)
{
   return m_BulbTee->get_BottomFlangeWidth(pVal);
}

STDMETHODIMP CBulbTee::get_TopFlangeWidth(Float64 *pVal)
{
   return m_BulbTee->get_TopFlangeWidth(pVal);
}

STDMETHODIMP CBulbTee::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CBulbTee::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CBulbTee::get_ShapeProperties(IShapeProperties* *pVal)
{
   return m_Shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CBulbTee::get_BoundingBox(IRect2d* *pVal)
{
   return m_Shape->get_BoundingBox(pVal);
}

STDMETHODIMP CBulbTee::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   return m_Shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CBulbTee::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   return m_Shape->PointInShape(pPoint, pbResult);
}

STDMETHODIMP CBulbTee::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CBulbTee>* pTheClone;
   HRESULT hr = CComObject<CBulbTee>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IBulbTee> shape(pTheClone); // need at least one reference

   Float64 C1, D1, D2, D3, D4, D5, D6, D7, T1, T2, W1, W2, W3, W4, W5;
   get_C1(&C1);
   get_D1(&D1);
   get_D2(&D2);
   get_D3(&D3);
   get_D4(&D4);
   get_D5(&D5);
   get_D6(&D6);
   get_D7(&D7);
   get_T1(&T1);
   get_T2(&T2);
   get_W1(&W1);
   get_W2(&W2);
   get_W3(&W3);
   get_W4(&W4);
   get_W5(&W5);

   pTheClone->put_C1( C1 );
   pTheClone->put_D1( D1 );
   pTheClone->put_D2( D2 );
   pTheClone->put_D3( D3 );
   pTheClone->put_D4( D4 );
   pTheClone->put_D5( D5 );
   pTheClone->put_D6( D6 );
   pTheClone->put_D7( D7 );
   pTheClone->put_T1( T1 );
   pTheClone->put_T2( T2 );
   pTheClone->put_W1( W1 );
   pTheClone->put_W2( W2 );
   pTheClone->put_W3( W3 );
   pTheClone->put_W4( W4 );
   pTheClone->put_W5( W5 );

   CComPtr<IPoint2d> hp;
   m_BulbTee->get_HookPoint(&hp);

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(hp,nullptr,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CBulbTee::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   return m_Shape->ClipWithLine(pLine, pShape);
}

STDMETHODIMP CBulbTee::ClipIn(IRect2d* pRect,IShape** pShape)
{
   return m_Shape->ClipIn(pRect, pShape);
}

STDMETHODIMP CBulbTee::get_Perimeter(Float64 *pVal)
{
   return m_Shape->get_Perimeter(pVal);
}

STDMETHODIMP CBulbTee::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   return m_Shape->FurthestDistance(line, pVal);
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CBulbTee::Offset(Float64 dx,Float64 dy)
{
   return m_Position->Offset(dx, dy);
}

STDMETHODIMP CBulbTee::OffsetEx(ISize2d* pSize)
{
   return m_Position->OffsetEx(pSize);
}

STDMETHODIMP CBulbTee::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   return m_Position->get_LocatorPoint(lp, point);
}

STDMETHODIMP CBulbTee::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   return m_Position->put_LocatorPoint(lp, point);
}

STDMETHODIMP CBulbTee::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   return m_Position->MoveEx(pFrom, pTo);
}

STDMETHODIMP CBulbTee::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CBulbTee::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // Need to keep track of rotation amount when creating clones
   m_Rotation += angle;

   return m_Position->Rotate(cx, cy, angle);
}


STDMETHODIMP CBulbTee::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CBulbTee::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CBulbTee::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   Float64 C1, D1, D2, D3, D4, D5, D6, D7, T1, T2, W1, W2, W3, W4, W5;
   get_C1(&C1);
   get_D1(&D1);
   get_D2(&D2);
   get_D3(&D3);
   get_D4(&D4);
   get_D5(&D5);
   get_D6(&D6);
   get_D7(&D7);
   get_T1(&T1);
   get_T2(&T2);
   get_W1(&W1);
   get_W2(&W2);
   get_W3(&W3);
   get_W4(&W4);
   get_W5(&W5);

   CComPtr<IPoint2d> hp;
   m_BulbTee->get_HookPoint(&hp);

   pSave->BeginUnit(CComBSTR("BulbTee"),2.0);
   pSave->put_Property(CComBSTR("C1"),CComVariant(C1)); // added in version 2
   pSave->put_Property(CComBSTR("D1"),CComVariant(D1));
   pSave->put_Property(CComBSTR("D2"),CComVariant(D2));
   pSave->put_Property(CComBSTR("D3"),CComVariant(D3));
   pSave->put_Property(CComBSTR("D4"),CComVariant(D4));
   pSave->put_Property(CComBSTR("D5"),CComVariant(D5));
   pSave->put_Property(CComBSTR("D6"),CComVariant(D6));
   pSave->put_Property(CComBSTR("D7"),CComVariant(D7));
   pSave->put_Property(CComBSTR("T1"),CComVariant(T1));
   pSave->put_Property(CComBSTR("T2"),CComVariant(T2));
   pSave->put_Property(CComBSTR("W1"),CComVariant(W1));
   pSave->put_Property(CComBSTR("W2"),CComVariant(W2));
   pSave->put_Property(CComBSTR("W3"),CComVariant(W3));
   pSave->put_Property(CComBSTR("W4"),CComVariant(W4));
   pSave->put_Property(CComBSTR("W5"),CComVariant(W5));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(hp));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CBulbTee::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("BulbTee"));

   Float64 vers;
   pLoad->get_Version(&vers);

   Float64 C1, D1, D2, D3, D4, D5, D6, D7, T1, T2, W1, W2, W3, W4, W5;

   if (vers>1.0)
   {
      pLoad->get_Property(CComBSTR("C1"),&var);
      C1 = var.dblVal;
   }
   else
   {
      C1 = 0.0;
   }
   
   pLoad->get_Property(CComBSTR("D1"),&var);
   D1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D2"),&var);
   D2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D3"),&var);
   D3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D4"),&var);
   D4 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D5"),&var);
   D5 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D6"),&var);
   D6 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D7"),&var);
   D7 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("T1"),&var);
   T1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("T2"),&var);
   T2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W1"),&var);
   W1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W2"),&var);
   W2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W3"),&var);
   W3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W4"),&var);
   W4 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W5"),&var);
   W5 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Rotation"),&var);
   m_Rotation = var.dblVal;

   CComPtr<IPoint2d> hp;
   pLoad->get_Property(CComBSTR("HookPoint"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&hp,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   put_C1(C1);
   put_D1(D1);
   put_D2(D2);
   put_D3(D3);
   put_D4(D4);
   put_D5(D5);
   put_D6(D6);
   put_D7(D7);
   put_T1(T1);
   put_T2(T2);
   put_W1(W1);
   put_W2(W2);
   put_W3(W3);
   put_W4(W4);
   put_W5(W5);

   m_BulbTee->putref_HookPoint(hp);

   RotateEx(hp, m_Rotation);


   return S_OK;
}
