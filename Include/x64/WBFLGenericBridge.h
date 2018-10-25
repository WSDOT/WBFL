

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Oct 30 08:11:19 2017
 */
/* Compiler settings for ..\Include\WBFLGenericBridge.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __WBFLGenericBridge_h__
#define __WBFLGenericBridge_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IRebarLayoutItem_FWD_DEFINED__
#define __IRebarLayoutItem_FWD_DEFINED__
typedef interface IRebarLayoutItem IRebarLayoutItem;

#endif 	/* __IRebarLayoutItem_FWD_DEFINED__ */


#ifndef __IBridgeDeckRebarLayoutItem_FWD_DEFINED__
#define __IBridgeDeckRebarLayoutItem_FWD_DEFINED__
typedef interface IBridgeDeckRebarLayoutItem IBridgeDeckRebarLayoutItem;

#endif 	/* __IBridgeDeckRebarLayoutItem_FWD_DEFINED__ */


#ifndef __IGenericBridge_FWD_DEFINED__
#define __IGenericBridge_FWD_DEFINED__
typedef interface IGenericBridge IGenericBridge;

#endif 	/* __IGenericBridge_FWD_DEFINED__ */


#ifndef __ISuperstructureMember_FWD_DEFINED__
#define __ISuperstructureMember_FWD_DEFINED__
typedef interface ISuperstructureMember ISuperstructureMember;

#endif 	/* __ISuperstructureMember_FWD_DEFINED__ */


#ifndef __IPier_FWD_DEFINED__
#define __IPier_FWD_DEFINED__
typedef interface IPier IPier;

#endif 	/* __IPier_FWD_DEFINED__ */


#ifndef __ICrossBeam_FWD_DEFINED__
#define __ICrossBeam_FWD_DEFINED__
typedef interface ICrossBeam ICrossBeam;

#endif 	/* __ICrossBeam_FWD_DEFINED__ */


#ifndef __IColumnLayout_FWD_DEFINED__
#define __IColumnLayout_FWD_DEFINED__
typedef interface IColumnLayout IColumnLayout;

#endif 	/* __IColumnLayout_FWD_DEFINED__ */


#ifndef __IVoidedSlabSection2_FWD_DEFINED__
#define __IVoidedSlabSection2_FWD_DEFINED__
typedef interface IVoidedSlabSection2 IVoidedSlabSection2;

#endif 	/* __IVoidedSlabSection2_FWD_DEFINED__ */


#ifndef __IDeckedSlabBeamSection_FWD_DEFINED__
#define __IDeckedSlabBeamSection_FWD_DEFINED__
typedef interface IDeckedSlabBeamSection IDeckedSlabBeamSection;

#endif 	/* __IDeckedSlabBeamSection_FWD_DEFINED__ */


#ifndef __IBoxBeamSection_FWD_DEFINED__
#define __IBoxBeamSection_FWD_DEFINED__
typedef interface IBoxBeamSection IBoxBeamSection;

#endif 	/* __IBoxBeamSection_FWD_DEFINED__ */


#ifndef __IUGirderSection_FWD_DEFINED__
#define __IUGirderSection_FWD_DEFINED__
typedef interface IUGirderSection IUGirderSection;

#endif 	/* __IUGirderSection_FWD_DEFINED__ */


#ifndef __IUGirderSection2_FWD_DEFINED__
#define __IUGirderSection2_FWD_DEFINED__
typedef interface IUGirderSection2 IUGirderSection2;

#endif 	/* __IUGirderSection2_FWD_DEFINED__ */


#ifndef __ITendon_FWD_DEFINED__
#define __ITendon_FWD_DEFINED__
typedef interface ITendon ITendon;

#endif 	/* __ITendon_FWD_DEFINED__ */


#ifndef __ISegment_FWD_DEFINED__
#define __ISegment_FWD_DEFINED__
typedef interface ISegment ISegment;

#endif 	/* __ISegment_FWD_DEFINED__ */


#ifndef __IEffectiveFlangeWidthDetails_FWD_DEFINED__
#define __IEffectiveFlangeWidthDetails_FWD_DEFINED__
typedef interface IEffectiveFlangeWidthDetails IEffectiveFlangeWidthDetails;

#endif 	/* __IEffectiveFlangeWidthDetails_FWD_DEFINED__ */


#ifndef __IEffectiveFlangeWidthTool_FWD_DEFINED__
#define __IEffectiveFlangeWidthTool_FWD_DEFINED__
typedef interface IEffectiveFlangeWidthTool IEffectiveFlangeWidthTool;

#endif 	/* __IEffectiveFlangeWidthTool_FWD_DEFINED__ */


#ifndef __IRebar_FWD_DEFINED__
#define __IRebar_FWD_DEFINED__
typedef interface IRebar IRebar;

#endif 	/* __IRebar_FWD_DEFINED__ */


#ifndef __IRebarFactory_FWD_DEFINED__
#define __IRebarFactory_FWD_DEFINED__
typedef interface IRebarFactory IRebarFactory;

#endif 	/* __IRebarFactory_FWD_DEFINED__ */


#ifndef __IRebarSectionItem_FWD_DEFINED__
#define __IRebarSectionItem_FWD_DEFINED__
typedef interface IRebarSectionItem IRebarSectionItem;

#endif 	/* __IRebarSectionItem_FWD_DEFINED__ */


#ifndef __IEnumRebarSectionItem_FWD_DEFINED__
#define __IEnumRebarSectionItem_FWD_DEFINED__
typedef interface IEnumRebarSectionItem IEnumRebarSectionItem;

#endif 	/* __IEnumRebarSectionItem_FWD_DEFINED__ */


#ifndef __IRebarSection_FWD_DEFINED__
#define __IRebarSection_FWD_DEFINED__
typedef interface IRebarSection IRebarSection;

#endif 	/* __IRebarSection_FWD_DEFINED__ */


#ifndef __IRebarPattern_FWD_DEFINED__
#define __IRebarPattern_FWD_DEFINED__
typedef interface IRebarPattern IRebarPattern;

#endif 	/* __IRebarPattern_FWD_DEFINED__ */


#ifndef __IRebarRowFacePattern_FWD_DEFINED__
#define __IRebarRowFacePattern_FWD_DEFINED__
typedef interface IRebarRowFacePattern IRebarRowFacePattern;

#endif 	/* __IRebarRowFacePattern_FWD_DEFINED__ */


#ifndef __IRebarRowPattern_FWD_DEFINED__
#define __IRebarRowPattern_FWD_DEFINED__
typedef interface IRebarRowPattern IRebarRowPattern;

#endif 	/* __IRebarRowPattern_FWD_DEFINED__ */


#ifndef __ICrossBeamRebarPattern_FWD_DEFINED__
#define __ICrossBeamRebarPattern_FWD_DEFINED__
typedef interface ICrossBeamRebarPattern ICrossBeamRebarPattern;

#endif 	/* __ICrossBeamRebarPattern_FWD_DEFINED__ */


#ifndef __IEnumRebarPatterns_FWD_DEFINED__
#define __IEnumRebarPatterns_FWD_DEFINED__
typedef interface IEnumRebarPatterns IEnumRebarPatterns;

#endif 	/* __IEnumRebarPatterns_FWD_DEFINED__ */


#ifndef __IBridgeDeckRebarPattern_FWD_DEFINED__
#define __IBridgeDeckRebarPattern_FWD_DEFINED__
typedef interface IBridgeDeckRebarPattern IBridgeDeckRebarPattern;

#endif 	/* __IBridgeDeckRebarPattern_FWD_DEFINED__ */


#ifndef __IEnumBridgeDeckRebarPatterns_FWD_DEFINED__
#define __IEnumBridgeDeckRebarPatterns_FWD_DEFINED__
typedef interface IEnumBridgeDeckRebarPatterns IEnumBridgeDeckRebarPatterns;

#endif 	/* __IEnumBridgeDeckRebarPatterns_FWD_DEFINED__ */


#ifndef __IFixedLengthRebarLayoutItem_FWD_DEFINED__
#define __IFixedLengthRebarLayoutItem_FWD_DEFINED__
typedef interface IFixedLengthRebarLayoutItem IFixedLengthRebarLayoutItem;

#endif 	/* __IFixedLengthRebarLayoutItem_FWD_DEFINED__ */


#ifndef __INegativeMomentBridgeDeckRebarLayoutItem_FWD_DEFINED__
#define __INegativeMomentBridgeDeckRebarLayoutItem_FWD_DEFINED__
typedef interface INegativeMomentBridgeDeckRebarLayoutItem INegativeMomentBridgeDeckRebarLayoutItem;

#endif 	/* __INegativeMomentBridgeDeckRebarLayoutItem_FWD_DEFINED__ */


#ifndef __IEnumRebarLayoutItems_FWD_DEFINED__
#define __IEnumRebarLayoutItems_FWD_DEFINED__
typedef interface IEnumRebarLayoutItems IEnumRebarLayoutItems;

#endif 	/* __IEnumRebarLayoutItems_FWD_DEFINED__ */


#ifndef __IEnumBridgeDeckRebarLayoutItems_FWD_DEFINED__
#define __IEnumBridgeDeckRebarLayoutItems_FWD_DEFINED__
typedef interface IEnumBridgeDeckRebarLayoutItems IEnumBridgeDeckRebarLayoutItems;

#endif 	/* __IEnumBridgeDeckRebarLayoutItems_FWD_DEFINED__ */


#ifndef __IRebarLayout_FWD_DEFINED__
#define __IRebarLayout_FWD_DEFINED__
typedef interface IRebarLayout IRebarLayout;

#endif 	/* __IRebarLayout_FWD_DEFINED__ */


#ifndef __IBridgeDeckRebarLayout_FWD_DEFINED__
#define __IBridgeDeckRebarLayout_FWD_DEFINED__
typedef interface IBridgeDeckRebarLayout IBridgeDeckRebarLayout;

#endif 	/* __IBridgeDeckRebarLayout_FWD_DEFINED__ */


#ifndef __IMaterial_FWD_DEFINED__
#define __IMaterial_FWD_DEFINED__
typedef interface IMaterial IMaterial;

#endif 	/* __IMaterial_FWD_DEFINED__ */


#ifndef __IItemData_FWD_DEFINED__
#define __IItemData_FWD_DEFINED__
typedef interface IItemData IItemData;

#endif 	/* __IItemData_FWD_DEFINED__ */


#ifndef __IPrestressingStrand_FWD_DEFINED__
#define __IPrestressingStrand_FWD_DEFINED__
typedef interface IPrestressingStrand IPrestressingStrand;

#endif 	/* __IPrestressingStrand_FWD_DEFINED__ */


#ifndef __IOverhangPathStrategy_FWD_DEFINED__
#define __IOverhangPathStrategy_FWD_DEFINED__
typedef interface IOverhangPathStrategy IOverhangPathStrategy;

#endif 	/* __IOverhangPathStrategy_FWD_DEFINED__ */


#ifndef __IAlignmentOffsetStrategy_FWD_DEFINED__
#define __IAlignmentOffsetStrategy_FWD_DEFINED__
typedef interface IAlignmentOffsetStrategy IAlignmentOffsetStrategy;

#endif 	/* __IAlignmentOffsetStrategy_FWD_DEFINED__ */


#ifndef __IEdgePathStrategy_FWD_DEFINED__
#define __IEdgePathStrategy_FWD_DEFINED__
typedef interface IEdgePathStrategy IEdgePathStrategy;

#endif 	/* __IEdgePathStrategy_FWD_DEFINED__ */


#ifndef __IBridgeDeck_FWD_DEFINED__
#define __IBridgeDeck_FWD_DEFINED__
typedef interface IBridgeDeck IBridgeDeck;

#endif 	/* __IBridgeDeck_FWD_DEFINED__ */


#ifndef __ICastSlab_FWD_DEFINED__
#define __ICastSlab_FWD_DEFINED__
typedef interface ICastSlab ICastSlab;

#endif 	/* __ICastSlab_FWD_DEFINED__ */


#ifndef __IPrecastSlab_FWD_DEFINED__
#define __IPrecastSlab_FWD_DEFINED__
typedef interface IPrecastSlab IPrecastSlab;

#endif 	/* __IPrecastSlab_FWD_DEFINED__ */


#ifndef __IOverlaySlab_FWD_DEFINED__
#define __IOverlaySlab_FWD_DEFINED__
typedef interface IOverlaySlab IOverlaySlab;

#endif 	/* __IOverlaySlab_FWD_DEFINED__ */


#ifndef __IBarrier_FWD_DEFINED__
#define __IBarrier_FWD_DEFINED__
typedef interface IBarrier IBarrier;

#endif 	/* __IBarrier_FWD_DEFINED__ */


#ifndef __IGenericBarrier_FWD_DEFINED__
#define __IGenericBarrier_FWD_DEFINED__
typedef interface IGenericBarrier IGenericBarrier;

#endif 	/* __IGenericBarrier_FWD_DEFINED__ */


#ifndef __IFShapeBarrier_FWD_DEFINED__
#define __IFShapeBarrier_FWD_DEFINED__
typedef interface IFShapeBarrier IFShapeBarrier;

#endif 	/* __IFShapeBarrier_FWD_DEFINED__ */


#ifndef __ISidewalkBarrier_FWD_DEFINED__
#define __ISidewalkBarrier_FWD_DEFINED__
typedef interface ISidewalkBarrier ISidewalkBarrier;

#endif 	/* __ISidewalkBarrier_FWD_DEFINED__ */


#ifndef __IFlangedGirderSection_FWD_DEFINED__
#define __IFlangedGirderSection_FWD_DEFINED__
typedef interface IFlangedGirderSection IFlangedGirderSection;

#endif 	/* __IFlangedGirderSection_FWD_DEFINED__ */


#ifndef __ISuperstructureMemberSegment_FWD_DEFINED__
#define __ISuperstructureMemberSegment_FWD_DEFINED__
typedef interface ISuperstructureMemberSegment ISuperstructureMemberSegment;

#endif 	/* __ISuperstructureMemberSegment_FWD_DEFINED__ */


#ifndef __IEnumSegment_FWD_DEFINED__
#define __IEnumSegment_FWD_DEFINED__
typedef interface IEnumSegment IEnumSegment;

#endif 	/* __IEnumSegment_FWD_DEFINED__ */


#ifndef __IFilteredSegmentCollection_FWD_DEFINED__
#define __IFilteredSegmentCollection_FWD_DEFINED__
typedef interface IFilteredSegmentCollection IFilteredSegmentCollection;

#endif 	/* __IFilteredSegmentCollection_FWD_DEFINED__ */


#ifndef __ISegmentItem_FWD_DEFINED__
#define __ISegmentItem_FWD_DEFINED__
typedef interface ISegmentItem ISegmentItem;

#endif 	/* __ISegmentItem_FWD_DEFINED__ */


#ifndef __IEnumSuperstructureMembers_FWD_DEFINED__
#define __IEnumSuperstructureMembers_FWD_DEFINED__
typedef interface IEnumSuperstructureMembers IEnumSuperstructureMembers;

#endif 	/* __IEnumSuperstructureMembers_FWD_DEFINED__ */


#ifndef __ISuperstructureMemberCollection_FWD_DEFINED__
#define __ISuperstructureMemberCollection_FWD_DEFINED__
typedef interface ISuperstructureMemberCollection ISuperstructureMemberCollection;

#endif 	/* __ISuperstructureMemberCollection_FWD_DEFINED__ */


#ifndef __IPrismaticSegment_FWD_DEFINED__
#define __IPrismaticSegment_FWD_DEFINED__
typedef interface IPrismaticSegment IPrismaticSegment;

#endif 	/* __IPrismaticSegment_FWD_DEFINED__ */


#ifndef __IPrismaticSuperstructureMemberSegment_FWD_DEFINED__
#define __IPrismaticSuperstructureMemberSegment_FWD_DEFINED__
typedef interface IPrismaticSuperstructureMemberSegment IPrismaticSuperstructureMemberSegment;

#endif 	/* __IPrismaticSuperstructureMemberSegment_FWD_DEFINED__ */


#ifndef __IFlangedGirderEndBlockSegment_FWD_DEFINED__
#define __IFlangedGirderEndBlockSegment_FWD_DEFINED__
typedef interface IFlangedGirderEndBlockSegment IFlangedGirderEndBlockSegment;

#endif 	/* __IFlangedGirderEndBlockSegment_FWD_DEFINED__ */


#ifndef __IVoidedSlabEndBlockSegment_FWD_DEFINED__
#define __IVoidedSlabEndBlockSegment_FWD_DEFINED__
typedef interface IVoidedSlabEndBlockSegment IVoidedSlabEndBlockSegment;

#endif 	/* __IVoidedSlabEndBlockSegment_FWD_DEFINED__ */


#ifndef __IDeckedSlabBeamEndBlockSegment_FWD_DEFINED__
#define __IDeckedSlabBeamEndBlockSegment_FWD_DEFINED__
typedef interface IDeckedSlabBeamEndBlockSegment IDeckedSlabBeamEndBlockSegment;

#endif 	/* __IDeckedSlabBeamEndBlockSegment_FWD_DEFINED__ */


#ifndef __IBoxBeamEndBlockSegment_FWD_DEFINED__
#define __IBoxBeamEndBlockSegment_FWD_DEFINED__
typedef interface IBoxBeamEndBlockSegment IBoxBeamEndBlockSegment;

#endif 	/* __IBoxBeamEndBlockSegment_FWD_DEFINED__ */


#ifndef __IUGirderSection2EndBlockSegment_FWD_DEFINED__
#define __IUGirderSection2EndBlockSegment_FWD_DEFINED__
typedef interface IUGirderSection2EndBlockSegment IUGirderSection2EndBlockSegment;

#endif 	/* __IUGirderSection2EndBlockSegment_FWD_DEFINED__ */


#ifndef __ITaperedGirderSegment_FWD_DEFINED__
#define __ITaperedGirderSegment_FWD_DEFINED__
typedef interface ITaperedGirderSegment ITaperedGirderSegment;

#endif 	/* __ITaperedGirderSegment_FWD_DEFINED__ */


#ifndef __ISplicedGirderSegment_FWD_DEFINED__
#define __ISplicedGirderSegment_FWD_DEFINED__
typedef interface ISplicedGirderSegment ISplicedGirderSegment;

#endif 	/* __ISplicedGirderSegment_FWD_DEFINED__ */


#ifndef __IFlangedSplicedGirderSegment_FWD_DEFINED__
#define __IFlangedSplicedGirderSegment_FWD_DEFINED__
typedef interface IFlangedSplicedGirderSegment IFlangedSplicedGirderSegment;

#endif 	/* __IFlangedSplicedGirderSegment_FWD_DEFINED__ */


#ifndef __IUSplicedGirderSegment_FWD_DEFINED__
#define __IUSplicedGirderSegment_FWD_DEFINED__
typedef interface IUSplicedGirderSegment IUSplicedGirderSegment;

#endif 	/* __IUSplicedGirderSegment_FWD_DEFINED__ */


#ifndef __IBulbTeeSection_FWD_DEFINED__
#define __IBulbTeeSection_FWD_DEFINED__
typedef interface IBulbTeeSection IBulbTeeSection;

#endif 	/* __IBulbTeeSection_FWD_DEFINED__ */


#ifndef __IThickenedFlangeBulbTeeSegment_FWD_DEFINED__
#define __IThickenedFlangeBulbTeeSegment_FWD_DEFINED__
typedef interface IThickenedFlangeBulbTeeSegment IThickenedFlangeBulbTeeSegment;

#endif 	/* __IThickenedFlangeBulbTeeSegment_FWD_DEFINED__ */


#ifndef __IEnumSegmentItem_FWD_DEFINED__
#define __IEnumSegmentItem_FWD_DEFINED__
typedef interface IEnumSegmentItem IEnumSegmentItem;

#endif 	/* __IEnumSegmentItem_FWD_DEFINED__ */


#ifndef __IColumn_FWD_DEFINED__
#define __IColumn_FWD_DEFINED__
typedef interface IColumn IColumn;

#endif 	/* __IColumn_FWD_DEFINED__ */


#ifndef __ILinearCrossBeam_FWD_DEFINED__
#define __ILinearCrossBeam_FWD_DEFINED__
typedef interface ILinearCrossBeam ILinearCrossBeam;

#endif 	/* __ILinearCrossBeam_FWD_DEFINED__ */


#ifndef __IBearingLayout_FWD_DEFINED__
#define __IBearingLayout_FWD_DEFINED__
typedef interface IBearingLayout IBearingLayout;

#endif 	/* __IBearingLayout_FWD_DEFINED__ */


#ifndef __IBridgePier_FWD_DEFINED__
#define __IBridgePier_FWD_DEFINED__
typedef interface IBridgePier IBridgePier;

#endif 	/* __IBridgePier_FWD_DEFINED__ */


#ifndef __IPierEx_FWD_DEFINED__
#define __IPierEx_FWD_DEFINED__
typedef interface IPierEx IPierEx;

#endif 	/* __IPierEx_FWD_DEFINED__ */


#ifndef __IGirderSection_FWD_DEFINED__
#define __IGirderSection_FWD_DEFINED__
typedef interface IGirderSection IGirderSection;

#endif 	/* __IGirderSection_FWD_DEFINED__ */


#ifndef __IPrestressedGirderSection_FWD_DEFINED__
#define __IPrestressedGirderSection_FWD_DEFINED__
typedef interface IPrestressedGirderSection IPrestressedGirderSection;

#endif 	/* __IPrestressedGirderSection_FWD_DEFINED__ */


#ifndef __IMultiWebSection_FWD_DEFINED__
#define __IMultiWebSection_FWD_DEFINED__
typedef interface IMultiWebSection IMultiWebSection;

#endif 	/* __IMultiWebSection_FWD_DEFINED__ */


#ifndef __IMultiWebSection2_FWD_DEFINED__
#define __IMultiWebSection2_FWD_DEFINED__
typedef interface IMultiWebSection2 IMultiWebSection2;

#endif 	/* __IMultiWebSection2_FWD_DEFINED__ */


#ifndef __INUGirderSection_FWD_DEFINED__
#define __INUGirderSection_FWD_DEFINED__
typedef interface INUGirderSection INUGirderSection;

#endif 	/* __INUGirderSection_FWD_DEFINED__ */


#ifndef __IVoidedSlabSection_FWD_DEFINED__
#define __IVoidedSlabSection_FWD_DEFINED__
typedef interface IVoidedSlabSection IVoidedSlabSection;

#endif 	/* __IVoidedSlabSection_FWD_DEFINED__ */


#ifndef __ITendonSegment_FWD_DEFINED__
#define __ITendonSegment_FWD_DEFINED__
typedef interface ITendonSegment ITendonSegment;

#endif 	/* __ITendonSegment_FWD_DEFINED__ */


#ifndef __ILinearTendonSegment_FWD_DEFINED__
#define __ILinearTendonSegment_FWD_DEFINED__
typedef interface ILinearTendonSegment ILinearTendonSegment;

#endif 	/* __ILinearTendonSegment_FWD_DEFINED__ */


#ifndef __IParabolicTendonSegment_FWD_DEFINED__
#define __IParabolicTendonSegment_FWD_DEFINED__
typedef interface IParabolicTendonSegment IParabolicTendonSegment;

#endif 	/* __IParabolicTendonSegment_FWD_DEFINED__ */


#ifndef __IOffsetTendon_FWD_DEFINED__
#define __IOffsetTendon_FWD_DEFINED__
typedef interface IOffsetTendon IOffsetTendon;

#endif 	/* __IOffsetTendon_FWD_DEFINED__ */


#ifndef __IEnumTendonSegments_FWD_DEFINED__
#define __IEnumTendonSegments_FWD_DEFINED__
typedef interface IEnumTendonSegments IEnumTendonSegments;

#endif 	/* __IEnumTendonSegments_FWD_DEFINED__ */


#ifndef __IEnumTendons_FWD_DEFINED__
#define __IEnumTendons_FWD_DEFINED__
typedef interface IEnumTendons IEnumTendons;

#endif 	/* __IEnumTendons_FWD_DEFINED__ */


#ifndef __ITendonCollection_FWD_DEFINED__
#define __ITendonCollection_FWD_DEFINED__
typedef interface ITendonCollection ITendonCollection;

#endif 	/* __ITendonCollection_FWD_DEFINED__ */


#ifndef __IEnumPiers_FWD_DEFINED__
#define __IEnumPiers_FWD_DEFINED__
typedef interface IEnumPiers IEnumPiers;

#endif 	/* __IEnumPiers_FWD_DEFINED__ */


#ifndef __IPierCollection_FWD_DEFINED__
#define __IPierCollection_FWD_DEFINED__
typedef interface IPierCollection IPierCollection;

#endif 	/* __IPierCollection_FWD_DEFINED__ */


#ifndef __Rebar_FWD_DEFINED__
#define __Rebar_FWD_DEFINED__

#ifdef __cplusplus
typedef class Rebar Rebar;
#else
typedef struct Rebar Rebar;
#endif /* __cplusplus */

#endif 	/* __Rebar_FWD_DEFINED__ */


#ifndef __RebarSectionItem_FWD_DEFINED__
#define __RebarSectionItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class RebarSectionItem RebarSectionItem;
#else
typedef struct RebarSectionItem RebarSectionItem;
#endif /* __cplusplus */

#endif 	/* __RebarSectionItem_FWD_DEFINED__ */


#ifndef __RebarSection_FWD_DEFINED__
#define __RebarSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class RebarSection RebarSection;
#else
typedef struct RebarSection RebarSection;
#endif /* __cplusplus */

#endif 	/* __RebarSection_FWD_DEFINED__ */


#ifndef __RebarRowFacePattern_FWD_DEFINED__
#define __RebarRowFacePattern_FWD_DEFINED__

#ifdef __cplusplus
typedef class RebarRowFacePattern RebarRowFacePattern;
#else
typedef struct RebarRowFacePattern RebarRowFacePattern;
#endif /* __cplusplus */

#endif 	/* __RebarRowFacePattern_FWD_DEFINED__ */


#ifndef __RebarRowPattern_FWD_DEFINED__
#define __RebarRowPattern_FWD_DEFINED__

#ifdef __cplusplus
typedef class RebarRowPattern RebarRowPattern;
#else
typedef struct RebarRowPattern RebarRowPattern;
#endif /* __cplusplus */

#endif 	/* __RebarRowPattern_FWD_DEFINED__ */


#ifndef __CrossBeamRebarPattern_FWD_DEFINED__
#define __CrossBeamRebarPattern_FWD_DEFINED__

#ifdef __cplusplus
typedef class CrossBeamRebarPattern CrossBeamRebarPattern;
#else
typedef struct CrossBeamRebarPattern CrossBeamRebarPattern;
#endif /* __cplusplus */

#endif 	/* __CrossBeamRebarPattern_FWD_DEFINED__ */


#ifndef __RebarLayout_FWD_DEFINED__
#define __RebarLayout_FWD_DEFINED__

#ifdef __cplusplus
typedef class RebarLayout RebarLayout;
#else
typedef struct RebarLayout RebarLayout;
#endif /* __cplusplus */

#endif 	/* __RebarLayout_FWD_DEFINED__ */


#ifndef __FixedLengthRebarLayoutItem_FWD_DEFINED__
#define __FixedLengthRebarLayoutItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class FixedLengthRebarLayoutItem FixedLengthRebarLayoutItem;
#else
typedef struct FixedLengthRebarLayoutItem FixedLengthRebarLayoutItem;
#endif /* __cplusplus */

#endif 	/* __FixedLengthRebarLayoutItem_FWD_DEFINED__ */


#ifndef __BridgeDeckRebarPattern_FWD_DEFINED__
#define __BridgeDeckRebarPattern_FWD_DEFINED__

#ifdef __cplusplus
typedef class BridgeDeckRebarPattern BridgeDeckRebarPattern;
#else
typedef struct BridgeDeckRebarPattern BridgeDeckRebarPattern;
#endif /* __cplusplus */

#endif 	/* __BridgeDeckRebarPattern_FWD_DEFINED__ */


#ifndef __BridgeDeckRebarLayoutItem_FWD_DEFINED__
#define __BridgeDeckRebarLayoutItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class BridgeDeckRebarLayoutItem BridgeDeckRebarLayoutItem;
#else
typedef struct BridgeDeckRebarLayoutItem BridgeDeckRebarLayoutItem;
#endif /* __cplusplus */

#endif 	/* __BridgeDeckRebarLayoutItem_FWD_DEFINED__ */


#ifndef __NegativeMomentBridgeDeckRebarLayoutItem_FWD_DEFINED__
#define __NegativeMomentBridgeDeckRebarLayoutItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class NegativeMomentBridgeDeckRebarLayoutItem NegativeMomentBridgeDeckRebarLayoutItem;
#else
typedef struct NegativeMomentBridgeDeckRebarLayoutItem NegativeMomentBridgeDeckRebarLayoutItem;
#endif /* __cplusplus */

#endif 	/* __NegativeMomentBridgeDeckRebarLayoutItem_FWD_DEFINED__ */


#ifndef __RebarFactory_FWD_DEFINED__
#define __RebarFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class RebarFactory RebarFactory;
#else
typedef struct RebarFactory RebarFactory;
#endif /* __cplusplus */

#endif 	/* __RebarFactory_FWD_DEFINED__ */


#ifndef __GenericBridge_FWD_DEFINED__
#define __GenericBridge_FWD_DEFINED__

#ifdef __cplusplus
typedef class GenericBridge GenericBridge;
#else
typedef struct GenericBridge GenericBridge;
#endif /* __cplusplus */

#endif 	/* __GenericBridge_FWD_DEFINED__ */


#ifndef __BridgePier_FWD_DEFINED__
#define __BridgePier_FWD_DEFINED__

#ifdef __cplusplus
typedef class BridgePier BridgePier;
#else
typedef struct BridgePier BridgePier;
#endif /* __cplusplus */

#endif 	/* __BridgePier_FWD_DEFINED__ */


#ifndef __PierCollection_FWD_DEFINED__
#define __PierCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class PierCollection PierCollection;
#else
typedef struct PierCollection PierCollection;
#endif /* __cplusplus */

#endif 	/* __PierCollection_FWD_DEFINED__ */


#ifndef __SuperstructureMember_FWD_DEFINED__
#define __SuperstructureMember_FWD_DEFINED__

#ifdef __cplusplus
typedef class SuperstructureMember SuperstructureMember;
#else
typedef struct SuperstructureMember SuperstructureMember;
#endif /* __cplusplus */

#endif 	/* __SuperstructureMember_FWD_DEFINED__ */


#ifndef __FlangedGirderEndBlockSegment_FWD_DEFINED__
#define __FlangedGirderEndBlockSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class FlangedGirderEndBlockSegment FlangedGirderEndBlockSegment;
#else
typedef struct FlangedGirderEndBlockSegment FlangedGirderEndBlockSegment;
#endif /* __cplusplus */

#endif 	/* __FlangedGirderEndBlockSegment_FWD_DEFINED__ */


#ifndef __VoidedSlabEndBlockSegment_FWD_DEFINED__
#define __VoidedSlabEndBlockSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class VoidedSlabEndBlockSegment VoidedSlabEndBlockSegment;
#else
typedef struct VoidedSlabEndBlockSegment VoidedSlabEndBlockSegment;
#endif /* __cplusplus */

#endif 	/* __VoidedSlabEndBlockSegment_FWD_DEFINED__ */


#ifndef __DeckedSlabBeamEndBlockSegment_FWD_DEFINED__
#define __DeckedSlabBeamEndBlockSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class DeckedSlabBeamEndBlockSegment DeckedSlabBeamEndBlockSegment;
#else
typedef struct DeckedSlabBeamEndBlockSegment DeckedSlabBeamEndBlockSegment;
#endif /* __cplusplus */

#endif 	/* __DeckedSlabBeamEndBlockSegment_FWD_DEFINED__ */


#ifndef __BoxBeamEndBlockSegment_FWD_DEFINED__
#define __BoxBeamEndBlockSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class BoxBeamEndBlockSegment BoxBeamEndBlockSegment;
#else
typedef struct BoxBeamEndBlockSegment BoxBeamEndBlockSegment;
#endif /* __cplusplus */

#endif 	/* __BoxBeamEndBlockSegment_FWD_DEFINED__ */


#ifndef __UGirderSection2EndBlockSegment_FWD_DEFINED__
#define __UGirderSection2EndBlockSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class UGirderSection2EndBlockSegment UGirderSection2EndBlockSegment;
#else
typedef struct UGirderSection2EndBlockSegment UGirderSection2EndBlockSegment;
#endif /* __cplusplus */

#endif 	/* __UGirderSection2EndBlockSegment_FWD_DEFINED__ */


#ifndef __TaperedGirderSegment_FWD_DEFINED__
#define __TaperedGirderSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class TaperedGirderSegment TaperedGirderSegment;
#else
typedef struct TaperedGirderSegment TaperedGirderSegment;
#endif /* __cplusplus */

#endif 	/* __TaperedGirderSegment_FWD_DEFINED__ */


#ifndef __ThickenedFlangeBulbTeeSegment_FWD_DEFINED__
#define __ThickenedFlangeBulbTeeSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class ThickenedFlangeBulbTeeSegment ThickenedFlangeBulbTeeSegment;
#else
typedef struct ThickenedFlangeBulbTeeSegment ThickenedFlangeBulbTeeSegment;
#endif /* __cplusplus */

#endif 	/* __ThickenedFlangeBulbTeeSegment_FWD_DEFINED__ */


#ifndef __PrismaticSegment_FWD_DEFINED__
#define __PrismaticSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrismaticSegment PrismaticSegment;
#else
typedef struct PrismaticSegment PrismaticSegment;
#endif /* __cplusplus */

#endif 	/* __PrismaticSegment_FWD_DEFINED__ */


#ifndef __PrismaticSuperstructureMemberSegment_FWD_DEFINED__
#define __PrismaticSuperstructureMemberSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrismaticSuperstructureMemberSegment PrismaticSuperstructureMemberSegment;
#else
typedef struct PrismaticSuperstructureMemberSegment PrismaticSuperstructureMemberSegment;
#endif /* __cplusplus */

#endif 	/* __PrismaticSuperstructureMemberSegment_FWD_DEFINED__ */


#ifndef __FlangedSplicedGirderSegment_FWD_DEFINED__
#define __FlangedSplicedGirderSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class FlangedSplicedGirderSegment FlangedSplicedGirderSegment;
#else
typedef struct FlangedSplicedGirderSegment FlangedSplicedGirderSegment;
#endif /* __cplusplus */

#endif 	/* __FlangedSplicedGirderSegment_FWD_DEFINED__ */


#ifndef __USplicedGirderSegment_FWD_DEFINED__
#define __USplicedGirderSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class USplicedGirderSegment USplicedGirderSegment;
#else
typedef struct USplicedGirderSegment USplicedGirderSegment;
#endif /* __cplusplus */

#endif 	/* __USplicedGirderSegment_FWD_DEFINED__ */


#ifndef __NUSplicedGirderSegment_FWD_DEFINED__
#define __NUSplicedGirderSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class NUSplicedGirderSegment NUSplicedGirderSegment;
#else
typedef struct NUSplicedGirderSegment NUSplicedGirderSegment;
#endif /* __cplusplus */

#endif 	/* __NUSplicedGirderSegment_FWD_DEFINED__ */


#ifndef __SegmentItem_FWD_DEFINED__
#define __SegmentItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class SegmentItem SegmentItem;
#else
typedef struct SegmentItem SegmentItem;
#endif /* __cplusplus */

#endif 	/* __SegmentItem_FWD_DEFINED__ */


#ifndef __FilteredSegmentCollection_FWD_DEFINED__
#define __FilteredSegmentCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class FilteredSegmentCollection FilteredSegmentCollection;
#else
typedef struct FilteredSegmentCollection FilteredSegmentCollection;
#endif /* __cplusplus */

#endif 	/* __FilteredSegmentCollection_FWD_DEFINED__ */


#ifndef __SuperstructureMemberCollection_FWD_DEFINED__
#define __SuperstructureMemberCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class SuperstructureMemberCollection SuperstructureMemberCollection;
#else
typedef struct SuperstructureMemberCollection SuperstructureMemberCollection;
#endif /* __cplusplus */

#endif 	/* __SuperstructureMemberCollection_FWD_DEFINED__ */


#ifndef __Column_FWD_DEFINED__
#define __Column_FWD_DEFINED__

#ifdef __cplusplus
typedef class Column Column;
#else
typedef struct Column Column;
#endif /* __cplusplus */

#endif 	/* __Column_FWD_DEFINED__ */


#ifndef __ColumnLayout_FWD_DEFINED__
#define __ColumnLayout_FWD_DEFINED__

#ifdef __cplusplus
typedef class ColumnLayout ColumnLayout;
#else
typedef struct ColumnLayout ColumnLayout;
#endif /* __cplusplus */

#endif 	/* __ColumnLayout_FWD_DEFINED__ */


#ifndef __BearingLayout_FWD_DEFINED__
#define __BearingLayout_FWD_DEFINED__

#ifdef __cplusplus
typedef class BearingLayout BearingLayout;
#else
typedef struct BearingLayout BearingLayout;
#endif /* __cplusplus */

#endif 	/* __BearingLayout_FWD_DEFINED__ */


#ifndef __LinearCrossBeam_FWD_DEFINED__
#define __LinearCrossBeam_FWD_DEFINED__

#ifdef __cplusplus
typedef class LinearCrossBeam LinearCrossBeam;
#else
typedef struct LinearCrossBeam LinearCrossBeam;
#endif /* __cplusplus */

#endif 	/* __LinearCrossBeam_FWD_DEFINED__ */


#ifndef __Pier_FWD_DEFINED__
#define __Pier_FWD_DEFINED__

#ifdef __cplusplus
typedef class Pier Pier;
#else
typedef struct Pier Pier;
#endif /* __cplusplus */

#endif 	/* __Pier_FWD_DEFINED__ */


#ifndef __Material_FWD_DEFINED__
#define __Material_FWD_DEFINED__

#ifdef __cplusplus
typedef class Material Material;
#else
typedef struct Material Material;
#endif /* __cplusplus */

#endif 	/* __Material_FWD_DEFINED__ */


#ifndef __CastSlab_FWD_DEFINED__
#define __CastSlab_FWD_DEFINED__

#ifdef __cplusplus
typedef class CastSlab CastSlab;
#else
typedef struct CastSlab CastSlab;
#endif /* __cplusplus */

#endif 	/* __CastSlab_FWD_DEFINED__ */


#ifndef __AlignmentOffsetStrategy_FWD_DEFINED__
#define __AlignmentOffsetStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class AlignmentOffsetStrategy AlignmentOffsetStrategy;
#else
typedef struct AlignmentOffsetStrategy AlignmentOffsetStrategy;
#endif /* __cplusplus */

#endif 	/* __AlignmentOffsetStrategy_FWD_DEFINED__ */


#ifndef __EdgePathStrategy_FWD_DEFINED__
#define __EdgePathStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class EdgePathStrategy EdgePathStrategy;
#else
typedef struct EdgePathStrategy EdgePathStrategy;
#endif /* __cplusplus */

#endif 	/* __EdgePathStrategy_FWD_DEFINED__ */


#ifndef __PrecastSlab_FWD_DEFINED__
#define __PrecastSlab_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrecastSlab PrecastSlab;
#else
typedef struct PrecastSlab PrecastSlab;
#endif /* __cplusplus */

#endif 	/* __PrecastSlab_FWD_DEFINED__ */


#ifndef __OverlaySlab_FWD_DEFINED__
#define __OverlaySlab_FWD_DEFINED__

#ifdef __cplusplus
typedef class OverlaySlab OverlaySlab;
#else
typedef struct OverlaySlab OverlaySlab;
#endif /* __cplusplus */

#endif 	/* __OverlaySlab_FWD_DEFINED__ */


#ifndef __FlangedGirderSection_FWD_DEFINED__
#define __FlangedGirderSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class FlangedGirderSection FlangedGirderSection;
#else
typedef struct FlangedGirderSection FlangedGirderSection;
#endif /* __cplusplus */

#endif 	/* __FlangedGirderSection_FWD_DEFINED__ */


#ifndef __BulbTeeSection_FWD_DEFINED__
#define __BulbTeeSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class BulbTeeSection BulbTeeSection;
#else
typedef struct BulbTeeSection BulbTeeSection;
#endif /* __cplusplus */

#endif 	/* __BulbTeeSection_FWD_DEFINED__ */


#ifndef __MultiWebSection_FWD_DEFINED__
#define __MultiWebSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class MultiWebSection MultiWebSection;
#else
typedef struct MultiWebSection MultiWebSection;
#endif /* __cplusplus */

#endif 	/* __MultiWebSection_FWD_DEFINED__ */


#ifndef __MultiWebSection2_FWD_DEFINED__
#define __MultiWebSection2_FWD_DEFINED__

#ifdef __cplusplus
typedef class MultiWebSection2 MultiWebSection2;
#else
typedef struct MultiWebSection2 MultiWebSection2;
#endif /* __cplusplus */

#endif 	/* __MultiWebSection2_FWD_DEFINED__ */


#ifndef __NUGirderSection_FWD_DEFINED__
#define __NUGirderSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class NUGirderSection NUGirderSection;
#else
typedef struct NUGirderSection NUGirderSection;
#endif /* __cplusplus */

#endif 	/* __NUGirderSection_FWD_DEFINED__ */


#ifndef __UGirderSection_FWD_DEFINED__
#define __UGirderSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class UGirderSection UGirderSection;
#else
typedef struct UGirderSection UGirderSection;
#endif /* __cplusplus */

#endif 	/* __UGirderSection_FWD_DEFINED__ */


#ifndef __UGirderSection2_FWD_DEFINED__
#define __UGirderSection2_FWD_DEFINED__

#ifdef __cplusplus
typedef class UGirderSection2 UGirderSection2;
#else
typedef struct UGirderSection2 UGirderSection2;
#endif /* __cplusplus */

#endif 	/* __UGirderSection2_FWD_DEFINED__ */


#ifndef __VoidedSlabSection_FWD_DEFINED__
#define __VoidedSlabSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class VoidedSlabSection VoidedSlabSection;
#else
typedef struct VoidedSlabSection VoidedSlabSection;
#endif /* __cplusplus */

#endif 	/* __VoidedSlabSection_FWD_DEFINED__ */


#ifndef __VoidedSlabSection2_FWD_DEFINED__
#define __VoidedSlabSection2_FWD_DEFINED__

#ifdef __cplusplus
typedef class VoidedSlabSection2 VoidedSlabSection2;
#else
typedef struct VoidedSlabSection2 VoidedSlabSection2;
#endif /* __cplusplus */

#endif 	/* __VoidedSlabSection2_FWD_DEFINED__ */


#ifndef __DeckedSlabBeamSection_FWD_DEFINED__
#define __DeckedSlabBeamSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class DeckedSlabBeamSection DeckedSlabBeamSection;
#else
typedef struct DeckedSlabBeamSection DeckedSlabBeamSection;
#endif /* __cplusplus */

#endif 	/* __DeckedSlabBeamSection_FWD_DEFINED__ */


#ifndef __BoxBeamSection_FWD_DEFINED__
#define __BoxBeamSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class BoxBeamSection BoxBeamSection;
#else
typedef struct BoxBeamSection BoxBeamSection;
#endif /* __cplusplus */

#endif 	/* __BoxBeamSection_FWD_DEFINED__ */


#ifndef __GenericBarrier_FWD_DEFINED__
#define __GenericBarrier_FWD_DEFINED__

#ifdef __cplusplus
typedef class GenericBarrier GenericBarrier;
#else
typedef struct GenericBarrier GenericBarrier;
#endif /* __cplusplus */

#endif 	/* __GenericBarrier_FWD_DEFINED__ */


#ifndef __FShapeBarrier_FWD_DEFINED__
#define __FShapeBarrier_FWD_DEFINED__

#ifdef __cplusplus
typedef class FShapeBarrier FShapeBarrier;
#else
typedef struct FShapeBarrier FShapeBarrier;
#endif /* __cplusplus */

#endif 	/* __FShapeBarrier_FWD_DEFINED__ */


#ifndef __SidewalkBarrier_FWD_DEFINED__
#define __SidewalkBarrier_FWD_DEFINED__

#ifdef __cplusplus
typedef class SidewalkBarrier SidewalkBarrier;
#else
typedef struct SidewalkBarrier SidewalkBarrier;
#endif /* __cplusplus */

#endif 	/* __SidewalkBarrier_FWD_DEFINED__ */


#ifndef __LinearTendonSegment_FWD_DEFINED__
#define __LinearTendonSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class LinearTendonSegment LinearTendonSegment;
#else
typedef struct LinearTendonSegment LinearTendonSegment;
#endif /* __cplusplus */

#endif 	/* __LinearTendonSegment_FWD_DEFINED__ */


#ifndef __ParabolicTendonSegment_FWD_DEFINED__
#define __ParabolicTendonSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class ParabolicTendonSegment ParabolicTendonSegment;
#else
typedef struct ParabolicTendonSegment ParabolicTendonSegment;
#endif /* __cplusplus */

#endif 	/* __ParabolicTendonSegment_FWD_DEFINED__ */


#ifndef __Tendon_FWD_DEFINED__
#define __Tendon_FWD_DEFINED__

#ifdef __cplusplus
typedef class Tendon Tendon;
#else
typedef struct Tendon Tendon;
#endif /* __cplusplus */

#endif 	/* __Tendon_FWD_DEFINED__ */


#ifndef __OffsetTendon_FWD_DEFINED__
#define __OffsetTendon_FWD_DEFINED__

#ifdef __cplusplus
typedef class OffsetTendon OffsetTendon;
#else
typedef struct OffsetTendon OffsetTendon;
#endif /* __cplusplus */

#endif 	/* __OffsetTendon_FWD_DEFINED__ */


#ifndef __TendonCollection_FWD_DEFINED__
#define __TendonCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class TendonCollection TendonCollection;
#else
typedef struct TendonCollection TendonCollection;
#endif /* __cplusplus */

#endif 	/* __TendonCollection_FWD_DEFINED__ */


#ifndef __PrestressingStrand_FWD_DEFINED__
#define __PrestressingStrand_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrestressingStrand PrestressingStrand;
#else
typedef struct PrestressingStrand PrestressingStrand;
#endif /* __cplusplus */

#endif 	/* __PrestressingStrand_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"
#include "WBFLGeometry.h"
#include "WBFLLoading.h"
#include "WBFLCogo.h"
#include "WBFLBridgeGeometry.h"
#include "WBFLSections.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLGenericBridge_0000_0000 */
/* [local] */ 

#define GB_E_NUMGIRDERLINES               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,512)
#define GB_E_PIERINDEX                    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,513)
#define GB_E_SPANINDEX                    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,514)
#define GB_E_SPACEINDEX                   MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,515)
#define GB_E_SPACING                      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,516)
#define GB_E_AREA                         MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,517)
#define GB_E_MOMENTOFINERTIA              MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,518)
#define GB_E_MODULUSOFELASTICITY          MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,519)
#define GB_E_DENSITY                      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,520)
#define GB_E_WIDTH                        MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,521)
#define GB_E_THERMALCOEFF                 MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,522)
#define GB_E_LENGTH                       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,523)
#define GB_E_CANTLINKSOURCE               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,524)
#define GB_E_CANTLINKTOSELF               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,525)
#define GB_E_CANTEDITLINKTARGET           MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,526)
#define GB_E_NO_SEGMENTS_FOR_STAGE        MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,527)
#define GB_E_LOCATION_OUT_OF_RANGE        MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,528)
#define GB_E_LESS_THAN_MIN_GIRDER_LINES   MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,529)
#define GB_E_STAGE_NOT_FOUND              MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,530)
#define GB_E_LOCATION                     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,531)
#define GB_E_INVALID_NAME                 MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,532)
#define GB_E_DUPLICATENAME                MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,533)
#define GB_E_FRACTIONAL_EXPECTED          MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,534)
#define GB_E_ABSOLUTE_EXPECTED            MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,535)
#define GB_E_ID_IN_USE                    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,536)
#define GB_E_OVERHANG                     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,537)
#define GB_E_LESS_THAN_MIN_COLUMNS        MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,538)


extern RPC_IF_HANDLE __MIDL_itf_WBFLGenericBridge_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLGenericBridge_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLGenericBridge_LIBRARY_DEFINED__
#define __WBFLGenericBridge_LIBRARY_DEFINED__

/* library WBFLGenericBridge */
/* [helpstring][version][uuid] */ 
















typedef /* [public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("28251F79-72F8-4d9d-85EB-55426AC53CC6") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0001
    {
        rroRight	= 0,
        rroHCenter	= ( rroRight + 1 ) ,
        rroLeft	= ( rroHCenter + 1 ) ,
        rroDown	= ( rroLeft + 1 ) ,
        rroVCenter	= ( rroDown + 1 ) ,
        rroUp	= ( rroVCenter + 1 ) 
    } 	RebarRowOrientation;

typedef /* [public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("89A73421-B02A-4b19-B2B0-FC81FFC31494") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0002
    {
        xbTop	= 0,
        xbTopLowerXBeam	= ( xbTop + 1 ) ,
        xbBottom	= ( xbTopLowerXBeam + 1 ) 
    } 	CrossBeamRebarDatum;

typedef /* [public][public][uuid][helpstring][public] */  DECLSPEC_UUID("6033AA61-EB06-469e-8743-CFA09545FE96") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0003
    {
        msA615	= 0,
        msA706	= ( msA615 + 1 ) ,
        msA1035	= ( msA706 + 1 ) 
    } 	MaterialSpec;

typedef /* [public][public][uuid][helpstring][public] */  DECLSPEC_UUID("3DB21D7F-CA67-453a-9E62-FE9989BBBEA7") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0004
    {
        Grade40	= 0,
        Grade60	= ( Grade40 + 1 ) ,
        Grade75	= ( Grade60 + 1 ) ,
        Grade80	= ( Grade75 + 1 ) ,
        Grade100	= ( Grade80 + 1 ) 
    } 	RebarGrade;

typedef /* [public][public][uuid][helpstring][public] */  DECLSPEC_UUID("FCC0993E-988B-4bf2-A708-094AC20B51BA") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0005
    {
        bs3	= 3,
        bs4	= 4,
        bs5	= 5,
        bs6	= 6,
        bs7	= 7,
        bs8	= 8,
        bs9	= 9,
        bs10	= 10,
        bs11	= 11,
        bs14	= 14,
        bs18	= 18
    } 	BarSize;

typedef /* [public][public][public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("83EDBCC7-D8A1-4c1a-A0FF-AE2364CC003F") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0006
    {
        htNone	= 0,
        ht90	= ( htNone + 1 ) ,
        ht135	= ( ht90 + 1 ) ,
        ht180	= ( ht135 + 1 ) 
    } 	HookType;

typedef /* [public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("F7126E78-8EDF-4af7-9CFA-59C2D1F6C6B1") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0007
    {
        swpBetweenBarriers	= 0,
        swpBeneathBarriers	= 1
    } 	SidewalkPositionType;

typedef /* [public][uuid][helpstring][public] */  DECLSPEC_UUID("8C1F0B6B-3B40-4fe2-9C66-446CCA864D2F") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0008
    {
        qcbBefore	= 0,
        qcbAfter	= 1
    } 	PositionType;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("A81D53DF-CEBD-4865-8D20-E0CD40DEAAE2") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0009
    {
        qcbLeft	= 0,
        qcbRight	= 1
    } 	DirectionType;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("F0FF5886-CD4D-41B7-A21D-EBB9E14D502A") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0010
    {
        ltLeftExteriorGirder	= 0,
        ltInteriorGirder	= 1,
        ltRightExteriorGirder	= 2
    } 	LocationType;

typedef /* [public][uuid][helpstring][public] */  DECLSPEC_UUID("E6935478-50D4-4399-B21F-45779FD71638") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0011
    {
        ctRoller	= 0,
        ctPinned	= 1,
        ctIntegral	= 2,
        ctHinged	= 3,
        ctHingedIntegral	= 4
    } 	ConnectivityType;

typedef /* [public][uuid][helpstring][public] */  DECLSPEC_UUID("5C89BEE6-F3D8-4b53-BE40-ED22204221EA") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0012
    {
        otAlignment	= 0,
        otBridge	= 1
    } 	OffsetDatumType;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("692EA3D4-3C08-4890-BBAC-702E7734E5B0") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0013
    {
        rtNone	= 0,
        rtHinged	= 1
    } 	ReleaseType;

typedef /* [public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("502711DE-D90C-4fb3-A117-15333D8C7EE5") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0014
    {
        dotNone	= 0,
        dotTopTopFlange	= 1,
        dotBottomTopFlange	= 2
    } 	DeckOverhangTaper;

typedef /* [public][uuid][helpstring][public] */  DECLSPEC_UUID("426B4471-70BD-472d-B5CD-24770B37738D") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0015
    {
        pptLeft	= 1,
        pptAlignment	= 2,
        pptRight	= 3,
        pptBridge	= 4
    } 	PierPointType;

typedef /* [public][public][public][public][public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("0AF9E9B3-BD55-4656-930E-9F1A528574F7") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0016
    {
        tmTendon	= 1,
        tmPath	= 2
    } 	TendonMeasure;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("7DA23C65-4705-4351-81D9-08AF102984EF") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0017
    {
        jeLeft	= 0,
        jeRight	= ( jeLeft + 1 ) ,
        jeBoth	= ( jeRight + 1 ) 
    } 	JackingEndType;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("703D2C89-8DC1-44c5-A8EE-2797F823232A") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0018
    {
        Grade250	= 0x1,
        Grade270	= 0x2
    } 	StrandGrade;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("11E75BB6-8E13-4ac2-A608-F13FAC0577D9") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0019
    {
        LowRelaxation	= 0x4,
        StressRelieved	= 0x8
    } 	StrandType;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("B853E36E-FD4B-4e20-A8B0-2EC1E605EB97") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0020
    {
        D2500	= 0x10,
        D3125	= 0x20,
        D3750	= 0x40,
        D4375	= 0x80,
        D5000	= 0x100,
        D6000	= 0x200,
        D7000	= 0x400,
        D5200	= 0x800,
        D6200	= 0x1000
    } 	StrandSize;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("A6EE8250-D1D0-4ade-9C20-BA286A4215FA") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0021
    {
        None	= 0x10000,
        SmoothEpoxy	= 0x20000,
        GritEpoxy	= 0x40000
    } 	StrandCoating;

typedef /* [public][public][uuid][helpstring][public] */  DECLSPEC_UUID("E32B1A87-2444-42e3-878E-CD5742837900") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0022
    {
        sdVertical	= 0,
        sdHorizontal	= ( sdVertical + 1 ) 
    } 	SplittingDirection;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("35DFB6BF-F01C-45E9-8E05-A88A78AE934B") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0023
    {
        sztLeftPrismatic	= 0,
        sztLeftTapered	= ( sztLeftPrismatic + 1 ) ,
        sztRightTapered	= ( sztLeftTapered + 1 ) ,
        sztRightPrismatic	= ( sztRightTapered + 1 ) 
    } 	SegmentZoneType;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("C347973D-CC50-4AE0-81FC-7FD0F1438531") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0024
    {
        svtLinear	= 0,
        svtParabolic	= ( svtLinear + 1 ) ,
        svtDoubleLinear	= ( svtParabolic + 1 ) ,
        svtDoubleParabolic	= ( svtDoubleLinear + 1 ) ,
        svtNone	= ( svtDoubleParabolic + 1 ) 
    } 	SegmentVariationType;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("623C57F0-4C2E-48e8-A100-E550AE2B373F") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0025
    {
        ptContinuous	= 0,
        ptIntegral	= ( ptContinuous + 1 ) ,
        ptExpansion	= ( ptIntegral + 1 ) 
    } 	PierType;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("CC8AAA13-06C0-4bcc-9183-2EF8B145EB65") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0026
    {
        clmNormalToAlignment	= 0,
        clmPlaneOfPier	= ( clmNormalToAlignment + 1 ) 
    } 	CurbLineMeasurementType;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("247F2AEF-880D-4236-ADE2-041A6CE96E64") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0027
    {
        ftTopFace	= 0,
        ftBottomFace	= ( ftTopFace + 1 ) 
    } 	FaceType;

typedef /* [public][public][uuid][helpstring][public] */  DECLSPEC_UUID("8B252C51-C3E7-4533-9A6A-CC04540E3F77") 
enum __MIDL___MIDL_itf_WBFLGenericBridge_0000_0000_0028
    {
        xblTopUpperXBeam	= 0,
        xblTopLowerXBeam	= ( xblTopUpperXBeam + 1 ) ,
        xblBottomXBeam	= ( xblTopLowerXBeam + 1 ) 
    } 	XBeamLocation;


EXTERN_C const IID LIBID_WBFLGenericBridge;

#ifndef __IRebarLayoutItem_INTERFACE_DEFINED__
#define __IRebarLayoutItem_INTERFACE_DEFINED__

/* interface IRebarLayoutItem */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRebarLayoutItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("63465C7F-7036-43c3-95C1-D49A13271A68")
    IRebarLayoutItem : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ContainsLocation( 
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Start( 
            /* [retval][out] */ Float64 *start) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IRebarPattern **pattern) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddRebarPattern( 
            /* [in] */ IRebarPattern *pattern) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumRebarPatterns( 
            /* [retval][out] */ IEnumRebarPatterns **enumRebarPatterns) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRebarLayoutItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRebarLayoutItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRebarLayoutItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRebarLayoutItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ContainsLocation )( 
            IRebarLayoutItem * This,
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            IRebarLayoutItem * This,
            /* [retval][out] */ Float64 *start);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IRebarLayoutItem * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IRebarLayoutItem * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IRebarLayoutItem * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IRebarPattern **pattern);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddRebarPattern )( 
            IRebarLayoutItem * This,
            /* [in] */ IRebarPattern *pattern);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IRebarLayoutItem * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumRebarPatterns )( 
            IRebarLayoutItem * This,
            /* [retval][out] */ IEnumRebarPatterns **enumRebarPatterns);
        
        END_INTERFACE
    } IRebarLayoutItemVtbl;

    interface IRebarLayoutItem
    {
        CONST_VTBL struct IRebarLayoutItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRebarLayoutItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRebarLayoutItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRebarLayoutItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRebarLayoutItem_ContainsLocation(This,distFromStart,bResult)	\
    ( (This)->lpVtbl -> ContainsLocation(This,distFromStart,bResult) ) 

#define IRebarLayoutItem_get_Start(This,start)	\
    ( (This)->lpVtbl -> get_Start(This,start) ) 

#define IRebarLayoutItem_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define IRebarLayoutItem_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IRebarLayoutItem_get_Item(This,idx,pattern)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pattern) ) 

#define IRebarLayoutItem_AddRebarPattern(This,pattern)	\
    ( (This)->lpVtbl -> AddRebarPattern(This,pattern) ) 

#define IRebarLayoutItem_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IRebarLayoutItem_get__EnumRebarPatterns(This,enumRebarPatterns)	\
    ( (This)->lpVtbl -> get__EnumRebarPatterns(This,enumRebarPatterns) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRebarLayoutItem_INTERFACE_DEFINED__ */


#ifndef __IBridgeDeckRebarLayoutItem_INTERFACE_DEFINED__
#define __IBridgeDeckRebarLayoutItem_INTERFACE_DEFINED__

/* interface IBridgeDeckRebarLayoutItem */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBridgeDeckRebarLayoutItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D9CDC505-C445-4547-8C36-D781C1692EF6")
    IBridgeDeckRebarLayoutItem : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ContainsLocation( 
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 offset,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Start( 
            /* [retval][out] */ Float64 *start) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IBridgeDeckRebarPattern **pattern) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddRebarPattern( 
            /* [in] */ IBridgeDeckRebarPattern *pattern) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumRebarPatterns( 
            /* [retval][out] */ IEnumBridgeDeckRebarPatterns **enumRebarPatterns) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Bridge( 
            /* [in] */ IGenericBridge *pBridge) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBridgeDeckRebarLayoutItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBridgeDeckRebarLayoutItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBridgeDeckRebarLayoutItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBridgeDeckRebarLayoutItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ContainsLocation )( 
            IBridgeDeckRebarLayoutItem * This,
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 offset,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            IBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ Float64 *start);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IBridgeDeckRebarLayoutItem * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IBridgeDeckRebarPattern **pattern);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddRebarPattern )( 
            IBridgeDeckRebarLayoutItem * This,
            /* [in] */ IBridgeDeckRebarPattern *pattern);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumRebarPatterns )( 
            IBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ IEnumBridgeDeckRebarPatterns **enumRebarPatterns);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Bridge )( 
            IBridgeDeckRebarLayoutItem * This,
            /* [in] */ IGenericBridge *pBridge);
        
        END_INTERFACE
    } IBridgeDeckRebarLayoutItemVtbl;

    interface IBridgeDeckRebarLayoutItem
    {
        CONST_VTBL struct IBridgeDeckRebarLayoutItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBridgeDeckRebarLayoutItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBridgeDeckRebarLayoutItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBridgeDeckRebarLayoutItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBridgeDeckRebarLayoutItem_ContainsLocation(This,distFromStart,offset,bResult)	\
    ( (This)->lpVtbl -> ContainsLocation(This,distFromStart,offset,bResult) ) 

#define IBridgeDeckRebarLayoutItem_get_Start(This,start)	\
    ( (This)->lpVtbl -> get_Start(This,start) ) 

#define IBridgeDeckRebarLayoutItem_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define IBridgeDeckRebarLayoutItem_get_Item(This,idx,pattern)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pattern) ) 

#define IBridgeDeckRebarLayoutItem_AddRebarPattern(This,pattern)	\
    ( (This)->lpVtbl -> AddRebarPattern(This,pattern) ) 

#define IBridgeDeckRebarLayoutItem_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IBridgeDeckRebarLayoutItem_get__EnumRebarPatterns(This,enumRebarPatterns)	\
    ( (This)->lpVtbl -> get__EnumRebarPatterns(This,enumRebarPatterns) ) 

#define IBridgeDeckRebarLayoutItem_putref_Bridge(This,pBridge)	\
    ( (This)->lpVtbl -> putref_Bridge(This,pBridge) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBridgeDeckRebarLayoutItem_INTERFACE_DEFINED__ */


#ifndef __IGenericBridge_INTERFACE_DEFINED__
#define __IGenericBridge_INTERFACE_DEFINED__

/* interface IGenericBridge */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGenericBridge;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("542278AA-5049-40B6-9AB1-FC63C15410B0")
    IGenericBridge : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BridgeGeometry( 
            /* [retval][out] */ IBridgeGeometry **bridgeGeometry) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Alignment( 
            /* [retval][out] */ IAlignment **ppAlignment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Piers( 
            /* [retval][out] */ IPierCollection **piers) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SpanLength( 
            /* [in] */ SpanIndexType spanIdx,
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Deck( 
            /* [in] */ IBridgeDeck *deck) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Deck( 
            /* [retval][out] */ IBridgeDeck **deck) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftBarrier( 
            /* [retval][out] */ ISidewalkBarrier **barrier) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_LeftBarrier( 
            /* [in] */ ISidewalkBarrier *barrier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightBarrier( 
            /* [retval][out] */ ISidewalkBarrier **barrier) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_RightBarrier( 
            /* [in] */ ISidewalkBarrier *barrier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WearingSurfaceStage( 
            /* [retval][out] */ StageIndexType *stage) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WearingSurfaceStage( 
            /* [in] */ StageIndexType stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WearingSurfaceDepth( 
            /* [retval][out] */ Float64 *d) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WearingSurfaceDepth( 
            /* [in] */ Float64 d) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WearingSurfaceDensity( 
            /* [retval][out] */ Float64 *d) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WearingSurfaceDensity( 
            /* [in] */ Float64 d) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SacrificialDepthStage( 
            /* [retval][out] */ StageIndexType *stage) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SacrificialDepthStage( 
            /* [in] */ StageIndexType stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SacrificialDepth( 
            /* [retval][out] */ Float64 *depth) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SacrificialDepth( 
            /* [in] */ Float64 depth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateSuperstructureMember( 
            /* [in] */ GirderIDType id,
            /* [in] */ LocationType locationType,
            /* [retval][out] */ ISuperstructureMember **ppMbr) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SuperstructureMember( 
            /* [in] */ GirderIDType id,
            /* [retval][out] */ ISuperstructureMember **ppMbr) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumSuperstructureMembers( 
            /* [retval][out] */ IEnumSuperstructureMembers **enumSSMbrs) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateBridgeModel( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGenericBridgeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGenericBridge * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGenericBridge * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGenericBridge * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BridgeGeometry )( 
            IGenericBridge * This,
            /* [retval][out] */ IBridgeGeometry **bridgeGeometry);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alignment )( 
            IGenericBridge * This,
            /* [retval][out] */ IAlignment **ppAlignment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Piers )( 
            IGenericBridge * This,
            /* [retval][out] */ IPierCollection **piers);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IGenericBridge * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpanLength )( 
            IGenericBridge * This,
            /* [in] */ SpanIndexType spanIdx,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Deck )( 
            IGenericBridge * This,
            /* [in] */ IBridgeDeck *deck);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Deck )( 
            IGenericBridge * This,
            /* [retval][out] */ IBridgeDeck **deck);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftBarrier )( 
            IGenericBridge * This,
            /* [retval][out] */ ISidewalkBarrier **barrier);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_LeftBarrier )( 
            IGenericBridge * This,
            /* [in] */ ISidewalkBarrier *barrier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightBarrier )( 
            IGenericBridge * This,
            /* [retval][out] */ ISidewalkBarrier **barrier);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RightBarrier )( 
            IGenericBridge * This,
            /* [in] */ ISidewalkBarrier *barrier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WearingSurfaceStage )( 
            IGenericBridge * This,
            /* [retval][out] */ StageIndexType *stage);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WearingSurfaceStage )( 
            IGenericBridge * This,
            /* [in] */ StageIndexType stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WearingSurfaceDepth )( 
            IGenericBridge * This,
            /* [retval][out] */ Float64 *d);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WearingSurfaceDepth )( 
            IGenericBridge * This,
            /* [in] */ Float64 d);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WearingSurfaceDensity )( 
            IGenericBridge * This,
            /* [retval][out] */ Float64 *d);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WearingSurfaceDensity )( 
            IGenericBridge * This,
            /* [in] */ Float64 d);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SacrificialDepthStage )( 
            IGenericBridge * This,
            /* [retval][out] */ StageIndexType *stage);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SacrificialDepthStage )( 
            IGenericBridge * This,
            /* [in] */ StageIndexType stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SacrificialDepth )( 
            IGenericBridge * This,
            /* [retval][out] */ Float64 *depth);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SacrificialDepth )( 
            IGenericBridge * This,
            /* [in] */ Float64 depth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSuperstructureMember )( 
            IGenericBridge * This,
            /* [in] */ GirderIDType id,
            /* [in] */ LocationType locationType,
            /* [retval][out] */ ISuperstructureMember **ppMbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            IGenericBridge * This,
            /* [in] */ GirderIDType id,
            /* [retval][out] */ ISuperstructureMember **ppMbr);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumSuperstructureMembers )( 
            IGenericBridge * This,
            /* [retval][out] */ IEnumSuperstructureMembers **enumSSMbrs);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateBridgeModel )( 
            IGenericBridge * This);
        
        END_INTERFACE
    } IGenericBridgeVtbl;

    interface IGenericBridge
    {
        CONST_VTBL struct IGenericBridgeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGenericBridge_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGenericBridge_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGenericBridge_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGenericBridge_get_BridgeGeometry(This,bridgeGeometry)	\
    ( (This)->lpVtbl -> get_BridgeGeometry(This,bridgeGeometry) ) 

#define IGenericBridge_get_Alignment(This,ppAlignment)	\
    ( (This)->lpVtbl -> get_Alignment(This,ppAlignment) ) 

#define IGenericBridge_get_Piers(This,piers)	\
    ( (This)->lpVtbl -> get_Piers(This,piers) ) 

#define IGenericBridge_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define IGenericBridge_get_SpanLength(This,spanIdx,length)	\
    ( (This)->lpVtbl -> get_SpanLength(This,spanIdx,length) ) 

#define IGenericBridge_putref_Deck(This,deck)	\
    ( (This)->lpVtbl -> putref_Deck(This,deck) ) 

#define IGenericBridge_get_Deck(This,deck)	\
    ( (This)->lpVtbl -> get_Deck(This,deck) ) 

#define IGenericBridge_get_LeftBarrier(This,barrier)	\
    ( (This)->lpVtbl -> get_LeftBarrier(This,barrier) ) 

#define IGenericBridge_putref_LeftBarrier(This,barrier)	\
    ( (This)->lpVtbl -> putref_LeftBarrier(This,barrier) ) 

#define IGenericBridge_get_RightBarrier(This,barrier)	\
    ( (This)->lpVtbl -> get_RightBarrier(This,barrier) ) 

#define IGenericBridge_putref_RightBarrier(This,barrier)	\
    ( (This)->lpVtbl -> putref_RightBarrier(This,barrier) ) 

#define IGenericBridge_get_WearingSurfaceStage(This,stage)	\
    ( (This)->lpVtbl -> get_WearingSurfaceStage(This,stage) ) 

#define IGenericBridge_put_WearingSurfaceStage(This,stage)	\
    ( (This)->lpVtbl -> put_WearingSurfaceStage(This,stage) ) 

#define IGenericBridge_get_WearingSurfaceDepth(This,d)	\
    ( (This)->lpVtbl -> get_WearingSurfaceDepth(This,d) ) 

#define IGenericBridge_put_WearingSurfaceDepth(This,d)	\
    ( (This)->lpVtbl -> put_WearingSurfaceDepth(This,d) ) 

#define IGenericBridge_get_WearingSurfaceDensity(This,d)	\
    ( (This)->lpVtbl -> get_WearingSurfaceDensity(This,d) ) 

#define IGenericBridge_put_WearingSurfaceDensity(This,d)	\
    ( (This)->lpVtbl -> put_WearingSurfaceDensity(This,d) ) 

#define IGenericBridge_get_SacrificialDepthStage(This,stage)	\
    ( (This)->lpVtbl -> get_SacrificialDepthStage(This,stage) ) 

#define IGenericBridge_put_SacrificialDepthStage(This,stage)	\
    ( (This)->lpVtbl -> put_SacrificialDepthStage(This,stage) ) 

#define IGenericBridge_get_SacrificialDepth(This,depth)	\
    ( (This)->lpVtbl -> get_SacrificialDepth(This,depth) ) 

#define IGenericBridge_put_SacrificialDepth(This,depth)	\
    ( (This)->lpVtbl -> put_SacrificialDepth(This,depth) ) 

#define IGenericBridge_CreateSuperstructureMember(This,id,locationType,ppMbr)	\
    ( (This)->lpVtbl -> CreateSuperstructureMember(This,id,locationType,ppMbr) ) 

#define IGenericBridge_get_SuperstructureMember(This,id,ppMbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,id,ppMbr) ) 

#define IGenericBridge_get__EnumSuperstructureMembers(This,enumSSMbrs)	\
    ( (This)->lpVtbl -> get__EnumSuperstructureMembers(This,enumSSMbrs) ) 

#define IGenericBridge_UpdateBridgeModel(This)	\
    ( (This)->lpVtbl -> UpdateBridgeModel(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGenericBridge_INTERFACE_DEFINED__ */


#ifndef __ISuperstructureMember_INTERFACE_DEFINED__
#define __ISuperstructureMember_INTERFACE_DEFINED__

/* interface ISuperstructureMember */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISuperstructureMember;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2501E833-BB93-4458-869C-90EFA9BCA859")
    ISuperstructureMember : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ GirderIDType *pID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddSegment( 
            /* [in] */ ISuperstructureMemberSegment *segment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Segment( 
            /* [in] */ SegmentIndexType idx,
            /* [retval][out] */ ISuperstructureMemberSegment **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentCount( 
            /* [retval][out] */ SegmentIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDistanceFromStartOfSegment( 
            /* [in] */ Float64 Xg,
            /* [out] */ Float64 *pXs,
            /* [out] */ SegmentIndexType *pSegIdx,
            /* [out] */ ISuperstructureMemberSegment **ppSeg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDistanceFromStart( 
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [retval][out] */ Float64 *pXg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetEndRelease( 
            /* [in] */ EndType end,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ ReleaseType release) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEndRelease( 
            /* [in] */ EndType end,
            /* [out] */ StageIndexType *pStageIdx,
            /* [out] */ ReleaseType *release) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPlanAngle( 
            /* [in] */ Float64 distFromStartOfSSMbr,
            /* [retval][out] */ IAngle **ppAngle) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LocationType( 
            /* [retval][out] */ LocationType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Bridge( 
            /* [retval][out] */ IGenericBridge **ppBridge) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperstructureMemberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperstructureMember * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperstructureMember * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperstructureMember * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            ISuperstructureMember * This,
            /* [retval][out] */ GirderIDType *pID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSegment )( 
            ISuperstructureMember * This,
            /* [in] */ ISuperstructureMemberSegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Segment )( 
            ISuperstructureMember * This,
            /* [in] */ SegmentIndexType idx,
            /* [retval][out] */ ISuperstructureMemberSegment **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SegmentCount )( 
            ISuperstructureMember * This,
            /* [retval][out] */ SegmentIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDistanceFromStartOfSegment )( 
            ISuperstructureMember * This,
            /* [in] */ Float64 Xg,
            /* [out] */ Float64 *pXs,
            /* [out] */ SegmentIndexType *pSegIdx,
            /* [out] */ ISuperstructureMemberSegment **ppSeg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDistanceFromStart )( 
            ISuperstructureMember * This,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [retval][out] */ Float64 *pXg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEndRelease )( 
            ISuperstructureMember * This,
            /* [in] */ EndType end,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ ReleaseType release);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEndRelease )( 
            ISuperstructureMember * This,
            /* [in] */ EndType end,
            /* [out] */ StageIndexType *pStageIdx,
            /* [out] */ ReleaseType *release);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPlanAngle )( 
            ISuperstructureMember * This,
            /* [in] */ Float64 distFromStartOfSSMbr,
            /* [retval][out] */ IAngle **ppAngle);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocationType )( 
            ISuperstructureMember * This,
            /* [retval][out] */ LocationType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bridge )( 
            ISuperstructureMember * This,
            /* [retval][out] */ IGenericBridge **ppBridge);
        
        END_INTERFACE
    } ISuperstructureMemberVtbl;

    interface ISuperstructureMember
    {
        CONST_VTBL struct ISuperstructureMemberVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperstructureMember_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperstructureMember_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperstructureMember_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperstructureMember_get_ID(This,pID)	\
    ( (This)->lpVtbl -> get_ID(This,pID) ) 

#define ISuperstructureMember_AddSegment(This,segment)	\
    ( (This)->lpVtbl -> AddSegment(This,segment) ) 

#define ISuperstructureMember_get_Segment(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Segment(This,idx,pVal) ) 

#define ISuperstructureMember_get_SegmentCount(This,pVal)	\
    ( (This)->lpVtbl -> get_SegmentCount(This,pVal) ) 

#define ISuperstructureMember_GetDistanceFromStartOfSegment(This,Xg,pXs,pSegIdx,ppSeg)	\
    ( (This)->lpVtbl -> GetDistanceFromStartOfSegment(This,Xg,pXs,pSegIdx,ppSeg) ) 

#define ISuperstructureMember_GetDistanceFromStart(This,segIdx,Xs,pXg)	\
    ( (This)->lpVtbl -> GetDistanceFromStart(This,segIdx,Xs,pXg) ) 

#define ISuperstructureMember_SetEndRelease(This,end,stageIdx,release)	\
    ( (This)->lpVtbl -> SetEndRelease(This,end,stageIdx,release) ) 

#define ISuperstructureMember_GetEndRelease(This,end,pStageIdx,release)	\
    ( (This)->lpVtbl -> GetEndRelease(This,end,pStageIdx,release) ) 

#define ISuperstructureMember_GetPlanAngle(This,distFromStartOfSSMbr,ppAngle)	\
    ( (This)->lpVtbl -> GetPlanAngle(This,distFromStartOfSSMbr,ppAngle) ) 

#define ISuperstructureMember_get_LocationType(This,pVal)	\
    ( (This)->lpVtbl -> get_LocationType(This,pVal) ) 

#define ISuperstructureMember_get_Bridge(This,ppBridge)	\
    ( (This)->lpVtbl -> get_Bridge(This,ppBridge) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperstructureMember_INTERFACE_DEFINED__ */


#ifndef __IPier_INTERFACE_DEFINED__
#define __IPier_INTERFACE_DEFINED__

/* interface IPier */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPier;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1DA3DE0-D925-410d-8D76-7D99F0CEA454")
    IPier : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ PierType type) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ PierType *type) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DeckProfile( 
            /* [retval][out] */ IPoint2dCollection **ppPoints) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DeckThickness( 
            /* [retval][out] */ Float64 *pTDeck) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurbLineOffset( 
            /* [in] */ DirectionType side,
            /* [in] */ CurbLineMeasurementType clMeasure,
            /* [retval][out] */ Float64 *pCLO) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurbToCurbWidth( 
            /* [in] */ CurbLineMeasurementType clMeasure,
            /* [retval][out] */ Float64 *pWcc) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_SkewAngle( 
            /* [in] */ IAngle *pSkew) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SkewAngle( 
            /* [retval][out] */ IAngle **ppSkew) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_CrossBeam( 
            /* [in] */ ICrossBeam *pCrossBeam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CrossBeam( 
            /* [retval][out] */ ICrossBeam **ppCrossBeam) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_BearingLayout( 
            /* [in] */ IBearingLayout *pBearingLayout) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingLayout( 
            /* [retval][out] */ IBearingLayout **ppBearingLayout) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_ColumnLayout( 
            /* [in] */ IColumnLayout *pColumnLayout) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnLayout( 
            /* [retval][out] */ IColumnLayout **ppColumnLayout) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Column( 
            /* [in] */ ColumnIndexType columnIdx,
            /* [retval][out] */ IColumn **column) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertCrossBeamToCurbLineCoordinate( 
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pXcl) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertCurbLineToCrossBeamCoordinate( 
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pXxb) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertPierToCrossBeamCoordinate( 
            /* [in] */ Float64 Xp,
            /* [retval][out] */ Float64 *pXxb) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertCrossBeamToPierCoordinate( 
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pXp) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertPierToCurbLineCoordinate( 
            /* [in] */ Float64 Xp,
            /* [retval][out] */ Float64 *pXcl) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertCurbLineToPierCoordinate( 
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pXp) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Elevation( 
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pElev) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurbLineElevation( 
            /* [in] */ DirectionType side,
            /* [retval][out] */ Float64 *pElev) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPierVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPier * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPier * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPier * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IPier * This,
            /* [in] */ PierType type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IPier * This,
            /* [retval][out] */ PierType *type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeckProfile )( 
            IPier * This,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeckThickness )( 
            IPier * This,
            /* [retval][out] */ Float64 *pTDeck);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbLineOffset )( 
            IPier * This,
            /* [in] */ DirectionType side,
            /* [in] */ CurbLineMeasurementType clMeasure,
            /* [retval][out] */ Float64 *pCLO);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbToCurbWidth )( 
            IPier * This,
            /* [in] */ CurbLineMeasurementType clMeasure,
            /* [retval][out] */ Float64 *pWcc);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SkewAngle )( 
            IPier * This,
            /* [in] */ IAngle *pSkew);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SkewAngle )( 
            IPier * This,
            /* [retval][out] */ IAngle **ppSkew);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_CrossBeam )( 
            IPier * This,
            /* [in] */ ICrossBeam *pCrossBeam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CrossBeam )( 
            IPier * This,
            /* [retval][out] */ ICrossBeam **ppCrossBeam);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_BearingLayout )( 
            IPier * This,
            /* [in] */ IBearingLayout *pBearingLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingLayout )( 
            IPier * This,
            /* [retval][out] */ IBearingLayout **ppBearingLayout);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ColumnLayout )( 
            IPier * This,
            /* [in] */ IColumnLayout *pColumnLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColumnLayout )( 
            IPier * This,
            /* [retval][out] */ IColumnLayout **ppColumnLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Column )( 
            IPier * This,
            /* [in] */ ColumnIndexType columnIdx,
            /* [retval][out] */ IColumn **column);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCrossBeamToCurbLineCoordinate )( 
            IPier * This,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pXcl);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCurbLineToCrossBeamCoordinate )( 
            IPier * This,
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pXxb);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertPierToCrossBeamCoordinate )( 
            IPier * This,
            /* [in] */ Float64 Xp,
            /* [retval][out] */ Float64 *pXxb);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCrossBeamToPierCoordinate )( 
            IPier * This,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pXp);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertPierToCurbLineCoordinate )( 
            IPier * This,
            /* [in] */ Float64 Xp,
            /* [retval][out] */ Float64 *pXcl);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCurbLineToPierCoordinate )( 
            IPier * This,
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pXp);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Elevation )( 
            IPier * This,
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pElev);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbLineElevation )( 
            IPier * This,
            /* [in] */ DirectionType side,
            /* [retval][out] */ Float64 *pElev);
        
        END_INTERFACE
    } IPierVtbl;

    interface IPier
    {
        CONST_VTBL struct IPierVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPier_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPier_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPier_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPier_put_Type(This,type)	\
    ( (This)->lpVtbl -> put_Type(This,type) ) 

#define IPier_get_Type(This,type)	\
    ( (This)->lpVtbl -> get_Type(This,type) ) 

#define IPier_get_DeckProfile(This,ppPoints)	\
    ( (This)->lpVtbl -> get_DeckProfile(This,ppPoints) ) 

#define IPier_get_DeckThickness(This,pTDeck)	\
    ( (This)->lpVtbl -> get_DeckThickness(This,pTDeck) ) 

#define IPier_get_CurbLineOffset(This,side,clMeasure,pCLO)	\
    ( (This)->lpVtbl -> get_CurbLineOffset(This,side,clMeasure,pCLO) ) 

#define IPier_get_CurbToCurbWidth(This,clMeasure,pWcc)	\
    ( (This)->lpVtbl -> get_CurbToCurbWidth(This,clMeasure,pWcc) ) 

#define IPier_putref_SkewAngle(This,pSkew)	\
    ( (This)->lpVtbl -> putref_SkewAngle(This,pSkew) ) 

#define IPier_get_SkewAngle(This,ppSkew)	\
    ( (This)->lpVtbl -> get_SkewAngle(This,ppSkew) ) 

#define IPier_putref_CrossBeam(This,pCrossBeam)	\
    ( (This)->lpVtbl -> putref_CrossBeam(This,pCrossBeam) ) 

#define IPier_get_CrossBeam(This,ppCrossBeam)	\
    ( (This)->lpVtbl -> get_CrossBeam(This,ppCrossBeam) ) 

#define IPier_putref_BearingLayout(This,pBearingLayout)	\
    ( (This)->lpVtbl -> putref_BearingLayout(This,pBearingLayout) ) 

#define IPier_get_BearingLayout(This,ppBearingLayout)	\
    ( (This)->lpVtbl -> get_BearingLayout(This,ppBearingLayout) ) 

#define IPier_putref_ColumnLayout(This,pColumnLayout)	\
    ( (This)->lpVtbl -> putref_ColumnLayout(This,pColumnLayout) ) 

#define IPier_get_ColumnLayout(This,ppColumnLayout)	\
    ( (This)->lpVtbl -> get_ColumnLayout(This,ppColumnLayout) ) 

#define IPier_get_Column(This,columnIdx,column)	\
    ( (This)->lpVtbl -> get_Column(This,columnIdx,column) ) 

#define IPier_ConvertCrossBeamToCurbLineCoordinate(This,Xxb,pXcl)	\
    ( (This)->lpVtbl -> ConvertCrossBeamToCurbLineCoordinate(This,Xxb,pXcl) ) 

#define IPier_ConvertCurbLineToCrossBeamCoordinate(This,Xcl,pXxb)	\
    ( (This)->lpVtbl -> ConvertCurbLineToCrossBeamCoordinate(This,Xcl,pXxb) ) 

#define IPier_ConvertPierToCrossBeamCoordinate(This,Xp,pXxb)	\
    ( (This)->lpVtbl -> ConvertPierToCrossBeamCoordinate(This,Xp,pXxb) ) 

#define IPier_ConvertCrossBeamToPierCoordinate(This,Xxb,pXp)	\
    ( (This)->lpVtbl -> ConvertCrossBeamToPierCoordinate(This,Xxb,pXp) ) 

#define IPier_ConvertPierToCurbLineCoordinate(This,Xp,pXcl)	\
    ( (This)->lpVtbl -> ConvertPierToCurbLineCoordinate(This,Xp,pXcl) ) 

#define IPier_ConvertCurbLineToPierCoordinate(This,Xcl,pXp)	\
    ( (This)->lpVtbl -> ConvertCurbLineToPierCoordinate(This,Xcl,pXp) ) 

#define IPier_get_Elevation(This,Xcl,pElev)	\
    ( (This)->lpVtbl -> get_Elevation(This,Xcl,pElev) ) 

#define IPier_get_CurbLineElevation(This,side,pElev)	\
    ( (This)->lpVtbl -> get_CurbLineElevation(This,side,pElev) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPier_INTERFACE_DEFINED__ */


#ifndef __ICrossBeam_INTERFACE_DEFINED__
#define __ICrossBeam_INTERFACE_DEFINED__

/* interface ICrossBeam */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICrossBeam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D77377CB-A040-4008-B1BF-9710BA6FBB63")
    ICrossBeam : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Pier( 
            /* [in] */ IPier *pPier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Pier( 
            /* [retval][out] */ IPier **ppPier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [in] */ XBeamLocation location,
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Depth( 
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pDepth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FullDepth( 
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pDepth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IShape **ppShape) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopSurface( 
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IPoint2dCollection **ppPoints) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomSurface( 
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IPoint2dCollection **ppPoints) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Surface( 
            /* [in] */ CrossBeamRebarDatum datum,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2dCollection **ppPoints) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ IShape **ppShape) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BasicShape( 
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ IShape **ppShape) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayout( 
            /* [retval][out] */ IRebarLayout **ppRebarLayout) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_RebarLayout( 
            /* [in] */ IRebarLayout *pRebarLayout) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICrossBeamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICrossBeam * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICrossBeam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICrossBeam * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Pier )( 
            ICrossBeam * This,
            /* [in] */ IPier *pPier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pier )( 
            ICrossBeam * This,
            /* [retval][out] */ IPier **ppPier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ICrossBeam * This,
            /* [in] */ XBeamLocation location,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Depth )( 
            ICrossBeam * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pDepth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FullDepth )( 
            ICrossBeam * This,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pDepth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            ICrossBeam * This,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopSurface )( 
            ICrossBeam * This,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomSurface )( 
            ICrossBeam * This,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surface )( 
            ICrossBeam * This,
            /* [in] */ CrossBeamRebarDatum datum,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ICrossBeam * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BasicShape )( 
            ICrossBeam * This,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayout )( 
            ICrossBeam * This,
            /* [retval][out] */ IRebarLayout **ppRebarLayout);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarLayout )( 
            ICrossBeam * This,
            /* [in] */ IRebarLayout *pRebarLayout);
        
        END_INTERFACE
    } ICrossBeamVtbl;

    interface ICrossBeam
    {
        CONST_VTBL struct ICrossBeamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICrossBeam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICrossBeam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICrossBeam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICrossBeam_putref_Pier(This,pPier)	\
    ( (This)->lpVtbl -> putref_Pier(This,pPier) ) 

#define ICrossBeam_get_Pier(This,ppPier)	\
    ( (This)->lpVtbl -> get_Pier(This,ppPier) ) 

#define ICrossBeam_get_Length(This,location,length)	\
    ( (This)->lpVtbl -> get_Length(This,location,length) ) 

#define ICrossBeam_get_Depth(This,stageIdx,Xxb,pDepth)	\
    ( (This)->lpVtbl -> get_Depth(This,stageIdx,Xxb,pDepth) ) 

#define ICrossBeam_get_FullDepth(This,Xxb,pDepth)	\
    ( (This)->lpVtbl -> get_FullDepth(This,Xxb,pDepth) ) 

#define ICrossBeam_get_Profile(This,stageIdx,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,stageIdx,ppShape) ) 

#define ICrossBeam_get_TopSurface(This,stageIdx,ppPoints)	\
    ( (This)->lpVtbl -> get_TopSurface(This,stageIdx,ppPoints) ) 

#define ICrossBeam_get_BottomSurface(This,stageIdx,ppPoints)	\
    ( (This)->lpVtbl -> get_BottomSurface(This,stageIdx,ppPoints) ) 

#define ICrossBeam_get_Surface(This,datum,offset,ppPoints)	\
    ( (This)->lpVtbl -> get_Surface(This,datum,offset,ppPoints) ) 

#define ICrossBeam_get_Shape(This,stageIdx,Xxb,ppShape)	\
    ( (This)->lpVtbl -> get_Shape(This,stageIdx,Xxb,ppShape) ) 

#define ICrossBeam_get_BasicShape(This,Xxb,ppShape)	\
    ( (This)->lpVtbl -> get_BasicShape(This,Xxb,ppShape) ) 

#define ICrossBeam_get_RebarLayout(This,ppRebarLayout)	\
    ( (This)->lpVtbl -> get_RebarLayout(This,ppRebarLayout) ) 

#define ICrossBeam_putref_RebarLayout(This,pRebarLayout)	\
    ( (This)->lpVtbl -> putref_RebarLayout(This,pRebarLayout) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICrossBeam_INTERFACE_DEFINED__ */


#ifndef __IColumnLayout_INTERFACE_DEFINED__
#define __IColumnLayout_INTERFACE_DEFINED__

/* interface IColumnLayout */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IColumnLayout;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9AC642C8-524A-4FF7-8038-D5A696C3974A")
    IColumnLayout : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Pier( 
            /* [in] */ IPier *pPier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Pier( 
            /* [retval][out] */ IPier **ppPier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Uniform( 
            /* [retval][out] */ VARIANT_BOOL *bUniform) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Uniform( 
            /* [in] */ VARIANT_BOOL bUniform) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
            /* [in] */ SpacingIndexType spaceIdx,
            /* [retval][out] */ Float64 *space) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
            /* [in] */ SpacingIndexType spaceIdx,
            /* [in] */ Float64 space) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Overhang( 
            /* [in] */ DirectionType side,
            /* [retval][out] */ Float64 *overhang) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Overhang( 
            /* [in] */ DirectionType side,
            /* [in] */ Float64 overhang) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnCount( 
            /* [retval][out] */ ColumnIndexType *nColumns) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ColumnCount( 
            /* [in] */ ColumnIndexType nColumns) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ColumnIndexType nColumns) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ SpacingIndexType spaceIdx,
            /* [in] */ SpacingIndexType nInsert) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ ColumnIndexType colIdx,
            /* [in] */ ColumnIndexType nRemove) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetReferenceColumn( 
            /* [in] */ ColumnIndexType colIdx,
            /* [in] */ Float64 alignmentOffset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetReferenceColumn( 
            /* [out] */ ColumnIndexType *pColIdx,
            /* [out] */ Float64 *pAlignmentOffset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Column( 
            /* [in] */ ColumnIndexType colIdx,
            /* [retval][out] */ IColumn **column) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnLayoutWidth( 
            /* [retval][out] */ Float64 *pCLW) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnLocation( 
            /* [in] */ ColumnIndexType colIdx,
            /* [retval][out] */ Float64 *pXxb) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnOffset( 
            /* [in] */ ColumnIndexType colIdx,
            /* [retval][out] */ Float64 *pOffset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopColumnElevation( 
            /* [in] */ ColumnIndexType colIdx,
            /* [retval][out] */ Float64 *pElev) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomColumnElevation( 
            /* [in] */ ColumnIndexType colIdx,
            /* [retval][out] */ Float64 *pElev) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IColumnLayoutVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IColumnLayout * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IColumnLayout * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IColumnLayout * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Pier )( 
            IColumnLayout * This,
            /* [in] */ IPier *pPier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pier )( 
            IColumnLayout * This,
            /* [retval][out] */ IPier **ppPier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Uniform )( 
            IColumnLayout * This,
            /* [retval][out] */ VARIANT_BOOL *bUniform);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Uniform )( 
            IColumnLayout * This,
            /* [in] */ VARIANT_BOOL bUniform);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            IColumnLayout * This,
            /* [in] */ SpacingIndexType spaceIdx,
            /* [retval][out] */ Float64 *space);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            IColumnLayout * This,
            /* [in] */ SpacingIndexType spaceIdx,
            /* [in] */ Float64 space);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Overhang )( 
            IColumnLayout * This,
            /* [in] */ DirectionType side,
            /* [retval][out] */ Float64 *overhang);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Overhang )( 
            IColumnLayout * This,
            /* [in] */ DirectionType side,
            /* [in] */ Float64 overhang);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColumnCount )( 
            IColumnLayout * This,
            /* [retval][out] */ ColumnIndexType *nColumns);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ColumnCount )( 
            IColumnLayout * This,
            /* [in] */ ColumnIndexType nColumns);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IColumnLayout * This,
            /* [in] */ ColumnIndexType nColumns);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IColumnLayout * This,
            /* [in] */ SpacingIndexType spaceIdx,
            /* [in] */ SpacingIndexType nInsert);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IColumnLayout * This,
            /* [in] */ ColumnIndexType colIdx,
            /* [in] */ ColumnIndexType nRemove);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetReferenceColumn )( 
            IColumnLayout * This,
            /* [in] */ ColumnIndexType colIdx,
            /* [in] */ Float64 alignmentOffset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetReferenceColumn )( 
            IColumnLayout * This,
            /* [out] */ ColumnIndexType *pColIdx,
            /* [out] */ Float64 *pAlignmentOffset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Column )( 
            IColumnLayout * This,
            /* [in] */ ColumnIndexType colIdx,
            /* [retval][out] */ IColumn **column);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColumnLayoutWidth )( 
            IColumnLayout * This,
            /* [retval][out] */ Float64 *pCLW);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColumnLocation )( 
            IColumnLayout * This,
            /* [in] */ ColumnIndexType colIdx,
            /* [retval][out] */ Float64 *pXxb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColumnOffset )( 
            IColumnLayout * This,
            /* [in] */ ColumnIndexType colIdx,
            /* [retval][out] */ Float64 *pOffset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopColumnElevation )( 
            IColumnLayout * This,
            /* [in] */ ColumnIndexType colIdx,
            /* [retval][out] */ Float64 *pElev);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomColumnElevation )( 
            IColumnLayout * This,
            /* [in] */ ColumnIndexType colIdx,
            /* [retval][out] */ Float64 *pElev);
        
        END_INTERFACE
    } IColumnLayoutVtbl;

    interface IColumnLayout
    {
        CONST_VTBL struct IColumnLayoutVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IColumnLayout_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IColumnLayout_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IColumnLayout_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IColumnLayout_putref_Pier(This,pPier)	\
    ( (This)->lpVtbl -> putref_Pier(This,pPier) ) 

#define IColumnLayout_get_Pier(This,ppPier)	\
    ( (This)->lpVtbl -> get_Pier(This,ppPier) ) 

#define IColumnLayout_get_Uniform(This,bUniform)	\
    ( (This)->lpVtbl -> get_Uniform(This,bUniform) ) 

#define IColumnLayout_put_Uniform(This,bUniform)	\
    ( (This)->lpVtbl -> put_Uniform(This,bUniform) ) 

#define IColumnLayout_get_Spacing(This,spaceIdx,space)	\
    ( (This)->lpVtbl -> get_Spacing(This,spaceIdx,space) ) 

#define IColumnLayout_put_Spacing(This,spaceIdx,space)	\
    ( (This)->lpVtbl -> put_Spacing(This,spaceIdx,space) ) 

#define IColumnLayout_get_Overhang(This,side,overhang)	\
    ( (This)->lpVtbl -> get_Overhang(This,side,overhang) ) 

#define IColumnLayout_put_Overhang(This,side,overhang)	\
    ( (This)->lpVtbl -> put_Overhang(This,side,overhang) ) 

#define IColumnLayout_get_ColumnCount(This,nColumns)	\
    ( (This)->lpVtbl -> get_ColumnCount(This,nColumns) ) 

#define IColumnLayout_put_ColumnCount(This,nColumns)	\
    ( (This)->lpVtbl -> put_ColumnCount(This,nColumns) ) 

#define IColumnLayout_Add(This,nColumns)	\
    ( (This)->lpVtbl -> Add(This,nColumns) ) 

#define IColumnLayout_Insert(This,spaceIdx,nInsert)	\
    ( (This)->lpVtbl -> Insert(This,spaceIdx,nInsert) ) 

#define IColumnLayout_Remove(This,colIdx,nRemove)	\
    ( (This)->lpVtbl -> Remove(This,colIdx,nRemove) ) 

#define IColumnLayout_SetReferenceColumn(This,colIdx,alignmentOffset)	\
    ( (This)->lpVtbl -> SetReferenceColumn(This,colIdx,alignmentOffset) ) 

#define IColumnLayout_GetReferenceColumn(This,pColIdx,pAlignmentOffset)	\
    ( (This)->lpVtbl -> GetReferenceColumn(This,pColIdx,pAlignmentOffset) ) 

#define IColumnLayout_get_Column(This,colIdx,column)	\
    ( (This)->lpVtbl -> get_Column(This,colIdx,column) ) 

#define IColumnLayout_get_ColumnLayoutWidth(This,pCLW)	\
    ( (This)->lpVtbl -> get_ColumnLayoutWidth(This,pCLW) ) 

#define IColumnLayout_get_ColumnLocation(This,colIdx,pXxb)	\
    ( (This)->lpVtbl -> get_ColumnLocation(This,colIdx,pXxb) ) 

#define IColumnLayout_get_ColumnOffset(This,colIdx,pOffset)	\
    ( (This)->lpVtbl -> get_ColumnOffset(This,colIdx,pOffset) ) 

#define IColumnLayout_get_TopColumnElevation(This,colIdx,pElev)	\
    ( (This)->lpVtbl -> get_TopColumnElevation(This,colIdx,pElev) ) 

#define IColumnLayout_get_BottomColumnElevation(This,colIdx,pElev)	\
    ( (This)->lpVtbl -> get_BottomColumnElevation(This,colIdx,pElev) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IColumnLayout_INTERFACE_DEFINED__ */


#ifndef __IVoidedSlabSection2_INTERFACE_DEFINED__
#define __IVoidedSlabSection2_INTERFACE_DEFINED__

/* interface IVoidedSlabSection2 */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVoidedSlabSection2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A938B67A-8208-49d1-AEB5-FB700DBDE584")
    IVoidedSlabSection2 : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ IVoidedSlab2 *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IVoidedSlab2 **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVoidedSlabSection2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVoidedSlabSection2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVoidedSlabSection2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVoidedSlabSection2 * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            IVoidedSlabSection2 * This,
            /* [in] */ IVoidedSlab2 *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IVoidedSlabSection2 * This,
            /* [retval][out] */ IVoidedSlab2 **beam);
        
        END_INTERFACE
    } IVoidedSlabSection2Vtbl;

    interface IVoidedSlabSection2
    {
        CONST_VTBL struct IVoidedSlabSection2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoidedSlabSection2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVoidedSlabSection2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVoidedSlabSection2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVoidedSlabSection2_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define IVoidedSlabSection2_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVoidedSlabSection2_INTERFACE_DEFINED__ */


#ifndef __IDeckedSlabBeamSection_INTERFACE_DEFINED__
#define __IDeckedSlabBeamSection_INTERFACE_DEFINED__

/* interface IDeckedSlabBeamSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDeckedSlabBeamSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FADE6744-A4F6-4bec-8522-82F578E70A9C")
    IDeckedSlabBeamSection : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ IDeckedSlabBeam *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IDeckedSlabBeam **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDeckedSlabBeamSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDeckedSlabBeamSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDeckedSlabBeamSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDeckedSlabBeamSection * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            IDeckedSlabBeamSection * This,
            /* [in] */ IDeckedSlabBeam *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IDeckedSlabBeamSection * This,
            /* [retval][out] */ IDeckedSlabBeam **beam);
        
        END_INTERFACE
    } IDeckedSlabBeamSectionVtbl;

    interface IDeckedSlabBeamSection
    {
        CONST_VTBL struct IDeckedSlabBeamSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDeckedSlabBeamSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDeckedSlabBeamSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDeckedSlabBeamSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDeckedSlabBeamSection_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define IDeckedSlabBeamSection_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDeckedSlabBeamSection_INTERFACE_DEFINED__ */


#ifndef __IBoxBeamSection_INTERFACE_DEFINED__
#define __IBoxBeamSection_INTERFACE_DEFINED__

/* interface IBoxBeamSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBoxBeamSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("90FD25A4-0DA9-4e74-B6D3-CF1D1CF49FD3")
    IBoxBeamSection : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ IBoxBeam *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IBoxBeam **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBoxBeamSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBoxBeamSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBoxBeamSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBoxBeamSection * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            IBoxBeamSection * This,
            /* [in] */ IBoxBeam *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IBoxBeamSection * This,
            /* [retval][out] */ IBoxBeam **beam);
        
        END_INTERFACE
    } IBoxBeamSectionVtbl;

    interface IBoxBeamSection
    {
        CONST_VTBL struct IBoxBeamSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBoxBeamSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBoxBeamSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBoxBeamSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBoxBeamSection_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define IBoxBeamSection_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBoxBeamSection_INTERFACE_DEFINED__ */


#ifndef __IUGirderSection_INTERFACE_DEFINED__
#define __IUGirderSection_INTERFACE_DEFINED__

/* interface IUGirderSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUGirderSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("191C88B3-4DD6-42e4-AF89-5D31E0EA57A4")
    IUGirderSection : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ IUBeam *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IUBeam **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUGirderSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUGirderSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUGirderSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUGirderSection * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            IUGirderSection * This,
            /* [in] */ IUBeam *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IUGirderSection * This,
            /* [retval][out] */ IUBeam **beam);
        
        END_INTERFACE
    } IUGirderSectionVtbl;

    interface IUGirderSection
    {
        CONST_VTBL struct IUGirderSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUGirderSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUGirderSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUGirderSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUGirderSection_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define IUGirderSection_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUGirderSection_INTERFACE_DEFINED__ */


#ifndef __IUGirderSection2_INTERFACE_DEFINED__
#define __IUGirderSection2_INTERFACE_DEFINED__

/* interface IUGirderSection2 */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUGirderSection2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5CAEAB79-CA95-4957-ACE6-BAF844A2E1E7")
    IUGirderSection2 : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ IUBeam2 *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IUBeam2 **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUGirderSection2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUGirderSection2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUGirderSection2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUGirderSection2 * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            IUGirderSection2 * This,
            /* [in] */ IUBeam2 *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IUGirderSection2 * This,
            /* [retval][out] */ IUBeam2 **beam);
        
        END_INTERFACE
    } IUGirderSection2Vtbl;

    interface IUGirderSection2
    {
        CONST_VTBL struct IUGirderSection2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUGirderSection2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUGirderSection2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUGirderSection2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUGirderSection2_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define IUGirderSection2_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUGirderSection2_INTERFACE_DEFINED__ */


#ifndef __ITendon_INTERFACE_DEFINED__
#define __ITendon_INTERFACE_DEFINED__

/* interface ITendon */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITendon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("33FDE356-2981-4ff7-AA76-B392FC22262F")
    ITendon : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddSegment( 
            /* [in] */ ITendonSegment *segment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Segment( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ITendonSegment **segment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveSegment( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearSegments( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_JackingEnd( 
            /* [retval][out] */ JackingEndType *type) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_JackingEnd( 
            /* [in] */ JackingEndType type) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OutsideDiameter( 
            /* [retval][out] */ Float64 *size) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OutsideDiameter( 
            /* [in] */ Float64 size) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InsideDiameter( 
            /* [retval][out] */ Float64 *size) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_InsideDiameter( 
            /* [in] */ Float64 size) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StrandCount( 
            /* [retval][out] */ StrandIndexType *count) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StrandCount( 
            /* [in] */ StrandIndexType count) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Material( 
            /* [retval][out] */ IPrestressingStrand **material) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Material( 
            /* [in] */ IPrestressingStrand *material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InsideDuctArea( 
            /* [retval][out] */ Float64 *Apt) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TendonArea( 
            /* [retval][out] */ Float64 *Apt) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MinimumRadiusOfCurvature( 
            /* [retval][out] */ Float64 *pMinRadiusOfCurvature) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CG( 
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3d **cg) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Slope( 
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IVector3d **slope) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Start( 
            /* [retval][out] */ IPoint3d **start) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_End( 
            /* [retval][out] */ IPoint3d **end) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Centerline( 
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3dCollection **ppPoints) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_SuperstructureMember( 
            /* [in] */ ISuperstructureMember *pMbr) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SuperstructureMember( 
            /* [retval][out] */ ISuperstructureMember **ppMbr) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITendonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITendon * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITendon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITendon * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSegment )( 
            ITendon * This,
            /* [in] */ ITendonSegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Segment )( 
            ITendon * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ITendonSegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITendon * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveSegment )( 
            ITendon * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearSegments )( 
            ITendon * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JackingEnd )( 
            ITendon * This,
            /* [retval][out] */ JackingEndType *type);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_JackingEnd )( 
            ITendon * This,
            /* [in] */ JackingEndType type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutsideDiameter )( 
            ITendon * This,
            /* [retval][out] */ Float64 *size);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutsideDiameter )( 
            ITendon * This,
            /* [in] */ Float64 size);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InsideDiameter )( 
            ITendon * This,
            /* [retval][out] */ Float64 *size);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InsideDiameter )( 
            ITendon * This,
            /* [in] */ Float64 size);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandCount )( 
            ITendon * This,
            /* [retval][out] */ StrandIndexType *count);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StrandCount )( 
            ITendon * This,
            /* [in] */ StrandIndexType count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Material )( 
            ITendon * This,
            /* [retval][out] */ IPrestressingStrand **material);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Material )( 
            ITendon * This,
            /* [in] */ IPrestressingStrand *material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InsideDuctArea )( 
            ITendon * This,
            /* [retval][out] */ Float64 *Apt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TendonArea )( 
            ITendon * This,
            /* [retval][out] */ Float64 *Apt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinimumRadiusOfCurvature )( 
            ITendon * This,
            /* [retval][out] */ Float64 *pMinRadiusOfCurvature);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CG )( 
            ITendon * This,
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3d **cg);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            ITendon * This,
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IVector3d **slope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ITendon * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            ITendon * This,
            /* [retval][out] */ IPoint3d **start);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_End )( 
            ITendon * This,
            /* [retval][out] */ IPoint3d **end);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Centerline )( 
            ITendon * This,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3dCollection **ppPoints);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            ITendon * This,
            /* [in] */ ISuperstructureMember *pMbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            ITendon * This,
            /* [retval][out] */ ISuperstructureMember **ppMbr);
        
        END_INTERFACE
    } ITendonVtbl;

    interface ITendon
    {
        CONST_VTBL struct ITendonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITendon_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITendon_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITendon_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITendon_AddSegment(This,segment)	\
    ( (This)->lpVtbl -> AddSegment(This,segment) ) 

#define ITendon_get_Segment(This,index,segment)	\
    ( (This)->lpVtbl -> get_Segment(This,index,segment) ) 

#define ITendon_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define ITendon_RemoveSegment(This,index)	\
    ( (This)->lpVtbl -> RemoveSegment(This,index) ) 

#define ITendon_ClearSegments(This)	\
    ( (This)->lpVtbl -> ClearSegments(This) ) 

#define ITendon_get_JackingEnd(This,type)	\
    ( (This)->lpVtbl -> get_JackingEnd(This,type) ) 

#define ITendon_put_JackingEnd(This,type)	\
    ( (This)->lpVtbl -> put_JackingEnd(This,type) ) 

#define ITendon_get_OutsideDiameter(This,size)	\
    ( (This)->lpVtbl -> get_OutsideDiameter(This,size) ) 

#define ITendon_put_OutsideDiameter(This,size)	\
    ( (This)->lpVtbl -> put_OutsideDiameter(This,size) ) 

#define ITendon_get_InsideDiameter(This,size)	\
    ( (This)->lpVtbl -> get_InsideDiameter(This,size) ) 

#define ITendon_put_InsideDiameter(This,size)	\
    ( (This)->lpVtbl -> put_InsideDiameter(This,size) ) 

#define ITendon_get_StrandCount(This,count)	\
    ( (This)->lpVtbl -> get_StrandCount(This,count) ) 

#define ITendon_put_StrandCount(This,count)	\
    ( (This)->lpVtbl -> put_StrandCount(This,count) ) 

#define ITendon_get_Material(This,material)	\
    ( (This)->lpVtbl -> get_Material(This,material) ) 

#define ITendon_putref_Material(This,material)	\
    ( (This)->lpVtbl -> putref_Material(This,material) ) 

#define ITendon_get_InsideDuctArea(This,Apt)	\
    ( (This)->lpVtbl -> get_InsideDuctArea(This,Apt) ) 

#define ITendon_get_TendonArea(This,Apt)	\
    ( (This)->lpVtbl -> get_TendonArea(This,Apt) ) 

#define ITendon_get_MinimumRadiusOfCurvature(This,pMinRadiusOfCurvature)	\
    ( (This)->lpVtbl -> get_MinimumRadiusOfCurvature(This,pMinRadiusOfCurvature) ) 

#define ITendon_get_CG(This,z,measure,cg)	\
    ( (This)->lpVtbl -> get_CG(This,z,measure,cg) ) 

#define ITendon_get_Slope(This,z,measure,slope)	\
    ( (This)->lpVtbl -> get_Slope(This,z,measure,slope) ) 

#define ITendon_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define ITendon_get_Start(This,start)	\
    ( (This)->lpVtbl -> get_Start(This,start) ) 

#define ITendon_get_End(This,end)	\
    ( (This)->lpVtbl -> get_End(This,end) ) 

#define ITendon_get_Centerline(This,measure,ppPoints)	\
    ( (This)->lpVtbl -> get_Centerline(This,measure,ppPoints) ) 

#define ITendon_putref_SuperstructureMember(This,pMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,pMbr) ) 

#define ITendon_get_SuperstructureMember(This,ppMbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ppMbr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITendon_INTERFACE_DEFINED__ */


#ifndef __ISegment_INTERFACE_DEFINED__
#define __ISegment_INTERFACE_DEFINED__

/* interface ISegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74FEB936-F483-4c0a-9C26-723F28C4C2B6")
    ISegment : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PrimaryShape( 
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PrevSegment( 
            /* [retval][out] */ ISegment **segment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NextSegment( 
            /* [retval][out] */ ISegment **segment) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PrevSegment( 
            /* [in] */ ISegment *segment) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_NextSegment( 
            /* [in] */ ISegment *segment) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ISegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            ISegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            ISegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            ISegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            ISegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            ISegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            ISegment * This,
            /* [in] */ ISegment *segment);
        
        END_INTERFACE
    } ISegmentVtbl;

    interface ISegment
    {
        CONST_VTBL struct ISegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ISegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define ISegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define ISegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define ISegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define ISegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define ISegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISegment_INTERFACE_DEFINED__ */


#ifndef __IEffectiveFlangeWidthDetails_INTERFACE_DEFINED__
#define __IEffectiveFlangeWidthDetails_INTERFACE_DEFINED__

/* interface IEffectiveFlangeWidthDetails */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IEffectiveFlangeWidthDetails;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("262B5A19-8911-45de-A53D-DC7CDB73809E")
    IEffectiveFlangeWidthDetails : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_EffectiveSpanLength( 
            /* [in] */ Float64 length) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EffectiveSpanLength( 
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SlabThickness( 
            /* [in] */ Float64 tSlab) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SlabThickness( 
            /* [retval][out] */ Float64 *tSlab) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddFlangeParameters( 
            /* [in] */ Float64 tWeb,
            /* [in] */ Float64 wFlange,
            /* [in] */ Float64 lSpacing,
            /* [in] */ Float64 rSpacing) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FlangeCount( 
            /* [retval][out] */ FlangeIndexType *nFlange) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlangeParameters( 
            /* [in] */ FlangeIndexType flangeIdx,
            /* [out] */ Float64 *tWeb,
            /* [out] */ Float64 *wFlange,
            /* [out] */ Float64 *lSpacing,
            /* [out] */ Float64 *rSpacing) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EffectiveFlangeWidth( 
            /* [retval][out] */ Float64 *effFlangeWidth) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEffectiveFlangeWidthDetailsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEffectiveFlangeWidthDetails * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEffectiveFlangeWidthDetails * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEffectiveFlangeWidthDetails * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_EffectiveSpanLength )( 
            IEffectiveFlangeWidthDetails * This,
            /* [in] */ Float64 length);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EffectiveSpanLength )( 
            IEffectiveFlangeWidthDetails * This,
            /* [retval][out] */ Float64 *length);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_SlabThickness )( 
            IEffectiveFlangeWidthDetails * This,
            /* [in] */ Float64 tSlab);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SlabThickness )( 
            IEffectiveFlangeWidthDetails * This,
            /* [retval][out] */ Float64 *tSlab);
        
        HRESULT ( STDMETHODCALLTYPE *AddFlangeParameters )( 
            IEffectiveFlangeWidthDetails * This,
            /* [in] */ Float64 tWeb,
            /* [in] */ Float64 wFlange,
            /* [in] */ Float64 lSpacing,
            /* [in] */ Float64 rSpacing);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_FlangeCount )( 
            IEffectiveFlangeWidthDetails * This,
            /* [retval][out] */ FlangeIndexType *nFlange);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlangeParameters )( 
            IEffectiveFlangeWidthDetails * This,
            /* [in] */ FlangeIndexType flangeIdx,
            /* [out] */ Float64 *tWeb,
            /* [out] */ Float64 *wFlange,
            /* [out] */ Float64 *lSpacing,
            /* [out] */ Float64 *rSpacing);
        
        HRESULT ( STDMETHODCALLTYPE *EffectiveFlangeWidth )( 
            IEffectiveFlangeWidthDetails * This,
            /* [retval][out] */ Float64 *effFlangeWidth);
        
        END_INTERFACE
    } IEffectiveFlangeWidthDetailsVtbl;

    interface IEffectiveFlangeWidthDetails
    {
        CONST_VTBL struct IEffectiveFlangeWidthDetailsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEffectiveFlangeWidthDetails_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEffectiveFlangeWidthDetails_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEffectiveFlangeWidthDetails_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEffectiveFlangeWidthDetails_put_EffectiveSpanLength(This,length)	\
    ( (This)->lpVtbl -> put_EffectiveSpanLength(This,length) ) 

#define IEffectiveFlangeWidthDetails_get_EffectiveSpanLength(This,length)	\
    ( (This)->lpVtbl -> get_EffectiveSpanLength(This,length) ) 

#define IEffectiveFlangeWidthDetails_put_SlabThickness(This,tSlab)	\
    ( (This)->lpVtbl -> put_SlabThickness(This,tSlab) ) 

#define IEffectiveFlangeWidthDetails_get_SlabThickness(This,tSlab)	\
    ( (This)->lpVtbl -> get_SlabThickness(This,tSlab) ) 

#define IEffectiveFlangeWidthDetails_AddFlangeParameters(This,tWeb,wFlange,lSpacing,rSpacing)	\
    ( (This)->lpVtbl -> AddFlangeParameters(This,tWeb,wFlange,lSpacing,rSpacing) ) 

#define IEffectiveFlangeWidthDetails_get_FlangeCount(This,nFlange)	\
    ( (This)->lpVtbl -> get_FlangeCount(This,nFlange) ) 

#define IEffectiveFlangeWidthDetails_GetFlangeParameters(This,flangeIdx,tWeb,wFlange,lSpacing,rSpacing)	\
    ( (This)->lpVtbl -> GetFlangeParameters(This,flangeIdx,tWeb,wFlange,lSpacing,rSpacing) ) 

#define IEffectiveFlangeWidthDetails_EffectiveFlangeWidth(This,effFlangeWidth)	\
    ( (This)->lpVtbl -> EffectiveFlangeWidth(This,effFlangeWidth) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEffectiveFlangeWidthDetails_INTERFACE_DEFINED__ */


#ifndef __IEffectiveFlangeWidthTool_INTERFACE_DEFINED__
#define __IEffectiveFlangeWidthTool_INTERFACE_DEFINED__

/* interface IEffectiveFlangeWidthTool */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IEffectiveFlangeWidthTool;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ACD48CEC-704A-417D-B070-30DA37BAFFB4")
    IEffectiveFlangeWidthTool : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TributaryFlangeWidthBySSMbr( 
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xg,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ Float64 *tribFlangeWidth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TributaryFlangeWidthBySSMbrEx( 
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xg,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [out] */ Float64 *twLeft,
            /* [out] */ Float64 *twRight,
            /* [out] */ Float64 *tribFlangeWidth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TributaryFlangeWidthBySegment( 
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ Float64 *tribFlangeWidth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TributaryFlangeWidthBySegmentEx( 
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [out] */ Float64 *twLeft,
            /* [out] */ Float64 *twRight,
            /* [out] */ Float64 *tribFlangeWidth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EffectiveFlangeWidthBySSMbr( 
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xg,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ Float64 *effFlangeWidth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EffectiveFlangeWidthBySSMbrEx( 
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xg,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ IEffectiveFlangeWidthDetails **details) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EffectiveFlangeWidthBySegment( 
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ Float64 *effFlangeWidth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EffectiveFlangeWidthBySegmentEx( 
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ IEffectiveFlangeWidthDetails **details) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEffectiveFlangeWidthToolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEffectiveFlangeWidthTool * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEffectiveFlangeWidthTool * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEffectiveFlangeWidthTool * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TributaryFlangeWidthBySSMbr )( 
            IEffectiveFlangeWidthTool * This,
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xg,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ Float64 *tribFlangeWidth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TributaryFlangeWidthBySSMbrEx )( 
            IEffectiveFlangeWidthTool * This,
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xg,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [out] */ Float64 *twLeft,
            /* [out] */ Float64 *twRight,
            /* [out] */ Float64 *tribFlangeWidth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TributaryFlangeWidthBySegment )( 
            IEffectiveFlangeWidthTool * This,
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ Float64 *tribFlangeWidth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TributaryFlangeWidthBySegmentEx )( 
            IEffectiveFlangeWidthTool * This,
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [out] */ Float64 *twLeft,
            /* [out] */ Float64 *twRight,
            /* [out] */ Float64 *tribFlangeWidth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EffectiveFlangeWidthBySSMbr )( 
            IEffectiveFlangeWidthTool * This,
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xg,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ Float64 *effFlangeWidth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EffectiveFlangeWidthBySSMbrEx )( 
            IEffectiveFlangeWidthTool * This,
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xg,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ IEffectiveFlangeWidthDetails **details);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EffectiveFlangeWidthBySegment )( 
            IEffectiveFlangeWidthTool * This,
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ Float64 *effFlangeWidth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EffectiveFlangeWidthBySegmentEx )( 
            IEffectiveFlangeWidthTool * This,
            /* [in] */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [retval][out] */ IEffectiveFlangeWidthDetails **details);
        
        END_INTERFACE
    } IEffectiveFlangeWidthToolVtbl;

    interface IEffectiveFlangeWidthTool
    {
        CONST_VTBL struct IEffectiveFlangeWidthToolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEffectiveFlangeWidthTool_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEffectiveFlangeWidthTool_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEffectiveFlangeWidthTool_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEffectiveFlangeWidthTool_TributaryFlangeWidthBySSMbr(This,bridge,ssMbrID,Xg,leftSSMbrID,rightSSMbrID,tribFlangeWidth)	\
    ( (This)->lpVtbl -> TributaryFlangeWidthBySSMbr(This,bridge,ssMbrID,Xg,leftSSMbrID,rightSSMbrID,tribFlangeWidth) ) 

#define IEffectiveFlangeWidthTool_TributaryFlangeWidthBySSMbrEx(This,bridge,ssMbrID,Xg,leftSSMbrID,rightSSMbrID,twLeft,twRight,tribFlangeWidth)	\
    ( (This)->lpVtbl -> TributaryFlangeWidthBySSMbrEx(This,bridge,ssMbrID,Xg,leftSSMbrID,rightSSMbrID,twLeft,twRight,tribFlangeWidth) ) 

#define IEffectiveFlangeWidthTool_TributaryFlangeWidthBySegment(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,tribFlangeWidth)	\
    ( (This)->lpVtbl -> TributaryFlangeWidthBySegment(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,tribFlangeWidth) ) 

#define IEffectiveFlangeWidthTool_TributaryFlangeWidthBySegmentEx(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,twLeft,twRight,tribFlangeWidth)	\
    ( (This)->lpVtbl -> TributaryFlangeWidthBySegmentEx(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,twLeft,twRight,tribFlangeWidth) ) 

#define IEffectiveFlangeWidthTool_EffectiveFlangeWidthBySSMbr(This,bridge,ssMbrID,Xg,leftSSMbrID,rightSSMbrID,effFlangeWidth)	\
    ( (This)->lpVtbl -> EffectiveFlangeWidthBySSMbr(This,bridge,ssMbrID,Xg,leftSSMbrID,rightSSMbrID,effFlangeWidth) ) 

#define IEffectiveFlangeWidthTool_EffectiveFlangeWidthBySSMbrEx(This,bridge,ssMbrID,Xg,leftSSMbrID,rightSSMbrID,details)	\
    ( (This)->lpVtbl -> EffectiveFlangeWidthBySSMbrEx(This,bridge,ssMbrID,Xg,leftSSMbrID,rightSSMbrID,details) ) 

#define IEffectiveFlangeWidthTool_EffectiveFlangeWidthBySegment(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,effFlangeWidth)	\
    ( (This)->lpVtbl -> EffectiveFlangeWidthBySegment(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,effFlangeWidth) ) 

#define IEffectiveFlangeWidthTool_EffectiveFlangeWidthBySegmentEx(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,details)	\
    ( (This)->lpVtbl -> EffectiveFlangeWidthBySegmentEx(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,details) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEffectiveFlangeWidthTool_INTERFACE_DEFINED__ */


#ifndef __IRebar_INTERFACE_DEFINED__
#define __IRebar_INTERFACE_DEFINED__

/* interface IRebar */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRebar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6D610B2E-6D62-45d9-AE5D-2F8159D4B2CC")
    IRebar : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ BSTR name,
            /* [in] */ Float64 Es,
            /* [in] */ Float64 density,
            /* [in] */ Float64 fpu,
            /* [in] */ Float64 fpy,
            /* [in] */ Float64 db,
            /* [in] */ Float64 Ab,
            /* [in] */ StageIndexType stageIdx) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UltimateStrength( 
            /* [retval][out] */ Float64 *fpu) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_UltimateStrength( 
            /* [in] */ Float64 fpu) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_YieldStrength( 
            /* [retval][out] */ Float64 *fpy) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_YieldStrength( 
            /* [in] */ Float64 fpy) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NominalDiameter( 
            /* [retval][out] */ Float64 *db) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_NominalDiameter( 
            /* [in] */ Float64 db) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NominalArea( 
            /* [retval][out] */ Float64 *Ab) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_NominalArea( 
            /* [in] */ Float64 Ab) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InstallationStage( 
            /* [retval][out] */ StageIndexType *pStageIdx) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_InstallationStage( 
            /* [in] */ StageIndexType stageIdx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IRebar **ppClone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRebarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRebar * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRebar * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRebar * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IRebar * This,
            /* [in] */ BSTR name,
            /* [in] */ Float64 Es,
            /* [in] */ Float64 density,
            /* [in] */ Float64 fpu,
            /* [in] */ Float64 fpy,
            /* [in] */ Float64 db,
            /* [in] */ Float64 Ab,
            /* [in] */ StageIndexType stageIdx);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IRebar * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IRebar * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UltimateStrength )( 
            IRebar * This,
            /* [retval][out] */ Float64 *fpu);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UltimateStrength )( 
            IRebar * This,
            /* [in] */ Float64 fpu);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_YieldStrength )( 
            IRebar * This,
            /* [retval][out] */ Float64 *fpy);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_YieldStrength )( 
            IRebar * This,
            /* [in] */ Float64 fpy);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NominalDiameter )( 
            IRebar * This,
            /* [retval][out] */ Float64 *db);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NominalDiameter )( 
            IRebar * This,
            /* [in] */ Float64 db);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NominalArea )( 
            IRebar * This,
            /* [retval][out] */ Float64 *Ab);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NominalArea )( 
            IRebar * This,
            /* [in] */ Float64 Ab);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InstallationStage )( 
            IRebar * This,
            /* [retval][out] */ StageIndexType *pStageIdx);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InstallationStage )( 
            IRebar * This,
            /* [in] */ StageIndexType stageIdx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IRebar * This,
            /* [retval][out] */ IRebar **ppClone);
        
        END_INTERFACE
    } IRebarVtbl;

    interface IRebar
    {
        CONST_VTBL struct IRebarVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRebar_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRebar_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRebar_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRebar_Init(This,name,Es,density,fpu,fpy,db,Ab,stageIdx)	\
    ( (This)->lpVtbl -> Init(This,name,Es,density,fpu,fpy,db,Ab,stageIdx) ) 

#define IRebar_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IRebar_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 

#define IRebar_get_UltimateStrength(This,fpu)	\
    ( (This)->lpVtbl -> get_UltimateStrength(This,fpu) ) 

#define IRebar_put_UltimateStrength(This,fpu)	\
    ( (This)->lpVtbl -> put_UltimateStrength(This,fpu) ) 

#define IRebar_get_YieldStrength(This,fpy)	\
    ( (This)->lpVtbl -> get_YieldStrength(This,fpy) ) 

#define IRebar_put_YieldStrength(This,fpy)	\
    ( (This)->lpVtbl -> put_YieldStrength(This,fpy) ) 

#define IRebar_get_NominalDiameter(This,db)	\
    ( (This)->lpVtbl -> get_NominalDiameter(This,db) ) 

#define IRebar_put_NominalDiameter(This,db)	\
    ( (This)->lpVtbl -> put_NominalDiameter(This,db) ) 

#define IRebar_get_NominalArea(This,Ab)	\
    ( (This)->lpVtbl -> get_NominalArea(This,Ab) ) 

#define IRebar_put_NominalArea(This,Ab)	\
    ( (This)->lpVtbl -> put_NominalArea(This,Ab) ) 

#define IRebar_get_InstallationStage(This,pStageIdx)	\
    ( (This)->lpVtbl -> get_InstallationStage(This,pStageIdx) ) 

#define IRebar_put_InstallationStage(This,stageIdx)	\
    ( (This)->lpVtbl -> put_InstallationStage(This,stageIdx) ) 

#define IRebar_Clone(This,ppClone)	\
    ( (This)->lpVtbl -> Clone(This,ppClone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRebar_INTERFACE_DEFINED__ */


#ifndef __IRebarFactory_INTERFACE_DEFINED__
#define __IRebarFactory_INTERFACE_DEFINED__

/* interface IRebarFactory */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRebarFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E873B37D-4E71-4e72-9ED0-1B05E5AC6089")
    IRebarFactory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateRebar( 
            /* [in] */ MaterialSpec spec,
            /* [in] */ RebarGrade grade,
            /* [in] */ BarSize size,
            /* [in] */ IUnitConvert *convert,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IRebar **rebar) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRebarFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRebarFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRebarFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRebarFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateRebar )( 
            IRebarFactory * This,
            /* [in] */ MaterialSpec spec,
            /* [in] */ RebarGrade grade,
            /* [in] */ BarSize size,
            /* [in] */ IUnitConvert *convert,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IRebar **rebar);
        
        END_INTERFACE
    } IRebarFactoryVtbl;

    interface IRebarFactory
    {
        CONST_VTBL struct IRebarFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRebarFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRebarFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRebarFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRebarFactory_CreateRebar(This,spec,grade,size,convert,stageIdx,rebar)	\
    ( (This)->lpVtbl -> CreateRebar(This,spec,grade,size,convert,stageIdx,rebar) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRebarFactory_INTERFACE_DEFINED__ */


#ifndef __IRebarSectionItem_INTERFACE_DEFINED__
#define __IRebarSectionItem_INTERFACE_DEFINED__

/* interface IRebarSectionItem */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRebarSectionItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("450B480F-A093-4e5e-BA48-A405055A3844")
    IRebarSectionItem : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IPoint2d *location,
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 distFromEnd,
            /* [in] */ HookType htLeft,
            /* [in] */ HookType htRight,
            /* [in] */ IRebar *rebar) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ IPoint2d **location) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftExtension( 
            /* [retval][out] */ Float64 *dist) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightExtension( 
            /* [retval][out] */ Float64 *dist) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftHook( 
            /* [retval][out] */ HookType *hook) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightHook( 
            /* [retval][out] */ HookType *hook) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Rebar( 
            /* [retval][out] */ IRebar **rebar) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRebarSectionItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRebarSectionItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRebarSectionItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRebarSectionItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IRebarSectionItem * This,
            /* [in] */ IPoint2d *location,
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 distFromEnd,
            /* [in] */ HookType htLeft,
            /* [in] */ HookType htRight,
            /* [in] */ IRebar *rebar);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IRebarSectionItem * This,
            /* [retval][out] */ IPoint2d **location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftExtension )( 
            IRebarSectionItem * This,
            /* [retval][out] */ Float64 *dist);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightExtension )( 
            IRebarSectionItem * This,
            /* [retval][out] */ Float64 *dist);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftHook )( 
            IRebarSectionItem * This,
            /* [retval][out] */ HookType *hook);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightHook )( 
            IRebarSectionItem * This,
            /* [retval][out] */ HookType *hook);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rebar )( 
            IRebarSectionItem * This,
            /* [retval][out] */ IRebar **rebar);
        
        END_INTERFACE
    } IRebarSectionItemVtbl;

    interface IRebarSectionItem
    {
        CONST_VTBL struct IRebarSectionItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRebarSectionItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRebarSectionItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRebarSectionItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRebarSectionItem_Init(This,location,distFromStart,distFromEnd,htLeft,htRight,rebar)	\
    ( (This)->lpVtbl -> Init(This,location,distFromStart,distFromEnd,htLeft,htRight,rebar) ) 

#define IRebarSectionItem_get_Location(This,location)	\
    ( (This)->lpVtbl -> get_Location(This,location) ) 

#define IRebarSectionItem_get_LeftExtension(This,dist)	\
    ( (This)->lpVtbl -> get_LeftExtension(This,dist) ) 

#define IRebarSectionItem_get_RightExtension(This,dist)	\
    ( (This)->lpVtbl -> get_RightExtension(This,dist) ) 

#define IRebarSectionItem_get_LeftHook(This,hook)	\
    ( (This)->lpVtbl -> get_LeftHook(This,hook) ) 

#define IRebarSectionItem_get_RightHook(This,hook)	\
    ( (This)->lpVtbl -> get_RightHook(This,hook) ) 

#define IRebarSectionItem_get_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> get_Rebar(This,rebar) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRebarSectionItem_INTERFACE_DEFINED__ */


#ifndef __IEnumRebarSectionItem_INTERFACE_DEFINED__
#define __IEnumRebarSectionItem_INTERFACE_DEFINED__

/* interface IEnumRebarSectionItem */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumRebarSectionItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9FD3BB0E-1AE0-4421-B44C-76AF46077068")
    IEnumRebarSectionItem : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumRebarSectionItem **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IRebarSectionItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumRebarSectionItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumRebarSectionItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumRebarSectionItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumRebarSectionItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumRebarSectionItem * This,
            /* [out] */ IEnumRebarSectionItem **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumRebarSectionItem * This,
            /* [in] */ ULONG celt,
            /* [out] */ IRebarSectionItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumRebarSectionItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumRebarSectionItem * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumRebarSectionItemVtbl;

    interface IEnumRebarSectionItem
    {
        CONST_VTBL struct IEnumRebarSectionItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumRebarSectionItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumRebarSectionItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumRebarSectionItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumRebarSectionItem_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumRebarSectionItem_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumRebarSectionItem_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumRebarSectionItem_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumRebarSectionItem_INTERFACE_DEFINED__ */


#ifndef __IRebarSection_INTERFACE_DEFINED__
#define __IRebarSection_INTERFACE_DEFINED__

/* interface IRebarSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRebarSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BC1C7976-D479-4c25-9869-A449B0EDAFBC")
    IRebarSection : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IRebarSectionItem *item) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IRebarSectionItem **item) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumRebarSectionItem( 
            /* [retval][out] */ IEnumRebarSectionItem **enumRSI) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRebarSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRebarSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRebarSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRebarSection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IRebarSection * This,
            /* [in] */ IRebarSectionItem *item);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IRebarSection * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IRebarSection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IRebarSectionItem **item);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IRebarSection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumRebarSectionItem )( 
            IRebarSection * This,
            /* [retval][out] */ IEnumRebarSectionItem **enumRSI);
        
        END_INTERFACE
    } IRebarSectionVtbl;

    interface IRebarSection
    {
        CONST_VTBL struct IRebarSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRebarSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRebarSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRebarSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRebarSection_Add(This,item)	\
    ( (This)->lpVtbl -> Add(This,item) ) 

#define IRebarSection_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IRebarSection_get_Item(This,idx,item)	\
    ( (This)->lpVtbl -> get_Item(This,idx,item) ) 

#define IRebarSection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IRebarSection_get__EnumRebarSectionItem(This,enumRSI)	\
    ( (This)->lpVtbl -> get__EnumRebarSectionItem(This,enumRSI) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRebarSection_INTERFACE_DEFINED__ */


#ifndef __IRebarPattern_INTERFACE_DEFINED__
#define __IRebarPattern_INTERFACE_DEFINED__

/* interface IRebarPattern */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRebarPattern;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70D6E658-49B9-491d-B4DF-156457A835B8")
    IRebarPattern : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Rebar( 
            /* [in] */ IRebar *rebar) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Rebar( 
            /* [retval][out] */ IRebar **rebar) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_RebarLayoutItem( 
            /* [in] */ IRebarLayoutItem *rebarLayoutItem) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Hook( 
            /* [in] */ DirectionType side,
            /* [in] */ HookType hook) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Hook( 
            /* [in] */ DirectionType side,
            /* [retval][out] */ HookType *hook) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [in] */ Float64 distFromStartOfPattern,
            /* [in] */ CollectionIndexType barIdx,
            /* [retval][out] */ IPoint2d **location) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [in] */ IndexType barIdx,
            /* [retval][out] */ IPoint2dCollection **ppProfile) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRebarPatternVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRebarPattern * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRebarPattern * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRebarPattern * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Rebar )( 
            IRebarPattern * This,
            /* [in] */ IRebar *rebar);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rebar )( 
            IRebarPattern * This,
            /* [retval][out] */ IRebar **rebar);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarLayoutItem )( 
            IRebarPattern * This,
            /* [in] */ IRebarLayoutItem *rebarLayoutItem);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Hook )( 
            IRebarPattern * This,
            /* [in] */ DirectionType side,
            /* [in] */ HookType hook);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Hook )( 
            IRebarPattern * This,
            /* [in] */ DirectionType side,
            /* [retval][out] */ HookType *hook);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IRebarPattern * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IRebarPattern * This,
            /* [in] */ Float64 distFromStartOfPattern,
            /* [in] */ CollectionIndexType barIdx,
            /* [retval][out] */ IPoint2d **location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IRebarPattern * This,
            /* [in] */ IndexType barIdx,
            /* [retval][out] */ IPoint2dCollection **ppProfile);
        
        END_INTERFACE
    } IRebarPatternVtbl;

    interface IRebarPattern
    {
        CONST_VTBL struct IRebarPatternVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRebarPattern_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRebarPattern_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRebarPattern_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRebarPattern_putref_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> putref_Rebar(This,rebar) ) 

#define IRebarPattern_get_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> get_Rebar(This,rebar) ) 

#define IRebarPattern_putref_RebarLayoutItem(This,rebarLayoutItem)	\
    ( (This)->lpVtbl -> putref_RebarLayoutItem(This,rebarLayoutItem) ) 

#define IRebarPattern_put_Hook(This,side,hook)	\
    ( (This)->lpVtbl -> put_Hook(This,side,hook) ) 

#define IRebarPattern_get_Hook(This,side,hook)	\
    ( (This)->lpVtbl -> get_Hook(This,side,hook) ) 

#define IRebarPattern_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IRebarPattern_get_Location(This,distFromStartOfPattern,barIdx,location)	\
    ( (This)->lpVtbl -> get_Location(This,distFromStartOfPattern,barIdx,location) ) 

#define IRebarPattern_get_Profile(This,barIdx,ppProfile)	\
    ( (This)->lpVtbl -> get_Profile(This,barIdx,ppProfile) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRebarPattern_INTERFACE_DEFINED__ */


#ifndef __IRebarRowFacePattern_INTERFACE_DEFINED__
#define __IRebarRowFacePattern_INTERFACE_DEFINED__

/* interface IRebarRowFacePattern */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRebarRowFacePattern;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B818106D-4689-481d-BC87-9C4154355DB0")
    IRebarRowFacePattern : public IRebarPattern
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Segment( 
            /* [in] */ ISegment *pSegment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Segment( 
            /* [retval][out] */ ISegment **pSegment) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Face( 
            /* [in] */ FaceType faceType) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Face( 
            /* [retval][out] */ FaceType *faceType) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Offset( 
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Offset( 
            /* [retval][out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Count( 
            /* [in] */ RowIndexType count) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
            /* [in] */ Float64 spacing) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
            /* [retval][out] */ Float64 *spacing) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ RebarRowOrientation oreintation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ RebarRowOrientation *oreintation) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRebarRowFacePatternVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRebarRowFacePattern * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRebarRowFacePattern * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRebarRowFacePattern * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Rebar )( 
            IRebarRowFacePattern * This,
            /* [in] */ IRebar *rebar);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rebar )( 
            IRebarRowFacePattern * This,
            /* [retval][out] */ IRebar **rebar);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarLayoutItem )( 
            IRebarRowFacePattern * This,
            /* [in] */ IRebarLayoutItem *rebarLayoutItem);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Hook )( 
            IRebarRowFacePattern * This,
            /* [in] */ DirectionType side,
            /* [in] */ HookType hook);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Hook )( 
            IRebarRowFacePattern * This,
            /* [in] */ DirectionType side,
            /* [retval][out] */ HookType *hook);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IRebarRowFacePattern * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IRebarRowFacePattern * This,
            /* [in] */ Float64 distFromStartOfPattern,
            /* [in] */ CollectionIndexType barIdx,
            /* [retval][out] */ IPoint2d **location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IRebarRowFacePattern * This,
            /* [in] */ IndexType barIdx,
            /* [retval][out] */ IPoint2dCollection **ppProfile);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Segment )( 
            IRebarRowFacePattern * This,
            /* [in] */ ISegment *pSegment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Segment )( 
            IRebarRowFacePattern * This,
            /* [retval][out] */ ISegment **pSegment);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Face )( 
            IRebarRowFacePattern * This,
            /* [in] */ FaceType faceType);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Face )( 
            IRebarRowFacePattern * This,
            /* [retval][out] */ FaceType *faceType);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Offset )( 
            IRebarRowFacePattern * This,
            /* [in] */ Float64 offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Offset )( 
            IRebarRowFacePattern * This,
            /* [retval][out] */ Float64 *offset);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Count )( 
            IRebarRowFacePattern * This,
            /* [in] */ RowIndexType count);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            IRebarRowFacePattern * This,
            /* [in] */ Float64 spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            IRebarRowFacePattern * This,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IRebarRowFacePattern * This,
            /* [in] */ RebarRowOrientation oreintation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IRebarRowFacePattern * This,
            /* [retval][out] */ RebarRowOrientation *oreintation);
        
        END_INTERFACE
    } IRebarRowFacePatternVtbl;

    interface IRebarRowFacePattern
    {
        CONST_VTBL struct IRebarRowFacePatternVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRebarRowFacePattern_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRebarRowFacePattern_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRebarRowFacePattern_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRebarRowFacePattern_putref_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> putref_Rebar(This,rebar) ) 

#define IRebarRowFacePattern_get_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> get_Rebar(This,rebar) ) 

#define IRebarRowFacePattern_putref_RebarLayoutItem(This,rebarLayoutItem)	\
    ( (This)->lpVtbl -> putref_RebarLayoutItem(This,rebarLayoutItem) ) 

#define IRebarRowFacePattern_put_Hook(This,side,hook)	\
    ( (This)->lpVtbl -> put_Hook(This,side,hook) ) 

#define IRebarRowFacePattern_get_Hook(This,side,hook)	\
    ( (This)->lpVtbl -> get_Hook(This,side,hook) ) 

#define IRebarRowFacePattern_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IRebarRowFacePattern_get_Location(This,distFromStartOfPattern,barIdx,location)	\
    ( (This)->lpVtbl -> get_Location(This,distFromStartOfPattern,barIdx,location) ) 

#define IRebarRowFacePattern_get_Profile(This,barIdx,ppProfile)	\
    ( (This)->lpVtbl -> get_Profile(This,barIdx,ppProfile) ) 


#define IRebarRowFacePattern_putref_Segment(This,pSegment)	\
    ( (This)->lpVtbl -> putref_Segment(This,pSegment) ) 

#define IRebarRowFacePattern_get_Segment(This,pSegment)	\
    ( (This)->lpVtbl -> get_Segment(This,pSegment) ) 

#define IRebarRowFacePattern_put_Face(This,faceType)	\
    ( (This)->lpVtbl -> put_Face(This,faceType) ) 

#define IRebarRowFacePattern_get_Face(This,faceType)	\
    ( (This)->lpVtbl -> get_Face(This,faceType) ) 

#define IRebarRowFacePattern_put_Offset(This,offset)	\
    ( (This)->lpVtbl -> put_Offset(This,offset) ) 

#define IRebarRowFacePattern_get_Offset(This,offset)	\
    ( (This)->lpVtbl -> get_Offset(This,offset) ) 

#define IRebarRowFacePattern_put_Count(This,count)	\
    ( (This)->lpVtbl -> put_Count(This,count) ) 

#define IRebarRowFacePattern_put_Spacing(This,spacing)	\
    ( (This)->lpVtbl -> put_Spacing(This,spacing) ) 

#define IRebarRowFacePattern_get_Spacing(This,spacing)	\
    ( (This)->lpVtbl -> get_Spacing(This,spacing) ) 

#define IRebarRowFacePattern_put_Orientation(This,oreintation)	\
    ( (This)->lpVtbl -> put_Orientation(This,oreintation) ) 

#define IRebarRowFacePattern_get_Orientation(This,oreintation)	\
    ( (This)->lpVtbl -> get_Orientation(This,oreintation) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRebarRowFacePattern_INTERFACE_DEFINED__ */


#ifndef __IRebarRowPattern_INTERFACE_DEFINED__
#define __IRebarRowPattern_INTERFACE_DEFINED__

/* interface IRebarRowPattern */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRebarRowPattern;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("200FB0A9-E906-4b1e-A2D0-01BBE933CB6C")
    IRebarRowPattern : public IRebarPattern
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AnchorPoint( 
            /* [in] */ EndType endType,
            /* [in] */ IPoint2d *anchorPt) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AnchorPoint( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IPoint2d **anchorPt) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Count( 
            /* [in] */ RowIndexType count) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
            /* [in] */ Float64 spacing) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
            /* [retval][out] */ Float64 *spacing) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ RebarRowOrientation oreintation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ RebarRowOrientation *oreintation) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRebarRowPatternVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRebarRowPattern * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRebarRowPattern * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRebarRowPattern * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Rebar )( 
            IRebarRowPattern * This,
            /* [in] */ IRebar *rebar);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rebar )( 
            IRebarRowPattern * This,
            /* [retval][out] */ IRebar **rebar);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarLayoutItem )( 
            IRebarRowPattern * This,
            /* [in] */ IRebarLayoutItem *rebarLayoutItem);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Hook )( 
            IRebarRowPattern * This,
            /* [in] */ DirectionType side,
            /* [in] */ HookType hook);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Hook )( 
            IRebarRowPattern * This,
            /* [in] */ DirectionType side,
            /* [retval][out] */ HookType *hook);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IRebarRowPattern * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IRebarRowPattern * This,
            /* [in] */ Float64 distFromStartOfPattern,
            /* [in] */ CollectionIndexType barIdx,
            /* [retval][out] */ IPoint2d **location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IRebarRowPattern * This,
            /* [in] */ IndexType barIdx,
            /* [retval][out] */ IPoint2dCollection **ppProfile);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AnchorPoint )( 
            IRebarRowPattern * This,
            /* [in] */ EndType endType,
            /* [in] */ IPoint2d *anchorPt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AnchorPoint )( 
            IRebarRowPattern * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IPoint2d **anchorPt);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Count )( 
            IRebarRowPattern * This,
            /* [in] */ RowIndexType count);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            IRebarRowPattern * This,
            /* [in] */ Float64 spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            IRebarRowPattern * This,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IRebarRowPattern * This,
            /* [in] */ RebarRowOrientation oreintation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IRebarRowPattern * This,
            /* [retval][out] */ RebarRowOrientation *oreintation);
        
        END_INTERFACE
    } IRebarRowPatternVtbl;

    interface IRebarRowPattern
    {
        CONST_VTBL struct IRebarRowPatternVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRebarRowPattern_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRebarRowPattern_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRebarRowPattern_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRebarRowPattern_putref_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> putref_Rebar(This,rebar) ) 

#define IRebarRowPattern_get_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> get_Rebar(This,rebar) ) 

#define IRebarRowPattern_putref_RebarLayoutItem(This,rebarLayoutItem)	\
    ( (This)->lpVtbl -> putref_RebarLayoutItem(This,rebarLayoutItem) ) 

#define IRebarRowPattern_put_Hook(This,side,hook)	\
    ( (This)->lpVtbl -> put_Hook(This,side,hook) ) 

#define IRebarRowPattern_get_Hook(This,side,hook)	\
    ( (This)->lpVtbl -> get_Hook(This,side,hook) ) 

#define IRebarRowPattern_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IRebarRowPattern_get_Location(This,distFromStartOfPattern,barIdx,location)	\
    ( (This)->lpVtbl -> get_Location(This,distFromStartOfPattern,barIdx,location) ) 

#define IRebarRowPattern_get_Profile(This,barIdx,ppProfile)	\
    ( (This)->lpVtbl -> get_Profile(This,barIdx,ppProfile) ) 


#define IRebarRowPattern_put_AnchorPoint(This,endType,anchorPt)	\
    ( (This)->lpVtbl -> put_AnchorPoint(This,endType,anchorPt) ) 

#define IRebarRowPattern_get_AnchorPoint(This,endType,anchorPt)	\
    ( (This)->lpVtbl -> get_AnchorPoint(This,endType,anchorPt) ) 

#define IRebarRowPattern_put_Count(This,count)	\
    ( (This)->lpVtbl -> put_Count(This,count) ) 

#define IRebarRowPattern_put_Spacing(This,spacing)	\
    ( (This)->lpVtbl -> put_Spacing(This,spacing) ) 

#define IRebarRowPattern_get_Spacing(This,spacing)	\
    ( (This)->lpVtbl -> get_Spacing(This,spacing) ) 

#define IRebarRowPattern_put_Orientation(This,oreintation)	\
    ( (This)->lpVtbl -> put_Orientation(This,oreintation) ) 

#define IRebarRowPattern_get_Orientation(This,oreintation)	\
    ( (This)->lpVtbl -> get_Orientation(This,oreintation) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRebarRowPattern_INTERFACE_DEFINED__ */


#ifndef __ICrossBeamRebarPattern_INTERFACE_DEFINED__
#define __ICrossBeamRebarPattern_INTERFACE_DEFINED__

/* interface ICrossBeamRebarPattern */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICrossBeamRebarPattern;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1D884636-E396-4755-AF3C-17B919114109")
    ICrossBeamRebarPattern : public IRebarPattern
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_CrossBeam( 
            /* [in] */ ICrossBeam *pXBeam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CrossBeam( 
            /* [retval][out] */ ICrossBeam **ppXBeam) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Datum( 
            /* [in] */ CrossBeamRebarDatum datum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Datum( 
            /* [retval][out] */ CrossBeamRebarDatum *pDatum) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Cover( 
            /* [in] */ Float64 cover) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Cover( 
            /* [retval][out] */ Float64 *pCover) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Count( 
            /* [in] */ RowIndexType count) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
            /* [in] */ Float64 spacing) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
            /* [retval][out] */ Float64 *spacing) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayProfile( 
            /* [in] */ IndexType barIdx,
            /* [retval][out] */ IPoint2dCollection **ppProfile) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICrossBeamRebarPatternVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICrossBeamRebarPattern * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICrossBeamRebarPattern * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Rebar )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ IRebar *rebar);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rebar )( 
            ICrossBeamRebarPattern * This,
            /* [retval][out] */ IRebar **rebar);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarLayoutItem )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ IRebarLayoutItem *rebarLayoutItem);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Hook )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ DirectionType side,
            /* [in] */ HookType hook);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Hook )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ DirectionType side,
            /* [retval][out] */ HookType *hook);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICrossBeamRebarPattern * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ Float64 distFromStartOfPattern,
            /* [in] */ CollectionIndexType barIdx,
            /* [retval][out] */ IPoint2d **location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ IndexType barIdx,
            /* [retval][out] */ IPoint2dCollection **ppProfile);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_CrossBeam )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ ICrossBeam *pXBeam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CrossBeam )( 
            ICrossBeamRebarPattern * This,
            /* [retval][out] */ ICrossBeam **ppXBeam);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Datum )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ CrossBeamRebarDatum datum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Datum )( 
            ICrossBeamRebarPattern * This,
            /* [retval][out] */ CrossBeamRebarDatum *pDatum);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Cover )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ Float64 cover);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cover )( 
            ICrossBeamRebarPattern * This,
            /* [retval][out] */ Float64 *pCover);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Count )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ RowIndexType count);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ Float64 spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            ICrossBeamRebarPattern * This,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayProfile )( 
            ICrossBeamRebarPattern * This,
            /* [in] */ IndexType barIdx,
            /* [retval][out] */ IPoint2dCollection **ppProfile);
        
        END_INTERFACE
    } ICrossBeamRebarPatternVtbl;

    interface ICrossBeamRebarPattern
    {
        CONST_VTBL struct ICrossBeamRebarPatternVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICrossBeamRebarPattern_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICrossBeamRebarPattern_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICrossBeamRebarPattern_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICrossBeamRebarPattern_putref_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> putref_Rebar(This,rebar) ) 

#define ICrossBeamRebarPattern_get_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> get_Rebar(This,rebar) ) 

#define ICrossBeamRebarPattern_putref_RebarLayoutItem(This,rebarLayoutItem)	\
    ( (This)->lpVtbl -> putref_RebarLayoutItem(This,rebarLayoutItem) ) 

#define ICrossBeamRebarPattern_put_Hook(This,side,hook)	\
    ( (This)->lpVtbl -> put_Hook(This,side,hook) ) 

#define ICrossBeamRebarPattern_get_Hook(This,side,hook)	\
    ( (This)->lpVtbl -> get_Hook(This,side,hook) ) 

#define ICrossBeamRebarPattern_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define ICrossBeamRebarPattern_get_Location(This,distFromStartOfPattern,barIdx,location)	\
    ( (This)->lpVtbl -> get_Location(This,distFromStartOfPattern,barIdx,location) ) 

#define ICrossBeamRebarPattern_get_Profile(This,barIdx,ppProfile)	\
    ( (This)->lpVtbl -> get_Profile(This,barIdx,ppProfile) ) 


#define ICrossBeamRebarPattern_putref_CrossBeam(This,pXBeam)	\
    ( (This)->lpVtbl -> putref_CrossBeam(This,pXBeam) ) 

#define ICrossBeamRebarPattern_get_CrossBeam(This,ppXBeam)	\
    ( (This)->lpVtbl -> get_CrossBeam(This,ppXBeam) ) 

#define ICrossBeamRebarPattern_put_Datum(This,datum)	\
    ( (This)->lpVtbl -> put_Datum(This,datum) ) 

#define ICrossBeamRebarPattern_get_Datum(This,pDatum)	\
    ( (This)->lpVtbl -> get_Datum(This,pDatum) ) 

#define ICrossBeamRebarPattern_put_Cover(This,cover)	\
    ( (This)->lpVtbl -> put_Cover(This,cover) ) 

#define ICrossBeamRebarPattern_get_Cover(This,pCover)	\
    ( (This)->lpVtbl -> get_Cover(This,pCover) ) 

#define ICrossBeamRebarPattern_put_Count(This,count)	\
    ( (This)->lpVtbl -> put_Count(This,count) ) 

#define ICrossBeamRebarPattern_put_Spacing(This,spacing)	\
    ( (This)->lpVtbl -> put_Spacing(This,spacing) ) 

#define ICrossBeamRebarPattern_get_Spacing(This,spacing)	\
    ( (This)->lpVtbl -> get_Spacing(This,spacing) ) 

#define ICrossBeamRebarPattern_get_DisplayProfile(This,barIdx,ppProfile)	\
    ( (This)->lpVtbl -> get_DisplayProfile(This,barIdx,ppProfile) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICrossBeamRebarPattern_INTERFACE_DEFINED__ */


#ifndef __IEnumRebarPatterns_INTERFACE_DEFINED__
#define __IEnumRebarPatterns_INTERFACE_DEFINED__

/* interface IEnumRebarPatterns */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumRebarPatterns;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("61D6DF2E-6BA5-4ba4-B045-F57DFC16F973")
    IEnumRebarPatterns : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumRebarPatterns **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IRebarPattern **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumRebarPatternsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumRebarPatterns * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumRebarPatterns * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumRebarPatterns * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumRebarPatterns * This,
            /* [out] */ IEnumRebarPatterns **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumRebarPatterns * This,
            /* [in] */ ULONG celt,
            /* [out] */ IRebarPattern **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumRebarPatterns * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumRebarPatterns * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumRebarPatternsVtbl;

    interface IEnumRebarPatterns
    {
        CONST_VTBL struct IEnumRebarPatternsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumRebarPatterns_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumRebarPatterns_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumRebarPatterns_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumRebarPatterns_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumRebarPatterns_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumRebarPatterns_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumRebarPatterns_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumRebarPatterns_INTERFACE_DEFINED__ */


#ifndef __IBridgeDeckRebarPattern_INTERFACE_DEFINED__
#define __IBridgeDeckRebarPattern_INTERFACE_DEFINED__

/* interface IBridgeDeckRebarPattern */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBridgeDeckRebarPattern;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C9AE211E-037B-4c52-BDAE-22520DFCE2B9")
    IBridgeDeckRebarPattern : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Rebar( 
            /* [in] */ IRebar *rebar) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Rebar( 
            /* [retval][out] */ IRebar **rebar) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_RebarLayoutItem( 
            /* [in] */ IBridgeDeckRebarLayoutItem *rebarLayoutItem) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
            /* [in] */ Float64 spacing) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
            /* [retval][out] */ Float64 *spacing) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ Float64 y) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ Float64 *pY) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IsLumped( 
            /* [in] */ VARIANT_BOOL bIsLumped) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsLumped( 
            /* [retval][out] */ VARIANT_BOOL *pbIsLumped) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBridgeDeckRebarPatternVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBridgeDeckRebarPattern * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBridgeDeckRebarPattern * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBridgeDeckRebarPattern * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Rebar )( 
            IBridgeDeckRebarPattern * This,
            /* [in] */ IRebar *rebar);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rebar )( 
            IBridgeDeckRebarPattern * This,
            /* [retval][out] */ IRebar **rebar);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarLayoutItem )( 
            IBridgeDeckRebarPattern * This,
            /* [in] */ IBridgeDeckRebarLayoutItem *rebarLayoutItem);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            IBridgeDeckRebarPattern * This,
            /* [in] */ Float64 spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            IBridgeDeckRebarPattern * This,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Location )( 
            IBridgeDeckRebarPattern * This,
            /* [in] */ Float64 y);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IBridgeDeckRebarPattern * This,
            /* [retval][out] */ Float64 *pY);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsLumped )( 
            IBridgeDeckRebarPattern * This,
            /* [in] */ VARIANT_BOOL bIsLumped);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsLumped )( 
            IBridgeDeckRebarPattern * This,
            /* [retval][out] */ VARIANT_BOOL *pbIsLumped);
        
        END_INTERFACE
    } IBridgeDeckRebarPatternVtbl;

    interface IBridgeDeckRebarPattern
    {
        CONST_VTBL struct IBridgeDeckRebarPatternVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBridgeDeckRebarPattern_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBridgeDeckRebarPattern_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBridgeDeckRebarPattern_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBridgeDeckRebarPattern_putref_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> putref_Rebar(This,rebar) ) 

#define IBridgeDeckRebarPattern_get_Rebar(This,rebar)	\
    ( (This)->lpVtbl -> get_Rebar(This,rebar) ) 

#define IBridgeDeckRebarPattern_putref_RebarLayoutItem(This,rebarLayoutItem)	\
    ( (This)->lpVtbl -> putref_RebarLayoutItem(This,rebarLayoutItem) ) 

#define IBridgeDeckRebarPattern_put_Spacing(This,spacing)	\
    ( (This)->lpVtbl -> put_Spacing(This,spacing) ) 

#define IBridgeDeckRebarPattern_get_Spacing(This,spacing)	\
    ( (This)->lpVtbl -> get_Spacing(This,spacing) ) 

#define IBridgeDeckRebarPattern_put_Location(This,y)	\
    ( (This)->lpVtbl -> put_Location(This,y) ) 

#define IBridgeDeckRebarPattern_get_Location(This,pY)	\
    ( (This)->lpVtbl -> get_Location(This,pY) ) 

#define IBridgeDeckRebarPattern_put_IsLumped(This,bIsLumped)	\
    ( (This)->lpVtbl -> put_IsLumped(This,bIsLumped) ) 

#define IBridgeDeckRebarPattern_get_IsLumped(This,pbIsLumped)	\
    ( (This)->lpVtbl -> get_IsLumped(This,pbIsLumped) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBridgeDeckRebarPattern_INTERFACE_DEFINED__ */


#ifndef __IEnumBridgeDeckRebarPatterns_INTERFACE_DEFINED__
#define __IEnumBridgeDeckRebarPatterns_INTERFACE_DEFINED__

/* interface IEnumBridgeDeckRebarPatterns */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumBridgeDeckRebarPatterns;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B13A045-FE2F-41fb-8A64-0F0DCE0CB281")
    IEnumBridgeDeckRebarPatterns : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumBridgeDeckRebarPatterns **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IBridgeDeckRebarPattern **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumBridgeDeckRebarPatternsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumBridgeDeckRebarPatterns * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumBridgeDeckRebarPatterns * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumBridgeDeckRebarPatterns * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumBridgeDeckRebarPatterns * This,
            /* [out] */ IEnumBridgeDeckRebarPatterns **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumBridgeDeckRebarPatterns * This,
            /* [in] */ ULONG celt,
            /* [out] */ IBridgeDeckRebarPattern **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumBridgeDeckRebarPatterns * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumBridgeDeckRebarPatterns * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumBridgeDeckRebarPatternsVtbl;

    interface IEnumBridgeDeckRebarPatterns
    {
        CONST_VTBL struct IEnumBridgeDeckRebarPatternsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumBridgeDeckRebarPatterns_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumBridgeDeckRebarPatterns_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumBridgeDeckRebarPatterns_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumBridgeDeckRebarPatterns_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumBridgeDeckRebarPatterns_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumBridgeDeckRebarPatterns_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumBridgeDeckRebarPatterns_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumBridgeDeckRebarPatterns_INTERFACE_DEFINED__ */


#ifndef __IFixedLengthRebarLayoutItem_INTERFACE_DEFINED__
#define __IFixedLengthRebarLayoutItem_INTERFACE_DEFINED__

/* interface IFixedLengthRebarLayoutItem */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IFixedLengthRebarLayoutItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5471ADD4-FB20-4694-A4F2-0267447AAE3E")
    IFixedLengthRebarLayoutItem : public IRebarLayoutItem
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Start( 
            /* [in] */ Float64 start) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_End( 
            /* [in] */ Float64 end) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_End( 
            /* [retval][out] */ Float64 *end) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFixedLengthRebarLayoutItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFixedLengthRebarLayoutItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFixedLengthRebarLayoutItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFixedLengthRebarLayoutItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ContainsLocation )( 
            IFixedLengthRebarLayoutItem * This,
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            IFixedLengthRebarLayoutItem * This,
            /* [retval][out] */ Float64 *start);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IFixedLengthRebarLayoutItem * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFixedLengthRebarLayoutItem * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFixedLengthRebarLayoutItem * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IRebarPattern **pattern);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddRebarPattern )( 
            IFixedLengthRebarLayoutItem * This,
            /* [in] */ IRebarPattern *pattern);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFixedLengthRebarLayoutItem * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumRebarPatterns )( 
            IFixedLengthRebarLayoutItem * This,
            /* [retval][out] */ IEnumRebarPatterns **enumRebarPatterns);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Start )( 
            IFixedLengthRebarLayoutItem * This,
            /* [in] */ Float64 start);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_End )( 
            IFixedLengthRebarLayoutItem * This,
            /* [in] */ Float64 end);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_End )( 
            IFixedLengthRebarLayoutItem * This,
            /* [retval][out] */ Float64 *end);
        
        END_INTERFACE
    } IFixedLengthRebarLayoutItemVtbl;

    interface IFixedLengthRebarLayoutItem
    {
        CONST_VTBL struct IFixedLengthRebarLayoutItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFixedLengthRebarLayoutItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFixedLengthRebarLayoutItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFixedLengthRebarLayoutItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFixedLengthRebarLayoutItem_ContainsLocation(This,distFromStart,bResult)	\
    ( (This)->lpVtbl -> ContainsLocation(This,distFromStart,bResult) ) 

#define IFixedLengthRebarLayoutItem_get_Start(This,start)	\
    ( (This)->lpVtbl -> get_Start(This,start) ) 

#define IFixedLengthRebarLayoutItem_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define IFixedLengthRebarLayoutItem_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IFixedLengthRebarLayoutItem_get_Item(This,idx,pattern)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pattern) ) 

#define IFixedLengthRebarLayoutItem_AddRebarPattern(This,pattern)	\
    ( (This)->lpVtbl -> AddRebarPattern(This,pattern) ) 

#define IFixedLengthRebarLayoutItem_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IFixedLengthRebarLayoutItem_get__EnumRebarPatterns(This,enumRebarPatterns)	\
    ( (This)->lpVtbl -> get__EnumRebarPatterns(This,enumRebarPatterns) ) 


#define IFixedLengthRebarLayoutItem_put_Start(This,start)	\
    ( (This)->lpVtbl -> put_Start(This,start) ) 

#define IFixedLengthRebarLayoutItem_put_End(This,end)	\
    ( (This)->lpVtbl -> put_End(This,end) ) 

#define IFixedLengthRebarLayoutItem_get_End(This,end)	\
    ( (This)->lpVtbl -> get_End(This,end) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFixedLengthRebarLayoutItem_INTERFACE_DEFINED__ */


#ifndef __INegativeMomentBridgeDeckRebarLayoutItem_INTERFACE_DEFINED__
#define __INegativeMomentBridgeDeckRebarLayoutItem_INTERFACE_DEFINED__

/* interface INegativeMomentBridgeDeckRebarLayoutItem */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_INegativeMomentBridgeDeckRebarLayoutItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EA709870-6420-48ee-AB07-03BABE4F979C")
    INegativeMomentBridgeDeckRebarLayoutItem : public IBridgeDeckRebarLayoutItem
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PierID( 
            /* [in] */ PierIDType pierID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PierID( 
            /* [retval][out] */ PierIDType *pPierID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LeftCutoff( 
            /* [in] */ Float64 coLeft) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftCutoff( 
            /* [retval][out] */ Float64 *pcoLeft) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RightCutoff( 
            /* [in] */ Float64 coRight) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightCutoff( 
            /* [retval][out] */ Float64 *pcoRight) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct INegativeMomentBridgeDeckRebarLayoutItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ContainsLocation )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 offset,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ Float64 *start);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IBridgeDeckRebarPattern **pattern);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddRebarPattern )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [in] */ IBridgeDeckRebarPattern *pattern);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumRebarPatterns )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ IEnumBridgeDeckRebarPatterns **enumRebarPatterns);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Bridge )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [in] */ IGenericBridge *pBridge);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PierID )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [in] */ PierIDType pierID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PierID )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ PierIDType *pPierID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LeftCutoff )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [in] */ Float64 coLeft);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftCutoff )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ Float64 *pcoLeft);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RightCutoff )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [in] */ Float64 coRight);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightCutoff )( 
            INegativeMomentBridgeDeckRebarLayoutItem * This,
            /* [retval][out] */ Float64 *pcoRight);
        
        END_INTERFACE
    } INegativeMomentBridgeDeckRebarLayoutItemVtbl;

    interface INegativeMomentBridgeDeckRebarLayoutItem
    {
        CONST_VTBL struct INegativeMomentBridgeDeckRebarLayoutItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INegativeMomentBridgeDeckRebarLayoutItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INegativeMomentBridgeDeckRebarLayoutItem_ContainsLocation(This,distFromStart,offset,bResult)	\
    ( (This)->lpVtbl -> ContainsLocation(This,distFromStart,offset,bResult) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_get_Start(This,start)	\
    ( (This)->lpVtbl -> get_Start(This,start) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_get_Item(This,idx,pattern)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pattern) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_AddRebarPattern(This,pattern)	\
    ( (This)->lpVtbl -> AddRebarPattern(This,pattern) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_get__EnumRebarPatterns(This,enumRebarPatterns)	\
    ( (This)->lpVtbl -> get__EnumRebarPatterns(This,enumRebarPatterns) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_putref_Bridge(This,pBridge)	\
    ( (This)->lpVtbl -> putref_Bridge(This,pBridge) ) 


#define INegativeMomentBridgeDeckRebarLayoutItem_put_PierID(This,pierID)	\
    ( (This)->lpVtbl -> put_PierID(This,pierID) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_get_PierID(This,pPierID)	\
    ( (This)->lpVtbl -> get_PierID(This,pPierID) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_put_LeftCutoff(This,coLeft)	\
    ( (This)->lpVtbl -> put_LeftCutoff(This,coLeft) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_get_LeftCutoff(This,pcoLeft)	\
    ( (This)->lpVtbl -> get_LeftCutoff(This,pcoLeft) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_put_RightCutoff(This,coRight)	\
    ( (This)->lpVtbl -> put_RightCutoff(This,coRight) ) 

#define INegativeMomentBridgeDeckRebarLayoutItem_get_RightCutoff(This,pcoRight)	\
    ( (This)->lpVtbl -> get_RightCutoff(This,pcoRight) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INegativeMomentBridgeDeckRebarLayoutItem_INTERFACE_DEFINED__ */


#ifndef __IEnumRebarLayoutItems_INTERFACE_DEFINED__
#define __IEnumRebarLayoutItems_INTERFACE_DEFINED__

/* interface IEnumRebarLayoutItems */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumRebarLayoutItems;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("216C0A97-4C1C-4584-BCD9-5F5C9CFB6511")
    IEnumRebarLayoutItems : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumRebarLayoutItems **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IRebarLayoutItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumRebarLayoutItemsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumRebarLayoutItems * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumRebarLayoutItems * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumRebarLayoutItems * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumRebarLayoutItems * This,
            /* [out] */ IEnumRebarLayoutItems **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumRebarLayoutItems * This,
            /* [in] */ ULONG celt,
            /* [out] */ IRebarLayoutItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumRebarLayoutItems * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumRebarLayoutItems * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumRebarLayoutItemsVtbl;

    interface IEnumRebarLayoutItems
    {
        CONST_VTBL struct IEnumRebarLayoutItemsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumRebarLayoutItems_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumRebarLayoutItems_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumRebarLayoutItems_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumRebarLayoutItems_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumRebarLayoutItems_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumRebarLayoutItems_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumRebarLayoutItems_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumRebarLayoutItems_INTERFACE_DEFINED__ */


#ifndef __IEnumBridgeDeckRebarLayoutItems_INTERFACE_DEFINED__
#define __IEnumBridgeDeckRebarLayoutItems_INTERFACE_DEFINED__

/* interface IEnumBridgeDeckRebarLayoutItems */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumBridgeDeckRebarLayoutItems;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("306F8277-C7FD-46dd-B2F5-1AF20716DF9A")
    IEnumBridgeDeckRebarLayoutItems : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumBridgeDeckRebarLayoutItems **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IBridgeDeckRebarLayoutItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumBridgeDeckRebarLayoutItemsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumBridgeDeckRebarLayoutItems * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumBridgeDeckRebarLayoutItems * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumBridgeDeckRebarLayoutItems * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumBridgeDeckRebarLayoutItems * This,
            /* [out] */ IEnumBridgeDeckRebarLayoutItems **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumBridgeDeckRebarLayoutItems * This,
            /* [in] */ ULONG celt,
            /* [out] */ IBridgeDeckRebarLayoutItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumBridgeDeckRebarLayoutItems * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumBridgeDeckRebarLayoutItems * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumBridgeDeckRebarLayoutItemsVtbl;

    interface IEnumBridgeDeckRebarLayoutItems
    {
        CONST_VTBL struct IEnumBridgeDeckRebarLayoutItemsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumBridgeDeckRebarLayoutItems_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumBridgeDeckRebarLayoutItems_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumBridgeDeckRebarLayoutItems_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumBridgeDeckRebarLayoutItems_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumBridgeDeckRebarLayoutItems_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumBridgeDeckRebarLayoutItems_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumBridgeDeckRebarLayoutItems_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumBridgeDeckRebarLayoutItems_INTERFACE_DEFINED__ */


#ifndef __IRebarLayout_INTERFACE_DEFINED__
#define __IRebarLayout_INTERFACE_DEFINED__

/* interface IRebarLayout */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRebarLayout;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("455C735E-09FD-443a-BE17-7237AA1BA045")
    IRebarLayout : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateRebarSection( 
            /* [in] */ Float64 cutLocation,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IRebarSection **section) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IRebarLayoutItem **rli) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IRebarLayoutItem *rli) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumRebarLayoutItems( 
            /* [retval][out] */ IEnumRebarLayoutItems **enumRebarLayoutItems) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRebarLayoutVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRebarLayout * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRebarLayout * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRebarLayout * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateRebarSection )( 
            IRebarLayout * This,
            /* [in] */ Float64 cutLocation,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IRebarSection **section);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IRebarLayout * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IRebarLayoutItem **rli);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IRebarLayout * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IRebarLayout * This,
            /* [in] */ IRebarLayoutItem *rli);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IRebarLayout * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumRebarLayoutItems )( 
            IRebarLayout * This,
            /* [retval][out] */ IEnumRebarLayoutItems **enumRebarLayoutItems);
        
        END_INTERFACE
    } IRebarLayoutVtbl;

    interface IRebarLayout
    {
        CONST_VTBL struct IRebarLayoutVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRebarLayout_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRebarLayout_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRebarLayout_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRebarLayout_CreateRebarSection(This,cutLocation,stageIdx,section)	\
    ( (This)->lpVtbl -> CreateRebarSection(This,cutLocation,stageIdx,section) ) 

#define IRebarLayout_get_Item(This,idx,rli)	\
    ( (This)->lpVtbl -> get_Item(This,idx,rli) ) 

#define IRebarLayout_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IRebarLayout_Add(This,rli)	\
    ( (This)->lpVtbl -> Add(This,rli) ) 

#define IRebarLayout_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IRebarLayout_get__EnumRebarLayoutItems(This,enumRebarLayoutItems)	\
    ( (This)->lpVtbl -> get__EnumRebarLayoutItems(This,enumRebarLayoutItems) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRebarLayout_INTERFACE_DEFINED__ */


#ifndef __IBridgeDeckRebarLayout_INTERFACE_DEFINED__
#define __IBridgeDeckRebarLayout_INTERFACE_DEFINED__

/* interface IBridgeDeckRebarLayout */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBridgeDeckRebarLayout;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4CF20D1A-02DC-451e-88FA-832A84F99C32")
    IBridgeDeckRebarLayout : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Bridge( 
            /* [in] */ IGenericBridge *pBridge) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Bridge( 
            /* [retval][out] */ IGenericBridge **ppBridge) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_EffectiveFlangeWidthTool( 
            /* [in] */ IEffectiveFlangeWidthTool *pTool) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EffectiveFlangeWidthTool( 
            /* [retval][out] */ IEffectiveFlangeWidthTool **pTool) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateRebarSection( 
            /* [in] */ IDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 distFromStartOfSegment,
            /* [in] */ IDType leftSSMbrID,
            /* [in] */ IDType rightSSMbrID,
            /* [retval][out] */ IRebarSection **section) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IBridgeDeckRebarLayoutItem **rli) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IBridgeDeckRebarLayoutItem *rli) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumRebarLayoutItems( 
            /* [retval][out] */ IEnumBridgeDeckRebarLayoutItems **enumRebarLayoutItems) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBridgeDeckRebarLayoutVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBridgeDeckRebarLayout * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBridgeDeckRebarLayout * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBridgeDeckRebarLayout * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Bridge )( 
            IBridgeDeckRebarLayout * This,
            /* [in] */ IGenericBridge *pBridge);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bridge )( 
            IBridgeDeckRebarLayout * This,
            /* [retval][out] */ IGenericBridge **ppBridge);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_EffectiveFlangeWidthTool )( 
            IBridgeDeckRebarLayout * This,
            /* [in] */ IEffectiveFlangeWidthTool *pTool);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EffectiveFlangeWidthTool )( 
            IBridgeDeckRebarLayout * This,
            /* [retval][out] */ IEffectiveFlangeWidthTool **pTool);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateRebarSection )( 
            IBridgeDeckRebarLayout * This,
            /* [in] */ IDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 distFromStartOfSegment,
            /* [in] */ IDType leftSSMbrID,
            /* [in] */ IDType rightSSMbrID,
            /* [retval][out] */ IRebarSection **section);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IBridgeDeckRebarLayout * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IBridgeDeckRebarLayoutItem **rli);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IBridgeDeckRebarLayout * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IBridgeDeckRebarLayout * This,
            /* [in] */ IBridgeDeckRebarLayoutItem *rli);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IBridgeDeckRebarLayout * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumRebarLayoutItems )( 
            IBridgeDeckRebarLayout * This,
            /* [retval][out] */ IEnumBridgeDeckRebarLayoutItems **enumRebarLayoutItems);
        
        END_INTERFACE
    } IBridgeDeckRebarLayoutVtbl;

    interface IBridgeDeckRebarLayout
    {
        CONST_VTBL struct IBridgeDeckRebarLayoutVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBridgeDeckRebarLayout_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBridgeDeckRebarLayout_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBridgeDeckRebarLayout_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBridgeDeckRebarLayout_putref_Bridge(This,pBridge)	\
    ( (This)->lpVtbl -> putref_Bridge(This,pBridge) ) 

#define IBridgeDeckRebarLayout_get_Bridge(This,ppBridge)	\
    ( (This)->lpVtbl -> get_Bridge(This,ppBridge) ) 

#define IBridgeDeckRebarLayout_putref_EffectiveFlangeWidthTool(This,pTool)	\
    ( (This)->lpVtbl -> putref_EffectiveFlangeWidthTool(This,pTool) ) 

#define IBridgeDeckRebarLayout_get_EffectiveFlangeWidthTool(This,pTool)	\
    ( (This)->lpVtbl -> get_EffectiveFlangeWidthTool(This,pTool) ) 

#define IBridgeDeckRebarLayout_CreateRebarSection(This,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,section)	\
    ( (This)->lpVtbl -> CreateRebarSection(This,ssMbrID,segIdx,distFromStartOfSegment,leftSSMbrID,rightSSMbrID,section) ) 

#define IBridgeDeckRebarLayout_get_Item(This,idx,rli)	\
    ( (This)->lpVtbl -> get_Item(This,idx,rli) ) 

#define IBridgeDeckRebarLayout_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IBridgeDeckRebarLayout_Add(This,rli)	\
    ( (This)->lpVtbl -> Add(This,rli) ) 

#define IBridgeDeckRebarLayout_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IBridgeDeckRebarLayout_get__EnumRebarLayoutItems(This,enumRebarLayoutItems)	\
    ( (This)->lpVtbl -> get__EnumRebarLayoutItems(This,enumRebarLayoutItems) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBridgeDeckRebarLayout_INTERFACE_DEFINED__ */


#ifndef __IMaterial_INTERFACE_DEFINED__
#define __IMaterial_INTERFACE_DEFINED__

/* interface IMaterial */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IMaterial;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9344D48A-BE1C-4dce-8558-4D1CAE81D2F0")
    IMaterial : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_E( 
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ Float64 *E) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_E( 
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 E) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Density( 
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ Float64 *w) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Density( 
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 w) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMaterialVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMaterial * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMaterial * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMaterial * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_E )( 
            IMaterial * This,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ Float64 *E);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_E )( 
            IMaterial * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 E);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Density )( 
            IMaterial * This,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ Float64 *w);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Density )( 
            IMaterial * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 w);
        
        END_INTERFACE
    } IMaterialVtbl;

    interface IMaterial
    {
        CONST_VTBL struct IMaterialVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMaterial_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMaterial_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMaterial_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMaterial_get_E(This,stageIdx,E)	\
    ( (This)->lpVtbl -> get_E(This,stageIdx,E) ) 

#define IMaterial_put_E(This,stageIdx,E)	\
    ( (This)->lpVtbl -> put_E(This,stageIdx,E) ) 

#define IMaterial_get_Density(This,stageIdx,w)	\
    ( (This)->lpVtbl -> get_Density(This,stageIdx,w) ) 

#define IMaterial_put_Density(This,stageIdx,w)	\
    ( (This)->lpVtbl -> put_Density(This,stageIdx,w) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMaterial_INTERFACE_DEFINED__ */


#ifndef __IItemData_INTERFACE_DEFINED__
#define __IItemData_INTERFACE_DEFINED__

/* interface IItemData */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IItemData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36BB7165-1665-47a2-9A17-D9CA5E6DCCAB")
    IItemData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddItemData( 
            /* [in] */ BSTR name,
            /* [in] */ IUnknown *data) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetItemData( 
            /* [in] */ BSTR name,
            /* [retval][out] */ IUnknown **data) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveItemData( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetItemDataCount( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IItemDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IItemData * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IItemData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IItemData * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddItemData )( 
            IItemData * This,
            /* [in] */ BSTR name,
            /* [in] */ IUnknown *data);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetItemData )( 
            IItemData * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ IUnknown **data);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveItemData )( 
            IItemData * This,
            /* [in] */ BSTR name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetItemDataCount )( 
            IItemData * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        END_INTERFACE
    } IItemDataVtbl;

    interface IItemData
    {
        CONST_VTBL struct IItemDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IItemData_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IItemData_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IItemData_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IItemData_AddItemData(This,name,data)	\
    ( (This)->lpVtbl -> AddItemData(This,name,data) ) 

#define IItemData_GetItemData(This,name,data)	\
    ( (This)->lpVtbl -> GetItemData(This,name,data) ) 

#define IItemData_RemoveItemData(This,name)	\
    ( (This)->lpVtbl -> RemoveItemData(This,name) ) 

#define IItemData_GetItemDataCount(This,count)	\
    ( (This)->lpVtbl -> GetItemDataCount(This,count) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IItemData_INTERFACE_DEFINED__ */


#ifndef __IPrestressingStrand_INTERFACE_DEFINED__
#define __IPrestressingStrand_INTERFACE_DEFINED__

/* interface IPrestressingStrand */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPrestressingStrand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1568D12A-4F24-449f-8875-6401C56FEF13")
    IPrestressingStrand : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Grade( 
            /* [retval][out] */ StrandGrade *grade) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Grade( 
            /* [in] */ StrandGrade grade) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ StrandType *type) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ StrandType type) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Coating( 
            /* [retval][out] */ StrandCoating *coating) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Coating( 
            /* [in] */ StrandCoating coating) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ StrandSize *size) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Size( 
            /* [in] */ StrandSize size) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InstallationStage( 
            /* [retval][out] */ StageIndexType *pStageIdx) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_InstallationStage( 
            /* [in] */ StageIndexType stageIdx) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NominalDiameter( 
            /* [retval][out] */ Float64 *dps) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NominalArea( 
            /* [retval][out] */ Float64 *aps) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UltimateStrength( 
            /* [retval][out] */ Float64 *fpu) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_YieldStrength( 
            /* [retval][out] */ Float64 *fpy) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ModulusE( 
            /* [retval][out] */ Float64 *e) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPrestressingStrandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPrestressingStrand * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPrestressingStrand * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPrestressingStrand * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IPrestressingStrand * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IPrestressingStrand * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Grade )( 
            IPrestressingStrand * This,
            /* [retval][out] */ StrandGrade *grade);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Grade )( 
            IPrestressingStrand * This,
            /* [in] */ StrandGrade grade);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IPrestressingStrand * This,
            /* [retval][out] */ StrandType *type);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IPrestressingStrand * This,
            /* [in] */ StrandType type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Coating )( 
            IPrestressingStrand * This,
            /* [retval][out] */ StrandCoating *coating);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Coating )( 
            IPrestressingStrand * This,
            /* [in] */ StrandCoating coating);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IPrestressingStrand * This,
            /* [retval][out] */ StrandSize *size);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            IPrestressingStrand * This,
            /* [in] */ StrandSize size);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InstallationStage )( 
            IPrestressingStrand * This,
            /* [retval][out] */ StageIndexType *pStageIdx);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InstallationStage )( 
            IPrestressingStrand * This,
            /* [in] */ StageIndexType stageIdx);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NominalDiameter )( 
            IPrestressingStrand * This,
            /* [retval][out] */ Float64 *dps);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NominalArea )( 
            IPrestressingStrand * This,
            /* [retval][out] */ Float64 *aps);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UltimateStrength )( 
            IPrestressingStrand * This,
            /* [retval][out] */ Float64 *fpu);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_YieldStrength )( 
            IPrestressingStrand * This,
            /* [retval][out] */ Float64 *fpy);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ModulusE )( 
            IPrestressingStrand * This,
            /* [retval][out] */ Float64 *e);
        
        END_INTERFACE
    } IPrestressingStrandVtbl;

    interface IPrestressingStrand
    {
        CONST_VTBL struct IPrestressingStrandVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrestressingStrand_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPrestressingStrand_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPrestressingStrand_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPrestressingStrand_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IPrestressingStrand_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 

#define IPrestressingStrand_get_Grade(This,grade)	\
    ( (This)->lpVtbl -> get_Grade(This,grade) ) 

#define IPrestressingStrand_put_Grade(This,grade)	\
    ( (This)->lpVtbl -> put_Grade(This,grade) ) 

#define IPrestressingStrand_get_Type(This,type)	\
    ( (This)->lpVtbl -> get_Type(This,type) ) 

#define IPrestressingStrand_put_Type(This,type)	\
    ( (This)->lpVtbl -> put_Type(This,type) ) 

#define IPrestressingStrand_get_Coating(This,coating)	\
    ( (This)->lpVtbl -> get_Coating(This,coating) ) 

#define IPrestressingStrand_put_Coating(This,coating)	\
    ( (This)->lpVtbl -> put_Coating(This,coating) ) 

#define IPrestressingStrand_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define IPrestressingStrand_put_Size(This,size)	\
    ( (This)->lpVtbl -> put_Size(This,size) ) 

#define IPrestressingStrand_get_InstallationStage(This,pStageIdx)	\
    ( (This)->lpVtbl -> get_InstallationStage(This,pStageIdx) ) 

#define IPrestressingStrand_put_InstallationStage(This,stageIdx)	\
    ( (This)->lpVtbl -> put_InstallationStage(This,stageIdx) ) 

#define IPrestressingStrand_get_NominalDiameter(This,dps)	\
    ( (This)->lpVtbl -> get_NominalDiameter(This,dps) ) 

#define IPrestressingStrand_get_NominalArea(This,aps)	\
    ( (This)->lpVtbl -> get_NominalArea(This,aps) ) 

#define IPrestressingStrand_get_UltimateStrength(This,fpu)	\
    ( (This)->lpVtbl -> get_UltimateStrength(This,fpu) ) 

#define IPrestressingStrand_get_YieldStrength(This,fpy)	\
    ( (This)->lpVtbl -> get_YieldStrength(This,fpy) ) 

#define IPrestressingStrand_get_ModulusE(This,e)	\
    ( (This)->lpVtbl -> get_ModulusE(This,e) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPrestressingStrand_INTERFACE_DEFINED__ */


#ifndef __IOverhangPathStrategy_INTERFACE_DEFINED__
#define __IOverhangPathStrategy_INTERFACE_DEFINED__

/* interface IOverhangPathStrategy */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IOverhangPathStrategy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86C8373C-8E36-4413-BFE6-B32F5E176100")
    IOverhangPathStrategy : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ IPath **path) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IOverhangPathStrategyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOverhangPathStrategy * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOverhangPathStrategy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOverhangPathStrategy * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Path )( 
            IOverhangPathStrategy * This,
            /* [retval][out] */ IPath **path);
        
        END_INTERFACE
    } IOverhangPathStrategyVtbl;

    interface IOverhangPathStrategy
    {
        CONST_VTBL struct IOverhangPathStrategyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOverhangPathStrategy_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOverhangPathStrategy_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOverhangPathStrategy_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOverhangPathStrategy_get_Path(This,path)	\
    ( (This)->lpVtbl -> get_Path(This,path) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOverhangPathStrategy_INTERFACE_DEFINED__ */


#ifndef __IAlignmentOffsetStrategy_INTERFACE_DEFINED__
#define __IAlignmentOffsetStrategy_INTERFACE_DEFINED__

/* interface IAlignmentOffsetStrategy */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAlignmentOffsetStrategy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3E603B81-D649-4ffc-A220-B3EA22343A3D")
    IAlignmentOffsetStrategy : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Alignment( 
            /* [in] */ IAlignment *alignment) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Offset( 
            /* [in] */ Float64 offset) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAlignmentOffsetStrategyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAlignmentOffsetStrategy * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAlignmentOffsetStrategy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAlignmentOffsetStrategy * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Alignment )( 
            IAlignmentOffsetStrategy * This,
            /* [in] */ IAlignment *alignment);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Offset )( 
            IAlignmentOffsetStrategy * This,
            /* [in] */ Float64 offset);
        
        END_INTERFACE
    } IAlignmentOffsetStrategyVtbl;

    interface IAlignmentOffsetStrategy
    {
        CONST_VTBL struct IAlignmentOffsetStrategyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlignmentOffsetStrategy_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAlignmentOffsetStrategy_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAlignmentOffsetStrategy_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAlignmentOffsetStrategy_putref_Alignment(This,alignment)	\
    ( (This)->lpVtbl -> putref_Alignment(This,alignment) ) 

#define IAlignmentOffsetStrategy_put_Offset(This,offset)	\
    ( (This)->lpVtbl -> put_Offset(This,offset) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAlignmentOffsetStrategy_INTERFACE_DEFINED__ */


#ifndef __IEdgePathStrategy_INTERFACE_DEFINED__
#define __IEdgePathStrategy_INTERFACE_DEFINED__

/* interface IEdgePathStrategy */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IEdgePathStrategy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6D10EA7C-E16D-4dc1-8189-4B91C0441072")
    IEdgePathStrategy : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Path( 
            /* [in] */ IPath *path) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEdgePathStrategyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEdgePathStrategy * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEdgePathStrategy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEdgePathStrategy * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Path )( 
            IEdgePathStrategy * This,
            /* [in] */ IPath *path);
        
        END_INTERFACE
    } IEdgePathStrategyVtbl;

    interface IEdgePathStrategy
    {
        CONST_VTBL struct IEdgePathStrategyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEdgePathStrategy_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEdgePathStrategy_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEdgePathStrategy_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEdgePathStrategy_putref_Path(This,path)	\
    ( (This)->lpVtbl -> putref_Path(This,path) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEdgePathStrategy_INTERFACE_DEFINED__ */


#ifndef __IBridgeDeck_INTERFACE_DEFINED__
#define __IBridgeDeck_INTERFACE_DEFINED__

/* interface IBridgeDeck */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBridgeDeck;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DD39558A-CEEF-446f-AB50-EC6085D087FC")
    IBridgeDeck : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_DeckBoundary( 
            /* [in] */ IDeckBoundary *deckBoundary) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DeckBoundary( 
            /* [retval][out] */ IDeckBoundary **deckBoundary) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Composite( 
            /* [retval][out] */ VARIANT_BOOL *bComposite) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Composite( 
            /* [in] */ VARIANT_BOOL bComposite) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Material( 
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Material( 
            /* [in] */ IMaterial *material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuralDepth( 
            /* [retval][out] */ Float64 *depth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GrossDepth( 
            /* [retval][out] */ Float64 *depth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayout( 
            /* [retval][out] */ IBridgeDeckRebarLayout **rebarLayout) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_RebarLayout( 
            /* [in] */ IBridgeDeckRebarLayout *rebarLayout) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Bridge( 
            /* [in] */ IGenericBridge *pBridge) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Bridge( 
            /* [retval][out] */ IGenericBridge **ppBridge) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBridgeDeckVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBridgeDeck * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBridgeDeck * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBridgeDeck * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DeckBoundary )( 
            IBridgeDeck * This,
            /* [in] */ IDeckBoundary *deckBoundary);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeckBoundary )( 
            IBridgeDeck * This,
            /* [retval][out] */ IDeckBoundary **deckBoundary);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Composite )( 
            IBridgeDeck * This,
            /* [retval][out] */ VARIANT_BOOL *bComposite);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Composite )( 
            IBridgeDeck * This,
            /* [in] */ VARIANT_BOOL bComposite);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Material )( 
            IBridgeDeck * This,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Material )( 
            IBridgeDeck * This,
            /* [in] */ IMaterial *material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuralDepth )( 
            IBridgeDeck * This,
            /* [retval][out] */ Float64 *depth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GrossDepth )( 
            IBridgeDeck * This,
            /* [retval][out] */ Float64 *depth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayout )( 
            IBridgeDeck * This,
            /* [retval][out] */ IBridgeDeckRebarLayout **rebarLayout);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarLayout )( 
            IBridgeDeck * This,
            /* [in] */ IBridgeDeckRebarLayout *rebarLayout);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Bridge )( 
            IBridgeDeck * This,
            /* [in] */ IGenericBridge *pBridge);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bridge )( 
            IBridgeDeck * This,
            /* [retval][out] */ IGenericBridge **ppBridge);
        
        END_INTERFACE
    } IBridgeDeckVtbl;

    interface IBridgeDeck
    {
        CONST_VTBL struct IBridgeDeckVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBridgeDeck_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBridgeDeck_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBridgeDeck_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBridgeDeck_putref_DeckBoundary(This,deckBoundary)	\
    ( (This)->lpVtbl -> putref_DeckBoundary(This,deckBoundary) ) 

#define IBridgeDeck_get_DeckBoundary(This,deckBoundary)	\
    ( (This)->lpVtbl -> get_DeckBoundary(This,deckBoundary) ) 

#define IBridgeDeck_get_Composite(This,bComposite)	\
    ( (This)->lpVtbl -> get_Composite(This,bComposite) ) 

#define IBridgeDeck_put_Composite(This,bComposite)	\
    ( (This)->lpVtbl -> put_Composite(This,bComposite) ) 

#define IBridgeDeck_get_Material(This,material)	\
    ( (This)->lpVtbl -> get_Material(This,material) ) 

#define IBridgeDeck_putref_Material(This,material)	\
    ( (This)->lpVtbl -> putref_Material(This,material) ) 

#define IBridgeDeck_get_StructuralDepth(This,depth)	\
    ( (This)->lpVtbl -> get_StructuralDepth(This,depth) ) 

#define IBridgeDeck_get_GrossDepth(This,depth)	\
    ( (This)->lpVtbl -> get_GrossDepth(This,depth) ) 

#define IBridgeDeck_get_RebarLayout(This,rebarLayout)	\
    ( (This)->lpVtbl -> get_RebarLayout(This,rebarLayout) ) 

#define IBridgeDeck_putref_RebarLayout(This,rebarLayout)	\
    ( (This)->lpVtbl -> putref_RebarLayout(This,rebarLayout) ) 

#define IBridgeDeck_putref_Bridge(This,pBridge)	\
    ( (This)->lpVtbl -> putref_Bridge(This,pBridge) ) 

#define IBridgeDeck_get_Bridge(This,ppBridge)	\
    ( (This)->lpVtbl -> get_Bridge(This,ppBridge) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBridgeDeck_INTERFACE_DEFINED__ */


#ifndef __ICastSlab_INTERFACE_DEFINED__
#define __ICastSlab_INTERFACE_DEFINED__

/* interface ICastSlab */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICastSlab;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C50BB152-ED63-4842-B17D-437FB98BF2CB")
    ICastSlab : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GrossDepth( 
            /* [retval][out] */ Float64 *depth) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GrossDepth( 
            /* [in] */ Float64 depth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OverhangDepth( 
            /* [retval][out] */ Float64 *depth) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OverhangDepth( 
            /* [in] */ Float64 depth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OverhangTaper( 
            /* [retval][out] */ DeckOverhangTaper *taper) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OverhangTaper( 
            /* [in] */ DeckOverhangTaper taper) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICastSlabVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICastSlab * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICastSlab * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICastSlab * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GrossDepth )( 
            ICastSlab * This,
            /* [retval][out] */ Float64 *depth);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GrossDepth )( 
            ICastSlab * This,
            /* [in] */ Float64 depth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OverhangDepth )( 
            ICastSlab * This,
            /* [retval][out] */ Float64 *depth);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OverhangDepth )( 
            ICastSlab * This,
            /* [in] */ Float64 depth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OverhangTaper )( 
            ICastSlab * This,
            /* [retval][out] */ DeckOverhangTaper *taper);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OverhangTaper )( 
            ICastSlab * This,
            /* [in] */ DeckOverhangTaper taper);
        
        END_INTERFACE
    } ICastSlabVtbl;

    interface ICastSlab
    {
        CONST_VTBL struct ICastSlabVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICastSlab_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICastSlab_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICastSlab_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICastSlab_get_GrossDepth(This,depth)	\
    ( (This)->lpVtbl -> get_GrossDepth(This,depth) ) 

#define ICastSlab_put_GrossDepth(This,depth)	\
    ( (This)->lpVtbl -> put_GrossDepth(This,depth) ) 

#define ICastSlab_get_OverhangDepth(This,depth)	\
    ( (This)->lpVtbl -> get_OverhangDepth(This,depth) ) 

#define ICastSlab_put_OverhangDepth(This,depth)	\
    ( (This)->lpVtbl -> put_OverhangDepth(This,depth) ) 

#define ICastSlab_get_OverhangTaper(This,taper)	\
    ( (This)->lpVtbl -> get_OverhangTaper(This,taper) ) 

#define ICastSlab_put_OverhangTaper(This,taper)	\
    ( (This)->lpVtbl -> put_OverhangTaper(This,taper) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICastSlab_INTERFACE_DEFINED__ */


#ifndef __IPrecastSlab_INTERFACE_DEFINED__
#define __IPrecastSlab_INTERFACE_DEFINED__

/* interface IPrecastSlab */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPrecastSlab;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F2653B5B-970A-4914-B3EE-A134FCAC6E00")
    IPrecastSlab : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CastDepth( 
            /* [retval][out] */ Float64 *depth) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CastDepth( 
            /* [in] */ Float64 depth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PanelDepth( 
            /* [retval][out] */ Float64 *depth) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PanelDepth( 
            /* [in] */ Float64 depth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OverhangDepth( 
            /* [retval][out] */ Float64 *depth) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OverhangDepth( 
            /* [in] */ Float64 depth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OverhangTaper( 
            /* [retval][out] */ DeckOverhangTaper *taper) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OverhangTaper( 
            /* [in] */ DeckOverhangTaper taper) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPrecastSlabVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPrecastSlab * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPrecastSlab * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPrecastSlab * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CastDepth )( 
            IPrecastSlab * This,
            /* [retval][out] */ Float64 *depth);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CastDepth )( 
            IPrecastSlab * This,
            /* [in] */ Float64 depth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PanelDepth )( 
            IPrecastSlab * This,
            /* [retval][out] */ Float64 *depth);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PanelDepth )( 
            IPrecastSlab * This,
            /* [in] */ Float64 depth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OverhangDepth )( 
            IPrecastSlab * This,
            /* [retval][out] */ Float64 *depth);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OverhangDepth )( 
            IPrecastSlab * This,
            /* [in] */ Float64 depth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OverhangTaper )( 
            IPrecastSlab * This,
            /* [retval][out] */ DeckOverhangTaper *taper);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OverhangTaper )( 
            IPrecastSlab * This,
            /* [in] */ DeckOverhangTaper taper);
        
        END_INTERFACE
    } IPrecastSlabVtbl;

    interface IPrecastSlab
    {
        CONST_VTBL struct IPrecastSlabVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrecastSlab_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPrecastSlab_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPrecastSlab_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPrecastSlab_get_CastDepth(This,depth)	\
    ( (This)->lpVtbl -> get_CastDepth(This,depth) ) 

#define IPrecastSlab_put_CastDepth(This,depth)	\
    ( (This)->lpVtbl -> put_CastDepth(This,depth) ) 

#define IPrecastSlab_get_PanelDepth(This,depth)	\
    ( (This)->lpVtbl -> get_PanelDepth(This,depth) ) 

#define IPrecastSlab_put_PanelDepth(This,depth)	\
    ( (This)->lpVtbl -> put_PanelDepth(This,depth) ) 

#define IPrecastSlab_get_OverhangDepth(This,depth)	\
    ( (This)->lpVtbl -> get_OverhangDepth(This,depth) ) 

#define IPrecastSlab_put_OverhangDepth(This,depth)	\
    ( (This)->lpVtbl -> put_OverhangDepth(This,depth) ) 

#define IPrecastSlab_get_OverhangTaper(This,taper)	\
    ( (This)->lpVtbl -> get_OverhangTaper(This,taper) ) 

#define IPrecastSlab_put_OverhangTaper(This,taper)	\
    ( (This)->lpVtbl -> put_OverhangTaper(This,taper) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPrecastSlab_INTERFACE_DEFINED__ */


#ifndef __IOverlaySlab_INTERFACE_DEFINED__
#define __IOverlaySlab_INTERFACE_DEFINED__

/* interface IOverlaySlab */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IOverlaySlab;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("69308B82-EB06-4128-BE34-FDEAEBE75132")
    IOverlaySlab : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GrossDepth( 
            /* [retval][out] */ Float64 *depth) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GrossDepth( 
            /* [in] */ Float64 depth) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IOverlaySlabVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOverlaySlab * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOverlaySlab * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOverlaySlab * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GrossDepth )( 
            IOverlaySlab * This,
            /* [retval][out] */ Float64 *depth);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GrossDepth )( 
            IOverlaySlab * This,
            /* [in] */ Float64 depth);
        
        END_INTERFACE
    } IOverlaySlabVtbl;

    interface IOverlaySlab
    {
        CONST_VTBL struct IOverlaySlabVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOverlaySlab_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOverlaySlab_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOverlaySlab_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOverlaySlab_get_GrossDepth(This,depth)	\
    ( (This)->lpVtbl -> get_GrossDepth(This,depth) ) 

#define IOverlaySlab_put_GrossDepth(This,depth)	\
    ( (This)->lpVtbl -> put_GrossDepth(This,depth) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOverlaySlab_INTERFACE_DEFINED__ */


#ifndef __IBarrier_INTERFACE_DEFINED__
#define __IBarrier_INTERFACE_DEFINED__

/* interface IBarrier */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBarrier;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("84BDBE3E-928A-4a78-BF9B-39AE1AB8E6F9")
    IBarrier : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **shape) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Material( 
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Material( 
            /* [in] */ IMaterial *material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurbLocation( 
            /* [retval][out] */ Float64 *width) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BarrierToeLocations( 
            /* [out] */ Float64 *interiorToe,
            /* [out] */ Float64 *exteriorToe) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IBarrier **barrier) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBarrierVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBarrier * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBarrier * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBarrier * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IBarrier * This,
            /* [retval][out] */ IShape **shape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Material )( 
            IBarrier * This,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Material )( 
            IBarrier * This,
            /* [in] */ IMaterial *material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbLocation )( 
            IBarrier * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BarrierToeLocations )( 
            IBarrier * This,
            /* [out] */ Float64 *interiorToe,
            /* [out] */ Float64 *exteriorToe);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IBarrier * This,
            /* [retval][out] */ IBarrier **barrier);
        
        END_INTERFACE
    } IBarrierVtbl;

    interface IBarrier
    {
        CONST_VTBL struct IBarrierVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBarrier_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBarrier_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBarrier_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBarrier_get_Shape(This,shape)	\
    ( (This)->lpVtbl -> get_Shape(This,shape) ) 

#define IBarrier_get_Material(This,material)	\
    ( (This)->lpVtbl -> get_Material(This,material) ) 

#define IBarrier_putref_Material(This,material)	\
    ( (This)->lpVtbl -> putref_Material(This,material) ) 

#define IBarrier_get_CurbLocation(This,width)	\
    ( (This)->lpVtbl -> get_CurbLocation(This,width) ) 

#define IBarrier_get_BarrierToeLocations(This,interiorToe,exteriorToe)	\
    ( (This)->lpVtbl -> get_BarrierToeLocations(This,interiorToe,exteriorToe) ) 

#define IBarrier_Clone(This,barrier)	\
    ( (This)->lpVtbl -> Clone(This,barrier) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBarrier_INTERFACE_DEFINED__ */


#ifndef __IGenericBarrier_INTERFACE_DEFINED__
#define __IGenericBarrier_INTERFACE_DEFINED__

/* interface IGenericBarrier */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGenericBarrier;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("41B59BA7-844E-4f23-9056-B1ECCF6E7706")
    IGenericBarrier : public IBarrier
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IShape *shape,
            /* [in] */ Float64 curbWidth,
            /* [in] */ Float64 interiorToe,
            /* [in] */ Float64 exteriorToe) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGenericBarrierVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGenericBarrier * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGenericBarrier * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGenericBarrier * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IGenericBarrier * This,
            /* [retval][out] */ IShape **shape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Material )( 
            IGenericBarrier * This,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Material )( 
            IGenericBarrier * This,
            /* [in] */ IMaterial *material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbLocation )( 
            IGenericBarrier * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BarrierToeLocations )( 
            IGenericBarrier * This,
            /* [out] */ Float64 *interiorToe,
            /* [out] */ Float64 *exteriorToe);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IGenericBarrier * This,
            /* [retval][out] */ IBarrier **barrier);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IGenericBarrier * This,
            /* [in] */ IShape *shape,
            /* [in] */ Float64 curbWidth,
            /* [in] */ Float64 interiorToe,
            /* [in] */ Float64 exteriorToe);
        
        END_INTERFACE
    } IGenericBarrierVtbl;

    interface IGenericBarrier
    {
        CONST_VTBL struct IGenericBarrierVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGenericBarrier_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGenericBarrier_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGenericBarrier_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGenericBarrier_get_Shape(This,shape)	\
    ( (This)->lpVtbl -> get_Shape(This,shape) ) 

#define IGenericBarrier_get_Material(This,material)	\
    ( (This)->lpVtbl -> get_Material(This,material) ) 

#define IGenericBarrier_putref_Material(This,material)	\
    ( (This)->lpVtbl -> putref_Material(This,material) ) 

#define IGenericBarrier_get_CurbLocation(This,width)	\
    ( (This)->lpVtbl -> get_CurbLocation(This,width) ) 

#define IGenericBarrier_get_BarrierToeLocations(This,interiorToe,exteriorToe)	\
    ( (This)->lpVtbl -> get_BarrierToeLocations(This,interiorToe,exteriorToe) ) 

#define IGenericBarrier_Clone(This,barrier)	\
    ( (This)->lpVtbl -> Clone(This,barrier) ) 


#define IGenericBarrier_Init(This,shape,curbWidth,interiorToe,exteriorToe)	\
    ( (This)->lpVtbl -> Init(This,shape,curbWidth,interiorToe,exteriorToe) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGenericBarrier_INTERFACE_DEFINED__ */


#ifndef __IFShapeBarrier_INTERFACE_DEFINED__
#define __IFShapeBarrier_INTERFACE_DEFINED__

/* interface IFShapeBarrier */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFShapeBarrier;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("98E8E982-FFDF-48a5-9B5D-0189F803144B")
    IFShapeBarrier : public IBarrier
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Shape( 
            /* [in] */ ITrafficBarrier *shape) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFShapeBarrierVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFShapeBarrier * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFShapeBarrier * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFShapeBarrier * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IFShapeBarrier * This,
            /* [retval][out] */ IShape **shape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Material )( 
            IFShapeBarrier * This,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Material )( 
            IFShapeBarrier * This,
            /* [in] */ IMaterial *material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbLocation )( 
            IFShapeBarrier * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BarrierToeLocations )( 
            IFShapeBarrier * This,
            /* [out] */ Float64 *interiorToe,
            /* [out] */ Float64 *exteriorToe);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFShapeBarrier * This,
            /* [retval][out] */ IBarrier **barrier);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Shape )( 
            IFShapeBarrier * This,
            /* [in] */ ITrafficBarrier *shape);
        
        END_INTERFACE
    } IFShapeBarrierVtbl;

    interface IFShapeBarrier
    {
        CONST_VTBL struct IFShapeBarrierVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFShapeBarrier_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFShapeBarrier_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFShapeBarrier_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFShapeBarrier_get_Shape(This,shape)	\
    ( (This)->lpVtbl -> get_Shape(This,shape) ) 

#define IFShapeBarrier_get_Material(This,material)	\
    ( (This)->lpVtbl -> get_Material(This,material) ) 

#define IFShapeBarrier_putref_Material(This,material)	\
    ( (This)->lpVtbl -> putref_Material(This,material) ) 

#define IFShapeBarrier_get_CurbLocation(This,width)	\
    ( (This)->lpVtbl -> get_CurbLocation(This,width) ) 

#define IFShapeBarrier_get_BarrierToeLocations(This,interiorToe,exteriorToe)	\
    ( (This)->lpVtbl -> get_BarrierToeLocations(This,interiorToe,exteriorToe) ) 

#define IFShapeBarrier_Clone(This,barrier)	\
    ( (This)->lpVtbl -> Clone(This,barrier) ) 


#define IFShapeBarrier_put_Shape(This,shape)	\
    ( (This)->lpVtbl -> put_Shape(This,shape) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFShapeBarrier_INTERFACE_DEFINED__ */


#ifndef __ISidewalkBarrier_INTERFACE_DEFINED__
#define __ISidewalkBarrier_INTERFACE_DEFINED__

/* interface ISidewalkBarrier */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISidewalkBarrier;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6ED29E23-2D11-4391-932A-6DEC77964D4B")
    ISidewalkBarrier : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Barrier1( 
            /* [in] */ IBarrier *extBarrier,
            /* [in] */ TrafficBarrierOrientation orientation) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Barrier2( 
            /* [in] */ IBarrier *extBarrier,
            /* [in] */ Float64 h1,
            /* [in] */ Float64 h2,
            /* [in] */ Float64 swWidth,
            /* [in] */ TrafficBarrierOrientation orientation,
            /* [in] */ SidewalkPositionType swPosition) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Barrier3( 
            /* [in] */ IBarrier *extBarrier,
            /* [in] */ Float64 h1,
            /* [in] */ Float64 h2,
            /* [in] */ Float64 swWidth,
            /* [in] */ TrafficBarrierOrientation orientation,
            /* [in] */ SidewalkPositionType swPosition,
            /* [in] */ IBarrier *intBarrier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HasSidewalk( 
            /* [retval][out] */ VARIANT_BOOL *pbHasSidewalk) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HasInteriorBarrier( 
            /* [retval][out] */ VARIANT_BOOL *pbHasBarrier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SidewalkWidth( 
            /* [retval][out] */ Float64 *swWidth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **shape) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuralShape( 
            /* [retval][out] */ IShape **shape) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExteriorBarrier( 
            /* [retval][out] */ IBarrier **barr) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InteriorBarrier( 
            /* [retval][out] */ IBarrier **barr) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SidewalkShape( 
            /* [retval][out] */ IShape **shape) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ IPath **path) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Path( 
            /* [in] */ IPath *path) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IsInteriorStructurallyContinuous( 
            /* [in] */ VARIANT_BOOL bContinuous) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IsSidewalkStructurallyContinuous( 
            /* [in] */ VARIANT_BOOL bContinuous) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IsExteriorStructurallyContinuous( 
            /* [in] */ VARIANT_BOOL bContinuous) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsStructurallyContinuous( 
            /* [retval][out] */ VARIANT_BOOL *pbContinuous) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SidewalkPosition( 
            /* [retval][out] */ SidewalkPositionType *posType) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExteriorCurbWidth( 
            /* [retval][out] */ Float64 *width) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurbWidth( 
            /* [retval][out] */ Float64 *width) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OverlayToeWidth( 
            /* [retval][out] */ Float64 *toeWidth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISidewalkBarrier **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISidewalkBarrierVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISidewalkBarrier * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISidewalkBarrier * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISidewalkBarrier * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Barrier1 )( 
            ISidewalkBarrier * This,
            /* [in] */ IBarrier *extBarrier,
            /* [in] */ TrafficBarrierOrientation orientation);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Barrier2 )( 
            ISidewalkBarrier * This,
            /* [in] */ IBarrier *extBarrier,
            /* [in] */ Float64 h1,
            /* [in] */ Float64 h2,
            /* [in] */ Float64 swWidth,
            /* [in] */ TrafficBarrierOrientation orientation,
            /* [in] */ SidewalkPositionType swPosition);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Barrier3 )( 
            ISidewalkBarrier * This,
            /* [in] */ IBarrier *extBarrier,
            /* [in] */ Float64 h1,
            /* [in] */ Float64 h2,
            /* [in] */ Float64 swWidth,
            /* [in] */ TrafficBarrierOrientation orientation,
            /* [in] */ SidewalkPositionType swPosition,
            /* [in] */ IBarrier *intBarrier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasSidewalk )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ VARIANT_BOOL *pbHasSidewalk);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasInteriorBarrier )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ VARIANT_BOOL *pbHasBarrier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SidewalkWidth )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ Float64 *swWidth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ IShape **shape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuralShape )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ IShape **shape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExteriorBarrier )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ IBarrier **barr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InteriorBarrier )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ IBarrier **barr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SidewalkShape )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ IShape **shape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Path )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ IPath **path);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Path )( 
            ISidewalkBarrier * This,
            /* [in] */ IPath *path);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsInteriorStructurallyContinuous )( 
            ISidewalkBarrier * This,
            /* [in] */ VARIANT_BOOL bContinuous);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsSidewalkStructurallyContinuous )( 
            ISidewalkBarrier * This,
            /* [in] */ VARIANT_BOOL bContinuous);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsExteriorStructurallyContinuous )( 
            ISidewalkBarrier * This,
            /* [in] */ VARIANT_BOOL bContinuous);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsStructurallyContinuous )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ VARIANT_BOOL *pbContinuous);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SidewalkPosition )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ SidewalkPositionType *posType);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExteriorCurbWidth )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbWidth )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OverlayToeWidth )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ Float64 *toeWidth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISidewalkBarrier * This,
            /* [retval][out] */ ISidewalkBarrier **clone);
        
        END_INTERFACE
    } ISidewalkBarrierVtbl;

    interface ISidewalkBarrier
    {
        CONST_VTBL struct ISidewalkBarrierVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISidewalkBarrier_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISidewalkBarrier_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISidewalkBarrier_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISidewalkBarrier_put_Barrier1(This,extBarrier,orientation)	\
    ( (This)->lpVtbl -> put_Barrier1(This,extBarrier,orientation) ) 

#define ISidewalkBarrier_put_Barrier2(This,extBarrier,h1,h2,swWidth,orientation,swPosition)	\
    ( (This)->lpVtbl -> put_Barrier2(This,extBarrier,h1,h2,swWidth,orientation,swPosition) ) 

#define ISidewalkBarrier_put_Barrier3(This,extBarrier,h1,h2,swWidth,orientation,swPosition,intBarrier)	\
    ( (This)->lpVtbl -> put_Barrier3(This,extBarrier,h1,h2,swWidth,orientation,swPosition,intBarrier) ) 

#define ISidewalkBarrier_get_HasSidewalk(This,pbHasSidewalk)	\
    ( (This)->lpVtbl -> get_HasSidewalk(This,pbHasSidewalk) ) 

#define ISidewalkBarrier_get_HasInteriorBarrier(This,pbHasBarrier)	\
    ( (This)->lpVtbl -> get_HasInteriorBarrier(This,pbHasBarrier) ) 

#define ISidewalkBarrier_get_SidewalkWidth(This,swWidth)	\
    ( (This)->lpVtbl -> get_SidewalkWidth(This,swWidth) ) 

#define ISidewalkBarrier_get_Shape(This,shape)	\
    ( (This)->lpVtbl -> get_Shape(This,shape) ) 

#define ISidewalkBarrier_get_StructuralShape(This,shape)	\
    ( (This)->lpVtbl -> get_StructuralShape(This,shape) ) 

#define ISidewalkBarrier_get_ExteriorBarrier(This,barr)	\
    ( (This)->lpVtbl -> get_ExteriorBarrier(This,barr) ) 

#define ISidewalkBarrier_get_InteriorBarrier(This,barr)	\
    ( (This)->lpVtbl -> get_InteriorBarrier(This,barr) ) 

#define ISidewalkBarrier_get_SidewalkShape(This,shape)	\
    ( (This)->lpVtbl -> get_SidewalkShape(This,shape) ) 

#define ISidewalkBarrier_get_Path(This,path)	\
    ( (This)->lpVtbl -> get_Path(This,path) ) 

#define ISidewalkBarrier_put_Path(This,path)	\
    ( (This)->lpVtbl -> put_Path(This,path) ) 

#define ISidewalkBarrier_put_IsInteriorStructurallyContinuous(This,bContinuous)	\
    ( (This)->lpVtbl -> put_IsInteriorStructurallyContinuous(This,bContinuous) ) 

#define ISidewalkBarrier_put_IsSidewalkStructurallyContinuous(This,bContinuous)	\
    ( (This)->lpVtbl -> put_IsSidewalkStructurallyContinuous(This,bContinuous) ) 

#define ISidewalkBarrier_put_IsExteriorStructurallyContinuous(This,bContinuous)	\
    ( (This)->lpVtbl -> put_IsExteriorStructurallyContinuous(This,bContinuous) ) 

#define ISidewalkBarrier_get_IsStructurallyContinuous(This,pbContinuous)	\
    ( (This)->lpVtbl -> get_IsStructurallyContinuous(This,pbContinuous) ) 

#define ISidewalkBarrier_get_SidewalkPosition(This,posType)	\
    ( (This)->lpVtbl -> get_SidewalkPosition(This,posType) ) 

#define ISidewalkBarrier_get_ExteriorCurbWidth(This,width)	\
    ( (This)->lpVtbl -> get_ExteriorCurbWidth(This,width) ) 

#define ISidewalkBarrier_get_CurbWidth(This,width)	\
    ( (This)->lpVtbl -> get_CurbWidth(This,width) ) 

#define ISidewalkBarrier_get_OverlayToeWidth(This,toeWidth)	\
    ( (This)->lpVtbl -> get_OverlayToeWidth(This,toeWidth) ) 

#define ISidewalkBarrier_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISidewalkBarrier_INTERFACE_DEFINED__ */


#ifndef __IFlangedGirderSection_INTERFACE_DEFINED__
#define __IFlangedGirderSection_INTERFACE_DEFINED__

/* interface IFlangedGirderSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFlangedGirderSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8763E80A-AA45-4EC8-BA44-25890E5B0269")
    IFlangedGirderSection : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ IPrecastBeam *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IPrecastBeam **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFlangedGirderSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFlangedGirderSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFlangedGirderSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFlangedGirderSection * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            IFlangedGirderSection * This,
            /* [in] */ IPrecastBeam *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IFlangedGirderSection * This,
            /* [retval][out] */ IPrecastBeam **beam);
        
        END_INTERFACE
    } IFlangedGirderSectionVtbl;

    interface IFlangedGirderSection
    {
        CONST_VTBL struct IFlangedGirderSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFlangedGirderSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFlangedGirderSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFlangedGirderSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFlangedGirderSection_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define IFlangedGirderSection_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFlangedGirderSection_INTERFACE_DEFINED__ */


#ifndef __ISuperstructureMemberSegment_INTERFACE_DEFINED__
#define __ISuperstructureMemberSegment_INTERFACE_DEFINED__

/* interface ISuperstructureMemberSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISuperstructureMemberSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ACA24CD2-8201-459d-BF2B-D19D7DF87ACF")
    ISuperstructureMemberSegment : public ISegment
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SuperstructureMember( 
            /* [retval][out] */ ISuperstructureMember **ssmbr) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GirderLine( 
            /* [retval][out] */ IGirderLine **girderLine) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutLength( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ Float64 orientation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ Float64 *orientation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHaunchDepth( 
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetHaunchDepth( 
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ComputeHaunchDepth( 
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Fillet( 
            /* [in] */ Float64 Fillet) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Fillet( 
            /* [retval][out] */ Float64 *Fillet) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_SuperstructureMember( 
            /* [in] */ ISuperstructureMember *ssMbr) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_GirderLine( 
            /* [in] */ IGirderLine *girderLine) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperstructureMemberSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperstructureMemberSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperstructureMemberSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ISuperstructureMemberSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            ISuperstructureMemberSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            ISuperstructureMemberSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            ISuperstructureMemberSegment * This,
            /* [retval][out] */ ISuperstructureMember **ssmbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLine )( 
            ISuperstructureMemberSegment * This,
            /* [retval][out] */ IGirderLine **girderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            ISuperstructureMemberSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ Float64 orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            ISuperstructureMemberSegment * This,
            /* [retval][out] */ Float64 *orientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHaunchDepth )( 
            ISuperstructureMemberSegment * This,
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHaunchDepth )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHaunchDepth )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fillet )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ Float64 Fillet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fillet )( 
            ISuperstructureMemberSegment * This,
            /* [retval][out] */ Float64 *Fillet);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ ISuperstructureMember *ssMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_GirderLine )( 
            ISuperstructureMemberSegment * This,
            /* [in] */ IGirderLine *girderLine);
        
        END_INTERFACE
    } ISuperstructureMemberSegmentVtbl;

    interface ISuperstructureMemberSegment
    {
        CONST_VTBL struct ISuperstructureMemberSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperstructureMemberSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperstructureMemberSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperstructureMemberSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperstructureMemberSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ISuperstructureMemberSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define ISuperstructureMemberSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define ISuperstructureMemberSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define ISuperstructureMemberSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define ISuperstructureMemberSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define ISuperstructureMemberSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define ISuperstructureMemberSegment_get_SuperstructureMember(This,ssmbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ssmbr) ) 

#define ISuperstructureMemberSegment_get_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> get_GirderLine(This,girderLine) ) 

#define ISuperstructureMemberSegment_get_LayoutLength(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pVal) ) 

#define ISuperstructureMemberSegment_get_Profile(This,bIncludeClosure,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,bIncludeClosure,ppShape) ) 

#define ISuperstructureMemberSegment_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define ISuperstructureMemberSegment_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define ISuperstructureMemberSegment_GetHaunchDepth(This,pStartVal,pMidVal,pEndVal)	\
    ( (This)->lpVtbl -> GetHaunchDepth(This,pStartVal,pMidVal,pEndVal) ) 

#define ISuperstructureMemberSegment_SetHaunchDepth(This,startVal,midVal,endVal)	\
    ( (This)->lpVtbl -> SetHaunchDepth(This,startVal,midVal,endVal) ) 

#define ISuperstructureMemberSegment_ComputeHaunchDepth(This,distAlongSegment,pVal)	\
    ( (This)->lpVtbl -> ComputeHaunchDepth(This,distAlongSegment,pVal) ) 

#define ISuperstructureMemberSegment_put_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> put_Fillet(This,Fillet) ) 

#define ISuperstructureMemberSegment_get_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> get_Fillet(This,Fillet) ) 

#define ISuperstructureMemberSegment_putref_SuperstructureMember(This,ssMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,ssMbr) ) 

#define ISuperstructureMemberSegment_putref_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> putref_GirderLine(This,girderLine) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperstructureMemberSegment_INTERFACE_DEFINED__ */


#ifndef __IEnumSegment_INTERFACE_DEFINED__
#define __IEnumSegment_INTERFACE_DEFINED__

/* interface IEnumSegment */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("81007B86-0AD9-4a41-B9E2-721E31D93E20")
    IEnumSegment : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSegment **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISegment **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSegment * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSegment * This,
            /* [out] */ IEnumSegment **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSegment * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISegment **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSegment * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSegment * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSegmentVtbl;

    interface IEnumSegment
    {
        CONST_VTBL struct IEnumSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSegment_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSegment_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSegment_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSegment_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSegment_INTERFACE_DEFINED__ */


#ifndef __IFilteredSegmentCollection_INTERFACE_DEFINED__
#define __IFilteredSegmentCollection_INTERFACE_DEFINED__

/* interface IFilteredSegmentCollection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFilteredSegmentCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BD0F3210-F763-4787-9C5A-68E069918CFF")
    IFilteredSegmentCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ISegment **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSegment **pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFilteredSegmentCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFilteredSegmentCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFilteredSegmentCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFilteredSegmentCollection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFilteredSegmentCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFilteredSegmentCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ISegment **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFilteredSegmentCollection * This,
            /* [retval][out] */ IEnumSegment **pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFilteredSegmentCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } IFilteredSegmentCollectionVtbl;

    interface IFilteredSegmentCollection
    {
        CONST_VTBL struct IFilteredSegmentCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilteredSegmentCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFilteredSegmentCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFilteredSegmentCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFilteredSegmentCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFilteredSegmentCollection_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IFilteredSegmentCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFilteredSegmentCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFilteredSegmentCollection_INTERFACE_DEFINED__ */


#ifndef __ISegmentItem_INTERFACE_DEFINED__
#define __ISegmentItem_INTERFACE_DEFINED__

/* interface ISegmentItem */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISegmentItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DAC15BD1-5791-4c24-B4AA-3A71A27C82A4")
    ISegmentItem : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RelPosition( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Segment( 
            /* [retval][out] */ ISegment **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISegmentItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISegmentItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISegmentItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISegmentItem * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RelPosition )( 
            ISegmentItem * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Segment )( 
            ISegmentItem * This,
            /* [retval][out] */ ISegment **pVal);
        
        END_INTERFACE
    } ISegmentItemVtbl;

    interface ISegmentItem
    {
        CONST_VTBL struct ISegmentItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISegmentItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISegmentItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISegmentItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISegmentItem_get_RelPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_RelPosition(This,pVal) ) 

#define ISegmentItem_get_Segment(This,pVal)	\
    ( (This)->lpVtbl -> get_Segment(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISegmentItem_INTERFACE_DEFINED__ */


#ifndef __IEnumSuperstructureMembers_INTERFACE_DEFINED__
#define __IEnumSuperstructureMembers_INTERFACE_DEFINED__

/* interface IEnumSuperstructureMembers */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSuperstructureMembers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3B0C73B3-9A2E-4ea0-A327-F54E11DC896B")
    IEnumSuperstructureMembers : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSuperstructureMembers **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISuperstructureMember **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSuperstructureMembersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSuperstructureMembers * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSuperstructureMembers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSuperstructureMembers * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSuperstructureMembers * This,
            /* [out] */ IEnumSuperstructureMembers **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSuperstructureMembers * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISuperstructureMember **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSuperstructureMembers * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSuperstructureMembers * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSuperstructureMembersVtbl;

    interface IEnumSuperstructureMembers
    {
        CONST_VTBL struct IEnumSuperstructureMembersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSuperstructureMembers_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSuperstructureMembers_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSuperstructureMembers_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSuperstructureMembers_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSuperstructureMembers_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSuperstructureMembers_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSuperstructureMembers_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSuperstructureMembers_INTERFACE_DEFINED__ */


#ifndef __ISuperstructureMemberCollection_INTERFACE_DEFINED__
#define __ISuperstructureMemberCollection_INTERFACE_DEFINED__

/* interface ISuperstructureMemberCollection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISuperstructureMemberCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6129251E-9A42-4af7-8090-20DC84F50E94")
    ISuperstructureMemberCollection : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ISuperstructureMember *pSSMbr) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ISuperstructureMember **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSuperstructureMembers **pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType Index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ ISuperstructureMember *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperstructureMemberCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperstructureMemberCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperstructureMemberCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperstructureMemberCollection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISuperstructureMemberCollection * This,
            /* [in] */ ISuperstructureMember *pSSMbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISuperstructureMemberCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISuperstructureMemberCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ISuperstructureMember **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ISuperstructureMemberCollection * This,
            /* [retval][out] */ IEnumSuperstructureMembers **pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISuperstructureMemberCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ISuperstructureMemberCollection * This,
            /* [in] */ CollectionIndexType Index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISuperstructureMemberCollection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            ISuperstructureMemberCollection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ISuperstructureMemberCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ ISuperstructureMember *pVal);
        
        END_INTERFACE
    } ISuperstructureMemberCollectionVtbl;

    interface ISuperstructureMemberCollection
    {
        CONST_VTBL struct ISuperstructureMemberCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperstructureMemberCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperstructureMemberCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperstructureMemberCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperstructureMemberCollection_Add(This,pSSMbr)	\
    ( (This)->lpVtbl -> Add(This,pSSMbr) ) 

#define ISuperstructureMemberCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISuperstructureMemberCollection_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ISuperstructureMemberCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ISuperstructureMemberCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ISuperstructureMemberCollection_Remove(This,Index)	\
    ( (This)->lpVtbl -> Remove(This,Index) ) 

#define ISuperstructureMemberCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ISuperstructureMemberCollection_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define ISuperstructureMemberCollection_Insert(This,index,pVal)	\
    ( (This)->lpVtbl -> Insert(This,index,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperstructureMemberCollection_INTERFACE_DEFINED__ */


#ifndef __IPrismaticSegment_INTERFACE_DEFINED__
#define __IPrismaticSegment_INTERFACE_DEFINED__

/* interface IPrismaticSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPrismaticSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("67BE2D86-DCB1-40ae-AF16-59A766AE95C1")
    IPrismaticSegment : public ISegment
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ IndexType *pCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPrismaticSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPrismaticSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPrismaticSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPrismaticSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IPrismaticSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            IPrismaticSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IPrismaticSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            IPrismaticSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            IPrismaticSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            IPrismaticSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            IPrismaticSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            IPrismaticSegment * This,
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            IPrismaticSegment * This,
            /* [retval][out] */ IndexType *pCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            IPrismaticSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            IPrismaticSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        END_INTERFACE
    } IPrismaticSegmentVtbl;

    interface IPrismaticSegment
    {
        CONST_VTBL struct IPrismaticSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrismaticSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPrismaticSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPrismaticSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPrismaticSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define IPrismaticSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define IPrismaticSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define IPrismaticSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define IPrismaticSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define IPrismaticSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define IPrismaticSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define IPrismaticSegment_AddShape(This,pShape,pFGMaterial,pBGMaterial)	\
    ( (This)->lpVtbl -> AddShape(This,pShape,pFGMaterial,pBGMaterial) ) 

#define IPrismaticSegment_get_ShapeCount(This,pCount)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,pCount) ) 

#define IPrismaticSegment_get_ForegroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,idx,material) ) 

#define IPrismaticSegment_get_BackgroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,idx,material) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPrismaticSegment_INTERFACE_DEFINED__ */


#ifndef __IPrismaticSuperstructureMemberSegment_INTERFACE_DEFINED__
#define __IPrismaticSuperstructureMemberSegment_INTERFACE_DEFINED__

/* interface IPrismaticSuperstructureMemberSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPrismaticSuperstructureMemberSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DD5F5FF3-B22A-4fd6-820C-15F9E02A766D")
    IPrismaticSuperstructureMemberSegment : public ISuperstructureMemberSegment
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ IndexType *pCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPrismaticSuperstructureMemberSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPrismaticSuperstructureMemberSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPrismaticSuperstructureMemberSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [retval][out] */ ISuperstructureMember **ssmbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLine )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [retval][out] */ IGirderLine **girderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ Float64 orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [retval][out] */ Float64 *orientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHaunchDepth )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHaunchDepth )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHaunchDepth )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fillet )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ Float64 Fillet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fillet )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [retval][out] */ Float64 *Fillet);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ ISuperstructureMember *ssMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_GirderLine )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ IGirderLine *girderLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [retval][out] */ IndexType *pCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            IPrismaticSuperstructureMemberSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        END_INTERFACE
    } IPrismaticSuperstructureMemberSegmentVtbl;

    interface IPrismaticSuperstructureMemberSegment
    {
        CONST_VTBL struct IPrismaticSuperstructureMemberSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrismaticSuperstructureMemberSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPrismaticSuperstructureMemberSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPrismaticSuperstructureMemberSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPrismaticSuperstructureMemberSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define IPrismaticSuperstructureMemberSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define IPrismaticSuperstructureMemberSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define IPrismaticSuperstructureMemberSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define IPrismaticSuperstructureMemberSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define IPrismaticSuperstructureMemberSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define IPrismaticSuperstructureMemberSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define IPrismaticSuperstructureMemberSegment_get_SuperstructureMember(This,ssmbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ssmbr) ) 

#define IPrismaticSuperstructureMemberSegment_get_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> get_GirderLine(This,girderLine) ) 

#define IPrismaticSuperstructureMemberSegment_get_LayoutLength(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pVal) ) 

#define IPrismaticSuperstructureMemberSegment_get_Profile(This,bIncludeClosure,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,bIncludeClosure,ppShape) ) 

#define IPrismaticSuperstructureMemberSegment_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define IPrismaticSuperstructureMemberSegment_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define IPrismaticSuperstructureMemberSegment_GetHaunchDepth(This,pStartVal,pMidVal,pEndVal)	\
    ( (This)->lpVtbl -> GetHaunchDepth(This,pStartVal,pMidVal,pEndVal) ) 

#define IPrismaticSuperstructureMemberSegment_SetHaunchDepth(This,startVal,midVal,endVal)	\
    ( (This)->lpVtbl -> SetHaunchDepth(This,startVal,midVal,endVal) ) 

#define IPrismaticSuperstructureMemberSegment_ComputeHaunchDepth(This,distAlongSegment,pVal)	\
    ( (This)->lpVtbl -> ComputeHaunchDepth(This,distAlongSegment,pVal) ) 

#define IPrismaticSuperstructureMemberSegment_put_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> put_Fillet(This,Fillet) ) 

#define IPrismaticSuperstructureMemberSegment_get_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> get_Fillet(This,Fillet) ) 

#define IPrismaticSuperstructureMemberSegment_putref_SuperstructureMember(This,ssMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,ssMbr) ) 

#define IPrismaticSuperstructureMemberSegment_putref_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> putref_GirderLine(This,girderLine) ) 


#define IPrismaticSuperstructureMemberSegment_AddShape(This,pShape,pFGMaterial,pBGMaterial)	\
    ( (This)->lpVtbl -> AddShape(This,pShape,pFGMaterial,pBGMaterial) ) 

#define IPrismaticSuperstructureMemberSegment_get_ShapeCount(This,pCount)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,pCount) ) 

#define IPrismaticSuperstructureMemberSegment_get_ForegroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,idx,material) ) 

#define IPrismaticSuperstructureMemberSegment_get_BackgroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,idx,material) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPrismaticSuperstructureMemberSegment_INTERFACE_DEFINED__ */


#ifndef __IFlangedGirderEndBlockSegment_INTERFACE_DEFINED__
#define __IFlangedGirderEndBlockSegment_INTERFACE_DEFINED__

/* interface IFlangedGirderEndBlockSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFlangedGirderEndBlockSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("906BFF68-E90F-4b63-B41E-CC00BE22B7ED")
    IFlangedGirderEndBlockSegment : public ISuperstructureMemberSegment
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ IndexType *pCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlockTransitionLength( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlockTransitionLength( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlockWidth( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 width) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlockWidth( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pWidth) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFlangedGirderEndBlockSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFlangedGirderEndBlockSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFlangedGirderEndBlockSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IFlangedGirderEndBlockSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            IFlangedGirderEndBlockSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            IFlangedGirderEndBlockSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            IFlangedGirderEndBlockSegment * This,
            /* [retval][out] */ ISuperstructureMember **ssmbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLine )( 
            IFlangedGirderEndBlockSegment * This,
            /* [retval][out] */ IGirderLine **girderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            IFlangedGirderEndBlockSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ Float64 orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IFlangedGirderEndBlockSegment * This,
            /* [retval][out] */ Float64 *orientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHaunchDepth )( 
            IFlangedGirderEndBlockSegment * This,
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHaunchDepth )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHaunchDepth )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fillet )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ Float64 Fillet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fillet )( 
            IFlangedGirderEndBlockSegment * This,
            /* [retval][out] */ Float64 *Fillet);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ ISuperstructureMember *ssMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_GirderLine )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ IGirderLine *girderLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            IFlangedGirderEndBlockSegment * This,
            /* [retval][out] */ IndexType *pCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlockLength )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlockLength )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlockTransitionLength )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlockTransitionLength )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlockWidth )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlockWidth )( 
            IFlangedGirderEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pWidth);
        
        END_INTERFACE
    } IFlangedGirderEndBlockSegmentVtbl;

    interface IFlangedGirderEndBlockSegment
    {
        CONST_VTBL struct IFlangedGirderEndBlockSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFlangedGirderEndBlockSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFlangedGirderEndBlockSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFlangedGirderEndBlockSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFlangedGirderEndBlockSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define IFlangedGirderEndBlockSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define IFlangedGirderEndBlockSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define IFlangedGirderEndBlockSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define IFlangedGirderEndBlockSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define IFlangedGirderEndBlockSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define IFlangedGirderEndBlockSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define IFlangedGirderEndBlockSegment_get_SuperstructureMember(This,ssmbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ssmbr) ) 

#define IFlangedGirderEndBlockSegment_get_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> get_GirderLine(This,girderLine) ) 

#define IFlangedGirderEndBlockSegment_get_LayoutLength(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pVal) ) 

#define IFlangedGirderEndBlockSegment_get_Profile(This,bIncludeClosure,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,bIncludeClosure,ppShape) ) 

#define IFlangedGirderEndBlockSegment_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define IFlangedGirderEndBlockSegment_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define IFlangedGirderEndBlockSegment_GetHaunchDepth(This,pStartVal,pMidVal,pEndVal)	\
    ( (This)->lpVtbl -> GetHaunchDepth(This,pStartVal,pMidVal,pEndVal) ) 

#define IFlangedGirderEndBlockSegment_SetHaunchDepth(This,startVal,midVal,endVal)	\
    ( (This)->lpVtbl -> SetHaunchDepth(This,startVal,midVal,endVal) ) 

#define IFlangedGirderEndBlockSegment_ComputeHaunchDepth(This,distAlongSegment,pVal)	\
    ( (This)->lpVtbl -> ComputeHaunchDepth(This,distAlongSegment,pVal) ) 

#define IFlangedGirderEndBlockSegment_put_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> put_Fillet(This,Fillet) ) 

#define IFlangedGirderEndBlockSegment_get_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> get_Fillet(This,Fillet) ) 

#define IFlangedGirderEndBlockSegment_putref_SuperstructureMember(This,ssMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,ssMbr) ) 

#define IFlangedGirderEndBlockSegment_putref_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> putref_GirderLine(This,girderLine) ) 


#define IFlangedGirderEndBlockSegment_AddShape(This,pShape,pFGMaterial,pBGMaterial)	\
    ( (This)->lpVtbl -> AddShape(This,pShape,pFGMaterial,pBGMaterial) ) 

#define IFlangedGirderEndBlockSegment_get_ShapeCount(This,pCount)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,pCount) ) 

#define IFlangedGirderEndBlockSegment_get_ForegroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,idx,material) ) 

#define IFlangedGirderEndBlockSegment_get_BackgroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,idx,material) ) 

#define IFlangedGirderEndBlockSegment_put_EndBlockLength(This,endType,length)	\
    ( (This)->lpVtbl -> put_EndBlockLength(This,endType,length) ) 

#define IFlangedGirderEndBlockSegment_get_EndBlockLength(This,endType,pLength)	\
    ( (This)->lpVtbl -> get_EndBlockLength(This,endType,pLength) ) 

#define IFlangedGirderEndBlockSegment_put_EndBlockTransitionLength(This,endType,length)	\
    ( (This)->lpVtbl -> put_EndBlockTransitionLength(This,endType,length) ) 

#define IFlangedGirderEndBlockSegment_get_EndBlockTransitionLength(This,endType,pLength)	\
    ( (This)->lpVtbl -> get_EndBlockTransitionLength(This,endType,pLength) ) 

#define IFlangedGirderEndBlockSegment_put_EndBlockWidth(This,endType,width)	\
    ( (This)->lpVtbl -> put_EndBlockWidth(This,endType,width) ) 

#define IFlangedGirderEndBlockSegment_get_EndBlockWidth(This,endType,pWidth)	\
    ( (This)->lpVtbl -> get_EndBlockWidth(This,endType,pWidth) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFlangedGirderEndBlockSegment_INTERFACE_DEFINED__ */


#ifndef __IVoidedSlabEndBlockSegment_INTERFACE_DEFINED__
#define __IVoidedSlabEndBlockSegment_INTERFACE_DEFINED__

/* interface IVoidedSlabEndBlockSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVoidedSlabEndBlockSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2C189965-D747-4c98-B432-321B52B3ABDE")
    IVoidedSlabEndBlockSegment : public ISuperstructureMemberSegment
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ IndexType *pCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVoidedSlabEndBlockSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVoidedSlabEndBlockSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVoidedSlabEndBlockSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IVoidedSlabEndBlockSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            IVoidedSlabEndBlockSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            IVoidedSlabEndBlockSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            IVoidedSlabEndBlockSegment * This,
            /* [retval][out] */ ISuperstructureMember **ssmbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLine )( 
            IVoidedSlabEndBlockSegment * This,
            /* [retval][out] */ IGirderLine **girderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            IVoidedSlabEndBlockSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ Float64 orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IVoidedSlabEndBlockSegment * This,
            /* [retval][out] */ Float64 *orientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHaunchDepth )( 
            IVoidedSlabEndBlockSegment * This,
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHaunchDepth )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHaunchDepth )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fillet )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ Float64 Fillet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fillet )( 
            IVoidedSlabEndBlockSegment * This,
            /* [retval][out] */ Float64 *Fillet);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ ISuperstructureMember *ssMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_GirderLine )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ IGirderLine *girderLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            IVoidedSlabEndBlockSegment * This,
            /* [retval][out] */ IndexType *pCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlockLength )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlockLength )( 
            IVoidedSlabEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength);
        
        END_INTERFACE
    } IVoidedSlabEndBlockSegmentVtbl;

    interface IVoidedSlabEndBlockSegment
    {
        CONST_VTBL struct IVoidedSlabEndBlockSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoidedSlabEndBlockSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVoidedSlabEndBlockSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVoidedSlabEndBlockSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVoidedSlabEndBlockSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define IVoidedSlabEndBlockSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define IVoidedSlabEndBlockSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define IVoidedSlabEndBlockSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define IVoidedSlabEndBlockSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define IVoidedSlabEndBlockSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define IVoidedSlabEndBlockSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define IVoidedSlabEndBlockSegment_get_SuperstructureMember(This,ssmbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ssmbr) ) 

#define IVoidedSlabEndBlockSegment_get_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> get_GirderLine(This,girderLine) ) 

#define IVoidedSlabEndBlockSegment_get_LayoutLength(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pVal) ) 

#define IVoidedSlabEndBlockSegment_get_Profile(This,bIncludeClosure,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,bIncludeClosure,ppShape) ) 

#define IVoidedSlabEndBlockSegment_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define IVoidedSlabEndBlockSegment_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define IVoidedSlabEndBlockSegment_GetHaunchDepth(This,pStartVal,pMidVal,pEndVal)	\
    ( (This)->lpVtbl -> GetHaunchDepth(This,pStartVal,pMidVal,pEndVal) ) 

#define IVoidedSlabEndBlockSegment_SetHaunchDepth(This,startVal,midVal,endVal)	\
    ( (This)->lpVtbl -> SetHaunchDepth(This,startVal,midVal,endVal) ) 

#define IVoidedSlabEndBlockSegment_ComputeHaunchDepth(This,distAlongSegment,pVal)	\
    ( (This)->lpVtbl -> ComputeHaunchDepth(This,distAlongSegment,pVal) ) 

#define IVoidedSlabEndBlockSegment_put_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> put_Fillet(This,Fillet) ) 

#define IVoidedSlabEndBlockSegment_get_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> get_Fillet(This,Fillet) ) 

#define IVoidedSlabEndBlockSegment_putref_SuperstructureMember(This,ssMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,ssMbr) ) 

#define IVoidedSlabEndBlockSegment_putref_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> putref_GirderLine(This,girderLine) ) 


#define IVoidedSlabEndBlockSegment_AddShape(This,pShape,pFGMaterial,pBGMaterial)	\
    ( (This)->lpVtbl -> AddShape(This,pShape,pFGMaterial,pBGMaterial) ) 

#define IVoidedSlabEndBlockSegment_get_ShapeCount(This,pCount)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,pCount) ) 

#define IVoidedSlabEndBlockSegment_get_ForegroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,idx,material) ) 

#define IVoidedSlabEndBlockSegment_get_BackgroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,idx,material) ) 

#define IVoidedSlabEndBlockSegment_put_EndBlockLength(This,endType,length)	\
    ( (This)->lpVtbl -> put_EndBlockLength(This,endType,length) ) 

#define IVoidedSlabEndBlockSegment_get_EndBlockLength(This,endType,pLength)	\
    ( (This)->lpVtbl -> get_EndBlockLength(This,endType,pLength) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVoidedSlabEndBlockSegment_INTERFACE_DEFINED__ */


#ifndef __IDeckedSlabBeamEndBlockSegment_INTERFACE_DEFINED__
#define __IDeckedSlabBeamEndBlockSegment_INTERFACE_DEFINED__

/* interface IDeckedSlabBeamEndBlockSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDeckedSlabBeamEndBlockSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("319AC118-E4C8-4a9b-B653-67958B6CD071")
    IDeckedSlabBeamEndBlockSegment : public ISuperstructureMemberSegment
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ IndexType *pCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDeckedSlabBeamEndBlockSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDeckedSlabBeamEndBlockSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDeckedSlabBeamEndBlockSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [retval][out] */ ISuperstructureMember **ssmbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLine )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [retval][out] */ IGirderLine **girderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ Float64 orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [retval][out] */ Float64 *orientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHaunchDepth )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHaunchDepth )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHaunchDepth )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fillet )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ Float64 Fillet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fillet )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [retval][out] */ Float64 *Fillet);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ ISuperstructureMember *ssMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_GirderLine )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ IGirderLine *girderLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [retval][out] */ IndexType *pCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlockLength )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlockLength )( 
            IDeckedSlabBeamEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength);
        
        END_INTERFACE
    } IDeckedSlabBeamEndBlockSegmentVtbl;

    interface IDeckedSlabBeamEndBlockSegment
    {
        CONST_VTBL struct IDeckedSlabBeamEndBlockSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDeckedSlabBeamEndBlockSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDeckedSlabBeamEndBlockSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDeckedSlabBeamEndBlockSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDeckedSlabBeamEndBlockSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define IDeckedSlabBeamEndBlockSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define IDeckedSlabBeamEndBlockSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define IDeckedSlabBeamEndBlockSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define IDeckedSlabBeamEndBlockSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define IDeckedSlabBeamEndBlockSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define IDeckedSlabBeamEndBlockSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define IDeckedSlabBeamEndBlockSegment_get_SuperstructureMember(This,ssmbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ssmbr) ) 

#define IDeckedSlabBeamEndBlockSegment_get_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> get_GirderLine(This,girderLine) ) 

#define IDeckedSlabBeamEndBlockSegment_get_LayoutLength(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pVal) ) 

#define IDeckedSlabBeamEndBlockSegment_get_Profile(This,bIncludeClosure,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,bIncludeClosure,ppShape) ) 

#define IDeckedSlabBeamEndBlockSegment_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define IDeckedSlabBeamEndBlockSegment_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define IDeckedSlabBeamEndBlockSegment_GetHaunchDepth(This,pStartVal,pMidVal,pEndVal)	\
    ( (This)->lpVtbl -> GetHaunchDepth(This,pStartVal,pMidVal,pEndVal) ) 

#define IDeckedSlabBeamEndBlockSegment_SetHaunchDepth(This,startVal,midVal,endVal)	\
    ( (This)->lpVtbl -> SetHaunchDepth(This,startVal,midVal,endVal) ) 

#define IDeckedSlabBeamEndBlockSegment_ComputeHaunchDepth(This,distAlongSegment,pVal)	\
    ( (This)->lpVtbl -> ComputeHaunchDepth(This,distAlongSegment,pVal) ) 

#define IDeckedSlabBeamEndBlockSegment_put_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> put_Fillet(This,Fillet) ) 

#define IDeckedSlabBeamEndBlockSegment_get_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> get_Fillet(This,Fillet) ) 

#define IDeckedSlabBeamEndBlockSegment_putref_SuperstructureMember(This,ssMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,ssMbr) ) 

#define IDeckedSlabBeamEndBlockSegment_putref_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> putref_GirderLine(This,girderLine) ) 


#define IDeckedSlabBeamEndBlockSegment_AddShape(This,pShape,pFGMaterial,pBGMaterial)	\
    ( (This)->lpVtbl -> AddShape(This,pShape,pFGMaterial,pBGMaterial) ) 

#define IDeckedSlabBeamEndBlockSegment_get_ShapeCount(This,pCount)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,pCount) ) 

#define IDeckedSlabBeamEndBlockSegment_get_ForegroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,idx,material) ) 

#define IDeckedSlabBeamEndBlockSegment_get_BackgroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,idx,material) ) 

#define IDeckedSlabBeamEndBlockSegment_put_EndBlockLength(This,endType,length)	\
    ( (This)->lpVtbl -> put_EndBlockLength(This,endType,length) ) 

#define IDeckedSlabBeamEndBlockSegment_get_EndBlockLength(This,endType,pLength)	\
    ( (This)->lpVtbl -> get_EndBlockLength(This,endType,pLength) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDeckedSlabBeamEndBlockSegment_INTERFACE_DEFINED__ */


#ifndef __IBoxBeamEndBlockSegment_INTERFACE_DEFINED__
#define __IBoxBeamEndBlockSegment_INTERFACE_DEFINED__

/* interface IBoxBeamEndBlockSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBoxBeamEndBlockSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D492FA18-90EB-40a0-A90C-1395A19C7F92")
    IBoxBeamEndBlockSegment : public ISuperstructureMemberSegment
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ IndexType *pCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBoxBeamEndBlockSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBoxBeamEndBlockSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBoxBeamEndBlockSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IBoxBeamEndBlockSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            IBoxBeamEndBlockSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            IBoxBeamEndBlockSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            IBoxBeamEndBlockSegment * This,
            /* [retval][out] */ ISuperstructureMember **ssmbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLine )( 
            IBoxBeamEndBlockSegment * This,
            /* [retval][out] */ IGirderLine **girderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            IBoxBeamEndBlockSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ Float64 orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IBoxBeamEndBlockSegment * This,
            /* [retval][out] */ Float64 *orientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHaunchDepth )( 
            IBoxBeamEndBlockSegment * This,
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHaunchDepth )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHaunchDepth )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fillet )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ Float64 Fillet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fillet )( 
            IBoxBeamEndBlockSegment * This,
            /* [retval][out] */ Float64 *Fillet);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ ISuperstructureMember *ssMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_GirderLine )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ IGirderLine *girderLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            IBoxBeamEndBlockSegment * This,
            /* [retval][out] */ IndexType *pCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlockLength )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlockLength )( 
            IBoxBeamEndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength);
        
        END_INTERFACE
    } IBoxBeamEndBlockSegmentVtbl;

    interface IBoxBeamEndBlockSegment
    {
        CONST_VTBL struct IBoxBeamEndBlockSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBoxBeamEndBlockSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBoxBeamEndBlockSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBoxBeamEndBlockSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBoxBeamEndBlockSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define IBoxBeamEndBlockSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define IBoxBeamEndBlockSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define IBoxBeamEndBlockSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define IBoxBeamEndBlockSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define IBoxBeamEndBlockSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define IBoxBeamEndBlockSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define IBoxBeamEndBlockSegment_get_SuperstructureMember(This,ssmbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ssmbr) ) 

#define IBoxBeamEndBlockSegment_get_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> get_GirderLine(This,girderLine) ) 

#define IBoxBeamEndBlockSegment_get_LayoutLength(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pVal) ) 

#define IBoxBeamEndBlockSegment_get_Profile(This,bIncludeClosure,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,bIncludeClosure,ppShape) ) 

#define IBoxBeamEndBlockSegment_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define IBoxBeamEndBlockSegment_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define IBoxBeamEndBlockSegment_GetHaunchDepth(This,pStartVal,pMidVal,pEndVal)	\
    ( (This)->lpVtbl -> GetHaunchDepth(This,pStartVal,pMidVal,pEndVal) ) 

#define IBoxBeamEndBlockSegment_SetHaunchDepth(This,startVal,midVal,endVal)	\
    ( (This)->lpVtbl -> SetHaunchDepth(This,startVal,midVal,endVal) ) 

#define IBoxBeamEndBlockSegment_ComputeHaunchDepth(This,distAlongSegment,pVal)	\
    ( (This)->lpVtbl -> ComputeHaunchDepth(This,distAlongSegment,pVal) ) 

#define IBoxBeamEndBlockSegment_put_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> put_Fillet(This,Fillet) ) 

#define IBoxBeamEndBlockSegment_get_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> get_Fillet(This,Fillet) ) 

#define IBoxBeamEndBlockSegment_putref_SuperstructureMember(This,ssMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,ssMbr) ) 

#define IBoxBeamEndBlockSegment_putref_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> putref_GirderLine(This,girderLine) ) 


#define IBoxBeamEndBlockSegment_AddShape(This,pShape,pFGMaterial,pBGMaterial)	\
    ( (This)->lpVtbl -> AddShape(This,pShape,pFGMaterial,pBGMaterial) ) 

#define IBoxBeamEndBlockSegment_get_ShapeCount(This,pCount)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,pCount) ) 

#define IBoxBeamEndBlockSegment_get_ForegroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,idx,material) ) 

#define IBoxBeamEndBlockSegment_get_BackgroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,idx,material) ) 

#define IBoxBeamEndBlockSegment_put_EndBlockLength(This,endType,length)	\
    ( (This)->lpVtbl -> put_EndBlockLength(This,endType,length) ) 

#define IBoxBeamEndBlockSegment_get_EndBlockLength(This,endType,pLength)	\
    ( (This)->lpVtbl -> get_EndBlockLength(This,endType,pLength) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBoxBeamEndBlockSegment_INTERFACE_DEFINED__ */


#ifndef __IUGirderSection2EndBlockSegment_INTERFACE_DEFINED__
#define __IUGirderSection2EndBlockSegment_INTERFACE_DEFINED__

/* interface IUGirderSection2EndBlockSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUGirderSection2EndBlockSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FC05CC1E-5BF7-4c6c-858A-325C115209A8")
    IUGirderSection2EndBlockSegment : public ISuperstructureMemberSegment
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ IndexType *pCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUGirderSection2EndBlockSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUGirderSection2EndBlockSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUGirderSection2EndBlockSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IUGirderSection2EndBlockSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            IUGirderSection2EndBlockSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            IUGirderSection2EndBlockSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            IUGirderSection2EndBlockSegment * This,
            /* [retval][out] */ ISuperstructureMember **ssmbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLine )( 
            IUGirderSection2EndBlockSegment * This,
            /* [retval][out] */ IGirderLine **girderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            IUGirderSection2EndBlockSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ Float64 orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IUGirderSection2EndBlockSegment * This,
            /* [retval][out] */ Float64 *orientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHaunchDepth )( 
            IUGirderSection2EndBlockSegment * This,
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHaunchDepth )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHaunchDepth )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fillet )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ Float64 Fillet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fillet )( 
            IUGirderSection2EndBlockSegment * This,
            /* [retval][out] */ Float64 *Fillet);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ ISuperstructureMember *ssMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_GirderLine )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ IGirderLine *girderLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            IUGirderSection2EndBlockSegment * This,
            /* [retval][out] */ IndexType *pCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlockLength )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlockLength )( 
            IUGirderSection2EndBlockSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength);
        
        END_INTERFACE
    } IUGirderSection2EndBlockSegmentVtbl;

    interface IUGirderSection2EndBlockSegment
    {
        CONST_VTBL struct IUGirderSection2EndBlockSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUGirderSection2EndBlockSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUGirderSection2EndBlockSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUGirderSection2EndBlockSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUGirderSection2EndBlockSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define IUGirderSection2EndBlockSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define IUGirderSection2EndBlockSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define IUGirderSection2EndBlockSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define IUGirderSection2EndBlockSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define IUGirderSection2EndBlockSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define IUGirderSection2EndBlockSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define IUGirderSection2EndBlockSegment_get_SuperstructureMember(This,ssmbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ssmbr) ) 

#define IUGirderSection2EndBlockSegment_get_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> get_GirderLine(This,girderLine) ) 

#define IUGirderSection2EndBlockSegment_get_LayoutLength(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pVal) ) 

#define IUGirderSection2EndBlockSegment_get_Profile(This,bIncludeClosure,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,bIncludeClosure,ppShape) ) 

#define IUGirderSection2EndBlockSegment_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define IUGirderSection2EndBlockSegment_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define IUGirderSection2EndBlockSegment_GetHaunchDepth(This,pStartVal,pMidVal,pEndVal)	\
    ( (This)->lpVtbl -> GetHaunchDepth(This,pStartVal,pMidVal,pEndVal) ) 

#define IUGirderSection2EndBlockSegment_SetHaunchDepth(This,startVal,midVal,endVal)	\
    ( (This)->lpVtbl -> SetHaunchDepth(This,startVal,midVal,endVal) ) 

#define IUGirderSection2EndBlockSegment_ComputeHaunchDepth(This,distAlongSegment,pVal)	\
    ( (This)->lpVtbl -> ComputeHaunchDepth(This,distAlongSegment,pVal) ) 

#define IUGirderSection2EndBlockSegment_put_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> put_Fillet(This,Fillet) ) 

#define IUGirderSection2EndBlockSegment_get_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> get_Fillet(This,Fillet) ) 

#define IUGirderSection2EndBlockSegment_putref_SuperstructureMember(This,ssMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,ssMbr) ) 

#define IUGirderSection2EndBlockSegment_putref_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> putref_GirderLine(This,girderLine) ) 


#define IUGirderSection2EndBlockSegment_AddShape(This,pShape,pFGMaterial,pBGMaterial)	\
    ( (This)->lpVtbl -> AddShape(This,pShape,pFGMaterial,pBGMaterial) ) 

#define IUGirderSection2EndBlockSegment_get_ShapeCount(This,pCount)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,pCount) ) 

#define IUGirderSection2EndBlockSegment_get_ForegroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,idx,material) ) 

#define IUGirderSection2EndBlockSegment_get_BackgroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,idx,material) ) 

#define IUGirderSection2EndBlockSegment_put_EndBlockLength(This,endType,length)	\
    ( (This)->lpVtbl -> put_EndBlockLength(This,endType,length) ) 

#define IUGirderSection2EndBlockSegment_get_EndBlockLength(This,endType,pLength)	\
    ( (This)->lpVtbl -> get_EndBlockLength(This,endType,pLength) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUGirderSection2EndBlockSegment_INTERFACE_DEFINED__ */


#ifndef __ITaperedGirderSegment_INTERFACE_DEFINED__
#define __ITaperedGirderSegment_INTERFACE_DEFINED__

/* interface ITaperedGirderSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITaperedGirderSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1749EDD7-2483-4fc8-8F9F-2F22F48DB0BF")
    ITaperedGirderSegment : public ISuperstructureMemberSegment
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pStartShape,
            /* [in] */ IShape *pEndShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ IndexType *pCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITaperedGirderSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITaperedGirderSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITaperedGirderSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITaperedGirderSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ITaperedGirderSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            ITaperedGirderSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            ITaperedGirderSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            ITaperedGirderSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            ITaperedGirderSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            ITaperedGirderSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            ITaperedGirderSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            ITaperedGirderSegment * This,
            /* [retval][out] */ ISuperstructureMember **ssmbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLine )( 
            ITaperedGirderSegment * This,
            /* [retval][out] */ IGirderLine **girderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            ITaperedGirderSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            ITaperedGirderSegment * This,
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            ITaperedGirderSegment * This,
            /* [in] */ Float64 orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            ITaperedGirderSegment * This,
            /* [retval][out] */ Float64 *orientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHaunchDepth )( 
            ITaperedGirderSegment * This,
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHaunchDepth )( 
            ITaperedGirderSegment * This,
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHaunchDepth )( 
            ITaperedGirderSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fillet )( 
            ITaperedGirderSegment * This,
            /* [in] */ Float64 Fillet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fillet )( 
            ITaperedGirderSegment * This,
            /* [retval][out] */ Float64 *Fillet);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            ITaperedGirderSegment * This,
            /* [in] */ ISuperstructureMember *ssMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_GirderLine )( 
            ITaperedGirderSegment * This,
            /* [in] */ IGirderLine *girderLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            ITaperedGirderSegment * This,
            /* [in] */ IShape *pStartShape,
            /* [in] */ IShape *pEndShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            ITaperedGirderSegment * This,
            /* [retval][out] */ IndexType *pCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            ITaperedGirderSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            ITaperedGirderSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        END_INTERFACE
    } ITaperedGirderSegmentVtbl;

    interface ITaperedGirderSegment
    {
        CONST_VTBL struct ITaperedGirderSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITaperedGirderSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITaperedGirderSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITaperedGirderSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITaperedGirderSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ITaperedGirderSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define ITaperedGirderSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define ITaperedGirderSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define ITaperedGirderSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define ITaperedGirderSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define ITaperedGirderSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define ITaperedGirderSegment_get_SuperstructureMember(This,ssmbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ssmbr) ) 

#define ITaperedGirderSegment_get_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> get_GirderLine(This,girderLine) ) 

#define ITaperedGirderSegment_get_LayoutLength(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pVal) ) 

#define ITaperedGirderSegment_get_Profile(This,bIncludeClosure,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,bIncludeClosure,ppShape) ) 

#define ITaperedGirderSegment_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define ITaperedGirderSegment_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define ITaperedGirderSegment_GetHaunchDepth(This,pStartVal,pMidVal,pEndVal)	\
    ( (This)->lpVtbl -> GetHaunchDepth(This,pStartVal,pMidVal,pEndVal) ) 

#define ITaperedGirderSegment_SetHaunchDepth(This,startVal,midVal,endVal)	\
    ( (This)->lpVtbl -> SetHaunchDepth(This,startVal,midVal,endVal) ) 

#define ITaperedGirderSegment_ComputeHaunchDepth(This,distAlongSegment,pVal)	\
    ( (This)->lpVtbl -> ComputeHaunchDepth(This,distAlongSegment,pVal) ) 

#define ITaperedGirderSegment_put_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> put_Fillet(This,Fillet) ) 

#define ITaperedGirderSegment_get_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> get_Fillet(This,Fillet) ) 

#define ITaperedGirderSegment_putref_SuperstructureMember(This,ssMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,ssMbr) ) 

#define ITaperedGirderSegment_putref_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> putref_GirderLine(This,girderLine) ) 


#define ITaperedGirderSegment_AddShape(This,pStartShape,pEndShape,pFGMaterial,pBGMaterial)	\
    ( (This)->lpVtbl -> AddShape(This,pStartShape,pEndShape,pFGMaterial,pBGMaterial) ) 

#define ITaperedGirderSegment_get_ShapeCount(This,pCount)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,pCount) ) 

#define ITaperedGirderSegment_get_ForegroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,idx,material) ) 

#define ITaperedGirderSegment_get_BackgroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,idx,material) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITaperedGirderSegment_INTERFACE_DEFINED__ */


#ifndef __ISplicedGirderSegment_INTERFACE_DEFINED__
#define __ISplicedGirderSegment_INTERFACE_DEFINED__

/* interface ISplicedGirderSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISplicedGirderSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C27D9CB1-3FC1-4565-8755-14013DEB9CEB")
    ISplicedGirderSegment : public ISuperstructureMemberSegment
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ IndexType *pCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlockLength( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlockTransitionLength( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlockTransitionLength( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlockWidth( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 width) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlockWidth( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pWidth) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VariationType( 
            /* [in] */ SegmentVariationType variationType) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VariationType( 
            /* [retval][out] */ SegmentVariationType *variationType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetVariationParameters( 
            /* [in] */ SegmentZoneType zone,
            /* [in] */ Float64 length,
            /* [in] */ Float64 height,
            /* [in] */ Float64 bottomFlangeDepth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVariationParameters( 
            /* [in] */ SegmentZoneType zone,
            /* [out] */ Float64 *length,
            /* [out] */ Float64 *height,
            /* [out] */ Float64 *bottomFlangeDepth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentHeight( 
            /* [in] */ Float64 distFromStartOfSegment,
            /* [retval][out] */ Float64 *pHeight) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeProfile( 
            /* [retval][out] */ IPoint2dCollection **ppPoints) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClosureJointLength( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ClosureJointForegroundMaterial( 
            /* [in] */ EndType endType,
            /* [in] */ IMaterial *pFGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClosureJointForegroundMaterial( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IMaterial **ppFGMaterial) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ClosureJointBackgroundMaterial( 
            /* [in] */ EndType endType,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClosureJointBackgroundMaterial( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IMaterial **ppBGMaterial) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISplicedGirderSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISplicedGirderSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISplicedGirderSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISplicedGirderSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            ISplicedGirderSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            ISplicedGirderSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            ISplicedGirderSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            ISplicedGirderSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ ISuperstructureMember **ssmbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLine )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ IGirderLine **girderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            ISplicedGirderSegment * This,
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            ISplicedGirderSegment * This,
            /* [in] */ Float64 orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ Float64 *orientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHaunchDepth )( 
            ISplicedGirderSegment * This,
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHaunchDepth )( 
            ISplicedGirderSegment * This,
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHaunchDepth )( 
            ISplicedGirderSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fillet )( 
            ISplicedGirderSegment * This,
            /* [in] */ Float64 Fillet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fillet )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ Float64 *Fillet);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            ISplicedGirderSegment * This,
            /* [in] */ ISuperstructureMember *ssMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_GirderLine )( 
            ISplicedGirderSegment * This,
            /* [in] */ IGirderLine *girderLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            ISplicedGirderSegment * This,
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ IndexType *pCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            ISplicedGirderSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            ISplicedGirderSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlockLength )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlockLength )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlockTransitionLength )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlockTransitionLength )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlockWidth )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlockWidth )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pWidth);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VariationType )( 
            ISplicedGirderSegment * This,
            /* [in] */ SegmentVariationType variationType);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VariationType )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ SegmentVariationType *variationType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetVariationParameters )( 
            ISplicedGirderSegment * This,
            /* [in] */ SegmentZoneType zone,
            /* [in] */ Float64 length,
            /* [in] */ Float64 height,
            /* [in] */ Float64 bottomFlangeDepth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetVariationParameters )( 
            ISplicedGirderSegment * This,
            /* [in] */ SegmentZoneType zone,
            /* [out] */ Float64 *length,
            /* [out] */ Float64 *height,
            /* [out] */ Float64 *bottomFlangeDepth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentHeight )( 
            ISplicedGirderSegment * This,
            /* [in] */ Float64 distFromStartOfSegment,
            /* [retval][out] */ Float64 *pHeight);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeProfile )( 
            ISplicedGirderSegment * This,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClosureJointLength )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClosureJointForegroundMaterial )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ IMaterial *pFGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClosureJointForegroundMaterial )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IMaterial **ppFGMaterial);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClosureJointBackgroundMaterial )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClosureJointBackgroundMaterial )( 
            ISplicedGirderSegment * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IMaterial **ppBGMaterial);
        
        END_INTERFACE
    } ISplicedGirderSegmentVtbl;

    interface ISplicedGirderSegment
    {
        CONST_VTBL struct ISplicedGirderSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISplicedGirderSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISplicedGirderSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISplicedGirderSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISplicedGirderSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ISplicedGirderSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define ISplicedGirderSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define ISplicedGirderSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define ISplicedGirderSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define ISplicedGirderSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define ISplicedGirderSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define ISplicedGirderSegment_get_SuperstructureMember(This,ssmbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ssmbr) ) 

#define ISplicedGirderSegment_get_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> get_GirderLine(This,girderLine) ) 

#define ISplicedGirderSegment_get_LayoutLength(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pVal) ) 

#define ISplicedGirderSegment_get_Profile(This,bIncludeClosure,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,bIncludeClosure,ppShape) ) 

#define ISplicedGirderSegment_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define ISplicedGirderSegment_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define ISplicedGirderSegment_GetHaunchDepth(This,pStartVal,pMidVal,pEndVal)	\
    ( (This)->lpVtbl -> GetHaunchDepth(This,pStartVal,pMidVal,pEndVal) ) 

#define ISplicedGirderSegment_SetHaunchDepth(This,startVal,midVal,endVal)	\
    ( (This)->lpVtbl -> SetHaunchDepth(This,startVal,midVal,endVal) ) 

#define ISplicedGirderSegment_ComputeHaunchDepth(This,distAlongSegment,pVal)	\
    ( (This)->lpVtbl -> ComputeHaunchDepth(This,distAlongSegment,pVal) ) 

#define ISplicedGirderSegment_put_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> put_Fillet(This,Fillet) ) 

#define ISplicedGirderSegment_get_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> get_Fillet(This,Fillet) ) 

#define ISplicedGirderSegment_putref_SuperstructureMember(This,ssMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,ssMbr) ) 

#define ISplicedGirderSegment_putref_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> putref_GirderLine(This,girderLine) ) 


#define ISplicedGirderSegment_AddShape(This,pShape,pFGMaterial,pBGMaterial)	\
    ( (This)->lpVtbl -> AddShape(This,pShape,pFGMaterial,pBGMaterial) ) 

#define ISplicedGirderSegment_get_ShapeCount(This,pCount)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,pCount) ) 

#define ISplicedGirderSegment_get_ForegroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,idx,material) ) 

#define ISplicedGirderSegment_get_BackgroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,idx,material) ) 

#define ISplicedGirderSegment_put_EndBlockLength(This,endType,length)	\
    ( (This)->lpVtbl -> put_EndBlockLength(This,endType,length) ) 

#define ISplicedGirderSegment_get_EndBlockLength(This,endType,pLength)	\
    ( (This)->lpVtbl -> get_EndBlockLength(This,endType,pLength) ) 

#define ISplicedGirderSegment_put_EndBlockTransitionLength(This,endType,length)	\
    ( (This)->lpVtbl -> put_EndBlockTransitionLength(This,endType,length) ) 

#define ISplicedGirderSegment_get_EndBlockTransitionLength(This,endType,pLength)	\
    ( (This)->lpVtbl -> get_EndBlockTransitionLength(This,endType,pLength) ) 

#define ISplicedGirderSegment_put_EndBlockWidth(This,endType,width)	\
    ( (This)->lpVtbl -> put_EndBlockWidth(This,endType,width) ) 

#define ISplicedGirderSegment_get_EndBlockWidth(This,endType,pWidth)	\
    ( (This)->lpVtbl -> get_EndBlockWidth(This,endType,pWidth) ) 

#define ISplicedGirderSegment_put_VariationType(This,variationType)	\
    ( (This)->lpVtbl -> put_VariationType(This,variationType) ) 

#define ISplicedGirderSegment_get_VariationType(This,variationType)	\
    ( (This)->lpVtbl -> get_VariationType(This,variationType) ) 

#define ISplicedGirderSegment_SetVariationParameters(This,zone,length,height,bottomFlangeDepth)	\
    ( (This)->lpVtbl -> SetVariationParameters(This,zone,length,height,bottomFlangeDepth) ) 

#define ISplicedGirderSegment_GetVariationParameters(This,zone,length,height,bottomFlangeDepth)	\
    ( (This)->lpVtbl -> GetVariationParameters(This,zone,length,height,bottomFlangeDepth) ) 

#define ISplicedGirderSegment_GetSegmentHeight(This,distFromStartOfSegment,pHeight)	\
    ( (This)->lpVtbl -> GetSegmentHeight(This,distFromStartOfSegment,pHeight) ) 

#define ISplicedGirderSegment_get_BottomFlangeProfile(This,ppPoints)	\
    ( (This)->lpVtbl -> get_BottomFlangeProfile(This,ppPoints) ) 

#define ISplicedGirderSegment_get_ClosureJointLength(This,endType,pLength)	\
    ( (This)->lpVtbl -> get_ClosureJointLength(This,endType,pLength) ) 

#define ISplicedGirderSegment_put_ClosureJointForegroundMaterial(This,endType,pFGMaterial)	\
    ( (This)->lpVtbl -> put_ClosureJointForegroundMaterial(This,endType,pFGMaterial) ) 

#define ISplicedGirderSegment_get_ClosureJointForegroundMaterial(This,endType,ppFGMaterial)	\
    ( (This)->lpVtbl -> get_ClosureJointForegroundMaterial(This,endType,ppFGMaterial) ) 

#define ISplicedGirderSegment_put_ClosureJointBackgroundMaterial(This,endType,pBGMaterial)	\
    ( (This)->lpVtbl -> put_ClosureJointBackgroundMaterial(This,endType,pBGMaterial) ) 

#define ISplicedGirderSegment_get_ClosureJointBackgroundMaterial(This,endType,ppBGMaterial)	\
    ( (This)->lpVtbl -> get_ClosureJointBackgroundMaterial(This,endType,ppBGMaterial) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISplicedGirderSegment_INTERFACE_DEFINED__ */


#ifndef __IFlangedSplicedGirderSegment_INTERFACE_DEFINED__
#define __IFlangedSplicedGirderSegment_INTERFACE_DEFINED__

/* interface IFlangedSplicedGirderSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFlangedSplicedGirderSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8F3B43FE-5138-4a73-B567-D9C3B4EC0166")
    IFlangedSplicedGirderSegment : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_FlangedGirderSection( 
            /* [in] */ IFlangedGirderSection *pPrecastBeam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FlangedGirderSection( 
            /* [retval][out] */ IFlangedGirderSection **ppPrecastBeam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFlangedSplicedGirderSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFlangedSplicedGirderSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFlangedSplicedGirderSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFlangedSplicedGirderSegment * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_FlangedGirderSection )( 
            IFlangedSplicedGirderSegment * This,
            /* [in] */ IFlangedGirderSection *pPrecastBeam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FlangedGirderSection )( 
            IFlangedSplicedGirderSegment * This,
            /* [retval][out] */ IFlangedGirderSection **ppPrecastBeam);
        
        END_INTERFACE
    } IFlangedSplicedGirderSegmentVtbl;

    interface IFlangedSplicedGirderSegment
    {
        CONST_VTBL struct IFlangedSplicedGirderSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFlangedSplicedGirderSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFlangedSplicedGirderSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFlangedSplicedGirderSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFlangedSplicedGirderSegment_putref_FlangedGirderSection(This,pPrecastBeam)	\
    ( (This)->lpVtbl -> putref_FlangedGirderSection(This,pPrecastBeam) ) 

#define IFlangedSplicedGirderSegment_get_FlangedGirderSection(This,ppPrecastBeam)	\
    ( (This)->lpVtbl -> get_FlangedGirderSection(This,ppPrecastBeam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFlangedSplicedGirderSegment_INTERFACE_DEFINED__ */


#ifndef __IUSplicedGirderSegment_INTERFACE_DEFINED__
#define __IUSplicedGirderSegment_INTERFACE_DEFINED__

/* interface IUSplicedGirderSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUSplicedGirderSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4ED17E29-71D1-493d-BCA0-11AF8DF6B814")
    IUSplicedGirderSegment : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_UGirderSection( 
            /* [in] */ IUGirderSection *pPrecastBeam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UGirderSection( 
            /* [retval][out] */ IUGirderSection **ppPrecastBeam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUSplicedGirderSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUSplicedGirderSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUSplicedGirderSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUSplicedGirderSegment * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_UGirderSection )( 
            IUSplicedGirderSegment * This,
            /* [in] */ IUGirderSection *pPrecastBeam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UGirderSection )( 
            IUSplicedGirderSegment * This,
            /* [retval][out] */ IUGirderSection **ppPrecastBeam);
        
        END_INTERFACE
    } IUSplicedGirderSegmentVtbl;

    interface IUSplicedGirderSegment
    {
        CONST_VTBL struct IUSplicedGirderSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUSplicedGirderSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUSplicedGirderSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUSplicedGirderSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUSplicedGirderSegment_putref_UGirderSection(This,pPrecastBeam)	\
    ( (This)->lpVtbl -> putref_UGirderSection(This,pPrecastBeam) ) 

#define IUSplicedGirderSegment_get_UGirderSection(This,ppPrecastBeam)	\
    ( (This)->lpVtbl -> get_UGirderSection(This,ppPrecastBeam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUSplicedGirderSegment_INTERFACE_DEFINED__ */


#ifndef __IBulbTeeSection_INTERFACE_DEFINED__
#define __IBulbTeeSection_INTERFACE_DEFINED__

/* interface IBulbTeeSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBulbTeeSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4D6301FB-5724-43eb-BD34-A5F9351F7ECB")
    IBulbTeeSection : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ IBulbTee *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IBulbTee **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBulbTeeSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBulbTeeSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBulbTeeSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBulbTeeSection * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            IBulbTeeSection * This,
            /* [in] */ IBulbTee *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IBulbTeeSection * This,
            /* [retval][out] */ IBulbTee **beam);
        
        END_INTERFACE
    } IBulbTeeSectionVtbl;

    interface IBulbTeeSection
    {
        CONST_VTBL struct IBulbTeeSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBulbTeeSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBulbTeeSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBulbTeeSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBulbTeeSection_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define IBulbTeeSection_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBulbTeeSection_INTERFACE_DEFINED__ */


#ifndef __IThickenedFlangeBulbTeeSegment_INTERFACE_DEFINED__
#define __IThickenedFlangeBulbTeeSegment_INTERFACE_DEFINED__

/* interface IThickenedFlangeBulbTeeSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IThickenedFlangeBulbTeeSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2ECFBA7-6D57-4e72-B4C2-79450D5B4D9E")
    IThickenedFlangeBulbTeeSegment : public ISuperstructureMemberSegment
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_FlangeThickening( 
            /* [in] */ Float64 flangeThickening) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ IndexType *pCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IThickenedFlangeBulbTeeSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IThickenedFlangeBulbTeeSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IThickenedFlangeBulbTeeSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryShape )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ ISection **ppSection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSegment )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextSegment )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [retval][out] */ ISegment **segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevSegment )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextSegment )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ ISegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [retval][out] */ ISuperstructureMember **ssmbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLine )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [retval][out] */ IGirderLine **girderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ VARIANT_BOOL bIncludeClosure,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ Float64 orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [retval][out] */ Float64 *orientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHaunchDepth )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [out] */ Float64 *pStartVal,
            /* [out] */ Float64 *pMidVal,
            /* [out] */ Float64 *pEndVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHaunchDepth )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ Float64 startVal,
            /* [in] */ Float64 midVal,
            /* [in] */ Float64 endVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHaunchDepth )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ Float64 distAlongSegment,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fillet )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ Float64 Fillet);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fillet )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [retval][out] */ Float64 *Fillet);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ ISuperstructureMember *ssMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_GirderLine )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ IGirderLine *girderLine);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FlangeThickening )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ Float64 flangeThickening);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ IShape *pShape,
            /* [in] */ IMaterial *pFGMaterial,
            /* [in] */ IMaterial *pBGMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [retval][out] */ IndexType *pCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            IThickenedFlangeBulbTeeSegment * This,
            /* [in] */ IndexType idx,
            /* [retval][out] */ IMaterial **material);
        
        END_INTERFACE
    } IThickenedFlangeBulbTeeSegmentVtbl;

    interface IThickenedFlangeBulbTeeSegment
    {
        CONST_VTBL struct IThickenedFlangeBulbTeeSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IThickenedFlangeBulbTeeSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IThickenedFlangeBulbTeeSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IThickenedFlangeBulbTeeSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IThickenedFlangeBulbTeeSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define IThickenedFlangeBulbTeeSegment_get_PrimaryShape(This,distAlongSegment,ppShape)	\
    ( (This)->lpVtbl -> get_PrimaryShape(This,distAlongSegment,ppShape) ) 

#define IThickenedFlangeBulbTeeSegment_get_Section(This,stageIdx,distAlongSegment,ppSection)	\
    ( (This)->lpVtbl -> get_Section(This,stageIdx,distAlongSegment,ppSection) ) 

#define IThickenedFlangeBulbTeeSegment_get_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> get_PrevSegment(This,segment) ) 

#define IThickenedFlangeBulbTeeSegment_get_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> get_NextSegment(This,segment) ) 

#define IThickenedFlangeBulbTeeSegment_putref_PrevSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_PrevSegment(This,segment) ) 

#define IThickenedFlangeBulbTeeSegment_putref_NextSegment(This,segment)	\
    ( (This)->lpVtbl -> putref_NextSegment(This,segment) ) 


#define IThickenedFlangeBulbTeeSegment_get_SuperstructureMember(This,ssmbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ssmbr) ) 

#define IThickenedFlangeBulbTeeSegment_get_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> get_GirderLine(This,girderLine) ) 

#define IThickenedFlangeBulbTeeSegment_get_LayoutLength(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pVal) ) 

#define IThickenedFlangeBulbTeeSegment_get_Profile(This,bIncludeClosure,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,bIncludeClosure,ppShape) ) 

#define IThickenedFlangeBulbTeeSegment_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define IThickenedFlangeBulbTeeSegment_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define IThickenedFlangeBulbTeeSegment_GetHaunchDepth(This,pStartVal,pMidVal,pEndVal)	\
    ( (This)->lpVtbl -> GetHaunchDepth(This,pStartVal,pMidVal,pEndVal) ) 

#define IThickenedFlangeBulbTeeSegment_SetHaunchDepth(This,startVal,midVal,endVal)	\
    ( (This)->lpVtbl -> SetHaunchDepth(This,startVal,midVal,endVal) ) 

#define IThickenedFlangeBulbTeeSegment_ComputeHaunchDepth(This,distAlongSegment,pVal)	\
    ( (This)->lpVtbl -> ComputeHaunchDepth(This,distAlongSegment,pVal) ) 

#define IThickenedFlangeBulbTeeSegment_put_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> put_Fillet(This,Fillet) ) 

#define IThickenedFlangeBulbTeeSegment_get_Fillet(This,Fillet)	\
    ( (This)->lpVtbl -> get_Fillet(This,Fillet) ) 

#define IThickenedFlangeBulbTeeSegment_putref_SuperstructureMember(This,ssMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,ssMbr) ) 

#define IThickenedFlangeBulbTeeSegment_putref_GirderLine(This,girderLine)	\
    ( (This)->lpVtbl -> putref_GirderLine(This,girderLine) ) 


#define IThickenedFlangeBulbTeeSegment_put_FlangeThickening(This,flangeThickening)	\
    ( (This)->lpVtbl -> put_FlangeThickening(This,flangeThickening) ) 

#define IThickenedFlangeBulbTeeSegment_AddShape(This,pShape,pFGMaterial,pBGMaterial)	\
    ( (This)->lpVtbl -> AddShape(This,pShape,pFGMaterial,pBGMaterial) ) 

#define IThickenedFlangeBulbTeeSegment_get_ShapeCount(This,pCount)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,pCount) ) 

#define IThickenedFlangeBulbTeeSegment_get_ForegroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,idx,material) ) 

#define IThickenedFlangeBulbTeeSegment_get_BackgroundMaterial(This,idx,material)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,idx,material) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IThickenedFlangeBulbTeeSegment_INTERFACE_DEFINED__ */


#ifndef __IEnumSegmentItem_INTERFACE_DEFINED__
#define __IEnumSegmentItem_INTERFACE_DEFINED__

/* interface IEnumSegmentItem */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSegmentItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B422F9A5-8078-435a-AD4B-A3DC9C4D6801")
    IEnumSegmentItem : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSegmentItem **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISegmentItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSegmentItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSegmentItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSegmentItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSegmentItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSegmentItem * This,
            /* [out] */ IEnumSegmentItem **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSegmentItem * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISegmentItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSegmentItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSegmentItem * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSegmentItemVtbl;

    interface IEnumSegmentItem
    {
        CONST_VTBL struct IEnumSegmentItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSegmentItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSegmentItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSegmentItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSegmentItem_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSegmentItem_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSegmentItem_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSegmentItem_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSegmentItem_INTERFACE_DEFINED__ */


#ifndef __IColumn_INTERFACE_DEFINED__
#define __IColumn_INTERFACE_DEFINED__

/* interface IColumn */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IColumn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFC20A23-CE17-414A-A157-119AE012A0F9")
    IColumn : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_ColumnLayout( 
            /* [in] */ IColumnLayout *pColumnLayout) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnLayout( 
            /* [retval][out] */ IColumnLayout **ppColumnLayout) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Index( 
            /* [in] */ IndexType index) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ IndexType *pIndex) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *height) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ Float64 height) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BaseElevation( 
            /* [retval][out] */ Float64 *baseElevation) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BaseElevation( 
            /* [in] */ Float64 baseElevation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BaseOffset( 
            /* [retval][out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BaseOffset( 
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopElevation( 
            /* [retval][out] */ Float64 *topElev) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IColumn **ppClone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IColumnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IColumn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IColumn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IColumn * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ColumnLayout )( 
            IColumn * This,
            /* [in] */ IColumnLayout *pColumnLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColumnLayout )( 
            IColumn * This,
            /* [retval][out] */ IColumnLayout **ppColumnLayout);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Index )( 
            IColumn * This,
            /* [in] */ IndexType index);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Index )( 
            IColumn * This,
            /* [retval][out] */ IndexType *pIndex);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IColumn * This,
            /* [retval][out] */ Float64 *height);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IColumn * This,
            /* [in] */ Float64 height);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BaseElevation )( 
            IColumn * This,
            /* [retval][out] */ Float64 *baseElevation);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BaseElevation )( 
            IColumn * This,
            /* [in] */ Float64 baseElevation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BaseOffset )( 
            IColumn * This,
            /* [retval][out] */ Float64 *offset);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BaseOffset )( 
            IColumn * This,
            /* [in] */ Float64 offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IColumn * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopElevation )( 
            IColumn * This,
            /* [retval][out] */ Float64 *topElev);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IColumn * This,
            /* [retval][out] */ IColumn **ppClone);
        
        END_INTERFACE
    } IColumnVtbl;

    interface IColumn
    {
        CONST_VTBL struct IColumnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IColumn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IColumn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IColumn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IColumn_putref_ColumnLayout(This,pColumnLayout)	\
    ( (This)->lpVtbl -> putref_ColumnLayout(This,pColumnLayout) ) 

#define IColumn_get_ColumnLayout(This,ppColumnLayout)	\
    ( (This)->lpVtbl -> get_ColumnLayout(This,ppColumnLayout) ) 

#define IColumn_put_Index(This,index)	\
    ( (This)->lpVtbl -> put_Index(This,index) ) 

#define IColumn_get_Index(This,pIndex)	\
    ( (This)->lpVtbl -> get_Index(This,pIndex) ) 

#define IColumn_get_Height(This,height)	\
    ( (This)->lpVtbl -> get_Height(This,height) ) 

#define IColumn_put_Height(This,height)	\
    ( (This)->lpVtbl -> put_Height(This,height) ) 

#define IColumn_get_BaseElevation(This,baseElevation)	\
    ( (This)->lpVtbl -> get_BaseElevation(This,baseElevation) ) 

#define IColumn_put_BaseElevation(This,baseElevation)	\
    ( (This)->lpVtbl -> put_BaseElevation(This,baseElevation) ) 

#define IColumn_get_BaseOffset(This,offset)	\
    ( (This)->lpVtbl -> get_BaseOffset(This,offset) ) 

#define IColumn_put_BaseOffset(This,offset)	\
    ( (This)->lpVtbl -> put_BaseOffset(This,offset) ) 

#define IColumn_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define IColumn_get_TopElevation(This,topElev)	\
    ( (This)->lpVtbl -> get_TopElevation(This,topElev) ) 

#define IColumn_Clone(This,ppClone)	\
    ( (This)->lpVtbl -> Clone(This,ppClone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IColumn_INTERFACE_DEFINED__ */


#ifndef __ILinearCrossBeam_INTERFACE_DEFINED__
#define __ILinearCrossBeam_INTERFACE_DEFINED__

/* interface ILinearCrossBeam */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILinearCrossBeam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B2D3FD5-DAC7-4c48-80DB-8C85820B63EA")
    ILinearCrossBeam : public ICrossBeam
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H1( 
            /* [in] */ Float64 H1) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H1( 
            /* [retval][out] */ Float64 *pH1) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H2( 
            /* [in] */ Float64 H2) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H2( 
            /* [retval][out] */ Float64 *pH2) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H3( 
            /* [in] */ Float64 H3) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H3( 
            /* [retval][out] */ Float64 *pH3) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H4( 
            /* [in] */ Float64 H4) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H4( 
            /* [retval][out] */ Float64 *pH4) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H5( 
            /* [in] */ Float64 H4) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H5( 
            /* [retval][out] */ Float64 *pH4) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X1( 
            /* [in] */ Float64 X1) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X1( 
            /* [retval][out] */ Float64 *pX1) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X2( 
            /* [in] */ Float64 X2) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X2( 
            /* [retval][out] */ Float64 *pX2) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X3( 
            /* [in] */ Float64 X3) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X3( 
            /* [retval][out] */ Float64 *pX3) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X4( 
            /* [in] */ Float64 X4) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X4( 
            /* [retval][out] */ Float64 *pX4) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W1( 
            /* [in] */ Float64 W1) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W1( 
            /* [retval][out] */ Float64 *pW1) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W2( 
            /* [in] */ Float64 W1) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W2( 
            /* [retval][out] */ Float64 *pW1) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILinearCrossBeamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILinearCrossBeam * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILinearCrossBeam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILinearCrossBeam * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Pier )( 
            ILinearCrossBeam * This,
            /* [in] */ IPier *pPier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pier )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ IPier **ppPier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ILinearCrossBeam * This,
            /* [in] */ XBeamLocation location,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Depth )( 
            ILinearCrossBeam * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pDepth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FullDepth )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pDepth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            ILinearCrossBeam * This,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopSurface )( 
            ILinearCrossBeam * This,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomSurface )( 
            ILinearCrossBeam * This,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surface )( 
            ILinearCrossBeam * This,
            /* [in] */ CrossBeamRebarDatum datum,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ILinearCrossBeam * This,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BasicShape )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayout )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ IRebarLayout **ppRebarLayout);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarLayout )( 
            ILinearCrossBeam * This,
            /* [in] */ IRebarLayout *pRebarLayout);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H1 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 H1);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H1 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pH1);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H2 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 H2);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H2 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pH2);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H3 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 H3);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H3 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pH3);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H4 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 H4);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H4 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pH4);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H5 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 H4);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H5 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pH4);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X1 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 X1);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X1 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pX1);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X2 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 X2);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X2 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pX2);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X3 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 X3);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X3 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pX3);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X4 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 X4);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X4 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pX4);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W1 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 W1);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W1 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pW1);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W2 )( 
            ILinearCrossBeam * This,
            /* [in] */ Float64 W1);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W2 )( 
            ILinearCrossBeam * This,
            /* [retval][out] */ Float64 *pW1);
        
        END_INTERFACE
    } ILinearCrossBeamVtbl;

    interface ILinearCrossBeam
    {
        CONST_VTBL struct ILinearCrossBeamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILinearCrossBeam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILinearCrossBeam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILinearCrossBeam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILinearCrossBeam_putref_Pier(This,pPier)	\
    ( (This)->lpVtbl -> putref_Pier(This,pPier) ) 

#define ILinearCrossBeam_get_Pier(This,ppPier)	\
    ( (This)->lpVtbl -> get_Pier(This,ppPier) ) 

#define ILinearCrossBeam_get_Length(This,location,length)	\
    ( (This)->lpVtbl -> get_Length(This,location,length) ) 

#define ILinearCrossBeam_get_Depth(This,stageIdx,Xxb,pDepth)	\
    ( (This)->lpVtbl -> get_Depth(This,stageIdx,Xxb,pDepth) ) 

#define ILinearCrossBeam_get_FullDepth(This,Xxb,pDepth)	\
    ( (This)->lpVtbl -> get_FullDepth(This,Xxb,pDepth) ) 

#define ILinearCrossBeam_get_Profile(This,stageIdx,ppShape)	\
    ( (This)->lpVtbl -> get_Profile(This,stageIdx,ppShape) ) 

#define ILinearCrossBeam_get_TopSurface(This,stageIdx,ppPoints)	\
    ( (This)->lpVtbl -> get_TopSurface(This,stageIdx,ppPoints) ) 

#define ILinearCrossBeam_get_BottomSurface(This,stageIdx,ppPoints)	\
    ( (This)->lpVtbl -> get_BottomSurface(This,stageIdx,ppPoints) ) 

#define ILinearCrossBeam_get_Surface(This,datum,offset,ppPoints)	\
    ( (This)->lpVtbl -> get_Surface(This,datum,offset,ppPoints) ) 

#define ILinearCrossBeam_get_Shape(This,stageIdx,Xxb,ppShape)	\
    ( (This)->lpVtbl -> get_Shape(This,stageIdx,Xxb,ppShape) ) 

#define ILinearCrossBeam_get_BasicShape(This,Xxb,ppShape)	\
    ( (This)->lpVtbl -> get_BasicShape(This,Xxb,ppShape) ) 

#define ILinearCrossBeam_get_RebarLayout(This,ppRebarLayout)	\
    ( (This)->lpVtbl -> get_RebarLayout(This,ppRebarLayout) ) 

#define ILinearCrossBeam_putref_RebarLayout(This,pRebarLayout)	\
    ( (This)->lpVtbl -> putref_RebarLayout(This,pRebarLayout) ) 


#define ILinearCrossBeam_put_H1(This,H1)	\
    ( (This)->lpVtbl -> put_H1(This,H1) ) 

#define ILinearCrossBeam_get_H1(This,pH1)	\
    ( (This)->lpVtbl -> get_H1(This,pH1) ) 

#define ILinearCrossBeam_put_H2(This,H2)	\
    ( (This)->lpVtbl -> put_H2(This,H2) ) 

#define ILinearCrossBeam_get_H2(This,pH2)	\
    ( (This)->lpVtbl -> get_H2(This,pH2) ) 

#define ILinearCrossBeam_put_H3(This,H3)	\
    ( (This)->lpVtbl -> put_H3(This,H3) ) 

#define ILinearCrossBeam_get_H3(This,pH3)	\
    ( (This)->lpVtbl -> get_H3(This,pH3) ) 

#define ILinearCrossBeam_put_H4(This,H4)	\
    ( (This)->lpVtbl -> put_H4(This,H4) ) 

#define ILinearCrossBeam_get_H4(This,pH4)	\
    ( (This)->lpVtbl -> get_H4(This,pH4) ) 

#define ILinearCrossBeam_put_H5(This,H4)	\
    ( (This)->lpVtbl -> put_H5(This,H4) ) 

#define ILinearCrossBeam_get_H5(This,pH4)	\
    ( (This)->lpVtbl -> get_H5(This,pH4) ) 

#define ILinearCrossBeam_put_X1(This,X1)	\
    ( (This)->lpVtbl -> put_X1(This,X1) ) 

#define ILinearCrossBeam_get_X1(This,pX1)	\
    ( (This)->lpVtbl -> get_X1(This,pX1) ) 

#define ILinearCrossBeam_put_X2(This,X2)	\
    ( (This)->lpVtbl -> put_X2(This,X2) ) 

#define ILinearCrossBeam_get_X2(This,pX2)	\
    ( (This)->lpVtbl -> get_X2(This,pX2) ) 

#define ILinearCrossBeam_put_X3(This,X3)	\
    ( (This)->lpVtbl -> put_X3(This,X3) ) 

#define ILinearCrossBeam_get_X3(This,pX3)	\
    ( (This)->lpVtbl -> get_X3(This,pX3) ) 

#define ILinearCrossBeam_put_X4(This,X4)	\
    ( (This)->lpVtbl -> put_X4(This,X4) ) 

#define ILinearCrossBeam_get_X4(This,pX4)	\
    ( (This)->lpVtbl -> get_X4(This,pX4) ) 

#define ILinearCrossBeam_put_W1(This,W1)	\
    ( (This)->lpVtbl -> put_W1(This,W1) ) 

#define ILinearCrossBeam_get_W1(This,pW1)	\
    ( (This)->lpVtbl -> get_W1(This,pW1) ) 

#define ILinearCrossBeam_put_W2(This,W1)	\
    ( (This)->lpVtbl -> put_W2(This,W1) ) 

#define ILinearCrossBeam_get_W2(This,pW1)	\
    ( (This)->lpVtbl -> get_W2(This,pW1) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILinearCrossBeam_INTERFACE_DEFINED__ */


#ifndef __IBearingLayout_INTERFACE_DEFINED__
#define __IBearingLayout_INTERFACE_DEFINED__

/* interface IBearingLayout */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBearingLayout;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DE9531F0-F6F2-4282-9DE2-EE9D78833D4E")
    IBearingLayout : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Pier( 
            /* [in] */ IPier *pPier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Pier( 
            /* [retval][out] */ IPier **ppPier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingLineCount( 
            /* [retval][out] */ IndexType *pnBearingLines) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BearingLineCount( 
            /* [in] */ IndexType nBearingLines) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingLineOffset( 
            /* [in] */ IndexType brgLineIdx,
            /* [retval][out] */ Float64 *pOffset) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BearingLineOffset( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingCount( 
            /* [in] */ IndexType brgLineIdx,
            /* [retval][out] */ IndexType *nBearings) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BearingCount( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType nBearings) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ SpacingIndexType spaceIdx,
            /* [retval][out] */ Float64 *space) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ SpacingIndexType spaceIdx,
            /* [in] */ Float64 space) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType nBearings) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ SpacingIndexType spaceIdx,
            /* [in] */ SpacingIndexType nInsert) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType brgIdx,
            /* [in] */ IndexType nRemove) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetReferenceBearing( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType brgIdx,
            /* [in] */ Float64 alignmentOffset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetReferenceBearing( 
            /* [in] */ IndexType brgLineIdx,
            /* [out] */ IndexType *pBrgIdx,
            /* [out] */ Float64 *pAlignmentOffset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingLayoutWidth( 
            /* [in] */ IndexType brgLineIdx,
            /* [retval][out] */ Float64 *pCLW) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingLocation( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType brgIdx,
            /* [retval][out] */ Float64 *pXxb) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingOffset( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType brgIdx,
            /* [retval][out] */ Float64 *pOffset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingElevation( 
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType brgIdx,
            /* [retval][out] */ Float64 *pElev) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBearingLayoutVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBearingLayout * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBearingLayout * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBearingLayout * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Pier )( 
            IBearingLayout * This,
            /* [in] */ IPier *pPier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pier )( 
            IBearingLayout * This,
            /* [retval][out] */ IPier **ppPier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingLineCount )( 
            IBearingLayout * This,
            /* [retval][out] */ IndexType *pnBearingLines);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BearingLineCount )( 
            IBearingLayout * This,
            /* [in] */ IndexType nBearingLines);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingLineOffset )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [retval][out] */ Float64 *pOffset);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BearingLineOffset )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ Float64 offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingCount )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [retval][out] */ IndexType *nBearings);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BearingCount )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType nBearings);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ SpacingIndexType spaceIdx,
            /* [retval][out] */ Float64 *space);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ SpacingIndexType spaceIdx,
            /* [in] */ Float64 space);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType nBearings);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ SpacingIndexType spaceIdx,
            /* [in] */ SpacingIndexType nInsert);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType brgIdx,
            /* [in] */ IndexType nRemove);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetReferenceBearing )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType brgIdx,
            /* [in] */ Float64 alignmentOffset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetReferenceBearing )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [out] */ IndexType *pBrgIdx,
            /* [out] */ Float64 *pAlignmentOffset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingLayoutWidth )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [retval][out] */ Float64 *pCLW);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingLocation )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType brgIdx,
            /* [retval][out] */ Float64 *pXxb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingOffset )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType brgIdx,
            /* [retval][out] */ Float64 *pOffset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingElevation )( 
            IBearingLayout * This,
            /* [in] */ IndexType brgLineIdx,
            /* [in] */ IndexType brgIdx,
            /* [retval][out] */ Float64 *pElev);
        
        END_INTERFACE
    } IBearingLayoutVtbl;

    interface IBearingLayout
    {
        CONST_VTBL struct IBearingLayoutVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBearingLayout_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBearingLayout_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBearingLayout_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBearingLayout_putref_Pier(This,pPier)	\
    ( (This)->lpVtbl -> putref_Pier(This,pPier) ) 

#define IBearingLayout_get_Pier(This,ppPier)	\
    ( (This)->lpVtbl -> get_Pier(This,ppPier) ) 

#define IBearingLayout_get_BearingLineCount(This,pnBearingLines)	\
    ( (This)->lpVtbl -> get_BearingLineCount(This,pnBearingLines) ) 

#define IBearingLayout_put_BearingLineCount(This,nBearingLines)	\
    ( (This)->lpVtbl -> put_BearingLineCount(This,nBearingLines) ) 

#define IBearingLayout_get_BearingLineOffset(This,brgLineIdx,pOffset)	\
    ( (This)->lpVtbl -> get_BearingLineOffset(This,brgLineIdx,pOffset) ) 

#define IBearingLayout_put_BearingLineOffset(This,brgLineIdx,offset)	\
    ( (This)->lpVtbl -> put_BearingLineOffset(This,brgLineIdx,offset) ) 

#define IBearingLayout_get_BearingCount(This,brgLineIdx,nBearings)	\
    ( (This)->lpVtbl -> get_BearingCount(This,brgLineIdx,nBearings) ) 

#define IBearingLayout_put_BearingCount(This,brgLineIdx,nBearings)	\
    ( (This)->lpVtbl -> put_BearingCount(This,brgLineIdx,nBearings) ) 

#define IBearingLayout_get_Spacing(This,brgLineIdx,spaceIdx,space)	\
    ( (This)->lpVtbl -> get_Spacing(This,brgLineIdx,spaceIdx,space) ) 

#define IBearingLayout_put_Spacing(This,brgLineIdx,spaceIdx,space)	\
    ( (This)->lpVtbl -> put_Spacing(This,brgLineIdx,spaceIdx,space) ) 

#define IBearingLayout_Add(This,brgLineIdx,nBearings)	\
    ( (This)->lpVtbl -> Add(This,brgLineIdx,nBearings) ) 

#define IBearingLayout_Insert(This,brgLineIdx,spaceIdx,nInsert)	\
    ( (This)->lpVtbl -> Insert(This,brgLineIdx,spaceIdx,nInsert) ) 

#define IBearingLayout_Remove(This,brgLineIdx,brgIdx,nRemove)	\
    ( (This)->lpVtbl -> Remove(This,brgLineIdx,brgIdx,nRemove) ) 

#define IBearingLayout_SetReferenceBearing(This,brgLineIdx,brgIdx,alignmentOffset)	\
    ( (This)->lpVtbl -> SetReferenceBearing(This,brgLineIdx,brgIdx,alignmentOffset) ) 

#define IBearingLayout_GetReferenceBearing(This,brgLineIdx,pBrgIdx,pAlignmentOffset)	\
    ( (This)->lpVtbl -> GetReferenceBearing(This,brgLineIdx,pBrgIdx,pAlignmentOffset) ) 

#define IBearingLayout_get_BearingLayoutWidth(This,brgLineIdx,pCLW)	\
    ( (This)->lpVtbl -> get_BearingLayoutWidth(This,brgLineIdx,pCLW) ) 

#define IBearingLayout_get_BearingLocation(This,brgLineIdx,brgIdx,pXxb)	\
    ( (This)->lpVtbl -> get_BearingLocation(This,brgLineIdx,brgIdx,pXxb) ) 

#define IBearingLayout_get_BearingOffset(This,brgLineIdx,brgIdx,pOffset)	\
    ( (This)->lpVtbl -> get_BearingOffset(This,brgLineIdx,brgIdx,pOffset) ) 

#define IBearingLayout_get_BearingElevation(This,brgLineIdx,brgIdx,pElev)	\
    ( (This)->lpVtbl -> get_BearingElevation(This,brgLineIdx,brgIdx,pElev) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBearingLayout_INTERFACE_DEFINED__ */


#ifndef __IBridgePier_INTERFACE_DEFINED__
#define __IBridgePier_INTERFACE_DEFINED__

/* interface IBridgePier */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBridgePier;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C5D65F83-7B6C-468f-95EC-BE3F320E2492")
    IBridgePier : public IPier
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Bridge( 
            /* [retval][out] */ IGenericBridge **ppBridge) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ PierIndexType *pIndex) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ PierIDType *pID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Station( 
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ IDirection **direction) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBridgePierVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBridgePier * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBridgePier * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBridgePier * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IBridgePier * This,
            /* [in] */ PierType type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IBridgePier * This,
            /* [retval][out] */ PierType *type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeckProfile )( 
            IBridgePier * This,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeckThickness )( 
            IBridgePier * This,
            /* [retval][out] */ Float64 *pTDeck);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbLineOffset )( 
            IBridgePier * This,
            /* [in] */ DirectionType side,
            /* [in] */ CurbLineMeasurementType clMeasure,
            /* [retval][out] */ Float64 *pCLO);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbToCurbWidth )( 
            IBridgePier * This,
            /* [in] */ CurbLineMeasurementType clMeasure,
            /* [retval][out] */ Float64 *pWcc);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SkewAngle )( 
            IBridgePier * This,
            /* [in] */ IAngle *pSkew);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SkewAngle )( 
            IBridgePier * This,
            /* [retval][out] */ IAngle **ppSkew);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_CrossBeam )( 
            IBridgePier * This,
            /* [in] */ ICrossBeam *pCrossBeam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CrossBeam )( 
            IBridgePier * This,
            /* [retval][out] */ ICrossBeam **ppCrossBeam);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_BearingLayout )( 
            IBridgePier * This,
            /* [in] */ IBearingLayout *pBearingLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingLayout )( 
            IBridgePier * This,
            /* [retval][out] */ IBearingLayout **ppBearingLayout);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ColumnLayout )( 
            IBridgePier * This,
            /* [in] */ IColumnLayout *pColumnLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColumnLayout )( 
            IBridgePier * This,
            /* [retval][out] */ IColumnLayout **ppColumnLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Column )( 
            IBridgePier * This,
            /* [in] */ ColumnIndexType columnIdx,
            /* [retval][out] */ IColumn **column);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCrossBeamToCurbLineCoordinate )( 
            IBridgePier * This,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pXcl);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCurbLineToCrossBeamCoordinate )( 
            IBridgePier * This,
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pXxb);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertPierToCrossBeamCoordinate )( 
            IBridgePier * This,
            /* [in] */ Float64 Xp,
            /* [retval][out] */ Float64 *pXxb);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCrossBeamToPierCoordinate )( 
            IBridgePier * This,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pXp);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertPierToCurbLineCoordinate )( 
            IBridgePier * This,
            /* [in] */ Float64 Xp,
            /* [retval][out] */ Float64 *pXcl);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCurbLineToPierCoordinate )( 
            IBridgePier * This,
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pXp);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Elevation )( 
            IBridgePier * This,
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pElev);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbLineElevation )( 
            IBridgePier * This,
            /* [in] */ DirectionType side,
            /* [retval][out] */ Float64 *pElev);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bridge )( 
            IBridgePier * This,
            /* [retval][out] */ IGenericBridge **ppBridge);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Index )( 
            IBridgePier * This,
            /* [retval][out] */ PierIndexType *pIndex);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IBridgePier * This,
            /* [retval][out] */ PierIDType *pID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Station )( 
            IBridgePier * This,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Direction )( 
            IBridgePier * This,
            /* [retval][out] */ IDirection **direction);
        
        END_INTERFACE
    } IBridgePierVtbl;

    interface IBridgePier
    {
        CONST_VTBL struct IBridgePierVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBridgePier_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBridgePier_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBridgePier_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBridgePier_put_Type(This,type)	\
    ( (This)->lpVtbl -> put_Type(This,type) ) 

#define IBridgePier_get_Type(This,type)	\
    ( (This)->lpVtbl -> get_Type(This,type) ) 

#define IBridgePier_get_DeckProfile(This,ppPoints)	\
    ( (This)->lpVtbl -> get_DeckProfile(This,ppPoints) ) 

#define IBridgePier_get_DeckThickness(This,pTDeck)	\
    ( (This)->lpVtbl -> get_DeckThickness(This,pTDeck) ) 

#define IBridgePier_get_CurbLineOffset(This,side,clMeasure,pCLO)	\
    ( (This)->lpVtbl -> get_CurbLineOffset(This,side,clMeasure,pCLO) ) 

#define IBridgePier_get_CurbToCurbWidth(This,clMeasure,pWcc)	\
    ( (This)->lpVtbl -> get_CurbToCurbWidth(This,clMeasure,pWcc) ) 

#define IBridgePier_putref_SkewAngle(This,pSkew)	\
    ( (This)->lpVtbl -> putref_SkewAngle(This,pSkew) ) 

#define IBridgePier_get_SkewAngle(This,ppSkew)	\
    ( (This)->lpVtbl -> get_SkewAngle(This,ppSkew) ) 

#define IBridgePier_putref_CrossBeam(This,pCrossBeam)	\
    ( (This)->lpVtbl -> putref_CrossBeam(This,pCrossBeam) ) 

#define IBridgePier_get_CrossBeam(This,ppCrossBeam)	\
    ( (This)->lpVtbl -> get_CrossBeam(This,ppCrossBeam) ) 

#define IBridgePier_putref_BearingLayout(This,pBearingLayout)	\
    ( (This)->lpVtbl -> putref_BearingLayout(This,pBearingLayout) ) 

#define IBridgePier_get_BearingLayout(This,ppBearingLayout)	\
    ( (This)->lpVtbl -> get_BearingLayout(This,ppBearingLayout) ) 

#define IBridgePier_putref_ColumnLayout(This,pColumnLayout)	\
    ( (This)->lpVtbl -> putref_ColumnLayout(This,pColumnLayout) ) 

#define IBridgePier_get_ColumnLayout(This,ppColumnLayout)	\
    ( (This)->lpVtbl -> get_ColumnLayout(This,ppColumnLayout) ) 

#define IBridgePier_get_Column(This,columnIdx,column)	\
    ( (This)->lpVtbl -> get_Column(This,columnIdx,column) ) 

#define IBridgePier_ConvertCrossBeamToCurbLineCoordinate(This,Xxb,pXcl)	\
    ( (This)->lpVtbl -> ConvertCrossBeamToCurbLineCoordinate(This,Xxb,pXcl) ) 

#define IBridgePier_ConvertCurbLineToCrossBeamCoordinate(This,Xcl,pXxb)	\
    ( (This)->lpVtbl -> ConvertCurbLineToCrossBeamCoordinate(This,Xcl,pXxb) ) 

#define IBridgePier_ConvertPierToCrossBeamCoordinate(This,Xp,pXxb)	\
    ( (This)->lpVtbl -> ConvertPierToCrossBeamCoordinate(This,Xp,pXxb) ) 

#define IBridgePier_ConvertCrossBeamToPierCoordinate(This,Xxb,pXp)	\
    ( (This)->lpVtbl -> ConvertCrossBeamToPierCoordinate(This,Xxb,pXp) ) 

#define IBridgePier_ConvertPierToCurbLineCoordinate(This,Xp,pXcl)	\
    ( (This)->lpVtbl -> ConvertPierToCurbLineCoordinate(This,Xp,pXcl) ) 

#define IBridgePier_ConvertCurbLineToPierCoordinate(This,Xcl,pXp)	\
    ( (This)->lpVtbl -> ConvertCurbLineToPierCoordinate(This,Xcl,pXp) ) 

#define IBridgePier_get_Elevation(This,Xcl,pElev)	\
    ( (This)->lpVtbl -> get_Elevation(This,Xcl,pElev) ) 

#define IBridgePier_get_CurbLineElevation(This,side,pElev)	\
    ( (This)->lpVtbl -> get_CurbLineElevation(This,side,pElev) ) 


#define IBridgePier_get_Bridge(This,ppBridge)	\
    ( (This)->lpVtbl -> get_Bridge(This,ppBridge) ) 

#define IBridgePier_get_Index(This,pIndex)	\
    ( (This)->lpVtbl -> get_Index(This,pIndex) ) 

#define IBridgePier_get_ID(This,pID)	\
    ( (This)->lpVtbl -> get_ID(This,pID) ) 

#define IBridgePier_get_Station(This,station)	\
    ( (This)->lpVtbl -> get_Station(This,station) ) 

#define IBridgePier_get_Direction(This,direction)	\
    ( (This)->lpVtbl -> get_Direction(This,direction) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBridgePier_INTERFACE_DEFINED__ */


#ifndef __IPierEx_INTERFACE_DEFINED__
#define __IPierEx_INTERFACE_DEFINED__

/* interface IPierEx */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPierEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7C088AD6-C6BA-4DB7-910B-B13725973471")
    IPierEx : public IPier
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_DeckProfile( 
            /* [in] */ IPoint2dCollection *pPoints) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DeckThickness( 
            /* [in] */ Float64 tDeck) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CurbLineOffset( 
            /* [in] */ DirectionType side,
            /* [in] */ Float64 clo) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPierExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPierEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPierEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPierEx * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IPierEx * This,
            /* [in] */ PierType type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IPierEx * This,
            /* [retval][out] */ PierType *type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeckProfile )( 
            IPierEx * This,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeckThickness )( 
            IPierEx * This,
            /* [retval][out] */ Float64 *pTDeck);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbLineOffset )( 
            IPierEx * This,
            /* [in] */ DirectionType side,
            /* [in] */ CurbLineMeasurementType clMeasure,
            /* [retval][out] */ Float64 *pCLO);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbToCurbWidth )( 
            IPierEx * This,
            /* [in] */ CurbLineMeasurementType clMeasure,
            /* [retval][out] */ Float64 *pWcc);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SkewAngle )( 
            IPierEx * This,
            /* [in] */ IAngle *pSkew);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SkewAngle )( 
            IPierEx * This,
            /* [retval][out] */ IAngle **ppSkew);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_CrossBeam )( 
            IPierEx * This,
            /* [in] */ ICrossBeam *pCrossBeam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CrossBeam )( 
            IPierEx * This,
            /* [retval][out] */ ICrossBeam **ppCrossBeam);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_BearingLayout )( 
            IPierEx * This,
            /* [in] */ IBearingLayout *pBearingLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingLayout )( 
            IPierEx * This,
            /* [retval][out] */ IBearingLayout **ppBearingLayout);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ColumnLayout )( 
            IPierEx * This,
            /* [in] */ IColumnLayout *pColumnLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColumnLayout )( 
            IPierEx * This,
            /* [retval][out] */ IColumnLayout **ppColumnLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Column )( 
            IPierEx * This,
            /* [in] */ ColumnIndexType columnIdx,
            /* [retval][out] */ IColumn **column);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCrossBeamToCurbLineCoordinate )( 
            IPierEx * This,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pXcl);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCurbLineToCrossBeamCoordinate )( 
            IPierEx * This,
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pXxb);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertPierToCrossBeamCoordinate )( 
            IPierEx * This,
            /* [in] */ Float64 Xp,
            /* [retval][out] */ Float64 *pXxb);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCrossBeamToPierCoordinate )( 
            IPierEx * This,
            /* [in] */ Float64 Xxb,
            /* [retval][out] */ Float64 *pXp);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertPierToCurbLineCoordinate )( 
            IPierEx * This,
            /* [in] */ Float64 Xp,
            /* [retval][out] */ Float64 *pXcl);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertCurbLineToPierCoordinate )( 
            IPierEx * This,
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pXp);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Elevation )( 
            IPierEx * This,
            /* [in] */ Float64 Xcl,
            /* [retval][out] */ Float64 *pElev);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurbLineElevation )( 
            IPierEx * This,
            /* [in] */ DirectionType side,
            /* [retval][out] */ Float64 *pElev);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DeckProfile )( 
            IPierEx * This,
            /* [in] */ IPoint2dCollection *pPoints);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DeckThickness )( 
            IPierEx * This,
            /* [in] */ Float64 tDeck);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CurbLineOffset )( 
            IPierEx * This,
            /* [in] */ DirectionType side,
            /* [in] */ Float64 clo);
        
        END_INTERFACE
    } IPierExVtbl;

    interface IPierEx
    {
        CONST_VTBL struct IPierExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPierEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPierEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPierEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPierEx_put_Type(This,type)	\
    ( (This)->lpVtbl -> put_Type(This,type) ) 

#define IPierEx_get_Type(This,type)	\
    ( (This)->lpVtbl -> get_Type(This,type) ) 

#define IPierEx_get_DeckProfile(This,ppPoints)	\
    ( (This)->lpVtbl -> get_DeckProfile(This,ppPoints) ) 

#define IPierEx_get_DeckThickness(This,pTDeck)	\
    ( (This)->lpVtbl -> get_DeckThickness(This,pTDeck) ) 

#define IPierEx_get_CurbLineOffset(This,side,clMeasure,pCLO)	\
    ( (This)->lpVtbl -> get_CurbLineOffset(This,side,clMeasure,pCLO) ) 

#define IPierEx_get_CurbToCurbWidth(This,clMeasure,pWcc)	\
    ( (This)->lpVtbl -> get_CurbToCurbWidth(This,clMeasure,pWcc) ) 

#define IPierEx_putref_SkewAngle(This,pSkew)	\
    ( (This)->lpVtbl -> putref_SkewAngle(This,pSkew) ) 

#define IPierEx_get_SkewAngle(This,ppSkew)	\
    ( (This)->lpVtbl -> get_SkewAngle(This,ppSkew) ) 

#define IPierEx_putref_CrossBeam(This,pCrossBeam)	\
    ( (This)->lpVtbl -> putref_CrossBeam(This,pCrossBeam) ) 

#define IPierEx_get_CrossBeam(This,ppCrossBeam)	\
    ( (This)->lpVtbl -> get_CrossBeam(This,ppCrossBeam) ) 

#define IPierEx_putref_BearingLayout(This,pBearingLayout)	\
    ( (This)->lpVtbl -> putref_BearingLayout(This,pBearingLayout) ) 

#define IPierEx_get_BearingLayout(This,ppBearingLayout)	\
    ( (This)->lpVtbl -> get_BearingLayout(This,ppBearingLayout) ) 

#define IPierEx_putref_ColumnLayout(This,pColumnLayout)	\
    ( (This)->lpVtbl -> putref_ColumnLayout(This,pColumnLayout) ) 

#define IPierEx_get_ColumnLayout(This,ppColumnLayout)	\
    ( (This)->lpVtbl -> get_ColumnLayout(This,ppColumnLayout) ) 

#define IPierEx_get_Column(This,columnIdx,column)	\
    ( (This)->lpVtbl -> get_Column(This,columnIdx,column) ) 

#define IPierEx_ConvertCrossBeamToCurbLineCoordinate(This,Xxb,pXcl)	\
    ( (This)->lpVtbl -> ConvertCrossBeamToCurbLineCoordinate(This,Xxb,pXcl) ) 

#define IPierEx_ConvertCurbLineToCrossBeamCoordinate(This,Xcl,pXxb)	\
    ( (This)->lpVtbl -> ConvertCurbLineToCrossBeamCoordinate(This,Xcl,pXxb) ) 

#define IPierEx_ConvertPierToCrossBeamCoordinate(This,Xp,pXxb)	\
    ( (This)->lpVtbl -> ConvertPierToCrossBeamCoordinate(This,Xp,pXxb) ) 

#define IPierEx_ConvertCrossBeamToPierCoordinate(This,Xxb,pXp)	\
    ( (This)->lpVtbl -> ConvertCrossBeamToPierCoordinate(This,Xxb,pXp) ) 

#define IPierEx_ConvertPierToCurbLineCoordinate(This,Xp,pXcl)	\
    ( (This)->lpVtbl -> ConvertPierToCurbLineCoordinate(This,Xp,pXcl) ) 

#define IPierEx_ConvertCurbLineToPierCoordinate(This,Xcl,pXp)	\
    ( (This)->lpVtbl -> ConvertCurbLineToPierCoordinate(This,Xcl,pXp) ) 

#define IPierEx_get_Elevation(This,Xcl,pElev)	\
    ( (This)->lpVtbl -> get_Elevation(This,Xcl,pElev) ) 

#define IPierEx_get_CurbLineElevation(This,side,pElev)	\
    ( (This)->lpVtbl -> get_CurbLineElevation(This,side,pElev) ) 


#define IPierEx_putref_DeckProfile(This,pPoints)	\
    ( (This)->lpVtbl -> putref_DeckProfile(This,pPoints) ) 

#define IPierEx_put_DeckThickness(This,tDeck)	\
    ( (This)->lpVtbl -> put_DeckThickness(This,tDeck) ) 

#define IPierEx_put_CurbLineOffset(This,side,clo)	\
    ( (This)->lpVtbl -> put_CurbLineOffset(This,side,clo) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPierEx_INTERFACE_DEFINED__ */


#ifndef __IGirderSection_INTERFACE_DEFINED__
#define __IGirderSection_INTERFACE_DEFINED__

/* interface IGirderSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGirderSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("750677B3-DEA8-4e2d-B080-C54E0E948937")
    IGirderSection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebCount( 
            /* [retval][out] */ WebIndexType *nWebs) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebLocation( 
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ Float64 *location) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebSpacing( 
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ Float64 *spacing) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebThickness( 
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ Float64 *tWeb) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MinWebThickness( 
            /* [retval][out] */ Float64 *tWeb) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebPlane( 
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ IPlane3d **ppPlane) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EffectiveWebThickness( 
            /* [retval][out] */ Float64 *tWeb) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MatingSurfaceCount( 
            /* [retval][out] */ MatingSurfaceIndexType *nMatingSurfaces) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MatingSurfaceLocation( 
            /* [in] */ MatingSurfaceIndexType idx,
            /* [retval][out] */ Float64 *location) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MatingSurfaceWidth( 
            /* [in] */ MatingSurfaceIndexType idx,
            /* [retval][out] */ Float64 *wMatingSurface) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeCount( 
            /* [retval][out] */ FlangeIndexType *nTopFlanges) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeLocation( 
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *location) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *wFlange) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeThickness( 
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *tFlange) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeSpacing( 
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *spacing) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeCount( 
            /* [retval][out] */ FlangeIndexType *nBottomFlanges) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeLocation( 
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *location) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeWidth( 
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *wFlange) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeThickness( 
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *tFlange) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeSpacing( 
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *spacing) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GirderHeight( 
            /* [retval][out] */ Float64 *height) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopWidth( 
            /* [retval][out] */ Float64 *width) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomWidth( 
            /* [retval][out] */ Float64 *width) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShearWidth( 
            /* [retval][out] */ Float64 *shearwidth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MinTopFlangeThickness( 
            /* [retval][out] */ Float64 *tf) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MinBottomFlangeThickness( 
            /* [retval][out] */ Float64 *tf) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CL2ExteriorWebDistance( 
            /* [in] */ DirectionType side,
            /* [retval][out] */ Float64 *tf) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGirderSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGirderSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGirderSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGirderSection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebCount )( 
            IGirderSection * This,
            /* [retval][out] */ WebIndexType *nWebs);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebLocation )( 
            IGirderSection * This,
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebSpacing )( 
            IGirderSection * This,
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebThickness )( 
            IGirderSection * This,
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ Float64 *tWeb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinWebThickness )( 
            IGirderSection * This,
            /* [retval][out] */ Float64 *tWeb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebPlane )( 
            IGirderSection * This,
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ IPlane3d **ppPlane);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EffectiveWebThickness )( 
            IGirderSection * This,
            /* [retval][out] */ Float64 *tWeb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MatingSurfaceCount )( 
            IGirderSection * This,
            /* [retval][out] */ MatingSurfaceIndexType *nMatingSurfaces);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MatingSurfaceLocation )( 
            IGirderSection * This,
            /* [in] */ MatingSurfaceIndexType idx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MatingSurfaceWidth )( 
            IGirderSection * This,
            /* [in] */ MatingSurfaceIndexType idx,
            /* [retval][out] */ Float64 *wMatingSurface);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeCount )( 
            IGirderSection * This,
            /* [retval][out] */ FlangeIndexType *nTopFlanges);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeLocation )( 
            IGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *wFlange);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeThickness )( 
            IGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *tFlange);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeSpacing )( 
            IGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeCount )( 
            IGirderSection * This,
            /* [retval][out] */ FlangeIndexType *nBottomFlanges);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeLocation )( 
            IGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeWidth )( 
            IGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *wFlange);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeThickness )( 
            IGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *tFlange);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeSpacing )( 
            IGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderHeight )( 
            IGirderSection * This,
            /* [retval][out] */ Float64 *height);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopWidth )( 
            IGirderSection * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomWidth )( 
            IGirderSection * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShearWidth )( 
            IGirderSection * This,
            /* [retval][out] */ Float64 *shearwidth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinTopFlangeThickness )( 
            IGirderSection * This,
            /* [retval][out] */ Float64 *tf);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinBottomFlangeThickness )( 
            IGirderSection * This,
            /* [retval][out] */ Float64 *tf);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CL2ExteriorWebDistance )( 
            IGirderSection * This,
            /* [in] */ DirectionType side,
            /* [retval][out] */ Float64 *tf);
        
        END_INTERFACE
    } IGirderSectionVtbl;

    interface IGirderSection
    {
        CONST_VTBL struct IGirderSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGirderSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGirderSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGirderSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGirderSection_get_WebCount(This,nWebs)	\
    ( (This)->lpVtbl -> get_WebCount(This,nWebs) ) 

#define IGirderSection_get_WebLocation(This,idx,location)	\
    ( (This)->lpVtbl -> get_WebLocation(This,idx,location) ) 

#define IGirderSection_get_WebSpacing(This,idx,spacing)	\
    ( (This)->lpVtbl -> get_WebSpacing(This,idx,spacing) ) 

#define IGirderSection_get_WebThickness(This,idx,tWeb)	\
    ( (This)->lpVtbl -> get_WebThickness(This,idx,tWeb) ) 

#define IGirderSection_get_MinWebThickness(This,tWeb)	\
    ( (This)->lpVtbl -> get_MinWebThickness(This,tWeb) ) 

#define IGirderSection_get_WebPlane(This,idx,ppPlane)	\
    ( (This)->lpVtbl -> get_WebPlane(This,idx,ppPlane) ) 

#define IGirderSection_get_EffectiveWebThickness(This,tWeb)	\
    ( (This)->lpVtbl -> get_EffectiveWebThickness(This,tWeb) ) 

#define IGirderSection_get_MatingSurfaceCount(This,nMatingSurfaces)	\
    ( (This)->lpVtbl -> get_MatingSurfaceCount(This,nMatingSurfaces) ) 

#define IGirderSection_get_MatingSurfaceLocation(This,idx,location)	\
    ( (This)->lpVtbl -> get_MatingSurfaceLocation(This,idx,location) ) 

#define IGirderSection_get_MatingSurfaceWidth(This,idx,wMatingSurface)	\
    ( (This)->lpVtbl -> get_MatingSurfaceWidth(This,idx,wMatingSurface) ) 

#define IGirderSection_get_TopFlangeCount(This,nTopFlanges)	\
    ( (This)->lpVtbl -> get_TopFlangeCount(This,nTopFlanges) ) 

#define IGirderSection_get_TopFlangeLocation(This,idx,location)	\
    ( (This)->lpVtbl -> get_TopFlangeLocation(This,idx,location) ) 

#define IGirderSection_get_TopFlangeWidth(This,idx,wFlange)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,idx,wFlange) ) 

#define IGirderSection_get_TopFlangeThickness(This,idx,tFlange)	\
    ( (This)->lpVtbl -> get_TopFlangeThickness(This,idx,tFlange) ) 

#define IGirderSection_get_TopFlangeSpacing(This,idx,spacing)	\
    ( (This)->lpVtbl -> get_TopFlangeSpacing(This,idx,spacing) ) 

#define IGirderSection_get_BottomFlangeCount(This,nBottomFlanges)	\
    ( (This)->lpVtbl -> get_BottomFlangeCount(This,nBottomFlanges) ) 

#define IGirderSection_get_BottomFlangeLocation(This,idx,location)	\
    ( (This)->lpVtbl -> get_BottomFlangeLocation(This,idx,location) ) 

#define IGirderSection_get_BottomFlangeWidth(This,idx,wFlange)	\
    ( (This)->lpVtbl -> get_BottomFlangeWidth(This,idx,wFlange) ) 

#define IGirderSection_get_BottomFlangeThickness(This,idx,tFlange)	\
    ( (This)->lpVtbl -> get_BottomFlangeThickness(This,idx,tFlange) ) 

#define IGirderSection_get_BottomFlangeSpacing(This,idx,spacing)	\
    ( (This)->lpVtbl -> get_BottomFlangeSpacing(This,idx,spacing) ) 

#define IGirderSection_get_GirderHeight(This,height)	\
    ( (This)->lpVtbl -> get_GirderHeight(This,height) ) 

#define IGirderSection_get_TopWidth(This,width)	\
    ( (This)->lpVtbl -> get_TopWidth(This,width) ) 

#define IGirderSection_get_BottomWidth(This,width)	\
    ( (This)->lpVtbl -> get_BottomWidth(This,width) ) 

#define IGirderSection_get_ShearWidth(This,shearwidth)	\
    ( (This)->lpVtbl -> get_ShearWidth(This,shearwidth) ) 

#define IGirderSection_get_MinTopFlangeThickness(This,tf)	\
    ( (This)->lpVtbl -> get_MinTopFlangeThickness(This,tf) ) 

#define IGirderSection_get_MinBottomFlangeThickness(This,tf)	\
    ( (This)->lpVtbl -> get_MinBottomFlangeThickness(This,tf) ) 

#define IGirderSection_get_CL2ExteriorWebDistance(This,side,tf)	\
    ( (This)->lpVtbl -> get_CL2ExteriorWebDistance(This,side,tf) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGirderSection_INTERFACE_DEFINED__ */


#ifndef __IPrestressedGirderSection_INTERFACE_DEFINED__
#define __IPrestressedGirderSection_INTERFACE_DEFINED__

/* interface IPrestressedGirderSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPrestressedGirderSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AC74618B-C45B-4976-B015-8ECBBD9C6889")
    IPrestressedGirderSection : public IGirderSection
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SplittingZoneDimension( 
            /* [retval][out] */ Float64 *pSZD) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SplittingDirection( 
            /* [retval][out] */ SplittingDirection *pSD) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPrestressedGirderSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPrestressedGirderSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPrestressedGirderSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPrestressedGirderSection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebCount )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ WebIndexType *nWebs);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebLocation )( 
            IPrestressedGirderSection * This,
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebSpacing )( 
            IPrestressedGirderSection * This,
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebThickness )( 
            IPrestressedGirderSection * This,
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ Float64 *tWeb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinWebThickness )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ Float64 *tWeb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebPlane )( 
            IPrestressedGirderSection * This,
            /* [in] */ WebIndexType idx,
            /* [retval][out] */ IPlane3d **ppPlane);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EffectiveWebThickness )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ Float64 *tWeb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MatingSurfaceCount )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ MatingSurfaceIndexType *nMatingSurfaces);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MatingSurfaceLocation )( 
            IPrestressedGirderSection * This,
            /* [in] */ MatingSurfaceIndexType idx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MatingSurfaceWidth )( 
            IPrestressedGirderSection * This,
            /* [in] */ MatingSurfaceIndexType idx,
            /* [retval][out] */ Float64 *wMatingSurface);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeCount )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ FlangeIndexType *nTopFlanges);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeLocation )( 
            IPrestressedGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IPrestressedGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *wFlange);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeThickness )( 
            IPrestressedGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *tFlange);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeSpacing )( 
            IPrestressedGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeCount )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ FlangeIndexType *nBottomFlanges);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeLocation )( 
            IPrestressedGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeWidth )( 
            IPrestressedGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *wFlange);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeThickness )( 
            IPrestressedGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *tFlange);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeSpacing )( 
            IPrestressedGirderSection * This,
            /* [in] */ FlangeIndexType idx,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderHeight )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ Float64 *height);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopWidth )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomWidth )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShearWidth )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ Float64 *shearwidth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinTopFlangeThickness )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ Float64 *tf);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinBottomFlangeThickness )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ Float64 *tf);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CL2ExteriorWebDistance )( 
            IPrestressedGirderSection * This,
            /* [in] */ DirectionType side,
            /* [retval][out] */ Float64 *tf);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SplittingZoneDimension )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ Float64 *pSZD);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SplittingDirection )( 
            IPrestressedGirderSection * This,
            /* [retval][out] */ SplittingDirection *pSD);
        
        END_INTERFACE
    } IPrestressedGirderSectionVtbl;

    interface IPrestressedGirderSection
    {
        CONST_VTBL struct IPrestressedGirderSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrestressedGirderSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPrestressedGirderSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPrestressedGirderSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPrestressedGirderSection_get_WebCount(This,nWebs)	\
    ( (This)->lpVtbl -> get_WebCount(This,nWebs) ) 

#define IPrestressedGirderSection_get_WebLocation(This,idx,location)	\
    ( (This)->lpVtbl -> get_WebLocation(This,idx,location) ) 

#define IPrestressedGirderSection_get_WebSpacing(This,idx,spacing)	\
    ( (This)->lpVtbl -> get_WebSpacing(This,idx,spacing) ) 

#define IPrestressedGirderSection_get_WebThickness(This,idx,tWeb)	\
    ( (This)->lpVtbl -> get_WebThickness(This,idx,tWeb) ) 

#define IPrestressedGirderSection_get_MinWebThickness(This,tWeb)	\
    ( (This)->lpVtbl -> get_MinWebThickness(This,tWeb) ) 

#define IPrestressedGirderSection_get_WebPlane(This,idx,ppPlane)	\
    ( (This)->lpVtbl -> get_WebPlane(This,idx,ppPlane) ) 

#define IPrestressedGirderSection_get_EffectiveWebThickness(This,tWeb)	\
    ( (This)->lpVtbl -> get_EffectiveWebThickness(This,tWeb) ) 

#define IPrestressedGirderSection_get_MatingSurfaceCount(This,nMatingSurfaces)	\
    ( (This)->lpVtbl -> get_MatingSurfaceCount(This,nMatingSurfaces) ) 

#define IPrestressedGirderSection_get_MatingSurfaceLocation(This,idx,location)	\
    ( (This)->lpVtbl -> get_MatingSurfaceLocation(This,idx,location) ) 

#define IPrestressedGirderSection_get_MatingSurfaceWidth(This,idx,wMatingSurface)	\
    ( (This)->lpVtbl -> get_MatingSurfaceWidth(This,idx,wMatingSurface) ) 

#define IPrestressedGirderSection_get_TopFlangeCount(This,nTopFlanges)	\
    ( (This)->lpVtbl -> get_TopFlangeCount(This,nTopFlanges) ) 

#define IPrestressedGirderSection_get_TopFlangeLocation(This,idx,location)	\
    ( (This)->lpVtbl -> get_TopFlangeLocation(This,idx,location) ) 

#define IPrestressedGirderSection_get_TopFlangeWidth(This,idx,wFlange)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,idx,wFlange) ) 

#define IPrestressedGirderSection_get_TopFlangeThickness(This,idx,tFlange)	\
    ( (This)->lpVtbl -> get_TopFlangeThickness(This,idx,tFlange) ) 

#define IPrestressedGirderSection_get_TopFlangeSpacing(This,idx,spacing)	\
    ( (This)->lpVtbl -> get_TopFlangeSpacing(This,idx,spacing) ) 

#define IPrestressedGirderSection_get_BottomFlangeCount(This,nBottomFlanges)	\
    ( (This)->lpVtbl -> get_BottomFlangeCount(This,nBottomFlanges) ) 

#define IPrestressedGirderSection_get_BottomFlangeLocation(This,idx,location)	\
    ( (This)->lpVtbl -> get_BottomFlangeLocation(This,idx,location) ) 

#define IPrestressedGirderSection_get_BottomFlangeWidth(This,idx,wFlange)	\
    ( (This)->lpVtbl -> get_BottomFlangeWidth(This,idx,wFlange) ) 

#define IPrestressedGirderSection_get_BottomFlangeThickness(This,idx,tFlange)	\
    ( (This)->lpVtbl -> get_BottomFlangeThickness(This,idx,tFlange) ) 

#define IPrestressedGirderSection_get_BottomFlangeSpacing(This,idx,spacing)	\
    ( (This)->lpVtbl -> get_BottomFlangeSpacing(This,idx,spacing) ) 

#define IPrestressedGirderSection_get_GirderHeight(This,height)	\
    ( (This)->lpVtbl -> get_GirderHeight(This,height) ) 

#define IPrestressedGirderSection_get_TopWidth(This,width)	\
    ( (This)->lpVtbl -> get_TopWidth(This,width) ) 

#define IPrestressedGirderSection_get_BottomWidth(This,width)	\
    ( (This)->lpVtbl -> get_BottomWidth(This,width) ) 

#define IPrestressedGirderSection_get_ShearWidth(This,shearwidth)	\
    ( (This)->lpVtbl -> get_ShearWidth(This,shearwidth) ) 

#define IPrestressedGirderSection_get_MinTopFlangeThickness(This,tf)	\
    ( (This)->lpVtbl -> get_MinTopFlangeThickness(This,tf) ) 

#define IPrestressedGirderSection_get_MinBottomFlangeThickness(This,tf)	\
    ( (This)->lpVtbl -> get_MinBottomFlangeThickness(This,tf) ) 

#define IPrestressedGirderSection_get_CL2ExteriorWebDistance(This,side,tf)	\
    ( (This)->lpVtbl -> get_CL2ExteriorWebDistance(This,side,tf) ) 


#define IPrestressedGirderSection_get_SplittingZoneDimension(This,pSZD)	\
    ( (This)->lpVtbl -> get_SplittingZoneDimension(This,pSZD) ) 

#define IPrestressedGirderSection_get_SplittingDirection(This,pSD)	\
    ( (This)->lpVtbl -> get_SplittingDirection(This,pSD) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPrestressedGirderSection_INTERFACE_DEFINED__ */


#ifndef __IMultiWebSection_INTERFACE_DEFINED__
#define __IMultiWebSection_INTERFACE_DEFINED__

/* interface IMultiWebSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IMultiWebSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F24B5CFF-67A5-4b88-9C1A-CE63A7846801")
    IMultiWebSection : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ IMultiWeb *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IMultiWeb **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMultiWebSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiWebSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiWebSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiWebSection * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            IMultiWebSection * This,
            /* [in] */ IMultiWeb *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IMultiWebSection * This,
            /* [retval][out] */ IMultiWeb **beam);
        
        END_INTERFACE
    } IMultiWebSectionVtbl;

    interface IMultiWebSection
    {
        CONST_VTBL struct IMultiWebSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiWebSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMultiWebSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMultiWebSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMultiWebSection_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define IMultiWebSection_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMultiWebSection_INTERFACE_DEFINED__ */


#ifndef __IMultiWebSection2_INTERFACE_DEFINED__
#define __IMultiWebSection2_INTERFACE_DEFINED__

/* interface IMultiWebSection2 */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IMultiWebSection2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("97DFD327-7863-4fe3-B106-A88AA1E29A70")
    IMultiWebSection2 : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ IMultiWeb2 *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IMultiWeb2 **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMultiWebSection2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiWebSection2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiWebSection2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiWebSection2 * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            IMultiWebSection2 * This,
            /* [in] */ IMultiWeb2 *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IMultiWebSection2 * This,
            /* [retval][out] */ IMultiWeb2 **beam);
        
        END_INTERFACE
    } IMultiWebSection2Vtbl;

    interface IMultiWebSection2
    {
        CONST_VTBL struct IMultiWebSection2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiWebSection2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMultiWebSection2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMultiWebSection2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMultiWebSection2_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define IMultiWebSection2_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMultiWebSection2_INTERFACE_DEFINED__ */


#ifndef __INUGirderSection_INTERFACE_DEFINED__
#define __INUGirderSection_INTERFACE_DEFINED__

/* interface INUGirderSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_INUGirderSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6CAF89B9-970C-4C71-97F5-D3F1D6BC09DA")
    INUGirderSection : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ INUBeam *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ INUBeam **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct INUGirderSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INUGirderSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INUGirderSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INUGirderSection * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            INUGirderSection * This,
            /* [in] */ INUBeam *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            INUGirderSection * This,
            /* [retval][out] */ INUBeam **beam);
        
        END_INTERFACE
    } INUGirderSectionVtbl;

    interface INUGirderSection
    {
        CONST_VTBL struct INUGirderSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INUGirderSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INUGirderSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INUGirderSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INUGirderSection_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define INUGirderSection_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INUGirderSection_INTERFACE_DEFINED__ */


#ifndef __IVoidedSlabSection_INTERFACE_DEFINED__
#define __IVoidedSlabSection_INTERFACE_DEFINED__

/* interface IVoidedSlabSection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVoidedSlabSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("903A90F2-628F-4251-B9EE-84A3519998D1")
    IVoidedSlabSection : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Beam( 
            /* [in] */ IVoidedSlab *beam) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IVoidedSlab **beam) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVoidedSlabSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVoidedSlabSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVoidedSlabSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVoidedSlabSection * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beam )( 
            IVoidedSlabSection * This,
            /* [in] */ IVoidedSlab *beam);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IVoidedSlabSection * This,
            /* [retval][out] */ IVoidedSlab **beam);
        
        END_INTERFACE
    } IVoidedSlabSectionVtbl;

    interface IVoidedSlabSection
    {
        CONST_VTBL struct IVoidedSlabSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoidedSlabSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVoidedSlabSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVoidedSlabSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVoidedSlabSection_put_Beam(This,beam)	\
    ( (This)->lpVtbl -> put_Beam(This,beam) ) 

#define IVoidedSlabSection_get_Beam(This,beam)	\
    ( (This)->lpVtbl -> get_Beam(This,beam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVoidedSlabSection_INTERFACE_DEFINED__ */


#ifndef __ITendonSegment_INTERFACE_DEFINED__
#define __ITendonSegment_INTERFACE_DEFINED__

/* interface ITendonSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITendonSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("41B8907E-C782-4aa9-993A-7C3AD4B2C5E6")
    ITendonSegment : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Start( 
            /* [retval][out] */ IPoint3d **start) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_End( 
            /* [retval][out] */ IPoint3d **end) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Position( 
            /* [in] */ TendonMeasure measure,
            /* [in] */ Float64 z,
            /* [retval][out] */ IPoint3d **cg) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Slope( 
            /* [in] */ Float64 z,
            /* [retval][out] */ IVector3d **slope) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ProjectedLength( 
            /* [out] */ Float64 *dx,
            /* [out] */ Float64 *dy,
            /* [out] */ Float64 *dz) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Centerline( 
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3dCollection **ppPoints) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MinimumRadiusOfCurvature( 
            /* [retval][out] */ Float64 *pMinRadiusOfCurvature) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Tendon( 
            /* [in] */ ITendon *pTendon) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tendon( 
            /* [retval][out] */ ITendon **ppTendon) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITendonSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITendonSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITendonSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITendonSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            ITendonSegment * This,
            /* [retval][out] */ IPoint3d **start);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_End )( 
            ITendonSegment * This,
            /* [retval][out] */ IPoint3d **end);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Position )( 
            ITendonSegment * This,
            /* [in] */ TendonMeasure measure,
            /* [in] */ Float64 z,
            /* [retval][out] */ IPoint3d **cg);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            ITendonSegment * This,
            /* [in] */ Float64 z,
            /* [retval][out] */ IVector3d **slope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ITendonSegment * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectedLength )( 
            ITendonSegment * This,
            /* [out] */ Float64 *dx,
            /* [out] */ Float64 *dy,
            /* [out] */ Float64 *dz);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Centerline )( 
            ITendonSegment * This,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinimumRadiusOfCurvature )( 
            ITendonSegment * This,
            /* [retval][out] */ Float64 *pMinRadiusOfCurvature);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Tendon )( 
            ITendonSegment * This,
            /* [in] */ ITendon *pTendon);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tendon )( 
            ITendonSegment * This,
            /* [retval][out] */ ITendon **ppTendon);
        
        END_INTERFACE
    } ITendonSegmentVtbl;

    interface ITendonSegment
    {
        CONST_VTBL struct ITendonSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITendonSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITendonSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITendonSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITendonSegment_get_Start(This,start)	\
    ( (This)->lpVtbl -> get_Start(This,start) ) 

#define ITendonSegment_get_End(This,end)	\
    ( (This)->lpVtbl -> get_End(This,end) ) 

#define ITendonSegment_get_Position(This,measure,z,cg)	\
    ( (This)->lpVtbl -> get_Position(This,measure,z,cg) ) 

#define ITendonSegment_get_Slope(This,z,slope)	\
    ( (This)->lpVtbl -> get_Slope(This,z,slope) ) 

#define ITendonSegment_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define ITendonSegment_ProjectedLength(This,dx,dy,dz)	\
    ( (This)->lpVtbl -> ProjectedLength(This,dx,dy,dz) ) 

#define ITendonSegment_get_Centerline(This,measure,ppPoints)	\
    ( (This)->lpVtbl -> get_Centerline(This,measure,ppPoints) ) 

#define ITendonSegment_get_MinimumRadiusOfCurvature(This,pMinRadiusOfCurvature)	\
    ( (This)->lpVtbl -> get_MinimumRadiusOfCurvature(This,pMinRadiusOfCurvature) ) 

#define ITendonSegment_putref_Tendon(This,pTendon)	\
    ( (This)->lpVtbl -> putref_Tendon(This,pTendon) ) 

#define ITendonSegment_get_Tendon(This,ppTendon)	\
    ( (This)->lpVtbl -> get_Tendon(This,ppTendon) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITendonSegment_INTERFACE_DEFINED__ */


#ifndef __ILinearTendonSegment_INTERFACE_DEFINED__
#define __ILinearTendonSegment_INTERFACE_DEFINED__

/* interface ILinearTendonSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILinearTendonSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3A46EA8-56D5-40c6-A21A-6617C1358977")
    ILinearTendonSegment : public ITendonSegment
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Start( 
            /* [in] */ IPoint3d *start) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_End( 
            /* [in] */ IPoint3d *end) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PrevTendonSegment( 
            /* [in] */ ITendonSegment *pTendonSegment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PrevTendonSegment( 
            /* [retval][out] */ ITendonSegment **ppTendonSegment) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_NextTendonSegment( 
            /* [in] */ ITendonSegment *pTendonSegment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NextTendonSegment( 
            /* [retval][out] */ ITendonSegment **ppTendonSegment) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILinearTendonSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILinearTendonSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILinearTendonSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILinearTendonSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            ILinearTendonSegment * This,
            /* [retval][out] */ IPoint3d **start);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_End )( 
            ILinearTendonSegment * This,
            /* [retval][out] */ IPoint3d **end);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Position )( 
            ILinearTendonSegment * This,
            /* [in] */ TendonMeasure measure,
            /* [in] */ Float64 z,
            /* [retval][out] */ IPoint3d **cg);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            ILinearTendonSegment * This,
            /* [in] */ Float64 z,
            /* [retval][out] */ IVector3d **slope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ILinearTendonSegment * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectedLength )( 
            ILinearTendonSegment * This,
            /* [out] */ Float64 *dx,
            /* [out] */ Float64 *dy,
            /* [out] */ Float64 *dz);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Centerline )( 
            ILinearTendonSegment * This,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinimumRadiusOfCurvature )( 
            ILinearTendonSegment * This,
            /* [retval][out] */ Float64 *pMinRadiusOfCurvature);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Tendon )( 
            ILinearTendonSegment * This,
            /* [in] */ ITendon *pTendon);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tendon )( 
            ILinearTendonSegment * This,
            /* [retval][out] */ ITendon **ppTendon);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Start )( 
            ILinearTendonSegment * This,
            /* [in] */ IPoint3d *start);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_End )( 
            ILinearTendonSegment * This,
            /* [in] */ IPoint3d *end);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PrevTendonSegment )( 
            ILinearTendonSegment * This,
            /* [in] */ ITendonSegment *pTendonSegment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevTendonSegment )( 
            ILinearTendonSegment * This,
            /* [retval][out] */ ITendonSegment **ppTendonSegment);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NextTendonSegment )( 
            ILinearTendonSegment * This,
            /* [in] */ ITendonSegment *pTendonSegment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextTendonSegment )( 
            ILinearTendonSegment * This,
            /* [retval][out] */ ITendonSegment **ppTendonSegment);
        
        END_INTERFACE
    } ILinearTendonSegmentVtbl;

    interface ILinearTendonSegment
    {
        CONST_VTBL struct ILinearTendonSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILinearTendonSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILinearTendonSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILinearTendonSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILinearTendonSegment_get_Start(This,start)	\
    ( (This)->lpVtbl -> get_Start(This,start) ) 

#define ILinearTendonSegment_get_End(This,end)	\
    ( (This)->lpVtbl -> get_End(This,end) ) 

#define ILinearTendonSegment_get_Position(This,measure,z,cg)	\
    ( (This)->lpVtbl -> get_Position(This,measure,z,cg) ) 

#define ILinearTendonSegment_get_Slope(This,z,slope)	\
    ( (This)->lpVtbl -> get_Slope(This,z,slope) ) 

#define ILinearTendonSegment_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define ILinearTendonSegment_ProjectedLength(This,dx,dy,dz)	\
    ( (This)->lpVtbl -> ProjectedLength(This,dx,dy,dz) ) 

#define ILinearTendonSegment_get_Centerline(This,measure,ppPoints)	\
    ( (This)->lpVtbl -> get_Centerline(This,measure,ppPoints) ) 

#define ILinearTendonSegment_get_MinimumRadiusOfCurvature(This,pMinRadiusOfCurvature)	\
    ( (This)->lpVtbl -> get_MinimumRadiusOfCurvature(This,pMinRadiusOfCurvature) ) 

#define ILinearTendonSegment_putref_Tendon(This,pTendon)	\
    ( (This)->lpVtbl -> putref_Tendon(This,pTendon) ) 

#define ILinearTendonSegment_get_Tendon(This,ppTendon)	\
    ( (This)->lpVtbl -> get_Tendon(This,ppTendon) ) 


#define ILinearTendonSegment_put_Start(This,start)	\
    ( (This)->lpVtbl -> put_Start(This,start) ) 

#define ILinearTendonSegment_put_End(This,end)	\
    ( (This)->lpVtbl -> put_End(This,end) ) 

#define ILinearTendonSegment_putref_PrevTendonSegment(This,pTendonSegment)	\
    ( (This)->lpVtbl -> putref_PrevTendonSegment(This,pTendonSegment) ) 

#define ILinearTendonSegment_get_PrevTendonSegment(This,ppTendonSegment)	\
    ( (This)->lpVtbl -> get_PrevTendonSegment(This,ppTendonSegment) ) 

#define ILinearTendonSegment_putref_NextTendonSegment(This,pTendonSegment)	\
    ( (This)->lpVtbl -> putref_NextTendonSegment(This,pTendonSegment) ) 

#define ILinearTendonSegment_get_NextTendonSegment(This,ppTendonSegment)	\
    ( (This)->lpVtbl -> get_NextTendonSegment(This,ppTendonSegment) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILinearTendonSegment_INTERFACE_DEFINED__ */


#ifndef __IParabolicTendonSegment_INTERFACE_DEFINED__
#define __IParabolicTendonSegment_INTERFACE_DEFINED__

/* interface IParabolicTendonSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IParabolicTendonSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("83E0B7FE-6DE0-4b7f-ABF9-C4949771701A")
    IParabolicTendonSegment : public ITendonSegment
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Start( 
            /* [in] */ IPoint3d *start) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_End( 
            /* [in] */ IPoint3d *end) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Slope( 
            /* [in] */ Float64 slope) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Slope( 
            /* [retval][out] */ Float64 *slope) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SlopeEnd( 
            /* [in] */ DirectionType end) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SlopeEnd( 
            /* [retval][out] */ DirectionType *end) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IParabolicTendonSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IParabolicTendonSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IParabolicTendonSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IParabolicTendonSegment * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            IParabolicTendonSegment * This,
            /* [retval][out] */ IPoint3d **start);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_End )( 
            IParabolicTendonSegment * This,
            /* [retval][out] */ IPoint3d **end);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Position )( 
            IParabolicTendonSegment * This,
            /* [in] */ TendonMeasure measure,
            /* [in] */ Float64 z,
            /* [retval][out] */ IPoint3d **cg);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            IParabolicTendonSegment * This,
            /* [in] */ Float64 z,
            /* [retval][out] */ IVector3d **slope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IParabolicTendonSegment * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectedLength )( 
            IParabolicTendonSegment * This,
            /* [out] */ Float64 *dx,
            /* [out] */ Float64 *dy,
            /* [out] */ Float64 *dz);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Centerline )( 
            IParabolicTendonSegment * This,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinimumRadiusOfCurvature )( 
            IParabolicTendonSegment * This,
            /* [retval][out] */ Float64 *pMinRadiusOfCurvature);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Tendon )( 
            IParabolicTendonSegment * This,
            /* [in] */ ITendon *pTendon);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tendon )( 
            IParabolicTendonSegment * This,
            /* [retval][out] */ ITendon **ppTendon);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Start )( 
            IParabolicTendonSegment * This,
            /* [in] */ IPoint3d *start);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_End )( 
            IParabolicTendonSegment * This,
            /* [in] */ IPoint3d *end);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slope )( 
            IParabolicTendonSegment * This,
            /* [in] */ Float64 slope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            IParabolicTendonSegment * This,
            /* [retval][out] */ Float64 *slope);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SlopeEnd )( 
            IParabolicTendonSegment * This,
            /* [in] */ DirectionType end);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SlopeEnd )( 
            IParabolicTendonSegment * This,
            /* [retval][out] */ DirectionType *end);
        
        END_INTERFACE
    } IParabolicTendonSegmentVtbl;

    interface IParabolicTendonSegment
    {
        CONST_VTBL struct IParabolicTendonSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParabolicTendonSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IParabolicTendonSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IParabolicTendonSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IParabolicTendonSegment_get_Start(This,start)	\
    ( (This)->lpVtbl -> get_Start(This,start) ) 

#define IParabolicTendonSegment_get_End(This,end)	\
    ( (This)->lpVtbl -> get_End(This,end) ) 

#define IParabolicTendonSegment_get_Position(This,measure,z,cg)	\
    ( (This)->lpVtbl -> get_Position(This,measure,z,cg) ) 

#define IParabolicTendonSegment_get_Slope(This,z,slope)	\
    ( (This)->lpVtbl -> get_Slope(This,z,slope) ) 

#define IParabolicTendonSegment_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define IParabolicTendonSegment_ProjectedLength(This,dx,dy,dz)	\
    ( (This)->lpVtbl -> ProjectedLength(This,dx,dy,dz) ) 

#define IParabolicTendonSegment_get_Centerline(This,measure,ppPoints)	\
    ( (This)->lpVtbl -> get_Centerline(This,measure,ppPoints) ) 

#define IParabolicTendonSegment_get_MinimumRadiusOfCurvature(This,pMinRadiusOfCurvature)	\
    ( (This)->lpVtbl -> get_MinimumRadiusOfCurvature(This,pMinRadiusOfCurvature) ) 

#define IParabolicTendonSegment_putref_Tendon(This,pTendon)	\
    ( (This)->lpVtbl -> putref_Tendon(This,pTendon) ) 

#define IParabolicTendonSegment_get_Tendon(This,ppTendon)	\
    ( (This)->lpVtbl -> get_Tendon(This,ppTendon) ) 


#define IParabolicTendonSegment_put_Start(This,start)	\
    ( (This)->lpVtbl -> put_Start(This,start) ) 

#define IParabolicTendonSegment_put_End(This,end)	\
    ( (This)->lpVtbl -> put_End(This,end) ) 

#define IParabolicTendonSegment_put_Slope(This,slope)	\
    ( (This)->lpVtbl -> put_Slope(This,slope) ) 

#define IParabolicTendonSegment_get_Slope(This,slope)	\
    ( (This)->lpVtbl -> get_Slope(This,slope) ) 

#define IParabolicTendonSegment_put_SlopeEnd(This,end)	\
    ( (This)->lpVtbl -> put_SlopeEnd(This,end) ) 

#define IParabolicTendonSegment_get_SlopeEnd(This,end)	\
    ( (This)->lpVtbl -> get_SlopeEnd(This,end) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IParabolicTendonSegment_INTERFACE_DEFINED__ */


#ifndef __IOffsetTendon_INTERFACE_DEFINED__
#define __IOffsetTendon_INTERFACE_DEFINED__

/* interface IOffsetTendon */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IOffsetTendon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B8C5E222-2F3E-4dd3-8B3F-B264341F75E2")
    IOffsetTendon : public ITendon
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_RefTendon( 
            /* [in] */ ITendon *tendon) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddOffset( 
            /* [in] */ Float64 z,
            /* [in] */ Float64 offsetX,
            /* [in] */ Float64 offsetY) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IOffsetTendonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOffsetTendon * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOffsetTendon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOffsetTendon * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSegment )( 
            IOffsetTendon * This,
            /* [in] */ ITendonSegment *segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Segment )( 
            IOffsetTendon * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ITendonSegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IOffsetTendon * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveSegment )( 
            IOffsetTendon * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearSegments )( 
            IOffsetTendon * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JackingEnd )( 
            IOffsetTendon * This,
            /* [retval][out] */ JackingEndType *type);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_JackingEnd )( 
            IOffsetTendon * This,
            /* [in] */ JackingEndType type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutsideDiameter )( 
            IOffsetTendon * This,
            /* [retval][out] */ Float64 *size);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutsideDiameter )( 
            IOffsetTendon * This,
            /* [in] */ Float64 size);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InsideDiameter )( 
            IOffsetTendon * This,
            /* [retval][out] */ Float64 *size);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InsideDiameter )( 
            IOffsetTendon * This,
            /* [in] */ Float64 size);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandCount )( 
            IOffsetTendon * This,
            /* [retval][out] */ StrandIndexType *count);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StrandCount )( 
            IOffsetTendon * This,
            /* [in] */ StrandIndexType count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Material )( 
            IOffsetTendon * This,
            /* [retval][out] */ IPrestressingStrand **material);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Material )( 
            IOffsetTendon * This,
            /* [in] */ IPrestressingStrand *material);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InsideDuctArea )( 
            IOffsetTendon * This,
            /* [retval][out] */ Float64 *Apt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TendonArea )( 
            IOffsetTendon * This,
            /* [retval][out] */ Float64 *Apt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinimumRadiusOfCurvature )( 
            IOffsetTendon * This,
            /* [retval][out] */ Float64 *pMinRadiusOfCurvature);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CG )( 
            IOffsetTendon * This,
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3d **cg);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            IOffsetTendon * This,
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IVector3d **slope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IOffsetTendon * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            IOffsetTendon * This,
            /* [retval][out] */ IPoint3d **start);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_End )( 
            IOffsetTendon * This,
            /* [retval][out] */ IPoint3d **end);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Centerline )( 
            IOffsetTendon * This,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3dCollection **ppPoints);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SuperstructureMember )( 
            IOffsetTendon * This,
            /* [in] */ ISuperstructureMember *pMbr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMember )( 
            IOffsetTendon * This,
            /* [retval][out] */ ISuperstructureMember **ppMbr);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RefTendon )( 
            IOffsetTendon * This,
            /* [in] */ ITendon *tendon);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddOffset )( 
            IOffsetTendon * This,
            /* [in] */ Float64 z,
            /* [in] */ Float64 offsetX,
            /* [in] */ Float64 offsetY);
        
        END_INTERFACE
    } IOffsetTendonVtbl;

    interface IOffsetTendon
    {
        CONST_VTBL struct IOffsetTendonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOffsetTendon_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOffsetTendon_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOffsetTendon_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOffsetTendon_AddSegment(This,segment)	\
    ( (This)->lpVtbl -> AddSegment(This,segment) ) 

#define IOffsetTendon_get_Segment(This,index,segment)	\
    ( (This)->lpVtbl -> get_Segment(This,index,segment) ) 

#define IOffsetTendon_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IOffsetTendon_RemoveSegment(This,index)	\
    ( (This)->lpVtbl -> RemoveSegment(This,index) ) 

#define IOffsetTendon_ClearSegments(This)	\
    ( (This)->lpVtbl -> ClearSegments(This) ) 

#define IOffsetTendon_get_JackingEnd(This,type)	\
    ( (This)->lpVtbl -> get_JackingEnd(This,type) ) 

#define IOffsetTendon_put_JackingEnd(This,type)	\
    ( (This)->lpVtbl -> put_JackingEnd(This,type) ) 

#define IOffsetTendon_get_OutsideDiameter(This,size)	\
    ( (This)->lpVtbl -> get_OutsideDiameter(This,size) ) 

#define IOffsetTendon_put_OutsideDiameter(This,size)	\
    ( (This)->lpVtbl -> put_OutsideDiameter(This,size) ) 

#define IOffsetTendon_get_InsideDiameter(This,size)	\
    ( (This)->lpVtbl -> get_InsideDiameter(This,size) ) 

#define IOffsetTendon_put_InsideDiameter(This,size)	\
    ( (This)->lpVtbl -> put_InsideDiameter(This,size) ) 

#define IOffsetTendon_get_StrandCount(This,count)	\
    ( (This)->lpVtbl -> get_StrandCount(This,count) ) 

#define IOffsetTendon_put_StrandCount(This,count)	\
    ( (This)->lpVtbl -> put_StrandCount(This,count) ) 

#define IOffsetTendon_get_Material(This,material)	\
    ( (This)->lpVtbl -> get_Material(This,material) ) 

#define IOffsetTendon_putref_Material(This,material)	\
    ( (This)->lpVtbl -> putref_Material(This,material) ) 

#define IOffsetTendon_get_InsideDuctArea(This,Apt)	\
    ( (This)->lpVtbl -> get_InsideDuctArea(This,Apt) ) 

#define IOffsetTendon_get_TendonArea(This,Apt)	\
    ( (This)->lpVtbl -> get_TendonArea(This,Apt) ) 

#define IOffsetTendon_get_MinimumRadiusOfCurvature(This,pMinRadiusOfCurvature)	\
    ( (This)->lpVtbl -> get_MinimumRadiusOfCurvature(This,pMinRadiusOfCurvature) ) 

#define IOffsetTendon_get_CG(This,z,measure,cg)	\
    ( (This)->lpVtbl -> get_CG(This,z,measure,cg) ) 

#define IOffsetTendon_get_Slope(This,z,measure,slope)	\
    ( (This)->lpVtbl -> get_Slope(This,z,measure,slope) ) 

#define IOffsetTendon_get_Length(This,length)	\
    ( (This)->lpVtbl -> get_Length(This,length) ) 

#define IOffsetTendon_get_Start(This,start)	\
    ( (This)->lpVtbl -> get_Start(This,start) ) 

#define IOffsetTendon_get_End(This,end)	\
    ( (This)->lpVtbl -> get_End(This,end) ) 

#define IOffsetTendon_get_Centerline(This,measure,ppPoints)	\
    ( (This)->lpVtbl -> get_Centerline(This,measure,ppPoints) ) 

#define IOffsetTendon_putref_SuperstructureMember(This,pMbr)	\
    ( (This)->lpVtbl -> putref_SuperstructureMember(This,pMbr) ) 

#define IOffsetTendon_get_SuperstructureMember(This,ppMbr)	\
    ( (This)->lpVtbl -> get_SuperstructureMember(This,ppMbr) ) 


#define IOffsetTendon_putref_RefTendon(This,tendon)	\
    ( (This)->lpVtbl -> putref_RefTendon(This,tendon) ) 

#define IOffsetTendon_AddOffset(This,z,offsetX,offsetY)	\
    ( (This)->lpVtbl -> AddOffset(This,z,offsetX,offsetY) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOffsetTendon_INTERFACE_DEFINED__ */


#ifndef __IEnumTendonSegments_INTERFACE_DEFINED__
#define __IEnumTendonSegments_INTERFACE_DEFINED__

/* interface IEnumTendonSegments */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumTendonSegments;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("14299B76-FF0E-4271-897E-9D24F691BA0B")
    IEnumTendonSegments : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumTendonSegments **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ITendonSegment **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumTendonSegmentsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumTendonSegments * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumTendonSegments * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumTendonSegments * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumTendonSegments * This,
            /* [out] */ IEnumTendonSegments **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumTendonSegments * This,
            /* [in] */ ULONG celt,
            /* [out] */ ITendonSegment **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumTendonSegments * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumTendonSegments * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumTendonSegmentsVtbl;

    interface IEnumTendonSegments
    {
        CONST_VTBL struct IEnumTendonSegmentsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumTendonSegments_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumTendonSegments_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumTendonSegments_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumTendonSegments_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumTendonSegments_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumTendonSegments_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumTendonSegments_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumTendonSegments_INTERFACE_DEFINED__ */


#ifndef __IEnumTendons_INTERFACE_DEFINED__
#define __IEnumTendons_INTERFACE_DEFINED__

/* interface IEnumTendons */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumTendons;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0A5A7839-29B3-484b-B507-4D8F07EC3A32")
    IEnumTendons : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumTendons **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ITendon **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumTendonsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumTendons * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumTendons * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumTendons * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumTendons * This,
            /* [out] */ IEnumTendons **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumTendons * This,
            /* [in] */ ULONG celt,
            /* [out] */ ITendon **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumTendons * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumTendons * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumTendonsVtbl;

    interface IEnumTendons
    {
        CONST_VTBL struct IEnumTendonsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumTendons_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumTendons_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumTendons_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumTendons_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumTendons_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumTendons_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumTendons_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumTendons_INTERFACE_DEFINED__ */


#ifndef __ITendonCollection_INTERFACE_DEFINED__
#define __ITendonCollection_INTERFACE_DEFINED__

/* interface ITendonCollection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITendonCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32F8A1B7-A82F-43bb-97BB-33D3C0CE236E")
    ITendonCollection : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ITendon *tendon) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ DuctIndexType index,
            /* [retval][out] */ ITendon **tendon) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ DuctIndexType index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ DuctIndexType *nTendons) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CG( 
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3d **cg) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Slope( 
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IVector3d **slope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Cut( 
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3dCollection **points) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumTendons( 
            /* [retval][out] */ IEnumTendons **enumTendons) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITendonCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITendonCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITendonCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITendonCollection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITendonCollection * This,
            /* [in] */ ITendon *tendon);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITendonCollection * This,
            /* [in] */ DuctIndexType index,
            /* [retval][out] */ ITendon **tendon);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITendonCollection * This,
            /* [in] */ DuctIndexType index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ITendonCollection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITendonCollection * This,
            /* [retval][out] */ DuctIndexType *nTendons);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CG )( 
            ITendonCollection * This,
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3d **cg);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            ITendonCollection * This,
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IVector3d **slope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Cut )( 
            ITendonCollection * This,
            /* [in] */ Float64 z,
            /* [in] */ TendonMeasure measure,
            /* [retval][out] */ IPoint3dCollection **points);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumTendons )( 
            ITendonCollection * This,
            /* [retval][out] */ IEnumTendons **enumTendons);
        
        END_INTERFACE
    } ITendonCollectionVtbl;

    interface ITendonCollection
    {
        CONST_VTBL struct ITendonCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITendonCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITendonCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITendonCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITendonCollection_Add(This,tendon)	\
    ( (This)->lpVtbl -> Add(This,tendon) ) 

#define ITendonCollection_get_Item(This,index,tendon)	\
    ( (This)->lpVtbl -> get_Item(This,index,tendon) ) 

#define ITendonCollection_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define ITendonCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ITendonCollection_get_Count(This,nTendons)	\
    ( (This)->lpVtbl -> get_Count(This,nTendons) ) 

#define ITendonCollection_get_CG(This,z,measure,cg)	\
    ( (This)->lpVtbl -> get_CG(This,z,measure,cg) ) 

#define ITendonCollection_get_Slope(This,z,measure,slope)	\
    ( (This)->lpVtbl -> get_Slope(This,z,measure,slope) ) 

#define ITendonCollection_Cut(This,z,measure,points)	\
    ( (This)->lpVtbl -> Cut(This,z,measure,points) ) 

#define ITendonCollection_get__EnumTendons(This,enumTendons)	\
    ( (This)->lpVtbl -> get__EnumTendons(This,enumTendons) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITendonCollection_INTERFACE_DEFINED__ */


#ifndef __IEnumPiers_INTERFACE_DEFINED__
#define __IEnumPiers_INTERFACE_DEFINED__

/* interface IEnumPiers */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumPiers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AA989D6D-AFA1-4c54-B44A-E7D33832CC38")
    IEnumPiers : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPiers **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IBridgePier **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumPiersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPiers * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPiers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPiers * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPiers * This,
            /* [out] */ IEnumPiers **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPiers * This,
            /* [in] */ ULONG celt,
            /* [out] */ IBridgePier **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPiers * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPiers * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumPiersVtbl;

    interface IEnumPiers
    {
        CONST_VTBL struct IEnumPiersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPiers_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumPiers_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumPiers_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumPiers_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumPiers_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumPiers_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumPiers_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumPiers_INTERFACE_DEFINED__ */


#ifndef __IPierCollection_INTERFACE_DEFINED__
#define __IPierCollection_INTERFACE_DEFINED__

/* interface IPierCollection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPierCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A2D7C5BB-764E-44c4-A599-A8A74D1ED734")
    IPierCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ PierIndexType index,
            /* [retval][out] */ IBridgePier **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ PierIndexType *count) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PierIndex( 
            /* [in] */ IBridgePier *pier,
            /* [retval][out] */ PierIndexType *index) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumPiers( 
            /* [retval][out] */ IEnumPiers **enumPiers) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindPier( 
            /* [in] */ Float64 station,
            /* [retval][out] */ IBridgePier **ppPier) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPierCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPierCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPierCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPierCollection * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IPierCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPierCollection * This,
            /* [in] */ PierIndexType index,
            /* [retval][out] */ IBridgePier **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPierCollection * This,
            /* [retval][out] */ PierIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PierIndex )( 
            IPierCollection * This,
            /* [in] */ IBridgePier *pier,
            /* [retval][out] */ PierIndexType *index);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumPiers )( 
            IPierCollection * This,
            /* [retval][out] */ IEnumPiers **enumPiers);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindPier )( 
            IPierCollection * This,
            /* [in] */ Float64 station,
            /* [retval][out] */ IBridgePier **ppPier);
        
        END_INTERFACE
    } IPierCollectionVtbl;

    interface IPierCollection
    {
        CONST_VTBL struct IPierCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPierCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPierCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPierCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPierCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IPierCollection_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IPierCollection_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IPierCollection_get_PierIndex(This,pier,index)	\
    ( (This)->lpVtbl -> get_PierIndex(This,pier,index) ) 

#define IPierCollection_get__EnumPiers(This,enumPiers)	\
    ( (This)->lpVtbl -> get__EnumPiers(This,enumPiers) ) 

#define IPierCollection_FindPier(This,station,ppPier)	\
    ( (This)->lpVtbl -> FindPier(This,station,ppPier) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPierCollection_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Rebar;

#ifdef __cplusplus

class DECLSPEC_UUID("E01789C1-EC18-4c75-B42A-8DDB495C7326")
Rebar;
#endif

EXTERN_C const CLSID CLSID_RebarSectionItem;

#ifdef __cplusplus

class DECLSPEC_UUID("ED89484D-303E-452a-8165-8A6666200BAC")
RebarSectionItem;
#endif

EXTERN_C const CLSID CLSID_RebarSection;

#ifdef __cplusplus

class DECLSPEC_UUID("3D0BCC3C-1A32-44c5-A97E-55BD12DC62F1")
RebarSection;
#endif

EXTERN_C const CLSID CLSID_RebarRowFacePattern;

#ifdef __cplusplus

class DECLSPEC_UUID("0FBA0FAD-AF0B-4969-84DF-BA49A7D352B6")
RebarRowFacePattern;
#endif

EXTERN_C const CLSID CLSID_RebarRowPattern;

#ifdef __cplusplus

class DECLSPEC_UUID("5F9006C8-B6A7-488e-88BB-24304ED93E4D")
RebarRowPattern;
#endif

EXTERN_C const CLSID CLSID_CrossBeamRebarPattern;

#ifdef __cplusplus

class DECLSPEC_UUID("9E669BF9-FE19-4e06-85C9-8307AE1BEE68")
CrossBeamRebarPattern;
#endif

EXTERN_C const CLSID CLSID_RebarLayout;

#ifdef __cplusplus

class DECLSPEC_UUID("33813283-3F28-4291-AE33-AAD126881A38")
RebarLayout;
#endif

EXTERN_C const CLSID CLSID_FixedLengthRebarLayoutItem;

#ifdef __cplusplus

class DECLSPEC_UUID("BBAE8AB6-5822-47CA-8ECD-0C2AFF18FC0B")
FixedLengthRebarLayoutItem;
#endif

EXTERN_C const CLSID CLSID_BridgeDeckRebarPattern;

#ifdef __cplusplus

class DECLSPEC_UUID("1EAAA1BF-51A0-4a07-8C7A-90A9E42863E6")
BridgeDeckRebarPattern;
#endif

EXTERN_C const CLSID CLSID_BridgeDeckRebarLayoutItem;

#ifdef __cplusplus

class DECLSPEC_UUID("148BBC9B-3E74-462b-B90A-4CF617F92264")
BridgeDeckRebarLayoutItem;
#endif

EXTERN_C const CLSID CLSID_NegativeMomentBridgeDeckRebarLayoutItem;

#ifdef __cplusplus

class DECLSPEC_UUID("BBCE715B-3F02-4859-AA8B-81B9ED11826D")
NegativeMomentBridgeDeckRebarLayoutItem;
#endif

EXTERN_C const CLSID CLSID_RebarFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("867B7B93-BFF7-4879-980C-B1A2DC8C5DCC")
RebarFactory;
#endif

EXTERN_C const CLSID CLSID_GenericBridge;

#ifdef __cplusplus

class DECLSPEC_UUID("C228C58A-EE9A-45DE-BF6C-EC2ABD8C9219")
GenericBridge;
#endif

EXTERN_C const CLSID CLSID_BridgePier;

#ifdef __cplusplus

class DECLSPEC_UUID("72098BAA-D991-4ac1-94AD-B3B932E7EB54")
BridgePier;
#endif

EXTERN_C const CLSID CLSID_PierCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("2C363589-02D0-4391-A76F-932FCC891068")
PierCollection;
#endif

EXTERN_C const CLSID CLSID_SuperstructureMember;

#ifdef __cplusplus

class DECLSPEC_UUID("B1875476-2706-4d53-A5CC-27AA77B11E2A")
SuperstructureMember;
#endif

EXTERN_C const CLSID CLSID_FlangedGirderEndBlockSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("2E00BE46-658E-4431-A47A-A380DE4C1A93")
FlangedGirderEndBlockSegment;
#endif

EXTERN_C const CLSID CLSID_VoidedSlabEndBlockSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("BA0DCAF5-3500-421d-B1E5-2DBDF048A454")
VoidedSlabEndBlockSegment;
#endif

EXTERN_C const CLSID CLSID_DeckedSlabBeamEndBlockSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("F952F1A6-7FDD-4c6c-96BE-891E500390EF")
DeckedSlabBeamEndBlockSegment;
#endif

EXTERN_C const CLSID CLSID_BoxBeamEndBlockSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("B0E705F3-5B54-43e4-B869-222C77B2BD28")
BoxBeamEndBlockSegment;
#endif

EXTERN_C const CLSID CLSID_UGirderSection2EndBlockSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("E5E3C9E4-909B-47eb-8B40-E1279A1FE65E")
UGirderSection2EndBlockSegment;
#endif

EXTERN_C const CLSID CLSID_TaperedGirderSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("432FB365-C5D0-46b0-9DCD-65F21A91580F")
TaperedGirderSegment;
#endif

EXTERN_C const CLSID CLSID_ThickenedFlangeBulbTeeSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("7F93F993-02C8-451b-95DE-F0122E95E06C")
ThickenedFlangeBulbTeeSegment;
#endif

EXTERN_C const CLSID CLSID_PrismaticSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("5AC7585F-2AE5-4b15-9416-7FEA7A53CD03")
PrismaticSegment;
#endif

EXTERN_C const CLSID CLSID_PrismaticSuperstructureMemberSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("391BFF16-7930-4fcc-B35F-B7BBFBF345A4")
PrismaticSuperstructureMemberSegment;
#endif

EXTERN_C const CLSID CLSID_FlangedSplicedGirderSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("D3DF465C-E03B-4192-A17E-2DF7BE63CAFB")
FlangedSplicedGirderSegment;
#endif

EXTERN_C const CLSID CLSID_USplicedGirderSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("9DDC341B-E17F-4d54-9A33-F2C4F052650A")
USplicedGirderSegment;
#endif

EXTERN_C const CLSID CLSID_NUSplicedGirderSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("464D04E4-0A0D-4295-A8B3-F276EB49CBE3")
NUSplicedGirderSegment;
#endif

EXTERN_C const CLSID CLSID_SegmentItem;

#ifdef __cplusplus

class DECLSPEC_UUID("A81D7FA1-41CF-4980-AC98-F0CC555AA181")
SegmentItem;
#endif

EXTERN_C const CLSID CLSID_FilteredSegmentCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("9217644C-AD9D-4aa2-9A76-29DE6D8CE8B3")
FilteredSegmentCollection;
#endif

EXTERN_C const CLSID CLSID_SuperstructureMemberCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("627E1C31-A568-406e-8583-7887AD068D0B")
SuperstructureMemberCollection;
#endif

EXTERN_C const CLSID CLSID_Column;

#ifdef __cplusplus

class DECLSPEC_UUID("CB50DBAC-CF8D-4204-B581-9C8A7705EEB2")
Column;
#endif

EXTERN_C const CLSID CLSID_ColumnLayout;

#ifdef __cplusplus

class DECLSPEC_UUID("7AE3C6CE-8DB2-467E-8F5A-395B39582325")
ColumnLayout;
#endif

EXTERN_C const CLSID CLSID_BearingLayout;

#ifdef __cplusplus

class DECLSPEC_UUID("C86CAC8A-4986-4234-8E44-7C77561BCD6B")
BearingLayout;
#endif

EXTERN_C const CLSID CLSID_LinearCrossBeam;

#ifdef __cplusplus

class DECLSPEC_UUID("0ABE6940-BC27-4E91-8FF0-5A1CD2243153")
LinearCrossBeam;
#endif

EXTERN_C const CLSID CLSID_Pier;

#ifdef __cplusplus

class DECLSPEC_UUID("6AF46A10-C19E-438F-B69D-8AB743748CED")
Pier;
#endif

EXTERN_C const CLSID CLSID_Material;

#ifdef __cplusplus

class DECLSPEC_UUID("D3894F80-C95C-4a8b-A839-EAB39D92F196")
Material;
#endif

EXTERN_C const CLSID CLSID_CastSlab;

#ifdef __cplusplus

class DECLSPEC_UUID("994EBFE4-E2CE-4932-B58D-D0661ED9DE1A")
CastSlab;
#endif

EXTERN_C const CLSID CLSID_AlignmentOffsetStrategy;

#ifdef __cplusplus

class DECLSPEC_UUID("DE317A5D-4C21-4216-BB98-45A1AFAFD8DF")
AlignmentOffsetStrategy;
#endif

EXTERN_C const CLSID CLSID_EdgePathStrategy;

#ifdef __cplusplus

class DECLSPEC_UUID("2EDDEA3E-D428-472f-AC4A-3BE464B74ED7")
EdgePathStrategy;
#endif

EXTERN_C const CLSID CLSID_PrecastSlab;

#ifdef __cplusplus

class DECLSPEC_UUID("1CDE4F4B-59FA-4326-8BA6-7F9410DB31E9")
PrecastSlab;
#endif

EXTERN_C const CLSID CLSID_OverlaySlab;

#ifdef __cplusplus

class DECLSPEC_UUID("B7DDD2C1-B544-4bd0-91DA-40E7C3A2A9BC")
OverlaySlab;
#endif

EXTERN_C const CLSID CLSID_FlangedGirderSection;

#ifdef __cplusplus

class DECLSPEC_UUID("17B94525-BDF5-4036-8EA5-EE6D0C1DDBED")
FlangedGirderSection;
#endif

EXTERN_C const CLSID CLSID_BulbTeeSection;

#ifdef __cplusplus

class DECLSPEC_UUID("90F25ADA-74B8-4171-80CA-A445519885AC")
BulbTeeSection;
#endif

EXTERN_C const CLSID CLSID_MultiWebSection;

#ifdef __cplusplus

class DECLSPEC_UUID("D48BAC9D-876F-47ed-8B11-058009337492")
MultiWebSection;
#endif

EXTERN_C const CLSID CLSID_MultiWebSection2;

#ifdef __cplusplus

class DECLSPEC_UUID("E72B28B7-A74F-4245-AC74-015B7FB5B719")
MultiWebSection2;
#endif

EXTERN_C const CLSID CLSID_NUGirderSection;

#ifdef __cplusplus

class DECLSPEC_UUID("5CD0487E-041E-4ADE-973D-0B6AE4472478")
NUGirderSection;
#endif

EXTERN_C const CLSID CLSID_UGirderSection;

#ifdef __cplusplus

class DECLSPEC_UUID("A9D10C18-7AEA-4846-8165-DE3460B1BEAD")
UGirderSection;
#endif

EXTERN_C const CLSID CLSID_UGirderSection2;

#ifdef __cplusplus

class DECLSPEC_UUID("E8A71ACA-0C4E-495c-AC84-2E26C114A410")
UGirderSection2;
#endif

EXTERN_C const CLSID CLSID_VoidedSlabSection;

#ifdef __cplusplus

class DECLSPEC_UUID("C11EBF7B-A6AA-44b9-9642-E408300AC702")
VoidedSlabSection;
#endif

EXTERN_C const CLSID CLSID_VoidedSlabSection2;

#ifdef __cplusplus

class DECLSPEC_UUID("23E0A018-EB42-46d0-82EB-28811AF57C5B")
VoidedSlabSection2;
#endif

EXTERN_C const CLSID CLSID_DeckedSlabBeamSection;

#ifdef __cplusplus

class DECLSPEC_UUID("DED3DC73-280E-4fd2-8C1D-BCE96BB78750")
DeckedSlabBeamSection;
#endif

EXTERN_C const CLSID CLSID_BoxBeamSection;

#ifdef __cplusplus

class DECLSPEC_UUID("D6CB0FE7-AD6E-449f-91C7-6A4CDEEA5F70")
BoxBeamSection;
#endif

EXTERN_C const CLSID CLSID_GenericBarrier;

#ifdef __cplusplus

class DECLSPEC_UUID("9B910467-C7CE-4b56-B2C8-0CD47B73FBC2")
GenericBarrier;
#endif

EXTERN_C const CLSID CLSID_FShapeBarrier;

#ifdef __cplusplus

class DECLSPEC_UUID("0386B8E1-50E2-42bd-A93B-C2933F9BD1C0")
FShapeBarrier;
#endif

EXTERN_C const CLSID CLSID_SidewalkBarrier;

#ifdef __cplusplus

class DECLSPEC_UUID("8B5D872B-21C3-41f4-BFFB-A79E58CB9AC8")
SidewalkBarrier;
#endif

EXTERN_C const CLSID CLSID_LinearTendonSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("C1F73F53-6D63-44be-953F-3254EBB4F91A")
LinearTendonSegment;
#endif

EXTERN_C const CLSID CLSID_ParabolicTendonSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("99F3888C-7581-4fe6-BBB5-9D527CD8BEB6")
ParabolicTendonSegment;
#endif

EXTERN_C const CLSID CLSID_Tendon;

#ifdef __cplusplus

class DECLSPEC_UUID("68AF9D7E-A0B7-4174-8304-37E595725480")
Tendon;
#endif

EXTERN_C const CLSID CLSID_OffsetTendon;

#ifdef __cplusplus

class DECLSPEC_UUID("C4064D20-D146-48dd-8B89-685CAC219EAB")
OffsetTendon;
#endif

EXTERN_C const CLSID CLSID_TendonCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("505D6372-B76F-4d91-9013-E71E3D17C4F6")
TendonCollection;
#endif

EXTERN_C const CLSID CLSID_PrestressingStrand;

#ifdef __cplusplus

class DECLSPEC_UUID("9AC4752D-388F-4536-ABB6-B13933322915")
PrestressingStrand;
#endif
#endif /* __WBFLGenericBridge_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


