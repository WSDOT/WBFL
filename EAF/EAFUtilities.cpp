///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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
#include <EAF\EAFUtilities.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFStatusItem.h>

#include "ManagePluginsDlg.h"
#include "StatusMessageDialog.h"
#include "UIHintsDlg.h"

#include <AfxInet.h>

EAFFUNC CEAFApp* EAFGetApp()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   return (CEAFApp*)AfxGetApp();
}

// Global function for getting the broker from the current document
HRESULT EAFGetBroker(IBroker** ppBroker)
{
   // let's try it the easy way first
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   CEAFDocument* pDoc = pFrame->GetDocument();

   if ( pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CEAFBrokerDocument)) )
   {
      CEAFBrokerDocument* pBrokerDoc = (CEAFBrokerDocument*)pDoc;
      return pBrokerDoc->GetBroker(ppBroker);
   }
   else
   {
      // looks like we have to do it the hard way
      CWinApp* pApp = EAFGetApp();
      CDocument* pDocument = nullptr;
      bool bDone = false;
      POSITION doc_template_pos = pApp->GetFirstDocTemplatePosition();
      
      while ( doc_template_pos != nullptr && !bDone )
      {
         CDocTemplate* pTemplate = pApp->GetNextDocTemplate(doc_template_pos);

         POSITION doc_pos = pTemplate->GetFirstDocPosition();
         while ( doc_pos != nullptr )
         {
            pDocument = pTemplate->GetNextDoc(doc_pos);
            if ( pDocument )
            {
               bDone = true;
               break;
            }
         }
      }

      if ( pDocument && pDocument->IsKindOf(RUNTIME_CLASS(CEAFBrokerDocument)) )
      {
         CEAFBrokerDocument* pBrokerDoc = (CEAFBrokerDocument*)pDocument;
         return pBrokerDoc->GetBroker(ppBroker);
      }
   }

   (*ppBroker) = nullptr;

   return E_FAIL;
}

std::vector<CEAFPluginState> EAFManageApplicationPlugins(LPCTSTR lpszTitle,LPCTSTR lpszText,const CATID& catid,CWnd* pParent,UINT nHID,LPCTSTR lpszAppName)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CManagePluginsDlg dlg(lpszTitle,lpszText,catid,pParent,lpszAppName,nHID);
   dlg.DoModal(); // this DoModal is correct... dialog takes care of its own data
   return dlg.m_PluginStates;
}

CEAFMainFrame* EAFGetMainFrame()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFMainFrame* pFrame = (CEAFMainFrame*)AfxGetMainWnd();
   ASSERT_KINDOF(CEAFMainFrame,pFrame);
   return pFrame;
}

CEAFDocument* EAFGetDocument()
{
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   return pFrame->GetDocument();
}

CView* EAFGetActiveView()
{
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   CView* pView = pFrame->GetActiveView();
   if ( pView )
      return pView;

   if ( pFrame->IsKindOf(RUNTIME_CLASS(CFrameWnd)) )
   {
      CMDIChildWnd* pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
      pView = pChild->GetActiveView();
      return pView;
   }

   return nullptr;
}

void EAFShowStatusMessage(CEAFStatusItem* pStatusItem,eafTypes::StatusSeverityType severity,BOOL bRemoveableOnError,LPCTSTR lpszDocSetName,UINT helpID)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CStatusMessageDialog dlg(pStatusItem,severity,bRemoveableOnError,lpszDocSetName,helpID);

   if (dlg.DoModal() == IDOK)
   {
      if ( bRemoveableOnError || severity != eafTypes::statusError )
      {
         pStatusItem->RemoveAfterEdit(TRUE);
      }
      else
      {
         pStatusItem->RemoveAfterEdit(FALSE);
      }
   }
}

BOOL EAFShowUIHints(LPCTSTR lpszText,LPCTSTR lpszTitle)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CUIHintsDlg dlg;
   dlg.m_strTitle = lpszTitle;
   dlg.m_strText = lpszText;
   dlg.DoModal();
   return dlg.m_bDontShowAgain;
}

bool operator<(REFIID a,REFIID b)
{
   /*
   typedef struct _GUID {
      unsigned long  Data1;
      unsigned short Data2;
      unsigned short Data3;
      unsigned char  Data4[8];} GUID;
    */

    if ( a.Data1 > b.Data1 )
       return false;
    if ( a.Data1 < b.Data1 )
       return true;

    if ( a.Data2 > b.Data2 )
       return false;
    if ( a.Data2 < b.Data2 )
       return true;

    if ( a.Data3 > b.Data3 )
       return false;
    if ( a.Data3 < b.Data3 )
       return true;

    for ( int i = 0; i < 8; i++ )
    {
       if ( a.Data4[i] > b.Data4[i] )
          return false;
       if ( a.Data4[i] < b.Data4[i] )
          return true;
    }

    return false;
}

