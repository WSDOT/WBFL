///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

// PrecastSlab.h : Declaration of the CPrecastSlab

#ifndef __PRECASTSLAB_H_
#define __PRECASTSLAB_H_

#include "resource.h"       // main symbols
#include "BridgeDeckImpl.h"
#include <array>

/////////////////////////////////////////////////////////////////////////////
// CPrecastSlab
class ATL_NO_VTABLE CPrecastSlab : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPrecastSlab,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPrecastSlab, &CLSID_PrecastSlab>,
	public ISupportErrorInfo,
	public IStructuredStorage2,
	//public IConnectionPointContainerImpl<CPrecastSlab>,
   public IObjectSafetyImpl<CPrecastSlab,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IPrecastSlab,
   public IBridgeDeckImpl<CPrecastSlab>//,
   //public IOverhangPathStrategyEvents
{
public:
   CPrecastSlab() :
      m_OverhangDepth{ 0.0, 0.0 },
      m_Taper{ dotNone, dotNone }
	{
      m_PanelDepth = 0;
      m_CastDepth = 0;
      m_pDeckBoundary = nullptr;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

private:
   Float64 m_PanelDepth;
   Float64 m_CastDepth;
   std::array<Float64, 2> m_OverhangDepth;
   std::array<DeckOverhangTaper, 2> m_Taper;

   IDeckBoundary* m_pDeckBoundary; // weak reference

public:
DECLARE_REGISTRY_RESOURCEID(IDR_PRECASTSLAB)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPrecastSlab)
	COM_INTERFACE_ENTRY(IPrecastSlab)
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

// IPrecastSlab
public:
   STDMETHOD(get_PanelDepth)(/*[out,retval]*/Float64* depth) override;
	STDMETHOD(put_PanelDepth)(/*[in]*/Float64 depth) override;
   STDMETHOD(get_CastDepth)(/*[out,retval]*/Float64* depth) override;
	STDMETHOD(put_CastDepth)(/*[in]*/Float64 depth) override;
   STDMETHOD(get_OverhangDepth)(/*[in]*/DirectionType side,/*[out,retval]*/Float64* depth) override;
   STDMETHOD(put_OverhangDepth)(/*[in]*/DirectionType side,/*[in]*/Float64 depth) override;
   STDMETHOD(get_OverhangTaper)(/*[in]*/DirectionType side,/*[out,retval]*/DeckOverhangTaper* taper) override;
   STDMETHOD(put_OverhangTaper)(/*[in]*/DirectionType side,/*[in]*/DeckOverhangTaper taper) override;
   STDMETHOD(GetOverhang)(/*[out]*/Float64* leftDepth, /*[out]*/DeckOverhangTaper* leftTaper, /*[out]*/Float64* rightDepth, /*[out]*/DeckOverhangTaper* rightTaper) override;
   STDMETHOD(SetOverhang)(/*[in]*/Float64 leftDepth, /*[in]*/DeckOverhangTaper leftTaper, /*[in]*/Float64 rightDepth, /*[in]*/DeckOverhangTaper rightTaper) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__PRECASTSLAB_H_
