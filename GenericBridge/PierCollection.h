///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include "WBFLComCollections.h"

#include "BridgePier.h"

// NOTE: PierCollectionEvents
// PierCollection and SpanCollection are not like normal COM collections.
// Piers and Spans are logically linked together. A pier cannot be added or removed
// without a corresponding span being added or removed. This is try, because the
// software enforces the constraint that after every edit a valid model must result.
// The BridgeModel fires when Pier/Span pairs are added or removed. This collection
// simply forwards events received from its individual Items.

class CPierCollection;
typedef CComVectorCollection<IPierCollection,IBridgePier,IEnumPiers,&IID_IEnumPiers,PierIndexType> PierColl;
typedef CPersistentCollection<CPierCollection,PierColl,PierIndexType> PersistentPierCollection;

/////////////////////////////////////////////////////////////////////////////
// CPierCollection
class ATL_NO_VTABLE CPierCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPierCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPierCollection, &CLSID_PierCollection>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPierCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public PersistentPierCollection
{
public:
   CPierCollection()
	{
      CComObject<CBridgePier>* pTestPier;
      CComObject<CBridgePier>::CreateInstance(&pTestPier);
      m_TestPier = pTestPier;
	}

   void FinalRelease();

   PierIndexType GetPierIndex(IBridgePier* pier);
	HRESULT InsertQuietly(PierIndexType index, IBridgePier* pier);


DECLARE_REGISTRY_RESOURCEID(IDR_PIERCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPierCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentPierCollection)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

protected:
   CComBSTR GetCollectionName() { return CComBSTR("Piers"); }
   CComBSTR GetStoredName()     { return CComBSTR("Pier");  }

private:
   CComPtr<IBridgePier> m_TestPier; // used for searches
   IGenericBridge* m_pBridge; // Weak reference to parent

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPierCollection
public:
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;  
   //STDMETHOD(get_Item)(/*[in]*/ PierIndexType index, /*[out, retval]*/ ISpan* *pVal) override;
   //STDMETHOD(get_Count)(/*[out,retval]*/ PierIndexType* count) override;
   STDMETHOD(get_PierIndex)(/*[in]*/ IBridgePier* pier,/*[out,retval]*/PierIndexType* index) override;
   STDMETHOD(get__EnumPiers)(/*[out,retval]*/IEnumPiers* *enumPiers) override;
   STDMETHOD(FindPier)(/*[in]*/Float64 station,/*[out,retval]*/IBridgePier** ppPier) override;
   STDMETHOD(FindPierByID)(/*[in]*/PierIDType pierID, /*[out, retval]*/IBridgePier** ppPier) override;

// IStructuredStorage2
public:
   STDMETHOD(Load)(IStructuredLoad2 *pload) override;
};

#endif //__PIERCOLLECTION_H_
