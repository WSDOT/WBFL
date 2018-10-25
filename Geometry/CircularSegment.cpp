///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// CircularSegment.cpp : Implementation of CCircularSegment
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "CircularSegment.h"
#include "Helper.h"
#include <MathEx.h> // for InRange
#include <xutility> // for _cpp_min and _cpp_max
#include <WBFLTools.h> // for Mohr's Circle

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCircularSegment
HRESULT CCircularSegment::FinalConstruct()
{
   CreatePoint( 0.00, 0.00, NULL, &m_Center );
   HRESULT hr = CrAdvise(m_Center, this, IID_IPoint2dEvents, &m_CenterPointCookie);
   if (FAILED(hr))
      return hr;

   CreatePoint( 0.00, 0.00, NULL, &m_HookPoint );
   hr = CrAdvise(m_HookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   m_Radius = 0.00;
   m_MO = 0.00;
   m_Rotation = 0.00;
   m_SquelchEvents=false;

   return S_OK;
}

void CCircularSegment::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_HookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));

   hr = CrUnadvise(m_Center, this, IID_IPoint2dEvents, m_CenterPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}


void CCircularSegment::AdjustHookPoint()
{
   Float64 cx, cy;
   GetCoordinates(m_Center,&cx,&cy);

   Float64 hx,hy;
   hx = cx + (m_Radius-m_MO)*cos(m_Rotation);
   hy = cy + (m_Radius-m_MO)*sin(m_Rotation);

   // don't want events firing and blowing our stack
   m_SquelchEvents = true;
   m_HookPoint->Move(hx,hy);
   m_SquelchEvents = false;
}

void CCircularSegment::AdjustCenterPoint()
{
   Float64 hx,hy;
   GetCoordinates(m_HookPoint,&hx,&hy);

   Float64 cx, cy;
   cx = hx - (m_Radius-m_MO)*cos(m_Rotation);
   cy = hy - (m_Radius-m_MO)*sin(m_Rotation);

   m_SquelchEvents = true;
   m_Center->Move(cx,cy);
   m_SquelchEvents = false;
}


HRESULT CCircularSegment::BoundaryLine(ILine2d** line)
{
   // Create the boundary line that forms the straight edge of the shape
   CreateLine(NULL,line);

   CComPtr<IPoint2d> p1;
   CComPtr<IPoint2d> p2;

   EdgePoints(&p1,&p2);

   (*line)->ThroughPoints(p1,p2);

   return S_OK;
}

HRESULT CCircularSegment::EdgePoints(IPoint2d** p1,IPoint2d** p2)
{
   Float64 cx,cy;
   GetCoordinates(m_Center,&cx,&cy);

   Float64 angle;
   get_InteriorAngle(&angle);

   if (IsEqual(angle,TWO_PI))
      angle -= 0.01; // Prevent the closed circle case

   Float64 x1,y1;
   Float64 x2,y2;

   x1 = cx + m_Radius * cos(m_Rotation - angle/2);
   y1 = cy + m_Radius * sin(m_Rotation - angle/2);

   x2 = cx + m_Radius * cos(m_Rotation + angle/2);
   y2 = cy + m_Radius * sin(m_Rotation + angle/2);

   CreatePoint(x1,y1,NULL,p1);
   CreatePoint(x2,y2,NULL,p2);

   // Both points can't be the same.
   ATLASSERT( IsZero(angle) ? (IsEqual(x1,x2) && IsEqual(y1,y2)) : !(IsEqual(x1,x2) && IsEqual(y1,y2)));

   return S_OK;
}

STDMETHODIMP CCircularSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICircularSegment,
      &IID_IShape,
      &IID_IXYPosition,
		&IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCircularSegment::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CCircularSegment::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

STDMETHODIMP CCircularSegment::get_HookPoint(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return m_HookPoint.CopyTo(pVal);
}

