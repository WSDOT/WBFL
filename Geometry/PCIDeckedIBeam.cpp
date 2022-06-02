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

// PCIDeckedIBeam.cpp : Implementation of CPCIDeckedIBeam
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "PCIDeckedIBeam.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCIDeckedIBeam
HRESULT CPCIDeckedIBeam::FinalConstruct()
{
   m_Rotation = 0.00;
   m_D1 = 0.00;
   m_D2 = 0.00;
   m_D3 = 0.00;
   m_D4 = 0.00;
   m_D5 = 0.00;
   m_D6 = 0.00;
   m_D7 = 0.00;
   m_D8 = 0.00;
   m_D9 = 0.00;
   m_H = 0.00;
   m_T = 0.00;
   m_W1 = 0.00;
   m_W2 = 0.00;
   m_W3 = 0.00;
   m_W4 = 0.00;
   m_W5 = 0.00;
   m_W6 = 0.00;
   m_R1 = 0.00;
   m_R2 = 0.00;
   m_R3 = 0.00;
   m_C1 = 0.00;

   m_pHookPoint.CoCreateInstance(CLSID_Point2d);
   m_pHookPoint->Move(0, 0);
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   m_pShape.CoCreateInstance(CLSID_PolyShape);

   m_Dirty = true;

   return S_OK;
}

void CPCIDeckedIBeam::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CPCIDeckedIBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IPCIDeckedIBeam,
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

HRESULT CPCIDeckedIBeam::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
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

   pPoint->Location(px, py);

   return S_OK;

}

HRESULT CPCIDeckedIBeam::UpdateShape()
{
   if (m_Dirty)
   {
      // clear the polygon implemenation and recalculate all of the points
      m_pShape->Clear();

      m_pntLeftBottom.Release();
      m_pntLeftTop.Release();
      m_pntRightBottom.Release();
      m_pntRightTop.Release();

      // Generate points along the left-hand side of the shape... 
      // then we will copy and mirror them about the Y axis
      CComPtr<IPoint2dCollection> points;
      points.CoCreateInstance(CLSID_Point2dCollection);

      const long nSpaces = 20; // number of spaces used to approximate the curved fillets
      Float64 cx, cy;           // center of arc
      Float64 delta;            // sweep angle of arc
      Float64 startAngle;       // start angle for generating points along arc

      // Start at the lower left corner of the shape
      if  ( IsZero(m_C1) )
      {
         AddPoint(points,-m_W6/2,0.0);
      }
      else
      {
         AddPoint(points,-m_W6/2+m_C1,0.0);
         AddPoint(points,-m_W6/2,m_C1);
      }

      // compute angle of bottom flange (measured from vertical)
      delta = atan2((m_W6 - m_T) / 2, m_D8 - m_D9);

      // top of bottom flange
      cx = -m_W6 / 2 + m_R3;
      cy = m_D9 - m_R3*tan(delta/2);
      startAngle = M_PI;
      GenerateFillet(points, cx, cy, m_R3, startAngle, -delta, nSpaces);

      // generate bottom left flange-web fillet
      cx = -m_T/2 - m_R2;
      cy = m_D8 + m_R2*tan(delta/2);
      startAngle = TWO_PI - delta;

      GenerateFillet(points,cx,cy,m_R2,startAngle, delta,nSpaces);

      // compute angle of top flange (measured from vertical)
      delta = atan2( m_W1/2 + m_W2, m_D6 - m_D1 );

      // generate top left flange-web fillet
      cx = -m_T/2 - m_R1;
      cy = m_H - m_D6 - m_R1*tan(delta/2);
      startAngle = 0.0;

      GenerateFillet(points,cx,cy,m_R1,startAngle, delta,nSpaces);

      // bottom of top flange
      AddPoint(points, -m_W1 / 2, m_H - m_D7);

      AddPoint(points, -m_W1 / 2 - m_W2 + m_W3 + (m_W1/2 - (m_R1 + m_T/2)), m_H - m_D1 + (m_D6 - m_D7));

      AddPoint(points, -m_W1 / 2 - m_W2 + m_W3, m_H - m_D1);
      AddPoint(points, -m_W1 / 2 - m_W2, m_H - m_D1);
      AddPoint(points, -m_W1 / 2 - m_W2, m_H - m_D1 + m_D5);
      AddPoint(points, -m_W1 / 2 - m_W2 + m_W5, m_H - m_D1 + m_D4 + m_D5);
      AddPoint(points, -m_W1 / 2 - m_W2 + m_W5, m_H - m_D2 - m_D3);
      AddPoint(points, -m_W1 / 2 - m_W2 + m_W5 - m_W4, m_H - m_D2);
      AddPoint(points, -m_W1 / 2 - m_W2 + m_W5 - m_W4, m_H);


      IndexType nPoints;
      points->get_Count(&nPoints);
      IndexType idxLeftBottom = nPoints - 3;
      IndexType idxLeftTop = nPoints - 1;
      IndexType idxRightTop = nPoints;
      IndexType idxRightBottom = nPoints + 2;

      // copy the left hand side points
      CComPtr<IPoint2dCollection> rightPoints;
      points->Clone(&rightPoints);

      // reverse the order of the points
      rightPoints->Reverse();

      // mirror about Y = 0
      CComPtr<IEnumPoint2d> enumPoints;
      rightPoints->get__Enum(&enumPoints);
      CComPtr<IPoint2d> pnt;
      while ( enumPoints->Next(1,&pnt,nullptr) != S_FALSE )
      {
         Float64 x;
         pnt->get_X(&x);
         x *= -1;
         pnt->put_X(x);
         pnt.Release();
      }

      m_pShape->AddPoints(points);
      m_pShape->AddPoints(rightPoints);

      // rotate if necessary
      CComQIPtr<IXYPosition> pPosition(m_pShape);
      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00,0.00,m_Rotation);
      }

      CComPtr<IPoint2d> origin;
      origin.CoCreateInstance(CLSID_Point2d);
      origin->Move(0, 0);
      pPosition->MoveEx(origin,m_pHookPoint);

