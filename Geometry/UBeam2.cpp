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

// UBeam2.cpp : Implementation of CUBeam2 
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "UBeam2.h"
#include "Helper.h"
#include <MathEx.h>
#include <float.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUBeam2
HRESULT CUBeam2::FinalConstruct()
{
   m_Rotation = 0.00;
   m_D1 = 0.00;
   m_D2 = 0.00;
   m_D3 = 0.00;
   m_D4 = 0.00;
   m_D5 = 0.00;
   m_D6 = 0.00;
   m_W1 = 0.00;
   m_W2 = 0.00;
   m_W3 = 0.00;
   m_W4 = 0.00;
   m_W5 = 0.00;
   m_W6 = 0.00;
   m_W7 = 0.00;
   m_C1 = 0.00;
   m_bUseOutlineOnly = VARIANT_FALSE;

   CreatePoint( 0.00, 0.00, nullptr, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreatePolyShape( &m_pShape );

   CreatePoint(0,0,nullptr,&m_P2);
   CreatePoint(0,0,nullptr,&m_P3);
   CreatePoint(0,0,nullptr,&m_P8);
   CreateLine(m_P2,m_P3,nullptr,&m_OuterWebLine);
   CreateGeomUtil(&m_GeomUtil);

   m_Dirty = true;

   return S_OK;
}

void CUBeam2::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}


STDMETHODIMP CUBeam2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUBeam2,
      &IID_IShape,
      &IID_IXYPosition,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CUBeam2::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
{
   ATLASSERT(px != nullptr && py != nullptr);

   HRESULT hr;
   hr = UpdateShape();
   if (FAILED(hr))
      return hr;

   CComPtr<IPoint2d> pPoint;

   if (lp == lpHookPoint)
   {
      pPoint = m_pHookPoint;
   }
   else
   {
      CComQIPtr<IShape> pShape(m_pShape);
      CComPtr<IRect2d> pBox;
      pShape->get_BoundingBox(&pBox);

      switch (lp)
      {
      case lpTopLeft:
         pBox->get_TopLeft(&pPoint);
         break;

      case lpTopCenter:
         pBox->get_TopCenter(&pPoint);
         break;

      case lpTopRight:
         pBox->get_TopRight(&pPoint);
         break;

      case lpCenterLeft:
         pBox->get_CenterLeft(&pPoint);
         break;

      case lpCenterCenter:
         pBox->get_CenterCenter(&pPoint);
         break;

      case lpCenterRight:
         pBox->get_CenterRight(&pPoint);
         break;

      case lpBottomLeft:
         pBox->get_BottomLeft(&pPoint);
         break;

      case lpBottomCenter:
         pBox->get_BottomCenter(&pPoint);
         break;

      case lpBottomRight:
         pBox->get_BottomRight(&pPoint);
         break;

      case lpHookPoint:
      default:
         ATLASSERT(false); // Should never get here
      }
   }

   GetCoordinates(pPoint, px, py);

   return S_OK;
}

