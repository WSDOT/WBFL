///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright � 1999-2024  Washington State Department of Transportation
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
//
// WebBrowser.cpp: implementation of the CWebBrowser class.
//
//////////////////////////////////////////////////////////////////////

// Note: Most of the code below was copied on July 2, 2012 from http://www.codeproject.com from the 
//       article "Using the WebBrowser control, simplified" by Gary R. Wheeler | 13 Feb 2012
//       Original code was licensed by the "The Code Project Open License (CPOL)" which requires
//       reference back to the original code.
//       Class names were changed to retain compatibility with the original PGSuper/WBFL
//       code base.
//

#include "stdafx.h"
#include "comdef.h"
#include "mshtml.h"
#include "mshtmcid.h"
#include "mshtmhst.h"
#include "exdispid.h"

#include "WebBrowser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define Unused(parameter) parameter					// avoid compile warnings
													// about unused parameters

/////////////////////////////////////////////////////////////////////////////
// Construction and creation
/////////////////////////////////////////////////////////////////////////////

CWebBrowser::CWebBrowser()
	:	_Browser(nullptr),
		_BrowserDispatch(nullptr),
		_Ready(false),
		_Content(_T(""))
{
}

CWebBrowser::~CWebBrowser()
{
    // release browser interfaces

	if (_Browser != nullptr) {
		_Browser->Release();
		_Browser = nullptr;
	}

	if (_BrowserDispatch != nullptr) {
		_BrowserDispatch->Release();
		_BrowserDispatch = nullptr;
	}
}

// Standard create

BOOL CWebBrowser::Create(LPCTSTR pszWindowName, DWORD dwStyle, 
                           const RECT& rect, 
                           CWnd* pParentWnd, 
						   UINT nID)
{
    BOOL results = TRUE;

	_Ready      = false;
	
    _Browser	= nullptr;

    // create this window

    CWnd *window = this;
	results = window->Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW),
	                         pszWindowName,
							 dwStyle,
							 rect,
							 pParentWnd,
							 nID);
    if (!results) return FALSE;

    // create browser control window as child of this window; 
	// this window sinks events from control

	CRect browser_window_rect(0,0,(rect.right - rect.left),(rect.bottom - rect.top));

    results = _BrowserWindow.CreateControl(CLSID_WebBrowser,
                                           nullptr,
                                           (WS_VISIBLE | WS_TABSTOP),
                                           browser_window_rect,
                                           this,
                                           AFX_IDW_PANE_FIRST);
    if (!results) {
        DestroyWindow();
        return FALSE;
    }

    // get control interfaces

    LPUNKNOWN unknown = _BrowserWindow.GetControlUnknown();

    HRESULT hr = unknown->QueryInterface(IID_IWebBrowser2,(void **)&_Browser);
    if (SUCCEEDED(hr)) {
        hr = unknown->QueryInterface(IID_IDispatch,(void **)&_BrowserDispatch);
    }

    if (!SUCCEEDED(hr)) {
        _BrowserWindow.DestroyWindow();
        DestroyWindow();
        return FALSE;        
    }

    // Disable drag and drop - we are a child, we can't handle drops
    hr = _Browser->put_RegisterAsDropTarget(VARIANT_FALSE);
    ATLASSERT(SUCCEEDED(hr));

	// navigate to initial blank page

	if (_Browser != nullptr) {
		Navigate(_T("about:blank"));
	}

    return TRUE;
}

// Create in place of dialog control

BOOL CWebBrowser::CreateFromControl(CWnd *pParentWnd,UINT nID,DWORD dwStyle)
{
	BOOL result = FALSE;

	ASSERT(pParentWnd != nullptr);

	CWnd *control = pParentWnd->GetDlgItem(nID);

	if (control != nullptr) {

		// get control location

		CRect		rect;

		control->GetWindowRect(&rect);
		pParentWnd->ScreenToClient(&rect);

		// destroy control, since the browser will take its place

		control->DestroyWindow();

		// create browser

		result = Create(nullptr, dwStyle,
		                rect,
						pParentWnd,
						nID);

	}

	return result;
}

