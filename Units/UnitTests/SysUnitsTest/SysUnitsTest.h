// SysUnitsTest.h : main header file for the SYSUNITSTEST application
//

#if !defined(AFX_SYSUNITSTEST_H__7FA7E94A_578A_11D1_8AC0_0000F8776D5D__INCLUDED_)
#define AFX_SYSUNITSTEST_H__7FA7E94A_578A_11D1_8AC0_0000F8776D5D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSysUnitsTestApp:
// See SysUnitsTest.cpp for the implementation of this class
//

class CSysUnitsTestApp : public CWinApp
{
public:
	CSysUnitsTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysUnitsTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSysUnitsTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSUNITSTEST_H__7FA7E94A_578A_11D1_8AC0_0000F8776D5D__INCLUDED_)
