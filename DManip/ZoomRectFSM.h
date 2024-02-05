///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

#pragma once

#include "ZoomRectTask.h"

namespace WBFL
{
   namespace DManip
   {
      class ZoomRectFSM;

      //----------------------------------------------
      // ZoomRectFSMState: The base state class
      //
      class ZoomRectFSMState  
      {
      public:
	      ZoomRectFSMState();
	      virtual ~ZoomRectFSMState();

	      virtual LPCTSTR StateName() const = 0;
	      virtual void Do(ZoomRectFSM& fsm);
	      virtual void DoubleClick(ZoomRectFSM& fsm);
	      virtual void MouseDown(ZoomRectFSM& fsm);
	      virtual void MouseUp(ZoomRectFSM& fsm);
	      virtual void MouseMove(ZoomRectFSM& fsm);
         virtual void EscKey(ZoomRectFSM& fsm);
      };

      //----------------------------------------------
      // State: Done
      //
      class ZoomRectFSMDoneState : public ZoomRectFSMState
      {
      public:
         virtual LPCTSTR StateName() const  override { return _T("Done"); }
      };

      //----------------------------------------------
      // State: WaitingForFirstPoint
      //
      class ZoomRectFSMWaitingForFirstPointState : public ZoomRectFSMState
      {
      public:
         virtual LPCTSTR StateName() const  override { return _T("WaitingForFirstPoint"); }
         virtual void MouseMove(ZoomRectFSM& fsm) override;
         virtual void MouseDown(ZoomRectFSM& fsm) override;
         virtual void DoubleClick(ZoomRectFSM& fsm) override;
         virtual void EscKey(ZoomRectFSM& fsm) override;
      };

      //----------------------------------------------
      // State: WaitingForSecondPoint
      //
      class ZoomRectFSMWaitingForSecondPointState : public ZoomRectFSMState
      {
      public:
         virtual LPCTSTR StateName() const override { return _T("WaitingForSecondPoint"); }
         virtual void MouseMove(ZoomRectFSM& fsm) override;
         virtual void MouseUp(ZoomRectFSM& fsm) override;
         virtual void DoubleClick(ZoomRectFSM& fsm) override;
         virtual void EscKey(ZoomRectFSM& fsm) override;
      };

      //----------------------------------------------
      // State: Start
      //
      class ZoomRectFSMStartState : public ZoomRectFSMState
      {
      public:
         virtual LPCTSTR StateName() const  override { return _T("Start"); }
         virtual void Do(ZoomRectFSM& fsm) override;
      };

      class ZoomRectFSM : public iZoomRectTask
      {
      public:
         static ZoomRectFSMStartState Start;
         static ZoomRectFSMWaitingForFirstPointState WaitingForFirstPoint;
         static ZoomRectFSMWaitingForSecondPointState WaitingForSecondPoint;
         static ZoomRectFSMDoneState Done;

         ZoomRectFSM();

         // Event Functions
         void Do() {m_pState->Do(*this);}
         void DoubleClick() {m_pState->DoubleClick(*this);}
         void MouseDown()   {m_pState->MouseDown(*this); }
         void MouseUp()     {m_pState->MouseUp(*this); }
         void MouseMove()   {m_pState->MouseMove(*this); }
         void EscKey()      {m_pState->EscKey(*this); }

         // State Accessor Functions
         void SetState(ZoomRectFSMState& state) { m_pState = &state; }
         ZoomRectFSMState& GetState() const { return *m_pState; }

      private:
         ZoomRectFSMState* m_pState;
      };
   };
};
