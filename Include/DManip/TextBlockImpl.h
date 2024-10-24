///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <DManip/DManipExp.h>
#include <DManip/TextBlock.h>
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A display object that draws text.
      /// Multiple lines of text can be drawn. Lines must be seperated by \n
      class DMANIPCLASS TextBlock : public iTextBlock
      {
      protected:
         TextBlock(IDType id);

      public:
         static std::shared_ptr<TextBlock> Create(IDType id = INVALID_ID) { return std::shared_ptr<TextBlock>(new TextBlock(id)); }
	      virtual ~TextBlock() = default;

         // iDisplayObject Implementation
         virtual void Draw(CDC* pDC) override;
         virtual void Highlight(CDC* pDC,bool bHighlight) override;
         virtual RECT GetLogicalBoundingBox() const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override;

         // iTextBlock Implementation
         virtual void SetPosition(const WBFL::Geometry::Point2d& pos) override;
         virtual const WBFL::Geometry::Point2d& GetPosition() const override;
         virtual void SetTextAlign(UINT nFlags) override;
         virtual UINT GetTextAlign() const override;
         virtual void SetAngle(LONG angle) override;
         virtual LONG GetAngle() const override;
         virtual void SetPointSize(LONG pointSize) override;
         virtual LONG GetPointSize() const override;
         virtual void SetText(LPCTSTR lpszText) override;
         virtual CString GetText() const override;
         virtual void SetFont(const LOGFONT& Font) override;
         virtual LOGFONT GetFont() const override;
         virtual void SetTextColor(COLORREF color) override;
         virtual COLORREF GetTextColor() const override;
         virtual void SetBkColor(COLORREF color) override;
         virtual COLORREF GetBkColor() const override;
         virtual void SetBkMode(int bkMode) override;
         virtual int GetBkMode() const override;

      private:
         UINT m_TextAlign = TA_TOP | TA_LEFT;
         WBFL::Geometry::Point2d m_Position;
         CString m_strText = _T("");
         LOGFONT m_Font;
         COLORREF m_FgColor = BLACK;
         COLORREF m_BgColor = WHITE;
         int m_BkMode = OPAQUE;

         void GetTextLines(CStringArray& strings) const;
         void GetPositionInLogicalSpace(LONG* lx,LONG* ly) const;
         void CreateFont(CFont& font,CDC* pDC);
      };
   };
};
