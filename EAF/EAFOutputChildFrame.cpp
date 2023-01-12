///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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


// EAFOutputChildFrame.cpp : implementation of the CEAFOutputChildFrame class
//

#include "stdafx.h"
#include <EAF\EAFOutputChildFrame.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFOutputChildFrame

IMPLEMENT_DYNCREATE(CEAFOutputChildFrame, CEAFLicensePlateChildFrame)

BEGIN_MESSAGE_MAP(CEAFOutputChildFrame, CEAFLicensePlateChildFrame)
	//{{AFX_MSG_MAP(CEAFOutputChildFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFOutputChildFrame construction/destruction

CEAFOutputChildFrame::CEAFOutputChildFrame()
{
}

CEAFOutputChildFrame::~CEAFOutputChildFrame()
{
}

BOOL CEAFOutputChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
   // :TRICKY: rab 11.23.96 : Modifying default behavior
	// By turning off the default MFC-defined FWS_ADDTOTITLE style,
	// the framework will use first string in the document template
	// STRINGTABLE resource instead of the document name.

	cs.style &= ~(LONG)FWS_ADDTOTITLE;
	return CEAFLicensePlateChildFrame::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEAFOutputChildFrame diagnostics

#ifdef _DEBUG
void CEAFOutputChildFrame::AssertValid() const
{
	CEAFLicensePlateChildFrame::AssertValid();
}

void CEAFOutputChildFrame::Dump(CDumpContext& dc) const
{
	CEAFLicensePlateChildFrame::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEAFOutputChildFrame message handlers

void CEAFOutputChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	if (bAddToTitle && (GetStyle() & FWS_ADDTOTITLE) == 0)
   {

      // TRICKY:
      // we expect our view to provide is with text
      CView* pv = this->GetActiveView();

      if ( pv )
      {
         ASSERT(pv!=0);
         CString name;
         pv->GetWindowText(name);

         // set our title
		   AfxSetWindowText(m_hWnd, name);
      }
   }
   else
   {
      CEAFLicensePlateChildFrame::OnUpdateFrameTitle(bAddToTitle);
   }
}
