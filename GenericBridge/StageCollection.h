///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// StageCollection.h : Declaration of the CStageCollection

#ifndef __STAGECOLLECTION_H_
#define __STAGECOLLECTION_H_

#include "resource.h"       // main symbols
#include <WBFLComCollections.h>
#include "Stage.h"
#include "GenericBridgeCP.h"

class CStageCollection;
typedef CComSegmentCollection<IStageCollection,IStage, IEnumStages,&IID_IEnumStages, CollectionIndexType> StageCollImpl;
typedef CPersistentCollection<CStageCollection, StageCollImpl, CollectionIndexType> PersistentStageCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CStageCollection
class ATL_NO_VTABLE CStageCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStageCollection, &CLSID_StageCollection>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CStageCollection>,
   public PersistentStageCollImpl,
   public CProxyDStageCollectionEvents< CStageCollection >,
   public IObjectSafetyImpl<CStageCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IStageEvents
{
public:
	CStageCollection()
	{
	}

   void FinalRelease();

   void SetBridge(IGenericBridge* pBridge);

   STDMETHOD(Clone)(IStageCollection* *clone);

   CComBSTR m_bstrLastStageRemoved; // See note in OnBeforeRemove

DECLARE_REGISTRY_RESOURCEID(IDR_STAGECOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStageCollection)
	COM_INTERFACE_ENTRY(IStageCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY_CHAIN(PersistentStageCollImpl)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IStageEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStageCollection)
   CONNECTION_POINT_ENTRY(IID_IStageCollectionEvents)
END_CONNECTION_POINT_MAP()

   // Virtual over-rides for Segment Collection
   virtual HRESULT OnAfterAdd( StoredType* pVal, CollectionIndexType index);
   virtual HRESULT OnBeforeRemove( StoredType* pVal, CollectionIndexType index);
   virtual HRESULT OnAfterRemove(CollectionIndexType index);
   virtual HRESULT OnAfterMoveTo( CollectionIndexType from, CollectionIndexType to);
   virtual HRESULT OnAfterCopyTo( CollectionIndexType from, CollectionIndexType to);
   virtual HRESULT OnAfterReverse();

   HRESULT Advise(IStage* stage,DWORD* pdwCookie);
   HRESULT Unadvise(IStage* stage,DWORD dwCookie);

   IGenericBridge* m_pBridge; // weak reference to bridge

protected:
   CComBSTR GetCollectionName() { return CComBSTR("Stages"); }
   CComBSTR GetStoredName()     { return CComBSTR("Stage");  }
   virtual HRESULT DoSaveItem(IStructuredSave2* save,IStage* item);
   virtual HRESULT DoLoadItem(IStructuredLoad2* load,IStage* *ppItem);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStageCollection
public:
   STDMETHOD(Find)(/*[in]*/ BSTR name,/*[out,retval]*/ IStage* *stage);
	STDMETHOD(RemoveByName)(/*[in]*/ BSTR name);
	STDMETHOD(RemoveByIndex)(/*[in]*/ CollectionIndexType index);
//	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
//	STDMETHOD(get_Item)(/*[out, retval]*/ IStage* *pVal);
//	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal);
   STDMETHOD(CreateStage)(/*[in]*/ BSTR name,/*[in]*/ BSTR description);
   STDMETHOD(CreateStageAt)(/*[in]*/ BSTR name,/*[in]*/ BSTR description,/*[in]*/ CollectionIndexType pos);
   STDMETHOD(MoveStage)(/*[in]*/ CollectionIndexType fromPos,/*[in]*/ CollectionIndexType toPos);
	STDMETHOD(get__EnumStages)(/*[out, retval]*/ IEnumStages* *enumStages);
   STDMETHOD(Compare)(/*[in]*/ BSTR name1, /*[in]*/ BSTR name2,/*[out,retval]*/ long* cmp);

// IStageEvents
public:
   STDMETHOD(OnNameChanged)(/*[in]*/ BSTR bstrOldName,/*[in]*/ IStage* stage)
   {
      Fire_OnStageRenamed(bstrOldName,stage);
      return S_OK;
   }

   STDMETHOD(OnDescriptionChanged)(/*[in]*/IStage* stage)
   {
      Fire_OnStageDescriptionChanged(stage);
      return S_OK;
   }
};

#endif //__STAGECOLLECTION_H_
