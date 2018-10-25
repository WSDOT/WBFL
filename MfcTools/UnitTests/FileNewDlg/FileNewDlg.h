// FileNewDlg.h : main header file for the FILENEWDLG application
//

#if !defined(AFX_FILENEWDLG_H__BD01DE77_5A3D_11D2_9D69_00609710E6CE__INCLUDED_)
#define AFX_FILENEWDLG_H__BD01DE77_5A3D_11D2_9D69_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgApp:
// See FileNewDlg.cpp for the implementation of this class
//

class CFileNewDlgApp : public CWinApp
{
public:
	CFileNewDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileNewDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFileNewDlgApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENEWDLG_H__BD01DE77_5A3D_11D2_9D69_00609710E6CE__INCLUDED_)
