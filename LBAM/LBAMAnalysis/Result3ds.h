///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// Result3Ds.h : Declaration of the CResult3Ds

#ifndef __RESULT3DS_H_
#define __RESULT3DS_H_

#include "resource.h"       // main symbols

#include "Result3D.h"
#include <WBFLComCollections.h>
#include "LBAMUtils.h"

class CResult3Ds;
typedef CComVectorCollection<IResult3Ds, IResult3D, IEnumResult3D, &IID_IEnumResult3D,CollectionIndexType> FRVectorImpl;
typedef CPersistentCollection<CResult3Ds, FRVectorImpl,CollectionIndexType> PersistentFRCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CResult3Ds
class ATL_NO_VTABLE CResult3Ds : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CResult3Ds,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CResult3Ds, &CLSID_Result3Ds>,
   public PersistentFRCollImpl,
   public IObjectSafetyImpl<CResult3Ds,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo
{
public:
	CResult3Ds()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RESULT3DS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CResult3Ds)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentFRCollImpl)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IResult3Ds
public:
	STDMETHOD(Clone)(/*[out, retval]*/ IResult3Ds** clone);

   virtual HRESULT OnBeforeAdd ( FRVectorImpl::StoredType* pVal)
   {
      CHECK_IN(pVal);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove ( FRVectorImpl::StoredType* pVal, long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterRemove ( long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterAdd ( FRVectorImpl::ItemType* pVal, long id)
   {
      return S_OK;
   }

};

#endif //__Result3DS_H_
