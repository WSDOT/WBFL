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
#include "CompositeShapeItem.h"
#include "GenericShape.h"
#include "Circle.h"
#include "CircularSegment.h"

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

std::shared_ptr<WBFL::Geometry::Point2d> GetInnerPoint(IPoint2d* pPoint)
{
   CPoint2d* p = dynamic_cast<CPoint2d*>(pPoint);
   ATLASSERT(p);
   return p->GetPoint();
}

std::shared_ptr<WBFL::Geometry::Point3d> GetInnerPoint(IPoint3d* pPoint)
{
   CPoint3d* p = dynamic_cast<CPoint3d*>(pPoint);
   ATLASSERT(p);
   return p->GetPoint();
}

WBFL::Geometry::Point3d GetPoint(IPoint3d* pPoint)
{
   Float64 x, y, z;
   pPoint->Location(&x, &y, &z);
   return WBFL::Geometry::Point3d(x, y, z);
}

WBFL::Geometry::Vector3d GetVector(IVector3d* pVector)
{
   Float64 dx, dy, dz;
   pVector->get_X(&dx);
   pVector->get_Y(&dy);
   pVector->get_Z(&dz);
   return WBFL::Geometry::Vector3d(dx, dy, dz);
}

WBFL::Geometry::Point2d GetPoint(IPoint2d* pPoint)
{
   Float64 x, y; pPoint->Location(&x, &y);
   return WBFL::Geometry::Point2d(x, y);
}

WBFL::Geometry::Line2d GetLine(ILine2d* pLine)
{
   Float64 c;
   CComPtr<IVector2d> n;
   pLine->GetImplicit(&c, &n);

   Float64 nx, ny;
   n->get_X(&nx); n->get_Y(&ny);

   return WBFL::Geometry::Line2d(c, WBFL::Geometry::Vector2d(WBFL::Geometry::Size2d(nx, ny)));
}

WBFL::Geometry::LineSegment2d GetLineSegment(ILineSegment2d* pLineSegment)
{
   CComPtr<IPoint2d> pStart, pEnd;
   pLineSegment->get_StartPoint(&pStart);
   pLineSegment->get_EndPoint(&pEnd);
   return WBFL::Geometry::LineSegment2d(GetPoint(pStart), GetPoint(pEnd));
}

WBFL::Geometry::Rect2d GetRect(IRect2d* pRect)
{
   Float64 left, right, top, bottom;
   pRect->get_Left(&left);
   pRect->get_Right(&right);
   pRect->get_Top(&top);
   pRect->get_Bottom(&bottom);

   return WBFL::Geometry::Rect2d(left, bottom, right, top);
}

WBFL::Geometry::Size2d GetSize(ISize2d* pSize)
{
   Float64 dx, dy;
   pSize->Dimensions(&dx, &dy);
   return WBFL::Geometry::Size2d(dx, dy);
}

WBFL::Geometry::Vector2d GetVector(IVector2d* pVector)
{
   Float64 x, y;
   pVector->get_X(&x);
   pVector->get_Y(&y);
   return WBFL::Geometry::Vector2d(WBFL::Geometry::Size2d(x, y));
}

WBFL::Geometry::Circle GetCircle(ICircle* pCircle)
{
   CComPtr<IPoint2d> center;
   pCircle->get_Center(&center);
   Float64 radius;
   pCircle->get_Radius(&radius);

   return WBFL::Geometry::Circle(GetPoint(center), radius);
}

WBFL::Geometry::Circle2d GetCircle2d(ICircle* pCircle)
{
   CComPtr<IPoint2d> center;
   pCircle->get_Center(&center);
   Float64 radius;
   pCircle->get_Radius(&radius);

   return WBFL::Geometry::Circle2d(GetPoint(center), radius);
}

HRESULT CopyPoint(IPoint2d* pTo,IPoint2d* pFrom)
{
   ATLASSERT(pTo != nullptr && pFrom != nullptr);

   Float64 x,y;
   GetCoordinates(pFrom,&x,&y);
   PutCoordinates(x,y,pTo);

   return S_OK;
}

