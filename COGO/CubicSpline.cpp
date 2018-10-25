///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 2001  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// CubicSpline.cpp : Implementation of CCubicSpline
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CubicSpline.h"
#include "PointFactory.h"

#include "CogoHelpers.h"
#include <MathEx.h>
#include <string>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCubicSpline

STDMETHODIMP CCubicSpline::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICubicSpline,
		&IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CCubicSpline::FinalConstruct()
{
   HRESULT hr = m_Points.CoCreateInstance(CLSID_Point2dCollection);
   if ( FAILED(hr) )
      return hr;

   hr = m_CoordXform.CoCreateInstance(CLSID_CoordinateXform2d);
   if ( FAILED(hr) )
      return hr;

   hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

void CCubicSpline::FinalRelease()
{
}

// ICubicSpline
STDMETHODIMP CCubicSpline::AddPoints(IPoint2dCollection* points)
{
   CHECK_IN(points);

   CollectionIndexType nPoints;
   points->get_Count(&nPoints);
   for ( CollectionIndexType i = 0; i < nPoints; i++ )
   {
      CComPtr<IPoint2d> p;
      points->get_Item(i,&p);

      Float64 x,y;
      p->get_X(&x);
      p->get_Y(&y);

      CComPtr<IPoint2d> newPoint;
      CreatePoint(&newPoint);
      newPoint->Move(x,y);

      m_Points->Add(p);
   }

   m_bUpdateSpline = true;

   Fire_OnSplineChanged(this);

   return S_OK;
}

STDMETHODIMP CCubicSpline::AddPoint(Float64 x,Float64 y)
{
   CComPtr<IPoint2d> newPoint;
   CreatePoint(&newPoint);
   newPoint->Move(x,y);

   m_Points->Add(newPoint);

   m_bUpdateSpline = true;

   Fire_OnSplineChanged(this);

   return S_OK;
}

STDMETHODIMP CCubicSpline::AddPointEx(IPoint2d* point)
{
   CHECK_IN(point);

   Float64 x,y;
   point->get_X(&x);
   point->get_Y(&y);

   CComPtr<IPoint2d> newPoint;
   CreatePoint(&newPoint);
   newPoint->Move(x,y);

   m_Points->Add(newPoint);

   m_bUpdateSpline = true;

   Fire_OnSplineChanged(this);

   return S_OK;
}

STDMETHODIMP CCubicSpline::get_PointCount(CollectionIndexType* nPoints)
{
   return m_Points->get_Count(nPoints);
}

STDMETHODIMP CCubicSpline::get_Point(CollectionIndexType idx,IPoint2d** point)
{
   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   return m_Points->get_Item(idx,point);
}

STDMETHODIMP CCubicSpline::get_Points(IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);

   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   CollectionIndexType nPoints;
   m_Points->get_Count(&nPoints);
   for ( CollectionIndexType i = 0; i < nPoints; i++ )
   {
      CComPtr<IPoint2d> p;
      m_Points->get_Item(i,&p);

      CComPtr<IPoint2d> newPoint;
      CreatePoint(&newPoint);

      Float64 x,y;
      p->get_X(&x);
      p->get_Y(&y);

      newPoint->Move(x,y);
      points->Add(newPoint);
   }

   (*ppPoints) = points;
   (*ppPoints)->AddRef();
   return S_OK;
}

STDMETHODIMP CCubicSpline::get_StartPoint(IPoint2d** point)
{
   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   return m_Points->get_Item(0,point);
}

STDMETHODIMP CCubicSpline::get_EndPoint(IPoint2d** point)
{
   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   CollectionIndexType nPoints;
   m_Points->get_Count(&nPoints);
   return m_Points->get_Item(nPoints-1,point);
}

STDMETHODIMP CCubicSpline::Clear()
{
   m_Points->Clear();
   m_bUpdateSpline = true;
   Fire_OnSplineChanged(this);
   return S_OK;
}

STDMETHODIMP CCubicSpline::put_StartDirection(VARIANT varDirection)
{
   CComPtr<IDirection> direction;
   cogoUtil::DirectionFromVariant(varDirection,&direction);
   m_bUpdateSpline = true;
   direction->get_Value(&m_StartDirection);
   Fire_OnSplineChanged(this);
   return S_OK;
}

STDMETHODIMP CCubicSpline::get_StartDirection(IDirection** dir)
{
   return CreateDirection(m_StartDirection,dir);
}

STDMETHODIMP CCubicSpline::put_EndDirection( VARIANT varDirection)
{
   CComPtr<IDirection> direction;
   cogoUtil::DirectionFromVariant(varDirection,&direction);
   m_bUpdateSpline = true;
   direction->get_Value(&m_EndDirection);
   Fire_OnSplineChanged(this);
   return S_OK;
}

STDMETHODIMP CCubicSpline::get_EndDirection(IDirection** dir)
{
   return CreateDirection(m_EndDirection,dir);
}

STDMETHODIMP CCubicSpline::Bearing(Float64 distance,IDirection* *pVal)
{
   CHECK_RETOBJ(pVal);

   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   hr = UpdateSpline();
   if ( FAILED(hr) )
      return hr;

   distance = IsZero(distance) ? 0 : distance;
   if ( distance <= 0 )
   {
      // before start
      cogoUtil::DirectionFromVariant(CComVariant(m_StartDirection),pVal);
      return S_OK;
   }

   Float64 length;
   hr = get_Length(&length);
   if ( FAILED(hr) ) 
      return hr;

   distance = IsEqual(length,distance) ? length : distance;

   if ( length <= distance )
   {
      // after end
      cogoUtil::DirectionFromVariant(CComVariant(m_EndDirection),pVal);
      return S_OK;
   }

   // evalute the slope... convert to a bearing
   CComPtr<IPoint2d> pointOnSpline;
   PointOnSpline(distance,&pointOnSpline);

   Float64 x;
   pointOnSpline->get_X(&x);

   Float64 slope;
   Slope(x,VARIANT_TRUE,VARIANT_TRUE,&slope);

   Float64 angle = atan(slope);

   cogoUtil::DirectionFromVariant(CComVariant(angle),pVal);

   return S_OK;
}

