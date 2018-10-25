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

// PolyShape.cpp : Implementation of CPolyShape
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "PolyShape.h"
#include <MathEx.h>
#include <limits>
#include <xutility> // For Min/Max

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolyShape
HRESULT CPolyShape::FinalConstruct()
{
   // born dirty
   MakeDirty();

   // our internal point storage
   HRESULT hr = CreatePointCollection(&m_pPoints);
   if (FAILED(hr))
      return hr;

   hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   if (FAILED(hr))
      return hr;

   return CrAdvise(m_pPoints, this, IID_IPoint2dCollectionEvents, &m_PointsCookie);
}

void CPolyShape::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pPoints, this, IID_IPoint2dCollectionEvents, m_PointsCookie);
   ATLASSERT(SUCCEEDED(hr));
}

void CPolyShape::GetLocatorPoint(LocatorPointType lp,Float64* x,Float64* y)
{
   ATLASSERT( x != NULL && y != NULL );

   CComPtr<IRect2d> pBox;
   CComPtr<IPoint2d> pnt;

   get_BoundingBox(&pBox);

   switch(lp)
   {
   case lpTopLeft:
        pBox->get_TopLeft(&pnt);
        break;

   case lpTopCenter:
        pBox->get_TopCenter(&pnt);
        break;

   case lpTopRight:
        pBox->get_TopRight(&pnt);
        break;

   case lpCenterLeft:
        pBox->get_CenterLeft(&pnt);
        break;

   case lpCenterCenter:
        pBox->get_CenterCenter(&pnt);
        break;

   case lpCenterRight:
        pBox->get_CenterRight(&pnt);
        break;

   case lpBottomLeft:
        pBox->get_BottomLeft(&pnt);
        break;

   case lpBottomCenter:
        pBox->get_BottomCenter(&pnt);
        break;

   case lpBottomRight:
        pBox->get_BottomRight(&pnt);
        break;

   case lpHookPoint:
      {
         CollectionIndexType cPoints;
         m_pPoints->get_Count(&cPoints);
         if ( cPoints == 0 )
            CreatePoint(0.00,0.00,NULL,&pnt);
         else
         {
            m_pPoints->get_Item(0,&pnt);
         }
        break;
      }

   default:
      ATLASSERT( false ); // Should never get here!
      break;
   }

   GetCoordinates(pnt,x,y);
}

STDMETHODIMP CPolyShape::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPolyShape,
		&IID_IShape,
		&IID_IXYPosition,
      &IID_IStructuredStorage2
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPolyShape::AddPoint(Float64 x,Float64 y)
{
   HRESULT hr = S_OK;
   CComPtr<IPoint2d> pPoint;
   
   hr = CreatePoint(x,y,NULL,&pPoint);
   if ( FAILED(hr) )
      return hr;

   m_pPoints->Add(pPoint);

   return S_OK;
}

STDMETHODIMP CPolyShape::AddPointEx(IPoint2d *pPoint)
{
   CHECK_IN(pPoint);
   return  m_pPoints->Add(pPoint);
}

STDMETHODIMP CPolyShape::AddPoints(IPoint2dCollection *pPoints)
{
   CHECK_IN(pPoints);

   CollectionIndexType cPoints;
   pPoints->get_Count(&cPoints);

   for ( CollectionIndexType i = 0; i < cPoints; i++ )
   {
      CComPtr<IPoint2d> pPoint;
      pPoints->get_Item(i,&pPoint);
      AddPointEx(pPoint);
   }

   return S_OK;
}

STDMETHODIMP CPolyShape::RemovePoint(CollectionIndexType index)
{
   return m_pPoints->Remove(index);
}

STDMETHODIMP CPolyShape::get_NumPoints(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   return m_pPoints->get_Count(pVal);
}

STDMETHODIMP CPolyShape::get_Point(CollectionIndexType index, IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   CollectionIndexType nPoints;
   m_pPoints->get_Count(&nPoints);
   if ( index < 0 || nPoints <= index )
      return E_INVALIDARG;

   CComPtr<IPoint2d> pPoint;
   m_pPoints->get_Item(index,&pPoint);
   return pPoint.CopyTo( pVal );
}

