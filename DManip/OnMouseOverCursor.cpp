///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#include "stdafx.h"
#include "OnMouseOverCursor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

COnMouseOverCursor* COnMouseOverCursor::ms_pThis = nullptr;

COnMouseOverCursor::COnMouseOverCursor(HWND hwnd,HINSTANCE hInstance,LPCTSTR lpCursorName,UINT uElapse,CRgn* rgn)
{
   m_hwnd = hwnd;
   m_hOverCursor = ::LoadCursor(hInstance,lpCursorName);
   ASSERT(m_hOverCursor);

   // Create an empty region
   m_Rgn.CreateRectRgnIndirect(CRect(CPoint(0,0),CSize(1,1)));
   m_Rgn.CopyRgn(rgn); // Replaces the empty region with the passed parameter, however requires that
                       // m_Rgn has a valid region (hence the Create call above)

   m_uElapse = uElapse;
}

void COnMouseOverCursor::StartTracking(COnMouseOverCursor** ppParent)
{
   ATLTRACE("OnMouseOverCursor - StartTracking\n");
   m_ppParent = ppParent;
   SetOverCursor();
   StartTimer();
}

// The only way this things is going to get a mouse over event is if the cursor is over the
// display object... hence, there is no need to test this
//void COnMouseOverCursor::OnMouseMove(UINT nFlags,CPoint point)
//{
//   // A MouseMove event occured before the timer expired... is the mouse over the target region?
//   BOOL bInRegion = m_Rgn.PtInRegion(point);
//
//   if ( !bInRegion )
//   {
//      // If the mouse is no longer over the target region we're done
//      Done();
//   }
//}

void COnMouseOverCursor::Destroy()
{
   ATLTRACE("OnMouseOverCursor - Destroying self\n");
   (*m_ppParent) = nullptr;
   delete this;
}

void COnMouseOverCursor::StartTimer()
{
   ATLTRACE("OnMouseOverCursor - Starting timer\n");
   ms_pThis = this;
   m_TimerID = ::SetTimer(m_hwnd,1,m_uElapse,&COnMouseOverCursor::TimerProc);
   ASSERT( m_TimerID != 0);
}

void COnMouseOverCursor::StopTimer()
{
   ATLTRACE("OnMouseOverCursor - Stopping timer\n");
   BOOL bKilled = ::KillTimer(m_hwnd,m_TimerID);
   ASSERT(bKilled);
}

void COnMouseOverCursor::SetOverCursor()
{
   ATLTRACE("OnMouseOverCursor - Setting over cursor\n");
   m_hOriginalCursor = ::SetCursor(m_hOverCursor);
   ASSERT(m_hOriginalCursor);
}

void COnMouseOverCursor::ResetCursor()
{
   ATLTRACE("OnMouseOverCursor - Resetting cursor\n");
   ::SetCursor(m_hOriginalCursor);
}

VOID CALLBACK COnMouseOverCursor::TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime)
{
   // The timer went off...
   ATLTRACE("OnMouseOverCursor - Timer Event\n");

   // Is the cursor over the target region?
   BOOL bInRegion = FALSE;

   CPoint point;
   BOOL bSuccess = GetCursorPos(&point); // point is in screen coordinates
   if ( bSuccess )
   {
      // map point to client coordinates so that it is in the same coordinate system as the region
      if ( ::ScreenToClient(hwnd,&point) )
         bInRegion = COnMouseOverCursor::HitTest(point);
      else
         bInRegion = FALSE; // If the point couldn't be converted, assume cursor is not over target
   }
   else
   {
      // Unable to get the current cursor position... assume it is not over the target region
      bInRegion = FALSE;
   }

   // If the cursor is still over the target region, make sure the cursor is currect, otherwise we are done
   if ( bInRegion )
   {
      ATLTRACE("OnMouseOverCursor - Timer Event - Cursor is still in target region\n");
      COnMouseOverCursor::VerifyCursor();
   }
   else
   {
      ATLTRACE("OnMouseOverCursor - Timer Event - Cursor has left target region\n");
      COnMouseOverCursor::Done();
   }
}

BOOL COnMouseOverCursor::HitTest(CPoint point)
{
   return ms_pThis->m_Rgn.PtInRegion(point);
}

void COnMouseOverCursor::VerifyCursor()
{
   ATLTRACE("OnMouseOverCursor - Verifying cursor\n");
   if ( ms_pThis->m_hOverCursor != ::GetCursor() )
   {
      ATLTRACE("OnMouseOverCursor - Updating cursor\n");
      ms_pThis->SetOverCursor();
   }
}

void COnMouseOverCursor::Done()
{
   ATLTRACE("OnMouseOverCursor - Done Tracking\n");
   ms_pThis->StopTimer();
   ms_pThis->ResetCursor();
   ms_pThis->Destroy();
   ms_pThis = nullptr;
}