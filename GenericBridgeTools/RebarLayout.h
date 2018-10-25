///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2014  Washington State Department of Transportation
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

// RebarLayout.h : Declaration of the CRebarLayout

#ifndef __RebarLayout_H_
#define __RebarLayout_H_

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"
#include "GenericBridgeToolsCP.h"

class CRebarLayout;
typedef CComVectorCollection<IRebarLayout,IRebarLayoutItem,IEnumRebarLayoutItems,&IID_IEnumRebarLayoutItems,CollectionIndexType> ItemColl;
typedef CPersistentCollection<CRebarLayout,ItemColl,CollectionIndexType> PersistentRebarLayout;

/////////////////////////////////////////////////////////////////////////////
// CRebarLayout
class ATL_NO_VTABLE CRebarLayout : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CRebarLayout,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CRebarLayout, &CLSID_RebarLayout>,
	public ISupportErrorInfo,
   public PersistentRebarLayout,
   public IObjectSafetyImpl<CRebarLayout,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CRebarLayout()
	{
	}

   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_REBARLAYOUT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRebarLayout)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)

   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

protected:
   CComBSTR GetCollectionName() { return CComBSTR("RebarLayout"); }
   CComBSTR GetStoredName()     { return CComBSTR("RebarLayoutItems");  }
   virtual HRESULT DoSaveItem(IStructuredSave2* save,IRebarPattern* item);
   virtual HRESULT DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRebarLayout
public:
   STDMETHOD(CreateRebarSection)(/*[in]*/ Float64 cutLocation,/*[out,retval]*/IRebarSection** section);
//   STDMETHOD(get_Item)(/*[in]*/long idx,/*[out,retval]*/IRebarLayoutItem** rli);
//	STDMETHOD(get_Count)(/*[out,retval]*/ long* count);
//	STDMETHOD(Add)(/*[in]*/IRebarLayoutItem* rli);
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
   STDMETHOD(get__EnumRebarLayoutItems)(/*[out,retval]*/IEnumRebarLayoutItems** enumRebarLayoutItems);
};

#endif //__RebarLayout_H_
