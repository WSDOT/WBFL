///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// TextBlockImpl.cpp: implementation of the CTextBlockImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "TextBlockImpl.h"

#include <MathEx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextBlockImpl::CTextBlockImpl()
{
}

CTextBlockImpl::~CTextBlockImpl()
{
}

HRESULT CTextBlockImpl::FinalConstruct()
{
   m_TextAlign = TA_TOP | TA_LEFT;
   m_Position.CoCreateInstance(CLSID_Point2d);
   m_strText = "";

   CFont font;
   font.CreatePointFont(80,"Arial");
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 80;
   m_Font.lfQuality = ANTIALIASED_QUALITY;

   m_BkMode = OPAQUE;
   m_FgColor = RGB(0,0,0);
   m_BgColor = RGB(255,255,255);

   SetDisplayObject(this);

   return S_OK;
}

// iDisplayObject Implementation
// This are the methods not delegated to the implementation object
STDMETHODIMP_(void) CTextBlockImpl::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

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

   long lx,ly;
   GetPositionInLogicalSpace(&lx,&ly);


   CFont font;
   CreateFont(font,pDC);
//   font.CreatePointFontIndirect(&m_Font, pDC);
   CFont* pOldFont = pDC->SelectObject(&font);

   UINT nFlag = pDC->SetTextAlign(m_TextAlign);

   CStringArray strArray;
   GetTextLines(strArray);

   int bkMode = pDC->SetBkMode(m_BkMode);
   COLORREF bgColor = pDC->SetBkColor(m_BgColor);
   COLORREF fgColor = pDC->SetTextColor(m_FgColor);

   for ( int i = 0; i < strArray.GetSize(); i++ )
   {
      CString str = strArray.GetAt(i);
      CSize size = pDC->GetOutputTextExtent(str);
      pDC->TextOut(lx,ly,str);
      ly += size.cy;
   }

   pDC->SetBkMode(bkMode);
   pDC->SetBkColor(bgColor);
   pDC->SetTextColor(fgColor);


   pDC->SelectObject(pOldFont);
   pDC->SetTextAlign(nFlag);
}

STDMETHODIMP_(void) CTextBlockImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
#pragma Reminder("Clean this up")
   // Draw bold or something
   Draw(pDC);
}

STDMETHODIMP_(CRect) CTextBlockImpl::GetBoundingBox()
{
   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDM;
   pDL->GetDisplayMgr(&pDM);
   CComPtr<iCoordinateMap> pMapper;
   pDM->GetCoordinateMap(&pMapper);

   long lx,ly;
   GetPositionInLogicalSpace(&lx,&ly);

   CStringArray strArray;
   GetTextLines(strArray);
   
   CSize extents(0,0);
   for ( int i = 0; i < strArray.GetSize(); i++ )
   {
      CString str = strArray.GetAt(i);
      CSize size = pMapper->GetTextExtent(m_Font,str);

      if ( size.cx == 0 || size.cy == 0 )
         size = pMapper->GetTextExtent(m_Font,"ABCDEFG\0");

      // capture the width of the widest line of text
      if ( extents.cx < size.cx )
         extents.cx = size.cx;

      // accumulate the total height of all lines of text
      extents.cy += size.cy;
   }

   // Find the edges of the text block
   long top, left, right, bottom;
   CPoint crotate; // center of rotation
   if ( (m_TextAlign&TA_BOTTOM)==TA_BOTTOM || 
        (m_TextAlign&TA_BASELINE)==TA_BASELINE)
   {
      bottom = ly;
      top    = ly - extents.cy;
      crotate.y = bottom;
   }
   else
   {
      top    = ly;
      bottom = ly + extents.cy;
      crotate.y = top;
   }

   if ( (m_TextAlign&TA_CENTER)==TA_CENTER )
   {
      left  = lx - extents.cx/2;
      right = left + extents.cx;
      crotate.x = (left+right)/2;
   }
   else if ( (m_TextAlign&TA_RIGHT)==TA_RIGHT )
   {
      right = lx;
      left  = lx - extents.cx;
      crotate.x = right;
   }
   else
   {
      left  = lx;
      right = lx + extents.cx;
      crotate.x = left;
   }

   // rotate the 
   CRect box(left,top,right,bottom);
   CPoint tl(box.left,box.top);
   CPoint tr(box.right,box.top);
   CPoint bl(box.left,box.bottom);
   CPoint br(box.right,box.bottom);
   long langle = GetAngle(); // in 10ths of a degree
   Float64 angle = langle*M_PI/1800.;

   Float64 c = cos(angle);
   Float64 s = sin(angle);

   CPoint p1( int((tl.x - crotate.x)*c + (tl.y - crotate.y)*s + crotate.x), int(-(tl.x - crotate.x)*s + (tl.y - crotate.y)*c + crotate.y) );
   CPoint p2( int((tr.x - crotate.x)*c + (tr.y - crotate.y)*s + crotate.x), int(-(tr.x - crotate.x)*s + (tr.y - crotate.y)*c + crotate.y) );
   CPoint p3( int((bl.x - crotate.x)*c + (bl.y - crotate.y)*s + crotate.x), int(-(bl.x - crotate.x)*s + (bl.y - crotate.y)*c + crotate.y) );
   CPoint p4( int((br.x - crotate.x)*c + (br.y - crotate.y)*s + crotate.x), int(-(br.x - crotate.x)*s + (br.y - crotate.y)*c + crotate.y) );

   box.left   = _cpp_min( _cpp_min(p1.x,p2.x), _cpp_min(p3.x,p4.x) );
   box.right  = _cpp_max( _cpp_max(p1.x,p2.x), _cpp_max(p3.x,p4.x) );
   box.bottom = _cpp_max( _cpp_max(p1.y,p2.y), _cpp_max(p3.y,p4.y) );
   box.top    = _cpp_min( _cpp_min(p1.y,p2.y), _cpp_min(p3.y,p4.y) );

   return box;
}

