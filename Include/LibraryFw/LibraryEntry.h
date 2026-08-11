///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2026  Washington State Department of Transportation
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

#include <memory>

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
      ///
      /// AddRef()/Release()/GetRefCount() are an application-level "is this entry
      /// currently referenced by external model data" usage counter, layered on top
      /// of (and independent from) the std::shared_ptr machinery that actually owns
      /// entry memory (see Library::m_EntryList / LibraryManager::m_Libraries).
      /// Despite the COM-style naming, this counter has nothing to do with object
      /// lifetime/deletion -- see Release()'s doc comment below.
      class LIBRARYFWCLASS LibraryEntry
      {
      public:
         LibraryEntry() = default;

         // Copy ctor/operator=/dtor are intentionally hand-written, not = default.
         // CopyValuesAndAttributes() deliberately excludes m_UsageRefCnt (a copy/assignment
         // target must never inherit the source's "in use" count). A defaulted copy
         // ctor or operator= would copy m_UsageRefCnt too, reviving the exact bug this
         // hand-written code prevents. The dtor is user-declared only for its
         // CHECKX(!m_UsageRefCnt,...) diagnostic and must stay virtual regardless (this is
         // a polymorphic base). Do not "modernize" these to = default.
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

         /// @brief Return a pointer to our library, or nullptr if the library has
         /// been destroyed, or if this entry was added to its library before that
         /// library was itself registered with a LibraryManager via AddLibrary()
         /// (see AddLibrary()'s doc comment).
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
         std::weak_ptr<const ILibrary> m_pLibrary;
         mutable Uint32 m_UsageRefCnt = 0;
         bool              m_IsEditingEnabled = true;
         bool m_bCanCopy = true;

      };
   };
};
