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

#include <DManip/InplaceEditCtrl.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/DisplayView.h>
#include <DManip/EditableTextBlock.h>
#include <DManip/DisplayObjectEvents.h>
#include <DManip/NestedDisplayObjectEventRelay.h>

#include <System/NumericFormatTool.h>
#include <Units/Convert.h>
#include <Units/IndirectMeasure.h>

#include <boost/algorithm/string/trim.hpp>

class CInplaceEdit;

namespace WBFL
{
   namespace DManip
   {
      /// @brief Template class defining the functionality of an iEditableUnitValueTextBlock
      /// @tparam T The indirect measure type
      template <class T>
      class EditableUnitValueTextBlock :
         public iTextBlock,
         public InplaceEditableDefaultImpl
      {
      private:
         EditableUnitValueTextBlock(const T& indirectMeasure,IDType id) : m_IndirectMeasure(indirectMeasure), iTextBlock(id)
         {
            m_EditableTextBlock = EditableTextBlock::Create();
            m_EditableTextBlock->SetFormat(EditableTextBlock::Format::Numeric);
            m_pctlUnitTag = std::make_unique<CStatic>();
         }

         void Init()
         {
            m_EventRelay = NestedDisplayObjectEventRelay::Create(this);
            m_EditableTextBlock->RegisterEventSink(m_EventRelay);

            SetText(AsString(true).c_str());
         }

         std::_tstring AsString(bool bIncludeTag) const
         {
            WBFL::System::NumericFormatTool format_tool(m_IndirectMeasure.Format, m_IndirectMeasure.Width, m_IndirectMeasure.Precision);
            std::_tostringstream os;
            auto value = WBFL::Units::ConvertFromSysUnits(IsZero(m_Value,m_IndirectMeasure.Tol) ? 0.0 : m_Value, m_IndirectMeasure.UnitOfMeasure);
            if (bIncludeTag)
            {
               os << format_tool.AsString(value) << _T(" ") << m_IndirectMeasure.UnitOfMeasure.UnitTag().c_str();
            }
            else
            {
               os << format_tool.AsString(value);
            }

            auto str = os.str();
            boost::trim(str);
            return str;
         }

      public:
         static std::shared_ptr<EditableUnitValueTextBlock<T>> Create(const T& indirectMeasure,IDType id = INVALID_ID)
         { 
            auto me = std::shared_ptr<EditableUnitValueTextBlock<T>>(new EditableUnitValueTextBlock<T>(indirectMeasure,id));
            me->Init();
            return me;
         }

         virtual ~EditableUnitValueTextBlock()
         {
            m_EditableTextBlock->UnregisterEventSink();
         }

         void EnableAutoUpdate(bool bEnable) { m_EditableTextBlock->EnableAutoUpdate(bEnable); }
         bool IsAutoUpdateEnabled() const { return m_EditableTextBlock->IsAutoUpdateEnabled(); }
         void SetValue(Float64 value)
         {
            m_Value = value; // value in system units
            SetText(AsString(true).c_str());
         }

         Float64 GetValue() const
         {
            return m_Value;
         }

         Float64 GetEditedValue() const
         {
            Float64 editedValue = _wtof(m_EditableTextBlock->GetEditedText()); // value in display units (without unit tag)
            // Convert back to system units
            editedValue = WBFL::Units::ConvertToSysUnits(editedValue, m_IndirectMeasure.UnitOfMeasure);
            return editedValue;
         }

         // iInplaceEditable Implementation
         // (not implemented by InplaceEditableDefaultImpl)
         virtual void CreateEditControl() override
         {
            auto ipedit = std::dynamic_pointer_cast<iInplaceEditable>(m_EditableTextBlock);
            ipedit->CreateEditControl();

            // Replace the text in the edit control with the value in display units, without
            // the unit tag...
            CInplaceEdit* pEdit = GetEditObject();

            auto str = AsString(false);
            pEdit->SetWindowTextW(str.c_str());
            pEdit->SetSel(0, (DWORD)str.length(), TRUE);
            pEdit->UpdateWindow();

            // Make sure text is right justified
            pEdit->ModifyStyle(ES_LEFT | ES_CENTER, ES_RIGHT);

            // Drill up to the view and create a dc so that we can get the size of the tag
            // with that, we can make the static control the right size
            auto view = m_EditableTextBlock->GetDisplayList()->GetDisplayMgr()->GetView();

            CDManipClientDC dc(view);

            auto unit_tag = m_IndirectMeasure.UnitOfMeasure.UnitTag();
            CSize tagExtents = dc.GetTextExtent(unit_tag.c_str());

            // now, place a static control after the edit control and put the unit tag in it
            CRect editRect;
            pEdit->GetWindowRect(&editRect);

            CRect tagRect;
            tagRect.left = editRect.right;
            tagRect.right = tagRect.left + tagExtents.cx;
            tagRect.top = editRect.top;
            tagRect.bottom = editRect.bottom;
            if (tagRect.Height() < tagExtents.cy)
               tagRect.bottom = tagRect.top + tagExtents.cy;

            view->ScreenToClient(&tagRect);

            m_pctlUnitTag->Create(unit_tag.c_str(), WS_CHILD | WS_VISIBLE, tagRect, view);
         }

         virtual void DestroyEditControl() override
         {
            auto ipedit = std::dynamic_pointer_cast<iInplaceEditable>(m_EditableTextBlock);
            ipedit->DestroyEditControl();
            m_pctlUnitTag->DestroyWindow();
         }

         virtual bool ValidateData() override
         {
            auto ipedit = std::dynamic_pointer_cast<iInplaceEditable>(m_EditableTextBlock);
            return ipedit->ValidateData();
         }

         virtual void OnDataChanged() override
         {
            auto ipedit = std::dynamic_pointer_cast<iInplaceEditable>(m_EditableTextBlock);
            ipedit->OnDataChanged();
         }

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
         virtual bool OnLButtonDown(UINT nFlags, const POINT & point) override
         {
            // Confirm this point is really over the text block
            // Text blocks are often aggregated with other objects. The
            // LButtonDown event could have occurred over the other display object
            // and been forwarded here. The edit task should not begin if
            // the mouse was not pressed over the text.
            auto map = m_EditableTextBlock->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

            auto p = map->LPtoWP(point.x, point.y);

            // Hit test the text block
            if (HitTest(point))
            {
               DoInplaceEdit();
               return true;
            }
            else
            {
               return false;
            }
         }

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
         virtual void SetText(LPCTSTR lpszText) override
         {
            m_EditableTextBlock->SetText(lpszText); // update the real display object         
         }

         virtual CString GetText() const override
         {
            return AsString(false).c_str();
         }

         virtual void SetFont(const LOGFONT & font) override { m_EditableTextBlock->SetFont(font); }
         virtual LOGFONT GetFont() const override { return m_EditableTextBlock->GetFont(); }
         virtual void SetTextColor(COLORREF color) override { m_EditableTextBlock->SetTextColor(color); }
         virtual COLORREF GetTextColor() const override { return m_EditableTextBlock->GetTextColor(); }
         virtual void SetBkColor(COLORREF color) override { m_EditableTextBlock->SetBkColor(color); }
         virtual COLORREF GetBkColor() const override { return m_EditableTextBlock->GetBkColor(); }
         virtual void SetBkMode(int bkMode) override { m_EditableTextBlock->SetBkMode(bkMode); }
         virtual int GetBkMode() const override { return m_EditableTextBlock->GetBkMode(); }

      protected:
         virtual CDisplayView* GetDisplayView() override
         {
            return m_EditableTextBlock->GetDisplayList()->GetDisplayMgr()->GetView();
         }

         virtual CInplaceEdit* GetEditObject() override
         {
            auto editable = std::dynamic_pointer_cast<EditableTextBlock>(m_EditableTextBlock);
            return editable->GetEditObject();
         }
         
         virtual std::shared_ptr<iInplaceEditable> GetInplaceEditable() override
         {
            return std::dynamic_pointer_cast<iInplaceEditable>(shared_from_this());
         }

         private:
            const T& m_IndirectMeasure;
            std::shared_ptr<EditableTextBlock> m_EditableTextBlock; // Most all of the implementation is delegated here
            std::unique_ptr<CStatic> m_pctlUnitTag;
            Float64 m_Value = 0.0; // Always in system units

            std::shared_ptr<NestedDisplayObjectEventRelay> m_EventRelay;
      };

      DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::LengthData>;
      DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::MomentData>;
      DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::AngleData>;
      DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::StressData>;
      DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::ForceData>;
      DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::TimeData>;
      DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::Length2Data>;
      DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::Length3Data>;
      DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::Length4Data>;
      DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::PerLengthData>;

      using EditableLengthUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::LengthData>;
      using EditableMomentUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::MomentData>;
      using EditableRotationUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::AngleData>;
      using EditableStressUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::StressData>;
      using EditableForceUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::ForceData>;
      using EditableTimeUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::TimeData>;
      using EditableAreaUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::Length2Data>;
      using EditableSectionModulusUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::Length3Data>;
      using EditableMomentOfInertiaUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::Length4Data>;
      using EditableCurvatureUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::PerLengthData>;

      using EditableDeflectionUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::LengthData>;
      using EditableShearUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::ForceData>;
      using EditableAxialUnitValueTextBlock = EditableUnitValueTextBlock<WBFL::Units::ForceData>;
   };
};
