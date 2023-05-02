///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2023  Washington State Department of Transportation
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

// SectionResult3Ds.h : Declaration of the CSectionResult3Ds

#ifndef __SECTIONRESULT3DS_H_
#define __SECTIONRESULT3DS_H_

#include "resource.h"       // main symbols

#include "SectionResult3D.h"
#include <WBFLComCollections.h>
#include "LBAMUtils.h"

class CSectionResult3Ds;

using SFRVectorImpl = CComVectorCollection<ISectionResult3Ds, ISectionResult3D, IEnumSectionResult3D, &IID_IEnumSectionResult3D, CollectionIndexType>;
using PersistentSFRCollImpl = CPersistentCollection<CSectionResult3Ds, SFRVectorImpl,CollectionIndexType>;

/////////////////////////////////////////////////////////////////////////////
// CSectionResult3Ds
class ATL_NO_VTABLE CSectionResult3Ds : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSectionResult3Ds,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSectionResult3Ds, &CLSID_SectionResult3Ds>,
   public PersistentSFRCollImpl,
   public IObjectSafetyImpl<CSectionResult3Ds,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo
{
public:
	CSectionResult3Ds()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SECTIONRESULT3DS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSectionResult3Ds)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentSFRCollImpl)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISectionResult3Ds
public:
	STDMETHOD(Clone)(/*[out, retval]*/ ISectionResult3Ds** clone) override;

   virtual HRESULT OnBeforeAdd ( SFRVectorImpl::StoredType* pVal)
   {
      CHECK_IN(pVal);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove ( SFRVectorImpl::StoredType* pVal, long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterRemove ( long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterAdd ( SFRVectorImpl::ItemType* pVal, long id)
   {
      return S_OK;
   }

};

#endif //__SECTIONRESULT3DS_H_
