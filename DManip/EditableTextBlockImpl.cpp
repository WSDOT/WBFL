///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

// EditableTextBlock.cpp: implementation of the CEditableTextBlockImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "EditableTextBlockImpl.h"
#include "TextBlockImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define IDC_EDIT 100

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEditableTextBlockImpl::CEditableTextBlockImpl()
{
   m_pEdit = 0;
   m_pFont = NULL;
   m_Format = etbfText;
   m_pOnMouseOverCursor = NULL;
}

CEditableTextBlockImpl::~CEditableTextBlockImpl()
{
}

HRESULT CEditableTextBlockImpl::FinalConstruct()
{
   m_bAutoUpdate = FALSE;

   CComObject<CTextBlockImpl>* pTextBlock;
   HRESULT hr = CComObject<CTextBlockImpl>::CreateInstance(&pTextBlock);
   if ( FAILED(hr) )
      return hr;

   m_TextBlock = pTextBlock;
   m_TextBlock->RegisterEventSink(this);

   return S_OK;
}

void CEditableTextBlockImpl::FinalRelease()
{
   delete m_pEdit;
   m_pEdit = 0;
}

////////////////
// iInplaceEditImpl
STDMETHODIMP_(void) CEditableTextBlockImpl::CreateEditControl()
{
   CString strText;
   strText = GetText();

   LOGFONT font;
   GetFont(&font);

   // make sure the text is horizontal or it wont show up in the edit box
   font.lfEscapement  = 0;
   font.lfOrientation = 0;

   CComPtr<iDisplayList> pDL;
   m_TextBlock->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   CDisplayView* pView = pDispMgr->GetView();

   CDManipClientDC dc(pView);

   m_pFont = new CFont;
   m_pFont->CreatePointFontIndirect(&font);
   CFont* pOldFont = (CFont*)dc.SelectObject(m_pFont);

   CSize extent = (strText != "" ) ? dc.GetTextExtent(strText) : dc.GetTextExtent(_T("ABCDEFG"));
   CSize ctrlSize = extent;
   ctrlSize.cx *= 2; // need to make the edit box wide to accomodate more input
                     // in the future it would be better to get key press events and
                     // resize the text box
   ctrlSize += CSize(6,6); // Put a 3 pixel boundary around the text

   CComPtr<IPoint2d> position;
   GetPosition(&position);
   LONG lx,ly;
   Float64 wx,wy;
   pMap->MPtoWP(position,&wx,&wy);
   pMap->WPtoLP(wx,wy,&lx,&ly);

   UINT horzTextAlign = GetTextAlign() & (TA_LEFT | TA_CENTER| TA_RIGHT);
   if ( horzTextAlign == TA_RIGHT )
      lx -= extent.cx;
   else if ( horzTextAlign == TA_CENTER )
      lx -= extent.cx/2;

   UINT vertTextAlign = GetTextAlign() & (TA_TOP | TA_BOTTOM | TA_BASELINE);
   if ( vertTextAlign == TA_BASELINE || vertTextAlign == TA_BOTTOM )
      ly -= extent.cy;

   CInplaceEdit* pEdit = GetEditObject();
   DWORD dwStyle = WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL | ES_NOHIDESEL;
   if ( m_Format == etbfNumeric )
      dwStyle |= ES_RIGHT;
   else
      dwStyle |= ES_LEFT;

   pEdit->Create(dwStyle,CRect(CPoint(lx,ly),ctrlSize),pView,IDC_EDIT);

   pEdit->SetFont(m_pFont);
   pEdit->SetWindowText(strText);
   pEdit->SetFocus();

   // Select all of the text and don't scroll it
   pEdit->SetSel(0,strText.GetLength(),FALSE);

   pEdit->UpdateWindow();

   dc.SelectObject(pOldFont);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::DestroyEditControl()
{
   CInplaceEdit* pEdit = GetEditObject();

   // Save the value from the edit control before it is destroyed
   pEdit->GetWindowText(m_strCtrlText);

   // Destory the edit control
   pEdit->DestroyWindow();

   // Done with the font object
   delete m_pFont;
   m_pFont = NULL;
}

STDMETHODIMP_(BOOL) CEditableTextBlockImpl::ValidateData()
{
   CInplaceEdit* pEdit = GetEditObject();

   CString strText;
   pEdit->GetWindowText(strText);
   return strText.GetLength() > 0 ? TRUE : FALSE;
}

STDMETHODIMP_(void) CEditableTextBlockImpl::OnDataChanged()
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

   OnChanged(this);
#pragma Reminder("This event isn't forwarded")
   // Here is the problem... The implementation of iDisplayObject is
   // delegated to m_TextBlock. We don't necessarily want to call SetText.
   // Calling SetText is the only way to fire the event.
   //
   // We probably want to implement our own connection point and
   // listen for events from m_TextBlock and forward them
//   Fire_OnChanged();
}

