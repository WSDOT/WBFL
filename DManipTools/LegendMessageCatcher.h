///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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

#if !defined(AFX_LEGENDMESSAGECATCHER_H__4F0EFCD1_40FD_40C9_87A5_C70ECC623B4D__INCLUDED_)
#define AFX_LEGENDMESSAGECATCHER_H__4F0EFCD1_40FD_40C9_87A5_C70ECC623B4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LegendMessageCatcher.h : header file
//

#define MC_MSG_BASE 100
#define MC_MSG_MAX    200

interface iMessageListener
{
   virtual void OnCaughtMessage(int msg) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// CLegendMessageCatcher window
// This class is not a viewable window. It's sole purpose is to catch messages from menus
// created in the DManipTools dll.
class CLegendMessageCatcher : public CWnd
{
// Construction
public:
	CLegendMessageCatcher(iMessageListener* plistener);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLegendMessageCatcher)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLegendMessageCatcher();

	// Generated message map functions
   void OnMessageCaught(UINT id);

protected:
	//{{AFX_MSG(CLegendMessageCatcher)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	CLegendMessageCatcher();

   iMessageListener* m_pListener;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEGENDMESSAGECATCHER_H__4F0EFCD1_40FD_40C9_87A5_C70ECC623B4D__INCLUDED_)
