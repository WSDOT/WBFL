///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_PSGLIB_GETNEWFILENAME_H_
#define INCLUDED_PSGLIB_GETNEWFILENAME_H_
#pragma once

// SYSTEM INCLUDES
//
#include <vector>
#include <string>
// PROJECT INCLUDES
//
#include <MfcTools\MfcToolsExp.h>
#include <MfcTools\TemplateTabHelper.h>

// FORWARD DECLARATIONS
//
class CDocTemplateDialog;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   mfcDocTemplateFinder

   User interface class for creating new files based on a template


DESCRIPTION
   A Word-like file new dialog


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 10.02.1998 : Created file
*****************************************************************************/

class MFCTOOLSCLASS mfcDocTemplateFinder : CObject
{
   friend CDocTemplateDialog;
public:
   //------------------------------------------------------------------------
   // ListMode
   // Enum defining the types of list mode that the control can go into. 
   // This control support three 
   enum ListMode { SmallIconMode, 
                   LargeIconMode, 
                   ReportMode};

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   mfcDocTemplateFinder();

   //------------------------------------------------------------------------
   // uicGetNewFile
   // Construct with a directory list, suffix and display mode.
   mfcDocTemplateFinder(const std::vector<std::_tstring>& directoryList, 
                     const std::_tstring& suffix,
                     ListMode mode=SmallIconMode);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mfcDocTemplateFinder();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetDirectoryList
   // Set up the list of directories that will be searched for template 
   // files. Each directory and all of its first-level subdirectories 
   // will be searched.
   void SetDirectoryList(const std::vector<std::_tstring>& directoryList);

   //------------------------------------------------------------------------
   // GetDirectoryList
   // Get the list of directories that will be searched for template files. 
   // Each directory and all of its first-level subdirectories will be searched.
   void GetDirectoryList(std::vector<std::_tstring>* directoryList) const;

   //------------------------------------------------------------------------
   // SetFileSuffix
   // Set the suffix for the template files. Although any suffix will do, it 
   // is standard to use a three letter suffix for files on Windows platforms.
   // A blank suffix string will cause an assert.
   void SetFileSuffix(const std::_tstring& suffix);

   //------------------------------------------------------------------------
   // GetFileSuffix
   // Get the suffix for the template files. Although any suffix will do, 
   // it is standard to use a three letter suffix for files on Windows 
   // platforms. A blank suffix string will cause an assert.
   std::_tstring GetFileSuffix();

   //------------------------------------------------------------------------
   // SetDefaultFileName
   // Set the default template file name. This is similar to Word where the 
   // defalult listing in the file new dialog is "Blank Document" and the 
   // default file is "Normal". 
   // In fact, the defaults for this implementation are "Blank Document" and
   // the default file is "Normal.*" were * is the suffix associated with this
   // object.
   // NOTE: defaultName may not have a '.' in it. A '.' will cause an ASSERT
   void SetDefaultFileName(const std::_tstring& defaultName, const std::_tstring& defaltFile);

   //------------------------------------------------------------------------
   // GetDefaultFileName
   // Set the default template file name. This is similar to Word where the 
   // defalult listing in the file new dialog is "Blank Document" and the 
   // default file is "Normal.dot". 
   // In fact, the defaults for this implementation are "Blank Document" and
   // the default file is "Normal.*" were * is the suffix associated with this
   // object.
   void GetDefaultFileName(std::_tstring* pdefaultName, std::_tstring* pdefaltFile)const;


   bool OmitDefaultFile() const;
   void OmitDefaultFile(bool bOmit);

   //------------------------------------------------------------------------
   // SetListMode
   // Set the icon type for the list view.
   void SetListMode(mfcDocTemplateFinder::ListMode mode);

   //------------------------------------------------------------------------
   // GetListMode
   // Get the icon type for the list view.
   mfcDocTemplateFinder::ListMode GetListMode() const;

   //------------------------------------------------------------------------
   // SetIcon
   // Sets the document template icon
   void SetIcon(HICON hIcon);

   //------------------------------------------------------------------------
   // GetIcon
   // Gets the document template icon
   HICON GetIcon() const;

   //------------------------------------------------------------------------
   // GetTemplateFileResult
   // The possible outcomes of GetTemplateFile. 
   enum GetTemplateFileResult{ ValidFileSelected,
                               DefaultFileSelected,
                               CancelledSelection,
                               SelectedFileThatDoesntExist,
                               NoTemplatesAvailable
   };

   //------------------------------------------------------------------------
   // GetTemplateFile
   // Pop up the user interface (dialog) and ask user to select a template 
   // file. Returns false if the action was canceled by the user, or if 
   // directory list is empty, or suffix string is null. If true is 
   // returned, the string will contain the entire path to the template file.
   GetTemplateFileResult GetTemplateFile(std::_tstring& fileName);

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
   std::vector<std::_tstring> m_DirectoryList;
   std::_tstring              m_Suffix;
   std::_tstring              m_DefaultName;
   std::_tstring              m_DefaultFile;
   ListMode                 m_Mode;
   HICON                    m_HIcon;

   // need to hide dependencies to this puppy
   std::auto_ptr<CDocTemplateDialog>   m_pDocTemplateDialog;

   // Prevent accidental copying and assignment
   mfcDocTemplateFinder(const mfcDocTemplateFinder&);
   mfcDocTemplateFinder& operator=(const mfcDocTemplateFinder&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   void BuildTabList(TabList& list);
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG

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

#endif // INCLUDED_PSGLIB_GETNEWFILENAME_H_
