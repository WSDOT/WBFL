///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2019  Washington State Department of Transportation
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

#include <System\SysLib.h>
#include <iomanip>

/****************************************************************************
CLASS
   sysStructuredSaveXml
****************************************************************************/

#include <System\StructuredSaveXml.h>
#include <System\XStructuredSave.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// # of spaces per indentation
const int INDENT=2;


// free function to indent a stream
void indent_stream(std::_tostream& rOs, long spaces)
{
   for (long i = 0; i<spaces; i++)
      rOs << " ";
}


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysStructuredSaveXml::sysStructuredSaveXml():
m_pOStream(0),
m_Level(0)
{
}

sysStructuredSaveXml::~sysStructuredSaveXml()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void sysStructuredSaveXml::BeginSave(std::_tostream* pos)
{
   m_pOStream = pos;
   // set ostream to throw exceptions for all errors and save state to be restored
   // in destructor
   m_IoState = m_pOStream->exceptions();
   m_pOStream->exceptions(std::ios_base::badbit|std::ios_base::failbit|std::ios_base::eofbit);

   // write out header information
   *m_pOStream << _T("<?xml version=\"1.0\"?>") << std::endl;
}

void sysStructuredSaveXml::EndSave()
{
   CHECKX(m_Level==0,_T("Error: BeginUnit-EndUnit mismatch in structured save"));
   // final xml is not closed

   // restore original state
   m_pOStream->exceptions(m_IoState);
}

void sysStructuredSaveXml::BeginUnit(LPCTSTR name, Float64 version)
{
   ASSERTVALID;
   m_Level++;
   m_UnitList.emplace_back(name,version);
   
   try
   {
   indent_stream(*m_pOStream, m_Level*INDENT);
   *m_pOStream << _T("<")<<name<< _T(" version=\"")<<version<<_T("\">")<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::EndUnit()
{
   ASSERTVALID;
   
   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT);
      *m_pOStream << _T("</")<<m_UnitList.back().first <<_T(">")<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }


   m_UnitList.pop_back();
   m_Level--;

   ASSERTVALID;
}


Float64 sysStructuredSaveXml::GetVersion()
{
   ASSERTVALID;
   return m_UnitList.back().second;
}

Float64 sysStructuredSaveXml::GetParentVersion()
{
   ASSERTVALID;
   UnitListConstIterator iter = m_UnitList.end();
   iter--;
   return (*iter).second;
}

Float64 sysStructuredSaveXml::GetTopVersion()
{
   ASSERTVALID;
   return m_UnitList.front().second;
}

void sysStructuredSaveXml::Property(LPCTSTR name, LPCTSTR value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);
      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::Property(LPCTSTR name, Float64 value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);

      // set floating point percision
      *m_pOStream << std::setprecision(15);

      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::Property(LPCTSTR name, Int16 value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);
      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::Property(LPCTSTR name, Uint16 value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);
      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::Property(LPCTSTR name, Int32 value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);
      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::Property(LPCTSTR name, Uint32 value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);
      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::Property(LPCTSTR name, Int64 value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);
      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::Property(LPCTSTR name, Uint64 value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);
      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::Property(LPCTSTR name, LONG value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);
      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::Property(LPCTSTR name, ULONG value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);
      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXml::Property(LPCTSTR name, bool value)
{
   ASSERTVALID;

   try
   {
      indent_stream(*m_pOStream, m_Level*INDENT+INDENT);
      *m_pOStream << "<"<<name<<">"<<value<<"</"<<name<<">"<<std::endl;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
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
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool sysStructuredSaveXml::AssertValid() const
{
   // cannot have negative levels
   if (m_Level<0) 
      return false;

   if (!*m_pOStream) // must have happy stream
      return false;

   return true;
}

void sysStructuredSaveXml::Dump(dbgDumpContext& os) const
{
   os << "Dump for sysStructuredSaveXml" << endl;
   os << "  Level: " << m_Level << endl;
   os << "  Units: <name, version> " << endl;
   for (UnitListConstIterator it=m_UnitList.begin(); it!=m_UnitList.end(); it++)
      os <<"    <"<<(*it).first<<", "<<(*it).second<<">"<<endl;

}
#endif // _DEBUG

#if defined _UNITTEST
bool sysStructuredSaveXml::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("sysStructuredSaveXml");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for sysStructuredSaveXml");

   TESTME_EPILOG("StructuredSaveXml");
}
#endif // _UNITTEST
