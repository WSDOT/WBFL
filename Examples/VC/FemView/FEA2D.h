// FEA2D.h : main header file for the FEA2D application
//

#if !defined(AFX_FEA2D_H__BCB8A0E7_E659_11D4_8B81_006097C68A9C__INCLUDED_)
#define AFX_FEA2D_H__BCB8A0E7_E659_11D4_8B81_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include <WBFLDManip.h>

/////////////////////////////////////////////////////////////////////////////
// CFEA2DApp:
// See FEA2D.cpp for the implementation of this class
//

class CFEA2DApp : public CWinApp
{
public:
	CFEA2DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFEA2DApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFEA2DApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEA2D_H__BCB8A0E7_E659_11D4_8B81_006097C68A9C__INCLUDED_)
