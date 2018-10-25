

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:41:31 2017
 */
/* Compiler settings for ..\..\Include\WBFLLBAMAnalysisUtility.idl:
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


#ifndef __WBFLLBAMAnalysisUtility_h__
#define __WBFLLBAMAnalysisUtility_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILBAMAnalysisEngine_FWD_DEFINED__
#define __ILBAMAnalysisEngine_FWD_DEFINED__
typedef interface ILBAMAnalysisEngine ILBAMAnalysisEngine;

#endif 	/* __ILBAMAnalysisEngine_FWD_DEFINED__ */


#ifndef __ISupportProgressMonitorForEngine_FWD_DEFINED__
#define __ISupportProgressMonitorForEngine_FWD_DEFINED__
typedef interface ISupportProgressMonitorForEngine ISupportProgressMonitorForEngine;

#endif 	/* __ISupportProgressMonitorForEngine_FWD_DEFINED__ */


#ifndef __ILBAMModelEnveloper_FWD_DEFINED__
#define __ILBAMModelEnveloper_FWD_DEFINED__
typedef interface ILBAMModelEnveloper ILBAMModelEnveloper;

#endif 	/* __ILBAMModelEnveloper_FWD_DEFINED__ */


#ifndef __LBAMAnalysisEngine_FWD_DEFINED__
#define __LBAMAnalysisEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class LBAMAnalysisEngine LBAMAnalysisEngine;
#else
typedef struct LBAMAnalysisEngine LBAMAnalysisEngine;
#endif /* __cplusplus */

#endif 	/* __LBAMAnalysisEngine_FWD_DEFINED__ */


#ifndef __LBAMModelEnveloper_FWD_DEFINED__
#define __LBAMModelEnveloper_FWD_DEFINED__

#ifdef __cplusplus
typedef class LBAMModelEnveloper LBAMModelEnveloper;
#else
typedef struct LBAMModelEnveloper LBAMModelEnveloper;
#endif /* __cplusplus */

#endif 	/* __LBAMModelEnveloper_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTools.h"
#include "WBFLLBAM.h"
#include "WBFLLBAMUtility.h"
#include "WBFLLBAMAnalysis.h"
#include "WBFLLBAMLoadCombiner.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLLBAMAnalysisUtility_0000_0000 */
/* [local] */ 

#define LBAMU_E_ENGINE_INIT_ONCE                      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1013)
#define LBAMU_E_INVALID_CONTEXT                       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1014)
#define LBAMU_E_ENGINE_INIT                           MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1015)
#define LBAMU_E_PROGRESS_INIT_SEQUENCE                MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1016)


extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAMAnalysisUtility_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAMAnalysisUtility_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLLBAMAnalysisUtility_LIBRARY_DEFINED__
#define __WBFLLBAMAnalysisUtility_LIBRARY_DEFINED__

/* library WBFLLBAMAnalysisUtility */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WBFLLBAMAnalysisUtility;

#ifndef __ILBAMAnalysisEngine_INTERFACE_DEFINED__
#define __ILBAMAnalysisEngine_INTERFACE_DEFINED__

