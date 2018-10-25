

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:42:37 2017
 */
/* Compiler settings for ..\Include\WBFLLibrary.idl:
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


#ifndef __WBFLLibrary_h__
#define __WBFLLibrary_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILibraryEntry_FWD_DEFINED__
#define __ILibraryEntry_FWD_DEFINED__
typedef interface ILibraryEntry ILibraryEntry;

#endif 	/* __ILibraryEntry_FWD_DEFINED__ */


#ifndef __ILibraryEntryEvents_FWD_DEFINED__
#define __ILibraryEntryEvents_FWD_DEFINED__
typedef interface ILibraryEntryEvents ILibraryEntryEvents;

#endif 	/* __ILibraryEntryEvents_FWD_DEFINED__ */


#ifndef __IEnumLibraryEntry_FWD_DEFINED__
#define __IEnumLibraryEntry_FWD_DEFINED__
typedef interface IEnumLibraryEntry IEnumLibraryEntry;

#endif 	/* __IEnumLibraryEntry_FWD_DEFINED__ */


#ifndef __ILibrary_FWD_DEFINED__
#define __ILibrary_FWD_DEFINED__
typedef interface ILibrary ILibrary;

#endif 	/* __ILibrary_FWD_DEFINED__ */


#ifndef __IEnumLibrary_FWD_DEFINED__
#define __IEnumLibrary_FWD_DEFINED__
typedef interface IEnumLibrary IEnumLibrary;

#endif 	/* __IEnumLibrary_FWD_DEFINED__ */


#ifndef __ILibraryMgr_FWD_DEFINED__
#define __ILibraryMgr_FWD_DEFINED__
typedef interface ILibraryMgr ILibraryMgr;

#endif 	/* __ILibraryMgr_FWD_DEFINED__ */


#ifndef __ILibraryMgrEvents_FWD_DEFINED__
#define __ILibraryMgrEvents_FWD_DEFINED__
typedef interface ILibraryMgrEvents ILibraryMgrEvents;

#endif 	/* __ILibraryMgrEvents_FWD_DEFINED__ */


#ifndef __ILibraryEvents_FWD_DEFINED__
#define __ILibraryEvents_FWD_DEFINED__
typedef interface ILibraryEvents ILibraryEvents;

#endif 	/* __ILibraryEvents_FWD_DEFINED__ */


#ifndef __ILibraryViewer_FWD_DEFINED__
#define __ILibraryViewer_FWD_DEFINED__
typedef interface ILibraryViewer ILibraryViewer;

#endif 	/* __ILibraryViewer_FWD_DEFINED__ */


#ifndef __LibraryMgr_FWD_DEFINED__
#define __LibraryMgr_FWD_DEFINED__

#ifdef __cplusplus
typedef class LibraryMgr LibraryMgr;
#else
typedef struct LibraryMgr LibraryMgr;
#endif /* __cplusplus */

#endif 	/* __LibraryMgr_FWD_DEFINED__ */


#ifndef __Library_FWD_DEFINED__
#define __Library_FWD_DEFINED__

#ifdef __cplusplus
typedef class Library Library;
#else
typedef struct Library Library;
#endif /* __cplusplus */

#endif 	/* __Library_FWD_DEFINED__ */


#ifndef __ILibraryViewerEvents_FWD_DEFINED__
#define __ILibraryViewerEvents_FWD_DEFINED__
typedef interface ILibraryViewerEvents ILibraryViewerEvents;

#endif 	/* __ILibraryViewerEvents_FWD_DEFINED__ */


#ifndef __LibraryViewer_FWD_DEFINED__
#define __LibraryViewer_FWD_DEFINED__

#ifdef __cplusplus
typedef class LibraryViewer LibraryViewer;
#else
typedef struct LibraryViewer LibraryViewer;
#endif /* __cplusplus */

#endif 	/* __LibraryViewer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLLibrary_0000_0000 */
/* [local] */ 

// {46C55423-2575-4252-8B28-7F779B7AD078}
DEFINE_GUID(CATID_WBFLLibraryMgr, 
0x46c55423, 0x2575, 0x4252, 0x8b, 0x28, 0x7f, 0x77, 0x9b, 0x7a, 0xd0, 0x78);