STDMETHODIMP CCircularSegment::putref_HookPoint(IPoint2d *newVal)
{
   HRESULT hr = CrAssignPointer(m_HookPoint, newVal, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   // adjust our center point to account for change in hook point
   AdjustCenterPoint();

   return S_OK;
}

STDMETHODIMP CCircularSegment::get_Radius(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Radius;
	return S_OK;
}

STDMETHODIMP CCircularSegment::put_Radius(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_RADIUS,IID_ICircularSegment,GEOMETRY_E_RADIUS);

   m_Radius = newVal;

   // If the radius got so small that MO is beyond the boundries
   // of the circle, move MO to the edge of the circle
   if ( m_MO > 2.0*m_Radius )
      m_MO = 2.0*m_Radius;

   AdjustHookPoint();

	return S_OK;
}

STDMETHODIMP CCircularSegment::get_Center(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return m_Center.CopyTo(pVal);
}

STDMETHODIMP CCircularSegment::putref_Center(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   HRESULT hr = CrAssignPointer(m_Center, newVal, this, IID_IPoint2dEvents, &m_CenterPointCookie);
   if (FAILED(hr))
      return hr;

   // adjust our hook point to account for change in center point
   AdjustHookPoint();

   return S_OK;
}

STDMETHODIMP CCircularSegment::get_MidOrdinate(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_MO;
	return S_OK;
}

STDMETHODIMP CCircularSegment::put_MidOrdinate(Float64 newVal)
{
   if ( !InRange(0.0,newVal,2*m_Radius) )
      return Error(IDS_E_MIDORDINATE,IID_ICircularSegment,GEOMETRY_E_MIDORDINATE);

   m_MO = newVal;
   AdjustHookPoint();

   return S_OK;
}

STDMETHODIMP CCircularSegment::get_InteriorAngle(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   if (m_Radius>0.0)
   {
      Float64 x = (m_Radius - m_MO)/m_Radius;
      if ( IsZero(x-1.0) )
         x = 1.0;

      Float64 angle = acos(x);
	   *pVal = 2.0*angle;
   }
   else
   {
      *pVal = 0.0;
   }

	return S_OK;
}

STDMETHODIMP CCircularSegment::put_InteriorAngle(Float64 newVal)
{
   if ( newVal < 0 || TWO_PI < newVal)
      return Error(IDS_E_ANGLE,IID_ICircularSegment,GEOMETRY_E_ANGLE);

   m_MO = m_Radius*(1.0 - cos(newVal/2));
   AdjustHookPoint();

	return S_OK;
}

STDMETHODIMP CCircularSegment::get_Rotation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Rotation;
   return S_OK;
}

STDMETHODIMP CCircularSegment::put_Rotation(Float64 newVal)
{
   m_Rotation = newVal;
   m_Rotation = NormalizeAngle(m_Rotation);
   AdjustHookPoint();
   return S_OK;
}

