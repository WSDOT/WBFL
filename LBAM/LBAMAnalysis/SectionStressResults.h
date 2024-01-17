///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2024  Washington State Department of Transportation
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

// SectionStressResults.h : Declaration of the CSectionStressResults

#ifndef __SECTIONSTRESSRESULTS_H_
#define __SECTIONSTRESSRESULTS_H_

#include "resource.h"       // main symbols
#include "SectionStressResult.h"
#include <WBFLComCollections.h>
#include "LBAMUtils.h"

class CSectionStressResults;
using SSRVectorImpl = CComVectorCollection<ISectionStressResults, ISectionStressResult, IEnumSectionStressResult, &IID_IEnumSectionStressResult, IndexType>;
using PersistentSSRCollImpl = CPersistentCollection<CSectionStressResults, SSRVectorImpl,IndexType>;

/////////////////////////////////////////////////////////////////////////////
// CSectionStressResults
class ATL_NO_VTABLE CSectionStressResults : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSectionStressResults, &CLSID_SectionStressResults>,
   public PersistentSSRCollImpl,
   public IObjectSafetyImpl<CSectionStressResults,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo
{
public:
	CSectionStressResults()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SECTIONSTRESSRESULTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSectionStressResults)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentSSRCollImpl)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISectionStressResults
public:
protected:
	STDMETHOD(Clone)(/*[out, retval]*/ ISectionStressResults** clone) override;

   virtual HRESULT OnBeforeAdd ( SSRVectorImpl::StoredType* pVal)
   {
      CHECK_IN(pVal);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove ( SSRVectorImpl::StoredType* pVal, long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterRemove ( long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterAdd ( SSRVectorImpl::ItemType* pVal, long id)
   {
      return S_OK;
   }

};

#endif //__SECTIONSTRESSRESULTS_H_
