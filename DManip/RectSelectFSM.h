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

// RectSelectFSM.h: interface for the CRectSelectFSMState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LBTNRECTSELECTFSMSTATE_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
#define AFX_LBTNRECTSELECTFSMSTATE_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <DManip\RectSelectTask.h>

class CRectSelectFSM;

//----------------------------------------------
// CRectSelectFSMState: The base state class
//
class CRectSelectFSMState  
{
public:
	CRectSelectFSMState();
	virtual ~CRectSelectFSMState();

	virtual LPCTSTR StateName() const = 0;
	virtual void Do(CRectSelectFSM& fsm);
	virtual void MouseDown(CRectSelectFSM& fsm);
	virtual void MouseUp(CRectSelectFSM& fsm);
	virtual void MouseMove(CRectSelectFSM& fsm);
	virtual void KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,CRectSelectFSM& fsm);
};

//----------------------------------------------
// State: Done
//
class CRectSelectFSMDoneState : public CRectSelectFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("Done"); }
};

//----------------------------------------------
// State: WaitingForSecondPoint
//
class CRectSelectFSMWaitingForSecondPointState : public CRectSelectFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("WaitingForSecondPoint"); }
   virtual void MouseMove(CRectSelectFSM& fsm);
   virtual void MouseUp(CRectSelectFSM& fsm);
   virtual void KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,CRectSelectFSM& fsm);
};

//----------------------------------------------
// State: Start
//
class CRectSelectFSMStartState : public CRectSelectFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("Start"); }
   virtual void Do(CRectSelectFSM& fsm);
};

class CRectSelectFSM : public iRectSelectTask
{
public:
   static CRectSelectFSMStartState Start;
   static CRectSelectFSMWaitingForSecondPointState WaitingForSecondPoint;
   static CRectSelectFSMDoneState Done;

   CRectSelectFSM();

   // Event Functions
   void Do() {m_pState->Do(*this);}
   void MouseDown()   {m_pState->MouseDown(*this); }
   void MouseUp()     {m_pState->MouseUp(*this); }
   void MouseMove()   {m_pState->MouseMove(*this); }
   void KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags)
   {m_pState->KeyPress(nChar,nRepCnt,nFlags,*this); }

   // State Accessor Functions
   void SetState(CRectSelectFSMState& state) { m_pState = &state; }
   CRectSelectFSMState& GetState() const { return *m_pState; }
   bool CompareStates(CRectSelectFSMState& state)
   { return &state == m_pState; }

private:
   CRectSelectFSMState* m_pState;
};

#endif // !defined(AFX_LBTNRECTSELECTFSMSTATE_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
