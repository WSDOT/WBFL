///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
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

#if !defined(AFX_STRSAVE_H__0131A8C4_26EB_11D2_8EB0_006097DF3C68__INCLUDED_)
#define AFX_STRSAVE_H__0131A8C4_26EB_11D2_8EB0_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StrSave.h : header file
//

#include <System\StructuredSaveXML.h>
#include <System\FileStream.h>

/////////////////////////////////////////////////////////////////////////////
// CStrSave command target
class ATL_NO_VTABLE CStrSave : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStrSave, &CLSID_StructuredSave>,
   public IStructuredSave
{
public:
	CStrSave();
   virtual ~CStrSave();

DECLARE_REGISTRY_RESOURCEID(IDR_STRSAVE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrSave)
	COM_INTERFACE_ENTRY(IStructuredSave)
END_COM_MAP()


   BOOL m_bOpen;

// IStructuredSave
public:
   STDMETHOD(Open)(/*[in]*/ LPCTSTR name) override;
   STDMETHOD(BeginUnit)(/*[in]*/ LPCTSTR name, /*[in]*/ Float64 ver) override;
	STDMETHOD(put_Property)(/*[in]*/ LPCTSTR name, /*[in]*/ VARIANT newVal) override;
   STDMETHOD(get_TopVersion)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_ParentVersion)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_ParentUnit)(BSTR* pParentUnit) override;
   STDMETHOD(get_Version)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(EndUnit)() override;
   STDMETHOD(Close)() override;
   STDMETHOD(SaveRawUnit)(/*[in]*/LPCTSTR unitXML) override;

private:
   WBFL::System::StructuredSaveXml m_StrSave;
   WBFL::System::FileStream m_File;

   HRESULT HandleException( WBFL::System::XStructuredSave& e );
   HRESULT HandleException2(WBFL::System::XStructuredSave& e);

 //  HRESULT Open(/*[in]*/ LPCTSTR bstrFileName);
	//HRESULT BeginUnit(/*[in]*/ LPCTSTR bstrUnit,/*[in]*/ Float64 ver);
	//HRESULT EndUnit();
	//HRESULT get_Version(/*[out, retval]*/ Float64 *pVal);
	//HRESULT get_ParentVersion(/*[out, retval]*/ Float64 *pVal);
	//HRESULT get_TopVersion(/*[out, retval]*/ Float64 *pVal);
	//HRESULT put_Property(/*[in]*/ LPCTSTR bstrPropName, /*[in]*/ VARIANT newVal);
	//HRESULT Close();
};

OBJECT_ENTRY_AUTO(CLSID_StructuredSave,CStrSave)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRSAVE_H__0131A8C4_26EB_11D2_8EB0_006097DF3C68__INCLUDED_)
