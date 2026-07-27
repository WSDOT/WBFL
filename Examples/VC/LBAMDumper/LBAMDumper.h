

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for LBAMDumper.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __LBAMDumper_h__
#define __LBAMDumper_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __ILBAMResponseDumper_FWD_DEFINED__
#define __ILBAMResponseDumper_FWD_DEFINED__
typedef interface ILBAMResponseDumper ILBAMResponseDumper;

#endif 	/* __ILBAMResponseDumper_FWD_DEFINED__ */


#ifndef __LBAMResponseDumper_FWD_DEFINED__
#define __LBAMResponseDumper_FWD_DEFINED__

#ifdef __cplusplus
typedef class LBAMResponseDumper LBAMResponseDumper;
#else
typedef struct LBAMResponseDumper LBAMResponseDumper;
#endif /* __cplusplus */

#endif 	/* __LBAMResponseDumper_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLLBAMAnalysisUtility.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WBFLLBAMDumper_LIBRARY_DEFINED__
#define __WBFLLBAMDumper_LIBRARY_DEFINED__

/* library WBFLLBAMDumper */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WBFLLBAMDumper;

#ifndef __ILBAMResponseDumper_INTERFACE_DEFINED__
#define __ILBAMResponseDumper_INTERFACE_DEFINED__

