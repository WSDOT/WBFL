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

// FilteredSuperstructureMemberCollection.h : Declaration of the CFilteredSuperstructureMemberCollection

#ifndef __FILTEREDSUPERSTRUCTUREMEMBERCOLLECTION_H_
#define __FILTEREDSUPERSTRUCTUREMEMBERCOLLECTION_H_

#include "WBFLComCollections.h"
#include "resource.h"       // main symbols

typedef CComVectorCollection<IFilteredSuperstructureMemberCollection, ISuperstructureMember, IEnumSuperstructureMember, &IID_IEnumSuperstructureMember, CollectionIndexType> SSMBRVectorImpl;

/////////////////////////////////////////////////////////////////////////////
// CFilteredSuperstructureMemberCollection
class ATL_NO_VTABLE CFilteredSuperstructureMemberCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CFilteredSuperstructureMemberCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CFilteredSuperstructureMemberCollection, &CLSID_FilteredSuperstructureMemberCollection>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CFilteredSuperstructureMemberCollection>,
	public SSMBRVectorImpl
{
public:
	CFilteredSuperstructureMemberCollection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FILTEREDSUPERSTRUCTUREMEMBERCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFilteredSuperstructureMemberCollection)
	COM_INTERFACE_ENTRY(IFilteredSuperstructureMemberCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CFilteredSuperstructureMemberCollection)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFilteredSuperstructureMemberCollection
public:

private:
   // have to define virtuals
   virtual HRESULT OnBeforeAdd( StoredType* pVal)
   {return S_OK;}
   virtual HRESULT OnAfterAdd( ItemType* pVal, long id)
   {return S_OK;}
   virtual HRESULT OnBeforeRemove( StoredType* pVal, long id)
   {return S_OK;}
   virtual HRESULT OnAfterRemove( long id)
   {return S_OK;}
};

#endif //__FILTEREDSUPERSTRUCTUREMEMBERCOLLECTION_H_
