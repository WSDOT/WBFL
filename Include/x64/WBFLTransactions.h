

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:23:24 2017
 */
/* Compiler settings for ..\Include\WBFLTransactions.idl:
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


#ifndef __WBFLTransactions_h__
#define __WBFLTransactions_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWBFLTransaction_FWD_DEFINED__
#define __IWBFLTransaction_FWD_DEFINED__
typedef interface IWBFLTransaction IWBFLTransaction;

#endif 	/* __IWBFLTransaction_FWD_DEFINED__ */


#ifndef __IWBFLMacroTransaction_FWD_DEFINED__
#define __IWBFLMacroTransaction_FWD_DEFINED__
typedef interface IWBFLMacroTransaction IWBFLMacroTransaction;

#endif 	/* __IWBFLMacroTransaction_FWD_DEFINED__ */


#ifndef __IWBFLMacroAdapter_FWD_DEFINED__
#define __IWBFLMacroAdapter_FWD_DEFINED__
typedef interface IWBFLMacroAdapter IWBFLMacroAdapter;

#endif 	/* __IWBFLMacroAdapter_FWD_DEFINED__ */


#ifndef __IWBFLTransactionMgr_FWD_DEFINED__
#define __IWBFLTransactionMgr_FWD_DEFINED__
typedef interface IWBFLTransactionMgr IWBFLTransactionMgr;

#endif 	/* __IWBFLTransactionMgr_FWD_DEFINED__ */


#ifndef __IWBFLSupportTransactions_FWD_DEFINED__
#define __IWBFLSupportTransactions_FWD_DEFINED__
typedef interface IWBFLSupportTransactions IWBFLSupportTransactions;

#endif 	/* __IWBFLSupportTransactions_FWD_DEFINED__ */


#ifndef __WBFLTransactionMgr_FWD_DEFINED__
#define __WBFLTransactionMgr_FWD_DEFINED__

#ifdef __cplusplus
typedef class WBFLTransactionMgr WBFLTransactionMgr;
#else
typedef struct WBFLTransactionMgr WBFLTransactionMgr;
#endif /* __cplusplus */

#endif 	/* __WBFLTransactionMgr_FWD_DEFINED__ */


#ifndef __WBFLMacroTransaction_FWD_DEFINED__
#define __WBFLMacroTransaction_FWD_DEFINED__

#ifdef __cplusplus
typedef class WBFLMacroTransaction WBFLMacroTransaction;
#else
typedef struct WBFLMacroTransaction WBFLMacroTransaction;
#endif /* __cplusplus */

#endif 	/* __WBFLMacroTransaction_FWD_DEFINED__ */


#ifndef __WBFLMacroAdapter_FWD_DEFINED__
#define __WBFLMacroAdapter_FWD_DEFINED__

#ifdef __cplusplus
typedef class WBFLMacroAdapter WBFLMacroAdapter;
#else
typedef struct WBFLMacroAdapter WBFLMacroAdapter;
#endif /* __cplusplus */

#endif 	/* __WBFLMacroAdapter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WBFLTransactions_LIBRARY_DEFINED__
#define __WBFLTransactions_LIBRARY_DEFINED__

/* library WBFLTransactions */
/* [helpstring][version][uuid] */ 

typedef /* [public][public][uuid][helpstring][public] */  DECLSPEC_UUID("20D6F666-D2B1-4482-9353-301AC8061D01") 
enum __MIDL___MIDL_itf_WBFLTransactions_0000_0000_0001
    {
        txnRepeat	= 0,
        txnRedo	= 1
    } 	TxnModeType;


EXTERN_C const IID LIBID_WBFLTransactions;

#ifndef __IWBFLTransaction_INTERFACE_DEFINED__
#define __IWBFLTransaction_INTERFACE_DEFINED__

