///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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
bool SimpleFloatParse(const char* lpszText, Float64& d);
typedef std::string::size_type Sst;
#define npos std::string::npos

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

sysLineParseXml::LineType sysLineParseXml::ParseLine(const std::string& line)
{
   m_Line = line;
   m_Type =  sysLineParseXml::Unknown;
   m_Value="";

   // start parsing the line. we have four basic possibilities:
   //   <UNIT_NAME version="1.0">    // a BeginUnit
   //   <UNIT_NAME>                  // a BeginUnit with no version
   //   </UNIT_NAME>                 // an EndUnit
   //   <NAME>"VALUE"</NAME>         // a Property

   if (m_Line.empty()) return sysLineParseXml::Unknown;
   if (m_Line[0]!='<') return sysLineParseXml::Unknown;

   if (m_Line[1]=='/')
   {
      // we probably have an EndUnit
      Sst pos = m_Line.find(">",1);
      if (pos==npos) return sysLineParseXml::Unknown;
      if (pos>2)
         // save name in value location if name is given.
         m_Value = m_Line.substr(2,pos-2);
      else
         m_Value = "";

      return m_Type = sysLineParseXml::EndUnit;
   }
   else
   {
      // we either have a Property or a BeginUnit (or ???)
      Sst pos = m_Line.find("</",1);
      if (pos!=npos)
      {
         // we probably have a Property
         Sst apos = m_Line.find(">",1);
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
         Sst apos = m_Line.find(">",1);
         if (apos==npos)
            return sysLineParseXml::Unknown;

         Sst bpos = m_Line.find(" version=\"",1);
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
            Sst cpos = m_Line.find(" ",1);
            if (bpos!=npos)
               return sysLineParseXml::Unknown;

            m_Name  = m_Line.substr(1,apos-1);
            m_Value = "0";  // no version given
            return m_Type = sysLineParseXml::BeginUnit;
         }
      }
   }
}

sysLineParseXml::LineType sysLineParseXml::GetType() const
{
   return m_Type;
}

std::string sysLineParseXml::GetName() const
{
   CHECK(m_Type!=sysLineParseXml::Unknown);
   return m_Name;
}

bool sysLineParseXml::GetValue(std::string* value)
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
   std::istringstream is(m_Value);

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
   std::istringstream is(m_Value);

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
   std::istringstream is(m_Value);

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
   std::istringstream is(m_Value);

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

   if (m_Value=="1")
   {
      *value = true;
      return true;
   }
   else if (m_Value=="0")
   {
      *value = false;
      return true;
   }
   return false;
}

std::string sysLineParseXml::GetStateDump() const
{
   std::ostringstream os;
   os << "Dump for sysLineParseXml"<< std::endl;
   os << "   m_Line  = "<< m_Line  << std::endl;
   os << "   m_Type = "<< m_Type   << std::endl;
   os << "   m_Name = "<< m_Name   << std::endl;
   os << "   m_Value = "<< m_Value << std::endl;
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
   std::string tmp;
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

bool SimpleFloatParse(const char* lpszText, Float64& d)
{
	CHECK(lpszText != 0);
	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	char chFirst = lpszText[0];
   char* stopstr;
	d = strtod(lpszText, &stopstr);
	if (d == 0.0 && chFirst != '0')
		return false;   // could not convert
	while (*stopstr == ' ' || *stopstr == '\t')
		stopstr++;

	if (*stopstr != '\0')
		return false;   // not terminated properly

	return true;
}

