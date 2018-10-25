///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2014  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// StructuredSave2.cpp : Implementation of CStructuredSave2
#include "stdafx.h"
#include "WBFLTools.h"
#include "ToolsUtils.h"
#include <ComException.h>
#include <sstream>

#include <System\filestream.h>
#include "StructuredSave2.h"
#include "StrStorage2.hh"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStructuredSave2

STDMETHODIMP CStructuredSave2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStructuredSave2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CStructuredSave2::CStructuredSave2():
m_spDoc(0),
m_spObjectTable(0),
m_NextName(100),
m_bOpen(false),
m_WroteTopUnit(false)
{
}

HRESULT CStructuredSave2::Open(/*[in]*/ BSTR strFileName)
{
   try
   {
      // file should not be already open
      if (m_bOpen)
         THROW_IDS(IDS_STRSAVE_E_CANTOPEN,STRSAVE_E_CANTOPEN,IDH_STRSAVE_E_CANTOPEN);

      FileStream* pstrm = new(FileStream);
      if (pstrm==0)
         THROW_IDS(IDS_STRSAVE_E_CANTOPEN,STRSAVE_E_CANTOPEN,IDH_STRSAVE_E_CANTOPEN);

      m_pIStream.Attach(pstrm);
      if ( !pstrm->open( strFileName, false ) )
         THROW_IDS(IDS_STRSAVE_E_CANTOPEN,STRSAVE_E_CANTOPEN,IDH_STRSAVE_E_CANTOPEN);

      m_bOpen = true;

      this->BeginSave( m_pIStream);
   }
   catch( ... )
   {
      return HandleException();
   }

	return S_OK;
}

void CStructuredSave2::BeginSave(IStream* pis)
{
   ATLASSERT( pis != NULL );
   ATLASSERT(!(bool)m_spDoc);
   ATLASSERT(m_bOpen);
   ATLASSERT(!m_WroteTopUnit);
   ATLASSERT( m_NodeStack.size()==0); // previously used and not cleaned up?

   if ((bool)m_spObjectTable)
      m_spObjectTable.Release();

   m_ObjectSet.clear();

   // create our document
   MSXML::IXMLDOMDocumentPtr pDoc(__uuidof(MSXML::DOMDocument60));
   if (!(bool)pDoc)
   {
      THROW_IDS(IDS_STRSAVE_E_INITIALIZING_THE_PARSER,STRSAVE_E_INITIALIZING_THE_PARSER,IDH_STRSAVE_E_INITIALIZING_THE_PARSER);
   }

   // add a processing instruction for xml
   _bstr_t targ("xml");
   _bstr_t data("version=\"1.0\""); 
   MSXML::IXMLDOMProcessingInstructionPtr pi = pDoc->createProcessingInstruction (targ, data);
   pDoc->appendChild(pi);

   m_spDoc = pDoc;

   // push our top-level collection onto the stack
   ListItem tmp;
   tmp.Name = "Document";
   tmp.Version = 0.0;
   tmp.spCurrentNode =  pDoc;
   m_NodeStack.push_back(tmp);
}

HRESULT CStructuredSave2::Close()
{
   try
   {
      this->EndSave();

      m_pIStream.Release();
      m_bOpen = false;
   }
   catch( ... )
   {
      return HandleException();
   }

   return S_OK;
}

