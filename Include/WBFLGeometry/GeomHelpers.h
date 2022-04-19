///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <WBFLGeometry\GeometryExp.h>
#include "WBFLGeometry.h"

/*****************************************************************************
CLASS 
   geomUtil

   Utility class for cogo related operations.

DESCRIPTION
   Utility class for cogo related operations.  This classes handles things like
   converting to and from DMS format and stationing format.

LOG
   rab : 06.19.1997 : Created file
*****************************************************************************/

class GEOMETRYCLASS geomUtil
{
public:
   static HRESULT CreateParallelLineSegment(ILineSegment2d* pSeg, Float64 offset, ILineSegment2dFactory* pLineSegmentFactory, ILineSegment2d** pNewSeg);
   static HRESULT IsLineParallelToLineSegment(ILine2d* pLine, ILineSegment2d* pSeg, VARIANT_BOOL* pbResult);
   static HRESULT AreLineSegmentsParallel(ILineSegment2d* pSeg1, ILineSegment2d* pSeg2, VARIANT_BOOL* pbResult);
   static HRESULT AreLinesParallel(ILine2d* pLine1, ILine2d* pLine2, VARIANT_BOOL* pbResult);
   static HRESULT IntersectLineWithLineSegment(ILine2d* pLine, ILineSegment2d* pSeg, IPoint2dFactory* pPointFactory, IPoint2d** ppPoint);
   static HRESULT SegSegIntersect(ILineSegment2d* pSeg1, ILineSegment2d* pSeg2, IPoint2dFactory* pPointFactory, IPoint2d** ppPoint);
   static HRESULT LineLineIntersect(ILine2d* l1, ILine2d *l2, IPoint2dFactory* pPointFactory, IPoint2d **ppPoint);
   static HRESULT DivideLineSegment(ILineSegment2d* pSeg, IndexType nSpaces, IPoint2dFactory* pPointFactory, IPoint2dCollection** ppPoints);
   static HRESULT DivideArc(IPoint2d* pStart, IPoint2d* pCenter, IPoint2d* pEnd, IndexType nSpaces, IPoint2dFactory* pPointFactory, IPoint2dCollection** ppPoints);
   static HRESULT DoesLineSegmentContainPoint(ILineSegment2d* pSeg, IPoint2d* pPoint, Float64 tolerance, VARIANT_BOOL* pbResult);
   static HRESULT DoesLineContainPoint(ILine2d* pLine, IPoint2d* pPoint, Float64 tolerance, VARIANT_BOOL* pbResult);
   static HRESULT AreLinesColinear(ILine2d* pLine1, ILine2d* pLine2, VARIANT_BOOL* pbResult);
   static HRESULT CreateNormalLineThroughPoint(ILine2d* pLine, IPoint2d* pPoint, ILine2dFactory* pLineFactory, ILine2d** ppLine);
   static HRESULT CreateParallelLine(ILine2d* pLine, Float64 dist, ILine2dFactory* pLineFactory, ILine2d** ppLine);
   static HRESULT CreateParallelLineThroughPoint(ILine2d* pLine, IPoint2d* pPoint, ILine2dFactory* pLineFactory, ILine2d** ppLine);
   static HRESULT PointOnLineNearest(ILine2d* pLine, IPoint2d* pPoint, IPoint2dFactory* pPointFactory, IPoint2d** ppPOLN);
   static HRESULT ShortestDistanceToPoint(ILine2d* pLine, IPoint2d* pPoint, Float64* pDist);
   static HRESULT Magnitude(IPoint2d* pPoint, Float64* pMag);
   static HRESULT Distance(IPoint2d* p1, IPoint2d* p2, Float64* dist);
   static HRESULT Angle(IPoint2d* pStart, IPoint2d* pCenter, IPoint2d* pEnd, Float64* angle);
   static HRESULT GenerateCircle(IndexType nPoints, IPoint2d* center, Float64 radius, Float64 initAngle, IPoint2dFactory* pPointFactory, IPoint2dCollection** points);
   static HRESULT LineCircleIntersect(ILine2d *line, ICircle* circle, IPoint2dFactory* pPointFactory, IPoint2d** p1, IPoint2d** p2, short* nIntersect);
   static HRESULT CircleCircleIntersect(ICircle* circle1, ICircle* circle2, IPoint2dFactory* pPointFactory, IPoint2d** p1, IPoint2d** p2, short* nIntersect);
   static HRESULT PointInTriangle(IPoint2d* p, IPoint2d* pA, IPoint2d* pB, IPoint2d* pC, VARIANT_BOOL* pbResult);

   static HRESULT Magnitude(IPoint3d* p,Float64 *pMag);
   static HRESULT Distance(IPoint3d* p1,IPoint3d* p2,Float64* pDist);
   static HRESULT PointInTriangle(IPoint3d* p,IPoint3d* pA,IPoint3d* pB,IPoint3d* pC,VARIANT_BOOL* pbResult);

   static void XformToNew(IPoint2d* pOrigin, Float64 angle, IPoint2d* pPoint);
   static void XformToNew(IPoint2d* pOrigin, Float64 angle, IPoint2d* pPoint,IPoint2d** ppPoint);
   static void XformToOriginal(IPoint2d* pOrigin, Float64 angle, IPoint2d* pPoint);
   static void XformToOriginal(IPoint2d* pOrigin, Float64 angle, IPoint2d* pPoint,IPoint2d** ppPoint);

private:
   geomUtil() = delete;
   geomUtil(const geomUtil& rOther) = delete;
   geomUtil& operator=(const geomUtil& rOther) = delete;
};
