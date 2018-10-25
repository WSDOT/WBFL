#pragma once

#include "WBFLBridgeGeometry.h"

HRESULT PierPathIntersect(IPierLine* pPier,IPath* pPath,IPoint2d** ppPoint);
HRESULT LinePathIntersect(ILine2d* pLine,IPoint2d* pNearestPoint,IPath* pPath,IPoint2d** ppPoint);
HRESULT PierLineIntersect(IPierLine* pPier,ILine2d* pLine,IPoint2d** ppPoint);
HRESULT GetDirection(IPierLine* pPier,IDirection** ppDirection);
HRESULT CreateLine(IPoint2d* pPoint,IDirection* pDirection,ILine2d** ppLine);
