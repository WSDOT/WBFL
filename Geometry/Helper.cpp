///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2018  Washington State Department of Transportation
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

#include "StdAfx.h"
#include "WBFLGeometry.h"
#include "Helper.h"

#include "Point2d.h"
#include "Point3d.h"
#include "Rect2d.h"
#include "Size2d.h"
#include "Size3d.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include "Point2dCollection.h"
#include "Point3dCollection.h"
#include "LineSegment2d.h"
#include "Line2d.h"
#include "ShapeProperties.h"
#include "PolyShape.h"
#include "GeomUtil.h"
#include "CompositeShape.h"

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT CopyPoint(IPoint2d* pTo,IPoint2d* pFrom)
{
   ATLASSERT(pTo != 0 && pFrom != 0);

   Float64 x,y;
   GetCoordinates(pFrom,&x,&y);
   PutCoordinates(x,y,pTo);

   return S_OK;
}

HRESULT CopyLineSegment(ILineSegment2d* pTo,ILineSegment2d* pFrom)
{
   ATLASSERT( pTo != 0 && pFrom != 0 );
   CComPtr<IPoint2d> pStartFrom;
   CComPtr<IPoint2d> pEndFrom;
   pFrom->get_StartPoint(&pStartFrom);
   pFrom->get_EndPoint(&pEndFrom);

   CComPtr<IPoint2d> pStartTo;
   CComPtr<IPoint2d> pEndTo;
   pTo->get_StartPoint(&pStartTo);
   pTo->get_EndPoint(&pEndTo);

   CopyPoint(pStartTo,pStartFrom);
   CopyPoint(pEndTo,pEndFrom);

   return S_OK;
}

HRESULT CopyPoints(IPoint2dCollection* pTo,IPoint2dCollection* pFrom)
{
   ATLASSERT( pTo != 0 && pFrom != 0 );

   pTo->Clear();

   CollectionIndexType cPoint;
   pFrom->get_Count(&cPoint);
   for ( CollectionIndexType idx = 0; idx < cPoint; idx++ )
   {
      CComPtr<IPoint2d> pPoint;
      pFrom->get_Item(idx,&pPoint);

      CComPtr<IPoint2d> pNewPoint;
      CreatePoint(pPoint,nullptr,&pNewPoint);

      pTo->Add(pNewPoint);
   }

   return S_OK;
}

HRESULT CreatePointCollection(IPoint2dCollection** ppPoints,IPoint2dCollection* pCopyFrom)
{
   ATLASSERT( ppPoints != 0 && (*ppPoints) == 0 );

   CComObject<CPoint2dCollection>* pPoints;
   HRESULT hr = CComObject<CPoint2dCollection>::CreateInstance( &pPoints );
   if ( FAILED(hr) )
      return hr;

   pPoints->AddRef();
   (*ppPoints) = pPoints;

   pPoints->EnableEvents(false);
   CopyPoints(*ppPoints,pCopyFrom);
   pPoints->EnableEvents(true);

   return S_OK;
}

