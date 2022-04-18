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

// BoxBeam.cpp : Implementation of CBoxBeam
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "BoxBeam.h"
#include "Helper.h"
#include <MathEx.h>
#include <array>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// CBoxBeam
HRESULT CBoxBeam::FinalConstruct()
{
   m_Rotation = 0;
   m_W1 = 0;
   m_W2 = 0;
   m_W3 = 0;
   m_W4 = 0;
   m_H1 = 0;
   m_H2 = 0;
   m_H3 = 0;
   m_H4 = 0;
   m_H5 = 0;
   m_H6 = 0;
   m_H7 = 0;
   m_F1 = 0;
   m_F2 = 0;
   m_C1 = 0;
   m_VoidCount = 1;

   CreatePoint( 0.00, 0.00, nullptr, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreateCompositeShape( &m_pShape );

   m_bLeftBlockOut = VARIANT_TRUE;
   m_bRightBlockOut = VARIANT_TRUE;

   // Shape point indexs for top and bottom stress points
   m_LeftTopPointIdx = INVALID_INDEX;
   m_LeftBottomPointIdx = INVALID_INDEX;
   m_RightTopPointIdx = INVALID_INDEX;
   m_RightBottomPointIdx = INVALID_INDEX;

   m_Dirty = true;

   return S_OK;
}

void CBoxBeam::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CBoxBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IBoxBeam,
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

HRESULT CBoxBeam::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
{
   ATLASSERT(px != nullptr && py != nullptr);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
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

HRESULT CBoxBeam::UpdateShape()
{
   if (m_Dirty)
   {
      // create a new shape
      m_pShape.Release();
      CreateCompositeShape(&m_pShape);

      // Create the outer shape
      CComPtr<IPolyShape> outer;
      outer.CoCreateInstance(CLSID_PolyShape);

      // Start at bottom center and work CCW around the perimeter. 
      // Number of points varies depending on chamfer

      // outside dimensions
      Float64 wtop = 2.0*(m_W1 + m_W2) + m_W3;
      Float64 wbot = 2.0*(m_W4 + m_W2) + m_W3;
      Float64 hgt = m_H1 + m_H2 + m_H3;

      std::array<Float64,17> x, y; 
      int np = 0;

      // bottom center
      x[np]   = 0; 
      y[np++] = 0;

      if (m_C1 <= 0.0)
      {
         // bottom right
         x[np]   = wbot/2;
         y[np] = 0;
      }
      else
      {
         // deal with chamfer
         x[np]   = wbot/2 - m_C1;
         y[np++] = 0;

         x[np]   = wbot/2;
         y[np] = m_C1;
      }

      m_RightBottomPointIdx = np++;

      if ( m_bRightBlockOut == VARIANT_TRUE )
      {
         // up the right edge, H7
         x[np]   = x[np-1];
         y[np++] = m_H7;

         // bottom of the right key way, H6
         x[np]   = x[np-1] - m_W4;
         y[np++] = m_H7 + m_H6;

         // top of the right key way
         if(m_H5>0.0 || m_H4>0.0)
         {
            x[np]   = x[np-1];
            y[np++] = hgt - m_H4 - m_H5;
         }

         // right edge near top, H4
         if(m_H4>0.0)
         {
            x[np]   = wtop/2;
            y[np++] = hgt - m_H4; 
         }

         // top right corner
         x[np]   = wtop/2;
         y[np] = hgt;
      }
      else
      {
         // top right corner
         x[np]   = wbot/2;
         y[np] = hgt;
      }

      m_RightTopPointIdx = np++;

      if ( m_bLeftBlockOut == VARIANT_TRUE )
      {
         // top left corner
         x[np] = -wtop/2;
         y[np] = hgt;

         m_LeftTopPointIdx = np++;

         // left edge near top, H4
         if(m_H4>0.0)
         {
            x[np]   = -wtop/2;
            y[np++] = hgt - m_H4; 
         }

         // top of the left key way
         if(m_H5>0.0 || m_H4>0.0)
         {
            x[np]   = x[np-1] + m_W1;
            y[np++] = hgt - m_H4 - m_H5;
         }

         // bottom of the left key way, H6
         x[np]   = x[np-1];
         y[np++] = m_H7 + m_H6;

         // left edge, H7
         x[np]   = x[np-1] - m_W4;
         y[np++] = m_H7;
      }
      else
      {
         // top left corner
         x[np] = -wbot/2;
         y[np] = hgt;

         m_LeftTopPointIdx = np++;
      }

      if (m_C1 <= 0.0)
      {
         // bottom left
         x[np]   = -wbot/2;
         y[np] = 0;
      }
      else
      {
         // deal with chamfer
         x[np]   = -wbot/2;
         y[np++] = m_C1;

         x[np]   = -wbot/2 + m_C1;
         y[np] = 0;
      }

      m_LeftBottomPointIdx = np++;

      // bottom center
      x[np]   = 0; 
      y[np++] = 0;

      for (int ip = 0; ip < np; ip++)
      {
         outer->AddPoint(x[ip], y[ip]);
      }

      CComQIPtr<IShape> outer_shape(outer);
      m_pShape->AddShape(outer_shape,VARIANT_FALSE);

      // inner shape
      if (m_VoidCount>0)
      {
         CComPtr<IPolyShape> inner;
         inner.CoCreateInstance(CLSID_PolyShape);

         Float64 x1,y1;
         Float64 x2,y2;
         Float64 x3,y3;
         Float64 x4,y4;
         Float64 x5,y5;

         x1 = 0;
         y1 = m_H3;

         x2 = m_W3/2 - m_F2;
         y2 = y1;

         x3 = x2 + m_F2;
         y3 = y2 + m_F2;

         x4 = x3;
         y4 = m_H3 + m_H2 - m_F1;

         x5 = x4 - m_F1;
         y5 = y4 + m_F1;

         inner->AddPoint(x1,y1);
         inner->AddPoint(x2,y2);
         inner->AddPoint(x3,y3);
         inner->AddPoint(x4,y4);
         inner->AddPoint(x5,y5);
         inner->AddPoint(-x5,y5);
         inner->AddPoint(-x4,y4);
         inner->AddPoint(-x3,y3);
         inner->AddPoint(-x2,y2);
         inner->AddPoint(-x1,y1);

         CComQIPtr<IShape> inner_shape(inner);
         m_pShape->AddShape(inner_shape,VARIANT_TRUE);
      }

      CComQIPtr<IXYPosition> pPosition(m_pShape);

      // Rotate the shape
      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00,0.00,m_Rotation);
      }

      // move the shape to the real hook point
      CComPtr<IPoint2d> origin;
      CreatePoint(0.00,0.00,nullptr,&origin);  // Hook Point at Bottom Center
      pPosition->MoveEx(origin,m_pHookPoint);

      m_Dirty = false;
   }

   return S_OK;
}

