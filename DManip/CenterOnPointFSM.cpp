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
#include "CenterOnPointFSM.h"

using namespace WBFL::DManip;

// Definition of static state objects
CenterOnPointFSMStartState CenterOnPointFSM::Start;
CenterOnPointFSMWaitingForPointState CenterOnPointFSM::WaitingForPoint;
CenterOnPointFSMDoneState CenterOnPointFSM::Done;

CenterOnPointFSMState::CenterOnPointFSMState()
{

}

CenterOnPointFSMState::~CenterOnPointFSMState()
{

}

void CenterOnPointFSMState::Do(CenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

void CenterOnPointFSMState::DoubleClick(CenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("DoubleClick"),fsm.GetState().StateName());
}

void CenterOnPointFSMState::MouseDown(CenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseDown"),fsm.GetState().StateName());
}

void CenterOnPointFSMState::MouseUp(CenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseUp"),fsm.GetState().StateName());
}

void CenterOnPointFSMState::MouseMove(CenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseMove"),fsm.GetState().StateName());
}

void CenterOnPointFSMState::EscKey(CenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("EscKey"),fsm.GetState().StateName());
}

// States and State Transitions
void CenterOnPointFSMWaitingForPointState::MouseMove(CenterOnPointFSM& fsm)
{
}

void CenterOnPointFSMWaitingForPointState::MouseDown(CenterOnPointFSM& fsm)
{
   // Action
   fsm.CenterOnPoint();

   // Change State
   fsm.SetState(CenterOnPointFSM::Done);
}

void CenterOnPointFSMWaitingForPointState::DoubleClick(CenterOnPointFSM& fsm)
{
}

void CenterOnPointFSMWaitingForPointState::EscKey(CenterOnPointFSM& fsm)
{
   fsm.Cancel();
   fsm.SetState(CenterOnPointFSM::Done);
}

void CenterOnPointFSMStartState::Do(CenterOnPointFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(CenterOnPointFSM::WaitingForPoint);
}

CenterOnPointFSM::CenterOnPointFSM():
m_pState(&Start)
{
}
