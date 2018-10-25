///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_LIBRARY_LIBRARYENTRY_H_
#define INCLUDED_LIBRARY_LIBRARYENTRY_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <LibraryFw\LibraryFwExp.h>

// FORWARD DECLARATIONS
//
class libILibrary;
class sysIStructuredSave;
class sysIStructuredLoad;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   libLibraryEntry

   abstract base class for library entries


DESCRIPTION
   this class provides a base implementation for library entries.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 07.09.1998 : Created file
*****************************************************************************/

class LIBRARYFWCLASS libLibraryEntry
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   libLibraryEntry();

   //------------------------------------------------------------------------
   // Copy constructor
   libLibraryEntry(const libLibraryEntry& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~libLibraryEntry();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   libLibraryEntry& operator = (const libLibraryEntry& rOther);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Edit the entry. if allowEditing is false, the entry may be viewed,
   // but values may not be changed.
   // Return true if edit is to be accepted, false if edit is cancelled.
   // It is up to the implementer of this class to insure that the entry
   // is not changed if the edit is cancelled.
   virtual bool Edit(bool allowEditing)=0;

   //------------------------------------------------------------------------
   // Change the name of the entry
   void SetName(LPCTSTR name);

   //------------------------------------------------------------------------
   // Get the name of the entry
   std::_tstring GetName() const;

   //------------------------------------------------------------------------
   // Set a pointer back to our library
   void SetLibrary(const libILibrary* pLibrary);

   //------------------------------------------------------------------------
   // Return a pointer to our library
   const libILibrary* GetLibrary() const;

   //------------------------------------------------------------------------
   // Increment the reference count by one
   Uint32 AddRef() const;

   //------------------------------------------------------------------------
   // Decrement the reference count by one
   // This routine DOES NOT delete the entry when the count goes to zero. That
   // is the job of higher sources (e.g., the Library).
   Uint32 Release() const;

   //------------------------------------------------------------------------
   // Get the number of references to this entry
   Uint32 GetRefCount() const;

   //------------------------------------------------------------------------
   // Returns true if the entry can be edited.
   bool IsEditingEnabled() const;

   //------------------------------------------------------------------------
   // Enables or disables editing of entries
   void EnableEditing(bool enable);

   //------------------------------------------------------------------------
   // Save to structured storage
   virtual bool SaveMe(sysIStructuredSave* pSave)=0;

   //------------------------------------------------------------------------
   // Load from structured storage
   virtual bool LoadMe(sysIStructuredLoad* pLoad)=0;

   // ACCESS
   
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const libLibraryEntry& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const libLibraryEntry& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::_tstring       m_Name;
   const libILibrary* m_pLibrary;
   mutable Uint32 m_RefCnt;
   bool              m_IsEditingEnabled;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   void Clean();

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

};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LIBRARY_LIBRARYENTRY_H_
