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


static void CheckFailure(HRESULT hr, CString const& message)
{
   if (FAILED(hr))
   {
      CString text;
      text.Format(L"%s : 0x%08X", (LPCTSTR)message, hr);

      // TODO: log text

      std::exit(hr);
   }
}

#define CHECK_FAILURE_STRINGIFY(arg)         #arg
#define CHECK_FAILURE_FILE_LINE(file, line)  ([](HRESULT hr){ CheckFailure(hr, L"Failure at " CHECK_FAILURE_STRINGIFY(file) L"(" CHECK_FAILURE_STRINGIFY(line) L")"); })
#define CHECK_FAILURE                        CHECK_FAILURE_FILE_LINE(__FILE__, __LINE__)
#define CHECK_FAILURE_BOOL(value)            CHECK_FAILURE((value) ? S_OK : E_UNEXPECTED)

EdgeReportView::EdgeReportView(WBFL::Reporting::ReportBrowser* parentReportBrowser):
   m_pParentReportBrowser(parentReportBrowser)
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

   // Code below taken from MSFT's sample and modified
	// Create a single WebView within the parent window
	// Locate the browser and set up the environment for WebView

    // User data folder should be a custom location - the default is the location of the EXE
    // which generally isn't a write-able location at runtime
    // See https://learn.microsoft.com/en-us/microsoft-edge/webview2/concepts/user-data-folder
    TCHAR temp_path[_MAX_PATH];
    if (::GetTempPath(_MAX_PATH, temp_path) == 0)
       _tcscpy_s(temp_path, _MAX_PATH, _T("C:\\")); // Couldn't establish a temp path, just use the root drive.

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
                        else
                        {
                           ASSERT(0);
                           return E_FAIL;
                        }

						// Settings for the webview
						wil::com_ptr<ICoreWebView2Settings> settings2;
						m_webview->get_Settings(&settings2);
						settings2->put_IsScriptEnabled(TRUE);
#ifndef _DEBUG
                  settings2->put_AreDevToolsEnabled(FALSE); // get rid of "inspect" and "view page source" for production
