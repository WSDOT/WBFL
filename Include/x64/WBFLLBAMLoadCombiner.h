

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:33:34 2017
 */
/* Compiler settings for ..\..\Include\WBFLLBAMLoadCombiner.idl:
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


#ifndef __WBFLLBAMLoadCombiner_h__
#define __WBFLLBAMLoadCombiner_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILoadCombinationAnalysisContext_FWD_DEFINED__
#define __ILoadCombinationAnalysisContext_FWD_DEFINED__
typedef interface ILoadCombinationAnalysisContext ILoadCombinationAnalysisContext;

#endif 	/* __ILoadCombinationAnalysisContext_FWD_DEFINED__ */


#ifndef __ILoadCombinationAnalysisContextEvents_FWD_DEFINED__
#define __ILoadCombinationAnalysisContextEvents_FWD_DEFINED__
typedef interface ILoadCombinationAnalysisContextEvents ILoadCombinationAnalysisContextEvents;

#endif 	/* __ILoadCombinationAnalysisContextEvents_FWD_DEFINED__ */


#ifndef __IGetCombinationFactors_FWD_DEFINED__
#define __IGetCombinationFactors_FWD_DEFINED__
typedef interface IGetCombinationFactors IGetCombinationFactors;

#endif 	/* __IGetCombinationFactors_FWD_DEFINED__ */


#ifndef __ILoadCaseResponse_FWD_DEFINED__
#define __ILoadCaseResponse_FWD_DEFINED__
typedef interface ILoadCaseResponse ILoadCaseResponse;

#endif 	/* __ILoadCaseResponse_FWD_DEFINED__ */


#ifndef __IDependOnLoadCombinationAnalysisContext_FWD_DEFINED__
#define __IDependOnLoadCombinationAnalysisContext_FWD_DEFINED__
typedef interface IDependOnLoadCombinationAnalysisContext IDependOnLoadCombinationAnalysisContext;

#endif 	/* __IDependOnLoadCombinationAnalysisContext_FWD_DEFINED__ */


#ifndef __ILoadCombinationResultConfiguration_FWD_DEFINED__
#define __ILoadCombinationResultConfiguration_FWD_DEFINED__
typedef interface ILoadCombinationResultConfiguration ILoadCombinationResultConfiguration;

#endif 	/* __ILoadCombinationResultConfiguration_FWD_DEFINED__ */


#ifndef __ILoadCombinationResults_FWD_DEFINED__
#define __ILoadCombinationResults_FWD_DEFINED__
typedef interface ILoadCombinationResults ILoadCombinationResults;

#endif 	/* __ILoadCombinationResults_FWD_DEFINED__ */


#ifndef __ILoadCombinationSectionResults_FWD_DEFINED__
#define __ILoadCombinationSectionResults_FWD_DEFINED__
typedef interface ILoadCombinationSectionResults ILoadCombinationSectionResults;

#endif 	/* __ILoadCombinationSectionResults_FWD_DEFINED__ */


#ifndef __ILoadCombinationStressResults_FWD_DEFINED__
#define __ILoadCombinationStressResults_FWD_DEFINED__
typedef interface ILoadCombinationStressResults ILoadCombinationStressResults;

#endif 	/* __ILoadCombinationStressResults_FWD_DEFINED__ */


#ifndef __ILoadCombinationResponse_FWD_DEFINED__
#define __ILoadCombinationResponse_FWD_DEFINED__
typedef interface ILoadCombinationResponse ILoadCombinationResponse;

#endif 	/* __ILoadCombinationResponse_FWD_DEFINED__ */


#ifndef __IConcurrentLoadCombinationResponse_FWD_DEFINED__
#define __IConcurrentLoadCombinationResponse_FWD_DEFINED__
typedef interface IConcurrentLoadCombinationResponse IConcurrentLoadCombinationResponse;

#endif 	/* __IConcurrentLoadCombinationResponse_FWD_DEFINED__ */


#ifndef __IGetActiveLoadCases_FWD_DEFINED__
#define __IGetActiveLoadCases_FWD_DEFINED__
typedef interface IGetActiveLoadCases IGetActiveLoadCases;

#endif 	/* __IGetActiveLoadCases_FWD_DEFINED__ */


#ifndef __LoadCombinationAnalysisContext_FWD_DEFINED__
#define __LoadCombinationAnalysisContext_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadCombinationAnalysisContext LoadCombinationAnalysisContext;
#else
typedef struct LoadCombinationAnalysisContext LoadCombinationAnalysisContext;
#endif /* __cplusplus */

#endif 	/* __LoadCombinationAnalysisContext_FWD_DEFINED__ */


#ifndef __LoadCombiner_FWD_DEFINED__
#define __LoadCombiner_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadCombiner LoadCombiner;
#else
typedef struct LoadCombiner LoadCombiner;
#endif /* __cplusplus */

#endif 	/* __LoadCombiner_FWD_DEFINED__ */


#ifndef __LoadCombinationSectionResults_FWD_DEFINED__
#define __LoadCombinationSectionResults_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadCombinationSectionResults LoadCombinationSectionResults;
#else
typedef struct LoadCombinationSectionResults LoadCombinationSectionResults;
#endif /* __cplusplus */

#endif 	/* __LoadCombinationSectionResults_FWD_DEFINED__ */


