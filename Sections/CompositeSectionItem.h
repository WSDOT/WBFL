///////////////////////////////////////////////////////////////////////
// Sections - Model bridge member cross sections
// Copyright © 1999-2010  Washington State Department of Transportation
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

// CompositeSectionItem.h : Declaration of the CCompositeSectionItem

#ifndef __COMPOSITESECTIONITEM_H_
#define __COMPOSITESECTIONITEM_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCompositeSectionItem
class ATL_NO_VTABLE CCompositeSectionItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCompositeSectionItem, &CLSID_CompositeSectionItem>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCompositeSectionItem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ICompositeSectionItemEx,
   public IStructuredStorage2,
   public IPersistImpl<CCompositeSectionItem>
{
public:
	CCompositeSectionItem()
	{
      m_bStructural = VARIANT_TRUE;
      m_bVoid       = VARIANT_FALSE;
      m_Density     = 1;
      m_E           = 1;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_COMPOSITESECTIONITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCompositeSectionItem)
	COM_INTERFACE_ENTRY(ICompositeSectionItemEx)
	COM_INTERFACE_ENTRY(ICompositeSectionItem)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICompositeSectionItem
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
	STDMETHOD(get_Structural)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Structural)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Void)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Void)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Density)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Density)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_E)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_E)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal);
	STDMETHOD(putref_Shape)(/*[in]*/ IShape* newVal);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

private:
   VARIANT_BOOL m_bStructural;
   VARIANT_BOOL m_bVoid;
   Float64 m_Density;
   Float64 m_E;
   CComPtr<IShape> m_Shape;
};

#endif //__COMPOSITESECTIONITEM_H_
