// Dimension.h : main header file for the DIMENSION application
//

#if !defined(AFX_DIMENSION_H__2FC36C66_6F5A_11D2_9D88_00609710E6CE__INCLUDED_)
#define AFX_DIMENSION_H__2FC36C66_6F5A_11D2_9D88_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDimensionApp:
// See Dimension.cpp for the implementation of this class
//

class CDimensionApp : public CWinApp
{
public:
	CDimensionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDimensionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDimensionApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIMENSION_H__2FC36C66_6F5A_11D2_9D88_00609710E6CE__INCLUDED_)
