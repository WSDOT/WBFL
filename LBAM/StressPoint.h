///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
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

// StressPoint.h : Declaration of the CStressPoint

#ifndef __STRESSPOINT_H_
#define __STRESSPOINT_H_

#include "resource.h"       // main symbols
#include "CrossSectionCP.h"

/////////////////////////////////////////////////////////////////////////////
// CStressPoint
class ATL_NO_VTABLE CStressPoint : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CStressPoint,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CStressPoint, &CLSID_StressPoint>,
   public IPersistImpl<CStressPoint>,
	public ISupportErrorInfo,
	public IStressPoint,
	public IStructuredStorage2,
	public IConnectionPointContainerImpl<CStressPoint>,
   public IObjectSafetyImpl<CStressPoint,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDStressPointEvents< CStressPoint >
{
public:
   CStressPoint():
   m_Sm(0.0),
   m_Sa(0.0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRESSPOINT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStressPoint)
	COM_INTERFACE_ENTRY(IStressPoint)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStressPoint
public:
	STDMETHOD(get_Sm)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Sm)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Sa)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Sa)(/*[in]*/ Float64 newVal);
// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

protected:
   Float64 m_Sm;
   Float64 m_Sa;
public :
	STDMETHOD(Clone)(/*[out]*/IStressPoint** clone);

BEGIN_CONNECTION_POINT_MAP(CStressPoint)
CONNECTION_POINT_ENTRY(IID_IStressPointEvents)
END_CONNECTION_POINT_MAP()

};

#endif //__STRESSPOINT_H_
