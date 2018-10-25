///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// PierCollection.h : Declaration of the CPierCollection

#ifndef __PIERCOLLECTION_H_
#define __PIERCOLLECTION_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"
#include "WBFLComCollections.h"

// NOTE: PierCollectionEvents
// PierCollection and SpanCollection are not like normal COM collections.
// Piers and Spans are logically linked together. A pier cannot be added or removed
// without a corrosponding span being added or removed. This is try, because the
// software enforces the constraint that after every edit a valid model must result.
// The BridgeModel fires when Pier/Span pairs are added or removed. This collection
// simply forwards events received from its individual Items.

class CPierCollection;
typedef CComVectorCollection<IPierCollection,IPier,IEnumPiers,&IID_IEnumPiers,PierIndexType> PierColl;
typedef CPersistentCollection<CPierCollection,PierColl,PierIndexType> PersistentPierCollection;

/////////////////////////////////////////////////////////////////////////////
// CPierCollection
class ATL_NO_VTABLE CPierCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPierCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPierCollection, &CLSID_PierCollection>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPierCollection>,
   public IObjectSafetyImpl<CPierCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public PersistentPierCollection,
   public CProxyDPierCollectionEvents< CPierCollection >,
   public IPierEvents
{
public:
   CPierCollection()
	{
      m_bFireEvent = TRUE;
	}

   void FinalRelease();
   void SetBridge(IGenericBridge* bridge);

   // So far the only use for this is private, so it is not
   // part of the COM interface. However, it is written so that
   // it can easily be moved to the COM interface if the need arises
   STDMETHOD(Clone)(IPierCollection* *clone);

   PierIndexType GetPierIndex(IPier* pier);
	HRESULT InsertQuietly(PierIndexType index, IPier* pier);

   void RenameStageReferences(BSTR bstrOldName,BSTR bstrNewName);
   void AddDataForStage(BSTR bstrName);
   void RemoveDataForStage(BSTR bstrName);


DECLARE_REGISTRY_RESOURCEID(IDR_PIERCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPierCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)

   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY_CHAIN(PersistentPierCollection)

   COM_INTERFACE_ENTRY(IPierEvents)

   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPierCollection)
   CONNECTION_POINT_ENTRY(IID_IPierCollectionEvents)
END_CONNECTION_POINT_MAP()

   HRESULT Advise(IPier* pier,DWORD* pdwCookie);
   HRESULT Unadvise(IPier* pier,DWORD dwCookie);

   // CComVectorCollection overrides
   virtual HRESULT OnBeforeAdd( StoredType* pVal);
   virtual HRESULT OnAfterAdd( StoredType* pVal, PierIndexType index);
   virtual HRESULT OnBeforeRemove( StoredType* pVal, PierIndexType index);
   virtual HRESULT OnAfterRemove(PierIndexType index);
   virtual HRESULT OnBeforeReplace( StoredType* pVal, PierIndexType index);
   virtual HRESULT OnAfterReplace( StoredType* pVal, PierIndexType index);

protected:
   CComBSTR GetCollectionName() { return CComBSTR("Piers"); }
   CComBSTR GetStoredName()     { return CComBSTR("Pier");  }
   virtual HRESULT DoSaveItem(IStructuredSave2* save,IPier* item);
   virtual HRESULT DoLoadItem(IStructuredLoad2* load,IPier* *ppItem);

   std::vector<std::pair<long,long> > m_LinkData; // Used only during IStructuredStorage2::Load
   long m_LoadedPierCount; // keeps track of the number of piers that have been loaded

private:
   struct COPYTO
   {
      PierIndexType fromIdx;
      PierIndexType toIdx;
      CComPtr<IPier> originalPier;
   };
   static HRESULT DoCopyTo(CPierCollection* pThis,COPYTO& copy);
   static HRESULT UndoCopyTo(CPierCollection* pThis,COPYTO& copy);

   IGenericBridge* m_pBridge; // Weak reference to parent

   bool m_bFireEvent; // Used with InsertQuietly() to supress the OnPierAdded event

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPierCollection
public:
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
   //STDMETHOD(get_Item)(/*[in]*/ PierIndexType index, /*[out, retval]*/ ISpan* *pVal);
   //STDMETHOD(get_Count)(/*[out,retval]*/ PierIndexType* count);
   STDMETHOD(get_PierIndex)(/*[in]*/ IPier* pier,/*[out,retval]*/PierIndexType* index);
   STDMETHOD(get__EnumPiers)(/*[out,retval]*/IEnumPiers* *enumPiers);
	STDMETHOD(CopyTo)(/*[in]*/PierIndexType fromIdx, /*[in]*/PierIndexType toIdx);

// IStructuredStorage2
public:
   STDMETHOD(Load)(IStructuredLoad2 *pload);

// IPierEvents
public:
	STDMETHOD(OnPierChanged)(IPier * pier)
	{
      Fire_OnPierChanged(pier);
      return S_OK;
	}
};

#endif //__PIERCOLLECTION_H_
