///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#include "ProgressDlg.h"

// CProgressThread

class CProgressThread : public CWinThread
{
	DECLARE_DYNCREATE(CProgressThread)

protected:
	CProgressThread();           // protected constructor used by dynamic creation
	virtual ~CProgressThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

   virtual BOOL OnIdle(LONG lCount);

   void EndThread();

   HRESULT CreateProgressWindow(CWnd* pParentWnd,DWORD dwMask,UINT nDelay);

   void Init(short begin, short end, short inc);
   void Increment();
   void UpdateMessage( LPCTSTR msg);
   BOOL EnableCancel();
   void EnableCancel(BOOL bEnable);
   BOOL Continue();
   void DestroyProgressWindow();

protected:
   CProgressDlg m_ProgressDlg;
   BOOL m_bCancelEnabled;
   BOOL m_bTerminate;

	DECLARE_MESSAGE_MAP()
};


