// Watermark.h : main header file for the WATERMARK application
//

#if !defined(AFX_WATERMARK_H__FD924336_315B_11D2_8EB6_006097DF3C68__INCLUDED_)
#define AFX_WATERMARK_H__FD924336_315B_11D2_8EB6_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWatermarkApp:
// See Watermark.cpp for the implementation of this class
//

class CWatermarkApp : public CWinApp
{
public:
	CWatermarkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatermarkApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWatermarkApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATERMARK_H__FD924336_315B_11D2_8EB6_006097DF3C68__INCLUDED_)
