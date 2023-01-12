///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2023  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   libLibraryEntry
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
libLibraryEntry::libLibraryEntry()
{
   Init();
}

libLibraryEntry::libLibraryEntry(const libLibraryEntry& rOther)
{
   Init();
   MakeCopy(rOther);
}

libLibraryEntry::~libLibraryEntry()
{
   CHECKX(!m_RefCnt,_T("Can't kill entry until all references are gone"));
   Clean();
}

//======================== OPERATORS  =======================================
libLibraryEntry& libLibraryEntry::operator= (const libLibraryEntry& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void libLibraryEntry::SetName(LPCTSTR name)
{
   m_Name.erase();
   m_Name = name;
}

const std::_tstring& libLibraryEntry::GetName() const
{
   return m_Name;
}

bool libLibraryEntry::Edit(bool allowEditing,int nPage)
{
   return false;
}

void libLibraryEntry::SetLibrary(const libILibrary* pLibrary)
{
   m_pLibrary = pLibrary;
}

const libILibrary* libLibraryEntry::GetLibrary() const
{
   return m_pLibrary;
}

Uint32 libLibraryEntry::AddRef() const
{
   m_RefCnt++;
// WATCH( _T("Referencing ") << m_Name << _T(" Ref Count = ") << m_RefCnt );
   return m_RefCnt;
}

Uint32 libLibraryEntry::Release() const
{
   CHECKX(m_RefCnt>0,_T("Reference count cannot be negative"));

   // just some safety code for release builds
   if ( m_RefCnt == 0 )
      m_RefCnt++;

   m_RefCnt--;

// WATCH( _T("Releasing ") << m_Name << _T(" Ref Count = ") << m_RefCnt );
   return m_RefCnt;
}

Uint32 libLibraryEntry::GetRefCount() const
{
   return m_RefCnt;
}

bool libLibraryEntry::IsEditingEnabled() const
{
   return m_IsEditingEnabled;
}

void libLibraryEntry::EnableEditing(bool enable)
{
   m_IsEditingEnabled = enable;
}

void libLibraryEntry::EnableCopying(bool bEnable)
{
   m_bCanCopy = bEnable;
}

bool libLibraryEntry::IsCopyingEnabled() const
{
   return m_bCanCopy;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================


void libLibraryEntry::MakeCopy(const libLibraryEntry& rOther)
{
   // copied entries dont get reference counted.
   m_pLibrary         = rOther.m_pLibrary;
   m_Name             = rOther.m_Name;
   m_IsEditingEnabled = rOther.m_IsEditingEnabled;
   m_bCanCopy         = rOther.m_bCanCopy;
}

void libLibraryEntry::MakeAssignment(const libLibraryEntry& rOther)
{
   // Save the ref count, Init() will reset it.
   // During assignment, the ref count shouldn't change, only the library
   // entry data.
   Uint32 cTempRefCnt = m_RefCnt;

   Clean();
   Init();

   MakeCopy( rOther );

   // retore the ref count
   m_RefCnt = cTempRefCnt;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void libLibraryEntry::Init()
{
   m_pLibrary = 0;
   m_RefCnt = 0;
   m_IsEditingEnabled = true;
   m_bCanCopy = true;
}

void libLibraryEntry::Clean()
{
   // Add cleanup code here...
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool libLibraryEntry::AssertValid() const
{
   return true;
}

void libLibraryEntry::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T(" Dump for libLibraryEntry") << WBFL::Debug::endl;
   os << _T("  m_Name             : ") << m_Name << WBFL::Debug::endl;
   //os << _T("  m_pLibrary         : ") << m_pLibrary << WBFL::Debug::endl;
   os << _T("  m_RefCnt           : ") << m_RefCnt << WBFL::Debug::endl;
   os << _T("  m_IsEditingEnabled : ") << m_IsEditingEnabled << WBFL::Debug::endl;
}
#endif // _DEBUG

