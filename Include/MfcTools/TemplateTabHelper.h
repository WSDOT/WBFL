///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2012  Washington State Department of Transportation
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

#ifndef INCLUDED_PSGLIB_TEMPLATETABHELPER_H_
#define INCLUDED_PSGLIB_TEMPLATETABHELPER_H_
#pragma once

// SYSTEM INCLUDES
//
#include <set>
#include <map>
#include <string>
#include <vector>

// PROJECT INCLUDES
//
#include <System\System.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   mfcTemplateTabHelper

   Helper class for building template file tabs


DESCRIPTION
   Helper class for building template file tabs


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 10.07.1998 : Created file
*****************************************************************************/

class  mfcTemplateTabHelper
{
public:
   // class for display of file information
   class TabDisplayFile
   {
   public:
      TabDisplayFile() {;}
      CString  m_FileName;
      CString  m_LastWriteDate;
      CString  m_SizeInBytes;
      bool operator==(const TabDisplayFile& rOther) const {return m_FileName==rOther.m_FileName;}
      TabDisplayFile(const TabDisplayFile& rOther){
         m_FileName = rOther.m_FileName;
         m_LastWriteDate = rOther.m_LastWriteDate;
         m_SizeInBytes = rOther.m_SizeInBytes;
      }
   };
   
   typedef std::vector<TabDisplayFile> TabDisplayFileList;
   typedef TabDisplayFileList::iterator TabDisplayFileIterator;

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Constructor
   mfcTemplateTabHelper(const std::_tstring& name, const std::_tstring& suffix);

   //------------------------------------------------------------------------
   // copy
   mfcTemplateTabHelper(const mfcTemplateTabHelper&);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mfcTemplateTabHelper();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // add another sudirectory for this tab
   void AddSubDirectory(const std::_tstring& dirName);

   //------------------------------------------------------------------------
   // Get the file list for the current subdirectories. Returns an empty list
   // if no files with the suffix could be found.
   void GetFileList(TabDisplayFileList* pFileList);

   //------------------------------------------------------------------------
   // get the corresponding path for the given file. Returns an empty
   // string if the file could not be found.
   std::_tstring GetFilePath(const std::_tstring& fileName);

   // GROUP: ACCESS
   //------------------------------------------------------------------------
   // get name
   std::_tstring GetName() const {return m_Name;}
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
   // private internal list for keeping track of files
   class TabFile
   {
   public:
      std::_tstring  m_FileName;
      const std::_tstring* m_pDirectory;  // each file indexes to its directory
      bool operator==(const TabFile& rOther) const {return m_FileName==rOther.m_FileName;}
      bool operator<(const TabFile& rOther)  const {return m_FileName<rOther.m_FileName;}
   };

   //------------------------------------------------------------------------
   // hold a reference here. kind of dangerous, but saves on memory and speed,
   // and this guy is only used by doctemplatefinder-related classes
   const std::_tstring&    m_Suffix;
   std::_tstring           m_Name;

   //------------------------------------------------------------------------
   std::set<std::_tstring> m_DirectoryList;

   typedef std::set<TabFile> FileListType;
   typedef FileListType::iterator FileListTypeIterator;
   FileListType     m_FileList;
   // GROUP: LIFECYCLE

   // no default constructor
   mfcTemplateTabHelper();
   // Prevent accidental copying and assignment
   mfcTemplateTabHelper& operator=(const mfcTemplateTabHelper&);

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
   // Dumps the contents of the object to the given dump context.
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
   //------------------------------------------------------------------------
   // useful typedefs for tab and file lists
   typedef std::map<std::_tstring, mfcTemplateTabHelper> TabList;
   typedef TabList::value_type TabListEntry;
   typedef TabList::iterator TabListIterator;

// EXTERNAL REFERENCES
//

#endif // INCLUDED_PSGLIB_TEMPLATETABHELPER_H_
