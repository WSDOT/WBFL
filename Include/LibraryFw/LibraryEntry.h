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

#include <LibraryFw\LibraryFwExp.h>
#include <LibraryFw/LibraryHints.h>

namespace WBFL
{
   namespace System
   {
      class IStructuredSave;
      class IStructuredLoad;
   };

   namespace Library
   {
      class ILibrary;

      /// @brief abstract base class for library entries. 
      /// this class provides a base implementation for library entries.
      class LIBRARYFWCLASS LibraryEntry
      {
      public:
         LibraryEntry() = default;
         LibraryEntry(const LibraryEntry& rOther);

         virtual ~LibraryEntry();

         LibraryEntry& operator=(const LibraryEntry& rOther);

         /// @brief Edit the entry. if allowEditing is false, the entry may be viewed,
         /// but values may not be changed.
         /// Return true if edit is to be accepted, false if edit is cancelled.
         /// It is up to the implementer of this class to insure that the entry
         /// is not changed if the edit is cancelled.
         virtual bool Edit(bool allowEditing, int nPage = 0) = 0;

         /// @brief Change the name of the entry
         void SetName(LPCTSTR name);

         /// @brief Get the name of the entry
         const std::_tstring& GetName() const;

         /// @brief Set a pointer back to our library
         void SetLibrary(const ILibrary* pLibrary);

         /// @brief Return a pointer to our library
         const ILibrary* GetLibrary() const;

         /// @brief Increment the reference count by one
         Uint32 AddRef() const;

         /// @brief Decrement the reference count by one
         /// This routine DOES NOT delete the entry when the count goes to zero. That
         /// is the job of higher sources (e.g., the Library).
         Uint32 Release() const;

         /// @brief Get the number of references to this entry
         Uint32 GetRefCount() const;

         /// @brief Returns true if the entry can be edited.
         bool IsEditingEnabled() const;

         /// @brief Enables or disables editing of entries
         void EnableEditing(bool enable);

         void EnableCopying(bool bEnable);
         bool IsCopyingEnabled() const;

         /// @brief Save to structured storage
         virtual bool SaveMe(WBFL::System::IStructuredSave* pSave) = 0;

         /// @brief Load from structured storage
         virtual bool LoadMe(WBFL::System::IStructuredLoad* pLoad) = 0;

      protected:
         void CopyValuesAndAttributes(const LibraryEntry& rOther);

      private:
         std::_tstring       m_Name;
         const ILibrary* m_pLibrary = nullptr;
         mutable Uint32 m_RefCnt = 0;
         bool              m_IsEditingEnabled = true;
         bool m_bCanCopy = true;

      };
   };
};
