// TestProgress.h : main header file for the TESTPROGRESS application
//

#if !defined(AFX_TESTPROGRESS_H__0AD12FED_78FE_4B49_B90C_1D124CCDDA13__INCLUDED_)
#define AFX_TESTPROGRESS_H__0AD12FED_78FE_4B49_B90C_1D124CCDDA13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "TestProgress_i.h"

/////////////////////////////////////////////////////////////////////////////
// CTestProgressApp:
// See TestProgress.cpp for the implementation of this class
//

class CTestProgressApp : public CWinApp
{
public:
	CTestProgressApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestProgressApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestProgressApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPROGRESS_H__0AD12FED_78FE_4B49_B90C_1D124CCDDA13__INCLUDED_)