STDMETHODIMP CCubicSpline::BearingAtPoint(CollectionIndexType idx,IDirection** pDir)
{
   CollectionIndexType nPoints;
   m_Points->get_Count(&nPoints);
   if ( idx < 0 || nPoints <= idx )
      return E_INVALIDARG;

   CHECK_RETVAL(pDir);


   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   hr = UpdateSpline();
   if ( FAILED(hr) )
      return hr;

   CollectionIndexType splineIdx = (idx == m_SplineSegments.size() ? idx-1 : idx);
   const CSplineSegment& splineSegment = m_SplineSegments[splineIdx];

   // if first point, get slope at start of segment, otherwise at end
   Float64 angle = splineSegment.Slope( (idx == 0 ? 0 : splineSegment.Length()) );

   cogoUtil::DirectionFromVariant(CComVariant(angle),pDir);

   return S_OK;
}

STDMETHODIMP CCubicSpline::Normal( Float64 distance, IDirection* *pVal)
{
   CHECK_RETVAL(pVal);


   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   hr = UpdateSpline();
   if ( FAILED(hr) )
      return hr;

   // get the bearing and rotate it
   Bearing(distance,pVal);

   (*pVal)->IncrementBy(CComVariant(-PI_OVER_2));
   return S_OK;
}

STDMETHODIMP CCubicSpline::NormalAtPoint(CollectionIndexType idx,IDirection** pDir)
{
   CollectionIndexType nPoints;
   m_Points->get_Count(&nPoints);
   if ( idx < 0 || nPoints <= idx )
      return E_INVALIDARG;

   CHECK_RETVAL(pDir);

   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   hr = UpdateSpline();
   if ( FAILED(hr) )
      return hr;

   // get the bearing and rotate it
   BearingAtPoint(idx,pDir);

   (*pDir)->IncrementBy(CComVariant(-PI_OVER_2));
   return S_OK;
}

STDMETHODIMP CCubicSpline::PointOnSpline(Float64 distance,IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   hr = UpdateSpline();
   if ( FAILED(hr) )
      return hr;

   CHECK_RETVAL(pVal);

   Float64 length;
   get_Length(&length);

   distance = IsZero(distance) ? 0 : distance;
   distance = IsEqual(distance,length) ? length : distance;

   Float64 splineDist;
   CSplineSegment* pSplineSegment = FindSplineSegment(distance,&splineDist);

   if ( pSplineSegment == NULL ) // before or after spline
   {
      if ( splineDist < 0 )
      {
         // before start
         CComPtr<IPoint2d> pntStart;
         m_Points->get_Item(0,&pntStart);

         Float64 sx,sy;
         pntStart->get_X(&sx);
         pntStart->get_Y(&sy);

         Float64 x = sx + splineDist*cos(m_StartDirection);
         Float64 y = sy + splineDist*sin(m_StartDirection);

         CreatePoint(pVal);
         (*pVal)->Move(x,y);
      }
      else
      {
         // after end
         CollectionIndexType nPoints;
         m_Points->get_Count(&nPoints);

         CComPtr<IPoint2d> pntEnd;
         m_Points->get_Item(nPoints-1,&pntEnd);

         Float64 ex,ey;
         pntEnd->get_X(&ex);
         pntEnd->get_Y(&ey);

         Float64 x = ex + splineDist*cos(m_EndDirection);
         Float64 y = ey + splineDist*sin(m_EndDirection);

         CreatePoint(pVal);
         (*pVal)->Move(x,y);
      }
   }
   else
   {
      Float64 x,y;
      pSplineSegment->GetPoint(splineDist,&x,&y);

      CreatePoint(pVal);
      (*pVal)->Move(x,y);

      m_CoordXform->Xform(pVal, xfrmNewToOld);
   }

   return S_OK;
}

STDMETHODIMP CCubicSpline::ProjectPoint(IPoint2d* point,IPoint2d* *pNewPoint)
{
   Float64 dist;
   return ProjectPoint(point,&dist,pNewPoint);
}

STDMETHODIMP CCubicSpline::DistanceFromStart(IPoint2d* point,Float64* dist)
{
   CComPtr<IPoint2d> projectedPoint;
   return ProjectPoint(point,dist,&projectedPoint);
}

STDMETHODIMP CCubicSpline::DistanceFromStartAtPoint(CollectionIndexType idx,Float64* dist)
{
   CollectionIndexType nPoints;
   m_Points->get_Count(&nPoints);
   if ( idx < 0 || nPoints <= idx )
      return E_INVALIDARG;

   CHECK_RETVAL(dist);

   *dist = 0;
   if ( idx == 0 )
      return S_OK;

   if ( idx == nPoints-1 )
      return get_Length(dist);

   // add up length of spline segments
   for ( CollectionIndexType segmentIdx = 0; segmentIdx < idx; segmentIdx++ )
   {
      const CSplineSegment& splineSegment = m_SplineSegments[segmentIdx];
      (*dist) += splineSegment.Length();
   }

   return S_OK;
}

