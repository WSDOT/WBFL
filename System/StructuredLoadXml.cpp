///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free
// Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
///////////////////////////////////////////////////////////////////////
#include <System\SysLib.h>
#include <System\StructuredLoadXml.h>
#include <istream>
#include <list>

#include "FindReplaceAll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::System;

// Utility function to parse a BSTR to double
inline Float64 ConvertBSTRtoFloat(const BSTR bstr)
{
   USES_CONVERSION;
   return _tstof(OLE2T(bstr));
}

// This class is implemented with the famous PIMPL idiom.
// This is the implementation class
namespace WBFL
{
   namespace System
   {
      class StructuredLoadXml_Impl : public IStructuredLoad
      {
      public:
         StructuredLoadXml_Impl();
         virtual ~StructuredLoadXml_Impl();

         StructuredLoadXml_Impl(const StructuredLoadXml_Impl&) = delete;
         StructuredLoadXml_Impl& operator=(const StructuredLoadXml_Impl&) = delete;

         void BeginLoad(IStream* pis);
         void EndLoad();
         virtual bool BeginUnit(LPCTSTR name) override;
         virtual bool EndUnit() override;
         virtual Float64 GetVersion() override;
         virtual Float64 GetParentVersion() override;
         virtual std::_tstring GetParentUnit() override;
         virtual Float64 GetTopVersion() override;
         virtual bool Property(LPCTSTR name, std::_tstring* pvalue) override;
         virtual bool Property(LPCTSTR name, Float64* pvalue) override;
         virtual bool Property(LPCTSTR name, Int16* pvalue) override;
         virtual bool Property(LPCTSTR name, Uint16* pvalue) override;
         virtual bool Property(LPCTSTR name, Int32* pvalue) override;
         virtual bool Property(LPCTSTR name, Uint32* pvalue) override;
         virtual bool Property(LPCTSTR name, Int64* pvalue) override;
         virtual bool Property(LPCTSTR name, Uint64* pvalue) override;
         virtual bool Property(LPCTSTR name, LONG* pvalue) override;
         virtual bool Property(LPCTSTR name, ULONG* pvalue) override;
         virtual bool Property(LPCTSTR name, bool* pvalue) override;
         virtual bool Eof() const override;
         virtual std::_tstring GetStateDump() const override;
         virtual std::_tstring GetUnit() const override;

      private:
         IStream*                        m_pIStream;
         MSXML::IXMLDOMDocumentPtr       m_spDoc; // the top-level document node
         long          m_Level;   // unit nesting level

         // have to keep track of recursive data structure
         struct ListItem
         {
            std::_tstring           Name;
            Float64                Version;
            MSXML::IXMLDOMNodePtr spCurrentUnit;
            MSXML::IXMLDOMNodePtr spCurrentChild;
         };
         typedef std::list<ListItem> UnitList;
         typedef UnitList::const_iterator UnitListConstIterator;
         UnitList   m_UnitList; // stack of information about current units.

         MSXML::IXMLDOMNodePtr GetCurrentNode(LPCTSTR name);
         bool GetProperty(LPCTSTR name, _variant_t* pval);
         void ReadNext();

      public:
      #if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST
      };
   };
};


StructuredLoadXml::StructuredLoadXml():
m_pImp(std::make_unique<StructuredLoadXml_Impl>())
{
   PRECONDITION(m_pImp.get() != nullptr);
}

// why is this declared here? It is what you need to do to get the PIMPL idiom 
// to work with std::unique_ptr<>. See https://www.fluentcpp.com/2017/09/22/make-pimpl-using-unique_ptr/.
StructuredLoadXml::~StructuredLoadXml() = default;

void StructuredLoadXml::BeginLoad(IStream* pis)
{
   m_pImp->BeginLoad(pis);
}

void StructuredLoadXml::EndLoad()
{
   m_pImp->EndLoad();
}

bool StructuredLoadXml::BeginUnit(LPCTSTR name)
{
   return m_pImp->BeginUnit(name);
}

bool StructuredLoadXml::EndUnit()
{
   return m_pImp->EndUnit();
}