////////////////////////////////////////////////////
// IShape
////////////////////////////////////////////////////
STDMETHODIMP CCircularSegment::get_ShapeProperties(IShapeProperties * * pVal)
{
   CHECK_RETOBJ(pVal);

   HRESULT hr = CreateShapeProperties( pVal );
   if ( FAILED(hr) )
      return hr;

   // Compute properties for non-rotated shape, about global axes (0,0)
   Float64 angle;
   get_InteriorAngle(&angle);
   angle /= 2.0;

   Float64 area;
   Float64 ixx;
   Float64 iyy;
   Float64 ixy;
   Float64 cgx;
   Float64 cgy;

   if ( IsZero(angle) )
   {
      area = 0;
      ixx = 0;
      iyy = 0;
      ixy = 0;
      
      cgx = m_Radius;
      cgy = 0;
   }
   else
   {
      area = m_Radius*m_Radius*(angle - sin(2*angle)/2);
      ixx = (area*m_Radius*m_Radius/4)*(1 - (4*pow(sin(angle),3)*cos(angle))/(3*(2*angle - sin(2*angle))));
      iyy = (area*m_Radius*m_Radius/4)*(1 + (4*pow(sin(angle),3)*cos(angle))/(2*angle - sin(2*angle)));
      ixy = 0.00;

      cgx = (4*m_Radius/3) * pow(sin(angle),3)/(2*angle-sin(2*angle));
      cgy = 0.00;
   }

   CComPtr<IPoint2d> cg;
   CreatePoint(cgx,cgy,NULL,&cg);

   // Transform properties to centroidal coordinates
   iyy = iyy - area*cgx*cgx;

   // Transform properties into rotated coordinate system
   CComPtr<IMohrCircle> pMohrCircle;
   pMohrCircle.CoCreateInstance( CLSID_MohrCircle );
   pMohrCircle->put_Sii( ixx );
   pMohrCircle->put_Sjj( iyy );
   pMohrCircle->put_Sij( ixy );

   pMohrCircle->ComputeState(m_Rotation,&ixx,&iyy,&ixy);

   // next need to translate and rotate CG to proper position
   Float64 cx,cy;
   m_Center->get_X(&cx);
   m_Center->get_Y(&cy);
   cg->Offset(cx,cy);
   cg->RotateEx(m_Center,m_Rotation);
   // get coordinates of centroid in new coordinate system
   cg->get_X(&cgx);
   cg->get_Y(&cgy);

   // Get bounded box for Xleft, Xright, etc.
   CComPtr<IRect2d> box;
   get_BoundingBox(&box);
   Float64 left, right, top, bottom;
   GetRect(box,&left,&top,&right,&bottom);

   (*pVal)->put_Area( area );
   (*pVal)->put_Ixx( ixx );
   (*pVal)->put_Iyy( iyy );
   (*pVal)->put_Ixy( ixy );
   (*pVal)->put_Xleft( cgx - left );
   (*pVal)->put_Xright( right - cgx );
   (*pVal)->put_Ytop( top - cgy );
   (*pVal)->put_Ybottom( cgy - bottom );
   (*pVal)->put_Centroid(cg);
   (*pVal)->put_CoordinateSystem( csCentroidal );

	return S_OK;
}

STDMETHODIMP CCircularSegment::get_BoundingBox(IRect2d * * pVal)
{
   CHECK_RETOBJ(pVal);

   // Find the intersection points of the line and circle
   CComPtr<IPoint2d> p1;
   CComPtr<IPoint2d> p2;
   EdgePoints(&p1,&p2);
   Float64 p1x,p1y,p2x,p2y;
   GetCoordinates(p1,&p1x,&p1y);
   GetCoordinates(p2,&p2x,&p2y);

   // Get boundary line
   CComPtr<ILine2d> line;
   BoundaryLine(&line);
   Float64 c;
   CComPtr<IVector2d> n;
   line->GetImplicit(&c,&n); // normal to line

   Float64 nx,ny;
   GetCoordinates(n,&nx,&ny);
   // drown out any noice in the vector
   nx = IsZero(nx) ? 0.00 : nx;
   ny = IsZero(ny) ? 0.00 : ny;

   // Center of circle
   Float64 cx, cy;
   GetCoordinates(m_Center,&cx,&cy);

   // Find sides
   Float64 left, right, top, bottom;

   // left
   if ( (IsZero(nx) && m_Radius < m_MO) || 0.0 < nx )
      left = cx - m_Radius;
   else
      left = _cpp_min(p1x,p2x);

   // right
   if ( (IsZero(nx) && m_Radius < m_MO) || nx < 0.0 )
      right = cx + m_Radius;
   else
      right = _cpp_max(p1x,p2x);

   // top
   if ( (IsZero(ny) && m_MO < m_Radius) || 0.0 < ny )
      top = _cpp_max(p1y,p2y);
   else
      top = cy + m_Radius;

   // bottom
   if ( (IsZero(ny) && m_MO < m_Radius) || ny < 0.0 )
      bottom = _cpp_min(p1y,p2y);
   else
      bottom = cy - m_Radius;

   CreateRect(left,top,right,bottom,pVal);
   return S_OK;
}

