///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright � 1999-2025  Washington State Department of Transportation
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

#pragma once

// BridgeDeckRebarLayout.h : Declaration of the CBridgeDeckRebarLayout

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"

class CBridgeDeckRebarLayout;
using BridgeDeckItemColl = CComVectorCollection<IBridgeDeckRebarLayout, IBridgeDeckRebarLayoutItem, IEnumBridgeDeckRebarLayoutItems, &IID_IEnumBridgeDeckRebarLayoutItems, IndexType>;
using PersistentBridgeDeckRebarLayout = CPersistentCollection<CBridgeDeckRebarLayout,BridgeDeckItemColl,IndexType>;

/////////////////////////////////////////////////////////////////////////////
// CRebarLayout
class ATL_NO_VTABLE CBridgeDeckRebarLayout : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CBridgeDeckRebarLayout,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CBridgeDeckRebarLayout, &CLSID_BridgeDeckRebarLayout>,
	public ISupportErrorInfo,
   public PersistentBridgeDeckRebarLayout,
   public IObjectSafetyImpl<CBridgeDeckRebarLayout,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CBridgeDeckRebarLayout()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_BRIDGEDECKREBARLAYOUT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBridgeDeckRebarLayout)
   COM_INTERFACE_ENTRY(IBridgeDeckRebarLayout)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

protected:
   CComBSTR GetCollectionName() { return CComBSTR("RebarLayout"); }
   CComBSTR GetStoredName()     { return CComBSTR("RebarLayoutItems");  }
   HRESULT DoSaveItem(IStructuredSave2* save,IRebarPattern* item);
   HRESULT DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem);

   CComPtr<IEffectiveFlangeWidthTool> m_EffFlangeTool;
   CComPtr<IGenericBridge> m_Bridge;
   CComPtr<IBridgeGeometryTool> m_BridgeGeometryTool;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBridgeDeckRebarLayout
public:
   STDMETHOD(putref_Bridge)(IGenericBridge* pBridge) override;
	STDMETHOD(get_Bridge)(IGenericBridge** ppBridge) override;
   STDMETHOD(putref_EffectiveFlangeWidthTool)(IEffectiveFlangeWidthTool* pTool) override;
	STDMETHOD(get_EffectiveFlangeWidthTool)(IEffectiveFlangeWidthTool* *pTool) override;
   STDMETHOD(CreateRebarSection)(IDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,IRebarSection** section) override;
//   STDMETHOD(get_Item)(/*[in]*/long idx,/*[out,retval]*/IRebarLayoutItem** rli) override;
//	STDMETHOD(get_Count)(/*[out,retval]*/ long* count) override;
//	STDMETHOD(Add)(/*[in]*/IBridgeDeckRebarLayoutItem* rli) override;
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;  
   STDMETHOD(get__EnumRebarLayoutItems)(/*[out,retval]*/IEnumBridgeDeckRebarLayoutItems** enumRebarLayoutItems) override;
};