/* interface IWBFLTransaction */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IWBFLTransaction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DBB7742C-CD24-45d6-897B-58A91DD205F7")
    IWBFLTransaction : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Execute( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Undo( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsUndoable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsRepeatable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWBFLTransactionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWBFLTransaction * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWBFLTransaction * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWBFLTransaction * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Execute )( 
            IWBFLTransaction * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Undo )( 
            IWBFLTransaction * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWBFLTransaction * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsUndoable )( 
            IWBFLTransaction * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsRepeatable )( 
            IWBFLTransaction * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IWBFLTransactionVtbl;

    interface IWBFLTransaction
    {
        CONST_VTBL struct IWBFLTransactionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWBFLTransaction_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWBFLTransaction_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWBFLTransaction_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWBFLTransaction_Execute(This)	\
    ( (This)->lpVtbl -> Execute(This) ) 

#define IWBFLTransaction_Undo(This)	\
    ( (This)->lpVtbl -> Undo(This) ) 

#define IWBFLTransaction_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IWBFLTransaction_get_IsUndoable(This,pVal)	\
    ( (This)->lpVtbl -> get_IsUndoable(This,pVal) ) 

#define IWBFLTransaction_get_IsRepeatable(This,pVal)	\
    ( (This)->lpVtbl -> get_IsRepeatable(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWBFLTransaction_INTERFACE_DEFINED__ */


#ifndef __IWBFLMacroTransaction_INTERFACE_DEFINED__
#define __IWBFLMacroTransaction_INTERFACE_DEFINED__

/* interface IWBFLMacroTransaction */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IWBFLMacroTransaction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B39F34E-247E-47EF-B750-50854784D0C4")
    IWBFLMacroTransaction : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Execute( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Undo( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddTransaction( 
            /* [in] */ IWBFLTransaction *txn) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsUndoable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsRepeatable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWBFLMacroTransactionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWBFLMacroTransaction * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWBFLMacroTransaction * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWBFLMacroTransaction * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Execute )( 
            IWBFLMacroTransaction * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Undo )( 
            IWBFLMacroTransaction * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWBFLMacroTransaction * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWBFLMacroTransaction * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddTransaction )( 
            IWBFLMacroTransaction * This,
            /* [in] */ IWBFLTransaction *txn);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsUndoable )( 
            IWBFLMacroTransaction * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsRepeatable )( 
            IWBFLMacroTransaction * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWBFLMacroTransaction * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        END_INTERFACE
    } IWBFLMacroTransactionVtbl;

    interface IWBFLMacroTransaction
    {
        CONST_VTBL struct IWBFLMacroTransactionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWBFLMacroTransaction_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWBFLMacroTransaction_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWBFLMacroTransaction_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWBFLMacroTransaction_Execute(This)	\
    ( (This)->lpVtbl -> Execute(This) ) 

#define IWBFLMacroTransaction_Undo(This)	\
    ( (This)->lpVtbl -> Undo(This) ) 

#define IWBFLMacroTransaction_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IWBFLMacroTransaction_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IWBFLMacroTransaction_AddTransaction(This,txn)	\
    ( (This)->lpVtbl -> AddTransaction(This,txn) ) 

#define IWBFLMacroTransaction_get_IsUndoable(This,pVal)	\
    ( (This)->lpVtbl -> get_IsUndoable(This,pVal) ) 

#define IWBFLMacroTransaction_get_IsRepeatable(This,pVal)	\
    ( (This)->lpVtbl -> get_IsRepeatable(This,pVal) ) 

#define IWBFLMacroTransaction_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWBFLMacroTransaction_INTERFACE_DEFINED__ */


#ifndef __IWBFLMacroAdapter_INTERFACE_DEFINED__
#define __IWBFLMacroAdapter_INTERFACE_DEFINED__

/* interface IWBFLMacroAdapter */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IWBFLMacroAdapter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2F8F8D41-5D23-45DC-9C94-EC70CFE53F07")
    IWBFLMacroAdapter : public IWBFLTransaction
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Macro( 
            /* [retval][out] */ IWBFLMacroTransaction **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Macro( 
            /* [in] */ IWBFLMacroTransaction *newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWBFLMacroAdapterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWBFLMacroAdapter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWBFLMacroAdapter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWBFLMacroAdapter * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Execute )( 
            IWBFLMacroAdapter * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Undo )( 
            IWBFLMacroAdapter * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWBFLMacroAdapter * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsUndoable )( 
            IWBFLMacroAdapter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsRepeatable )( 
            IWBFLMacroAdapter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Macro )( 
            IWBFLMacroAdapter * This,
            /* [retval][out] */ IWBFLMacroTransaction **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Macro )( 
            IWBFLMacroAdapter * This,
            /* [in] */ IWBFLMacroTransaction *newVal);
        
        END_INTERFACE
    } IWBFLMacroAdapterVtbl;

    interface IWBFLMacroAdapter
    {
        CONST_VTBL struct IWBFLMacroAdapterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWBFLMacroAdapter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWBFLMacroAdapter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWBFLMacroAdapter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWBFLMacroAdapter_Execute(This)	\
    ( (This)->lpVtbl -> Execute(This) ) 

#define IWBFLMacroAdapter_Undo(This)	\
    ( (This)->lpVtbl -> Undo(This) ) 

#define IWBFLMacroAdapter_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IWBFLMacroAdapter_get_IsUndoable(This,pVal)	\
    ( (This)->lpVtbl -> get_IsUndoable(This,pVal) ) 

#define IWBFLMacroAdapter_get_IsRepeatable(This,pVal)	\
    ( (This)->lpVtbl -> get_IsRepeatable(This,pVal) ) 


#define IWBFLMacroAdapter_get_Macro(This,pVal)	\
    ( (This)->lpVtbl -> get_Macro(This,pVal) ) 

#define IWBFLMacroAdapter_putref_Macro(This,newVal)	\
    ( (This)->lpVtbl -> putref_Macro(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWBFLMacroAdapter_INTERFACE_DEFINED__ */


#ifndef __IWBFLTransactionMgr_INTERFACE_DEFINED__
#define __IWBFLTransactionMgr_INTERFACE_DEFINED__

/* interface IWBFLTransactionMgr */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IWBFLTransactionMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF78349C-CBC3-46AE-ACD8-08408F0A6231")
    IWBFLTransactionMgr : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Execute( 
            /* [in] */ IWBFLTransaction *txn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Undo( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Redo( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Repeat( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CanUndo( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CanRedo( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CanRepeat( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UndoName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RedoName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RepeatName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TransactionCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UndoCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PeekTransaction( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IWBFLTransaction **txn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PeekUndo( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IWBFLTransaction **txn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearTransactionHistory( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearUndoHistory( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Mode( 
            /* [retval][out] */ TxnModeType *mode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BeginMacro( 
            /* [in] */ VARIANT nameOrMacro) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ExecuteMacro( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AbortMacro( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWBFLTransactionMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWBFLTransactionMgr * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWBFLTransactionMgr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWBFLTransactionMgr * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Execute )( 
            IWBFLTransactionMgr * This,
            /* [in] */ IWBFLTransaction *txn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Undo )( 
            IWBFLTransactionMgr * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Redo )( 
            IWBFLTransactionMgr * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IWBFLTransactionMgr * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanUndo )( 
            IWBFLTransactionMgr * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanRedo )( 
            IWBFLTransactionMgr * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanRepeat )( 
            IWBFLTransactionMgr * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UndoName )( 
            IWBFLTransactionMgr * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RedoName )( 
            IWBFLTransactionMgr * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepeatName )( 
            IWBFLTransactionMgr * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransactionCount )( 
            IWBFLTransactionMgr * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UndoCount )( 
            IWBFLTransactionMgr * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PeekTransaction )( 
            IWBFLTransactionMgr * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IWBFLTransaction **txn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PeekUndo )( 
            IWBFLTransactionMgr * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IWBFLTransaction **txn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearTransactionHistory )( 
            IWBFLTransactionMgr * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearUndoHistory )( 
            IWBFLTransactionMgr * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IWBFLTransactionMgr * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mode )( 
            IWBFLTransactionMgr * This,
            /* [retval][out] */ TxnModeType *mode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BeginMacro )( 
            IWBFLTransactionMgr * This,
            /* [in] */ VARIANT nameOrMacro);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ExecuteMacro )( 
            IWBFLTransactionMgr * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AbortMacro )( 
            IWBFLTransactionMgr * This);
        
        END_INTERFACE
    } IWBFLTransactionMgrVtbl;

    interface IWBFLTransactionMgr
    {
        CONST_VTBL struct IWBFLTransactionMgrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWBFLTransactionMgr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWBFLTransactionMgr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWBFLTransactionMgr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWBFLTransactionMgr_Execute(This,txn)	\
    ( (This)->lpVtbl -> Execute(This,txn) ) 

#define IWBFLTransactionMgr_Undo(This)	\
    ( (This)->lpVtbl -> Undo(This) ) 

#define IWBFLTransactionMgr_Redo(This)	\
    ( (This)->lpVtbl -> Redo(This) ) 

#define IWBFLTransactionMgr_Repeat(This)	\
    ( (This)->lpVtbl -> Repeat(This) ) 

#define IWBFLTransactionMgr_get_CanUndo(This,pVal)	\
    ( (This)->lpVtbl -> get_CanUndo(This,pVal) ) 

#define IWBFLTransactionMgr_get_CanRedo(This,pVal)	\
    ( (This)->lpVtbl -> get_CanRedo(This,pVal) ) 

#define IWBFLTransactionMgr_get_CanRepeat(This,pVal)	\
    ( (This)->lpVtbl -> get_CanRepeat(This,pVal) ) 

#define IWBFLTransactionMgr_get_UndoName(This,pVal)	\
    ( (This)->lpVtbl -> get_UndoName(This,pVal) ) 

#define IWBFLTransactionMgr_get_RedoName(This,pVal)	\
    ( (This)->lpVtbl -> get_RedoName(This,pVal) ) 

#define IWBFLTransactionMgr_get_RepeatName(This,pVal)	\
    ( (This)->lpVtbl -> get_RepeatName(This,pVal) ) 

#define IWBFLTransactionMgr_get_TransactionCount(This,pVal)	\
    ( (This)->lpVtbl -> get_TransactionCount(This,pVal) ) 

#define IWBFLTransactionMgr_get_UndoCount(This,pVal)	\
    ( (This)->lpVtbl -> get_UndoCount(This,pVal) ) 

#define IWBFLTransactionMgr_PeekTransaction(This,idx,txn)	\
    ( (This)->lpVtbl -> PeekTransaction(This,idx,txn) ) 

#define IWBFLTransactionMgr_PeekUndo(This,idx,txn)	\
    ( (This)->lpVtbl -> PeekUndo(This,idx,txn) ) 

#define IWBFLTransactionMgr_ClearTransactionHistory(This)	\
    ( (This)->lpVtbl -> ClearTransactionHistory(This) ) 

#define IWBFLTransactionMgr_ClearUndoHistory(This)	\
    ( (This)->lpVtbl -> ClearUndoHistory(This) ) 

#define IWBFLTransactionMgr_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IWBFLTransactionMgr_get_Mode(This,mode)	\
    ( (This)->lpVtbl -> get_Mode(This,mode) ) 

#define IWBFLTransactionMgr_BeginMacro(This,nameOrMacro)	\
    ( (This)->lpVtbl -> BeginMacro(This,nameOrMacro) ) 

#define IWBFLTransactionMgr_ExecuteMacro(This)	\
    ( (This)->lpVtbl -> ExecuteMacro(This) ) 

#define IWBFLTransactionMgr_AbortMacro(This)	\
    ( (This)->lpVtbl -> AbortMacro(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWBFLTransactionMgr_INTERFACE_DEFINED__ */


#ifndef __IWBFLSupportTransactions_INTERFACE_DEFINED__
#define __IWBFLSupportTransactions_INTERFACE_DEFINED__

/* interface IWBFLSupportTransactions */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWBFLSupportTransactions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("01D989A2-2D02-462f-BD20-DB2BAA426021")
    IWBFLSupportTransactions : public IUnknown
    {
    public:
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_TransactionMgr( 
            /* [in] */ IWBFLTransactionMgr *txnMgr) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWBFLSupportTransactionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWBFLSupportTransactions * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWBFLSupportTransactions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWBFLSupportTransactions * This);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_TransactionMgr )( 
            IWBFLSupportTransactions * This,
            /* [in] */ IWBFLTransactionMgr *txnMgr);
        
        END_INTERFACE
    } IWBFLSupportTransactionsVtbl;

    interface IWBFLSupportTransactions
    {
        CONST_VTBL struct IWBFLSupportTransactionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWBFLSupportTransactions_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWBFLSupportTransactions_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWBFLSupportTransactions_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWBFLSupportTransactions_putref_TransactionMgr(This,txnMgr)	\
    ( (This)->lpVtbl -> putref_TransactionMgr(This,txnMgr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWBFLSupportTransactions_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WBFLTransactionMgr;

#ifdef __cplusplus

class DECLSPEC_UUID("05773828-07E0-4BE1-B99C-EF6D8E0326AE")
WBFLTransactionMgr;
#endif

EXTERN_C const CLSID CLSID_WBFLMacroTransaction;

#ifdef __cplusplus

class DECLSPEC_UUID("8CF1CDEA-D489-41C3-8A90-010D89474297")
WBFLMacroTransaction;
#endif

EXTERN_C const CLSID CLSID_WBFLMacroAdapter;

#ifdef __cplusplus

class DECLSPEC_UUID("125EC02E-C6FD-4385-931D-E9C44BEFB956")
WBFLMacroAdapter;
#endif
#endif /* __WBFLTransactions_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


