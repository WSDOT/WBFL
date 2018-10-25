///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2017  Washington State Department of Transportation
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

// StructuredLoad2.cpp : Implementation of CStructuredLoad2

#include "stdafx.h"
#include "WBFLTools.h"
#include "StructuredLoad2.h"


#include <System\FileStream.h>
#include "ToolsUtils.h"
#include <ComException.h>
#include <sstream>
#include "StrStorage2.hh"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CheckLoad(MSXML::IXMLDOMDocument* pDoc);
_bstr_t GetParseError(MSXML::IXMLDOMParseErrorPtr pXMLError);
HRESULT HandleException();
HRESULT HandlePropertyException(_com_error& e);

/////////////////////////////////////////////////////////////////////////////
// CStructuredLoad2

STDMETHODIMP CStructuredLoad2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStructuredLoad2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CStructuredLoad2::Open( BSTR strFile)
{
   try
   {
      // Check if the file exists.  If we can't get its attributes, then
      // it probably isn't there.
      _bstr_t bstrFile(strFile);
      DWORD dwResult = GetFileAttributes(bstrFile);
      if ( dwResult == 0xFFFFFFFF )
      {
         CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_FILENOTFOUND, strFile);
         THROW_MSG(msg,STRLOAD_E_FILENOTFOUND,IDH_STRLOAD_E_FILENOTFOUND);
      }

      FileStream* pstrm = new FileStream;
      if (pstrm==0)
      {
         CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_CANTOPEN, strFile);
         THROW_MSG(msg,STRLOAD_E_CANTOPEN,IDH_STRLOAD_E_CANTOPEN);
      }

      m_pIStream.Attach(pstrm);
      if ( !pstrm->open( strFile ) )
      {
         CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_CANTOPEN, strFile);
         THROW_MSG(msg,STRLOAD_E_CANTOPEN,IDH_STRLOAD_E_CANTOPEN);
      }

      m_bOpen = TRUE;

      this->BeginLoad( m_pIStream );

   }
   catch(...)
   {
      return HandleException();
   }

	return S_OK;
}

void CStructuredLoad2::BeginLoad(IStream* pis)
{
   ATLASSERT( pis != NULL );
   ATLASSERT(!(bool)m_spDoc);   //  previously used and not cleaned up?
   ATLASSERT(!(bool)m_spObjectTable);
   ATLASSERT(m_pIStream!=NULL); // "                                   "

   if (!m_NodeStack.empty())
      m_NodeStack.clear();

   try
   {
      // create our document
      MSXML::IXMLDOMDocumentPtr pDoc(__uuidof(MSXML::DOMDocument60));
      if (!(bool)pDoc)
      {
         CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_CANTOPEN, OLESTR("XML Parser"));
         THROW_MSG(msg,STRLOAD_E_CANTOPEN,IDH_STRLOAD_E_CANTOPEN);
      }

      m_spDoc = pDoc;

      // Load document and make sure it loads correctly
      m_spDoc->load( (IStream*)m_pIStream );
      if (m_pIStream==NULL)
      {
         THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
      }

      // check document's error state
      CheckLoad(m_spDoc);

      // make sure document is not empty
      if (m_spDoc->hasChildNodes())
      {
         // first node must be 'xml' node
         MSXML::IXMLDOMNodePtr xmlnode = m_spDoc->firstChild;
         _bstr_t nodenm = xmlnode->nodeName;
         if (nodenm!=_bstr_t("xml") && nodenm!=_bstr_t("XML"))
            THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);

         // push our top-level collection onto the stack
         ListItem tmp;
         tmp.Name = "Document";
         tmp.Version = 0.0;
         tmp.spCurrentChild = pDoc->GetdocumentElement();
         tmp.spCurrentUnit =  pDoc;
         m_NodeStack.push_back(tmp);

         // look for ObjectTable node
         try
         {
            m_spObjectTable = pDoc->GetdocumentElement()->selectSingleNode(OLESTR("ObjectTable"));
         }
         catch(...)
         {
            // it's ok, we just have no object table
            m_spObjectTable = NULL;
         }
      }
      else
      {
         THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
      }
   }
   catch(_com_error& e) 
   {
      // parser errors
      CComBSTR msg((LPTSTR )e.Description());
      THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
   }
}


