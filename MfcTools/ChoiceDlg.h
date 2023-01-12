///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2023  Washington State Department of Transportation
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
#pragma once

#include <MFCTools\HelpHandler.h>

// CChoiceDlg dialog

class CChoiceDlg : public CDialog
{
	DECLARE_DYNAMIC(CChoiceDlg)

public:
	CChoiceDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CChoiceDlg();

// Dialog Data
	enum { IDD = IDD_CHOICE };

   BOOL m_bCancel;
   CString m_Title;
   CString m_Question;
   CString m_Responses;
   int m_Choice;

   CHelpHandler* m_pHelpHandler;

protected:
   CStatic m_Icon;

   virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnInitDialog() override;
   void OnHelp();
};