//////////////////////////////////
// iDisplayObject Implementation
STDMETHODIMP_(void) CEditableTextBlockImpl::SetID(IDType id)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->SetID(id);
}

STDMETHODIMP_(IDType) CEditableTextBlockImpl::GetID()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->GetID();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetItemData(void* pItemData,bool bDelete)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->SetItemData(pItemData,bDelete);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::GetItemData(void** ppItemData)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->GetItemData(ppItemData);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetDisplayList(iDisplayList * pDL)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->SetDisplayList(pDL);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::GetDisplayList(iDisplayList** list)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->GetDisplayList(list);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::Visible(BOOL bVisible)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->Visible(bVisible);
}

STDMETHODIMP_(BOOL) CEditableTextBlockImpl::IsVisible()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->IsVisible();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::Draw(CDC* pDC)
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
      CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
      dispObj->Draw(pDC);
   }
}

STDMETHODIMP_(void) CEditableTextBlockImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->Highlite(pDC,bHighlite);
}

#if defined(_DEBUG)
STDMETHODIMP_(void) CEditableTextBlockImpl::DrawGravityWell(CDC* pDC)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->DrawGravityWell(pDC);
}
#endif

STDMETHODIMP_(void) CEditableTextBlockImpl::SetGravityWellStrategy(iGravityWellStrategy* pStrategy)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->SetGravityWellStrategy(pStrategy);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::GetGravityWellStrategy(iGravityWellStrategy** pStrategy)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->GetGravityWellStrategy(pStrategy);
}

STDMETHODIMP_(BOOL) CEditableTextBlockImpl::HitTest(CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->HitTest(point);
}

STDMETHODIMP_(CRect) CEditableTextBlockImpl::GetBoundingBox()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->GetBoundingBox();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::GetBoundingBox(IRect2d** rect)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->GetBoundingBox(rect);
}

STDMETHODIMP_(BOOL) CEditableTextBlockImpl::TouchesRect(CRect r)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->TouchesRect(r);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::Select(BOOL bSelect)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->Select(bSelect);
}

STDMETHODIMP_(BOOL) CEditableTextBlockImpl::IsSelected()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->IsSelected();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetSelectionType(SelectionType st)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->SetSelectionType(st);
}

STDMETHODIMP_(SelectionType) CEditableTextBlockImpl::GetSelectionType()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->GetSelectionType();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetToolTipText(LPCTSTR lpszToolTipText)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->SetToolTipText(lpszToolTipText);
}

STDMETHODIMP_(CString) CEditableTextBlockImpl::GetToolTipText()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->GetToolTipText();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetMaxTipWidth(INT maxWidth)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->SetMaxTipWidth(maxWidth);
}

STDMETHODIMP_(INT) CEditableTextBlockImpl::GetMaxTipWidth()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->GetMaxTipWidth();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetTipDisplayTime(INT iTime)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->SetTipDisplayTime(iTime);
}

