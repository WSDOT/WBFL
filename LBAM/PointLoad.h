///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2021  Washington State Department of Transportation
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

// PointLoad.h : Declaration of the CPointLoad

#ifndef __POINTLOAD_H_
#define __POINTLOAD_H_

#include "resource.h"       // main symbols
#include "LoadCP.h"

/////////////////////////////////////////////////////////////////////////////
// CPointLoad
class ATL_NO_VTABLE CPointLoad : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPointLoad,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPointLoad, &CLSID_PointLoad>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPointLoad>,
	public IPointLoad,
   public IPersistImpl<CPointLoad>,
	public IStructuredStorage2, 
   public IObjectSafetyImpl<CPointLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDPointLoadEvents< CPointLoad >
{
public:
   CPointLoad():
   m_Location(0.0),
   m_MemberID(-1),
   m_MemberType(mtUndefined),
   m_Fx(0.0),
   m_Fy(0.0),
   m_Mz(0.0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_POINTLOAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPointLoad)
	COM_INTERFACE_ENTRY(IPointLoad)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPointLoad)
CONNECTION_POINT_ENTRY(IID_IPointLoadEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// IPointLoad
public:
	STDMETHOD(Clone)(/*[out,retval]*/IPointLoad** clone) override;
	STDMETHOD(GetForce)(/*[out]*/Float64* Fx, /*[out]*/Float64* Fy, /*[out]*/Float64* Mz) override;
	STDMETHOD(SetForce)(/*[in]*/Float64 Fx, /*[in]*/Float64 Fy, /*[in]*/Float64 Mz) override;
	STDMETHOD(get_Mz)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Mz)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Fy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Fy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Fx)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Fx)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Location)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Location)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal) override;
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal) override;
	STDMETHOD(get_MemberType)(/*[out, retval]*/ MemberType *pVal) override;
	STDMETHOD(put_MemberType)(/*[in]*/ MemberType newVal) override;

protected:
   MemberType    m_MemberType;
   MemberIDType  m_MemberID;
   Float64       m_Location;
   Float64       m_Fx;
   Float64       m_Fy;
   Float64       m_Mz;
};

#endif //__POINTLOAD_H_
