///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

// ZoomRectFSM.h: interface for the CZoomRectFSM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZOOMRECTFSM_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
#define AFX_ZOOMRECTFSM_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <DManip\DManipExp.h>
#include <DManip\ZoomRectTask.h>

class CZoomRectFSM;

//----------------------------------------------
// CZoomRectFSMState: The base state class
//
class DMANIPCLASS CZoomRectFSMState  
{
public:
	CZoomRectFSMState();
	virtual ~CZoomRectFSMState();

	virtual LPCTSTR StateName() const = 0;
	virtual void Do(CZoomRectFSM& fsm);
	virtual void DoubleClick(CZoomRectFSM& fsm);
	virtual void MouseDown(CZoomRectFSM& fsm);
	virtual void MouseUp(CZoomRectFSM& fsm);
	virtual void MouseMove(CZoomRectFSM& fsm);
   virtual void EscKey(CZoomRectFSM& fsm);
};

//----------------------------------------------
// State: Done
//
class CZoomRectFSMDoneState : public CZoomRectFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("Done"); }
};

//----------------------------------------------
// State: WaitingForFirstPoint
//
class CZoomRectFSMWaitingForFirstPointState : public CZoomRectFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("WaitingForFirstPoint"); }
   virtual void MouseMove(CZoomRectFSM& fsm);
   virtual void MouseDown(CZoomRectFSM& fsm);
   virtual void DoubleClick(CZoomRectFSM& fsm);
   virtual void EscKey(CZoomRectFSM& fsm);
};

//----------------------------------------------
// State: WaitingForSecondPoint
//
class CZoomRectFSMWaitingForSecondPointState : public CZoomRectFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("WaitingForSecondPoint"); }
   virtual void MouseMove(CZoomRectFSM& fsm);
   virtual void MouseUp(CZoomRectFSM& fsm);
   virtual void DoubleClick(CZoomRectFSM& fsm);
   virtual void EscKey(CZoomRectFSM& fsm);
};

//----------------------------------------------
// State: Start
//
class CZoomRectFSMStartState : public CZoomRectFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("Start"); }
   virtual void Do(CZoomRectFSM& fsm);
};

class CZoomRectFSM : public iZoomRectTask
{
public:
   static CZoomRectFSMStartState Start;
   static CZoomRectFSMWaitingForFirstPointState WaitingForFirstPoint;
   static CZoomRectFSMWaitingForSecondPointState WaitingForSecondPoint;
   static CZoomRectFSMDoneState Done;

   CZoomRectFSM();

   // Event Functions
   void Do() {m_pState->Do(*this);}
   void DoubleClick() {m_pState->DoubleClick(*this);}
   void MouseDown()   {m_pState->MouseDown(*this); }
   void MouseUp()     {m_pState->MouseUp(*this); }
   void MouseMove()   {m_pState->MouseMove(*this); }
   void EscKey()      {m_pState->EscKey(*this); }

   // State Accessor Functions
   void SetState(CZoomRectFSMState& state) { m_pState = &state; }
   CZoomRectFSMState& GetState() const { return *m_pState; }

private:
   CZoomRectFSMState* m_pState;
};

#endif // !defined(AFX_ZOOMRECTFSM_H__5D499BF5_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
