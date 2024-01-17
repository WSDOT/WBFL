///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2024  Washington State Department of Transportation
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

// POIStressPoints.h : Declaration of the CPOIStressPoints

#ifndef __POISTRESSPOINTS_H_
#define __POISTRESSPOINTS_H_

#include "resource.h"       // main symbols
#include "POIStressPointsItem.h"
#include "POICP.h"

#include <WbflComCollections.h>
#include <map>


/////////////////////////////////////////////////////////////////////////////
// CPOIStressPoints
class ATL_NO_VTABLE CPOIStressPoints : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPOIStressPoints, &CLSID_POIStressPoints>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPOIStressPoints>,
	public IPOIStressPoints,
   public IPersistImpl<CPOIStressPoints>,
	public IStructuredStorage2,
	public CProxyDPOIEvents< CPOIStressPoints >,
	public IStressPointsEvents,
   public IObjectSafetyImpl<CPOIStressPoints,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDPOIStressPointsEvents< CPOIStressPoints >
{
public:
	CPOIStressPoints()
	{
	}

void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_POISTRESSPOINTS)
DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPOIStressPoints)
   COM_INTERFACE_ENTRY(IPOIStressPoints)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IStressPointsEvents)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPOIStressPoints)
CONNECTION_POINT_ENTRY(IID_IPOIStressPointsEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// IStressPointsEvents
   STDMETHOD(OnStressPointsChanged)(/*[in]*/IndexType index) override;
   STDMETHOD(OnStressPointsAdded)(/*[in]*/IndexType index) override;
   STDMETHOD(OnStressPointsRemoved)(/*[in]*/IndexType index) override;

// IPOIStressPoints
public:
	STDMETHOD(Clone)(/*[out,retval]*/IPOIStressPoints** Clone) override;
	STDMETHOD(Remove)(/*[in]*/BSTR Stage) override;
	STDMETHOD(Insert)(/*[in]*/BSTR Stage, /*[in]*/IStressPoints* leftSps, /*[in]*/IStressPoints* rightSps) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(get_Item)(/*[in]*/VARIANT idx, /*[out, retval]*/ IPOIStressPointsItem* *pVal) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ IndexType *pVal) override;
   STDMETHOD(get__EnumElements)(IEnumPOIStressPoints **ppenum) override;
   STDMETHOD(get__NewEnum)(IUnknown** ppUnk) override;

private:

   using ItemType = CAdapt<CComPtr<IPOIStressPointsItem>>;
   using StoredType = std::pair<CComBSTR, ItemType>;
   using ContainerType = std::map< CComBSTR, ItemType>;
   using IteratorType = ContainerType::iterator;

   // copy functions for enums
   using CustomCopyType = _CopyInterfacePair<IPOIStressPointsItem, std::pair<CComBSTR const, ItemType>>;
   using CopyType = _CopyVariantFromInterfacePair<std::pair<CComBSTR const, ItemType>>;


   ContainerType m_Container;

   void DoErase(IteratorType& it, bool doFire=true);
};

#endif //__POISTRESSPOINTS_H_
