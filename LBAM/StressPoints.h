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

// StressPoints.h : Declaration of the CStressPoints

#ifndef __STRESSPOINTS_H_
#define __STRESSPOINTS_H_

#include "resource.h"       // main symbols

#include "StressPoint.h"
#include <WBFLComCollections.h>
#include "CrossSectionCP.h"
#include "LBAMUtils.h"

class CStressPoints;

typedef CComVectorCollection<IStressPoints, IStressPoint, IEnumStressPoint, &IID_IEnumStressPoint,CollectionIndexType> StressPointVectorImpl;
typedef CPersistentCollection<CStressPoints, StressPointVectorImpl,CollectionIndexType> PersistentSPCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CStressPoints
class ATL_NO_VTABLE CStressPoints : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CStressPoints,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CStressPoints, &CLSID_StressPoints>,
	public ISupportErrorInfo,
   public PersistentSPCollImpl,
	public IStressPointEvents,
	public IConnectionPointContainerImpl<CStressPoints>,
   public IObjectSafetyImpl<CStressPoints,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDStressPointsEvents< CStressPoints >
{
public:
   CStressPoints()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRESSPOINTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStressPoints)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   // Chains in the COM_MAP in the persistence impl
   COM_INTERFACE_ENTRY_CHAIN(PersistentSPCollImpl)
   COM_INTERFACE_ENTRY(IStressPointEvents)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStressPoints)
CONNECTION_POINT_ENTRY(IID_IStressPointsEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStressPoints
   STDMETHOD(Clone)(/*[out]*/IStressPoints** clone);

// _IStressPointEvents
   STDMETHOD(OnStressPointChanged)(/*[in]*/IStressPoint* StressPoint);

private:
// implementation of needed virtual functions
   virtual HRESULT OnBeforeAdd ( StressPointVectorImpl::StoredType* pVal)
   {
      CHECK_IN(pVal);
      try
      {
         // set up connection point
         HRESULT hr;
         hr = CrAdvise(pVal->second.m_T, this, IID_IStressPointEvents, &(pVal->first));
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

   virtual HRESULT OnBeforeRemove ( StressPointVectorImpl::StoredType* pVal, CollectionIndexType idx)
   {
      try
      {
         // release connection point
         HRESULT hr;
         hr = CrUnadvise(pVal->second.m_T, this, IID_IStressPointEvents, pVal->first);
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

   virtual HRESULT OnAfterRemove ( CollectionIndexType idx)
   {
      Fire_OnStressPointsRemoved(idx);
      return S_OK;
   }

   virtual HRESULT OnAfterAdd ( StressPointVectorImpl::StoredType* pVal, CollectionIndexType idx)
   {
      Fire_OnStressPointsAdded(idx);
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
};

#endif //__StressPoints_H_
