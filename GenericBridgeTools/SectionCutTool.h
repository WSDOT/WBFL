///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2025  Washington State Department of Transportation
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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISectionCutTool
public:
   // Set/Get the effective flange width tool. This tool is needed for computing the effective
   // flange width when creating girder sections.
   STDMETHOD(putref_EffectiveFlangeWidthTool)(IEffectiveFlangeWidthTool* pTool) override;
	STDMETHOD(get_EffectiveFlangeWidthTool)(IEffectiveFlangeWidthTool* *pTool) override;

   //
   // The CreateXXXSection methods creates a ISection object. Use the resulting objects to get
   // section stiffness and section properties
   //

   // creates girder sections, including the deck, ducts, tendons, strands, and rebar
   STDMETHOD(CreateGirderSectionBySSMbr)(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 Xgp, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, StageIndexType stageIdx, SectionPropertyMethod sectionPropMethod, HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile, IndexType* beamIdx, IndexType* slabIdx, ISection** section) override;
   STDMETHOD(CreateGirderSectionBySegment)(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod, HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile, IndexType* beamIdx, IndexType* slabIdx, ISection** section) override;

   // creates a net section of the deck
   STDMETHOD(CreateNetDeckSection)(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,StageIndexType stageIdx,HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile,ISection** section) override;

   // creates a section for the entire bridge
   STDMETHOD(CreateBridgeSection)(/*[in]*/IGenericBridge* bridge,/*[in]*/Float64 Xb,/*[in]*/SectionBias sectionBias,/*[in]*/ StageIndexType stageIdx, /*[in]*/ BarrierSectionCut bsc,/*[out,retval]*/ISection** section) override;

   //
   // The CreateXXXShape methods create a shape object that is intended to be used as for a 
   // graphical representation of the cross section.
   //
   
   // creates a composite shape object containing the girder, holes for ducts, and the deck, if present
   STDMETHOD(CreateGirderShapeBySSMbr)(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 Xgp,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,VARIANT_BOOL bIncludeDeck,HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile,IShape** ppShape) override;
   STDMETHOD(CreateGirderShapeBySegment)(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,VARIANT_BOOL bIncludeDeck,HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile,IShape** ppShape) override;

   // creates shapes for the left and right railing systems
	STDMETHOD(CreateLeftBarrierShape)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/IDirection* pDirection,/*[out,retval]*/IShape** shape) override;
	STDMETHOD(CreateRightBarrierShape)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/IDirection* pDirection,/*[out,retval]*/IShape** shape) override;

   // creates a shape for the bridge deck
   STDMETHOD(CreateSlabShape)(/*[in]*/IGenericBridge* bridge,/*[in]*/Float64 station,/*[in]*/IDirection* pDirection,/*[in]*/ VARIANT_BOOL bIncludeHaunch,/*[out,retval]*/IShape** shape) override;

   STDMETHOD(CreateLongitudinalJointShapeBySSMbr)(/*[in]*/IGenericBridge* bridge, /*[in]*/GirderIDType ssMbrID, /*[in]*/Float64 Xgp, /*[in]*/SectionCoordinateSystemType coordinateSystem, /*[out]*/IShape** ppLeftJointShape, /*[out]*/IShape** ppRightJointShape);
   STDMETHOD(CreateLongitudinalJointShapeBySegment)(/*[in]*/IGenericBridge* bridge, /*[in]*/GirderIDType ssMbrID, /*[in]*/SegmentIndexType segIdx, /*[in]*/Float64 Xs, /*[in]*/SectionCoordinateSystemType coordinateSystem, /*[out]*/IShape** ppLeftJointShape,/*[out]*/IShape** ppRightJointShape);

   STDMETHOD(GetDeckProperties)(/*[in]*/IGenericBridge* bridge,/*[in]*/IndexType nSectionsPerSpan,/*[out]*/Float64* pSurfaceArea,/*[out]*/Float64* pVolume) override;
	STDMETHOD(GetStructuralHaunchDepth)(/*[in]*/IGenericBridge* bridge,/*[in]*/GirderIDType ssMbrID,/*[in]*/SegmentIndexType segIdx,/*[in]*/Float64 Xs,/*[in]*/HaunchDepthMethod haunchMethod, /*[out,retval]*/Float64* pHaunchDepth);

   // creates the deck shape used in composite analyses
   STDMETHOD(CreateDeckAnalysisShape)(IGenericBridge* bridge,IGirderSection* pSection,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs, SectionBias sectionBias, Float64 haunchDepth, BOOL bFollowMatingSurfaceProfile,StageIndexType stageIdx,IShape** shape) override;

private:
   // create section objects for the traffic barriers. This is only used for to total bridge section
   STDMETHOD(CreateLeftBarrierSection)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ VARIANT_BOOL bStructuralOnly,/*[out,retval]*/ISection** section);
   STDMETHOD(CreateRightBarrierSection)(/*[in]*/IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ VARIANT_BOOL bStructuralOnly,/*[out,retval]*/ISection** section);

   HRESULT CreateCompositeSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod, HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile, IndexType* beamIdx, IndexType* slabIdx,ISection** section);
   HRESULT CreateDeckSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,SectionBias sectionBias,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod, HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile,IGirderSection* pGirderSection,ISection** section);
   HRESULT CreateDeckShape(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs, SectionBias sectionBias, Float64 haunchDepth, BOOL bFollowMatingSurfaceProfile,IGirderSection* pGirderSection,IShape** pShape);
   HRESULT CreateNoncompositeSection(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod,ISection** section);
   HRESULT CreateBridgeDeckSection(IGenericBridge* bridge,Float64 Xb, SectionBias sectionBias, StageIndexType stageIdx,Float64 elevBottomDeck,ICompositeSectionItemEx** deckitem);
   HRESULT CreateGirderShape(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,VARIANT_BOOL bIncludeDeck,HaunchDepthMethod haunchMethod, BOOL bFollowMatingSurfaceProfile,IShape** ppShape);
   HRESULT CreateJointShapes(IGenericBridge* bridge, GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, SectionCoordinateSystemType coordinateSystem, IShape** ppLeftJointShape, IShape** ppRightJointShape);
   HRESULT LayoutRebar(ICompositeSectionEx* compositeSection,Float64 Econc,Float64 Dconc,IRebarSection* rebarSection,Float64 xTop,Float64 yTop,StageIndexType stageIdx,SectionPropertyMethod sectionPropMethod);
   HRESULT SkewShape(Float64 skewAngle,IShape* pShape,IShape** ppSkewedShape);
   HRESULT CreateBarrierShape(DirectionType side,IGenericBridge* bridge,Float64 station,IDirection* pDirection,IShape** ppShape);
   HRESULT ModelTendon(Float64 X, StageIndexType stageIdx, Float64 xTop, Float64 yTop, ITendon* pTendon, SectionPropertyMethod sectionPropMethod, Float64 Econc, Float64 Dconc, ICompositeSectionEx* pCompositeSection);

   struct GirderPointRecord
   {
      CComPtr<IStation> objGirderStation;
      Float64 normalOffset;
      Float64 cutLineOffset;
      GirderIDType girderID;
      LocationType girderLocation;
      SegmentIndexType segIdx;
      Float64 Xs;

      bool operator<(const GirderPointRecord& other) const
      {
         return cutLineOffset < other.cutLineOffset;
      }
   };

   std::vector<CSectionCutTool::GirderPointRecord> GetGirderPoints(IGenericBridge* pBridge,IStation* pStation,IDirection* pDirection);
};

#endif //__SECTIONCUTTOOL_H_
