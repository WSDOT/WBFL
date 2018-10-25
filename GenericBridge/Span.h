///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 2009  Washington State Department of Transportation
//                   Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// Span.h : Declaration of the CSpan

#ifndef __SPAN_H_
#define __SPAN_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"
#include "TemporaryPierItemCollection.h"
#include "GirderSpacing.h"

class CPier;


/////////////////////////////////////////////////////////////////////////////
// CSpan
class ATL_NO_VTABLE CSpan : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSpan,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSpan, &CLSID_Span>,
	public ISupportErrorInfo,
	public ISpan,
   public IStructuredStorage2,
   public CProxyDSpanEvents< CSpan >,
   public IConnectionPointContainerImpl<CSpan>,
   public IObjectSafetyImpl<CSpan,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IGirderSpacingEvents,
   public ITemporaryPierItemCollectionEvents
{
public:
   CSpan()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetBridge(IGenericBridge* bridge);
   void SetIndex(SpanIndexType index) { m_Index = index; }
   void SetPiers(CPier* prevPier,CPier* nextPier)
   {
      m_pPrevPier = prevPier;
      m_pNextPier = nextPier;

      m_pGirderSpacing[etStart]->SetPier(m_pPrevPier,etStart);
      m_pGirderSpacing[etEnd  ]->SetPier(m_pNextPier,etEnd);
   }

   CPier* GetPrevPier()
   {
      return m_pPrevPier;
   }

   CPier* GetNextPier()
   {
      return m_pNextPier;
   }

   STDMETHOD(Clone)(ISpan** clone);
   void SetTemporaryPiers(ITemporaryPierItemCollection* piers);

   void SetLength(Float64 newVal); // Same as PutLength, but doesn't generate a transaction or fire events

DECLARE_REGISTRY_RESOURCEID(IDR_SPAN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CSpan)
	COM_INTERFACE_ENTRY(ISpan)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IGirderSpacingEvents)
   COM_INTERFACE_ENTRY(ITemporaryPierItemCollectionEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSpan)
	CONNECTION_POINT_ENTRY(IID_ISpanEvents)
END_CONNECTION_POINT_MAP()

private:
   static HRESULT PutLength(CSpan* pThis,Float64 newVal);
   CPier* m_pPrevPier;
   CPier* m_pNextPier;
   SpanIndexType m_Index;
   IGenericBridge* m_pBridge; // weak reference to parent

   CGirderSpacing* m_pGirderSpacing[2];
   CComPtr<IGirderSpacing> m_GirderSpacing[2]; // spacing at start of span and end of span
   DWORD m_dwGirderSpacingCookie[2];
   HRESULT AdviseGirderSpacing();
   HRESULT UnadviseGirderSpacing();

   CComPtr<ITemporaryPierItemCollection> m_TemporaryPiers;
   DWORD m_dwCookie;
   HRESULT AdviseTemporaryPiers();
   HRESULT UnadviseTemporaryPiers();

   std::vector<CComPtr<ISuperstructureMember> > m_SuperstructureMembers;

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISpan
public:
   STDMETHOD(get_Length)(/*[out,retval]*/Float64* length);
   STDMETHOD(put_Length)(/*[in]*/Float64 length);
	STDMETHOD(get_GirderLineLength)(/*[in]*/ GirderIndexType gdrIdx,/*[out,retval]*/Float64* length);
   STDMETHOD(get_TemporaryPiers)(/*[out,retval]*/ ITemporaryPierItemCollection* *tempPiers);
   STDMETHOD(put_GirderCount)(/*[in]*/GirderIndexType nGirders);
	STDMETHOD(get_GirderCount)(/*[out,retval]*/GirderIndexType* nGirders);
	STDMETHOD(AddGirders)(/*[in]*/ GirderIndexType nGirders);
	STDMETHOD(RemoveGirders)(/*[in]*/ GirderIndexType nGirders);
	STDMETHOD(get_SuperstructureMember)(/*[in]*/GirderIndexType gdrIdx,/*[out,retval]*/ISuperstructureMember** ppSSM);
   STDMETHOD(get_GirderSpacing)(/*[in]*/ EndType endType,/*[out,retval]*/IGirderSpacing** ppGirderSpacing);
   STDMETHOD(get_PrevPier)(/*[out,retval]*/IPier** ppPrevPier);
	STDMETHOD(get_NextPier)(/*[out,retval]*/IPier** ppNextPier);
   STDMETHOD(get_Index)(/*[out,retval]*/SpanIndexType* pIndex);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

// IGirderSpacingEvents
public:
   STDMETHOD(OnGirderSpacingChanged)()
   {
      Fire_OnSpanChanged(this);
      return S_OK;
   };

// ITemporaryPierItemCollectionEvents
public:
	STDMETHOD(OnTemporaryPierItemChanged)(ITemporaryPierItem * tpi)
	{
      Fire_OnSpanChanged(this);
      return S_OK;
	}
	STDMETHOD(OnTemporaryPierItemAdded)(long id)
	{
      Fire_OnSpanChanged(this);
      return S_OK;
	}
	STDMETHOD(OnTemporaryPierItemRemoved)(long id)
	{
      Fire_OnSpanChanged(this);
      return S_OK;
	}
};

#endif //__SPAN_H_
