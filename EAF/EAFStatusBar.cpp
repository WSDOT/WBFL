///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include <EAF\EAFStatusBar.h>
#include <EAF\EAFDocument.h>
#include <EAF\StatusCenter.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// AFX_STATUSPANE, SBPF_UPDATE, and StatusBar::_GetPanePtr
// are copy/paste from barstat.cpp (an MFC file) to support
// our copy/paste and tweak implementation of SetIndicators.
// See notes in SetIndicators that explain why we have to 
// deviate from the MFC implementation.
struct AFX_STATUSPANE
{
	UINT    nID;        // IDC of indicator: 0 => normal text area
	int     cxText;     // width of string area in pixels
						//   on both sides there is a 3 pixel gap and
						//   a one pixel border, making a pane 6 pixels wider
	UINT    nStyle;     // style flags (SBPS_*)
	UINT    nFlags;     // state flags (SBPF_*)
	CString strText;    // text in the pane
};

#define SBPF_UPDATE 0x0001  // pending update of text

inline AFX_STATUSPANE* CStatusBar::_GetPanePtr(int nIndex) const
{
	ASSERT((nIndex >= 0 && nIndex < m_nCount) || m_nCount == 0);
	return ((AFX_STATUSPANE*)m_pData) + nIndex;
}


// CEAFStatusBar

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
   //EAFID_INDICATOR_AUTOSAVE_ON,
   EAFID_INDICATOR_MODIFIED,
   EAFID_INDICATOR_STATUS,
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
   m_AutoSavePaneIdx = -1;
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

BOOL CEAFStatusBar::SetStatusIndicators(const UINT* lpIDArray, int nIDCount)
{
   // DON'T CALL BASE CLASS VERSION, it doesn't work for us.
   // We have to tweak the module state when loading the string resources
   // See below.
   // NOTE: This method is a copy/paste from barstat.cpp, CStatusBar::SetIndicators
   // the only change is the test for the EAF_INDICATOR_MIN/MAX range along with the
   // module state tweak.

   //return SetIndicators(lpIDArray,nIDCount);

	ASSERT_VALID(this);
	ASSERT(nIDCount >= 1);  // must be at least one of them
	ASSERT(lpIDArray == nullptr ||
		AfxIsValidAddress(lpIDArray, sizeof(UINT) * nIDCount, FALSE));
	ASSERT(::IsWindow(m_hWnd));

	// first allocate array for panes and copy initial data
	if (!AllocElements(nIDCount, sizeof(AFX_STATUSPANE)))
		return FALSE;
	ASSERT(nIDCount == m_nCount);

	// copy initial data from indicator array
	BOOL bResult = TRUE;
	if (lpIDArray != nullptr)
	{
		HFONT hFont = (HFONT)SendMessage(WM_GETFONT);
		CClientDC dcScreen(nullptr);
		HGDIOBJ hOldFont = nullptr;
		if (hFont != nullptr)
			hOldFont = dcScreen.SelectObject(hFont);

		AFX_STATUSPANE* pSBP = _GetPanePtr(0);
		for (int i = 0; i < nIDCount; i++)
		{
			pSBP->nID = *lpIDArray++;
			pSBP->nFlags |= SBPF_UPDATE;
			if (pSBP->nID != 0)
			{
            if ( EAFID_INDICATOR_MIN <= pSBP->nID && pSBP->nID <= EAFID_INDICATOR_MAX )
            {
               // if the ID is one of ours (EAF), set the module state to our state
               // and load the string....
               AFX_MANAGE_STATE(AfxGetAppModuleState());
				   if (!pSBP->strText.LoadString(pSBP->nID))
				   {
					   TRACE(traceAppMsg, 0, "Warning: failed to load indicator string 0x%04X.\n",
						   pSBP->nID);
					   bResult = FALSE;
					   break;
				   }
            }
            else
            {
               // .... otherwise, load the string using the current state
				   if (!pSBP->strText.LoadString(pSBP->nID))
				   {
					   TRACE(traceAppMsg, 0, "Warning: failed to load indicator string 0x%04X.\n",
						   pSBP->nID);
					   bResult = FALSE;
					   break;
				   }
            }

				pSBP->cxText = dcScreen.GetTextExtent(pSBP->strText).cx;
				ASSERT(pSBP->cxText >= 0);
				if (!SetPaneText(i, pSBP->strText, FALSE))
				{
					bResult = FALSE;
					break;
				}
			}
			else
			{
				// no indicator (must access via index)
				// default to 1/4 the screen width (first pane is stretchy)
				pSBP->cxText = ::GetSystemMetrics(SM_CXSCREEN)/4;
				if (i == 0)
					pSBP->nStyle |= (SBPS_STRETCH | SBPS_NOBORDERS);
			}
			++pSBP;
		}
		if (hOldFont != nullptr)
			dcScreen.SelectObject(hOldFont);
	}
	UpdateAllPanes(TRUE, TRUE);

	return bResult;

}

