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

#include <EAF/EAFExp.h>
#include <EAF/EAFTypes.h>
#include <EAF/ComponentObject.h>
#include <EAF/ComponentManager.h>
#include <EAF/EventSinkManager.h>
#include <EAF/EAFStrings.h>

#include <System/Logger.h>

#include <boost/circular_buffer.hpp>
#include <memory>
#include <vector>
#include <set>
#include <map>
#include <guiddef.h> // for CLSID
#include <WBFLTools.h> // For structured save and load

using IID = CLSID;

namespace WBFL
{
   namespace EAF
   {
      class Agent;

      // This class records checking information about an Agent
      class EAFCLASS AgentChecker
      {
      public:
         bool bRegisterInterfacesCalled = false;
         bool bInitCalled = false; // Was Agent::Init() called? If not, a subclassed Agent needs to call the parent class Init() method
         bool bResetCalled = false;
         bool bShutDownCalled = false;
         bool bDestroyed = false; // Was Agent::~Agent() called? If not, there is probably a circular reference preventing the agent from being destroyed
      };

      // This lets an outside user of the broker know
      // if it was destroyed. If it isn't destroyed when
      // expected, then there is a very high probability that
      // there is a circular reference that results in a memory leak
      class EAFCLASS BrokerChecker
      {
      public:
         BrokerChecker() = default;
         bool bBrokerDestroyed = false;

         std::map<std::_tstring,std::shared_ptr<AgentChecker>> AgentCheckers;
         void AddAgentChecker(std::shared_ptr<Agent> agent);

         void DumpState();
         bool CheckInitial();
         bool CheckFinal();
      };

      struct EAFCLASS AgentError
      {
         ComponentInfo component;
         std::_tstring reason;
      };
      using AgentErrors = std::vector<AgentError>;

      /// @brief Broker object in the Agent-Broker framework. The broker object
      /// provides a centralized method for getting the interfaces of the applications
      /// API.
      class EAFCLASS Broker : public std::enable_shared_from_this<Broker>
      {
      public:
         std::shared_ptr<BrokerChecker> m_Checker;

         /// @brief Used for the return type of the Load function.
         /// Note that the order of these enums is important. They
         /// are compared in the Load function.
         enum class LoadResult
         {
            Error, ///< An error occurred while loading the data
            Success, ///< Data was loaded successfully
            Modified ///< Data was loaded successfully, but it was modified
         };


      public:
         Broker(std::shared_ptr<BrokerChecker> checker);
         ~Broker();

         /// @brief Loads agents with runtime discovery and dynamic creation
         /// @param catid Category ID
         /// @return 
         std::pair<bool, AgentErrors> LoadAgents(const CATID& catid);
         std::pair<bool, AgentErrors> LoadExtensionAgents(const CATID& catid);

         /// @brief Loads individual agents
         /// @param clsid 
         /// @return 
         std::pair<bool, AgentError> LoadAgent(const CLSID& clsid);
         std::pair<bool, AgentError> LoadExtensionAgent(const CLSID& clsid);

         /// @brief Adds a previously created agent to the broker
         /// @param agent 
         /// @return 
         std::pair<bool, AgentError> AddAgent(std::shared_ptr<Agent> agent);
         std::pair<bool, AgentError> AddExtensionAgent(std::shared_ptr<Agent> agent);

         /// @brief Initializes all of the agents after they have been loaded
         /// @return 
         bool InitAgents();

         /// @brief Integrates the agents with the Application
         /// @param bIntegrateWithUI 
         /// @param bIntegrateWithReporting 
         /// @param bIntegrateWithGraphing 
         /// @param bIntegrateWithDocumentation 
         void Integrate(bool bIntegrateWithUI, bool bIntegrateWithReporting, bool bIntegrateWithGraphing, bool bIntegrateWithDocumentation);

         /// @brief Removes the agent integration
         void RemoveIntegration();

         /// @brief Indicates the initialization state of the broker and the agents
         /// @return 
         bool IsInitialized() const {
            return m_bAgentsInitialized;
         }

         /// @brief Called by the agent to register on of its interfaces
         /// Agents should use the REGISTER_INTERFACE macro.
         /// @param iid 
         /// @param agent 
         /// @return 
         bool RegisterInterface(const IID& iid, std::shared_ptr<Agent> agent);

         /// @brief Resets all agents to their original state by calling Reset() on all agents
         void Reset();

         /// @brief Call this method when you are done with the broker. Calls ShutDown() on all agents
         void ShutDown();

