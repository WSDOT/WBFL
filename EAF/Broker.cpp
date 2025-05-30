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

#include "stdafx.h"
#include <EAF\Broker.h>
#include <EAF\Agent.h>
#include <EAF\ComponentManager.h>
#include <EAF\EAFUtilities.h>

DIAG_DEFINE_GROUP(Broker, DIAG_GROUP_ENABLE, 0);

using namespace WBFL::EAF;

template <class T>
HRESULT Integrate(bool bIntegrating, bool bIntegrateWithUI, bool bIntegrateWithReporting, bool bIntegrateWithGraphing, bool bIntegrateWithDocumentation,
   typename T begin, typename T end)
{
   while (begin != end)
   {
      auto agent = (*begin).second;
      if (bIntegrateWithUI)
      {
         auto pUI = std::dynamic_pointer_cast<WBFL::EAF::IAgentUIIntegration>(agent);
         if (pUI)
         {
            std::_tstringstream os;
            os << _T("Agent: ") << agent->GetName() << _T(" - integrating with UI");
            WBFL::System::Logger::Debug(os.str());
            pUI->IntegrateWithUI(bIntegrating);
         }
      }

      if (bIntegrateWithReporting)
      {
         auto pUI = std::dynamic_pointer_cast<WBFL::EAF::IAgentReportingIntegration>(agent);
         if (pUI)
         {
            std::_tstringstream os;
            os << _T("Agent: ") << agent->GetName() << _T(" - integrating with Reporting");
            WBFL::System::Logger::Debug(os.str());
            pUI->IntegrateWithReporting(bIntegrating);
         }
      }

      if (bIntegrateWithGraphing)
      {
         auto pUI = std::dynamic_pointer_cast<WBFL::EAF::IAgentGraphingIntegration>(agent);
         if (pUI)
         {
            std::_tstringstream os;
            os << _T("Agent: ") << agent->GetName() << _T(" - integrating with Graphing");
            WBFL::System::Logger::Debug(os.str());
            pUI->IntegrateWithGraphing(bIntegrating);
         }
      }

      if (bIntegrateWithDocumentation && bIntegrating)
      {
         auto pUI = std::dynamic_pointer_cast<WBFL::EAF::IAgentDocumentationIntegration>(agent);
         if (pUI)
         {
            std::_tstringstream os;
            os << _T("Agent: ") << agent->GetName() << _T(" - integrating with Documentation");
            WBFL::System::Logger::Debug(os.str());
            pUI->LoadDocumentationMap();
         }
      }

      begin++;
   }

   return S_OK;
}

bool Broker::InterfaceItem::operator<(const InterfaceItem& other) const { return iid < other.iid; }
bool Broker::InterfaceItem::operator==(const InterfaceItem& other) const { return iid == other.iid ? true : false; }

bool Broker::Key::operator<(const Key& key) const
{
   if (first == key.first)
      return second < key.second;
   else if (first < key.first)
      return true;
   else
      return false;
}

void BrokerChecker::AddAgentChecker(std::shared_ptr<Agent> agent)
{
   std::_tstringstream os;
   os << _T("Adding Agent: ") << agent->GetName();
   WBFL::System::Logger::Debug(os.str());

   auto agent_checker = std::make_shared<AgentChecker>();
   agent->SetChecker(agent_checker);
   auto result = AgentCheckers.insert({ agent->GetName(),agent_checker });
   ASSERT(result.second);
   ASSERT(agent->GetChecker() == result.first->second);
}

void BrokerChecker::DumpState()
{
   for (auto& agent_checker : AgentCheckers)
   {
      WATCH(_T("Agent: ") << agent_checker.first);
      WATCH(_T("   RegisterInterfaces: ") << (agent_checker.second->bRegisterInterfacesCalled ? _T("true") : _T("false")));
      WATCH(_T("   Init: ") << (agent_checker.second->bInitCalled ? _T("true") : _T("false")));
      WATCH(_T("   Reset: ") << (agent_checker.second->bResetCalled ? _T("true") : _T("false")));
      WATCH(_T("   ShutDown: ") << (agent_checker.second->bShutDownCalled ? _T("true") : _T("false")));
      WATCH(_T("   Destroyed: ") << (agent_checker.second->bDestroyed ? _T("true") : _T("false")));
   }
}