STDMETHODIMP CCircularSegment::get_PolyPoints(IPoint2dCollection * * ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   HRESULT hr = CreatePointCollection( ppPolyPoints );

   // number of vertex points used to describe a polyline version of a circle
   const short NUM_POINTS = 37; // 36 segments.

   Float64 angle;
   get_InteriorAngle(&angle);

   angle /= 2.0; // divide in half so this is the same angle that is used in the equations
   Float64 angle_inc = 2*angle / (NUM_POINTS-1);

   // determine radius of circle to make an "Area Perfect" polygon.
   Float64 cfArea = m_Radius*m_Radius*(angle - sin(2*angle)/2); // closed form area

   Float64 rad = sqrt( cfArea/(((NUM_POINTS-1)*sin(angle_inc/2)*cos(angle_inc/2) - sin(angle)*cos(angle))) );

#if defined _DEBUG
   Float64 polyArea = (NUM_POINTS-1)*(rad*rad*sin(angle_inc/2)*cos(angle_inc/2))-rad*rad*sin(angle)*cos(angle);
   ATLASSERT( IsEqual(cfArea,polyArea) );
#endif // _DEBUG

   Float64 cx,cy;
   GetCoordinates(m_Center,&cx,&cy);

   Float64 startAngle = m_Rotation - angle;

   for (short i = 0; i < NUM_POINTS; i++)
   {
      Float64 a = startAngle + i * angle_inc;

      Float64 x = cx + rad * cos(a);
      Float64 y = cy + rad * sin(a);

      CComPtr<IPoint2d> pPoint;
      hr = CreatePoint( x, y, NULL, &pPoint );
      if ( FAILED(hr) )
         return hr;

      (*ppPolyPoints)->Add( pPoint );
   }

#if defined _DEBUG
   // Create a polyshape and compute its area.
   // If these poly-points really do make an area perfect polygon then
   // we can verify it here.
   CComPtr<IPolyShape> polyShape;
   polyShape.CoCreateInstance(CLSID_PolyShape);
   polyShape->AddPoints(*ppPolyPoints);
   CComQIPtr<IShape> shape(polyShape);
   CComPtr<IShapeProperties> props;
   shape->get_ShapeProperties(&props);
   Float64 area;
   props->get_Area(&area);
   ATLASSERT(IsEqual(area,cfArea));
#endif

   return S_OK;
}

STDMETHODIMP CCircularSegment::PointInShape(IPoint2d * pPoint, VARIANT_BOOL * pbResult)
{
   // Point must be in the circle and to the right of the line
   // Use GeomUtil2d::ShortestDistanceToPoint to determine side of line
   // If distance is >= 0 then the point is in the shape
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   // Create a circle, check if point is in circle
   CComPtr<ICircle> circle;
   circle.CoCreateInstance(CLSID_Circle);
   circle->putref_Center(m_Center);
   circle->put_Radius(m_Radius);
   VARIANT_BOOL bInCircle;
   CComQIPtr<IShape> shape(circle);
   shape->PointInShape(pPoint,&bInCircle);
   if ( bInCircle == VARIANT_FALSE )
   {
      *pbResult = VARIANT_FALSE;
      return S_OK;
   }

   // OK, point is in circle. Check to see if it is right of the line.
   CComPtr<ILine2d> line;
   BoundaryLine(&line);

   CComPtr<IGeomUtil2d> util;
   CreateGeomUtil(&util);
   Float64 dist;
   util->ShortestDistanceToPoint(line,pPoint,&dist);
   // if dist is positive, point is on right side of line.
   // this means it is in the circle

   *pbResult = ( 0 <= dist ) ? VARIANT_TRUE : VARIANT_FALSE;
		
	return S_OK;
}

