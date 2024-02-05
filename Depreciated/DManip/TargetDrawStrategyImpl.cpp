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

// TargetDrawStrategyImpl.cpp: implementation of the CTargetDrawStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "TargetDrawStrategyImpl.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTargetDrawStrategyImpl::CTargetDrawStrategyImpl()
{
   m_Radius = 7;
   m_FgColor = RGB(200,0,0); // red
   m_BgColor = RGB(200,200,200); // white
   m_CachePoint.CoCreateInstance(CLSID_Point2d);
}

CTargetDrawStrategyImpl::~CTargetDrawStrategyImpl()
{

}

STDMETHODIMP_(void) CTargetDrawStrategyImpl::SetRadius(LONG radius)
{
   m_Radius = radius;
}

STDMETHODIMP_(LONG) CTargetDrawStrategyImpl::GetRadius()
{
   return m_Radius;
}

STDMETHODIMP_(void) CTargetDrawStrategyImpl::SetFgColor(COLORREF crColor)
{
   m_FgColor = crColor;
}

STDMETHODIMP_(COLORREF) CTargetDrawStrategyImpl::GetFgColor()
{
   return m_FgColor;
}

STDMETHODIMP_(void) CTargetDrawStrategyImpl::SetBgColor(COLORREF crColor)
{
   m_BgColor = crColor;
}

STDMETHODIMP_(COLORREF) CTargetDrawStrategyImpl::GetBgColor()
{
   return m_BgColor;
}

STDMETHODIMP_(void) CTargetDrawStrategyImpl::Draw(iPointDisplayObject* pDO,CDC* pDC)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   if ( pDO->IsSelected() )
      m_Color = pDispMgr->GetSelectionLineColor();
   else
      m_Color = m_FgColor;

   DrawMe(pDO,pDC);
}

STDMETHODIMP_(void) CTargetDrawStrategyImpl::DrawHighlite(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   m_Color = RGB(0,255,0);
   DrawMe(pDO,pDC);
}

STDMETHODIMP_(void) CTargetDrawStrategyImpl::DrawDragImage(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
   map->LPtoWP(dragPoint.x, dragPoint.y, &m_CachePoint);

   m_Color = RGB(0,0,255);

   DrawMe(pDO,pDC);
}

STDMETHODIMP_(void) CTargetDrawStrategyImpl::GetBoundingBox(iPointDisplayObject* pDO, IRect2d** rect)
{
   CComPtr<IPoint2d> point;
   pDO->GetPosition(&point);

   Float64 px, py;
   point->get_X(&px);
   point->get_Y(&py);

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
   pMap->LPtoWP(m_Radius,m_Radius,&x2,&y2);

   Float64 wid = fabs(x2-xo);
   Float64 hgt = fabs(y2-yo);

   CComPtr<IRect2d> bounding_box;
   bounding_box.CoCreateInstance(CLSID_Rect2d);

   bounding_box->put_Left(px-wid);
   bounding_box->put_Bottom(py-hgt);
   bounding_box->put_Right(px+wid);
   bounding_box->put_Top(py+hgt);

   (*rect) = bounding_box;
   (*rect)->AddRef();
}


void CTargetDrawStrategyImpl::DrawMe(iPointDisplayObject* pDO,CDC* pDC)
{
   CRect rect = pDO->GetBoundingBox();

   // Draw the background
   CPen bgpen(PS_SOLID,1,m_BgColor);
   CPen* pOldPen = pDC->SelectObject(&bgpen);

   CBrush bgbrush(m_BgColor);
   CBrush* pOldBrush = pDC->SelectObject(&bgbrush);

   pDC->Ellipse(rect);

   // Draw the forground
   CPen fgpen(PS_SOLID,1,m_Color);
   CBrush fgbrush(m_Color);

   pDC->SelectObject(&fgpen);
   pDC->SelectObject(&fgbrush);

   CPoint center = rect.CenterPoint();
   pDC->Pie(rect.left,rect.top, rect.right, rect.bottom, center.x, rect.top,    rect.left,  center.y);
   pDC->Pie(rect.left,rect.top, rect.right, rect.bottom, center.x, rect.bottom, rect.right, center.y);

   pDC->SelectObject(pOldPen);
   pDC->SelectObject(pOldBrush);
}
