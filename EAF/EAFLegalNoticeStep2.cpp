///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright � 1999-2026  Washington State Department of Transportation
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

// EAFLegalNoticeStep2.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFLegalNoticeStep2.h>
#include <EAF\EAFLegalNoticeWiz.h>

// CEAFLegalNoticeStep2 dialog

IMPLEMENT_DYNCREATE(CEAFLegalNoticeStep2, CPropertyPage)

CEAFLegalNoticeStep2::CEAFLegalNoticeStep2() : CPropertyPage(IDD_LICENSEWIZ_2)
{
   m_DontShowAgain = FALSE;
   m_Text = _T("");
}

CEAFLegalNoticeStep2::~CEAFLegalNoticeStep2()
{
}

void CEAFLegalNoticeStep2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK, m_DontShowAgain);
	DDX_Text(pDX, IDC_DISCLAIMER, m_Text);
}


BEGIN_MESSAGE_MAP(CEAFLegalNoticeStep2, CPropertyPage)
END_MESSAGE_MAP()

// CEAFLegalNoticeStep2 message handlers

BOOL CEAFLegalNoticeStep2::OnSetActive()
{
   CPropertySheet* pWiz = (CPropertySheet*)GetParent();
   pWiz->SetWizardButtons( PSWIZB_BACK | PSWIZB_FINISH );

	return CPropertyPage::OnSetActive();
}

BOOL CEAFLegalNoticeStep2::OnWizardFinish()
{
   UpdateData();

	return CPropertyPage::OnWizardFinish();
}

BOOL CEAFLegalNoticeStep2::OnInitDialog()
{
   m_Text = EAFGetDisclaimerText();

	CPropertyPage::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