STDMETHODIMP CCircularSegment::Clone(IShape * * pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CCircularSegment>* pTheClone;
   HRESULT hr = CComObject<CCircularSegment>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<ICircularSegment> pseg(pTheClone); // keep a reference

   // Copy the radius
   pTheClone->put_Radius(m_Radius);

   // Copy the mid ordinate
   pTheClone->put_MidOrdinate(m_MO);

   // Copy the rotation
   pTheClone->put_Rotation(m_Rotation);

   // Align the center points
   CComPtr<IPoint2d> ctrPnt;
   CreatePoint(m_Center,NULL,&ctrPnt);
   pTheClone->putref_Center(ctrPnt);

#if defined _DEBUG
   // Hook points should be the same
   CComPtr<IPoint2d> hp;
   Float64 hpx1,hpy1;
   Float64 hpx2,hpy2;
   pTheClone->get_HookPoint(&hp);
   GetCoordinates(hp,&hpx1,&hpy1);
   GetCoordinates(m_HookPoint,&hpx2,&hpy2);
   ATLASSERT(IsEqual(hpx1,hpx2));
   ATLASSERT(IsEqual(hpy1,hpy2));
#endif

   // Get the desired interface
   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CCircularSegment::ClipWithLine(ILine2d * pLine, IShape * * pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   // since clipping a circular segment is very expensive
   // first determine if shape really needs to be clipped.
   CComPtr<IGeomUtil2d> pGeomUtil;
   HRESULT hr = CreateGeomUtil(&pGeomUtil);
   if ( FAILED(hr) )
      return hr;

   // Find the intersection of the circle and the clipping line.
   // If either of the intersection points are in the shape, then
   // a clip is required.
   //
   // NOTE:
   // LineCircleIntersect will return points on the boundary of the circle
   // PointInShape cannot be used because points on the boundary are considered
   // out of the shape.
   short nIntersect;
   CComPtr<ICircle> circle;
   circle.CoCreateInstance(CLSID_Circle);
   circle->put_Radius(m_Radius);
   circle->putref_Center(m_Center);

   CComPtr<IPoint2d> p1,p2;
   pGeomUtil->LineCircleIntersect(pLine,circle,&p1,&p2,&nIntersect);

   bool bPoint1InShape = false;
   bool bPoint2InShape = false;

   CComPtr<ILine2d> edge;
   BoundaryLine(&edge);

   if ( nIntersect >= 1 )
   {
      Float64 dist1;
      pGeomUtil->ShortestDistanceToPoint(edge,p1,&dist1);
      bPoint1InShape = ( dist1 < 0 ) ? false : true;
   }

   if ( nIntersect == 2 )
   {
      Float64 dist2;
      pGeomUtil->ShortestDistanceToPoint(edge,p2,&dist2);
      bPoint2InShape = ( dist2 < 0 ) ? false : true;
   }

   if ( nIntersect == 0 || bPoint1InShape == false && bPoint2InShape == false )
   {
      // Clipping line does not intersect shape. If shape is
      // on the right side of the line, it remains
      // Determine if the shape is on the left or right of the line.
      CComPtr<ILine2d> normal_line;
      pGeomUtil->CreateNormalLineThroughPoint(pLine,m_Center,&normal_line);
      CComPtr<IPoint2d> p;
      CComPtr<IVector2d> v1;
      Float64 c;
      CComPtr<IVector2d> v2;

      pLine->GetImplicit(&c,&v1); // v1 is normal to pLine
      normal_line->GetExplicit(&p,&v2); // v2 is in the direction of normal_line

      // If v2 and v1 have the same direction their dot product will be > 0
      Float64 dot;
      v1->Dot(v2,&dot);
      ATLASSERT( !IsZero(dot) ); // dot is only zero if v1 and v2 are at right
                                 // angles from one another. This should never
                                 // happen in this case.

      // The clipping line does not intersect shape
      if ( dot > 0 )
      {
         // Circle in on the right
         // circle is entirely within clipping region
         return Clone( pShape );
      }
      else
      {
         // circle is entirely outside of clipping region
         *pShape = 0;
         return S_OK;
      }
   }
   else
   {
      // Clipping line intersects the shape
      // If the clipping line is in the same direction as the edge line,
      // the resulting shape is a circular segment, unless the clipping line and
      // edge line intersect on the shape boundary

      CComPtr<ILine2d> edge;
      BoundaryLine(&edge);
      Float64 c;
      CComPtr<IVector2d> n1; // normal to edge
      CComPtr<IVector2d> n2; // normal to clipping line
      edge->GetImplicit(&c,&n1);
      pLine->GetImplicit(&c,&n2);

      Float64 dot;
      n1->Dot(n2,&dot);

      if ( dot < 0 )
      {
         // Lines are in opposite direct

         // Make shape into a Polygon and use its clip
         CComPtr<IPoint2dCollection> pPoints;
         get_PolyPoints( &pPoints );

         CComPtr<IPolyShape> pPolygon;
         CreatePolyShape( pPoints, &pPolygon );

         CComQIPtr<IShape> pPolyShape(pPolygon);
         return pPolyShape->ClipWithLine( pLine, pShape );
      }
      else
      {
         // Lines are same direction
         // Check the interesction point
         CComPtr<IPoint2d> s;
         CComPtr<IPoint2d> e;
         EdgePoints(&s,&e);
         CComPtr<ILineSegment2d> ls;
         ls.CoCreateInstance(CLSID_LineSegment2d);
         ls->putref_StartPoint(s);
         ls->putref_EndPoint(e);

         CComPtr<IPoint2d> is; // intersection point
         pGeomUtil->IntersectLineWithLineSegment(pLine,ls,&is);

         if ( is != 0 )
         {
            // Clipping line intersects straight edge of shape
            // Make shape into a Polygon and use its clip
            CComPtr<IPoint2dCollection> pPoints;
            get_PolyPoints( &pPoints );

            CComPtr<IPolyShape> pPolygon;
            CreatePolyShape( pPoints, &pPolygon );

            CComQIPtr<IShape> pPolyShape(pPolygon);
            return pPolyShape->ClipWithLine( pLine, pShape );
         }
         else
         {
            // resulting shape is a circular segment
            Clone( pShape );
            CComQIPtr<ICircularSegment> result(*pShape);

            Float64 nx,ny;
            n2->get_X(&nx);
            n2->get_Y(&ny);
            Float64 rotation = atan2(-ny,-nx);
            result->put_Rotation(rotation);

            Float64 dist;
            pGeomUtil->ShortestDistanceToPoint(pLine,m_Center,&dist);
            result->put_MidOrdinate(m_Radius + dist);
            return S_OK;
         }
         ATLASSERT(false); // should never get here
      }
   }

   ATLASSERT(false); // should never get here
   return S_OK;
}

STDMETHODIMP CCircularSegment::ClipIn(IRect2d * pRect, IShape * * pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   CComPtr<ILine2d> pLine;
   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;

   // Clip using top edge
   pRect->get_TopLeft( &pStart );
   pRect->get_TopRight( &pEnd );
   CreateLine( pStart, pEnd, NULL, &pLine );

   CComPtr<IShape> pClipTop;
   ClipWithLine(pLine,&pClipTop);
   if ( pClipTop == NULL )
   {
      // the entire shape was clipped away
      *pShape = NULL;
      return S_OK;
   }

   pStart.Release();
   pEnd.Release();

   // Clip using Right edge
   pRect->get_TopRight(&pStart);
   pRect->get_BottomRight(&pEnd);
   pLine->ThroughPoints(pStart,pEnd);
   CComPtr<IShape> pClipRight;
   pClipTop->ClipWithLine(pLine,&pClipRight);
   pClipTop.Release();
   if ( pClipRight == NULL )
   {
      // the entire shape was clipped away
      *pShape = NULL;
      return S_OK;
   }

   pStart.Release();
   pEnd.Release();

   // Clip using Bottom edge
   pRect->get_BottomRight(&pStart);
   pRect->get_BottomLeft(&pEnd);
   pLine->ThroughPoints(pStart,pEnd);
   CComPtr<IShape> pClipBottom;
   pClipRight->ClipWithLine(pLine,&pClipBottom);
   pClipRight.Release();
   if ( pClipBottom == NULL )
   {
      // the entire shape was clipped away
      *pShape = NULL;
      return S_OK;
   }

   pStart.Release();
   pEnd.Release();

   // Clip using Left edge
   pRect->get_BottomLeft(&pStart);
   pRect->get_TopLeft(&pEnd);
   pLine->ThroughPoints(pStart,pEnd);
   CComPtr<IShape> pClipLeft;
   pClipBottom->ClipWithLine(pLine,&pClipLeft);
   pClipBottom.Release();
   if ( pClipLeft == NULL )
   {
      // the entire shape was clipped away
      *pShape = NULL;
      return S_OK;
   }

   pClipLeft->QueryInterface(pShape);

   return S_OK;
}

STDMETHODIMP CCircularSegment::get_Perimeter(Float64 * pVal)
{
   CHECK_RETVAL(pVal);

   Float64 angle;
   get_InteriorAngle(&angle);
   angle /= 2.0;

   Float64 arc_length;
   arc_length = 2.0*angle*m_Radius;

   Float64 chord_length;
   chord_length = 2*m_Radius*sin(angle);

   *pVal = arc_length + chord_length;
		
	return S_OK;
}

STDMETHODIMP CCircularSegment::FurthestDistance(ILine2d * line, Float64 * pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   CComPtr<ILine2d> bndLine; // boundry line
   BoundaryLine(&bndLine);

   Float64 c;
   CComPtr<IVector2d> n1; // normal of boundary line
   CComPtr<IVector2d> n2; // normal of input line

   bndLine->GetImplicit(&c,&n1);
   line->GetImplicit(&c,&n2);

   Float64 dot;
   n1->Dot(n2,&dot);
   // if dot < 0, the line in question and the straight edge of the shape
   // are in opposite directions

   CComPtr<IGeomUtil2d> util;
   CreateGeomUtil(&util);

   if ( dot < 0 )
   {
      // Lines are in opposite direction.
      // The furthest distance is the greater of the shorter distance from the line
      // to the edge points of the shape.
      Float64 d1, d2;
      CComPtr<IPoint2d> p1;
      CComPtr<IPoint2d> p2;
      EdgePoints(&p1,&p2);
      util->ShortestDistanceToPoint(line,p1,&d1);
      util->ShortestDistanceToPoint(line,p2,&d2);
      *pVal = _cpp_max(d1,d2);
   }
   else
   {
      // Lines are in the same direction. The furthest distance is the
      // shortest distance from the line to the center of the circle plus
      // the radius
      Float64 distToCenter; // Shortest distance from line to center of circle
                           // if < 0, circle is to the left of the line
      util->ShortestDistanceToPoint(line,m_Center,&distToCenter);
 
      *pVal = m_Radius + distToCenter;
  }
		
	return S_OK;
}

//////////////////////////////////////////////
// IXYPosition
//////////////////////////////////////////////
STDMETHODIMP CCircularSegment::Offset(Float64 dx, Float64 dy)
{
   Float64 x,y;
   GetCoordinates(m_Center,&x,&y);

   // shut down event handling since we are making two calls. Then update manually
   m_SquelchEvents = true;
   PutCoordinates(x+dx,y+dy,m_Center);
   m_SquelchEvents = false;
   
   AdjustHookPoint();

   return S_OK;
}

STDMETHODIMP CCircularSegment::OffsetEx(ISize2d * pSize)
{
   CHECK_IN(pSize);

   Float64 dx, dy;
   pSize->get_Dx( &dx );
   pSize->get_Dy( &dy );

   return Offset( dx, dy );
}

STDMETHODIMP CCircularSegment::get_LocatorPoint(LocatorPointType lp, IPoint2d * * point)
{
   HRESULT hr = S_OK;
   CHECK_RETOBJ(point);

   CComPtr<IRect2d> box;
   hr = get_BoundingBox(&box);
   if (FAILED(hr))
      return hr;

   switch(lp)
   {
   case lpHookPoint:
      m_HookPoint.CopyTo(point);
      break;

   case lpTopLeft:
      box->get_TopLeft(point);
      break;

   case lpTopCenter:
      box->get_TopCenter(point);
      break;

   case lpTopRight:
      box->get_TopRight(point);
      break;

   case lpCenterLeft:
      box->get_CenterLeft(point);
      break;

   case lpCenterCenter:
      box->get_CenterCenter(point);
      break;

   case lpCenterRight:
      box->get_CenterRight(point);
      break;

   case lpBottomLeft:
      box->get_BottomLeft(point);
      break;

   case lpBottomCenter:
      box->get_BottomCenter(point);
      break;

   case lpBottomRight:
      box->get_BottomRight(point);
      break;
   }
		
	return S_OK;
}

STDMETHODIMP CCircularSegment::put_LocatorPoint(LocatorPointType lp, IPoint2d * point)
{
   HRESULT hr = S_OK;

   CHECK_IN(point);

   CComPtr<IPoint2d> lp_current;
   hr = get_LocatorPoint(lp,&lp_current);
   ATLASSERT( SUCCEEDED(hr) );

   hr = MoveEx(lp_current,point);
   ATLASSERT( SUCCEEDED(hr) );

   return S_OK;
}

STDMETHODIMP CCircularSegment::MoveEx(IPoint2d * pFrom, IPoint2d * pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   Float64 x1,y1;
   pFrom->get_X(&x1);
   pFrom->get_Y(&y1);

   Float64 x2,y2;
   pTo->get_X(&x2);
   pTo->get_Y(&y2);

   Float64 dx = x2 - x1;
   Float64 dy = y2 - y1;

   return Offset(dx,dy);
}

STDMETHODIMP CCircularSegment::RotateEx(IPoint2d * pPoint, Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   pPoint->get_X(&x);
   pPoint->get_Y(&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CCircularSegment::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   m_Center->Rotate(cx,cy,angle);
   m_Rotation += angle;
   m_Rotation = NormalizeAngle(m_Rotation);
   AdjustHookPoint();

   return S_OK;
}

STDMETHODIMP CCircularSegment::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CCircularSegment::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CCircularSegment::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("CircularSegment"),1.0);
   
   // Center is stored with value symantics
   pSave->BeginUnit(CComBSTR("Center"),1.0);
   CComQIPtr<IStructuredStorage2> ss(m_Center);
   ss->Save(pSave);
   pSave->EndUnit(); // Center

   pSave->put_Property(CComBSTR("Radius"),CComVariant(m_Radius));
   pSave->put_Property(CComBSTR("MidOrdinate"),CComVariant(m_MO));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_HookPoint));


   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCircularSegment::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Circle"));
   
   pLoad->BeginUnit(CComBSTR("Center"));
   CComQIPtr<IStructuredStorage2> ss(m_Center);
   ss->Load(pLoad);

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);
   ATLASSERT(bEnd == VARIANT_TRUE);

   pLoad->get_Property(CComBSTR("Radius"),&var);
   m_Radius = var.dblVal;

   pLoad->get_Property(CComBSTR("MidOrdinate"),&var);
   m_MO = var.dblVal;

   pLoad->get_Property(CComBSTR("Rotation"),&var);
   m_Rotation = var.dblVal;

   pLoad->get_Property(CComBSTR("HookPoint"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_HookPoint,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

STDMETHODIMP CCircularSegment::OnPointChanged(IPoint2d* point)
{
   if (!m_SquelchEvents)
   {
	   if (m_HookPoint.IsEqualObject(point))
      {
         // hook point changed - we must update center point
         AdjustCenterPoint();
      }
	   else if(m_Center.IsEqualObject(point))
      {
         // center point changed - we must update hook point
         AdjustHookPoint();
      }
      else
         ATLASSERT(0); // we should not be listening to anyone else
   }

   return S_OK;
}
