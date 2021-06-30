///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   libLibraryManager
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
libLibraryManager::libLibraryManager() :
m_Name(_T(""))
{
}

libLibraryManager::~libLibraryManager()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void libLibraryManager::SetName(LPCTSTR name) 
{
   m_Name =name;
}

std::_tstring libLibraryManager::GetName() const
{
   return m_Name;
}

CollectionIndexType libLibraryManager::AddLibrary(libILibrary* pLibrary)
{
   PRECONDITION(pLibrary);
   libILibrary* plib = GetLibrary(pLibrary->GetIdName().c_str());
   PRECONDITIONX(!plib,_T("Libraries must have unique id names"));
   pLibrary->SetLibraryManager(this);

   m_Libraries.emplace_back(pLibrary);
   return m_Libraries.size()-1;
}

CollectionIndexType libLibraryManager::GetLibraryCount() const
{
   return m_Libraries.size();
}

bool libLibraryManager::IsDepreciated(CollectionIndexType idx) const
{
   const libILibrary* pLib = GetLibrary(idx);
   return pLib->IsDepreciated();
}

sysTime libLibraryManager::GetTimeStamp() const
{
   return m_LastSavedTime;
}

std::_tstring libLibraryManager::GetLibraryIdName(CollectionIndexType index) const
{
   const libILibrary* plib;
   if (0 <= index && index < m_Libraries.size())
   {
       plib = m_Libraries[index].get();
   }
   else
   {
      PRECONDITION(0);
   }

   return plib->GetIdName();
}

std::_tstring libLibraryManager::GetLibraryDisplayName(CollectionIndexType index) const
{
   const libILibrary* plib;
   if (0 <= index && index < m_Libraries.size())
   {
       plib = m_Libraries[index].get();
   }
   else
   {
      PRECONDITION(0);
   }

   return plib->GetDisplayName();
}

libILibrary* libLibraryManager::GetLibrary(CollectionIndexType index)
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

const libILibrary* libLibraryManager::GetLibrary(CollectionIndexType index) const
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

libILibrary* libLibraryManager::GetLibrary(LPCTSTR displayName)
{
   std::_tstring name(displayName);
   for(LibraryIterator it=m_Libraries.begin(); it!=m_Libraries.end(); it++)
   {
      if ((*it)->GetDisplayName()==name)
      {
         return (*it).get();
      }
   }
   return nullptr;
}


const libILibrary* libLibraryManager::GetLibrary(LPCTSTR displayName) const
{
   std::_tstring name(displayName);
   for(ConstLibraryIterator it=m_Libraries.begin(); it!=m_Libraries.end(); it++)
   {
      if ((*it)->GetDisplayName()==name)
      {
         return (*it).get();
      }
   }
   return nullptr;
}

CollectionIndexType libLibraryManager::GetIndex(LPCTSTR displayName) const
{
   CollectionIndexType idx = 0;
   std::_tstring name(displayName);
   for(ConstLibraryIterator it=m_Libraries.begin(); it!=m_Libraries.end(); it++)
   {
      if ((*it)->GetDisplayName()==name)
      {
         return idx;
      }
      idx++;
   }
   return INVALID_INDEX;
}


void libLibraryManager::ClearAllEntries()
{
   for(LibraryIterator it=m_Libraries.begin(); it!=m_Libraries.end(); it++)
   {
      (*it)->RemoveAll();
   }
}

void libLibraryManager::ClearLibraries()
{
   ClearAllEntries();
   m_Libraries.clear();
}


void libLibraryManager::EnableEditingForAllEntries(bool enable)
{
   for(LibraryIterator it=m_Libraries.begin(); it!=m_Libraries.end(); it++)
   {
      (*it)->EnableEditingForAll(enable);
   }
}

std::vector<libEntryUsageRecord> libLibraryManager::GetInUseLibraryEntries() const
{
   std::vector<libEntryUsageRecord> records;

   for (ConstLibraryIterator it = m_Libraries.begin(); it!=m_Libraries.end(); it++)
   {
      const libILibrary* pLibrary = (*it).get();
      std::_tstring strLibName = pLibrary->GetDisplayName();

      libKeyListType key_list;
      pLibrary->KeyList(key_list);
      libKeyListIterator key_iter;
      for (key_iter = key_list.begin(); key_iter != key_list.end(); key_iter++ )
      {
         std::_tstring key = (*key_iter);
         const libLibraryEntry* pEntry = pLibrary->GetEntry(key.c_str());
         if ( 0 < pEntry->GetRefCount() )
         {
            libEntryUsageRecord record;
            record.LibName = strLibName;
            record.EntryName = pEntry->GetName();
            record.bEditable = pEntry->IsEditingEnabled();

            records.push_back(record);
         }
      }
   }

   return records;
}

bool libLibraryManager::SaveMe(sysIStructuredSave* pSave)
{
   // not much data for a library manager 
   pSave->BeginUnit(_T("LIBRARY_MANAGER"), 2.0);

   sysTime time; // now
   pSave->Property(_T("TimeStamp"),time.Seconds());
   for (LibraryIterator it = m_Libraries.begin(); it!=m_Libraries.end(); it++)
   {
      libILibrary* pLibrary = (*it).get();

      if ( !pLibrary->IsDepreciated() )
      {
         // only save the library if it is not depreciated
         pSave->BeginUnit(_T("LIBRARY_MANAGER_ENTRY"),1.0);
         pSave->Property(_T("LIBRARY_NAME"), (*it)->GetIdName().c_str());

         (*it)->SaveMe(pSave);

         pSave->EndUnit();
      }
   }
   pSave->EndUnit();
   return true;
}

bool libLibraryManager::LoadMe(sysIStructuredLoad* pLoad)
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
            ClockTy time;
            pLoad->Property(_T("TimeStamp"),&time);
            m_LastSavedTime = sysTime((ClockTy)time);
         }
         else
         {
            m_LastSavedTime = sysTime(); // now
         }

         for (LibraryIterator it = m_Libraries.begin(); it!=m_Libraries.end(); it++)
         {
            libILibrary* pLib = (*it).get();


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

//======================== ACCESS     =======================================

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
#include <typeinfo>
bool libLibraryManager::AssertValid() const
{
   for (ConstLibraryIterator it = m_Libraries.begin(); it!=m_Libraries.end(); it++)
   {
      const std::shared_ptr<libILibrary>& libType = *it;
      libILibrary* pLib = libType.get();
      const type_info& ti = typeid( pLib );
      std::string name( ti.name() );
#if defined _WIN64
      std::string lib_type( "class libILibrary * __ptr64" );
#else
      std::string lib_type( "class libILibrary *" );
#endif
      if ( name != lib_type )
      {
         WATCH(_T("######## Bad library type"));
         return false; // bad name
      }
   }
   return true;
}

void libLibraryManager::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for libLibraryManager") << endl;
   os << _T("  Name = ") << m_Name << endl;
   os << _T("  Dumping ") <<m_Libraries.size()<<_T(" libraries:")<<endl;
   for (ConstLibraryIterator it = m_Libraries.begin(); it!=m_Libraries.end(); it++)
   {
      (*it)->Dump(os);
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool libLibraryManager::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("libLibraryManager");

   // tested in main unit test routine for package

   TESTME_EPILOG("LibraryManager");
}
#endif // _UNITTEST