HRESULT CopyLineSegment(ILineSegment2d* pTo,ILineSegment2d* pFrom)
{
   ATLASSERT( pTo != nullptr && pFrom != nullptr );
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

   pTo->ThroughPoints(pStartTo, pEndTo);

   return S_OK;
}

HRESULT CopyPoints(IPoint2dCollection* pTo,IPoint2dCollection* pFrom)
{
   ATLASSERT( pTo != nullptr && pFrom != nullptr );

   pTo->Clear();

   IndexType cPoint;
   pFrom->get_Count(&cPoint);
   for ( IndexType idx = 0; idx < cPoint; idx++ )
   {
      CComPtr<IPoint2d> pPoint;
      pFrom->get_Item(idx,&pPoint);

      CComPtr<IPoint2d> pNewPoint;
      CreatePoint(pPoint,&pNewPoint);

      pTo->Add(pNewPoint);
   }

   return S_OK;
}

HRESULT CreatePointCollection(IPoint2dCollection** ppPoints,IPoint2dCollection* pCopyFrom)
{
   ATLASSERT( ppPoints != nullptr && (*ppPoints) == nullptr );

   CComObject<CPoint2dCollection>* pPoints;
   HRESULT hr = CComObject<CPoint2dCollection>::CreateInstance( &pPoints );
   if ( FAILED(hr) )
      return hr;

   pPoints->AddRef();
   (*ppPoints) = pPoints;

   CopyPoints(*ppPoints,pCopyFrom);

   return S_OK;
}

std::vector<WBFL::Geometry::Point2d> CreatePointCollection(IPoint2dCollection* pPoints)
{
   std::vector<WBFL::Geometry::Point2d> vPoints;
   IndexType nPoints;
   pPoints->get_Count(&nPoints);
   for (IndexType i = 0; i < nPoints; i++)
   {
      CComPtr<IPoint2d> p;
      pPoints->get_Item(i, &p);
      Float64 x, y;
      p->Location(&x, &y);
      vPoints.push_back({ x,y });
   }
   return vPoints;
}


