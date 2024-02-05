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

#include "CenterOnPointTask.h"

namespace WBFL
{
   namespace DManip
   {
      class CenterOnPointFSM;

      //----------------------------------------------
      // CenterOnPointFSMState: The base state class
      //
      class CenterOnPointFSMState  
      {
      public:
	      CenterOnPointFSMState();
	      virtual ~CenterOnPointFSMState();

	      virtual LPCTSTR StateName() const = 0;
	      virtual void Do(CenterOnPointFSM& fsm);
	      virtual void DoubleClick(CenterOnPointFSM& fsm);
	      virtual void MouseDown(CenterOnPointFSM& fsm);
	      virtual void MouseUp(CenterOnPointFSM& fsm);
	      virtual void MouseMove(CenterOnPointFSM& fsm);
	      virtual void EscKey(CenterOnPointFSM& fsm);
      };

      //----------------------------------------------
      // State: Done
      //
      class CenterOnPointFSMDoneState : public CenterOnPointFSMState
      {
      public:
         virtual LPCTSTR StateName() const override { return _T("Done"); }
      };

      //----------------------------------------------
      // State: WaitingForPoint
      //
      class CenterOnPointFSMWaitingForPointState : public CenterOnPointFSMState
      {
      public:
         virtual LPCTSTR StateName() const override { return _T("WaitingForPoint"); }
         virtual void MouseMove(CenterOnPointFSM& fsm) override;
         virtual void MouseDown(CenterOnPointFSM& fsm) override;
         virtual void DoubleClick(CenterOnPointFSM& fsm) override;
	      virtual void EscKey(CenterOnPointFSM& fsm) override;
      };

      //----------------------------------------------
      // State: Start
      //
      class CenterOnPointFSMStartState : public CenterOnPointFSMState
      {
      public:
         virtual LPCTSTR StateName() const override { return _T("Start"); }
         virtual void Do(CenterOnPointFSM& fsm) override;
      };

      class CenterOnPointFSM : public iCenterOnPointTask
      {
      public:
         static CenterOnPointFSMStartState Start;
         static CenterOnPointFSMWaitingForPointState WaitingForPoint;
         static CenterOnPointFSMDoneState Done;

         CenterOnPointFSM();

         // Event Functions
         void Do() {m_pState->Do(*this);}
         void DoubleClick() {m_pState->DoubleClick(*this);}
         void MouseDown()   {m_pState->MouseDown(*this); }
         void MouseUp()     {m_pState->MouseUp(*this); }
         void MouseMove()   {m_pState->MouseMove(*this); }
         void EscKey()      {m_pState->EscKey(*this); }

         // State Accessor Functions
         void SetState(CenterOnPointFSMState& state) { m_pState = &state; }
         CenterOnPointFSMState& GetState() const { return *m_pState; }

      private:
         CenterOnPointFSMState* m_pState;
      };
   };
};
