///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

// RectangleDrawLineStrategyImpl.cpp: implementation of the CRectangleDrawLineStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "RectangleDrawLineStrategyImpl.h"
#include <math.h>

#include "DManipDebug.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangleDrawLineStrategyImpl::CRectangleDrawLineStrategyImpl()
{
}

CRectangleDrawLineStrategyImpl::~CRectangleDrawLineStrategyImpl()
{
}

HRESULT CRectangleDrawLineStrategyImpl::FinalConstruct()
{
   m_nWidth = 1;
   m_crColor = RGB(0,0,0);
   m_crFillColor = RGB(255,255,255);

   m_Style     = lsSolid;

   m_bPerimeterGravityWell = TRUE;
   m_bDoFill = FALSE;

   return S_OK;
}

/////////////////////////////////////////////////////////
// iLineDrawStrategy Implementation

STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::Draw(iLineDisplayObject* pDO,CDC* pDC)
{
   CPoint p1, p2, p3, p4;
   GetDrawRect(pDO,&p1,&p2,&p3,&p4);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   // draw fill first
   if (m_bDoFill)
   {
      COLORREF fill_color = pDO->IsSelected() ? pDispMgr->GetSelectionFillColor() : m_crFillColor;
      CPen pen(PS_SOLID,0,fill_color);
      CPen* oldPen = pDC->SelectObject(&pen);

      CBrush brush;
      if ( pDO->IsSelected() )
      {
         brush.CreateHatchBrush(HS_DIAGCROSS,fill_color);
      }
      else
      {
         brush.CreateSolidBrush(fill_color);
      }
      CBrush* oldBrush = pDC->SelectObject(&brush);

      POINT points[4];
      points[0] = p1;
      points[1] = p2;
      points[2] = p3;
      points[3] = p4;

      pDC->Polygon(points, 4);

      pDC->SelectObject(oldPen);
      pDC->SelectObject(&oldBrush);
   }

   COLORREF color = m_crColor;
   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();

   int nPenStyle;
   switch(m_Style)
   {
   case lsSolid:
      nPenStyle = PS_SOLID;
      break;
      
   case lsDot:
      nPenStyle = PS_DOT;
      break;

   case lsDash:
      nPenStyle = PS_DASH;
      break;
   }

   DrawPerimeter(pDC, color, nPenStyle, p1, p2, p3, p4);

   ///////////////////// DEBUG DUMPS
   CPoint vpOrg = pDC->GetViewportOrg();
   CPoint wnOrg = pDC->GetWindowOrg();
   CSize  vpExt = pDC->GetViewportExt();
   CSize  wnExt = pDC->GetWindowExt();

   WATCHX(DManip,1,_T("Viewport Origin:  x = ") << vpOrg.x  << _T(" y = ") << vpOrg.y);
   WATCHX(DManip,1,_T("Viewport Extent:  x = ") << vpExt.cx << _T(" y = ") << vpExt.cy);
   WATCHX(DManip,1,_T("Window   Origin:  x = ") << wnOrg.x  << _T(" y = ") << wnOrg.y);
   WATCHX(DManip,1,_T("Window   Extent:  x = ") << wnExt.cx << _T(" y = ") << wnExt.cy);
   CPoint p1d = p1;
   pDC->LPtoDP(&p1d);
   WATCHX(DManip,1,_T("LP x = ") << p1.x << _T(" y = ") << p1.y << _T(" -> DP x = ") << p1d.x << _T(" y = ") << p1d.y);
}

STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::DrawDragImage(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
#pragma Reminder("IMPLEMENT")
   ATLASSERT(false); // implement
}

STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::DrawHighlite(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   CPoint p1, p2, p3, p4;
   GetDrawRect(pDO,&p1,&p2,&p3,&p4);

   if ( bHighlite )
   {
      DrawPerimeter(pDC, RGB(255,128,128), PS_SOLID, p1, p2, p3, p4);
   }
   else
   {
      int nPenStyle;
      switch(m_Style)
      {
      case lsSolid:
         nPenStyle = PS_SOLID;
         break;
      
      case lsDot:
         nPenStyle = PS_DOT;
         break;

      case lsDash:
         nPenStyle = PS_DASH;
         break;
      }

      DrawPerimeter(pDC, m_crColor, nPenStyle, p1, p2, p3, p4);
   }
}

STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::GetBoundingBox(iLineDisplayObject* pDO,IRect2d** box)
{
   CComPtr<IPoint2d> pntTL, pntTR, pntBL, pntBR;
   GetPoints(pDO,&pntTL,&pntBL,&pntBR,&pntTR);

   Float64 x,y;
   pntTL->get_X(&x);
   pntTL->get_Y(&y);

   Float64 xmax,ymax,xmin,ymin;
   xmax = x;
   ymax = y;
   xmin = x;
   ymin = y;

   pntBL->get_X(&x);
   pntBL->get_Y(&y);
   xmax = _cpp_max(xmax,x);
   ymax = _cpp_max(ymax,y);
   xmin = _cpp_min(xmin,x);
   ymin = _cpp_min(ymin,y);

   pntBR->get_X(&x);
   pntBR->get_Y(&y);
   xmax = _cpp_max(xmax,x);
   ymax = _cpp_max(ymax,y);
   xmin = _cpp_min(xmin,x);
   ymin = _cpp_min(ymin,y);

   pntTR->get_X(&x);
   pntTR->get_Y(&y);
   xmax = _cpp_max(xmax,x);
   ymax = _cpp_max(ymax,y);
   xmin = _cpp_min(xmin,x);
   ymin = _cpp_min(ymin,y);

   CComPtr<IRect2d> rect;
   rect.CoCreateInstance(CLSID_Rect2d);

   rect->put_Left(xmin);
   rect->put_Right(xmax);
   rect->put_Bottom(ymin);
   rect->put_Top(ymax);

   (*box) = rect;
   (*box)->AddRef();
}

/////////////////////////////////////////////////////////
// iRectangleLineDrawStrategy Implementation
STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::SetWidth(Float64 width)
{
   m_RectWidth = width;
}

STDMETHODIMP_(Float64) CRectangleDrawLineStrategyImpl::GetWidth()
{
   return m_RectWidth;
}

STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::SetLineWidth(UINT nWidth)
{
   m_nWidth = nWidth;
}

STDMETHODIMP_(UINT) CRectangleDrawLineStrategyImpl::GetLineWidth()
{
   return m_nWidth;
}

STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::SetColor(COLORREF crColor)
{
   m_crColor = crColor;
}

STDMETHODIMP_(COLORREF) CRectangleDrawLineStrategyImpl::GetColor()
{
   return m_crColor;
}

STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::SetFillColor(COLORREF crColor)
{
   m_crFillColor = crColor;
}

STDMETHODIMP_(COLORREF) CRectangleDrawLineStrategyImpl::GetFillColor()
{
   return m_crFillColor;
}

STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::DoFill(BOOL fill)
{
   m_bDoFill = fill;
}

STDMETHODIMP_(BOOL) CRectangleDrawLineStrategyImpl::DoFill()
{
   return m_bDoFill;
}

STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::SetLineStyle(LineStyleType style)
{
   m_Style = style;
}

STDMETHODIMP_(LineStyleType) CRectangleDrawLineStrategyImpl::GetLineStyle()
{
   return m_Style;
}

STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::PerimeterGravityWell(BOOL bPerimeterGravityWell)
{
   m_bPerimeterGravityWell = bPerimeterGravityWell;
}

/////////////////////////////////////////////////////////
// iGravityWellStrategy Implementation
STDMETHODIMP_(void) CRectangleDrawLineStrategyImpl::GetGravityWell(iDisplayObject* pDO,CRgn* pRgn)
{
   CComQIPtr<iLineDisplayObject,&IID_iLineDisplayObject> pLine(pDO);

#pragma Reminder("Implement Gravity Well Correctly")

   CPoint p[4];
   GetDrawRect(pLine,&p[0],&p[1],&p[2],&p[3]);

   VERIFY(pRgn->CreatePolygonRgn(p,4,ALTERNATE));
}

