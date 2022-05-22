///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifndef INCLUDED_LIBRARYFW_ILIBRARY_H_
#define INCLUDED_LIBRARYFW_ILIBRARY_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <LibraryFw\LibraryFwExp.h>
#include <LibraryFw\LibraryEntry.h>
#include <System\IStructuredSave.h>
#include <System\IStructuredLoad.h>
#include <set>

// FORWARD DECLARATIONS
//
class LIBRARYFWCLASS libLibraryManager;


// MISCELLANEOUS
//
#define libKeyListType std::vector< std::_tstring >
typedef libKeyListType::iterator libKeyListIterator;


/*****************************************************************************
CLASS 
   libILibrary

   A abstract generic library interface for storing LibraryEntries.

   USAGE NOTES:
   If you want to reference an entry in the library at run time, you should 
   reference it by its pointer, NOT by entry name/key. This is because the 
   name of an entry can be changed arbitrarly, but its memory address can not.

   Conversely, at Storage time you may reference entries by their name/key.

   All entries use counted pointer schemes. You must make calls to AddRef/Release
   on the entries every time you reference the entry. LookupEntry automatically
   makes a call to AddRef() when it is called.


DESCRIPTION

LOG
   rdp : 07.09.1998 : Created file
*****************************************************************************/

class LIBRARYFWCLASS libILibrary
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   virtual ~libILibrary() {}

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // tell library who its manager is
   virtual void SetLibraryManager(libLibraryManager* pLibraryManager) = 0;

   //------------------------------------------------------------------------
   virtual libLibraryManager* GetLibraryManager() const = 0;

   //------------------------------------------------------------------------
   // See if an entry exists in the library. Return false if not.
   virtual bool IsEntry(LPCTSTR key) const = 0;

   //------------------------------------------------------------------------
   // Get the number of references to this entry
   virtual Uint32 GetEntryRefCount(LPCTSTR key) const = 0;

   //------------------------------------------------------------------------
   // Returns true if entry can be edited
   virtual bool IsEditingEnabled(LPCTSTR key) const = 0;

   //------------------------------------------------------------------------
   // set flag which enables entry to be edited
   virtual void EnableEditing(LPCTSTR key, bool enable) = 0;

   //------------------------------------------------------------------------
   // set flag which enables all entries in the library to be edited
   virtual void EnableEditingForAll(bool enable) = 0;

   virtual void EnableCopy(LPCTSTR key,bool enable) = 0;
   virtual bool IsCopyingEnabled(LPCTSTR key) const = 0;

   //------------------------------------------------------------------------
   // Add a new default entry with the given name. Returns false if unsuccessful.
   virtual bool NewEntry(LPCTSTR key) = 0;

   //------------------------------------------------------------------------
   // Create a clone of an existing entry (named key) and create a new entry
   // named newkey. key must be in the library and newkey must not. 
   // Returns false if unsuccessful.
   virtual bool CloneEntry(LPCTSTR key, LPCTSTR newkey) = 0;

   //------------------------------------------------------------------------
   // Create a polymorphic clone of a library entry into this library. 
   // The type of newentry is checked to make sure it is correct and will 
   // ASSERT if it is not.
   // Returns false if newkey is not a unique name
   virtual bool  AddEntry(const libLibraryEntry& rnewentry, LPCTSTR newkey) = 0;

   //------------------------------------------------------------------------
   // Factory function to create an external polymorphic clone of a library entry. 
   // You are responsible for deleting it.
   virtual libLibraryEntry* CreateEntryClone(LPCTSTR key) const = 0;

   //------------------------------------------------------------------------
   // Open the editing interface for the given entry. Returns the following
   // possible values:
   enum EntryEditOutcome { Ok,            // Successful edit
                           NotFound,      // Entry not found
                           Cancelled,     // User cancelled edit
                           RenameFailed}; // Rename failed because user tried to rename
                                          // the entry to a name that already is
                                          // in the library. Name rejected but other
                                          // edits retained.
                           
   //------------------------------------------------------------------------
   virtual EntryEditOutcome EditEntry( LPCTSTR key,UINT nPage=0) = 0;

   //------------------------------------------------------------------------
   // Rename an entry
   virtual bool RenameEntry( LPCTSTR oldKey, LPCTSTR newKey) = 0;

   //------------------------------------------------------------------------
   // Remove an entry. Returns the following possble values:
   enum EntryRemoveOutcome { RemOk,            // Successful edit
                             RemNotFound,      // Entry not found
                             RemReferenced};   // Entry has outstanding references
                                            // cannot be removed

   //------------------------------------------------------------------------
   virtual EntryRemoveOutcome RemoveEntry( LPCTSTR key ) = 0;

   //------------------------------------------------------------------------
   // Remove all entries. Will assert if entries have outstanding references
   virtual void RemoveAll() = 0;

   //------------------------------------------------------------------------
   // Save to structured storage
   virtual bool SaveMe(WBFL::System::IStructuredSave* pSave) = 0;

   //------------------------------------------------------------------------
   // Load from structured storage
   virtual bool LoadMe(WBFL::System::IStructuredLoad* pLoad) = 0;

   //------------------------------------------------------------------------
   // Change the display name of the library.
   virtual void SetDisplayName(LPCTSTR name) = 0;

   //------------------------------------------------------------------------
   // Get the display name of the library
   virtual std::_tstring GetDisplayName() const = 0;

   //------------------------------------------------------------------------
   // Get the identification name of the library
   virtual std::_tstring GetIdName() const = 0;

   //------------------------------------------------------------------------
   // Generate a name that's guaranteed not to be in the library
   virtual std::_tstring GetUniqueEntryName(LPCTSTR lpszBaseName=_T("New Entry-")) const = 0; 

   // ACCESS
   //------------------------------------------------------------------------
   // return a list of the names of all entries in the library.
   virtual void KeyList(libKeyListType& rList) const = 0;

   // INQUIRY
   //------------------------------------------------------------------------
   // Get the number of entries in the library
   virtual CollectionIndexType GetCount( ) const = 0;

   //------------------------------------------------------------------------
   // Returns the minimum number of required library entires
   virtual CollectionIndexType GetMinCount() const = 0;

   //------------------------------------------------------------------------
   // Get a const pointer to an entry by index
   // Returns nullptr if out of range and asserts
   // DOES NOT INCREASE REFERENCE COUNT!
   virtual const libLibraryEntry* GetEntry(LPCTSTR key) const  = 0;


   //------------------------------------------------------------------------
   // Is the library empty?
   virtual bool IsEmpty( ) const = 0;

   //------------------------------------------------------------------------
   // Returns true if this is an old library that is no longer used
   virtual bool IsDepreciated() const = 0;

   virtual std::set<std::_tstring> GetReservedNamesList() const = 0;
   virtual void AddReservedName(LPCTSTR strName) = 0;
   virtual bool IsReservedName(LPCTSTR strName) const = 0;

   // GROUP: ACCESS
   // GROUP: INQUIRY
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(WBFL::Debug::LogContext& os) const = 0;
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//


#endif // INCLUDED_LIBRARYFW_ILIBRARY_H_
