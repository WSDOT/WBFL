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
#include <DManip/DisplayObjectEvents.h>
#include <DManip/InplaceEditableDefaultImpl.h>
#include <DManip/NestedDisplayObjectEventRelay.h>


class COnMouseOverCursor;

namespace WBFL
{
   namespace DManip
   {
      class InplaceEdit;

      /// @brief A text block display object that allows the text to be edited by the user. 
      /// Clicking on an editable text block activates an edit window in which the enter text.
      class DMANIPCLASS EditableTextBlock :
         public InplaceEditableDefaultImpl,
         public iTextBlock
      {
      protected:
         EditableTextBlock(IDType id);

      private:
         void Init();

      public:
         enum class Format
         {
            Text, 
            Numeric
         };

         static std::shared_ptr<EditableTextBlock> Create(IDType id = INVALID_ID);
	      virtual ~EditableTextBlock();

         void EnableAutoUpdate(bool bEnable);
         bool IsAutoUpdateEnabled() const;
         CString GetEditedText() const;
         void SetFormat(Format format);
         Format GetFormat() const;

         // iInplaceEditable Implementation
         // (not implemented by InplaceEditableDefaultImpl)
         virtual void CreateEditControl() override;
         virtual void DestroyEditControl() override;
         virtual bool ValidateData() override;
         virtual void OnDataChanged() override;

         // iDisplayObject overrides
         virtual void SetID(IDType id) override { m_TextBlock->SetID(id); }
         virtual IDType GetID() const override { return m_TextBlock->GetID(); }
         virtual void SetItemData(void* pVoid, bool bDelete) override { m_TextBlock->SetItemData(pVoid, bDelete); }
         virtual void GetItemData(void** ppVoid) override { m_TextBlock->GetItemData(ppVoid); }
         virtual void SetDisplayList(std::weak_ptr<iDisplayList> pDL) override { m_TextBlock->SetDisplayList(pDL); }
         virtual std::shared_ptr<iDisplayList> GetDisplayList() override { return m_TextBlock->GetDisplayList(); }
         virtual std::shared_ptr<const iDisplayList> GetDisplayList() const override { return m_TextBlock->GetDisplayList(); }
         virtual void Visible(bool bVisible) override { m_TextBlock->Visible(bVisible); }
         virtual bool IsVisible() const override { return m_TextBlock->IsVisible(); }
         virtual void Draw(CDC* pDC) override;
         virtual void Highlight(CDC* pDC, bool bHighlite) override { m_TextBlock->Highlight(pDC, bHighlite); };
#if defined(_DEBUG)
         virtual void DrawGravityWell(CDC* pDC) override { m_TextBlock->DrawGravityWell(pDC); }
#endif
         virtual void SetGravityWellStrategy(std::shared_ptr<iGravityWellStrategy> pStrategy) override { m_TextBlock->SetGravityWellStrategy(pStrategy); }
         virtual std::shared_ptr<iGravityWellStrategy> GetGravityWellStrategy() override { return m_TextBlock->GetGravityWellStrategy(); }
         virtual bool HitTest(const POINT& point) const override { return m_TextBlock->HitTest(point); }
         virtual RECT GetLogicalBoundingBox() const override { return m_TextBlock->GetLogicalBoundingBox(); }
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override { return m_TextBlock->GetBoundingBox(); }
         virtual bool TouchesRect(const RECT& r) const override { return m_TextBlock->TouchesRect(r); }
         virtual void Select(bool bSelect) override { m_TextBlock->Select(bSelect); }
         virtual bool IsSelected() const override { return m_TextBlock->IsSelected(); }
         virtual void SetSelectionType(SelectionType st) override { m_TextBlock->SetSelectionType(st); }
         virtual SelectionType GetSelectionType() const override { return m_TextBlock->GetSelectionType(); }
         virtual void RetainSelection(bool bRetain) override { m_TextBlock->RetainSelection(); }
         virtual bool RetainSelection() const override { return m_TextBlock->RetainSelection(); }
         virtual void SetToolTipText(LPCTSTR lpszToolTipText) override { m_TextBlock->SetToolTipText(lpszToolTipText); }
         virtual std::_tstring GetToolTipText() const override { return m_TextBlock->GetToolTipText(); }
         virtual void SetMaxTipWidth(INT maxWidth) override { m_TextBlock->SetMaxTipWidth(maxWidth); }
         virtual INT GetMaxTipWidth() const override { return m_TextBlock->GetMaxTipWidth(); }
         virtual void SetTipDisplayTime(INT iTime) override { m_TextBlock->SetTipDisplayTime(iTime); }
         virtual INT GetTipDisplayTime() const override { return m_TextBlock->GetTipDisplayTime(); }
         virtual bool OnLButtonDown(UINT nFlags, const POINT& point) override;
         virtual bool OnLButtonUp(UINT nFlags, const POINT& point) override { return m_TextBlock->OnLButtonUp(nFlags, point); }
         virtual bool OnLButtonDblClk(UINT nFlags, const POINT& point) override { return m_TextBlock->OnLButtonDblClk(nFlags, point); }
         virtual bool OnRButtonDown(UINT nFlags, const POINT& point) override { return m_TextBlock->OnRButtonDown(nFlags, point); }
         virtual bool OnRButtonUp(UINT nFlags, const POINT& point) override { return m_TextBlock->OnRButtonUp(nFlags, point); }
         virtual bool OnRButtonDblClk(UINT nFlags, const POINT& point) override { return m_TextBlock->OnRButtonDblClk(nFlags, point); }
         virtual bool OnMouseMove(UINT nFlags, const POINT& point) override;
         virtual bool OnMouseWheel(UINT nFlags, short zDelta, const POINT& point) override { return m_TextBlock->OnMouseWheel(nFlags, zDelta, point); }
         virtual bool OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override { return m_TextBlock->OnKeyDown(nChar, nRepCnt, nFlags); }
         virtual bool OnContextMenu(CWnd* pWnd, const POINT& point) override { return m_TextBlock->OnContextMenu(pWnd, point); }
         virtual void RegisterDropSite(std::shared_ptr<iDropSite> pDropSite) override { m_TextBlock->RegisterDropSite(pDropSite); }
         virtual void UnregisterDropSite() override { return m_TextBlock->UnregisterDropSite(); }
         virtual std::shared_ptr<iDropSite> GetDropSite() override { return m_TextBlock->GetDropSite(); }
         virtual void SetParent(std::weak_ptr<iDisplayObject> pParent) override { m_TextBlock->SetParent(pParent); }
         virtual std::shared_ptr<iDisplayObject> GetParent() override { return m_TextBlock->GetParent(); }

         // iTextBlock overrides
         virtual void SetPosition(const WBFL::Geometry::Point2d& pos) override { m_TextBlock->SetPosition(pos);}
         virtual const WBFL::Geometry::Point2d& GetPosition() const override { return m_TextBlock->GetPosition(); }
         virtual void SetTextAlign(UINT nFlags) override;
         virtual UINT GetTextAlign() const override { return m_TextBlock->GetTextAlign(); }
         virtual void SetAngle(LONG angle) override { m_TextBlock->SetAngle(angle); }
         virtual LONG GetAngle() const override { return m_TextBlock->GetAngle(); }
         virtual void SetPointSize(LONG pointSize) override { m_TextBlock->SetPointSize(pointSize); }
         virtual LONG GetPointSize() const override { return m_TextBlock->GetPointSize(); }
         virtual void SetText(LPCTSTR lpszText) override;
         virtual CString GetText() const override;
         virtual void SetFont(const LOGFONT& font) override { m_TextBlock->SetFont(font); }
         virtual LOGFONT GetFont() const override { return m_TextBlock->GetFont(); }
         virtual void SetTextColor(COLORREF color) override { m_TextBlock->SetTextColor(color); }
         virtual COLORREF GetTextColor() const override { return m_TextBlock->GetTextColor(); }
         virtual void SetBkColor(COLORREF color) override { m_TextBlock->SetBkColor(color); }
         virtual COLORREF GetBkColor() const override { return m_TextBlock->GetBkColor(); }
         virtual void SetBkMode(int bkMode) override { m_TextBlock->SetBkMode(bkMode); }
         virtual int GetBkMode() const override { return m_TextBlock->GetBkMode(); }



      public:
         virtual CDisplayView* GetDisplayView() override;
         virtual CInplaceEdit* GetEditObject() override;
         virtual std::shared_ptr<iInplaceEditable> GetInplaceEditable() override;

      private:
         std::shared_ptr<iTextBlock> m_TextBlock;
         std::shared_ptr<NestedDisplayObjectEventRelay> m_EventRelay;

         CInplaceEdit* m_pEdit = nullptr;
         bool m_bAutoUpdate = false;
         CString m_strCtrlText; // Text that was in the edit control immediately before it was destroyed
         CFont* m_pFont = nullptr; // Pointer to the font used by the edit control. nullptr when m_pEdit's window handle is invalid
         Format m_Format = Format::Text;
         COnMouseOverCursor* m_pOnMouseOverCursor = nullptr;
      };
   };
};
