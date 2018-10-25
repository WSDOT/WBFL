///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// SimpleDrawLineStrategyImpl.cpp: implementation of the CSimpleDrawLineStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "SimpleDrawLineStrategyImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimpleDrawLineStrategyImpl::CSimpleDrawLineStrategyImpl()
{
}

CSimpleDrawLineStrategyImpl::~CSimpleDrawLineStrategyImpl()
{
}

HRESULT CSimpleDrawLineStrategyImpl::FinalConstruct()
{
   m_nWidth = 1;
   m_crColor = RGB(0,0,0);

   m_BeginType = leNone;
   m_BeginSize = 0;
   m_EndType   = leNone;
   m_EndSize   = 0;
   m_Style     = lsSolid;

   return S_OK;
}

/////////////////////////////////////////////////////////
// iLineDrawStrategy Implementation

STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::Draw(iLineDisplayObject* pDO,CDC* pDC)
{
   Float64 sx,sy, ex,ey;
   GetPointsInWorldSpace(pDO,&sx,&sy,&ex,&ey);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   CPoint start, end;
   pMap->WPtoLP(sx,sy,&start.x,&start.y);
   pMap->WPtoLP(ex,ey,&end.x,&end.y);

   COLORREF color = m_crColor;
   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();

   DWORD centerStyle[] = { 20, 2, 3, 2 };
   LOGBRUSH lb;
   lb.lbStyle = BS_SOLID;
   lb.lbColor = color;
   lb.lbHatch = 0;
   CPen pen;
   switch(m_Style)
   {
   case lsSolid:
      pen.CreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_JOIN_BEVEL, m_nWidth, &lb);
      break;
      
   case lsDot:
      pen.CreatePen(PS_DOT,m_nWidth,color);
      break;

   case lsDash:
      pen.CreatePen(PS_DASH,m_nWidth,color);
      break;

   case lsCenterline:
      pen.CreatePen(PS_USERSTYLE | PS_GEOMETRIC,m_nWidth,&lb,sizeof(centerStyle)/sizeof(DWORD),centerStyle);
      break;
   }

   CPen* oldPen = pDC->SelectObject(&pen);

   // Draw the main line
   pDC->MoveTo(start);
   pDC->LineTo(end);

   // Draw the begining end
   if ( m_BeginType == leCircle || m_BeginType == leDot )
   {
      CRect rect(start,start);
      rect.InflateRect(m_BeginSize,m_BeginSize);
      pDC->Ellipse(rect);
   }

   // Draw the terminous end
   if ( m_EndType == leCircle || m_EndType == leDot )
   {
      CRect rect(end,end);
      rect.InflateRect(m_EndSize,m_EndSize);
      pDC->Ellipse(rect);
   }

   // Cleanup
   pDC->SelectObject(oldPen);
}

STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::DrawDragImage(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
}

STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::DrawHighlite(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
}

STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::GetBoundingBox(iLineDisplayObject* pDO,IRect2d** box)
{
   // the end points of this line are in Model Space
   // the need to be converted to World Space for the bounding box
   Float64 sx,sy, ex,ey;
   GetPointsInWorldSpace(pDO,&sx,&sy,&ex,&ey);

   CComPtr<IRect2d> rect;
   rect.CoCreateInstance(CLSID_Rect2d);

   rect->put_Left(_cpp_min(sx, ex));
   rect->put_Bottom(_cpp_min(sy, ey));
   rect->put_Right(_cpp_max(sx, ex));
   rect->put_Top(_cpp_max(sy, ey));

   (*box) = rect;
   (*box)->AddRef();
}

/////////////////////////////////////////////////////////
// iSimpleLineDrawStrategy Implementation
STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::SetWidth(UINT nWidth)
{
   m_nWidth = nWidth;
}

STDMETHODIMP_(UINT) CSimpleDrawLineStrategyImpl::GetWidth()
{
   return m_nWidth;
}

STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::SetColor(COLORREF crColor)
{
   m_crColor = crColor;
}

STDMETHODIMP_(COLORREF) CSimpleDrawLineStrategyImpl::GetColor()
{
   return m_crColor;
}

STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::SetBeginType(LineEndType type)
{
   m_BeginType = type;
}

STDMETHODIMP_(LineEndType) CSimpleDrawLineStrategyImpl::GetBeginType()
{
   return m_BeginType;
}

STDMETHODIMP_(int) CSimpleDrawLineStrategyImpl::GetBeginSize()
{
   return m_BeginSize;
}

STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::SetBeginSize(int size)
{
   m_BeginSize = size;
}

STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::SetEndType(LineEndType type)
{
   m_EndType = type;
}

STDMETHODIMP_(LineEndType) CSimpleDrawLineStrategyImpl::GetEndType()
{
   return m_EndType;
}

STDMETHODIMP_(int) CSimpleDrawLineStrategyImpl::GetEndSize()
{
   return m_EndSize;
}

STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::SetEndSize(int size)
{
   m_EndSize = size;
}

STDMETHODIMP_(void) CSimpleDrawLineStrategyImpl::SetLineStyle(LineStyleType style)
{
   m_Style = style;
}

STDMETHODIMP_(LineStyleType) CSimpleDrawLineStrategyImpl::GetLineStyle()
{
   return m_Style;
}

/////////////////////////////////

void CSimpleDrawLineStrategyImpl::GetStartPoint(iLineDisplayObject* pDO,IPoint2d* *point)
{
   CComQIPtr<iConnector,&IID_iConnector> connector(pDO);

   CComPtr<iPlug> plug;
   connector->GetStartPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}

void CSimpleDrawLineStrategyImpl::GetEndPoint(iLineDisplayObject* pDO,IPoint2d* *point)
{
   CComQIPtr<iConnector,&IID_iConnector> connector(pDO);

   CComPtr<iPlug> plug;
   connector->GetEndPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}

void CSimpleDrawLineStrategyImpl::GetPointsInWorldSpace(iLineDisplayObject* pDO,Float64* sx,Float64* sy,Float64* ex,Float64* ey)
{
   // the end points of this line are in Model Space
   // the need to be converted to World Space for the bounding box


   // start by getting the coordinate mapper
   CComPtr<iDisplayList> display_list;
   pDO->GetDisplayList(&display_list);

   CComPtr<iDisplayMgr> display_mgr;
   display_list->GetDisplayMgr(&display_mgr);

   CComPtr<iCoordinateMap> map;
   display_mgr->GetCoordinateMap(&map);

   // get the points
   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;
   pDO->GetEndPoints(&pStart,&pEnd);

   // convert them to world space
   map->MPtoWP(pStart,sx,sy);
   map->MPtoWP(pEnd,  ex,ey);
}