#endif
                  // disable drag and drop (much easier than handling
                  wil::com_ptr<ICoreWebView2Controller4> controller4 = m_webviewController.query<ICoreWebView2Controller4>();
                  controller4->put_AllowExternalDrop(FALSE);

						// Resize WebView to fit the bounds of the parent window
						RECT bounds;
						GetClientRect(hwndParent, &bounds);
						m_webviewController->put_Bounds(bounds);

						// Schedule an async task to navigate to our file
						m_webview->Navigate(m_strRawURI.c_str());

                  LPCWSTR subFolder = nullptr;
                  // Use default options from constructor
                  auto options = Microsoft::WRL::Make<CoreWebView2EnvironmentOptions>();

                  HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(
                     subFolder, temp_path, options.Get(),
                     Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
                        this, &EdgeReportView::OnCreateEnvironmentCompleted)
                     .Get());
                  //! [CreateCoreWebView2EnvironmentWithOptions]
                  if (!SUCCEEDED(hr))
                  {
                     MessageBox(m_hwndParent, L"Failed to create WebView2 environment", nullptr, MB_OK);
                  }

                  //
                  // Deal with accelerator keys
                  //
                  wil::com_ptr<ICoreWebView2Settings3> settings3 = settings2.query<ICoreWebView2Settings3>();
                  settings3->put_AreBrowserAcceleratorKeysEnabled(TRUE);

                  CHECK_FAILURE(m_webviewController->add_AcceleratorKeyPressed(
                     Callback<ICoreWebView2AcceleratorKeyPressedEventHandler>(
                        [this](
                           ICoreWebView2Controller* sender,
                           ICoreWebView2AcceleratorKeyPressedEventArgs* args) -> HRESULT
                        {
                           COREWEBVIEW2_KEY_EVENT_KIND kind;
                           CHECK_FAILURE(args->get_KeyEventKind(&kind));
                           // We only care about key down events.
                           if (kind == COREWEBVIEW2_KEY_EVENT_KIND_KEY_DOWN ||
                              kind == COREWEBVIEW2_KEY_EVENT_KIND_SYSTEM_KEY_DOWN)
                           {
                              UINT key;
                              CHECK_FAILURE(args->get_VirtualKey(&key));

                              wil::com_ptr<ICoreWebView2AcceleratorKeyPressedEventArgs2> args2;

                              args->QueryInterface(IID_PPV_ARGS(&args2));
                              if (args2)
                              {
                                 // Allow standard Edge Ctrl-shortcuts to be processed but send others to parent window
                                 if (!(key == VK_CONTROL)) // ignore ctrl key by itself
                                 {
                                    if ((GetKeyState(VK_CONTROL) < 0))
                                    {
                                       bool isEdge = (key == 'F' || key == 'P' || key == 'R' || key == 'X' || key == 'C' || key == 'V' || key == 'A' || key == 'Z' || key == VK_OEM_PLUS || key == VK_OEM_MINUS);

                                       if (!isEdge)
                                       {
                                          // Tell the browser to skip the key and send command to parent window
                                          CHECK_FAILURE(args2->put_IsBrowserAcceleratorKeyEnabled(FALSE));
                                          PostMessage(m_hwndParent, WM_KEYDOWN, VK_CONTROL, 0); // Press Ctrl
                                          PostMessage(m_hwndParent, WM_KEYDOWN, key, 0);
                                       }
                                    }
                                    else if (key == VK_F1)
                                    {
                                       // Allow help
                                       CHECK_FAILURE(args2->put_IsBrowserAcceleratorKeyEnabled(FALSE));
                                       PostMessage(m_hwndParent, WM_KEYDOWN, key, 0);
                                    }
                                 }
                              }
                           }
                           return S_OK;
                        })
                     .Get(),
                     &m_acceleratorKeyPressedToken));

                  //
                  // Context menus
                  // 
                  wil::com_ptr<ICoreWebView2_11>            m_webView2_11;
                  m_webview->QueryInterface(IID_PPV_ARGS(&m_webView2_11));
 
                  m_webView2_11->add_ContextMenuRequested(
                  Callback<ICoreWebView2ContextMenuRequestedEventHandler>(
                     [this](
                        ICoreWebView2* sender,
                        ICoreWebView2ContextMenuRequestedEventArgs* eventArgs)
                     {
                        wil::com_ptr<ICoreWebView2ContextMenuRequestedEventArgs> args =
                           eventArgs;
                        wil::com_ptr<ICoreWebView2ContextMenuItemCollection> items;
                        CHECK_FAILURE(args->get_MenuItems(&items));

                        wil::com_ptr<ICoreWebView2ContextMenuTarget> target;
                        CHECK_FAILURE(args->get_ContextMenuTarget(&target));

                        COREWEBVIEW2_CONTEXT_MENU_TARGET_KIND targetKind;
                        CHECK_FAILURE(target->get_Kind(&targetKind));

                        // Remove the 'Shared' context menu item.
                        // This item doesn't make sense because the report file is temporary
                        UINT32 itemsCount;
                        CHECK_FAILURE(items->get_Count(&itemsCount));

                        UINT32 removeIndex = itemsCount;
                        wil::com_ptr<ICoreWebView2ContextMenuItem> current;
                        for (UINT32 i = 0; i < itemsCount; i++)
                        {
                           CHECK_FAILURE(items->GetValueAtIndex(i, &current));
                           wil::unique_cotaskmem_string name;
                           CHECK_FAILURE(current->get_Name(&name));
                           if (std::wstring(L"share") == name.get())
                           {
                              removeIndex = i;
                           }
                        }
                        if (removeIndex < itemsCount)
                        {
                           CHECK_FAILURE(items->RemoveValueAtIndex(removeIndex));
                        }

                        // Remove the 'Save image as' context menu item for image context
                        // selections.
                        if (targetKind == COREWEBVIEW2_CONTEXT_MENU_TARGET_KIND_IMAGE)
                        {
                           UINT32 itemsCount;
                           CHECK_FAILURE(items->get_Count(&itemsCount));

                           UINT32 removeIndex = itemsCount;
                           wil::com_ptr<ICoreWebView2ContextMenuItem> current;
                           for (UINT32 i = 0; i < itemsCount; i++)
                           {
                              CHECK_FAILURE(items->GetValueAtIndex(i, &current));
                              wil::unique_cotaskmem_string name;
                              CHECK_FAILURE(current->get_Name(&name));
                              if (std::wstring(L"saveImageAs") == name.get())
                              {
                                 removeIndex = i;
                              }
                           }
                           if (removeIndex < itemsCount)
                           {
                              CHECK_FAILURE(items->RemoveValueAtIndex(removeIndex));
                           }
                        }

                        // Add our custom menu items for all cases except when text is selected.
                        // Otherwise use default Edge menu
                        if (targetKind != COREWEBVIEW2_CONTEXT_MENU_TARGET_KIND_SELECTED_TEXT)
                        {
                           wil::com_ptr<ICoreWebView2Environment9> webviewEnvironment;
                           CHECK_FAILURE(m_webViewEnvironment->QueryInterface(IID_PPV_ARGS(&webviewEnvironment)));

                           // Add menu item for Select All
                           wil::com_ptr<ICoreWebView2ContextMenuItem> selectAllMenuItem;
                           CHECK_FAILURE(webviewEnvironment->CreateContextMenuItem(
                              L"Select All", nullptr,
                              COREWEBVIEW2_CONTEXT_MENU_ITEM_KIND_COMMAND,
                              &selectAllMenuItem));
                           CHECK_FAILURE(selectAllMenuItem->add_CustomItemSelected(
                              Callback<ICoreWebView2CustomItemSelectedEventHandler>(
                                 [pedgeView = this](ICoreWebView2ContextMenuItem* sender, IUnknown* args)
                                 {
                                    pedgeView->SelectAll();
                                    return S_OK;
                                 }).Get(), nullptr));

                           CHECK_FAILURE(items->InsertValueAtIndex(0, selectAllMenuItem.get()));

                           // Add menu item for Find
#pragma Reminder("WebView2 Find feature should be added by MSFT in Late 2024 - Check to see if this has happened")
                           wil::com_ptr<ICoreWebView2ContextMenuItem> findMenuItem;
                           CHECK_FAILURE(webviewEnvironment->CreateContextMenuItem(
                              L"Press F3 or <Ctrl>-F to Find", nullptr,
                              COREWEBVIEW2_CONTEXT_MENU_ITEM_KIND_COMMAND,
                              &findMenuItem));
                           findMenuItem->put_IsEnabled(FALSE);
                           //CHECK_FAILURE(findMenuItem->add_CustomItemSelected(
                           //   Callback<ICoreWebView2CustomItemSelectedEventHandler>(
                           //      [webview = m_webview](ICoreWebView2ContextMenuItem* sender, IUnknown* args)
                           //      {
                           //         // The script method below works poorly. Hopefully MSFT will add a real feature in future
                           //         // HRESULT hr = webview->ExecuteScript(L"window.find(false,false,false,false,false,false,true);", nullptr);
                           //         return S_OK;
                           //      }).Get(), nullptr));

                           CHECK_FAILURE(items->InsertValueAtIndex(0, findMenuItem.get()));

                           // Table of Contents menu items
                           if (!m_TableOfContents.empty())
                           {
                              // Separator before toc
                              wil::com_ptr<ICoreWebView2ContextMenuItem> separatorMenuItem;
                              CHECK_FAILURE(webviewEnvironment->CreateContextMenuItem(
                                 L"", nullptr,
                                 COREWEBVIEW2_CONTEXT_MENU_ITEM_KIND_SEPARATOR,
                                 &separatorMenuItem));
                              CHECK_FAILURE(items->InsertValueAtIndex(0, separatorMenuItem.get()));

                              // Add custom context menu item for table of contents
                              if (m_tableOfContentsSubMenuItem)
                              {
                                 m_tableOfContentsSubMenuItem.put_void();
                              }

                              CHECK_FAILURE(webviewEnvironment->CreateContextMenuItem(L"Table of Contents", nullptr,
                                 COREWEBVIEW2_CONTEXT_MENU_ITEM_KIND_SUBMENU, &m_tableOfContentsSubMenuItem));

                              // Create 2nd level chapter TOC items and add to menu
                              UINT32 tocChapIdx = 0;
                              for (const auto& tocChapterItem : m_TableOfContents)
                              {
                                 // Chapter items can be submenu or a direct command depending if subparagraphs
                                 COREWEBVIEW2_CONTEXT_MENU_ITEM_KIND kind = tocChapterItem.m_ParagraphTOCItems.empty() ?
                                    COREWEBVIEW2_CONTEXT_MENU_ITEM_KIND_COMMAND : COREWEBVIEW2_CONTEXT_MENU_ITEM_KIND_SUBMENU;

                                 wil::com_ptr<ICoreWebView2ContextMenuItem> chapterTocMenuItem;
                                 CHECK_FAILURE(webviewEnvironment->CreateContextMenuItem(
                                    tocChapterItem.m_TocItem.m_Title.c_str(), nullptr,
                                    kind, &chapterTocMenuItem));
                                 CHECK_FAILURE(chapterTocMenuItem->add_CustomItemSelected(
                                    Callback<ICoreWebView2CustomItemSelectedEventHandler>(
                                       [pedgeView = this, target, id = tocChapterItem.m_TocItem.m_ID](ICoreWebView2ContextMenuItem* sender, IUnknown* args)
                                       {
                                          pedgeView->HandleTOCsubMenu(id);
                                          return S_OK;
                                       }).Get(), nullptr));

                                 // Create 3rd level paragraph toc menu items and add
                                 UINT32 tocParaIdx = 0;
                                 for (const auto& tocParaItem : tocChapterItem.m_ParagraphTOCItems)
                                 {
                                    wil::com_ptr<ICoreWebView2ContextMenuItem> paraTocMenuItem;
                                    CHECK_FAILURE(webviewEnvironment->CreateContextMenuItem(
                                       tocParaItem.m_Title.c_str(), nullptr,
                                       COREWEBVIEW2_CONTEXT_MENU_ITEM_KIND_COMMAND,
                                       &paraTocMenuItem));
                                    CHECK_FAILURE(paraTocMenuItem->add_CustomItemSelected(
                                       Callback<ICoreWebView2CustomItemSelectedEventHandler>(
                                          [pedgeView = this, target, id = tocParaItem.m_ID](ICoreWebView2ContextMenuItem* sender, IUnknown* args)
                                          {
                                             pedgeView->HandleTOCsubMenu(id);
                                             return S_OK;
                                          }).Get(), nullptr));

                                    wil::com_ptr<ICoreWebView2ContextMenuItemCollection>  chapterTocContextSubMenuItemChildren;
                                    CHECK_FAILURE(chapterTocMenuItem->get_Children(&chapterTocContextSubMenuItemChildren));
                                    chapterTocContextSubMenuItemChildren->InsertValueAtIndex(tocParaIdx++, paraTocMenuItem.get());
                                 }


                                 wil::com_ptr<ICoreWebView2ContextMenuItemCollection>  tocSubMenuItemChildren;
                                 CHECK_FAILURE(m_tableOfContentsSubMenuItem->get_Children(&tocSubMenuItemChildren));
                                 tocSubMenuItemChildren->InsertValueAtIndex(tocChapIdx++, chapterTocMenuItem.get());
                              }

                              CHECK_FAILURE(items->InsertValueAtIndex(0, m_tableOfContentsSubMenuItem.get()));

                              // Add menu item for Edit
                              wil::com_ptr<ICoreWebView2ContextMenuItem> editMenuItem;
                              CHECK_FAILURE(webviewEnvironment->CreateContextMenuItem(
                                 L"Edit", nullptr,
                                 COREWEBVIEW2_CONTEXT_MENU_ITEM_KIND_COMMAND,
                                 &editMenuItem));
                              CHECK_FAILURE(editMenuItem->add_CustomItemSelected(
                                 Callback<ICoreWebView2CustomItemSelectedEventHandler>(
                                    [pedgeView = this](ICoreWebView2ContextMenuItem* sender, IUnknown* args)
                                    {
                                       pedgeView->OnEdit();
                                       return S_OK;
                                    }).Get(), nullptr));

                              CHECK_FAILURE(items->InsertValueAtIndex(0, editMenuItem.get()));
                           }
                        }
                        // menu will be displayed
                        return S_OK;
                     })
                  .Get(), &m_contextMenuRequestedToken);

						return S_OK;
					}).Get());
				return S_OK;
			}).Get());

	return TRUE;
}

