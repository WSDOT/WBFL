///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include <LibraryFw\LibraryFwLib.h>
#include <LibraryFw\LibraryEntry.h>
#include <LibraryFw\Library.h>

using namespace WBFL::Library;

LibraryEntry::LibraryEntry(const LibraryEntry& rOther)
{
   CopyValuesAndAttributes(rOther);
}

LibraryEntry::~LibraryEntry()
{
   CHECKX(!m_RefCnt,_T("Can't destroy an entry until all references are gone"));
}

LibraryEntry& LibraryEntry::operator=(const LibraryEntry& rOther)
{
   if( this != &rOther )
   {
      CopyValuesAndAttributes(rOther);
   }

   return *this;
}

void LibraryEntry::SetName(LPCTSTR name)
{
   m_Name.erase();
   m_Name = name;
}

const std::_tstring& LibraryEntry::GetName() const
{
   return m_Name;
}

bool LibraryEntry::Edit(bool allowEditing,int nPage)
{
   return false;
}

void LibraryEntry::SetLibrary(const ILibrary* pLibrary)
{
   m_pLibrary = pLibrary;
}

const ILibrary* LibraryEntry::GetLibrary() const
{
   return m_pLibrary;
}

Uint32 LibraryEntry::AddRef() const
{
   m_RefCnt++;
   return m_RefCnt;
}

Uint32 LibraryEntry::Release() const
{
   CHECKX(0 < m_RefCnt,_T("Reference count cannot be negative"));

   // just some safety code for release builds
   if ( m_RefCnt == 0 )
      m_RefCnt++;

   m_RefCnt--;

   return m_RefCnt;
}

Uint32 LibraryEntry::GetRefCount() const
{
   return m_RefCnt;
}

bool LibraryEntry::IsEditingEnabled() const
{
   return m_IsEditingEnabled;
}

void LibraryEntry::EnableEditing(bool enable)
{
   m_IsEditingEnabled = enable;
}

void LibraryEntry::EnableCopying(bool bEnable)
{
   m_bCanCopy = bEnable;
}

bool LibraryEntry::IsCopyingEnabled() const
{
   return m_bCanCopy;
}

void LibraryEntry::CopyValuesAndAttributes(const LibraryEntry& rOther)
{
   // copied entries don't get reference counted.
   m_pLibrary         = rOther.m_pLibrary;
   m_Name             = rOther.m_Name;
   m_IsEditingEnabled = rOther.m_IsEditingEnabled;
   m_bCanCopy         = rOther.m_bCanCopy;
}
