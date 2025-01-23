///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>
#include <System\StructuredSaveXml.h>
#include <System\XStructuredSave.h>
#include <System\XProgrammingError.h>
#include <istream>
#include <iomanip>
#include <cctype>
#include "FindReplaceAll.h"

#include <list>

using namespace WBFL::System;

// This class is implemented with the famous PIMPL idiom.
// This is the implementation class
namespace WBFL
{
   namespace System
   {
      class SYSCLASS StructuredSaveXml_Impl : public IStructuredSave
      {
      public:
         StructuredSaveXml_Impl();
         virtual ~StructuredSaveXml_Impl();

         StructuredSaveXml_Impl(const StructuredSaveXml_Impl&) = delete;
         StructuredSaveXml_Impl& operator=(const StructuredSaveXml_Impl&) = delete;

         void BeginSave(IStream* pis);
         void EndSave();
         virtual void BeginUnit(LPCTSTR name, Float64 version=0.0);
         virtual void EndUnit();
         virtual Float64 GetVersion();
         virtual Float64 GetParentVersion();
         virtual std::_tstring GetParentUnit();
         virtual Float64 GetTopVersion();
         virtual void Property(LPCTSTR name, LPCTSTR value);
         virtual void Property(LPCTSTR name, Float64 value);
         virtual void Property(LPCTSTR name, Int16 value);
         virtual void Property(LPCTSTR name, Uint16 value);
         virtual void Property(LPCTSTR name, Int32 value);
         virtual void Property(LPCTSTR name, Uint32 value);
         virtual void Property(LPCTSTR name, Int64 value);
         virtual void Property(LPCTSTR name, Uint64 value);
         virtual void Property(LPCTSTR name, LONG value);
         virtual void Property(LPCTSTR name, ULONG value);
         virtual void Property(LPCTSTR name, bool value);

         virtual void PutUnit(LPCTSTR xml);

      private:
         IStream*                        m_pOStream;
         MSXML::IXMLDOMDocumentPtr       m_spDoc;
         MSXML::IXMLDOMNodePtr           m_spCurrentUnit;
         long          m_Level; // unit nesting level
         using ListItem = std::pair<std::_tstring, Float64>;
         using UnitList = std::list<ListItem>;
         using UnitListConstIterator = UnitList::const_iterator;
         UnitList   m_UnitList; // stack of information about current units.


         MSXML::IXMLDOMNodePtr MakeChildNode(LPCTSTR name, Float64 vers=0.0);
      };
   };
};

StructuredSaveXml::StructuredSaveXml():
m_pImp(std::make_unique<StructuredSaveXml_Impl>())
{
   PRECONDITION(m_pImp.get() != nullptr);
}

// why is this declared here? It is what you need to do to get the PIMPL idiom 
// to work with std::unique_ptr<>. See https://www.fluentcpp.com/2017/09/22/make-pimpl-using-unique_ptr/.
StructuredSaveXml::~StructuredSaveXml() = default;

void StructuredSaveXml::BeginSave(IStream* pis)
{
   m_pImp->BeginSave(pis);
}

void StructuredSaveXml::EndSave()
{
   m_pImp->EndSave();
}

void StructuredSaveXml::BeginUnit(LPCTSTR name, Float64 version)
{
   m_pImp->BeginUnit(name,version);
}

void StructuredSaveXml::EndUnit()
{
   m_pImp->EndUnit();
}

Float64 StructuredSaveXml::GetVersion()
{
   return m_pImp->GetVersion();
}

Float64 StructuredSaveXml::GetParentVersion()
{
   return m_pImp->GetParentVersion();
}

std::_tstring StructuredSaveXml::GetParentUnit()
{
   return m_pImp->GetParentUnit();
}

Float64 StructuredSaveXml::GetTopVersion()
{
   return m_pImp->GetTopVersion();
}

