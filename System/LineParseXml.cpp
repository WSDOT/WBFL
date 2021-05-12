///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2021  Washington State Department of Transportation
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

/****************************************************************************
CLASS
   sysLineParseXml
****************************************************************************/

#include <System\LineParseXml.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////
bool SimpleFloatParse(LPCTSTR lpszText, Float64& d);
typedef std::_tstring::size_type Sst;
#define npos std::_tstring::npos

//======================== LIFECYCLE  =======================================
sysLineParseXml::sysLineParseXml():
m_Type(sysLineParseXml::Unknown)
{
}

sysLineParseXml::~sysLineParseXml()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

sysLineParseXml::LineType sysLineParseXml::ParseLine(const std::_tstring& line)
{
   m_Line = line;
   m_Type =  sysLineParseXml::Unknown;
   m_Value= _T("");

   // start parsing the line. we have four basic possibilities:
   //   <UNIT_NAME version="1.0">    // a BeginUnit
   //   <UNIT_NAME>                  // a BeginUnit with no version
   //   </UNIT_NAME>                 // an EndUnit
   //   <NAME>"VALUE"</NAME>         // a Property

   if (m_Line.empty()) 
      return sysLineParseXml::Unknown;

   if (m_Line[0] != _T('<') ) 
      return sysLineParseXml::Unknown;

   if (m_Line[1] == _T('/') )
   {
      // we probably have an EndUnit
      Sst pos = m_Line.find(_T(">"),1);
      if (pos==npos) return sysLineParseXml::Unknown;
      if (pos>2)
         // save name in value location if name is given.
         m_Value = m_Line.substr(2,pos-2);
      else
         m_Value = _T("");

      return m_Type = sysLineParseXml::EndUnit;
   }
   else
   {
      // we either have a Property or a BeginUnit (or ???)
      Sst pos = m_Line.find(_T("</"),1);
      if (pos!=npos)
      {
         // we probably have a Property
         Sst apos = m_Line.find(_T(">"),1);
         if (apos==npos)
            return sysLineParseXml::Unknown;
         else if (apos!=pos+2)
         {
            m_Name  = m_Line.substr(1,apos-1);
            m_Value = m_Line.substr(apos+1,pos-(apos+1)); // value is always quoted
            return m_Type = sysLineParseXml::Property;
         }
         else
            return sysLineParseXml::Unknown;
      }
      else
      {
         // we probably have a BeginUnit
         Sst apos = m_Line.find(_T(">"),1);
         if (apos==npos)
            return sysLineParseXml::Unknown;

         Sst bpos = m_Line.find(_T(" version=\""),1);
         if (bpos!=npos)
         {
            // have BeginUnit with version
            m_Name  = m_Line.substr(1,bpos-1);
            m_Value = m_Line.substr(bpos+10,apos-(bpos+11));
            return m_Type = sysLineParseXml::BeginUnit;
         }
         else
         {
            // may have BeginUnit with no version - check for blanks.
            Sst cpos = m_Line.find(_T(" "),1);
            if (bpos!=npos)
               return sysLineParseXml::Unknown;

            m_Name  = m_Line.substr(1,apos-1);
            m_Value = _T("0");  // no version given
            return m_Type = sysLineParseXml::BeginUnit;
         }
      }
   }
}

sysLineParseXml::LineType sysLineParseXml::GetType() const
{
   return m_Type;
}

std::_tstring sysLineParseXml::GetName() const
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   return m_Name;
}

bool sysLineParseXml::GetValue(std::_tstring* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);

   *value = m_Value;
   return true;
}

bool sysLineParseXml::GetValue(Float64* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   if (m_Value.empty())
      return false;

   Float64 d;
   if (SimpleFloatParse(m_Value.c_str(), d))
   {
      *value = d;
      return true;
   }
   return false;
}

bool sysLineParseXml::GetValue(Int16* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   if (m_Value.empty())
      return false;

   Int16 l;
   std::_tistringstream is(m_Value);

   is >> l;
   if (is)
   {
      *value = l;
      return true;
   }
   return false;
}

bool sysLineParseXml::GetValue(Uint16* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   if (m_Value.empty())
      return false;

   Uint16 l;
   std::_tistringstream is(m_Value);

   is >> l;
   if (is)
   {
      *value = l;
      return true;
   }
   return false;
}

bool sysLineParseXml::GetValue(Int32* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   if (m_Value.empty())
      return false;

   Int32 l;
   std::_tistringstream is(m_Value);

   is >> l;
   if (is)
   {
      *value = l;
      return true;
   }
   return false;
}

bool sysLineParseXml::GetValue(Uint32* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   if (m_Value.empty())
      return false;

   Uint32 l;
   std::_tistringstream is(m_Value);

   is >> l;
   if (is)
   {
      *value = l;
      return true;
   }
   return false;
}

bool sysLineParseXml::GetValue(Int64* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   if (m_Value.empty())
      return false;

   Int64 l;
   std::_tistringstream is(m_Value);

   is >> l;
   if (is)
   {
      *value = l;
      return true;
   }
   return false;
}

bool sysLineParseXml::GetValue(Uint64* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   if (m_Value.empty())
      return false;

   Uint64 l;
   std::_tistringstream is(m_Value);

   is >> l;
   if (is)
   {
      *value = l;
      return true;
   }
   return false;
}

bool sysLineParseXml::GetValue(LONG* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   if (m_Value.empty())
      return false;

   LONG l;
   std::_tistringstream is(m_Value);

   is >> l;
   if (is)
   {
      *value = l;
      return true;
   }
   return false;
}

bool sysLineParseXml::GetValue(ULONG* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   if (m_Value.empty())
      return false;

   ULONG l;
   std::_tistringstream is(m_Value);

   is >> l;
   if (is)
   {
      *value = l;
      return true;
   }
   return false;
}

bool sysLineParseXml::GetValue(bool* value)
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   if (m_Value.empty())
      return false;

   if (m_Value == _T("1") )
   {
      *value = true;
      return true;
   }
   else if (m_Value == _T("0") )
   {
      *value = false;
      return true;
   }
   return false;
}

std::_tstring sysLineParseXml::GetStateDump() const
{
   std::_tostringstream os;
   os << _T("Dump for sysLineParseXml") << std::endl;
   os << _T("   m_Line  = ") << m_Line  << std::endl;
   os << _T("   m_Type = ") << m_Type   << std::endl;
   os << _T("   m_Name = ") << m_Name   << std::endl;
   os << _T("   m_Value = ") << m_Value << std::endl;
   return os.str();
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
bool sysLineParseXml::AssertValid() const
{
   return true;
}

void sysLineParseXml::Dump(dbgDumpContext& os) const
{
   std::_tstring tmp;
   tmp = GetStateDump();
   os << tmp << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool sysLineParseXml::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("sysLineParseXml");

   // Testme done in UnitTest for main project

   TESTME_EPILOG("LineParseXml");
}
#endif // _UNITTEST

bool SimpleFloatParse(LPCTSTR lpszText, Float64& d)
{
	CHECK(lpszText != 0);
	while (*lpszText == _T(' ') || *lpszText == _T('\t') )
		lpszText++;

	TCHAR chFirst = lpszText[0];
   LPTSTR stopstr;
	d = _tcstod(lpszText, &stopstr);
	if (d == 0.0 && chFirst != _T('0') )
		return false;   // could not convert
	while (*stopstr == _T(' ') || *stopstr == _T('\t') )
		stopstr++;

	if (*stopstr != _T('\0') )
		return false;   // not terminated properly

	return true;
}

