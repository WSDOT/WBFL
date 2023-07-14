///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

class CEAFApp;

#include <EAF\EAFExp.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFPluginState.h>
#include <EAF\EAFTypes.h>
#include <vector>
#include <map>

class CEAFStatusItem;
interface IBroker;

// Returns the main application object
EAFFUNC CEAFApp* EAFGetApp();

// Returns a pointer to the broker. Only call this method if you are using a document
// type that is a desendent of CEAFBrokerDocument
EAFFUNC HRESULT EAFGetBroker(IBroker** ppBroker);

// Displays a dialog for enabling/disabling plugin components. catid is the component
// category ID of the type of plugin to be managed.
EAFFUNC std::vector<CEAFPluginState> EAFManageApplicationPlugins(LPCTSTR lpszTitle,LPCTSTR lpszText,const CATID& catid,CWnd* pParent = nullptr,UINT helpID=0,LPCTSTR lpszAppName=nullptr);

// Returns the main frame window
EAFFUNC CEAFMainFrame* EAFGetMainFrame();

// Returns the document object
EAFFUNC CEAFDocument* EAFGetDocument();

// Returns the currently active view
EAFFUNC CView* EAFGetActiveView();

// Displays the common status center item message dialog box
EAFFUNC eafTypes::StatusItemDisplayReturn EAFShowStatusMessage(CEAFStatusItem* pStatusItem,eafTypes::StatusSeverityType severity,BOOL bRemoveableOnError,BOOL bEnableEdit,LPCTSTR lpszDocSetName=nullptr,UINT helpID=0);

// Compares IIDs
EAFFUNC bool operator<(REFIID a,REFIID b);

// Displays the standard Hints dialog. Returns TRUE if the user never wants to see this hint again
EAFFUNC BOOL EAFShowUIHints(LPCTSTR lpszText,LPCTSTR lpszTitle = _T("Hints"));

// Retrieves a file from an HTTP server.
EAFFUNC eafTypes::HttpGetResult EAFGetFileFromHTTPServer(const CString& strFileURL, const CString& strLocalTargetFile);

// Returns the name of the documentaion map (.DM) file
EAFFUNC CString EAFGetDocumentationMapFile(LPCTSTR lpszDocSetName,LPCTSTR lpszDocumentationURL);

// Causes the specified documentation map file to be loaded and fills topicMap with the help topic ID mapping 
// returns TRUE if successful
EAFFUNC BOOL EAFLoadDocumentationMap(LPCTSTR lpszDocMapFile,std::map<UINT,CString>& topicMap);

// Returns true if more than one instance of BridgeLink is running. This is a bad condition for updating configurations
EAFFUNC bool EAFAreOtherBridgeLinksRunning();