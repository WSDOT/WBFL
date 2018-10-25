///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

// TemporaryPierItemCollection.h : Declaration of the CTemporaryPierItemCollection

#ifndef __TEMPORARYPIERITEMCOLLECTION_H_
#define __TEMPORARYPIERITEMCOLLECTION_H_

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"
#include "GenericBridgeCP.h"

class CTemporaryPierItemCollection;
typedef CComLongKeyedCollection<ITemporaryPierItemCollection, ITemporaryPierItem, IEnumTemporaryPierItems, &IID_IEnumTemporaryPierItems,CollectionIndexType> TPICollImpl;
typedef CPersistentCollection<CTemporaryPierItemCollection, TPICollImpl,CollectionIndexType> PersistentTPICollImpl;

/////////////////////////////////////////////////////////////////////////////
// CTemporaryPierItemCollection
class ATL_NO_VTABLE CTemporaryPierItemCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CTemporaryPierItemCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CTemporaryPierItemCollection, &CLSID_TemporaryPierItemCollection>,
	public ISupportErrorInfo,
   public PersistentTPICollImpl,
   public IConnectionPointContainerImpl<CTemporaryPierItemCollection>,
   public CProxyDTemporaryPierItemCollectionEvents< CTemporaryPierItemCollection >,
   public ITemporaryPierItemEvents,
   public IObjectSafetyImpl<CTemporaryPierItemCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CTemporaryPierItemCollection()
	{
	}

   void FinalRelease();

   STDMETHOD(Clone)(ITemporaryPierItemCollection* *clone);

   void SetBridge(IGenericBridge* pBridge);

DECLARE_REGISTRY_RESOURCEID(IDR_TEMPORARYPIERITEMCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTemporaryPierItemCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentTPICollImpl)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ITemporaryPierItemEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTemporaryPierItemCollection)
   CONNECTION_POINT_ENTRY(IID_ITemporaryPierItemCollectionEvents)
END_CONNECTION_POINT_MAP()

protected:

   // Container overrides
   virtual HRESULT OnAfterAdd(StoredType* pVal);
   virtual HRESULT OnBeforeRemove(StoredType* pVal);
   virtual HRESULT OnAfterRemove(long id);

   virtual CComBSTR GetCollectionName() { return CComBSTR("TemporaryPiers"); }
   virtual CComBSTR GetStoredName() { return CComBSTR("TemporaryPier"); }
   virtual HRESULT DoSaveItem(IStructuredSave2* save,ITemporaryPierItem* item);
   virtual HRESULT DoLoadItem(IStructuredLoad2* load,ITemporaryPierItem* *ppItem);

private:
   HRESULT Advise(ITemporaryPierItem* tpi,DWORD* pdwCookie);
   HRESULT Unadvise(ITemporaryPierItem* tpi,DWORD dwCookie);

   IGenericBridge* m_pBridge; // Weak reference to bridge

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITemporaryPierItemCollection
public:
//   STDMETHOD(get_Item)(/*[in]*/PierIndexType idx, /*[out, retval]*/ ITemporaryPierItem** pVal);
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval); 
//   STDMETHOD(get_Count)(/*[out, retval]*/ PierIndexType *pVal);
   STDMETHOD(get__EnumTemporaryPierItems)(/*[out, retval]*/ IEnumTemporaryPierItems* *pVal);
   STDMETHOD(Add)(/*[in]*/ long id,/*[in]*/ Float64 location,/*[in]*/ BSTR bstrRemovalStage);
   STDMETHOD(RemoveByIndex)(/*[in]*/CollectionIndexType index);
   STDMETHOD(RemoveByID)(/*[in]*/long id);
   STDMETHOD(Clear)();
//   STDMETHOD(Find)(/*[in]*/ long id,/*[out,retval]*/ ITemporaryPierItem** pVal);

// ITemporaryPierItemEvents
public:
	STDMETHOD(OnTemporaryPierChanged)(long id)
	{
      CComPtr<ITemporaryPierItem> item;
      Find(id,&item);
      Fire_OnTemporaryPierItemChanged(item);
		return S_OK;
	}
	STDMETHOD(OnTemporaryPierAdded)(PierIndexType index)
	{
      Fire_OnTemporaryPierItemAdded(index);
      return S_OK;
	}
	STDMETHOD(OnTemporaryPierRemoved)(PierIndexType index)
	{
      Fire_OnTemporaryPierItemRemoved(index);
      return S_OK;
	}
};

#endif //__TEMPORARYPIERITEMCOLLECTION_H_
