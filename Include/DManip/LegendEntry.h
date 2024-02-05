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
#include <DManip/DragData.h>

class CRect;
class CDC;

namespace WBFL
{
   namespace DManip
   {
      /// @brief Interface defining an entry in a legend
      class DMANIPCLASS iLegendEntry
      {
      public:
         /// @brief Name of the entry
         /// @param lpszName 
         virtual void SetName(LPCTSTR lpszName) = 0;
         virtual std::_tstring GetName() const = 0;

         /// @brief Draw symbol in drawRect. Size is in logical units
         virtual void Draw(CDC* pDC, const RECT& drawRect, bool beingDrabbed) const = 0;

         /// @brief Write to a data source for drag/drop operations
         virtual void WriteDragData(std::shared_ptr<iDragDataSink> pSink, UINT cfFormat) = 0;

         /// @brief Read from a data source for drag/drop operations
         virtual void ReadDragData(std::shared_ptr<iDragDataSource> pSource, UINT cfFormat) = 0;

         /// @brief Name of font face for symbol. "Symbol" is the default
         virtual std::_tstring GetSymbolFontFace() const = 0;
         virtual void SetSymbolFontFace(LPCTSTR newVal) = 0;

         /// @brief Character font size in 1/10 points
         virtual long GetSymbolSize() const = 0;
         virtual void SetSymbolSize(long code) = 0;

         /// @brief Unicode constant defining symbol to be used for legend item
         /// Refer to Word's Insert Symbol command for a list of these codes
         /// NOTE that a value of zero will fill the entire legend box with the current color.
         virtual DWORD GetSymbolCharacterCode() const = 0;
         virtual void SetSymbolCharacterCode(DWORD code) = 0;

         /// @brief Color associated with the legend item
         /// @return 
         virtual COLORREF GetColor() const = 0;
         virtual void SetColor(COLORREF color) = 0;

         /// @brief Indicates if the legend entry is drawn as a horizontal colored line across the legend box
         /// If not, it is drawn as a rectangle
         virtual bool DrawLine() const = 0;
         virtual void DrawLine(bool bDraw) = 0;
      };
   };
};
