

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Nov 09 11:06:48 2018
 */
/* Compiler settings for ..\Include\WBFLCore.idl:
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


#ifndef __WBFLCore_h__
#define __WBFLCore_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBroker_FWD_DEFINED__
#define __IBroker_FWD_DEFINED__
typedef interface IBroker IBroker;

#endif 	/* __IBroker_FWD_DEFINED__ */


#ifndef __IProgress_FWD_DEFINED__
#define __IProgress_FWD_DEFINED__
typedef interface IProgress IProgress;

#endif 	/* __IProgress_FWD_DEFINED__ */


#ifndef __IAgent_FWD_DEFINED__
#define __IAgent_FWD_DEFINED__
typedef interface IAgent IAgent;

#endif 	/* __IAgent_FWD_DEFINED__ */


#ifndef __IAgentEx_FWD_DEFINED__
#define __IAgentEx_FWD_DEFINED__
typedef interface IAgentEx IAgentEx;

#endif 	/* __IAgentEx_FWD_DEFINED__ */


#ifndef __IAgentPersist_FWD_DEFINED__
#define __IAgentPersist_FWD_DEFINED__
typedef interface IAgentPersist IAgentPersist;

#endif 	/* __IAgentPersist_FWD_DEFINED__ */


#ifndef __IAgentUIIntegration_FWD_DEFINED__
#define __IAgentUIIntegration_FWD_DEFINED__
typedef interface IAgentUIIntegration IAgentUIIntegration;

#endif 	/* __IAgentUIIntegration_FWD_DEFINED__ */


#ifndef __IAgentReportingIntegration_FWD_DEFINED__
#define __IAgentReportingIntegration_FWD_DEFINED__
typedef interface IAgentReportingIntegration IAgentReportingIntegration;

#endif 	/* __IAgentReportingIntegration_FWD_DEFINED__ */


#ifndef __IAgentGraphingIntegration_FWD_DEFINED__
#define __IAgentGraphingIntegration_FWD_DEFINED__
typedef interface IAgentGraphingIntegration IAgentGraphingIntegration;

#endif 	/* __IAgentGraphingIntegration_FWD_DEFINED__ */


#ifndef __IAgentDocumentationIntegration_FWD_DEFINED__
#define __IAgentDocumentationIntegration_FWD_DEFINED__
typedef interface IAgentDocumentationIntegration IAgentDocumentationIntegration;

#endif 	/* __IAgentDocumentationIntegration_FWD_DEFINED__ */


#ifndef __IBrokerInit_FWD_DEFINED__
#define __IBrokerInit_FWD_DEFINED__
typedef interface IBrokerInit IBrokerInit;

#endif 	/* __IBrokerInit_FWD_DEFINED__ */


#ifndef __IBrokerInitEx_FWD_DEFINED__
#define __IBrokerInitEx_FWD_DEFINED__
typedef interface IBrokerInitEx IBrokerInitEx;

#endif 	/* __IBrokerInitEx_FWD_DEFINED__ */


#ifndef __IBrokerInit2_FWD_DEFINED__
#define __IBrokerInit2_FWD_DEFINED__
typedef interface IBrokerInit2 IBrokerInit2;

#endif 	/* __IBrokerInit2_FWD_DEFINED__ */


#ifndef __IBrokerInitEx2_FWD_DEFINED__
#define __IBrokerInitEx2_FWD_DEFINED__
typedef interface IBrokerInitEx2 IBrokerInitEx2;

#endif 	/* __IBrokerInitEx2_FWD_DEFINED__ */


#ifndef __IBrokerInitEx3_FWD_DEFINED__
#define __IBrokerInitEx3_FWD_DEFINED__
typedef interface IBrokerInitEx3 IBrokerInitEx3;

#endif 	/* __IBrokerInitEx3_FWD_DEFINED__ */


#ifndef __ICLSIDMap_FWD_DEFINED__
#define __ICLSIDMap_FWD_DEFINED__
typedef interface ICLSIDMap ICLSIDMap;

#endif 	/* __ICLSIDMap_FWD_DEFINED__ */


#ifndef __IBrokerPersist_FWD_DEFINED__
#define __IBrokerPersist_FWD_DEFINED__
typedef interface IBrokerPersist IBrokerPersist;

#endif 	/* __IBrokerPersist_FWD_DEFINED__ */


#ifndef __IBrokerPersist2_FWD_DEFINED__
#define __IBrokerPersist2_FWD_DEFINED__
typedef interface IBrokerPersist2 IBrokerPersist2;

#endif 	/* __IBrokerPersist2_FWD_DEFINED__ */


#ifndef __IManageAgents_FWD_DEFINED__
#define __IManageAgents_FWD_DEFINED__
typedef interface IManageAgents IManageAgents;

#endif 	/* __IManageAgents_FWD_DEFINED__ */


#ifndef __Broker_FWD_DEFINED__
#define __Broker_FWD_DEFINED__

#ifdef __cplusplus
typedef class Broker Broker;
#else
typedef struct Broker Broker;
#endif /* __cplusplus */

#endif 	/* __Broker_FWD_DEFINED__ */


#ifndef __Broker2_FWD_DEFINED__
#define __Broker2_FWD_DEFINED__

