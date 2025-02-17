///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright � 1999-2025  Washington State Department of Transportation
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

// Axle.h : Declaration of the CAxle

#ifndef __AXLE_H_
#define __AXLE_H_

#include "resource.h"       // main symbols
#include "LoadingCP.h"

/////////////////////////////////////////////////////////////////////////////
// CAxle
class ATL_NO_VTABLE CAxle : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAxle, &CLSID_ldAxle>,
	public ISupportErrorInfo,
   public IPersistImpl<CAxle>,
	public IStructuredStorage2,
	public IConnectionPointContainerImpl<CAxle>,
	public ldIAxle,
	public CProxyDAxleEvents< CAxle >
{
public:
   CAxle():
   m_Weight(0.0),
   m_Spacing(0.0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AXLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAxle)
	COM_INTERFACE_ENTRY(ldIAxle)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAxle)
CONNECTION_POINT_ENTRY(IID_ldIAxleEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ldIAxle
public:
	STDMETHOD(Clone)(/*[out,retval]*/ldIAxle** clone) override;
	STDMETHOD(get_Spacing)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Spacing)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Weight)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Weight)(/*[in]*/ Float64 newVal) override;

// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

protected:
   Float64 m_Weight;
   Float64 m_Spacing;
};

#endif //__AXLE_H_
