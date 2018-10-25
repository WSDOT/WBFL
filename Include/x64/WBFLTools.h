

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:22:07 2017
 */
/* Compiler settings for ..\Include\WBFLTools.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
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


#ifndef __WBFLTools_h__
#define __WBFLTools_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IStructuredLoad2_FWD_DEFINED__
#define __IStructuredLoad2_FWD_DEFINED__
typedef interface IStructuredLoad2 IStructuredLoad2;

#endif 	/* __IStructuredLoad2_FWD_DEFINED__ */


#ifndef __IStructuredSave2_FWD_DEFINED__
#define __IStructuredSave2_FWD_DEFINED__
typedef interface IStructuredSave2 IStructuredSave2;

#endif 	/* __IStructuredSave2_FWD_DEFINED__ */


#ifndef __IStructuredStorage2_FWD_DEFINED__
#define __IStructuredStorage2_FWD_DEFINED__
typedef interface IStructuredStorage2 IStructuredStorage2;

#endif 	/* __IStructuredStorage2_FWD_DEFINED__ */


#ifndef __IMohrCircle_FWD_DEFINED__
#define __IMohrCircle_FWD_DEFINED__
typedef interface IMohrCircle IMohrCircle;

#endif 	/* __IMohrCircle_FWD_DEFINED__ */


#ifndef __IARPNotice_FWD_DEFINED__
#define __IARPNotice_FWD_DEFINED__
typedef interface IARPNotice IARPNotice;

#endif 	/* __IARPNotice_FWD_DEFINED__ */


#ifndef __IWBFLErrorLog_FWD_DEFINED__
#define __IWBFLErrorLog_FWD_DEFINED__
typedef interface IWBFLErrorLog IWBFLErrorLog;

#endif 	/* __IWBFLErrorLog_FWD_DEFINED__ */


#ifndef __IProgressMonitorWindow_FWD_DEFINED__
#define __IProgressMonitorWindow_FWD_DEFINED__
typedef interface IProgressMonitorWindow IProgressMonitorWindow;

#endif 	/* __IProgressMonitorWindow_FWD_DEFINED__ */


#ifndef __ILogProgressToFile_FWD_DEFINED__
#define __ILogProgressToFile_FWD_DEFINED__
typedef interface ILogProgressToFile ILogProgressToFile;

#endif 	/* __ILogProgressToFile_FWD_DEFINED__ */


#ifndef __IEnumLongArray_FWD_DEFINED__
#define __IEnumLongArray_FWD_DEFINED__
typedef interface IEnumLongArray IEnumLongArray;

#endif 	/* __IEnumLongArray_FWD_DEFINED__ */


#ifndef __ILongArray_FWD_DEFINED__
#define __ILongArray_FWD_DEFINED__
typedef interface ILongArray ILongArray;

#endif 	/* __ILongArray_FWD_DEFINED__ */


#ifndef __IEnumIDArray_FWD_DEFINED__
#define __IEnumIDArray_FWD_DEFINED__
typedef interface IEnumIDArray IEnumIDArray;

#endif 	/* __IEnumIDArray_FWD_DEFINED__ */


#ifndef __IIDArray_FWD_DEFINED__
#define __IIDArray_FWD_DEFINED__
typedef interface IIDArray IIDArray;

#endif 	/* __IIDArray_FWD_DEFINED__ */


#ifndef __IEnumIndexArray_FWD_DEFINED__
#define __IEnumIndexArray_FWD_DEFINED__
typedef interface IEnumIndexArray IEnumIndexArray;

#endif 	/* __IEnumIndexArray_FWD_DEFINED__ */


#ifndef __IIndexArray_FWD_DEFINED__
#define __IIndexArray_FWD_DEFINED__
typedef interface IIndexArray IIndexArray;

#endif 	/* __IIndexArray_FWD_DEFINED__ */


#ifndef __IEnumDblArray_FWD_DEFINED__
#define __IEnumDblArray_FWD_DEFINED__
typedef interface IEnumDblArray IEnumDblArray;

#endif 	/* __IEnumDblArray_FWD_DEFINED__ */


#ifndef __IDblArray_FWD_DEFINED__
#define __IDblArray_FWD_DEFINED__
typedef interface IDblArray IDblArray;

#endif 	/* __IDblArray_FWD_DEFINED__ */


#ifndef __IEnumBstrArray_FWD_DEFINED__
#define __IEnumBstrArray_FWD_DEFINED__
typedef interface IEnumBstrArray IEnumBstrArray;

#endif 	/* __IEnumBstrArray_FWD_DEFINED__ */


#ifndef __IBstrArray_FWD_DEFINED__
#define __IBstrArray_FWD_DEFINED__
typedef interface IBstrArray IBstrArray;

#endif 	/* __IBstrArray_FWD_DEFINED__ */


#ifndef __IEnumUnkArray_FWD_DEFINED__
#define __IEnumUnkArray_FWD_DEFINED__
typedef interface IEnumUnkArray IEnumUnkArray;

#endif 	/* __IEnumUnkArray_FWD_DEFINED__ */


#ifndef __IUnkArray_FWD_DEFINED__
#define __IUnkArray_FWD_DEFINED__
typedef interface IUnkArray IUnkArray;

#endif 	/* __IUnkArray_FWD_DEFINED__ */


#ifndef __IProgressMonitor_FWD_DEFINED__
#define __IProgressMonitor_FWD_DEFINED__
typedef interface IProgressMonitor IProgressMonitor;

#endif 	/* __IProgressMonitor_FWD_DEFINED__ */


#ifndef __ISupportProgressMonitor_FWD_DEFINED__
#define __ISupportProgressMonitor_FWD_DEFINED__
typedef interface ISupportProgressMonitor ISupportProgressMonitor;

#endif 	/* __ISupportProgressMonitor_FWD_DEFINED__ */


#ifndef __MohrCircle_FWD_DEFINED__
#define __MohrCircle_FWD_DEFINED__

#ifdef __cplusplus
typedef class MohrCircle MohrCircle;
#else
typedef struct MohrCircle MohrCircle;
#endif /* __cplusplus */

#endif 	/* __MohrCircle_FWD_DEFINED__ */


#ifndef __ARPNotice_FWD_DEFINED__
#define __ARPNotice_FWD_DEFINED__

#ifdef __cplusplus
typedef class ARPNotice ARPNotice;
#else
typedef struct ARPNotice ARPNotice;
#endif /* __cplusplus */

#endif 	/* __ARPNotice_FWD_DEFINED__ */


#ifndef __StructuredSave2_FWD_DEFINED__
#define __StructuredSave2_FWD_DEFINED__

#ifdef __cplusplus
typedef class StructuredSave2 StructuredSave2;
#else
typedef struct StructuredSave2 StructuredSave2;
#endif /* __cplusplus */

#endif 	/* __StructuredSave2_FWD_DEFINED__ */


#ifndef __StructuredLoad2_FWD_DEFINED__
#define __StructuredLoad2_FWD_DEFINED__

#ifdef __cplusplus
typedef class StructuredLoad2 StructuredLoad2;
#else
typedef struct StructuredLoad2 StructuredLoad2;
#endif /* __cplusplus */

#endif 	/* __StructuredLoad2_FWD_DEFINED__ */


