///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// LocalDragDropFSM.cpp: implementation of the CLocalDragDropFSM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LocalDragDropFSM.h"

#include "DManipDebug.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Definition of static state objects
CLocalDragDropFSMStartState               CLocalDragDropFSM::Start;
CLocalDragDropFSMWaitingForDragEnterState CLocalDragDropFSM::WaitingForDragEnter;
CLocalDragDropFSMWaitingForDropState      CLocalDragDropFSM::WaitingForDrop;
CLocalDragDropFSMDoneState                CLocalDragDropFSM::Done;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLocalDragDropFSMState::CLocalDragDropFSMState()
{

}

CLocalDragDropFSMState::~CLocalDragDropFSMState()
{

}

void CLocalDragDropFSMState::Do(CLocalDragDropFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

DROPEFFECT CLocalDragDropFSMState::DragEnter(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DragEnter"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

void CLocalDragDropFSMState::DragLeave(CLocalDragDropFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("DragLeave"),fsm.GetState().StateName());
}

DROPEFFECT CLocalDragDropFSMState::DragOver(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DragOver"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

DROPEFFECT CLocalDragDropFSMState::DragScroll(CLocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DragScroll"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

BOOL CLocalDragDropFSMState::Drop(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("Drop"),fsm.GetState().StateName());
   return FALSE;
}

DROPEFFECT CLocalDragDropFSMState::DropEx(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Default implementation
   fsm.FSMError(_T("DropEx"),fsm.GetState().StateName());
   return DROPEFFECT_NONE;
}

// States and State Transitions
DROPEFFECT CLocalDragDropFSMWaitingForDragEnterState::DragScroll(CLocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

DROPEFFECT CLocalDragDropFSMWaitingForDragEnterState::DragEnter(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Action
   fsm.CreateDragObjects();

   // Change State
   fsm.SetState(CLocalDragDropFSM::WaitingForDrop);

   return DROPEFFECT_NONE;
}

void CLocalDragDropFSMWaitingForDropState::DragLeave(CLocalDragDropFSM& fsm)
{
   // Action
   fsm.DestroyDragObjects();

   // Change State
   fsm.SetState(CLocalDragDropFSM::WaitingForDragEnter);
}

DROPEFFECT CLocalDragDropFSMWaitingForDropState::DragOver(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Action
   DROPEFFECT de = fsm.DetermineDropEffect();
   fsm.TrackDragObjects();

   // Change State
   fsm.SetState(CLocalDragDropFSM::WaitingForDrop);

   return de;
}

DROPEFFECT CLocalDragDropFSMWaitingForDropState::DragScroll(CLocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

BOOL CLocalDragDropFSMWaitingForDropState::Drop(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Action
   fsm.NotifyDropTarget();
   fsm.DestroyDragObjects();

   // Change State
   fsm.SetState(CLocalDragDropFSM::Done);

   return TRUE;
}

DROPEFFECT CLocalDragDropFSMWaitingForDropState::DropEx(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Action
   fsm.DestroyDragObjects();
   fsm.NotifyDropTarget();

   // Change State
   fsm.SetState(CLocalDragDropFSM::Done);

   return DROPEFFECT_NONE;
}

void CLocalDragDropFSMStartState::Do(CLocalDragDropFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(CLocalDragDropFSM::WaitingForDragEnter);
}

CLocalDragDropFSM::CLocalDragDropFSM():
m_pState(&Start)
{
}

void CLocalDragDropFSM::SetState(CLocalDragDropFSMState& state) 
{ 
   WATCHX(DManip,1,_T("Entering state ") << state.StateName());
   m_pState = &state; 
}

CLocalDragDropFSMState& CLocalDragDropFSM::GetState() const 
{ 
   return *m_pState; 
}

bool CLocalDragDropFSM::CompareStates(CLocalDragDropFSMState& state)
{ 
   return &state == m_pState; 
}
