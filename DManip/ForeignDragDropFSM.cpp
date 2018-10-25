///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// ForeignDragDropFSM.cpp: implementation of the CForeignDragDropFSM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ForeignDragDropFSM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Definition of static state objects
CForeignDragDropFSMStartState               CForeignDragDropFSM::Start;
CForeignDragDropFSMWaitingForDropState      CForeignDragDropFSM::WaitingForDrop;
CForeignDragDropFSMDoneState                CForeignDragDropFSM::Done;
CForeignDragDropFSMWaitingForDragEnterState CForeignDragDropFSM::WaitingForDragEnter;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CForeignDragDropFSMState::CForeignDragDropFSMState()
{

}

CForeignDragDropFSMState::~CForeignDragDropFSMState()
{

}

void CForeignDragDropFSMState::Do(CForeignDragDropFSM &fsm)
{
   // Default implementation
   fsm.FSMError("Do",fsm.GetState().StateName());
}

DROPEFFECT CForeignDragDropFSMState::DragEnter(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError("DragEnter",fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

void CForeignDragDropFSMState::DragLeave(CForeignDragDropFSM &fsm)
{
   // Default implementation
   fsm.FSMError("DragLeave",fsm.GetState().StateName());
}

DROPEFFECT CForeignDragDropFSMState::DragOver(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError("DragOver",fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

DROPEFFECT CForeignDragDropFSMState::DragScroll(CForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError("DragScroll",fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

BOOL CForeignDragDropFSMState::Drop(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Default implementation
   fsm.FSMError("Drop",fsm.GetState().StateName());
   return FALSE;
}

DROPEFFECT CForeignDragDropFSMState::DropEx(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Default implementation
   fsm.FSMError("DropEx",fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

// States and State Transitions
void CForeignDragDropFSMWaitingForDropState::DragLeave(CForeignDragDropFSM& fsm)
{
   // Action
   fsm.DestroyDragObjects();

   // Change State
   fsm.SetState(CForeignDragDropFSM::Done);
}

DROPEFFECT CForeignDragDropFSMWaitingForDropState::DragOver(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Action
   DROPEFFECT de = fsm.DetermineDropEffect();
   fsm.TrackDragObjects();

   // Change State
   fsm.SetState(CForeignDragDropFSM::WaitingForDrop);

   return de;
}

// States and State Transitions
DROPEFFECT CForeignDragDropFSMWaitingForDragEnterState::DragScroll(CForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

DROPEFFECT CForeignDragDropFSMWaitingForDragEnterState::DragEnter(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Action
   fsm.CreateDragObjects();

   // Change State
   fsm.SetState(CForeignDragDropFSM::WaitingForDrop);

   return DROPEFFECT_NONE;
}

DROPEFFECT CForeignDragDropFSMWaitingForDropState::DragScroll(CForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

BOOL CForeignDragDropFSMWaitingForDropState::Drop(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Action
   fsm.NotifyDropTarget();
   fsm.DestroyDragObjects();

   // Change State
   fsm.SetState(CForeignDragDropFSM::Done);

   return TRUE;
}

DROPEFFECT CForeignDragDropFSMWaitingForDropState::DropEx(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Action
   fsm.DestroyDragObjects();
   fsm.NotifyDropTarget();

   // Change State
   fsm.SetState(CForeignDragDropFSM::Done);

   return DROPEFFECT_NONE;
}

void CForeignDragDropFSMStartState::Do(CForeignDragDropFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(CForeignDragDropFSM::WaitingForDragEnter);
}

CForeignDragDropFSM::CForeignDragDropFSM():
m_pState(&Start)
{
}

void CForeignDragDropFSM::SetState(CForeignDragDropFSMState& state) 
{ 
   WATCHX(DManip,1,"Entering state " << state.StateName());
   m_pState = &state; 
}
CForeignDragDropFSMState& CForeignDragDropFSM::GetState() const 
{ 
   return *m_pState; 
}

bool CForeignDragDropFSM::CompareStates(CForeignDragDropFSMState& state)
{ 
   return &state == m_pState; 
}
