

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Jun 23 11:25:39 2017
 */
/* Compiler settings for ..\Include\WBFLBridgeGeometry.idl:
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __WBFLBridgeGeometry_h__
#define __WBFLBridgeGeometry_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPierLine_FWD_DEFINED__
#define __IPierLine_FWD_DEFINED__
typedef interface IPierLine IPierLine;

#endif 	/* __IPierLine_FWD_DEFINED__ */


#ifndef __IEnumPierLines_FWD_DEFINED__
#define __IEnumPierLines_FWD_DEFINED__
typedef interface IEnumPierLines IEnumPierLines;

#endif 	/* __IEnumPierLines_FWD_DEFINED__ */


#ifndef __IPierLineCollection_FWD_DEFINED__
#define __IPierLineCollection_FWD_DEFINED__
typedef interface IPierLineCollection IPierLineCollection;

#endif 	/* __IPierLineCollection_FWD_DEFINED__ */


#ifndef __ILayoutLineFactory_FWD_DEFINED__
#define __ILayoutLineFactory_FWD_DEFINED__
typedef interface ILayoutLineFactory ILayoutLineFactory;

#endif 	/* __ILayoutLineFactory_FWD_DEFINED__ */


#ifndef __IAlignmentOffsetLayoutLineFactory_FWD_DEFINED__
#define __IAlignmentOffsetLayoutLineFactory_FWD_DEFINED__
typedef interface IAlignmentOffsetLayoutLineFactory IAlignmentOffsetLayoutLineFactory;

#endif 	/* __IAlignmentOffsetLayoutLineFactory_FWD_DEFINED__ */


#ifndef __ISimpleLayoutLineFactory_FWD_DEFINED__
#define __ISimpleLayoutLineFactory_FWD_DEFINED__
typedef interface ISimpleLayoutLineFactory ISimpleLayoutLineFactory;

#endif 	/* __ISimpleLayoutLineFactory_FWD_DEFINED__ */


#ifndef __IUniformSpacingLayoutLineFactory_FWD_DEFINED__
#define __IUniformSpacingLayoutLineFactory_FWD_DEFINED__
typedef interface IUniformSpacingLayoutLineFactory IUniformSpacingLayoutLineFactory;

#endif 	/* __IUniformSpacingLayoutLineFactory_FWD_DEFINED__ */


#ifndef __IGirderLineFactory_FWD_DEFINED__
#define __IGirderLineFactory_FWD_DEFINED__
typedef interface IGirderLineFactory IGirderLineFactory;

#endif 	/* __IGirderLineFactory_FWD_DEFINED__ */


#ifndef __ISingleGirderLineFactory_FWD_DEFINED__
#define __ISingleGirderLineFactory_FWD_DEFINED__
typedef interface ISingleGirderLineFactory ISingleGirderLineFactory;

#endif 	/* __ISingleGirderLineFactory_FWD_DEFINED__ */


#ifndef __ISimpleGirderLineFactory_FWD_DEFINED__
#define __ISimpleGirderLineFactory_FWD_DEFINED__
typedef interface ISimpleGirderLineFactory ISimpleGirderLineFactory;

#endif 	/* __ISimpleGirderLineFactory_FWD_DEFINED__ */


#ifndef __IGirderLine_FWD_DEFINED__
#define __IGirderLine_FWD_DEFINED__
typedef interface IGirderLine IGirderLine;

#endif 	/* __IGirderLine_FWD_DEFINED__ */


#ifndef __IDiaphragmLineFactory_FWD_DEFINED__
#define __IDiaphragmLineFactory_FWD_DEFINED__
typedef interface IDiaphragmLineFactory IDiaphragmLineFactory;

#endif 	/* __IDiaphragmLineFactory_FWD_DEFINED__ */


#ifndef __ISingleDiaphragmLineFactory_FWD_DEFINED__
#define __ISingleDiaphragmLineFactory_FWD_DEFINED__
typedef interface ISingleDiaphragmLineFactory ISingleDiaphragmLineFactory;

#endif 	/* __ISingleDiaphragmLineFactory_FWD_DEFINED__ */


#ifndef __IThroughPointDiaphragmLineFactory_FWD_DEFINED__
#define __IThroughPointDiaphragmLineFactory_FWD_DEFINED__
typedef interface IThroughPointDiaphragmLineFactory IThroughPointDiaphragmLineFactory;

#endif 	/* __IThroughPointDiaphragmLineFactory_FWD_DEFINED__ */


#ifndef __IEqualSpaceDiaphragmLineFactory_FWD_DEFINED__
#define __IEqualSpaceDiaphragmLineFactory_FWD_DEFINED__
typedef interface IEqualSpaceDiaphragmLineFactory IEqualSpaceDiaphragmLineFactory;

#endif 	/* __IEqualSpaceDiaphragmLineFactory_FWD_DEFINED__ */


#ifndef __IDiaphragmLine_FWD_DEFINED__
#define __IDiaphragmLine_FWD_DEFINED__
typedef interface IDiaphragmLine IDiaphragmLine;

#endif 	/* __IDiaphragmLine_FWD_DEFINED__ */


#ifndef __IDeckBoundary_FWD_DEFINED__
#define __IDeckBoundary_FWD_DEFINED__
typedef interface IDeckBoundary IDeckBoundary;

#endif 	/* __IDeckBoundary_FWD_DEFINED__ */


#ifndef __IDeckBoundaryFactory_FWD_DEFINED__
#define __IDeckBoundaryFactory_FWD_DEFINED__
typedef interface IDeckBoundaryFactory IDeckBoundaryFactory;

#endif 	/* __IDeckBoundaryFactory_FWD_DEFINED__ */


#ifndef __ISimpleDeckBoundaryFactory_FWD_DEFINED__
#define __ISimpleDeckBoundaryFactory_FWD_DEFINED__
typedef interface ISimpleDeckBoundaryFactory ISimpleDeckBoundaryFactory;

#endif 	/* __ISimpleDeckBoundaryFactory_FWD_DEFINED__ */


#ifndef __IBridgeGeometry_FWD_DEFINED__
#define __IBridgeGeometry_FWD_DEFINED__
typedef interface IBridgeGeometry IBridgeGeometry;

#endif 	/* __IBridgeGeometry_FWD_DEFINED__ */


#ifndef __BridgeGeometry_FWD_DEFINED__
#define __BridgeGeometry_FWD_DEFINED__

#ifdef __cplusplus
typedef class BridgeGeometry BridgeGeometry;
#else
typedef struct BridgeGeometry BridgeGeometry;
#endif /* __cplusplus */

#endif 	/* __BridgeGeometry_FWD_DEFINED__ */


#ifndef __PierLine_FWD_DEFINED__
#define __PierLine_FWD_DEFINED__

#ifdef __cplusplus
typedef class PierLine PierLine;
#else
typedef struct PierLine PierLine;
#endif /* __cplusplus */

#endif 	/* __PierLine_FWD_DEFINED__ */


#ifndef __PierLineCollection_FWD_DEFINED__
#define __PierLineCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class PierLineCollection PierLineCollection;
#else
typedef struct PierLineCollection PierLineCollection;
#endif /* __cplusplus */

#endif 	/* __PierLineCollection_FWD_DEFINED__ */


#ifndef __AlignmentOffsetLayoutLineFactory_FWD_DEFINED__
#define __AlignmentOffsetLayoutLineFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class AlignmentOffsetLayoutLineFactory AlignmentOffsetLayoutLineFactory;
#else
typedef struct AlignmentOffsetLayoutLineFactory AlignmentOffsetLayoutLineFactory;
#endif /* __cplusplus */

#endif 	/* __AlignmentOffsetLayoutLineFactory_FWD_DEFINED__ */


#ifndef __SimpleLayoutLineFactory_FWD_DEFINED__
#define __SimpleLayoutLineFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleLayoutLineFactory SimpleLayoutLineFactory;
#else
typedef struct SimpleLayoutLineFactory SimpleLayoutLineFactory;
#endif /* __cplusplus */

#endif 	/* __SimpleLayoutLineFactory_FWD_DEFINED__ */


#ifndef __UniformSpacingLayoutLineFactory_FWD_DEFINED__
#define __UniformSpacingLayoutLineFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class UniformSpacingLayoutLineFactory UniformSpacingLayoutLineFactory;
#else
typedef struct UniformSpacingLayoutLineFactory UniformSpacingLayoutLineFactory;
#endif /* __cplusplus */

#endif 	/* __UniformSpacingLayoutLineFactory_FWD_DEFINED__ */


#ifndef __GirderLine_FWD_DEFINED__
#define __GirderLine_FWD_DEFINED__

#ifdef __cplusplus
typedef class GirderLine GirderLine;
#else
typedef struct GirderLine GirderLine;
#endif /* __cplusplus */

#endif 	/* __GirderLine_FWD_DEFINED__ */


#ifndef __DiaphragmLine_FWD_DEFINED__
#define __DiaphragmLine_FWD_DEFINED__

#ifdef __cplusplus
typedef class DiaphragmLine DiaphragmLine;
#else
typedef struct DiaphragmLine DiaphragmLine;
#endif /* __cplusplus */

#endif 	/* __DiaphragmLine_FWD_DEFINED__ */


#ifndef __DeckBoundary_FWD_DEFINED__
#define __DeckBoundary_FWD_DEFINED__

#ifdef __cplusplus
typedef class DeckBoundary DeckBoundary;
#else
typedef struct DeckBoundary DeckBoundary;
#endif /* __cplusplus */

#endif 	/* __DeckBoundary_FWD_DEFINED__ */


#ifndef __SingleGirderLineFactory_FWD_DEFINED__
#define __SingleGirderLineFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class SingleGirderLineFactory SingleGirderLineFactory;
#else
typedef struct SingleGirderLineFactory SingleGirderLineFactory;
#endif /* __cplusplus */

#endif 	/* __SingleGirderLineFactory_FWD_DEFINED__ */


#ifndef __SimpleGirderLineFactory_FWD_DEFINED__
#define __SimpleGirderLineFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleGirderLineFactory SimpleGirderLineFactory;
#else
typedef struct SimpleGirderLineFactory SimpleGirderLineFactory;
#endif /* __cplusplus */

#endif 	/* __SimpleGirderLineFactory_FWD_DEFINED__ */


#ifndef __EqualSpaceDiaphragmLineFactory_FWD_DEFINED__
#define __EqualSpaceDiaphragmLineFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class EqualSpaceDiaphragmLineFactory EqualSpaceDiaphragmLineFactory;
#else
typedef struct EqualSpaceDiaphragmLineFactory EqualSpaceDiaphragmLineFactory;
#endif /* __cplusplus */

#endif 	/* __EqualSpaceDiaphragmLineFactory_FWD_DEFINED__ */


#ifndef __SingleDiaphragmLineFactory_FWD_DEFINED__
#define __SingleDiaphragmLineFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class SingleDiaphragmLineFactory SingleDiaphragmLineFactory;
#else
typedef struct SingleDiaphragmLineFactory SingleDiaphragmLineFactory;
#endif /* __cplusplus */

#endif 	/* __SingleDiaphragmLineFactory_FWD_DEFINED__ */


#ifndef __ThroughPointDiaphragmLineFactory_FWD_DEFINED__
#define __ThroughPointDiaphragmLineFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class ThroughPointDiaphragmLineFactory ThroughPointDiaphragmLineFactory;
#else
typedef struct ThroughPointDiaphragmLineFactory ThroughPointDiaphragmLineFactory;
#endif /* __cplusplus */

#endif 	/* __ThroughPointDiaphragmLineFactory_FWD_DEFINED__ */


#ifndef __SimpleDeckBoundaryFactory_FWD_DEFINED__
#define __SimpleDeckBoundaryFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleDeckBoundaryFactory SimpleDeckBoundaryFactory;
#else
typedef struct SimpleDeckBoundaryFactory SimpleDeckBoundaryFactory;
#endif /* __cplusplus */

#endif 	/* __SimpleDeckBoundaryFactory_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLCogo.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLBridgeGeometry_0000_0000 */
/* [local] */ 

#define BRIDGEGEOMETRY_E_INITIALIZATION     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,512)
#define BRIDGEGEOMETRY_E_INVALIDSTATION     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,513)
#define BRIDGEGEOMETRY_E_ID                 MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,514)
typedef IDType LineIDType;

typedef IDType PathIDType;


