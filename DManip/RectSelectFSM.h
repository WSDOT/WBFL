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

#pragma once

#include "RectSelectTask.h"

namespace WBFL
{
   namespace DManip
   {
      class RectSelectFSM;

      //----------------------------------------------
      // RectSelectFSMState: The base state class
      //
      class RectSelectFSMState  
      {
      public:
	      RectSelectFSMState();
	      virtual ~RectSelectFSMState();

	      virtual LPCTSTR StateName() const = 0;
	      virtual void Do(RectSelectFSM& fsm);
	      virtual void MouseDown(RectSelectFSM& fsm);
	      virtual void MouseUp(RectSelectFSM& fsm);
	      virtual void MouseMove(RectSelectFSM& fsm);
	      virtual void KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,RectSelectFSM& fsm);
      };

      //----------------------------------------------
      // State: Done
      //
      class RectSelectFSMDoneState : public RectSelectFSMState
      {
      public:
         virtual LPCTSTR StateName() const override { return _T("Done"); }
      };

      //----------------------------------------------
      // State: WaitingForSecondPoint
      //
      class RectSelectFSMWaitingForSecondPointState : public RectSelectFSMState
      {
      public:
         virtual LPCTSTR StateName() const override { return _T("WaitingForSecondPoint"); }
         virtual void MouseMove(RectSelectFSM& fsm) override;
         virtual void MouseUp(RectSelectFSM& fsm) override;
         virtual void KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags,RectSelectFSM& fsm) override;
      };

      //----------------------------------------------
      // State: Start
      //
      class RectSelectFSMStartState : public RectSelectFSMState
      {
      public:
         virtual LPCTSTR StateName() const  override { return _T("Start"); }
         virtual void Do(RectSelectFSM& fsm) override;
      };

      class RectSelectFSM : public iRectSelectTask
      {
      public:
         static RectSelectFSMStartState Start;
         static RectSelectFSMWaitingForSecondPointState WaitingForSecondPoint;
         static RectSelectFSMDoneState Done;

         RectSelectFSM();

         // Event Functions
         void Do() {m_pState->Do(*this);}
         void MouseDown()   {m_pState->MouseDown(*this); }
         void MouseUp()     {m_pState->MouseUp(*this); }
         void MouseMove()   {m_pState->MouseMove(*this); }
         void KeyPress(UINT nChar, UINT nRepCnt, UINT nFlags)
         {m_pState->KeyPress(nChar,nRepCnt,nFlags,*this); }

         // State Accessor Functions
         void SetState(RectSelectFSMState& state) { m_pState = &state; }
         RectSelectFSMState& GetState() const { return *m_pState; }
         bool CompareStates(RectSelectFSMState& state)
         { return &state == m_pState; }

      private:
         RectSelectFSMState* m_pState;
      };
   };
};
