#pragma once

#include "DataPointDrawStrategy.h"

class CDataPointDrawStrategyImpl : public iDataPointDrawStrategy
{
public:
   CDataPointDrawStrategyImpl();
   ~CDataPointDrawStrategyImpl();

   std::_tstring GetSymbolFontFace() override;
   void SetSymbolFontFace(std::_tstring newVal) override;
   long GetSymbolSize() override;
   void SetSymbolSize(long code) override;
   DWORD GetSymbolCharacterCode() override;
   void SetSymbolCharacterCode(DWORD code) override;
   COLORREF GetColor() override;
   void SetColor(COLORREF color) override;

   void Draw(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC) const override;
   void DrawHighlight(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC, bool bHighlight) const override;
   void DrawDragImage(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC, std::shared_ptr<const WBFL::DManip::iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const override;
   WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO) const override;

private:
   void Draw(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC, COLORREF color, const WBFL::Geometry::Point2d& loc) const;

   std::_tstring  m_FontFace;
   long     m_FontSize;
   DWORD    m_CharCode;
   COLORREF m_Color;
};