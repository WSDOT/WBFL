///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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

#include <DManip/Legend.h>
#include <DManip/Draggable.h>
#include <DManip/ContextMenuCommandCallback.h>
#include <DManip/ContextMenuCommandWnd.h>
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A draggable legend display object with a context menu that allows the user to dynamically change the arrangement of legend entries
      class DMANIPCLASS LegendDisplayObject : public iLegendDisplayObject, public iDraggable, public iContextMenuCommandCallback
      {
      protected:
         LegendDisplayObject(IDType id);

      public:
         static std::shared_ptr<LegendDisplayObject> Create(IDType id = INVALID_ID) { return std::shared_ptr<LegendDisplayObject>(new LegendDisplayObject(id)); }

         // clipboard format
         static UINT ms_cfFormat;

         // iDisplayObject
         virtual void Draw(CDC* pDC) override;
         virtual void Highlight(CDC* pDC, bool bHighlight) override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override;
         virtual std::_tstring GetToolTipText() const override;
         virtual bool OnLButtonDown(UINT nFlags, const POINT& point) override;
         virtual bool OnRButtonDown(UINT nFlags, const POINT& point) override;
         virtual bool OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override;

         // iLegendDisplayObject
         virtual void SetPosition(const WBFL::Geometry::Point2d& pos, bool bRedraw, bool bFireEvent) override;
         virtual const WBFL::Geometry::Point2d& GetPosition() const override;
         virtual std::_tstring GetTitle() const override;
         virtual void SetTitle(LPCTSTR lpszTitle) override;
         virtual void SetFont(const LOGFONT& font) override;
         virtual const LOGFONT& GetFont() const override;
         virtual IndexType GetEntryCount() const override;
         virtual void AddEntry(std::shared_ptr<iLegendEntry> entry) override;
         virtual void InsertEntry(IndexType index, std::shared_ptr<iLegendEntry> entry) override;
         virtual std::shared_ptr<iLegendEntry> GetEntry(IndexType index) override;
         virtual void RemoveEntry(IndexType index) override;
         virtual void ClearEntries() override;
         virtual IndexType GetNumRows() const override;
         virtual void SetNumRows(IndexType nRows) override;
         virtual SIZE GetCellSize() const override;
         virtual void SetCellSize(const SIZE& size) override;
         virtual SIZE GetMinCellSize() const override;
         virtual bool DrawBorder() const override;
         virtual void DrawBorder(bool bDraw) override;
         virtual bool Fill() const override;
         virtual void Fill(bool bFill) override;
         virtual COLORREF GetFillColor() const override;
         virtual void SetFillColor(COLORREF color) override;
         virtual bool IsDraggable() const override;
         virtual void IsDraggable(bool bDraggable) override;

         // iDraggable Implementation
         virtual void SetDragData(std::shared_ptr<iDragData> dd) override;
         virtual std::shared_ptr<iDragData> GetDragData() override;
         virtual UINT Format() override;
         virtual void PrepareDrag(std::shared_ptr<iDragDataSink> pSink) override;
         virtual void OnDrop(std::shared_ptr<iDragDataSource> pSource) override;
         virtual void OnDragMoved(const WBFL::Geometry::Size2d& offset) override;
         virtual void OnMoved() override;
         virtual void OnCopied() override;
         virtual void DrawDragImage(CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) override;


         // iContextMenuCommandCallback
         virtual void OnMessage(UINT msg) override;

      private:
         void Draw(CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& location, bool hiLite, bool beingDragged=false) const;
         WBFL::Geometry::Rect2d GetBoundingBoxEx(bool bIncludeTitle) const;

         WBFL::Geometry::Point2d m_Position;
         std::_tstring m_Title;
         LOGFONT  m_Font;
         IndexType m_nRows = 1;
         bool     m_bDrawBorder = true;
         bool     m_bFill = true;
         COLORREF m_FillColor = LIGHTYELLOW;
         SIZE     m_CellSize = { 12 * 80 * 2, 3 * 80 * 2 };  // proportional to font size (twips)
         bool     m_bIsDraggable = true;

         std::vector<std::shared_ptr<iLegendEntry>> m_LegendEntries;

         std::shared_ptr<iDragData> m_pDragData;

         CSize m_DragOffset; // only for dragging - used to make dragging smooth

         std::unique_ptr<CContextMenuCommandWnd> m_pContextMenuMsgWnd;
      };
   };
};
