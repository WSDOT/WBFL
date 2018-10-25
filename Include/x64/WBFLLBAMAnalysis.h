

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:29:06 2017
 */
/* Compiler settings for ..\..\Include\WBFLLBAMAnalysis.idl:
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


#ifndef __WBFLLBAMAnalysis_h__
#define __WBFLLBAMAnalysis_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAnalysisPOIs_FWD_DEFINED__
#define __IAnalysisPOIs_FWD_DEFINED__
typedef interface IAnalysisPOIs IAnalysisPOIs;

#endif 	/* __IAnalysisPOIs_FWD_DEFINED__ */


#ifndef __ISectionResult3D_FWD_DEFINED__
#define __ISectionResult3D_FWD_DEFINED__
typedef interface ISectionResult3D ISectionResult3D;

#endif 	/* __ISectionResult3D_FWD_DEFINED__ */


#ifndef __IEnumSectionResult3D_FWD_DEFINED__
#define __IEnumSectionResult3D_FWD_DEFINED__
typedef interface IEnumSectionResult3D IEnumSectionResult3D;

#endif 	/* __IEnumSectionResult3D_FWD_DEFINED__ */


#ifndef __ISectionResult3Ds_FWD_DEFINED__
#define __ISectionResult3Ds_FWD_DEFINED__
typedef interface ISectionResult3Ds ISectionResult3Ds;

#endif 	/* __ISectionResult3Ds_FWD_DEFINED__ */


#ifndef __IResult3D_FWD_DEFINED__
#define __IResult3D_FWD_DEFINED__
typedef interface IResult3D IResult3D;

#endif 	/* __IResult3D_FWD_DEFINED__ */


#ifndef __IEnumResult3D_FWD_DEFINED__
#define __IEnumResult3D_FWD_DEFINED__
typedef interface IEnumResult3D IEnumResult3D;

#endif 	/* __IEnumResult3D_FWD_DEFINED__ */


#ifndef __IResult3Ds_FWD_DEFINED__
#define __IResult3Ds_FWD_DEFINED__
typedef interface IResult3Ds IResult3Ds;

#endif 	/* __IResult3Ds_FWD_DEFINED__ */


#ifndef __IStressResult_FWD_DEFINED__
#define __IStressResult_FWD_DEFINED__
typedef interface IStressResult IStressResult;

#endif 	/* __IStressResult_FWD_DEFINED__ */


#ifndef __IEnumStressResult_FWD_DEFINED__
#define __IEnumStressResult_FWD_DEFINED__
typedef interface IEnumStressResult IEnumStressResult;

#endif 	/* __IEnumStressResult_FWD_DEFINED__ */


#ifndef __IStressResults_FWD_DEFINED__
#define __IStressResults_FWD_DEFINED__
typedef interface IStressResults IStressResults;

#endif 	/* __IStressResults_FWD_DEFINED__ */


#ifndef __ISectionStressResult_FWD_DEFINED__
#define __ISectionStressResult_FWD_DEFINED__
typedef interface ISectionStressResult ISectionStressResult;

#endif 	/* __ISectionStressResult_FWD_DEFINED__ */


#ifndef __IEnumSectionStressResult_FWD_DEFINED__
#define __IEnumSectionStressResult_FWD_DEFINED__
typedef interface IEnumSectionStressResult IEnumSectionStressResult;

#endif 	/* __IEnumSectionStressResult_FWD_DEFINED__ */


#ifndef __ISectionStressResults_FWD_DEFINED__
#define __ISectionStressResults_FWD_DEFINED__
typedef interface ISectionStressResults ISectionStressResults;

#endif 	/* __ISectionStressResults_FWD_DEFINED__ */


#ifndef __IDependOnLBAM_FWD_DEFINED__
#define __IDependOnLBAM_FWD_DEFINED__
typedef interface IDependOnLBAM IDependOnLBAM;

#endif 	/* __IDependOnLBAM_FWD_DEFINED__ */


#ifndef __ILoadGroupResponse_FWD_DEFINED__
#define __ILoadGroupResponse_FWD_DEFINED__
typedef interface ILoadGroupResponse ILoadGroupResponse;

#endif 	/* __ILoadGroupResponse_FWD_DEFINED__ */


#ifndef __IDiagnostics_FWD_DEFINED__
#define __IDiagnostics_FWD_DEFINED__
typedef interface IDiagnostics IDiagnostics;

#endif 	/* __IDiagnostics_FWD_DEFINED__ */


#ifndef __IUnitLoadResponse_FWD_DEFINED__
#define __IUnitLoadResponse_FWD_DEFINED__
typedef interface IUnitLoadResponse IUnitLoadResponse;

#endif 	/* __IUnitLoadResponse_FWD_DEFINED__ */


#ifndef __IInfluenceLine_FWD_DEFINED__
#define __IInfluenceLine_FWD_DEFINED__
typedef interface IInfluenceLine IInfluenceLine;

#endif 	/* __IInfluenceLine_FWD_DEFINED__ */


#ifndef __IInfluenceLineResponse_FWD_DEFINED__
#define __IInfluenceLineResponse_FWD_DEFINED__
typedef interface IInfluenceLineResponse IInfluenceLineResponse;

#endif 	/* __IInfluenceLineResponse_FWD_DEFINED__ */


#ifndef __ILiveLoadNegativeMomentRegion_FWD_DEFINED__
#define __ILiveLoadNegativeMomentRegion_FWD_DEFINED__
typedef interface ILiveLoadNegativeMomentRegion ILiveLoadNegativeMomentRegion;

#endif 	/* __ILiveLoadNegativeMomentRegion_FWD_DEFINED__ */


#ifndef __IContraflexureResponse_FWD_DEFINED__
#define __IContraflexureResponse_FWD_DEFINED__
typedef interface IContraflexureResponse IContraflexureResponse;

#endif 	/* __IContraflexureResponse_FWD_DEFINED__ */


#ifndef __IGetFemForLoadGroupResponse_FWD_DEFINED__
#define __IGetFemForLoadGroupResponse_FWD_DEFINED__
typedef interface IGetFemForLoadGroupResponse IGetFemForLoadGroupResponse;

#endif 	/* __IGetFemForLoadGroupResponse_FWD_DEFINED__ */


#ifndef __IGetActiveLoadGroups_FWD_DEFINED__
#define __IGetActiveLoadGroups_FWD_DEFINED__
typedef interface IGetActiveLoadGroups IGetActiveLoadGroups;

#endif 	/* __IGetActiveLoadGroups_FWD_DEFINED__ */


#ifndef __IGetDistributionFactors_FWD_DEFINED__
#define __IGetDistributionFactors_FWD_DEFINED__
typedef interface IGetDistributionFactors IGetDistributionFactors;

#endif 	/* __IGetDistributionFactors_FWD_DEFINED__ */


#ifndef __IGetSegmentCrossSection_FWD_DEFINED__
#define __IGetSegmentCrossSection_FWD_DEFINED__
typedef interface IGetSegmentCrossSection IGetSegmentCrossSection;

#endif 	/* __IGetSegmentCrossSection_FWD_DEFINED__ */


#ifndef __IGetStressPoints_FWD_DEFINED__
#define __IGetStressPoints_FWD_DEFINED__
typedef interface IGetStressPoints IGetStressPoints;

#endif 	/* __IGetStressPoints_FWD_DEFINED__ */


#ifndef __SectionResult3D_FWD_DEFINED__
#define __SectionResult3D_FWD_DEFINED__

#ifdef __cplusplus
typedef class SectionResult3D SectionResult3D;
#else
typedef struct SectionResult3D SectionResult3D;
#endif /* __cplusplus */

#endif 	/* __SectionResult3D_FWD_DEFINED__ */


#ifndef __Result3D_FWD_DEFINED__
#define __Result3D_FWD_DEFINED__

#ifdef __cplusplus
typedef class Result3D Result3D;
#else
typedef struct Result3D Result3D;
#endif /* __cplusplus */

#endif 	/* __Result3D_FWD_DEFINED__ */


#ifndef __SectionResult3Ds_FWD_DEFINED__
#define __SectionResult3Ds_FWD_DEFINED__

#ifdef __cplusplus
typedef class SectionResult3Ds SectionResult3Ds;
#else
typedef struct SectionResult3Ds SectionResult3Ds;
#endif /* __cplusplus */

#endif 	/* __SectionResult3Ds_FWD_DEFINED__ */


#ifndef __Result3Ds_FWD_DEFINED__
#define __Result3Ds_FWD_DEFINED__

#ifdef __cplusplus
typedef class Result3Ds Result3Ds;
#else
typedef struct Result3Ds Result3Ds;
#endif /* __cplusplus */

#endif 	/* __Result3Ds_FWD_DEFINED__ */


#ifndef __LoadGroupDeflectionResponse_FWD_DEFINED__
#define __LoadGroupDeflectionResponse_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadGroupDeflectionResponse LoadGroupDeflectionResponse;
#else
typedef struct LoadGroupDeflectionResponse LoadGroupDeflectionResponse;
#endif /* __cplusplus */

#endif 	/* __LoadGroupDeflectionResponse_FWD_DEFINED__ */


#ifndef __LoadGroupForceResponse_FWD_DEFINED__
#define __LoadGroupForceResponse_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadGroupForceResponse LoadGroupForceResponse;
#else
typedef struct LoadGroupForceResponse LoadGroupForceResponse;
#endif /* __cplusplus */

#endif 	/* __LoadGroupForceResponse_FWD_DEFINED__ */


#ifndef __InfluenceLine_FWD_DEFINED__
#define __InfluenceLine_FWD_DEFINED__

#ifdef __cplusplus
typedef class InfluenceLine InfluenceLine;
#else
typedef struct InfluenceLine InfluenceLine;
#endif /* __cplusplus */

