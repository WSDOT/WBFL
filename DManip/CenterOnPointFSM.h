///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

// CenterOnPointFSM.h: interface for the CCenterOnPointFSM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CENTERONPOINTFSM_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
#define AFX_CENTERONPOINTFSM_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <DManip\CenterOnPointTask.h>

class CCenterOnPointFSM;

//----------------------------------------------
// CCenterOnPointFSMState: The base state class
//
class CCenterOnPointFSMState  
{
public:
	CCenterOnPointFSMState();
	virtual ~CCenterOnPointFSMState();

	virtual LPCTSTR StateName() const = 0;
	virtual void Do(CCenterOnPointFSM& fsm);
	virtual void DoubleClick(CCenterOnPointFSM& fsm);
	virtual void MouseDown(CCenterOnPointFSM& fsm);
	virtual void MouseUp(CCenterOnPointFSM& fsm);
	virtual void MouseMove(CCenterOnPointFSM& fsm);
	virtual void EscKey(CCenterOnPointFSM& fsm);
};

//----------------------------------------------
// State: Done
//
class CCenterOnPointFSMDoneState : public CCenterOnPointFSMState
{
public:
   virtual LPCTSTR StateName() const override { return _T("Done"); }
};

//----------------------------------------------
// State: WaitingForPoint
//
class CCenterOnPointFSMWaitingForPointState : public CCenterOnPointFSMState
{
public:
   virtual LPCTSTR StateName() const override { return _T("WaitingForPoint"); }
   virtual void MouseMove(CCenterOnPointFSM& fsm) override;
   virtual void MouseDown(CCenterOnPointFSM& fsm) override;
   virtual void DoubleClick(CCenterOnPointFSM& fsm) override;
	virtual void EscKey(CCenterOnPointFSM& fsm) override;
};

//----------------------------------------------
// State: Start
//
class CCenterOnPointFSMStartState : public CCenterOnPointFSMState
{
public:
   virtual LPCTSTR StateName() const override { return _T("Start"); }
   virtual void Do(CCenterOnPointFSM& fsm) override;
};

class CCenterOnPointFSM : public iCenterOnPointTask
{
public:
   static CCenterOnPointFSMStartState Start;
   static CCenterOnPointFSMWaitingForPointState WaitingForPoint;
   static CCenterOnPointFSMDoneState Done;

   CCenterOnPointFSM();

   // Event Functions
   void Do() {m_pState->Do(*this);}
   void DoubleClick() {m_pState->DoubleClick(*this);}
   void MouseDown()   {m_pState->MouseDown(*this); }
   void MouseUp()     {m_pState->MouseUp(*this); }
   void MouseMove()   {m_pState->MouseMove(*this); }
   void EscKey()      {m_pState->EscKey(*this); }

   // State Accessor Functions
   void SetState(CCenterOnPointFSMState& state) { m_pState = &state; }
   CCenterOnPointFSMState& GetState() const { return *m_pState; }

private:
   CCenterOnPointFSMState* m_pState;
};

#endif // !defined(AFX_CENTERONPOINTFSM_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