#ifdef __cplusplus
typedef class Broker2 Broker2;
#else
typedef struct Broker2 Broker2;
#endif /* __cplusplus */

#endif 	/* __Broker2_FWD_DEFINED__ */


#ifndef __SysAgent_FWD_DEFINED__
#define __SysAgent_FWD_DEFINED__

#ifdef __cplusplus
typedef class SysAgent SysAgent;
#else
typedef struct SysAgent SysAgent;
#endif /* __cplusplus */

#endif 	/* __SysAgent_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLCore_0000_0000 */
/* [local] */ 

/////////////////////////////////////////////////////////////////////////////
// IBroker, IBrokerInit, IBrokerPersist status codes
#define BROKER_E_FIRST    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x0200)
#define BROKER_E_LAST     MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x020F)

#define BROKER_E_LOADAGENT           (BROKER_E_FIRST+0)
// Error loading or initalizing an agent
#define BROKER_E_ADDAGENT            (BROKER_E_FIRST+1)
#define BROKER_E_INITAGENT           (BROKER_E_FIRST+2)
// Error loading adding an agent
/////////////////////////////////////////////////////////////////////////////
// IAgent, IAgentPersist, IAgentPersist2 status codes
#define AGENT_E_FIRST    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x0200)
#define AGENT_E_LAST     MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x020F)
#define AGENT_S_FIRST    MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 0x0200)
#define AGENT_S_LAST     MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 0x020F)
// Agent wants a second pass during initialization
#define AGENT_S_SECONDPASSINIT	(AGENT_S_FIRST+0)
// Agent must implement the IAgentEx interface
#define AGENT_E_NOTAGENTEX    	(AGENT_E_FIRST+0)
/////////////////////////////////////////////////////////////////////////////
// IProgress status codes
#define PROGRESS_E_FIRST    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x0200)
#define PROGRESS_E_LAST     MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x020F)

#define PROGRESS_E_CREATE           (PROGRESS_E_FIRST+0)
// Error creating progress window
// Progress Window Flags
#define PW_ALL        0x0000
#define PW_NOMESSAGE  0x0001
#define PW_NOGAUGE    0x0002
#define PW_NOCANCEL   0x0004


extern RPC_IF_HANDLE __MIDL_itf_WBFLCore_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLCore_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLCore_LIBRARY_DEFINED__
#define __WBFLCore_LIBRARY_DEFINED__

/* library WBFLCore */
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_WBFLCore;

#ifndef __IBroker_INTERFACE_DEFINED__
#define __IBroker_INTERFACE_DEFINED__

