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


#include "stdafx.h"
#include <EAF\EAFDataRecoveryHandler.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFApp.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFStatusBar.h>

CEAFDataRecoveryHandler::CEAFDataRecoveryHandler(_In_ DWORD dwRestartManagerSupportFlags, _In_ int nAutosaveInterval) :
   CDataRecoveryHandler(dwRestartManagerSupportFlags, nAutosaveInterval)
{
   m_bIsAutosaving = FALSE;
}

BOOL CEAFDataRecoveryHandler::AutosaveDocumentInfo(_In_ CDocument *pDocument, _In_ BOOL bResetModifiedFlag)
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   CEAFStatusBar* pStatusBar = pMainFrame->GetStatusBar();
   pStatusBar->AutoSaveSaving(TRUE);

   m_bIsAutosaving = TRUE;
   BOOL bResult = __super::AutosaveDocumentInfo(pDocument, bResetModifiedFlag);
   m_bIsAutosaving = FALSE;

   DWORD dwAttrib = GetFileAttributes(pDocument->GetPathName());
   if (bResult && !(dwAttrib & FILE_ATTRIBUTE_READONLY) && EAFGetApp()->IsAutoSaveEnabled() && pDocument->IsModified())
   {
      // if the recovery autosave was successful do a regular save if the file has been previously saved and is not readonly
      pDocument->DoFileSave();
   }

   pStatusBar->AutoSaveSaving(FALSE);

   return bResult;
}

BOOL CEAFDataRecoveryHandler::ReopenPreviousDocuments()
{
   // we don't want the base class implementation. it creates a new empty document but
   // we just want to open the autosave/recovery document.
   // this is now a do-nothing method
   return TRUE;
}


BOOL CEAFDataRecoveryHandler::IsAutosaving() { return m_bIsAutosaving; }
