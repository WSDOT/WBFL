///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2022  Washington State Department of Transportation
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

// WatermarkMainFrm.cpp
//

#include "stdafx.h"

#include <MfcTools\WatermarkMainFrm.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CWatermarkMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CWatermarkMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CWatermarkMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWatermarkMainFrame construction/destruction

CWatermarkMainFrame::CWatermarkMainFrame(UINT nIDResource)
{
	// TODO: add member initialization code here
   m_nIDResource = nIDResource;
   m_lpszResourceName = 0;
}

CWatermarkMainFrame::CWatermarkMainFrame(LPCTSTR lpszResourceName)
{
	// TODO: add member initialization code here
   m_nIDResource = 0;
   CollectionIndexType nChar = _tcslen(lpszResourceName)+1;
   m_lpszResourceName = new TCHAR[nChar];
   _tcscpy_s( m_lpszResourceName, nChar, lpszResourceName );
}

CWatermarkMainFrame::~CWatermarkMainFrame()
{
   if ( m_lpszResourceName )
   {
      delete m_lpszResourceName;
      m_lpszResourceName = 0;
   }
}

int CWatermarkMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

   int retval;
	if ( m_lpszResourceName != 0 )
	{
	   retval = m_Watermark.MarkIt( m_lpszResourceName, m_hWndMDIClient );
   }
   else
   {
	   retval = m_Watermark.MarkIt( m_nIDResource, m_hWndMDIClient );
   }

   if ( retval == -1 )
   {
      TRACE("Failed to create watermark");
     return -1;
   }

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CWatermarkMainFrame diagnostics

#ifdef _DEBUG
void CWatermarkMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CWatermarkMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG
