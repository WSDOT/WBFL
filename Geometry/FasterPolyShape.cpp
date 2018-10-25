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

// FasterPolyShape.cpp : Implementation of CFasterPolyShape
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "FasterPolyShape.h"
#include <limits>
#include <xutility> // For Min/Max

#include <GeometricPrimitives\Line2d.h>
#include <GeometricPrimitives\LineSegment2d.h>
#include <GeometricPrimitives\GeomOp2d.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Free utility functions
inline gpLine2d ComLine2gpLine(ILine2d* pcLine)
{
   Float64 c;
   CComPtr<IVector2d> pcVec;
   pcLine->GetImplicit(&c, &pcVec);

   Float64 vm, vd;
   pcVec->get_Magnitude(&vm);
   pcVec->get_Direction(&vd);

   gpVector2d vec(vm, vd);
   return gpLine2d(c, vec);
}

/////////////////////////////////////////////////////////////////////////////
// CFasterPolyShape
HRESULT CFasterPolyShape::FinalConstruct()
{
   // born dirty
   MakeDirty();

   return S_OK;
}

void CFasterPolyShape::GetLocatorPoint(LocatorPointType lp,Float64* x,Float64* y)
{
   ATLASSERT( x != NULL && y != NULL );

   UpdateBoundingBox();

   gpPoint2d point;

   switch(lp)
   {
   case lpTopLeft:
        point = m_BoundingRect.TopLeft();
        break;

   case lpTopCenter:
        point = m_BoundingRect.TopCenter();
        break;

   case lpTopRight:
        point = m_BoundingRect.TopRight();
        break;

   case lpCenterLeft:
        point = m_BoundingRect.LeftCenter();
        break;

   case lpCenterCenter:
        point = m_BoundingRect.Center();
        break;

   case lpCenterRight:
        point = m_BoundingRect.RightCenter();
        break;

   case lpBottomLeft:
        point = m_BoundingRect.BottomLeft();
        break;

   case lpBottomCenter:
        point = m_BoundingRect.BottomCenter();
        break;

   case lpBottomRight:
        point = m_BoundingRect.BottomRight();
        break;

   case lpHookPoint:
      {
         CollectionIndexType cPoints = m_Points.size();
         if ( cPoints == 0 )
            point.Move(0,0);
         else
         {
            // first point in list
            point = m_Points.front();
         }
        break;
      }

   default:
      ATLASSERT( false ); // Should never get here!
      break;
   }

   *x = point.X();
   *y = point.Y();
}

STDMETHODIMP CFasterPolyShape::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFasterPolyShape,
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

STDMETHODIMP CFasterPolyShape::AddPoint(Float64 x,Float64 y)
{
   m_Points.push_back( gpPoint2d(x, y) );

   MakeDirty();

   return S_OK;
}

STDMETHODIMP CFasterPolyShape::AddPointEx(IPoint2d *pPoint)
{
   CHECK_IN(pPoint);
   Float64 x, y;
   pPoint->get_X(&x);
   pPoint->get_Y(&y);

   return  AddPoint(x,y);
}

STDMETHODIMP CFasterPolyShape::AddPoints(IPoint2dCollection *pPoints)
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

STDMETHODIMP CFasterPolyShape::ChangePoint(CollectionIndexType index, Float64 x,Float64 y)
{
   if (index>=0 && index<(CollectionIndexType)m_Points.size())
   {
      gpPoint2d& rpoint = m_Points.at(index);
      if (x != rpoint.X() && y!=rpoint.Y())
      {
         rpoint.X() = x;
         rpoint.Y() = y;

         MakeDirty();
      }

      return S_OK;
   }
   else
   {
      return E_INVALIDARG;
   }
}

STDMETHODIMP CFasterPolyShape::RemovePoint(CollectionIndexType index)
{
   if (index>=0 && index<(CollectionIndexType)m_Points.size())
   {
      fpPointIterator it = m_Points.begin();
      it += index;

      fpPointIterator rit=m_Points.erase( it );

      MakeDirty();
      return S_OK;
   }
   else
   {
      return E_INVALIDARG;
   }
}

