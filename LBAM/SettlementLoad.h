///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright (C) 2009  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// SettlementLoad.h : Declaration of the CSettlementLoad

#ifndef __SETTLEMENTLOAD_H_
#define __SETTLEMENTLOAD_H_

#include "resource.h"       // main symbols
#include "LoadCP.h"

/////////////////////////////////////////////////////////////////////////////
// CSettlementLoad
class ATL_NO_VTABLE CSettlementLoad : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSettlementLoad,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSettlementLoad, &CLSID_SettlementLoad>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CSettlementLoad>,
	public ISettlementLoad,
   public IPersistImpl<CSettlementLoad>,
	public IStructuredStorage2,
   public IObjectSafetyImpl<CSettlementLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDSettlementLoadEvents< CSettlementLoad >
{
public:
   CSettlementLoad():
   m_MemberID(-1),
   m_Dx(0.0),
   m_Dy(0.0),
   m_Rz(0.0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SETTLEMENTLOAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSettlementLoad)
	COM_INTERFACE_ENTRY(ISettlementLoad)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSettlementLoad)
CONNECTION_POINT_ENTRY(IID_ISettlementLoadEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

// ISettlementLoad
public:
	STDMETHOD(Clone)(/*[out,retval]*/ISettlementLoad** clone);
	STDMETHOD(get_Rz)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Rz)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Dy)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Dy)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Dx)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Dx)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal);
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal);

protected:
   MemberIDType  m_MemberID;
   Float64       m_Dx;
   Float64       m_Dy;
   Float64       m_Rz;

};

#endif //__SETTLEMENTLOAD_H_
