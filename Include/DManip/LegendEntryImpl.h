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

#pragma once

#include <DManip/Legend.h>
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief An entry in a legend
      class DMANIPCLASS LegendEntry : public iLegendEntry
      {
      protected:
         LegendEntry() = default;

      public:
         static std::shared_ptr<LegendEntry> Create() { return std::shared_ptr<LegendEntry>(new LegendEntry()); }

      // iLegendEntry
      public:
         virtual void SetName(LPCTSTR lpszName) override;
         virtual std::_tstring GetName() const override;

         virtual void Draw(CDC* pDC, const RECT& drawRect, bool beingDrabbed) const override;
         virtual void WriteDragData(std::shared_ptr<iDragDataSink> pSink, UINT cfFormat) override;
         virtual void ReadDragData(std::shared_ptr<iDragDataSource> pSource, UINT cfFormat) override;

         virtual std::_tstring GetSymbolFontFace() const override;
         virtual void SetSymbolFontFace(LPCTSTR newVal) override;
         virtual long GetSymbolSize() const override;
         virtual void SetSymbolSize(long code) override;
         virtual DWORD GetSymbolCharacterCode() const override;
         virtual void SetSymbolCharacterCode(DWORD code) override;
         virtual COLORREF GetColor() const override;
         virtual void SetColor(COLORREF color) override;
         virtual bool DrawLine() const override;
         virtual void DrawLine(bool bDraw) override;

      private:
         std::_tstring m_Name;
         std::_tstring m_FontFace = _T("Symbol");
         long     m_FontSize = 120;
         DWORD    m_CharCode = 0;
         COLORREF m_Color = RED3;
         bool     m_bDrawLine = false;

      };
   };
};
