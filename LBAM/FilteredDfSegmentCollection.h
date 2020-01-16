///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2020  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// FilteredDfSegmentCollection.h : Declaration of the CFilteredDfSegmentCollection

#ifndef __FILTEREDDFSEGMENTCOLLECTION_H_
#define __FILTEREDDFSEGMENTCOLLECTION_H_

#include "resource.h"       // main symbols
#include "LBAMUtils.h"
#include <WBFLComCollections.h>

typedef CComVectorCollection<IFilteredDfSegmentCollection, IDistributionFactorSegment, IEnumDistributionFactorSegment, &IID_IEnumDistributionFactorSegment,SegmentIndexType> DfVectorImpl;

/////////////////////////////////////////////////////////////////////////////
// CFilteredDfSegmentCollection
class ATL_NO_VTABLE CFilteredDfSegmentCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFilteredDfSegmentCollection, &CLSID_FilteredDfSegmentCollection>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CFilteredDfSegmentCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public DfVectorImpl
{
public:
	CFilteredDfSegmentCollection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FILTEREDDFSEGMENTCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFilteredDfSegmentCollection)
	COM_INTERFACE_ENTRY(IFilteredDfSegmentCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFilteredDfSegmentCollection
public:

private:
   // have to define virtuals
   virtual HRESULT OnBeforeAdd( StoredType* pVal)
   {
     CHECK_IN(pVal);
     return S_OK;
   }
   virtual HRESULT OnAfterAdd( ItemType* pVal, SegmentIndexType idx)
   {return S_OK;}
   virtual HRESULT OnBeforeRemove( StoredType* pVal, SegmentIndexType idx)
   {return S_OK;}
   virtual HRESULT OnAfterRemove( SegmentIndexType idx)
   {return S_OK;}
};

#endif //__FILTEREDDFSEGMENTCOLLECTION_H_
