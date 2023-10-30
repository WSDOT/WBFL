///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <LibraryFw\LibraryFwExp.h>
#include <LibraryFw\LibraryEntry.h>
#include <System\IStructuredSave.h>
#include <System\IStructuredLoad.h>
#include <set>

namespace WBFL
{
   namespace Library
   {
      class LIBRARYFWCLASS LibraryManager;

      using KeyListType = std::vector<std::_tstring>;
      using KeyListIterator = KeyListType::iterator;


      /// @brief A abstract generic library interface for storing LibraryEntries.
      ///
      /// USAGE NOTES:
      /// If you want to reference an entry in the library at run time, you should 
      /// reference it by its pointer, NOT by entry name/key. This is because the 
      /// name of an entry can be changed arbitrarily, but its memory address can not.
      ///
      /// Conversely, at Storage time you may reference entries by their name/key.
      ///
      /// All entries use counted pointer schemes. You must make calls to AddRef/Release
      /// on the entries every time you reference the entry. LookupEntry automatically
      /// makes a call to AddRef() when it is called.
      class LIBRARYFWCLASS ILibrary
      {
      public:
         virtual ~ILibrary() = default;

         /// @brief tell library who its manager is
         virtual void SetLibraryManager(LibraryManager* pLibraryManager) = 0;

         virtual LibraryManager* GetLibraryManager() const = 0;

         /// @brief See if an entry exists in the library. Return false if not.
         virtual bool IsEntry(LPCTSTR key) const = 0;

         /// @brief Get the number of references to this entry
         virtual Uint32 GetEntryRefCount(LPCTSTR key) const = 0;

         /// @brief Returns true if entry can be edited
         virtual bool IsEditingEnabled(LPCTSTR key) const = 0;

         /// @brief set flag which enables entry to be edited
         virtual void EnableEditing(LPCTSTR key, bool enable) = 0;

         /// @brief set flag which enables all entries in the library to be edited
         virtual void EnableEditingForAll(bool enable) = 0;

         virtual void EnableCopy(LPCTSTR key,bool enable) = 0;
         virtual bool IsCopyingEnabled(LPCTSTR key) const = 0;

         /// @brief Add a new default entry with the given name. Returns false if unsuccessful.
         virtual bool NewEntry(LPCTSTR key) = 0;

         /// @brief Create a clone of an existing entry (named key) and create a new entry
         /// named newkey. key must be in the library and newkey must not. 
         /// Returns false if unsuccessful.
         virtual bool CloneEntry(LPCTSTR key, LPCTSTR newkey) = 0;

         /// @brief Create a polymorphic clone of a library entry into this library.
         /// The type of newentry is checked to make sure it is correct and will 
         /// ASSERT if it is not.
         /// Returns false if newkey is not a unique name
         virtual bool  AddEntry(const LibraryEntry& rnewentry, LPCTSTR newkey) = 0;

         /// @brief Factory function to create an external polymorphic clone of a library entry. 
         /// You are responsible for deleting it.
         virtual std::unique_ptr<LibraryEntry> CreateEntryClone(LPCTSTR key) const = 0;

         /// @brief Open the editing interface for the given entry. Returns the following
         /// possible values:
         enum class EntryEditOutcome { Ok,            // Successful edit
                                 NotFound,      // Entry not found
                                 Cancelled,     // User cancelled edit
                                 RenameFailed}; // Rename failed because user tried to rename
                                                // the entry to a name that already is
                                                // in the library. Name rejected but other
                                                // edits retained.
                           
         virtual EntryEditOutcome EditEntry( LPCTSTR key,UINT nPage=0) = 0;

         /// @brief Rename an entry
         virtual bool RenameEntry( LPCTSTR oldKey, LPCTSTR newKey) = 0;

         /// @brief Remove an entry. Returns the following possible values:
         enum class EntryRemoveOutcome {Ok,            // Successful edit
                                   NotFound,      // Entry not found
                                   Referenced};   // Entry has outstanding references and cannot be removed

         virtual EntryRemoveOutcome RemoveEntry( LPCTSTR key ) = 0;

         /// @brief Remove all entries. Will assert if entries have outstanding references
         virtual void RemoveAll() = 0;

         /// @brief Save to structured storage
         virtual bool SaveMe(WBFL::System::IStructuredSave* pSave) = 0;

         /// @brief Load from structured storage
         virtual bool LoadMe(WBFL::System::IStructuredLoad* pLoad) = 0;

         /// @brief Change the display name of the library.
         virtual void SetDisplayName(LPCTSTR name) = 0;

         /// @brief Get the display name of the library
         virtual std::_tstring GetDisplayName() const = 0;

         /// @brief Get the identification name of the library
         virtual std::_tstring GetIdName() const = 0;

         /// @brief Generate a name that's guaranteed not to be in the library
         virtual std::_tstring GetUniqueEntryName(LPCTSTR lpszBaseName=_T("New Entry-")) const = 0; 

         /// @brief return a list of the names of all entries in the library.
         virtual void KeyList(KeyListType& rList) const = 0;

         /// @brief Get the number of entries in the library
         virtual IndexType GetCount( ) const = 0;

         /// @brief Returns the minimum number of required library entires
         virtual IndexType GetMinCount() const = 0;

         /// @brief Get a const pointer to an entry by index
         /// Returns nullptr if out of range and asserts
         /// DOES NOT INCREASE REFERENCE COUNT!
         virtual const LibraryEntry* GetEntry(LPCTSTR key) const  = 0;


         /// @brief Is the library empty?
         virtual bool IsEmpty( ) const = 0;

         /// @brief Returns true if this is an old library that is no longer used
         virtual bool IsDepreciated() const = 0;

         virtual std::set<std::_tstring> GetReservedNamesList() const = 0;
         virtual void AddReservedName(LPCTSTR strName) = 0;
         virtual bool IsReservedName(LPCTSTR strName) const = 0;
      };
   };
};
