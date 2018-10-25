///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

// SimpleDrawDashedLineStrategyImpl.cpp: implementation of the CSimpleDrawDashedLineStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "SimpleDrawDashedLineStrategyImpl.h"
#include <Colors.h>
#include <MathEx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimpleDrawDashedLineStrategyImpl::CSimpleDrawDashedLineStrategyImpl()
{
}

CSimpleDrawDashedLineStrategyImpl::~CSimpleDrawDashedLineStrategyImpl()
{
}

HRESULT CSimpleDrawDashedLineStrategyImpl::FinalConstruct()
{
   m_nWidth = 1;
   m_crColor1 = BLACK;
   m_crColor2 = WHITE;

   m_dwDash = 0;

   return S_OK;
}

/////////////////////////////////////////////////////////
// iLineDrawStrategy Implementation

STDMETHODIMP_(void) CSimpleDrawDashedLineStrategyImpl::Draw(iLineDisplayObject* pDO,CDC* pDC)
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

   // Draw the dash color as a solid background line
   CPen bkPen(PS_SOLID,1,m_crColor2);
   CPen* oldPen = pDC->SelectObject(&bkPen);
   pDC->MoveTo(start);
   pDC->LineTo(end);

   // Setup the dash patter
   DWORD dashStyle[3];
   dashStyle[0] = m_dwDash;
   dashStyle[1] = m_dwDash;
   dashStyle[2] = m_dwDash;

   // Draw the primary color as a dashed line
   LOGBRUSH lb;
   lb.lbStyle = BS_SOLID;
   lb.lbColor = m_crColor1;
   lb.lbHatch = 0;
   CPen fgPen(PS_USERSTYLE | PS_GEOMETRIC,m_nWidth,&lb,sizeof(dashStyle)/sizeof(DWORD),dashStyle);

   pDC->SelectObject(&fgPen);

   // Draw the main line
   pDC->MoveTo(start);
   pDC->LineTo(end);

   // Cleanup
   pDC->SelectObject(oldPen);
}

STDMETHODIMP_(void) CSimpleDrawDashedLineStrategyImpl::DrawDragImage(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
}

STDMETHODIMP_(void) CSimpleDrawDashedLineStrategyImpl::DrawHighlite(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
}

STDMETHODIMP_(void) CSimpleDrawDashedLineStrategyImpl::GetBoundingBox(iLineDisplayObject* pDO,IRect2d** box)
{
   // the end points of this line are in Model Space
   // the need to be converted to World Space for the bounding box
   Float64 sx,sy, ex,ey;
   GetPointsInWorldSpace(pDO,&sx,&sy,&ex,&ey);

   CComPtr<IRect2d> rect;
   rect.CoCreateInstance(CLSID_Rect2d);

   rect->put_Left(Min(sx, ex));
   rect->put_Bottom(Min(sy, ey));
   rect->put_Right(Max(sx, ex));
   rect->put_Top(Max(sy, ey));

   (*box) = rect;
   (*box)->AddRef();
}

/////////////////////////////////////////////////////////
// iSimpleLineDashedDrawStrategy Implementation
STDMETHODIMP_(void) CSimpleDrawDashedLineStrategyImpl::SetWidth(UINT nWidth)
{
   m_nWidth = nWidth;
}

STDMETHODIMP_(UINT) CSimpleDrawDashedLineStrategyImpl::GetWidth()
{
   return m_nWidth;
}

STDMETHODIMP_(void) CSimpleDrawDashedLineStrategyImpl::SetColor1(COLORREF crColor)
{
   m_crColor1 = crColor;
}

STDMETHODIMP_(COLORREF) CSimpleDrawDashedLineStrategyImpl::GetColor1()
{
   return m_crColor1;
}

STDMETHODIMP_(void) CSimpleDrawDashedLineStrategyImpl::SetColor2(COLORREF crColor)
{
   m_crColor2 = crColor;
}

STDMETHODIMP_(COLORREF) CSimpleDrawDashedLineStrategyImpl::GetColor2()
{
   return m_crColor2;
}

STDMETHODIMP_(void) CSimpleDrawDashedLineStrategyImpl::SetDashLength(DWORD dwDash)
{
   m_dwDash = dwDash;
}

STDMETHODIMP_(DWORD) CSimpleDrawDashedLineStrategyImpl::GetDashLength()
{
   return m_dwDash;
}

/////////////////////////////////

void CSimpleDrawDashedLineStrategyImpl::GetStartPoint(iLineDisplayObject* pDO,IPoint2d* *point)
{
   CComQIPtr<iConnector,&IID_iConnector> connector(pDO);

   CComPtr<iPlug> plug;
   connector->GetStartPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}

void CSimpleDrawDashedLineStrategyImpl::GetEndPoint(iLineDisplayObject* pDO,IPoint2d* *point)
{
   CComQIPtr<iConnector,&IID_iConnector> connector(pDO);

   CComPtr<iPlug> plug;
   connector->GetEndPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}

void CSimpleDrawDashedLineStrategyImpl::GetPointsInWorldSpace(iLineDisplayObject* pDO,Float64* sx,Float64* sy,Float64* ex,Float64* ey)
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