BOOL CEAFStatusBar::Create(CWnd* pParentWnd, DWORD dwStyle , UINT nID)
{
   // MFC is expecting the status bar window to be created in the app module state
   // so force it here. Below, SetStatusIndicators is called instead of 
   // CStatusBar::SetIndicators so that app plugins can set the module
   // state to their module state so status indicator text strings can
   // be read from their string tables.
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   BOOL bResult = CStatusBar::Create(pParentWnd, dwStyle, nID);
   if ( !bResult )
   {
      return bResult;
   }

   const UINT* pIndicators;
   GetStatusIndicators(&pIndicators,&m_nIndicators);
   bResult = SetStatusIndicators(pIndicators,m_nIndicators);

   int idx = GetStatusPaneIndex();
   if ( 0 <= idx )
   {
      SetPaneStyle( idx, SBPS_NORMAL | SBT_OWNERDRAW );
   }

   idx = GetModifiedPaneIndex();
   if ( 0 <= idx )
   {
      SetPaneStyle( idx, SBPS_DISABLED );
   }

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
   {
      SetPaneStyle(idx, style );
   }
}

int CEAFStatusBar::GetPaneCount()
{
   return m_nIndicators;
}

int CEAFStatusBar::GetPaneIndex(UINT nIDPane)
{
   int index = -1;
   for (int i = 0; i < GetPaneCount(); i++)
   {
      UINT nID;
      UINT nStyle;
      int cxWidth;
      GetPaneInfo(i, nID, nStyle, cxWidth);

      if (nID == nIDPane)
      {
         index = i;
         break;
      }
   }

   return index;
}

int CEAFStatusBar::GetModifiedPaneIndex()
{
   if ( m_ModifiedPaneIdx < 0 )
   {
      m_ModifiedPaneIdx = GetPaneIndex(EAFID_INDICATOR_MODIFIED);
   }
   return m_ModifiedPaneIdx;
}

int CEAFStatusBar::GetStatusPaneIndex()
{
   if ( m_StatusPaneIdx < 0 )
   {
      m_StatusPaneIdx = GetPaneIndex(EAFID_INDICATOR_STATUS);
   }
   return m_StatusPaneIdx;
}

int CEAFStatusBar::GetAutoSavePaneIndex()
{
   if (m_AutoSavePaneIdx < 0)
   {
      m_AutoSavePaneIdx = GetPaneIndex(EAFID_INDICATOR_AUTOSAVE_ON);
   }

   return m_AutoSavePaneIdx;
}

CEAFDocument* CEAFStatusBar::GetDocument()
{
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   if ( pFrame->IsKindOf(RUNTIME_CLASS(CFrameWnd)) )
   {
      CMDIChildWnd* pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
      CView* pView = pChild->GetActiveView();
      CDocument* pDoc = nullptr;
      if ( pView )
      {
         pDoc = pView->GetDocument();
      }

      if ( pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CEAFDocument)) )
      {
         CEAFDocument* pEAFDoc = (CEAFDocument*)pDoc;
         return pEAFDoc;
      }
   }

   return nullptr;
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
         color = (severity == eafTypes::statusInformation ? STATUS_INFORMATION_COLOR :
                  severity == eafTypes::statusWarning ? STATUS_WARNING_COLOR : STATUS_ERROR_COLOR);

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
            PostMessage(WM_COMMAND,EAFID_VIEW_STATUSCENTER,0);
         }
      }
   }

   GetStatusBarCtrl().GetRect(GetAutoSavePaneIndex(), &rect);
   if (rect.PtInRect(point))
   {
      CEAFApp* pApp = EAFGetApp();
      if (pApp)
      {
         pApp->EnableAutoSave(!pApp->IsAutoSaveEnabled(), pApp->GetAutoSaveInterval());
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

void CEAFStatusBar::AutoSaveEnabled(BOOL bEnable)
{
   CString status_text;
   VERIFY(status_text.LoadString(bEnable ? EAFID_INDICATOR_AUTOSAVE_ON : EAFID_INDICATOR_AUTOSAVE_OFF));

   int idx = GetAutoSavePaneIndex();
   if (0 <= idx)
   {
      SetPaneText(idx, status_text, TRUE);
   }
}