/* interface ILBAMAnalysisEngine */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILBAMAnalysisEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A191EA1A-4FCA-470D-AF9A-242969F7F86F")
    ILBAMAnalysisEngine : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ ILBAMModel *model,
            /* [in] */ AnalysisType forceOrDeflection) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeEx( 
            /* [in] */ ILBAMModel *model,
            /* [in] */ AnalysisType forceOrDeflection,
            /* [in] */ ILoadGroupResponse *plgResponse,
            /* [in] */ IUnitLoadResponse *pUnitLoadResponse,
            /* [in] */ IInfluenceLineResponse *pilResponse,
            /* [in] */ IAnalysisPOIs *pPois,
            /* [in] */ IBasicVehicularResponse *pBVR,
            /* [in] */ ILiveLoadModelResponse *pLLMR,
            /* [in] */ IEnvelopedVehicularResponse *pEVR,
            /* [in] */ ILoadCaseResponse *plcResponse,
            /* [in] */ ILoadCombinationResponse *plcomboResponse,
            /* [in] */ IConcurrentLoadCombinationResponse *pclcResponse,
            /* [in] */ ILiveLoadNegativeMomentRegion *pllnmRegion,
            /* [in] */ IContraflexureResponse *pcontraResponse) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroupResponse( 
            /* [retval][out] */ ILoadGroupResponse **pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_UnitLoadResponse( 
            /* [retval][out] */ IUnitLoadResponse **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InfluenceLineResponse( 
            /* [retval][out] */ IInfluenceLineResponse **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AnalysisPOIs( 
            /* [retval][out] */ IAnalysisPOIs **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BasicVehicularResponse( 
            /* [retval][out] */ IBasicVehicularResponse **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LiveLoadModelResponse( 
            /* [retval][out] */ ILiveLoadModelResponse **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EnvelopedVehicularResponse( 
            /* [retval][out] */ IEnvelopedVehicularResponse **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadCaseResponse( 
            /* [retval][out] */ ILoadCaseResponse **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadCombinationResponse( 
            /* [retval][out] */ ILoadCombinationResponse **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ConcurrentLoadCombinationResponse( 
            /* [retval][out] */ IConcurrentLoadCombinationResponse **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Model( 
            /* [retval][out] */ ILBAMModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AnalysisType( 
            /* [retval][out] */ AnalysisType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LiveLoadNegativeMomentRegion( 
            /* [retval][out] */ ILiveLoadNegativeMomentRegion **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ContraflexureResponse( 
            /* [retval][out] */ IContraflexureResponse **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILBAMAnalysisEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILBAMAnalysisEngine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILBAMAnalysisEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILBAMAnalysisEngine * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ILBAMAnalysisEngine * This,
            /* [in] */ ILBAMModel *model,
            /* [in] */ AnalysisType forceOrDeflection);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeEx )( 
            ILBAMAnalysisEngine * This,
            /* [in] */ ILBAMModel *model,
            /* [in] */ AnalysisType forceOrDeflection,
            /* [in] */ ILoadGroupResponse *plgResponse,
            /* [in] */ IUnitLoadResponse *pUnitLoadResponse,
            /* [in] */ IInfluenceLineResponse *pilResponse,
            /* [in] */ IAnalysisPOIs *pPois,
            /* [in] */ IBasicVehicularResponse *pBVR,
            /* [in] */ ILiveLoadModelResponse *pLLMR,
            /* [in] */ IEnvelopedVehicularResponse *pEVR,
            /* [in] */ ILoadCaseResponse *plcResponse,
            /* [in] */ ILoadCombinationResponse *plcomboResponse,
            /* [in] */ IConcurrentLoadCombinationResponse *pclcResponse,
            /* [in] */ ILiveLoadNegativeMomentRegion *pllnmRegion,
            /* [in] */ IContraflexureResponse *pcontraResponse);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroupResponse )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ ILoadGroupResponse **pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitLoadResponse )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ IUnitLoadResponse **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InfluenceLineResponse )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ IInfluenceLineResponse **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AnalysisPOIs )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ IAnalysisPOIs **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BasicVehicularResponse )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ IBasicVehicularResponse **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LiveLoadModelResponse )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ ILiveLoadModelResponse **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnvelopedVehicularResponse )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ IEnvelopedVehicularResponse **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCaseResponse )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ ILoadCaseResponse **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCombinationResponse )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ ILoadCombinationResponse **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConcurrentLoadCombinationResponse )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ IConcurrentLoadCombinationResponse **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Model )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ ILBAMModel **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AnalysisType )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ AnalysisType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LiveLoadNegativeMomentRegion )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ ILiveLoadNegativeMomentRegion **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContraflexureResponse )( 
            ILBAMAnalysisEngine * This,
            /* [retval][out] */ IContraflexureResponse **pVal);
        
        END_INTERFACE
    } ILBAMAnalysisEngineVtbl;

    interface ILBAMAnalysisEngine
    {
        CONST_VTBL struct ILBAMAnalysisEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILBAMAnalysisEngine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILBAMAnalysisEngine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILBAMAnalysisEngine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILBAMAnalysisEngine_Initialize(This,model,forceOrDeflection)	\
    ( (This)->lpVtbl -> Initialize(This,model,forceOrDeflection) ) 

#define ILBAMAnalysisEngine_InitializeEx(This,model,forceOrDeflection,plgResponse,pUnitLoadResponse,pilResponse,pPois,pBVR,pLLMR,pEVR,plcResponse,plcomboResponse,pclcResponse,pllnmRegion,pcontraResponse)	\
    ( (This)->lpVtbl -> InitializeEx(This,model,forceOrDeflection,plgResponse,pUnitLoadResponse,pilResponse,pPois,pBVR,pLLMR,pEVR,plcResponse,plcomboResponse,pclcResponse,pllnmRegion,pcontraResponse) ) 

#define ILBAMAnalysisEngine_get_LoadGroupResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroupResponse(This,pVal) ) 

#define ILBAMAnalysisEngine_get_UnitLoadResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_UnitLoadResponse(This,pVal) ) 

#define ILBAMAnalysisEngine_get_InfluenceLineResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_InfluenceLineResponse(This,pVal) ) 

#define ILBAMAnalysisEngine_get_AnalysisPOIs(This,pVal)	\
    ( (This)->lpVtbl -> get_AnalysisPOIs(This,pVal) ) 

#define ILBAMAnalysisEngine_get_BasicVehicularResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_BasicVehicularResponse(This,pVal) ) 

#define ILBAMAnalysisEngine_get_LiveLoadModelResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_LiveLoadModelResponse(This,pVal) ) 

#define ILBAMAnalysisEngine_get_EnvelopedVehicularResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_EnvelopedVehicularResponse(This,pVal) ) 

#define ILBAMAnalysisEngine_get_LoadCaseResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadCaseResponse(This,pVal) ) 

#define ILBAMAnalysisEngine_get_LoadCombinationResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadCombinationResponse(This,pVal) ) 

#define ILBAMAnalysisEngine_get_ConcurrentLoadCombinationResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_ConcurrentLoadCombinationResponse(This,pVal) ) 

#define ILBAMAnalysisEngine_get_Model(This,pVal)	\
    ( (This)->lpVtbl -> get_Model(This,pVal) ) 

#define ILBAMAnalysisEngine_get_AnalysisType(This,pVal)	\
    ( (This)->lpVtbl -> get_AnalysisType(This,pVal) ) 

#define ILBAMAnalysisEngine_get_LiveLoadNegativeMomentRegion(This,pVal)	\
    ( (This)->lpVtbl -> get_LiveLoadNegativeMomentRegion(This,pVal) ) 

#define ILBAMAnalysisEngine_get_ContraflexureResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_ContraflexureResponse(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILBAMAnalysisEngine_INTERFACE_DEFINED__ */


#ifndef __ISupportProgressMonitorForEngine_INTERFACE_DEFINED__
#define __ISupportProgressMonitorForEngine_INTERFACE_DEFINED__

/* interface ISupportProgressMonitorForEngine */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISupportProgressMonitorForEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6857CDD0-169F-4ba3-A73C-51B491EB7273")
    ISupportProgressMonitorForEngine : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE InitializeProgressMonitor4E( 
            /* [in] */ IProgressMonitor *progMon,
            /* [in] */ LONG loadGroupCookie,
            /* [in] */ LONG liveLoadCookie,
            /* [in] */ LONG loadCombinationCookie) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportProgressMonitorForEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupportProgressMonitorForEngine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupportProgressMonitorForEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupportProgressMonitorForEngine * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitializeProgressMonitor4E )( 
            ISupportProgressMonitorForEngine * This,
            /* [in] */ IProgressMonitor *progMon,
            /* [in] */ LONG loadGroupCookie,
            /* [in] */ LONG liveLoadCookie,
            /* [in] */ LONG loadCombinationCookie);
        
        END_INTERFACE
    } ISupportProgressMonitorForEngineVtbl;

    interface ISupportProgressMonitorForEngine
    {
        CONST_VTBL struct ISupportProgressMonitorForEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupportProgressMonitorForEngine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupportProgressMonitorForEngine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupportProgressMonitorForEngine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupportProgressMonitorForEngine_InitializeProgressMonitor4E(This,progMon,loadGroupCookie,liveLoadCookie,loadCombinationCookie)	\
    ( (This)->lpVtbl -> InitializeProgressMonitor4E(This,progMon,loadGroupCookie,liveLoadCookie,loadCombinationCookie) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupportProgressMonitorForEngine_INTERFACE_DEFINED__ */


#ifndef __ILBAMModelEnveloper_INTERFACE_DEFINED__
#define __ILBAMModelEnveloper_INTERFACE_DEFINED__

/* interface ILBAMModelEnveloper */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILBAMModelEnveloper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E04FBF3C-C12C-43CE-9DFF-C592F1328AEA")
    ILBAMModelEnveloper : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Engines( 
            /* [retval][out] */ IUnkArray **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IUnkArray *newVal,
            /* [in] */ AnalysisType aType,
            /* [in] */ OptimizationType opType) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_AnalysisType( 
            /* [retval][out] */ AnalysisType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_OptimizationType( 
            /* [out] */ OptimizationType *opType) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_LoadCombinationResponse( 
            /* [retval][out] */ ILoadCombinationResponse **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_LiveLoadModelResponse( 
            /* [retval][out] */ ILiveLoadModelResponse **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_EnvelopedVehicularResponse( 
            /* [retval][out] */ IEnvelopedVehicularResponse **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE AddModel( 
            /* [in] */ ILBAMModel *pModel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddEngine( 
            /* [in] */ ILBAMAnalysisEngine *pEngine) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroupResponse( 
            /* [in] */ ForceEffectType forceEffect,
            /* [in] */ OptimizationType optimization,
            /* [retval][out] */ ILoadGroupResponse **pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LoadCaseResponse( 
            /* [in] */ ForceEffectType forceEffect,
            /* [in] */ OptimizationType optimization,
            /* [retval][out] */ ILoadCaseResponse **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILBAMModelEnveloperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILBAMModelEnveloper * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILBAMModelEnveloper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILBAMModelEnveloper * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Engines )( 
            ILBAMModelEnveloper * This,
            /* [retval][out] */ IUnkArray **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ILBAMModelEnveloper * This,
            /* [in] */ IUnkArray *newVal,
            /* [in] */ AnalysisType aType,
            /* [in] */ OptimizationType opType);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AnalysisType )( 
            ILBAMModelEnveloper * This,
            /* [retval][out] */ AnalysisType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OptimizationType )( 
            ILBAMModelEnveloper * This,
            /* [out] */ OptimizationType *opType);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCombinationResponse )( 
            ILBAMModelEnveloper * This,
            /* [retval][out] */ ILoadCombinationResponse **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LiveLoadModelResponse )( 
            ILBAMModelEnveloper * This,
            /* [retval][out] */ ILiveLoadModelResponse **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnvelopedVehicularResponse )( 
            ILBAMModelEnveloper * This,
            /* [retval][out] */ IEnvelopedVehicularResponse **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *AddModel )( 
            ILBAMModelEnveloper * This,
            /* [in] */ ILBAMModel *pModel);
        
        HRESULT ( STDMETHODCALLTYPE *AddEngine )( 
            ILBAMModelEnveloper * This,
            /* [in] */ ILBAMAnalysisEngine *pEngine);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroupResponse )( 
            ILBAMModelEnveloper * This,
            /* [in] */ ForceEffectType forceEffect,
            /* [in] */ OptimizationType optimization,
            /* [retval][out] */ ILoadGroupResponse **pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCaseResponse )( 
            ILBAMModelEnveloper * This,
            /* [in] */ ForceEffectType forceEffect,
            /* [in] */ OptimizationType optimization,
            /* [retval][out] */ ILoadCaseResponse **pVal);
        
        END_INTERFACE
    } ILBAMModelEnveloperVtbl;

    interface ILBAMModelEnveloper
    {
        CONST_VTBL struct ILBAMModelEnveloperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILBAMModelEnveloper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILBAMModelEnveloper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILBAMModelEnveloper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILBAMModelEnveloper_get_Engines(This,pVal)	\
    ( (This)->lpVtbl -> get_Engines(This,pVal) ) 

#define ILBAMModelEnveloper_Initialize(This,newVal,aType,opType)	\
    ( (This)->lpVtbl -> Initialize(This,newVal,aType,opType) ) 

#define ILBAMModelEnveloper_get_AnalysisType(This,pVal)	\
    ( (This)->lpVtbl -> get_AnalysisType(This,pVal) ) 

#define ILBAMModelEnveloper_get_OptimizationType(This,opType)	\
    ( (This)->lpVtbl -> get_OptimizationType(This,opType) ) 

#define ILBAMModelEnveloper_get_LoadCombinationResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadCombinationResponse(This,pVal) ) 

#define ILBAMModelEnveloper_get_LiveLoadModelResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_LiveLoadModelResponse(This,pVal) ) 

#define ILBAMModelEnveloper_get_EnvelopedVehicularResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_EnvelopedVehicularResponse(This,pVal) ) 

#define ILBAMModelEnveloper_AddModel(This,pModel)	\
    ( (This)->lpVtbl -> AddModel(This,pModel) ) 

#define ILBAMModelEnveloper_AddEngine(This,pEngine)	\
    ( (This)->lpVtbl -> AddEngine(This,pEngine) ) 

#define ILBAMModelEnveloper_get_LoadGroupResponse(This,forceEffect,optimization,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroupResponse(This,forceEffect,optimization,pVal) ) 

#define ILBAMModelEnveloper_get_LoadCaseResponse(This,forceEffect,optimization,pVal)	\
    ( (This)->lpVtbl -> get_LoadCaseResponse(This,forceEffect,optimization,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILBAMModelEnveloper_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LBAMAnalysisEngine;

#ifdef __cplusplus

class DECLSPEC_UUID("3D1EF310-E132-4DF4-85CC-3A7467F948E6")
LBAMAnalysisEngine;
#endif

EXTERN_C const CLSID CLSID_LBAMModelEnveloper;

#ifdef __cplusplus

class DECLSPEC_UUID("48715D04-3187-4ECD-A7B4-3AC4F3F58CA7")
LBAMModelEnveloper;
#endif
#endif /* __WBFLLBAMAnalysisUtility_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