#ifndef __LoadCombinationResultConfiguration_FWD_DEFINED__
#define __LoadCombinationResultConfiguration_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadCombinationResultConfiguration LoadCombinationResultConfiguration;
#else
typedef struct LoadCombinationResultConfiguration LoadCombinationResultConfiguration;
#endif /* __cplusplus */

#endif 	/* __LoadCombinationResultConfiguration_FWD_DEFINED__ */


#ifndef __LoadCombinationResults_FWD_DEFINED__
#define __LoadCombinationResults_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadCombinationResults LoadCombinationResults;
#else
typedef struct LoadCombinationResults LoadCombinationResults;
#endif /* __cplusplus */

#endif 	/* __LoadCombinationResults_FWD_DEFINED__ */


#ifndef __LoadCombinationStressResults_FWD_DEFINED__
#define __LoadCombinationStressResults_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadCombinationStressResults LoadCombinationStressResults;
#else
typedef struct LoadCombinationStressResults LoadCombinationStressResults;
#endif /* __cplusplus */

#endif 	/* __LoadCombinationStressResults_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"
#include "WBFLLBAM.h"
#include "WBFLLBAMAnalysis.h"
#include "WBFLLBAMLiveLoader.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLLBAMLoadCombiner_0000_0000 */
/* [local] */ 

#include "LBAMLoadCombinerErrors.h"


extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAMLoadCombiner_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAMLoadCombiner_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLLBAMLoadCombiner_LIBRARY_DEFINED__
#define __WBFLLBAMLoadCombiner_LIBRARY_DEFINED__

/* library WBFLLBAMLoadCombiner */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 

typedef /* [public][helpstring][uuid][public] */  DECLSPEC_UUID("959322BB-58AE-4c8f-B5DB-0603DA5E9AD1") 
enum __MIDL___MIDL_itf_WBFLLBAMLoadCombiner_0000_0000_0001
    {
        cctILoadCombinationAnalysisContextChanged	= 80001,
        cctResultsChanged	= 80002,
        cctCombinationChanged	= 80003
    } 	LBAMLCChangeTargetType;

