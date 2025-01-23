///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
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

#include <map>
#include <set>

#include <memory>

#include <Checks.h>
#include <LibraryFw\ILibrary.h>
#include <LibraryFw\LibraryHints.h>
#include <System\IStructuredSave.h>
#include <System\IStructuredLoad.h>
#include <System\XStructuredLoad.h>

namespace WBFL
{
   namespace Library
   {
      class LIBRARYFWCLASS LibraryManager;

      /// @brief This class provides a generic interface for storing LibraryEntries
      template<class T,IndexType MIN_COUNT>
      class Library : public ILibrary
      {
      public:
         Library() = delete;
         Library(const Library&) = delete;

         /// @brief Constructor
         /// idName must be a unique name (to other libraries added to a manager) and
         /// must not contain any whitespace.
         /// displayName is a name fit to be displayed by an editor
         Library(LPCTSTR idName, LPCTSTR displayName, bool bIsDepreciated = false):
         m_IdName( idName ),
         m_DisplayName(displayName),
         m_bIsDepreciated(bIsDepreciated)
         {
            m_pLibraryManager = 0;
         }

         virtual ~Library() = default;

         Library& operator=(const Library&) = delete;

         void SetLibraryManager(LibraryManager* pLibraryManager)
         {
            m_pLibraryManager = pLibraryManager;
         }


         LibraryManager* GetLibraryManager() const
         {
            return m_pLibraryManager;
         }

         /// @brief Add a new default entry with the given name. Returns false if 
         /// unsuccessful, which likely means that an entry with the same name
         /// already exists.
         bool NewEntry(LPCTSTR key)
         {
            if ( IsReservedName(key) )
            {
               return false;
            }

            // check if key exists already
            const T* pentry = LookupEntryPrv(key);

            if (!pentry)
            {
               // doesn't exist - add a new one.
               LibItem apentry( std::make_shared<T>() );
               apentry->SetName(key);
               apentry->SetLibrary(this);
               m_EntryList.insert(EntryList::value_type(key, apentry));
               return true;
            }
            else
            {
               return false;
            }
         }

         /// @brief Add an entry based on another. key must be unique. Returns false if failed.
         bool AddEntry( const T& rNewValue, LPCTSTR key, bool bAddRef = false )
         {
            if ( IsReservedName(key) )
            {
               return false;
            }

            // check if key exists already
            const T* pentry = LookupEntryPrv(key);

            if (!pentry)
            {
               // doesn't exist - add it
               LibItem apentry( new T(rNewValue) );
               if ( bAddRef )
               {
                  apentry->AddRef();
               }

               apentry->SetName(key);
               apentry->SetLibrary(this);

               auto result = m_EntryList.insert(EntryList::value_type(key, apentry));
               return result.second;
            }
            else
               return false;
         }

         /// @brief Create a clone of an existing entry (named key) and create a new entry
         /// named newkey. key must be in the library and newkey must not. 
         /// Returns false if unsuccessful.
         bool CloneEntry(LPCTSTR key, LPCTSTR newkey)
         {
            if ( IsReservedName(newkey) )
            {
               return false;
            }

            T* pentry = LookupEntryPrv(key);
            T* pnewentry = LookupEntryPrv(newkey);
            if (!pentry)
            {
               // Attempting to edit an unknown entry - not good form.
               return false;
            }
            else if (pnewentry)
            {
               // target entry exists already - return false
               return false;
            }
            else if (std::_tstring(key)==std::_tstring(newkey))
            {
               // can't clone yourself
               return false;
            }
            else
            {
               // copy
               LibItem apentry( std::make_shared<T>(*pentry) );
               apentry->SetName(newkey);
               apentry->SetLibrary(this);
               m_EntryList.insert(EntryList::value_type(newkey, apentry));
               return true;
            }
         }


         /// @brief Open the editing interface for the given entry. 
         ILibrary::EntryEditOutcome EditEntry( LPCTSTR key,UINT nPage=0 )
         {
            T* pentry = LookupEntryPrv(key);
            if (!pentry)
            {
               // Attempting to edit an unknown entry - not good form.
               return ILibrary::EntryEditOutcome::NotFound;
            }
            else
            {
               if (pentry->Edit(pentry->IsEditingEnabled(),nPage))
               {
                  auto hint = Hint_EntryEdited;
                  // it's a tough call what to do here if the user changes the name of the 
                  // entry to be the same as another item in the library. The only safe thing to
                  // do is to abort the edit. This may piss some folks off though.
            
                  std::_tstring nam = pentry->GetName();
                  if (nam!=std::_tstring(key))
                  {
                     hint |= Hint_EntryRenamed;

                     T* apentry = LookupEntryPrv(nam.c_str());
                     if(apentry)
                     {
                        // user gave entry a name that already exists - too bad.
                        pentry->SetName(key);
                        return ILibrary::EntryEditOutcome::RenameFailed;
                     }
                     else
                     {
                        // must delete old location and move it to a new one
                        if (!this->RenameEntry(key, nam.c_str()))
                           return ILibrary::EntryEditOutcome::RenameFailed;
                     }
                  }

                  pentry->Notify(hint);
            
               }
               else
               {
                  // restore back to original
                  return ILibrary::EntryEditOutcome::Cancelled;
               }
            }
            return ILibrary::EntryEditOutcome::Ok;
         }

