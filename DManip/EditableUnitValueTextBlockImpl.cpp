///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// EditableUnitValueTextBlock.cpp: implementation of the CEditableUnitValueTextBlockImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "EditableUnitValueTextBlockImpl.h"
#include "EditableTextBlockImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define IDC_EDIT 100

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEditableUnitValueTextBlockImpl::CEditableUnitValueTextBlockImpl()
{
   m_Value = 0.0;
   m_pctlUnitTag = 0;
   m_bIsStation = false;
}

CEditableUnitValueTextBlockImpl::~CEditableUnitValueTextBlockImpl()
{
}

HRESULT CEditableUnitValueTextBlockImpl::FinalConstruct()
{
   CComObject<CEditableTextBlockImpl>* pTextBlock;
   HRESULT hr = CComObject<CEditableTextBlockImpl>::CreateInstance(&pTextBlock);
   if ( FAILED(hr) )
      return hr;

   m_EditableTextBlock = pTextBlock;
   m_EditableTextBlock->RegisterEventSink(this);

   m_EditableTextBlock->SetFormat(etbfNumeric);
   CString str;
   str.Format(_T("%f"),m_Value);
   m_EditableTextBlock->SetText(str);

   m_pctlUnitTag = new CStatic;

   return S_OK;
}

void CEditableUnitValueTextBlockImpl::FinalRelease()
{
   m_EditableTextBlock->UnregisterEventSink();
   m_EditableTextBlock.Release();

   delete m_pctlUnitTag;
   m_pctlUnitTag = NULL;

   m_UnitSystem.Release();
}

////////////////
// iInplaceEditImpl
STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::CreateEditControl()
{
   CComQIPtr<iInplaceEditable,&IID_iInplaceEditable> ipedit(m_EditableTextBlock);
   ipedit->CreateEditControl();

   // Replace the text in the edit control with the value in display units, without
   // the unit tag...
   CInplaceEdit* pEdit = GetEditObject();

   if ( !m_bIsStation )
   {
      CComBSTR bstrText;
      m_UnitSystem->Format(m_Value,m_bstrDisplayUnitGroup,VARIANT_FALSE,&bstrText);
      CString strText(bstrText);
      pEdit->SetWindowText(strText);
      pEdit->SetSel(0,strText.GetLength(),TRUE);
      pEdit->UpdateWindow();
   }

   // Make sure text is right justified
   pEdit->ModifyStyle(ES_LEFT | ES_CENTER, ES_RIGHT);

   // Drill up to the view and create a dc so that we can get the size of the tag
   // with that, we can make the static control the right size
   CComPtr<iDisplayList> pDL;
   m_EditableTextBlock->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CDisplayView* pView = pDispMgr->GetView();
   CDManipClientDC dc(pView);

   CComBSTR bstrTag;
   m_UnitSystem->get_Tag(m_bstrDisplayUnitGroup,&bstrTag);
   CString strTag(bstrTag);
   CSize tagExtents = dc.GetTextExtent(strTag);

   // now, place a static control after the edit control and put the unit tag in it
   CRect editRect;
   pEdit->GetWindowRect(&editRect);

   CRect tagRect;
   tagRect.left = editRect.right;
   tagRect.right = tagRect.left + tagExtents.cx;
   tagRect.top = editRect.top;
   tagRect.bottom = editRect.bottom;
   if ( tagRect.Height() < tagExtents.cy )
      tagRect.bottom = tagRect.top + tagExtents.cy;

   pView->ScreenToClient(&tagRect);

   m_pctlUnitTag->Create(strTag,WS_CHILD | WS_VISIBLE,tagRect,pView);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::DestroyEditControl()
{
   CComQIPtr<iInplaceEditable,&IID_iInplaceEditable> ipedit(m_EditableTextBlock);
   ipedit->DestroyEditControl();

   m_pctlUnitTag->DestroyWindow();
}

STDMETHODIMP_(BOOL) CEditableUnitValueTextBlockImpl::ValidateData()
{
   if ( m_bIsStation )
   {
      UnitModeType unitMode;
      m_UnitSystem->get_UnitMode(&unitMode);

      HRESULT hr = m_Station->FromString(CComBSTR(m_EditableTextBlock->GetText()),unitMode);
      return SUCCEEDED(hr) ? TRUE : FALSE;
   }
   else
   {
      CComQIPtr<iInplaceEditable,&IID_iInplaceEditable> ipedit(m_EditableTextBlock);
      return ipedit->ValidateData();
   }
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::OnDataChanged()
{
   CComQIPtr<iInplaceEditable,&IID_iInplaceEditable> ipedit(m_EditableTextBlock);
   ipedit->OnDataChanged();

//   OnChanged(this);
#pragma Reminder("This event isn't forwarded")
   // Here is the problem... The implementation of iDisplayObject is
   // delegated to m_EditableTextBlock. We don't necessarily want to call SetText.
   // Calling SetText is the only way to fire the event.
   //
   // We probably want to implement our own connection point and
   // listen for events from m_EditableTextBlock and forward them
//   Fire_OnChanged();
}

//////////////////////////////////
// iDisplayObject Implementation
STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetID(IDType id)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->SetID(id);
}

STDMETHODIMP_(IDType) CEditableUnitValueTextBlockImpl::GetID()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->GetID();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetDisplayList(iDisplayList * pDL)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->SetDisplayList(pDL);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetItemData(void* pItemData,bool bDelete)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->SetItemData(pItemData,bDelete);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::GetItemData(void** ppItemData)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->GetItemData(ppItemData);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::GetDisplayList(iDisplayList** list)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->GetDisplayList(list);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::Visible(BOOL bVisible)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->Visible(bVisible);
}