STDMETHODIMP CBoxBeam::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_W1;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_W1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_W1 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_W2;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_W2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_W2 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_W3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_W3;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_W3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_W3 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_W4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_W4;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_W4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_W4 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_H1;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_H1 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_H2;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_H2 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_H3;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_H3 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_H4;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_H4 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_H5;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_H5 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_H6;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H6(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_H6 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H7(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_H7;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H7(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_H7 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_F1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_F1;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_F1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_F1 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_F2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_F2;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_F2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_F2 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_C1;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_C1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_C1 = newVal;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_VoidCount(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_VoidCount;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_VoidCount(CollectionIndexType newVal)
{
   MakeDirty();

   // can only have 0 or 1 void
   if ( newVal < 0 || newVal>1)
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_VoidCount = newVal;

   return S_OK;
}

STDMETHODIMP CBoxBeam::put_LeftBlockOut(VARIANT_BOOL bLeftBlockOut)
{
   MakeDirty();
   m_bLeftBlockOut = bLeftBlockOut;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_LeftBlockOut(VARIANT_BOOL* pbLeftBlockOut)
{
   CHECK_RETVAL(pbLeftBlockOut);
   *pbLeftBlockOut = m_bLeftBlockOut;
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_RightBlockOut(VARIANT_BOOL bRightBlockOut)
{
   MakeDirty();
   m_bRightBlockOut = bRightBlockOut;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_RightBlockOut(VARIANT_BOOL* pbRightBlockOut)
{
   CHECK_RETVAL(pbRightBlockOut);
   *pbRightBlockOut = m_bRightBlockOut;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_WebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   bool bSmallShearKey    = (m_W1 < m_W2/2 || m_W4 < m_W2/2)       ? true : false;
   bool bShearKeyAtTop    = (m_H4 < m_H1 && m_H2+m_H3-m_F1 < m_H7) ? true : false;
   bool bShearKeyAtBottom = (m_H7 < m_H3 && m_H1+m_H2-m_F2 < m_H4) ? true : false;

   if ( bSmallShearKey && bShearKeyAtTop )
      *pVal = 2.0*(m_W2 + m_W4);
   else if ( bSmallShearKey && bShearKeyAtBottom )
      *pVal = 2.0*(m_W1 + m_W2);
   else
      *pVal = 2.0*m_W2;

   return S_OK;
}

STDMETHODIMP CBoxBeam::get_BottomFlangeWidth(Float64* pLeft, Float64* pRight)
{
   CHECK_RETVAL(pLeft);
   CHECK_RETVAL(pRight);

   Float64 val = m_W4 + m_W2 + m_W3/2.0;
   *pLeft = val;
   *pRight = val;
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_TopFlangeWidth(Float64* pLeft, Float64* pRight)
{
   CHECK_RETVAL(pLeft);
   CHECK_RETVAL(pRight);

   Float64 Bot2 = m_W4 + m_W2 + m_W3/2.0;
   Float64 Top2 = m_W1 + m_W2 + m_W3/2.0;

   // if blockout, use top dimension
   *pLeft  = (m_bLeftBlockOut  != VARIANT_FALSE) ? Top2 : Bot2;
   *pRight = (m_bRightBlockOut != VARIANT_FALSE) ? Top2 : Bot2;

   return S_OK;
}

STDMETHODIMP CBoxBeam::get_Width(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 top = m_W3 + 2*m_W2; // middle part
   top += m_bLeftBlockOut == VARIANT_FALSE  ? m_W4 : m_W1; // left part
   top += m_bRightBlockOut == VARIANT_FALSE ? m_W4 : m_W1; // right part

   Float64 bot = 2 * (m_W4 + m_W2) + m_W3;

   *pVal = max(top, bot);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_Height(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_H1 + m_H2 + m_H3;
   return S_OK;
}

STDMETHODIMP CBoxBeam::GetBoundaryPoints(IPoint2d ** ppLeftTop, IPoint2d ** ppLeftBottom, IPoint2d ** ppRightTop, IPoint2d ** ppRightBottom)
{
   CHECK_RETOBJ(ppLeftTop);
   CHECK_RETOBJ(ppLeftBottom);
   CHECK_RETOBJ(ppRightTop);
   CHECK_RETOBJ(ppRightBottom);

   UpdateShape();

   // outer shape
   CComPtr<ICompositeShapeItem> pOuterShapeItem;
   m_pShape->get_Item(0, &pOuterShapeItem);
   CComPtr<IShape> pOuterShape;
   pOuterShapeItem->get_Shape(&pOuterShape);
   CComQIPtr<IPolyShape> outer(pOuterShape);


   CComPtr<IPoint2d> leftTop, leftBottom, rightTop, rightBottom;
   outer->get_Point(m_LeftTopPointIdx, &leftTop);
   outer->get_Point(m_RightTopPointIdx, &rightTop);
   outer->get_Point(m_LeftBottomPointIdx, &leftBottom);
   outer->get_Point(m_RightBottomPointIdx, &rightBottom);

   // top points are actual points. simply clone them
   rightTop->Clone(ppRightTop);
   leftTop->Clone(ppLeftTop);

   // bottom points aren't that simple it there is a chamfer. we need to create a point at the intersection.
   if (m_C1 > 0.0)
   {
//
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            \                               / rB
//             \                             /
//           lB -----------------------------
//

// get points just before indexed points
      CComPtr<IPoint2d> leftBottomM1, rightBottomM1;
      outer->get_Point(m_RightBottomPointIdx-1, &rightBottomM1);
      outer->get_Point(m_LeftBottomPointIdx-1, &leftBottomM1);

      Float64 x, y;  // locations of corner without chamfer
      // left bottom
      leftBottomM1->get_X(&x);
      leftBottom->get_Y(&y);

      CreatePoint(x, y, nullptr, ppLeftBottom);

      // right bottom
      rightBottom->get_X(&x);
      rightBottomM1->get_Y(&y);

      CreatePoint(x, y, nullptr, ppRightBottom);
   }
   else
   {
      leftBottom->Clone(ppLeftBottom);
      rightBottom->Clone(ppRightBottom);
   }


   return E_NOTIMPL;
}


STDMETHODIMP CBoxBeam::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CBoxBeam::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CBoxBeam::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CBoxBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CBoxBeam::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CBoxBeam::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CBoxBeam::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CBoxBeam::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CBoxBeam::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CBoxBeam>* pTheClone;
   HRESULT hr = CComObject<CBoxBeam>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IBoxBeam> shape(pTheClone); // need at least one reference

   pTheClone->put_H1(m_H1);
   pTheClone->put_H2(m_H2);
   pTheClone->put_H3(m_H3);
   pTheClone->put_H4(m_H4);
   pTheClone->put_H5(m_H5);
   pTheClone->put_H6(m_H6);
   pTheClone->put_H7(m_H7);
   pTheClone->put_W1(m_W1);
   pTheClone->put_W2(m_W2);
   pTheClone->put_W3(m_W3);
   pTheClone->put_W4(m_W4);
   pTheClone->put_F1(m_F1);
   pTheClone->put_F2(m_F2);
   pTheClone->put_C1(m_C1);
   pTheClone->put_VoidCount( m_VoidCount );
   pTheClone->put_LeftBlockOut(m_bLeftBlockOut);
   pTheClone->put_RightBlockOut(m_bRightBlockOut);

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,nullptr,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CBoxBeam::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CBoxBeam::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CBoxBeam::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CBoxBeam::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->FurthestDistance(line,pVal);
}

/////////////////////////////////////////////////////////////////////////////
// ICompositeShape
/////////////////////////////////////////////////////////////////////////////
//STDMETHODIMP CBoxBeam::get_StructuredStorage(IStructuredStorage2* *pStg)
//{
//   return m_pShape->get_StructuredStorage(pStg);
//}
//
//STDMETHODIMP CBoxBeam::get_XYPosition(IXYPosition* *pVal)
//{
//   return m_pShape->get_XYPosition(pVal);
//}
//
//STDMETHODIMP CBoxBeam::get_Shape(IShape* *pVal)
//{
//   return m_pShape->get_Shape(pVal);
//}

STDMETHODIMP CBoxBeam::get_Item(CollectionIndexType idx,ICompositeShapeItem* *pVal)
{
   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   return m_pShape->get_Item(idx,pVal);
}

STDMETHODIMP CBoxBeam::get__NewEnum(IUnknown* *pVal)
{
   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   return m_pShape->get__NewEnum(pVal);
}

STDMETHODIMP CBoxBeam::get_Count(CollectionIndexType *pVal)
{
   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;

   return m_pShape->get_Count(pVal);
}

STDMETHODIMP CBoxBeam::Remove(CollectionIndexType idx)
{
   return m_pShape->Remove(idx);
}

STDMETHODIMP CBoxBeam::Clear()
{
   return m_pShape->Clear();
}

STDMETHODIMP CBoxBeam::ReplaceEx(CollectionIndexType idx,ICompositeShapeItem* pShapeItem)
{
   return m_pShape->ReplaceEx(idx,pShapeItem);
}

STDMETHODIMP CBoxBeam::Replace(CollectionIndexType idx,IShape* pShape)
{
   return m_pShape->Replace(idx,pShape);
}

STDMETHODIMP CBoxBeam::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   return m_pShape->AddShapeEx(ShapeItem);
}

STDMETHODIMP CBoxBeam::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   return m_pShape->AddShape(shape,bVoid);
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CBoxBeam::Offset(Float64 dx,Float64 dy)
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

STDMETHODIMP CBoxBeam::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->Dimensions(&dx, &dy);

   return Offset(dx,dy);
}

STDMETHODIMP CBoxBeam::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;


   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,nullptr,point);
}

STDMETHODIMP CBoxBeam::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CBoxBeam::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CBoxBeam::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CBoxBeam::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to make dirty since our hook point will call us back
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


STDMETHODIMP CBoxBeam::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CBoxBeam::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CBoxBeam::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("BoxBeam"),3.0);
   pSave->put_Property(CComBSTR("H1"),CComVariant(m_H1));
   pSave->put_Property(CComBSTR("H2"),CComVariant(m_H2));
   pSave->put_Property(CComBSTR("H3"),CComVariant(m_H3));
   pSave->put_Property(CComBSTR("H4"),CComVariant(m_H4));
   pSave->put_Property(CComBSTR("H5"),CComVariant(m_H5));
   pSave->put_Property(CComBSTR("H6"),CComVariant(m_H6));
   pSave->put_Property(CComBSTR("H7"),CComVariant(m_H7));
   pSave->put_Property(CComBSTR("W1"),CComVariant(m_W1));
   pSave->put_Property(CComBSTR("W2"),CComVariant(m_W2));
   pSave->put_Property(CComBSTR("W3"),CComVariant(m_W3));
   pSave->put_Property(CComBSTR("W4"),CComVariant(m_W4));
   pSave->put_Property(CComBSTR("F1"),CComVariant(m_F1));
   pSave->put_Property(CComBSTR("F2"),CComVariant(m_F2));
   pSave->put_Property(CComBSTR("C1"),CComVariant(m_C1));
   pSave->put_Property(CComBSTR("VoidCount"),CComVariant(m_VoidCount));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CBoxBeam::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("BoxBeam"));
   
   Float64 version;
   pLoad->get_Version(&version);

   if (2.0 < version )
      return STRLOAD_E_BADVERSION;

   Float64 h1(0), h2(0), h3(0), h4(0), h5(0), h6(0), h7(0), h8(0);
   Float64 w1(0), w2(0), w3(0), w4(0), w5(0);

   pLoad->get_Property(CComBSTR("H1"),&var);
   h1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("H2"),&var);
   h2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("H3"),&var);
   h3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("H4"),&var);
   h4 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("H5"),&var);
   h5 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("H6"),&var);
   h6 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("H7"),&var);
   h7 = var.dblVal;
   
   if (version < 2)
   {
      pLoad->get_Property(CComBSTR("H8"),&var);
      h8 = var.dblVal;
   }
   
   pLoad->get_Property(CComBSTR("W1"),&var);
   w1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W2"),&var);
   w2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W3"),&var);
   w3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W4"),&var);
   w4 = var.dblVal;
   
   if (version < 2)
   {
      pLoad->get_Property(CComBSTR("W5"),&var);
      w5 = var.dblVal;
   }

   // The definitions of W's, and H's changed radically between version 1 and 2. 
   // The old section was flawed due to redundant dimensions
   // Refer to BoxBeam.vsd in html help for mapping
   if (version < 2.0)
   {
      m_H1 = h8;
      m_H2 = h7;
      m_H3 = h6;
      m_H4 = h5;
      m_H5 = h4;
      m_H6 = h3;
      m_H7 = h2;

      m_W1 = w4;
      m_W2 = (w1-2*w4-w5)/2.0; // this also could be (w2-2*w3-w5)/2.0
      m_W3 = w5;
      m_W4 = w3;
   }
   else
   {
      m_H1 = h1;
      m_H2 = h2;
      m_H3 = h3;
      m_H4 = h4;
      m_H5 = h5;
      m_H6 = h6;
      m_H7 = h7;

      m_W1 = w1;
      m_W2 = w2;
      m_W3 = w3;
      m_W4 = w4;
   }
   
   pLoad->get_Property(CComBSTR("F1"),&var);
   m_F1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("F2"),&var);
   m_F2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("C1"),&var);
   m_C1 = var.dblVal;

   pLoad->get_Property(CComBSTR("C1"),&var);
   m_C1 = var.dblVal;

   if (version >= 3.0)
   {
      pLoad->get_Property(CComBSTR("VoidCount"),&var);
      m_VoidCount = var.iVal;
   }

   pLoad->get_Property(CComBSTR("Rotation"),&var);
   m_Rotation = var.dblVal;

   pLoad->get_Property(CComBSTR("HookPoint"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pHookPoint,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   HRESULT hr;
   hr = UpdateShape();
   if(FAILED(hr))
      return hr;


   return S_OK;
}

STDMETHODIMP CBoxBeam::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
