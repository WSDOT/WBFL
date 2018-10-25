///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2014  Washington State Department of Transportation
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

#if !defined(AFX_STRLOAD_H__0131A8C3_26EB_11D2_8EB0_006097DF3C68__INCLUDED_)
#define AFX_STRLOAD_H__0131A8C3_26EB_11D2_8EB0_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StrLoad.h : header file
//

#include <System\StructuredLoadXMLPrs.h>
#include <System\FileStream.h>
#include <iostream>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// CStrLoad command target
class ATL_NO_VTABLE CStrLoad : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStrLoad, &CLSID_StructuredLoad>,
   public IStructuredLoad
{
public:
	CStrLoad()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRLOAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrLoad)
	COM_INTERFACE_ENTRY(IStructuredLoad)
END_COM_MAP()


// IStructuredLoad
public:
	STDMETHOD(Open)(/*[in]*/ LPCTSTR name);
	STDMETHOD(BeginUnit)(/*[in]*/ LPCTSTR name);
	STDMETHOD(EndUnit)();
	STDMETHOD(get_Version)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_ParentVersion)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_TopVersion)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Property)(/*[in]*/ LPCTSTR name, /*[out, retval]*/ VARIANT *pVal);
   STDMETHOD(get_ParentUnit)(BSTR* pParentUnit);
   STDMETHOD(EndOfStorage)();
	STDMETHOD(Close)();
   STDMETHOD(LoadRawUnit)(/*[out]*/ BSTR* pbstrUnit);

private:
   sysStructuredLoadXmlPrs m_StrLoad;
   FileStream m_File;
   BOOL m_bOpen;

   HRESULT HandleException( sysXStructuredLoad& e );
   HRESULT HandleException2( sysXStructuredLoad& e );

   //HRESULT Open(/*[in]*/ LPCTSTR bstrFile);
   //HRESULT BeginUnit(/*[in]*/ LPCTSTR bstrUnit);
   //HRESULT get_EndUnit(/*[out,retval]*/VARIANT_BOOL* bEnd);
   //HRESULT get_Version(/*[out, retval]*/ Float64 *pVal);
   //HRESULT get_ParentVersion(/*[out, retval]*/ Float64 *pVal);
   //HRESULT get_TopVersion(/*[out, retval]*/ Float64 *pVal);
   //HRESULT get_Property(/*[in]*/ LPCTSTR bstrPropName, /*[out, retval]*/ VARIANT *pVal);
   //HRESULT get_EndOfStorage(/*[out,retval]*/VARIANT_BOOL* bEnd);
   //HRESULT Close();
};

OBJECT_ENTRY_AUTO(CLSID_StructuredLoad,CStrLoad)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRLOAD_H__0131A8C3_26EB_11D2_8EB0_006097DF3C68__INCLUDED_)