STDMETHODIMP CCubicSpline::Intersect(ILine2d* line,VARIANT_BOOL bProjectBack,VARIANT_BOOL bProjectAhead,IPoint2dCollection** points)
{
   CHECK_IN(line);
   CHECK_RETOBJ(points);

   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   hr = UpdateSpline();
   if ( FAILED(hr) )
      return hr;

   CHECK_RETOBJ(points);
   CComPtr<IPoint2dCollection> objPoints;
   objPoints.CoCreateInstance(CLSID_Point2dCollection);

   CComPtr<IPoint2d> lastPoint;

   if ( bProjectBack == VARIANT_TRUE )
   {
      // create a "back tangent" line
      CComPtr<ILine2d> bkTangent;
      bkTangent.CoCreateInstance(CLSID_Line2d);

      // use explicit form of a line (a point + a vector passing through the point)

      // create vector
      CComPtr<IVector2d> v;
      v.CoCreateInstance(CLSID_Vector2d);
      v->put_Direction(m_StartDirection);

      // create point - use pntA of first spline segment
      CComPtr<IPoint2d> startPnt;
      get_StartPoint(&startPnt);

      bkTangent->SetExplicit(startPnt,v);

      // do a line-line intersect
      CComPtr<IPoint2d> bkTangentPoint;
      m_GeomUtil->LineLineIntersect(line,bkTangent,&bkTangentPoint);
      // intersection point is in global coordinates

      if ( bkTangentPoint )
      {
         // intersection must occur before the start of the spline
         Float64 xa;
         startPnt->get_X(&xa);

         Float64 x;
         bkTangentPoint->get_X(&x);


         if ( x < xa )
         {
            // intersection is before the start of the spline so
            // we'll keep that point
            objPoints->Add(bkTangentPoint);
            lastPoint = bkTangentPoint;
         }
      }
   }

   // intersect line with each spline segment. retain intsection points

   // the line is in the global coordinate system and the spline segments
   // are in the local spline coordinate system. create a line object
   // in the local coordinate system
   CComPtr<IPoint2d> pnt;
   CComPtr<IVector2d> v;
   line->GetExplicit(&pnt,&v);
   m_CoordXform->Xform(&pnt.p,xfrmOldToNew);
   v->Rotate(-m_RotationAngle);
   CComPtr<ILine2d> line2;
   line2.CoCreateInstance(CLSID_Line2d);
   line2->SetExplicit(pnt,v);

   std::vector<CSplineSegment>::const_iterator iter;
   for ( iter = m_SplineSegments.begin(); iter != m_SplineSegments.end(); iter++ )
   {
      const CSplineSegment& splineSegment = *iter;

      CComPtr<IPoint2d> p1,p2,p3; // in local spline coordinates
      splineSegment.Intersect(line2,m_GeomUtil,&p1,&p2,&p3);

      if ( p1 )
      {
         m_CoordXform->Xform(&p1.p,xfrmNewToOld);

         if ( !lastPoint || !cogoUtil::IsEqual(lastPoint,p1) )
         {
            objPoints->Add(p1);
            lastPoint = p1;
         }
      }

      if ( p2 )
      {
         m_CoordXform->Xform(&p2.p,xfrmNewToOld);

         if ( !lastPoint || !cogoUtil::IsEqual(lastPoint,p2) )
         {
            objPoints->Add(p2);
            lastPoint = p2;
         }
      }

      if ( p3 )
      {
         m_CoordXform->Xform(&p3.p,xfrmNewToOld);

         if ( !lastPoint || !cogoUtil::IsEqual(lastPoint,p3) )
         {
            objPoints->Add(p3);
            lastPoint = p3;
         }
      }
   }


   if ( bProjectAhead == VARIANT_TRUE )
   {
      // create an "ahead tangent" line
      CComPtr<ILine2d> aheadTangent;
      aheadTangent.CoCreateInstance(CLSID_Line2d);

      // use explicit form of a line (a point + a vector passing through the point)

      // create vector
      CComPtr<IVector2d> v;
      v.CoCreateInstance(CLSID_Vector2d);
      v->put_Direction(m_EndDirection);

      CComPtr<IPoint2d> endPoint;
      get_EndPoint(&endPoint);

      aheadTangent->SetExplicit(endPoint,v);

      // do a line-line intersect
      CComPtr<IPoint2d> aheadTangentPoint;
      m_GeomUtil->LineLineIntersect(line,aheadTangent,&aheadTangentPoint);

      if ( aheadTangentPoint )
      {
         // intersection must occur after the end of the spline
         Float64 xb;
         endPoint->get_X(&xb);

         Float64 x;
         aheadTangentPoint->get_X(&x);


         if ( IsEqual(xb,x) || xb < x )
         {
            // intersection is after the end of the spline so
            // we'll keep that point
            if ( !lastPoint || !cogoUtil::IsEqual(lastPoint,aheadTangentPoint) )
            {
               objPoints->Add(aheadTangentPoint);
               lastPoint = aheadTangentPoint;
            }
         }
      }
   }

   (*points) = objPoints;
   (*points)->AddRef();

   return S_OK;
}

STDMETHODIMP CCubicSpline::get_Length(Float64* pLength)
{
   CHECK_RETVAL(pLength);

   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   hr = UpdateSpline();
   if ( FAILED(hr) )
      return hr;

   Float64 L = 0;
   std::vector<CSplineSegment>::iterator iter;
   for ( iter = m_SplineSegments.begin(); iter != m_SplineSegments.end(); iter++ )
   {
      const CSplineSegment& splineSegment = *iter;
      L += splineSegment.Length();
   }

   *pLength = L;
   return S_OK;
}

STDMETHODIMP CCubicSpline::get_PointFactory(IPoint2dFactory* *factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_PointFactory;
   (*factory)->AddRef();

   return S_OK;
}

STDMETHODIMP CCubicSpline::putref_PointFactory(IPoint2dFactory *factory)
{
   CHECK_IN(factory);
   m_PointFactory = factory;
   return S_OK;
}

STDMETHODIMP CCubicSpline::Clone(ICubicSpline* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CCubicSpline>* pClone;
   CComObject<CCubicSpline>::CreateInstance(&pClone);

   pClone->AddPoints(m_Points);
   pClone->put_StartDirection( CComVariant(m_StartDirection) );
   pClone->put_EndDirection(   CComVariant(m_EndDirection)   );
   
   (*clone) = pClone;
   (*clone)->AddRef();

   return S_OK;
}

