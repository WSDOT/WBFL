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

// LoadModifierPage.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include <MFCTools\LoadModifierPage.h>
#include <MFCTools\CustomDDX.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static DWORD CALLBACK StreamInCtrl(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb )
{
   CString* psBuffer = (CString*)dwCookie;
   if ( psBuffer->GetLength() < cb )
      cb = psBuffer->GetLength();

   for ( int i = 0; i < cb; i++ )
   {
      *(pbBuff+i) = (BYTE)psBuffer->GetAt(i);
   }
   *pcb = cb;
   *psBuffer = psBuffer->Mid(cb);
   return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CLoadModifierPage property page

CLoadModifierPage::CLoadModifierPage(const CString& t1,const CString& t2,const CString& t3,TCHAR ss) :
CPropertyPage(CLoadModifierPage::IDD),
m_Text1( t1 ),
m_Text2( t2 ),
m_Text3( t3 ),
m_Subscript( ss )
{
	//{{AFX_DATA_INIT(CLoadModifierPage)
	m_LimitStateFactor = 0.0;
	m_Flag = 1;
	//}}AFX_DATA_INIT

   AfxInitRichEdit2();
}

CLoadModifierPage::~CLoadModifierPage()
{
}

void CLoadModifierPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadModifierPage)
	DDX_Text(pDX, IDC_N, m_LimitStateFactor);
	DDX_Radio(pDX, IDC_RADIO1, m_Flag);
	//}}AFX_DATA_MAP

   if ( m_Flag != 1 )
     DDV_LimitOrMore( pDX, IDC_N, m_LimitStateFactor, (m_Flag == 0 ? 1.05 : 0.95) );
}


BEGIN_MESSAGE_MAP(CLoadModifierPage, CPropertyPage)
	//{{AFX_MSG_MAP(CLoadModifierPage)
	ON_BN_CLICKED(IDC_RADIO1, OnRadioButtonChanged)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_RADIO2, OnRadioButtonChanged)
	ON_BN_CLICKED(IDC_RADIO3, OnRadioButtonChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadModifierPage message handlers

BOOL CLoadModifierPage::OnInitDialog() 
{
   m_psp.dwFlags |= PSP_HASHELP;

   CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

   CString label1;
   CString label2;

   CRichEditCtrl* pLabel = (CRichEditCtrl*)GetDlgItem(IDC_N_LABEL);
   ASSERT( pLabel );
   pLabel->SetBackgroundColor(FALSE, GetSysColor(COLOR_3DFACE) );
   label1.Format(_T("{\\rtf1\\ansi\\deff0\\deftab720{\\fonttbl{\\f0\\fswiss MS Sans Serif;}{\\f1\\froman\\fcharset2 Symbol;}{\\f2\\froman\\fprq2\\fcharset2 Symbol;}{\\f3\\froman Times New Roman;}}{\\colortbl\\red0\\green0\\blue0;}\\deflang1033\\pard\\plain\\f2\\fs20 h\\plain\\f3\\fs20 \\sub %lc\\nosupersub\\par }"),m_Subscript);
   EDITSTREAM es;
   es.dwCookie = (DWORD)(&label1);
   es.dwError = 0;
   es.pfnCallback = StreamInCtrl;
   pLabel->StreamIn( SF_RTF, es );

   pLabel = (CRichEditCtrl*)GetDlgItem(IDC_N_SERVICE);
   ASSERT( pLabel );
   pLabel->SetBackgroundColor(FALSE, GetSysColor(COLOR_3DFACE) );
   label2.Format(_T("{\\rtf1\\ansi\\deff0\\deftab720{\\fonttbl{\\f0\\fswiss MS Sans Serif;}{\\f1\\froman\\fcharset2 Symbol;}{\\f2\\froman\\fprq2\\fcharset2 Symbol;}{\\f3\\froman Times New Roman;}}{\\colortbl\\red0\\green0\\blue0;}\\deflang1033\\pard\\plain\\f2\\fs20 h\\plain\\f3\\fs20 \\sub %lc\\nosupersub = 1.0 for all other limit states.\\par }"),m_Subscript);
   es.dwCookie = (DWORD)(&label2);
   pLabel->StreamIn( SF_RTF, es );

   CButton* pButton;
   pButton = (CButton*)GetDlgItem(IDC_RADIO1);
   ASSERT( pButton );
   pButton->SetWindowText( m_Text1 );

   pButton = (CButton*)GetDlgItem(IDC_RADIO2);
   ASSERT( pButton );
   pButton->SetWindowText( m_Text2 );

   pButton = (CButton*)GetDlgItem(IDC_RADIO3);
   ASSERT( pButton );
   pButton->SetWindowText( m_Text3 );

   OnRadioButtonChanged();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoadModifierPage::OnRadioButtonChanged() 
{
	// TODO: Add your control notification handler code here
   bool bEnable = false;
   CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO2);
   ASSERT( pButton );
   if ( pButton->GetCheck() == 0 ) // Not checked
      bEnable = true;

   CEdit* pEdit = (CEdit*)GetDlgItem(IDC_N);
   ASSERT( pEdit );
   pEdit->EnableWindow( bEnable ? TRUE : FALSE );

   if ( !bEnable )
      pEdit->SetWindowText(_T("1.0"));
}
