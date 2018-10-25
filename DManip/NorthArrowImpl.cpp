///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// NorthArrowImpl.cpp: implementation of the CNorthArrowImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "NorthArrowImpl.h"
#include "Helpers.h"

#include <MathEx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNorthArrowImpl::CNorthArrowImpl()
{
}

CNorthArrowImpl::~CNorthArrowImpl()
{
}

HRESULT CNorthArrowImpl::FinalConstruct()
{
   m_strText = _T("");
   m_Direction = PI_OVER_2;
   m_Size = 50;

   CFont font;
   font.CreatePointFont(80,_T("Arial"));
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 80;
   m_Font.lfQuality = ANTIALIASED_QUALITY;

   SetDisplayObject(this);

   return S_OK;
}

// iDisplayObject Implementation
// This are the methods not delegated to the implementation object
STDMETHODIMP_(void) CNorthArrowImpl::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDM;
   pDL->GetDisplayMgr(&pDM);

   CDisplayView* pView = pDM->GetView();
//   // For debugging... Draw the gravity well
//   CComPtr<iGravityWellStrategy> strategy;
//   GetGravityWellStrategy(&strategy);
//   CRgn rgn;
//   if ( strategy )
//   {
//      strategy->GetGravityWell(this,&rgn);
//   }
//   else
//   {
//      CRect box = GetBoundingBox();
//      rgn.CreateRectRgnIndirect(&box);
//   }
//   CBrush brush;
//   brush.CreateHatchBrush(HS_DIAGCROSS,RGB(127,127,127));
//   pDC->FillRgn(&rgn,&brush);
//   // End of debug code

   CFont font;
   font.CreatePointFontIndirect(&m_Font, pDC);
   CFont* pOldFont = pDC->SelectObject(&font);

   UINT nFlag = pDC->SetTextAlign(TA_TOP | TA_CENTER);
   CSize extents = pDC->GetTextExtent("North");
   LONG size = 125*extents.cx/100;

   CRect rClient = pView->GetViewRect();

   CPoint tl;
   tl.x = rClient.left;
   tl.y = rClient.top;

   // size of the north arrow box
   CPoint br(tl);
   br += CSize(size,size);

   CRect box(tl,br);

   CPoint center = box.CenterPoint();

   LONG ox = size/2;
   LONG oy = size/2;

   Float64 c = cos(m_Direction);
   Float64 s = sin(m_Direction);

   CPoint p1(center);
   p1.Offset( int(-ox*c), int(oy*s) );

   CPoint p2(center);
   p2.Offset( int(ox*c), int(-oy*s) );

   pDC->MoveTo(p1);
   pDC->LineTo(p2);

   ox /= 2;
   oy /= 2;

   CPoint p3;
   p3.x = p2.x - LONG(  ox*s + oy*c);
   p3.y = p2.y + LONG( -ox*c + oy*s);

   CPoint p4;
   p4.x = p2.x + LONG( ox*s - oy*c);
   p4.y = p2.y + LONG( ox*c + oy*s);

   DrawArrowHead(pDC,DManip::ahsFilled,p3,p2,p4);

//   pDC->LineTo(p3);
//   pDC->LineTo(p4);
//   pDC->LineTo(p2);
   
   pDC->TextOut(box.CenterPoint().x,box.bottom,"North");

   pDC->SelectObject(pOldFont);
   pDC->SetTextAlign(nFlag);
}

STDMETHODIMP_(void) CNorthArrowImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
#pragma Reminder("Clean this up")
   // Draw bold or something
   Draw(pDC);
}

STDMETHODIMP_(CRect) CNorthArrowImpl::GetBoundingBox()
{
   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDM;
   pDL->GetDisplayMgr(&pDM);
   
   CComPtr<iCoordinateMap> pMapper;
   pDM->GetCoordinateMap(&pMapper);

   CDisplayView* pView = pDM->GetView();

   CRect rClient;
   pView->GetClientRect(&rClient);

   CPoint p;
   p.x = rClient.left;
   p.y = rClient.top;

   
   CSize extents(0,0);

   // Find the edges of the text block
   LONG top, left, right, bottom;
   top    = p.y;
   bottom = p.y + extents.cy;
   left   = p.x - extents.cx/2;
   right  = left + extents.cx;
   CRect box(left,top,right,bottom);

   return box;
}

STDMETHODIMP_(void) CNorthArrowImpl::GetBoundingBox(IRect2d** wrect)
{
   CRect box = GetBoundingBox(); // logical coordinates

   // map to world coordinates
   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDM;
   pDL->GetDisplayMgr(&pDM);
   CComPtr<iCoordinateMap> pMapper;
   pDM->GetCoordinateMap(&pMapper);

   Float64 left,right,top,bottom;
   pMapper->LPtoWP(box.left,box.bottom,&left,&bottom);
   pMapper->LPtoWP(box.right,box.top,&right,&top);


   CComPtr<IRect2d> bounding_box;
   bounding_box.CoCreateInstance(CLSID_Rect2d);
   bounding_box->put_Left(left);
   bounding_box->put_Right(right);
   bounding_box->put_Top(top);
   bounding_box->put_Bottom(bottom);

   (*wrect) = bounding_box;
   (*wrect)->AddRef();
}

STDMETHODIMP_(void) CNorthArrowImpl::SetText(LPCTSTR lpszText)
{
   if ( m_strText == CString(lpszText) )
      return;

   m_strText = lpszText;

   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);

   if ( pDL )
   {
      CComPtr<iDisplayMgr> pDispMgr;
      pDL->GetDisplayMgr(&pDispMgr);

      if ( pDispMgr )
      {
         CRect box = GetBoundingBox();
         pDispMgr->InvalidateRect(box);
      }
   }
}

STDMETHODIMP_(CString) CNorthArrowImpl::GetText()
{
   return m_strText;
}

STDMETHODIMP_(void) CNorthArrowImpl::SetFont(const LOGFONT& Font)
{
   m_Font = Font;
}

STDMETHODIMP_(void) CNorthArrowImpl::GetFont(LOGFONT* pFont)
{
   *pFont = m_Font;
}

STDMETHODIMP_(void) CNorthArrowImpl::SetDirection(Float64 angle)
{
   m_Direction = angle;
}

STDMETHODIMP_(Float64) CNorthArrowImpl::GetDirection()
{
   return m_Direction;
}

STDMETHODIMP_(void) CNorthArrowImpl::SetSize(LONG size)
{
   m_Size = size;
}

STDMETHODIMP_(LONG) CNorthArrowImpl::GetSize()
{
   return m_Size;
}
