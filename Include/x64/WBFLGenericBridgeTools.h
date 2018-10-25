

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Oct 30 08:13:01 2017
 */
/* Compiler settings for ..\Include\WBFLGenericBridgeTools.idl:
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


#ifndef __WBFLGenericBridgeTools_h__
#define __WBFLGenericBridgeTools_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPrecastGirder_FWD_DEFINED__
#define __IPrecastGirder_FWD_DEFINED__
typedef interface IPrecastGirder IPrecastGirder;

#endif 	/* __IPrecastGirder_FWD_DEFINED__ */


#ifndef __IFlexRebarLayoutItem_FWD_DEFINED__
#define __IFlexRebarLayoutItem_FWD_DEFINED__
typedef interface IFlexRebarLayoutItem IFlexRebarLayoutItem;

#endif 	/* __IFlexRebarLayoutItem_FWD_DEFINED__ */


#ifndef __ISectionCutTool_FWD_DEFINED__
#define __ISectionCutTool_FWD_DEFINED__
typedef interface ISectionCutTool ISectionCutTool;

#endif 	/* __ISectionCutTool_FWD_DEFINED__ */


#ifndef __IStrandMover_FWD_DEFINED__
#define __IStrandMover_FWD_DEFINED__
typedef interface IStrandMover IStrandMover;

#endif 	/* __IStrandMover_FWD_DEFINED__ */


#ifndef __IStrandGrid_FWD_DEFINED__
#define __IStrandGrid_FWD_DEFINED__
typedef interface IStrandGrid IStrandGrid;

#endif 	/* __IStrandGrid_FWD_DEFINED__ */


#ifndef __IStrandGridFiller_FWD_DEFINED__
#define __IStrandGridFiller_FWD_DEFINED__
typedef interface IStrandGridFiller IStrandGridFiller;

#endif 	/* __IStrandGridFiller_FWD_DEFINED__ */


#ifndef __IStrandFillTool_FWD_DEFINED__
#define __IStrandFillTool_FWD_DEFINED__
typedef interface IStrandFillTool IStrandFillTool;

#endif 	/* __IStrandFillTool_FWD_DEFINED__ */


#ifndef __IBridgeGeometryTool_FWD_DEFINED__
#define __IBridgeGeometryTool_FWD_DEFINED__
typedef interface IBridgeGeometryTool IBridgeGeometryTool;

#endif 	/* __IBridgeGeometryTool_FWD_DEFINED__ */


#ifndef __FlexRebarLayoutItem_FWD_DEFINED__
#define __FlexRebarLayoutItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class FlexRebarLayoutItem FlexRebarLayoutItem;
#else
typedef struct FlexRebarLayoutItem FlexRebarLayoutItem;
#endif /* __cplusplus */

#endif 	/* __FlexRebarLayoutItem_FWD_DEFINED__ */


#ifndef __EffectiveFlangeWidthDetails_FWD_DEFINED__
#define __EffectiveFlangeWidthDetails_FWD_DEFINED__

#ifdef __cplusplus
typedef class EffectiveFlangeWidthDetails EffectiveFlangeWidthDetails;
#else
typedef struct EffectiveFlangeWidthDetails EffectiveFlangeWidthDetails;
#endif /* __cplusplus */

#endif 	/* __EffectiveFlangeWidthDetails_FWD_DEFINED__ */


#ifndef __EffectiveFlangeWidthTool_FWD_DEFINED__
#define __EffectiveFlangeWidthTool_FWD_DEFINED__

#ifdef __cplusplus
typedef class EffectiveFlangeWidthTool EffectiveFlangeWidthTool;
#else
typedef struct EffectiveFlangeWidthTool EffectiveFlangeWidthTool;
#endif /* __cplusplus */

#endif 	/* __EffectiveFlangeWidthTool_FWD_DEFINED__ */


#ifndef __SectionCutTool_FWD_DEFINED__
#define __SectionCutTool_FWD_DEFINED__

#ifdef __cplusplus
typedef class SectionCutTool SectionCutTool;
#else
typedef struct SectionCutTool SectionCutTool;
#endif /* __cplusplus */

#endif 	/* __SectionCutTool_FWD_DEFINED__ */


#ifndef __PrecastGirder_FWD_DEFINED__
#define __PrecastGirder_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrecastGirder PrecastGirder;
#else
typedef struct PrecastGirder PrecastGirder;
#endif /* __cplusplus */

#endif 	/* __PrecastGirder_FWD_DEFINED__ */


#ifndef __BridgeGeometryTool_FWD_DEFINED__
#define __BridgeGeometryTool_FWD_DEFINED__

#ifdef __cplusplus
typedef class BridgeGeometryTool BridgeGeometryTool;
#else
typedef struct BridgeGeometryTool BridgeGeometryTool;
#endif /* __cplusplus */

#endif 	/* __BridgeGeometryTool_FWD_DEFINED__ */


#ifndef __StrandGrid_FWD_DEFINED__
#define __StrandGrid_FWD_DEFINED__

#ifdef __cplusplus
typedef class StrandGrid StrandGrid;
#else
typedef struct StrandGrid StrandGrid;
#endif /* __cplusplus */

#endif 	/* __StrandGrid_FWD_DEFINED__ */


#ifndef __StrandFillTool_FWD_DEFINED__
#define __StrandFillTool_FWD_DEFINED__

#ifdef __cplusplus
typedef class StrandFillTool StrandFillTool;
#else
typedef struct StrandFillTool StrandFillTool;
#endif /* __cplusplus */

#endif 	/* __StrandFillTool_FWD_DEFINED__ */


#ifndef __BridgeDeckRebarLayout_FWD_DEFINED__
#define __BridgeDeckRebarLayout_FWD_DEFINED__

#ifdef __cplusplus
typedef class BridgeDeckRebarLayout BridgeDeckRebarLayout;
#else
typedef struct BridgeDeckRebarLayout BridgeDeckRebarLayout;
#endif /* __cplusplus */

#endif 	/* __BridgeDeckRebarLayout_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"
#include "WBFLUnitServer.h"
#include "WBFLGeometry.h"
#include "WBFLSections.h"
#include "WBFLCogo.h"
#include "WBFLBridgeGeometry.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLGenericBridgeTools_0000_0000 */
/* [local] */ 

#include <WBFLGenericBridge.h>
#define GBMT_E_UNKNOWNDECKTYPE             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,512)
#define GBMT_E_GIRDERSECTION               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,513)
#define GBMT_E_NODECK                      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,514)
#define GBMT_E_COMPOSITEDECK               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,515)
#define GBMT_E_MATERIAL                    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,516)
#define GBMT_E_SHAPE                       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,517)
#define GBMT_E_REMOVEDEBOND                MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,518)


extern RPC_IF_HANDLE __MIDL_itf_WBFLGenericBridgeTools_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLGenericBridgeTools_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLGenericBridgeTools_LIBRARY_DEFINED__
#define __WBFLGenericBridgeTools_LIBRARY_DEFINED__

/* library WBFLGenericBridgeTools */
/* [helpstring][version][uuid] */ 


typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("9246CAAE-3CAD-401f-BB00-0DA5EFA41EE2") 
enum __MIDL___MIDL_itf_WBFLGenericBridgeTools_0000_0000_0001
    {
        lpLeft	= 0,
        lpCenter	= ( lpLeft + 1 ) ,
        lpRight	= ( lpCenter + 1 ) 
    } 	LayoutPosition;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("B7DC993C-340A-4fb0-A058-6286F9C890B7") 
enum __MIDL___MIDL_itf_WBFLGenericBridgeTools_0000_0000_0002
    {
        spmGrossNoncomposite	= 0,
        spmGross	= ( spmGrossNoncomposite + 1 ) ,
        spmTransformedNoncomposite	= ( spmGross + 1 ) ,
        spmTransformed	= ( spmTransformedNoncomposite + 1 ) ,
        spmNet	= ( spmTransformed + 1 ) 
    } 	SectionPropertyMethod;

typedef /* [public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("9744FFFE-8025-422e-A4C3-9A58B48DD102") 
enum __MIDL___MIDL_itf_WBFLGenericBridgeTools_0000_0000_0003
    {
        hprEndOfGirder	= 0,
        hprBearing	= 1,
        hprCenterOfGirder	= 2
    } 	HarpPointReference;

typedef /* [public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("97051264-41BA-4691-9C4E-CDE659BB2C5A") 
enum __MIDL___MIDL_itf_WBFLGenericBridgeTools_0000_0000_0004
    {
        hpmFractionOfSpanLength	= 0,
        hpmFractionOfGirderLength	= 1,
        hpmAbsoluteDistance	= 2
    } 	HarpPointMeasure;

typedef /* [public][public][uuid][helpstring][public] */  DECLSPEC_UUID("B87307A0-81D1-41e5-A115-E1CAB0E39A43") 
enum __MIDL___MIDL_itf_WBFLGenericBridgeTools_0000_0000_0005
    {
        bscNone	= 0,
        bscStructurallyContinuousOnly	= ( bscNone + 1 ) ,
        bscAll	= ( bscStructurallyContinuousOnly + 1 ) 
    } 	BarrierSectionCut;