typedef /* [public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("621DA6BE-19C3-49FE-9227-95F988D8A6BF") 
enum __MIDL___MIDL_itf_WBFLBridgeGeometry_0000_0000_0001
    {
        glChord	= 0,
        glPath	= 1
    } 	GirderLineType;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("FC45D43A-BE9D-4725-8913-E2B2947CEC73") 
enum __MIDL___MIDL_itf_WBFLBridgeGeometry_0000_0000_0002
    {
        pfBack	= 0,
        pfAhead	= 1
    } 	PierFaceType;

typedef /* [public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("45561BA8-9178-4AEF-8B2B-C25BA2D09E1B") 
enum __MIDL___MIDL_itf_WBFLBridgeGeometry_0000_0000_0003
    {
        setPier	= 0,
        setLayout	= ( setPier + 1 ) 
    } 	DeckBoundaryEdgeType;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("A8F6552D-A5A9-40DB-9562-B33623CC9C31") 
enum __MIDL___MIDL_itf_WBFLBridgeGeometry_0000_0000_0004
    {
        mtAlongItem	= 0,
        mtNormal	= 1
    } 	MeasurementType;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("A884BF5A-0C8F-4D89-BDA7-114E6944A9D0") 
enum __MIDL___MIDL_itf_WBFLBridgeGeometry_0000_0000_0005
    {
        mlPierLine	= 0,
        mlCenterlineBearing	= 1
    } 	MeasurementLocation;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("834FAD6D-79ED-4253-A49C-8B3CB270C899") 
enum __MIDL___MIDL_itf_WBFLBridgeGeometry_0000_0000_0006
    {
        etStart	= 0,
        etEnd	= 1
    } 	EndType;

typedef /* [public][public][public][public][public][public][public][public][uuid][helpstring][public] */  DECLSPEC_UUID("73C1F1F8-36DE-4042-A9A5-A1CC07F1C323") 
enum __MIDL___MIDL_itf_WBFLBridgeGeometry_0000_0000_0007
    {
        stLeft	= 0,
        stRight	= 1
    } 	SideType;



extern RPC_IF_HANDLE __MIDL_itf_WBFLBridgeGeometry_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLBridgeGeometry_0000_0000_v0_0_s_ifspec;

#ifndef __IPierLine_INTERFACE_DEFINED__
#define __IPierLine_INTERFACE_DEFINED__

