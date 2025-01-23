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

#include <LibraryFw\LibraryFwLib.h>

#include <LibraryFw\LibraryManager.h>

#include <System\IStructuredSave.h>
#include <System\IStructuredLoad.h>
#include <System\XStructuredLoad.h>

using namespace WBFL::Library;

void LibraryManager::SetName(LPCTSTR name) 
{
   m_Name =name;
}

std::_tstring LibraryManager::GetName() const
{
   return m_Name;
}

IndexType LibraryManager::AddLibrary(ILibrary* pLibrary)
{
   PRECONDITION(pLibrary);
   ILibrary* plib = GetLibrary(pLibrary->GetIdName().c_str());
   PRECONDITIONX(!plib,_T("Libraries must have unique id names"));
   pLibrary->SetLibraryManager(this);

   m_Libraries.emplace_back(pLibrary);
   return m_Libraries.size()-1;
}

IndexType LibraryManager::GetLibraryCount() const
{
   return m_Libraries.size();
}

bool LibraryManager::IsDepreciated(IndexType idx) const
{
   const ILibrary* pLib = GetLibrary(idx);
   return pLib->IsDepreciated();
}

const WBFL::System::Time& LibraryManager::GetTimeStamp() const
{
   return m_LastSavedTime;
}

std::_tstring LibraryManager::GetLibraryIdName(IndexType index) const
{
   const ILibrary* plib;
   if (0 <= index && index < m_Libraries.size())
   {
       plib = m_Libraries[index].get();
   }
   else
   {
      throw std::invalid_argument("Invalid library index");
   }

   return plib->GetIdName();
}

std::_tstring LibraryManager::GetLibraryDisplayName(IndexType index) const
{
   const ILibrary* plib;
   if (0 <= index && index < m_Libraries.size())
   {
       plib = m_Libraries[index].get();
   }
   else
   {
      throw std::invalid_argument("Invalid library index");
   }

   return plib->GetDisplayName();
}

ILibrary* LibraryManager::GetLibrary(IndexType index)
{
   if (0 <= index && index < m_Libraries.size())
   {
      return m_Libraries[index].get();
   }
   else
   {
      return nullptr;
   }
}

const ILibrary* LibraryManager::GetLibrary(IndexType index) const
{
   if (0 <= index && index < m_Libraries.size())
   {
      return m_Libraries[index].get();
   }
   else
   {
      return nullptr;
   }
}

ILibrary* LibraryManager::GetLibrary(LPCTSTR displayName)
{
   std::_tstring name(displayName);
   for(auto& library : m_Libraries)
   {
      if (library->GetDisplayName() == name)
      {
         return library.get();
      }
   }
   return nullptr;
}


const ILibrary* LibraryManager::GetLibrary(LPCTSTR displayName) const
{
   std::_tstring name(displayName);
   for (const auto& library : m_Libraries)
   {
      if (library->GetDisplayName() == name)
      {
         return library.get();
      }
   }
   return nullptr;
}

IndexType LibraryManager::GetIndex(LPCTSTR displayName) const
{
   IndexType idx = 0;
   std::_tstring name(displayName);
   for(const auto& library : m_Libraries)
   {
      if (library->GetDisplayName() == name)
      {
         return idx;
      }
      idx++;
   }
   return INVALID_INDEX;
}

void LibraryManager::ClearAllEntries()
{
   std::for_each(m_Libraries.begin(), m_Libraries.end(), [](auto& library) {library->RemoveAll(); });
}

void LibraryManager::ClearLibraries()
{
   ClearAllEntries();
   m_Libraries.clear();
}


void LibraryManager::EnableEditingForAllEntries(bool enable)
{
   std::for_each(m_Libraries.begin(), m_Libraries.end(), [&enable](auto& library) {library->EnableEditingForAll(enable); });
}

