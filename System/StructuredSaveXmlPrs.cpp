///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2011  Washington State Department of Transportation
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
#include <System\StructuredSaveXmlPrs.h>
#include <System\XStructuredSave.h>
#include <istream>
#include <iomanip>
#include "FindReplaceAll.h"

#include <list>
#import  <msxml6.dll> rename_namespace("MSXML")

/****************************************************************************
Implementation CLASS
   sysStructuredSaveXmlPrs_Impl
****************************************************************************/

class SYSCLASS sysStructuredSaveXmlPrs_Impl : public sysIStructuredSave
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   sysStructuredSaveXmlPrs_Impl();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysStructuredSaveXmlPrs_Impl();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Initializes the structured save object before writing a stream.
   // Call this method before calling any other method of this class.
   void BeginSave(IStream* pis);

   //------------------------------------------------------------------------
   // Call this method after you are done with your structured save
   void EndSave();

   //------------------------------------------------------------------------
   // Mark the Beginning of a structured data chunk. This call must be always
   // balanced by a corresponding call to EndUnit. An optional version number
   // may be used to tag major units.
   // Version 0.0 means no version was attached.
   virtual void BeginUnit(LPCTSTR name, Float64 version=0.0);

   //------------------------------------------------------------------------
   // Mark the end of a structured data chunk that was started by a call to 
   // BeginUnit.
   virtual void EndUnit();

   //------------------------------------------------------------------------
   // Get the version number of the current unit
   virtual Float64 GetVersion();

   //------------------------------------------------------------------------
   // Get the version number of the unit that is the parent to this unit
   virtual Float64 GetParentVersion();

   virtual std::_tstring GetParentUnit();

   //------------------------------------------------------------------------
   // Get the version number of the top-most unit
   virtual Float64 GetTopVersion();

   //------------------------------------------------------------------------
   // Write a string property
   virtual void Property(LPCTSTR name, LPCTSTR value);

   //------------------------------------------------------------------------
   // Write a real number property
   virtual void Property(LPCTSTR name, Float64 value);

   //------------------------------------------------------------------------
   // Write an integral property
   virtual void Property(LPCTSTR name, Int16 value);

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, Uint16 value);

   //------------------------------------------------------------------------
   // Write an integral property
   virtual void Property(LPCTSTR name, Int32 value);

   //------------------------------------------------------------------------
   // Write an unsigned integral property
   virtual void Property(LPCTSTR name, Uint32 value);

   //------------------------------------------------------------------------
   // Write a bool property
   virtual void Property(LPCTSTR name, bool value);

   virtual void PutUnit(LPCTSTR xml);


   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   IStream*                        m_pOStream;
   MSXML::IXMLDOMDocumentPtr       m_spDoc;
   MSXML::IXMLDOMNodePtr           m_spCurrentUnit;
   long          m_Level; // unit nesting level
   typedef std::pair<std::_tstring, Float64> ListItem;
   typedef std::list<ListItem> UnitList;
   typedef UnitList::const_iterator UnitListConstIterator;
   UnitList   m_UnitList; // stack of information about current units.

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   sysStructuredSaveXmlPrs_Impl(const sysStructuredSaveXmlPrs_Impl&);
   sysStructuredSaveXmlPrs_Impl& operator=(const sysStructuredSaveXmlPrs_Impl&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   MSXML::IXMLDOMNodePtr MakeChildNode(LPCTSTR name, Float64 vers=0.0);
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

/****************************************************************************
CLASS
   sysStructuredSaveXmlPrs
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysStructuredSaveXmlPrs::sysStructuredSaveXmlPrs():
m_pImp(new sysStructuredSaveXmlPrs_Impl())
{
   PRECONDITION(m_pImp.get()!=0);
}

sysStructuredSaveXmlPrs::~sysStructuredSaveXmlPrs()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void sysStructuredSaveXmlPrs::BeginSave(IStream* pis)
{
   m_pImp->BeginSave(pis);
}

void sysStructuredSaveXmlPrs::EndSave()
{
   m_pImp->EndSave();
}

void sysStructuredSaveXmlPrs::BeginUnit(LPCTSTR name, Float64 version)
{
   m_pImp->BeginUnit(name,version);
}

void sysStructuredSaveXmlPrs::EndUnit()
{
   m_pImp->EndUnit();
}

Float64 sysStructuredSaveXmlPrs::GetVersion()
{
   return m_pImp->GetVersion();
}

Float64 sysStructuredSaveXmlPrs::GetParentVersion()
{
   return m_pImp->GetParentVersion();
}

std::_tstring sysStructuredSaveXmlPrs::GetParentUnit()
{
   return m_pImp->GetParentUnit();
}

Float64 sysStructuredSaveXmlPrs::GetTopVersion()
{
   return m_pImp->GetTopVersion();
}

void sysStructuredSaveXmlPrs::Property(LPCTSTR name, LPCTSTR value)
{
   m_pImp->Property(name,value);
}

void sysStructuredSaveXmlPrs::Property(LPCTSTR name, Float64 value)
{
   m_pImp->Property(name,value);
}

void sysStructuredSaveXmlPrs::Property(LPCTSTR name, Int16 value)
{
   m_pImp->Property(name,value);
}

void sysStructuredSaveXmlPrs::Property(LPCTSTR name, Uint16 value)
{
   m_pImp->Property(name,value);
}

void sysStructuredSaveXmlPrs::Property(LPCTSTR name, Int32 value)
{
   m_pImp->Property(name,value);
}

void sysStructuredSaveXmlPrs::Property(LPCTSTR name, Uint32 value)
{
   m_pImp->Property(name,value);
}

void sysStructuredSaveXmlPrs::Property(LPCTSTR name, bool value)
{
   m_pImp->Property(name,value);
}

void sysStructuredSaveXmlPrs::PutUnit(LPCTSTR xml)
{
   m_pImp->PutUnit(xml);
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
bool sysStructuredSaveXmlPrs::AssertValid() const
{
   return m_pImp->AssertValid();
}

void sysStructuredSaveXmlPrs::Dump(dbgDumpContext& os) const
{
   m_pImp->Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool sysStructuredSaveXmlPrs::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("sysStructuredSaveXmlPrs");

   // Tests in main unit testing routine

   TESTME_EPILOG("StructuredSaveXmlPrs");
}
#endif // _UNITTEST




/****************************************************************************
CLASS
   sysStructuredSaveXmlPrs_Impl
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysStructuredSaveXmlPrs_Impl::sysStructuredSaveXmlPrs_Impl():
m_pOStream(0),
m_Level(0),
m_spDoc(0),
m_spCurrentUnit(0)
{
   // make sure com is up and ready
   ::CoInitialize(NULL);
}

sysStructuredSaveXmlPrs_Impl::~sysStructuredSaveXmlPrs_Impl()
{
   ::CoUninitialize();
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void sysStructuredSaveXmlPrs_Impl::BeginSave(IStream* pis)
{
   PRECONDITION( pis != NULL );
   CHECK(!(bool)m_spDoc);
   CHECK(m_pOStream==NULL); // previously used and not cleaned up?

   if ((bool)m_spCurrentUnit)
      m_spCurrentUnit.Release();

   HRESULT hr = 0;

   try
   {
      m_pOStream = pis;
      m_pOStream->AddRef();

      // create our document
      MSXML::IXMLDOMDocumentPtr pDoc(__uuidof(MSXML::DOMDocument));
      if (!(bool)pDoc)
      {
         THROW(sysXStructuredSave,CantInitializeTheParser);
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
      THROW(sysXStructuredSave,CantInitializeTheParser);
   }
   catch(...)
   {
      THROW(sysXStructuredSave,CantInitializeTheParser);
   }
}

void sysStructuredSaveXmlPrs_Impl::EndSave()
{
   CHECKX(m_Level==0,_T("Error: BeginUnit-EndUnit mismatch in structured save"));
   try
   {
      // Save document and make sure it saves correctly
      m_spDoc->save(m_pOStream);
      if (m_pOStream==NULL)
      {
         THROW(sysXStructuredSave,BadWrite);
      }

      // free up com resources
      m_pOStream->Release();
      m_pOStream=0;

      m_spCurrentUnit.Release();
      m_spCurrentUnit = 0;

      m_spDoc.Release();
      m_spDoc=0;
   }
#if defined __WARN
   catch(_com_error& e) 
#else
   catch(_com_error& /*e*/) 
