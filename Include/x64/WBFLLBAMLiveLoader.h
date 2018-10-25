

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:30:18 2017
 */
/* Compiler settings for ..\..\Include\WBFLLBAMLiveLoader.idl:
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


#ifndef __WBFLLBAMLiveLoader_h__
#define __WBFLLBAMLiveLoader_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IVehicularAnalysisContext_FWD_DEFINED__
#define __IVehicularAnalysisContext_FWD_DEFINED__
typedef interface IVehicularAnalysisContext IVehicularAnalysisContext;

#endif 	/* __IVehicularAnalysisContext_FWD_DEFINED__ */


#ifndef __IVehicularAnalysisContextEvents_FWD_DEFINED__
#define __IVehicularAnalysisContextEvents_FWD_DEFINED__
typedef interface IVehicularAnalysisContextEvents IVehicularAnalysisContextEvents;

#endif 	/* __IVehicularAnalysisContextEvents_FWD_DEFINED__ */


#ifndef __IDependOnVehicularAnalysisContext_FWD_DEFINED__
#define __IDependOnVehicularAnalysisContext_FWD_DEFINED__
typedef interface IDependOnVehicularAnalysisContext IDependOnVehicularAnalysisContext;

#endif 	/* __IDependOnVehicularAnalysisContext_FWD_DEFINED__ */


#ifndef __ISupportLocations_FWD_DEFINED__
#define __ISupportLocations_FWD_DEFINED__
typedef interface ISupportLocations ISupportLocations;

#endif 	/* __ISupportLocations_FWD_DEFINED__ */


#ifndef __ILiveLoadConfiguration_FWD_DEFINED__
#define __ILiveLoadConfiguration_FWD_DEFINED__
typedef interface ILiveLoadConfiguration ILiveLoadConfiguration;

#endif 	/* __ILiveLoadConfiguration_FWD_DEFINED__ */


#ifndef __ILiveLoadConfigurationEvents_FWD_DEFINED__
#define __ILiveLoadConfigurationEvents_FWD_DEFINED__
typedef interface ILiveLoadConfigurationEvents ILiveLoadConfigurationEvents;

#endif 	/* __ILiveLoadConfigurationEvents_FWD_DEFINED__ */


#ifndef __ILiveLoadModelSectionResults_FWD_DEFINED__
#define __ILiveLoadModelSectionResults_FWD_DEFINED__
typedef interface ILiveLoadModelSectionResults ILiveLoadModelSectionResults;

#endif 	/* __ILiveLoadModelSectionResults_FWD_DEFINED__ */


#ifndef __ILiveLoadModelResults_FWD_DEFINED__
#define __ILiveLoadModelResults_FWD_DEFINED__
typedef interface ILiveLoadModelResults ILiveLoadModelResults;

#endif 	/* __ILiveLoadModelResults_FWD_DEFINED__ */


#ifndef __ILiveLoadModelStressResults_FWD_DEFINED__
#define __ILiveLoadModelStressResults_FWD_DEFINED__
typedef interface ILiveLoadModelStressResults ILiveLoadModelStressResults;

#endif 	/* __ILiveLoadModelStressResults_FWD_DEFINED__ */


#ifndef __IEnvelopedVehicularResponse_FWD_DEFINED__
#define __IEnvelopedVehicularResponse_FWD_DEFINED__
typedef interface IEnvelopedVehicularResponse IEnvelopedVehicularResponse;

#endif 	/* __IEnvelopedVehicularResponse_FWD_DEFINED__ */


#ifndef __IBasicVehicularResponse_FWD_DEFINED__
#define __IBasicVehicularResponse_FWD_DEFINED__
typedef interface IBasicVehicularResponse IBasicVehicularResponse;

#endif 	/* __IBasicVehicularResponse_FWD_DEFINED__ */


#ifndef __IEnvelopedVehicularResponseFactory_FWD_DEFINED__
#define __IEnvelopedVehicularResponseFactory_FWD_DEFINED__
typedef interface IEnvelopedVehicularResponseFactory IEnvelopedVehicularResponseFactory;

#endif 	/* __IEnvelopedVehicularResponseFactory_FWD_DEFINED__ */


#ifndef __ISupportEnvelopedVehicularResponseFactory_FWD_DEFINED__
#define __ISupportEnvelopedVehicularResponseFactory_FWD_DEFINED__
typedef interface ISupportEnvelopedVehicularResponseFactory ISupportEnvelopedVehicularResponseFactory;

#endif 	/* __ISupportEnvelopedVehicularResponseFactory_FWD_DEFINED__ */


#ifndef __ILiveLoadModelResponse_FWD_DEFINED__
#define __ILiveLoadModelResponse_FWD_DEFINED__
typedef interface ILiveLoadModelResponse ILiveLoadModelResponse;

#endif 	/* __ILiveLoadModelResponse_FWD_DEFINED__ */


#ifndef __IEnvelopingStrategy_FWD_DEFINED__
#define __IEnvelopingStrategy_FWD_DEFINED__
typedef interface IEnvelopingStrategy IEnvelopingStrategy;

#endif 	/* __IEnvelopingStrategy_FWD_DEFINED__ */


#ifndef __VehicularAnalysisContext_FWD_DEFINED__
#define __VehicularAnalysisContext_FWD_DEFINED__

#ifdef __cplusplus
typedef class VehicularAnalysisContext VehicularAnalysisContext;
#else
typedef struct VehicularAnalysisContext VehicularAnalysisContext;
#endif /* __cplusplus */

#endif 	/* __VehicularAnalysisContext_FWD_DEFINED__ */


#ifndef __BasicVehicularResponse_FWD_DEFINED__
#define __BasicVehicularResponse_FWD_DEFINED__

#ifdef __cplusplus
typedef class BasicVehicularResponse BasicVehicularResponse;
#else
typedef struct BasicVehicularResponse BasicVehicularResponse;
#endif /* __cplusplus */

#endif 	/* __BasicVehicularResponse_FWD_DEFINED__ */


#ifndef __BruteForceVehicularResponse_FWD_DEFINED__
#define __BruteForceVehicularResponse_FWD_DEFINED__

#ifdef __cplusplus
typedef class BruteForceVehicularResponse BruteForceVehicularResponse;
#else
typedef struct BruteForceVehicularResponse BruteForceVehicularResponse;
#endif /* __cplusplus */

#endif 	/* __BruteForceVehicularResponse_FWD_DEFINED__ */


#ifndef __BruteForceVehicularResponse2_FWD_DEFINED__
#define __BruteForceVehicularResponse2_FWD_DEFINED__

#ifdef __cplusplus
typedef class BruteForceVehicularResponse2 BruteForceVehicularResponse2;
#else
typedef struct BruteForceVehicularResponse2 BruteForceVehicularResponse2;
#endif /* __cplusplus */

#endif 	/* __BruteForceVehicularResponse2_FWD_DEFINED__ */


#ifndef __LiveLoadConfiguration_FWD_DEFINED__
#define __LiveLoadConfiguration_FWD_DEFINED__

#ifdef __cplusplus
typedef class LiveLoadConfiguration LiveLoadConfiguration;
#else
typedef struct LiveLoadConfiguration LiveLoadConfiguration;
#endif /* __cplusplus */