#ifndef __WBFLErrorLog_FWD_DEFINED__
#define __WBFLErrorLog_FWD_DEFINED__

#ifdef __cplusplus
typedef class WBFLErrorLog WBFLErrorLog;
#else
typedef struct WBFLErrorLog WBFLErrorLog;
#endif /* __cplusplus */

#endif 	/* __WBFLErrorLog_FWD_DEFINED__ */


#ifndef __ProgressMonitor_FWD_DEFINED__
#define __ProgressMonitor_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProgressMonitor ProgressMonitor;
#else
typedef struct ProgressMonitor ProgressMonitor;
#endif /* __cplusplus */

#endif 	/* __ProgressMonitor_FWD_DEFINED__ */


#ifndef __ProgressMonitorWindow_FWD_DEFINED__
#define __ProgressMonitorWindow_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProgressMonitorWindow ProgressMonitorWindow;
#else
typedef struct ProgressMonitorWindow ProgressMonitorWindow;
#endif /* __cplusplus */

#endif 	/* __ProgressMonitorWindow_FWD_DEFINED__ */


#ifndef __LongArray_FWD_DEFINED__
#define __LongArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class LongArray LongArray;
#else
typedef struct LongArray LongArray;
#endif /* __cplusplus */

#endif 	/* __LongArray_FWD_DEFINED__ */


#ifndef __IDArray_FWD_DEFINED__
#define __IDArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class IDArray IDArray;
#else
typedef struct IDArray IDArray;
#endif /* __cplusplus */

#endif 	/* __IDArray_FWD_DEFINED__ */


#ifndef __IndexArray_FWD_DEFINED__
#define __IndexArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class IndexArray IndexArray;
#else
typedef struct IndexArray IndexArray;
#endif /* __cplusplus */

#endif 	/* __IndexArray_FWD_DEFINED__ */


#ifndef __DblArray_FWD_DEFINED__
#define __DblArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class DblArray DblArray;
#else
typedef struct DblArray DblArray;
#endif /* __cplusplus */

#endif 	/* __DblArray_FWD_DEFINED__ */


#ifndef __BstrArray_FWD_DEFINED__
#define __BstrArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class BstrArray BstrArray;
#else
typedef struct BstrArray BstrArray;
#endif /* __cplusplus */

#endif 	/* __BstrArray_FWD_DEFINED__ */


#ifndef __UnkArray_FWD_DEFINED__
#define __UnkArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnkArray UnkArray;
#else
typedef struct UnkArray UnkArray;
#endif /* __cplusplus */

#endif 	/* __UnkArray_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLTools_0000_0000 */
/* [local] */ 

/////////////////////////////////////////////////////////////////////////////
// ILogFile status codes
#define LOGFILE_E_FIRST    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x0200)
#define LOGFILE_E_LAST     MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x020F)

#define LOGFILE_E_CANTOPEN           (LOGFILE_E_FIRST+0)
// unable to open the log file

#define LOGFILE_E_BADWRITE           (LOGFILE_E_FIRST+1)
// error occured while logging message

#define LOGFILE_E_NOLOGFILE          (LOGFILE_E_FIRST+2)
// invalid cookie was used
/////////////////////////////////////////////////////////////////////////////
// IStructuredLoad status codes
#define STRLOAD_E_FIRST    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x0200)
#define STRLOAD_E_LAST     MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x020F)

#define STRLOAD_E_CANTOPEN           (STRLOAD_E_FIRST+0)
// unable to open the structured storage

#define STRLOAD_E_INVALIDFORMAT      (STRLOAD_E_FIRST+1)
// invalid structured storage format

#define STRLOAD_E_BADVERSION         (STRLOAD_E_FIRST+2)
// invalid version number encountered

#define STRLOAD_E_FILENOTFOUND       (STRLOAD_E_FIRST+3)
// the specified file was not found

#define STRLOAD_E_CLASS_NOT_REGISTERED (STRLOAD_E_FIRST+4)
// class was not registered and cannot be created

#define STRLOAD_E_CLASS_ISTRUCTUREDSTORAGE2 (STRLOAD_E_FIRST+5)
// the class does not support the IStructuredStorage2 interface

/////////////////////////////////////////////////////////////////////////////
// IStructuredSave status codes
#define STRSAVE_E_FIRST    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x0200)
#define STRSAVE_E_LAST     MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x020F)

#define STRSAVE_E_CANTOPEN                (STRSAVE_E_FIRST+0)
// unable to open the structured storage

#define STRSAVE_E_BADWRITE                (STRSAVE_E_FIRST+1)
// could not write to stream

#define STRSAVE_E_INITIALIZING_THE_PARSER (STRSAVE_E_FIRST+2)
// problem firing up the parser

#define STRSAVE_E_INVALID_VARIANT_TYPE    (STRSAVE_E_FIRST+3)
// Invalid variant type passed in by client or in xml file

#define STRSAVE_E_FILE_NOT_OPEN           (STRSAVE_E_FIRST+4)
// tried to write to file that's not open

#define STRSAVE_E_IPERSIST                (STRSAVE_E_FIRST+5)
// classes saved must support IPersist

#define STRSAVE_E_CLASS_ISTRUCTUREDSTORAGE2 (STRSAVE_E_FIRST+6)
// the class does not support the IStructuredStorage2 interface

#define STRSAVE_E_MUST_HAVE_ONE_UNIT        (STRSAVE_E_FIRST+7)
// all structured storage documents must have at least on unit 

#define STRSAVE_E_ONLY_ONE_UNIT             (STRSAVE_E_FIRST+8)


extern RPC_IF_HANDLE __MIDL_itf_WBFLTools_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLTools_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLTools_LIBRARY_DEFINED__
#define __WBFLTools_LIBRARY_DEFINED__

/* library WBFLTools */
/* [helpstring][helpcontext][helpfile][version][uuid] */ 