STDMETHODIMP CPolyShape::Clear()
{
   return m_pPoints->Clear();
}

STDMETHODIMP CPolyShape::get_Points(IPoint2dCollection** coll)
{
   CHECK_RETOBJ(coll);

   m_pPoints->QueryInterface(coll);

   return S_OK;
}

STDMETHODIMP CPolyShape::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CPolyShape::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CPolyShape::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);
   UpdateShapeProperties();

   return m_ShapeProps.CreateIShapeProperties(pVal);
}

void CPolyShape::UpdateShapeProperties()
{

   if (m_DirtyProperties)
   {
      Float64 area, ixx, iyy, ixy;
      Float64 cgx, cgy;

      // Intialize and check for null polygon.
      area = ixx = iyy = ixy = 0.;
      cgx = 0.00;
      cgy = 0.00;

      CollectionIndexType cPoints;
      m_pPoints->get_Count(&cPoints);

      if ( cPoints < 3) 
      {
         // If there are less than three points, it is a degenerate shape.
         // Just return default shape properties (All values are zero).
         m_ShapeProps.Init();
         return;
      }

      Float64 x0,y0;
      Float64 x1,y1;
      Float64 dy, dx;
      Float64 ar, at;
      Float64 g_ixx=0, g_iyy=0, g_ixy=0; // moments of inertia about the global axes
      Float64 c_ixx=0, c_iyy=0, c_ixy=0; // moments of inertia about the centroid
      Float64 area_local =0;

      // loop over all points - make sure of closure
      CollectionIndexType idx0, idx1;
      idx0 = 0;
      idx1 = 1;

      bool loop = true;
      bool last_round = false;

      while (loop)
      {
         CComPtr<IPoint2d> p0;
         CComPtr<IPoint2d> p1;

         m_pPoints->get_Item(idx0,&p0);
         m_pPoints->get_Item(idx1,&p1);

         GetCoordinates(p0,&x0,&y0);
         GetCoordinates(p1,&x1,&y1);

         dx = x1 - x0;
         dy = y1 - y0;

         ar = dx * y0;
         at = 0.5*dy*dx;

         area_local += (ar + at);

         // Centroid
         cgx += ar*(x1 + x0)/2 + at*(2*dx/3 + x0);
         cgy += ar*(y0/2) + at*(dy/3 + y0);

         // Inertia about global axes
         g_ixx += (y0)*(y0)*(y0)*dx/12 + ar*(y0/2)*(y0/2) +
                  dy*dy*dy*dx/36       + at*(dy/3 + y0)*(dy/3 + y0);

         g_iyy += (y0)*dx*dx*dx/12 + ar*(x0 + dx/2)*(x0 + dx/2) +
                  dy*dx*dx*dx/36   + at*(2*dx/3 + x0)*(2*dx/3 + x0);

         g_ixy += ar*(y0/2)*(x0 + dx/2) +
                  at*(dy/3 + y0)*(2*dx/3 + x0) +
                  dy*dy*dx*dx/72;

         // loop termination test - need to go one more iteration if loop is not closed
         if (last_round)
         {
            // just finished closure loop. time to quit
            loop = false;
         }
         else
         {
            // increment for next go-around
            idx0++;
            idx1++;

            if ( idx0 == cPoints-1 )
            {
               idx0 = cPoints-1;
               idx1 = 0;

               // check if extra loop is required for closure
               CComPtr<IPoint2d> pStart;
               CComPtr<IPoint2d> pEnd;
               m_pPoints->get_Item(idx1,&pStart);
               m_pPoints->get_Item(idx0,&pEnd);

               if ( !IsEqualPoint(pStart,pEnd) )
               {
                  // one more loop to close poly
                  last_round = true;
               }
               else
               {
                  // loop is closed - just quit
                  loop = false;
               }
            }
         }
      }     // while

      // If the Polygon has no area_local, then there is nothing left to compute.
      if ( area_local != 0 )
      {
         // Finish centriod
         cgx /= area_local;
         cgy /= area_local;

         // Inertia about local axes
         c_ixx = g_ixx - area_local * cgy * cgy;
         c_iyy = g_iyy - area_local * cgx * cgx;
         c_ixy = g_ixy - area_local * cgx * cgy;


         // assign properties to pProperties
         area = area_local;
         ixx  = c_ixx;
         iyy  = c_iyy;
         ixy  = c_ixy;
      }

      // if defined CCW, then area will be less than zero
      // if this is the case, multiply by -1
      if( area < 0 )
      {
         area *= -1;
         ixx  *= -1;
         iyy  *= -1;
         ixy  *= -1;
      }

      // update bounding rect
      this->UpdateBoundingBox();

      m_ShapeProps.Area = area;
      m_ShapeProps.Ixx = ixx;
      m_ShapeProps.Iyy = iyy;
      m_ShapeProps.Ixy = ixy;
      m_ShapeProps.Cx = cgx;
      m_ShapeProps.Cy = cgy;
      m_ShapeProps.Xleft = cgx - m_BoundingRect.Left;
      m_ShapeProps.Xright = m_BoundingRect.Right - cgx;
      m_ShapeProps.Ytop = m_BoundingRect.Top - cgy;
      m_ShapeProps.Ybottom = cgy - m_BoundingRect.Bottom;

      m_DirtyProperties = false;
   }
}


