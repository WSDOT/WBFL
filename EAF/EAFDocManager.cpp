///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


AFX_STATIC void AFXAPI _AfxAppendFilterSuffix(CString& filter, CString& allFilter,OPENFILENAME& ofn,
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
		if (pstrDefaultExt != nullptr)
			pstrDefaultExt->Empty();

		// add to filter
		filter += strFilterName;
		ASSERT(!filter.IsEmpty());  // must have a file type name
		filter += (TCHAR)'\n';  // next string please

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
				if ((pstrDefaultExt != nullptr) && pstrDefaultExt->IsEmpty())
				{
					// set the default extension
					*pstrDefaultExt = strExtension.Mid( 1 );  // skip the '.'
					ofn.lpstrDefExt = *pstrDefaultExt;
					ofn.nFilterIndex = ofn.nMaxCustFilter + 1;  // 1 based number
				}

				filter += (TCHAR)'*';
				filter += strExtension;
				filter += (TCHAR)';';  // Always append a ';'.  The last ';' will get replaced with a '\0' later.

            allFilter += (TCHAR)'*';
            allFilter += strExtension;
            allFilter += (TCHAR)';';  // Always append a ';'.  The last ';' will get replaced with a '\0' later.
         }
		} while (iStart != -1);

      filter.SetAt(filter.GetLength() - 1, (TCHAR)'\n');;  // Replace the last ';' with a '\0'
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
      CString strError;
      strError.LoadString(AFX_IDP_FAILED_TO_CREATE_DOC);
      CString strMsg;
      strMsg.Format(_T("%s\r\nThere are no Project Types available.\r\nSelect File > Manage > Project Types to enable project types."), strError);
		AfxMessageBox(strMsg);
		return;
	}

   CEAFDocTemplate* pTemplate = nullptr;
   IndexType nTemplates = m_TemplateGroups.GetTemplateCount();
   if ( 1 < nTemplates)
   {
      // prompt to select a project template

      CNewProjectDlg dlg(&m_TemplateGroups);
		if ( dlg.DoModal() != IDOK )
         return;
      
      pTemplate = dlg.m_pSelectedTemplate;

      ASSERT(pTemplate != nullptr);
      ASSERT_KINDOF(CEAFDocTemplate,pTemplate);

      CEAFDocTemplate* pEAFTemplate = (CEAFDocTemplate*)pTemplate;
      pEAFTemplate->SetTemplateItem(dlg.m_pTemplateItem);
   }
   else
   {
      // there is only one project template available so just create a new document using it
      ATLASSERT(m_templateList.GetCount() == 1);
      pTemplate = m_TemplateGroups.GetGroup(0)->GetItem(0)->GetDocTemplate();
      pTemplate->SetTemplateItem(pTemplate->GetTemplateGroup()->GetItem(0));
   }


   pTemplate->OpenDocumentFile(nullptr,FALSE,TRUE);
}

BOOL CEAFDocManager::DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{
   // Don't call base class version. we want to replace its functionality
   // return CDocManager::DoPromptFileName(fileName,nIDSTitle,lFlags,bOpenFileDialog,pTemplate);

   // This code is copied from the base class version... the only difference is that default (*.*) file
   // type is removed... also, we need to use \0 as the separater character in CFileDialog filters, however
   // the string append doesn't work right with \0 so we will use \n and then replace all the \n with \0
   // at the last moment
	CFileDialog dlgFile(bOpenFileDialog, nullptr, nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, nullptr, nullptr, 0);

	CString title;
	ENSURE(title.LoadString(nIDSTitle));

	dlgFile.m_ofn.Flags |= lFlags;

   CEAFApp* pApp = EAFGetApp();
   CString strAllFilters;
   strAllFilters.Format(_T("%s Files\n"),pApp->m_pszProfileName);
	CString strFilter;
	CString strDefault;
	if (pTemplate != nullptr)
	{
		ASSERT_VALID(pTemplate);
		_AfxAppendFilterSuffix(strFilter, strAllFilters,dlgFile.m_ofn, pTemplate, &strDefault);
	}
	else
	{
		// do for all doc template
		POSITION pos = m_templateList.GetHeadPosition();
		BOOL bFirst = TRUE;
		while (pos != nullptr)
		{
			pTemplate = (CDocTemplate*)m_templateList.GetNext(pos);
			_AfxAppendFilterSuffix(strFilter, strAllFilters,dlgFile.m_ofn, pTemplate,
				bFirst ? &strDefault : nullptr);

         bFirst = FALSE;
		}
	}


   if (bOpenFileDialog)
   {
      dlgFile.m_ofn.nMaxCustFilter++;
      strAllFilters.SetAt(strAllFilters.GetLength() - 1, (TCHAR)'\n');  // Replace the last ';' with a '\0'
      strFilter += strAllFilters;
      //strFilter = strAllFilters;
      // Set the default file extension
      dlgFile.m_ofn.nFilterIndex = dlgFile.m_ofn.nMaxCustFilter+1;
   }

   strFilter.Replace((TCHAR)'\n', (TCHAR)'\0');
   dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	INT_PTR nResult = dlgFile.DoModal();
	return nResult == IDOK;
}

