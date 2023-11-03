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
#include "EdgeReportView.h"


using namespace Microsoft::WRL;




EdgeReportView::EdgeReportView()
{
}

BOOL EdgeReportView::Create(
   LPCTSTR lpszWindowName,
   DWORD dwStyle,
   const RECT& rect,
   HWND hwndParent,
   UINT nID)
{
	m_hwndParent = hwndParent;

	// <-- WebView2 sample code starts here -->
	// Step 3 - Create a single WebView within the parent window
	// Locate the browser and set up the environment for WebView
	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			[&, hwndParent](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {

				// Create a CoreWebView2Controller and get the associated CoreWebView2 whose parent is the main window hWnd
				env->CreateCoreWebView2Controller(hwndParent, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
					[&, hwndParent](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
						if (controller != nullptr) {
							m_webviewController = controller;
							m_webviewController->get_CoreWebView2(&m_webview);
						}

						// Add a few settings for the webview
						// The demo step is redundant since the values are the default settings
						wil::com_ptr<ICoreWebView2Settings> settings;
						m_webview->get_Settings(&settings);
						settings->put_IsScriptEnabled(TRUE);
						settings->put_AreDefaultScriptDialogsEnabled(TRUE);
						settings->put_IsWebMessageEnabled(TRUE);

						// Resize WebView to fit the bounds of the parent window
						RECT bounds;
						GetClientRect(hwndParent, &bounds);
						m_webviewController->put_Bounds(bounds);

						// Schedule an async task to navigate to our file
						m_webview->Navigate(m_strURI.c_str());

						//// <NavigationEvents>
						//// Step 4 - Navigation events
						//// register an ICoreWebView2NavigationStartingEventHandler to cancel any non-https navigation
						//EventRegistrationToken token;
						//webview->add_NavigationStarting(Callback<ICoreWebView2NavigationStartingEventHandler>(
						//	[](ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
						//		wil::unique_cotaskmem_string uri;
						//		args->get_Uri(&uri);
						//		std::wstring source(uri.get());
						//		//if (source.substr(0, 5) != L"https") {
						//		//	args->put_Cancel(true);
						//		//}
						//		return S_OK;
						//	}).Get(), &token);
						//// </NavigationEvents>

						//// <Scripting>
						//// Step 5 - Scripting
						//// Schedule an async task to add initialization script that freezes the Object object
						//webview->AddScriptToExecuteOnDocumentCreated(L"Object.freeze(Object);", nullptr);
						//// Schedule an async task to get the document URL
						//webview->ExecuteScript(L"window.document.URL;", Callback<ICoreWebView2ExecuteScriptCompletedHandler>(
						//	[](HRESULT errorCode, LPCWSTR resultObjectAsJson) -> HRESULT {
						//		LPCWSTR URL = resultObjectAsJson;
						//		//doSomethingWithURL(URL);
						//		return S_OK;
						//	}).Get());
						//// </Scripting>

						//// <CommunicationHostWeb>
						//// Step 6 - Communication between host and web content
						//// Set an event handler for the host to return received message back to the web content
						//webview->add_WebMessageReceived(Callback<ICoreWebView2WebMessageReceivedEventHandler>(
						//	[](ICoreWebView2* webview, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
						//		wil::unique_cotaskmem_string message;
						//		args->TryGetWebMessageAsString(&message);
						//		// processMessage(&message);
						//		webview->PostWebMessageAsString(message.get());
						//		return S_OK;
						//	}).Get(), &token);

						//// Schedule an async task to add initialization script that
						//// 1) Add an listener to print message from the host
						//// 2) Post document URL to the host
						//webview->AddScriptToExecuteOnDocumentCreated(
						//	L"window.chrome.webview.addEventListener(\'message\', event => alert(event.data));" \
						//	L"window.chrome.webview.postMessage(window.document.URL);",
						//	nullptr);
						//// </CommunicationHostWeb>

						return S_OK;
					}).Get());
				return S_OK;
			}).Get());



	// <-- WebView2 sample code ends here -->

	return TRUE;
}

void EdgeReportView::FitToParent()
{
	if (m_webviewController)
	{
		RECT bounds;
		GetClientRect(m_hwndParent, &bounds);
		m_webviewController->put_Bounds(bounds);
	}
}

void EdgeReportView::Move(POINT topLeft)
{
   //::SetWindowPos(GetBrowserWnd(), nullptr, topLeft.x, topLeft.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void EdgeReportView::Size(SIZE size)
{
	//::SetWindowPos(GetBrowserWnd(), nullptr, 0, 0, size.cx, size.cy, SWP_NOZORDER | SWP_NOMOVE);
	if (m_webviewController)
	{
		RECT bounds;
		bounds.left = 0;
		bounds.top = 0;
		bounds.right = size.cx;
		bounds.bottom = size.cy;
		m_webviewController->put_Bounds(bounds);
	}
}

void EdgeReportView::Print(bool bPrompt)
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
   //m_pWebBrowser->Print(header, footer);
}

void EdgeReportView::Find()
{
   //LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   //IOleCommandTarget* pIOleCmdTarget;
   //if (S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget))
   //{
   //   pIOleCmdTarget->Exec(&CGID_IWebBrowserPriv, CWBCmdGroup::HTMLID_FIND, 0, nullptr, nullptr);
   //   pIOleCmdTarget->Release();
   //}
}

void EdgeReportView::SelectAll()
{
//   LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
//   IOleCommandTarget* pIOleCmdTarget;
//   if (S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget))
//   {
//      pIOleCmdTarget->Exec(nullptr, OLECMDID_SELECTALL, OLECMDEXECOPT_DODEFAULT, nullptr, nullptr);
//      pIOleCmdTarget->Release();
//   }
}

void EdgeReportView::Copy()
{
   //LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   //IOleCommandTarget* pIOleCmdTarget;
   //if (S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget))
   //{
   //   pIOleCmdTarget->Exec(nullptr, OLECMDID_COPY, OLECMDEXECOPT_DODEFAULT, nullptr, nullptr);
   //   pIOleCmdTarget->Release();
   //}
}

void EdgeReportView::Refresh()
{
	if(m_webview) m_webview->Reload();
}

void EdgeReportView::ViewSource()
{
   //LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   //IOleCommandTarget* pIOleCmdTarget;
   //if (S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget))
   //{
   //   pIOleCmdTarget->Exec(&CGID_IWebBrowserPriv, CWBCmdGroup::HTMLID_VIEWSOURCE, 0, nullptr, nullptr);
   //   pIOleCmdTarget->Release();
   //}
}

void EdgeReportView::Back()
{
	if (m_webview) m_webview->GoBack();
}

void EdgeReportView::Forward()
{
	if (m_webview) m_webview->GoForward();
}

void EdgeReportView::Navigate(LPCTSTR uri)
{
	// creation of web view 2 occurs asynchronously. 
	// store the uri
	// Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler> will call Navigate
	// with this URI once the control is ready to display something
	m_strURI = uri;
	if(m_webview) m_webview->Navigate(uri);
}
