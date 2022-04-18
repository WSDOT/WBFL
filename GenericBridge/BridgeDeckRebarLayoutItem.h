///////////////////////////////////////////////////////////////////////
// GenericBridge - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2022  Washington State Department of Transportation
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

// BridgeDeckRebarLayoutItem.h : Declaration of the CBridgeDeckRebarLayoutItem

#pragma once

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"

class CBridgeDeckRebarLayoutItem;
typedef CComVectorCollection<IBridgeDeckRebarLayoutItem,IBridgeDeckRebarPattern,IEnumBridgeDeckRebarPatterns,&IID_IEnumBridgeDeckRebarPatterns,CollectionIndexType> DeckRebarPtrnColl;
typedef CPersistentCollection<CBridgeDeckRebarLayoutItem,DeckRebarPtrnColl,CollectionIndexType> PersistentDeckRebarLayoutItem;

/////////////////////////////////////////////////////////////////////////////
// CBridgeDeckRebarLayoutItem
class ATL_NO_VTABLE CBridgeDeckRebarLayoutItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CBridgeDeckRebarLayoutItem,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CBridgeDeckRebarLayoutItem, &CLSID_BridgeDeckRebarLayoutItem>,
	public ISupportErrorInfo,
   public PersistentDeckRebarLayoutItem,
   public IObjectSafetyImpl<CBridgeDeckRebarLayoutItem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CBridgeDeckRebarLayoutItem()
	{
      m_pBridge = 0;
	}

   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_BRIDGEDECKREBARLAYOUTITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBridgeDeckRebarLayoutItem)
   COM_INTERFACE_ENTRY(IBridgeDeckRebarLayoutItem)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

protected:
   CComBSTR GetCollectionName() { return CComBSTR("RebarPatterns"); }
   CComBSTR GetStoredName()     { return CComBSTR("RebarPattern");  }
   HRESULT DoSaveItem(IStructuredSave2* save,IRebarPattern* item);
   HRESULT DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem);

   IGenericBridge* m_pBridge;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBridgeDeckRebarLayoutItem
public:
   STDMETHOD(ContainsLocation)(/*[in]*/ Float64 distFromStart,/*[in]*/ Float64 offset,/*[out,retval]*/ VARIANT_BOOL* bResult) override;
	STDMETHOD(get_Start)(/*[out,retval]*/Float64* start) override;
	STDMETHOD(get_Length)(/*[out,retval]*/Float64* length) override;
//	STDMETHOD(get_Item)(/*[in]*/ long idx,/*[out,retval]*/IRebarPattern** pattern) override;
	STDMETHOD(AddRebarPattern)(/*[in]*/IBridgeDeckRebarPattern* pattern) override;
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;  
   STDMETHOD(get__EnumRebarPatterns)(/*[out,retval]*/IEnumBridgeDeckRebarPatterns** enumRebarPatterns) override;
	STDMETHOD(putref_Bridge)(/*[in]*/IGenericBridge* pBridge) override;
};
