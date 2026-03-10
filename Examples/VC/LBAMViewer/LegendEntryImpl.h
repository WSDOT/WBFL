#pragma once

#include "Legend.h"
#include "GraphXYDisplayObject.h"

class CLegendEntryImpl :
   public WBFL::DManip::iLegendEntry,
   public iDataPointFactory
{
public:
   CLegendEntryImpl();

   // iLegendEntry 
   void SetName(LPCTSTR lpszName) override;
   std::_tstring GetName() const override;
   std::_tstring GetSymbolFontFace() const override;
   void SetSymbolFontFace(LPCTSTR newVal) override;
   long GetSymbolSize() const override;
   void SetSymbolSize(long code) override;
   DWORD GetSymbolCharacterCode() const override;
   void SetSymbolCharacterCode(DWORD code) override;
   COLORREF GetColor() const override;
   void SetColor(COLORREF color) override;
   bool DrawLine() const override;
   void DrawLine(bool bDraw) override;

   void Draw(CDC* pDC, const RECT& drawRect, bool beingDrabbed) const override;
  
   void WriteDragData(std::shared_ptr<WBFL::DManip::iDragDataSink> pSink, UINT cfFormat) override;
   void ReadDragData(std::shared_ptr<WBFL::DManip::iDragDataSource> pSource, UINT cfFormat) override;

   // iDataPointFactory
   std::shared_ptr<WBFL::DManip::iDisplayObject> CreateDataPoint(Float64 dataX, Float64 dataY, Float64 graphX, Float64 graphY) override;
   COLORREF GetColor() override;

private:
   std::_tstring m_Name;
   std::_tstring m_FontFace;
   long     m_FontSize;
   DWORD    m_CharCode;
   COLORREF m_Color;
   bool     m_DoDrawLine;
};
