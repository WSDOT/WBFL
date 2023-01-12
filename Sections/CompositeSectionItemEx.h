///////////////////////////////////////////////////////////////////////
// Sections - Model bridge member cross sections
// Copyright © 1999-2023  Washington State Department of Transportation
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

// CompositeSectionItemEx.h : Declaration of the CCompositeSectionItem

#ifndef __COMPOSITESECTIONITEMEX_H_
#define __COMPOSITESECTIONITEMEX_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCompositeSectionItemEx
class ATL_NO_VTABLE CCompositeSectionItemEx : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCompositeSectionItemEx, &CLSID_CompositeSectionItemEx>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCompositeSectionItemEx,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ICompositeSectionItemEx,
   public IStructuredStorage2,
   public IPersistImpl<CCompositeSectionItemEx>
{
public:
	CCompositeSectionItemEx()
	{
      m_bStructural = VARIANT_TRUE;
      m_Dfg     = 1;
      m_Dbg     = 0;
      m_Efg     = 1;
      m_Ebg     = 0;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_COMPOSITESECTIONITEMEX)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCompositeSectionItemEx)
	COM_INTERFACE_ENTRY(ICompositeSectionItemEx)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICompositeSectionItemEx
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
	STDMETHOD(get_Structural)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_Structural)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(get_Dfg)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Dfg)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Dbg)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Dbg)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Efg)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Efg)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Ebg)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Ebg)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(putref_Shape)(/*[in]*/ IShape* newVal) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

private:
   VARIANT_BOOL m_bStructural;
   Float64 m_Dfg;
   Float64 m_Dbg;
   Float64 m_Efg;
   Float64 m_Ebg;
   CComPtr<IShape> m_Shape;
};

#endif //__COMPOSITESECTIONITEMEX_H_
