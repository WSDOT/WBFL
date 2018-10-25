///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_LIBRARYFW_LIBRARY_H_
#define INCLUDED_LIBRARYFW_LIBRARY_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>
#include <set>
#include <boost\shared_ptr.hpp>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//
#include <Checks.h>
#include <LibraryFw\ILibrary.h>
#include <LibraryFw\LibraryHints.h>
#include <LibraryFw\UnitsMode.h>
#include <System\IStructuredSave.h>
#include <System\IStructuredLoad.h>
#include <System\XStructuredLoad.h>

// FORWARD DECLARATIONS
//
class LIBRARYFWCLASS libLibraryManager;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   libLibrary

   A generic library base class for storing LibraryEntries.


DESCRIPTION
   This class provides a generic interface for storing LibraryEntries


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 07.09.1998 : Created file
*****************************************************************************/
template<class T>
class libLibrary : public libILibrary
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   // idName must be a unique name (to other libraries added to a manager) and
   // must not contain any whitespace.
   // displayName is a name fit to be displayed by an editor
   libLibrary(const char* idName, const char* displayName, bool bIsDepreciated = false):
   m_IdName( idName ),
   m_DisplayName(displayName),
   m_bIsDepreciated(bIsDepreciated)
   {
      m_pLibraryManager = 0;
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~libLibrary()
   {
   }

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // tell library who its manager is
   void SetLibraryManager(libLibraryManager* pLibraryManager)
   {
      m_pLibraryManager = pLibraryManager;
   } // SetLibraryManager


   //------------------------------------------------------------------------
   // Get a pointer to my manager
   libLibraryManager* GetLibraryManager() const
   {
      return m_pLibraryManager;
   } // GetLibraryManager

   //------------------------------------------------------------------------
   // Add a new default entry with the given name. Returns false if 
   // unsuccessful, which likely means that an entry with the same name
   // already exists.
   bool NewEntry(const char* key)
   {
      if ( IsReservedName(key) )
         return false;

      // check if key exists already
      const T* pentry = LookupEntryPrv(key);

      if (!pentry)
      {
         // doesn't exist - add a new one.
         LibItem apentry( new T() );
         apentry->SetName(key);
         m_EntryList.insert(EntryList::value_type(key, apentry));
         return true;
      }
      else
         return false;
   } // NewEntry

   //------------------------------------------------------------------------
   // Add an entry based on another. key must be unique. Returns false if
   // failed.
   bool AddEntry( const T& rNewValue, const char* key, bool bAddRef = false )
   {
      if ( IsReservedName(key) )
         return false;

      // check if key exists already
      const T* pentry = LookupEntryPrv(key);

      if (!pentry)
      {
         // doesn't exist - add it
         LibItem apentry( new T(rNewValue) );
         if ( bAddRef )
            apentry->AddRef();

         apentry->SetName(key);

         std::pair<EntryListIterator,bool> result;
         result = m_EntryList.insert(EntryList::value_type(key, apentry));
         return result.second;
      }
      else
         return false;
   } // AddEntry

   //------------------------------------------------------------------------
   // Create a clone of an existing entry (named key) and create a new entry
   // named newkey. key must be in the library and newkey must not. 
   // Returns false if unsuccessful.
   bool CloneEntry(const char* key, const char* newkey)
   {
      if ( IsReservedName(newkey) )
         return false;

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
      else if (std::string(key)==std::string(newkey))
      {
         // can't clone yourself
         return false;
      }
      else
      {
         // copy
         LibItem apentry( new T(*pentry) );
         apentry->SetName(newkey);
         m_EntryList.insert(EntryList::value_type(newkey, apentry));
         return true;
      }
   }


   //------------------------------------------------------------------------
   // Open the editing interface for the given entry. 
   libILibrary::EntryEditOutcome EditEntry( const char* key, libUnitsMode::Mode mode )
   {
      T* pentry = LookupEntryPrv(key);
      if (!pentry)
      {
         // Attempting to edit an unknown entry - not good form.
         return libILibrary::NotFound;
      }
      else
      {
         if (pentry->Edit(mode, pentry->IsEditingEnabled()))
         {
            int hint = LibraryHints::EntryEdited;
            // it's a tough call what to do here if the user changes the name of the 
            // entry to be the same as another item in the library. The only safe thing to
            // do is to abort the edit. This may piss some folks off though.
            
            std::string nam = pentry->GetName();
            if (nam!=std::string(key))
            {
               hint |= LibraryHints::EntryRenamed;

               T* apentry = LookupEntryPrv(nam.c_str());
               if(apentry)
               {
                  // user gave entry a name that already exists - too bad.
                  pentry->SetName(key);
                  return libILibrary::RenameFailed;
               }
               else
               {
                  // must delete old location and move it to a new one
                  if (!this->RenameEntry(key, nam.c_str()))
                     return libILibrary::RenameFailed;
               }
            }

            pentry->Notify(hint);
            
         }
         else
         {
            // restore back to original
            return libILibrary::Cancelled;
         }
      }
      return libILibrary::Ok;
   } // EditEntry

   //------------------------------------------------------------------------
   // Return a pointer to an entry based on its key. Returns zero if failed.
   // NOTE: this call causes a call to AddRef() for the given entry. You must
   //       call Release() on the entry when you are done with it.
   const T*  LookupEntry( const char* key) const
   {
      EntryListConstIterator tmp = m_EntryList.find(key);
      if (tmp != m_EntryList.end() )
      {
         (*tmp).second->AddRef();     // increment reference count
         return (*tmp).second.get();
      }
      else
         return 0;
   }

   //------------------------------------------------------------------------
   // get the key of an existing entry in the library
   bool GetEntryKey( const T& rValue, std::string& rkey ) const
   {
      // linear search to compare pointers
      for (EntryListConstIterator it = m_EntryList.begin(); it!=m_EntryList.end(); it++)
      {
         if (&rValue==(*it).second.get())
         {
            rkey = (*it).first;
            return true;
         }
      }
      return false;      
   }

   //------------------------------------------------------------------------
   // Update an existing entry by copying another to it.
   bool UpdateEntry( const T& rNewValue, const char* key )
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
         std::string onam = pentry->GetName();
         if (onam != key)
            pentry->SetName(key);

         pentry->Notify(LibraryHints::EntryEdited);

         return true;
      }
   }

   //------------------------------------------------------------------------
   // Rename an entry
   bool RenameEntry( const char* oldKey, const char* newKey)
   {
      if ( IsReservedName(newKey) )
         return false;

      T* pentry = LookupEntryPrv(newKey);
      if (pentry)
         // new already exists
         return false;
      else
      {

         EntryListIterator tmp = m_EntryList.find(oldKey);
         if (tmp != m_EntryList.end() )
         {
            // must continue to use same pointer
            boost::shared_ptr<T> apentry = (*tmp).second;
            // erase old entry
            int st = m_EntryList.erase(oldKey);
            CHECK(st==1);
            // reinsert pointer with new name
            apentry->SetName(newKey);
            bool suc = (m_EntryList.insert(EntryList::value_type(newKey, LibItem(apentry))).second);
            CHECK(suc);

            apentry->Notify(LibraryHints::EntryRenamed);

            return suc;
         }
         else
            // not found
            return false;
      }
   }

   //------------------------------------------------------------------------
   // Remove an entry. 
   libILibrary::EntryRemoveOutcome RemoveEntry( const char* key )
   {
      EntryListIterator tmp = m_EntryList.find(key);
      if (tmp != m_EntryList.end() )
      {
         if ((*tmp).second->GetRefCount()==0)
         {
            m_EntryList.erase(tmp);
            return libILibrary::RemOk;
         }
         else
         {
            return libILibrary::RemReferenced;
         }
      }
      else
         return libILibrary::RemNotFound;
   }


   //------------------------------------------------------------------------
   // Remove all entries. Will assert if entries have outstanding references
   void RemoveAll()
   {
      m_EntryList.clear();
   }

   //------------------------------------------------------------------------
   // Save to structured storage
   bool SaveMe(sysIStructuredSave* pSave)
   {
      // not much data for a library
      pSave->BeginUnit("LIBRARY", 1.0);
      pSave->Property("LIBRARY_ID_NAME", m_IdName.c_str());
      pSave->Property("LIBRARY_DISPLAY_NAME", m_DisplayName.c_str());
      for (EntryListIterator it = m_EntryList.begin(); it!=m_EntryList.end(); it++)
      {
         pSave->BeginUnit("LIBRARY_ENTRY",1.0);
         pSave->Property("ENTRY_KEY", (*it).first.c_str());

         (*it).second->SaveMe(pSave);

         pSave->EndUnit();
      }
      pSave->EndUnit();
      return true;
   }

   //------------------------------------------------------------------------
   // Load from structured storage
   bool LoadMe(sysIStructuredLoad* pLoad)
   {
      // load library and its entries
      if (pLoad->BeginUnit("LIBRARY"))
      {
         if (pLoad->GetVersion()==1.0)
         {
            if (pLoad->Property("LIBRARY_ID_NAME", &m_IdName))
            {
               if (pLoad->Property("LIBRARY_DISPLAY_NAME", &m_DisplayName))
               {
                  std::string key;
                  while (pLoad->BeginUnit("LIBRARY_ENTRY"))
                  {
                     if (pLoad->Property("ENTRY_KEY", &key))
                     {
                        // allocate a new item
                        LibItem itm(new T);
                        if (itm.get()==0)
                           THROW_LOAD(MemoryError,pLoad);

                        if (itm->LoadMe(pLoad))
                        {
                           // store it in the map
                           if(itm->GetName()==key)
                           {
                              m_EntryList.insert(EntryList::value_type(key,LibItem(itm)));
                           }
                           else
                              THROW_LOAD(InvalidFileFormat,pLoad);  // key doesn't match name
                        }
                        else
                           THROW_LOAD(BadRead,pLoad);

                        if(!pLoad->EndUnit())
                           THROW_LOAD(InvalidFileFormat,pLoad);
                     }
                     else
                        THROW_LOAD(InvalidFileFormat,pLoad);
                  } // while
               }
               else
                  THROW_LOAD(InvalidFileFormat,pLoad);
            }
            else
               THROW_LOAD(InvalidFileFormat,pLoad);
         }
         else
            // File is wrong version - need to puke
            THROW_LOAD(BadVersion,pLoad);
      }
      else
         return false;

      if(!pLoad->EndUnit())
         THROW_LOAD(InvalidFileFormat,pLoad);

      return true;
   }


   //------------------------------------------------------------------------
   // Change the display name of the library.
   void SetDisplayName(const char* name)
   {
      m_DisplayName = name;
   }

   //------------------------------------------------------------------------
   // Get the name of the library
   std::string GetDisplayName() const
   {
      return m_DisplayName;
   }

   //------------------------------------------------------------------------
   // Get the idenfication name of the library
   std::string GetIdName() const
   {
      return m_IdName;
   }

   // ACCESS
   //------------------------------------------------------------------------
   // return a list of the names of all entries in the library.
   void KeyList(libKeyListType& rList) const
   {
      rList.clear();
      for (EntryListConstIterator it = m_EntryList.begin(); it!=m_EntryList.end(); it++)
      {
         rList.push_back(std::string((*it).first));
      }
   }

   // INQUIRY
   //------------------------------------------------------------------------
   // Get the number of entries in the library
   int GetCount( ) const
   {
      return m_EntryList.size();
   }

   //------------------------------------------------------------------------
   // Is the library empty?
   bool IsEmpty( ) const
   {
      return m_EntryList.size()==0;
   }

   bool IsDepreciated() const
   {
      return m_bIsDepreciated;
   }

   //------------------------------------------------------------------------
   // Get a const pointer to an entry by index
   // Returns NULL if out of range and asserts
   // DOES NOT INCREASE REFERENCE COUNT!
   const libLibraryEntry* GetEntry(const char* key) const
   {
      const libLibraryEntry* pent = LookupEntry(key);
      if (pent!=0)
         pent->Release();
      
      return pent;
   }

   //------------------------------------------------------------------------
   // See if an entry exists in the library
   bool IsEntry(const char* key) const 
   {
      const T* pent = LookupEntry(key);
      if (pent!=0)
         pent->Release();
      return (pent!=0);
   }

   //------------------------------------------------------------------------
   // Get the number of references to this entry
   Uint32 GetEntryRefCount(const char* key) const
   {
      const T* pent = LookupEntry(key);
      if (pent!=0)
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

   //------------------------------------------------------------------------
   // Returns true if entry can be edited
   virtual bool IsEditingEnabled(const char* key) const
   {
      const T* pent = LookupEntry(key);
      if (pent!=0)
      {
         pent->Release();
         return pent->IsEditingEnabled();
      }
      else
      {
         CHECK(0); // bad key
         return 0;
      }
   }

   //------------------------------------------------------------------------
   // set flag which enables entry to be edited
   virtual void EnableEditing(const char* key, bool enable) 
   {
      T* pent = LookupEntryPrv(key);
      if (pent!=0)
         pent->EnableEditing(enable);
      else
         CHECK(0); // bad key
   }

   //------------------------------------------------------------------------
   // set flag which enables all entries in the library to be edited
   virtual void EnableEditingForAll(bool enable)
   {
      for (EntryListIterator it = m_EntryList.begin(); it!=m_EntryList.end(); it++)
      {
         (*it).second->EnableEditing(enable);
      }
   }

   //------------------------------------------------------------------------
   // Generate a name that's guaranteed not to be in the library
   std::string GetUniqueEntryName() const 
   {
      // name will be in the form on "Unnamednn" where nn is some number.
      bool unique=false;
      std::stringstream sstr;
      for (int i=0; true; i++)
      {
         std::ostringstream sstr;
         sstr << "New Entry-"<<i;
         const T* pent = LookupEntry(sstr.str().c_str());
         if (pent==0)
            return sstr.str();
         else
            pent->Release();
      }
      return "Error"; // power failure will happen before we ever get here.
   }

   //------------------------------------------------------------------------
   // Create a polymorphic clone of a library entry into this library. 
   // The type of newentry is checked to make sure it is correct and will 
   // ASSERT if it is not.
   // Returns false if newkey is not a unique name
   virtual bool  AddEntry(const libLibraryEntry& newentry, const char* newkey)
   {
      const T* pent = dynamic_cast<const T*>(&newentry);
      if (pent==0)
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

   //------------------------------------------------------------------------
   // Factory function to create an external polymorphic clone of a library entry. 
   // You are responsible for deleting it.
   virtual libLibraryEntry* CreateEntryClone(const char* key) const
   {
      const T* pent = LookupEntry(key);
      if (pent!=0)
      {
         pent->Release(); // balances the AddRef call in LookupEntry
         return new T(*pent);
      }
      else
         return 0;
   }

   std::set<std::string> GetReservedNamesList() const
   {
      return m_ReservedNamesList;
   }

   void AddReservedName(const char* strName)
   {
      m_ReservedNamesList.insert( strName );
   }

   bool IsReservedName(const char* strName) const
   {
      std::set<std::string>::const_iterator found = m_ReservedNamesList.find(strName);
      return (found == m_ReservedNamesList.end() ? false : true);
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::string m_IdName;
   std::string m_DisplayName;
   bool m_bIsDepreciated;
   libLibraryManager* m_pLibraryManager;

   typedef boost::shared_ptr<T>         LibItem;
   typedef typename std::map<std::string, LibItem >        EntryList;
   typedef typename EntryList::iterator                    EntryListIterator;
   typedef typename EntryList::const_iterator              EntryListConstIterator;

   EntryList m_EntryList;

   std::set<std::string> m_ReservedNamesList;


   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   libLibrary() {}

   // Prevent accidental copying and assignment
   libLibrary(const libLibrary&) {}
   libLibrary& operator=(const libLibrary&) {return *this;}

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Return a non-const pointer to an entry based on its key. Returns zero if failed
   T*  LookupEntryPrv( const char* key)
   {
      // if the name is on the reserved list, get outta here
      if ( IsReservedName(key) )
         return 0;

      EntryListIterator tmp = m_EntryList.find(key);
      if (tmp != m_EntryList.end() )
         return (*tmp).second.get();
      else
         return 0;
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const
   {
      os << "Dump for libLibrary: " << m_IdName << endl;
      os << "  Display Name      = "<< m_DisplayName<<endl;
      os << "  m_pLibraryManager = " << m_pLibraryManager << endl;
      os << "  Library Entries: " << m_EntryList.size() << endl;

      for (EntryListConstIterator it = m_EntryList.begin(); it!=m_EntryList.end(); it++)
      {
         os << "Dump for Entry: "<< (*it).first << endl;
         (*it).second->Dump(os);
      }

   }
   #endif // _DEBUG
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LIBRARYFW_LIBRARY_H_
