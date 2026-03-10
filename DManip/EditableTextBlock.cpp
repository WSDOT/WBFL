///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include "pch.h"
#include <DManip/EditableTextBlock.h>
#include <DManip/TextBlockImpl.h>
#include <DManip/InplaceEditCtrl.h>
#include <DManip/InplaceNumericEditCtrl.h>
#include <DManip/DisplayMgr.h>
#include <DManip/DisplayView.h>
#include <DManip/InplaceEdit.h>
#include "OnMouseOverCursor.h"

#define IDC_EDIT 100

using namespace WBFL::DManip;

EditableTextBlock::EditableTextBlock(IDType id) : iTextBlock(id)
{
   m_TextBlock = TextBlock::Create();
}

void EditableTextBlock::Init()
{
   m_EventRelay = NestedDisplayObjectEventRelay::Create(this);
   m_TextBlock->RegisterEventSink(m_EventRelay);
}

std::shared_ptr<EditableTextBlock> EditableTextBlock::Create(IDType id) 
{ 
   auto editable_text_block = std::shared_ptr<EditableTextBlock>(new EditableTextBlock(id)); 
   editable_text_block->Init();
   return editable_text_block;
}

EditableTextBlock::~EditableTextBlock()
{
   m_TextBlock->UnregisterDropSite();
   delete m_pEdit;
}

////////////////
// iInplaceEditImpl
void EditableTextBlock::CreateEditControl()
{
   CString strText;
   strText = GetText();

   LOGFONT font = GetFont();

   // make sure the text is horizontal or it wont show up in the edit box
   font.lfEscapement  = 0;
   font.lfOrientation = 0;

   auto map = m_TextBlock->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();
   auto view = m_TextBlock->GetDisplayList()->GetDisplayMgr()->GetView();

   CDManipClientDC dc(view);

   m_pFont = new CFont;
   m_pFont->CreatePointFontIndirect(&font);
   CFont* pOldFont = (CFont*)dc.SelectObject(m_pFont);

   CSize extent = (strText != "" ) ? dc.GetTextExtent(strText) : dc.GetTextExtent(_T("ABCDEFG"));
   CSize ctrlSize = extent;
   ctrlSize.cx *= 2; // need to make the edit box wide to accommodate more input
                     // in the future it would be better to get key press events and
                     // resize the text box
   ctrlSize += CSize(6,6); // Put a 3 pixel boundary around the text

   auto position = GetPosition();
   LONG lx,ly;
   auto wp = map->MPtoWP(position);
   map->WPtoLP(wp.X(),wp.Y(), &lx, &ly);

   UINT horzTextAlign = GetTextAlign() & (TA_LEFT | TA_CENTER| TA_RIGHT);
   if ( horzTextAlign == TA_RIGHT )
      lx -= extent.cx;
   else if ( horzTextAlign == TA_CENTER )
      lx -= extent.cx/2;

   UINT vertTextAlign = GetTextAlign() & (TA_TOP | TA_BOTTOM | TA_BASELINE);
   if ( vertTextAlign == TA_BASELINE || vertTextAlign == TA_BOTTOM )
      ly -= extent.cy;

   CInplaceEdit* pEdit = GetEditObject();
   DWORD dwStyle = WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL;
   if ( m_Format == Format::Numeric )
      dwStyle |= ES_RIGHT;
   else
      dwStyle |= ES_LEFT;

   pEdit->Create(dwStyle,CRect(CPoint(lx,ly),ctrlSize),view,IDC_EDIT);

   pEdit->SetFont(m_pFont);
   pEdit->SetWindowText(strText);
   pEdit->SetFocus();

   // Select all of the text and don't scroll it
   pEdit->SetSel(0,strText.GetLength(),FALSE);

   dc.SelectObject(pOldFont);
}

void EditableTextBlock::DestroyEditControl()
{
   CInplaceEdit* pEdit = GetEditObject();

   // Save the value from the edit control before it is destroyed
   pEdit->GetWindowText(m_strCtrlText);

   // Destory the edit control
   pEdit->DestroyWindow();

   // Done with the font object
   delete m_pFont;
   m_pFont = nullptr;
}

bool EditableTextBlock::ValidateData()
{
   CInplaceEdit* pEdit = GetEditObject();

   CString strText;
   pEdit->GetWindowText(strText);
   return 0 < strText.GetLength();
}

void EditableTextBlock::OnDataChanged()
{
   CInplaceEdit* pEdit = GetEditObject();

   if ( m_bAutoUpdate )
   {
      CString strText;
      if ( ::IsWindow(pEdit->GetSafeHwnd()) )
         pEdit->GetWindowText(strText);
      else
         strText = m_strCtrlText;

      SetText(strText);
   }

   Fire_OnChanged();
}

