///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2015  Washington State Department of Transportation
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

#include "stdafx.h"
#include "BridgeGeometryHelper.h"

HRESULT PierAlignmentIntersect(IPierLine* pPier,IAlignment* pAlignment,IPoint2d** ppPoint)
{
   CComPtr<ILine2d> line;
   pPier->get_Centerline(&line);

   CComPtr<IPoint2d> pntPier;
   pPier->get_AlignmentPoint(&pntPier);

   return LineAlignmentIntersect(line,pntPier,pAlignment,ppPoint);
}

HRESULT LineAlignmentIntersect(ILine2d* pLine,IPoint2d* pNearestPoint,IAlignment* pAlignment,IPoint2d** ppPoint)
{
   HRESULT hr;

   CComPtr<IPoint2d> pntIntersect;
   hr = pAlignment->Intersect(pLine,pNearestPoint,&pntIntersect);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
      return hr;

   pntIntersect.CopyTo(ppPoint);
   return S_OK;
}

HRESULT PierLineIntersect(IPierLine* pPier,ILine2d* pLine,IPoint2d** ppPoint)
{
#pragma Reminder("UPDATE: this would be more efficient if we didn't create a GeomUtil2d object every time")
   CComPtr<ILine2d> line;
   pPier->get_Centerline(&line);

   CComPtr<IGeomUtil2d> geomUtil;
   geomUtil.CoCreateInstance(CLSID_GeomUtil);
   return geomUtil->LineLineIntersect(line,pLine,ppPoint);
}

HRESULT GetDirection(IPierLine* pPier,IDirection** ppDirection)
{
   CComPtr<ILine2d> centerline;
   pPier->get_Centerline(&centerline);

   CComPtr<IPoint2d> pnt;
   CComPtr<IVector2d> v;
   centerline->GetExplicit(&pnt,&v);

   Float64 dir;
   v->get_Direction(&dir);

   CComPtr<IDirection> direction;
   direction.CoCreateInstance(CLSID_Direction);
   direction->put_Value(dir);

   direction.CopyTo(ppDirection);
   return S_OK;
}

HRESULT CreateLine(IPoint2d* pPoint,IDirection* pDirection,ILine2d** ppLine)
{
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   CComPtr<IPoint2d> pnt;
   CComPtr<IVector2d> v;
   line->GetExplicit(&pnt,&v);

   Float64 value;
   pDirection->get_Value(&value);
   v->put_Direction(value);

   line->SetExplicit(pPoint,v);
   line.CopyTo(ppLine);

   return S_OK;
}