STDMETHODIMP CCubicSpline::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CCubicSpline::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("CubicSpline"),1.0);

   pSave->put_Property(CComBSTR("StartDirection"),CComVariant(m_StartDirection));
   pSave->put_Property(CComBSTR("EndDirection"),  CComVariant(m_EndDirection));
   
   CComQIPtr<IStructuredStorage2> ss2(m_Points);
   ss2->Save(pSave);

   if (m_PointFactory)
   {
      pSave->put_Property(CComBSTR("PointFactory"),CComVariant(m_PointFactory));
   }
   
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCubicSpline::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("CubicSpline"));

   pLoad->get_Property(CComBSTR("StartDirection"),&var);
   m_StartDirection = var.dblVal;

   pLoad->get_Property(CComBSTR("EndDirection"),&var);
   m_EndDirection = var.dblVal;

   CComQIPtr<IStructuredStorage2> ss2(m_Points);
   ss2->Load(pLoad);

   if ( SUCCEEDED(pLoad->get_Property(CComBSTR("PointFactory"),&var)) )
   {
      CComPtr<IPoint2dFactory> factory;
      _CopyVariantToInterface<IPoint2dFactory>::copy(&factory,&var);
      putref_PointFactory(factory);
   }

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CCubicSpline::Evaluate(Float64 x,VARIANT_BOOL bProjectBack,VARIANT_BOOL bProjectAhead,Float64* y)
{
   CHECK_RETVAL(y);

   CComPtr<IPoint2d> p;
   p.CoCreateInstance(CLSID_Point2d);
   p->Move(x,0);

   CComPtr<IVector2d> v;
   v.CoCreateInstance(CLSID_Vector2d);
   v->put_Direction(PI_OVER_2); // vertical

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   line->SetExplicit(p,v);

   CComPtr<IPoint2dCollection> points;
   HRESULT hr = Intersect(line,bProjectBack,bProjectAhead,&points);
   if ( FAILED(hr) )
      return hr;

   CollectionIndexType nPoints;
   points->get_Count(&nPoints);
   if ( nPoints == 0 )
   {
      *y = -999;
      return E_INVALIDARG;
   }

   CComPtr<IPoint2d> pnt;
   points->get_Item(0,&pnt);
   pnt->get_Y(y);
   return S_OK;
}

STDMETHODIMP CCubicSpline::Slope(Float64 x,VARIANT_BOOL bProjectBack,VARIANT_BOOL bProjectAhead,Float64* dy)
{
   // x is global X value
   CHECK_RETVAL(dy);

   // get the point on the spline where we want to evaluate the slope
   Float64 y;
   HRESULT hr = Evaluate(x,bProjectBack,bProjectAhead,&y);
   if ( FAILED(hr) )
      return hr;

   // convert X into spline coordinates
   CComPtr<IPoint2d> p;
   p.CoCreateInstance(CLSID_Point2d);
   p->Move(x,y); // point on spline where we want to evaluate the slope
   m_CoordXform->Xform(&p.p, xfrmOldToNew);
   Float64 xs; // x in spline coordinates
   p->get_X(&xs);


   // quick check to see if we even need to worry about evaluating the spline
   Float64 xStart, xEnd;
   m_SplineSegments.front().pntA->get_X(&xStart);
   m_SplineSegments.back().pntB->get_X(&xEnd);

   if ( (xs < xStart && bProjectBack == VARIANT_FALSE) ||
        (xEnd < xs && bProjectAhead == VARIANT_FALSE) )
   {
      return E_INVALIDARG;
   }

   // check if x is before the start of the spline
   if ( xs < xStart && bProjectBack == VARIANT_TRUE )
   {
      *dy = tan(m_StartDirection - m_RotationAngle);
      return S_OK;
   }

   // check if x is after the end of the spline
   if ( xEnd < xs && bProjectAhead == VARIANT_TRUE )
   {
      *dy = tan(m_EndDirection - m_RotationAngle);
      return S_OK;
   }

   // find the spline that contains x
   std::vector<CSplineSegment>::iterator iter;
   for ( iter = m_SplineSegments.begin(); iter != m_SplineSegments.end(); iter++ )
   {
      CSplineSegment splineSegment = *iter;
      Float64 xa,xb;
      splineSegment.pntA->get_X(&xa);
      splineSegment.pntB->get_X(&xb);

      if ( InRange(xa,xs,xb) )
      {
         Float64 slope = splineSegment.Slope(xs);
         *dy = slope + tan(m_RotationAngle);
         return S_OK;
      }
   }

   *dy = -999;
   return E_INVALIDARG;
}

HRESULT CCubicSpline::CreateSplineSegments()
{
   m_SplineSegments.clear();

   // determine the orientation of a coordinate system with it's origin
   // at the first point and its positive X axis passing through the last point
   CComPtr<IPoint2d> p0, pn; // point 0 and point "n"
   CollectionIndexType nPoints;
   m_Points->get_Count(&nPoints);

   m_Points->get_Item(0,&p0);
   m_Points->get_Item(nPoints-1,&pn);

   Float64 distance;
   CComPtr<IDirection> direction;
   cogoUtil::Inverse(p0,pn,&distance,&direction);

   direction->get_Value(&m_RotationAngle);

   // later on, we will need to compute the slope of the start and end tangent using the tan function
   // if the start or end angles are PI/2 or 3PI/2, tan is infinity and we've got problems
   // rotate the "local" coordinate system to avoid this problem
   Float64 start_angle = cogoUtil::NormalizeAngle(m_StartDirection - m_RotationAngle);
   Float64 end_angle   = cogoUtil::NormalizeAngle(m_EndDirection   - m_RotationAngle);
   while ( (IsEqual(start_angle,PI_OVER_2) || IsEqual(start_angle,3*PI_OVER_2)) ||
           (IsEqual(end_angle,  PI_OVER_2) || IsEqual(end_angle,  3*PI_OVER_2)) )
   {
      m_RotationAngle += M_PI*10./180.;  // 10 degree "tweak" of the rotation angle
      start_angle = cogoUtil::NormalizeAngle(m_StartDirection - m_RotationAngle);
      end_angle   = cogoUtil::NormalizeAngle(m_EndDirection   - m_RotationAngle);
   }

   m_CoordXform->putref_NewOrigin(p0);
   m_CoordXform->put_RotationAngle(m_RotationAngle);

   // transform the points into the new coordinate system
   // and same in a spline segment object
   for ( CollectionIndexType i = 0; i < nPoints-1; i++ )
   {
      CComPtr<IPoint2d> pi, pi1; // point i and i+1
      m_Points->get_Item(i,  &pi);
      m_Points->get_Item(i+1,&pi1);

      CSplineSegment splineSegment;
      m_CoordXform->XformEx(pi, xfrmOldToNew,&splineSegment.pntA);
      m_CoordXform->XformEx(pi1,xfrmOldToNew,&splineSegment.pntB);

      Float64 xa, xb;
      splineSegment.pntA->get_X(&xa);
      splineSegment.pntB->get_X(&xb);

      // xb has to come after xa
      if ( xb <= xa )
         return Error(IDS_E_CUBICSPLINEPOINTS,IID_ICubicSpline,COGO_E_CUBICSPLINEPOINTS);

      m_SplineSegments.push_back(splineSegment);
   }

   return S_OK;
}