typedef /* [public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("AB6DF408-C7B1-11D3-8A1D-006097C68A9C") 
enum __MIDL___MIDL_itf_WBFLTools_0000_0000_0001
    {
        ltAROSL	= 1,
        ltARLOSL	= 2
    } 	LicenseType;

typedef /* [public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("AB6DF409-C7B1-11D3-8A1D-006097C68A9C") 
enum __MIDL___MIDL_itf_WBFLTools_0000_0000_0002
    {
        atAccept	= 1,
        atReject	= 2
    } 	AcceptanceType;


EXTERN_C const IID LIBID_WBFLTools;

#ifndef __IStructuredLoad2_INTERFACE_DEFINED__
#define __IStructuredLoad2_INTERFACE_DEFINED__

/* interface IStructuredLoad2 */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStructuredLoad2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("88110BF6-AC46-11d4-8B4B-006097C68A9C")
    IStructuredLoad2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR bstrFile) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE BeginUnit( 
            /* [in] */ BSTR bstrUnit) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE EndUnit( 
            /* [retval][out] */ VARIANT_BOOL *bEnd) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopVersion( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Property( 
            /* [in] */ BSTR bstrPropName,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE EndOfStorage( 
            /* [retval][out] */ VARIANT_BOOL *bEnd) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStructuredLoad2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStructuredLoad2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStructuredLoad2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStructuredLoad2 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IStructuredLoad2 * This,
            /* [in] */ BSTR bstrFile);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *BeginUnit )( 
            IStructuredLoad2 * This,
            /* [in] */ BSTR bstrUnit);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *EndUnit )( 
            IStructuredLoad2 * This,
            /* [retval][out] */ VARIANT_BOOL *bEnd);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IStructuredLoad2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopVersion )( 
            IStructuredLoad2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Property )( 
            IStructuredLoad2 * This,
            /* [in] */ BSTR bstrPropName,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *EndOfStorage )( 
            IStructuredLoad2 * This,
            /* [retval][out] */ VARIANT_BOOL *bEnd);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IStructuredLoad2 * This);
        
        END_INTERFACE
    } IStructuredLoad2Vtbl;

    interface IStructuredLoad2
    {
        CONST_VTBL struct IStructuredLoad2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStructuredLoad2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStructuredLoad2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStructuredLoad2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStructuredLoad2_Open(This,bstrFile)	\
    ( (This)->lpVtbl -> Open(This,bstrFile) ) 

#define IStructuredLoad2_BeginUnit(This,bstrUnit)	\
    ( (This)->lpVtbl -> BeginUnit(This,bstrUnit) ) 

#define IStructuredLoad2_EndUnit(This,bEnd)	\
    ( (This)->lpVtbl -> EndUnit(This,bEnd) ) 

#define IStructuredLoad2_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IStructuredLoad2_get_TopVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_TopVersion(This,pVal) ) 

#define IStructuredLoad2_get_Property(This,bstrPropName,pVal)	\
    ( (This)->lpVtbl -> get_Property(This,bstrPropName,pVal) ) 

#define IStructuredLoad2_EndOfStorage(This,bEnd)	\
    ( (This)->lpVtbl -> EndOfStorage(This,bEnd) ) 

#define IStructuredLoad2_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStructuredLoad2_INTERFACE_DEFINED__ */


#ifndef __IStructuredSave2_INTERFACE_DEFINED__
#define __IStructuredSave2_INTERFACE_DEFINED__

/* interface IStructuredSave2 */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStructuredSave2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("88110BF7-AC46-11d4-8B4B-006097C68A9C")
    IStructuredSave2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE BeginUnit( 
            /* [in] */ BSTR bstrUnit,
            /* [in] */ Float64 ver) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE EndUnit( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopVersion( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Property( 
            /* [in] */ BSTR bstrPropName,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStructuredSave2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStructuredSave2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStructuredSave2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStructuredSave2 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IStructuredSave2 * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *BeginUnit )( 
            IStructuredSave2 * This,
            /* [in] */ BSTR bstrUnit,
            /* [in] */ Float64 ver);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *EndUnit )( 
            IStructuredSave2 * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IStructuredSave2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopVersion )( 
            IStructuredSave2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Property )( 
            IStructuredSave2 * This,
            /* [in] */ BSTR bstrPropName,
            /* [in] */ VARIANT newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IStructuredSave2 * This);
        
        END_INTERFACE
    } IStructuredSave2Vtbl;

    interface IStructuredSave2
    {
        CONST_VTBL struct IStructuredSave2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStructuredSave2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStructuredSave2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStructuredSave2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStructuredSave2_Open(This,bstrFileName)	\
    ( (This)->lpVtbl -> Open(This,bstrFileName) ) 

#define IStructuredSave2_BeginUnit(This,bstrUnit,ver)	\
    ( (This)->lpVtbl -> BeginUnit(This,bstrUnit,ver) ) 

#define IStructuredSave2_EndUnit(This)	\
    ( (This)->lpVtbl -> EndUnit(This) ) 

#define IStructuredSave2_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IStructuredSave2_get_TopVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_TopVersion(This,pVal) ) 

#define IStructuredSave2_put_Property(This,bstrPropName,newVal)	\
    ( (This)->lpVtbl -> put_Property(This,bstrPropName,newVal) ) 

#define IStructuredSave2_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStructuredSave2_INTERFACE_DEFINED__ */


#ifndef __IStructuredStorage2_INTERFACE_DEFINED__
#define __IStructuredStorage2_INTERFACE_DEFINED__

/* interface IStructuredStorage2 */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStructuredStorage2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5693D0F5-AC55-11d4-8B4B-006097C68A9C")
    IStructuredStorage2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ IStructuredLoad2 *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ IStructuredSave2 *save) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStructuredStorage2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStructuredStorage2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStructuredStorage2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStructuredStorage2 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IStructuredStorage2 * This,
            /* [in] */ IStructuredLoad2 *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IStructuredStorage2 * This,
            /* [in] */ IStructuredSave2 *save);
        
        END_INTERFACE
    } IStructuredStorage2Vtbl;

    interface IStructuredStorage2
    {
        CONST_VTBL struct IStructuredStorage2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStructuredStorage2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStructuredStorage2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStructuredStorage2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStructuredStorage2_Load(This,load)	\
    ( (This)->lpVtbl -> Load(This,load) ) 

#define IStructuredStorage2_Save(This,save)	\
    ( (This)->lpVtbl -> Save(This,save) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStructuredStorage2_INTERFACE_DEFINED__ */


#ifndef __IMohrCircle_INTERFACE_DEFINED__
#define __IMohrCircle_INTERFACE_DEFINED__

/* interface IMohrCircle */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IMohrCircle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E590D200-FF47-11D2-8CDF-F43C3928A334")
    IMohrCircle : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Sii( 
            /* [retval][out] */ Float64 *sii) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Sii( 
            /* [in] */ Float64 sii) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Sjj( 
            /* [retval][out] */ Float64 *sjj) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Sjj( 
            /* [in] */ Float64 sjj) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Sij( 
            /* [retval][out] */ Float64 *sij) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Sij( 
            /* [in] */ Float64 sij) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Center( 
            /* [retval][out] */ Float64 *center) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Radius( 
            /* [retval][out] */ Float64 *radius) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_PrincipleDirection( 
            /* [retval][out] */ Float64 *dir) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Smax( 
            /* [retval][out] */ Float64 *Smax) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Smin( 
            /* [retval][out] */ Float64 *Smin) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Tmax( 
            /* [retval][out] */ Float64 *Tmax) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeState( 
            /* [in] */ Float64 angle,
            /* [out] */ Float64 *S11,
            /* [out] */ Float64 *S22,
            /* [out] */ Float64 *S12) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeSxx( 
            /* [in] */ Float64 angle,
            /* [retval][out] */ Float64 *sxx) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeSxy( 
            /* [in] */ Float64 angle,
            /* [retval][out] */ Float64 *sxy) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeSyy( 
            /* [in] */ Float64 angle,
            /* [retval][out] */ Float64 *syy) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMohrCircleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMohrCircle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMohrCircle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMohrCircle * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sii )( 
            IMohrCircle * This,
            /* [retval][out] */ Float64 *sii);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sii )( 
            IMohrCircle * This,
            /* [in] */ Float64 sii);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sjj )( 
            IMohrCircle * This,
            /* [retval][out] */ Float64 *sjj);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sjj )( 
            IMohrCircle * This,
            /* [in] */ Float64 sjj);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sij )( 
            IMohrCircle * This,
            /* [retval][out] */ Float64 *sij);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sij )( 
            IMohrCircle * This,
            /* [in] */ Float64 sij);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Center )( 
            IMohrCircle * This,
            /* [retval][out] */ Float64 *center);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Radius )( 
            IMohrCircle * This,
            /* [retval][out] */ Float64 *radius);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrincipleDirection )( 
            IMohrCircle * This,
            /* [retval][out] */ Float64 *dir);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Smax )( 
            IMohrCircle * This,
            /* [retval][out] */ Float64 *Smax);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Smin )( 
            IMohrCircle * This,
            /* [retval][out] */ Float64 *Smin);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tmax )( 
            IMohrCircle * This,
            /* [retval][out] */ Float64 *Tmax);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeState )( 
            IMohrCircle * This,
            /* [in] */ Float64 angle,
            /* [out] */ Float64 *S11,
            /* [out] */ Float64 *S22,
            /* [out] */ Float64 *S12);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeSxx )( 
            IMohrCircle * This,
            /* [in] */ Float64 angle,
            /* [retval][out] */ Float64 *sxx);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeSxy )( 
            IMohrCircle * This,
            /* [in] */ Float64 angle,
            /* [retval][out] */ Float64 *sxy);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeSyy )( 
            IMohrCircle * This,
            /* [in] */ Float64 angle,
            /* [retval][out] */ Float64 *syy);
        
        END_INTERFACE
    } IMohrCircleVtbl;

    interface IMohrCircle
    {
        CONST_VTBL struct IMohrCircleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMohrCircle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMohrCircle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMohrCircle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMohrCircle_get_Sii(This,sii)	\
    ( (This)->lpVtbl -> get_Sii(This,sii) ) 

#define IMohrCircle_put_Sii(This,sii)	\
    ( (This)->lpVtbl -> put_Sii(This,sii) ) 

#define IMohrCircle_get_Sjj(This,sjj)	\
    ( (This)->lpVtbl -> get_Sjj(This,sjj) ) 

#define IMohrCircle_put_Sjj(This,sjj)	\
    ( (This)->lpVtbl -> put_Sjj(This,sjj) ) 

#define IMohrCircle_get_Sij(This,sij)	\
    ( (This)->lpVtbl -> get_Sij(This,sij) ) 

#define IMohrCircle_put_Sij(This,sij)	\
    ( (This)->lpVtbl -> put_Sij(This,sij) ) 

#define IMohrCircle_get_Center(This,center)	\
    ( (This)->lpVtbl -> get_Center(This,center) ) 

#define IMohrCircle_get_Radius(This,radius)	\
    ( (This)->lpVtbl -> get_Radius(This,radius) ) 

#define IMohrCircle_get_PrincipleDirection(This,dir)	\
    ( (This)->lpVtbl -> get_PrincipleDirection(This,dir) ) 

#define IMohrCircle_get_Smax(This,Smax)	\
    ( (This)->lpVtbl -> get_Smax(This,Smax) ) 

#define IMohrCircle_get_Smin(This,Smin)	\
    ( (This)->lpVtbl -> get_Smin(This,Smin) ) 

#define IMohrCircle_get_Tmax(This,Tmax)	\
    ( (This)->lpVtbl -> get_Tmax(This,Tmax) ) 

#define IMohrCircle_ComputeState(This,angle,S11,S22,S12)	\
    ( (This)->lpVtbl -> ComputeState(This,angle,S11,S22,S12) ) 

#define IMohrCircle_ComputeSxx(This,angle,sxx)	\
    ( (This)->lpVtbl -> ComputeSxx(This,angle,sxx) ) 

#define IMohrCircle_ComputeSxy(This,angle,sxy)	\
    ( (This)->lpVtbl -> ComputeSxy(This,angle,sxy) ) 

#define IMohrCircle_ComputeSyy(This,angle,syy)	\
    ( (This)->lpVtbl -> ComputeSyy(This,angle,syy) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMohrCircle_INTERFACE_DEFINED__ */


#ifndef __IARPNotice_INTERFACE_DEFINED__
#define __IARPNotice_INTERFACE_DEFINED__

/* interface IARPNotice */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IARPNotice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("27F9E27F-7102-11D3-89BB-006097C68A9C")
    IARPNotice : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [in] */ VARIANT_BOOL bGiveChoice,
            /* [in] */ LicenseType lt,
            /* [retval][out] */ AcceptanceType *lResult) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ShowAgain( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_ShowAgain( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IARPNoticeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IARPNotice * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IARPNotice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IARPNotice * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IARPNotice * This,
            /* [in] */ VARIANT_BOOL bGiveChoice,
            /* [in] */ LicenseType lt,
            /* [retval][out] */ AcceptanceType *lResult);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShowAgain )( 
            IARPNotice * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ShowAgain )( 
            IARPNotice * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IARPNoticeVtbl;

    interface IARPNotice
    {
        CONST_VTBL struct IARPNoticeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IARPNotice_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IARPNotice_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IARPNotice_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IARPNotice_Show(This,bGiveChoice,lt,lResult)	\
    ( (This)->lpVtbl -> Show(This,bGiveChoice,lt,lResult) ) 

#define IARPNotice_get_ShowAgain(This,pVal)	\
    ( (This)->lpVtbl -> get_ShowAgain(This,pVal) ) 

#define IARPNotice_put_ShowAgain(This,newVal)	\
    ( (This)->lpVtbl -> put_ShowAgain(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IARPNotice_INTERFACE_DEFINED__ */


#ifndef __IWBFLErrorLog_INTERFACE_DEFINED__
#define __IWBFLErrorLog_INTERFACE_DEFINED__

/* interface IWBFLErrorLog */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IWBFLErrorLog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF5644CF-0E91-4b71-9AD6-3B50162AEA01")
    IWBFLErrorLog : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR fileName,
            /* [retval][out] */ DWORD *dwCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LogMessage( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ BSTR msg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Close( 
            /* [in] */ DWORD dwCookie) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWBFLErrorLogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWBFLErrorLog * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWBFLErrorLog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWBFLErrorLog * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IWBFLErrorLog * This,
            /* [in] */ BSTR fileName,
            /* [retval][out] */ DWORD *dwCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LogMessage )( 
            IWBFLErrorLog * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ BSTR msg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IWBFLErrorLog * This,
            /* [in] */ DWORD dwCookie);
        
        END_INTERFACE
    } IWBFLErrorLogVtbl;

    interface IWBFLErrorLog
    {
        CONST_VTBL struct IWBFLErrorLogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWBFLErrorLog_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWBFLErrorLog_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWBFLErrorLog_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWBFLErrorLog_Open(This,fileName,dwCookie)	\
    ( (This)->lpVtbl -> Open(This,fileName,dwCookie) ) 

#define IWBFLErrorLog_LogMessage(This,dwCookie,msg)	\
    ( (This)->lpVtbl -> LogMessage(This,dwCookie,msg) ) 

#define IWBFLErrorLog_Close(This,dwCookie)	\
    ( (This)->lpVtbl -> Close(This,dwCookie) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWBFLErrorLog_INTERFACE_DEFINED__ */


#ifndef __IProgressMonitorWindow_INTERFACE_DEFINED__
#define __IProgressMonitorWindow_INTERFACE_DEFINED__

/* interface IProgressMonitorWindow */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProgressMonitorWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0A64ECCB-ABA8-4F70-98CC-5C5D69A25505")
    IProgressMonitorWindow : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_HasCancel( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_HasCancel( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [in] */ BSTR initialMessage,
            /* [in] */ HWND hParent) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Hide( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_HasGauge( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_HasGauge( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProgressMonitorWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProgressMonitorWindow * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProgressMonitorWindow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProgressMonitorWindow * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasCancel )( 
            IProgressMonitorWindow * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasCancel )( 
            IProgressMonitorWindow * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IProgressMonitorWindow * This,
            /* [in] */ BSTR initialMessage,
            /* [in] */ HWND hParent);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Hide )( 
            IProgressMonitorWindow * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IProgressMonitorWindow * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasGauge )( 
            IProgressMonitorWindow * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasGauge )( 
            IProgressMonitorWindow * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IProgressMonitorWindowVtbl;

    interface IProgressMonitorWindow
    {
        CONST_VTBL struct IProgressMonitorWindowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProgressMonitorWindow_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProgressMonitorWindow_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProgressMonitorWindow_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProgressMonitorWindow_get_HasCancel(This,pVal)	\
    ( (This)->lpVtbl -> get_HasCancel(This,pVal) ) 

#define IProgressMonitorWindow_put_HasCancel(This,newVal)	\
    ( (This)->lpVtbl -> put_HasCancel(This,newVal) ) 

#define IProgressMonitorWindow_Show(This,initialMessage,hParent)	\
    ( (This)->lpVtbl -> Show(This,initialMessage,hParent) ) 

#define IProgressMonitorWindow_Hide(This)	\
    ( (This)->lpVtbl -> Hide(This) ) 

#define IProgressMonitorWindow_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IProgressMonitorWindow_get_HasGauge(This,pVal)	\
    ( (This)->lpVtbl -> get_HasGauge(This,pVal) ) 

#define IProgressMonitorWindow_put_HasGauge(This,newVal)	\
    ( (This)->lpVtbl -> put_HasGauge(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProgressMonitorWindow_INTERFACE_DEFINED__ */


#ifndef __ILogProgressToFile_INTERFACE_DEFINED__
#define __ILogProgressToFile_INTERFACE_DEFINED__

/* interface ILogProgressToFile */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILogProgressToFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D530ADC7-94D0-43a6-901E-BDEEAD53AE79")
    ILogProgressToFile : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OpenLogFile( 
            BSTR FileName) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE CloseLogFile( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILogProgressToFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILogProgressToFile * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILogProgressToFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILogProgressToFile * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OpenLogFile )( 
            ILogProgressToFile * This,
            BSTR FileName);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *CloseLogFile )( 
            ILogProgressToFile * This);
        
        END_INTERFACE
    } ILogProgressToFileVtbl;

    interface ILogProgressToFile
    {
        CONST_VTBL struct ILogProgressToFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILogProgressToFile_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILogProgressToFile_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILogProgressToFile_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILogProgressToFile_OpenLogFile(This,FileName)	\
    ( (This)->lpVtbl -> OpenLogFile(This,FileName) ) 

#define ILogProgressToFile_CloseLogFile(This)	\
    ( (This)->lpVtbl -> CloseLogFile(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILogProgressToFile_INTERFACE_DEFINED__ */


#ifndef __IEnumLongArray_INTERFACE_DEFINED__
#define __IEnumLongArray_INTERFACE_DEFINED__

/* interface IEnumLongArray */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumLongArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("79E6350B-7E91-475a-A54E-05D8AA65605B")
    IEnumLongArray : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumLongArray **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ LONG *rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumLongArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumLongArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumLongArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumLongArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumLongArray * This,
            /* [out] */ IEnumLongArray **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumLongArray * This,
            /* [in] */ ULONG celt,
            /* [out] */ LONG *rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumLongArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumLongArray * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumLongArrayVtbl;

    interface IEnumLongArray
    {
        CONST_VTBL struct IEnumLongArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumLongArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumLongArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumLongArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumLongArray_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumLongArray_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumLongArray_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumLongArray_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumLongArray_INTERFACE_DEFINED__ */


#ifndef __ILongArray_INTERFACE_DEFINED__
#define __ILongArray_INTERFACE_DEFINED__

/* interface ILongArray */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILongArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B0BF1679-929A-466C-8F95-A7D6FA825307")
    ILongArray : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumLongArray **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILongArray **clone) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ReDim( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ long value,
            /* [retval][out] */ CollectionIndexType *fndIndex) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ LONG item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType relPosition) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ LONG item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType count) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILongArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILongArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILongArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILongArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ILongArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            ILongArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ LONG newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ILongArray * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ILongArray * This,
            /* [retval][out] */ IEnumLongArray **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILongArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILongArray * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILongArray * This,
            /* [retval][out] */ ILongArray **clone);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ReDim )( 
            ILongArray * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ILongArray * This,
            /* [in] */ long value,
            /* [retval][out] */ CollectionIndexType *fndIndex);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILongArray * This,
            /* [in] */ LONG item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ILongArray * This,
            /* [in] */ CollectionIndexType relPosition);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ILongArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ LONG item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            ILongArray * This,
            /* [in] */ CollectionIndexType count);
        
        END_INTERFACE
    } ILongArrayVtbl;

    interface ILongArray
    {
        CONST_VTBL struct ILongArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILongArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILongArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILongArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILongArray_get_Item(This,relPosition,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,relPosition,pVal) ) 

#define ILongArray_put_Item(This,relPosition,newVal)	\
    ( (This)->lpVtbl -> put_Item(This,relPosition,newVal) ) 

#define ILongArray_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ILongArray_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ILongArray_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILongArray_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILongArray_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ILongArray_ReDim(This,size)	\
    ( (This)->lpVtbl -> ReDim(This,size) ) 

#define ILongArray_Find(This,value,fndIndex)	\
    ( (This)->lpVtbl -> Find(This,value,fndIndex) ) 

#define ILongArray_Add(This,item)	\
    ( (This)->lpVtbl -> Add(This,item) ) 

#define ILongArray_Remove(This,relPosition)	\
    ( (This)->lpVtbl -> Remove(This,relPosition) ) 

#define ILongArray_Insert(This,relPosition,item)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,item) ) 

#define ILongArray_Reserve(This,count)	\
    ( (This)->lpVtbl -> Reserve(This,count) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILongArray_INTERFACE_DEFINED__ */


#ifndef __IEnumIDArray_INTERFACE_DEFINED__
#define __IEnumIDArray_INTERFACE_DEFINED__

/* interface IEnumIDArray */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumIDArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6189734A-45B5-4a71-8DC1-68B030035B52")
    IEnumIDArray : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumIDArray **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IDType *rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumIDArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumIDArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumIDArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumIDArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumIDArray * This,
            /* [out] */ IEnumIDArray **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumIDArray * This,
            /* [in] */ ULONG celt,
            /* [out] */ IDType *rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumIDArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumIDArray * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumIDArrayVtbl;

    interface IEnumIDArray
    {
        CONST_VTBL struct IEnumIDArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumIDArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumIDArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumIDArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumIDArray_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumIDArray_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumIDArray_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumIDArray_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumIDArray_INTERFACE_DEFINED__ */


#ifndef __IIDArray_INTERFACE_DEFINED__
#define __IIDArray_INTERFACE_DEFINED__

/* interface IIDArray */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IIDArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8F36811E-3E9D-406a-AF6E-99AE377796BD")
    IIDArray : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ IDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IDType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumIDArray **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IIDArray **clone) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ReDim( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ IDType value,
            /* [retval][out] */ CollectionIndexType *fndIndex) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IDType item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType relPosition) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IDType item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType count) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIDArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIDArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIDArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIDArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IIDArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ IDType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IIDArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IDType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IIDArray * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IIDArray * This,
            /* [retval][out] */ IEnumIDArray **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IIDArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IIDArray * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IIDArray * This,
            /* [retval][out] */ IIDArray **clone);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ReDim )( 
            IIDArray * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IIDArray * This,
            /* [in] */ IDType value,
            /* [retval][out] */ CollectionIndexType *fndIndex);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IIDArray * This,
            /* [in] */ IDType item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IIDArray * This,
            /* [in] */ CollectionIndexType relPosition);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IIDArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IDType item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            IIDArray * This,
            /* [in] */ CollectionIndexType count);
        
        END_INTERFACE
    } IIDArrayVtbl;

    interface IIDArray
    {
        CONST_VTBL struct IIDArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIDArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIDArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIDArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIDArray_get_Item(This,relPosition,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,relPosition,pVal) ) 

