// MfcTools.h : main header file for the MFCTOOLS DLL
//

#if !defined(AFX_MFCTOOLS_H__3C5D7EEB_3089_11D2_9D3D_00609710E6CE__INCLUDED_)
#define AFX_MFCTOOLS_H__3C5D7EEB_3089_11D2_9D3D_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcToolsApp
// See MfcTools.cpp for the implementation of this class
//

class CMfcToolsApp : public CWinApp
{
public:
	CMfcToolsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcToolsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMfcToolsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCTOOLS_H__3C5D7EEB_3089_11D2_9D3D_00609710E6CE__INCLUDED_)