bool BrokerChecker::CheckInitial()
{
   bool bResult = true;
   DumpState();

   for (auto& agent_checker : AgentCheckers)
   {
      bResult &= agent_checker.second->bRegisterInterfacesCalled;
      bResult &= agent_checker.second->bInitCalled;
   }

   return bResult;
}

bool BrokerChecker::CheckFinal()
{
   bool bResult = true;
   WATCH(_T("Broker Destroyed: ") << (bBrokerDestroyed ? _T("true") : _T("false")));
   bResult &= bBrokerDestroyed;

   DumpState();

   for (auto& agent_checker : AgentCheckers)
   {
      bResult &= agent_checker.second->bRegisterInterfacesCalled;
      bResult &= agent_checker.second->bInitCalled;
      bResult &= agent_checker.second->bResetCalled;
      bResult &= agent_checker.second->bShutDownCalled;
      bResult &= agent_checker.second->bDestroyed;
   }

   return bResult;
}


Broker::Broker(std::shared_ptr<BrokerChecker> checker) : 
   m_Checker(checker), m_MostFrequentlyUsed(10)
{
}

Broker::~Broker()
{
   if (m_Checker)
      m_Checker->bBrokerDestroyed = true;
}

void Broker::Reset()
{
   WBFL::System::Logger::Debug(_T("Resetting Broker"));

   if (!m_bAgentsInitialized)
      return; // do nothing if the agents weren't initialized


   // reset in reverse order (Extension Agents, then regular Agents)
   for (auto& [key,agent] : m_ExtensionAgents)
   {
      std::_tstringstream os;
      os << _T("Resetting extension agent: ") << agent->GetName();
      WBFL::System::Logger::Debug(os.str());
      agent->Reset();
   }

   for (auto& [key, agent] : m_Agents)
   {
      std::_tstringstream os;
      os << _T("Resetting agent: ") << agent->GetName();
      WBFL::System::Logger::Debug(os.str());
      agent->Reset();
   }

   m_bAgentsInitialized = false;
}

void Broker::ShutDown()
{
   WBFL::System::Logger::Debug(_T("Shutting down broker"));

   Reset();

#if defined _DEBUG
   ListInterfaceUsage();
#endif // _DEBUG

   m_Interfaces.clear();
   m_MostFrequentlyUsed.clear();

   m_bAgentsInitialized = true;

   for (auto& [key, agent] : m_ExtensionAgents)
   {
      std::_tstringstream os;
      os << _T("Shutting down extension agent: ") << agent->GetName();
      WBFL::System::Logger::Debug(os.str());

      agent->ShutDown();

      // This breaks the circular reference between Broker and Agent 
      agent->SetBroker(nullptr);
   }

   for (auto& [key, agent] : m_Agents)
   {
      std::_tstringstream os;
      os << _T("Shutting down agent: ") << agent->GetName();
      WBFL::System::Logger::Debug(os.str());

      agent->ShutDown();

      // This breaks the circular reference between Broker and Agent 
      agent->SetBroker(nullptr);
   }

   ClearAgents();

   m_bAgentsInitialized = false;
}

std::pair<bool, AgentErrors> Broker::LoadAgents(const CATID& catid)
{
   std::_tstringstream os;
   os << _T("Loading agents for CATID : ") << EAFStringFromCATID(catid);
   WBFL::System::Logger::Debug(os.str());

   return LoadAgents(catid, m_Agents);
}

std::pair<bool, AgentErrors> Broker::LoadExtensionAgents(const CATID& catid)
{
   std::_tstringstream os;
   os << _T("Loading extension agents for CATID : ") << EAFStringFromCATID(catid);
   WBFL::System::Logger::Debug(os.str());

   return LoadAgents(catid, m_ExtensionAgents ,false);
}

std::pair<bool, AgentError> Broker::LoadAgent(const CLSID& clsid)
{
   std::_tstringstream os;
   os << _T("Loading agents for CLSID : ") << EAFStringFromCLSID(clsid);
   WBFL::System::Logger::Debug(os.str());

   return LoadAgent(clsid, m_Agents);
}

std::pair<bool, AgentError> Broker::LoadExtensionAgent(const CLSID& clsid)
{
   std::_tstringstream os;
   os << _T("Loading extension agents for CLSID : ") << EAFStringFromCLSID(clsid);
   WBFL::System::Logger::Debug(os.str());

   return LoadAgent(clsid, m_ExtensionAgents, false);
}

