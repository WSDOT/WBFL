///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2016  Washington State Department of Transportation
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

// Span.h : Declaration of the CSpan

#ifndef __SPAN_H_
#define __SPAN_H_

#include "resource.h"       // main symbols
#include "SpanCP.h" 
#include "LoadModifierHelper.h"

/////////////////////////////////////////////////////////////////////////////
// CSpan
class ATL_NO_VTABLE CSpan : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSpan,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSpan, &CLSID_Span>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CSpan>,
	public ISpan,
   public IPersistImpl<CSpan>,
	public IStructuredStorage2,
	public CProxyDSpanEvents< CSpan >,
   public IObjectSafetyImpl<CSpan,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ITemporarySupportsEvents
{
public:
   CSpan():
      m_Length(0.0),
      m_TemporarySupportsCookie(0)
	{
   }

   STDMETHOD(FinalConstruct)();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_SPAN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSpan)
	COM_INTERFACE_ENTRY(ISpan)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ITemporarySupportsEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSpan)
CONNECTION_POINT_ENTRY(IID_ISpanEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISpan
public:
	STDMETHOD(RemoveStage)(BSTR stage);
	STDMETHOD(Clone)(/*[out,retval]*/ISpan** clone);
	STDMETHOD(GetLoadModifier)(/*[in]*/ LoadCombinationType type, /*[out]*/ Float64 *minVal, /*[out]*/ Float64 *maxVal);
	STDMETHOD(SetLoadModifier)(/*[in]*/ LoadCombinationType type, /*[in]*/ Float64 minVal, /*[in]*/ Float64 maxVal);
	STDMETHOD(get_TemporarySupports)(/*[out, retval]*/ ITemporarySupports* *pVal);
	STDMETHOD(putref_TemporarySupports)(/*[in]*/ ITemporarySupports* newVal);
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Length)(/*[in]*/ Float64 newVal);

// _ITemporarySupportsEvents
   STDMETHOD(OnTemporarySupportsChanged)(/*[in]*/ITemporarySupport* supports, BSTR stage, /*[in]*/ChangeType change);
   STDMETHOD(OnTemporarySupportsAdded)(/*[in]*/ITemporarySupport* supports,/*[in]*/SupportIndexType index);
   STDMETHOD(OnTemporarySupportsBeforeRemove)(/*[in]*/ITemporarySupport* supports,/*[in]*/SupportIndexType index);

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

protected:
   Float64 m_Length;

   CLoadModifierHelper m_LoadModifierHelper;

   CComPtr<ITemporarySupports> m_TemporarySupports;
   DWORD m_TemporarySupportsCookie;

};

#endif //__SPAN_H_
