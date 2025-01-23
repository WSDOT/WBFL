///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

// FilteredSegmentCollection.h : Declaration of the CFilteredSegmentCollection

#ifndef __FILTEREDSEGMENTCOLLECTION_H_
#define __FILTEREDSEGMENTCOLLECTION_H_

#include "WBFLComCollections.h"
#include "resource.h"       // main symbols

using VectorImpl = CComVectorCollection<IFilteredSegmentCollection, ISegment, IEnumSegment, &IID_IEnumSegment,IndexType>;

/////////////////////////////////////////////////////////////////////////////
// CFilteredSegmentCollection
class ATL_NO_VTABLE CFilteredSegmentCollection : 
//	public CComObjectRootEx<CComSingleThreadModel>,
   public CComRefCountTracer<CFilteredSegmentCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CFilteredSegmentCollection, &CLSID_FilteredSegmentCollection>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CFilteredSegmentCollection>,
	public VectorImpl
{
public:
	CFilteredSegmentCollection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FILTEREDSEGMENTCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFilteredSegmentCollection)
	COM_INTERFACE_ENTRY(IFilteredSegmentCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CFilteredSegmentCollection)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFilteredSegmentCollection
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

#endif //__FILTEREDSEGMENTCOLLECTION_H_
