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
#include <DManip/DisplayObjectDefaultImpl.h>


namespace WBFL
{
   namespace DManip
   {
      /// @brief Draws text as a title on a view. The title is centered on the top of the display view
      class DMANIPCLASS ViewTitle : public DisplayObjectDefaultImpl
      {
      private:
         ViewTitle(IDType id);

      public:
         static std::shared_ptr<ViewTitle> Create(IDType id = INVALID_ID) { return std::shared_ptr<ViewTitle>(new ViewTitle(id)); }
	      virtual ~ViewTitle();

         void SetText(LPCTSTR lpszText);
         CString GetText() const;

         void SetFont(const LOGFONT& Font);
         LOGFONT GetFont() const;

         // iDisplayObject Implementation
         virtual void Draw(CDC* pDC) override;
         virtual void Highlight(CDC* pDC,bool bHighlight) override;
         virtual RECT GetLogicalBoundingBox() const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override;

      private:
         CString m_strText;
         LOGFONT m_Font;

         void GetTextLines(CStringArray& strings) const;
      };
   };
};
