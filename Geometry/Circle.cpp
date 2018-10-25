///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// Circle.cpp : Implementation of CCircle
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Circle.h"
#include "CircularSegment.h"
#include "Line2d.h"
#include "Point2d.h"
#include "GeomUtil.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT CCircle::FinalConstruct()
{
   m_Radius = 0.00;
   HRESULT hr = m_pCenter.CoCreateInstance( CLSID_Point2d );
   if ( FAILED(hr) )
      return hr;

// No need to actually move the point because default is at (0,0)
//   m_pCenter->Move(0.0,0.0);

   return S_OK;
}

STDMETHODIMP CCircle::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICircle,
		&IID_IShape,
		&IID_IXYPosition,
      &IID_IStructuredStorage2,
	};
	for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CCircle::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
{
   Float64 cx,cy;
   GetCoordinates(m_pCenter,&cx,&cy);

   switch( lp )
   {
   case lpTopLeft:
      *px = cx - m_Radius;
      *py = cy + m_Radius;
      break;

   case lpTopCenter:
      *px = cx;
      *py = cy + m_Radius;
      break;

   case lpTopRight:
      *px = cx + m_Radius;
      *py = cy + m_Radius;
      break;

   case lpCenterLeft:
      *px = cx - m_Radius;
      *py = cy;
      break;

   case lpCenterCenter:
   case lpHookPoint:
      *px = cx;
      *py = cy;
      break;

   case lpCenterRight:
      *px = cx + m_Radius;
      *py = cy;
      break;

   case lpBottomLeft: 
      *px = cx - m_Radius;
      *py = cy - m_Radius;
      break;

   case lpBottomCenter:
      *px = cx;
      *py = cy - m_Radius;
      break;

   case lpBottomRight:
      *px = cx + m_Radius;
      *py = cy - m_Radius;
      break;

   default:
      ATLASSERT( false ); // Should never get here
   }
}

/////////////////////////////////////////////////////////////////////////////
// CCircle
STDMETHODIMP CCircle::get_Radius(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Radius;
	return S_OK;
}

STDMETHODIMP CCircle::put_Radius(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_RADIUS,IID_ICircle,GEOMETRY_E_RADIUS);

   m_Radius = newVal;
	return S_OK;
}

STDMETHODIMP CCircle::get_Center(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   return m_pCenter->QueryInterface(pVal);
}

STDMETHODIMP CCircle::putref_Center(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   m_pCenter = newVal;

   return S_OK;
}

STDMETHODIMP CCircle::ThroughTwoPoints(IPoint2d* p1,IPoint2d* p2)
{
   CHECK_IN(p1);
   CHECK_IN(p2);

   Float64 x1,y1;
   GetCoordinates(p1,&x1,&y1);

   Float64 x2,y2;
   GetCoordinates(p2,&x2,&y2);

   Float64 diameter = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
   if ( IsZero(diameter) )
      return Error(IDS_E_COINCIDENTPOINTS,IID_ICircle,GEOMETRY_E_COINCIDENTPOINTS);

   m_Radius = diameter/2;
   m_pCenter->Move( (x1+x2)/2, (y1+y2)/2 );

   return S_OK;
}

