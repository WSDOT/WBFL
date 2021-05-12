///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2021  Washington State Department of Transportation
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

/////////////////////////////////  Includes  //////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include <MfcTools\ddxfolder.h>
#include <MfcTools\choosedirdlg.h>


///////////////////////////////// defines /////////////////////////////////////

#define GETFOLDER_EDIT_ID 100

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




///////////////////////////////// Implementation //////////////////////////////


BEGIN_MESSAGE_MAP(CGetFolderControl, CEdit)
  //{{AFX_MSG_MAP(CGetFolderControl)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGetFolderControl::CGetFolderControl()
{
}

BOOL CGetFolderControl::SubclassEdit(HWND hEdit,int nIDC)
{   
  //test our inputs
  ASSERT(this);
  if (!IsWindow(hEdit))
  {
    ASSERT(FALSE);
    TRACE(_T("CGetFolderControl::SubclassEdit -- window handle is invalid!\n"));
    return FALSE;
  }                
  
  //subclass the control
  if (SubclassWindow(hEdit))
    return AddEditButton(nIDC);
  else
  {
    TRACE(_T("CGetFolderControl::SubclassEdit -- Could not subclass edit control!\n"));
    ASSERT(FALSE);
    return FALSE;
  }
}

BOOL CGetFolderControl::AddEditButton(int nIDC)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

  CRect Rect;
  GetWindowRect(Rect);
  GetParent()->ScreenToClient(Rect);
  Rect.left = Rect.right;
  Rect.right = Rect.left + (Rect.Height()*8/10);  //width is 8/10 of height

  //dynamically create the edit button control
  CString sEditControlText;
  if (!sEditControlText.LoadString(IDS_DDXFOLDER_EDIT_TEXT))
    ASSERT(FALSE);
  BOOL bSuccess = m_Edit.Create(sEditControlText, WS_VISIBLE | WS_CHILD | WS_GROUP, Rect, GetParent(), nIDC);

  //tell the button to call this class when it is clicked
  m_Edit.SetBuddy(this);

  //ensure it is using the same font as the parent
  m_Edit.SetFont(GetParent()->GetFont());

  return bSuccess;
}

void CGetFolderControl::EnableButton(BOOL bEnable)
{
   m_Edit.EnableWindow(bEnable);
}

void CGetFolderControl::Edit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	CChooseDirDlg dlg;
  CString sDir;
  GetWindowText(sDir);
  if (dlg.GetDirectory(sDir, this, m_dwFlags, m_sDialogTitle))
    SetWindowText(sDir);
}

CString CGetFolderControl::GetFolder() const
{
  //Return the folder which thiss control contains as a string
  CString sFolder;
  GetWindowText(sFolder);

  /* Remove any trailing slashes if there is any, unless this is just a drive like C:\ */
  if (!sFolder.IsEmpty())
  {
    int nLength = sFolder.GetLength();
    if (sFolder[nLength-1] == _T('\\') && 3 < nLength) 
      sFolder = sFolder.Left(nLength - 1);
  }

  return sFolder;
}

void CGetFolderControl::SetFolder(const CString& sFolder)
{
  CString sText(sFolder);

  //Remove any trailing slashes if there is any
  if (!sText.IsEmpty())
  {
    int nLength = sText.GetLength();
    if (sText[nLength-1] == _T('\\') && 3 < nLength)
      sText = sText.Left(nLength - 1);
  }

  SetWindowText(sText);
}



void DDX_FolderControl(CDataExchange* pDX, int nIDC,int nIDCBtn, CGetFolderControl& rCGetFolderControl, DWORD dwFlags, const CString& sDialogTitle)
{
  HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
  if (!pDX->m_bSaveAndValidate && rCGetFolderControl.m_hWnd == nullptr)    // not subclassed yet
  {
    if (!rCGetFolderControl.SubclassEdit(hWndCtrl,nIDCBtn))
    {
      ASSERT(FALSE);      // possibly trying to subclass twice ?
      AfxThrowNotSupportedException();
    }
  }
  rCGetFolderControl.SetFlags(dwFlags);
  rCGetFolderControl.SetDialogTitle(sDialogTitle);
}



void DDX_FolderValue(CDataExchange* pDX, CGetFolderControl& rCGetFolderControl, CString& sFolder)
{
  if (pDX->m_bSaveAndValidate)
    sFolder = rCGetFolderControl.GetFolder(); 
  else
    rCGetFolderControl.SetFolder(sFolder);     
}



void DDV_FolderControl(CDataExchange* pDX, CGetFolderControl& rCGetFolderControl, DWORD dwFlags)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (dwFlags & GFLDR_FOLDER_MUST_EXIST)
  {
    BOOL bFolderExists = FALSE;
    CString sFolder = rCGetFolderControl.GetFolder();

    //Check to see if the folder exists
    DWORD dwAttributes = GetFileAttributes(sFolder);
    if (dwAttributes != 0xFFFFFFFF)
      bFolderExists = ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);

   	if (!pDX->m_bSaveAndValidate && !bFolderExists)
	  {
		  TRACE0("Warning: initial dialog data contains a non - existant folder.\n");
		  return;     // don't stop now
    }

    if (pDX->m_bSaveAndValidate && !bFolderExists)
    {
	    AfxMessageBox(IDS_DDXFOLDER_REQUIRE_VALID_FOLDER);
      pDX->PrepareEditCtrl(rCGetFolderControl.GetDlgCtrlID());
	    pDX->Fail();
    }
  }
}