STDMETHODIMP CFasterPolyShape::get_NumPoints(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Points.size();

   return S_OK;
}

STDMETHODIMP CFasterPolyShape::GetPoint(CollectionIndexType index, Float64* pX,Float64* pY)
{
   CHECK_RETVAL(pX);
   CHECK_RETVAL(pY);

   if (index>=0 && index<(CollectionIndexType)m_Points.size())
   {
      gpPoint2d& rpoint = m_Points.at(index);
      *pX = rpoint.X();
      *pY = rpoint.Y();

      return S_OK;
   }
   else
   {
      return E_INVALIDARG;
   }
}

STDMETHODIMP CFasterPolyShape::Clear()
{
   m_Points.clear();
   MakeDirty();
   return S_OK;
}

STDMETHODIMP CFasterPolyShape::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CFasterPolyShape::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CFasterPolyShape::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);
   UpdateShapeProperties();

   return m_ShapeProps.CreateIShapeProperties(pVal);
}

void CFasterPolyShape::UpdateShapeProperties()
{

   if (m_DirtyProperties)
   {
      Float64 area, ixx, iyy, ixy;
      Float64 cgx, cgy;

      // Intialize and check for null polygon.
      area = ixx = iyy = ixy = 0.;
      cgx = 0.00;
      cgy = 0.00;

      CollectionIndexType cPoints = m_Points.size();

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
         const gpPoint2d& p0 = m_Points[idx0];
         const gpPoint2d& p1 = m_Points[idx1];

         x0 = p0.X();
         y0 = p0.Y();
         x1 = p1.X();
         y1 = p1.Y();

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
               const gpPoint2d& pStart = m_Points[idx1];
               const gpPoint2d& pEnd   = m_Points[idx0];

               if ( pStart!=pEnd )
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
      m_ShapeProps.Xleft = cgx - m_BoundingRect.Left();
      m_ShapeProps.Xright = m_BoundingRect.Right() - cgx;
      m_ShapeProps.Ytop = m_BoundingRect.Top() - cgy;
      m_ShapeProps.Ybottom = cgy - m_BoundingRect.Bottom();

      m_DirtyProperties = false;
   }
}

STDMETHODIMP CFasterPolyShape::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateBoundingBox();

    return ::CreateRect(m_BoundingRect.Left(), m_BoundingRect.Top(), m_BoundingRect.Right(), m_BoundingRect.Bottom(), pVal);
}

void CFasterPolyShape::UpdateBoundingBox()
{
   if (m_DirtyBoundingBox)
   {
      if ( m_Points.empty() )
      {
         m_BoundingRect.SetNull();
      }
      else
      {
         Float64 left   =  DBL_MAX;
         Float64 right  = -DBL_MAX;
         Float64 top    = -DBL_MAX;
         Float64 bottom =  DBL_MAX;

         for ( fpPointIterator it=m_Points.begin(); it!=m_Points.end(); it++)
         {
            Float64 x = it->X();
            Float64 y = it->Y();

            left   = _cpp_min( x, left);
            right  = _cpp_max( x, right);
            bottom = _cpp_min( y, bottom);
            top    = _cpp_max( y, top);
         }

         m_BoundingRect.Left() = left;
         m_BoundingRect.Right() = right;
         m_BoundingRect.Top() = top;
         m_BoundingRect.Bottom() = bottom;
      }

      m_DirtyBoundingBox = false;
   }
}

STDMETHODIMP CFasterPolyShape::get_PolyPoints(IPoint2dCollection** coll)
{
   CHECK_RETOBJ(coll);

   CComPtr<IPoint2dCollection> points;
   HRESULT hr = CreatePointCollection(&points);
   if (FAILED(hr))
      return hr;

   for (fpPointIterator it=m_Points.begin(); it!=m_Points.end(); it++)
   {
      Float64 x = it->X();
      Float64 y = it->Y();

      CComPtr<IPoint2d> point;
      hr = CreatePoint(x,y,NULL,&point);
      if (FAILED(hr))
         return hr;

      point->put_X(x);
      point->put_Y(y);

      hr = points->Add(point);
      if (FAILED(hr))
         return hr;
   }

   return points.CopyTo(coll);
}

