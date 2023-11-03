///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include "stdafx.h"
#include "IEReportView.h"
#include "WBCmdGroup.h" // magical cmd_ids for find

IEReportView::IEReportView()
{
   m_pWebBrowser = std::make_unique<CWebBrowser>();
}

BOOL IEReportView::Create(
   LPCTSTR lpszWindowName,
   DWORD dwStyle,
   const RECT& rect,
   HWND hwndParent,
   UINT nID)
{
   //AFX_MANAGE_STATE(AfxGetAppModuleState());
   CWnd* pWnd = CWnd::FromHandle(hwndParent);
   return m_pWebBrowser->Create(lpszWindowName, dwStyle, rect, pWnd, nID);
}

void IEReportView::FitToParent()
{
   CWnd* pParent = m_pWebBrowser->GetParent();
   CRect rect;
   pParent->GetClientRect(&rect);
   m_pWebBrowser->SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
}

void IEReportView::Move(POINT topLeft)
{
   m_pWebBrowser->SetWindowPos(nullptr, topLeft.x, topLeft.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void IEReportView::Size(SIZE size)
{
   m_pWebBrowser->SetWindowPos(nullptr, 0, 0, size.cx, size.cy, SWP_NOZORDER | SWP_NOMOVE);
}

void IEReportView::Print(bool bPrompt)
{
#pragma Reminder("WORKING HERE - Report Viewer Printing")
   // Build footer string
   //std::_tstring lftFoot = m_pRptSpec->GetLeftFooter();
   //std::_tstring ctrFoot = m_pRptSpec->GetCenterFooter();
   CString footer;
   //footer.Format(_T("%s&b%s&b&d"), lftFoot.c_str(), ctrFoot.c_str());

   // Build Header string
   //std::_tstring lftHead = m_pRptSpec->GetLeftHeader();
   //std::_tstring ctrHead = m_pRptSpec->GetCenterHeader();
   CString header;
   //header.Format(_T("%s&b%s&bPage &p of &P"), lftHead.c_str(), ctrHead.c_str());

   // Print from browser
   m_pWebBrowser->Print(header, footer);
}

void IEReportView::Find()
{
   LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   IOleCommandTarget* pIOleCmdTarget;
   if (S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget))
   {
      pIOleCmdTarget->Exec(&CGID_IWebBrowserPriv, CWBCmdGroup::HTMLID_FIND, 0, nullptr, nullptr);
      pIOleCmdTarget->Release();
   }
}

void IEReportView::SelectAll()
{
   LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   IOleCommandTarget* pIOleCmdTarget;
   if (S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget))
   {
      pIOleCmdTarget->Exec(nullptr, OLECMDID_SELECTALL, OLECMDEXECOPT_DODEFAULT, nullptr, nullptr);
      pIOleCmdTarget->Release();
   }
}

void IEReportView::Copy()
{
   LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   IOleCommandTarget* pIOleCmdTarget;
   if (S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget))
   {
      pIOleCmdTarget->Exec(nullptr, OLECMDID_COPY, OLECMDEXECOPT_DODEFAULT, nullptr, nullptr);
      pIOleCmdTarget->Release();
   }
}

void IEReportView::Refresh()
{
   m_pWebBrowser->Refresh();
}

void IEReportView::ViewSource()
{
   LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   IOleCommandTarget* pIOleCmdTarget;
   if (S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget))
   {
      pIOleCmdTarget->Exec(&CGID_IWebBrowserPriv, CWBCmdGroup::HTMLID_VIEWSOURCE, 0, nullptr, nullptr);
      pIOleCmdTarget->Release();
   }
}

void IEReportView::Back()
{
   m_pWebBrowser->GoBack();
}

void IEReportView::Forward()
{
   m_pWebBrowser->GoForward();
}

void IEReportView::Navigate(LPCTSTR uri)
{
   m_pWebBrowser->Navigate(uri);
}
