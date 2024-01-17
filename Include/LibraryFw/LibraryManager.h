///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <vector>
#include <memory>
#include <LibraryFw\LibraryFwExp.h>
#include <LibraryFw\ILibrary.h>
#include <System\Time.h>

namespace WBFL
{
   namespace Library
   {
      struct LIBRARYFWCLASS EntryUsageRecord
      {
         std::_tstring LibName;   // name of the library the contains the entry
         std::_tstring EntryName; // name of the library entry
         bool bEditable;        // true if the entry can be edited

         bool operator<(const EntryUsageRecord& other) const
         {
            return LibName < other.LibName;
         }

         bool operator==(const EntryUsageRecord& other) const
         {
            return (LibName == other.LibName)
               && (EntryName == other.EntryName) 
               && (bEditable == other.bEditable);
         }
      };

      /// @brief keeps a list of all current libraries
      /// This class provides a container for all defined system libraries
      class LIBRARYFWCLASS LibraryManager
      {
      public:
         LibraryManager() = default;
         LibraryManager(const LibraryManager&) = delete;
         virtual ~LibraryManager() = default;

         LibraryManager& operator=(const LibraryManager&) = delete;

         /// @brief Add a new library to the list. The library manager takes ownership of 
         /// the pointer and will delete it. Hence, you must create the library on
         /// the heap.
         IndexType AddLibrary(ILibrary* pLibrary);

         /// @brief Get manager's name
         std::_tstring GetName() const;

         /// @brief Set manager's name
         void SetName(LPCTSTR name);

         /// @brief Get the identifier name of a library based on its index
         std::_tstring GetLibraryIdName(IndexType index) const;

         /// @brief Get the display name of a library based on its index
         std::_tstring GetLibraryDisplayName(IndexType index) const;

         /// @brief Get a pointer to a library based on its index
         ILibrary* GetLibrary(IndexType index);
         const ILibrary* GetLibrary(IndexType index) const;

         /// @brief Get a pointer to a library based on its display name
         ILibrary* GetLibrary(LPCTSTR displayName);
         const ILibrary* GetLibrary(LPCTSTR displayName) const;

         /// @brief Get the index of a library based on its display name
         //// Returns -1 if no library exists.
         IndexType GetIndex(LPCTSTR displayName) const;

         /// @brief Clears all entries from all contained libraries. This function can
         /// be dangerous because it will try to delete entries regardless if
         /// they have outstanding references.
         virtual void ClearAllEntries();

         /// @brief Clears libraries from collection
         virtual void ClearLibraries();

         /// @brief set flags to enable (or disable) editing for all entries in all libraries
         virtual void EnableEditingForAllEntries(bool enable);

         /// @brief Save to structured storage
         virtual bool SaveMe(WBFL::System::IStructuredSave* pSave);

         /// @brief Load from structured storage. This function will load the library. It
         /// should only be called once during the lifetime of this class.
         virtual bool LoadMe(WBFL::System::IStructuredLoad* pLoad);

         /// @brief Get number of libraries in manager
         IndexType GetLibraryCount() const;

         bool IsDepreciated(IndexType idx) const;

         const WBFL::System::Time& GetTimeStamp() const;

         std::vector<EntryUsageRecord> GetInUseLibraryEntries() const;

      protected:
         using LibraryEntryType = std::shared_ptr<ILibrary>;
         using LibraryContainerType = std::vector<LibraryEntryType>;
         LibraryContainerType m_Libraries;

         WBFL::System::Time m_LastSavedTime;

      private:
         std::_tstring m_Name = _T("");
      };
   };
};
