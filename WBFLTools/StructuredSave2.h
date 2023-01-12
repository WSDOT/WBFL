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

// StructuredSave2.h : Declaration of the CStructuredSave2

#ifndef __STRUCTUREDSAVE2_H_
#define __STRUCTUREDSAVE2_H_

#include <list>
#include <map>
#import  <msxml6.dll> rename_namespace("MSXML")


#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStructuredSave2
class ATL_NO_VTABLE CStructuredSave2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStructuredSave2, &CLSID_StructuredSave2>,
   public IObjectSafetyImpl<CStructuredSave2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo,
	public IStructuredSave2
{
public:
   CStructuredSave2();

DECLARE_REGISTRY_RESOURCEID(IDR_STRUCTUREDSAVE2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStructuredSave2)
	COM_INTERFACE_ENTRY(IStructuredSave2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStructuredSave2
public:
	STDMETHOD(Open)(/*[in]*/ BSTR bstrFileName) override;
	STDMETHOD(BeginUnit)(/*[in]*/ BSTR bstrUnit,/*[in]*/ Float64 ver) override;
	STDMETHOD(EndUnit)() override;
	STDMETHOD(get_Version)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_TopVersion)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Property)(/*[in]*/ BSTR bstrPropName, /*[in]*/ VARIANT newVal) override;
	STDMETHOD(Close)() override;

private:
   // Data Members
   CComPtr<IStream>                m_pIStream;
   bool                            m_bOpen;
   bool                            m_WroteTopUnit; // can only write top unit once
   MSXML::IXMLDOMDocumentPtr       m_spDoc;        // the top-level document
   MSXML::IXMLDOMNodePtr           m_spObjectTable;// top-level node of object table

   // keep Stack of current Nodes (Units) being saved
   struct ListItem
   {
      _bstr_t               Name;
      Float64                Version;
      MSXML::IXMLDOMNodePtr spCurrentNode;
   };
   typedef std::list<ListItem> NodeStack;
   typedef NodeStack::const_iterator NodeStackConstIterator;
   NodeStack   m_NodeStack;

   // Set of objects that have already been saved. This is needed so we don't 
   // save the same object twice.
   typedef std::map<IUnknown*,_bstr_t> ObjectSet;
   typedef ObjectSet::const_iterator ObjectSetConstIterator;
   ObjectSet m_ObjectSet;

   // Unique object names
   long m_NextName;

private:
   // Operations
   void Property(BSTR name, IUnknown *pUnk, MSXML::IXMLDOMNodePtr& pchild);
   void BeginSave(IStream* pis);
   void EndSave();

   MSXML::IXMLDOMNodePtr MakeChildNode(BSTR name, Float64 vers=0.0);
   MSXML::IXMLDOMNodePtr MakePropertyNode(BSTR name, VARIANT* pVar);

   HRESULT HandleException();
   void AssertValid() const;
};

#endif //__STRUCTUREDSAVE2_H_
