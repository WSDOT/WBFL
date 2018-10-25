///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2013  Washington State Department of Transportation
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

// CogoEngine.cpp : Implementation of CCogoEngine
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CogoEngine.h"
#include "PointFactory.h"
#include "LineSegmentFactory.h"
#include "Angle.h"
#include "CogoHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCogoEngine

HRESULT CCogoEngine::FinalConstruct()
{
   HRESULT hr;

   // Geometry Utility Object
   hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   if ( FAILED(hr) )
      return hr;
 
   CComQIPtr<IGeomUtil> gu(m_GeomUtil);

   // Add a point factory to it
   CComObject<CPointFactory>* pPointFactory;
   CComObject<CPointFactory>::CreateInstance(&pPointFactory);
   gu->putref_Point2dFactory(pPointFactory);
 
   // Add a line segment factory to it
   CComObject<CLineSegmentFactory>* pLineSegmentFactory;
   CComObject<CLineSegmentFactory>::CreateInstance(&pLineSegmentFactory);
   gu->putref_LineSegment2dFactory(pLineSegmentFactory);

   return S_OK;
}

STDMETHODIMP CCogoEngine::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICogoEngine,
      &IID_IIntersect2,
      &IID_ILocate2,
      &IID_IMeasure2,
      &IID_IProject2,
      &IID_IDivide2,
      &IID_ITangent2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////
// Helper Methods

HRESULT CCogoEngine::CreateParallelLine(IPoint2d* pnt,IDirection* objDir,Float64 offset,ILine2d** line)
{
   // Save the direction of the line before it is altered.
   Float64 dir;
   objDir->get_Value(&dir);

   // Get the offset point for line
   CComPtr<IPoint2d> pntLine;
   CComPtr<IDirection> objClone;
   objDir->Clone(&objClone);
   objClone->IncrementBy(CComVariant(-PI_OVER_2));
   
   CComPtr<IPoint2dFactory> factory;
   get_PointFactory(&factory);

   HRESULT hr = cogoUtil::LocateByDistDir(pnt,offset,objClone,0.0,factory,&pntLine);
   ATLASSERT(SUCCEEDED(hr));

   // Create a vector in the direction of line
   CComPtr<IVector2d> vec;
   vec.CoCreateInstance(CLSID_Vector2d);
   vec->put_X(cos(dir));
   vec->put_Y(sin(dir));

   // Create line
   CComPtr<ILine2d> newLine;
   newLine.CoCreateInstance(CLSID_Line2d);
   newLine->SetExplicit(pntLine,vec);

   *line = newLine;
   (*line)->AddRef();

   return S_OK;
}


