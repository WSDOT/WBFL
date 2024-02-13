
// DManipDemo.h : main header file for the DManipDemo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDManipDemoApp:
// See DManipDemo.cpp for the implementation of this class
//

class CDManipDemoApp : public CWinApp
{
public:
	CDManipDemoApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDManipDemoApp theApp;
