///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// EAFDocManager.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFDocManager.h>
#include <EAF\EAFDocTemplate.h>
#include <EAF\EAFApp.h>
#include <EAF\EAFUtilities.h>

#include "NewProjectDlg.h"

AFX_STATIC void AFXAPI _AfxAppendFilterSuffix(CString& filter, OPENFILENAME& ofn,
	CDocTemplate* pTemplate, CString* pstrDefaultExt)
{
	ENSURE_VALID(pTemplate);
	ASSERT_KINDOF(CDocTemplate, pTemplate);

	CString strFilterExt, strFilterName;
	if (pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt) &&
		!strFilterExt.IsEmpty() &&
		pTemplate->GetDocString(strFilterName, CDocTemplate::filterName) &&
		!strFilterName.IsEmpty())
	{
		if (pstrDefaultExt != NULL)
			pstrDefaultExt->Empty();

		// add to filter
		filter += strFilterName;
		ASSERT(!filter.IsEmpty());  // must have a file type name
		filter += (TCHAR)'\0';  // next string please

		int iStart = 0;
		do
		{
			CString strExtension = strFilterExt.Tokenize( _T( ";" ), iStart );

			if (iStart != -1)
			{
				// a file based document template - add to filter list

				// If you hit the following ASSERT, your document template 
				// string is formatted incorrectly.  The section of your 
				// document template string that specifies the allowable file
				// extensions should be formatted as follows:
				//    .<ext1>;.<ext2>;.<ext3>
				// Extensions may contain wildcards (e.g. '?', '*'), but must
				// begin with a '.' and be separated from one another by a ';'.
				// Example:
				//    .jpg;.jpeg
				ASSERT(strExtension[0] == '.');
				if ((pstrDefaultExt != NULL) && pstrDefaultExt->IsEmpty())
				{
					// set the default extension
					*pstrDefaultExt = strExtension.Mid( 1 );  // skip the '.'
					ofn.lpstrDefExt = *pstrDefaultExt;
					ofn.nFilterIndex = ofn.nMaxCustFilter + 1;  // 1 based number
				}

				filter += (TCHAR)'*';
				filter += strExtension;
				filter += (TCHAR)';';  // Always append a ';'.  The last ';' will get replaced with a '\0' later.
			}
		} while (iStart != -1);

		filter.SetAt( filter.GetLength()-1, '\0' );;  // Replace the last ';' with a '\0'
		ofn.nMaxCustFilter++;
	}
}

// CEAFDocManager

IMPLEMENT_DYNAMIC(CEAFDocManager, CDocManager)


CEAFDocManager::CEAFDocManager()
{
   CEAFApp* pApp = EAFGetApp();
   m_strCurrentFilter = pApp->GetProfileString(_T("Settings"),_T("Filter"),_T(""));
}

CEAFDocManager::~CEAFDocManager()
{
   CEAFApp* pApp = EAFGetApp();
   pApp->WriteProfileString(_T("Settings"),_T("Filter"),m_strCurrentFilter);
}

void CEAFDocManager::OnFileNew()
{
   // Don't call base class, we don't want to use its functionality
   //CDocManager::OnFileNew();

	if (m_templateList.IsEmpty())
	{
		TRACE(traceAppMsg, 0, "Error: no document templates registered with CWinApp.\n");
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return;
	}

	CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)m_templateList.GetHead();
	if ( 1 < m_templateList.GetCount() || 0 < pTemplate->GetTemplateGroup()->GetGroupCount() )
	{
		// more than one document template to choose from
		// bring up dialog prompting user
		CNewProjectDlg dlg(&m_templateList);
		if ( dlg.DoModal() != IDOK )
         return;
      
      pTemplate = dlg.m_pSelectedTemplate;

      ASSERT(pTemplate != NULL);
      ASSERT_KINDOF(CEAFDocTemplate,pTemplate);

      CEAFDocTemplate* pEAFTemplate = (CEAFDocTemplate*)pTemplate;
      pEAFTemplate->SetTemplateItem(dlg.m_pTemplateItem);
   }
   else
   {
      CEAFDocTemplate* pEAFTemplate = (CEAFDocTemplate*)pTemplate;
      pEAFTemplate->SetTemplateItem(pEAFTemplate->GetTemplateGroup()->GetItem(0));
   }

   pTemplate->OpenDocumentFile(NULL);
}

BOOL CEAFDocManager::DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{
   // Don't call base class version. we want to replace its functionality
   // CDocManager::DoPromptFileName(fileName,nIDSTitle,lFlags,bOpenFileDialog,pTemplate);


   // This code is copied from the base class version... the only difference is that default (*.*) file
   // type is removed
	CFileDialog dlgFile(bOpenFileDialog, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL, 0);

	CString title;
	ENSURE(title.LoadString(nIDSTitle));

	dlgFile.m_ofn.Flags |= lFlags;

	CString strFilter;
	CString strDefault;
	if (pTemplate != NULL)
	{
		ASSERT_VALID(pTemplate);
		_AfxAppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate, &strDefault);
	}
	else
	{
		// do for all doc template
		POSITION pos = m_templateList.GetHeadPosition();
		BOOL bFirst = TRUE;
		while (pos != NULL)
		{
			pTemplate = (CDocTemplate*)m_templateList.GetNext(pos);
			_AfxAppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate,
				bFirst ? &strDefault : NULL);

         bFirst = FALSE;
		}
	}


	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

   if ( bOpenFileDialog )
   {
      // Set the default file extension
      CEAFApp* pApp = EAFGetApp();
      dlgFile.m_ofn.nFilterIndex = pApp->GetProfileInt(_T("Settings"),_T("LastFileType"),1);
   }

   TCHAR strCustomFilter[40] = { _T("\0\0") };
   dlgFile.m_ofn.lpstrCustomFilter = strCustomFilter;
   dlgFile.m_ofn.nMaxCustFilter = 40;

   if ( !m_strCurrentFilter.IsEmpty() )
   {
      int count = 0;
      int length = strFilter.GetLength();
      for ( int i = 0; i < length; i++ )
      {
         if ( strFilter.GetAt(i) == 0 )
         {
            count++;
            if ( m_strCurrentFilter.Compare(strFilter.Mid(i+1)) == 0 )
            {
               dlgFile.m_ofn.nFilterIndex = (count+1)/2;
               break;
            }
         }
      }
   }

	INT_PTR nResult = dlgFile.DoModal();

   LPTSTR pstrCustomFilter = strCustomFilter;
   pstrCustomFilter++;
   m_strCurrentFilter.Format(_T("%s"),pstrCustomFilter);

	fileName.ReleaseBuffer();

   // Save type type of the last file
   if ( nResult == IDOK && bOpenFileDialog )
   {
      CEAFApp* pApp = EAFGetApp();
      pApp->WriteProfileInt(_T("Settings"),_T("LastFileType"),dlgFile.m_ofn.nFilterIndex);
   }

	return nResult == IDOK;
}

void CEAFDocManager::AddDocTemplate(CDocTemplate* pTemplate)
{
   CDocManager::AddDocTemplate(pTemplate);
   SortDocTemplates();
}

void CEAFDocManager::RemoveDocTemplate(POSITION pos)
{
   m_templateList.RemoveAt(pos);
}

void CEAFDocManager::SortDocTemplates()
{
   // need to sort the document templates by pTemplate->GetDocString(strTypeName, CDocTemplate::fileNewName)
   // so that the always display in a consistent order in the New Project dialog
}
