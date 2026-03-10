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
#include <memory>
#include <vector>
#include <string>
#include <guiddef.h> // for CLSID
#include <boost/dll/import.hpp>

using CATID = CLSID; // Component Category Identifier


namespace WBFL
{
   namespace EAF
   {
      class ComponentManager;
      class ComponentObject;

      /// @brief Component registration record.
      class EAFCLASS ComponentInfo
      {
      public:
         std::_tstring name; ///< Friendly name of component
         CLSID clsid = CLSID_NULL; ///< CLSID for component creation
         std::_tstring dll; ///< Full path to DLL that implements component
         std::vector<CATID> categories; ///< Categories that this component belongs to, if any
      };

      /// @brief Manages component records, component categories, and ComponentObject creation
      class EAFCLASS ComponentManager
      {
      public:
         ComponentManager() = default;
         virtual ~ComponentManager() = default;
         
         ComponentManager(const ComponentManager&) = delete;
         ComponentManager& operator=(const ComponentManager&) = delete;

         /// @brief Returns an instance of the ComponentManager. The first time this method is called
         /// the ComponentManager is created using the ComponentManagerFactory, if provided.
         /// @return 
         static ComponentManager& GetInstance();

         /// @brief Clears all component records, but does not destroy the component manager
         static void Reset();

         /// @brief Call this method as the application shuts down to perform clean up such as unloading any
         /// DLLs that where previously loaded. For EAFApp-based applications, this is automatically called from
         /// EAFApp::ExitInstance()
         static void Terminate();

         /// @brief Registers a component and associates it with a component category
         /// @param name User friendly name
         /// @param clsid The class ID
         /// @param dll Path to the DLL implementing the component (typically this will be just the DLL name and extension or a fully qualified path to the DLL. relative paths should not be used)
         /// @param catid ID of the category the class is a member of
         void RegisterComponent(const std::_tstring& name, const CLSID& clsid, const std::_tstring& dll, const CATID& catid);

         /// @brief Registers a component and associates it with multiple component categories
         /// @param name User friendly name
         /// @param clsid The class ID
         /// @param dll Path to the DLL implementing the component (typically this will be just the DLL name and extension or a fully qualified path to the DLL. relative paths should not be used)
         /// @param catids list of IDs of the category the class is a member of
         void RegisterComponent(const std::_tstring& name, const CLSID& clsid, const std::_tstring& dll, const std::vector<CATID>& catids);

         /// @brief Registers a component and associates it with component categories
         /// @param ci Component registration information
         void RegisterComponent(const ComponentInfo& ci);

         /// @brief Registers a component
         /// @param name User friendly name
         /// @param clsid The class ID
         /// @param dll Path to the DLL implementing the component (typically this will be just the DLL name and extension or a fully qualified path to the DLL. relative paths should not be used)
         void RegisterComponent(const std::_tstring& name, const CLSID& clsid, const std::_tstring& dll);

         /// @brief Returns all components registered with the specified category
         /// @param catid 
         /// @return 
         std::vector<ComponentInfo> GetComponents(CATID catid) const;

         /// @brief Returns the information about a component
         /// @param clsid
         /// @return 
         const ComponentInfo& GetComponent(CLSID clsid) const;

         /// @brief Creates a new component object
         /// @param info 
         /// @return nullptr if unsuccessful
         virtual std::shared_ptr<ComponentObject> CreateComponent(const ComponentInfo& info) const;

         /// @brief Creates a new component object
         /// @tparam T Type of the component object
         /// @param info 
         /// @return nullptr if unsuccessful
         template <class T>
         std::shared_ptr<T> CreateComponent(const ComponentInfo& info) const
         {
            return std::dynamic_pointer_cast<T>(CreateComponent(info));
         }

         /// @brief Creates a new component object. The component information must have been previously added.
         /// @param clsid 
         /// @return nullptr if unsuccessful
         std::shared_ptr<ComponentObject> CreateComponent(const CLSID& clsid) const;

         /// @brief Creates a new component object
         /// @tparam T Type of the component object
         /// @param clsid 
         /// @return nullptr if unsuccessful
         template <class T>
         std::shared_ptr<T> CreateComponent(const CLSID& clsid) const
         {
            return std::dynamic_pointer_cast<T>(CreateComponent(clsid));
         }

         /// @brief Saves the component registration information into a manifest file
         /// @param filename 
         void Save(const std::_tstring& filename) const;

         /// @brief Loads the component registration information from a manifest file
         /// @param filename 
         void Load(const std::_tstring& filename);

      private:
         static std::unique_ptr<ComponentManager> instance;
         std::vector<ComponentInfo> m_components;
         
         using factory_t = std::shared_ptr<WBFL::EAF::ComponentObject>(const CLSID& );
         mutable std::vector<boost::dll::detail::library_function<factory_t>> m_factories; // this holds the DLL in memory
      };
   };
};