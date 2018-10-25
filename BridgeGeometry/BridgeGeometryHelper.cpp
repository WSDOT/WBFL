#include "stdafx.h"
#include "BridgeGeometryHelper.h"

HRESULT PierPathIntersect(IPierLine* pPier,IPath* pPath,IPoint2d** ppPoint)
{
   CComPtr<ILine2d> line;
   pPier->get_Centerline(&line);

   CComPtr<IPoint2d> pntPier;
   pPier->get_AlignmentPoint(&pntPier);

   return LinePathIntersect(line,pntPier,pPath,ppPoint);
}

HRESULT LinePathIntersect(ILine2d* pLine,IPoint2d* pNearestPoint,IPath* pPath,IPoint2d** ppPoint)
{
   HRESULT hr;

   CComPtr<IPoint2d> pntIntersect;
   hr = pPath->Intersect(pLine,pNearestPoint,&pntIntersect);
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