HRESULT CUBeam2::UpdateShape()
{
   if (m_Dirty)
   {
      // clear the polygon implemenation and recalculate all of the points
      m_pShape->Clear();

      // compute wall slope
      Float64 slope;
      get_Slope(1,&slope);

      // start at the bottom center and go around clockwise
      // Hook point is at bottom center (0,0)
      // Compute left side points, mirror for right side
      Float64 p1_x =  0.;
      Float64 p1_y =  0.;

      Float64 p2_x = -m_W1/2;
      Float64 p2_y =  0.;

      Float64 p3_x =  p2_x - (IsZero(slope) ? 0: (m_D1 - m_D4 - m_D5)/slope);
      Float64 p3_y =  m_D1 - m_D4 - m_D5;

      Float64 p4_x =  -m_W2/2 + m_W4;
      Float64 p4_y =  m_D1 - m_D5;

      Float64 p5_x =  -m_W2/2;
      Float64 p5_y =  m_D1;

      Float64 p6_x =  -m_W2/2 + m_W6;
      Float64 p6_y =  p5_y;

      Float64 p7_x =  p6_x + m_W7;
      Float64 p7_y =  p6_y - m_D6;

      Float64 p8_x =  p7_x + (IsZero(slope) ? 0 : (m_D1 - m_D6 - m_D2 - m_D3)/slope);
      Float64 p8_y =  m_D2 + m_D3;

      Float64 p9_x =  p8_x + m_W3;
      Float64 p9_y =  m_D2;

      // next build chamfer points if needed
      Float64 p2a_x(0), p2b_x(0);
      Float64 p2a_y(0), p2b_y(0);

      Float64 p4a_x(0), p4b_x(0);
      Float64 p4a_y(0), p4b_y(0);

      bool is_chamfer = m_C1>0.0;
      if (is_chamfer)
      {
         ProjectPointAlongLine(p2_x, p2_y, p1_x, p1_y, m_C1, &p2a_x, &p2a_y);
         ProjectPointAlongLine(p2_x, p2_y, p3_x, p3_y, m_C1, &p2b_x, &p2b_y);

         ProjectPointAlongLine(p4_x, p4_y, p3_x, p3_y, m_C1, &p4a_x, &p4a_y);
         ProjectPointAlongLine(p4_x, p4_y, p5_x, p5_y, m_C1, &p4b_x, &p4b_y);
      }

      m_pShape->AddPoint( p1_x, p1_y);  // 1

      if (is_chamfer)
      {
         m_pShape->AddPoint( p2a_x, p2a_y);
         m_pShape->AddPoint( p2b_x, p2b_y);
      }
      else
      {
         m_pShape->AddPoint( p2_x, p2_y);
      }

      m_pShape->AddPoint( p3_x, p3_y);

      if (is_chamfer)
      {
         m_pShape->AddPoint( p4a_x, p4a_y);
         m_pShape->AddPoint( p4b_x, p4b_y);
      }
      else
      {
         m_pShape->AddPoint( p4_x, p4_y);
      }

      m_pShape->AddPoint( p5_x, p5_y);

      // Using the outline of the shape only
      // place the inner points along the top edge of the shape
      if (m_bUseOutlineOnly == VARIANT_TRUE)
      {
         m_pShape->AddPoint( p6_x, p6_y);
         m_pShape->AddPoint( p7_x, p6_y);
         m_pShape->AddPoint( p8_x, p6_y);
         m_pShape->AddPoint( p9_x, p6_y);

         // mirror points
         m_pShape->AddPoint(-p9_x, p6_y);
         m_pShape->AddPoint(-p8_x, p6_y);
         m_pShape->AddPoint(-p7_x, p6_y);
         m_pShape->AddPoint(-p6_x, p6_y); 
      }
      else
      {
         m_pShape->AddPoint( p6_x, p6_y);
         m_pShape->AddPoint( p7_x, p7_y);
         m_pShape->AddPoint( p8_x, p8_y);
         m_pShape->AddPoint( p9_x, p9_y);

         // mirror points
         m_pShape->AddPoint(-p9_x, p9_y);
         m_pShape->AddPoint(-p8_x, p8_y);
         m_pShape->AddPoint(-p7_x, p7_y);
         m_pShape->AddPoint(-p6_x, p6_y); 
      }

      m_pShape->AddPoint(-p5_x, p5_y);

      if (is_chamfer)
      {
         m_pShape->AddPoint(-p4b_x, p4b_y);
         m_pShape->AddPoint(-p4a_x, p4a_y);
      }
      else
      {
         m_pShape->AddPoint(-p4_x, p4_y);
      }

      m_pShape->AddPoint(-p3_x, p3_y);

      if (is_chamfer)
      {
         m_pShape->AddPoint(-p2b_x, p2b_y);
         m_pShape->AddPoint(-p2a_x, p2a_y);
      }
      else
      {
         m_pShape->AddPoint(-p2_x, p2_y);
      }


      m_P2->Move(p2_x, p2_y);
      m_P3->Move(p3_x, p3_y);
      m_P8->Move(p8_x, p8_y);
      m_OuterWebLine->ThroughPoints(m_P2, m_P3);
      m_GeomUtil->ShortestOffsetToPoint(m_OuterWebLine, m_P8, &m_T);


#ifdef _DEBUG
      //CComPtr<IPoint2dCollection> points;
      //m_pShape->get_Points(&points);
      //IndexType npts;
      //points->get_Count(&npts);
      //ATLTRACE("Trace of Points for UBeam2 - count = %d \n", npts);
      //ATLTRACE("  pt         X         Y\n");
      //ATLTRACE("---------------------------------\n");
      //for (IndexType ip = 0; ip<npts; ip++)
      //{
      //   CComPtr<IPoint2d> pnt;
      //   points->get_Item(ip, &pnt);
      //   Float64 x, y;
      //   pnt->get_X(&x);
      //   pnt->get_Y(&y);
      //   ATLTRACE(" %4d  %10f %10f \n", ip, x, y);
      //}
      //ATLTRACE("---------------------------\n");
#endif

      CComQIPtr<IXYPosition> pPosition(m_pShape);

      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00,0.00,m_Rotation);
      }

      CComPtr<IPoint2d> origin;
      CreatePoint(0.00,0.00,nullptr,&origin);  // Hook Point at Bottom Center
      pPosition->MoveEx(origin,m_pHookPoint);

      m_Dirty = false;
   }

   return S_OK;
}