#endif 	/* __InfluenceLine_FWD_DEFINED__ */


#ifndef __StressResult_FWD_DEFINED__
#define __StressResult_FWD_DEFINED__

#ifdef __cplusplus
typedef class StressResult StressResult;
#else
typedef struct StressResult StressResult;
#endif /* __cplusplus */

#endif 	/* __StressResult_FWD_DEFINED__ */


#ifndef __StressResults_FWD_DEFINED__
#define __StressResults_FWD_DEFINED__

#ifdef __cplusplus
typedef class StressResults StressResults;
#else
typedef struct StressResults StressResults;
#endif /* __cplusplus */

#endif 	/* __StressResults_FWD_DEFINED__ */


#ifndef __SectionStressResult_FWD_DEFINED__
#define __SectionStressResult_FWD_DEFINED__

#ifdef __cplusplus
typedef class SectionStressResult SectionStressResult;
#else
typedef struct SectionStressResult SectionStressResult;
#endif /* __cplusplus */

#endif 	/* __SectionStressResult_FWD_DEFINED__ */


#ifndef __SectionStressResults_FWD_DEFINED__
#define __SectionStressResults_FWD_DEFINED__

#ifdef __cplusplus
typedef class SectionStressResults SectionStressResults;
#else
typedef struct SectionStressResults SectionStressResults;
#endif /* __cplusplus */

#endif 	/* __SectionStressResults_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLLBAM.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLLBAMAnalysis_0000_0000 */
/* [local] */ 

#include "LBAMAnalysisErrors.h"


extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAMAnalysis_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAMAnalysis_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLLBAMAnalysis_LIBRARY_DEFINED__
#define __WBFLLBAMAnalysis_LIBRARY_DEFINED__

/* library WBFLLBAMAnalysis */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 

