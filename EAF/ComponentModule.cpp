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