STDMETHODIMP CUBeam2::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W1;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_W1 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W2;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_W2 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W3;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_W3 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W4;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_W4 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W5;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_W5 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W6;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W6(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_W6 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W7(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W7;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W7(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_W7 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D1;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_D1 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D2;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_D2 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D3;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_D3 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D4;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_D4 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D5;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_D5 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D6;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D6(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_D6 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C1;
   return S_OK;
}

STDMETHODIMP CUBeam2::put_C1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_C1 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_T(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   *pVal = m_T;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_Slope(WebIndexType webIdx,Float64* slope)
{
   CHECK_RETVAL(slope);
   if ( webIdx < 0 || 2 <= webIdx )
      return E_INVALIDARG;

   Float64 rise = m_D1 - m_D4 - m_D5;
   Float64 run = (m_W2 - m_W1)/2 - m_W4 - m_W5;

   if ( IsZero(run) )
      *slope = DBL_MAX;
   else
      *slope = rise/run;

   if ( webIdx == 0 )
      (*slope) *= -1;

   return S_OK;
}

STDMETHODIMP CUBeam2::get_TopWidth(Float64* width)
{
   CHECK_RETVAL(width);
   *width = m_W2;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_TopFlangeWidth(Float64* width)
{
   CHECK_RETVAL(width);

   if (m_bUseOutlineOnly == VARIANT_TRUE)
   {
      // if the shape is just the outline of the U-beam,
      // then the top flange is half the width of the beam
      (*width) = m_W2/2;
   }
   else
   {
      // otherwise it is the normal input value
      (*width) = m_W6;
   }

   return S_OK;
}

STDMETHODIMP CUBeam2::get_WebLocation(WebIndexType webIdx,Float64* location)
{
   CHECK_RETVAL(location);
   if ( webIdx < 0 || 2 <= webIdx )
      return E_INVALIDARG;

   Float64 sign = (webIdx == 0) ? -1 : 1;
   Float64 top_width;
   Float64 slope;

   get_TopWidth(&top_width);
   get_Slope(webIdx,&slope);
   slope = fabs(slope);
   Float64 t;
   
   get_T(&t);
   (*location) = sign*(m_D1/slope - 0.5*t*sqrt(slope*slope+1)/slope + m_W1/2);

   return S_OK;
}

STDMETHODIMP CUBeam2::get_WebSpacing(Float64* spacing)
{
   CHECK_RETVAL(spacing);

   Float64 top_width;
   Float64 slope;

   get_TopWidth(&top_width);
   get_Slope(0,&slope);
   slope = fabs(slope);

   Float64 t;
   get_T(&t);

   (*spacing) = m_W1 - t*sqrt(slope*slope+1)/slope + 2*m_D1/slope;

   return S_OK;
}

STDMETHODIMP CUBeam2::put_UseOutlineOnly(VARIANT_BOOL bUseOutlineOnly)
{
   MakeDirty();

   m_bUseOutlineOnly = bUseOutlineOnly;

   return S_OK;
}

STDMETHODIMP CUBeam2::get_UseOutlineOnly(VARIANT_BOOL* pUseOutlineOnly)
{
   CHECK_RETVAL(pUseOutlineOnly);

   *pUseOutlineOnly = m_bUseOutlineOnly;
   return S_OK;
}

STDMETHODIMP CUBeam2::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.CopyTo( hookPnt );

   return S_OK;
}

STDMETHODIMP CUBeam2::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CUBeam2::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D1;

	return S_OK;
}

STDMETHODIMP CUBeam2::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CUBeam2::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CUBeam2::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CUBeam2::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CUBeam2::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CUBeam2::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CUBeam2::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CUBeam2>* pTheClone;
   HRESULT hr = CComObject<CUBeam2>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IUBeam2> shape(pTheClone); // need at least one reference

   pTheClone->put_D1( m_D1 );
   pTheClone->put_D2( m_D2 );
   pTheClone->put_D3( m_D3 );
   pTheClone->put_D4( m_D4 );
   pTheClone->put_D5( m_D5 );
   pTheClone->put_D6( m_D6 );
   pTheClone->put_W1( m_W1 );
   pTheClone->put_W2( m_W2 );
   pTheClone->put_W3( m_W3 );
   pTheClone->put_W4( m_W4 );
   pTheClone->put_W5( m_W5 );
   pTheClone->put_W6( m_W6 );
   pTheClone->put_W7( m_W7 );
   pTheClone->put_C1( m_C1 );
   pTheClone->put_UseOutlineOnly(m_bUseOutlineOnly);

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,nullptr,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CUBeam2::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CUBeam2::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CUBeam2::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CUBeam2::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->FurthestDistance(line,pVal);
}

STDMETHODIMP CUBeam2::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}
/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CUBeam2::Offset(Float64 dx,Float64 dy)
{
   if (m_Dirty)
   {
      // this is going to fire an event that sets m_Dirty to true... since it is already true
      // no need to worry about it
      m_pHookPoint->Offset(dx, dy);
   }
   else
   {
      // We are just offsetting... detach from m_pHookPoint events so we don't invalidate
      // everything about this shape...
      CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
      m_pHookPoint->Offset(dx, dy); // offset the hook point
      CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);

      CComQIPtr<IXYPosition> pos(m_pShape);
      pos->Offset(dx, dy); // offset the shape
   }
   return S_OK;
}

