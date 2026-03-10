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
#pragma once

interface IPoint2d;
interface IPoint3d;
interface ISize2d;
interface ISize3d;
interface IRect2d;
interface IVector2d;
interface IVector3d;
interface IPoint2dCollection;
interface IPoint3dCollection;
interface ILineSegment2d;
interface ILine2d;
interface IShapeProperties;
interface IPolyShape;

#include <GeomModel/GenericShape.h>
#include <GeomModel/Circle.h>
#include <GeomModel/Circle2d.h>
#include <GeomModel/CircularSegment.h>
#include <GeomModel/CompositeShape.h>

// Forward declarations
namespace WBFL
{
   namespace Geometry
   {
      class Size2d;
      class Point2d;
      class Rect2d;
      class Vector2d;
      class Size3d;
      class Point3d;
      class Vector3d;

      class Line2d;
      class LineSegment2d;
      class Polygon;
      class Shape;
      class ShapeProperties;

      class GenericShape;
   };
};


std::shared_ptr<WBFL::Geometry::Point2d> GetInnerPoint(IPoint2d* pPoint);
std::shared_ptr<WBFL::Geometry::Point3d> GetInnerPoint(IPoint3d* pPoint);

WBFL::Geometry::Point2d GetPoint(IPoint2d* pPoint);
WBFL::Geometry::Line2d GetLine(ILine2d* pLine);
WBFL::Geometry::LineSegment2d GetLineSegment(ILineSegment2d* pLineSegment);
WBFL::Geometry::Rect2d GetRect(IRect2d* pRect);
WBFL::Geometry::Size2d GetSize(ISize2d* pSize);
WBFL::Geometry::Vector2d GetVector(IVector2d* pVector);
WBFL::Geometry::Circle GetCircle(ICircle* pCircle);
WBFL::Geometry::Circle2d GetCircle2d(ICircle* pCircle);

WBFL::Geometry::Point3d GetPoint(IPoint3d* pPoint);
WBFL::Geometry::Vector3d GetVector(IVector3d* pVector);

HRESULT CopyPoint(IPoint2d* pTo,IPoint2d* pFrom);
HRESULT CopyPoints(IPoint2dCollection* pTo,IPoint2dCollection* pFrom);
HRESULT CopyLineSegment(ILineSegment2d* pTo,ILineSegment2d* pFrom);
HRESULT GetCoordinates(IPoint2d* pPoint,Float64* px,Float64* py);
HRESULT GetCoordinates(IPoint3d* pPoint,Float64* px,Float64* py,Float64* pz);
HRESULT PutCoordinates(Float64 x,Float64 y,IPoint2d* pPoint);
HRESULT PutCoordinates(Float64 x,Float64 y,Float64 z,IPoint3d* pPoint);
HRESULT GetSize(ISize2d* pSize,Float64* pdx,Float64* pdy);
HRESULT GetRect(IRect2d* rect,Float64 *left,Float64 *top,Float64 *right,Float64 *bottom);

HRESULT CreatePoint(const WBFL::Geometry::Point2d& point, IPoint2d** ppPoint);
HRESULT CreatePoint(std::shared_ptr<WBFL::Geometry::Point2d>& point, IPoint2d** ppPoint);
HRESULT CreatePoint(IPoint2d* pPoint,IPoint2d** ppPoint);
HRESULT CreatePoint(Float64 x,Float64 y,IPoint2d** ppPoint);

HRESULT CreatePoint(const WBFL::Geometry::Point3d& point, IPoint3d** ppPoint);
HRESULT CreatePoint(std::shared_ptr<WBFL::Geometry::Point3d>& point, IPoint3d** ppPoint);
HRESULT CreatePoint(IPoint3d* pPoint,IPoint3d** ppPoint);
HRESULT CreatePoint(Float64 x,Float64 y,Float64 z,IPoint3d** ppPoint);

