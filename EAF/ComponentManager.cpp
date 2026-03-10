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

#include <EAF/EAFApp.h>
#include <EAF/ComponentManager.h>

#include <algorithm>
#include <vector>

#include <iostream>
#include <filesystem>

#include <boost/dll/import.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace WBFL::EAF;

std::unique_ptr<ComponentManager> ComponentManager::instance;

ComponentManager& ComponentManager::GetInstance()
{
   if (instance == nullptr)
   {
      instance = std::make_unique<ComponentManager>();
   }
   return *instance;
}

void ComponentManager::Reset()
{
   GetInstance().m_components.clear();
}

void ComponentManager::Terminate()
{
   Reset();

   // m_factories holds references to all the DLLs. These DLLs don't unload until
   // their reference is cleared.
   GetInstance().m_factories.clear();

   instance = nullptr;
}

void ComponentManager::RegisterComponent(const std::_tstring& name, const CLSID& clsid, const std::_tstring& dll, const CATID& catid)
{
   ComponentInfo ci;
   ci.name = name;
   ci.clsid = clsid;
   ci.dll = dll;
   ci.categories.push_back(catid);
   m_components.push_back(ci);
}

void ComponentManager::RegisterComponent(const std::_tstring& name, const CLSID& clsid, const std::_tstring& dll, const std::vector<CATID>& catids)
{
   ComponentInfo ci;
   ci.name = name;
   ci.clsid = clsid;
   ci.dll = dll;
   ci.categories = catids;
   m_components.push_back(ci);
}

void ComponentManager::RegisterComponent(const ComponentInfo& ci)
{
   m_components.push_back(ci);
}

void ComponentManager::RegisterComponent(const std::_tstring& name, const CLSID& clsid, const std::_tstring& dll)
{
   ComponentInfo ci;
   ci.name = name;
   ci.clsid = clsid;
   ci.dll = dll;
   RegisterComponent(ci);
}

std::vector<ComponentInfo> ComponentManager::GetComponents(CATID catid) const
{
   // there is probably a more efficient way to do this - like have a container with key = catid and value = vector of components
   // that is created on startup
   std::vector<ComponentInfo> records;
   for (const auto& component : m_components)
   {
      for (const auto& category_id : component.categories)
      {
         if (category_id == catid)
            records.push_back(component);
      }
   }
   return records;
}

const ComponentInfo& ComponentManager::GetComponent(CLSID clsid) const
{
   for (const auto& component : m_components)
   {
      if (component.clsid == clsid)
         return component;
   }

   USES_CONVERSION;
   std::string cld(OLE2A(EAFStringFromCLSID(clsid).c_str()));
   std::ostringstream msg;
   msg << "ComponentManager::GetComponent - component with CLSID " << cld << " not found" << std::endl;
   WBFL::System::Logger::Debug(msg.str());
   throw std::runtime_error(msg.str());
}

template <class T>
typename boost::dll::detail::import_type<T>::type get_factory_method(const boost::dll::fs::path& lib,
   boost::dll::load_mode::type mode = boost::dll::load_mode::default_mode)
{
   typedef typename boost::dll::detail::import_type<T>::base_type type;

   boost::shared_ptr<boost::dll::shared_library> p = boost::make_shared<boost::dll::shared_library>(lib, mode);
   auto f = p->get<T*>("create_class_object");
   if (f == nullptr)
   {
      f = boost::addressof(p->get<T>("EAFGetClassObject"));
   }

   if (f == nullptr)
   {
      std::ostringstream os;
      os << "Factory methods not found in " << lib;
      WBFL::System::Logger::Debug(os.str());
      throw std::runtime_error(os.str());
   }
   return type(p, f);
}