STDMETHODIMP CFasterPolyShape::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   // Reference:
   // "Use of the residue theorem in locating points within an
   // arbitrary multiply-connected region"
   // G. Steven Gipson
   // Adv. Eng. Software, 1986, Vol. 8, No. 2

   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateBoundingBox();

   CollectionIndexType cPoints = m_Points.size();
   if ( cPoints < 3 )
   {
      // Points and lines can't contain anything
      ATLTRACE("*** WARNING: FasterPolyShapes must have at least 3 points\n");
      *pbResult = VARIANT_FALSE;
      return S_OK;
   }

   const Float64 angular_tolerance = TWO_PI*1e-2; // 2*pi*10^-2

   Float64 height = m_BoundingRect.Height();
   Float64 width  = m_BoundingRect.Width();

   // if height or width is zero, the point can't be in the shape.
   if ( IsZero(height) || IsZero(width) )
   {
      *pbResult = VARIANT_FALSE;
      return S_OK;
   }

   Float64 edgelen = min(width,height);

   gpPoint2d pTopLeft = m_BoundingRect.TopLeft();
   gpPoint2d pBottomRight = m_BoundingRect.BottomRight();

   Float64 dist = pTopLeft.Distance(pBottomRight);
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
      const gpPoint2d& p0 = m_Points[idx0];
      const gpPoint2d& p1 = m_Points[idx1];

      Float64 x0 = p0.X();
      Float64 y0 = p0.Y();
      Float64 x1 = p1.X();
      Float64 y1 = p1.Y();

      // no calculation if points are coincident
      if (x0 != x1 || y0 != y1)
      {

         // Compute components of two vectors formed by
         // joining point in question with endpoints of 
         // boundary segment
         Float64 xp,yp;
         GetCoordinates(pPoint,&xp,&yp);

         Float64 ax = x0 - xp;
         Float64 ay = y0 - yp;
         Float64 bx = x1 - xp;
         Float64 by = y1 - yp;

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
            gpLineSegment2d seg(x0,y0,x1,y1);

            bool bContains = seg.Contains(gpPoint2d(xp,yp));
            if ( bContains )
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
            const gpPoint2d& pStart = m_Points[idx1];
            const gpPoint2d& pEnd   = m_Points[idx0];

            if ( pStart != pEnd )
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

STDMETHODIMP CFasterPolyShape::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CFasterPolyShape>* pTheClone;
   HRESULT hr = CComObject<CFasterPolyShape>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   pTheClone->m_Points = m_Points;

   CComPtr<IFasterPolyShape> pcClone(pTheClone);
   return pcClone.QueryInterface( pClone );
}

STDMETHODIMP CFasterPolyShape::ClipWithLine(ILine2d* pcLine,IShape** pShape)
{
   // Clips on the right side of the line
   CHECK_IN(pcLine);
   CHECK_RETOBJ(pShape);

   // Convert from COM to gp objects
   gpLine2d theLine( ComLine2gpLine(pcLine) );

   return ClipWithgpLine(theLine, pShape);
}


