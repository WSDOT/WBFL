///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// ViewTitleImpl.cpp: implementation of the CViewTitleImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "ViewTitleImpl.h"

#include <MathEx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CViewTitleImpl::CViewTitleImpl()
{
}

CViewTitleImpl::~CViewTitleImpl()
{
}

HRESULT CViewTitleImpl::FinalConstruct()
{
   m_strText = "";

   CFont font;
   font.CreatePointFont(120,_T("Arial"));
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 120;
   m_Font.lfQuality = ANTIALIASED_QUALITY;

   SetDisplayObject(this);

   return S_OK;
}

// iDisplayObject Implementation
// This are the methods not delegated to the implementation object
STDMETHODIMP_(void) CViewTitleImpl::Draw(CDC* pDC)
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

   CRect rClient = pView->GetViewRect();

   CPoint p;
   p.x = rClient.CenterPoint().x;
   p.y = rClient.top;

   CFont font;
   font.CreatePointFontIndirect(&m_Font, pDC);
   CFont* pOldFont = pDC->SelectObject(&font);

   UINT nFlag = pDC->SetTextAlign(TA_TOP | TA_CENTER);

   CStringArray strArray;
   GetTextLines(strArray);

   for ( INT_PTR i = strArray.GetSize()-1; 0 <= i; i-- )
   {
      CString str = strArray.GetAt(i);
      CSize size = pDC->GetOutputTextExtent(str);
      pDC->TextOut(p.x,p.y,str);
      p.y -= size.cy;
   }


   pDC->SelectObject(pOldFont);
   pDC->SetTextAlign(nFlag);
}

STDMETHODIMP_(void) CViewTitleImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
#pragma Reminder("Clean this up")
   // Draw bold or something
   Draw(pDC);
}

STDMETHODIMP_(CRect) CViewTitleImpl::GetBoundingBox()
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
   p.x = rClient.CenterPoint().x;
   p.y = rClient.top;

   CStringArray strArray;
   GetTextLines(strArray);
   
   CSize extents(0,0);
   for ( int i = 0; i < strArray.GetSize(); i++ )
   {
      CString str = strArray.GetAt(i);
      CSize size = pMapper->GetTextExtent(m_Font,str);

      if ( size.cx == 0 || size.cy == 0 )
         size = pMapper->GetTextExtent(m_Font,_T("ABCDEFG\0"));

      // capture the width of the widest line of text
      if ( extents.cx < size.cx )
         extents.cx = size.cx;

      // accumulate the total height of all lines of text
      extents.cy += size.cy;
   }

   // Find the edges of the text block
   int top, left, right, bottom;
   top    = p.y;
   bottom = p.y + extents.cy;
   left   = p.x - extents.cx/2;
   right  = left + extents.cx;
   CRect box(left,top,right,bottom);

   return box;
}

STDMETHODIMP_(void) CViewTitleImpl::GetBoundingBox(IRect2d** wrect)
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

STDMETHODIMP_(void) CViewTitleImpl::SetText(LPCTSTR lpszText)
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

STDMETHODIMP_(CString) CViewTitleImpl::GetText()
{
   return m_strText;
}

STDMETHODIMP_(void) CViewTitleImpl::SetFont(const LOGFONT& Font)
{
   m_Font = Font;
}

STDMETHODIMP_(void) CViewTitleImpl::GetFont(LOGFONT* pFont)
{
   *pFont = m_Font;
}


void CViewTitleImpl::GetTextLines(CStringArray& strArray)
{
   // deal with multiline text because TextOut doesn't know what to do with "\n"
   CString strText = GetText();

   int position = 0;
   int length = strText.GetLength();
   while ( true )
   {
      int next_position = strText.Find(_T("\n"),position);
      if ( next_position == -1 )
      {
         strArray.Add(strText.Mid(position));
         break;
      }
      else
      {
         strArray.Add(strText.Mid(position,next_position-position));
         position = next_position+1;
      }
   }
}