typedef /* [public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("F35F63C1-32EA-4de6-B6D8-1F3A5E9863A4") 
enum __MIDL___MIDL_itf_WBFLGenericBridgeTools_0000_0000_0006
    {
        sgtEnd	= 0,
        sgtHarpPoint	= ( sgtEnd + 1 ) 
    } 	StrandGridType;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("56213312-6399-4417-A8F0-1B933056D00E") 
enum __MIDL___MIDL_itf_WBFLGenericBridgeTools_0000_0000_0007
    {
        wdblEither	= 0,
        wdblLeft	= ( wdblEither + 1 ) ,
        wdblRight	= ( wdblLeft + 1 ) 
    } 	WDebondLocationType;


EXTERN_C const IID LIBID_WBFLGenericBridgeTools;

#ifndef __IPrecastGirder_INTERFACE_DEFINED__
#define __IPrecastGirder_INTERFACE_DEFINED__

/* interface IPrecastGirder */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IPrecastGirder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("231B2534-7714-459c-A2CE-A2195474A2C2")
    IPrecastGirder : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ /* external definition not present */ ISuperstructureMemberSegment *segment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetStrandMovers( 
            /* [in] */ IStrandMover *pStartStrandMover,
            /* [in] */ IStrandMover *pHp1StrandMover,
            /* [in] */ IStrandMover *pHp2StrandMover,
            /* [in] */ IStrandMover *pEndStrandMover) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_StrandMover( 
            /* [in] */ StrandGridType sgType,
            /* [in] */ EndType endType,
            /* [in] */ IStrandMover *pStrandMover) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StrandMover( 
            /* [in] */ StrandGridType sgType,
            /* [in] */ EndType endType,
            /* [retval][out] */ IStrandMover **ppStrandMover) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_StraightStrandMaterial( 
            /* [in] */ /* external definition not present */ IPrestressingStrand *pMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StraightStrandMaterial( 
            /* [retval][out] */ /* external definition not present */ IPrestressingStrand **ppMaterial) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HarpedStrandMaterial( 
            /* [in] */ /* external definition not present */ IPrestressingStrand *pMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedStrandMaterial( 
            /* [retval][out] */ /* external definition not present */ IPrestressingStrand **ppMaterial) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_TemporaryStrandMaterial( 
            /* [in] */ /* external definition not present */ IPrestressingStrand *pMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TemporaryStrandMaterial( 
            /* [retval][out] */ /* external definition not present */ IPrestressingStrand **ppMaterial) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StraightStrandGrid( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IStrandGrid **ptrn) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TemporaryStrandGrid( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IStrandGrid **ptrn) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedStrandGridEnd( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IStrandGrid **ptrn) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedStrandGridHP( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IStrandGrid **ptrn) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AllowOddNumberOfHarpedStrands( 
            /* [in] */ VARIANT_BOOL bUseMin) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AllowOddNumberOfHarpedStrands( 
            /* [retval][out] */ VARIANT_BOOL *bUseMin) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_UseDifferentHarpedGridsAtEnds( 
            /* [in] */ VARIANT_BOOL bUseDifferent) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UseDifferentHarpedGridsAtEnds( 
            /* [retval][out] */ VARIANT_BOOL *bUseDifferent) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedEndAdjustmentIncrement( 
            /* [retval][out] */ Float64 *increment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedHpAdjustmentIncrement( 
            /* [retval][out] */ Float64 *increment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopElevation( 
            /* [retval][out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedStrandAdjustmentEnd( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HarpedStrandAdjustmentEnd( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedStrandAdjustmentHP( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HarpedStrandAdjustmentHP( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetHarpingPoints( 
            /* [in] */ Float64 hp1,
            /* [in] */ Float64 hp2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHarpingPoints( 
            /* [out] */ Float64 *hp1,
            /* [out] */ Float64 *hp2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetEndHarpingPoints( 
            /* [in] */ Float64 hp1,
            /* [in] */ Float64 hp2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEndHarpingPoints( 
            /* [out] */ Float64 *hp1,
            /* [out] */ Float64 *hp2) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_UseMinHarpPointDistance( 
            /* [in] */ VARIANT_BOOL bUseMin) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UseMinHarpPointDistance( 
            /* [retval][out] */ VARIANT_BOOL *bUseMin) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MinHarpPointDistance( 
            /* [in] */ Float64 minHpDist) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MinHarpPointDistance( 
            /* [retval][out] */ Float64 *minHpDist) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HarpingPointMeasure( 
            /* [in] */ HarpPointMeasure measure) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpingPointMeasure( 
            /* [retval][out] */ HarpPointMeasure *measure) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndHarpingPointMeasure( 
            /* [in] */ HarpPointMeasure measure) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndHarpingPointMeasure( 
            /* [retval][out] */ HarpPointMeasure *measure) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HarpingPointReference( 
            /* [in] */ HarpPointReference hpRef) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpingPointReference( 
            /* [retval][out] */ HarpPointReference *hpRef) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndHarpingPointReference( 
            /* [in] */ HarpPointReference hpRef) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndHarpingPointReference( 
            /* [retval][out] */ HarpPointReference *hpRef) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHarpingPointLocations( 
            /* [out] */ Float64 *hp1,
            /* [out] */ Float64 *hp2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEndHarpingPointLocations( 
            /* [out] */ Float64 *hp1,
            /* [out] */ Float64 *hp2) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SpanLength( 
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GirderLength( 
            /* [retval][out] */ Float64 *length) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftEndDistance( 
            /* [retval][out] */ Float64 *size) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightEndDistance( 
            /* [retval][out] */ Float64 *size) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftBearingOffset( 
            /* [retval][out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightBearingOffset( 
            /* [retval][out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEndPoints( 
            /* [out] */ IPoint2d **pntPier1,
            /* [out] */ IPoint2d **pntEnd1,
            /* [out] */ IPoint2d **pntBrg1,
            /* [out] */ IPoint2d **pntBrg2,
            /* [out] */ IPoint2d **pntEnd2,
            /* [out] */ IPoint2d **pntPier2) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StraightMaxStrandFill( 
            /* [retval][out] */ IIndexArray **fill) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedMaxStrandFill( 
            /* [retval][out] */ IIndexArray **fill) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TemporaryMaxStrandFill( 
            /* [retval][out] */ IIndexArray **fill) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StraightStrandFill( 
            /* [retval][out] */ IIndexArray **fill) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_StraightStrandFill( 
            /* [in] */ IIndexArray *fill) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedStrandFill( 
            /* [retval][out] */ IIndexArray **fill) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HarpedStrandFill( 
            /* [in] */ IIndexArray *fill) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TemporaryStrandFill( 
            /* [retval][out] */ IIndexArray **fill) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_TemporaryStrandFill( 
            /* [in] */ IIndexArray *fill) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StraightStrandPositions( 
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StraightStrandPositionsEx( 
            /* [in] */ Float64 distFromStart,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedStrandPositions( 
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedStrandPositionsEx( 
            /* [in] */ Float64 distFromStart,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TemporaryStrandPositions( 
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TemporaryStrandPositionsEx( 
            /* [in] */ Float64 distFromStart,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StraightStrandIndexToGridIndex( 
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StraightStrandIndexToGridIndexEx( 
            /* [in] */ IIndexArray *fill,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HarpedStrandIndexToGridIndex( 
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HarpedStrandIndexToGridIndexEx( 
            /* [in] */ IIndexArray *fill,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TemporaryStrandIndexToGridIndex( 
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TemporaryStrandIndexToGridIndexEx( 
            /* [in] */ IIndexArray *fill,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StraightStrandBoundingBox( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IRect2d **box) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StraightStrandBoundingBoxEx( 
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IRect2d **box) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HarpedEndStrandBoundingBox( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IRect2d **box) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HarpedEndStrandBoundingBoxEx( 
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IRect2d **box) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HarpedHpStrandBoundingBox( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IRect2d **box) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HarpedHpStrandBoundingBoxEx( 
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IRect2d **box) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HarpedEndStrandBoundaryCheck( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *adjustment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HarpedHpStrandBoundaryCheck( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *adjustment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHarpedEndAdjustmentBounds( 
            /* [in] */ EndType endType,
            /* [out] */ Float64 *DownwardAdjustment,
            /* [out] */ Float64 *UpwardAdjustment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHarpedEndAdjustmentBoundsEx( 
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *DownwardAdjustment,
            /* [out] */ Float64 *UpwardAdjustment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHarpedHpAdjustmentBounds( 
            /* [in] */ EndType endType,
            /* [out] */ Float64 *DownwardAdjustment,
            /* [out] */ Float64 *UpwardAdjustment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHarpedHpAdjustmentBoundsEx( 
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *DownwardAdjustment,
            /* [out] */ Float64 *UpwardAdjustment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHarpedEndFilledGridBoundsEx( 
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *bottomElev,
            /* [out] */ Float64 *topElev) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHarpedHpFilledGridBoundsEx( 
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *bottomElev,
            /* [out] */ Float64 *topElev) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ComputeMaxHarpedStrandSlope( 
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ Float64 *slope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ComputeMaxHarpedStrandSlopeEx( 
            /* [in] */ Float64 distFromStart,
            /* [in] */ IIndexArray *fill,
            /* [in] */ Float64 startOffset,
            /* [in] */ Float64 hp1Offset,
            /* [in] */ Float64 hp2Offset,
            /* [in] */ Float64 endOffset,
            /* [retval][out] */ Float64 *slope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ComputeAvgHarpedStrandSlope( 
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ Float64 *slope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ComputeAvgHarpedStrandSlopeEx( 
            /* [in] */ Float64 distFromStart,
            /* [in] */ IIndexArray *fill,
            /* [in] */ Float64 startOffset,
            /* [in] */ Float64 hp1Offset,
            /* [in] */ Float64 hp2Offset,
            /* [in] */ Float64 endOffset,
            /* [retval][out] */ Float64 *slope) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxStraightStrands( 
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxHarpedStrands( 
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxTemporaryStrands( 
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandCount( 
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHarpedStrandCount( 
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTemporaryStrandCount( 
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandCountEx( 
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHarpedStrandCountEx( 
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTemporaryStrandCountEx( 
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandDebondCount( 
            /* [in] */ WDebondLocationType loc,
            /* [retval][out] */ StrandIndexType *count) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearStraightStrandDebonding( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DebondStraightStrandByGridIndex( 
            /* [in] */ GridIndexType grdIndex,
            /* [in] */ Float64 l1,
            /* [in] */ Float64 l2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDebondedStraightStrandsByGridIndex( 
            /* [retval][out] */ IIndexArray **grdIndexes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandDebondLengthByGridIndex( 
            /* [in] */ EndType endType,
            /* [in] */ GridIndexType grdIndex,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *l1,
            /* [out] */ Float64 *l2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandDebondLengthByPositionIndex( 
            /* [in] */ EndType endType,
            /* [in] */ StrandIndexType positionIndex,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *l1,
            /* [out] */ Float64 *l2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandsDebondedByPositionIndex( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ IIndexArray **positionIndexes) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StraightStrandRowsWithStrand( 
            /* [retval][out] */ RowIndexType *nRows) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StraightStrandsInRow( 
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ IIndexArray **gridIndexes) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumStraightStrandsInRow( 
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StraightStrandDebondInRow( 
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsExteriorStraightStrandDebondedInRow( 
            /* [in] */ RowIndexType rowIndex,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedStrandRowsWithStrand( 
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ RowIndexType *nRows) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HarpedStrandsInRow( 
            /* [in] */ Float64 distFromStart,
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ IIndexArray **gridIndexes) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumHarpedStrandsInRow( 
            /* [in] */ Float64 distFromStart,
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandDebondAtSections( 
            /* [out] */ IDblArray **arrLeft,
            /* [out] */ IDblArray **arrRight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandDebondAtLeftSection( 
            /* [in] */ SectionIndexType sectionIdx,
            /* [retval][out] */ IIndexArray **pstnIndexes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandDebondAtRightSection( 
            /* [in] */ SectionIndexType sectionIdx,
            /* [retval][out] */ IIndexArray **pstnIndexes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandBondedLengthByPositionIndex( 
            /* [in] */ StrandIndexType positionIndex,
            /* [in] */ Float64 distFromStart,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *leftBond,
            /* [out] */ Float64 *rightBond) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStraightStrandBondedLengthByGridIndex( 
            /* [in] */ GridIndexType grdIndex,
            /* [in] */ Float64 distFromStart,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *leftBond,
            /* [out] */ Float64 *rightBond) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SuperstructureMemberSegment( 
            /* [retval][out] */ /* external definition not present */ ISuperstructureMemberSegment **segment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayout( 
            /* [retval][out] */ /* external definition not present */ IRebarLayout **rebarLayout) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClosureJointRebarLayout( 
            /* [retval][out] */ /* external definition not present */ IRebarLayout **rebarLayout) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPrecastGirderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPrecastGirder * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPrecastGirder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPrecastGirder * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IPrecastGirder * This,
            /* [in] */ /* external definition not present */ ISuperstructureMemberSegment *segment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetStrandMovers )( 
            IPrecastGirder * This,
            /* [in] */ IStrandMover *pStartStrandMover,
            /* [in] */ IStrandMover *pHp1StrandMover,
            /* [in] */ IStrandMover *pHp2StrandMover,
            /* [in] */ IStrandMover *pEndStrandMover);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StrandMover )( 
            IPrecastGirder * This,
            /* [in] */ StrandGridType sgType,
            /* [in] */ EndType endType,
            /* [in] */ IStrandMover *pStrandMover);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandMover )( 
            IPrecastGirder * This,
            /* [in] */ StrandGridType sgType,
            /* [in] */ EndType endType,
            /* [retval][out] */ IStrandMover **ppStrandMover);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StraightStrandMaterial )( 
            IPrecastGirder * This,
            /* [in] */ /* external definition not present */ IPrestressingStrand *pMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StraightStrandMaterial )( 
            IPrecastGirder * This,
            /* [retval][out] */ /* external definition not present */ IPrestressingStrand **ppMaterial);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HarpedStrandMaterial )( 
            IPrecastGirder * This,
            /* [in] */ /* external definition not present */ IPrestressingStrand *pMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedStrandMaterial )( 
            IPrecastGirder * This,
            /* [retval][out] */ /* external definition not present */ IPrestressingStrand **ppMaterial);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_TemporaryStrandMaterial )( 
            IPrecastGirder * This,
            /* [in] */ /* external definition not present */ IPrestressingStrand *pMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TemporaryStrandMaterial )( 
            IPrecastGirder * This,
            /* [retval][out] */ /* external definition not present */ IPrestressingStrand **ppMaterial);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StraightStrandGrid )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IStrandGrid **ptrn);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TemporaryStrandGrid )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IStrandGrid **ptrn);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedStrandGridEnd )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IStrandGrid **ptrn);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedStrandGridHP )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IStrandGrid **ptrn);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AllowOddNumberOfHarpedStrands )( 
            IPrecastGirder * This,
            /* [in] */ VARIANT_BOOL bUseMin);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AllowOddNumberOfHarpedStrands )( 
            IPrecastGirder * This,
            /* [retval][out] */ VARIANT_BOOL *bUseMin);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseDifferentHarpedGridsAtEnds )( 
            IPrecastGirder * This,
            /* [in] */ VARIANT_BOOL bUseDifferent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseDifferentHarpedGridsAtEnds )( 
            IPrecastGirder * This,
            /* [retval][out] */ VARIANT_BOOL *bUseDifferent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedEndAdjustmentIncrement )( 
            IPrecastGirder * This,
            /* [retval][out] */ Float64 *increment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedHpAdjustmentIncrement )( 
            IPrecastGirder * This,
            /* [retval][out] */ Float64 *increment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopElevation )( 
            IPrecastGirder * This,
            /* [retval][out] */ Float64 *offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedStrandAdjustmentEnd )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *offset);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HarpedStrandAdjustmentEnd )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedStrandAdjustmentHP )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *offset);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HarpedStrandAdjustmentHP )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 offset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetHarpingPoints )( 
            IPrecastGirder * This,
            /* [in] */ Float64 hp1,
            /* [in] */ Float64 hp2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHarpingPoints )( 
            IPrecastGirder * This,
            /* [out] */ Float64 *hp1,
            /* [out] */ Float64 *hp2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEndHarpingPoints )( 
            IPrecastGirder * This,
            /* [in] */ Float64 hp1,
            /* [in] */ Float64 hp2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEndHarpingPoints )( 
            IPrecastGirder * This,
            /* [out] */ Float64 *hp1,
            /* [out] */ Float64 *hp2);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseMinHarpPointDistance )( 
            IPrecastGirder * This,
            /* [in] */ VARIANT_BOOL bUseMin);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseMinHarpPointDistance )( 
            IPrecastGirder * This,
            /* [retval][out] */ VARIANT_BOOL *bUseMin);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinHarpPointDistance )( 
            IPrecastGirder * This,
            /* [in] */ Float64 minHpDist);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinHarpPointDistance )( 
            IPrecastGirder * This,
            /* [retval][out] */ Float64 *minHpDist);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HarpingPointMeasure )( 
            IPrecastGirder * This,
            /* [in] */ HarpPointMeasure measure);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpingPointMeasure )( 
            IPrecastGirder * This,
            /* [retval][out] */ HarpPointMeasure *measure);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndHarpingPointMeasure )( 
            IPrecastGirder * This,
            /* [in] */ HarpPointMeasure measure);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndHarpingPointMeasure )( 
            IPrecastGirder * This,
            /* [retval][out] */ HarpPointMeasure *measure);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HarpingPointReference )( 
            IPrecastGirder * This,
            /* [in] */ HarpPointReference hpRef);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpingPointReference )( 
            IPrecastGirder * This,
            /* [retval][out] */ HarpPointReference *hpRef);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndHarpingPointReference )( 
            IPrecastGirder * This,
            /* [in] */ HarpPointReference hpRef);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndHarpingPointReference )( 
            IPrecastGirder * This,
            /* [retval][out] */ HarpPointReference *hpRef);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHarpingPointLocations )( 
            IPrecastGirder * This,
            /* [out] */ Float64 *hp1,
            /* [out] */ Float64 *hp2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEndHarpingPointLocations )( 
            IPrecastGirder * This,
            /* [out] */ Float64 *hp1,
            /* [out] */ Float64 *hp2);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpanLength )( 
            IPrecastGirder * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLength )( 
            IPrecastGirder * This,
            /* [retval][out] */ Float64 *length);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftEndDistance )( 
            IPrecastGirder * This,
            /* [retval][out] */ Float64 *size);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightEndDistance )( 
            IPrecastGirder * This,
            /* [retval][out] */ Float64 *size);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftBearingOffset )( 
            IPrecastGirder * This,
            /* [retval][out] */ Float64 *offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightBearingOffset )( 
            IPrecastGirder * This,
            /* [retval][out] */ Float64 *offset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEndPoints )( 
            IPrecastGirder * This,
            /* [out] */ IPoint2d **pntPier1,
            /* [out] */ IPoint2d **pntEnd1,
            /* [out] */ IPoint2d **pntBrg1,
            /* [out] */ IPoint2d **pntBrg2,
            /* [out] */ IPoint2d **pntEnd2,
            /* [out] */ IPoint2d **pntPier2);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StraightMaxStrandFill )( 
            IPrecastGirder * This,
            /* [retval][out] */ IIndexArray **fill);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedMaxStrandFill )( 
            IPrecastGirder * This,
            /* [retval][out] */ IIndexArray **fill);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TemporaryMaxStrandFill )( 
            IPrecastGirder * This,
            /* [retval][out] */ IIndexArray **fill);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StraightStrandFill )( 
            IPrecastGirder * This,
            /* [retval][out] */ IIndexArray **fill);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StraightStrandFill )( 
            IPrecastGirder * This,
            /* [in] */ IIndexArray *fill);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedStrandFill )( 
            IPrecastGirder * This,
            /* [retval][out] */ IIndexArray **fill);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HarpedStrandFill )( 
            IPrecastGirder * This,
            /* [in] */ IIndexArray *fill);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TemporaryStrandFill )( 
            IPrecastGirder * This,
            /* [retval][out] */ IIndexArray **fill);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_TemporaryStrandFill )( 
            IPrecastGirder * This,
            /* [in] */ IIndexArray *fill);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StraightStrandPositions )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StraightStrandPositionsEx )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedStrandPositions )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedStrandPositionsEx )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TemporaryStrandPositions )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TemporaryStrandPositionsEx )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StraightStrandIndexToGridIndex )( 
            IPrecastGirder * This,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StraightStrandIndexToGridIndexEx )( 
            IPrecastGirder * This,
            /* [in] */ IIndexArray *fill,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HarpedStrandIndexToGridIndex )( 
            IPrecastGirder * This,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HarpedStrandIndexToGridIndexEx )( 
            IPrecastGirder * This,
            /* [in] */ IIndexArray *fill,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TemporaryStrandIndexToGridIndex )( 
            IPrecastGirder * This,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TemporaryStrandIndexToGridIndexEx )( 
            IPrecastGirder * This,
            /* [in] */ IIndexArray *fill,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StraightStrandBoundingBox )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IRect2d **box);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StraightStrandBoundingBoxEx )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IRect2d **box);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HarpedEndStrandBoundingBox )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IRect2d **box);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HarpedEndStrandBoundingBoxEx )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IRect2d **box);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HarpedHpStrandBoundingBox )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IRect2d **box);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HarpedHpStrandBoundingBoxEx )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IRect2d **box);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HarpedEndStrandBoundaryCheck )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *adjustment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HarpedHpStrandBoundaryCheck )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *adjustment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHarpedEndAdjustmentBounds )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [out] */ Float64 *DownwardAdjustment,
            /* [out] */ Float64 *UpwardAdjustment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHarpedEndAdjustmentBoundsEx )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *DownwardAdjustment,
            /* [out] */ Float64 *UpwardAdjustment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHarpedHpAdjustmentBounds )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [out] */ Float64 *DownwardAdjustment,
            /* [out] */ Float64 *UpwardAdjustment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHarpedHpAdjustmentBoundsEx )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *DownwardAdjustment,
            /* [out] */ Float64 *UpwardAdjustment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHarpedEndFilledGridBoundsEx )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *bottomElev,
            /* [out] */ Float64 *topElev);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHarpedHpFilledGridBoundsEx )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *bottomElev,
            /* [out] */ Float64 *topElev);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeMaxHarpedStrandSlope )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ Float64 *slope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeMaxHarpedStrandSlopeEx )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [in] */ IIndexArray *fill,
            /* [in] */ Float64 startOffset,
            /* [in] */ Float64 hp1Offset,
            /* [in] */ Float64 hp2Offset,
            /* [in] */ Float64 endOffset,
            /* [retval][out] */ Float64 *slope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeAvgHarpedStrandSlope )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ Float64 *slope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeAvgHarpedStrandSlopeEx )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [in] */ IIndexArray *fill,
            /* [in] */ Float64 startOffset,
            /* [in] */ Float64 hp1Offset,
            /* [in] */ Float64 hp2Offset,
            /* [in] */ Float64 endOffset,
            /* [retval][out] */ Float64 *slope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxStraightStrands )( 
            IPrecastGirder * This,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxHarpedStrands )( 
            IPrecastGirder * This,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxTemporaryStrands )( 
            IPrecastGirder * This,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandCount )( 
            IPrecastGirder * This,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHarpedStrandCount )( 
            IPrecastGirder * This,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTemporaryStrandCount )( 
            IPrecastGirder * This,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandCountEx )( 
            IPrecastGirder * This,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHarpedStrandCountEx )( 
            IPrecastGirder * This,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTemporaryStrandCountEx )( 
            IPrecastGirder * This,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandDebondCount )( 
            IPrecastGirder * This,
            /* [in] */ WDebondLocationType loc,
            /* [retval][out] */ StrandIndexType *count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearStraightStrandDebonding )( 
            IPrecastGirder * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DebondStraightStrandByGridIndex )( 
            IPrecastGirder * This,
            /* [in] */ GridIndexType grdIndex,
            /* [in] */ Float64 l1,
            /* [in] */ Float64 l2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDebondedStraightStrandsByGridIndex )( 
            IPrecastGirder * This,
            /* [retval][out] */ IIndexArray **grdIndexes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandDebondLengthByGridIndex )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ GridIndexType grdIndex,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *l1,
            /* [out] */ Float64 *l2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandDebondLengthByPositionIndex )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ StrandIndexType positionIndex,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *l1,
            /* [out] */ Float64 *l2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandsDebondedByPositionIndex )( 
            IPrecastGirder * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ IIndexArray **positionIndexes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StraightStrandRowsWithStrand )( 
            IPrecastGirder * This,
            /* [retval][out] */ RowIndexType *nRows);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StraightStrandsInRow )( 
            IPrecastGirder * This,
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ IIndexArray **gridIndexes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumStraightStrandsInRow )( 
            IPrecastGirder * This,
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StraightStrandDebondInRow )( 
            IPrecastGirder * This,
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsExteriorStraightStrandDebondedInRow )( 
            IPrecastGirder * This,
            /* [in] */ RowIndexType rowIndex,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedStrandRowsWithStrand )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [retval][out] */ RowIndexType *nRows);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HarpedStrandsInRow )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ IIndexArray **gridIndexes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumHarpedStrandsInRow )( 
            IPrecastGirder * This,
            /* [in] */ Float64 distFromStart,
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandDebondAtSections )( 
            IPrecastGirder * This,
            /* [out] */ IDblArray **arrLeft,
            /* [out] */ IDblArray **arrRight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandDebondAtLeftSection )( 
            IPrecastGirder * This,
            /* [in] */ SectionIndexType sectionIdx,
            /* [retval][out] */ IIndexArray **pstnIndexes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandDebondAtRightSection )( 
            IPrecastGirder * This,
            /* [in] */ SectionIndexType sectionIdx,
            /* [retval][out] */ IIndexArray **pstnIndexes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandBondedLengthByPositionIndex )( 
            IPrecastGirder * This,
            /* [in] */ StrandIndexType positionIndex,
            /* [in] */ Float64 distFromStart,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *leftBond,
            /* [out] */ Float64 *rightBond);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStraightStrandBondedLengthByGridIndex )( 
            IPrecastGirder * This,
            /* [in] */ GridIndexType grdIndex,
            /* [in] */ Float64 distFromStart,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *leftBond,
            /* [out] */ Float64 *rightBond);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMemberSegment )( 
            IPrecastGirder * This,
            /* [retval][out] */ /* external definition not present */ ISuperstructureMemberSegment **segment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayout )( 
            IPrecastGirder * This,
            /* [retval][out] */ /* external definition not present */ IRebarLayout **rebarLayout);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClosureJointRebarLayout )( 
            IPrecastGirder * This,
            /* [retval][out] */ /* external definition not present */ IRebarLayout **rebarLayout);
        
        END_INTERFACE
    } IPrecastGirderVtbl;

    interface IPrecastGirder
    {
        CONST_VTBL struct IPrecastGirderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrecastGirder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPrecastGirder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPrecastGirder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPrecastGirder_Initialize(This,segment)	\
    ( (This)->lpVtbl -> Initialize(This,segment) ) 

#define IPrecastGirder_SetStrandMovers(This,pStartStrandMover,pHp1StrandMover,pHp2StrandMover,pEndStrandMover)	\
    ( (This)->lpVtbl -> SetStrandMovers(This,pStartStrandMover,pHp1StrandMover,pHp2StrandMover,pEndStrandMover) ) 

#define IPrecastGirder_putref_StrandMover(This,sgType,endType,pStrandMover)	\
    ( (This)->lpVtbl -> putref_StrandMover(This,sgType,endType,pStrandMover) ) 

#define IPrecastGirder_get_StrandMover(This,sgType,endType,ppStrandMover)	\
    ( (This)->lpVtbl -> get_StrandMover(This,sgType,endType,ppStrandMover) ) 

#define IPrecastGirder_putref_StraightStrandMaterial(This,pMaterial)	\
    ( (This)->lpVtbl -> putref_StraightStrandMaterial(This,pMaterial) ) 

#define IPrecastGirder_get_StraightStrandMaterial(This,ppMaterial)	\
    ( (This)->lpVtbl -> get_StraightStrandMaterial(This,ppMaterial) ) 

#define IPrecastGirder_putref_HarpedStrandMaterial(This,pMaterial)	\
    ( (This)->lpVtbl -> putref_HarpedStrandMaterial(This,pMaterial) ) 

#define IPrecastGirder_get_HarpedStrandMaterial(This,ppMaterial)	\
    ( (This)->lpVtbl -> get_HarpedStrandMaterial(This,ppMaterial) ) 

#define IPrecastGirder_putref_TemporaryStrandMaterial(This,pMaterial)	\
    ( (This)->lpVtbl -> putref_TemporaryStrandMaterial(This,pMaterial) ) 

#define IPrecastGirder_get_TemporaryStrandMaterial(This,ppMaterial)	\
    ( (This)->lpVtbl -> get_TemporaryStrandMaterial(This,ppMaterial) ) 

#define IPrecastGirder_get_StraightStrandGrid(This,endType,ptrn)	\
    ( (This)->lpVtbl -> get_StraightStrandGrid(This,endType,ptrn) ) 

#define IPrecastGirder_get_TemporaryStrandGrid(This,endType,ptrn)	\
    ( (This)->lpVtbl -> get_TemporaryStrandGrid(This,endType,ptrn) ) 

#define IPrecastGirder_get_HarpedStrandGridEnd(This,endType,ptrn)	\
    ( (This)->lpVtbl -> get_HarpedStrandGridEnd(This,endType,ptrn) ) 

#define IPrecastGirder_get_HarpedStrandGridHP(This,endType,ptrn)	\
    ( (This)->lpVtbl -> get_HarpedStrandGridHP(This,endType,ptrn) ) 

#define IPrecastGirder_put_AllowOddNumberOfHarpedStrands(This,bUseMin)	\
    ( (This)->lpVtbl -> put_AllowOddNumberOfHarpedStrands(This,bUseMin) ) 

#define IPrecastGirder_get_AllowOddNumberOfHarpedStrands(This,bUseMin)	\
    ( (This)->lpVtbl -> get_AllowOddNumberOfHarpedStrands(This,bUseMin) ) 

#define IPrecastGirder_put_UseDifferentHarpedGridsAtEnds(This,bUseDifferent)	\
    ( (This)->lpVtbl -> put_UseDifferentHarpedGridsAtEnds(This,bUseDifferent) ) 

#define IPrecastGirder_get_UseDifferentHarpedGridsAtEnds(This,bUseDifferent)	\
    ( (This)->lpVtbl -> get_UseDifferentHarpedGridsAtEnds(This,bUseDifferent) ) 

#define IPrecastGirder_get_HarpedEndAdjustmentIncrement(This,increment)	\
    ( (This)->lpVtbl -> get_HarpedEndAdjustmentIncrement(This,increment) ) 

#define IPrecastGirder_get_HarpedHpAdjustmentIncrement(This,increment)	\
    ( (This)->lpVtbl -> get_HarpedHpAdjustmentIncrement(This,increment) ) 

#define IPrecastGirder_get_TopElevation(This,offset)	\
    ( (This)->lpVtbl -> get_TopElevation(This,offset) ) 

#define IPrecastGirder_get_HarpedStrandAdjustmentEnd(This,endType,offset)	\
    ( (This)->lpVtbl -> get_HarpedStrandAdjustmentEnd(This,endType,offset) ) 

#define IPrecastGirder_put_HarpedStrandAdjustmentEnd(This,endType,offset)	\
    ( (This)->lpVtbl -> put_HarpedStrandAdjustmentEnd(This,endType,offset) ) 

#define IPrecastGirder_get_HarpedStrandAdjustmentHP(This,endType,offset)	\
    ( (This)->lpVtbl -> get_HarpedStrandAdjustmentHP(This,endType,offset) ) 

#define IPrecastGirder_put_HarpedStrandAdjustmentHP(This,endType,offset)	\
    ( (This)->lpVtbl -> put_HarpedStrandAdjustmentHP(This,endType,offset) ) 

#define IPrecastGirder_SetHarpingPoints(This,hp1,hp2)	\
    ( (This)->lpVtbl -> SetHarpingPoints(This,hp1,hp2) ) 

#define IPrecastGirder_GetHarpingPoints(This,hp1,hp2)	\
    ( (This)->lpVtbl -> GetHarpingPoints(This,hp1,hp2) ) 

#define IPrecastGirder_SetEndHarpingPoints(This,hp1,hp2)	\
    ( (This)->lpVtbl -> SetEndHarpingPoints(This,hp1,hp2) ) 

#define IPrecastGirder_GetEndHarpingPoints(This,hp1,hp2)	\
    ( (This)->lpVtbl -> GetEndHarpingPoints(This,hp1,hp2) ) 

#define IPrecastGirder_put_UseMinHarpPointDistance(This,bUseMin)	\
    ( (This)->lpVtbl -> put_UseMinHarpPointDistance(This,bUseMin) ) 

#define IPrecastGirder_get_UseMinHarpPointDistance(This,bUseMin)	\
    ( (This)->lpVtbl -> get_UseMinHarpPointDistance(This,bUseMin) ) 

#define IPrecastGirder_put_MinHarpPointDistance(This,minHpDist)	\
    ( (This)->lpVtbl -> put_MinHarpPointDistance(This,minHpDist) ) 

#define IPrecastGirder_get_MinHarpPointDistance(This,minHpDist)	\
    ( (This)->lpVtbl -> get_MinHarpPointDistance(This,minHpDist) ) 

#define IPrecastGirder_put_HarpingPointMeasure(This,measure)	\
    ( (This)->lpVtbl -> put_HarpingPointMeasure(This,measure) ) 

#define IPrecastGirder_get_HarpingPointMeasure(This,measure)	\
    ( (This)->lpVtbl -> get_HarpingPointMeasure(This,measure) ) 

#define IPrecastGirder_put_EndHarpingPointMeasure(This,measure)	\
    ( (This)->lpVtbl -> put_EndHarpingPointMeasure(This,measure) ) 

#define IPrecastGirder_get_EndHarpingPointMeasure(This,measure)	\
    ( (This)->lpVtbl -> get_EndHarpingPointMeasure(This,measure) ) 

#define IPrecastGirder_put_HarpingPointReference(This,hpRef)	\
    ( (This)->lpVtbl -> put_HarpingPointReference(This,hpRef) ) 

#define IPrecastGirder_get_HarpingPointReference(This,hpRef)	\
    ( (This)->lpVtbl -> get_HarpingPointReference(This,hpRef) ) 

#define IPrecastGirder_put_EndHarpingPointReference(This,hpRef)	\
    ( (This)->lpVtbl -> put_EndHarpingPointReference(This,hpRef) ) 

#define IPrecastGirder_get_EndHarpingPointReference(This,hpRef)	\
    ( (This)->lpVtbl -> get_EndHarpingPointReference(This,hpRef) ) 

#define IPrecastGirder_GetHarpingPointLocations(This,hp1,hp2)	\
    ( (This)->lpVtbl -> GetHarpingPointLocations(This,hp1,hp2) ) 

#define IPrecastGirder_GetEndHarpingPointLocations(This,hp1,hp2)	\
    ( (This)->lpVtbl -> GetEndHarpingPointLocations(This,hp1,hp2) ) 

#define IPrecastGirder_get_SpanLength(This,length)	\
    ( (This)->lpVtbl -> get_SpanLength(This,length) ) 

#define IPrecastGirder_get_GirderLength(This,length)	\
    ( (This)->lpVtbl -> get_GirderLength(This,length) ) 

#define IPrecastGirder_get_LeftEndDistance(This,size)	\
    ( (This)->lpVtbl -> get_LeftEndDistance(This,size) ) 

#define IPrecastGirder_get_RightEndDistance(This,size)	\
    ( (This)->lpVtbl -> get_RightEndDistance(This,size) ) 

#define IPrecastGirder_get_LeftBearingOffset(This,offset)	\
    ( (This)->lpVtbl -> get_LeftBearingOffset(This,offset) ) 

#define IPrecastGirder_get_RightBearingOffset(This,offset)	\
    ( (This)->lpVtbl -> get_RightBearingOffset(This,offset) ) 

#define IPrecastGirder_GetEndPoints(This,pntPier1,pntEnd1,pntBrg1,pntBrg2,pntEnd2,pntPier2)	\
    ( (This)->lpVtbl -> GetEndPoints(This,pntPier1,pntEnd1,pntBrg1,pntBrg2,pntEnd2,pntPier2) ) 

#define IPrecastGirder_get_StraightMaxStrandFill(This,fill)	\
    ( (This)->lpVtbl -> get_StraightMaxStrandFill(This,fill) ) 

#define IPrecastGirder_get_HarpedMaxStrandFill(This,fill)	\
    ( (This)->lpVtbl -> get_HarpedMaxStrandFill(This,fill) ) 

#define IPrecastGirder_get_TemporaryMaxStrandFill(This,fill)	\
    ( (This)->lpVtbl -> get_TemporaryMaxStrandFill(This,fill) ) 

#define IPrecastGirder_get_StraightStrandFill(This,fill)	\
    ( (This)->lpVtbl -> get_StraightStrandFill(This,fill) ) 

#define IPrecastGirder_putref_StraightStrandFill(This,fill)	\
    ( (This)->lpVtbl -> putref_StraightStrandFill(This,fill) ) 

#define IPrecastGirder_get_HarpedStrandFill(This,fill)	\
    ( (This)->lpVtbl -> get_HarpedStrandFill(This,fill) ) 

#define IPrecastGirder_putref_HarpedStrandFill(This,fill)	\
    ( (This)->lpVtbl -> putref_HarpedStrandFill(This,fill) ) 

#define IPrecastGirder_get_TemporaryStrandFill(This,fill)	\
    ( (This)->lpVtbl -> get_TemporaryStrandFill(This,fill) ) 

#define IPrecastGirder_putref_TemporaryStrandFill(This,fill)	\
    ( (This)->lpVtbl -> putref_TemporaryStrandFill(This,fill) ) 

#define IPrecastGirder_get_StraightStrandPositions(This,distFromStart,points)	\
    ( (This)->lpVtbl -> get_StraightStrandPositions(This,distFromStart,points) ) 

#define IPrecastGirder_get_StraightStrandPositionsEx(This,distFromStart,fill,points)	\
    ( (This)->lpVtbl -> get_StraightStrandPositionsEx(This,distFromStart,fill,points) ) 

#define IPrecastGirder_get_HarpedStrandPositions(This,distFromStart,points)	\
    ( (This)->lpVtbl -> get_HarpedStrandPositions(This,distFromStart,points) ) 

#define IPrecastGirder_get_HarpedStrandPositionsEx(This,distFromStart,fill,points)	\
    ( (This)->lpVtbl -> get_HarpedStrandPositionsEx(This,distFromStart,fill,points) ) 

#define IPrecastGirder_get_TemporaryStrandPositions(This,distFromStart,points)	\
    ( (This)->lpVtbl -> get_TemporaryStrandPositions(This,distFromStart,points) ) 

#define IPrecastGirder_get_TemporaryStrandPositionsEx(This,distFromStart,fill,points)	\
    ( (This)->lpVtbl -> get_TemporaryStrandPositionsEx(This,distFromStart,fill,points) ) 

#define IPrecastGirder_StraightStrandIndexToGridIndex(This,strandIndex,gridIndex)	\
    ( (This)->lpVtbl -> StraightStrandIndexToGridIndex(This,strandIndex,gridIndex) ) 

#define IPrecastGirder_StraightStrandIndexToGridIndexEx(This,fill,strandIndex,gridIndex)	\
    ( (This)->lpVtbl -> StraightStrandIndexToGridIndexEx(This,fill,strandIndex,gridIndex) ) 

#define IPrecastGirder_HarpedStrandIndexToGridIndex(This,strandIndex,gridIndex)	\
    ( (This)->lpVtbl -> HarpedStrandIndexToGridIndex(This,strandIndex,gridIndex) ) 

#define IPrecastGirder_HarpedStrandIndexToGridIndexEx(This,fill,strandIndex,gridIndex)	\
    ( (This)->lpVtbl -> HarpedStrandIndexToGridIndexEx(This,fill,strandIndex,gridIndex) ) 

#define IPrecastGirder_TemporaryStrandIndexToGridIndex(This,strandIndex,gridIndex)	\
    ( (This)->lpVtbl -> TemporaryStrandIndexToGridIndex(This,strandIndex,gridIndex) ) 

#define IPrecastGirder_TemporaryStrandIndexToGridIndexEx(This,fill,strandIndex,gridIndex)	\
    ( (This)->lpVtbl -> TemporaryStrandIndexToGridIndexEx(This,fill,strandIndex,gridIndex) ) 

#define IPrecastGirder_StraightStrandBoundingBox(This,endType,box)	\
    ( (This)->lpVtbl -> StraightStrandBoundingBox(This,endType,box) ) 

#define IPrecastGirder_StraightStrandBoundingBoxEx(This,endType,fill,box)	\
    ( (This)->lpVtbl -> StraightStrandBoundingBoxEx(This,endType,fill,box) ) 

#define IPrecastGirder_HarpedEndStrandBoundingBox(This,endType,box)	\
    ( (This)->lpVtbl -> HarpedEndStrandBoundingBox(This,endType,box) ) 

#define IPrecastGirder_HarpedEndStrandBoundingBoxEx(This,endType,fill,box)	\
    ( (This)->lpVtbl -> HarpedEndStrandBoundingBoxEx(This,endType,fill,box) ) 

#define IPrecastGirder_HarpedHpStrandBoundingBox(This,endType,box)	\
    ( (This)->lpVtbl -> HarpedHpStrandBoundingBox(This,endType,box) ) 

#define IPrecastGirder_HarpedHpStrandBoundingBoxEx(This,endType,fill,box)	\
    ( (This)->lpVtbl -> HarpedHpStrandBoundingBoxEx(This,endType,fill,box) ) 

#define IPrecastGirder_HarpedEndStrandBoundaryCheck(This,endType,adjustment)	\
    ( (This)->lpVtbl -> HarpedEndStrandBoundaryCheck(This,endType,adjustment) ) 

#define IPrecastGirder_HarpedHpStrandBoundaryCheck(This,endType,adjustment)	\
    ( (This)->lpVtbl -> HarpedHpStrandBoundaryCheck(This,endType,adjustment) ) 

#define IPrecastGirder_GetHarpedEndAdjustmentBounds(This,endType,DownwardAdjustment,UpwardAdjustment)	\
    ( (This)->lpVtbl -> GetHarpedEndAdjustmentBounds(This,endType,DownwardAdjustment,UpwardAdjustment) ) 

#define IPrecastGirder_GetHarpedEndAdjustmentBoundsEx(This,endType,fill,DownwardAdjustment,UpwardAdjustment)	\
    ( (This)->lpVtbl -> GetHarpedEndAdjustmentBoundsEx(This,endType,fill,DownwardAdjustment,UpwardAdjustment) ) 

#define IPrecastGirder_GetHarpedHpAdjustmentBounds(This,endType,DownwardAdjustment,UpwardAdjustment)	\
    ( (This)->lpVtbl -> GetHarpedHpAdjustmentBounds(This,endType,DownwardAdjustment,UpwardAdjustment) ) 

#define IPrecastGirder_GetHarpedHpAdjustmentBoundsEx(This,endType,fill,DownwardAdjustment,UpwardAdjustment)	\
    ( (This)->lpVtbl -> GetHarpedHpAdjustmentBoundsEx(This,endType,fill,DownwardAdjustment,UpwardAdjustment) ) 

#define IPrecastGirder_GetHarpedEndFilledGridBoundsEx(This,endType,fill,bottomElev,topElev)	\
    ( (This)->lpVtbl -> GetHarpedEndFilledGridBoundsEx(This,endType,fill,bottomElev,topElev) ) 

#define IPrecastGirder_GetHarpedHpFilledGridBoundsEx(This,endType,fill,bottomElev,topElev)	\
    ( (This)->lpVtbl -> GetHarpedHpFilledGridBoundsEx(This,endType,fill,bottomElev,topElev) ) 

#define IPrecastGirder_ComputeMaxHarpedStrandSlope(This,distFromStart,slope)	\
    ( (This)->lpVtbl -> ComputeMaxHarpedStrandSlope(This,distFromStart,slope) ) 

#define IPrecastGirder_ComputeMaxHarpedStrandSlopeEx(This,distFromStart,fill,startOffset,hp1Offset,hp2Offset,endOffset,slope)	\
    ( (This)->lpVtbl -> ComputeMaxHarpedStrandSlopeEx(This,distFromStart,fill,startOffset,hp1Offset,hp2Offset,endOffset,slope) ) 

#define IPrecastGirder_ComputeAvgHarpedStrandSlope(This,distFromStart,slope)	\
    ( (This)->lpVtbl -> ComputeAvgHarpedStrandSlope(This,distFromStart,slope) ) 

#define IPrecastGirder_ComputeAvgHarpedStrandSlopeEx(This,distFromStart,fill,startOffset,hp1Offset,hp2Offset,endOffset,slope)	\
    ( (This)->lpVtbl -> ComputeAvgHarpedStrandSlopeEx(This,distFromStart,fill,startOffset,hp1Offset,hp2Offset,endOffset,slope) ) 

#define IPrecastGirder_get_MaxStraightStrands(This,nStrands)	\
    ( (This)->lpVtbl -> get_MaxStraightStrands(This,nStrands) ) 

#define IPrecastGirder_get_MaxHarpedStrands(This,nStrands)	\
    ( (This)->lpVtbl -> get_MaxHarpedStrands(This,nStrands) ) 

#define IPrecastGirder_get_MaxTemporaryStrands(This,nStrands)	\
    ( (This)->lpVtbl -> get_MaxTemporaryStrands(This,nStrands) ) 

#define IPrecastGirder_GetStraightStrandCount(This,nStrands)	\
    ( (This)->lpVtbl -> GetStraightStrandCount(This,nStrands) ) 

#define IPrecastGirder_GetHarpedStrandCount(This,nStrands)	\
    ( (This)->lpVtbl -> GetHarpedStrandCount(This,nStrands) ) 

#define IPrecastGirder_GetTemporaryStrandCount(This,nStrands)	\
    ( (This)->lpVtbl -> GetTemporaryStrandCount(This,nStrands) ) 

#define IPrecastGirder_GetStraightStrandCountEx(This,fill,nStrands)	\
    ( (This)->lpVtbl -> GetStraightStrandCountEx(This,fill,nStrands) ) 

#define IPrecastGirder_GetHarpedStrandCountEx(This,fill,nStrands)	\
    ( (This)->lpVtbl -> GetHarpedStrandCountEx(This,fill,nStrands) ) 

#define IPrecastGirder_GetTemporaryStrandCountEx(This,fill,nStrands)	\
    ( (This)->lpVtbl -> GetTemporaryStrandCountEx(This,fill,nStrands) ) 

#define IPrecastGirder_GetStraightStrandDebondCount(This,loc,count)	\
    ( (This)->lpVtbl -> GetStraightStrandDebondCount(This,loc,count) ) 

#define IPrecastGirder_ClearStraightStrandDebonding(This)	\
    ( (This)->lpVtbl -> ClearStraightStrandDebonding(This) ) 

#define IPrecastGirder_DebondStraightStrandByGridIndex(This,grdIndex,l1,l2)	\
    ( (This)->lpVtbl -> DebondStraightStrandByGridIndex(This,grdIndex,l1,l2) ) 

#define IPrecastGirder_GetDebondedStraightStrandsByGridIndex(This,grdIndexes)	\
    ( (This)->lpVtbl -> GetDebondedStraightStrandsByGridIndex(This,grdIndexes) ) 

#define IPrecastGirder_GetStraightStrandDebondLengthByGridIndex(This,endType,grdIndex,YCoord,l1,l2)	\
    ( (This)->lpVtbl -> GetStraightStrandDebondLengthByGridIndex(This,endType,grdIndex,YCoord,l1,l2) ) 

#define IPrecastGirder_GetStraightStrandDebondLengthByPositionIndex(This,endType,positionIndex,YCoord,l1,l2)	\
    ( (This)->lpVtbl -> GetStraightStrandDebondLengthByPositionIndex(This,endType,positionIndex,YCoord,l1,l2) ) 

#define IPrecastGirder_GetStraightStrandsDebondedByPositionIndex(This,endType,distFromStart,positionIndexes)	\
    ( (This)->lpVtbl -> GetStraightStrandsDebondedByPositionIndex(This,endType,distFromStart,positionIndexes) ) 

#define IPrecastGirder_get_StraightStrandRowsWithStrand(This,nRows)	\
    ( (This)->lpVtbl -> get_StraightStrandRowsWithStrand(This,nRows) ) 

#define IPrecastGirder_get_StraightStrandsInRow(This,rowIdx,gridIndexes)	\
    ( (This)->lpVtbl -> get_StraightStrandsInRow(This,rowIdx,gridIndexes) ) 

#define IPrecastGirder_get_NumStraightStrandsInRow(This,rowIdx,nStrands)	\
    ( (This)->lpVtbl -> get_NumStraightStrandsInRow(This,rowIdx,nStrands) ) 

#define IPrecastGirder_get_StraightStrandDebondInRow(This,rowIdx,nStrands)	\
    ( (This)->lpVtbl -> get_StraightStrandDebondInRow(This,rowIdx,nStrands) ) 

#define IPrecastGirder_IsExteriorStraightStrandDebondedInRow(This,rowIndex,bResult)	\
    ( (This)->lpVtbl -> IsExteriorStraightStrandDebondedInRow(This,rowIndex,bResult) ) 

#define IPrecastGirder_get_HarpedStrandRowsWithStrand(This,distFromStart,nRows)	\
    ( (This)->lpVtbl -> get_HarpedStrandRowsWithStrand(This,distFromStart,nRows) ) 

#define IPrecastGirder_get_HarpedStrandsInRow(This,distFromStart,rowIdx,gridIndexes)	\
    ( (This)->lpVtbl -> get_HarpedStrandsInRow(This,distFromStart,rowIdx,gridIndexes) ) 

#define IPrecastGirder_get_NumHarpedStrandsInRow(This,distFromStart,rowIdx,nStrands)	\
    ( (This)->lpVtbl -> get_NumHarpedStrandsInRow(This,distFromStart,rowIdx,nStrands) ) 

#define IPrecastGirder_GetStraightStrandDebondAtSections(This,arrLeft,arrRight)	\
    ( (This)->lpVtbl -> GetStraightStrandDebondAtSections(This,arrLeft,arrRight) ) 

#define IPrecastGirder_GetStraightStrandDebondAtLeftSection(This,sectionIdx,pstnIndexes)	\
    ( (This)->lpVtbl -> GetStraightStrandDebondAtLeftSection(This,sectionIdx,pstnIndexes) ) 

#define IPrecastGirder_GetStraightStrandDebondAtRightSection(This,sectionIdx,pstnIndexes)	\
    ( (This)->lpVtbl -> GetStraightStrandDebondAtRightSection(This,sectionIdx,pstnIndexes) ) 

#define IPrecastGirder_GetStraightStrandBondedLengthByPositionIndex(This,positionIndex,distFromStart,YCoord,leftBond,rightBond)	\
    ( (This)->lpVtbl -> GetStraightStrandBondedLengthByPositionIndex(This,positionIndex,distFromStart,YCoord,leftBond,rightBond) ) 

#define IPrecastGirder_GetStraightStrandBondedLengthByGridIndex(This,grdIndex,distFromStart,YCoord,leftBond,rightBond)	\
    ( (This)->lpVtbl -> GetStraightStrandBondedLengthByGridIndex(This,grdIndex,distFromStart,YCoord,leftBond,rightBond) ) 

#define IPrecastGirder_get_SuperstructureMemberSegment(This,segment)	\
    ( (This)->lpVtbl -> get_SuperstructureMemberSegment(This,segment) ) 

#define IPrecastGirder_get_RebarLayout(This,rebarLayout)	\
    ( (This)->lpVtbl -> get_RebarLayout(This,rebarLayout) ) 

#define IPrecastGirder_get_ClosureJointRebarLayout(This,rebarLayout)	\
    ( (This)->lpVtbl -> get_ClosureJointRebarLayout(This,rebarLayout) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPrecastGirder_INTERFACE_DEFINED__ */


#ifndef __IFlexRebarLayoutItem_INTERFACE_DEFINED__
#define __IFlexRebarLayoutItem_INTERFACE_DEFINED__

/* interface IFlexRebarLayoutItem */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFlexRebarLayoutItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B887911C-EC53-4f32-B5E2-9D43C1F8D977")
    IFlexRebarLayoutItem : public IRebarLayoutItem
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Position( 
            /* [retval][out] */ LayoutPosition *lp) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Position( 
            /* [in] */ LayoutPosition lp) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LengthFactor( 
            /* [retval][out] */ Float64 *lf) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LengthFactor( 
            /* [in] */ Float64 lf) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Girder( 
            /* [in] */ IPrecastGirder *girder) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFlexRebarLayoutItemVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFlexRebarLayoutItem * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj);
        
        /* [id][restricted][funcdescattr] */ unsigned long ( STDMETHODCALLTYPE *AddRef )( 
            IFlexRebarLayoutItem * This);
        
        /* [id][restricted][funcdescattr] */ unsigned long ( STDMETHODCALLTYPE *Release )( 
            IFlexRebarLayoutItem * This);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *ContainsLocation )( 
            IFlexRebarLayoutItem * This,
            /* [in][idldescattr] */ double distFromStart,
            /* [out][idldescattr] */ BOOLEAN *bResult);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            IFlexRebarLayoutItem * This,
            /* [out][idldescattr] */ double *Start,
            /* [retval][out] */ HRESULT *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IFlexRebarLayoutItem * This,
            /* [out][idldescattr] */ double *Length,
            /* [retval][out] */ HRESULT *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFlexRebarLayoutItem * This,
            /* [out][idldescattr] */ unsigned int64 *Count,
            /* [retval][out] */ HRESULT *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFlexRebarLayoutItem * This,
            /* [in][idldescattr] */ unsigned int64 idx,
            /* [out][idldescattr] */ IRebarPattern **pattern,
            /* [retval][out] */ HRESULT *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRebarPattern )( 
            IFlexRebarLayoutItem * This,
            /* [in][idldescattr] */ IRebarPattern *pattern);
        
        /* [id][propget][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFlexRebarLayoutItem * This,
            /* [out][idldescattr] */ IUnknown **retval,
            /* [retval][out] */ HRESULT *retval);
        
        /* [id][propget][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get__EnumRebarPatterns )( 
            IFlexRebarLayoutItem * This,
            /* [out][idldescattr] */ IEnumRebarPatterns **enumRebarPatterns,
            /* [retval][out] */ HRESULT *retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Position )( 
            IFlexRebarLayoutItem * This,
            /* [retval][out] */ LayoutPosition *lp);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Position )( 
            IFlexRebarLayoutItem * This,
            /* [in] */ LayoutPosition lp);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LengthFactor )( 
            IFlexRebarLayoutItem * This,
            /* [retval][out] */ Float64 *lf);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LengthFactor )( 
            IFlexRebarLayoutItem * This,
            /* [in] */ Float64 lf);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Girder )( 
            IFlexRebarLayoutItem * This,
            /* [in] */ IPrecastGirder *girder);
        
        END_INTERFACE
    } IFlexRebarLayoutItemVtbl;

    interface IFlexRebarLayoutItem
    {
        CONST_VTBL struct IFlexRebarLayoutItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFlexRebarLayoutItem_QueryInterface(This,riid,ppvObj)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj) ) 