std::shared_ptr<ComponentObject> ComponentManager::CreateComponent(const ComponentInfo& component) const
{
   boost::dll::fs::path lib_path;

   try
   {
      std::filesystem::path p(component.dll);
      if (p.is_relative() && p.has_parent_path())
      {
         // relative path, convert to absolute
         p = std::filesystem::absolute(p);
      }

      if (!p.is_absolute())
      {
         auto search_directories = EAFGetApp()->GetSearchDirectories();
         for (auto& directory : search_directories)
         {
            auto f = std::filesystem::path((LPCTSTR)directory) / p;
            if (std::filesystem::exists(f))
            {
               p = f;
               break;   
            }
         }
      }

      lib_path = p;

      // need to use our own version of import_alias. it is called get_factory_method<T>. see note above.
      //auto factory = boost::dll::import_alias<factory_t>(lib_path, "create_class_object", boost::dll::load_mode::append_decorations);
      auto factory = get_factory_method<factory_t>(lib_path, boost::dll::load_mode::default_mode);
      m_factories.push_back(factory);

      auto class_object = factory(component.clsid);
      if (class_object == nullptr)
      {
         std::_tostringstream os;
         os << _T("Object creation failed : ") << component.name << _T(", ") << EAFStringFromCLSID(component.clsid);
         WBFL::System::Logger::Error(os.str());
         WATCH(os.str());
      }
      return class_object;
   }
   catch (std::exception& e)
   {
      std::_tstringstream os;
      os << e.what() << _T(" - ") << lib_path;
      WBFL::System::Logger::Error(os.str());
      WATCH(os.str());
   }
   return nullptr;
}

std::shared_ptr<ComponentObject> ComponentManager::CreateComponent(const CLSID& clsid) const
{
   for (const auto& component : m_components)
   {
      if (component.clsid == clsid)
         return CreateComponent(component);
   }

   return nullptr;
}

void ComponentManager::Save(const std::_tstring& filename) const
{
   USES_CONVERSION;
   namespace pt = boost::property_tree;
   pt::ptree tree;
   for (const auto& component : m_components)
   {
      pt::ptree parent;
      parent.put("Name", T2A(component.name.c_str()));
      parent.put("CLSID", T2A(EAFStringFromCLSID(component.clsid).c_str()));
      parent.put("dll", T2A(component.dll.c_str()));
      if (!component.categories.empty())
      {
         for (const auto& category : component.categories)
         {
            pt::ptree child;
            child.put("", T2A(EAFStringFromCLSID(category).c_str()));
            parent.add_child("Categories.CATID", child);
         }
      }
      tree.add_child("Component", parent);
   }

   std::ofstream ofs(T2A(filename.c_str()));
   if (ofs.fail() || ofs.bad()) 
      throw;
   pt::json_parser::write_json(ofs, tree);
}

void ComponentManager::Load(const std::_tstring& filename)
{
   USES_CONVERSION;

   std::filesystem::path p(filename);
   if (!p.is_absolute())
   {
      // Need a super verbose logging mode that lists all attempts to create objects
      CString strApp = EAFGetApp()->GetAppLocation();
      p = std::filesystem::path(std::_tstring(strApp.LockBuffer()) + filename);
   }

   std::_tostringstream os;
   os << _T("Loading manifest: ") << p;
   WBFL::System::Logger::Debug(os.str());

   namespace pt = boost::property_tree;
   pt::ptree tree;
   std::ifstream ifs(T2A(p.c_str()));

   if (ifs.fail())
   {
      std::_tostringstream os;
      os << _T("Failed to open manifest: ") << p;
      WBFL::System::Logger::Error(os.str());
   }

   pt::json_parser::read_json(ifs, tree);

   for (auto c : tree)
   {
      if (c.first == std::string("Component"))
      {
         ComponentInfo component_info;
         component_info.name = A2T(c.second.get<std::string>("Name").c_str());
         ::CLSIDFromString(A2OLE(c.second.get<std::string>("CLSID").c_str()), &component_info.clsid);
         component_info.dll = A2T(c.second.get<std::string>("dll").c_str());
         try
         {
            auto child = c.second.get_child("Categories");
            for (auto ch : child)
            {
               CATID catid;
               ::CLSIDFromString(A2OLE(ch.second.data().c_str()), &catid);
               component_info.categories.push_back(catid);
            }
         }
         catch (...)
         {
            // Not all component objects are associated with a component category
            // When this happens, the manifest file will not have a "Categories" node and
            // get_child("Categories") will throw an exception.
            // Catch the exception and continue because it's ok to not have categories
         }

         RegisterComponent(component_info);
      }
      else
      {
         std::runtime_error e("Invalid manifest");
         WBFL::System::Logger::Error(e.what());
         throw e;
      }
   }
}