HRESULT CStructuredLoad2::BeginUnit( BSTR name)
{
   try
   {
      try
      {
         // get next element with name
         MSXML::IXMLDOMNodePtr ptest = GetCurrentNode(name);
         if (ptest != NULL)
         {
            // get the version of the unit
            Float64 vers=0.0;
            _bstr_t bsvers;
            try
            {
               // this will throw if no version attribute - not a big deal.
               bsvers = ptest->attributes->getNamedItem("version")->text;
               _variant_t vvers(bsvers);
               vvers.ChangeType(VT_R8);
               vers = (Float64)vvers;
            }
            catch (...)
            {;} // again, no big deal.

            // push new unit onto the stack
            ListItem tmp;
            tmp.Name = name;
            tmp.Version = vers;
            if (ptest->hasChildNodes())
               tmp.spCurrentChild = ptest->firstChild;
            else
               tmp.spCurrentChild = 0;

            tmp.spCurrentUnit = ptest;

            m_NodeStack.push_back(tmp);
         }
         else
         {
            THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
         }
      }
      catch(_com_error &e) 
      {
         CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, e.Description());
         THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
      }
      catch(...)
      {
         THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
      }
   }
   catch(...)
   {
      return HandleException();
   }

   return S_OK;
}

HRESULT CStructuredLoad2::EndUnit(VARIANT_BOOL* bEnd)
{
   try
   {
      // can't go negative here.
      if (m_NodeStack.size()<=1)
         THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);

      // check to see we are really at the last property - child should be null or at the ObjectTable node
      MSXML::IXMLDOMNodePtr& rback = m_NodeStack.back().spCurrentChild;
      if (bEnd != NULL)
      {
         if (rback != NULL && rback != m_spObjectTable)
            *bEnd = VARIANT_FALSE;
         else
            *bEnd = VARIANT_TRUE;
      }

      // climb back up the tree
      m_NodeStack.pop_back();

      ReadNext(); // go on to next node
   }
   catch(...) 
   {
      return HandleException();
   }

	return S_OK;
}

HRESULT CStructuredLoad2::get_Version( Float64 *pVal)
{
   *pVal = 0.0;

   try
   {
      if (m_NodeStack.empty())
         return E_FAIL;

      *pVal = m_NodeStack.back().Version;
   }
   catch(...) 
   {
      return HandleException();
   }

	return S_OK;
}

HRESULT CStructuredLoad2::get_TopVersion( Float64 *pVal)
{
   *pVal = 0.0;

   try
   {
      if (m_NodeStack.empty())
         return E_FAIL;

      // dummy document node is first in stack - top node is second
      NodeStackConstIterator it = m_NodeStack.begin();
      it ++;
      *pVal = it->Version;

	  return S_OK;
   }
   catch(...) 
   {
      return HandleException();
   }

	return S_OK;
}