/* interface IBroker */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IBroker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C0E926D0-2620-11D2-8EB0-006097DF3C68")
    IBroker : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetInterface( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShutDown( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBrokerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBroker * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBroker * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBroker * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetInterface )( 
            IBroker * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown **ppUnk);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IBroker * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShutDown )( 
            IBroker * This);
        
        END_INTERFACE
    } IBrokerVtbl;

    interface IBroker
    {
        CONST_VTBL struct IBrokerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBroker_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBroker_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBroker_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBroker_GetInterface(This,riid,ppUnk)	\
    ( (This)->lpVtbl -> GetInterface(This,riid,ppUnk) ) 

#define IBroker_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IBroker_ShutDown(This)	\
    ( (This)->lpVtbl -> ShutDown(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBroker_INTERFACE_DEFINED__ */


#ifndef __IProgress_INTERFACE_DEFINED__
#define __IProgress_INTERFACE_DEFINED__

/* interface IProgress */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IProgress;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF34DB70-2BEF-11d2-8EB3-006097DF3C68")
    IProgress : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateProgressWindow( 
            /* [in] */ DWORD dwMask,
            /* [in] */ UINT nDelay) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ short begin,
            /* [in] */ short end,
            /* [in] */ short inc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Increment( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateMessage( 
            /* [in] */ LPCTSTR msg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Continue( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DestroyProgressWindow( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProgressVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProgress * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProgress * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProgress * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateProgressWindow )( 
            IProgress * This,
            /* [in] */ DWORD dwMask,
            /* [in] */ UINT nDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IProgress * This,
            /* [in] */ short begin,
            /* [in] */ short end,
            /* [in] */ short inc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Increment )( 
            IProgress * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateMessage )( 
            IProgress * This,
            /* [in] */ LPCTSTR msg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Continue )( 
            IProgress * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DestroyProgressWindow )( 
            IProgress * This);
        
        END_INTERFACE
    } IProgressVtbl;

    interface IProgress
    {
        CONST_VTBL struct IProgressVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProgress_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProgress_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProgress_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProgress_CreateProgressWindow(This,dwMask,nDelay)	\
    ( (This)->lpVtbl -> CreateProgressWindow(This,dwMask,nDelay) ) 

#define IProgress_Init(This,begin,end,inc)	\
    ( (This)->lpVtbl -> Init(This,begin,end,inc) ) 

#define IProgress_Increment(This)	\
    ( (This)->lpVtbl -> Increment(This) ) 

#define IProgress_UpdateMessage(This,msg)	\
    ( (This)->lpVtbl -> UpdateMessage(This,msg) ) 

#define IProgress_Continue(This)	\
    ( (This)->lpVtbl -> Continue(This) ) 

#define IProgress_DestroyProgressWindow(This)	\
    ( (This)->lpVtbl -> DestroyProgressWindow(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProgress_INTERFACE_DEFINED__ */


#ifndef __IAgent_INTERFACE_DEFINED__
#define __IAgent_INTERFACE_DEFINED__

/* interface IAgent */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IAgent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BD40316D-259A-11D2-8EB0-006097DF3C68")
    IAgent : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetBroker( 
            /* [in] */ IBroker *pBroker) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RegInterfaces( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShutDown( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAgentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAgent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAgent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAgent * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetBroker )( 
            IAgent * This,
            /* [in] */ IBroker *pBroker);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RegInterfaces )( 
            IAgent * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IAgent * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IAgent * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShutDown )( 
            IAgent * This);
        
        END_INTERFACE
    } IAgentVtbl;

    interface IAgent
    {
        CONST_VTBL struct IAgentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAgent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAgent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAgent_SetBroker(This,pBroker)	\
    ( (This)->lpVtbl -> SetBroker(This,pBroker) ) 

#define IAgent_RegInterfaces(This)	\
    ( (This)->lpVtbl -> RegInterfaces(This) ) 

#define IAgent_Init(This)	\
    ( (This)->lpVtbl -> Init(This) ) 

#define IAgent_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IAgent_ShutDown(This)	\
    ( (This)->lpVtbl -> ShutDown(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAgent_INTERFACE_DEFINED__ */


#ifndef __IAgentEx_INTERFACE_DEFINED__
#define __IAgentEx_INTERFACE_DEFINED__

/* interface IAgentEx */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IAgentEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0AE540FE-8525-4db3-BC36-31B90E74830B")
    IAgentEx : public IAgent
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init2( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClassID( 
            /* [out] */ CLSID *pCLSID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAgentExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAgentEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAgentEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAgentEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetBroker )( 
            IAgentEx * This,
            /* [in] */ IBroker *pBroker);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RegInterfaces )( 
            IAgentEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IAgentEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IAgentEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShutDown )( 
            IAgentEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init2 )( 
            IAgentEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetClassID )( 
            IAgentEx * This,
            /* [out] */ CLSID *pCLSID);
        
        END_INTERFACE
    } IAgentExVtbl;

    interface IAgentEx
    {
        CONST_VTBL struct IAgentExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAgentEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAgentEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAgentEx_SetBroker(This,pBroker)	\
    ( (This)->lpVtbl -> SetBroker(This,pBroker) ) 

#define IAgentEx_RegInterfaces(This)	\
    ( (This)->lpVtbl -> RegInterfaces(This) ) 

#define IAgentEx_Init(This)	\
    ( (This)->lpVtbl -> Init(This) ) 

#define IAgentEx_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IAgentEx_ShutDown(This)	\
    ( (This)->lpVtbl -> ShutDown(This) ) 


#define IAgentEx_Init2(This)	\
    ( (This)->lpVtbl -> Init2(This) ) 

#define IAgentEx_GetClassID(This,pCLSID)	\
    ( (This)->lpVtbl -> GetClassID(This,pCLSID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAgentEx_INTERFACE_DEFINED__ */


#ifndef __IAgentPersist_INTERFACE_DEFINED__
#define __IAgentPersist_INTERFACE_DEFINED__

/* interface IAgentPersist */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IAgentPersist;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E6268300-26FA-11d2-8EB0-006097DF3C68")
    IAgentPersist : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ IStructuredLoad *pStrLoad) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ IStructuredSave *pStrSave) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAgentPersistVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAgentPersist * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAgentPersist * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAgentPersist * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IAgentPersist * This,
            /* [in] */ IStructuredLoad *pStrLoad);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IAgentPersist * This,
            /* [in] */ IStructuredSave *pStrSave);
        
        END_INTERFACE
    } IAgentPersistVtbl;

    interface IAgentPersist
    {
        CONST_VTBL struct IAgentPersistVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentPersist_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAgentPersist_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAgentPersist_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAgentPersist_Load(This,pStrLoad)	\
    ( (This)->lpVtbl -> Load(This,pStrLoad) ) 

#define IAgentPersist_Save(This,pStrSave)	\
    ( (This)->lpVtbl -> Save(This,pStrSave) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAgentPersist_INTERFACE_DEFINED__ */


#ifndef __IAgentUIIntegration_INTERFACE_DEFINED__
#define __IAgentUIIntegration_INTERFACE_DEFINED__

/* interface IAgentUIIntegration */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IAgentUIIntegration;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("79B52B0A-B19B-4dc9-80B7-9EF36157A2B9")
    IAgentUIIntegration : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IntegrateWithUI( 
            BOOL bIntegrate) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAgentUIIntegrationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAgentUIIntegration * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAgentUIIntegration * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAgentUIIntegration * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IntegrateWithUI )( 
            IAgentUIIntegration * This,
            BOOL bIntegrate);
        
        END_INTERFACE
    } IAgentUIIntegrationVtbl;

    interface IAgentUIIntegration
    {
        CONST_VTBL struct IAgentUIIntegrationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentUIIntegration_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAgentUIIntegration_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAgentUIIntegration_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAgentUIIntegration_IntegrateWithUI(This,bIntegrate)	\
    ( (This)->lpVtbl -> IntegrateWithUI(This,bIntegrate) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAgentUIIntegration_INTERFACE_DEFINED__ */


#ifndef __IAgentReportingIntegration_INTERFACE_DEFINED__
#define __IAgentReportingIntegration_INTERFACE_DEFINED__

/* interface IAgentReportingIntegration */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IAgentReportingIntegration;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B03A0005-11F8-40c3-8D18-D94032886129")
    IAgentReportingIntegration : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IntegrateWithReporting( 
            BOOL bIntegrate) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAgentReportingIntegrationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAgentReportingIntegration * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAgentReportingIntegration * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAgentReportingIntegration * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IntegrateWithReporting )( 
            IAgentReportingIntegration * This,
            BOOL bIntegrate);
        
        END_INTERFACE
    } IAgentReportingIntegrationVtbl;

    interface IAgentReportingIntegration
    {
        CONST_VTBL struct IAgentReportingIntegrationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentReportingIntegration_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAgentReportingIntegration_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAgentReportingIntegration_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAgentReportingIntegration_IntegrateWithReporting(This,bIntegrate)	\
    ( (This)->lpVtbl -> IntegrateWithReporting(This,bIntegrate) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAgentReportingIntegration_INTERFACE_DEFINED__ */


#ifndef __IAgentGraphingIntegration_INTERFACE_DEFINED__
#define __IAgentGraphingIntegration_INTERFACE_DEFINED__

/* interface IAgentGraphingIntegration */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IAgentGraphingIntegration;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9AF52AB6-BECA-4aa4-8242-C7910B11AA08")
    IAgentGraphingIntegration : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IntegrateWithGraphing( 
            BOOL bIntegrate) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAgentGraphingIntegrationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAgentGraphingIntegration * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAgentGraphingIntegration * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAgentGraphingIntegration * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IntegrateWithGraphing )( 
            IAgentGraphingIntegration * This,
            BOOL bIntegrate);
        
        END_INTERFACE
    } IAgentGraphingIntegrationVtbl;

    interface IAgentGraphingIntegration
    {
        CONST_VTBL struct IAgentGraphingIntegrationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentGraphingIntegration_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAgentGraphingIntegration_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAgentGraphingIntegration_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAgentGraphingIntegration_IntegrateWithGraphing(This,bIntegrate)	\
    ( (This)->lpVtbl -> IntegrateWithGraphing(This,bIntegrate) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAgentGraphingIntegration_INTERFACE_DEFINED__ */


#ifndef __IAgentDocumentationIntegration_INTERFACE_DEFINED__
#define __IAgentDocumentationIntegration_INTERFACE_DEFINED__

/* interface IAgentDocumentationIntegration */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IAgentDocumentationIntegration;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("369EE64B-5135-4b0a-95F3-C3B001A39D6F")
    IAgentDocumentationIntegration : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDocumentationSetName( 
            BSTR *pbstrName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadDocumentationMap( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDocumentLocation( 
            UINT nHID,
            BSTR *pbstrURL) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAgentDocumentationIntegrationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAgentDocumentationIntegration * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAgentDocumentationIntegration * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAgentDocumentationIntegration * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDocumentationSetName )( 
            IAgentDocumentationIntegration * This,
            BSTR *pbstrName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadDocumentationMap )( 
            IAgentDocumentationIntegration * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDocumentLocation )( 
            IAgentDocumentationIntegration * This,
            UINT nHID,
            BSTR *pbstrURL);
        
        END_INTERFACE
    } IAgentDocumentationIntegrationVtbl;

    interface IAgentDocumentationIntegration
    {
        CONST_VTBL struct IAgentDocumentationIntegrationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentDocumentationIntegration_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAgentDocumentationIntegration_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAgentDocumentationIntegration_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAgentDocumentationIntegration_GetDocumentationSetName(This,pbstrName)	\
    ( (This)->lpVtbl -> GetDocumentationSetName(This,pbstrName) ) 

#define IAgentDocumentationIntegration_LoadDocumentationMap(This)	\
    ( (This)->lpVtbl -> LoadDocumentationMap(This) ) 

#define IAgentDocumentationIntegration_GetDocumentLocation(This,nHID,pbstrURL)	\
    ( (This)->lpVtbl -> GetDocumentLocation(This,nHID,pbstrURL) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAgentDocumentationIntegration_INTERFACE_DEFINED__ */


#ifndef __IBrokerInit_INTERFACE_DEFINED__
#define __IBrokerInit_INTERFACE_DEFINED__

/* interface IBrokerInit */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IBrokerInit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("53CAB1E0-262E-11d2-8EB0-006097DF3C68")
    IBrokerInit : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadAgents( 
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IndexType *lErrIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddAgent( 
            /* [in] */ IAgent *pAgent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindConnectionPoint( 
            /* [in] */ REFIID riid,
            /* [out] */ IConnectionPoint **ppCP) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RegInterface( 
            /* [in] */ REFIID riid,
            /* [in] */ IAgent *pAgent) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBrokerInitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrokerInit * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrokerInit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrokerInit * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadAgents )( 
            IBrokerInit * This,
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IndexType *lErrIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddAgent )( 
            IBrokerInit * This,
            /* [in] */ IAgent *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindConnectionPoint )( 
            IBrokerInit * This,
            /* [in] */ REFIID riid,
            /* [out] */ IConnectionPoint **ppCP);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RegInterface )( 
            IBrokerInit * This,
            /* [in] */ REFIID riid,
            /* [in] */ IAgent *pAgent);
        
        END_INTERFACE
    } IBrokerInitVtbl;

    interface IBrokerInit
    {
        CONST_VTBL struct IBrokerInitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrokerInit_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBrokerInit_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBrokerInit_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBrokerInit_LoadAgents(This,pClsid,nClsid,lErrIndex)	\
    ( (This)->lpVtbl -> LoadAgents(This,pClsid,nClsid,lErrIndex) ) 

#define IBrokerInit_AddAgent(This,pAgent)	\
    ( (This)->lpVtbl -> AddAgent(This,pAgent) ) 

#define IBrokerInit_FindConnectionPoint(This,riid,ppCP)	\
    ( (This)->lpVtbl -> FindConnectionPoint(This,riid,ppCP) ) 

#define IBrokerInit_RegInterface(This,riid,pAgent)	\
    ( (This)->lpVtbl -> RegInterface(This,riid,pAgent) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBrokerInit_INTERFACE_DEFINED__ */


#ifndef __IBrokerInitEx_INTERFACE_DEFINED__
#define __IBrokerInitEx_INTERFACE_DEFINED__

/* interface IBrokerInitEx */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IBrokerInitEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("673DC477-468D-4466-98AA-53EE7A0EECA5")
    IBrokerInitEx : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadAgents( 
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IIndexArray **lErrIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadExtensionAgents( 
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IIndexArray **lErrIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddAgent( 
            /* [in] */ IAgentEx *pAgent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddExtensionAgent( 
            /* [in] */ IAgentEx *pAgent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindConnectionPoint( 
            /* [in] */ REFIID riid,
            /* [out] */ IConnectionPoint **ppCP) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RegInterface( 
            /* [in] */ REFIID riid,
            /* [in] */ IAgentEx *pAgent) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBrokerInitExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrokerInitEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrokerInitEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrokerInitEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadAgents )( 
            IBrokerInitEx * This,
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IIndexArray **lErrIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadExtensionAgents )( 
            IBrokerInitEx * This,
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IIndexArray **lErrIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddAgent )( 
            IBrokerInitEx * This,
            /* [in] */ IAgentEx *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddExtensionAgent )( 
            IBrokerInitEx * This,
            /* [in] */ IAgentEx *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindConnectionPoint )( 
            IBrokerInitEx * This,
            /* [in] */ REFIID riid,
            /* [out] */ IConnectionPoint **ppCP);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RegInterface )( 
            IBrokerInitEx * This,
            /* [in] */ REFIID riid,
            /* [in] */ IAgentEx *pAgent);
        
        END_INTERFACE
    } IBrokerInitExVtbl;

    interface IBrokerInitEx
    {
        CONST_VTBL struct IBrokerInitExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrokerInitEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBrokerInitEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBrokerInitEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBrokerInitEx_LoadAgents(This,pClsid,nClsid,lErrIndex)	\
    ( (This)->lpVtbl -> LoadAgents(This,pClsid,nClsid,lErrIndex) ) 

#define IBrokerInitEx_LoadExtensionAgents(This,pClsid,nClsid,lErrIndex)	\
    ( (This)->lpVtbl -> LoadExtensionAgents(This,pClsid,nClsid,lErrIndex) ) 

#define IBrokerInitEx_AddAgent(This,pAgent)	\
    ( (This)->lpVtbl -> AddAgent(This,pAgent) ) 

#define IBrokerInitEx_AddExtensionAgent(This,pAgent)	\
    ( (This)->lpVtbl -> AddExtensionAgent(This,pAgent) ) 

#define IBrokerInitEx_FindConnectionPoint(This,riid,ppCP)	\
    ( (This)->lpVtbl -> FindConnectionPoint(This,riid,ppCP) ) 

#define IBrokerInitEx_RegInterface(This,riid,pAgent)	\
    ( (This)->lpVtbl -> RegInterface(This,riid,pAgent) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBrokerInitEx_INTERFACE_DEFINED__ */


#ifndef __IBrokerInit2_INTERFACE_DEFINED__
#define __IBrokerInit2_INTERFACE_DEFINED__

/* interface IBrokerInit2 */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IBrokerInit2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7E70337A-DED7-43ae-936F-824EB1127012")
    IBrokerInit2 : public IBrokerInit
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DelayInit( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitAgents( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBrokerInit2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrokerInit2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrokerInit2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrokerInit2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadAgents )( 
            IBrokerInit2 * This,
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IndexType *lErrIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddAgent )( 
            IBrokerInit2 * This,
            /* [in] */ IAgent *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindConnectionPoint )( 
            IBrokerInit2 * This,
            /* [in] */ REFIID riid,
            /* [out] */ IConnectionPoint **ppCP);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RegInterface )( 
            IBrokerInit2 * This,
            /* [in] */ REFIID riid,
            /* [in] */ IAgent *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DelayInit )( 
            IBrokerInit2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitAgents )( 
            IBrokerInit2 * This);
        
        END_INTERFACE
    } IBrokerInit2Vtbl;

    interface IBrokerInit2
    {
        CONST_VTBL struct IBrokerInit2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrokerInit2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBrokerInit2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBrokerInit2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBrokerInit2_LoadAgents(This,pClsid,nClsid,lErrIndex)	\
    ( (This)->lpVtbl -> LoadAgents(This,pClsid,nClsid,lErrIndex) ) 

#define IBrokerInit2_AddAgent(This,pAgent)	\
    ( (This)->lpVtbl -> AddAgent(This,pAgent) ) 

#define IBrokerInit2_FindConnectionPoint(This,riid,ppCP)	\
    ( (This)->lpVtbl -> FindConnectionPoint(This,riid,ppCP) ) 

#define IBrokerInit2_RegInterface(This,riid,pAgent)	\
    ( (This)->lpVtbl -> RegInterface(This,riid,pAgent) ) 


#define IBrokerInit2_DelayInit(This)	\
    ( (This)->lpVtbl -> DelayInit(This) ) 

#define IBrokerInit2_InitAgents(This)	\
    ( (This)->lpVtbl -> InitAgents(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBrokerInit2_INTERFACE_DEFINED__ */


#ifndef __IBrokerInitEx2_INTERFACE_DEFINED__
#define __IBrokerInitEx2_INTERFACE_DEFINED__

/* interface IBrokerInitEx2 */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IBrokerInitEx2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F4A9DD8F-273D-4ae6-B044-AC9DEAFD43D4")
    IBrokerInitEx2 : public IBrokerInitEx
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DelayInit( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitAgents( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBrokerInitEx2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrokerInitEx2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrokerInitEx2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrokerInitEx2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadAgents )( 
            IBrokerInitEx2 * This,
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IIndexArray **lErrIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadExtensionAgents )( 
            IBrokerInitEx2 * This,
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IIndexArray **lErrIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddAgent )( 
            IBrokerInitEx2 * This,
            /* [in] */ IAgentEx *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddExtensionAgent )( 
            IBrokerInitEx2 * This,
            /* [in] */ IAgentEx *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindConnectionPoint )( 
            IBrokerInitEx2 * This,
            /* [in] */ REFIID riid,
            /* [out] */ IConnectionPoint **ppCP);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RegInterface )( 
            IBrokerInitEx2 * This,
            /* [in] */ REFIID riid,
            /* [in] */ IAgentEx *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DelayInit )( 
            IBrokerInitEx2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitAgents )( 
            IBrokerInitEx2 * This);
        
        END_INTERFACE
    } IBrokerInitEx2Vtbl;

    interface IBrokerInitEx2
    {
        CONST_VTBL struct IBrokerInitEx2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrokerInitEx2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBrokerInitEx2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBrokerInitEx2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBrokerInitEx2_LoadAgents(This,pClsid,nClsid,lErrIndex)	\
    ( (This)->lpVtbl -> LoadAgents(This,pClsid,nClsid,lErrIndex) ) 

#define IBrokerInitEx2_LoadExtensionAgents(This,pClsid,nClsid,lErrIndex)	\
    ( (This)->lpVtbl -> LoadExtensionAgents(This,pClsid,nClsid,lErrIndex) ) 

#define IBrokerInitEx2_AddAgent(This,pAgent)	\
    ( (This)->lpVtbl -> AddAgent(This,pAgent) ) 

#define IBrokerInitEx2_AddExtensionAgent(This,pAgent)	\
    ( (This)->lpVtbl -> AddExtensionAgent(This,pAgent) ) 

#define IBrokerInitEx2_FindConnectionPoint(This,riid,ppCP)	\
    ( (This)->lpVtbl -> FindConnectionPoint(This,riid,ppCP) ) 

#define IBrokerInitEx2_RegInterface(This,riid,pAgent)	\
    ( (This)->lpVtbl -> RegInterface(This,riid,pAgent) ) 


#define IBrokerInitEx2_DelayInit(This)	\
    ( (This)->lpVtbl -> DelayInit(This) ) 

#define IBrokerInitEx2_InitAgents(This)	\
    ( (This)->lpVtbl -> InitAgents(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBrokerInitEx2_INTERFACE_DEFINED__ */


#ifndef __IBrokerInitEx3_INTERFACE_DEFINED__
#define __IBrokerInitEx3_INTERFACE_DEFINED__

/* interface IBrokerInitEx3 */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IBrokerInitEx3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("94B63C86-A159-4330-80AA-D16618A7FFCB")
    IBrokerInitEx3 : public IBrokerInitEx2
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Integrate( 
            BOOL bIntegrateWithUI,
            BOOL bIntegrateWithReporting,
            BOOL bIntegrateWithGraphing,
            BOOL bIntegrateWithDocumentation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveIntegration( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBrokerInitEx3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrokerInitEx3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrokerInitEx3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrokerInitEx3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadAgents )( 
            IBrokerInitEx3 * This,
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IIndexArray **lErrIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadExtensionAgents )( 
            IBrokerInitEx3 * This,
            /* [in] */ CLSID *pClsid,
            /* [in] */ IndexType nClsid,
            /* [out] */ IIndexArray **lErrIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddAgent )( 
            IBrokerInitEx3 * This,
            /* [in] */ IAgentEx *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddExtensionAgent )( 
            IBrokerInitEx3 * This,
            /* [in] */ IAgentEx *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindConnectionPoint )( 
            IBrokerInitEx3 * This,
            /* [in] */ REFIID riid,
            /* [out] */ IConnectionPoint **ppCP);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RegInterface )( 
            IBrokerInitEx3 * This,
            /* [in] */ REFIID riid,
            /* [in] */ IAgentEx *pAgent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DelayInit )( 
            IBrokerInitEx3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitAgents )( 
            IBrokerInitEx3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Integrate )( 
            IBrokerInitEx3 * This,
            BOOL bIntegrateWithUI,
            BOOL bIntegrateWithReporting,
            BOOL bIntegrateWithGraphing,
            BOOL bIntegrateWithDocumentation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveIntegration )( 
            IBrokerInitEx3 * This);
        
        END_INTERFACE
    } IBrokerInitEx3Vtbl;

    interface IBrokerInitEx3
    {
        CONST_VTBL struct IBrokerInitEx3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrokerInitEx3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBrokerInitEx3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBrokerInitEx3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBrokerInitEx3_LoadAgents(This,pClsid,nClsid,lErrIndex)	\
    ( (This)->lpVtbl -> LoadAgents(This,pClsid,nClsid,lErrIndex) ) 

#define IBrokerInitEx3_LoadExtensionAgents(This,pClsid,nClsid,lErrIndex)	\
    ( (This)->lpVtbl -> LoadExtensionAgents(This,pClsid,nClsid,lErrIndex) ) 

#define IBrokerInitEx3_AddAgent(This,pAgent)	\
    ( (This)->lpVtbl -> AddAgent(This,pAgent) ) 

#define IBrokerInitEx3_AddExtensionAgent(This,pAgent)	\
    ( (This)->lpVtbl -> AddExtensionAgent(This,pAgent) ) 

#define IBrokerInitEx3_FindConnectionPoint(This,riid,ppCP)	\
    ( (This)->lpVtbl -> FindConnectionPoint(This,riid,ppCP) ) 

#define IBrokerInitEx3_RegInterface(This,riid,pAgent)	\
    ( (This)->lpVtbl -> RegInterface(This,riid,pAgent) ) 


#define IBrokerInitEx3_DelayInit(This)	\
    ( (This)->lpVtbl -> DelayInit(This) ) 

#define IBrokerInitEx3_InitAgents(This)	\
    ( (This)->lpVtbl -> InitAgents(This) ) 


#define IBrokerInitEx3_Integrate(This,bIntegrateWithUI,bIntegrateWithReporting,bIntegrateWithGraphing,bIntegrateWithDocumentation)	\
    ( (This)->lpVtbl -> Integrate(This,bIntegrateWithUI,bIntegrateWithReporting,bIntegrateWithGraphing,bIntegrateWithDocumentation) ) 

#define IBrokerInitEx3_RemoveIntegration(This)	\
    ( (This)->lpVtbl -> RemoveIntegration(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBrokerInitEx3_INTERFACE_DEFINED__ */


#ifndef __ICLSIDMap_INTERFACE_DEFINED__
#define __ICLSIDMap_INTERFACE_DEFINED__

/* interface ICLSIDMap */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_ICLSIDMap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1ED36EAA-D850-424c-96D6-3A993DB5EECF")
    ICLSIDMap : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddCLSID( 
            BSTR bstrOldCLSID,
            BSTR bstrNewCLSID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICLSIDMapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICLSIDMap * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICLSIDMap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICLSIDMap * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddCLSID )( 
            ICLSIDMap * This,
            BSTR bstrOldCLSID,
            BSTR bstrNewCLSID);
        
        END_INTERFACE
    } ICLSIDMapVtbl;

    interface ICLSIDMap
    {
        CONST_VTBL struct ICLSIDMapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICLSIDMap_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICLSIDMap_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICLSIDMap_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICLSIDMap_AddCLSID(This,bstrOldCLSID,bstrNewCLSID)	\
    ( (This)->lpVtbl -> AddCLSID(This,bstrOldCLSID,bstrNewCLSID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICLSIDMap_INTERFACE_DEFINED__ */


#ifndef __IBrokerPersist_INTERFACE_DEFINED__
#define __IBrokerPersist_INTERFACE_DEFINED__

/* interface IBrokerPersist */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IBrokerPersist;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E6268301-26FA-11d2-8EB0-006097DF3C68")
    IBrokerPersist : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ IStructuredLoad *pStrLoad) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ IStructuredSave *pStrSave) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBrokerPersistVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrokerPersist * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrokerPersist * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrokerPersist * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IBrokerPersist * This,
            /* [in] */ IStructuredLoad *pStrLoad);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IBrokerPersist * This,
            /* [in] */ IStructuredSave *pStrSave);
        
        END_INTERFACE
    } IBrokerPersistVtbl;

    interface IBrokerPersist
    {
        CONST_VTBL struct IBrokerPersistVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrokerPersist_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBrokerPersist_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBrokerPersist_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBrokerPersist_Load(This,pStrLoad)	\
    ( (This)->lpVtbl -> Load(This,pStrLoad) ) 

#define IBrokerPersist_Save(This,pStrSave)	\
    ( (This)->lpVtbl -> Save(This,pStrSave) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBrokerPersist_INTERFACE_DEFINED__ */


#ifndef __IBrokerPersist2_INTERFACE_DEFINED__
#define __IBrokerPersist2_INTERFACE_DEFINED__

/* interface IBrokerPersist2 */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IBrokerPersist2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2D663F88-1B17-4d1b-9DE8-8CD06050E2C2")
    IBrokerPersist2 : public IBrokerPersist
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSaveMissingAgentDataFlag( 
            /* [in] */ VARIANT_BOOL bSetFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSaveMissingAgentDataFlag( 
            /* [out] */ VARIANT_BOOL *bFlag) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBrokerPersist2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrokerPersist2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrokerPersist2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrokerPersist2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IBrokerPersist2 * This,
            /* [in] */ IStructuredLoad *pStrLoad);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IBrokerPersist2 * This,
            /* [in] */ IStructuredSave *pStrSave);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetSaveMissingAgentDataFlag )( 
            IBrokerPersist2 * This,
            /* [in] */ VARIANT_BOOL bSetFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSaveMissingAgentDataFlag )( 
            IBrokerPersist2 * This,
            /* [out] */ VARIANT_BOOL *bFlag);
        
        END_INTERFACE
    } IBrokerPersist2Vtbl;

    interface IBrokerPersist2
    {
        CONST_VTBL struct IBrokerPersist2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrokerPersist2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBrokerPersist2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBrokerPersist2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBrokerPersist2_Load(This,pStrLoad)	\
    ( (This)->lpVtbl -> Load(This,pStrLoad) ) 

#define IBrokerPersist2_Save(This,pStrSave)	\
    ( (This)->lpVtbl -> Save(This,pStrSave) ) 


#define IBrokerPersist2_SetSaveMissingAgentDataFlag(This,bSetFlag)	\
    ( (This)->lpVtbl -> SetSaveMissingAgentDataFlag(This,bSetFlag) ) 

#define IBrokerPersist2_GetSaveMissingAgentDataFlag(This,bFlag)	\
    ( (This)->lpVtbl -> GetSaveMissingAgentDataFlag(This,bFlag) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBrokerPersist2_INTERFACE_DEFINED__ */


#ifndef __IManageAgents_INTERFACE_DEFINED__
#define __IManageAgents_INTERFACE_DEFINED__

/* interface IManageAgents */
/* [object][unique][uuid] */ 


EXTERN_C const IID IID_IManageAgents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("57EC999E-BCC8-4227-B415-AE9537668173")
    IManageAgents : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AgentCount( 
            /* [retval][out] */ CollectionIndexType *nAgents) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Agent( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IAgent **ppAgent) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ExtensionAgentCount( 
            /* [retval][out] */ CollectionIndexType *nAgents) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ExtensionAgent( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IAgent **ppAgent) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IManageAgentsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IManageAgents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IManageAgents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IManageAgents * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AgentCount )( 
            IManageAgents * This,
            /* [retval][out] */ CollectionIndexType *nAgents);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Agent )( 
            IManageAgents * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IAgent **ppAgent);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExtensionAgentCount )( 
            IManageAgents * This,
            /* [retval][out] */ CollectionIndexType *nAgents);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExtensionAgent )( 
            IManageAgents * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IAgent **ppAgent);
        
        END_INTERFACE
    } IManageAgentsVtbl;

    interface IManageAgents
    {
        CONST_VTBL struct IManageAgentsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IManageAgents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IManageAgents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IManageAgents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IManageAgents_get_AgentCount(This,nAgents)	\
    ( (This)->lpVtbl -> get_AgentCount(This,nAgents) ) 

#define IManageAgents_get_Agent(This,idx,ppAgent)	\
    ( (This)->lpVtbl -> get_Agent(This,idx,ppAgent) ) 

#define IManageAgents_get_ExtensionAgentCount(This,nAgents)	\
    ( (This)->lpVtbl -> get_ExtensionAgentCount(This,nAgents) ) 

#define IManageAgents_get_ExtensionAgent(This,idx,ppAgent)	\
    ( (This)->lpVtbl -> get_ExtensionAgent(This,idx,ppAgent) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IManageAgents_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Broker;

#ifdef __cplusplus

class DECLSPEC_UUID("C0E926D1-2620-11D2-8EB0-006097DF3C68")
Broker;
#endif

EXTERN_C const CLSID CLSID_Broker2;

#ifdef __cplusplus

class DECLSPEC_UUID("CF37B1E5-F9B8-4e78-B8B3-B91E326131CD")
Broker2;
#endif

EXTERN_C const CLSID CLSID_SysAgent;

#ifdef __cplusplus

class DECLSPEC_UUID("D71212B0-2BEF-11d2-8EB3-006097DF3C68")
SysAgent;
#endif
#endif /* __WBFLCore_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


