///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2019  Washington State Department of Transportation
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
#include "MfcTools\choosedirdlg.h"
#include "shlobj.h"
#include <dlgs.h>
#include <VersionHelpers.h>


//////////////////////////////// Defines //////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



///////////////////////////////// Implementation //////////////////////////////

class COldFileDirDialog : public CFileDialog
{
public:
// Public data members
  BOOL m_bDlgJustCameUp;
    
// Constructors
  COldFileDirDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
                 LPCTSTR lpszDefExt = nullptr,
                 LPCTSTR lpszFileName = nullptr,
                 DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                 LPCTSTR lpszFilter = nullptr,
                 CWnd* pParentWnd = nullptr);
                                          
// Implementation
protected:
  //{{AFX_MSG(COldFileDirDialog)
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};





COldFileDirDialog::COldFileDirDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, 
                                     LPCTSTR lpszFileName, DWORD dwFlags, 
                                     LPCTSTR lpszFilter, CWnd* pParentWnd) 
  : CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
  //{{AFX_DATA_INIT(COldFileDirDialog)
  //}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(COldFileDirDialog, CFileDialog)
  //{{AFX_MSG_MAP(COldFileDirDialog)
  ON_WM_PAINT()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL COldFileDirDialog::OnInitDialog()
{  
  //CenterWindow();

  //Let's hide these windows so the user cannot tab to them.  Note that in
  //the private template the coordinates for these guys are
  //*outside* the coordinates of the dlg window itself.  Without the following
  //ShowWindow()'s you would not see them, but could still tab to them.
    
  GetDlgItem(stc2)->ShowWindow(SW_HIDE);
  GetDlgItem(stc3)->ShowWindow(SW_HIDE);
  GetDlgItem(edt1)->ShowWindow(SW_HIDE);
  GetDlgItem(lst1)->ShowWindow(SW_HIDE);
  GetDlgItem(cmb1)->ShowWindow(SW_HIDE);
    
  //We must put something in this field, even though it is hidden.  This is
  //because if this field is empty, or has something like "*.txt" in it,
  //and the user hits OK, the dlg will NOT close.  We'll jam something in
  //there (like "Junk") so when the user hits OK, the dlg terminates.
  //Note that we'll deal with the "Junk" during return processing (see below)

  SetDlgItemText(edt1, _T("Junk"));

  //Now set the focus to the directories listbox.  Due to some painting
  //problems, we *must* also process the first WM_PAINT that comes through
  //and set the current selection at that point.  Setting the selection
  //here will NOT work.  See comment below in the on paint handler.
            
  GetDlgItem(lst2)->SetFocus();
            
  m_bDlgJustCameUp=TRUE;
               
  CFileDialog::OnInitDialog();
     
  return(FALSE);
}
  
void COldFileDirDialog::OnPaint()
{
  CPaintDC dc(this); // device context for painting
    
  //This code makes the directory listbox "highlight" an entry when it first
  //comes up.  W/O this code, the focus is on the directory listbox, but no
  //focus rectangle is drawn and no entries are selected.  Ho hum.

  if (m_bDlgJustCameUp)
  {
    m_bDlgJustCameUp=FALSE;
    SendDlgItemMessage(lst2, LB_SETCURSEL, 0, 0L);
  }
    
  // Do not call CFileDialog::OnPaint() for painting messages
}

int CALLBACK CChooseDirDlg::SetSelProc(HWND hWnd, UINT uMsg, LPARAM /*lParam*/, LPARAM lpData)
{
  if (uMsg == BFFM_INITIALIZED)
    ::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);

  return 0;
}

BOOL CChooseDirDlg::GetDirectory(CString& sDir, CWnd* pWndParent, BOOL bOldStyleDialog, const CString& sTitle)
{
  BOOL bSuccess = FALSE;

  //BYTE WinMajorVersion = LOBYTE(LOWORD(GetVersion()));
  //if ((WinMajorVersion >= 4) && !bOldStyleDialog) //Running on Windows 95 shell and new style requested
  if ( IsWindowsVersionOrGreater(4,0,0) && !bOldStyleDialog )
  {
    TCHAR sDisplayName[_MAX_PATH];
    BROWSEINFO bi;
    bi.hwndOwner = pWndParent->GetSafeHwnd();
    bi.pidlRoot = nullptr;
    bi.lpszTitle =  sTitle;
    bi.pszDisplayName = sDisplayName;
    bi.ulFlags = BIF_RETURNONLYFSDIRS;
    bi.lpfn = SetSelProc;
    bi.lParam = (LPARAM)(LPCTSTR)sDir;
	  LPITEMIDLIST pItemIDList = SHBrowseForFolder(&bi);

    if (pItemIDList)
    {
      TCHAR sPath[_MAX_PATH];
      if (SHGetPathFromIDList(pItemIDList, sPath))
      {
        bSuccess = TRUE;
        sDir = sPath;
      }

      //avoid memory leaks by deleting the PIDL
      //using the shells task allocator
      IMalloc* pMalloc;
      if (SHGetMalloc(&pMalloc) != NOERROR)
      {
        TRACE(_T("Failed to get pointer to shells task allocator"));
        bSuccess = FALSE;
      }
      pMalloc->Free(pItemIDList);
      if (pMalloc)
        pMalloc->Release();
    }
  }
  else  //Use old style if requested or when running on NT 3.51 where we have no choice
  {
    COldFileDirDialog dlg(FALSE, nullptr, nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLETEMPLATE, nullptr, pWndParent);
    dlg.m_ofn.Flags &= ~OFN_EXPLORER; //Turn of the explorer style customisation
    dlg.m_ofn.hInstance = AfxGetInstanceHandle();
    dlg.m_ofn.lpTemplateName = MAKEINTRESOURCE(FILEOPENORD);
    dlg.m_ofn.lpstrInitialDir = sDir;
    dlg.m_ofn.lpstrTitle = sTitle;
    if (dlg.DoModal() == IDOK)
    {
      dlg.m_ofn.lpstrFile[dlg.m_ofn.nFileOffset-1] = 0; //Nuke the "Junk" text filename
      bSuccess = TRUE;
      sDir = dlg.m_ofn.lpstrFile;

    }
  }

  return bSuccess;
}