#endif // __WARN
   {
      WARN(0,(LPTSTR)(e.Description()));
      THROW(sysXStructuredSave,BadWrite);
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXmlPrs_Impl::BeginUnit(LPCTSTR name, Float64 version)
{
   ASSERTVALID;
   
   try
   {
     MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name, version);
     if (!(bool)pchild)
         THROW(sysXStructuredSave,BadWrite);

     // walk down to next level
     m_spCurrentUnit = pchild;
     m_Level++;
     m_UnitList.push_back(ListItem(name,version));
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXmlPrs_Impl::EndUnit()
{
   ASSERTVALID;
   
   try
   {
      // pop back up the tree
      m_spCurrentUnit = m_spCurrentUnit->parentNode;
      if (!(bool)m_spCurrentUnit)
      {
         CHECKX(0,_T("Popped too far - no parent for child node"));
         THROW(sysXStructuredSave,BadWrite);
      }

      m_UnitList.pop_back();
      m_Level--;

   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }

   ASSERTVALID;
}

Float64 sysStructuredSaveXmlPrs_Impl::GetVersion()
{
   ASSERTVALID;
   return m_UnitList.back().second;
}

Float64 sysStructuredSaveXmlPrs_Impl::GetParentVersion()
{
   ASSERTVALID;
   UnitListConstIterator iter = m_UnitList.end();
   iter--;
   iter--;
   return (*iter).second;
}

std::_tstring sysStructuredSaveXmlPrs_Impl::GetParentUnit()
{
   ASSERTVALID;
   UnitListConstIterator iter = m_UnitList.end();
   iter--;
   iter--;
   return (*iter).first;
}

Float64 sysStructuredSaveXmlPrs_Impl::GetTopVersion()
{
   ASSERTVALID;
   return m_UnitList.front().second;
}

void sysStructuredSaveXmlPrs_Impl::Property(LPCTSTR name, LPCTSTR value)
{
   ASSERTVALID;

   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(sysXStructuredSave,BadWrite);

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
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXmlPrs_Impl::Property(LPCTSTR name, Float64 value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(sysXStructuredSave,BadWrite);

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
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXmlPrs_Impl::Property(LPCTSTR name, Int16 value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(sysXStructuredSave,BadWrite);

      // made node, now do data conversion
      _variant_t val(value);
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXmlPrs_Impl::Property(LPCTSTR name, Uint16 value)
{
   Property(name, (Uint32)value);
}

void sysStructuredSaveXmlPrs_Impl::Property(LPCTSTR name, Int32 value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(sysXStructuredSave,BadWrite);

      // made node, now do data conversion
      _variant_t val(value);
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXmlPrs_Impl::Property(LPCTSTR name, Uint32 value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(sysXStructuredSave,BadWrite);

      // made node, now do data conversion
      std::_tostringstream os;
      os<<value;
      _variant_t val(os.str().c_str());
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXmlPrs_Impl::Property(LPCTSTR name, bool value)
{
   ASSERTVALID;
   try
   {
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name);
      if (!(bool)pchild)
        THROW(sysXStructuredSave,BadWrite);

      // made node, now do data conversion
      _variant_t val(value);
      pchild->text = (_bstr_t)val;
   }
   catch(...)
   {
      THROW(sysXStructuredSave,BadWrite);
   }
}

void sysStructuredSaveXmlPrs_Impl::PutUnit(LPCTSTR xml)
{
   MSXML::IXMLDOMDocumentPtr pDoc(__uuidof(MSXML::DOMDocument));
   pDoc->loadXML(_bstr_t(xml));

   MSXML::IXMLDOMNodePtr pNewNode = pDoc->firstChild;
   m_spCurrentUnit->appendChild(pNewNode);
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
bool sysStructuredSaveXmlPrs_Impl::AssertValid() const
{
   // cannot have negative levels
   if (m_Level<0) 
      return false;

   if (m_pOStream==0) // must have happy stream
      return false;

   return true;
}

void sysStructuredSaveXmlPrs_Impl::Dump(dbgDumpContext& os) const
{
   os << "Dump for sysStructuredSaveXmlPrs_Impl" << endl;
   os << "  Level: " << m_Level << endl;
   os << "  Units: <name, version> " << endl;
   for (UnitListConstIterator it=m_UnitList.begin(); it!=m_UnitList.end(); it++)
      os <<"    <"<<(*it).first<<", "<<(*it).second<<">"<<endl;

}
#endif // _DEBUG

#if defined _UNITTEST
bool sysStructuredSaveXmlPrs_Impl::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("sysStructuredSaveXmlPrs_Impl");

   // Tests in main unit testing routine

   TESTME_EPILOG("StructuredSaveXmlPrs");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////////////////
// Helper function: Make a named child node
////////////////////////////////////////////////////////////////////////////
MSXML::IXMLDOMNodePtr sysStructuredSaveXmlPrs_Impl::MakeChildNode(LPCTSTR name, Float64 vers)
{
   ASSERTVALID;

   MSXML::IXMLDOMNodePtr pchild;
   try
   {
     _variant_t type((long)MSXML::NODE_ELEMENT);
     MSXML::IXMLDOMNodePtr pnewunit = m_spDoc->createNode(type, name, "");
     if (!(bool)pnewunit)
         THROW(sysXStructuredSave,BadWrite);

     pchild = m_spCurrentUnit->appendChild(pnewunit);
     if (!(bool)pchild)
         THROW(sysXStructuredSave,BadWrite);

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
      THROW(sysXStructuredSave,BadWrite);
   }
   catch(...)
   {
      WARN(0,"Caught unknown exception");
      THROW(sysXStructuredSave,BadWrite);
   }

   return pchild;
}