HRESULT CStructuredLoad2::get_Property( BSTR name,  VARIANT *pVal)
{
   HRESULT hr = E_FAIL;

   try
   {
      // get the "variant" version. we may have to do some doctoring to the variant 
      // before we can return it though.
      _variant_t vval;
      _bstr_t bsvt;
      if (GetProperty(name, &vval, bsvt )) 
      {
         // check property coming back from file. If it's VT_EMPTY, the type was 
         // not set in the xml file. 
         if (_bstr_t("VT_EMPTY") == bsvt)
         {
            // This probably means that the file is of an old format
            // and we are expecting the type to come from the client 
            // via the pVal parameter.  Let's check it:
            GetTypeNameFromVariant(*pVal, &bsvt);
            // No need to check for errors here since if-else block below will
            // do the work for us.
         }

         if (_bstr_t("VT_BSTR") == bsvt )
         {
            // must reconstitute string first
            std::_tstring tmp((LPTSTR )(_bstr_t)vval);
            find_replace_all(&tmp, _T("&amp;"),_T("&"));
            find_replace_all(&tmp, _T("&lt;"),_T("<"));
            find_replace_all(&tmp, _T("&gt;"),_T(">"));
            find_replace_all(&tmp, _T("&sq;"),_T("'"));
            find_replace_all(&tmp, _T("&dq;"),_T("\""));

            pVal->bstrVal = CString( tmp.c_str() ).AllocSysString();
            pVal->vt = VT_BSTR;
         }
         else if (_bstr_t("VT_R4") == bsvt)
         {
            pVal->fltVal = (float)vval;
            pVal->vt = VT_R4;
         }
         else if (_bstr_t("VT_R8") == bsvt)
         {
            pVal->dblVal = (Float64)vval;
            pVal->vt = VT_R8;
         }
         else if (_bstr_t("VT_I2") == bsvt)
         {
            pVal->iVal = (short)vval;
            pVal->vt = VT_I2;
         }
         else if (_bstr_t("VT_I4") == bsvt)
         {
            pVal->lVal = (long)vval;
            pVal->vt = VT_I4;
         }
         else if (_bstr_t("VT_I8") == bsvt)
         {
            pVal->llVal = (LONGLONG)vval;
            pVal->vt = VT_I8;
         }
         else if (_bstr_t("VT_INT") == bsvt)
         {
            pVal->intVal = (int)vval;
            pVal->vt = VT_INT;
         }
         else if (_bstr_t("VT_UINT") == bsvt)
         {
            pVal->uintVal = (unsigned int)vval;
            pVal->vt = VT_UINT;
         }
         else if (_bstr_t("VT_UI2") == bsvt)
         {
            pVal->uiVal = (USHORT)vval;
            pVal->vt = VT_UI2;
         }
         else if (_bstr_t("VT_UI4") == bsvt)
         {
            // variant_t's don't deal with unsigned longs well
            unsigned long ul;
            try
            {
               long lul = (long)vval;
               if (lul<0)
                  throw;
               else
                  ul = lul;
            }
            catch(...) 
            {
               // variant couldn't parse, so try brute force
               _bstr_t bval(vval);
               TCHAR* sv = (TCHAR*)bval; 
               //TCHAR** ev = &sv + bval.length();
               unsigned long uval = _tcstoul(sv,NULL,10);
               if (uval==0 && *sv != _T('0') )
                  THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);

               ul = uval;
            } 
            pVal->ulVal = ul;
            pVal->vt = VT_UI4;
         }
         else if (_bstr_t("VT_UI8") == bsvt)
         {
            // variant_t's don't deal with unsigned longs well
            unsigned long long ull;
            try
            {
               long long lul = (long long)vval;
               if (lul<0)
                  throw;
               else
                  ull = lul;
            }
            catch(...) 
            {
               // variant couldn't parse, so try brute force
               _bstr_t bval(vval);
               TCHAR* sv = (TCHAR*)bval; 
               //TCHAR** ev = &sv + bval.length();
               unsigned long long uval = _tcstoui64(sv,NULL,10);
               if (uval==0 && *sv != _T('0') )
                  THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);

               ull = uval;
            } 
            pVal->ullVal = ull;
            pVal->vt = VT_UI8;
         }
         else if (_bstr_t("VT_BOOL") == bsvt)
         {
            pVal->boolVal = (bool)vval?VARIANT_TRUE:VARIANT_FALSE;
            pVal->vt = VT_BOOL;
         }
         else if (_bstr_t("VT_UNKNOWN") == bsvt  || _bstr_t("VT_DISPATCH") == bsvt)
         {
            // expecting an object reference - get object id and crawl down to load it
            _bstr_t bsobjref;
            try
            {
               const MSXML::IXMLDOMNodePtr& rback = m_NodeStack.back().spCurrentChild;
               bsobjref = rback->text;
            }
            catch (...)
            {
               // node did not have an ObjRef attribute - can only puke
               CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, OLESTR("Expected Object Reference"));
               THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
            }

            // get the object out of the running object table or create it
            CComPtr<IUnknown> piu;
            try
            {
               piu = this->GetObjectRef( bsobjref );
               ATLASSERT(piu!=NULL);
            }
            catch (...)
            {
               // node did not have an ObjRef attribute - can only puke
               CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, OLESTR("Could not find object reference"));
               THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
            }

            // have object, now convert to desired form
            if (_bstr_t("VT_UNKNOWN") == bsvt)
            {
               pVal->punkVal = piu;
               pVal->vt = VT_UNKNOWN;
            }
            else
            {
               // convert to idispatch
               IDispatch* pid = NULL;
               HRESULT hrl = piu->QueryInterface(IID_IDispatch,(void**)&pid);
               if (FAILED(hrl) || pid==NULL)
               {
                  CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, OLESTR("Could not cast object to IDispatch"));
                  THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
               }

               pVal->pdispVal = pid; // already addref'd for client by QI
               pVal->vt = VT_DISPATCH; 
            }
         }
         else
         {
            // all other kinds not supported
            ATLASSERT(false);
            THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
         }

         hr = S_OK;
      }
      else
      {
         // The property was not found. This is a tough call here. We could maintain the 
         // cursor at the current location, or skip to the next location. I think that
         // skipping to the next node is the most valuable option because it allows
         // clients to skip over unknown nodes (maybe written by someone else). Time
         // will tell if this was the best decision.
         THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);

      }

      // Move the parser's cursor. Read the next node even if the property was not found
      ReadNext(); 
   }
   catch( _com_error & e )
   {
      return HandlePropertyException( e );
   }
   catch(...) 
   {
      return HandleException();
   }

   return hr;
}



