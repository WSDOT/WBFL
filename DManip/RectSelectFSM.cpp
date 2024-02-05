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
#include "RectSelectFSM.h"

using namespace WBFL::DManip;

// Definition of static state objects
RectSelectFSMStartState                 RectSelectFSM::Start;
RectSelectFSMWaitingForSecondPointState RectSelectFSM::WaitingForSecondPoint;
RectSelectFSMDoneState                  RectSelectFSM::Done;

RectSelectFSMState::RectSelectFSMState()
{

}

RectSelectFSMState::~RectSelectFSMState()
{

}

void RectSelectFSMState::Do(RectSelectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

void RectSelectFSMState::MouseDown(RectSelectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseDown"),fsm.GetState().StateName());
}

void RectSelectFSMState::MouseUp(RectSelectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseUp"),fsm.GetState().StateName());
}

void RectSelectFSMState::MouseMove(RectSelectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseMove"),fsm.GetState().StateName());
}

void RectSelectFSMState::KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,RectSelectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("KeyPress"),fsm.GetState().StateName());
}

// States and State Transitions
void RectSelectFSMWaitingForSecondPointState::MouseUp(RectSelectFSM& fsm)
{
   // Action
   fsm.SelectObjects();

   // Change State
   fsm.SetState(RectSelectFSM::Done);
}

void RectSelectFSMWaitingForSecondPointState::MouseMove(RectSelectFSM& fsm)
{
   // Action
   fsm.TrackRect();

   // Change State
   fsm.SetState(RectSelectFSM::WaitingForSecondPoint);
}

void RectSelectFSMWaitingForSecondPointState::KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,RectSelectFSM& fsm)
{
   // Conditional state change
   if ( nChar == VK_ESCAPE )
   {
      // Action
      fsm.Cancel();

      // Change State
      fsm.SetState(RectSelectFSM::Done);
   }
}


void RectSelectFSMStartState::Do(RectSelectFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(RectSelectFSM::WaitingForSecondPoint);
}

RectSelectFSM::RectSelectFSM():
m_pState(&Start)
{
}
