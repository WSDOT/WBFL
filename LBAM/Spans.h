///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2025  Washington State Department of Transportation
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

// Spans.h : Declaration of the CSpans

#ifndef __SPANS_H_
#define __SPANS_H_

#include "resource.h"       // main symbols
#include "SpanCP.h" 
#include <WBFLComCollections.h>
#include "LBAMUtils.h"

class CSpans;
using SpanCollImpl = CComSegmentCollection< ISpans, ISpan, IEnumSpan, &IID_IEnumSpan, SpanIndexType>;
using PersistentSpanCollImpl = CPersistentCollection<CSpans, SpanCollImpl,SpanIndexType>;

/////////////////////////////////////////////////////////////////////////////
// CSpans
class ATL_NO_VTABLE CSpans : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSpans,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSpans, &CLSID_Spans>,
	public ISupportErrorInfo,
   public PersistentSpanCollImpl,
	public IConnectionPointContainerImpl<CSpans>,
	public CProxyDSpansEvents< CSpans >,
   public IObjectSafetyImpl<CSpans,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISpanEvents
{
public:
	CSpans()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SPANS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSpans)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentSpanCollImpl)
   COM_INTERFACE_ENTRY(ISpanEvents)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSpans)
CONNECTION_POINT_ENTRY(IID_ISpansEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISpanEvents
   STDMETHOD(OnSpanChanged)(/*[in]*/ISpan* Span, BSTR stage, ChangeType change) override;

// ISpans
public:
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(Clone)(/*[out, retval]*/ ISpans** clone) override;


private:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal)
   {
      CHECK_IN(pVal);
      try
      {
         // set up connection point
         HRESULT hr;
         hr = CrAdvise(pVal->second.m_T, this, IID_ISpanEvents, &(pVal->first));
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

   virtual HRESULT OnAfterAdd( StoredType* pVal, SpanIndexType idx)
   {
      Fire_OnSpansAdded(pVal->second.m_T, idx);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove( StoredType* pVal, SpanIndexType idx)
   {
      try
      {
         // release connection point
         HRESULT hr;
         hr = CrUnadvise(pVal->second.m_T, this, IID_ISpanEvents, pVal->first);
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(false);
         return E_FAIL;
      }

      Fire_OnSpansBeforeRemove(pVal->second.m_T, idx);

      return S_OK;
   }

   virtual HRESULT OnAfterRemove( SpanIndexType idx)
   {
      return S_OK; 
   }

   virtual HRESULT OnAfterMoveTo( SpanIndexType from, SpanIndexType to)
   {
      Fire_OnSpansMoveTo (from, to);
      return S_OK;
   }
   virtual HRESULT OnAfterCopyTo( SpanIndexType from, SpanIndexType to)
   {
      Fire_OnSpansCopyTo(from, to);
      return S_OK;
   }
   virtual HRESULT OnAfterReverse()
   {
      Fire_OnSpansReverse();
      return S_OK;
   }

public:
   virtual void FinalRelease()
   {
      // free up all of our connectionpoints on destruct
      SpanIndexType cnt = 0;
      for (iterator it= begin(); it != end(); it++)
      {
         OnBeforeRemove(*it, cnt++);
      }
   }

};

#endif //__SPANS_H_