void CStructuredSave2::EndSave()
{
   AssertValid();

   if(m_NodeStack.size()!=1) // Error: BeginUnit-EndUnit mismatch - this is ok with
                             // the xml parser, but indicates a problem in client code
   {
      ATLASSERT(false);
      // THROW_IDS(IDS_E_BEGIN_END_UNIT_MISMATCH,TOOLS_E_BEGIN_END_UNIT_MISMATCH,IDH_E_BEGIN_END_UNIT_MISMATCH);
   }

   // need to append object table to document if there were any objects written
   if (m_ObjectSet.size()>0)
   {
      ATLASSERT((bool)m_spObjectTable);

      MSXML::IXMLDOMNodePtr& ptop = m_spDoc->lastChild;
      if (!(bool)ptop)
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);

      MSXML::IXMLDOMNodePtr& pchild = ptop->appendChild(m_spObjectTable);
      if (!(bool)pchild)
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);

      m_spObjectTable.Release();
      m_spObjectTable = 0;
   }

   // Save document to stream
   m_spDoc->save((IStream*)m_pIStream);
   if (m_pIStream==NULL)
   {
      ATLASSERT(false);
      THROW_IDS(IDS_STRSAVE_E_CANTOPEN,STRSAVE_E_CANTOPEN,IDH_STRSAVE_E_CANTOPEN);
   }

   // empty node list
   m_NodeStack.clear();

   m_spDoc.Release();
   m_spDoc=0;

   m_ObjectSet.clear();
}

HRESULT CStructuredSave2::BeginUnit( BSTR name, Float64 version)
{
   
   try
   {
      AssertValid();

      if (m_NodeStack.size()==1)
      {
         // This is the top level node. We can only BeginUnit here once.
         // be 
         if (m_WroteTopUnit)
         {
            THROW_IDS(IDS_STRSAVE_E_ONLY_ONE_UNIT,STRSAVE_E_ONLY_ONE_UNIT,IDH_STRSAVE_E_ONLY_ONE_UNIT);
         }
         else
            m_WroteTopUnit = true;
      }

      // create a new child node
      MSXML::IXMLDOMNodePtr pchild = MakeChildNode(name, version);
      if (!(bool)pchild)
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

      // append it to the current node
      MSXML::IXMLDOMNodePtr& rback = m_NodeStack.back().spCurrentNode;
      pchild = rback->appendChild(pchild);
      if (!(bool)pchild)
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

      // walk down to next level by pushing node onto stack
      ListItem tmp;
      tmp.Name = name;
      tmp.Version = version;
      tmp.spCurrentNode =  pchild;
      m_NodeStack.push_back(tmp);

   }
   catch( ... )
   {
      return HandleException();
   }

   return S_OK;
}

HRESULT CStructuredSave2::EndUnit()
{
   AssertValid();
   
   try
   {
      // should never pop back to top level document
      if (m_NodeStack.size()<1)
      {
         ATLASSERT(false);// Popped too far - no parent for child node
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

      // pop back up the tree
      m_NodeStack.pop_back();

      AssertValid();
   }
   catch( ... )
   {
      return HandleException();
   }

   return S_OK;
}

HRESULT CStructuredSave2::get_Version(Float64* pver)
{
   try
   {
      AssertValid();

      *pver = m_NodeStack.back().Version;
   }
   catch( ... )
   {
      return HandleException();
   }

   return S_OK;
}

HRESULT CStructuredSave2::get_TopVersion(Float64* pver)
{
   try
   {
      AssertValid();
      // top version is in second member of list
      ATLASSERT(m_NodeStack.size()>1);
      // dummy document node is first in stack - top node is second
      NodeStackConstIterator it = m_NodeStack.begin();
      it ++;
      *pver = it->Version;
   }
   catch( ... )
   {
      return HandleException();
   }

   return S_OK;
}


HRESULT CStructuredSave2::put_Property(/*[in]*/ BSTR strPropName, /*[in]*/ VARIANT newVal)
{
   try
   {
      AssertValid();

      MSXML::IXMLDOMNodePtr pchild = 0;
      // create node for all property types
      pchild = MakePropertyNode(strPropName, &newVal);
      if (!(bool)pchild)
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);

      switch ( newVal.vt)
      {
      case VT_BSTR:
         {
            // first need to take out special characters &,',",<,>
            _bstr_t value(newVal);
            std::_tstring tmp(value);
            find_replace_all(&tmp, _T("&") , _T("&amp;"));
            find_replace_all(&tmp, _T("<") , _T("&lt;" ));
            find_replace_all(&tmp, _T(">") , _T("&gt;" ));
            find_replace_all(&tmp, _T("'") , _T("&sq;" ));
            find_replace_all(&tmp, _T("\""), _T("&dq;" ));

            _bstr_t val(tmp.c_str());
            pchild->text = (_bstr_t)val;
         }
         break;

      // simple data types
      case VT_R4:
      case VT_R8:
      case VT_I2:
      case VT_I4:
      case VT_I8:
      case VT_INT:
      case VT_BOOL:
         {
            _variant_t val(newVal);
            pchild->text = (_bstr_t)val;
         }
         break;

      // unsigned objects require our attention to convert
      case VT_UI2:
      case VT_UINT:
         {
            unsigned int ul = newVal.uintVal;
            std::_tostringstream os;
            os<<ul;
            std::_tstring msg(os.str());
            _bstr_t bval(msg.c_str());
            pchild->text = bval;
         }
         break;

      case VT_UI4:
         {
            unsigned long ul = newVal.ulVal;
            std::_tostringstream os;
            os<<ul;
            _bstr_t bval(os.str().c_str());
            pchild->text = bval;
         }
         break;

      case VT_UI8:
         {
            unsigned long long ull = newVal.ullVal;
            std::_tostringstream os;
            os<<ull;
            _bstr_t bval(os.str().c_str());
            pchild->text = bval;
         }
         break;

      // com objects require their own routine
      case VT_UNKNOWN:
      case VT_DISPATCH:
            Property(strPropName, newVal.punkVal, pchild);
         break;

      default:
         // all other kinds not supported
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_INVALID_VARIANT_TYPE, STRSAVE_E_INVALID_VARIANT_TYPE, IDH_STRSAVE_E_INVALID_VARIANT_TYPE );
         break;
      }
   }
   catch( ... )
   {
      return HandleException();
   }

   return S_OK;
}

