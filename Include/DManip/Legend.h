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
#include <DManip/LegendEntry.h>
#include <DManip/DragData.h>

class CRect;
class CDC;

namespace WBFL
{
   namespace DManip
   {
      /// @brief An interface defining a legend display object 
      class iLegendDisplayObject : public DisplayObjectDefaultImpl
      {
      public:
         using DisplayObjectDefaultImpl::DisplayObjectDefaultImpl;

         /// @brief Location of top left corner of border
         virtual void SetPosition(const WBFL::Geometry::Point2d& pos,bool bRedraw,bool bFireEvent) = 0;
         virtual const WBFL::Geometry::Point2d& GetPosition() const = 0;

         /// @brief A title for the legend box
         /// @return 
         virtual std::_tstring GetTitle() const = 0;
         virtual void SetTitle(LPCTSTR lpszTitle) = 0;

         /// @brief Font for legend entry names. Note that font height is in 10th of points.
         /// Note that Title is drawn in bold version of same font
         virtual void SetFont(const LOGFONT& font) = 0;
         virtual const LOGFONT& GetFont() const = 0;

         /// @brief Returns the number of legend entries
         /// @return 
         virtual IndexType GetEntryCount() const = 0;

         /// @brief Adds a legend entry
         /// @param entry 
         virtual void AddEntry(std::shared_ptr<iLegendEntry> entry) = 0;

         /// @brief Inserts a legend entry at the specified position
         /// @param index 
         /// @param entry 
         virtual void InsertEntry(IndexType index, std::shared_ptr<iLegendEntry> entry) = 0;

         /// @brief Returns a legend entry
         /// @param index 
         /// @return 
         virtual std::shared_ptr<iLegendEntry> GetEntry(IndexType index) = 0;

         /// @brief Removes a legend entry
         /// @param index 
         virtual void RemoveEntry(IndexType index) = 0;

         /// @brief Clears all entries from the legend
         virtual void ClearEntries() = 0;

         /// @brief Number of rows displayed in legend "grid". Number of columns is
         /// determined by the number of entries to be displayed. Grid is filled
         /// column-wise
         virtual IndexType GetNumRows() const = 0;
         virtual void SetNumRows(IndexType nRows) = 0;

         /// @brief Size of each legend grid in twips. The minimum allowable size is
         /// 10x wide and 4x high of the Font size.
         virtual SIZE GetCellSize() const = 0;
         virtual void SetCellSize(const SIZE& size) = 0;

         /// @brief Call this after filling legend entries to compute minimum cell
         /// size in twips based on text size.
         virtual SIZE GetMinCellSize() const = 0;

         /// @brief Indicates if a border should be drawn
         virtual bool DrawBorder() const = 0;
         virtual void DrawBorder(bool bDraw) = 0;

         /// @brief Indicates if the legend background is filled?
         virtual bool Fill() const = 0;
         virtual void Fill(bool bFill) = 0;

         /// @brief the fill color
         virtual COLORREF GetFillColor() const = 0;
         virtual void SetFillColor(COLORREF color) = 0;

         /// @brief Indicates if a users is allowed to drag the legend around screen?
         virtual bool IsDraggable() const = 0;
         virtual void IsDraggable(bool bDraggable) = 0;
      };
   };
};