/* interface IPierLine */
/* [unique][helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPierLine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("04086070-2A58-4557-A320-649C615652FA")
    IPierLine : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AlignmentID( 
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Station( 
            /* [retval][out] */ IStation **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ IDirection **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Normal( 
            /* [retval][out] */ IDirection **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Skew( 
            /* [retval][out] */ IAngle **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ PierIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ PierIDType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NextPierLine( 
            /* [retval][out] */ IPierLine **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PrevPierLine( 
            /* [retval][out] */ IPierLine **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingOffset( 
            /* [in] */ PierFaceType pierFace,
            /* [retval][out] */ Float64 *brgOffset) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BearingOffset( 
            /* [in] */ PierFaceType pierFace,
            /* [in] */ Float64 brgOffset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingOffsetMeasurementType( 
            /* [in] */ PierFaceType pierFace,
            /* [retval][out] */ MeasurementType *measure) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BearingOffsetMeasurementType( 
            /* [in] */ PierFaceType pierFace,
            /* [in] */ MeasurementType measure) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndDistance( 
            /* [in] */ PierFaceType pierFace,
            /* [retval][out] */ Float64 *endDist) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndDistance( 
            /* [in] */ PierFaceType pierFace,
            /* [in] */ Float64 endDist) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndDistanceMeasurementType( 
            /* [in] */ PierFaceType pierFace,
            /* [retval][out] */ MeasurementType *measure) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndDistanceMeasurementType( 
            /* [in] */ PierFaceType pierFace,
            /* [in] */ MeasurementType measure) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndDistanceMeasurementLocation( 
            /* [in] */ PierFaceType pierFace,
            /* [retval][out] */ MeasurementLocation *measure) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndDistanceMeasurementLocation( 
            /* [in] */ PierFaceType pierFace,
            /* [in] */ MeasurementLocation measure) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AlignmentPoint( 
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BridgePoint( 
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftPoint( 
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightPoint( 
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Centerline( 
            /* [retval][out] */ ILine2d **ppLine) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBearingOffset( 
            /* [in] */ PierFaceType pierFace,
            /* [in] */ IDirection *direction,
            /* [retval][out] */ Float64 *brgOffset) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPierLineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPierLine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPierLine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPierLine * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlignmentID )( 
            IPierLine * This,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Station )( 
            IPierLine * This,
            /* [retval][out] */ IStation **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Direction )( 
            IPierLine * This,
            /* [retval][out] */ IDirection **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Normal )( 
            IPierLine * This,
            /* [retval][out] */ IDirection **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Skew )( 
            IPierLine * This,
            /* [retval][out] */ IAngle **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Index )( 
            IPierLine * This,
            /* [retval][out] */ PierIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IPierLine * This,
            /* [retval][out] */ PierIDType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextPierLine )( 
            IPierLine * This,
            /* [retval][out] */ IPierLine **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevPierLine )( 
            IPierLine * This,
            /* [retval][out] */ IPierLine **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingOffset )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [retval][out] */ Float64 *brgOffset);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BearingOffset )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [in] */ Float64 brgOffset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingOffsetMeasurementType )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [retval][out] */ MeasurementType *measure);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BearingOffsetMeasurementType )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [in] */ MeasurementType measure);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndDistance )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [retval][out] */ Float64 *endDist);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndDistance )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [in] */ Float64 endDist);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndDistanceMeasurementType )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [retval][out] */ MeasurementType *measure);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndDistanceMeasurementType )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [in] */ MeasurementType measure);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndDistanceMeasurementLocation )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [retval][out] */ MeasurementLocation *measure);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndDistanceMeasurementLocation )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [in] */ MeasurementLocation measure);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlignmentPoint )( 
            IPierLine * This,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BridgePoint )( 
            IPierLine * This,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftPoint )( 
            IPierLine * This,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightPoint )( 
            IPierLine * This,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Centerline )( 
            IPierLine * This,
            /* [retval][out] */ ILine2d **ppLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBearingOffset )( 
            IPierLine * This,
            /* [in] */ PierFaceType pierFace,
            /* [in] */ IDirection *direction,
            /* [retval][out] */ Float64 *brgOffset);
        
        END_INTERFACE
    } IPierLineVtbl;

    interface IPierLine
    {
        CONST_VTBL struct IPierLineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPierLine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPierLine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPierLine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPierLine_get_AlignmentID(This,ID)	\
    ( (This)->lpVtbl -> get_AlignmentID(This,ID) ) 

#define IPierLine_get_Station(This,pVal)	\
    ( (This)->lpVtbl -> get_Station(This,pVal) ) 

#define IPierLine_get_Direction(This,pVal)	\
    ( (This)->lpVtbl -> get_Direction(This,pVal) ) 

#define IPierLine_get_Normal(This,pVal)	\
    ( (This)->lpVtbl -> get_Normal(This,pVal) ) 

#define IPierLine_get_Skew(This,pVal)	\
    ( (This)->lpVtbl -> get_Skew(This,pVal) ) 

#define IPierLine_get_Index(This,pVal)	\
    ( (This)->lpVtbl -> get_Index(This,pVal) ) 

#define IPierLine_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IPierLine_get_NextPierLine(This,pVal)	\
    ( (This)->lpVtbl -> get_NextPierLine(This,pVal) ) 

#define IPierLine_get_PrevPierLine(This,pVal)	\
    ( (This)->lpVtbl -> get_PrevPierLine(This,pVal) ) 

#define IPierLine_get_BearingOffset(This,pierFace,brgOffset)	\
    ( (This)->lpVtbl -> get_BearingOffset(This,pierFace,brgOffset) ) 

#define IPierLine_put_BearingOffset(This,pierFace,brgOffset)	\
    ( (This)->lpVtbl -> put_BearingOffset(This,pierFace,brgOffset) ) 

#define IPierLine_get_BearingOffsetMeasurementType(This,pierFace,measure)	\
    ( (This)->lpVtbl -> get_BearingOffsetMeasurementType(This,pierFace,measure) ) 

#define IPierLine_put_BearingOffsetMeasurementType(This,pierFace,measure)	\
    ( (This)->lpVtbl -> put_BearingOffsetMeasurementType(This,pierFace,measure) ) 

#define IPierLine_get_EndDistance(This,pierFace,endDist)	\
    ( (This)->lpVtbl -> get_EndDistance(This,pierFace,endDist) ) 

#define IPierLine_put_EndDistance(This,pierFace,endDist)	\
    ( (This)->lpVtbl -> put_EndDistance(This,pierFace,endDist) ) 

#define IPierLine_get_EndDistanceMeasurementType(This,pierFace,measure)	\
    ( (This)->lpVtbl -> get_EndDistanceMeasurementType(This,pierFace,measure) ) 

#define IPierLine_put_EndDistanceMeasurementType(This,pierFace,measure)	\
    ( (This)->lpVtbl -> put_EndDistanceMeasurementType(This,pierFace,measure) ) 

#define IPierLine_get_EndDistanceMeasurementLocation(This,pierFace,measure)	\
    ( (This)->lpVtbl -> get_EndDistanceMeasurementLocation(This,pierFace,measure) ) 

#define IPierLine_put_EndDistanceMeasurementLocation(This,pierFace,measure)	\
    ( (This)->lpVtbl -> put_EndDistanceMeasurementLocation(This,pierFace,measure) ) 

#define IPierLine_get_AlignmentPoint(This,ppPoint)	\
    ( (This)->lpVtbl -> get_AlignmentPoint(This,ppPoint) ) 

#define IPierLine_get_BridgePoint(This,ppPoint)	\
    ( (This)->lpVtbl -> get_BridgePoint(This,ppPoint) ) 

#define IPierLine_get_LeftPoint(This,ppPoint)	\
    ( (This)->lpVtbl -> get_LeftPoint(This,ppPoint) ) 

#define IPierLine_get_RightPoint(This,ppPoint)	\
    ( (This)->lpVtbl -> get_RightPoint(This,ppPoint) ) 

#define IPierLine_get_Centerline(This,ppLine)	\
    ( (This)->lpVtbl -> get_Centerline(This,ppLine) ) 

#define IPierLine_GetBearingOffset(This,pierFace,direction,brgOffset)	\
    ( (This)->lpVtbl -> GetBearingOffset(This,pierFace,direction,brgOffset) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPierLine_INTERFACE_DEFINED__ */


#ifndef __IEnumPierLines_INTERFACE_DEFINED__
#define __IEnumPierLines_INTERFACE_DEFINED__

/* interface IEnumPierLines */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumPierLines;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A1A7AE0-B7E1-46b7-A4A7-2532F92F1246")
    IEnumPierLines : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPierLines **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IPierLine **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumPierLinesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPierLines * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPierLines * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPierLines * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPierLines * This,
            /* [out] */ IEnumPierLines **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPierLines * This,
            /* [in] */ ULONG celt,
            /* [out] */ IPierLine **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPierLines * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPierLines * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumPierLinesVtbl;

    interface IEnumPierLines
    {
        CONST_VTBL struct IEnumPierLinesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPierLines_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumPierLines_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumPierLines_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumPierLines_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumPierLines_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumPierLines_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumPierLines_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumPierLines_INTERFACE_DEFINED__ */


#ifndef __IPierLineCollection_INTERFACE_DEFINED__
#define __IPierLineCollection_INTERFACE_DEFINED__

/* interface IPierLineCollection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPierLineCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B97C82D3-EE60-4D92-B999-E6C915C49F83")
    IPierLineCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PierLine( 
            /* [in] */ PierIndexType index,
            /* [retval][out] */ IPierLine **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ PierIndexType *count) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PierLineIndex( 
            /* [in] */ IPierLine *pier,
            /* [retval][out] */ PierIndexType *index) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumPiers( 
            /* [retval][out] */ IEnumPierLines **enumPiers) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindPierLine( 
            /* [in] */ PierIDType pierID,
            /* [retval][out] */ IPierLine **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPierLineCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPierLineCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPierLineCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPierLineCollection * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IPierLineCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PierLine )( 
            IPierLineCollection * This,
            /* [in] */ PierIndexType index,
            /* [retval][out] */ IPierLine **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPierLineCollection * This,
            /* [retval][out] */ PierIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PierLineIndex )( 
            IPierLineCollection * This,
            /* [in] */ IPierLine *pier,
            /* [retval][out] */ PierIndexType *index);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumPiers )( 
            IPierLineCollection * This,
            /* [retval][out] */ IEnumPierLines **enumPiers);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindPierLine )( 
            IPierLineCollection * This,
            /* [in] */ PierIDType pierID,
            /* [retval][out] */ IPierLine **pVal);
        
        END_INTERFACE
    } IPierLineCollectionVtbl;

    interface IPierLineCollection
    {
        CONST_VTBL struct IPierLineCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPierLineCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPierLineCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPierLineCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPierLineCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IPierLineCollection_get_PierLine(This,index,pVal)	\
    ( (This)->lpVtbl -> get_PierLine(This,index,pVal) ) 

#define IPierLineCollection_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define IPierLineCollection_get_PierLineIndex(This,pier,index)	\
    ( (This)->lpVtbl -> get_PierLineIndex(This,pier,index) ) 

#define IPierLineCollection_get__EnumPiers(This,enumPiers)	\
    ( (This)->lpVtbl -> get__EnumPiers(This,enumPiers) ) 

#define IPierLineCollection_FindPierLine(This,pierID,pVal)	\
    ( (This)->lpVtbl -> FindPierLine(This,pierID,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPierLineCollection_INTERFACE_DEFINED__ */


#ifndef __ILayoutLineFactory_INTERFACE_DEFINED__
#define __ILayoutLineFactory_INTERFACE_DEFINED__

/* interface ILayoutLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILayoutLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D58BBF23-B486-417E-B55C-63D181068947")
    ILayoutLineFactory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ IBridgeGeometry *pBridge,
            /* [in] */ IPathCollection *pPaths) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILayoutLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILayoutLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILayoutLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILayoutLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            ILayoutLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [in] */ IPathCollection *pPaths);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ILayoutLineFactory * This);
        
        END_INTERFACE
    } ILayoutLineFactoryVtbl;

    interface ILayoutLineFactory
    {
        CONST_VTBL struct ILayoutLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILayoutLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILayoutLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILayoutLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILayoutLineFactory_Create(This,pBridge,pPaths)	\
    ( (This)->lpVtbl -> Create(This,pBridge,pPaths) ) 

#define ILayoutLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILayoutLineFactory_INTERFACE_DEFINED__ */


#ifndef __IAlignmentOffsetLayoutLineFactory_INTERFACE_DEFINED__
#define __IAlignmentOffsetLayoutLineFactory_INTERFACE_DEFINED__

/* interface IAlignmentOffsetLayoutLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAlignmentOffsetLayoutLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0A47CB63-C3CF-47DF-8F2F-5B72C83C02B8")
    IAlignmentOffsetLayoutLineFactory : public ILayoutLineFactory
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LayoutLineID( 
            /* [in] */ LineIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutLineID( 
            /* [retval][out] */ LineIDType *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LayoutLineIDInc( 
            /* [in] */ LineIDType inc) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutLineIDInc( 
            /* [retval][out] */ LineIDType *inc) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LayoutLineCount( 
            /* [in] */ LineIDType nLayoutLines) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutLineCount( 
            /* [retval][out] */ LineIDType *nLayoutLines) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Offset( 
            /* [retval][out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Offset( 
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OffsetIncrement( 
            /* [retval][out] */ Float64 *inc) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OffsetIncrement( 
            /* [in] */ Float64 inc) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AlignmentID( 
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AlignmentID( 
            /* [in] */ CogoObjectID ID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAlignmentOffsetLayoutLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAlignmentOffsetLayoutLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAlignmentOffsetLayoutLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [in] */ IPathCollection *pPaths);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IAlignmentOffsetLayoutLineFactory * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayoutLineID )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [in] */ LineIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLineID )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [retval][out] */ LineIDType *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayoutLineIDInc )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [in] */ LineIDType inc);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLineIDInc )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [retval][out] */ LineIDType *inc);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayoutLineCount )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [in] */ LineIDType nLayoutLines);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLineCount )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [retval][out] */ LineIDType *nLayoutLines);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Offset )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [retval][out] */ Float64 *offset);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Offset )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [in] */ Float64 offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetIncrement )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [retval][out] */ Float64 *inc);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetIncrement )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [in] */ Float64 inc);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlignmentID )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AlignmentID )( 
            IAlignmentOffsetLayoutLineFactory * This,
            /* [in] */ CogoObjectID ID);
        
        END_INTERFACE
    } IAlignmentOffsetLayoutLineFactoryVtbl;

    interface IAlignmentOffsetLayoutLineFactory
    {
        CONST_VTBL struct IAlignmentOffsetLayoutLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlignmentOffsetLayoutLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAlignmentOffsetLayoutLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAlignmentOffsetLayoutLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAlignmentOffsetLayoutLineFactory_Create(This,pBridge,pPaths)	\
    ( (This)->lpVtbl -> Create(This,pBridge,pPaths) ) 

#define IAlignmentOffsetLayoutLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 


#define IAlignmentOffsetLayoutLineFactory_put_LayoutLineID(This,ID)	\
    ( (This)->lpVtbl -> put_LayoutLineID(This,ID) ) 

#define IAlignmentOffsetLayoutLineFactory_get_LayoutLineID(This,ID)	\
    ( (This)->lpVtbl -> get_LayoutLineID(This,ID) ) 

#define IAlignmentOffsetLayoutLineFactory_put_LayoutLineIDInc(This,inc)	\
    ( (This)->lpVtbl -> put_LayoutLineIDInc(This,inc) ) 

#define IAlignmentOffsetLayoutLineFactory_get_LayoutLineIDInc(This,inc)	\
    ( (This)->lpVtbl -> get_LayoutLineIDInc(This,inc) ) 

#define IAlignmentOffsetLayoutLineFactory_put_LayoutLineCount(This,nLayoutLines)	\
    ( (This)->lpVtbl -> put_LayoutLineCount(This,nLayoutLines) ) 

#define IAlignmentOffsetLayoutLineFactory_get_LayoutLineCount(This,nLayoutLines)	\
    ( (This)->lpVtbl -> get_LayoutLineCount(This,nLayoutLines) ) 

#define IAlignmentOffsetLayoutLineFactory_get_Offset(This,offset)	\
    ( (This)->lpVtbl -> get_Offset(This,offset) ) 

#define IAlignmentOffsetLayoutLineFactory_put_Offset(This,offset)	\
    ( (This)->lpVtbl -> put_Offset(This,offset) ) 

#define IAlignmentOffsetLayoutLineFactory_get_OffsetIncrement(This,inc)	\
    ( (This)->lpVtbl -> get_OffsetIncrement(This,inc) ) 

#define IAlignmentOffsetLayoutLineFactory_put_OffsetIncrement(This,inc)	\
    ( (This)->lpVtbl -> put_OffsetIncrement(This,inc) ) 

#define IAlignmentOffsetLayoutLineFactory_get_AlignmentID(This,ID)	\
    ( (This)->lpVtbl -> get_AlignmentID(This,ID) ) 

#define IAlignmentOffsetLayoutLineFactory_put_AlignmentID(This,ID)	\
    ( (This)->lpVtbl -> put_AlignmentID(This,ID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAlignmentOffsetLayoutLineFactory_INTERFACE_DEFINED__ */


#ifndef __ISimpleLayoutLineFactory_INTERFACE_DEFINED__
#define __ISimpleLayoutLineFactory_INTERFACE_DEFINED__

/* interface ISimpleLayoutLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISimpleLayoutLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("64CC0388-9A1C-41D3-8324-D3EA44DC6CFF")
    ISimpleLayoutLineFactory : public ILayoutLineFactory
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPath( 
            /* [in] */ LineIDType ID,
            /* [in] */ IPath *path) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISimpleLayoutLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISimpleLayoutLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISimpleLayoutLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISimpleLayoutLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            ISimpleLayoutLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [in] */ IPathCollection *pPaths);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ISimpleLayoutLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPath )( 
            ISimpleLayoutLineFactory * This,
            /* [in] */ LineIDType ID,
            /* [in] */ IPath *path);
        
        END_INTERFACE
    } ISimpleLayoutLineFactoryVtbl;

    interface ISimpleLayoutLineFactory
    {
        CONST_VTBL struct ISimpleLayoutLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISimpleLayoutLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISimpleLayoutLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISimpleLayoutLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISimpleLayoutLineFactory_Create(This,pBridge,pPaths)	\
    ( (This)->lpVtbl -> Create(This,pBridge,pPaths) ) 

#define ISimpleLayoutLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 


#define ISimpleLayoutLineFactory_AddPath(This,ID,path)	\
    ( (This)->lpVtbl -> AddPath(This,ID,path) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISimpleLayoutLineFactory_INTERFACE_DEFINED__ */


#ifndef __IUniformSpacingLayoutLineFactory_INTERFACE_DEFINED__
#define __IUniformSpacingLayoutLineFactory_INTERFACE_DEFINED__

/* interface IUniformSpacingLayoutLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IUniformSpacingLayoutLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B34A9D24-9551-490A-A3C2-3C7CF6803D4C")
    IUniformSpacingLayoutLineFactory : public ILayoutLineFactory
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AlignmentID( 
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AlignmentID( 
            /* [in] */ CogoObjectID ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartPierID( 
            /* [retval][out] */ PierIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartPierID( 
            /* [in] */ PierIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPierID( 
            /* [retval][out] */ PierIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndPierID( 
            /* [in] */ PierIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PierIDInc( 
            /* [retval][out] */ PierIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PierIDInc( 
            /* [in] */ PierIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartSpacingOffset( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartSpacingOffset( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndSpacingOffset( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndSpacingOffset( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartSpacing( 
            /* [retval][out] */ IDblArray **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartSpacing( 
            /* [in] */ IDblArray *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndSpacing( 
            /* [retval][out] */ IDblArray **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndSpacing( 
            /* [in] */ IDblArray *newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LayoutLineID( 
            /* [in] */ LineIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutLineID( 
            /* [retval][out] */ LineIDType *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LayoutLineIDInc( 
            /* [in] */ LineIDType inc) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutLineIDInc( 
            /* [retval][out] */ LineIDType *inc) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUniformSpacingLayoutLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUniformSpacingLayoutLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUniformSpacingLayoutLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [in] */ IPathCollection *pPaths);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IUniformSpacingLayoutLineFactory * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlignmentID )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AlignmentID )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ CogoObjectID ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPierID )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [retval][out] */ PierIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartPierID )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ PierIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPierID )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [retval][out] */ PierIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndPierID )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ PierIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PierIDInc )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [retval][out] */ PierIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PierIDInc )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ PierIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartSpacingOffset )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartSpacingOffset )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndSpacingOffset )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndSpacingOffset )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartSpacing )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [retval][out] */ IDblArray **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartSpacing )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ IDblArray *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndSpacing )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [retval][out] */ IDblArray **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndSpacing )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ IDblArray *newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayoutLineID )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ LineIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLineID )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [retval][out] */ LineIDType *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayoutLineIDInc )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [in] */ LineIDType inc);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLineIDInc )( 
            IUniformSpacingLayoutLineFactory * This,
            /* [retval][out] */ LineIDType *inc);
        
        END_INTERFACE
    } IUniformSpacingLayoutLineFactoryVtbl;

    interface IUniformSpacingLayoutLineFactory
    {
        CONST_VTBL struct IUniformSpacingLayoutLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUniformSpacingLayoutLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUniformSpacingLayoutLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUniformSpacingLayoutLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUniformSpacingLayoutLineFactory_Create(This,pBridge,pPaths)	\
    ( (This)->lpVtbl -> Create(This,pBridge,pPaths) ) 

#define IUniformSpacingLayoutLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 


#define IUniformSpacingLayoutLineFactory_get_AlignmentID(This,ID)	\
    ( (This)->lpVtbl -> get_AlignmentID(This,ID) ) 

#define IUniformSpacingLayoutLineFactory_put_AlignmentID(This,ID)	\
    ( (This)->lpVtbl -> put_AlignmentID(This,ID) ) 

#define IUniformSpacingLayoutLineFactory_get_StartPierID(This,pVal)	\
    ( (This)->lpVtbl -> get_StartPierID(This,pVal) ) 

#define IUniformSpacingLayoutLineFactory_put_StartPierID(This,newVal)	\
    ( (This)->lpVtbl -> put_StartPierID(This,newVal) ) 

#define IUniformSpacingLayoutLineFactory_get_EndPierID(This,pVal)	\
    ( (This)->lpVtbl -> get_EndPierID(This,pVal) ) 

#define IUniformSpacingLayoutLineFactory_put_EndPierID(This,newVal)	\
    ( (This)->lpVtbl -> put_EndPierID(This,newVal) ) 

#define IUniformSpacingLayoutLineFactory_get_PierIDInc(This,pVal)	\
    ( (This)->lpVtbl -> get_PierIDInc(This,pVal) ) 

#define IUniformSpacingLayoutLineFactory_put_PierIDInc(This,newVal)	\
    ( (This)->lpVtbl -> put_PierIDInc(This,newVal) ) 

#define IUniformSpacingLayoutLineFactory_get_StartSpacingOffset(This,pVal)	\
    ( (This)->lpVtbl -> get_StartSpacingOffset(This,pVal) ) 

#define IUniformSpacingLayoutLineFactory_put_StartSpacingOffset(This,newVal)	\
    ( (This)->lpVtbl -> put_StartSpacingOffset(This,newVal) ) 

#define IUniformSpacingLayoutLineFactory_get_EndSpacingOffset(This,pVal)	\
    ( (This)->lpVtbl -> get_EndSpacingOffset(This,pVal) ) 

#define IUniformSpacingLayoutLineFactory_put_EndSpacingOffset(This,newVal)	\
    ( (This)->lpVtbl -> put_EndSpacingOffset(This,newVal) ) 

#define IUniformSpacingLayoutLineFactory_get_StartSpacing(This,pVal)	\
    ( (This)->lpVtbl -> get_StartSpacing(This,pVal) ) 

#define IUniformSpacingLayoutLineFactory_put_StartSpacing(This,newVal)	\
    ( (This)->lpVtbl -> put_StartSpacing(This,newVal) ) 

#define IUniformSpacingLayoutLineFactory_get_EndSpacing(This,pVal)	\
    ( (This)->lpVtbl -> get_EndSpacing(This,pVal) ) 

#define IUniformSpacingLayoutLineFactory_put_EndSpacing(This,newVal)	\
    ( (This)->lpVtbl -> put_EndSpacing(This,newVal) ) 

#define IUniformSpacingLayoutLineFactory_put_LayoutLineID(This,ID)	\
    ( (This)->lpVtbl -> put_LayoutLineID(This,ID) ) 

#define IUniformSpacingLayoutLineFactory_get_LayoutLineID(This,ID)	\
    ( (This)->lpVtbl -> get_LayoutLineID(This,ID) ) 

#define IUniformSpacingLayoutLineFactory_put_LayoutLineIDInc(This,inc)	\
    ( (This)->lpVtbl -> put_LayoutLineIDInc(This,inc) ) 

#define IUniformSpacingLayoutLineFactory_get_LayoutLineIDInc(This,inc)	\
    ( (This)->lpVtbl -> get_LayoutLineIDInc(This,inc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUniformSpacingLayoutLineFactory_INTERFACE_DEFINED__ */


#ifndef __IGirderLineFactory_INTERFACE_DEFINED__
#define __IGirderLineFactory_INTERFACE_DEFINED__

/* interface IGirderLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGirderLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F7A4B484-4C6B-4A36-B62C-FC216F09F033")
    IGirderLineFactory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IUnkArray **ppArrayGirderLines) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGirderLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGirderLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGirderLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGirderLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IGirderLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IUnkArray **ppArrayGirderLines);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IGirderLineFactory * This);
        
        END_INTERFACE
    } IGirderLineFactoryVtbl;

    interface IGirderLineFactory
    {
        CONST_VTBL struct IGirderLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGirderLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGirderLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGirderLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGirderLineFactory_Create(This,pBridge,ppArrayGirderLines)	\
    ( (This)->lpVtbl -> Create(This,pBridge,ppArrayGirderLines) ) 

#define IGirderLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGirderLineFactory_INTERFACE_DEFINED__ */


#ifndef __ISingleGirderLineFactory_INTERFACE_DEFINED__
#define __ISingleGirderLineFactory_INTERFACE_DEFINED__

/* interface ISingleGirderLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISingleGirderLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9BE02875-99F1-4529-B7F7-1235DF2FC010")
    ISingleGirderLineFactory : public IGirderLineFactory
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GirderLineID( 
            /* [retval][out] */ GirderIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GirderLineID( 
            /* [in] */ GirderIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutLineID( 
            /* [retval][out] */ LineIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LayoutLineID( 
            /* [in] */ LineIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ GirderLineType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ GirderLineType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartPierID( 
            /* [retval][out] */ PierIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartPierID( 
            /* [in] */ PierIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPierID( 
            /* [retval][out] */ PierIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndPierID( 
            /* [in] */ PierIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartMeasurementType( 
            /* [retval][out] */ MeasurementType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartMeasurementType( 
            /* [in] */ MeasurementType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartMeasurementLocation( 
            /* [retval][out] */ MeasurementLocation *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartMeasurementLocation( 
            /* [in] */ MeasurementLocation newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndMeasurementType( 
            /* [retval][out] */ MeasurementType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndMeasurementType( 
            /* [in] */ MeasurementType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndMeasurementLocation( 
            /* [retval][out] */ MeasurementLocation *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndMeasurementLocation( 
            /* [in] */ MeasurementLocation newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISingleGirderLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISingleGirderLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISingleGirderLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISingleGirderLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            ISingleGirderLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IUnkArray **ppArrayGirderLines);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ISingleGirderLineFactory * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLineID )( 
            ISingleGirderLineFactory * This,
            /* [retval][out] */ GirderIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GirderLineID )( 
            ISingleGirderLineFactory * This,
            /* [in] */ GirderIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLineID )( 
            ISingleGirderLineFactory * This,
            /* [retval][out] */ LineIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayoutLineID )( 
            ISingleGirderLineFactory * This,
            /* [in] */ LineIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ISingleGirderLineFactory * This,
            /* [retval][out] */ GirderLineType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            ISingleGirderLineFactory * This,
            /* [in] */ GirderLineType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPierID )( 
            ISingleGirderLineFactory * This,
            /* [retval][out] */ PierIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartPierID )( 
            ISingleGirderLineFactory * This,
            /* [in] */ PierIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPierID )( 
            ISingleGirderLineFactory * This,
            /* [retval][out] */ PierIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndPierID )( 
            ISingleGirderLineFactory * This,
            /* [in] */ PierIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartMeasurementType )( 
            ISingleGirderLineFactory * This,
            /* [retval][out] */ MeasurementType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartMeasurementType )( 
            ISingleGirderLineFactory * This,
            /* [in] */ MeasurementType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartMeasurementLocation )( 
            ISingleGirderLineFactory * This,
            /* [retval][out] */ MeasurementLocation *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartMeasurementLocation )( 
            ISingleGirderLineFactory * This,
            /* [in] */ MeasurementLocation newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndMeasurementType )( 
            ISingleGirderLineFactory * This,
            /* [retval][out] */ MeasurementType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndMeasurementType )( 
            ISingleGirderLineFactory * This,
            /* [in] */ MeasurementType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndMeasurementLocation )( 
            ISingleGirderLineFactory * This,
            /* [retval][out] */ MeasurementLocation *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndMeasurementLocation )( 
            ISingleGirderLineFactory * This,
            /* [in] */ MeasurementLocation newVal);
        
        END_INTERFACE
    } ISingleGirderLineFactoryVtbl;

    interface ISingleGirderLineFactory
    {
        CONST_VTBL struct ISingleGirderLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISingleGirderLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISingleGirderLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISingleGirderLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISingleGirderLineFactory_Create(This,pBridge,ppArrayGirderLines)	\
    ( (This)->lpVtbl -> Create(This,pBridge,ppArrayGirderLines) ) 

#define ISingleGirderLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 


#define ISingleGirderLineFactory_get_GirderLineID(This,pVal)	\
    ( (This)->lpVtbl -> get_GirderLineID(This,pVal) ) 

#define ISingleGirderLineFactory_put_GirderLineID(This,newVal)	\
    ( (This)->lpVtbl -> put_GirderLineID(This,newVal) ) 

#define ISingleGirderLineFactory_get_LayoutLineID(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLineID(This,pVal) ) 

#define ISingleGirderLineFactory_put_LayoutLineID(This,newVal)	\
    ( (This)->lpVtbl -> put_LayoutLineID(This,newVal) ) 

#define ISingleGirderLineFactory_get_Type(This,pVal)	\
    ( (This)->lpVtbl -> get_Type(This,pVal) ) 

#define ISingleGirderLineFactory_put_Type(This,newVal)	\
    ( (This)->lpVtbl -> put_Type(This,newVal) ) 

#define ISingleGirderLineFactory_get_StartPierID(This,pVal)	\
    ( (This)->lpVtbl -> get_StartPierID(This,pVal) ) 

#define ISingleGirderLineFactory_put_StartPierID(This,newVal)	\
    ( (This)->lpVtbl -> put_StartPierID(This,newVal) ) 

#define ISingleGirderLineFactory_get_EndPierID(This,pVal)	\
    ( (This)->lpVtbl -> get_EndPierID(This,pVal) ) 

#define ISingleGirderLineFactory_put_EndPierID(This,newVal)	\
    ( (This)->lpVtbl -> put_EndPierID(This,newVal) ) 

#define ISingleGirderLineFactory_get_StartMeasurementType(This,pVal)	\
    ( (This)->lpVtbl -> get_StartMeasurementType(This,pVal) ) 

#define ISingleGirderLineFactory_put_StartMeasurementType(This,newVal)	\
    ( (This)->lpVtbl -> put_StartMeasurementType(This,newVal) ) 

#define ISingleGirderLineFactory_get_StartMeasurementLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_StartMeasurementLocation(This,pVal) ) 

#define ISingleGirderLineFactory_put_StartMeasurementLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_StartMeasurementLocation(This,newVal) ) 

#define ISingleGirderLineFactory_get_EndMeasurementType(This,pVal)	\
    ( (This)->lpVtbl -> get_EndMeasurementType(This,pVal) ) 

#define ISingleGirderLineFactory_put_EndMeasurementType(This,newVal)	\
    ( (This)->lpVtbl -> put_EndMeasurementType(This,newVal) ) 

#define ISingleGirderLineFactory_get_EndMeasurementLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_EndMeasurementLocation(This,pVal) ) 

#define ISingleGirderLineFactory_put_EndMeasurementLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_EndMeasurementLocation(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISingleGirderLineFactory_INTERFACE_DEFINED__ */


#ifndef __ISimpleGirderLineFactory_INTERFACE_DEFINED__
#define __ISimpleGirderLineFactory_INTERFACE_DEFINED__

/* interface ISimpleGirderLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISimpleGirderLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4DCF9E5C-3035-4150-882E-7084796B93B5")
    ISimpleGirderLineFactory : public IGirderLineFactory
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GirderLineID( 
            /* [retval][out] */ GirderIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GirderLineID( 
            /* [in] */ GirderIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GirderLineIDInc( 
            /* [retval][out] */ GirderIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GirderLineIDInc( 
            /* [in] */ GirderIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftLayoutLineID( 
            /* [retval][out] */ LineIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LeftLayoutLineID( 
            /* [in] */ LineIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightLayoutLineID( 
            /* [retval][out] */ LineIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RightLayoutLineID( 
            /* [in] */ LineIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutLineIDInc( 
            /* [retval][out] */ LineIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LayoutLineIDInc( 
            /* [in] */ LineIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ GirderLineType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ GirderLineType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartPierID( 
            /* [retval][out] */ PierIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartPierID( 
            /* [in] */ PierIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPierID( 
            /* [retval][out] */ PierIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndPierID( 
            /* [in] */ PierIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PierIDInc( 
            /* [retval][out] */ PierIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PierIDInc( 
            /* [in] */ PierIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Continuous( 
            /* [retval][out] */ VARIANT_BOOL *pbContinuous) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Continuous( 
            /* [in] */ VARIANT_BOOL bContinuous) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartMeasurementType( 
            /* [retval][out] */ MeasurementType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartMeasurementType( 
            /* [in] */ MeasurementType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartMeasurementLocation( 
            /* [retval][out] */ MeasurementLocation *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartMeasurementLocation( 
            /* [in] */ MeasurementLocation newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndMeasurementType( 
            /* [retval][out] */ MeasurementType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndMeasurementType( 
            /* [in] */ MeasurementType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndMeasurementLocation( 
            /* [retval][out] */ MeasurementLocation *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndMeasurementLocation( 
            /* [in] */ MeasurementLocation newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISimpleGirderLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISimpleGirderLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISimpleGirderLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IUnkArray **ppArrayGirderLines);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ISimpleGirderLineFactory * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLineID )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ GirderIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GirderLineID )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ GirderIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLineIDInc )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ GirderIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GirderLineIDInc )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ GirderIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftLayoutLineID )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ LineIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LeftLayoutLineID )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ LineIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightLayoutLineID )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ LineIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RightLayoutLineID )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ LineIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLineIDInc )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ LineIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayoutLineIDInc )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ LineIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ GirderLineType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ GirderLineType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPierID )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ PierIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartPierID )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ PierIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPierID )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ PierIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndPierID )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ PierIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PierIDInc )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ PierIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PierIDInc )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ PierIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Continuous )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ VARIANT_BOOL *pbContinuous);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Continuous )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ VARIANT_BOOL bContinuous);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartMeasurementType )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ MeasurementType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartMeasurementType )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ MeasurementType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartMeasurementLocation )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ MeasurementLocation *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartMeasurementLocation )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ MeasurementLocation newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndMeasurementType )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ MeasurementType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndMeasurementType )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ MeasurementType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndMeasurementLocation )( 
            ISimpleGirderLineFactory * This,
            /* [retval][out] */ MeasurementLocation *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndMeasurementLocation )( 
            ISimpleGirderLineFactory * This,
            /* [in] */ MeasurementLocation newVal);
        
        END_INTERFACE
    } ISimpleGirderLineFactoryVtbl;

    interface ISimpleGirderLineFactory
    {
        CONST_VTBL struct ISimpleGirderLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISimpleGirderLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISimpleGirderLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISimpleGirderLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISimpleGirderLineFactory_Create(This,pBridge,ppArrayGirderLines)	\
    ( (This)->lpVtbl -> Create(This,pBridge,ppArrayGirderLines) ) 

#define ISimpleGirderLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 


#define ISimpleGirderLineFactory_get_GirderLineID(This,pVal)	\
    ( (This)->lpVtbl -> get_GirderLineID(This,pVal) ) 

#define ISimpleGirderLineFactory_put_GirderLineID(This,newVal)	\
    ( (This)->lpVtbl -> put_GirderLineID(This,newVal) ) 

#define ISimpleGirderLineFactory_get_GirderLineIDInc(This,pVal)	\
    ( (This)->lpVtbl -> get_GirderLineIDInc(This,pVal) ) 

#define ISimpleGirderLineFactory_put_GirderLineIDInc(This,newVal)	\
    ( (This)->lpVtbl -> put_GirderLineIDInc(This,newVal) ) 

#define ISimpleGirderLineFactory_get_LeftLayoutLineID(This,pVal)	\
    ( (This)->lpVtbl -> get_LeftLayoutLineID(This,pVal) ) 

#define ISimpleGirderLineFactory_put_LeftLayoutLineID(This,newVal)	\
    ( (This)->lpVtbl -> put_LeftLayoutLineID(This,newVal) ) 

#define ISimpleGirderLineFactory_get_RightLayoutLineID(This,pVal)	\
    ( (This)->lpVtbl -> get_RightLayoutLineID(This,pVal) ) 

#define ISimpleGirderLineFactory_put_RightLayoutLineID(This,newVal)	\
    ( (This)->lpVtbl -> put_RightLayoutLineID(This,newVal) ) 

#define ISimpleGirderLineFactory_get_LayoutLineIDInc(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLineIDInc(This,pVal) ) 

#define ISimpleGirderLineFactory_put_LayoutLineIDInc(This,newVal)	\
    ( (This)->lpVtbl -> put_LayoutLineIDInc(This,newVal) ) 

#define ISimpleGirderLineFactory_get_Type(This,pVal)	\
    ( (This)->lpVtbl -> get_Type(This,pVal) ) 

#define ISimpleGirderLineFactory_put_Type(This,newVal)	\
    ( (This)->lpVtbl -> put_Type(This,newVal) ) 

#define ISimpleGirderLineFactory_get_StartPierID(This,pVal)	\
    ( (This)->lpVtbl -> get_StartPierID(This,pVal) ) 

#define ISimpleGirderLineFactory_put_StartPierID(This,newVal)	\
    ( (This)->lpVtbl -> put_StartPierID(This,newVal) ) 

#define ISimpleGirderLineFactory_get_EndPierID(This,pVal)	\
    ( (This)->lpVtbl -> get_EndPierID(This,pVal) ) 

#define ISimpleGirderLineFactory_put_EndPierID(This,newVal)	\
    ( (This)->lpVtbl -> put_EndPierID(This,newVal) ) 

#define ISimpleGirderLineFactory_get_PierIDInc(This,pVal)	\
    ( (This)->lpVtbl -> get_PierIDInc(This,pVal) ) 

#define ISimpleGirderLineFactory_put_PierIDInc(This,newVal)	\
    ( (This)->lpVtbl -> put_PierIDInc(This,newVal) ) 

#define ISimpleGirderLineFactory_get_Continuous(This,pbContinuous)	\
    ( (This)->lpVtbl -> get_Continuous(This,pbContinuous) ) 

#define ISimpleGirderLineFactory_put_Continuous(This,bContinuous)	\
    ( (This)->lpVtbl -> put_Continuous(This,bContinuous) ) 

#define ISimpleGirderLineFactory_get_StartMeasurementType(This,pVal)	\
    ( (This)->lpVtbl -> get_StartMeasurementType(This,pVal) ) 

#define ISimpleGirderLineFactory_put_StartMeasurementType(This,newVal)	\
    ( (This)->lpVtbl -> put_StartMeasurementType(This,newVal) ) 

#define ISimpleGirderLineFactory_get_StartMeasurementLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_StartMeasurementLocation(This,pVal) ) 

#define ISimpleGirderLineFactory_put_StartMeasurementLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_StartMeasurementLocation(This,newVal) ) 

#define ISimpleGirderLineFactory_get_EndMeasurementType(This,pVal)	\
    ( (This)->lpVtbl -> get_EndMeasurementType(This,pVal) ) 

#define ISimpleGirderLineFactory_put_EndMeasurementType(This,newVal)	\
    ( (This)->lpVtbl -> put_EndMeasurementType(This,newVal) ) 

#define ISimpleGirderLineFactory_get_EndMeasurementLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_EndMeasurementLocation(This,pVal) ) 

#define ISimpleGirderLineFactory_put_EndMeasurementLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_EndMeasurementLocation(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISimpleGirderLineFactory_INTERFACE_DEFINED__ */


#ifndef __IGirderLine_INTERFACE_DEFINED__
#define __IGirderLine_INTERFACE_DEFINED__

/* interface IGirderLine */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGirderLine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EDD54A64-4F63-4DC0-B605-DAA4C63BDA64")
    IGirderLine : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ GirderIDType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartPier( 
            /* [retval][out] */ IPierLine **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPier( 
            /* [retval][out] */ IPierLine **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GirderLength( 
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SpanLength( 
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutLength( 
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PierPoint( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingPoint( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPoint( 
            /* [in] */ EndType endType,
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEndPoints( 
            /* [out] */ IPoint2d **pntPier1,
            /* [out] */ IPoint2d **pntEnd1,
            /* [out] */ IPoint2d **pntBrg1,
            /* [out] */ IPoint2d **pntBrg2,
            /* [out] */ IPoint2d **pntEnd2,
            /* [out] */ IPoint2d **pntPier2) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ IPath **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ IDirection **ppDirection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingOffset( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pBrgOffset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndDistance( 
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pEndDist) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGirderLineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGirderLine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGirderLine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGirderLine * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IGirderLine * This,
            /* [retval][out] */ GirderIDType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPier )( 
            IGirderLine * This,
            /* [retval][out] */ IPierLine **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPier )( 
            IGirderLine * This,
            /* [retval][out] */ IPierLine **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLength )( 
            IGirderLine * This,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpanLength )( 
            IGirderLine * This,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLength )( 
            IGirderLine * This,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PierPoint )( 
            IGirderLine * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingPoint )( 
            IGirderLine * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPoint )( 
            IGirderLine * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEndPoints )( 
            IGirderLine * This,
            /* [out] */ IPoint2d **pntPier1,
            /* [out] */ IPoint2d **pntEnd1,
            /* [out] */ IPoint2d **pntBrg1,
            /* [out] */ IPoint2d **pntBrg2,
            /* [out] */ IPoint2d **pntEnd2,
            /* [out] */ IPoint2d **pntPier2);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Path )( 
            IGirderLine * This,
            /* [retval][out] */ IPath **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Direction )( 
            IGirderLine * This,
            /* [retval][out] */ IDirection **ppDirection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingOffset )( 
            IGirderLine * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pBrgOffset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndDistance )( 
            IGirderLine * This,
            /* [in] */ EndType endType,
            /* [retval][out] */ Float64 *pEndDist);
        
        END_INTERFACE
    } IGirderLineVtbl;

    interface IGirderLine
    {
        CONST_VTBL struct IGirderLineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGirderLine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGirderLine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGirderLine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGirderLine_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IGirderLine_get_StartPier(This,pVal)	\
    ( (This)->lpVtbl -> get_StartPier(This,pVal) ) 

#define IGirderLine_get_EndPier(This,pVal)	\
    ( (This)->lpVtbl -> get_EndPier(This,pVal) ) 

#define IGirderLine_get_GirderLength(This,pLength)	\
    ( (This)->lpVtbl -> get_GirderLength(This,pLength) ) 

#define IGirderLine_get_SpanLength(This,pLength)	\
    ( (This)->lpVtbl -> get_SpanLength(This,pLength) ) 

#define IGirderLine_get_LayoutLength(This,pLength)	\
    ( (This)->lpVtbl -> get_LayoutLength(This,pLength) ) 

#define IGirderLine_get_PierPoint(This,endType,ppPoint)	\
    ( (This)->lpVtbl -> get_PierPoint(This,endType,ppPoint) ) 

#define IGirderLine_get_BearingPoint(This,endType,ppPoint)	\
    ( (This)->lpVtbl -> get_BearingPoint(This,endType,ppPoint) ) 

#define IGirderLine_get_EndPoint(This,endType,ppPoint)	\
    ( (This)->lpVtbl -> get_EndPoint(This,endType,ppPoint) ) 

#define IGirderLine_GetEndPoints(This,pntPier1,pntEnd1,pntBrg1,pntBrg2,pntEnd2,pntPier2)	\
    ( (This)->lpVtbl -> GetEndPoints(This,pntPier1,pntEnd1,pntBrg1,pntBrg2,pntEnd2,pntPier2) ) 

#define IGirderLine_get_Path(This,pVal)	\
    ( (This)->lpVtbl -> get_Path(This,pVal) ) 

#define IGirderLine_get_Direction(This,ppDirection)	\
    ( (This)->lpVtbl -> get_Direction(This,ppDirection) ) 

#define IGirderLine_get_BearingOffset(This,endType,pBrgOffset)	\
    ( (This)->lpVtbl -> get_BearingOffset(This,endType,pBrgOffset) ) 

#define IGirderLine_get_EndDistance(This,endType,pEndDist)	\
    ( (This)->lpVtbl -> get_EndDistance(This,endType,pEndDist) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGirderLine_INTERFACE_DEFINED__ */


#ifndef __IDiaphragmLineFactory_INTERFACE_DEFINED__
#define __IDiaphragmLineFactory_INTERFACE_DEFINED__

/* interface IDiaphragmLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDiaphragmLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B3979762-E72A-401B-AC03-28E953A222C2")
    IDiaphragmLineFactory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IUnkArray **ppArrayDiaphagmLines) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDiaphragmLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDiaphragmLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDiaphragmLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDiaphragmLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IDiaphragmLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IUnkArray **ppArrayDiaphagmLines);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IDiaphragmLineFactory * This);
        
        END_INTERFACE
    } IDiaphragmLineFactoryVtbl;

    interface IDiaphragmLineFactory
    {
        CONST_VTBL struct IDiaphragmLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDiaphragmLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDiaphragmLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDiaphragmLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDiaphragmLineFactory_Create(This,pBridge,ppArrayDiaphagmLines)	\
    ( (This)->lpVtbl -> Create(This,pBridge,ppArrayDiaphagmLines) ) 

#define IDiaphragmLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDiaphragmLineFactory_INTERFACE_DEFINED__ */


#ifndef __ISingleDiaphragmLineFactory_INTERFACE_DEFINED__
#define __ISingleDiaphragmLineFactory_INTERFACE_DEFINED__

/* interface ISingleDiaphragmLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISingleDiaphragmLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56FB1927-B2C5-46AB-ABCC-DF68C619160C")
    ISingleDiaphragmLineFactory : public IDiaphragmLineFactory
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AlignmentID( 
            /* [in] */ CogoObjectID ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AlignmentID( 
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Station( 
            /* [in] */ Float64 station) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Station( 
            /* [retval][out] */ Float64 *pStation) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ BSTR orientation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ BSTR *orientation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DiaphragmLineID( 
            /* [retval][out] */ LineIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DiaphragmLineID( 
            /* [in] */ LineIDType newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Staggered( 
            /* [in] */ VARIANT_BOOL bStaggered) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Staggered( 
            /* [retval][out] */ VARIANT_BOOL *bStaggered) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LeftGirderLineID( 
            /* [in] */ GirderIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftGirderLineID( 
            /* [retval][out] */ GirderIDType *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RightGirderLineID( 
            /* [in] */ GirderIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightGirderLineID( 
            /* [retval][out] */ GirderIDType *ID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISingleDiaphragmLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISingleDiaphragmLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISingleDiaphragmLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISingleDiaphragmLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            ISingleDiaphragmLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IUnkArray **ppArrayDiaphagmLines);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ISingleDiaphragmLineFactory * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AlignmentID )( 
            ISingleDiaphragmLineFactory * This,
            /* [in] */ CogoObjectID ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlignmentID )( 
            ISingleDiaphragmLineFactory * This,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Station )( 
            ISingleDiaphragmLineFactory * This,
            /* [in] */ Float64 station);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Station )( 
            ISingleDiaphragmLineFactory * This,
            /* [retval][out] */ Float64 *pStation);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            ISingleDiaphragmLineFactory * This,
            /* [in] */ BSTR orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            ISingleDiaphragmLineFactory * This,
            /* [retval][out] */ BSTR *orientation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DiaphragmLineID )( 
            ISingleDiaphragmLineFactory * This,
            /* [retval][out] */ LineIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DiaphragmLineID )( 
            ISingleDiaphragmLineFactory * This,
            /* [in] */ LineIDType newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Staggered )( 
            ISingleDiaphragmLineFactory * This,
            /* [in] */ VARIANT_BOOL bStaggered);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Staggered )( 
            ISingleDiaphragmLineFactory * This,
            /* [retval][out] */ VARIANT_BOOL *bStaggered);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LeftGirderLineID )( 
            ISingleDiaphragmLineFactory * This,
            /* [in] */ GirderIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftGirderLineID )( 
            ISingleDiaphragmLineFactory * This,
            /* [retval][out] */ GirderIDType *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RightGirderLineID )( 
            ISingleDiaphragmLineFactory * This,
            /* [in] */ GirderIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightGirderLineID )( 
            ISingleDiaphragmLineFactory * This,
            /* [retval][out] */ GirderIDType *ID);
        
        END_INTERFACE
    } ISingleDiaphragmLineFactoryVtbl;

    interface ISingleDiaphragmLineFactory
    {
        CONST_VTBL struct ISingleDiaphragmLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISingleDiaphragmLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISingleDiaphragmLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISingleDiaphragmLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISingleDiaphragmLineFactory_Create(This,pBridge,ppArrayDiaphagmLines)	\
    ( (This)->lpVtbl -> Create(This,pBridge,ppArrayDiaphagmLines) ) 

#define ISingleDiaphragmLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 


#define ISingleDiaphragmLineFactory_put_AlignmentID(This,ID)	\
    ( (This)->lpVtbl -> put_AlignmentID(This,ID) ) 

#define ISingleDiaphragmLineFactory_get_AlignmentID(This,ID)	\
    ( (This)->lpVtbl -> get_AlignmentID(This,ID) ) 

#define ISingleDiaphragmLineFactory_put_Station(This,station)	\
    ( (This)->lpVtbl -> put_Station(This,station) ) 

#define ISingleDiaphragmLineFactory_get_Station(This,pStation)	\
    ( (This)->lpVtbl -> get_Station(This,pStation) ) 

#define ISingleDiaphragmLineFactory_put_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> put_Orientation(This,orientation) ) 

#define ISingleDiaphragmLineFactory_get_Orientation(This,orientation)	\
    ( (This)->lpVtbl -> get_Orientation(This,orientation) ) 

#define ISingleDiaphragmLineFactory_get_DiaphragmLineID(This,pVal)	\
    ( (This)->lpVtbl -> get_DiaphragmLineID(This,pVal) ) 

#define ISingleDiaphragmLineFactory_put_DiaphragmLineID(This,newVal)	\
    ( (This)->lpVtbl -> put_DiaphragmLineID(This,newVal) ) 

#define ISingleDiaphragmLineFactory_put_Staggered(This,bStaggered)	\
    ( (This)->lpVtbl -> put_Staggered(This,bStaggered) ) 

#define ISingleDiaphragmLineFactory_get_Staggered(This,bStaggered)	\
    ( (This)->lpVtbl -> get_Staggered(This,bStaggered) ) 

#define ISingleDiaphragmLineFactory_put_LeftGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> put_LeftGirderLineID(This,ID) ) 

#define ISingleDiaphragmLineFactory_get_LeftGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> get_LeftGirderLineID(This,ID) ) 

#define ISingleDiaphragmLineFactory_put_RightGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> put_RightGirderLineID(This,ID) ) 

#define ISingleDiaphragmLineFactory_get_RightGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> get_RightGirderLineID(This,ID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISingleDiaphragmLineFactory_INTERFACE_DEFINED__ */


#ifndef __IThroughPointDiaphragmLineFactory_INTERFACE_DEFINED__
#define __IThroughPointDiaphragmLineFactory_INTERFACE_DEFINED__

/* interface IThroughPointDiaphragmLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IThroughPointDiaphragmLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E479B523-613F-4383-B555-2E749CAFABE8")
    IThroughPointDiaphragmLineFactory : public IDiaphragmLineFactory
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Point( 
            /* [in] */ IPoint2d *point) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Point( 
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Direction( 
            /* [in] */ IDirection *direction) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ IDirection **direction) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DiaphragmLineID( 
            /* [retval][out] */ LineIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DiaphragmLineID( 
            /* [in] */ LineIDType newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Staggered( 
            /* [in] */ VARIANT_BOOL bStaggered) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Staggered( 
            /* [retval][out] */ VARIANT_BOOL *bStaggered) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LeftGirderLineID( 
            /* [in] */ GirderIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftGirderLineID( 
            /* [retval][out] */ GirderIDType *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RightGirderLineID( 
            /* [in] */ GirderIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightGirderLineID( 
            /* [retval][out] */ GirderIDType *ID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IThroughPointDiaphragmLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IThroughPointDiaphragmLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IThroughPointDiaphragmLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IUnkArray **ppArrayDiaphagmLines);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IThroughPointDiaphragmLineFactory * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Point )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [in] */ IPoint2d *point);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Point )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Direction )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [in] */ IDirection *direction);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Direction )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [retval][out] */ IDirection **direction);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DiaphragmLineID )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [retval][out] */ LineIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DiaphragmLineID )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [in] */ LineIDType newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Staggered )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [in] */ VARIANT_BOOL bStaggered);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Staggered )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [retval][out] */ VARIANT_BOOL *bStaggered);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LeftGirderLineID )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [in] */ GirderIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftGirderLineID )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [retval][out] */ GirderIDType *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RightGirderLineID )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [in] */ GirderIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightGirderLineID )( 
            IThroughPointDiaphragmLineFactory * This,
            /* [retval][out] */ GirderIDType *ID);
        
        END_INTERFACE
    } IThroughPointDiaphragmLineFactoryVtbl;

    interface IThroughPointDiaphragmLineFactory
    {
        CONST_VTBL struct IThroughPointDiaphragmLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IThroughPointDiaphragmLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IThroughPointDiaphragmLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IThroughPointDiaphragmLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IThroughPointDiaphragmLineFactory_Create(This,pBridge,ppArrayDiaphagmLines)	\
    ( (This)->lpVtbl -> Create(This,pBridge,ppArrayDiaphagmLines) ) 

#define IThroughPointDiaphragmLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 


#define IThroughPointDiaphragmLineFactory_put_Point(This,point)	\
    ( (This)->lpVtbl -> put_Point(This,point) ) 

#define IThroughPointDiaphragmLineFactory_get_Point(This,point)	\
    ( (This)->lpVtbl -> get_Point(This,point) ) 

#define IThroughPointDiaphragmLineFactory_put_Direction(This,direction)	\
    ( (This)->lpVtbl -> put_Direction(This,direction) ) 

#define IThroughPointDiaphragmLineFactory_get_Direction(This,direction)	\
    ( (This)->lpVtbl -> get_Direction(This,direction) ) 

#define IThroughPointDiaphragmLineFactory_get_DiaphragmLineID(This,pVal)	\
    ( (This)->lpVtbl -> get_DiaphragmLineID(This,pVal) ) 

#define IThroughPointDiaphragmLineFactory_put_DiaphragmLineID(This,newVal)	\
    ( (This)->lpVtbl -> put_DiaphragmLineID(This,newVal) ) 

#define IThroughPointDiaphragmLineFactory_put_Staggered(This,bStaggered)	\
    ( (This)->lpVtbl -> put_Staggered(This,bStaggered) ) 

#define IThroughPointDiaphragmLineFactory_get_Staggered(This,bStaggered)	\
    ( (This)->lpVtbl -> get_Staggered(This,bStaggered) ) 

#define IThroughPointDiaphragmLineFactory_put_LeftGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> put_LeftGirderLineID(This,ID) ) 

#define IThroughPointDiaphragmLineFactory_get_LeftGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> get_LeftGirderLineID(This,ID) ) 

#define IThroughPointDiaphragmLineFactory_put_RightGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> put_RightGirderLineID(This,ID) ) 

#define IThroughPointDiaphragmLineFactory_get_RightGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> get_RightGirderLineID(This,ID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IThroughPointDiaphragmLineFactory_INTERFACE_DEFINED__ */


#ifndef __IEqualSpaceDiaphragmLineFactory_INTERFACE_DEFINED__
#define __IEqualSpaceDiaphragmLineFactory_INTERFACE_DEFINED__

/* interface IEqualSpaceDiaphragmLineFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEqualSpaceDiaphragmLineFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FD9086BA-9DEA-4AF0-BDF9-5E67E7E0A1D0")
    IEqualSpaceDiaphragmLineFactory : public IDiaphragmLineFactory
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AlignmentID( 
            /* [in] */ CogoObjectID ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AlignmentID( 
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartStation( 
            /* [in] */ Float64 station) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartStation( 
            /* [retval][out] */ Float64 *pStation) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndStation( 
            /* [in] */ Float64 station) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndStation( 
            /* [retval][out] */ Float64 *pStation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DiaphragmLineID( 
            /* [retval][out] */ LineIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DiaphragmLineID( 
            /* [in] */ LineIDType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DiaphragmLineIDInc( 
            /* [retval][out] */ LineIDType *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DiaphragmLineIDInc( 
            /* [in] */ LineIDType newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Divisor( 
            /* [in] */ Int16 divisor) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Divisor( 
            /* [retval][out] */ Int16 *divisor) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Staggered( 
            /* [in] */ VARIANT_BOOL bStaggered) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Staggered( 
            /* [retval][out] */ VARIANT_BOOL *bStaggered) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LeftGirderLineID( 
            /* [in] */ GirderIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftGirderLineID( 
            /* [retval][out] */ GirderIDType *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RightGirderLineID( 
            /* [in] */ GirderIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightGirderLineID( 
            /* [retval][out] */ GirderIDType *ID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEqualSpaceDiaphragmLineFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEqualSpaceDiaphragmLineFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEqualSpaceDiaphragmLineFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IUnkArray **ppArrayDiaphagmLines);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEqualSpaceDiaphragmLineFactory * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AlignmentID )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ CogoObjectID ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlignmentID )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartStation )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ Float64 station);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartStation )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [retval][out] */ Float64 *pStation);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndStation )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ Float64 station);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndStation )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [retval][out] */ Float64 *pStation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DiaphragmLineID )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [retval][out] */ LineIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DiaphragmLineID )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ LineIDType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DiaphragmLineIDInc )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [retval][out] */ LineIDType *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DiaphragmLineIDInc )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ LineIDType newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Divisor )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ Int16 divisor);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Divisor )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [retval][out] */ Int16 *divisor);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Staggered )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ VARIANT_BOOL bStaggered);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Staggered )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [retval][out] */ VARIANT_BOOL *bStaggered);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LeftGirderLineID )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ GirderIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftGirderLineID )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [retval][out] */ GirderIDType *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RightGirderLineID )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [in] */ GirderIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightGirderLineID )( 
            IEqualSpaceDiaphragmLineFactory * This,
            /* [retval][out] */ GirderIDType *ID);
        
        END_INTERFACE
    } IEqualSpaceDiaphragmLineFactoryVtbl;

    interface IEqualSpaceDiaphragmLineFactory
    {
        CONST_VTBL struct IEqualSpaceDiaphragmLineFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEqualSpaceDiaphragmLineFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEqualSpaceDiaphragmLineFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEqualSpaceDiaphragmLineFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEqualSpaceDiaphragmLineFactory_Create(This,pBridge,ppArrayDiaphagmLines)	\
    ( (This)->lpVtbl -> Create(This,pBridge,ppArrayDiaphagmLines) ) 

#define IEqualSpaceDiaphragmLineFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 


#define IEqualSpaceDiaphragmLineFactory_put_AlignmentID(This,ID)	\
    ( (This)->lpVtbl -> put_AlignmentID(This,ID) ) 

#define IEqualSpaceDiaphragmLineFactory_get_AlignmentID(This,ID)	\
    ( (This)->lpVtbl -> get_AlignmentID(This,ID) ) 

#define IEqualSpaceDiaphragmLineFactory_put_StartStation(This,station)	\
    ( (This)->lpVtbl -> put_StartStation(This,station) ) 

#define IEqualSpaceDiaphragmLineFactory_get_StartStation(This,pStation)	\
    ( (This)->lpVtbl -> get_StartStation(This,pStation) ) 

#define IEqualSpaceDiaphragmLineFactory_put_EndStation(This,station)	\
    ( (This)->lpVtbl -> put_EndStation(This,station) ) 

#define IEqualSpaceDiaphragmLineFactory_get_EndStation(This,pStation)	\
    ( (This)->lpVtbl -> get_EndStation(This,pStation) ) 

#define IEqualSpaceDiaphragmLineFactory_get_DiaphragmLineID(This,pVal)	\
    ( (This)->lpVtbl -> get_DiaphragmLineID(This,pVal) ) 

#define IEqualSpaceDiaphragmLineFactory_put_DiaphragmLineID(This,newVal)	\
    ( (This)->lpVtbl -> put_DiaphragmLineID(This,newVal) ) 

#define IEqualSpaceDiaphragmLineFactory_get_DiaphragmLineIDInc(This,pVal)	\
    ( (This)->lpVtbl -> get_DiaphragmLineIDInc(This,pVal) ) 

#define IEqualSpaceDiaphragmLineFactory_put_DiaphragmLineIDInc(This,newVal)	\
    ( (This)->lpVtbl -> put_DiaphragmLineIDInc(This,newVal) ) 

#define IEqualSpaceDiaphragmLineFactory_put_Divisor(This,divisor)	\
    ( (This)->lpVtbl -> put_Divisor(This,divisor) ) 

#define IEqualSpaceDiaphragmLineFactory_get_Divisor(This,divisor)	\
    ( (This)->lpVtbl -> get_Divisor(This,divisor) ) 

#define IEqualSpaceDiaphragmLineFactory_put_Staggered(This,bStaggered)	\
    ( (This)->lpVtbl -> put_Staggered(This,bStaggered) ) 

#define IEqualSpaceDiaphragmLineFactory_get_Staggered(This,bStaggered)	\
    ( (This)->lpVtbl -> get_Staggered(This,bStaggered) ) 

#define IEqualSpaceDiaphragmLineFactory_put_LeftGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> put_LeftGirderLineID(This,ID) ) 

#define IEqualSpaceDiaphragmLineFactory_get_LeftGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> get_LeftGirderLineID(This,ID) ) 

#define IEqualSpaceDiaphragmLineFactory_put_RightGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> put_RightGirderLineID(This,ID) ) 

#define IEqualSpaceDiaphragmLineFactory_get_RightGirderLineID(This,ID)	\
    ( (This)->lpVtbl -> get_RightGirderLineID(This,ID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEqualSpaceDiaphragmLineFactory_INTERFACE_DEFINED__ */


#ifndef __IDiaphragmLine_INTERFACE_DEFINED__
#define __IDiaphragmLine_INTERFACE_DEFINED__

/* interface IDiaphragmLine */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDiaphragmLine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("24885559-FABB-4327-B30D-B2EE5C95C5C1")
    IDiaphragmLine : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LineIDType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [in] */ GirderIDType gdrLineID,
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Point( 
            /* [in] */ GirderIDType gdrLineID,
            /* [in] */ EndType endType,
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDiaphragmLineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDiaphragmLine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDiaphragmLine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDiaphragmLine * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IDiaphragmLine * This,
            /* [retval][out] */ LineIDType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IDiaphragmLine * This,
            /* [in] */ GirderIDType gdrLineID,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Point )( 
            IDiaphragmLine * This,
            /* [in] */ GirderIDType gdrLineID,
            /* [in] */ EndType endType,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        END_INTERFACE
    } IDiaphragmLineVtbl;

    interface IDiaphragmLine
    {
        CONST_VTBL struct IDiaphragmLineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDiaphragmLine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDiaphragmLine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDiaphragmLine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDiaphragmLine_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IDiaphragmLine_get_Length(This,gdrLineID,pLength)	\
    ( (This)->lpVtbl -> get_Length(This,gdrLineID,pLength) ) 

#define IDiaphragmLine_get_Point(This,gdrLineID,endType,ppPoint)	\
    ( (This)->lpVtbl -> get_Point(This,gdrLineID,endType,ppPoint) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDiaphragmLine_INTERFACE_DEFINED__ */


#ifndef __IDeckBoundary_INTERFACE_DEFINED__
#define __IDeckBoundary_INTERFACE_DEFINED__

/* interface IDeckBoundary */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDeckBoundary;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8FC6DE2C-969D-4F74-BD77-9355C1C4BEB6")
    IDeckBoundary : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Perimeter( 
            /* [in] */ CollectionIndexType nMinPointsPerSide,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PerimeterEx( 
            /* [in] */ CollectionIndexType nMinPointsPerSide,
            /* [in] */ PierIDType startPierID,
            /* [in] */ PierIDType endPierID,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TransverseEdgePoints( 
            /* [in] */ EndType endType,
            /* [out] */ IPoint2d **ppLeft,
            /* [out] */ IPoint2d **ppLeftBreak,
            /* [out] */ IPoint2d **ppRightBreak,
            /* [out] */ IPoint2d **ppRight) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EdgePath( 
            /* [in] */ SideType side,
            /* [in] */ VARIANT_BOOL vbLayoutPath,
            /* [retval][out] */ IPath **path) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDeckBoundaryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDeckBoundary * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDeckBoundary * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDeckBoundary * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Perimeter )( 
            IDeckBoundary * This,
            /* [in] */ CollectionIndexType nMinPointsPerSide,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PerimeterEx )( 
            IDeckBoundary * This,
            /* [in] */ CollectionIndexType nMinPointsPerSide,
            /* [in] */ PierIDType startPierID,
            /* [in] */ PierIDType endPierID,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransverseEdgePoints )( 
            IDeckBoundary * This,
            /* [in] */ EndType endType,
            /* [out] */ IPoint2d **ppLeft,
            /* [out] */ IPoint2d **ppLeftBreak,
            /* [out] */ IPoint2d **ppRightBreak,
            /* [out] */ IPoint2d **ppRight);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EdgePath )( 
            IDeckBoundary * This,
            /* [in] */ SideType side,
            /* [in] */ VARIANT_BOOL vbLayoutPath,
            /* [retval][out] */ IPath **path);
        
        END_INTERFACE
    } IDeckBoundaryVtbl;

    interface IDeckBoundary
    {
        CONST_VTBL struct IDeckBoundaryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDeckBoundary_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDeckBoundary_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDeckBoundary_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDeckBoundary_get_Perimeter(This,nMinPointsPerSide,points)	\
    ( (This)->lpVtbl -> get_Perimeter(This,nMinPointsPerSide,points) ) 

#define IDeckBoundary_get_PerimeterEx(This,nMinPointsPerSide,startPierID,endPierID,points)	\
    ( (This)->lpVtbl -> get_PerimeterEx(This,nMinPointsPerSide,startPierID,endPierID,points) ) 

#define IDeckBoundary_get_TransverseEdgePoints(This,endType,ppLeft,ppLeftBreak,ppRightBreak,ppRight)	\
    ( (This)->lpVtbl -> get_TransverseEdgePoints(This,endType,ppLeft,ppLeftBreak,ppRightBreak,ppRight) ) 

#define IDeckBoundary_get_EdgePath(This,side,vbLayoutPath,path)	\
    ( (This)->lpVtbl -> get_EdgePath(This,side,vbLayoutPath,path) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDeckBoundary_INTERFACE_DEFINED__ */


#ifndef __IDeckBoundaryFactory_INTERFACE_DEFINED__
#define __IDeckBoundaryFactory_INTERFACE_DEFINED__

/* interface IDeckBoundaryFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDeckBoundaryFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F89D246A-8F7D-4A27-A27E-DD73BE332087")
    IDeckBoundaryFactory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IDeckBoundary **ppDeckBoundary) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDeckBoundaryFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDeckBoundaryFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDeckBoundaryFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDeckBoundaryFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IDeckBoundaryFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IDeckBoundary **ppDeckBoundary);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IDeckBoundaryFactory * This);
        
        END_INTERFACE
    } IDeckBoundaryFactoryVtbl;

    interface IDeckBoundaryFactory
    {
        CONST_VTBL struct IDeckBoundaryFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDeckBoundaryFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDeckBoundaryFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDeckBoundaryFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDeckBoundaryFactory_Create(This,pBridge,ppDeckBoundary)	\
    ( (This)->lpVtbl -> Create(This,pBridge,ppDeckBoundary) ) 

#define IDeckBoundaryFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDeckBoundaryFactory_INTERFACE_DEFINED__ */


#ifndef __ISimpleDeckBoundaryFactory_INTERFACE_DEFINED__
#define __ISimpleDeckBoundaryFactory_INTERFACE_DEFINED__

/* interface ISimpleDeckBoundaryFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISimpleDeckBoundaryFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AA59EF93-7A3C-493A-BF37-B38B3644A653")
    ISimpleDeckBoundaryFactory : public IDeckBoundaryFactory
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TransverseEdgeID( 
            /* [in] */ EndType end,
            /* [in] */ LineIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TransverseEdgeID( 
            /* [in] */ EndType end,
            /* [retval][out] */ LineIDType *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TransverseEdgeType( 
            /* [in] */ EndType end,
            /* [in] */ DeckBoundaryEdgeType edgeType) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TransverseEdgeType( 
            /* [in] */ EndType end,
            /* [retval][out] */ DeckBoundaryEdgeType *edgeType) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EdgeID( 
            /* [in] */ SideType side,
            /* [in] */ PathIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EdgeID( 
            /* [in] */ SideType side,
            /* [retval][out] */ PathIDType *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EdgeBreakID( 
            /* [in] */ SideType side,
            /* [in] */ PathIDType ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EdgeBreakID( 
            /* [in] */ SideType side,
            /* [retval][out] */ PathIDType *ID) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BreakEdge( 
            /* [in] */ EndType end,
            /* [in] */ SideType side,
            /* [in] */ VARIANT_BOOL bBreak) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BreakEdge( 
            /* [in] */ EndType end,
            /* [in] */ SideType side,
            /* [retval][out] */ VARIANT_BOOL *bBreak) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISimpleDeckBoundaryFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISimpleDeckBoundaryFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISimpleDeckBoundaryFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ IBridgeGeometry *pBridge,
            /* [retval][out] */ IDeckBoundary **ppDeckBoundary);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ISimpleDeckBoundaryFactory * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransverseEdgeID )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ EndType end,
            /* [in] */ LineIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransverseEdgeID )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ EndType end,
            /* [retval][out] */ LineIDType *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransverseEdgeType )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ EndType end,
            /* [in] */ DeckBoundaryEdgeType edgeType);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransverseEdgeType )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ EndType end,
            /* [retval][out] */ DeckBoundaryEdgeType *edgeType);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EdgeID )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ SideType side,
            /* [in] */ PathIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EdgeID )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ SideType side,
            /* [retval][out] */ PathIDType *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EdgeBreakID )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ SideType side,
            /* [in] */ PathIDType ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EdgeBreakID )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ SideType side,
            /* [retval][out] */ PathIDType *ID);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BreakEdge )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ EndType end,
            /* [in] */ SideType side,
            /* [in] */ VARIANT_BOOL bBreak);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BreakEdge )( 
            ISimpleDeckBoundaryFactory * This,
            /* [in] */ EndType end,
            /* [in] */ SideType side,
            /* [retval][out] */ VARIANT_BOOL *bBreak);
        
        END_INTERFACE
    } ISimpleDeckBoundaryFactoryVtbl;

    interface ISimpleDeckBoundaryFactory
    {
        CONST_VTBL struct ISimpleDeckBoundaryFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISimpleDeckBoundaryFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISimpleDeckBoundaryFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISimpleDeckBoundaryFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISimpleDeckBoundaryFactory_Create(This,pBridge,ppDeckBoundary)	\
    ( (This)->lpVtbl -> Create(This,pBridge,ppDeckBoundary) ) 

#define ISimpleDeckBoundaryFactory_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 


#define ISimpleDeckBoundaryFactory_put_TransverseEdgeID(This,end,ID)	\
    ( (This)->lpVtbl -> put_TransverseEdgeID(This,end,ID) ) 

#define ISimpleDeckBoundaryFactory_get_TransverseEdgeID(This,end,ID)	\
    ( (This)->lpVtbl -> get_TransverseEdgeID(This,end,ID) ) 

#define ISimpleDeckBoundaryFactory_put_TransverseEdgeType(This,end,edgeType)	\
    ( (This)->lpVtbl -> put_TransverseEdgeType(This,end,edgeType) ) 

#define ISimpleDeckBoundaryFactory_get_TransverseEdgeType(This,end,edgeType)	\
    ( (This)->lpVtbl -> get_TransverseEdgeType(This,end,edgeType) ) 

#define ISimpleDeckBoundaryFactory_put_EdgeID(This,side,ID)	\
    ( (This)->lpVtbl -> put_EdgeID(This,side,ID) ) 

#define ISimpleDeckBoundaryFactory_get_EdgeID(This,side,ID)	\
    ( (This)->lpVtbl -> get_EdgeID(This,side,ID) ) 

#define ISimpleDeckBoundaryFactory_put_EdgeBreakID(This,side,ID)	\
    ( (This)->lpVtbl -> put_EdgeBreakID(This,side,ID) ) 

#define ISimpleDeckBoundaryFactory_get_EdgeBreakID(This,side,ID)	\
    ( (This)->lpVtbl -> get_EdgeBreakID(This,side,ID) ) 

#define ISimpleDeckBoundaryFactory_put_BreakEdge(This,end,side,bBreak)	\
    ( (This)->lpVtbl -> put_BreakEdge(This,end,side,bBreak) ) 

#define ISimpleDeckBoundaryFactory_get_BreakEdge(This,end,side,bBreak)	\
    ( (This)->lpVtbl -> get_BreakEdge(This,end,side,bBreak) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISimpleDeckBoundaryFactory_INTERFACE_DEFINED__ */


#ifndef __IBridgeGeometry_INTERFACE_DEFINED__
#define __IBridgeGeometry_INTERFACE_DEFINED__

/* interface IBridgeGeometry */
/* [unique][helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBridgeGeometry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CF09FA44-1095-4F63-B3DB-C4BA8617A98E")
    IBridgeGeometry : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_CogoModel( 
            /* [in] */ ICogoModel *pCogoModel) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CogoModel( 
            /* [retval][out] */ ICogoModel **pCogoModel) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Alignment( 
            /* [in] */ CogoObjectID ID,
            /* [in] */ IAlignment *pAligment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Alignment( 
            /* [in] */ CogoObjectID ID,
            /* [retval][out] */ IAlignment **pAlignment) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BridgeAlignmentID( 
            /* [in] */ CogoObjectID ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BridgeAlignmentID( 
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BridgeAlignment( 
            /* [retval][out] */ IAlignment **alignment) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AlignmentOffset( 
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AlignmentOffset( 
            /* [retval][out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BridgeLine( 
            /* [retval][out] */ IPath **bridgeLine) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateLayoutLines( 
            /* [in] */ ILayoutLineFactory *pFactory) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindLayoutLine( 
            /* [in] */ LineIDType ID,
            /* [retval][out] */ IPath **path) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutLineCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreatePierLine( 
            /* [in] */ PierIDType ID,
            /* [in] */ CogoObjectID alignmentID,
            /* [in] */ VARIANT station,
            /* [in] */ BSTR orientation,
            /* [in] */ Float64 width,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPierLine **ppPier) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPierLine( 
            /* [in] */ PierIndexType idx,
            /* [retval][out] */ IPierLine **ppPier) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindPierLine( 
            /* [in] */ PierIDType ID,
            /* [retval][out] */ IPierLine **ppPier) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PierLineCount( 
            /* [retval][out] */ PierIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateGirderLines( 
            /* [in] */ IGirderLineFactory *pFactory) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindGirderLine( 
            /* [in] */ GirderIDType ID,
            /* [retval][out] */ IGirderLine **ppGirderLine) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GirderLineCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateDiaphragmLines( 
            /* [in] */ IDiaphragmLineFactory *pFactory) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindDiaphragmLine( 
            /* [in] */ LineIDType ID,
            /* [retval][out] */ IDiaphragmLine **ppDiaphragmLine) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DiaphragmLineCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateDeckBoundary( 
            /* [in] */ IDeckBoundaryFactory *pFactory) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DeckBoundary( 
            /* [retval][out] */ IDeckBoundary **ppDeckBoundary) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateGeometry( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBridgeGeometryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBridgeGeometry * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBridgeGeometry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBridgeGeometry * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_CogoModel )( 
            IBridgeGeometry * This,
            /* [in] */ ICogoModel *pCogoModel);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CogoModel )( 
            IBridgeGeometry * This,
            /* [retval][out] */ ICogoModel **pCogoModel);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Alignment )( 
            IBridgeGeometry * This,
            /* [in] */ CogoObjectID ID,
            /* [in] */ IAlignment *pAligment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alignment )( 
            IBridgeGeometry * This,
            /* [in] */ CogoObjectID ID,
            /* [retval][out] */ IAlignment **pAlignment);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BridgeAlignmentID )( 
            IBridgeGeometry * This,
            /* [in] */ CogoObjectID ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BridgeAlignmentID )( 
            IBridgeGeometry * This,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BridgeAlignment )( 
            IBridgeGeometry * This,
            /* [retval][out] */ IAlignment **alignment);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AlignmentOffset )( 
            IBridgeGeometry * This,
            /* [in] */ Float64 offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlignmentOffset )( 
            IBridgeGeometry * This,
            /* [retval][out] */ Float64 *offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BridgeLine )( 
            IBridgeGeometry * This,
            /* [retval][out] */ IPath **bridgeLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateLayoutLines )( 
            IBridgeGeometry * This,
            /* [in] */ ILayoutLineFactory *pFactory);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindLayoutLine )( 
            IBridgeGeometry * This,
            /* [in] */ LineIDType ID,
            /* [retval][out] */ IPath **path);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutLineCount )( 
            IBridgeGeometry * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatePierLine )( 
            IBridgeGeometry * This,
            /* [in] */ PierIDType ID,
            /* [in] */ CogoObjectID alignmentID,
            /* [in] */ VARIANT station,
            /* [in] */ BSTR orientation,
            /* [in] */ Float64 width,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPierLine **ppPier);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPierLine )( 
            IBridgeGeometry * This,
            /* [in] */ PierIndexType idx,
            /* [retval][out] */ IPierLine **ppPier);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindPierLine )( 
            IBridgeGeometry * This,
            /* [in] */ PierIDType ID,
            /* [retval][out] */ IPierLine **ppPier);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PierLineCount )( 
            IBridgeGeometry * This,
            /* [retval][out] */ PierIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateGirderLines )( 
            IBridgeGeometry * This,
            /* [in] */ IGirderLineFactory *pFactory);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindGirderLine )( 
            IBridgeGeometry * This,
            /* [in] */ GirderIDType ID,
            /* [retval][out] */ IGirderLine **ppGirderLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GirderLineCount )( 
            IBridgeGeometry * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateDiaphragmLines )( 
            IBridgeGeometry * This,
            /* [in] */ IDiaphragmLineFactory *pFactory);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindDiaphragmLine )( 
            IBridgeGeometry * This,
            /* [in] */ LineIDType ID,
            /* [retval][out] */ IDiaphragmLine **ppDiaphragmLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DiaphragmLineCount )( 
            IBridgeGeometry * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateDeckBoundary )( 
            IBridgeGeometry * This,
            /* [in] */ IDeckBoundaryFactory *pFactory);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeckBoundary )( 
            IBridgeGeometry * This,
            /* [retval][out] */ IDeckBoundary **ppDeckBoundary);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateGeometry )( 
            IBridgeGeometry * This);
        
        END_INTERFACE
    } IBridgeGeometryVtbl;

    interface IBridgeGeometry
    {
        CONST_VTBL struct IBridgeGeometryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBridgeGeometry_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBridgeGeometry_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBridgeGeometry_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBridgeGeometry_putref_CogoModel(This,pCogoModel)	\
    ( (This)->lpVtbl -> putref_CogoModel(This,pCogoModel) ) 

#define IBridgeGeometry_get_CogoModel(This,pCogoModel)	\
    ( (This)->lpVtbl -> get_CogoModel(This,pCogoModel) ) 

#define IBridgeGeometry_putref_Alignment(This,ID,pAligment)	\
    ( (This)->lpVtbl -> putref_Alignment(This,ID,pAligment) ) 

#define IBridgeGeometry_get_Alignment(This,ID,pAlignment)	\
    ( (This)->lpVtbl -> get_Alignment(This,ID,pAlignment) ) 

#define IBridgeGeometry_put_BridgeAlignmentID(This,ID)	\
    ( (This)->lpVtbl -> put_BridgeAlignmentID(This,ID) ) 

#define IBridgeGeometry_get_BridgeAlignmentID(This,ID)	\
    ( (This)->lpVtbl -> get_BridgeAlignmentID(This,ID) ) 

#define IBridgeGeometry_get_BridgeAlignment(This,alignment)	\
    ( (This)->lpVtbl -> get_BridgeAlignment(This,alignment) ) 

#define IBridgeGeometry_put_AlignmentOffset(This,offset)	\
    ( (This)->lpVtbl -> put_AlignmentOffset(This,offset) ) 

#define IBridgeGeometry_get_AlignmentOffset(This,offset)	\
    ( (This)->lpVtbl -> get_AlignmentOffset(This,offset) ) 

#define IBridgeGeometry_get_BridgeLine(This,bridgeLine)	\
    ( (This)->lpVtbl -> get_BridgeLine(This,bridgeLine) ) 

#define IBridgeGeometry_CreateLayoutLines(This,pFactory)	\
    ( (This)->lpVtbl -> CreateLayoutLines(This,pFactory) ) 

#define IBridgeGeometry_FindLayoutLine(This,ID,path)	\
    ( (This)->lpVtbl -> FindLayoutLine(This,ID,path) ) 

#define IBridgeGeometry_get_LayoutLineCount(This,pVal)	\
    ( (This)->lpVtbl -> get_LayoutLineCount(This,pVal) ) 

#define IBridgeGeometry_CreatePierLine(This,ID,alignmentID,station,orientation,width,offset,ppPier)	\
    ( (This)->lpVtbl -> CreatePierLine(This,ID,alignmentID,station,orientation,width,offset,ppPier) ) 

#define IBridgeGeometry_GetPierLine(This,idx,ppPier)	\
    ( (This)->lpVtbl -> GetPierLine(This,idx,ppPier) ) 

#define IBridgeGeometry_FindPierLine(This,ID,ppPier)	\
    ( (This)->lpVtbl -> FindPierLine(This,ID,ppPier) ) 

#define IBridgeGeometry_get_PierLineCount(This,pVal)	\
    ( (This)->lpVtbl -> get_PierLineCount(This,pVal) ) 

#define IBridgeGeometry_CreateGirderLines(This,pFactory)	\
    ( (This)->lpVtbl -> CreateGirderLines(This,pFactory) ) 

#define IBridgeGeometry_FindGirderLine(This,ID,ppGirderLine)	\
    ( (This)->lpVtbl -> FindGirderLine(This,ID,ppGirderLine) ) 

#define IBridgeGeometry_get_GirderLineCount(This,pVal)	\
    ( (This)->lpVtbl -> get_GirderLineCount(This,pVal) ) 

#define IBridgeGeometry_CreateDiaphragmLines(This,pFactory)	\
    ( (This)->lpVtbl -> CreateDiaphragmLines(This,pFactory) ) 

#define IBridgeGeometry_FindDiaphragmLine(This,ID,ppDiaphragmLine)	\
    ( (This)->lpVtbl -> FindDiaphragmLine(This,ID,ppDiaphragmLine) ) 

#define IBridgeGeometry_get_DiaphragmLineCount(This,pVal)	\
    ( (This)->lpVtbl -> get_DiaphragmLineCount(This,pVal) ) 

#define IBridgeGeometry_CreateDeckBoundary(This,pFactory)	\
    ( (This)->lpVtbl -> CreateDeckBoundary(This,pFactory) ) 

#define IBridgeGeometry_get_DeckBoundary(This,ppDeckBoundary)	\
    ( (This)->lpVtbl -> get_DeckBoundary(This,ppDeckBoundary) ) 

#define IBridgeGeometry_UpdateGeometry(This)	\
    ( (This)->lpVtbl -> UpdateGeometry(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBridgeGeometry_INTERFACE_DEFINED__ */



#ifndef __WBFLBridgeGeometry_LIBRARY_DEFINED__
#define __WBFLBridgeGeometry_LIBRARY_DEFINED__

/* library WBFLBridgeGeometry */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WBFLBridgeGeometry;

EXTERN_C const CLSID CLSID_BridgeGeometry;

#ifdef __cplusplus

class DECLSPEC_UUID("24D75303-8425-4590-913E-FF2908F65BD1")
BridgeGeometry;
#endif

EXTERN_C const CLSID CLSID_PierLine;

#ifdef __cplusplus

class DECLSPEC_UUID("9865B17B-5E4C-430B-9020-A5D5EC999858")
PierLine;
#endif

EXTERN_C const CLSID CLSID_PierLineCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("66394ACF-2A3E-43EB-94EE-0E7CE50A8904")
PierLineCollection;
#endif

EXTERN_C const CLSID CLSID_AlignmentOffsetLayoutLineFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("6B593F0D-688B-48B2-BC03-5399D1BDAA1B")
AlignmentOffsetLayoutLineFactory;
#endif

EXTERN_C const CLSID CLSID_SimpleLayoutLineFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("71E25E05-E16B-415C-9812-9A2F1EFD9A4B")
SimpleLayoutLineFactory;
#endif

EXTERN_C const CLSID CLSID_UniformSpacingLayoutLineFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("4FA7EC00-ADFB-4F50-A9E6-0A3142090639")
UniformSpacingLayoutLineFactory;
#endif

EXTERN_C const CLSID CLSID_GirderLine;

#ifdef __cplusplus

class DECLSPEC_UUID("189665C5-3B81-405B-B011-B78FF2036467")
GirderLine;
#endif

EXTERN_C const CLSID CLSID_DiaphragmLine;

#ifdef __cplusplus

class DECLSPEC_UUID("3F5A914A-73B6-43F6-A12B-D545B6B829CE")
DiaphragmLine;
#endif

EXTERN_C const CLSID CLSID_DeckBoundary;

#ifdef __cplusplus

class DECLSPEC_UUID("E66BB224-9C23-47FE-836A-A59945BB46DE")
DeckBoundary;
#endif

EXTERN_C const CLSID CLSID_SingleGirderLineFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("FF6273A8-1037-4CCE-B494-F43459E65800")
SingleGirderLineFactory;
#endif

EXTERN_C const CLSID CLSID_SimpleGirderLineFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("055CA73B-DD1F-4BC0-A6E5-C13729C16243")
SimpleGirderLineFactory;
#endif

EXTERN_C const CLSID CLSID_EqualSpaceDiaphragmLineFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("FF0B7F56-329E-4DB3-BF9C-E076555C1EEE")
EqualSpaceDiaphragmLineFactory;
#endif

EXTERN_C const CLSID CLSID_SingleDiaphragmLineFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("17FE1E15-7E72-4F4E-AC48-37E1497D0806")
SingleDiaphragmLineFactory;
#endif

EXTERN_C const CLSID CLSID_ThroughPointDiaphragmLineFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("F95676E6-9741-49C0-A3A4-15D9627BDCD8")
ThroughPointDiaphragmLineFactory;
#endif

EXTERN_C const CLSID CLSID_SimpleDeckBoundaryFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("132789EE-9C31-4D4D-8129-AD733BFA215B")
SimpleDeckBoundaryFactory;
#endif
#endif /* __WBFLBridgeGeometry_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


