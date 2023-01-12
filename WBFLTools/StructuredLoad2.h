///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2023  Washington State Department of Transportation
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

// StructuredLoad2.h : Declaration of the CStructuredLoad2

#ifndef __STRUCTUREDLOAD2_H_
#define __STRUCTUREDLOAD2_H_

#include "resource.h"       // main symbols

#include <list>
#include <map>

#import  <msxml6.dll> rename_namespace("MSXML")

/////////////////////////////////////////////////////////////////////////////
// CStructuredLoad2
class ATL_NO_VTABLE CStructuredLoad2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStructuredLoad2, &CLSID_StructuredLoad2>,
   public IObjectSafetyImpl<CStructuredLoad2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo,
	public IStructuredLoad2
{
public:
	CStructuredLoad2()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRUCTUREDLOAD2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStructuredLoad2)
	COM_INTERFACE_ENTRY(IStructuredLoad2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStructuredLoad2
		STDMETHOD(Open)(/*[in]*/ BSTR bstrFile) override;
		STDMETHOD(BeginUnit)(/*[in]*/ BSTR bstrUnit) override;
		STDMETHOD(EndUnit)(/*[out,retval]*/VARIANT_BOOL* bEnd) override;
		STDMETHOD(get_Version)(/*[out, retval]*/ Float64 *pVal) override;
		STDMETHOD(get_TopVersion)(/*[out, retval]*/ Float64 *pVal) override;
		STDMETHOD(get_Property)(/*[in]*/ BSTR bstrPropName, /*[out, retval]*/ VARIANT *pVal) override;
		STDMETHOD(EndOfStorage)(/*[out,retval]*/VARIANT_BOOL* bEnd) override;
		STDMETHOD(Close)() override;

private:
   CComPtr<IStream>                m_pIStream;
   BOOL m_bOpen;
   MSXML::IXMLDOMDocumentPtr       m_spDoc;        // the top-level document
   MSXML::IXMLDOMNodePtr           m_spObjectTable;// top-level node of object table

   // stack to keep track of recursive calls to parser
   struct ListItem
   {
      _bstr_t               Name;
      Float64                Version;
      MSXML::IXMLDOMNodePtr spCurrentUnit;
      MSXML::IXMLDOMNodePtr spCurrentChild;
   };
   typedef std::list<ListItem> NodeStack;
   typedef NodeStack::const_iterator NodeStackConstIterator;
   NodeStack   m_NodeStack; // stack of information about current units.

   // Running object table. These are the objects that have been brought to life
   typedef std::map<_bstr_t, CComPtr<IUnknown> > ObjectTable;
   typedef ObjectTable::iterator ObjectTableIterator;
   ObjectTable m_RunningObjectTable;

   // private methods
   void AssertValid() const;
   void BeginLoad(IStream* pis);
   void EndLoad();

   MSXML::IXMLDOMNodePtr GetCurrentNode(BSTR name);
   bool GetProperty(BSTR name, _variant_t* pval, _bstr_t& bsvt);
   bool ReadNext();
   CComPtr<IUnknown> GetObjectRef( BSTR bsobjref );
};

#endif //__STRUCTUREDLOAD2_H_
