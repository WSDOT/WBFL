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

// POIStressPointsItem.h : Declaration of the CPOIStressPointsItem

#ifndef __POISTRESSPOINTSITEM_H_
#define __POISTRESSPOINTSITEM_H_

#include "resource.h"       // main symbols
class CPOIStressPoints;

/////////////////////////////////////////////////////////////////////////////
// CPOIStressPointsItem
class ATL_NO_VTABLE CPOIStressPointsItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPOIStressPointsItem, &CLSID_POIStressPointsItem>,
   public IPersistImpl<CPOIStressPointsItem>,
	public IStructuredStorage2,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPOIStressPointsItem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IPOIStressPointsItem
{
public:
   CPOIStressPointsItem():
      m_LeftCookie(0),
      m_RightCookie(0)
	{
	}

// our friend the collection
   friend CPOIStressPoints;

DECLARE_REGISTRY_RESOURCEID(IDR_POISTRESSPOINTSITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPOIStressPointsItem)
	COM_INTERFACE_ENTRY(IPOIStressPointsItem)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPOIStressPointsItem)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPOIStressPointsItem
public:
	STDMETHOD(get_RightStressPoints)(/*[out, retval]*/ IStressPoints* *pVal);
	STDMETHOD(get_LeftStressPoints)(/*[out, retval]*/ IStressPoints* *pVal);
	STDMETHOD(get_Stage)(/*[out, retval]*/ BSTR *pVal);

   // IStructuredStorage2 (not officially)
   STDMETHOD(Load)(IStructuredLoad2 * pload);
   STDMETHOD(Save)(IStructuredSave2 * psave);


private:
// public only to our local friends - our cookies for connection points
   DWORD m_LeftCookie;
   DWORD m_RightCookie;
   CComBSTR               m_Stage;
   CComPtr<IStressPoints> m_LeftStressPoints;
   CComPtr<IStressPoints> m_RightStressPoints;
};

#endif //__POISTRESSPOINTSITEM_H_