#define IIDArray_put_Item(This,relPosition,newVal)	\
    ( (This)->lpVtbl -> put_Item(This,relPosition,newVal) ) 

#define IIDArray_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IIDArray_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IIDArray_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IIDArray_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IIDArray_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IIDArray_ReDim(This,size)	\
    ( (This)->lpVtbl -> ReDim(This,size) ) 

#define IIDArray_Find(This,value,fndIndex)	\
    ( (This)->lpVtbl -> Find(This,value,fndIndex) ) 

#define IIDArray_Add(This,item)	\
    ( (This)->lpVtbl -> Add(This,item) ) 

#define IIDArray_Remove(This,relPosition)	\
    ( (This)->lpVtbl -> Remove(This,relPosition) ) 

#define IIDArray_Insert(This,relPosition,item)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,item) ) 

#define IIDArray_Reserve(This,count)	\
    ( (This)->lpVtbl -> Reserve(This,count) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIDArray_INTERFACE_DEFINED__ */


#ifndef __IEnumIndexArray_INTERFACE_DEFINED__
#define __IEnumIndexArray_INTERFACE_DEFINED__

/* interface IEnumIndexArray */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumIndexArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E069B7E0-762D-4f4c-9A77-48A98AC82585")
    IEnumIndexArray : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumIndexArray **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ CollectionIndexType *rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumIndexArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumIndexArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumIndexArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumIndexArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumIndexArray * This,
            /* [out] */ IEnumIndexArray **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumIndexArray * This,
            /* [in] */ ULONG celt,
            /* [out] */ CollectionIndexType *rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumIndexArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumIndexArray * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumIndexArrayVtbl;

    interface IEnumIndexArray
    {
        CONST_VTBL struct IEnumIndexArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumIndexArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumIndexArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumIndexArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumIndexArray_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumIndexArray_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumIndexArray_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumIndexArray_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumIndexArray_INTERFACE_DEFINED__ */


#ifndef __IIndexArray_INTERFACE_DEFINED__
#define __IIndexArray_INTERFACE_DEFINED__

/* interface IIndexArray */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IIndexArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C074A733-E1AB-419f-811F-56D192517490")
    IIndexArray : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ CollectionIndexType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumIndexArray **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IIndexArray **clone) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ReDim( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ CollectionIndexType value,
            /* [retval][out] */ CollectionIndexType *fndIndex) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ CollectionIndexType item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType relPosition) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ CollectionIndexType item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType count) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Assign( 
            /* [in] */ CollectionIndexType numElements,
            /* [in] */ CollectionIndexType value) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIndexArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIndexArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIndexArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIndexArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IIndexArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IIndexArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ CollectionIndexType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IIndexArray * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IIndexArray * This,
            /* [retval][out] */ IEnumIndexArray **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IIndexArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IIndexArray * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IIndexArray * This,
            /* [retval][out] */ IIndexArray **clone);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ReDim )( 
            IIndexArray * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IIndexArray * This,
            /* [in] */ CollectionIndexType value,
            /* [retval][out] */ CollectionIndexType *fndIndex);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IIndexArray * This,
            /* [in] */ CollectionIndexType item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IIndexArray * This,
            /* [in] */ CollectionIndexType relPosition);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IIndexArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ CollectionIndexType item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            IIndexArray * This,
            /* [in] */ CollectionIndexType count);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Assign )( 
            IIndexArray * This,
            /* [in] */ CollectionIndexType numElements,
            /* [in] */ CollectionIndexType value);
        
        END_INTERFACE
    } IIndexArrayVtbl;

    interface IIndexArray
    {
        CONST_VTBL struct IIndexArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIndexArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIndexArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIndexArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIndexArray_get_Item(This,relPosition,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,relPosition,pVal) ) 