typedef /* [public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("6EE31018-31E8-4dff-90A7-A9DA4A0BAE87") 
enum __MIDL___MIDL_itf_WBFLLBAMLoadCombiner_0000_0000_0002
    {
        ctLoadCase	= 1,
        ctLoadCombination	= 2
    } 	ComboType;



EXTERN_C const IID LIBID_WBFLLBAMLoadCombiner;

#ifndef __ILoadCombinationAnalysisContext_INTERFACE_DEFINED__
#define __ILoadCombinationAnalysisContext_INTERFACE_DEFINED__

/* interface ILoadCombinationAnalysisContext */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCombinationAnalysisContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("27090848-5158-4AB7-AFCD-7B1DAD2F1C17")
    ILoadCombinationAnalysisContext : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ ILBAMModel *model,
            /* [in] */ ILoadGroupResponse *loadGroupResponse,
            /* [in] */ ILiveLoadModelResponse *liveLoadModelResponse,
            /* [in] */ IBasicVehicularResponse *bvResponse,
            /* [in] */ IAnalysisPOIs *analysisPOIs,
            /* [in] */ IGetStressPoints *GetStressPoints) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationAnalysisContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombinationAnalysisContext * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombinationAnalysisContext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombinationAnalysisContext * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ILoadCombinationAnalysisContext * This,
            /* [in] */ ILBAMModel *model,
            /* [in] */ ILoadGroupResponse *loadGroupResponse,
            /* [in] */ ILiveLoadModelResponse *liveLoadModelResponse,
            /* [in] */ IBasicVehicularResponse *bvResponse,
            /* [in] */ IAnalysisPOIs *analysisPOIs,
            /* [in] */ IGetStressPoints *GetStressPoints);
        
        END_INTERFACE
    } ILoadCombinationAnalysisContextVtbl;

    interface ILoadCombinationAnalysisContext
    {
        CONST_VTBL struct ILoadCombinationAnalysisContextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombinationAnalysisContext_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombinationAnalysisContext_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombinationAnalysisContext_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombinationAnalysisContext_Initialize(This,model,loadGroupResponse,liveLoadModelResponse,bvResponse,analysisPOIs,GetStressPoints)	\
    ( (This)->lpVtbl -> Initialize(This,model,loadGroupResponse,liveLoadModelResponse,bvResponse,analysisPOIs,GetStressPoints) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombinationAnalysisContext_INTERFACE_DEFINED__ */


#ifndef __ILoadCombinationAnalysisContextEvents_INTERFACE_DEFINED__
#define __ILoadCombinationAnalysisContextEvents_INTERFACE_DEFINED__

/* interface ILoadCombinationAnalysisContextEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILoadCombinationAnalysisContextEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4B0AB00-60BB-49d2-8A47-2151E912C3DE")
    ILoadCombinationAnalysisContextEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnCombinationChanged( 
            /* [in] */ ComboType ctype,
            /* [in] */ BSTR combination) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnResultsChanged( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationAnalysisContextEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombinationAnalysisContextEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombinationAnalysisContextEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombinationAnalysisContextEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnCombinationChanged )( 
            ILoadCombinationAnalysisContextEvents * This,
            /* [in] */ ComboType ctype,
            /* [in] */ BSTR combination);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnResultsChanged )( 
            ILoadCombinationAnalysisContextEvents * This);
        
        END_INTERFACE
    } ILoadCombinationAnalysisContextEventsVtbl;

    interface ILoadCombinationAnalysisContextEvents
    {
        CONST_VTBL struct ILoadCombinationAnalysisContextEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombinationAnalysisContextEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombinationAnalysisContextEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombinationAnalysisContextEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombinationAnalysisContextEvents_OnCombinationChanged(This,ctype,combination)	\
    ( (This)->lpVtbl -> OnCombinationChanged(This,ctype,combination) ) 

#define ILoadCombinationAnalysisContextEvents_OnResultsChanged(This)	\
    ( (This)->lpVtbl -> OnResultsChanged(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombinationAnalysisContextEvents_INTERFACE_DEFINED__ */


#ifndef __IGetCombinationFactors_INTERFACE_DEFINED__
#define __IGetCombinationFactors_INTERFACE_DEFINED__

/* interface IGetCombinationFactors */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGetCombinationFactors;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E8DCEFD6-1756-45a1-9E3E-79C9EDADA403")
    IGetCombinationFactors : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetPOICombinationFactors( 
            /* [in] */ PoiIDType POI,
            /* [in] */ BSTR Stage,
            /* [in] */ LoadCombinationType type,
            /* [out] */ Float64 *minLoadModifier,
            /* [out] */ Float64 *maxLoadModifier) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSupportCombinationFactors( 
            /* [in] */ SupportIDType supportID,
            /* [in] */ BSTR Stage,
            /* [in] */ LoadCombinationType type,
            /* [out] */ Float64 *minLoadModifier,
            /* [out] */ Float64 *maxLoadModifier) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGetCombinationFactorsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetCombinationFactors * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetCombinationFactors * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetCombinationFactors * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPOICombinationFactors )( 
            IGetCombinationFactors * This,
            /* [in] */ PoiIDType POI,
            /* [in] */ BSTR Stage,
            /* [in] */ LoadCombinationType type,
            /* [out] */ Float64 *minLoadModifier,
            /* [out] */ Float64 *maxLoadModifier);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSupportCombinationFactors )( 
            IGetCombinationFactors * This,
            /* [in] */ SupportIDType supportID,
            /* [in] */ BSTR Stage,
            /* [in] */ LoadCombinationType type,
            /* [out] */ Float64 *minLoadModifier,
            /* [out] */ Float64 *maxLoadModifier);
        
        END_INTERFACE
    } IGetCombinationFactorsVtbl;

    interface IGetCombinationFactors
    {
        CONST_VTBL struct IGetCombinationFactorsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetCombinationFactors_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetCombinationFactors_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetCombinationFactors_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetCombinationFactors_GetPOICombinationFactors(This,POI,Stage,type,minLoadModifier,maxLoadModifier)	\
    ( (This)->lpVtbl -> GetPOICombinationFactors(This,POI,Stage,type,minLoadModifier,maxLoadModifier) ) 

#define IGetCombinationFactors_GetSupportCombinationFactors(This,supportID,Stage,type,minLoadModifier,maxLoadModifier)	\
    ( (This)->lpVtbl -> GetSupportCombinationFactors(This,supportID,Stage,type,minLoadModifier,maxLoadModifier) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetCombinationFactors_INTERFACE_DEFINED__ */


#ifndef __ILoadCaseResponse_INTERFACE_DEFINED__
#define __ILoadCaseResponse_INTERFACE_DEFINED__

/* interface ILoadCaseResponse */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCaseResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D30B0176-CB31-44B6-9296-F5957AF35297")
    ILoadCaseResponse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeForces( 
            /* [in] */ BSTR LoadCase,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeDeflections( 
            /* [in] */ BSTR LoadCase,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeReactions( 
            /* [in] */ BSTR LoadCase,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ IResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeSupportDeflections( 
            /* [in] */ BSTR LoadCase,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ IResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeStresses( 
            /* [in] */ BSTR LoadCase,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionStressResults **results) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCaseResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCaseResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCaseResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCaseResponse * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeForces )( 
            ILoadCaseResponse * This,
            /* [in] */ BSTR LoadCase,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeDeflections )( 
            ILoadCaseResponse * This,
            /* [in] */ BSTR LoadCase,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeReactions )( 
            ILoadCaseResponse * This,
            /* [in] */ BSTR LoadCase,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ IResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeSupportDeflections )( 
            ILoadCaseResponse * This,
            /* [in] */ BSTR LoadCase,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ IResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeStresses )( 
            ILoadCaseResponse * This,
            /* [in] */ BSTR LoadCase,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [retval][out] */ ISectionStressResults **results);
        
        END_INTERFACE
    } ILoadCaseResponseVtbl;

    interface ILoadCaseResponse
    {
        CONST_VTBL struct ILoadCaseResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCaseResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCaseResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCaseResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCaseResponse_ComputeForces(This,LoadCase,poiIDs,Stage,orientation,summ,results)	\
    ( (This)->lpVtbl -> ComputeForces(This,LoadCase,poiIDs,Stage,orientation,summ,results) ) 

#define ILoadCaseResponse_ComputeDeflections(This,LoadCase,poiIDs,Stage,summ,results)	\
    ( (This)->lpVtbl -> ComputeDeflections(This,LoadCase,poiIDs,Stage,summ,results) ) 

#define ILoadCaseResponse_ComputeReactions(This,LoadCase,supportIDs,Stage,summ,results)	\
    ( (This)->lpVtbl -> ComputeReactions(This,LoadCase,supportIDs,Stage,summ,results) ) 

#define ILoadCaseResponse_ComputeSupportDeflections(This,LoadCase,supportIDs,Stage,summ,results)	\
    ( (This)->lpVtbl -> ComputeSupportDeflections(This,LoadCase,supportIDs,Stage,summ,results) ) 

#define ILoadCaseResponse_ComputeStresses(This,LoadCase,poiIDs,Stage,summ,results)	\
    ( (This)->lpVtbl -> ComputeStresses(This,LoadCase,poiIDs,Stage,summ,results) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCaseResponse_INTERFACE_DEFINED__ */


#ifndef __IDependOnLoadCombinationAnalysisContext_INTERFACE_DEFINED__
#define __IDependOnLoadCombinationAnalysisContext_INTERFACE_DEFINED__

/* interface IDependOnLoadCombinationAnalysisContext */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDependOnLoadCombinationAnalysisContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B08D9240-43D0-4b71-9949-A06BB56B11DC")
    IDependOnLoadCombinationAnalysisContext : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IUnknown *context) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDependOnLoadCombinationAnalysisContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDependOnLoadCombinationAnalysisContext * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDependOnLoadCombinationAnalysisContext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDependOnLoadCombinationAnalysisContext * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IDependOnLoadCombinationAnalysisContext * This,
            /* [in] */ IUnknown *context);
        
        END_INTERFACE
    } IDependOnLoadCombinationAnalysisContextVtbl;

    interface IDependOnLoadCombinationAnalysisContext
    {
        CONST_VTBL struct IDependOnLoadCombinationAnalysisContextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDependOnLoadCombinationAnalysisContext_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDependOnLoadCombinationAnalysisContext_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDependOnLoadCombinationAnalysisContext_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDependOnLoadCombinationAnalysisContext_Initialize(This,context)	\
    ( (This)->lpVtbl -> Initialize(This,context) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDependOnLoadCombinationAnalysisContext_INTERFACE_DEFINED__ */


#ifndef __ILoadCombinationResultConfiguration_INTERFACE_DEFINED__
#define __ILoadCombinationResultConfiguration_INTERFACE_DEFINED__

/* interface ILoadCombinationResultConfiguration */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCombinationResultConfiguration;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("213F09DE-BB24-4A22-B8B3-7FD55651783E")
    ILoadCombinationResultConfiguration : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadCaseFactorCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLoadCaseFactor( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ BSTR *loadCase,
            /* [out] */ Float64 *factor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddLoadCaseFactor( 
            /* [in] */ BSTR loadCase,
            /* [in] */ Float64 factor) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LiveLoadFactor( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LiveLoadFactor( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddLiveLoadConfiguration( 
            /* [in] */ ILiveLoadConfiguration *Config) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLiveLoadConfiguration( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ILiveLoadConfiguration **Config) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLiveLoadConfigurationCount( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SummationType( 
            /* [retval][out] */ ResultsSummationType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SummationType( 
            /* [in] */ ResultsSummationType newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationResultConfigurationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombinationResultConfiguration * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombinationResultConfiguration * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombinationResultConfiguration * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCaseFactorCount )( 
            ILoadCombinationResultConfiguration * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLoadCaseFactor )( 
            ILoadCombinationResultConfiguration * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ BSTR *loadCase,
            /* [out] */ Float64 *factor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddLoadCaseFactor )( 
            ILoadCombinationResultConfiguration * This,
            /* [in] */ BSTR loadCase,
            /* [in] */ Float64 factor);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LiveLoadFactor )( 
            ILoadCombinationResultConfiguration * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LiveLoadFactor )( 
            ILoadCombinationResultConfiguration * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddLiveLoadConfiguration )( 
            ILoadCombinationResultConfiguration * This,
            /* [in] */ ILiveLoadConfiguration *Config);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLiveLoadConfiguration )( 
            ILoadCombinationResultConfiguration * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ILiveLoadConfiguration **Config);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLiveLoadConfigurationCount )( 
            ILoadCombinationResultConfiguration * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SummationType )( 
            ILoadCombinationResultConfiguration * This,
            /* [retval][out] */ ResultsSummationType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SummationType )( 
            ILoadCombinationResultConfiguration * This,
            /* [in] */ ResultsSummationType newVal);
        
        END_INTERFACE
    } ILoadCombinationResultConfigurationVtbl;

    interface ILoadCombinationResultConfiguration
    {
        CONST_VTBL struct ILoadCombinationResultConfigurationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombinationResultConfiguration_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombinationResultConfiguration_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombinationResultConfiguration_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombinationResultConfiguration_get_LoadCaseFactorCount(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadCaseFactorCount(This,pVal) ) 

#define ILoadCombinationResultConfiguration_GetLoadCaseFactor(This,index,loadCase,factor)	\
    ( (This)->lpVtbl -> GetLoadCaseFactor(This,index,loadCase,factor) ) 

#define ILoadCombinationResultConfiguration_AddLoadCaseFactor(This,loadCase,factor)	\
    ( (This)->lpVtbl -> AddLoadCaseFactor(This,loadCase,factor) ) 

#define ILoadCombinationResultConfiguration_get_LiveLoadFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_LiveLoadFactor(This,pVal) ) 

#define ILoadCombinationResultConfiguration_put_LiveLoadFactor(This,newVal)	\
    ( (This)->lpVtbl -> put_LiveLoadFactor(This,newVal) ) 

#define ILoadCombinationResultConfiguration_AddLiveLoadConfiguration(This,Config)	\
    ( (This)->lpVtbl -> AddLiveLoadConfiguration(This,Config) ) 

#define ILoadCombinationResultConfiguration_GetLiveLoadConfiguration(This,index,Config)	\
    ( (This)->lpVtbl -> GetLiveLoadConfiguration(This,index,Config) ) 

#define ILoadCombinationResultConfiguration_GetLiveLoadConfigurationCount(This,count)	\
    ( (This)->lpVtbl -> GetLiveLoadConfigurationCount(This,count) ) 

#define ILoadCombinationResultConfiguration_get_SummationType(This,pVal)	\
    ( (This)->lpVtbl -> get_SummationType(This,pVal) ) 

#define ILoadCombinationResultConfiguration_put_SummationType(This,newVal)	\
    ( (This)->lpVtbl -> put_SummationType(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombinationResultConfiguration_INTERFACE_DEFINED__ */


#ifndef __ILoadCombinationResults_INTERFACE_DEFINED__
#define __ILoadCombinationResults_INTERFACE_DEFINED__

/* interface ILoadCombinationResults */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCombinationResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5FD09BF8-C76C-4955-B7BA-58FFAC06A10C")
    ILoadCombinationResults : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ Float64 Result,
            /* [in] */ ILoadCombinationResultConfiguration *Config) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetResult( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 Result,
            /* [in] */ ILoadCombinationResultConfiguration *Config) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetResult( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *Result,
            /* [out] */ ILoadCombinationResultConfiguration **Config) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombinationResults * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombinationResults * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombinationResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILoadCombinationResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            ILoadCombinationResults * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILoadCombinationResults * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILoadCombinationResults * This,
            /* [in] */ Float64 Result,
            /* [in] */ ILoadCombinationResultConfiguration *Config);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetResult )( 
            ILoadCombinationResults * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 Result,
            /* [in] */ ILoadCombinationResultConfiguration *Config);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            ILoadCombinationResults * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *Result,
            /* [out] */ ILoadCombinationResultConfiguration **Config);
        
        END_INTERFACE
    } ILoadCombinationResultsVtbl;

    interface ILoadCombinationResults
    {
        CONST_VTBL struct ILoadCombinationResultsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombinationResults_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombinationResults_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombinationResults_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombinationResults_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILoadCombinationResults_Reserve(This,size)	\
    ( (This)->lpVtbl -> Reserve(This,size) ) 

#define ILoadCombinationResults_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILoadCombinationResults_Add(This,Result,Config)	\
    ( (This)->lpVtbl -> Add(This,Result,Config) ) 

#define ILoadCombinationResults_SetResult(This,index,Result,Config)	\
    ( (This)->lpVtbl -> SetResult(This,index,Result,Config) ) 

#define ILoadCombinationResults_GetResult(This,index,Result,Config)	\
    ( (This)->lpVtbl -> GetResult(This,index,Result,Config) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombinationResults_INTERFACE_DEFINED__ */


#ifndef __ILoadCombinationSectionResults_INTERFACE_DEFINED__
#define __ILoadCombinationSectionResults_INTERFACE_DEFINED__

/* interface ILoadCombinationSectionResults */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCombinationSectionResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("780AFAC0-F426-41F5-9632-0F46711CDCB6")
    ILoadCombinationSectionResults : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ Float64 leftResult,
            /* [in] */ ILoadCombinationResultConfiguration *leftConfig,
            /* [in] */ Float64 rightResult,
            /* [in] */ ILoadCombinationResultConfiguration *rightConfig) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetResult( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 leftResult,
            /* [in] */ ILoadCombinationResultConfiguration *leftConfig,
            /* [in] */ Float64 rightResult,
            /* [in] */ ILoadCombinationResultConfiguration *rightConfig) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetResult( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *leftResult,
            /* [out] */ ILoadCombinationResultConfiguration **leftConfig,
            /* [out] */ Float64 *rightResult,
            /* [out] */ ILoadCombinationResultConfiguration **rightConfig) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationSectionResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombinationSectionResults * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombinationSectionResults * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombinationSectionResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILoadCombinationSectionResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            ILoadCombinationSectionResults * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILoadCombinationSectionResults * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILoadCombinationSectionResults * This,
            /* [in] */ Float64 leftResult,
            /* [in] */ ILoadCombinationResultConfiguration *leftConfig,
            /* [in] */ Float64 rightResult,
            /* [in] */ ILoadCombinationResultConfiguration *rightConfig);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetResult )( 
            ILoadCombinationSectionResults * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 leftResult,
            /* [in] */ ILoadCombinationResultConfiguration *leftConfig,
            /* [in] */ Float64 rightResult,
            /* [in] */ ILoadCombinationResultConfiguration *rightConfig);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            ILoadCombinationSectionResults * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *leftResult,
            /* [out] */ ILoadCombinationResultConfiguration **leftConfig,
            /* [out] */ Float64 *rightResult,
            /* [out] */ ILoadCombinationResultConfiguration **rightConfig);
        
        END_INTERFACE
    } ILoadCombinationSectionResultsVtbl;

    interface ILoadCombinationSectionResults
    {
        CONST_VTBL struct ILoadCombinationSectionResultsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombinationSectionResults_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombinationSectionResults_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombinationSectionResults_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombinationSectionResults_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILoadCombinationSectionResults_Reserve(This,size)	\
    ( (This)->lpVtbl -> Reserve(This,size) ) 

#define ILoadCombinationSectionResults_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILoadCombinationSectionResults_Add(This,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> Add(This,leftResult,leftConfig,rightResult,rightConfig) ) 

#define ILoadCombinationSectionResults_SetResult(This,index,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> SetResult(This,index,leftResult,leftConfig,rightResult,rightConfig) ) 

#define ILoadCombinationSectionResults_GetResult(This,index,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> GetResult(This,index,leftResult,leftConfig,rightResult,rightConfig) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombinationSectionResults_INTERFACE_DEFINED__ */


#ifndef __ILoadCombinationStressResults_INTERFACE_DEFINED__
#define __ILoadCombinationStressResults_INTERFACE_DEFINED__

/* interface ILoadCombinationStressResults */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCombinationStressResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9F06ABE0-D32B-4394-90F4-BD73A172C59A")
    ILoadCombinationStressResults : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IStressResult *leftResult,
            /* [in] */ ILoadCombinationResultConfiguration *leftConfig,
            /* [in] */ IStressResult *rightResult,
            /* [in] */ ILoadCombinationResultConfiguration *rightConfig) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetResult( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ IStressResult *leftResult,
            /* [in] */ ILoadCombinationResultConfiguration *leftConfig,
            /* [in] */ IStressResult *rightResult,
            /* [in] */ ILoadCombinationResultConfiguration *rightConfig) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetResult( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ IStressResult **leftResult,
            /* [out] */ ILoadCombinationResultConfiguration **leftConfig,
            /* [out] */ IStressResult **rightResult,
            /* [out] */ ILoadCombinationResultConfiguration **rightConfig) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationStressResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombinationStressResults * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombinationStressResults * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombinationStressResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILoadCombinationStressResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            ILoadCombinationStressResults * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILoadCombinationStressResults * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILoadCombinationStressResults * This,
            /* [in] */ IStressResult *leftResult,
            /* [in] */ ILoadCombinationResultConfiguration *leftConfig,
            /* [in] */ IStressResult *rightResult,
            /* [in] */ ILoadCombinationResultConfiguration *rightConfig);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetResult )( 
            ILoadCombinationStressResults * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ IStressResult *leftResult,
            /* [in] */ ILoadCombinationResultConfiguration *leftConfig,
            /* [in] */ IStressResult *rightResult,
            /* [in] */ ILoadCombinationResultConfiguration *rightConfig);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            ILoadCombinationStressResults * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ IStressResult **leftResult,
            /* [out] */ ILoadCombinationResultConfiguration **leftConfig,
            /* [out] */ IStressResult **rightResult,
            /* [out] */ ILoadCombinationResultConfiguration **rightConfig);
        
        END_INTERFACE
    } ILoadCombinationStressResultsVtbl;

    interface ILoadCombinationStressResults
    {
        CONST_VTBL struct ILoadCombinationStressResultsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombinationStressResults_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombinationStressResults_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombinationStressResults_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombinationStressResults_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILoadCombinationStressResults_Reserve(This,size)	\
    ( (This)->lpVtbl -> Reserve(This,size) ) 

#define ILoadCombinationStressResults_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILoadCombinationStressResults_Add(This,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> Add(This,leftResult,leftConfig,rightResult,rightConfig) ) 

#define ILoadCombinationStressResults_SetResult(This,index,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> SetResult(This,index,leftResult,leftConfig,rightResult,rightConfig) ) 

#define ILoadCombinationStressResults_GetResult(This,index,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> GetResult(This,index,leftResult,leftConfig,rightResult,rightConfig) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombinationStressResults_INTERFACE_DEFINED__ */


#ifndef __ILoadCombinationResponse_INTERFACE_DEFINED__
#define __ILoadCombinationResponse_INTERFACE_DEFINED__

/* interface ILoadCombinationResponse */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCombinationResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6E738E23-95C4-48bf-9D00-1E2E5A8DF58E")
    ILoadCombinationResponse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeForces( 
            /* [in] */ BSTR LoadCombination,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ResultsSummationType summ,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VARIANT_BOOL includeLiveLoad,
            /* [in] */ VARIANT_BOOL includeImpact,
            /* [in] */ VARIANT_BOOL computeConfig,
            /* [retval][out] */ ILoadCombinationSectionResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeDeflections( 
            /* [in] */ BSTR LoadCombination,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VARIANT_BOOL includeLiveLoad,
            /* [in] */ VARIANT_BOOL includeImpact,
            /* [in] */ VARIANT_BOOL computeConfig,
            /* [retval][out] */ ILoadCombinationSectionResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeReactions( 
            /* [in] */ BSTR LoadCombination,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VARIANT_BOOL includeLiveLoad,
            /* [in] */ VARIANT_BOOL includeImpact,
            /* [in] */ VARIANT_BOOL computeConfig,
            /* [retval][out] */ ILoadCombinationResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeSupportDeflections( 
            /* [in] */ BSTR LoadCombination,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VARIANT_BOOL includeLiveLoad,
            /* [in] */ VARIANT_BOOL includeImpact,
            /* [in] */ VARIANT_BOOL computeConfig,
            /* [retval][out] */ ILoadCombinationResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeStresses( 
            /* [in] */ BSTR LoadCombination,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VARIANT_BOOL includeLiveLoad,
            /* [in] */ VARIANT_BOOL includeImpact,
            /* [in] */ VARIANT_BOOL computeConfig,
            /* [retval][out] */ ILoadCombinationStressResults **results) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombinationResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombinationResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombinationResponse * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeForces )( 
            ILoadCombinationResponse * This,
            /* [in] */ BSTR LoadCombination,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ResultsSummationType summ,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VARIANT_BOOL includeLiveLoad,
            /* [in] */ VARIANT_BOOL includeImpact,
            /* [in] */ VARIANT_BOOL computeConfig,
            /* [retval][out] */ ILoadCombinationSectionResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeDeflections )( 
            ILoadCombinationResponse * This,
            /* [in] */ BSTR LoadCombination,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VARIANT_BOOL includeLiveLoad,
            /* [in] */ VARIANT_BOOL includeImpact,
            /* [in] */ VARIANT_BOOL computeConfig,
            /* [retval][out] */ ILoadCombinationSectionResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeReactions )( 
            ILoadCombinationResponse * This,
            /* [in] */ BSTR LoadCombination,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VARIANT_BOOL includeLiveLoad,
            /* [in] */ VARIANT_BOOL includeImpact,
            /* [in] */ VARIANT_BOOL computeConfig,
            /* [retval][out] */ ILoadCombinationResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeSupportDeflections )( 
            ILoadCombinationResponse * This,
            /* [in] */ BSTR LoadCombination,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VARIANT_BOOL includeLiveLoad,
            /* [in] */ VARIANT_BOOL includeImpact,
            /* [in] */ VARIANT_BOOL computeConfig,
            /* [retval][out] */ ILoadCombinationResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeStresses )( 
            ILoadCombinationResponse * This,
            /* [in] */ BSTR LoadCombination,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR Stage,
            /* [in] */ ResultsSummationType summ,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VARIANT_BOOL includeLiveLoad,
            /* [in] */ VARIANT_BOOL includeImpact,
            /* [in] */ VARIANT_BOOL computeConfig,
            /* [retval][out] */ ILoadCombinationStressResults **results);
        
        END_INTERFACE
    } ILoadCombinationResponseVtbl;

    interface ILoadCombinationResponse
    {
        CONST_VTBL struct ILoadCombinationResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombinationResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombinationResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombinationResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombinationResponse_ComputeForces(This,LoadCombination,poiIDs,Stage,orientation,summ,effect,optimization,includeLiveLoad,includeImpact,computeConfig,results)	\
    ( (This)->lpVtbl -> ComputeForces(This,LoadCombination,poiIDs,Stage,orientation,summ,effect,optimization,includeLiveLoad,includeImpact,computeConfig,results) ) 

#define ILoadCombinationResponse_ComputeDeflections(This,LoadCombination,poiIDs,Stage,summ,effect,optimization,includeLiveLoad,includeImpact,computeConfig,results)	\
    ( (This)->lpVtbl -> ComputeDeflections(This,LoadCombination,poiIDs,Stage,summ,effect,optimization,includeLiveLoad,includeImpact,computeConfig,results) ) 

#define ILoadCombinationResponse_ComputeReactions(This,LoadCombination,supportIDs,Stage,summ,effect,optimization,includeLiveLoad,includeImpact,computeConfig,results)	\
    ( (This)->lpVtbl -> ComputeReactions(This,LoadCombination,supportIDs,Stage,summ,effect,optimization,includeLiveLoad,includeImpact,computeConfig,results) ) 

#define ILoadCombinationResponse_ComputeSupportDeflections(This,LoadCombination,supportIDs,Stage,summ,effect,optimization,includeLiveLoad,includeImpact,computeConfig,results)	\
    ( (This)->lpVtbl -> ComputeSupportDeflections(This,LoadCombination,supportIDs,Stage,summ,effect,optimization,includeLiveLoad,includeImpact,computeConfig,results) ) 

#define ILoadCombinationResponse_ComputeStresses(This,LoadCombination,poiIDs,Stage,summ,effect,optimization,includeLiveLoad,includeImpact,computeConfig,results)	\
    ( (This)->lpVtbl -> ComputeStresses(This,LoadCombination,poiIDs,Stage,summ,effect,optimization,includeLiveLoad,includeImpact,computeConfig,results) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombinationResponse_INTERFACE_DEFINED__ */


#ifndef __IConcurrentLoadCombinationResponse_INTERFACE_DEFINED__
#define __IConcurrentLoadCombinationResponse_INTERFACE_DEFINED__

/* interface IConcurrentLoadCombinationResponse */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IConcurrentLoadCombinationResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DCA0FA3E-E4BD-45CA-98D0-D18E7DD14080")
    IConcurrentLoadCombinationResponse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeForces( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ILoadCombinationResultConfiguration *config,
            /* [retval][out] */ ISectionResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeDeflections( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILoadCombinationResultConfiguration *config,
            /* [retval][out] */ ISectionResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeReactions( 
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILoadCombinationResultConfiguration *config,
            /* [retval][out] */ IResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeSupportDeflections( 
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILoadCombinationResultConfiguration *config,
            /* [retval][out] */ IResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeStresses( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILoadCombinationResultConfiguration *config,
            /* [retval][out] */ ISectionStressResults **results) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IConcurrentLoadCombinationResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConcurrentLoadCombinationResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConcurrentLoadCombinationResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConcurrentLoadCombinationResponse * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeForces )( 
            IConcurrentLoadCombinationResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ILoadCombinationResultConfiguration *config,
            /* [retval][out] */ ISectionResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeDeflections )( 
            IConcurrentLoadCombinationResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILoadCombinationResultConfiguration *config,
            /* [retval][out] */ ISectionResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeReactions )( 
            IConcurrentLoadCombinationResponse * This,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILoadCombinationResultConfiguration *config,
            /* [retval][out] */ IResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeSupportDeflections )( 
            IConcurrentLoadCombinationResponse * This,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILoadCombinationResultConfiguration *config,
            /* [retval][out] */ IResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeStresses )( 
            IConcurrentLoadCombinationResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILoadCombinationResultConfiguration *config,
            /* [retval][out] */ ISectionStressResults **results);
        
        END_INTERFACE
    } IConcurrentLoadCombinationResponseVtbl;

    interface IConcurrentLoadCombinationResponse
    {
        CONST_VTBL struct IConcurrentLoadCombinationResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConcurrentLoadCombinationResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IConcurrentLoadCombinationResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IConcurrentLoadCombinationResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IConcurrentLoadCombinationResponse_ComputeForces(This,poiIDs,stage,orientation,config,results)	\
    ( (This)->lpVtbl -> ComputeForces(This,poiIDs,stage,orientation,config,results) ) 

#define IConcurrentLoadCombinationResponse_ComputeDeflections(This,poiIDs,stage,config,results)	\
    ( (This)->lpVtbl -> ComputeDeflections(This,poiIDs,stage,config,results) ) 

#define IConcurrentLoadCombinationResponse_ComputeReactions(This,supportIDs,stage,config,results)	\
    ( (This)->lpVtbl -> ComputeReactions(This,supportIDs,stage,config,results) ) 

#define IConcurrentLoadCombinationResponse_ComputeSupportDeflections(This,supportIDs,stage,config,results)	\
    ( (This)->lpVtbl -> ComputeSupportDeflections(This,supportIDs,stage,config,results) ) 

#define IConcurrentLoadCombinationResponse_ComputeStresses(This,poiIDs,stage,config,results)	\
    ( (This)->lpVtbl -> ComputeStresses(This,poiIDs,stage,config,results) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IConcurrentLoadCombinationResponse_INTERFACE_DEFINED__ */


#ifndef __IGetActiveLoadCases_INTERFACE_DEFINED__
#define __IGetActiveLoadCases_INTERFACE_DEFINED__

/* interface IGetActiveLoadCases */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGetActiveLoadCases;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF00D72F-BEDA-4ea7-9801-AAAF72A7291F")
    IGetActiveLoadCases : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetActiveLoadCases( 
            /* [retval][out] */ IBstrArray **loadCases) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGetActiveLoadCasesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetActiveLoadCases * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetActiveLoadCases * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetActiveLoadCases * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetActiveLoadCases )( 
            IGetActiveLoadCases * This,
            /* [retval][out] */ IBstrArray **loadCases);
        
        END_INTERFACE
    } IGetActiveLoadCasesVtbl;

    interface IGetActiveLoadCases
    {
        CONST_VTBL struct IGetActiveLoadCasesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetActiveLoadCases_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetActiveLoadCases_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetActiveLoadCases_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetActiveLoadCases_GetActiveLoadCases(This,loadCases)	\
    ( (This)->lpVtbl -> GetActiveLoadCases(This,loadCases) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetActiveLoadCases_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LoadCombinationAnalysisContext;

#ifdef __cplusplus

class DECLSPEC_UUID("03CBD1B0-60CB-4779-9778-27A436C5E96B")
LoadCombinationAnalysisContext;
#endif

EXTERN_C const CLSID CLSID_LoadCombiner;

#ifdef __cplusplus

class DECLSPEC_UUID("B14CCE9F-891A-45C0-BA1C-CB1018CD57D6")
LoadCombiner;
#endif

EXTERN_C const CLSID CLSID_LoadCombinationSectionResults;

#ifdef __cplusplus

class DECLSPEC_UUID("F6D90F11-6091-4A73-8A51-56E948F7416C")
LoadCombinationSectionResults;
#endif

EXTERN_C const CLSID CLSID_LoadCombinationResultConfiguration;

#ifdef __cplusplus

class DECLSPEC_UUID("947CD836-CB00-470F-BC22-51E989BC2CE2")
LoadCombinationResultConfiguration;
#endif

EXTERN_C const CLSID CLSID_LoadCombinationResults;

#ifdef __cplusplus

class DECLSPEC_UUID("00F61030-02BB-4A53-9FF7-B8C27FFF1291")
LoadCombinationResults;
#endif

EXTERN_C const CLSID CLSID_LoadCombinationStressResults;

#ifdef __cplusplus

class DECLSPEC_UUID("EFE07497-0FC8-4404-9FCC-E7B449DA2696")
LoadCombinationStressResults;
#endif
#endif /* __WBFLLBAMLoadCombiner_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


