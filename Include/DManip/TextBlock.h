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
      /// @brief Draws text at a location in model space
      class DMANIPCLASS iTextBlock : public DisplayObjectDefaultImpl
      {
      public:
         using DisplayObjectDefaultImpl::DisplayObjectDefaultImpl;

         /// @brief Model space position
         /// @param pos 
         virtual void SetPosition(const WBFL::Geometry::Point2d& pos) = 0;
         virtual const WBFL::Geometry::Point2d& GetPosition() const = 0;

         /// @brief Use CDC::SetTextAlign constants
         virtual void SetTextAlign(UINT nFlags) = 0;
         virtual UINT GetTextAlign() const = 0;

         /// @brief Rotation angle of the text, measured in 10th of a degree from horizontal
         virtual void SetAngle(LONG angle) = 0;
         virtual LONG GetAngle() const = 0;

         /// @brief Point size of the font, in 10ths of a point
         /// @param pointSize 
         virtual void SetPointSize(LONG pointSize) = 0;
         virtual LONG GetPointSize() const = 0;

         /// @brief The text
         /// @param lpszText 
         virtual void SetText(LPCTSTR lpszText) = 0;
         virtual CString GetText() const = 0;

         /// @brief Font information.
         virtual void SetFont(const LOGFONT& Font) = 0;
         virtual LOGFONT GetFont() const = 0;

         virtual void SetTextColor(COLORREF color) = 0;
         virtual COLORREF GetTextColor() const = 0;

         virtual void SetBkColor(COLORREF color) = 0;
         virtual COLORREF GetBkColor() const = 0;

         /// @brief Background mode - Use CDC::SetBkMode
         /// @param bkMode 
         virtual void SetBkMode(int bkMode) = 0;
         virtual int GetBkMode() const = 0;
      };
   };
};
