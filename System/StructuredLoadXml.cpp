///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
   sysStructuredLoadXml
****************************************************************************/

#include <System\StructuredLoadXml.h>
#include <System\Tokenizer.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////// FREE FUNCTIONS
// free function to eat white space
std::istream& eatwhite(std::istream& is);
// a free function to read a line trimmed of whitespace
void get_clean_line(std::istream& is, std::string& str);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysStructuredLoadXml::sysStructuredLoadXml():
m_pIStream(0),
m_Level(0),
m_LineNumber(0)
{
}

sysStructuredLoadXml::~sysStructuredLoadXml()
{
   WARN( m_pIStream != 0, "Did you forget to call FinishLoad()?" );
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void sysStructuredLoadXml::BeginLoad(std::istream* pis)
{
   PRECONDITION( pis != 0 );

   m_pIStream = pis;

   // save iostate of stream and restore it in destructor
   // throw exceptions for any type of i/o errors
   m_IoState = m_pIStream->exceptions();
   m_pIStream->exceptions(std::ios_base::badbit|std::ios_base::failbit|std::ios_base::eofbit);

   // read header information and compare to what we expect
   std::string lin;
   try
   {
      eatwhite(*m_pIStream);          // eat leading white space
      std::getline(*m_pIStream, lin);
   }
   catch(...)
   {
      THROW_LOAD(BadRead,this);
   }
   m_LineNumber++;

   // tokenize line to make sure xml is of right format
   // should look something like: <?xml version="1.0" ?>
   // not a perfect parse, but...
   const char* Dels[] = {"?"," ","=","<",">",0};
   sysTokenizer tokize(Dels);
   tokize.push_back(lin);
   bool failed = false;
   if (tokize.size()==3)
   {
      failed |= tokize[0] != std::string("xml");
      failed |= tokize[1] != std::string("version");
      failed |= tokize[2] != std::string("\"1.0\"");
   }
   else
   {
      failed=true;
   }

   if (failed)
   {
      // File is wrong format - need to puke
      THROW(sysXStructuredLoad,InvalidFileFormat);
   }

   // read next xml chunk
   ReadNext();
}

void sysStructuredLoadXml::EndLoad()
{
   PRECONDITION( m_pIStream != 0 );
   dbgDiagBase::EnableWarnPopup(false);
   WARN(m_Level==0,"Error: BeginUnit-EndUnit mismatch in structured load");
   dbgDiagBase::EnableWarnPopup(true);
   // restore original state
   m_pIStream->exceptions(m_IoState);
   m_pIStream = 0;
}

bool sysStructuredLoadXml::BeginUnit(const char* name)
{
   ASSERTVALID;

   std::string unit_name;
   Float64 unit_version;
   // ask parser if a BeginUnit was last parsed item
   if (m_LineParser.GetType()==sysLineParseXml::BeginUnit)
   {
      unit_name = m_LineParser.GetName();
      std::string inputname(name);
      if (unit_name==inputname)
      {
         // was a BeginUnit and the name matches
         if (!m_LineParser.GetValue(&unit_version))
            unit_version=0;
         // push unit onto stack
         m_Level++;
         m_UnitList.push_back(ListItem(unit_name,unit_version));
         // Read next line and store in buffer
         ReadNext();
         return true;
      }
   }

   return false;
}

bool sysStructuredLoadXml::EndUnit()
{
   ASSERTVALID;

   // ask parser if a EndUnit was last parsed item
   if (m_LineParser.GetType()==sysLineParseXml::EndUnit)
   {
      // can't go negative here.
      if (m_Level<=0)
         THROW_LOAD(InvalidFileFormat,this);

      m_UnitList.pop_back();
      m_Level--;
      ASSERTVALID;
      ReadNext();
      return true;
   }
   return false;
}


Float64 sysStructuredLoadXml::GetVersion()
{
   ASSERTVALID;
   CHECK(m_UnitList.size()>0);
   return m_UnitList.back().second;
}

Float64 sysStructuredLoadXml::GetParentVersion()
{
   ASSERTVALID;
   CHECK(m_UnitList.size()>0);
   UnitListConstIterator iter = m_UnitList.end();
   iter--;
   return (*iter).second;
}

Float64 sysStructuredLoadXml::GetTopVersion()
{
   ASSERTVALID;
   CHECK(m_UnitList.size()>0);
   return m_UnitList.front().second;
}

bool sysStructuredLoadXml::Property(const char* name, std::string* value)
{
   ASSERTVALID;
   // ask parser if a Property was last parsed item
   if (m_LineParser.GetType()==sysLineParseXml::Property)
   {
      std::string prop_name = m_LineParser.GetName();
      std::string inputname(name);
      if (prop_name==inputname)
      {
         std::string val;
         if (m_LineParser.GetValue(&val))
         {
            *value = val;
            ReadNext();
            return true;
         }
      }
   }
   return false;
}

bool sysStructuredLoadXml::Property(const char* name, Float64* value)
{
   ASSERTVALID;
   // ask parser if a Property was last parsed item
   if (m_LineParser.GetType()==sysLineParseXml::Property)
   {
      std::string prop_name = m_LineParser.GetName();
      std::string inputname(name);
      if (prop_name==inputname)
      {
         Float64 val;
         if (m_LineParser.GetValue(&val))
         {
            *value = val;
            ReadNext();
            return true;
         }
      }
   }
   return false;
}

bool sysStructuredLoadXml::Property(const char* name, Int16* value)
{
   ASSERTVALID;
   // ask parser if a Property was last parsed item
   if (m_LineParser.GetType()==sysLineParseXml::Property)
   {
      std::string prop_name = m_LineParser.GetName();
      std::string inputname(name);
      if (prop_name==inputname)
      {
         Int16 val;
         if (m_LineParser.GetValue(&val))
         {
            *value = val;
            ReadNext();
            return true;
         }
      }
   }
   return false;
}

bool sysStructuredLoadXml::Property(const char* name, Uint16* value)
{
   ASSERTVALID;
   // ask parser if a Property was last parsed item
   if (m_LineParser.GetType()==sysLineParseXml::Property)
   {
      std::string prop_name = m_LineParser.GetName();
      std::string inputname(name);
      if (prop_name==inputname)
      {
         Uint16 val;
         if (m_LineParser.GetValue(&val))
         {
            *value = val;
            ReadNext();
            return true;
         }
      }
   }
   return false;
}


bool sysStructuredLoadXml::Property(const char* name, Int32* value)
{
   ASSERTVALID;
   // ask parser if a Property was last parsed item
   if (m_LineParser.GetType()==sysLineParseXml::Property)
   {
      std::string prop_name = m_LineParser.GetName();
      std::string inputname(name);
      if (prop_name==inputname)
      {
         Int32 val;
         if (m_LineParser.GetValue(&val))
         {
            *value = val;
            ReadNext();
            return true;
         }
      }
   }
   return false;
}

bool sysStructuredLoadXml::Property(const char* name, Uint32* value)
{
   ASSERTVALID;
   // ask parser if a Property was last parsed item
   if (m_LineParser.GetType()==sysLineParseXml::Property)
   {
      std::string prop_name = m_LineParser.GetName();
      std::string inputname(name);
      if (prop_name==inputname)
      {
         Uint32 val;
         if (m_LineParser.GetValue(&val))
         {
            *value = val;
            ReadNext();
            return true;
         }
      }
   }
   return false;
}

bool sysStructuredLoadXml::Property(const char* name, bool* value)
{
   ASSERTVALID;
   // ask parser if a Property was last parsed item
   if (m_LineParser.GetType()==sysLineParseXml::Property)
   {
      std::string prop_name = m_LineParser.GetName();
      std::string inputname(name);
      if (prop_name==inputname)
      {
         bool val;
         if (m_LineParser.GetValue(&val))
         {
            *value = val;
            ReadNext();
            return true;
         }
      }
   }
   return false;
}


bool sysStructuredLoadXml::Eof() const
{
   if (m_LineParser.GetType()==sysLineParseXml::Eof)
      return true;
   else
      return false;
}

std::string sysStructuredLoadXml::GetStateDump() const
{
   // use Dump
   std::ostringstream os;
   os << "Dump for sysStructuredLoadXml" << std::endl;
   os << "  Level       = " << m_Level << std::endl;
   os << "  Line Number = " << m_LineNumber << std::endl;
   os << "  Units: <name, version> " << std::endl;
   for (UnitListConstIterator it=m_UnitList.begin(); it!=m_UnitList.end(); it++)
      os <<"    <"<<(*it).first<<", "<<(*it).second<<">"<<std::endl;
   os << "  LineParser" << std::endl;
   os << m_LineParser.GetStateDump();
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
void sysStructuredLoadXml::ReadNext()
{
   
   PRECONDITION( m_pIStream );
   std::string block;
   bool ateof=false; 
   sysLineParseXml::LineType lt;

   try
   {
      // Read next xml block and store in buffer
      eatwhite(*m_pIStream);
      // blocks must start with a '<'
      char br = m_pIStream->get();
      if (br!='<')
         THROW_LOAD(InvalidFileFormat,this);
      m_pIStream->putback(br);

      bool loop=true;
      bool first=true;
      while(loop&&m_pIStream)
      {
         std::string lin;
         std::getline(*m_pIStream, lin);
         if (m_pIStream)
         {
            m_LineNumber++;
            std::string::size_type dpos = lin.find("</");
            std::string::size_type apos = lin.find(">");
            std::string::size_type bpos = lin.find_last_of(">",lin.size());
            if (std::string::npos != dpos)
            {
               // found end of block - either a property or and endunit
               std::string::size_type epos = lin.find(">",dpos);
               if (std::string::npos != epos)
               {
                  block+=lin.substr(0,epos+1);
                  loop=false;
               }
               else
               {
                  THROW_LOAD(InvalidFileFormat,this);
               }
            }
            else if (first && apos==bpos && apos==lin.size()-1)
            {
               // likely at a BeginUnit
               block =lin;
               loop=false;
            }
            else
            {
               // a multi line block - re-add eol
               block+=lin;
               block+="\n";
            }
         }
         first=false;
      }
   }
   catch (...)
   {
      if (m_pIStream->eof())
      {
         m_LineParser.SetEndOfFile();
         ateof=true;
      }
      else
         THROW_LOAD(BadRead,this);
   }

   if (!ateof)
   {
      // parse the block if we're not at the end of file
      lt = m_LineParser.ParseLine(block);

      // throw if unknown
      if (lt==sysLineParseXml::Unknown)
         // huck if line type is unknown.
      {
         THROW_LOAD(InvalidFileFormat,this);
      }
   }
}


//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool sysStructuredLoadXml::AssertValid() const
{
   // cannot have negative levels
   if (m_Level<0) 
      return false;

   return true;
}

void sysStructuredLoadXml::Dump(dbgDumpContext& os) const
{
   std::string tmp;
   tmp = GetStateDump();
   os << tmp << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool sysStructuredLoadXml::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("sysStructuredLoadXml");

   // Tests performed by main UnitTest in project.

   TESTME_EPILOG("StructuredLoadXml");
}

#endif // _UNITTEST


// free function to eat white space
std::istream& eatwhite(std::istream& is)
{
   char c;
   while(is.get(c))
   {
      if (!isspace(c))
      {
         is.putback(c);
         break;
      }
   }
   return is;
}

// a free function to read a line trimmed of whitespace
void get_clean_line(std::istream& is, std::string& str)
{
   CHECK(is);
   eatwhite(is);          // eat leading white space
   std::getline(is, str); // get the rest of the line
}