std::pair<bool, AgentError> Broker::AddAgent(std::shared_ptr<Agent> agent)
{
   std::_tstringstream os;
   os << _T("Adding agent : ") << agent->GetName();
   WBFL::System::Logger::Debug(os.str());

   return AddAgent(agent, m_Agents);
}

std::pair<bool, AgentError> Broker::AddExtensionAgent(std::shared_ptr<Agent> agent)
{
   std::_tstringstream os;
   os << _T("Adding extension agent : ") << agent->GetName();
   WBFL::System::Logger::Debug(os.str());

   return AddAgent(agent, m_ExtensionAgents);
}

bool Broker::RegisterInterface(const IID& iid, std::shared_ptr<Agent> agent)
{
   std::_tstringstream os;
   os << _T("Registering interface Agent: ") << agent->GetName() << _T(" IID: ") << EAFStringFromIID(iid);
   WBFL::System::Logger::Debug(os.str());

   InterfaceItem item(iid, agent);
   auto result = m_Interfaces.insert(item);
   CHECK(result.second); // if this fires, the interface was already registered
   return result.second;
}

bool Broker::InitAgents()
{
   WBFL::System::Logger::Debug(_T("Initalizing agents"));

   if (!InitAgents(m_Agents.begin(), m_Agents.end()))
      return false;

   m_bAgentsInitialized = false; // InitAgents sets this to true, reset it to false so the extension agents get initialized
   
   WBFL::System::Logger::Debug(_T("Initalizing extension agents"));
   if (!InitAgents(m_ExtensionAgents.begin(), m_ExtensionAgents.end()))
      return false;

   CHECK(m_bAgentsInitialized == true);

   return true;
}

void Broker::Integrate(bool bIntegrateWithUI, bool bIntegrateWithReporting, bool bIntegrateWithGraphing, bool bIntegrateWithDocumentation)
{
   m_bIntegrateWithUI = bIntegrateWithUI;
   m_bIntegrateWithReporting = bIntegrateWithReporting;
   m_bIntegrateWithGraphing = bIntegrateWithGraphing;

   ::Integrate(true, m_bIntegrateWithUI, m_bIntegrateWithReporting, m_bIntegrateWithGraphing, bIntegrateWithDocumentation, m_Agents.begin(), m_Agents.end());
   ::Integrate(true, m_bIntegrateWithUI, m_bIntegrateWithReporting, m_bIntegrateWithGraphing, bIntegrateWithDocumentation, m_ExtensionAgents.begin(), m_ExtensionAgents.end());
}

void Broker::RemoveIntegration()
{
   ::Integrate(false, m_bIntegrateWithUI, m_bIntegrateWithReporting, m_bIntegrateWithGraphing, false, m_ExtensionAgents.rbegin(), m_ExtensionAgents.rend());
   ::Integrate(false, m_bIntegrateWithUI, m_bIntegrateWithReporting, m_bIntegrateWithGraphing, false, m_Agents.rbegin(), m_Agents.rend());
}

WBFL::EAF::Broker::LoadResult Broker::Load(IStructuredLoad* pStrLoad)
{
   HRESULT hr = pStrLoad->BeginUnit(_T("Broker"));
   if (FAILED(hr))
   {
      // the data isn't saved in the current format
      // it was probably created using an old implementation of Broker
      return LoadOldFormat(pStrLoad);
   }

   LoadResult max_result = WBFL::EAF::Broker::LoadResult::Error;

   // until we run out of "Agent" units
   while (SUCCEEDED(pStrLoad->BeginUnit(_T("Agent"))))
   {
      // get CLSID of the agent
      CComVariant varCLSID;
      varCLSID.vt = VT_BSTR;
      HRESULT hr = pStrLoad->get_Property(_T("CLSID"), &varCLSID);
      if (FAILED(hr)) return LoadResult::Error;

      CComBSTR bstrCLSID(varCLSID.bstrVal);
      bstrCLSID.ToUpper();
      auto strCLSID = TranslateCLSID(CString(bstrCLSID));

      CLSID clsid;
      hr = ::CLSIDFromString(strCLSID.c_str(), &clsid);
      if (FAILED(hr)) return LoadResult::Error;

      // get the agent
      auto agent = FindAgent(clsid);
      if (agent)
      {
         auto persist = std::dynamic_pointer_cast<IAgentPersist>(agent);
         if (persist)
         {
            auto load_result = persist->Load(pStrLoad);
            if (max_result < load_result)
               max_result = load_result;

            if ( load_result == LoadResult::Error)
               return load_result;
         }
         else
         {
            // agent previously saved data, but it no longer implements the IAgentPersist interface?
         }
      }
      else
      {
         // agent not found... 
         // this could be because it is a 3rd party agent and it isn't installed
         // skip to the next "Agent" unit by loading the entire unit of data
         CComBSTR bstrRawUnit;
         hr = pStrLoad->LoadRawUnit(&bstrRawUnit);
         if (FAILED(hr)) return LoadResult::Error;

         m_MissingAgentData.push_back(OLE2T(bstrRawUnit));
      }

      pStrLoad->EndUnit(); // end of "Agent" unit
   };

   pStrLoad->EndUnit(); // Broker
   
   return max_result;
}

