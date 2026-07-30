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

// EAFLegalNoticeStep1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFLegalNoticeStep1.h>
#include <EAF\EAFLegalNoticeWiz.h>

// CEAFLegalNoticeStep1 property page

IMPLEMENT_DYNCREATE(CEAFLegalNoticeStep1, CPropertyPage)

CEAFLegalNoticeStep1::CEAFLegalNoticeStep1() : CPropertyPage(IDD_LICENSEWIZ_1)
{
   m_Text = _T("");
   m_License = EAFLicenseType::AROSL;
}

CEAFLegalNoticeStep1::~CEAFLegalNoticeStep1()
{
}

void CEAFLegalNoticeStep1::SetLicense(EAFLicenseType license)
{
   m_License = license;
}

void CEAFLegalNoticeStep1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LIC_TEXT, m_Text);
}


BEGIN_MESSAGE_MAP(CEAFLegalNoticeStep1, CPropertyPage)
END_MESSAGE_MAP()

// CEAFLegalNoticeStep1 message handlers

BOOL CEAFLegalNoticeStep1::OnSetActive()
{
   CPropertySheet* pWiz = (CPropertySheet*)GetParent();
   pWiz->SetWizardButtons( PSWIZB_NEXT );

	return CPropertyPage::OnSetActive();
}

BOOL CEAFLegalNoticeStep1::OnInitDialog()
{
   m_Text = EAFGetLicenseText( m_License );

   CPropertyPage::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