STDMETHODIMP CPolyShape::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateBoundingBox();

   return m_BoundingRect.CreateIRect(pVal);
}

void CPolyShape::UpdateBoundingBox()
{
   if (m_DirtyBoundingBox)
   {
      CollectionIndexType cPoints;
      m_pPoints->get_Count(&cPoints);

      if ( cPoints == 0 )
      {
         m_BoundingRect.Init();
      }
      else
      {
         Float64 left   =  DBL_MAX;
         Float64 right  = -DBL_MAX;
         Float64 top    = -DBL_MAX;
         Float64 bottom =  DBL_MAX;

         for ( CollectionIndexType idx = 0; idx < cPoints; idx++)
         {
            CComPtr<IPoint2d> pPoint;
            Float64 x,y;
            m_pPoints->get_Item(idx,&pPoint);
            GetCoordinates(pPoint,&x,&y);

            left   = _cpp_min( x, left);
            right  = _cpp_max( x, right);
            bottom = _cpp_min( y, bottom);
            top    = _cpp_max( y, top);
         }

         m_BoundingRect.Left = left;
         m_BoundingRect.Right = right;
         m_BoundingRect.Top = top;
         m_BoundingRect.Bottom = bottom;
      }

      m_DirtyBoundingBox = false;
   }
}

STDMETHODIMP CPolyShape::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   CreatePointCollection( ppPolyPoints );
   return CopyPoints( *ppPolyPoints, m_pPoints );
}

