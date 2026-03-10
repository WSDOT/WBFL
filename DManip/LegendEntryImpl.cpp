///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include "pch.h"
#include <DManip/LegendEntryImpl.h>

using namespace WBFL::DManip;

std::_tstring LegendEntry::GetName() const
{
	return m_Name;
}

void LegendEntry::SetName(LPCTSTR lpszName)
{
	m_Name = lpszName;
}

std::_tstring LegendEntry::GetSymbolFontFace() const
{
   return m_FontFace;
}

void LegendEntry::SetSymbolFontFace(LPCTSTR newVal)
{
   m_FontFace = newVal;
}

long LegendEntry::GetSymbolSize() const
{
   return m_FontSize;
}

void LegendEntry::SetSymbolSize(long size)
{
   CHECK(20 < size); // are you sure you want smaller than a two point font?
   m_FontSize = size;
}

DWORD LegendEntry::GetSymbolCharacterCode() const
{
   return m_CharCode;
}

void LegendEntry::SetSymbolCharacterCode(DWORD code)
{
   m_CharCode = code;
}

COLORREF LegendEntry::GetColor() const
{
   return m_Color;
}

void LegendEntry::SetColor(COLORREF color)
{
   m_Color = color;
}

bool LegendEntry::DrawLine() const
{
   return m_bDrawLine;
}

void LegendEntry::DrawLine(bool bDraw)
{
   m_bDrawLine = bDraw;
}

void LegendEntry::Draw(CDC *pDC, const RECT& drawRect, bool beingDragged) const
{
	if (m_CharCode==0 && !m_bDrawLine)
   {
      // fill rect solid
      CBrush brush(m_Color);
      CPen back_pen(PS_SOLID, 1, m_Color);
      CBrush* pold_brush = pDC->SelectObject(&brush);
      CPen* pold_pen = pDC->SelectObject(&back_pen);

      pDC->Rectangle(&drawRect);

      pDC->SelectObject(&pold_brush);
      pDC->SelectObject(&pold_pen);
   }
   else
   {
      long midy =(drawRect.top + drawRect.bottom)/2;

      if (m_bDrawLine)
      {
         CPen pen(PS_SOLID, 3, m_Color);
         CPen* old_pen = pDC->SelectObject(&pen);

         pDC->MoveTo(drawRect.left, midy);
         pDC->LineTo(drawRect.right, midy);

         pDC->SelectObject(old_pen);
      }

      if (!beingDragged && m_CharCode!=0)
      {
         COLORREF old_col = pDC->SetTextColor(m_Color);
         CFont font;
         font.CreatePointFont(m_FontSize, m_FontFace.c_str(), pDC);
         CFont* old_font = pDC->SelectObject(&font);

         CRect rect(0,0,0,0);
         pDC->DrawText( (LPCTSTR)&m_CharCode, 1, &rect, DT_CALCRECT);
         long hgt2 = 1 + rect.Height()/2;

         long midx = (drawRect.left+drawRect.right)/2;

         UINT old_align = pDC->SetTextAlign(TA_CENTER|TA_TOP);
         pDC->TextOut(midx, midy-hgt2, (LPCTSTR)&m_CharCode, 1);

         pDC->SetTextAlign(old_align);
         pDC->SelectObject(old_font);
         pDC->SetTextColor(old_col);
      }
   }
}

void LegendEntry::WriteDragData(std::shared_ptr<iDragDataSink> pSink, UINT cfFormat)
{
   // name
   long len = (long)m_Name.length();
   pSink->Write(cfFormat,&len,sizeof(long));
   if (0 < len)
   {
      auto tstr = m_Name.c_str();
      pSink->Write(cfFormat,(void*)tstr,len*sizeof(wchar_t)); // string data
   }

   // font face
   len = (long)m_FontFace.length();
   pSink->Write(cfFormat,&len,sizeof(long));
   pSink->Write(cfFormat,(void*)LPCTSTR(m_FontFace.c_str()),len*sizeof(TCHAR));
  
   pSink->Write(cfFormat,&m_FontSize,sizeof(long));
   pSink->Write(cfFormat,&m_CharCode,sizeof(DWORD));
   pSink->Write(cfFormat,&m_Color,sizeof(COLORREF));
   pSink->Write(cfFormat,&m_bDrawLine,sizeof(BOOL));
}

void LegendEntry::ReadDragData(std::shared_ptr<iDragDataSource> pSource, UINT cfFormat)
{
   long len;
   // name
   pSource->Read(cfFormat,&len,sizeof(long));
   wchar_t* wstr = new wchar_t[len+1];

   if (len>0)
      pSource->Read(cfFormat,wstr,len*sizeof(wchar_t)); 

   wstr[len] = _T('\0');
   m_Name = wstr;

   delete[] wstr;

   // font face
   pSource->Read(cfFormat,&len,sizeof(long));
   TCHAR* tstr = new TCHAR[len+1];

   if (len>0)
      pSource->Read(cfFormat,tstr,len*sizeof(TCHAR)); 

   tstr[len] = _T('\0');
   m_FontFace = tstr;

   delete[] tstr;
  
   pSource->Read(cfFormat,&m_FontSize,sizeof(long));
   pSource->Read(cfFormat,&m_CharCode,sizeof(DWORD));
   pSource->Read(cfFormat,&m_Color,sizeof(COLORREF));
   pSource->Read(cfFormat,&m_bDrawLine,sizeof(BOOL));
}
