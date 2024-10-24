#pragma once

#include "Legend.h"
#include "GraphXYDisplayObject.h"

class CLegendEntryImpl :
   public iSymbolLegendEntry,
   public iDataPointFactory
{
public:
   CLegendEntryImpl();

   // iSymbolLegendEntry 
   void SetName(std::_tstring name) override;
   std::_tstring GetSymbolFontFace() override;
   void SetSymbolFontFace(LPCTSTR newVal) override;
   long GetSymbolSize() override;
   void SetSymbolSize(long code) override;
   DWORD GetSymbolCharacterCode() override;
   void SetSymbolCharacterCode(DWORD code) override;
   COLORREF GetColor() override;
   void SetColor(COLORREF color) override;
   BOOL DoDrawLine() override;
   void DoDrawLine(BOOL doDraw) override;

   // iDataPointFactory
   std::shared_ptr<WBFL::DManip::iDisplayObject> CreateDataPoint(Float64 dataX, Float64 dataY, Float64 graphX, Float64 graphY) override;

private:
   std::_tstring m_Name;
   std::_tstring m_FontFace;
   long     m_FontSize;
   DWORD    m_CharCode;
   COLORREF m_Color;
   BOOL     m_DoDrawLine;
};
