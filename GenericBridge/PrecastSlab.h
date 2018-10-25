///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

/////////////////////////////////////////////////////////////////////////////
// CPrecastSlab
class ATL_NO_VTABLE CPrecastSlab : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPrecastSlab,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPrecastSlab, &CLSID_PrecastSlab>,
	public ISupportErrorInfo,
	public IStructuredStorage2,
	public IConnectionPointContainerImpl<CPrecastSlab>,
   public IObjectSafetyImpl<CPrecastSlab,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IPrecastSlab,
   public IBridgeDeckImpl<CPrecastSlab>,
   public IOverhangPathStrategyEvents
{
public:
   CPrecastSlab()
	{
      m_PanelDepth = 0;
      m_CastDepth = 0;
      m_OverhangDepth = 0;
      m_Fillet = 0;
      m_Taper = dotNone;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

private:
   DWORD m_dwLeftPathStrategyCookie;
   DWORD m_dwRightPathStrategyCookie;

   Float64 m_PanelDepth;
   Float64 m_CastDepth;
   Float64 m_OverhangDepth;
   Float64 m_Fillet;
   DeckOverhangTaper m_Taper;
   CComBSTR m_bstrCastingStage;
   CComPtr<IOverhangPathStrategy> m_LeftPathStrategy;
   CComPtr<IOverhangPathStrategy> m_RightPathStrategy;

public:
DECLARE_REGISTRY_RESOURCEID(IDR_PRECASTSLAB)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPrecastSlab)
	COM_INTERFACE_ENTRY(IPrecastSlab)
	COM_INTERFACE_ENTRY(IBridgeDeck)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IOverhangPathStrategyEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPrecastSlab)
   CONNECTION_POINT_ENTRY(IID_IBridgeDeckEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IBridgeDeck
public:
   STDMETHOD(get_StructuralDepth)(/*[out,retval]*/Float64* depth);
   STDMETHOD(get_GrossDepth)(/*[out,retval]*/Float64* depth);

// IPrecastSlab
public:
   STDMETHOD(get_CastingStage)(/*[out,retval]*/BSTR* bstrStage);
	STDMETHOD(put_CastingStage)(/*[in]*/BSTR bstrStage);
   STDMETHOD(get_PanelDepth)(/*[out,retval]*/Float64* depth);
	STDMETHOD(put_PanelDepth)(/*[in]*/Float64 depth);
   STDMETHOD(get_CastDepth)(/*[out,retval]*/Float64* depth);
	STDMETHOD(put_CastDepth)(/*[in]*/Float64 depth);
	STDMETHOD(get_OverhangDepth)(/*[out,retval]*/Float64* depth);
	STDMETHOD(put_OverhangDepth)(/*[in]*/Float64 depth);
	STDMETHOD(get_Fillet)(/*[out,retval]*/Float64* depth);
	STDMETHOD(put_Fillet)(/*[in]*/Float64 depth);
	STDMETHOD(get_OverhangTaper)(/*[out,retval]*/DeckOverhangTaper* taper);
	STDMETHOD(put_OverhangTaper)(/*[in]*/DeckOverhangTaper taper);
   STDMETHOD(Clone)(/*[out,retval]*/IBridgeDeck** clone);

	STDMETHOD(get_LeftOverhangPathStrategy)(/*[out,retval]*/IOverhangPathStrategy** strategy);
	STDMETHOD(putref_LeftOverhangPathStrategy)(/*[in]*/IOverhangPathStrategy* strategy);
	STDMETHOD(get_RightOverhangPathStrategy)(/*[out,retval]*/IOverhangPathStrategy** strategy);
	STDMETHOD(putref_RightOverhangPathStrategy)(/*[in]*/IOverhangPathStrategy* strategy);

	STDMETHOD(get_LeftOverhangPath)(/*[out,retval]*/IPath** Path);
	STDMETHOD(get_RightOverhangPath)(/*[out,retval]*/IPath** Path);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);



// IOverhangPathStrategyEvents
public:
   STDMETHOD(OnStrategyChanged)()
   {
      Fire_OnBridgeDeckChanged(this);
      return S_OK;
   }
};

#endif //__PRECASTSLAB_H_
