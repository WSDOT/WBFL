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
   mfcTemplateTabHelper
****************************************************************************/
#include <stdafx.h>
#include <mfcTools\TemplateTabHelper.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mfcTemplateTabHelper::mfcTemplateTabHelper(const std::_tstring& name, const std::_tstring& suffix):
m_Name(name),
m_Suffix(suffix)
{
}

mfcTemplateTabHelper::~mfcTemplateTabHelper()
{
}

mfcTemplateTabHelper::mfcTemplateTabHelper(const mfcTemplateTabHelper& rOther):
m_Suffix(rOther.m_Suffix),
m_Name(rOther.m_Name)
{
   m_DirectoryList = rOther.m_DirectoryList;
   m_FileList      = rOther.m_FileList;
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void mfcTemplateTabHelper::GetFileList(TabDisplayFileList* pFileList)
{
   m_FileList.clear();
   pFileList->clear();
   // loop over all subdirectories to fill internal file list and display list
   for (std::set<std::_tstring>::iterator it=m_DirectoryList.begin(); it!=m_DirectoryList.end(); it++)
   {
      CString filespec = CString(it->c_str()) + CString(_T("*.")) + CString(m_Suffix.c_str());
      CFileFind finder;
      BOOL is_file;
      is_file = finder.FindFile(filespec);
      while(is_file)
      {
         is_file = finder.FindNextFile();
         TabFile file;
         file.m_FileName = std::_tstring(finder.GetFileName());
         file.m_pDirectory = &(*it);
         
         std::pair<FileListTypeIterator,bool> pib;
         pib = m_FileList.insert(file);

         // only insert file into display list if it is unique (i.e. it wasn't
         // inserted into the set.
         if (pib.second)
         {
            mfcTemplateTabHelper::TabDisplayFile mf;
            mf.m_FileName = finder.GetFileName();
            CTime tim;
            VERIFY(finder.GetLastWriteTime(tim));
            mf.m_LastWriteDate= tim.Format(_T("%m/%d/%Y %I:%M:%S%p"));
            mf.m_SizeInBytes.Format(_T("%d bytes"),finder.GetLength());
            pFileList->push_back(mf);
         }
      }
   }
}

std::_tstring mfcTemplateTabHelper::GetFilePath(const std::_tstring& fileName)
{
   TabFile file;
   file.m_FileName = fileName;
   file.m_pDirectory = 0; // doesn't matter

   FileListTypeIterator it = m_FileList.find(file);
   if (it!=m_FileList.end())
   {
      return std::_tstring(*(it->m_pDirectory) + fileName);
   }
   else
      return std::_tstring(); // return an empty string
}


void mfcTemplateTabHelper::AddSubDirectory(const std::_tstring& dirName) 
{
   // make sure directory is '\' terminated
   int siz = dirName.size();
   ASSERT(siz);  // null name in directory - no no
   if(dirName[siz-1] != _T('\\') )
   {
      std::_tstring tmp(dirName);
      tmp += _T("\\");
      m_DirectoryList.insert(tmp);
   }
   else
      m_DirectoryList.insert(dirName);
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
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool mfcTemplateTabHelper::AssertValid() const
{
   return true;
}

void mfcTemplateTabHelper::Dump(dbgDumpContext& os) const
{
   os << "Dump for mfcTemplateTabHelper" << endl;
   os << "  m_Name   = "<< m_Name<<endl;
   os << "  m_Suffix = "<< m_Suffix<<endl;
   os << " Directory List "<<endl;
   for (std::set<std::_tstring>::const_iterator itd = m_DirectoryList.begin(); itd!=m_DirectoryList.end(); itd++)
   {
      os << "     "<<*itd<<endl;
   }
   os << " Tab File List"<<endl;
   for(FileListType::const_iterator itf= m_FileList.begin(); itf!=m_FileList.end(); itf++)
   {
      os << "  File: "<<itf->m_FileName<<endl;
      os << "    Directory: "<< *(itf->m_pDirectory)<<endl;
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool mfcTemplateTabHelper::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("mfcTemplateTabHelper");


   TESTME_EPILOG("TemplateTabHelper");
}
#endif // _UNITTEST