/////////////////////////////////

void CRectangleDrawLineStrategyImpl::GetStartPoint(iLineDisplayObject* pDO,IPoint2d* *point)
{
   CComQIPtr<iConnector,&IID_iConnector> connector(pDO);

   CComPtr<iPlug> plug;
   connector->GetStartPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}

void CRectangleDrawLineStrategyImpl::GetEndPoint(iLineDisplayObject* pDO,IPoint2d* *point)
{
   CComQIPtr<iConnector,&IID_iConnector> connector(pDO);

   CComPtr<iPlug> plug;
   connector->GetEndPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}

void CRectangleDrawLineStrategyImpl::GetPoints(iLineDisplayObject* pDO,IPoint2d** pntTopLeft,IPoint2d** pntBottomLeft,IPoint2d** pntBottomRight,IPoint2d** pntTopRight)
{
   CComPtr<IPoint2d> pntStart, pntEnd;
   pDO->GetEndPoints(&pntStart,&pntEnd);

   Float64 sx,sy,ex,ey;
   pntStart->get_X(&sx); pntStart->get_Y(&sy);
   pntEnd->get_X(&ex);   pntEnd->get_Y(&ey);

   Float64 angle = atan2(ey-sy,ex-sx);

   Float64 wx = m_RectWidth*sin(angle)/2;
   Float64 wy = m_RectWidth*cos(angle)/2;

   CComPtr<IPoint2d> pntTL;
   pntTL.CoCreateInstance(CLSID_Point2d);
   pntTL->Move(sx-wx,sy+wy);

   CComPtr<IPoint2d> pntBL;
   pntBL.CoCreateInstance(CLSID_Point2d);
   pntBL->Move(sx+wx,sy-wy);

   CComPtr<IPoint2d> pntBR;
   pntBR.CoCreateInstance(CLSID_Point2d);
   pntBR->Move(ex+wx,ey-wy);

   CComPtr<IPoint2d> pntTR;
   pntTR.CoCreateInstance(CLSID_Point2d);
   pntTR->Move(ex-wx,ey+wy);

   (*pntTopLeft) = pntTL;
   (*pntTopLeft)->AddRef();

   (*pntBottomLeft) = pntBL;
   (*pntBottomLeft)->AddRef();

   (*pntBottomRight) = pntBR;
   (*pntBottomRight)->AddRef();

   (*pntTopRight) = pntTR;
   (*pntTopRight)->AddRef();
}

void CRectangleDrawLineStrategyImpl::GetDrawRect(iLineDisplayObject* pDO,CPoint* p1,CPoint* p2,CPoint* p3,CPoint* p4)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   CComPtr<IPoint2d> pntTL, pntTR, pntBL, pntBR;
   GetPoints(pDO,&pntTL,&pntBL,&pntBR,&pntTR);

   pMap->WPtoLP(pntTL,&(p1->x),&(p1->y));
   pMap->WPtoLP(pntBL,&(p2->x),&(p2->y));
   pMap->WPtoLP(pntBR,&(p3->x),&(p3->y));
   pMap->WPtoLP(pntTR,&(p4->x),&(p4->y));
}

void CRectangleDrawLineStrategyImpl::DrawPerimeter(CDC* pDC,COLORREF color, int penStyle, CPoint& p1,CPoint& p2,CPoint& p3,CPoint& p4)
{
   CPen pen(penStyle,m_nWidth,color);
   CPen* oldPen = pDC->SelectObject(&pen);

   // Draw the rectangle
   pDC->MoveTo(p1);
   pDC->LineTo(p2);
   pDC->LineTo(p3);
   pDC->LineTo(p4);
   pDC->LineTo(p1);

   // Cleanup
   pDC->SelectObject(oldPen);

}