STDMETHODIMP CPolyShape::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   // Reference:
   // "Use of the residue theorem in locating points within an
   // arbitrary multiply-connected region"
   // G. Steven Gipson
   // Adv. Eng. Software, 1986, Vol. 8, No. 2

   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   CollectionIndexType cPoints;
   m_pPoints->get_Count(&cPoints);
   if ( cPoints < 3 )
   {
      // Points and lines can't contain anything
      ATLTRACE("*** WARNING: PolyShapes must have at least 3 points\n");
      *pbResult = VARIANT_FALSE;
      return S_OK;
   }

   const Float64 angular_tolerance = TWO_PI*1e-2; // 2*pi*10^-2

   CComPtr<IRect2d> pBox;
   get_BoundingBox( &pBox );

   Float64 height,width;
   pBox->get_Height(&height);
   pBox->get_Width(&width);

   // if height or width is zero, the point can't be in the shape.
   if ( IsZero(height) || IsZero(width) )
   {
      *pbResult = VARIANT_FALSE;
      return S_OK;
   }

   Float64 edgelen = min(width,height);

   CComPtr<IPoint2d> pTopLeft;
   CComPtr<IPoint2d> pBottomRight;
   pBox->get_TopLeft(&pTopLeft);
   pBox->get_BottomRight(&pBottomRight);

   Float64 dist;
   m_GeomUtil->Distance(pTopLeft,pBottomRight,&dist);
   dist *= 2;

   ATLASSERT( !IsZero(dist) ); // Distance cannot be zero if height or width is non-zero

   Float64 boundary_tolerance = edgelen / dist;
   boundary_tolerance = min( 1e-06, boundary_tolerance );

   Float64 sum = 0;

   CollectionIndexType idx0 = 0;
   CollectionIndexType idx1 = 1;
   bool loop       = true;
   bool last_round = false;
   while (loop)
   {
      CComPtr<IPoint2d> p0;
      CComPtr<IPoint2d> p1;

      m_pPoints->get_Item(idx0,&p0);
      m_pPoints->get_Item(idx1,&p1);

      Float64 x0;
      Float64 y0;
      Float64 x1;
      Float64 y1;

      GetCoordinates(p0,&x0,&y0);
      GetCoordinates(p1,&x1,&y1);

      // no calculation if points are coincident
      if (x0 != x1 || y0 != y1)
      {

         // Compute components of two vectors formed by
         // joining point in question with endpoints of 
         // boundary segment
         Float64 x,y;
         GetCoordinates(pPoint,&x,&y);

         Float64 ax = x0 - x;
         Float64 ay = y0 - y;
         Float64 bx = x1 - x;
         Float64 by = y1 - y;

         // Form cross product of the vectors to determine
         // the sign of the angular segment
         Float64 cp = ax*by - ay*bx;
         Float64 sign = cp < 0 ? -1 : 1;

         // Test for vanishing cross product in case the test point
         // is on the boundary.
         if ( IsZero( fabs( cp ), boundary_tolerance ) )
         {
            // Make sure the point is actually on the boundary and not
            // on a projection of a line segment
            CComPtr<ILineSegment2d> seg;
            CreateLineSegment(NULL,&seg);

            CComPtr<IPoint2d> p0,p1;
            seg->get_StartPoint(&p0);
            seg->get_EndPoint(&p1);

            p0->Move(x0,y0);
            p1->Move(x1,y1);

            VARIANT_BOOL bContains;
            m_GeomUtil->DoesLineSegmentContainPoint(seg,pPoint,1e-6,&bContains);

            if ( bContains == VARIANT_TRUE )
            {
               *pbResult = VARIANT_FALSE;
               return S_OK;
            }
         }

         // Compute dot product of two vectors for purpose of obtaining
         // the actual angle subtended by the boundary increment.
         Float64  dot  = ax*bx + ay*by;
         Float64  A2   = ax*ax + ay*ay;
         Float64  B2   = bx*bx + by*by;
         Float64  prod = A2 * B2;

         // Compute angle
         Float64  angle = 0;
         if ( !IsZero( prod ), 1.0e-16 )
         {
            Float64 x = dot/sqrt( prod );
            if ( IsZero(x-1.0) )
               x = 1.0;

            angle = acos(x);
         }

         // Add angle to running sum
         sum += sign * angle;
      }

      // loop termination test - need to go one more iteration if loop is not closed
      if (last_round)
      {
         // just finished closure loop. time to quit
         loop = false;
      }
      else
      {
         // increment for next go-around
         idx0++;
         idx1++;

         if ( idx0 == cPoints-1 )
         {
            idx0 = cPoints-1;
            idx1 = 0;

            // check if extra loop is required for closure
            CComPtr<IPoint2d> pEnd;
            CComPtr<IPoint2d> pStart;

            m_pPoints->get_Item(idx0,&pEnd);
            m_pPoints->get_Item(idx1,&pStart);

            if ( !IsEqualPoint(pStart,pEnd) )
            {
               // one more loop to close poly
               last_round = true; 
            }
            else
            {
               // loop is closed - just quit
               loop = false;
            }
         }
      }
   }

   // Clean up round off errors in sum and determine if the point
   // is in or out.
   sum *= 1.0/TWO_PI;

   bool bContained;

   if ( IsEqual( sum, -1., angular_tolerance) || IsEqual( sum, 1., angular_tolerance ) )
      bContained = true;
   else if ( IsZero( sum, angular_tolerance ) )
      bContained = false;
   else
   {
      ATLASSERT( false ); // This should never happen!
   }

   *pbResult = MakeBool(bContained);

   return S_OK;
}

STDMETHODIMP CPolyShape::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CPolyShape>* pTheClone;
   HRESULT hr = CComObject<CPolyShape>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPolyShape> pcClone(pTheClone);

   CollectionIndexType cPoints;
   m_pPoints->get_Count(&cPoints);

   for ( CollectionIndexType i = 0; i < cPoints; i++ )
   {
      CComPtr<IPoint2d> pPoint;
      m_pPoints->get_Item(i,&pPoint);

      CComPtr<IPoint2d> pNewPoint;
      CreatePoint( pPoint, NULL, &pNewPoint );

      pcClone->AddPointEx( pNewPoint );
   }

   return pcClone.QueryInterface( pClone );
}

STDMETHODIMP CPolyShape::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   // Clips on the right side of the line
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   // before we do anything, make sure there is a chance for this shape to be clipped
   CComPtr<IRect2d> bounding_box;
   get_BoundingBox(&bounding_box);
   CComPtr<IPoint2d> pntTL,pntTR,pntBL,pntBR;
   bounding_box->get_TopLeft(&pntTL);
   bounding_box->get_TopRight(&pntTR);
   bounding_box->get_BottomLeft(&pntBL);
   bounding_box->get_BottomRight(&pntBR);

   Float64 d1,d2,d3,d4;
   m_GeomUtil->ShortestDistanceToPoint(pLine,pntTL,&d1);
   m_GeomUtil->ShortestDistanceToPoint(pLine,pntTR,&d2);
   m_GeomUtil->ShortestDistanceToPoint(pLine,pntBL,&d3);
   m_GeomUtil->ShortestDistanceToPoint(pLine,pntBR,&d4);

   if ( d1 < 0 && d2 < 0 && d3 < 0 && d4 < 0 )
   {
      // entire shape is left of the line so nothing will remain after clipping
      *pShape = NULL;
      return S_OK;
   }

   if ( 0 < d1 && 0 < d2 && 0 < d3 && 0 < d4 )
   {
      // entire shape is right of the line so the entire shape will remain after clipping
      Clone(pShape);
      return S_OK;
   }

   // create an empty clipped Polygon - return empty if need be
   CComObject<CPolyShape>* pClipShape;
   HRESULT hr = CComObject<CPolyShape>::CreateInstance( &pClipShape );
   if ( FAILED(hr) )
      return hr;

   pClipShape->QueryInterface( pShape ); // Does an AddRef();

   // Sanity check
   // If this polygon isn't at least a triangle, just get the heck outta here.
   CollectionIndexType cPoints;
   m_pPoints->get_Count(&cPoints);
   if ( cPoints < 3 )
   {
      ATLTRACE("*** WARNING: PolyShapes must have at least 3 points\n");
      (*pShape)->Release();
      *pShape = 0;
      return S_OK;
   }

   CComPtr<IVector2d> dir;
   CComPtr<IPoint2d> pnt_a;
   CComPtr<IPoint2d> pnt_b;

   // point on the line and direction of vector
   pLine->GetExplicit(&pnt_a,&dir);

   Float64 dir_x, dir_y;
   dir->get_X(&dir_x);
   dir->get_Y(&dir_y);

   CreatePoint(pnt_a,NULL,&pnt_b);
   pnt_b->Offset(-dir_x,-dir_y);

   Float64 dx, dy; // components of the direction vector of the clipping line
   Float64 nx, ny; // components of a vector normal to the clipping line
   Float64 s;      // dot product of the normal vector and the position vector
                   // of this Polygon

   Float64 ax,ay;
   Float64 bx,by;
   GetCoordinates(pnt_a,&ax,&ay);
   GetCoordinates(pnt_b,&bx,&by);

   dx = bx - ax;
   dy = by - ay;

   nx = -dy;
   ny =  dx;

   // get the vector of points from the Polygon and make sure that it's closed
   CComPtr<IPoint2d> current;
   CComPtr<IPoint2d> last;
   CComPtr<IPoint2d> last_added;
   bool      was_last_added=false;

   CComPtr<IPoint2dCollection> my_points;
   CreatePointCollection(&my_points,m_pPoints);// creates and copies
   my_points->get_Count(&cPoints);

   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;
   my_points->get_Item(0,&pStart);
   my_points->get_Item(cPoints-1,&pEnd);

   if ( !IsEqualPoint(pStart,pEnd) )
   {
      CComPtr<IPoint2d> closure;
      CreatePoint(pStart,NULL,&closure);
      my_points->Add(closure); // close the polygon if not already
      my_points->get_Count(&cPoints);
   }

   CollectionIndexType idx = 0;
   bool current_out;
   bool last_out;

   my_points->get_Item(idx++,&last);

   Float64 lx,ly;
   GetCoordinates(last,&lx,&ly);
   s = nx*(lx - ax) + ny*(ly - ay);

   last_out = ( s < 0 ) ? true : false;

   if ( !last_out )
   {
      CreatePoint(lx,ly,NULL,&last_added);
      was_last_added = true;
      pClipShape->AddPointEx( last_added );
   }

   CComPtr<ILine2d> line2; // Line to be clipped
   line2.CoCreateInstance( CLSID_Line2d );
   do
   {
      current.Release();
      my_points->get_Item(idx++,&current);

      Float64 cx,cy;
      GetCoordinates(current,&cx,&cy);
      s = nx*(cx - ax) + ny*(cy - ay);
      current_out = ( s < 0 ) ? true : false;

      CComPtr<IPoint2d> intersect;
      if ( last_out && !current_out ||
          !last_out &&  current_out )
      {
         // Find intersection
         line2->ThroughPoints(last,current);
         CComPtr<IGeomUtil2d> util;
         util.CoCreateInstance( CLSID_GeomUtil );
         intersect.Release();
         util->LineLineIntersect(pLine,line2,&intersect);
         ATLASSERT(intersect.p != NULL);

         // don't add duplicate points
         if (!(was_last_added && IsEqualPoint(intersect,last_added)))
         {
            last_added.Release();
            CreatePoint(intersect,NULL,&last_added);
            was_last_added = true;
            pClipShape->AddPointEx( last_added );
         }
      }

      if ( !current_out && !(was_last_added && IsEqualPoint(current,last_added)))
      {
         last_added.Release();
         CreatePoint(current,NULL,&last_added);
         was_last_added = true;
         pClipShape->AddPointEx(current);
      }

      CopyPoint(last,current);
      last_out = current_out;

   } while ( idx < cPoints );

   my_points.Release();

   // make sure clipped Polygon has enough points to be interesting
   // If there are less than 3 points, it isn't a shape.
   // If there are exactly 3 points, and the first and last points are the same
   // it isn't a shape either (area is zero)
   CollectionIndexType nPoints;
   pClipShape->get_NumPoints(&nPoints);
   bool bIsLine = false;
   if ( nPoints == 3 )
   {
      pStart.Release();
      pEnd.Release();
      pClipShape->get_Point(0,&pStart);
      pClipShape->get_Point(nPoints-1,&pEnd);
      bIsLine = IsEqualPoint(pStart,pEnd);
   }

   if ( nPoints < 3 || bIsLine )
   {
      (*pShape)->Release();
      *pShape = 0;
      return S_OK;
   }

   return S_OK;
}

