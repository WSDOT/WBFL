///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
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

// TemperatureLoad.h : Declaration of the CTemperatureLoad

#ifndef __TEMPERATURELOAD_H_
#define __TEMPERATURELOAD_H_

#include "resource.h"       // main symbols
#include "LoadingCP.h"

/////////////////////////////////////////////////////////////////////////////
// CTemperatureLoad
class ATL_NO_VTABLE CTemperatureLoad : 
public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CTemperatureLoad,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CTemperatureLoad, &CLSID_ldTemperatureLoad>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CTemperatureLoad>,
	public ldITemperatureLoad,
   public IPersistImpl<CTemperatureLoad>,
	public IStructuredStorage2,
   public IObjectSafetyImpl<CTemperatureLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDTemperatureLoadEvents< CTemperatureLoad >
{
public:
   CTemperatureLoad():
   m_MemberID(-1),
   m_TTop(0.0),
   m_TBottom(0.0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TEMPERATURELOAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTemperatureLoad)
	COM_INTERFACE_ENTRY(ldITemperatureLoad)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTemperatureLoad)
CONNECTION_POINT_ENTRY(IID_ldITemperatureLoadEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// ldITemperatureLoad
public:
	STDMETHOD(Clone)(/*[out,retval]*/ldITemperatureLoad** clone) override;
	STDMETHOD(get_TBottom)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_TBottom)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_TTop)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_TTop)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal) override;
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal) override;
//	STDMETHOD(get_MemberType)(/*[out, retval]*/ MemberType *pVal) override;
//	STDMETHOD(put_MemberType)(/*[in]*/ MemberType newVal) override;

protected:
//   MemberType   m_MemberType;
   MemberIDType  m_MemberID;
   Float64       m_TTop;
   Float64       m_TBottom;
};

#endif //__TEMPERATURELOAD_H_