#define IFlexRebarLayoutItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFlexRebarLayoutItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFlexRebarLayoutItem_ContainsLocation(This,distFromStart,bResult)	\
    ( (This)->lpVtbl -> ContainsLocation(This,distFromStart,bResult) ) 

#define IFlexRebarLayoutItem_get_Start(This,Start,retval)	\
    ( (This)->lpVtbl -> get_Start(This,Start,retval) ) 

#define IFlexRebarLayoutItem_get_Length(This,Length,retval)	\
    ( (This)->lpVtbl -> get_Length(This,Length,retval) ) 

#define IFlexRebarLayoutItem_get_Count(This,Count,retval)	\
    ( (This)->lpVtbl -> get_Count(This,Count,retval) ) 

#define IFlexRebarLayoutItem_get_Item(This,idx,pattern,retval)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pattern,retval) ) 

#define IFlexRebarLayoutItem_AddRebarPattern(This,pattern)	\
    ( (This)->lpVtbl -> AddRebarPattern(This,pattern) ) 

#define IFlexRebarLayoutItem_get__NewEnum(This,retval,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval,retval) ) 

#define IFlexRebarLayoutItem_get__EnumRebarPatterns(This,enumRebarPatterns,retval)	\
    ( (This)->lpVtbl -> get__EnumRebarPatterns(This,enumRebarPatterns,retval) ) 