eafTypes::HttpGetResult EAFGetFileFromHTTPServer(const CString& strFileURL, const CString& strLocalTargetFile)
{
	DWORD dwAccessType = PRE_CONFIG_INTERNET_ACCESS;
	DWORD dwHttpRequestFlags = /*INTERNET_FLAG_EXISTING_CONNECT |*/ INTERNET_FLAG_DONT_CACHE;

	LPCTSTR pstrAgent = nullptr;

	//the verb we will be using for this connection
	//if nullptr then GET is assumed
	LPCTSTR pstrVerb = _T("GET");
	
	//the address of the url in the request was obtained from
	LPCTSTR pstrReferer = nullptr;

	//Http version we are using; nullptr = HTTP/1.0
	LPCTSTR pstrVersion = nullptr;

	//For the Accept request headers if we need them later on
	LPCTSTR pstrAcceptTypes = nullptr;
	CString szHeaders = _T("Accept: audio/x-aiff, audio/basic, audio/midi, audio/mpeg, audio/wav, image/jpeg, image/gif, image/jpg, image/png, image/mng, image/bmp, text/plain, text/html, text/htm\r\n");

	//Username we will use if a secure site comes into play
	LPCTSTR pstrUserName = nullptr; 
	//The password we will use
	LPCTSTR pstrPassword = nullptr;

	//CInternetSession flags if we need them
	//DWORD dwFlags = INTERNET_FLAG_ASYNC;
	DWORD dwFlags = INTERNET_FLAG_DONT_CACHE;

	//Proxy setting if we need them
	LPCTSTR pstrProxyName = nullptr;
	LPCTSTR pstrProxyBypass = nullptr;

   // see if url parses before going further
   DWORD dwServiceType;
   CString strServer, strObject;
   INTERNET_PORT nPort;

   BOOL bSuccess = AfxParseURL(strFileURL,dwServiceType,strServer,strObject,nPort);
   if ( !bSuccess || dwServiceType != AFX_INET_SERVICE_HTTP )
   {
      return eafTypes::hgrInvalidUrl;
   }

	CInternetSession	session(pstrAgent, 1, dwAccessType, pstrProxyName, pstrProxyBypass, dwFlags);

	//Set any CInternetSession options we  may need
	int ntimeOut = 30;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,1000* ntimeOut);
	session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF,1000);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES,1);

	//Enable or disable status callbacks
	//session.EnableStatusCallback(FALSE);
   eafTypes::HttpGetResult retVal = eafTypes::hgrConnectionError;

	CHttpConnection*	pServer = nullptr;   
	CHttpFile* pFile = nullptr;
	DWORD dwRet;
	try 
   {		
		pServer = session.GetHttpConnection(strServer, nPort, 
			pstrUserName, pstrPassword);
		pFile = pServer->OpenRequest(pstrVerb, strObject, pstrReferer, 
			1, &pstrAcceptTypes, pstrVersion, dwHttpRequestFlags);

		pFile->AddRequestHeaders(szHeaders);
      CString strHeader;
      strHeader.Format(_T("User-Agent: %s/3.3/r/n"),AfxGetAppName());
		pFile->AddRequestHeaders(strHeader, HTTP_ADDREQ_FLAG_ADD_IF_NEW);
		pFile->SendRequest();

		pFile->QueryInfoStatusCode(dwRet);//Check wininet.h for info
										  //about the status codes


		if (dwRet == HTTP_STATUS_DENIED)
		{
         return eafTypes::hgrConnectionError;
		}

		if (dwRet == HTTP_STATUS_MOVED ||
			dwRet == HTTP_STATUS_REDIRECT ||
			dwRet == HTTP_STATUS_REDIRECT_METHOD)
		{
			CString strNewAddress;
			//again check wininet.h for info on the query info codes
			//there is alot one can do and re-act to based on these codes
			pFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, strNewAddress);
			
			int nPos = strNewAddress.Find(_T("Location: "));
			if (nPos == -1)
			{
            return eafTypes::hgrNotFound;
			}

			strNewAddress = strNewAddress.Mid(nPos + 10);
			nPos = strNewAddress.Find('\n');
			if (0 < nPos)
         {
				strNewAddress = strNewAddress.Left(nPos);
         }

			pFile->Close();      
			delete pFile;
			pServer->Close();  
			delete pServer;

			CString strServerName;
			CString strObject;
			INTERNET_PORT nNewPort;
			DWORD dwServiceType;

			if (!AfxParseURL(strNewAddress, dwServiceType, strServerName, strObject, nNewPort))
			{
            return eafTypes::hgrInvalidUrl;
			}

			pServer = session.GetHttpConnection(strServerName, nNewPort, 
				pstrUserName, pstrPassword);
			pFile = pServer->OpenRequest(pstrVerb, strObject, 
				pstrReferer, 1, &pstrAcceptTypes, pstrVersion, dwHttpRequestFlags);
			pFile->AddRequestHeaders(szHeaders);
			pFile->SendRequest();

			pFile->QueryInfoStatusCode(dwRet);
			if (dwRet != HTTP_STATUS_OK)
			{
            return eafTypes::hgrNotFound;
			}
		}

		if(dwRet == HTTP_STATUS_OK)
      {
         // Copy file
			ULONGLONG len = pFile->GetLength();
			TCHAR buf[2000];
			int numread;

         CFile myfile(strLocalTargetFile, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);
		   while ((numread = pFile->Read(buf,sizeof(buf)/sizeof(TCHAR)-1)) > 0)
		   {
			   buf[numread] = _T('\0');
			   strObject += buf;
			   myfile.Write(buf, numread);
		   }
		   myfile.Close();

         retVal = eafTypes::hgrOk; // only good exit
		}
      else
      {
         retVal = eafTypes::hgrNotFound;
      }

		pFile->Close();      
		delete pFile;

      pServer->Close();  
		delete pServer;

      session.Close();
	}
	catch (CInternetException* pEx) 
	{
      // catch any exceptions from WinINet      
		TCHAR szErr[1024];
		szErr[0] = _T('\0');
      if(!pEx->GetErrorMessage(szErr, 1024))
      {
			_tcscpy_s(szErr,1024,_T("Some crazy unknown error"));
      }
		pEx->Delete();
		if(pFile)
      {
			delete pFile;
      }
		if(pServer)
      {
			delete pServer;
      }
		session.Close(); 

      retVal = eafTypes::hgrNotFound;
	}

	return retVal;
}