typedef /* [public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("4D9C6339-8154-4128-B92A-DA58D190196E") 
enum __MIDL___MIDL_itf_WBFLLBAMAnalysis_0000_0000_0001
    {
        atForce	= 0,
        atDeflection	= 1
    } 	AnalysisType;

typedef /* [public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("2E6C3B26-9740-11d5-B052-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLLBAMAnalysis_0000_0000_0002
    {
        roGlobal	= 0,
        roMember	= 1
    } 	ResultsOrientation;

typedef /* [public][public][public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("2EC2238D-A218-11d5-B05D-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLLBAMAnalysis_0000_0000_0003
    {
        rsCumulative	= 0,
        rsIncremental	= 1
    } 	ResultsSummationType;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("464E27B3-3BE0-437f-BB8B-43D8F8BD9CE7") 
enum __MIDL___MIDL_itf_WBFLLBAMAnalysis_0000_0000_0004
    {
        iflSingle	= 0,
        iflDualLeft	= 1,
        iflDualRight	= 2
    } 	InfluenceLocationType;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("BABE8D4A-689E-4a0f-9382-7D53E7F384C4") 
enum __MIDL___MIDL_itf_WBFLLBAMAnalysis_0000_0000_0005
    {
        fetFx	= 0,
        fetFy	= 1,
        fetMz	= 2,
        fetDx	= 0,
        fetDy	= 1,
        fetRz	= 2
    } 	ForceEffectType;

typedef /* [public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("EE6936C5-F7C8-46a9-849C-9143D694A5B5") 
enum __MIDL___MIDL_itf_WBFLLBAMAnalysis_0000_0000_0006
    {
        optMaximize	= 0,
        optMinimize	= 1
    } 	OptimizationType;

typedef /* [public][public][public][public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("CC040323-E031-437b-A3D7-501836996806") 
enum __MIDL___MIDL_itf_WBFLLBAMAnalysis_0000_0000_0007
    {
        ilsBoth	= 0,
        ilsPositive	= 1,
        ilsNegative	= 2
    } 	InfluenceSideType;


EXTERN_C const IID LIBID_WBFLLBAMAnalysis;

#ifndef __IAnalysisPOIs_INTERFACE_DEFINED__
#define __IAnalysisPOIs_INTERFACE_DEFINED__

/* interface IAnalysisPOIs */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAnalysisPOIs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("80A2C1BF-DA1D-482e-A138-8A92DFC3016E")
    IAnalysisPOIs : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SpanPoiIncrement( 
            /* [retval][out] */ PoiIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SpanPoiIncrement( 
            /* [in] */ PoiIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CantileverPoiIncrement( 
            /* [retval][out] */ PoiIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CantileverPoiIncrement( 
            /* [in] */ PoiIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSuperstructurePois( 
            /* [in] */ BSTR stage,
            /* [out] */ IIDArray **poiIDs,
            /* [out] */ IDblArray **poiLocations) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetPoiInfo( 
            /* [in] */ BSTR stage,
            /* [in] */ PoiIDType poiID,
            /* [out] */ MemberType *lbamMemberType,
            /* [out] */ MemberIDType *memberID,
            /* [out] */ Float64 *memberLocation) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAnalysisPOIsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAnalysisPOIs * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAnalysisPOIs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAnalysisPOIs * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpanPoiIncrement )( 
            IAnalysisPOIs * This,
            /* [retval][out] */ PoiIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SpanPoiIncrement )( 
            IAnalysisPOIs * This,
            /* [in] */ PoiIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CantileverPoiIncrement )( 
            IAnalysisPOIs * This,
            /* [retval][out] */ PoiIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CantileverPoiIncrement )( 
            IAnalysisPOIs * This,
            /* [in] */ PoiIDType newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSuperstructurePois )( 
            IAnalysisPOIs * This,
            /* [in] */ BSTR stage,
            /* [out] */ IIDArray **poiIDs,
            /* [out] */ IDblArray **poiLocations);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPoiInfo )( 
            IAnalysisPOIs * This,
            /* [in] */ BSTR stage,
            /* [in] */ PoiIDType poiID,
            /* [out] */ MemberType *lbamMemberType,
            /* [out] */ MemberIDType *memberID,
            /* [out] */ Float64 *memberLocation);
        
        END_INTERFACE
    } IAnalysisPOIsVtbl;

    interface IAnalysisPOIs
    {
        CONST_VTBL struct IAnalysisPOIsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnalysisPOIs_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAnalysisPOIs_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAnalysisPOIs_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAnalysisPOIs_get_SpanPoiIncrement(This,pVal)	\
    ( (This)->lpVtbl -> get_SpanPoiIncrement(This,pVal) ) 

#define IAnalysisPOIs_put_SpanPoiIncrement(This,newVal)	\
    ( (This)->lpVtbl -> put_SpanPoiIncrement(This,newVal) ) 

#define IAnalysisPOIs_get_CantileverPoiIncrement(This,pVal)	\
    ( (This)->lpVtbl -> get_CantileverPoiIncrement(This,pVal) ) 

#define IAnalysisPOIs_put_CantileverPoiIncrement(This,newVal)	\
    ( (This)->lpVtbl -> put_CantileverPoiIncrement(This,newVal) ) 

#define IAnalysisPOIs_GetSuperstructurePois(This,stage,poiIDs,poiLocations)	\
    ( (This)->lpVtbl -> GetSuperstructurePois(This,stage,poiIDs,poiLocations) ) 

#define IAnalysisPOIs_GetPoiInfo(This,stage,poiID,lbamMemberType,memberID,memberLocation)	\
    ( (This)->lpVtbl -> GetPoiInfo(This,stage,poiID,lbamMemberType,memberID,memberLocation) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAnalysisPOIs_INTERFACE_DEFINED__ */


#ifndef __ISectionResult3D_INTERFACE_DEFINED__
#define __ISectionResult3D_INTERFACE_DEFINED__

/* interface ISectionResult3D */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISectionResult3D;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("57CCF24A-970B-11D5-B052-00105A9AF985")
    ISectionResult3D : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XLeft( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_XLeft( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XRight( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_XRight( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_YLeft( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_YLeft( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_YRight( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_YRight( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ZLeft( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ZLeft( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ZRight( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ZRight( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetResult( 
            /* [in] */ Float64 XLeft,
            /* [in] */ Float64 YLeft,
            /* [in] */ Float64 ZLeft,
            /* [in] */ Float64 XRight,
            /* [in] */ Float64 YRight,
            /* [in] */ Float64 ZRight) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetResult( 
            /* [out] */ Float64 *XLeft,
            /* [out] */ Float64 *YLeft,
            /* [out] */ Float64 *ZLeft,
            /* [out] */ Float64 *XRight,
            /* [out] */ Float64 *YRight,
            /* [out] */ Float64 *ZRight) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISectionResult3D **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Sum( 
            /* [in] */ Float64 XLeft,
            /* [in] */ Float64 YLeft,
            /* [in] */ Float64 ZLeft,
            /* [in] */ Float64 XRight,
            /* [in] */ Float64 YRight,
            /* [in] */ Float64 ZRight) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FactorAndSum( 
            /* [in] */ ISectionResult3D *res,
            /* [in] */ Float64 leftFactor,
            /* [in] */ Float64 rightFactor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Zero( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSingleResult( 
            /* [in] */ ForceEffectType effect,
            /* [out] */ Float64 *leftVal,
            /* [out] */ Float64 *rightVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetSingleResult( 
            /* [in] */ ForceEffectType effect,
            /* [in] */ Float64 leftVal,
            /* [in] */ Float64 rightVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISectionResult3DVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISectionResult3D * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISectionResult3D * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISectionResult3D * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XLeft )( 
            ISectionResult3D * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_XLeft )( 
            ISectionResult3D * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XRight )( 
            ISectionResult3D * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_XRight )( 
            ISectionResult3D * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_YLeft )( 
            ISectionResult3D * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_YLeft )( 
            ISectionResult3D * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_YRight )( 
            ISectionResult3D * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_YRight )( 
            ISectionResult3D * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZLeft )( 
            ISectionResult3D * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ZLeft )( 
            ISectionResult3D * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZRight )( 
            ISectionResult3D * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ZRight )( 
            ISectionResult3D * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetResult )( 
            ISectionResult3D * This,
            /* [in] */ Float64 XLeft,
            /* [in] */ Float64 YLeft,
            /* [in] */ Float64 ZLeft,
            /* [in] */ Float64 XRight,
            /* [in] */ Float64 YRight,
            /* [in] */ Float64 ZRight);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            ISectionResult3D * This,
            /* [out] */ Float64 *XLeft,
            /* [out] */ Float64 *YLeft,
            /* [out] */ Float64 *ZLeft,
            /* [out] */ Float64 *XRight,
            /* [out] */ Float64 *YRight,
            /* [out] */ Float64 *ZRight);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISectionResult3D * This,
            /* [retval][out] */ ISectionResult3D **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Sum )( 
            ISectionResult3D * This,
            /* [in] */ Float64 XLeft,
            /* [in] */ Float64 YLeft,
            /* [in] */ Float64 ZLeft,
            /* [in] */ Float64 XRight,
            /* [in] */ Float64 YRight,
            /* [in] */ Float64 ZRight);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FactorAndSum )( 
            ISectionResult3D * This,
            /* [in] */ ISectionResult3D *res,
            /* [in] */ Float64 leftFactor,
            /* [in] */ Float64 rightFactor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Zero )( 
            ISectionResult3D * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSingleResult )( 
            ISectionResult3D * This,
            /* [in] */ ForceEffectType effect,
            /* [out] */ Float64 *leftVal,
            /* [out] */ Float64 *rightVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetSingleResult )( 
            ISectionResult3D * This,
            /* [in] */ ForceEffectType effect,
            /* [in] */ Float64 leftVal,
            /* [in] */ Float64 rightVal);
        
        END_INTERFACE
    } ISectionResult3DVtbl;

    interface ISectionResult3D
    {
        CONST_VTBL struct ISectionResult3DVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISectionResult3D_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISectionResult3D_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISectionResult3D_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISectionResult3D_get_XLeft(This,pVal)	\
    ( (This)->lpVtbl -> get_XLeft(This,pVal) ) 

#define ISectionResult3D_put_XLeft(This,newVal)	\
    ( (This)->lpVtbl -> put_XLeft(This,newVal) ) 

#define ISectionResult3D_get_XRight(This,pVal)	\
    ( (This)->lpVtbl -> get_XRight(This,pVal) ) 

#define ISectionResult3D_put_XRight(This,newVal)	\
    ( (This)->lpVtbl -> put_XRight(This,newVal) ) 

#define ISectionResult3D_get_YLeft(This,pVal)	\
    ( (This)->lpVtbl -> get_YLeft(This,pVal) ) 

#define ISectionResult3D_put_YLeft(This,newVal)	\
    ( (This)->lpVtbl -> put_YLeft(This,newVal) ) 

#define ISectionResult3D_get_YRight(This,pVal)	\
    ( (This)->lpVtbl -> get_YRight(This,pVal) ) 

#define ISectionResult3D_put_YRight(This,newVal)	\
    ( (This)->lpVtbl -> put_YRight(This,newVal) ) 

#define ISectionResult3D_get_ZLeft(This,pVal)	\
    ( (This)->lpVtbl -> get_ZLeft(This,pVal) ) 

#define ISectionResult3D_put_ZLeft(This,newVal)	\
    ( (This)->lpVtbl -> put_ZLeft(This,newVal) ) 

#define ISectionResult3D_get_ZRight(This,pVal)	\
    ( (This)->lpVtbl -> get_ZRight(This,pVal) ) 

#define ISectionResult3D_put_ZRight(This,newVal)	\
    ( (This)->lpVtbl -> put_ZRight(This,newVal) ) 

#define ISectionResult3D_SetResult(This,XLeft,YLeft,ZLeft,XRight,YRight,ZRight)	\
    ( (This)->lpVtbl -> SetResult(This,XLeft,YLeft,ZLeft,XRight,YRight,ZRight) ) 

#define ISectionResult3D_GetResult(This,XLeft,YLeft,ZLeft,XRight,YRight,ZRight)	\
    ( (This)->lpVtbl -> GetResult(This,XLeft,YLeft,ZLeft,XRight,YRight,ZRight) ) 

#define ISectionResult3D_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISectionResult3D_Sum(This,XLeft,YLeft,ZLeft,XRight,YRight,ZRight)	\
    ( (This)->lpVtbl -> Sum(This,XLeft,YLeft,ZLeft,XRight,YRight,ZRight) ) 

#define ISectionResult3D_FactorAndSum(This,res,leftFactor,rightFactor)	\
    ( (This)->lpVtbl -> FactorAndSum(This,res,leftFactor,rightFactor) ) 

#define ISectionResult3D_Zero(This)	\
    ( (This)->lpVtbl -> Zero(This) ) 

#define ISectionResult3D_GetSingleResult(This,effect,leftVal,rightVal)	\
    ( (This)->lpVtbl -> GetSingleResult(This,effect,leftVal,rightVal) ) 

#define ISectionResult3D_SetSingleResult(This,effect,leftVal,rightVal)	\
    ( (This)->lpVtbl -> SetSingleResult(This,effect,leftVal,rightVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISectionResult3D_INTERFACE_DEFINED__ */


#ifndef __IEnumSectionResult3D_INTERFACE_DEFINED__
#define __IEnumSectionResult3D_INTERFACE_DEFINED__

/* interface IEnumSectionResult3D */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSectionResult3D;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2E6C3B27-9740-11d5-B052-00105A9AF985")
    IEnumSectionResult3D : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSectionResult3D **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISectionResult3D **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSectionResult3DVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSectionResult3D * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSectionResult3D * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSectionResult3D * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSectionResult3D * This,
            /* [out] */ IEnumSectionResult3D **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSectionResult3D * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISectionResult3D **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSectionResult3D * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSectionResult3D * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSectionResult3DVtbl;

    interface IEnumSectionResult3D
    {
        CONST_VTBL struct IEnumSectionResult3DVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSectionResult3D_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSectionResult3D_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSectionResult3D_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSectionResult3D_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSectionResult3D_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSectionResult3D_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSectionResult3D_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSectionResult3D_INTERFACE_DEFINED__ */


#ifndef __ISectionResult3Ds_INTERFACE_DEFINED__
#define __ISectionResult3Ds_INTERFACE_DEFINED__

/* interface ISectionResult3Ds */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISectionResult3Ds;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("57CCF24E-970B-11D5-B052-00105A9AF985")
    ISectionResult3Ds : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISectionResult3D **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSectionResult3D **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ISectionResult3D *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ ISectionResult3D *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            ISectionResult3Ds **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reserve( 
            CollectionIndexType size) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISectionResult3DsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISectionResult3Ds * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISectionResult3Ds * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISectionResult3Ds * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISectionResult3Ds * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISectionResult3D **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISectionResult3Ds * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISectionResult3Ds * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ISectionResult3Ds * This,
            /* [retval][out] */ IEnumSectionResult3D **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISectionResult3Ds * This,
            /* [in] */ ISectionResult3D *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ISectionResult3Ds * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ ISectionResult3D *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ISectionResult3Ds * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISectionResult3Ds * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISectionResult3Ds * This,
            ISectionResult3Ds **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            ISectionResult3Ds * This,
            CollectionIndexType size);
        
        END_INTERFACE
    } ISectionResult3DsVtbl;

    interface ISectionResult3Ds
    {
        CONST_VTBL struct ISectionResult3DsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISectionResult3Ds_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISectionResult3Ds_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISectionResult3Ds_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISectionResult3Ds_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define ISectionResult3Ds_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ISectionResult3Ds_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISectionResult3Ds_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ISectionResult3Ds_Add(This,pVal)	\
    ( (This)->lpVtbl -> Add(This,pVal) ) 

#define ISectionResult3Ds_Insert(This,index,pVal)	\
    ( (This)->lpVtbl -> Insert(This,index,pVal) ) 

#define ISectionResult3Ds_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define ISectionResult3Ds_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ISectionResult3Ds_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISectionResult3Ds_Reserve(This,size)	\
    ( (This)->lpVtbl -> Reserve(This,size) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISectionResult3Ds_INTERFACE_DEFINED__ */


#ifndef __IResult3D_INTERFACE_DEFINED__
#define __IResult3D_INTERFACE_DEFINED__

/* interface IResult3D */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IResult3D;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("57CCF24C-970B-11D5-B052-00105A9AF985")
    IResult3D : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Z( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Z( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IResult3D **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Sum( 
            /* [in] */ Float64 X,
            /* [in] */ Float64 Y,
            /* [in] */ Float64 Z) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FactorAndSum( 
            /* [in] */ IResult3D *combinedRes,
            /* [in] */ Float64 Factor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Zero( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetResult( 
            /* [in] */ Float64 X,
            /* [in] */ Float64 Y,
            /* [in] */ Float64 Z) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetResult( 
            /* [out] */ Float64 *X,
            /* [out] */ Float64 *Y,
            /* [out] */ Float64 *Z) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSingleResult( 
            /* [in] */ ForceEffectType fet,
            /* [retval][out] */ Float64 *val) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetSingleResult( 
            /* [in] */ ForceEffectType fet,
            /* [in] */ Float64 val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IResult3DVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IResult3D * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IResult3D * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IResult3D * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IResult3D * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IResult3D * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IResult3D * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IResult3D * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Z )( 
            IResult3D * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Z )( 
            IResult3D * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IResult3D * This,
            /* [retval][out] */ IResult3D **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Sum )( 
            IResult3D * This,
            /* [in] */ Float64 X,
            /* [in] */ Float64 Y,
            /* [in] */ Float64 Z);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FactorAndSum )( 
            IResult3D * This,
            /* [in] */ IResult3D *combinedRes,
            /* [in] */ Float64 Factor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Zero )( 
            IResult3D * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetResult )( 
            IResult3D * This,
            /* [in] */ Float64 X,
            /* [in] */ Float64 Y,
            /* [in] */ Float64 Z);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            IResult3D * This,
            /* [out] */ Float64 *X,
            /* [out] */ Float64 *Y,
            /* [out] */ Float64 *Z);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSingleResult )( 
            IResult3D * This,
            /* [in] */ ForceEffectType fet,
            /* [retval][out] */ Float64 *val);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetSingleResult )( 
            IResult3D * This,
            /* [in] */ ForceEffectType fet,
            /* [in] */ Float64 val);
        
        END_INTERFACE
    } IResult3DVtbl;

    interface IResult3D
    {
        CONST_VTBL struct IResult3DVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResult3D_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IResult3D_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IResult3D_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IResult3D_get_X(This,pVal)	\
    ( (This)->lpVtbl -> get_X(This,pVal) ) 

#define IResult3D_put_X(This,newVal)	\
    ( (This)->lpVtbl -> put_X(This,newVal) ) 

#define IResult3D_get_Y(This,pVal)	\
    ( (This)->lpVtbl -> get_Y(This,pVal) ) 

#define IResult3D_put_Y(This,newVal)	\
    ( (This)->lpVtbl -> put_Y(This,newVal) ) 

#define IResult3D_get_Z(This,pVal)	\
    ( (This)->lpVtbl -> get_Z(This,pVal) ) 

#define IResult3D_put_Z(This,newVal)	\
    ( (This)->lpVtbl -> put_Z(This,newVal) ) 

#define IResult3D_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IResult3D_Sum(This,X,Y,Z)	\
    ( (This)->lpVtbl -> Sum(This,X,Y,Z) ) 

#define IResult3D_FactorAndSum(This,combinedRes,Factor)	\
    ( (This)->lpVtbl -> FactorAndSum(This,combinedRes,Factor) ) 

#define IResult3D_Zero(This)	\
    ( (This)->lpVtbl -> Zero(This) ) 

#define IResult3D_SetResult(This,X,Y,Z)	\
    ( (This)->lpVtbl -> SetResult(This,X,Y,Z) ) 

#define IResult3D_GetResult(This,X,Y,Z)	\
    ( (This)->lpVtbl -> GetResult(This,X,Y,Z) ) 

#define IResult3D_GetSingleResult(This,fet,val)	\
    ( (This)->lpVtbl -> GetSingleResult(This,fet,val) ) 

#define IResult3D_SetSingleResult(This,fet,val)	\
    ( (This)->lpVtbl -> SetSingleResult(This,fet,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IResult3D_INTERFACE_DEFINED__ */


#ifndef __IEnumResult3D_INTERFACE_DEFINED__
#define __IEnumResult3D_INTERFACE_DEFINED__

/* interface IEnumResult3D */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumResult3D;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7303806-EA7A-40dc-BF2F-50BFB6ACF749")
    IEnumResult3D : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumResult3D **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IResult3D **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumResult3DVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumResult3D * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumResult3D * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumResult3D * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumResult3D * This,
            /* [out] */ IEnumResult3D **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumResult3D * This,
            /* [in] */ ULONG celt,
            /* [out] */ IResult3D **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumResult3D * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumResult3D * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumResult3DVtbl;

    interface IEnumResult3D
    {
        CONST_VTBL struct IEnumResult3DVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumResult3D_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumResult3D_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumResult3D_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumResult3D_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumResult3D_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumResult3D_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumResult3D_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumResult3D_INTERFACE_DEFINED__ */


#ifndef __IResult3Ds_INTERFACE_DEFINED__
#define __IResult3Ds_INTERFACE_DEFINED__

/* interface IResult3Ds */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IResult3Ds;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("46ECFAEB-0BE5-47CA-B516-D6FD928ADDE9")
    IResult3Ds : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IResult3D **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumResult3D **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IResult3D *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ IResult3D *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            IResult3Ds **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reserve( 
            CollectionIndexType size) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IResult3DsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IResult3Ds * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IResult3Ds * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IResult3Ds * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IResult3Ds * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IResult3D **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IResult3Ds * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IResult3Ds * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IResult3Ds * This,
            /* [retval][out] */ IEnumResult3D **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IResult3Ds * This,
            /* [in] */ IResult3D *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IResult3Ds * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ IResult3D *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IResult3Ds * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IResult3Ds * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IResult3Ds * This,
            IResult3Ds **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            IResult3Ds * This,
            CollectionIndexType size);
        
        END_INTERFACE
    } IResult3DsVtbl;

    interface IResult3Ds
    {
        CONST_VTBL struct IResult3DsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResult3Ds_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IResult3Ds_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IResult3Ds_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IResult3Ds_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IResult3Ds_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IResult3Ds_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IResult3Ds_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IResult3Ds_Add(This,pVal)	\
    ( (This)->lpVtbl -> Add(This,pVal) ) 

#define IResult3Ds_Insert(This,index,pVal)	\
    ( (This)->lpVtbl -> Insert(This,index,pVal) ) 

#define IResult3Ds_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define IResult3Ds_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IResult3Ds_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IResult3Ds_Reserve(This,size)	\
    ( (This)->lpVtbl -> Reserve(This,size) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IResult3Ds_INTERFACE_DEFINED__ */


#ifndef __IStressResult_INTERFACE_DEFINED__
#define __IStressResult_INTERFACE_DEFINED__

/* interface IStressResult */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStressResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F362D7BF-0940-49A0-B19C-0ACA2437C03C")
    IStressResult : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddResult( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetResult( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetResult( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IStressResult **pClone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FactorAndSum( 
            /* [in] */ IStressResult *incRes,
            /* [in] */ Float64 factor) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStressResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStressResult * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStressResult * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStressResult * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IStressResult * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddResult )( 
            IStressResult * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetResult )( 
            IStressResult * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            IStressResult * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IStressResult * This,
            /* [retval][out] */ IStressResult **pClone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FactorAndSum )( 
            IStressResult * This,
            /* [in] */ IStressResult *incRes,
            /* [in] */ Float64 factor);
        
        END_INTERFACE
    } IStressResultVtbl;

    interface IStressResult
    {
        CONST_VTBL struct IStressResultVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStressResult_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStressResult_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStressResult_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStressResult_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IStressResult_AddResult(This,newVal)	\
    ( (This)->lpVtbl -> AddResult(This,newVal) ) 

#define IStressResult_SetResult(This,index,newVal)	\
    ( (This)->lpVtbl -> SetResult(This,index,newVal) ) 

#define IStressResult_GetResult(This,index,pVal)	\
    ( (This)->lpVtbl -> GetResult(This,index,pVal) ) 

#define IStressResult_Clone(This,pClone)	\
    ( (This)->lpVtbl -> Clone(This,pClone) ) 

#define IStressResult_FactorAndSum(This,incRes,factor)	\
    ( (This)->lpVtbl -> FactorAndSum(This,incRes,factor) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStressResult_INTERFACE_DEFINED__ */


#ifndef __IEnumStressResult_INTERFACE_DEFINED__
#define __IEnumStressResult_INTERFACE_DEFINED__

/* interface IEnumStressResult */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumStressResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4646A2AE-17EC-4c67-A2ED-DE65A226EECD")
    IEnumStressResult : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumStressResult **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IStressResult **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumStressResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumStressResult * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumStressResult * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumStressResult * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumStressResult * This,
            /* [out] */ IEnumStressResult **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumStressResult * This,
            /* [in] */ ULONG celt,
            /* [out] */ IStressResult **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumStressResult * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumStressResult * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumStressResultVtbl;

    interface IEnumStressResult
    {
        CONST_VTBL struct IEnumStressResultVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumStressResult_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumStressResult_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumStressResult_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumStressResult_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumStressResult_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumStressResult_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumStressResult_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumStressResult_INTERFACE_DEFINED__ */


#ifndef __IStressResults_INTERFACE_DEFINED__
#define __IStressResults_INTERFACE_DEFINED__

/* interface IStressResults */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStressResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1547A6FD-F035-494D-9709-0CBE39658B0B")
    IStressResults : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IStressResult **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumStressResult **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IStressResult *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ IStressResult *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            IStressResults **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reserve( 
            CollectionIndexType size) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStressResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStressResults * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStressResults * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStressResults * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IStressResults * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IStressResult **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IStressResults * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IStressResults * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IStressResults * This,
            /* [retval][out] */ IEnumStressResult **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IStressResults * This,
            /* [in] */ IStressResult *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IStressResults * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ IStressResult *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IStressResults * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IStressResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IStressResults * This,
            IStressResults **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            IStressResults * This,
            CollectionIndexType size);
        
        END_INTERFACE
    } IStressResultsVtbl;

    interface IStressResults
    {
        CONST_VTBL struct IStressResultsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStressResults_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStressResults_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStressResults_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStressResults_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IStressResults_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IStressResults_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IStressResults_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IStressResults_Add(This,pVal)	\
    ( (This)->lpVtbl -> Add(This,pVal) ) 

#define IStressResults_Insert(This,index,pVal)	\
    ( (This)->lpVtbl -> Insert(This,index,pVal) ) 

#define IStressResults_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define IStressResults_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IStressResults_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IStressResults_Reserve(This,size)	\
    ( (This)->lpVtbl -> Reserve(This,size) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStressResults_INTERFACE_DEFINED__ */


#ifndef __ISectionStressResult_INTERFACE_DEFINED__
#define __ISectionStressResult_INTERFACE_DEFINED__

/* interface ISectionStressResult */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISectionStressResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E4ED7062-B14A-4A44-BB90-CB64B6CE8571")
    ISectionStressResult : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddLeftResult( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetLeftResult( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLeftResult( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddRightResult( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetRightResult( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetRightResult( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISectionStressResult **pClone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FactorAndSum( 
            /* [in] */ ISectionStressResult *incRes,
            /* [in] */ Float64 leftFactor,
            /* [in] */ Float64 rightFactor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateLeftStressResult( 
            /* [retval][out] */ IStressResult **result) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateRightStressResult( 
            /* [retval][out] */ IStressResult **result) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISectionStressResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISectionStressResult * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISectionStressResult * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISectionStressResult * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftCount )( 
            ISectionStressResult * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddLeftResult )( 
            ISectionStressResult * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLeftResult )( 
            ISectionStressResult * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLeftResult )( 
            ISectionStressResult * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightCount )( 
            ISectionStressResult * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddRightResult )( 
            ISectionStressResult * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetRightResult )( 
            ISectionStressResult * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRightResult )( 
            ISectionStressResult * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISectionStressResult * This,
            /* [retval][out] */ ISectionStressResult **pClone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FactorAndSum )( 
            ISectionStressResult * This,
            /* [in] */ ISectionStressResult *incRes,
            /* [in] */ Float64 leftFactor,
            /* [in] */ Float64 rightFactor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateLeftStressResult )( 
            ISectionStressResult * This,
            /* [retval][out] */ IStressResult **result);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateRightStressResult )( 
            ISectionStressResult * This,
            /* [retval][out] */ IStressResult **result);
        
        END_INTERFACE
    } ISectionStressResultVtbl;

    interface ISectionStressResult
    {
        CONST_VTBL struct ISectionStressResultVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISectionStressResult_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISectionStressResult_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISectionStressResult_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISectionStressResult_get_LeftCount(This,pVal)	\
    ( (This)->lpVtbl -> get_LeftCount(This,pVal) ) 

#define ISectionStressResult_AddLeftResult(This,newVal)	\
    ( (This)->lpVtbl -> AddLeftResult(This,newVal) ) 

#define ISectionStressResult_SetLeftResult(This,index,newVal)	\
    ( (This)->lpVtbl -> SetLeftResult(This,index,newVal) ) 

#define ISectionStressResult_GetLeftResult(This,index,pVal)	\
    ( (This)->lpVtbl -> GetLeftResult(This,index,pVal) ) 

#define ISectionStressResult_get_RightCount(This,pVal)	\
    ( (This)->lpVtbl -> get_RightCount(This,pVal) ) 

#define ISectionStressResult_AddRightResult(This,newVal)	\
    ( (This)->lpVtbl -> AddRightResult(This,newVal) ) 

#define ISectionStressResult_SetRightResult(This,index,newVal)	\
    ( (This)->lpVtbl -> SetRightResult(This,index,newVal) ) 

#define ISectionStressResult_GetRightResult(This,index,pVal)	\
    ( (This)->lpVtbl -> GetRightResult(This,index,pVal) ) 

#define ISectionStressResult_Clone(This,pClone)	\
    ( (This)->lpVtbl -> Clone(This,pClone) ) 

#define ISectionStressResult_FactorAndSum(This,incRes,leftFactor,rightFactor)	\
    ( (This)->lpVtbl -> FactorAndSum(This,incRes,leftFactor,rightFactor) ) 

#define ISectionStressResult_CreateLeftStressResult(This,result)	\
    ( (This)->lpVtbl -> CreateLeftStressResult(This,result) ) 

#define ISectionStressResult_CreateRightStressResult(This,result)	\
    ( (This)->lpVtbl -> CreateRightStressResult(This,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISectionStressResult_INTERFACE_DEFINED__ */


#ifndef __IEnumSectionStressResult_INTERFACE_DEFINED__
#define __IEnumSectionStressResult_INTERFACE_DEFINED__

/* interface IEnumSectionStressResult */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSectionStressResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C16525E-3DAA-40dd-829F-BA5837234733")
    IEnumSectionStressResult : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSectionStressResult **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISectionStressResult **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSectionStressResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSectionStressResult * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSectionStressResult * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSectionStressResult * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSectionStressResult * This,
            /* [out] */ IEnumSectionStressResult **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSectionStressResult * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISectionStressResult **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSectionStressResult * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSectionStressResult * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSectionStressResultVtbl;

    interface IEnumSectionStressResult
    {
        CONST_VTBL struct IEnumSectionStressResultVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSectionStressResult_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSectionStressResult_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSectionStressResult_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSectionStressResult_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSectionStressResult_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSectionStressResult_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSectionStressResult_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSectionStressResult_INTERFACE_DEFINED__ */


#ifndef __ISectionStressResults_INTERFACE_DEFINED__
#define __ISectionStressResults_INTERFACE_DEFINED__

/* interface ISectionStressResults */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISectionStressResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("83096266-F98A-45AA-AF25-F1676057A360")
    ISectionStressResults : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISectionStressResult **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSectionStressResult **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ISectionStressResult *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ ISectionStressResult *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            ISectionStressResults **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reserve( 
            CollectionIndexType size) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISectionStressResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISectionStressResults * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISectionStressResults * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISectionStressResults * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISectionStressResults * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISectionStressResult **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISectionStressResults * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISectionStressResults * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ISectionStressResults * This,
            /* [retval][out] */ IEnumSectionStressResult **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISectionStressResults * This,
            /* [in] */ ISectionStressResult *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ISectionStressResults * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ ISectionStressResult *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ISectionStressResults * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISectionStressResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISectionStressResults * This,
            ISectionStressResults **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            ISectionStressResults * This,
            CollectionIndexType size);
        
        END_INTERFACE
    } ISectionStressResultsVtbl;

    interface ISectionStressResults
    {
        CONST_VTBL struct ISectionStressResultsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISectionStressResults_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISectionStressResults_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISectionStressResults_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISectionStressResults_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define ISectionStressResults_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ISectionStressResults_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISectionStressResults_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ISectionStressResults_Add(This,pVal)	\
    ( (This)->lpVtbl -> Add(This,pVal) ) 

#define ISectionStressResults_Insert(This,index,pVal)	\
    ( (This)->lpVtbl -> Insert(This,index,pVal) ) 

#define ISectionStressResults_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define ISectionStressResults_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ISectionStressResults_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISectionStressResults_Reserve(This,size)	\
    ( (This)->lpVtbl -> Reserve(This,size) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISectionStressResults_INTERFACE_DEFINED__ */


#ifndef __IDependOnLBAM_INTERFACE_DEFINED__
#define __IDependOnLBAM_INTERFACE_DEFINED__

/* interface IDependOnLBAM */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDependOnLBAM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("75D6F903-7594-4ba3-BEAD-423050E0F23A")
    IDependOnLBAM : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Model( 
            /* [retval][out] */ ILBAMModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Model( 
            /* [in] */ ILBAMModel *newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDependOnLBAMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDependOnLBAM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDependOnLBAM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDependOnLBAM * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Model )( 
            IDependOnLBAM * This,
            /* [retval][out] */ ILBAMModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Model )( 
            IDependOnLBAM * This,
            /* [in] */ ILBAMModel *newVal);
        
        END_INTERFACE
    } IDependOnLBAMVtbl;

    interface IDependOnLBAM
    {
        CONST_VTBL struct IDependOnLBAMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDependOnLBAM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDependOnLBAM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDependOnLBAM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDependOnLBAM_get_Model(This,pVal)	\
    ( (This)->lpVtbl -> get_Model(This,pVal) ) 

#define IDependOnLBAM_putref_Model(This,newVal)	\
    ( (This)->lpVtbl -> putref_Model(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDependOnLBAM_INTERFACE_DEFINED__ */


#ifndef __ILoadGroupResponse_INTERFACE_DEFINED__
#define __ILoadGroupResponse_INTERFACE_DEFINED__

/* interface ILoadGroupResponse */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadGroupResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ECEBE280-A182-11d5-B05C-00105A9AF985")
    ILoadGroupResponse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeForces( 
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeDeflections( 
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeReactions( 
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ IResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeSupportDeflections( 
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ IResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeStresses( 
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionStressResults **results) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadGroupResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadGroupResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadGroupResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadGroupResponse * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeForces )( 
            ILoadGroupResponse * This,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeDeflections )( 
            ILoadGroupResponse * This,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeReactions )( 
            ILoadGroupResponse * This,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ IResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeSupportDeflections )( 
            ILoadGroupResponse * This,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ IResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeStresses )( 
            ILoadGroupResponse * This,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionStressResults **results);
        
        END_INTERFACE
    } ILoadGroupResponseVtbl;

    interface ILoadGroupResponse
    {
        CONST_VTBL struct ILoadGroupResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadGroupResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadGroupResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadGroupResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadGroupResponse_ComputeForces(This,LoadGroup,poiIDs,Stage,orientation,summ,results)	\
    ( (This)->lpVtbl -> ComputeForces(This,LoadGroup,poiIDs,Stage,orientation,summ,results) ) 

#define ILoadGroupResponse_ComputeDeflections(This,LoadGroup,poiIDs,Stage,summ,results)	\
    ( (This)->lpVtbl -> ComputeDeflections(This,LoadGroup,poiIDs,Stage,summ,results) ) 

#define ILoadGroupResponse_ComputeReactions(This,LoadGroup,supportIDs,Stage,summ,results)	\
    ( (This)->lpVtbl -> ComputeReactions(This,LoadGroup,supportIDs,Stage,summ,results) ) 

#define ILoadGroupResponse_ComputeSupportDeflections(This,LoadGroup,supportIDs,Stage,summ,results)	\
    ( (This)->lpVtbl -> ComputeSupportDeflections(This,LoadGroup,supportIDs,Stage,summ,results) ) 

#define ILoadGroupResponse_ComputeStresses(This,LoadGroup,poiIDs,Stage,summ,results)	\
    ( (This)->lpVtbl -> ComputeStresses(This,LoadGroup,poiIDs,Stage,summ,results) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadGroupResponse_INTERFACE_DEFINED__ */


#ifndef __IDiagnostics_INTERFACE_DEFINED__
#define __IDiagnostics_INTERFACE_DEFINED__

/* interface IDiagnostics */
/* [uuid][object] */ 


EXTERN_C const IID IID_IDiagnostics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C72EEE97-B176-4275-A847-394A63B4A819")
    IDiagnostics : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DumpFEMModels( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDiagnosticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDiagnostics * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDiagnostics * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDiagnostics * This);
        
        HRESULT ( STDMETHODCALLTYPE *DumpFEMModels )( 
            IDiagnostics * This);
        
        END_INTERFACE
    } IDiagnosticsVtbl;

    interface IDiagnostics
    {
        CONST_VTBL struct IDiagnosticsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDiagnostics_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDiagnostics_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDiagnostics_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDiagnostics_DumpFEMModels(This)	\
    ( (This)->lpVtbl -> DumpFEMModels(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDiagnostics_INTERFACE_DEFINED__ */


#ifndef __IUnitLoadResponse_INTERFACE_DEFINED__
#define __IUnitLoadResponse_INTERFACE_DEFINED__

/* interface IUnitLoadResponse */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnitLoadResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7D6930D2-707E-49a2-9E77-7786C51E70FF")
    IUnitLoadResponse : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ComputeForces( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ PoiIDType ldPoiID,
            /* [in] */ BSTR bstrStage,
            /* [in] */ ForceEffectType forceEffectType,
            /* [in] */ ResultsOrientation orientation,
            /* [retval][out] */ ISectionResult3Ds **results) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitLoadResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitLoadResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitLoadResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitLoadResponse * This);
        
        HRESULT ( STDMETHODCALLTYPE *ComputeForces )( 
            IUnitLoadResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ PoiIDType ldPoiID,
            /* [in] */ BSTR bstrStage,
            /* [in] */ ForceEffectType forceEffectType,
            /* [in] */ ResultsOrientation orientation,
            /* [retval][out] */ ISectionResult3Ds **results);
        
        END_INTERFACE
    } IUnitLoadResponseVtbl;

    interface IUnitLoadResponse
    {
        CONST_VTBL struct IUnitLoadResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitLoadResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitLoadResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitLoadResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitLoadResponse_ComputeForces(This,poiIDs,ldPoiID,bstrStage,forceEffectType,orientation,results)	\
    ( (This)->lpVtbl -> ComputeForces(This,poiIDs,ldPoiID,bstrStage,forceEffectType,orientation,results) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitLoadResponse_INTERFACE_DEFINED__ */


#ifndef __IInfluenceLine_INTERFACE_DEFINED__
#define __IInfluenceLine_INTERFACE_DEFINED__

/* interface IInfluenceLine */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IInfluenceLine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("66BB77DB-C509-450F-B9ED-F3EA598E052B")
    IInfluenceLine : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ Float64 *location) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_POI( 
            /* [retval][out] */ PoiIDType *poi) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ InfluenceSideType side,
            /* [out] */ Float64 *value,
            /* [out] */ InfluenceLocationType *locationType,
            /* [out] */ Float64 *location) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [in] */ InfluenceSideType side,
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ InfluenceLocationType locationType,
            /* [in] */ Float64 location,
            /* [in] */ Float64 value) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IInfluenceLine **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Bounds( 
            /* [out] */ Float64 *start,
            Float64 *end) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Evaluate( 
            /* [in] */ Float64 location,
            /* [in] */ InfluenceSideType side,
            /* [out] */ VARIANT_BOOL *isDualValue,
            /* [out] */ Float64 *left_value,
            /* [out] */ Float64 *right_value) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeArea( 
            /* [in] */ InfluenceSideType side,
            /* [retval][out] */ Float64 *area) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeNonZeroRegions( 
            /* [in] */ InfluenceSideType side,
            /* [retval][out] */ IDblArray **locations) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeAreaInRegions( 
            /* [in] */ IDblArray *locations,
            /* [retval][out] */ Float64 *area) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IsZero( 
            /* [in] */ InfluenceSideType side,
            /* [retval][out] */ VARIANT_BOOL *isZero) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindMaxValue( 
            /* [in] */ Float64 start,
            /* [in] */ Float64 end,
            /* [out] */ Float64 *pLocation,
            /* [out] */ Float64 *pValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindMinValue( 
            /* [in] */ Float64 start,
            /* [in] */ Float64 end,
            /* [out] */ Float64 *pLocation,
            /* [out] */ Float64 *pValue) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IInfluenceLineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInfluenceLine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInfluenceLine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInfluenceLine * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IInfluenceLine * This,
            /* [retval][out] */ Float64 *location);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_POI )( 
            IInfluenceLine * This,
            /* [retval][out] */ PoiIDType *poi);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IInfluenceLine * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ InfluenceSideType side,
            /* [out] */ Float64 *value,
            /* [out] */ InfluenceLocationType *locationType,
            /* [out] */ Float64 *location);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IInfluenceLine * This,
            /* [in] */ InfluenceSideType side,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IInfluenceLine * This,
            /* [in] */ InfluenceLocationType locationType,
            /* [in] */ Float64 location,
            /* [in] */ Float64 value);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IInfluenceLine * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IInfluenceLine * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IInfluenceLine * This,
            /* [retval][out] */ IInfluenceLine **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Bounds )( 
            IInfluenceLine * This,
            /* [out] */ Float64 *start,
            Float64 *end);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Evaluate )( 
            IInfluenceLine * This,
            /* [in] */ Float64 location,
            /* [in] */ InfluenceSideType side,
            /* [out] */ VARIANT_BOOL *isDualValue,
            /* [out] */ Float64 *left_value,
            /* [out] */ Float64 *right_value);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeArea )( 
            IInfluenceLine * This,
            /* [in] */ InfluenceSideType side,
            /* [retval][out] */ Float64 *area);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeNonZeroRegions )( 
            IInfluenceLine * This,
            /* [in] */ InfluenceSideType side,
            /* [retval][out] */ IDblArray **locations);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeAreaInRegions )( 
            IInfluenceLine * This,
            /* [in] */ IDblArray *locations,
            /* [retval][out] */ Float64 *area);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsZero )( 
            IInfluenceLine * This,
            /* [in] */ InfluenceSideType side,
            /* [retval][out] */ VARIANT_BOOL *isZero);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindMaxValue )( 
            IInfluenceLine * This,
            /* [in] */ Float64 start,
            /* [in] */ Float64 end,
            /* [out] */ Float64 *pLocation,
            /* [out] */ Float64 *pValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindMinValue )( 
            IInfluenceLine * This,
            /* [in] */ Float64 start,
            /* [in] */ Float64 end,
            /* [out] */ Float64 *pLocation,
            /* [out] */ Float64 *pValue);
        
        END_INTERFACE
    } IInfluenceLineVtbl;

    interface IInfluenceLine
    {
        CONST_VTBL struct IInfluenceLineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInfluenceLine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInfluenceLine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInfluenceLine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInfluenceLine_get_Location(This,location)	\
    ( (This)->lpVtbl -> get_Location(This,location) ) 

#define IInfluenceLine_get_POI(This,poi)	\
    ( (This)->lpVtbl -> get_POI(This,poi) ) 

#define IInfluenceLine_Item(This,idx,side,value,locationType,location)	\
    ( (This)->lpVtbl -> Item(This,idx,side,value,locationType,location) ) 

#define IInfluenceLine_get_Count(This,side,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,side,pVal) ) 

#define IInfluenceLine_Add(This,locationType,location,value)	\
    ( (This)->lpVtbl -> Add(This,locationType,location,value) ) 

#define IInfluenceLine_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define IInfluenceLine_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IInfluenceLine_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IInfluenceLine_Bounds(This,start,end)	\
    ( (This)->lpVtbl -> Bounds(This,start,end) ) 

#define IInfluenceLine_Evaluate(This,location,side,isDualValue,left_value,right_value)	\
    ( (This)->lpVtbl -> Evaluate(This,location,side,isDualValue,left_value,right_value) ) 

#define IInfluenceLine_ComputeArea(This,side,area)	\
    ( (This)->lpVtbl -> ComputeArea(This,side,area) ) 

#define IInfluenceLine_ComputeNonZeroRegions(This,side,locations)	\
    ( (This)->lpVtbl -> ComputeNonZeroRegions(This,side,locations) ) 

#define IInfluenceLine_ComputeAreaInRegions(This,locations,area)	\
    ( (This)->lpVtbl -> ComputeAreaInRegions(This,locations,area) ) 

#define IInfluenceLine_IsZero(This,side,isZero)	\
    ( (This)->lpVtbl -> IsZero(This,side,isZero) ) 

#define IInfluenceLine_FindMaxValue(This,start,end,pLocation,pValue)	\
    ( (This)->lpVtbl -> FindMaxValue(This,start,end,pLocation,pValue) ) 

#define IInfluenceLine_FindMinValue(This,start,end,pLocation,pValue)	\
    ( (This)->lpVtbl -> FindMinValue(This,start,end,pLocation,pValue) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInfluenceLine_INTERFACE_DEFINED__ */


#ifndef __IInfluenceLineResponse_INTERFACE_DEFINED__
#define __IInfluenceLineResponse_INTERFACE_DEFINED__

/* interface IInfluenceLineResponse */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IInfluenceLineResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2F280ADF-C4CE-4012-B9E5-802ADECF3972")
    IInfluenceLineResponse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeForceInfluenceLine( 
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [in] */ ForceEffectType forceEffect,
            /* [in] */ ResultsOrientation orientation,
            /* [out] */ IInfluenceLine **leftInfl,
            /* [out] */ IInfluenceLine **rightInfl) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeDeflectionInfluenceLine( 
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [in] */ ForceEffectType deflectionEffect,
            /* [out] */ IInfluenceLine **leftInfl,
            /* [out] */ IInfluenceLine **rightInfl) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeReactionInfluenceLine( 
            /* [in] */ SupportIDType supportID,
            /* [in] */ BSTR stage,
            /* [in] */ ForceEffectType ReactionEffect,
            /* [retval][out] */ IInfluenceLine **newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeSupportDeflectionInfluenceLine( 
            /* [in] */ SupportIDType supportID,
            /* [in] */ BSTR stage,
            /* [in] */ ForceEffectType ReactionEffect,
            /* [retval][out] */ IInfluenceLine **newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetZeroTolerance( 
            /* [out] */ Float64 *forceTolerance,
            /* [out] */ Float64 *deflectionTolerance) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetZeroTolerance( 
            /* [in] */ Float64 forceTolerance,
            /* [in] */ Float64 deflectionTolerance) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IInfluenceLineResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInfluenceLineResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInfluenceLineResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInfluenceLineResponse * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeForceInfluenceLine )( 
            IInfluenceLineResponse * This,
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [in] */ ForceEffectType forceEffect,
            /* [in] */ ResultsOrientation orientation,
            /* [out] */ IInfluenceLine **leftInfl,
            /* [out] */ IInfluenceLine **rightInfl);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeDeflectionInfluenceLine )( 
            IInfluenceLineResponse * This,
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [in] */ ForceEffectType deflectionEffect,
            /* [out] */ IInfluenceLine **leftInfl,
            /* [out] */ IInfluenceLine **rightInfl);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeReactionInfluenceLine )( 
            IInfluenceLineResponse * This,
            /* [in] */ SupportIDType supportID,
            /* [in] */ BSTR stage,
            /* [in] */ ForceEffectType ReactionEffect,
            /* [retval][out] */ IInfluenceLine **newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeSupportDeflectionInfluenceLine )( 
            IInfluenceLineResponse * This,
            /* [in] */ SupportIDType supportID,
            /* [in] */ BSTR stage,
            /* [in] */ ForceEffectType ReactionEffect,
            /* [retval][out] */ IInfluenceLine **newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetZeroTolerance )( 
            IInfluenceLineResponse * This,
            /* [out] */ Float64 *forceTolerance,
            /* [out] */ Float64 *deflectionTolerance);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetZeroTolerance )( 
            IInfluenceLineResponse * This,
            /* [in] */ Float64 forceTolerance,
            /* [in] */ Float64 deflectionTolerance);
        
        END_INTERFACE
    } IInfluenceLineResponseVtbl;

    interface IInfluenceLineResponse
    {
        CONST_VTBL struct IInfluenceLineResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInfluenceLineResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInfluenceLineResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInfluenceLineResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInfluenceLineResponse_ComputeForceInfluenceLine(This,poiID,stage,forceEffect,orientation,leftInfl,rightInfl)	\
    ( (This)->lpVtbl -> ComputeForceInfluenceLine(This,poiID,stage,forceEffect,orientation,leftInfl,rightInfl) ) 

#define IInfluenceLineResponse_ComputeDeflectionInfluenceLine(This,poiID,stage,deflectionEffect,leftInfl,rightInfl)	\
    ( (This)->lpVtbl -> ComputeDeflectionInfluenceLine(This,poiID,stage,deflectionEffect,leftInfl,rightInfl) ) 

#define IInfluenceLineResponse_ComputeReactionInfluenceLine(This,supportID,stage,ReactionEffect,newVal)	\
    ( (This)->lpVtbl -> ComputeReactionInfluenceLine(This,supportID,stage,ReactionEffect,newVal) ) 

#define IInfluenceLineResponse_ComputeSupportDeflectionInfluenceLine(This,supportID,stage,ReactionEffect,newVal)	\
    ( (This)->lpVtbl -> ComputeSupportDeflectionInfluenceLine(This,supportID,stage,ReactionEffect,newVal) ) 

#define IInfluenceLineResponse_GetZeroTolerance(This,forceTolerance,deflectionTolerance)	\
    ( (This)->lpVtbl -> GetZeroTolerance(This,forceTolerance,deflectionTolerance) ) 

#define IInfluenceLineResponse_SetZeroTolerance(This,forceTolerance,deflectionTolerance)	\
    ( (This)->lpVtbl -> SetZeroTolerance(This,forceTolerance,deflectionTolerance) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInfluenceLineResponse_INTERFACE_DEFINED__ */


#ifndef __ILiveLoadNegativeMomentRegion_INTERFACE_DEFINED__
#define __ILiveLoadNegativeMomentRegion_INTERFACE_DEFINED__

/* interface ILiveLoadNegativeMomentRegion */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILiveLoadNegativeMomentRegion;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A2227E3-29F2-4b5d-B7A9-9105D5651619")
    ILiveLoadNegativeMomentRegion : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsPOIInNegativeLiveLoadMomentZone( 
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [retval][out] */ InZoneType *isInZone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeNegativeMomentRegions( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ IDblArray **locations) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadNegativeMomentRegionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoadNegativeMomentRegion * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoadNegativeMomentRegion * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoadNegativeMomentRegion * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsPOIInNegativeLiveLoadMomentZone )( 
            ILiveLoadNegativeMomentRegion * This,
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [retval][out] */ InZoneType *isInZone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeNegativeMomentRegions )( 
            ILiveLoadNegativeMomentRegion * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IDblArray **locations);
        
        END_INTERFACE
    } ILiveLoadNegativeMomentRegionVtbl;

    interface ILiveLoadNegativeMomentRegion
    {
        CONST_VTBL struct ILiveLoadNegativeMomentRegionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoadNegativeMomentRegion_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoadNegativeMomentRegion_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoadNegativeMomentRegion_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoadNegativeMomentRegion_get_IsPOIInNegativeLiveLoadMomentZone(This,poiID,stage,isInZone)	\
    ( (This)->lpVtbl -> get_IsPOIInNegativeLiveLoadMomentZone(This,poiID,stage,isInZone) ) 

#define ILiveLoadNegativeMomentRegion_ComputeNegativeMomentRegions(This,stage,locations)	\
    ( (This)->lpVtbl -> ComputeNegativeMomentRegions(This,stage,locations) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoadNegativeMomentRegion_INTERFACE_DEFINED__ */


#ifndef __IContraflexureResponse_INTERFACE_DEFINED__
#define __IContraflexureResponse_INTERFACE_DEFINED__

/* interface IContraflexureResponse */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IContraflexureResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FEC87963-9461-4125-9159-C8F12C90085D")
    IContraflexureResponse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeContraflexureLocations( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ IDblArray **locations) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeContraflexureResponse( 
            /* [in] */ BSTR stage,
            /* [in] */ ForceEffectType forceEffect,
            /* [retval][out] */ IInfluenceLine **results) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsPOIInContraflexureZone( 
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [retval][out] */ InZoneType *isInZone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IContraflexureResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IContraflexureResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IContraflexureResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IContraflexureResponse * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeContraflexureLocations )( 
            IContraflexureResponse * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IDblArray **locations);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeContraflexureResponse )( 
            IContraflexureResponse * This,
            /* [in] */ BSTR stage,
            /* [in] */ ForceEffectType forceEffect,
            /* [retval][out] */ IInfluenceLine **results);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsPOIInContraflexureZone )( 
            IContraflexureResponse * This,
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [retval][out] */ InZoneType *isInZone);
        
        END_INTERFACE
    } IContraflexureResponseVtbl;

    interface IContraflexureResponse
    {
        CONST_VTBL struct IContraflexureResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IContraflexureResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IContraflexureResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IContraflexureResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IContraflexureResponse_ComputeContraflexureLocations(This,stage,locations)	\
    ( (This)->lpVtbl -> ComputeContraflexureLocations(This,stage,locations) ) 

#define IContraflexureResponse_ComputeContraflexureResponse(This,stage,forceEffect,results)	\
    ( (This)->lpVtbl -> ComputeContraflexureResponse(This,stage,forceEffect,results) ) 

#define IContraflexureResponse_get_IsPOIInContraflexureZone(This,poiID,stage,isInZone)	\
    ( (This)->lpVtbl -> get_IsPOIInContraflexureZone(This,poiID,stage,isInZone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IContraflexureResponse_INTERFACE_DEFINED__ */


#ifndef __IGetFemForLoadGroupResponse_INTERFACE_DEFINED__
#define __IGetFemForLoadGroupResponse_INTERFACE_DEFINED__

/* interface IGetFemForLoadGroupResponse */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGetFemForLoadGroupResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A6A5408-B4FE-11d5-B070-00105A9AF985")
    IGetFemForLoadGroupResponse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SaveFem2D( 
            /* [in] */ BSTR Stage,
            /* [in] */ IStructuredSave2 *Save) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGetFemForLoadGroupResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetFemForLoadGroupResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetFemForLoadGroupResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetFemForLoadGroupResponse * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveFem2D )( 
            IGetFemForLoadGroupResponse * This,
            /* [in] */ BSTR Stage,
            /* [in] */ IStructuredSave2 *Save);
        
        END_INTERFACE
    } IGetFemForLoadGroupResponseVtbl;

    interface IGetFemForLoadGroupResponse
    {
        CONST_VTBL struct IGetFemForLoadGroupResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetFemForLoadGroupResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetFemForLoadGroupResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetFemForLoadGroupResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetFemForLoadGroupResponse_SaveFem2D(This,Stage,Save)	\
    ( (This)->lpVtbl -> SaveFem2D(This,Stage,Save) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetFemForLoadGroupResponse_INTERFACE_DEFINED__ */


#ifndef __IGetActiveLoadGroups_INTERFACE_DEFINED__
#define __IGetActiveLoadGroups_INTERFACE_DEFINED__

/* interface IGetActiveLoadGroups */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGetActiveLoadGroups;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7273349A-6D91-4a18-8226-8F2DED231B84")
    IGetActiveLoadGroups : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetActiveLoadGroups( 
            /* [retval][out] */ IBstrArray **loadGroups) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGetActiveLoadGroupsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetActiveLoadGroups * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetActiveLoadGroups * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetActiveLoadGroups * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetActiveLoadGroups )( 
            IGetActiveLoadGroups * This,
            /* [retval][out] */ IBstrArray **loadGroups);
        
        END_INTERFACE
    } IGetActiveLoadGroupsVtbl;

    interface IGetActiveLoadGroups
    {
        CONST_VTBL struct IGetActiveLoadGroupsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetActiveLoadGroups_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetActiveLoadGroups_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetActiveLoadGroups_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetActiveLoadGroups_GetActiveLoadGroups(This,loadGroups)	\
    ( (This)->lpVtbl -> GetActiveLoadGroups(This,loadGroups) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetActiveLoadGroups_INTERFACE_DEFINED__ */


#ifndef __IGetDistributionFactors_INTERFACE_DEFINED__
#define __IGetDistributionFactors_INTERFACE_DEFINED__

/* interface IGetDistributionFactors */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGetDistributionFactors;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9255C966-ED91-4449-80CC-9DC187DBAF3C")
    IGetDistributionFactors : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetPOIDistributionFactor( 
            /* [in] */ PoiIDType POI,
            /* [in] */ BSTR Stage,
            /* [out] */ IDistributionFactor **leftFactor,
            /* [out] */ IDistributionFactor **rightFactor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSupportDistributionFactor( 
            /* [in] */ SupportIDType supportID,
            /* [in] */ BSTR Stage,
            /* [retval][out] */ IDistributionFactor **Factor) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGetDistributionFactorsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetDistributionFactors * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetDistributionFactors * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetDistributionFactors * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPOIDistributionFactor )( 
            IGetDistributionFactors * This,
            /* [in] */ PoiIDType POI,
            /* [in] */ BSTR Stage,
            /* [out] */ IDistributionFactor **leftFactor,
            /* [out] */ IDistributionFactor **rightFactor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSupportDistributionFactor )( 
            IGetDistributionFactors * This,
            /* [in] */ SupportIDType supportID,
            /* [in] */ BSTR Stage,
            /* [retval][out] */ IDistributionFactor **Factor);
        
        END_INTERFACE
    } IGetDistributionFactorsVtbl;

    interface IGetDistributionFactors
    {
        CONST_VTBL struct IGetDistributionFactorsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetDistributionFactors_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetDistributionFactors_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetDistributionFactors_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetDistributionFactors_GetPOIDistributionFactor(This,POI,Stage,leftFactor,rightFactor)	\
    ( (This)->lpVtbl -> GetPOIDistributionFactor(This,POI,Stage,leftFactor,rightFactor) ) 

#define IGetDistributionFactors_GetSupportDistributionFactor(This,supportID,Stage,Factor)	\
    ( (This)->lpVtbl -> GetSupportDistributionFactor(This,supportID,Stage,Factor) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetDistributionFactors_INTERFACE_DEFINED__ */


#ifndef __IGetSegmentCrossSection_INTERFACE_DEFINED__
#define __IGetSegmentCrossSection_INTERFACE_DEFINED__

/* interface IGetSegmentCrossSection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGetSegmentCrossSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D999E50F-69F2-479b-9547-201F544EAA20")
    IGetSegmentCrossSection : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentCrossSectionAtPOI( 
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [out] */ ISegmentCrossSection **leftSegmentCrossSection,
            /* [out] */ ISegmentCrossSection **rightSegmentCrossSection) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGetSegmentCrossSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetSegmentCrossSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetSegmentCrossSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetSegmentCrossSection * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentCrossSectionAtPOI )( 
            IGetSegmentCrossSection * This,
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [out] */ ISegmentCrossSection **leftSegmentCrossSection,
            /* [out] */ ISegmentCrossSection **rightSegmentCrossSection);
        
        END_INTERFACE
    } IGetSegmentCrossSectionVtbl;

    interface IGetSegmentCrossSection
    {
        CONST_VTBL struct IGetSegmentCrossSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetSegmentCrossSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetSegmentCrossSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetSegmentCrossSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetSegmentCrossSection_GetSegmentCrossSectionAtPOI(This,poiID,stage,leftSegmentCrossSection,rightSegmentCrossSection)	\
    ( (This)->lpVtbl -> GetSegmentCrossSectionAtPOI(This,poiID,stage,leftSegmentCrossSection,rightSegmentCrossSection) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetSegmentCrossSection_INTERFACE_DEFINED__ */


#ifndef __IGetStressPoints_INTERFACE_DEFINED__
#define __IGetStressPoints_INTERFACE_DEFINED__

/* interface IGetStressPoints */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGetStressPoints;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D17AC799-78B0-4936-9948-C367CDAB8793")
    IGetStressPoints : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetStressPointsAtPOI( 
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [out] */ IStressPoints **leftStressPoints,
            /* [out] */ IStressPoints **rightStressPoints) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGetStressPointsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetStressPoints * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetStressPoints * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetStressPoints * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStressPointsAtPOI )( 
            IGetStressPoints * This,
            /* [in] */ PoiIDType poiID,
            /* [in] */ BSTR stage,
            /* [out] */ IStressPoints **leftStressPoints,
            /* [out] */ IStressPoints **rightStressPoints);
        
        END_INTERFACE
    } IGetStressPointsVtbl;

    interface IGetStressPoints
    {
        CONST_VTBL struct IGetStressPointsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetStressPoints_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetStressPoints_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetStressPoints_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetStressPoints_GetStressPointsAtPOI(This,poiID,stage,leftStressPoints,rightStressPoints)	\
    ( (This)->lpVtbl -> GetStressPointsAtPOI(This,poiID,stage,leftStressPoints,rightStressPoints) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetStressPoints_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SectionResult3D;

#ifdef __cplusplus

class DECLSPEC_UUID("57CCF24B-970B-11D5-B052-00105A9AF985")
SectionResult3D;
#endif

EXTERN_C const CLSID CLSID_Result3D;

#ifdef __cplusplus

class DECLSPEC_UUID("57CCF24D-970B-11D5-B052-00105A9AF985")
Result3D;
#endif

EXTERN_C const CLSID CLSID_SectionResult3Ds;

#ifdef __cplusplus

class DECLSPEC_UUID("57CCF24F-970B-11D5-B052-00105A9AF985")
SectionResult3Ds;
#endif

EXTERN_C const CLSID CLSID_Result3Ds;

#ifdef __cplusplus

class DECLSPEC_UUID("280ED0C7-4BA2-49D0-84A9-84E175844DDF")
Result3Ds;
#endif

EXTERN_C const CLSID CLSID_LoadGroupDeflectionResponse;

#ifdef __cplusplus

class DECLSPEC_UUID("A36770D3-0378-4240-B4F9-51CA31AF5603")
LoadGroupDeflectionResponse;
#endif

EXTERN_C const CLSID CLSID_LoadGroupForceResponse;

#ifdef __cplusplus

class DECLSPEC_UUID("BDADAB05-D5C5-4E82-8F06-92BB839502C7")
LoadGroupForceResponse;
#endif

EXTERN_C const CLSID CLSID_InfluenceLine;

#ifdef __cplusplus

class DECLSPEC_UUID("262B8AF3-4DA9-4639-8681-31A96233FAB5")
InfluenceLine;
#endif

EXTERN_C const CLSID CLSID_StressResult;

#ifdef __cplusplus

class DECLSPEC_UUID("836C5B66-4F11-4B61-8F8F-844BBA6F48B7")
StressResult;
#endif

EXTERN_C const CLSID CLSID_StressResults;

#ifdef __cplusplus

class DECLSPEC_UUID("7EFCAFCB-C862-47BB-8ADE-BA5AC43F8B5D")
StressResults;
#endif

EXTERN_C const CLSID CLSID_SectionStressResult;

#ifdef __cplusplus

class DECLSPEC_UUID("49EFC321-5773-42DB-91E7-9DD40D5095A1")
SectionStressResult;
#endif

EXTERN_C const CLSID CLSID_SectionStressResults;

#ifdef __cplusplus

class DECLSPEC_UUID("07E09A3B-C097-4A25-9E3F-A1D1340F0C5C")
SectionStressResults;
#endif
#endif /* __WBFLLBAMAnalysis_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


