///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#pragma once

namespace WBFL
{
   namespace DManip
   {
      /// @brief An interface defining a task, based on the Task Master architecture
      class iTask
      {
      public:
         /// @brief Called by the framework when the task is started
         virtual void Start() = 0;

         virtual void OnLButtonDown(UINT nFlags, const CPoint& point) = 0;
	      virtual void OnLButtonUp(UINT nFlags,const CPoint& point) = 0;
         virtual void OnLButtonDblClk(UINT nFlags,const CPoint& point) = 0;

         virtual void OnRButtonDown(UINT nFlags, const CPoint& point) = 0;
	      virtual void OnRButtonUp(UINT nFlags,const CPoint& point) = 0;
         virtual void OnRButtonDblClk(UINT nFlags,const CPoint& point) = 0;

         virtual void OnMouseMove(UINT nFlags, const CPoint& point) = 0;
         virtual void OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point) = 0;

         virtual void OnContextMenu(CWnd* pWnd, const CPoint& point) = 0;

         virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)  = 0;

         virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) = 0;
         virtual void OnDragLeave() = 0;
         virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) = 0;
         virtual DROPEFFECT OnDragScroll(DWORD dwKeyState,CPoint point) = 0;
         virtual BOOL OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point) = 0;
         virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point) = 0;
      };
   };
};