STDMETHODIMP_(INT) CEditableTextBlockImpl::GetTipDisplayTime()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->GetTipDisplayTime();
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnLButtonDown(UINT nFlags,CPoint point)
{
   // Confirm this point is really over the text block
   // Text blocks are often aggregated with other objects. The
   // LButtonDown event could have occured over the other display object
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

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnLButtonUp(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->OnLButtonUp(nFlags,point);
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnLButtonDblClk(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->OnLButtonDblClk(nFlags,point);
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnRButtonDown(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->OnRButtonDown(nFlags,point);
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnRButtonUp(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->OnRButtonUp(nFlags,point);
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnRButtonDblClk(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->OnRButtonDblClk(nFlags,point);
}


STDMETHODIMP_(bool) CEditableTextBlockImpl::OnMouseMove(UINT nFlags,CPoint point)
{
   ATLTRACE("EditableTextBlock - OnMouseOver\n");

   if ( m_pOnMouseOverCursor == NULL )
   {
      ATLTRACE("EditableTextBlock - Creating mouse over cursor tracking\n");

      CDisplayView* pView = GetDisplayView();
      HWND hwnd = pView->GetSafeHwnd();

      CRgn rgn;
      CComPtr<iGravityWellStrategy> strategy;
      GetGravityWellStrategy(&strategy);

      if ( strategy )
      {
         strategy->GetGravityWell(this,&rgn);
      }
      else
      {
         CRect box = GetBoundingBox();
         rgn.CreateRectRgnIndirect(box);
      }

      m_pOnMouseOverCursor = new COnMouseOverCursor(hwnd,NULL,IDC_IBEAM,500,&rgn);
      m_pOnMouseOverCursor->StartTracking(&m_pOnMouseOverCursor);
   }
//   else
//   {
//      m_pOnMouseOverCursor->OnMouseMove(nFlags,point);
//   }


   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->OnMouseMove(nFlags,point);
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnMouseWheel(UINT nFlags,short zDelta,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->OnMouseWheel(nFlags,zDelta,point);
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->OnKeyDown(nChar,nRepCnt,nFlags);
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnContextMenu(CWnd* pWnd,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   return dispObj->OnContextMenu(pWnd,point);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::RegisterEventSink(iDisplayObjectEvents* pEventSink)
{
   m_EventSink = pEventSink;
}

STDMETHODIMP_(void) CEditableTextBlockImpl::UnregisterEventSink()
{
   m_EventSink.Release();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::GetEventSink(iDisplayObjectEvents** pEventSink)
{
   *pEventSink = m_EventSink;
   (*pEventSink)->AddRef();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetDropSite(iDropSite* pDropSite)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->SetDropSite(pDropSite);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::GetDropSite(iDropSite** dropSite)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_TextBlock);
   dispObj->GetDropSite(dropSite);
}

///////////////////////////////////////////
// iTextBlock Implementation
STDMETHODIMP_(void) CEditableTextBlockImpl::SetPosition(IPoint2d* pos)
{
   m_TextBlock->SetPosition(pos);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::GetPosition(IPoint2d** pos)
{
   m_TextBlock->GetPosition(pos);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetTextAlign(UINT nFlags)
{
   // Text cannot be changed while inplace editing is active
   CEdit* pEdit = GetEditObject();
   if ( pEdit && ::IsWindow(pEdit->GetSafeHwnd()) )
      return;

   m_TextBlock->SetTextAlign(nFlags);
}

STDMETHODIMP_(UINT) CEditableTextBlockImpl::GetTextAlign()
{
   return m_TextBlock->GetTextAlign();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetAngle(LONG angle)
{
   m_TextBlock->SetAngle(angle);
}

STDMETHODIMP_(LONG) CEditableTextBlockImpl::GetAngle()
{
   return m_TextBlock->GetAngle();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetText(LPCTSTR lpszText)
{
   CInplaceEdit* pEdit = GetEditObject();

   if ( pEdit && ::IsWindow(pEdit->GetSafeHwnd()) )
      return; // don't update text if inplace editing is active
   else
      m_TextBlock->SetText(lpszText);
}

STDMETHODIMP_(CString) CEditableTextBlockImpl::GetText()
{
   CInplaceEdit* pEdit = GetEditObject();

   if ( ::IsWindow(pEdit->GetSafeHwnd()) )
   {
      CString strText;
      pEdit->GetWindowText(strText);
      return strText;
   }

   return m_TextBlock->GetText();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetFont(const LOGFONT& Font)
{
   m_TextBlock->SetFont(Font);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::GetFont(LOGFONT* pFont)
{
   m_TextBlock->GetFont(pFont);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetTextColor(COLORREF color)
{
   m_TextBlock->SetTextColor(color);
}

STDMETHODIMP_(COLORREF) CEditableTextBlockImpl::GetTextColor()
{
   return m_TextBlock->GetTextColor();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetBkColor(COLORREF color)
{
   m_TextBlock->SetBkColor(color);
}

STDMETHODIMP_(COLORREF) CEditableTextBlockImpl::GetBkColor()
{
   return m_TextBlock->GetBkColor();
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetBkMode(int bkMode)
{
   m_TextBlock->SetBkMode(bkMode);
}

STDMETHODIMP_(int) CEditableTextBlockImpl::GetBkMode()
{
   return m_TextBlock->GetBkMode();
}

/////////////////////////////////
// iEditableTextBlock Implementation
STDMETHODIMP_(void) CEditableTextBlockImpl::EnableAutoUpdate(BOOL bEnable)
{
   m_bAutoUpdate = bEnable;
}

STDMETHODIMP_(BOOL) CEditableTextBlockImpl::IsAutoUpdateEnabled()
{
   return m_bAutoUpdate;
}

STDMETHODIMP_(CString) CEditableTextBlockImpl::GetEditedText()
{
   return m_strCtrlText;
}

STDMETHODIMP_(void) CEditableTextBlockImpl::SetFormat(EditableTextBlockFormatType format)
{
   if ( m_Format != format )
   {
      m_Format = format;
      delete m_pEdit;
      m_pEdit = 0;
   }

}

STDMETHODIMP_(EditableTextBlockFormatType) CEditableTextBlockImpl::GetFormat()
{
   return m_Format;
}

////////////////////////////////////////////////
// iDisplayObjectEvents
STDMETHODIMP_(bool) CEditableTextBlockImpl::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonDblClk(pDO,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonDown(pDO,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonUp(pDO,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonDblClk(pDO,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonDown(pDO,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonUp(pDO,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnMouseMove(pDO,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnMouseWheel(pDO,nFlags,zDelta,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnKeyDown(pDO,nChar,nRepCnt,nFlags);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableTextBlockImpl::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnContextMenu(this,pWnd,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(void) CEditableTextBlockImpl::OnChanged(iDisplayObject* pDO)
{
   if ( m_EventSink )
      m_EventSink->OnChanged(pDO);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::OnDragMoved(iDisplayObject* pDO,ISize2d* offset)
{
   if ( m_EventSink )
      m_EventSink->OnDragMoved(pDO,offset);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::OnMoved(iDisplayObject* pDO)
{
   if ( m_EventSink )
      m_EventSink->OnMoved(pDO);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::OnCopied(iDisplayObject* pDO)
{
   if ( m_EventSink )
      m_EventSink->OnCopied(pDO);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::OnSelect(iDisplayObject* pDO)
{
   ASSERT(m_TextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
      m_EventSink->OnSelect(this);
}

STDMETHODIMP_(void) CEditableTextBlockImpl::OnUnselect(iDisplayObject* pDO)
{
   ASSERT(m_TextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
      m_EventSink->OnUnselect(this);
}

/////////////////////////////////////////////////
CDisplayView* CEditableTextBlockImpl::GetDisplayView()
{
   CComPtr<iDisplayList> pDL;
   m_TextBlock->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   return pDispMgr->GetView();
}

CInplaceEdit* CEditableTextBlockImpl::GetEditObject()
{
   if ( m_pEdit == NULL )
   {
      m_pEdit = (m_Format == etbfText ? new CInplaceEdit : new CInplaceNumericEdit);
   }

   return m_pEdit;
}