HRESULT CCubicSpline::UpdateSpline()
{
   // See http://www.physics.arizona.edu/~restrepo/475A/Notes/sourcea/node35.html

   if ( !m_bUpdateSpline )
      return S_OK;

   HRESULT hr = CreateSplineSegments();
   if ( FAILED(hr) )
      return hr;

   long nPoints = m_SplineSegments.size() + 1;

   // spline coefficients y = a + bx + cx^2 + dx^3
   Float64* an = new Float64[nPoints];
   Float64* bn = new Float64[nPoints];
   Float64* cn = new Float64[nPoints];
   Float64* dn = new Float64[nPoints];

   // set an[i] = f(xi)
   std::vector<CSplineSegment>::iterator iter;
   int i = 0;
   for ( iter = m_SplineSegments.begin(); iter != m_SplineSegments.end(); iter++, i++ )
   {
      CSplineSegment& splineSegment = *iter;
      splineSegment.pntA->get_Y(&an[i]);
   }
   // get the last point
   m_SplineSegments.back().pntB->get_Y(&an[nPoints-1]);

   // hi = x(i+1) - x(i)
   Float64* hi = new Float64[nPoints];
   i = 0;
   for ( iter = m_SplineSegments.begin(); iter != m_SplineSegments.end(); iter++, i++ )
   {
      CSplineSegment& splineSegment = *iter;
      Float64 xi, xi1;
      splineSegment.pntA->get_X(&xi);
      splineSegment.pntB->get_X(&xi1);
      
      Float64 h = xi1 - xi;
      hi[i] = h;
   }

   // get start and end slope WRT rotated coordinate system
   Float64 start_angle = cogoUtil::NormalizeAngle(m_StartDirection - m_RotationAngle);
   ATLASSERT( !IsEqual(start_angle,PI_OVER_2) && !IsEqual(start_angle,3*PI_OVER_2) );
   Float64 start_slope = tan(start_angle);

   Float64 end_angle = cogoUtil::NormalizeAngle(m_EndDirection - m_RotationAngle);
   ATLASSERT( !IsEqual(end_angle,PI_OVER_2) && !IsEqual(end_angle,3*PI_OVER_2) );
   Float64 end_slope = tan(end_angle);

   // set ai0 = 3(a1-a0)/hi0 - 3dfx0
   // set ain = 3dfxn-3{an-an(n-1)}/hi(n-1)
   Float64* ai = new Float64[nPoints];
   ai[0]         = (((3*(an[1] - an[0]))/hi[0]) - (3*start_slope));
   ai[nPoints-1] = ((3*end_slope)-((3*(an[(nPoints-1)]-an[(nPoints-2)]))/hi[(nPoints-2)]));

   // set ai=(3/hi)*[a(i+1)-ai]-[3/h(i-1)]*[ai-a(i-1)]     for i=1,2,3,...,n-1
   for(i = 1; i < nPoints-1; i++)
   {
      ai[i] = (((3/hi[i])*(an[(i+1)]-an[i]))-((3/(hi[(i-1)])*(an[i]-an[(i-1)]))));
   }

   Float64* li = new Float64[nPoints];
   Float64* ui = new Float64[nPoints];
   Float64* zi = new Float64[nPoints];
   // set li0=2hi0
   //     ui0=0.5
   //     zi0=ai0/li0
   li[0] = (2*hi[0]);
   ui[0] = 0.5;
   zi[0] = (ai[0]/li[0]);

   // for i=1,2,3,...,n-1 ,set
   //    li=[2*{x(i+1)-x(i-1)}]-[h(i-1)*u(i-1)]
   //    ui=hi/li
   //    zi=[ai-{h(i-1)*z(i-1)}]/li
   for(i = 1; i < nPoints-1; i++)
   {
      CSplineSegment& splineSegment1 = m_SplineSegments[i-1];  // x(i-1) = pntA, x(i) = pntB
      CSplineSegment& splineSegment2 = m_SplineSegments[i];    // x(i) = pntA, x(i+1) = pntB

      Float64 prevX, nextX; // x(i-1), x(i+1);
      splineSegment1.pntA->get_X(&prevX);
      splineSegment2.pntB->get_X(&nextX);

      li[i] = ((2*(nextX-prevX))-(hi[(i-1)]*ui[(i-1)]));
      ui[i] = (hi[i]/li[i]);
      zi[i] = ((ai[i]-(hi[(i-1)]*zi[(i-1)]))/li[i]);
   }

   // set lin=h(n-1){2-ui(n-1)}
   //     zin={ain-hi(n-1)zi(n-1)}/lin
   //     cn=zin
   li[(nPoints-1)] = (hi[(nPoints-2)]*(2-ui[(nPoints-2)]));
   zi[(nPoints-1)] = ((ai[(nPoints-1)]-(hi[(nPoints-2)]*zi[(nPoints-2)]))/li[(nPoints-1)]);
   cn[(nPoints-1)] = zi[(nPoints-1)];

   // for i=n-1,n-2,...,0   , set
   //     ci=zi-[ui*c(i+1)]
   //     bi=[a(i+1)-ai]/hi-{hi*{c(i+1)+[2*ci]}/3
   //     di=[c(i+1)-ci]/[3*hi]
   for( i = nPoints-2; i >= 0; i--)
   {
      cn[i]=(zi[i]-(ui[i]*cn[(i+1)]));
	   bn[i]=(((an[(i+1)]-an[i])/hi[i])-((hi[i]*(cn[(i+1)]+(2*cn[i])))/3));
      dn[i]=((cn[(i+1)]-cn[i])/(3*hi[i]));
   }

   for ( i = 0, iter = m_SplineSegments.begin(); iter != m_SplineSegments.end(); i++, iter++ )
   {
      CSplineSegment& splineSegment = *iter;
      splineSegment.Init(an[i],bn[i],cn[i],dn[i]);
   }

   // clean up
   delete[] an;
   delete[] bn;
   delete[] cn;
   delete[] dn;

   delete[] hi;
   delete[] ai;
   delete[] li;
   delete[] ui;
   delete[] zi;

   m_bUpdateSpline = false;
   return S_OK;
}

