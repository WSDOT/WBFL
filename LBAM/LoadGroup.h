///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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

// LoadGroup.h : Declaration of the CLoadGroup

#ifndef __LOADGROUP_H_
#define __LOADGROUP_H_

#include "resource.h"       // main symbols
#include "LoadGroupCP.h"

/////////////////////////////////////////////////////////////////////////////
// CLoadGroup
class ATL_NO_VTABLE CLoadGroup : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CLoadGroup,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CLoadGroup, &CLSID_LoadGroup>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLoadGroup>,
	public ILoadGroup,
   public IPersistImpl<CLoadGroup>,
	public IStructuredStorage2, 
   public IObjectSafetyImpl<CLoadGroup,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDLoadGroupEvents< CLoadGroup >
{
public:
   CLoadGroup():
   m_Transient(VARIANT_FALSE)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADGROUP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadGroup)
	COM_INTERFACE_ENTRY(ILoadGroup)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadGroup)
CONNECTION_POINT_ENTRY(IID_ILoadGroupEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

// ILoadGroup
public:
	STDMETHOD(get_Transient)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Transient)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(Clone)(/*[out,retval]*/ILoadGroup** clone);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);

protected:
   CComBSTR     m_Name;
   CComBSTR     m_Description;
   VARIANT_BOOL m_Transient;
};

#endif //__LOADGROUP_H_