STDMETHODIMP CFasterPolyShape::ClipWithgpLine(gpLine2d& theLine,IShape** pShape)
{
   UpdateBoundingBox();

   // Sanity check
   // If this polygon isn't at least a triangle, just get the heck outta here.
   CollectionIndexType cPoints = m_Points.size();
   if ( cPoints < 3 )
   {
      ATLTRACE("*** WARNING: FasterPolyShapes must have at least 3 points\n");
      *pShape = NULL;
      return S_OK;
   }

   // Point on the line and direction of vector
   gpVector2d vdir;
   gpPoint2d pnt_a;
   theLine.GetExplicit(&pnt_a,&vdir); 

   // Create an empty clipped Polygon - return empty if need be
   CComObject<CFasterPolyShape>* pClipShape;
   HRESULT hr = CComObject<CFasterPolyShape>::CreateInstance( &pClipShape );
   if ( FAILED(hr) )
      return hr;

   pClipShape->QueryInterface( pShape ); // Does an AddRef();

   Float64 dir_x = vdir.X();
   Float64 dir_y = vdir.Y();

   gpPoint2d pnt_b(pnt_a);
   pnt_b.Offset(-dir_x,-dir_y);

   Float64 dx, dy; // components of the direction vector of the clipping line
   Float64 nx, ny; // components of a vector normal to the clipping line
   Float64 s;      // dot product of the normal vector and the position vector
                   // of this Polygon

   Float64 ax,ay;
   Float64 bx,by;
   ax = pnt_a.X();
   ay = pnt_a.Y();
   bx = pnt_b.X();
   by = pnt_b.Y();

   dx = bx - ax;
   dy = by - ay;

   nx = -dy;
   ny =  dx;

   // get the vector of points from the Polygon and make sure that it's closed
   fpPointCollection my_points = m_Points;
   const gpPoint2d& pStart = my_points.front();
   const gpPoint2d& pEnd   = my_points.back();
   if (pStart != pEnd)
   {
      my_points.push_back( pStart );
   }

   // Start loop through points
   cPoints = my_points.size();

   gpPoint2d current;
   gpPoint2d last;
   gpPoint2d last_added;
   bool      was_last_added=false;

   CollectionIndexType idx = 0;
   bool current_out;
   bool last_out;

   last = my_points[idx++];

   Float64 lx,ly;
   lx = last.X();
   ly = last.Y();

   s = nx*(lx - ax) + ny*(ly - ay);

   last_out = ( s < 0 ) ? true : false;

   if ( !last_out )
   {
      was_last_added = true;

      pClipShape->m_Points.push_back( gpPoint2d(lx,ly) );
   }

   gpLine2d line2; // Line to be clipped
   do
   {
      current = my_points[idx++];

      Float64 cx,cy;
      cx = current.X();
      cy = current.Y();
      s = nx*(cx - ax) + ny*(cy - ay);
      current_out = ( s < 0 ) ? true : false;

      if ( last_out && !current_out ||
          !last_out &&  current_out )
      {
         // Find intersection
         line2.SetPoints(last,current);

         gpPoint2d intersect;
         Int16 st = gpGeomOp2d::Intersect(&intersect, theLine, line2);
         ATLASSERT(st == 1);

         // don't add duplicate points
         if (!(was_last_added && intersect==last_added))
         {
            last_added = intersect;
            was_last_added = true;

            pClipShape->m_Points.push_back( last_added );
         }
      }

      if ( !current_out && !(was_last_added && current==last_added))
      {
         last_added = current;
         was_last_added = true;
         pClipShape->m_Points.push_back( current );
      }

      last = current;
      last_out = current_out;

   } while ( idx < cPoints );

   // make sure clipped Polygon has enough points to be interesting
   // If there are less than 3 points, it isn't a shape.
   // If there are exactly 3 points, and the first and last points are the same
   // it isn't a shape either (area is zero)
   CollectionIndexType nPoints = pClipShape->m_Points.size();
   bool bIsLine = false;
   if ( nPoints == 3 )
   {
      bIsLine = pClipShape->m_Points.front() == pClipShape->m_Points.back();
   }

   if ( nPoints < 3 || bIsLine )
   {
      (*pShape)->Release();
      *pShape = 0;
      return S_OK;
   }

   return S_OK;
}

