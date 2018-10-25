// GraphicsTest.h : main header file for the GRAPHICSTEST application
//

#if !defined(AFX_GRAPHICSTEST_H__09BC96C6_8907_11D1_9C68_00609710E6CE__INCLUDED_)
#define AFX_GRAPHICSTEST_H__09BC96C6_8907_11D1_9C68_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestApp:
// See GraphicsTest.cpp for the implementation of this class
//

class CGraphicsTestApp : public CWinApp
{
public:
	CGraphicsTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGraphicsTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSTEST_H__09BC96C6_8907_11D1_9C68_00609710E6CE__INCLUDED_)