STDMETHODIMP CCircle::ThroughThreePoints(IPoint2d* p1,IPoint2d* p2,IPoint2d* p3)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   CHECK_IN(p3);

   // Create lines that go between the poinst
   CComObject<CLine2d>* pLine1;
   CComObject<CLine2d>* pLine2;
   CComObject<CLine2d>::CreateInstance(&pLine1);
   CComObject<CLine2d>::CreateInstance(&pLine2);

   CComPtr<ILine2d> line1(pLine1);
   CComPtr<ILine2d> line2(pLine2);

   line1->ThroughPoints(p1,p2);
   line2->ThroughPoints(p2,p3);

   // Determine if the lines are colinear
   CComObject<CGeomUtil>* pGeomUtil;
   CComObject<CGeomUtil>::CreateInstance(&pGeomUtil);
   CComPtr<IGeomUtil2d> util(pGeomUtil);

   VARIANT_BOOL bAreColinear;
   util->AreLinesColinear(line1,line2,&bAreColinear);
   if ( bAreColinear == VARIANT_TRUE )
      return Error(IDS_E_COLINEAR,IID_ICircle,GEOMETRY_E_COLINEAR);

   // Create lines that are normal to line1 and line2, passing through the midpoint
   Float64 x1,y1;
   Float64 x2,y2;
   Float64 x3,y3;
   GetCoordinates(p1,&x1,&y1);
   GetCoordinates(p2,&x2,&y2);
   GetCoordinates(p3,&x3,&y3);

   Float64 mx1 = (x1+x2)/2;
   Float64 my1 = (y1+y2)/2;
   Float64 mx2 = (x2+x3)/2;
   Float64 my2 = (y2+y3)/2;

   CComObject<CPoint2d>* pMidPoint1;
   CComObject<CPoint2d>* pMidPoint2;
   CComObject<CPoint2d>::CreateInstance(&pMidPoint1);
   CComObject<CPoint2d>::CreateInstance(&pMidPoint2);
   CComPtr<IPoint2d> mp1(pMidPoint1);
   CComPtr<IPoint2d> mp2(pMidPoint2);
   mp1->Move(mx1,my1);
   mp2->Move(mx2,my2);

   CComPtr<ILine2d> normal1, normal2;
   util->CreateNormalLineThroughPoint(line1,mp1,&normal1);
   util->CreateNormalLineThroughPoint(line2,mp2,&normal2);

   // The intersection of the normal lines is the center of the circle
   CComPtr<IPoint2d> center;
   util->LineLineIntersect(normal1,normal2,&center);

   Float64 radius;
   util->Distance(center,p1,&radius);

#if defined _DEBUG
   Float64 r2,r3;
   util->Distance(center,p2,&r2);
   util->Distance(center,p3,&r3);
   ATLASSERT(IsEqual(radius,r2));
   ATLASSERT(IsEqual(radius,r3));
   ATLASSERT(IsEqual(r2,r3));
#endif

   Float64 cx,cy;
   GetCoordinates(center,&cx,&cy);
   m_pCenter->Move(cx,cy);
   m_Radius = radius;

   return S_OK;
}

STDMETHODIMP CCircle::ContainsPoint(IPoint2d* p,VARIANT_BOOL* pResult)
{
   CHECK_IN(p);
   CHECK_RETVAL(pResult);
   Float64 px,py;
   GetCoordinates(p,&px,&py);

   Float64 cx,cy;
   GetCoordinates(m_pCenter,&cx,&cy);

   Float64 r = sqrt(pow(cx-px,2) + pow(cy-py,2));
   if ( r < m_Radius || IsEqual(r,m_Radius) )
      *pResult = VARIANT_TRUE;
   else
      *pResult = VARIANT_FALSE;

   return S_OK;
}

STDMETHODIMP CCircle::PointOnCircle(IPoint2d* p,VARIANT_BOOL* pResult)
{
   CHECK_IN(p);
   CHECK_RETVAL(pResult);
   Float64 px,py;
   GetCoordinates(p,&px,&py);

   Float64 cx,cy;
   GetCoordinates(m_pCenter,&cx,&cy);

   Float64 r = sqrt(pow(cx-px,2) + pow(cy-py,2));
   if ( IsEqual(r,m_Radius) )
      *pResult = VARIANT_TRUE;
   else
      *pResult = VARIANT_FALSE;

   return S_OK;
}

