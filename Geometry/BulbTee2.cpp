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

// BulbTee2.cpp : Implementation of CBulbTee2
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "BulbTee2.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// CBulbTee2
HRESULT CBulbTee2::FinalConstruct()
{
   m_Rotation = 0.00;
   m_C1 = 0.00;
   m_C2 = 0.00;
   m_D1 = 0.00;
   m_D2 = 0.00;
   m_D3 = 0.00;
   m_D4 = 0.00;
   m_D5 = 0.00;
   m_D6 = 0.00;
   m_D7 = 0.00;
   m_T1 = 0.00;
   m_T2 = 0.00;
   m_W1 = 0.00;
   m_W2 = 0.00;
   m_W3 = 0.00;
   m_W4 = 0.00;
   m_W5 = 0.00;
   m_W6 = 0.00;
   m_n1 = 0.00;
   m_n2 = 0.00;

   CreatePoint( 0.00, 0.00, nullptr, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreatePolyShape( &m_pShape );

   m_Dirty = true;

   return S_OK;
}

void CBulbTee2::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CBulbTee2::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IBulbTee2,
      &IID_IShape,
      &IID_IXYPosition,
      &IID_IStructuredStorage2
   };
   for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

HRESULT CBulbTee2::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
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

   GetCoordinates(pPoint,px,py);

   return S_OK;
}

void CBulbTee2::GetHeight(Float64* pHl, Float64* pHc, Float64* pHr) const
{
   // Hl = height at left edge
   // Hc = height at C2
   // Hr = height at right edge

   Float64 H = m_D1 + m_D2 + m_D3 + m_D4 + m_D5 + m_D6 + m_D7; // basic height

   Float64 dL = m_n1*m_C2; // change in depth on left side of crown point
   Float64 dR = m_n2*(m_W5 + m_W6 - m_C2); // change in depth on right side of crown point

   if (dL < 0 && 0 < dR)
   {
      // the top flange is a "V" shape... low point is at C
      *pHc = H;
      *pHl = H - dL;
      *pHr = H + dR;
   }
   else if ( dL < -dR )
   {
      // low point is on the right side
      *pHr = H;
      *pHc = H - dR;
      *pHl = H - dR - dL;
   }
   else
   {
      // low point is on the left side
      *pHl = H;
      *pHc = H + dL;
      *pHr = H + dL + dR;
   }
}