#define IFlexRebarLayoutItem_get_Position(This,lp)	\
    ( (This)->lpVtbl -> get_Position(This,lp) ) 

#define IFlexRebarLayoutItem_put_Position(This,lp)	\
    ( (This)->lpVtbl -> put_Position(This,lp) ) 

#define IFlexRebarLayoutItem_get_LengthFactor(This,lf)	\
    ( (This)->lpVtbl -> get_LengthFactor(This,lf) ) 

#define IFlexRebarLayoutItem_put_LengthFactor(This,lf)	\
    ( (This)->lpVtbl -> put_LengthFactor(This,lf) ) 

#define IFlexRebarLayoutItem_putref_Girder(This,girder)	\
    ( (This)->lpVtbl -> putref_Girder(This,girder) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFlexRebarLayoutItem_INTERFACE_DEFINED__ */


#ifndef __ISectionCutTool_INTERFACE_DEFINED__
#define __ISectionCutTool_INTERFACE_DEFINED__

/* interface ISectionCutTool */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISectionCutTool;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B3D076FB-B0B0-4791-ADCF-BE1826640996")
    ISectionCutTool : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_EffectiveFlangeWidthTool( 
            /* [in] */ /* external definition not present */ IEffectiveFlangeWidthTool *pTool) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EffectiveFlangeWidthTool( 
            /* [retval][out] */ /* external definition not present */ IEffectiveFlangeWidthTool **pTool) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateGirderSectionBySSMbr( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xgp,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ SectionPropertyMethod sectionPropMethod,
            /* [retval][out] */ ISection **section) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateGirderSectionBySegment( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ SectionPropertyMethod sectionPropMethod,
            /* [retval][out] */ ISection **section) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateBridgeSection( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 distFromStartOfBridge,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ BarrierSectionCut bsc,
            /* [retval][out] */ ISection **section) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateLeftBarrierSection( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ VARIANT_BOOL bStructuralOnly,
            /* [retval][out] */ ISection **section) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateRightBarrierSection( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ VARIANT_BOOL bStructuralOnly,
            /* [retval][out] */ ISection **section) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateNetDeckSection( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ ISection **section) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateGirderShapeBySSMbr( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xgp,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IShape **ppShape) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateGirderShapeBySegment( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IShape **ppShape) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateLeftBarrierShape( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *pDirection,
            /* [retval][out] */ IShape **shape) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateRightBarrierShape( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *pDirection,
            /* [retval][out] */ IShape **shape) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateSlabShape( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *pDirection,
            /* [in] */ VARIANT_BOOL bIncludeHaunch,
            /* [retval][out] */ IShape **shape) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDeckProperties( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ IndexType nSectionsPerSpan,
            /* [out] */ Float64 *pSurfaceArea,
            /* [out] */ Float64 *pVolume) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISectionCutToolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISectionCutTool * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISectionCutTool * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISectionCutTool * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_EffectiveFlangeWidthTool )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IEffectiveFlangeWidthTool *pTool);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EffectiveFlangeWidthTool )( 
            ISectionCutTool * This,
            /* [retval][out] */ /* external definition not present */ IEffectiveFlangeWidthTool **pTool);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateGirderSectionBySSMbr )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xgp,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ SectionPropertyMethod sectionPropMethod,
            /* [retval][out] */ ISection **section);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateGirderSectionBySegment )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ SectionPropertyMethod sectionPropMethod,
            /* [retval][out] */ ISection **section);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateBridgeSection )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 distFromStartOfBridge,
            /* [in] */ StageIndexType stageIdx,
            /* [in] */ BarrierSectionCut bsc,
            /* [retval][out] */ ISection **section);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateLeftBarrierSection )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ VARIANT_BOOL bStructuralOnly,
            /* [retval][out] */ ISection **section);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateRightBarrierSection )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ VARIANT_BOOL bStructuralOnly,
            /* [retval][out] */ ISection **section);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateNetDeckSection )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ ISection **section);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateGirderShapeBySSMbr )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 Xgp,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateGirderShapeBySegment )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType leftSSMbrID,
            /* [in] */ GirderIDType rightSSMbrID,
            /* [in] */ StageIndexType stageIdx,
            /* [retval][out] */ IShape **ppShape);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateLeftBarrierShape )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *pDirection,
            /* [retval][out] */ IShape **shape);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateRightBarrierShape )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *pDirection,
            /* [retval][out] */ IShape **shape);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSlabShape )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *pDirection,
            /* [in] */ VARIANT_BOOL bIncludeHaunch,
            /* [retval][out] */ IShape **shape);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDeckProperties )( 
            ISectionCutTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ IndexType nSectionsPerSpan,
            /* [out] */ Float64 *pSurfaceArea,
            /* [out] */ Float64 *pVolume);
        
        END_INTERFACE
    } ISectionCutToolVtbl;

    interface ISectionCutTool
    {
        CONST_VTBL struct ISectionCutToolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISectionCutTool_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISectionCutTool_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISectionCutTool_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISectionCutTool_putref_EffectiveFlangeWidthTool(This,pTool)	\
    ( (This)->lpVtbl -> putref_EffectiveFlangeWidthTool(This,pTool) ) 

#define ISectionCutTool_get_EffectiveFlangeWidthTool(This,pTool)	\
    ( (This)->lpVtbl -> get_EffectiveFlangeWidthTool(This,pTool) ) 

#define ISectionCutTool_CreateGirderSectionBySSMbr(This,bridge,ssMbrID,Xgp,leftSSMbrID,rightSSMbrID,stageIdx,sectionPropMethod,section)	\
    ( (This)->lpVtbl -> CreateGirderSectionBySSMbr(This,bridge,ssMbrID,Xgp,leftSSMbrID,rightSSMbrID,stageIdx,sectionPropMethod,section) ) 

#define ISectionCutTool_CreateGirderSectionBySegment(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,sectionPropMethod,section)	\
    ( (This)->lpVtbl -> CreateGirderSectionBySegment(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,sectionPropMethod,section) ) 

#define ISectionCutTool_CreateBridgeSection(This,bridge,distFromStartOfBridge,stageIdx,bsc,section)	\
    ( (This)->lpVtbl -> CreateBridgeSection(This,bridge,distFromStartOfBridge,stageIdx,bsc,section) ) 

#define ISectionCutTool_CreateLeftBarrierSection(This,bridge,station,bStructuralOnly,section)	\
    ( (This)->lpVtbl -> CreateLeftBarrierSection(This,bridge,station,bStructuralOnly,section) ) 

#define ISectionCutTool_CreateRightBarrierSection(This,bridge,station,bStructuralOnly,section)	\
    ( (This)->lpVtbl -> CreateRightBarrierSection(This,bridge,station,bStructuralOnly,section) ) 

#define ISectionCutTool_CreateNetDeckSection(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,section)	\
    ( (This)->lpVtbl -> CreateNetDeckSection(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,section) ) 

#define ISectionCutTool_CreateGirderShapeBySSMbr(This,bridge,ssMbrID,Xgp,leftSSMbrID,rightSSMbrID,stageIdx,ppShape)	\
    ( (This)->lpVtbl -> CreateGirderShapeBySSMbr(This,bridge,ssMbrID,Xgp,leftSSMbrID,rightSSMbrID,stageIdx,ppShape) ) 

#define ISectionCutTool_CreateGirderShapeBySegment(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,ppShape)	\
    ( (This)->lpVtbl -> CreateGirderShapeBySegment(This,bridge,ssMbrID,segIdx,Xs,leftSSMbrID,rightSSMbrID,stageIdx,ppShape) ) 

#define ISectionCutTool_CreateLeftBarrierShape(This,bridge,station,pDirection,shape)	\
    ( (This)->lpVtbl -> CreateLeftBarrierShape(This,bridge,station,pDirection,shape) ) 

#define ISectionCutTool_CreateRightBarrierShape(This,bridge,station,pDirection,shape)	\
    ( (This)->lpVtbl -> CreateRightBarrierShape(This,bridge,station,pDirection,shape) ) 

#define ISectionCutTool_CreateSlabShape(This,bridge,station,pDirection,bIncludeHaunch,shape)	\
    ( (This)->lpVtbl -> CreateSlabShape(This,bridge,station,pDirection,bIncludeHaunch,shape) ) 

#define ISectionCutTool_GetDeckProperties(This,bridge,nSectionsPerSpan,pSurfaceArea,pVolume)	\
    ( (This)->lpVtbl -> GetDeckProperties(This,bridge,nSectionsPerSpan,pSurfaceArea,pVolume) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISectionCutTool_INTERFACE_DEFINED__ */


#ifndef __IStrandMover_INTERFACE_DEFINED__
#define __IStrandMover_INTERFACE_DEFINED__

/* interface IStrandMover */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStrandMover;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0FAD048E-8F77-472a-B2BF-7ED599FA765D")
    IStrandMover : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopElevation( 
            /* [retval][out] */ Float64 *topElev) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SectionHeight( 
            /* [retval][out] */ Float64 *pHeight) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HpStrandElevationBoundaries( 
            /* [in] */ EndType endType,
            /* [out] */ Float64 *bottomMin,
            /* [out] */ Float64 *topMax) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndStrandElevationBoundaries( 
            /* [in] */ EndType endType,
            /* [out] */ Float64 *bottomMin,
            /* [out] */ Float64 *topMax) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StrandIncrements( 
            /* [out] */ Float64 *endIncrement,
            /* [out] */ Float64 *hpIncrement) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TestHpStrandLocation( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 Hg,
            /* [in] */ Float64 originalX,
            /* [in] */ Float64 originalY,
            /* [in] */ Float64 Yoffset,
            /* [out] */ VARIANT_BOOL *isWithin) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TestEndStrandLocation( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 Hg,
            /* [in] */ Float64 originalX,
            /* [in] */ Float64 originalY,
            /* [in] */ Float64 Yoffset,
            /* [out] */ VARIANT_BOOL *isWithin) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TranslateHpStrand( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 originalX,
            /* [in] */ Float64 originalY,
            /* [in] */ Float64 Yoffset,
            /* [out] */ Float64 *newX,
            /* [out] */ Float64 *newY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TranslateEndStrand( 
            /* [in] */ EndType endType,
            /* [in] */ Float64 originalX,
            /* [in] */ Float64 originalY,
            /* [in] */ Float64 Yoffset,
            /* [out] */ Float64 *newX,
            /* [out] */ Float64 *newY) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStrandMoverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStrandMover * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStrandMover * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStrandMover * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopElevation )( 
            IStrandMover * This,
            /* [retval][out] */ Float64 *topElev);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SectionHeight )( 
            IStrandMover * This,
            /* [retval][out] */ Float64 *pHeight);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HpStrandElevationBoundaries )( 
            IStrandMover * This,
            /* [in] */ EndType endType,
            /* [out] */ Float64 *bottomMin,
            /* [out] */ Float64 *topMax);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndStrandElevationBoundaries )( 
            IStrandMover * This,
            /* [in] */ EndType endType,
            /* [out] */ Float64 *bottomMin,
            /* [out] */ Float64 *topMax);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandIncrements )( 
            IStrandMover * This,
            /* [out] */ Float64 *endIncrement,
            /* [out] */ Float64 *hpIncrement);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TestHpStrandLocation )( 
            IStrandMover * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 Hg,
            /* [in] */ Float64 originalX,
            /* [in] */ Float64 originalY,
            /* [in] */ Float64 Yoffset,
            /* [out] */ VARIANT_BOOL *isWithin);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TestEndStrandLocation )( 
            IStrandMover * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 Hg,
            /* [in] */ Float64 originalX,
            /* [in] */ Float64 originalY,
            /* [in] */ Float64 Yoffset,
            /* [out] */ VARIANT_BOOL *isWithin);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TranslateHpStrand )( 
            IStrandMover * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 originalX,
            /* [in] */ Float64 originalY,
            /* [in] */ Float64 Yoffset,
            /* [out] */ Float64 *newX,
            /* [out] */ Float64 *newY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TranslateEndStrand )( 
            IStrandMover * This,
            /* [in] */ EndType endType,
            /* [in] */ Float64 originalX,
            /* [in] */ Float64 originalY,
            /* [in] */ Float64 Yoffset,
            /* [out] */ Float64 *newX,
            /* [out] */ Float64 *newY);
        
        END_INTERFACE
    } IStrandMoverVtbl;

    interface IStrandMover
    {
        CONST_VTBL struct IStrandMoverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrandMover_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStrandMover_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStrandMover_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStrandMover_get_TopElevation(This,topElev)	\
    ( (This)->lpVtbl -> get_TopElevation(This,topElev) ) 

#define IStrandMover_get_SectionHeight(This,pHeight)	\
    ( (This)->lpVtbl -> get_SectionHeight(This,pHeight) ) 

#define IStrandMover_get_HpStrandElevationBoundaries(This,endType,bottomMin,topMax)	\
    ( (This)->lpVtbl -> get_HpStrandElevationBoundaries(This,endType,bottomMin,topMax) ) 

#define IStrandMover_get_EndStrandElevationBoundaries(This,endType,bottomMin,topMax)	\
    ( (This)->lpVtbl -> get_EndStrandElevationBoundaries(This,endType,bottomMin,topMax) ) 

#define IStrandMover_get_StrandIncrements(This,endIncrement,hpIncrement)	\
    ( (This)->lpVtbl -> get_StrandIncrements(This,endIncrement,hpIncrement) ) 

#define IStrandMover_TestHpStrandLocation(This,endType,Hg,originalX,originalY,Yoffset,isWithin)	\
    ( (This)->lpVtbl -> TestHpStrandLocation(This,endType,Hg,originalX,originalY,Yoffset,isWithin) ) 

#define IStrandMover_TestEndStrandLocation(This,endType,Hg,originalX,originalY,Yoffset,isWithin)	\
    ( (This)->lpVtbl -> TestEndStrandLocation(This,endType,Hg,originalX,originalY,Yoffset,isWithin) ) 

#define IStrandMover_TranslateHpStrand(This,endType,originalX,originalY,Yoffset,newX,newY)	\
    ( (This)->lpVtbl -> TranslateHpStrand(This,endType,originalX,originalY,Yoffset,newX,newY) ) 

#define IStrandMover_TranslateEndStrand(This,endType,originalX,originalY,Yoffset,newX,newY)	\
    ( (This)->lpVtbl -> TranslateEndStrand(This,endType,originalX,originalY,Yoffset,newX,newY) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrandMover_INTERFACE_DEFINED__ */


#ifndef __IStrandGrid_INTERFACE_DEFINED__
#define __IStrandGrid_INTERFACE_DEFINED__

/* interface IStrandGrid */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStrandGrid;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("656F5032-BB18-4644-911A-CD4672EBA5B0")
    IStrandGrid : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddGridPoint( 
            /* [in] */ IPoint2d *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddGridPoints( 
            /* [in] */ IPoint2dCollection *points) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GridPointCount( 
            /* [retval][out] */ GridIndexType *count) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GridPoint( 
            /* [in] */ GridIndexType idx,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GridPoints( 
            /* [retval][out] */ IPoint2dCollection **point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveGridPoint( 
            /* [in] */ GridIndexType idx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearGridPoints( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GridBoundingBox( 
            /* [retval][out] */ IRect2d **box) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStrandGridVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStrandGrid * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStrandGrid * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStrandGrid * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddGridPoint )( 
            IStrandGrid * This,
            /* [in] */ IPoint2d *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddGridPoints )( 
            IStrandGrid * This,
            /* [in] */ IPoint2dCollection *points);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GridPointCount )( 
            IStrandGrid * This,
            /* [retval][out] */ GridIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GridPoint )( 
            IStrandGrid * This,
            /* [in] */ GridIndexType idx,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GridPoints )( 
            IStrandGrid * This,
            /* [retval][out] */ IPoint2dCollection **point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveGridPoint )( 
            IStrandGrid * This,
            /* [in] */ GridIndexType idx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearGridPoints )( 
            IStrandGrid * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GridBoundingBox )( 
            IStrandGrid * This,
            /* [retval][out] */ IRect2d **box);
        
        END_INTERFACE
    } IStrandGridVtbl;

    interface IStrandGrid
    {
        CONST_VTBL struct IStrandGridVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrandGrid_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStrandGrid_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStrandGrid_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStrandGrid_AddGridPoint(This,point)	\
    ( (This)->lpVtbl -> AddGridPoint(This,point) ) 

#define IStrandGrid_AddGridPoints(This,points)	\
    ( (This)->lpVtbl -> AddGridPoints(This,points) ) 

#define IStrandGrid_get_GridPointCount(This,count)	\
    ( (This)->lpVtbl -> get_GridPointCount(This,count) ) 

#define IStrandGrid_get_GridPoint(This,idx,point)	\
    ( (This)->lpVtbl -> get_GridPoint(This,idx,point) ) 

#define IStrandGrid_get_GridPoints(This,point)	\
    ( (This)->lpVtbl -> get_GridPoints(This,point) ) 

#define IStrandGrid_RemoveGridPoint(This,idx)	\
    ( (This)->lpVtbl -> RemoveGridPoint(This,idx) ) 

#define IStrandGrid_ClearGridPoints(This)	\
    ( (This)->lpVtbl -> ClearGridPoints(This) ) 

#define IStrandGrid_GridBoundingBox(This,box)	\
    ( (This)->lpVtbl -> GridBoundingBox(This,box) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrandGrid_INTERFACE_DEFINED__ */


#ifndef __IStrandGridFiller_INTERFACE_DEFINED__
#define __IStrandGridFiller_INTERFACE_DEFINED__

/* interface IStrandGridFiller */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStrandGridFiller;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E5DF8437-92B8-4d3e-A3F5-71E46214571D")
    IStrandGridFiller : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxStrandCount( 
            /* [retval][out] */ StrandIndexType *count) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMaxStrandFill( 
            /* [retval][out] */ IIndexArray **maxFill) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StrandFill( 
            /* [retval][out] */ IIndexArray **fill) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_StrandFill( 
            /* [in] */ IIndexArray *fill) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveAllStrands( void) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_StrandMover( 
            /* [in] */ StrandGridType gridType,
            /* [in] */ EndType endType,
            /* [in] */ IStrandMover *mover) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStrandMover( 
            /* [out] */ StrandGridType *gridType,
            /* [out] */ EndType *endType,
            /* [out] */ IStrandMover **mover) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VerticalStrandAdjustment( 
            /* [retval][out] */ Float64 *adjust) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VerticalStrandAdjustment( 
            /* [in] */ Float64 adjust) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStrandCount( 
            /* [retval][out] */ StrandIndexType *count) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStrandPositions( 
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StrandIndexToGridIndex( 
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GridIndexToStrandIndex( 
            /* [in] */ GridIndexType gridIndex,
            /* [out] */ StrandIndexType *strandIndex1,
            /* [out] */ StrandIndexType *strandIndex2) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CG( 
            /* [out] */ Float64 *cgx,
            /* [out] */ Float64 *cgy) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StrandBoundingBox( 
            /* [retval][out] */ IRect2d **box) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FilledGridBounds( 
            /* [out] */ Float64 *bottomElev,
            /* [out] */ Float64 *topElev) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RowsWithStrand( 
            /* [retval][out] */ RowIndexType *nRows) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StrandsInRow( 
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ IIndexArray **gridIndexes) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumStrandsInRow( 
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStrandCountEx( 
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ StrandIndexType *count) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStrandPositionsEx( 
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CGEx( 
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *cgx,
            /* [out] */ Float64 *cgy) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StrandBoundingBoxEx( 
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IRect2d **box) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StrandIndexToGridIndexEx( 
            /* [in] */ IIndexArray *fill,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FilledGridBoundsEx( 
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *bottomElev,
            /* [out] */ Float64 *topElev) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStrandDebondCount( 
            /* [in] */ WDebondLocationType loc,
            /* [retval][out] */ StrandIndexType *count) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DebondStrandByGridIndex( 
            /* [in] */ GridIndexType grdIndex,
            /* [in] */ Float64 l1,
            /* [in] */ Float64 l2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDebondedStrandsByGridIndex( 
            /* [retval][out] */ IIndexArray **grdIndexes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDebondLengthByGridIndex( 
            /* [in] */ GridIndexType grdIndex,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *l1,
            /* [out] */ Float64 *l2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDebondLengthByPositionIndex( 
            /* [in] */ StrandIndexType positionIndex,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *l1,
            /* [out] */ Float64 *l2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStrandsDebondedByPositionIndex( 
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 girderLength,
            /* [retval][out] */ IIndexArray **positionIndexes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBondedLengthByPositionIndex( 
            /* [in] */ StrandIndexType positionIndex,
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 girderLength,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *leftBond,
            /* [out] */ Float64 *rightBond) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBondedLengthByGridIndex( 
            /* [in] */ GridIndexType grdIndex,
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 girderLength,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *leftBond,
            /* [out] */ Float64 *rightBond) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StrandDebondInRow( 
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ StrandIndexType *nStrands) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsExteriorStrandDebondedInRow( 
            /* [in] */ RowIndexType rowIndex,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDebondSections( 
            /* [out] */ IDblArray **arrLeft,
            /* [out] */ IDblArray **arrRight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDebondAtLeftSection( 
            /* [in] */ SectionIndexType sectionIdx,
            /* [retval][out] */ IIndexArray **strandIndexes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDebondAtRightSection( 
            /* [in] */ SectionIndexType sectionIdx,
            /* [retval][out] */ IIndexArray **strandIndexes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearDebonding( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStrandGridFillerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStrandGridFiller * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStrandGridFiller * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStrandGridFiller * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxStrandCount )( 
            IStrandGridFiller * This,
            /* [retval][out] */ StrandIndexType *count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMaxStrandFill )( 
            IStrandGridFiller * This,
            /* [retval][out] */ IIndexArray **maxFill);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandFill )( 
            IStrandGridFiller * This,
            /* [retval][out] */ IIndexArray **fill);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StrandFill )( 
            IStrandGridFiller * This,
            /* [in] */ IIndexArray *fill);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllStrands )( 
            IStrandGridFiller * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StrandMover )( 
            IStrandGridFiller * This,
            /* [in] */ StrandGridType gridType,
            /* [in] */ EndType endType,
            /* [in] */ IStrandMover *mover);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStrandMover )( 
            IStrandGridFiller * This,
            /* [out] */ StrandGridType *gridType,
            /* [out] */ EndType *endType,
            /* [out] */ IStrandMover **mover);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VerticalStrandAdjustment )( 
            IStrandGridFiller * This,
            /* [retval][out] */ Float64 *adjust);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VerticalStrandAdjustment )( 
            IStrandGridFiller * This,
            /* [in] */ Float64 adjust);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStrandCount )( 
            IStrandGridFiller * This,
            /* [retval][out] */ StrandIndexType *count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStrandPositions )( 
            IStrandGridFiller * This,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StrandIndexToGridIndex )( 
            IStrandGridFiller * This,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GridIndexToStrandIndex )( 
            IStrandGridFiller * This,
            /* [in] */ GridIndexType gridIndex,
            /* [out] */ StrandIndexType *strandIndex1,
            /* [out] */ StrandIndexType *strandIndex2);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CG )( 
            IStrandGridFiller * This,
            /* [out] */ Float64 *cgx,
            /* [out] */ Float64 *cgy);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandBoundingBox )( 
            IStrandGridFiller * This,
            /* [retval][out] */ IRect2d **box);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FilledGridBounds )( 
            IStrandGridFiller * This,
            /* [out] */ Float64 *bottomElev,
            /* [out] */ Float64 *topElev);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RowsWithStrand )( 
            IStrandGridFiller * This,
            /* [retval][out] */ RowIndexType *nRows);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandsInRow )( 
            IStrandGridFiller * This,
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ IIndexArray **gridIndexes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumStrandsInRow )( 
            IStrandGridFiller * This,
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStrandCountEx )( 
            IStrandGridFiller * This,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ StrandIndexType *count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStrandPositionsEx )( 
            IStrandGridFiller * This,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CGEx )( 
            IStrandGridFiller * This,
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *cgx,
            /* [out] */ Float64 *cgy);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandBoundingBoxEx )( 
            IStrandGridFiller * This,
            /* [in] */ IIndexArray *fill,
            /* [retval][out] */ IRect2d **box);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StrandIndexToGridIndexEx )( 
            IStrandGridFiller * This,
            /* [in] */ IIndexArray *fill,
            /* [in] */ StrandIndexType strandIndex,
            /* [retval][out] */ GridIndexType *gridIndex);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FilledGridBoundsEx )( 
            IStrandGridFiller * This,
            /* [in] */ IIndexArray *fill,
            /* [out] */ Float64 *bottomElev,
            /* [out] */ Float64 *topElev);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStrandDebondCount )( 
            IStrandGridFiller * This,
            /* [in] */ WDebondLocationType loc,
            /* [retval][out] */ StrandIndexType *count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DebondStrandByGridIndex )( 
            IStrandGridFiller * This,
            /* [in] */ GridIndexType grdIndex,
            /* [in] */ Float64 l1,
            /* [in] */ Float64 l2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDebondedStrandsByGridIndex )( 
            IStrandGridFiller * This,
            /* [retval][out] */ IIndexArray **grdIndexes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDebondLengthByGridIndex )( 
            IStrandGridFiller * This,
            /* [in] */ GridIndexType grdIndex,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *l1,
            /* [out] */ Float64 *l2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDebondLengthByPositionIndex )( 
            IStrandGridFiller * This,
            /* [in] */ StrandIndexType positionIndex,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *l1,
            /* [out] */ Float64 *l2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStrandsDebondedByPositionIndex )( 
            IStrandGridFiller * This,
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 girderLength,
            /* [retval][out] */ IIndexArray **positionIndexes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBondedLengthByPositionIndex )( 
            IStrandGridFiller * This,
            /* [in] */ StrandIndexType positionIndex,
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 girderLength,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *leftBond,
            /* [out] */ Float64 *rightBond);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBondedLengthByGridIndex )( 
            IStrandGridFiller * This,
            /* [in] */ GridIndexType grdIndex,
            /* [in] */ Float64 distFromStart,
            /* [in] */ Float64 girderLength,
            /* [out] */ Float64 *YCoord,
            /* [out] */ Float64 *leftBond,
            /* [out] */ Float64 *rightBond);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandDebondInRow )( 
            IStrandGridFiller * This,
            /* [in] */ RowIndexType rowIdx,
            /* [retval][out] */ StrandIndexType *nStrands);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsExteriorStrandDebondedInRow )( 
            IStrandGridFiller * This,
            /* [in] */ RowIndexType rowIndex,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDebondSections )( 
            IStrandGridFiller * This,
            /* [out] */ IDblArray **arrLeft,
            /* [out] */ IDblArray **arrRight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDebondAtLeftSection )( 
            IStrandGridFiller * This,
            /* [in] */ SectionIndexType sectionIdx,
            /* [retval][out] */ IIndexArray **strandIndexes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDebondAtRightSection )( 
            IStrandGridFiller * This,
            /* [in] */ SectionIndexType sectionIdx,
            /* [retval][out] */ IIndexArray **strandIndexes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearDebonding )( 
            IStrandGridFiller * This);
        
        END_INTERFACE
    } IStrandGridFillerVtbl;

    interface IStrandGridFiller
    {
        CONST_VTBL struct IStrandGridFillerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrandGridFiller_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStrandGridFiller_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStrandGridFiller_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStrandGridFiller_get_MaxStrandCount(This,count)	\
    ( (This)->lpVtbl -> get_MaxStrandCount(This,count) ) 

#define IStrandGridFiller_GetMaxStrandFill(This,maxFill)	\
    ( (This)->lpVtbl -> GetMaxStrandFill(This,maxFill) ) 

#define IStrandGridFiller_get_StrandFill(This,fill)	\
    ( (This)->lpVtbl -> get_StrandFill(This,fill) ) 

#define IStrandGridFiller_putref_StrandFill(This,fill)	\
    ( (This)->lpVtbl -> putref_StrandFill(This,fill) ) 

#define IStrandGridFiller_RemoveAllStrands(This)	\
    ( (This)->lpVtbl -> RemoveAllStrands(This) ) 

#define IStrandGridFiller_putref_StrandMover(This,gridType,endType,mover)	\
    ( (This)->lpVtbl -> putref_StrandMover(This,gridType,endType,mover) ) 

#define IStrandGridFiller_GetStrandMover(This,gridType,endType,mover)	\
    ( (This)->lpVtbl -> GetStrandMover(This,gridType,endType,mover) ) 

#define IStrandGridFiller_get_VerticalStrandAdjustment(This,adjust)	\
    ( (This)->lpVtbl -> get_VerticalStrandAdjustment(This,adjust) ) 

#define IStrandGridFiller_put_VerticalStrandAdjustment(This,adjust)	\
    ( (This)->lpVtbl -> put_VerticalStrandAdjustment(This,adjust) ) 

#define IStrandGridFiller_GetStrandCount(This,count)	\
    ( (This)->lpVtbl -> GetStrandCount(This,count) ) 

#define IStrandGridFiller_GetStrandPositions(This,points)	\
    ( (This)->lpVtbl -> GetStrandPositions(This,points) ) 

#define IStrandGridFiller_StrandIndexToGridIndex(This,strandIndex,gridIndex)	\
    ( (This)->lpVtbl -> StrandIndexToGridIndex(This,strandIndex,gridIndex) ) 

#define IStrandGridFiller_GridIndexToStrandIndex(This,gridIndex,strandIndex1,strandIndex2)	\
    ( (This)->lpVtbl -> GridIndexToStrandIndex(This,gridIndex,strandIndex1,strandIndex2) ) 

#define IStrandGridFiller_get_CG(This,cgx,cgy)	\
    ( (This)->lpVtbl -> get_CG(This,cgx,cgy) ) 

#define IStrandGridFiller_get_StrandBoundingBox(This,box)	\
    ( (This)->lpVtbl -> get_StrandBoundingBox(This,box) ) 

#define IStrandGridFiller_get_FilledGridBounds(This,bottomElev,topElev)	\
    ( (This)->lpVtbl -> get_FilledGridBounds(This,bottomElev,topElev) ) 

#define IStrandGridFiller_get_RowsWithStrand(This,nRows)	\
    ( (This)->lpVtbl -> get_RowsWithStrand(This,nRows) ) 

#define IStrandGridFiller_get_StrandsInRow(This,rowIdx,gridIndexes)	\
    ( (This)->lpVtbl -> get_StrandsInRow(This,rowIdx,gridIndexes) ) 

#define IStrandGridFiller_get_NumStrandsInRow(This,rowIdx,nStrands)	\
    ( (This)->lpVtbl -> get_NumStrandsInRow(This,rowIdx,nStrands) ) 

#define IStrandGridFiller_GetStrandCountEx(This,fill,count)	\
    ( (This)->lpVtbl -> GetStrandCountEx(This,fill,count) ) 

#define IStrandGridFiller_GetStrandPositionsEx(This,fill,points)	\
    ( (This)->lpVtbl -> GetStrandPositionsEx(This,fill,points) ) 

#define IStrandGridFiller_get_CGEx(This,fill,cgx,cgy)	\
    ( (This)->lpVtbl -> get_CGEx(This,fill,cgx,cgy) ) 

#define IStrandGridFiller_get_StrandBoundingBoxEx(This,fill,box)	\
    ( (This)->lpVtbl -> get_StrandBoundingBoxEx(This,fill,box) ) 

#define IStrandGridFiller_StrandIndexToGridIndexEx(This,fill,strandIndex,gridIndex)	\
    ( (This)->lpVtbl -> StrandIndexToGridIndexEx(This,fill,strandIndex,gridIndex) ) 

#define IStrandGridFiller_get_FilledGridBoundsEx(This,fill,bottomElev,topElev)	\
    ( (This)->lpVtbl -> get_FilledGridBoundsEx(This,fill,bottomElev,topElev) ) 

#define IStrandGridFiller_GetStrandDebondCount(This,loc,count)	\
    ( (This)->lpVtbl -> GetStrandDebondCount(This,loc,count) ) 

#define IStrandGridFiller_DebondStrandByGridIndex(This,grdIndex,l1,l2)	\
    ( (This)->lpVtbl -> DebondStrandByGridIndex(This,grdIndex,l1,l2) ) 

#define IStrandGridFiller_GetDebondedStrandsByGridIndex(This,grdIndexes)	\
    ( (This)->lpVtbl -> GetDebondedStrandsByGridIndex(This,grdIndexes) ) 

#define IStrandGridFiller_GetDebondLengthByGridIndex(This,grdIndex,YCoord,l1,l2)	\
    ( (This)->lpVtbl -> GetDebondLengthByGridIndex(This,grdIndex,YCoord,l1,l2) ) 

#define IStrandGridFiller_GetDebondLengthByPositionIndex(This,positionIndex,YCoord,l1,l2)	\
    ( (This)->lpVtbl -> GetDebondLengthByPositionIndex(This,positionIndex,YCoord,l1,l2) ) 

#define IStrandGridFiller_GetStrandsDebondedByPositionIndex(This,distFromStart,girderLength,positionIndexes)	\
    ( (This)->lpVtbl -> GetStrandsDebondedByPositionIndex(This,distFromStart,girderLength,positionIndexes) ) 

#define IStrandGridFiller_GetBondedLengthByPositionIndex(This,positionIndex,distFromStart,girderLength,YCoord,leftBond,rightBond)	\
    ( (This)->lpVtbl -> GetBondedLengthByPositionIndex(This,positionIndex,distFromStart,girderLength,YCoord,leftBond,rightBond) ) 

#define IStrandGridFiller_GetBondedLengthByGridIndex(This,grdIndex,distFromStart,girderLength,YCoord,leftBond,rightBond)	\
    ( (This)->lpVtbl -> GetBondedLengthByGridIndex(This,grdIndex,distFromStart,girderLength,YCoord,leftBond,rightBond) ) 

#define IStrandGridFiller_get_StrandDebondInRow(This,rowIdx,nStrands)	\
    ( (This)->lpVtbl -> get_StrandDebondInRow(This,rowIdx,nStrands) ) 

#define IStrandGridFiller_IsExteriorStrandDebondedInRow(This,rowIndex,bResult)	\
    ( (This)->lpVtbl -> IsExteriorStrandDebondedInRow(This,rowIndex,bResult) ) 

#define IStrandGridFiller_GetDebondSections(This,arrLeft,arrRight)	\
    ( (This)->lpVtbl -> GetDebondSections(This,arrLeft,arrRight) ) 

#define IStrandGridFiller_GetDebondAtLeftSection(This,sectionIdx,strandIndexes)	\
    ( (This)->lpVtbl -> GetDebondAtLeftSection(This,sectionIdx,strandIndexes) ) 

#define IStrandGridFiller_GetDebondAtRightSection(This,sectionIdx,strandIndexes)	\
    ( (This)->lpVtbl -> GetDebondAtRightSection(This,sectionIdx,strandIndexes) ) 

#define IStrandGridFiller_ClearDebonding(This)	\
    ( (This)->lpVtbl -> ClearDebonding(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrandGridFiller_INTERFACE_DEFINED__ */


#ifndef __IStrandFillTool_INTERFACE_DEFINED__
#define __IStrandFillTool_INTERFACE_DEFINED__

/* interface IStrandFillTool */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStrandFillTool;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DBD342C8-9EA4-408c-9CF5-27744DE0CA60")
    IStrandFillTool : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ComputeHarpedStrandMaxFill( 
            /* [in] */ IStrandGridFiller *pEndGridFiller,
            /* [in] */ IStrandGridFiller *pHPGridFiller,
            /* [out] */ StrandIndexType *pMaxStrandCount,
            /* [out] */ IIndexArray **ppStrandFill) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStrandFillToolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStrandFillTool * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStrandFillTool * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStrandFillTool * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeHarpedStrandMaxFill )( 
            IStrandFillTool * This,
            /* [in] */ IStrandGridFiller *pEndGridFiller,
            /* [in] */ IStrandGridFiller *pHPGridFiller,
            /* [out] */ StrandIndexType *pMaxStrandCount,
            /* [out] */ IIndexArray **ppStrandFill);
        
        END_INTERFACE
    } IStrandFillToolVtbl;

    interface IStrandFillTool
    {
        CONST_VTBL struct IStrandFillToolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrandFillTool_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStrandFillTool_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStrandFillTool_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStrandFillTool_ComputeHarpedStrandMaxFill(This,pEndGridFiller,pHPGridFiller,pMaxStrandCount,ppStrandFill)	\
    ( (This)->lpVtbl -> ComputeHarpedStrandMaxFill(This,pEndGridFiller,pHPGridFiller,pMaxStrandCount,ppStrandFill) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrandFillTool_INTERFACE_DEFINED__ */


#ifndef __IBridgeGeometryTool_INTERFACE_DEFINED__
#define __IBridgeGeometryTool_INTERFACE_DEFINED__

/* interface IBridgeGeometryTool */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IBridgeGeometryTool;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C5CBE002-A27E-408c-91DF-56A6AF5346BC")
    IBridgeGeometryTool : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PointBySSMbr( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 distFromStartOfSSMbr,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PointBySegment( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StationAndOffsetBySSMbr( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 distFromStartOfSSMbr,
            /* [out] */ IStation **station,
            /* [out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StationAndOffsetBySegment( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [out] */ IStation **station,
            /* [out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GirderPathOffset( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GirderPathPoint( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ VARIANT varStation,
            /* [in] */ VARIANT varDirection,
            /* [in] */ VARIANT_BOOL vbProject,
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckEdgePoint( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckEdgePoints( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [in] */ CollectionIndexType nPoints,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CurbOffset( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [out] */ IStation **ppOffsetStation,
            /* [out] */ Float64 *pOffset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckOffset( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [out] */ IStation **ppOffsetStation,
            /* [out] */ Float64 *pOffset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckOverhang( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [retval][out] */ Float64 *pOverhang) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckOverhangBySSMbr( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 distFromStartOfSSMbr,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [retval][out] */ Float64 *pOverhang) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckOverhangBySegment( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [retval][out] */ Float64 *pOverhang) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GirderSpacingBySSMbr( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 distFromStartOfSSMbr,
            /* [in] */ GirderIDType otherSSMbrID,
            /* [retval][out] */ Float64 *pSpacing) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GirderSpacingBySegment( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType otherSSMbrID,
            /* [retval][out] */ Float64 *pSpacing) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InteriorCurbOffset( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [out] */ IStation **ppOffsetStation,
            /* [out] */ Float64 *pOffset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CurbLinePoint( 
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [retval][out] */ IPoint2d **point) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBridgeGeometryToolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBridgeGeometryTool * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBridgeGeometryTool * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBridgeGeometryTool * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointBySSMbr )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 distFromStartOfSSMbr,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointBySegment )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StationAndOffsetBySSMbr )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 distFromStartOfSSMbr,
            /* [out] */ IStation **station,
            /* [out] */ Float64 *offset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StationAndOffsetBySegment )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [out] */ IStation **station,
            /* [out] */ Float64 *offset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GirderPathOffset )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ Float64 *offset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GirderPathPoint )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ VARIANT varStation,
            /* [in] */ VARIANT varDirection,
            /* [in] */ VARIANT_BOOL vbProject,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckEdgePoint )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckEdgePoints )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [in] */ CollectionIndexType nPoints,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CurbOffset )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [out] */ IStation **ppOffsetStation,
            /* [out] */ Float64 *pOffset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckOffset )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [out] */ IStation **ppOffsetStation,
            /* [out] */ Float64 *pOffset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckOverhang )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [retval][out] */ Float64 *pOverhang);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckOverhangBySSMbr )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 distFromStartOfSSMbr,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [retval][out] */ Float64 *pOverhang);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckOverhangBySegment )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [retval][out] */ Float64 *pOverhang);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GirderSpacingBySSMbr )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ Float64 distFromStartOfSSMbr,
            /* [in] */ GirderIDType otherSSMbrID,
            /* [retval][out] */ Float64 *pSpacing);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GirderSpacingBySegment )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ GirderIDType ssMbrID,
            /* [in] */ SegmentIndexType segIdx,
            /* [in] */ Float64 Xs,
            /* [in] */ GirderIDType otherSSMbrID,
            /* [retval][out] */ Float64 *pSpacing);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InteriorCurbOffset )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [out] */ IStation **ppOffsetStation,
            /* [out] */ Float64 *pOffset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CurbLinePoint )( 
            IBridgeGeometryTool * This,
            /* [in] */ /* external definition not present */ IGenericBridge *bridge,
            /* [in] */ Float64 station,
            /* [in] */ IDirection *direction,
            /* [in] */ /* external definition not present */ DirectionType side,
            /* [retval][out] */ IPoint2d **point);
        
        END_INTERFACE
    } IBridgeGeometryToolVtbl;

    interface IBridgeGeometryTool
    {
        CONST_VTBL struct IBridgeGeometryToolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBridgeGeometryTool_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBridgeGeometryTool_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBridgeGeometryTool_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBridgeGeometryTool_PointBySSMbr(This,bridge,ssMbrID,distFromStartOfSSMbr,point)	\
    ( (This)->lpVtbl -> PointBySSMbr(This,bridge,ssMbrID,distFromStartOfSSMbr,point) ) 

#define IBridgeGeometryTool_PointBySegment(This,bridge,ssMbrID,segIdx,Xs,point)	\
    ( (This)->lpVtbl -> PointBySegment(This,bridge,ssMbrID,segIdx,Xs,point) ) 

#define IBridgeGeometryTool_StationAndOffsetBySSMbr(This,bridge,ssMbrID,distFromStartOfSSMbr,station,offset)	\
    ( (This)->lpVtbl -> StationAndOffsetBySSMbr(This,bridge,ssMbrID,distFromStartOfSSMbr,station,offset) ) 

#define IBridgeGeometryTool_StationAndOffsetBySegment(This,bridge,ssMbrID,segIdx,Xs,station,offset)	\
    ( (This)->lpVtbl -> StationAndOffsetBySegment(This,bridge,ssMbrID,segIdx,Xs,station,offset) ) 

#define IBridgeGeometryTool_GirderPathOffset(This,bridge,ssMbrID,segIdx,varStation,offset)	\
    ( (This)->lpVtbl -> GirderPathOffset(This,bridge,ssMbrID,segIdx,varStation,offset) ) 

#define IBridgeGeometryTool_GirderPathPoint(This,bridge,ssMbrID,segIdx,varStation,varDirection,vbProject,ppPoint)	\
    ( (This)->lpVtbl -> GirderPathPoint(This,bridge,ssMbrID,segIdx,varStation,varDirection,vbProject,ppPoint) ) 

#define IBridgeGeometryTool_DeckEdgePoint(This,bridge,station,direction,side,point)	\
    ( (This)->lpVtbl -> DeckEdgePoint(This,bridge,station,direction,side,point) ) 

#define IBridgeGeometryTool_DeckEdgePoints(This,bridge,side,nPoints,points)	\
    ( (This)->lpVtbl -> DeckEdgePoints(This,bridge,side,nPoints,points) ) 

#define IBridgeGeometryTool_CurbOffset(This,bridge,station,direction,side,ppOffsetStation,pOffset)	\
    ( (This)->lpVtbl -> CurbOffset(This,bridge,station,direction,side,ppOffsetStation,pOffset) ) 

#define IBridgeGeometryTool_DeckOffset(This,bridge,station,direction,side,ppOffsetStation,pOffset)	\
    ( (This)->lpVtbl -> DeckOffset(This,bridge,station,direction,side,ppOffsetStation,pOffset) ) 

#define IBridgeGeometryTool_DeckOverhang(This,bridge,station,ssMbrID,direction,side,pOverhang)	\
    ( (This)->lpVtbl -> DeckOverhang(This,bridge,station,ssMbrID,direction,side,pOverhang) ) 

#define IBridgeGeometryTool_DeckOverhangBySSMbr(This,bridge,ssMbrID,distFromStartOfSSMbr,direction,side,pOverhang)	\
    ( (This)->lpVtbl -> DeckOverhangBySSMbr(This,bridge,ssMbrID,distFromStartOfSSMbr,direction,side,pOverhang) ) 

#define IBridgeGeometryTool_DeckOverhangBySegment(This,bridge,ssMbrID,segIdx,Xs,direction,side,pOverhang)	\
    ( (This)->lpVtbl -> DeckOverhangBySegment(This,bridge,ssMbrID,segIdx,Xs,direction,side,pOverhang) ) 

#define IBridgeGeometryTool_GirderSpacingBySSMbr(This,bridge,ssMbrID,distFromStartOfSSMbr,otherSSMbrID,pSpacing)	\
    ( (This)->lpVtbl -> GirderSpacingBySSMbr(This,bridge,ssMbrID,distFromStartOfSSMbr,otherSSMbrID,pSpacing) ) 

#define IBridgeGeometryTool_GirderSpacingBySegment(This,bridge,ssMbrID,segIdx,Xs,otherSSMbrID,pSpacing)	\
    ( (This)->lpVtbl -> GirderSpacingBySegment(This,bridge,ssMbrID,segIdx,Xs,otherSSMbrID,pSpacing) ) 

#define IBridgeGeometryTool_InteriorCurbOffset(This,bridge,station,direction,side,ppOffsetStation,pOffset)	\
    ( (This)->lpVtbl -> InteriorCurbOffset(This,bridge,station,direction,side,ppOffsetStation,pOffset) ) 

#define IBridgeGeometryTool_CurbLinePoint(This,bridge,station,direction,side,point)	\
    ( (This)->lpVtbl -> CurbLinePoint(This,bridge,station,direction,side,point) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBridgeGeometryTool_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_FlexRebarLayoutItem;

#ifdef __cplusplus

class DECLSPEC_UUID("8B4B8193-D5C8-4e1f-86D1-D7044859B9CC")
FlexRebarLayoutItem;
#endif

EXTERN_C const CLSID CLSID_EffectiveFlangeWidthDetails;

#ifdef __cplusplus

class DECLSPEC_UUID("7DDC7A24-05FA-4565-92AC-4FFD54D5063D")
EffectiveFlangeWidthDetails;
#endif

EXTERN_C const CLSID CLSID_EffectiveFlangeWidthTool;

#ifdef __cplusplus

class DECLSPEC_UUID("7AF06A24-3EF5-433B-9A03-B22A8404048B")
EffectiveFlangeWidthTool;
#endif

EXTERN_C const CLSID CLSID_SectionCutTool;

#ifdef __cplusplus

class DECLSPEC_UUID("88738282-9CE8-4553-BC7E-4DB1DF3D8809")
SectionCutTool;
#endif

EXTERN_C const CLSID CLSID_PrecastGirder;

#ifdef __cplusplus

class DECLSPEC_UUID("6E8068AB-ABC2-4cae-A31B-74ABD7500570")
PrecastGirder;
#endif

EXTERN_C const CLSID CLSID_BridgeGeometryTool;

#ifdef __cplusplus

class DECLSPEC_UUID("77B0384B-5C9D-46ac-A8B6-AA8ADA58B37D")
BridgeGeometryTool;
#endif

EXTERN_C const CLSID CLSID_StrandGrid;

#ifdef __cplusplus

class DECLSPEC_UUID("A547E2F5-BE84-49F9-846E-2A5B2C2FD53F")
StrandGrid;
#endif

EXTERN_C const CLSID CLSID_StrandFillTool;

#ifdef __cplusplus

class DECLSPEC_UUID("A757985C-CC7F-4789-B3F3-03BCCED77970")
StrandFillTool;
#endif

EXTERN_C const CLSID CLSID_BridgeDeckRebarLayout;

#ifdef __cplusplus

class DECLSPEC_UUID("2C4F5781-2FD5-4fcc-AC8F-E8CD9C324066")
BridgeDeckRebarLayout;
#endif
#endif /* __WBFLGenericBridgeTools_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


