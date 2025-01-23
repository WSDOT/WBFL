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

// ForeignDragDropFSM.h: interface for the CForeighDragDropFSM class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_FOREIGNDRAGDROPFSM_H_
#define INCLUDED_FOREIGNDRAGDROPFSM_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <DManip\ForeignDragDropTask.h>

class CForeignDragDropFSM;

//----------------------------------------------
// CForeignDragDropFSMState: The base state class
//
class CForeignDragDropFSMState  
{
public:
	CForeignDragDropFSMState();
	virtual ~CForeignDragDropFSMState();

	virtual LPCTSTR StateName() const = 0;
	virtual void Do(CForeignDragDropFSM& fsm);
	virtual DROPEFFECT DragEnter(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
	virtual void DragLeave(CForeignDragDropFSM& fsm);
	virtual DROPEFFECT DragOver(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
   virtual DROPEFFECT DragScroll(CForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point);
	virtual BOOL Drop(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point);
   virtual DROPEFFECT DropEx(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point);
};

//----------------------------------------------
// State: Start
//
class CForeignDragDropFSMStartState : public CForeignDragDropFSMState
{
public:
   virtual LPCTSTR StateName() const  override { return _T("Start"); }
   virtual void Do(CForeignDragDropFSM& fsm) override;
};

//----------------------------------------------
// State: Done
//
class CForeignDragDropFSMDoneState : public CForeignDragDropFSMState
{
public:
   virtual LPCTSTR StateName() const override { return _T("Done"); }
};

//----------------------------------------------
// State: WaitingForDragEnter
//
class CForeignDragDropFSMWaitingForDragEnterState : public CForeignDragDropFSMState
{
public:
   virtual LPCTSTR StateName() const  override { return _T("WaitingForDragEnter"); }
   virtual DROPEFFECT DragScroll(CForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point) override;
	virtual DROPEFFECT DragEnter(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
};

//----------------------------------------------
// State: WaitingForDrop
//
class CForeignDragDropFSMWaitingForDropState : public CForeignDragDropFSMState
{
public:
   virtual LPCTSTR StateName() const override { return _T("WaitingForDrop"); }
	virtual void DragLeave(CForeignDragDropFSM& fsm) override;
	virtual DROPEFFECT DragOver(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
   virtual DROPEFFECT DragScroll(CForeignDragDropFSM& fsm,DWORD dwKeyState,CPoint point) override;
	virtual BOOL Drop(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point) override;
   virtual DROPEFFECT DropEx(CForeignDragDropFSM& fsm,COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point) override;
};

class CForeignDragDropFSM : public iForeignDragDropTask
{
public:
   static CForeignDragDropFSMStartState               Start;
   static CForeignDragDropFSMWaitingForDragEnterState WaitingForDragEnter;
   static CForeignDragDropFSMWaitingForDropState      WaitingForDrop;
   static CForeignDragDropFSMDoneState                Done;

   CForeignDragDropFSM();

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
   void SetState(CForeignDragDropFSMState& state);
   CForeignDragDropFSMState& GetState() const;
   bool CompareStates(CForeignDragDropFSMState& state);

private:
   CForeignDragDropFSMState* m_pState;
};

#endif // INCLUDED_FOREIGHDRAGDROPFSM_H_