#define IIndexArray_put_Item(This,relPosition,newVal)	\
    ( (This)->lpVtbl -> put_Item(This,relPosition,newVal) ) 

#define IIndexArray_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IIndexArray_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IIndexArray_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IIndexArray_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IIndexArray_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IIndexArray_ReDim(This,size)	\
    ( (This)->lpVtbl -> ReDim(This,size) ) 

#define IIndexArray_Find(This,value,fndIndex)	\
    ( (This)->lpVtbl -> Find(This,value,fndIndex) ) 

#define IIndexArray_Add(This,item)	\
    ( (This)->lpVtbl -> Add(This,item) ) 

#define IIndexArray_Remove(This,relPosition)	\
    ( (This)->lpVtbl -> Remove(This,relPosition) ) 

#define IIndexArray_Insert(This,relPosition,item)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,item) ) 

#define IIndexArray_Reserve(This,count)	\
    ( (This)->lpVtbl -> Reserve(This,count) ) 

#define IIndexArray_Assign(This,numElements,value)	\
    ( (This)->lpVtbl -> Assign(This,numElements,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIndexArray_INTERFACE_DEFINED__ */


#ifndef __IEnumDblArray_INTERFACE_DEFINED__
#define __IEnumDblArray_INTERFACE_DEFINED__

/* interface IEnumDblArray */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumDblArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EB880B96-ACFF-4d1c-BFFD-FC032A3E1D00")
    IEnumDblArray : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumDblArray **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ Float64 *rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumDblArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumDblArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumDblArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumDblArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumDblArray * This,
            /* [out] */ IEnumDblArray **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumDblArray * This,
            /* [in] */ ULONG celt,
            /* [out] */ Float64 *rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumDblArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumDblArray * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumDblArrayVtbl;

    interface IEnumDblArray
    {
        CONST_VTBL struct IEnumDblArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumDblArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumDblArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumDblArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumDblArray_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumDblArray_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumDblArray_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumDblArray_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumDblArray_INTERFACE_DEFINED__ */


#ifndef __IDblArray_INTERFACE_DEFINED__
#define __IDblArray_INTERFACE_DEFINED__

/* interface IDblArray */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDblArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CABA1F9A-CEE0-40E6-91CA-18D3F4FC0718")
    IDblArray : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumDblArray **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IDblArray **clone) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ReDim( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ Float64 item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType relPosition) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ Float64 item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType count) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDblArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDblArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDblArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDblArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IDblArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IDblArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IDblArray * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IDblArray * This,
            /* [retval][out] */ IEnumDblArray **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IDblArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IDblArray * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDblArray * This,
            /* [retval][out] */ IDblArray **clone);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ReDim )( 
            IDblArray * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IDblArray * This,
            /* [in] */ Float64 item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IDblArray * This,
            /* [in] */ CollectionIndexType relPosition);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IDblArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ Float64 item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            IDblArray * This,
            /* [in] */ CollectionIndexType count);
        
        END_INTERFACE
    } IDblArrayVtbl;

    interface IDblArray
    {
        CONST_VTBL struct IDblArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDblArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDblArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDblArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDblArray_get_Item(This,relPosition,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,relPosition,pVal) ) 

