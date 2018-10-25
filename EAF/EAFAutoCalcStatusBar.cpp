///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// EAFAutoCalcStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFAutoCalcStatusBar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT indicators[] =
{
   ID_SEPARATOR,           // status line indicator
   EAFID_INDICATOR_STATUS,
   EAFID_INDICATOR_MODIFIED,
   EAFID_INDICATOR_AUTOCALC_ON,
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcStatusBar

CEAFAutoCalcStatusBar::CEAFAutoCalcStatusBar()
{
   m_AutoCalcPaneIdx     = -1;
}

CEAFAutoCalcStatusBar::~CEAFAutoCalcStatusBar()
{
}

BEGIN_MESSAGE_MAP(CEAFAutoCalcStatusBar, CEAFStatusBar)
	//{{AFX_MSG_MAP(CEAFAutoCalcStatusBar)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEAFAutoCalcStatusBar::GetStatusIndicators(const UINT** lppIDArray,int* pnIDCount)
{
   *lppIDArray = indicators;
   *pnIDCount = sizeof(indicators)/sizeof(UINT);
}

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcStatusBar message handlers

void CEAFAutoCalcStatusBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
   CRect rect;

   // AutoCalc Mode
   GetStatusBarCtrl().GetRect(GetAutoCalcPaneIndex(),&rect);
   if (rect.PtInRect(point))
   {
      PostMessage(WM_COMMAND,EAFID_TOGGLE_AUTOCALC,0);
   }

   CEAFStatusBar::OnLButtonDblClk(nFlags, point);
}

int CEAFAutoCalcStatusBar::GetAutoCalcPaneIndex()
{
   if ( m_AutoCalcPaneIdx < 0 )
   {
      for ( int i = 0; i < GetPaneCount(); i++ )
      {
         UINT nID;
         UINT nStyle;
         int cxWidth;
         GetPaneInfo(i,nID,nStyle,cxWidth);

         if ( nID == EAFID_INDICATOR_AUTOCALC_ON )
         {
            m_AutoCalcPaneIdx = i;
            break;
         }
      }
   }

   return m_AutoCalcPaneIdx;
}

void CEAFAutoCalcStatusBar::Reset()
{
   CEAFStatusBar::Reset();

   int idx = GetAutoCalcPaneIndex();
   if ( 0 <= idx )
   {
      SetPaneText( idx, _T("") );
   }
}

void CEAFAutoCalcStatusBar::AutoCalcEnabled( bool bEnable )
{
   CString status_text;
   VERIFY(status_text.LoadString(bEnable ? EAFID_INDICATOR_AUTOCALC_ON : EAFID_INDICATOR_AUTOCALC_OFF));

   int idx = GetAutoCalcPaneIndex();
   if ( 0 <= idx )
   {
      SetPaneText(idx, status_text, TRUE);
   }
}