STDMETHODIMP CPolyShape::ClipIn(IRect2d* pRect,IShape** pShape)
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
   pStart.Release();
   pEnd.Release();

   if ( pClipTop == 0 ) // Resulting Shape is Nothing
      return S_OK;


   // Clip using Right edge
   pRect->get_TopRight(&pStart);
   pRect->get_BottomRight(&pEnd);
   pLine->ThroughPoints(pStart,pEnd);
   CComPtr<IShape> pClipRight;
   pClipTop->ClipWithLine(pLine,&pClipRight);
   pClipTop.Release();
   pStart.Release();
   pEnd.Release();

   if ( pClipRight == 0 ) // Resulting Shape is Nothing
      return S_OK;


   // Clip using Bottom edge
   pRect->get_BottomRight(&pStart);
   pRect->get_BottomLeft(&pEnd);
   pLine->ThroughPoints(pStart,pEnd);
   CComPtr<IShape> pClipBottom;
   pClipRight->ClipWithLine(pLine,&pClipBottom);
   pClipRight.Release();
   pStart.Release();
   pEnd.Release();

   if ( pClipBottom == 0 ) // Resulting Shape is Nothing
      return S_OK;

   // Clip using Left edge
   pRect->get_BottomLeft(&pStart);
   pRect->get_TopLeft(&pEnd);
   pLine->ThroughPoints(pStart,pEnd);
   CComPtr<IShape> pClipLeft;
   pClipBottom->ClipWithLine(pLine,&pClipLeft);
   pClipBottom.Release();
   pStart.Release();
   pEnd.Release();

   if ( pClipLeft == 0 ) // Resulting Shape is Nothing
      return S_OK;

   pClipLeft->QueryInterface(pShape);

   return S_OK;
}
//
//STDMETHODIMP CPolyShape::ClipOut(IRect2d* pRect,IShape** pShape)
//{
//   if ( pRect == 0 )
//      return E_INVALIDARG;
//
//   if ( pShape == 0 )
//      return E_POINTER;
//
//   CComPtr<ILine2d> pLine;
//   CComPtr<IPoint2d> pStart;
//   CComPtr<IPoint2d> pEnd;
//
//   // Clip using Top edge
//   pRect->get_TopRight( &pStart );
//   pRect->get_TopLeft( &pEnd );
//   CreateLine( pStart, pEnd, NULL, &pLine );
//
//   CComPtr<IShape> pClipTop;
//   ClipWithLine(pLine,&pClipTop);
//
//   pStart.Release();
//   pEnd.Release();
//
//   // Clip using Left edge
//   pRect->get_TopLeft(&pStart);
//   pRect->get_BottomLeft(&pEnd);
//   pLine->ThroughPoints(pStart,pEnd);
//   CComPtr<IShape> pClipLeft;
//   pClipTop->ClipWithLine(pLine,&pClipLeft);
//   pClipTop.Release();
//
//   pStart.Release();
//   pEnd.Release();
//
//   // Clip using Bottom edge
//   pRect->get_BottomLeft(&pStart);
//   pRect->get_BottomRight(&pEnd);
//   pLine->ThroughPoints(pStart,pEnd);
//   CComPtr<IShape> pClipBottom;
//   pClipLeft->ClipWithLine(pLine,&pClipBottom);
//   pClipLeft.Release();
//
//   pStart.Release();
//   pEnd.Release();
//
//   // Clip using Right edge
//   pRect->get_BottomRight(&pStart);
//   pRect->get_TopRight(&pEnd);
//   pLine->ThroughPoints(pStart,pEnd);
//   CComPtr<IShape> pClipRight;
//   pClipBottom->ClipWithLine(pLine,&pClipRight);
//   pClipBottom.Release();
//
//   pClipRight->QueryInterface(pShape);
//
//   return S_OK;
//}

