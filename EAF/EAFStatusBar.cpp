///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

// EAFStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFResources.h>
#include <EAF\EAFStatusBar.h>
#include <EAF\EAFDocument.h>
#include <EAF\StatusCenter.h>
#include <Colors.h>

#define STATUS_OK_COLOR    GREEN
#define STATUS_WARN_COLOR  YELLOW
#define STATUS_ERROR_COLOR RED

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CEAFStatusBar

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_MODIFIED,
   ID_INDICATOR_STATUS,
   ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

IMPLEMENT_DYNAMIC(CEAFStatusBar, CStatusBar)

CEAFStatusBar::CEAFStatusBar()
{
   m_nIndicators     = -1;
   m_ModifiedPaneIdx = -1;
   m_StatusPaneIdx   = -1;
}

CEAFStatusBar::~CEAFStatusBar()
{
}


BEGIN_MESSAGE_MAP(CEAFStatusBar, CStatusBar)
   ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CEAFStatusBar message handlers


void CEAFStatusBar::GetStatusIndicators(const UINT** lppIDArray,int* pnIDCount)
{
   *lppIDArray = indicators;
   *pnIDCount = sizeof(indicators)/sizeof(UINT);
}

BOOL CEAFStatusBar::Create(CWnd* pParentWnd, DWORD dwStyle , UINT nID)
{
   BOOL bResult = CStatusBar::Create(pParentWnd, dwStyle, nID);
   if ( !bResult )
      return bResult;

   const UINT* pIndicators;
   GetStatusIndicators(&pIndicators,&m_nIndicators);
   bResult = SetIndicators(pIndicators,m_nIndicators);

   int idx = GetStatusPaneIndex();
   if ( 0 <= idx )
      SetPaneStyle( idx, SBPS_NORMAL | SBT_OWNERDRAW );

   idx = GetModifiedPaneIndex();
   if ( 0 <= idx )
      SetPaneStyle( idx, SBPS_DISABLED );

   for ( int i = 0; i < m_nIndicators; i++ )
   {
      UINT style = GetPaneStyle(i);
      style |= SBPS_NOBORDERS;
      SetPaneStyle(i,style);
   }

   return bResult;
}

void CEAFStatusBar::EnableModifiedFlag(BOOL bEnable)
{
   UINT style = (bEnable ? SBPS_NORMAL : SBPS_DISABLED) | SBPS_NOBORDERS;
   int idx = GetModifiedPaneIndex();
   if ( 0 <= idx )
      SetPaneStyle(idx, style );
}

int CEAFStatusBar::GetPaneCount()
{
   return m_nIndicators;
}

int CEAFStatusBar::GetModifiedPaneIndex()
{
   if ( m_ModifiedPaneIdx < 0 )
   {
      for ( int i = 0; i < m_nIndicators; i++ )
      {
         UINT nID;
         UINT nStyle;
         int cxWidth;
         GetPaneInfo(i,nID,nStyle,cxWidth);

         if ( nID == ID_INDICATOR_MODIFIED )
         {
            m_ModifiedPaneIdx = i;
            break;
         }
      }
   }
   return m_ModifiedPaneIdx;
}

int CEAFStatusBar::GetStatusPaneIndex()
{
   if ( m_StatusPaneIdx < 0 )
   {
      for ( int i = 0; i < m_nIndicators; i++ )
      {
         UINT nID;
         UINT nStyle;
         int cxWidth;
         GetPaneInfo(i,nID,nStyle,cxWidth);

         if ( nID == ID_INDICATOR_STATUS )
         {
            m_StatusPaneIdx = i;
            break;
         }
      }
   }
   return m_StatusPaneIdx;
}

CEAFDocument* CEAFStatusBar::GetDocument()
{
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   if ( pFrame->IsKindOf(RUNTIME_CLASS(CFrameWnd)) )
   {
      CMDIChildWnd* pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
      CView* pView = pChild->GetActiveView();
      CDocument* pDoc = NULL;
      if ( pView )
         pDoc = pView->GetDocument();

      if ( pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CEAFDocument)) )
      {
         CEAFDocument* pEAFDoc = (CEAFDocument*)pDoc;
         return pEAFDoc;
      }
   }

   return NULL;
}

void CEAFStatusBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

   COLORREF color;

   CollectionIndexType status_count = 0;

   CEAFDocument* pEAFDoc = GetDocument();
   if ( pEAFDoc )
   {
      CEAFStatusCenter& status_center = pEAFDoc->GetStatusCenter();
      if ( status_center.IsEnabled() )
      {
         eafTypes::StatusSeverityType severity = status_center.GetSeverity();
         color = (severity == eafTypes::statusOK      ? STATUS_OK_COLOR :
                  severity == eafTypes::statusWarning ? STATUS_WARN_COLOR : STATUS_ERROR_COLOR);

         status_count = status_center.Count();

         CBrush brush(color);
         CPen pen(PS_SOLID,1,color);

         CBrush* pOldBrush = pDC->SelectObject(&brush);
         CPen* pOldPen = pDC->SelectObject(&pen);

         pDC->Rectangle( &(lpDrawItemStruct->rcItem) );

         CString strStatus;
         strStatus.Format(_T("%d"),status_count);
         int bkMode = pDC->SetBkMode(TRANSPARENT);
         pDC->DrawText(strStatus,&(lpDrawItemStruct->rcItem),DT_CENTER | DT_VCENTER);
         pDC->SetBkMode(bkMode);

         pDC->SelectObject(pOldBrush);
         pDC->SelectObject(pOldPen);
      }
   }
   else
   {
      COLORREF color = ::GetSysColor(COLOR_BTNFACE);
      CBrush brush(color);
      CPen pen(PS_SOLID,1,color);

      CBrush* pOldBrush = pDC->SelectObject(&brush);
      CPen* pOldPen = pDC->SelectObject(&pen);

      pDC->Rectangle( &(lpDrawItemStruct->rcItem) );

      pDC->SelectObject(pOldBrush);
      pDC->SelectObject(pOldPen);
   }
}

void CEAFStatusBar::OnLButtonDblClk(UINT nFlags, CPoint point)
{
   CRect rect;

   CEAFDocument* pDoc = GetDocument();
   if ( pDoc )
   {
      // Status Center
      CEAFStatusCenter& status_center = pDoc->GetStatusCenter();
      if ( status_center.IsEnabled() )
      {
         GetStatusBarCtrl().GetRect(GetStatusPaneIndex(),&rect);
         if (rect.PtInRect(point))
         {
            PostMessage(WM_COMMAND,ID_VIEW_STATUSCENTER,0);
         }
      }
   }

   CStatusBar::OnLButtonDblClk(nFlags,point);
}

void CEAFStatusBar::OnStatusChanged()
{
   // the status changed so invalidated the status pane and force a redraw
   CRect rect;
   GetStatusBarCtrl().GetRect(GetStatusPaneIndex(),&rect);
   InvalidateRect(rect);
   UpdateWindow();
}

void CEAFStatusBar::Reset()
{
   OnStatusChanged();
}

#ifdef _DEBUG
void CEAFStatusBar::AssertValid() const
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	CStatusBar::AssertValid();
}
#endif
