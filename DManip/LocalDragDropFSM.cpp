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

#include "pch.h"
#include "LocalDragDropFSM.h"
#include "DManipDebug.h"

using namespace WBFL::DManip;

// Definition of static state objects
LocalDragDropFSMStartState               LocalDragDropFSM::Start;
LocalDragDropFSMWaitingForDragEnterState LocalDragDropFSM::WaitingForDragEnter;
LocalDragDropFSMWaitingForDropState      LocalDragDropFSM::WaitingForDrop;
LocalDragDropFSMDoneState                LocalDragDropFSM::Done;

LocalDragDropFSMState::LocalDragDropFSMState()
{

}

LocalDragDropFSMState::~LocalDragDropFSMState()
{

}

void LocalDragDropFSMState::Do(LocalDragDropFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

DROPEFFECT LocalDragDropFSMState::DragEnter(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DragEnter"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

void LocalDragDropFSMState::DragLeave(LocalDragDropFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("DragLeave"),fsm.GetState().StateName());
}

DROPEFFECT LocalDragDropFSMState::DragOver(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DragOver"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

DROPEFFECT LocalDragDropFSMState::DragScroll(LocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DragScroll"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

BOOL LocalDragDropFSMState::Drop(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("Drop"),fsm.GetState().StateName());
   return FALSE;
}

DROPEFFECT LocalDragDropFSMState::DropEx(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DropEx"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

// States and State Transitions
DROPEFFECT LocalDragDropFSMWaitingForDragEnterState::DragScroll(LocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

DROPEFFECT LocalDragDropFSMWaitingForDragEnterState::DragEnter(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Action
   fsm.CreateDragObjects();

   // Change State
   fsm.SetState(LocalDragDropFSM::WaitingForDrop);

   return DROPEFFECT_NONE;
}

void LocalDragDropFSMWaitingForDropState::DragLeave(LocalDragDropFSM& fsm)
{
   // Action
   fsm.DestroyDragObjects();

   // Change State
   fsm.SetState(LocalDragDropFSM::WaitingForDragEnter);
}

DROPEFFECT LocalDragDropFSMWaitingForDropState::DragOver(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Action
   DROPEFFECT de = fsm.DetermineDropEffect();
   fsm.TrackDragObjects();

   // Change State
   fsm.SetState(LocalDragDropFSM::WaitingForDrop);

   return de;
}

DROPEFFECT LocalDragDropFSMWaitingForDropState::DragScroll(LocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

BOOL LocalDragDropFSMWaitingForDropState::Drop(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Action
   fsm.NotifyDropTarget();
   fsm.DestroyDragObjects();

   // Change State
   fsm.SetState(LocalDragDropFSM::Done);

   return TRUE;
}

DROPEFFECT LocalDragDropFSMWaitingForDropState::DropEx(LocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Action
   fsm.DestroyDragObjects();
   fsm.NotifyDropTarget();

   // Change State
   fsm.SetState(LocalDragDropFSM::Done);

   return DROPEFFECT_NONE;
}

void LocalDragDropFSMStartState::Do(LocalDragDropFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(LocalDragDropFSM::WaitingForDragEnter);
}

LocalDragDropFSM::LocalDragDropFSM():
m_pState(&Start)
{
}

void LocalDragDropFSM::SetState(LocalDragDropFSMState& state) 
{ 
   WATCHX(DManip,1,_T("Entering state ") << state.StateName());
   m_pState = &state; 
}

LocalDragDropFSMState& LocalDragDropFSM::GetState() const 
{ 
   return *m_pState; 
}

bool LocalDragDropFSM::CompareStates(LocalDragDropFSMState& state)
{ 
   return &state == m_pState; 
}
