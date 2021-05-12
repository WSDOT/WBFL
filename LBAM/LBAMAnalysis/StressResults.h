///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2021  Washington State Department of Transportation
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

// StressResults.h : Declaration of the CStressResults

#ifndef __STRESSRESULTS_H_
#define __STRESSRESULTS_H_

#include "resource.h"       // main symbols

#include "StressResult.h"
#include "WbflComCollections.h"
#include "LBAMUtils.h"

class CStressResults;
typedef CComVectorCollection<IStressResults, IStressResult, IEnumStressResult, &IID_IEnumStressResult,CollectionIndexType> SRVectorImpl;
typedef CPersistentCollection<CStressResults, SRVectorImpl,CollectionIndexType> PersistentSRCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CStressResults
class ATL_NO_VTABLE CStressResults : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStressResults, &CLSID_StressResults>,
   public PersistentSRCollImpl,
   public IObjectSafetyImpl<CStressResults,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo
{
public:
	CStressResults()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRESSRESULTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStressResults)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentSRCollImpl)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStressResults
public:
	STDMETHOD(Clone)(/*[out, retval]*/ IStressResults** clone) override;

protected:

   virtual HRESULT OnBeforeAdd ( SRVectorImpl::StoredType* pVal)
   {
      CHECK_IN(pVal);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove ( SRVectorImpl::StoredType* pVal, long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterRemove ( long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterAdd ( SRVectorImpl::ItemType* pVal, long id)
   {
      return S_OK;
   }


};

#endif //__STRESSRESULTS_H_