CSplineSegment* CCubicSpline::FindSplineSegment(Float64 distance,Float64* pDistFromStartOfSegment)
{
   if ( distance < 0 )
   {
      *pDistFromStartOfSegment = distance;
      return NULL;
   }

   Float64 start_distance = 0;
   std::vector<CSplineSegment>::iterator iter;
   for ( iter = m_SplineSegments.begin(); iter != m_SplineSegments.end(); iter++ )
   {
      CSplineSegment& splineSegment = *iter;
      Float64 S = splineSegment.Length();

      if ( start_distance <= distance && distance < start_distance+S )
      {
         *pDistFromStartOfSegment = distance - start_distance;
         return &splineSegment;
      }

      start_distance += S;
   }

   // beyond end
   *pDistFromStartOfSegment = distance - start_distance; // distance past end
   return NULL;
}

void CCubicSpline::CreatePoint(IPoint2d** ppPoint)
{
   if (m_PointFactory)
   {
      m_PointFactory->CreatePoint(ppPoint);
   }
   else
   {
      CComPtr<IPoint2d> p;
      p.CoCreateInstance(CLSID_Point2d);
      (*ppPoint) = p;
      (*ppPoint)->AddRef();
   }
}

HRESULT CCubicSpline::CheckValid()
{
   CollectionIndexType nPoints;
   m_Points->get_Count(&nPoints);
   if ( nPoints < 2 )
      return Error(IDS_E_CUBICSPLINEPOINTS,IID_ICubicSpline,COGO_E_CUBICSPLINEPOINTS);
   else
      return S_OK;
}