STDMETHODIMP CCircle::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CCircle::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCircle::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   HRESULT hr = CreateShapeProperties( pVal );
   if ( FAILED(hr) )
      return hr;

   // get non-rotated properties
   Float64 area = M_PI * m_Radius * m_Radius;
   Float64 ixx  = M_PI * pow(m_Radius,4.)/4.;
   Float64 iyy  = ixx;
   Float64 ixy  = 0;

   CComPtr<IPoint2d> pCenter;
   hr = CreatePoint(m_pCenter,nullptr,&pCenter);
   if ( FAILED(hr) )
      return hr;

   Float64 cx,cy;
   GetCoordinates(m_pCenter,&cx,&cy);

   (*pVal)->put_Area( area );
   (*pVal)->put_Ixx( ixx );
   (*pVal)->put_Iyy( iyy );
   (*pVal)->put_Ixy( ixy );
   (*pVal)->put_Xleft( m_Radius );
   (*pVal)->put_Xright( m_Radius );
   (*pVal)->put_Ytop( m_Radius );
   (*pVal)->put_Ybottom( m_Radius );
   (*pVal)->put_Centroid( pCenter );
   (*pVal)->put_CoordinateSystem( csCentroidal );

   return S_OK;
}

STDMETHODIMP CCircle::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 cx,cy;
   GetCoordinates(m_pCenter,&cx,&cy);

   return CreateRect( cx - m_Radius,
                      cy + m_Radius,
                      cx + m_Radius,
                      cy - m_Radius,
                      pVal);
}

STDMETHODIMP CCircle::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   HRESULT hr = CreatePointCollection( ppPolyPoints );

   // number of vertex points used to describe a polyline version of a circle
   const short NUM_POINTS = 36; // 36 segments. 9 per quadrant (Need symmetry)
   Float64 angle_inc = TWO_PI/NUM_POINTS;

   // determine radius of circle to make an "Area Perfect" polycircle.
   Float64 rad = sqrt(M_PI * m_Radius * m_Radius / 
                      (NUM_POINTS * sin(M_PI/NUM_POINTS) * cos(M_PI/NUM_POINTS)));

#if defined _DEBUG
   Float64 area1 = M_PI*m_Radius*m_Radius;
   Float64 area2 = NUM_POINTS*rad*rad*sin(angle_inc)/2;
   ATLASSERT( IsEqual(area1,area2) );
#endif // _DEBUG

   Float64 cx,cy;
   GetCoordinates(m_pCenter,&cx,&cy);

   for (short i = 0; i < NUM_POINTS; i++)
   {
      Float64 a = i * angle_inc;

#if defined _DEBUG
      if ( i == NUM_POINTS-1 )
         ATLASSERT( IsEqual(a,TWO_PI-angle_inc) );
#endif // _DEBUG

      Float64 x = cx + rad * cos(a);
      Float64 y = cy + rad * sin(a);

      CComPtr<IPoint2d> pPoint;
      hr = CreatePoint( x, y, nullptr, &pPoint );
      if ( FAILED(hr) )
         return hr;

      (*ppPolyPoints)->Add( pPoint );
   }

#if defined _DEBUG
   // The first and last points should not be the same.
   // The distance between the first and last point should be the
   // same as the distance between the first and second point
   CComPtr<IPoint2d> pFirst;
   CComPtr<IPoint2d> pSecond;
   CComPtr<IPoint2d> pLast;
   CollectionIndexType cPoints;
   Float64 dist1;
   Float64 dist2;

   (*ppPolyPoints)->get_Count(&cPoints);
   (*ppPolyPoints)->get_Item(0,&pFirst);
   (*ppPolyPoints)->get_Item(1,&pSecond);
   (*ppPolyPoints)->get_Item(cPoints-1,&pLast);

   ATLASSERT( !IsEqualPoint(pFirst,pLast) );

   Float64 x1,y1;
   Float64 x2,y2;
   pFirst->get_X(&x1);
   pFirst->get_Y(&y1);
   pSecond->get_X(&x2);
   pSecond->get_Y(&y2);
   dist1 = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);

   pFirst->get_X(&x1);
   pFirst->get_Y(&y1);
   pLast->get_X(&x2);
   pLast->get_Y(&y2);
   dist2 = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);

   ATLASSERT( IsEqual(dist1,dist2) );

   Float64 dist = 2*rad*sin(angle_inc/2);
   dist1=sqrt(dist1);
   ATLASSERT( IsEqual(dist1,dist) );

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
   Float64 cfArea = M_PI*m_Radius*m_Radius;
   ATLASSERT(IsEqual(area,cfArea));
