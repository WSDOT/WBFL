#pragma once

#include "stdafx.h"
#include <DManip/DrawPointStrategy.h>

class iDataPointDrawStrategy : public WBFL::DManip::iDrawPointStrategy
{
public:
   // name of font face for symbol
   // "Symbol" is the default
   virtual std::_tstring GetSymbolFontFace() = 0;
   virtual void SetSymbolFontFace(std::_tstring newVal) = 0;

   // character font size in 1/10 points
   virtual long GetSymbolSize() = 0;
   virtual void SetSymbolSize(long code) = 0;

   // symbol character code (ascii)
   virtual DWORD GetSymbolCharacterCode() = 0;
   virtual void SetSymbolCharacterCode(DWORD code) = 0;

   virtual COLORREF GetColor() = 0;
   virtual void SetColor(COLORREF color) = 0;
};