BOOL EAFLoadDocumentationMap(LPCTSTR lpszDocMapFile,std::map<UINT,CString>& topicMap)
{
   topicMap.clear();

   CString strMapFile(lpszDocMapFile);
   std::ifstream ifMapFile(strMapFile);
   if ( ifMapFile.bad() || !ifMapFile.is_open() )
   {
      return FALSE;
   }

   char buffer[256];
   while (!ifMapFile.eof())
   {
      ifMapFile.getline(buffer,256);
      CString str(buffer);
      if ( !str.IsEmpty() )
      {
         int pos = str.Find(_T("="));
         CString token = str.Left(pos);
         token.Trim();
         UINT nID = ::_tstol(token.GetBuffer());

         CString strTopic = str.Mid(pos+1);
         strTopic.Trim();

         topicMap.insert(std::make_pair(nID,strTopic));
      }
   }

   return TRUE;
}

CString EAFGetDocumentationMapFile(LPCTSTR lpszDocSetName,LPCTSTR lpszDocumentationURL)
{
   CEAFApp* pApp = EAFGetApp();
   if ( pApp->UseOnlineDocumentation() )
   {
      TCHAR buffer[256];
      ::GetTempPath(256,buffer);
      CString strLocalFile;
      strLocalFile.Format(_T("%s%s.dm"),buffer,lpszDocSetName);

      CString strFileURL;
      strFileURL.Format(_T("%s%s.dm"),lpszDocumentationURL,lpszDocSetName);

      eafTypes::HttpGetResult result;
      bool bDone = false;
      do
      {
         // when we are running a bunch of instances of the application at the same time, getting the file from
         // the HTTP server can fail because of a sharing violation. Loop until we have successfullly retrieved our file.
         try
         {
            result = EAFGetFileFromHTTPServer(strFileURL, strLocalFile);

            // NOTE: This is a total HACK... WSDOT's web servers won't let "unknown" file types be downloaded throught HTTP
            // .dm is an unknown type. On WSDOT servers, we'll add .html to the filename so that we can get the file downloaded.
            if ( result == eafTypes::hgrNotFound )
            {
               strFileURL += _T(".html");
               result = EAFGetFileFromHTTPServer(strFileURL, strLocalFile);
            }
            bDone = true;
         }
         catch(CFileException* pException)
         {
            //TCHAR szError[255];
            //pException->GetErrorMessage(szError,255);
            //CString strMsg;
            //strMsg.Format(_T("Error getting documentation map file: %s"),szError);
            //AfxMessageBox(strMsg);
            pException->Delete();
         }
      }
      while ( !bDone );

      return strLocalFile;
   }
   else
   {
      CString str;
      str.Format(_T("%s\\%s.dm"),lpszDocumentationURL,lpszDocSetName);
      return str;
   }

}