HRESULT GetCoordinates(IPoint2d* pPoint,Float64* px,Float64* py)
{
   ATLASSERT(pPoint != nullptr && px != nullptr && py != nullptr);

   HRESULT hr = pPoint->Location(px,py);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

HRESULT GetCoordinates(IPoint3d* pPoint,Float64* px,Float64* py,Float64* pz)
{
   ATLASSERT(pPoint != nullptr && px != nullptr && py != nullptr && pz != nullptr);

   HRESULT hr = pPoint->Location(px,py,pz);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

HRESULT PutCoordinates(Float64 x,Float64 y,IPoint2d* pPoint)
{
   ATLASSERT(pPoint != nullptr );

   pPoint->Move(x,y);

   return S_OK;
}

HRESULT PutCoordinates(Float64 x,Float64 y,Float64 z,IPoint3d* pPoint)
{
   ATLASSERT(pPoint != nullptr );

   pPoint->Move(x,y,z);

   return S_OK;
}

HRESULT GetSize(ISize2d* pSize,Float64* pdx,Float64* pdy)
{
   ATLASSERT( pSize != nullptr && pdx != nullptr && pdy != nullptr );
   return pSize->Dimensions(pdx, pdy);
}

HRESULT GetRect(IRect2d* rect,Float64 *left,Float64 *top,Float64 *right,Float64 *bottom)
{
   ATLASSERT( rect != nullptr && left != nullptr && top != nullptr && right != nullptr && bottom != nullptr);
   rect->get_Left(left);
   rect->get_Right(right);
   rect->get_Top(top);
   rect->get_Bottom(bottom);
   return S_OK;
}

HRESULT CreatePoint(const WBFL::Geometry::Point2d& point, IPoint2d** ppPoint)
{
   return CreatePoint(point.X(), point.Y(), ppPoint);
}

HRESULT CreatePoint(std::shared_ptr<WBFL::Geometry::Point2d>& point, IPoint2d** ppPoint)
{
   CComObject<CPoint2d>* pPoint;
   CComObject<CPoint2d>::CreateInstance(&pPoint);
   pPoint->SetPoint(point);
   (*ppPoint) = pPoint;
   (*ppPoint)->AddRef();
   return S_OK;
}

HRESULT CreatePoint(IPoint2d* pPoint,IPoint2d** ppPoint)
{
   ATLASSERT( pPoint != nullptr && ppPoint != nullptr && (*ppPoint) == nullptr );

   Float64 x,y;
   pPoint->Location(&x,&y);

   return CreatePoint(x,y,ppPoint);
}

HRESULT CreatePoint(Float64 x,Float64 y,IPoint2d** ppPoint)
{
   ATLASSERT( ppPoint != nullptr && (*ppPoint) == nullptr );

   CComObject<CPoint2d>* pPoint;
   HRESULT hr = CComObject<CPoint2d>::CreateInstance(&pPoint);
   if ( FAILED(hr) )
      return hr;

   pPoint->AddRef();
   (*ppPoint) = pPoint;

   (*ppPoint)->Move(x,y);

   return S_OK;
}

HRESULT CreatePoint(const WBFL::Geometry::Point3d& point, IPoint3d** ppPoint)
{
   return CreatePoint(point.X(), point.Y(), point.Z(), ppPoint);
}

HRESULT CreatePoint(std::shared_ptr<WBFL::Geometry::Point3d>& point, IPoint3d** ppPoint)
{
   CComObject<CPoint3d>* pPoint;
   CComObject<CPoint3d>::CreateInstance(&pPoint);
   pPoint->SetPoint(point);
   (*ppPoint) = pPoint;
   (*ppPoint)->AddRef();
   return S_OK;
}

HRESULT CreatePoint(IPoint3d* pPoint,IPoint3d** ppPoint)
{
   ATLASSERT( pPoint != nullptr && ppPoint != nullptr && (*ppPoint == nullptr) );

   Float64 x,y,z;
   pPoint->Location(&x,&y,&z);

   return CreatePoint(x,y,z,ppPoint);
}

HRESULT CreatePoint(Float64 x,Float64 y,Float64 z,IPoint3d** ppPoint)
{
   ATLASSERT( ppPoint != nullptr && (*ppPoint == nullptr) );

   CComObject<CPoint3d>* pPoint;
   HRESULT hr = CComObject<CPoint3d>::CreateInstance(&pPoint);
   if ( FAILED(hr) )
      return hr;

   pPoint->AddRef();
   (*ppPoint) = pPoint;

   (*ppPoint)->Move(x,y,z);

   return S_OK;
}

HRESULT CreateRect(const WBFL::Geometry::Rect2d& rect, IRect2d** ppRect)
{
   return CreateRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), ppRect);
}