#endif

   // close the polyshape by repeating the first point
   CComPtr<IPoint2d> p1;
   (*ppPolyPoints)->get_Item(0,&p1);
   (*ppPolyPoints)->Add(p1);

   return S_OK;
}

STDMETHODIMP CCircle::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   return ContainsPoint(pPoint,pbResult);
//   CHECK_IN(pPoint);
//   CHECK_RETVAL(pbResult);
//
//   Float64 x,y;
//   GetCoordinates(pPoint,&x,&y);
//
//   Float64 cx,cy;
//   GetCoordinates(m_pCenter,&cx,&cy);
//
//   Float64 dist; // Distance from center of circle to p
//   dist = sqrt( pow(cx-x,2) + pow(cy-y,2) );
//   *pbResult = ( dist < m_Radius ) ? VARIANT_TRUE : VARIANT_FALSE;
//
//   return S_OK;
}

STDMETHODIMP CCircle::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CCircle>* pTheClone;
   HRESULT hr = CComObject<CCircle>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   // Copy the center point.
   CComPtr<IPoint2d> center;
   CreatePoint( m_pCenter, nullptr, &center );

   pTheClone->putref_Center( center );
   pTheClone->put_Radius( m_Radius );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CCircle::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   // since clipping a circle is very expensive
   // first determine if circle really needs to be clipped.
   CComPtr<IGeomUtil2d> pGeomUtil;
   HRESULT hr = CreateGeomUtil(&pGeomUtil);
   if ( FAILED(hr) )
      return hr;

   Float64 distance;
   pGeomUtil->ShortestDistanceToPoint( pLine, m_pCenter, &distance );

   if ( fabs(distance) < m_Radius)
   {
      // circle touches line, must clip
     
//      // Resulting shape is a circular segment
//      CComObject<CCircularSegment>* clip;
//      CComObject<CCircularSegment>::CreateInstance(&clip);
//      CComPtr<ICircularSegment> pclip(clip); // need to hold onto a reference
//
//      CComPtr<IPoint2d> ctrPnt;
//      CreatePoint(m_pCenter,nullptr,&ctrPnt);
//      clip->putref_Center(ctrPnt);
//      clip->put_Radius(m_Radius);
//
//      Float64 c;
//      CComPtr<IVector2d> n;
//      pLine->GetImplicit(&c,&n);
//
//      Float64 nx,ny;
//      n->get_X(&nx);
//      n->get_Y(&ny);
//      Float64 rotation = atan2(-ny,-nx);
//      clip->put_Rotation(rotation);
//
//      clip->put_MidOrdinate(m_Radius + distance);
//
//      return clip->QueryInterface(pShape);

      // make shape into a polygon and use its clip
      CComPtr<IPoint2dCollection> pPoints;
      get_PolyPoints( &pPoints );

      CComPtr<IPolyShape> pPolygon;
      CreatePolyShape( pPoints, &pPolygon );
      
      CComQIPtr<IShape> pPolyShape(pPolygon);
      return pPolyShape->ClipWithLine( pLine, pShape );
   }
   else
   {
      // Determine if the circle is on the left or right of the line.
      CComPtr<ILine2d> normal_line;
      pGeomUtil->CreateNormalLineThroughPoint(pLine,m_pCenter,&normal_line);
      CComPtr<IPoint2d> p;
      CComPtr<IVector2d> v1;
      Float64 c;
      CComPtr<IVector2d> v2;

      CComVariant varC;
      CComVariant varP;
      CComVariant varV1;
      CComVariant varV2;

      pLine->GetImplicit(&c,&v1); // v1 is normal to pLine
      normal_line->GetExplicit(&p,&v2); // v2 is in the direction of normal_line


      // If v2 and v1 have the same direction their dot product will be > 0
      Float64 dot;
      v1->Dot(v2,&dot);
      ATLASSERT( !IsZero(dot) ); // dot is only zero if v1 and v2 are at right
                                 // angles from one another. This should never
                                 // happen in this case.
      if ( dot > 0 )
      {
         // Circle in on the right
         // circle is entirely within clipping region
         return Clone( pShape );
      }
      else
      {
         // circle is entirely outside of clipping region
         ATLASSERT( *pShape == 0 );
         return S_OK;
      }
   }

   return S_OK;
}

