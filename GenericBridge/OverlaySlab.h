///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2017  Washington State Department of Transportation
//                        Bridge and Structures Office
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

// OverlaySlab.h : Declaration of the COverlaySlab

#ifndef __OVERLAYSLAB_H_
#define __OVERLAYSLAB_H_

#include "resource.h"       // main symbols
#include "BridgeDeckImpl.h"

/////////////////////////////////////////////////////////////////////////////
// COverlaySlab
class ATL_NO_VTABLE COverlaySlab : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<COverlaySlab,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<COverlaySlab, &CLSID_OverlaySlab>,
	public ISupportErrorInfo,
	public IStructuredStorage2,
   public IObjectSafetyImpl<COverlaySlab,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IOverlaySlab,
   public IBridgeDeckImpl<COverlaySlab>
{
public:
   COverlaySlab()
	{
      m_GrossDepth = 0;
      m_pDeckBoundary = nullptr;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

private:
   Float64 m_GrossDepth;

   IDeckBoundary* m_pDeckBoundary; // weak reference

public:
DECLARE_REGISTRY_RESOURCEID(IDR_OVERLAYSLAB)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(COverlaySlab)
	COM_INTERFACE_ENTRY(IOverlaySlab)
	COM_INTERFACE_ENTRY(IBridgeDeck)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBridgeDeck
public:
   STDMETHOD(get_StructuralDepth)(/*[out,retval]*/Float64* depth) override;
   STDMETHOD(get_GrossDepth)(/*[out,retval]*/Float64* depth) override;
   STDMETHOD(putref_DeckBoundary)(IDeckBoundary* deckBoundary) override;
   STDMETHOD(get_DeckBoundary)(IDeckBoundary** deckBoundary) override;

// IOverlaySlab
public:
	STDMETHOD(put_GrossDepth)(/*[in]*/Float64 depth) override;


// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__OVERLAYSLAB_H_