HRESULT CStructuredLoad2::EndOfStorage(VARIANT_BOOL* bEnd)
{
   // this function does not make any sense in the context of an xml implementation
   if (bEnd!=NULL)
      *bEnd = VARIANT_FALSE;

   return S_OK;
}

HRESULT CStructuredLoad2::Close()
{
   try 
   {
      this->EndLoad();
      m_bOpen = FALSE;
   }
   catch( ...)
   {
      return HandleException( );
   }

   return S_OK;
}

void CStructuredLoad2::EndLoad()
{
   ATLASSERT( m_pIStream!=NULL );
   ATLASSERT(m_NodeStack.size()==1); // Warning: BeginUnit-EndUnit mismatch 

   // free up com resources
   m_pIStream=NULL;

   if (!m_NodeStack.empty())
      m_NodeStack.clear();

   m_spDoc.Release();
   m_spDoc=0;
}

CComPtr<IUnknown> CStructuredLoad2::GetObjectRef( BSTR bsobjref )
{
   if (!(bool)m_spObjectTable)
   {
      ATLASSERT(false); // object table node doesn't exist in xml file
                    // cannot create objects without an object table
      CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, OLESTR("Need to create an object and no object table exists in input file."));
      THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
   }

   CComPtr<IUnknown> piu;

   // first see if object has already been created
   ObjectTableIterator it = m_RunningObjectTable.find(bsobjref);
   if (it != m_RunningObjectTable.end())
   {
      // object is already alive, just return it
      piu = it->second;
   }
   else
   {
      // object has not been created yet. We need to create it from our object table
      // first find the node in the object table
      MSXML::IXMLDOMNodePtr objnode;
      try
      {
          objnode = m_spObjectTable->selectSingleNode(bsobjref);

          if ( !(bool) objnode) 
             throw;
      }
      catch(...)
      {
         ATLASSERT(false); // object with id doesn't exist in table
         CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, OLESTR("object with id doesn't exist in object table"));
         THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
      }

      // found the node. now we need to get the clsid and create the object. first put the 
      // object node on the stack so we can call property
      ListItem tmp;
      tmp.Name = bsobjref;
      tmp.Version = 0.0;
      tmp.spCurrentUnit =  objnode;
      tmp.spCurrentChild = objnode->firstChild;
      ATLASSERT((bool)objnode->firstChild);
      m_NodeStack.push_back(tmp);

      // get the clsid
      _variant_t varclsid;
      varclsid.vt = VT_BSTR;
      if ( S_OK == this->get_Property(OLESTR("CLSID") , &varclsid))
      {
         CLSID clsid;
         HRESULT hr = ::CLSIDFromString(_bstr_t(varclsid), &clsid);
         if (FAILED(hr))
         {
            ATLASSERT(false);
            CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_CLASS_NOT_REGISTERED, (_bstr_t)varclsid);
            THROW_MSG(msg,STRLOAD_E_CLASS_NOT_REGISTERED,IDS_STRLOAD_E_CLASS_NOT_REGISTERED);
         }

         // have the clsid, now bring the object to life
         CComPtr<IUnknown> punk;
         hr = punk.CoCreateInstance( clsid );
         if (FAILED(hr))
         {
            ATLASSERT(false);
            CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_CLASS_NOT_REGISTERED, (_bstr_t)varclsid);
            THROW_MSG(msg,STRLOAD_E_CLASS_NOT_REGISTERED,IDH_STRLOAD_E_CLASS_NOT_REGISTERED);
         }

         // it's alive!
         // we're almost there. Now we need to make sure it supports the proper interfaces and 
         // tell it to load itself
         CComPtr<IStructuredStorage2> pss;
         hr = punk->QueryInterface(IID_IStructuredStorage2, (void**)&pss);
         if (FAILED(hr) || pss==NULL)
         {
            ATLASSERT(false); // object doesn't support IStructuredStorage2 - makes you wonder how it saved 
                          // itself in the first place
            THROW_IDS(IDS_STRLOAD_E_CLASS_ISTRUCTUREDSTORAGE2,STRLOAD_E_CLASS_ISTRUCTUREDSTORAGE2,IDH_STRLOAD_E_CLASS_ISTRUCTUREDSTORAGE2);
         }

         // tell object to load itself
         hr = pss->Load(this);
         if (FAILED(hr))
         {
            ATLASSERT(false);
            THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
         }

         // pop object table off of the stack so we can move onward
         m_NodeStack.pop_back();

         // add our object to the running object table
         m_RunningObjectTable.insert( ObjectTable::value_type(bsobjref, punk));

         piu = punk;
      }
      else
      {
         ATLASSERT(false); // CLSID must be next property in an object reference
         CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, OLESTR("CLSID must be next property in an object reference"));
         THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
      }
   }

   return piu;
}