/* interface ILBAMResponseDumper */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILBAMResponseDumper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2596FCA6-D3A3-49CC-AB8D-79522FC0D360")
    ILBAMResponseDumper : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Dump( 
            /* [in] */ ILBAMAnalysisEngine *engine,
            /* [in] */ BSTR dumpFileName,
            /* [in] */ BSTR detailsFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DumpModel( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DumpModel( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DumpLoadGroupResponse( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DumpLoadGroupResponse( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DumpInfluenceLines( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DumpInfluenceLines( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DumpContraflexure( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DumpContraflexure( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DumpEnvelopedVehicularResponse( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DumpEnvelopedVehicularResponse( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DumpLiveLoadModelResponse( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DumpLiveLoadModelResponse( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DumpLoadCaseResponse( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DumpLoadCaseResponse( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DumpLoadCombinationResponse( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DumpLoadCombinationResponse( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILBAMResponseDumperVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILBAMResponseDumper * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILBAMResponseDumper * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILBAMResponseDumper * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILBAMResponseDumper * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILBAMResponseDumper * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILBAMResponseDumper * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILBAMResponseDumper * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, Dump)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Dump )( 
            ILBAMResponseDumper * This,
            /* [in] */ ILBAMAnalysisEngine *engine,
            /* [in] */ BSTR dumpFileName,
            /* [in] */ BSTR detailsFileName);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, get_DumpModel)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DumpModel )( 
            ILBAMResponseDumper * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, put_DumpModel)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DumpModel )( 
            ILBAMResponseDumper * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, get_DumpLoadGroupResponse)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DumpLoadGroupResponse )( 
            ILBAMResponseDumper * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, put_DumpLoadGroupResponse)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DumpLoadGroupResponse )( 
            ILBAMResponseDumper * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, get_DumpInfluenceLines)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DumpInfluenceLines )( 
            ILBAMResponseDumper * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, put_DumpInfluenceLines)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DumpInfluenceLines )( 
            ILBAMResponseDumper * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, get_DumpContraflexure)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DumpContraflexure )( 
            ILBAMResponseDumper * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, put_DumpContraflexure)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DumpContraflexure )( 
            ILBAMResponseDumper * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, get_DumpEnvelopedVehicularResponse)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DumpEnvelopedVehicularResponse )( 
            ILBAMResponseDumper * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, put_DumpEnvelopedVehicularResponse)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DumpEnvelopedVehicularResponse )( 
            ILBAMResponseDumper * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, get_DumpLiveLoadModelResponse)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DumpLiveLoadModelResponse )( 
            ILBAMResponseDumper * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, put_DumpLiveLoadModelResponse)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DumpLiveLoadModelResponse )( 
            ILBAMResponseDumper * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, get_DumpLoadCaseResponse)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DumpLoadCaseResponse )( 
            ILBAMResponseDumper * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, put_DumpLoadCaseResponse)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DumpLoadCaseResponse )( 
            ILBAMResponseDumper * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, get_DumpLoadCombinationResponse)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DumpLoadCombinationResponse )( 
            ILBAMResponseDumper * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        DECLSPEC_XFGVIRT(ILBAMResponseDumper, put_DumpLoadCombinationResponse)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DumpLoadCombinationResponse )( 
            ILBAMResponseDumper * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } ILBAMResponseDumperVtbl;

    interface ILBAMResponseDumper
    {
        CONST_VTBL struct ILBAMResponseDumperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILBAMResponseDumper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILBAMResponseDumper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILBAMResponseDumper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILBAMResponseDumper_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILBAMResponseDumper_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILBAMResponseDumper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILBAMResponseDumper_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ILBAMResponseDumper_Dump(This,engine,dumpFileName,detailsFileName)	\
    ( (This)->lpVtbl -> Dump(This,engine,dumpFileName,detailsFileName) ) 

#define ILBAMResponseDumper_get_DumpModel(This,pVal)	\
    ( (This)->lpVtbl -> get_DumpModel(This,pVal) ) 

#define ILBAMResponseDumper_put_DumpModel(This,newVal)	\
    ( (This)->lpVtbl -> put_DumpModel(This,newVal) ) 

#define ILBAMResponseDumper_get_DumpLoadGroupResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_DumpLoadGroupResponse(This,pVal) ) 

#define ILBAMResponseDumper_put_DumpLoadGroupResponse(This,newVal)	\
    ( (This)->lpVtbl -> put_DumpLoadGroupResponse(This,newVal) ) 

#define ILBAMResponseDumper_get_DumpInfluenceLines(This,pVal)	\
    ( (This)->lpVtbl -> get_DumpInfluenceLines(This,pVal) ) 

#define ILBAMResponseDumper_put_DumpInfluenceLines(This,newVal)	\
    ( (This)->lpVtbl -> put_DumpInfluenceLines(This,newVal) ) 

#define ILBAMResponseDumper_get_DumpContraflexure(This,pVal)	\
    ( (This)->lpVtbl -> get_DumpContraflexure(This,pVal) ) 

#define ILBAMResponseDumper_put_DumpContraflexure(This,newVal)	\
    ( (This)->lpVtbl -> put_DumpContraflexure(This,newVal) ) 

#define ILBAMResponseDumper_get_DumpEnvelopedVehicularResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_DumpEnvelopedVehicularResponse(This,pVal) ) 

#define ILBAMResponseDumper_put_DumpEnvelopedVehicularResponse(This,newVal)	\
    ( (This)->lpVtbl -> put_DumpEnvelopedVehicularResponse(This,newVal) ) 

#define ILBAMResponseDumper_get_DumpLiveLoadModelResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_DumpLiveLoadModelResponse(This,pVal) ) 

#define ILBAMResponseDumper_put_DumpLiveLoadModelResponse(This,newVal)	\
    ( (This)->lpVtbl -> put_DumpLiveLoadModelResponse(This,newVal) ) 

#define ILBAMResponseDumper_get_DumpLoadCaseResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_DumpLoadCaseResponse(This,pVal) ) 

#define ILBAMResponseDumper_put_DumpLoadCaseResponse(This,newVal)	\
    ( (This)->lpVtbl -> put_DumpLoadCaseResponse(This,newVal) ) 

#define ILBAMResponseDumper_get_DumpLoadCombinationResponse(This,pVal)	\
    ( (This)->lpVtbl -> get_DumpLoadCombinationResponse(This,pVal) ) 

#define ILBAMResponseDumper_put_DumpLoadCombinationResponse(This,newVal)	\
    ( (This)->lpVtbl -> put_DumpLoadCombinationResponse(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILBAMResponseDumper_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LBAMResponseDumper;

#ifdef __cplusplus

class DECLSPEC_UUID("0F4EB9EE-1F5C-4460-BE11-53C71F8645FE")
LBAMResponseDumper;
#endif
#endif /* __WBFLLBAMDumper_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


