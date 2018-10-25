///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// SectionCutTool.h : Declaration of the CSectionCutTool

#ifndef __SECTIONCUTTOOL_H_
#define __SECTIONCUTTOOL_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CSectionCutTool
class ATL_NO_VTABLE CSectionCutTool : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSectionCutTool, &CLSID_SectionCutTool>,
	public ISupportErrorInfo,
	public ISectionCutTool,
   public IObjectSafetyImpl<CSectionCutTool,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CSectionCutTool()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SECTIONCUTTOOL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSectionCutTool)
	COM_INTERFACE_ENTRY(ISectionCutTool)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   HRESULT CreateCompositeSection(IGenericBridge* bridge,SpanIndexType span,GirderIndexType gdr,Float64 location,BSTR stage,ISection** section);
   HRESULT CreateNoncompositeSection(IGenericBridge* bridge,SpanIndexType span,GirderIndexType gdr,Float64 location,BSTR stage,ISection** section);
   HRESULT CreateBridgeDeckSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,BSTR stage,Float64 elevBottomDeck,ICompositeSectionItem** deckitem);
   HRESULT CreateCIPBridgeDeckSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,Float64 elevBottomDeck,ICompositeSectionItem** deckitem);
   HRESULT CreateSIPBridgeDeckSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,Float64 elevBottomDeck,ICompositeSectionItem** deckitem);
   HRESULT CreateOverlayBridgeDeckSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,Float64 elevBottomDeck,ICompositeSectionItem** deckitem);

   CComPtr<IEffectiveFlangeWidthTool> m_EffFlangeTool;
   CComPtr<IBridgeGeometryTool> m_BridgeGeometryTool;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISectionCutTool
public:
   STDMETHOD(putref_EffectiveFlangeWidthTool)(/*[in]*/ IEffectiveFlangeWidthTool* pTool);
	STDMETHOD(get_EffectiveFlangeWidthTool)(/*[out,retval]*/ IEffectiveFlangeWidthTool* *pTool);
   STDMETHOD(CreateGirderSection)(/*[in]*/IGenericBridge* bridge,/*[in]*/SpanIndexType span,/*[in]*/GirderIndexType gdr,/*[in]*/Float64 location, /*[in]*/ BSTR stage,/*[out,retval]*/ISection** section);
   STDMETHOD(CreateBridgeSection)(/*[in]*/IGenericBridge* bridge,/*[in]*/Float64 distFromStartOfBridge,/*[in]*/ BSTR stage, /*[in]*/ BarrierSectionCut bsc,/*[out,retval]*/ISection** section);
	STDMETHOD(CreateLeftBarrierShape)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[out,retval]*/IShape** shape);
	STDMETHOD(CreateRightBarrierShape)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[out,retval]*/IShape** shape);
   STDMETHOD(CreateLeftBarrierSection)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ VARIANT_BOOL bStructuralOnly,/*[out,retval]*/ICompositeSectionItem** section);
	STDMETHOD(CreateRightBarrierSection)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ VARIANT_BOOL bStructuralOnly,/*[out,retval]*/ICompositeSectionItem** section);
   STDMETHOD(CreateSlabShape)(/*[in]*/IGenericBridge* bridge,/*[in]*/Float64 station,/*[out,retval]*/IShape** shape);
};

#endif //__SECTIONCUTTOOL_H_
