///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_HELPER_H_
#define INCLUDED_HELPER_H_

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
interface IPoint2dFactory;
interface IPoint2dFactory;
interface ILine2dFactory;
interface ILineSegment2dFactory;

HRESULT CopyPoint(IPoint2d* pTo,IPoint2d* pFrom);
HRESULT CopyPoints(IPoint2dCollection* pTo,IPoint2dCollection* pFrom);
HRESULT CopyLineSegment(ILineSegment2d* pTo,ILineSegment2d* pFrom);
HRESULT GetCoordinates(IPoint2d* pPoint,Float64* px,Float64* py);
HRESULT GetCoordinates(IPoint3d* pPoint,Float64* px,Float64* py,Float64* pz);
HRESULT PutCoordinates(Float64 x,Float64 y,IPoint2d* pPoint);
HRESULT PutCoordinates(Float64 x,Float64 y,Float64 z,IPoint3d* pPoint);
HRESULT GetSize(ISize2d* pSize,Float64* pdx,Float64* pdy);
HRESULT GetRect(IRect2d* rect,Float64 *left,Float64 *top,Float64 *right,Float64 *bottom);

HRESULT CreatePoint(IPoint2d* pPoint,IPoint2dFactory* pFactory,IPoint2d** ppPoint);
HRESULT CreatePoint(Float64 x,Float64 y,IPoint2dFactory* pFactory,IPoint2d** ppPoint);
HRESULT CreatePoint(IPoint3d* pPoint,IPoint3dFactory* pFactory,IPoint3d** ppPoint);
HRESULT CreatePoint(Float64 x,Float64 y,Float64 z,IPoint3dFactory* pFactory,IPoint3d** ppPoint);

HRESULT CreateRect(Float64 left,Float64 top,Float64 right,Float64 bottom,IRect2d** ppRect);

HRESULT CreateSize(Float64 dx,Float64 dy,ISize2d** ppSize);
HRESULT CreateSize(Float64 dx,Float64 dy,Float64 dz,ISize3d** ppSize);

HRESULT CreateVector(Float64 x,Float64 y,IVector2d** ppVector);
HRESULT CreateVector(IPoint2d* pSource,IVector2d** ppTarget);
HRESULT GetCoordinates(IVector2d* pSource,Float64* px,Float64 *py);

HRESULT CreateVector( IVector3d** ppTarget );
HRESULT CreateVector(Float64 x,Float64 y,Float64 z,IVector3d** ppVector);
HRESULT CreateVector( IVector3d* pSource, IVector3d** ppTarget );
HRESULT CreateVector( IPoint3d* pSource, IVector3d** ppTarget );

HRESULT GetCoordinates(IVector3d* pVector,Float64* px,Float64* py,Float64* pz);
HRESULT Add(IVector3d* pResult,IVector3d* pA,IVector3d* pB);
HRESULT Subtract(IVector3d* pResult,IVector3d* pA,IVector3d* pB);

HRESULT CreatePointCollection(IPoint2dCollection** ppPoints);
HRESULT CreatePointCollection(IPoint2dCollection** ppPoints,IPoint2dCollection* pCopyFrom);

HRESULT CreateLine(ILine2d* pLine,ILine2dFactory* pFactory,ILine2d** ppLine);
HRESULT CreateLine(ILine2dFactory* pFactory,ILine2d** ppLine);
HRESULT CreateLine(ILineSegment2d* pSeg,ILine2dFactory* pFactory,ILine2d** ppLine);
HRESULT CreateLine(IPoint2d* pStart,IPoint2d* pEnd,ILine2dFactory* pFactor,ILine2d** ppLine);

HRESULT CreateLineSegment(ILineSegment2dFactory* pFactory,ILineSegment2d** ppSeg);

HRESULT CreateShapeProperties(IShapeProperties** ppProps);
HRESULT CreatePolyShape(IPoint2dCollection* pPoints,IPolyShape** ppPolyShape);
HRESULT CreatePolyShape(IPolyShape** ppPolyShape);
HRESULT CreateCompositeShape(ICompositeShape** ppCompositeShape);
HRESULT CreateGeomUtil(IGeomUtil2d** ppUtil);
HRESULT CreateGeomUtil(IGeomUtil3d** ppUtil);

VARIANT_BOOL MakeBool(bool boolean);

Float64 NormalizeAngle(Float64 angle);
bool IsEqualPoint(IPoint2d* p1,IPoint2d* p2);
bool IsEqualVector(IVector2d* p1,IVector2d* p2);

// Help functions that aren't used.
// This methods have not been tested
//HRESULT CopyPoint(IPoint3d* pTo,IPoint3d* pFrom);
//HRESULT CopyVector(IVector3d* pTarget,IVector3d* pSource);
//bool MakeBool(VARIANT_BOOL boolean);

// function to compute a point along a line given an offset
// the line is defined by P1 and P2
// Offset is measured along line from p1 to p2
void ProjectPointAlongLine(Float64 P1_x, Float64 P1_y, Float64 P2_x, Float64 P2_y, Float64 Offset, 
                           Float64* pP_x, Float64* pP_y);

#endif // INCLUDED_HELPER_H_
