///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// CenterOnPointFSM.cpp: implementation of the CCenterOnPointFSMState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CenterOnPointFSM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Definition of static state objects
CCenterOnPointFSMStartState CCenterOnPointFSM::Start;
CCenterOnPointFSMWaitingForPointState CCenterOnPointFSM::WaitingForPoint;
CCenterOnPointFSMDoneState CCenterOnPointFSM::Done;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCenterOnPointFSMState::CCenterOnPointFSMState()
{

}

CCenterOnPointFSMState::~CCenterOnPointFSMState()
{

}

void CCenterOnPointFSMState::Do(CCenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

void CCenterOnPointFSMState::DoubleClick(CCenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("DoubleClick"),fsm.GetState().StateName());
}

void CCenterOnPointFSMState::MouseDown(CCenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseDown"),fsm.GetState().StateName());
}

void CCenterOnPointFSMState::MouseUp(CCenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseUp"),fsm.GetState().StateName());
}

void CCenterOnPointFSMState::MouseMove(CCenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseMove"),fsm.GetState().StateName());
}

void CCenterOnPointFSMState::EscKey(CCenterOnPointFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("EscKey"),fsm.GetState().StateName());
}

// States and State Transitions
void CCenterOnPointFSMWaitingForPointState::MouseMove(CCenterOnPointFSM& fsm)
{
}

void CCenterOnPointFSMWaitingForPointState::MouseDown(CCenterOnPointFSM& fsm)
{
   // Action
   fsm.CenterOnPoint();

   // Change State
   fsm.SetState(CCenterOnPointFSM::Done);
}

void CCenterOnPointFSMWaitingForPointState::DoubleClick(CCenterOnPointFSM& fsm)
{
}

void CCenterOnPointFSMWaitingForPointState::EscKey(CCenterOnPointFSM& fsm)
{
   fsm.Cancel();
   fsm.SetState(CCenterOnPointFSM::Done);
}

void CCenterOnPointFSMStartState::Do(CCenterOnPointFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(CCenterOnPointFSM::WaitingForPoint);
}

CCenterOnPointFSM::CCenterOnPointFSM():
m_pState(&Start)
{
}
