///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// RebarSectionItem.h : Declaration of the CRebarSectionItem

#ifndef __RebarSectionItem_H_
#define __RebarSectionItem_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRebarSectionItem
class ATL_NO_VTABLE CRebarSectionItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CRebarSectionItem,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CRebarSectionItem, &CLSID_RebarSectionItem>,
	public ISupportErrorInfo,
	public IRebarSectionItem,
	public IStructuredStorage2,
   public IObjectSafetyImpl<CRebarSectionItem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CRebarSectionItem()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_REBARSECTIONITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRebarSectionItem)
	COM_INTERFACE_ENTRY(IRebarSectionItem)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRebarSectionItem
public:
   STDMETHOD(Init)(IPoint2d* location,Float64 distFromStart,Float64 distFromEnd,IRebar* rebar);
   STDMETHOD(get_Location)(/*[out,retval]*/IPoint2d** location);
	STDMETHOD(get_LeftExtension)(/*[out,retval]*/ Float64* dist);
	STDMETHOD(get_RightExtension)(/*[out,retval]*/ Float64* dist);
   STDMETHOD(get_Rebar)(/*[out,retval]*/ IRebar** rebar);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

private:
   CComPtr<IPoint2d> m_Location;
   Float64 m_LeftExtension;
   Float64 m_RightExtension;
   CComPtr<IRebar> m_Rebar;
};

#endif //__RebarSectionItem_H_
