///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#ifndef INCLUDED_LIBRARY_LIBRARYMANAGER_H_
#define INCLUDED_LIBRARY_LIBRARYMANAGER_H_
#pragma once

// SYSTEM INCLUDES
//
#include <vector>
#include <boost\shared_ptr.hpp>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//
#if !defined INCLUDED_LIBRARYFW_LIBRARYFWEXP_H_
#include <LibraryFw\LibraryFwExp.h>
#endif

#if !defined INCLUDED_LIBRARYFW_ILIBRARY_H_
#include <LibraryFw\ILibrary.h>
#endif

#if !defined INCLUDED_SYSTEM_TIME_H_
#include <System\Time.h>
#endif

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

struct LIBRARYFWCLASS libEntryUsageRecord
{
   std::_tstring LibName;   // name of the library the contains the entry
   std::_tstring EntryName; // name of the library entry
   bool bEditable;        // true if the entry can be editied

   bool operator<(const libEntryUsageRecord& other) const
   {
      return LibName < other.LibName;
   }

   bool operator==(const libEntryUsageRecord& other) const
   {
      return (LibName == other.LibName)
         && (EntryName == other.EntryName) 
         && (bEditable == other.bEditable);
   }
};

/*****************************************************************************
CLASS 
   libLibraryManager

   Library manager - keeps a list of all current libraries


DESCRIPTION
   This class provides a container for all defined system libraries


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 07.09.1998 : Created file
*****************************************************************************/

class LIBRARYFWCLASS libLibraryManager
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   libLibraryManager();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~libLibraryManager();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Add a new library to the list. The library manager takes ownership of 
   // the pointer and will delete it. Hence, you must create the library on
   // the heap.
   CollectionIndexType AddLibrary(libILibrary* pLibrary);

   // GROUP: ACCESS
   //------------------------------------------------------------------------
   // Get manager's name
   std::_tstring GetName() const;

   //------------------------------------------------------------------------
   // Set manager's name
   void SetName(LPCTSTR name);

   //------------------------------------------------------------------------
   // Get the identifier name of a library based on its index
   std::_tstring GetLibraryIdName(CollectionIndexType index) const;

   //------------------------------------------------------------------------
   // Get the display name of a library based on its index
   std::_tstring GetLibraryDisplayName(CollectionIndexType index) const;

   //------------------------------------------------------------------------
   // Get a pointer to a library based on its index
   libILibrary* GetLibrary(CollectionIndexType index);
   const libILibrary* GetLibrary(CollectionIndexType index) const;

   //------------------------------------------------------------------------
   // Get a pointer to a library based on its display name
   libILibrary* GetLibrary(LPCTSTR displayName);
   const libILibrary* GetLibrary(LPCTSTR displayName) const;

   //------------------------------------------------------------------------
   // Get the index of a library based on its display name
   // Returns -1 if no library exists.
   CollectionIndexType GetIndex(LPCTSTR displayName) const;

   //------------------------------------------------------------------------
   // Clears all entries from all contained libraries. This function can
   // be dangerous because it will try to delete entries regardless if
   // they have outstanding references.
   virtual void ClearAllEntries();

   //------------------------------------------------------------------------
   // Clears libraries from collection
   virtual void ClearLibraries();

   //------------------------------------------------------------------------
   // set flags to enable (or disable) editing for all entries in all libraries
   virtual void EnableEditingForAllEntries(bool enable);

   //------------------------------------------------------------------------
   // Save to structured storage
   virtual bool SaveMe(sysIStructuredSave* pSave);

   //------------------------------------------------------------------------
   // Load from structured storage. This function will load the library. It
   // should only be called once during the lifetime of this class.
   virtual bool LoadMe(sysIStructuredLoad* pLoad);

   // GROUP: INQUIRY
   //------------------------------------------------------------------------
   // Get number of libraries in manager
   CollectionIndexType GetLibraryCount() const;

   bool IsDepreciated(CollectionIndexType idx) const;

   sysTime GetTimeStamp() const;

   std::vector<libEntryUsageRecord> GetInUseLibraryEntries() const;

protected:
   // GROUP: DATA MEMBERS
   typedef boost::shared_ptr<libILibrary> LibraryEntryType;
   typedef std::vector<LibraryEntryType>  LibraryContainerType;
   typedef LibraryContainerType::iterator LibraryIterator;
   typedef LibraryContainerType::const_iterator ConstLibraryIterator;
   //------------------------------------------------------------------------
   LibraryContainerType m_Libraries;

   sysTime m_LastSavedTime;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   //------------------------------------------------------------------------
   // Name of the manager
   std::_tstring m_Name;


   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   libLibraryManager(const libLibraryManager&);
   libLibraryManager& operator=(const libLibraryManager&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LIBRARY_LIBRARYMANAGER_H_
