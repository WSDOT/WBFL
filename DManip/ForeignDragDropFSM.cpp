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

#include "pch.h"
#include "ForeignDragDropFSM.h"
#include "DManipDebug.h"

using namespace WBFL::DManip;

// Definition of static state objects
ForeignDragDropFSMStartState               ForeignDragDropFSM::Start;
ForeignDragDropFSMWaitingForDropState      ForeignDragDropFSM::WaitingForDrop;
ForeignDragDropFSMDoneState                ForeignDragDropFSM::Done;
ForeignDragDropFSMWaitingForDragEnterState ForeignDragDropFSM::WaitingForDragEnter;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ForeignDragDropFSMState::ForeignDragDropFSMState()
{

}

ForeignDragDropFSMState::~ForeignDragDropFSMState()
{

}

void ForeignDragDropFSMState::Do(ForeignDragDropFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

DROPEFFECT ForeignDragDropFSMState::DragEnter(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DragEnter"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

void ForeignDragDropFSMState::DragLeave(ForeignDragDropFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("DragLeave"),fsm.GetState().StateName());
}

DROPEFFECT ForeignDragDropFSMState::DragOver(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DragOver"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

DROPEFFECT ForeignDragDropFSMState::DragScroll(ForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DragScroll"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

BOOL ForeignDragDropFSMState::Drop(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("Drop"),fsm.GetState().StateName());
   return FALSE;
}

DROPEFFECT ForeignDragDropFSMState::DropEx(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DropEx"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

// States and State Transitions
void ForeignDragDropFSMWaitingForDropState::DragLeave(ForeignDragDropFSM& fsm)
{
   // Action
   fsm.DestroyDragObjects();

   // Change State
   fsm.SetState(ForeignDragDropFSM::Done);
}

DROPEFFECT ForeignDragDropFSMWaitingForDropState::DragOver(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Action
   DROPEFFECT de = fsm.DetermineDropEffect();
   fsm.TrackDragObjects();

   // Change State
   fsm.SetState(ForeignDragDropFSM::WaitingForDrop);

   return de;
}

// States and State Transitions
DROPEFFECT ForeignDragDropFSMWaitingForDragEnterState::DragScroll(ForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

DROPEFFECT ForeignDragDropFSMWaitingForDragEnterState::DragEnter(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Action
   fsm.CreateDragObjects();

   // Change State
   fsm.SetState(ForeignDragDropFSM::WaitingForDrop);

   return DROPEFFECT_NONE;
}

DROPEFFECT ForeignDragDropFSMWaitingForDropState::DragScroll(ForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

BOOL ForeignDragDropFSMWaitingForDropState::Drop(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Action
   fsm.NotifyDropTarget();
   fsm.DestroyDragObjects();

   // Change State
   fsm.SetState(ForeignDragDropFSM::Done);

   return TRUE;
}

DROPEFFECT ForeignDragDropFSMWaitingForDropState::DropEx(ForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Action
   fsm.DestroyDragObjects();
   fsm.NotifyDropTarget();

   // Change State
   fsm.SetState(ForeignDragDropFSM::Done);

   return DROPEFFECT_NONE;
}

void ForeignDragDropFSMStartState::Do(ForeignDragDropFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(ForeignDragDropFSM::WaitingForDragEnter);
}

ForeignDragDropFSM::ForeignDragDropFSM():
m_pState(&Start)
{
}

void ForeignDragDropFSM::SetState(ForeignDragDropFSMState& state) 
{ 
   WATCHX(DManip,1,_T("Entering state ") << state.StateName());
   m_pState = &state; 
}
ForeignDragDropFSMState& ForeignDragDropFSM::GetState() const 
{ 
   return *m_pState; 
}

bool ForeignDragDropFSM::CompareStates(ForeignDragDropFSMState& state)
{ 
   return &state == m_pState; 
}