bool Broker::Save(IStructuredSave* pStrSave)
{
   pStrSave->BeginUnit(_T("Broker"), 1.0);
   if (!SaveAgentData(pStrSave, m_Agents.begin(), m_Agents.end()))
      return false;

   if (!SaveAgentData(pStrSave, m_ExtensionAgents.begin(), m_ExtensionAgents.end()))
      return false;

   if (m_bSaveMissingAgentData)
   {
      for (const auto& data : m_MissingAgentData)
      {
         if (!pStrSave->SaveRawUnit(data.c_str()))
            return false;
      }
   }

   pStrSave->EndUnit(); // Broker
   return true;
}

void Broker::SetSaveMissingAgentDataFlag(bool bSet)
{
   m_bSaveMissingAgentData = bSet;
}

bool Broker::GetSaveMissingAgentDataFlag()
{
   return m_bSaveMissingAgentData;
}

void Broker::AddMappedCLSID(LPCTSTR oldCLSID, LPCTSTR newCLSID)
{
   m_CLSIDMap.insert(std::make_pair(oldCLSID, newCLSID));
}

IndexType Broker::GetAgentCount()
{
   return (IndexType)m_Agents.size();
}

std::shared_ptr<Agent> Broker::GetAgent(IndexType idx)
{
   IndexType i = 0;
   auto iter = m_Agents.begin();
   auto end = m_Agents.end();
   for (; iter != end && i != idx; iter++, i++)
   {
   }

   return iter->second;
}

IndexType Broker::GetExtensionAgentCount()
{
   return (IndexType)m_ExtensionAgents.size();
}

std::shared_ptr<Agent> Broker::GetExtensionAgent(IndexType idx)
{
   IndexType i = 0;
   auto iter = m_ExtensionAgents.begin();
   auto end = m_ExtensionAgents.end();
   for (; iter != end && i != idx; iter++, i++)
   {
   }

   return iter->second;
}

Broker::LoadResult Broker::LoadOldFormat(IStructuredLoad* strLoad)
{
   LoadResult result = LoadResult::Error;

   Agents::iterator i(m_Agents.begin());
   Agents::iterator i_end(m_Agents.end());
   for (; i != i_end; i++)
   {
      auto pAgent = (*i).second;
      auto pPersist = std::dynamic_pointer_cast<IAgentPersist>(pAgent);
      if (pPersist)
      {
         result = pPersist->Load(strLoad);
         // When we had the old data format there was only one agent
         // that persisted data. Now we have extension agents that can also 
         // implement the IAgentPersist interface and will get called if they are loaded.
         // Since this is an old format file, there is no way they will
         // have data in the file....
         //
         // Load from the first agent supporting IAgentPersist and break out of the loop
         break;
      }
   }

   return result;
}

void Broker::ClearAgents()
{
   m_ExtensionAgents.clear();
   m_Agents.clear();
}