HRESULT CreateRect(Float64 left, Float64 top, Float64 right, Float64 bottom, IRect2d** ppRect);
HRESULT CreateRect(const WBFL::Geometry::Rect2d& rect, IRect2d** ppRect);

HRESULT CreateSize(Float64 dx,Float64 dy,ISize2d** ppSize);
HRESULT CreateSize(const WBFL::Geometry::Size2d& size, ISize2d** ppSize);
HRESULT CreateSize(Float64 dx,Float64 dy,Float64 dz,ISize3d** ppSize);
HRESULT CreateSize(const WBFL::Geometry::Size3d& size, ISize3d** ppSize);

HRESULT CreateVector(Float64 x,Float64 y,IVector2d** ppVector);
HRESULT CreateVector(IPoint2d* pSource,IVector2d** ppTarget);
HRESULT CreateVector(const WBFL::Geometry::Vector2d& source, IVector2d** ppVector);
HRESULT GetCoordinates(IVector2d* pSource,Float64* px,Float64 *py);

HRESULT CreateVector( IVector3d** ppTarget );
HRESULT CreateVector(Float64 x,Float64 y,Float64 z,IVector3d** ppVector);
HRESULT CreateVector( IVector3d* pSource, IVector3d** ppTarget );
HRESULT CreateVector( IPoint3d* pSource, IVector3d** ppTarget );
HRESULT CreateVector(const WBFL::Geometry::Vector3d& source, IVector3d** ppTarget);

HRESULT GetCoordinates(IVector3d* pVector,Float64* px,Float64* py,Float64* pz);
HRESULT Add(IVector3d* pResult,IVector3d* pA,IVector3d* pB);
HRESULT Subtract(IVector3d* pResult,IVector3d* pA,IVector3d* pB);

HRESULT CreatePointCollection(const std::vector<WBFL::Geometry::Point2d>& vPoints, IPoint2dCollection** ppPoints);
HRESULT CreatePointCollection(IPoint2dCollection** ppPoints);
HRESULT CreatePointCollection(IPoint2dCollection** ppPoints,IPoint2dCollection* pCopyFrom);
std::vector<WBFL::Geometry::Point2d> CreatePointCollection(IPoint2dCollection* pPoints);

HRESULT CreateLine(const WBFL::Geometry::Line2d& line, ILine2d** ppLine);
HRESULT CreateLine(ILine2d* pLine,ILine2d** ppLine);
HRESULT CreateLine(ILine2d** ppLine);
HRESULT CreateLine(ILineSegment2d* pSeg,ILine2d** ppLine);
HRESULT CreateLine(IPoint2d* pStart,IPoint2d* pEnd,ILine2d** ppLine);

HRESULT CreateLineSegment(const WBFL::Geometry::LineSegment2d& ls,ILineSegment2d** ppSeg);
HRESULT CreateLineSegment(ILineSegment2d** ppSeg);

HRESULT CreateShapeProperties(const WBFL::Geometry::ShapeProperties& props,IShapeProperties** ppProps);
HRESULT CreateShapeProperties(IShapeProperties** ppProps);

HRESULT CreateGenericShape(const WBFL::Geometry::Shape* pShape, IGenericShape** ppGenericShape);
HRESULT CreateCircle(const WBFL::Geometry::Shape* pShape, ICircle** ppCircle);
HRESULT CreateCircularSegment(const WBFL::Geometry::Shape* pShape, ICircularSegment** ppCircularSegment);
HRESULT CreatePolyShape(const WBFL::Geometry::Shape* pShape, IPolyShape** ppPolyShape);

//HRESULT CreatePolyShape(IPoint2dCollection* pPoints,IPolyShape** ppPolyShape);
//HRESULT CreatePolyShape(IPolyShape** ppPolyShape);
HRESULT CreateCompositeShape(ICompositeShape** ppCompositeShape);
HRESULT CreateGeomUtil(IGeomUtil2d** ppUtil);

VARIANT_BOOL MakeBool(bool boolean);