void CEAFDocManager::AddDocTemplate(CDocTemplate* pTemplate)
{
   ATLASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CEAFDocTemplate)));
   CEAFDocTemplate* pEAFDocTemplate = (CEAFDocTemplate*)pTemplate;

   // Store the doc template in the MFC template list.
   CDocManager::AddDocTemplate(pTemplate);

   // Organize the document templates in a way that works with the new project dialog
   CComPtr<IEAFAppPlugin> plugin;
   pEAFDocTemplate->GetPlugin(&plugin);
   ATLASSERT(plugin!=nullptr);

   // This is the root group (corrosponds to the root level nodes on the project type tree
   // in the new project dialog)
   const CEAFTemplateGroup* pTemplateGroup = pEAFDocTemplate->GetTemplateGroup();

   // Search to see if there is already a group for the same plugin
   CEAFTemplateGroup* pExistingGroup = m_TemplateGroups.FindGroup(pTemplateGroup->GetGroupName());

   if ( pExistingGroup == nullptr )
   {
      // this is a new group
      m_TemplateGroups.AddGroup(pTemplateGroup->Clone());
   }
   else
   {
      // a group already exists... merge the sub-groups and template items so they
      // display as sub-items on a single node in the project type tree
      IndexType nItems = pTemplateGroup->GetItemCount();
      for ( IndexType itemIdx = 0; itemIdx < nItems; itemIdx++ )
      {
         pExistingGroup->AddItem( pTemplateGroup->GetItem(itemIdx)->Clone() );
      }

      IndexType nGroups = pTemplateGroup->GetGroupCount();
      for ( IndexType grpIdx = 0; grpIdx < nGroups; grpIdx++ )
      {
         pExistingGroup->AddGroup( pTemplateGroup->GetGroup(grpIdx)->Clone() );
      }
   }
}

void CEAFDocManager::RemoveDocTemplate(POSITION pos)
{
   CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)m_templateList.GetAt(pos);

   RemoveDocTemplate(pTemplate,&m_TemplateGroups);

   m_templateList.RemoveAt(pos);
}

void CEAFDocManager::RemoveDocTemplate(CEAFDocTemplate* pTemplate,CEAFTemplateGroup* pGroup)
{
   IndexType nItems = pGroup->GetItemCount();
   for ( IndexType itemIdx = nItems; 0 < itemIdx; itemIdx-- )
   {
      CEAFTemplateItem* pItem = pGroup->GetItem(itemIdx-1);
      if ( pItem->GetDocTemplate() == pTemplate )
      {
         pGroup->RemoveItem(itemIdx-1);
      }
   }

   GroupIndexType nGroups = pGroup->GetGroupCount();
   for ( GroupIndexType grpIdx = nGroups; 0 < grpIdx; grpIdx-- )
   {
      CEAFTemplateGroup* pSubGroup = pGroup->GetGroup(grpIdx-1);
      RemoveDocTemplate(pTemplate,pSubGroup);
      if ( pSubGroup->GetItemCount() == 0 && pSubGroup->GetGroupCount() == 0 )
      {
         pGroup->RemoveGroup(grpIdx-1);
      }
   }
}
