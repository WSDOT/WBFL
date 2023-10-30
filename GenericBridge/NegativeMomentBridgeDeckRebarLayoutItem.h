///////////////////////////////////////////////////////////////////////
// GenericBridge - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2023  Washington State Department of Transportation
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

// NegativeMomentBridgeDeckRebarLayoutItem.h : Declaration of the CNegativeMomentBridgeDeckRebarLayoutItem

#pragma once

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"

class CNegativeMomentBridgeDeckRebarLayoutItem;
using NegMomentDeckRebarPtrnColl = CComVectorCollection<INegativeMomentBridgeDeckRebarLayoutItem, IBridgeDeckRebarPattern, IEnumBridgeDeckRebarPatterns, &IID_IEnumBridgeDeckRebarPatterns, IndexType>;
using PersistentNegMomentDeckRebarLayoutItem = CPersistentCollection<CNegativeMomentBridgeDeckRebarLayoutItem,NegMomentDeckRebarPtrnColl,IndexType>;

/////////////////////////////////////////////////////////////////////////////
// CNegativeMomentBridgeDeckRebarLayoutItem
class ATL_NO_VTABLE CNegativeMomentBridgeDeckRebarLayoutItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CNegativeMomentBridgeDeckRebarLayoutItem,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CNegativeMomentBridgeDeckRebarLayoutItem, &CLSID_NegativeMomentBridgeDeckRebarLayoutItem>,
	public ISupportErrorInfo,
   public PersistentNegMomentDeckRebarLayoutItem,
   public IObjectSafetyImpl<CNegativeMomentBridgeDeckRebarLayoutItem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CNegativeMomentBridgeDeckRebarLayoutItem()
	{
      m_pBridge = 0;
      m_PierID = INVALID_ID;
      m_LeftCutoff = 0;
      m_RightCutoff = 0;
	}

   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_NMBRIDGEDECKREBARLAYOUTITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNegativeMomentBridgeDeckRebarLayoutItem)
   COM_INTERFACE_ENTRY(INegativeMomentBridgeDeckRebarLayoutItem)
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
   PierIDType m_PierID;
   Float64 m_LeftCutoff;
   Float64 m_RightCutoff;

   CComPtr<IBridgePier> m_Pier;
   Float64 m_PierLocation; // location of the pier measured as distance from start of bridge

   Float64 GetStart(Float64 offset);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// INegativeMomentBridgeDeckRebarLayoutItem
public:
   STDMETHOD(ContainsLocation)(/*[in]*/ Float64 distFromStart,/*[in]*/ Float64 offset,/*[out,retval]*/ VARIANT_BOOL* bResult) override;
	STDMETHOD(get_Start)(/*[out,retval]*/Float64* start) override;
	STDMETHOD(get_Length)(/*[out,retval]*/Float64* length) override;
//	STDMETHOD(get_Item)(/*[in]*/ long idx,/*[out,retval]*/IRebarPattern** pattern) override;
	STDMETHOD(AddRebarPattern)(/*[in]*/IBridgeDeckRebarPattern* pattern) override;
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;  
   STDMETHOD(get__EnumRebarPatterns)(/*[out,retval]*/IEnumBridgeDeckRebarPatterns** enumRebarPatterns) override;
	STDMETHOD(putref_Bridge)(/*[in]*/IGenericBridge* pBridge) override;
   STDMETHOD(put_PierID)(PierIDType pierID) override;
   STDMETHOD(get_PierID)(PierIDType* pPierID) override;
   STDMETHOD(put_LeftCutoff)(Float64 coLeft) override;
   STDMETHOD(get_LeftCutoff)(Float64* pcoLeft) override;
   STDMETHOD(put_RightCutoff)(Float64 coRight) override;
   STDMETHOD(get_RightCutoff)(Float64* pcoRight) override;
};