std::pair<bool, AgentErrors> Broker::LoadAgents(const CATID& catid, Agents& agents, bool bRequired)
{
   if (m_bAgentsInitialized)
   {
      USES_CONVERSION;
      std::runtime_error e("Broker::LoadAgents - loading agents after initialization");
      WBFL::System::Logger::Error(A2T(e.what()));
      ASSERT(!m_bAgentsInitialized); // Can't load any more agents after InitAgent has been called
      throw e;
   }

   std::vector<AgentError> errors;
   auto components = WBFL::EAF::ComponentManager::GetInstance().GetComponents(catid);
   for (auto& component : components)
   {
      auto agent = WBFL::EAF::ComponentManager::GetInstance().CreateComponent<Agent>(component);
      if (agent)
      {
         IndexType priority_index = 999;
         auto priority = std::dynamic_pointer_cast<IAgentPriority>(agent);
         if (priority)
            priority_index = priority->GetPriority();

         auto result = agents.insert(std::make_pair(Key(priority_index, component.clsid), agent));
         if (result.second == false)
         {
            std::_tostringstream os;
            os << _T("Loading agent ") << agent->GetName() << _T(" multiple times");
            WBFL::System::Logger::Error(os.str());
            errors.push_back({ component, os.str()});
            
            if ( bRequired ) return { false, errors };
         }

         if (!agent->SetBroker(std::dynamic_pointer_cast<Broker>(shared_from_this())))
         {
            std::_tostringstream os;
            os << _T("Error setting broker on agent: ") << agent->GetName();
            WBFL::System::Logger::Error(os.str());
            errors.push_back({ component,os.str()});

            if (bRequired) return { false, errors };
         }

         if (!agent->RegisterInterfaces())
         {
            std::_tostringstream os;
            os << _T("Error registering interfaces: Agent ") << agent->GetName();
            WBFL::System::Logger::Error(os.str());
            errors.push_back({ component,os.str()});

            if (bRequired) return { false, errors };
         }
      }
      else
      {
         WBFL::System::Logger::Error(_T("Could not create agent"));
         errors.push_back({ component,_T("Broker::LoadAgents - Could not create agent") });

         if (bRequired) return { false, errors };
      }
   }

   return { true,errors };
}

std::pair<bool, AgentError> Broker::LoadAgent(const CLSID& clsid, Agents& agents, bool bRequired)
{
   if (m_bAgentsInitialized)
   {
      USES_CONVERSION;
      std::runtime_error e("Broker::LoadAgents - loading agents after initialization");
      WBFL::System::Logger::Error(A2T(e.what()));
      ASSERT(!m_bAgentsInitialized); // Can't load any more agents after InitAgent has been called
      throw e;
   }

   auto agent = WBFL::EAF::ComponentManager::GetInstance().CreateComponent<Agent>(clsid);
   if (agent)
   {
      IndexType priority_index = 999;
      auto priority = std::dynamic_pointer_cast<IAgentPriority>(agent);
      if (priority)
         priority_index = priority->GetPriority();

      const auto& component = WBFL::EAF::ComponentManager::GetInstance().GetComponent(clsid);
      auto result = agents.insert(std::make_pair(Key(priority_index, clsid), agent));
      if (result.second == false && bRequired)
      {
         std::_tostringstream os;
         os << _T("Loading agent ") << agent->GetName() << _T(" multiple times");
         WBFL::System::Logger::Error(os.str());

         return { false, { component,os.str()}};
      }

      if (!agent->SetBroker(std::dynamic_pointer_cast<Broker>(shared_from_this())) && bRequired)
      {
         std::_tostringstream os;
         os << _T("Error setting broker on agent: ") << agent->GetName();
         WBFL::System::Logger::Error(os.str());
         return { false, { component, os.str()}};
      }

      if (!agent->RegisterInterfaces() && bRequired)
      {
         std::_tostringstream os;
         os << _T("Error registering interfaces: Agent ") << agent->GetName();
         WBFL::System::Logger::Error(os.str());
         return { false, { component,os.str()}};
      }
   }
   else
   {
      WBFL::System::Logger::Error(_T("Could not create agent"));
      return { false,{ComponentInfo(),_T("Broker::LoadAgent - Could not create agent")} };
   }

   return { true,{ComponentInfo(),_T("")} };
}

std::pair<bool, AgentError> Broker::AddAgent(std::shared_ptr<Agent> agent, Agents& agents)
{
   if (m_bAgentsInitialized)
   {
      USES_CONVERSION;
      std::runtime_error e("Broker::LoadAgents - loading agents after initialization");
      WBFL::System::Logger::Error(A2T(e.what()));
      ASSERT(!m_bAgentsInitialized); // Can't load any more agents after InitAgent has been called
      throw e;
   }

   ComponentInfo component;
   component.name = agent->GetName();
   component.clsid = agent->GetCLSID();

   if (!agent->SetBroker(std::dynamic_pointer_cast<Broker>(shared_from_this())))
   {
      std::_tostringstream os;
      os << _T("Error setting broker on agent: ") << agent->GetName();
      WBFL::System::Logger::Error(os.str());
      return { false,{component,os.str()}};
   }

   if (!agent->RegisterInterfaces())
   {
      std::_tostringstream os;
      os << _T("Error registering interfaces: Agent ") << agent->GetName();
      WBFL::System::Logger::Error(os.str());
      return { false,{component,os.str()}};
   }

   IndexType priority_index = 999;
   auto priority = std::dynamic_pointer_cast<IAgentPriority>(agent);
   if (priority)
      priority_index = priority->GetPriority();

   auto result = agents.insert(std::make_pair(Key(priority_index, agent->GetCLSID()), agent));
   if (result.second == false)
   {
      std::_tostringstream os;
      os << _T("Loading agent ") << agent->GetName() << _T(" multiple times");
      WBFL::System::Logger::Error(os.str());
      return { false,{component,os.str()}};
   }

   return { true, {component,_T("")} };
}

