///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright � 1999-2025  Washington State Department of Transportation
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

// Axles.h : Declaration of the CAxles

#ifndef __AXLES_H_
#define __AXLES_H_

#include "resource.h"       // main symbols
#include "LoadingCP.h"

#include "ComCollections.h"
#include "LoadingUtils.h"

class CAxles;
using AxleCollImpl = CComSegmentCollection< ldIAxles, ldIAxle, ldIEnumAxle, &IID_ldIEnumAxle, AxleIndexType >;
using PersistentAxleCollImpl = CPersistentCollection<CAxles, AxleCollImpl,AxleIndexType>;

/////////////////////////////////////////////////////////////////////////////
// CAxles
class ATL_NO_VTABLE CAxles : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CAxles,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CAxles, &CLSID_ldAxles>,
	public ISupportErrorInfo,
   public PersistentAxleCollImpl,
	public IConnectionPointContainerImpl<CAxles>,
	public CProxyDAxlesEvents< CAxles >,
	public ldIAxleEvents
{
public:
	CAxles()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AXLES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAxles)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentAxleCollImpl)
   COM_INTERFACE_ENTRY(ldIAxleEvents)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAxles)
CONNECTION_POINT_ENTRY(IID_ldIAxlesEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ldIAxleEvents
   STDMETHOD(OnAxleChanged)(/*[in]*/ldIAxle* Axle) override;

// ldIAxles
public:
	STDMETHOD(Clone)(/*[out, retval]*/ ldIAxles** clone) override;


private:
   // implementations of virtual functions for collection
   HRESULT OnBeforeAdd( StoredType* pVal)
   {
      CHECK_IN(pVal);
      try
      {
         // set up connection point
         HRESULT hr;
         hr = CrAdvise(pVal->second.m_T, this, IID_ldIAxleEvents, &(pVal->first));
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(false);
         return E_FAIL;
      }
      return S_OK;
   };

   HRESULT OnAfterAdd( StoredType* pVal, AxleIndexType position)
   {
      Fire_OnAxlesAdded(pVal->second.m_T, position);
      return S_OK;
   };

   HRESULT OnBeforeRemove( StoredType* pVal, AxleIndexType position)
   {
      try
      {
         // release connection point
         HRESULT hr;
         hr = CrUnadvise(pVal->second.m_T, this, IID_ldIAxleEvents, pVal->first);
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(false);
         return E_FAIL;
      }

      Fire_OnAxlesBeforeRemove(pVal->second.m_T, position);

      return S_OK;
   }

   HRESULT OnAfterRemove( AxleIndexType position)
   {
      return S_OK; 
   }

   HRESULT OnAfterMoveTo( AxleIndexType from, AxleIndexType to)
   {
      Fire_OnAxlesMoveTo (from, to);
      return S_OK;
   }
   HRESULT OnAfterCopyTo( AxleIndexType from, AxleIndexType to)
   {
      Fire_OnAxlesCopyTo(from, to);
      return S_OK;
   }
   HRESULT OnAfterReverse()
   {
      Fire_OnAxlesReverse();
      return S_OK;
   }

public:
   void FinalRelease()
   {
      // free up all of our connectionpoints on destruct
      IndexType cnt = 0;
      for (iterator it= begin(); it != end(); it++)
      {
         OnBeforeRemove(*it, cnt++);
      }
   }
};

#endif //__AXLES_H_
