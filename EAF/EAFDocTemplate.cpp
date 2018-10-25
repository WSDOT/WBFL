///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

#include "StdAfx.h"
#include <EAF\EAFDocTemplate.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFMainFrame.h>

#include <afximpl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEAFDocTemplate,CMultiDocTemplate)

CEAFDocTemplate::CEAFDocTemplate(UINT nIDResource,
                                 IEAFCommandCallback* pCallback,
                                 CRuntimeClass* pDocClass,
                                 CRuntimeClass* pFrameClass,
                                 CRuntimeClass* pViewClass,
                                 HMENU hSharedMenu,
                                 int maxViewCount) :
CMultiDocTemplate(nIDResource,pDocClass,pFrameClass,pViewClass)
{
   m_pPlugin = NULL;
   m_pCommandCallback = pCallback;

   m_pCreateData = NULL;

   m_bSharedMenu = FALSE;
   if ( hSharedMenu != NULL )
   {
      m_bSharedMenu = TRUE;
      m_hMenuShared = hSharedMenu;
   }
   m_MaxViewCount = maxViewCount;

   m_pTemplateItem = NULL;

   CString strFileNewName;
   GetDocString(strFileNewName,CDocTemplate::fileNewName);
   m_TemplateGroup.SetGroupName(strFileNewName);
}

CEAFDocTemplate::~CEAFDocTemplate()
{
   if ( m_bSharedMenu )
   {
      // This prevents the base class virtual destructor from
      // destroying the menu resource (i.e. it checks to make
      // sure the handle isn't NULL)
      //
      // See MSKB Article ID: Q118435, "Sharing Menus Between MDI Child Windows"

      m_hMenuShared = NULL;
   }
}

void CEAFDocTemplate::LoadTemplate()
{
   CMultiDocTemplate::LoadTemplate();

   m_AccelTable.Init(EAFGetApp()->GetPluginCommandManager());
   m_AccelTable.AddAccelTable(m_hAccelTable,GetCommandCallback());
   m_hAccelTable = NULL;
}

void CEAFDocTemplate::CreateDefaultItem(HICON hIcon)
{
   CString strExtName;
   GetDocString(strExtName,CDocTemplate::filterExt);

   CString strFileName;
   GetDocString(strFileName,CDocTemplate::fileNewName);

   CString strItemName;
   if ( strExtName != _T("") )
      strItemName.Format(_T("%s (%s)"),strFileName,strExtName);
   else
      strItemName = strFileName;
 
   m_TemplateGroup.AddItem( new CEAFTemplateItem(this,strItemName,NULL,hIcon) );
}

CDocument* CEAFDocTemplate::OpenDocumentFile(LPCTSTR lpszPathName,BOOL bMakeVisible)
{
   // We don't want to call the base class version
   //CDocument* pDocument = CMultiDocTemplate::OpenDocumentFile(lpszPathName,bMakeVisible);

   CDocument* pDocument = NULL;
   CEAFDocument* pEAFDoc = NULL;
   CFrameWnd* pFrame = NULL;

   try
   {
	   pDocument = CreateNewDocument();
	   if (pDocument == NULL)
	   {
		   TRACE(traceAppMsg, 0, _T("CEAFDocTemplate::CreateNewDocument returned NULL.\n"));
		   AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		   return NULL;
	   }
	   ASSERT_VALID(pDocument);
      ASSERT_KINDOF(CEAFDocument,pDocument);
      pEAFDoc = (CEAFDocument*)pDocument;

	   BOOL bAutoDelete = pDocument->m_bAutoDelete; // capture current state
	   pDocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong during CreateNewFrame
	   pFrame = CreateNewFrame(pDocument, NULL);
	   pDocument->m_bAutoDelete = bAutoDelete; // reset state

	   if (pFrame == NULL)
	   {
		   AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		   delete pDocument;       // explicit delete on error
		   return NULL;
	   }
	   ASSERT_VALID(pFrame);

      pEAFDoc->OnCreateInitialize();

      if ( !DoOpenDocumentFile(lpszPathName,bMakeVisible,pEAFDoc,pFrame) )
      {
         return NULL;
      }
   }
   catch(sysXStructuredLoad& e)
   {
      std::_tstring msg;
      e.GetErrorMessage(&msg);

      CString strMsg;
      strMsg.Format(_T("An error occured while opening %s\n\n%s"),lpszPathName,msg.c_str());
      AfxMessageBox(strMsg,MB_OK);

      pDocument->m_bAutoDelete = TRUE; // pDocument will be deleted when the frame window is destroyed
      pFrame->DestroyWindow();

      return NULL;
   }

	InitialUpdateFrame(pFrame, pDocument, bMakeVisible);

   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   pMainFrame->HideMainFrameToolBar();
   pMainFrame->HideStartPage();

   pEAFDoc->OnCreateFinalize();

   return pDocument;
}

