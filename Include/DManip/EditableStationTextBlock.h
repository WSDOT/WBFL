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
#include <DManip/InplaceEditableDefaultImpl.h>
#include <DManip/EditableTextBlock.h>
#include <DManip/NestedDisplayObjectEventRelay.h>

#include <CoordGeom/Station.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A text block containing an editable station
      class DMANIPCLASS EditableStationTextBlock :
         public InplaceEditableDefaultImpl,
         public iTextBlock
      {
      protected:
         EditableStationTextBlock(IDType id);

      private:
         void Init();
         std::_tstring AsString() const;

      public:
         static std::shared_ptr<EditableStationTextBlock> Create(IDType id = INVALID_ID);
         static std::shared_ptr<EditableStationTextBlock> Create(const WBFL::Units::StationFormat& stationFormat, IDType id = INVALID_ID);
         virtual ~EditableStationTextBlock() = default;

         /// @brief Indicates of the text is automatically updated if the value is changed with SetStation
         void EnableAutoUpdate(bool bEnable) { m_EditableTextBlock->EnableAutoUpdate(bEnable); }
         bool IsAutoUpdateEnabled() const { return m_EditableTextBlock->IsAutoUpdateEnabled();  }

         /// @brief Sets the station formatting type
         void SetStationFormat(const WBFL::Units::StationFormat& stationFormat);
         const WBFL::Units::StationFormat& GetStationFormat() const;

         /// @brief Sets the station
         void SetStation(const WBFL::COGO::Station& station);
         const WBFL::COGO::Station& GetStation() const;

         /// @brief Returns the station value from the edit control
         WBFL::COGO::Station GetEditedStation() const;

         // iInplaceEditable Implementation
         // (not implemented by InplaceEditableDefaultImpl)
         virtual void CreateEditControl() override;
         virtual void DestroyEditControl() override;
         virtual bool ValidateData() override;
         virtual void OnDataChanged() override;

         // iDisplayObject overrides
         virtual void SetID(IDType id) override { m_EditableTextBlock->SetID(id); }
         virtual IDType GetID() const override { return m_EditableTextBlock->GetID(); }
         virtual void SetItemData(void* pVoid, bool bDelete) override { m_EditableTextBlock->SetItemData(pVoid, bDelete); }
         virtual void GetItemData(void** ppVoid) override { m_EditableTextBlock->GetItemData(ppVoid); }
         virtual void SetDisplayList(std::weak_ptr<iDisplayList> pDL) override { m_EditableTextBlock->SetDisplayList(pDL); }
         virtual std::shared_ptr<iDisplayList> GetDisplayList() override { return m_EditableTextBlock->GetDisplayList(); }
         virtual std::shared_ptr<const iDisplayList> GetDisplayList() const override { return m_EditableTextBlock->GetDisplayList(); }
         virtual void Visible(bool bVisible) override { m_EditableTextBlock->Visible(bVisible); }
         virtual bool IsVisible() const override { return m_EditableTextBlock->IsVisible(); }
         virtual void Draw(CDC * pDC) override { m_EditableTextBlock->Draw(pDC); }
         virtual void Highlight(CDC * pDC, bool bHighlight) override { m_EditableTextBlock->Highlight(pDC, bHighlight); };
#if defined(_DEBUG)
         virtual void DrawGravityWell(CDC * pDC) override { m_EditableTextBlock->DrawGravityWell(pDC); }
#endif
         virtual void SetGravityWellStrategy(std::shared_ptr<iGravityWellStrategy> pStrategy) override { m_EditableTextBlock->SetGravityWellStrategy(pStrategy); }
         virtual std::shared_ptr<iGravityWellStrategy> GetGravityWellStrategy() override { return m_EditableTextBlock->GetGravityWellStrategy(); }
         virtual bool HitTest(const POINT & point) const override { return m_EditableTextBlock->HitTest(point); }
         virtual RECT GetLogicalBoundingBox() const override { return m_EditableTextBlock->GetLogicalBoundingBox(); }
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override { return m_EditableTextBlock->GetBoundingBox(); }
         virtual bool TouchesRect(const RECT & r) const override { return m_EditableTextBlock->TouchesRect(r); }
         virtual void Select(bool bSelect) override { m_EditableTextBlock->Select(bSelect); }
         virtual bool IsSelected() const override { return m_EditableTextBlock->IsSelected(); }
         virtual void SetSelectionType(SelectionType st) override { m_EditableTextBlock->SetSelectionType(st); }
         virtual SelectionType GetSelectionType() const override { return m_EditableTextBlock->GetSelectionType(); }
         virtual void RetainSelection(bool bRetain) override { m_EditableTextBlock->RetainSelection(); }
         virtual bool RetainSelection() const override { return m_EditableTextBlock->RetainSelection(); }
         virtual void SetToolTipText(LPCTSTR lpszToolTipText) override { m_EditableTextBlock->SetToolTipText(lpszToolTipText); }
         virtual std::_tstring GetToolTipText() const override { return m_EditableTextBlock->GetToolTipText(); }
         virtual void SetMaxTipWidth(INT maxWidth) override { m_EditableTextBlock->SetMaxTipWidth(maxWidth); }
         virtual INT GetMaxTipWidth() const override { return m_EditableTextBlock->GetMaxTipWidth(); }
         virtual void SetTipDisplayTime(INT iTime) override { m_EditableTextBlock->SetTipDisplayTime(iTime); }
         virtual INT GetTipDisplayTime() const override { return m_EditableTextBlock->GetTipDisplayTime(); }
         virtual bool OnLButtonDown(UINT nFlags, const POINT& point) override;
         virtual bool OnLButtonUp(UINT nFlags, const POINT & point) override { return m_EditableTextBlock->OnLButtonUp(nFlags, point); }
         virtual bool OnLButtonDblClk(UINT nFlags, const POINT & point) override { return m_EditableTextBlock->OnLButtonDblClk(nFlags, point); }
         virtual bool OnRButtonDown(UINT nFlags, const POINT & point) override { return m_EditableTextBlock->OnRButtonDown(nFlags, point); }
         virtual bool OnRButtonUp(UINT nFlags, const POINT & point) override { return m_EditableTextBlock->OnRButtonUp(nFlags, point); }
         virtual bool OnRButtonDblClk(UINT nFlags, const POINT & point) override { return m_EditableTextBlock->OnRButtonDblClk(nFlags, point); }
         virtual bool OnMouseMove(UINT nFlags, const POINT & point) override { return m_EditableTextBlock->OnMouseMove(nFlags, point); }
         virtual bool OnMouseWheel(UINT nFlags, short zDelta, const POINT & point) override { return m_EditableTextBlock->OnMouseWheel(nFlags, zDelta, point); }
         virtual bool OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override { return m_EditableTextBlock->OnKeyDown(nChar, nRepCnt, nFlags); }
         virtual bool OnContextMenu(CWnd * pWnd, const POINT & point) override { return m_EditableTextBlock->OnContextMenu(pWnd, point); }
         virtual void RegisterDropSite(std::shared_ptr<iDropSite> pDropSite) override { m_EditableTextBlock->RegisterDropSite(pDropSite); }
         virtual void UnregisterDropSite() override { return m_EditableTextBlock->UnregisterDropSite(); }
         virtual std::shared_ptr<iDropSite> GetDropSite() override { return m_EditableTextBlock->GetDropSite(); }
         virtual void SetParent(std::weak_ptr<iDisplayObject> pParent) override { m_EditableTextBlock->SetParent(pParent); }
         virtual std::shared_ptr<iDisplayObject> GetParent() override { return m_EditableTextBlock->GetParent(); }

         // iTextBlock overrides
         virtual void SetPosition(const WBFL::Geometry::Point2d& pos) override { m_EditableTextBlock->SetPosition(pos); }
         virtual const WBFL::Geometry::Point2d& GetPosition() const override { return m_EditableTextBlock->GetPosition(); }
         virtual void SetTextAlign(UINT nFlags) override { m_EditableTextBlock->SetTextAlign(nFlags); }
         virtual UINT GetTextAlign() const override { return m_EditableTextBlock->GetTextAlign(); }
         virtual void SetAngle(LONG angle) override { m_EditableTextBlock->SetAngle(angle); }
         virtual LONG GetAngle() const override { return m_EditableTextBlock->GetAngle(); }
         virtual void SetPointSize(LONG pointSize) override { m_EditableTextBlock->SetPointSize(pointSize); }
         virtual LONG GetPointSize() const override { return m_EditableTextBlock->GetPointSize(); }
         virtual void SetText(LPCTSTR lpszText) override;
         virtual CString GetText() const override;
         virtual void SetFont(const LOGFONT & font) override { m_EditableTextBlock->SetFont(font); }
         virtual LOGFONT GetFont() const override { return m_EditableTextBlock->GetFont(); }
         virtual void SetTextColor(COLORREF color) override { m_EditableTextBlock->SetTextColor(color); }
         virtual COLORREF GetTextColor() const override { return m_EditableTextBlock->GetTextColor(); }
         virtual void SetBkColor(COLORREF color) override { m_EditableTextBlock->SetBkColor(color); }
         virtual COLORREF GetBkColor() const override { return m_EditableTextBlock->GetBkColor(); }
         virtual void SetBkMode(int bkMode) override { m_EditableTextBlock->SetBkMode(bkMode); }
         virtual int GetBkMode() const override { return m_EditableTextBlock->GetBkMode(); }

      protected:
         virtual CDisplayView* GetDisplayView() override;
         virtual CInplaceEdit* GetEditObject() override;
         virtual std::shared_ptr<iInplaceEditable> GetInplaceEditable() override;

      private:
         std::shared_ptr<EditableTextBlock> m_EditableTextBlock; // Most all of the implementation is delegated here
         std::shared_ptr<NestedDisplayObjectEventRelay> m_EventRelay;
         WBFL::Units::StationFormat m_StationFormat = WBFL::Units::StationFormats::US;
         WBFL::COGO::Station m_Station;
      };
   };
};
