///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include "CenterOnPointFSM.h"
#include <DManip/Task.h>

class CDisplayView;

namespace WBFL
{
   namespace DManip
   {
      class CenterOnPointTask : 
         public CenterOnPointFSM,
         public iTask
      {
      public:
         CenterOnPointTask();
         CenterOnPointTask(CDisplayView* pView);
         virtual ~CenterOnPointTask();

         // CenterOnPointTask methods (from CenterOnPointFSM)
	      virtual void FSMError(LPCTSTR t,LPCTSTR s) override;
	      virtual void CenterOnPoint() override;
         virtual void Cancel() override;
	      virtual void InitTask() override;

         // iTask methods
         virtual void Start() override;
         virtual void OnLButtonDown(UINT nFlags, const CPoint& point) override;
	      virtual void OnLButtonUp(UINT nFlags,const CPoint& point) override;
         virtual void OnLButtonDblClk(UINT nFlags,const CPoint& point) override;
         virtual void OnRButtonDown(UINT nFlags, const CPoint& point) override;
	      virtual void OnRButtonUp(UINT nFlags,const CPoint& point) override;
         virtual void OnRButtonDblClk(UINT nFlags,const CPoint& point) override;
         virtual void OnMouseMove(UINT nFlags, const CPoint& point) override;
         virtual void OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point) override;
         virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override;
         virtual void OnContextMenu(CWnd* pWnd,const CPoint& point) override;
         virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
         virtual void OnDragLeave() override;
         virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
         virtual DROPEFFECT OnDragScroll(DWORD dwKeyState,CPoint point) override;
         virtual BOOL OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point) override;
         virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point) override;

      private:
         CDisplayView* m_pView;
         CPoint m_Point;
         HCURSOR m_OldCursor;
      };
   };
};
