///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

// AnchoredTextBlockImpl.cpp: implementation of the CAnchoredTextBlockImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "AnchoredTextBlockImpl.h"

#include <MathEx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnchoredTextBlockImpl::CAnchoredTextBlockImpl()
{
}

CAnchoredTextBlockImpl::~CAnchoredTextBlockImpl()
{
}

HRESULT CAnchoredTextBlockImpl::FinalConstruct()
{
   m_strText = "";
   m_Location.x = 0;
   m_Location.y = 0;

   CFont font;
   font.CreatePointFont(80,_T("Arial"));
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 80;
   m_Font.lfQuality = ANTIALIASED_QUALITY;

   SetDisplayObject(this);

   return S_OK;
}

void CAnchoredTextBlockImpl::FinalRelease()
{
   CDisplayObjectDefaultImpl::Do_FinalRelease();
}

// iDisplayObject Implementation
// This are the methods not delegated to the implementation object
STDMETHODIMP_(void) CAnchoredTextBlockImpl::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDM;
   pDL->GetDisplayMgr(&pDM);

   CDisplayView* pView = pDM->GetView();
   CRect rClient = pView->GetViewRect();
   CPoint topLeft = rClient.TopLeft();

   LOGFONT lf = m_Font;
   pView->ScaleFont(lf);

   CFont font;
   font.CreatePointFontIndirect(&lf, pDC);
   CFont* pOldFont = pDC->SelectObject(&font);

   UINT nFlag = pDC->SetTextAlign(TA_TOP | TA_LEFT);

   CStringArray strArray;
   GetTextLines(strArray);

   CPoint p(m_Location);
   for ( INT_PTR i = 0; i < strArray.GetSize(); i++ )
   {
      CString str = strArray.GetAt(i);
      CSize size = pDC->GetOutputTextExtent(str);
      pDC->TextOut(topLeft.x + p.x,topLeft.y + p.y,str);
      p.y += size.cy;
   }


   pDC->SelectObject(pOldFont);
   pDC->SetTextAlign(nFlag);
}

STDMETHODIMP_(void) CAnchoredTextBlockImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
#pragma Reminder("Clean this up")
   // Draw bold or something
   Draw(pDC);
}

STDMETHODIMP_(CRect) CAnchoredTextBlockImpl::GetBoundingBox()
{
   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDM;
   pDL->GetDisplayMgr(&pDM);
   
   CComPtr<iCoordinateMap> pMapper;
   pDM->GetCoordinateMap(&pMapper);

   CDisplayView* pView = pDM->GetView();

   CStringArray strArray;
   GetTextLines(strArray);
   
   CSize extents(0,0);
   for ( int i = 0; i < strArray.GetSize(); i++ )
   {
      CString str = strArray.GetAt(i);
      CSize size = pMapper->GetTextExtent(pView,m_Font,str);

      if ( size.cx == 0 || size.cy == 0 )
         size = pMapper->GetTextExtent(pView,m_Font,_T("ABCDEFG\0"));

      // capture the width of the widest line of text
      if ( extents.cx < size.cx )
         extents.cx = size.cx;

      // accumulate the total height of all lines of text
      extents.cy += size.cy;
   }

   CRect rClient = pView->GetViewRect();
   CPoint topLeft = rClient.TopLeft();

   // Find the edges of the text block
   int top, left, right, bottom;
   top    = topLeft.y + m_Location.y;
   bottom = top + extents.cy;
   left   = topLeft.x + m_Location.x;
   right  = left + extents.cx;
   CRect box(left,top,right,bottom);

   return box;
}

STDMETHODIMP_(void) CAnchoredTextBlockImpl::GetBoundingBox(IRect2d** wrect)
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

STDMETHODIMP_(void) CAnchoredTextBlockImpl::SetLocation(const POINT& point)
{
   m_Location = point;
}

STDMETHODIMP_(POINT) CAnchoredTextBlockImpl::GetLocation() const
{
   return m_Location;
}

STDMETHODIMP_(void) CAnchoredTextBlockImpl::SetText(LPCTSTR lpszText)
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

STDMETHODIMP_(CString) CAnchoredTextBlockImpl::GetText()
{
   return m_strText;
}

STDMETHODIMP_(void) CAnchoredTextBlockImpl::SetFont(const LOGFONT& Font)
{
   m_Font = Font;
}

STDMETHODIMP_(void) CAnchoredTextBlockImpl::GetFont(LOGFONT* pFont)
{
   *pFont = m_Font;
}


void CAnchoredTextBlockImpl::GetTextLines(CStringArray& strArray)
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