STDMETHODIMP CPolyShape::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CollectionIndexType cPoints;
   m_pPoints->get_Count(&cPoints);

   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;

   m_pPoints->get_Item(0,&pStart);
   m_pPoints->get_Item(cPoints-1,&pEnd);

   Float64 sum = 0.00;

   // Get the distance between the first and last point.
   // If the polygon is closed, it will be zero.
   Float64 last_dist;
   m_GeomUtil->Distance(pStart,pEnd,&last_dist);

   for ( CollectionIndexType idx = 1; idx < cPoints; idx++ )
   {
      CComPtr<IPoint2d> p1;
      CComPtr<IPoint2d> p2;
   
      m_pPoints->get_Item(idx-1,&p1);
      m_pPoints->get_Item(idx  ,&p2);

      Float64 dist;
      HRESULT hr = m_GeomUtil->Distance(p1,p2,&dist);
      ATLASSERT( SUCCEEDED(hr) );

      sum += dist;
   }

   sum += last_dist;

   *pVal = sum;

   return S_OK;
}

STDMETHODIMP CPolyShape::FurthestDistance(ILine2d* line, Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   CollectionIndexType cPoints;
   m_pPoints->get_Count(&cPoints);

   Float64 maxDist = -DBL_MAX;

   for ( CollectionIndexType i = 0; i < cPoints; i++ )
   {
      CComPtr<IPoint2d> pPoint;
      m_pPoints->get_Item(i,&pPoint);

      Float64 dist;
      m_GeomUtil->ShortestDistanceToPoint(line,pPoint,&dist);
      maxDist = _cpp_max( maxDist, dist );
   }

   *pVal = maxDist;

   return S_OK;

}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CPolyShape::Offset(Float64 dx,Float64 dy)
{
   CollectionIndexType cPoints;
   m_pPoints->get_Count(&cPoints);

   for ( CollectionIndexType i = 0; i < cPoints; i++ )
   {
      CComPtr<IPoint2d> pPoint;
      m_pPoints->get_Item(i,&pPoint);
      pPoint->Offset(dx,dy);
   }

   return S_OK;
}