         /// @brief Return a pointer to an entry based on its key. Returns zero if failed.
         /// NOTE: this call causes a call to AddRef() for the given entry. You must
         ///       call Release() on the entry when you are done with it.
         const T*  LookupEntry( LPCTSTR key) const
         {
            auto tmp = m_EntryList.find(key);
            if (tmp != m_EntryList.end() )
            {
               (*tmp).second->AddRef();     // increment reference count
               return (*tmp).second.get();
            }
            else
            {
               return nullptr;
            }
         }

         /// @brief get the key of an existing entry in the library
         bool GetEntryKey( const T& rValue, std::_tstring& rkey ) const
         {
            // linear search to compare pointers
#if (201703L <= _MSVC_LANG)
            for (const auto& [name, item] : m_EntryList)
            {
#else
            for (const auto& entry : m_EntryList)
            {
               const auto& name(entry.first);
               auto& item(entry.second);
#endif
               if (&rValue == item.get())
               {
                  rkey = name;
                  return true;
               }
            }
            return false;      
         }

         /// @brief Update an existing entry by copying another to it.
         bool UpdateEntry( const T& rNewValue, LPCTSTR key )
         {
            T* pentry = LookupEntryPrv(key);
            if (!pentry || pentry==&rNewValue)
            {
               // Attempting to edit an unknown entry - not good form.
               return false;
            }
            else
            {
               // copy new entry over top of existing - keep existing name though
               *pentry = rNewValue;
               std::_tstring onam = pentry->GetName();
               if (onam != key)
               {
                  pentry->SetName(key);
               }

               pentry->Notify(Hint_EntryEdited);

               return true;
            }
         }

         /// @brief Rename an entry
         bool RenameEntry( LPCTSTR oldKey, LPCTSTR newKey)
         {
            if ( IsReservedName(newKey) )
               return false;

            T* pentry = LookupEntryPrv(newKey);
            if (pentry)
            {
               // new already exists
               return false;
            }
            else
            {

               auto tmp = m_EntryList.find(oldKey);
               if (tmp != m_EntryList.end() )
               {
                  // must continue to use same pointer
                  std::shared_ptr<T> apentry = (*tmp).second;
                  // erase old entry
                  IndexType st = m_EntryList.erase(oldKey);
                  CHECK(st==1);
                  // reinsert pointer with new name
                  apentry->SetName(newKey);
                  bool suc = (m_EntryList.insert(EntryList::value_type(newKey, LibItem(apentry))).second);
                  CHECK(suc);

                  apentry->Notify(Hint_EntryRenamed);

                  return suc;
               }
               else
               {
                  // not found
                  return false;
               }
            }
         }

         /// @brief Remove an entry. 
         ILibrary::EntryRemoveOutcome RemoveEntry( LPCTSTR key )
         {
            auto tmp = m_EntryList.find(key);
            if (tmp != m_EntryList.end() )
            {
               if ((*tmp).second->GetRefCount()==0)
               {
                  m_EntryList.erase(tmp);
                  return ILibrary::EntryRemoveOutcome::Ok;
               }
               else
               {
                  return ILibrary::EntryRemoveOutcome::Referenced;
               }
            }
            else
            {
               return ILibrary::EntryRemoveOutcome::NotFound;
            }
         }

         /// @brief Remove all entries. Will assert if entries have outstanding references
         void RemoveAll()
         {
            m_EntryList.clear();
         }

         /// @brief Save to structured storage
         bool SaveMe(WBFL::System::IStructuredSave* pSave)
         {
            // not much data for a library
            pSave->BeginUnit(_T("LIBRARY"), 1.0);
            pSave->Property(_T("LIBRARY_ID_NAME"), m_IdName.c_str());
            pSave->Property(_T("LIBRARY_DISPLAY_NAME"), m_DisplayName.c_str());
#if (201703L <= _MSVC_LANG)
            for (const auto& [name, item] : m_EntryList)
            {
#else
            for (const auto& entry : m_EntryList)
            {
               const auto& name(entry.first);
               auto& item(entry.second);
#endif
               pSave->BeginUnit(_T("LIBRARY_ENTRY"),1.0);
               pSave->Property(_T("ENTRY_KEY"), name.c_str());

               item->SaveMe(pSave);

               pSave->EndUnit();
            }
            pSave->EndUnit();
            return true;
         }

         /// @brief Load from structured storage
         bool LoadMe(WBFL::System::IStructuredLoad* pLoad)
         {
            // load library and its entries
            if (pLoad->BeginUnit(_T("LIBRARY")))
            {
               if (pLoad->GetVersion()==1.0)
               {
                  if (pLoad->Property(_T("LIBRARY_ID_NAME"), &m_IdName))
                  {
                     if (pLoad->Property(_T("LIBRARY_DISPLAY_NAME"), &m_DisplayName))
                     {
                        std::_tstring key;
                        while (pLoad->BeginUnit(_T("LIBRARY_ENTRY")))
                        {
                           if (pLoad->Property(_T("ENTRY_KEY"), &key))
                           {
                              // allocate a new item
                              LibItem itm(std::make_shared<T>());
                              itm->SetLibrary(this);
                              if (itm.get()==0)
                              {
                                 THROW_LOAD(MemoryError,pLoad);
                              }

                              if (itm->LoadMe(pLoad))
                              {
                                 // store it in the map
                                 if(itm->GetName()==key)
                                 {
                                    m_EntryList.insert(EntryList::value_type(key,LibItem(itm)));
                                 }
                                 else
                                 {
                                    THROW_LOAD(InvalidFileFormat,pLoad);  // key doesn't match name
                                 }
                              }
                              else
                              {
                                 THROW_LOAD(BadRead,pLoad);
                              }

                              if(!pLoad->EndUnit())
                                 THROW_LOAD(InvalidFileFormat,pLoad);
                           }
                           else
                           {
                              THROW_LOAD(InvalidFileFormat,pLoad);
                           }
                        } // while
                     }
                     else
                     {
                        THROW_LOAD(InvalidFileFormat,pLoad);
                     }
                  }
                  else
                  {
                     THROW_LOAD(InvalidFileFormat,pLoad);
                  }
               }
               else
               {
                  // File is wrong version - need to puke
                  THROW_LOAD(BadVersion,pLoad);
               }
            }
            else
            {
               return false;
            }

            if(!pLoad->EndUnit())
            {
               THROW_LOAD(InvalidFileFormat,pLoad);
            }

            return true;
         }


         /// @brief Change the display name of the library.
         void SetDisplayName(LPCTSTR name)
         {
            m_DisplayName = name;
         }

         /// @brief Get the name of the library
         std::_tstring GetDisplayName() const
         {
            return m_DisplayName;
         }

         /// @brief Get the identification name of the library
         std::_tstring GetIdName() const
         {
            return m_IdName;
         }

         /// @brief return a list of the names of all entries in the library.
         void KeyList(KeyListType& rList) const
         {
            rList.clear();
#if (201703L <= _MSVC_LANG)
            for( const auto& [name,item] : m_EntryList)
            {
#else
            for(const auto& entry : m_EntryList)
            {
               const auto& name(entry.first);
#endif
               rList.emplace_back(name);
            }
         }

         /// @brief Get the number of entries in the library
         IndexType GetCount( ) const
         {
            return m_EntryList.size();
         }

         IndexType GetMinCount() const
         {
            return MIN_COUNT;
         }

         /// @brief Returns true when the library is empty
         bool IsEmpty( ) const
         {
            return m_EntryList.size() == 0;
         }

         bool IsDepreciated() const
         {
            return m_bIsDepreciated;
         }

         /// @brief Get a const pointer to an entry by index
         /// Returns nullptr if out of range and asserts
         /// DOES NOT INCREASE REFERENCE COUNT!
         const LibraryEntry* GetEntry(LPCTSTR key) const
         {
            const auto* pent = LookupEntry(key);
            if (pent != nullptr)
            {
               pent->Release();
            }
      
            return pent;
         }

         /// @brief See if an entry exists in the library
         bool IsEntry(LPCTSTR key) const 
         {
            const T* pent = LookupEntry(key);
            if (pent!=nullptr)
            {
               pent->Release();
            }
            return (pent!=nullptr);
         }

         /// @brief Get the number of references to this entry
         Uint32 GetEntryRefCount(LPCTSTR key) const
         {
            const T* pent = LookupEntry(key);
            if (pent!=nullptr)
            {
               pent->Release();
               return pent->GetRefCount();
            }
            else
            {
               CHECK(0); // bad key
               return 0;
            }
         }

         virtual void EnableCopy(LPCTSTR key,bool enable)
         {
            T* pent = LookupEntryPrv(key);
            if (pent!=nullptr)
            {
               pent->EnableCopying(enable);
            }
            else
            {
               CHECK(0); // bad key
            }
         }

         virtual bool IsCopyingEnabled(LPCTSTR key) const
         {
            const T* pent = LookupEntry(key);
            if (pent!=nullptr)
            {
               pent->Release();
               return pent->IsCopyingEnabled();
            }
            else
            {
               CHECK(0); // bad key
               return false;
            }
         }

         /// @brief Returns true if entry can be edited
         virtual bool IsEditingEnabled(LPCTSTR key) const
         {
            const T* pent = LookupEntry(key);
            if (pent!=nullptr)
            {
               pent->Release();
               return pent->IsEditingEnabled();
            }
            else
            {
               CHECK(0); // bad key
               return false;
            }
         }

         /// @brief set flag which enables entry to be edited
         virtual void EnableEditing(LPCTSTR key, bool enable) 
         {
            T* pent = LookupEntryPrv(key);
            if (pent!=nullptr)
            {
               pent->EnableEditing(enable);
            }
            else
            {
               CHECK(0); // bad key
            }
         }

         /// @brief set flag which enables all entries in the library to be edited
         virtual void EnableEditingForAll(bool enable)
         {
            for(auto& entry : m_EntryList)
            {
               entry.second->EnableEditing(enable);
            }
         }

         /// @brief Generate a name that's guaranteed not to be in the library
         std::_tstring GetUniqueEntryName(LPCTSTR lpszBaseName=_T("New Entry-")) const 
         {
            // name will be in the form on lpszBaseNamenn where nn is some number.
            bool unique=false;
            std::_tostringstream sstr;
            for (int i = 0; true; i++)
            {
               std::_tostringstream sstr;
               sstr << lpszBaseName << i;
               const T* pent = LookupEntry(sstr.str().c_str());
               if (pent==nullptr)
               {
                  return sstr.str();
               }
               else
               {
                  pent->Release();
               }
            }
            CHECK(false);
            return _T("Error"); // power failure will happen before we ever get here.
         }

         /// @brief Create a polymorphic clone of a library entry into this library. 
         /// The type of newentry is checked to make sure it is correct and will 
         /// ASSERT if it is not.
         /// Returns false if newkey is not a unique name
         virtual bool AddEntry(const LibraryEntry& newentry, LPCTSTR newkey)
         {
            const T* pent = dynamic_cast<const T*>(&newentry);
            if (pent==nullptr)
            {
               CHECK(0);
               return false;
            }
            else
            {
               // right type - now add it to our library
               return AddEntry(*pent, newkey, false);
            }
         }

         /// @brief Factory function to create an external polymorphic clone of a library entry. 
         /// You are responsible for deleting it.
         virtual std::unique_ptr<LibraryEntry> CreateEntryClone(LPCTSTR key) const
         {
            const T* pent = LookupEntry(key);
            if (pent != nullptr)
            {
               pent->Release(); // balances the AddRef call in LookupEntry
               std::unique_ptr<LibraryEntry> newEntry(std::make_unique<T>(*pent));
               newEntry->SetLibrary(this);
               return newEntry;
            }
            else
            {
               return nullptr;
            }
         }

         std::set<std::_tstring> GetReservedNamesList() const
         {
            return m_ReservedNamesList;
         }

         void AddReservedName(LPCTSTR strName)
         {
            m_ReservedNamesList.insert( strName );
         }

         bool IsReservedName(LPCTSTR strName) const
         {
            std::set<std::_tstring>::const_iterator found = m_ReservedNamesList.find(strName);
            return (found == m_ReservedNamesList.end() ? false : true);
         }

      protected:
         std::_tstring m_IdName;
         std::_tstring m_DisplayName;
         bool m_bIsDepreciated;
         LibraryManager* m_pLibraryManager = nullptr;

         using LibItem = std::shared_ptr<T>;
         using EntryList = typename std::map<std::_tstring, LibItem>;

         EntryList m_EntryList;

         std::set<std::_tstring> m_ReservedNamesList;

         /// @brief Return a non-const pointer to an entry based on its key. Returns zero if failed
         T*  LookupEntryPrv( LPCTSTR key)
         {
            // if the name is on the reserved list, get outta here
            if ( IsReservedName(key) )
            {
               return nullptr;
            }

            auto tmp = m_EntryList.find(key);
            if (tmp != m_EntryList.end() )
            {
               return (*tmp).second.get();
            }
            else
            {
               return nullptr;
            }
         }
      };
   };
};