BOOL CEAFDocTemplate::DoOpenDocumentFile(LPCTSTR lpszPathName,BOOL bMakeVisible,CEAFDocument* pDocument,CFrameWnd* pFrame)
{
   SetDefaultTitle(pDocument);
	if (lpszPathName == NULL)
	{
		// create a new document - with default document name

		// avoid creating temporary compound file when starting up invisible
		if (!bMakeVisible)
			pDocument->m_bEmbedded = TRUE;

      CString strTemplateFile = m_pTemplateItem->GetTemplateFilePath();
      if ( strTemplateFile.IsEmpty() )
      {
		   if (!pDocument->OnNewDocument())
		   {
			   // user has be alerted to what failed in OnNewDocument
			   TRACE(traceAppMsg, 0, _T("CEAFDocument::OnNewDocument returned FALSE.\n"));
			   pFrame->DestroyWindow();
			   return FALSE;
		   }
      }
      else
      {
		   if (!pDocument->OnNewDocumentFromTemplate(strTemplateFile))
		   {
			   // user has be alerted to what failed in OnNewDocumentFromTemplate
			   TRACE(traceAppMsg, 0, _T("CEAFDocument::OnNewDocumentFromTemplate returned FALSE.\n"));
			   pFrame->DestroyWindow();
			   return FALSE;
		   }
      }

		// it worked, now bump untitled count
		m_nUntitledCount++;
	}
	else
	{
		// open an existing document
		CWaitCursor wait;
		if (!pDocument->OnOpenDocument(lpszPathName))
		{
			// user has be alerted to what failed in OnOpenDocument
			TRACE(traceAppMsg, 0, _T("CEAFDocument::OnOpenDocument returned FALSE.\n"));
			pFrame->DestroyWindow();
			return FALSE;
		}
	}

   return TRUE;
}

CString CEAFDocTemplate::GetTemplateGroupItemDescription(const CEAFTemplateItem* pItem) const
{
   CString strDesc;
   strDesc.Format(_T("Create a new %s"),pItem->GetName());
   return strDesc;
}

void CEAFDocTemplate::SetTemplateItem(const CEAFTemplateItem* pItem)
{
   m_pTemplateItem = pItem;
}

const CEAFTemplateGroup* CEAFDocTemplate::GetTemplateGroup() const
{
   return &m_TemplateGroup;
}

UINT CEAFDocTemplate::GetResourceID() const
{
   return m_nIDResource;
}

IEAFCommandCallback* CEAFDocTemplate::GetCommandCallback()
{
   return m_pCommandCallback;
}

void CEAFDocTemplate::SetPlugin(IEAFAppPlugin* pPlugin)
{
   m_pPlugin = pPlugin;
}

void CEAFDocTemplate::GetPlugin(IEAFAppPlugin** ppPlugin)
{
   (*ppPlugin) = m_pPlugin;
   if ( *ppPlugin )
   {
      (*ppPlugin)->AddRef();
   }
}

CDocTemplate::Confidence CEAFDocTemplate::MatchDocType(LPCTSTR lpszPathName,CDocument*& rpDocMatch)
{
   // There seems to be a bug in the base-class version so we are going to do this ourselves.

	ASSERT(lpszPathName != NULL);
	rpDocMatch = NULL;

	// go through all documents
	POSITION pos = GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = GetNextDoc(pos);
		if (AfxComparePath(pDoc->GetPathName(), lpszPathName))
		{
			// already open
			rpDocMatch = pDoc;
			return yesAlreadyOpen;
		}
	}

	// see if it matches our default suffix
	CString strFilterExt;
	if (GetDocString(strFilterExt, CDocTemplate::filterExt) &&
	  !strFilterExt.IsEmpty())
	{
		// see if extension matches
      // This is where the bug is in the base-class version... there can be more than
      // one valid extension in the strFilterExt string, separated with ;.
		ASSERT(strFilterExt[0] == '.');
		LPCTSTR lpszDot = ::PathFindExtension(lpszPathName);
		if (lpszDot != NULL)
        {
           int iStart = 0;
           do
           {
               CString strExtension = strFilterExt.Tokenize(_T(";"),iStart);

               if ( iStart != -1 )
               {
                  if(::AfxComparePath(lpszDot, static_cast<const TCHAR *>(strExtension)))
                  {
			          return yesAttemptNative; // extension matches, looks like ours
                  }
               }
           }
           while (iStart != -1);

        }
	}

	// otherwise we will guess it may work
	return yesAttemptForeign;
}

CEAFAcceleratorTable* CEAFDocTemplate::GetAcceleratorTable()
{
   return &m_AccelTable;
}

int CEAFDocTemplate::GetMaxViewCount() const
{
   return m_MaxViewCount;
}

CRuntimeClass* CEAFDocTemplate::GetViewClass()
{
   return m_pViewClass;
}

void CEAFDocTemplate::SetViewCreationData(LPVOID pCreateData)
{
   m_pCreateData = pCreateData;
}

LPVOID CEAFDocTemplate::GetViewCreationData()
{
   return m_pCreateData;
}