#define IDblArray_put_Item(This,relPosition,newVal)	\
    ( (This)->lpVtbl -> put_Item(This,relPosition,newVal) ) 

#define IDblArray_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IDblArray_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IDblArray_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IDblArray_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IDblArray_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IDblArray_ReDim(This,size)	\
    ( (This)->lpVtbl -> ReDim(This,size) ) 

#define IDblArray_Add(This,item)	\
    ( (This)->lpVtbl -> Add(This,item) ) 

#define IDblArray_Remove(This,relPosition)	\
    ( (This)->lpVtbl -> Remove(This,relPosition) ) 

#define IDblArray_Insert(This,relPosition,item)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,item) ) 

#define IDblArray_Reserve(This,count)	\
    ( (This)->lpVtbl -> Reserve(This,count) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDblArray_INTERFACE_DEFINED__ */


#ifndef __IEnumBstrArray_INTERFACE_DEFINED__
#define __IEnumBstrArray_INTERFACE_DEFINED__

/* interface IEnumBstrArray */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumBstrArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("68F75050-236A-4a73-B1D1-25A48221CFEF")
    IEnumBstrArray : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumBstrArray **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ BSTR *rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumBstrArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumBstrArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumBstrArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumBstrArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumBstrArray * This,
            /* [out] */ IEnumBstrArray **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumBstrArray * This,
            /* [in] */ ULONG celt,
            /* [out] */ BSTR *rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumBstrArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumBstrArray * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumBstrArrayVtbl;

    interface IEnumBstrArray
    {
        CONST_VTBL struct IEnumBstrArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumBstrArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumBstrArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumBstrArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumBstrArray_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumBstrArray_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumBstrArray_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumBstrArray_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumBstrArray_INTERFACE_DEFINED__ */


#ifndef __IBstrArray_INTERFACE_DEFINED__
#define __IBstrArray_INTERFACE_DEFINED__

/* interface IBstrArray */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBstrArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("505C846A-96F9-42FD-8202-C06170538E65")
    IBstrArray : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumBstrArray **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IBstrArray **clone) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ReDim( 
            /* [in] */ CollectionIndexType size) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ BSTR value,
            /* [retval][out] */ CollectionIndexType *fndIndex) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType relPosition) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ BSTR item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType count) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBstrArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBstrArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBstrArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBstrArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IBstrArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IBstrArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IBstrArray * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IBstrArray * This,
            /* [retval][out] */ IEnumBstrArray **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IBstrArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IBstrArray * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IBstrArray * This,
            /* [retval][out] */ IBstrArray **clone);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ReDim )( 
            IBstrArray * This,
            /* [in] */ CollectionIndexType size);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IBstrArray * This,
            /* [in] */ BSTR value,
            /* [retval][out] */ CollectionIndexType *fndIndex);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IBstrArray * This,
            /* [in] */ BSTR item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IBstrArray * This,
            /* [in] */ CollectionIndexType relPosition);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IBstrArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ BSTR item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            IBstrArray * This,
            /* [in] */ CollectionIndexType count);
        
        END_INTERFACE
    } IBstrArrayVtbl;

    interface IBstrArray
    {
        CONST_VTBL struct IBstrArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBstrArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBstrArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBstrArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBstrArray_get_Item(This,relPosition,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,relPosition,pVal) ) 

