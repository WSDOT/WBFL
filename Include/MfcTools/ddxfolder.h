///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef __DDXFOLDER_H__
#define __DDXFOLDER_H__
#pragma once

#include <MfcTools\ModifyButton.h>
#include <MfcTools\MfcToolsExp.h>

////////////////////////////////// Consts /////////////////////////////////////

//flags used to control how the DDX_FolderControl routine works

const DWORD GFLDR_OLD_STYLE_DIALOG = 0x0001;   //Use the old style file open dialog instead of the
                                               //style as used in Windows Explorer


//Flags used to control how the DDV_FolderControl routine works

const DWORD GFLDR_FOLDER_MUST_EXIST = 0x0001;  //Fail validation if the folder does not exist.


////////////////////// foward declaration ///////////////////////////


class MFCTOOLSCLASS CGetFolderControl : public CEdit, public IGetEdit
{
public:
//Constructors / Destructors
  CGetFolderControl();

//Methods
  BOOL SubclassEdit(HWND hEdit,int nIDC);

//Accessors/Mutators
  //Set/Get the flags
  void SetFlags(DWORD dwFlags) { m_dwFlags = dwFlags; };
  DWORD GetFlags() const { return m_dwFlags; };

  //Set/Get the dialog title
  void SetDialogTitle(const CString& sDialogTitle) { m_sDialogTitle = sDialogTitle; };
  CString GetDialogTitle() const { return m_sDialogTitle; };

  //Set/Get the actual value
  CString GetFolder() const;
  void SetFolder(const CString& sFolder);

  //Bring up the directory picker dialog
  void Edit();

  void EnableButton(BOOL bEnable=TRUE);

protected:
  //{{AFX_VIRTUAL(CGetFolderControl)
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CGetFolderControl)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

  BOOL AddEditButton(int nIDC);

  CModifyButton m_Edit;
  DWORD         m_dwFlags;
  CString       m_sDialogTitle;
};





/////////////// MFC Data exchange routines //////////////////////////

void MFCTOOLSFUNC DDX_FolderControl(CDataExchange* pDX, int nIDC,int nIDCBtn, CGetFolderControl& rCGetFolderControl, DWORD dwFlags, const CString& sDialogTitle);
void MFCTOOLSFUNC DDX_FolderValue(CDataExchange* pDX, CGetFolderControl& rCGetFolderControl, CString& sFolder);
void MFCTOOLSFUNC DDV_FolderControl(CDataExchange* pDX, CGetFolderControl& rCGetFolderControl, DWORD dwFlags);


#endif //_DDXFOLDER_H__