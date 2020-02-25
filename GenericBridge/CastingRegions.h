///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2020  Washington State Department of Transportation
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

// CastingRegions.h : Declaration of the CCastingRegions

#pragma once

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"

class CCastingRegions;
typedef CComVectorCollection<ICastingRegions,ICastingRegion, IEnumCastingRegions,&IID_IEnumCastingRegions,CollectionIndexType> CastingRegionItemColl;
typedef CPersistentCollection<CCastingRegions, CastingRegionItemColl,CollectionIndexType> PersistentCastingRegions;

/////////////////////////////////////////////////////////////////////////////
// CCastingRegions
class ATL_NO_VTABLE CCastingRegions :
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CCastingRegions,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CCastingRegions, &CLSID_CastingRegions>,
	public ISupportErrorInfo,
   public PersistentCastingRegions,
   public IObjectSafetyImpl<CCastingRegions,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CCastingRegions()
	{
      m_pBridge = nullptr;
      m_Boundary = crbParallelToPier;
	}

   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_CASTING_REGIONS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCastingRegions)
   COM_INTERFACE_ENTRY(ICastingRegions)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

   IGenericBridge* m_pBridge; // weak reference

   CastingRegionBoundary m_Boundary;

protected:
   CComBSTR GetCollectionName() { return CComBSTR("CastingRegions"); }
   CComBSTR GetStoredName()     { return CComBSTR("CastingRegion");  }
   HRESULT DoSaveItem(IStructuredSave2* save,ICastingRegion* item);
   HRESULT DoLoadItem(IStructuredLoad2* load,ICastingRegion* *ppItem);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICastingRegions
public:
   STDMETHOD(putref_Bridge)(/*[in]*/IGenericBridge* pBridge) override;
   STDMETHOD(get_Bridge)(/*[out, retval]*/IGenericBridge** ppBridge) override;
   STDMETHOD(put_Boundary)(/*[in]*/CastingRegionBoundary boundary) override;
   STDMETHOD(get_Boundary)(/*[out, retval]*/CastingRegionBoundary *pBoundary) override;
   STDMETHOD(CreateRegion)(/*[in]*/PierIDType startPierID, /*[in]*/Float64 Xstart, /*[in]*/PierIDType endPierID,/*[in]*/Float64 Xend, /*[in]*/IMaterial* pMaterial, /*[out, retval]*/ICastingRegion** ppRegion) override;
   STDMETHOD(FindRegion)(/*[in]*/Float64 Xb, /*[in]*/SectionBias bias, /*[out]*/IndexType* pIndex,/*[out]*/ICastingRegion** ppRegion) override;
   STDMETHOD(FindRegionEx)(/*[in]*/GirderIDType ssmbrID, /*[in]*/SegmentIndexType segIdx, /*[in]*/Float64 Xs, /*[in]*/SectionBias bias,/*[out]*/IndexType* pIndex,/*[out]*/ICastingRegion** ppRegion) override;
   //STDMETHOD(get_Item)(/*[in]*/CollectionIndexType idx, /*[out, retval]*/ICastingRegion** ppRegion) override;
   //STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType* count) override;
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;
   STDMETHOD(get__EnumCastingRegions)(/*[out, retval]*/IEnumCastingRegions** ppEnumCastingRegions) override;
};
