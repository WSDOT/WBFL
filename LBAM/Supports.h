///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2012  Washington State Department of Transportation
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

// Supports.h : Declaration of the CSupports

#ifndef __SUPPORTS_H_
#define __SUPPORTS_H_

#include "resource.h"       // main symbols
#include "SupportCP.h"
#include <WBFLComCollections.h>
#include "LBAMUtils.h"

class CSupports;
typedef CComSegmentCollection< ISupports, ISupport, IEnumSupport, &IID_IEnumSupport,SupportIndexType > SupportCollImpl;
typedef CPersistentCollection<CSupports, SupportCollImpl,SupportIndexType> PersistentSupportCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CSupports
class ATL_NO_VTABLE CSupports : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSupports,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSupports, &CLSID_Supports>,
	public ISupportErrorInfo,
   public PersistentSupportCollImpl,
	public IConnectionPointContainerImpl<CSupports>,
	public CProxyDSupportsEvents< CSupports >,
   public IObjectSafetyImpl<CSupports,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportEvents
{
public:
	CSupports()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SUPPORTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSupports)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentSupportCollImpl)
   COM_INTERFACE_ENTRY(ISupportEvents)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSupports)
CONNECTION_POINT_ENTRY(IID_ISupportsEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// _ISupportEvents
   STDMETHOD(OnSupportChanged)(/*[in]*/ISupport* Support, BSTR stage, ChangeType change);

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

// ISupports
public:
	STDMETHOD(Clone)(/*[out, retval]*/ ISupports** clone);


private:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal)
   {
      CHECK_IN(pVal);
      try
      {
         // set up connection point
         HRESULT hr;
         hr = CrAdvise(pVal->second.m_T, this, IID_ISupportEvents, &(pVal->first));
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(0);
         return E_FAIL;
      }
      return S_OK;
   }

   virtual HRESULT OnAfterAdd( StoredType* pVal, SupportIndexType idx)
   {
      Fire_OnSupportsAdded(pVal->second.m_T, idx);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove( StoredType* pVal, SupportIndexType idx)
   {
      try
      {
         // release connection point
         HRESULT hr;
         hr = CrUnadvise(pVal->second.m_T, this, IID_ISupportEvents, pVal->first);
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(0);
         return E_FAIL;
      }

      Fire_OnSupportsBeforeRemove(pVal->second.m_T, idx);

      return S_OK;
   }

   virtual HRESULT OnAfterRemove( SupportIndexType id)
   {
      return S_OK; 
   }
   virtual HRESULT OnAfterMoveTo( SupportIndexType from, SupportIndexType to)
   {
      Fire_OnSupportsMoveTo (from, to);
      return S_OK;
   }
   virtual HRESULT OnAfterCopyTo( SupportIndexType from, SupportIndexType to)
   {
      Fire_OnSupportsCopyTo(from, to);
      return S_OK;
   }
   virtual HRESULT OnAfterReverse()
   {
      Fire_OnSupportsReverse();
      return S_OK;
   }

public:
   virtual void FinalRelease()
   {
      // free up all of our connectionpoints on destruct
      SupportIDType cnt=0;
      for (iterator it= begin(); it != end(); it++)
      {
         OnBeforeRemove(*it,cnt++);
      }
   }


};

#endif //__SUPPORTS_H_
