///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include "afxwin.h"
#include "resource.h"

// CQuestionDlg dialog

class CQuestionDlg : public CDialog
{
	DECLARE_DYNAMIC(CQuestionDlg)

public:
	CQuestionDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CQuestionDlg();

// Dialog Data
	enum { IDD = IDD_QUESTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
   CStatic m_Icon;

public:
   CString m_Title;
   CString m_Question;
   CString m_Answer;

   virtual BOOL OnInitDialog() override;
};
