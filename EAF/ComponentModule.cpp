///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2026  Washington State Department of Transportation
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
#include <EAF/ComponentModule.h>
#include <EAF/EAFStrings.h>

using namespace WBFL::EAF;

std::vector<ComponentModule*> ComponentModuleMgr::modules;

std::shared_ptr<WBFL::EAF::ComponentObject> ComponentModuleMgr::CreateClassObject(const CLSID& clsid)
{
   for (auto& m : modules)
   {
      if (m->CanCreateObject(clsid))
      {
         auto obj = m->CreateClassObject(clsid);
         if (!obj)
         {
            std::_tostringstream os;
            os << _T("Failed to create class object for ") << EAFStringFromCLSID(clsid) << _T(". The component module was found, but object creation failed.");
            WBFL::System::Logger::Error(os.str());
         }
         return obj;
      }
   }

   std::_tostringstream os;
   os << _T("Failed to create class object for ") << EAFStringFromCLSID(clsid) << _T(". No modules support this CLSID.");
   WBFL::System::Logger::Error(os.str());

   return nullptr;
}

ComponentModule* ComponentModuleMgr::FindModule(const CLSID& clsid)
{
   for (auto& m : modules)
   {
      if (m->CanCreateObject(clsid))
         return m;
   }

   return nullptr;
}

void ComponentModuleMgr::AddModule(ComponentModule* pModule)
{
   modules.push_back(pModule);
}

void ComponentModule::Init(OBJMAP_ENTRY* objMap)
{
   OBJMAP_ENTRY* pEntry = objMap;
   while (pEntry->pclsid != nullptr)
   {
      m_ObjMap.push_back(*pEntry);
      pEntry++;
   }

   ComponentModuleMgr::AddModule(this);
}

void ComponentModule::AddObjectMapEntry(const CLSID* pclsid, std::function<std::shared_ptr<WBFL::EAF::ComponentObject>()> fn)
{
   OBJMAP_ENTRY entry(pclsid, fn);
   m_ObjMap.push_back(entry);
}

void ComponentModule::Term()
{
   // do nothing, but this is a placeholder for future cleanup if needed
}

std::shared_ptr<ComponentObject> ComponentModule::CreateClassObject(const CLSID& clsid) const
{
   for(const auto& entry : m_ObjMap)
   {
      if (*entry.pclsid == clsid)
      {
         return entry.fn();
      }
   }
   return nullptr;
}

bool ComponentModule::CanCreateObject(const CLSID& clsid) const
{
   for (const auto& entry : m_ObjMap)
   {
      if (*entry.pclsid == clsid)
      {
         return true;
      }
   }
   return false;
}