STDMETHODIMP CFasterPolyShape::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   // Assume no clip
   *pShape = NULL;

   // Before we do anything, make sure there is a chance for this shape to be clipped
   // Check if we are inside, outside, or intersect this rect
   UpdateBoundingBox();

   Float64 cLeft, cRight, cBottom, cTop; // clipping box coords
   pRect->GetBounds(&cLeft, &cRight, &cBottom, &cTop);

   gpRect2d clipBox(cLeft, cBottom, cRight, cTop);

   gpRect2d::rctPosition rpos = clipBox.GetPosition(m_BoundingRect);
   if (rpos==gpRect2d::rpOutside)
   {
      // entire shape is outside so nothing will remain after clipping
      return S_OK;
   }
   else if (rpos==gpRect2d::rpContains)
   {
      // entire shape is inside so the entire shape will remain after clipping
      Clone(pShape);
      return S_OK;
   }

   // Now we must clip
   // Clip using top edge
   CComPtr<IShape> pClipTop;
   Float64 sTop = m_BoundingRect.Top();

   gpVector2d vector;

   if ( sTop > cTop)
   {
      vector.SetSize(0.0, 1.0);
      gpLine2d line(cTop, vector);
      ClipWithgpLine(line,&pClipTop);
   }
   else
   {
      Clone(&pClipTop);
   }

   if ( pClipTop == NULL ) // Resulting Shape is Nothing
   {
      ATLASSERT(0); // should not happen because we have checked clip box above
      return S_OK;
   }

   // Clip using Right edge
   CComPtr<IShape> pClipRight;
   Float64 sRight = m_BoundingRect.Right();
   if ( sRight > cRight)
   {
      CFasterPolyShape* pPolyTop = dynamic_cast<CFasterPolyShape*>(pClipTop.p); // we made it, we can cast it

      vector.SetSize(1.0, 0.0);
      gpLine2d line(cRight, vector);
      pPolyTop->ClipWithgpLine(line,&pClipRight);
   }
   else
   {
      // no need to clone, just copy
      pClipTop.CopyTo(&pClipRight);
   }

   if ( pClipRight == 0 ) // Resulting Shape is Nothing
   {
      ATLASSERT(0); // should not happen because we have checked clip box above
      return S_OK;
   }

   // Clip using Bottom edge
   CComPtr<IShape> pClipBottom;
   Float64 sBottom = m_BoundingRect.Bottom();
   if ( sBottom < cBottom)
   {
      CFasterPolyShape* pPolyRight = dynamic_cast<CFasterPolyShape*>(pClipRight.p); // we made it, we can cast it

      vector.SetSize(0.0, -1.0);
      gpLine2d line(-1.0*cBottom, vector);
      pPolyRight->ClipWithgpLine(line,&pClipBottom);
   }
   else
   {
      pClipRight.CopyTo(&pClipBottom);
   }

   if ( pClipBottom == 0 ) // Resulting Shape is Nothing
   {
//      ATLASSERT(0); // should not happen because we have checked clip box above. actually does happen when shapes just touch
      return S_OK;
   }

   // Clip using Left edge
   CComPtr<IShape> pClipLeft;
   Float64 sLeft = m_BoundingRect.Left();
   if ( sLeft < cLeft)
   {
      CFasterPolyShape* pPolyBottom = dynamic_cast<CFasterPolyShape*>(pClipBottom.p); // we made it, we can cast it

      vector.SetSize(-1.0, 0.0);
      gpLine2d line(-1.0*cLeft, vector);
      pPolyBottom->ClipWithgpLine(line,&pClipLeft);
   }
   else
   {
      pClipBottom.CopyTo(&pClipLeft);
   }

   if ( pClipLeft == 0 ) // Resulting Shape is Nothing
   {
      ATLASSERT(0); // should not happen because we have checked clip box above
      return S_OK;
   }

   pClipLeft->QueryInterface(pShape);

   return S_OK;
}

//
//STDMETHODIMP CFasterPolyShape::ClipOut(IRect2d* pRect,IShape** pShape)
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

STDMETHODIMP CFasterPolyShape::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CollectionIndexType cPoints = m_Points.size();
   if (cPoints<=1)
   {
      *pVal = 0.0;
      return S_OK;
   }

   // Get the distance between the first and last point.
   // If the polygon is closed, it will be zero.
   const gpPoint2d& pStart = m_Points.front();
   const gpPoint2d& pEnd   = m_Points.back();

   Float64 last_dist = pStart.Distance(pEnd);

   // Loop to get rest
   Float64 sum = 0.00;
   for ( CollectionIndexType idx = 1; idx < cPoints; idx++ )
   {
      const gpPoint2d& p1 = m_Points[idx-1];
      const gpPoint2d& p2 = m_Points[idx];

      Float64 dist = p1.Distance(p2);

      sum += dist;
   }

   sum += last_dist;

   *pVal = sum;

   return S_OK;
}