         /// @brief Gets an interface based on its interface identifier, IID
         /// @tparam T The interface type
         /// @param iid The interface identifier
         /// @return The interface if found, otherwise nullptr
         template <typename T>
            std::shared_ptr<T> GetInterface(const IID& iid)
         {
            auto sort_by_usage_frequency = [](const auto& item1, const auto& item2) {
               return *(item2.usage_count) < *(item1.usage_count);
               };

            // first check the most frequently used list
            InterfaceItem key;
            key.iid = iid;
            auto found(std::find(m_MostFrequentlyUsed.begin(), m_MostFrequentlyUsed.end(), key));
            if (found != m_MostFrequentlyUsed.end())
            {
               auto& item = *found;
               ASSERT(iid == item.iid);
               ASSERT(item.agent != nullptr);

               auto iface = std::dynamic_pointer_cast<T>(item.agent);
               if (iface == nullptr)
               {
                  std::_tstringstream os;
                  os << _T("The requested interface is not implemented on any agent: IID = ") << EAFStringFromIID(iid);
                  WBFL::System::Logger::Warning(os.str());
                  return nullptr;
               }

               // this IID is on the frequently used list
               // increment the usage count (updates in the main list of all interfaces as well)
               (*item.usage_count)++;

               // sort the MFU list based on usage count
               std::sort(m_MostFrequentlyUsed.begin(), m_MostFrequentlyUsed.end(), sort_by_usage_frequency);

               return iface;
            }

            // IID is not in the most frequently used list... search for it in the regular list of interfaces
            auto interface_found(m_Interfaces.find(key));
            if (interface_found == m_Interfaces.end())
            {
               // the interface wasn't found
               std::_tostringstream os;
               os << _T("The requested interface is not registered with the broker: IID = ") << EAFStringFromIID(iid);
               WBFL::System::Logger::Warning(os.str());
               return nullptr;
            }

            const auto& item = *(interface_found);
            auto iface = std::dynamic_pointer_cast<T>(item.agent);
            if (iface)
            {
               // update the usage count
               (*item.usage_count)++;

               // See if the usage count is high enough to be in the most frequently used list
               if (m_MostFrequentlyUsed.empty())
               {
                  m_MostFrequentlyUsed.push_front(item);
               }
               else
               {
                  const auto& least_used_item = m_MostFrequentlyUsed.back();

                  // a quick check to make sure sorting is ok
                  ASSERT(*(least_used_item.usage_count) <= *(m_MostFrequentlyUsed.front().usage_count));

                  if (*(least_used_item.usage_count) <= *(item.usage_count))
                  {
                     // Current interface item has been used more times then the least used interface item
                     // in the MFU list. Add the current item to the MFU list and re-sort. The least used
                     // item will drop out
                     m_MostFrequentlyUsed.push_front(item);

                     // sort the MFU list based on usage count
                     std::sort(m_MostFrequentlyUsed.begin(), m_MostFrequentlyUsed.end(), sort_by_usage_frequency);
                  }
               }
            }
            return iface;
         }

         /// @brief Registers a callback event sink. 
         /// Don't call this method directly, instead use the REGISTER_EVENT_SINK macro.
         /// @tparam T Callback interface type
         /// @param eventSink The event sink
         /// @return The event sink cookie
         template <typename T>
         IDType RegisterEventSink(std::weak_ptr<T> eventSink)
         {
            for (auto& [key,agent] : m_Agents)
            {
               auto reg = std::dynamic_pointer_cast<EventSinkManager<T>>(agent);
               if (reg)
                  return reg->RegisterEventSink(eventSink);
            }

            for (auto& [key, agent] : m_ExtensionAgents)
            {
               auto reg = std::dynamic_pointer_cast<EventSinkManager<T>>(agent);
               if (reg)
                  return reg->RegisterEventSink(eventSink);
            }

            return INVALID_ID;
         }

         /// @brief Unregisters a callback event sink.
         /// Don't call this method directly, instead use the UNREGISTER_EVENT_SINK macro
         /// @tparam T 
         /// @param id Event sink identifier cookie returned from RegisterEventSink
         /// @return True if successful
         template <typename T>
         bool UnregisterEventSink(IDType id)
         {
            for (auto& [key, agent] : m_Agents)
            {
               auto reg = std::dynamic_pointer_cast<EventSinkManager<T>>(agent);
               if (reg)
                  return reg->UnregisterEventSink(id);
            }

            for (auto& [key, agent] : m_ExtensionAgents)
            {
               auto reg = std::dynamic_pointer_cast<EventSinkManager<T>>(agent);
               if (reg)
                  return reg->UnregisterEventSink(id);
            }

            return false;
         }