#define IBstrArray_put_Item(This,relPosition,newVal)	\
    ( (This)->lpVtbl -> put_Item(This,relPosition,newVal) ) 

#define IBstrArray_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IBstrArray_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IBstrArray_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IBstrArray_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IBstrArray_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IBstrArray_ReDim(This,size)	\
    ( (This)->lpVtbl -> ReDim(This,size) ) 

#define IBstrArray_Find(This,value,fndIndex)	\
    ( (This)->lpVtbl -> Find(This,value,fndIndex) ) 

#define IBstrArray_Add(This,item)	\
    ( (This)->lpVtbl -> Add(This,item) ) 

#define IBstrArray_Remove(This,relPosition)	\
    ( (This)->lpVtbl -> Remove(This,relPosition) ) 

#define IBstrArray_Insert(This,relPosition,item)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,item) ) 

#define IBstrArray_Reserve(This,count)	\
    ( (This)->lpVtbl -> Reserve(This,count) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBstrArray_INTERFACE_DEFINED__ */


#ifndef __IEnumUnkArray_INTERFACE_DEFINED__
#define __IEnumUnkArray_INTERFACE_DEFINED__

/* interface IEnumUnkArray */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumUnkArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ADD1A335-0A98-4ae5-9C7C-7DAEB7718DE3")
    IEnumUnkArray : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumUnkArray **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IUnknown **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumUnkArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumUnkArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumUnkArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumUnkArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumUnkArray * This,
            /* [out] */ IEnumUnkArray **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumUnkArray * This,
            /* [in] */ ULONG celt,
            /* [out] */ IUnknown **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumUnkArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumUnkArray * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumUnkArrayVtbl;

    interface IEnumUnkArray
    {
        CONST_VTBL struct IEnumUnkArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumUnkArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumUnkArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumUnkArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumUnkArray_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumUnkArray_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumUnkArray_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumUnkArray_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumUnkArray_INTERFACE_DEFINED__ */


#ifndef __IUnkArray_INTERFACE_DEFINED__
#define __IUnkArray_INTERFACE_DEFINED__

/* interface IUnkArray */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnkArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F7E15329-3F3B-4161-9C9C-43ED3F9B689C")
    IUnkArray : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IUnknown *newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumUnkArray **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IUnkArray **clone) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IUnknown *item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType relPosition) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IUnknown *item) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ CollectionIndexType count) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnkArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnkArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnkArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnkArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IUnkArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IUnkArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IUnknown *newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IUnkArray * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IUnkArray * This,
            /* [retval][out] */ IEnumUnkArray **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IUnkArray * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IUnkArray * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IUnkArray * This,
            /* [retval][out] */ IUnkArray **clone);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IUnkArray * This,
            /* [in] */ IUnknown *item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IUnkArray * This,
            /* [in] */ CollectionIndexType relPosition);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IUnkArray * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IUnknown *item);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            IUnkArray * This,
            /* [in] */ CollectionIndexType count);
        
        END_INTERFACE
    } IUnkArrayVtbl;

    interface IUnkArray
    {
        CONST_VTBL struct IUnkArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnkArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnkArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnkArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnkArray_get_Item(This,relPosition,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,relPosition,pVal) ) 

