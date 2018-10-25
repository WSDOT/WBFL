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

// MultiWeb2.cpp : Implementation of CMultiWeb2
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "MultiWeb2.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// CMultiWeb2
HRESULT CMultiWeb2::FinalConstruct()
{
   m_Rotation = 0.00;
   m_H1       = 0.00;
   m_H2       = 0.00;
   m_H3       = 0.00;
   m_W1       = 0.00;
   m_W2       = 0.00;
   m_T1       = 0.00;
   m_T2       = 0.00;
   m_T3       = 0.00;
   m_T4       = 0.00;
   m_T5       = 0.00;
   m_F1       = 0.00;
   m_F2       = 0.00;
   m_C1       = 0.00;
   m_C2       = 0.00;
   m_WebCount = 0;
   m_bLeftBlockOut = VARIANT_TRUE;
   m_bRightBlockOut = VARIANT_TRUE;

   CreatePoint( 0.00, 0.00, NULL, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreatePolyShape( &m_pShape );

   m_Dirty = true;

   return S_OK;
}

void CMultiWeb2::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CMultiWeb2::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IMultiWeb2,
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

HRESULT CMultiWeb2::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
{
   ATLASSERT(px != NULL && py != NULL);

   UpdateShape();

   CComPtr<IPoint2d> pPoint;

   CComQIPtr<IShape> pShape(m_pShape);
   CComPtr<IRect2d> pBox;
   pShape->get_BoundingBox(&pBox);

   switch(lp)
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
   case lpHookPoint:
      pBox->get_BottomCenter(&pPoint);
      break;

   case lpBottomRight:
      pBox->get_BottomRight(&pPoint);
      break;

   default:
      ATLASSERT(false); // Should never get here
   }

   GetCoordinates(pPoint,px,py);

   return S_OK;
}