STDMETHODIMP CFasterPolyShape::FurthestDistance(ILine2d* pcLine, Float64 *pVal)
{
   CHECK_IN(pcLine);
   CHECK_RETVAL(pVal);

   // Convert from COM to gp objects
   gpLine2d theLine( ComLine2gpLine(pcLine) );

   Float64 maxDist = -DBL_MAX;

   for ( fpPointIterator it=m_Points.begin(); it!=m_Points.end(); it++ )
   {
      const gpPoint2d& rPoint = *it;

      // Multiply by -1.0 becase gp convention is opposite com convention
      Float64 dist = -1.0 * theLine.DistanceToPoint(rPoint);
      maxDist = _cpp_max( maxDist, dist );
   }

   *pVal = maxDist;

   return S_OK;

}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CFasterPolyShape::Offset(Float64 dx,Float64 dy)
{
   for ( fpPointIterator it=m_Points.begin(); it!=m_Points.end(); it++ )
   {
      gpPoint2d& rPoint = *it;
      rPoint.Offset(dx,dy);
   }

   MakeDirty();

   return S_OK;
}

STDMETHODIMP CFasterPolyShape::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   GetSize(pSize,&dx,&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CFasterPolyShape::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,NULL,point);
}

STDMETHODIMP CFasterPolyShape::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CFasterPolyShape::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CFasterPolyShape::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);
   return Rotate(x,y,angle);
}


STDMETHODIMP CFasterPolyShape::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   if (IsZero(angle, 1.0e-06))
   {
      return S_OK;
   }
   else
   {
      gpPoint2d cpoint(cx,cy);

      for ( fpPointIterator it=m_Points.begin(); it!=m_Points.end(); it++ )
      {
         gpPoint2d& rPoint = *it;
         rPoint.Rotate(cpoint, angle);
      }

      MakeDirty();

      return S_OK;
   }
}

STDMETHODIMP CFasterPolyShape::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CFasterPolyShape::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CFasterPolyShape::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("FasterPolyShape"),1.0);
   pSave->put_Property(CComBSTR("NumPoints"), CComVariant(m_Points.size()));
   for ( fpPointIterator it=m_Points.begin(); it!=m_Points.end(); it++ )
   {
      const gpPoint2d& rPoint = *it;
      pSave->BeginUnit(CComBSTR("Point"),1.0);
      pSave->put_Property(CComBSTR("X"), CComVariant(rPoint.X()));
      pSave->put_Property(CComBSTR("Y"), CComVariant(rPoint.Y()));
      pSave->EndUnit();
   }
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CFasterPolyShape::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   pLoad->BeginUnit(CComBSTR("FasterPolyShape"));
   
   CComVariant var;
   HRESULT hr =pLoad->get_Property(CComBSTR("NumPoints"),&var);
   if (FAILED(hr))
      return STRLOAD_E_INVALIDFORMAT;

   CollectionIndexType num_pts = var.iVal;
   for(CollectionIndexType i=0; i<num_pts; i++)
   {
      hr = pLoad->BeginUnit(CComBSTR("Point"));
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = pLoad->get_Property(CComBSTR("X"),&var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      Float64 x = var.dblVal;
      
      pLoad->get_Property(CComBSTR("Y"),&var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      Float64 y = var.dblVal;

      VARIANT_BOOL bEnd;
      pLoad->EndUnit(&bEnd);

      m_Points.push_back(gpPoint2d(x,y));
   }

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

void CFasterPolyShape::ShapeProps::Init()
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

HRESULT CFasterPolyShape::ShapeProps::CreateIShapeProperties(IShapeProperties ** props)
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