#endif 	/* __LiveLoadConfiguration_FWD_DEFINED__ */


#ifndef __LiveLoadModelResponse_FWD_DEFINED__
#define __LiveLoadModelResponse_FWD_DEFINED__

#ifdef __cplusplus
typedef class LiveLoadModelResponse LiveLoadModelResponse;
#else
typedef struct LiveLoadModelResponse LiveLoadModelResponse;
#endif /* __cplusplus */

#endif 	/* __LiveLoadModelResponse_FWD_DEFINED__ */


#ifndef __LiveLoadModelSectionResults_FWD_DEFINED__
#define __LiveLoadModelSectionResults_FWD_DEFINED__

#ifdef __cplusplus
typedef class LiveLoadModelSectionResults LiveLoadModelSectionResults;
#else
typedef struct LiveLoadModelSectionResults LiveLoadModelSectionResults;
#endif /* __cplusplus */

#endif 	/* __LiveLoadModelSectionResults_FWD_DEFINED__ */


#ifndef __LiveLoadModelResults_FWD_DEFINED__
#define __LiveLoadModelResults_FWD_DEFINED__

#ifdef __cplusplus
typedef class LiveLoadModelResults LiveLoadModelResults;
#else
typedef struct LiveLoadModelResults LiveLoadModelResults;
#endif /* __cplusplus */

#endif 	/* __LiveLoadModelResults_FWD_DEFINED__ */


#ifndef __LiveLoadModelStressResults_FWD_DEFINED__
#define __LiveLoadModelStressResults_FWD_DEFINED__

#ifdef __cplusplus
typedef class LiveLoadModelStressResults LiveLoadModelStressResults;
#else
typedef struct LiveLoadModelStressResults LiveLoadModelStressResults;
#endif /* __cplusplus */

#endif 	/* __LiveLoadModelStressResults_FWD_DEFINED__ */


#ifndef __EnvelopedVehicularResponseFactory_FWD_DEFINED__
#define __EnvelopedVehicularResponseFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnvelopedVehicularResponseFactory EnvelopedVehicularResponseFactory;
#else
typedef struct EnvelopedVehicularResponseFactory EnvelopedVehicularResponseFactory;
#endif /* __cplusplus */

#endif 	/* __EnvelopedVehicularResponseFactory_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"
#include "WBFLLBAM.h"
#include "WBFLLBAMAnalysis.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLLBAMLiveLoader_0000_0000 */
/* [local] */ 

#include "LBAMLiveLoaderErrors.h"


extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAMLiveLoader_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAMLiveLoader_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLLBAMLiveLoader_LIBRARY_DEFINED__
#define __WBFLLBAMLiveLoader_LIBRARY_DEFINED__

/* library WBFLLBAMLiveLoader */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 

typedef /* [public][helpstring][uuid][public] */  DECLSPEC_UUID("E5972CBF-5C95-4fc0-8BBC-045496AD3872") 
enum __MIDL___MIDL_itf_WBFLLBAMLiveLoader_0000_0000_0001
    {
        lctIVehicularAnalysisContextChanged	= 70001,
        lctLiveLoadChanged	= 70002,
        lctStiffnessResponseChanged	= 70003,
        lctLiveLoadConfigurationChanged	= 70004
    } 	LBAMLLChangeTargetType;


EXTERN_C const IID LIBID_WBFLLBAMLiveLoader;

#ifndef __IVehicularAnalysisContext_INTERFACE_DEFINED__
#define __IVehicularAnalysisContext_INTERFACE_DEFINED__

