///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
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


/****************************************************************************
CLASS
   mfcDocTemplateFinder
****************************************************************************/
#include <stdafx.h>
#include <mfcTools\DocTemplateFinder.h>
#include <mfcTools\DocTemplateDialog.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// funtion to make sure directories are \ terminated
void TerminateDirList(std::vector<std::_tstring>* list);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mfcDocTemplateFinder::mfcDocTemplateFinder():
m_Mode(mfcDocTemplateFinder::SmallIconMode),
m_Suffix(_T("tmp")),
m_DefaultName(_T("Blank Document")),
m_DefaultFile(_T("Normal")),
m_HIcon(0),
m_pDocTemplateDialog(new CDocTemplateDialog(NULL)) 
{

}

mfcDocTemplateFinder::mfcDocTemplateFinder(const std::vector<std::_tstring>& directoryList, 
                                     const std::_tstring& suffix,
                                     ListMode mode):
m_DirectoryList(directoryList),
m_Suffix(suffix),
m_Mode(mode),
m_DefaultName(_T("Blank Document")),
m_DefaultFile(_T("Normal")),
m_HIcon(0),
m_pDocTemplateDialog(new CDocTemplateDialog(NULL)) 
{

   TerminateDirList(&m_DirectoryList);
}

mfcDocTemplateFinder::~mfcDocTemplateFinder()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void mfcDocTemplateFinder::OmitDefaultFile(bool bOmit)
{
   m_pDocTemplateDialog->m_bOmitDefaultFile = bOmit;
}

bool mfcDocTemplateFinder::OmitDefaultFile() const
{
   return m_pDocTemplateDialog->m_bOmitDefaultFile;
}

void mfcDocTemplateFinder::SetDirectoryList(const std::vector<std::_tstring>& directoryList)
{
   m_DirectoryList = directoryList;

   TerminateDirList(&m_DirectoryList);
}

void mfcDocTemplateFinder::GetDirectoryList(std::vector<std::_tstring>* directoryList) const
{
   *directoryList = m_DirectoryList;
}

void mfcDocTemplateFinder::SetFileSuffix(const std::_tstring& suffix)
{
   m_Suffix = suffix;
}

std::_tstring mfcDocTemplateFinder::GetFileSuffix()
{
   return m_Suffix;
}

void mfcDocTemplateFinder::SetDefaultFileName(const std::_tstring& defaultName, const std::_tstring& defaultFile)
{
   ASSERT(std::_tstring::npos==defaultName.find('.'));
   m_DefaultName = defaultName;
   m_DefaultFile = defaultFile;
}

void mfcDocTemplateFinder::GetDefaultFileName(std::_tstring* pdefaultName, std::_tstring* pdefaltFile)const
{
   *pdefaultName = m_DefaultName;
   *pdefaltFile  = m_DefaultFile;
}

void mfcDocTemplateFinder::SetListMode(mfcDocTemplateFinder::ListMode mode)
{
   m_Mode = mode;
}

mfcDocTemplateFinder::ListMode mfcDocTemplateFinder::GetListMode() const
{
   return m_Mode;
}

void mfcDocTemplateFinder::SetIcon(HICON hIcon)
{
   m_HIcon = hIcon;
   m_pDocTemplateDialog->SetIcon(hIcon);
}

HICON mfcDocTemplateFinder::GetIcon() const
{
   return m_HIcon;
}