std::vector<EntryUsageRecord> LibraryManager::GetInUseLibraryEntries() const
{
   std::vector<EntryUsageRecord> records;

   for(const auto& library : m_Libraries)
   {
      std::_tstring strLibName = library->GetDisplayName();

      KeyListType key_list;
      library->KeyList(key_list);
      for(auto& key : key_list)
      {
         const LibraryEntry* pEntry = library->GetEntry(key.c_str());
         if ( 0 < pEntry->GetRefCount() )
         {
            EntryUsageRecord record;
            record.LibName = strLibName;
            record.EntryName = pEntry->GetName();
            record.bEditable = pEntry->IsEditingEnabled();

            records.push_back(record);
         }
      }
   }

   return records;
}

bool LibraryManager::SaveMe(WBFL::System::IStructuredSave* pSave)
{
   // not much data for a library manager 
   pSave->BeginUnit(_T("LIBRARY_MANAGER"), 2.0);

   WBFL::System::Time time; // now
   pSave->Property(_T("TimeStamp"),time.Seconds());
   for(auto& library : m_Libraries)
   {
      if ( !library->IsDepreciated() )
      {
         // only save the library if it is not depreciated
         pSave->BeginUnit(_T("LIBRARY_MANAGER_ENTRY"),1.0);
         pSave->Property(_T("LIBRARY_NAME"), library->GetIdName().c_str());

         library->SaveMe(pSave);

         pSave->EndUnit();
      }
   }
   pSave->EndUnit();
   return true;
}

bool LibraryManager::LoadMe(WBFL::System::IStructuredLoad* pLoad)
{
   // load library and its entries
   if (pLoad->BeginUnit(_T("LIBRARY_MANAGER")))
   {
      Float64 version = pLoad->GetVersion();

      if ( 1.0 <= version && version <= 2.0 )
      {
         if ( 2.0 <= version )
         {
            // beginning with version 2, a time stamp was added
            WBFL::System::ClockTy time;
            pLoad->Property(_T("TimeStamp"),&time);
            m_LastSavedTime = WBFL::System::Time((WBFL::System::ClockTy)time);
         }
         else
         {
            m_LastSavedTime = WBFL::System::Time(); // now
         }

         auto it = m_Libraries.begin();
         auto end = m_Libraries.end();
         for (; it != end; it++)
         {
            ILibrary* pLib = (*it).get();

            std::_tstring key;
            if ( pLoad->BeginUnit(_T("LIBRARY_MANAGER_ENTRY")) )
            {
               if (pLoad->Property(_T("LIBRARY_NAME"), &key) )
               {
                  while ( key != pLib->GetIdName() )
                  {
                     // The current library in the library manager and the library data
                     // in the file don't match up because a library has been depreciated.

                     if ( !pLib->IsDepreciated() )
                     {
                        // the names don't match and the library isn't depreciated... 
                        // something is wrong with the data
                        THROW_LOAD(InvalidFileFormat,pLoad);
                     }

                     // The data for the depreciated library is missing from the file.
                     // Skip libraries until there is a match between the data and the library manager
                     // or we run out of libraries

                     it++; // next library
                     if ( it == m_Libraries.end() )
                     {
                        // we ran out of libraries so the data can't be read (so the data is unknown)
                        THROW_LOAD(InvalidFileFormat,pLoad);
                     }

                     pLib = (*it).get();
                     // at the top of this while loop, check to see if the names match
                  }

                  //ASSERT(key==pLib->GetIdName());

                  if (!pLib->LoadMe(pLoad))    // load library
                  {
                        THROW_LOAD(BadRead,pLoad);
                  }
               }

               if(!pLoad->EndUnit())
               {
                  THROW_LOAD(InvalidFileFormat,pLoad);
               }
            } 
         } // for
      }
      else
      {
         // File is wrong version - need to puke
         THROW_LOAD(BadVersion,pLoad);
      }
   }
   else
   {
      THROW_LOAD(InvalidFileFormat,pLoad);
   }

   if(!pLoad->EndUnit())
   {
      THROW_LOAD(InvalidFileFormat,pLoad);
   }

   return true;
}