STDMETHODIMP CUBeam2::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CUBeam2::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,nullptr,point);
}

STDMETHODIMP CUBeam2::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{

   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CUBeam2::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   Float64 x1,y1;
   Float64 x2,y2;

   GetCoordinates(pFrom,&x1,&y1);
   GetCoordinates(pTo,&x2,&y2);

   Float64 dx = x2 - x1;
   Float64 dy = y2 - y1;

   return Offset(dx,dy);
}

STDMETHODIMP CUBeam2::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CUBeam2::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to call MakeDirty since our hookpoint will call us back

   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


// IPersist
STDMETHODIMP CUBeam2::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CUBeam2::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("UBeam2"),3.0);
   pSave->put_Property(CComBSTR("D1"),CComVariant(m_D1));
   pSave->put_Property(CComBSTR("D2"),CComVariant(m_D2));
   pSave->put_Property(CComBSTR("D3"),CComVariant(m_D3));
   pSave->put_Property(CComBSTR("D4"),CComVariant(m_D4));
   pSave->put_Property(CComBSTR("D5"),CComVariant(m_D5));
   pSave->put_Property(CComBSTR("D6"),CComVariant(m_D6));
   pSave->put_Property(CComBSTR("W1"),CComVariant(m_W1));
   pSave->put_Property(CComBSTR("W2"),CComVariant(m_W2));
   pSave->put_Property(CComBSTR("W3"),CComVariant(m_W3));
   pSave->put_Property(CComBSTR("W4"),CComVariant(m_W4));
   pSave->put_Property(CComBSTR("W5"),CComVariant(m_W5));
   pSave->put_Property(CComBSTR("W6"),CComVariant(m_W6));
   pSave->put_Property(CComBSTR("W7"),CComVariant(m_W7));
   pSave->put_Property(CComBSTR("C1"),CComVariant(m_C1)); // C1 added in version 2.0
   pSave->put_Property(CComBSTR("UseOutlineOnly"),CComVariant(m_bUseOutlineOnly)); // added in version 3.0
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CUBeam2::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("UBeam2"));
   
   Float64 version;
   pLoad->get_Version(&version);

   if (2.0 < version )
      return STRLOAD_E_BADVERSION;

   pLoad->get_Property(CComBSTR("D1"),&var);
   m_D1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D2"),&var);
   m_D2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D3"),&var);
   m_D3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D4"),&var);
   m_D4 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D5"),&var);
   m_D5 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D6"),&var);
   m_D6 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W1"),&var);
   m_W1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W2"),&var);
   m_W2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W3"),&var);
   m_W3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W4"),&var);
   m_W4 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W5"),&var);
   m_W5 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W6"),&var);
   m_W6 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W7"),&var);
   m_W7 = var.dblVal;

   if ( 2.0 <= version )
   {
      pLoad->get_Property(CComBSTR("C1"),&var);
      m_C1 = var.dblVal;
   }
   else
   {
      m_C1 = 0.0;
   }

   if ( 3.0 <= version )
   {
      pLoad->get_Property(CComBSTR("UseOutlineOnly"),&var);
      m_bUseOutlineOnly = var.boolVal;
   }
   else
   {
      m_bUseOutlineOnly = VARIANT_FALSE;
   }

   pLoad->get_Property(CComBSTR("Rotation"),&var);
   m_Rotation = var.dblVal;

   pLoad->get_Property(CComBSTR("HookPoint"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pHookPoint,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   UpdateShape();

   return S_OK;
}


STDMETHODIMP CUBeam2::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
