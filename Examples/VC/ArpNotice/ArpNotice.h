// ArpNotice.h : main header file for the ARPNOTICE application
//

#if !defined(AFX_ARPNOTICE_H__790C005C_8D43_11D3_89DC_006097C68A9C__INCLUDED_)
#define AFX_ARPNOTICE_H__790C005C_8D43_11D3_89DC_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <WBFLTools.h>

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeApp:
// See ArpNotice.cpp for the implementation of this class
//

class CArpNoticeApp : public CWinApp
{
public:
	CArpNoticeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArpNoticeApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

   AcceptanceType ShowLegalNotice(VARIANT_BOOL bGiveChoice);

// Implementation
	//{{AFX_MSG(CArpNoticeApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHelpLegal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
   VARIANT_BOOL m_bShowLegalNotice;
   AcceptanceType ShowLegalNoticeAtStartup(void);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARPNOTICE_H__790C005C_8D43_11D3_89DC_006097C68A9C__INCLUDED_)