HRESULT CCubicSpline::ProjectPoint(IPoint2d* point,Float64* pDistFromStart,IPoint2d* *pNewPoint)
{
   CHECK_IN(point);
   CHECK_RETVAL(pDistFromStart);
   CHECK_RETOBJ(pNewPoint);

   HRESULT hr = CheckValid();
   if ( FAILED(hr) )
      return hr;

   hr = UpdateSpline();
   if ( FAILED(hr) )
      return hr;

   // First we have to determine if the point is before or after the spline
   // This is accomplished by setting up coordinate systems at the start and end
   // of the spline. The X axes are the line connecting the start and end points.

   CComPtr<ICoordinateXform2d> xfrm; // local coordinate transform
   xfrm.CoCreateInstance(CLSID_CoordinateXform2d);

   // Setup the first coordinate system, with origin at p0
   CComPtr<IPoint2d> p0;
   get_StartPoint(&p0);

   CComPtr<IPoint2d> pn;
   get_EndPoint(&pn);

   CComPtr<IDirection> dir;
   Float64 dist;
   cogoUtil::Inverse(p0,pn,&dist,&dir);

   Float64 dirValue;
   dir->get_Value(&dirValue);


   xfrm->putref_NewOrigin(p0);
   xfrm->put_RotationAngle(dirValue);

   CComPtr<IPoint2d> xfrmPoint;
   xfrm->XformEx(point,xfrmOldToNew,&xfrmPoint);
   Float64 x1; // X ordinate in coordinate system 1
   xfrmPoint->get_X(&x1);
   x1 = IsZero(x1) ? 0.00 : x1;

   // Setup the second coordinate system, with origin at pn
   xfrmPoint.Release();


   xfrm->putref_NewOrigin(pn);
   xfrm->put_RotationAngle(dirValue + M_PI);
   xfrm->XformEx(point,xfrmOldToNew,&xfrmPoint);
   Float64 x2;
   xfrmPoint->get_X(&x2);
   x2 = IsZero(x2) ? 0.00 : x2;


   if ( x1 < 0 && x2 < 0 )
   {
      // Point projects onto both the foward and back tangents
      // Find the point nearest the spline. If equal distance, take the
      // point on the foward tangent

      // Create a line object along the back tangent bearing. Locate the point on
      // that line that is nearest the input point
      CComPtr<IVector2d> v;
      v.CoCreateInstance(CLSID_Vector2d);
      v->put_Direction(m_StartDirection);
      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->SetExplicit(p0,v);

      CComPtr<IPoint2d> p1;
      m_GeomUtil->PointOnLineNearest(line,point,&p1);

      // Create a line object along the foward tangent bearing. Locate the point on
      // that line that is nearest the input point
      
      v->put_Direction(m_EndDirection);
      line->SetExplicit(pn,v);

      CComPtr<IPoint2d> p2;
      m_GeomUtil->PointOnLineNearest(line,point,&p2);

      Float64 d1, d2;
      m_GeomUtil->Distance(point,p1,&d1);
      m_GeomUtil->Distance(point,p2,&d2);

      if ( d1 < d2 )
      {
         // Point projects onto the back tangent bearing (it is before the curve)
         p1.QueryInterface(pNewPoint);
         ATLASSERT( *pNewPoint != NULL );

         m_GeomUtil->Distance(p0,p1,pDistFromStart);
         (*pDistFromStart) *= -1;

         ATLASSERT( (*pDistFromStart) <= 0 ); // must be negative because it is before the curve
      }
      else
      {
         // Point projects onto the forward tangent bearing (it is after the curve)
         p2.QueryInterface(pNewPoint);
         ATLASSERT( *pNewPoint != NULL );

         Float64 Lt; // Total length of curve
         get_Length(&Lt);

         m_GeomUtil->Distance(pn,p2,pDistFromStart);
         (*pDistFromStart) += Lt;

         ATLASSERT( (*pDistFromStart) >= 0 && (*pDistFromStart) >= Lt );
      }

      return S_OK;
   }
   else if ( x1 <= 0 )
   {
      // Point is before the curve
      // Create a line object along the back tangent bearing. Locate the point on
      // that line that is nearest the input point
      CComPtr<IVector2d> v;
      v.CoCreateInstance(CLSID_Vector2d);
      v->put_Direction(m_StartDirection);
      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->SetExplicit(p0,v);

      CComPtr<IPoint2d> p;
      m_GeomUtil->PointOnLineNearest(line,point,&p);
      p.QueryInterface(pNewPoint);
      ATLASSERT( *pNewPoint != NULL );

      m_GeomUtil->Distance(p0,*pNewPoint,pDistFromStart);
      (*pDistFromStart) *= -1;

      ATLASSERT( (*pDistFromStart) <= 0 ); // must be negative because it is before the curve
      return S_OK;
   }
   else if ( 0 < x1 && 0 < x2 )
   {
      // point is between limits of spline

      // we have to work in the rotated coordinate system
      CComPtr<IPoint2d> pntRotated;
      m_CoordXform->XformEx(point, xfrmOldToNew,&pntRotated);
      Float64 px,py;
      pntRotated->get_X(&px);
      pntRotated->get_Y(&py);

      // NOTE: when comparing distance from the point to be projected onto the spline and the point on 
      // the spline where a normal vector passes through the point to be projected, the square of the 
      // distance will be evaluated. The actual distance between these points doesn't matter so we
      // can save some CPU cycles by not computing the square root.

      Float64 dist_from_start = 0;
      Float64 shortest_distance = DBL_MAX;
      Float64 sx, sy; // coordinates of point on segment that produced the current "shortest distance"

      bool bFound = false;

      // for each spline, find a point on the spline that a normal vector passes through
      // and also passes through the target point.
      //
      // compute the distace between these two points
      //
      // the point associated with the shortest distance is the one we are after
      std::vector<CSplineSegment>::const_iterator iter;
      for ( iter = m_SplineSegments.begin(); iter != m_SplineSegments.end(); iter++ )
      {
         const CSplineSegment& splineSegment = *iter;
         CSplineSegmentProjectPointFunction fn(splineSegment,pntRotated,m_GeomUtil);
         mathBisectionRootFinder2d rootfinder;

         // find the length along the spline segment where a normal line passes through
         // point
         Float64 s; // distance along segment
         try
         {
            s = rootfinder.FindRootInRange(fn,0,splineSegment.Length(),0.00001);
         }
         catch(...)
         {
            // a solution wasn't found... go to the next segment
            dist_from_start += splineSegment.Length();
            continue;
         }

         bFound = true;

         Float64 x,y;
         splineSegment.GetPoint(s,&x,&y);

         Float64 dist2 = (px-x)*(px-x) + (py-y)*(py-y); // square of the distance

         if ( dist2 < shortest_distance )
         {
            shortest_distance = dist2;
            *pDistFromStart = dist_from_start + s;
            sx = x;
            sy = y;
         }
      }

      if ( bFound )
      {
         CreatePoint(pNewPoint);
         (*pNewPoint)->Move(sx,sy);

         // convert back to original coordiante system
         m_CoordXform->Xform(pNewPoint, xfrmNewToOld);

         return S_OK;
      }
      else
      {
         return E_FAIL;
      }
   }
   else if ( x2 <= 0 )
   {
      // Point is after the curve
      // Create a line object along the foward tangent bearing. Locate the point on
      // that line that is nearest the input point
      CComPtr<IVector2d> v;
      v.CoCreateInstance(CLSID_Vector2d);
      v->put_Direction(m_EndDirection);
      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->SetExplicit(pn,v);

      CComPtr<IPoint2d> p;
      m_GeomUtil->PointOnLineNearest(line,point,&p);
      p.QueryInterface(pNewPoint);
      ATLASSERT( *pNewPoint != NULL );

      Float64 Lt;
      get_Length(&Lt);
      m_GeomUtil->Distance(pn,*pNewPoint,pDistFromStart);
      (*pDistFromStart) += Lt;

      ATLASSERT( (*pDistFromStart) >= 0 && (*pDistFromStart) >= Lt );
      return S_OK;
   }
   
   ATLASSERT(false); // should never get here
   return E_FAIL;
}

/////////////////////////////////////////////////////
CSplineSegment::CSplineSegment()
{
   m_bComputeLength = true;
}

void CSplineSegment::Init(Float64 a,Float64 b,Float64 c,Float64 d)
{
   A = a;
   B = b;
   C = c;
   D = d;
   m_bComputeLength = true;
}

Float64 CSplineSegment::Length() const
{
   if ( m_bComputeLength )
   {
      Float64 xa, xb;
      pntB->get_X(&xb);
      pntA->get_X(&xa);

      Float64 dist = xb - xa;
      m_Length = Length( dist );
      m_bComputeLength = false;
   }

   return m_Length;
}

Float64 CSplineSegment::Length(Float64 dx) const
{
   Float64 xa;
   pntA->get_X(&xa);

   CSplineSegmentLengthFunction fn(*this);

   mathTrapezoidalRuleIntegrator integrator;
   Float64 L = integrator.Evaluate(fn,xa,xa+dx,50);
   return L;
}

Float64 CSplineSegment::Evaluate(Float64 x) const
{
   Float64 xa;
   pntA->get_X(&xa);
   Float64 z = x-xa;
   return A + B*z + C*z*z + D*z*z*z;
}

Float64 CSplineSegment::Slope(Float64 x) const
{
   Float64 xa;
   pntA->get_X(&xa);
   Float64 z = x-xa;
   return B + 2*C*z + 3*D*z*z;
}

void CSplineSegment::GetPoint(Float64 distance,Float64* pX,Float64* pY) const
{
   Float64 xa, xb;
   pntA->get_X(&xa);
   pntB->get_X(&xb);
   
   CSplineSegmentPointFunction fn(distance,xa,*this);

   mathBisectionRootFinder2d rootfinder;
   Float64 xr = rootfinder.FindRootInRange(fn,xa,xb,0.00001);
   Float64 yr = Evaluate(xr);

   *pX = xr;
   *pY = yr;
}