bool Broker::InitAgents(Agents::iterator begin, Agents::iterator end)
{
   if (m_bAgentsInitialized)
   {
      USES_CONVERSION;
      std::runtime_error e("Broker::LoadAgents - loading agents after initialization");
      WBFL::System::Logger::Error(A2T(e.what()));
      ASSERT(!m_bAgentsInitialized); // Can't load any more agents after InitAgent has been called
      throw e;
   }

   while (begin != end)
   {
      auto agent = (*begin).second;
      if (!agent->Init())
      {
         ASSERT(false);
         return false;
      }
      begin++;
   }

   m_bAgentsInitialized = true;
   return true;
}

bool Broker::SaveAgentData(IStructuredSave* pStrSave, Agents::iterator begin, Agents::iterator end)
{
   while (begin != end)
   {
      auto [key, agent](*begin);
      auto persist = std::dynamic_pointer_cast<IAgentPersist>(agent);
      if (persist)
      {
         // create a unit around each agent's data
         pStrSave->BeginUnit(_T("Agent"), 1.0);

         CString strCLSID(EAFStringFromCLSID(key.second).c_str());

         // capture the class id of the agent
         pStrSave->put_Property(_T("CLSID"), CComVariant(strCLSID));

         if (!persist->Save(pStrSave)) // agent to save its own data
            return false;

         pStrSave->EndUnit(); // end of "Agent" unit
      }

      begin++;
   }

   return true;
}

std::shared_ptr<Agent> Broker::FindAgent(const CLSID& clsid)
{
   for (auto& [key, agent] : m_Agents)
   {
      if (key.second == clsid)
      {
         return agent;
      }
   }

   for (auto& [key, agent] : m_ExtensionAgents)
   {
      if (key.second == clsid)
      {
         return agent;
      }
   }

   return nullptr;
}

std::_tstring Broker::TranslateCLSID(LPCTSTR strCLSID)
{
   auto found = m_CLSIDMap.find(strCLSID);
   if (found == m_CLSIDMap.end())
      return strCLSID;

   return found->second;
}


#if defined _DEBUG
void Broker::ListInterfaceUsage()
{
   USES_CONVERSION;
   WATCHX(Broker, 0, _T("Most frequently used interfaces"));
   for(auto& item : m_MostFrequentlyUsed)
   {
      OLECHAR szGUID[39];
      ::StringFromGUID2(item.iid, szGUID, 39);
      WATCHX(Broker, 0, item.agent->GetName() << _T(": IID = ") << OLE2T(szGUID) << _T(" Usage Count = ") << (*item.usage_count));

   }

   WATCHX(Broker, 0, _T(""));
   WATCHX(Broker, 0, _T("Total interface usage count"));

   // fill up a temporary vector so we can sort and report by CLSID
   std::vector<InterfaceItem> interfaces;
   for(auto& item : m_Interfaces)
   {
      interfaces.push_back(item);
   }

   std::sort(interfaces.begin(), interfaces.end(), [](const auto& a, const auto& b) {return a.agent->GetCLSID() < b.agent->GetCLSID(); });

   IndexType count = 0;
   for(auto& item : interfaces)
   {
      OLECHAR szGUID[39];
      ::StringFromGUID2(item.iid, szGUID, 39);

      WATCHX(Broker, 0, item.agent->GetName() << _T(" IID = ") << OLE2T(szGUID) << _T(" Usage Count = ") << (*item.usage_count));

      count += (*item.usage_count);
   }
   WATCHX(Broker, 0, _T("Total count = ") << count);
}
#endif // _DEBUG
