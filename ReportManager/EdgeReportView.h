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

#pragma once

#include <ReportManager\IReportView.h>

#include <wrl.h>
#include <wil/com.h>
#include "WebView2.h"
#include "WebView2EnvironmentOptions.h"
#include <Reporter\HtmlHelper.h>
#include <ReportManager\ReportBrowser.h>

class EdgeReportView : public WBFL::Reporting::IReportView
{
public:
   EdgeReportView(WBFL::Reporting::ReportBrowser* parentReportBrowser);

   virtual ~EdgeReportView() {;}

   virtual BOOL Create(
      LPCTSTR lpszWindowName,
      DWORD dwStyle,
      const RECT& rect,
      HWND hwndParent,
      UINT nID) override;

   HRESULT OnCreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* environment);

   virtual void FitToParent() override;
   virtual void Move(POINT topLeft) override;
   virtual void Size(SIZE size) override;
   virtual void Print(bool bPrompt) override;
   virtual void Find() override;
   virtual void SelectAll() override;
   virtual void Copy() override;
   virtual void Refresh() override;
   virtual void ViewSource() override;
   virtual void Back() override;
   virtual void Forward() override;
   virtual void Navigate(LPCTSTR uri) override;

   // Table of Contents context menu (different than Internet Explorer)
   // The IE browser builds its table of contents from the HTML DOM in custsite.cpp
   // The Edge WebView2 object does not have a C++ interface to the DOM, so the only browser-based method is really 
   // messy asyncronous jscript calls, that will result in nasty bugs, I beleive.
   // So we will build the TOC directly in C++ and pass it to this class

   void SetTableOfContents(const std::vector<rptHtmlReportVisitor::ChapterTocItem>& tableOfContents);

   void OnEdit() { m_pParentReportBrowser->Edit(true); }

private:
   WBFL::Reporting::ReportBrowser* m_pParentReportBrowser; // need access to our parents functions
   HWND m_hwndParent; // handle of parent window
   std::_tstring m_strRawURI; // caches the URI of file

   // Pointer to WebView window
   wil::com_ptr<ICoreWebView2> m_webview;

   // The following is state that belongs with the webview, and should
   // be reinitialized along with it. Everything here is undefined when
   // m_webView is null.
   wil::com_ptr<ICoreWebView2Environment> m_webViewEnvironment;
   wil::com_ptr<ICoreWebView2Controller> m_webviewController;
   wil::com_ptr<ICoreWebView2ContextMenuItem> m_tableOfContentsSubMenuItem;

   EventRegistrationToken m_contextMenuRequestedToken;

   std::vector<rptHtmlReportVisitor::ChapterTocItem> m_TableOfContents;

   EventRegistrationToken m_acceleratorKeyPressedToken;

   void HandleTOCsubMenu(UINT32 id);
};