STDMETHODIMP_(BOOL) CEditableUnitValueTextBlockImpl::IsVisible()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->IsVisible();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::Draw(CDC* pDC)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->Draw(pDC);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->Highlite(pDC,bHighlite);
}

#if defined(_DEBUG)
STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::DrawGravityWell(CDC* pDC)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->DrawGravityWell(pDC);
}
#endif 

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetGravityWellStrategy(iGravityWellStrategy* pStrategy)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->SetGravityWellStrategy(pStrategy);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::GetGravityWellStrategy(iGravityWellStrategy** pStrategy)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->GetGravityWellStrategy(pStrategy);
}

STDMETHODIMP_(BOOL) CEditableUnitValueTextBlockImpl::HitTest(CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->HitTest(point);
}

STDMETHODIMP_(CRect) CEditableUnitValueTextBlockImpl::GetBoundingBox()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->GetBoundingBox();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::GetBoundingBox(IRect2d** rect)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->GetBoundingBox(rect);
}

STDMETHODIMP_(BOOL) CEditableUnitValueTextBlockImpl::TouchesRect(CRect r)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->TouchesRect(r);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::Select(BOOL bSelect)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->Select(bSelect);
}

STDMETHODIMP_(BOOL) CEditableUnitValueTextBlockImpl::IsSelected()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->IsSelected();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetSelectionType(SelectionType st)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->SetSelectionType(st);
}

STDMETHODIMP_(SelectionType) CEditableUnitValueTextBlockImpl::GetSelectionType()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->GetSelectionType();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetToolTipText(LPCTSTR lpszToolTipText)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->SetToolTipText(lpszToolTipText);
}

STDMETHODIMP_(CString) CEditableUnitValueTextBlockImpl::GetToolTipText()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->GetToolTipText();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetMaxTipWidth(INT maxWidth)
{ 
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->SetMaxTipWidth(maxWidth);
}

STDMETHODIMP_(INT) CEditableUnitValueTextBlockImpl::GetMaxTipWidth()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->GetMaxTipWidth();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetTipDisplayTime(INT iTime)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->SetTipDisplayTime(iTime);
}

