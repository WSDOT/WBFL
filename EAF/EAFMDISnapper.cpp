///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

// EAFMDISnapper.cpp: implementation of the CEAFMDISnapper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFMDISnapper.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)	((int)(short)LOWORD(lParam))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)	((int)(short)HIWORD(lParam))
#endif

CEAFMDISnapper::CEAFMDISnapper(DWORD snapWidth)
{
   m_bSizeMoveIsSysCommand = false;
	SetSnapWidth(snapWidth);
}

CEAFMDISnapper::~CEAFMDISnapper()
{
}


// ==================================================================
//  CEAFMDISnapper::AllowSnap
// ------------------------------------------------------------------
///
/// decides whether snapping is enabled.
/// 
/// Default Implementation
///     The default implementation returns false when either Shift is pressed, 
///     or m_bSizeMoveIsSysCommand is true. m_bSizeMoveIsSysCommand indicates
///     that the current sizing / moving command was initiated through the menu.
/// 
/// Override
///     A derived class can override this function to modify the conditions that disable
///     snapping. 
/// 
bool CEAFMDISnapper::AllowSnap()
{
    if (m_bSizeMoveIsSysCommand)
        return false;

    bool shiftPressed = GetAsyncKeyState(VK_SHIFT) < 0; 
    return !shiftPressed;
}



// ========================================================
//	Init/Set/Get
// --------------------------------------------------------

void CEAFMDISnapper::SetSnapWidth(DWORD snapWidth)
{
	m_snapWidth = snapWidth;
}


// ================================================================
//	OnMessage
// ----------------------------------------------------------------

LRESULT CEAFMDISnapper::OnMessage(CEAFChildFrame * wnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_MOVING			:	if (AllowSnap()) OnMoving(wnd, wp, (LPRECT) lp); break;
		case WM_ENTERSIZEMOVE	:	if (AllowSnap()) OnEnterSizeMove(wnd);  break;
		case WM_EXITSIZEMOVE	:	OnExitSizeMove();   break;

        case WM_SYSCOMMAND      :   
            if (wp == SC_MOVE || wp == SC_SIZE)
                m_bSizeMoveIsSysCommand = true;
            break;

	};

	return 0;
}

// ================================================================
//	OnEnterSizeMove
// ----------------------------------------------------------------

void CEAFMDISnapper::OnMoving(CEAFChildFrame * wnd, WPARAM edge, LPRECT newrect)
{
   if ( wnd == m_wndMoving && m_wndMoving->IsSnapped() )
   {
      m_wndMoving->Unsnap();
      m_wndMoving->GetWindowRect(newrect);
   }
}

void CEAFMDISnapper::OnEnterSizeMove(CEAFChildFrame * wnd)
{
	m_wndMoving = wnd;
}



// ================================================================
//	OnExitSizeMove
// ----------------------------------------------------------------

void CEAFMDISnapper::OnExitSizeMove()
{
   if ( m_wndMoving && AllowSnap() )
   {
      DWORD dw = GetMessagePos();
      POINT mouse = { GET_X_LPARAM(dw), GET_Y_LPARAM(dw)   };

      CWnd* pParent = m_wndMoving->GetParent();
      pParent->ScreenToClient(&mouse);

      CRect rWnd;
      pParent->GetClientRect(&rWnd);

      if ( mouse.x <= m_snapWidth )
      {
         rWnd.right = rWnd.left + rWnd.Width()/2;
         m_wndMoving->SnapToRect(&rWnd);
      }
      else if ( rWnd.right - m_snapWidth <= mouse.x )
      {
         rWnd.left = rWnd.Width()/2;
         m_wndMoving->SnapToRect(&rWnd);
      }
      else if ( mouse.y <= m_snapWidth )
      {
         m_wndMoving->ShowWindow(SW_SHOWMAXIMIZED);
      }
   }

   m_bSizeMoveIsSysCommand = false;
	m_wndMoving = nullptr;
}
