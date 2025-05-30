#pragma once

#include <EAF\EAFExp.h>
#include <boost/dll/alias.hpp>

#include <EAF\ComponentObject.h>

#include <memory>

#include <guiddef.h>
#include <vector>

template <typename T>
auto create_object_fn = []()->std::shared_ptr<WBFL::EAF::ComponentObject>
   {
      auto obj = std::make_shared<T>();
      auto com = std::dynamic_pointer_cast<WBFL::EAF::ComponentObject>(obj);
      if (!com) WBFL::System::Logger::Error(_T("Class is not a ComponentObject"));
      return com;
   };

template <typename T>
auto create_singleton_fn = []()->std::shared_ptr<WBFL::EAF::ComponentObject>
   {
      auto obj = T::CreateInstance();
      auto com = std::dynamic_pointer_cast<WBFL::EAF::ComponentObject>(obj);
      if (!com) WBFL::System::Logger::Error(_T("Class is not a ComponentObject"));
      return com;
   };

using OBJMAP_ENTRY = struct { const CLSID* pclsid; std::function<std::shared_ptr<WBFL::EAF::ComponentObject>()> fn; };
#define EAF_BEGIN_OBJECT_MAP(x) static OBJMAP_ENTRY x[] = {
#define EAF_END_OBJECT_MAP() { nullptr, []{return nullptr;}} };
#define EAF_OBJECT_ENTRY(clsid,class) {&clsid,create_object_fn<class>},
#define EAF_OBJECT_ENTRY_SINGLETON(clsid,class) {&clsid,create_singleton_fn<class>},

#define EAF_MANUAL_OBJECT_ENTRY(_module_,clsid,class) _module_.AddObjectMapEntry(&clsid,create_object_fn<class>)

namespace WBFL
{
   namespace EAF
   {
      class ComponentModule;

      /// @brief Manages component modules
      class EAFCLASS ComponentModuleMgr
      {
      public:
         /// @brief Searches the registered modules for an instance that can create a ComponentObject
         /// from the specified CLSID.
         /// @param clsid 
         /// @return 
         static std::shared_ptr<WBFL::EAF::ComponentObject> CreateClassObject(const CLSID& clsid);

         /// @brief Adds a module
         /// @param pModule 
         static void AddModule(ComponentModule* pModule);
      private:
         static std::vector<ComponentModule*> modules;
         static ComponentModule* FindModule(const CLSID& clsid);
      };

      /// @brief A component module is essentially a class factory that creates instances of ComponentObjects.
      /// DLLs providing a ComponentModule create an instance of ComponentModule and define the object entry map
      /// with the EAF_BEGIN_OBJECT_MAP, EAF_OBJECT_ENTRY, and EAF_END_OBJECT_MAP macros.
      class EAFCLASS ComponentModule
      {
      public:
         /// @brief Initializes the module with object entries
         /// @param objMap 
         void Init(OBJMAP_ENTRY* objMap);

         /// @brief Adds an object entry to the modules object map
         /// The EAF_MANUAL_OBJECT_ENTRY macro can be used to manually add an object entry to the object map
         /// instead of calling this method directly
         /// @param pclsid 
         /// @param fn 
         void AddObjectMapEntry(const CLSID* pclsid, std::function<std::shared_ptr<WBFL::EAF::ComponentObject>()> fn);

         /// @brief Called by the framework with a component module is about to be destroyed
         void Term();

         /// @brief Factory method that creates a ComponentObject from the CLSID
         /// @param clsid 
         /// @return 
         virtual std::shared_ptr<ComponentObject> CreateClassObject(const CLSID& clsid) const;

         /// @brief Returns true if this module can create an object with the specified clsid.
         /// @param clsid 
         /// @return 
         virtual bool CanCreateObject(const CLSID& clsid) const;

      private:
         std::vector<OBJMAP_ENTRY> m_ObjMap;
      };
   };
};


BOOST_DLL_ALIAS(WBFL::EAF::ComponentModuleMgr::CreateClassObject, create_class_object);