HRESULT CBulbTee2::UpdateShape()
{
   if (m_Dirty)
   {
      // clear the polygon implemenation and recalculate all of the points
      m_pShape->Clear();

      Float64 Hl, Hc, Hr;
      GetHeight(&Hl, &Hc, &Hr);
                                   
      // start at bottom center (0,0)
      // and work counter-clockwise around shape
      Float64 p1_x = 0;
      Float64 p1_y = 0;

      // outside corner of bottom flange... intersection of vertical and horizontal
      // edges... no chamfer
      Float64 p2_x = p1_x + m_T2 / 2 + m_W3 + m_W4;
      Float64 p2_y = p1_y;

      Float64 p3_x = p2_x;
      Float64 p3_y = p2_y + m_D4;

      Float64 p4_x = p3_x - m_W3;
      Float64 p4_y = p3_y + m_D5;

      Float64 p5_x = p4_x - m_W4;
      Float64 p5_y = p4_y + m_D6;

      Float64 p6_x = p5_x - (m_T2 - m_T1) / 2;
      Float64 p6_y = p5_y + m_D7;

      Float64 p7_x = p6_x + m_W2;
      Float64 p7_y = p6_y + m_D3;

      Float64 p8_x = p7_x + m_W1;
      Float64 p8_y = p7_y + m_D2;

      //m_pShape->AddPoint(p1_x, p1_y); // skip 0,0... this is just an extra point we don't really need
      if (0 < m_C1)
      {
         // there is a chamfer
         m_pShape->AddPoint(p2_x - m_C1, p2_y);
         m_pShape->AddPoint(p2_x       , p2_y + m_C1);
      }
      else
      {
         m_pShape->AddPoint(p2_x, p2_y);
      }
      m_pShape->AddPoint(p3_x, p3_y);
      m_pShape->AddPoint(p4_x, p4_y);
      m_pShape->AddPoint(p5_x, p5_y);
      m_pShape->AddPoint(p6_x, p6_y);
      m_pShape->AddPoint(p7_x, p7_y);
      m_pShape->AddPoint(p8_x, p8_y);

      // Right tip of top flange... on soffit below top surface
      m_pShape->AddPoint(m_W6, p8_y);

      // Top right corner
      m_pShape->AddPoint(m_W6, Hr);

      if (!IsZero(m_C2) && !IsEqual(m_C2, m_W5 + m_W6))
      {
         // there is a peak at C2
         m_pShape->AddPoint(m_C2 - m_W5, Hc);
      }

      // Top left corner
      m_pShape->AddPoint(-m_W5, Hl);

      // left tip of top flange... on soffet below top surface
      m_pShape->AddPoint(-m_W5, p8_y);

      // work down the left side of the soffit and web
      m_pShape->AddPoint(-p8_x, p8_y);
      m_pShape->AddPoint(-p7_x, p7_y);
      m_pShape->AddPoint(-p6_x, p6_y);
      m_pShape->AddPoint(-p5_x, p5_y);
      m_pShape->AddPoint(-p4_x, p4_y);
      m_pShape->AddPoint(-p3_x, p3_y);
      if (0 < m_C1)
      {
         // there is a chamfer
         m_pShape->AddPoint(-p2_x, p2_y + m_C1);
         m_pShape->AddPoint(-p2_x + m_C1, p2_y);
      }
      else
      {
         m_pShape->AddPoint(-p2_x, p2_y);
      }

      CComQIPtr<IXYPosition> pPosition(m_pShape);

      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00, 0.00, m_Rotation);
      }

      // The hook point is at the bottom centerline of the web (which may not be at the bottom CL of the bounding box)
      // The shape was built with bottom centerline of the web at (0,0)
      // Move the shape so that point (0,0) moves to the hook point
      CComPtr<IPoint2d> origin;
      CreatePoint(0.00,0.00,nullptr,&origin);  // Hook Point at Bottom Center
      pPosition->MoveEx(origin,m_pHookPoint);

      m_Dirty = false;
   }

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W1;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_W1 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W2;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_W2 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W3;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_W3 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W4;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_W4 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W5;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_W5 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W6;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W6(Float64 newVal)
{
   MakeDirty();

   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_W6 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C1;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_C1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_C1 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_C2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C2;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_C2(Float64 newVal)
{
   MakeDirty();

   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_C2 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D1;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_D1 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D2;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_D2 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D3;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_D3 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D4;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_D4 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D5;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_D5 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D6;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D6(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_D6 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D7(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D7;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D7(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_D7 = newVal;
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_T1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T1;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_T1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_T1 = newVal;

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_T2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T2;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_T2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_T2 = newVal;

   return S_OK;
}


STDMETHODIMP CBulbTee2::get_n1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_n1;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_n1(Float64 newVal)
{
   MakeDirty();

   m_n1 = newVal;

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_n2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_n2;
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_n2(Float64 newVal)
{
   MakeDirty();

   m_n2 = newVal;

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CBulbTee2::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CBulbTee2::get_MinHeight(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 Hl, Hc, Hr;
   GetHeight(&Hl, &Hc, &Hr);

   *pVal = Min(Hl, Hr, Hc);

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_MaxHeight(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 Hl, Hc, Hr;
   GetHeight(&Hl, &Hc, &Hr);

   *pVal = Max(Hl, Hr, Hc);

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_CLHeight(Float64 *pVal)
{
   // this is actually the height at the CL Web not the CL of the bounding box
   CHECK_RETVAL(pVal);

   Float64 Hl, Hc, Hr;
   GetHeight(&Hl, &Hc, &Hr);
   if (m_W5 < m_C2)
   {
      *pVal = Hl + m_n1*m_W5;
   }
   else
   {
      *pVal = Hl + m_n1*m_C2 + m_n2*(m_W5 - m_C2);
   }
   
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_Height(Float64 *pVal)
{
   return get_MaxHeight(pVal);
}

STDMETHODIMP CBulbTee2::get_AvgWebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = (m_T1+m_T2)/2.;

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_BottomFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T2 + 2.*(m_W3+m_W4);

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W5 + m_W6;

   return S_OK;
}

STDMETHODIMP CBulbTee2::GetTopFlangeThickness(Float64* pHl, Float64* pHc, Float64* pHr)
{
   CHECK_RETVAL(pHl);
   CHECK_RETVAL(pHc);
   CHECK_RETVAL(pHr);

   Float64 Hl, Hc, Hr;
   GetHeight(&Hl, &Hc, &Hr);

   Float64 baseHeight = /*m_D1 +*/ m_D2 + m_D3 + m_D4 + m_D5 + m_D6 + m_D7; // basic height

   *pHl = Hl - baseHeight;
   *pHc = Hc - baseHeight;
   *pHr = Hr - baseHeight;

   return S_OK;
}

STDMETHODIMP CBulbTee2::GetTopFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppTopCentral, IPoint2d** ppRightTop, IPoint2d** ppRightBottom)
{
   CHECK_RETOBJ(ppLeftTop);
   CHECK_RETOBJ(ppLeftBottom);
   CHECK_RETOBJ(ppTopCentral);
   CHECK_RETOBJ(ppRightTop);
   CHECK_RETOBJ(ppRightBottom);

   IndexType leftTopIdx(11), leftBottomIdx(12), topCentralIdx(10), rightTopIdx(9), rightBottomIdx(8); // index into the polygon points
   if (IsZero(m_C1))
   {
      // we don't have a chamfer in the bottom flange... reduce indicies by one
      leftTopIdx--;
      leftBottomIdx--;
      topCentralIdx--;
      rightTopIdx--;
      rightBottomIdx--;
   }

   if (IsZero(m_C2) || IsEqual(m_C2, m_W5 + m_W6))
   {
      // there isn't a crown point between flange tips
      // high point is at left or right flange tip... reduce one from left flange indicies
      leftTopIdx--;
      leftBottomIdx--;

      if (IsZero(m_C2))
      {
         // top flange is thicker on the right side
         topCentralIdx = rightTopIdx;
      }
      else
      {
         // top flange is thicker on the left side
         topCentralIdx = leftTopIdx;
      }
   }

   UpdateShape();

   // get the points from our polygon implementation
   CComPtr<IPoint2d> leftTop, leftBottom, topCentral, rightTop, rightBottom;
   m_pShape->get_Point(leftTopIdx, &leftTop);
   m_pShape->get_Point(leftBottomIdx, &leftBottom);
   m_pShape->get_Point(topCentralIdx, &topCentral);
   m_pShape->get_Point(rightTopIdx, &rightTop);
   m_pShape->get_Point(rightBottomIdx, &rightBottom);

   // these are the actual points... we don't want external users to change
   // them and mess up our shape so we must create clones
   leftTop->Clone(ppLeftTop);
   leftBottom->Clone(ppLeftBottom);
   topCentral->Clone(ppTopCentral);
   rightTop->Clone(ppRightTop);
   rightBottom->Clone(ppRightBottom);

#if defined _DEBUG
   Float64 Hl, Hc, Hr;
   GetTopFlangeThickness(&Hl, &Hc, &Hr);
   Float64 hl, hr;
   leftTop->DistanceEx(leftBottom, &hl);
   rightTop->DistanceEx(rightBottom, &hr);
   ATLASSERT(IsEqual(hl, Hl));
   ATLASSERT(IsEqual(hr, Hr));
#endif

   return S_OK;
}

STDMETHODIMP CBulbTee2::GetBottomFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppRightTop, IPoint2d** ppRightBottom)
{
   CHECK_RETOBJ(ppLeftTop);
   CHECK_RETOBJ(ppLeftBottom);
   CHECK_RETOBJ(ppRightTop);
   CHECK_RETOBJ(ppRightBottom);

   UpdateShape();
   IndexType nPoints;
   m_pShape->get_Count(&nPoints);

   // get the points from our polygon implementation
   CComPtr<IPoint2d> leftTop, leftBottom,  rightTop, rightBottom;
   if (IsZero(m_C1))
   {
      // no chamfer
      m_pShape->get_Point(0, &rightBottom);
      m_pShape->get_Point(0, &rightTop);

      m_pShape->get_Point(nPoints - 1, &leftTop);
      m_pShape->get_Point(nPoints - 1, &leftBottom);
   }
   else
   {
      m_pShape->get_Point(0, &rightBottom);
      m_pShape->get_Point(1, &rightTop);

      m_pShape->get_Point(nPoints - 2, &leftTop);
      m_pShape->get_Point(nPoints - 1, &leftBottom);
   }

   // these are the actual points... we don't want external users to change
   // them and mess up our shape so we must create clones
   leftTop->Clone(ppLeftTop);
   leftBottom->Clone(ppLeftBottom);
   rightTop->Clone(ppRightTop);
   rightBottom->Clone(ppRightBottom);

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CBulbTee2::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CBulbTee2::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CBulbTee2::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CBulbTee2::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CBulbTee2::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CBulbTee2::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CBulbTee2>* pTheClone;
   HRESULT hr = CComObject<CBulbTee2>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IBulbTee2> shape(pTheClone); // need at least one reference

   pTheClone->put_C1(m_C1);
   pTheClone->put_C2(m_C2);
   pTheClone->put_D1( m_D1 );
   pTheClone->put_D2( m_D2 );
   pTheClone->put_D3( m_D3 );
   pTheClone->put_D4( m_D4 );
   pTheClone->put_D5( m_D5 );
   pTheClone->put_D6( m_D6 );
   pTheClone->put_D7( m_D7 );
   pTheClone->put_T1( m_T1 );
   pTheClone->put_T2( m_T2 );
   pTheClone->put_W1( m_W1 );
   pTheClone->put_W2( m_W2 );
   pTheClone->put_W3( m_W3 );
   pTheClone->put_W4( m_W4 );
   pTheClone->put_W5(m_W5);
   pTheClone->put_W6(m_W6);
   pTheClone->put_n1(m_n1);
   pTheClone->put_n2(m_n2);

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,nullptr,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CBulbTee2::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CBulbTee2::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CBulbTee2::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CBulbTee2::FurthestDistance(ILine2d* line,Float64 *pVal)
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

STDMETHODIMP CBulbTee2::Offset(Float64 dx,Float64 dy)
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

STDMETHODIMP CBulbTee2::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->Dimensions(&dx, &dy);

   return Offset(dx,dy);
}

STDMETHODIMP CBulbTee2::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,nullptr,point);
}

STDMETHODIMP CBulbTee2::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   MakeDirty();

   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CBulbTee2::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CBulbTee2::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CBulbTee2::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to make dirty since our hook point will call us back
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


STDMETHODIMP CBulbTee2::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CBulbTee2::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CBulbTee2::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("BulbTee2"),1.0);
   pSave->put_Property(CComBSTR("C1"), CComVariant(m_C1));
   pSave->put_Property(CComBSTR("C2"), CComVariant(m_C2));
   pSave->put_Property(CComBSTR("D1"),CComVariant(m_D1));
   pSave->put_Property(CComBSTR("D2"),CComVariant(m_D2));
   pSave->put_Property(CComBSTR("D3"),CComVariant(m_D3));
   pSave->put_Property(CComBSTR("D4"),CComVariant(m_D4));
   pSave->put_Property(CComBSTR("D5"),CComVariant(m_D5));
   pSave->put_Property(CComBSTR("D6"),CComVariant(m_D6));
   pSave->put_Property(CComBSTR("D7"),CComVariant(m_D7));
   pSave->put_Property(CComBSTR("T1"),CComVariant(m_T1));
   pSave->put_Property(CComBSTR("T2"),CComVariant(m_T2));
   pSave->put_Property(CComBSTR("W1"),CComVariant(m_W1));
   pSave->put_Property(CComBSTR("W2"),CComVariant(m_W2));
   pSave->put_Property(CComBSTR("W3"),CComVariant(m_W3));
   pSave->put_Property(CComBSTR("W4"),CComVariant(m_W4));
   pSave->put_Property(CComBSTR("W5"), CComVariant(m_W5));
   pSave->put_Property(CComBSTR("W6"), CComVariant(m_W6));
   pSave->put_Property(CComBSTR("n1"), CComVariant(m_n1));
   pSave->put_Property(CComBSTR("n2"), CComVariant(m_n2));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CBulbTee2::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("BulbTee2"));

   Float64 vers;
   pLoad->get_Version(&vers);

   pLoad->get_Property(CComBSTR("C1"), &var);
   m_C1 = var.dblVal;

   pLoad->get_Property(CComBSTR("C2"), &var);
   m_C2 = var.dblVal;

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
   
   pLoad->get_Property(CComBSTR("D7"),&var);
   m_D7 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("T1"),&var);
   m_T1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("T2"),&var);
   m_T2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W1"),&var);
   m_W1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W2"),&var);
   m_W2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W3"),&var);
   m_W3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W4"),&var);
   m_W4 = var.dblVal;

   pLoad->get_Property(CComBSTR("W5"), &var);
   m_W5 = var.dblVal;

   pLoad->get_Property(CComBSTR("W6"), &var);
   m_W6 = var.dblVal;

   pLoad->get_Property(CComBSTR("n1"), &var);
   m_n1 = var.dblVal;

   pLoad->get_Property(CComBSTR("n2"), &var);
   m_n2 = var.dblVal;

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

STDMETHODIMP CBulbTee2::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
