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

// RectSelectFSM.cpp: implementation of the CRectSelectFSMState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RectSelectFSM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Definition of static state objects
CRectSelectFSMStartState                 CRectSelectFSM::Start;
CRectSelectFSMWaitingForSecondPointState CRectSelectFSM::WaitingForSecondPoint;
CRectSelectFSMDoneState                  CRectSelectFSM::Done;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectSelectFSMState::CRectSelectFSMState()
{

}

CRectSelectFSMState::~CRectSelectFSMState()
{

}

void CRectSelectFSMState::Do(CRectSelectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

void CRectSelectFSMState::MouseDown(CRectSelectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseDown"),fsm.GetState().StateName());
}

void CRectSelectFSMState::MouseUp(CRectSelectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseUp"),fsm.GetState().StateName());
}

void CRectSelectFSMState::MouseMove(CRectSelectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseMove"),fsm.GetState().StateName());
}

void CRectSelectFSMState::KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,CRectSelectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("KeyPress"),fsm.GetState().StateName());
}

// States and State Transitions
void CRectSelectFSMWaitingForSecondPointState::MouseUp(CRectSelectFSM& fsm)
{
   // Action
   fsm.SelectObjects();

   // Change State
   fsm.SetState(CRectSelectFSM::Done);
}

void CRectSelectFSMWaitingForSecondPointState::MouseMove(CRectSelectFSM& fsm)
{
   // Action
   fsm.TrackRect();

   // Change State
   fsm.SetState(CRectSelectFSM::WaitingForSecondPoint);
}

void CRectSelectFSMWaitingForSecondPointState::KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,CRectSelectFSM& fsm)
{
   // Conditional state change
   if ( nChar == VK_ESCAPE )
   {
      // Action
      fsm.Cancel();

      // Change State
      fsm.SetState(CRectSelectFSM::Done);
   }
}


void CRectSelectFSMStartState::Do(CRectSelectFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(CRectSelectFSM::WaitingForSecondPoint);
}

CRectSelectFSM::CRectSelectFSM():
m_pState(&Start)
{
}
