///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2018  Washington State Department of Transportation
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


////////////////////////////////// Macros ///////////////////////////

#ifndef _DDXFILE_H__
#define _DDXFILE_H__
#pragma once

#include <MfcTools\ModifyButton.h>
#include <MfcTools\MfcToolsExp.h>
#include <afxdlgs.h>

////////////////////////////////// Consts /////////////////////////////////////

//flags used to control how the DDX_GetFilenameControl routine workds

const DWORD GF_OVERWRITEPROMPT  = 0x0001;   //User will be prompted about overwriting existing file 
                                            //prior to allowing selection
const DWORD GF_FILEMUSTEXIST    = 0x0002;   //File must exist to be selected
const DWORD GF_OLD_STYLE_DIALOG = 0x0004;   //Use the old style file open dialog instead of the
                                            //style as used in Windows Explorer


class MFCTOOLSCLASS CGetFileNameDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CGetFileNameDialog)

public:
	CGetFileNameDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt = nullptr, LPCTSTR lpszFileName = nullptr,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	LPCTSTR lpszFilter = nullptr, CWnd* pParentWnd = nullptr);

protected:
  virtual void OnInitDone();
  virtual BOOL OnFileNameOK();

	//{{AFX_MSG(CGetFileNameDialog)
	//}}AFX_MSG
  virtual BOOL OnInitDialog() override;
  virtual void OnOK() override;

	DECLARE_MESSAGE_MAP()
};


class MFCTOOLSCLASS CGetFilenameControl : public CEdit, public IGetEdit
{
public:
//Constructors / Destructors
  CGetFilenameControl();

//Methods
  BOOL SubclassEdit(HWND hEdit,int nIDC);

//Accessors/Mutators
  //Set/Get the flags
  void SetFlags(DWORD dwFlags) { m_dwFlags = dwFlags; };
  DWORD GetFlags() const { return m_dwFlags; };

  //Set/Get the dialog title
  void SetDialogTitle(const CString& sDialogTitle) { m_sDialogTitle = sDialogTitle; };
  CString GetDialogTitle() const { return m_sDialogTitle; };

  //Set/Get the extension filter string
  void SetExtensionFilter(const CString& sExtFilter) { m_sExtFilter = sExtFilter; };
  CString GetExtensionFilter() const { return m_sExtFilter; };

  void EnableButton(BOOL bEnable = TRUE);

  //Bring up the file picker dialog
  void Edit();

protected:
  //{{AFX_VIRTUAL(CGetFilenameControl)
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CGetFilenameControl)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

  BOOL AddEditButton(int nIDC);

  CModifyButton m_Edit;
  DWORD         m_dwFlags;
  CString       m_sDialogTitle;
  CString       m_sExtFilter;
};





/////////////// MFC Data exchange routines //////////////////////////

void MFCTOOLSFUNC DDX_FilenameControl(CDataExchange* pDX, int nIDC, int nIDCBtn,CGetFilenameControl& rCGetFilenameControl, DWORD dwFlags, const CString& sDialogTitle, const CString& sExtFilter);
void MFCTOOLSFUNC DDX_FilenameValue(CDataExchange* pDX, CGetFilenameControl& rCGetFilenameControl, CString& sFile);
void MFCTOOLSFUNC DDV_FilenameControl(CDataExchange* pDX, CGetFilenameControl& rCGetFilenameControl);


#endif //_DDXFILE_H__