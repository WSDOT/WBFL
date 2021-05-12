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
#include <dlgs.h>
#include "resource.h"
#include <MfcTools\ddxfile.h>
#include <VersionHelpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


///////////////////////////////// defines /////////////////////////////////////

#define GETFILENAME_EDIT_ID 100

IMPLEMENT_DYNAMIC(CGetFileNameDialog, CFileDialog)

CGetFileNameDialog::CGetFileNameDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName, DWORD dwFlags, LPCTSTR lpszFilter, 
                                       CWnd* pParentWnd) :	CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

BEGIN_MESSAGE_MAP(CGetFileNameDialog, CFileDialog)
	//{{AFX_MSG_MAP(CGetFileNameDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGetFileNameDialog::OnInitDialog() 
{
	CFileDialog::OnInitDialog();

  //modify the text on the IDOK button to ok
  //if we are using the old style common dialog
  if ( ((m_ofn.Flags & OFN_EXPLORER) == 0) || !IsWindowsVersionOrGreater(4,0,0)/*((GetVersion() & 0xff) < 4)*/ )
  {
	  CString sText;
    if (!sText.LoadString(IDS_DDXFILE_OK))
      ASSERT(FALSE);
    CWnd* pOkButton = GetDlgItem(IDOK);
    ASSERT(pOkButton);
    if (pOkButton)
	    pOkButton->SetWindowText(sText);
  }
	
	return TRUE;
}

void CGetFileNameDialog::OnOK()
{
  BOOL bCallParent = TRUE;

  if ( ((m_ofn.Flags & OFN_EXPLORER) == 0) || !IsWindowsVersionOrGreater(4, 0, 0)/*((GetVersion() & 0xff) < 4)*/ )
  {
    //check for overwrite if that flag is used
    if (m_ofn.Flags & OFN_OVERWRITEPROMPT)
    {
      //Retrieve the filename selected
      TCHAR sPath[_MAX_PATH];
      GetDlgItemText(edt1, sPath, _MAX_PATH);

      //check to see if the file already exists
      CFileStatus fs;
      if (CFile::GetStatus(sPath, fs))
      {
        CString sMessage;
        AfxFormatString1(sMessage, IDS_DDXFILE_OVERWRITE_PROMPT, sPath);

        //ensure the title is the same as the common dialog caption
        CString sCaption;
        GetWindowText(sCaption);
        bCallParent = (MessageBox(sMessage, sCaption, MB_YESNO | MB_ICONQUESTION) == IDYES);
      }
    }
  }

  if (bCallParent)
    CFileDialog::OnOK();
}

void CGetFileNameDialog::OnInitDone()
{
	CString sText;
  if (!sText.LoadString(IDS_DDXFILE_OK))
    ASSERT(FALSE);
  LPTSTR pszBuffer = sText.GetBuffer(sText.GetLength());

  //modify the text on the IDOK button to ok
  CommDlg_OpenSave_SetControlText(GetParent()->m_hWnd, IDOK, pszBuffer);

  sText.ReleaseBuffer();
}

BOOL CGetFileNameDialog::OnFileNameOK()
{
  BOOL rVal = CFileDialog::OnFileNameOK();

  if (!rVal)  //if the filename passed the parent tests
             //then put it throught our own tests
  {
    //check for overwrite if that flag is used, since the file open
    //common dialog will not bother looking at this flag
    if (m_ofn.Flags & OFN_OVERWRITEPROMPT)
    {
      //Retrieve the filename selected
      TCHAR sPath[_MAX_PATH];
      CommDlg_OpenSave_GetFilePath(GetParent()->m_hWnd, sPath, _MAX_PATH);

      //check to see if the file already exists
      CFileStatus fs;
      if (CFile::GetStatus(sPath, fs))
      {
        CString sMessage;
        AfxFormatString1(sMessage, IDS_DDXFILE_OVERWRITE_PROMPT, sPath);

        //ensure the title is the same as the common dialog caption
        CString sCaption;
        GetParent()->GetWindowText(sCaption);
        rVal = (MessageBox(sMessage, sCaption, MB_YESNO | MB_ICONQUESTION) != IDYES);
      }
    }
  }
  return rVal;
}



BEGIN_MESSAGE_MAP(CGetFilenameControl, CEdit)
  //{{AFX_MSG_MAP(CGetFilenameControl)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGetFilenameControl::CGetFilenameControl()
{
}

BOOL CGetFilenameControl::SubclassEdit(HWND hEdit,int nIDC)
{   
  //test our inputs
  ASSERT(this);
  if (!IsWindow(hEdit))
  {
    ASSERT(FALSE);
    TRACE(_T("CGetFilenameControl::SubclassEdit -- window handle is invalid!\n"));
    return FALSE;
  }                
  
  //subclass the control
  if (SubclassWindow(hEdit))
    return AddEditButton(nIDC);
  else
  {
    TRACE(_T("CGetFilenameControl::SubclassEdit -- Could not subclass edit control!\n"));
    ASSERT(FALSE);
    return FALSE;
  }
}

