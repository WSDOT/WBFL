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

// EAFPluginManager.h: interface for the CEAFPluginManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\EAFExp.h>
#include <EAF\EAFSplashScreen.h>
#include <EAF\AcceleratorTable.h>
#include <EAF\EAFUtilities.h>
#include <EAF/EAFStrings.h>
#include <EAF\PluginApp.h>
#include <atlcomcli.h>

#include <comcat.h>
#include <map>

// Generic template class for managing plugins

#include <boost/dll/import.hpp>
#include "ComponentObject.h"
#include "ComponentManager.h"
namespace WBFL
{
   namespace EAF
   {
      template <typename T, typename Parent>
      class PluginManagerBase
      {
      public:
         PluginManagerBase() { m_CATID = CLSID_NULL; }
         PluginManagerBase(const CATID& catid) { m_CATID = catid; }
         virtual ~PluginManagerBase() {};
         void SetCATID(const CATID& catid) { m_CATID = catid; }
         void SetParent(typename Parent* parent)
         {
            m_pParent = parent;
            m_PluginAcceleratorTable->Init(m_pParent->GetPluginCommandManager());
         }
         typename Parent* GetParent() { return m_pParent; }

         std::shared_ptr<WBFL::EAF::AcceleratorTable> GetAcceleratorTable()
         {
            return m_PluginAcceleratorTable;
         }

         bool AddPlugin(const CLSID& clsid, typename std::shared_ptr<T> pPlugin)
         {
            if (pPlugin == nullptr) return false;
            auto [iter, bSuccess] = m_Plugins.insert( std::make_pair(clsid,pPlugin));
            if (bSuccess)
            {
               // plugin was successfully added to the container
               if (!pPlugin->Init(m_pParent))
               {
                  // plugin did not initialize properly, remove it from the container
                  m_Plugins.erase(iter);
                  return false;
               }
               return true; // plug-in added and initialized successfully
            }
            return false; // plug-in not added to container
         }

         bool LoadPlugins(bool bAlwaysAttemptToLoad = false)
         {
            auto* pApp = AfxGetApp();
            auto components = ComponentManager::GetInstance().GetComponents(m_CATID);
            for (const auto& component : components)
            {
               CString strCLSID(EAFStringFromCLSID(component.clsid).c_str());
               CString strState = pApp->GetProfileString(_T("Plugins"), strCLSID, _T("Enabled"));
               if (bAlwaysAttemptToLoad || strState.CompareNoCase(_T("Enabled")) == 0)
               {
                  auto plugin = ComponentManager::GetInstance().CreateComponent<T>(component);
                  if (plugin)
                  {
                     m_Plugins.insert({ component.clsid,plugin });
                  }
                  else
                  {
                     if (bAlwaysAttemptToLoad)
                     {
                        // failing is OK if we always attempt
                     }
                     else
                     {
                        CString strMsg;
                        strMsg.Format(_T("Failed to load %s plug-in (%s).\n\nWould you like to disable this plug-in?"), component.name.c_str(), strCLSID);
                        if (AfxMessageBox(strMsg, MB_YESNO | MB_ICONQUESTION) == IDYES)
                        {
                           pApp->WriteProfileString(_T("Plugins"), strCLSID, _T("Disabled"));
                        }
                     }
                  }
               }
            }

            return true;
         }

         bool InitPlugins()
         {
#if (201703L <= _MSVC_LANG)
            for (auto& [clsid, plugin] : m_Plugins)
            {
#else
            for (auto& item : m_Plugins)
            {
               auto& plugin = item.second;
#endif
               CString strMsg;
               strMsg.Format(_T("Initializing %s"), plugin->GetName());
               WBFL::System::Logger::Info((LPCTSTR)strMsg);
               CEAFSplashScreen::SetText(strMsg);

               if (!plugin->Init(m_pParent))
                  return false;
            }

            CEAFSplashScreen::SetText(_T(""));
            return true;
         }

         void UnloadPlugins()
         {
#if (201703L <= _MSVC_LANG)
            for (auto& [clsid, plugin] : m_Plugins)
            {
#else
            for (auto& item : m_Plugins)
            {
               auto& plugin = item.second;
#endif
            plugin->Terminate();
         }
         m_Plugins.clear();
         }

         void RemovePlugin(const CLSID& clsid)
         {
            auto found = m_Plugins.find(clsid);
            if (found != std::end(m_Plugins))
            {
               // plug-in was found
               auto plugin = found->second; // hang on to it
               m_Plugins.erase(found); // erase if from the container

               plugin->Terminate(); // terminate the plugin
            }
         }

         IndexType GetPluginCount() const
         {
            return m_Plugins.size();
         }

         std::shared_ptr<T> GetPlugin(const CLSID& clsid)
         {
            auto found = m_Plugins.find(clsid);
            if (found != m_Plugins.end())
            {
               return found->second;
            }

            return nullptr;
         }

         std::shared_ptr<T> GetPlugin(IndexType idx)
         {
            if (m_Plugins.size() <= idx)
            {
               return nullptr;
            }

            auto iter = m_Plugins.begin();
            for (IndexType i = 0; i < idx; i++)
            {
               iter++;
            }

            return iter->second;
         }

         std::shared_ptr<T> FindPlugin(LPCTSTR lpszName)
         {
            for (auto& [clsid, plugin] : m_Plugins)
            {
               auto appCmdLine = std::dynamic_pointer_cast<WBFL::EAF::IAppCommandLine>(plugin);

               if (appCmdLine && appCmdLine->GetCommandLineAppName().CompareNoCase(lpszName) == 0)
               {
                  return plugin;
               }
            }

            return nullptr;
         }

         void ManagePlugins(LPCTSTR lpszTitle, LPCTSTR lpszText)
         {
            CWnd* pWnd = EAFGetMainFrame();
            EAFManageApplicationPlugins(lpszTitle, lpszText, m_CATID, pWnd);
         }

      protected:
         CATID m_CATID;
         Parent* m_pParent = nullptr;
         using Plugins = std::map<CLSID, std::shared_ptr<T>>;
         Plugins m_Plugins;

         std::shared_ptr<WBFL::EAF::AcceleratorTable> m_PluginAcceleratorTable = std::make_shared<WBFL::EAF::AcceleratorTable>();
      };
   };
};