Float64 CSplineSegment::Bearing(Float64 distance) const
{
   // evalute the slope... convert to a bearing
   CComPtr<IPoint2d> pointOnSpline;
   Float64 x,y;
   GetPoint(distance,&x,&y);

   Float64 slope = Slope(x);

   Float64 angle = atan(slope);
   return cogoUtil::NormalizeAngle(angle);
}

Float64 CSplineSegment::Normal(Float64 distance) const
{
   Float64 angle = Bearing(distance);
   angle -= PI_OVER_2;
   return cogoUtil::NormalizeAngle(angle);
}

void CSplineSegment::Intersect(ILine2d* line,IGeomUtil2d* pGU,IPoint2d** p1,IPoint2d** p2,IPoint2d** p3) const
{
   (*p1) = NULL;
   (*p2) = NULL;
   (*p3) = NULL;

   // get coefficients for function of line
   // y = mx + k

   // get the explicit form of the line and derive the slope, m, 
   // from the vector running in the direction of the line
   CComPtr<IVector2d> dir;
   CComPtr<IPoint2d> p;
   line->GetExplicit(&p,&dir);

   CComPtr<ISize2d> size;
   dir->get_Size(&size);
   Float64 dx,dy;
   size->get_Dx(&dx);
   size->get_Dy(&dy);

   Float64 xa,xb;
   pntA->get_X(&xa);
   pntB->get_X(&xb);

   int nRoots = 0;
   Float64 x[3];
   if ( IsZero(dx) )
   {
      // the line is vertical. there will be exactly one intersection point
      nRoots = 1;
      p->get_X(&x[0]);
      x[0] -= xa;
   }
   else
   {
      Float64 m = dy/dx;

      // determine the y-intercept
      // we need any point on the line to do this. an easy point to get
      // is the point on the line nearest the origin
      CComPtr<IPoint2d> origin;
      origin.CoCreateInstance(CLSID_Point2d);
      origin->Move(0,0);

      CComPtr<IPoint2d> poln;
      pGU->PointOnLineNearest(line,origin,&poln);
      Float64 X,Y;
      poln->get_X(&X);
      poln->get_Y(&Y);
      Float64 k = Y - m*(X-xa);

      // solve A + Bx + Cx^2 + Dx^3 - (mx+k) = (A-k) + (B-m)x + Cx^2 + Dx^3 = 0
      // NOTE: The coefficients in this CubicSplineSegment class and in the
      // cubic solver aren't the same.
      //          k1*x^3   + k2*x^2   + k3*x   + k4
      // Spline   D          C          B        A
      // Solver   A          B          C        D
      mathCubicSolver solver(D,C,(B-m),(A-k));

      nRoots = solver.Solve(&x[0],&x[1],&x[2]);

#if defined _DEBUG
      for ( int i = 0;i < nRoots; i++ )
      {
         Float64 z1 = A + B*x[i] + C*x[i]*x[i] + D*x[i]*x[i]*x[i];
         Float64 z2 = m*x[i] + k;
         ATLASSERT( IsEqual(z1,z2,0.0001) );
      }
#endif // _DEBUG
   }

   for ( int i = 0; i < nRoots; i++ )
   {
      if ( InRange(xa,x[i]+xa,xb) )
      {
         // keep only the roots that are within the limits of the spline segment
         CComPtr<IPoint2d> p;
         p.CoCreateInstance(CLSID_Point2d);
         p->Move(x[i]+xa,Evaluate(x[i]+xa));

         switch(i)
         {
         case 0:
            (*p1) = p;
            (*p1)->AddRef();
            break;
         case 1:
            (*p2) = p;
            (*p2)->AddRef();
            break;
         case 2:
            (*p3) = p;
            (*p3)->AddRef();
            break;
         default:
            ATLASSERT(false); // should never get here
         }
      }
   }
}

///////////////////////////////////////////////////////
CSplineSegmentLengthFunction::CSplineSegmentLengthFunction(const CSplineSegment& splineSegment) :
m_SplineSegment(splineSegment)
{
}

Float64 CSplineSegmentLengthFunction::Evaluate(Float64 x) const
{
   Float64 dy = m_SplineSegment.Slope(x);
   return sqrt(1 + dy*dy);
}


///////////////////////////////////////////////////////
CSplineSegmentPointFunction::CSplineSegmentPointFunction(Float64 distance,Float64 x0,const CSplineSegment& splineSegment) :
m_Distance(distance),
m_X0(x0),
m_SplineSegment(splineSegment)
{
}

Float64 CSplineSegmentPointFunction::Evaluate(Float64 x) const
{
   // solve (target distance - distance between [x0,x] along the spline curve) = 0
   //
   //        x
   //      /    __________
   // S -  |  \/(1 + dy^2) dx = 0
   //      /
   //       x0
   Float64 dist = x - m_X0;
   Float64 result = m_Distance - m_SplineSegment.Length(dist);
   return result;
}

/////////////////////////////////////////////////////////////

CSplineSegmentProjectPointFunction::CSplineSegmentProjectPointFunction(const CSplineSegment& splineSegment,IPoint2d* tp,IGeomUtil2d* gu) :
m_SplineSegment(splineSegment), m_TargetPoint(tp), m_GeomUtil(gu)
{
   m_Vector.CoCreateInstance(CLSID_Vector2d);
   m_Line.CoCreateInstance(CLSID_Line2d);
   m_Point.CoCreateInstance(CLSID_Point2d);
}

Float64 CSplineSegmentProjectPointFunction::Evaluate(Float64 s) const
{
   Float64 angle = m_SplineSegment.Normal(s);

   Float64 x,y;
   m_SplineSegment.GetPoint(s,&x,&y);
   m_Point->Move(x,y);

   m_Vector->put_Direction(angle);

   m_Line->SetExplicit(m_Point,m_Vector); // line that is normal to the curve at "s" from the start

   Float64 dist; // shortest distance between the target point and the normal line
   // > 0 if target point is on the right hand side of the normal line
   m_GeomUtil->ShortestDistanceToPoint(m_Line,m_TargetPoint,&dist);
   return dist;
}