BOOL CGetFilenameControl::AddEditButton(int nIDC)
{
  CRect Rect;
  GetWindowRect(Rect);
  GetParent()->ScreenToClient(Rect);
  Rect.left = Rect.right;
  Rect.right = Rect.left + (Rect.Height()*8/10);  //width is 8/10 of height

  //dynamically create the edit button control
  CString sEditControlText;
  if (!sEditControlText.LoadString(IDS_DDXFILE_EDIT_TEXT))
    ASSERT(FALSE);
  BOOL bSuccess = m_Edit.Create(sEditControlText, WS_VISIBLE | WS_CHILD | WS_GROUP, Rect, GetParent(), nIDC);

  //tell the button to call this class when it is clicked
  m_Edit.SetBuddy(this);

  //ensure it is using the same font as the parent
  m_Edit.SetFont(GetParent()->GetFont());

  return bSuccess;
}

void CGetFilenameControl::EnableButton(BOOL bEnable)
{
   m_Edit.EnableWindow(bEnable);
}

void CGetFilenameControl::Edit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

  //bring up the common file open dialog to select the filename

  //retreive the current filename to use as the initial value
  CString sCurrentFilename;
  GetWindowText(sCurrentFilename);

  //work out the flags to use
  DWORD dwFlags = OFN_HIDEREADONLY;
  if (m_dwFlags & GF_OVERWRITEPROMPT)
    dwFlags |= OFN_OVERWRITEPROMPT;
  if (m_dwFlags & GF_FILEMUSTEXIST)
    dwFlags |= OFN_FILEMUSTEXIST;
                 
  CGetFileNameDialog dlg(TRUE, nullptr, nullptr, dwFlags, m_sExtFilter, GetParent());

  //Modify the title to the desired value
  dlg.m_ofn.lpstrTitle = m_sDialogTitle;
  
  //uncomment the following line if you want to use the old style file open Scommon dialog
  if (m_dwFlags & GF_OLD_STYLE_DIALOG)
    dlg.m_ofn.Flags &= ~OFN_EXPLORER;

  //bring up the dialog and if hit ok set the text in this control to the new filename
  if (dlg.DoModal() == IDOK)
    SetWindowText(dlg.GetPathName());
}



void DDX_FilenameControl(CDataExchange* pDX, int nIDC, int nIDCBtn, CGetFilenameControl& rCGetFilenameControl, DWORD dwFlags, const CString& sDialogTitle, const CString& sExtFilter)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

  HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
  if (!pDX->m_bSaveAndValidate && rCGetFilenameControl.m_hWnd == nullptr)    // not subclassed yet
  {
    if (!rCGetFilenameControl.SubclassEdit(hWndCtrl,nIDCBtn))
    {
      ASSERT(FALSE);      // possibly trying to subclass twice ?
      AfxThrowNotSupportedException();
    }
  }
  rCGetFilenameControl.SetFlags(dwFlags);
  rCGetFilenameControl.SetDialogTitle(sDialogTitle);
  rCGetFilenameControl.SetExtensionFilter(sExtFilter);
}



void DDX_FilenameValue(CDataExchange* pDX, CGetFilenameControl& rCGetFilenameControl, CString& sFile)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

  if (pDX->m_bSaveAndValidate)
    rCGetFilenameControl.GetWindowText(sFile); 
  else
    rCGetFilenameControl.SetWindowText(sFile);     
}



void DDV_FilenameControl(CDataExchange* pDX, CGetFilenameControl& rCGetFilenameControl)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

  BOOL bFileExists = FALSE;
  DWORD dwFlags = rCGetFilenameControl.GetFlags();
	if (dwFlags & GF_FILEMUSTEXIST)
  {
    CString sFile;
    rCGetFilenameControl.GetWindowText(sFile);

    //Check to see if the file exists
    DWORD dwAttributes = GetFileAttributes(sFile);
    if (dwAttributes != 0xFFFFFFFF)
      bFileExists = ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0);

   	if (!pDX->m_bSaveAndValidate && !bFileExists)
	  {
		  TRACE(_T("Warning: initial dialog data contains a non - existant file name.\n"));
		  return;     // don't stop now
    }

    if (pDX->m_bSaveAndValidate && !bFileExists)
    {
	    AfxMessageBox(IDS_DDXFILE_REQUIRE_VALID_FILE);
      pDX->PrepareEditCtrl(rCGetFilenameControl.GetDlgCtrlID());
	    pDX->Fail();
    }
  }

	if (dwFlags & GF_OVERWRITEPROMPT)
  {
    CString sFile;
    rCGetFilenameControl.GetWindowText(sFile);

    //Check to see if the file exists
    DWORD dwAttributes = GetFileAttributes(sFile);
    if (dwAttributes != 0xFFFFFFFF)
      bFileExists = ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0);

    if (pDX->m_bSaveAndValidate && bFileExists)
    {
      CString sMsg;
      AfxFormatString1(sMsg, IDS_DDXFILE_OVERWRITE_PROMPT, sFile);
	    if (AfxMessageBox(sMsg, MB_YESNO | MB_ICONQUESTION) != IDYES)
      {
        pDX->PrepareEditCtrl(rCGetFilenameControl.GetDlgCtrlID());
	      pDX->Fail();
      }
    }
  }
}
