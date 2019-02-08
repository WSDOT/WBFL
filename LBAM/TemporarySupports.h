///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2019  Washington State Department of Transportation
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

// TemporarySupports.h : Declaration of the CTemporarySupports

#ifndef __TEMPORARYSUPPORTS_H_
#define __TEMPORARYSUPPORTS_H_

#include "resource.h"       // main symbols
#include <WBFLComCollections.h>
#include "SupportCP.h"
#include "LBAMUtils.h"

class CTemporarySupports;
typedef CComVectorCollection<ITemporarySupports, ITemporarySupport, IEnumTemporarySupport, &IID_IEnumTemporarySupport,SupportIndexType> TemporarySupportVectorImpl;
typedef CPersistentCollection<CTemporarySupports, TemporarySupportVectorImpl,SupportIndexType> PersistentTSCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CTemporarySupports
class ATL_NO_VTABLE CTemporarySupports : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CTemporarySupports,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CTemporarySupports, &CLSID_TemporarySupports>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CTemporarySupports>,
   public PersistentTSCollImpl,
	public ITemporarySupportEvents,
   public IObjectSafetyImpl<CTemporarySupports,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDTemporarySupportsEvents< CTemporarySupports >
{
public:
	CTemporarySupports()
	{
#if defined _DEBUG
      m_bTestLocations = true;
#endif
	}

	~CTemporarySupports()
	{;}

#if defined _DEBUG
   bool m_bTestLocations; // when getting temporary supports from CModel::get_TemporarySupports, we put all temporary supports into the same container
   // temporary support locations are relative to the start of the span where they occur. Our OnBeforeAdd method tests for duplicate locations.
   // This test causes bad asserts to fire when this is a container of all temp supports. CModel::get_TemporarySupports sets m_bTestLocations to false
   // so that these bad asserts don't fire;
#endif

DECLARE_REGISTRY_RESOURCEID(IDR_TEMPORARYSUPPORTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTemporarySupports)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   // Chains in the COM_MAP in the persistence impl
   COM_INTERFACE_ENTRY_CHAIN(PersistentTSCollImpl)
   COM_INTERFACE_ENTRY(ITemporarySupportEvents)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTemporarySupports)
CONNECTION_POINT_ENTRY(IID_ITemporarySupportsEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ITemporarySupports
   STDMETHOD(Clone)(/*[out]*/ITemporarySupports** clone) override;
   STDMETHOD(Find)(SupportIDType tsID,ITemporarySupport** ppTS) override;

// ITemporarySupportEvents
   STDMETHOD(OnTemporarySupportChanged)(/*[in]*/ITemporarySupport* TemporarySupport, BSTR stage, /*[in]*/ChangeType change) override;

public:
// implementation of needed virtual functions
   virtual HRESULT OnBeforeAdd(TemporarySupportVectorImpl::StoredType* pVal)
   {
      CHECK_IN(pVal);

#if defined _DEBUG
      // make sure we aren't adding a temporary support at the same location
      // where one was previously defined
      if (m_bTestLocations)
      {
         Float64 location;
         pVal->second.m_T->get_Location(&location);

         for (iterator it = begin(); it != end(); it++)
         {
            CComPtr<ITemporarySupport> ts = it->second;
            Float64 loc;
            ts->get_Location(&loc);
            ATLASSERT(!IsEqual(loc, location));
         }
      }
#endif

      try
      {
         // set up connection point
         HRESULT hr;
         hr = CrAdvise(pVal->second.m_T, this, IID_ITemporarySupportEvents, &(pVal->first));
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(false);
         return E_FAIL;
      }

      return S_OK;
   }

   virtual HRESULT OnBeforeRemove ( TemporarySupportVectorImpl::StoredType* pVal, SupportIndexType idx)
   {
      try
      {
         // release connection point
         HRESULT hr;
         hr = CrUnadvise(pVal->second.m_T, this, IID_ITemporarySupportEvents, pVal->first);
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(false);
         return E_FAIL;
      }

      Fire_OnTemporarySupportsBeforeRemove(pVal->second.m_T, idx);

      return S_OK;
   }

   virtual HRESULT OnAfterRemove ( SupportIndexType idx) 
   {
      return S_OK;
   }

   virtual HRESULT OnAfterAdd ( TemporarySupportVectorImpl::StoredType* pVal, SupportIndexType idx)
   {
      Fire_OnTemporarySupportsAdded(pVal->second.m_T, idx);
      return S_OK;
   }

public:
   virtual void FinalRelease()
   {
      // free up all of our connectionpoints on destruct
      SupportIndexType cnt = 0;
      for (iterator it= begin(); it != end(); it++)
      {
         OnBeforeRemove(*it, cnt);
         cnt++;
      }
   }

};

#endif //__TEMPORARYSUPPORTS_H_
