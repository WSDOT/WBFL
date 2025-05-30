///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

// EAFDocProxyAgent.cpp: implementation of the CEAFDocProxyAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF/Agent.h>
#include "AgentTools.h"

using namespace WBFL::EAF;

Agent::~Agent()
{
   m_AgentChecker->bDestroyed = true;
}

bool Agent::SetBroker(std::shared_ptr<Broker> broker)
{
   std::_tostringstream os;
   os << _T("Setting broker for agent ") << GetName();
   WBFL::System::Logger::Debug(os.str());

   m_pBroker = broker;
   if (m_pBroker)
   {
      m_pBroker->m_Checker->AddAgentChecker(std::dynamic_pointer_cast<Agent>(shared_from_this()));
   }
   return true;
}

void Agent::SetChecker(std::shared_ptr<AgentChecker> checker)
{
   ASSERT(m_AgentChecker == nullptr);
   m_AgentChecker = checker;
}

std::shared_ptr<AgentChecker> Agent::GetChecker() const
{
   return m_AgentChecker;
}

bool Agent::Init()
{
   std::_tostringstream os;
   os << _T("Initializing agent ") << GetName();
   WBFL::System::Logger::Debug(os.str());

   m_AgentChecker->bInitCalled = true;

   return true;
}

bool Agent::RegisterInterfaces()
{
   std::_tostringstream os;
   os << _T("Registering interfaces for agent ") << GetName();
   WBFL::System::Logger::Debug(os.str());

   m_AgentChecker->bRegisterInterfacesCalled = true;
   return true;
}

bool Agent::Reset() 
{ 
   m_AgentChecker->bResetCalled = true;

   return true; 
}

bool Agent::ShutDown()
{ 
   m_AgentChecker->bShutDownCalled = true;
   return true;
}
