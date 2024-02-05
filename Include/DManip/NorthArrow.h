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
      /// @brief Specialized display object representing a north arrow
      class DMANIPCLASS NorthArrow : public DisplayObjectDefaultImpl
      {
      private:
         NorthArrow(IDType id);

      public:
         static std::shared_ptr<NorthArrow> Create(IDType id = INVALID_ID) { return std::shared_ptr<NorthArrow>(new NorthArrow(id)); }
	      virtual ~NorthArrow() = default;

         void SetText(LPCTSTR lpszText);
         CString GetText() const;

         void SetFont(const LOGFONT& Font);
         LOGFONT GetFont() const;

         /// @brief Direction of north relative to the horizontal axis of the screen
         void SetDirection(Float64 angle);
         Float64 GetDirection() const;

         /// @brief Size of the north arrow in logical coordinates
         /// @param size 
         void SetSize(LONG size);
         LONG GetSize() const;

         // iDisplayObject Implementation
         // Drawing
         virtual void Draw(CDC* pDC) override;
         virtual void Highlight(CDC* pDC,bool bHighlight) override;

         virtual RECT GetLogicalBoundingBox() const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override; 

      private:
         CString m_strText = _T("");
         LOGFONT m_Font;
         Float64 m_Direction = PI_OVER_2;
         LONG m_Size = 50;
      };
   };
};
