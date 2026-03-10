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

#include "LocalDragDropTask.h"

namespace WBFL
{
   namespace DManip
   {
      class LocalDragDropFSM;

      //----------------------------------------------
      // LocalDragDropFSMState: The base state class
      //
      class LocalDragDropFSMState  
      {
      public:
	      LocalDragDropFSMState();
	      virtual ~LocalDragDropFSMState();

	      virtual LPCTSTR StateName() const = 0;
	      virtual void Do(LocalDragDropFSM& fsm);
	      virtual DROPEFFECT DragEnter(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
	      virtual void DragLeave(LocalDragDropFSM& fsm);
	      virtual DROPEFFECT DragOver(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
         virtual DROPEFFECT DragScroll(LocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point);
	      virtual BOOL Drop(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point);
         virtual DROPEFFECT DropEx(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point);
      };

      //----------------------------------------------
      // State: Start
      //
      class LocalDragDropFSMStartState : public LocalDragDropFSMState
      {
      public:
         virtual LPCTSTR StateName() const  override { return _T("Start"); }
         virtual void Do(LocalDragDropFSM& fsm) override;
      };

      //----------------------------------------------
      // State: Done
      //
      class LocalDragDropFSMDoneState : public LocalDragDropFSMState
      {
      public:
         virtual LPCTSTR StateName() const override { return _T("Done"); }
      };

      //----------------------------------------------
      // State: WaitingForDragEnter
      //
      class LocalDragDropFSMWaitingForDragEnterState : public LocalDragDropFSMState
      {
      public:
         virtual LPCTSTR StateName() const  override { return _T("WaitingForDragEnter"); }
         virtual DROPEFFECT DragScroll(LocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point) override;
	      virtual DROPEFFECT DragEnter(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
      };

      //----------------------------------------------
      // State: WaitingForDrop
      //
      class LocalDragDropFSMWaitingForDropState : public LocalDragDropFSMState
      {
      public:
         virtual LPCTSTR StateName() const  override { return _T("WaitingForDrop"); }
	      virtual void DragLeave(LocalDragDropFSM& fsm) override;
	      virtual DROPEFFECT DragOver(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
         virtual DROPEFFECT DragScroll(LocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point) override;
	      virtual BOOL Drop(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point) override;
         virtual DROPEFFECT DropEx(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point) override;
      };

      class LocalDragDropFSM : public iLocalDragDropTask
      {
      public:
         static LocalDragDropFSMStartState               Start;
         static LocalDragDropFSMWaitingForDragEnterState WaitingForDragEnter;
         static LocalDragDropFSMWaitingForDropState      WaitingForDrop;
         static LocalDragDropFSMDoneState                Done;

         LocalDragDropFSM();

         // Event Functions
         void Do() {m_pState->Do(*this);}

         DROPEFFECT DragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
         {return m_pState->DragEnter(*this,pDataObject,dwKeyState,point); }

         void DragLeave()
         {m_pState->DragLeave(*this); }

         DROPEFFECT DragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
         {return m_pState->DragOver(*this,pDataObject,dwKeyState,point); }
   
         DROPEFFECT DragScroll(DWORD dwKeyState,CPoint point)
         {return m_pState->DragScroll(*this,dwKeyState,point);}

         BOOL Drop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
         {return m_pState->Drop(*this,pDataObject,dropEffect,point); }

         DROPEFFECT DropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
         {return m_pState->DropEx(*this,pDataObject,dropEffect,dropList,point); }

         // State Accessor Functions
         void SetState(LocalDragDropFSMState& state);
         LocalDragDropFSMState& GetState() const;
         bool CompareStates(LocalDragDropFSMState& state);

      private:
         LocalDragDropFSMState* m_pState;
      };
   };
};
