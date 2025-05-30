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

#pragma once

#include <EAF\EAFExp.h>
#include <EAF\ComponentObject.h>
#include <EAF\EAFStatusCenter.h>
#include <EAF\Broker.h>
#include <EAF\EAFTypes.h>
#include <memory>

interface IStructuredLoad;
interface IStructuredSave;

namespace WBFL
{
   namespace EAF
   {
      /// @brief Base class for Agent objects in the Agent-Broker framework
      class EAFCLASS Agent : public ComponentObject
      {
      public:
         Agent() = default;
         virtual ~Agent();
         
         /// @brief Associates a broker with the agent
         /// Even though this is a strong reference, which creates a circular dependency between the Agent and Broker,
         /// Broker::ShutDown calls SetBroker(nullptr) breaking the circular dependency
         /// @param broker 
         virtual bool SetBroker(std::shared_ptr<Broker> broker);

         /// @brief Called by the framework to inject a checking object used at application shutdown to
         /// to verify the broker and agents have been properly destroyed.
         /// @param checker 
         void SetChecker(std::shared_ptr<AgentChecker> checker);
         std::shared_ptr<AgentChecker> GetChecker() const;

         /// @brief Returns the agent's name
         /// @return 
         virtual std::_tstring GetName() const = 0;
         
         /// @brief Called by Broker to register the Agent's callback interfaces.
         /// Implementations will use the REGISTER_INTERFACE macro for each interface to be exposed via the broker
         /// @return True if successful
         virtual bool RegisterInterfaces();

         /// @brief Called by the framework for agent initialization. Initialization occurs after all agents are loaded
         /// and their interfaces are registered
         /// @return True if successful
         virtual bool Init();

         /// @brief Called by the framework indicating the agent should reset itself to its initial state
         /// @return True if successful
         virtual bool Reset();

         /// @brief Called by the framework before the agent is destroyed. The agent should do any final cleanup in this method
         /// @return True if successful
         virtual bool ShutDown();

         /// @brief Returns the agent's CLSID
         /// @return 
         virtual CLSID GetCLSID() const = 0;
         
         protected:
            std::shared_ptr<WBFL::EAF::Broker> m_pBroker;

         private:
            std::shared_ptr<AgentChecker> m_AgentChecker;
      };

      /// @brief Interface to be implemented by agents that need to establish a priority position
      /// in the Broker's search order.
      class EAFCLASS IAgentPriority
      {
      public:
         /// @brief Returns a priority number which affects the agent search order within the Broker.
         /// Agents with lower priority numbers occur before Agents with higher numbers.
         /// Agents not implementing this interface are assumed to have a priority of 999.
         /// @return 
         virtual IndexType GetPriority() const = 0;
      };

      /// @brief Interface to be implemented by agents that persist data
      class EAFCLASS IAgentPersist
      {
      public:
         /// @brief Called to load the agent's data
         /// @param pStrLoad 
         /// @return 
         virtual WBFL::EAF::Broker::LoadResult Load(IStructuredLoad* pStrLoad) = 0;

         /// @brief Called to save the agent's data
         /// @param pStrSave 
         /// @return 
         virtual bool Save(IStructuredSave* pStrSave) = 0;
      };

      /// @brief Interface to be implemented by agents that integrate with the application's user interface
      class EAFCLASS IAgentUIIntegration
      {
      public:
         /// @brief Called by the framework to allow the agent to integrate or remove its user interface elements
         /// @param bIntegrate True when integrating. False when the agent needs to remove its interface elements
         /// @return 
         virtual bool IntegrateWithUI(bool bIntegrate) = 0;
      };

      /// @brief Interface to be implemented by agents that integrate with the application's reporting system
      class EAFCLASS IAgentReportingIntegration
      {
      public:
         virtual bool IntegrateWithReporting(bool bIntegrate) = 0;
      };

      /// @brief Interface to be implemented by agents that integrate with the application's graphing system
      class EAFCLASS IAgentGraphingIntegration
      {
      public:
         virtual bool IntegrateWithGraphing(bool bIntegrate) = 0;
      };

      /// @brief Interface to be implemented by agents that integrate with the application's documentation system
      class EAFCLASS IAgentDocumentationIntegration
      {
      public:
         /// @brief Returns the documentation set name
         virtual CString GetDocumentationSetName() const = 0;

         /// @brief Loads the documentation map
         virtual bool LoadDocumentationMap() = 0;

         /// @brief Gets the URL of the documentation for its ID
         /// @param nHID Help topic identifier
         /// @return Result information and URL
         virtual std::pair<WBFL::EAF::HelpResult,CString> GetDocumentLocation(UINT nHID) const = 0;
      };
   };
};


// EAF_DECLARE_AGENT_DATA - add this macro to your Agent implementation class
// EAF_AGENT_INIT - add this macro to your Agent::Init method

/// @brief declares the required data components for an agent
/// Put this macro in the private data area of the agent class declaration 
#define EAF_DECLARE_AGENT_DATA StatusGroupIDType m_StatusGroupID

/// @brief Agent initialization macro. Add this macro to your implementation of the IAgent::Init method
#define EAF_AGENT_INIT Agent::Init(); GET_IFACE(IEAFStatusCenter,_pStatusCenter_); m_StatusGroupID = _pStatusCenter_->CreateStatusGroupID()

/// @brief Agent interface registration macro. Add this macro to your implementation of IAgent::RegisterInterfaces method
#define EAF_AGENT_REGISTER_INTERFACES Agent::RegisterInterfaces()

/// @brief Agent reset macro. Add this macro to your implementation of IAgent::Reset method
#define EAF_AGENT_RESET Agent::Reset()

/// @brief Agent showdown macro. Add this macro to your implementation of IAgent::ShutDown method
#define EAF_AGENT_SHUTDOWN Agent::ShutDown()
