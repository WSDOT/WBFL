///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

// CastSlab.h : Declaration of the CCastSlab

#ifndef __CASTSLAB_H_
#define __CASTSLAB_H_

#include "resource.h"       // main symbols
#include "BridgeDeckImpl.h"
#include <array>

/////////////////////////////////////////////////////////////////////////////
// CCastSlab
class ATL_NO_VTABLE CCastSlab : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CCastSlab,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CCastSlab, &CLSID_CastSlab>,
	public ISupportErrorInfo,
	public IStructuredStorage2,
   public IObjectSafetyImpl<CCastSlab,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ICastSlab,
   public IBridgeDeckImpl<CCastSlab>
{
public:
   CCastSlab() :
      m_GrossDepth(0.0),
      m_OverhangDepth {0.0, 0.0}, 
      m_Taper{dotNone, dotNone}
   {
      m_pDeckBoundary = nullptr;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

private:
   Float64 m_GrossDepth;
   std::array<Float64,2> m_OverhangDepth;
   std::array<DeckOverhangTaper,2> m_Taper;

   CComPtr<ICastingRegions> m_CastingRegions;

   IDeckBoundary* m_pDeckBoundary; // weak reference

public:
DECLARE_REGISTRY_RESOURCEID(IDR_CASTSLAB)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCastSlab)
	COM_INTERFACE_ENTRY(ICastSlab)
	COM_INTERFACE_ENTRY(IBridgeDeck)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
END_COM_MAP()

protected:
   virtual void OnBridge() override;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBridgeDeck
public:
   STDMETHOD(get_StructuralDepth)(/*[out,retval]*/Float64* depth) override;
   STDMETHOD(get_GrossDepth)(/*[out,retval]*/Float64* depth) override;
   STDMETHOD(putref_DeckBoundary)(IDeckBoundary* deckBoundary) override;
   STDMETHOD(get_DeckBoundary)(IDeckBoundary** deckBoundary) override;

// ICastSlab
public:
   STDMETHOD(get_CastingRegions)(/*[out, retval]*/ICastingRegions** ppRegions) override;
   STDMETHOD(putref_CastingRegions)(/*[in]*/ICastingRegions* pRegions) override;
   STDMETHOD(put_GrossDepth)(/*[in]*/Float64 depth) override;
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

#endif //__CASTSLAB_H_
