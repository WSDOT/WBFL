///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// SimpleDrawPointStrategyImpl.cpp: implementation of the CSimpleDrawPointStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "SimpleDrawPointStrategyImpl.h"
#include <MathEx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimpleDrawPointStrategyImpl::CSimpleDrawPointStrategyImpl()
{
   m_Color = RGB(0,0,0); // black
   m_Type  = ptCircle;
   m_Size  = 0;
   m_LogicalSize = 0;
   m_bIsLogicalPoint = false;
   m_CachePoint.CoCreateInstance(CLSID_Point2d);
}

CSimpleDrawPointStrategyImpl::~CSimpleDrawPointStrategyImpl()
{

}

STDMETHODIMP_(void) CSimpleDrawPointStrategyImpl::SetColor(COLORREF crColor)
{
   m_Color = crColor;
}

STDMETHODIMP_(COLORREF) CSimpleDrawPointStrategyImpl::GetColor()
{
   return m_Color;
}

STDMETHODIMP_(void) CSimpleDrawPointStrategyImpl::SetPointType(PointType type)
{
   m_Type = type;
}

STDMETHODIMP_(PointType) CSimpleDrawPointStrategyImpl::GetPointType()
{
   return m_Type;
}

STDMETHODIMP_(void) CSimpleDrawPointStrategyImpl::SetPointSize(Float64 size)
{
   m_bIsLogicalPoint = false;
   m_Size = size;
}

STDMETHODIMP_(Float64) CSimpleDrawPointStrategyImpl::GetPointSize()
{
   return m_Size;
}

STDMETHODIMP_(void) CSimpleDrawPointStrategyImpl::SetLogicalPointSize(int size)
{
   m_bIsLogicalPoint = true;
   m_LogicalSize = size;
}

STDMETHODIMP_(int) CSimpleDrawPointStrategyImpl::GetLogicalPointSize()
{
   return m_LogicalSize;
}

STDMETHODIMP_(void) CSimpleDrawPointStrategyImpl::Draw(iPointDisplayObject* pDO,CDC* pDC)
{
   CRect r = GetPointBox(pDO);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   COLORREF line_color, fill_color;
   if ( pDO->IsSelected() )
   {
      line_color = pDispMgr->GetSelectionLineColor();
      fill_color = pDispMgr->GetSelectionFillColor();
   }
   else
   {
      line_color = m_Color;
      fill_color = m_Color;
   }

   CPen pen(PS_SOLID,1,line_color);
   CPen* pOldPen = pDC->SelectObject(&pen);

   CBrush brush(fill_color);
   CBrush* pOldBrush = pDC->SelectObject(&brush);

   DrawMe(r,pDC);

   pDC->SelectObject(pOldPen);
   pDC->SelectObject(pOldBrush);
}

STDMETHODIMP_(void) CSimpleDrawPointStrategyImpl::DrawHighlite(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   CRect r = GetPointBox(pDO);

   COLORREF color;
   color = RGB(0,255,0);

   UINT nWidth = bHighlite ? 2 : 1;
   CPen pen(PS_SOLID,nWidth,color);
   CPen* pOldPen = pDC->SelectObject(&pen);
   DrawMe(r,pDC);
   pDC->SelectObject(pOldPen);
}

STDMETHODIMP_(void) CSimpleDrawPointStrategyImpl::DrawDragImage(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
   map->LPtoWP(dragPoint.x, dragPoint.y, &m_CachePoint);

   CRect r = GetPointBox(pDO);

   COLORREF color;
   color = RGB(0,0,255);

   CPen pen(PS_SOLID,1,color);
   CPen* pOldPen = pDC->SelectObject(&pen);
   DrawMe(r,pDC);
   pDC->SelectObject(pOldPen);
}

