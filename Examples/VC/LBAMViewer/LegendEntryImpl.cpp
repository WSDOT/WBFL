///////////////////////////////////////////////////////////////////////////////
// generic support draw routines to share between Supports and TemporarySupports

#include "stdafx.h"
#include "LegendEntryImpl.h"

#include "DataPointDrawStrategyImpl.h"
#include "DataPointEventsImpl.h"

CLegendEntryImpl::CLegendEntryImpl() :
   m_FontFace(_T("Symbol")),
   m_FontSize(120),
   m_CharCode(0),
   m_Color(RGB(200, 0, 0)),
   m_DoDrawLine(FALSE)
{
}

void CLegendEntryImpl::SetName(std::_tstring newVal)
{
   m_Name = newVal;
}

std::_tstring CLegendEntryImpl::GetSymbolFontFace()
{
   return m_FontFace;
}

void CLegendEntryImpl::SetSymbolFontFace(LPCTSTR  newVal)
{
   m_FontFace = newVal;
}

long CLegendEntryImpl::GetSymbolSize()
{
   return m_FontSize;
}

void CLegendEntryImpl::SetSymbolSize(long size)
{
   CHECK(20 <= size); // are you sure you want smaller than a two point font?
   m_FontSize = size;
}

DWORD CLegendEntryImpl::GetSymbolCharacterCode()
{
   return m_CharCode;
}

void CLegendEntryImpl::SetSymbolCharacterCode(DWORD code)
{
   m_CharCode = code;
}

COLORREF CLegendEntryImpl::GetColor()
{
   return m_Color;
}

void CLegendEntryImpl::SetColor(COLORREF color)
{
   m_Color = color;
}

BOOL CLegendEntryImpl::DoDrawLine()
{
   return m_DoDrawLine;
}

void CLegendEntryImpl::DoDrawLine(BOOL doDraw)
{
   m_DoDrawLine = doDraw;
}


//void CLegendEntryImpl::Draw(CDC* pDC, CRect& drawRect, BOOL beingDragged)
//{
//   if (m_CharCode == 0 && !m_DoDrawLine)
//   {
//      // fill rect solid
//      CBrush brush(m_Color);
//      CPen back_pen(PS_SOLID, 1, m_Color);
//      CBrush* pold_brush = pDC->SelectObject(&brush);
//      CPen* pold_pen = pDC->SelectObject(&back_pen);
//
//      pDC->Rectangle(drawRect);
//
//      pDC->SelectObject(&pold_brush);
//      pDC->SelectObject(&pold_pen);
//   }
//   else
//   {
//      long midy = (drawRect.top + drawRect.bottom) / 2;
//
//      if (m_DoDrawLine)
//      {
//         CPen pen(PS_SOLID, 3, m_Color);
//         CPen* old_pen = pDC->SelectObject(&pen);
//
//         pDC->MoveTo(drawRect.left, midy);
//         pDC->LineTo(drawRect.right, midy);
//
//         pDC->SelectObject(old_pen);
//      }
//
//      if (!beingDragged && m_CharCode != 0)
//      {
//         COLORREF old_col = pDC->SetTextColor(m_Color);
//         CFont font;
//         font.CreatePointFont(m_FontSize, m_FontFace.c_str(), pDC);
//         CFont* old_font = pDC->SelectObject(&font);
//
//         CRect rect(0, 0, 0, 0);
//         pDC->DrawText((LPCTSTR)&m_CharCode, 1, &rect, DT_CALCRECT);
//         long hgt2 = 1 + rect.Height() / 2;
//
//         long midx = (drawRect.left + drawRect.right) / 2;
//
//         UINT old_align = pDC->SetTextAlign(TA_CENTER | TA_TOP);
//         pDC->TextOut(midx, midy - hgt2, (LPCTSTR)&m_CharCode, 1);
//
//         pDC->SetTextAlign(old_align);
//         pDC->SelectObject(old_font);
//         pDC->SetTextColor(old_col);
//      }
//   }
//}

std::shared_ptr<WBFL::DManip::iDisplayObject> CLegendEntryImpl::CreateDataPoint(Float64 dataX, Float64 dataY, Float64 graphX, Float64 graphY)
{
   WBFL::Geometry::Point2d mpnt(graphX, graphY);

   // data point
   auto dp_rep = WBFL::DManip::PointDisplayObject::Create();

   auto pDisplayImpl = std::make_shared<CDataPointDrawStrategyImpl>();
   dp_rep->SetDrawingStrategy(pDisplayImpl);

   dp_rep->SetPosition(mpnt, FALSE, FALSE);

   auto pEvents = std::make_shared<CDataPointEventsImpl>();
   dp_rep->RegisterEventSink(pEvents);

   pDisplayImpl->SetColor(m_Color);
   pDisplayImpl->SetSymbolCharacterCode(m_CharCode);
   pDisplayImpl->SetSymbolSize(m_FontSize);
   pDisplayImpl->SetSymbolFontFace(m_FontFace);

   auto dp_connectable = std::dynamic_pointer_cast<WBFL::DManip::iConnectable>(dp_rep);
   auto socket = dp_connectable->AddSocket(0, mpnt);

   // tool tips
   CString strToolTipText;
   strToolTipText.Format(_T("(%f, %f)"), dataX, dataY);
   dp_rep->SetToolTipText(strToolTipText);

   return dp_rep;
}

//void CLegendEntryImpl::WriteDragData(std::shared_ptr<WBFL::DManip::iDragDataSink> pSink, UINT cfFormat)
//{
//   // name
//   long len = m_Name.size();
//   pSink->Write(cfFormat, &len, sizeof(long));
//   if (len > 0)
//   {
//      pSink->Write(cfFormat, (void*)m_Name.c_str(), len * sizeof(TCHAR)); // string data
//   }
//
//   // font face
//   len = m_FontFace.size();
//   pSink->Write(cfFormat, &len, sizeof(long));
//   pSink->Write(cfFormat, (void*)m_FontFace.c_str(), len * sizeof(TCHAR));
//
//   pSink->Write(cfFormat, &m_FontSize, sizeof(long));
//   pSink->Write(cfFormat, &m_CharCode, sizeof(DWORD));
//   pSink->Write(cfFormat, &m_Color, sizeof(COLORREF));
//   pSink->Write(cfFormat, &m_DoDrawLine, sizeof(BOOL));
//}
//
//void CLegendEntryImpl::ReadDragData(std::shared_ptr<WBFL::DManip::iDragDataSource> pSource, UINT cfFormat)
//{
//   long len;
//   // name
//   pSource->Read(cfFormat, &len, sizeof(long));
//   wchar_t* wstr = new wchar_t[len + 1];
//
//   if (len > 0)
//      pSource->Read(cfFormat, wstr, len * sizeof(wchar_t));
//
//   wstr[len] = _T('\0');
//   m_Name = wstr;
//
//   delete[] wstr;
//
//   // font face
//   pSource->Read(cfFormat, &len, sizeof(long));
//   TCHAR* tstr = new TCHAR[len + 1];
//
//   if (len > 0)
//      pSource->Read(cfFormat, tstr, len * sizeof(TCHAR));
//
//   tstr[len] = _T('\0');
//   m_FontFace = tstr;
//
//   delete[] tstr;
//
//   pSource->Read(cfFormat, &m_FontSize, sizeof(long));
//   pSource->Read(cfFormat, &m_CharCode, sizeof(DWORD));
//   pSource->Read(cfFormat, &m_Color, sizeof(COLORREF));
//   pSource->Read(cfFormat, &m_DoDrawLine, sizeof(BOOL));
//}
