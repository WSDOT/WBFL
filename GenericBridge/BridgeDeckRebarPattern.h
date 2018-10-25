///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2017  Washington State Department of Transportation
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

// BridgeDeckRebarPattern.h : Declaration of the CBridgeDeckRebarPattern
#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CBridgeDeckRebarPattern
class ATL_NO_VTABLE CBridgeDeckRebarPattern : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CBridgeDeckRebarPattern,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CBridgeDeckRebarPattern, &CLSID_BridgeDeckRebarPattern>,
	public ISupportErrorInfo,
	public IBridgeDeckRebarPattern,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CBridgeDeckRebarPattern,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CBridgeDeckRebarPattern()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_BRIDGEDECKREBARPATTERN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBridgeDeckRebarPattern)
	COM_INTERFACE_ENTRY(IBridgeDeckRebarPattern)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

   CComPtr<IRebar> m_Rebar;
   CComPtr<IBridgeDeckRebarLayoutItem> m_RebarLayoutItem;
   Float64 m_Spacing;
   Float64 m_Y; // elevation above the bottom of the slab
   VARIANT_BOOL m_bIsLumped; // if true, the rebar is a lumped area/length

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBridgeDeckRebarPattern
public:
   STDMETHOD(putref_Rebar)(IRebar* rebar) override;
	STDMETHOD(get_Rebar)(IRebar** rebar) override;
	STDMETHOD(putref_RebarLayoutItem)(IBridgeDeckRebarLayoutItem* rebarLayoutItem) override;
	STDMETHOD(put_Spacing)(Float64 spacing) override;
	STDMETHOD(get_Spacing)(Float64* spacing) override;
	STDMETHOD(put_Location)(Float64 y) override;
	STDMETHOD(get_Location)(Float64* pY) override;
   STDMETHOD(put_IsLumped)(VARIANT_BOOL bIsLumped) override;
   STDMETHOD(get_IsLumped)(VARIANT_BOOL* pbIsLumped) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

