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

#include "ForeignDragDropTask.h"

namespace WBFL
{
   namespace DManip
   {
      class ForeignDragDropFSM;

      //----------------------------------------------
      // ForeignDragDropFSMState: The base state class
      //
      class ForeignDragDropFSMState  
      {
      public:
	      ForeignDragDropFSMState();
	      virtual ~ForeignDragDropFSMState();

	      virtual LPCTSTR StateName() const = 0;
	      virtual void Do(ForeignDragDropFSM& fsm);
	      virtual DROPEFFECT DragEnter(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
	      virtual void DragLeave(ForeignDragDropFSM& fsm);
	      virtual DROPEFFECT DragOver(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
         virtual DROPEFFECT DragScroll(ForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point);
	      virtual BOOL Drop(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point);
         virtual DROPEFFECT DropEx(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point);
      };

      //----------------------------------------------
      // State: Start
      //
      class ForeignDragDropFSMStartState : public ForeignDragDropFSMState
      {
      public:
         virtual LPCTSTR StateName() const  override { return _T("Start"); }
         virtual void Do(ForeignDragDropFSM& fsm) override;
      };

      //----------------------------------------------
      // State: Done
      //
      class ForeignDragDropFSMDoneState : public ForeignDragDropFSMState
      {
      public:
         virtual LPCTSTR StateName() const override { return _T("Done"); }
      };

      //----------------------------------------------
      // State: WaitingForDragEnter
      //
      class ForeignDragDropFSMWaitingForDragEnterState : public ForeignDragDropFSMState
      {
      public:
         virtual LPCTSTR StateName() const  override { return _T("WaitingForDragEnter"); }
         virtual DROPEFFECT DragScroll(ForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point) override;
	      virtual DROPEFFECT DragEnter(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
      };

      //----------------------------------------------
      // State: WaitingForDrop
      //
      class ForeignDragDropFSMWaitingForDropState : public ForeignDragDropFSMState
      {
      public:
         virtual LPCTSTR StateName() const override { return _T("WaitingForDrop"); }
	      virtual void DragLeave(ForeignDragDropFSM& fsm) override;
	      virtual DROPEFFECT DragOver(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
         virtual DROPEFFECT DragScroll(ForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point) override;
	      virtual BOOL Drop(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point) override;
         virtual DROPEFFECT DropEx(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point) override;
      };

      class ForeignDragDropFSM : public iForeignDragDropTask
      {
      public:
         static ForeignDragDropFSMStartState               Start;
         static ForeignDragDropFSMWaitingForDragEnterState WaitingForDragEnter;
         static ForeignDragDropFSMWaitingForDropState      WaitingForDrop;
         static ForeignDragDropFSMDoneState                Done;

         ForeignDragDropFSM();

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
         void SetState(ForeignDragDropFSMState& state);
         ForeignDragDropFSMState& GetState() const;
         bool CompareStates(ForeignDragDropFSMState& state);

      private:
         ForeignDragDropFSMState* m_pState;
      };
   };
};
