

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:28:07 2017
 */
/* Compiler settings for ..\..\Include\WBFLLBAMUtility.idl:
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


#ifndef __WBFLLBAMUtility_h__
#define __WBFLLBAMUtility_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILBAMFactory_FWD_DEFINED__
#define __ILBAMFactory_FWD_DEFINED__
typedef interface ILBAMFactory ILBAMFactory;

#endif 	/* __ILBAMFactory_FWD_DEFINED__ */


#ifndef __ILBAMLRFDFactory_FWD_DEFINED__
#define __ILBAMLRFDFactory_FWD_DEFINED__
typedef interface ILBAMLRFDFactory ILBAMLRFDFactory;

#endif 	/* __ILBAMLRFDFactory_FWD_DEFINED__ */


#ifndef __ILBAMLRFDFactory2_FWD_DEFINED__
#define __ILBAMLRFDFactory2_FWD_DEFINED__
typedef interface ILBAMLRFDFactory2 ILBAMLRFDFactory2;

#endif 	/* __ILBAMLRFDFactory2_FWD_DEFINED__ */


#ifndef __ILBAMLRFDFactory3_FWD_DEFINED__
#define __ILBAMLRFDFactory3_FWD_DEFINED__
typedef interface ILBAMLRFDFactory3 ILBAMLRFDFactory3;

#endif 	/* __ILBAMLRFDFactory3_FWD_DEFINED__ */


#ifndef __LRFDFactory_FWD_DEFINED__
#define __LRFDFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class LRFDFactory LRFDFactory;
#else
typedef struct LRFDFactory LRFDFactory;
#endif /* __cplusplus */

#endif 	/* __LRFDFactory_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"
#include "WBFLLBAM.h"
#include "WBFLUnitServer.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLLBAMUtility_0000_0000 */
/* [local] */ 

#define LBAMU_E_MUST_HAVE_ONE_SPAN      				     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1002)
#define LBAMU_E_E_MUST_BE_GT_ZERO      				     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1003)
#define LBAMU_E_A_MUST_BE_GT_ZERO      				     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1004)
#define LBAMU_E_I_MUST_BE_GT_ZERO      				     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1005)
#define LBAMU_E_DEPTH_MUST_BE_GT_ZERO    			     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1006)
#define LBAMU_E_SPAN_LENGTH_MUST_BE_GT_ZERO 			     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1007)
#define LBAMU_E_POI_INCREMENT_MUST_BE_GT_ZERO		     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1008)
#define LBAMU_E_MUST_HAVE_ONE_SSM      		             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1009)
#define LBAMU_E_INVALID_POI_MEMBER_TYPE  	             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1010)
#define LBAMU_E_POI_BAD_LOCATION  	                     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1011)
#define LBAMU_E_POI_TEMP_SUPPORT_OOR                      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1012)


extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAMUtility_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAMUtility_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLLBAMUtility_LIBRARY_DEFINED__
#define __WBFLLBAMUtility_LIBRARY_DEFINED__

/* library WBFLLBAMUtility */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 

