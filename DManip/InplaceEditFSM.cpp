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
#include "InplaceEditFSM.h"

using namespace WBFL::DManip;

// Definition of static state objects
InplaceEditFSMStartState        InplaceEditFSM::Start;
InplaceEditFSMEnteringTextState InplaceEditFSM::EnteringText;
InplaceEditFSMDoneState         InplaceEditFSM::Done;
InplaceEditFSMCancelledState    InplaceEditFSM::Cancelled;

//////////////////////////////////////////////////////////
// Finite State Machine Initialization
InplaceEditFSM::InplaceEditFSM():
m_pState(&Start) // Begin in the Start state
{
}

//////////////////////////////////////////////////////////
// Default implementation for State objects
InplaceEditFSMState::InplaceEditFSMState()
{
}

InplaceEditFSMState::~InplaceEditFSMState()
{

}

void InplaceEditFSMState::Do(InplaceEditFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

void InplaceEditFSMState::LButtonDown(InplaceEditFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("LButtonDown"),fsm.GetState().StateName());
}

void InplaceEditFSMState::KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,InplaceEditFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("KeyPress"),fsm.GetState().StateName());
}

//////////////////////////////////////////////////////////
// States and State Transitions


void InplaceEditFSMStartState::Do(InplaceEditFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(InplaceEditFSM::EnteringText);
}

void InplaceEditFSMEnteringTextState::LButtonDown(InplaceEditFSM& fsm)
{
   // Action
   BOOL bValid = fsm.ValidateData();

   // Change State
   if ( bValid )
   {
      fsm.SetState(InplaceEditFSM::Done);
   }
   else
   {
      ::MessageBeep(MB_ICONEXCLAMATION);
      fsm.SetState(InplaceEditFSM::EnteringText);
   }
}

void InplaceEditFSMEnteringTextState::KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,InplaceEditFSM& fsm)
{
   // Conditional action and state change
   if ( nChar == VK_ESCAPE )
   {
      fsm.SetState(InplaceEditFSM::Cancelled);
   }
   else if ( nChar == VK_RETURN )
   {
      // Same as if user clicked Left mouse button
      LButtonDown(fsm);
   }
}