/* interface IVehicularAnalysisContext */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVehicularAnalysisContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D010B702-8E8B-44D0-84DB-8B50B32D79EE")
    IVehicularAnalysisContext : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ ILBAMModel *model,
            /* [in] */ IInfluenceLineResponse *influence,
            /* [in] */ ILiveLoadNegativeMomentRegion *nllr,
            /* [in] */ IAnalysisPOIs *pois,
            /* [in] */ IGetDistributionFactors *dfs,
            /* [in] */ IGetStressPoints *gcs) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Model( 
            /* [retval][out] */ ILBAMModel **ppModel) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVehicularAnalysisContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVehicularAnalysisContext * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVehicularAnalysisContext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVehicularAnalysisContext * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IVehicularAnalysisContext * This,
            /* [in] */ ILBAMModel *model,
            /* [in] */ IInfluenceLineResponse *influence,
            /* [in] */ ILiveLoadNegativeMomentRegion *nllr,
            /* [in] */ IAnalysisPOIs *pois,
            /* [in] */ IGetDistributionFactors *dfs,
            /* [in] */ IGetStressPoints *gcs);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Model )( 
            IVehicularAnalysisContext * This,
            /* [retval][out] */ ILBAMModel **ppModel);
        
        END_INTERFACE
    } IVehicularAnalysisContextVtbl;

    interface IVehicularAnalysisContext
    {
        CONST_VTBL struct IVehicularAnalysisContextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVehicularAnalysisContext_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVehicularAnalysisContext_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVehicularAnalysisContext_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVehicularAnalysisContext_Initialize(This,model,influence,nllr,pois,dfs,gcs)	\
    ( (This)->lpVtbl -> Initialize(This,model,influence,nllr,pois,dfs,gcs) ) 

#define IVehicularAnalysisContext_get_Model(This,ppModel)	\
    ( (This)->lpVtbl -> get_Model(This,ppModel) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVehicularAnalysisContext_INTERFACE_DEFINED__ */


#ifndef __IVehicularAnalysisContextEvents_INTERFACE_DEFINED__
#define __IVehicularAnalysisContextEvents_INTERFACE_DEFINED__

/* interface IVehicularAnalysisContextEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][oleautomation][object] */ 


EXTERN_C const IID IID_IVehicularAnalysisContextEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C494C99B-016A-43bd-AA1D-0B7246221EA6")
    IVehicularAnalysisContextEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLiveLoadChanged( 
            /* [in] */ LiveLoadModelType lltype) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStiffnessResponseChanged( 
            /* [in] */ ChangeScopeType scope,
            /* [in] */ PoiIDType poiID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVehicularAnalysisContextEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVehicularAnalysisContextEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVehicularAnalysisContextEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVehicularAnalysisContextEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLiveLoadChanged )( 
            IVehicularAnalysisContextEvents * This,
            /* [in] */ LiveLoadModelType lltype);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStiffnessResponseChanged )( 
            IVehicularAnalysisContextEvents * This,
            /* [in] */ ChangeScopeType scope,
            /* [in] */ PoiIDType poiID);
        
        END_INTERFACE
    } IVehicularAnalysisContextEventsVtbl;

    interface IVehicularAnalysisContextEvents
    {
        CONST_VTBL struct IVehicularAnalysisContextEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVehicularAnalysisContextEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVehicularAnalysisContextEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVehicularAnalysisContextEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVehicularAnalysisContextEvents_OnLiveLoadChanged(This,lltype)	\
    ( (This)->lpVtbl -> OnLiveLoadChanged(This,lltype) ) 

#define IVehicularAnalysisContextEvents_OnStiffnessResponseChanged(This,scope,poiID)	\
    ( (This)->lpVtbl -> OnStiffnessResponseChanged(This,scope,poiID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVehicularAnalysisContextEvents_INTERFACE_DEFINED__ */


#ifndef __IDependOnVehicularAnalysisContext_INTERFACE_DEFINED__
#define __IDependOnVehicularAnalysisContext_INTERFACE_DEFINED__

/* interface IDependOnVehicularAnalysisContext */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDependOnVehicularAnalysisContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5640876E-1A20-417f-A7D7-E5CEDCF14543")
    IDependOnVehicularAnalysisContext : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IUnknown *context) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDependOnVehicularAnalysisContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDependOnVehicularAnalysisContext * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDependOnVehicularAnalysisContext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDependOnVehicularAnalysisContext * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IDependOnVehicularAnalysisContext * This,
            /* [in] */ IUnknown *context);
        
        END_INTERFACE
    } IDependOnVehicularAnalysisContextVtbl;

    interface IDependOnVehicularAnalysisContext
    {
        CONST_VTBL struct IDependOnVehicularAnalysisContextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDependOnVehicularAnalysisContext_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDependOnVehicularAnalysisContext_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDependOnVehicularAnalysisContext_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDependOnVehicularAnalysisContext_Initialize(This,context)	\
    ( (This)->lpVtbl -> Initialize(This,context) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDependOnVehicularAnalysisContext_INTERFACE_DEFINED__ */


#ifndef __ISupportLocations_INTERFACE_DEFINED__
#define __ISupportLocations_INTERFACE_DEFINED__

/* interface ISupportLocations */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISupportLocations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF2ED39C-CBD8-460e-840F-0417D40BD2B5")
    ISupportLocations : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftOverhang( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightOverhang( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SupportLocations( 
            /* [retval][out] */ IDblArray **suppLocs) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TotalLength( 
            /* [retval][out] */ Float64 *Length) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IsInteriorSupport( 
            /* [in] */ SupportIDType supportID,
            /* [retval][out] */ VARIANT_BOOL *isInterior) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportLocationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupportLocations * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupportLocations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupportLocations * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftOverhang )( 
            ISupportLocations * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightOverhang )( 
            ISupportLocations * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupportLocations )( 
            ISupportLocations * This,
            /* [retval][out] */ IDblArray **suppLocs);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TotalLength )( 
            ISupportLocations * This,
            /* [retval][out] */ Float64 *Length);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsInteriorSupport )( 
            ISupportLocations * This,
            /* [in] */ SupportIDType supportID,
            /* [retval][out] */ VARIANT_BOOL *isInterior);
        
        END_INTERFACE
    } ISupportLocationsVtbl;

    interface ISupportLocations
    {
        CONST_VTBL struct ISupportLocationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupportLocations_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupportLocations_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupportLocations_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupportLocations_get_LeftOverhang(This,pVal)	\
    ( (This)->lpVtbl -> get_LeftOverhang(This,pVal) ) 

#define ISupportLocations_get_RightOverhang(This,pVal)	\
    ( (This)->lpVtbl -> get_RightOverhang(This,pVal) ) 

#define ISupportLocations_get_SupportLocations(This,suppLocs)	\
    ( (This)->lpVtbl -> get_SupportLocations(This,suppLocs) ) 

#define ISupportLocations_get_TotalLength(This,Length)	\
    ( (This)->lpVtbl -> get_TotalLength(This,Length) ) 

#define ISupportLocations_IsInteriorSupport(This,supportID,isInterior)	\
    ( (This)->lpVtbl -> IsInteriorSupport(This,supportID,isInterior) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupportLocations_INTERFACE_DEFINED__ */


#ifndef __ILiveLoadConfiguration_INTERFACE_DEFINED__
#define __ILiveLoadConfiguration_INTERFACE_DEFINED__

/* interface ILiveLoadConfiguration */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILiveLoadConfiguration;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("75ECDDE4-5B36-4E36-9532-F5527F6D7131")
    ILiveLoadConfiguration : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LiveLoadModel( 
            /* [retval][out] */ LiveLoadModelType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LiveLoadModel( 
            /* [in] */ LiveLoadModelType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VehicleIndex( 
            /* [retval][out] */ VehicleIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VehicleIndex( 
            /* [in] */ VehicleIndexType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VehicularLoadConfiguration( 
            /* [retval][out] */ VehicularLoadConfigurationType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VehicularLoadConfiguration( 
            /* [in] */ VehicularLoadConfigurationType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TruckPosition( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TruckPosition( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TruckDirection( 
            /* [retval][out] */ TruckDirectionType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TruckDirection( 
            /* [in] */ TruckDirectionType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PivotAxleIndex( 
            /* [retval][out] */ AxleIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PivotAxleIndex( 
            /* [in] */ AxleIndexType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VariableSpacing( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VariableSpacing( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AxleConfig( 
            /* [retval][out] */ IIndexArray **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AxleConfig( 
            /* [in] */ IIndexArray *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DoApplyImpact( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DoApplyImpact( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsApplicable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IsApplicable( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DistributionFactorType( 
            /* [retval][out] */ DistributionFactorType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DistributionFactorType( 
            /* [in] */ DistributionFactorType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ForceEffect( 
            /* [retval][out] */ ForceEffectType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ForceEffect( 
            /* [in] */ ForceEffectType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Optimization( 
            /* [retval][out] */ OptimizationType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Optimization( 
            /* [in] */ OptimizationType newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILiveLoadConfiguration **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadConfigurationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoadConfiguration * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoadConfiguration * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoadConfiguration * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LiveLoadModel )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ LiveLoadModelType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LiveLoadModel )( 
            ILiveLoadConfiguration * This,
            /* [in] */ LiveLoadModelType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VehicleIndex )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ VehicleIndexType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VehicleIndex )( 
            ILiveLoadConfiguration * This,
            /* [in] */ VehicleIndexType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VehicularLoadConfiguration )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ VehicularLoadConfigurationType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VehicularLoadConfiguration )( 
            ILiveLoadConfiguration * This,
            /* [in] */ VehicularLoadConfigurationType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TruckPosition )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TruckPosition )( 
            ILiveLoadConfiguration * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TruckDirection )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ TruckDirectionType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TruckDirection )( 
            ILiveLoadConfiguration * This,
            /* [in] */ TruckDirectionType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PivotAxleIndex )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ AxleIndexType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PivotAxleIndex )( 
            ILiveLoadConfiguration * This,
            /* [in] */ AxleIndexType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VariableSpacing )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VariableSpacing )( 
            ILiveLoadConfiguration * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AxleConfig )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ IIndexArray **pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AxleConfig )( 
            ILiveLoadConfiguration * This,
            /* [in] */ IIndexArray *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DoApplyImpact )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DoApplyImpact )( 
            ILiveLoadConfiguration * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsApplicable )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsApplicable )( 
            ILiveLoadConfiguration * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DistributionFactorType )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ DistributionFactorType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DistributionFactorType )( 
            ILiveLoadConfiguration * This,
            /* [in] */ DistributionFactorType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForceEffect )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ ForceEffectType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ForceEffect )( 
            ILiveLoadConfiguration * This,
            /* [in] */ ForceEffectType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Optimization )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ OptimizationType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Optimization )( 
            ILiveLoadConfiguration * This,
            /* [in] */ OptimizationType newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILiveLoadConfiguration * This,
            /* [retval][out] */ ILiveLoadConfiguration **clone);
        
        END_INTERFACE
    } ILiveLoadConfigurationVtbl;

    interface ILiveLoadConfiguration
    {
        CONST_VTBL struct ILiveLoadConfigurationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoadConfiguration_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoadConfiguration_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoadConfiguration_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoadConfiguration_get_LiveLoadModel(This,pVal)	\
    ( (This)->lpVtbl -> get_LiveLoadModel(This,pVal) ) 

#define ILiveLoadConfiguration_put_LiveLoadModel(This,newVal)	\
    ( (This)->lpVtbl -> put_LiveLoadModel(This,newVal) ) 

#define ILiveLoadConfiguration_get_VehicleIndex(This,pVal)	\
    ( (This)->lpVtbl -> get_VehicleIndex(This,pVal) ) 

#define ILiveLoadConfiguration_put_VehicleIndex(This,newVal)	\
    ( (This)->lpVtbl -> put_VehicleIndex(This,newVal) ) 

#define ILiveLoadConfiguration_get_VehicularLoadConfiguration(This,pVal)	\
    ( (This)->lpVtbl -> get_VehicularLoadConfiguration(This,pVal) ) 

#define ILiveLoadConfiguration_put_VehicularLoadConfiguration(This,newVal)	\
    ( (This)->lpVtbl -> put_VehicularLoadConfiguration(This,newVal) ) 

#define ILiveLoadConfiguration_get_TruckPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_TruckPosition(This,pVal) ) 

#define ILiveLoadConfiguration_put_TruckPosition(This,newVal)	\
    ( (This)->lpVtbl -> put_TruckPosition(This,newVal) ) 

#define ILiveLoadConfiguration_get_TruckDirection(This,pVal)	\
    ( (This)->lpVtbl -> get_TruckDirection(This,pVal) ) 

#define ILiveLoadConfiguration_put_TruckDirection(This,newVal)	\
    ( (This)->lpVtbl -> put_TruckDirection(This,newVal) ) 

#define ILiveLoadConfiguration_get_PivotAxleIndex(This,pVal)	\
    ( (This)->lpVtbl -> get_PivotAxleIndex(This,pVal) ) 

#define ILiveLoadConfiguration_put_PivotAxleIndex(This,newVal)	\
    ( (This)->lpVtbl -> put_PivotAxleIndex(This,newVal) ) 

#define ILiveLoadConfiguration_get_VariableSpacing(This,pVal)	\
    ( (This)->lpVtbl -> get_VariableSpacing(This,pVal) ) 

#define ILiveLoadConfiguration_put_VariableSpacing(This,newVal)	\
    ( (This)->lpVtbl -> put_VariableSpacing(This,newVal) ) 

#define ILiveLoadConfiguration_get_AxleConfig(This,pVal)	\
    ( (This)->lpVtbl -> get_AxleConfig(This,pVal) ) 

#define ILiveLoadConfiguration_put_AxleConfig(This,newVal)	\
    ( (This)->lpVtbl -> put_AxleConfig(This,newVal) ) 

#define ILiveLoadConfiguration_get_DoApplyImpact(This,pVal)	\
    ( (This)->lpVtbl -> get_DoApplyImpact(This,pVal) ) 

#define ILiveLoadConfiguration_put_DoApplyImpact(This,newVal)	\
    ( (This)->lpVtbl -> put_DoApplyImpact(This,newVal) ) 

#define ILiveLoadConfiguration_get_IsApplicable(This,pVal)	\
    ( (This)->lpVtbl -> get_IsApplicable(This,pVal) ) 

#define ILiveLoadConfiguration_put_IsApplicable(This,newVal)	\
    ( (This)->lpVtbl -> put_IsApplicable(This,newVal) ) 

#define ILiveLoadConfiguration_get_DistributionFactorType(This,pVal)	\
    ( (This)->lpVtbl -> get_DistributionFactorType(This,pVal) ) 

#define ILiveLoadConfiguration_put_DistributionFactorType(This,newVal)	\
    ( (This)->lpVtbl -> put_DistributionFactorType(This,newVal) ) 

#define ILiveLoadConfiguration_get_ForceEffect(This,pVal)	\
    ( (This)->lpVtbl -> get_ForceEffect(This,pVal) ) 

#define ILiveLoadConfiguration_put_ForceEffect(This,newVal)	\
    ( (This)->lpVtbl -> put_ForceEffect(This,newVal) ) 

#define ILiveLoadConfiguration_get_Optimization(This,pVal)	\
    ( (This)->lpVtbl -> get_Optimization(This,pVal) ) 

#define ILiveLoadConfiguration_put_Optimization(This,newVal)	\
    ( (This)->lpVtbl -> put_Optimization(This,newVal) ) 

#define ILiveLoadConfiguration_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoadConfiguration_INTERFACE_DEFINED__ */


#ifndef __ILiveLoadConfigurationEvents_INTERFACE_DEFINED__
#define __ILiveLoadConfigurationEvents_INTERFACE_DEFINED__

/* interface ILiveLoadConfigurationEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILiveLoadConfigurationEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("301D2692-BFDD-4937-B454-7DF2A388D199")
    ILiveLoadConfigurationEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLiveLoadConfigurationChanged( 
            /* [in] */ ILiveLoadConfiguration *config) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadConfigurationEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoadConfigurationEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoadConfigurationEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoadConfigurationEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLiveLoadConfigurationChanged )( 
            ILiveLoadConfigurationEvents * This,
            /* [in] */ ILiveLoadConfiguration *config);
        
        END_INTERFACE
    } ILiveLoadConfigurationEventsVtbl;

    interface ILiveLoadConfigurationEvents
    {
        CONST_VTBL struct ILiveLoadConfigurationEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoadConfigurationEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoadConfigurationEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoadConfigurationEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoadConfigurationEvents_OnLiveLoadConfigurationChanged(This,config)	\
    ( (This)->lpVtbl -> OnLiveLoadConfigurationChanged(This,config) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoadConfigurationEvents_INTERFACE_DEFINED__ */


#ifndef __ILiveLoadModelSectionResults_INTERFACE_DEFINED__
#define __ILiveLoadModelSectionResults_INTERFACE_DEFINED__

/* interface ILiveLoadModelSectionResults */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILiveLoadModelSectionResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("507DB6D8-E616-46E4-BCEE-AD3B9EA069EE")
    ILiveLoadModelSectionResults : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ Float64 leftResult,
            /* [in] */ ILiveLoadConfiguration *leftConfig,
            /* [in] */ Float64 rightResult,
            /* [in] */ ILiveLoadConfiguration *rightConfig) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetResult( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 leftResult,
            /* [in] */ ILiveLoadConfiguration *leftConfig,
            /* [in] */ Float64 rightResult,
            /* [in] */ ILiveLoadConfiguration *rightConfig) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetResult( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *leftResult,
            /* [out] */ ILiveLoadConfiguration **leftConfig,
            /* [out] */ Float64 *rightResult,
            /* [out] */ ILiveLoadConfiguration **rightConfig) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadModelSectionResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoadModelSectionResults * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoadModelSectionResults * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoadModelSectionResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILiveLoadModelSectionResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            ILiveLoadModelSectionResults * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILiveLoadModelSectionResults * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILiveLoadModelSectionResults * This,
            /* [in] */ Float64 leftResult,
            /* [in] */ ILiveLoadConfiguration *leftConfig,
            /* [in] */ Float64 rightResult,
            /* [in] */ ILiveLoadConfiguration *rightConfig);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetResult )( 
            ILiveLoadModelSectionResults * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 leftResult,
            /* [in] */ ILiveLoadConfiguration *leftConfig,
            /* [in] */ Float64 rightResult,
            /* [in] */ ILiveLoadConfiguration *rightConfig);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            ILiveLoadModelSectionResults * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *leftResult,
            /* [out] */ ILiveLoadConfiguration **leftConfig,
            /* [out] */ Float64 *rightResult,
            /* [out] */ ILiveLoadConfiguration **rightConfig);
        
        END_INTERFACE
    } ILiveLoadModelSectionResultsVtbl;

    interface ILiveLoadModelSectionResults
    {
        CONST_VTBL struct ILiveLoadModelSectionResultsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoadModelSectionResults_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoadModelSectionResults_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoadModelSectionResults_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoadModelSectionResults_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILiveLoadModelSectionResults_Reserve(This,size)	\
    ( (This)->lpVtbl -> Reserve(This,size) ) 

#define ILiveLoadModelSectionResults_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILiveLoadModelSectionResults_Add(This,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> Add(This,leftResult,leftConfig,rightResult,rightConfig) ) 

#define ILiveLoadModelSectionResults_SetResult(This,index,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> SetResult(This,index,leftResult,leftConfig,rightResult,rightConfig) ) 

#define ILiveLoadModelSectionResults_GetResult(This,index,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> GetResult(This,index,leftResult,leftConfig,rightResult,rightConfig) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoadModelSectionResults_INTERFACE_DEFINED__ */


#ifndef __ILiveLoadModelResults_INTERFACE_DEFINED__
#define __ILiveLoadModelResults_INTERFACE_DEFINED__

/* interface ILiveLoadModelResults */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILiveLoadModelResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6BC9DDBA-71C1-489b-A6C4-B7DF7811BE0C")
    ILiveLoadModelResults : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ Float64 result,
            /* [in] */ ILiveLoadConfiguration *config) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetResult( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 result,
            /* [in] */ ILiveLoadConfiguration *config) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetResult( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *result,
            /* [out] */ ILiveLoadConfiguration **config) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadModelResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoadModelResults * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoadModelResults * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoadModelResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILiveLoadModelResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            ILiveLoadModelResults * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILiveLoadModelResults * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILiveLoadModelResults * This,
            /* [in] */ Float64 result,
            /* [in] */ ILiveLoadConfiguration *config);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetResult )( 
            ILiveLoadModelResults * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 result,
            /* [in] */ ILiveLoadConfiguration *config);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            ILiveLoadModelResults * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *result,
            /* [out] */ ILiveLoadConfiguration **config);
        
        END_INTERFACE
    } ILiveLoadModelResultsVtbl;

    interface ILiveLoadModelResults
    {
        CONST_VTBL struct ILiveLoadModelResultsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoadModelResults_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoadModelResults_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoadModelResults_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoadModelResults_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILiveLoadModelResults_Reserve(This,size)	\
    ( (This)->lpVtbl -> Reserve(This,size) ) 

#define ILiveLoadModelResults_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILiveLoadModelResults_Add(This,result,config)	\
    ( (This)->lpVtbl -> Add(This,result,config) ) 

#define ILiveLoadModelResults_SetResult(This,index,result,config)	\
    ( (This)->lpVtbl -> SetResult(This,index,result,config) ) 

#define ILiveLoadModelResults_GetResult(This,index,result,config)	\
    ( (This)->lpVtbl -> GetResult(This,index,result,config) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoadModelResults_INTERFACE_DEFINED__ */


#ifndef __ILiveLoadModelStressResults_INTERFACE_DEFINED__
#define __ILiveLoadModelStressResults_INTERFACE_DEFINED__

/* interface ILiveLoadModelStressResults */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILiveLoadModelStressResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6632DF91-1B2F-451D-99B8-6006F7AD1E52")
    ILiveLoadModelStressResults : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IStressResult *leftResult,
            /* [in] */ ILiveLoadConfiguration *leftConfig,
            /* [in] */ IStressResult *rightResult,
            /* [in] */ ILiveLoadConfiguration *rightConfig) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetResult( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ IStressResult *leftResult,
            /* [in] */ ILiveLoadConfiguration *leftConfig,
            /* [in] */ IStressResult *rightResult,
            /* [in] */ ILiveLoadConfiguration *rightConfig) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetResult( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ IStressResult **leftResult,
            /* [out] */ ILiveLoadConfiguration **leftConfig,
            /* [out] */ IStressResult **rightResult,
            /* [out] */ ILiveLoadConfiguration **rightConfig) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadModelStressResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoadModelStressResults * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoadModelStressResults * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoadModelStressResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILiveLoadModelStressResults * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            ILiveLoadModelStressResults * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILiveLoadModelStressResults * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILiveLoadModelStressResults * This,
            /* [in] */ IStressResult *leftResult,
            /* [in] */ ILiveLoadConfiguration *leftConfig,
            /* [in] */ IStressResult *rightResult,
            /* [in] */ ILiveLoadConfiguration *rightConfig);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetResult )( 
            ILiveLoadModelStressResults * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ IStressResult *leftResult,
            /* [in] */ ILiveLoadConfiguration *leftConfig,
            /* [in] */ IStressResult *rightResult,
            /* [in] */ ILiveLoadConfiguration *rightConfig);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            ILiveLoadModelStressResults * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ IStressResult **leftResult,
            /* [out] */ ILiveLoadConfiguration **leftConfig,
            /* [out] */ IStressResult **rightResult,
            /* [out] */ ILiveLoadConfiguration **rightConfig);
        
        END_INTERFACE
    } ILiveLoadModelStressResultsVtbl;

    interface ILiveLoadModelStressResults
    {
        CONST_VTBL struct ILiveLoadModelStressResultsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoadModelStressResults_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoadModelStressResults_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoadModelStressResults_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoadModelStressResults_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILiveLoadModelStressResults_Reserve(This,size)	\
    ( (This)->lpVtbl -> Reserve(This,size) ) 

#define ILiveLoadModelStressResults_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILiveLoadModelStressResults_Add(This,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> Add(This,leftResult,leftConfig,rightResult,rightConfig) ) 

#define ILiveLoadModelStressResults_SetResult(This,index,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> SetResult(This,index,leftResult,leftConfig,rightResult,rightConfig) ) 

#define ILiveLoadModelStressResults_GetResult(This,index,leftResult,leftConfig,rightResult,rightConfig)	\
    ( (This)->lpVtbl -> GetResult(This,index,leftResult,leftConfig,rightResult,rightConfig) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoadModelStressResults_INTERFACE_DEFINED__ */


#ifndef __IEnvelopedVehicularResponse_INTERFACE_DEFINED__
#define __IEnvelopedVehicularResponse_INTERFACE_DEFINED__

/* interface IEnvelopedVehicularResponse */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IEnvelopedVehicularResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5327AB6C-3122-430F-9F4F-76682BCC9B69")
    IEnvelopedVehicularResponse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeForces( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ VehicleIndexType vehicleIndex,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ DistributionFactorType distributionType,
            /* [in] */ VARIANT_BOOL computePlacements,
            /* [retval][out] */ ILiveLoadModelSectionResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeDeflections( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ VehicleIndexType vehicleIndex,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ DistributionFactorType distributionType,
            /* [in] */ VARIANT_BOOL computePlacements,
            /* [retval][out] */ ILiveLoadModelSectionResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeReactions( 
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ VehicleIndexType vehicleIndex,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ DistributionFactorType distributionType,
            /* [in] */ VARIANT_BOOL computePlacements,
            /* [retval][out] */ ILiveLoadModelResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeSupportDeflections( 
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ VehicleIndexType vehicleIndex,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ DistributionFactorType distributionType,
            /* [in] */ VARIANT_BOOL computePlacements,
            /* [retval][out] */ ILiveLoadModelResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeStresses( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ VehicleIndexType vehicleIndex,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ DistributionFactorType distributionType,
            /* [in] */ VARIANT_BOOL computePlacements,
            /* [retval][out] */ ILiveLoadModelStressResults **results) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnvelopedVehicularResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnvelopedVehicularResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnvelopedVehicularResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnvelopedVehicularResponse * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeForces )( 
            IEnvelopedVehicularResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ VehicleIndexType vehicleIndex,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ DistributionFactorType distributionType,
            /* [in] */ VARIANT_BOOL computePlacements,
            /* [retval][out] */ ILiveLoadModelSectionResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeDeflections )( 
            IEnvelopedVehicularResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ VehicleIndexType vehicleIndex,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ DistributionFactorType distributionType,
            /* [in] */ VARIANT_BOOL computePlacements,
            /* [retval][out] */ ILiveLoadModelSectionResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeReactions )( 
            IEnvelopedVehicularResponse * This,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ VehicleIndexType vehicleIndex,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ DistributionFactorType distributionType,
            /* [in] */ VARIANT_BOOL computePlacements,
            /* [retval][out] */ ILiveLoadModelResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeSupportDeflections )( 
            IEnvelopedVehicularResponse * This,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ VehicleIndexType vehicleIndex,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ DistributionFactorType distributionType,
            /* [in] */ VARIANT_BOOL computePlacements,
            /* [retval][out] */ ILiveLoadModelResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeStresses )( 
            IEnvelopedVehicularResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ VehicleIndexType vehicleIndex,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ DistributionFactorType distributionType,
            /* [in] */ VARIANT_BOOL computePlacements,
            /* [retval][out] */ ILiveLoadModelStressResults **results);
        
        END_INTERFACE
    } IEnvelopedVehicularResponseVtbl;

    interface IEnvelopedVehicularResponse
    {
        CONST_VTBL struct IEnvelopedVehicularResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnvelopedVehicularResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnvelopedVehicularResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnvelopedVehicularResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnvelopedVehicularResponse_ComputeForces(This,poiIDs,stage,type,vehicleIndex,orientation,effect,optimization,vehConfiguration,applyImpact,distributionType,computePlacements,results)	\
    ( (This)->lpVtbl -> ComputeForces(This,poiIDs,stage,type,vehicleIndex,orientation,effect,optimization,vehConfiguration,applyImpact,distributionType,computePlacements,results) ) 

#define IEnvelopedVehicularResponse_ComputeDeflections(This,poiIDs,stage,type,vehicleIndex,effect,optimization,vehConfiguration,applyImpact,distributionType,computePlacements,results)	\
    ( (This)->lpVtbl -> ComputeDeflections(This,poiIDs,stage,type,vehicleIndex,effect,optimization,vehConfiguration,applyImpact,distributionType,computePlacements,results) ) 

#define IEnvelopedVehicularResponse_ComputeReactions(This,supportIDs,stage,type,vehicleIndex,effect,optimization,vehConfiguration,applyImpact,distributionType,computePlacements,results)	\
    ( (This)->lpVtbl -> ComputeReactions(This,supportIDs,stage,type,vehicleIndex,effect,optimization,vehConfiguration,applyImpact,distributionType,computePlacements,results) ) 

#define IEnvelopedVehicularResponse_ComputeSupportDeflections(This,supportIDs,stage,type,vehicleIndex,effect,optimization,vehConfiguration,applyImpact,distributionType,computePlacements,results)	\
    ( (This)->lpVtbl -> ComputeSupportDeflections(This,supportIDs,stage,type,vehicleIndex,effect,optimization,vehConfiguration,applyImpact,distributionType,computePlacements,results) ) 

#define IEnvelopedVehicularResponse_ComputeStresses(This,poiIDs,stage,type,vehicleIndex,effect,optimization,vehConfiguration,applyImpact,distributionType,computePlacements,results)	\
    ( (This)->lpVtbl -> ComputeStresses(This,poiIDs,stage,type,vehicleIndex,effect,optimization,vehConfiguration,applyImpact,distributionType,computePlacements,results) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnvelopedVehicularResponse_INTERFACE_DEFINED__ */


#ifndef __IBasicVehicularResponse_INTERFACE_DEFINED__
#define __IBasicVehicularResponse_INTERFACE_DEFINED__

/* interface IBasicVehicularResponse */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBasicVehicularResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4E6F569-62C7-4932-AD45-0D973BA73A8A")
    IBasicVehicularResponse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeForces( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ILiveLoadConfiguration *config,
            /* [retval][out] */ ISectionResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeDeflections( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILiveLoadConfiguration *config,
            /* [retval][out] */ ISectionResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeReactions( 
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILiveLoadConfiguration *config,
            /* [retval][out] */ IResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeSupportDeflections( 
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILiveLoadConfiguration *config,
            /* [retval][out] */ IResult3Ds **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeStresses( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILiveLoadConfiguration *config,
            /* [retval][out] */ ISectionStressResults **results) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBasicVehicularResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBasicVehicularResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBasicVehicularResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBasicVehicularResponse * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeForces )( 
            IBasicVehicularResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ILiveLoadConfiguration *config,
            /* [retval][out] */ ISectionResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeDeflections )( 
            IBasicVehicularResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILiveLoadConfiguration *config,
            /* [retval][out] */ ISectionResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeReactions )( 
            IBasicVehicularResponse * This,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILiveLoadConfiguration *config,
            /* [retval][out] */ IResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeSupportDeflections )( 
            IBasicVehicularResponse * This,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILiveLoadConfiguration *config,
            /* [retval][out] */ IResult3Ds **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeStresses )( 
            IBasicVehicularResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ ILiveLoadConfiguration *config,
            /* [retval][out] */ ISectionStressResults **results);
        
        END_INTERFACE
    } IBasicVehicularResponseVtbl;

    interface IBasicVehicularResponse
    {
        CONST_VTBL struct IBasicVehicularResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBasicVehicularResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBasicVehicularResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBasicVehicularResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBasicVehicularResponse_ComputeForces(This,poiIDs,stage,orientation,config,results)	\
    ( (This)->lpVtbl -> ComputeForces(This,poiIDs,stage,orientation,config,results) ) 

#define IBasicVehicularResponse_ComputeDeflections(This,poiIDs,stage,config,results)	\
    ( (This)->lpVtbl -> ComputeDeflections(This,poiIDs,stage,config,results) ) 

#define IBasicVehicularResponse_ComputeReactions(This,supportIDs,stage,config,results)	\
    ( (This)->lpVtbl -> ComputeReactions(This,supportIDs,stage,config,results) ) 

#define IBasicVehicularResponse_ComputeSupportDeflections(This,supportIDs,stage,config,results)	\
    ( (This)->lpVtbl -> ComputeSupportDeflections(This,supportIDs,stage,config,results) ) 

#define IBasicVehicularResponse_ComputeStresses(This,poiIDs,stage,config,results)	\
    ( (This)->lpVtbl -> ComputeStresses(This,poiIDs,stage,config,results) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBasicVehicularResponse_INTERFACE_DEFINED__ */


#ifndef __IEnvelopedVehicularResponseFactory_INTERFACE_DEFINED__
#define __IEnvelopedVehicularResponseFactory_INTERFACE_DEFINED__

/* interface IEnvelopedVehicularResponseFactory */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IEnvelopedVehicularResponseFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29E23348-A456-4a68-A3CD-1CE39020CAAE")
    IEnvelopedVehicularResponseFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateEnvelopedVehicularResponse( 
            /* [retval][out] */ IEnvelopedVehicularResponse **pEVR) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnvelopedVehicularResponseFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnvelopedVehicularResponseFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnvelopedVehicularResponseFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnvelopedVehicularResponseFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateEnvelopedVehicularResponse )( 
            IEnvelopedVehicularResponseFactory * This,
            /* [retval][out] */ IEnvelopedVehicularResponse **pEVR);
        
        END_INTERFACE
    } IEnvelopedVehicularResponseFactoryVtbl;

    interface IEnvelopedVehicularResponseFactory
    {
        CONST_VTBL struct IEnvelopedVehicularResponseFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnvelopedVehicularResponseFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnvelopedVehicularResponseFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnvelopedVehicularResponseFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnvelopedVehicularResponseFactory_CreateEnvelopedVehicularResponse(This,pEVR)	\
    ( (This)->lpVtbl -> CreateEnvelopedVehicularResponse(This,pEVR) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnvelopedVehicularResponseFactory_INTERFACE_DEFINED__ */


#ifndef __ISupportEnvelopedVehicularResponseFactory_INTERFACE_DEFINED__
#define __ISupportEnvelopedVehicularResponseFactory_INTERFACE_DEFINED__

/* interface ISupportEnvelopedVehicularResponseFactory */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISupportEnvelopedVehicularResponseFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("045494D0-86BA-445c-A42B-88F90B25E503")
    ISupportEnvelopedVehicularResponseFactory : public IUnknown
    {
    public:
        virtual /* [propputref] */ HRESULT STDMETHODCALLTYPE putref_EnvelopedVehicularRepsonseFactory( 
            /* [in] */ IEnvelopedVehicularResponseFactory *pFactory) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EnvelopedVehicularRepsonseFactory( 
            /* [retval][out] */ IEnvelopedVehicularResponseFactory **pFactory) = 0;
        
        virtual /* [propputref] */ HRESULT STDMETHODCALLTYPE putref_EnvelopedVehicularRepsonse( 
            /* [in] */ IEnvelopedVehicularResponse *pResponse) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportEnvelopedVehicularResponseFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupportEnvelopedVehicularResponseFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupportEnvelopedVehicularResponseFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupportEnvelopedVehicularResponseFactory * This);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_EnvelopedVehicularRepsonseFactory )( 
            ISupportEnvelopedVehicularResponseFactory * This,
            /* [in] */ IEnvelopedVehicularResponseFactory *pFactory);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnvelopedVehicularRepsonseFactory )( 
            ISupportEnvelopedVehicularResponseFactory * This,
            /* [retval][out] */ IEnvelopedVehicularResponseFactory **pFactory);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_EnvelopedVehicularRepsonse )( 
            ISupportEnvelopedVehicularResponseFactory * This,
            /* [in] */ IEnvelopedVehicularResponse *pResponse);
        
        END_INTERFACE
    } ISupportEnvelopedVehicularResponseFactoryVtbl;

    interface ISupportEnvelopedVehicularResponseFactory
    {
        CONST_VTBL struct ISupportEnvelopedVehicularResponseFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupportEnvelopedVehicularResponseFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupportEnvelopedVehicularResponseFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupportEnvelopedVehicularResponseFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupportEnvelopedVehicularResponseFactory_putref_EnvelopedVehicularRepsonseFactory(This,pFactory)	\
    ( (This)->lpVtbl -> putref_EnvelopedVehicularRepsonseFactory(This,pFactory) ) 

#define ISupportEnvelopedVehicularResponseFactory_get_EnvelopedVehicularRepsonseFactory(This,pFactory)	\
    ( (This)->lpVtbl -> get_EnvelopedVehicularRepsonseFactory(This,pFactory) ) 

#define ISupportEnvelopedVehicularResponseFactory_putref_EnvelopedVehicularRepsonse(This,pResponse)	\
    ( (This)->lpVtbl -> putref_EnvelopedVehicularRepsonse(This,pResponse) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupportEnvelopedVehicularResponseFactory_INTERFACE_DEFINED__ */


#ifndef __ILiveLoadModelResponse_INTERFACE_DEFINED__
#define __ILiveLoadModelResponse_INTERFACE_DEFINED__

/* interface ILiveLoadModelResponse */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILiveLoadModelResponse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("03CF6636-DC31-4F82-8B6C-6527D280F864")
    ILiveLoadModelResponse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeForces( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ VARIANT_BOOL applyDistribution,
            /* [in] */ VARIANT_BOOL computePlacement,
            /* [retval][out] */ ILiveLoadModelSectionResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeDeflections( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ VARIANT_BOOL applyDistribution,
            /* [in] */ VARIANT_BOOL computePlacement,
            /* [retval][out] */ ILiveLoadModelSectionResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeReactions( 
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ VARIANT_BOOL applyDistribution,
            /* [in] */ VARIANT_BOOL computePlacement,
            /* [retval][out] */ ILiveLoadModelResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeSupportDeflections( 
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ VARIANT_BOOL applyDistribution,
            /* [in] */ VARIANT_BOOL computePlacement,
            /* [retval][out] */ ILiveLoadModelResults **results) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeStresses( 
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ VARIANT_BOOL applyDistribution,
            /* [in] */ VARIANT_BOOL computePlacement,
            /* [retval][out] */ ILiveLoadModelStressResults **results) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadModelResponseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoadModelResponse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoadModelResponse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoadModelResponse * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeForces )( 
            ILiveLoadModelResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ ResultsOrientation orientation,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ VARIANT_BOOL applyDistribution,
            /* [in] */ VARIANT_BOOL computePlacement,
            /* [retval][out] */ ILiveLoadModelSectionResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeDeflections )( 
            ILiveLoadModelResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ VARIANT_BOOL applyDistribution,
            /* [in] */ VARIANT_BOOL computePlacement,
            /* [retval][out] */ ILiveLoadModelSectionResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeReactions )( 
            ILiveLoadModelResponse * This,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ VARIANT_BOOL applyDistribution,
            /* [in] */ VARIANT_BOOL computePlacement,
            /* [retval][out] */ ILiveLoadModelResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeSupportDeflections )( 
            ILiveLoadModelResponse * This,
            /* [in] */ IIDArray *supportIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ VARIANT_BOOL applyDistribution,
            /* [in] */ VARIANT_BOOL computePlacement,
            /* [retval][out] */ ILiveLoadModelResults **results);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeStresses )( 
            ILiveLoadModelResponse * This,
            /* [in] */ IIDArray *poiIDs,
            /* [in] */ BSTR stage,
            /* [in] */ LiveLoadModelType type,
            /* [in] */ ForceEffectType effect,
            /* [in] */ OptimizationType optimization,
            /* [in] */ VehicularLoadConfigurationType vehConfiguration,
            /* [in] */ VARIANT_BOOL applyImpact,
            /* [in] */ VARIANT_BOOL applyDistribution,
            /* [in] */ VARIANT_BOOL computePlacement,
            /* [retval][out] */ ILiveLoadModelStressResults **results);
        
        END_INTERFACE
    } ILiveLoadModelResponseVtbl;

    interface ILiveLoadModelResponse
    {
        CONST_VTBL struct ILiveLoadModelResponseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoadModelResponse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoadModelResponse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoadModelResponse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoadModelResponse_ComputeForces(This,poiIDs,stage,type,orientation,effect,optimization,vehConfiguration,applyImpact,applyDistribution,computePlacement,results)	\
    ( (This)->lpVtbl -> ComputeForces(This,poiIDs,stage,type,orientation,effect,optimization,vehConfiguration,applyImpact,applyDistribution,computePlacement,results) ) 

#define ILiveLoadModelResponse_ComputeDeflections(This,poiIDs,stage,type,effect,optimization,vehConfiguration,applyImpact,applyDistribution,computePlacement,results)	\
    ( (This)->lpVtbl -> ComputeDeflections(This,poiIDs,stage,type,effect,optimization,vehConfiguration,applyImpact,applyDistribution,computePlacement,results) ) 

#define ILiveLoadModelResponse_ComputeReactions(This,supportIDs,stage,type,effect,optimization,vehConfiguration,applyImpact,applyDistribution,computePlacement,results)	\
    ( (This)->lpVtbl -> ComputeReactions(This,supportIDs,stage,type,effect,optimization,vehConfiguration,applyImpact,applyDistribution,computePlacement,results) ) 

#define ILiveLoadModelResponse_ComputeSupportDeflections(This,supportIDs,stage,type,effect,optimization,vehConfiguration,applyImpact,applyDistribution,computePlacement,results)	\
    ( (This)->lpVtbl -> ComputeSupportDeflections(This,supportIDs,stage,type,effect,optimization,vehConfiguration,applyImpact,applyDistribution,computePlacement,results) ) 

#define ILiveLoadModelResponse_ComputeStresses(This,poiIDs,stage,type,effect,optimization,vehConfiguration,applyImpact,applyDistribution,computePlacement,results)	\
    ( (This)->lpVtbl -> ComputeStresses(This,poiIDs,stage,type,effect,optimization,vehConfiguration,applyImpact,applyDistribution,computePlacement,results) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoadModelResponse_INTERFACE_DEFINED__ */


#ifndef __IEnvelopingStrategy_INTERFACE_DEFINED__
#define __IEnvelopingStrategy_INTERFACE_DEFINED__

/* interface IEnvelopingStrategy */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IEnvelopingStrategy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2EF48A46-945E-4f87-B942-A76B39F2385A")
    IEnvelopingStrategy : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Strategy( 
            /* [retval][out] */ IEnvelopedVehicularResponse **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Strategy( 
            /* [in] */ IEnvelopedVehicularResponse *newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnvelopingStrategyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnvelopingStrategy * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnvelopingStrategy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnvelopingStrategy * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strategy )( 
            IEnvelopingStrategy * This,
            /* [retval][out] */ IEnvelopedVehicularResponse **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Strategy )( 
            IEnvelopingStrategy * This,
            /* [in] */ IEnvelopedVehicularResponse *newVal);
        
        END_INTERFACE
    } IEnvelopingStrategyVtbl;

    interface IEnvelopingStrategy
    {
        CONST_VTBL struct IEnvelopingStrategyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnvelopingStrategy_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnvelopingStrategy_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnvelopingStrategy_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnvelopingStrategy_get_Strategy(This,pVal)	\
    ( (This)->lpVtbl -> get_Strategy(This,pVal) ) 

#define IEnvelopingStrategy_putref_Strategy(This,newVal)	\
    ( (This)->lpVtbl -> putref_Strategy(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnvelopingStrategy_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_VehicularAnalysisContext;

#ifdef __cplusplus

class DECLSPEC_UUID("7FCDE23E-4655-4AF7-81B2-8E5C852831A4")
VehicularAnalysisContext;
#endif

EXTERN_C const CLSID CLSID_BasicVehicularResponse;

#ifdef __cplusplus

class DECLSPEC_UUID("6743856D-388C-46EE-8517-02975B951790")
BasicVehicularResponse;
#endif

EXTERN_C const CLSID CLSID_BruteForceVehicularResponse;

#ifdef __cplusplus

class DECLSPEC_UUID("8CB030DC-CB84-47CF-8FAA-71AB8228447A")
BruteForceVehicularResponse;
#endif

EXTERN_C const CLSID CLSID_BruteForceVehicularResponse2;

#ifdef __cplusplus

class DECLSPEC_UUID("F957DB0F-730B-4b90-A2F8-A83212EDB0F5")
BruteForceVehicularResponse2;
#endif

EXTERN_C const CLSID CLSID_LiveLoadConfiguration;

#ifdef __cplusplus

class DECLSPEC_UUID("9AA4092D-749C-48A3-8822-D192C1D0063B")
LiveLoadConfiguration;
#endif

EXTERN_C const CLSID CLSID_LiveLoadModelResponse;

#ifdef __cplusplus

class DECLSPEC_UUID("17850599-F2D0-457D-BA13-69D8F6488E51")
LiveLoadModelResponse;
#endif

EXTERN_C const CLSID CLSID_LiveLoadModelSectionResults;

#ifdef __cplusplus

class DECLSPEC_UUID("2AECD198-BB29-4439-959C-A0F6B977C0BE")
LiveLoadModelSectionResults;
#endif

EXTERN_C const CLSID CLSID_LiveLoadModelResults;

#ifdef __cplusplus

class DECLSPEC_UUID("D3440F19-F960-4580-A915-A1FF9466609C")
LiveLoadModelResults;
#endif

EXTERN_C const CLSID CLSID_LiveLoadModelStressResults;

#ifdef __cplusplus

class DECLSPEC_UUID("CF37172B-654D-446B-B66D-9FFBBC1959FA")
LiveLoadModelStressResults;
#endif

EXTERN_C const CLSID CLSID_EnvelopedVehicularResponseFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("4799D84B-F57B-4519-910E-8949AEB33996")
EnvelopedVehicularResponseFactory;
#endif
#endif /* __WBFLLBAMLiveLoader_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


