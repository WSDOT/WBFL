///////////////////////////////////////////////////////////////////////////////
// generic support draw routines to share between Supports and TemporarySupports

#include "stdafx.h"
#include "DataPointDrawStrategyImpl.h"


// default symbol size in twips
static const long SSIZE = 1440 * 3 / 32;

CDataPointDrawStrategyImpl::CDataPointDrawStrategyImpl() :
   m_Color(RGB(200, 0, 0)),
   m_FontFace(_T("Symbol")),
   m_FontSize(80),
   m_CharCode(0)
{
}

CDataPointDrawStrategyImpl::~CDataPointDrawStrategyImpl()
{
}

std::_tstring CDataPointDrawStrategyImpl::GetSymbolFontFace()
{
   return m_FontFace;
}

void CDataPointDrawStrategyImpl::SetSymbolFontFace(std::_tstring newVal)
{
   m_FontFace = newVal;
}

long CDataPointDrawStrategyImpl::GetSymbolSize()
{
   return m_FontSize;
}

void CDataPointDrawStrategyImpl::SetSymbolSize(long size)
{
   CHECK(20 <= size); // are you sure you want smaller than a two point font?
   m_FontSize = size;
}

DWORD CDataPointDrawStrategyImpl::GetSymbolCharacterCode()
{
   return m_CharCode;
}

void CDataPointDrawStrategyImpl::SetSymbolCharacterCode(DWORD code)
{
   m_CharCode = code;
}

COLORREF CDataPointDrawStrategyImpl::GetColor()
{
   return m_Color;
}

void CDataPointDrawStrategyImpl::SetColor(COLORREF color)
{
   m_Color = color;
}

void CDataPointDrawStrategyImpl::Draw(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC) const
{
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();

   COLORREF color;

   if (pDO->IsSelected())
      color = pDispMgr->GetSelectionLineColor();
   else
      color = m_Color;

   auto pos = pDO->GetPosition();

   Draw(pDO, pDC, color, pos);
}

void CDataPointDrawStrategyImpl::DrawHighlight(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC, bool bHighlite) const 
{
   Draw(pDO, pDC);
}

void CDataPointDrawStrategyImpl::DrawDragImage(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC, std::shared_ptr<const WBFL::DManip::iCoordinateMap> map, const POINT& dragStart, const POINT& cpdragPoint) const
{
   auto dragPoint = map->LPtoWP(cpdragPoint.x, cpdragPoint.y);
   Draw(pDO, pDC, RGB(255, 0, 0), dragPoint);
}

WBFL::Geometry::Rect2d CDataPointDrawStrategyImpl::GetBoundingBox(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO) const
{
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();
   auto pMap = pDispMgr->GetCoordinateMap();

   // height of cut above/below girder
   Float64 xo, yo;
   pMap->TPtoWP(0, 0, &xo, &yo);
   Float64 x2, y2;
   pMap->TPtoWP(SSIZE, SSIZE, &x2, &y2);

   Float64 width = (x2 - xo) / 2.0;
   Float64 height = (y2 - yo) / 2.0;

   auto point = pDO->GetPosition();
   auto [xp, yp] = point.GetLocation();

   return WBFL::Geometry::Rect2d(xp - width, yp - height, xp + width, yp + height);
}

void CDataPointDrawStrategyImpl::Draw(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC, COLORREF color, const WBFL::Geometry::Point2d& loc) const
{
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();
   auto pMap = pDispMgr->GetCoordinateMap();

   long cx, cy;
   pMap->WPtoLP(loc, &cx, &cy);

   if (m_CharCode == 0)
   {
      // draw nothing
   }
   else
   {
      COLORREF old_col = pDC->SetTextColor(m_Color);

      CFont font;
      font.CreatePointFont(m_FontSize, m_FontFace.c_str(), pDC);
      CFont* old_font = pDC->SelectObject(&font);

      CRect rect(0, 0, 0, 0);
      pDC->DrawText((LPCTSTR)&m_CharCode, 1, &rect, DT_CALCRECT);
      long wid2 = rect.Width() / 2;
      long hgt2 = rect.Height() / 2;

      CRect newrect(cx - wid2, cy - hgt2, cx + wid2, cy + hgt2);
      pDC->DrawText((LPCTSTR)&m_CharCode, 1, &newrect, DT_CENTER | DT_VCENTER | DT_NOCLIP);

      pDC->SelectObject(old_font);
      pDC->SetTextColor(old_col);
   }
}