Float64 NormalizeAngle(Float64 angle);
bool IsEqualPoint(IPoint2d* p1,IPoint2d* p2);
bool IsEqualVector(IVector2d* p1,IVector2d* p2);

HRESULT ConvertShape(const WBFL::Geometry::Shape* pShape, IShape** ppShape);
std::shared_ptr<WBFL::Geometry::Shape> ConvertShape(IShape* pShape);

// function to compute a point along a line given an offset
// the line is defined by P1 and P2
// Offset is measured along line from p1 to p2
void ProjectPointAlongLine(Float64 P1_x, Float64 P1_y, Float64 P2_x, Float64 P2_y, Float64 Offset, 
                           Float64* pP_x, Float64* pP_y);

////// Template methods to implement IShapeImplT and IShape in a generic way
template <class T>
HRESULT GetShapeProperties(const T& shape, IShapeProperties** ppProps)
{
   CHECK_RETOBJ(ppProps);
   return CreateShapeProperties(shape.GetProperties(), ppProps);
}

template <class T>
HRESULT GetBoundingBox(const T& shape, IRect2d** ppRect)
{
   CHECK_RETOBJ(ppRect);
   return CreateRect(shape.GetBoundingBox(), ppRect);
}

template <class T>
HRESULT PointInShape(const T& shape, IPoint2d* pPoint, VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);
   *pbResult = (shape.PointInShape(GetPoint(pPoint)) ? VARIANT_TRUE : VARIANT_FALSE);
   return S_OK;
}

template <class T>
HRESULT ClipWithLine(const T& shape, ILine2d* pLine, IShape** ppShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(ppShape);

   *ppShape = nullptr;

   // Clips on the right side of the line (clip away the left side, the right side remains)
   std::unique_ptr<WBFL::Geometry::Shape> clipped_shape = shape.CreateClippedShape(GetLine(pLine), WBFL::Geometry::Line2d::Side::Left);

   if (clipped_shape)
   {
      HRESULT hr = ConvertShape(clipped_shape.get(), ppShape);
      if (FAILED(hr)) return hr;
   }

   return S_OK;
}

template <class T>
HRESULT ClipIn(const T& shape, IRect2d* pRect, IShape** ppShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(ppShape);

   *ppShape = nullptr;

   std::unique_ptr<WBFL::Geometry::Shape> clipped_shape = shape.CreateClippedShape(GetRect(pRect), WBFL::Geometry::Shape::ClipRegion::In);
   if (clipped_shape)
   {
      HRESULT hr = ConvertShape(clipped_shape.get(), ppShape);
      if (FAILED(hr)) return hr;
   }
   return S_OK;
}

template <class T>
HRESULT GetPerimeter(const T& shape, Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = shape.GetPerimeter();
   return S_OK;
}

template <class T>
HRESULT GetFurthestDistance(const T& shape, ILine2d* line,Float64* pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);
   *pVal = shape.GetFurthestDistance(GetLine(line), WBFL::Geometry::Line2d::Side::Right);
   return S_OK;
}

template <class T>
HRESULT GetFurthestPoint(const T& shape, ILine2d* line, IPoint2d** ppPoint, Float64* pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);
   CHECK_RETOBJ(ppPoint);
   auto [point,dist] = shape.GetFurthestPoint(GetLine(line), WBFL::Geometry::Line2d::Side::Right);
   CreatePoint(point, ppPoint);
   *pVal = dist;
   return S_OK;
}

template <class T>
HRESULT GetPolyPoints(const T& shape, IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);
   return CreatePointCollection(shape.GetPolyPoints(), ppPolyPoints);
}

template <class C,class T>
HRESULT Clone(const T& shape,IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<C>* pTheClone;
   HRESULT hr = CComObject<C>::CreateInstance(&pTheClone);
   if (FAILED(hr))
      return hr;

   pTheClone->SetShape(shape);

   pTheClone->QueryInterface(pClone);

   return S_OK;
}