#if defined _DEBUG
      {
          IndexType nPoints;
          m_pShape->get_Count(&nPoints);
          if (IsZero(m_C1)) ATLASSERT(nPoints == 146); else ATLASSERT(nPoints == 148);
      }
#endif
      m_pShape->get_Point(idxLeftBottom, &m_pntLeftBottom);
      m_pShape->get_Point(idxLeftTop, &m_pntLeftTop);
      m_pShape->get_Point(idxRightTop, &m_pntRightTop);
      m_pShape->get_Point(idxRightBottom, &m_pntRightBottom);
      m_Dirty = false;
   }

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W1;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_W1 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W2;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_W2 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_W3(Float64* pVal)
{
    CHECK_RETVAL(pVal);

    *pVal = m_W3;
    return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W3(Float64 newVal)
{
    MakeDirty();

    if (newVal < 0.0)
        return Error(IDS_E_DIMENSION, IID_IPCIDeckedIBeam, GEOMETRY_E_DIMENSION);

    m_W3 = newVal;
    return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_W4(Float64* pVal)
{
    CHECK_RETVAL(pVal);

    *pVal = m_W4;
    return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W4(Float64 newVal)
{
    MakeDirty();

    if (newVal < 0.0)
        return Error(IDS_E_DIMENSION, IID_IPCIDeckedIBeam, GEOMETRY_E_DIMENSION);

    m_W4 = newVal;
    return S_OK;
}


STDMETHODIMP CPCIDeckedIBeam::get_W5(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W5;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W5(Float64 newVal)
{
   MakeDirty();

   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IPCIDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_W5 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_W6(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W6;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W6(Float64 newVal)
{
   MakeDirty();

   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IPCIDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_W6 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D1;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_D1 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D2;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_D2 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D3;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_D3 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D4;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_D4 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D5;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_D5 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D6(Float64* pVal)
{
    CHECK_RETVAL(pVal);

    *pVal = m_D6;
    return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D6(Float64 newVal)
{
    MakeDirty();

    if (newVal < 0.0)
        return Error(IDS_E_DIMENSION, IID_IPCIDeckedIBeam, GEOMETRY_E_DIMENSION);

    m_D6 = newVal;
    return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D7(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D7;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D7(Float64 newVal)
{
   MakeDirty();

   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IPCIDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_D7 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D8(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D8;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D8(Float64 newVal)
{
   MakeDirty();

   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IPCIDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_D8 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D9(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D9;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D9(Float64 newVal)
{
   MakeDirty();

   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IPCIDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_D9 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_H(Float64* pVal)
{
    CHECK_RETVAL(pVal);

    *pVal = m_H;
    return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_H(Float64 newVal)
{
    MakeDirty();

    if (newVal < 0.0)
        return Error(IDS_E_DIMENSION, IID_IPCIDeckedIBeam, GEOMETRY_E_DIMENSION);

    m_H = newVal;

    return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_T(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_T(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_T = newVal;

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_R1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_R1;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_R1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_R1 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_R2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_R2;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_R2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_R2 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_R3(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_R3;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_R3(Float64 newVal)
{
   MakeDirty();

   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IPCIDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_R3 = newVal;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C1;
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_C1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPCIDeckedIBeam,GEOMETRY_E_DIMENSION);

   m_C1 = newVal;

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CPCIDeckedIBeam::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_H;

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_AvgWebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T;

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_BottomFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W6;

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W1 + 2*(m_W2 - m_W5);

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::GetTopFlangeThickness(Float64* pHl, Float64* pHc, Float64* pHr)
{
    CHECK_RETVAL(pHl);
    CHECK_RETVAL(pHc);
    CHECK_RETVAL(pHr);

    *pHl = m_D7;
    *pHc = m_D7;
    *pHr = m_D7;

    return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::GetTopFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppTopCentral, IPoint2d** ppRightTop, IPoint2d** ppRightBottom)
{
    CHECK_RETOBJ(ppLeftTop);
    CHECK_RETOBJ(ppLeftBottom);
    CHECK_RETOBJ(ppTopCentral);
    CHECK_RETOBJ(ppRightTop);
    CHECK_RETOBJ(ppRightBottom);

    UpdateShape();

    m_pntLeftTop.CopyTo(ppLeftTop);
    m_pntLeftBottom.CopyTo(ppLeftBottom);

    m_pntRightBottom.CopyTo(ppRightBottom);
    m_pntRightTop.CopyTo(ppRightTop);

    CComPtr<IPoint2d> pntTopCentral;
    pntTopCentral.CoCreateInstance(CLSID_Point2d);

    Float64 xl, yl, xr, yr;
    m_pntLeftTop->Location(&xl, &yl);
    m_pntRightTop->Location(&xr, &yr);

    pntTopCentral->Move((xl + xr) / 2, (yl + yr) / 2);
    pntTopCentral.CopyTo(ppTopCentral);

    return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::GetBottomFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppRightTop, IPoint2d** ppRightBottom)
{
    CHECK_RETOBJ(ppLeftTop);
    CHECK_RETOBJ(ppLeftBottom);
    CHECK_RETOBJ(ppRightTop);
    CHECK_RETOBJ(ppRightBottom);

    UpdateShape();
    IndexType nPoints;
    m_pShape->get_Count(&nPoints);

    // get the points from our polygon implementation
    CComPtr<IPoint2d> leftTop, leftBottom, rightTop, rightBottom;
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

STDMETHODIMP CPCIDeckedIBeam::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CPCIDeckedIBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CPCIDeckedIBeam::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CPCIDeckedIBeam::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CPCIDeckedIBeam::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CPCIDeckedIBeam::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CPCIDeckedIBeam::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CPCIDeckedIBeam>* pTheClone;
   HRESULT hr = CComObject<CPCIDeckedIBeam>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPCIDeckedIBeam> shape(pTheClone); // need at least one reference

   pTheClone->put_D1( m_D1 );
   pTheClone->put_D2( m_D2 );
   pTheClone->put_D3( m_D3 );
   pTheClone->put_D4( m_D4 );
   pTheClone->put_D5(m_D5);
   pTheClone->put_D6(m_D6);
   pTheClone->put_D7(m_D7);
   pTheClone->put_D8(m_D8);
   pTheClone->put_D9(m_D9);
   pTheClone->put_H(m_H);
   pTheClone->put_T(m_T);
   pTheClone->put_W1( m_W1 );
   pTheClone->put_W2(m_W2);
   pTheClone->put_W3(m_W3);
   pTheClone->put_W4(m_W4);
   pTheClone->put_W5(m_W5);
   pTheClone->put_W6(m_W6);
   pTheClone->put_R1( m_R1 );
   pTheClone->put_R2(m_R2);
   pTheClone->put_R3(m_R3);
   pTheClone->put_C1( m_C1 );

   CComPtr<IPoint2d> hookPnt;
   m_pHookPoint->Clone(&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CPCIDeckedIBeam::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CPCIDeckedIBeam::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CPCIDeckedIBeam::FurthestDistance(ILine2d* line,Float64 *pVal)
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

STDMETHODIMP CPCIDeckedIBeam::Offset(Float64 dx,Float64 dy)
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

STDMETHODIMP CPCIDeckedIBeam::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->Dimensions(&dx, &dy);
   return Offset(dx,dy);
}

STDMETHODIMP CPCIDeckedIBeam::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance(CLSID_Point2d);
   pnt->Move(lx, ly);
   pnt.CopyTo(point);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   point->Location(&cx, &cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CPCIDeckedIBeam::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   Float64 x1,y1;
   Float64 x2,y2;
   pFrom->Location(&x1, &y1);
   pTo->Location(&x2, &y2);

   Float64 dx = x2 - x1;
   Float64 dy = y2 - y1;

   return Offset(dx,dy);
}

STDMETHODIMP CPCIDeckedIBeam::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   pPoint->Location(&x, &y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CPCIDeckedIBeam::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to call MakeDirty since our hookpoint will call us back
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


STDMETHODIMP CPCIDeckedIBeam::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CPCIDeckedIBeam::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CPCIDeckedIBeam::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("PCIDeckedIBeam"),1.0);
   pSave->put_Property(CComBSTR("D1"),CComVariant(m_D1));
   pSave->put_Property(CComBSTR("D2"),CComVariant(m_D2));
   pSave->put_Property(CComBSTR("D3"),CComVariant(m_D3));
   pSave->put_Property(CComBSTR("D4"),CComVariant(m_D4));
   pSave->put_Property(CComBSTR("D5"), CComVariant(m_D5));
   pSave->put_Property(CComBSTR("D6"), CComVariant(m_D6));
   pSave->put_Property(CComBSTR("D7"), CComVariant(m_D7));
   pSave->put_Property(CComBSTR("D8"), CComVariant(m_D8));
   pSave->put_Property(CComBSTR("D9"), CComVariant(m_D9));
   pSave->put_Property(CComBSTR("H"), CComVariant(m_H));
   pSave->put_Property(CComBSTR("T"), CComVariant(m_T));
   pSave->put_Property(CComBSTR("W1"),CComVariant(m_W1));
   pSave->put_Property(CComBSTR("W2"),CComVariant(m_W2));
   pSave->put_Property(CComBSTR("W3"), CComVariant(m_W3));
   pSave->put_Property(CComBSTR("W4"), CComVariant(m_W4));
   pSave->put_Property(CComBSTR("W5"), CComVariant(m_W5));
   pSave->put_Property(CComBSTR("W6"), CComVariant(m_W6));
   pSave->put_Property(CComBSTR("R1"),CComVariant(m_R1));
   pSave->put_Property(CComBSTR("R2"), CComVariant(m_R2));
   pSave->put_Property(CComBSTR("R3"), CComVariant(m_R3));
   pSave->put_Property(CComBSTR("C1"),CComVariant(m_C1));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("PCIDeckedIBeam"));

   pLoad->get_Property(CComBSTR("D1"),&var);
   m_D1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D2"),&var);
   m_D2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D3"),&var);
   m_D3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D4"),&var);
   m_D4 = var.dblVal;

   pLoad->get_Property(CComBSTR("D5"), &var);
   m_D5 = var.dblVal;

   pLoad->get_Property(CComBSTR("D6"), &var);
   m_D6 = var.dblVal;

   pLoad->get_Property(CComBSTR("D7"), &var);
   m_D7 = var.dblVal;

   pLoad->get_Property(CComBSTR("D8"), &var);
   m_D8 = var.dblVal;

   pLoad->get_Property(CComBSTR("D9"), &var);
   m_D9 = var.dblVal;

   pLoad->get_Property(CComBSTR("H"), &var);
   m_H = var.dblVal;

   pLoad->get_Property(CComBSTR("T"), &var);
   m_T = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W1"),&var);
   m_W1 = var.dblVal;

   pLoad->get_Property(CComBSTR("W2"), &var);
   m_W2 = var.dblVal;

   pLoad->get_Property(CComBSTR("W3"), &var);
   m_W3 = var.dblVal;

   pLoad->get_Property(CComBSTR("W4"), &var);
   m_W4 = var.dblVal;

   pLoad->get_Property(CComBSTR("W5"), &var);
   m_W5 = var.dblVal;

   pLoad->get_Property(CComBSTR("W6"), &var);
   m_W6 = var.dblVal;

   pLoad->get_Property(CComBSTR("R1"),&var);
   m_R1 = var.dblVal;

   pLoad->get_Property(CComBSTR("R2"), &var);
   m_R2 = var.dblVal;

   pLoad->get_Property(CComBSTR("R3"), &var);
   m_R3 = var.dblVal;

   pLoad->get_Property(CComBSTR("C1"),&var);
   m_C1 = var.dblVal;
   
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

void CPCIDeckedIBeam::AddPoint(IPoint2dCollection* pPoints,Float64 x,Float64 y)
{
   CComPtr<IPoint2d> point;
   point.CoCreateInstance(CLSID_Point2d);
   point->Move(x,y);
   pPoints->Add(point);
}

void CPCIDeckedIBeam::GenerateFillet(IPoint2dCollection* pPoints,Float64 cx,Float64 cy,Float64 r,Float64 startAngle,Float64 delta,long nSpaces)
{
   Float64 dAngle = delta/nSpaces;
   for ( long i = 0; i <= nSpaces; i++ )
   {
      Float64 x = cx + r*cos(startAngle + i*dAngle);
      Float64 y = cy + r*sin(startAngle + i*dAngle);
      AddPoint(pPoints,x,y);
   }
}

STDMETHODIMP CPCIDeckedIBeam::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
