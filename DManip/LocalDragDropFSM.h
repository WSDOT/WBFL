///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// LocalDragDropFSM.h: interface for the CLocalDragDropFSM class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_LOCALDRAGDROPFSM_H_
#define INCLUDED_LOCALDRAGDROPFSM_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <DManip\LocalDragDropTask.h>

class CLocalDragDropFSM;

//----------------------------------------------
// CLocalDragDropFSMState: The base state class
//
class CLocalDragDropFSMState  
{
public:
	CLocalDragDropFSMState();
	virtual ~CLocalDragDropFSMState();

	virtual LPCTSTR StateName() const = 0;
	virtual void Do(CLocalDragDropFSM& fsm);
	virtual DROPEFFECT DragEnter(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
	virtual void DragLeave(CLocalDragDropFSM& fsm);
	virtual DROPEFFECT DragOver(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
   virtual DROPEFFECT DragScroll(CLocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point);
	virtual BOOL Drop(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point);
   virtual DROPEFFECT DropEx(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point);
};

//----------------------------------------------
// State: Start
//
class CLocalDragDropFSMStartState : public CLocalDragDropFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("Start"); }
   virtual void Do(CLocalDragDropFSM& fsm);
};

//----------------------------------------------
// State: Done
//
class CLocalDragDropFSMDoneState : public CLocalDragDropFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("Done"); }
};

//----------------------------------------------
// State: WaitingForDragEnter
//
class CLocalDragDropFSMWaitingForDragEnterState : public CLocalDragDropFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("WaitingForDragEnter"); }
   virtual DROPEFFECT DragScroll(CLocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point);
	virtual DROPEFFECT DragEnter(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
};

//----------------------------------------------
// State: WaitingForDrop
//
class CLocalDragDropFSMWaitingForDropState : public CLocalDragDropFSMState
{
public:
   virtual LPCTSTR StateName() const { return _T("WaitingForDrop"); }
	virtual void DragLeave(CLocalDragDropFSM& fsm);
	virtual DROPEFFECT DragOver(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
   virtual DROPEFFECT DragScroll(CLocalDragDropFSM& fsm,DWORD dwKeyState,CPoint point);
	virtual BOOL Drop(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point);
   virtual DROPEFFECT DropEx(CLocalDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point);
};

class CLocalDragDropFSM : public iLocalDragDropTask
{
public:
   static CLocalDragDropFSMStartState               Start;
   static CLocalDragDropFSMWaitingForDragEnterState WaitingForDragEnter;
   static CLocalDragDropFSMWaitingForDropState      WaitingForDrop;
   static CLocalDragDropFSMDoneState                Done;

   CLocalDragDropFSM();

   // Event Functions
   void Do() {m_pState->Do(*this);}

   DROPEFFECT DragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
   {return m_pState->DragEnter(*this,pDataObject,dwKeyState,point); }

   void DragLeave()
   {m_pState->DragLeave(*this); }

   DROPEFFECT DragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
   {return m_pState->DragOver(*this,pDataObject,dwKeyState,point); }
   
   DROPEFFECT DragScroll(DWORD dwKeyState,CPoint point)
   {return m_pState->DragScroll(*this,dwKeyState,point);}

   BOOL Drop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
   {return m_pState->Drop(*this,pDataObject,dropEffect,point); }

   DROPEFFECT DropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
   {return m_pState->DropEx(*this,pDataObject,dropEffect,dropList,point); }

   // State Accessor Functions
   void SetState(CLocalDragDropFSMState& state);
   CLocalDragDropFSMState& GetState() const;
   bool CompareStates(CLocalDragDropFSMState& state);

private:
   CLocalDragDropFSMState* m_pState;
};

#endif // INCLUDED_LOCALDRAGDROPFSM_H_