HRESULT GetCoordinates(IPoint2d* pPoint,Float64* px,Float64* py)
{
   ATLASSERT(pPoint != 0 && px != 0 && py != 0);

   HRESULT hr = pPoint->Location(px,py);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

HRESULT GetCoordinates(IPoint3d* pPoint,Float64* px,Float64* py,Float64* pz)
{
   ATLASSERT(pPoint != 0 && px != 0 && py != 0 && pz != 0);

   HRESULT hr = pPoint->Location(px,py,pz);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

HRESULT PutCoordinates(Float64 x,Float64 y,IPoint2d* pPoint)
{
   ATLASSERT(pPoint != 0 );

   pPoint->Move(x,y);

   return S_OK;
}

HRESULT PutCoordinates(Float64 x,Float64 y,Float64 z,IPoint3d* pPoint)
{
   ATLASSERT(pPoint != 0 );

   pPoint->Move(x,y,z);

   return S_OK;
}

HRESULT GetSize(ISize2d* pSize,Float64* pdx,Float64* pdy)
{
   ATLASSERT( pSize != 0 && pdx != 0 && pdy != 0 );

   HRESULT hr;
   hr = pSize->get_Dx(pdx);
   if ( FAILED(hr) )
      return hr;

   hr = pSize->get_Dy(pdy);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

HRESULT GetRect(IRect2d* rect,Float64 *left,Float64 *top,Float64 *right,Float64 *bottom)
{
   ATLASSERT( rect != 0 && left != 0 && top != 0 && right != 0 && bottom != 0);
   rect->get_Left(left);
   rect->get_Right(right);
   rect->get_Top(top);
   rect->get_Bottom(bottom);
   return S_OK;
}

HRESULT CreatePoint(IPoint2d* pPoint,IPoint2dFactory* pFactory,IPoint2d** ppPoint)
{
   ATLASSERT( pPoint != 0 && ppPoint != 0 && (*ppPoint) == 0 );

   Float64 x,y;
   pPoint->Location(&x,&y);

   return CreatePoint(x,y,pFactory,ppPoint);
}

HRESULT CreatePoint(Float64 x,Float64 y,IPoint2dFactory* pFactory,IPoint2d** ppPoint)
{
   ATLASSERT( ppPoint != 0 && (*ppPoint) == 0 );

   if ( pFactory == 0 )
   {
      CComObject<CPoint2d>* pPoint;
      HRESULT hr = CComObject<CPoint2d>::CreateInstance(&pPoint);
      if ( FAILED(hr) )
         return hr;

      pPoint->AddRef();
      (*ppPoint) = pPoint;
   }
   else
   {
      HRESULT hr = pFactory->CreatePoint(ppPoint);
      if ( FAILED(hr) )
         return hr;
   }

   (*ppPoint)->Move(x,y);


   return S_OK;
}

HRESULT CreatePoint(IPoint3d* pPoint,IPoint3dFactory* pFactory,IPoint3d** ppPoint)
{
   ATLASSERT( pPoint != 0 && ppPoint != 0 && (*ppPoint == 0) );

   Float64 x,y,z;
   pPoint->Location(&x,&y,&z);

   return CreatePoint(x,y,z,pFactory,ppPoint);
}

HRESULT CreatePoint(Float64 x,Float64 y,Float64 z,IPoint3dFactory* pFactory,IPoint3d** ppPoint)
{
   ATLASSERT( ppPoint != 0 && (*ppPoint == 0) );

   if ( pFactory == 0 )
   {
      CComObject<CPoint3d>* pPoint;
      HRESULT hr = CComObject<CPoint3d>::CreateInstance(&pPoint);
      if ( FAILED(hr) )
         return hr;

      pPoint->AddRef();
      (*ppPoint) = pPoint;
   }
   else
   {
      HRESULT hr = pFactory->CreatePoint(ppPoint);
      if ( FAILED(hr) )
         return hr;
   }

   (*ppPoint)->Move(x,y,z);


   return S_OK;
}

HRESULT CreateRect(Float64 left,Float64 top,Float64 right,Float64 bottom,IRect2d** ppRect)
{
   ATLASSERT( ppRect != 0 && (*ppRect) == 0 );

   CComObject<CRect2d>* pRect;
   HRESULT hr = CComObject<CRect2d>::CreateInstance(&pRect);
   if ( FAILED(hr) )
      return hr;

   pRect->AddRef();

   pRect->put_Left( left );
   pRect->put_Right( right );
   pRect->put_Top( top );
   pRect->put_Bottom( bottom );

   (*ppRect) = pRect;

   return S_OK;
}

HRESULT CreateSize(Float64 dx,Float64 dy,ISize2d** ppSize)
{
   ATLASSERT( ppSize != 0 && (*ppSize) == 0 );

   CComObject<CSize2d>* pSize;
   HRESULT hr = CComObject<CSize2d>::CreateInstance(&pSize);
   if ( FAILED(hr) )
      return hr;

   pSize->AddRef();

   pSize->put_Dx( dx );
   pSize->put_Dy( dy );

   (*ppSize) = pSize;

   return S_OK;
}

HRESULT CreateSize(Float64 dx,Float64 dy,Float64 dz,ISize3d** ppSize)
{
   ATLASSERT( ppSize != 0 && (*ppSize) == 0 );

   CComObject<CSize3d>* pSize;
   HRESULT hr = CComObject<CSize3d>::CreateInstance(&pSize);
   if ( FAILED(hr) )
      return hr;

   pSize->AddRef();

   pSize->put_Dx( dx );
   pSize->put_Dy( dy );
   pSize->put_Dz( dz );

   (*ppSize) = pSize;

   return S_OK;
}

HRESULT CreateVector(IPoint2d* pSource,IVector2d** ppTarget)
{
   ATLASSERT( pSource != 0 && ppTarget != 0 && (*ppTarget) == 0);

   Float64 x,y;
   GetCoordinates(pSource,&x,&y);
   return CreateVector(x,y,ppTarget);
}

HRESULT CreateVector(Float64 x,Float64 y,IVector2d** ppVector)
{
   ATLASSERT( ppVector != 0 && (*ppVector) == 0);

   CComObject<CVector2d>* pVector;
   HRESULT hr = CComObject<CVector2d>::CreateInstance(&pVector);
   if ( FAILED(hr) )
      return hr;

   pVector->AddRef();

   pVector->put_X( x );
   pVector->put_Y( y );

   (*ppVector) = pVector;

   return S_OK;
}

HRESULT GetCoordinates(IVector2d* pSource,Float64* px,Float64 *py)
{
   ATLASSERT( pSource != 0 && px != 0 && py != 0 );
   pSource->get_X(px);
   pSource->get_Y(py);
   return S_OK;
}

///////////////////////////////////////////////////////////////////
// Vector3d Helpers
HRESULT CreateVector(IVector3d** ppVector)
{
   ATLASSERT( ppVector != 0 && (*ppVector) == 0);

   CComObject<CVector3d>* pVector;
   HRESULT hr = CComObject<CVector3d>::CreateInstance(&pVector);
   if ( FAILED(hr) )
      return hr;

   pVector->QueryInterface( ppVector );

   return S_OK;
}

HRESULT CreateVector(Float64 x,Float64 y,Float64 z,IVector3d** ppVector)
{
   ATLASSERT( ppVector != 0 && (*ppVector) == 0);

   HRESULT hr;
   hr = CreateVector(ppVector);
   if ( FAILED(hr) )
      return hr;

   (*ppVector)->put_X(x);
   (*ppVector)->put_Y(y);
   (*ppVector)->put_Z(z);

   return S_OK;
}

HRESULT CreateVector( IVector3d* pSource, IVector3d** ppTarget )
{
   ATLASSERT( pSource != 0 && ppTarget != 0 && (*ppTarget) == 0);

   HRESULT hr;

   Float64 x,y,z;
   hr = GetCoordinates(pSource,&x,&y,&z);
   if (FAILED(hr)) return hr;

   return CreateVector(x,y,z,ppTarget);
}

HRESULT CreateVector( IPoint3d* pSource, IVector3d** ppTarget )
{
   ATLASSERT( pSource != 0 && ppTarget != 0 && (*ppTarget) == 0);

   HRESULT hr;

   Float64 x,y,z;
   hr = GetCoordinates(pSource,&x,&y,&z);
   if (FAILED(hr)) return hr;

   return CreateVector(x,y,z,ppTarget);
}

HRESULT GetCoordinates(IVector3d* pVector,Float64* px,Float64* py,Float64* pz)
{
   ATLASSERT( pVector != 0 && px != 0 && py != 0 && pz != 0 );

   pVector->get_X(px);
   pVector->get_Y(py);
   pVector->get_Z(pz);

   return S_OK;
}

HRESULT Add(IVector3d* pResult,IVector3d* pA,IVector3d* pB)
{
   ATLASSERT( pResult != 0 && pA != 0 && pB != 0 );

   Float64 xa,ya,za;
   Float64 xb,yb,zb;

   GetCoordinates(pA,&xa,&ya,&za);
   GetCoordinates(pB,&xb,&yb,&zb);

   pResult->put_X(xa+xb);
   pResult->put_Y(ya+yb);
   pResult->put_Z(za+zb);

   return S_OK;
}

HRESULT Subtract(IVector3d* pResult,IVector3d* pA,IVector3d* pB)
{
   ATLASSERT( pResult != 0 && pA != 0 && pB != 0 );

   Float64 xa,ya,za;
   Float64 xb,yb,zb;

   GetCoordinates(pA,&xa,&ya,&za);
   GetCoordinates(pB,&xb,&yb,&zb);

   pResult->put_X(xa-xb);
   pResult->put_Y(ya-yb);
   pResult->put_Z(za-zb);

   return S_OK;
}

HRESULT CreatePointCollection(IPoint2dCollection** ppPoints)
{
   ATLASSERT( ppPoints != 0 && (*ppPoints) == 0 );

   CComObject<CPoint2dCollection>* pPoints;
   HRESULT hr = CComObject<CPoint2dCollection>::CreateInstance( &pPoints );
   if ( FAILED(hr) )
      return hr;

   pPoints->AddRef();
   (*ppPoints) = pPoints;

   return S_OK;
}

HRESULT CreateLine(ILineSegment2d* pSeg,ILine2dFactory* pFactory,ILine2d** ppLine)
{
   ATLASSERT( pSeg != 0 && ppLine != 0 && (*ppLine) == 0 );

   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;
   pSeg->get_StartPoint(&pStart);
   pSeg->get_EndPoint(&pEnd);

   return CreateLine(pStart,pEnd,pFactory,ppLine);
}

HRESULT CreateLine(ILine2d* pLine,ILine2dFactory* pFactory,ILine2d** ppLine)
{
   // Bad input
   ATLASSERT( pLine != 0 );

   // Create a new default line
   HRESULT hr = CreateLine(pFactory,ppLine);
   if ( FAILED(hr) )
      return hr;

   // Get the implicit format of the source line
   Float64 c;
   CComPtr<IVector2d> v;
   pLine->GetImplicit(&c,&v);

   // Copy the implicit format to the target line
   (*ppLine)->SetImplicit(c,v);

   return S_OK;
}

HRESULT CreateLine(ILine2dFactory* pFactory,ILine2d** ppLine)
{
   ATLASSERT( ppLine != 0 && (*ppLine) == 0 );

   HRESULT hr = S_OK;

   if ( pFactory == nullptr )
   {
      CComObject<CLine2d>* pLine;
      hr = CComObject<CLine2d>::CreateInstance(&pLine);
      if ( FAILED(hr) )
         return hr;

      pLine->QueryInterface(ppLine);
   }
   else
   {
      hr = pFactory->CreateLine(ppLine);
      if ( FAILED(hr) )
         return hr;
   }

   return S_OK;
}

HRESULT CreateLine(IPoint2d* pStart,IPoint2d* pEnd,ILine2dFactory* pFactory,ILine2d** ppLine)
{
   ATLASSERT( pStart != 0 && pEnd != 0 && ppLine != 0 && (*ppLine) == 0 );

   HRESULT hr = CreateLine(pFactory,ppLine);
   if ( FAILED(hr) )
      return hr;

   (*ppLine)->ThroughPoints(pStart,pEnd);

   return S_OK;
}

HRESULT CreateShapeProperties(IShapeProperties** ppProps)
{
   ATLASSERT( ppProps != 0 && (*ppProps) == 0 );

   CComObject<CShapeProperties>* pProps;
   HRESULT hr = CComObject<CShapeProperties>::CreateInstance(&pProps);
   if ( FAILED(hr) )
      return hr;

   pProps->QueryInterface(ppProps);

   return S_OK;
}

HRESULT CreatePolyShape(IPolyShape** ppPolyShape)
{
   ATLASSERT( ppPolyShape != 0 && (*ppPolyShape) == 0 );

   CComObject<CPolyShape>* pNewShape;
   HRESULT hr = CComObject<CPolyShape>::CreateInstance( &pNewShape );
   if ( FAILED(hr) )
      return hr;

   return pNewShape->QueryInterface( ppPolyShape );
}

HRESULT CreateCompositeShape(ICompositeShape** ppCompositeShape)
{
   ATLASSERT( ppCompositeShape != 0 && (*ppCompositeShape) == 0 );

   CComObject<CCompositeShape>* pNewShape;
   HRESULT hr = CComObject<CCompositeShape>::CreateInstance( &pNewShape );
   if ( FAILED(hr) )
      return hr;

   return pNewShape->QueryInterface( ppCompositeShape );
}

HRESULT CreatePolyShape(IPoint2dCollection* pPoints,IPolyShape** ppPolyShape)
{
   ATLASSERT( pPoints != 0 && ppPolyShape != 0 && (*ppPolyShape) == 0 );

   HRESULT hr;
   hr = CreatePolyShape( ppPolyShape );
   if ( FAILED(hr) )
      return hr;

   CollectionIndexType cPoints;
   pPoints->get_Count(&cPoints);
   for ( CollectionIndexType i = 0; i < cPoints; i++ )
   {
      CComPtr<IPoint2d> pPoint;
      pPoints->get_Item(i,&pPoint);
/*
      CComVariant varPoint;
      pPoints->get_Item(i,&varPoint);

      CComPtr<IPoint2d> pPoint;
      ATLASSERT( varPoint.vt == VT_DISPATCH );
      varPoint.pdispVal->QueryInterface( &pPoint );
*/
      (*ppPolyShape)->AddPointEx( pPoint );
   }

   return S_OK;
}

HRESULT CreateGeomUtil(IGeomUtil2d** ppUtil)
{
   ATLASSERT( ppUtil != 0 && (*ppUtil) == 0);

   CComObject<CGeomUtil>* pUtil;
   HRESULT hr = CComObject<CGeomUtil>::CreateInstance( &pUtil );
   if ( FAILED(hr) )
      return hr;

   pUtil->QueryInterface( ppUtil );
   return S_OK;
}

HRESULT CreateGeomUtil(IGeomUtil3d** ppUtil)
{
   CComPtr<IGeomUtil2d> pUtil2d;
   HRESULT hr = CreateGeomUtil(&pUtil2d);
   if ( FAILED(hr) )
      return hr;

   return pUtil2d->QueryInterface(ppUtil);
}


VARIANT_BOOL MakeBool(bool boolean)
{
   return boolean ? VARIANT_TRUE : VARIANT_FALSE;
}

Float64 NormalizeAngle(Float64 angle)
{
   while ( angle < 0 )
      angle += TWO_PI;

   while ( angle >= TWO_PI )
      angle -= TWO_PI;

   ATLASSERT( InRange(0.0,angle,TWO_PI) );

   angle = IsZero(angle) ? 0 : angle;
   angle = IsEqual(angle,TWO_PI) ? TWO_PI : angle;

   return angle;
}

bool IsEqualPoint(IPoint2d* p1,IPoint2d* p2)
{
   ATLASSERT( p1 != 0 && p2 != 0 );

   Float64 x1,y1;
   GetCoordinates(p1,&x1,&y1);

   Float64 x2,y2;
   GetCoordinates(p2,&x2,&y2);

   return IsEqual(x1,x2) && IsEqual(y1,y2);
}

bool IsEqualVector(IVector2d* v1,IVector2d* v2)
{
   ATLASSERT( v1 != 0 && v2 != 0 );

   Float64 x1,y1;
   GetCoordinates(v1,&x1,&y1);

   Float64 x2,y2;
   GetCoordinates(v2,&x2,&y2);

   return IsEqual(x1,x2) && IsEqual(y1,y2);
}

HRESULT CreateLineSegment(ILineSegment2dFactory* pFactory,ILineSegment2d** ppSeg)
{
   ATLASSERT( ppSeg != 0 && (*ppSeg) == 0 );

   HRESULT hr = S_OK;

   if ( pFactory == nullptr )
   {
      CComObject<CLineSegment2d>* pSeg;
      hr = CComObject<CLineSegment2d>::CreateInstance(&pSeg);
      if ( FAILED(hr) )
         return hr;

      pSeg->QueryInterface(ppSeg);
   }
   else
   {
      hr = pFactory->CreateLineSegment(ppSeg);
      if ( FAILED(hr) )
         return hr;
   }

   return S_OK;
}


void ProjectPointAlongLine(Float64 P1_x, Float64 P1_y, Float64 P2_x, Float64 P2_y, Float64 Offset, 
                           Float64* pP_x, Float64* pP_y)
{
   // points must not be coincident
   Float64 pdx =  P2_x-P1_x;
   Float64 pdy =  P2_y-P1_y;

   ATLASSERT(pdx>0.0 || pdy>0.0); 

   if (Offset == 0.0 || pdx==0.0 && pdy==0.0)
   {
      *pP_x = P1_x;
      *pP_y = P1_y;
   }
   else
   {
      Float64 angle;
      if (pdx != 0.0)
      {
         angle = atan2(pdy, pdx);
      }
      else
      {
         angle = pdy>0.0 ? PI_OVER_2 : -PI_OVER_2;
      }

      *pP_x = P1_x + Offset * cos(angle);
      *pP_y = P1_y + Offset * sin(angle);
   }
}


//
// Thes methods are not used. They have not been tested.
//

//HRESULT CopyPoint(IPoint3d* pTo,IPoint3d* pFrom)
//{
//   ATLASSERT( pTo != 0 && pFrom != 0 );
//
//   Float64 x,y,z;
//   GetCoordinates(pFrom,&x,&y,&z);
//   PutCoordinates(x,y,z,pTo);
//
//   return S_OK;
//}
//
//HRESULT CopyVector(IVector3d* pTarget,IVector3d* pSource)
//{
//   ATLASSERT( pTarget != 0 && pSource != 0 );
//   Float64 x,y,z;
//   GetCoordinates(pSource,&x,&y,&z);
//   pTarget->put_X(x);
//   pTarget->put_Y(y);
//   pTarget->put_Z(z);
//
//   return S_OK;
//}
//
//bool MakeBool(VARIANT_BOOL boolean)
//{
//   return (boolean == VARIANT_TRUE) ? true : false;
//}
