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

// InplaceEditFSM.h: interface for the CInplaceEditFSM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_InplaceEditFSM_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
#define AFX_InplaceEditFSM_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <DManip\InplaceEditTask.h>

class CInplaceEditFSM;

//----------------------------------------------
// CInplaceEditFSMState: The base state class
//
class CInplaceEditFSMState  
{
public:
	CInplaceEditFSMState();
	virtual ~CInplaceEditFSMState();

	virtual LPCTSTR StateName() const = 0;

   // Events
	virtual void Do(CInplaceEditFSM& fsm);
	virtual void LButtonDown(CInplaceEditFSM& fsm);
	virtual void KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,CInplaceEditFSM& fsm);
};

//----------------------------------------------
// State: Done
//
class CInplaceEditFSMDoneState : public CInplaceEditFSMState
{
public:
   virtual LPCTSTR StateName() const override { return _T("Done"); }
};

//----------------------------------------------
// State: Cancelled
//
class CInplaceEditFSMCancelledState : public CInplaceEditFSMState
{
public:
   virtual LPCTSTR StateName() const  override { return _T("Cancelled"); }
};

//----------------------------------------------
// State: EnteringText
//
class CInplaceEditFSMEnteringTextState : public CInplaceEditFSMState
{
public:
   virtual LPCTSTR StateName() const  override { return _T("EnteringText"); }
   virtual void LButtonDown(CInplaceEditFSM& fsm) override;
	virtual void KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,CInplaceEditFSM& fsm) override;
};

//----------------------------------------------
// State: Start
//
class CInplaceEditFSMStartState : public CInplaceEditFSMState
{
public:
   virtual LPCTSTR StateName() const  override { return _T("Start"); }
   virtual void Do(CInplaceEditFSM& fsm) override;
};

class CInplaceEditFSM : public iInplaceEditTask
{
public:
   static CInplaceEditFSMStartState Start;
   static CInplaceEditFSMEnteringTextState EnteringText;
   static CInplaceEditFSMDoneState Done;
   static CInplaceEditFSMCancelledState Cancelled;

   CInplaceEditFSM();

   // Event Functions
   void Do() {m_pState->Do(*this);}
   void LButtonDown()   {m_pState->LButtonDown(*this); }
   void KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags)
   {m_pState->KeyPress(nChar,nRepCnt,nFlags,*this);}

   // State Accessor Functions
   void SetState(CInplaceEditFSMState& state) { m_pState = &state; }
   CInplaceEditFSMState& GetState() const { return *m_pState; }
   bool CompareStates(CInplaceEditFSMState& state)
   { return &state == m_pState; }

private:
   CInplaceEditFSMState* m_pState;
};

#endif // !defined(AFX_InplaceEditFSM_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