// This is the callback passed to CreateCoreWebView2EnvironmentWithOptions.
HRESULT EdgeReportView::OnCreateEnvironmentCompleted(
   HRESULT result, ICoreWebView2Environment* environment)
{
   if (result != S_OK)
   {
      MessageBox(m_hwndParent, L"Failed to create environment object.",nullptr,S_OK);
      return S_OK;
   }

   // Need to grab onto this variable here so we can create context menu
   m_webViewEnvironment = environment;

   return S_OK;
}

static CString filename_to_URL(const std::_tstring& fname)
{
   //turn into an internet-looking url
   CString filename(fname.c_str());
   filename.Replace(_T("///"), _T("//"));

   return filename;
}


void EdgeReportView::HandleTOCsubMenu(UINT32 id)
{
   CString filename = filename_to_URL(m_strRawURI);
   CString anc;
   anc.Format(_T("file://%s#_%d"), filename, id);

   if (m_webview)
   {
      m_webview->Navigate(anc);
   }
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
   COREWEBVIEW2_PRINT_DIALOG_KIND printDialogKind = COREWEBVIEW2_PRINT_DIALOG_KIND_BROWSER;
   wil::com_ptr<ICoreWebView2_16> webView2_16;
   CHECK_FAILURE(m_webview->QueryInterface(IID_PPV_ARGS(&webView2_16)));
   CHECK_FAILURE(webView2_16->ShowPrintUI(printDialogKind));
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
   if (m_webview != nullptr)
   {
      m_webview->ExecuteScript(L"document.execCommand(\"SelectAll\")", nullptr);
   }
}

void EdgeReportView::Copy()
{
   // Handled by Edge
}

void EdgeReportView::Refresh()
{
	if(m_webview) m_webview->Reload();
}

void EdgeReportView::ViewSource()
{
   // Handled by Edge as part of dev tools
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
	// Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler> will call Navigate
	// with this URI once the control is ready to display something

   // store the raw file uri
   if (m_strRawURI.empty())
   {
      m_strRawURI = uri;
   }

	if(m_webview) m_webview->Navigate(uri);
}

void EdgeReportView::SetTableOfContents(const std::vector<rptHtmlReportVisitor::ChapterTocItem>& tableOfContents)
{
   m_TableOfContents = tableOfContents;
}