mfcDocTemplateFinder::GetTemplateFileResult mfcDocTemplateFinder::GetTemplateFile(std::_tstring& fileName)
{

   // create a tab list and build it
   TabList tab_list;
   this->BuildTabList(tab_list);

   if ( tab_list.size() == 1 )
   {
      // only the general tab
      // if that tab is empty, get the heck outta here
      mfcTemplateTabHelper& helper = tab_list.begin()->second;

      std::vector<mfcTemplateTabHelper::TabDisplayFile> files;
      helper.GetFileList(&files);

      if ( files.size() == 0 )
         return mfcDocTemplateFinder::NoTemplatesAvailable;

   }

   // give tab list to dialog
   m_pDocTemplateDialog->SetTabList(&tab_list);

   // give dialog the default file name
   m_pDocTemplateDialog->SetDefaultFile(m_DefaultName);

   m_pDocTemplateDialog->SetListMode( m_Mode );
   int st = m_pDocTemplateDialog->DoModal();
   m_Mode = m_pDocTemplateDialog->GetListMode();

   if (st==IDOK)
   {
      std::_tstring tmp = m_pDocTemplateDialog->GetSelectedFile();
      if (tmp.size())
      {
         if (tmp == m_DefaultName)
         {
            fileName = m_DefaultFile + std::_tstring(_T(".")) + m_Suffix;
            return DefaultFileSelected;
         }
         else
         {
            fileName = tmp;
            CFileFind finder;
            BOOL is_file = finder.FindFile(tmp.c_str());
            if (is_file)
               return ValidFileSelected;
            else
               return SelectedFileThatDoesntExist;
         }
      }
      else
      {
         // should never happen
         ASSERT(0);
         return CancelledSelection;
      }
   }
   else
   {
      return CancelledSelection;
   }
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void mfcDocTemplateFinder::BuildTabList(TabList& tab_list)
{
   // big, ugly routine to build list of tabs for display based on
   // directory structure

   // add a General tab regardless of what happens
   mfcTemplateTabHelper general(_T("General"), m_Suffix);
   tab_list.insert(TabListEntry(_T("general"), general)); // use lower case for keys

   // if no directories in list, have General tab list files in same directory as 
   // executable
   if (m_DirectoryList.size()==0)
   {
      TCHAR cdir[MAX_PATH];
      ::GetCurrentDirectory(MAX_PATH, cdir);
      TabListIterator it = tab_list.find(_T("general"));
      ASSERT(it!=tab_list.end());
      it->second.AddSubDirectory(cdir);
   }
   else
      // build tabs based on directory list
   {
      for (std::vector<std::_tstring>::iterator it=m_DirectoryList.begin();
           it!=m_DirectoryList.end(); it++)
      {
         // find all subdirectories in each directory and create a tab for them
         CFileFind finder;
         BOOL is_file;
         CString dirnam = CString(it->c_str()) + CString(_T("*.*"));
         is_file = finder.FindFile(dirnam);
         if (is_file)
         {
            // add directory to general tab
            TabListIterator itt = tab_list.find(_T("general"));
            ASSERT(itt!=tab_list.end());
            itt->second.AddSubDirectory(it->c_str());
         }
         while(is_file)
         {
            is_file = finder.FindNextFile();
            if (finder.IsDirectory() && !finder.IsDots())
            {
               // found a subdirectory
               CString fulnam = finder.GetFilePath();

               // see if any files with template file suffix exist in the directory
               CFileFind template_finder;
               BOOL is_templatefile;
               CString filspec = fulnam + CString(_T("\\*.")) + CString(m_Suffix.c_str());
               is_templatefile = template_finder.FindFile(filspec);

               // add tab only if template files exist in this subdirectory
               if (is_templatefile)
               {
                  CString tabnam = finder.GetFileName();
                  CString subdirnam = tabnam;
                  subdirnam.MakeLower();  // convert all names to lower case for compares

                  // see if subdirectory is already a tab. if not, add it
                  TabListIterator itt = tab_list.find(std::_tstring(subdirnam));
                  if(itt!=tab_list.end())
                  {
                     // already a tab for this directory - add it to the list
                     itt->second.AddSubDirectory(std::_tstring(fulnam));
                  }
                  else
                  {
                     // add a new tab
                     mfcTemplateTabHelper tabr(std::_tstring(tabnam), m_Suffix);
                     tabr.AddSubDirectory(std::_tstring(fulnam));
                     tab_list.insert(TabListEntry(std::_tstring(subdirnam), tabr));
                  }
               }
            }
         }
      }
   }
}
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================

#if defined _UNITTEST
bool mfcDocTemplateFinder::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("mfcDocTemplateFinder");
   // due to lack of a gui testing tool, this one must be tested by hand
   TESTME_EPILOG("GetNewFileName");
}
#endif // _UNITTEST

void TerminateDirList(std::vector<std::_tstring>* list)
{
   for (std::vector<std::_tstring>::iterator it=list->begin(); 
        it!=list->end(); it++)
   {
      int siz = it->size();
      ASSERT(siz);  // null name in directory - no no
      // this is about the ugliest looking piece of code i've written
      if((*it)[siz-1] != _T('\\')) 
         (*it) += _T("\\");
   }
}