typedef /* [public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("B454245B-8E83-4378-8B46-8DE759EDA165") 
enum __MIDL___MIDL_itf_WBFLLBAMUtility_0000_0000_0001
    {
        dvoDesignTruck	= 0,
        dvoDesignTandem	= 1,
        dvoDualTruckTrain	= 2,
        dvoOptionalLowBoy	= 3
    } 	DesignVehicularLoadOrder;


EXTERN_C const IID LIBID_WBFLLBAMUtility;

#ifndef __ILBAMFactory_INTERFACE_DEFINED__
#define __ILBAMFactory_INTERFACE_DEFINED__

/* interface ILBAMFactory */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILBAMFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12D5CC56-BF21-11D5-B075-00105A9AF985")
    ILBAMFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateSimpleModel( 
            /* [in] */ IDblArray *SpanLengths,
            /* [in] */ Float64 E,
            /* [in] */ Float64 A,
            /* [in] */ Float64 I,
            /* [in] */ Float64 Depth,
            /* [retval][out] */ ILBAMModel **newModel) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSupportIDsForStage( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IIDArray **supportIDs) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MapLoadGroupToLoadCase( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR lgName,
            /* [in] */ BSTR lgDesc,
            /* [in] */ BSTR lcName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateSelfWeightDeadLoad( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR lgName,
            /* [in] */ Float64 unitWgt,
            /* [in] */ Float64 E) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GeneratePOIsOnSuperstructure( 
            /* [in] */ ILBAMModel *Model,
            /* [in] */ PoiIDType startID,
            /* [in] */ PoiIDType Increment,
            /* [retval][out] */ PoiIDType *lastVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSuperstructurePOIs( 
            /* [in] */ ILBAMModel *Model,
            /* [out] */ IIDArray **PoiIDs,
            /* [out] */ IDblArray **PoiLocations) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILBAMFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILBAMFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILBAMFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILBAMFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSimpleModel )( 
            ILBAMFactory * This,
            /* [in] */ IDblArray *SpanLengths,
            /* [in] */ Float64 E,
            /* [in] */ Float64 A,
            /* [in] */ Float64 I,
            /* [in] */ Float64 Depth,
            /* [retval][out] */ ILBAMModel **newModel);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSupportIDsForStage )( 
            ILBAMFactory * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IIDArray **supportIDs);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MapLoadGroupToLoadCase )( 
            ILBAMFactory * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR lgName,
            /* [in] */ BSTR lgDesc,
            /* [in] */ BSTR lcName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSelfWeightDeadLoad )( 
            ILBAMFactory * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR lgName,
            /* [in] */ Float64 unitWgt,
            /* [in] */ Float64 E);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GeneratePOIsOnSuperstructure )( 
            ILBAMFactory * This,
            /* [in] */ ILBAMModel *Model,
            /* [in] */ PoiIDType startID,
            /* [in] */ PoiIDType Increment,
            /* [retval][out] */ PoiIDType *lastVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSuperstructurePOIs )( 
            ILBAMFactory * This,
            /* [in] */ ILBAMModel *Model,
            /* [out] */ IIDArray **PoiIDs,
            /* [out] */ IDblArray **PoiLocations);
        
        END_INTERFACE
    } ILBAMFactoryVtbl;

    interface ILBAMFactory
    {
        CONST_VTBL struct ILBAMFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILBAMFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILBAMFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILBAMFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILBAMFactory_CreateSimpleModel(This,SpanLengths,E,A,I,Depth,newModel)	\
    ( (This)->lpVtbl -> CreateSimpleModel(This,SpanLengths,E,A,I,Depth,newModel) ) 

#define ILBAMFactory_GetSupportIDsForStage(This,pModel,stage,supportIDs)	\
    ( (This)->lpVtbl -> GetSupportIDsForStage(This,pModel,stage,supportIDs) ) 

#define ILBAMFactory_MapLoadGroupToLoadCase(This,pModel,lgName,lgDesc,lcName)	\
    ( (This)->lpVtbl -> MapLoadGroupToLoadCase(This,pModel,lgName,lgDesc,lcName) ) 

#define ILBAMFactory_CreateSelfWeightDeadLoad(This,pModel,stage,lgName,unitWgt,E)	\
    ( (This)->lpVtbl -> CreateSelfWeightDeadLoad(This,pModel,stage,lgName,unitWgt,E) ) 

#define ILBAMFactory_GeneratePOIsOnSuperstructure(This,Model,startID,Increment,lastVal)	\
    ( (This)->lpVtbl -> GeneratePOIsOnSuperstructure(This,Model,startID,Increment,lastVal) ) 

#define ILBAMFactory_GetSuperstructurePOIs(This,Model,PoiIDs,PoiLocations)	\
    ( (This)->lpVtbl -> GetSuperstructurePOIs(This,Model,PoiIDs,PoiLocations) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILBAMFactory_INTERFACE_DEFINED__ */


#ifndef __ILBAMLRFDFactory_INTERFACE_DEFINED__
#define __ILBAMLRFDFactory_INTERFACE_DEFINED__

/* interface ILBAMLRFDFactory */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILBAMLRFDFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1ACF6808-3391-4902-8032-936958682174")
    ILBAMLRFDFactory : public ILBAMFactory
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ConfigureLiveLoad( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ VARIANT_BOOL includeLowBoy,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ConfigureLoadCombinations( 
            /* [in] */ ILBAMModel *pModel) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILBAMLRFDFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILBAMLRFDFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILBAMLRFDFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILBAMLRFDFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSimpleModel )( 
            ILBAMLRFDFactory * This,
            /* [in] */ IDblArray *SpanLengths,
            /* [in] */ Float64 E,
            /* [in] */ Float64 A,
            /* [in] */ Float64 I,
            /* [in] */ Float64 Depth,
            /* [retval][out] */ ILBAMModel **newModel);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSupportIDsForStage )( 
            ILBAMLRFDFactory * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IIDArray **supportIDs);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MapLoadGroupToLoadCase )( 
            ILBAMLRFDFactory * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR lgName,
            /* [in] */ BSTR lgDesc,
            /* [in] */ BSTR lcName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSelfWeightDeadLoad )( 
            ILBAMLRFDFactory * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR lgName,
            /* [in] */ Float64 unitWgt,
            /* [in] */ Float64 E);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GeneratePOIsOnSuperstructure )( 
            ILBAMLRFDFactory * This,
            /* [in] */ ILBAMModel *Model,
            /* [in] */ PoiIDType startID,
            /* [in] */ PoiIDType Increment,
            /* [retval][out] */ PoiIDType *lastVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSuperstructurePOIs )( 
            ILBAMLRFDFactory * This,
            /* [in] */ ILBAMModel *Model,
            /* [out] */ IIDArray **PoiIDs,
            /* [out] */ IDblArray **PoiLocations);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureLiveLoad )( 
            ILBAMLRFDFactory * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ VARIANT_BOOL includeLowBoy,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureLoadCombinations )( 
            ILBAMLRFDFactory * This,
            /* [in] */ ILBAMModel *pModel);
        
        END_INTERFACE
    } ILBAMLRFDFactoryVtbl;

    interface ILBAMLRFDFactory
    {
        CONST_VTBL struct ILBAMLRFDFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILBAMLRFDFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILBAMLRFDFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILBAMLRFDFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILBAMLRFDFactory_CreateSimpleModel(This,SpanLengths,E,A,I,Depth,newModel)	\
    ( (This)->lpVtbl -> CreateSimpleModel(This,SpanLengths,E,A,I,Depth,newModel) ) 

#define ILBAMLRFDFactory_GetSupportIDsForStage(This,pModel,stage,supportIDs)	\
    ( (This)->lpVtbl -> GetSupportIDsForStage(This,pModel,stage,supportIDs) ) 

#define ILBAMLRFDFactory_MapLoadGroupToLoadCase(This,pModel,lgName,lgDesc,lcName)	\
    ( (This)->lpVtbl -> MapLoadGroupToLoadCase(This,pModel,lgName,lgDesc,lcName) ) 

#define ILBAMLRFDFactory_CreateSelfWeightDeadLoad(This,pModel,stage,lgName,unitWgt,E)	\
    ( (This)->lpVtbl -> CreateSelfWeightDeadLoad(This,pModel,stage,lgName,unitWgt,E) ) 

#define ILBAMLRFDFactory_GeneratePOIsOnSuperstructure(This,Model,startID,Increment,lastVal)	\
    ( (This)->lpVtbl -> GeneratePOIsOnSuperstructure(This,Model,startID,Increment,lastVal) ) 

#define ILBAMLRFDFactory_GetSuperstructurePOIs(This,Model,PoiIDs,PoiLocations)	\
    ( (This)->lpVtbl -> GetSuperstructurePOIs(This,Model,PoiIDs,PoiLocations) ) 


#define ILBAMLRFDFactory_ConfigureLiveLoad(This,pModel,includeLowBoy,units,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureLiveLoad(This,pModel,includeLowBoy,units,pUnitServer) ) 

#define ILBAMLRFDFactory_ConfigureLoadCombinations(This,pModel)	\
    ( (This)->lpVtbl -> ConfigureLoadCombinations(This,pModel) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILBAMLRFDFactory_INTERFACE_DEFINED__ */


#ifndef __ILBAMLRFDFactory2_INTERFACE_DEFINED__
#define __ILBAMLRFDFactory2_INTERFACE_DEFINED__

/* interface ILBAMLRFDFactory2 */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILBAMLRFDFactory2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B62C903B-BDE8-4317-9945-267ED015EB69")
    ILBAMLRFDFactory2 : public ILBAMLRFDFactory
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ConfigureDesignLiveLoad( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ VARIANT_BOOL includeDualTrucks,
            /* [in] */ VARIANT_BOOL includeLowBoy,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ConfigureFatigueLiveLoad( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ConfigureDeflectionLiveLoad( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILBAMLRFDFactory2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILBAMLRFDFactory2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILBAMLRFDFactory2 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSimpleModel )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ IDblArray *SpanLengths,
            /* [in] */ Float64 E,
            /* [in] */ Float64 A,
            /* [in] */ Float64 I,
            /* [in] */ Float64 Depth,
            /* [retval][out] */ ILBAMModel **newModel);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSupportIDsForStage )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IIDArray **supportIDs);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MapLoadGroupToLoadCase )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR lgName,
            /* [in] */ BSTR lgDesc,
            /* [in] */ BSTR lcName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSelfWeightDeadLoad )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR lgName,
            /* [in] */ Float64 unitWgt,
            /* [in] */ Float64 E);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GeneratePOIsOnSuperstructure )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ ILBAMModel *Model,
            /* [in] */ PoiIDType startID,
            /* [in] */ PoiIDType Increment,
            /* [retval][out] */ PoiIDType *lastVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSuperstructurePOIs )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ ILBAMModel *Model,
            /* [out] */ IIDArray **PoiIDs,
            /* [out] */ IDblArray **PoiLocations);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureLiveLoad )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ VARIANT_BOOL includeLowBoy,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureLoadCombinations )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ ILBAMModel *pModel);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureDesignLiveLoad )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ VARIANT_BOOL includeDualTrucks,
            /* [in] */ VARIANT_BOOL includeLowBoy,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureFatigueLiveLoad )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureDeflectionLiveLoad )( 
            ILBAMLRFDFactory2 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer);
        
        END_INTERFACE
    } ILBAMLRFDFactory2Vtbl;

    interface ILBAMLRFDFactory2
    {
        CONST_VTBL struct ILBAMLRFDFactory2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILBAMLRFDFactory2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILBAMLRFDFactory2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILBAMLRFDFactory2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILBAMLRFDFactory2_CreateSimpleModel(This,SpanLengths,E,A,I,Depth,newModel)	\
    ( (This)->lpVtbl -> CreateSimpleModel(This,SpanLengths,E,A,I,Depth,newModel) ) 

#define ILBAMLRFDFactory2_GetSupportIDsForStage(This,pModel,stage,supportIDs)	\
    ( (This)->lpVtbl -> GetSupportIDsForStage(This,pModel,stage,supportIDs) ) 

#define ILBAMLRFDFactory2_MapLoadGroupToLoadCase(This,pModel,lgName,lgDesc,lcName)	\
    ( (This)->lpVtbl -> MapLoadGroupToLoadCase(This,pModel,lgName,lgDesc,lcName) ) 

#define ILBAMLRFDFactory2_CreateSelfWeightDeadLoad(This,pModel,stage,lgName,unitWgt,E)	\
    ( (This)->lpVtbl -> CreateSelfWeightDeadLoad(This,pModel,stage,lgName,unitWgt,E) ) 

#define ILBAMLRFDFactory2_GeneratePOIsOnSuperstructure(This,Model,startID,Increment,lastVal)	\
    ( (This)->lpVtbl -> GeneratePOIsOnSuperstructure(This,Model,startID,Increment,lastVal) ) 

#define ILBAMLRFDFactory2_GetSuperstructurePOIs(This,Model,PoiIDs,PoiLocations)	\
    ( (This)->lpVtbl -> GetSuperstructurePOIs(This,Model,PoiIDs,PoiLocations) ) 


#define ILBAMLRFDFactory2_ConfigureLiveLoad(This,pModel,includeLowBoy,units,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureLiveLoad(This,pModel,includeLowBoy,units,pUnitServer) ) 

#define ILBAMLRFDFactory2_ConfigureLoadCombinations(This,pModel)	\
    ( (This)->lpVtbl -> ConfigureLoadCombinations(This,pModel) ) 


#define ILBAMLRFDFactory2_ConfigureDesignLiveLoad(This,pModel,llmt,imTruck,imLane,includeDualTrucks,includeLowBoy,units,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureDesignLiveLoad(This,pModel,llmt,imTruck,imLane,includeDualTrucks,includeLowBoy,units,pUnitServer) ) 

#define ILBAMLRFDFactory2_ConfigureFatigueLiveLoad(This,pModel,llmt,imTruck,imLane,units,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureFatigueLiveLoad(This,pModel,llmt,imTruck,imLane,units,pUnitServer) ) 

#define ILBAMLRFDFactory2_ConfigureDeflectionLiveLoad(This,pModel,llmt,imTruck,imLane,units,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureDeflectionLiveLoad(This,pModel,llmt,imTruck,imLane,units,pUnitServer) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILBAMLRFDFactory2_INTERFACE_DEFINED__ */


#ifndef __ILBAMLRFDFactory3_INTERFACE_DEFINED__
#define __ILBAMLRFDFactory3_INTERFACE_DEFINED__

/* interface ILBAMLRFDFactory3 */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILBAMLRFDFactory3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FEF8CA66-2A31-4663-A001-9DC1700ECBDD")
    ILBAMLRFDFactory3 : public ILBAMLRFDFactory2
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ConfigureLegalLiveLoad( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ VARIANT_BOOL includeType33,
            /* [in] */ VARIANT_BOOL includeDualType33,
            /* [in] */ VARIANT_BOOL removeLaneLoad,
            /* [in] */ IUnitServer *pUnitServer) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ConfigureNotionalRatingLoad( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ IUnitServer *pUnitServer) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ConfigureEmergencyRatingLoad( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ VARIANT_BOOL bIncludeLaneLoad,
            /* [in] */ IUnitServer *pUnitServer) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ConfigureSpecializedHaulingUnits( 
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ IUnitServer *pUnitServer) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILBAMLRFDFactory3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILBAMLRFDFactory3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILBAMLRFDFactory3 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSimpleModel )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ IDblArray *SpanLengths,
            /* [in] */ Float64 E,
            /* [in] */ Float64 A,
            /* [in] */ Float64 I,
            /* [in] */ Float64 Depth,
            /* [retval][out] */ ILBAMModel **newModel);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSupportIDsForStage )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IIDArray **supportIDs);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MapLoadGroupToLoadCase )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR lgName,
            /* [in] */ BSTR lgDesc,
            /* [in] */ BSTR lcName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSelfWeightDeadLoad )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR lgName,
            /* [in] */ Float64 unitWgt,
            /* [in] */ Float64 E);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GeneratePOIsOnSuperstructure )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *Model,
            /* [in] */ PoiIDType startID,
            /* [in] */ PoiIDType Increment,
            /* [retval][out] */ PoiIDType *lastVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSuperstructurePOIs )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *Model,
            /* [out] */ IIDArray **PoiIDs,
            /* [out] */ IDblArray **PoiLocations);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureLiveLoad )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ VARIANT_BOOL includeLowBoy,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureLoadCombinations )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureDesignLiveLoad )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ VARIANT_BOOL includeDualTrucks,
            /* [in] */ VARIANT_BOOL includeLowBoy,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureFatigueLiveLoad )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureDeflectionLiveLoad )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ SpecUnitType units,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureLegalLiveLoad )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ VARIANT_BOOL includeType33,
            /* [in] */ VARIANT_BOOL includeDualType33,
            /* [in] */ VARIANT_BOOL removeLaneLoad,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureNotionalRatingLoad )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureEmergencyRatingLoad )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ VARIANT_BOOL bIncludeLaneLoad,
            /* [in] */ IUnitServer *pUnitServer);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureSpecializedHaulingUnits )( 
            ILBAMLRFDFactory3 * This,
            /* [in] */ ILBAMModel *pModel,
            /* [in] */ LiveLoadModelType llmt,
            /* [in] */ Float64 imTruck,
            /* [in] */ Float64 imLane,
            /* [in] */ IUnitServer *pUnitServer);
        
        END_INTERFACE
    } ILBAMLRFDFactory3Vtbl;

    interface ILBAMLRFDFactory3
    {
        CONST_VTBL struct ILBAMLRFDFactory3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILBAMLRFDFactory3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILBAMLRFDFactory3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILBAMLRFDFactory3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILBAMLRFDFactory3_CreateSimpleModel(This,SpanLengths,E,A,I,Depth,newModel)	\
    ( (This)->lpVtbl -> CreateSimpleModel(This,SpanLengths,E,A,I,Depth,newModel) ) 

#define ILBAMLRFDFactory3_GetSupportIDsForStage(This,pModel,stage,supportIDs)	\
    ( (This)->lpVtbl -> GetSupportIDsForStage(This,pModel,stage,supportIDs) ) 

#define ILBAMLRFDFactory3_MapLoadGroupToLoadCase(This,pModel,lgName,lgDesc,lcName)	\
    ( (This)->lpVtbl -> MapLoadGroupToLoadCase(This,pModel,lgName,lgDesc,lcName) ) 

#define ILBAMLRFDFactory3_CreateSelfWeightDeadLoad(This,pModel,stage,lgName,unitWgt,E)	\
    ( (This)->lpVtbl -> CreateSelfWeightDeadLoad(This,pModel,stage,lgName,unitWgt,E) ) 

#define ILBAMLRFDFactory3_GeneratePOIsOnSuperstructure(This,Model,startID,Increment,lastVal)	\
    ( (This)->lpVtbl -> GeneratePOIsOnSuperstructure(This,Model,startID,Increment,lastVal) ) 

#define ILBAMLRFDFactory3_GetSuperstructurePOIs(This,Model,PoiIDs,PoiLocations)	\
    ( (This)->lpVtbl -> GetSuperstructurePOIs(This,Model,PoiIDs,PoiLocations) ) 


#define ILBAMLRFDFactory3_ConfigureLiveLoad(This,pModel,includeLowBoy,units,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureLiveLoad(This,pModel,includeLowBoy,units,pUnitServer) ) 

#define ILBAMLRFDFactory3_ConfigureLoadCombinations(This,pModel)	\
    ( (This)->lpVtbl -> ConfigureLoadCombinations(This,pModel) ) 


#define ILBAMLRFDFactory3_ConfigureDesignLiveLoad(This,pModel,llmt,imTruck,imLane,includeDualTrucks,includeLowBoy,units,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureDesignLiveLoad(This,pModel,llmt,imTruck,imLane,includeDualTrucks,includeLowBoy,units,pUnitServer) ) 

#define ILBAMLRFDFactory3_ConfigureFatigueLiveLoad(This,pModel,llmt,imTruck,imLane,units,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureFatigueLiveLoad(This,pModel,llmt,imTruck,imLane,units,pUnitServer) ) 

#define ILBAMLRFDFactory3_ConfigureDeflectionLiveLoad(This,pModel,llmt,imTruck,imLane,units,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureDeflectionLiveLoad(This,pModel,llmt,imTruck,imLane,units,pUnitServer) ) 


#define ILBAMLRFDFactory3_ConfigureLegalLiveLoad(This,pModel,llmt,imTruck,imLane,includeType33,includeDualType33,removeLaneLoad,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureLegalLiveLoad(This,pModel,llmt,imTruck,imLane,includeType33,includeDualType33,removeLaneLoad,pUnitServer) ) 

#define ILBAMLRFDFactory3_ConfigureNotionalRatingLoad(This,pModel,llmt,imTruck,imLane,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureNotionalRatingLoad(This,pModel,llmt,imTruck,imLane,pUnitServer) ) 

#define ILBAMLRFDFactory3_ConfigureEmergencyRatingLoad(This,pModel,llmt,imTruck,imLane,bIncludeLaneLoad,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureEmergencyRatingLoad(This,pModel,llmt,imTruck,imLane,bIncludeLaneLoad,pUnitServer) ) 

#define ILBAMLRFDFactory3_ConfigureSpecializedHaulingUnits(This,pModel,llmt,imTruck,imLane,pUnitServer)	\
    ( (This)->lpVtbl -> ConfigureSpecializedHaulingUnits(This,pModel,llmt,imTruck,imLane,pUnitServer) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILBAMLRFDFactory3_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LRFDFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("12D5CC57-BF21-11D5-B075-00105A9AF985")
LRFDFactory;
#endif
#endif /* __WBFLLBAMUtility_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