void CStructuredSave2::Property(BSTR name, IUnknown *pUnk, MSXML::IXMLDOMNodePtr& pChild)
{
   AssertValid();
   HRESULT hr;

   if (pUnk==NULL)
   {
      ATLASSERT(false);
      THROW_MSG("NULL Pointer: CStructuredSave2::Property",E_POINTER, NULL);
   }

   // check to see if we have written any objects yet. If not, create an object table
   if (!(bool)m_spObjectTable)
   {
      ATLASSERT(m_ObjectSet.size()==0); // better not have any objects stored yet

      // create and store object table in a separate element until the end of the save
      MSXML::IXMLDOMNodePtr pot = MakeChildNode(OLESTR("ObjectTable"), 1.0);
      if (!(bool)pot)
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

      m_spObjectTable = pot;
   }

   // check to see if this object has already been saved. 
   _bstr_t object_name;
   ObjectSetConstIterator it = m_ObjectSet.find(pUnk);
   if (it != m_ObjectSet.end())
   {
      // Found object. it has already been saved.
      // Get it's name so we can write out the reference
      object_name = it->second;
   }
   else
   {
      // Object hasn't been written to object table yet. 
      // Let's see if it supports the right interfaces
      CComPtr<IPersist> pip;
      hr = pUnk->QueryInterface(IID_IPersist, (void**)&pip);
      if (FAILED(hr) || pip==NULL)
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_IPERSIST,STRSAVE_E_IPERSIST,IDH_STRSAVE_E_IPERSIST);
      }

      CComPtr<IStructuredStorage2> pss;
      hr = pUnk->QueryInterface(IID_IStructuredStorage2, (void**)&pss);
      if (FAILED(hr) || pss==NULL)
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_CLASS_ISTRUCTUREDSTORAGE2,STRSAVE_E_CLASS_ISTRUCTUREDSTORAGE2,IDH_STRSAVE_E_CLASS_ISTRUCTUREDSTORAGE2);
      }

      // We're going to be writing this into the object table, 
      // so let's put the table on the stack
      ListItem tmp;
      tmp.Name = "ObjectTable";
      tmp.Version = 1.0;
      tmp.spCurrentNode = m_spObjectTable;
      m_NodeStack.push_back(tmp);

      // create the unique name for our object
      std::_tostringstream os;
      os<<"Object_"<<m_NextName++;
      object_name = _bstr_t(os.str().c_str());

      // create a node with our unique name
      hr = this->BeginUnit(object_name, 0.0);
      if (FAILED(hr))
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

      // write a property with the clsid
      CLSID clsid;
      hr = pip->GetClassID(&clsid);
      if (FAILED(hr))
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_IPERSIST,STRSAVE_E_IPERSIST,IDH_STRSAVE_E_IPERSIST);
      }

      LPOLESTR postr = 0;
      hr = StringFromCLSID(clsid, &postr);
      if (FAILED(hr))
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

      hr = this->put_Property(OLESTR("CLSID"), _variant_t(postr));
      if (FAILED(hr))
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

      CoTaskMemFree(postr);

      // ask our com object to write itself
      hr = pss->Save(this);
      if (FAILED(hr))
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

      // We saved it - let's make a record so it only gets saved once.
      m_ObjectSet.insert(ObjectSet::value_type(pUnk, object_name) ); 

      hr = this->EndUnit();
      if (FAILED(hr))
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

      // pop object table node - check first to make sure we are popping the right node