//////////////////////////////////
// iDisplayObject Implementation

void EditableTextBlock::Draw(CDC* pDC)
{
   CInplaceEdit* pEdit = GetEditObject();
   if ( pEdit && ::IsWindow(pEdit->GetSafeHwnd()) )
   {
      // If we are in inplace edit mode... simply have the edit control redraw itself
      pEdit->UpdateWindow();
   }
   else
   {
      // Otherwise delegate.
      m_TextBlock->Draw(pDC);
   }
}

bool EditableTextBlock::OnLButtonDown(UINT nFlags,const POINT& point)
{
   // Confirm this point is really over the text block
   // Text blocks are often aggregated with other objects. The
   // LButtonDown event could have occurred over the other display object
   // and been forwarded here. The edit task should not begin if
   // the mouse was not pressed over the text.
   if ( HitTest(point) )
   {
      DoInplaceEdit();
      return true;
   }
   else
   {
      return false;
   }
}

bool EditableTextBlock::OnMouseMove(UINT nFlags,const POINT& point)
{
   ATLTRACE("EditableTextBlock - OnMouseOver\n");

   if ( m_pOnMouseOverCursor == nullptr )
   {
      ATLTRACE("EditableTextBlock - Creating mouse over cursor tracking\n");

      CDisplayView* pView = GetDisplayView();
      HWND hwnd = pView->GetSafeHwnd();

      CRgn rgn;
      auto strategy = GetGravityWellStrategy();

      if ( strategy )
      {
         strategy->GetGravityWell(shared_from_this(), &rgn);
      }
      else
      {
         CRect box = GetLogicalBoundingBox();
         rgn.CreateRectRgnIndirect(box);
      }

      m_pOnMouseOverCursor = new COnMouseOverCursor(hwnd,nullptr,IDC_IBEAM,500,&rgn);
      m_pOnMouseOverCursor->StartTracking(&m_pOnMouseOverCursor);
   }

   return m_TextBlock->OnMouseMove(nFlags, point);
}

///////////////////////////////////////////
// iTextBlock Implementation
void EditableTextBlock::SetTextAlign(UINT nFlags)
{
   // Text cannot be changed while inplace editing is active
   CEdit* pEdit = GetEditObject();
   if ( pEdit && ::IsWindow(pEdit->GetSafeHwnd()) )
      return;

   m_TextBlock->SetTextAlign(nFlags);
}

void EditableTextBlock::SetText(LPCTSTR lpszText)
{
   CInplaceEdit* pEdit = GetEditObject();

   if ( pEdit && ::IsWindow(pEdit->GetSafeHwnd()) )
      return; // don't update text if inplace editing is active
   else
      m_TextBlock->SetText(lpszText);
}

CString EditableTextBlock::GetText() const
{
   CInplaceEdit* pEdit = const_cast<EditableTextBlock*>(this)->GetEditObject();

   if ( ::IsWindow(pEdit->GetSafeHwnd()) )
   {
      CString strText;
      pEdit->GetWindowText(strText);
      return strText;
   }

   return m_TextBlock->GetText();
}

/////////////////////////////////
// iEditableTextBlock Implementation
void EditableTextBlock::EnableAutoUpdate(bool bEnable)
{
   m_bAutoUpdate = bEnable;
}

bool EditableTextBlock::IsAutoUpdateEnabled() const
{
   return m_bAutoUpdate;
}

CString EditableTextBlock::GetEditedText() const
{
   return m_strCtrlText;
}

void EditableTextBlock::SetFormat(Format format)
{
   if ( m_Format != format )
   {
      m_Format = format;
      delete m_pEdit;
      m_pEdit = 0;
   }

}

EditableTextBlock::Format EditableTextBlock::GetFormat() const
{
   return m_Format;
}

/////////////////////////////////////////////////
CDisplayView* EditableTextBlock::GetDisplayView()
{
   return m_TextBlock->GetDisplayList()->GetDisplayMgr()->GetView();
}

CInplaceEdit* EditableTextBlock::GetEditObject()
{
   if ( m_pEdit == nullptr )
   {
      m_pEdit = (m_Format == Format::Text ? new CInplaceEdit : new CInplaceNumericEdit);
   }

   return m_pEdit;
}

std::shared_ptr<iInplaceEditable> EditableTextBlock::GetInplaceEditable()
{
   return std::dynamic_pointer_cast<iInplaceEditable>(shared_from_this());
}