STDMETHODIMP CCogoEngine::get_Intersect(/*[out, retval]*/ IIntersect2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IIntersect2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::get_Locate(/*[out, retval]*/ ILocate2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_ILocate2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::get_Measure(/*[out, retval]*/ IMeasure2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IMeasure2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::get_Project(/*[out, retval]*/ IProject2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IProject2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::get_Divide(/*[out, retval]*/ IDivide2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IDivide2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::get_Tangent(/*[out, retval]*/ ITangent2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_ITangent2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::putref_PointFactory(/*[in]*/IPoint2dFactory* factory)
{
   CHECK_IN(factory);
   CComQIPtr<IGeomUtil> gu(m_GeomUtil);

   CComQIPtr<IPoint2dFactory> factory2d(factory);
   if ( factory2d == NULL )
      return E_FAIL; // object must also support IPoint2dFactory

   gu->putref_Point2dFactory(factory2d);

   return S_OK;
}

STDMETHODIMP CCogoEngine::get_PointFactory(/*[out,retval]*/ IPoint2dFactory** factory)
{
   CHECK_RETOBJ(factory);
   CComQIPtr<IGeomUtil> gu(m_GeomUtil);
   CComPtr<IPoint2dFactory> f;
   gu->get_Point2dFactory(&f);
   f.QueryInterface(factory);
   ATLASSERT( factory != NULL ); // There should be no way for anything other than an Ex factory
                                 // to get in here
   return S_OK;
}

STDMETHODIMP CCogoEngine::putref_LineSegmentFactory(/*[in]*/ ILineSegment2dFactory* factory)
{
   CHECK_IN(factory);
   CComQIPtr<IGeomUtil> gu(m_GeomUtil);

   CComQIPtr<ILineSegment2dFactory> factory2d(factory);
   if ( factory2d == NULL )
      return E_FAIL; // object must also support IPoint2dFactory

   gu->putref_LineSegment2dFactory(factory2d);

   return S_OK;
}

STDMETHODIMP CCogoEngine::get_LineSegmentFactory(/*[out,retval]*/ILineSegment2dFactory** factory)
{
   CHECK_RETOBJ(factory);
   CComQIPtr<IGeomUtil> gu(m_GeomUtil);
   CComQIPtr<ILineSegment2dFactory> f;
   gu->get_LineSegment2dFactory(&f);
   f.QueryInterface(factory);
   ATLASSERT( factory != NULL ); // There should be no way for anything other than an Ex factory
                                 // to get in here
   return S_OK;
}

STDMETHODIMP CCogoEngine::Angle(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* vertex,/*[in]*/ IPoint2d* to,/*[out,retval]*/ IAngle** angle)
{
   CHECK_IN(from);
   CHECK_IN(vertex);
   CHECK_IN(to);
   CHECK_RETOBJ(angle);

   HRESULT hr;

   Float64 val;
   hr = m_GeomUtil->Angle(from,vertex,to,&val);
   if ( FAILED(hr) )
   {
      return Error(IDS_E_ANGLE,IID_IMeasure2,COGO_E_ANGLE);
   }

   CComObject<CAngle>* pAngle;
   CComObject<CAngle>::CreateInstance(&pAngle);
   pAngle->put_Value(val);
   pAngle->QueryInterface(angle);

   return S_OK;
}

STDMETHODIMP CCogoEngine::Area(/*[in]*/ IPoint2dCollection* points,/*[out,retval]*/ Float64* area)
{
   CHECK_IN(points);
   CHECK_RETVAL(area);

   // We will use a polyshape object from the Geometry library
   // to compute the area. Create the object here
   CComPtr<IPolyShape> polyshape;
   polyshape.CoCreateInstance(CLSID_PolyShape);
   polyshape->AddPoints(points);

   CComQIPtr<IShape> shape(polyshape);
   CComPtr<IShapeProperties> props;
   shape->get_ShapeProperties(&props);
   props->get_Area(area);

   return S_OK;
}

STDMETHODIMP CCogoEngine::Distance(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to,/*[out,retval]*/ Float64* dist)
{
   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETVAL(dist);
 
   HRESULT hr = m_GeomUtil->Distance(from,to,dist);
   return hr;
}

STDMETHODIMP CCogoEngine::Direction(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to,/*[out,retval]*/ IDirection** dir)
{
   Float64 dist;
   return Inverse(from,to,&dist,dir);
}

STDMETHODIMP CCogoEngine::Inverse(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to,/*[out]*/ Float64* dist,/*[out]*/ IDirection** dir)
{
   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETVAL(dist);
   CHECK_RETOBJ(dir);

   cogoUtil::Inverse(from,to,dist,dir);

   return S_OK;
}

STDMETHODIMP CCogoEngine::ByDistAngle(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varAngle, /*[in]*/ Float64 offset,/*[out,retval]*/IPoint2d** point)
{
   /////////////////////////////////////////////////
   // NOTE: This method is very similar to ByDistDefAngle
   //       If changes need to be made here, look at
   //       ByDistDefAngle because similar changes may need to
   //       be made there as well
   /////////////////////////////////////////////////

   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETOBJ(point);


   CComPtr<IAngle> angle;
   HRESULT hr = cogoUtil::AngleFromVariant(varAngle,&angle);
   if ( FAILED(hr) )
      return hr;

   // Get Direction of line going from to towards from (backsight bearing)
   // Then turn a 90 angle. This will be the normal to the line, in the direction 
   // of positive offset
   CComPtr<IDirection> brgBacksight;
   CComPtr<IDirection> brgNormal;
   hr = Direction(to,from,&brgBacksight); // this is the backsight bearing
   if ( FAILED(hr) )
      return hr;

   hr = Direction(to,from,&brgNormal); // this is the backsight bearing
   if ( FAILED(hr) )
      return hr;
   brgNormal->IncrementBy(CComVariant(PI_OVER_2)); // now it is the normal

   CComPtr<IPoint2dFactory> factory;
   get_PointFactory(&factory);

   // Locate a point at the desired offset
   // This will be the reference point from which we locate the
   // desired point
   CComPtr<IPoint2d> refPnt;
   hr = cogoUtil::LocateByDistDir(to,offset,brgNormal,0.00,factory,&refPnt);
   ATLASSERT(SUCCEEDED(hr));

   // Locate the new point
   // Bearing of line is the backsight bearing plus the angle
   brgBacksight->IncrementBy(CComVariant(angle));
   CComPtr<IPoint2d> newPnt;
   hr = cogoUtil::LocateByDistDir(refPnt,dist,brgBacksight,0.00,factory,&newPnt);
   ATLASSERT(SUCCEEDED(hr));

   (*point) = newPnt;
   (*point)->AddRef();

   return S_OK;
}

STDMETHODIMP CCogoEngine::ByDistDefAngle(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* to, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDefAngle, /*[in]*/ Float64 offset, /*[out,retval]*/ IPoint2d** point)
{
   /////////////////////////////////////////////////
   // NOTE: This method is very similar to ByDistAngle
   //       If changes need to be made here, look at
   //       ByDistAngle because similar changes may need to
   //       be made there as well
   /////////////////////////////////////////////////

   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETOBJ(point);


   CComPtr<IAngle> defAngle;
   HRESULT hr = cogoUtil::AngleFromVariant(varDefAngle,&defAngle);
   if ( FAILED(hr) )
      return hr;

   // Get Direction of line going from to towards from (backsight bearing)
   // Then turn a 90 angle. This will be the normal to the line, in the direction 
   // of positive offset
   CComPtr<IDirection> brgBacksight;
   hr = Direction(to,from,&brgBacksight); // this is the backsight bearing
   if ( FAILED(hr) )
      return hr;

   CComPtr<IDirection> brgNormal;
   hr = Direction(to,from,&brgNormal); // this is the backsight bearing
   if ( FAILED(hr) )
      return hr;

   brgNormal->IncrementBy(CComVariant(PI_OVER_2)); // now it is the normal

   CComPtr<IPoint2dFactory> factory;
   get_PointFactory(&factory);

   // Locate a point at the desired offset
   // This will be the reference point from which we locate the
   // desired point
   CComPtr<IPoint2d> refPnt;
   hr = cogoUtil::LocateByDistDir(to,offset,brgNormal,0.00,factory,&refPnt);
   ATLASSERT(SUCCEEDED(hr));

   // Locate the new point
   // Bearing of line is the backsight bearing plus the angle + 180def
   Float64 dir;
   defAngle->get_Value(&dir);
   dir += M_PI;
   brgBacksight->IncrementBy(CComVariant(dir));
   CComPtr<IPoint2d> newPnt;
   hr = cogoUtil::LocateByDistDir(refPnt,dist,brgBacksight,0.00,factory,&newPnt);
   ATLASSERT(SUCCEEDED(hr));

   (*point) = newPnt;
   (*point)->AddRef();

   return S_OK;
}

STDMETHODIMP CCogoEngine::ByDistDir(/*[in]*/ IPoint2d* from, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset,/*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(from);
   CHECK_RETOBJ(point);

   HRESULT hr;

   CComPtr<IDirection> dir;
   hr = cogoUtil::DirectionFromVariant(varDir,&dir);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2dFactory> factory;
   get_PointFactory(&factory);

   hr = cogoUtil::LocateByDistDir(from,dist,dir,offset,factory,point);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoEngine::PointOnLine(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* to, /*[in]*/ Float64 dist, /*[in]*/ Float64 offset,/*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETOBJ(point);

   HRESULT hr;

   // Get the bearing of the line going from "from" to "to"
   CComPtr<IDirection> brgLine, brgNormal;
   hr = Direction(from,to,&brgLine);
   hr = Direction(from,to,&brgNormal);
   ATLASSERT(SUCCEEDED(hr));

   // Get the value and subtract 90deg to get the direction of the
   // right normal of the line
   brgNormal->IncrementBy(CComVariant(-PI_OVER_2));

   CComPtr<IPoint2dFactory> factory;
   get_PointFactory(&factory);

   // Locate the offset "from" point
   CComPtr<IPoint2d> pntOffset;
   cogoUtil::LocateByDistDir(from,offset,brgNormal,0.00,factory,&pntOffset);
   ATLASSERT(SUCCEEDED(hr));

   // Locate the point
   hr = cogoUtil::LocateByDistDir(pntOffset,dist,brgLine,0.00,factory,point);
   ATLASSERT(SUCCEEDED(hr));

   return S_OK;
}

STDMETHODIMP CCogoEngine::ParallelLineByPoints(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to, /*[in]*/ Float64 offset,/*[out]*/IPoint2d** p1,/*[out]*/IPoint2d** p2)
{
   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETOBJ(p1);
   CHECK_RETOBJ(p2);

   HRESULT hr;

   CComPtr<ILineSegment2d> seg;
   seg.CoCreateInstance(CLSID_LineSegment2d);
   seg->putref_StartPoint(from);
   seg->putref_EndPoint(to);

   CComPtr<ILineSegment2d> newLS;
   hr = m_GeomUtil->CreateParallelLineSegment(seg,offset,&newLS);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pnt1, pnt2;
   newLS->get_StartPoint(&pnt1);
   newLS->get_EndPoint(&pnt2);

   pnt1.QueryInterface(p1);
   pnt2.QueryInterface(p2);

   return S_OK;
}

STDMETHODIMP CCogoEngine::ParallelLineSegment(/*[in]*/ ILineSegment2d* line,/*[in]*/ Float64 offset,/*[out,retval]*/ ILineSegment2d** linesegment)
{
   CHECK_IN(line);
   CHECK_RETOBJ(linesegment);

   HRESULT hr;

   CComPtr<ILineSegment2d> l;
   hr = m_GeomUtil->CreateParallelLineSegment(line,offset,&l);
   if ( FAILED(hr) )
      return hr;

   l.QueryInterface(linesegment);

   return S_OK;
}

STDMETHODIMP CCogoEngine::Bearings(/*[in]*/ IPoint2d* p1, /*[in]*/ VARIANT varDir1, /*[in]*/ Float64 offset1,/*[in]*/ IPoint2d* p2, /*[in]*/ VARIANT varDir2, /*[in]*/ Float64 offset2, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   CHECK_RETOBJ(point);

   HRESULT hr;

   // Get the input data and validate
   CComPtr<IPoint2d> pnt[2];
   pnt[0] = p1;
   pnt[1] = p2;

   CComPtr<IDirection> dir[2];
   hr = cogoUtil::DirectionFromVariant(varDir1,&dir[0]);
   if ( FAILED(hr) )
      return hr;

   hr = cogoUtil::DirectionFromVariant(varDir2,&dir[1]);
   if ( FAILED(hr) )
      return hr;

   Float64 offset[2];
   offset[0] = offset1;
   offset[1] = offset2;

   CComPtr<ILine2d> line[2];
   for ( long i = 0; i < 2; i++ )
   {
      CreateParallelLine(pnt[i],dir[i],offset[i],&line[i]);
   }

   // Intersect the lines
   CComPtr<IPoint2d> p;
   hr = m_GeomUtil->LineLineIntersect(line[0],line[1],&p);
   if ( FAILED(hr) )
      return hr;

   if ( p != NULL )
   {
      p->QueryInterface(point);
   }
   else
   {
      *point = NULL;
   }

   return S_OK;
}

STDMETHODIMP CCogoEngine::BearingCircle(/*[in]*/ IPoint2d* pnt1, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset,/*[in]*/ IPoint2d* pntCenter, /*[in]*/ Float64 radius, /*[in]*/ IPoint2d* pntNearest, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(pnt1);
   CHECK_IN(pntCenter);
   CHECK_IN(pntNearest);
   CHECK_RETOBJ(point);

   if ( radius <= 0.0 )
      return Error(IDS_E_RADIUS,IID_IIntersect,COGO_E_RADIUS);

   // Get the input data and validate
   HRESULT hr;


   CComPtr<IDirection> dir;
   hr = cogoUtil::DirectionFromVariant(varDir,&dir);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ILine2d> line;
   CreateParallelLine(pnt1,dir,offset,&line);

   CComPtr<ICircle> circle;
   circle.CoCreateInstance(CLSID_Circle);
   circle->putref_Center(pntCenter);
   circle->put_Radius(radius);

   CComPtr<IPoint2d> p1, p2;
   short nIntersect;
   m_GeomUtil->LineCircleIntersect(line,circle,&p1,&p2,&nIntersect);

   if ( nIntersect == 0 )
   {
      (*point) = 0;
   }
   else if ( nIntersect == 1 )
   {
      p1.QueryInterface(point);
   }
   else
   {
      ATLASSERT(nIntersect == 2);

      Float64 d1, d2;
      m_GeomUtil->Distance(pntNearest,p1,&d1);
      m_GeomUtil->Distance(pntNearest,p2,&d2);

      if ( d2 < d1 )
      {
         p2.QueryInterface(point);
      }
      else
      {
         p1.QueryInterface(point);
      }
   }

   return S_OK;
}

STDMETHODIMP CCogoEngine::Circles(/*[in]*/ IPoint2d* c1, /*[in]*/ Float64 r1, /*[in]*/ IPoint2d* c2, /*[in]*/ Float64 r2, /*[in]*/ IPoint2d* nearest, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(c1);
   CHECK_IN(c2);
   CHECK_IN(nearest);
   CHECK_RETOBJ(point);

   if ( r1 <= 0.0 || r2 <= 0.0 )
      return Error(IDS_E_RADIUS,IID_IIntersect,COGO_E_RADIUS);


   CComPtr<ICircle> circle1;
   circle1.CoCreateInstance(CLSID_Circle);
   circle1->putref_Center(c1);
   circle1->put_Radius(r1);

   CComPtr<ICircle> circle2;
   circle2.CoCreateInstance(CLSID_Circle);
   circle2->putref_Center(c2);
   circle2->put_Radius(r2);

   CComPtr<IPoint2d> p1, p2;
   short nIntersect;
   m_GeomUtil->CircleCircleIntersect(circle1,circle2,&p1,&p2,&nIntersect);

   if ( nIntersect == 0 )
   {
      (*point) = 0;
   }
   else if ( nIntersect == 1 )
   {
      p1.QueryInterface(point);
   }
   else
   {
      ATLASSERT(nIntersect == 2);

      Float64 d1, d2;
      m_GeomUtil->Distance(nearest,p1,&d1);
      m_GeomUtil->Distance(nearest,p2,&d2);

      if ( d2 < d1 )
      {
         p2.QueryInterface(point);
      }
      else
      {
         p1.QueryInterface(point);
      }
   }

   return S_OK;
}

STDMETHODIMP CCogoEngine::LineByPointsCircle(/*[in]*/ IPoint2d* pnt1, /*[in]*/ IPoint2d* pnt2, /*[in]*/ Float64 offset,/*[in]*/ IPoint2d* center, /*[in]*/ Float64 radius, /*[in]*/ IPoint2d* nearest, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(pnt1);
   CHECK_IN(pnt2);
   CHECK_IN(center);
   CHECK_IN(nearest);
   CHECK_RETOBJ(point);

   if ( radius <= 0.0 )
      return Error(IDS_E_RADIUS,IID_IIntersect,COGO_E_RADIUS);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->ThroughPoints(pnt1,pnt2);
   CComPtr<ILine2d> offsetLine;
   m_GeomUtil->CreateParallelLine(line,offset,&offsetLine);

   CComPtr<ICircle> circle;
   circle.CoCreateInstance(CLSID_Circle);
   circle->putref_Center(center);
   circle->put_Radius(radius);

   CComPtr<IPoint2d> p1, p2;
   short nIntersect;
   m_GeomUtil->LineCircleIntersect(offsetLine,circle,&p1,&p2,&nIntersect);

   if ( nIntersect == 0 )
   {
      (*point) = 0;
   }
   else if ( nIntersect == 1 )
   {
      p1.QueryInterface(point);
   }
   else
   {
      ATLASSERT(nIntersect == 2);

      Float64 d1, d2;
      m_GeomUtil->Distance(nearest,p1,&d1);
      m_GeomUtil->Distance(nearest,p2,&d2);

      if ( d2 < d1 )
      {
         p2.QueryInterface(point);
      }
      else
      {
         p1.QueryInterface(point);
      }
   }

   return S_OK;
}

STDMETHODIMP CCogoEngine::LinesByPoints(/*[in]*/ IPoint2d* p11, /*[in]*/ IPoint2d* p12, /*[in]*/ Float64 offset1,/*[in]*/ IPoint2d* p21, /*[in]*/ IPoint2d* p22, /*[in]*/ Float64 offset2, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(p11);
   CHECK_IN(p12);
   CHECK_IN(p21);
   CHECK_IN(p22);
   CHECK_RETOBJ(point);

   HRESULT hr;

   CComPtr<ILine2d> line1;
   line1.CoCreateInstance(CLSID_Line2d);
   line1->ThroughPoints(p11,p12);
   CComPtr<ILine2d> offsetLine1;
   m_GeomUtil->CreateParallelLine(line1,offset1,&offsetLine1);

   CComPtr<ILine2d> line2;
   line2.CoCreateInstance(CLSID_Line2d);
   line2->ThroughPoints(p21,p22);
   CComPtr<ILine2d> offsetLine2;
   m_GeomUtil->CreateParallelLine(line2,offset2,&offsetLine2);

   CComPtr<IPoint2d> pnt;
   hr = m_GeomUtil->LineLineIntersect(offsetLine1,offsetLine2,&pnt);

   if ( pnt != NULL )
      pnt.QueryInterface(point);
   else
      (*point) = NULL;

   return S_OK;
}

STDMETHODIMP CCogoEngine::Lines(/*[in]*/ILineSegment2d* l1,/*[in]*/Float64 offset1,/*[in]*/ILineSegment2d* l2,/*[in]*/Float64 offset2,/*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(l1);
   CHECK_IN(l2);
   CHECK_RETOBJ(point);

   HRESULT hr;


   CComPtr<IPoint2d> start, end;
   l1->get_StartPoint(&start);
   l1->get_EndPoint(&end);
   CComPtr<ILine2d> line1;
   line1.CoCreateInstance(CLSID_Line2d);
   line1->ThroughPoints(start,end);

   CComPtr<ILine2d> offsetLine1;
   m_GeomUtil->CreateParallelLine(line1,offset1,&offsetLine1);

   start.Release();
   end.Release();
   l2->get_StartPoint(&start);
   l2->get_EndPoint(&end);
   CComPtr<ILine2d> line2;
   line2.CoCreateInstance(CLSID_Line2d);
   line2->ThroughPoints(start,end);

   CComPtr<ILine2d> offsetLine2;
   m_GeomUtil->CreateParallelLine(line2,offset2,&offsetLine2);

   CComPtr<IPoint2d> pnt;
   hr = m_GeomUtil->LineLineIntersect(offsetLine1,offsetLine2,&pnt);
   if ( FAILED(hr) )
      return hr;

   if ( pnt != NULL )
      pnt.QueryInterface(point);
   else
      (*point) = NULL;

   return S_OK;
}

STDMETHODIMP CCogoEngine::LineSegmentCircle(/*[in]*/ ILineSegment2d* seg, /*[in]*/ Float64 offset,/*[in]*/ IPoint2d* center, /*[in]*/ Float64 radius, /*[in]*/ IPoint2d* nearest, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(seg);
   CHECK_IN(center);
   CHECK_IN(nearest);
   CHECK_RETOBJ(point);

   if ( radius <= 0 )
      return Error(IDS_E_RADIUS,IID_ILocate,COGO_E_RADIUS);

   CComPtr<IPoint2d> start, end;
   seg->get_StartPoint(&start);
   seg->get_EndPoint(&end);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->ThroughPoints(start,end);
   CComPtr<ILine2d> offsetLine;
   m_GeomUtil->CreateParallelLine(line,offset,&offsetLine);

   CComPtr<ICircle> circle;
   circle.CoCreateInstance(CLSID_Circle);
   circle->putref_Center(center);
   circle->put_Radius(radius);

   CComPtr<IPoint2dFactory> factory;
   get_PointFactory(&factory);

   cogoUtil::LineCircleIntersect(offsetLine,circle,nearest,factory,point);

   return S_OK;
}

STDMETHODIMP CCogoEngine::PointOnLineByPoints(/*[in]*/ IPoint2d* pnt, /*[in]*/ IPoint2d* start, /*[in]*/ IPoint2d* end, /*[in]*/ Float64 offset,/*[out,retval]*/IPoint2d** point)
{
   CHECK_IN(pnt);
   CHECK_IN(start);
   CHECK_IN(end);
   CHECK_RETOBJ(point);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->ThroughPoints(start,end);

   CComPtr<ILine2d> offsetLine;
   m_GeomUtil->CreateParallelLine(line,offset,&offsetLine);

   CComPtr<IPoint2d> p;
   m_GeomUtil->PointOnLineNearest(offsetLine,pnt,&p);
   p.QueryInterface(point);

   return S_OK;
}

STDMETHODIMP CCogoEngine::PointOnLineSegment(/*[in]*/ IPoint2d* from,/*[in]*/ ILineSegment2d* seg, /*[in]*/ Float64 offset, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(from);
   CHECK_IN(seg);
   CHECK_RETOBJ(point);

   CComPtr<IPoint2d> start,end;
   seg->get_StartPoint(&start);
   seg->get_EndPoint(&end);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->ThroughPoints(start,end);

   CComPtr<ILine2d> offsetLine;
   m_GeomUtil->CreateParallelLine(line,offset,&offsetLine);

   CComPtr<IPoint2d> pnt;
   m_GeomUtil->PointOnLineNearest(offsetLine,from,&pnt);
   pnt.QueryInterface(point);

   return S_OK;
}

STDMETHODIMP CCogoEngine::PointOnCurve(/*[in]*/ IPoint2d* pnt, /*[in]*/ IHorzCurve* curve,/*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(pnt);
   CHECK_IN(curve);
   CHECK_RETOBJ(point);

   return curve->ProjectPoint(pnt,point);
}

STDMETHODIMP CCogoEngine::Arc(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* vertex, /*[in]*/ IPoint2d* to,/*[in]*/ CollectionIndexType nParts,/*[out,retval]*/ IPoint2dCollection** points)
{
   CHECK_IN(from);
   CHECK_IN(vertex);
   CHECK_IN(to);
   CHECK_RETVAL(points);

   if ( nParts <= 1 )
      return E_INVALIDARG;

   Float64 d1, d2, d3;
   m_GeomUtil->Distance(from,vertex,&d1);
   m_GeomUtil->Distance(from,to,&d2);
   m_GeomUtil->Distance(vertex,to,&d3);
   if ( IsZero(d1) || IsZero(d2) || IsZero(d3) )
   {
      return Error(IDS_E_ANGLE,IID_IDivide,COGO_E_ANGLE);
   }


   // Divide the arc
   // The resulting collection contains the from and to points
   // Be sure not to add these points to the collection
   HRESULT hr = m_GeomUtil->DivideArc(from,vertex,to,nParts,points);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoEngine::BetweenPoints(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* to,/*[in]*/ CollectionIndexType nParts,/*[out,retval]*/ IPoint2dCollection** points)
{
   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETOBJ(points);

   if ( nParts <= 1 )
      return E_INVALIDARG;

   HRESULT hr;

   // Divide the line
   // The resulting collection contains the from and to points
   // Be sure not to add these points to the collection
   CComPtr<ILineSegment2d> seg;
   seg.CoCreateInstance(CLSID_LineSegment2d); // we have to create a line segment first
   seg->putref_StartPoint(from);
   seg->putref_EndPoint(to);

   hr = m_GeomUtil->DivideLineSegment(seg,nParts,points);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoEngine::LineSegment(/*[in]*/ ILineSegment2d* seg,/*[in]*/ CollectionIndexType nParts,/*[out,retval]*/ IPoint2dCollection** points)
{
   CHECK_IN(seg);
   CHECK_RETOBJ(points);

   if ( nParts <= 1 )
      return E_INVALIDARG;

   HRESULT hr;

   // Divide the line
   // The resulting collection contains the from and to points
   // Be sure not to add these points to the collection
   hr = m_GeomUtil->DivideLineSegment(seg,nParts,points);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoEngine::HorzCurve(/*[in]*/ IHorzCurve* curve, /*[in]*/ CollectionIndexType nParts, /*[out,retval]*/ IPoint2dCollection** points)
{
   CHECK_IN(curve);
   CHECK_RETOBJ(points);

   if ( nParts <= 1 )
      return E_INVALIDARG;

   HRESULT hr;

   // Divide the curve
   Float64 Lt; // Total length of curve
   curve->get_TotalLength(&Lt);

   hr = ::CoCreateInstance(CLSID_Point2dCollection,NULL,CLSCTX_ALL,IID_IPoint2dCollection,(void**)points);
   ATLASSERT(SUCCEEDED(hr));

   Float64 stepSize = Lt/nParts;
   Float64 currDist = stepSize;
   for ( CollectionIndexType i = 0; i < nParts-1; i++ )
   {
      CComPtr<IPoint2d> point;
      curve->PointOnCurve(currDist,&point);

      (*points)->Add(point);

      currDist += stepSize;
   }

   return S_OK;
}

STDMETHODIMP CCogoEngine::Path(IPath* pPath,CollectionIndexType nParts,Float64 start,Float64 end,IPoint2dCollection** points)
{
   CHECK_IN(pPath);
   CHECK_RETOBJ(points);

   if ( nParts <= 1 )
      return E_INVALIDARG;

   HRESULT hr = ::CoCreateInstance(CLSID_Point2dCollection,NULL,CLSCTX_ALL,IID_IPoint2dCollection,(void**)points);
   ATLASSERT(SUCCEEDED(hr));


   Float64 distance = end - start;
   Float64 stepSize = distance/nParts;
   Float64 location = stepSize + start;
   for ( CollectionIndexType i = 0; i < nParts-1; i++ )
   {
      CComPtr<IPoint2d> point;
      pPath->LocatePoint(location,omtNormal,0.0,CComVariant(0.00),&point);

      (*points)->Add(point);

      location += stepSize;
   }

   return S_OK;
}

STDMETHODIMP CCogoEngine::External(/*[in]*/ IPoint2d* center1, /*[in]*/ Float64 radius1,/*[in]*/ IPoint2d* center2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign, /*[out]*/ IPoint2d** t1,/*[out]*/ IPoint2d** t2)
{
   // Check the radii
   if ( radius1 <= 0.0 )
      return Error(IDS_E_RADIUS,IID_ITangent,COGO_E_RADIUS);

   if ( radius2 <= 0.0 )
      return Error(IDS_E_RADIUS,IID_ITangent,COGO_E_RADIUS);


   CComPtr<IPoint2d> A, B; // center points of circle A and B. Circle A is the one with the larger radius
   Float64 Ar, Br; // Radius of circle A and B
   if ( radius2 <= radius1 )
   {
      A = center1;
      Ar = radius1;

      B = center2;
      Br = radius2;
   }
   else
   {
      A = center2;
      Ar = radius2;

      B = center1;
      Br = radius1;
   }

   Float64 JG;
   JG = Ar - Br;


   // Compute "delta". The angle of the line connecting the centers of the circle
   Float64 Ax,Ay, Bx,By;
   A->get_X(&Ax);
   A->get_Y(&Ay);
   B->get_X(&Bx);
   B->get_Y(&By);

   Float64 delta;
   Float64 dx = Bx - Ax;
   Float64 dy = By - Ay;
   delta = atan2(dy,dx);
   delta = cogoUtil::NormalizeAngle(delta);

   // Compute "theta". The angle formed by the line connecting the centers of the circles and
   // the line line connection the center of one circle and the tangent point on that circle
   Float64 JH = sqrt(dx*dx + dy*dy);
   if ( IsZero(JH) )
      return Error(IDS_E_COINCIDENTPOINTS,IID_ITangent,COGO_E_COINCIDENTPOINTS);

   Float64 JG_JH = JG/JH;
   if ( IsZero(JG_JH - 1.0) )
      JG_JH = 1.0;

   Float64 theta = acos(JG_JH);

   if ( sign == tsCCW )
      theta *= -1;

   Float64 Gx, Gy;
   Float64 Hx, Hy;

   Gx = Ax + Ar*cos(theta+delta);
   Gy = Ay + Ar*sin(theta+delta);

   Hx = Bx + Br*cos(theta+delta);
   Hy = By + Br*sin(theta+delta);

   // create the two new points
   CComPtr<IPoint2dFactory> factory;
   get_PointFactory(&factory);

   CComPtr<IPoint2d> p1, p2;
   factory->CreatePoint(t1);
   factory->CreatePoint(t2);

   (*t1)->Move(Gx,Gy);
   (*t2)->Move(Hx,Hy);

   return S_OK;
}

STDMETHODIMP CCogoEngine::Cross(/*[in]*/ IPoint2d* center1, /*[in]*/ Float64 radius1,/*[in]*/ IPoint2d* center2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign, /*[out]*/ IPoint2d** t1,/*[out]*/ IPoint2d** t2)
{
   CHECK_IN(center1);
   CHECK_IN(center2);
   CHECK_RETOBJ(t1);
   CHECK_RETOBJ(t2);

   // Check the radii
   if ( radius1 <= 0.0 )
      return Error(IDS_E_RADIUS,IID_ITangent,COGO_E_RADIUS);

   if ( radius2 <= 0.0 )
      return Error(IDS_E_RADIUS,IID_ITangent,COGO_E_RADIUS);

   // Compute "delta". The angle of the line connecting the centers of the circle
   Float64 Ax,Ay, Bx,By;
   center1->get_X(&Ax);
   center1->get_Y(&Ay);
   center2->get_X(&Bx);
   center2->get_Y(&By);

   Float64 delta;
   Float64 dx = Bx - Ax;
   Float64 dy = By - Ay;
   delta = atan2(dy,dx);
   delta = cogoUtil::NormalizeAngle(delta);

   // Compute "theta". The angle formed by the line connecting the centers of the circles and
   // the line line connection the center of one circle and the tangent point on that circle
   Float64 d = sqrt(dx*dx + dy*dy);
   if ( IsZero(d) )
      return Error(IDS_E_COINCIDENTPOINTS,IID_ITangent,COGO_E_COINCIDENTPOINTS);

   Float64 x = radius1/(d*radius1/(radius1 + radius2));
   if ( IsZero(x-1.0) )
       x = 1.0;

   Float64 theta = acos(x);

   Float64 sG,sH;
   if ( sign == tsCCW )
   {
      sG = -1;
      sH =  1;
   }
   else
   {
      sG =  1;
      sH = -1;
   }

   Float64 Gx, Gy;
   Float64 Hx, Hy;

   Gx = Ax + radius1*cos(sG*theta+delta);
   Gy = Ay + radius1*sin(sG*theta+delta);

   Hx = Bx + radius2*cos(sH*theta+delta);
   Hy = By + radius2*sin(sH*theta+delta);

   // create the two new points
   CComPtr<IPoint2dFactory> factory;
   get_PointFactory(&factory);

   CComPtr<IPoint2d> p1, p2;
   factory->CreatePoint(t1);
   factory->CreatePoint(t2);

   (*t1)->Move(Gx,Gy);
   (*t2)->Move(Hx,Hy);

   return S_OK;
}

STDMETHODIMP CCogoEngine::Point(/*[in]*/ IPoint2d* center, /*[in]*/ Float64 radius,/*[in]*/ IPoint2d* point, /*[in]*/ TangentSignType sign, /*[out]*/ IPoint2d** tangent)
{
   CHECK_IN(center);
   CHECK_IN(point);
   CHECK_RETOBJ(tangent);

   // Check the radii
   if ( radius <= 0.0 )
      return Error(IDS_E_RADIUS,IID_ITangent,COGO_E_RADIUS);

   // Compute "delta". The angle of the line connecting the centers of the circle
   Float64 Ax,Ay, Bx,By;
   center->get_X(&Ax);
   center->get_Y(&Ay);
   point->get_X(&Bx);
   point->get_Y(&By);

   Float64 delta;
   Float64 dx = Bx - Ax;
   Float64 dy = By - Ay;
   delta = atan2(dy,dx);
   delta = cogoUtil::NormalizeAngle(delta);

   // Compute "theta". The angle formed by the line connecting the center of the circle and
   // the tangent point
   Float64 d = sqrt(dx*dx + dy*dy);
   if ( IsZero(d) )
      return Error(IDS_E_COINCIDENTPOINTS,IID_ITangent,COGO_E_COINCIDENTPOINTS);

   if ( d <= radius )
      return Error(IDS_E_POINTINCIRCLE,IID_ITangent,COGO_E_POINTINCIRCLE);

   Float64 x = radius/d;
   if ( IsZero(x-1.0) )
      x = 1.0;
   Float64 theta = acos(x);

   Float64 sG;
   if ( sign == tsCCW )
   {
      sG = -1;
   }
   else
   {
      sG =  1;
   }

   Float64 Gx, Gy;

   Gx = Ax + radius*cos(sG*theta+delta);
   Gy = Ay + radius*sin(sG*theta+delta);

   // create the two new points
   CComPtr<IPoint2dFactory> factory;
   get_PointFactory(&factory);

   factory->CreatePoint(tangent);

   (*tangent)->Move(Gx,Gy);

   return S_OK;
}