#if defined _DEBUG
      ListItem rtmp = m_NodeStack.back();
      ATLASSERT(rtmp.Name == _bstr_t("ObjectTable"));
#endif

      m_NodeStack.pop_back();
   }

   // We've dealt with writing our object to the object table, now 
   // let's write the reference.
   pChild->text = object_name;
   MSXML::IXMLDOMNodePtr& rback = m_NodeStack.back().spCurrentNode;
   MSXML::IXMLDOMNodePtr& pc = rback->appendChild(pChild);
   if (!(bool)pc)
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
}

void CStructuredSave2::AssertValid() const
{
#if defined _DEBUG

   // file needs to be open
   if (!m_bOpen)
   {
      ATLASSERT(false);
      THROW_IDS(IDS_STRSAVE_E_FILE_NOT_OPEN,STRSAVE_E_FILE_NOT_OPEN,IDH_STRSAVE_E_FILE_NOT_OPEN);
   }

   // cannot have negative levels
   if (m_NodeStack.size()<1) 
   {
      ATLASSERT(false); 
   }

   if (m_pIStream==0) // must have happy stream
   {
      ATLASSERT(false);
      THROW_IDS(IDS_STRSAVE_E_FILE_NOT_OPEN,STRSAVE_E_FILE_NOT_OPEN,IDH_STRSAVE_E_FILE_NOT_OPEN);
   }
#endif // _DEBUG
}


////////////////////////////////////////////////////////////////////////////
// Helper function: Make a named child node
////////////////////////////////////////////////////////////////////////////
MSXML::IXMLDOMNodePtr CStructuredSave2::MakeChildNode(BSTR name, Float64 vers)
{
   AssertValid();

   MSXML::IXMLDOMNodePtr pchild;
   try
   {
      _variant_t type((long)MSXML::NODE_ELEMENT);
      pchild = m_spDoc->createNode(type, name, "");
      if (!(bool)pchild)
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

      if (vers!=0.0)
      {
        // we have a version - com-style cast to an element and set the version
        MSXML::IXMLDOMElementPtr pel;
        HRESULT hr = pchild->QueryInterface(__uuidof(MSXML::IXMLDOMElement), (void**)&pel);
        if (SUCCEEDED(hr) && pel!=0)
        {
           _variant_t var(vers);
           pel->setAttribute("version",var);
        }
        else
        {
           ATLASSERT(false); // eating our own dog food here. this should be impossible.
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
        }
      }
   }
   catch(_com_error& e) 
   {
      ATLASSERT(false); // parser threw
      _bstr_t msg(e.Description());
      THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
   }
   catch(...)
   {
      throw; // don't know what it is, but somebody needs to deal with it.
   }

   return pchild;
}

