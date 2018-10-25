// LBAMViewer.h : main header file for the LBAMVIEWER application
//

#if !defined(AFX_LBAMVIEWER_H__FDE87788_2325_4709_8169_46AEC1E48624__INCLUDED_)
#define AFX_LBAMVIEWER_H__FDE87788_2325_4709_8169_46AEC1E48624__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "LBAMViewer_i.h"

#include <WBFLDManip.h>
#include <WBFLDManipTools.h>

/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerApp:
// See LBAMViewer.cpp for the implementation of this class
//

class CLBAMViewerApp : public CWinApp
{
public:
	CLBAMViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLBAMViewerApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CLBAMViewerApp)
	afx_msg void OnAppAbout();
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

#endif // !defined(AFX_LBAMVIEWER_H__FDE87788_2325_4709_8169_46AEC1E48624__INCLUDED_)
