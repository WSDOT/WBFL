///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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

// RectSelectFSMState.cpp: implementation of the CZoomRectFSMState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZoomRectFSM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Definition of static state objects
CZoomRectFSMStartState CZoomRectFSM::Start;
CZoomRectFSMWaitingForFirstPointState CZoomRectFSM::WaitingForFirstPoint;
CZoomRectFSMWaitingForSecondPointState CZoomRectFSM::WaitingForSecondPoint;
CZoomRectFSMDoneState CZoomRectFSM::Done;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZoomRectFSMState::CZoomRectFSMState()
{

}

CZoomRectFSMState::~CZoomRectFSMState()
{

}

void CZoomRectFSMState::Do(CZoomRectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("Do"),fsm.GetState().StateName());
}

void CZoomRectFSMState::DoubleClick(CZoomRectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("DoubleClick"),fsm.GetState().StateName());
}

void CZoomRectFSMState::MouseDown(CZoomRectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseDown"),fsm.GetState().StateName());
}

void CZoomRectFSMState::MouseUp(CZoomRectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseUp"),fsm.GetState().StateName());
}

void CZoomRectFSMState::MouseMove(CZoomRectFSM &fsm)
{
   // Default implementation
   fsm.FSMError(_T("MouseMove"),fsm.GetState().StateName());
}

void CZoomRectFSMState::EscKey(CZoomRectFSM& fsm)
{
   // Default implementation
   fsm.FSMError(_T("EscKey"),fsm.GetState().StateName());
}

// States and State Transitions
void CZoomRectFSMWaitingForFirstPointState::MouseMove(CZoomRectFSM& fsm)
{
}

void CZoomRectFSMWaitingForFirstPointState::MouseDown(CZoomRectFSM& fsm)
{
   // Action
   fsm.RecordFirstPoint();

   // Change State
   fsm.SetState(CZoomRectFSM::WaitingForSecondPoint);
}

void CZoomRectFSMWaitingForFirstPointState::DoubleClick(CZoomRectFSM& fsm)
{
}

void CZoomRectFSMWaitingForFirstPointState::EscKey(CZoomRectFSM& fsm)
{
   // Action
   fsm.Cancel();

   // State Change
   fsm.SetState(CZoomRectFSM::Done);
}

void CZoomRectFSMWaitingForSecondPointState::MouseUp(CZoomRectFSM& fsm)
{
   // Action
   fsm.ZoomRect();

   // Change State
   fsm.SetState(CZoomRectFSM::Done);
}

void CZoomRectFSMWaitingForSecondPointState::MouseMove(CZoomRectFSM& fsm)
{
   // Action
   fsm.TrackRect();

   // Change State
   fsm.SetState(CZoomRectFSM::WaitingForSecondPoint);
}

void CZoomRectFSMWaitingForSecondPointState::DoubleClick(CZoomRectFSM& fsm)
{
   // No action or state change. Just a stub so the default error doesn't occur
}

void CZoomRectFSMWaitingForSecondPointState::EscKey(CZoomRectFSM& fsm)
{
   // Action
   fsm.Cancel();

   // State Change
   fsm.SetState(CZoomRectFSM::Done);
}


void CZoomRectFSMStartState::Do(CZoomRectFSM& fsm)
{
   // Action
   fsm.InitTask();

   // Change State
   fsm.SetState(CZoomRectFSM::WaitingForFirstPoint);
}

CZoomRectFSM::CZoomRectFSM():
m_pState(&Start)
{
}
