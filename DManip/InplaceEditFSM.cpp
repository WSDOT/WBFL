///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

// InplaceEditFSM.cpp: implementation of the CInplaceEditFSMState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InplaceEditFSM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Definition of static state objects
CInplaceEditFSMStartState        CInplaceEditFSM::Start;
CInplaceEditFSMEnteringTextState CInplaceEditFSM::EnteringText;
CInplaceEditFSMDoneState         CInplaceEditFSM::Done;
CInplaceEditFSMCancelledState    CInplaceEditFSM::Cancelled;

//////////////////////////////////////////////////////////
// Finite State Machine Initialization
CInplaceEditFSM::CInplaceEditFSM():
m_pState(&Start) // Begin in the Start state
{
}

//////////////////////////////////////////////////////////
// Default implementation for State objects
CInplaceEditFSMState::CInplaceEditFSMState()
{
}

CInplaceEditFSMState::~CInplaceEditFSMState()
{

}

void CInplaceEditFSMState::Do(CInplaceEditFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

void CInplaceEditFSMState::LButtonDown(CInplaceEditFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("LButtonDown"),fsm.GetState().StateName());
}

void CInplaceEditFSMState::KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,CInplaceEditFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("KeyPress"),fsm.GetState().StateName());
}

//////////////////////////////////////////////////////////
// States and State Transitions


void CInplaceEditFSMStartState::Do(CInplaceEditFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(CInplaceEditFSM::EnteringText);
}

void CInplaceEditFSMEnteringTextState::LButtonDown(CInplaceEditFSM& fsm)
{
   // Action
   BOOL bValid = fsm.ValidateData();

   // Change State
   if ( bValid )
   {
      fsm.SetState(CInplaceEditFSM::Done);
   }
   else
   {
      ::MessageBeep(MB_ICONEXCLAMATION);
      fsm.SetState(CInplaceEditFSM::EnteringText);
   }
}

void CInplaceEditFSMEnteringTextState::KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,CInplaceEditFSM& fsm)
{
   // Conditional action and state change
   if ( nChar == VK_ESCAPE )
   {
      fsm.SetState(CInplaceEditFSM::Cancelled);
   }
   else if ( nChar == VK_RETURN )
   {
      // Same as if user clicked Left mouse button
      LButtonDown(fsm);
   }
}
