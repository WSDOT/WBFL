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

#include "stdafx.h"
#include "MFCToolBar.h"
#include "afximpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define STRING_REFRESH_OFFSET 1000000

/*
struct AFX_DLLVERSIONINFO
{
		DWORD cbSize;
		DWORD dwMajorVersion;                   // Major version
		DWORD dwMinorVersion;                   // Minor version
		DWORD dwBuildNumber;                    // Build number
		DWORD dwPlatformID;                     // DLLVER_PLATFORM_*
};

typedef HRESULT (CALLBACK* AFX_DLLGETVERSIONPROC)(AFX_DLLVERSIONINFO *);

int _afxComCtlVersion = -1;

DWORD AFXAPI _AfxGetComCtlVersion()
{
	// return cached version if already determined...
	if (_afxComCtlVersion != -1)
		return _afxComCtlVersion;

	// otherwise determine comctl32.dll version via DllGetVersion
	HINSTANCE hInst = afxComCtlWrapper->GetModuleHandle();
	ASSERT(hInst != nullptr);
	AFX_DLLGETVERSIONPROC pfn;
	pfn = (AFX_DLLGETVERSIONPROC)GetProcAddress(hInst, "DllGetVersion");
	DWORD dwVersion = VERSION_WIN4;
	if (pfn != nullptr)
	{
		AFX_DLLVERSIONINFO dvi;
		memset(&dvi, 0, sizeof(dvi));
		dvi.cbSize = sizeof(dvi);
		HRESULT hr = (*pfn)(&dvi);
		if (SUCCEEDED(hr))
		{
			ASSERT(dvi.dwMajorVersion <= 0xFFFF);
			ASSERT(dvi.dwMinorVersion <= 0xFFFF);
			dwVersion = MAKELONG(dvi.dwMinorVersion, dvi.dwMajorVersion);
		}
	}
	_afxComCtlVersion = dwVersion;
	return dwVersion;
}
*/
int _afxDropDownWidth = -1;

int AFXAPI _AfxGetDropDownWidth()
{
	// return cached version if already determined...
	if (_afxDropDownWidth != -1)
		return _afxDropDownWidth;

	// otherwise calculate it...
	HDC hDC = GetDC(nullptr);
	ASSERT(hDC != nullptr);
	HFONT hFont = nullptr, hFontOld = nullptr;
	if ((hFont = CreateFont(GetSystemMetrics(SM_CYMENUCHECK), 0, 0, 0, 
		FW_NORMAL, 0, 0, 0, SYMBOL_CHARSET, 0, 0, 0, 0, _T("Marlett"))) != nullptr)
		hFontOld = (HFONT)SelectObject(hDC, hFont);
	VERIFY(GetCharWidth(hDC, '6', '6', &_afxDropDownWidth));
	if (hFont != nullptr)
	{
		SelectObject(hDC, hFontOld);
		DeleteObject(hFont);
	}
	ReleaseDC(nullptr, hDC);
	ASSERT(_afxDropDownWidth != -1);
	return _afxDropDownWidth;
}

CMyToolBar::CMyToolBar() :
CToolBar()
{
}

void CMyToolBar::_GetButton(int nIndex, TBBUTTON* pButton) const
{
	CMyToolBar* pBar = (CMyToolBar*)this;
	VERIFY(pBar->DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)pButton));
	// TBSTATE_ENABLED == TBBS_DISABLED so invert it
	pButton->fsState ^= TBSTATE_ENABLED;
}

void CMyToolBar::_SetButton(int nIndex, TBBUTTON* pButton)
{
	// get original button state
	TBBUTTON button;
	VERIFY(DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)&button));

	// prepare for old/new button comparsion
	button.bReserved[0] = 0;
	button.bReserved[1] = 0;
	// TBSTATE_ENABLED == TBBS_DISABLED so invert it
	pButton->fsState ^= TBSTATE_ENABLED;
	pButton->bReserved[0] = 0;
	pButton->bReserved[1] = 0;

	// nothing to do if they are the same
	if (memcmp(pButton, &button, sizeof(TBBUTTON)) != 0)
	{
		// don't redraw everything while setting the button
		DWORD dwStyle = GetStyle();
		ModifyStyle(WS_VISIBLE, 0);
		VERIFY(DefWindowProc(TB_DELETEBUTTON, nIndex, 0));

		// Force a recalc of the toolbar's layout to work around a comctl bug
		if (pButton->iString<-1){	
			int iTextRows;
			iTextRows = (int)::SendMessage(m_hWnd, TB_GETTEXTROWS, 0, 0);
			::SendMessage(m_hWnd, WM_SETREDRAW, FALSE, 0);
			::SendMessage(m_hWnd, TB_SETMAXTEXTROWS, iTextRows+1, 0);
			::SendMessage(m_hWnd, TB_SETMAXTEXTROWS, iTextRows, 0);
			::SendMessage(m_hWnd, WM_SETREDRAW, TRUE, 0);
			pButton->iString+=STRING_REFRESH_OFFSET;
 		}
		VERIFY(DefWindowProc(TB_INSERTBUTTON, nIndex, (LPARAM)pButton));
		ModifyStyle(0, dwStyle & WS_VISIBLE);

		// invalidate appropriate parts
		if (((pButton->fsStyle ^ button.fsStyle) & TBSTYLE_SEP) ||
			((pButton->fsStyle & TBSTYLE_SEP) && pButton->iBitmap != button.iBitmap))
		{
			// changing a separator
			Invalidate();
		}
		else
		{
			// invalidate just the button
			CRect rect;
			if (DefWindowProc(TB_GETITEMRECT, nIndex, (LPARAM)&rect))
				InvalidateRect(rect);
		}
	}
}

