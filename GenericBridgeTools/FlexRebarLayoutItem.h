///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// FlexRebarLayoutItem.h : Declaration of the CFlexRebarLayoutItem

#ifndef __FlexRebarLayoutItem_H_
#define __FlexRebarLayoutItem_H_

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"
#include "GenericBridgeToolsCP.h"

class CFlexRebarLayoutItem;
typedef CComVectorCollection<IFlexRebarLayoutItem,IRebarPattern,IEnumRebarPatterns,&IID_IEnumRebarPatterns,CollectionIndexType> PtrnColl;
typedef CPersistentCollection<CFlexRebarLayoutItem,PtrnColl,CollectionIndexType> PersistentFlexRebarLayoutItem;

/////////////////////////////////////////////////////////////////////////////
// CFlexRebarLayoutItem
class ATL_NO_VTABLE CFlexRebarLayoutItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CFlexRebarLayoutItem,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CFlexRebarLayoutItem, &CLSID_FlexRebarLayoutItem>,
	public ISupportErrorInfo,
   public PersistentFlexRebarLayoutItem,
   public IObjectSafetyImpl<CFlexRebarLayoutItem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CFlexRebarLayoutItem()
	{
      m_pGirder = 0;
	}

   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_FLEXREBARLAYOUTITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFlexRebarLayoutItem)
   COM_INTERFACE_ENTRY(IFlexRebarLayoutItem)
   COM_INTERFACE_ENTRY(IRebarLayoutItem)

	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

protected:
   CComBSTR GetCollectionName() { return CComBSTR("RebarPatterns"); }
   CComBSTR GetStoredName()     { return CComBSTR("RebarPattern");  }
   virtual HRESULT DoSaveItem(IStructuredSave2* save,IRebarPattern* item);
   virtual HRESULT DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem);

   LayoutPosition m_Position;
   Float64 m_Factor;
   IPrecastGirder* m_pGirder; // weak reference

   static HRESULT PutPosition(CFlexRebarLayoutItem* pThis,LayoutPosition lp);
   static HRESULT PutLengthFactor(CFlexRebarLayoutItem* pThis,Float64 lf);
   static HRESULT PutRefGirder(CFlexRebarLayoutItem* pThis,IPrecastGirder* girder);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFlexRebarLayoutItem
public:
   STDMETHOD(ContainsLocation)(/*[in]*/ Float64 distFromGdrStart,/*[out,retval]*/ VARIANT_BOOL* bResult);
	STDMETHOD(get_Start)(/*[out,retval]*/Float64* start);
	STDMETHOD(get_Length)(/*[out,retval]*/Float64* length);
//	STDMETHOD(get_Count)(/*[out,retval]*/long* count);
//	STDMETHOD(get_Item)(/*[in]*/ long idx,/*[out,retval]*/IRebarPattern** pattern);
	STDMETHOD(AddRebarPattern)(/*[in]*/IRebarPattern* pattern);
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
   STDMETHOD(get__EnumRebarPatterns)(/*[out,retval]*/IEnumRebarPatterns** enumRebarPatterns);
	STDMETHOD(get_Position)(/*[out,retval]*/ LayoutPosition* lp);
	STDMETHOD(put_Position)(/*[in]*/ LayoutPosition lp);
	STDMETHOD(get_LengthFactor)(/*[out,retval]*/ Float64* lf);
	STDMETHOD(put_LengthFactor)(/*[in]*/ Float64 lf);
	STDMETHOD(putref_Girder)(/*[in]*/IPrecastGirder* girder);
};

#endif //__FlexRebarLayoutItem_H_
