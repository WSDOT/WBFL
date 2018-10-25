///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2013  Washington State Department of Transportation
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
   CComPtr<IEffectiveFlangeWidthTool> m_EffFlangeTool;
   CComPtr<IBridgeGeometryTool> m_BridgeGeometryTool;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISectionCutTool
public:
   // Set/Get the effective flange width tool. This tool is needed for computing the effective
   // flange width when creating girder sections.
   STDMETHOD(putref_EffectiveFlangeWidthTool)(IEffectiveFlangeWidthTool* pTool);
	STDMETHOD(get_EffectiveFlangeWidthTool)(IEffectiveFlangeWidthTool* *pTool);

   //
   // The CreateXXXSection methods creates a ISection object. Use the resulting objects to get
   // section stiffness and section properties
   //

   // creates girder sections, including the deck, ducts, tendons, strands, and rebar
   STDMETHOD(CreateGirderSectionBySSMbr)(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 distFromStartOfSSMbr, GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx, SectionPropertyMethod sectionPropMethod,ISection** section);
   STDMETHOD(CreateGirderSectionBySegment)(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section);

   // creates a net section of the deck
   STDMETHOD(CreateNetDeckSection)(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,ISection** section);

   // creates a section for the entire bridge
   STDMETHOD(CreateBridgeSection)(/*[in]*/IGenericBridge* bridge,/*[in]*/Float64 distFromStartOfBridge,/*[in]*/ StageIndexType stageIdx, /*[in]*/ BarrierSectionCut bsc,/*[out,retval]*/ISection** section);

   // creates section objects for the traffic barriers
   STDMETHOD(CreateLeftBarrierSection)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ VARIANT_BOOL bStructuralOnly,/*[out,retval]*/ISection** section);
	STDMETHOD(CreateRightBarrierSection)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ VARIANT_BOOL bStructuralOnly,/*[out,retval]*/ISection** section);

   //
   // The CreateXXXShape methods create a shape object that is intended to be used as for a 
   // graphical representation of the cross section.
   //
   
   // creates a composite shape object containing the girder, holes for ducts, and the deck, if present
   STDMETHOD(CreateGirderShapeBySSMbr)(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 distFromStartOfSSMbr,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,IShape** ppShape);
   STDMETHOD(CreateGirderShapeBySegment)(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx, IShape** ppShape);

   // creates shapes for the left and right railing systems
	STDMETHOD(CreateLeftBarrierShape)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[out,retval]*/IShape** shape);
	STDMETHOD(CreateRightBarrierShape)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[out,retval]*/IShape** shape);

   // creates a shape for the bridge deck
   STDMETHOD(CreateSlabShape)(/*[in]*/IGenericBridge* bridge,/*[in]*/Float64 station,/*[out,retval]*/IShape** shape);

private:
   HRESULT CreateCompositeSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section);
   HRESULT CreateDeckSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section);
   HRESULT CreateNoncompositeSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section);
   HRESULT CreateBridgeDeckSection(IGenericBridge* bridge,Float64 distFromStartOfBridge,StageIndexType stageIdx,Float64 elevBottomDeck,ICompositeSectionItemEx** deckitem);
   HRESULT CreateGirderShape(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,StageIndexType stageIdx,IShape** ppShape);
   HRESULT LayoutRebar(ICompositeSectionEx* compositeSection,Float64 Econc,Float64 Dconc,IRebarSection* rebarSection,Float64 yBottom,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod);
};

#endif //__SECTIONCUTTOOL_H_