HRESULT CreateRect(Float64 left,Float64 top,Float64 right,Float64 bottom,IRect2d** ppRect)
{
   ATLASSERT( ppRect != nullptr && (*ppRect) == nullptr );

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

HRESULT CreateSize(const WBFL::Geometry::Size2d& size, ISize2d** ppSize)
{
   return CreateSize(size.Dx(), size.Dy(), ppSize);
}

HRESULT CreateSize(Float64 dx,Float64 dy,ISize2d** ppSize)
{
   ATLASSERT( ppSize != nullptr && (*ppSize) == nullptr );

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

HRESULT CreateSize(const WBFL::Geometry::Size3d& size, ISize3d** ppSize)
{
   return CreateSize(size.Dx(), size.Dy(), size.Dz(), ppSize);
}

HRESULT CreateSize(Float64 dx,Float64 dy,Float64 dz,ISize3d** ppSize)
{
   ATLASSERT( ppSize != nullptr && (*ppSize) == nullptr );

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
   ATLASSERT( pSource != nullptr && ppTarget != nullptr && (*ppTarget) == nullptr);

   Float64 x,y;
   GetCoordinates(pSource,&x,&y);
   return CreateVector(x,y,ppTarget);
}

HRESULT CreateVector(const WBFL::Geometry::Vector2d& source, IVector2d** ppVector)
{
   return CreateVector(source.X(), source.Y(), ppVector);
}

HRESULT CreateVector(Float64 x,Float64 y,IVector2d** ppVector)
{
   ATLASSERT( ppVector != nullptr && (*ppVector) == nullptr);

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
   ATLASSERT( pSource != nullptr && px != nullptr && py != nullptr );
   pSource->get_X(px);
   pSource->get_Y(py);
   return S_OK;
}

///////////////////////////////////////////////////////////////////
// Vector3d Helpers
HRESULT CreateVector(IVector3d** ppVector)
{
   ATLASSERT( ppVector != nullptr && (*ppVector) == nullptr);

   CComObject<CVector3d>* pVector;
   HRESULT hr = CComObject<CVector3d>::CreateInstance(&pVector);
   if ( FAILED(hr) )
      return hr;

   pVector->QueryInterface( ppVector );

   return S_OK;
}

HRESULT CreateVector(Float64 x,Float64 y,Float64 z,IVector3d** ppVector)
{
   ATLASSERT( ppVector != nullptr && (*ppVector) == nullptr);

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
   ATLASSERT( pSource != nullptr && ppTarget != nullptr && (*ppTarget) == nullptr);

   HRESULT hr;

   Float64 x,y,z;
   hr = GetCoordinates(pSource,&x,&y,&z);
   if (FAILED(hr)) return hr;

   return CreateVector(x,y,z,ppTarget);
}

HRESULT CreateVector( IPoint3d* pSource, IVector3d** ppTarget )
{
   ATLASSERT( pSource != nullptr && ppTarget != nullptr && (*ppTarget) == nullptr);

   HRESULT hr;

   Float64 x,y,z;
   hr = GetCoordinates(pSource,&x,&y,&z);
   if (FAILED(hr)) return hr;

   return CreateVector(x,y,z,ppTarget);
}

HRESULT CreateVector(const WBFL::Geometry::Vector3d& source, IVector3d** ppTarget)
{
   return CreateVector(source.X(), source.Y(), source.Z(), ppTarget);
}

HRESULT GetCoordinates(IVector3d* pVector,Float64* px,Float64* py,Float64* pz)
{
   ATLASSERT( pVector != nullptr && px != nullptr && py != nullptr && pz != nullptr );

   pVector->get_X(px);
   pVector->get_Y(py);
   pVector->get_Z(pz);

   return S_OK;
}

HRESULT Add(IVector3d* pResult,IVector3d* pA,IVector3d* pB)
{
   ATLASSERT( pResult != nullptr && pA != nullptr && pB != nullptr );

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
   ATLASSERT( pResult != nullptr && pA != nullptr && pB != nullptr );

   Float64 xa,ya,za;
   Float64 xb,yb,zb;

   GetCoordinates(pA,&xa,&ya,&za);
   GetCoordinates(pB,&xb,&yb,&zb);

   pResult->put_X(xa-xb);
   pResult->put_Y(ya-yb);
   pResult->put_Z(za-zb);

   return S_OK;
}

HRESULT CreatePointCollection(const std::vector<WBFL::Geometry::Point2d>& vPoints, IPoint2dCollection** ppPoints)
{
   ATLASSERT(ppPoints != nullptr && (*ppPoints) == nullptr);

   CComObject<CPoint2dCollection>* pPoints;
   HRESULT hr = CComObject<CPoint2dCollection>::CreateInstance(&pPoints);
   if (FAILED(hr))
      return hr;

   std::for_each(std::cbegin(vPoints), std::cend(vPoints),
      [&](const auto& point)
      {
         CComPtr<IPoint2d> pPoint;
         CreatePoint(point, &pPoint);
         pPoints->Add(pPoint);
      }
   );

   pPoints->AddRef();
   (*ppPoints) = pPoints;

   return S_OK;
}

HRESULT CreatePointCollection(IPoint2dCollection** ppPoints)
{
   ATLASSERT( ppPoints != nullptr && (*ppPoints) == nullptr );

   CComObject<CPoint2dCollection>* pPoints;
   HRESULT hr = CComObject<CPoint2dCollection>::CreateInstance( &pPoints );
   if ( FAILED(hr) )
      return hr;

   pPoints->AddRef();
   (*ppPoints) = pPoints;

   return S_OK;
}

HRESULT CreateLine(ILineSegment2d* pSeg,ILine2d** ppLine)
{
   ATLASSERT( pSeg != nullptr && ppLine != nullptr && (*ppLine) == nullptr );

   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;
   pSeg->get_StartPoint(&pStart);
   pSeg->get_EndPoint(&pEnd);

   return CreateLine(pStart,pEnd,ppLine);
}

HRESULT CreateLine(ILine2d* pLine,ILine2d** ppLine)
{
   // Bad input
   ATLASSERT( pLine != nullptr );

   // Create a new default line
   HRESULT hr = CreateLine(ppLine);
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

HRESULT CreateLine(ILine2d** ppLine)
{
   ATLASSERT( ppLine != nullptr && (*ppLine) == nullptr );

   HRESULT hr = S_OK;

   CComObject<CLine2d>* pLine;
   hr = CComObject<CLine2d>::CreateInstance(&pLine);
   if ( FAILED(hr) )
      return hr;

   pLine->QueryInterface(ppLine);

   return S_OK;
}

HRESULT CreateLine(IPoint2d* pStart,IPoint2d* pEnd,ILine2d** ppLine)
{
   ATLASSERT( pStart != nullptr && pEnd != nullptr && ppLine != nullptr && (*ppLine) == nullptr );

   HRESULT hr = CreateLine(ppLine);
   if ( FAILED(hr) )
      return hr;

   (*ppLine)->ThroughPoints(pStart,pEnd);

   return S_OK;
}

HRESULT CreateShapeProperties(const WBFL::Geometry::ShapeProperties& props, IShapeProperties** ppProps)
{
   ATLASSERT(ppProps != nullptr && (*ppProps) == nullptr);

   CComObject<CShapeProperties>* pProps;
   HRESULT hr = CComObject<CShapeProperties>::CreateInstance(&pProps);
   if (FAILED(hr))
      return hr;

   pProps->SetProperties(props);

   pProps->QueryInterface(ppProps);

   return S_OK;
}

HRESULT CreateShapeProperties(IShapeProperties** ppProps)
{
   ATLASSERT( ppProps != nullptr && (*ppProps) == nullptr );

   CComObject<CShapeProperties>* pProps;
   HRESULT hr = CComObject<CShapeProperties>::CreateInstance(&pProps);
   if ( FAILED(hr) )
      return hr;

   pProps->QueryInterface(ppProps);

   return S_OK;
}

//HRESULT CreatePolyShape(IPolyShape** ppPolyShape)
//{
//   ATLASSERT( ppPolyShape != nullptr && (*ppPolyShape) == nullptr );
//
//   CComObject<CPolyShape>* pNewShape;
//   HRESULT hr = CComObject<CPolyShape>::CreateInstance( &pNewShape );
//   if ( FAILED(hr) )
//      return hr;
//
//   return pNewShape->QueryInterface( ppPolyShape );
//}

HRESULT CreateCompositeShape(ICompositeShape** ppCompositeShape)
{
   ATLASSERT( ppCompositeShape != nullptr && (*ppCompositeShape) == nullptr );

   CComObject<CCompositeShape>* pNewShape;
   HRESULT hr = CComObject<CCompositeShape>::CreateInstance( &pNewShape );
   if ( FAILED(hr) )
      return hr;

   return pNewShape->QueryInterface( ppCompositeShape );
}

HRESULT CreateGenericShape(const WBFL::Geometry::Shape* shape, IGenericShape** ppGenericShape)
{
   ATLASSERT(ppGenericShape != nullptr && (*ppGenericShape) == nullptr);

   *ppGenericShape = nullptr;
   if (shape == nullptr) return E_INVALIDARG;

   CComObject<CGenericShape>* pGenericShape;
   HRESULT hr = CComObject<CGenericShape>::CreateInstance(&pGenericShape);
   if (FAILED(hr)) return hr;

   const auto* generic_shape(dynamic_cast<const WBFL::Geometry::GenericShape*>(shape));
   pGenericShape->SetShape(*generic_shape);
   return pGenericShape->QueryInterface(ppGenericShape);
}

HRESULT CreateCircle(const WBFL::Geometry::Shape* shape, ICircle** ppCircle)
{
   ATLASSERT(ppCircle != nullptr && (*ppCircle) == nullptr);

   *ppCircle = nullptr;
   if (shape == nullptr) return E_INVALIDARG;

   CComObject<CCircle>* pCircle;
   HRESULT hr = CComObject<CCircle>::CreateInstance(&pCircle);
   if (FAILED(hr)) return hr;

   const auto* circle(dynamic_cast<const WBFL::Geometry::Circle*>(shape));
   pCircle->SetShape(*circle);
   return pCircle->QueryInterface(ppCircle);
}

HRESULT CreateCircularSegment(const WBFL::Geometry::Shape* shape, ICircularSegment** ppCircularSegment)
{
   ATLASSERT(ppCircularSegment != nullptr && (*ppCircularSegment) == nullptr);

   *ppCircularSegment = nullptr;
   if (shape == nullptr) return E_INVALIDARG;

   CComObject<CCircularSegment>* pCircularSegment;
   HRESULT hr = CComObject<CCircularSegment>::CreateInstance(&pCircularSegment);
   if (FAILED(hr)) return hr;

   const auto* circular_segment(dynamic_cast<const WBFL::Geometry::CircularSegment*>(shape));
   pCircularSegment->SetShape(*circular_segment);
   return pCircularSegment->QueryInterface(ppCircularSegment);
}

HRESULT CreatePolyShape(const WBFL::Geometry::Shape* shape, IPolyShape** ppPolyShape)
{
   ATLASSERT(ppPolyShape != nullptr && (*ppPolyShape) == nullptr);
   if (shape == nullptr) return E_INVALIDARG;

   CComObject<CPolyShape>* pNewShape;
   HRESULT hr = CComObject<CPolyShape>::CreateInstance(&pNewShape);
   if (FAILED(hr)) return hr;

   WBFL::Geometry::Polygon polygon;
   polygon.SetPoints(shape->GetPolyPoints());
   pNewShape->SetPolygon(polygon);

   return pNewShape->QueryInterface(ppPolyShape);
}

HRESULT CreateGeomUtil(IGeomUtil2d** ppUtil)
{
   ATLASSERT( ppUtil != nullptr && (*ppUtil) == nullptr);

   CComObject<CGeomUtil>* pUtil;
   HRESULT hr = CComObject<CGeomUtil>::CreateInstance( &pUtil );
   if ( FAILED(hr) )
      return hr;

   pUtil->QueryInterface( ppUtil );
   return S_OK;
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
   ATLASSERT( p1 != nullptr && p2 != nullptr );

   Float64 x1,y1;
   GetCoordinates(p1,&x1,&y1);

   Float64 x2,y2;
   GetCoordinates(p2,&x2,&y2);

   return IsEqual(x1,x2) && IsEqual(y1,y2);
}

bool IsEqualVector(IVector2d* v1,IVector2d* v2)
{
   ATLASSERT( v1 != nullptr && v2 != nullptr );

   Float64 x1,y1;
   GetCoordinates(v1,&x1,&y1);

   Float64 x2,y2;
   GetCoordinates(v2,&x2,&y2);

   return IsEqual(x1,x2) && IsEqual(y1,y2);
}

HRESULT CreateLineSegment(const WBFL::Geometry::LineSegment2d& ls, ILineSegment2d** ppSeg)
{
   ATLASSERT(ppSeg != nullptr && (*ppSeg) == nullptr);

   CComObject<CLineSegment2d>* pSeg;
   HRESULT hr = CComObject<CLineSegment2d>::CreateInstance(&pSeg);
   if (FAILED(hr))
      return hr;

   pSeg->SetLineSegment(ls);
   return pSeg->QueryInterface(ppSeg);
}

HRESULT CreateLine(const WBFL::Geometry::Line2d& line, ILine2d** ppLine)
{
   ATLASSERT(ppLine != nullptr && (*ppLine) == nullptr);
   CComObject<CLine2d>* pLine;
   HRESULT hr = CComObject<CLine2d>::CreateInstance(&pLine);
   if (FAILED(hr)) return hr;
   pLine->SetLine(line);
   return pLine->QueryInterface(ppLine);
}

HRESULT CreateLineSegment(ILineSegment2d** ppSeg)
{
   ATLASSERT( ppSeg != nullptr && (*ppSeg) == nullptr );

   HRESULT hr = S_OK;

   CComObject<CLineSegment2d>* pSeg;
   hr = CComObject<CLineSegment2d>::CreateInstance(&pSeg);
   if ( FAILED(hr) )
      return hr;

   pSeg->QueryInterface(ppSeg);

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

HRESULT ConvertShape(const WBFL::Geometry::Shape* pShape, IShape** ppShape)
{
   if (dynamic_cast<const WBFL::Geometry::GenericShape*>(pShape))
   {
      CComPtr<IGenericShape> generic_shape;
      HRESULT hr = ::CreateGenericShape(pShape, &generic_shape);
      if (FAILED(hr)) return hr;
      generic_shape->get_Shape(ppShape);
   }
   else if (dynamic_cast<const WBFL::Geometry::Circle*>(pShape))
   {
      CComPtr<ICircle> circle;
      HRESULT hr = ::CreateCircle(pShape, &circle);
      if (FAILED(hr)) return hr;
      circle->get_Shape(ppShape);
   }
   else if (dynamic_cast<const WBFL::Geometry::CircularSegment*>(pShape))
   {
      CComPtr<ICircularSegment> circular_segment;
      HRESULT hr = ::CreateCircularSegment(pShape, &circular_segment);
      if (FAILED(hr)) return hr;
      circular_segment->get_Shape(ppShape);
   }
   else if (dynamic_cast<const WBFL::Geometry::CompositeShape*>(pShape))
   {
      CComPtr<ICompositeShape> composite_shape;
      CreateCompositeShape(&composite_shape);

      const WBFL::Geometry::CompositeShape* pCompositeShape = dynamic_cast<const WBFL::Geometry::CompositeShape*>(pShape);
      IndexType nShapes = pCompositeShape->GetShapeCount();
      for (IndexType i = 0; i < nShapes; i++)
      {
         auto shape = pCompositeShape->GetShape(i);
         CComPtr<IShape> converted_shape;
         ConvertShape(shape.get(), &converted_shape);
         composite_shape->AddShape(converted_shape, pCompositeShape->GetShapeType(i) == WBFL::Geometry::CompositeShape::ShapeType::Void ? VARIANT_TRUE : VARIANT_FALSE);
      }

      composite_shape->get_Shape(ppShape);
   }
   else
   {
      CComPtr<IPolyShape> polyShape;
      HRESULT hr = ::CreatePolyShape(pShape, &polyShape);
      if (FAILED(hr))  return hr;
      polyShape->get_Shape(ppShape);
   }
   return S_OK;
}

std::shared_ptr<WBFL::Geometry::Shape> ConvertShape(IShape* pShape)
{
   std::shared_ptr<WBFL::Geometry::Shape> shape;

   CComQIPtr<ICompositeShape> cshape(pShape);
   if (cshape)
   {
      std::shared_ptr<WBFL::Geometry::CompositeShape> composite_shape = std::make_shared<WBFL::Geometry::CompositeShape>();
      IndexType nShapes;
      cshape->get_Count(&nShapes);
      for (IndexType i = 0; i < nShapes; i++)
      {
         CComPtr<ICompositeShapeItem> item;
         cshape->get_Item(i, &item);
         VARIANT_BOOL bVoid;
         item->get_Void(&bVoid);
         CComPtr<IShape> s;
         item->get_Shape(&s);

         auto converted_shape = ConvertShape(s);
         composite_shape->AddShape(converted_shape, bVoid == VARIANT_TRUE ? WBFL::Geometry::CompositeShape::ShapeType::Void : WBFL::Geometry::CompositeShape::ShapeType::Solid);
      }
      shape = composite_shape;
   }
   else
   {
      CComPtr<IPoint2dCollection> points;
      pShape->get_PolyPoints(&points);

      auto polygon = std::make_shared<WBFL::Geometry::Polygon>();
      polygon->AddPoints(CreatePointCollection(points));
      shape = polygon;
   }

   return shape;
}