Float64 StructuredLoadXml::GetVersion()
{
   return m_pImp->GetVersion();
}

Float64 StructuredLoadXml::GetParentVersion()
{
   return m_pImp->GetParentVersion();
}

std::_tstring StructuredLoadXml::GetParentUnit()
{
   return m_pImp->GetParentUnit();
}

Float64 StructuredLoadXml::GetTopVersion()
{
   return m_pImp->GetTopVersion();
}

bool StructuredLoadXml::Property(LPCTSTR name, std::_tstring* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Property(LPCTSTR name, Float64* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Property(LPCTSTR name, Int16* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Property(LPCTSTR name, Uint16* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Property(LPCTSTR name, Int32* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Property(LPCTSTR name, Uint32* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Property(LPCTSTR name, Int64* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Property(LPCTSTR name, Uint64* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Property(LPCTSTR name, LONG* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Property(LPCTSTR name, ULONG* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Property(LPCTSTR name, bool* pvalue)
{
   return m_pImp->Property(name, pvalue);
}

bool StructuredLoadXml::Eof() const
{
   return m_pImp->Eof();
}

std::_tstring StructuredLoadXml::GetStateDump() const
{
   return m_pImp->GetStateDump();
}

std::_tstring StructuredLoadXml::GetUnit() const
{
   return m_pImp->GetUnit();
}

#if defined _DEBUG
bool StructuredLoadXml::AssertValid() const
{
   return m_pImp->AssertValid();
}

void StructuredLoadXml::Dump(WBFL::Debug::LogContext& os) const
{
   m_pImp->Dump(os);
}

#endif // _DEBUG

#if defined _UNITTEST
bool StructuredLoadXml::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("StructuredLoadXml");

   // Tests performed by main UnitTest in project.

   TESTME_EPILOG("StructuredLoadXml");
}

#endif // _UNITTEST


HRESULT CheckLoad(MSXML::IXMLDOMDocument* pDoc);
void ThrowParseError(MSXML::IXMLDOMParseErrorPtr pXMLError, LPCTSTR file, int line);

StructuredLoadXml_Impl::StructuredLoadXml_Impl():
m_Level(0),
m_pIStream(0),
m_spDoc(0)
{
   // make sure com is up and ready
   HRESULT hr = ::CoInitialize(nullptr);
}

StructuredLoadXml_Impl::~StructuredLoadXml_Impl()
{
   WARN( m_pIStream != 0, "Did you forget to call FinishLoad()?" );

   // this is a shitty way to make exception safe, but BeginLoad Forces this...
   if (m_pIStream!=0)
      m_pIStream->Release();

   ::CoUninitialize();
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void StructuredLoadXml_Impl::BeginLoad(IStream* pis)
{
   PRECONDITION( pis != nullptr );
   CHECK(!(bool)m_spDoc);   //  previously used and not cleaned up?
   CHECK(m_pIStream==nullptr); // "                                   "

   if (!m_UnitList.empty())
      m_UnitList.clear();

   HRESULT hr = 0;

   try
   {
      m_pIStream = pis;
      m_pIStream->AddRef();

      // create our document
      MSXML::IXMLDOMDocumentPtr pDoc(__uuidof(MSXML::DOMDocument60));
      if (!(bool)pDoc)
      {
         THROW_LOAD(CantInitializeTheParser,this);
      }

      m_spDoc = pDoc;

      // Load document and make sure it loads correctly
      m_spDoc->load(m_pIStream);
      if (m_pIStream==nullptr)
      {
         THROW_LOAD(InvalidFileFormat,this);
      }

      hr = CheckLoad(m_spDoc);
      if (FAILED(hr))
      {
         THROW_LOAD(InvalidFileFormat,this);
      }

      // make sure document is not empty
      if (m_spDoc->hasChildNodes())
      {
         // first node must be 'xml' node
         MSXML::IXMLDOMNodePtr xmlnode = m_spDoc->firstChild;
         _bstr_t nodenm = xmlnode->nodeName;
         if (nodenm!=_bstr_t("xml") && nodenm!=_bstr_t("XML"))
            THROW_LOAD(InvalidFileFormat,this);

         // push our top-level collection onto the stack
         ListItem tmp;
         tmp.Name = _T("Document");
         tmp.Version = 0.0;
         tmp.spCurrentChild = pDoc->GetdocumentElement();
         tmp.spCurrentUnit =  pDoc;

         m_UnitList.push_back(tmp);
      }
      else
      {
         THROW_LOAD(InvalidFileFormat,this);
      }
   }
   catch(XStructuredLoad &e) 
   {
      throw e;
   }
#if defined __WARN
   catch(_com_error& e) 
#else
   catch(_com_error& /*e*/) 
#endif // __WARN
   {
      WARN(0,(LPTSTR)(e.Description()));
      THROW_LOAD(InvalidFileFormat,this);
   }
   catch(...)
   {
      THROW_LOAD(InvalidFileFormat,this);
   }
}

void StructuredLoadXml_Impl::EndLoad()
{
   PRECONDITION( m_pIStream );
   WBFL::Debug::Diagnostics::EnableWarnPopup(false);
   WARN(m_Level!=0,"Error: BeginUnit-EndUnit mismatch in structured load");
#if defined _DEBUG
   UnitListConstIterator iter(m_UnitList.begin());
   UnitListConstIterator end(m_UnitList.end());
   for ( ; iter != end; iter++ )
   {
      const ListItem& item = *iter;
      //WATCH(_T("Open Unit: ") << item.Name);
   }
#endif
   WBFL::Debug::Diagnostics::EnableWarnPopup(true);

   // free up com resources
   m_pIStream->Release();
   m_pIStream = 0;

   if (!m_UnitList.empty())
      m_UnitList.clear();

   m_spDoc.Release();
   m_spDoc = 0;

}

bool StructuredLoadXml_Impl::BeginUnit(LPCTSTR name)
{
   ASSERTVALID;
   bool retval = false;

   try
   {
      // look for an element in current collection with name
      MSXML::IXMLDOMNodePtr ptest = GetCurrentNode(name);
      if ((bool)ptest)
      {
         // get the version of the unit
         Float64 vers=0.0;
         _bstr_t bsvers;
         try
         {
            // this will throw if no version attribute - not a big deal.
            bsvers = ptest->attributes->getNamedItem("version")->text;
            vers = ConvertBSTRtoFloat(bsvers);
            //_variant_t vvers(bsvers);
            //vers = atof(bsvers);

// RAB: 11/29/07
// ChangeType is an easy function to use, but it doesn't work for us if foreign locals are used
// for example, if the '.' is the 1000th separator then a version string of "1.5" because the floating
// point value of 15.0. For this reason I've switched to using the slightly less robust atof function

//            vvers.ChangeType(VT_R8);
//            vers = (Float64)vvers;
         }
         catch (...)
         {;} // again, no big deal.

         // push new unit onto the stack
         m_Level++;
         ListItem tmp;
         tmp.Name = std::_tstring(name);
         tmp.Version = vers;
         if (ptest->hasChildNodes())
            tmp.spCurrentChild = ptest->firstChild;
         else
            tmp.spCurrentChild = 0;

         tmp.spCurrentUnit = ptest;

         m_UnitList.push_back(tmp);
         retval = true; // got our work done
      }
   }
#if defined __WARN
   catch(_com_error& e) 
#else
   catch(_com_error& /*e*/) 
#endif // __WARN
   {
      WARN(0,(LPTSTR)(e.Description()));
      THROW_LOAD(InvalidFileFormat,this);
   }
   catch(...)
   {
      THROW_LOAD(InvalidFileFormat,this);
   }

   //WATCH(_T("BeginUnit: ") << m_UnitList.back().Name);

   return retval;
}

bool StructuredLoadXml_Impl::EndUnit()
{
   ASSERTVALID;

   try
   {
      // can't go negative here.
      if (m_Level<=0)
         THROW_LOAD(InvalidFileFormat,this);

      //WATCH(_T("EndUnit: ") << m_UnitList.back().Name);

      // climb back up the tree
      m_UnitList.pop_back();
      m_Level--;
      ReadNext(); // go on to next node
      ASSERTVALID;
      return true;
   }
   catch(XStructuredLoad &e) 
   {
      throw e;
   }
#if defined __WARN
   catch(_com_error& e) 
#else
   catch(_com_error& /*e*/) 
#endif // __WARN
   {
      WARN(0,(LPTSTR)(e.Description()));
      THROW_LOAD(InvalidFileFormat,this);
   }
   catch(...)
   {
      THROW_LOAD(InvalidFileFormat,this);
   }

   return false;
}

Float64 StructuredLoadXml_Impl::GetVersion()
{
   ASSERTVALID;
   CHECK(!m_UnitList.empty());
   return m_UnitList.back().Version;
}

Float64 StructuredLoadXml_Impl::GetParentVersion()
{
   ASSERTVALID;
   CHECK(!m_UnitList.empty());
   UnitListConstIterator it = m_UnitList.end(); // one past end
   it--; // last item in the list (this is the current unit)
   it--; // back up one, this is the parent
   return (*it).Version;
}

std::_tstring StructuredLoadXml_Impl::GetParentUnit()
{
   ASSERTVALID;
   CHECK(!m_UnitList.empty());
   UnitListConstIterator it = m_UnitList.end(); // one past end
   it--; // last item in the list (this is the current unit)
   it--; // back up one, this is the parent
   return (*it).Name;
}

Float64 StructuredLoadXml_Impl::GetTopVersion()
{
   ASSERTVALID;
   CHECK(m_UnitList.size()>1);
   // dummy document node is first in stack - top node is second
   UnitListConstIterator it = m_UnitList.begin();
   it ++;
   return it->Version;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, std::_tstring* pvalue)
{
   bool retval = false;
   _variant_t val;
   if (GetProperty(name, &val))
   {
      // need to take out special characters &,',",<,>
      std::_tstring tmp((LPTSTR)(_bstr_t)val);
      find_replace_all(&tmp, _T("&amp;"),_T("&"));
      find_replace_all(&tmp, _T("&lt;"),_T("<"));
      find_replace_all(&tmp, _T("&gt;"),_T(">"));
      find_replace_all(&tmp, _T("&sq;"),_T("'"));
      find_replace_all(&tmp, _T("&dq;"),_T("\""));
      *pvalue = tmp;
      retval = true;
   }

   return retval;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, Float64* pvalue)
{
   bool retval = false;
   _variant_t val;
   if (GetProperty(name, &val))
   {
      *pvalue = ConvertBSTRtoFloat(val.bstrVal);
      //*pvalue = atof((_bstr_t)val);
      retval = true;
   }

   return retval;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, Int16* pvalue)
{
   Int32 val;
   if (Property(name, &val))
   {
      *pvalue = (Int16)val;
      CHECK(Uint16_Max>=val); // check for overflows
      return true;
   }
   else
      return false;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, Uint16* pvalue)
{
   Uint32 val;
   if (Property(name, &val))
   {
      *pvalue = (Uint16)val;
      CHECK(Uint16_Max>=val); // check for overflows
      return true;
   }
   else
      return false;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, Int32* pvalue)
{
   bool retval = false;
   _variant_t val;
   if (GetProperty(name, &val))
   {
      *pvalue = (Int32)val;
      retval = true;
   }

   return retval;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, Uint32* pvalue)
{
   bool retval = false;
   _variant_t val;
   if (GetProperty(name, &val))
   {
      // variant does not handle large unsigned values well
      try
      {
         *pvalue = (Uint32)val;
      }
      catch(...) 
      {
         // variant couldn't parse, so try brute force
         _bstr_t bval(val);
         LPTSTR sv = (LPTSTR)bval;
         LPTSTR* ev = &sv + bval.length();
         Uint32 uval = _tcstoul(sv,ev,10);
         if (uval==0 && *sv != '0')
            THROW_LOAD(InvalidFileFormat,this);

         *pvalue = uval;
      }
      retval = true; // got our work done
   }
   return retval;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, Int64* pvalue)
{
   bool retval = false;
   _variant_t val;
   if (GetProperty(name, &val))
   {
      *pvalue = (Int64)val;
      retval = true;
   }

   return retval;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, Uint64* pvalue)
{
   bool retval = false;
   _variant_t val;
   if (GetProperty(name, &val))
   {
      // variant does not handle large unsigned values well
      try
      {
         *pvalue = (Uint64)val;
      }
      catch(...) 
      {
         // variant couldn't parse, so try brute force
         _bstr_t bval(val);
         TCHAR* sv = (TCHAR*)bval;
         Uint64 uval = _tcstoui64(sv,nullptr,10);
         if ( uval == 0 && *sv != _T('0'))
            THROW_LOAD(InvalidFileFormat,this);

         *pvalue = uval;
      }
      retval = true; // got our work done
   }
   return retval;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, LONG* pvalue)
{
   bool retval = false;
   _variant_t val;
   if (GetProperty(name, &val))
   {
      *pvalue = (LONG)val;
      retval = true;
   }

   return retval;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, ULONG* pvalue)
{
   bool retval = false;
   _variant_t val;
   if (GetProperty(name, &val))
   {
      // variant does not handle large unsigned values well
      try
      {
         *pvalue = (ULONG)val;
      }
      catch(...) 
      {
         // variant couldn't parse, so try brute force
         _bstr_t bval(val);
         LPTSTR sv = (LPTSTR)bval;
         LPTSTR* ev = &sv + bval.length();
         ULONG uval = _tcstoul(sv,ev,10);
         if (uval==0 && *sv != '0')
            THROW_LOAD(InvalidFileFormat,this);

         *pvalue = uval;
      }
      retval = true; // got our work done
   }
   return retval;
}

bool StructuredLoadXml_Impl::Property(LPCTSTR name, bool* pvalue)
{
   bool retval = false;
   _variant_t val;
   if (GetProperty(name, &val))
   {
      *pvalue = (bool)val;
      retval = true;
   }

   return retval;
}

bool StructuredLoadXml_Impl::Eof() const
{
   // doesn't make any sense in this context
   return false;
}

std::_tstring StructuredLoadXml_Impl::GetStateDump() const
{
   // use Dump
   std::_tostringstream os;
   os << _T("Dump for StructuredLoadXml_Impl") << std::endl;
   os << _T("  Level       = ") << m_Level << std::endl;
   os << _T("  Units: <name, version> ") << std::endl;
   for (UnitListConstIterator it=m_UnitList.begin(); it!=m_UnitList.end(); it++)
      os <<_T("    <")<<(*it).Name<<_T(", ")<<(*it).Version<<_T(">")<<std::endl;
   return os.str(); 
}

std::_tstring StructuredLoadXml_Impl::GetUnit() const
{
   PRECONDITION(!m_UnitList.empty());
   const MSXML::IXMLDOMNodePtr& rUnit = m_UnitList.back().spCurrentUnit;

   _bstr_t bstrXML = rUnit->xml;

   return std::_tstring((LPTSTR)bstrXML);
}

#if defined _DEBUG
bool StructuredLoadXml_Impl::AssertValid() const
{
   // cannot have negative levels
   if (m_Level<0) 
      return false;

   // pointers have to be up and ready
   if (m_pIStream==0)
      return false;
   if (m_spDoc==0)
      return false;
   if (m_UnitList.empty())
      return false;

   return true;
}

void StructuredLoadXml_Impl::Dump(WBFL::Debug::LogContext& os) const
{
   std::_tstring tmp;
   tmp = GetStateDump();
   os << tmp << WBFL::Debug::endl;
}

#endif // _DEBUG

#if defined _UNITTEST
bool StructuredLoadXml_Impl::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("StructuredLoadXml_Impl");

   // Tests performed by main UnitTest in project.

   TESTME_EPILOG("StructuredLoadXml_Impl");
}

#endif // _UNITTEST

////////////////////////////////////////////////////////////////////////////
// Helper function: Check load results
////////////////////////////////////////////////////////////////////////////
HRESULT CheckLoad(MSXML::IXMLDOMDocument* pDoc)
{
    // And since we don't have the VARIANT_BOOL from load we
    // need to check the parse Error errorCode property to see
    // if everything went ok.
   LONG errorCode = E_FAIL;
   HRESULT hr=S_OK;
   try
   {
       MSXML::IXMLDOMParseErrorPtr pXMLError = pDoc->parseError;
       long code = pXMLError->errorCode;
       if (code != 0)
       {
           ThrowParseError(pXMLError,_T(__FILE__),__LINE__);
       }
       else
       {
           //WATCH(_T("XML document loaded successfully"));
       }
   }
   catch (XStructuredLoad& e)
   {
      throw e;
   }
   catch(...)
   {
      hr = errorCode;
   }
   return hr;
}

////////////////////////////////////////////////////////////////////////////
// Helper function: Report parsing error information
////////////////////////////////////////////////////////////////////////////
void ThrowParseError(MSXML::IXMLDOMParseErrorPtr pXMLError, LPCTSTR file, int lineno)
{
   long line, linePos;
   LONG errorCode;
   _bstr_t pBURL, pBReason;
   std::_tostringstream os;

   // create and throw and exception
   XStructuredLoad except(XStructuredLoad::InvalidFileFormat, file, lineno );

   try
   {
      line = pXMLError->line;
      linePos = pXMLError->linepos;
      errorCode = pXMLError->errorCode;
      pBURL = pXMLError->url;
      pBReason = pXMLError->reason;

      if (line > 0)
      {
        os << _T("Error in xml file on line ")<< line<<_T(", position ")<<linePos;
        if ( (LPTSTR)pBURL )
           os <<_T(" in \"")<<(LPTSTR)pBURL;
        os <<_T("\" Reason was ")<<(LPTSTR)pBReason; 
      }
      else
      {
         os<<_T("Error in xml file - location unknown");
      }
   }
   catch(...)
   {
   }

  if (os.str().size()>0)
     except.SetExtendedMessage(os.str().c_str());

  throw except;
}

MSXML::IXMLDOMNodePtr StructuredLoadXml_Impl::GetCurrentNode(LPCTSTR name)
{
   PRECONDITION(!m_UnitList.empty());
   _bstr_t bname(name);
   const MSXML::IXMLDOMNodePtr& rback = m_UnitList.back().spCurrentChild;
   if ((bool)rback)
   {
      _bstr_t nodenm = rback->nodeName;
      if (nodenm == bname)
         return rback;
      else
         return nullptr;
   }
   else
      return nullptr;
}

bool StructuredLoadXml_Impl::GetProperty(LPCTSTR name, _variant_t* pval)
{
   ASSERTVALID;
   bool retval = false;
   try
   {
      // look for an element in current collection with name
      MSXML::IXMLDOMNodePtr ptest = GetCurrentNode(name);
      if ((bool)ptest)
      {
         // ask parser if a Property was last parsed item
         if (MSXML::NODE_ELEMENT==ptest->nodeType)
         {
            *pval = ptest->nodeTypedValue;
            // read the next node
            ReadNext(); 
            retval = true; // got our work done
         }
      }
   }
#if defined __WARN
   catch(_com_error& e) 
#else
   catch(_com_error& /*e*/) 
#endif // __WARN
   {
      WARN(0,(LPTSTR)(e.Description()));
      THROW_LOAD(InvalidFileFormat,this);
   }
   catch(...)
   {
      THROW_LOAD(InvalidFileFormat,this);
   }

   return retval;
}

void StructuredLoadXml_Impl::ReadNext()
{
   PRECONDITION(!m_UnitList.empty());
   MSXML::IXMLDOMNodePtr& rback = m_UnitList.back().spCurrentChild;

   if ((bool)rback)
   {
      rback = rback->nextSibling;
   }
   else
      CHECK(0); // should not be trying to read next if previous was null
}