STDMETHODIMP_(void) CTextBlockImpl::GetBoundingBox(IRect2d** wrect)
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

STDMETHODIMP_(void) CTextBlockImpl::SetPosition(IPoint2d* pos)
{
   m_Position->MoveEx(pos);
}

STDMETHODIMP_(void) CTextBlockImpl::GetPosition(IPoint2d** pos)
{
   (*pos) = m_Position;
   (*pos)->AddRef();
}

STDMETHODIMP_(void) CTextBlockImpl::SetTextAlign(UINT nFlags)
{
   m_TextAlign = nFlags;
}

STDMETHODIMP_(UINT) CTextBlockImpl::GetTextAlign()
{
   return m_TextAlign;
}

STDMETHODIMP_(void) CTextBlockImpl::SetAngle(long angle)
{
   m_Font.lfEscapement  = angle;
   m_Font.lfOrientation = angle;
}

STDMETHODIMP_(long) CTextBlockImpl::GetAngle()
{
   return m_Font.lfEscapement;
}

STDMETHODIMP_(void) CTextBlockImpl::SetText(LPCSTR lpszText)
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

STDMETHODIMP_(CString) CTextBlockImpl::GetText()
{
   return m_strText;
}

STDMETHODIMP_(void) CTextBlockImpl::SetFont(const LOGFONT& Font)
{
   m_Font = Font;
}

STDMETHODIMP_(void) CTextBlockImpl::GetFont(LOGFONT* pFont)
{
   *pFont = m_Font;
}

STDMETHODIMP_(void) CTextBlockImpl::SetTextColor(COLORREF color)
{
   m_FgColor = color;
}

STDMETHODIMP_(COLORREF) CTextBlockImpl::GetTextColor()
{
   return m_FgColor;
}

STDMETHODIMP_(void) CTextBlockImpl::SetBkColor(COLORREF color)
{
   m_BgColor = color;
}

STDMETHODIMP_(COLORREF) CTextBlockImpl::GetBkColor()
{
   return m_BgColor;
}

STDMETHODIMP_(void) CTextBlockImpl::SetBkMode(int bkMode)
{
   m_BkMode = bkMode;
}

STDMETHODIMP_(int) CTextBlockImpl::GetBkMode()
{
   return m_BkMode;
}

void CTextBlockImpl::GetTextLines(CStringArray& strArray)
{
   // deal with multiline text because TextOut doesn't know what to do with "\n"
   CString strText = GetText();

   int position = 0;
   int length = strText.GetLength();
   while ( true )
   {
      int next_position = strText.Find("\n",position);
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

void CTextBlockImpl::GetPositionInWorldSpace(Float64* wx,Float64* wy)
{
   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDM;
   pDL->GetDisplayMgr(&pDM);
 
   CComPtr<iCoordinateMap> pMapper;
   pDM->GetCoordinateMap(&pMapper);

   pMapper->MPtoWP(m_Position,wx,wy);
}

void CTextBlockImpl::GetPositionInLogicalSpace(long* lx,long* ly)
{
   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDM;
   pDL->GetDisplayMgr(&pDM);
 
   CComPtr<iCoordinateMap> pMapper;
   pDM->GetCoordinateMap(&pMapper);

   Float64 wx,wy;
   pMapper->MPtoWP(m_Position,&wx,&wy);
   pMapper->WPtoLP(wx,wy,lx,ly);
}

void CTextBlockImpl::CreateFont(CFont& font,CDC* pDC)
{
   // this font accounts for the rotation between Model and World space

   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDM;
   pDL->GetDisplayMgr(&pDM);
 
   CComPtr<iCoordinateMap> pMapper;
   pDM->GetCoordinateMap(&pMapper);

   CComQIPtr<iMapping> mapping(pMapper);
   Float64 cx,cy,angle;
   mapping->GetRotation(&cx,&cy,&angle);

   angle *= 1800/M_PI; // convert to angle degrees (in 10ths of a degree)

   LOGFONT lfFont = m_Font;
   long text_angle = lfFont.lfEscapement;

   text_angle += (long)angle;

   text_angle = (900 < text_angle  && text_angle  < 2700 ) ? text_angle-1800  : text_angle;

   if ( -2700 <= text_angle && text_angle <= -900 )
      text_angle += 1800;

   lfFont.lfEscapement  = text_angle;
   lfFont.lfOrientation = text_angle;


   font.CreatePointFontIndirect(&lfFont, pDC);
}