HRESULT HandleException()
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
      return CComCoClass<CStructuredLoad2,&CLSID_StructuredLoad2>::Error(msg, helpid, GetHelpFile(), IID_IStructuredLoad2, hr);
   }
   catch(_com_error &e) 
   {
      // parser puked
      ATLASSERT(false);
      _bstr_t msg(e.Description());
      return CComCoClass<CStructuredLoad2,&CLSID_StructuredLoad2>::Error(msg, NULL, GetHelpFile(), IID_IStructuredLoad2, E_FAIL);
   }
   catch (...)
   {
      // could make up a custom message here, but we don't know what happened so why try?
      // the main point is not to let the exception out into the com world
      ATLASSERT(false);
      return E_FAIL;
   }
}

HRESULT HandlePropertyException(_com_error& e)
{
   // this error likely occured when a variant_t was trying to parse its value
   // and cast it.
   try
   {
      CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, e.Description());
      THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
   }
   catch(...) 
   {
      return HandleException();
   }

   return E_FAIL; // compiler pacifier - should never get here
}


bool CStructuredLoad2::GetProperty(BSTR name, _variant_t* pval, _bstr_t& bsvt)
{
   bool retval = false;
   try
   {
      // walk sequentially through this node list (unit) until
      // we find a property with name, or we hit the end
      bool flag = true;
      while(flag)
      {
         // look for an element at current location with name
         MSXML::IXMLDOMNodePtr ptest = GetCurrentNode(name);
         if ((bool)ptest)
         {
            // ask parser if a Property was last parsed item
            if (MSXML::NODE_ELEMENT==ptest->nodeType)
            {
               // found our node - let's get the value and type
               *pval = ptest->nodeTypedValue;

               try
               {
                  _bstr_t refnam = ptest->attributes->getNamedItem("VarType")->text;
                  if (refnam.length()!=0)
                  {
                     bsvt = refnam;
                  }
                  else
                  {
                     ATLASSERT(false); // something's fishy with the file format here.
                     bsvt = _bstr_t("VT_EMPTY");
                  }
               }
               catch (...)
               {
                  // node did not have a VarType - could be an older version
                  bsvt = _bstr_t("VT_EMPTY");
               }

               retval = true;
               flag = false; // got our work done - only successful way out
            }
         }
         else
         {
            // node not found. 
            flag = ReadNext(); 
         }
      }
   }
   catch(_com_error &e) 
   {
      ATLASSERT(false);
      CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, e.Description());
      THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
   }
   catch(...)
   {
      THROW_IDS(IDS_STRLOAD_E_INVALIDFORMAT,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
   }

   return retval;
}