void StructuredSaveXml::Property(LPCTSTR name, LPCTSTR value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::Property(LPCTSTR name, Float64 value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::Property(LPCTSTR name, Int16 value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::Property(LPCTSTR name, Uint16 value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::Property(LPCTSTR name, Int32 value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::Property(LPCTSTR name, Uint32 value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::Property(LPCTSTR name, Int64 value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::Property(LPCTSTR name, Uint64 value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::Property(LPCTSTR name, LONG value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::Property(LPCTSTR name, ULONG value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::Property(LPCTSTR name, bool value)
{
   m_pImp->Property(name,value);
}

void StructuredSaveXml::PutUnit(LPCTSTR xml)
{
   m_pImp->PutUnit(xml);
}


StructuredSaveXml_Impl::StructuredSaveXml_Impl():
m_pOStream(0),
m_Level(0),
m_spDoc(0),
m_spCurrentUnit(0)
{
   // make sure com is up and ready
   HRESULT hr = ::CoInitialize(nullptr);
}

StructuredSaveXml_Impl::~StructuredSaveXml_Impl()
{
   ::CoUninitialize();
}

void StructuredSaveXml_Impl::BeginSave(IStream* pis)
{
   PRECONDITION( pis != nullptr );
   CHECK(!(bool)m_spDoc);
   CHECK(m_pOStream==nullptr); // previously used and not cleaned up?

   if ((bool)m_spCurrentUnit)
      m_spCurrentUnit.Release();

   HRESULT hr = 0;

   try
   {
      m_pOStream = pis;
      m_pOStream->AddRef();

      // create our document
      MSXML::IXMLDOMDocumentPtr pDoc(__uuidof(MSXML::DOMDocument60));
      if (!(bool)pDoc)
      {
         THROW(XStructuredSave,CantInitializeTheParser);
      }

      // add a processing instruction for xml
      _bstr_t targ("xml");
      _bstr_t data("version=\"1.0\""); 
      MSXML::IXMLDOMProcessingInstructionPtr pi = pDoc->createProcessingInstruction (targ, data);
      pDoc->appendChild(pi);

      m_spDoc = pDoc;
      m_spCurrentUnit = pDoc;
   }
#if defined __WARN
   catch(_com_error& e) 
#else
   catch(_com_error& /*e*/) 
#endif // __WARN
   {
      WARN(0,(LPTSTR)(e.Description()));
      THROW(XStructuredSave,CantInitializeTheParser);
   }
   catch(...)
   {
      THROW(XStructuredSave,CantInitializeTheParser);
   }
}

void StructuredSaveXml_Impl::EndSave()
{
   CHECKX(m_Level==0,_T("Error: BeginUnit-EndUnit mismatch in structured save"));
   try
   {
      // Save document and make sure it saves correctly
      m_spDoc->save(m_pOStream);
      if (m_pOStream==nullptr)
      {
         THROW(XStructuredSave,BadWrite);
      }

      // free up com resources
      m_pOStream->Release();
      m_pOStream = 0;

      m_spCurrentUnit.Release();
      m_spCurrentUnit = 0;

      m_spDoc.Release();
      m_spDoc = 0;
   }
#if defined __WARN
   catch(_com_error& e) 
#else
   catch(_com_error& /*e*/) 
#endif // __WARN
   {
      WARN(0,(LPTSTR)(e.Description()));
      THROW(XStructuredSave,BadWrite);
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::BeginUnit(LPCTSTR name, Float64 version)
{
   ASSERTVALID;
   
   try
   {
     MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name, version);
     if (!(bool)pchild)
         THROW(XStructuredSave,BadWrite);

     // walk down to next level
     m_spCurrentUnit = pchild;
     m_Level++;
     m_UnitList.emplace_back(name,version);
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::EndUnit()
{
   ASSERTVALID;
   
   try
   {
      // pop back up the tree
      m_spCurrentUnit = m_spCurrentUnit->parentNode;
      if (!(bool)m_spCurrentUnit)
      {
         CHECKX(0,_T("Popped too far - no parent for child node"));
         THROW(XStructuredSave,BadWrite);
      }

      m_UnitList.pop_back();
      m_Level--;

   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }

   ASSERTVALID;
}

Float64 StructuredSaveXml_Impl::GetVersion()
{
   ASSERTVALID;
   return m_UnitList.back().second;
}

Float64 StructuredSaveXml_Impl::GetParentVersion()
{
   ASSERTVALID;
   UnitListConstIterator iter = m_UnitList.end();
   iter--;
   iter--;
   return (*iter).second;
}

std::_tstring StructuredSaveXml_Impl::GetParentUnit()
{
   ASSERTVALID;
   UnitListConstIterator iter = m_UnitList.end();
   iter--;
   iter--;
   return (*iter).first;
}

Float64 StructuredSaveXml_Impl::GetTopVersion()
{
   ASSERTVALID;
   return m_UnitList.front().second;
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, LPCTSTR value)
{
   ASSERTVALID;

   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(XStructuredSave,BadWrite);

      // made node, now do data conversion
      // first need to take out special characters &,',",<,>
      std::_tstring tmp(value);
      find_replace_all(&tmp, _T("&") , _T("&amp;"));
      find_replace_all(&tmp, _T("<") , _T("&lt;" ));
      find_replace_all(&tmp, _T(">") , _T("&gt;" ));
      find_replace_all(&tmp, _T("'") , _T("&sq;" ));
      find_replace_all(&tmp, _T("\""), _T("&dq;" ));

      _variant_t val(tmp.c_str());
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, Float64 value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(XStructuredSave,BadWrite);

      // made node, now do data conversion
      std::_tostringstream os;
      os << std::setprecision(17) << value;
      pchild->text = _bstr_t(os.str().c_str());
      // RAB: 11/29/2007
      // coercing the variant to a string causes the floating point number to be
      // formatted according to the locale. This is problematic as the decimal separator
      // could either be a '.' or a ','. Using the string stream above seems to solve this 
      // problem
//      _variant_t val(value);
//      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, Int16 value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(XStructuredSave,BadWrite);

      // made node, now do data conversion
      _variant_t val(value);
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, Uint16 value)
{
   Property(name, (Uint32)value);
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, Int32 value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(XStructuredSave,BadWrite);

      // made node, now do data conversion
      _variant_t val(value);
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, Uint32 value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(XStructuredSave,BadWrite);

      // made node, now do data conversion
      std::_tostringstream os;
      os<<value;
      _variant_t val(os.str().c_str());
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, Int64 value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(XStructuredSave,BadWrite);

      // made node, now do data conversion
      _variant_t val(value);
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, Uint64 value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(XStructuredSave,BadWrite);

      // made node, now do data conversion
      std::_tostringstream os;
      os<<value;
      _variant_t val(os.str().c_str());
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, LONG value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(XStructuredSave,BadWrite);

      // made node, now do data conversion
      _variant_t val(value);
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, ULONG value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(XStructuredSave,BadWrite);

      // made node, now do data conversion
      std::_tostringstream os;
      os<<value;
      _variant_t val(os.str().c_str());
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::Property(LPCTSTR name, bool value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(XStructuredSave,BadWrite);

      // made node, now do data conversion
      _variant_t val(value);
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(XStructuredSave,BadWrite);
   }
}

void StructuredSaveXml_Impl::PutUnit(LPCTSTR xml)
{
   MSXML::IXMLDOMDocumentPtr pDoc(__uuidof(MSXML::DOMDocument60));
   pDoc->loadXML(_bstr_t(xml));

   MSXML::IXMLDOMNodePtr pNewNode = pDoc->firstChild;
   m_spCurrentUnit->appendChild(pNewNode);
}

////////////////////////////////////////////////////////////////////////////
// Helper function: Make a named child node
////////////////////////////////////////////////////////////////////////////
MSXML::IXMLDOMNodePtr StructuredSaveXml_Impl::MakeChildNode(LPCTSTR name, Float64 vers)
{
   std::_tstring strName(name);
   if (std::find_if(strName.begin(), strName.end(), [](auto& t) {return std::isspace(t) != 0;}) != strName.end())
   {
      WBFL::Debug::Message::Precondition(_T("Node names cannot contain spaces"), _T(__FILE__), __LINE__);
   }

   ASSERTVALID;

   MSXML::IXMLDOMNodePtr pchild;
   try
   {
     _variant_t type((long)MSXML::NODE_ELEMENT);
     MSXML::IXMLDOMNodePtr pnewunit = m_spDoc->createNode(type, name, "");
     if (!(bool)pnewunit)
         THROW(XStructuredSave,BadWrite);

     pchild = m_spCurrentUnit->appendChild(pnewunit);
     if (!(bool)pchild)
         THROW(XStructuredSave,BadWrite);

     if (vers!=0.0)
     {
        // we have a version - com-style cast to an element and set the version
        MSXML::IXMLDOMElementPtr pel;
        HRESULT hr = pchild->QueryInterface(__uuidof(MSXML::IXMLDOMElement), (void**)&pel);
        if (SUCCEEDED(hr) && pel!=0)
        {
           _variant_t var((Float64)vers);
           pel->setAttribute("version",var);
        }
        else
        {
           CHECK(0); // eating our own dog food here. this should be impossible.
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
      THROW(XStructuredSave,BadWrite);
   }
   catch(...)
   {
      WARN(0,"Caught unknown exception");
      THROW(XStructuredSave,BadWrite);
   }

   return pchild;
}