STDMETHODIMP_(void) CSimpleDrawPointStrategyImpl::GetBoundingBox(iPointDisplayObject* pDO, IRect2d** rect)
{
   Float64 px,py;
   GetPointInWorldSpace(pDO,&px,&py);

   CComPtr<IRect2d> bounding_box;
   bounding_box.CoCreateInstance(CLSID_Rect2d);

   if ( IsZero(m_Size) )
   {
      // make 4x4 logical size
      CComPtr<iDisplayList> pDL;
      pDO->GetDisplayList(&pDL);
      CComPtr<iDisplayMgr> pDispMgr;
      pDL->GetDisplayMgr(&pDispMgr);
      CComPtr<iCoordinateMap> pMap;
      pDispMgr->GetCoordinateMap(&pMap);

      Float64 xo,yo;
      pMap->LPtoWP(0,0,&xo,&yo);
      Float64 x2,y2;
      pMap->LPtoWP(4,4,&x2,&y2);

      Float64 wid = fabs(x2-xo);
      Float64 hgt = fabs(y2-yo);

      bounding_box->put_Left(px-wid);
      bounding_box->put_Bottom(py-hgt);
      bounding_box->put_Right(px+wid);
      bounding_box->put_Top(py+hgt);
   }
   else
   {
      Float64 left   = px - m_Size/2;
      Float64 right  = px + m_Size/2;
      Float64 top    = py + m_Size/2;
      Float64 bottom = py - m_Size/2;

      bounding_box->put_Left(left);
      bounding_box->put_Bottom(bottom);
      bounding_box->put_Right(right);
      bounding_box->put_Top(top);
   }

   (*rect) = bounding_box;
   (*rect)->AddRef();
}


void CSimpleDrawPointStrategyImpl::DrawMe(const CRect& rect,CDC* pDC)
{
   // sometimes mapping skews the shape... clean that up here
   int width = rect.Width();
   int height = rect.Height();

   CRect r(rect);

   if ( width < height )
   {
      int cx = r.CenterPoint().x;
      r.left  = cx - height/2;      
      r.right = cx + height/2;      
   }
   else if ( height < width )
   {
      int cy = r.CenterPoint().y;
      r.top    = cy - width/2;
      r.bottom = cy + width/2;
   }

   switch ( m_Type )
   {
   case ptNone:
      break; // do nothing

   case ptCircle:
      pDC->Ellipse(r);
      break;

   case ptSquare:
      pDC->Rectangle(r);
      break;

   case ptCrossHair:
      pDC->MoveTo(rect.left, rect.CenterPoint().y);
      pDC->LineTo(rect.right, rect.CenterPoint().y);
      pDC->MoveTo(rect.CenterPoint().x, rect.bottom );
      pDC->LineTo(rect.CenterPoint().x, rect.top );
      break;

   default:
      ATLASSERT(false); // should never get here!!!
   }
}

void CSimpleDrawPointStrategyImpl::GetPointInWorldSpace(iPointDisplayObject* pDO,Float64* wx,Float64* wy)
{
   // this is the point in Model Space
   CComPtr<IPoint2d> point;
   pDO->GetPosition(&point);

   // get the coordinate map
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   // map the point to world space
   pMap->MPtoWP(point,wx,wy);
}

CRect CSimpleDrawPointStrategyImpl::GetPointBox(iPointDisplayObject* pDO)
{
   CRect rect;
   if (m_bIsLogicalPoint)
   {
      Float64 px, py;
      GetPointInWorldSpace(pDO, &px, &py);

      CComPtr<iDisplayList> pDL;
      pDO->GetDisplayList(&pDL);
      CComPtr<iDisplayMgr> pDispMgr;
      pDL->GetDisplayMgr(&pDispMgr);
      CComPtr<iCoordinateMap> pMap;
      pDispMgr->GetCoordinateMap(&pMap);

      LONG x, y;
      pMap->WPtoLP(px, py, &x, &y);

      rect.left = x - m_LogicalSize / 2;
      rect.right = rect.left + m_LogicalSize;
      rect.top = y - m_LogicalSize / 2;
      rect.bottom = rect.top + m_LogicalSize;
   }
   else
   {
      rect = pDO->GetBoundingBox();
   }

   return rect;
}