MSXML::IXMLDOMNodePtr CStructuredLoad2::GetCurrentNode(BSTR name)
{
   ATLASSERT(!m_NodeStack.empty());

   _bstr_t bname(name);
   const MSXML::IXMLDOMNodePtr& rback = m_NodeStack.back().spCurrentChild;
   if (rback != NULL)
   {
      _bstr_t nodenm = rback->nodeName;
      if (nodenm == bname )
         return rback;
      else
         return 0;
   }
   else
      return 0;
}

bool CStructuredLoad2::ReadNext()
{
   ATLASSERT(!m_NodeStack.empty());
   MSXML::IXMLDOMNodePtr& rback = m_NodeStack.back().spCurrentChild;

   if (rback != NULL)
   {
      rback = rback->nextSibling;
   }
   else
   {
      ATLASSERT(false); // should not be trying to read next if previous was null
   }

   return (bool)rback;
}

////////////////////////////////////////////////////////////////////////////
// Helper function: Check load results
////////////////////////////////////////////////////////////////////////////
void CheckLoad(MSXML::IXMLDOMDocument* pDoc)
{
    // Since we don't have the VARIANT_BOOL from load we
    // need to check the parse Error errorCode property to see
    // if everything went ok.
   try
   {
       MSXML::IXMLDOMParseErrorPtr pXMLError = pDoc->parseError;
       long code = pXMLError->errorCode;
       if (code != 0)
       {
          CComBSTR errmsg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, GetParseError(pXMLError));
          THROW_MSG(errmsg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
       }
   }
   catch(_com_error e)
   {
      CComBSTR msg = CreateErrorMsgStr1(IDS_STRLOAD_E_INVALIDFORMAT, e.Description());
      THROW_MSG(msg,STRLOAD_E_INVALIDFORMAT,IDH_STRLOAD_E_INVALIDFORMAT);
   }
}


////////////////////////////////////////////////////////////////////////////
// Helper function: Report parsing error information
////////////////////////////////////////////////////////////////////////////
_bstr_t GetParseError(MSXML::IXMLDOMParseErrorPtr pXMLError)
{
   long line, linePos;
   LONG errorCode;
   _bstr_t pBURL, pBReason;
   std::_tostringstream os;

   try
   {
      line = pXMLError->line;
      linePos = pXMLError->linepos;
      errorCode = pXMLError->errorCode;
      pBURL = pXMLError->url;
      pBReason = pXMLError->reason;

      if (line > 0)
        os<< "Error in xml file on line "<< line<<", position "<<linePos<<" in \""<<(TCHAR*)pBURL<<"\" Reason was "<<(TCHAR*)pBReason; 
      else
         os<<"Error in xml file - location unknown";
   }
   catch(...)
   {
      ATLASSERT(false);
   }

   return _bstr_t ( os.str().c_str());
}