STDMETHODIMP CPolyShape::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   GetSize(pSize,&dx,&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CPolyShape::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,NULL,point);
}

STDMETHODIMP CPolyShape::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CPolyShape::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   Float64 x1,y1;
   Float64 x2,y2;

   GetCoordinates(pFrom,&x1,&y1);
   GetCoordinates(pTo,&x2,&y2);

   Float64 dx,dy;
   dx = x2 - x1;
   dy = y2 - y1;

   return Offset(dx,dy);
}

STDMETHODIMP CPolyShape::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);
   return Rotate(x,y,angle);
}


STDMETHODIMP CPolyShape::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   CollectionIndexType cPoints;
   m_pPoints->get_Count(&cPoints);

   for ( CollectionIndexType i = 0; i < cPoints; i++ )
   {
      CComPtr<IPoint2d> pPoint;
      m_pPoints->get_Item(i,&pPoint);
      pPoint->Rotate(cx,cy,angle);
   }

   return S_OK;
}

STDMETHODIMP CPolyShape::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CPolyShape::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CPolyShape::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("PolyShape"),1.0);
   pSave->put_Property(CComBSTR("Points"),CComVariant(m_pPoints));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CPolyShape::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("PolyShape"));
   
   pLoad->get_Property(CComBSTR("Points"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2dCollection>::copy(&m_pPoints,&var)) )
      return STRLOAD_E_INVALIDFORMAT;


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

STDMETHODIMP CPolyShape::OnPointChanged(IPoint2d* point)
{
   MakeDirty();
   return S_OK;
}

STDMETHODIMP CPolyShape::OnPointAdded(CollectionIndexType index,IPoint2d* point)
{
   MakeDirty();
   return S_OK;
}

STDMETHODIMP CPolyShape::OnPointRemoved(CollectionIndexType index)
{
   MakeDirty();
   return S_OK;
}

STDMETHODIMP CPolyShape::OnPointsCleared()
{
   MakeDirty();
   return S_OK;
}

void CPolyShape::ShapeProps::Init()
{
   Area = 0.0;
   Ixx = 0.0;
   Iyy = 0.0;
   Ixy = 0.0;
   Xleft = 0.0;
   Xright = 0.0;
   Ytop = 0.0;
   Ybottom = 0.0;
   Cx = 0.0;
   Cy = 0.0;
}

HRESULT CPolyShape::ShapeProps::CreateIShapeProperties(IShapeProperties ** props)
{
   HRESULT hr = CreateShapeProperties(props);
   if (FAILED(hr))
      return hr;

   (*props)->put_Area( Area );
   (*props)->put_Ixx( Ixx );
   (*props)->put_Iyy( Iyy );
   (*props)->put_Ixy( Ixy );
   (*props)->put_Xleft( Xleft );
   (*props)->put_Xright( Xright );
   (*props)->put_Ytop( Ytop );
   (*props)->put_Ybottom( Ybottom );

   CComPtr<IPoint2d> centroid;
   centroid.CoCreateInstance(CLSID_Point2d);
   centroid->put_X(Cx);
   centroid->put_Y(Cy);
   (*props)->put_Centroid( centroid );

   (*props)->put_CoordinateSystem( csCentroidal );

   return S_OK;
}