#define IUnkArray_put_Item(This,relPosition,newVal)	\
    ( (This)->lpVtbl -> put_Item(This,relPosition,newVal) ) 

#define IUnkArray_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IUnkArray_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IUnkArray_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IUnkArray_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IUnkArray_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IUnkArray_Add(This,item)	\
    ( (This)->lpVtbl -> Add(This,item) ) 

#define IUnkArray_Remove(This,relPosition)	\
    ( (This)->lpVtbl -> Remove(This,relPosition) ) 

#define IUnkArray_Insert(This,relPosition,item)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,item) ) 

#define IUnkArray_Reserve(This,count)	\
    ( (This)->lpVtbl -> Reserve(This,count) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnkArray_INTERFACE_DEFINED__ */


#ifndef __IProgressMonitor_INTERFACE_DEFINED__
#define __IProgressMonitor_INTERFACE_DEFINED__

/* interface IProgressMonitor */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProgressMonitor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B9CDE114-D5D8-4acc-A764-DF0C2863E028")
    IProgressMonitor : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GaugeValue( 
            /* [in] */ long cookie,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Message( 
            /* [in] */ long cookie,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WasCancelled( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProgressMonitorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProgressMonitor * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProgressMonitor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProgressMonitor * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GaugeValue )( 
            IProgressMonitor * This,
            /* [in] */ long cookie,
            /* [in] */ long newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Message )( 
            IProgressMonitor * This,
            /* [in] */ long cookie,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WasCancelled )( 
            IProgressMonitor * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IProgressMonitorVtbl;

    interface IProgressMonitor
    {
        CONST_VTBL struct IProgressMonitorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProgressMonitor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProgressMonitor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProgressMonitor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProgressMonitor_put_GaugeValue(This,cookie,newVal)	\
    ( (This)->lpVtbl -> put_GaugeValue(This,cookie,newVal) ) 

#define IProgressMonitor_put_Message(This,cookie,newVal)	\
    ( (This)->lpVtbl -> put_Message(This,cookie,newVal) ) 

#define IProgressMonitor_get_WasCancelled(This,pVal)	\
    ( (This)->lpVtbl -> get_WasCancelled(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProgressMonitor_INTERFACE_DEFINED__ */


#ifndef __ISupportProgressMonitor_INTERFACE_DEFINED__
#define __ISupportProgressMonitor_INTERFACE_DEFINED__

/* interface ISupportProgressMonitor */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISupportProgressMonitor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6F2C304-53CF-4033-BC49-193B50077F3E")
    ISupportProgressMonitor : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitializeProgressMonitor( 
            /* [in] */ IProgressMonitor *newVal,
            /* [in] */ long cookie) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportProgressMonitorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupportProgressMonitor * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupportProgressMonitor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupportProgressMonitor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitializeProgressMonitor )( 
            ISupportProgressMonitor * This,
            /* [in] */ IProgressMonitor *newVal,
            /* [in] */ long cookie);
        
        END_INTERFACE
    } ISupportProgressMonitorVtbl;

    interface ISupportProgressMonitor
    {
        CONST_VTBL struct ISupportProgressMonitorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupportProgressMonitor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupportProgressMonitor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupportProgressMonitor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupportProgressMonitor_InitializeProgressMonitor(This,newVal,cookie)	\
    ( (This)->lpVtbl -> InitializeProgressMonitor(This,newVal,cookie) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupportProgressMonitor_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MohrCircle;

#ifdef __cplusplus

class DECLSPEC_UUID("E590D201-FF47-11D2-8CDF-F43C3928A334")
MohrCircle;
#endif

EXTERN_C const CLSID CLSID_ARPNotice;

#ifdef __cplusplus

class DECLSPEC_UUID("27F9E280-7102-11D3-89BB-006097C68A9C")
ARPNotice;
#endif

EXTERN_C const CLSID CLSID_StructuredSave2;

#ifdef __cplusplus

class DECLSPEC_UUID("043B36E6-64EE-11d5-B017-00105A9AF985")
StructuredSave2;
#endif

EXTERN_C const CLSID CLSID_StructuredLoad2;

#ifdef __cplusplus

class DECLSPEC_UUID("043B36E7-64EE-11d5-B017-00105A9AF985")
StructuredLoad2;
#endif

EXTERN_C const CLSID CLSID_WBFLErrorLog;

#ifdef __cplusplus

class DECLSPEC_UUID("49E8A61D-E83B-4b60-B0D7-96B0D1A96CC3")
WBFLErrorLog;
#endif

EXTERN_C const CLSID CLSID_ProgressMonitor;

#ifdef __cplusplus

class DECLSPEC_UUID("28706F21-DA7C-45C8-866C-3285BCAF3434")
ProgressMonitor;
#endif

EXTERN_C const CLSID CLSID_ProgressMonitorWindow;

#ifdef __cplusplus

class DECLSPEC_UUID("8C63C999-10B8-43B5-A7CC-72B6AC48283F")
ProgressMonitorWindow;
#endif

EXTERN_C const CLSID CLSID_LongArray;

#ifdef __cplusplus

class DECLSPEC_UUID("51EAE330-F430-492C-95A1-A755D76A8C4F")
LongArray;
#endif

EXTERN_C const CLSID CLSID_IDArray;

#ifdef __cplusplus

class DECLSPEC_UUID("78227B01-D41C-47e7-BE49-6A8CF2EB833A")
IDArray;
#endif

EXTERN_C const CLSID CLSID_IndexArray;

#ifdef __cplusplus

class DECLSPEC_UUID("0AA0835E-C025-48c6-A9DD-CD33C0BBFB7B")
IndexArray;
#endif

EXTERN_C const CLSID CLSID_DblArray;

#ifdef __cplusplus

class DECLSPEC_UUID("851D2378-0F8C-4040-8E84-B26C5E7F9528")
DblArray;
#endif

EXTERN_C const CLSID CLSID_BstrArray;

#ifdef __cplusplus

class DECLSPEC_UUID("FA223DB0-69C7-4FB6-90CC-0C20BE566982")
BstrArray;
#endif

EXTERN_C const CLSID CLSID_UnkArray;

#ifdef __cplusplus

class DECLSPEC_UUID("88D26763-7BD5-4F92-A064-7497A72E7D81")
UnkArray;
#endif
#endif /* __WBFLTools_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