MSXML::IXMLDOMNodePtr CStructuredSave2::MakePropertyNode(BSTR name, VARIANT* pVar)
{
   // we can't write properties to the top node since xml documents can only have 
   // one element at their top level. (we could have gotten around this by creating
   // a default top-level node for all structuredstorage documents, but backwards-
   // compatibility with PGSuper keeps us from doing this

   // huck if we are trying to write a property at the bottom level
   if (m_NodeStack.size()<=1)
   {
      THROW_IDS(IDS_STRSAVE_E_MUST_HAVE_ONE_UNIT, STRSAVE_E_MUST_HAVE_ONE_UNIT, IDH_STRSAVE_E_MUST_HAVE_ONE_UNIT);
   }

   // test our variant and see if we can handle one of these then assign the type
   // to our string
   _bstr_t vtName;
   GetTypeNameFromVariant(*pVar, &vtName);

   // huck if variant type is not known
   if (vtName== _bstr_t("VT_EMPTY"))
   {
      ATLASSERT(false);
      THROW_IDS(IDS_STRSAVE_E_INVALID_VARIANT_TYPE, STRSAVE_E_INVALID_VARIANT_TYPE, IDH_STRSAVE_E_INVALID_VARIANT_TYPE);
   }

   // create a node and add it to the document
   MSXML::IXMLDOMNodePtr pchild;
   try
   {
      _variant_t type((long)MSXML::NODE_ELEMENT);
      pchild = m_spDoc->createNode(type, name, "");
      if (!(bool)pchild)
      {
         ATLASSERT(false);
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
      }

     // set our Type attribute
     MSXML::IXMLDOMElementPtr pel;
     HRESULT hr = pchild->QueryInterface(__uuidof(MSXML::IXMLDOMElement), (void**)&pel);
     if (SUCCEEDED(hr) && pel!=0)
     {
        _variant_t var(vtName);
        pel->setAttribute("VarType",var);
     }
     else
     {
        ATLASSERT(false); // should never happen
     }
   }
   catch(_com_error& e) 
   {
      ATLASSERT(false); // parser threw
      _bstr_t msg(e.Description());
      THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
   }
   catch(...)
   {
      throw; // don't know what it is, but somebody needs to deal with it.
   }


   try
   {
      // Now we have our new element: append it to the current node
      MSXML::IXMLDOMNodePtr& rback = m_NodeStack.back().spCurrentNode;
      pchild = rback->appendChild(pchild);
      if (!(bool)pchild)
         THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
   }
   catch(_com_error &e) 
   {
      ATLASSERT(false);
      _bstr_t msg(e.Description());
      THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
   }
   catch(...)
   {
      ATLASSERT(false);
      THROW_IDS(IDS_STRSAVE_E_BADWRITE,STRSAVE_E_BADWRITE,IDH_STRSAVE_E_BADWRITE);
   }

   return pchild;
}

HRESULT CStructuredSave2::HandleException()
{
   try
   {
      // something got thrown. that's why were here - to try and dissect it.
      // put initialization code here if it's needed to get us back into 
      // a stable state

      throw; // throw whatever got thrown last to be caught immediately!
   }
   catch (CComException& re)
   {
      ATLASSERT(false);
      // somebody puked from way down deep. Build error message and return hresult
      _bstr_t msg(re.GetErrorMessage());
      HRESULT hr = re.GetHresult();
      DWORD helpid = re.GetHelpID();
      return CComCoClass<CStructuredSave2,&CLSID_StructuredSave2>::Error(msg, helpid, GetHelpFile(), IID_IStructuredSave2, hr);
   }
   catch(_com_error &e) 
   {
      // parser puked
      ATLASSERT(false);
      _bstr_t msg(e.Description());
      HRESULT hr = STRSAVE_E_BADWRITE;
      DWORD helpid = IDH_STRSAVE_E_BADWRITE;
      return CComCoClass<CStructuredSave2,&CLSID_StructuredSave2>::Error(msg, helpid, GetHelpFile(), IID_IStructuredSave2, hr);
   }
   catch (...)
   {
      // could make up a custom message here, but we don't know what happened so why try?
      // the main point is not to let the exception out into the com world
      ATLASSERT(false);
      return E_FAIL;
   }
}