STDMETHODIMP_(INT) CEditableUnitValueTextBlockImpl::GetTipDisplayTime()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->GetTipDisplayTime();
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnLButtonDown(UINT nFlags,CPoint point)
{
   // Confirm this point is really over the text block
   // Text blocks are often aggregated with other objects. The
   // LButtonDown event could have occured over the other display object
   // and been forwarded here. The edit task should not begin if
   // the mouse was not pressed over the text.
   CComPtr<iDisplayList> pDL;
   m_EditableTextBlock->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   CComPtr<IPoint2d> p;
   pMap->LPtoWP(point.x,point.y,&p);

   // Hit test the text block
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

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnLButtonUp(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->OnLButtonUp(nFlags,point);
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnLButtonDblClk(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->OnLButtonDblClk(nFlags,point);
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnRButtonDown(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->OnRButtonDown(nFlags,point);
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnRButtonUp(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->OnRButtonUp(nFlags,point);
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnRButtonDblClk(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->OnRButtonDblClk(nFlags,point);
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnMouseMove(UINT nFlags,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->OnMouseMove(nFlags,point);
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnMouseWheel(UINT nFlags,short zDelta,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->OnMouseWheel(nFlags,zDelta,point);
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->OnKeyDown(nChar,nRepCnt,nFlags);
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnContextMenu(CWnd* pWnd,CPoint point)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   return dispObj->OnContextMenu(pWnd,point);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::RegisterEventSink(iDisplayObjectEvents* pEventSink)
{
   UnregisterEventSink();

   m_EventSink = pEventSink;
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::UnregisterEventSink()
{
   m_EventSink.Release();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::GetEventSink(iDisplayObjectEvents** pEventSink)
{
   *pEventSink = m_EventSink;
   (*pEventSink)->AddRef();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::RegisterDropSite(iDropSite* pDropSite)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->RegisterDropSite(pDropSite);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::UnregisterDropSite()
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->UnregisterDropSite();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::GetDropSite(iDropSite** dropSite)
{
   CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_EditableTextBlock);
   dispObj->GetDropSite(dropSite);
}

///////////////////////////////////////////
// iTextBlock Implementation
STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetPosition(IPoint2d* pos)
{
   m_EditableTextBlock->SetPosition(pos);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::GetPosition(IPoint2d** pos)
{
   m_EditableTextBlock->GetPosition(pos);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetTextAlign(UINT nFlags)
{
   m_EditableTextBlock->SetTextAlign(nFlags);
}

STDMETHODIMP_(UINT) CEditableUnitValueTextBlockImpl::GetTextAlign()
{
   return m_EditableTextBlock->GetTextAlign();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetAngle(LONG angle)
{
   m_EditableTextBlock->SetAngle(angle);
}

STDMETHODIMP_(LONG) CEditableUnitValueTextBlockImpl::GetAngle()
{
   return m_EditableTextBlock->GetAngle();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetText(LPCTSTR lpszText)
{
   // Convert the inbound string to a value... inbound value is in base units
   m_Value = _wtof(lpszText);
   CString strText = GetText(); // converts it to a display string

   m_EditableTextBlock->SetText(strText); // update the real display object
}

STDMETHODIMP_(CString) CEditableUnitValueTextBlockImpl::GetText()
{
   CComBSTR bstrText;
   m_UnitSystem->Format(m_Value,m_bstrDisplayUnitGroup,VARIANT_TRUE,&bstrText);
   return CString(bstrText);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetFont(const LOGFONT& Font)
{
   m_EditableTextBlock->SetFont(Font);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::GetFont(LOGFONT* pFont)
{
   m_EditableTextBlock->GetFont(pFont);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetTextColor(COLORREF color)
{
   m_EditableTextBlock->SetTextColor(color);
}

STDMETHODIMP_(COLORREF) CEditableUnitValueTextBlockImpl::GetTextColor()
{
   return m_EditableTextBlock->GetTextColor();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetBkColor(COLORREF color)
{
   m_EditableTextBlock->SetBkColor(color);
}

STDMETHODIMP_(COLORREF) CEditableUnitValueTextBlockImpl::GetBkColor()
{
   return m_EditableTextBlock->GetBkColor();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetBkMode(int bkMode)
{
   m_EditableTextBlock->SetBkMode(bkMode);
}

STDMETHODIMP_(int) CEditableUnitValueTextBlockImpl::GetBkMode()
{
   return m_EditableTextBlock->GetBkMode();
}

/////////////////////////////////
// iEditableUnitValueTextBlock Implementation
STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::EnableAutoUpdate(BOOL bEnable)
{
   m_EditableTextBlock->EnableAutoUpdate(bEnable);
}

STDMETHODIMP_(BOOL) CEditableUnitValueTextBlockImpl::IsAutoUpdateEnabled()
{
   return m_EditableTextBlock->IsAutoUpdateEnabled();
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetUnitSystem(IDocUnitSystem* docUnitSystem)
{
   m_UnitSystem = docUnitSystem;
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetDisplayUnitGroupName(LPCTSTR strGroupName)
{
   m_bstrDisplayUnitGroup = strGroupName;
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::SetValue(Float64 value)
{
   m_Value = value;
   CString strValue;
   strValue.Format(_T("%f"),value);
   SetText(strValue);
}

STDMETHODIMP_(Float64) CEditableUnitValueTextBlockImpl::GetValue()
{
   return m_Value;
}

STDMETHODIMP_(Float64) CEditableUnitValueTextBlockImpl::GetEditedValue()
{
   Float64 editedValue;
   if ( m_bIsStation )
   {
      // value is in station format... need to make it a Float64
      UnitModeType unitMode;
      m_UnitSystem->get_UnitMode(&unitMode);

      HRESULT hr = m_Station->FromString(CComBSTR(m_EditableTextBlock->GetEditedText()),unitMode);
      ATLASSERT(SUCCEEDED(hr));
      
      m_Station->get_Value(&editedValue);
   }
   else
   {
      editedValue = _wtof(m_EditableTextBlock->GetEditedText()); // value in display units (without unit tag)
   }

   // Convert back to base units
   m_UnitSystem->ConvertFromDisplayUnits(editedValue,m_bstrDisplayUnitGroup,&editedValue);

   return editedValue;
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::IsStation()
{
   return m_bIsStation;
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::IsStation(bool bIsStation)
{
   if ( m_bIsStation != bIsStation )
   {
      m_bIsStation = bIsStation;
      m_EditableTextBlock->SetFormat(m_bIsStation ? etbfText : etbfNumeric);

      if ( m_bIsStation && m_Station == NULL )
         m_Station.CoCreateInstance(CLSID_Station);
   }
}

////////////////////////////////////////////////
// iDisplayObjectEvents
STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonDblClk(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonDown(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonUp(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonDblClk(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonDown(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonUp(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));
#pragma Reminder("Fix this assert")

   if ( m_EventSink )
   {
      return m_EventSink->OnMouseMove(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnMouseWheel(this,nFlags,zDelta,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
   {
      return m_EventSink->OnKeyDown(this,nChar,nRepCnt,nFlags);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CEditableUnitValueTextBlockImpl::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
   {
      return m_EventSink->OnContextMenu(this,pWnd,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::OnChanged(iDisplayObject* pDO)
{
   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
      m_EventSink->OnChanged(this);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::OnDragMoved(iDisplayObject* pDO,ISize2d* offset)
{
   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
      m_EventSink->OnDragMoved(this,offset);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::OnMoved(iDisplayObject* pDO)
{
   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
      m_EventSink->OnMoved(this);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::OnCopied(iDisplayObject* pDO)
{
   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
      m_EventSink->OnCopied(this);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::OnSelect(iDisplayObject* pDO)
{
   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
      m_EventSink->OnSelect(this);
}

STDMETHODIMP_(void) CEditableUnitValueTextBlockImpl::OnUnselect(iDisplayObject* pDO)
{
   ASSERT(m_EditableTextBlock.IsEqualObject(pDO));

   if ( m_EventSink )
      m_EventSink->OnUnselect(this);
}

/////////////////////////////////////////////////
CDisplayView* CEditableUnitValueTextBlockImpl::GetDisplayView()
{
   CEditableTextBlockImpl* pEditableTextBlock = dynamic_cast<CEditableTextBlockImpl*>(m_EditableTextBlock.p);
   return pEditableTextBlock->GetDisplayView();
}

CInplaceEdit* CEditableUnitValueTextBlockImpl::GetEditObject()
{
   CEditableTextBlockImpl* pEditableTextBlock = dynamic_cast<CEditableTextBlockImpl*>(m_EditableTextBlock.p);
   return pEditableTextBlock->GetEditObject();
}
