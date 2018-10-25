///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#ifndef INCLUDED_ONMOUSEOVERCURSOR_H_
#define INCLUDED_ONMOUSEOVERCURSOR_H_
#pragma once

class COnMouseOverCursor
{
public:
   COnMouseOverCursor(HWND hwnd,HINSTANCE hInstance,LPCTSTR lpCursorName,UINT uElapse,CRgn* rgn);
   
   // Sets the address of the point the owner has to this object...
   // When the timer goes off, this passed pointer is set to nullptr indicating that
   // this object has been deleted
   void StartTracking(COnMouseOverCursor* *parent);

   // Not needed
   //void OnMouseMove(UINT nFlags,CPoint point);

private:
   HCURSOR m_hOriginalCursor;
   HCURSOR m_hOverCursor;
   UINT_PTR m_TimerID;
   UINT m_uElapse;
   CRgn m_Rgn;
   HWND m_hwnd;
   COnMouseOverCursor** m_ppParent;
   static COnMouseOverCursor* ms_pThis;

   void Destroy();
   void StartTimer();
   void StopTimer();
   void SetOverCursor();
   void ResetCursor();

   static VOID CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);
   static BOOL HitTest(CPoint point);
   static void VerifyCursor();
   static void Done();
};

#endif // INCLUDED_ONMOUSEOVERCURSOR_H_