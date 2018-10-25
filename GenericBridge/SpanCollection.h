///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// SpanCollection.h : Declaration of the CSpanCollection

#ifndef __SPANCOLLECTION_H_
#define __SPANCOLLECTION_H_

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"
#include "GenericBridgeCP.h"

class CSpanCollection;
typedef CComVectorCollection<ISpanCollection,ISpan,IEnumSpans,&IID_IEnumSpans,SpanIndexType> SpanColl;
typedef CPersistentCollection<CSpanCollection,SpanColl,SpanIndexType> PersistentSpanCollection;

/////////////////////////////////////////////////////////////////////////////
// CSpanCollection
class ATL_NO_VTABLE CSpanCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSpanCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSpanCollection, &CLSID_SpanCollection>,
	public ISupportErrorInfo,
   public PersistentSpanCollection,
   public CProxyDSpanCollectionEvents< CSpanCollection >,
   public IConnectionPointContainerImpl<CSpanCollection>,
   public ISpanEvents,
   public IObjectSafetyImpl<CSpanCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CSpanCollection()
	{
      m_pBridge = 0;
	}

   void FinalRelease();
   void SetBridge(IGenericBridge* bridge);

   STDMETHOD(Clone)(ISpanCollection* *clone);

DECLARE_REGISTRY_RESOURCEID(IDR_SPANCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSpanCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentSpanCollection)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISpanEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSpanCollection)
   CONNECTION_POINT_ENTRY(IID_ISpanCollectionEvents)
END_CONNECTION_POINT_MAP()

private:
   HRESULT Advise(ISpan* pier,DWORD* pdwCookie);
   HRESULT Unadvise(ISpan* pier,DWORD dwCookie);

   // CComVectorCollection overrides
   virtual HRESULT OnBeforeAdd( StoredType* pVal);
   virtual HRESULT OnAfterAdd(StoredType* pVal, SpanIndexType index);
   virtual HRESULT OnBeforeRemove( StoredType* pVal, SpanIndexType index);

   SpanIndexType GetSpanIndex(ISpan* span);

   IGenericBridge* m_pBridge; // weak referece to parent

protected:
   CComBSTR GetCollectionName() { return CComBSTR("Spans"); }
   CComBSTR GetStoredName()     { return CComBSTR("Span");  }
   virtual HRESULT DoSaveItem(IStructuredSave2* save,ISpan* item);
   virtual HRESULT DoLoadItem(IStructuredLoad2* load,ISpan* *ppItem);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISpanCollection
public:
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
   //STDMETHOD(get_Item)(/*[in]*/ long index, /*[out, retval]*/ ISpan* *pVal);
   //STDMETHOD(get_Count)(/*[out,retval]*/ long* count);
   STDMETHOD(get_SpanIndex)(/*[in]*/ISpan* span,/*[out,retval]*/SpanIndexType* index);
   STDMETHOD(get__EnumSpans)(/*[out,retval]*/IEnumSpans* *enumSpans);

public :

// ISpanEvents
	STDMETHOD(OnSpanChanged)(ISpan * span)
	{
      Fire_OnSpanChanged(span);
      return S_OK;
	}
};

#endif //__SPANCOLLECTION_H_