void CMyToolBar::SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert)
{
	ASSERT(pData != nullptr && nCount > 0);

	if (!bVert)
	{
		int nMin, nMax, nTarget, nCurrent, nMid;

		// Wrap ToolBar as specified
		nMax = nLength;
		nTarget = WrapToolBar(pData, nCount, nMax);

		// Wrap ToolBar vertically
		nMin = 0;
		nCurrent = WrapToolBar(pData, nCount, nMin);

		if (nCurrent != nTarget)
		{
			while (nMin < nMax)
			{
				nMid = (nMin + nMax) / 2;
				nCurrent = WrapToolBar(pData, nCount, nMid);

				if (nCurrent == nTarget)
					nMax = nMid;
				else
				{
					if (nMin == nMid)
					{
						WrapToolBar(pData, nCount, nMax);
						break;
					}
					nMin = nMid;
				}
			}
		}
		CSize size = CalcSize(pData, nCount);
		WrapToolBar(pData, nCount, size.cx);
	}
	else
	{
		CSize sizeMax, sizeMin, sizeMid;

		// Wrap ToolBar vertically
		WrapToolBar(pData, nCount, 0);
		sizeMin = CalcSize(pData, nCount);

		// Wrap ToolBar horizontally
		WrapToolBar(pData, nCount, 32767);
		sizeMax = CalcSize(pData, nCount);

		while (sizeMin.cx < sizeMax.cx)
		{
			sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;
			WrapToolBar(pData, nCount, sizeMid.cx);
			sizeMid = CalcSize(pData, nCount);

			if (nLength < sizeMid.cy)
			{
				if (sizeMin == sizeMid)
				{
					WrapToolBar(pData, nCount, sizeMax.cx);
					return;
				}
				sizeMin = sizeMid;
			}
			else if (nLength > sizeMid.cy && sizeMax != sizeMid)
      		sizeMax = sizeMid;
			else
				return;
		}
	}
}

struct _AFX_CONTROLPOS
{
	int nIndex, nID;
	CRect rectOldPos;
};

CSize CMyToolBar::CalcLayout(DWORD dwMode, int nLength)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));
	if (dwMode & LM_HORZDOCK)
		ASSERT(dwMode & LM_HORZ);

	int nCount;
   std::unique_ptr<TBBUTTON[]> pData;
   CSize sizeResult(0,0);

	//BLOCK: Load Buttons
	{
	  //IA64: Assume max button count < 2G
		nCount = int(DefWindowProc(TB_BUTTONCOUNT, 0, 0));
		if (nCount != 0)
		{
			int i;
			pData = std::make_unique<TBBUTTON[]>(nCount);
			for (i = 0; i < nCount; i++)
				_GetButton(i, &pData[i]);
		}
	}

	if (0 < nCount)
	{
		if (!(m_dwStyle & CBRS_SIZE_FIXED))
		{
			BOOL bDynamic = m_dwStyle & CBRS_SIZE_DYNAMIC;

         if (bDynamic && (dwMode & LM_MRUWIDTH))
         {
            SizeToolBar(pData.get(), nCount, m_nMRUWidth);
         }
         else if (bDynamic && (dwMode & LM_HORZDOCK))
         {
            SizeToolBar(pData.get(), nCount, 32767);
         }
         else if (bDynamic && (dwMode & LM_VERTDOCK))
         {
            SizeToolBar(pData.get(), nCount, 0);
         }
			else if (bDynamic && (nLength != -1))
			{
				CRect rect; rect.SetRectEmpty();
				CalcInsideRect(rect, (dwMode & LM_HORZ));
				BOOL bVert = (dwMode & LM_LENGTHY);
				int nLen = nLength + (bVert ? rect.Height() : rect.Width());

				SizeToolBar(pData.get(), nCount, nLen, bVert);
			}
         else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
         {
            SizeToolBar(pData.get(), nCount, m_nMRUWidth);
         }
         else
         {
            SizeToolBar(pData.get(), nCount, (dwMode & LM_HORZ) ? 32767 : 0);
         }
		}

		sizeResult = CalcSize(pData.get(), nCount);

		if (dwMode & LM_COMMIT)
		{
			std::unique_ptr<_AFX_CONTROLPOS[]> pControl;
			int nControlCount = 0;
			BOOL bIsDelayed = m_bDelayedButtonLayout;
			m_bDelayedButtonLayout = FALSE;

         for (int i = 0; i < nCount; i++)
         {
            if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
            {
               nControlCount++;
            }
         }

			if (0 < nControlCount)
			{
				pControl = std::make_unique<_AFX_CONTROLPOS[]>(nControlCount);
				int nControlAlloc = nControlCount;
				nControlCount = 0;

				for(int i = 0; i < nCount && nControlCount < nControlAlloc; i++)
				{
					if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
					{
						pControl[nControlCount].nIndex = i;
						pControl[nControlCount].nID = pData[i].idCommand;

						CRect rect;
						GetItemRect(i, &rect);
						ClientToScreen(&rect);
						pControl[nControlCount].rectOldPos = rect;

						nControlCount++;
					}
				}
			}

         if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
         {
            m_nMRUWidth = sizeResult.cx;
         }

         for (int i = 0; i < nCount; i++)
         {
            _SetButton(i, &pData[i]);
         }

			if (0 < nControlCount)
			{
				for (int i = 0; i < nControlCount; i++)
				{
					CWnd* pWnd = GetDlgItem(pControl[i].nID);
					if (pWnd != nullptr)
					{
						CRect rect;
						pWnd->GetWindowRect(&rect);
						CPoint pt = rect.TopLeft() - pControl[i].rectOldPos.TopLeft();
						GetItemRect(pControl[i].nIndex, &rect);
						pt = rect.TopLeft() + pt;
						pWnd->SetWindowPos(nullptr, pt.x, pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
					}
				}
			}
			m_bDelayedButtonLayout = bIsDelayed;
		}
	}

	//BLOCK: Adjust Margins
	{
		CRect rect; rect.SetRectEmpty();
		CalcInsideRect(rect, (dwMode & LM_HORZ));
		sizeResult.cy -= rect.Height();
		sizeResult.cx -= rect.Width();

		CSize size = CControlBar::CalcFixedLayout((dwMode & LM_STRETCH), (dwMode & LM_HORZ));
		sizeResult.cx = max(sizeResult.cx, size.cx);
		sizeResult.cy = max(sizeResult.cy, size.cy);
	}
	return sizeResult;
}