extern RPC_IF_HANDLE __MIDL_itf_WBFLLibrary_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLLibrary_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLLibrary_LIBRARY_DEFINED__
#define __WBFLLibrary_LIBRARY_DEFINED__

/* library WBFLLibrary */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WBFLLibrary;

#ifndef __ILibraryEntry_INTERFACE_DEFINED__
#define __ILibraryEntry_INTERFACE_DEFINED__

/* interface ILibraryEntry */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILibraryEntry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CD76D614-68E6-4b49-B8D4-4160B0FB7F33")
    ILibraryEntry : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InUse( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_InUse( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Locked( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Locked( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILibraryEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILibraryEntry * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILibraryEntry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILibraryEntry * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ILibraryEntry * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ILibraryEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InUse )( 
            ILibraryEntry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InUse )( 
            ILibraryEntry * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Locked )( 
            ILibraryEntry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Locked )( 
            ILibraryEntry * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } ILibraryEntryVtbl;

    interface ILibraryEntry
    {
        CONST_VTBL struct ILibraryEntryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILibraryEntry_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILibraryEntry_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILibraryEntry_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILibraryEntry_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ILibraryEntry_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ILibraryEntry_get_InUse(This,pVal)	\
    ( (This)->lpVtbl -> get_InUse(This,pVal) ) 

#define ILibraryEntry_put_InUse(This,newVal)	\
    ( (This)->lpVtbl -> put_InUse(This,newVal) ) 

#define ILibraryEntry_get_Locked(This,pVal)	\
    ( (This)->lpVtbl -> get_Locked(This,pVal) ) 

#define ILibraryEntry_put_Locked(This,newVal)	\
    ( (This)->lpVtbl -> put_Locked(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILibraryEntry_INTERFACE_DEFINED__ */


#ifndef __ILibraryEntryEvents_INTERFACE_DEFINED__
#define __ILibraryEntryEvents_INTERFACE_DEFINED__

/* interface ILibraryEntryEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILibraryEntryEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("344D345E-987D-4f0c-9D41-9D408118C3B5")
    ILibraryEntryEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnNameChanged( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnEntryChanged( 
            /* [in] */ ILibraryEntry *entry) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILibraryEntryEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILibraryEntryEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILibraryEntryEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILibraryEntryEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnNameChanged )( 
            ILibraryEntryEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        HRESULT ( STDMETHODCALLTYPE *OnEntryChanged )( 
            ILibraryEntryEvents * This,
            /* [in] */ ILibraryEntry *entry);
        
        END_INTERFACE
    } ILibraryEntryEventsVtbl;

    interface ILibraryEntryEvents
    {
        CONST_VTBL struct ILibraryEntryEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILibraryEntryEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILibraryEntryEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILibraryEntryEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILibraryEntryEvents_OnNameChanged(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnNameChanged(This,oldName,newName) ) 

#define ILibraryEntryEvents_OnEntryChanged(This,entry)	\
    ( (This)->lpVtbl -> OnEntryChanged(This,entry) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILibraryEntryEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumLibraryEntry_INTERFACE_DEFINED__
#define __IEnumLibraryEntry_INTERFACE_DEFINED__

/* interface IEnumLibraryEntry */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumLibraryEntry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("82556E2C-659C-481a-8B92-39EE77C46AFE")
    IEnumLibraryEntry : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumLibraryEntry **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ILibraryEntry **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumLibraryEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumLibraryEntry * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumLibraryEntry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumLibraryEntry * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumLibraryEntry * This,
            /* [out] */ IEnumLibraryEntry **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumLibraryEntry * This,
            /* [in] */ ULONG celt,
            /* [out] */ ILibraryEntry **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumLibraryEntry * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumLibraryEntry * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumLibraryEntryVtbl;

    interface IEnumLibraryEntry
    {
        CONST_VTBL struct IEnumLibraryEntryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumLibraryEntry_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumLibraryEntry_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumLibraryEntry_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumLibraryEntry_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumLibraryEntry_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumLibraryEntry_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumLibraryEntry_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumLibraryEntry_INTERFACE_DEFINED__ */


#ifndef __ILibrary_INTERFACE_DEFINED__
#define __ILibrary_INTERFACE_DEFINED__

/* interface ILibrary */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILibrary;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E15347B8-CB99-4D3D-9861-6B4954173AD6")
    ILibrary : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR name,
            /* [retval][out] */ ILibraryEntry **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateEntry( 
            /* [in] */ BSTR name,
            /* [retval][out] */ ILibraryEntry **newEntry) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveEntry( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__Enum( 
            /* [retval][out] */ IEnumLibraryEntry **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILibraryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILibrary * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILibrary * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILibrary * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ILibrary * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILibraryEntry **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ILibrary * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ILibrary * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ILibrary * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateEntry )( 
            ILibrary * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILibraryEntry **newEntry);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveEntry )( 
            ILibrary * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILibrary * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILibrary * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__Enum )( 
            ILibrary * This,
            /* [retval][out] */ IEnumLibraryEntry **pVal);
        
        END_INTERFACE
    } ILibraryVtbl;

    interface ILibrary
    {
        CONST_VTBL struct ILibraryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILibrary_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILibrary_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILibrary_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILibrary_get_Item(This,name,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,name,pVal) ) 

#define ILibrary_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define ILibrary_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ILibrary_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ILibrary_CreateEntry(This,name,newEntry)	\
    ( (This)->lpVtbl -> CreateEntry(This,name,newEntry) ) 

#define ILibrary_RemoveEntry(This,name)	\
    ( (This)->lpVtbl -> RemoveEntry(This,name) ) 

#define ILibrary_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILibrary_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILibrary_get__Enum(This,pVal)	\
    ( (This)->lpVtbl -> get__Enum(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILibrary_INTERFACE_DEFINED__ */


#ifndef __IEnumLibrary_INTERFACE_DEFINED__
#define __IEnumLibrary_INTERFACE_DEFINED__

/* interface IEnumLibrary */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumLibrary;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("18B051F5-D3B5-4228-BD8D-88533856905F")
    IEnumLibrary : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumLibrary **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ILibrary **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumLibraryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumLibrary * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumLibrary * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumLibrary * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumLibrary * This,
            /* [out] */ IEnumLibrary **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumLibrary * This,
            /* [in] */ ULONG celt,
            /* [out] */ ILibrary **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumLibrary * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumLibrary * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumLibraryVtbl;

    interface IEnumLibrary
    {
        CONST_VTBL struct IEnumLibraryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumLibrary_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumLibrary_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumLibrary_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumLibrary_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumLibrary_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumLibrary_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumLibrary_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumLibrary_INTERFACE_DEFINED__ */


#ifndef __ILibraryMgr_INTERFACE_DEFINED__
#define __ILibraryMgr_INTERFACE_DEFINED__

/* interface ILibraryMgr */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILibraryMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("63BC88AF-2C7D-4224-90B7-5C078C0983CE")
    ILibraryMgr : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ILibrary *newLibrary) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR name,
            /* [retval][out] */ ILibrary **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__Enum( 
            /* [retval][out] */ IEnumLibrary **ppenum) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILibraryMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILibraryMgr * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILibraryMgr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILibraryMgr * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ILibraryMgr * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ILibraryMgr * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ILibraryMgr * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILibraryMgr * This,
            /* [in] */ ILibrary *newLibrary);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ILibraryMgr * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILibraryMgr * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ILibraryMgr * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILibrary **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILibraryMgr * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__Enum )( 
            ILibraryMgr * This,
            /* [retval][out] */ IEnumLibrary **ppenum);
        
        END_INTERFACE
    } ILibraryMgrVtbl;

    interface ILibraryMgr
    {
        CONST_VTBL struct ILibraryMgrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILibraryMgr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILibraryMgr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILibraryMgr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILibraryMgr_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define ILibraryMgr_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ILibraryMgr_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ILibraryMgr_Add(This,newLibrary)	\
    ( (This)->lpVtbl -> Add(This,newLibrary) ) 

#define ILibraryMgr_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define ILibraryMgr_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILibraryMgr_get_Item(This,name,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,name,pVal) ) 

#define ILibraryMgr_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILibraryMgr_get__Enum(This,ppenum)	\
    ( (This)->lpVtbl -> get__Enum(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILibraryMgr_INTERFACE_DEFINED__ */


#ifndef __ILibraryMgrEvents_INTERFACE_DEFINED__
#define __ILibraryMgrEvents_INTERFACE_DEFINED__

/* interface ILibraryMgrEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILibraryMgrEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47D4D00D-1EFF-4a34-9F92-DD6777F19AF3")
    ILibraryMgrEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnNameChanged( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnChanged( 
            /* [in] */ ILibraryMgr *libMgr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnLibraryNameChanged( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnLibraryChanged( 
            /* [in] */ ILibrary *lib) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnEntryNameChanged( 
            /* [in] */ ILibrary *lib,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnEntryChanged( 
            /* [in] */ ILibrary *lib,
            /* [in] */ ILibraryEntry *entry) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILibraryMgrEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILibraryMgrEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILibraryMgrEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILibraryMgrEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnNameChanged )( 
            ILibraryMgrEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        HRESULT ( STDMETHODCALLTYPE *OnChanged )( 
            ILibraryMgrEvents * This,
            /* [in] */ ILibraryMgr *libMgr);
        
        HRESULT ( STDMETHODCALLTYPE *OnLibraryNameChanged )( 
            ILibraryMgrEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        HRESULT ( STDMETHODCALLTYPE *OnLibraryChanged )( 
            ILibraryMgrEvents * This,
            /* [in] */ ILibrary *lib);
        
        HRESULT ( STDMETHODCALLTYPE *OnEntryNameChanged )( 
            ILibraryMgrEvents * This,
            /* [in] */ ILibrary *lib,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        HRESULT ( STDMETHODCALLTYPE *OnEntryChanged )( 
            ILibraryMgrEvents * This,
            /* [in] */ ILibrary *lib,
            /* [in] */ ILibraryEntry *entry);
        
        END_INTERFACE
    } ILibraryMgrEventsVtbl;

    interface ILibraryMgrEvents
    {
        CONST_VTBL struct ILibraryMgrEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILibraryMgrEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILibraryMgrEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILibraryMgrEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILibraryMgrEvents_OnNameChanged(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnNameChanged(This,oldName,newName) ) 

#define ILibraryMgrEvents_OnChanged(This,libMgr)	\
    ( (This)->lpVtbl -> OnChanged(This,libMgr) ) 

#define ILibraryMgrEvents_OnLibraryNameChanged(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLibraryNameChanged(This,oldName,newName) ) 

#define ILibraryMgrEvents_OnLibraryChanged(This,lib)	\
    ( (This)->lpVtbl -> OnLibraryChanged(This,lib) ) 

#define ILibraryMgrEvents_OnEntryNameChanged(This,lib,oldName,newName)	\
    ( (This)->lpVtbl -> OnEntryNameChanged(This,lib,oldName,newName) ) 

#define ILibraryMgrEvents_OnEntryChanged(This,lib,entry)	\
    ( (This)->lpVtbl -> OnEntryChanged(This,lib,entry) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILibraryMgrEvents_INTERFACE_DEFINED__ */


#ifndef __ILibraryEvents_INTERFACE_DEFINED__
#define __ILibraryEvents_INTERFACE_DEFINED__

/* interface ILibraryEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILibraryEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("623332B2-B575-4b2e-88F3-8299650891DE")
    ILibraryEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnNameChanged( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnLibraryChanged( 
            /* [in] */ ILibrary *lib) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnEntryNameChanged( 
            /* [in] */ ILibrary *lib,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnEntryChanged( 
            /* [in] */ ILibrary *lib,
            /* [in] */ ILibraryEntry *entry) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILibraryEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILibraryEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILibraryEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILibraryEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnNameChanged )( 
            ILibraryEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        HRESULT ( STDMETHODCALLTYPE *OnLibraryChanged )( 
            ILibraryEvents * This,
            /* [in] */ ILibrary *lib);
        
        HRESULT ( STDMETHODCALLTYPE *OnEntryNameChanged )( 
            ILibraryEvents * This,
            /* [in] */ ILibrary *lib,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        HRESULT ( STDMETHODCALLTYPE *OnEntryChanged )( 
            ILibraryEvents * This,
            /* [in] */ ILibrary *lib,
            /* [in] */ ILibraryEntry *entry);
        
        END_INTERFACE
    } ILibraryEventsVtbl;

    interface ILibraryEvents
    {
        CONST_VTBL struct ILibraryEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILibraryEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILibraryEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILibraryEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILibraryEvents_OnNameChanged(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnNameChanged(This,oldName,newName) ) 

#define ILibraryEvents_OnLibraryChanged(This,lib)	\
    ( (This)->lpVtbl -> OnLibraryChanged(This,lib) ) 

#define ILibraryEvents_OnEntryNameChanged(This,lib,oldName,newName)	\
    ( (This)->lpVtbl -> OnEntryNameChanged(This,lib,oldName,newName) ) 

#define ILibraryEvents_OnEntryChanged(This,lib,entry)	\
    ( (This)->lpVtbl -> OnEntryChanged(This,lib,entry) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILibraryEvents_INTERFACE_DEFINED__ */


#ifndef __ILibraryViewer_INTERFACE_DEFINED__
#define __ILibraryViewer_INTERFACE_DEFINED__

/* interface ILibraryViewer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILibraryViewer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6A3E5A8-C81D-46F1-8C58-848CB38B6D6A")
    ILibraryViewer : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoSize( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoSize( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LibraryMgr( 
            /* [retval][out] */ ILibraryMgr **pVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_LibraryMgr( 
            /* [in] */ ILibraryMgr *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EditCurSel( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILibraryViewerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILibraryViewer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILibraryViewer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILibraryViewer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILibraryViewer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILibraryViewer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILibraryViewer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILibraryViewer * This,
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
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoSize )( 
            ILibraryViewer * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoSize )( 
            ILibraryViewer * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LibraryMgr )( 
            ILibraryViewer * This,
            /* [retval][out] */ ILibraryMgr **pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_LibraryMgr )( 
            ILibraryViewer * This,
            /* [in] */ ILibraryMgr *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EditCurSel )( 
            ILibraryViewer * This);
        
        END_INTERFACE
    } ILibraryViewerVtbl;

    interface ILibraryViewer
    {
        CONST_VTBL struct ILibraryViewerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILibraryViewer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILibraryViewer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILibraryViewer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILibraryViewer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILibraryViewer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILibraryViewer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILibraryViewer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ILibraryViewer_put_AutoSize(This,vbool)	\
    ( (This)->lpVtbl -> put_AutoSize(This,vbool) ) 

#define ILibraryViewer_get_AutoSize(This,pbool)	\
    ( (This)->lpVtbl -> get_AutoSize(This,pbool) ) 

#define ILibraryViewer_get_LibraryMgr(This,pVal)	\
    ( (This)->lpVtbl -> get_LibraryMgr(This,pVal) ) 

#define ILibraryViewer_putref_LibraryMgr(This,newVal)	\
    ( (This)->lpVtbl -> putref_LibraryMgr(This,newVal) ) 

#define ILibraryViewer_EditCurSel(This)	\
    ( (This)->lpVtbl -> EditCurSel(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILibraryViewer_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LibraryMgr;

#ifdef __cplusplus

class DECLSPEC_UUID("0795E1D7-3F1B-4E6A-B010-7AE07A5EB70C")
LibraryMgr;
#endif

EXTERN_C const CLSID CLSID_Library;

#ifdef __cplusplus

class DECLSPEC_UUID("21270B15-4445-4D09-ABF2-F38D712472EF")
Library;
#endif

#ifndef __ILibraryViewerEvents_INTERFACE_DEFINED__
#define __ILibraryViewerEvents_INTERFACE_DEFINED__

/* interface ILibraryViewerEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILibraryViewerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74C5DA97-57F1-4FE2-B6C0-929C48B5A8F2")
    ILibraryViewerEvents : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct ILibraryViewerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILibraryViewerEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILibraryViewerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILibraryViewerEvents * This);
        
        END_INTERFACE
    } ILibraryViewerEventsVtbl;

    interface ILibraryViewerEvents
    {
        CONST_VTBL struct ILibraryViewerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILibraryViewerEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILibraryViewerEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILibraryViewerEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILibraryViewerEvents_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LibraryViewer;

#ifdef __cplusplus

class DECLSPEC_UUID("14361D58-AF5B-11D4-8B4D-006097C68A9C")
LibraryViewer;
#endif
#endif /* __WBFLLibrary_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


