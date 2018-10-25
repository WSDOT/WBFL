///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
#pragma once

#define WM_TERMINATE_HELP_WINDOW_THREAD WM_USER+1

class CEAFHelpWindowThread : public CWinThread
{
	DECLARE_DYNCREATE(CEAFHelpWindowThread)

protected:
	CEAFHelpWindowThread();           // protected constructor used by dynamic creation
	virtual ~CEAFHelpWindowThread();

public:
	virtual BOOL InitInstance();
   virtual int ExitInstance();

   void Navigate(LPCTSTR lpszURL);
   afx_msg void OnKillThread(WPARAM wParam,LPARAM lParam);

protected:
	DECLARE_MESSAGE_MAP()
   CEvent m_Event;
};


