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
#include "ZoomRectFSM.h"

using namespace WBFL::DManip;

// Definition of static state objects
ZoomRectFSMStartState ZoomRectFSM::Start;
ZoomRectFSMWaitingForFirstPointState ZoomRectFSM::WaitingForFirstPoint;
ZoomRectFSMWaitingForSecondPointState ZoomRectFSM::WaitingForSecondPoint;
ZoomRectFSMDoneState ZoomRectFSM::Done;

ZoomRectFSMState::ZoomRectFSMState()
{

}

ZoomRectFSMState::~ZoomRectFSMState()
{

}

void ZoomRectFSMState::Do(ZoomRectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

void ZoomRectFSMState::DoubleClick(ZoomRectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("DoubleClick"),fsm.GetState().StateName());
}

void ZoomRectFSMState::MouseDown(ZoomRectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseDown"),fsm.GetState().StateName());
}

void ZoomRectFSMState::MouseUp(ZoomRectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseUp"),fsm.GetState().StateName());
}

void ZoomRectFSMState::MouseMove(ZoomRectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseMove"),fsm.GetState().StateName());
}

void ZoomRectFSMState::EscKey(ZoomRectFSM& fsm)
{
   // Default implementation
   fsm.FSMError(_T("EscKey"),fsm.GetState().StateName());
}

// States and State Transitions
void ZoomRectFSMWaitingForFirstPointState::MouseMove(ZoomRectFSM& fsm)
{
}

void ZoomRectFSMWaitingForFirstPointState::MouseDown(ZoomRectFSM& fsm)
{
   // Action
   fsm.RecordFirstPoint();

   // Change State
   fsm.SetState(ZoomRectFSM::WaitingForSecondPoint);
}

void ZoomRectFSMWaitingForFirstPointState::DoubleClick(ZoomRectFSM& fsm)
{
}

void ZoomRectFSMWaitingForFirstPointState::EscKey(ZoomRectFSM& fsm)
{
   // Action
   fsm.Cancel();

   // State Change
   fsm.SetState(ZoomRectFSM::Done);
}

void ZoomRectFSMWaitingForSecondPointState::MouseUp(ZoomRectFSM& fsm)
{
   // Action
   fsm.ZoomRect();

   // Change State
   fsm.SetState(ZoomRectFSM::Done);
}

void ZoomRectFSMWaitingForSecondPointState::MouseMove(ZoomRectFSM& fsm)
{
   // Action
   fsm.TrackRect();

   // Change State
   fsm.SetState(ZoomRectFSM::WaitingForSecondPoint);
}

void ZoomRectFSMWaitingForSecondPointState::DoubleClick(ZoomRectFSM& fsm)
{
   // No action or state change. Just a stub so the default error doesn't occur
}

void ZoomRectFSMWaitingForSecondPointState::EscKey(ZoomRectFSM& fsm)
{
   // Action
   fsm.Cancel();

   // State Change
   fsm.SetState(ZoomRectFSM::Done);
}


void ZoomRectFSMStartState::Do(ZoomRectFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(ZoomRectFSM::WaitingForFirstPoint);
}

ZoomRectFSM::ZoomRectFSM():
m_pState(&Start)
{
}
