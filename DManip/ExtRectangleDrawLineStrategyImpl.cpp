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

// ExtRectangleDrawLineStrategyImpl.cpp: implementation of the CExtRectangleDrawLineStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "ExtRectangleDrawLineStrategyImpl.h"
#include <MathEx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExtRectangleDrawLineStrategyImpl::CExtRectangleDrawLineStrategyImpl()
{
}

CExtRectangleDrawLineStrategyImpl::~CExtRectangleDrawLineStrategyImpl()
{
}

HRESULT CExtRectangleDrawLineStrategyImpl::FinalConstruct()
{
   m_nWidth = 1;
   m_crColor = RGB(0,0,0);
   m_crFillColor = RGB(255,255,255);

   m_Style     = lsSolid;

   m_bPerimeterGravityWell = TRUE;
   m_bDoFill = FALSE;

   m_StartSkew = 0;
   m_EndSkew   = 0;

   m_StartExtension = 0;
   m_EndExtension   = 0;

   m_LeftOffset  = 0;
   m_RightOffset = 0;

   return S_OK;
}

/////////////////////////////////////////////////////////
// iLineDrawStrategy Implementation

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::Draw(iLineDisplayObject* pDO,CDC* pDC)
{
   CPoint p1, p2, p3, p4;
   GetDrawRect(pDO,&p1,&p2,&p3,&p4);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   COLORREF linecolor = m_crColor;
   COLORREF fillcolor = m_crFillColor;
   if ( pDO->IsSelected() )
   {
      linecolor = pDispMgr->GetSelectionLineColor();
      fillcolor = pDispMgr->GetSelectionFillColor();
   }

   // draw fill first
   if (m_bDoFill)
   {
      CPen pen(PS_SOLID,0,linecolor);
      CPen* oldPen = pDC->SelectObject(&pen);

      CBrush brush;
      if ( pDO->IsSelected() )
         brush.CreateHatchBrush(HS_DIAGCROSS,fillcolor);
      else
         brush.CreateSolidBrush(fillcolor);

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

   case lsCenterline:
      nPenStyle = PS_DASHDOTDOT;
      break;

   default:
      ATLASSERT(false);  // new type of pen style?
      nPenStyle = PS_SOLID;
      break;

   }

   DrawPerimeter(pDC, linecolor, nPenStyle, p1, p2, p3, p4);

//   ///////////////////// DEBUG DUMPS
//   CPoint vpOrg = pDC->GetViewportOrg();
//   CPoint wnOrg = pDC->GetWindowOrg();
//   CSize  vpExt = pDC->GetViewportExt();
//   CSize  wnExt = pDC->GetWindowExt();
//
//   TRACE("Viewport Origin:  x = %d,  y = %d\n",vpOrg.x,vpOrg.y);
//   TRACE("Viewport Extent: dx = %d, dy = %d\n",vpExt.cx,vpExt.cy);
//   TRACE("Window Origin:  x = %d,  y = %d\n",wnOrg.x,wnOrg.y);
//   TRACE("Window Extent: dx = %d, dy = %d\n",wnExt.cx,wnExt.cy);
//   CPoint p1d = p1;
//   pDC->LPtoDP(&p1d);
//   TRACE("LP x = %d, y = %d -> DP x = %d, y = %d\n",p1.x,p1.y,p1d.x,p1d.y);
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::DrawDragImage(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::DrawHighlite(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
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

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::GetBoundingBox(iLineDisplayObject* pDO,IRect2d** box)
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
   xmax = Max(xmax,x);
   ymax = Max(ymax,y);
   xmin = Min(xmin,x);
   ymin = Min(ymin,y);

   pntBR->get_X(&x);
   pntBR->get_Y(&y);
   xmax = Max(xmax,x);
   ymax = Max(ymax,y);
   xmin = Min(xmin,x);
   ymin = Min(ymin,y);

   pntTR->get_X(&x);
   pntTR->get_Y(&y);
   xmax = Max(xmax,x);
   ymax = Max(ymax,y);
   xmin = Min(xmin,x);
   ymin = Min(ymin,y);

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
// iExtRectangleLineDrawStrategy Implementation
STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::SetLeftOffset(Float64 offset)
{
   m_LeftOffset = offset;
}

STDMETHODIMP_(Float64) CExtRectangleDrawLineStrategyImpl::GetLeftOffset()
{
   return m_LeftOffset;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::SetRightOffset(Float64 offset)
{
   m_RightOffset = offset;
}

STDMETHODIMP_(Float64) CExtRectangleDrawLineStrategyImpl::GetRightOffset()
{
   return m_RightOffset;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::SetStartExtension(Float64 ext)
{
   m_StartExtension = ext;
}

STDMETHODIMP_(Float64) CExtRectangleDrawLineStrategyImpl::GetStartExtension()
{
   return m_StartExtension;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::SetEndExtension(Float64 ext)
{
   m_EndExtension = ext;
}

STDMETHODIMP_(Float64) CExtRectangleDrawLineStrategyImpl::GetEndExtension()
{
   return m_EndExtension;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::SetStartSkew(Float64 skew)
{
   m_StartSkew = skew;
}

STDMETHODIMP_(Float64) CExtRectangleDrawLineStrategyImpl::GetStartSkew()
{
   return m_StartSkew;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::SetEndSkew(Float64 skew)
{
   m_EndSkew = skew;
}

STDMETHODIMP_(Float64) CExtRectangleDrawLineStrategyImpl::GetEndSkew()
{
   return m_EndSkew;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::SetLineWidth(UINT nWidth)
{
   m_nWidth = nWidth;
}

STDMETHODIMP_(UINT) CExtRectangleDrawLineStrategyImpl::GetLineWidth()
{
   return m_nWidth;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::SetColor(COLORREF crColor)
{
   m_crColor = crColor;
}

STDMETHODIMP_(COLORREF) CExtRectangleDrawLineStrategyImpl::GetColor()
{
   return m_crColor;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::SetFillColor(COLORREF crColor)
{
   m_crFillColor = crColor;
}

STDMETHODIMP_(COLORREF) CExtRectangleDrawLineStrategyImpl::GetFillColor()
{
   return m_crFillColor;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::DoFill(BOOL fill)
{
   m_bDoFill = fill;
}

STDMETHODIMP_(BOOL) CExtRectangleDrawLineStrategyImpl::DoFill()
{
   return m_bDoFill;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::SetLineStyle(LineStyleType style)
{
   m_Style = style;
}

STDMETHODIMP_(LineStyleType) CExtRectangleDrawLineStrategyImpl::GetLineStyle()
{
   return m_Style;
}

STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::PerimeterGravityWell(BOOL bPerimeterGravityWell)
{
   m_bPerimeterGravityWell = bPerimeterGravityWell;
}

/////////////////////////////////////////////////////////
// iGravityWellStrategy Implementation
STDMETHODIMP_(void) CExtRectangleDrawLineStrategyImpl::GetGravityWell(iDisplayObject* pDO,CRgn* pRgn)
{
   CComQIPtr<iLineDisplayObject,&IID_iLineDisplayObject> pLine(pDO);

#pragma Reminder("Implement Gravity Well Correctly")

   CPoint p[4];
   GetDrawRect(pLine,&p[0],&p[1],&p[2],&p[3]);

   VERIFY(pRgn->CreatePolygonRgn(p,4,ALTERNATE));
}

/////////////////////////////////

void CExtRectangleDrawLineStrategyImpl::GetStartPoint(iLineDisplayObject* pDO,IPoint2d* *point)
{
   CComQIPtr<iConnector,&IID_iConnector> connector(pDO);

   CComPtr<iPlug> plug;
   connector->GetStartPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}

void CExtRectangleDrawLineStrategyImpl::GetEndPoint(iLineDisplayObject* pDO,IPoint2d* *point)
{
   CComQIPtr<iConnector,&IID_iConnector> connector(pDO);

   CComPtr<iPlug> plug;
   connector->GetEndPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}

void CExtRectangleDrawLineStrategyImpl::GetPoints(iLineDisplayObject* pDO,IPoint2d** pntTopLeft,IPoint2d** pntBottomLeft,IPoint2d** pntBottomRight,IPoint2d** pntTopRight)
{
   // This functino returns the points in World Space

   // start by getting the points in model space
   CComPtr<IPoint2d> pntStart, pntEnd;
   pDO->GetEndPoints(&pntStart,&pntEnd);

   Float64 sx,sy,ex,ey;
   pntStart->get_X(&sx); pntStart->get_Y(&sy);
   pntEnd->get_X(&ex);   pntEnd->get_Y(&ey);

   Float64 angle = atan2(ey-sy,ex-sx);

   // start extension, left side
   Float64 SELx = sx - m_StartExtension*cos(angle) - (m_LeftOffset/cos(m_StartSkew))*cos(angle+m_StartSkew+PI_OVER_2);
   Float64 SELy = sy - m_StartExtension*sin(angle) - (m_LeftOffset/cos(m_StartSkew))*sin(angle+m_StartSkew+PI_OVER_2);
   
   // start extension, right side
   Float64 SERx = sx - m_StartExtension*cos(angle) + (m_RightOffset/cos(m_StartSkew))*cos(angle+m_StartSkew+PI_OVER_2);
   Float64 SERy = sy - m_StartExtension*sin(angle) + (m_RightOffset/cos(m_StartSkew))*sin(angle+m_StartSkew+PI_OVER_2);

   // end extension, left side
   Float64 EELx = ex + m_EndExtension*cos(angle) - (m_LeftOffset/cos(m_EndSkew))*cos(angle+m_EndSkew+PI_OVER_2);
   Float64 EELy = ey + m_EndExtension*sin(angle) - (m_LeftOffset/cos(m_EndSkew))*sin(angle+m_EndSkew+PI_OVER_2);

   // end extension, right side
   Float64 EERx = ex + m_EndExtension*cos(angle) + (m_RightOffset/cos(m_EndSkew))*cos(angle+m_EndSkew+PI_OVER_2);
   Float64 EERy = ey + m_EndExtension*sin(angle) + (m_RightOffset/cos(m_EndSkew))*sin(angle+m_EndSkew+PI_OVER_2);

   //
   // Map the Model space points into World Space
   //

   // first we need the coordinate mapper
   CComPtr<iDisplayList> display_list;
   pDO->GetDisplayList(&display_list);

   CComPtr<iDisplayMgr> display_mgr;
   display_list->GetDisplayMgr(&display_mgr);

   CComPtr<iCoordinateMap> map;
   display_mgr->GetCoordinateMap(&map);

   map->MPtoWP(SELx,SELy,&SELx,&SELy);
   map->MPtoWP(SERx,SERy,&SERx,&SERy);
   map->MPtoWP(EELx,EELy,&EELx,&EELy);
   map->MPtoWP(EERx,EERy,&EERx,&EERy);

   // this points are all in world space
   CComPtr<IPoint2d> pntTL;
   pntTL.CoCreateInstance(CLSID_Point2d);
   pntTL->Move(SELx,SELy);

   CComPtr<IPoint2d> pntBL;
   pntBL.CoCreateInstance(CLSID_Point2d);
   pntBL->Move(SERx,SERy);

   CComPtr<IPoint2d> pntBR;
   pntBR.CoCreateInstance(CLSID_Point2d);
   pntBR->Move(EERx,EERy);

   CComPtr<IPoint2d> pntTR;
   pntTR.CoCreateInstance(CLSID_Point2d);
   pntTR->Move(EELx,EELy);

   (*pntTopLeft) = pntTL;
   (*pntTopLeft)->AddRef();

   (*pntBottomLeft) = pntBL;
   (*pntBottomLeft)->AddRef();

   (*pntBottomRight) = pntBR;
   (*pntBottomRight)->AddRef();

   (*pntTopRight) = pntTR;
   (*pntTopRight)->AddRef();
}

void CExtRectangleDrawLineStrategyImpl::GetDrawRect(iLineDisplayObject* pDO,CPoint* p1,CPoint* p2,CPoint* p3,CPoint* p4)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   CComPtr<IPoint2d> pntTL, pntTR, pntBL, pntBR;
   GetPoints(pDO,&pntTL,&pntBL,&pntBR,&pntTR); // these points are in world coordinates

   pMap->WPtoLP(pntTL,&(p1->x),&(p1->y));
   pMap->WPtoLP(pntBL,&(p2->x),&(p2->y));
   pMap->WPtoLP(pntBR,&(p3->x),&(p3->y));
   pMap->WPtoLP(pntTR,&(p4->x),&(p4->y));
}

void CExtRectangleDrawLineStrategyImpl::DrawPerimeter(CDC* pDC,COLORREF color, int penStyle, CPoint& p1,CPoint& p2,CPoint& p3,CPoint& p4)
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