HRESULT CMultiWeb2::UpdateShape()
{
   if (m_Dirty)
   {
      // clear the polygon implemenation and recalculate all of the points
      m_pShape->Clear();

      Float64 W;
      get_TopFlangeWidth(&W);

      Float64 H = m_H1+m_H2+m_H3;

      // start at top left and go around clockwise

      // top left
      Float64 p1_x = (m_bLeftBlockOut==VARIANT_FALSE) ? 0.0 : m_C2;
      Float64 p1_y = 0.;
      m_pShape->AddPoint( p1_x, p1_y );

      // top right
      Float64 p2_x = (m_bRightBlockOut==VARIANT_FALSE) ? W : W-m_C2;
      Float64 p2_y = 0;
      m_pShape->AddPoint( p2_x, p2_y );

      // top right, bottom of top flange
      Float64 p3_x = W;
      Float64 p3_y = -m_H3;
      m_pShape->AddPoint( p3_x, p3_y );

      // corner at outside of right outside web, top of fillet
      Float64 p4_x = W - m_W1 + m_F1;
      Float64 p4_y = -(m_H2 + m_H3);
      m_pShape->AddPoint( p4_x, p4_y );

      // corner at outside of right outside web, bottom of fillet
      Float64 p5_x = W - m_W1;
      Float64 p5_y = -(m_H2 + m_H3 + m_F1);
      m_pShape->AddPoint( p5_x, p5_y );

      // bottom right corner of right web
      // if no chamfer, computation is simple
      Float64 p6_x = W - m_W1 - m_T1;
      Float64 p6_y = -H;

      if (m_C1<=0.0)
      {
         m_pShape->AddPoint( p6_x, p6_y );
      }
      else
      {
         // must compute chamfer locations along outside of right outside web
         // a is first location b is second
         Float64 p6a_x, p6a_y;

         ProjectPointAlongLine(p6_x, p6_y, p5_x, p5_y, m_C1, &p6a_x, &p6a_y);
         m_pShape->AddPoint( p6a_x, p6a_y );

         Float64 p6b_x = p6_x - m_C1;
         Float64 p6b_y = p6_y;
         m_pShape->AddPoint( p6b_x, p6b_y );
      }

      // bottom left corner of right web - again, chamfer is an issue
      Float64 p7_x = W - m_W1 - m_T1 - m_T2;
      Float64 p7_y = -H;

      // corner at inside of right web, bottom of fillet
      Float64 p8_x = p7_x - m_T3;
      Float64 p8_y = -H + m_H1 - m_F1;

      if (m_C1<=0.0)
      {
         m_pShape->AddPoint( p7_x, p7_y );
      }
      else
      {
         // must compute chamfer locations along inside of right outside web
         // a is first location b is second
         Float64 p7a_x = p7_x + m_C1;
         Float64 p7a_y = p7_y;
         m_pShape->AddPoint( p7a_x, p7a_y );

         Float64 p7b_x, p7b_y;
         ProjectPointAlongLine(p7_x, p7_y, p8_x, p8_y, m_C1, &p7b_x, &p7b_y);
         m_pShape->AddPoint( p7b_x, p7b_y );
      }

      m_pShape->AddPoint( p8_x, p8_y );

      // corner at inside of right web, top of fillet
      Float64 p9_x = p8_x - m_F1;
      Float64 p9_y = p8_y + m_F1;
      m_pShape->AddPoint( p9_x, p9_y );

      // loop over all the interior webs
      Float64 x1 = W - (m_W1 + m_T1+ m_T2+m_T3 + m_W2 - m_F2);
      Float64 y1 = -H + m_H1;

      for ( WebIndexType webIdx = 1; webIdx < m_WebCount-1; webIdx++ )
      {
         m_pShape->AddPoint(x1,y1);

         // top right corner of web, above fillet
         // work clockwise around the web
         Float64 x2 = x1 - m_F2;
         Float64 y2 = y1 - m_F2;
         m_pShape->AddPoint(x2,y2);

         // add chamfer at right side of web if needed
         Float64 x3 = x2 - m_T4;
         Float64 y3 = -H;

         if (m_C1<=0.0)
         {
            m_pShape->AddPoint( x3, y3 );
         }
         else
         {
            // must compute chamfer locations along right side of inside web
            // a is first location b is second
            Float64 x3_a, y3_a;

            ProjectPointAlongLine(x3, x3, x2, x2, m_C1, &x3_a, &y3_a);
            m_pShape->AddPoint( x3_a, y3_a );

            Float64 x3_b = x3 - m_C1;
            Float64 y3_b = y3;
            m_pShape->AddPoint( x3_b, y3_b );
         }

         Float64 x4 = x3 - m_T5;
         Float64 y4 = y3;

         Float64 x5 = x4 - m_T4;
         Float64 y5 = y4 + m_H1 - m_F2;

         if (m_C1<=0.0)
         {
            m_pShape->AddPoint( x4, y4 );
         }
         else
         {
            // must compute chamfer locations along left side of inside web
            Float64 x4_a = x4 + m_C1;
            Float64 y4_a = y4;
            m_pShape->AddPoint( x4_a, y4_a );

            Float64 x4_b, y4_b;
            ProjectPointAlongLine(x4, y4, x5, y5, m_C1, &x4_b, &y4_b);
            m_pShape->AddPoint( x4_b, y4_b );
         }

         Float64 x6 = x5 - m_F2;
         Float64 y6 = y5 + m_F2;

         m_pShape->AddPoint(x5,y5);
         m_pShape->AddPoint(x6,y6);

         x1 = x6 - (m_W2 - 2*m_F2);
      }

      // left exterior web

      // inside right corner of left web... top of fillet
      Float64 p10_x = m_W1 + m_T1+m_T2+m_T3 + m_F1;
      Float64 p10_y = p9_y;
      m_pShape->AddPoint( p10_x, p10_y);

      Float64 p11_x = p10_x - m_F1;
      Float64 p11_y = p9_y - m_F1;
      m_pShape->AddPoint( p11_x, p11_y);

      // right side bottom
      Float64 p12_x = p11_x - m_T3;
      Float64 p12_y = -H;

      if (m_C1<=0.0)
      {
         m_pShape->AddPoint( p12_x, p12_y );
      }
      else
      {
         // must compute chamfer locations along right side of left outside web
         Float64 p12a_x, p12a_y;

         ProjectPointAlongLine(p12_x, p12_y, p11_x, p11_y, m_C1, &p12a_x, &p12a_y);
         m_pShape->AddPoint( p12a_x, p12a_y );

         Float64 p12b_x = p12_x - m_C1;
         Float64 p12b_y = p12_y;
         m_pShape->AddPoint( p12b_x, p12b_y );
      }
      
      Float64 p13_x = p12_x - m_T2;
      Float64 p13_y = p12_y;

      Float64 p14_x = p13_x - m_T1;
      Float64 p14_y = p5_y;


      if (m_C1<=0.0)
      {
         m_pShape->AddPoint( p13_x, p13_y );
      }
      else
      {
         // must compute chamfer locations along left side of left outside web
         // a is first location b is second
         Float64 p13a_x = p13_x + m_C1;
         Float64 p13a_y = p13_y;
         m_pShape->AddPoint( p13a_x, p13a_y );

         Float64 p13b_x, p13b_y;
         ProjectPointAlongLine(p13_x, p13_y, p14_x, p14_y, m_C1, &p13b_x, &p13b_y);
         m_pShape->AddPoint( p13b_x, p13b_y );
      }

      m_pShape->AddPoint( p14_x, p14_y);

      Float64 p15_x = p14_x - m_F1;
      Float64 p15_y = p14_y + m_F1;

      Float64 p16_x = 0;
      Float64 p16_y = -m_H3;

      m_pShape->AddPoint( p15_x, p15_y);
      m_pShape->AddPoint( p16_x, p16_y);

      // close the shape
      m_pShape->AddPoint( p1_x, p1_y);


      // move the shape so that the bottom center is at (0,0)
      CComQIPtr<IXYPosition> pPosition(m_pShape);
      pPosition->Offset(-W/2,H);

      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00,0.00,m_Rotation);
      }

      CComPtr<IPoint2d> origin;
      CreatePoint(0.00,0.00,NULL,&origin);  // Hook Point at Bottom Center
      pPosition->MoveEx(origin,m_pHookPoint);

      m_Dirty = false;
   }

   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W1;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_W1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_W1 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W2;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_W2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_W2 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_H1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_H1;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_H1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_H1 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_H2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_H2;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_H2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_H2 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_H3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_H3;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_H3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_H3 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_T1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T1;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_T1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_T1 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_T2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T2;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_T2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_T2 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_T3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T3;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_T3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_T3 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_T4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T4;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_T4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_T4 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_T5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T5;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_T5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_T5 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_F1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_F1;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_F1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_F1 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_F2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_F2;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_F2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_F2 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C1;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_C1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_C1 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_C2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C2;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_C2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_C2 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_WebCount(WebIndexType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_WebCount;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_WebCount(WebIndexType newVal)
{
   MakeDirty();

   // minimum of 2 webs required
   if ( newVal < 2 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_WebCount = newVal;

   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_LeftBlockOut(VARIANT_BOOL bLeftBlockOut)
{
   MakeDirty();
   m_bLeftBlockOut = bLeftBlockOut;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_LeftBlockOut(VARIANT_BOOL* pbLeftBlockOut)
{
   CHECK_RETVAL(pbLeftBlockOut);
   *pbLeftBlockOut = m_bLeftBlockOut;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_RightBlockOut(VARIANT_BOOL bRightBlockOut)
{
   MakeDirty();
   m_bRightBlockOut = bRightBlockOut;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_RightBlockOut(VARIANT_BOOL* pbRightBlockOut)
{
   CHECK_RETVAL(pbRightBlockOut);
   *pbRightBlockOut = m_bRightBlockOut;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_WebLocation(WebIndexType webIdx,Float64* location)
{
   CHECK_RETVAL(location);
   if ( webIdx < 0 || m_WebCount <= webIdx )
      return E_INVALIDARG;

   Float64 W;
   get_TopFlangeWidth(&W);

   WebIndexType nExteriorWebs, nInteriorWebs;
   nInteriorWebs = m_WebCount - 2;
   if ( nInteriorWebs < 0 )
      nInteriorWebs = 0;
   
   nExteriorWebs = m_WebCount - nInteriorWebs;

   if ( webIdx == 0 )
   {
      // first web
      (*location) = m_W1 + m_T1 + m_T2/2 - W/2;
   }
   else if ( webIdx == m_WebCount-1 )
   {
      // last web
      (*location) = m_W1 + m_T1+m_T2+m_T3 + nInteriorWebs*(m_T4+m_T5+m_T4) + (nInteriorWebs-1)*m_W2 + m_T3 + m_T2/2 - W/2;
   }
   else
   {
      // interior web
      (*location) = m_W1 + m_T1+m_T2+m_T3 + (webIdx-1)*(m_W2 + m_T4+m_T5+m_T4) + m_W2+m_T4+m_T5/2 - W/2;
   }

   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CMultiWeb2::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CMultiWeb2::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_H1+m_H2+m_H3;

   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   WebIndexType nExteriorWebs, nInteriorWebs;
   nInteriorWebs = m_WebCount - 2;
   if ( nInteriorWebs < 0 )
      nInteriorWebs = 0;
   
   nExteriorWebs = m_WebCount - nInteriorWebs;


   *pVal = 2*m_W1 + nExteriorWebs*(m_T1+m_T2+m_T3) + nInteriorWebs*(m_T4+m_T5+m_T4) + m_W2*(nInteriorWebs+1);

   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_AvgWebWidth(WebIndexType webIdx,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   if ( webIdx < 0 || m_WebCount <= webIdx )
      return E_INVALIDARG;

   if ( webIdx == 0 || webIdx == m_WebCount-1 )
   {
      *pVal = (m_T1+m_T2+m_T3 + m_T2)/2;
   }
   else
   {
      *pVal = (2*m_T4+m_T5 + m_T5)/2;
   }

   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CMultiWeb2::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMultiWeb2::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CMultiWeb2::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CMultiWeb2::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CMultiWeb2::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CMultiWeb2::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CMultiWeb2>* pTheClone;
   HRESULT hr = CComObject<CMultiWeb2>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IMultiWeb2> shape(pTheClone); // need at least one reference

   pTheClone->put_H1( m_H1 );
   pTheClone->put_H2( m_H2 );
   pTheClone->put_H3( m_H3 );
   pTheClone->put_W1( m_W1 );
   pTheClone->put_W2( m_W2 );
   pTheClone->put_T1( m_T1 );
   pTheClone->put_T2( m_T2 );
   pTheClone->put_T3( m_T3 );
   pTheClone->put_T4( m_T4 );
   pTheClone->put_T5( m_T5 );
   pTheClone->put_F1( m_F1 );
   pTheClone->put_F2( m_F2 );
   pTheClone->put_C1( m_C1 );
   pTheClone->put_C2( m_C2 );
   pTheClone->put_WebCount( m_WebCount );
   pTheClone->put_LeftBlockOut(m_bLeftBlockOut);
   pTheClone->put_RightBlockOut(m_bRightBlockOut);

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,NULL,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CMultiWeb2::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CMultiWeb2::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CMultiWeb2::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CMultiWeb2::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->FurthestDistance(line,pVal);
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CMultiWeb2::Offset(Float64 dx,Float64 dy)
{
   // no need to call MakeDirty since our hookpoint will call us back

   m_pHookPoint->Offset(dx,dy);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CMultiWeb2::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,NULL,point);
}

STDMETHODIMP CMultiWeb2::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   MakeDirty();

   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CMultiWeb2::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CMultiWeb2::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CMultiWeb2::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to make dirty since our hook point will call us back
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


STDMETHODIMP CMultiWeb2::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CMultiWeb2::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CMultiWeb2::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("MultiWeb2"),3.0);
   pSave->put_Property(CComBSTR("H1"),CComVariant(m_H1));
   pSave->put_Property(CComBSTR("H2"),CComVariant(m_H2));
   pSave->put_Property(CComBSTR("H3"),CComVariant(m_H3));
   pSave->put_Property(CComBSTR("W1"),CComVariant(m_W1));
   pSave->put_Property(CComBSTR("W2"),CComVariant(m_W2));
   pSave->put_Property(CComBSTR("T1"),CComVariant(m_T1));
   pSave->put_Property(CComBSTR("T2"),CComVariant(m_T2));
   pSave->put_Property(CComBSTR("T3"),CComVariant(m_T3));
   pSave->put_Property(CComBSTR("T4"),CComVariant(m_T4));
   pSave->put_Property(CComBSTR("T5"),CComVariant(m_T5));
   pSave->put_Property(CComBSTR("F1"),CComVariant(m_F1));
   pSave->put_Property(CComBSTR("F2"),CComVariant(m_F2));
   pSave->put_Property(CComBSTR("C1"),CComVariant(m_C1));
   pSave->put_Property(CComBSTR("C2"),CComVariant(m_C2));
   pSave->put_Property(CComBSTR("WebCount"),CComVariant(m_WebCount));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->put_Property(CComBSTR("LeftBlockOut"),CComVariant(m_bLeftBlockOut));
   pSave->put_Property(CComBSTR("RightBlockOut"),CComVariant(m_bRightBlockOut));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CMultiWeb2::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("MultiWeb2"));

   Float64 version;
   pLoad->get_Version(&version);

   if (2.0 < version )
      return STRLOAD_E_BADVERSION;

   pLoad->get_Property(CComBSTR("H1"),&var);
   m_H1 = var.dblVal;

   pLoad->get_Property(CComBSTR("H2"),&var);
   m_H2 = var.dblVal;

   pLoad->get_Property(CComBSTR("H3"),&var);
   m_H3 = var.dblVal;

   pLoad->get_Property(CComBSTR("W1"),&var);
   m_W1 = var.dblVal;

   pLoad->get_Property(CComBSTR("W2"),&var);
   m_W2 = var.dblVal;

   pLoad->get_Property(CComBSTR("T1"),&var);
   m_T1 = var.dblVal;

   pLoad->get_Property(CComBSTR("T2"),&var);
   m_T2 = var.dblVal;

   pLoad->get_Property(CComBSTR("T3"),&var);
   m_T3 = var.dblVal;

   pLoad->get_Property(CComBSTR("T4"),&var);
   m_T4 = var.dblVal;

   pLoad->get_Property(CComBSTR("T5"),&var);
   m_T5 = var.dblVal;

   pLoad->get_Property(CComBSTR("F1"),&var);
   m_F1 = var.dblVal;

   pLoad->get_Property(CComBSTR("F2"),&var);
   m_F2 = var.dblVal;


   if ( 2.0 <= version )
   {
      pLoad->get_Property(CComBSTR("C1"),&var);
      m_C1 = var.dblVal;

      pLoad->get_Property(CComBSTR("C2"),&var);
      m_C2 = var.dblVal;
   }
   else
   {
      m_C1 = 0.0;
      m_C2 = 0.0;
   }

   pLoad->get_Property(CComBSTR("WebCount"),&var);
   m_WebCount = var.iVal;
   
   pLoad->get_Property(CComBSTR("Rotation"),&var);
   m_Rotation = var.dblVal;

   pLoad->get_Property(CComBSTR("HookPoint"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pHookPoint,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   if ( 3.0 <= version )
   {
      pLoad->get_Property(CComBSTR("LeftBlockOut"),&var);
      m_bLeftBlockOut = var.boolVal;

      pLoad->get_Property(CComBSTR("RightBlockOut"),&var);
      m_bRightBlockOut = var.boolVal;
   }
   else
   {
      m_bLeftBlockOut = VARIANT_TRUE;
      m_bRightBlockOut = VARIANT_TRUE;
   }

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   UpdateShape();

   return S_OK;
}

STDMETHODIMP CMultiWeb2::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