// Destruction

void CWebBrowser::PostNcDestroy()
{
    // release browser interfaces

	if (_Browser != nullptr) {
		_Browser->Release();
		_Browser = nullptr;
	}

	if (_BrowserDispatch != nullptr) {
		_BrowserDispatch->Release();
		_BrowserDispatch = nullptr;
	}
	
	_Ready		= false;
	_Content	= _T("");
	
	CWnd::PostNcDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// Controls
/////////////////////////////////////////////////////////////////////////////

// Navigate to URL

void CWebBrowser::Navigate(LPCTSTR URL)
{
	_Ready   = false;
	_Content = _T("");

	if (_Browser != nullptr) {

		CString		url(URL);

		_variant_t	flags(0L,VT_I4);
		_variant_t	target_frame_name("");
		_variant_t	post_data("");
		_variant_t	headers("");

		_Browser->Navigate(url.AllocSysString(),
						   &flags,
						   &target_frame_name,
						   &post_data,
						   &headers);

	}
}

// Navigate to HTML document in resource

void CWebBrowser::NavigateResource(int resource_ID)
{
	if (_Browser != nullptr) {

		CString resource_string;

		// load HTML document from resource

		HRSRC resource_handle = FindResource(AfxGetResourceHandle(),
											 MAKEINTRESOURCE(resource_ID),
											 RT_HTML);

		if (resource_handle != nullptr) {

			HGLOBAL resource = LoadResource(AfxGetResourceHandle(),
											resource_handle);

			if (resource != nullptr) {

				LPVOID resource_memory = LockResource(resource);

				if (resource_memory != nullptr) {

					DWORD resource_size = SizeofResource(AfxGetResourceHandle(),
														 resource_handle);

					// identify the resource document as MBCS (e.g. ANSI)
					// or UNICODE

					bool     UNICODE_document = false;

					wchar_t *UNICODE_memory   = (wchar_t *)resource_memory;
					int      UNICODE_size     = resource_size / sizeof(wchar_t);

					if (UNICODE_size >= 1) {

						// check for UNICODE byte order mark

						if (*UNICODE_memory == L'\xFEFF') {
							UNICODE_document = true;
							UNICODE_memory  += 1;
							UNICODE_size    -= 1;
						}

						// otherwise, check for UNICODE leading tag

						else if (UNICODE_size >= 5) {

							if ((UNICODE_memory[0]           == L'<') &&
							    (towupper(UNICODE_memory[1]) == L'H') &&
							    (towupper(UNICODE_memory[2]) == L'T') &&
							    (towupper(UNICODE_memory[3]) == L'M') &&
							    (towupper(UNICODE_memory[4]) == L'L')) {
								UNICODE_document = true;
							}

						}

						// Note: This logic assumes that the UNICODE resource document is 
						//       in little-endian byte order, which would be typical for 
						//       any HTML document used as a resource in a Windows application.

					}

					// convert resource document if required

#if !defined(UNICODE)

					if (UNICODE_document) {

						char *MBCS_buffer = resource_string.GetBufferSetLength(resource_size + 1);

						int MBCS_length = ::WideCharToMultiByte(CP_ACP,
						                                        0,
											                    UNICODE_memory,
											                    UNICODE_size,
											                    MBCS_buffer,
											                    resource_size + 1,
											                    nullptr,
											                    nullptr);

						resource_string.ReleaseBuffer(MBCS_length);

					}

					else {

						resource_string = CString((char *)resource_memory,resource_size);

					}

#else

					if (UNICODE_document) {

						resource_string = CString(UNICODE_memory,UNICODE_size);

					}

					else {

						wchar_t *UNICODE_buffer = resource_string.GetBufferSetLength(resource_size + 1);

						int UNICODE_length = ::MultiByteToWideChar(CP_ACP,
						                                           0,
											                       (const char *)resource_memory,
											                       resource_size,
											                       UNICODE_buffer,
											                       (resource_size + 1));

						resource_string.ReleaseBuffer(UNICODE_length);

					}

#endif


				}

			}

		}

		Clear();
		Write(resource_string);

	}
}

// Append string to current document

void CWebBrowser::Write(LPCTSTR string)
{
	if (_Browser != nullptr) {

		_Content.Append(string);
		
		_ContentWrite();

	}
}

void CWebBrowser::Clear()
{
	if (_Browser != nullptr) {

		_Content = _T("");

		// get document interface

		IHTMLDocument2	*document	= GetDocument();
		HRESULT			hr			= S_OK;
		
		if (document != nullptr) {

			// close and re-open document to empty contents

			document->close();
			
			VARIANT		open_name;
			VARIANT		open_features;
			VARIANT		open_replace;
			IDispatch	*open_window	= nullptr;

			::VariantInit(&open_name);

			open_name.vt      = VT_BSTR;
			open_name.bstrVal = ::SysAllocString(L"_self");

			::VariantInit(&open_features);
			::VariantInit(&open_replace);
			
			hr = document->open(::SysAllocString(L"text/html"),
			                    open_name,
			                    open_features,
			                    open_replace,
			                    &open_window);

			if (hr == S_OK) {
				Refresh();
			}

			if (open_window != nullptr) {
				open_window->Release();
			}

			::VariantClear(&open_name);
			
			document->Release();
			document = nullptr;
		
		}
		
		else {

			Navigate(_T("about:blank"));

		}
		
	}
}

// Navigation operations

void CWebBrowser::GoBack()
{
	if (_Browser != nullptr) {
		_Browser->GoBack();
	}
}

void CWebBrowser::GoForward()
{
	if (_Browser != nullptr) {
		_Browser->GoForward();
	}
}

void CWebBrowser::GoHome()
{
	if (_Browser != nullptr) {
		_Browser->GoHome();
	}
}

void CWebBrowser::Refresh()
{
	if (_Browser != nullptr) {
		_Browser->Refresh();
	}
}

void CWebBrowser::Stop()
{
	if (_Browser != nullptr) {
		_Browser->Stop();
	}
}

// Print contents

void CWebBrowser::Print(LPCTSTR header,LPCTSTR footer)
{
	if (_Browser != nullptr) {

		// construct two element SAFEARRAY;
		// first element is header string, second element is footer string

		HRESULT hr;

		VARIANT		header_variant;
		VariantInit(&header_variant);
		V_VT(&header_variant)   = VT_BSTR;
		V_BSTR(&header_variant) = CString(header).AllocSysString();

		VARIANT		footer_variant;
		VariantInit(&footer_variant);
		V_VT(&footer_variant)   = VT_BSTR;
		V_BSTR(&footer_variant) = CString(footer).AllocSysString();

		long index;

		SAFEARRAYBOUND	parameter_array_bound[1];
		SAFEARRAY		*parameter_array = nullptr;

		parameter_array_bound[0].cElements = 2;
		parameter_array_bound[0].lLbound   = 0;

		parameter_array = SafeArrayCreate(VT_VARIANT,1,parameter_array_bound);

		index = 0;
		hr    = SafeArrayPutElement(parameter_array,&index,&header_variant);

		index = 1;
		hr    = SafeArrayPutElement(parameter_array,&index,&footer_variant);

		VARIANT	parameter;
		VariantInit(&parameter);
		V_VT(&parameter)    = VT_ARRAY | VT_BYREF;
		V_ARRAY(&parameter) = parameter_array;

		// start printing browser contents

		hr = _Browser->ExecWB(OLECMDID_PRINT,OLECMDEXECOPT_DODEFAULT,&parameter,nullptr);

		// release SAFEARRAY

		if (!SUCCEEDED(hr)) {
			VariantClear(&header_variant);
			VariantClear(&footer_variant);
			if (parameter_array != nullptr) {
				SafeArrayDestroy(parameter_array);
			}
		}

	}
}

void CWebBrowser::PrintPreview()
{
	if (_Browser != nullptr) {
		_Browser->ExecWB(OLECMDID_PRINTPREVIEW,OLECMDEXECOPT_DODEFAULT,nullptr,nullptr);
	}
}

// Miscellaneous

bool CWebBrowser::GetBusy()
{
    bool busy = false;

	if (_Browser != nullptr) {

		VARIANT_BOOL    variant_bool;

		HRESULT hr = _Browser->get_Busy(&variant_bool);
		if (SUCCEEDED(hr)) {
			busy = (variant_bool == VARIANT_TRUE);    
		}

	}

    return busy;
}

CString CWebBrowser::GetLocationName()
{
    CString location_name = _T("");

	if (_Browser != nullptr) {

		BSTR location_name_BSTR = nullptr;

		HRESULT hr = _Browser->get_LocationName(&location_name_BSTR);
		if (SUCCEEDED(hr)) {
			location_name = location_name_BSTR;
		}

		::SysFreeString(location_name_BSTR);

	}

    return location_name;
}

CString CWebBrowser::GetLocationURL()
{
    CString location_URL = _T("");

	if (_Browser != nullptr) {

		BSTR location_URL_BSTR = nullptr;

		HRESULT hr = _Browser->get_LocationURL(&location_URL_BSTR);
		if (SUCCEEDED(hr)) {
			location_URL = location_URL_BSTR;
		}

		::SysFreeString(location_URL_BSTR);

	}

    return location_URL;
}

READYSTATE CWebBrowser::GetReadyState()
{
    READYSTATE readystate = READYSTATE_UNINITIALIZED;

    if (_Browser != nullptr) {
		_Browser->get_ReadyState(&readystate);
	}

    return readystate;
}

bool CWebBrowser::GetSilent()
{
    bool silent = false;

	if (_Browser != nullptr) {

		VARIANT_BOOL silent_variant;

		HRESULT hr = _Browser->get_Silent(&silent_variant);
		if (SUCCEEDED(hr)) {
			silent = (silent_variant == VARIANT_TRUE);
		}

	}

    return silent;
}

void CWebBrowser::PutSilent(bool silent)
{
	if (_Browser != nullptr) {

		VARIANT_BOOL silent_variant;

		if (silent) silent_variant = VARIANT_TRUE;
		else        silent_variant = VARIANT_FALSE;

		_Browser->put_Silent(silent_variant);
	}
}

IHTMLDocument2 *CWebBrowser::GetDocument()
{
	IHTMLDocument2 *document = nullptr;
	
	if (_Browser != nullptr) {
	
		// get browser document's dispatch interface

		IDispatch *document_dispatch = nullptr;

		HRESULT hr = _Browser->get_Document(&document_dispatch);

		if (SUCCEEDED(hr) && (document_dispatch != nullptr)) {

			// get the actual document interface

			hr = document_dispatch->QueryInterface(IID_IHTMLDocument2,
			                                       (void **)&document);

			// release dispatch interface
					
			document_dispatch->Release();
		
		}
		
	}
	
	return document;
}

/////////////////////////////////////////////////////////////////////////////
// Message handlers
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CWebBrowser,CWnd)
    //{{AFX_MSG_MAP(CWebBrowser)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CWebBrowser::PreTranslateMessage(MSG *pMsg)
{
	BOOL result = FALSE;

   // IE is a tabbed browser and it gobbles up the Ctrl-Tab/Shift-Ctrl-Tab message to
   // swap between tabs with the keyboard. We are using IE as a single window control so
   // we need Ctrl-Tab/Shift-Ctrl-Tab to swap between the windows of our application.
   // Pretranslate the message. If it is a KeyDown message and Ctrl-Tab or Shift-Ctrl-Tab
   // are pressed, just pass the message along to the regular MFC command processing.
   if ( pMsg->message == WM_KEYDOWN )
   {
      BOOL bIsCtrlTab      = ::GetKeyState(VK_CONTROL) && ::GetKeyState(VK_TAB);
      BOOL bIsShiftCtrlTab = ::GetKeyState(VK_SHIFT) && ::GetKeyState(VK_CONTROL) && ::GetKeyState(VK_TAB);
      if( bIsCtrlTab || bIsShiftCtrlTab )
         return CWnd::PreTranslateMessage(pMsg);
   }

	// translate keys correctly, especially Tab, Del, (Enter?)
	
	if (_Browser != nullptr) {
	
		IOleInPlaceActiveObject* OleInPlaceActiveObject = nullptr;

		HRESULT hr = _Browser->QueryInterface(IID_IOleInPlaceActiveObject, (void**)&OleInPlaceActiveObject);

		if (SUCCEEDED(hr) && (OleInPlaceActiveObject != nullptr)) {

			hr = OleInPlaceActiveObject->TranslateAccelerator(pMsg);
			result = (hr == S_OK ? TRUE : FALSE);

			OleInPlaceActiveObject->Release();

		}

	}

	else {
		result = CWnd::PreTranslateMessage(pMsg);
	}

	return result;
}