         /// @brief Loads the Broker's data and the data for all agents implementing the IAgentPersist interface
         /// @param pStrLoad 
         /// @return 
         LoadResult Load(IStructuredLoad* pStrLoad);

         /// @brief Saves the Broker's data and the data for all agents implementing the IAgentPersist interface
         /// @param pStrSave 
         /// @return 
         bool Save(IStructuredSave* pStrSave);

         /// @brief Set this flag to true to save missing agent data. When missing agent data is saved,
         /// it is retained as a blob when Load is called and then saved when Save is called. If the data
         /// is not saved, it is discarded and lost forever
         /// @param bSet 
         void SetSaveMissingAgentDataFlag(bool bSet);
         bool GetSaveMissingAgentDataFlag();

         /// @brief Adds a map between object CLSIDs. Occasionally, an objects CLSID may be changed
         /// or an old object is replaced with a new one. When a CLSID is loaded from a file, the
         /// CLSID map is checked for an updated CLSID before attempting to create the object.
         /// @param oldCLSID 
         /// @param newCLSID 
         void AddMappedCLSID(LPCTSTR oldCLSID, LPCTSTR newCLSID);

         /// @brief Returns the number of agents (excluding extension agents)
         /// @return 
         IndexType GetAgentCount();

         /// @brief Returns an agent
         /// @param idx 
         /// @return 
         std::shared_ptr<Agent> GetAgent(IndexType idx);

         /// @brief Returns the number of extension agents
         /// @return 
         IndexType GetExtensionAgentCount();

         /// @brief Returns an extension agent
         /// @param idx 
         /// @return 
         std::shared_ptr<Agent> GetExtensionAgent(IndexType idx);

      private:
         struct EAFCLASS InterfaceItem
         {
            IID iid = CLSID_NULL; // ID of the interface
            std::shared_ptr<Agent> agent; // Agent that implements the interface
            std::shared_ptr<IndexType> usage_count = std::make_shared<IndexType>(0); // Number of times the interface has been requested

            InterfaceItem() = default;
            InterfaceItem(const IID& iid, std::shared_ptr<Agent> agent) : iid(iid), agent(agent) {}

            bool operator<(const InterfaceItem& other) const;
            bool operator==(const InterfaceItem& other) const;
         };

         using Interfaces = std::set<InterfaceItem>;
         Interfaces m_Interfaces;
         boost::circular_buffer<InterfaceItem> m_MostFrequentlyUsed;

         std::map<std::_tstring, std::_tstring> m_CLSIDMap;

         class Key : public std::pair<IndexType, CLSID>
         {
         public:
            Key(IndexType idx, CLSID clsid) : std::pair<IndexType, CLSID>(idx, clsid) {}
            bool operator<(const Key& key) const;
         };

         // Broker owns the Agents because it creates them in LoadAgents.
         // However, Agent has a pointer to Broker so that it can request
         // interfaces from other agents. This creates a circular reference
         // and agents and broker will never be deleted. The ShutDown()
         // method calls Agent::SetBroker(nullptr) to break the circular reference.
         using Agents = std::map<Key, std::shared_ptr<Agent>>;
         Agents m_Agents;
         Agents m_ExtensionAgents;


         bool m_bAgentsInitialized = false; // true if the agents where initialized

         bool m_bSaveMissingAgentData = true;
         std::vector<std::_tstring> m_MissingAgentData; // holds the entire unit data block, for agent data that is in the file, but the agent can't be created

         LoadResult LoadOldFormat(IStructuredLoad* strLoad);
         void ClearAgents();

         std::pair<bool, AgentErrors> LoadAgents(const CATID& catid, Agents& agents, bool bRequired = true);
         std::pair<bool, AgentError> LoadAgent(const CLSID& clsid, Agents& agents, bool bRequired = true);
         std::pair<bool, AgentError> AddAgent(std::shared_ptr<Agent> pAgent, Agents& agents);
         bool InitAgents(Agents::iterator begin, Agents::iterator end);
         bool SaveAgentData(IStructuredSave* pStrSave, Agents::iterator begin, Agents::iterator end);
         std::shared_ptr<Agent> FindAgent(const CLSID& clsid);

         bool m_bIntegrateWithUI = false;
         bool m_bIntegrateWithReporting = false;
         bool m_bIntegrateWithGraphing = false;

         std::_tstring TranslateCLSID(LPCTSTR strCLSID);


#if defined _DEBUG
         void ListInterfaceUsage();
#endif
      };
   };
};