STDMETHODIMP CCircle::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   CComPtr<ILine2d> pLine;
   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;

   // Clip using top edge
   pRect->get_TopLeft( &pStart );
   pRect->get_TopRight( &pEnd );
   CreateLine( pStart, pEnd, nullptr, &pLine );

   CComPtr<IShape> pClipTop;
   ClipWithLine(pLine,&pClipTop);

   if ( pClipTop == nullptr )
      return S_OK; // Entire shape clipped away

   pStart.Release();
   pEnd.Release();

   // Clip using Right edge
   pRect->get_TopRight(&pStart);
   pRect->get_BottomRight(&pEnd);
   pLine->ThroughPoints(pStart,pEnd);
   CComPtr<IShape> pClipRight;
   pClipTop->ClipWithLine(pLine,&pClipRight);
   pClipTop.Release();

   if ( pClipRight == nullptr )
      return S_OK; // Entire shape clipped away

   pStart.Release();
   pEnd.Release();

   // Clip using Bottom edge
   pRect->get_BottomRight(&pStart);
   pRect->get_BottomLeft(&pEnd);
   pLine->ThroughPoints(pStart,pEnd);
   CComPtr<IShape> pClipBottom;
   pClipRight->ClipWithLine(pLine,&pClipBottom);
   pClipRight.Release();

   if ( pClipBottom == nullptr )
      return S_OK; // Entire shape clipped away

   pStart.Release();
   pEnd.Release();

   // Clip using Left edge
   pRect->get_BottomLeft(&pStart);
   pRect->get_TopLeft(&pEnd);
   pLine->ThroughPoints(pStart,pEnd);
   CComPtr<IShape> pClipLeft;
   pClipBottom->ClipWithLine(pLine,&pClipLeft);
   pClipBottom.Release();

   if ( pClipLeft == nullptr )
      return S_OK; // Entire shape clipped away

   pClipLeft->QueryInterface(pShape);

   return S_OK;
}

STDMETHODIMP CCircle::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = TWO_PI*m_Radius;

   return S_OK;
}

STDMETHODIMP CCircle::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   CComPtr<IGeomUtil2d> util;
   CreateGeomUtil(&util);

   Float64 dist;
   util->ShortestDistanceToPoint(line,m_pCenter,&dist);

   *pVal = dist + m_Radius;

   return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CCircle::Offset(Float64 dx,Float64 dy)
{
   Float64 x,y;
   GetCoordinates(m_pCenter,&x,&y);
   PutCoordinates(x+dx,y+dy,m_pCenter);

   return S_OK;
}

STDMETHODIMP CCircle::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx, dy;
   pSize->get_Dx( &dx );
   pSize->get_Dy( &dy );

   return Offset( dx, dy );
}

STDMETHODIMP CCircle::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,nullptr,point);
}

STDMETHODIMP CCircle::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CCircle::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CCircle::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   pPoint->get_X(&x);
   pPoint->get_Y(&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CCircle::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_pCenter->Rotate(cx,cy,angle);
   return S_OK;
}

STDMETHODIMP CCircle::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CCircle::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CCircle::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Circle"),1.0);
   pSave->put_Property(CComBSTR("Center"),CComVariant(m_pCenter));
   pSave->put_Property(CComBSTR("Radius"),CComVariant(m_Radius));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCircle::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Circle"));
   
   pLoad->get_Property(CComBSTR("Center"),&var);
   m_pCenter.Release();
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pCenter,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   pLoad->get_Property(CComBSTR("Radius"),&var);
   m_Radius = var.dblVal;


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