// Resize control window as this window is resized

void CWebBrowser::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (_Browser != nullptr) {
        CRect rect(0,0,cx,cy);	
		_BrowserWindow.MoveWindow(&rect);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Event handlers
/////////////////////////////////////////////////////////////////////////////

#ifndef DISPID_PRINTTEMPLATEINSTANTIATION
	#define DISPID_PRINTTEMPLATEINSTANTIATION 225
#endif
#ifndef DISPID_PRINTTEMPLATETEARDOWN
	#define DISPID_PRINTTEMPLATETEARDOWN 226
#endif

BEGIN_EVENTSINK_MAP(CWebBrowser,CWnd)
    ON_EVENT(CWebBrowser,AFX_IDW_PANE_FIRST,
	         DISPID_BEFORENAVIGATE2,
             _OnBeforeNavigate2, 
			 VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
    ON_EVENT(CWebBrowser,AFX_IDW_PANE_FIRST,
	         DISPID_DOCUMENTCOMPLETE,
             _OnDocumentComplete, 
			 VTS_DISPATCH VTS_PVARIANT)
    ON_EVENT(CWebBrowser,AFX_IDW_PANE_FIRST,
	         DISPID_DOWNLOADBEGIN,
             _OnDownloadBegin, 
			 VTS_NONE)
    ON_EVENT(CWebBrowser,AFX_IDW_PANE_FIRST,
	         DISPID_PROGRESSCHANGE,
             _OnProgressChange, 
			 VTS_I4 VTS_I4)
    ON_EVENT(CWebBrowser,AFX_IDW_PANE_FIRST,
	         DISPID_DOWNLOADCOMPLETE,
             _OnDownloadComplete, 
			 VTS_NONE)
    ON_EVENT(CWebBrowser,AFX_IDW_PANE_FIRST,
	         DISPID_NAVIGATECOMPLETE2,
             _OnNavigateComplete2, 
			 VTS_DISPATCH VTS_PVARIANT)
    ON_EVENT(CWebBrowser,AFX_IDW_PANE_FIRST,
	         DISPID_STATUSTEXTCHANGE,
             _OnStatusTextChange, 
			 VTS_BSTR)
    ON_EVENT(CWebBrowser,AFX_IDW_PANE_FIRST,
	         DISPID_TITLECHANGE,
             _OnTitleChange, 
			 VTS_BSTR)
	ON_EVENT(CWebBrowser,AFX_IDW_PANE_FIRST,
	         DISPID_PRINTTEMPLATEINSTANTIATION,
	         _OnPrintTemplateInstantiation, 
	         VTS_DISPATCH)
	ON_EVENT(CWebBrowser,AFX_IDW_PANE_FIRST,
	         DISPID_PRINTTEMPLATETEARDOWN,
	         _OnPrintTemplateTeardown, 
	         VTS_DISPATCH)
END_EVENTSINK_MAP()

CWebBrowser::Notification::Notification(HWND hwnd,UINT ID,NotificationType type)
{
	hdr.hwndFrom	= hwnd;
	hdr.idFrom		= ID;
	hdr.code		= type;
	URL				= _T("");
	frame			= _T("");
	post_data		= nullptr;
	post_data_size	= 0;
	headers			= _T("");
	progress		= 0;
	progress_max	= 0;
	text			= _T("");
}

CWebBrowser::Notification::~Notification()
{
}

// Called before navigation begins; application may cancel if required

void CWebBrowser::_OnBeforeNavigate2(LPDISPATCH lpDisp,
                                       VARIANT FAR *URL,
                                       VARIANT FAR *Flags,
                                       VARIANT FAR *TargetFrameName,
                                       VARIANT FAR *PostData,
                                       VARIANT FAR *Headers,
                                       VARIANT_BOOL *Cancel)
{
	Unused(Flags);	// Note: flags value is reserved

    if (lpDisp == _BrowserDispatch) {

		CString				URL_string;
		CString				frame;
		unsigned char		*post_data		= nullptr;
		int					post_data_size	= 0;
		CString				headers;

        if ((URL       != nullptr) && 
		    (V_VT(URL) == VT_BSTR)) {
            URL_string = V_BSTR(URL);
        }

		if ((TargetFrameName       != nullptr) &&
            (V_VT(TargetFrameName) == VT_BSTR)) {
			frame = V_BSTR(TargetFrameName);
        }

		if ((PostData       != nullptr)                    &&
		    (V_VT(PostData) == (VT_VARIANT | VT_BYREF))) {

			VARIANT *PostData_variant = V_VARIANTREF(PostData);

			if ((PostData_variant       != nullptr) &&
			    (V_VT(PostData_variant) != VT_EMPTY)) {

				SAFEARRAY *PostData_safearray = V_ARRAY(PostData_variant);

				if (PostData_safearray != nullptr) {

					char *post_data_array = nullptr;

					SafeArrayAccessData(PostData_safearray,(void HUGEP **)&post_data_array);

					long		lower_bound = 1;
					long		upper_bound = 1;

					SafeArrayGetLBound(PostData_safearray,1,&lower_bound);
					SafeArrayGetUBound(PostData_safearray,1,&upper_bound);

					post_data_size = (int)(upper_bound - lower_bound + 1);

					post_data = new unsigned char[post_data_size];

					memcpy(post_data,post_data_array,post_data_size);

					SafeArrayUnaccessData(PostData_safearray);

				}

			}

		}

		if ((Headers       != nullptr) &&
            (V_VT(Headers) == VT_BSTR)) {
			headers = V_BSTR(Headers);
        }

		bool cancel = OnBeforeNavigate2(URL_string,
		                                frame,
										post_data,post_data_size,
										headers);

		if (Cancel != nullptr) {
			if (cancel) *Cancel = VARIANT_TRUE;
			else        *Cancel = VARIANT_FALSE;
		}

		delete []post_data;

    }    
}

bool CWebBrowser::OnBeforeNavigate2(CString URL,
                                      CString frame,
									  void    *post_data,int post_data_size,
									  CString headers)
{
	bool cancel = false;
	
	CWnd *parent = GetParent();
	
	if (parent != nullptr) {

		Notification	notification(m_hWnd,GetDlgCtrlID(),BeforeNavigate2);
		
		notification.URL			= URL;
		notification.frame			= frame;
		notification.post_data		= post_data;
		notification.post_data_size	= post_data_size;
		notification.headers		= headers;

		LRESULT result = parent->SendMessage(WM_NOTIFY,
		                                     notification.hdr.idFrom,
											 (LPARAM)&notification);
		
		if (result) {
			cancel = true;
		}

	}
	
    return cancel;
}

bool CWebBrowser::ParsePostData(CString post_data,
	                              CStringArray &names,
	                              CStringArray &values)
{
	bool result = true;
	
	int size = 1;
	
	names.SetSize(size);
	values.SetSize(size);
	
	int offset = 0;
	
	bool parsing_name = true;
	
	CString hex(_T("0123456789ABCDEF"));
	
	while ((offset < post_data.GetLength()) && result) {

		if      (post_data[offset] == _T('%')) {

			if ((offset + 2) < post_data.GetLength()) {

				int digit1 = hex.Find(_totupper(post_data[offset + 1]));
				int digit2 = hex.Find(_totupper(post_data[offset + 2]));

				if ((digit1 >= 0) && (digit2 >= 0)) {

					_TCHAR character = (_TCHAR)((digit1 << 4) + digit2);

					if (parsing_name) names[size - 1].AppendChar(character);
					else              values[size - 1].AppendChar(character);

				}
				
				else {
					result = false;
				}

				offset += 2;

			}

			else {
				result = false;
			}

		}

		else if (post_data[offset] == _T('+')) {
			if (parsing_name) names[size - 1].AppendChar(_T(' '));
			else              values[size - 1].AppendChar(_T(' '));
		}

		else if (post_data[offset] == _T('=')) {

			if (parsing_name) {
				parsing_name = false;
			}
			else {
				values[size - 1].AppendChar(post_data[offset]);
			}

		}

		else if (post_data[offset] == _T('&')) {

			if (!parsing_name) {
				parsing_name = true;
				size += 1;
				names.SetSize(size);
				values.SetSize(size);
			}

			else {
				values[size - 1].AppendChar(post_data[offset]);
			}

		}
		
		else {

			if (parsing_name) names[size - 1].AppendChar(post_data[offset]);
			else              values[size - 1].AppendChar(post_data[offset]);

		}

		offset++;
		
	}

	if ((names[size - 1]  == _T("")) &&
	    (values[size - 1] == _T(""))) {
		names.SetSize(size - 1);
		values.SetSize(size - 1);
	}

	return result;
}

// Document loaded and initialized

void CWebBrowser::_OnDocumentComplete(LPDISPATCH lpDisp,VARIANT *URL)
{
    if (lpDisp == _BrowserDispatch) {

		CString URL_string;
		
		if ((URL       != nullptr) &&
            (V_VT(URL) == VT_BSTR)) {
			URL_string = CString(V_BSTR(URL));
        }

        OnDocumentComplete(URL_string);

    }    
}

void CWebBrowser::OnDocumentComplete(CString URL)
{
	CWnd *parent = GetParent();
	
	if (parent != nullptr) {

		Notification	notification(m_hWnd,GetDlgCtrlID(),DocumentComplete);
		
		notification.URL = URL;

		LRESULT result = parent->SendMessage(WM_NOTIFY,
		                                     notification.hdr.idFrom,
											 (LPARAM)&notification);
		
	}
}

// Navigation/download progress

void CWebBrowser::_OnDownloadBegin()
{
    OnDownloadBegin();
}

void CWebBrowser::OnDownloadBegin()
{
	CWnd *parent = GetParent();
	
	if (parent != nullptr) {

		Notification	notification(m_hWnd,GetDlgCtrlID(),DownloadBegin);
		
		LRESULT result = parent->SendMessage(WM_NOTIFY,
		                                     notification.hdr.idFrom,
											 (LPARAM)&notification);
		
	}
}

void CWebBrowser::_OnProgressChange(long progress,long progress_max)
{
    OnProgressChange((int)progress,(int)progress_max);
}

void CWebBrowser::OnProgressChange(int progress,int progress_max)
{
	CWnd *parent = GetParent();
	
	if (parent != nullptr) {

		Notification	notification(m_hWnd,GetDlgCtrlID(),ProgressChange);
		
		notification.progress     = progress;
		notification.progress_max = progress_max;

		LRESULT result = parent->SendMessage(WM_NOTIFY,
		                                     notification.hdr.idFrom,
											 (LPARAM)&notification);
		
	}
}

void CWebBrowser::_OnDownloadComplete()
{
    OnDownloadComplete();
}

void CWebBrowser::OnDownloadComplete()
{
	CWnd *parent = GetParent();
	
	if (parent != nullptr) {

		Notification	notification(m_hWnd,GetDlgCtrlID(),DownloadComplete);
		
		LRESULT result = parent->SendMessage(WM_NOTIFY,
		                                     notification.hdr.idFrom,
											 (LPARAM)&notification);
		
	}
}

// Navigation to a link has completed

void CWebBrowser::_OnNavigateComplete2(LPDISPATCH lpDisp,VARIANT *URL)
{
    if (lpDisp == _BrowserDispatch) {

		// signal document ready

		_Ready = true;

		// write current content
		
		_ContentWrite();
		
		// inform user navigation complete
		
		CString URL_string;
		
		if ((URL       != nullptr) &&
            (V_VT(URL) == VT_BSTR)) {
			URL_string = V_BSTR(URL);
        }

		OnNavigateComplete2(URL_string);

    }    
}

void CWebBrowser::OnNavigateComplete2(CString URL)
{
	CWnd *parent = GetParent();
	
	if (parent != nullptr) {

		Notification	notification(m_hWnd,GetDlgCtrlID(),NavigateComplete2);
		
		notification.URL = URL;

		LRESULT result = parent->SendMessage(WM_NOTIFY,
		                                     notification.hdr.idFrom,
											 (LPARAM)&notification);
		
	}
}

// Status text has changed

void CWebBrowser::_OnStatusTextChange(BSTR bstrText)
{
    CString text;
	
	if (bstrText != nullptr) {
		text = (LPCTSTR)bstrText;
	}

    OnStatusTextChange(text);
}

void CWebBrowser::OnStatusTextChange(CString text)
{
	CWnd *parent = GetParent();
	
	if (parent != nullptr) {

		Notification	notification(m_hWnd,GetDlgCtrlID(),StatusTextChange);
		
		notification.text = text;

		LRESULT result = parent->SendMessage(WM_NOTIFY,
		                                     notification.hdr.idFrom,
											 (LPARAM)&notification);
		
	}
}

// Title text has changed

void CWebBrowser::_OnTitleChange(BSTR bstrText)
{
    CString text;
	
	if (bstrText != nullptr) {
		text = (LPCTSTR)bstrText;
	}

    OnTitleChange(text);
}

void CWebBrowser::OnTitleChange(CString text)
{
	CWnd *parent = GetParent();
	
	if (parent != nullptr) {

		Notification	notification(m_hWnd,GetDlgCtrlID(),TitleChange);
		
		notification.text = text;

		LRESULT result = parent->SendMessage(WM_NOTIFY,
		                                     notification.hdr.idFrom,
											 (LPARAM)&notification);
		
	}
}

// Print template instantiation and teardown
 
void CWebBrowser::_OnPrintTemplateInstantiation(LPDISPATCH lpDisp)
{
	OnPrintTemplateInstantiation();
};

void CWebBrowser::OnPrintTemplateInstantiation()
{
	CWnd *parent = GetParent();
	
	if (parent != nullptr) {

		Notification	notification(m_hWnd,GetDlgCtrlID(),PrintTemplateInstantiation);
		
		LRESULT result = parent->SendMessage(WM_NOTIFY,
		                                     notification.hdr.idFrom,
											 (LPARAM)&notification);
		
	}
}

void CWebBrowser::_OnPrintTemplateTeardown(LPDISPATCH lpDisp)
{
	OnPrintTemplateTeardown();
};

void CWebBrowser::OnPrintTemplateTeardown()
{
	CWnd *parent = GetParent();
	
	if (parent != nullptr) {

		Notification	notification(m_hWnd,GetDlgCtrlID(),PrintTemplateTeardown);
		
		LRESULT result = parent->SendMessage(WM_NOTIFY,
		                                     notification.hdr.idFrom,
											 (LPARAM)&notification);
		
	}
}

// Write deferred content

void CWebBrowser::_ContentWrite()
{
	if (_Ready && (!_Content.IsEmpty())) {
	
		// get document interface

		IHTMLDocument2 *document = GetDocument();
		
		if (document != nullptr) {

			// construct text to be written to browser as SAFEARRAY

			SAFEARRAY *safe_array = SafeArrayCreateVector(VT_VARIANT,0,1);
			
			VARIANT	*variant;
			
			SafeArrayAccessData(safe_array,(LPVOID *)&variant);
			
			variant->vt      = VT_BSTR;
			variant->bstrVal = _Content.AllocSysString();
			
			SafeArrayUnaccessData(safe_array);

			// write SAFEARRAY to browser document

			document->write(safe_array);
			
			// cleanup
			
			document->Release();
			document = nullptr;

			::SysFreeString(variant->bstrVal);
			variant->bstrVal = nullptr;
			
			SafeArrayDestroy(safe_array);
		
		}

	}
}
