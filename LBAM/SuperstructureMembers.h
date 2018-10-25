///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2010  Washington State Department of Transportation
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

// SuperstructureMembers.h : Declaration of the CSuperstructureMembers

#ifndef __SUPERSTRUCTUREMEMBERS_H_
#define __SUPERSTRUCTUREMEMBERS_H_

#include "resource.h"       // main symbols
#include "SuperstructureMemberCP.h"
#include <WBFLComCollections.h>
#include "LBAMUtils.h"

class CSuperstructureMembers;
typedef CComSegmentCollection< ISuperstructureMembers, ISuperstructureMember, IEnumSuperstructureMember, &IID_IEnumSuperstructureMember,CollectionIndexType > SuperstructureMemberCollImpl;
typedef CPersistentCollection<CSuperstructureMembers, SuperstructureMemberCollImpl,CollectionIndexType> PersistentSuperstructureMemberCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CSuperstructureMembers
class ATL_NO_VTABLE CSuperstructureMembers : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSuperstructureMembers,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSuperstructureMembers, &CLSID_SuperstructureMembers>,
	public ISupportErrorInfo,
   public PersistentSuperstructureMemberCollImpl,
	public IConnectionPointContainerImpl<CSuperstructureMembers>,
	public CProxyDSuperstructureMembersEvents< CSuperstructureMembers >,
   public IObjectSafetyImpl<CSuperstructureMembers,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISuperstructureMemberEvents
{
public:
   CSuperstructureMembers():
   m_Offset(0.0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SUPERSTRUCTUREMEMBERS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSuperstructureMembers)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentSuperstructureMemberCollImpl)
   COM_INTERFACE_ENTRY(ISuperstructureMemberEvents)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSuperstructureMembers)
CONNECTION_POINT_ENTRY(IID_ISuperstructureMembersEvents)
END_CONNECTION_POINT_MAP()

// _ISuperstructureMemberEvents
   STDMETHOD(OnSuperstructureMemberChanged)(/*[in]*/ISuperstructureMember* SuperstructureMember, BSTR stage, ChangeType change);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISuperstructureMembers
public:
	STDMETHOD(get_Offset)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Offset)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(Clone)(/*[out, retval]*/ ISuperstructureMembers** clone);

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

private:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal)
   {
      CHECK_IN(pVal);
      try
      {
         // set up connection point
         HRESULT hr;
         hr = CrAdvise(pVal->second.m_T, this, IID_ISuperstructureMemberEvents, &(pVal->first));
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

   virtual HRESULT OnAfterAdd( StoredType* pVal, CollectionIndexType idx)
   {
      Fire_OnSuperstructureMembersAdded(pVal->second.m_T, idx);
      return S_OK;
   }
   virtual HRESULT OnBeforeRemove( StoredType* pVal, CollectionIndexType idx)
   {
      try
      {
         // release connection point
         HRESULT hr;
         hr = CrUnadvise(pVal->second.m_T, this, IID_ISuperstructureMemberEvents, pVal->first);
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(0);
         return E_FAIL;
      }

      Fire_OnSuperstructureMembersBeforeRemove(pVal->second.m_T, idx);

      return S_OK;
   }

   virtual HRESULT OnAfterRemove( CollectionIndexType idx)
   {
      return S_OK; 
   }
   virtual HRESULT OnAfterMoveTo( CollectionIndexType from, CollectionIndexType to)
   {
      Fire_OnSuperstructureMembersMoveTo (from, to);
      return S_OK;
   }
   virtual HRESULT OnAfterCopyTo( CollectionIndexType from, CollectionIndexType to)
   {
      Fire_OnSuperstructureMembersCopyTo(from, to);
      return S_OK;
   }
   virtual HRESULT OnAfterReverse()
   {
      Fire_OnSuperstructureMembersReverse();
      return S_OK;
   }

public:
   virtual void FinalRelease()
   {
      // free up all of our connectionpoints on destruct
      CollectionIndexType cnt=0;
      for (iterator it= begin(); it != end(); it++)
      {
         OnBeforeRemove(*it, cnt++);
      }
   }

protected:
   Float64 m_Offset;
};

#endif //__SUPERSTRUCTUREMEMBERS_H_