CSize CMyToolBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	DWORD dwMode = bStretch ? LM_STRETCH : 0;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout(dwMode);
}

CSize CMyToolBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
		((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
	{
		return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
	}
	return CalcLayout(dwMode, nLength);
}

#define CX_OVERLAP  0

CSize CMyToolBar::CalcSize(TBBUTTON* pData, int nCount)
{
	ASSERT(pData != nullptr && nCount > 0);

	CPoint cur(0,0);
	CSize sizeResult(0,0);

   //IA64: Assume retval of TB_GETEXTENDEDSTYLE is still 32-bit
	DWORD dwExtendedStyle = DWORD(DefWindowProc(TB_GETEXTENDEDSTYLE, 0, 0));

	for (int i = 0; i < nCount; i++)
	{
		//  The IE4 version of COMCTL32.DLL calculates the separation
		//	on a TBSTYLE_WRAP button as 100% of the value in iBitmap compared
		//	to the other versions which calculate it at 2/3 of that value.
		//	This is actually a bug which should be fixed in IE 4.01, so we
		//	only do the 100% calculation specifically for IE4.
		int cySep = pData[i].iBitmap;
		//ASSERT(_AfxGetComCtlVersion() != -1);
		//if (!(GetStyle() & TBSTYLE_FLAT) && _AfxGetComCtlVersion() != VERSION_IE4)
		//	cySep = cySep * 2 / 3;

		if (pData[i].fsState & TBSTATE_HIDDEN)
			continue;

		int cx = m_sizeButton.cx;
		if (pData[i].fsStyle & TBSTYLE_SEP)
		{
			// a separator represents either a height or width
			if (pData[i].fsState & TBSTATE_WRAP)
				sizeResult.cy = max(cur.y + m_sizeButton.cy + cySep, sizeResult.cy);
			else
				sizeResult.cx = max(cur.x + pData[i].iBitmap, sizeResult.cx);
		}
		else 
		{
			// check for dropdown style, but only if the buttons are being drawn
			if (((pData[i].fsStyle & TBSTYLE_DROPDOWN) || (pData[i].fsStyle & BTNS_WHOLEDROPDOWN))&& 
				(dwExtendedStyle & TBSTYLE_EX_DRAWDDARROWS))
			{
				// add size of drop down
				ASSERT(_AfxGetDropDownWidth() != -1);
				cx += _AfxGetDropDownWidth();
			}
			sizeResult.cx = max(cur.x + cx, sizeResult.cx);
			sizeResult.cy = max(cur.y + m_sizeButton.cy, sizeResult.cy);
		}

		if (pData[i].fsStyle & TBSTYLE_SEP)
			cur.x += pData[i].iBitmap;
		else
			cur.x += cx - CX_OVERLAP;

		if (pData[i].fsState & TBSTATE_WRAP)
		{
			cur.x = 0;
			cur.y += m_sizeButton.cy;
			if (pData[i].fsStyle & TBSTYLE_SEP)
				cur.y += cySep;
		}
	}
	return sizeResult;
}
